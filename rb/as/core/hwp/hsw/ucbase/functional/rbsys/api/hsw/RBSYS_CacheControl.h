#ifndef RBSYS_CACHECONTROL_H__
#define RBSYS_CACHECONTROL_H__

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
 * To fulfil our safety requirements it could be necessary to invalidate the instruction cache,
 * clear the data buffer or to flush the WT-Buffer to ensure an access from real memory.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_Intrinsics.h"
#include "RBSYS_uCRegisters.h"


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



/**
 * Instruction cache and data buffers:
 *
 * Instruction cache for Code Flash (not available on D1 and D2):
 * The RH850 cores are equipped with an instruction cache. This means all CPU instruction fetches
 * from the Code Flash are performed via the instruction cache. There is no data cache for RAM,
 * so there is no need for write-policy or cache coherence logic.
 *
 * Instruction cache error reporting to ECM:
 * Instruction cache automatically invalidates the entry which includes an error and the CPU continues the
 * instruction execution by refetching from the code flash. ICCTRL register bit 1 - ICHEMK:
 * "Setting this bit to 1 selects masking of cache error exception notifications for
 * the CPU when cache errors are encountered." Renesas confirmed here that cache errors are always reported to ECM.
 * This bit will mask only system exception generation to the CPU.
 *
 * Data Buffer for Code Flash:
 * Each CPU has its own data buffer to reduce data fetch latency from Code Flash memory.
 *   Renesas P1x-C family: The data buffer (DBUF) consists of 4 entries with 64 bits.
 *   Renesas U2A family: The data buffer consists of 4 lines with 256 bits per line.
 *   Renesas U2C family: The data buffer consists of 2 lines with 256 bits per line.
 *
 * Write-Through Buffer for Global RAM (Renesas P1x-C only):
 * Since one WT-Buffer is shared for both cores, no coherency control is needed. The data
 * coherency between GRAM and WT-Buffer is always kept because the same data is always written to
 * GRAM and WT-Buffer at the same time. The data coherency between CPUs and other bus masters like DMA
 * is also kept, as DMA writes to GRAM as well as WT-Buffer at the same time and DMA always reads
 * from GRAM not from WT-Buffer.
 */



#if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
  /**
   * @brief Flush Write-Through Buffer of GRAM
   *
   * Due to the fact, that one common buffer is shared for both CPUs no coherence control is needed. The data coherence between GRAM
   * and WT-Buffer is always kept because the same data is always written to GRAM and WT-Buffer at the same time. The data coherence
   * between CPUs and DMA is also kept, as DMA writes to GRAM as well as WT-Buffer at the same time and DMA always reads from GRAM not
   * from WT-Buffer.
   *
   * @note It's only important for safety tests to invalidate the WT-Buffer to ensure real accesses from GRAM!
   *
   * @note Sequence agreed from Renesas (see Mantis issue 799 within CC-Cube DeviceSupport)
   *
   * @return void
   */
  extern void RBSYS_flushWriteThroughBuffer(void);
#endif



#if(   (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) \
    )
  /**
   * @brief Invalidate instruction cache
   *
   * This function call will invalidate core specific the whole instruction cache and does not return until
   * the cache is completely cleared. Due to big performance impact this function may only be called
   * if required by safety issues (e.g. ensure instructions are executed out of Flash and not from cache).
   *
   * @note The instruction cache applies only for code fetches from the Flash memory. It is not used for code fetches from the RAM.
   *
   * @return void
   */
  extern void RBSYS_invalidateInstructionCache(void);
#endif


#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  /**
  * @brief Clear Code Flash Data Buffer
  *
  * This function will clear the core specific code flash data buffer.
  *
  * @return void
  */
  extern void RBSYS_clearDataBuffer(void);
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  /**
  * @brief Invalidate Code Flash Data Cache
  *
  * This function will clear the core specific code flash data cache.
  *
  * @return void
  */
  extern void RBSYS_invalidateDataCache(void);
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
