#ifndef RBTPSW_TPSWCAPSULE_TIMERDRIVER_H__
#define RBTPSW_TPSWCAPSULE_TIMERDRIVER_H__

/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Third party software capsule - timer driver
 *
 * This internal API provides OS timer services for TPSW timing protection
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWCapsule,
                          RBFS_TPSWCapsule_OFF,
                          RBFS_TPSWCapsule_SC3,
                          RBFS_TPSWCapsule_SC4);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A);


#if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)

  /* HW specific implementations */
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    /* Renesas P1x */
    #include "RBTPSW_TPSWCapsule_TimerDriver_RenesasP1x.h"
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    /* Renesas U2A */
    #include "RBTPSW_TPSWCapsule_TimerDriver_RenesasU2A.h"
  #endif /* RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) */

#endif



/** @} */
/* End ingroup RBTPSW */

#endif /* End of multiple include protection */
