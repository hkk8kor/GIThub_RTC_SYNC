#ifndef TRBSYS_OS_H__
#define TRBSYS_OS_H__

#include "SwTest_Global.h"                      // for SWT functionality
#include "RBSYS_Config.h"

#define OS_VOLATILE volatile

#if (RBFS_MCORE == RBFS_MCORE_ON)
  #define OS_CORE_ID_0     (0U)
  #define OS_CORE_ID_1     (1U)
#endif

// actually defined in Os_Cfg.h but only Os.h includes it
#if (RBFS_MCORE == RBFS_MCORE_ON)
  #define OS_CORE_FOR_ISRSTM04            (1u)
  #define OS_CORE_FOR_ISRSTM05            (0u)
  #define OS_CORE_FOR_ISRCommonTimer      (1u)
  #define OS_CORE_FOR_TaskBaseCtrlCycx1High (0u)
  #define OS_CORE_FOR_ISRSWINT0             (1u)
#endif


#define OS_APPL_CODE
#define OS_CALLOUT_CODE

// already defined in "rb/as/core/hwp/hsw/tools/tst/unit/CoreStubs/api/Std_Types.h"
#ifndef STATUSTYPEDEFINED
  #define STATUSTYPEDEFINED
  typedef unsigned char StatusType;
  #define E_OK            ((StatusType)0u)
#endif
#define E_OS_LIMIT        ((StatusType)4u)
#define E_OS_NOFUNC       ((StatusType)5u)

enum Os_TaskStateType {SUSPENDED = 0U, READY, WAITING, RUNNING};
typedef enum Os_TaskStateType TaskStateType;
typedef TaskStateType* TaskStateRefType;
typedef void (*Os_VoidVoidFunctionType)(void);


typedef struct {
  uint32 task;
  TaskStateType State;
  Os_VoidVoidFunctionType entry_function;
} Os_TaskType;


typedef struct {
  uint32 isr;
  void(*entry_function)(void);
} Os_ISRType;


typedef Os_TaskType* TaskType;
typedef Os_ISRType* ISRType;
typedef TaskType* TaskRefType;


#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  #define OS_NUM_TASKS  18
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  #define OS_NUM_TASKS  19
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  #define OS_NUM_TASKS  16
#else
  #define OS_NUM_TASKS  14
#endif

#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
    #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
      #define OS_NUM_ISRS   14
    #else
      #define OS_NUM_ISRS   13
    #endif
  #else
    #define OS_NUM_ISRS   15
  #endif
#else
  #define OS_NUM_ISRS   1
#endif


extern Os_TaskType Os_const_tasks0[OS_NUM_TASKS];
extern const TaskType Os_const_tasks[OS_NUM_TASKS];

extern Os_ISRType Os_const_isrs[OS_NUM_ISRS];


#define TaskBaseCtrlCycx24                  (&Os_const_tasks0[0u])
#define TaskBaseCtrlCycx8                   (&Os_const_tasks0[1u])
#define TaskBaseCtrlCycx4                   (&Os_const_tasks0[2u])
#define TaskBaseCtrlCycx2p                  (&Os_const_tasks0[3u])
#define TaskBaseCtrlCycx2                   (&Os_const_tasks0[4u])
#define TaskBaseCtrlCycx1Low                (&Os_const_tasks0[5u])
#define TaskFlexray                         (&Os_const_tasks0[6u])
#define TaskBaseCtrlCycx1High               (&Os_const_tasks0[7u])
#define Task1ms                             (&Os_const_tasks0[8u])
#define Task0p5ms                           (&Os_const_tasks0[9u])
#define TaskInitP                           (&Os_const_tasks0[10u])
#define TaskInit                            (&Os_const_tasks0[11u])
#define TaskTPSWKillCore0                   (&Os_const_tasks0[12u])
#define TaskTPSWKillCore1                   (&Os_const_tasks0[13u])

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  #define TaskBaseCtrlCycx4pLow             (&Os_const_tasks0[14u])
  #define TaskBaseCtrlCycx200Background     (&Os_const_tasks0[15u])
  #define TaskEventCtrlExtPrio1             (&Os_const_tasks0[16u])
  #define TaskEventCtrlExtPrio2             (&Os_const_tasks0[17u])
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  #define TaskBaseCtrlCycx1Guest            (&Os_const_tasks0[14u])
  #define TaskBaseCtrlCycx2Guest            (&Os_const_tasks0[15u])
  #define TaskBaseCtrlCycx4Guest            (&Os_const_tasks0[16u])
  #define TaskBaseCtrlCycx10Guest           (&Os_const_tasks0[17u])
  #define TaskBaseCtrlCycx20Guest           (&Os_const_tasks0[18u])
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  #define TaskBaseCtrlCycx10                (&Os_const_tasks0[14u])
  #define TaskBaseCtrlCycx20                (&Os_const_tasks0[15u])
