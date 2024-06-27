/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Dynamic framework (i.e. task and interrupt frames)
 *
 * This module provides and controls the complete dynamic framework of the system on task, process and interrupt granularity.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "Os.h"
#include "RBSYS_TaskInfo.h"
#include "RBSYS_CpuInfo.h"
#include "RBSYS_Idle.h"
#include "Statistics/RBSYS_TaskStats.h"
#include "Statistics/RBSYS_RuntimeMeasure.h"
#include "Statistics/RBSYS_StartupTimingIntern.h" //For InitTask timestamps
#include "Monitorings/RBSYS_ErrorHooks.h"
#include "RBSYS_TimerOsConfig.h"
#include "RBSYS_SystemTimer.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_LocksImpl.h"  // first include LocksImpl then ImplIntern!
#include "RBSYS_LocksImplIntern.h"
#include "RBSYS_MultiCoreSyncIntern.h"
#include "RBSYS_PlantStartupCtrl.h"
#include "RBSYS_EnableIRQs.h"
#include "RBSYS_uCRegisters.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_TestInjection.h"
#include "SystemMemoryProtection/RBSYS_GuardConfigCommon.h"
#include "../rtaos/src/RBSYS_OsConfig.h"
#include "RBSYS_Subsystem.h" //< todo: check if this is necessary (call)
#include "RB_IntParts.h"
#include "RBSYS_ExceptionHandler.h"

/******************************************************************************/
/* default header includes for appl. processes via merge proc                 */
/******************************************************************************/
/*ROOT_SECTION: HeaderIncludes_Root |#include "|" */
/*PROC_EP: HeaderIncludes */
/*ROOT_SECTION_END: */



/* realized interfaces */
#include "RBSYS_OsServices.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysDebugUnbalancedLock,
                          RBFS_SysDebugUnbalancedLock_OFF,
                          RBFS_SysDebugUnbalancedLock_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysDebugProcRuntime,
                          RBFS_SysDebugProcRuntime_OFF,
                          RBFS_SysDebugProcRuntime_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTask0p5ms,
                          RBFS_SysTask0p5ms_OFF,
                          RBFS_SysTask0p5ms_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysFlxrTask,
                          RBFS_SysFlxrTask_OFF,
                          RBFS_SysFlxrTask_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWCapsule,
                          RBFS_TPSWCapsule_OFF,
                          RBFS_TPSWCapsule_SC3,
                          RBFS_TPSWCapsule_SC4);
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSchemeExtension,
                          RBFS_TaskSchemeExtension_None,
                          RBFS_TaskSchemeExtension_VMPS,
                          RBFS_TaskSchemeExtension_HostCore0GuestCore1,
                          RBFS_TaskSchemeExtension_AB15);
RB_ASSERT_SWITCH_SETTINGS(RBFS_LockTimeMonitoring,
                          RBFS_LockTimeMonitoring_Enabled,
                          RBFS_LockTimeMonitoring_Disabled);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTPSWSupport,
                          RBFS_SysTPSWSupport_YES,
                          RBFS_SysTPSWSupport_NO);


static void taskbody_prc_calls(const PRC_PTR proc_table[]);


#if (RBFS_SysDebugProcRuntime == RBFS_SysDebugProcRuntime_ON)
  /* in case of enabled debug support store for each task the longest running process and prepare content for MM6 */
  typedef struct            /*TOOL_SCAN*/
  {
    uint32 address;         /*COMMENT=address of process with maximum runtime per task*/
    uint32 runtime;         /*COMMENT=maximum runtime of corresponding process[ticks]*/

  } RBSYS_ProcRuntime_t;


  RBSYS_ProcRuntime_t RBSYS_DebugInfo_MaxProcPerTask[OS_NUM_TASKS];
  /*[[MEASUREMENT_TYPEDEF*/
  /*TYPE=RBSYS_ProcRuntime_t*/
  /*NAME=RBSYS_DebugInfo_MaxProcPerTask[RBSYS_TASK_SIZE_4_GENPRODB]*/
  /*MTEVENT=c_MT_Default_Task_x1*/
  /*]]MEASUREMENT_TYPEDEF*/

#endif


/***********************************************************************************/
/* Hint: Process tables are scanned by external StackCalculator tool!              */
/*       Therefore the keywords "static const PRC_PTR" and "NULL" as end marker of */
/*       the process list are not allowed to be changed without a tool adaptation  */
/***********************************************************************************/
static const PRC_PTR c_TaskIdle[] =
{
  /*ROOT_SECTION: SPG_TaskIdle_Root | &|, */
  /*PROC_EP: SPG_TaskIdle */
  /*ROOT_SECTION_END: */
  NULL
};

