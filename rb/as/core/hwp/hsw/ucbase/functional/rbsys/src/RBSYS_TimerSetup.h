#ifndef RBSYS_TIMERSETUP_H__
#define RBSYS_TIMERSETUP_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Process header for System Timer initialization
 *
 * This interface contains for the System Timer initialization process an extern declaration.
 * The interface itself must be merged via header entry in RBSYS_Subsystem.proc with
 * mergeproc into final RBSYS_Dyn.c
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */


/* Assert supported configurations: switches, parameters, constants, ... */


extern void RBSYS_InitTimers(void);


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
