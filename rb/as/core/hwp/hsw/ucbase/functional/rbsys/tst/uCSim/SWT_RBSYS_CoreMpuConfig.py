'''
/**
  * \Reference
  *
  * \Purpose
  * Test whether the core MPU regions are correctly configured.
  *
  * \Sequence
  * 1. Run until main
  * For each core do the following:
  *   2. Collect MPU region configurations
  *
  * \ExpectedResult
  * At 2. for each ROM and RAM of the device and the background region there is exactly one matching MPU region configured and enabled and no other MPU regions are enabled.
  */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.application as app
import swt2.environment as env
import DeviceInfo


app.execution_condition()

#############################################################################
#                             Setup                                         #
#############################################################################
# get physical RAM and ROM regions of target device
target_device = app.get_function_switch_setting("RBFS_TargetDevice")[-2:]
map_mode = app.get_function_switch_setting("RBFS_CodeFlashMemoryMode").split("_")[-1] + "Mode"
if env.is_renesas_p1x_device():
  target_device_info = DeviceInfo.getDeviceInfo(target_device)
else:
  target_device_info = DeviceInfo.getDeviceInfo(target_device, map_mode)


# prepare RAM address ranges that should be configured: all avaiblabe global RAM and local RAM of used cores
RAMs = filter(lambda ram: ram is not None, target_device_info.GlobalRAM + target_device_info.LocalRAM[:app.get_number_of_used_cores()])
RAM_addresses = [[start,start+size-4] for start,size in RAMs]

# D1/2 software compiled for emulation devices changes start address of LRAM
if app.get_function_switch_setting("RBFS_EmulationDevice") != "RBFS_EmulationDevice_None":
  target_device = app.get_function_switch_setting("RBFS_TargetDevice")[-2:]
  if target_device == "D1":
    RAM_addresses[0][0] -= 0x10000
  elif target_device == "D2":
    RAM_addresses[0][0] -= 0x7000

print("The following RAM address ranges should be configured:")
for ram in RAM_addresses:
  print("From %s to %s"%(hex(ram[0]),hex(ram[1])))


# prepare ROM address ranges that should be configured
ROMs = target_device_info.CodeFlash # hint: this is missing inactive flash banks in double map mode
ROM_addresses = []

# recreate flash banks from DDF.ini data
i = 0
while i < len(ROMs):
  if i+1 < len(ROMs) and ROMs[i][2] < ROMs[i+1][2]:
    ROM_addresses.append([ROMs[i][0], ROMs[i+1][0]+ROMs[i+1][1]*ROMs[i+1][2]-4])
    i += 1
  else:
    ROM_addresses.append([ROMs[i][0], ROMs[i][0]+ROMs[i][1]*ROMs[i][2]-4])
  i += 1

# software compiled for emulation devices gets more flash than on target device
if app.get_function_switch_setting("RBFS_EmulationDevice") != "RBFS_EmulationDevice_None":
  if target_device == "D1":
    ROM_addresses[0][1] += 1.5*1024*1024
  elif target_device == "D2":
    ROM_addresses[0][1] += 1*1024*1024
  elif target_device == "D3":
    ROM_addresses.append((0x00800000, 0x00800000 + 512*1024 - 4))
  elif target_device == "D4":
    ROM_addresses[0][1] += 1*1024*1024
  elif target_device == "D5":
    ROM_addresses[0][1] += 2*1024*1024
  elif target_device == "M2" and app.get_function_switch_setting("RBFS_CodeFlashMemoryMode") == "RBFS_CodeFlashMemoryMode_SingleMap":
    ROM_addresses[0][1] += 1*1024*1024

# if HSM is supported its code flash is excluded from the MPU configuration
if app.get_function_switch_setting("RBFS_HardwareSecurityModule") == "RBFS_HardwareSecurityModule_Supported":
  RBFS_HSMBlockSize = app.get_function_switch_setting("RBFS_HSMBlockSize")
  if RBFS_HSMBlockSize != "RBFS_HSMBlockSize_Customized":
    hsm_size = int(RBFS_HSMBlockSize.split("_")[-1][:-2]) * 1024
  else:
    hsm_size = 0 # todo

  # remove HSM size from end of last flash bank except with D3 where it has to be removed from first flash bank
  if target_device == "D3":
    ROM_addresses[0][1] -= hsm_size
  else:
    ROM_addresses[-1][1] -= hsm_size

# background region start at end of ROM (ignoring inactive banks at the moment, if changed just move this down a few lines) until the end of 32bit address range
background_region = [ROM_addresses[-1][1] + 4, 0xFFFFFFFC]
print("The following background region should be configured:")
print("From %s to %s"%(hex(background_region[0]),hex(background_region[1])))

# for double map mode add a copy of the active ROM banks at the inactive ROM banks offset
if app.get_function_switch_setting("RBFS_CodeFlashMemoryMode") == "RBFS_CodeFlashMemoryMode_DoubleMap":
  ROM_addresses += [[start + 0x02000000, end + 0x02000000] for start, end in ROM_addresses]

print("The following ROM address ranges should be configured:")
for rom in ROM_addresses:
  print("From %s to %s"%(hex(rom[0]),hex(rom[1])))


#############################################################################
#                             Test start                                    #
#############################################################################
tst.start()

tgt.run_until("main")
for core in app.get_used_cores():
  regions = []
  mpm = core.get_register("MPM").read()
  mea = core.get_register("MEA").read()
  mei = core.get_register("MEI").read()
  print("MPU configuration of core %d:"%core.get_index())
  if env.is_renesas_p1x_device():
    for i in range(16):
      mpla = core.get_register("MPLA%d"%i).read()
      mpua = core.get_register("MPUA%d"%i).read()
      mpat = core.get_register("MPAT%d"%i).read()
      print("Region %i start: %s, end: %s, attributes: %s"%(i,hex(mpla),hex(mpua),hex(mpat)))
      regions.append((mpla,mpua,mpat))
  else:
    for i in range(16):
      core.get_register("MPIDX").write(i)
      mpla = core.get_register("MPLA").read()
      mpua = core.get_register("MPUA").read()
      mpat = core.get_register("MPAT").read()
      print("Region %i start: %s, end: %s, attributes: %s"%(i,hex(mpla),hex(mpua),hex(mpat)))
      regions.append((mpla,mpua,mpat))
  if app.get_function_switch_setting("RBFS_TPSWSVPRestrictions") == "RBFS_TPSWSVPRestrictions_ON":
    tst.eval_eq(mpm, 0x3)
  else:
    tst.eval_eq(mpm, 0x1)
  tst.eval_eq(mea, 0x0)
  tst.eval_eq(mei, 0x0)

  for ram in RAM_addresses:
    found = 0
    for region_id in range(16):
      if (regions[region_id][0] == ram[0]) and (regions[region_id][1] == ram[1]) and ((regions[region_id][2] & (1<<7)) != 0):
        tst.eval_eq(regions[region_id][0], ram[0])
        tst.eval_eq(regions[region_id][1], ram[1])
        tst.eval_neq(regions[region_id][2] & (1<<7), 0)
        found +=1
    tst.eval_eq(found, 1)

  for rom in ROM_addresses:
    found = 0
    for region_id in range(16):
      if (regions[region_id][0] == rom[0]) and (regions[region_id][1] == rom[1]) and ((regions[region_id][2] & (1<<7)) != 0):
        tst.eval_eq(regions[region_id][0], rom[0])
        tst.eval_eq(regions[region_id][1], rom[1])
        tst.eval_neq(regions[region_id][2] & (1<<7), 0)
        found +=1
    tst.eval_eq(found, 1)

  if app.get_function_switch_setting("RBFS_TPSWSVPRestrictions") == "RBFS_TPSWSVPRestrictions_ON":
    found = 0
    for region_id in range(16):
      if (regions[region_id][0] == background_region[0]) and (regions[region_id][1] == background_region[1]) and ((regions[region_id][2] & (1<<7)) != 0):
        tst.eval_eq(regions[region_id][0], background_region[0])
        tst.eval_eq(regions[region_id][1], background_region[1])
        tst.eval_neq(regions[region_id][2] & (1<<7), 0)
        found +=1
    tst.eval_eq(found, 1)

  # above ROM and RAM regions + the background region are all the active MPU regions
  active_regions = filter(lambda region: (region[2] & (1<<7)) != 0, regions)
  expected_active_regions = len(ROM_addresses) + len(RAM_addresses)
  if app.get_function_switch_setting("RBFS_TPSWSVPRestrictions") == "RBFS_TPSWSVPRestrictions_ON":
    expected_active_regions += 1 # additional background region for supervisor
  tst.eval_eq(expected_active_regions, len(active_regions))

tst.end()