#if (RBFS_MCORE == RBFS_MCORE_ON)
  static const PRC_PTR c_TaskIdleP[] =
  {
    /*ROOT_SECTION: SPG_TaskIdleP_Root | &|, */
    /*PROC_EP: SPG_TaskIdleP */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

static const PRC_PTR c_TaskInit[] =
{
  /*ROOT_SECTION: SPG_TaskInit_Root | &|, */
  /*PROC_EP: SPG_TaskInit */
  /*ROOT_SECTION_END: */
  NULL
};

#if (RBFS_MCORE == RBFS_MCORE_ON)
  static const PRC_PTR c_TaskInitP[] =
  {
    /*ROOT_SECTION: SPG_TaskInitP_Root | &|, */
    /*PROC_EP: SPG_TaskInitP */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  static const PRC_PTR c_Task0p5ms[] =
  {
    /*ROOT_SECTION: SPG_Task0p5ms_Root | &|, */
    /*PROC_EP: SPG_Task0p5ms */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

static const PRC_PTR c_Task1ms[] =
{
  /*ROOT_SECTION: SPG_Task1ms_Root | &|, */
  /*PROC_EP: SPG_Task1ms */
  /*ROOT_SECTION_END: */
  NULL
};

static const PRC_PTR c_Taskx1h[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx1High_Root | &|, */
  /*PROC_EP: SPG_TaskBaseCtrlCycx1High */
  /*ROOT_SECTION_END: */
  NULL
};

#if (RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON)
  static const PRC_PTR c_FlexrayTask[] =
  {
    /*ROOT_SECTION: SPG_TaskFlexray_Root | &|, */
    /*PROC_EP: SPG_TaskFlexray */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

static const PRC_PTR c_Taskx1l[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx1Low_Root | &|, */
  /*PROC_EP: SPG_TaskBaseCtrlCycx1Low */
  /*ROOT_SECTION_END: */
  NULL
};

static const PRC_PTR c_Taskx2[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx2_Root | &|, */
  /*PROC_EP: SPG_TaskBaseCtrlCycx2 */
  /*ROOT_SECTION_END: */
  NULL
};

#if (RBFS_MCORE == RBFS_MCORE_ON)
  static const PRC_PTR c_Taskx2p[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx2p_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx2p */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

static const PRC_PTR c_Taskx4[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx4_Root | &|, */
  /*PROC_EP: SPG_TaskBaseCtrlCycx4 */
  /*ROOT_SECTION_END: */
  NULL
};

static const PRC_PTR c_Taskx8[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx8_Root | &|, */
  /*PROC_EP: SPG_TaskBaseCtrlCycx8 */
  /*ROOT_SECTION_END: */
  NULL
};

static const PRC_PTR c_Taskx24[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx24_Root | &|, */
  /*PROC_EP: SPG_TaskBaseCtrlCycx24 */
  /*ROOT_SECTION_END: */
  NULL
};

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  static const PRC_PTR c_Taskx4pl[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx4pLow_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx4pLow */
    /*ROOT_SECTION_END: */
    NULL
  };

  static const PRC_PTR c_Taskx200bg[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx200bg_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx200bg */
    /*ROOT_SECTION_END: */
    NULL
  };

  static const PRC_PTR c_TaskEventExtPrio1[] =
  {
    /*ROOT_SECTION: SPG_TaskEventExtPrio1_Root | &|, */
    /*PROC_EP: SPG_TaskEventExtPrio1 */
    /*ROOT_SECTION_END: */
    NULL
  };

  static const PRC_PTR c_TaskEventExtPrio2[] =
  {
    /*ROOT_SECTION: SPG_TaskEventExtPrio2_Root | &|, */
    /*PROC_EP: SPG_TaskEventExtPrio2 */
    /*ROOT_SECTION_END: */
    NULL
  };
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  static const PRC_PTR c_Taskx1Guest[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx1Guest_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx1Guest */
    /*ROOT_SECTION_END: */
    NULL
  };
  static const PRC_PTR c_Taskx2Guest[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx2Guest_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx2Guest */
    /*ROOT_SECTION_END: */
    NULL
  };
  static const PRC_PTR c_Taskx4Guest[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx4Guest_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx4Guest */
    /*ROOT_SECTION_END: */
    NULL
  };
  static const PRC_PTR c_Taskx10Guest[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx10Guest_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx10Guest */
    /*ROOT_SECTION_END: */
    NULL
  };
  static const PRC_PTR c_Taskx20Guest[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx20Guest_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx20Guest */
    /*ROOT_SECTION_END: */
    NULL
  };
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  static const PRC_PTR c_Taskx10[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx10_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx10 */
    /*ROOT_SECTION_END: */
    NULL
  };
  static const PRC_PTR c_Taskx20[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx20_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx20 */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

static const PRC_PTR c_TaskInitBaseOS[] =
{
  /*ROOT_SECTION: SPG_TaskInitBaseOS_Root | &|, */
  /*PROC_EP: SPG_TaskInitBaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

#if (RBFS_MCORE == RBFS_MCORE_ON)
  static const PRC_PTR c_TaskInitPBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskInitPBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskInitPBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  static const PRC_PTR c_Task0p5msBaseOS[] =
  {
    /*ROOT_SECTION: SPG_Task0p5msBaseOS_Root | &|, */
    /*PROC_EP: SPG_Task0p5msBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

static const PRC_PTR c_Task1msBaseOS[] =
{
  /*ROOT_SECTION: SPG_Task1msBaseOS_Root | &|, */
  /*PROC_EP: SPG_Task1msBaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

static const PRC_PTR c_Taskx1hBaseOS[] =
{
  /*ROOT_SECTION: SPG_Taskx1hBaseOS_Root | &|, */
  /*PROC_EP: SPG_Taskx1hBaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

static const PRC_PTR c_Taskx1lBaseOS[] =
{
  /*ROOT_SECTION: SPG_Taskx1lBaseOS_Root | &|, */
  /*PROC_EP: SPG_Taskx1lBaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

static const PRC_PTR c_Taskx2BaseOS[] =
{
  /*ROOT_SECTION: SPG_Taskx2BaseOS_Root | &|, */
  /*PROC_EP: SPG_Taskx2BaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

#if (RBFS_MCORE == RBFS_MCORE_ON)
  static const PRC_PTR c_Taskx2pBaseOS[] =
  {
    /*ROOT_SECTION: SPG_Taskx2pBaseOS_Root | &|, */
    /*PROC_EP: SPG_Taskx2pBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

static const PRC_PTR c_Taskx4BaseOS[] =
{
  /*ROOT_SECTION: SPG_Taskx4BaseOS_Root | &|, */
  /*PROC_EP: SPG_Taskx4BaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

static const PRC_PTR c_Taskx8BaseOS[] =
{
  /*ROOT_SECTION: SPG_Taskx8BaseOS_Root | &|, */
  /*PROC_EP: SPG_Taskx8BaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

static const PRC_PTR c_Taskx24BaseOS[] =
{
  /*ROOT_SECTION: SPG_Taskx24BaseOS_Root | &|, */
  /*PROC_EP: SPG_Taskx24BaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  static const PRC_PTR c_Taskx4plBaseOS[] =
  {
    /*ROOT_SECTION: SPG_Taskx4plBaseOS_Root | &|, */
    /*PROC_EP: SPG_Taskx4plBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };

  static const PRC_PTR c_Taskx200bgBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx200bgBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx200bgBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };

  static const PRC_PTR c_TaskEventExtPrio1BaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskEventExtPrio1BaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskEventExtPrio1BaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };

  static const PRC_PTR c_TaskEventExtPrio2BaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskEventExtPrio2BaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskEventExtPrio2BaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  static const PRC_PTR c_Taskx1GuestBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx1GuestBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx1GuestBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
  static const PRC_PTR c_Taskx2GuestBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx2GuestBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx2GuestBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
  static const PRC_PTR c_Taskx4GuestBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx4GuestBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx4GuestBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
  static const PRC_PTR c_Taskx10GuestBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx10GuestBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx10GuestBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
  static const PRC_PTR c_Taskx20GuestBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx20GuestBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx20GuestBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  static const PRC_PTR c_Taskx10BaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx10BaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx10BaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
  static const PRC_PTR c_Taskx20BaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx20BaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx20BaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  RBMESG_DefineMESG(RBMESG_Task0p5msCnt_u32);
  RBMESG_DefineMESG(RBMESG_Task0p5msCompletedCnt_u32);
#endif
RBMESG_DefineMESG(RBMESG_Task1msCnt_u32);
RBMESG_DefineMESG(RBMESG_Task1msCompletedCnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx1Cnt_u32);
#if (RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON)
  RBMESG_DefineMESG(RBMESG_TaskFlexrayCnt_u32);
#endif
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx1CompletedCnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx1LowCnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx1LowCompletedCnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx2Cnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx2CompletedCnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx4Cnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx4CompletedCnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx8Cnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx8CompletedCnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx24Cnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx24CompletedCnt_u32);

#if (RBFS_MCORE == RBFS_MCORE_ON)
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx2pCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx2pCompletedCnt_u32);
#endif

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx4pLowCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx4pLowCompletedCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx200BackgroundCompletedCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskEventCtrlExtPrio1Cnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskEventCtrlExtPrio1CompletedCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskEventCtrlExtPrio2Cnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskEventCtrlExtPrio2CompletedCnt_u32);
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx1GuestCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx1GuestCompletedCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx2GuestCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx2GuestCompletedCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx4GuestCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx4GuestCompletedCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx10GuestCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx10GuestCompletedCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx20GuestCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx20GuestCompletedCnt_u32);
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx10Cnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx10CompletedCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx20Cnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx20CompletedCnt_u32);
#endif

#if( RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON )
  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_Task0p5msCnt_u32*/
  /*COMMENT=Task0p5msCnt*/
  /*MTEVENT=c_MT_Default_Task_500us*/
  /*]]MEASUREMENT*/
#endif

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_Task1msCnt_u32*/
/*COMMENT=Task1msCnt*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskBaseCtrlx1Cnt_u32*/
/*COMMENT=TaskBaseCtrlx1Cnt*/
/*MTEVENT=c_MT_Default_Task_x1*/
/*]]MEASUREMENT*/


#if (RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON)
/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskFlexrayCnt_u32*/
/*COMMENT=TaskFlexrayCnt*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskBaseCtrlx1LowCnt_u32*/
/*COMMENT=TaskBaseCtrlx1LowCnt*/
/*MTEVENT=c_MT_Default_Task_x1*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskBaseCtrlx2Cnt_u32*/
/*COMMENT=TaskBaseCtrlx2Cnt*/
/*MTEVENT=c_MT_Default_Task_x2*/
/*]]MEASUREMENT*/

#if( RBFS_MCORE == RBFS_MCORE_ON )
  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_TaskBaseCtrlx2pCnt_u32*/
  /*COMMENT=TaskBaseCtrlx2pCnt*/
  /*MTEVENT=c_MT_Default_Task_x2*/
  /*]]MEASUREMENT*/
#endif

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskBaseCtrlx4Cnt_u32*/
/*COMMENT=TaskBaseCtrlx4Cnt*/
/*MTEVENT=c_MT_Default_Task_x4*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskBaseCtrlx8Cnt_u32*/
/*COMMENT=TaskBaseCtrlx8Cnt*/
/*MTEVENT=c_MT_Default_Task_x8*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskBaseCtrlx24Cnt_u32*/
/*COMMENT=TaskBaseCtrlx24Cnt*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_TaskBaseCtrlx4pLowCnt_u32*/
  /*COMMENT=TaskBaseCtrlx4pLowCnt*/
  /*MTEVENT=c_MT_Default_Task_x4pLow*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_TaskBaseCtrlx200BackgroundCnt_u32*/
  /*COMMENT=TaskBaseCtrlx200BackgroundCnt*/
  /*MTEVENT=c_MT_Default_Task_x200bg*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_TaskEventCtrlExtPrio1Cnt_u32*/
  /*COMMENT=TaskEventCtrlExtPrio1Cnt*/
  /*MTEVENT=c_MT_Default_Task_EventExtPrio1*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_TaskEventCtrlExtPrio2Cnt_u32*/
  /*COMMENT=TaskEventCtrlExtPrio2Cnt*/
  /*MTEVENT=c_MT_Default_Task_EventExtPrio2*/
  /*]]MEASUREMENT*/
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_TaskBaseCtrlx1GuestCnt_u32*/
  /*COMMENT=TaskBaseCtrlx1GuestCnt*/
  /*MTEVENT=c_MT_Default_Task_x1Guest*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_TaskBaseCtrlx2GuestCnt_u32*/
  /*COMMENT=TaskBaseCtrlx2GuestCnt*/
  /*MTEVENT=c_MT_Default_Task_x2Guest*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_TaskBaseCtrlx4GuestCnt_u32*/
  /*COMMENT=TaskBaseCtrlx4GuestCnt*/
  /*MTEVENT=c_MT_Default_Task_x4Guest*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_TaskBaseCtrlx10GuestCnt_u32*/
  /*COMMENT=TaskBaseCtrlx10GuestCnt*/
  /*MTEVENT=c_MT_Default_Task_x10Guest*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_TaskBaseCtrlx20GuestCnt_u32*/
  /*COMMENT=TaskBaseCtrlx20GuestCnt*/
  /*MTEVENT=c_MT_Default_Task_x20Guest*/
  /*]]MEASUREMENT*/
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  #warning ("add measurement variables when events are available")
  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_TaskBaseCtrlx10Cnt_u32*/
  /*COMMENT=TaskBaseCtrlx10Cnt*/
  /*MTEVENT=c_MT_Default_Task_x10*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=RBMESG_RBMESG_TaskBaseCtrlx20Cnt_u32*/
  /*COMMENT=TaskBaseCtrlx20Cnt*/
  /*MTEVENT=c_MT_Default_Task_x20*/
  /*]]MEASUREMENT*/
#endif



/* following measurement variables/comments are required for Open Loop Offline Simulation (OOL)
 *  - OOL requires measurable counters for each ASW task: needed for synchronization purposes
 *  - counters must be incremented at beginning of task
 *  - existing task counters are used but provided with separate name so that the OOL functionality
 *    is independent of normal task counter/measurement names (see also Gen9 CSCRM00332552)
 */

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskBaseCtrlx1LowCnt_u32*/
/*MODEL_NAME=OOLTaskBaseCtrlx1Cnt_UL*/
/*COMMENT=OOLTaskBaseCtrlx1Cnt_UL*/
/*MTEVENT=c_MT_Default_Task_x1*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskBaseCtrlx2Cnt_u32*/
/*MODEL_NAME=OOLTaskBaseCtrlx2Cnt_UL*/
/*COMMENT=OOLTaskBaseCtrlx2Cnt_UL*/
/*MTEVENT=c_MT_Default_Task_x2*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskBaseCtrlx4Cnt_u32*/
/*MODEL_NAME=OOLTaskBaseCtrlx4Cnt_UL*/
/*COMMENT=OOLTaskBaseCtrlx4Cnt_UL*/
/*MTEVENT=c_MT_Default_Task_x4*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskBaseCtrlx8Cnt_u32*/
/*MODEL_NAME=OOLTaskBaseCtrlx8Cnt_UL*/
/*COMMENT=OOLTaskBaseCtrlx8Cnt_UL*/
/*MTEVENT=c_MT_Default_Task_x8*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskBaseCtrlx24Cnt_u32*/
/*MODEL_NAME=OOLTaskBaseCtrlx24Cnt_UL*/
/*COMMENT=OOLTaskBaseCtrlx24Cnt_UL*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/





/* pointers to process lists to be set in InitTask to distinguish Normal and BaseOS */
static const PRC_PTR *prclist_taskinit;
#if (RBFS_MCORE == RBFS_MCORE_ON)
  static const PRC_PTR *prclist_taskinitp;
#endif
#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  static const PRC_PTR *prclist_task0p5ms;
#endif
static const PRC_PTR *prclist_task1ms;
static const PRC_PTR *prclist_taskx1h;
static const PRC_PTR *prclist_taskx1l;
static const PRC_PTR *prclist_taskx2;
#if (RBFS_MCORE == RBFS_MCORE_ON)
  static const PRC_PTR *prclist_taskx2p;
#endif
static const PRC_PTR *prclist_taskx4;
static const PRC_PTR *prclist_taskx8;
static const PRC_PTR *prclist_taskx24;


#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  static const PRC_PTR *prclist_taskx4pl;
  static const PRC_PTR *prclist_taskx200bg;
  static const PRC_PTR *prclist_taskeventprio1;
  static const PRC_PTR *prclist_taskeventprio2;
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  static const PRC_PTR *prclist_taskx1guest;
  static const PRC_PTR *prclist_taskx2guest;
  static const PRC_PTR *prclist_taskx4guest;
  static const PRC_PTR *prclist_taskx10guest;
  static const PRC_PTR *prclist_taskx20guest;
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  static const PRC_PTR *prclist_taskx10;
  static const PRC_PTR *prclist_taskx20;
#endif

static inline void set_prclist_default(void)
{
  prclist_taskinit       = c_TaskInit;
#if (RBFS_MCORE == RBFS_MCORE_ON)
  prclist_taskinitp      = c_TaskInitP;
#endif
#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  prclist_task0p5ms      = c_Task0p5ms;
#endif
  prclist_task1ms        = c_Task1ms;
  prclist_taskx1h        = c_Taskx1h;
  prclist_taskx1l        = c_Taskx1l;
  prclist_taskx2         = c_Taskx2;
#if (RBFS_MCORE == RBFS_MCORE_ON)
  prclist_taskx2p        = c_Taskx2p;
#endif
  prclist_taskx4         = c_Taskx4;
  prclist_taskx8         = c_Taskx8;
  prclist_taskx24        = c_Taskx24;

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  prclist_taskx4pl       = c_Taskx4pl;
  prclist_taskx200bg     = c_Taskx200bg;
  prclist_taskeventprio1 = c_TaskEventExtPrio1;
  prclist_taskeventprio2 = c_TaskEventExtPrio2;
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  prclist_taskx1guest    = c_Taskx1Guest;
  prclist_taskx2guest    = c_Taskx2Guest;
  prclist_taskx4guest    = c_Taskx4Guest;
  prclist_taskx10guest   = c_Taskx10Guest;
  prclist_taskx20guest   = c_Taskx20Guest;
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  prclist_taskx10   = c_Taskx10;
  prclist_taskx20   = c_Taskx20;
#endif
}

static inline void set_prclist_baseos(void)
{
  prclist_taskinit       = c_TaskInitBaseOS;
#if (RBFS_MCORE == RBFS_MCORE_ON)
  prclist_taskinitp      = c_TaskInitPBaseOS;
#endif
#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  prclist_task0p5ms      = c_Task0p5msBaseOS;
#endif
  prclist_task1ms        = c_Task1msBaseOS;
  prclist_taskx1h        = c_Taskx1hBaseOS;
  prclist_taskx1l        = c_Taskx1lBaseOS;
  prclist_taskx2         = c_Taskx2BaseOS;
#if (RBFS_MCORE == RBFS_MCORE_ON)
  prclist_taskx2p        = c_Taskx2pBaseOS;
#endif
  prclist_taskx4         = c_Taskx4BaseOS;
  prclist_taskx8         = c_Taskx8BaseOS;
  prclist_taskx24        = c_Taskx24BaseOS;

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  prclist_taskx4pl       = c_Taskx4plBaseOS;
  prclist_taskx200bg     = c_Taskx200bgBaseOS;
  prclist_taskeventprio1 = c_TaskEventExtPrio1BaseOS;
  prclist_taskeventprio2 = c_TaskEventExtPrio2BaseOS;
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  prclist_taskx1guest    = c_Taskx1GuestBaseOS;
  prclist_taskx2guest    = c_Taskx2GuestBaseOS;
  prclist_taskx4guest    = c_Taskx4GuestBaseOS;
  prclist_taskx10guest   = c_Taskx10GuestBaseOS;
  prclist_taskx20guest   = c_Taskx20GuestBaseOS;
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  prclist_taskx10   = c_Taskx10BaseOS;
  prclist_taskx20   = c_Taskx20BaseOS;
#endif
}


static void taskbody_prc_calls(const PRC_PTR proc_table[])
{
  unsigned int proc_id = 0;

   /* Loop through Processes */
  while (proc_table[proc_id] != NULL)
  {

    #if (RBFS_SysDebugProcRuntime == RBFS_SysDebugProcRuntime_ON)
      /* measure process runtime to get longest running process per task */
      rba_Runtime_MTValues_t proc_runtime;
      rba_Runtime_MTStartMeasure(&proc_runtime);
    #endif

    /* if controlled runtime is enabled (i.e. via WinRTM), check if process has to be measured */
    RBA_RUNTIME_MSR_PROC(proc_table[proc_id]);

    #if (RBFS_SysDebugProcRuntime == RBFS_SysDebugProcRuntime_ON)
      rba_Runtime_MTEndMeasure(&proc_runtime);

      {
        uint32 task_id = RBSYS_GetTaskIndex(RBSYS_GetCurrentTask());

        /* store longest running process per task*/
        if (proc_runtime.tiActRT_u32 > RBSYS_DebugInfo_MaxProcPerTask[task_id].runtime)
        {
          RBSYS_DebugInfo_MaxProcPerTask[task_id].address = (uint32)proc_table[proc_id];
          RBSYS_DebugInfo_MaxProcPerTask[task_id].runtime = proc_runtime.tiActRT_u32;
        }
      }
    #endif

    #if (RBFS_SysDebugUnbalancedLock == RBFS_SysDebugUnbalancedLock_ON)
      /* check for unbalanced locks after each process */
      RBSYS_checkUnbalancedLock((uint32)proc_table[proc_id]);
    #endif

    proc_id++;
  }
}

static inline void check_and_activate_next_task(uint32 taskcnt, TaskType task)
{
  if ((taskcnt & 0x00000001u) == 0x00000001u) {
    (void)ActivateTask(task);
    #if (RBFS_MCORE == RBFS_MCORE_ON)   // task activation can also be done as first instruction in x2 task, so avoiding this logic here
    if (task == TaskBaseCtrlCycx2)
    {
      (void)ActivateTask(TaskBaseCtrlCycx2p);
    }
    #endif
  }
}

static void check_and_activate_x24(void)
{
  static uint8 cnt=3; // use own counter to avoid %3

  if (cnt >= 3) {
    (void)ActivateTask(TaskBaseCtrlCycx24);
    cnt=0;
  }
  cnt++;
}

static void RBSYS_TerminateTask(void)
{
  /* Extract from RTA-OS Reference Guide:
   * If the "Fast Terminate" is enabled in optimizations for RTA-OS then TerminateTask() must only
   * be called from the task entry function and the return status should not be checked (ErrorHook,
   * when configured, will be called if there is an error). This optimization saves memory and
   * execution time. For further savings, you can actually omit the call to TerminateTask() in SC1 and SC2.
   */
  #if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)
    (void)TerminateTask();
  #endif
}


TASK(TaskInit)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSActive);
  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSActive);

  if (l_RBMESG_RBSYSBaseOSActive)
  {
    set_prclist_baseos();
  }
  else
  {
    set_prclist_default();
  }

  RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_Init);
  RBSYS_StartupSyncBarrier(RBSYS_BeforeInitTaskProcs);   // sync after process list is initialized

  taskbody_prc_calls(prclist_taskinit);

  RBSYS_StartupSyncBarrier(RBSYS_AfterInitTaskProcs);   // sync after processes are executed before max.lock could be cleared

  /* after finishing all processes in init task, maximum lock count must be cleared before cyclic task execution */
  /* this additional call is to zero the locks from the measurement event in the Init */
  #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
    RBSYS_PRC_ResetMaxLockTime_Init();
  #endif

  #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      // enable software interrupt 0 used for BERT only
      RBSYS_EnableIRQ_SWINT0();
    #endif
  #else
    #warning("ToDo: RBSYS Stellar support")
  #endif

  /* due to required sync barrier (between timer configuration and enabling timer IRQs) below functions could
   * not be handled via mergeproc */
  RBSYS_SetupOsTimer();
  RBSYS_StartupSyncBarrier(RBSYS_OsTimerSetupFinished);
  RBSYS_EnableOsTimerIRQs();


  /* handle below Taskmon initialization explicitly here and not via mainproc list due to required sync barrier
   * above between timer configuration and enabling timer IRQs */

  /*ROOT_SECTION: SPG_RBTaskMon_Init_Root | |(); */
  /*PROC_EP: SPG_RBTaskMon_Init */
  /*ROOT_SECTION_END: */


  RBSYS_StartupSyncBarrier(RBSYS_TaskInitEnd);
  RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_Cyclic);

  RBSYS_SetInitTaskTimestamp(RBSYS_TimestampInitTask);
  RBSYS_TerminateTask();
}

/* TaskInitP is autostarted by OS for multi-core systems; no autostart for single core
 *
 * TaskInitP is needed to start Idle processing after normal InitTask is finished; we have selected this
 * solution to avoid an "if" in the idle-loop; therefore the synchronization is done in InitTask/P
 *
 * In general it's not planned to run processes in TaskInitP - therefore no MergeProc entry is available!
 */
TASK(TaskInitP)
{
  #if (RBFS_MCORE == RBFS_MCORE_ON)

    RBSYS_StartupSyncBarrier(RBSYS_BeforeInitTaskProcs);   // sync after process list is initialized

    taskbody_prc_calls(prclist_taskinitp);

    RBSYS_StartupSyncBarrier(RBSYS_AfterInitTaskProcs);   // sync after processes are executed before max.lock could be cleared

    #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
      // enable software interrupt 0 used for BERT only
      RBSYS_EnableIRQ_SWINT0();
    #else
      #warning("ToDo: RBSYS Stellar support")
    #endif

    RBSYS_StartupSyncBarrier(RBSYS_OsTimerSetupFinished);

    RBSYS_EnableOsTimerIRQs();

    RBSYS_StartupSyncBarrier(RBSYS_TaskInitEnd);
  #endif

  RBSYS_SetInitTaskTimestamp(RBSYS_TimestampInitTaskP);
  RBSYS_TerminateTask();
}

TASK(Task0p5ms)
{
  #if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
    RBMESG_DefineMESGDef(RBMESG_Task0p5msCnt_u32);
    RBMESG_IncrementMESG(RBMESG_Task0p5msCnt_u32);
    RBMESG_RcvMESGDef(RBMESG_Task0p5msCnt_u32);

    set_current_task_cnt(Task0p5ms, l_RBMESG_Task0p5msCnt_u32);   //store task counter for task statistics
    taskbody_prc_calls(prclist_task0p5ms);

    check_and_activate_next_task(l_RBMESG_Task0p5msCnt_u32, Task1ms);

    RBMESG_IncrementMESG(RBMESG_Task0p5msCompletedCnt_u32);
  #endif

  RBSYS_TerminateTask();
}

TASK(Task1ms)
{
  RBMESG_DefineMESGDef(RBMESG_Task1msCnt_u32);
  RBMESG_IncrementMESG(RBMESG_Task1msCnt_u32);
  RBMESG_RcvMESGDef(RBMESG_Task1msCnt_u32);

  set_current_task_cnt(Task1ms, l_RBMESG_Task1msCnt_u32);
  taskbody_prc_calls(prclist_task1ms);

  RBMESG_IncrementMESG(RBMESG_Task1msCompletedCnt_u32);

  RBSYS_TerminateTask();
}

static boolean is_task_still_active(TaskType task)
{
  TaskStateType tsk_state;
  (void)GetTaskState(task, &tsk_state);
  return ((tsk_state == READY)||(tsk_state == RUNNING));
}

TASK(TaskBaseCtrlCycx1High)
{
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx1Cnt_u32);
  RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx1Cnt_u32);
  RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx1Cnt_u32);

  set_current_task_cnt(TaskBaseCtrlCycx1High, l_RBMESG_TaskBaseCtrlx1Cnt_u32);
  taskbody_prc_calls(prclist_taskx1h);

  check_and_activate_next_task(1, TaskBaseCtrlCycx1Low);

  RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx1CompletedCnt_u32);

  RBSYS_TerminateTask();
}


