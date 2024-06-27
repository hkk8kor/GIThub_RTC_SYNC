'''
/**
 * \Reference
 * Gen_SWFS_0979_HSW_OverallRequirements_6738
 *
 * \Purpose
 * Check SPID configuration
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
 * Run until SPID configuration is finished
 *
 * \ExpectedResult
 * U2x: SPID Masks are not locked at start of FSW (also after OEMBLDR/RBBLDR were running) and at the end of BMGR but are locked after initialization
 * PE's and other safe busmaster's SPIDs are set to safe SPID
 * All other bus master's SPIDs are set to unsafe SPID (exceptions: HSM, AUD)
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.environment as env
import swt2.application as app


app.execution_condition("ALWAYS")

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
    tst.eval_eq(lock & 0x1, expectedValue)


#############################################################################
#                             Setup                                         #
#############################################################################
# SPID configuration depends on target device and does not factor in emulation device function switch
targetDevice = app.get_function_switch_setting("RBFS_TargetDevice")[-2:]
# U2x emulation devices have additional bus masters to configure (AUD, MAU)
emulationDevice = app.get_function_switch_setting("RBFS_EmulationDevice")[-4:]

# SPIDs and SPID masks
safeSPID       = 2
unsafeSPID     = 3
restrictedSPID = 4
DMAUnsafeSPID  = 5
AUDSPID        = 30
MAUSPID        = 31
SPID_mask      = 0x1F
if env.is_renesas_u2c_device():
  safeSPID = 0

# Expected configuration of bus master SPIDs
if env.is_renesas_p1x_device():
  # Safe bus masters
  Core_SPIDs = [(core.get_register("MCFG0").get_path(), 16) for core in app.get_used_cores()]
  DTS_SPIDs  = [("RH850.PFRH850.DMA.DTSCM%d" % i, 18) for i in range(128)]
  DMA0_SPIDs = [("RH850.PFRH850.DMA.DM0CM%d" % i, 2) for i in range(8)]
  if targetDevice not in ["D1", "D2"]:
    DMA1_SPIDs = [("RH850.PFRH850.DMA.DM1CM%d" % i, 2) for i in range(8)]
  else:
    DMA1_SPIDs = []

  safeBusMaster = Core_SPIDs + DTS_SPIDs + DMA0_SPIDs + DMA1_SPIDs

  # Unsafe bus masters
  unsafeBusMaster = []
  if targetDevice not in ["D1", "D2"]:
    unsafeBusMaster += [
      (0xFFFA1000, 0),  # FlexRay0
      (0xFFFA1008, 0),  # Ethernet0
      (0xFFFA1010, 0),  # HS-USRT0
      (0xFFFA1014, 0)   # HS-USRT1
    ]
  if targetDevice not in ["D1", "D2", "D3"]:
    unsafeBusMaster += [
      (0xFFFA1004, 0),  # FlexRay1
      (0xFFFA100C, 0),  # Ethernet1
      (0xFFFA1018, 0),  # HS-USRT2
      (0xFFFA101C, 0)   # HS-USRT3
    ]

  # SPIDs cannot be locked on P1x, only U2x
  LockRegs = []

elif env.is_renesas_u2a_device():
  # Safe bus masters
  Core_SPIDs = [(core.get_register("SPID").get_path(), 0) for core in app.get_used_cores()] # Cores 2 and 3 are not in use, SPID can only be set by the core itself
  DTS_SPIDs = [("RH850.PFRH850.DTS.DTSCM[%d]" % i, 18) for i in range (128)]
  safeBusMaster = Core_SPIDs + DTS_SPIDs

  # Unsafe bus masters
  unsafeBusMaster = [
    ("RH850.PFRH850.SPID.BMSPID[23]", 0), # FlexRay0
    ("RH850.PFRH850.SPID.BMSPID[24]", 0)  # Fast Ether
  ]
  if targetDevice in ["D7", "M6", "M3"]:
    unsafeBusMaster += [
      ("RH850.PFRH850.SPID.BMSPID[17]", 0), # Gb Ether
      ("RH850.PFRH850.SPID.BMSPID[19]", 0), # RHSIF0
      ("RH850.PFRH850.SPID.BMSPID[22]", 0), # FlexRay1
    ]

  # DMAUnsafe bus masters
  DMA0_SPIDs = [("RH850.PFRH850.DMA0.CM[%d]" % i, 8) for i in range (16)]
  DMA1_SPIDs = [("RH850.PFRH850.DMA1.CM[%d]" % i, 8) for i in range (16)]
  DMAUnsafeBusMaster = DMA0_SPIDs + DMA1_SPIDs

  # Other SPIDs for HSM and Debugging
  Others = [
    ("RH850.PFRH850.SPID.BMSPID[25]", 0, 25), # ICUM_AES0
    ("RH850.PFRH850.SPID.BMSPID[26]", 0, 26), # ICUMHA
    ("RH850.PFRH850.SPID.BMSPID[30]", 0, 30)  # AUD
  ]

  # Masks for restricting selectable SPIDs per bus master
  MaskRegs = [
    ("RH850.PFRH850.SPID.BMSPIDMSK[0]",  (0x1 << safeSPID), (0x1 << restrictedSPID)), # CPU0
    ("RH850.PFRH850.SPID.BMSPIDMSK[1]",  (0x1 << safeSPID), (0x1 << restrictedSPID)), # CPU1
    ("RH850.PFRH850.SPID.BMSPIDMSK[23]", 0x1 << unsafeSPID), # FlexRay0
    ("RH850.PFRH850.SPID.BMSPIDMSK[24]", 0x1 << unsafeSPID), # Fast Ether
    ("RH850.PFRH850.SPID.BMSPIDMSK[25]", 0), # ICUM_AES0
    ("RH850.PFRH850.SPID.BMSPIDMSK[26]", 0), # ICUMHA
    ("RH850.PFRH850.SPID.BMSPIDMSK[27]", 0x1 << DMAUnsafeSPID), # sDMAC1
    ("RH850.PFRH850.SPID.BMSPIDMSK[28]", 0x1 << DMAUnsafeSPID), # sDMAC0
    ("RH850.PFRH850.SPID.BMSPIDMSK[29]", 0x1 << safeSPID) # DTS
  ]
  if targetDevice in ["D7", "M6", "M3"]:
    MaskRegs += [
      ("RH850.PFRH850.SPID.BMSPIDMSK[17]", 0x1 << unsafeSPID), # Gb Ether
      ("RH850.PFRH850.SPID.BMSPIDMSK[19]", 0x1 << unsafeSPID), # RHSIF0
      ("RH850.PFRH850.SPID.BMSPIDMSK[22]", 0x1 << unsafeSPID), # FlexRay1
    ]
  if targetDevice in ["D7", "M6"]:
    MaskRegs += [
      ("RH850.PFRH850.SPID.BMSPIDMSK[2]",  0), # CPU2
      ("RH850.PFRH850.SPID.BMSPIDMSK[3]",  0)  # CPU3
    ]
  if emulationDevice in ["D7ED", "M6ED"]:
    MaskRegs += [
      ("RH850.PFRH850.SPID.BMSPIDMSK[30]", (0x1 << AUDSPID) | (0x1 << MAUSPID)),  # AUD
      ("RH850.PFRH850.SPID.BMSPIDMSK[31]", (0x1 << AUDSPID) | (0x1 << MAUSPID))   # MAU
    ]

  LockRegs = [
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[0]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[1]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[23]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[24]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[25]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[26]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[27]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[28]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[29]"
  ]
  if targetDevice in ["D7", "M6", "M3"]:
    LockRegs += [
      "RH850.PFRH850.SPID.BMSPIDMSKLOCK[17]",
      "RH850.PFRH850.SPID.BMSPIDMSKLOCK[19]",
      "RH850.PFRH850.SPID.BMSPIDMSKLOCK[22]",
    ]
  if targetDevice in ["D7", "M6"]:
    LockRegs += [
      "RH850.PFRH850.SPID.BMSPIDMSKLOCK[2]",
      "RH850.PFRH850.SPID.BMSPIDMSKLOCK[3]"
    ]
  if emulationDevice in ["D7ED", "M6ED"]:
    LockRegs += [
      "RH850.PFRH850.SPID.BMSPIDMSKLOCK[30]",
      "RH850.PFRH850.SPID.BMSPIDMSKLOCK[31]"
    ]
elif env.is_renesas_u2c_device():
  # Safe bus masters
  Core_SPIDs = [(core.get_register("SPID").get_path(), 0) for core in app.get_used_cores()]
  DTS_SPIDs = [("RH850.PFRH850.DTS.DTSCM[%d]" % i, 18) for i in range (128)]
  safeBusMaster = Core_SPIDs + DTS_SPIDs

  # Unsafe bus masters, todo: SPID register over 31 are not implemented by VLAB yet
  unsafeBusMaster = [
    ("RH850.PFRH850.SPID.BMSPID[10]", 0), # GTM Cluster 0
    ("RH850.PFRH850.SPID.BMSPID[11]", 0), # GTM Cluster 1
    ("RH850.PFRH850.SPID.BMSPID[22]", 0), # Ether AVB0 (T1S)
    ("RH850.PFRH850.SPID.BMSPID[23]", 0), # ACEU
    ("RH850.PFRH850.SPID.BMSPID[30]", 0), # CANXL0
  ]
  if targetDevice in ["K1","K3"]:
    unsafeBusMaster += [
      ("RH850.PFRH850.SPID.BMSPID[29]", 0), # CANXL1
      #("RH850.PFRH850.SPID.BMSPID[32]", 0), # FlexRay0
      #("RH850.PFRH850.SPID.BMSPID[34]", 0)  # ETND0
    ]
  if targetDevice in ["K3"]:
    unsafeBusMaster += [
      #("RH850.PFRH850.SPID.BMSPID[33]", 0), # ETND1
    ]

  # DMAUnsafe bus masters
  DMA0_SPIDs = [("RH850.PFRH850.DMA0.CM[%d]" % i, 8) for i in range (16)]
  DMA1_SPIDs = [("RH850.PFRH850.DMA1.CM[%d]" % i, 8) for i in range (16)]
  DMAUnsafeBusMaster = [] #DMA0_SPIDs + DMA1_SPIDs, todo: sDMAC SPIDs not configured yet

  # Other SPIDs for HSM and Debugging
  Others = [
    #("RH850.PFRH850.SPID.BMSPID[35]", 0, 25), # ICUM
    #("RH850.PFRH850.SPID.BMSPID[36]", 0, 26), # AES
    #("RH850.PFRH850.SPID.BMSPID[37]", 0, 30), # ICUM DMA
    #("RH850.PFRH850.SPID.BMSPID[43]", 0, 30)  # ICUM debug
  ]

  # Masks for restricting selectable SPIDs per bus master, todo: 38,39,40,42 are not yet mapped to the following peripherals: sDMAC1, sDMAC0, DTS, MAU
  MaskRegs = [
    ("RH850.PFRH850.SPID.BMSPIDMSK[0]",  (0x1 << safeSPID), (0x1 << restrictedSPID)), # CPU0
    ("RH850.PFRH850.SPID.BMSPIDMSK[10]", 0x1 << unsafeSPID),                          # GTM Cluster 0
    ("RH850.PFRH850.SPID.BMSPIDMSK[11]", 0x1 << unsafeSPID),                          # GTM Cluster 1
    ("RH850.PFRH850.SPID.BMSPIDMSK[22]", 0x1 << unsafeSPID),                          # Ether AVB0 (T1S)
    ("RH850.PFRH850.SPID.BMSPIDMSK[23]", 0x1 << unsafeSPID),                          # ACEU
    ("RH850.PFRH850.SPID.BMSPIDMSK[29]", 0x1 << unsafeSPID),                          # CANXL1
    ("RH850.PFRH850.SPID.BMSPIDMSK[30]", 0x1 << unsafeSPID),                          # CANXL0
    #("RH850.PFRH850.SPID.BMSPIDMSK[35]", 0),                                          # ICUM
    #("RH850.PFRH850.SPID.BMSPIDMSK[36]", 0),                                          # AES
    #("RH850.PFRH850.SPID.BMSPIDMSK[37]", 0),                                          # ICUM DMA
    #("RH850.PFRH850.SPID.BMSPIDMSK[43]", 0),                                          # ICUM debug
  ]
  if targetDevice in ["K1","K3"]:
    MaskRegs += [
      ("RH850.PFRH850.SPID.BMSPIDMSK[1]",  (0x1 << safeSPID), (0x1 << restrictedSPID)), # CPU1
      ("RH850.PFRH850.SPID.BMSPIDMSK[29]", 0x1 << unsafeSPID),                          # CANXL1
      #("RH850.PFRH850.SPID.BMSPIDMSK[32]", 0x1 << unsafeSPID),                          # FlexRay0
      #("RH850.PFRH850.SPID.BMSPIDMSK[34]", 0x1 << unsafeSPID),                          # ETND0
    ]
  if targetDevice in ["K3"]:
    MaskRegs += [
      #("RH850.PFRH850.SPID.BMSPIDMSK[33]", 0x1 << unsafeSPID), # ETND1
    ]

  LockRegs = [
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[0]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[10]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[11]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[22]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[23]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[29]",
    "RH850.PFRH850.SPID.BMSPIDMSKLOCK[30]",
    #"RH850.PFRH850.SPID.BMSPIDMSKLOCK[35]",
    #"RH850.PFRH850.SPID.BMSPIDMSKLOCK[36]",
    #"RH850.PFRH850.SPID.BMSPIDMSKLOCK[37]",
    #"RH850.PFRH850.SPID.BMSPIDMSKLOCK[43]"
  ]
  if targetDevice in ["K1","K3"]:
    LockRegs += [
      "RH850.PFRH850.SPID.BMSPIDMSKLOCK[1]",
      "RH850.PFRH850.SPID.BMSPIDMSKLOCK[29]",
      #"RH850.PFRH850.SPID.BMSPIDMSKLOCK[32]",
      #"RH850.PFRH850.SPID.BMSPIDMSKLOCK[34]"
    ]
  if targetDevice in ["K3"]:
    LockRegs += [
      #"RH850.PFRH850.SPID.BMSPIDMSKLOCK[33]"
    ]


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
CheckGuardLockBit(1)

# PE's and other safe busmaster's SPIDs are set to safe SPID
for (reg, offset) in safeBusMaster:
  spid = (ReadRegisterOrAddress(reg) >> offset) & SPID_mask
  tst.eval_eq(spid, safeSPID)

# All other bus master's SPIDs are set to unsafe SPID (exception: HSM, AUD)
for (reg, offset) in unsafeBusMaster:
  spid = (ReadRegisterOrAddress(reg) >> offset) & SPID_mask
  tst.eval_eq(spid, unsafeSPID)

if env.is_renesas_u2a_device() or env.is_renesas_u2c_device():
  # DMA unsafe bus master
  for (reg, offset) in DMAUnsafeBusMaster:
    spid = (ReadRegisterOrAddress(reg) >> offset) & SPID_mask
    tst.eval_eq(spid, DMAUnsafeSPID)

  # Others
  for (reg, offset, expectedSpid) in Others:
    spid = (ReadRegisterOrAddress(reg) >> offset) & SPID_mask
    tst.eval_eq(spid, expectedSpid)

  # On U2x allowed SPIDs can be restricted per bus master
  for element in MaskRegs:
    if len(element) == 3:
      maskReg, expectedMask, optionalMask = element
    else:
      maskReg, expectedMask = element
      optionalMask = 0
    mask = ReadRegisterOrAddress(maskReg)
    mask &= ~optionalMask # remove optional SPIDs from check
    tst.eval_eq(mask, expectedMask)


tst.end()