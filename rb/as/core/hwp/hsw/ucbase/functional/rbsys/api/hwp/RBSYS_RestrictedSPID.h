#ifndef RBSYS_RESTRICTEDSPID_H__
#define RBSYS_RESTRICTEDSPID_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Restricted SPID Handling
 *
 * This interface header provides possibility to modify the SPID of the host core to the Restricted SPID and back.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"




/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysExclusiveSPID,
                          RBFS_SysExclusiveSPID_Used,
                          RBFS_SysExclusiveSPID_NotUsed);



#if( RBFS_SysExclusiveSPID == RBFS_SysExclusiveSPID_Used )

  /**
   * @brief Set SPID (system protection identifier) of host core from "SafeSPID" to "RestrictedSPID"
   *
   * This "set" and the corresponing "reset" API shall only be called at least under core local lock
   * to suppress any kind of interruption.
   *
   * @note The SPID will only be changed on the core who is calling this API.
   *
   * @return void
   */
  extern void RBSYS_setCoreSPID2RestrictedSPID(void);

  /**
   * @brief Reset SPID (system protection identifier) of host core from "RestrictedSPID" to "SafeSPID"
   *
   * @note The SPID will only be changed on the core who is calling this API.
   *
   * @return void
   */
  extern void RBSYS_resetCoreSPID2SafeSPID(void);

#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
