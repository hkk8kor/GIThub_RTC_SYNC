#ifndef RBSYS_RESETSYNC_H__
#define RBSYS_RESETSYNC_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file RBSYS_ResetSync.h
 * @brief Interfaces for Synchronization before SW Reset (interface towards RBECM)
 *
 * Any of these Interfaces may only be used by RBECM!!!
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);

#if( RBFS_MCORE == RBFS_MCORE_ON )

  /** 
   * @brief Interface for RuntimeSyncBarrier_Impl
   * 
   * Hint: "static inline" is optional. Is currently inlined because it is only used once
   * 
   * @param phase is the requested synchronization barrier
   * @return void
   */
  extern void RBSYS_RuntimeResetSyncBarrier(void);
  /* todo: remove whole file once this function is provided generically from MultiCoreSync */
  
  /**
   * @brief Trigger the preselected reset immediately from RBECM. 
   * 
   * Only to be called by one core. All other cores shall be stuck in infinite loop!
   * 
   * ATTENTION: Only to be used by RBECM for Synchronization Handshake before Reset!!!
   * Always consider asking the Component responsible regarding this interface!!
   */
  extern void RBSYS_ECMTriggerUCResetAfterCoreSync(void);

#endif

/** @} */
/* End ingroup RBSYS */

#endif //< multi-include-guard