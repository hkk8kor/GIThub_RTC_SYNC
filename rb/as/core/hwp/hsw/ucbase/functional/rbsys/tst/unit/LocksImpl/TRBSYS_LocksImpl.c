#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                       ///< for RBFS_MCORE, RBFS_TPSWCapsule

#include "TRBSYS_LocksImpl_Adaptor.h"
#include "RBSYS_Subsystem.h"


#include "RBSYS_LocksImplIntern.h"
#include "RBSYS_LocksImpl.h"

#include "RBHSWDEM_Facade.h"
#include "DemStub_Helper.h"
#include "TRBSYS_Intrinsics.h"
#include "TRBSYS_CpuInfo.h"
#include "TRBSYS_SystemTimer.h"

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
   #define TRBSYS_PMRVAL_LOCKED   (0xFFFFu)
   #define TRBSYS_PMRVAL_UNLOCKED (0x0u)
#elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
   #define TRBSYS_PMRVAL_LOCKED   (0x0u)
   #define TRBSYS_PMRVAL_UNLOCKED (0x10u)
#endif

#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
/********************************/
/*    FAST CORE LOCAL LOCK      */
/********************************/

/**
 * \Reference
 * RBSYS_EnterCorelocalIntlockSysfast, RBSYS_ExitCorelocalIntlockSysfast, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Single balanced fast core local lock
 *
 * \Sequence
 *  Call fast core local lock balanced (Enter+Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  Interrupts must be masked via PMR (interrupt priority masking) register after function call of RBSYS_EnterCorelocalIntlockSysfast
 *  Interrupts must be released via PMR after function call of RBSYS_ExitCorelocalIntlockSysfast
 *  No failure entry available
 */
SWTEST void TRBSYS_PRC_LockMonitoring_FastCoreLocalLock_single_balanced(void)
{
  int i;
  unsigned int reg_val;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);
    RBSYS_LDSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID(), TRBSYS_PMRVAL_UNLOCKED);

    RBSYS_EnterCorelocalIntlockSysfast();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_ExitCorelocalIntlockSysfast();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_UNLOCKED);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCorelocalIntlockSysfast, RBSYS_ExitCorelocalIntlockSysfast, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Nested balanced fast core local lock
 *
 * \Sequence
 *  Call fast core local lock nested balanced (Enter+Enter+Exit+Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  No failure entry available
 *  Interupts must still be masked via PMR (interrupt priority masking) register as long as second function call of RBSYS_ExitCorelocalIntlockSysfast
 */
SWTEST void TRBSYS_PRC_LockMonitoring_FastCoreLocalLock_balanced_nested(void)
{
  int i;
  unsigned int reg_val;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);
    RBSYS_LDSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID(), TRBSYS_PMRVAL_UNLOCKED);

    RBSYS_EnterCorelocalIntlockSysfast();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_EnterCorelocalIntlockSysfast();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 2);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_ExitCorelocalIntlockSysfast();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_ExitCorelocalIntlockSysfast();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_UNLOCKED);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCorelocalIntlockSysfast, RBSYS_ExitCorelocalIntlockSysfast, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Unbalanced fast core local lock (only RBSYS_EnterCorelocalIntlockSysfast called)
 *
 * \Sequence
 *  Call fast core local lock unbalanced (Enter)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
 */
SWTEST void TRBSYS_PRC_LockMonitoring_FastCoreLocalLock_unbalanced_enter(void)
{
  uint32 expected_lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;
  uint32 expected_nest_cnt = 1;
  RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Local;

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    RBSYS_EnterCorelocalIntlockSysfast();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_nest_cnt);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidLockNesting);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                               (  ((expected_nest_cnt  & 0xFu) << 28)
                                | ((expected_lock_type & 0x3u) << 26)
                                | ((RBSYS_getCoreID()  & 0x3u) << 24)
                                | ( expected_lockaddr  & 0x00FFFFFFu)));


    RBSYS_ExitCorelocalIntlockSysfast();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCorelocalIntlockSysfast, RBSYS_ExitCorelocalIntlockSysfast, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Unbalanced fast core local lock (only RBSYS_ExitCorelocalIntlockSysfast called)
 *
 * \Sequence
 *  Call fast core local lock unbalanced (Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
 */
SWTEST void TRBSYS_PRC_LockMonitoring_FastCoreLocalLock_unbalanced_exit(void)
{
  uint32 expected_lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;
  uint32 expected_nest_cnt = -1;
  RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Local;

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    RBSYS_ExitCorelocalIntlockSysfast();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_nest_cnt);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidLockNesting);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                               (  ((expected_nest_cnt  & 0xFu) << 28)
                                | ((expected_lock_type & 0x3u) << 26)
                                | ((RBSYS_getCoreID()  & 0x3u) << 24)
                                | ( expected_lockaddr  & 0x00FFFFFFu)));
  }
}


