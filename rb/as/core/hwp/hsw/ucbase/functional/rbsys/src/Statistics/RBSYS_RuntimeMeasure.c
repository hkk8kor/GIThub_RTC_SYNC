/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief This module is responsible to integrate rba_Runtime within RBSYS.
 *
 * The rba_Runtime (provided by CUBAS\EbOS) uses the timing monitoring features of RTA-OS.
 * To detect all preemptions (start and end), it's necessary to have hooks called
 * from the OS when Tasks, cross core interrupts and CAT2 interrupts occur.
 * CAT1 interrupts are not considered at all.
 *
 * In addition to the OS hooks rba_Runtime functions (PreOsInit, Init and MainFunction)
 * must be called from RBSYS.
 *
 * To get also the Task and ISR runtime values on MM6 measurement technique the rba_Runtime
 * structures are mapped here to MM6 measurement comments.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* realized interfaces */
#include "RBSYS_RuntimeMeasure.h"
#include "RBSYS_TaskInfo.h"
#include "RBSYS_Subsystem.h"


/* used interfaces */
#include "rba_Runtime.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_ON,
                          RBFS_MCORE_OFF);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSchemeExtension,
                          RBFS_TaskSchemeExtension_None,
                          RBFS_TaskSchemeExtension_VMPS,
                          RBFS_TaskSchemeExtension_HostCore0GuestCore1,
                          RBFS_TaskSchemeExtension_AB15);


/**
 * @brief This rba_Runtime initialization function must be called before the OS start. It must be called on each core
 *
 * @return void
 */
void RBSYS_PRC_RuntimeMeasure_PreOSInit(void)
{
  rba_Runtime_PreOSInit();
}


/**
 * @brief This rba_Runtime function must be called in an initialization task (after StartOS() call). It must be only called on one core.
 *
 * @return void
 */
void RBSYS_PRC_RuntimeMeasure_Init(void)
{
  rba_Runtime_Init();
  rba_Runtime_MonSystemLoadInit();          // skip first "undefined" SystemLoad measurement event
}


/**
 * @brief This function must be called in a cyclic task after the rba_Runtime initialization.
 *
 * Take care that the cyclic task rba_Runtime is running must fit to the configuration within RBSYS_RuntimeMeasure_Cfg.h
 * It can be called from any core.
 *
 * @return void
 */
void RBSYS_PRC_RuntimeMeasure_MainFunction(void)
{
  rba_Runtime_MainFunction();
}




/* formula for MM6 measurement of system load: 0x10000 is 100% = 65536[Bit] */
#define NF_RUNTIMESYSLOAD    (65536.0)


/* ********** MM6 labels for rba_runtime task/isr measurement *********** */

// todo: adapt corresponding index

/**
 * System load:
 * The load of each core is acquired on every end of the configured time frame. The results are written into the array
 * <rba_Runtime_MonSystemLoadPer64k_au16>. The index is the logical (OS) core ID, the value is the average load in the
 * elapsed time frame (65536 stands for 100%).
 */

uint16 RBSYS_getSystemLoadCore0(void)
{
  return rba_Runtime_MonSystemLoadPer64k_au16[0];
}

/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonSystemLoadPer64k_au16[0]*/
/*COMMENT=rba_Runtime_MonSystemLoadPer64k_au16[0]*/
/*MTEVENT=c_MT_Default_Task_x1*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonSystemLoadPer64k_au16[0]*/
/*MODEL_NAME=rba_Runtime_SystemLoadCore0Percent*/
/*COMMENT=rba_Runtime_SystemLoadCore0Percent*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_x1*/
/*]]MEASUREMENT*/


