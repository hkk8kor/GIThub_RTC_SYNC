#ifndef OS_H
#define OS_H

#include "RBSYS_Config.h" ///< stub config

/* -- Start expansion of <osminusconfig.h> -- */
/* File version information [BSW00402] */
#define OS_MODULE_ID (1U)
#define OS_VENDOR_ID (11U)

/// for OS_AR_MAJOR_VERSION etc.
#include "RBSYS_OsAutosarVersion.h"

#define OS_SW_MAJOR_VERSION (5U)
#define OS_SW_MINOR_VERSION (3U)
#define OS_SW_PATCH_VERSION (1U)

#include <Std_Types.h>  /* [$UKS 649] : Includes Std_Types.h EHI 93361 */
#ifndef STD_TYPES_H
  #error "STD_TYPES_H is not defined. This should appear in Std_Types.h (AUTOSAR requirement STD014). Is Std_Types.h in the include path? (try --samples:[Includes]overwrite -ISamples\Includes)"
#endif

typedef enum
{
  OSDEFAULTAPPMODE,
  AppModeBaseOS
}AppModeType;

typedef struct {
  // CONSTP2VAR(Os_ResourceDynType, OS_VAR, OS_CONST) dynamic;
  // Os_tpmaskType tpmask;
  // Os_imaskType imask;
  uint8 access;
  // ApplicationType application;
} Os_ResourceType;
typedef P2CONST(Os_ResourceType, TYPEDEF, OS_CONST) ResourceType;  /* [$UKS 202] */
extern Os_ResourceType OSStub_Core[2];

#define TASK(name)  void Os_Entry_##name(void)
#define ISR(name)   void Os_Entry_##name(void)

#define TASK_DEFINITION(name) \
  Os_TaskType name##_task_var = {\
      .id=(unsigned int)(&Os_Entry_##name),\
      .sim_type=0xDEADBEEFu,\
      .task_func = &Os_Entry_##name\
      };\
  const Os_TaskType* name = &name##_task_var


typedef unsigned int ISRType;
#define OS_ISRTYPE_TO_INDEX(isr)   (isr)

#define GetISRID(x)  0
#define INVALID_ISR  0

typedef struct Os_TaskType
{
  unsigned int id;
  unsigned int sim_type;
  void         (*task_func)(void);
  unsigned int index;

  /// private members
  int          isIndexSet;
}Os_TaskType;
typedef const Os_TaskType* TaskType;///< used by RTE (just a simple definition
#define INVALID_TASK  ((TaskType)0)
#define OS_TASKTYPE_TO_INDEX(task) ((task)->id)
/// - could be perhaps be the same like in original Os.h

/* OSApplications */
typedef unsigned long ApplicationType; /* [$UKS 411] */
#define INVALID_OSAPPLICATION ((ApplicationType)0U)  /* [$UKS 413] */

typedef void (*Os_AppErrorHookFunctionType)(StatusType e); /* [$UKS 450] */
#define OS_PSW (5U)
#define OS_SELID_0 (0U)
typedef uint32 Os_tmaskType; /* [$UKS 2047] */
typedef struct Os_ApplicationConfigurationType_s {
  ApplicationType app_id;
  uint8 access;
  Os_tmaskType tmask;
} Os_ApplicationConfigurationType;


typedef TaskType* TaskRefType;

typedef uint8 EventMaskType;  /* [$UKS 141] */
/* Timing */
typedef unsigned long TickType; /* [$UKS 276] */
typedef signed long SignedTickType;
typedef P2VAR(TickType, TYPEDEF, OS_VAR) TickRefType; /* [$UKS 277] */
typedef signed long Os_TimeLimitType;

typedef uint16 CoreIdType;  /* [$UKS 1608] */

#define OS_NUM_CORES (1U)

#define OS_CORE_ID_MASTER (0U)  /* [$UKS 1609] */
#if (RBFS_MCORE == RBFS_MCORE_ON)
  // real OS only defines core IDs in multi core configs, for single core configs it is stubbed in RBSYS
  #define OS_CORE_ID_0 (0U)
  #define OS_CORE_ID_1 (1U)
