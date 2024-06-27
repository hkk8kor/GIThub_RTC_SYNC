/**
 * @ingroup RBSYS
 * @{
 *
 * \file
 * \brief Dynamics
 *
 * 'Detailed description of this module, several lines/paragraphes'
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"
#include "RBSYSStub_EntryPoint.h" // defines taskCounters

/* used interfaces */
#include "Os.h"
#include "RBSYS_TaskInfo.h"
#include "RBSYS_CpuInfo.h"
//#include "RBSYS_Idle.h"
//#include "RBSYS_TaskStats.h"
//#include "RBSYS_TimerSetup.h"

// from rba_Runtime.h
/* Controlled measure off, create empty macros */
# define RBA_RUNTIME_MSR_CODESEQ_ID(ID,CODESEQ) (CODESEQ)
# define RBA_RUNTIME_MSR_CODESEQ(FUNNAME,CODESEQ) (CODESEQ)
# define RBA_RUNTIME_MSR_PROC(PROCNAME) (PROCNAME)()



/******************************************************************************/
/* default header includes for appl. processes via merge proc                 */
/******************************************************************************/
/*ROOT_SECTION: HeaderIncludes_Root |#include "|" */
/*PROC_EP: HeaderIncludes */
/*ROOT_SECTION_END: */


/******************************************************************************/
/* header includes for ECM exception handler via MergeProc                    */
/******************************************************************************/
/*ROOT_SECTION: ExceptionHandlerHeaderIncludes_Root |#include "|" */
/*PROC_EP: ExceptionHandlerHeaderIncludes */
/*ROOT_SECTION_END: */

/* realized interfaces */
// #include "RBSYS_PlantStartupCtrl.h"


/* typedef for processes: void-void function call */
typedef void (*PRC_PTR)(void);

typedef void (*RBHWBIST_PreCInit_fptr_t)(void);
typedef void (*RBHWBIST_PRC_PTR)(RBHWBIST_PreCInit_fptr_t returnAddress);

/******************************************************************************/
/* proc sections for xcp simulation processes via merge proc                  */
/******************************************************************************/
/*ROOT_SECTION: SPG_SIM_XCP_ExternDeclarations_Root |extern void | (void); */
/*PROC_EP: SPG_SIM_XCP_CLIENT_Init*/
/*PROC_EP: SPG_SIM_XCP_CLIENT_500us*/
/*PROC_EP: SPG_SIM_XCP_CLIENT_1ms*/
/*PROC_EP: SPG_SIM_XCP_CLIENT_X1*/
/*PROC_EP: SPG_SIM_XCP_CLIENT_X2*/
/*PROC_EP: SPG_SIM_XCP_CLIENT_X4*/
/*PROC_EP: SPG_SIM_XCP_CLIENT_X8*/
/*PROC_EP: SPG_SIM_XCP_CLIENT_X24*/
/*ROOT_SECTION_END:  */
/* Prototyping for use in IdleTask */
//static void taskbody_prc_calls(const PRC_PTR proc_table[]);


#if( 0 )
static void RBSYSStub_UnusedProcs(void)
{
  /*ROOT_SECTION: SPG_RBSYS_AfterResetSync_Root | |(); */
  /*PROC_EP: SPG_RBSYS_AfterResetSync */
  /*ROOT_SECTION_END: */
}
#endif


const PRC_PTR c_TaskIdle[] =
{
  /*ROOT_SECTION: SPG_TaskIdle_Root | &|, */
  /*PROC_EP: SPG_TaskIdle */
  /*ROOT_SECTION_END: */
  NULL
};

OSSim_ProcessMeasurePoint c_TaskIdle_pmp[] =
{
  /*ROOT_SECTION: SPG_TaskIdle_Root |OSSIM_PROC_MEAS_POINT_INIT(|), */
  /*PROC_EP: SPG_TaskIdle */
  /*ROOT_SECTION_END: */
  OSSIM_PROC_MEAS_POINT_LIST_END
};

#if (RBFS_MCORE == RBFS_MCORE_ON)
  const PRC_PTR c_TaskIdleP[] =
  {
    /*ROOT_SECTION: SPG_TaskIdleP_Root | &|, */
    /*PROC_EP: SPG_TaskIdleP */
    /*ROOT_SECTION_END: */
    NULL
  };

  OSSim_ProcessMeasurePoint c_TaskIdleP_pmp[] =
  {
    /*ROOT_SECTION: SPG_TaskIdleP_Root |OSSIM_PROC_MEAS_POINT_INIT(|), */
    /*PROC_EP: SPG_TaskIdleP */
    /*ROOT_SECTION_END: */
    OSSIM_PROC_MEAS_POINT_LIST_END
  };
#endif