#if (RBFS_MCORE == RBFS_MCORE_ON)
  uint16 RBSYS_getSystemLoadCore1(void)
  {
    return rba_Runtime_MonSystemLoadPer64k_au16[1];
  }

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonSystemLoadPer64k_au16[1]*/
  /*COMMENT=rba_Runtime_MonSystemLoadPer64k_au16*/
  /*MTEVENT=c_MT_Default_Task_x1*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonSystemLoadPer64k_au16[1]*/
  /*MODEL_NAME=rba_Runtime_SystemLoadCore1Percent*/
  /*COMMENT=Task1msCnt*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_x1*/
  /*]]MEASUREMENT*/
#endif




/** Hint:
 *    The rba_Runtime_MonTask_ast array is filled according the given order in RBSYS_RBA_RUNTIME_MON_TASK_LIST.
 *    The rba_Runtime_MonIsr_ast array is filled according the given order in RBSYS_RBA_RUNTIME_MON_ISR_LIST.
 *
 * The measurement variables are updated after a task/ISR ends execution and contain the followings:
 *  - ctCallsTotal_u32: The number of calls since last reset of the ECU.
 *  - tiMinRT_u32, tiMaxRT_u32: The minimal/maximal net runtime of the task/ISR since last reset of the ECU.
 *  - tiCurRT_u32: The net runtime from the last cycle of the task/ISR.
 *  - tiMinResponseT_u32, tiMaxResponseT_u32: The minimal/maximal response time of the task since last reset of the ECU.
 *  - tiCurResponseT_u32: The response time from the last cycle of the task.
 *  - dataMaxRTCallRef_u32: Task counter reference for max runtime value.
 *  Hint: Response time is the time from activation of the task until the task comes to an end. The response time for ISRs cannot be acquired.
 *
 * If the generation of statistical values is turned on the following values are available in addition and are generated after the task/ISR
 * and the current time frame ends:
 *  - loadPer64k_u16: The load caused by the task or ISR (65536 stands for 100%) in the last elapsed time frame.
 *  - tiAvrgRT_u32: The average net runtime of the task or ISR in the last elapsed time frame.
 */

