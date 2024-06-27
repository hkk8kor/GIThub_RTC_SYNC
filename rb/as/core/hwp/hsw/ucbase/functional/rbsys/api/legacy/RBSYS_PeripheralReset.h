#ifndef RBSYS_PERIPHERALRESET_H__
#define RBSYS_PERIPHERALRESET_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief CC-CUBE peripheral startup handling
 *
 * @deprecated Deprecated, do not use any longer! Use RBSYS_uCModuleEnable.h instead.
 *
 * Dependent on uC device, some peripherals must be switched from standby mode to run mode explicitly.
 * The strategy is to enable all available instances of the corresponding peripheral.
 * This must be done before first usage by the responsible SW part that owns the peripheral.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_uCModuleEnable.h"

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
