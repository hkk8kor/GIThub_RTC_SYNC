#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                      // for RBFS_BUILDCONFIG_
#include "RBSYS_SystemTimer.h"
#include "TRBSYS_SystemTimer.h"

#include "Statistics/RBSYS_StartupTimingIntern.h"
#include "TRBSYS_StartupTiming_Adaptor.h"
#include "RBSYS_Subsystem.h"


/**
 * \Reference
 *  RBSYS_SetStartupTimestamp, Gen_SWCS_HSW_uC_Base_SYS-250
 *
 * \Purpose
 *  Verify startup timestamps for the uC startup measurement
 *
 * \Sequence
 *  Simulate consecutive timer base (via RBSYS_getRealtimeTickCtr)
 *  Call function RBSYS_SetStartupTimestamp with corresponding startup phases
 *
 * \ExpectedResult
 *  Within valid phases the corresponding time stamp must be stored
 *  Outside the valid phases an assert must occur
 */
SWTEST void TRBSYS_SetStartupTimestamp(void)
{
  uint8 phase;

  /* verify good cases */
  for(phase = RBSYS_TimestampBeforeCinit; phase < RBSYS_MaxNumberOfStartupTimestamps; phase++)
  {
    uint32* startupTimestamp = GetPrivate_RBSYS_StartupTimestamp();

    TRBSYS_setRealtimeTickCtr(phase * 10);
    RBSYS_SetStartupTimestamp((RBSYS_StartupTimestamps_t) phase);

    SWT_EvalEq(startupTimestamp[phase], (phase * 10) );
  }


  /* verify bad case with assert check */
  SWT_AssertCheckDestructiveStart("RBSYS_SetStartupTimestamp", "phase < RBSYS_MaxNumberOfStartupTimestamps");
  RBSYS_SetStartupTimestamp(RBSYS_MaxNumberOfStartupTimestamps);
  SWT_AssertCheckDestructiveEnd_NeverReached();
}


/**
 * \Reference
 *  RBSYS_StartupTimeStampInMicroSecs, Gen_SWCS_HSW_uC_Base_SYS-250
 *
 * \Purpose
 *  Verify startup timestamps retrieval for TSI in microsecs
 *
 * \Sequence
 *  Simulate consecutive timer base (via RBSYS_getRealtimeTickCtr)
 *  Call function RBSYS_SetStartupTimestamp with corresponding startup phases
 *  Call function RBSYS_StartupTimeStampInMicroSecs with corresponding startup phases and check values
 *
 * \ExpectedResult
 *  Within valid phases the corresponding time stamp must be stored
 *  Outside the valid phases an assert must occur
 */
SWTEST void TRBSYS_StartupTimeStampInMicroSecs(void)
{
  uint8 phase;
  uint32 microSecStartupTimestamp;

  /* verify good cases */
  for(phase = RBSYS_TimestampBeforeCinit; phase < RBSYS_MaxNumberOfStartupTimestamps; phase++)
  {
    TRBSYS_setRealtimeTickCtr(phase * 10 * RBSYS_TIMERTICKS_PER_US);
    RBSYS_SetStartupTimestamp((RBSYS_StartupTimestamps_t) phase);

    microSecStartupTimestamp = RBSYS_StartupTimeStampInMicroSecs((RBSYS_StartupTimestamps_t) phase);
    SWT_EvalEq(microSecStartupTimestamp, (phase * 10) );
  }


  /* verify bad case with assert check */
  SWT_AssertCheckDestructiveStart("RBSYS_StartupTimeStampInMicroSecs", "phase < RBSYS_MaxNumberOfStartupTimestamps");
  RBSYS_StartupTimeStampInMicroSecs(RBSYS_MaxNumberOfStartupTimestamps);
  SWT_AssertCheckDestructiveEnd_NeverReached();
}

/**
 * \Reference
 *  RBSYS_SetInitTaskTimestamp
 *
 * \Purpose
 *  Verify Init task timestamps for the uC startup measurement
 *
 * \Sequence
 *  Simulate consecutive timer base (via RBSYS_getRealtimeTickCtr)
 *  Call function RBSYS_SetInitTaskTimestamp with corresponding init task
 *
 * \ExpectedResult
 *  Within valid tasks the corresponding time stamp must be stored
 *  Outside the valid tasks an assert must occur
 */
SWTEST void TRBSYS_SetInitTaskTimestamp(void)
{
  uint8 task;

  /* verify good cases */
  for(task = RBSYS_TimestampInitTask; task < RBSYS_MaxNumberOfInitTaskTimestamps; task++)
  {
    uint32* initTaskTimestamp = GetPrivate_RBSYS_InitTaskTimestamp();

    TRBSYS_setRealtimeTickCtr(task * 10);
    RBSYS_SetInitTaskTimestamp((RBSYS_InitTaskTimestamps_t) task);

    SWT_EvalEq(initTaskTimestamp[task], (task * 10) );
  }


  /* verify bad case with assert check */
  SWT_AssertCheckDestructiveStart("RBSYS_SetInitTaskTimestamp", "task < RBSYS_MaxNumberOfInitTaskTimestamps");
  RBSYS_SetInitTaskTimestamp(RBSYS_MaxNumberOfStartupTimestamps);
  SWT_AssertCheckDestructiveEnd_NeverReached();
}