const PRC_PTR c_TaskInit[] =
{
  /*ROOT_SECTION: SPG_TaskInit_Root | &|, */
  /*PROC_EP: SPG_TaskInit */
  /*ROOT_SECTION_END: */

  #if( RBFS_MCORE == RBFS_MCORE_ON )
    /*ROOT_SECTION: SPG_TaskInitP_Root | &|, */
    /*PROC_EP: SPG_TaskInitP */
    /*ROOT_SECTION_END: */
  #endif

  /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_Init_Root | &|, */
  /*PROC_EP: SPG_SIM_XCP_CLIENT_Init */
  /*ROOT_SECTION_END: */
  NULL
};

OSSim_ProcessMeasurePoint c_TaskInit_pmp[] =
{
  /*ROOT_SECTION: SPG_TaskInit_Root |OSSIM_PROC_MEAS_POINT_INIT(|), */
  /*PROC_EP: SPG_TaskInit */
  /*ROOT_SECTION_END: */
  OSSIM_PROC_MEAS_POINT_LIST_END
};

#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  const PRC_PTR c_Task0p5ms[] =
  {
    /*ROOT_SECTION: SPG_Task0p5ms_Root | &|, */
    /*PROC_EP: SPG_Task0p5ms */
    /*ROOT_SECTION_END: */


    /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_500us_Root | &|, */
    /*PROC_EP: SPG_SIM_XCP_CLIENT_500us */
    /*ROOT_SECTION_END: */
    NULL
  };

  OSSim_ProcessMeasurePoint c_Task0p5ms_pmp[] =
  {
    /*ROOT_SECTION: SPG_Task0p5ms_Root |  OSSIM_PROC_MEAS_POINT_INIT(|), */
    /*PROC_EP: SPG_Task0p5ms */
    /*ROOT_SECTION_END: */
    OSSIM_PROC_MEAS_POINT_LIST_END
  };
#endif

const PRC_PTR c_Task1ms[] =
{
  /*ROOT_SECTION: SPG_Task1ms_Root | &|, */
  /*PROC_EP: SPG_Task1ms */
  /*ROOT_SECTION_END: */

  /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_1ms_Root | &|, */
  /*PROC_EP: SPG_SIM_XCP_CLIENT_1ms */
  /*ROOT_SECTION_END: */
  NULL
};

OSSim_ProcessMeasurePoint c_Task1ms_pmp[] =
{
  /*ROOT_SECTION: SPG_Task1ms_Root |  OSSIM_PROC_MEAS_POINT_INIT(|), */
  /*PROC_EP: SPG_Task1ms */
  /*ROOT_SECTION_END: */
  OSSIM_PROC_MEAS_POINT_LIST_END
};

const PRC_PTR c_Taskx1h[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx1High_Root | &|, */
  /*PROC_EP: SPG_TaskBaseCtrlCycx1High */
  /*ROOT_SECTION_END: */
  NULL
};

OSSim_ProcessMeasurePoint c_Taskx1h_pmp[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx1High_Root |  OSSIM_PROC_MEAS_POINT_INIT(|), */
  /*PROC_EP: SPG_TaskBaseCtrlCycx1High */
  /*ROOT_SECTION_END: */
  OSSIM_PROC_MEAS_POINT_LIST_END
};