#endif


#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
  #define ISRFLX0LINE0              (&Os_const_isrs[0u])
  #define ISRFLX1LINE0              (&Os_const_isrs[1u])
  #define ISRSTM04                  (&Os_const_isrs[2u])
  #define ISRSTM05                  (&Os_const_isrs[3u])
  #define ISRSWINT0                 (&Os_const_isrs[4u])
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    #define ISRMCAN0I0              (&Os_const_isrs[5u])
    #define ISRMCAN1I0              (&Os_const_isrs[6u])
    #define ISRMCAN2I0              (&Os_const_isrs[7u])
    #define ISRMTTCANI0             (&Os_const_isrs[8u])
    #define ISRRLIN30RX             (&Os_const_isrs[9u])
    #define ISRRLIN30STATUS         (&Os_const_isrs[10u])
    #define ISRRLIN31RX             (&Os_const_isrs[11u])
    #define ISRRLIN31STATUS         (&Os_const_isrs[12u])
    #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
      #define ISR0p5ms                (&Os_const_isrs[13u])
    #endif
  #else
    #define ISRCAN0REC              (&Os_const_isrs[5u])
    #define ISRCAN0TRX              (&Os_const_isrs[6u])
    #define ISRCAN1REC              (&Os_const_isrs[7u])
    #define ISRCAN1TRX              (&Os_const_isrs[8u])
    #define ISRCAN2REC              (&Os_const_isrs[9u])
    #define ISRCAN2TRX              (&Os_const_isrs[10u])
    #define ISRCAN6REC              (&Os_const_isrs[11u])
    #define ISRCAN6TRX              (&Os_const_isrs[12u])
    #define ISRCAN8REC              (&Os_const_isrs[13u])
    #define ISRCAN8TRX              (&Os_const_isrs[14u])
  #endif
#else
  #define ISRCommonTimer            (&Os_const_isrs[0u])
#endif

typedef unsigned int Os_StopwatchTickType;

extern void TRBSYS_SetTaskState(TaskType TaskID, TaskStateType State);
extern StatusType GetTaskState(TaskType TaskID, TaskStateRefType State);

typedef uint16 CoreIdType;


#define OS_TASKTYPE_TO_INDEX(tasktype) (tasktype - &Os_const_tasks0[0])
#define OS_INDEX_TO_TASKTYPE(index) ((TaskType)(Os_const_tasks[(index)]))

#define OS_ISRTYPE_TO_INDEX(isrtype) (isrtype - &Os_const_isrs[0])
#define OS_INDEX_TO_ISRTYPE(index) ((ISRType)&Os_const_isrs[(index)])

#define TASK(x) void Os_Entry_##x(void)
#define ISR(x) void Os_Entry_##x(void)

extern TaskType TRBSYS_CurrentTask;
extern StatusType GetTaskID(TaskRefType TaskID);


extern uint32 TRBSYS_TerminateTask_cnt;
extern void TerminateTask(void);

extern void Os_Entry_TaskBaseCtrlCycx24(void);
extern void Os_Entry_TaskBaseCtrlCycx8(void);
extern void Os_Entry_TaskBaseCtrlCycx4(void);
extern void Os_Entry_TaskBaseCtrlCycx2p(void);
extern void Os_Entry_TaskBaseCtrlCycx2(void);
extern void Os_Entry_TaskBaseCtrlCycx1Low(void);
extern void Os_Entry_TaskFlexray(void);
extern void Os_Entry_TaskBaseCtrlCycx1High(void);
extern void Os_Entry_Task1ms(void);
extern void Os_Entry_Task0p5ms(void);
extern void Os_Entry_TaskInitP(void);
extern void Os_Entry_TaskInit(void);
extern void Os_Entry_TaskTPSWKillCore0(void);
extern void Os_Entry_TaskTPSWKillCore1(void);
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  extern void Os_Entry_TaskBaseCtrlCycx4pLow(void);
  extern void Os_Entry_TaskBaseCtrlCycx200Background(void);
  extern void Os_Entry_TaskEventCtrlExtPrio1(void);
  extern void Os_Entry_TaskEventCtrlExtPrio2(void);
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  extern void Os_Entry_TaskBaseCtrlCycx1Guest(void);
  extern void Os_Entry_TaskBaseCtrlCycx2Guest(void);
  extern void Os_Entry_TaskBaseCtrlCycx4Guest(void);
  extern void Os_Entry_TaskBaseCtrlCycx10Guest(void);
  extern void Os_Entry_TaskBaseCtrlCycx20Guest(void);
