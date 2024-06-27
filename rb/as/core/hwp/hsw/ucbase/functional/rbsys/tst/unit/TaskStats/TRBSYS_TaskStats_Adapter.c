#include "csw/RBSYS_TaskInfo.h"       // ensure include of original RBSYS header instead of CoreStub
#include "RBSYS_TaskStats.c"



#include "TRBSYS_TaskStats_Adapter.h"
#include "RBSYS_Config.h"

#include "TRBSYS_Os.h"

boolean rba_Runtime_GetTaskIdx_ReturnValid = TRUE;
boolean rba_Runtime_GetIsrIdx_ReturnValid  = TRUE;


int GetPrivate_RBSYS_TASKSTAT_TASKSIZE(void)
{
  return RBSYS_TASKSTAT_TASKSIZE;
}

int GetPrivate_RBSYS_TASKSTAT_ISRSIZE(void)
{
  return RBSYS_TASKSTAT_ISRSIZE;
}



TaskType GetPrivate_RBSYS_taskstatsTasks_task(int index)
{
  return RBSYS_taskstatsTasks[index].task;
}

RBSYS_taskstats_ids_t GetPrivate_RBSYS_taskstatsTasks_id(int index)
{
  return RBSYS_taskstatsTasks[index].id;
}



ISRType GetPrivate_RBSYS_taskstatsIsrs_isr(int index)
{
  return RBSYS_taskstatsIsrs[index].isr;
}

RBSYS_taskstats_ids_t GetPrivate_RBSYS_taskstatsIsrs_id(int index)
{
  return RBSYS_taskstatsIsrs[index].id;
}