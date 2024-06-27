#ifndef RBVOLTAGEHANDLER_CONFIGSETTINGS_H__
#define RBVOLTAGEHANDLER_CONFIGSETTINGS_H__

/**********************************************************************************/
/* [COPYRIGHT]                                                                    */
/* Robert Bosch GmbH reserves all rights even in the event of industrial          */
/* property rights. We reserve all rights of disposal such as copying and         */
/* passing on to third parties.                                                   */
/* [COPYRIGHT_END]                                                                */
/**********************************************************************************/

#include "rb/as/core/app/dsm/RBVoltageHandler/api/RBVoltageHandler_ConfigElements.h"

#if (RBFS_HydrActSystem != RBFS_HydrActSystem_Unused) //  currently no logic for iBooster systems

/* ------------------------------------------------------------------------ */
/* RBFS_VoltageSupplyMonitoringSupportHysteresis                            */
/* ------------------------------------------------------------------------ */
#define RBFS_VoltageSupplyMonitoringSupportHysteresis   RBFS_VoltageSupplyMonitoringSupportHysteresis_Time
/*DG|Konfigurationsschalter für hysterese spannung bei Fehlerheilung|*/
/*DE|Configuration switch for hysteresis voltage|*/


/* ------------------------------------------------------------------------ */
/* RBFS_VoltageSupplyMonitoringUseDefaultParameter                          */
/* ------------------------------------------------------------------------ */
#define RBFS_VoltageSupplyMonitoringUseDefaultParameter   RBFS_VoltageSupplyMonitoringUseDefaultParameter_No
/*DG|Konfigurationsschalter zur Auswahl der Parameter, entweder projekt spzifisch oder mainstream default|*/
/*DE|Configuration switch for parameter choice, default mainstream or project defined|*/

#endif // EP, IPB only
#endif
