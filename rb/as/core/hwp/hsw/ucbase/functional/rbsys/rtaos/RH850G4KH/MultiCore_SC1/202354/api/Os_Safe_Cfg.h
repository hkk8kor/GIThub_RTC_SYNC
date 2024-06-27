#include "Os_Target_Cfg.h"
#define OS_NUM_APPMODES (2U)
#define OS_NUM_APPLICATIONS (2U)
#define OS_NUM_SPINLOCKS (0U)
#define OS_NUM_TRUSTED_FUNCTIONS (0U)
#define OS_NUM_IOC_CALLBACK_FUNCTIONS (Os_const_ioc_function_count)
#define OS_NUM_EVENTS (0U)
#define OS_NUM_TASKS (14U)
#define OS_NUM_ISRS (12U)
#define OS_NUM_RESOURCES (2U)
#define OS_NUM_ALARMS (0U)
#define OS_NUM_SCHEDULETABLES (0U)
#define OS_NUM_PERIPHERALAREAS (0U)
#define OS_NUM_TRACEPOINTS (2U)
#define OS_NUM_TASKTRACEPOINTS (0U)
#define OS_NUM_INTERVALS (0U)
#define OS_NUM_TRACECATEGORIES (0U)
#define OS_TRACE_CATEGORY_ALWAYS ((Os_TraceCategoriesType)(0x80000000UL))
#define OS_TRACE_CATEGORY_NEVER  ((Os_TraceCategoriesType)(0x00000000UL))
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_TICKS2*) */
#define OS_NUM_COUNTERS (0U)
#define OSCYCLEDURATION (1000) /* [$UKS 1224] */
#define OSCYCLESPERSECOND (1000000U) /* [$UKS 1225] */
#define OSSWTICKDURATION (1000) /* [$UKS 1226] */
#define OSSWTICKSPERSECOND (1000000U) /* [$UKS 1227] */
#define OSMAXALLOWEDVALUE OSMAXALLOWEDVALUE_SystemCounter /* [$UKS 215] */
#define OSTICKSPERBASE OSTICKSPERBASE_SystemCounter /* [$UKS 216] */
#define OSMINCYCLE OSMINCYCLE_SystemCounter /* [$UKS 218] */
#define OSTICKDURATION OSTICKDURATION_SystemCounter /* [$UKS 217] */
#define OS_NUM_CORES (2U)
#define OS_NUM_OS_CORES (2U)
#define OS_CORE_ID_MASTER (0U)  /* [$UKS 1609] */
/* [$UKS 1611] */
#define OS_CORE_ID_0 (0U)
#define OS_CORE_ID_1 (1U)

/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_CODE) Os_Entry_TaskBaseCtrlCycx24(void);
extern FUNC(void, OS_CODE) Os_Entry_TaskBaseCtrlCycx8(void);
extern FUNC(void, OS_CODE) Os_Entry_TaskBaseCtrlCycx4(void);
extern FUNC(void, OS_CODE) Os_Entry_TaskBaseCtrlCycx2p(void);
extern FUNC(void, OS_CODE) Os_Entry_TaskBaseCtrlCycx2(void);
extern FUNC(void, OS_CODE) Os_Entry_TaskBaseCtrlCycx1Low(void);
extern FUNC(void, OS_CODE) Os_Entry_TaskFlexray(void);
extern FUNC(void, OS_CODE) Os_Entry_TaskBaseCtrlCycx1High(void);
extern FUNC(void, OS_CODE) Os_Entry_Task1ms(void);
extern FUNC(void, OS_CODE) Os_Entry_Task0p5ms(void);
extern FUNC(void, OS_CODE) Os_Entry_TaskInitP(void);
extern FUNC(void, OS_CODE) Os_Entry_TaskInit(void);
extern FUNC(void, OS_CODE) Os_Entry_TaskTPSWKillCore0(void);
extern FUNC(void, OS_CODE) Os_Entry_TaskTPSWKillCore1(void);
extern FUNC(void, OS_CODE) Os_Entry_ISRCAN0REC(void);
extern FUNC(void, OS_CODE) Os_Entry_ISRCAN0TRX(void);
extern FUNC(void, OS_CODE) Os_Entry_ISRCAN1REC(void);
extern FUNC(void, OS_CODE) Os_Entry_ISRCAN1TRX(void);
extern FUNC(void, OS_CODE) Os_Entry_ISRCAN2REC(void);
extern FUNC(void, OS_CODE) Os_Entry_ISRCAN2TRX(void);
extern FUNC(void, OS_CODE) Os_Entry_ISRCAN3REC(void);
extern FUNC(void, OS_CODE) Os_Entry_ISRCAN3TRX(void);
extern FUNC(void, OS_CODE) Os_Entry_ISRFLX0LINE0(void);
extern FUNC(void, OS_CODE) Os_Entry_ISRSTM04(void);
extern FUNC(void, OS_CODE) Os_Entry_ISRSTM05(void);
extern FUNC(void, OS_CODE) Os_Entry_ISRSWINT0(void);
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
