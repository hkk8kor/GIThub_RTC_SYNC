#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                       ///< for RBFS_TaskSync, RBFS_SysTask0p5ms

#include "RBSYS_TaskSync.h"
#include "TRBSYS_TaskSync_Adaptor.h"
#include "RBSYS_Subsystem.h"

#include "TRBSYS_LocksHelper.h"


#if (RBFS_TaskSync == RBFS_TaskSync_ON)


  /**
   * \Reference
   *  RBSYS_PRC_SRMSTimeBaseAdaptation, Gen_SWCS_HSW_uC_Base_SYS-288
   *
   * \Purpose
   *  Max correction is limted per adaption cycle (RBSYS_TASKSCHEME_ADJUST_MAX_PERCENT => 2%)
   *
   * \Sequence
   *  (verification is based on macros, therefore no functional sequence necessary)
   *
   * \ExpectedResult
   *  Max taskscheme adaption factor is 2%
   *  - 20us based of adaption within 1ms task
   *  - 10us based of adaption within 500us task
   */
  SWTEST void TRBSYS_SRMSTimeBaseLimitation(void)
  {
    sint32 limited_correction_us = GetPrivate_RBSYS_SRMSMAXCORRECTION_US();
    sint32 cycletime_us = GetPrivate_RBSYS_SRMS_CYCLETIME_US();

    sint32 correction_factor = 100.0 / cycletime_us * limited_correction_us;

    #if (RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
      SWT_EvalEqF(cycletime_us, 500, 0.0);
      SWT_EvalEqF(limited_correction_us, 10, 0.0);
    #else
      SWT_EvalEqF(cycletime_us, 1000, 0.0);
      SWT_EvalEqF(limited_correction_us, 20, 0.0);
    #endif

    SWT_EvalEqF(correction_factor, 2.0f, 0.0);
    SWT_EvalEqF(RBSYS_TASKSCHEME_ADJUST_MAX_PERCENT, 2.0f, 0.0);
  }


  /**
   * \Reference
   *  RBSYS_PRC_SRMSTimeBaseAdaptation, Gen_SWCS_HSW_uC_Base_SYS-225
   *
   * \Purpose
   *  No flexray time base adaption in case it's not requested
   *
   * \Sequence
   *  Initialize global variable "RBSYS_SRMS_ticks_to_adapt" with zero
   *  Call process "RBSYS_PRC_SRMSTimeBaseAdaptation"
   *
   * \ExpectedResult
   *  Global variable "RBSYS_SRMS_ticks_to_adapt" must still contain zero
   *  Global variable "RBSYS_SRMS_overall_adapted_ticks" must be equal to zero
   *  Global lock must be called once within function call RBSYS_SRMS_adapt_timebase
   */
  SWTEST void TRBSYS_SRMSTimeBaseAdaptation(void)
  {
    sint32 ticks_to_adapt = 0;
    RBSYS_SRMS_adapt_timebase(ticks_to_adapt);
    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);

    RBSYS_PRC_SRMSTimeBaseAdaptation();

    SWT_EvalEq(RBSYS_SRMS_adapt_ticks_left(), 0);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_ticks_to_adapt(), 0);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_overall_adapted_ticks(), 0);

    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
  }


  /**
   * \Reference
   *  RBSYS_PRC_SRMSTimeBaseAdaptation, Gen_SWCS_HSW_uC_Base_SYS-225
   *
   * \Purpose
   *  Flexray time base adaption greater than max correction (advance)
   *
   * \Sequence
   *  Initialize global variable "RBSYS_SRMS_ticks_to_adapt" with RBSYS_SRMSMAXCORRECTION_TICKS +1
   *  Call process "RBSYS_PRC_SRMSTimeBaseAdaptation"
   *
   * \ExpectedResult
   *  Global variable "RBSYS_SRMS_ticks_to_adapt" must still contain requested value - RBSYS_SRMSMAXCORRECTION_TICKS (=> 1)
   *  Global variable "RBSYS_SRMS_overall_adapted_ticks" must be equal to RBSYS_SRMSMAXCORRECTION_TICKS
   *  Global lock must be called a first time within function call RBSYS_SRMS_adapt_timebase
   *  Global lock must be called a second time within RBSYS_PRC_SRMSTimeBaseAdaptation
   */
  SWTEST void TRBSYS_SRMSTimeBaseAdaptation_advance_1(void)
  {
    sint32 ticks_to_adapt = GetPrivate_RBSYS_SRMSMAXCORRECTION_TICKS() + 1;

    RBSYS_SRMS_adapt_timebase(ticks_to_adapt);
    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);

    RBSYS_PRC_SRMSTimeBaseAdaptation();

    SWT_EvalEq(RBSYS_SRMS_adapt_ticks_left(), 1);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_ticks_to_adapt(), 1);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_overall_adapted_ticks(), GetPrivate_RBSYS_SRMSMAXCORRECTION_TICKS());

    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 2);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
  }


  /**
   * \Reference
   *  RBSYS_PRC_SRMSTimeBaseAdaptation, Gen_SWCS_HSW_uC_Base_SYS-225
   *
   * \Purpose
   *  Flexray time base adaption equal max correction (advance)
   *
   * \Sequence
   *  Initialize global variable "RBSYS_SRMS_ticks_to_adapt" with RBSYS_SRMSMAXCORRECTION_TICKS
   *  Call process "RBSYS_PRC_SRMSTimeBaseAdaptation"
   *
   * \ExpectedResult
   *  Global variable "RBSYS_SRMS_ticks_to_adapt" must contain 0
   *  Global variable "RBSYS_SRMS_overall_adapted_ticks" must be equal to RBSYS_SRMSMAXCORRECTION_TICKS
   *  Global lock must be called a first time within function call RBSYS_SRMS_adapt_timebase
   *  Global lock must be called a second time within RBSYS_PRC_SRMSTimeBaseAdaptation
   */
  SWTEST void TRBSYS_SRMSTimeBaseAdaptation_advance_2(void)
  {
    sint32 ticks_to_adapt = GetPrivate_RBSYS_SRMSMAXCORRECTION_TICKS();
    RBSYS_SRMS_adapt_timebase(ticks_to_adapt);
    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);

    RBSYS_PRC_SRMSTimeBaseAdaptation();

    SWT_EvalEq(RBSYS_SRMS_adapt_ticks_left(), 0);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_ticks_to_adapt(), 0);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_overall_adapted_ticks(), GetPrivate_RBSYS_SRMSMAXCORRECTION_TICKS());

    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 2);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
  }


  /**
   * \Reference
   *  RBSYS_PRC_SRMSTimeBaseAdaptation, Gen_SWCS_HSW_uC_Base_SYS-225
   *
   * \Purpose
   *  Flexray time base adaption less than max correction (advance)
   *
   * \Sequence
   *  Initialize global variable "RBSYS_SRMS_ticks_to_adapt" with RBSYS_SRMSMAXCORRECTION_TICKS -1
   *  Call process "RBSYS_PRC_SRMSTimeBaseAdaptation"
   *
   * \ExpectedResult
   *  Global variable "RBSYS_SRMS_ticks_to_adapt" must contain 0
   *  Global variable "RBSYS_SRMS_overall_adapted_ticks" must be equal to RBSYS_SRMSMAXCORRECTION_TICKS -1
   *  Global lock must be called a first time within function call RBSYS_SRMS_adapt_timebase
   *  Global lock must be called a second time within RBSYS_PRC_SRMSTimeBaseAdaptation)
   */
  SWTEST void TRBSYS_SRMSTimeBaseAdaptation_advance_3(void)
  {
    sint32 ticks_to_adapt = GetPrivate_RBSYS_SRMSMAXCORRECTION_TICKS() - 1;
    RBSYS_SRMS_adapt_timebase(ticks_to_adapt);
    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);

    RBSYS_PRC_SRMSTimeBaseAdaptation();

    SWT_EvalEq(RBSYS_SRMS_adapt_ticks_left(), 0);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_ticks_to_adapt(), 0);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_overall_adapted_ticks(), ticks_to_adapt);

    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 2);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
  }


  /**
   * \Reference
   *  RBSYS_PRC_SRMSTimeBaseAdaptation, Gen_SWCS_HSW_uC_Base_SYS-225
   *
   * \Purpose
   *  Flexray time base adaption greater than max correction (retard)
   *
   * \Sequence
   *  Initialize global variable "RBSYS_SRMS_ticks_to_adapt" with -RBSYS_SRMSMAXCORRECTION_TICKS -1
   *  Call process "RBSYS_PRC_SRMSTimeBaseAdaptation"
   *
   * \ExpectedResult
   *  Global variable "RBSYS_SRMS_ticks_to_adapt" must still contain requested value - RBSYS_SRMSMAXCORRECTION_TICKS (=> -1)
   *  Global variable "RBSYS_SRMS_overall_adapted_ticks" must be equal to -RBSYS_SRMSMAXCORRECTION_TICKS
   *  Global lock must be called a first time within function call RBSYS_SRMS_adapt_timebase
   *  Global lock must be called a second time within RBSYS_PRC_SRMSTimeBaseAdaptation)
   */
  SWTEST void TRBSYS_SRMSTimeBaseAdaptation_retard_1(void)
  {
    sint32 ticks_to_adapt = -GetPrivate_RBSYS_SRMSMAXCORRECTION_TICKS() - 1;
    RBSYS_SRMS_adapt_timebase(ticks_to_adapt);
    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);

    RBSYS_PRC_SRMSTimeBaseAdaptation();

    SWT_EvalEq(RBSYS_SRMS_adapt_ticks_left(), -1);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_ticks_to_adapt(), -1);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_overall_adapted_ticks(), -GetPrivate_RBSYS_SRMSMAXCORRECTION_TICKS());

    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 2);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
  }


  /**
   * \Reference
   *  RBSYS_PRC_SRMSTimeBaseAdaptation, Gen_SWCS_HSW_uC_Base_SYS-225
   *
   * \Purpose
   *  Flexray time base adaption equal max correction (retard)
   *
   * \Sequence
   *  Initialize global variable "RBSYS_SRMS_ticks_to_adapt" with -RBSYS_SRMSMAXCORRECTION_TICKS
   *  Call process "RBSYS_PRC_SRMSTimeBaseAdaptation"
   *
   * \ExpectedResult
   *  Global variable "RBSYS_SRMS_ticks_to_adapt" must contain 0
   *  Global variable "RBSYS_SRMS_overall_adapted_ticks" must be equal to -RBSYS_SRMSMAXCORRECTION_TICKS
   *  Global lock must be called a first time within function call RBSYS_SRMS_adapt_timebase
   *  Global lock must be called a second time within RBSYS_PRC_SRMSTimeBaseAdaptation)
   */
  SWTEST void TRBSYS_SRMSTimeBaseAdaptation_retard_2(void)
  {
    sint32 ticks_to_adapt = -GetPrivate_RBSYS_SRMSMAXCORRECTION_TICKS();
    RBSYS_SRMS_adapt_timebase(ticks_to_adapt);
    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);

    RBSYS_PRC_SRMSTimeBaseAdaptation();

    SWT_EvalEq(RBSYS_SRMS_adapt_ticks_left(), 0);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_ticks_to_adapt(), 0);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_overall_adapted_ticks(), -GetPrivate_RBSYS_SRMSMAXCORRECTION_TICKS());

    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 2);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
  }


  /**
   * \Reference
   *  RBSYS_PRC_SRMSTimeBaseAdaptation, Gen_SWCS_HSW_uC_Base_SYS-225
   *
   * \Purpose
   *  Flexray time base adaption less than max correction (retard)
   *
   * \Sequence
   *  Initialize global variable "RBSYS_SRMS_ticks_to_adapt" with -RBSYS_SRMSMAXCORRECTION_TICKS +1
   *  Call process "RBSYS_PRC_SRMSTimeBaseAdaptation"
   *
   * \ExpectedResult
   *  Global variable "RBSYS_SRMS_ticks_to_adapt" must contain 0
   *  Global variable "RBSYS_SRMS_overall_adapted_ticks" must be equal to -RBSYS_SRMSMAXCORRECTION_TICKS +1
   *  Global lock must be called a first time within function call RBSYS_SRMS_adapt_timebase
   *  Global lock must be called a second time within RBSYS_PRC_SRMSTimeBaseAdaptation)
   */
  SWTEST void TRBSYS_SRMSTimeBaseAdaptation_retard_3(void)
  {
    sint32 ticks_to_adapt = -GetPrivate_RBSYS_SRMSMAXCORRECTION_TICKS() + 1;
    RBSYS_SRMS_adapt_timebase(ticks_to_adapt);
    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);

    RBSYS_PRC_SRMSTimeBaseAdaptation();

    SWT_EvalEq(RBSYS_SRMS_adapt_ticks_left(), 0);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_ticks_to_adapt(), 0);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_overall_adapted_ticks(), ticks_to_adapt);

    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 2);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
  }


  /**
   * \Reference
   *  RBSYS_SRMS_adapt_ticks_left, Gen_SWCS_HSW_uC_Base_SYS-225
   *
   * \Purpose
   *  Verify function which returns number of adaptation ticks left
   *
   * \Sequence
   *  Call function RBSYS_SRMS_adapt_timebase with defined number of ticks to adapt as parameter
   *
   * \ExpectedResult
   *  Function RBSYS_SRMS_adapt_ticks_left must return the defined number of ticks from the call of RBSYS_SRMS_adapt_timebase
   *  Global variable "RBSYS_SRMS_ticks_to_adapt" must contain the same value as RBSYS_SRMS_adapt_ticks_left
   *  Global variable "RBSYS_SRMS_overall_adapted_ticks" must be zero
   *  Global lock must be called once within function call RBSYS_SRMS_adapt_timebase
   */
  SWTEST void TRBSYS_TaskSync_adapt_timebase(void)
  {
    sint32 ticks_to_adapt = 10;

    RBSYS_SRMS_adapt_timebase(ticks_to_adapt);

    SWT_EvalEq(RBSYS_SRMS_adapt_ticks_left(), ticks_to_adapt);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_ticks_to_adapt(), ticks_to_adapt);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_overall_adapted_ticks(), 0);

    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
  }


  /**
   * \Reference
   *  RBSYS_SRMS_adapt_timebase, Gen_SWCS_HSW_uC_Base_SYS-225
   *
   * \Purpose
   *  Verify process to test the task adaptation (e.g. via RB Diag)
   *
   * \Sequence
   *  Initialize variable RBSYS_SRMS_test_advance_ticks with defined number of ticks to adapt (e.g. 250)
   *  Call process RBSYS_PRC_SRMSCylicTest
   *
   * \ExpectedResult
   *  Function RBSYS_SRMS_adapt_ticks_left must return the positive defined number of ticks
   *  Global variable "RBSYS_SRMS_ticks_to_adapt" must contain the same value as RBSYS_SRMS_adapt_ticks_left
   *  Global variable "RBSYS_SRMS_overall_adapted_ticks" must be zero
   *  Global lock must be called once
   */
  SWTEST void TRBSYS_TaskSync_SRMSCylicTest_advance_ticks(void)
  {
    uint16 ticks_to_adapt = 250;

    RBSYS_SRMS_test_advance_ticks = ticks_to_adapt;

    RBSYS_PRC_SRMSCylicTest();

    SWT_EvalEq(RBSYS_SRMS_adapt_ticks_left(), ticks_to_adapt);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_ticks_to_adapt(), ticks_to_adapt);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_overall_adapted_ticks(), 0);

    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
  }


  /**
   * \Reference
   *  RBSYS_SRMS_adapt_timebase, Gen_SWCS_HSW_uC_Base_SYS-225
   *
   * \Purpose
   *  Verify process to test the task adaptation (e.g. via RB Diag)
   *
   * \Sequence
   *  Initialize variable RBSYS_SRMS_test_retard_ticks with defined number of ticks to adapt (e.g. 255)
   *  Call process RBSYS_PRC_SRMSCylicTest
   *
   * \ExpectedResult
   *  Function RBSYS_SRMS_adapt_ticks_left must return the negative defined number of ticks
   *  Global variable "RBSYS_SRMS_ticks_to_adapt" must contain the same value as RBSYS_SRMS_adapt_ticks_left   *  Global variable "RBSYS_SRMS_ticks_to_adapt" must be the negative defined number of ticks
   *  Global variable "RBSYS_SRMS_overall_adapted_ticks" must be zero
   *  Global lock must be called once
   */
  SWTEST void TRBSYS_TaskSync_SRMSCylicTest_retard_ticks(void)
  {
    uint16 ticks_to_adapt = 255;

    RBSYS_SRMS_test_retard_ticks = ticks_to_adapt;

    RBSYS_PRC_SRMSCylicTest();

    SWT_EvalEq(RBSYS_SRMS_adapt_ticks_left(), -ticks_to_adapt);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_ticks_to_adapt(), -ticks_to_adapt);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_overall_adapted_ticks(), 0);

    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
  }


  /**
   * \Reference
   *  RBSYS_SRMS_adapt_timebase, Gen_SWCS_HSW_uC_Base_SYS-225
   *
   * \Purpose
   *  Verify process to test the task adaptation (e.g. via RB Diag)
   *
   * \Sequence
   *  Initialize variables RBSYS_SRMS_test_advance_ticks and RBSYS_SRMS_test_retard_ticks with 0
   *  Call process RBSYS_PRC_SRMSCylicTest
   *
   * \ExpectedResult
   *  Function RBSYS_SRMS_adapt_ticks_left  must return zero
   *  Global variable "RBSYS_SRMS_ticks_to_adapt" must be zero
   *  Global variable "RBSYS_SRMS_overall_adapted_ticks" must be zero
   *  No Global lock will be called
   */
  SWTEST void TRBSYS_TaskSync_SRMSCylicTest(void)
  {
    uint16 ticks_to_adapt = 0;

    RBSYS_SRMS_test_advance_ticks = ticks_to_adapt;
    RBSYS_SRMS_test_retard_ticks = ticks_to_adapt;

    RBSYS_PRC_SRMSCylicTest();

    SWT_EvalEq(RBSYS_SRMS_adapt_ticks_left(), 0);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_ticks_to_adapt(), 0);
    SWT_EvalEq(GetPrivate_RBSYS_SRMS_overall_adapted_ticks(), 0);

    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 0);
    SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);
  }

#else

  SWTEST void TRBSYS_TaskSync_FeatureNotAvailable(void)
  {
    SWT_EvalEx(TRUE, "Feature not Available");
  }

#endif



#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
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