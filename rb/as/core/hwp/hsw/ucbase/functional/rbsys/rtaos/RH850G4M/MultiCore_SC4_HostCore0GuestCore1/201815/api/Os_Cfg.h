/*
 * This is Os_Cfg.h, auto-generated for:
 *   Project: rtaos_ccas_u2a_mcore_sc4
 *   Target:  RH850x2GHS
 *   Variant: U2A
 *   Version: 5.0.6
 *   [$UKS 650]
 */
#ifndef OS_CFG_H
#define OS_CFG_H
/*
 * Note that only documented OS APIs are considered to be public.
 * Functions and data in OS header files that are not documented should not be used in
 * non-OS code.
 */
#include "Os_Safe_Cfg.h"
/* -------- Time Monitoring --------- */
#define OS_TIME_MONITORING  /* [$UKS 959] */
/* -------- Time Recording --------- */
#define OS_ELAPSED_TIME_RECORDING
/* -------- Activation Monitoring --------- */
#define OS_ACTIVATION_MONITORING  /* [$UKS 1282] */

/* -------- AppMode declarations --------- */

/* ----- OS-Application declarations ----- */
#define TrustedAppCore0 ((ApplicationType)0U) /* [$UKS 412] */
#define TrustedAppCore1 ((ApplicationType)1U) /* [$UKS 412] */
#define UntrustedAppCore0 ((ApplicationType)2U) /* [$UKS 412] */
#define UntrustedAppCore1 ((ApplicationType)3U) /* [$UKS 412] */

/* ----- Trusted function declarations ----- */
#define UntrustedFuncCore0 ((TrustedFunctionIndexType)0U) /* [$UKS 969] */
#define UntrustedFuncCore1 ((TrustedFunctionIndexType)1U) /* [$UKS 969] */

/* ----- PeripheralArea declarations ----- */

/* ----- Spinlock declarations ----- */

/* -------- Event declarations --------- */

/* -------- Task declarations --------- */
#define TaskBaseCtrlCycx24 (&Os_const_tasks0[0])
#define OS_CORE_FOR_TaskBaseCtrlCycx24 (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx24 (0U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx24 (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx24 (0U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx24)
#define TaskBaseCtrlCycx20Guest (&Os_const_tasks1[0])
#define OS_CORE_FOR_TaskBaseCtrlCycx20Guest (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx20Guest (0U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx20Guest (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx20Guest (1U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx20Guest)
#define TaskBaseCtrlCycx10Guest (&Os_const_tasks1[1])
#define OS_CORE_FOR_TaskBaseCtrlCycx10Guest (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx10Guest (1U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx10Guest (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx10Guest (2U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx10Guest)
#define TaskBaseCtrlCycx8 (&Os_const_tasks0[1])
#define OS_CORE_FOR_TaskBaseCtrlCycx8 (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx8 (1U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx8 (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx8 (3U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx8)
#define TaskBaseCtrlCycx4Guest (&Os_const_tasks1[2])
#define OS_CORE_FOR_TaskBaseCtrlCycx4Guest (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx4Guest (2U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx4Guest (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx4Guest (4U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx4Guest)
#define TaskBaseCtrlCycx4 (&Os_const_tasks0[2])
#define OS_CORE_FOR_TaskBaseCtrlCycx4 (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx4 (2U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx4 (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx4 (5U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx4)
#define TaskBaseCtrlCycx2Guest (&Os_const_tasks1[3])
#define OS_CORE_FOR_TaskBaseCtrlCycx2Guest (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx2Guest (3U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx2Guest (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx2Guest (6U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx2Guest)
#define TaskBaseCtrlCycx2p (&Os_const_tasks1[4])
#define OS_CORE_FOR_TaskBaseCtrlCycx2p (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx2p (4U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx2p (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx2p (7U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx2p)
#define TaskBaseCtrlCycx2 (&Os_const_tasks0[3])
#define OS_CORE_FOR_TaskBaseCtrlCycx2 (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx2 (3U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx2 (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx2 (8U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx2)
#define TaskBaseCtrlCycx1Low (&Os_const_tasks0[4])
#define OS_CORE_FOR_TaskBaseCtrlCycx1Low (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx1Low (4U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx1Low (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx1Low (9U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx1Low)
#define TaskBaseCtrlCycx1Guest (&Os_const_tasks1[5])
#define OS_CORE_FOR_TaskBaseCtrlCycx1Guest (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx1Guest (5U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx1Guest (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx1Guest (10U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx1Guest)
#define TaskFlexray (&Os_const_tasks0[5])
#define OS_CORE_FOR_TaskFlexray (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskFlexray (5U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskFlexray (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskFlexray (11U) /* [$UKS 2185] */
DeclareTask(TaskFlexray)
#define TaskBaseCtrlCycx1High (&Os_const_tasks0[6])
#define OS_CORE_FOR_TaskBaseCtrlCycx1High (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx1High (6U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx1High (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx1High (12U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx1High)
#define Task1ms (&Os_const_tasks0[7])
#define OS_CORE_FOR_Task1ms (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_Task1ms (7U) /* [$UKS 2007] */
#define OS_IMASK_FOR_Task1ms (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_Task1ms (13U) /* [$UKS 2185] */
DeclareTask(Task1ms)
#define Task0p5ms (&Os_const_tasks0[8])
#define OS_CORE_FOR_Task0p5ms (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_Task0p5ms (8U) /* [$UKS 2007] */
#define OS_IMASK_FOR_Task0p5ms (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_Task0p5ms (14U) /* [$UKS 2185] */
DeclareTask(Task0p5ms)
#define TaskInitP (&Os_const_tasks1[6])
#define OS_CORE_FOR_TaskInitP (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskInitP (6U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskInitP (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskInitP (15U) /* [$UKS 2185] */
DeclareTask(TaskInitP)
#define TaskInit (&Os_const_tasks0[9])
#define OS_CORE_FOR_TaskInit (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskInit (9U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskInit (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskInit (16U) /* [$UKS 2185] */
DeclareTask(TaskInit)
#define TaskTPSWKillCore0 (&Os_const_tasks0[10])
#define OS_CORE_FOR_TaskTPSWKillCore0 (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskTPSWKillCore0 (10U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskTPSWKillCore0 (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskTPSWKillCore0 (17U) /* [$UKS 2185] */
DeclareTask(TaskTPSWKillCore0)
#define TaskTPSWKillCore1 (&Os_const_tasks1[7])
#define OS_CORE_FOR_TaskTPSWKillCore1 (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskTPSWKillCore1 (7U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskTPSWKillCore1 (16U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskTPSWKillCore1 (18U) /* [$UKS 2185] */
DeclareTask(TaskTPSWKillCore1)
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_TPL_FOR_TASK, OS_IMASK_FOR_TASK) */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, OS_TPL_FOR_TASK) */
#define OS_TPL_FOR_TASK(n) OS_TPL_FOR_##n  /* [$UKS 2008] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, OS_IMASK_FOR_TASK) */
#define OS_IMASK_FOR_TASK(n) OS_IMASK_FOR_##n  /* [$UKS 2010] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_CORE_FOR_TASK) */
#define OS_CORE_FOR_TASK(t) (t)->core_id /* [$UKS 1921] */

