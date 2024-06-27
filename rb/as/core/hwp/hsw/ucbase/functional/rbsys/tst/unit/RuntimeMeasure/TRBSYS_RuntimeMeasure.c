#include "SwTest_Global.h"            // for SWT functionality

#include "RBSYS_Config.h"            // for RBFS_MCORE, RBFS_BUILDCONFIG_
#include "csw/RBSYS_TaskInfo.h"      // ensure include of original RBSYS header instead of CoreStub
#include "TRBSYS_rba_Runtime.h"
#include "Statistics/RBSYS_RuntimeMeasure.h"
#include "RBSYS_Subsystem.h"



/**
 * \Reference
 *  RBSYS_PRC_RuntimeMeasure_PreOSInit, Gen_SWCS_HSW_uC_Base_SYS-222
 *
 * \Purpose
 *  Verification of process "RBSYS_PRC_RuntimeMeasure_PreOSInit"
 *
 * \Sequence
 *  Call process "RBSYS_PRC_RuntimeMeasure_PreOSInit"
 *
 * \ExpectedResult
 *  Function "rba_Runtime_PreOSInit()" must be called once
 */
SWTEST void TRBSYS_PRC_RuntimeMeasure_PreOSInit(void)
{
  RBSYS_PRC_RuntimeMeasure_PreOSInit();

  SWT_EvalEq(TRBSYS_GetPreOSInit_Counter(), 1);
}


/**
 * \Reference
 *  RBSYS_PRC_RuntimeMeasure_Init, Gen_SWCS_HSW_uC_Base_SYS-222
 *
 * \Purpose
 *  Verification of process "RBSYS_PRC_RuntimeMeasure_Init"
 *
 * \Sequence
 *  Call process "RBSYS_PRC_RuntimeMeasure_Init"
 *
 * \ExpectedResult
 *  Function "rba_Runtime_Init" must be called once
 *  Function "rba_Runtime_MonSystemLoadInit" must be called once
 */
SWTEST void TRBSYS_PRC_RuntimeMeasure_Init(void)
{
  RBSYS_PRC_RuntimeMeasure_Init();

  SWT_EvalEq(TRBSYS_GetInit_Counter(), 1);
  SWT_EvalEq(TRBSYS_GetMonSystemLoadInit_Counter(), 1);
}


/**
 * \Reference
 *  RBSYS_PRC_RuntimeMeasure_MainFunction, Gen_SWCS_HSW_uC_Base_SYS-222
 *
 * \Purpose
 *  Verification of process "RBSYS_PRC_RuntimeMeasure_MainFunction"
 *
 * \Sequence
 *  Call process "RBSYS_PRC_RuntimeMeasure_MainFunction"
 *
 * \ExpectedResult
 *  Function "rba_Runtime_MainFunction" must be called once
 */
SWTEST void TRBSYS_PRC_RuntimeMeasure_MainFunction(void)
{
  RBSYS_PRC_RuntimeMeasure_MainFunction();

  SWT_EvalEq(TRBSYS_GetMainFunction_Counter(), 1);
}


/**
 * \Reference
 *  RBSYS_RuntimeMeasure_TaskStart, Gen_SWCS_HSW_uC_Base_SYS-222
 *
 * \Purpose
 *  Verification of function "RBSYS_RuntimeMeasure_TaskStart"
 *
 * \Sequence
 *  Call function "RBSYS_RuntimeMeasure_TaskStart"
 *
 * \ExpectedResult
 *  Function "rba_Runtime_TaskStart" must be called once
 *  Parameter "TaskType" must be forwarded as parameter for "rba_Runtime_TaskStart"
 */
SWTEST void TRBSYS_RuntimeMeasure_TaskStart(void)
{
  RBSYS_RuntimeMeasure_TaskStart(Task1ms);

  SWT_EvalEq(TRBSYS_GetTaskStart_Counter(), 1);
  SWT_Eval(TRBSYS_get_current_task() == Task1ms);
}


/**
 * \Reference
 *  RBSYS_RuntimeMeasure_TaskEnd, Gen_SWCS_HSW_uC_Base_SYS-222
 *
 * \Purpose
 *  Verification of function "RBSYS_RuntimeMeasure_TaskEnd"
 *
 * \Sequence
 *  Call function "RBSYS_RuntimeMeasure_TaskEnd"
 *
 * \ExpectedResult
 *  Function "rba_Runtime_TaskEnd" must be called once
 *  Parameter "TaskType" must be forwarded as parameter for "rba_Runtime_TaskEnd"
 */
SWTEST void TRBSYS_RuntimeMeasure_TaskEnd(void)
{
  RBSYS_RuntimeMeasure_TaskEnd(TaskBaseCtrlCycx1High);

  SWT_EvalEq(TRBSYS_GetTaskEnd_Counter(), 1);
  SWT_Eval(TRBSYS_get_current_task() == TaskBaseCtrlCycx1High);
}


/**
 * \Reference
 *  RBSYS_RuntimeMeasure_IsrStart, Gen_SWCS_HSW_uC_Base_SYS-222
 *
 * \Purpose
 *  Verification of function "RBSYS_RuntimeMeasure_IsrStart"
 *
 * \Sequence
 *  Call function "RBSYS_RuntimeMeasure_IsrStart"
 *
 * \ExpectedResult
 *  Function "rba_Runtime_IsrStart" must be called once
 *  Parameter "ISRType" must be forwarded as parameter for "rba_Runtime_IsrStart"
 */
