
#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                      // for RBFS_TPSWCapsule
#include "RBSYS_uCRegisters.h"                    // peripheral labels
#include "RBSYS_SystemTimer.h"
#include "TRBSYS_SystemTimer.h"
#include "RBSYS_TimerSetup.h"
#include "TRBSYS_Intrinsics.h"
#include "TRBSYS_CpuInfo.h"
#include "RBSYS_CpuInfo.h"

#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )

/**
 * \Reference
 * RBSYS_InitTimers, Gen_SWCS_HSW_uC_Base_SYS-248
 *
 * \Purpose
 * Verify correct initialization of System Timer
 *
 * \Sequence
 * Call function RBSYS_InitTimers()
 *
 * \ExpectedResult
 * P1x:
 * - Setup Timers only on Core 0
 * - STM0 timer counter channel 1 and channel 2 must be stopped
 * - Peripheral clock must be configured as input clock for counter channels 0..3
 * - Counter values for channel 1 and 2 must be reset
 * - Following interrupt configuration must be configured:
 *       STM interrupt 4 to STM0CMP1A
 *       STM interrupt 5 to STM0CMP1B
 *       STM interrupt 0 to STM0CMP2A
 *       STM interrupt 1 to STM0CMP2B
 * - Reset mask shall be disabled for all channels
 * - Status register must be cleared
 * - STM0 timer counter channel 1 and channel 2 must be started at the end
 * U2A:
 * - Setup Timers only on Core 0
 * - TPTM0 timer counter channel 0 and channel 1 must be stopped
 * - Clock divider must be configured such that the resulting clock frequency is 80MHz
 * - Interrupts for TPTM0 channel 0 compare 0 and 1 are enabled (if SC4 is configured, also TPTM0 channel 1 compare 2 and 3 are enabled)
 * - TPTM0 timer counter channel 0 and channel 1 must be started at the end
 */
SWTEST void TRBSYS_InitTimers(void)
{
  #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)||(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    TPTMPE0TPTM0USTR = 0x3; // timers are running
  #endif

  #if( RBFS_MCORE == RBFS_MCORE_ON )
    /* Single Core variants will always consider CORE_ID_0 */
    TRBSYS_setCoreID(RBSYS_CORE_ID_0 + 1);

    RBSYS_InitTimers();

    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)

      SWT_EvalEq(STM0TT, 0x0);
      SWT_EvalEq(STM0CKSEL, 0x0);
      SWT_EvalEq(STM0CNT1, 0x0);
      SWT_EvalEq(STM0CNT2, 0x0);
      SWT_EvalEq(STM0IS, 0x0 );
      SWT_EvalEq(STM0RM, 0x0);
      SWT_EvalEq(STM0STC, 0x0);
      SWT_EvalEq(STM0TS, 0x0);

    #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)||(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))

      SWT_EvalEq(TPTMPE0TPTM0USTP, 0x0);
      SWT_EvalEq(TPTMPE0TPTM0UDIV, 0x0);
      SWT_EvalEq(TPTMPE0TPTM0UIEN, 0x0);
      SWT_EvalEq(TPTMPE0TPTM0URUN, 0x0);

    #endif
  #endif

  TRBSYS_setCoreID(RBSYS_CORE_ID_0);

  RBSYS_InitTimers();

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)

    SWT_EvalEq(STM0TT, 0x6);
    SWT_EvalEq(STM0CKSEL, 0x0);
    SWT_EvalEq(STM0CNT1, 0x0);
    SWT_EvalEq(STM0CNT2, 0x0);
    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
      #if (RBFS_MCORE == RBFS_MCORE_ON)
        SWT_EvalEq(STM0IS, (1<<0) | (1<<2) | (0<<8) | (0<<10) );
      #else
        SWT_EvalEq(STM0IS, (1<<0) | (0<<8) | (0<<10) );
      #endif
    #else
      SWT_EvalEq(STM0IS, (0<<8) | (0<<10) );
    #endif
    SWT_EvalEq(STM0RM, 0x0);
    SWT_EvalEq(STM0STC, 0xFFFFF);
    SWT_EvalEq(STM0TS, 0x6);

  #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)||(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))

    SWT_EvalEq(TPTMPE0TPTM0USTP, 0x3); // timers were stopped for configuration
    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      SWT_EvalEq(TPTMPE0TPTM0UDIV, 0x4); // 400MHz / (4 + 1) = 80MHz
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      SWT_EvalEq(TPTMPE0TPTM0UDIV, 0x3); // 320MHz / (3 + 1) = 80MHz
    #endif
    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
      SWT_EvalEq(TPTMPE0TPTM0UIEN, (0x3u << 10) | (0x3u << 0));
    #else
      SWT_EvalEq(TPTMPE0TPTM0UIEN, 0x3);
    #endif
    SWT_EvalEq(TPTMPE0TPTM0URUN, 0x3);

  #endif
}

