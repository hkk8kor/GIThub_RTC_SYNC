/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Task/ISR statistics
 *
 * This module provides for tasks and ISRs statistics like slack time, response time,
 * timestamps for activation, start & end and also the timestamps(task counter) when the min slack time was recorded.
 *
 * To get also the task and ISR statistic values on MM6 measurement technique the corresponding
 * structures are mapped here to MM6 measurement comments.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* realized interfaces */
#include "RBSYS_TaskStats.h"
#include "RBSYS_TaskInfo.h"
#include "RBSYS_Subsystem.h"


/* used interfaces */
#include <assert.h>               // for static_assert()
#include "RBSYS_OsServices.h"
#include "Os.h"
#include "rba_Runtime.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysResettableSlackTimesSupport,
                          RBFS_SysResettableSlackTimesSupport_ON,
                          RBFS_SysResettableSlackTimesSupport_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSchemeExtension,
                          RBFS_TaskSchemeExtension_None,
                          RBFS_TaskSchemeExtension_VMPS,
                          RBFS_TaskSchemeExtension_HostCore0GuestCore1,
                          RBFS_TaskSchemeExtension_AB15);


typedef struct
{
  TaskType task;
  RBSYS_taskstats_ids_t id;
}RBSYS_taskstatsTaskTable_t;

typedef struct
{
  ISRType isr;
  RBSYS_taskstats_ids_t id;
}RBSYS_taskstatsIsrTable_t;

/* table for mapping os taskname to MM6 ID, order does not matter - same envelop used as on OS config */
static const RBSYS_taskstatsTaskTable_t RBSYS_taskstatsTasks[] = {
                            {TaskInit,                      RBSYS_TaskInit},
                            {TaskInitP,                     RBSYS_TaskInitP},
                            {Task0p5ms,                     RBSYS_Task0p5ms},
                            {Task1ms,                       RBSYS_Task1ms},
                            {TaskBaseCtrlCycx1High,         RBSYS_TaskBaseCtrlCycx1High},
                            {TaskFlexray,                   RBSYS_TaskFlexray},
                            {TaskBaseCtrlCycx1Low,          RBSYS_TaskBaseCtrlCycx1Low},
                            {TaskBaseCtrlCycx2,             RBSYS_TaskBaseCtrlCycx2},
                            {TaskBaseCtrlCycx2p,            RBSYS_TaskBaseCtrlCycx2p},
                            {TaskBaseCtrlCycx4,             RBSYS_TaskBaseCtrlCycx4},
                            {TaskBaseCtrlCycx8,             RBSYS_TaskBaseCtrlCycx8},
                            {TaskBaseCtrlCycx24,            RBSYS_TaskBaseCtrlCycx24},
                          #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
                            {TaskBaseCtrlCycx4pLow,         RBSYS_TaskBaseCtrlCycx4pLow},
                            {TaskBaseCtrlCycx200Background, RBSYS_TaskBaseCtrlCycx200Background},
                            {TaskEventCtrlExtPrio1,         RBSYS_TaskEventCtrlExtPrio1},
                            {TaskEventCtrlExtPrio2,         RBSYS_TaskEventCtrlExtPrio2},
                          #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
                            {TaskBaseCtrlCycx1Guest,        RBSYS_TaskBaseCtrlCycx1Guest},
                            {TaskBaseCtrlCycx2Guest,        RBSYS_TaskBaseCtrlCycx2Guest},
                            {TaskBaseCtrlCycx4Guest,        RBSYS_TaskBaseCtrlCycx4Guest},
                            {TaskBaseCtrlCycx10Guest,       RBSYS_TaskBaseCtrlCycx10Guest},
                            {TaskBaseCtrlCycx20Guest,       RBSYS_TaskBaseCtrlCycx20Guest},
                          #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
                            {TaskBaseCtrlCycx10,       RBSYS_TaskBaseCtrlCycx10},
                            {TaskBaseCtrlCycx20,       RBSYS_TaskBaseCtrlCycx20},
                          #endif
                            {TaskTPSWKillCore0,             RBSYS_TaskTPSWKillCore0},
                            {TaskTPSWKillCore1,             RBSYS_TaskTPSWKillCore1}  };

#define RBSYS_TASKSTAT_TASKSIZE   (sizeof(RBSYS_taskstatsTasks)/sizeof(RBSYS_taskstatsTasks[0]))
static_assert(RBSYS_TASKSTAT_TASKSIZE == OS_NUM_TASKS, "Number of Tasks are not matching between OS config and TaskStats!");