#endif


extern void Os_Entry_ISRFLX0LINE0(void);
extern void Os_Entry_ISRFLX1LINE0(void);
extern void Os_Entry_ISRSTM04(void);
extern void Os_Entry_ISRSTM05(void);
extern void Os_Entry_ISRCommonTimer(void);
extern void Os_Entry_ISRSWINT0(void);

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  extern void Os_Entry_ISRRLIN30STATUS(void);
  extern void Os_Entry_ISRRLIN30RX(void);
  extern void Os_Entry_ISRRLIN31STATUS(void);
  extern void Os_Entry_ISRRLIN31RX(void);
  extern void Os_Entry_ISRMCAN0I0(void);
  extern void Os_Entry_ISRMCAN1I0(void);
  extern void Os_Entry_ISRMCAN2I0(void);
  extern void Os_Entry_ISRMTTCANI0(void);
#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  extern void Os_Entry_ISRCAN0REC(void);
  extern void Os_Entry_ISRCAN0TRX(void);
  extern void Os_Entry_ISRCAN1REC(void);
  extern void Os_Entry_ISRCAN1TRX(void);
  extern void Os_Entry_ISRCAN2REC(void);
  extern void Os_Entry_ISRCAN2TRX(void);
  extern void Os_Entry_ISRCAN6REC(void);
  extern void Os_Entry_ISRCAN6TRX(void);
  extern void Os_Entry_ISRCAN8REC(void);
  extern void Os_Entry_ISRCAN8TRX(void);
#endif



#define CAT1_ISR(x) void Os_CAT1_ISR_##x(void)

extern void Os_CAT1_ISR_EXCHVTRAP(void);
extern void Os_CAT1_ISR_EXCFETRAP(void);
extern void Os_CAT1_ISR_EXCUCPOP(void);
extern void Os_CAT1_ISR_EXCFENMI(void);
extern void Os_CAT1_ISR_EXCPIE(void);
extern void Os_CAT1_ISR_EXCMDP(void);
extern void Os_CAT1_ISR_ISRSTM06_SC4core0(void);
extern void Os_CAT1_ISR_ISRSTM07_SC4core1(void);
extern void Os_CAT1_ISR_ISRGenericTimerCore0(void);
extern void Os_CAT1_ISR_ISRGenericTimerCore1(void);


extern void InvalidInt(void);

// OS callbacks
extern boolean Os_Cbk_Idle(void);
extern Os_StopwatchTickType Os_Cbk_GetStopwatch(void);
extern void Os_Cbk_TaskStart(TaskType task);
extern void Os_Cbk_TaskEnd(TaskType task);
extern void Os_Cbk_CrosscoreISRStart(CoreIdType core_id);
extern void Os_Cbk_CrosscoreISREnd(CoreIdType core_id);
extern void Os_Cbk_ISRStart(ISRType isr);
extern void Os_Cbk_ISREnd(ISRType isr);



#ifdef FUNC
  #undef FUNC
#endif

#define FUNC(type, os_callout_code)  type

typedef uint8 OSServiceIdType;
extern OSServiceIdType OSErrorGetServiceId(void);
extern void TRBSYS_SetServiceId(OSServiceIdType nServiceID);

#define OSServiceId_None                      ((OSServiceIdType)0u)
#define OSServiceId_ActivateTask              ((OSServiceIdType)1u)
#define OSServiceId_Os_AdvanceCounter         ((OSServiceIdType)2u)

static Os_TaskType activateTask = {0x0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx1High};
extern TaskType OSError_ActivateTask_TaskID(void);

extern void ErrorHook(StatusType Error);


#define OSDEFAULTAPPMODE    (1U)

typedef uint8_least AppModeType;
typedef StatusType *Os_StatusRefType;

#define TRBSYS_OK ((StatusType)0U)

extern uint32 TRBSYS_Os_InitializeVectorTable_cnt;
extern uint32 TRBSYS_StartOS_cnt;
extern uint32 TRBSYS_StartCore_cnt[RB_NUM_CORES];
extern uint32 TRBSYS_Os_AwaitStartup_cnt;
extern uint32 TRBSYS_Os_StartCoreGate_cnt;

