#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h" // for RBFS_uCFamily

/* used interfaces */
#include "RBSYS_SystemTimer.h"
#include "TRBSYS_SystemTimer.h"
#include "RBSYS_uCModuleEnable.h"
#include "TRBSYS_PeripheralReset.h"
#include "RBSYS_Subsystem.h"

#include "RBHSWDEM_Facade.h"
#include "DemStub_Helper.h"
#include "RBSYS_ErrorHooks.h"

/* realized interfaces */
#include "TRBSYS_TimerMonitoring_Adaptor.h"

#define TIMERMON_MAX_DEV        ((2.0*RBSYS_TASKSCHEME_ADJUST_MAX_PERCENT)/100.0)
#define TIMERMON_DEV_ADDITONAL  ((unsigned)RBSYS_convertUsecToTimerTicks(50))
#define TIMERMON_UPPER_LIMIT(delta_r) (((delta_r)*((uint32)(((1.0+TIMERMON_MAX_DEV)*1024.0)+0.5)))/1024 + TIMERMON_DEV_ADDITONAL)
#define TIMERMON_LOWER_LIMIT_WITHOUT_ADDITIONAL(delta_r) (((delta_r)*((uint32)(((1.0-TIMERMON_MAX_DEV)*1024.0)+0.5)))/1024)
#define TIMERMON_LOWER_LIMIT(delta_r) ((TIMERMON_LOWER_LIMIT_WITHOUT_ADDITIONAL(delta_r) > TIMERMON_DEV_ADDITONAL) ? (TIMERMON_LOWER_LIMIT_WITHOUT_ADDITIONAL(delta_r)-TIMERMON_DEV_ADDITONAL) : 0)



#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
/**
 * \Reference
 *  RBSYS_PRC_TimerMonitoring, Gen_SWCS_HSW_uC_Base_SYS-253
 *
 * \Purpose
 *  Good case of timer monitoring (inside upper limit)
 *
 * \Sequence
 *  Initialize sync and real time
 *  Call process RBSYS_PRC_TimerMonitoring first time
 *  Modify sync and real time in a way that the delta is still inside the upper limit
 *  Call process RBSYS_PRC_TimerMonitoring second time
 *
 * \ExpectedResult
 *  No fault entry of SYSErrorHook
 */
SWTEST void TRBSYS_PRC_TimerMonitoring_GoodCase_1(void)
{
  uint32 timerSyncValue = 10;
  uint32 timerRtValue = 10;
  uint32 delta_s = 0;
  uint32 delta_r = 0;

  TRBSYS_setSynctimeTickCtr(timerSyncValue);
  TRBSYS_setRealtimeTickCtr(timerRtValue);

  /* 1st sequence: init_done 0 --> 1 */
  RBSYS_PRC_TimerMonitoring();

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_last(), timerSyncValue);
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_last(), timerRtValue);

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_dev__debug(), 0);
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_dev__debug(), 0);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);


  /* 2nd sequence */
  delta_r = 200 - timerRtValue;
  delta_s = TIMERMON_UPPER_LIMIT(delta_r) - 1; // calculate upper allowed limit for delta_s
  timerSyncValue += delta_s;
  timerRtValue += delta_r;

  TRBSYS_setSynctimeTickCtr(timerSyncValue);
  TRBSYS_setRealtimeTickCtr(timerRtValue);

  // if ((delta_s >= delta_r_hi) || (delta_s <= delta_r_lo))  --> FALSE
  RBSYS_PRC_TimerMonitoring();

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_last(), timerSyncValue );
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_last(), timerRtValue);

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_dev__debug(), delta_s);
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_dev__debug(), delta_r);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
}


/**
 * \Reference
 *  RBSYS_PRC_TimerMonitoring, Gen_SWCS_HSW_uC_Base_SYS-253
 *
 * \Purpose
 *  Good case of timer monitoring (inside	lower limit)
 *
 * \Sequence
 *  Initialize sync and real time
 *  Call process RBSYS_PRC_TimerMonitoring first time
 *  Modify sync and real time in a way that the delta is still inside the lower limit
 *  Call process RBSYS_PRC_TimerMonitoring second time
 *
 * \ExpectedResult
 *  No fault entry of SYSErrorHook
 */
