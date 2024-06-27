'''
/**
 * \TestCaseName RBSYS_BootblockStartup
 *
 * \Reference Gen_SWFS_0979_HSW_OverallRequirements_6800, Gen_SWCS_HSW_uC_Base_SYS-267
 *
 * \Purpose Check that system timer is working in BB, BMGR is only run by core 0 and application is reached by all cores and only via SW reset
 *
 * \Sequence
 * - Run system until jump to BMGR
 * - Run for 25ns to check running system timer in BMGR
 * - Run system until RBSYS_StartupPreOSPhase2 so that all cores must have reached application
 *
 * \ExpectedResult
 * - Only core 0 executed BBMain
 * - System timer is running in BBMain
 * - At the start of FSWStartup the SWReset flag is set (ensure branch from BMGR to Application via SW reset)
 * - All cores reach the application
 */
'''

import swt2.test as tst
import swt2.application as app
import swt2.target as tgt
import swt2.environment as env


app.execution_condition(include_switches=["RBFS_Bootblock_Enabled"])

tst.start()

#############################################################################
#                             Setup                                         #
#############################################################################

# device family specific register information
if (env.is_renesas_p1x_device()):
  ResfReg = "RH850.PFRH850.SYSCTL.PWRSTCTL_D4.RESF"
  ResfSWSystemResetFlag = (1 << 3)
  ResfSWApplicationResetFlag = (1 << 7)

  SyncTimeCntReg = "RH850.PFRH850.STM0.CNT1"
  RealTimeCntReg = "RH850.PFRH850.STM0.CNT2"

elif(env.is_renesas_u2a_device()):
  ResfReg = "RH850.PFRH850.PWRSTCTL.RESF"
  ResfSWSystemResetFlag = (1 << 4)
  ResfSWApplicationResetFlag = (1 << 8)

  SyncTimeCntReg = "RH850.CPUSS.SCHEAPG4.NSMVRH850V02.G4SS.TPTM.TPTM0UCNT0"
  RealTimeCntReg = "RH850.CPUSS.SCHEAPG4.NSMVRH850V02.G4SS.TPTM.TPTM0UCNT1"


# at jumps to BMGR check that only core 0 reaches this point
def BMGRCoreCheck(br):
  tst.eval(br.core == tgt.get_core(0))

tgt.add_breakpoint("RB_JumpToBBMain", image=app.get_bmgr_elf_image(), action=BMGRCoreCheck)


# at application start check that a SW reset flag is set
def FSWResetCheck(br):
  RESF = tgt.get_register(ResfReg).read()
  tst.eval( ((RESF & ResfSWSystemResetFlag) != 0) or ((RESF & ResfSWApplicationResetFlag) != 0) )

tgt.add_breakpoint("FSWStart", image=app.get_bmgr_elf_image(), action=FSWResetCheck)


#############################################################################
#                             Test start                                    #
#############################################################################

# run until jump to BMGR
hit = tgt.is_breakpoint_hit(tgt.run_until("RB_JumpToBBMain", image=app.get_bmgr_elf_image(), timeout=200))
tst.eval(hit) # if False: BMGR not reached, BMGRCoreCheck could not run

if hit:
  # check that system timer is running in BMGR by letting 25ns elapse and checking timer counter registers for change
  SyncTimeCnt = tgt.get_register(SyncTimeCntReg).read()
  RealTimeCnt = tgt.get_register(RealTimeCntReg).read()
  tgt.run(25, timeout_unit="ns")
  tst.eval(SyncTimeCnt < tgt.get_register(SyncTimeCntReg).read())
  tst.eval(RealTimeCnt < tgt.get_register(RealTimeCntReg).read())

  # run until RBSYS_StartupPreOSPhase2, cores have been synced before that by RBHWBIST_PRC_HWBISTEvaluationAndPatternTest, so all cores reached application
  hit = tgt.is_breakpoint_hit(tgt.run_until("RBSYS_StartupPreOSPhase2", timeout=300))
  tst.eval(hit) # if False: at least one core did not reach application, FSWResetCheck might not have run

tst.end()