#ifndef RBSYS_BBFSW_JUMP_H__
#define RBSYS_BBFSW_JUMP_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Branch from bootblock to application software
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

RB_ASSERT_SWITCH_SETTINGS(RBFS_BootblockSysStartupCode,
                          RBFS_BootblockSysStartupCode_ON,
                          RBFS_BootblockSysStartupCode_OFF);


#if ( (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active) \
   && (RBFS_BootblockSysStartupCode == RBFS_BootblockSysStartupCode_ON) )
  extern void RBSYS_BBJumpToApplication(void);
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
