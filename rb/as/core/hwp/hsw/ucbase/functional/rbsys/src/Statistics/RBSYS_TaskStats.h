#ifndef RBSYS_TASKSTATS_H__
#define RBSYS_TASKSTATS_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Task/ISR statistics
 *
 * This internal interface provides for tasks and ISRs statistics like slack time, response time,
 * timestamps for activation, start & end.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include <assert.h>               // for static_assert()
#include "Os.h"
#include "RBSYS_OsServices.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSchemeExtension,
                          RBFS_TaskSchemeExtension_None,
                          RBFS_TaskSchemeExtension_VMPS,
                          RBFS_TaskSchemeExtension_HostCore0GuestCore1,
                          RBFS_TaskSchemeExtension_AB15);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysResettableSlackTimesSupport,
                          RBFS_SysResettableSlackTimesSupport_ON,
                          RBFS_SysResettableSlackTimesSupport_OFF);


/* Temporary workaround as long as GenProDB does not support 'U' suffix from OS_NUM_TASKS).
  But as long as MTC less than 10.7 is still used this needs to be considered.
  https://rb-ubk-clm-02.de.bosch.com:9443/ccm/web/projects/CC%20Tools%20%28ccm%29#action=com.ibm.team.workitem.viewWorkItem&id=148743
  https://abt-ismbugzilla.abt.de.bosch.com/bugzilla/show_bug.cgi?id=47590 */
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  #define RBSYS_TASK_SIZE_4_GENPRODB    (18)
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  #define RBSYS_TASK_SIZE_4_GENPRODB    (19)
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  #define RBSYS_TASK_SIZE_4_GENPRODB    (16)
#else
  #define RBSYS_TASK_SIZE_4_GENPRODB    (14)
#endif
static_assert(RBSYS_TASK_SIZE_4_GENPRODB == OS_NUM_TASKS, "Number of Tasks are not matching for GenProDB!");


#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
    #define RBSYS_ISR_SIZE_4_GENPRODB     (14)
  #else
    #define RBSYS_ISR_SIZE_4_GENPRODB     (13)
  #endif
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  #define RBSYS_ISR_SIZE_4_GENPRODB     (15)
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  #define RBSYS_ISR_SIZE_4_GENPRODB     (12)
#else
  #define RBSYS_ISR_SIZE_4_GENPRODB     (1)
  #warning("ToDo: RBSYS Stellar support")
#endif
static_assert(RBSYS_ISR_SIZE_4_GENPRODB == OS_NUM_ISRS, "Number of ISRs are not matching for GenProDB!");


/* labels for MM6 measurement, order does not matter
   enum is evaluated in resources tracking sheet, any changes must be discussed with resources tracking responsible */
typedef enum  /*TOOL_SCAN*/
{
  RBSYS_TaskInit = 0,
  RBSYS_TaskInitP,
  RBSYS_Task0p5ms,
  RBSYS_Task1ms,
  RBSYS_TaskBaseCtrlCycx1High,
  RBSYS_TaskFlexray,
  RBSYS_TaskBaseCtrlCycx1Low,
  RBSYS_TaskBaseCtrlCycx2,
  RBSYS_TaskBaseCtrlCycx2p,
  RBSYS_TaskBaseCtrlCycx4,
  RBSYS_TaskBaseCtrlCycx8,
  RBSYS_TaskBaseCtrlCycx24,
  RBSYS_TaskTPSWKillCore0,
  RBSYS_TaskTPSWKillCore1,
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    RBSYS_ISRSTM04,
    RBSYS_ISRSTM05,
    RBSYS_ISRSWINT0,
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      RBSYS_ISRMTTCANI0,
      RBSYS_ISRMCAN0I0,
      RBSYS_ISRMCAN1I0,
      RBSYS_ISRMCAN2I0,
    #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      // todo: adapt this when U2C OS is available
      RBSYS_ISRCAN0REC,
      RBSYS_ISRCAN0TRX,
      RBSYS_ISRCAN1REC,
      RBSYS_ISRCAN1TRX,
      RBSYS_ISRCAN2REC,
      RBSYS_ISRCAN2TRX,
      #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
        RBSYS_ISRCAN6REC,
        RBSYS_ISRCAN6TRX,
        RBSYS_ISRCAN8REC,
        RBSYS_ISRCAN8TRX,
      #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
        RBSYS_ISRCAN3REC,
        RBSYS_ISRCAN3TRX,
      #endif
    #endif
    RBSYS_ISRFLX0LINE0,
    #if( RBFS_uCFamily != RBFS_uCFamily_RenesasU2C )
      RBSYS_ISRFLX1LINE0,
    #endif
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      RBSYS_ISRRLIN30RX,
      RBSYS_ISRRLIN30STATUS,
      RBSYS_ISRRLIN31RX,
      RBSYS_ISRRLIN31STATUS,
    #endif
    //place task scheme extensions at the back so that standard tasks and isrs stats keep their index for the resource tracking sheet
    #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
      RBSYS_TaskBaseCtrlCycx4pLow,
      RBSYS_TaskBaseCtrlCycx200Background,
      RBSYS_TaskEventCtrlExtPrio1,
      RBSYS_TaskEventCtrlExtPrio2,
    #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
      RBSYS_TaskBaseCtrlCycx1Guest,
      RBSYS_TaskBaseCtrlCycx2Guest,
      RBSYS_TaskBaseCtrlCycx4Guest,
      RBSYS_TaskBaseCtrlCycx10Guest,
      RBSYS_TaskBaseCtrlCycx20Guest,
    #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
      RBSYS_ISR0p5ms,
      RBSYS_TaskBaseCtrlCycx10,
      RBSYS_TaskBaseCtrlCycx20,
    #endif
  #else
    RBSYS_ISRCommonTimer,
  #endif
}RBSYS_taskstats_ids_t;

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #warning("TaskStats are not implemented for STM Stellar ISRs")
#endif


