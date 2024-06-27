/*
 * This is Os_Cfg.h, auto-generated for:
 *   Project: rtaos_ccas_mcore_sc4
 *   Target:  RH850GHS
 *   Variant: P1HC
 *   Version: 5.0.36
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
#define TaskBaseCtrlCycx24 (&Os_const_tasks1[0])
#define OS_CORE_FOR_TaskBaseCtrlCycx24 (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx24 (0U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx24 (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx24 (0U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx24)
#define TaskBaseCtrlCycx8 (&Os_const_tasks0[0])
#define OS_CORE_FOR_TaskBaseCtrlCycx8 (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx8 (0U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx8 (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx8 (1U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx8)
#define TaskBaseCtrlCycx4 (&Os_const_tasks1[1])
#define OS_CORE_FOR_TaskBaseCtrlCycx4 (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx4 (1U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx4 (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx4 (2U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx4)
#define TaskBaseCtrlCycx2p (&Os_const_tasks0[1])
#define OS_CORE_FOR_TaskBaseCtrlCycx2p (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx2p (1U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx2p (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx2p (3U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx2p)
#define TaskBaseCtrlCycx2 (&Os_const_tasks1[2])
#define OS_CORE_FOR_TaskBaseCtrlCycx2 (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx2 (2U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx2 (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx2 (4U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx2)
#define TaskBaseCtrlCycx1Low (&Os_const_tasks0[2])
#define OS_CORE_FOR_TaskBaseCtrlCycx1Low (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx1Low (2U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx1Low (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx1Low (5U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx1Low)
#define TaskFlexray (&Os_const_tasks1[3])
#define OS_CORE_FOR_TaskFlexray (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskFlexray (3U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskFlexray (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskFlexray (6U) /* [$UKS 2185] */
DeclareTask(TaskFlexray)
#define TaskBaseCtrlCycx1High (&Os_const_tasks0[3])
#define OS_CORE_FOR_TaskBaseCtrlCycx1High (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskBaseCtrlCycx1High (3U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskBaseCtrlCycx1High (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskBaseCtrlCycx1High (7U) /* [$UKS 2185] */
DeclareTask(TaskBaseCtrlCycx1High)
#define Task1ms (&Os_const_tasks1[4])
#define OS_CORE_FOR_Task1ms (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_Task1ms (4U) /* [$UKS 2007] */
#define OS_IMASK_FOR_Task1ms (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_Task1ms (8U) /* [$UKS 2185] */
DeclareTask(Task1ms)
#define Task0p5ms (&Os_const_tasks1[5])
#define OS_CORE_FOR_Task0p5ms (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_Task0p5ms (5U) /* [$UKS 2007] */
#define OS_IMASK_FOR_Task0p5ms (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_Task0p5ms (9U) /* [$UKS 2185] */
DeclareTask(Task0p5ms)
#define TaskInitP (&Os_const_tasks1[6])
#define OS_CORE_FOR_TaskInitP (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskInitP (6U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskInitP (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskInitP (10U) /* [$UKS 2185] */
DeclareTask(TaskInitP)
#define TaskInit (&Os_const_tasks0[4])
#define OS_CORE_FOR_TaskInit (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskInit (4U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskInit (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskInit (11U) /* [$UKS 2185] */
DeclareTask(TaskInit)
#define TaskTPSWKillCore0 (&Os_const_tasks0[5])
#define OS_CORE_FOR_TaskTPSWKillCore0 (0U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskTPSWKillCore0 (5U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskTPSWKillCore0 (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskTPSWKillCore0 (12U) /* [$UKS 2185] */
DeclareTask(TaskTPSWKillCore0)
#define TaskTPSWKillCore1 (&Os_const_tasks1[7])
#define OS_CORE_FOR_TaskTPSWKillCore1 (1U) /* [$UKS 1909] */
#define OS_TPL_FOR_TaskTPSWKillCore1 (7U) /* [$UKS 2007] */
#define OS_IMASK_FOR_TaskTPSWKillCore1 (0x0000U) /* [$UKS 2009] */
#define OS_INDEX_FOR_TaskTPSWKillCore1 (13U) /* [$UKS 2185] */
DeclareTask(TaskTPSWKillCore1)
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_TPL_FOR_TASK, OS_IMASK_FOR_TASK) */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, OS_TPL_FOR_TASK) */
#define OS_TPL_FOR_TASK(n) OS_TPL_FOR_##n  /* [$UKS 2008] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, OS_IMASK_FOR_TASK) */
#define OS_IMASK_FOR_TASK(n) OS_IMASK_FOR_##n  /* [$UKS 2010] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_CORE_FOR_TASK) */
#define OS_CORE_FOR_TASK(t) (t)->core_id /* [$UKS 1921] */

