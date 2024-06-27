'''
/**
 * \Reference
 *  Gen_SWFS_0979_HSW_OverallRequirements_6738, Gen_SWCS_HSW_uC_Base_SYS-332
 *
 * \Purpose
 *  Test if a locked GRAM Guard is detected during configuration and a SysErrorHook is reported later (after cinit)
 *
 * \Sequence
 *  Lock one GRAM Guard (by setting MGDGRxPROT.LOCK)
 *  Run until End of Init
 *  Eval: SysErrorHook shall be reported with Debug0 == RBSYS_Error_GuardConfigurationFailed and Debug1 == 0x1 (GRG configuration invalid)
 *
 * \ExpectedResult
 *  see \Sequence
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.application as app


app.execution_condition(include_switches=["RBFS_GlobalRamSupport_ON", "RBFS_uCFamily_RenesasP1x"])

#############################################################################
#                             Test start                                    #
#############################################################################

tst.start()

tgt.run_until("RBSYS_StartupPreOSPhase0")
tgt.write_memory_uint32(0xFFC49010, (1<<31)) # set lock bit of MGDGRPROT1
app.run_until_end_of_init()

tst.eval(app.get_event("RBSYS_SYSErrorHook").is_failed())

app.run_until_bfm_was_updated()
tst.eval_eq(app.get_bfm_record("RBSYS_SYSErrorHook").get_debug0(), 0x8)
tst.eval_eq(app.get_bfm_record("RBSYS_SYSErrorHook").get_debug1(), 0x2)

tst.end()