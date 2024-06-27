/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Task jitter monitoring
 *
 * In addition to the normal OS task monitoring, which allows 100% task jitter,
 * some signal chains have stricter requirements. Therefore further monitoring
 * is necessary.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_SystemTimer.h"
#include "RBSYS_TaskInfo.h"
#include "RBSYS_ErrorHooks.h"

/* realized interfaces */
#include "RBSYS_TaskJitter.h"
#include "RBSYS_Subsystem.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysMaxTaskx1Jitter,
                          RBFS_SysMaxTaskx1Jitter_5,
                          RBFS_SysMaxTaskx1Jitter_15,
                          RBFS_SysMaxTaskx1Jitter_SERIES);



static __attribute__((used)) sint32 RBSYS_JitterInfoTask_x1_s32;
/*[[MEASUREMENT*/
/*NAME=RBSYS_JitterInfoTask_x1_s32*/
/*COMMENT=Jitter of x1 Task*/
/*MTEVENT=c_MT_Default_Task_x1*/
/*]]MEASUREMENT*/


/**
 * @brief Jitter monitoring of x1 task
 *
 * This jitter check is implemented to monitor the task jitter for some sensitive processes
 * at the beginning of BaseCtrlx1 (5ms) task. It works in the way that this jitter monitor
 * process at specific location in the BaseCtrlx1 task checks the difference in time between
 * the current and the last point of this process execution against the ideal task cycle time
 * +/- an allowed jitter.
 *
 * This realization of the jitter monitor can detect immediate delays due to higher priority
 * tasks or interrupts greater than the allowed jitter. It is possible that the execution
 * delays more than the max. jitter from ideal point in time by accumulating a delay over more
 * than one task - means max. jitter is allowed in every task cycle again. This is considered
 * to be ok for the application and improbable.
 *
 * Hint: An overall jitter accumulation is restricted by the task cycle time monitored by the OS and TaskMon.
 *
 * @return void
 */
void RBSYS_PRC_JitterMonitoring_x1(void)
{
  static boolean active;
  static uint32 last_timestamp_u32;
  /*[[MEASUREMENT*/
  /*NAME=last_timestamp_u32*/
  /*MODEL_NAME=RBSYS_JitterMonitoring_x1_LastTimeStamp*/
  /*COMMENT=Last time stamp of x1 jitter monitor process required for test automation*/
  /*MTEVENT=c_MT_Default_Task_x1*/
  /*]]MEASUREMENT*/

  uint32 current_timestamp_u32 = RBSYS_getSynctimeTickCtr();

  if (active)
  {
    uint32 delta_u32 = current_timestamp_u32 - last_timestamp_u32;
    sint32 jitter_s32 = (sint32)delta_u32 - TIMERTICKS_PER_TASK_X1;

    RBSYS_JitterInfoTask_x1_s32 = jitter_s32;

    // no failure reporting in case of series / release builds
    #if (RBFS_SysMaxTaskx1Jitter != RBFS_SysMaxTaskx1Jitter_SERIES)
      if ((jitter_s32 > JITTER_LIMIT_TASK_X1) || (jitter_s32 < (-JITTER_LIMIT_TASK_X1)))
      {
        RBSYS_setTaskJitterError((uint32)TIMERTICKS_PER_TASK_X1, (uint32)jitter_s32);
      }
    #endif
  }
  else
  {
    active = TRUE;

    #if (RBFS_SysMaxTaskx1Jitter != RBFS_SysMaxTaskx1Jitter_SERIES)
      /* trigger good check in first task run after reset: jitter is calibrated and ok by definition */
      RBSYS_setGoodCheckRequest(DemConf_DemEventParameter_RBSYS_TaskJitter);
    #endif
  }

  last_timestamp_u32 = current_timestamp_u32;

}




/** @} */
/* End ingroup RBSYS */