/* -------- ISR declarations --------- */
#define ISRFLX0LINE0 (&Os_const_isrs[0U])
#define OS_IMASK_FOR_ISRFLX0LINE0 (0xFFC0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRFLX0LINE0 (0U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRFLX0LINE0 (0U) /* [$UKS 1909] */
DeclareISR(ISRFLX0LINE0)
#define ISRFLX1LINE0 (&Os_const_isrs[1U])
#define OS_IMASK_FOR_ISRFLX1LINE0 (0xFFC0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRFLX1LINE0 (1U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRFLX1LINE0 (0U) /* [$UKS 1909] */
DeclareISR(ISRFLX1LINE0)
#define ISRMCAN0I0 (&Os_const_isrs[2U])
#define OS_IMASK_FOR_ISRMCAN0I0 (0xFFC0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRMCAN0I0 (2U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRMCAN0I0 (0U) /* [$UKS 1909] */
DeclareISR(ISRMCAN0I0)
#define ISRMCAN1I0 (&Os_const_isrs[3U])
#define OS_IMASK_FOR_ISRMCAN1I0 (0xFFC0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRMCAN1I0 (3U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRMCAN1I0 (0U) /* [$UKS 1909] */
DeclareISR(ISRMCAN1I0)
#define ISRMCAN2I0 (&Os_const_isrs[4U])
#define OS_IMASK_FOR_ISRMCAN2I0 (0xFFC0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRMCAN2I0 (4U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRMCAN2I0 (0U) /* [$UKS 1909] */
DeclareISR(ISRMCAN2I0)
#define ISRMTTCANI0 (&Os_const_isrs[5U])
#define OS_IMASK_FOR_ISRMTTCANI0 (0xFFC0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRMTTCANI0 (5U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRMTTCANI0 (0U) /* [$UKS 1909] */
DeclareISR(ISRMTTCANI0)
#define ISRRLIN30RX (&Os_const_isrs[6U])
#define OS_IMASK_FOR_ISRRLIN30RX (0xFFC0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRRLIN30RX (6U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRRLIN30RX (0U) /* [$UKS 1909] */
DeclareISR(ISRRLIN30RX)
#define ISRRLIN30STATUS (&Os_const_isrs[7U])
#define OS_IMASK_FOR_ISRRLIN30STATUS (0xFFC0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRRLIN30STATUS (7U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRRLIN30STATUS (0U) /* [$UKS 1909] */
DeclareISR(ISRRLIN30STATUS)
#define ISRRLIN31RX (&Os_const_isrs[8U])
#define OS_IMASK_FOR_ISRRLIN31RX (0xFFC0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRRLIN31RX (8U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRRLIN31RX (0U) /* [$UKS 1909] */
DeclareISR(ISRRLIN31RX)
#define ISRRLIN31STATUS (&Os_const_isrs[9U])
#define OS_IMASK_FOR_ISRRLIN31STATUS (0xFFC0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRRLIN31STATUS (9U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRRLIN31STATUS (0U) /* [$UKS 1909] */
DeclareISR(ISRRLIN31STATUS)
#define ISRSTM04 (&Os_const_isrs[10U])
#define OS_IMASK_FOR_ISRSTM04 (0xFFC0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRSTM04 (10U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRSTM04 (1U) /* [$UKS 1909] */
DeclareISR(ISRSTM04)
#define ISRSTM05 (&Os_const_isrs[11U])
#define OS_IMASK_FOR_ISRSTM05 (0xFFC0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRSTM05 (11U) /* [$UKS 2186] */
#define OS_CORE_FOR_ISRSTM05 (0U) /* [$UKS 1909] */
DeclareISR(ISRSTM05)
#define ISRSWINT0 (&Os_const_isrs[12U])
#define OS_IMASK_FOR_ISRSWINT0 (0xFFE0U) /* [$UKS 2009] */
#define OS_INDEX_FOR_ISRSWINT0 (12U) /* [$UKS 2186] */
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

#define OS_IMASK_FOR_ISRSTM06_SC4core0 (0xFFE0U) /* [$UKS 2009] */
#define Os_Cat1_ISRSTM06_SC4core0 (29U)
#define OS_CORE_FOR_ISRSTM06_SC4core0 (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_ISRSTM07_SC4core1 (0xFFE0U) /* [$UKS 2009] */
#define Os_Cat1_ISRSTM07_SC4core1 (30U)
#define OS_CORE_FOR_ISRSTM07_SC4core1 (1U) /* [$UKS 1909] */
#define OS_IMASK_FOR_b_EXCFPP (0xFFFFU) /* [$UKS 2009] */
#define Os_Cat1_b_EXCFPP (31U)
#define OS_CORE_FOR_b_EXCFPP (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_EXCFETRAP (0xFFFFU) /* [$UKS 2009] */
#define Os_Cat1_EXCFETRAP (32U)
#define OS_CORE_FOR_EXCFETRAP (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_EXCHVTRAP (0xFFFFU) /* [$UKS 2009] */
#define Os_Cat1_EXCHVTRAP (33U)
#define OS_CORE_FOR_EXCHVTRAP (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_EXCUCPOP (0xFFFFU) /* [$UKS 2009] */
#define Os_Cat1_EXCUCPOP (34U)
#define OS_CORE_FOR_EXCUCPOP (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_b_EXCDEBUG (0xFFFFU) /* [$UKS 2009] */
#define Os_Cat1_b_EXCDEBUG (35U)
#define OS_CORE_FOR_b_EXCDEBUG (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_b_EXCFEINT (0xFFFFU) /* [$UKS 2009] */
#define Os_Cat1_b_EXCFEINT (36U)
#define OS_CORE_FOR_b_EXCFEINT (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_b_EXCMAE (0xFFFFU) /* [$UKS 2009] */
#define Os_Cat1_b_EXCMAE (37U)
#define OS_CORE_FOR_b_EXCMAE (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_b_EXCRIE (0xFFFFU) /* [$UKS 2009] */
#define Os_Cat1_b_EXCRIE (38U)
#define OS_CORE_FOR_b_EXCRIE (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_EXCFENMI (0xFFFFU) /* [$UKS 2009] */
#define Os_Cat1_EXCFENMI (39U)
#define OS_CORE_FOR_EXCFENMI (0U) /* [$UKS 1909] */
#define OS_IMASK_FOR_b_EXCSYSERR (0xFFFFU) /* [$UKS 2009] */
#define Os_Cat1_b_EXCSYSERR (40U)
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
