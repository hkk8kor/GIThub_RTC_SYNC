#ifndef RBSYS_BBSTACKHANDLING_H__
#define RBSYS_BBSTACKHANDLING_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Stack handling for bootblock
 *
 * Stack handling and allocation of bootblock software. Stack size must be a part of project specific configuration.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBLCF_MemoryRemap.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysBootblockBuild,
                          RBFS_SysBootblockBuild_Active,
                          RBFS_SysBootblockBuild_NotActive);



#if (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active)

  /* forwarded header for "RBSYS_stackInit" function */
  #include "../../Monitorings/RBSYS_StackHandling.h"


  RBSECTION_START_SECTTYPE_NO_SDA
  extern volatile unsigned int* const RB_SP0_Bootblock;
  extern volatile unsigned int* const RB_SP1_Bootblock;
  RBSECTION_END_SECTTYPE_NO_SDA

#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
