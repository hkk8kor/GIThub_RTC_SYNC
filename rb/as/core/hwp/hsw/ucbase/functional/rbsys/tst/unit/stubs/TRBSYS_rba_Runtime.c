#include "SwTest_Global.h"                      // for SWT functionality
#include "RBSYS_Config.h"

#include "TRBSYS_rba_Runtime.h"
#include "Os.h"


uint16 rba_Runtime_MonSystemLoadPer64k_au16[RB_NUM_CORES];

/* helper functionality */
static uint8 TRBSYS_PreOSInit_Counter = 0;
uint8 TRBSYS_GetPreOSInit_Counter(void)
{
  return TRBSYS_PreOSInit_Counter;
}

static uint8 TRBSYS_Init_Counter = 0;
uint8 TRBSYS_GetInit_Counter(void)
{
  return TRBSYS_Init_Counter;
}

static uint8 TRBSYS_MainFunction_Counter = 0;
uint8 TRBSYS_GetMainFunction_Counter(void)
{
  return TRBSYS_MainFunction_Counter;
}

static uint8 TRBSYS_MonSystemLoadInit_Counter = 0;
uint8 TRBSYS_GetMonSystemLoadInit_Counter(void)
{
  return TRBSYS_MonSystemLoadInit_Counter;
}

static uint8 TRBSYS_CrossCoreIntStart_Counter = 0;
uint8 TRBSYS_GetCrossCoreIntStart_Counter(void)
{
  return TRBSYS_CrossCoreIntStart_Counter;
}

static uint8 TRBSYS_CrossCoreIntEnd_Counter = 0;
uint8 TRBSYS_GetCrossCoreIntEnd_Counter(void)
{
  return TRBSYS_CrossCoreIntEnd_Counter;
}

static uint8 TRBSYS_IsrStart_Counter = 0;
uint8 TRBSYS_GetIsrStart_Counter(void)
{
  return TRBSYS_IsrStart_Counter;
}

static uint8 TRBSYS_IsrEnd_Counter = 0;
uint8 TRBSYS_GetIsrEnd_Counter(void)
{
  return TRBSYS_IsrEnd_Counter;
}

static uint8 TRBSYS_TaskStart_Counter = 0;
uint8 TRBSYS_GetTaskStart_Counter(void)
{
  return TRBSYS_TaskStart_Counter;
}

static uint8 TRBSYS_TaskEnd_Counter = 0;
uint8 TRBSYS_GetTaskEnd_Counter(void)
{
  return TRBSYS_TaskEnd_Counter;
}

static ISRType TRBSYS_IsrType;
ISRType TRBSYS_get_current_isr(void)
{
  return TRBSYS_IsrType;
}

static TaskType TRBSYS_TaskType;
TaskType TRBSYS_get_current_task(void)
{
  return TRBSYS_TaskType;
}



/* rba_Runtime stubs */
void rba_Runtime_PreOSInit(void)
{
  TRBSYS_PreOSInit_Counter++;
}

void rba_Runtime_Init(void)
{
  TRBSYS_Init_Counter++;
}

void rba_Runtime_MainFunction(void)
{
  TRBSYS_MainFunction_Counter++;
}

void rba_Runtime_MonSystemLoadInit(void)
{
  TRBSYS_MonSystemLoadInit_Counter++;
}

void rba_Runtime_CrossCoreIntStart(void)
{
  TRBSYS_CrossCoreIntStart_Counter++;
}

void rba_Runtime_CrossCoreIntEnd(void)
{
  TRBSYS_CrossCoreIntEnd_Counter++;
}

void rba_Runtime_IsrStart(ISRType nIsrType)
{
  TRBSYS_IsrStart_Counter++;
  TRBSYS_IsrType = nIsrType;
}

void rba_Runtime_IsrEnd(ISRType nIsrType)
{
  TRBSYS_IsrEnd_Counter++;
  TRBSYS_IsrType = nIsrType;
}

void rba_Runtime_TaskStart(TaskType nTaskType)
{
  TRBSYS_TaskStart_Counter++;
  TRBSYS_TaskType = nTaskType;
}

void rba_Runtime_TaskEnd(TaskType nTaskType)
{
  TRBSYS_TaskEnd_Counter++;
  TRBSYS_TaskType = nTaskType;
}

void TRBSYS_setSystemLoadCore0(uint16 load)
{
  rba_Runtime_MonSystemLoadPer64k_au16[0] = load;
}

#if (RBFS_MCORE == RBFS_MCORE_ON)
  void TRBSYS_setSystemLoadCore1(uint16 load)
  {
    rba_Runtime_MonSystemLoadPer64k_au16[1] = load;
  }
#endif