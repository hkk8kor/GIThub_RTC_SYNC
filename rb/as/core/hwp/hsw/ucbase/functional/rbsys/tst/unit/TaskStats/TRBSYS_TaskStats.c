#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                      // for RBFS_BUILDCONFIG_
#include "Statistics/RBSYS_TaskStats.h"
#include "RBSYS_Subsystem.h"

#include "TRBSYS_TaskStats_Adapter.h"
#include "TRBSYS_Os.h"
#include "TRBA_Runtime.h"


rba_Runtime_MonTask_t rba_Runtime_MonTask_ast[OS_NUM_TASKS];
rba_Runtime_MonISR_t  rba_Runtime_MonIsr_ast[OS_NUM_ISRS];

#if( (RBFS_uCFamily != RBFS_uCFamily_RenesasP1x) && (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15) )
  static_assert((RBFS_uCFamily != RBFS_uCFamily_RenesasP1x) && (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15), "Unsupported Unit Variant");
#endif

/**
 * \Reference
 *  RBSYS_PRC_InitTaskStats, Gen_SWCS_HSW_uC_Base_SYS-221
 *
 * \Purpose
 *  Verification of process RBSYS_PRC_InitTaskStats
 *
 * \Sequence
 *  Call process RBSYS_PRC_InitTaskStats
 *
 * \ExpectedResult
 *  Mapping of OS configured tasks & ISRs must be mapped to corresponding MM6 measurement label
 *  Slacktime must be initialized for each task to 0xFFFFFFFFu
 */
SWTEST void TRBSYS_PRC_InitTaskStats(void)
{
  int i;

  RBSYS_PRC_InitTaskStats();

  for (i=0; i<GetPrivate_RBSYS_TASKSTAT_TASKSIZE(); i++)
  {
    TaskType os_task = GetPrivate_RBSYS_taskstatsTasks_task(i);
    RBSYS_taskstats_ids_t rbsys_id = GetPrivate_RBSYS_taskstatsTasks_id(i);

    SWT_EvalEq(RBSYS_taskstats_tasks[OS_TASKTYPE_TO_INDEX(os_task)].id, rbsys_id);
  }

  for (i=0; i<GetPrivate_RBSYS_TASKSTAT_ISRSIZE(); i++)
  {
    ISRType os_isr = GetPrivate_RBSYS_taskstatsIsrs_isr(i);
    RBSYS_taskstats_ids_t rbsys_id = GetPrivate_RBSYS_taskstatsIsrs_id(i);

    SWT_EvalEq(RBSYS_taskstats_isrs[OS_ISRTYPE_TO_INDEX(os_isr)].id, rbsys_id);
  }

  for (i=0; i<OS_NUM_TASKS; i++)
  {
    SWT_EvalEq(RBSYS_taskstats_tasks[i].slack_time_min, 0xFFFFFFFFu);
  }
}


/**
 * \Reference
 *  set_task_activation_ts, set_task_start_ts, set_task_end_ts, Gen_SWCS_HSW_uC_Base_SYS-221,Gen_SWCS_HSW_uC_Base_SYS-295
 *
 * \Purpose
 *  Verification of task timing statistics
 *
 * \Sequence
 *  Call process RBSYS_PRC_InitTaskStats
 *  1) Simulate for each task the activation, start and end with corresponding timestamps, task count
 *  2) Simulate for each task the activation, start and end with corresponding timestamps, task count
 *     where slack_time_min, gross_max and resp_time_max will be overwritten
 *  3) Simulate for each task the activation, start and end with corresponding timestamps, task count
 *     where slack_time_min, gross_max and resp_time_max will NOT be overwritten
 *
 * \ExpectedResult
 *  1) Initial slack_time must be 0xFFFFFFFFu
 *     Inital task count for the min slack time must be zero.
 *     Actual gross time must be end minus start timestamps
 *     Actual gross time must be the max gross time (gross_max)
 *     Actual response time must be the end minus activation
 *     Actual response time must be the max response time (resp_time_max)
 *     Actual task counter must be one for the first task.
 *  2) Actual slack time must be activation time minus previous task end
 *     Actual slack time must be the min slack time (slack_time_min)
 *     Actual task count for the min slack time must be one for the second task.
 *     Actual gross time must be end minus start timestamps
 *     Actual gross time must be the max gross time (gross_max)
 *     Actual response time must be the end minus activation
 *     Actual response time must be the max response time (resp_time_max)
 *     Actual task counter must be incremented for the next task.
 *  3) Actual slack time must be activation time minus previous task end
 *     Last slack time must still be the min slack time (slack_time_min)
 *     Last task count for the min slack time must now remain the same.
 *     Actual gross time must be end minus start timestamps
 *     Last gross time must still be the max gross time (gross_max)
 *     Actual response time must be the end minus activation
 *     Last response time must still be the max response time (resp_time_max)
 *     Actual task counter must be incremented for the next task.
 */
