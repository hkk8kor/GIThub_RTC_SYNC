#ifndef RBSYS_RTEOSSERVICES_H__
#define RBSYS_RTEOSSERVICES_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief RTE OS services
 *
 * RBSYS specific abstraction of OS services for RTE
 * These services are not supported outside of application software

 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

/*
 * There should be no other include of interfaces then Os.h within this file!
 * Otherwise all this interface must also be visible via GenExSW for software sharing with RTE.
 */
#include "Os.h"



/* RTE resource only allowed for RTE - all other users shall use common lock.
 * Resource blocks all Tasks and ISRs and therefore blocking time must be less than 50usec (same as for common lock)
 * no monitoring up to now - therefore lock time must be guaranteed by user
 * implements normal OS resource functionality (i.e. no nesting allowed, core-specific, ...)
 *
 * No direct use of OS service allowed -> encapsulated service via this RBSYS wrapper (=> provides the possibility for impl. a monitoring)
 */
#define RBSYS_RTE_RESOURCE_CORE0             OS_RTE_RESOURCE_CORE0
#define RBSYS_RTE_RESOURCE_CORE1             OS_RTE_RESOURCE_CORE1

static inline void RBSYS_GetOSResource(ResourceType ResID)
{
  (void)GetResource(ResID);
}
static inline void RBSYS_ReleaseOSResource(ResourceType ResID)
{
  (void)ReleaseResource(ResID);
}



/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
