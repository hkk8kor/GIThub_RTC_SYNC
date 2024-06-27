'''
/**
  * \Reference
  * Gen_SWCS_HSW_uC_Base_SYS-290
  *
  * \Purpose
  * Test whether execution from RAM is caught by MPU configuration and handled correctly.
  *
  * \Sequence
  * For each core and each start and end address of RAM do the following:
  *   1. Run until end of Init task
  *   2. Overwrite program counter with RAM address
  *   3. Run until reset
  *   4. Run until end of Init task
  *   5. Run until BFM was updated
  *
  * \ExpectedResult
  * At 1. RBSYS_SYSErrorHook is not failed
  * At 3. reset is triggered
  * At 4. RBSYS_SYSErrorHook is failed
  * At 5. RBSYS_SYSErrorHook is in BFM with correct debug data
  */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.application as app
import swt2.environment as env
import swt2.software as sw
import DeviceInfo


app.execution_condition(include_switches=["RBFS_TPSWSVPRestrictions_ON"])

#############################################################################
#                             Setup                                         #
#############################################################################
# get boundary addresses of RAMs
device_info = DeviceInfo.getDeviceInfoBasedOnSWConfig()
RAMs = filter(lambda ram: ram is not None, device_info.GlobalRAM + device_info.LocalRAM)
RAM_addresses_to_test =  [start              for start,_    in RAMs]  # start address of RAMs
RAM_addresses_to_test += [(start + size - 4) for start,size in RAMs]  # end address of RAMs

if env.is_renesas_p1x_device():
  LRAM_self_end = 0xFEE00000
elif env.is_renesas_u2a_device():
  LRAM_self_end = 0xFDE10000
elif env.is_renesas_u2c_device():
  LRAM_self_end = 0xFDE20000
LRAM_self_start = LRAM_self_end - device_info.LocalRAM[0][1]
RAM_addresses_to_test += [LRAM_self_start, LRAM_self_end - 4] # start and end address of LRAM self

print("Execution will be triggered at the following addresses:")
for addr in RAM_addresses_to_test:
  print(hex(addr))

# stub flash test due to performance issues
sw.get_function("RBROMSafety_InitialFlashTest").stub()
sw.get_function("RBROMSafety_PRC_CyclicFlashTest").stub()

#############################################################################
#                             Test start                                    #
#############################################################################
tst.start()

for RAM_address in RAM_addresses_to_test:
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
    # 2. Overwrite program counter with RAM address
    core.get_program_counter_register().write(RAM_address)

    #############################################################################
    #                             Failure must be set                           #
    #############################################################################
    # 3. Run until reset
    br = tgt.run_until_reset()
    # reset is triggered
    tst.eval(tgt.is_breakpoint_hit(br))

    # 4. Run until end of Init task
    app.run_until_end_of_init()
    # RBSYS_SYSErrorHook is failed
    tst.eval(app.get_event("RBSYS_SYSErrorHook").is_failed())

    #############################################################################
    #                Epilogue, check BfmRecord debug values and reset           #
    #############################################################################
    # 5. Run until BFM was updated
    #app.run_until_bfm_was_updated()
    # temporary workaround
    tgt.run_until_end_of("Os_Entry_TaskBaseCtrlCycx4")
    tgt.run_until_end_of("Os_Entry_TaskBaseCtrlCycx4")
    # RBSYS_SYSErrorHook is in BFM with correct debug data
    bfm_record = app.get_bfm_record("RBSYS_SYSErrorHook")
    tst.eval(bfm_record)
    if bfm_record:
      tst.eval_eq(bfm_record.get_debug0(), 7)
      tst.eval_eq(bfm_record.get_debug1(), RAM_address)

    app.do_test_environment_reset()

tst.end()