/**
 * \Reference
 *  RBSYS_EnterCorelocalIntlockSysfast, RBSYS_ExitCorelocalIntlockSysfast, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Unbalanced nested fast core local lock (RBSYS_EnterCorelocalIntlockSysfast called twice without RBSYS_ExitCorelocalIntlockSysfast)
 *
 * \Sequence
 *  Call fast core local lock unbalanced (Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
 */
SWTEST void TRBSYS_PRC_LockMonitoring_FastCoreLocalLock_unbalanced_nested(void)
{
  uint32 expected_lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;
  uint32 expected_nest_cnt = 2;
  RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Local;

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    RBSYS_EnterCorelocalIntlockSysfast();
    RBSYS_EnterCorelocalIntlockSysfast();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_nest_cnt);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidLockNesting);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                               (  ((expected_nest_cnt  & 0xFu) << 28)
                                | ((expected_lock_type & 0x3u) << 26)
                                | ((RBSYS_getCoreID()  & 0x3u) << 24)
                                | ( expected_lockaddr  & 0x00FFFFFFu)));

    RBSYS_ExitCorelocalIntlockSysfast();
    RBSYS_ExitCorelocalIntlockSysfast();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCorelocalIntlockSysfast, RBSYS_ExitCorelocalIntlockSysfast, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Locktime is ignored in case of fast core local lock
 *
 * \Sequence
 *  Simulate max locktime between enter and exit of fast core local lock and call afterwards RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  No failure entry available
 */
SWTEST void TRBSYS_PRC_LockMonitoring_FastCoreLocalLock_ignore_locktime(void)
{
  uint32 locktime = RBSYS_MAX_LOCKTIME_US * RBSYS_TIMERTICKS_PER_US + 1;
  uint32 lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    TRBSYS_setRealtimeTickCtr(0);
    TRBSYS_setLinkPointer(lockaddr);
    RBSYS_EnterCorelocalIntlockSysfast();

    TRBSYS_setRealtimeTickCtr(locktime);
    RBSYS_ExitCorelocalIntlockSysfast();

    RBSYS_PRC_LockMonitoring();

    #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
      SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_locktime, 0);
      SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_lockadr, 0);
    #endif

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  }
}


/********************************/
/*        CORE LOCAL LOCK       */
/********************************/

/**
 * \Reference
 *  RBSYS_EnterCorelocalIntlock, RBSYS_ExitCorelocalIntlock, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Single balanced core local lock
 *
 * \Sequence
 *  Call core local lock balanced (Enter+Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  Interrupts must be masked via PMR (interrupt priority masking) register after function call of RBSYS_EnterCorelocalIntlockSysfast
 *  Interrupts must be released via PMR after function call of RBSYS_ExitCorelocalIntlockSysfast
 *  No failure entry available
 */
SWTEST void TRBSYS_PRC_LockMonitoring_CoreLocalLock_single_balanced(void)
{
  int i;
  unsigned int reg_val;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);
    RBSYS_LDSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID(), TRBSYS_PMRVAL_UNLOCKED);

    RBSYS_EnterCorelocalIntlock();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_ExitCorelocalIntlock();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_UNLOCKED);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCorelocalIntlock, RBSYS_ExitCorelocalIntlock, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Nested balanced core local lock
 *
 * \Sequence
 *  Call core local lock nested balanced (Enter+Enter+Exit+Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  No failure entry available
 *  Interupts must still be masked via PMR (interrupt priority masking) register as long as second function call of RBSYS_ExitCorelocalIntlock
 */
SWTEST void TRBSYS_PRC_LockMonitoring_CoreLocalLock_balanced_nested(void)
{
  int i;
  unsigned int reg_val;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);
    RBSYS_LDSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID(), TRBSYS_PMRVAL_UNLOCKED);

    RBSYS_EnterCorelocalIntlock();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_EnterCorelocalIntlock();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 2);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_ExitCorelocalIntlock();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_ExitCorelocalIntlock();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_UNLOCKED);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCorelocalIntlock, RBSYS_ExitCorelocalIntlock, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Unbalanced core local lock (only RBSYS_EnterCorelocalIntlock called)
 *
 * \Sequence
 *  Call core local lock unbalanced (Enter)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
 */
SWTEST void TRBSYS_PRC_LockMonitoring_CoreLocalLock_unbalanced_enter(void)
{
  uint32 expected_lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;
  uint32 expected_nest_cnt = 1;
  RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Local;

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    RBSYS_EnterCorelocalIntlock();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_nest_cnt);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidLockNesting);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                               (  ((expected_nest_cnt  & 0xFu) << 28)
                                | ((expected_lock_type & 0x3u) << 26)
                                | ((RBSYS_getCoreID()  & 0x3u) << 24)
                                | ( expected_lockaddr  & 0x00FFFFFFu)));

    RBSYS_ExitCorelocalIntlock();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCorelocalIntlock, RBSYS_ExitCorelocalIntlock, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Unbalanced core local lock (only RBSYS_ExitCorelocalIntlock called)
 *
 * \Sequence
 *  Call core local lock unbalanced (Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
 */
SWTEST void TRBSYS_PRC_LockMonitoring_CoreLocalLock_unbalanced_exit(void)
{
  uint32 expected_lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;
  uint32 expected_nest_cnt = -1;
  RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Local;

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    RBSYS_ExitCorelocalIntlock();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_nest_cnt);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidLockNesting);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                               (  ((expected_nest_cnt  & 0xFu) << 28)
                                | ((expected_lock_type & 0x3u) << 26)
                                | ((RBSYS_getCoreID()  & 0x3u) << 24)
                                | ( expected_lockaddr  & 0x00FFFFFFu)));
  }
}