SWTEST void TRBSYS_RuntimeMeasure_IsrStart(void)
{
  RBSYS_RuntimeMeasure_IsrStart(&Os_const_isrs[0]);

  SWT_EvalEq(TRBSYS_GetIsrStart_Counter(), 1);
  SWT_Eval(TRBSYS_get_current_isr() == &Os_const_isrs[0]);
}


/**
 * \Reference
 *  RBSYS_RuntimeMeasure_IsrEnd, Gen_SWCS_HSW_uC_Base_SYS-222
 *
 * \Purpose
 *  Verification of function "RBSYS_RuntimeMeasure_IsrEnd"
 *
 * \Sequence
 *  Call function "RBSYS_RuntimeMeasure_IsrEnd"
 *
 * \ExpectedResult
 *  Function "rba_Runtime_IsrEnd" must be called once
 *  Parameter "ISRType" must be forwarded as parameter for "rba_Runtime_IsrEnd"
 */
SWTEST void TRBSYS_RuntimeMeasure_IsrEnd(void)
{
  RBSYS_RuntimeMeasure_IsrEnd(&Os_const_isrs[0]);

  SWT_EvalEq(TRBSYS_GetIsrEnd_Counter(), 1);
  SWT_Eval(TRBSYS_get_current_isr() == &Os_const_isrs[0]);
}


#if (RBFS_MCORE == RBFS_MCORE_ON)
  /**
   * \Reference
   *  RBSYS_RuntimeMeasure_CrossCoreIntStart, Gen_SWCS_HSW_uC_Base_SYS-222
   *
   * \Purpose
   *  Verification of function "RBSYS_RuntimeMeasure_CrossCoreIntStart"
   *
   * \Sequence
   *  Call function "RBSYS_RuntimeMeasure_CrossCoreIntStart"
   *
   * \ExpectedResult
   *  Function "rba_Runtime_CrossCoreIntStart" must be called once
   */
  SWTEST void TRBSYS_RuntimeMeasure_CrossCoreIntStart(void)
  {
    RBSYS_RuntimeMeasure_CrossCoreIntStart();

    SWT_EvalEq(TRBSYS_GetCrossCoreIntStart_Counter(), 1);
  }


  /**
   * \Reference
   *  RBSYS_RuntimeMeasure_CrossCoreIntEnd, Gen_SWCS_HSW_uC_Base_SYS-222
   *
   * \Purpose
   *  Verification of function "RBSYS_RuntimeMeasure_CrossCoreIntEnd"
   *
   * \Sequence
   *  Call function "RBSYS_RuntimeMeasure_CrossCoreIntEnd"
   *
   * \ExpectedResult
   *  Function "rba_Runtime_CrossCoreIntEnd" must be called once
   */
  SWTEST void TRBSYS_RuntimeMeasure_CrossCoreIntEnd(void)
  {
    RBSYS_RuntimeMeasure_CrossCoreIntEnd();

    SWT_EvalEq(TRBSYS_GetCrossCoreIntEnd_Counter(), 1);
  }
#endif


/**
 * \Reference
 *  RBSYS_getSystemLoadCore0, Gen_SWCS_HSW_uC_Base_SYS-313
 *
 * \Purpose
 *  Verification of function "RBSYS_getSystemLoadCore0"
 *
 * \Sequence
 *  Call function "RBSYS_getSystemLoadCore0"
 *
 * \ExpectedResult
 *  Function "RBSYS_getSystemLoadCore0" must return the calculated value
 *  "rba_Runtime_MonSystemLoadPer64k_au16[0]" from rba_Runtime
 */
SWTEST void TRBSYS_getSystemLoadCore0(void)
{
  uint16 TRBSYS_SystemLoadCore0;

  TRBSYS_setSystemLoadCore0(0x1234);

  TRBSYS_SystemLoadCore0 = RBSYS_getSystemLoadCore0();

  SWT_EvalEq(TRBSYS_SystemLoadCore0, 0x1234);
}


#if (RBFS_MCORE == RBFS_MCORE_ON)
  /**
   * \Reference
   *  RBSYS_getSystemLoadCore1, Gen_SWCS_HSW_uC_Base_SYS-313
   *
   * \Purpose
   *  Verification of function "RBSYS_getSystemLoadCore1"
   *
   * \Sequence
   *  Call function "RBSYS_getSystemLoadCore1"
   *
   * \ExpectedResult
   *  Function "RBSYS_getSystemLoadCore1" must return the calculated value
   *  "rba_Runtime_MonSystemLoadPer64k_au16[1]" from rba_Runtime
   */
  SWTEST void TRBSYS_getSystemLoadCore1(void)
  {
    uint16 TRBSYS_SystemLoadCore1;

    TRBSYS_setSystemLoadCore1(0x4567);

    TRBSYS_SystemLoadCore1 = RBSYS_getSystemLoadCore1();

    SWT_EvalEq(TRBSYS_SystemLoadCore1, 0x4567);
  }
#endif


