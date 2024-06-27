/****************************************************************************/
/* Multiple include protection. Define symbol like following pattern:       */
#ifndef RBDET_CONFIGSETTINGS_H__
#define RBDET_CONFIGSETTINGS_H__

/**********************************************************************************/
/* [COPYRIGHT]                                                                    */
/* Robert Bosch GmbH reserves all rights even in the event of industrial          */
/* property rights. We reserve all rights of disposal such as copying and         */
/* passing on to third parties.                                                   */
/* [COPYRIGHT_END]                                                                */
/**********************************************************************************/

#include "rb/as/core/app/dsm/rbdet/api/RBDET_ConfigElements.h"

/****************************************************************************/
/* Include here interfaces that are necessary for this interface but may    */
/* not be used in modules.                                                  */
/* PRIVATE_INTERFACES:                                                      */
/*                                                                          */
/*                                                                          */
/* PRIVATE_INTERFACES_END:                                                  */
/****************************************************************************/



/****************************************************************************/
/* Include here interfaces that are generalized by this interface and that  */
/* are public for usage in this AND other modules.                          */
/* PUBLIC_INTERFACES:                                                       */
/*                                                                          */

/*                                                                          */
/* PUBLIC_INTERFACES_END:                                                   */
/****************************************************************************/



/****************************************************************************/
/* Check here used switches.                                                */
/* USED_SWITCHES:                                                           */
/*                                                                          */

/*                                                                          */
/* USED_SWITCHES_END:                                                       */
/****************************************************************************/



/****************************************************************************/
/* Write here all settings which are supported by this module.              */
/* For other settings GenProdDb aborts.                                     */
/* SUPPORTED_SWITCH_SETTINGS:                                               */
/* RBFS_DETReportError_Standard,RBFS_DETReportError_Project,RBFS_DETReportError_OFF */
/*                                                                          */
/* SUPPORTED_SWITCH_SETTINGS_END:                                           */
/****************************************************************************/
/* ------------------------------------------------------------------------ */
/* RBFS_DETReportError                                                      */
/* ------------------------------------------------------------------------ */
#ifndef RBFS_DETReportError
#ifdef RBFS_BUILDTYPE // MTC 10.0.8.0 or higher
#if (RBFS_BUILDTYPE == RBFS_BUILDTYPE_RELEASE)
#define RBFS_DETReportError RBFS_DETReportError_OFF
#else   // DEVELOPMENTBUILD
#define RBFS_DETReportError RBFS_DETReportError_Standard
#endif  // End of (RBFS_BUILDTYPE == RBFS_BUILDTYPE_RELEASE)
#else   // RBFS_BUILDTYPE not defined
#define RBFS_DETReportError RBFS_DETReportError_Standard
#endif  // End of RBFS_BUILDTYPE
#endif  // End of RBFS_DETReportError

#endif/* End of multiple include protection                                */
/****************************************************************************/