/**
 * \Reference
 *  RBSYS_EnterCorelocalIntlock, RBSYS_ExitCorelocalIntlock, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Unbalanced nested core local lock (RBSYS_EnterCorelocalIntlock called twice without RBSYS_ExitCorelocalIntlock)
 *
 * \Sequence
 *  Call core local lock unbalanced (Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
 */
SWTEST void TRBSYS_PRC_LockMonitoring_CoreLocalLock_unbalanced_nested(void)
{
  uint32 expected_lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;
  uint32 expected_nest_cnt = 2;
  RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Local;

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    RBSYS_EnterCorelocalIntlock();
    RBSYS_EnterCorelocalIntlock();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_nest_cnt);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidLockNesting);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                               (  ((expected_nest_cnt  & 0xFu) << 28)
                                | ((expected_lock_type & 0x3u) << 26)
                                | ((RBSYS_getCoreID()  & 0x3u) << 24)
                                | ( expected_lockaddr  & 0x00FFFFFFu)));

    RBSYS_ExitCorelocalIntlock();
    RBSYS_ExitCorelocalIntlock();
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
  }
}


#if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
  /**
  * \Reference
  *  RBSYS_EnterCorelocalIntlock, RBSYS_ExitCorelocalIntlock, Gen_SWCS_HSW_uC_Base_SYS-219
  *
  * \Purpose
  *  Locktime is below allowed threshold
  *
  * \Sequence
  *  Simulate max allowed locktime between enter and exit of core local lock and call afterwards RBSYS_PRC_LockMonitoring
  *  => This shall be repeated for each available core
  *
  * \ExpectedResult
  *  No failure entry available
  */
  SWTEST void TRBSYS_PRC_LockMonitoring_CoreLocalLock_valid_locktime(void)
  {
    uint32 locktime = RBSYS_MAX_LOCKTIME_US * RBSYS_TIMERTICKS_PER_US;
    uint32 lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;

    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);

      TRBSYS_setRealtimeTickCtr(0);
      TRBSYS_setLinkPointer(lockaddr);
      RBSYS_EnterCorelocalIntlock();

      TRBSYS_setRealtimeTickCtr(locktime);
      RBSYS_ExitCorelocalIntlock();

      RBSYS_PRC_LockMonitoring();

      SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_locktime, locktime);
      SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_lockadr, lockaddr);

      SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
      SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
      SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    }
  }


  /**
  * \Reference
  *  RBSYS_EnterCorelocalIntlock, RBSYS_ExitCorelocalIntlock, Gen_SWCS_HSW_uC_Base_SYS-219
  *
  * \Purpose
  *  Locktime is across allowed threshold
  *
  * \Sequence
  *  Simulate max locktime across allowed threshold between enter and exit of core local lock and call afterwards RBSYS_PRC_LockMonitoring
  *  => This shall be repeated for each available core
  *
  * \ExpectedResult
  *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
  */
  SWTEST void TRBSYS_PRC_LockMonitoring_CoreLocalLock_too_long_locktime(void)
  {
    uint32 locktime = RBSYS_MAX_LOCKTIME_US * RBSYS_TIMERTICKS_PER_US + 1;
    uint32 lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;

    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);

      TRBSYS_setRealtimeTickCtr(0);
      TRBSYS_setLinkPointer(lockaddr);
      RBSYS_EnterCorelocalIntlock();

      TRBSYS_setRealtimeTickCtr(locktime);
      RBSYS_ExitCorelocalIntlock();

      RBSYS_PRC_LockMonitoring();

      SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_locktime, locktime);
      SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_lockadr, lockaddr);

      SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
      SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_LockTooLong);
      SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), lockaddr);
    }
  }
#endif


/********************************/
/*       FAST COMMON LOCK       */
/********************************/

