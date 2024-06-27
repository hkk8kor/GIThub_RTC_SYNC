#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                       ///< for RBFS_MCORE

#include "TRBSYS_uCRegisters.h"


#include "RBSYS_Idle.h"
#include "TRBSYS_Idle_Adaptor.h"
#include "TRBSYS_Intrinsics.h"
#include "RBSYS_CpuInfo.h"
#include "TRBSYS_CpuInfo.h"
#include "RBSYS_SystemTimer.h"
#include "TRBSYS_SystemTimer.h"
#include "TRBSYS_TestInjection.h"


/**
 * \Reference
 *  sys_general_idleloop, Gen_SWCS_HSW_uC_Base_SYS-266
 *
 * \Purpose
 *  Verify single idle loop on Core0
 *
 * \Sequence
 *  Call function sys_general_idleloop with RBSYS_CORE_ID_0
 *
 * \ExpectedResult
 *  Core-specific idle loop counter is incremented by one
 *  Snooze is called at least once to slow-down a bit the idle loop to avoid bus congestion on MCORE
 */
SWTEST void TRBSYS_idleloop_core0(void)
{
  sys_general_idleloop(RBSYS_CORE_ID_0);

  SWT_EvalEq(GetPrivate_idle_cnt_core0(), 1);
  SWT_EvalGE(TRBSYS_GetSnoozeLoopCounter(), 1);
}


#if (RBFS_MCORE == RBFS_MCORE_ON)
  /**
   * \Reference
   *  sys_general_idleloop, Gen_SWCS_HSW_uC_Base_SYS-266
   *
   * \Purpose
   *  Verify single idle loop on Core1
   *
   * \Sequence
   *  Call function sys_general_idleloop with RBSYS_CORE_ID_1
   *
   * \ExpectedResult
   *  Core-specific idle loop counter is incremented by one
   *  Snooze is called at least once to slow-down a bit the idle loop to avoid bus congestion on MCORE
   */
  SWTEST void TRBSYS_idleloop_core1(void)
  {
    sys_general_idleloop(RBSYS_CORE_ID_1);

    SWT_EvalEq(GetPrivate_idle_cnt_core1(), 1);
    SWT_EvalGE(TRBSYS_GetSnoozeLoopCounter(), 1);
  }
#endif


/**
 * \Reference
 *  sys_idleloop_request_rerun, Gen_SWCS_HSW_uC_Base_SYS-266
 *
 * \Purpose
 *  Verify request for immediate rerun of idle loop on Core0
 *
 * \Sequence
 *  Call function sys_idleloop_request_rerun on Core0
 *
 * \ExpectedResult
 *  Core-specific idle loop rerun counter is incremented by one
 */
SWTEST void TRBSYS_idleloop_request_rerun_core0(void)
{
  TRBSYS_setCoreID(RBSYS_CORE_ID_0);

  sys_idleloop_request_rerun();

  SWT_EvalEq(GetPrivate_idleloop_immediate_rerun_core0(), 1);
}


#if (RBFS_MCORE == RBFS_MCORE_ON)
  /**
   * \Reference
   *  sys_idleloop_request_rerun, Gen_SWCS_HSW_uC_Base_SYS-266
   *
   * \Purpose
   *  Verify request for immediate rerun of idle loop on Core1
   *
   * \Sequence
   *  Call function sys_idleloop_request_rerun on Core1
   *
   * \ExpectedResult
   *  Core-specific idle loop rerun counter is incremented by one
   */
  SWTEST void TRBSYS_idleloop_request_rerun_core1(void)
  {
    TRBSYS_setCoreID(RBSYS_CORE_ID_1);

    sys_idleloop_request_rerun();

    SWT_EvalEq(GetPrivate_idleloop_immediate_rerun_core1(), 1);
  }
#endif


/**
 * \Reference
 *  sys_delayed_idleloop, Gen_SWCS_HSW_uC_Base_SYS-266
 *
 * \Purpose
 *  Verify immediate reexecution inside sys_delayed_idleloop on Core0
 *
 * \Sequence
 *  Call function sys_idleloop_request_rerun on Core0
 *  Call function sys_delayed_idleloop on Core0
 *
 * \ExpectedResult
 *  Core-specific idle loop rerun counter is incremented by one after sys_idleloop_request_rerun
 *  Core-specific idle loop rerun counter is decremented to zero after sys_delayed_idleloop
 */
SWTEST void TRBSYS_sys_delayed_idleloop_rerun_core0(void)
{
  TRBSYS_setCoreID(RBSYS_CORE_ID_0);
  sys_idleloop_request_rerun();
  SWT_EvalEq(GetPrivate_idleloop_immediate_rerun_core0(), 1);

  sys_delayed_idleloop(RBSYS_CORE_ID_0);
  SWT_EvalEq(GetPrivate_idleloop_immediate_rerun_core0(), 0);
}