#if( RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON )
  void RBSYS_ActivateFlexrayTask(void)
  {
    (void)ActivateTask(TaskFlexray);
    set_task_activation_ts(TaskFlexray, RBSYS_getRealtimeTickCtr());
  }
#endif

TASK(TaskFlexray)
{
  #if (RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON)
    RBMESG_IncrementMESG(RBMESG_TaskFlexrayCnt_u32);

    taskbody_prc_calls(c_FlexrayTask);
  #endif

  RBSYS_TerminateTask();
}

TASK(TaskBaseCtrlCycx1Low)
{
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx1LowCnt_u32);
  RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx1LowCnt_u32);
  RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx1LowCnt_u32);

  set_current_task_cnt(TaskBaseCtrlCycx1Low,l_RBMESG_TaskBaseCtrlx1LowCnt_u32);
  taskbody_prc_calls(prclist_taskx1l);

  check_and_activate_next_task(l_RBMESG_TaskBaseCtrlx1LowCnt_u32, TaskBaseCtrlCycx2);

  RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx1LowCompletedCnt_u32);

  RBSYS_TerminateTask();
}


TASK(TaskBaseCtrlCycx2)
{
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx2Cnt_u32);
  RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx2Cnt_u32);
  RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx2Cnt_u32);

  set_current_task_cnt(TaskBaseCtrlCycx2,l_RBMESG_TaskBaseCtrlx2Cnt_u32);
  taskbody_prc_calls(prclist_taskx2);

  check_and_activate_next_task(l_RBMESG_TaskBaseCtrlx2Cnt_u32, TaskBaseCtrlCycx4);

  RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx2CompletedCnt_u32);

  RBSYS_TerminateTask();
}