/**
 * \Reference
 *  RBSYS_EnterCommonLockSysfast, RBSYS_ExitCommonLockSysfast, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Single balanced fast common lock
 *
 * \Sequence
 *  Call fast common lock balanced (Enter+Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  No failure entry available
 */
 SWTEST void TRBSYS_PRC_LockMonitoring_FastCommonLock_single_balanced(void)
{
  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 0);
      SWT_EvalEq(RBSYS_common_lock.lock, 0);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);

    RBSYS_EnterCommonLockSysfast();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 1);
      SWT_EvalEq(RBSYS_common_lock.lock, 1);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);

    RBSYS_ExitCommonLockSysfast();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 0);
      SWT_EvalEq(RBSYS_common_lock.lock, 0);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCommonLockSysfast, RBSYS_ExitCommonLockSysfast, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Nested balanced fast common lock
 *
 * \Sequence
 *  Call fast common lock nested balanced (Enter+Enter+Exit+Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  Lock must still be active till second function call of RBSYS_ExitCommonLockSysfast
 *  Interupts must still be masked via PMR (interrupt priority masking) register till second function call of RBSYS_ExitCommonLockSysfast
 *  No failure entry available
 */
SWTEST void TRBSYS_PRC_LockMonitoring_FastCommonLock_balanced_nested(void)
{
  int i;
  unsigned int reg_val;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);
    RBSYS_LDSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID(), TRBSYS_PMRVAL_UNLOCKED);

    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 0);
      SWT_EvalEq(RBSYS_common_lock.lock, 0);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);

    RBSYS_EnterCommonLockSysfast();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 1);
      SWT_EvalEq(RBSYS_common_lock.lock, 1);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_EnterCommonLockSysfast();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 2);
      SWT_EvalEq(RBSYS_common_lock.lock, 1);
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);
    #else
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 2);
    #endif
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_ExitCommonLockSysfast();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 1);
      SWT_EvalEq(RBSYS_common_lock.lock, 1);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_ExitCommonLockSysfast();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 0);
      SWT_EvalEq(RBSYS_common_lock.lock, 0);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_UNLOCKED);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCommonLockSysfast, RBSYS_ExitCommonLockSysfast, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Unbalanced fast common lock (only RBSYS_EnterCommonLockSysfast called)
 *
 * \Sequence
 *  Call fast common lock unbalanced (Enter)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
 */
SWTEST void TRBSYS_PRC_LockMonitoring_FastCommonLock_unbalanced_enter(void)
{
  uint32 expected_lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;
  uint32 expected_nest_cnt = 1;
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Common;
  #else
    RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Local;
  #endif

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    RBSYS_EnterCommonLockSysfast();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], expected_nest_cnt);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_nest_cnt);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidLockNesting);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                               (  ((expected_nest_cnt  & 0xFu) << 28)
                                | ((expected_lock_type & 0x3u) << 26)
                                | ((RBSYS_getCoreID()  & 0x3u) << 24)
                                | ( expected_lockaddr  & 0x00FFFFFFu)));

    RBSYS_ExitCommonLockSysfast();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 0);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCommonLockSysfast, RBSYS_ExitCommonLockSysfast, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Unbalanced fast common lock (only RBSYS_ExitCommonLockSysfast called)
 *
 * \Sequence
 *  Call fast common lock unbalanced (Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
 */
SWTEST void TRBSYS_PRC_LockMonitoring_FastCommonLock_unbalanced_exit(void)
{
  uint32 expected_lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;
  uint32 expected_nest_cnt = -1;
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Common;
  #else
    RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Local;
  #endif

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    RBSYS_ExitCommonLockSysfast();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], expected_nest_cnt);
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt,0);
    #else
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_nest_cnt);
    #endif


    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidLockNesting);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                               (  ((expected_nest_cnt  & 0xFu) << 28)
                                | ((expected_lock_type & 0x3u) << 26)
                                | ((RBSYS_getCoreID()  & 0x3u) << 24)
                                | ( expected_lockaddr  & 0x00FFFFFFu)));
  }
}



/**
 * \Reference
 *  RBSYS_EnterCommonLockSysfast, RBSYS_ExitCommonLockSysfast, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Unbalanced nested fast common lock (RBSYS_EnterCorelocalIntlockSysfast called twice without RBSYS_ExitCorelocalIntlockSysfast)
 *
 * \Sequence
 *  Call fast common lock unbalanced (Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
 */
SWTEST void TRBSYS_PRC_LockMonitoring_FastCommonLock_unbalanced_nested(void)
{
  uint32 expected_lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;
  uint32 expected_common_lock_nest_cnt = 2;
  uint32 expected_interrupt_lock_nest_cnt = 1;
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Common;
  #else
    RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Local;
  #endif

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    RBSYS_EnterCommonLockSysfast();
    RBSYS_EnterCommonLockSysfast();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], expected_common_lock_nest_cnt);
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_interrupt_lock_nest_cnt);
    #else
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_common_lock_nest_cnt);
    #endif


    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidLockNesting);

    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                             (  ((expected_common_lock_nest_cnt  & 0xFu) << 28)
                              | ((expected_lock_type & 0x3u) << 26)
                              | ((RBSYS_getCoreID()  & 0x3u) << 24)
                              | ( expected_lockaddr  & 0x00FFFFFFu)));
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], expected_common_lock_nest_cnt);
    #else
      SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                             (  ((expected_common_lock_nest_cnt  & 0xFu) << 28)
                              | ((expected_lock_type & 0x3u) << 26)
                              | ((RBSYS_getCoreID()  & 0x3u) << 24)
                              | ( expected_lockaddr  & 0x00FFFFFFu)));
    #endif

    RBSYS_ExitCommonLockSysfast();
    RBSYS_ExitCommonLockSysfast();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 0);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCommonLockSysfast, RBSYS_ExitCommonLockSysfast, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Locktime is ignored in case of fast common lock
 *
 * \Sequence
 *  Simulate max locktime between enter and exit of fast common lock and call afterwards RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  No failure entry available
 */
