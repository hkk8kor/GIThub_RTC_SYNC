'''
/**
 *
 * \Reference Gen_SWCS_HSW_uC_Base_SYS-246
 *
 * \Purpose
 *  Verify that the software is compatible to the used uC.
 *  In case of incompatibility an error "UnsupportedHW" will be reported.
 *
 * \Sequence
 * Passed Test:
 * 1. run system till RBSYS_PRC_UnsupportedHW
 * 2. modify PRDNAME3 and optionally PRDSEL3 so combination is plausible (PRDNUM for U2A) e.g. D5-SW -> D5ED-HW
 * 3. run till Bfm was updated
 * 4. check that RB_UnsupportedHW has not been set
 * Failed Test:
 * 1. run system till RBSYS_PRC_UnsupportedHW
 * 2. define expected debug values: PRDNAME3, PRDSEL3, targetDevice and emulationDevice
 * 3. modify PRDNAME3 and optionally PRDSEL3 (PRDNUM for U2A)
 * 4. run till Bfm was updated
 * 5. check if RB_UnsupportedHW has been set
 *
 * \ExpectedResult
 * RB_UnsupportedHW is set with device specific defined debug1 value. Debug0 is always 0x1.
 *
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.environment as env
import swt2.application as app


app.execution_condition("ALWAYS")

#######################

tst.start()

# get target and emulation device the software was compiled for
targetDevice = app.get_function_switch_setting("RBFS_TargetDevice")[-2:]
emulationDevice = app.get_function_switch_setting("RBFS_EmulationDevice")[-4:]
# deduce device on which this software is supposed to be executed
if emulationDevice != "None":
  device = emulationDevice
else:
  device = targetDevice

if(env.is_renesas_u2a_device()):
  # PRDNUM and PRDNAME not supported as register by VLAB
  u2a_prdnum_addr   = 0x08030040
  u2a_prdname2_addr = 0x080300A4
  u2a_prdname3_addr = 0x080300A8

# maps device to their PRDNAME/SEL/NUM
deviceToProductInformation = {
  # P1x Device | PRDSEL3  | PRDNAME2  | PRDNAME3  |
  "D3EDRevB":  (0x01000000, 0x33333130, 0x20204234), # D3ED Rev B v1.0
  "D4RevA":    (0x01000000, 0x32333230, 0x20204137), # D4 Rev A v1.0
  "D5Rev0":    (0x02000000, 0x32333230, 0x20202036), # D5 Rev 0 v2.0
  "D5EDv3":    (0x01000000, 0x32333130, 0x20204235), # D5EDv3
  # U2A Device | PRDNUM   | PRDNAME2  | PRDNAME3  |
  "M3v1.00":   (0x00018408, 0x30333230, 0x20202031), # M3 in BGA292 package v1.00
  "M6v1.00":   (0x00018406, 0x30333230, 0x20202030), # M6 in BGA516 package v1.00
  "M6EDv1.00": (0x000183FF, 0x315A3230, 0x20202039), # M6ED in BGA516 package v1.00
  "M6EDv1.10": (0x0001840B, 0x315A3230, 0x20204139)  # M6ED in BGA516 package v1.10
}
def getPRDSEL3(dev):
  return deviceToProductInformation[dev][0]
def getPRDNUM(dev):
  return deviceToProductInformation[dev][0]
def getPRDNAME2(dev):
  return deviceToProductInformation[dev][1]
def getPRDNAME3(dev):
  return deviceToProductInformation[dev][2]

#############################################################################
#                             Passed Test                                   #
#############################################################################
tgt.run_until("RBSYS_PRC_UnsupportedHW")

if env.is_renesas_p1x_device():
  # save original register content
  prdsel3_org  = tgt.get_register("RH850.PFRH850.SCDS.GREG50").read() # get PRDSEL3
  prdname2_org = tgt.get_register("RH850.PFRH850.SCDS.GREG53").read() # get PRDNAME2
  prdname3_org = tgt.get_register("RH850.PFRH850.SCDS.GREG54").read() # get PRDNAME3

  if device in ["D1", "D2"]:
    # every Renesas D1/D2 SW must run on a D3ED
    tgt.get_register("RH850.PFRH850.SCDS.GREG50").write(getPRDSEL3("D3EDRevB"))  # set PRDSEL3 of D3ED Rev.B
    tgt.get_register("RH850.PFRH850.SCDS.GREG53").write(getPRDNAME2("D3EDRevB")) # set PRDNAME2 of D3ED Rev.B
    tgt.get_register("RH850.PFRH850.SCDS.GREG54").write(getPRDNAME3("D3EDRevB")) # set PRDNAME3 of D3ED Rev.B
  else: # D3, D4, D5
    # every Renesas D3/D4/D5 SW must run on a D5ED
    tgt.get_register("RH850.PFRH850.SCDS.GREG50").write(getPRDSEL3("D5EDv3"))  # set PRDSEL3 of D5EDv3
    tgt.get_register("RH850.PFRH850.SCDS.GREG53").write(getPRDNAME2("D5EDv3")) # set PRDNAME2 of D5EDv3
    tgt.get_register("RH850.PFRH850.SCDS.GREG54").write(getPRDNAME3("D5EDv3")) # set PRDNAME3 of D5EDv3

elif env.is_renesas_u2a_device():
  # save original register content
  prdnum_org   = tgt.read_memory_uint32(u2a_prdnum_addr)   # get PRDNUM
  prdname2_org = tgt.read_memory_uint32(u2a_prdname2_addr) # get PRDNAME2
  prdname3_org = tgt.read_memory_uint32(u2a_prdname3_addr) # get PRDNAME3

  # every Renesas U2A SW must run on a M6ED
  tgt.write_memory_uint32(u2a_prdnum_addr, getPRDNUM("M6EDv1.10")) # set PRDNUM of M6ED v1.10
  tgt.write_memory_uint32(u2a_prdname2_addr, getPRDNAME2("M6EDv1.10")) # set PRDNAME2 of M6ED v1.10
  tgt.write_memory_uint32(u2a_prdname3_addr, getPRDNAME3("M6EDv1.10")) # set PRDNAME3 of M6ED v1.10

# run until failure should have been reported
tgt.run_until_end_of("RBRCFG_ReportUnsupportedConfig")

# restore original register content to not interfere with dynamic features also checking product identifier
if env.is_renesas_p1x_device():
  tgt.get_register("RH850.PFRH850.SCDS.GREG50").write(prdsel3_org)
  tgt.get_register("RH850.PFRH850.SCDS.GREG53").write(prdname2_org)
  tgt.get_register("RH850.PFRH850.SCDS.GREG54").write(prdname3_org)
elif env.is_renesas_u2a_device():
  tgt.write_memory_uint32(u2a_prdnum_addr,   prdnum_org)
  tgt.write_memory_uint32(u2a_prdname2_addr, prdname2_org)
  tgt.write_memory_uint32(u2a_prdname3_addr, prdname3_org)

# failure RB_UnsupportedHW must not be set since any SW can be executed on the corresponding Emulation Device
app.run_until_bfm_was_updated()
tst.eval( not(app.get_event("RB_UnsupportedHW").is_failed()))

app.do_test_environment_reset()  # Reset to prepare environment for the next test

#############################################################################
#                             Failed Test                                   #
#############################################################################
tgt.run_until("RBSYS_PRC_UnsupportedHW")
prdname3 = 0
prdnum   = 0

# maps a device for which software is compiled to a device which is unsupported by this software
deviceCompiledForToUnsupportedDevice = {
  "D1":   "D4RevA",
  "D2":   "D4RevA",
  "D3":   "D4RevA",
  "D3ED": "D4RevA",
  "D4":   "D5Rev0",
  "D5":   "D4RevA",
  "D5ED": "D5Rev0",
  "M2":   "M6v1.00",
  "M3":   "M6v1.00",
  "D7":   "M3v1.00",
  "M6":   "M3v1.00",
  "D7ED": "M3v1.00" if targetDevice in ["M3"] else "M6EDv1.00",
  "M6ED": "M3v1.00" if targetDevice in ["M3"] else "M6EDv1.00"
}
# maps target device to RBFS_TargetDevice value
targetDeviceToEnumValue = {"D1": 1, "D2": 2, "D3": 3, "D4": 4, "D5": 5, "D7": 7, "M3": 8, "M6": 9, "M2": 13}
# maps emulation device to RBFS_EmulationDevice value
emuDeviceToEnumValue = {"None": 1, "D3ED": 2, "D5ED": 3, "D7ED": 4, "M6ED": 5}

if device in deviceCompiledForToUnsupportedDevice:
  if(env.is_renesas_p1x_device()):
    # get PRDNAME/SEL of an unsupported device for the current software
    unsupportedDevice = deviceCompiledForToUnsupportedDevice[device]
    prdsel3  = getPRDSEL3(unsupportedDevice)
    prdname3 = getPRDNAME3(unsupportedDevice)

    tgt.get_register("RH850.PFRH850.SCDS.GREG50").write(prdsel3)  # set PRDSEL3
    tgt.get_register("RH850.PFRH850.SCDS.GREG54").write(prdname3) # set PRDNAME3

    # Debug Data:
    # Bit[31..20] corresponds to Bits [11..0] of PRDNAME3 Register;
    #             via PRDNAME3 it's possible to identify the used device (see RBSYS_CpuVersions.h)
    # Bit[19..8] product version;
    # Bit[7..4] RBFS_TargetDevice (in software configured function switch);
    # Bit[3..0] RBFS_EmulationDevice (in software configured function switch);
    debug1  = ((prdname3 & 0xFFF) << 20)
    debug1 |= ((prdsel3 & 0x0FFF0000) >> 8)

  elif(env.is_renesas_u2a_device()):
    # get PRDNUM of an unsupported device for the current software
    unsupportedDevice = deviceCompiledForToUnsupportedDevice[device]
    prdnum = getPRDNUM(unsupportedDevice)

    tgt.write_memory_uint32(u2a_prdnum_addr, prdnum) # set PRDNUM

    # Debug Data:
    # Bit[31..12] corresponds to Bits [19..0] of PRDNUM Register;
    #             via PRDNUM it's possible to identify the used device (see RBSYS_CpuVersions.h)
    # Bit[11..8] unused
    # Bit[7..4] RBFS_TargetDevice (in software configured function switch);
    # Bit[3..0] RBFS_EmulationDevice (in software configured function switch);
    debug1  = ((prdnum & 0x000FFFFF) << 12)

  debug1 |= (targetDeviceToEnumValue[targetDevice] << 4)
  debug1 |= (emuDeviceToEnumValue[emulationDevice] << 0)

  # run until failure should have been reported
  tgt.run_until_end_of("RBRCFG_ReportUnsupportedConfig")

  # restore original register content to not interfere with dynamic features also checking product identifier
  if env.is_renesas_p1x_device():
    tgt.get_register("RH850.PFRH850.SCDS.GREG50").write(prdsel3_org)
    tgt.get_register("RH850.PFRH850.SCDS.GREG53").write(prdname2_org)
    tgt.get_register("RH850.PFRH850.SCDS.GREG54").write(prdname3_org)
  elif env.is_renesas_u2a_device():
    tgt.write_memory_uint32(u2a_prdnum_addr,   prdnum_org)
    tgt.write_memory_uint32(u2a_prdname2_addr, prdname2_org)
    tgt.write_memory_uint32(u2a_prdname3_addr, prdname3_org)

  app.run_until_bfm_was_updated()
  # app.print_system_info()
  tst.eval(app.get_event("RB_UnsupportedHW").is_failed())
  tst.eval_eq(((app.get_bfm_record("RB_UnsupportedHW").get_debug0())), 0x1)
  tst.eval_eq(((app.get_bfm_record("RB_UnsupportedHW").get_debug1())), debug1)
else:
  tst.eval(False) # tests does not support this device at the moment


tst.end()
