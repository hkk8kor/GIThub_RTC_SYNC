'''
/**
  * \Reference
  *
  * \Purpose
  * Test whether writing to ROM is caught by MPU configuration and handled correctly.
  *
  * \Sequence
  * For each core and each start and end address of ROM do the following:
  *   1. Run until end of init task
  *   2. Run until store instruction in current core
  *   3. Change store destination address to ROM
  *   4. Run until reset
  *   5. Run until end of Init task
  *   6. Run until BFM was updated
  *
  * \ExpectedResult
  * At 1. RBSYS_SYSErrorHook is not failed
  * At 4. reset is triggered
  * At 5. RBSYS_SYSErrorHook is failed
  * At 6. RBSYS_SYSErrorHook is in BFM with correct debug data
  */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.application as app
import swt2.software as sw
import swt2.environment as env
import swt2.software.assembly._rh850 as _rh850
import DeviceInfo


app.execution_condition(include_switches=["RBFS_TPSWSVPRestrictions_ON"])

#############################################################################
#                             Setup                                         #
#############################################################################
# get boundary addresses of flash banks
target_device = app.get_function_switch_setting("RBFS_TargetDevice")[-2:]
map_mode = app.get_function_switch_setting("RBFS_CodeFlashMemoryMode").split("_")[-1] + "Mode"
target_device_info = DeviceInfo.getDeviceInfoBasedOnSWConfig()
ROMs = target_device_info.CodeFlash # todo: this is missing inactive flash banks in double map mode, they are not tested at the moment
ROM_addresses = []
i = 0
while i < len(ROMs):
  if i+1 < len(ROMs) and ROMs[i][2] < ROMs[i+1][2]:
    ROM_addresses.append([ROMs[i][0], ROMs[i+1][0]+ROMs[i+1][1]*ROMs[i+1][2]-4])
    i += 1
  else:
    ROM_addresses.append([ROMs[i][0], ROMs[i][0]+ROMs[i][1]*ROMs[i][2]-4])
  i += 1


# if HSM is supported its code flash is excluded from the MPU configuration
if app.get_function_switch_setting("RBFS_HardwareSecurityModule") == "RBFS_HardwareSecurityModule_Supported":
  RBFS_HSMBlockSize = app.get_function_switch_setting("RBFS_HSMBlockSize")
  if RBFS_HSMBlockSize != "RBFS_HSMBlockSize_Customized":
    hsm_size = int(RBFS_HSMBlockSize.split("_")[-1][:-2]) * 1024
  else:
    hsm_size = 0 # todo

  if target_device == "D3":
    ROM_addresses[0][1] -= hsm_size
  else:
    ROM_addresses[-1][1] -= hsm_size

ROM_addresses_to_test = []
for rom in ROM_addresses:
  ROM_addresses_to_test.append(rom[0])
  ROM_addresses_to_test.append(rom[1])

print("A write operation will be triggered at the following addresses:")
for addr in ROM_addresses_to_test:
  print(hex(addr))


# set breakpoints on store instructions that are executed on all cores
functions = ["RBTaskMon_CheckTaskActivation"] #todo find suitable functions in RBSYS
store_instruction_addresses = []
for function in functions:
  disassembly = sw.get_function(function).get_disassembly()
  store_instruction_addresses += [i.address for i in disassembly if i.instruction.startswith("st.") or i.instruction.startswith("sst.")]
bps = []
for address in store_instruction_addresses:
  bp = tgt.add_breakpoint(address)
  bp.disable()
  bps.append(bp)

# stub flash test due to performance issues
sw.get_function("RBROMSafety_InitialFlashTest").stub()
sw.get_function("RBROMSafety_PRC_CyclicFlashTest").stub()

#############################################################################
#                             Test start                                    #
#############################################################################
tst.start()

for ROM_address in ROM_addresses_to_test:
  for core in app.get_used_cores():
    #############################################################################
    #              GoodCheck -> Failure is not already set                      #
    #############################################################################
    # 1. Run until end of Init task
    app.run_until_end_of_init(core=core)
    # RBSYS_SYSErrorHook is not failed
    tst.eval(not app.get_event("RBSYS_SYSErrorHook").is_failed())

    #############################################################################
    #                             Manipulation                                  #
    #############################################################################
    # 2. Run until store instruction in current core
    for bp in bps:
      bp.enable()
    br = tgt.run()
    while br.core != core:
      br = tgt.run()
    for bp in bps:
      bp.disable()

    # 3. Change store destination address to ROM
    tst.eval(br.breakpoint in bps)
    if br.breakpoint in bps:
      store_instruction = sw.read_instruction(core.get_program_counter_register().read())
      content_register = _rh850.decode_reg(store_instruction.parameters[0])
      displacement, destination_register = _rh850.decode_disp_with_reg(store_instruction.parameters[1],23)
      register = core.get_register("r%d"%destination_register)
      original_value = register.read()
      register.write(ROM_address - displacement)
      core.step()
      register.write(original_value) # restore register as it could be r4/gp


    #############################################################################
    #                             Failure must be set                           #
    #############################################################################
    # 4. Run until reset
    br = tgt.run_until_reset()
    # reset is triggered
    tst.eval(tgt.is_breakpoint_hit(br))

    # 5. Run until end of Init task
    app.run_until_end_of_init()
    # RBSYS_SYSErrorHook is failed
    tst.eval(app.get_event("RBSYS_SYSErrorHook").is_failed())

    #############################################################################
    #                Epilogue, check BfmRecord debug values and reset           #
    #############################################################################
    # 6. Run until BFM was updated
    app.run_until_bfm_was_updated()
    # RBSYS_SYSErrorHook is in BFM with correct debug data
    bfm_record = app.get_bfm_record("RBSYS_SYSErrorHook")
    tst.eval(bfm_record)
    if bfm_record:
      tst.eval_eq(bfm_record.get_debug0(), 7)
      tst.eval_eq(bfm_record.get_debug1(), store_instruction.address)

    app.do_test_environment_reset()

tst.end()