/* -------- ISR declarations --------- */
#define ISRCAN0REC (&Os_const_isrs[0U])
#define OS_IMASK_FOR_ISRCAN0REC (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRCAN0REC (0U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRCAN0REC (0U) /* [$UKS 1909] */
DeclareISR(ISRCAN0REC)
#define ISRCAN0TRX (&Os_const_isrs[1U])
#define OS_IMASK_FOR_ISRCAN0TRX (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRCAN0TRX (1U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRCAN0TRX (0U) /* [$UKS 1909] */
DeclareISR(ISRCAN0TRX)
#define ISRCAN1REC (&Os_const_isrs[2U])
#define OS_IMASK_FOR_ISRCAN1REC (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRCAN1REC (2U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRCAN1REC (0U) /* [$UKS 1909] */
DeclareISR(ISRCAN1REC)
#define ISRCAN1TRX (&Os_const_isrs[3U])
#define OS_IMASK_FOR_ISRCAN1TRX (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRCAN1TRX (3U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRCAN1TRX (0U) /* [$UKS 1909] */
DeclareISR(ISRCAN1TRX)
#define ISRCAN2REC (&Os_const_isrs[4U])
#define OS_IMASK_FOR_ISRCAN2REC (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRCAN2REC (4U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRCAN2REC (0U) /* [$UKS 1909] */
DeclareISR(ISRCAN2REC)
#define ISRCAN2TRX (&Os_const_isrs[5U])
#define OS_IMASK_FOR_ISRCAN2TRX (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRCAN2TRX (5U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRCAN2TRX (0U) /* [$UKS 1909] */
DeclareISR(ISRCAN2TRX)
#define ISRCAN6REC (&Os_const_isrs[6U])
#define OS_IMASK_FOR_ISRCAN6REC (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRCAN6REC (6U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRCAN6REC (0U) /* [$UKS 1909] */
DeclareISR(ISRCAN6REC)
#define ISRCAN6TRX (&Os_const_isrs[7U])
#define OS_IMASK_FOR_ISRCAN6TRX (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRCAN6TRX (7U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRCAN6TRX (0U) /* [$UKS 1909] */
DeclareISR(ISRCAN6TRX)
#define ISRCAN8REC (&Os_const_isrs[8U])
#define OS_IMASK_FOR_ISRCAN8REC (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRCAN8REC (8U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRCAN8REC (0U) /* [$UKS 1909] */
DeclareISR(ISRCAN8REC)
#define ISRCAN8TRX (&Os_const_isrs[9U])
#define OS_IMASK_FOR_ISRCAN8TRX (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRCAN8TRX (9U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRCAN8TRX (0U) /* [$UKS 1909] */
DeclareISR(ISRCAN8TRX)
#define ISRFLX0LINE0 (&Os_const_isrs[10U])
#define OS_IMASK_FOR_ISRFLX0LINE0 (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRFLX0LINE0 (10U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRFLX0LINE0 (0U) /* [$UKS 1909] */
DeclareISR(ISRFLX0LINE0)
#define ISRFLX1LINE0 (&Os_const_isrs[11U])
#define OS_IMASK_FOR_ISRFLX1LINE0 (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRFLX1LINE0 (11U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRFLX1LINE0 (0U) /* [$UKS 1909] */
DeclareISR(ISRFLX1LINE0)
#define ISRSTM04 (&Os_const_isrs[12U])
#define OS_IMASK_FOR_ISRSTM04 (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRSTM04 (12U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRSTM04 (0U) /* [$UKS 1909] */
DeclareISR(ISRSTM04)
#define ISRSTM05 (&Os_const_isrs[13U])
#define OS_IMASK_FOR_ISRSTM05 (6U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRSTM05 (13U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRSTM05 (0U) /* [$UKS 1909] */
DeclareISR(ISRSTM05)
#define ISRSWINT0 (&Os_const_isrs[14U])
#define OS_IMASK_FOR_ISRSWINT0 (5U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRSWINT0 (14U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRSWINT0 (1U) /* [$UKS 1909] */
DeclareISR(ISRSWINT0)
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_CORE_FOR_ISR) */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, OS_CORE_FOR_ISR) */
#define OS_CORE_FOR_ISR(i) OS_CORE_FOR_##i /* [$UKS 1922] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_IMASK_FOR_ISR) */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, OS_IMASK_FOR_ISR) */
#define OS_IMASK_FOR_ISR(n) OS_IMASK_FOR_##n  /* [$UKS 2011] */