typedef struct  /*TOOL_SCAN*/
{
  RBSYS_taskstats_ids_t id; /*FORMULA=RBSYS_taskstats_ids_t*/  // just an ID for MM6 purposes => filled during init
  uint32 ts_activation;  // virtual activation time in ISR, updated for all cyclic tasks activated within this cycle (e.g. ts of x1 activation time will be used also for x2, x4, x8 depending on activation cycle)
  uint32 ts_start;       // in Os_Cbk_TaskStart
  uint32 ts_end;         // in Os_Cbk_TaskEnd
  //uint32 net;          // done by rba_Runtime
  uint32 gross;          // start until end
  uint32 resp_time;      // tasks only: time from activation until task finished
  uint32 slack_time;     // tasks only: time from task finished until next activation isr
  uint32 resp_time_max;
  uint32 gross_max;
  uint32 slack_time_min;
  uint32 current_task_cnt;
  uint32 slack_time_min_task_cnt; // timestamp (task counter) when the min slack time was recorded
  uint32 slack_time_min_resettable;
  uint32 slack_time_min_resettable_task_cnt;
}RBSYS_TaskStatsTASK_t;

typedef struct  /*TOOL_SCAN*/
{
  RBSYS_taskstats_ids_t id; /*FORMULA=RBSYS_taskstats_ids_t*/  // just an ID for MM6 purposes => filled during init
  uint32 ts_start;       // in Os_Cbk_TaskStart
  uint32 ts_end;         // in Os_Cbk_TaskEnd
  uint32 gross;          // start until end
  uint32 gross_max;
} RBSYS_TaskStatsISR_t;


/* note: response time cannot be calculated using OS API or rba_Runtime
   because OS/rba_Runtime take the timestamp from ActivateTask which happens at
   the end of the task; We need the timestamp from the x1 isr which checks
   also that all tasks to be activated are finished at that time
*/


extern RBSYS_TaskStatsTASK_t RBSYS_taskstats_tasks[OS_NUM_TASKS];
extern RBSYS_TaskStatsISR_t RBSYS_taskstats_isrs[OS_NUM_ISRS];


/* called in isr */
static inline void set_task_activation_ts(TaskType task, uint32 ts)
{
  RBSYS_TaskStatsTASK_t* act = &RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)];
  act->ts_activation = ts;

  // do slack_time calc after 2nd activation
  if ((act->ts_end != 0) || (act->slack_time_min != 0xFFFFFFFFU))
  {
    act->slack_time = act->ts_activation - act->ts_end;
    if(act->slack_time < act->slack_time_min)
    {
        act->slack_time_min = act->slack_time;
        act->slack_time_min_task_cnt = act->current_task_cnt;
    }

    #if( RBFS_SysResettableSlackTimesSupport == RBFS_SysResettableSlackTimesSupport_ON )
      if( act->slack_time < act->slack_time_min_resettable )
      {
        act->slack_time_min_resettable = act->slack_time;
        act->slack_time_min_resettable_task_cnt = act->current_task_cnt;
      }
    #endif

  }
}

/* called in os hook */
static inline void set_task_start_ts(TaskType task, uint32 ts)
{
  RBSYS_TaskStatsTASK_t* act = &RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)];
  act->ts_start = ts;
}

/* called in os hook */
static inline void set_task_end_ts(TaskType task, uint32 ts)
{
  RBSYS_TaskStatsTASK_t* act = &RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)];
  act->ts_end = ts;
  act->gross = act->ts_end - act->ts_start;
  act->resp_time = act->ts_end - act->ts_activation;

  act->gross_max = (act->gross > act->gross_max) ? act->gross : act->gross_max;
  act->resp_time_max = (act->resp_time > act->resp_time_max) ? act->resp_time : act->resp_time_max;
}

static inline void set_isr_start_ts(ISRType isr, uint32 ts)
{
  RBSYS_TaskStatsISR_t* act = &RBSYS_taskstats_isrs[OS_ISRTYPE_TO_INDEX(isr)];
  act->ts_start = ts;
}

static inline void set_isr_end_ts(ISRType isr, uint32 ts)
{
  RBSYS_TaskStatsISR_t* act = &RBSYS_taskstats_isrs[OS_ISRTYPE_TO_INDEX(isr)];
  act->ts_end = ts;
  act->gross = act->ts_end - act->ts_start;

  act->gross_max = (act->gross > act->gross_max) ? act->gross : act->gross_max;
}

// Refer Task 775540
static inline void set_current_task_cnt(TaskType task, uint32 taskcnt)
{
  RBSYS_TaskStatsTASK_t* act = &RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)];
  act->current_task_cnt = taskcnt;
}


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