static const RBSYS_taskstatsIsrTable_t RBSYS_taskstatsIsrs[] = {
                        #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
                          {ISRSTM04,     RBSYS_ISRSTM04},
                          {ISRSTM05,     RBSYS_ISRSTM05},
                          {ISRSWINT0,    RBSYS_ISRSWINT0},
                          #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
                            {ISRMTTCANI0,  RBSYS_ISRMTTCANI0},
                            {ISRMCAN0I0,   RBSYS_ISRMCAN0I0},
                            {ISRMCAN1I0,   RBSYS_ISRMCAN1I0},
                            {ISRMCAN2I0,   RBSYS_ISRMCAN2I0},
                          #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
                            {ISRCAN0REC,   RBSYS_ISRCAN0REC},
                            {ISRCAN0TRX,   RBSYS_ISRCAN0TRX},
                            {ISRCAN1REC,   RBSYS_ISRCAN1REC},
                            {ISRCAN1TRX,   RBSYS_ISRCAN1TRX},
                            {ISRCAN2REC,   RBSYS_ISRCAN2REC},
                            {ISRCAN2TRX,   RBSYS_ISRCAN2TRX},
                            {ISRCAN6REC,   RBSYS_ISRCAN6REC},
                            {ISRCAN6TRX,   RBSYS_ISRCAN6TRX},
                            {ISRCAN8REC,   RBSYS_ISRCAN8REC},
                            {ISRCAN8TRX,   RBSYS_ISRCAN8TRX},
                          #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
                            {ISRCAN0REC,   RBSYS_ISRCAN0REC},
                            {ISRCAN0TRX,   RBSYS_ISRCAN0TRX},
                            {ISRCAN1REC,   RBSYS_ISRCAN1REC},
                            {ISRCAN1TRX,   RBSYS_ISRCAN1TRX},
                            {ISRCAN2REC,   RBSYS_ISRCAN2REC},
                            {ISRCAN2TRX,   RBSYS_ISRCAN2TRX},
                            {ISRCAN3REC,   RBSYS_ISRCAN3REC},
                            {ISRCAN3TRX,   RBSYS_ISRCAN3TRX},
                          #endif
                          {ISRFLX0LINE0, RBSYS_ISRFLX0LINE0},
                          #if( RBFS_uCFamily != RBFS_uCFamily_RenesasU2C )
                            {ISRFLX1LINE0, RBSYS_ISRFLX1LINE0},
                          #endif
                          #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
                            {ISRRLIN30RX,           RBSYS_ISRRLIN30RX},
                            {ISRRLIN30STATUS,       RBSYS_ISRRLIN30STATUS},
                            {ISRRLIN31RX,           RBSYS_ISRRLIN31RX},
                            {ISRRLIN31STATUS,       RBSYS_ISRRLIN31STATUS},
                          #endif
                          #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15) )
                            {ISR0p5ms,     RBSYS_ISR0p5ms},
                          #endif
                        #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
                          {ISRCommonTimer,  RBSYS_ISRCommonTimer},
                        #endif
                      };

#define RBSYS_TASKSTAT_ISRSIZE   (sizeof(RBSYS_taskstatsIsrs)/sizeof(RBSYS_taskstatsIsrs[0]))
static_assert(RBSYS_TASKSTAT_ISRSIZE == OS_NUM_ISRS, "Number of ISRs are not matching between OS config and TaskStats!");


// ordered according OS configuration (saves some runtime if this order is taken)
RBSYS_TaskStatsTASK_t RBSYS_taskstats_tasks[RBSYS_TASKSTAT_TASKSIZE];
/*[[MEASUREMENT_TYPEDEF*/
/*TYPE=RBSYS_TaskStatsTASK_t*/
/*NAME=RBSYS_taskstats_tasks[RBSYS_TASK_SIZE_4_GENPRODB]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


RBSYS_TaskStatsISR_t RBSYS_taskstats_isrs[RBSYS_TASKSTAT_ISRSIZE];
/*[[MEASUREMENT_TYPEDEF*/
/*TYPE=RBSYS_TaskStatsISR_t*/
/*NAME=RBSYS_taskstats_isrs[RBSYS_ISR_SIZE_4_GENPRODB]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


/* map OS id to MM6 label => just for measurement purposes */
void RBSYS_PRC_InitTaskStats(void)
{
  uint32 i;
  for (i=0; i<RBSYS_TASKSTAT_TASKSIZE; i++)
  {
    RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(RBSYS_taskstatsTasks[i].task)].id = RBSYS_taskstatsTasks[i].id;
    RBSYS_taskstats_tasks[i].slack_time_min = 0xFFFFFFFFu;

    #if( RBFS_SysResettableSlackTimesSupport == RBFS_SysResettableSlackTimesSupport_ON )
      RBSYS_taskstats_tasks[i].slack_time_min_resettable = 0xFFFFFFFFu;
    #endif
  }

  for (i=0; i<RBSYS_TASKSTAT_ISRSIZE; i++)
  {
    RBSYS_taskstats_isrs[OS_ISRTYPE_TO_INDEX(RBSYS_taskstatsIsrs[i].isr)].id = RBSYS_taskstatsIsrs[i].id;
  }
}


/* return last activation time of given task */
uint32 RBSYS_get_task_activation_ts(RBSYS_TaskType task)
{
  return RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)].ts_activation;
}



/* returns slack time in ticks */
uint32 RBSYS_getSlackTime(RBSYS_TaskType task)
{
  return RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)].slack_time;
}