/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[0].tiCurRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx24.tiCurRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[0].tiCurRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[0].tiMinRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx24.tiMinRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[0].tiMinRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[0].tiMaxRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx24.tiMaxRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[0].tiMaxRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[0].ctCallsTotal_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx24.ctCallsTotal_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[0].ctCallsTotal_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[0].tiAvrgRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx24.tiAvrgRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[0].tiAvrgRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[0].loadPer64k_u16 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx24.loadPer64k_u16*/
/*COMMENT=rba_Runtime_MonTask_ast[0].loadPer64k_u16*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[0].dataMaxRTCallRef_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx24.dataMaxRTCallRef_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[0].dataMaxRTCallRef_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[1].tiCurRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx8.tiCurRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[1].tiCurRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[1].tiMinRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx8.tiMinRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[1].tiMinRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[1].tiMaxRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx8.tiMaxRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[1].tiMaxRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[1].ctCallsTotal_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx8.ctCallsTotal_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[1].ctCallsTotal_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[1].tiAvrgRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx8.tiAvrgRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[1].tiAvrgRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[1].loadPer64k_u16 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx8.loadPer64k_u16*/
/*COMMENT=rba_Runtime_MonTask_ast[1].loadPer64k_u16*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[1].dataMaxRTCallRef_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx8.dataMaxRTCallRef_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[1].dataMaxRTCallRef_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[2].tiCurRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4.tiCurRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[2].tiCurRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[2].tiMinRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4.tiMinRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[2].tiMinRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[2].tiMaxRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4.tiMaxRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[2].tiMaxRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[2].ctCallsTotal_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4.ctCallsTotal_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[2].ctCallsTotal_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[2].tiAvrgRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4.tiAvrgRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[2].tiAvrgRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[2].loadPer64k_u16 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4.loadPer64k_u16*/
/*COMMENT=rba_Runtime_MonTask_ast[2].loadPer64k_u16*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[2].dataMaxRTCallRef_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4.dataMaxRTCallRef_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[2].dataMaxRTCallRef_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/



/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[3].tiCurRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2.tiCurRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[3].tiCurRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[3].tiMinRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2.tiMinRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[3].tiMinRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[3].tiMaxRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2.tiMaxRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[3].tiMaxRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[3].ctCallsTotal_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2.ctCallsTotal_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[3].ctCallsTotal_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[3].tiAvrgRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2.tiAvrgRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[3].tiAvrgRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[3].loadPer64k_u16 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2.loadPer64k_u16*/
/*COMMENT=rba_Runtime_MonTask_ast[3].loadPer64k_u16*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[3].dataMaxRTCallRef_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2.dataMaxRTCallRef_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[3].dataMaxRTCallRef_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/



/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[4].tiCurRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Low.tiCurRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[4].tiCurRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[4].tiMinRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Low.tiMinRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[4].tiMinRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[4].tiMaxRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Low.tiMaxRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[4].tiMaxRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[4].ctCallsTotal_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Low.ctCallsTotal_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[4].ctCallsTotal_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[4].tiAvrgRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Low.tiAvrgRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[4].tiAvrgRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[4].loadPer64k_u16 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Low.loadPer64k_u16*/
/*COMMENT=rba_Runtime_MonTask_ast[4].loadPer64k_u16*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[4].dataMaxRTCallRef_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Low.dataMaxRTCallRef_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[4].dataMaxRTCallRef_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/



/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[5].tiCurRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskFlexray.tiCurRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[5].tiCurRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[5].tiMinRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskFlexray.tiMinRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[5].tiMinRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[5].tiMaxRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskFlexray.tiMaxRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[5].tiMaxRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[5].ctCallsTotal_u32 */
/*MODEL_NAME=rba_Runtime_TaskFlexray.ctCallsTotal_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[5].ctCallsTotal_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[5].tiAvrgRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskFlexray.tiAvrgRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[5].tiAvrgRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[5].loadPer64k_u16 */
/*MODEL_NAME=rba_Runtime_TaskFlexray.loadPer64k_u16*/
/*COMMENT=rba_Runtime_MonTask_ast[5].loadPer64k_u16*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[5].dataMaxRTCallRef_u32 */
/*MODEL_NAME=rba_Runtime_TaskFlexray.dataMaxRTCallRef_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[5].dataMaxRTCallRef_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/



/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[6].tiCurRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1High.tiCurRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[6].tiCurRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[6].tiMinRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1High.tiMinRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[6].tiMinRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[6].tiMaxRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1High.tiMaxRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[6].tiMaxRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[6].ctCallsTotal_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1High.ctCallsTotal_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[6].ctCallsTotal_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[6].tiAvrgRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1High.tiAvrgRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[6].tiAvrgRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[6].loadPer64k_u16 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1High.loadPer64k_u16*/
/*COMMENT=rba_Runtime_MonTask_ast[6].loadPer64k_u16*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[6].dataMaxRTCallRef_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1High.dataMaxRTCallRef_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[6].dataMaxRTCallRef_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/



/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[7].tiCurRT_u32 */
/*MODEL_NAME=rba_Runtime_Task1ms.tiCurRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[7].tiCurRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[7].tiMinRT_u32 */
/*MODEL_NAME=rba_Runtime_Task1ms.tiMinRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[7].tiMinRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[7].tiMaxRT_u32 */
/*MODEL_NAME=rba_Runtime_Task1ms.tiMaxRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[7].tiMaxRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[7].ctCallsTotal_u32 */
/*MODEL_NAME=rba_Runtime_Task1ms.ctCallsTotal_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[7].ctCallsTotal_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[7].tiAvrgRT_u32 */
/*MODEL_NAME=rba_Runtime_Task1ms.tiAvrgRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[7].tiAvrgRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[7].loadPer64k_u16 */
/*MODEL_NAME=rba_Runtime_Task1ms.loadPer64k_u16*/
/*COMMENT=rba_Runtime_MonTask_ast[7].loadPer64k_u16*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[7].dataMaxRTCallRef_u32 */
/*MODEL_NAME=rba_Runtime_Task1ms.dataMaxRTCallRef_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[7].dataMaxRTCallRef_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/



/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[8].tiCurRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskInit.tiCurRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[8].tiCurRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[8].tiMinRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskInit.tiMinRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[8].tiMinRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[8].tiMaxRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskInit.tiMaxRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[8].tiMaxRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[8].ctCallsTotal_u32 */
/*MODEL_NAME=rba_Runtime_TaskInit.ctCallsTotal_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[8].ctCallsTotal_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[8].tiAvrgRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskInit.tiAvrgRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[8].tiAvrgRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[8].loadPer64k_u16 */
/*MODEL_NAME=rba_Runtime_TaskInit.loadPer64k_u16*/
/*COMMENT=rba_Runtime_MonTask_ast[8].loadPer64k_u16*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[8].dataMaxRTCallRef_u32 */
/*MODEL_NAME=rba_Runtime_TaskInit.dataMaxRTCallRef_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[8].dataMaxRTCallRef_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/



/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[9].tiCurRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskInitP.tiCurRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[9].tiCurRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[9].tiMinRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskInitP.tiMinRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[9].tiMinRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[9].tiMaxRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskInitP.tiMaxRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[9].tiMaxRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[9].ctCallsTotal_u32 */
/*MODEL_NAME=rba_Runtime_TaskInitP.ctCallsTotal_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[9].ctCallsTotal_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[9].tiAvrgRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskInitP.tiAvrgRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[9].tiAvrgRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[9].loadPer64k_u16 */
/*MODEL_NAME=rba_Runtime_TaskInitP.loadPer64k_u16*/
/*COMMENT=rba_Runtime_MonTask_ast[9].loadPer64k_u16*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[9].dataMaxRTCallRef_u32 */
/*MODEL_NAME=rba_Runtime_TaskInitP.dataMaxRTCallRef_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[9].dataMaxRTCallRef_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/



/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[10].tiCurRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2p.tiCurRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[10].tiCurRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[10].tiMinRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2p.tiMinRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[10].tiMinRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[10].tiMaxRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2p.tiMaxRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[10].tiMaxRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[10].ctCallsTotal_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2p.ctCallsTotal_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[10].ctCallsTotal_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[10].tiAvrgRT_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2p.tiAvrgRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[10].tiAvrgRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[10].loadPer64k_u16 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2p.loadPer64k_u16*/
/*COMMENT=rba_Runtime_MonTask_ast[10].loadPer64k_u16*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[10].dataMaxRTCallRef_u32 */
/*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2p.dataMaxRTCallRef_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[10].dataMaxRTCallRef_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/



/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[11].tiCurRT_u32 */
/*MODEL_NAME=rba_Runtime_Task0p5ms.tiCurRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[11].tiCurRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[11].tiMinRT_u32 */
/*MODEL_NAME=rba_Runtime_Task0p5ms.tiMinRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[11].tiMinRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[11].tiMaxRT_u32 */
/*MODEL_NAME=rba_Runtime_Task0p5ms.tiMaxRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[11].tiMaxRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[11].ctCallsTotal_u32 */
/*MODEL_NAME=rba_Runtime_Task0p5ms.ctCallsTotal_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[11].ctCallsTotal_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[11].tiAvrgRT_u32 */
/*MODEL_NAME=rba_Runtime_Task0p5ms.tiAvrgRT_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[11].tiAvrgRT_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[11].loadPer64k_u16 */
/*MODEL_NAME=rba_Runtime_Task0p5ms.loadPer64k_u16*/
/*COMMENT=rba_Runtime_MonTask_ast[11].loadPer64k_u16*/
/*FORMULA=NF_RUNTIMESYSLOAD*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rba_Runtime_MonTask_ast[11].dataMaxRTCallRef_u32 */
/*MODEL_NAME=rba_Runtime_Task0p5ms.dataMaxRTCallRef_u32*/
/*COMMENT=rba_Runtime_MonTask_ast[11].dataMaxRTCallRef_u32*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4pLow.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4pLow.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4pLow.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4pLow.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4pLow.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4pLow.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].dataMaxRTCallRef_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4pLow.dataMaxRTCallRef_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].dataMaxRTCallRef_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx200Background.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx200Background.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx200Background.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx200Background.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx200Background.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx200Background.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].dataMaxRTCallRef_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx200Background.dataMaxRTCallRef_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].dataMaxRTCallRef_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio1.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio1.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio1.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio1.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio1.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio1.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].dataMaxRTCallRef_u32 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio1.dataMaxRTCallRef_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].dataMaxRTCallRef_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio2.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio2.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio2.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio2.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio2.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio2.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].dataMaxRTCallRef_u32 */
  /*MODEL_NAME=rba_Runtime_TaskEventCtrlExtPrio2.dataMaxRTCallRef_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].dataMaxRTCallRef_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/

#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Guest.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Guest.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Guest.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Guest.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Guest.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Guest.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].dataMaxRTCallRef_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx1Guest.dataMaxRTCallRef_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].dataMaxRTCallRef_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2Guest.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2Guest.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2Guest.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2Guest.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2Guest.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2Guest.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].dataMaxRTCallRef_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx2Guest.dataMaxRTCallRef_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].dataMaxRTCallRef_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4Guest.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4Guest.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4Guest.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4Guest.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4Guest.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4Guest.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[14].dataMaxRTCallRef_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx4Guest.dataMaxRTCallRef_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[14].dataMaxRTCallRef_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10Guest.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10Guest.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10Guest.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10Guest.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10Guest.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10Guest.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[15].dataMaxRTCallRef_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10Guest.dataMaxRTCallRef_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[15].dataMaxRTCallRef_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[16].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20Guest.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[16].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[16].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20Guest.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[16].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[16].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20Guest.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[16].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[16].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20Guest.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[16].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[16].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20Guest.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[16].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[16].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20Guest.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonTask_ast[16].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[16].dataMaxRTCallRef_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20Guest.dataMaxRTCallRef_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[16].dataMaxRTCallRef_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/

#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[12].dataMaxRTCallRef_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx10.dataMaxRTCallRef_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[12].dataMaxRTCallRef_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonTask_ast[13].dataMaxRTCallRef_u32 */
  /*MODEL_NAME=rba_Runtime_TaskBaseCtrlCycx20.dataMaxRTCallRef_u32*/
  /*COMMENT=rba_Runtime_MonTask_ast[13].dataMaxRTCallRef_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/

#endif



#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMTTCANI0.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMTTCANI0.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMTTCANI0.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMTTCANI0.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMTTCANI0.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRMTTCANI0.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/


  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN0I0.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN0I0.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN0I0.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN0I0.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN0I0.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN0I0.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/


  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[2].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN1I0.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[2].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[2].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN1I0.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[2].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[2].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN1I0.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[2].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[2].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN1I0.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[2].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[2].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN1I0.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[2].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[2].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN1I0.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[2].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[3].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN2I0.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[3].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[3].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN2I0.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[3].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[3].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN2I0.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[3].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[3].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN2I0.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[3].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[3].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN2I0.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[3].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[3].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRMCAN2I0.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[3].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/




  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[4].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX0LINE0.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[4].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[4].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX0LINE0.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[4].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[4].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX0LINE0.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[4].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[4].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX0LINE0.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[4].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[4].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX0LINE0.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[4].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[4].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRFLX0LINE0.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[4].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/


  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[5].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX1LINE0.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[5].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[5].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX1LINE0.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[5].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[5].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX1LINE0.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[5].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[5].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX1LINE0.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[5].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[5].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX1LINE0.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[5].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[5].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRFLX1LINE0.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[5].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[6].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[6].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[6].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[6].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[6].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[6].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[6].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[6].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[6].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[6].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[6].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[6].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[7].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[7].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[7].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[7].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[7].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[7].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[7].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[7].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[7].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[7].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[7].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[7].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[8].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSWINT0.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[8].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[8].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSWINT0.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[8].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[8].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSWINT0.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[8].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[8].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSWINT0.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[8].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[8].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSWINT0.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[8].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[8].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRSWINT0.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[8].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[9].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN30RX.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[9].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[9].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN30RX.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[9].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[9].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN30RX.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[9].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[9].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN30RX.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[9].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[9].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN30RX.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[9].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[9].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN30RX.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[9].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[10].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN30STATUS.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[10].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[10].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN30STATUS.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[10].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[10].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN30STATUS.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[10].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[10].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN30STATUS.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[10].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[10].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN30STATUS.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[10].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[10].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN30STATUS.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[10].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[11].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN31RX.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[11].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[11].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN31RX.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[11].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[11].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN31RX.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[11].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[11].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN31RX.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[11].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[11].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN31RX.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[11].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[11].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN31RX.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[11].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[12].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN31STATUS.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[12].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[12].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN31STATUS.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[12].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[12].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN31STATUS.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[12].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[12].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN31STATUS.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[12].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[12].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN31STATUS.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[12].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[12].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRRLIN31STATUS.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[12].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
    /*[[MEASUREMENT*/
    /*NAME=rba_Runtime_MonIsr_ast[13].tiCurRT_u32 */
    /*MODEL_NAME=rba_Runtime_ISR0p5ms.tiCurRT_u32*/
    /*COMMENT=rba_Runtime_MonIsr_ast[13].tiCurRT_u32*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/
    /*[[MEASUREMENT*/
    /*NAME=rba_Runtime_MonIsr_ast[13].tiMinRT_u32 */
    /*MODEL_NAME=rba_Runtime_ISR0p5ms.tiMinRT_u32*/
    /*COMMENT=rba_Runtime_MonIsr_ast[13].tiMinRT_u32*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/
    /*[[MEASUREMENT*/
    /*NAME=rba_Runtime_MonIsr_ast[13].tiMaxRT_u32 */
    /*MODEL_NAME=rba_Runtime_ISR0p5ms.tiMaxRT_u32*/
    /*COMMENT=rba_Runtime_MonIsr_ast[13].tiMaxRT_u32*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/
    /*[[MEASUREMENT*/
    /*NAME=rba_Runtime_MonIsr_ast[13].ctCallsTotal_u32 */
    /*MODEL_NAME=rba_Runtime_ISR0p5ms.ctCallsTotal_u32*/
    /*COMMENT=rba_Runtime_MonIsr_ast[13].ctCallsTotal_u32*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/
    /*[[MEASUREMENT*/
    /*NAME=rba_Runtime_MonIsr_ast[13].tiAvrgRT_u32 */
    /*MODEL_NAME=rba_Runtime_ISR0p5ms.tiAvrgRT_u32*/
    /*COMMENT=rba_Runtime_MonIsr_ast[13].tiAvrgRT_u32*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/
    /*[[MEASUREMENT*/
    /*NAME=rba_Runtime_MonIsr_ast[13].loadPer64k_u16 */
    /*MODEL_NAME=rba_Runtime_ISR0p5ms.loadPer64k_u16*/
    /*COMMENT=rba_Runtime_MonIsr_ast[13].loadPer64k_u16*/
    /*FORMULA=NF_RUNTIMESYSLOAD*/
    /*MTEVENT=c_MT_Default_Task_1ms*/
    /*]]MEASUREMENT*/
  #endif

  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN0REC.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN0REC.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN0REC.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN0REC.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN0REC.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRCAN0REC.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN0TRX.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN0TRX.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN0TRX.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN0TRX.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN0TRX.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRCAN0TRX.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[2].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN1REC.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[2].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[2].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN1REC.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[2].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[2].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN1REC.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[2].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[2].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN1REC.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[2].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[2].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN1REC.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[2].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[2].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRCAN1REC.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[2].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[3].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN1TRX.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[3].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[3].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN1TRX.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[3].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[3].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN1TRX.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[3].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[3].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN1TRX.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[3].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[3].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN1TRX.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[3].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[3].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRCAN1TRX.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[3].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[4].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN2REC.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[4].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[4].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN2REC.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[4].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[4].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN2REC.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[4].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[4].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN2REC.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[4].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[4].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN2REC.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[4].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[4].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRCAN2REC.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[4].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[5].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN2TRX.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[5].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[5].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN2TRX.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[5].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[5].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN2TRX.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[5].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[5].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN2TRX.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[5].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[5].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN2TRX.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[5].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[5].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRCAN2TRX.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[5].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[6].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN6REC.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[6].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[6].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN6REC.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[6].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[6].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN6REC.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[6].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[6].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN6REC.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[6].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[6].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN6REC.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[6].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[6].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRCAN6REC.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[6].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[7].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN6TRX.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[7].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[7].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN6TRX.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[7].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[7].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN6TRX.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[7].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[7].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN6TRX.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[7].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[7].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN6TRX.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[7].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[7].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRCAN6TRX.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[7].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[8].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN8REC.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[8].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[8].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN8REC.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[8].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[8].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN8REC.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[8].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[8].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN8REC.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[8].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[8].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN8REC.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[8].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[8].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRCAN8REC.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[8].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[9].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN8TRX.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[9].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[9].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN8TRX.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[9].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[9].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN8TRX.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[9].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[9].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN8TRX.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[9].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[9].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRCAN8TRX.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[9].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[9].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRCAN8TRX.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[9].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[10].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX0LINE0.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[10].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[10].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX0LINE0.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[10].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[10].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX0LINE0.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[10].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[10].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX0LINE0.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[10].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[10].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX0LINE0.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[10].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[10].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRFLX0LINE0.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[10].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[11].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX1LINE0.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[11].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[11].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX1LINE0.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[11].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[11].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX1LINE0.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[11].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[11].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX1LINE0.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[11].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[11].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRFLX1LINE0.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[11].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[11].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRFLX1LINE0.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[11].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[12].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[12].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[12].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[12].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[12].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[12].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[12].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[12].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[12].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[12].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[12].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[12].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[13].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[13].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[13].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[13].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[13].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[13].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[13].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[13].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[13].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[13].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[13].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[13].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[14].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSWINT0.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[14].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[14].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSWINT0.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[14].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[14].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSWINT0.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[14].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[14].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSWINT0.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[14].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[14].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSWINT0.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[14].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[14].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRSWINT0.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[14].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/

#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
//todo: fill

#elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)

  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[0].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRSTM04.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[0].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].tiCurRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.tiCurRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].tiCurRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].tiMinRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.tiMinRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].tiMinRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].tiMaxRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.tiMaxRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].tiMaxRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].ctCallsTotal_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.ctCallsTotal_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].ctCallsTotal_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].tiAvrgRT_u32 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.tiAvrgRT_u32*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].tiAvrgRT_u32*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  /*[[MEASUREMENT*/
  /*NAME=rba_Runtime_MonIsr_ast[1].loadPer64k_u16 */
  /*MODEL_NAME=rba_Runtime_ISRSTM05.loadPer64k_u16*/
  /*COMMENT=rba_Runtime_MonIsr_ast[1].loadPer64k_u16*/
  /*FORMULA=NF_RUNTIMESYSLOAD*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/

#endif






/** @} */
/* End ingroup RBSYS */