// - only for multi-core systems scheduled: runs on other core than TaskBaseCtrlCycx2
// - activated in parallel to TaskBaseCtrlCycx2 (i.e. also same deadline)
// - no further consistency mechanisms implemented
// => only allowed to be used by specific agreed use cases
TASK(TaskBaseCtrlCycx2p)
{
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx2pCnt_u32);
    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx2pCnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx2pCnt_u32);

    set_current_task_cnt(TaskBaseCtrlCycx2p,l_RBMESG_TaskBaseCtrlx2pCnt_u32);
    taskbody_prc_calls(prclist_taskx2p);

    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx2pCompletedCnt_u32);
  #endif

  RBSYS_TerminateTask();
}

TASK(TaskBaseCtrlCycx4)
{
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx4Cnt_u32);
  RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx4Cnt_u32);
  RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx4Cnt_u32);

  set_current_task_cnt(TaskBaseCtrlCycx4,l_RBMESG_TaskBaseCtrlx4Cnt_u32);
  taskbody_prc_calls(prclist_taskx4);

  check_and_activate_next_task(l_RBMESG_TaskBaseCtrlx4Cnt_u32, TaskBaseCtrlCycx8);

  RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx4CompletedCnt_u32);

  RBSYS_TerminateTask();
}

TASK(TaskBaseCtrlCycx8)
{
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx8Cnt_u32);
  RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx8Cnt_u32);
  RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx8Cnt_u32);

  set_current_task_cnt(TaskBaseCtrlCycx8,l_RBMESG_TaskBaseCtrlx8Cnt_u32);
  taskbody_prc_calls(prclist_taskx8);

  check_and_activate_x24();

  RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx8CompletedCnt_u32);

  RBSYS_TerminateTask();
}

TASK(TaskBaseCtrlCycx24)
{
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx24Cnt_u32);
  RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx24Cnt_u32);
  RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx24Cnt_u32);

  set_current_task_cnt(TaskBaseCtrlCycx24,l_RBMESG_TaskBaseCtrlx24Cnt_u32);
  taskbody_prc_calls(prclist_taskx24);

  RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx24CompletedCnt_u32);

  RBSYS_TerminateTask();
}

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  TASK(TaskBaseCtrlCycx4pLow)
  {
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx4pLowCnt_u32);
    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx4pLowCnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx4pLowCnt_u32);

    set_current_task_cnt(TaskBaseCtrlCycx4pLow, l_RBMESG_TaskBaseCtrlx4pLowCnt_u32);
    taskbody_prc_calls(prclist_taskx4pl);

    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx4pLowCompletedCnt_u32);

    RBSYS_TerminateTask();
  }

  TASK(TaskBaseCtrlCycx200Background)
  {
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);

    set_current_task_cnt(TaskBaseCtrlCycx200Background, l_RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
    taskbody_prc_calls(prclist_taskx200bg);

    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx200BackgroundCompletedCnt_u32);

    RBSYS_TerminateTask();
  }

  TASK(TaskEventCtrlExtPrio1)
  {
    RBMESG_DefineMESGDef(RBMESG_TaskEventCtrlExtPrio1Cnt_u32);
    RBMESG_IncrementMESG(RBMESG_TaskEventCtrlExtPrio1Cnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskEventCtrlExtPrio1Cnt_u32);

    set_current_task_cnt(TaskEventCtrlExtPrio1, l_RBMESG_TaskEventCtrlExtPrio1Cnt_u32);
    taskbody_prc_calls(prclist_taskeventprio1);

    RBMESG_IncrementMESG(RBMESG_TaskEventCtrlExtPrio1CompletedCnt_u32);

    RBSYS_TerminateTask();
  }

  TASK(TaskEventCtrlExtPrio2)
  {
    RBMESG_DefineMESGDef(RBMESG_TaskEventCtrlExtPrio2Cnt_u32);
    RBMESG_IncrementMESG(RBMESG_TaskEventCtrlExtPrio2Cnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskEventCtrlExtPrio2Cnt_u32);

    set_current_task_cnt(TaskEventCtrlExtPrio2, l_RBMESG_TaskEventCtrlExtPrio2Cnt_u32);
    taskbody_prc_calls(prclist_taskeventprio2);

    RBMESG_IncrementMESG(RBMESG_TaskEventCtrlExtPrio2CompletedCnt_u32);

    RBSYS_TerminateTask();
  }
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  TASK(TaskBaseCtrlCycx1Guest)
  {
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx1GuestCnt_u32);
    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx1GuestCnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx1GuestCnt_u32);

    set_current_task_cnt(TaskBaseCtrlCycx1Guest,l_RBMESG_TaskBaseCtrlx1GuestCnt_u32);
    taskbody_prc_calls(prclist_taskx1guest);

    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx1GuestCompletedCnt_u32);

    RBSYS_TerminateTask();
  }

  TASK(TaskBaseCtrlCycx2Guest)
  {
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx2GuestCnt_u32);
    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx2GuestCnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx2GuestCnt_u32);

    set_current_task_cnt(TaskBaseCtrlCycx2Guest,l_RBMESG_TaskBaseCtrlx2GuestCnt_u32);
    taskbody_prc_calls(prclist_taskx2guest);

    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx2GuestCompletedCnt_u32);

    RBSYS_TerminateTask();
  }

  TASK(TaskBaseCtrlCycx4Guest)
  {
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx4GuestCnt_u32);
    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx4GuestCnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx4GuestCnt_u32);

    set_current_task_cnt(TaskBaseCtrlCycx4Guest,l_RBMESG_TaskBaseCtrlx4GuestCnt_u32);
    taskbody_prc_calls(prclist_taskx4guest);

    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx4GuestCompletedCnt_u32);

    RBSYS_TerminateTask();
  }

  TASK(TaskBaseCtrlCycx10Guest)
  {
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx10GuestCnt_u32);
    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx10GuestCnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx10GuestCnt_u32);

    set_current_task_cnt(TaskBaseCtrlCycx10Guest,l_RBMESG_TaskBaseCtrlx10GuestCnt_u32);
    taskbody_prc_calls(prclist_taskx10guest);

    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx10GuestCompletedCnt_u32);

    RBSYS_TerminateTask();
  }

  TASK(TaskBaseCtrlCycx20Guest)
  {
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx20GuestCnt_u32);
    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx20GuestCnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx20GuestCnt_u32);

    set_current_task_cnt(TaskBaseCtrlCycx20Guest,l_RBMESG_TaskBaseCtrlx20GuestCnt_u32);
    taskbody_prc_calls(prclist_taskx20guest);

    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx20GuestCompletedCnt_u32);

    RBSYS_TerminateTask();
  }
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  TASK(TaskBaseCtrlCycx10)
  {
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx10Cnt_u32);
    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx10Cnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx10Cnt_u32);

    set_current_task_cnt(TaskBaseCtrlCycx10,l_RBMESG_TaskBaseCtrlx10Cnt_u32);
    taskbody_prc_calls(prclist_taskx10);

    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx10CompletedCnt_u32);

    RBSYS_TerminateTask();
  }

  TASK(TaskBaseCtrlCycx20)
  {
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx20Cnt_u32);
    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx20Cnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx20Cnt_u32);

    set_current_task_cnt(TaskBaseCtrlCycx20,l_RBMESG_TaskBaseCtrlx20Cnt_u32);
    taskbody_prc_calls(prclist_taskx20);

    RBMESG_IncrementMESG(RBMESG_TaskBaseCtrlx20CompletedCnt_u32);

    RBSYS_TerminateTask();
  }
