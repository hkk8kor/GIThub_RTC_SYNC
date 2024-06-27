'''
/**
 * \Reference
 * Gen_SWFS_0979_HSW_OverallRequirements_6738
 *
 * \Purpose
 * Check PE guard configuration
 *
 * \Sequence
 * Run until start of FSW
 * If valid OEMBLDR exists:
 *   reset to OEMBLDR
 *   run until start of FSW
 * If valid RBBLDR exists:
 *   reset to RBBLDR
 *   reset back to FSW
 *   run until start of FSW
 * Run until guard configuration is finished
 *
 * \ExpectedResult
 * P1x: Guards are not locked at start of FSW (also after OEMBLDR/RBBLDR were running) and at the end of BMGR but are locked after initialization
 * PE guards only allow write access to local RAM for safe SPIDs and all local RAM addresses are guarded
 * Protected Regions do not overlap
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.environment as env
import swt2.application as app


app.execution_condition("ALWAYS")

import DeviceInfo

#############################################################################
#                             Helper functions                              #
#############################################################################

# helper function for reading register value so that test can handle both register names and register addresses (if names are not available in VLAB)
def ReadRegisterOrAddress(reg):
  if type(reg) is long:
    return tgt.read_memory_uint32(reg)
  else:
    return tgt.get_register(reg).read()

# check that lock bits are set to expected value
def CheckGuardLockBit(expectedValue):
  for lockReg in LockRegs:
    lock = ReadRegisterOrAddress(lockReg)
    tst.eval_eq((lock >> 4) & 0x1, expectedValue)


#############################################################################
#                             Setup                                         #
#############################################################################
# Guard configuration depends on target device and does not factor in emulation device function switch
targetDevice = app.get_function_switch_setting("RBFS_TargetDevice")[-2:]
# U2x emulation devices have to permit access for debug bus masters (AUD, MAU)
emulationDevice = app.get_function_switch_setting("RBFS_EmulationDevice")[-4:]

# SPIDs and SPID masks
safeSPID = 2
AUDSPID  = 30
MAUSPID  = 31
if env.is_renesas_u2a_device():
  DebugSPID_mask = (0x1 << AUDSPID) | (0x1 << MAUSPID)
elif env.is_renesas_u2c_device():
  safeSPID = 0
  DebugSPID_mask = (0x1 << MAUSPID)

# Guard Registers and expected bits
if env.is_renesas_p1x_device():
  PEGuardRegs = [
    (0xFFFEE680,0xFFFEE684,0xFFFEE688), #PEGG0MK, PEGG0BA, PEGG0SP
    (0xFFFEE690,0xFFFEE694,0xFFFEE698), #PEGG1MK, PEGG1BA, PEGG1SP
    (0xFFFEE6A0,0xFFFEE6A4,0xFFFEE6A8), #PEGG2MK, PEGG2BA, PEGG2SP
    (0xFFFEE6B0,0xFFFEE6B4,0xFFFEE6B8), #PEGG3MK, PEGG3BA, PEGG3SP
    (0xFFFEE6C0,0xFFFEE6C4,0xFFFEE6C8), #PEGG4MK, PEGG4BA, PEGG4SP
    (0xFFFEE6D0,0xFFFEE6D4,0xFFFEE6D8), #PEGG5MK, PEGG5BA, PEGG5SP
    (0xFFFEE6E0,0xFFFEE6E4,0xFFFEE6E8), #PEGG6MK, PEGG6BA, PEGG6SP
    (0xFFFEE6F0,0xFFFEE6F4,0xFFFEE6F8), #PEGG7MK, PEGG7BA, PEGG7SP
  ]
  PEGEnabledOffset      = 0
  PEGEnabledValue       = 1
  PEGWriteAccessOffset  = 2
  PEGWriteAccessValue   = 1
  PEGValidBitMask       = 0xFFFFF000
  PEGuardRegions = DeviceInfo.getDeviceInfoBasedOnSWConfig().LocalRAM

  LockRegs = [regs[1] for regs in PEGuardRegs]

elif env.is_renesas_u2a_device() or env.is_renesas_u2c_device():
  PEGuardRegs = [ # not all PE Guard registers have names in VLAB
    ("RH850.PFRH850.GUARD_PE0CL0.PROT0", "RH850.PFRH850.GUARD_PE0CL0.SPID0", "RH850.PFRH850.GUARD_PE0CL0.BAD0", "RH850.PFRH850.GUARD_PE0CL0.ADV0"),
    ("RH850.PFRH850.GUARD_PE0CL0.PROT1", "RH850.PFRH850.GUARD_PE0CL0.SPID1", "RH850.PFRH850.GUARD_PE0CL0.BAD1", "RH850.PFRH850.GUARD_PE0CL0.ADV1"),
    ("RH850.PFRH850.GUARD_PE0CL0.PROT2", "RH850.PFRH850.GUARD_PE0CL0.SPID2", "RH850.PFRH850.GUARD_PE0CL0.BAD2", "RH850.PFRH850.GUARD_PE0CL0.ADV2"),
    ("RH850.PFRH850.GUARD_PE0CL0.PROT3", "RH850.PFRH850.GUARD_PE0CL0.SPID3", "RH850.PFRH850.GUARD_PE0CL0.BAD3", "RH850.PFRH850.GUARD_PE0CL0.ADV3"),
    (0xFFC6C080, 0xFFC6C084, 0xFFC6C088, 0xFFC6C08C), # GUARD_PE0CL0_PEGPROT4, GUARD_PE0CL0_PEGSPID4, GUARD_PE0CL0_PEGBAD4, GUARD_PE0CL0_PEGADV4
    (0xFFC6C090, 0xFFC6C094, 0xFFC6C098, 0xFFC6C09C), # GUARD_PE0CL0_PEGPROT5, GUARD_PE0CL0_PEGSPID5, GUARD_PE0CL0_PEGBAD5, GUARD_PE0CL0_PEGADV5
    (0xFFC6C0A0, 0xFFC6C0A4, 0xFFC6C0A8, 0xFFC6C0AC), # GUARD_PE0CL0_PEGPROT6, GUARD_PE0CL0_PEGSPID6, GUARD_PE0CL0_PEGBAD6, GUARD_PE0CL0_PEGADV6
    (0xFFC6C0B0, 0xFFC6C0B4, 0xFFC6C0B8, 0xFFC6C0BC), # GUARD_PE0CL0_PEGPROT7, GUARD_PE0CL0_PEGSPID7, GUARD_PE0CL0_PEGBAD7, GUARD_PE0CL0_PEGADV7

    ("RH850.PFRH850.GUARD_PE1CL0.PROT0", "RH850.PFRH850.GUARD_PE1CL0.SPID0", "RH850.PFRH850.GUARD_PE1CL0.BAD0", "RH850.PFRH850.GUARD_PE1CL0.ADV0"),
    ("RH850.PFRH850.GUARD_PE1CL0.PROT1", "RH850.PFRH850.GUARD_PE1CL0.SPID1", "RH850.PFRH850.GUARD_PE1CL0.BAD1", "RH850.PFRH850.GUARD_PE1CL0.ADV1"),
    ("RH850.PFRH850.GUARD_PE1CL0.PROT2", "RH850.PFRH850.GUARD_PE1CL0.SPID2", "RH850.PFRH850.GUARD_PE1CL0.BAD2", "RH850.PFRH850.GUARD_PE1CL0.ADV2"),
    ("RH850.PFRH850.GUARD_PE1CL0.PROT3", "RH850.PFRH850.GUARD_PE1CL0.SPID3", "RH850.PFRH850.GUARD_PE1CL0.BAD3", "RH850.PFRH850.GUARD_PE1CL0.ADV3"),
    (0xFFC6C180, 0xFFC6C184, 0xFFC6C188, 0xFFC6C18C), # GUARD_PE1CL0_PEGPROT4, GUARD_PE1CL0_PEGSPID4, GUARD_PE1CL0_PEGBAD4, GUARD_PE1CL0_PEGADV4
    (0xFFC6C190, 0xFFC6C194, 0xFFC6C198, 0xFFC6C19C), # GUARD_PE1CL0_PEGPROT5, GUARD_PE1CL0_PEGSPID5, GUARD_PE1CL0_PEGBAD5, GUARD_PE1CL0_PEGADV5
    (0xFFC6C1A0, 0xFFC6C1A4, 0xFFC6C1A8, 0xFFC6C1AC), # GUARD_PE1CL0_PEGPROT6, GUARD_PE1CL0_PEGSPID6, GUARD_PE1CL0_PEGBAD6, GUARD_PE1CL0_PEGADV6
    (0xFFC6C1B0, 0xFFC6C1B4, 0xFFC6C1B8, 0xFFC6C1BC), # GUARD_PE1CL0_PEGPROT7, GUARD_PE1CL0_PEGSPID7, GUARD_PE1CL0_PEGBAD7, GUARD_PE1CL0_PEGADV7
  ]
  if targetDevice in ["D7", "M6"]:
    PEGuardRegs += [
      ("RH850.PFRH850.GUARD_PE2CL1.PROT0", "RH850.PFRH850.GUARD_PE2CL1.SPID0", "RH850.PFRH850.GUARD_PE2CL1.BAD0", "RH850.PFRH850.GUARD_PE2CL1.ADV0"),
      ("RH850.PFRH850.GUARD_PE2CL1.PROT1", "RH850.PFRH850.GUARD_PE2CL1.SPID1", "RH850.PFRH850.GUARD_PE2CL1.BAD1", "RH850.PFRH850.GUARD_PE2CL1.ADV1"),
      ("RH850.PFRH850.GUARD_PE2CL1.PROT2", "RH850.PFRH850.GUARD_PE2CL1.SPID2", "RH850.PFRH850.GUARD_PE2CL1.BAD2", "RH850.PFRH850.GUARD_PE2CL1.ADV2"),
      ("RH850.PFRH850.GUARD_PE2CL1.PROT3", "RH850.PFRH850.GUARD_PE2CL1.SPID3", "RH850.PFRH850.GUARD_PE2CL1.BAD3", "RH850.PFRH850.GUARD_PE2CL1.ADV3"),
      (0xFFC6C280, 0xFFC6C284, 0xFFC6C288, 0xFFC6C28C), # GUARD_PE2CL1_PEGPROT4, GUARD_PE2CL1_PEGSPID4, GUARD_PE2CL1_PEGBAD4, GUARD_PE2CL1_PEGADV4
      (0xFFC6C290, 0xFFC6C294, 0xFFC6C298, 0xFFC6C29C), # GUARD_PE2CL1_PEGPROT5, GUARD_PE2CL1_PEGSPID5, GUARD_PE2CL1_PEGBAD5, GUARD_PE2CL1_PEGADV5
      (0xFFC6C2A0, 0xFFC6C2A4, 0xFFC6C2A8, 0xFFC6C2AC), # GUARD_PE2CL1_PEGPROT6, GUARD_PE2CL1_PEGSPID6, GUARD_PE2CL1_PEGBAD6, GUARD_PE2CL1_PEGADV6
      (0xFFC6C2B0, 0xFFC6C2B4, 0xFFC6C2B8, 0xFFC6C2BC), # GUARD_PE2CL1_PEGPROT7, GUARD_PE2CL1_PEGSPID7, GUARD_PE2CL1_PEGBAD7, GUARD_PE2CL1_PEGADV7

      ("RH850.PFRH850.GUARD_PE3CL1.PROT0", "RH850.PFRH850.GUARD_PE3CL1.SPID0", "RH850.PFRH850.GUARD_PE3CL1.BAD0", "RH850.PFRH850.GUARD_PE3CL1.ADV0"),
      ("RH850.PFRH850.GUARD_PE3CL1.PROT1", "RH850.PFRH850.GUARD_PE3CL1.SPID1", "RH850.PFRH850.GUARD_PE3CL1.BAD1", "RH850.PFRH850.GUARD_PE3CL1.ADV1"),
      ("RH850.PFRH850.GUARD_PE3CL1.PROT2", "RH850.PFRH850.GUARD_PE3CL1.SPID2", "RH850.PFRH850.GUARD_PE3CL1.BAD2", "RH850.PFRH850.GUARD_PE3CL1.ADV2"),
      ("RH850.PFRH850.GUARD_PE3CL1.PROT3", "RH850.PFRH850.GUARD_PE3CL1.SPID3", "RH850.PFRH850.GUARD_PE3CL1.BAD3", "RH850.PFRH850.GUARD_PE3CL1.ADV3"),
      (0xFFC6C380, 0xFFC6C384, 0xFFC6C388, 0xFFC6C38C), # GUARD_PE3CL1_PEGPROT4, GUARD_PE3CL1_PEGSPID4, GUARD_PE3CL1_PEGBAD4, GUARD_PE3CL1_PEGADV4
      (0xFFC6C390, 0xFFC6C394, 0xFFC6C398, 0xFFC6C39C), # GUARD_PE3CL1_PEGPROT5, GUARD_PE3CL1_PEGSPID5, GUARD_PE3CL1_PEGBAD5, GUARD_PE3CL1_PEGADV5
      (0xFFC6C3A0, 0xFFC6C3A4, 0xFFC6C3A8, 0xFFC6C3AC), # GUARD_PE3CL1_PEGPROT6, GUARD_PE3CL1_PEGSPID6, GUARD_PE3CL1_PEGBAD6, GUARD_PE3CL1_PEGADV6
      (0xFFC6C3B0, 0xFFC6C3B4, 0xFFC6C3B8, 0xFFC6C3BC), # GUARD_PE3CL1_PEGPROT7, GUARD_PE3CL1_PEGSPID7, GUARD_PE3CL1_PEGBAD7, GUARD_PE3CL1_PEGADV7
    ]
  PEGEnabledOffset      = 8
  PEGEnabledValue       = 1
  PEGWriteAccessOffset  = 1
  PEGWriteAccessValue   = 0
  PEGValidBitMask       = 0x03FFF000
  PEGuardRegions = [
      DeviceInfo.getDeviceInfoBasedOnSWConfig().LocalRAM[0],
      DeviceInfo.getDeviceInfoBasedOnSWConfig().LocalRAM[1],
      (0xFFFC4000, 0x4000), # CPU0 Peripheral
      (0xFFFC8000, 0x4000), # CPU1 Peripheral

      # Hint for M6: As long as Core2/3 are disabled, LRAM2/3 and the corresponding INTC1-Controller are not accessible and guards are not configured.
      #DeviceInfo.getDeviceInfoBasedOnSWConfig().LocalRAM[2],
      #DeviceInfo.getDeviceInfoBasedOnSWConfig().LocalRAM[3],
      #(0xFFFCC000, 0x4000), # CPU2 Peripheral
      #(0xFFFD0000, 0x4000), # CPU3 Peripheral
    ]

  LockRegs = []

#############################################################################
#                             Test start                                    #
#############################################################################
tst.start()

# Run until start of Application and check that guards are not locked
tgt.run_until("RBSYS_StartupPreOSPhase0")
CheckGuardLockBit(0)

# Skip bootblock tests if stubbed BMGR is detected
if not app.get_bmgr_elf_image() or not app.get_bmgr_elf_image().does_symbol_exist("TRBA_BMGR_IS_STUBBED"):
  if app.get_function_switch_setting("RBFS_OEMBootloader") == "RBFS_OEMBootloader_Yes":
    # Reset to OEMBLDR
    tgt.run_until("Os_Entry_TaskBaseCtrlCycx1High")
    tgt.trigger_execution_of_function("RBSYS_uCReset_ApplResetWithBootBlock4OEM", 0)
    # Run until end of BMGR befor jump to OEMBLDR and check that guards are not locked
    tgt.run_until("rba_Bmgr_JumpToOemBldr", image=app.get_bmgr_elf_image())
    CheckGuardLockBit(0)
    # Run until start of Application and check that guards are not locked
    tgt.run_until("RBSYS_StartupPreOSPhase0")
    CheckGuardLockBit(0)

  if app.get_function_switch_setting("RBFS_RBBootloader") == "RBFS_RBBootloader_Yes":
    # Reset to RBBLDR
    tgt.run_until("Os_Entry_TaskBaseCtrlCycx1High")
    tgt.trigger_execution_of_function("RBSYS_uCReset_ApplResetWithBootBlock4RB", 0)
    # Run until end of BMGR befor jump to RBBLDR and check that guards are not locked
    tgt.run_until("rba_Bmgr_JumpToRbBldr", image=app.get_bmgr_elf_image())
    CheckGuardLockBit(0)
    # Reset to Application
    tgt.run_until("rba_BldrOs_Iterate", image=app.get_rbbldr_elf_image())
    tgt.trigger_execution_of_function("rba_BldrCmp_Cfg_PerformReset", image=app.get_rbbldr_elf_image(), core=0)
    # Run until start of Application and check that guards are not locked
    tgt.run_until("RBSYS_StartupPreOSPhase0")
    CheckGuardLockBit(0)

# Run until init is done and check that guards are locked
app.run_until_end_of_init()

# Check PE guard (local RAM) only allows write access for safe SPIDs
unitingProtections = [] # collect guard base addresses and guard masks
for PEGuardRegGroup in PEGuardRegs:
  # get guard register content
  if env.is_renesas_p1x_device():
    maskReg, protReg, spidReg = PEGuardRegGroup
    base = ReadRegisterOrAddress(protReg) & PEGValidBitMask
  elif env.is_renesas_u2a_device() or env.is_renesas_u2c_device():
    protReg, spidReg, baseReg, maskReg = PEGuardRegGroup
    base = ReadRegisterOrAddress(baseReg)
  mask = ReadRegisterOrAddress(maskReg)
  prot = ReadRegisterOrAddress(protReg)
  spid = ReadRegisterOrAddress(spidReg)

  # if guard is enabled and allows write access, add to unitingProtections
  if ((prot >> PEGEnabledOffset) & 0x1) == PEGEnabledValue and ((prot >> PEGWriteAccessOffset) & 0x1) == PEGWriteAccessValue:
    if env.is_renesas_p1x_device():
      mask = ~mask # PE guard mask is inverted on P1x
    unitingProtections.append((base & PEGValidBitMask, mask & PEGValidBitMask, spid))


# check that every address is protected correctly
for (start, length) in PEGuardRegions:
  regionProtected = True

  # Due to guard configuration given as bit mask, address ranges are difficult to calculate.
  # Instead just do the same check for every address as the guards do.
  for addr in range(start, start + length):
    # calculate sum of individual permission (overlap is union)
    unitedSPID = 0x0
    appliedGuards = 0
    for (base, mask, spid) in unitingProtections:
      if (addr & mask) == (base & mask):
        appliedGuards += 1
        unitedSPID |= spid

     # address must be protected but allow no overlaps
    if appliedGuards != 1:
      tst.eval_eq(appliedGuards, 1)
      regionProtected = False
      break

    # if protection is not configured as expected,
    # stop checking this region and report failed
    expectedSPID = 0x1 << safeSPID
    if (env.is_renesas_u2a_device() or env.is_renesas_u2c_device()) and emulationDevice in ["D7ED", "M6ED", "K3ED"]:
      expectedSPID |= DebugSPID_mask
    if unitedSPID != expectedSPID:
      tst.eval_eq(unitedSPID, expectedSPID)
      regionProtected = False
      break

  tst.eval(regionProtected)

tst.end()