#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                      // for RBFS_SysMaxTaskx1Jitter

#include "RBSYS_SystemTimer.h"
#include "TRBSYS_SystemTimer.h"
#include "RBSYS_TaskInfo.h"
#include "RBSYS_Subsystem.h"

#include "RBHSWDEM_Facade.h"
#include "DemStub_Helper.h"


/* realized interfaces */
#include "TRBSYS_TaskJitter_Adaptor.h"



#if (  (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_5)  \
    || (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_15) \
    )

  static boolean TRBSYS_isPassed(Dem_EventIdType EventId)
  {
    return DemStub_isTested(EventId) && !DemStub_isFailed(EventId);
  }

  /**
   * \Reference
   *  RBSYS_TaskJitter, Gen_SWCS_HSW_uC_Base_SYS-218
   *
   * \Purpose
   *  Good check of x1 task jitter monitoring
   *
   * \Sequence
   *  Call process RBSYS_PRC_JitterMonitoring_x1
   *  Hint: Good check in first task run after reset: jitter is calibrated and ok by definition
   *
   * \ExpectedResult
   *  Initial good check report of corresponding failure word "RBSYS_TaskJitter"
   */
  SWTEST void TRBSYS_JitterMonitoring_GoodCheck(void)
  {
    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);
  }


  /**
   * \Reference
   *  RBSYS_TaskJitter, Gen_SWCS_HSW_uC_Base_SYS-218
   *
   * \Purpose
   *  No x1 task jitter
   *
   * \Sequence
   *  Set initial sync time
   *  Call process RBSYS_PRC_JitterMonitoring_x1 first time
   *  Increment sync time by exactly one ideal x1 task cycle (=> 0% jitter)
   *  Call process RBSYS_PRC_JitterMonitoring_x1 second time
   *
   * \ExpectedResult
   *  Initial good check report of corresponding failure word "RBSYS_TaskJitter" after first process call
   *  Initial good check report of corresponding failure word "RBSYS_TaskJitter" still valid after second process call
   *  Last jitter of x1 task needs to be zero
   */
  SWTEST void TRBSYS_JitterMonitoring_NoJitter(void)
  {
    sint32 current_time = 10000;
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);

    current_time += TIMERTICKS_PER_TASK_X1;
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(GetPrivate_RBSYS_JitterInfoTask_x1_s32(), 0);
    SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);
  }


  /**
   * \Reference
   *  RBSYS_TaskJitter, Gen_SWCS_HSW_uC_Base_SYS-218
   *
   * \Purpose
   *  Maximum allowed negative x1 task jitter
   *
   * \Sequence
   *  Set initial sync time
   *  Call process RBSYS_PRC_JitterMonitoring_x1 first time
   *  Increment sync time by maximum allowed negative jitter limit
   *  Call process RBSYS_PRC_JitterMonitoring_x1 second time
   *
   * \ExpectedResult
   *  Initial good check report of corresponding failure word "RBSYS_TaskJitter" after first process call
   *  Initial good check report of corresponding failure word "RBSYS_TaskJitter" still valid after second process call
   *  Last jitter of x1 task needs to be the negative limit
   */
  SWTEST void TRBSYS_JitterMonitoring_MaxNegativeJitter(void)
  {
    sint32 current_time = 10000;
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);

    current_time += (TIMERTICKS_PER_TASK_X1 - JITTER_LIMIT_TASK_X1);
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(GetPrivate_RBSYS_JitterInfoTask_x1_s32(), -JITTER_LIMIT_TASK_X1);
    SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);
  }


  /**
   * \Reference
   *  RBSYS_TaskJitter, Gen_SWCS_HSW_uC_Base_SYS-218
   *
   * \Purpose
   *  Maximum allowed positive x1 task jitter
   *
   * \Sequence
   *  Set initial sync time
   *  Call process RBSYS_PRC_JitterMonitoring_x1 first time
   *  Increment sync time by maximum allowed positive jitter limit
   *  Call process RBSYS_PRC_JitterMonitoring_x1 second time
   *
   * \ExpectedResult
   *  Initial good check report of corresponding failure word "RBSYS_TaskJitter" after first process call
   *  Initial good check report of corresponding failure word "RBSYS_TaskJitter" still valid after second process call
   *  Last jitter of x1 task needs to be the positive limit
   */
  SWTEST void TRBSYS_JitterMonitoring_MaxPositiveJitter(void)
  {
    sint32 current_time = 10000;
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);

    current_time += (TIMERTICKS_PER_TASK_X1 + JITTER_LIMIT_TASK_X1);
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(GetPrivate_RBSYS_JitterInfoTask_x1_s32(), JITTER_LIMIT_TASK_X1);
    SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);
  }


  /**
   * \Reference
   *  RBSYS_TaskJitter, Gen_SWCS_HSW_uC_Base_SYS-218
   *
   * \Purpose
   *  Too high negative x1 task jitter
   *
   * \Sequence
   *  Set initial sync time
   *  Call process RBSYS_PRC_JitterMonitoring_x1 first time
   *  Increment sync time by not allowed negative jitter (=> max allowed limit - 1)
   *  Call process RBSYS_PRC_JitterMonitoring_x1 second time
   *
   * \ExpectedResult
   *  Initial good check report of corresponding failure word "RBSYS_TaskJitter" after first process call
   *  To high negative jitter must lead to corresponding failure word "RBSYS_TaskJitter" after second process call with corresponding debug data
   *  Last jitter of x1 task needs to be the not allowed negative jitter
   */
  SWTEST void TRBSYS_JitterMonitoring_NegativeJitterToHigh(void)
  {
    sint32 current_time = 10000;
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);

    current_time = current_time + TIMERTICKS_PER_TASK_X1 - JITTER_LIMIT_TASK_X1 - 1;
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(GetPrivate_RBSYS_JitterInfoTask_x1_s32(), (-JITTER_LIMIT_TASK_X1 - 1));
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskJitter), TIMERTICKS_PER_TASK_X1);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskJitter), (-JITTER_LIMIT_TASK_X1 - 1));
  }


  /**
   * \Reference
   *  RBSYS_TaskJitter, Gen_SWCS_HSW_uC_Base_SYS-218
   *
   * \Purpose
   *  Too high positive x1 task jitter
   *
   * \Sequence
   *  Set initial sync time
   *  Call process RBSYS_PRC_JitterMonitoring_x1 first time
   *  Increment sync time by not allowed positive jitter (=> max allowed limit + 1)
   *  Call process RBSYS_PRC_JitterMonitoring_x1 second time
   *
   * \ExpectedResult
   *  Initial good check report of corresponding failure word "RBSYS_TaskJitter" after first process call
   *  To high positve jitter must lead to corresponding failure word "RBSYS_TaskJitter" after second process call with corresponding debug data
   *  Last jitter of x1 task needs to be the not allowed positive jitter
   */
  SWTEST void TRBSYS_JitterMonitoring_PositiveJitterToHigh(void)
  {
    sint32 current_time = 10000;
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);

    current_time += (TIMERTICKS_PER_TASK_X1 + JITTER_LIMIT_TASK_X1 + 1);
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(GetPrivate_RBSYS_JitterInfoTask_x1_s32(), (JITTER_LIMIT_TASK_X1 + 1));
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskJitter), TIMERTICKS_PER_TASK_X1);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskJitter), (JITTER_LIMIT_TASK_X1 + 1));
  }