SWTEST void TRBSYS_TASK_TIMESTAMPS(void)
{
  int i;

  RBSYS_PRC_InitTaskStats();

  for (i=0; i<OS_NUM_TASKS; i++)
  {
    TaskType task = Os_const_tasks[i];
    RBSYS_TaskStatsTASK_t* act = &RBSYS_taskstats_tasks[OS_TASKTYPE_TO_INDEX(task)];
    int activation, start, end, temp_slack_time, temp_response_time, temp_gross, previous_end, taskcnt, temp_slack_time_min_task_cnt;

    // 1) simulate first task
    activation = i + 10;
    start = i + 21;
    end = i + 320;
    taskcnt = 1;

    set_task_activation_ts(task, activation);
    set_task_start_ts(task, start);
    set_task_end_ts(task, end);
    set_current_task_cnt(task,taskcnt);

    SWT_EvalEq(act->slack_time_min, 0xFFFFFFFFu);
    SWT_EvalEq(act->slack_time_min_task_cnt, 0);

    SWT_EvalEq(act->gross, end - start);
    SWT_EvalEq(act->gross, act->gross_max);

    SWT_EvalEq(act->resp_time, end - activation);
    SWT_EvalEq(act->resp_time, act->resp_time_max);
    SWT_EvalEq(act->current_task_cnt, taskcnt);

    previous_end = end;

    // 2) simulate second task (overwrite slack_time_min, gross_max and resp_time_max)
    activation = i + 350;
    start = i + 3100;
    end = i + 40200;
    taskcnt = 2;

    set_task_activation_ts(task, activation);
    set_task_start_ts(task, start);
    set_task_end_ts(task, end);
    set_current_task_cnt(task,taskcnt);

    SWT_EvalEq(act->slack_time, activation - previous_end);
    SWT_EvalEq(act->slack_time, act->slack_time_min);
    SWT_EvalEq(act->slack_time_min_task_cnt, 1);

    SWT_EvalEq(act->gross, end - start);
    SWT_EvalEq(act->gross, act->gross_max);

    SWT_EvalEq(act->resp_time, end - activation);
    SWT_EvalEq(act->resp_time, act->resp_time_max);
    SWT_EvalEq(act->current_task_cnt, taskcnt);

    temp_response_time = act->resp_time;
    temp_slack_time = act->slack_time;
    temp_gross = act->gross;
    temp_slack_time_min_task_cnt = act->slack_time_min_task_cnt;
    previous_end = end;


    // 3) simulate third task (no overwrite of slack_time_min, gross_max and resp_time_max)
    activation = i + 40300;
    start = i + 40400;
    end = i + 40500;
    taskcnt = 3;

    set_task_activation_ts(task, activation);
    set_task_start_ts(task, start);
    set_task_end_ts(task, end);
    set_current_task_cnt(task,taskcnt);

    SWT_EvalEq(act->slack_time, activation - previous_end);
    SWT_EvalEq(act->slack_time_min, temp_slack_time);
    SWT_EvalEq(act->slack_time_min_task_cnt,temp_slack_time_min_task_cnt);

    SWT_EvalEq(act->gross, end - start);
    SWT_EvalEq(act->gross_max, temp_gross);

    SWT_EvalEq(act->resp_time, end - activation);
    SWT_EvalEq(act->resp_time_max, temp_response_time);
    SWT_EvalEq(act->current_task_cnt, taskcnt);
  }
}