#endif

/**
 * Triggering pseudo task on highest prio is used for killing untrusted application on other core.
 * This will invoke CallTrustedFunction within CC-AS TPSW framework and therefore preempted TPSW can be killed.
 * Hint: Works only for TPSWs running in tasks.
 */
TASK(TaskTPSWKillCore0)
{
  #if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)
    /*ROOT_SECTION: SPG_RBTPSW_KillCore0_Root | |(); */
    /*PROC_EP: SPG_RBTPSW_KillCore0 */
    /*ROOT_SECTION_END: */
  #endif

  RBSYS_TerminateTask();
}

TASK(TaskTPSWKillCore1)
{
  #if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)
    /*ROOT_SECTION: SPG_RBTPSW_KillCore1_Root | |(); */
    /*PROC_EP: SPG_RBTPSW_KillCore1 */
    /*ROOT_SECTION_END: */
  #endif

  RBSYS_TerminateTask();
}


/* no static because of polyspace analysis */
void sys_idle_loop(void)
{
  /* Idle loop: for(;;) => macro to allow polyspace overloading */
  SYS_ENDLESS_IDLE_LOOP
  {
    unsigned int coreid = RBSYS_getCoreID();
    const PRC_PTR* idle = c_TaskIdle;

    /* Concept:
     *   TaskIdle  => for normal background processes
     *   TaskIdleP => only for specific SYS/uC processes!
     *
     *  for TaskIdle best is to select core where no x1 task is running
     *  => to utilize x1-slot for every "super-cycle"
     *
     * VMPS:
     *   Complete BSW shall run on Core0, including TaskIdle
     *   ASW is running on Core1
     *
     * HostCore0GuestCore1:
     *    Brake system shall run on Core0, including TaskIdle
     *    Guest is running on Core1
     *
     */
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_None)
        if (coreid == RBSYS_OS_CORE_FOR_TaskBaseCtrlCycx1High)
        {
          idle = c_TaskIdleP;
        }
      #elif ((RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS) || (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1))
        if (coreid != RBSYS_OS_CORE_FOR_TaskBaseCtrlCycx1High)
        {
          idle = c_TaskIdleP;
        }
      #endif
      RBSYS_TEST_INJECTION_CheckIdleCfg();
    #endif

    // TODO: limit maximum idle speed: to be set by PDM etc. if bus contention is too high
    // clarified with Gerd Frick: solution is possible, memstack has a busy-status which can be used
    // -> we start with maximum idle-speed and measure the performance drop if first multi-core system
    // is running -> interface will be introduced if there is a performance benefit
    // => so sys_idleloop_request_rerun() has to be moved from this location to memstack
    sys_idleloop_request_rerun();

    taskbody_prc_calls(idle);

    sys_delayed_idleloop(coreid);

    sys_general_idleloop(coreid);

    RBSYS_TEST_INJECTION_LeaveInfiniteLoop();
  }
}


/* all cores run on same cbk_idle */
FUNC(boolean, OS_APPL_CODE) Os_Cbk_Idle(void)
{
  sys_idle_loop();
  return TRUE;
}

static_assert(OS_NUM_TASKS <= 32, "Error: there are more tasks available than there are bits in taskOvr");

static void check_task1ms_deadline_get_act_ts(uint32 current_match_ts) /* called in 0p5ms activation ISR */
{
#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)

  static uint8 act_cnt_1ms = 0;
  uint32 taskOvr = 0;

  set_task_activation_ts(Task0p5ms, current_match_ts);

  if ((act_cnt_1ms%2) == 0) // 1ms to be activated in this cycle
  {
    set_task_activation_ts(Task1ms, current_match_ts);  // OS API cannot be used because real OS activation is done at the end of the prev task
    if (is_task_still_active(Task1ms))
    {
      taskOvr |= ((uint32)1u << RBSYS_GetTaskIndex(Task1ms));  // 1ms not finished when 500us is activated
    }
  }
  act_cnt_1ms++;

  if (taskOvr != 0)
  {
    RBSYS_setTaskOverRunError(taskOvr);
  }
#else
  // DEM report not needed as 1ms overrun is detected via OS limit
  set_task_activation_ts(Task1ms, current_match_ts);
#endif

}

static void check_task_deadline_get_act_ts(uint32 current_match_ts) /* called in x1 activation ISR */
{
  static uint8 act_cnt = 0;
  uint32 taskOvr = 0;

  //if ((act_cnt%1) == 0) => x1 to be activated in this cycle. This is always true, the if statement is here for consistency.
  {
    set_task_activation_ts(TaskBaseCtrlCycx1High, current_match_ts);  // OS API cannot be used because real OS activation is done at the end of the prev task
    set_task_activation_ts(TaskBaseCtrlCycx1Low, current_match_ts);
    if (is_task_still_active(TaskBaseCtrlCycx1Low))
    {
      taskOvr |= ((uint32)1u << RBSYS_GetTaskIndex(TaskBaseCtrlCycx1Low));  // x1l not finished when x1 high is activated
    }
  }
  if ((act_cnt%2) == 0) // x2 to be activated in this cycle
  {
    set_task_activation_ts(TaskBaseCtrlCycx2, current_match_ts);
    if (is_task_still_active(TaskBaseCtrlCycx2))
    {
      taskOvr |= ((uint32)1u << RBSYS_GetTaskIndex(TaskBaseCtrlCycx2)); // x2 will be activated in this cycle: check that last execution has been finished
    }
    #if (RBFS_MCORE == RBFS_MCORE_ON)
    set_task_activation_ts(TaskBaseCtrlCycx2p, current_match_ts);
    if (is_task_still_active(TaskBaseCtrlCycx2p))
    {
      taskOvr |= ((uint32)1u << RBSYS_GetTaskIndex(TaskBaseCtrlCycx2p)); // x2p  will be activated in this cycle: check that last execution has been finished
    }
    #endif
  }
  if ((act_cnt%4) == 0)  // x4 to be activated in this cycle
  {
    set_task_activation_ts(TaskBaseCtrlCycx4, current_match_ts);
    if (is_task_still_active(TaskBaseCtrlCycx4))
    {
      taskOvr |= ((uint32)1u << RBSYS_GetTaskIndex(TaskBaseCtrlCycx4));
    }
  }
  if ((act_cnt%8) == 0)
  {
    set_task_activation_ts(TaskBaseCtrlCycx8, current_match_ts);
    if (is_task_still_active(TaskBaseCtrlCycx8))
    {
      taskOvr |= ((uint32)1u << RBSYS_GetTaskIndex(TaskBaseCtrlCycx8));
    }
  }
  /* avoid %24 => div for x24 task*/
  if (act_cnt == 0)
  {
    set_task_activation_ts(TaskBaseCtrlCycx24, current_match_ts);
    if (is_task_still_active(TaskBaseCtrlCycx24))
    {
      taskOvr |= ((uint32)1u << RBSYS_GetTaskIndex(TaskBaseCtrlCycx24));
    }
  }

  act_cnt++;  /* 0..23 */
  if (act_cnt > 23)
  {
    act_cnt = 0;
  }

  if (taskOvr != 0)
  {
    RBSYS_setTaskOverRunError(taskOvr);
  }
}

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  //activate all core 1 guest tasks at once
  //because all tasks are running on the same core, tasks are running in sequence according to their priority (higher priority task shall start first)
  //task overrun check is completely covered by OS through activation limit, no additional monitorings necessary like for brake tasks
  static void check_and_activate_guest_tasks_on_core1(uint32 current_match_ts)
  {
    static uint8 act_cnt = 0;
    (void)ActivateTask(TaskBaseCtrlCycx1Guest);
    set_task_activation_ts(TaskBaseCtrlCycx1Guest, current_match_ts);
    if((act_cnt % 2) == 0)
    {
      (void)ActivateTask(TaskBaseCtrlCycx2Guest);
      set_task_activation_ts(TaskBaseCtrlCycx2Guest, current_match_ts);
    }
    if((act_cnt % 4) == 0)
    {
      (void)ActivateTask(TaskBaseCtrlCycx4Guest);
      set_task_activation_ts(TaskBaseCtrlCycx4Guest, current_match_ts);
    }
    if((act_cnt % 10) == 0)
    {
      (void)ActivateTask(TaskBaseCtrlCycx10Guest);
      set_task_activation_ts(TaskBaseCtrlCycx10Guest, current_match_ts);
    }
    if((act_cnt % 20) == 0)
    {
      (void)ActivateTask(TaskBaseCtrlCycx20Guest);
      set_task_activation_ts(TaskBaseCtrlCycx20Guest, current_match_ts);
    }

    //increment counter and reset it when it reaches 20 to avoid an overflow
    //UINT32 MAX is not divisible by 10 or 20, so letting the counter overflow will lead to too early activated x10 and x20 tasks
    act_cnt++;
    if(act_cnt > 19)
    {
      act_cnt = 0;
    }
  }
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  //activate all Airbag 15 specific tasks at once
  //because all tasks are running on the same core, tasks are running in sequence according to their priority (higher priority task shall start first)
  //task overrun check is completely covered by OS through activation limit, no additional monitorings necessary like for brake tasks
  static void check_and_activate_ab15_tasks(uint32 current_match_ts)
  {
    static uint8 act_cnt = 0;
    if((act_cnt % 10) == 0)
    {
      (void)ActivateTask(TaskBaseCtrlCycx10);
      set_task_activation_ts(TaskBaseCtrlCycx10, current_match_ts);
    }
    if((act_cnt % 20) == 0)
    {
      (void)ActivateTask(TaskBaseCtrlCycx20);
      set_task_activation_ts(TaskBaseCtrlCycx20, current_match_ts);
    }

    //increment counter and reset it when it reaches 20 to avoid an overflow
    //UINT32 MAX is not divisible by 10 or 20, so letting the counter overflow will lead to too early activated x10 and x20 tasks
    act_cnt++;
    if(act_cnt > 19)
    {
      act_cnt = 0;
    }
  }
