#ifndef RBSYS_OPBT_U2A_SVROFF_H__
#define RBSYS_OPBT_U2A_SVROFF_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Disabled SVR configuration for HCUHEX file generation
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#error "Unsupported Config"

#include "RBSYS_Config.h"

/* ATTENTION: When changing option byte values take care to update the option byte history for the option bytes check.
              Changes must be discussed with SiKo */

//OPBT16 - SVR control
#define c_SVRADNSMP      (0xFF)
#define c_SVRAJDTP       (0x7)
#define c_SVRAJDTN       (0x7)
#define c_SVRAJPRDSR     (0xF)
#define c_SVRENABLE      (0x0)

//OPTB17 - SVR control
#define c_SVRSWMODE      (0x3)
#define c_SVRMINSKIPDUTY (0x3)
#define c_SVRMAXDUTY     (0xFF)
#define c_SVRADTHRESH    (0xFF)
#define c_SVRADTHRESHE   (0xFF)

//OPBT18/19 - SVR PID parameter
#define c_SVRKPVSCL      (0x3FFF)
#define c_SVRKIVSCL      (0x3FFF)
#define c_SVRKDVSCL      (0x3FFF)

#endif