/**
 * \Reference
 *  RBSYS_getTaskRuntime, RBSYS_getIsrRuntime, Gen_SWCS_HSW_uC_Base_SYS-221
 *
 * \Purpose
 *  Verification of task / ISR runtime interfaces
 *
 * \Sequence
 *  Call process RBSYS_PRC_InitTaskStats
 *  1) Set valid measurement input for rba_Runtime + valid input for rbsys_TaskStats
 *  2) Eval: values are equal to the provided input + mapping of Tasks / ISRs is correct
 *
 *  3) manipulate rba_Runtime-stub: no tasks / ISRs are measured anymore
 *  4) Eval: Interfaces shall return 0
 *
 *  5) Test Sanity checks
 *
 * \ExpectedResult
 *  see \sequence
 */
SWTEST void TRBSYS_TaskStats_TaskRuntimeNetAndGross(void)
{
  RBSYS_PRC_InitTaskStats();

  /************* Tasks **************/
  // rba_Runtime measured stuff
  rba_Runtime_MonTask_ast[OS_TASKTYPE_TO_INDEX(RBSYS_TaskType_TaskBaseCtrlCycx24)].tiCurRT_u32 = 100;
  rba_Runtime_MonTask_ast[OS_TASKTYPE_TO_INDEX(RBSYS_TaskType_TaskBaseCtrlCycx24)].tiMaxRT_u32 = 200;

  // rbsys measured stuff
  RBSYS_taskstats_tasks[OS_TASKTYPE_TO_INDEX(RBSYS_TaskType_TaskBaseCtrlCycx24)].gross = 500;
  RBSYS_taskstats_tasks[OS_TASKTYPE_TO_INDEX(RBSYS_TaskType_TaskBaseCtrlCycx24)].gross_max = 600;

  /// Net Runtime of Task
  SWT_EvalEq(RBSYS_getTaskRuntime (RBSYS_TaskType_TaskBaseCtrlCycx24, RBSYS_RuntimeType_NetCurrent), 100);
  SWT_EvalEq(RBSYS_getTaskRuntime (RBSYS_TaskType_TaskBaseCtrlCycx24, RBSYS_RuntimeType_NetMax),     200);
  /// Gross Runtime of Task
  SWT_EvalEq(RBSYS_getTaskRuntime (RBSYS_TaskType_TaskBaseCtrlCycx24, RBSYS_RuntimeType_GrossCurrent), 500);
  SWT_EvalEq(RBSYS_getTaskRuntime (RBSYS_TaskType_TaskBaseCtrlCycx24, RBSYS_RuntimeType_GrossMax),     600);

  rba_Runtime_GetTaskIdx_ReturnValid = FALSE;

  /// Net Runtime of Task where Net Runtime is not measured (not measured by stub, really measured inside target software)
  SWT_EvalEq(RBSYS_getTaskRuntime (RBSYS_TaskType_TaskBaseCtrlCycx24, RBSYS_RuntimeType_NetCurrent), 0);
  SWT_EvalEq(RBSYS_getTaskRuntime (RBSYS_TaskType_TaskBaseCtrlCycx24, RBSYS_RuntimeType_NetMax),     0);

  rba_Runtime_GetTaskIdx_ReturnValid = TRUE;

  // sanity checks
  SWT_AssertCheckStart("RBSYS_getTaskRuntime", "0");
  (void)RBSYS_getTaskRuntime(RBSYS_TaskType_TaskBaseCtrlCycx24, (RBSYS_RuntimeType_t) 1337);
  SWT_AssertCheckEnd();

  #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )

    /************* ISRs ***************/
    // rba_Runtime measured stuff
    rba_Runtime_MonIsr_ast[OS_ISRTYPE_TO_INDEX(RBSYS_IsrType_ISRFLX0LINE0)].tiCurRT_u32 = 300;
    rba_Runtime_MonIsr_ast[OS_ISRTYPE_TO_INDEX(RBSYS_IsrType_ISRFLX0LINE0)].tiMaxRT_u32 = 400;

    // rbsys measured stuff
    RBSYS_taskstats_isrs[OS_ISRTYPE_TO_INDEX(RBSYS_IsrType_ISRFLX0LINE0)].gross = 700;
    RBSYS_taskstats_isrs[OS_ISRTYPE_TO_INDEX(RBSYS_IsrType_ISRFLX0LINE0)].gross_max = 800;

    /// Net Runtime of ISR
    SWT_EvalEq(RBSYS_getIsrRuntime  (RBSYS_IsrType_ISRFLX0LINE0,        RBSYS_RuntimeType_NetCurrent), 300);
    SWT_EvalEq(RBSYS_getIsrRuntime  (RBSYS_IsrType_ISRFLX0LINE0,        RBSYS_RuntimeType_NetMax),     400);
    /// Gross Runtime of ISR
    SWT_EvalEq(RBSYS_getIsrRuntime  (RBSYS_IsrType_ISRFLX0LINE0,        RBSYS_RuntimeType_GrossCurrent), 700);
    SWT_EvalEq(RBSYS_getIsrRuntime  (RBSYS_IsrType_ISRFLX0LINE0,        RBSYS_RuntimeType_GrossMax),     800);

    rba_Runtime_GetIsrIdx_ReturnValid  = FALSE;

    /// Net Runtime of ISR where Net Runtime is not measured (not measured by stub, really measured inside target software)
    SWT_EvalEq(RBSYS_getIsrRuntime  (RBSYS_IsrType_ISRFLX0LINE0, RBSYS_RuntimeType_NetCurrent), 0);
    SWT_EvalEq(RBSYS_getIsrRuntime  (RBSYS_IsrType_ISRFLX0LINE0, RBSYS_RuntimeType_NetMax),     0);

    rba_Runtime_GetIsrIdx_ReturnValid  = TRUE;

    SWT_AssertCheckStart("RBSYS_getIsrRuntime", "0");
    (void)RBSYS_getIsrRuntime(RBSYS_IsrType_ISRFLX0LINE0, (RBSYS_RuntimeType_t) 1337);
    SWT_AssertCheckEnd();
  
  #else
    #warning("Missing support for Stellar")
  #endif
}


