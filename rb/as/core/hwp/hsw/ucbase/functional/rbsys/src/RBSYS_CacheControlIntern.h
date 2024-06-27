#ifndef RBSYS_CACHECONTROLINTERN_H__
#define RBSYS_CACHECONTROLINTERN_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief RBSYS internal handling of instruction cache and data buffers
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


/* Assert supported configurations: switches, parameters, constants, ... */
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
  /**
   * @brief SW workaround for Renesas Errata RB113 (ID88) "WT-Buffer data overwrite"
   *
   * Under certain conditions it can happen that the WT-Buffer (Write-Through Buffer) does not update
   * it's content correctly, therefore a data corruption on Global RAM can occur. Therefore it's
   * necessary that the WT-Buffer is completely switched off on the affected device revisions.
   * For further details see Renesas Errata RB113 (ID88) "WT-Buffer data overwrite"
   *
   * @note But it's also important to call this function before CPU1 and other bus masters are enabled to avoid
   * further synchronization. It must be ensured that WT-Buffer mode is only changed while no other
   * bus master is accessing the GRAM [see further Renesas HW Errata RB120 (ID113)]. As an exception correct
   * operation will also be guaranteed if the following two conditions will be met:
   * (1) Only ICUM accesses the GRAM. Other masters do not access the GRAM.
   * (2) WT-Buffer is configured from "enable" to "disable".
   * This means it's not necessary to consider the ICUM (HSM) while disabling the WT-Buffer.
   *
   * @return void
   */
  extern void RBSYS_WTBufErrataHandling(void);
#endif



#if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))
  /**
   * @brief Disable instruction cache
   *
   * Since the instruction cache is not available on a D1 and D2 but on a D3ED-HW, it must be disabled for D1 and D2 emulated on a D3ED.
   *
   * @note The instruction cache applies only for code fetches from the Flash memory. It is not used for code fetches from the RAM.
   *
   * @return void
   */
  extern void RBSYS_DisableInstructionCache(void);
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
