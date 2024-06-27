/**
 * @ingroup RBSYS
 * @{
 *
 * @file  RBSYS_OsServices.c
 * @brief Service Provider: Operation Mode, Current Running Task

 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"

/* realized interfaces */
#include "RBSYS_OsServices.h"
#include "RBSYS_OsConfig.h"

/* used interfaces */
#include "Os.h"

/* Assert supported configurations: switches, parameters, constants, ... */


/* Current RBSYS Operation Mode (Information on active phase of Startup) */
static RBSYS_OperationMode_n RBSYS_CurrentOperationMode;

RBSYS_OperationMode_n RBSYS_GetCurrentOperationMode(void)
{
  return RBSYS_CurrentOperationMode;
}

void RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_n mode)
{
  RBSYS_CurrentOperationMode = mode;
}

RBSYS_TaskType RBSYS_GetCurrentTask(void)
{
  TaskType currentTask;

  (void)RBSYS_GetTaskID(&currentTask);

  return ((RBSYS_TaskType)currentTask);
}

StatusType RBSYS_GetTaskID(TaskRefType TaskID)
{
  // "GetTaskID" may not be called before Starting the Operating System (see API description of GetTaskID)
  assert((RBSYS_GetCurrentOperationMode() == RBSYS_OperationMode_Init) || (RBSYS_GetCurrentOperationMode() == RBSYS_OperationMode_Cyclic));

  return GetTaskID(TaskID);
}


/** @} */
/* End ingroup RBSYS */