extern uint32 TRBSYS_Os_InitializeVectorTable_EBASEManipulation;
extern void Os_InitializeVectorTable(void);
extern boolean StartOS(AppModeType Mode);
extern void StartCore(CoreIdType CoreID, Os_StatusRefType Status);

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
extern StatusType Os_AwaitStartup(void);
#endif

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
extern void Os_AwaitStartup(void);
#endif

#if (RBFS_uCFamily == RBFS_uCFamily_STMStellar)
extern void Os_StartCoreGate(void);
#endif


// must be implemented as inline function to ensure correct evaluation on #define TRBSYS_DYN_ADAPTOR_H__
static inline void TRBSYS_TaskWrapper(TaskType TaskID)
{

  #ifdef TRBSYS_DYN_ADAPTOR_H__   /* Os_Cbk_xxx and Os_Entry_xxx are only implemented within RBSYS_Dyn and
                                   * therefore it could be only used within RBSYS_Dyn UnitTest */

    Os_Cbk_TaskStart(TaskID);

    switch (OS_TASKTYPE_TO_INDEX(TaskID))
    {
      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx24):
      {
        Os_Entry_TaskBaseCtrlCycx24();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx8):
      {
        Os_Entry_TaskBaseCtrlCycx8();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx4):
      {
        Os_Entry_TaskBaseCtrlCycx4();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx2p):
      {
        Os_Entry_TaskBaseCtrlCycx2p();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx2):
      {
        Os_Entry_TaskBaseCtrlCycx2();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx1Low):
      {
        Os_Entry_TaskBaseCtrlCycx1Low();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskFlexray):
      {
        Os_Entry_TaskFlexray();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx1High):
      {
        Os_Entry_TaskBaseCtrlCycx1High();
      } break;

      case OS_TASKTYPE_TO_INDEX(Task1ms):
      {
        Os_Entry_Task1ms();
      } break;

      case OS_TASKTYPE_TO_INDEX(Task0p5ms):
      {
        Os_Entry_Task0p5ms();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskInitP):
      {
        Os_Entry_TaskInitP();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskInit):
      {
        Os_Entry_TaskInit();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskTPSWKillCore0):
      {
        Os_Entry_TaskTPSWKillCore0();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskTPSWKillCore1):
      {
        Os_Entry_TaskTPSWKillCore1();
      } break;

    #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx4pLow):
      {
        Os_Entry_TaskBaseCtrlCycx4pLow();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx200Background):
      {
        Os_Entry_TaskBaseCtrlCycx200Background();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskEventCtrlExtPrio1):
      {
        Os_Entry_TaskEventCtrlExtPrio1();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskEventCtrlExtPrio2):
      {
        Os_Entry_TaskEventCtrlExtPrio2();
      } break;
    #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx1Guest):
      {
        Os_Entry_TaskBaseCtrlCycx1Guest();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx2Guest):
      {
        Os_Entry_TaskBaseCtrlCycx2Guest();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx4Guest):
      {
        Os_Entry_TaskBaseCtrlCycx4Guest();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx10Guest):
      {
        Os_Entry_TaskBaseCtrlCycx10Guest();
      } break;

      case OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx20Guest):
      {
        Os_Entry_TaskBaseCtrlCycx20Guest();
      } break;
    #endif
      default:
      {

      } break;
    }

    Os_Cbk_TaskEnd(TaskID);

  #endif
}

extern boolean TRBSYS_TaskChainingEnabled;
extern boolean TRBSYS_TaskActivationDoneOnce;
extern boolean TRBSYS_isTaskChainingEnabled(void);

/* must be implemented as inline function due to RBSYS_Dyn.c dependency: implementation is dependend on #define within TRBSYS_TaskWrapper */
static inline StatusType ActivateTask(TaskType TaskID)
{
  if(TRBSYS_isTaskChainingEnabled())
  {
    TRBSYS_TaskWrapper(TaskID);

    TaskID->task++;
  }
  return (StatusType)0;
}

static inline void TRBSYS_RunTaskStandalone(TaskType TaskID)
{
  TRBSYS_TaskChainingEnabled = FALSE;
  TRBSYS_TaskActivationDoneOnce = FALSE;
  ActivateTask(TaskID);
  TRBSYS_TaskChainingEnabled = TRUE;  // reset default behavior to task chaining, e.g. for following ISR function calls
}

static inline void TRBSYS_RunTaskChained(TaskType TaskID)
{
  TRBSYS_TaskChainingEnabled = TRUE;
  TRBSYS_TaskActivationDoneOnce = FALSE;
  ActivateTask(TaskID);
}

static inline void Os_CacheCoreID (void)
{
  // to be tested
}


#endif