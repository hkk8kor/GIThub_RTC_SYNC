#ifndef RBTPSW_TPSWCAPSULE_EXCHANDLER_H__
#define RBTPSW_TPSWCAPSULE_EXCHANDLER_H__

/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Third party software capsule - exception handler
 *
 * This module provides the exception handling for the TPSW framework
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* used interfaces */


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTPSWSupport,
                          RBFS_SysTPSWSupport_YES,
                          RBFS_SysTPSWSupport_NO);

#if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)

  /* HW specific implementations */
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    /* Renesas P1x */
    #include "RBTPSW_TPSWCapsule_ExcHandler_RenesasP1x.h"
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    /* Renesas U2A */
    #include "RBTPSW_TPSWCapsule_ExcHandler_RenesasU2A.h"
  #else
    #error ("TPSW Environment is not supported for the specified RBFS_uCFamily.")
  #endif /* RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) */

#endif  /* (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES) */


#endif /* End of multiple include protection */
