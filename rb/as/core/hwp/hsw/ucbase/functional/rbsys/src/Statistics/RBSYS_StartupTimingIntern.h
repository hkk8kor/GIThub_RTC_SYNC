#ifndef RBSYS_STARTUPTIMINGINTERN_H__
#define RBSYS_STARTUPTIMINGINTERN_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * \file
 * \brief Startup timing (internal interface)
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
#include "RBSYS_StartupTimingExtern.h"

typedef enum /*TOOL_SCAN*/
{
  RBSYS_TimestampInitTask = 0,
  RBSYS_TimestampInitTaskP,
  RBSYS_MaxNumberOfInitTaskTimestamps,
} RBSYS_InitTaskTimestamps_t;

extern void RBSYS_SetStartupTimestamp(RBSYS_StartupTimestamps_t phase);
extern void RBSYS_SetInitTaskTimestamp(RBSYS_InitTaskTimestamps_t task);



/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