#else
  /**
   * \Reference
   *  RBSYS_TaskJitter, Gen_SWCS_HSW_uC_Base_SYS-218
   *
   * \Purpose
   *  No x1 task jitter
   *
   * \Sequence
   *  Set initial sync time
   *  Call process RBSYS_PRC_JitterMonitoring_x1 first time
   *  Increment sync time by exactly one ideal x1 task cycle (=> 0% jitter)
   *  Call process RBSYS_PRC_JitterMonitoring_x1 second time
   *
   * \ExpectedResult
   *  Last jitter of x1 task needs to be zero
   */
  SWTEST void TRBSYS_JitterMonitoring_NoJitter(void)
  {
    sint32 current_time = 10000;
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    current_time += TIMERTICKS_PER_TASK_X1;
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(GetPrivate_RBSYS_JitterInfoTask_x1_s32(), 0);
  }


  /**
   * \Reference
   *  RBSYS_TaskJitter, Gen_SWCS_HSW_uC_Base_SYS-218
   *
   * \Purpose
   *  Positive x1 task jitter
   *
   * \Sequence
   *  Set initial sync time
   *  Call process RBSYS_PRC_JitterMonitoring_x1 first time
   *  Increment sync time by positive jitter
   *  Call process RBSYS_PRC_JitterMonitoring_x1 second time
   *
   * \ExpectedResult
   *  Last jitter of x1 task needs to be the positive jitter
   */
  SWTEST void TRBSYS_JitterMonitoring_PositiveJitter(void)
  {
    sint32 current_time = 10000;
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    current_time += TIMERTICKS_PER_TASK_X1;
    current_time += 2;

    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(GetPrivate_RBSYS_JitterInfoTask_x1_s32(), 2);
  }


  /**
   * \Reference
   *  RBSYS_TaskJitter, Gen_SWCS_HSW_uC_Base_SYS-218
   *
   * \Purpose
   *  Negative x1 task jitter
   *
   * \Sequence
   *  Set initial sync time
   *  Call process RBSYS_PRC_JitterMonitoring_x1 first time
   *  Increment sync time by negative jitter
   *  Call process RBSYS_PRC_JitterMonitoring_x1 second time
   *
   * \ExpectedResult
   *  Last jitter of x1 task needs to be the negative jitter
   */
  SWTEST void TRBSYS_JitterMonitoring_NegativeJitter(void)
  {
    sint32 current_time = 10000;
    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    current_time += TIMERTICKS_PER_TASK_X1;
    current_time -= 2;

    TRBSYS_setSynctimeTickCtr(current_time);

    RBSYS_PRC_JitterMonitoring_x1();

    SWT_EvalEq(GetPrivate_RBSYS_JitterInfoTask_x1_s32(), -2);
  }

#endif