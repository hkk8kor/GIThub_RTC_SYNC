#ifndef RBSYS_BOOTBLOCK_STARTUP_H__
#define RBSYS_BOOTBLOCK_STARTUP_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief RBSYS related start-up code for bootblock
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysBootblockBuild,
                          RBFS_SysBootblockBuild_Active,
                          RBFS_SysBootblockBuild_NotActive);


#if (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active)
  extern void RBSYS_BBStartupPreOSPhase0(void);
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
