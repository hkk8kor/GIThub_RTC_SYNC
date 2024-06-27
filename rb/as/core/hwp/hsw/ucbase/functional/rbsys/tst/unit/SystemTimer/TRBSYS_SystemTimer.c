#include "SwTest_Global.h"                      // for SWT functionality
#include "TRBSYS_uCRegisters.h"

#include "TRBSYS_SystemTimer_Adaptor.h"

#include "RBSYS_SystemTimer.h"
#include "TRBSYS_SystemTimer.h"


/**
 * \Reference
 *  RBSYS_getSynctimeTickCtr, Gen_SWFS_0979_HSW_OverallRequirements_3677
 *
 * \Purpose
 *  Prove that STM0CNT1/TPTMPE0TPTM0UCNT0 is returned
 *
 * \Sequence
 *  1. Set STM0CNT1/TPTMPE0TPTM0UCNT0 and call: RBSYS_getSynctimeTickCtr
 *
 * \ExpectedResult
 *  STM0CNT1/TPTMPE0TPTM0UCNT0 is being returned
 */
SWTEST void TRBSYS_getSynctimeTickCtr(void)
{
  TRBSYS_setSyncTime(0xC0FFEE);
  SWT_EvalEq(RBSYS_getSynctimeTickCtr(), 0xC0FFEE);
}

/**
 * \Reference
 *  RBSYS_getRealtimeTickCtr, Gen_SWFS_0979_HSW_OverallRequirements_3677
 *
 * \Purpose
 *  Prove that STM0CNT2/TPTMPE0TPTM0UCNT1 is returned
 *
 * \Sequence
 *  1. Set STM0CNT2/TPTMPE0TPTM0UCNT1 and call: RBSYS_getRealtimeTickCtr
 *
 * \ExpectedResult
 *  STM0CNT2/TPTMPE0TPTM0UCNT1 is being returned
 */
SWTEST void TRBSYS_getRealtimeTickCtr(void)
{
  TRBSYS_setRealtimeTickCtr(0x1234);
  SWT_EvalEq(RBSYS_getRealtimeTickCtr(), 0x1234);
}

/**
 * \Reference
 *  RBSYS_startUsecTimer
 *
 * \Purpose
 *  Prove that STM0CNT2/TPTMPE0TPTM0UCNT1 is set in parameter (start_tick) which is passed to RBSYS_startUsecTimer
 *
 * \Sequence
 *  1. Initialize start_tick
 *  2. Set STM0CNT2/TPTMPE0TPTM0UCNT1 and call: RBSYS_startUsecTimer
 *
 * \ExpectedResult
 *  STM0CNT2/TPTMPE0TPTM0UCNT1 is being returned
 */
SWTEST void TRBSYS_startUsecTimer(void)
{
  uint32 start_tick = 0;
  TRBSYS_setRealtimeTickCtr(0xAFFE);

  RBSYS_startUsecTimer(&start_tick);

  SWT_EvalEq(start_tick, 0xAFFE);
}

/**
 * \Reference
 *  RBSYS_isUsecTimerElapsed
 *
 * \Purpose
 *  Check functionality of RBSYS_isUsecTimerElapsed() 
 *
 * \Sequence
 *  1. Set startTick to 200 and time_in_usec to 5us (-> 400 ticks)
 *  2. Set STM0CNT2/TPTMPE0TPTM0UCNT1 to 400 and call: RBSYS_isUsecTimerElapsed
 *  3. Set STM0CNT2/TPTMPE0TPTM0UCNT1 to 600 and call: RBSYS_isUsecTimerElapsed
 *  4. Set STM0CNT2/TPTMPE0TPTM0UCNT1 to 601 and call: RBSYS_isUsecTimerElapsed
 *  5. Set STM0CNT2/TPTMPE0TPTM0UCNT1 to 800 and call: RBSYS_isUsecTimerElapsed
 *
 * \ExpectedResult
 *  2. Timer is not elapsed since tick diff is 200 (<5us) -> Result == 0
 *  3. Timer is not elapsed since tick diff is 400 (<5us) -> Result == 0
 *  4. Timer is elapsed since tick diff is 401     (>5us) -> Result > 0
 *  5. Timer is elapsed since tick diff is 600     (>5us) -> Result > 0
 */