#if (RBFS_MCORE == RBFS_MCORE_ON)
  /**
   * \Reference
   *  sys_delayed_idleloop, Gen_SWCS_HSW_uC_Base_SYS-266
   *
   * \Purpose
   *  Verify immediate reexecution inside sys_delayed_idleloop on Core1
   *
   * \Sequence
   *  Call function sys_idleloop_request_rerun on Core1
   *  Call function sys_delayed_idleloop on Core1
   *
   * \ExpectedResult
   *  Core-specific idle loop rerun counter is incremented by one after sys_idleloop_request_rerun
   *  Core-specific idle loop rerun counter is decremented to zero after sys_delayed_idleloop
   */
  SWTEST void TRBSYS_sys_delayed_idleloop_rerun_core1(void)
  {
    TRBSYS_setCoreID(RBSYS_CORE_ID_1);
    sys_idleloop_request_rerun();
    SWT_EvalEq(GetPrivate_idleloop_immediate_rerun_core1(), 1);

    sys_delayed_idleloop(RBSYS_CORE_ID_1);
    SWT_EvalEq(GetPrivate_idleloop_immediate_rerun_core1(), 0);
  }
#endif


/**
 * \Reference
 *  sys_delayed_idleloop, Gen_SWCS_HSW_uC_Base_SYS-266
 *
 * \Purpose
 *  Verify delayed reexecution inside sys_delayed_idleloop on Core0
 *
 * \Sequence
 *  Call function sys_delayed_idleloop that while loop is not executed (done via faked timer)
 *
 * \ExpectedResult
 *  Snooze inside while loop is not executed
 */
SWTEST void TRBSYS_sys_delayed_idleloop_core0(void)
{
  TRBSYS_TicksForPreempt = RBSYS_convertUsecToTimerTicks(GetPrivate_IDLE_LOOP_DELAY_US()) + 1;

  sys_delayed_idleloop(RBSYS_CORE_ID_0);

  SWT_EvalEq(TRBSYS_GetSnoozeLoopCounter(), 0);
}

/**
 * \Reference
 *  sys_delayed_idleloop, Gen_SWCS_HSW_uC_Base_SYS-266
 *
 * \Purpose
 *  Verify delayed reexecution inside sys_delayed_idleloop on Core0
 *
 * \Sequence
 *  Call function sys_delayed_idleloop that while loop is executed (done via faked timer)
 *
 * \ExpectedResult
 *  Snooze is called twice per while loop
 */
SWTEST void TRBSYS_sys_delayed_idleloop1_core0(void)
{

  TRBSYS_TicksForPreempt = RBSYS_convertUsecToTimerTicks(GetPrivate_IDLE_LOOP_DELAY_US() - 1); // 1us left to run in idle loop
  TRBSYS_TicksPerLoop = 10; // 10 ticks per loop, 80 ticks per us => 8 loops + 1 loop until condition is met

  sys_delayed_idleloop(RBSYS_CORE_ID_0);

  SWT_EvalEq(TRBSYS_GetSnoozeCounter(), ((RBSYS_TIMERTICKS_PER_US / TRBSYS_TicksPerLoop) + 1)); // 1x RBSYS_Snooze per while-loop
}


#if (RBFS_MCORE == RBFS_MCORE_ON)
  /**
   * \Reference
   *  sys_delayed_idleloop, Gen_SWCS_HSW_uC_Base_SYS-266
   *
   * \Purpose
   *  Verify delayed reexecution inside sys_delayed_idleloop on Core1
   *
   * \Sequence
   *  Call function sys_delayed_idleloop that while loop is not executed (done via faked timer)
   *
   * \ExpectedResult
   *  Snooze inside while loop is not executed
   */
  SWTEST void TRBSYS_sys_delayed_idleloop_core1(void)
  {
    TRBSYS_TicksForPreempt = RBSYS_convertUsecToTimerTicks(GetPrivate_IDLE_LOOP_DELAY_US()) + 1;

    sys_delayed_idleloop(RBSYS_CORE_ID_1);

    SWT_EvalEq(TRBSYS_GetSnoozeLoopCounter(), 0);
  }


  /**
   * \Reference
   *  sys_delayed_idleloop, Gen_SWCS_HSW_uC_Base_SYS-266
   *
   * \Purpose
   *  Verify delayed reexecution inside sys_delayed_idleloop on Core1
   *
   * \Sequence
   *  Call function sys_delayed_idleloop that while loop is executed (done via faked timer)
   *
   * \ExpectedResult
   *  Snooze is called twice per while loop
   */
  SWTEST void TRBSYS_sys_delayed_idleloop1_core1(void)
  {
    TRBSYS_TicksForPreempt = RBSYS_convertUsecToTimerTicks(GetPrivate_IDLE_LOOP_DELAY_US() - 1); // 1us left to run in idle loop
    TRBSYS_TicksPerLoop = 10; // 10 ticks per loop, 80 ticks per us => 8 loops + 1 loop until condition is met

    sys_delayed_idleloop(RBSYS_CORE_ID_1);

    SWT_EvalEq(TRBSYS_GetSnoozeCounter(), ((RBSYS_TIMERTICKS_PER_US / TRBSYS_TicksPerLoop) + 1));   // 1x RBSYS_Snooze per while-loop
  }
#endif