/* returns the minimal value of slack time in ticks */
uint32 RBSYS_getSlackTimeMin(RBSYS_TaskType task)
{
  return RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)].slack_time_min;
}

/** returns the runtime (specified by RuntimeType type) of the corresponding Task (specified by TaskType task) */
uint32 RBSYS_getTaskRuntime(RBSYS_TaskType task, RBSYS_RuntimeType_t type)
{
  uint32 rt = 0;

  switch(type)
  {
    case RBSYS_RuntimeType_NetCurrent:
      /* Net Runtime = Tend - Tstart - Tstandby (preemptions etc.) */
      {
        uint32 taskIdx = rba_Runtime_GetTaskIdx(task);
        if( taskIdx != RBA_RUNTIME_TASKNOTUSED )
        {
          rt = rba_Runtime_MonTask_ast[taskIdx].tiCurRT_u32;
        }
      }
      break;

    case RBSYS_RuntimeType_NetMax:
      /* Net Runtime = Tend - Tstart - Tstandby (preemptions etc.) */
      {
        uint32 taskIdx = rba_Runtime_GetTaskIdx(task);
        if( taskIdx != RBA_RUNTIME_TASKNOTUSED )
        {
          rt = rba_Runtime_MonTask_ast[taskIdx].tiMaxRT_u32;
        }
      }
      break;

    case RBSYS_RuntimeType_GrossCurrent:
      /* Gross Runtime = Tend - Tstart */
      rt = RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)].gross;
      break;

    case RBSYS_RuntimeType_GrossMax:
      /* Gross Runtime = Tend - Tstart */
      rt = RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)].gross_max;
      break;

    default:
      assert(0);
      break;
  }

  return rt;
}

/** returns the runtime (specified by RuntimeType type) of the corresponding ISR (specified by ISRType isr) */
uint32 RBSYS_getIsrRuntime(RBSYS_ISRType isr, RBSYS_RuntimeType_t type)
{
  uint32 rt = 0;

  switch(type)
  {
    case RBSYS_RuntimeType_NetCurrent:
      /* Net Runtime = Tend - Tstart - Tstandby (preemptions etc.) */
      {
        uint32 isrIdx = rba_Runtime_GetIsrIdx(isr);
        if( isrIdx != RBA_RUNTIME_ISRNOTUSED )
        {
          rt = rba_Runtime_MonIsr_ast[isrIdx].tiCurRT_u32;
        }
      }
      break;

    case RBSYS_RuntimeType_NetMax:
      /* Net Runtime = Tend - Tstart - Tstandby (preemptions etc.) */
      {
        uint32 isrIdx = rba_Runtime_GetIsrIdx(isr);
        if( isrIdx != RBA_RUNTIME_ISRNOTUSED )
        {
          rt = rba_Runtime_MonIsr_ast[isrIdx].tiMaxRT_u32;
        }
      }
      break;

    case RBSYS_RuntimeType_GrossCurrent:
      /* Gross Runtime = Tend - Tstart */
      rt = RBSYS_taskstats_isrs[OS_ISRTYPE_TO_INDEX(isr)].gross;
      break;

    case RBSYS_RuntimeType_GrossMax:
      /* Gross Runtime = Tend - Tstart */
      rt = RBSYS_taskstats_isrs[OS_ISRTYPE_TO_INDEX(isr)].gross_max;
      break;

    default:
      assert(0);
      break;
  }

  return rt;
}

#if( RBFS_SysResettableSlackTimesSupport == RBFS_SysResettableSlackTimesSupport_ON )
  /* returns the minimal value of resettable slack time in ticks */
  uint32 RBSYS_getResettableSlackTimeMin(RBSYS_TaskType task)
  {
    const RBSYS_TaskStatsTASK_t * const act = &RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)];
    return act->slack_time_min_resettable;
  }

  /* returns the corresponding task counter value for the minimal value given by RBSYS_getResettableSlackTimeMin */
  uint32 RBSYS_getTimestampResettableSlackTimeMin(RBSYS_TaskType task)
  {
    const RBSYS_TaskStatsTASK_t * const act = &RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)];
    return act->slack_time_min_resettable_task_cnt;
  }

  /* resets the resettable slack time min + the corresponding timestamp */
  void   RBSYS_clearResettableSlackTimeMin(RBSYS_TaskType task)
  {
    RBSYS_TaskStatsTASK_t* act = &RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)];

    act->slack_time_min_resettable = 0xFFFFFFFFu;
    act->slack_time_min_resettable_task_cnt = 0;
  }

  /* resets all resettable slack time min data (see RBSYS_clearResettableSlackTimeMin as well) */
  void   RBSYS_clearAllResettableSlackTimesMin(void)
  {
    uint32 i;
    for (i=0; i<RBSYS_TASKSTAT_TASKSIZE; i++)
    {
      RBSYS_taskstats_tasks[i].slack_time_min_resettable = 0xFFFFFFFFU;
      RBSYS_taskstats_tasks[i].slack_time_min_resettable_task_cnt = 0;
    }
  }
#endif

/** @} */
/* End ingroup RBSYS */
