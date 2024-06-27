#ifndef TRBSYS_PERFORMANCECOUNTER_ADAPTOR_H__
#define TRBSYS_PERFORMANCECOUNTER_ADAPTOR_H__

#include "Statistics/RBSYS_PerformanceCounter.h"
#include "RBSYS_Config.h"

#if(((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) || (RBFS_uCFamily == RBFS_uCFamily_STMStellar)) && RBFS_SYSDebugFeatures == RBFS_SYSDebugFeatures_ON)

  #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))

    // Register number (*_REG) and selection ID (*_SEL) of relevant system registers
    #define TRBSYS_TS_SEL              11
    #define TRBSYS_TSCOUNTL_REG        0           // Timestamp count L register
    #define TRBSYS_TSCOUNTH_REG        1           // Timestamp count H register
    #define TRBSYS_TSCTRL_REG          2           // Timestamp count control register

    #define TRBSYS_PMUMCTRL_SEL        11
    #define TRBSYS_PMUMCTRL_REG        8           // Performance counter User mode control register

    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      #define TRBSYS_PMCTRL_SEL        14
      #define TRBSYS_PMCTRLn_REG(n)    (n)          // Performance count control n register
      #define TRBSYS_PMCOUNT_SEL       14
      #define TRBSYS_PMCOUNTn_REG(n)   (16 + (n))   // Performance count n register
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      #define TRBSYS_PMCTRL_SEL        11
      #define TRBSYS_PMCTRLn_REG(n)    (17 + 2*(n)) // Performance count control n register
      #define TRBSYS_PMCOUNT_SEL       11
      #define TRBSYS_PMCOUNTn_REG(n)   (16 + 2*(n)) // Performance count n register
    #endif

    // Types of events that are possible to be counted
    #define TRBSYS_TYPE_CLK_CYC                         0x00  //Number of all clock cycles
    #define TRBSYS_TYPE_INSTRUCTION                     0x10  //Number of executions of all instructions
    #define TRBSYS_TYPE_BRANCH_INSTRUCTION              0x18  //Number of instructions that cause branch
    #define TRBSYS_TYPE_CONDITIONAL_BRANCH_INSTRUCTION  0x19  //Number of executions of conditional branch instructions (Bcond/Loop)
    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) //U2C does not support branch prediction
      #define TRBSYS_TYPE_BRANCH_PREDICTION_MISSES      0x1A  //Number of branch prediction misses of conditional branch instructions (Bcond/Loop)
    #endif
    #define TRBSYS_TYPE_EIINTN_ACC                      0x20  //Number of EIINTn acceptances
    #define TRBSYS_TYPE_FEINT_ACC                       0x21  //Number of FEINT acceptances
    #define TRBSYS_TYPE_TERMINATING_EXC_ACC             0x22  //Number of terminating type exception acceptances (including EIINTn and FEINT)
    #define TRBSYS_TYPE_RES_PEN_EXC_ACC                 0x23  //Number of resumable and pending type exception acceptances
    #define TRBSYS_TYPE_CLK_CYC_NO_INT                  0x28  //Number of clock cycles during no interrupt is processed (period during which the ISPR register holds 0000H)
    #define TRBSYS_TYPE_CLK_CYC_NO_INT_DISABLED         0x29  //Number of clock cycles during no interrupt is processed and interrupts are disabled (period during which the ISPR register holds 0000H*7 and PSW.ID = 1)
    #define TRBSYS_TYPE_INSTRUCTION_FETCH_REQ           0x30  //Number of instruction fetch requests
    #define TRBSYS_TYPE_INSTRUCTION_CACHE_HIT           0x31  //Number of instruction cache hits
    #define TRBSYS_TYPE_STALL_CYC                       0x40  //Number of stall cycles during which instructions are not issued to the instruction execution unit
    #define TRBSYS_TYPE_FLASH_INSTRUCTION_FETCH_REQ     0x50  //Number of instruction fetch requests to Flash ROM
    #define TRBSYS_TYPE_FLASH_DATA_READ_REQ             0x51  //Number of data read requests to Flash ROM

    // Helper macros as system register functions only work with constant expressions
    #define TRBSYS_PC_GET_TYPE(n)                       (RBSYS_STSR(TRBSYS_PMCTRLn_REG(n), TRBSYS_PMCTRL_SEL) >> 8)
    #define TRBSYS_PC_GET_VALUE(n)                      RBSYS_STSR(TRBSYS_PMCOUNTn_REG(n), TRBSYS_PMCOUNT_SEL)
    #define TRBSYS_PC_SET_VALUE(n, val)                 RBSYS_LDSR(TRBSYS_PMCOUNTn_REG(n), TRBSYS_PMCOUNT_SEL, val)
    #define TRBSYS_PC_IS_STARTED(n)                     RBSYS_STSR(TRBSYS_PMCTRLn_REG(n), TRBSYS_PMCTRL_SEL) & 0x1

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
  #define TRBSYS_EXECUTION_CNT_RESTART (12)

  RBSYS_PerformanceCounterMetrics_t TRBSYS_PerformanceCounterGetMetrics(unsigned int coreId);
  RBSYS_PerformanceCounterMonitoringInfo_t TRBSYS_PerformanceCounterGetMonitoringInfo(unsigned int coreId);

#endif

#endif