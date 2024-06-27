'''
/**
 * \Reference
 * Gen_SWFS_0979_HSW_OverallRequirements_6738, Gen_SWCS_HSW_uC_Base_SYS-332
 *
 * \Purpose
 * Check global RAM guard configuration
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
 * Guards are not locked at start of FSW (also after OEMBLDR/RBBLDR were running) and at the end of BMGR but are locked after initialization
 * Global RAM guards only allow write access to global RAM for safe SPIDs except for special areas also accessible by HSM, Ethernet or DMA
 * All global RAM addresses are guarded
 * For P1x: Protected Regions do not overlap
 * If RestrictedSPID feature is enabled:
 *  P1x: depending on RBFS_RestrictedExclusiveGRAMsize either MGDGRPROT2 or MGDGRPROT3 will not be locked
 *  RestrictedSPID may be allowed write access to protected RAM region in combination or instead of SafeSPID
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.environment as env
import swt2.application as app
import swt2.software as sw


app.execution_condition(include_switches=["RBFS_GlobalRamSupport_ON"])

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

def CheckGuardLockBit(expectedValue):
  for lockReg in LockRegs:
    lock = ReadRegisterOrAddress(lockReg)
    tst.eval_eq((lock >> 31) & 0x1, expectedValue)

#############################################################################
#                             Setup                                         #
#############################################################################
# Guard configuration depends on target device and does not factor in emulation device function switch
targetDevice = app.get_function_switch_setting("RBFS_TargetDevice")[-2:]
# U2x emulation devices have to permit access for debug bus masters (AUD, MAU)
emulationDevice = app.get_function_switch_setting("RBFS_EmulationDevice")[-4:]
# Guard configuration depends on whether RestrictedSPID feature is enabled
RestrictedSPIDEnabled = app.get_function_switch_setting("RBFS_SysExclusiveSPID") == "RBFS_SysExclusiveSPID_Used"

# SPIDs and SPID masks
safeSPID       = 2
restrictedSPID = 4
DMAUnsafeSPID  = 5
AUDSPID        = 30
MAUSPID        = 31
if env.is_renesas_p1x_device():
  SecureSPID_mask = (0x1 << 0) | (0x1 << 1)
elif env.is_renesas_u2a_device():
  SecureSPID_mask = (0x1 << 25) | (0x1 << 26)
  DebugSPID_mask  = (0x1 << AUDSPID) | (0x1 << MAUSPID)
elif env.is_renesas_u2c_device():
  safeSPID        = 0
  SecureSPID_mask = (0x1 << 26)
  DebugSPID_mask  = (0x1 << MAUSPID)

# Guard Registers and expected bits
if env.is_renesas_p1x_device():
  GlobalRamGuardRegs = [
    (0xFFC49000, 0xFFC49004, 0xFFC49008, 0xFFC4900C), # MGDGRPROT0, MGDGRSPID0, MGDGRBAD0, MGDGRADV0
    (0xFFC49010, 0xFFC49014, 0xFFC49018, 0xFFC4901C), # MGDGRPROT1, MGDGRSPID1, MGDGRBAD1, MGDGRADV1
    (0xFFC49020, 0xFFC49024, 0xFFC49028, 0xFFC4902C), # MGDGRPROT2, MGDGRSPID2, MGDGRBAD2, MGDGRADV2
    (0xFFC49030, 0xFFC49034, 0xFFC49038, 0xFFC4903C), # MGDGRPROT3, MGDGRSPID3, MGDGRBAD3, MGDGRADV3
    (0xFFC49040, 0xFFC49044, 0xFFC49048, 0xFFC4904C), # MGDGRPROT4, MGDGRSPID4, MGDGRBAD4, MGDGRADV4
    (0xFFC49050, 0xFFC49054, 0xFFC49058, 0xFFC4905C), # MGDGRPROT5, MGDGRSPID5, MGDGRBAD5, MGDGRADV5
    (0xFFC49060, 0xFFC49064, 0xFFC49068, 0xFFC4906C), # MGDGRPROT6, MGDGRSPID6, MGDGRBAD6, MGDGRADV6
    (0xFFC49070, 0xFFC49074, 0xFFC49078, 0xFFC4907C), # MGDGRPROT7, MGDGRSPID7, MGDGRBAD7, MGDGRADV7
  ]
  GlobalRamGuardEnableOffset  = 30
  GlobalRamGuardEnableValue   = 1
  GlobalRamGuardValidBitMask  = 0x001FFE00
  GlobalRamGuardRegions = DeviceInfo.getDeviceInfoBasedOnSWConfig().GlobalRAM

  LockRegs = [regs[0] for regs in GlobalRamGuardRegs]
  # exceptions for shared areas with HSM and Ethernet
  GlobalRamGuardExceptions = []
  if app.get_function_switch_setting("RBFS_SysEthSharedGRAMsize") != "RBFS_SysEthSharedGRAMsize_0K":
    GlobalRamGuardExceptions += [(
        sw.get_variable("__ghs_rblcf_ethernet_shared_ram_start").get_address(),
        sw.get_variable("__ghs_rblcf_ethernet_shared_ram_end").get_address(),
        (0x1 << UnsafeSPID)
      )]
  if app.get_function_switch_setting("RBFS_SysHsmSharedGRAMsize") != "RBFS_SysHsmSharedGRAMsize_0K":
    GlobalRamGuardExceptions += [(
        sw.get_variable("__ghs_rblcf_hsm_shared_ram_start").get_address(),
        sw.get_variable("__ghs_rblcf_hsm_shared_ram_end").get_address(),
        SecureSPID_mask
      )]

elif env.is_renesas_u2a_device():
  GlobalRamGuardRegs = []
  for cluster in range(4):
    if (cluster == 1 and targetDevice in ["M3"]) or ((cluster == 1 or cluster == 2) and targetDevice in ["M2"]):
      continue
    for i in range(8):
      GlobalRamGuardRegs.append(( "RH850.PFRH850.GUARD_CRAMCRG%d0.PROT%d" % (cluster,i),
                                  "RH850.PFRH850.GUARD_CRAMCRG%d0.SPID%d" % (cluster,i),
                                  "RH850.PFRH850.GUARD_CRAMCRG%d0.BAD%d"  % (cluster,i),
                                  "RH850.PFRH850.GUARD_CRAMCRG%d0.ADV%d"  % (cluster,i)))
    for i in range(4):
      GlobalRamGuardRegs.append(( "RH850.PFRH850.GUARD_CRAMCSG%d.PROT%d" % (cluster,i),
                                  "RH850.PFRH850.GUARD_CRAMCSG%d.SPID%d" % (cluster,i),
                                  "RH850.PFRH850.GUARD_CRAMCSG%d.BAD%d"  % (cluster,i),
                                  "RH850.PFRH850.GUARD_CRAMCSG%d.ADV%d"  % (cluster,i)))
  GlobalRamGuardEnableOffset        = 8
  GlobalRamGuardEnableValue         = 1
  GlobalRamGuardWriteAccessOffset   = 1
  GlobalRamGuardWriteAccessValue    = 0
  GlobalRamGuardRegions = [region for region in DeviceInfo.getDeviceInfoBasedOnSWConfig().GlobalRAM if region != None] # M3 GlobalRAM region 1 does not exist

  LockRegs = [regs[0] for regs in GlobalRamGuardRegs if "CSG" in regs[0]]

  # exceptions for shared areas with HSM, Ethernet and DMA
  GlobalRamGuardExceptions = [(
      sw.get_variable("__ghs_rblcf_dma_shared_ram_start").get_address(),
      sw.get_variable("__ghs_rblcf_dma_shared_ram_end").get_address(),
      (0x1 << DMAUnsafeSPID)
    )]
  if app.get_function_switch_setting("RBFS_SysEthSharedGRAMsize") != "RBFS_SysEthSharedGRAMsize_0K":
    GlobalRamGuardExceptions += [(
        sw.get_variable("__ghs_rblcf_ethernet_shared_ram_start").get_address(),
        sw.get_variable("__ghs_rblcf_ethernet_shared_ram_end").get_address(),
        (0x1 << UnsafeSPID)
      )]
  if app.get_function_switch_setting("RBFS_SysHsmSharedGRAMsize") != "RBFS_SysHsmSharedGRAMsize_0K":
    GlobalRamGuardExceptions += [(
        sw.get_variable("__ghs_rblcf_hsm_shared_ram_start").get_address(),
        sw.get_variable("__ghs_rblcf_hsm_shared_ram_end").get_address(),
        SecureSPID_mask
      )]
elif env.is_renesas_u2c_device():
  GlobalRamGuardRegs = []
  for ram_in_cluster in range(3):
    for i in range(8):
      GlobalRamGuardRegs.append(( "RH850.PFRH850.GUARD_CRAMCRG0%d.PROT%d" % (ram_in_cluster,i),
                                  "RH850.PFRH850.GUARD_CRAMCRG0%d.SPID%d" % (ram_in_cluster,i),
                                  "RH850.PFRH850.GUARD_CRAMCRG0%d.BAD%d"  % (ram_in_cluster,i),
                                  "RH850.PFRH850.GUARD_CRAMCRG0%d.ADV%d"  % (ram_in_cluster,i)))
    # todo: CSG not implemented by VLAB yet
    for i in range(4):
      GlobalRamGuardRegs.append(( "RH850.PFRH850.GUARD_CRAMCSG0%d.PROT%d" % (ram_in_cluster,i),
                                  "RH850.PFRH850.GUARD_CRAMCSG0%d.SPID%d" % (ram_in_cluster,i),
                                  "RH850.PFRH850.GUARD_CRAMCSG0%d.BAD%d"  % (ram_in_cluster,i),
                                  "RH850.PFRH850.GUARD_CRAMCSG0%d.ADV%d"  % (ram_in_cluster,i)))
  GlobalRamGuardEnableOffset        = 8
  GlobalRamGuardEnableValue         = 1
  GlobalRamGuardWriteAccessOffset   = 1
  GlobalRamGuardWriteAccessValue    = 0
  GlobalRamGuardRegions = [region for region in DeviceInfo.getDeviceInfoBasedOnSWConfig().GlobalRAM if region != None] # M3 GlobalRAM region 1 does not exist

  LockRegs = [regs[0] for regs in GlobalRamGuardRegs if "CSG" in regs[0]]

  # exceptions for shared areas with HSM, Ethernet and DMA
  GlobalRamGuardExceptions = [(
      sw.get_variable("__ghs_rblcf_dma_shared_ram_start").get_address(),
      sw.get_variable("__ghs_rblcf_dma_shared_ram_end").get_address(),
      (0x1 << DMAUnsafeSPID)
    )]
  if app.get_function_switch_setting("RBFS_SysEthSharedGRAMsize") != "RBFS_SysEthSharedGRAMsize_0K":
    GlobalRamGuardExceptions += [(
        sw.get_variable("__ghs_rblcf_ethernet_shared_ram_start").get_address(),
        sw.get_variable("__ghs_rblcf_ethernet_shared_ram_end").get_address(),
        (0x1 << UnsafeSPID)
      )]
  if app.get_function_switch_setting("RBFS_SysHsmSharedGRAMsize") != "RBFS_SysHsmSharedGRAMsize_0K":
    GlobalRamGuardExceptions += [(
        sw.get_variable("__ghs_rblcf_hsm_shared_ram_start").get_address(),
        sw.get_variable("__ghs_rblcf_hsm_shared_ram_end").get_address(),
        SecureSPID_mask
      )]


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

# Run until init is done and check that GRAM Guards are not locked for P1x (U2A does still have locked GRAM Guards)
app.run_until_end_of_init()

if env.is_renesas_p1x_device():
  CheckGuardLockBit(0)
elif env.is_renesas_u2a_device() or env.is_renesas_u2c_device():
  CheckGuardLockBit(1)


# Global RAM guards only allow write access to safe SPIDs (and DMA on U2x for a small RAM area)
unitingProtections = []      # for collection regions that, when overlapping, permit access individually
intersectingProtections = [] # for collecting regions that, when overlapping, restrict access individually
# Collect base address, valid bit settings and spid for all global RAM guards
for (protReg, spidReg, baseReg, maskReg) in GlobalRamGuardRegs:
  # get guard register content
  prot = ReadRegisterOrAddress(protReg)
  spid = ReadRegisterOrAddress(spidReg)
  base = ReadRegisterOrAddress(baseReg)
  mask = ReadRegisterOrAddress(maskReg)

  # if guard is enabled and allows write access, add to intersectingProtections/unitingProtections
  if ((prot >> GlobalRamGuardEnableOffset) & 0x1) == GlobalRamGuardEnableValue:
    if env.is_renesas_p1x_device():
      intersectingProtections.append((base & GlobalRamGuardValidBitMask, mask & GlobalRamGuardValidBitMask, spid))
    if (env.is_renesas_u2a_device() or env.is_renesas_u2c_device()) and ((prot >> GlobalRamGuardWriteAccessOffset) & 0x1) == GlobalRamGuardWriteAccessValue:
      # Most significant bits are cut from BAD and ADV register, so register content does not allow to distinguish between CRAMs
      # To allow that, most significant bits are added again depending on the register
      deviceInfo = DeviceInfo.getDeviceInfoBasedOnSWConfig()
      if "CRAMCRG00" in protReg or "CRAMCSG0" in protReg:
        completeBase = (base & 0x0007FF00) | (deviceInfo.GlobalRAM[0][0] & 0xFFF80000)
        completeMask = (mask & 0x0007FF00) | 0xFFF80000
      if "CRAMCRG10" in protReg or "CRAMCSG1" in protReg:
        completeBase = (base & 0x0007FF00) | (deviceInfo.GlobalRAM[1][0] & 0xFFF80000)
        completeMask = (mask & 0x0007FF00) | 0xFFF80000
      if "CRAMCRG20" in protReg or "CRAMCSG2" in protReg:
        completeBase = (base & 0x001FFF00) | (deviceInfo.GlobalRAM[2][0] & 0xFFE00000)
        completeMask = (mask & 0x001FFF00) | 0xFFE00000
      if "CRAMCRG30" in protReg or "CRAMCSG3" in protReg:
        completeBase = (base & 0x0003FF00) | (deviceInfo.GlobalRAM[3][0] & 0xFFFC0000)
        completeMask = (mask & 0x0003FF00) | 0xFFFC0000
      if "CRAMCRG" in protReg: # overlapping CRG regions allow access to both configured SPIDs
        unitingProtections.append((completeBase, completeMask, spid))
      elif "CRAMCSG" in protReg: # CSG regions restrict access completely to the configured SPID
        intersectingProtections.append((completeBase, completeMask, spid))
      else:
        tst.eval(False) # not recognized register


# Check that every global RAM region is guarded as specified
for (start, length) in GlobalRamGuardRegions:
  regionProtected = True

  # Due to guard configuration given as bit mask, address ranges are difficult to calculate.
  # Instead just do the same check for every address as the guards do.
  for addr in range(start, start + length):
    # calculate sum of individual guards (overlap is intersection)
    intersectedSPID = 0xFFFFFFFF
    appliedIntersectingGuards = 0
    for (base, mask, spid) in intersectingProtections:
      if (addr & mask) == (base & mask):
        appliedIntersectingGuards += 1
        intersectedSPID &= spid
    if env.is_renesas_p1x_device() and appliedIntersectingGuards > 1:
      tst.eval_eq(appliedIntersectingGuards, 1) # allow no overlaps
      regionProtected = False
      break

    # calculate sum of individual permission (overlap is union)
    unitedSPID = 0x0
    appliedUnitingGuards = 0
    for (base, mask, spid) in unitingProtections:
      if (addr & mask) == (base & mask):
        appliedUnitingGuards += 1
        unitedSPID |= spid

    # in U2x when CRG and CSG overlap, CSG decides
    if appliedIntersectingGuards != 0:
      effectiveSPID = intersectedSPID
    elif appliedUnitingGuards != 0:
      effectiveSPID = unitedSPID
    else:
      # no guard configured for this address, address is not protected
      tst.eval(appliedIntersectingGuards != 0 or appliedUnitingGuards != 0)
      regionProtected = False
      break

    # expected SPID is safe SPID only by default, but exceptions can apply
    expectedSPID = 0x1 << safeSPID
    if (env.is_renesas_u2a_device() or env.is_renesas_u2c_device()) and emulationDevice in ["D7ED", "M6ED", "K3ED"]:
      expectedSPID |= DebugSPID_mask
    for (excStart, excEnd, excSPID) in GlobalRamGuardExceptions:
      if addr >= excStart and addr < excEnd:
        expectedSPID |= excSPID


    if RestrictedSPIDEnabled == False:
      # if protection is not configured exactly as expected,
      # stop checking this region and report failed
      if expectedSPID != effectiveSPID:
        tst.eval_eq(expectedSPID, effectiveSPID)
        regionProtected = False
        break
    else:
      # If RestrictedSPID feature is active, RestrictedSPID is allowed instead of/in combination with SafeSPID
      restrictedAndSafeMask = (1 << safeSPID) | (1 << restrictedSPID)
      # check if at least one of RestrictedSPID or SafeSPID is set
      if (effectiveSPID & restrictedAndSafeMask) == 0:
        tst.eval(False) # neither SafeSPID nor RestrictedSPID has write access
        regionProtected = False
        break
      # check if other expected SPIDs are set
      elif (expectedSPID & ~restrictedAndSafeMask) != (effectiveSPID & ~restrictedAndSafeMask):
        tst.eval(False) # protection is not configured as expected
        regionProtected = False
        break


  tst.eval(regionProtected)

tst.end()