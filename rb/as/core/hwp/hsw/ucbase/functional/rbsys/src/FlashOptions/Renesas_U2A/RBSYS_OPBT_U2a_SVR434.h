#ifndef RBSYS_OPBT_U2A_SVR434_H__
#define RBSYS_OPBT_U2A_SVR434_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief SVR434 configuration for HCUHEX file generation
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"

RB_ASSERT_SWITCH_SETTINGS(RBFS_uC,
                          RBFS_uC_RenesasD7,
                          RBFS_uC_RenesasD7onD7ED,
                          RBFS_uC_RenesasM2,
                          RBFS_uC_RenesasM2onM6ED,
                          RBFS_uC_RenesasM3,
                          RBFS_uC_RenesasM3onM6ED,
                          RBFS_uC_RenesasM6,
                          RBFS_uC_RenesasM6onM6ED);

#if( (RBFS_uC == RBFS_uC_RenesasD7onD7ED) \
  || (RBFS_uC == RBFS_uC_RenesasM2onM6ED) \
  || (RBFS_uC == RBFS_uC_RenesasM3onM6ED) \
  || (RBFS_uC == RBFS_uC_RenesasM6onM6ED) \
  )

  /* ATTENTION: When changing option byte values take care to update the option byte history for the option bytes check.
              Changes must be discussed with SiKo */

  //OPBT16 - SVR control
  #define c_SVRADNSMP      (0x12u)
  #define c_SVRAJDTP       (0x2u)
  #define c_SVRAJDTN       (0x2u)
  #define c_SVRAJPRDSR     (0xFu)
  #define c_SVRENABLE      (0x1u)

  //OPTB17 - SVR control
  #define c_SVRSWMODE      (0u)
  #define c_SVRMINSKIPDUTY (3u)
  #define c_SVRMAXDUTY     (0xFCu)
  #define c_SVRADTHRESH    (0x7Du)
  #define c_SVRADTHRESHE   (0xF9u)

  //OPBT18/19 - SVR PID parameter
  #define c_SVRKPVSCL      (0x046Fu)
  #define c_SVRKIVSCL      (0x05F1u)
  #define c_SVRKDVSCL      (0x04F0u)

#elif( (RBFS_uC == RBFS_uC_RenesasD7) \
    || (RBFS_uC == RBFS_uC_RenesasM6) )

  //OPBT16 - SVR control
  #define c_SVRADNSMP      (0x10u)
  #define c_SVRAJDTP       (0x2u)
  #define c_SVRAJDTN       (0x2u)
  #define c_SVRAJPRDSR     (0xFu)
  #define c_SVRENABLE      (0x1u)

  //OPTB17 - SVR control
  #define c_SVRSWMODE      (0u)
  #define c_SVRMINSKIPDUTY (3u)
  #define c_SVRMAXDUTY     (0xFCu)
  #define c_SVRADTHRESH    (0xAAu)
  #define c_SVRADTHRESHE   (0xF9u)

  //OPBT18/19 - SVR PID parameter
  #define c_SVRKPVSCL      (0x046Fu)
  #define c_SVRKIVSCL      (0x05F1u)
  #define c_SVRKDVSCL      (0x04F0u)

#elif( (RBFS_uC == RBFS_uC_RenesasM2) \
    || (RBFS_uC == RBFS_uC_RenesasM3) )

  //OPBT16 - SVR control
  #define c_SVRADNSMP      (0x10u)
  #define c_SVRAJDTP       (0x2u)
  #define c_SVRAJDTN       (0x2u)
  #define c_SVRAJPRDSR     (0xFu)
  #define c_SVRENABLE      (0x1u)

  //OPTB17 - SVR control
  #define c_SVRSWMODE      (0u)
  #define c_SVRMINSKIPDUTY (3u)
  #define c_SVRMAXDUTY     (0xFCu)
  #define c_SVRADTHRESH    (0xAAu)
  #define c_SVRADTHRESHE   (0xF9u)

  //OPBT18/19 - SVR PID parameter
  #define c_SVRKPVSCL      (0x098Eu)
  #define c_SVRKIVSCL      (0x1002u)
  #define c_SVRKDVSCL      (0x0883u)

#endif

#endif