SWTEST void TRBSYS_PRC_TimerMonitoring_GoodCase_2(void)
{
  uint32 timerSyncValue = 10;
  uint32 timerRtValue = 10;
  uint32 delta_s = 0;
  uint32 delta_r = 0;

  TRBSYS_setSynctimeTickCtr(timerSyncValue);
  TRBSYS_setRealtimeTickCtr(timerRtValue);

  /* 1st sequence: init_done 0 --> 1 */
  RBSYS_PRC_TimerMonitoring();

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_last(), timerSyncValue);
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_last(), timerRtValue);

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_dev__debug(), 0);
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_dev__debug(), 0);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);


  /* 2nd sequence */
  delta_r = 200 - timerRtValue;
  delta_s = TIMERMON_LOWER_LIMIT(delta_r) + 1; // calculate lower allowed limit for delta_s
  timerSyncValue += delta_s;
  timerRtValue += delta_r;

  TRBSYS_setSynctimeTickCtr(timerSyncValue);
  TRBSYS_setRealtimeTickCtr(timerRtValue);

  // if ((delta_s >= delta_r_hi) || (delta_s <= delta_r_lo))  --> FALSE
  RBSYS_PRC_TimerMonitoring();

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_last(), timerSyncValue );
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_last(), timerRtValue);

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_dev__debug(), delta_s);
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_dev__debug(), delta_r);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
}


/**
 * \Reference
 *  RBSYS_PRC_TimerMonitoring, Gen_SWCS_HSW_uC_Base_SYS-253
 *
 * \Purpose
 *  Good case of timer monitoring with more than TIMERMON_DEV_ADDITONAL as difference
 *
 * \Sequence
 *  Initialize sync and real time
 *  Call process RBSYS_PRC_TimerMonitoring first time
 *  Modify sync and real time in a way that the delta is still TIMERMON_DEV_ADDITONAL
 *  Call process RBSYS_PRC_TimerMonitoring second time
 *
 * \ExpectedResult
 *  No fault entry of SYSErrorHook
 */
SWTEST void TRBSYS_PRC_TimerMonitoring_GoodCase_3(void)
{
  uint32 timerSyncValue = 10;
  uint32 timerRtValue = 10;
  uint32 delta_s = 0;
  uint32 delta_r = 0;

  TRBSYS_setSynctimeTickCtr(timerSyncValue);
  TRBSYS_setRealtimeTickCtr(timerRtValue);

  /* 1st sequence: init_done 0 --> 1 */
  RBSYS_PRC_TimerMonitoring();

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_last(), timerSyncValue);
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_last(), timerRtValue);

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_dev__debug(), 0);
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_dev__debug(), 0);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);


  /* 2nd sequence */
  delta_r = 2*TIMERMON_DEV_ADDITONAL;
  delta_s = 2*TIMERMON_DEV_ADDITONAL;
  timerSyncValue += delta_s;
  timerRtValue += delta_r;

  TRBSYS_setSynctimeTickCtr(timerSyncValue);
  TRBSYS_setRealtimeTickCtr(timerRtValue);

  // if ((delta_s >= delta_r_hi) || (delta_s <= delta_r_lo))  --> FALSE
  RBSYS_PRC_TimerMonitoring();

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_last(), timerSyncValue );
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_last(), timerRtValue);

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_dev__debug(), delta_s);
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_dev__debug(), delta_r);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
}


/**
 * \Reference
 *  RBSYS_PRC_TimerMonitoring, Gen_SWCS_HSW_uC_Base_SYS-253
 *
 * \Purpose
 *  Fault case of timer monitoring (outside upper limit)
 *
 * \Sequence
 *  Initialize sync and real time
 *  Call process RBSYS_PRC_TimerMonitoring first time
 *  Modify sync and real time in a way that the delta is outside the upper limit
 *  Call process RBSYS_PRC_TimerMonitoring second time
 *
 * \ExpectedResult
 *  SYSErrorHook fault entry must be available
 */
SWTEST void TRBSYS_PRC_TimerMonitoring_FaultCase1(void)
{
  uint32 timerSyncValue = 10;
  uint32 timerRtValue = 10;
  uint32 delta_s = 0;
  uint32 delta_r = 0;

  TRBSYS_setSynctimeTickCtr(timerSyncValue);
  TRBSYS_setRealtimeTickCtr(timerRtValue);

  /* 1st sequence: init_done 0 --> 1 */
  RBSYS_PRC_TimerMonitoring();

  /* 2nd sequence */
  delta_r = 200 - timerRtValue;
  delta_s = TIMERMON_UPPER_LIMIT(delta_r); // calculate upper allowed limit for delta_s
  timerSyncValue += delta_s;
  timerRtValue += delta_r;

  TRBSYS_setSynctimeTickCtr(timerSyncValue);
  TRBSYS_setRealtimeTickCtr(timerRtValue);

  //(delta_s >= delta_r_hi) --> TRUE
  RBSYS_PRC_TimerMonitoring();

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_dev__debug(), delta_s);
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_dev__debug(), delta_r);
  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_last(), timerSyncValue );
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_last(), timerRtValue);
  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
}


