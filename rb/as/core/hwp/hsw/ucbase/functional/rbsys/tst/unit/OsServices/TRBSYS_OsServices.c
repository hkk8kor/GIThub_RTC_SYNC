#include "SwTest_Global.h"

#include "RBSYS_Config.h" ///< for RBFS_CpuClock, RBFS_TargetDevice


// access API for api header under test
#include "RBSYS_OsServices.h"
#include "RBSYS_OsConfig.h"


/**
 * \Reference
 *  RBSYS_SetCurrentOperationMode, RBSYS_GetCurrentOperationMode
 *
 * \Purpose
 *  Verify Get/Set APIs for Current Operation Mode
 *
 * \Sequence
 *  Set any Operation Mode
 *  GetCurrentOperationMode should return the set Operation Mode
 *
 * \ExpectedResult
 * see \Sequence
 */
SWTEST void TRBSYS_GetSetOperationMode_001(void)
{
  RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_Init);
  SWT_EvalEq(RBSYS_GetCurrentOperationMode(), RBSYS_OperationMode_Init);
}

/**
 * \Reference
 *  RBSYS_GetCurrentTask
 *
 * \Purpose
 *  Verify API RBSYS_GetCurrentTask
 *
 * \Sequence
 *  Set Operation Mode "PreInit"
 *  RBSYS_GetCurrentTask shall fail with sanity check
 *  Set Operation Mode "Init" or "Cyclic"
 *  RBSYS_GetCurrentTask shall return the active task
 *
 * \ExpectedResult
 * see \Sequence
 */
SWTEST void TRBSYS_GetCurrentTask_002(void)
{
  TaskType result = NULL;
  TRBSYS_CurrentTask = NULL;
  RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_PreInit);

  // sanity check will fail because GetCurrentTask may not be called if OperationMode == PreInit
  SWT_AssertCheckStart("RBSYS_GetTaskID", "(RBSYS_GetCurrentOperationMode() == RBSYS_OperationMode_Init) || (RBSYS_GetCurrentOperationMode() == RBSYS_OperationMode_Cyclic)");
  result = RBSYS_GetCurrentTask();
  SWT_AssertCheckEnd();

  // current task is returned
  TRBSYS_CurrentTask = TaskInit;
  RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_Init);
  result = RBSYS_GetCurrentTask();
  SWT_Eval(result == TaskInit);

  // current task is returned
  TRBSYS_CurrentTask = TaskBaseCtrlCycx2p;
  RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_Cyclic);
  result = RBSYS_GetCurrentTask();
  SWT_Eval(result == TaskBaseCtrlCycx2p);
}

/**
 * \Reference
 *  RBSYS_GetTaskID
 *
 * \Purpose
 *  Verify API RBSYS_GetTaskID
 *
 * \Sequence
 *  Set Operation Mode "PreInit"
 *  RBSYS_GetTaskID shall fail with sanity check
 *  Set Operation Mode "Init" or "Cyclic"
 *  RBSYS_GetTaskID shall return the active task
 *
 * \ExpectedResult
 * see \Sequence
 */
SWTEST void TRBSYS_GetTaskID_003(void)
{
  TaskType result = NULL;
  StatusType status = E_NOT_OK;
  TRBSYS_CurrentTask = NULL;
  RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_PreInit);

  // sanity check will fail because GetTaskID may not be called if OperationMode == PreInit
  SWT_AssertCheckStart("RBSYS_GetTaskID", "(RBSYS_GetCurrentOperationMode() == RBSYS_OperationMode_Init) || (RBSYS_GetCurrentOperationMode() == RBSYS_OperationMode_Cyclic)");
  status = RBSYS_GetTaskID(&result);
  SWT_AssertCheckEnd();
  SWT_Eval(status == E_NOT_OK);

  // current task is returned
  RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_Init);
  status = E_NOT_OK;
  TRBSYS_CurrentTask = TaskInit;
  status = RBSYS_GetTaskID(&result);
  SWT_Eval(result == TaskInit);
  SWT_Eval(status == E_OK);

  // current task is returned
  TRBSYS_CurrentTask = TaskBaseCtrlCycx2p;
  RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_Cyclic);
  status = E_NOT_OK;
  status = RBSYS_GetTaskID(&result);
  SWT_Eval(result == TaskBaseCtrlCycx2p);
  SWT_Eval(status == E_OK);
}