SWTEST void TRBSYS_PRC_LockMonitoring_FastCommonLock_ignore_locktime(void)
{
  uint32 locktime = RBSYS_MAX_LOCKTIME_US * RBSYS_TIMERTICKS_PER_US + 1;
  uint32 lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    TRBSYS_setRealtimeTickCtr(0);
    TRBSYS_setLinkPointer(lockaddr);
    RBSYS_EnterCommonLockSysfast();

    TRBSYS_setRealtimeTickCtr(locktime);
    RBSYS_ExitCommonLockSysfast();

    RBSYS_PRC_LockMonitoring();

    #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
      SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_locktime, 0);
      SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_lockadr, 0);
    #endif

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  }
}


/********************************/
/*          COMMON LOCK         */
/********************************/

/**
 * \Reference
 *  RBSYS_EnterCommonLock, RBSYS_ExitCommonLock, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Single balanced common lock
 *
 * \Sequence
 *  Call common lock balanced (Enter+Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  No failure entry available
 */
SWTEST void TRBSYS_PRC_LockMonitoring_CommonLock_single_balanced(void)
{
  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 0);
      SWT_EvalEq(RBSYS_common_lock.lock, 0);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);

    RBSYS_EnterCommonLock();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 1);
      SWT_EvalEq(RBSYS_common_lock.lock, 1);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);

    RBSYS_ExitCommonLock();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 0);
      SWT_EvalEq(RBSYS_common_lock.lock, 0);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCommonLock, RBSYS_ExitCommonLock, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Nested balanced common lock
 *
 * \Sequence
 *  Call common lock nested balanced (Enter+Enter+Exit+Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  Lock must still be active till second function call of RBSYS_ExitCommonLock
 *  Interupts must still be masked via PMR (interrupt priority masking) register till second function call of RBSYS_ExitCommonLock
 *  No failure entry available
 */
SWTEST void TRBSYS_PRC_LockMonitoring_CommonLock_balanced_nested(void)
{
  int i;
  unsigned int reg_val;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);
    RBSYS_LDSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID(), TRBSYS_PMRVAL_UNLOCKED);

    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 0);
      SWT_EvalEq(RBSYS_common_lock.lock, 0);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);

    RBSYS_EnterCommonLock();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 1);
      SWT_EvalEq(RBSYS_common_lock.lock, 1);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_EnterCommonLock();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 2);
      SWT_EvalEq(RBSYS_common_lock.lock, 1);
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);
    #else
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 2);
    #endif
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_ExitCommonLock();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 1);
      SWT_EvalEq(RBSYS_common_lock.lock, 1);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 1);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_LOCKED);

    RBSYS_ExitCommonLock();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 0);
      SWT_EvalEq(RBSYS_common_lock.lock, 0);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
    reg_val = RBSYS_STSR(TRBSYS_Get_PMR_REG_ID(), TRBSYS_Get_PMR_SEL_ID());
    SWT_EvalEqX(reg_val, TRBSYS_PMRVAL_UNLOCKED);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCommonLock, RBSYS_ExitCommonLock, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Unbalanced common lock (only RBSYS_EnterCommonLock called)
 *
 * \Sequence
 *  Call common lock unbalanced (Enter)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
 */
SWTEST void TRBSYS_PRC_LockMonitoring_CommonLock_unbalanced_enter(void)
{
  uint32 expected_lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;
  uint32 expected_nest_cnt = 1;
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Common;
  #else
    RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Local;
  #endif

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    RBSYS_EnterCommonLock();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], expected_nest_cnt);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_nest_cnt);

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidLockNesting);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                               (  ((expected_nest_cnt  & 0xFu) << 28)
                                | ((expected_lock_type & 0x3u) << 26)
                                | ((RBSYS_getCoreID()  & 0x3u) << 24)
                                | ( expected_lockaddr  & 0x00FFFFFFu)));

    RBSYS_ExitCommonLock();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 0);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCommonLock, RBSYS_ExitCommonLock, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Unbalanced common lock (only RBSYS_ExitCommonLock called)
 *
 * \Sequence
 *  Call common lock unbalanced (Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
 */
SWTEST void TRBSYS_PRC_LockMonitoring_CommonLock_unbalanced_exit(void)
{
  uint32 expected_lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;
  uint32 expected_nest_cnt = -1;
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Common;
  #else
    RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Local;
  #endif

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    RBSYS_ExitCommonLock();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], expected_nest_cnt);
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
    #else
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_nest_cnt);
    #endif

    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidLockNesting);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                               (  ((expected_nest_cnt  & 0xFu) << 28)
                                | ((expected_lock_type & 0x3u) << 26)
                                | ((RBSYS_getCoreID()  & 0x3u) << 24)
                                | ( expected_lockaddr  & 0x00FFFFFFu)));
  }
}



