#ifndef RBSYS_STARTUPTIMINGEXTERN_H__
#define RBSYS_STARTUPTIMINGEXTERN_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * \file
 * \brief Startup timing (external interface)
 *
 * This module provide time stamps for CC CUBE startup time measurement.
 * Due to the fact that uC internal system timer is used below hardware timings are not considered:
 *
 * HW Power Up:
 *  - uC reset release from ASIC                  max.  9 [ms]
 *  - uC BIST (including HW based RAM zeroing)    max. 22 [ms]
 *
 * Also bootblock runtime is not considered, because timer is re-initialized within application software.
 *
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */

typedef enum /*TOOL_SCAN*/
{
  RBSYS_TimestampBeforeCinit = 0,
  RBSYS_TimestampAfterCinit,
  RBSYS_TimestampBeforeSafety,
  RBSYS_TimestampAfterSafety,
  RBSYS_TimestampBeforeOS,
  RBSYS_MaxNumberOfStartupTimestamps
} RBSYS_StartupTimestamps_t;


/**
 * @brief RBSYS_StartupTimeStampInMicroSecs(RBSYS_StartupTimestamps_t phase)
 *
 * Official interface to retrieve timestamps taken during Sys-Startup (e.g. for TSI)
 *
 * @return uint32
 */

extern uint32 RBSYS_StartupTimeStampInMicroSecs(RBSYS_StartupTimestamps_t phase);



/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
