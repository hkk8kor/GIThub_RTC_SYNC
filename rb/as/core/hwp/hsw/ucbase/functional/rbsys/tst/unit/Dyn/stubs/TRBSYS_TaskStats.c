#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_TaskStats.h"
#include "TRBSYS_TaskStats.h"

#include "TRBSYS_Os.h"

RBSYS_TaskStatsTASK_t RBSYS_taskstats_tasks[OS_NUM_TASKS];
RBSYS_TaskStatsISR_t RBSYS_taskstats_isrs[OS_NUM_ISRS];

uint32 TRBSYS_get_current_taskcnt(TaskType task)
{
    return RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)].current_task_cnt;
}
