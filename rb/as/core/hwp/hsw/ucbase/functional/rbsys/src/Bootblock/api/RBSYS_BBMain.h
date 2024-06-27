#ifndef RBSYS_BBMAIN_H__
#define RBSYS_BBMAIN_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Branch to bootblock main
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "../../src/RBSYS_FSWStartup.h"     // forward "FSWStart" to bootblock


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysBootblockBuild,
                          RBFS_SysBootblockBuild_Active,
                          RBFS_SysBootblockBuild_NotActive);

RB_ASSERT_SWITCH_SETTINGS(RBFS_BootblockSysStartupCode,
                          RBFS_BootblockSysStartupCode_ON,
                          RBFS_BootblockSysStartupCode_OFF);



#if ( (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active) \
   && (RBFS_BootblockSysStartupCode == RBFS_BootblockSysStartupCode_ON) )

    /* callback declared in RBSYS and realized by bootblock */
    extern void RB_JumpToBBMain(void);

#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
