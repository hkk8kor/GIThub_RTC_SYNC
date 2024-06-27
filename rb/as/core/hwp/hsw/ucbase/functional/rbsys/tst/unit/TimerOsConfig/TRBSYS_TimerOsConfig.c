#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                      // for RBFS_TaskSync

/* used interfaces */
#include "RBSYS_uCRegisters.h"         // peripheral labels
#include "RBSYS_OSServices.h"
#include "TRBSYS_OSServices.h"
#include "RBSYS_ErrorHooks.h"
#include "RBSYS_EnableIRQs.h"
#include "Os.h"
#include "RBSYS_CpuInfo.h"
#include "TRBSYS_CpuInfo.h"
#include "RBSYS_SystemTimer.h"
#include "TRBSYS_LocksHelper.h"

#include "RBHSWDEM_Facade.h"
#include "DemStub_Helper.h"

#include "RBSYS_TaskSync.h"
#include "RBSYS_TimerOsConfig.h"
#include "TRBSYS_TimerOsConfig_Adaptor.h"


#include <stdio.h> //< for printf()
#include <stdlib.h> //< for abs()

/**
 * \Reference
 * RBSYS_timer_freq_mhz
 *
 * \Purpose
 * Store system timer frequency to measurement variable for converting MM6 results
 *
 * \Sequence
 * n/a
 *
 * \ExpectedResult
 * Measurement variable "RBSYS_timer_freq_mhz" must be initialized correct
 */
SWTEST void TRBSYS_timer_freq_mhz(void)
{
  SWT_EvalEq(GetPrivate_RBSYS_timer_freq_mhz(), RBSYS_TIMERTICKS_PER_US);
}


/**
 * \Reference
 * RBSYS_SetupOsTimer, Gen_SWCS_HSW_uC_Base_SYS-248
 *
 * \Purpose
 * Verify timer configuration for Operating System
 *
 * \Sequence
 * Initialize System Timer counter for sync time
 * Call function RBSYS_SetupOsTimer
 *
 * \ExpectedResult
 * Enter/Exit of common lock must be called
 * System Timer compare 0: first 1ms task activation
 * System Timer compare 1: first x1 task activation
 */
SWTEST void TRBSYS_SetupOsTimer(void)
{
  uint32 frc_init = 10;
  uint32 delay_init_to_1ms = DELAY_init_TO_1ms_US * RBSYS_TIMERTICKS_PER_US;
  uint32 delay_init_to_x1 = (DELAY_init_TO_1ms_US + DELAY_1ms_TO_x1_US) * RBSYS_TIMERTICKS_PER_US;

  RBSYS_SYNCTIME_CNT = frc_init;

  RBSYS_SetupOsTimer();

  SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
  SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);

  SWT_EvalEq(RBSYS_SYNCTIME_CMP0, frc_init + delay_init_to_1ms);
  SWT_EvalEq(RBSYS_SYNCTIME_CMP0, TRBSYS_getTask1msFirstTickCtr());

  SWT_EvalEq(RBSYS_SYNCTIME_CMP1, frc_init + delay_init_to_x1);
  SWT_EvalEq(RBSYS_SYNCTIME_CMP1, TRBSYS_getTaskBaseCtrlFirstTickCtr());

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEqX(STM0STC, 0x20);
  #endif
}


/**
 * \Reference
 * RBSYS_EnableOsTimerIRQs, Gen_SWCS_HSW_uC_Base_SYS-248
 *
 * \Purpose
 * Verify enabling of timer IRQs for Operating System
 *
 * \Sequence
 * Simulate corresponding core ID for highest frequency OS timer interrupt
 * Call function RBSYS_EnableOsTimerIRQs
 * Only for multi core and only if different HW timer interrupts are used:
 *   Simulate corresponding core ID for lower frequency OS timer interrupt
 *   Call function RBSYS_EnableOsTimerIRQs
 * Only if not all cores are linked to separate HW timer interrupts:
 *   Simulate core ID of non-used core
 *   Call function RBSYS_EnableOsTimerIRQs
 *   Evaluate: Sanity check should fail
 *
 * \ExpectedResult
 * Ensure that corresponding enable function is called dependent on the corresponding core
 */
