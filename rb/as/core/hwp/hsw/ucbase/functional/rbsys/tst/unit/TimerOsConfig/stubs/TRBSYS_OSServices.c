#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_OSServices.h"
#include "TRBSYS_OSServices.h"


RBSYS_TaskType currentTaskType;

RBSYS_TaskType RBSYS_GetCurrentTask(void)
{
  return currentTaskType;
}

void TRBSYS_SetCurrentTask(TaskType type)
{
  currentTaskType = type;
}