#if ( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TriggerTimerSupport == RBFS_TriggerTimerSupport_On) )
/**
 * \Reference
 * RBSYS_StartTriggerTimer, Gen_SWCS_HSW_uC_Base_SYS-173
 *
 * \Purpose
 * Verify function RBSYS_StartTriggerTimer which is required to start a defined timer with compare
 *
 * \Sequence
 * Initialize used STM counter value
 * Call function RBSYS_StartTriggerTimer with a corresponding timer time
 *
 * \ExpectedResult
 * counter value is zeroed
 * compares are setup correctly
 * other necessary settings are done correctly
 */
SWTEST void TRBSYS_StartTriggerTimer(void)
{
  STM0CNT0L = 0xDEADBEEF;
  STM0CNT0H = 0xDEADBEEF;

  RBSYS_StartTriggerTimer(900 /*us*/);

  SWT_EvalEq(STM0CNT0L, 0);
  SWT_EvalEq(STM0CNT0H, 0);

  SWT_EvalEq(STM0CMP0AL, 900*RBSYS_TIMERTICKS_PER_US);
  SWT_EvalEq(STM0CMP0AH, 0);

  SWT_EvalEq(STM0STC, 0x10001);
  SWT_EvalEq(STM0TS, 0x1);
}

/**
 * \Reference
 * RBSYS_StopTriggerTimer, Gen_SWCS_HSW_uC_Base_SYS-173
 *
 * \Purpose
 * Verify function RBSYS_StopTriggerTimer which is required to stop a (potentially) running Trigger Timer
 *
 * \Sequence
 * Call function RBSYS_StopTriggerTimer
 *
 * \ExpectedResult
 * Stop bit shall be set
 */
SWTEST void TRBSYS_StopTriggerTimer(void)
{
  RBSYS_StopTriggerTimer();

  SWT_EvalEq(STM0TT, 0x1);
}
#endif

/**
 * \Reference
 * RBSYS_waitUsecLoop, Gen_SWCS_HSW_uC_Base_SYS-173
 * Gen_SWFS_0979_HSW_OverallRequirements_3677
 *
 * \Purpose
 * Verify the function which is required to wait a defined time in usec
 *
 * \Sequence
 * Initialize used STM counter value
 * Call function RBSYS_waitUsecLoop with a corresponding wait time
 *
 * \ExpectedResult
 * STM counter value after wait time must be equal than initial value + wait time
 * + one additional wait loop (required due to evaluation of "less than" within RBSYS_waitUsecLoop)
 */
SWTEST void TRBSYS_waitUsecLoop(void)
{
  uint8 snooze_loops = 10;
  uint16 wait_time_in_usec = (snooze_loops * TRBSYS_SNOOZE_LOOP_TICKS) / RBSYS_TIMERTICKS_PER_US;
  uint32 start_timer_ticks = 50;
  uint32 actual_end, expected_end;  /* [timer ticks] */

  TRBSYS_setRealtimeTickCtr( start_timer_ticks );

  RBSYS_waitUsecLoop(wait_time_in_usec);

  actual_end = RBSYS_SystemTimerRealtimeCnt;
  expected_end = start_timer_ticks + (wait_time_in_usec * RBSYS_TIMERTICKS_PER_US) + TRBSYS_SNOOZE_LOOP_TICKS;

  SWT_EvalEq(actual_end, expected_end);
}




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