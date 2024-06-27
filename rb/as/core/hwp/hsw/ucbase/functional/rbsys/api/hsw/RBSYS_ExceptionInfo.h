#ifndef RBSYS_EXCEPTIONINFO_H__
#define RBSYS_EXCEPTIONINFO_H__


/**
 * @ingroup RBSYS
 * @{
 *
 * \file
 * \brief RBSYS exception handler
 *
 * RBSYS exception handler provides with this interface a possibility to modify the return address together with
 * the corresponding PSW of the exception, which is required for some special safety tests.

 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  extern uint32 RBSYS_ExceptionHandler_GetExceptionProgramCounterForDebug(void);
#endif




/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