/**
 * \Reference
 *  RBSYS_EnterCommonLock, RBSYS_ExitCommonLock, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Unbalanced nested common lock (RBSYS_EnterCommonLock called twice without RBSYS_ExitCommonLock)
 *
 * \Sequence
 *  Call common lock unbalanced (Exit)
 *  Afterwards call process RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
 */
SWTEST void TRBSYS_PRC_LockMonitoring_CommonLock_unbalanced_nested(void)
{
  uint32 expected_lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;
  uint32 expected_common_lock_nest_cnt = 2;
  uint32 expected_interrupt_lock_nest_cnt = 1;
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Common;
  #else
    RBSYS_locktype_t expected_lock_type = RBSYS_LockType_Local;
  #endif

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    RBSYS_EnterCommonLock();
    RBSYS_EnterCommonLock();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], expected_common_lock_nest_cnt);
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_interrupt_lock_nest_cnt);
    #else
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, expected_common_lock_nest_cnt);
    #endif


    RBSYS_PRC_LockMonitoring();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidLockNesting);

    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                             (  ((expected_common_lock_nest_cnt  & 0xFu) << 28)
                              | ((expected_lock_type & 0x3u) << 26)
                              | ((RBSYS_getCoreID()  & 0x3u) << 24)
                              | ( expected_lockaddr  & 0x00FFFFFFu)));
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], expected_common_lock_nest_cnt);
    #else
      SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook),
                             (  ((expected_common_lock_nest_cnt  & 0xFu) << 28)
                              | ((expected_lock_type & 0x3u) << 26)
                              | ((RBSYS_getCoreID()  & 0x3u) << 24)
                              | ( expected_lockaddr  & 0x00FFFFFFu)));
    #endif

    RBSYS_ExitCommonLock();
    RBSYS_ExitCommonLock();
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      SWT_EvalEq(RBSYS_common_lock.core_cnt[RBSYS_getCoreID()], 0);
    #endif
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
  }
}


/**
 * \Reference
 *  RBSYS_EnterCommonLock, RBSYS_ExitCommonLock, Gen_SWCS_HSW_uC_Base_SYS-219
 *
 * \Purpose
 *  Locktime is below allowed threshold
 *
 * \Sequence
 *  Simulate max allowed locktime between enter and exit of common lock and call afterwards RBSYS_PRC_LockMonitoring
 *  => This shall be repeated for each available core
 *
 * \ExpectedResult
 *  No failure entry available
 */
SWTEST void TRBSYS_PRC_LockMonitoring_CommonLock_valid_locktime(void)
{
  uint32 locktime = RBSYS_MAX_LOCKTIME_US * RBSYS_TIMERTICKS_PER_US;
  uint32 lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;

  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    TRBSYS_setRealtimeTickCtr(0);
    TRBSYS_setLinkPointer(lockaddr);
    RBSYS_EnterCommonLock();

    TRBSYS_setRealtimeTickCtr(locktime);
    RBSYS_ExitCommonLock();

    RBSYS_PRC_LockMonitoring();

    #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
      SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_locktime, locktime);
      SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_lockadr, lockaddr);
    #endif

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  }
}


#if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
  /**
  * \Reference
  *  RBSYS_EnterCommonLock, RBSYS_ExitCommonLock, Gen_SWCS_HSW_uC_Base_SYS-219
  *
  * \Purpose
  *  Locktime is across allowed threshold
  *
  * \Sequence
  *  Simulate max locktime across allowed threshold between enter and exit of common lock and call afterwards RBSYS_PRC_LockMonitoring
  *  => This shall be repeated for each available core
  *
  * \ExpectedResult
  *  RBSYS_SYSErrorHook failure entry must be available with corresponding debug data
  */
  SWTEST void TRBSYS_PRC_LockMonitoring_CommonLock_too_long_locktime(void)
  {
    uint32 locktime = RBSYS_MAX_LOCKTIME_US * RBSYS_TIMERTICKS_PER_US + 1;
    uint32 lockaddr = (uint32)&RBSYS_PRC_LockMonitoring;

    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);

      TRBSYS_setRealtimeTickCtr(0);
      TRBSYS_setLinkPointer(lockaddr);
      RBSYS_EnterCommonLock();

      TRBSYS_setRealtimeTickCtr(locktime);
      RBSYS_ExitCommonLock();

      RBSYS_PRC_LockMonitoring();

      SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_locktime, locktime);
      SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_lockadr, lockaddr);

      SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
      SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_LockTooLong);
      SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), lockaddr);
    }
  }
#endif


