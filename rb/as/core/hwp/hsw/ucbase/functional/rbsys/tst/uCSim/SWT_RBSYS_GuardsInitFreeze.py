'''
/**
 * \Reference
 * Gen_SWFS_0979_HSW_OverallRequirements_6738
 *
 * \Purpose
 * Check Freeze Guard error handling for wrongly configured guards
 *
 * \Sequence
 * Run until initialization is done
 * For selected guards checked by FreezeGuards:
 *   Reset test environment
 *   Run until start of FSW (one exception for manipulating U2A PE Guard: run until after PE Guard is configured but before access is restricted)
 *   Set (and lock if possible) wrong guard configuration
 *   Run until BFM was updated
 *
 * \ExpectedResult
 * RBSYS_SYSErrorHook must not be set on first run
 * RBSYS_SYSErrorHook must be set after manipulation
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.environment as env
import swt2.application as app


app.execution_condition("ALWAYS")

#############################################################################
#                             Setup                                         #
#############################################################################
# Guard configuration depends on target device and does not factor in emulation device function switch
targetDevice = app.get_function_switch_setting("RBFS_TargetDevice")[-2:]
# U2x emulation devices have to permit access for debug bus masters (AUD, MAU)
emulationDevice = app.get_function_switch_setting("RBFS_EmulationDevice")[-4:]

# SPIDs and SPID masks
safeSPID       = 2
unsafeSPID     = 3
restrictedSPID = 4
AUDSPID        = 30
MAUSPID        = 31

if env.is_renesas_u2a_device():
  if emulationDevice != "None":
    SPID_SAFE_MASK = (0x1 << safeSPID) | 0x1 << AUDSPID | 0x1 << MAUSPID
  else:
    SPID_SAFE_MASK = 0x1 << safeSPID
elif env.is_renesas_u2c_device():
  safeSPID = 0
  if emulationDevice != "None":
    SPID_SAFE_MASK = (0x1 << safeSPID)  | 0x1 << MAUSPID
  else:
    SPID_SAFE_MASK = 0x1 << safeSPID

# Wrong configurations for various guards
if env.is_renesas_p1x_device():
  FreezeGuardViolations = [
    # PBUS Guard (APBFSGDPROT_INTC2_B, APBFSGDSPID_INTC2_B): wrong PROT and wrong SPID
    (0xFFC4C028, 0xFFC4C02C, 0x0601FE1B | (1 << 18) | (1 << 19) | (1 << 21) | (1 << 22) | (1 << 31), 0x1 << safeSPID),
    (0xFFC4C028, 0xFFC4C02C, 0x0601FE1B | (1 << 18) | (1 << 19) | (1 << 31), 0x1 << unsafeSPID)
  ]
  if targetDevice not in ["D1", "D2"]:
    FreezeGuardViolations += [
      # HBUS Guard (FSGDF0PROT01, FSGDF0SPID01): wrong PROT and wrong SPID
      (0xFFFA0008, 0xFFFA000C, 0x0601FE1B | (1 << 18) | (1 << 19) | (1 << 21) | (1 << 22) | (1 << 31), 0x1 << safeSPID),
      (0xFFFA0008, 0xFFFA000C, 0x0601FE1B | (1 << 18) | (1 << 19) | (1 << 31),  0x1 << unsafeSPID)
    ]
elif env.is_renesas_u2a_device():
  FreezeGuardViolations = [
    # CSG: wrong PROT and wrong SPID
    ("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.GUARD_CRAMCSG0.PROT0", "RH850.PFRH850.GUARD_CRAMCSG0.SPID0", "RH850.PFRH850.GUARD_CRAMCRG00.KCPROT", 0x1 | (0x1 << 1) | (0x1 << 8) | (0x1 << 31), SPID_SAFE_MASK),
    ("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.GUARD_CRAMCSG0.PROT0", "RH850.PFRH850.GUARD_CRAMCSG0.SPID0", "RH850.PFRH850.GUARD_CRAMCRG00.KCPROT", (0x1 << 8) | (0x1 << 31), SPID_SAFE_MASK | (0x1 << unsafeSPID)),
    # SPID module: wrong SPID
    ("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.SPID.BMSPIDMSKLOCK[0]", "RH850.PFRH850.SPID.BMSPIDMSK[0]", "RH850.PFRH850.SPID.SPIDKCPROT", 0x1, (0x1 << safeSPID) | (0x1 << unsafeSPID) | (0x1 << restrictedSPID)),
    # PBUS Guard: wrong PROT and wrong SPID
    ("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.PBG0.PROT0_CH0_GR0", "RH850.PFRH850.PBG0.PROT1_CH0_GR0", "RH850.PFRH850.PBG0.KCPROT", 0x1 << 31, SPID_SAFE_MASK),
    ("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.PBG0.PROT0_CH0_GR0", "RH850.PFRH850.PBG0.PROT1_CH0_GR0", "RH850.PFRH850.PBG0.KCPROT", (0x1 << 4) | (0x1 << 6) | (0x1 << 8) | (0x1 << 31), SPID_SAFE_MASK | (0x1 << unsafeSPID)),
    # HBUS Guard: wrong PROT and wrong SPID
    ("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.HBG92.PROT0", "RH850.PFRH850.HBG92.PROT1", "RH850.PFRH850.HBG92.KCPROT", 0x1 << 31, SPID_SAFE_MASK),
    ("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.HBG92.PROT0", "RH850.PFRH850.HBG92.PROT1", "RH850.PFRH850.HBG92.KCPROT", (0x1 << 4) | (0x1 << 6) | (0x1 << 8) | (0x1 << 31), SPID_SAFE_MASK | (0x1 << unsafeSPID)),
  ]
elif env.is_renesas_u2c_device():
  FreezeGuardViolations = [
    # CRG: wrong PROT and wrong SPID, todo: not checked by our software yet
    # ("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.GUARD_CRAMCRG00.PROT0", "RH850.PFRH850.GUARD_CRAMCRG00.SPID0", "RH850.PFRH850.GUARD_CRAMCRG00.KCPROT", 0x1 | (0x1 << 1) | (0x1 << 8) | (0x1 << 31), SPID_SAFE_MASK),
    # ("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.GUARD_CRAMCRG00.PROT0", "RH850.PFRH850.GUARD_CRAMCRG00.SPID0", "RH850.PFRH850.GUARD_CRAMCRG00.KCPROT", (0x1 << 8) | (0x1 << 31), SPID_SAFE_MASK | (0x1 << unsafeSPID)),
    # SPID module: wrong SPID
    ("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.SPID.BMSPIDMSKLOCK[0]", "RH850.PFRH850.SPID.BMSPIDMSK[0]", "RH850.PFRH850.SPID.SPIDKCPROT", 0x1, (0x1 << safeSPID) | (0x1 << unsafeSPID) | (0x1 << restrictedSPID)),
    # PBUS Guard: wrong PROT and wrong SPID
    ("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.PBG00.PROT0_CH2_GR0", "RH850.PFRH850.PBG00.PROT1_CH2_GR0", "RH850.PFRH850.PBG00.KCPROT", 0x1 << 31, SPID_SAFE_MASK),
    ("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.PBG00.PROT0_CH2_GR0", "RH850.PFRH850.PBG00.PROT1_CH2_GR0", "RH850.PFRH850.PBG00.KCPROT", (0x1 << 4) | (0x1 << 6) | (0x1 << 8) | (0x1 << 31), SPID_SAFE_MASK | (0x1 << unsafeSPID)),
    # HBUS Guard: wrong PROT and wrong SPID, todo: HBG not implemented in VLAB yet
    #("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.HBG92.PROT0", "RH850.PFRH850.HBG92.PROT1", "RH850.PFRH850.HBG92.KCPROT", 0x1 << 31, SPID_SAFE_MASK),
    #("RBSYS_StartupPreOSPhase0", "RH850.PFRH850.HBG92.PROT0", "RH850.PFRH850.HBG92.PROT1", "RH850.PFRH850.HBG92.KCPROT", (0x1 << 4) | (0x1 << 6) | (0x1 << 8) | (0x1 << 31), SPID_SAFE_MASK | (0x1 << unsafeSPID)),
  ]


#############################################################################
#                             Test start                                    #
#############################################################################
tst.start()

# Run until init is done
app.run_until_end_of_init()

#############################################################################
#              GoodCheck -> Failure is not already set                      #
#############################################################################
tst.eval(not app.get_event("RBSYS_SYSErrorHook").is_failed())

#############################################################################
#                             Manipulation                                  #
#############################################################################
for manipulationTuple in FreezeGuardViolations:
  app.do_test_environment_reset()
  if env.is_renesas_p1x_device():
    tgt.run_until("RBSYS_StartupPreOSPhase0")
    protReg, spidReg, prot, spid = manipulationTuple
    tgt.write_memory_uint32(spidReg, spid)
    tgt.write_memory_uint32(protReg, prot)

  elif env.is_renesas_u2a_device() or env.is_renesas_u2c_device():
    bp, protReg, spidReg, kprotReg, prot, spid = manipulationTuple
    tgt.run_until(bp)
    tgt.get_register(kprotReg).write(0xA5A5A501)
    tgt.get_register(spidReg).write(spid)
    tgt.get_register(protReg).write(prot)
    tgt.get_register(kprotReg).write(0xA5A5A500)

  #############################################################################
  #                             Failure must be set                           #
  #############################################################################
  app.run_until_end_of_init()
  tst.eval(app.get_event("RBSYS_SYSErrorHook").is_failed())

  app.run_until_bfm_was_updated()
  tst.eval_eq(app.get_bfm_record("RBSYS_SYSErrorHook").get_debug0(), 0x8)
  if env.is_renesas_p1x_device():
    tst.eval_eq(app.get_bfm_record("RBSYS_SYSErrorHook").get_debug1(), 0x4)
  elif env.is_renesas_u2a_device() or env.is_renesas_u2c_device():
    tst.eval((app.get_bfm_record("RBSYS_SYSErrorHook").get_debug1() & 0xF) > 0)

tst.end()