/**
 * \Reference
 *  RBSYS_PRC_TimerMonitoring, Gen_SWCS_HSW_uC_Base_SYS-253
 *
 * \Purpose
 *  Fault case of timer monitoring (outside lower limit)
 *
 * \Sequence
 *  Initialize sync and real time
 *  Call process RBSYS_PRC_TimerMonitoring first time
 *  Modify sync and real time in a way that the delta is outside the lower limit
 *  Call process RBSYS_PRC_TimerMonitoring second time
 *
 * \ExpectedResult
 *  SYSErrorHook fault entry must be available
 */
SWTEST void TRBSYS_PRC_TimerMonitoring_FaultCase2(void)
{
  uint32 timerSyncValue = 10;
  uint32 timerRtValue = 10;
  uint32 delta_s = 0;
  uint32 delta_r = 0;

  TRBSYS_setSynctimeTickCtr(timerSyncValue);
  TRBSYS_setRealtimeTickCtr(timerRtValue);

  /* 1st sequence: init_done 0 --> 1 */
  RBSYS_PRC_TimerMonitoring();

  /* 2nd sequence */
  delta_r = 200 - timerRtValue;
  delta_s = TIMERMON_LOWER_LIMIT(delta_r); // calculate lower allowed limit for delta_s
  timerSyncValue += delta_s;
  timerRtValue += delta_r;

  TRBSYS_setSynctimeTickCtr(timerSyncValue);
  TRBSYS_setRealtimeTickCtr(timerRtValue);

  //(delta_s <= delta_r_lo) --> TRUE
  RBSYS_PRC_TimerMonitoring();

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_dev__debug(), delta_s);
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_dev__debug(), delta_r);
  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_last(), timerSyncValue );
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_last(), timerRtValue);
  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
}


/**
 * \Reference
 *  RBSYS_PRC_TimerMonitoring, Gen_SWCS_HSW_uC_Base_SYS-253
 *
 * \Purpose
 *  Fault case of timer monitoring (timer stopped)
 *
 * \Sequence
 *  Initialize sync and real time
 *  Call process RBSYS_PRC_TimerMonitoring first time
 *  Do not modify sync and real time as if timer has stopped
 *  Call process RBSYS_PRC_TimerMonitoring second time
 *
 * \ExpectedResult
 *  SYSErrorHook fault entry must be available
 */
SWTEST void TRBSYS_PRC_TimerMonitoring_FaultCase3(void)
{
  uint32 timerSyncValue = 10;
  uint32 timerRtValue = 10;

  TRBSYS_setSynctimeTickCtr(timerSyncValue);
  TRBSYS_setRealtimeTickCtr(timerRtValue);

  /* 1st sequence: init_done 0 --> 1 */
  RBSYS_PRC_TimerMonitoring();

  /* 2nd sequence */
  // Do not modify SynctimeTickCtr and RealtimeTickCtr
  //delta_s = 10-10 = 0
  //delta_r = 10-10 = 0   -->   delta_r_hi = 0 (+50) = 50   delta_r_lo = 0 (-50) = 0

  //(delta_s <= delta_r_lo) --> TRUE
  RBSYS_PRC_TimerMonitoring();

  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_dev__debug(), 0 /*delta_s*/);
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_dev__debug(), 0 /*delta_r*/);
  SWT_EvalEq(GetPrivate_TimerMonitoring_sync_last(), timerSyncValue );
  SWT_EvalEq(GetPrivate_TimerMonitoring_rt_last(), timerRtValue);
  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
}


#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

#define TAUD_TICKS_PER_US (40)
#if (RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
  #define TAUD_TICKS_PER_INTERRUPT (500 * TAUD_TICKS_PER_US)
#else
  #define TAUD_TICKS_PER_INTERRUPT (1000 * TAUD_TICKS_PER_US)
#endif

#if (RBFS_TaskSync == RBFS_TaskSync_ON)
  #define TAUD_TICKS_MAX_FLEXRAY_DEVIATION ((RBSYS_TASKSCHEME_ADJUST_MAX_PERCENT * TAUD_TICKS_PER_INTERRUPT) / 100)
  #define TAUD_TICKS_MAX_DEVIATION ((uint32) ((TAUD_TICKS_PER_INTERRUPT / 100) + TAUD_TICKS_MAX_FLEXRAY_DEVIATION))