#if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)
  /**
   * \Reference
   *  RBSYS_ResetLocIntsCounter, Gen_SWCS_HSW_uC_Base_SYS-219
   *
   * \Purpose
   *  Reset core local interrupt lock counter for killed TPSW application
   *
   * \Sequence
   *  1) Initialize interrupt lock counter to zero and call RBSYS_ResetLocIntsCounter
   *  2) Initialize interrupt lock counter unequal to zero and call RBSYS_ResetLocIntsCounter
   *  => This shall be repeated for each available core
   *
   * \ExpectedResult
   *  1+2) Interrupt lock counter must be cleared (set to zero)
   */
  SWTEST void TRBSYS_ResetLocIntsCounter(void)
  {
    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);

      RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt = 0;
      RBSYS_ResetLocIntsCounter(RBSYS_getCoreID());
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);

      RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt = 5;
      RBSYS_ResetLocIntsCounter(RBSYS_getCoreID());
      SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt, 0);
    }
  }


  /**
   * \Reference
   *  RBSYS_ResetNestLocCounter, Gen_SWCS_HSW_uC_Base_SYS-219
   *
   * \Purpose
   *  Reset lock counter for killed TPSW application
   *
   * \Sequence
   *  1) Initialize core-specific lock and lock counter to zero and call RBSYS_ResetNestLocCounter
   *  2) Initialize core-specific lock and lock counter unequal to zero and call RBSYS_ResetNestLocCounter
   *  => This shall be repeated for each available core
   *
   * \ExpectedResult
   *  1+2) Lock counter must be set to zero and lock must be released
   */
  SWTEST void TRBSYS_ResetNestLocCounter(void)
  {
    volatile lockstr_t TRBSYS_lock;
    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);

      TRBSYS_lock.core_cnt[RBSYS_getCoreID()] = 0;
      TRBSYS_lock.lock = 0;
      RBSYS_ResetNestLocCounter(&TRBSYS_lock, RBSYS_getCoreID());
      SWT_EvalEq(TRBSYS_lock.core_cnt[RBSYS_getCoreID()], 0);
      SWT_EvalEq(TRBSYS_lock.lock, 0);

      TRBSYS_lock.core_cnt[RBSYS_getCoreID()] = 5;
      TRBSYS_lock.lock = 1;
      RBSYS_ResetNestLocCounter(&TRBSYS_lock, RBSYS_getCoreID());
      SWT_EvalEq(TRBSYS_lock.core_cnt[RBSYS_getCoreID()], 0);
      SWT_EvalEq(TRBSYS_lock.lock, 0);
    }
  }
#endif


#if (RBFS_MCORE == RBFS_MCORE_ON)
  static unsigned int terminateLock[RB_NUM_CORES];
  static void TRBSYS_SYNCM_Check(void)
  {
    if (TRBSYS_Get_SYNCM_CNT() >= 10)
    {
      volatile lockstr_t* loc = &RBSYS_common_lock;

      unsigned int orgID = RBSYS_getCoreID();
      if (terminateLock[RBSYS_CORE_ID_0])
      {
        if (loc->core_cnt[RBSYS_CORE_ID_0] > 0)
        {
          TRBSYS_setCoreID(RBSYS_CORE_ID_0);
          RBSYS_ExitCommonLock();
        }
      }
      else if (terminateLock[RBSYS_CORE_ID_1])
      {
        if (loc->core_cnt[RBSYS_CORE_ID_1] > 0)
        {
          TRBSYS_setCoreID(RBSYS_CORE_ID_1);
          RBSYS_ExitCommonLock();
        }
      }
      TRBSYS_setCoreID(orgID);
    }
  }

  /**
   * \Reference
   *  RBSYS_EnterCommonLock, RBSYS_ExitCommonLock, Gen_SWCS_HSW_uC_Base_SYS-219
   *
   * \Purpose
   *  Enter/Exit Common Lock
   *
   * \Sequence
   *  Core0 will call the function RBSYS_EnterCommonLock to get the lock
   *  Afterwards core1 will also call the function RBSYS_EnterCommonLock
   *  Then core0 will release the common lock (this is stubbed within RBSYS_SYNCM while core1 is trying to get the lock)
   *
   * \ExpectedResult
   *  Core0 must get the lock
   *  After function call of RBSYS_ExitCommonLock by core0 (triggered via terminateLock), core1 must get the lock
   *  After function call of RBSYS_ExitCommonLock by core1, the common lock is released
   */
  SWTEST void TRBSYS_CommonLock(void)
  {
    int synchm_cnt1, synchm_cnt2, synchm_cnt3;
    TRBSYS_setCoreID(RBSYS_CORE_ID_0);
    TRBSYS_SYNCM_Callback = TRBSYS_SYNCM_Check;

    synchm_cnt1 = TRBSYS_Get_SYNCM_CNT();
    SWT_EvalEq(synchm_cnt1, 0);

    RBSYS_EnterCommonLock();

    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_CORE_ID_0]->suspend_cnt, 1);
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_CORE_ID_1]->suspend_cnt, 0);
    SWT_EvalEq(RBSYS_common_lock.lock, 1);

    synchm_cnt2 = TRBSYS_Get_SYNCM_CNT();
    SWT_EvalGT(synchm_cnt2, synchm_cnt1);  // RBSYS_LDL_W & RBSYS_STC_W functions will return "successful" only after second call

    terminateLock[RBSYS_CORE_ID_0] = 1;
    TRBSYS_setCoreID(RBSYS_CORE_ID_1);
    RBSYS_EnterCommonLock();

    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_CORE_ID_0]->suspend_cnt, 0);
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_CORE_ID_1]->suspend_cnt, 1);
    SWT_EvalEq(RBSYS_common_lock.lock, 1);

    synchm_cnt3 = TRBSYS_Get_SYNCM_CNT();
    SWT_EvalGT(synchm_cnt3, synchm_cnt2);

    RBSYS_ExitCommonLock();

    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_CORE_ID_0]->suspend_cnt, 0);
    SWT_EvalEq(RBSYS_coreintlockinfo[RBSYS_CORE_ID_1]->suspend_cnt, 0);
    SWT_EvalEq(RBSYS_common_lock.lock, 0);
  }