#if( RBFS_SysResettableSlackTimesSupport == RBFS_SysResettableSlackTimesSupport_ON )
/**
 * \Reference
 *  RBSYS_getResettableSlackTimeMin, RBSYS_getTimestampResettableSlackTimeMin, RBSYS_clearResettableSlackTimeMin, RBSYS_clearAllResettableSlackTimesMin, Gen_SWCS_HSW_uC_Base_SYS-221
 *
 * \Purpose
 *  Verification of task timing statistics of resettable slack time min
 *
 * \Sequence
 *  Call process RBSYS_PRC_InitTaskStats
 *  1) Simulate the first task activation to prepare the intial state for task stats (slack time will always count
       for the previous task but will be calculated as soon as the next one is activated)
 *  2) Simulate the second task activation
       Result: Resettable Slack Time Min is same as Non-Resettable Slack Time Min
 *  3) Reset resettable slack time min
    4) Simulate the third task activation with a higher slack time then the one of end of 1.) to activation of 2.)
       Result: Non-resettable slack time min is not changed whereas resettable slack time min is set again
    5) Check if RBSYS_clearAllResettableSlackTimesMin works: All resettable slack times must be reset where as others are not changed
 *
 * \ExpectedResult
 *  see \sequence
 */
SWTEST void TRBSYS_TaskStats_ResettableSlackTime(void)
{
  int i;

  RBSYS_PRC_InitTaskStats();

  for (i=0; i<OS_NUM_TASKS; i++)
  {
    TaskType task = Os_const_tasks[i];
    RBSYS_TaskStatsTASK_t* act = &RBSYS_taskstats_tasks[OS_TASKTYPE_TO_INDEX(task)];
    int activation, start, end, temp_slack_time, temp_response_time, temp_gross, previous_end, taskcnt, temp_slack_time_min_task_cnt, temp_slack_time_min;

    // 1) simulate first task
    activation = i + 10;
    start = i + 21;
    end = i + 320;
    taskcnt = 1;

    set_task_activation_ts(task, activation);
    set_task_start_ts(task, start);
    set_task_end_ts(task, end);
    set_current_task_cnt(task,taskcnt);

    // 2) simulate second task (overwrite slack_time_min, gross_max and resp_time_max)
    activation = i + 350;
    start = i + 3100;
    end = i + 40200;
    taskcnt = 2;

    set_task_activation_ts(task, activation);
    set_task_start_ts(task, start);
    set_task_end_ts(task, end);
    set_current_task_cnt(task, taskcnt);

    /** Check if the measured resettable SlackTimeMin + corresponding timestamp are same as the non-resettable */
    SWT_EvalEq(RBSYS_getResettableSlackTimeMin(task), RBSYS_getSlackTimeMin(task));
    SWT_EvalEq(RBSYS_getTimestampResettableSlackTimeMin(task), act->slack_time_min_task_cnt);

    temp_slack_time_min = RBSYS_getSlackTimeMin(task);
    temp_slack_time_min_task_cnt = act->slack_time_min_task_cnt;

    /** Reset and check if only the resettable part is reset */
    RBSYS_clearResettableSlackTimeMin(task);
    SWT_EvalEq(RBSYS_getResettableSlackTimeMin(task), 0xFFFFFFFFu);
    SWT_EvalEq(RBSYS_getTimestampResettableSlackTimeMin(task), 0);
    SWT_EvalEq(RBSYS_getSlackTimeMin(task), temp_slack_time_min);
    SWT_EvalEq(act->slack_time_min_task_cnt, temp_slack_time_min_task_cnt);

    previous_end = end;

    // 3) simulate third task (no new minimum of slack_time_min)
    activation = i + 40300;
    start = i + 40400;
    end = i + 40500;
    taskcnt = 3;

    set_task_activation_ts(task, activation);
    set_task_start_ts(task, start);
    set_task_end_ts(task, end);
    set_current_task_cnt(task,taskcnt);

    /** Resettable SlackTimeMin + Timestamp have changed */
    SWT_EvalEq(RBSYS_getResettableSlackTimeMin(task), activation - previous_end);
    SWT_EvalEq(RBSYS_getTimestampResettableSlackTimeMin(task), taskcnt - 1);
    /** Whereas Non-Resettable SlacktimeMin + Timestamp have not changed */
    SWT_EvalEq(RBSYS_getSlackTimeMin(task), temp_slack_time_min);
    SWT_EvalEq(act->slack_time_min_task_cnt, temp_slack_time_min_task_cnt);
  }

  /** Test reset functionality of RBSYS_clearAllResettableSlackTimesMin */
  RBSYS_clearAllResettableSlackTimesMin();

  for (i=0; i<OS_NUM_TASKS; i++)
  {
    TaskType task = Os_const_tasks[i];
    RBSYS_TaskStatsTASK_t* act = &RBSYS_taskstats_tasks[OS_TASKTYPE_TO_INDEX(task)];

    SWT_Eval(RBSYS_getResettableSlackTimeMin(task)          == 0xFFFFFFFFu);
    SWT_Eval(RBSYS_getTimestampResettableSlackTimeMin(task) == 0);

    SWT_Eval(RBSYS_getSlackTimeMin(task)                    != 0xFFFFFFFFu);
    SWT_Eval(act->slack_time_min_task_cnt                   != 0);
  }
}
#endif


