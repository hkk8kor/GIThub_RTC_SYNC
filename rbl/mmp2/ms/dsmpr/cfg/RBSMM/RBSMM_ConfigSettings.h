#ifndef RBSMM_CONFIGSETTINGS_H__
#define RBSMM_CONFIGSETTINGS_H__

/**********************************************************************************/
/* [COPYRIGHT]                                                                    */
/* Robert Bosch GmbH reserves all rights even in the event of industrial          */
/* property rights. We reserve all rights of disposal such as copying and         */
/* passing on to third parties.                                                   */
/* [COPYRIGHT_END]                                                                */
/**********************************************************************************/

#include "rb/as/core/app/dsm/RBSMM/api/RBSMM_ConfigElements.h"

/*----------------------------------------------------------------------------*/
/* for all settings definition see RBSMM_ConfigElements.cfg */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* RBFS_SystemModeManagerForceImmediateShutdown */
/*----------------------------------------------------------------------------*/
#ifndef RBFS_SMMForceImmediateShutdown
#define RBFS_SMMForceImmediateShutdown RBFS_SMMForceImmediateShutdown_No
#endif

/*----------------------------------------------------------------------------*/
/* RBFS_SMMOneRequestsInitMonitoring */
/*----------------------------------------------------------------------------*/
#ifndef RBFS_SMMOneRequestsInitMonitoring
#ifdef RBFS_BUILDTYPE // MTC 10.0.8.0 or higher
#if (RBFS_BUILDTYPE == RBFS_BUILDTYPE_RELEASE)
#define RBFS_SMMOneRequestsInitMonitoring RBFS_SMMOneRequestsInitMonitoring_No
#else  // DEVELOPMENTBUILD
#define RBFS_SMMOneRequestsInitMonitoring RBFS_SMMOneRequestsInitMonitoring_Yes
#endif // End of (RBFS_BUILDTYPE == RBFS_BUILDTYPE_RELEASE)
#else  // RBFS_BUILDTYPE not defined
#define RBFS_SMMOneRequestsInitMonitoring RBFS_SMMOneRequestsInitMonitoring_Yes
#endif // End of RBFS_BUILDTYPE
#endif // End of RBFS_SMMOneRequestsInitMonitoring

#endif