#endif


#if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
/**
 * \Reference
 *  RBSYS_EnterCommonLock, RBSYS_ExitCommonLock, Gen_SWCS_HSW_uC_Base_SYS-220
 *
 * \Purpose
 *  Measure and monitor longest locktime
 *
 * \Sequence
 *  Call for each available core
 *    - RBSYS_EnterCommonLock/RBSYS_ExitCommonLock with locktime
 *    - RBSYS_EnterCommonLock/RBSYS_ExitCommonLock with locktime longer thene 1st time
 *    - RBSYS_EnterCommonLock/RBSYS_ExitCommonLock with locktime shorter then 1st time
 *    - clear address and time via RBSYS_PRC_ResetMaxLockTime_Init
 *
 * \ExpectedResult
 *  Corresponding address and locktime of the longest lock must be stored (=> 2nd)
 */
SWTEST void TRBSYS_MeasureLongestLockTime(void)
{
  uint32 locktime1 = 20 * RBSYS_TIMERTICKS_PER_US;
  uint32 locktime2 = locktime1 + 1;
  uint32 locktime3 = locktime1 - 1;
  uint32 lockaddr1 = (uint32)&locktime1;
  uint32 lockaddr2 = (uint32)&locktime2;
  uint32 lockaddr3 = (uint32)&locktime3;

  unsigned int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    TRBSYS_setRealtimeTickCtr(0);
    TRBSYS_setLinkPointer(lockaddr1);
    RBSYS_EnterCommonLock();
    TRBSYS_setRealtimeTickCtr(locktime1);
    RBSYS_ExitCommonLock();

    TRBSYS_setRealtimeTickCtr(0);
    TRBSYS_setLinkPointer(lockaddr2);
    RBSYS_EnterCommonLock();
    TRBSYS_setRealtimeTickCtr(locktime2);
    RBSYS_ExitCommonLock();

    TRBSYS_setRealtimeTickCtr(0);
    TRBSYS_setLinkPointer(lockaddr3);
    RBSYS_EnterCommonLock();
    TRBSYS_setRealtimeTickCtr(locktime3);
    RBSYS_ExitCommonLock();

    SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_lockadr, lockaddr2);
    SWT_EvalEq(RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_locktime, locktime2);

    // clear all entries
    RBSYS_PRC_ResetMaxLockTime_Init();
  }
}

/**
 * \Reference
 *  RBSYS_PRC_ResetMaxLockTime_Init, Gen_SWCS_HSW_uC_Base_SYS-220
 *
 * \Purpose
 *  After finishing init task, maximum lock count must be cleared before cyclic task execution
 *
 * \Sequence
 *  Initialize lock time and corresponding lock address for each core with a value unequal to zero
 *  Call function RBSYS_PRC_ResetMaxLockTime_Init
 *
 * \ExpectedResult
 * Lock time and corresponding lock address for each core must be set to zero
 */
SWTEST void TRBSYS_PRC_ResetMaxLockTime_Init(void)
{
  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    RBSYS_lockstatsinfo[i]->max_lockadr = 0x1;
    RBSYS_lockstatsinfo[i]->max_locktime = 0x2;
    RBSYS_lockstatsinfo[i]->tmp_lockadr =  0x3;
    RBSYS_lockstatsinfo[i]->tmp_locktime =  0x4;
  }

  RBSYS_PRC_ResetMaxLockTime_Init();

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    SWT_EvalEq(RBSYS_lockstatsinfo[i]->max_lockadr, 0);
    SWT_EvalEq(RBSYS_lockstatsinfo[i]->max_locktime, 0);
    SWT_EvalEq(RBSYS_lockstatsinfo[i]->tmp_lockadr, 0);
    SWT_EvalEq(RBSYS_lockstatsinfo[i]->tmp_locktime, 0);
  }
}
#endif



#else //( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
/**
    * \TestCaseName TRBSYS_Dummy
    *
    * \Reference
    * Dummy
    *
    *
    * \Purpose Dummy testcase for missing Stellar Unittests. To be removed once there are Stellar implementations.
    *
    * \Sequence
    *
    *
    * \ExpectedResult
    *
    */
  SWTEST void TRBSYS_Dummy(void)
  {
      SWT_EvalEx(TRUE, "Feature is not supported for Series yet.");
  }
#endif