SWTEST void TRBSYS_EnableOsTimerIRQs(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    TRBSYS_setCoreID(OS_CORE_FOR_ISRSTM04);
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    TRBSYS_setCoreID(OS_CORE_FOR_ISRCommonTimer);
  #endif

  RBSYS_EnableOsTimerIRQs();

  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    #if(RBFS_MCORE == RBFS_MCORE_OFF)
      // both timer interrupts have been enabled
      SWT_EvalEqX(TRBSYS_Os_Clear_ISRSTM04_CallCnt, 1);
      SWT_EvalEqX(TRBSYS_Os_Enable_ISRSTM04_CallCnt, 1);
      SWT_EvalEqX(TRBSYS_Os_Clear_ISRSTM05_CallCnt, 1);
      SWT_EvalEqX(TRBSYS_Os_Enable_ISRSTM05_CallCnt, 1);
      // clear pending IRQ has been called before enable IRQ
      SWT_EvalEqX(TRBSYS_Os_ISRSTM04_Status, 1);
      SWT_EvalEqX(TRBSYS_Os_ISRSTM05_Status, 1);
      // core ids to which the interrupts are assigend to are the same
      SWT_EvalEqX(OS_CORE_FOR_ISRSTM04, OS_CORE_FOR_ISRSTM05);
    #else
      // only STM04 interrupt has been enabled
      SWT_EvalEqX(TRBSYS_Os_Clear_ISRSTM04_CallCnt, 1);
      SWT_EvalEqX(TRBSYS_Os_Enable_ISRSTM04_CallCnt, 1);
      SWT_EvalEqX(TRBSYS_Os_Clear_ISRSTM05_CallCnt, 0);
      SWT_EvalEqX(TRBSYS_Os_Enable_ISRSTM05_CallCnt, 0);
      // clear pending has been called before enable IRQ
      SWT_EvalEqX(TRBSYS_Os_ISRSTM04_Status, 1);

      TRBSYS_setCoreID(OS_CORE_FOR_ISRSTM05);

      RBSYS_EnableOsTimerIRQs();

      // only STM05 interrupt has been enabled
      SWT_EvalEqX(TRBSYS_Os_Clear_ISRSTM04_CallCnt, 1);
      SWT_EvalEqX(TRBSYS_Os_Enable_ISRSTM04_CallCnt, 1);
      SWT_EvalEqX(TRBSYS_Os_Clear_ISRSTM05_CallCnt, 1);
      SWT_EvalEqX(TRBSYS_Os_Enable_ISRSTM05_CallCnt, 1);
      // clear pending IRQ has been called before enable IRQ
      SWT_EvalEqX(TRBSYS_Os_ISRSTM05_Status, 1);
    #endif
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      SWT_EvalEqX(TRBSYS_Os_Clear_ISRCommonTimer_CallCnt, 1);
      SWT_EvalEqX(TRBSYS_Os_Enable_ISRCommonTimer_CallCnt, 1);
      SWT_EvalEqX(TRBSYS_Os_ISRCommonTimer_Status, 1);

      TRBSYS_setCoreID(RBSYS_getCoreID() + 1); // invalid core ID

      // Os Functions have not been called again
      RBSYS_EnableOsTimerIRQs();
      SWT_EvalEqX(TRBSYS_Os_Clear_ISRCommonTimer_CallCnt, 1);
      SWT_EvalEqX(TRBSYS_Os_Enable_ISRCommonTimer_CallCnt, 1);
      SWT_EvalEqX(TRBSYS_Os_ISRCommonTimer_Status, 1);
  #endif
}