#else
  #define TAUD_TICKS_MAX_DEVIATION (TAUD_TICKS_PER_INTERRUPT / 100)
#endif

/**
 * \Reference
 *  RBSYS_PRC_TimerInterruptMonitoring, Gen_SWCS_HSW_uC_Base_SYS-326
 *
 * \Purpose
 *  Good case of timer interrupt monitoring
 *
 * \Sequence
 *  Call process RBSYS_PRC_TimerInterruptMonitoring two times to initialize it
 *  Set TAUD0CDR0 and TAUD0CSR0 to valid values
 *  Call process RBSYS_PRC_TimerInterruptMonitoring
 *
 * \ExpectedResult
 *  No fault entry of SYSErrorHook
 */

SWTEST void TRBSYS_PRC_TimerInterruptMonitoring_GoodCase_1(void)
{
  //first call: initialization
  RBSYS_PRC_TimerInterruptMonitoring();

  //init done, no fault set
  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);

  SWT_EvalEq(TRBSYS_TAUD0_SetToRunMode_GetCallCount(), 1);
  SWT_EvalEq(TAUD0TPS, 0x1);
  SWT_EvalEq(TAUD0CMOR0, 0x144);
  SWT_EvalEq(TAUD0CMUR0, 0x2);
  SWT_EvalEq(TAUD0TS, 0x1);
  SWT_EvalEq(PIC1REG31, (0x31 << 6));
  SWT_EvalEq(PIC1TAUD0SEL, ~0x3Fu);
  SWT_EvalEq(PIC1REG30, ~((0x1u << 22) | (0x3u << 16) | 0x3u));
  SWT_EvalEq(PIC1INI01 & 0x7, 0x0);

  //second call: do nothing
  RBSYS_PRC_TimerInterruptMonitoring();

  //no fault set despite captured value being invalid
  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);

  //set captured value
  TAUD0CDR0 = TAUD_TICKS_PER_INTERRUPT - 1;
  TAUD0CSR0 = 0;

  //third call: first monitoring
  RBSYS_PRC_TimerInterruptMonitoring();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
}

/**
 * \Reference
 *  RBSYS_PRC_TimerInterruptMonitoring, Gen_SWCS_HSW_uC_Base_SYS-326
 *
 * \Purpose
 *  Fault case of timer monitoring (just outside lower limit)
 *
 * \Sequence
 *  Call process RBSYS_PRC_TimerInterruptMonitoring two times to initialize it
 *  Set TAUD0CDR0 to lower than valid value, set TAUD0CSR0 to zero (no overflow)
 *  Call process RBSYS_PRC_TimerInterruptMonitoring
 *
 * \ExpectedResult
 *  SYSErrorHook fault entry must be available
 */

SWTEST void TRBSYS_PRC_TimerInterruptMonitoring_FaultCase_1(void)
{
  //first call: initialization
  RBSYS_PRC_TimerInterruptMonitoring();

  //init done, no fault set
  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);

  SWT_EvalEq(TRBSYS_TAUD0_SetToRunMode_GetCallCount(), 1);
  SWT_EvalEq(TAUD0TPS, 0x1);
  SWT_EvalEq(TAUD0CMOR0, 0x144);
  SWT_EvalEq(TAUD0CMUR0, 0x2);
  SWT_EvalEq(TAUD0TS, 0x1);
  SWT_EvalEq(PIC1REG31, (0x31 << 6));
  SWT_EvalEq(PIC1TAUD0SEL, ~0x3Fu);
  SWT_EvalEq(PIC1REG30, ~((0x1u << 22) | (0x3u << 16) | 0x3u));
  SWT_EvalEq(PIC1INI01 & 0x7, 0x0);

  //second call: do nothing
  RBSYS_PRC_TimerInterruptMonitoring();

  //no fault set despite captured value being invalid
  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);

  //set captured value
  TAUD0CDR0 = TAUD_TICKS_PER_INTERRUPT - TAUD_TICKS_MAX_DEVIATION - TAUD_TICKS_PER_US - 1;
  TAUD0CSR0 = 0;

  //third call: first monitoring
  RBSYS_PRC_TimerInterruptMonitoring();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_TimerInterruptMonitoring);
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TAUD_TICKS_PER_INTERRUPT - TAUD_TICKS_MAX_DEVIATION - TAUD_TICKS_PER_US);
}