/**
 * \Reference
 *  set_isr_start_ts, set_isr_end_ts, Gen_SWCS_HSW_uC_Base_SYS-221
 *
 * \Purpose
 *  Verification of ISR timing statistics
 *
 * \Sequence
 *  1) Simulate for each ISR the start and end with corresponding timestamps
 *  2) Simulate for each ISR the start and end with corresponding timestamps
 *     where gross_max will be overwritten
 *  3) Simulate for each ISR the start and end with corresponding timestamps
 *     where gross_max will NOT be overwritten
 *
 * \ExpectedResult
 *  1) Actual gross time must be end minus start timestamps
 *     Actual gross time must be the max gross time (gross_max)
 *  2) Actual gross time must be end minus start timestamps
 *     Actual gross time must be the max gross time (gross_max)
 *  2) Actual gross time must be end minus start timestamps
 *     Last gross time must still be the max gross time (gross_max)
 */
SWTEST void TRBSYS_ISR_TIMESTAMPS(void)
{
  int i;

  for (i=0; i<OS_NUM_ISRS; i++)
  {
    ISRType isr = &Os_const_isrs[i];
    RBSYS_TaskStatsISR_t* act = &RBSYS_taskstats_isrs[OS_ISRTYPE_TO_INDEX(isr)];
    int start, end, temp_gross;

    // 1) simulate first ISR
    start = i + 10;
    end = i + 100;

    set_isr_start_ts(isr, start);
    set_isr_end_ts(isr, end);

    SWT_EvalEq(act->gross, end - start);
    SWT_EvalEq(act->gross, act->gross_max);

    // 2) simulate second ISR (overwrite gross_max)
    start = i + 1000;
    end = i + 10000;

    set_isr_start_ts(isr, start);
    set_isr_end_ts(isr, end);

    SWT_EvalEq(act->gross, end - start);
    SWT_EvalEq(act->gross, act->gross_max);
    temp_gross = act->gross_max;

    // 3) simulate third ISR (no overwrite of gross_max)
    start = i + 10011;
    end = i + 10222;

    set_isr_start_ts(isr, start);
    set_isr_end_ts(isr, end);

    SWT_EvalEq(act->gross, end - start);
    SWT_EvalEq(act->gross_max, temp_gross);
  }
}

