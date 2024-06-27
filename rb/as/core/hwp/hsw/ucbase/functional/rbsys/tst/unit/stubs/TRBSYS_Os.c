#include "TRBSYS_Os.h"
#include "RBSYS_Config.h"
#include "TRBSYS_Intrinsics.h"

Os_ISRType Os_const_isrs[OS_NUM_ISRS];
Os_TaskType Os_const_tasks0[OS_NUM_TASKS] = {
  { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx24 },
  { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx8 },
  { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx4 },
  { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx2p },
  { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx2 },
  { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx1Low },
  { 0, SUSPENDED, Os_Entry_TaskFlexray },
  { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx1High },
  { 0, SUSPENDED, Os_Entry_Task1ms },
  { 0, SUSPENDED, Os_Entry_Task0p5ms },
  { 0, SUSPENDED, Os_Entry_TaskInitP },
  { 0, SUSPENDED, Os_Entry_TaskInit },
  { 0, SUSPENDED, Os_Entry_TaskTPSWKillCore0 },
  { 0, SUSPENDED, Os_Entry_TaskTPSWKillCore1 },
  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
    { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx4pLow },
    { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx200Background },
    { 0, SUSPENDED, Os_Entry_TaskEventCtrlExtPrio1 },
    { 0, SUSPENDED, Os_Entry_TaskEventCtrlExtPrio2 },
  #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
    { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx1Guest },
    { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx2Guest },
    { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx4Guest },
    { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx10Guest },
    { 0, SUSPENDED, Os_Entry_TaskBaseCtrlCycx20Guest },
  #endif
};

const TaskType Os_const_tasks[OS_NUM_TASKS] = {
  &Os_const_tasks0[0u],
  &Os_const_tasks0[1u],
  &Os_const_tasks0[2u],
  &Os_const_tasks0[3u],
  &Os_const_tasks0[4u],
  &Os_const_tasks0[5u],
  &Os_const_tasks0[6u],
  &Os_const_tasks0[7u],
  &Os_const_tasks0[8u],
  &Os_const_tasks0[9u],
  &Os_const_tasks0[10u],
  &Os_const_tasks0[11u],
  &Os_const_tasks0[12u],
  &Os_const_tasks0[13u],
  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
    &Os_const_tasks0[14u],
    &Os_const_tasks0[15u],
    &Os_const_tasks0[16u],
    &Os_const_tasks0[17u],
  #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
    &Os_const_tasks0[14u],
    &Os_const_tasks0[15u],
    &Os_const_tasks0[16u],
    &Os_const_tasks0[17u],
    &Os_const_tasks0[18u],
  #endif
};

TaskType TRBSYS_CurrentTask = NULL;
StatusType GetTaskID(TaskRefType TaskID){
  if(TRBSYS_CurrentTask != NULL)
  {
    *TaskID = TRBSYS_CurrentTask;
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
};

uint32 TRBSYS_TerminateTask_cnt = 0;
void TerminateTask(void)
{
  TRBSYS_TerminateTask_cnt++;
}


void TRBSYS_SetTaskState(TaskType TaskID, TaskStateType State)
{
  TaskID->State = State;
}


StatusType GetTaskState(TaskType TaskID, TaskStateRefType State)
{
  *State = TaskID->State;
  return (StatusType)0;
}


OSServiceIdType serviceID;

OSServiceIdType OSErrorGetServiceId(void)
{
  return serviceID;
}

void TRBSYS_SetServiceId(OSServiceIdType nServiceID)
{
  serviceID = nServiceID;
}

TaskType OSError_ActivateTask_TaskID(void)
{
  return &activateTask;
}

uint32 TRBSYS_Os_InitializeVectorTable_EBASEManipulation = 0xDEADBEEFu;
uint32 TRBSYS_Os_InitializeVectorTable_cnt = 0;
void Os_InitializeVectorTable(void)
{
  TRBSYS_Os_InitializeVectorTable_cnt++;
  #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A))
    if( TRBSYS_Os_InitializeVectorTable_EBASEManipulation == 0xDEADBEEFu )
    {
      TRBSYS_SetSystemRegister(3, 1, (1<<0)); //< write EBASE.RINT = 1
    }
    else
    {
      TRBSYS_SetSystemRegister(3, 1, TRBSYS_Os_InitializeVectorTable_EBASEManipulation);
    }
  #endif
}

uint32 TRBSYS_StartOS_cnt = 0;
boolean StartOS(AppModeType Mode)
{
  TRBSYS_StartOS_cnt++;
  return TRUE;
}

uint32 TRBSYS_StartCore_cnt[RB_NUM_CORES];
void StartCore(CoreIdType CoreID, Os_StatusRefType Status)
{
  TRBSYS_StartCore_cnt[CoreID]++;
}

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  uint32 TRBSYS_Os_AwaitStartup_cnt = 0;

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  StatusType Os_AwaitStartup(void)
  #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  void Os_AwaitStartup(void)
  #endif
  {
    TRBSYS_Os_AwaitStartup_cnt++;
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      return 0;
    #endif
  }
#endif

#if (RBFS_uCFamily == RBFS_uCFamily_STMStellar)
uint32 TRBSYS_Os_StartCoreGate_cnt = 0;
void Os_StartCoreGate(void)
{
  TRBSYS_Os_StartCoreGate_cnt++;
}
#endif

boolean TRBSYS_TaskChainingEnabled = TRUE;
boolean TRBSYS_TaskActivationDoneOnce = FALSE;
boolean TRBSYS_isTaskChainingEnabled(void)
{
  if(!TRBSYS_TaskChainingEnabled && !TRBSYS_TaskActivationDoneOnce)
  {
    TRBSYS_TaskActivationDoneOnce = TRUE;
    return TRUE;
  }
  return TRBSYS_TaskChainingEnabled;
}