#endif

/// Flechsig: Used by RTE.
#ifndef STATUSTYPEDEFINED
  #define STATUSTYPEDEFINED
  typedef unsigned char StatusType; /* [$UKS 468] */
  #define E_OK ((StatusType)0U)
#endif /* STATUSTYPEDEFINED */
#define E_OS_ACCESS ((StatusType)1U)
#define E_OS_CALLEVEL ((StatusType)2U)
#define E_OS_ID ((StatusType)3U)
#define E_OS_LIMIT ((StatusType)4U)
#define E_OS_NOFUNC ((StatusType)5U)
#define E_OS_RESOURCE ((StatusType)6U)
#define E_OS_STATE ((StatusType)7U)
#define E_OS_VALUE ((StatusType)8U)
#define E_OS_SERVICEID ((StatusType)9U)
#define E_OS_ILLEGAL_ADDRESS ((StatusType)10U)
#define E_OS_MISSINGEND ((StatusType)11U)
#define E_OS_DISABLEDINT ((StatusType)12U)
#define E_OS_STACKFAULT ((StatusType)13U)
#define E_OS_PROTECTION_MEMORY ((StatusType)14U)
#define E_OS_PROTECTION_TIME ((StatusType)15U)
#define E_OS_PROTECTION_ARRIVAL ((StatusType)16U)
#define E_OS_PROTECTION_LOCKED ((StatusType)17U)
#define E_OS_PROTECTION_EXCEPTION ((StatusType)18U)
#define E_OS_CORE ((StatusType)19U)
#define E_OS_SPINLOCK ((StatusType)20U)
#define E_OS_INTERFERENCE_DEADLOCK ((StatusType)21U)
#define E_OS_NESTING_DEADLOCK ((StatusType)22U)
#define E_OS_SYS_NO_RESTART ((StatusType)23U)
#define E_OS_SYS_RESTART ((StatusType)24U)
#define E_OS_SYS_OVERRUN ((StatusType)25U)
typedef P2VAR(StatusType, TYPEDEF, OS_VAR) Os_StatusRefType;

/// Flechsig: ActivateTask used by FlexrayTask
typedef CONSTP2CONST(void, TYPEDEF, OS_VAR) Os_AnyType;

StatusType ActivateTask_impl(const void* proc_table,
                                    const char* task_name);

enum Os_TaskStateType {SUSPENDED = 0U, READY, WAITING, RUNNING};  /* [$UKS 43] [$UKS 47] */
typedef enum Os_TaskStateType TaskStateType;  /* [$UKS 57] */
typedef P2VAR(TaskStateType, TYPEDEF, OS_VAR) TaskStateRefType; /* [$UKS 58] */

#define ActivateTask(task) ActivateTask_impl(task,#task)

/// Flechsig: Used by RTE.
#define DeclareResource(x) /* [$UKS 203] */ /*lint -e(19) : DeclareResource has no content */

/// Flechsig: Used by MBPC
typedef uint16 CoreIdType;  /* [$UKS 1608] */

extern CoreIdType GetCoreID(void);

/* Alarms */
typedef struct {
  TickType maxallowedvalue;
  TickType ticksperbase;
  TickType mincycle;
} AlarmBaseType;  /* [$UKS 278] */
typedef P2VAR(AlarmBaseType, TYPEDEF, OS_VAR) AlarmBaseRefType; /* [$UKS 279] */
typedef struct Os_AlarmDynType_s {
  boolean running;
  TickType match;
  TickType period;
} Os_AlarmDynType;
typedef struct Os_AlarmType_s {
  uint8 config;
  uint8 access;
  ApplicationType application;
} Os_AlarmType;
typedef unsigned long AlarmType;  /* [$UKS 280] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, DeclareAlarm, ALARMCALLBACK) */
#define DeclareAlarm(x) /* [$UKS 281] */ /*lint -e(19) : DeclareAlarm has no content */

typedef void (*Os_AlarmCallbackType)(void);
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, ALARMCALLBACK) */
#define ALARMCALLBACK(x) FUNC(void, OS_CODE) Os_Cbk_Alarm_##x(void) /* [$UKS 274] */

