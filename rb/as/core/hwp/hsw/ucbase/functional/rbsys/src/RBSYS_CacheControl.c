/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Handling of instruction cache and data buffers
 *
 * - Instruction cache for Code Flash
 * - Data Buffer for Code Flash
 * - Write-Through Buffer for Global RAM
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_CpuVersions.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_uCRegisters.h"
#include "RBSYS_CpuVersions.h"  // RBSYS_CPU_REL_D3ED and RBSYS_CPU_REL_D5ED
#include "RB_MemoryBarrier.h"

/* realized interfaces */
#include "RBSYS_CacheControl.h"
#include "RBSYS_CacheControlIntern.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasP1xGRAM,
                          RBFS_RenesasP1xGRAM_ON,
                          RBFS_RenesasP1xGRAM_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                          RBFS_TargetDevice_RenesasD1,
                          RBFS_TargetDevice_RenesasD2,
                          RBFS_TargetDevice_RenesasD3,
                          RBFS_TargetDevice_RenesasD4,
                          RBFS_TargetDevice_RenesasD5,
                          RBFS_TargetDevice_RenesasD7,
                          RBFS_TargetDevice_RenesasM2,
                          RBFS_TargetDevice_RenesasM3,
                          RBFS_TargetDevice_RenesasM6,
                          RBFS_TargetDevice_RenesasK0,
                          RBFS_TargetDevice_RenesasK1,
                          RBFS_TargetDevice_STMP6);


#if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)

  /** Affected devices for Renesas Errata RB113 (ID88) "WT-Buffer data overwrite":
   *
   *  D3 (v1)     R7F701328, R7F701329, R7F701330, R7F701331, R7F701333
   *  D4 (v2)     R7F701327
   *  D3ED (v1)   R7F701334A
   *  D5ED (v2)   R7F701325A
   *
   *  D1onD3ED and D2onD3ED builds are not affected by this Errata,
   *  because only the XCP structures are allocated in GRAM and no further Bus-Master is accessing this content.
   */
   #if (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3)
    #define RBSYS_WTBUF_ERRATA_DEVICES                                        \
                                      ( RBSYS_CPU_REL_D3_LQFP144_DPS_V100 ||  \
                                        RBSYS_CPU_REL_D3_BGA292_DPS_V100  ||  \
                                        RBSYS_CPU_REL_D3_BGA292_EVR_V100  ||  \
                                        RBSYS_CPU_REL_D3_LQFP144_EVR_V100 ||  \
                                        RBSYS_CPU_REL_D3_HQFP144_EVR_V100 ||  \
                                        RBSYS_CPU_REL_D3ED_V100           ||  \
                                        RBSYS_CPU_REL_D5EDV2_V100             \
                                       )
  #elif (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4)
    #define RBSYS_WTBUF_ERRATA_DEVICES (RBSYS_CPU_REL_D5EDV2_V100)
  #elif (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5)
    #define RBSYS_WTBUF_ERRATA_DEVICES  RBSYS_CPU_REL_D5EDV2_V100
  #else
    #error ("Unsupported uC")
  #endif

  void RBSYS_WTBufErrataHandling(void)
  {
    if(RBSYS_WTBUF_ERRATA_DEVICES)
    {
      GRAMC_WTBCONFIG0 = 0x0;   // disable WT-Buffer
      (void)GRAMC_WTBCONFIG0;   // read necessary according to HW UM Rev.1.30 page 244
      RBSYS_SYNCP();            // ensure completion of previous write instruction (disabling WT-Buffer has been completed)
    }
  }

#endif



#if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))
  void RBSYS_DisableInstructionCache(void)
  {
    if(RBSYS_CPU_REL_D3ED || RBSYS_CPU_REL_D5ED)
    {
     /* Disable instruction cache in case of D1/D2-SW running on a D3ED or D5ED.
      * Detection during runtime is required, due to trace based failure analysis of a series D1/D2-SW on
      * an Emulation-Device
      */
      unsigned int icctrl = RBSYS_STSR(24, 4);    // read System register 24, 4 ICCTRL (Instruction cache control)

      icctrl &= 0xFFFFFFFEu;


      RBSYS_LDSR(24, 4, icctrl);                  // setting ICCTRL.ICHEN (bit0) to 0 disables the instruction cache.

      RBSYS_SYNCM();                              // ensure completion of write to icctrl
      RBSYS_SYNCI();                              // clear CPU instruction fetch pipeline so that subsequently executed instructions are re-fetched
    }
  }
#endif



#if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
  void RBSYS_flushWriteThroughBuffer(void)
  {
    RBSYS_SchM_Enter_CoreLocalLock();   // ensure no interruption between SYNCM and GRAMC_WTBCONFIG2

    RB_FullHardwareMemoryBarrier();                      // wait for completion of all previous data transfers

    /* Confirmed by GHS Compiler Team that below read from volatile location is never removed by the compiler
     * => see attached Email on ALM Task 1113970 */
    (void)GRAMC_WTBCONFIG2;             // when this register is read, all Write-Through Buffer entries are flushed

    RBSYS_SYNCP();                      // ensure completion of previous read instruction (flushing WT-Buffer has been completed)

    RBSYS_SchM_Exit_CoreLocalLock();
  }