/**
 * \Reference
 *  RBSYS_getSlackTime, RBSYS_getSlackTimeMin, Gen_SWCS_HSW_uC_Base_SYS-297
 *
 * \Purpose
 *  Verification of RBSYS_getSlackTime and RBSYS_getSlackTimeMin interface
 *
 * \Sequence
 *  Call process RBSYS_PRC_InitTaskStats
 *  1, 2) Simulate for each task the activation, start and end with corresponding timestamps, task count
 *
 * \ExpectedResult
 * 	- Actual slack time must be activation time minus previous task end
 * 	- RBSYS_getSlackTime interface returns actual slack time
 */
SWTEST void TRBSYS_TASK_getSlackTime(void)
{
  int i;

  RBSYS_PRC_InitTaskStats();

  for (i=0; i<OS_NUM_TASKS; i++)
  {
    TaskType task = Os_const_tasks[i];
    RBSYS_TaskStatsTASK_t* act = &RBSYS_taskstats_tasks[OS_TASKTYPE_TO_INDEX(task)];
    uint32 rcvSlacktime, activation_1, start_1, end_1, taskcnt, activation_2, start_2, end_2, activation_3, start_3, end_3;

    // 1)
    activation_1 = i + 10;
    start_1 = i + 21;
    end_1 = i + 320;
    taskcnt = 1;

    set_task_activation_ts(task, activation_1);
    set_task_start_ts(task, start_1);
    set_task_end_ts(task, end_1);
    set_current_task_cnt(task, taskcnt);

    // 2)
    activation_2 = i + 350;
    start_2 = i + 3100;
    end_2 = i + 4020;
    taskcnt++;

    set_task_activation_ts(task, activation_2);
    set_task_start_ts(task, start_2);
    set_task_end_ts(task, end_2);
    set_current_task_cnt(task,taskcnt);

    // verify correct slack time calculation
    SWT_EvalEq(activation_2 - end_1, act->slack_time);
    // verify interface returns expected slack time
    SWT_EvalEq(RBSYS_getSlackTime(task), act->slack_time);

    // first calculated slack time must be also the slack time min
    SWT_EvalEq(act->slack_time, act->slack_time_min);
    // verify interface returns expected slack time min
    SWT_EvalEq(RBSYS_getSlackTimeMin(task), act->slack_time_min);


    // 3)
    activation_3 = i + 5000;
    start_3 = i + 5100;
    end_3 = i + 5500;
    taskcnt++;

    set_task_activation_ts(task, activation_3);
    set_task_start_ts(task, start_3);
    set_task_end_ts(task, end_3);
    set_current_task_cnt(task,taskcnt);

    // verify correct slack time calculation
    SWT_EvalEq( activation_3 - end_2, act->slack_time );
    // verify interface returns expected slack time
    SWT_EvalEq(RBSYS_getSlackTime(task), act->slack_time);

    // first slack time must still be the slack time min
    SWT_EvalEq(activation_2 - end_1, act->slack_time_min);
    // verify interface returns expected slack time min
    SWT_EvalEq(RBSYS_getSlackTimeMin(task), act->slack_time_min);
  }
}


/**
 * \Reference
 *  RBSYS_get_task_activation_ts
 *
 * \Purpose
 *  Verification of function RBSYS_get_task_activation_ts
 *
 * \Sequence
 *  Set for all tasks different activation timestamps
 *
 * \ExpectedResult
 *  RBSYS_get_task_activation_ts must return the previous timestamps for each task
 */
SWTEST void TRBSYS_TASK_get_task_activation_ts(void)
{
  int i;
  for (i=0; i<OS_NUM_TASKS; i++)
  {
    TaskType task = Os_const_tasks[i];
    set_task_activation_ts(task, i);

    SWT_EvalEq(RBSYS_get_task_activation_ts(task), i);
  }
}