/* Counters */
typedef struct {
  boolean Running;
  boolean Pending;
  TickType Delay;
} Os_CounterStatusType;  /* [$UKS 249] */
typedef P2VAR(Os_CounterStatusType, TYPEDEF, OS_VAR) Os_CounterStatusRefType; /* [$UKS 250] */

typedef TickType (*Os_HwCounterNowType)(void);  /* [$UKS 260] */
typedef void (*Os_HwCounterSetType)(TickType Value);  /* [$UKS 261] */
typedef void (*Os_HwCounterStateType)(Os_CounterStatusRefType State); /* [$UKS 262] */
typedef void (*Os_HwCounterCancelType)(void); /* [$UKS 263] */
typedef StatusType (*Os_CounterIncrAdvType)(void);
typedef FUNC(void, OS_CODE) (*Os_CounterStartType)(Os_AnyType ctr, TickType requested, TickType relative, TickRefType match_value);

typedef struct Os_CounterDynType_s {
  union {
    struct s_swd { /* [$UKS 211] */
      TickType count;
    } sw;
  } type_dependent; /* [MISRA 2012 Rule 19.2] */ /*lint !e9018 */
} Os_CounterDynType;
typedef struct Os_CounterType_s {
  CONSTP2VAR(Os_CounterDynType, OS_VAR, OS_CONST) dynamic;
  Os_CounterIncrAdvType advincr;
  AlarmBaseType base;
  uint8 access;
  ApplicationType application;
} Os_CounterType;
typedef P2CONST(Os_CounterType, TYPEDEF, OS_CONST) CounterType;  /* [$UKS 223] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, DeclareCounter) */
#define DeclareCounter(x) /* [$UKS  1183] */ /*lint -e(19) : DeclareCounter has no content */

struct Os_ScheduleTableDynType_s;
typedef struct Os_ScheduleTableType_s {
  CONSTP2VAR(struct Os_ScheduleTableDynType_s, OS_VAR, OS_CONST) dynamic;
  CounterType counter;
  boolean repeat;
  uint8 config;
  uint8 initial;
  uint8 access;
  ApplicationType application;
} Os_ScheduleTableType;
typedef P2CONST(Os_ScheduleTableType, TYPEDEF, OS_CONST) ScheduleTableType;  /* [$UKS 326] */

#define StartCore Os_StartCore
#define GetTaskState Os_GetTaskState
extern void Os_StartCore(CoreIdType CoreID, Os_StatusRefType Status) /* [$UKS 1626] */;

#define ShutdownAllCores Os_ShutdownAllCores
extern void Os_ShutdownAllCores(StatusType Error) /* [$UKS 1518] */;

#define StartOS(x)  ;  /*dead - requires semicolon because original is a while(1) loop*/
#define ShutdownOS(x)  /*dead*/

static inline StatusType GetResource(ResourceType ResID){return E_OK;}
static inline StatusType ReleaseResource(ResourceType ResID){return E_OK;}

typedef enum {PRO_IGNORE = 0U, PRO_TERMINATETASKISR, PRO_TERMINATEAPPL, PRO_TERMINATEAPPL_RESTART, PRO_SHUTDOWN} ProtectionReturnType; /* [$UKS 589] [$UKS 590] [$UKS 591] */

/// returns currently running task - right now not implemented in OSSim (can be implemented in project specific code)
#define GetTaskID Os_GetTaskID
extern StatusType Os_GetTaskID(TaskRefType TaskID);
extern FUNC(StatusType, OS_CODE) Os_GetTaskState(TaskType TaskID, TaskStateRefType State) /* [$UKS 89] */;

/// currently don't know how to identify the func to call.
/// func-table unknown. Just stubbed dead. R.Flechsig 27-Apr-2021
/// need do-while, because it is used with (void) [ignore return code] so
/// compiler expects something.
#define CallTrustedFunction(func_index, context)  callTrustedFake()
static inline int callTrustedFake(void){return 0;}

#include "Os_Cfg.h" ///< Tasks / need to be last to avoid cyclomatic dependency.

#endif /* OS_H */
