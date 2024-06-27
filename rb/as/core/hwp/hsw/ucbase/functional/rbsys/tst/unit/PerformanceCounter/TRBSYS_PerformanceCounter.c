/**
 * @ingroup RBSYS
 * @{
 *
 * \file
 * \brief Unit test for RBSYS_PerformanceCounter
 *
 * This unit test checks the correct behaviour of the RBSYS_PerfomanceCounter Task.
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "SwTest_Global.h"          // for SWT functionality
#include "RBSYS_Config.h"          // for RBFS_uCFamily, RBFS_SYSDebugFeatures

/* used interfaces */
#include "TRBSYS_Intrinsics.h"
#include "RBSYS_CpuInfo.h"
#include "TRBSYS_CpuInfo.h"
#include "RBSYS_Subsystem.h"

/* realized interfaces */
#include "TRBSYS_PerformanceCounter_Adaptor.h"

#if(((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) || (RBFS_uCFamily == RBFS_uCFamily_STMStellar)) && RBFS_SYSDebugFeatures == RBFS_SYSDebugFeatures_ON)

/* Check for correct configuration of performance counters */
static void TRBSYS_PC_Check_Configuration(void)
{
  #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    SWT_EvalEq(TRBSYS_PC_GET_TYPE(0), TRBSYS_TYPE_INSTRUCTION);
    SWT_EvalEq(TRBSYS_PC_GET_TYPE(1), TRBSYS_TYPE_INSTRUCTION_FETCH_REQ);
    SWT_EvalEq(TRBSYS_PC_GET_TYPE(2), TRBSYS_TYPE_FLASH_INSTRUCTION_FETCH_REQ);
    SWT_EvalEq(TRBSYS_PC_GET_TYPE(3), TRBSYS_TYPE_STALL_CYC);
    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      SWT_EvalEq(TRBSYS_PC_GET_TYPE(4), TRBSYS_TYPE_CONDITIONAL_BRANCH_INSTRUCTION);
      SWT_EvalEq(TRBSYS_PC_GET_TYPE(5), TRBSYS_TYPE_BRANCH_PREDICTION_MISSES);
    #endif
  #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
    SWT_EvalEq(RBSYS_MRC(15, 0, 14, 12, 0),PC_TYPE_INST_RETIRED);
    SWT_EvalEq(RBSYS_MRC(15, 0, 14, 12, 1),PC_TYPE_STALL_FRONTEND);
    SWT_EvalEq(RBSYS_MRC(15, 0, 14, 12, 2),PC_TYPE_STALL_BACKEND);
  #endif
}

/* Check whether performance counters are running */
static void TRBSYS_PC_Check_Counter_Running(void)
{
  #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    SWT_EvalEq(RBSYS_STSR(TRBSYS_TSCTRL_REG, TRBSYS_TS_SEL), 0x1);
    SWT_EvalEq(TRBSYS_PC_IS_STARTED(0), 0x1);
    SWT_EvalEq(TRBSYS_PC_IS_STARTED(1), 0x1);
    SWT_EvalEq(TRBSYS_PC_IS_STARTED(2), 0x1);
    SWT_EvalEq(TRBSYS_PC_IS_STARTED(3), 0x1);
    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      SWT_EvalEq(TRBSYS_PC_IS_STARTED(4), 0x1);
      SWT_EvalEq(TRBSYS_PC_IS_STARTED(5), 0x1);
    #endif
  #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
    SWT_EvalEq(RBSYS_MRC(15, 0, 9, 12, 0) & 0x1, 0x1);
    SWT_EvalEq(RBSYS_MRC(15, 0, 9, 12, 1), (1u << 31) | (1u << 3) | (1u << 2) | (1u << 1) | 1u);
  #endif
}

/* Check whether global variables are updated correctly */
static void TRBSYS_PC_Check_Monitoring_Info(unsigned int iteration, boolean running)
{
  unsigned int coreId = RBSYS_getCoreID();
  RBSYS_PerformanceCounterMonitoringInfo_t monitoringInfo = TRBSYS_PerformanceCounterGetMonitoringInfo(coreId);
  SWT_EvalEq(monitoringInfo.initialized, running);
  SWT_EvalEq(monitoringInfo.execution_cnt, iteration % TRBSYS_EXECUTION_CNT_RESTART);
}

/**
 * Set counter values depending on the execution iteration and executing core
 * e.g. PC_TYPE_INSTRUCTION counter is incremented by (0x1 * coreFactor) every iteration.
 * The coreFactor ensures different counter values and different resulting metrics per core.
 */
