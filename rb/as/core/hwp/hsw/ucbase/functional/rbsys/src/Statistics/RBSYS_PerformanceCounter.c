/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Task performance counter monitoring
 *
 * This task configures and monitors the U2A performance counters and timestamp counter per PE.
 * It reads out and resets each counter periodically and calculates relevant metrics.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_Intrinsics.h"
#include "RBSYS_CpuInfo.h"


/* realized interfaces */
#include "RBSYS_PerformanceCounter.h"
#include "RBSYS_Subsystem.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SYSDebugFeatures,
                          RBFS_SYSDebugFeatures_ON,
                          RBFS_SYSDebugFeatures_OFF);


#if( ( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)\
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)\
    || (RBFS_uCFamily == RBFS_uCFamily_STMStellar) )\
  && (RBFS_SYSDebugFeatures == RBFS_SYSDebugFeatures_ON) )

  #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))

    // Register number (*_REG) and selection ID (*_SEL) of relevant system registers
    #define TS_SEL              11
    #define TSCOUNTL_REG        0           // Timestamp count L register
    #define TSCOUNTH_REG        1           // Timestamp count H register
    #define TSCTRL_REG          2           // Timestamp count control register

    #define PMUMCTRL_SEL        11
    #define PMUMCTRL_REG        8           // Performance counter User mode control register

    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      #define PMCTRL_SEL        14
      #define PMCTRLn_REG(n)    (n)          // Performance count control n register
      #define PMCOUNT_SEL       14
      #define PMCOUNTn_REG(n)   (16 + (n))   // Performance count n register
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      #define PMCTRL_SEL        11
      #define PMCTRLn_REG(n)    (17 + 2*(n)) // Performance count control n register
      #define PMCOUNT_SEL       11
      #define PMCOUNTn_REG(n)   (16 + 2*(n)) // Performance count n register
    #endif

    // Types of events that are possible to be counted
    #define PC_TYPE_CLK_CYC                         0x00  //Number of all clock cycles
    #define PC_TYPE_INSTRUCTION                     0x10  //Number of executions of all instructions
    #define PC_TYPE_BRANCH_INSTRUCTION              0x18  //Number of instructions that cause branch
    #define PC_TYPE_CONDITIONAL_BRANCH_INSTRUCTION  0x19  //Number of executions of conditional branch instructions (Bcond/Loop)
    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) //U2C does not support branch prediction
      #define PC_TYPE_BRANCH_PREDICTION_MISSES      0x1A  //Number of branch prediction misses of conditional branch instructions (Bcond/Loop)
    #endif
    #define PC_TYPE_EIINTN_ACC                      0x20  //Number of EIINTn acceptances
    #define PC_TYPE_FEINT_ACC                       0x21  //Number of FEINT acceptances
    #define PC_TYPE_TERMINATING_EXC_ACC             0x22  //Number of terminating type exception acceptances (including EIINTn and FEINT)
    #define PC_TYPE_RES_PEN_EXC_ACC                 0x23  //Number of resumable and pending type exception acceptances
    #define PC_TYPE_CLK_CYC_NO_INT                  0x28  //Number of clock cycles during no interrupt is processed (period during which the ISPR register holds 0000H)
    #define PC_TYPE_CLK_CYC_NO_INT_DISABLED         0x29  //Number of clock cycles during no interrupt is processed and interrupts are disabled (period during which the ISPR register holds 0000H*7 and PSW.ID = 1)
    #define PC_TYPE_INSTRUCTION_FETCH_REQ           0x30  //Number of instruction fetch requests
    #define PC_TYPE_INSTRUCTION_CACHE_HIT           0x31  //Number of instruction cache hits
    #define PC_TYPE_STALL_CYC                       0x40  //Number of stall cycles during which instructions are not issued to the instruction execution unit
    #define PC_TYPE_FLASH_INSTRUCTION_FETCH_REQ     0x50  //Number of instruction fetch requests to Flash ROM
    #define PC_TYPE_FLASH_DATA_READ_REQ             0x51  //Number of data read requests to Flash ROM

    // Helper macros as system register functions only work with constant expressions
    #define RBSYS_PC_SET_TYPE(n,val)                RBSYS_LDSR(PMCTRLn_REG(n), PMCTRL_SEL, ((uint32)(val) << 8))
    #define RBSYS_PC_START(n)                       RBSYS_LDSR(PMCTRLn_REG(n), PMCTRL_SEL, RBSYS_STSR(PMCTRLn_REG(n), PMCTRL_SEL) | 0x1u)
    #define RBSYS_PC_STOP(n)                        RBSYS_LDSR(PMCTRLn_REG(n), PMCTRL_SEL, RBSYS_STSR(PMCTRLn_REG(n), PMCTRL_SEL) & ~(uint32)1)
    #define RBSYS_PC_GET_VALUE(n)                   RBSYS_STSR(PMCOUNTn_REG(n), PMCOUNT_SEL)
    #define RBSYS_PC_SET_VALUE(n, val)              RBSYS_LDSR(PMCOUNTn_REG(n), PMCOUNT_SEL, (val))
    #define RBSYS_PC_GET_OVF(n)                     (RBSYS_STSR(PMCTRLn_REG(n), PMCOUNT_SEL) & 0x2u)

  #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)

    // Types of events that are possible to be counted
    #define PC_TYPE_SW_INCR                      0x000 // Software increment. The register is incremented only on writes to the Software Increment Register (PMSWINC).
    #define PC_TYPE_L1I_CACHE_REFILL             0x001 // L1 instruction cache refill.
    #define PC_TYPE_L1D_CACHE_REFILL             0x003 // L1 data cache refill.
    #define PC_TYPE_L1D_CACHE                    0x004 // L1 data cache access.
    #define PC_TYPE_LD_RETIRED                   0x006 // Instruction architecturally executed, condition check pass - load.
    #define PC_TYPE_ST_RETIRED                   0x007 // Instruction architecturally executed, condition check pass - store.
    #define PC_TYPE_INST_RETIRED                 0x008 // Instruction architecturally executed.
    #define PC_TYPE_EXC_TAKEN                    0x009 // Exception taken.
    #define PC_TYPE_EXC_RETURN                   0x00A // Instruction architecturally executed, condition code check pass, exception return.
    #define PC_TYPE_CID_WRITE_RETIRED            0x00B // Instruction architecturally executed, condition code check pass, write to CONTEXTIDR.
    #define PC_TYPE_PC_WRITE_RETIRED             0x00C // Instruction architecturally executed, condition check pass, software change of the PC.
    #define PC_TYPE_BR_IMMED_RETIRED             0x00D // Instruction architecturally executed, immediate branch.
    #define PC_TYPE_BR_RETURN_RETIRED            0x00E // Instruction architecturally executed, condition code check pass, procedure return.
    #define PC_TYPE_UNALIGNED_LDST_RETIRED       0x00F // Instruction architecturally executed, condition code check pass, unaligned load or store.
    #define PC_TYPE_BR_MIS_PRED                  0x010 // Mispredicted or not predicted branch speculatively executed.
    #define PC_TYPE_CPU_CYCLES                   0x011 // Cycle
    #define PC_TYPE_BR_PRED                      0x012 // Predictable branch speculatively executed.
    #define PC_TYPE_MEM_ACCESS                   0x013 // Data memory access.
    #define PC_TYPE_L1I_CACHE                    0x014 // L1 instruction cache access.
    #define PC_TYPE_BUS_ACCESS                   0x019 // AXIM , Flash, or LLPP bus access.
    #define PC_TYPE_MEMORY_ERROR                 0x01A // Local memory error (instruction cache, data cache, ATCM, BTCM, CTCM, or Flash).
    #define PC_TYPE_INST_SPEC                    0x01B // Operation speculatively executed.
    #define PC_TYPE_BUS_CYCLES                   0x01D // Bus cycle (AXIM).
    #define PC_TYPE_CHAIN                        0x01E // For odd-numbered counters, increments the count by one for each overflow of the preceding even-numbered counter. For evennumbered counters, there is no increment.
    #define PC_TYPE_BR_RETIRED                   0x021 // Instruction architecturally executed, branch.
    #define PC_TYPE_BR_MIS_PRED_RETIRED          0x022 // Instruction architecturally executed, mispredicted branch.
    #define PC_TYPE_STALL_FRONTEND               0x023 // No operation issued due to the front end.
    #define PC_TYPE_STALL_BACKEND                0x024 // No operation issued due to the back end.
    #define PC_TYPE_BUS_ACCESS_RD                0x060 // Bus access - Read (AXIM, Flash, or LLPP).
    #define PC_TYPE_BUS_ACCESS_WR                0x061 // Bus access - Write (AXIM, Flash, or LLPP).
    #define PC_TYPE_EXC_SVC                      0x082 // Exception taken, supervisor call.
    #define PC_TYPE_EXC_IRQ                      0x086 // Exception taken, IRQ.
    #define PC_TYPE_EXC_FIQ                      0x087 // Exception taken, FIQ.
    #define PC_TYPE_EXC_HVC                      0x08A // Exception taken, Hypervisor Call.
    #define PC_TYPE_EXC_TRAP_IRQ                 0x08E // Exception taken, IRQ not taken locally.
    #define PC_TYPE_EXC_TRAP_FIQ                 0x08F // Exception taken, FIQ not taken locally.
    #define PC_TYPE_KITE_AXI_READ                0x0C0 // External memory request, AXIM read.
    #define PC_TYPE_KITE_AXI_WRITE               0x0C1 // External memory request, AXIM write.
    #define PC_TYPE_KITE_FLASH_READ              0x0C2 // External memory request, Flash (read-only).
    #define PC_TYPE_KITE_LLPP_READ               0x0C3 // External memory request, LLPP read.
    #define PC_TYPE_KITE_LLPP_WRITE              0x0C4 // External memory request, LLPP write.
    #define PC_TYPE_KITE_NC_AXI_READ             0x0C5 // Non cacheable external memory request, AXIM read.
    #define PC_TYPE_KITE_NC_AXI_WRITE            0x0C6 // Non cacheable external memory request, AXIM write.
    #define PC_TYPE_KITE_NC_FLASH_READ           0x0C7 // Non cacheable external memory request, Flash (read-only).
    #define PC_TYPE_KITE_REFILL_PF_AXI           0x0C8 // L1 data cache refill because of prefetch (AXIM only).
    #define PC_TYPE_KITE_REFILL_LS_AXI           0x0C9 // L1 data cache refill because of load or store, AXIM.
    #define PC_TYPE_KITE_REFILL_LS_FLASH         0x0CA // L1 data cache refill because of load or store, Flash.bx
    #define PC_TYPE_KITE_DC_ACCESS_AXI           0x0CB // L1 data cache access in a way reserved for AXIM.
    #define PC_TYPE_KITE_DC_ACCESS_FLASH         0x0CC // L1 data cache access in a way reserved for Flash.by
    #define PC_TYPE_KITE_IC_ACCESS_AXI           0x0CD // L1 instruction cache access in a way reserved for AXIM.
    #define PC_TYPE_KITE_IC_ACCESS_FLASH         0x0CE // L1 instruction cache access in a way reserved for Flash.bz
    #define PC_TYPE_KITE_NC_LS_HINTED_AXI        0x0CF // Non cacheable external memory request because of load was hinted, AXIM.ca
    #define PC_TYPE_KITE_NC_LS_HINTED_FLASH_READ 0x0D0 // Non cacheable external memory request because of load was hinted, Flash.ca
    #define PC_TYPE_KITE_REFILL_IC_AXI           0x0D1 // L1 Instruction cache refill, AXIM.
    #define PC_TYPE_KITE_REFILL_IC_FLASH         0x0D2 // L1 Instruction cache refill, Flash.cb
    #define PC_TYPE_KITE_NC_LS_AXI_READ          0x0D3 // Non cacheable external memory request because of load, AXIM.
    #define PC_TYPE_KITE_NC_LS_FLASH_READ        0x0D4 // Non cacheable external memory request because of load, Flash.
    #define PC_TYPE_KITE_COND_BR_RETIRED         0x0D5 // Conditional branch executed.
    #define PC_TYPE_KITE_MIS_PRED_COND_BR        0x0D6 // Conditional branch mispredicted.
    #define PC_TYPE_KITE_BTAC_BR_RETIRED         0x0D7 // BTAC branch executed.
    #define PC_TYPE_KITE_MIS_PRED_BTAC_BR        0x0D8 // Conditional branch mispredicted.
    #define PC_TYPE_KITE_VSCTLR_CHANGED          0x0D9 // Instruction architecturally executed, MCR to VSCTLR.
    #define PC_TYPE_KITE_DSB_ALL_RETIRED         0x0DA // Instruction architecturally executed, strong DSB, DFB.
    #define PC_TYPE_KITE_SIMULT_ACCESS_AXI       0x0DB // Simultaneous accesses from instruction side and data side to AXIM (causing contention).
    #define PC_TYPE_KITE_SIMULT_ACCESS_FLASH     0x0DC // Simultaneous accesses from instruction side and data side to Flash (causing contention) bx Event 0x003 (LID_CACHE_REFILL) is the sum of events 0x0C9 and 0x0CA. by Event 0x004 (LID_CACHE) is the sum of events 0x0CB and 0x0CC. bz Event 0x014 (LII_CACHE) is the sum of events 0x0CD and 0x0CE. ca A hinted Load Store Unit (LSU) request is an early request issued from the Load Store 1 (LS1) pipeline stage to reduce memory latency. More specifically, hinted requests be can be made before the condition codes of the instruction have been determined. cb Event 001 (LII_CACHE_REFILL) is the sum of events 0x0D1 and 0x0D2.
    #define PC_TYPE_KITE_EL2_ENTERED             0x0DD // Exception taken to EL2 (hyp mode entry), excluding reset.
    #define PC_TYPE_KITE_CRS_BR_RETIRED          0x0DE // Implementation defined event. CRS branch executed.
    #define PC_TYPE_KITE_MIS_PRED_CRS_BR         0x0DF // CRS branch mispredicted.
    #define PC_TYPE_KITE_COR_ERR_MEM             0x0F0 // Correctable memory error occurred from any source (L1 instruction cache, L1 data cache, ATCM, BTCM, CTCM, or flash).
    #define PC_TYPE_KITE_FAT_ERR_MEM             0x0F1 // Fatal memory error occurred from any source (ATCM, BTCM, CTCM, or Flash).
    #define PC_TYPE_KITE_BUS_COR_DATA            0x0F2 // Correctable data payload bus error occurred from any source (AXIM or LLPP).
    #define PC_TYPE_KITE_BUS_FAT_OTHER           0x0F3 // Fatal non-protocol bus error (payload errors, except data) occurred from any source (AXIM, Flash, or LLPP).
    #define PC_TYPE_KITE_BUS_PROTOCOL_ANY        0x0F4 // Fatal protocol bus error (LEN, ID, LAST, READY, and interconnect protection errors) occurred from any source (AXIM, Flash, or LLPP).
    #define PC_TYPE_KITE_IQ_EMPTY_NO_MISS        0x100 // Counts every cycle that the DPU IQ is empty and that is not because of a recent instruction cache miss in any way.
    #define PC_TYPE_KITE_IQ_EMPTY_AXI_MISS       0x101 // Counts every cycle that the DPU IQ is empty and there is an instruction cache miss being processed for a cache way reserved for AXI Master.
    #define PC_TYPE_KITE_IQ_EMPTY_FLASH_MISS     0x102 // Counts every cycle that the DPU IQ is empty and there is an instruction cache miss being processed for a cache way reserved for Flash.
    #define PC_TYPE_KITE_INTERLOCK_OTHER         0x103 // Counts every cycle there is an interlock that is not because of an Advanced SIMD or floating-point instruction, and not because of a load/store instruction waiting for data to calculate the address in the AGU. Stall cycles because of a stall in Wr, typically awaiting load data, are excluded.
    #define PC_TYPE_KITE_INTERLOCK_AGU           0x104 // Counts every cycle there is an interlock that is because of a load/ store instruction waiting for data to calculate the address in the AGU. Stall cycles because of a stall in Wr, typically awaiting load data, are excluded.
    #define PC_TYPE_KITE_INTERLOCK_FPASIMD       0x105 // Counts every cycle there is an interlock that is because of an Advanced SIMD or floating-point instruction. Stall cycles because of a stall in the Wr stage, typically waiting load data, are excluded.
    #define PC_TYPE_KITE_LOAD_STALL_AXI          0x106 // Counts every cycle there is a stall in the Wr stage because of a load miss from the AXIM.
    #define PC_TYPE_KITE_LOAD_STALL_FLASH        0x107 // Counts every cycle there is a stall in the Wr stage because of a load miss from Flash.
    #define PC_TYPE_KITE_WR_STALL_STORE          0x108 // Counts every cycle there is a stall in the Wr stage because of a store.
    #define PC_TYPE_KITE_WR_STALL_AXI_STB_FULL   0x109 // Store stalled because the AXIM part of the store buffer was full.
    #define PC_TYPE_KITE_WR_STALL_TCM_STB_FULL   0x10A // Store stalled because the TCM part of the store buffer was full.
    #define PC_TYPE_KITE_WR_STALL_LLPP_STB_FULL  0x10B // Store stalled because the LLPP part of the store buffer was full.
    #define PC_TYPE_KITE_BARRIER_STALL_BARRIER   0x10C // Barrier stalled because store buffer was busy with another barrier.
    #define PC_TYPE_KITE_BARRIER_STORE_AXIWRITE  0x10D // Barrier stalled because it was waiting for a write to complete on the AXIM bus.
    #define PC_TYPE_KITE_IC_WT_HIT               0x200 // L1 instruction cache way tracker hit.
    #define PC_TYPE_KITE_DC_WT_HIT               0x201 // L1 data cache way tracker hit.
    #define PC_TYPE_KITE_I_UMPU_HIT              0x202 // Instruction side micro MPU hit.
    #define PC_TYPE_KITE_D_UMPU_HIT              0x203 // Data side micro MPU hit. This can also be counted on a pipeline stall.
    #define PC_TYPE_KITE_IC_CACHE_HIT            0x204 // L1 instruction cache hit.
    #define PC_TYPE_KITE_IC_LFB_HIT              0x205 // L1 instruction cache linefill buffer hit.
    #define PC_TYPE_KITE_IC_BIU_HIT              0x206 // L1 instruction cache hit on BIU response.
    #define PC_TYPE_KITE_IC_HINT_REQ             0x207 // L1 instruction cache hint request sent.

  #endif

  // Number of execution until the metrics are calculated and the performance counters are reset
  #define EXECUTION_CNT_RESTART (12)

  // Stores metrics calculated from performance counters per core
  static __attribute__((used)) RBSYS_PerformanceCounterMetrics_t RBSYS_PerformanceCounterMetrics[RB_NUM_CORES];
  /*[[MEASUREMENT_TYPEDEF*/
  /*TYPE=RBSYS_PerformanceCounterMetrics_t */
  /*NAME=RBSYS_PerformanceCounterMetrics[RB_NUM_CORES]*/
  /*MTEVENT=c_MT_Default_Task_x2*/
  /*]]MEASUREMENT_TYPEDEF*/

  // Stores status of initialization and execution count of the performance counter monitoring task per core
  static __attribute__((used)) RBSYS_PerformanceCounterMonitoringInfo_t RBSYS_PerformanceCounterMonitoringInfo[RB_NUM_CORES] = {{FALSE, 0}, {FALSE, 0}};

  /**
  * @brief Performance counter monitoring
  *
  * Configures performance counters and timestamp counter on first run.
  * Periodically reads out and resets counter values every 12th execution (120ms).
  * Calculates relevant metrics that can be measured.
  *
  * Note: This task is run as x2 and x2p task (instead of as x24 task) because an instance has to be run
  *       on every PE and x2p is guaranteed to be run on a different PE than x2.
  *
  * @return void
  */
  void RBSYS_PRC_PerformanceCounterMonitoring_x2(void)
  {
    #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      // Variables for temporarily holding integer values of performance counters used as dividers
      uint64 temp_clk_cyc;
      uint32 temp_instr_fetch_req;
      // Variable for clock cycle counter value
      float clk_cyc;
      // Variables for the performance counter values
      float instr, instr_fetch_req, flash_instr_fetch_req, stall_cyc;
      #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        uint32 temp_cond_branch_instr;
        float cond_branch_instr, branch_pred_misses;
      #endif
    #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
      uint32 pmcr;
      // Variables for temporarily holding integer values of performance counters used as dividers
      uint32 temp_clk_cyc;
      // Variable for clock cycle counter value
      float clk_cyc;
      // Variables for the performance counter values, todo: decide which metrics to measure
      // group 1
      float instruction_cnt, stall_frontend_cnt, stall_backend_cnt;
      // group 2
      //uint32 temp_instruction_cache_access, temp_data_cache_access;
      //float instruction_cache_access, instruction_cache_hit, data_cache_access, data_cache_hit;
      // group 3
      //uint32 temp_branch_cnt;
      //float branch_cnt, branch_predicted_cnt;
    #endif

    uint32 coreid = RBSYS_getCoreID();

    // Increment execution counter
    RBSYS_PerformanceCounterMonitoringInfo[coreid].execution_cnt++;

    // Configure counters
    if(!RBSYS_PerformanceCounterMonitoringInfo[coreid].initialized)
    {
      #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        RBSYS_PC_SET_TYPE(0, PC_TYPE_INSTRUCTION);
        RBSYS_PC_SET_TYPE(1, PC_TYPE_INSTRUCTION_FETCH_REQ);
        RBSYS_PC_SET_TYPE(2, PC_TYPE_FLASH_INSTRUCTION_FETCH_REQ);
        RBSYS_PC_SET_TYPE(3, PC_TYPE_STALL_CYC);
        #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
          RBSYS_PC_SET_TYPE(4, PC_TYPE_CONDITIONAL_BRANCH_INSTRUCTION);
          RBSYS_PC_SET_TYPE(5, PC_TYPE_BRANCH_PREDICTION_MISSES);
        #endif
      #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
        // group 1
        RBSYS_MCR(15, 0, PC_TYPE_INST_RETIRED     , 14, 12, 0); //PMEVTYPER0
        RBSYS_MCR(15, 0, PC_TYPE_STALL_FRONTEND   , 14, 12, 1); //PMEVTYPER1
        RBSYS_MCR(15, 0, PC_TYPE_STALL_BACKEND    , 14, 12, 2); //PMEVTYPER2

        // group 2
        //RBSYS_MCR(15, 0, PC_TYPE_L1I_CACHE        , 14, 12, 0); //PMEVTYPER0
        //RBSYS_MCR(15, 0, PC_TYPE_KITE_IC_CACHE_HIT, 14, 12, 1); //PMEVTYPER1
        //RBSYS_MCR(15, 0, PC_TYPE_L1D_CACHE        , 14, 12, 2); //PMEVTYPER2
        //RBSYS_MCR(15, 0, PC_TYPE_KITE_DC_WT_HIT   , 14, 12, 3); //PMEVTYPER3

        // group 3
        //RBSYS_MCR(15, 0, PC_TYPE_BR_PRED   , 14, 12, 0); //PMEVTYPER0
        //RBSYS_MCR(15, 0, PC_TYPE_BR_RETIRED, 14, 12, 1); //PMEVTYPER1

        RBSYS_MCR(15, 0, (1u << 31) | (1u << 3) | (1u << 2) | (1u << 1) | 1u, 9, 12, 1); //PMCNTENSET
      #endif

      RBSYS_PerformanceCounterMonitoringInfo[coreid].initialized = true;
      RBSYS_PerformanceCounterMonitoringInfo[coreid].execution_cnt = EXECUTION_CNT_RESTART;
    }

    // Only calculate measurements and reset performance counter every 12th execution (120ms)
    if(RBSYS_PerformanceCounterMonitoringInfo[coreid].execution_cnt == EXECUTION_CNT_RESTART)
    {
      // Reset execution counter
      RBSYS_PerformanceCounterMonitoringInfo[coreid].execution_cnt = 0;

      // Stop counters
      #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        RBSYS_LDSR(TSCTRL_REG, TS_SEL, 0x0);
        RBSYS_PC_STOP(0);
        RBSYS_PC_STOP(1);
        RBSYS_PC_STOP(2);
        RBSYS_PC_STOP(3);
        #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
          RBSYS_PC_STOP(4);
          RBSYS_PC_STOP(5);
        #endif
      #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
        pmcr = RBSYS_MRC(15, 0, 9, 12, 0); //PMCR
        pmcr &= ~1;
        RBSYS_MCR(15, 0, pmcr, 9, 12, 0); //PMCR
      #endif

      // Read counter values, values that are used for division are read as integer to be able to check whether they are 0
      #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        temp_clk_cyc           = (uint64)RBSYS_STSR(TSCOUNTH_REG, TS_SEL) << 32;
        temp_clk_cyc          |= (uint64)RBSYS_STSR(TSCOUNTL_REG, TS_SEL);
        instr                  = (float) RBSYS_PC_GET_VALUE(0);
        temp_instr_fetch_req   =         RBSYS_PC_GET_VALUE(1);
        flash_instr_fetch_req  = (float) RBSYS_PC_GET_VALUE(2);
        stall_cyc              = (float) RBSYS_PC_GET_VALUE(3);
        #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
          temp_cond_branch_instr =         RBSYS_PC_GET_VALUE(4);
          branch_pred_misses     = (float) RBSYS_PC_GET_VALUE(5);
        #endif
      #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
        temp_clk_cyc       =         RBSYS_MRC(15, 0, 9, 13, 0); //PMCCNTR
        // group 1
        instruction_cnt    = (float) RBSYS_MRC(15, 0, 14, 8, 0); //PMEVCNTR0
        stall_frontend_cnt = (float) RBSYS_MRC(15, 0, 14, 8, 1); //PMEVCNTR1
        stall_backend_cnt  = (float) RBSYS_MRC(15, 0, 14, 8, 2); //PMEVCNTR2

        // group 2
        //temp_instruction_cache_access =         RBSYS_MRC(15, 0, 14, 8, 0); //PMEVCNTR0
        //instruction_cache_hit         = (float) RBSYS_MRC(15, 0, 14, 8, 1); //PMEVCNTR1
        //temp_data_cache_access        =         RBSYS_MRC(15, 0, 14, 8, 2); //PMEVCNTR2
        //data_cache_hit                = (float) RBSYS_MRC(15, 0, 14, 8, 3); //PMEVCNTR3

        // group 3
        //branch_predicted_cnt = (float) RBSYS_MRC(15, 0, 14, 8, 0); //PMEVCNTR0
        //temp_branch_cnt      =         RBSYS_MRC(15, 0, 14, 8, 1); //PMEVCNTR1
      #endif

      // Calculate metrics
      #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        if(temp_clk_cyc != 0)
        {
          clk_cyc = (float) temp_clk_cyc;
          // Instructions per cycle
          RBSYS_PerformanceCounterMetrics[coreid].ipc                        = instr / clk_cyc;
          // CPU stall rate
          RBSYS_PerformanceCounterMetrics[coreid].cpu_stall_rate             = stall_cyc / clk_cyc;
        }
        if(temp_instr_fetch_req != 0)
        {
          instr_fetch_req = (float) temp_instr_fetch_req;
          // Instruction cache hit rate
          RBSYS_PerformanceCounterMetrics[coreid].is_hit_rate                = 1.0f - (flash_instr_fetch_req / instr_fetch_req);
        }
        #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
          if(temp_cond_branch_instr != 0)
          {
            cond_branch_instr = (float) temp_cond_branch_instr;
            // Branch prediction hit rate
            RBSYS_PerformanceCounterMetrics[coreid].branch_prediction_hit_rate = (cond_branch_instr - branch_pred_misses) / cond_branch_instr;
          }
        #endif
      #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
        // group 1
        if(temp_clk_cyc != 0)
        {
          clk_cyc = (float) temp_clk_cyc;
          // Instructions per cycle
          RBSYS_PerformanceCounterMetrics[coreid].ipc                        = instruction_cnt / clk_cyc;
          // CPU stall rate
          RBSYS_PerformanceCounterMetrics[coreid].cpu_stall_rate_frontend    = stall_frontend_cnt / clk_cyc;
          RBSYS_PerformanceCounterMetrics[coreid].cpu_stall_rate_backend     = stall_backend_cnt / clk_cyc;
        }

        // group 2
        //if(temp_instruction_cache_access != 0)
        //{
        //  instruction_cache_access = (float) temp_instruction_cache_access;
        //  // Instruction cache hit rate
        //  RBSYS_PerformanceCounterMetrics[coreid].is_hit_rate                = instruction_cache_hit / instruction_cache_access;
        //}
        //if(temp_data_cache_access != 0)
        //{
        //  data_cache_access = (float) temp_data_cache_access;
        //  // Data cache hit rate
        //  RBSYS_PerformanceCounterMetrics[coreid].da_hit_rate                = data_cache_hit / data_cache_access;
        //}

        // group 3
        //if(temp_branch_cnt != 0)
        //{
        //  branch_cnt = (float) temp_branch_cnt;
        //  // Branch prediction hit rate
        //  RBSYS_PerformanceCounterMetrics[coreid].branch_prediction_hit_rate = branch_predicted_cnt / branch_cnt;
        //}
      #endif

      // Reset counter values and start counters
      #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        RBSYS_LDSR(TSCOUNTL_REG, TS_SEL, 0x0);
        RBSYS_LDSR(TSCOUNTH_REG, TS_SEL, 0x0);
        RBSYS_PC_SET_VALUE(0,0x0);
        RBSYS_PC_SET_VALUE(1,0x0);
        RBSYS_PC_SET_VALUE(2,0x0);
        RBSYS_PC_SET_VALUE(3,0x0);
        #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
          RBSYS_PC_SET_VALUE(4,0x0);
          RBSYS_PC_SET_VALUE(5,0x0);
        #endif

        RBSYS_LDSR(TSCTRL_REG, TS_SEL, 0x1);
        RBSYS_PC_START(0);
        RBSYS_PC_START(1);
        RBSYS_PC_START(2);
        RBSYS_PC_START(3);
        #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
          RBSYS_PC_START(4);
          RBSYS_PC_START(5);
        #endif
      #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
        pmcr = RBSYS_MRC(15, 0, 9, 12, 0); //PMCR
        pmcr |= (1u << 2) | (1u << 1);
        RBSYS_MCR(15, 0, pmcr, 9, 12, 0); //PMCR

        pmcr = RBSYS_MRC(15, 0, 9, 12, 0); //PMCR
        pmcr |= 1;
        RBSYS_MCR(15, 0, pmcr, 9, 12, 0); //PMCR
      #endif
    }
  }
#endif /* (RBFS_uCFamily_RenesasU2A || RBFS_uCFamily_STMStellar) && RBFS_SYSDebugFeatures_ON */

/** @} */
/* End ingroup RBSYS */