#if (RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON)
  const PRC_PTR c_FlexrayTask[] =
  {
    /*ROOT_SECTION: SPG_TaskFlexray_Root | &|, */
    /*PROC_EP: SPG_TaskFlexray */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

const PRC_PTR c_Taskx1l[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx1Low_Root | &|, */
  /*PROC_EP: SPG_TaskBaseCtrlCycx1Low */
  /*ROOT_SECTION_END: */

  /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_X1_Root | &|, */
  /*PROC_EP: SPG_SIM_XCP_CLIENT_X1 */
  /*ROOT_SECTION_END: */
  NULL
};

OSSim_ProcessMeasurePoint c_Taskx1l_pmp[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx1Low_Root |  OSSIM_PROC_MEAS_POINT_INIT(|), */
  /*PROC_EP: SPG_TaskBaseCtrlCycx1Low */
  /*ROOT_SECTION_END: */
  OSSIM_PROC_MEAS_POINT_LIST_END
};

const PRC_PTR c_Taskx2[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx2_Root | &|, */
  /*PROC_EP: SPG_TaskBaseCtrlCycx2 */
  /*ROOT_SECTION_END: */

  /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_X2_Root | &|, */
  /*PROC_EP: SPG_SIM_XCP_CLIENT_X2 */
  /*ROOT_SECTION_END: */
  NULL
};

OSSim_ProcessMeasurePoint c_Taskx2_pmp[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx2_Root |  OSSIM_PROC_MEAS_POINT_INIT(|), */
  /*PROC_EP: SPG_TaskBaseCtrlCycx2 */
  /*ROOT_SECTION_END: */
  OSSIM_PROC_MEAS_POINT_LIST_END
};

#if (RBFS_MCORE == RBFS_MCORE_ON)
  const PRC_PTR c_Taskx2p[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx2p_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx2p */
    /*ROOT_SECTION_END: */
    NULL
  };

  OSSim_ProcessMeasurePoint c_Taskx2p_pmp[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx2p_Root |  OSSIM_PROC_MEAS_POINT_INIT(|), */
    /*PROC_EP: SPG_TaskBaseCtrlCycx2p */
    /*ROOT_SECTION_END: */
    OSSIM_PROC_MEAS_POINT_LIST_END
  };
#endif

const PRC_PTR c_Taskx4[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx4_Root | &|, */
  /*PROC_EP: SPG_TaskBaseCtrlCycx4 */
  /*ROOT_SECTION_END: */

  /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_X4_Root | &|, */
  /*PROC_EP: SPG_SIM_XCP_CLIENT_X4*/
  /*ROOT_SECTION_END: */
  NULL
};

OSSim_ProcessMeasurePoint c_Taskx4_pmp[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx4_Root |  OSSIM_PROC_MEAS_POINT_INIT(|), */
  /*PROC_EP: SPG_TaskBaseCtrlCycx4 */
  /*ROOT_SECTION_END: */
  OSSIM_PROC_MEAS_POINT_LIST_END
};

const PRC_PTR c_Taskx8[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx8_Root | &|, */
  /*PROC_EP: SPG_TaskBaseCtrlCycx8 */
  /*ROOT_SECTION_END: */

  /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_X8_Root | &|, */
  /*PROC_EP: SPG_SIM_XCP_CLIENT_X8 */
  /*ROOT_SECTION_END: */
  NULL
};

OSSim_ProcessMeasurePoint c_Taskx8_pmp[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx8_Root |  OSSIM_PROC_MEAS_POINT_INIT(|), */
  /*PROC_EP: SPG_TaskBaseCtrlCycx8 */
  /*ROOT_SECTION_END: */
  OSSIM_PROC_MEAS_POINT_LIST_END
};

const PRC_PTR c_Taskx24[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx24_Root | &|, */
  /*PROC_EP: SPG_TaskBaseCtrlCycx24 */
  /*ROOT_SECTION_END: */

  /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_X24_Root | &|, */
  /*PROC_EP: SPG_SIM_XCP_CLIENT_X24 */
  /*ROOT_SECTION_END: */
  NULL
};

OSSim_ProcessMeasurePoint c_Taskx24_pmp[] =
{
  /*ROOT_SECTION: SPG_TaskBaseCtrlCycx24_Root |  OSSIM_PROC_MEAS_POINT_INIT(|), */
  /*PROC_EP: SPG_TaskBaseCtrlCycx24 */
  /*ROOT_SECTION_END: */
  OSSIM_PROC_MEAS_POINT_LIST_END
};

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  const PRC_PTR c_Taskx4pl[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx4pLow_Root | &|, */
    /*PROC_EP: SPG_RBAPPLIF_TraceMT_CM_BOS_X4PL */
    /*PROC_EP: SPG_TaskBaseCtrlCycx4pLow */
    /*ROOT_SECTION_END: */
    NULL
  };

  const PRC_PTR c_Taskx200bg[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx200bg_Root | &|, */
    /*PROC_EP: SPG_RBAPPLIF_TraceMT_CM_BOS_X200BG */
    /*PROC_EP: SPG_TaskBaseCtrlCycx200bg */
    /*ROOT_SECTION_END: */
    NULL
  };

  const PRC_PTR c_TaskEventExtPrio1[] =
  {
      /*ROOT_SECTION: SPG_TaskEventExtPrio1_Root | &|, */
      /*PROC_EP: SPG_RBAPPLIF_TraceMT_CM_BOS_EventExtPrio1 */
      /*PROC_EP: SPG_TaskEventExtPrio1 */
      /*ROOT_SECTION_END: */
      NULL
  };

  const PRC_PTR c_TaskEventExtPrio2[] =
  {
      /*ROOT_SECTION: SPG_TaskEventExtPrio2_Root | &|, */
      /*PROC_EP: SPG_RBAPPLIF_TraceMT_CM_BOS_EventExtPrio2 */
      /*PROC_EP: SPG_TaskEventExtPrio2 */
      /*ROOT_SECTION_END: */
      NULL
  };
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  const PRC_PTR c_Taskx1Guest[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx1Guest_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx1Guest */
    /*ROOT_SECTION_END: */

    /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_X1Guest_Root | &|, */
    /*PROC_EP: SPG_SIM_XCP_CLIENT_X1Guest */
    /*ROOT_SECTION_END: */
    NULL
  };

  OSSim_ProcessMeasurePoint c_Taskx1Guest_pmp[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx1Guest_Root | OSSIM_PROC_MEAS_POINT_INIT(|), */
    /*PROC_EP: SPG_TaskBaseCtrlCycx1Guest */
    /*ROOT_SECTION_END: */
    OSSIM_PROC_MEAS_POINT_LIST_END
  };

  const PRC_PTR c_Taskx2Guest[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx2Guest_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx2Guest */
    /*ROOT_SECTION_END: */

    /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_X2Guest_Root | &|, */
    /*PROC_EP: SPG_SIM_XCP_CLIENT_X2Guest */
    /*ROOT_SECTION_END: */
    NULL
  };

  OSSim_ProcessMeasurePoint c_Taskx2Guest_pmp[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx2Guest_Root | OSSIM_PROC_MEAS_POINT_INIT(|), */
    /*PROC_EP: SPG_TaskBaseCtrlCycx2Guest */
    /*ROOT_SECTION_END: */
    OSSIM_PROC_MEAS_POINT_LIST_END
  };

  const PRC_PTR c_Taskx4Guest[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx4Guest_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx4Guest */
    /*ROOT_SECTION_END: */

    /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_X4Guest_Root | &|, */
    /*PROC_EP: SPG_SIM_XCP_CLIENT_X4Guest */
    /*ROOT_SECTION_END: */
    NULL
  };

  OSSim_ProcessMeasurePoint c_Taskx4Guest_pmp[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx4Guest_Root | OSSIM_PROC_MEAS_POINT_INIT(|), */
    /*PROC_EP: SPG_TaskBaseCtrlCycx4Guest */
    /*ROOT_SECTION_END: */
    OSSIM_PROC_MEAS_POINT_LIST_END
  };

  const PRC_PTR c_Taskx10Guest[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx10Guest_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx10Guest */
    /*ROOT_SECTION_END: */

    /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_X10Guest_Root | &|, */
    /*PROC_EP: SPG_SIM_XCP_CLIENT_X10Guest */
    /*ROOT_SECTION_END: */
    NULL
  };

  OSSim_ProcessMeasurePoint c_Taskx10Guest_pmp[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx10Guest_Root | OSSIM_PROC_MEAS_POINT_INIT(|), */
    /*PROC_EP: SPG_TaskBaseCtrlCycx10Guest */
    /*ROOT_SECTION_END: */
    OSSIM_PROC_MEAS_POINT_LIST_END
  };

  const PRC_PTR c_Taskx20Guest[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx20Guest_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx20Guest */
    /*ROOT_SECTION_END: */

    /*ROOT_SECTION: SPG_SIM_XCP_CLIENT_X20Guest_Root | &|, */
    /*PROC_EP: SPG_SIM_XCP_CLIENT_X20Guest */
    /*ROOT_SECTION_END: */
    NULL
  };

  OSSim_ProcessMeasurePoint c_Taskx20Guest_pmp[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx20Guest_Root | OSSIM_PROC_MEAS_POINT_INIT(|), */
    /*PROC_EP: SPG_TaskBaseCtrlCycx20Guest */
    /*ROOT_SECTION_END: */
    OSSIM_PROC_MEAS_POINT_LIST_END
  };
#endif



const PRC_PTR c_TaskInitBaseOS[] =
{
  /*ROOT_SECTION: SPG_TaskInitBaseOS_Root | &|, */
  /*PROC_EP: SPG_TaskInitBaseOS */
  /*ROOT_SECTION_END: */

  #if( RBFS_MCORE == RBFS_MCORE_ON )
    /*ROOT_SECTION: SPG_TaskInitPBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskInitPBaseOS */
    /*ROOT_SECTION_END: */
  #endif
  NULL
};

#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  const PRC_PTR c_Task0p5msBaseOS[] =
  {
    /*ROOT_SECTION: SPG_Task0p5msBaseOS_Root | &|, */
    /*PROC_EP: SPG_Task0p5msBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

const PRC_PTR c_Task1msBaseOS[] =
{
  /*ROOT_SECTION: SPG_Task1msBaseOS_Root | &|, */
  /*PROC_EP: SPG_Task1msBaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

const PRC_PTR c_Taskx1hBaseOS[] =
{
  /*ROOT_SECTION: SPG_Taskx1hBaseOS_Root | &|, */
  /*PROC_EP: SPG_Taskx1hBaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

const PRC_PTR c_Taskx1lBaseOS[] =
{
  /*ROOT_SECTION: SPG_Taskx1lBaseOS_Root | &|, */
  /*PROC_EP: SPG_Taskx1lBaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

const PRC_PTR c_Taskx2BaseOS[] =
{
  /*ROOT_SECTION: SPG_Taskx2BaseOS_Root | &|, */
  /*PROC_EP: SPG_Taskx2BaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

#if (RBFS_MCORE == RBFS_MCORE_ON)
  const PRC_PTR c_Taskx2pBaseOS[] =
  {
    /*ROOT_SECTION: SPG_Taskx2pBaseOS_Root | &|, */
    /*PROC_EP: SPG_Taskx2pBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

const PRC_PTR c_Taskx4BaseOS[] =
{
  /*ROOT_SECTION: SPG_Taskx4BaseOS_Root | &|, */
  /*PROC_EP: SPG_Taskx4BaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

const PRC_PTR c_Taskx8BaseOS[] =
{
  /*ROOT_SECTION: SPG_Taskx8BaseOS_Root | &|, */
  /*PROC_EP: SPG_Taskx8BaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

const PRC_PTR c_Taskx24BaseOS[] =
{
  /*ROOT_SECTION: SPG_Taskx24BaseOS_Root | &|, */
  /*PROC_EP: SPG_Taskx24BaseOS */
  /*ROOT_SECTION_END: */
  NULL
};

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  const PRC_PTR c_Taskx4plBaseOS[] =
  {
    /*ROOT_SECTION: SPG_Taskx4plBaseOS_Root | &|, */
    /*PROC_EP: SPG_Taskx4plBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };

  const PRC_PTR c_Taskx200bgBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx200bgBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx200bgBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };

  const PRC_PTR c_TaskEventExtPrio1BaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskEventExtPrio1BaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskEventExtPrio1BaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };

  const PRC_PTR c_TaskEventExtPrio2BaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskEventExtPrio2BaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskEventExtPrio2BaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  const PRC_PTR c_Taskx1GuestBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx1GuestBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx1GuestBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };

  const PRC_PTR c_Taskx2GuestBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx2GuestBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx2GuestBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };

  const PRC_PTR c_Taskx4GuestBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx4GuestBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx4GuestBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };

  const PRC_PTR c_Taskx10GuestBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx10GuestBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx10GuestBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };

  const PRC_PTR c_Taskx20GuestBaseOS[] =
  {
    /*ROOT_SECTION: SPG_TaskBaseCtrlCycx20GuestBaseOS_Root | &|, */
    /*PROC_EP: SPG_TaskBaseCtrlCycx20GuestBaseOS */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

const PRC_PTR c_SysResetSync[] =
{
  /*ROOT_SECTION: SPG_RBSYS_ResetSync_Root | &|, */
  /*PROC_EP: SPG_RBSYS_ResetSync */
  /*ROOT_SECTION_END: */
  NULL
};


#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  RBMESG_DefineMESG(RBMESG_Task0p5msCnt_u32);
#endif
RBMESG_DefineMESG(RBMESG_Task1msCnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx1Cnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx1LowCnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx2Cnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx4Cnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx8Cnt_u32);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx24Cnt_u32);

#if (RBFS_MCORE == RBFS_MCORE_ON)
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx2pCnt_u32);
#endif

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx4pLowCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskEventCtrlExtPrio1Cnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskEventCtrlExtPrio2Cnt_u32);
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx1GuestCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx2GuestCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx4GuestCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx10GuestCnt_u32);
  RBMESG_DefineMESG(RBMESG_TaskBaseCtrlx20GuestCnt_u32);