/**
 * \Reference
 *  RBSYS_PRC_TimerInterruptMonitoring, Gen_SWCS_HSW_uC_Base_SYS-326
 *
 * \Purpose
 *  Fault case of timer monitoring (just outside upper limit)
 *
 * \Sequence
 *  Call process RBSYS_PRC_TimerInterruptMonitoring two times to initialize it
 *  Set TAUD0CDR0 to higher than valid value, set TAUD0CSR0 to zero (no overflow)
 *  Call process RBSYS_PRC_TimerInterruptMonitoring
 *
 * \ExpectedResult
 *  SYSErrorHook fault entry must be available
 */

SWTEST void TRBSYS_PRC_TimerInterruptMonitoring_FaultCase_2(void)
{
  //first call: initialization
  RBSYS_PRC_TimerInterruptMonitoring();

  //init done, no fault set
  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);

  SWT_EvalEq(TRBSYS_TAUD0_SetToRunMode_GetCallCount(), 1);
  SWT_EvalEq(TAUD0TPS, 0x1);
  SWT_EvalEq(TAUD0CMOR0, 0x144);
  SWT_EvalEq(TAUD0CMUR0, 0x2);
  SWT_EvalEq(TAUD0TS, 0x1);
  SWT_EvalEq(PIC1REG31, (0x31 << 6));
  SWT_EvalEq(PIC1TAUD0SEL, ~0x3Fu);
  SWT_EvalEq(PIC1REG30, ~((0x1u << 22) | (0x3u << 16) | 0x3u));
  SWT_EvalEq(PIC1INI01 & 0x7, 0x0);

  //second call: do nothing
  RBSYS_PRC_TimerInterruptMonitoring();

  //no fault set despite captured value being invalid
  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);

  //set captured value
  TAUD0CDR0 = TAUD_TICKS_PER_INTERRUPT + TAUD_TICKS_MAX_DEVIATION + TAUD_TICKS_PER_US - 1;
  TAUD0CSR0 = 0;

  //third call: first monitoring
  RBSYS_PRC_TimerInterruptMonitoring();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_TimerInterruptMonitoring);
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TAUD_TICKS_PER_INTERRUPT + TAUD_TICKS_MAX_DEVIATION + TAUD_TICKS_PER_US);
}

/**
 * \Reference
 *  RBSYS_PRC_TimerInterruptMonitoring, Gen_SWCS_HSW_uC_Base_SYS-326
 *
 * \Purpose
 *  Fault case of timer monitoring (counter overflow)
 *
 * \Sequence
 *  Call process RBSYS_PRC_TimerInterruptMonitoring two times to initialize it
 *  Set TAUD0CDR0 to valid value, set TAUD0CSR0 to one (overflow)
 *  Call process RBSYS_PRC_TimerInterruptMonitoring
 *
 * \ExpectedResult
 *  SYSErrorHook fault entry must be available
 */

SWTEST void TRBSYS_PRC_TimerInterruptMonitoring_FaultCase_3(void)
{
  //first call: initialization
  RBSYS_PRC_TimerInterruptMonitoring();

  //init done, no fault set
  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);

  SWT_EvalEq(TRBSYS_TAUD0_SetToRunMode_GetCallCount(), 1);
  SWT_EvalEq(TAUD0TPS, 0x1);
  SWT_EvalEq(TAUD0CMOR0, 0x144);
  SWT_EvalEq(TAUD0CMUR0, 0x2);
  SWT_EvalEq(TAUD0TS, 0x1);
  SWT_EvalEq(PIC1REG31, (0x31 << 6));
  SWT_EvalEq(PIC1TAUD0SEL, ~0x3Fu);
  SWT_EvalEq(PIC1REG30, ~((0x1u << 22) | (0x3u << 16) | 0x3u));
  SWT_EvalEq(PIC1INI01 & 0x7, 0x0);

  //second call: do nothing
  RBSYS_PRC_TimerInterruptMonitoring();

  //no fault set despite captured value being invalid
  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);

  //set captured value
  TAUD0CDR0 = TAUD_TICKS_PER_INTERRUPT - 1;
  TAUD0CSR0 = 1;

  //third call: first monitoring
  RBSYS_PRC_TimerInterruptMonitoring();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_TimerInterruptMonitoring);
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (1 << 16) | TAUD_TICKS_PER_INTERRUPT);
}

#endif /* RBFS_uCFamily_RenesasU2A */



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