/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Startup timing
 *
 * This module provide time stamps for CC CUBE startup time measurement.
 * Due to the fact that uC internal system timer is used below hardware timings are not considered:
 *
 * HW Power Up:
 *  - uC reset release from ASIC                  max.  9 [ms]
 *  - uC BIST (including HW based RAM zeroing)    max. 22 [ms]
 *
 * Also bootblock runtime is not considered, because timer is re-initialized within application software.
 *
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_SystemTimer.h"
#include "RBLCF_MemoryRemap.h"
#include <assert.h>

/* realized interfaces */
#include "RBSYS_StartupTimingExtern.h"
#include "RBSYS_StartupTimingIntern.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_GlobalRamSupport,
                          RBFS_GlobalRamSupport_ON,
                          RBFS_GlobalRamSupport_OFF);


/* timestamps are copied before cinit to this array, therefore allocation must be done into a noclear section */
#if(RBFS_GlobalRamSupport == RBFS_GlobalRamSupport_ON)
  RBSECTION_START_GRAM_BSS_NOCLEAR
#else
  RBSECTION_START_LRAM0_BSS_NOCLEAR
#endif

  static uint32 RBSYS_StartupTimestamp[RBSYS_MaxNumberOfStartupTimestamps];

#if(RBFS_GlobalRamSupport == RBFS_GlobalRamSupport_ON)
  RBSECTION_END_GRAM_BSS_NOCLEAR
#else
  RBSECTION_END_LRAM0_BSS_NOCLEAR
#endif


/*[[MEASUREMENT*/
/*NAME=RBSYS_StartupTimestamp[RBSYS_TimestampBeforeCinit]*/
/*MODEL_NAME=RBSYS_StartupTimestamp_BeforeCinit*/
/*COMMENT= 1st time-stamp from timer initialization till startup phase directly before cinit [timer ticks] */
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBSYS_StartupTimestamp[RBSYS_TimestampAfterCinit]*/
/*MODEL_NAME=RBSYS_StartupTimestamp_AfterCinit*/
/*COMMENT=2nd time-stamp from timer initialization till startup phase after cinit [timer ticks] */
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBSYS_StartupTimestamp[RBSYS_TimestampBeforeSafety]*/
/*MODEL_NAME=RBSYS_StartupTimestamp_BeforeSafety*/
/*COMMENT=3rd time-stamp from timer initialization till startup phase before uC safety tests [timer ticks] */
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBSYS_StartupTimestamp[RBSYS_TimestampAfterSafety]*/
/*MODEL_NAME=RBSYS_StartupTimestamp_AfterSafety*/
/*COMMENT=4th time-stamp from timer initialization till startup phase after uC safety tests [timer ticks] */
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBSYS_StartupTimestamp[RBSYS_TimestampBeforeOS]*/
/*MODEL_NAME=RBSYS_StartupTimestamp_BeforeOS*/
/*COMMENT=5th time-stamp from timer initialization till startup phase directly before OS start [timer ticks] */
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/

uint32 RBSYS_InitTaskTimestamp[RBSYS_MaxNumberOfInitTaskTimestamps];

/*[[MEASUREMENT*/
/*NAME=RBSYS_InitTaskTimestamp[RBSYS_TimestampInitTask]*/
/*MODEL_NAME=RBSYS_Timestamp_InitTask*/
/*COMMENT=Timestamp when the InitTask finished*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBSYS_InitTaskTimestamp[RBSYS_TimestampInitTaskP]*/
/*MODEL_NAME=RBSYS_Timestamp_InitTaskP*/
/*COMMENT=Timestamp when the InitTaskP finished*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/

/**
 * @brief Set corresponding startup time stamp
 *
 * This function must be called during startup at the corresponding phases (see enum #RBSYS_StartupTimestamps_t)
 * to provide relevant time stamps for startup time measurement within projects using MM6 (without trace). Use #RBSYS_timer_freq_mhz
 * to convert system timer ticks.
 *
 * @param [in] phase  corresponding startup time phase
 *
 * @return void
 */
void RBSYS_SetStartupTimestamp(RBSYS_StartupTimestamps_t phase)
{
  /* parameter phase must be in the range specified by the enum */
  assert(phase < RBSYS_MaxNumberOfStartupTimestamps);

  RBSYS_StartupTimestamp[phase] = RBSYS_getRealtimeTickCtr();
}

/**
 * @brief RBSYS_StartupTimeStampInMicroSecs(RBSYS_StartupTimestamps_t phase)
 *
 * Official interface to retrieve timestamps taken during Sys-Startup (e.g. for TSI)
 *
 * @return uint32
 */

uint32 RBSYS_StartupTimeStampInMicroSecs(RBSYS_StartupTimestamps_t phase)
{
  uint32 timeInMicroSecs = 0;

  /* parameter phase must be in the range specified by the enum */
  assert(phase < RBSYS_MaxNumberOfStartupTimestamps);

  timeInMicroSecs = RBSYS_convertTimerTicksToUsec(RBSYS_StartupTimestamp[phase]);

  return timeInMicroSecs;
}

/**
 * @brief Set the corresponding init task time stamp
 *
 * This function must be called at the end of each init task (see enum #RBSYS_InitTaskTimestamps_t)
 * to provide relevant time stamps for init task completion within projects using MM6. Use #RBSYS_timer_freq_mhz to convert system timer ticks.
 *
 * @param[in] task  corresponding init task
 *
 * @return void
 */
void RBSYS_SetInitTaskTimestamp(RBSYS_InitTaskTimestamps_t task)
{
  assert(task < RBSYS_MaxNumberOfInitTaskTimestamps);

  RBSYS_InitTaskTimestamp[task] = RBSYS_getRealtimeTickCtr();
}


/** @} */
/* End ingroup RBSYS */
