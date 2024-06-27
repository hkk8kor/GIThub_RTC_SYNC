/// @file rbl_SigChain_ConfigSettings.h
/// @brief ConfigSettings for the Signal Chain
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_SIGCHAIN_CONFIGSETTINGS_H_
#define RBL_SIGCHAIN_CONFIGSETTINGS_H_

#include "rbl_SigChain_ConfigElements.h"

#define RBFS_SigChainCorrln RBFS_SigChainCorrln_OFF

#define RBFS_SigChainMounting RBFS_SigChainMounting_OFF

// todo: make dependend on SW Build
#define RBFS_SigChainChMap RBFS_SigChainChMap_3SMU
//#define RBFS_SigChainChMap RBFS_SigChainChMap_4SMU


#if (RBFS_NvmBasedFilter == RBFS_NvmBasedFilter_ON)
#define RBFS_SigChainFilter RBFS_SigChainFilter_Nvm
#define RBFS_SigChainFilter2 RBFS_SigChainFilter2_Nvm

#define RBFS_SigChainNoFilter RBFS_SigChainNoFilter_Available
#define RBFS_SigChain20HzFilter RBFS_SigChain20HzFilter_Available
#define RBFS_SigChain45HzFilter RBFS_SigChain45HzFilter_Available

#else
// filter settings for hardcoded filters


// is the no Filter configured on Filter 1
#if (RBFS_FilterCharacteristic == RBFS_FilterCharacteristic_NoFilter)
#define RBFS_SigChainFilter RBFS_SigChainFilter_NoFilter
#define RBFS_SigChainNoFilter RBFS_SigChainNoFilter_Available
#else
#define RBFS_SigChainNoFilter RBFS_SigChainNoFilter_None
#endif

// is the 20 hz filter active (currently only supported on filter 1)
#if (RBFS_FilterCharacteristic == RBFS_FilterCharacteristic_Filter20Hz)
#define RBFS_SigChainFilter RBFS_SigChainFilter_20Hz
#define RBFS_SigChain20HzFilter RBFS_SigChain20HzFilter_Available
#else
#define RBFS_SigChain20HzFilter RBFS_SigChain20HzFilter_None
#endif

// is the 45 filter active (currently possible on both filters)
#if (RBFS_FilterCharacteristic == RBFS_FilterCharacteristic_Filter45Hz) || (RBFS_Filter2Characteristic == RBFS_Filter2Characteristic_FilterFreq45Hz)
#define RBFS_SigChain45HzFilter RBFS_SigChain45HzFilter_Available
// filter 1
#if (RBFS_FilterCharacteristic == RBFS_FilterCharacteristic_Filter45Hz)
#define RBFS_SigChainFilter RBFS_SigChainFilter_45Hz
#endif
//filter 2
#if (RBFS_Filter2Characteristic == RBFS_Filter2Characteristic_FilterFreq45Hz)
#define RBFS_SigChainFilter2 RBFS_SigChainFilter2_45Hz
#endif
#else // neither is configured as 45hz
#define RBFS_SigChain45HzFilter RBFS_SigChain45HzFilter_None
#endif

#if (RBFS_Filter2Characteristic == RBFS_Filter2Characteristic_NoFilter2)
#define RBFS_SigChainFilter2 RBFS_SigChainFilter2_NoFilter
#endif

#endif

#endif