#endif



#if(   (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) \
    )
  /* Hint: Currently, no functionality requires invalidating the Instruction Cache. Could e.g. by required for
   * self-programming and execution.
   *
   * - add timeout monitoring for clearing cache:
   *    ICCTRL Register: "ICHCLR Setting this bit to 1 selects clearing of the whole instruction cache in a single operation.
   *    After this bit has been set to 1, it will be read as 1 until clearing is completed. The bit is cleared to 0 once
   *    clearing of the cache is completed." We requested from Renesas the worst case timing for clearing the whole cache!
   */
  void RBSYS_invalidateInstructionCache(void)
  {
    /* instruction cache is core related and therefore core specific lock recommended - it ensures no further writer to ICCTRL register */
    RBSYS_SchM_Enter_CoreLocalLock();

    {
      unsigned int icctrl = RBSYS_STSR(24, 4);    // read System register 24, 4 ICCTRL (Instruction cache control)

      icctrl |= 0x00000100u;


      RBSYS_LDSR(24, 4, icctrl);                  // setting ICCTRL.ICHCLR (bit8) to 1 selects clearing of the whole instruction cache in a single operation.

      RBSYS_SYNCM();                              // ensure that ICCTRL has been written
      RBSYS_SYNCI();                              // clear CPU instruction fetch pipeline so that subsequently executed instructions are re-fetched

      do
      {
        icctrl = RBSYS_STSR(24, 4);
      }
      while ((icctrl & 0x00000100u) != 0);        // wait until clearing is completed (see P1x UM Rev. 1.30 Chapter 3.4.8)
    }

    RBSYS_SchM_Exit_CoreLocalLock();
  }

  /* Hint: This function is not implemented for U2C. If required, you have to consider that the DataBuffer is used additionally by 
   * the Instruction Cache (e.g. if reading from CodeFlash). */
#endif


#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

  void RBSYS_clearDataBuffer(void)
  {
    /* code flash data buffer is core related and therefore core specific lock recommended - it ensures no further writer to cdbcr register */
    RBSYS_SchM_Enter_CoreLocalLock();

    /* ensure that all previous load operations are finished before writing to the Data Buffer Control Register */
    RBSYS_SYNCP();

    {
      unsigned int cdbcr = RBSYS_STSR(24, 13);  // get Data Buffer Control Register (P1x:CDBCR - U2A / U2C:RDBCR)

      cdbcr |= 0x2u;                            // set CDBCR.CDBCLR (P1x) / RDBCR.RDBCLR (U2A, U2C) to clear the data buffer

      RBSYS_LDSR(24, 13, cdbcr);
    }

    RBSYS_SYNCM();                              // Ensure that CDBCR has been written
    RBSYS_SYNCI();                              // Flush Instruction Pipeline (fetch through data buffer has to be renewed)

    RBSYS_SchM_Exit_CoreLocalLock();
  }

#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  /* Write Back is not required, because D$ is only used on Program Flash -> see RBSYS_registerInit() */
  void RBSYS_invalidateDataCache(void)
  {
    /* code flash data cache is core related and therefore core specific lock recommended - it ensures no further writer to dcisw register */
    RBSYS_SchM_Enter_CoreLocalLock();
    RBSYS_DSB(); // Complete all write accesses to Cache configuration registers

    {
      /* DataCache is invalidated by Set/Way - there is no option to invalidate all entries at once */
      uint32 ccsidr, numOfSets, numOfWays, set, way;

      RBSYS_MCR(15,2,0x00000000u,0,0,0); // CSSELR.InD = 0 (Select Data Cache for Cache Size Register CCSIDR)

      ccsidr = RBSYS_MRC(15,1,0,0,0);

      numOfSets = ((ccsidr >> 13) & 0x7FFF) + 1;
      numOfWays = 4u;
      /*< ARM Cortex R52 does always implement 4 Cache Ways (see ARM R52 Technical RM 100026_0101_00_en) */

      for( way=0; way<numOfWays; way++ )
      {
        for( set=0; set<numOfSets; set++ )
        {
          /* DCISW Instruction:
           *   from R52 Reference Manual:
           *     Associativity:  0x3  => The cache has four ways.      => A = log2(Associativity) = 2 (rounded up)
           *     Line size:      0x3  => 16 words (64B) per cache line => L = log2(LineSize=64)   = 6
           *     Number of Sets: 0x7F => 128 sets per way              => S = log2(NumSets)       = 7 (rounded up)
           *   Which leads to the following encoding of DCISW:
           *     [31:32-A] => [31:30] = Way
           *     [L+S-1:L] => [12:6]  = Set
           */
          uint32 dcisw_command = ((way << 30) | (set << 6));
          RBSYS_MCR(15, 0, dcisw_command, 7, 6, 2);
        }
      }
    }

    RBSYS_DSB(); // Complete all write accesses to Cache configuration registers
    RBSYS_SchM_Exit_CoreLocalLock();
  }

#endif

/** @} */
/* End ingroup RBSYS */