#endif

static uint32 RBSYS_ISRcnt_1ms;
/*[[MEASUREMENT*/
/*NAME=RBSYS_ISRcnt_1ms*/
/*COMMENT=ISR counter for 500us timer interrupt if 500us task is activated, otherwise for 1ms*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
static void RBSYS_DynScheduleHandlerFast(void)
{
  uint32 timestamp, cmp, delta;

  RBSYS_ISRcnt_1ms++;

  RBSYS_SchM_Enter_GlobLock();
  {
    // get compare value as ideal activation point based on synchronized counter
    cmp = RBSYS_SYNCTIME_CMP0;

    // calculate delay between ideal task activation and real activation
    delta = RBSYS_getSynctimeTickCtr() - cmp;

    // use for activation timestamp the real-time counter as consistent timebase (hint: rt counter is used for all members of taskstats structures)
    timestamp = RBSYS_getRealtimeTickCtr() - delta;

    cmp += RBSYS_convertUsecToTimerTicks(CYCLETIME_STM04); // ToDo: check next match between current counter value and compare (current counter > compare match)
    RBSYS_SYNCTIME_CMP0 = cmp;


    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      STM0STC = 0x10;      // reset compare match bit to get new interrupt with next match
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      // clear interrupt to not get stuck in interrupt loop
      RBSYS_SYNCTIME_CLRINT = 0x1; // Synctime Compare0
    #endif
  }
  RBSYS_SchM_Exit_GlobLock();

  #if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
    (void)ActivateTask(Task0p5ms);
  #else
    (void)ActivateTask(Task1ms);
  #endif

  check_task1ms_deadline_get_act_ts(timestamp);
}

static uint32 RBSYS_ISRcnt_x1;
/*[[MEASUREMENT*/
/*NAME=RBSYS_ISRcnt_x1*/
/*COMMENT=ISR counter for 5ms timer interrupt*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
static void RBSYS_DynScheduleHandler5ms(void)
{
  uint32 timestamp, cmp, delta;

  RBSYS_ISRcnt_x1++;

  RBSYS_SchM_Enter_GlobLock();
  {
    // get compare value as ideal activation point based on synchronized counter
    cmp = RBSYS_SYNCTIME_CMP1;

    // calculate delay between ideal task activation and real activation
    delta = RBSYS_getSynctimeTickCtr() - cmp;

    // use for activation timestamp the real-time counter as consistent timebase (hint: rt counter is used for all members of taskstats structures)
    timestamp = RBSYS_getRealtimeTickCtr() - delta;

    cmp += RBSYS_convertUsecToTimerTicks(CYCLETIME_x1); // ToDo: check next match between current counter value and compare (current counter > compare match)
    RBSYS_SYNCTIME_CMP1 = cmp;


    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      STM0STC = 0x20;
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      // clear interrupt to not get stuck in interrupt loop
      RBSYS_SYNCTIME_CLRINT = 0x2; // Synctime Compare1
    #endif
  }
  RBSYS_SchM_Exit_GlobLock();

  (void)ActivateTask(TaskBaseCtrlCycx1High);

  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
    check_and_activate_guest_tasks_on_core1(timestamp);
  #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
    check_and_activate_ab15_tasks(timestamp);
  #endif

  // check manually for deadline (lower prios must finish with x1 trigger of same activation cycle): MCore approach
  // x1h and 1ms checks are done with ActivatTask
  // additionally do some task statistics stuff
  check_task_deadline_get_act_ts(timestamp);
}

/** Scheduling Interrupt Concept:
  * - P1x/U2A: Two independent interrupts (one STM / TPTM with each 2 compares and independent interrupt sources)
  * - Stellar: One common interrupt (Per each ARC, all Compare-Interrupts are mapped to 1 interrupt source and to one Core only)
  *            Hint: Should always be mapped to Core of fastest Task (which may then forward the interrupt per CrossCore-ISR)
  */
#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  ISR(ISRCommonTimer)
  {
    uint32 interruptStatus = RBSYS_SYNCTIME_INT_STATUS;
    uint32 activeInterruptIdx = RB_GetLsbSetPosition_u32(interruptStatus);

    /* activeInterruptIdx == 0: No Interrupt active */
    /* activeInterruptIdx == 1: Compare0 IRQ active -> ideally, this should be the highest priority Compare (to be processed first) */
    /* activeInterruptIdx == 2: Compare1 IRQ active */

    switch(activeInterruptIdx)
    {
      case 1:
        RBSYS_DynScheduleHandlerFast();
        break;
      case 2:
        RBSYS_DynScheduleHandler5ms();
        break;
      default:
        assert(0); //< unexpected timer interrupt source
        break;
    }
  }
#else
  /* 500us timer interrupt service routine if 500us task is activated, otherwise 1ms */
  ISR(ISRSTM04)
  {
    RBSYS_DynScheduleHandlerFast();
  }

  /* 5ms timer interrupt service routine */
  ISR(ISRSTM05)
  {
    RBSYS_DynScheduleHandler5ms();
  }

  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
    /* 500us timer interrupt service routine for Airbag 15 */
    ISR(ISR0p5ms)
    {
    }
  #endif
#endif


