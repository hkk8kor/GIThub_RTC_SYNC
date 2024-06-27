#ifndef RBSYS_OPBT_U2C_SVR434_H__
#define RBSYS_OPBT_U2C_SVR434_H__

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
                          RBFS_uC_RenesasK0,
                          RBFS_uC_RenesasK0onK3ED,
                          RBFS_uC_RenesasK1,
                          RBFS_uC_RenesasK1onK3ED);

#if( (RBFS_uC == RBFS_uC_RenesasK0onK3ED) \
  || (RBFS_uC == RBFS_uC_RenesasK1onK3ED) \
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

#elif(RBFS_uC == RBFS_uC_RenesasK1)

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

#elif(RBFS_uC == RBFS_uC_RenesasK0)

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