#endif

/// ***************** The less important part *********************************

// ISRs aren't supported in sim, but entry points have to be defined for MergeProc
#define SIM_KILLED_ISR(func)  void func(void);void func(void)
// TPSW framework isn't supported in sim, too.
#define SIM_KILLED_TPSW_TASK(func)  void func(void);void func(void)
///< prototype trick: to avoid warning for currently unused functions.
///< I keep them 1. for MergeProc and 2. for potential to use later.


SIM_KILLED_TPSW_TASK(task_SPG_RBTPSW_KillCore0)
{
  /*ROOT_SECTION: SPG_RBTPSW_KillCore0_Root | |(); */
  /*PROC_EP: SPG_RBTPSW_KillCore0 */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_TPSW_TASK(task_SPG_RBTPSW_KillCore1)
{
  /*ROOT_SECTION: SPG_RBTPSW_KillCore1_Root | |(); */
  /*PROC_EP: SPG_RBTPSW_KillCore1 */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_TPSW_TASK(task_SPG_RBSYS_TPSWTimeout)
{
  /*ROOT_SECTION: SPG_RBSYS_TPSWTimeout_C0_Root | |(); */
  /*PROC_EP: SPG_RBSYS_TPSWTimeout */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_TPSW_TASK(task_SPG_RBSYS_TPSWEXCMAE)
{
  /*ROOT_SECTION: SPG_RBSYS_TPSWEXCMAE_Root | |(); */
  /*PROC_EP: SPG_RBSYS_TPSWEXCMAE */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_TPSW_TASK(task_SPG_RBSYS_TPSWEXCFPP)
{
  /*ROOT_SECTION: SPG_RBSYS_TPSWEXCFPP_Root | |(); */
  /*PROC_EP: SPG_RBSYS_TPSWEXCFPP */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_TPSW_TASK(task_SPG_RBSYS_TPSWEXCRIE)
{
  /*ROOT_SECTION: SPG_RBSYS_TPSWEXCRIE_Root | |(); */
  /*PROC_EP: SPG_RBSYS_TPSWEXCRIE */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRSWINT0)
{
  /*ROOT_SECTION: SPG_ISRSWINT0_Root |RBA_RUNTIME_MSR_PROC(|); */
  /*PROC_EP: SPG_ISRSWINT0 */
  /*ROOT_SECTION_END: */
}

// #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
SIM_KILLED_ISR(isr_SPG_ISRMTTCANI0)
{
  /*ROOT_SECTION: SPG_ISRMTTCANI0_Root |RBA_RUNTIME_MSR_PROC(|); */
  /*PROC_EP: SPG_ISRMTTCANI0 */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRMCAN0I0)
{
  /*ROOT_SECTION: SPG_ISRMCAN0I0_Root |RBA_RUNTIME_MSR_PROC(|); */
  /*PROC_EP: SPG_ISRMCAN0I0 */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRMCAN1I0)
{
  /*ROOT_SECTION: SPG_ISRMCAN1I0_Root |RBA_RUNTIME_MSR_PROC(|); */
  /*PROC_EP: SPG_ISRMCAN1I0 */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRMCAN2I0)
{
  /*ROOT_SECTION: SPG_ISRMCAN2I0_Root |RBA_RUNTIME_MSR_PROC(|); */
  /*PROC_EP: SPG_ISRMCAN2I0 */
  /*ROOT_SECTION_END: */
}

// newly added with U2A.
SIM_KILLED_ISR(ISRCAN0TRX)
{
  /*ROOT_SECTION: SPG_ISRCAN0TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN0TRX */
  /*ROOT_SECTION_END: */
}
SIM_KILLED_ISR(ISRCAN1TRX)
{
  /*ROOT_SECTION: SPG_ISRCAN1TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN1TRX */
  /*ROOT_SECTION_END: */
}
SIM_KILLED_ISR(ISRCAN2TRX)
{
  /*ROOT_SECTION: SPG_ISRCAN2TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN2TRX */
  /*ROOT_SECTION_END: */
}
SIM_KILLED_ISR(ISRCAN3TRX)
{
  /*ROOT_SECTION: SPG_ISRCAN3TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN3TRX */
  /*ROOT_SECTION_END: */
}
SIM_KILLED_ISR(ISRCAN4TRX)
{
  /*ROOT_SECTION: SPG_ISRCAN4TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN4TRX */
  /*ROOT_SECTION_END: */
}
SIM_KILLED_ISR(ISRCAN5TRX)
{
  /*ROOT_SECTION: SPG_ISRCAN5TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN5TRX */
  /*ROOT_SECTION_END: */
}
SIM_KILLED_ISR(ISRCAN6TRX)
{
  /*ROOT_SECTION: SPG_ISRCAN6TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN6TRX */
  /*ROOT_SECTION_END: */
}
SIM_KILLED_ISR(ISRCAN8TRX)
{
  /*ROOT_SECTION: SPG_ISRCAN8TRX_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN8TRX */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRCAN0REC)
{
  /*ROOT_SECTION: SPG_ISRCAN0REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN0REC */
  /*ROOT_SECTION_END: */
}


SIM_KILLED_ISR(isr_SPG_ISRCAN1REC)
{
  /*ROOT_SECTION: SPG_ISRCAN1REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN1REC */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRCAN2REC)
{
  /*ROOT_SECTION: SPG_ISRCAN2REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN2REC */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRCAN3REC)
{
  /*ROOT_SECTION: SPG_ISRCAN3REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN3REC */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRCAN4REC)
{
  /*ROOT_SECTION: SPG_ISRCAN4REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN4REC */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRCAN5REC)
{
  /*ROOT_SECTION: SPG_ISRCAN5REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN5REC */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRCAN6REC)
{
  /*ROOT_SECTION: SPG_ISRCAN6REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN6REC */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRCAN8REC)
{
  /*ROOT_SECTION: SPG_ISRCAN8REC_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRCAN8REC */
  /*ROOT_SECTION_END: */
}

// U2A end

SIM_KILLED_ISR(isr_SPG_ISRFLX0LINE0)
{
  /*ROOT_SECTION: SPG_ISRFLX0LINE0_Root |RBA_RUNTIME_MSR_PROC(|); */
  /*PROC_EP: SPG_ISRFLX0LINE0 */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRFLX1LINE0)
{
  /*ROOT_SECTION: SPG_ISRFLX1LINE0_Root |RBA_RUNTIME_MSR_PROC(|); */
  /*PROC_EP: SPG_ISRFLX1LINE0 */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRRLIN30RX)
{
  /*ROOT_SECTION: SPG_ISRRLIN30RX_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRRLIN30RX */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRRLIN30STATUS)
{
  /*ROOT_SECTION: SPG_ISRRLIN30STATUS_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRRLIN30STATUS */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRRLIN31RX)
{
  /*ROOT_SECTION: SPG_ISRRLIN31RX_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRRLIN31RX */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(isr_SPG_ISRRLIN31STATUS)
{
  /*ROOT_SECTION: SPG_ISRRLIN31STATUS_Root |RBA_RUNTIME_MSR_PROC(&|); */
  /*PROC_EP: SPG_ISRRLIN31STATUS */
  /*ROOT_SECTION_END: */
}



/// ********************* further lists for RBSYS ***************************

const RBHWBIST_PRC_PTR c_HWBistEval[] =
{
  /*ROOT_SECTION: SPG_HWBistEval_Root | &|, */
  /*PROC_EP: SPG_HWBistInitialEvalAndSWPatternTest */
  /*ROOT_SECTION_END: */
  (RBHWBIST_PRC_PTR)0
};

const PRC_PTR c_PreCinit[] =
{
  /*ROOT_SECTION: SPG_PreCInit_Root | &|, */
  /*PROC_EP: SPG_PreCInit */
  /*ROOT_SECTION_END: */
  NULL
};

static const PRC_PTR c_HostCycurHsmInit[] =
{
  /*ROOT_SECTION: SPG_HostCycurHsmInit_Root | &|, */
  /*PROC_EP: SPG_HostCycurHsmInit */
  /*ROOT_SECTION_END: */
  NULL
};

const PRC_PTR c_PreReprogCheck[] =
{
  /*ROOT_SECTION: SPG_PreReprogCheck_Root | &|, */
  /*PROC_EP: SPG_PreReprogCheck */
  /*ROOT_SECTION_END: */
  NULL
};

const PRC_PTR c_PrePlantCheck[] =
{
  /*ROOT_SECTION: SPG_PrePlantCheck_Root | &|, */
  /*PROC_EP: SPG_PrePlantCheck */
  /*ROOT_SECTION_END: */
  NULL
};

OSSim_ProcessMeasurePoint c_PrePlantCheck_pmp[] =
{
  /*ROOT_SECTION: SPG_PrePlantCheck_Root |  OSSIM_PROC_MEAS_POINT_INIT(|), */
  /*PROC_EP: SPG_PrePlantCheck */
  /*ROOT_SECTION_END: */
  OSSIM_PROC_MEAS_POINT_LIST_END
};

#if(RBFS_ReprogDriverSupport == RBFS_ReprogDriverSupport_ON)
  const PRC_PTR c_PreReprogSession[] =
  {
    /*ROOT_SECTION: SPG_PreReprogSession_Root | &|, */
    /*PROC_EP: SPG_PreReprogSession */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

/* Vx1000PreReprogSession is normally part of RBSYS_FSWStartup.c
   has to be killed here because proc section is part of general
   APPLIF proc file */
const PRC_PTR SIM_KILLED_SECTION_Vx1000PreReprogSession[] =
{
  /*ROOT_SECTION: SPG_Vx1000PreReprogSession_Root | &|, */
  /*PROC_EP: SPG_Vx1000PreReprogSession */
  /*ROOT_SECTION_END: */
  NULL
};

/* Vx1000ParHandlingSession is normally part of RBSYS_FSWStartup.c
   has to be killed here because proc section is part of general
   APPLIF proc file */
const PRC_PTR SIM_KILLED_SECTION_Vx1000ParHandlingSession[] =
{
  /*ROOT_SECTION: SPG_Vx1000ParHandlingSession_Root | &|, */
  /*PROC_EP: SPG_Vx1000ParHandlingSession */
  /*ROOT_SECTION_END: */
  NULL
};

const PRC_PTR c_PreSafetyAlwaysExecute[] =
{
  /*ROOT_SECTION: SPG_RBSYS_PreSafetyAlwaysExecute_Root | &|, */
  /*PROC_EP: SPG_RBSYS_PreSafetyAlwaysExecute */
  /*ROOT_SECTION_END: */
  NULL
};

const PRC_PTR c_PreSafety[] =
{
  /*ROOT_SECTION: SPG_PreSafety_Root | &|, */
  /*PROC_EP: SPG_PreSafety */
  /*ROOT_SECTION_END: */
  NULL
};

const PRC_PTR c_SafetyC0[] =
{
  /*ROOT_SECTION: SPG_SafetyC0_Root | &|, */
  /*PROC_EP: SPG_SafetyC0 */
  /*ROOT_SECTION_END: */
  NULL
};

#if (RBFS_MCORE == RBFS_MCORE_ON)
  const PRC_PTR c_SafetyC1[] =
  {
    /*ROOT_SECTION: SPG_SafetyC1_Root | &|, */
    /*PROC_EP: SPG_SafetyC1 */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

const PRC_PTR c_PreOSStart[] =
{
  /*ROOT_SECTION: SPG_PreOSStart_Root | &|, */
  /*PROC_EP: SPG_PreOSStart */
  /*ROOT_SECTION_END: */
  NULL
};

#if (RBFS_MCORE == RBFS_MCORE_ON)
  const PRC_PTR c_PreOSStartC1[] =
  {
    /*ROOT_SECTION: SPG_PreOSStartC1_Root | &|, */
    /*PROC_EP: SPG_PreOSStartC1 */
    /*ROOT_SECTION_END: */
    NULL
  };
#endif

SIM_KILLED_ISR(STUB_Cbk_TaskStart)
{
  /*ROOT_SECTION: SPG_T1_TaskStart_Root | |(); */
  /*PROC_EP: SPG_T1_TaskStart */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(STUB_Cbk_TaskEnd)
{
  /*ROOT_SECTION: SPG_T1_TaskEnd_Root | |(); */
  /*PROC_EP: SPG_T1_TaskEnd */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(STUB_Cbk_ISRStart)
{
  /*ROOT_SECTION: SPG_T1_IsrStart_Root | |(); */
  /*PROC_EP: SPG_T1_IsrStart */
  /*ROOT_SECTION_END: */
}

SIM_KILLED_ISR(STUB_Cbk_ISREnd)
{
  /*ROOT_SECTION: SPG_T1_IsrEnd_Root | |(); */
  /*PROC_EP: SPG_T1_IsrEnd */
  /*ROOT_SECTION_END: */
}


#define CAT1_ISR(func)  void func(void);void func(void)
///< prototype trick: to avoid warning for currently unused functions.
///< I keep them 1. for MergeProc and 2. for potential to use later.


/* OS Category 1 ISR for "hypervisor trap (HVTRAP)" */
CAT1_ISR(EXCHVTRAP)
{
  /*ROOT_SECTION: SPG_RBSYS_EXCHVTRAP_Root | |(); */
  /*PROC_EP: SPG_RBSYS_EXCHVTRAP */
  /*ROOT_SECTION_END: */
}


/* OS Category 1 ISR for "FE-level software exception" */
CAT1_ISR(EXCFETRAP)
{
  /*ROOT_SECTION: SPG_RBSYS_EXCFETRAP_Root | |(); */
  /*PROC_EP: SPG_RBSYS_EXCFETRAP */
  /*ROOT_SECTION_END: */
}


/* OS Category 1 ISR for "reserved instruction exception" */
CAT1_ISR(EXCRIE)
{
  /*ROOT_SECTION: SPG_RBSYS_EXCRIE_Root | |(); */
  /*PROC_EP: SPG_RBSYS_EXCRIE */
  /*ROOT_SECTION_END: */
}


/* OS Category 1 ISR for "FPU exception" */
CAT1_ISR(EXCFPP)
{
  /*ROOT_SECTION: SPG_RBSYS_EXCFPP_Root | |(); */
  /*PROC_EP: SPG_RBSYS_EXCFPP */
  /*ROOT_SECTION_END: */
}


/* OS Category 1 ISR for "co-processor unusable exception" */
CAT1_ISR(EXCUCPOP)
{
  /*ROOT_SECTION: SPG_RBSYS_EXCUCPOP_Root | |(); */
  /*PROC_EP: SPG_RBSYS_EXCUCPOP */
  /*ROOT_SECTION_END: */
}


/* OS Category 1 ISR for "misalign exception" */
CAT1_ISR(EXCMAE)
{
  /*ROOT_SECTION: SPG_RBSYS_EXCMAE_Root | |(); */
  /*PROC_EP: SPG_RBSYS_EXCMAE */
  /*ROOT_SECTION_END: */
}


/* OS Category 1 ISR for "FE-level non maskable interrupt" */
CAT1_ISR(EXCFENMI)
{
  /*ROOT_SECTION: SPG_RBSYS_EXCFENMI_Root | |(); */
  /*PROC_EP: SPG_RBSYS_EXCFENMI */
  /*ROOT_SECTION_END: */
}


/* OS Category 1 ISR for "Privileged instruction exception" */
CAT1_ISR(EXCPIE)
{
    /*ROOT_SECTION: SPG_RBSYS_EXCPIE_Root | |(); */
    /*PROC_EP: SPG_RBSYS_EXCPIE */
    /*ROOT_SECTION_END: */
}


/* OS Category 1 ISR for "Memory protection exception" */
CAT1_ISR(EXCMDP)
{
    /*ROOT_SECTION: SPG_RBSYS_EXCMDP_Root | |(); */
    /*PROC_EP: SPG_RBSYS_EXCMDP */
    /*ROOT_SECTION_END: */
}


/* raw exception handler, called via RBSYS_ExceptionHander.c */
SIM_KILLED_ISR(RBSYS_EXCSYSERR_IMPL)
{
  /*ROOT_SECTION: SPG_RBSYS_EXCSYSERR_Root | |(); */
  /*PROC_EP: SPG_RBSYS_EXCSYSERR */
  /*ROOT_SECTION_END: */
}


/* raw exception handler, called via RBSYS_ExceptionHander.c */
SIM_KILLED_ISR(RBSYS_EXCFEINT_IMPL)
{
  /*ROOT_SECTION: SPG_RBSYS_EXCFEINT_Root | |(); */
  /*PROC_EP: SPG_RBSYS_EXCFEINT */
  /*ROOT_SECTION_END: */
}

/* raw exception handler, called via RBSYS_ExceptionHander.c
 * (but only called if Gliwa T1.flex is not integrated) */
SIM_KILLED_ISR(RBSYS_EXCDEBUG_IMPL)
{
  /*ROOT_SECTION: SPG_RBSYS_EXCDEBUG_Root | |(); */
  /*PROC_EP: SPG_RBSYS_EXCDEBUG */
  /*ROOT_SECTION_END: */

  /*ROOT_SECTION: SPG_T1_EXCDEBUG_ROOT | __asm("jr _| "); */
  /*PROC_EP: SPG_T1_EXCDEBUG */
  /*ROOT_SECTION_END: */
}

#if( RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON )
  void RBSYS_ActivateFlexrayTask(void)
  {
      ActivateTask(TaskFlexray);
  }
#endif

/** @} */
/* End ingroup RBSYS */