static void TRBSYS_PC_Set_Counter_Values(unsigned int iteration)
{
  unsigned int coreId = RBSYS_getCoreID();
  unsigned int coreFactor = (coreId + 1);
  #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    RBSYS_LDSR(TRBSYS_TSCOUNTL_REG, TRBSYS_TS_SEL, iteration * 0xf);
    RBSYS_LDSR(TRBSYS_TSCOUNTH_REG, TRBSYS_TS_SEL, iteration * 0x0);
    TRBSYS_PC_SET_VALUE(0, iteration * 0x1 * coreFactor);
    TRBSYS_PC_SET_VALUE(1, iteration * 0x2 * coreFactor);
    TRBSYS_PC_SET_VALUE(2, iteration * 0x3 * coreFactor);
    TRBSYS_PC_SET_VALUE(3, iteration * 0x4 * coreFactor);
    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      TRBSYS_PC_SET_VALUE(4, iteration * 0x5 * coreFactor);
      TRBSYS_PC_SET_VALUE(5, iteration * 0x6 * coreFactor);
    #endif
  #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
    RBSYS_MCR(15, 0, iteration * 0xf, 9, 13, 0);
    RBSYS_MCR(15, 0, iteration * 0x1 * coreFactor, 14, 8, 0);
    RBSYS_MCR(15, 0, iteration * 0x2 * coreFactor, 14, 8, 1);
    RBSYS_MCR(15, 0, iteration * 0x3 * coreFactor, 14, 8, 2);
  #endif
}

/* Check counter values depending on the execution iteration and executing core */
static void TRBSYS_PC_Check_Counter_Values(unsigned int iteration)
{
  unsigned int coreId = RBSYS_getCoreID();
  unsigned int coreFactor = (coreId + 1);
  #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    SWT_EvalEq(RBSYS_STSR(TRBSYS_TSCOUNTL_REG, TRBSYS_TS_SEL), iteration * 0xf);
    SWT_EvalEq(RBSYS_STSR(TRBSYS_TSCOUNTH_REG, TRBSYS_TS_SEL), iteration * 0x0);
    SWT_EvalEq(TRBSYS_PC_GET_VALUE(0), iteration * 0x1 * coreFactor);
    SWT_EvalEq(TRBSYS_PC_GET_VALUE(1), iteration * 0x2 * coreFactor);
    SWT_EvalEq(TRBSYS_PC_GET_VALUE(2), iteration * 0x3 * coreFactor);
    SWT_EvalEq(TRBSYS_PC_GET_VALUE(3), iteration * 0x4 * coreFactor);
    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      SWT_EvalEq(TRBSYS_PC_GET_VALUE(4), iteration * 0x5 * coreFactor);
      SWT_EvalEq(TRBSYS_PC_GET_VALUE(5), iteration * 0x6 * coreFactor);
    #endif
  #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
    unsigned int pmcr = RBSYS_MRC(15, 0, 9, 12, 0);
    if((pmcr & 0x2) == 0x2)
    {
      // reset event counters
      pmcr &= ~0x2;
      RBSYS_MCR(15, 0, pmcr, 9, 12, 0);
      RBSYS_MCR(15, 0, 0x0, 14, 8, 0);
      RBSYS_MCR(15, 0, 0x0, 14, 8, 1);
      RBSYS_MCR(15, 0, 0x0, 14, 8, 2);
    }
    if((pmcr & 0x4) == 0x4)
    {
      // reset cycle counter
      pmcr &= ~0x4;
      RBSYS_MCR(15, 0, pmcr, 9, 12, 0);
      RBSYS_MCR(15, 0, 0x0, 9, 13, 0);
    }

    SWT_EvalEq(RBSYS_MRC(15, 0, 9, 13, 0), iteration * 0xf);
    SWT_EvalEq(RBSYS_MRC(15, 0, 14, 8, 0), iteration * 0x1 * coreFactor);
    SWT_EvalEq(RBSYS_MRC(15, 0, 14, 8, 1), iteration * 0x2 * coreFactor);
    SWT_EvalEq(RBSYS_MRC(15, 0, 14, 8, 2), iteration * 0x3 * coreFactor);
  #endif
}