/* -------- Resource declarations --------- */
#define OS_RTE_RESOURCE_CORE0 (&Os_const_resources[0U])
DeclareResource(OS_RTE_RESOURCE_CORE0)
#define OS_RTE_RESOURCE_CORE1 (&Os_const_resources[1U])
DeclareResource(OS_RTE_RESOURCE_CORE1)

/* -------- Counter declarations --------- */

/* -------- Alarm declaration --------- */

/* -------- ScheduleTable declaration --------- */

/* -------- Tracepoint declarations --------- */
#define OSApp_TrustedAppCore0 (1U)
#define OSApp_TrustedAppCore1 (2U)
#define OSApp_UntrustedAppCore0 (3U)
#define OSApp_UntrustedAppCore1 (4U)

/* -------- TaskTracepoint declarations --------- */

/* -------- Interval declarations --------- */

/* -------- Filtered APIs --------- */
#define Os_LogTracepoint(TpointID,Category) /* never */
#define Os_LogTracepointValue(TpointID,Value,Category) /* never */
#define Os_LogTracepointData(TpointID,Data,Length,Category) /* never */
#define Os_LogTaskTracepoint(TTpointID,Category) /* never */
#define Os_LogTaskTracepointValue(TTpointID,Value,Category) /* never */
#define Os_LogTaskTracepointData(TTpointID,Data,Length,Category) /* never */
#define Os_LogIntervalStart(IntervalID,Category) /* never */
#define Os_LogIntervalStartValue(IntervalID,Value,Category) /* never */
#define Os_LogIntervalStartData(IntervalID,Data,Length,Category) /* never */
#define Os_LogIntervalEnd(IntervalID,Category) /* never */
#define Os_LogIntervalEndValue(IntervalID,Value,Category) /* never */
#define Os_LogIntervalEndData(IntervalID,Data,Length,Category) /* never */
#ifndef OS_TRACE_NAMESPACE_PURE /* [$UKS 1154] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, LogTrace*, LogTaskTrace*, LogInterval*) */  #define LogTracepoint(TpointID,Category) Os_LogTracepoint(TpointID,Category)
  #define LogTracepointValue(TpointID,Value,Category) Os_LogTracepointValue(TpointID,Value,Category)
  #define LogTracepointData(TpointID,Data,Length,Category) Os_LogTracepointData(TpointID,Data,Length,Category)
  #define LogTaskTracepoint(TTpointID,Category) Os_LogTaskTracepoint(TTpointID,Category)
  #define LogTaskTracepointValue(TTpointID,Value,Category) Os_LogTaskTracepointValue(TTpointID,Value,Category)
  #define LogTaskTracepointData(TTpointID,Data,Length,Category) Os_LogTaskTracepointData(TTpointID,Data,Length,Category)
  #define LogIntervalStart(IntervalID,Category) Os_LogIntervalStart(IntervalID,Category)
  #define LogIntervalStartValue(IntervalID,Value,Category) Os_LogIntervalStartValue(IntervalID,Value,Category)
  #define LogIntervalStartData(IntervalID,Data,Length,Category) Os_LogIntervalStartData(IntervalID,Data,Length,Category)
  #define LogIntervalEnd(IntervalID,Category) Os_LogIntervalEnd(IntervalID,Category)
  #define LogIntervalEndValue(IntervalID,Value,Category) Os_LogIntervalEndValue(IntervalID,Value,Category)
  #define LogIntervalEndData(IntervalID,Data,Length,Category) Os_LogIntervalEndData(IntervalID,Data,Length,Category)
