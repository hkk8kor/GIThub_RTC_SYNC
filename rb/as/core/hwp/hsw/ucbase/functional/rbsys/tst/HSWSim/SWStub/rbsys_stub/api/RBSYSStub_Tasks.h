#ifndef RBSYSSTUB_TASKS_H__
#define RBSYSSTUB_TASKS_H__

#include "RBSYS_Config.h"
#include "SWStub_Config.h"

/* typedef for processes: Void-Void function call */
typedef void (*PRC_PTR)(void);

/// LEGACY: Process-Lists DO NOT USE AS TaskType identifiers
extern const PRC_PTR c_PreReprogCheck[];
extern const PRC_PTR c_PrePlantCheck[];
extern const PRC_PTR c_TaskInit[];
extern const PRC_PTR c_TaskIdle[];
#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
  extern const PRC_PTR c_Task0p5ms[];
#endif
extern const PRC_PTR c_Task1ms[];
extern const PRC_PTR c_Taskx1h[];
extern const PRC_PTR c_Taskx1l[];
extern const PRC_PTR c_Taskx2[];
extern const PRC_PTR c_Taskx4[];
extern const PRC_PTR c_Taskx8[];
extern const PRC_PTR c_Taskx24[];
extern const PRC_PTR c_FlexrayTask[];

extern const PRC_PTR c_TaskInitBaseOS[];
#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
  extern const PRC_PTR c_Task0p5msBaseOS[];
#endif
extern const PRC_PTR c_Task1msBaseOS[];
extern const PRC_PTR c_Taskx1hBaseOS[];
extern const PRC_PTR c_Taskx1lBaseOS[];
extern const PRC_PTR c_Taskx2BaseOS[];
extern const PRC_PTR c_Taskx4BaseOS[];
extern const PRC_PTR c_Taskx8BaseOS[];
extern const PRC_PTR c_Taskx24BaseOS[];

#if (RBFS_MCORE == RBFS_MCORE_ON)
  extern const PRC_PTR c_Taskx2p[];
  extern const PRC_PTR c_Taskx2pBaseOS[];
#endif

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  /* VMPS specific tasks */
  extern const PRC_PTR c_Taskx4pl[];
  extern const PRC_PTR c_Taskx200bg[];
  extern const PRC_PTR c_TaskEventExtPrio1[];
  extern const PRC_PTR c_TaskEventExtPrio2[];

  extern const PRC_PTR c_Taskx4plBaseOS[];
  extern const PRC_PTR c_Taskx200bgBaseOS[];
  extern const PRC_PTR c_TaskEventExtPrio1BaseOS[];
  extern const PRC_PTR c_TaskEventExtPrio2BaseOS[];
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  extern const PRC_PTR c_Taskx1Guest[];
  extern const PRC_PTR c_Taskx2Guest[];
  extern const PRC_PTR c_Taskx4Guest[];
  extern const PRC_PTR c_Taskx10Guest[];
  extern const PRC_PTR c_Taskx20Guest[];

  extern const PRC_PTR c_Taskx1GuestBaseOS[];
  extern const PRC_PTR c_Taskx2GuestBaseOS[];
  extern const PRC_PTR c_Taskx4GuestBaseOS[];
  extern const PRC_PTR c_Taskx10GuestBaseOS[];
  extern const PRC_PTR c_Taskx20GuestBaseOS[];
#endif

#endif