#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
  static uint32 RBSYS_ISRcnt_SWINT0;
  /*[[MEASUREMENT*/
  /*NAME=RBSYS_ISRcnt_SWINT0*/
  /*COMMENT=ISR counter for SWINT0 (software interrupt 0)*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/

  /* ISR for software interrupt 0 - only for BERT:
  * Concept: BERT must synchronize both cores in addition to stop all asynchronous bus-masters.
  * BERT is running on one core in every second x1H task and must use SWINT0 to sync other core.
  * Therefore it must be ensured that SWINT0 ISR is executed on other core than x1h task is running.
  */
  ISR(ISRSWINT0)
  {
    RBSYS_ISRcnt_SWINT0++;
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      RBSYS_ClearIRQ_SWINT0();

      /*ROOT_SECTION: SPG_ISRSWINT0_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRSWINT0 */
      /*ROOT_SECTION_END: */
    #endif
  }

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    static uint32 RBSYS_ISRcnt_MTTCANI0;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_MTTCANI0*/
    /*COMMENT=ISR counter for interrupt 0 of MTTCAN0*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* ISR for interrupt 0 of MTTCAN0 */
    ISR(ISRMTTCANI0)
    {
      RBSYS_ISRcnt_MTTCANI0++;

      /*ROOT_SECTION: SPG_ISRMTTCANI0_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRMTTCANI0 */
      /*ROOT_SECTION_END: */
    }


    static uint32 RBSYS_ISRcnt_MCAN0I0;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_MCAN0I0*/
    /*COMMENT=ISR counter for interrupt 0 of MCAN0*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* ISR for interrupt 0 of MCAN0 */
    ISR(ISRMCAN0I0)
    {
      RBSYS_ISRcnt_MCAN0I0++;

      /*ROOT_SECTION: SPG_ISRMCAN0I0_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRMCAN0I0 */
      /*ROOT_SECTION_END: */
    }


    static uint32 RBSYS_ISRcnt_MCAN1I0;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_MCAN1I0*/
    /*COMMENT=ISR counter for interrupt 0 of MCAN1*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* ISR for interrupt 0 of MCAN1 */
    ISR(ISRMCAN1I0)
    {
      RBSYS_ISRcnt_MCAN1I0++;

      /*ROOT_SECTION: SPG_ISRMCAN1I0_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRMCAN1I0 */
      /*ROOT_SECTION_END: */
    }


    static uint32 RBSYS_ISRcnt_MCAN2I0;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_MCAN2I0*/
    /*COMMENT=ISR counter interrupt 0 of MCAN2*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* ISR for interrupt 0 of MCAN2 */
    ISR(ISRMCAN2I0)
    {
      RBSYS_ISRcnt_MCAN2I0++;

      /*ROOT_SECTION: SPG_ISRMCAN2I0_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRMCAN2I0 */
      /*ROOT_SECTION_END: */
    }

  #else

    static uint32 RBSYS_ISRcnt_CAN0REC;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_CAN0REC*/
    /*COMMENT=ISR counter for CAN0 transmit/receive FIFO receive completion interrupt*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* CAN0 transmit/receive FIFO receive completion interrupt */
    ISR(ISRCAN0REC)
    {
      RBSYS_ISRcnt_CAN0REC++;

      /*ROOT_SECTION: SPG_ISRCAN0REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRCAN0REC */
      /*ROOT_SECTION_END: */
    }

    static uint32 RBSYS_ISRcnt_CAN0TRX;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_CAN0TRX*/
    /*COMMENT=ISR counter for CAN0 transmit interrupt*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* CAN0 transmit interrupt */
    ISR(ISRCAN0TRX)
    {
      RBSYS_ISRcnt_CAN0TRX++;

      /*ROOT_SECTION: SPG_ISRCAN0TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRCAN0TRX */
      /*ROOT_SECTION_END: */
    }

    static uint32 RBSYS_ISRcnt_CAN1REC;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_CAN1REC*/
    /*COMMENT=ISR counter for CAN1 transmit/receive FIFO receive completion interrupt*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* CAN1 transmit/receive FIFO receive completion interrupt */
    ISR(ISRCAN1REC)
    {
      RBSYS_ISRcnt_CAN1REC++;

      /*ROOT_SECTION: SPG_ISRCAN1REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRCAN1REC */
      /*ROOT_SECTION_END: */
    }

    static uint32 RBSYS_ISRcnt_CAN1TRX;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_CAN1TRX*/
    /*COMMENT=ISR counter for CAN1 transmit interrupt*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* CAN1 transmit interrupt */
    ISR(ISRCAN1TRX)
    {
      RBSYS_ISRcnt_CAN1TRX++;

      /*ROOT_SECTION: SPG_ISRCAN1TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRCAN1TRX */
      /*ROOT_SECTION_END: */
    }

    static uint32 RBSYS_ISRcnt_CAN2REC;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_CAN2REC*/
    /*COMMENT=ISR counter for CAN2 transmit/receive FIFO receive completion interrupt*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* CAN2 transmit/receive FIFO receive completion interrupt */
    ISR(ISRCAN2REC)
    {
      RBSYS_ISRcnt_CAN2REC++;

      /*ROOT_SECTION: SPG_ISRCAN2REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRCAN2REC */
      /*ROOT_SECTION_END: */
    }

    static uint32 RBSYS_ISRcnt_CAN2TRX;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_CAN2TRX*/
    /*COMMENT=ISR counter for CAN2 transmit interrupt*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* CAN2 transmit interrupt */
    ISR(ISRCAN2TRX)
    {
      RBSYS_ISRcnt_CAN2TRX++;

      /*ROOT_SECTION: SPG_ISRCAN2TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRCAN2TRX */
      /*ROOT_SECTION_END: */
    }

    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_STMStellar) )
      static uint32 RBSYS_ISRcnt_CAN6REC;
      /*[[MEASUREMENT*/
      /*NAME=RBSYS_ISRcnt_CAN6REC*/
      /*COMMENT=ISR counter for CAN6 transmit/receive FIFO receive completion interrupt*/
      /*MTEVENT=c_MT_Default_Task_1ms*/
      /*]]MEASUREMENT*/

      /* CAN6 transmit/receive FIFO receive completion interrupt */
      ISR(ISRCAN6REC)
      {
        RBSYS_ISRcnt_CAN6REC++;

        /*ROOT_SECTION: SPG_ISRCAN6REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
        /*PROC_EP: SPG_ISRCAN6REC */
        /*ROOT_SECTION_END: */
      }

      static uint32 RBSYS_ISRcnt_CAN6TRX;
      /*[[MEASUREMENT*/
      /*NAME=RBSYS_ISRcnt_CAN6TRX*/
      /*COMMENT=ISR counter for CAN6 transmit interrupt*/
      /*MTEVENT=c_MT_Default_Task_1ms*/
      /*]]MEASUREMENT*/

      /* CAN6 transmit interrupt */
      ISR(ISRCAN6TRX)
      {
        RBSYS_ISRcnt_CAN6TRX++;

        /*ROOT_SECTION: SPG_ISRCAN6TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
        /*PROC_EP: SPG_ISRCAN6TRX */
        /*ROOT_SECTION_END: */
      }

      static uint32 RBSYS_ISRcnt_CAN8REC;
      /*[[MEASUREMENT*/
      /*NAME=RBSYS_ISRcnt_CAN8REC*/
      /*COMMENT=ISR counter for CAN8 transmit/receive FIFO receive completion interrupt*/
      /*MTEVENT=c_MT_Default_Task_1ms*/
      /*]]MEASUREMENT*/

      /* CAN8 transmit/receive FIFO receive completion interrupt */
      ISR(ISRCAN8REC)
      {
        RBSYS_ISRcnt_CAN8REC++;

        /*ROOT_SECTION: SPG_ISRCAN8REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
        /*PROC_EP: SPG_ISRCAN8REC */
        /*ROOT_SECTION_END: */
      }

      static uint32 RBSYS_ISRcnt_CAN8TRX;
      /*[[MEASUREMENT*/
      /*NAME=RBSYS_ISRcnt_CAN8TRX*/
      /*COMMENT=ISR counter for CAN8 transmit interrupt*/
      /*MTEVENT=c_MT_Default_Task_1ms*/
      /*]]MEASUREMENT*/

      /* CAN8 transmit interrupt */
      ISR(ISRCAN8TRX)
      {
        RBSYS_ISRcnt_CAN8TRX++;

        /*ROOT_SECTION: SPG_ISRCAN8TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
        /*PROC_EP: SPG_ISRCAN8TRX */
        /*ROOT_SECTION_END: */
      }
    #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
      static uint32 RBSYS_ISRcnt_CAN3REC;
      /*[[MEASUREMENT*/
      /*NAME=RBSYS_ISRcnt_CAN3REC*/
      /*COMMENT=ISR counter for CAN3 transmit/receive FIFO receive completion interrupt*/
      /*MTEVENT=c_MT_Default_Task_1ms*/
      /*]]MEASUREMENT*/

      /* CAN3 transmit/receive FIFO receive completion interrupt */
      ISR(ISRCAN3REC)
      {
        RBSYS_ISRcnt_CAN3REC++;

        /*ROOT_SECTION: SPG_ISRCAN3REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
        /*PROC_EP: SPG_ISRCAN3REC */
        /*ROOT_SECTION_END: */
      }

      static uint32 RBSYS_ISRcnt_CAN3TRX;
      /*[[MEASUREMENT*/
      /*NAME=RBSYS_ISRcnt_CAN3TRX*/
      /*COMMENT=ISR counter for CAN3 transmit interrupt*/
      /*MTEVENT=c_MT_Default_Task_1ms*/
      /*]]MEASUREMENT*/

      /* CAN3 transmit interrupt */
      ISR(ISRCAN3TRX)
      {
        RBSYS_ISRcnt_CAN3TRX++;

        /*ROOT_SECTION: SPG_ISRCAN3TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
        /*PROC_EP: SPG_ISRCAN3TRX */
        /*ROOT_SECTION_END: */
      }
    #endif
  #endif

  static uint32 RBSYS_ISRcnt_FLX0LINE0;
  /*[[MEASUREMENT*/
  /*NAME=RBSYS_ISRcnt_FLX0LINE0*/
  /*COMMENT=ISR counter for universal interrupt channel A of FLXA0*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/

  /* ISR for universal interrupt channel A of FLXA0 */
  ISR(ISRFLX0LINE0)
  {
    RBSYS_ISRcnt_FLX0LINE0++;

    /*ROOT_SECTION: SPG_ISRFLX0LINE0_Root |RBA_RUNTIME_MSR_PROC(&|); */
    /*PROC_EP: SPG_ISRFLX0LINE0 */
    /*ROOT_SECTION_END: */
  }


  #if( RBFS_uCFamily != RBFS_uCFamily_RenesasU2C )
    static uint32 RBSYS_ISRcnt_FLX1LINE0;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_FLX1LINE0*/
    /*COMMENT=ISR counter for universal interrupt channel A of FLXA1*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* ISR for universal interrupt channel A of FLXA1 */
    ISR(ISRFLX1LINE0)
    {
      RBSYS_ISRcnt_FLX1LINE0++;

      /*ROOT_SECTION: SPG_ISRFLX1LINE0_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRFLX1LINE0 */
      /*ROOT_SECTION_END: */
    }
  #endif

  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x ) //< currently, LIN Interrupts are only used on P1x devices
    static uint32 RBSYS_ISRcnt_RLIN30RX;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_RLIN30RX*/
    /*COMMENT=ISR counter for RLIN3_0 interrupt 0 receive */
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* ISR for RLIN3_0 interrupt 0 receive */
    ISR(ISRRLIN30RX)
    {
      RBSYS_ISRcnt_RLIN30RX++;

      /*ROOT_SECTION: SPG_ISRRLIN30RX_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRRLIN30RX */
      /*ROOT_SECTION_END: */
    }


    static uint32 RBSYS_ISRcnt_RLIN30STATUS;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_RLIN30STATUS*/
    /*COMMENT=ISR counter for RLIN3_0 interrupt 0 status */
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* ISR for RLIN3_0 interrupt 0 status  */
    ISR(ISRRLIN30STATUS)
    {
      RBSYS_ISRcnt_RLIN30STATUS++;

      /*ROOT_SECTION: SPG_ISRRLIN30STATUS_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRRLIN30STATUS */
      /*ROOT_SECTION_END: */
    }


    static uint32 RBSYS_ISRcnt_RLIN31RX;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_RLIN31RX*/
    /*COMMENT=ISR counter for RLIN3_1 interrupt 0 receive */
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* ISR for RLIN3_1 interrupt 0 receive */
    ISR(ISRRLIN31RX)
    {
      RBSYS_ISRcnt_RLIN31RX++;

      /*ROOT_SECTION: SPG_ISRRLIN31RX_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRRLIN31RX */
      /*ROOT_SECTION_END: */
    }


    static uint32 RBSYS_ISRcnt_RLIN31STATUS;
    /*[[MEASUREMENT*/
    /*NAME=RBSYS_ISRcnt_RLIN31STATUS*/
    /*COMMENT=ISR counter for RLIN3_1 interrupt 0 status */
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/

    /* ISR for RLIN3_1 interrupt 0 status  */
    ISR(ISRRLIN31STATUS)
    {
      RBSYS_ISRcnt_RLIN31STATUS++;

      /*ROOT_SECTION: SPG_ISRRLIN31STATUS_Root |RBA_RUNTIME_MSR_PROC(&|); */
      /*PROC_EP: SPG_ISRRLIN31STATUS */
      /*ROOT_SECTION_END: */
    }
  #endif