/* Check calculated metrics depending on the execution iteration and executing core */
static void TRBSYS_PC_Check_Metrics(unsigned int iteration)
{
  unsigned int coreId = RBSYS_getCoreID();
  unsigned int coreFactor = (coreId + 1);

  RBSYS_PerformanceCounterMetrics_t PC = TRBSYS_PerformanceCounterGetMetrics(coreId);
  if( iteration == 0 )
  {
    #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      SWT_Eval(PC.ipc                         == 0);
      SWT_Eval(PC.cpu_stall_rate              == 0);
      SWT_Eval(PC.is_hit_rate                 == 0);
      #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        SWT_Eval(PC.branch_prediction_hit_rate  == 0);
      #endif
    #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
      SWT_Eval(PC.ipc                         == 0);
      SWT_Eval(PC.cpu_stall_rate_frontend     == 0);
      SWT_Eval(PC.cpu_stall_rate_backend      == 0);
    #endif
  }
  else
  {
    #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      // Calculate expected performance counter values with core dependent increments per iteration as in TRBSYS_Set_Counter_Values
      float clk_cyc               = iteration * 0xf;
      float instr                 = iteration * 0x1 * coreFactor;
      float instr_fetch_req       = iteration * 0x2 * coreFactor;
      float flash_instr_fetch_req = iteration * 0x3 * coreFactor;
      float stall_cyc             = iteration * 0x4 * coreFactor;
      #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        float cond_branch_instr     = iteration * 0x5 * coreFactor;
        float branch_pred_misses    = iteration * 0x6 * coreFactor;
      #endif

      // Calculate expected metrics
      float32 ipc                         = instr / clk_cyc;
      float32 cpu_stall_rate              = stall_cyc / clk_cyc;
      float32 is_hit_rate                 = 1.0f - (flash_instr_fetch_req / instr_fetch_req);
      #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        float32 branch_prediction_hit_rate  = (cond_branch_instr - branch_pred_misses) / cond_branch_instr;
      #endif

      SWT_Eval(PC.ipc                         == ipc);
      SWT_Eval(PC.cpu_stall_rate              == cpu_stall_rate);
      SWT_Eval(PC.is_hit_rate                 == is_hit_rate);
      #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        SWT_Eval(PC.branch_prediction_hit_rate  == branch_prediction_hit_rate);
      #endif
    #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
      // Calculate expected performance counter values with core dependent increments per iteration as in TRBSYS_Set_Counter_Values
      float clk_cyc_f          = iteration * 0xf;
      float instruction_cnt    = iteration * 0x1 * coreFactor;
      float stall_frontend_cnt = iteration * 0x2 * coreFactor;
      float stall_backend_cnt  = iteration * 0x3 * coreFactor;

      // Calculate expected metrics
      float32 ipc                        = instruction_cnt / clk_cyc_f;
      float32 cpu_stall_rate_frontend    = stall_frontend_cnt / clk_cyc_f;
      float32 cpu_stall_rate_backend     = stall_backend_cnt / clk_cyc_f;

      SWT_Eval(PC.ipc                     == ipc);
      SWT_Eval(PC.cpu_stall_rate_frontend == cpu_stall_rate_frontend);
      SWT_Eval(PC.cpu_stall_rate_backend  == cpu_stall_rate_backend);
    #endif
  }
}

/**
 * \Reference
 *  RBSYS_PRC_PerformanceCounterMonitoring_x2
 *
 * \Purpose
 *  Verification of process RBSYS_PRC_PerformanceCounterMonitoring_x2
 *
 * \Sequence
 *  Call process RBSYS_PRC_PerformanceCounterMonitoring_x2 13 times for two cores
 *  Increment Performance Counters before every call
 *
 * \ExpectedResult
 * Initialization of performance counters in the first run,
 * no changes of metrics in the next 11 runs,
 * 12th run after starting calculates metrics, resets and restarts performance counters
 * no interference between the cores.
 */
SWTEST void TRBSYS_PRC_PerformanceCounterMonitoring_x2(void)
{
  int i, coreId;

  /* Run the first time */
  for (coreId = 0; coreId < RB_NUM_CORES; coreId++)
  {
    TRBSYS_setCoreID(coreId);
    TRBSYS_PC_Set_Counter_Values(0); // Set counter values to zero, to check for division by zero in the next task call
    TRBSYS_PC_Check_Monitoring_Info(0, FALSE); // Already_done is FALSE and execution_cnt is 0

    RBSYS_PRC_PerformanceCounterMonitoring_x2();

    // Check configuration, counter values and counter started
    TRBSYS_PC_Check_Monitoring_Info(0, TRUE); // Already_done is TRUE and execution_cnt is 0 as it is reset
    TRBSYS_PC_Check_Configuration();       // Configured correctly
    TRBSYS_PC_Check_Counter_Values(0);     // Counter Values are not changed
    TRBSYS_PC_Check_Counter_Running();     // Counters have been started
    TRBSYS_PC_Check_Metrics(0);            // Metrics have not been calculated
  }

  /* For the next 11 execution, check that counter values are not reset and metrics are not calculated */
  for (i=1; i<12; i++)
  {
    for (coreId = 0; coreId < RB_NUM_CORES; coreId++)
    {
      TRBSYS_setCoreID(coreId);
      TRBSYS_PC_Set_Counter_Values(i); // Set different counter values

      RBSYS_PRC_PerformanceCounterMonitoring_x2();

      /* Check configuration and counter values not changed, counter still running, metrics not calculated */
      TRBSYS_PC_Check_Monitoring_Info(i, TRUE);
      TRBSYS_PC_Check_Configuration();
      TRBSYS_PC_Check_Counter_Values(i);
      TRBSYS_PC_Check_Counter_Running();
      TRBSYS_PC_Check_Metrics(0);
    }
  }

  /* The 12th execution after starting the counters calculates metrics and resets the counter values */
  for (coreId = 0; coreId < RB_NUM_CORES; coreId++)
  {
    TRBSYS_setCoreID(coreId);
    TRBSYS_PC_Set_Counter_Values(12);

    RBSYS_PRC_PerformanceCounterMonitoring_x2();

    TRBSYS_PC_Check_Monitoring_Info(12, TRUE);
    TRBSYS_PC_Check_Metrics(12);
    TRBSYS_PC_Check_Counter_Values(0);
    TRBSYS_PC_Check_Counter_Running();
  }
}

#else

  SWTEST void TRBSYS_PerformanceCounter_FeatureNotAvailable(void)
  {
    SWT_EvalEx(TRUE, "Feature not Available");
  }

#endif

/** @} */
/* End ingroup RBSYS */