#if (RBFS_TaskSync == RBFS_TaskSync_ON)

  /**
  * \Reference
  * RBSYS_STMControlTicks, Gen_SWCS_HSW_uC_Base_SYS-225
  *
  * \Purpose
  * Test different Timer adaption scenarios
  *
  * \Sequence
  * Setup Counter Register (according to tested scenario, see table below)
  * Call function RBSYS_STMControlTicks
  * Evaluate Adapted Counter Register (according to tested scenario)
  * Evaluate Synctime and Realtime value (according to tested scenario)
  *
  * \ExpectedResult
  * see table of scenarios below
  */
  SWTEST void TRBSYS_STMControlTicks_Adaption(void)
  {
    typedef struct{
      sint32 RequestedAdaption;
      uint32 Counter;
      uint32 Compare0;
      uint32 Compare1;
      sint32 ExpectedRealizedAdaption;
    }TRBSYS_STMControlTicks_TestCaseScenario_t;

    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

      static TRBSYS_STMControlTicks_TestCaseScenario_t testCases[] =
      { /* Requested Adaption, Counter, Compare0, Compare1, Expected Realized Adaption */
        /* -------------------- ACCELERATION SEQUENCES --------------------- */
/*  0*/ {  1,                  10,       11,       13,       0        }, // Compare0 has least difference to Count, adaption limited to 0 (Count must be < Least_CMP -2)
        {  1,                  10,       13,       11,       0        }, // Compare1 has least difference to Count, adaption limited to 0 (Count must be < Least_CMP -2)
        {  1,                  10,       12,       13,       0        }, // Compare0 has least difference to Count, adaption limited to 0 (Count must be < Least_CMP -2)
        {  1,                  10,       13,       12,       0        }, // Compare1 has least difference to Count, adaption limited to 0 (Count must be < Least_CMP -2)
        {  1,                  10,       14,       15,       1        }, // Compare0 has least difference to Count, adaption valid
        {  1,                  10,       16,       18,       1        }, // Compare0 has least difference to Count, adaption valid
        {  2,                  10,       13,       15,       1        }, // Compare0 has least difference to Count, adaption limited to 1 (Count must be < Least_CMP -2)
        {  2,                  10,       14,       15,       2        }, // Compare0 has least difference to Count, adaption valid
        {  1,                  RBSYS_convertUsecToTimerTicks(CYCLETIME_x1),       RBSYS_convertUsecToTimerTicks(CYCLETIME_x1) - 4,                                                       RBSYS_convertUsecToTimerTicks(CYCLETIME_x1) - 5,      1        }, // both Compares are in the past, future Compare will be calculated and difference to Count is higher than requested adaption
        {  2,                  RBSYS_convertUsecToTimerTicks(CYCLETIME_x1),       RBSYS_convertUsecToTimerTicks(CYCLETIME_x1) - RBSYS_convertUsecToTimerTicks(CYCLETIME_STM04) + 3,      5,                                                    1        }, // both Compares are in the past, future Compare0 has least difference to Count (difference 3 -> max adaption = 1)
/* 10*/ {  2,                  RBSYS_convertUsecToTimerTicks(CYCLETIME_x1),       RBSYS_convertUsecToTimerTicks(CYCLETIME_x1) - RBSYS_convertUsecToTimerTicks(CYCLETIME_STM04) + 5,      3,                                                    1        }, // both Compares are in the past, future Compare1 has least difference to Count (difference 3 -> max adaption = 1)
        /* -------------------- DECELERATION SEQUENCES --------------------- */
        {  -2,                 10,       9,        8,       -2        }, // For active waiting, no limitation is required
        {  -2,                 10,       8,        9,       -2        }, // For active waiting, no limitation is required
        {  -2,                 10,       11,       12,      -2        }, // For active waiting, no limitation is required
        {  -2,                 10,       12,       11,      -2        }, // For active waiting, no limitation is required
        /* --------------------------- IDLE ------------------------------- */
/* 15*/ {  0,                  10,       20,       30,       0        }, // requested adaption is 0 => nothing happens
      };

    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

      static TRBSYS_STMControlTicks_TestCaseScenario_t testCases[] =
      { /* Requested Adaption, Counter, Compare0, Compare1, Expected Realized Adaption */
        /* -------------------- ACCELERATION SEQUENCES --------------------- */
/*  0*/ {  50,                 0,       100,      200,      0        }, // both Compares too close to Count
        {  50,                 0,       100,      700,      0        }, // Compare0 too close to Count
        {  50,                 0,       700,      100,      0        }, // Compare1 too close to Count
        {  50,                 100,     100,      100,      0        }, // both Compares exactly match Count
        {  50,                 100,     100,      700,      0        }, // Compare0 exactly matches Count
        {  50,                 100,     700,      100,      0        }, // Compare1 exactly matches Count
        {  50,                 100,     700,      800,      50       }, // Compare0 has least difference to Count (100), adaption valid
        {  50,                 100,     800,      700,      50       }, // Compare1 has least difference to Count (100), adaption valid
        {  250,                100,     800,      700,      100      }, // Compare0 has least difference to Count (100), adaption limited to 100
        {  250,                100,     700,      800,      100      }, // Compare1 has least difference to Count (100), adaption limited to 100
/* 10*/ {  250,                100,     0,        50,       250      }, // both Compares are in the past, no limitation required
        {  250,                100,     0,        700,      100      }, // Compare0 allows infinite adaption, Compare1 limits adaption to 100
        {  250,                100,     700,      0,        100      }, // Compare1 allows infinite adaption, Compare0 limits adaption to 100
        {  250,                100,     0,        550,      0        }, // Compare0 allows infinite adaption, Compare1 is too close to Count
/* 14*/ {  250,                100,     550,      0,        0        }, // Compare1 allows infinite adaption, Compare0 is too close to Count
        /* -------------------- DECELERATION SEQUENCES --------------------- */
/* 15*/ {  -50,                 0,       100,      200,      0        }, // both Compares too close to Count
        {  -50,                 0,       100,      700,      0        }, // Compare0 too close to Count
        {  -50,                 0,       700,      100,      0        }, // Compare1 too close to Count
        {  -50,                 100,     100,      100,      0        }, // both Compares exactly match Count
        {  -50,                 100,     100,      700,      0        }, // Compare0 exactly matches Count
/* 20*/ {  -50,                 100,     700,      100,      0        }, // Compare1 exactly matches Count
        {  -50,                 300,     100,      0,        -50      }, // Compare0 has least difference to Count (-200), adaption is valid
        {  -50,                 300,     0,        100,      -50      }, // Compare1 has least difference to Count (-200), adaption is valid
        {  -250,                300,     100,      0,        -199     }, // Compare0 has least difference to Count (-200), adaption limited to -199
        {  -250,                300,     0,        100,      -199     }, // Compare1 has least difference to Count (-200), adaption limited to -199
        {  -50,                 100,     700,      800,      -50      }, // both Compares are in the future, no limitation required
        {  -250,                300,     100,      900,      -199     }, // Compare0 has least difference to Count (-200), adaption limited to -199
        {  -250,                300,     900,      100,      -199     }, // Compare1 has least difference to Count (-200), adaption limited to -199
        {  -50,                 300,     100,      550,      0        }, // Compare0 valid, Compare1 too close to Count
/* 29*/ {  -50,                 300,     550,      100,      0        }, // Compare1 valid, Compare0 too close to Count
        /* --------------------------- IDLE ------------------------------- */
/* 30*/ {   0,                  100,     800,      900,      0        }, // requested adaption is 0 => nothing happens
      };
    #endif


    uint32 i;
    for( i=0; i < sizeof(testCases)/sizeof(testCases[0]); i++ )
    {
      static uint32 overall_adapted_ticks = 0;

      sint32 result;
      RBSYS_SYNCTIME_CNT = testCases[i].Counter;
      RBSYS_SYNCTIME_CMP0 = testCases[i].Compare0;
      RBSYS_SYNCTIME_CMP1 = testCases[i].Compare1;
      RBSYS_SYNCTIME_STR = RBSYS_SYNCTIME_STRMASK;
      RBSYS_SYNCTIME_STP = 0;

      #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
        RBSYS_SystemTimerRealtimeCnt = 0;
      #endif

      printf("Current Test Case index: %d\n", i);
      result = RBSYS_STMControlTicks(testCases[i].RequestedAdaption);

      /* P1x / U2A: Timer is stopped and Counter value is adapted
        * Stellar: Timer is not stopped and Compare values are adapted */
      #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
        if( testCases[i].ExpectedRealizedAdaption != 0 )
        {
          SWT_EvalEqX(RBSYS_SYNCTIME_STP, RBSYS_SYNCTIME_STPVAL);
        }
        SWT_EvalEqX(RBSYS_SYNCTIME_RUN, RBSYS_SYNCTIME_RUNVAL);
        if( testCases[i].ExpectedRealizedAdaption > 0 )
        {
          /* Acceleration: SynctimeCount will be increased, RealtimeCnt is same */
          SWT_EvalEq(RBSYS_getSynctimeTickCtr(), (testCases[i].Counter + (uint32)testCases[i].ExpectedRealizedAdaption));
          SWT_EvalEq(RBSYS_getRealtimeTickCtr(), 0);
        }
        else // testCases[i].ExpectedRealizedAdaption <= 0
        {
          /* Deceleration: Waiting for Realtime to pass by - SynctimeCount same, RealtimeCnt is increased */
          SWT_EvalEq(RBSYS_getSynctimeTickCtr(), testCases[i].Counter);
          SWT_EvalEq(RBSYS_getRealtimeTickCtr(), abs(testCases[i].ExpectedRealizedAdaption));
        }
      #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        SWT_EvalEq(RBSYS_getSynctimeTickCtr(), (testCases[i].Counter + overall_adapted_ticks + (uint32)testCases[i].ExpectedRealizedAdaption));
        overall_adapted_ticks += result;
      #endif

      SWT_EvalEq(result, testCases[i].ExpectedRealizedAdaption);

      /* P1x / U2A: Counter value is adapted
        * Stellar: Compare values are adapted */
      #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
        if( testCases[i].ExpectedRealizedAdaption > 0 )
        {
          /* Acceleration: Count will be increased */
          SWT_EvalEq(RBSYS_SYNCTIME_CNT,  testCases[i].Counter + testCases[i].ExpectedRealizedAdaption); //< HW Counter register has been changed
        }
        else // testCases[i].ExpectedRealizedAdaption <= 0
        {
          /* Deceleration: Waiting for Realtime to pass by - Count is not modified */
          SWT_EvalEq(RBSYS_SYNCTIME_CNT, testCases[i].Counter);
        }
        SWT_EvalEq(RBSYS_SYNCTIME_CMP0, testCases[i].Compare0); //< unchanged
        SWT_EvalEq(RBSYS_SYNCTIME_CMP1, testCases[i].Compare1); //< unchanged
      #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        SWT_EvalEq(RBSYS_SYNCTIME_CNT,  testCases[i].Counter); //< HW Counter register has not been changed
        SWT_EvalEq(RBSYS_SYNCTIME_CMP0, testCases[i].Compare0 - testCases[i].ExpectedRealizedAdaption);
        SWT_EvalEq(RBSYS_SYNCTIME_CMP1, testCases[i].Compare1 - testCases[i].ExpectedRealizedAdaption);
      #endif

      SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
      if( testCases[i].RequestedAdaption != 0 )
      {
        SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
        TRBSYS_GlobLock.fnc_call_cnt = 0; //< reset
      }
      else
      {
        SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 0);
      }
    }
  }

  #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    /**
      * \Reference
      * rbsys_STMControlTicks_LimitedAccelerationTicks, Gen_SWCS_HSW_uC_Base_SYS-225
      *
      * \Purpose
      * Test if sanity checks work (Sanity checks are for development purpose only - cannot be triggered from outside this unit)
      *
      * \Sequence
      * Call rbsys_STMControlTicks_LimitedAccelerationTicks with negative adaption value
      * Call rbsys_STMControlTicks_LimitedAccelerationTicks with difference to next compare of 1
      * Call rbsys_STMControlTicks_LimitedDecelerationTicks with positive adaption value
      *
      * \ExpectedResult
      * assertions should fail individually
      */
    SWTEST void TRBSYS_STMControlTicks_SanityChecks(void)
    {
      SWT_AssertCheckStart("rbsys_STMControlTicks_LimitedAccelerationTicks", "delta_ticks > 0");
      CallPrivate_rbsys_STMControlTicks_LimitedAccelerationTicks(-1, 0);
      SWT_AssertCheckEnd();

      SWT_AssertCheckStart("rbsys_STMControlTicks_LimitedAccelerationTicks", "diff_to_compare > RBSYS_TASKSYNC_BUFFER_TIME");
      CallPrivate_rbsys_STMControlTicks_LimitedAccelerationTicks(1, 1);
      SWT_AssertCheckEnd();

      SWT_AssertCheckStart("rbsys_STMControlTicks_LimitedDecelerationTicks", "delta_ticks < 0");
      CallPrivate_rbsys_STMControlTicks_LimitedDecelerationTicks(1, 0);
      SWT_AssertCheckEnd();
    }
  #endif


  /**
  * \Reference
  * RBSYS_GetTimeToNextBaseCycle, Gen_SWCS_HSW_uC_Base_SYS-225
  *
  * \Purpose
  * Verify function to get timer ticks for next x1 base-cycle activation
  *
  * \Sequence
  * 1. Simulate other task than x1 and call function RBSYS_GetTimeToNextBaseCycle
  * 2. Simulate x1High task, adapt timer registers and call function RBSYS_GetTimeToNextBaseCycle
  * 3. Simulate x1Low task, adapt timer registers and call function RBSYS_GetTimeToNextBaseCycle
  *
  * \ExpectedResult
  * 1. RBSYS_setSYSErrorHook will be called with corresponding debug data
  * 2. return value must be compare value - counter value (and common lock must be called)
  * 3. return value must be compare value - counter value (and common lock must be called)
  */
  SWTEST void TRBSYS_GetTimeToNextBaseCycle(void)
  {
    uint32 result;

    // 1st sequence
    TRBSYS_SetCurrentTask(RBSYS_TaskType_TaskBaseCtrlCycx2);
    result = RBSYS_GetTimeToNextBaseCycle();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_WrongAPIcalled);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), ((uint32)(&RBSYS_GetTimeToNextBaseCycle)));
    SWT_EvalEq(result, 0);


    // 2nd sequence
    TRBSYS_SetCurrentTask(RBSYS_TaskType_TaskBaseCtrlCycx1High);

    RBSYS_SYNCTIME_CNT = 1;
    RBSYS_SYNCTIME_CMP1 = 10;

    result = RBSYS_GetTimeToNextBaseCycle();

    SWT_EvalEq(result, 9);                  // RBSYS_SYNCTIME_CMP1 - RBSYS_getSynctimeTickCtr() or RBSYS_SYNCTIME_CMP1 - RBSYS_getSynctimeTickCtr()
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);


    // 3rd sequence
    TRBSYS_SetCurrentTask(RBSYS_TaskType_TaskBaseCtrlCycx1Low);

    RBSYS_SYNCTIME_CNT = 1;
    RBSYS_SYNCTIME_CMP1 = 10;

    result = RBSYS_GetTimeToNextBaseCycle();

    SWT_EvalEq(result, 9);                  // RBSYS_SYNCTIME_CMP1 - RBSYS_getSynctimeTickCtr() or RBSYS_SYNCTIME_CMP1 - RBSYS_getSynctimeTickCtr()
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 2);
  }

#endif