#else
  #warning("ToDo: RBSYS Stellar support")
#endif


FUNC(Os_StopwatchTickType, OS_CALLOUT_CODE) Os_Cbk_GetStopwatch(void)
{
   return (Os_StopwatchTickType)RBSYS_getRealtimeTickCtr();
}

FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TaskStart(TaskType task)
{
  set_task_start_ts(task, Os_Cbk_GetStopwatch());

  RBSYS_RuntimeMeasure_TaskStart(task);

  /*ROOT_SECTION: SPG_T1_TaskStart_Root | |(task); */
  /*PROC_EP: SPG_T1_TaskStart */
  /*ROOT_SECTION_END: */
}


#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  static uint32 RBSYS_TASKcnt_x200bg_skippedActivation;
  /*[[MEASUREMENT*/
  /*NAME=RBSYS_TASKcnt_x200bg_skippedActivation*/
  /*COMMENT=Skip counter of TaskBaseCtrlCycx200Background activation*/
  /*MTEVENT=c_MT_Default_Task_x2*/
  /*]]MEASUREMENT*/
#endif


FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TaskEnd(TaskType task)
{
  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
    if (task == TaskBaseCtrlCycx4)
    {
      /* activate at the end of x4 the x4p low */
      (void)ActivateTask(TaskBaseCtrlCycx4pLow);
    }
    else if (task == TaskBaseCtrlCycx2p)
    {
      static uint8 RBSYS_TASKcnt_x2p = 100;

      if (RBSYS_TASKcnt_x2p >= 100)
      {
        if (!(is_task_still_active(TaskBaseCtrlCycx200Background)))
        {
          (void)ActivateTask(TaskBaseCtrlCycx200Background);
        }
        else
        {
          /* task could not be activated as it is still running - increment skip counter as measurement variable */
          RBSYS_TASKcnt_x200bg_skippedActivation++;
        }
        RBSYS_TASKcnt_x2p=0;
      }
      RBSYS_TASKcnt_x2p++;
    }
    else
    {
      /* MISRA - nothing to do here for all other tasks */
    }
  #endif

  /*ROOT_SECTION: SPG_T1_TaskEnd_Root | |(task); */
  /*PROC_EP: SPG_T1_TaskEnd */
  /*ROOT_SECTION_END: */

  RBSYS_RuntimeMeasure_TaskEnd(task);

  set_task_end_ts(task, Os_Cbk_GetStopwatch());
}

FUNC(void, OS_CALLOUT_CODE) Os_Cbk_ISRStart(ISRType isr)
{
  set_isr_start_ts(isr, Os_Cbk_GetStopwatch());

  RBSYS_RuntimeMeasure_IsrStart(isr);

  /*ROOT_SECTION: SPG_T1_IsrStart_Root | |(isr); */
  /*PROC_EP: SPG_T1_IsrStart */
  /*ROOT_SECTION_END: */
}

FUNC(void, OS_CALLOUT_CODE) Os_Cbk_ISREnd(ISRType isr)
{
  /*ROOT_SECTION: SPG_T1_IsrEnd_Root | |(isr); */
  /*PROC_EP: SPG_T1_IsrEnd */
  /*ROOT_SECTION_END: */
  RBSYS_RuntimeMeasure_IsrEnd(isr);
  #if (RBFS_SysDebugUnbalancedLock == RBFS_SysDebugUnbalancedLock_ON)
    RBSYS_checkUnbalancedLock((uint32)isr->entry_function);
  #endif
  set_isr_end_ts(isr, Os_Cbk_GetStopwatch());
}


#if (RBFS_MCORE == RBFS_MCORE_ON)

  FUNC(void, OS_CALLOUT_CODE) Os_Cbk_CrosscoreISRStart(CoreIdType core_id)
  {
    RBSYS_RuntimeMeasure_CrossCoreIntStart();
  }

  FUNC(void, OS_CALLOUT_CODE) Os_Cbk_CrosscoreISREnd(CoreIdType core_id)
  {
    RBSYS_RuntimeMeasure_CrossCoreIntEnd();
  }

#endif


#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
  /* OS Category 1 ISR for "hypervisor trap (HVTRAP)" */
  CAT1_ISR(EXCHVTRAP)
  {
    RBSYS_TRAP_PERMISSION_ENTRY();  //< Set Core SPID to SAFE

    /*ROOT_SECTION: SPG_RBSYS_EXCHVTRAP_Root | |(); */
    /*PROC_EP: SPG_RBSYS_EXCHVTRAP */
    /*ROOT_SECTION_END: */

    RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID
  }


  /* OS Category 1 ISR for "FE-level software exception" */
  CAT1_ISR(EXCFETRAP)
  {
    RBSYS_TRAP_PERMISSION_ENTRY();  //< Set Core SPID to SAFE

    /*ROOT_SECTION: SPG_RBSYS_EXCFETRAP_Root | |(); */
    /*PROC_EP: SPG_RBSYS_EXCFETRAP */
    /*ROOT_SECTION_END: */

    RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID
  }


  /* OS Category 1 ISR for "co-processor unusable exception" */
  CAT1_ISR(EXCUCPOP)
  {
    RBSYS_TRAP_PERMISSION_ENTRY();  //< Set Core SPID to SAFE

    /*ROOT_SECTION: SPG_RBSYS_EXCUCPOP_Root | |(); */
    /*PROC_EP: SPG_RBSYS_EXCUCPOP */
    /*ROOT_SECTION_END: */

    RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID
  }


  /* OS Category 1 ISR for "FE-level non maskable interrupt" */
  CAT1_ISR(EXCFENMI)
  {
    RBSYS_TRAP_PERMISSION_ENTRY();  //< Set Core SPID to SAFE

    /*ROOT_SECTION: SPG_RBSYS_EXCFENMI_Root | |(); */
    /*PROC_EP: SPG_RBSYS_EXCFENMI */
    /*ROOT_SECTION_END: */

    RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID
  }

  #if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_NO)
  /* This exceptions are only configured in SC1 system to be handled by RBSYS.
  * In case of SC3/4 no ISR placed at this vector - handled directly via OS (Os_abort) together with TPSW framework */

    /* OS Category 1 ISR for "Privileged instruction exception" */
    CAT1_ISR(EXCPIE)
    {
      RBSYS_TRAP_PERMISSION_ENTRY();  //< Set Core SPID to SAFE

      /*ROOT_SECTION: SPG_RBSYS_EXCPIE_Root | |(); */
      /*PROC_EP: SPG_RBSYS_EXCPIE */
      /*ROOT_SECTION_END: */

      RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID
    }


    /* OS Category 1 ISR for "Memory protection exception" */
    CAT1_ISR(EXCMDP)
    {
      RBSYS_TRAP_PERMISSION_ENTRY();  //< Set Core SPID to SAFE

      RBSYS_HandleSupervisorMpuViolation();

      RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID
    }
  #endif


  #if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)
    /* OS Category 1 ISR for "Timing protection (core 0)" */
    CAT1_ISR(ISRSTM06_SC4core0)
    {
      RBSYS_TRAP_PERMISSION_ENTRY();  //< Set Core SPID to SAFE

      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        /*ROOT_SECTION: SPG_RBSYS_TPSWTimeout_C0_Root | |(); */
        /*PROC_EP: SPG_RBSYS_TPSWTimeout */
        /*ROOT_SECTION_END: */
      #else
        InvalidInt();
      #endif

      RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID
    }

    /* OS Category 1 ISR for "Timing protection (core 1)" */
    CAT1_ISR(ISRSTM07_SC4core1)
    {
      RBSYS_TRAP_PERMISSION_ENTRY();  //< Set Core SPID to SAFE

      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        /*ROOT_SECTION: SPG_RBSYS_TPSWTimeout_C1_Root | |(); */
        /*PROC_EP: SPG_RBSYS_TPSWTimeout */
        /*ROOT_SECTION_END: */
      #else
        InvalidInt();
      #endif

      RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID
    }
  #endif

#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  /* TODO: Current SC1 Stellar OS includes SC4 interrupts, to be removed later */
  CAT1_ISR(ISRGenericTimerCore0)
  {
    assert(0); //< not yet implemented
  }
  CAT1_ISR(ISRGenericTimerCore1)
  {
    assert(0); //< not yet implemented
  }
  #warning("ToDo: RBSYS Stellar support")

#endif


/** @} */
/* End ingroup RBSYS */
