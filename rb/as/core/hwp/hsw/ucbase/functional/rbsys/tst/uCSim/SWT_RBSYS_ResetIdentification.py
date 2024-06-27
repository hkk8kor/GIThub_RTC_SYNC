'''
/**
 * \TestCaseName RBSYS_ResetIdentification
 *
 * \Reference
 *
 * \Purpose Check that Information on the type of Reset is pertained and given to Users
 *
 * \Sequence
 * - Perform Terminal Reset (ASIC Undervoltage Reset)
 * - Run until RBSYS_StartupPreOsPhase1
 * - Check that User BackupRAM contains the TerminalReset Flag (currently only for RBECM)
 *
 * \ExpectedResult
 * see \Sequence
 */
'''

import swt2.test as tst
import swt2.application as app
import swt2.target as tgt
import swt2.software as sw
import swt2.environment as env


app.execution_condition(include_switches=["RBFS_BackupRAMLayout_V1", "RBFS_uCFamily_RenesasU2A"])
# Currently, RBECM requires those interfaces for U2A only (and interfaces are only available in case of BackupRAMLayout_V1 )

tst.start()

#############################################################################
#                             Setup                                         #
#############################################################################

# device family specific register information
if (env.is_renesas_p1x_device()):
  ResfReg = "RH850.PFRH850.SYSCTL.PWRSTCTL_D4.RESF"
  TerminalResetFlag = (1<<1)


elif(env.is_renesas_u2a_device() or env.is_renesas_u2c_device()):
  ResfReg = "RH850.PFRH850.PWRSTCTL.RESF"
  TerminalResetFlag = (1<<2)

tgt.get_register(ResfReg).write(tgt.get_register(ResfReg).read() & ~TerminalResetFlag) # Delete possible TerminalResetFlag (Could be set by PowerOn Reset)

# Sanity Check: Terminal Reset is not set by default
tgt.run_until_end_of("RBSYS_BackupRAM_FSW_GetResetFlagsForRBECM")
resetFlags = sw.get_variable("RBSYS_BackupRAM_SYS_Current.ResetFlagsForRBECM").read()
tst.eval( (resetFlags & TerminalResetFlag) == 0 )

# SW Test starts here!
# Reset via Undervoltage Reset
tgt.do_terminal_reset()

# Run until ResetFlag handling has been completed
tgt.run_until_end_of("RBSYS_BackupRAM_FSW_GetResetFlagsForRBECM")

# Evaluate if TerminalReset has been stored
resetFlags = sw.get_variable("RBSYS_BackupRAM_SYS_Current.ResetFlagsForRBECM").read()
tst.eval( (resetFlags & TerminalResetFlag) != 0 )

tst.end()