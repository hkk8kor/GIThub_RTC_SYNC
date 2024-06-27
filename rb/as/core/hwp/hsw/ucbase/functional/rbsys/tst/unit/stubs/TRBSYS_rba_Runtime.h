#ifndef TRBSYS_RBA_RUNTIME_H__
#define TRBSYS_RBA_RUNTIME_H__

#include "Os.h"
#include "RBSYS_Config.h"

#define RBA_RUNTIME_MSR_PROC(PROCNAME)   ((PROCNAME)())

extern uint16 rba_Runtime_MonSystemLoadPer64k_au16[RB_NUM_CORES];

extern void rba_Runtime_CrossCoreIntStart(void);
extern void rba_Runtime_CrossCoreIntEnd(void);
extern void rba_Runtime_IsrStart(ISRType isrId);
extern void rba_Runtime_IsrEnd(ISRType isrId);
extern void rba_Runtime_TaskStart(TaskType taskId);
extern void rba_Runtime_TaskEnd(TaskType taskId);

extern void rba_Runtime_PreOSInit(void);
extern void rba_Runtime_Init(void);
extern void rba_Runtime_MainFunction(void);
extern void rba_Runtime_MonSystemLoadInit(void);

extern uint8 TRBSYS_GetPreOSInit_Counter(void);
extern uint8 TRBSYS_GetInit_Counter(void);
extern uint8 TRBSYS_GetMainFunction_Counter(void);
extern uint8 TRBSYS_GetMonSystemLoadInit_Counter(void);

extern uint8 TRBSYS_GetCrossCoreIntStart_Counter(void);
extern uint8 TRBSYS_GetCrossCoreIntEnd_Counter(void);
extern uint8 TRBSYS_GetIsrStart_Counter(void);
extern uint8 TRBSYS_GetIsrEnd_Counter(void);
extern uint8 TRBSYS_GetTaskStart_Counter(void);
extern uint8 TRBSYS_GetTaskEnd_Counter(void);


/* helpers */
extern ISRType TRBSYS_get_current_isr(void);
extern TaskType TRBSYS_get_current_task(void);

extern void TRBSYS_setSystemLoadCore0(uint16 load);
#if (RBFS_MCORE == RBFS_MCORE_ON)
extern void TRBSYS_setSystemLoadCore1(uint16 load);
#endif



#endif
