#ifndef OSSTUB_OS_CONFIG_H__
#define OSSTUB_OS_CONFIG_H__

/**
 * @ingroup OSStub
 * @{
 *
 * @file OSStub_Os_Config.h
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"
#include <string.h> // for memcpy()

#include "HSim_Global.h" // standard types
#include "RBSYSStub_Tasks.h" // defines the process type PRC_PTR and the tables
#include "RBSYSStub_EntryPoint.h" // TODO: defines the AppModeType should be moved to OSStub header.

#include "OSStub_Internal.h" ///< realize
#include "RBSYS_OSServices.h"

#include "../../../../../../../tools/sim/HSim/SWStub/SWStub_Init.h" ///< Init-Routine of SWStub
#include "RBSYS_ClockSettings.h" ///< for RBSYS_ECLK_DEFAULT_KHZ

#include "RBSYS_PlantStartupCtrl.h" ///< RBMESG_RBMESG_RBSYSPlantModeRequest
#include "RBSYS_RAMBackupServiceIntern.h" ///< restoreBaseOSRequest

#include "HSWSim_MeasurementForOSSim.h"
#include "OSStub_DynamicProcessList.h"
#include "Gresh_ResetHandler.h" // for ResetHandler_IsResetRequested

#endif