SWTEST void TRBSYS_isUsecTimerElapsed(void)
{
  uint32 result;
  uint32 startTick = 200;
  uint32 time_in_usec = 5;

  TRBSYS_setRealtimeTickCtr(400);
  result = RBSYS_isUsecTimerElapsed(&startTick, time_in_usec);
  SWT_EvalEq(result, FALSE);

  TRBSYS_setRealtimeTickCtr(startTick + 5*RBSYS_TIMERTICKS_PER_US);
  result = RBSYS_isUsecTimerElapsed(&startTick, time_in_usec);
  SWT_EvalEq(result, FALSE);

  TRBSYS_setRealtimeTickCtr(startTick + 5*RBSYS_TIMERTICKS_PER_US + 1);
  result = RBSYS_isUsecTimerElapsed(&startTick, time_in_usec);
  SWT_EvalEq(result, TRUE);

  TRBSYS_setRealtimeTickCtr(800);
  result = RBSYS_isUsecTimerElapsed(&startTick, time_in_usec);
  SWT_EvalEq(result, TRUE);
}


/**
 * \Reference
 *  TRBSYS_isUsecTimerElapsed_ExtendedRange
 *
 * \Purpose
 *  Check functionality of TRBSYS_isUsecTimerElapsed_ExtendedRange() 
 *
 * \Sequence
 *  1. Set timer (startTick) to 0
 *  2. 400us shall not be elapsed after 400us
 *  3. 400us shall be elapsed after 400us + 1tick
 *  4. 53687090us shall be a valid input for "time_in_usec" -> 32bit timer shall be capable of handling it
 *  5. [value of 4.)] + 1 shall be an invalid input for "time_in_usec" -> result can be ignored, assert shall hit
 *
 * \ExpectedResult
 *  see \Sequence
 */
SWTEST void TRBSYS_isUsecTimerElapsed_ExtendedRange(void)
{
  uint32 timer;
  const uint32 upperLimit_timeInUsec = UINT32_MAX/RBSYS_TIMERTICKS_PER_US - 1; // 53.687.090 us

  TRBSYS_setRealtimeTickCtr(0);
  RBSYS_startUsecTimer(&timer);

  /* end of timer range is reached -> still not elapsed */
  TRBSYS_setRealtimeTickCtr(400*RBSYS_TIMERTICKS_PER_US);
  SWT_EvalEq(RBSYS_isUsecTimerElapsed_ExtendedRange(&timer, 400), FALSE);

  /* 1 tick later, timer is elapsed -> is now elapsed */
  TRBSYS_setRealtimeTickCtr(400*RBSYS_TIMERTICKS_PER_US + 1);
  SWT_EvalEq(RBSYS_isUsecTimerElapsed_ExtendedRange(&timer, 400), TRUE);

  /** boundary check: does the allowed "time_in_usec" still fit if the HW-timer is at its limit? -> already elapsed */
  TRBSYS_setRealtimeTickCtr(UINT32_MAX);
  SWT_EvalEq(RBSYS_isUsecTimerElapsed_ExtendedRange(&timer, upperLimit_timeInUsec), TRUE);

  /** boundary check: if "time_in_usec" is out of the allowed range: overflow MAY happen and result may be invalid, 
   * therfore assert SHALL hit  */
  SWT_AssertCheckStart("RBSYS_isUsecTimerElapsed_ExtendedRange", "time_in_usec < RBSYS_convertTimerTicksToUsec(UINT32_MAX)");
  RBSYS_isUsecTimerElapsed_ExtendedRange(&timer, upperLimit_timeInUsec+1);
  SWT_AssertCheckEnd();
}

/**
 * \Reference
 * TRBSYS_waitUntilTimerElapsed
 *
 * \Purpose
 *  Check functionality of TRBSYS_waitUntilTimerElapsed()
 *
 *  \Sequence
 *   1. Set timer to 0
 *   2. Ensure timer is >400us after TRBSYS_waitUntilTimerElapsed is called
 *
 * \ExpectedResult
 *   see \Sequence
 */
SWTEST void TRBSYS_waitUntilTimerElapsed(void)
{
  uint32 timer;

  TRBSYS_setRealtimeTickCtr(0);
  RBSYS_startUsecTimer(&timer);

  RBSYS_waitUntilTimerElapsed(&timer, 400);
  SWT_Eval(RBSYS_SystemTimerRealtimeCnt > RBSYS_convertUsecToTimerTicks(400));
}