#endif

#define OS_IMASK_FOR_ISRSTM06_SC4core0 (5U) /* [$UKS 2009] */
#define Os_Cat1_ISRSTM06_SC4core0 (36U)
#define OS_CORE_FOR_ISRSTM06_SC4core0 (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_ISRSTM07_SC4core1 (5U) /* [$UKS 2009] */
#define Os_Cat1_ISRSTM07_SC4core1 (37U)
#define OS_CORE_FOR_ISRSTM07_SC4core1 (1U) /* [$UKS 1909] */
#define OS_IMASK_FOR_EXCFENMI (-1U) /* [$UKS 2009] */
#define Os_Cat1_EXCFENMI (38U)
#define OS_CORE_FOR_EXCFENMI (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_EXCFETRAP (-1U) /* [$UKS 2009] */
#define Os_Cat1_EXCFETRAP (39U)
#define OS_CORE_FOR_EXCFETRAP (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_EXCHVTRAP (-1U) /* [$UKS 2009] */
#define Os_Cat1_EXCHVTRAP (40U)
#define OS_CORE_FOR_EXCHVTRAP (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_EXCUCPOP (-1U) /* [$UKS 2009] */
#define Os_Cat1_EXCUCPOP (41U)
#define OS_CORE_FOR_EXCUCPOP (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_b_EXCDEBUG (-1U) /* [$UKS 2009] */
#define Os_Cat1_b_EXCDEBUG (42U)
#define OS_CORE_FOR_b_EXCDEBUG (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_b_EXCFEINT (-1U) /* [$UKS 2009] */
#define Os_Cat1_b_EXCFEINT (43U)
#define OS_CORE_FOR_b_EXCFEINT (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_b_EXCFPP (-1U) /* [$UKS 2009] */
#define Os_Cat1_b_EXCFPP (44U)
#define OS_CORE_FOR_b_EXCFPP (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_b_EXCMAE (-1U) /* [$UKS 2009] */
#define Os_Cat1_b_EXCMAE (45U)
#define OS_CORE_FOR_b_EXCMAE (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_b_EXCRIE (-1U) /* [$UKS 2009] */
#define Os_Cat1_b_EXCRIE (46U)
#define OS_CORE_FOR_b_EXCRIE (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_b_EXCSYSERR (-1U) /* [$UKS 2009] */
#define Os_Cat1_b_EXCSYSERR (47U)
#define OS_CORE_FOR_b_EXCSYSERR (0U) /* [$UKS 1909] */
/* [MISRA 2012 Rule 1.3] */ /*lint -estring(9023, Os_LogCat1ISRStart) */
/* [MISRA 2012 Rule 20.10] */ /*lint -esym(9024, Os_LogCat1ISRStart) */
#define Os_LogCat1ISRStart(IsrId)  /* [$UKS 1036] [$UKS 1037] [$UKS 1177] */
/* [MISRA 2012 Rule 1.3] */ /*lint -estring(9023, Os_LogCat1ISREnd) */
/* [MISRA 2012 Rule 20.10] */ /*lint -esym(9024, Os_LogCat1ISREnd) */
#define Os_LogCat1ISREnd(IsrId)  /* [$UKS 1038] [$UKS 1039] [$UKS 1178] */

#ifndef OS_TRACE_NAMESPACE_PURE /* [$UKS 1154] */
  #define LogCat1ISRStart Os_LogCat1ISRStart
  #define LogCat1ISREnd Os_LogCat1ISREnd
#endif
#endif /* OS_CFG_H */
