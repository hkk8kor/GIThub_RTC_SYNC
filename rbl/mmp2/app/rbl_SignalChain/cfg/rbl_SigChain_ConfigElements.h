/// @file rbl_SigChain_ConfigElements.h
/// @brief config elements for the signal chain
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_SIGCHAIN_CONFIGELEMENTS_H__
#define RBL_SIGCHAIN_CONFIGELEMENTS_H__

/// no correlation monitor
#define RBFS_SigChainCorrln_OFF 1
/// correlation monitor
#define RBFS_SigChainCorrln_ON  2

/// no mounting correction
#define RBFS_SigChainMounting_OFF 1

/// flexible channel mapping (plant software)
#define RBFS_SigChainChMap_Flex 1

/// fixed channel mapping (customer software)
#define RBFS_SigChainChMap_3SMU 2

/// fixed channel mapping (customer software)
#define RBFS_SigChainChMap_3SMU2SMI 3

/// fixed channel mapping (old platform)
#define RBFS_SigChainChMap_4SMU 4


// Filter 1
// No Filter selected
#define RBFS_SigChainFilter_NoFilter 1

//20Hz Filter
#define RBFS_SigChainFilter_20Hz 2

//45Hz Filter
#define RBFS_SigChainFilter_45Hz 3

//Filter is not fixed, but from Nvm
#define RBFS_SigChainFilter_Nvm 4

// Filter 2
// No Filter selected
#define RBFS_SigChainFilter2_NoFilter 1

//20Hz Filter
#define RBFS_SigChainFilter2_20Hz 2

//45Hz Filter
#define RBFS_SigChainFilter2_45Hz 3

//Filter is not fixed, but from Nvm
#define RBFS_SigChainFilter2_Nvm 4

//setting for availability of hardcoded values in the code

#define RBFS_SigChain20HzFilter_Available 1

#define RBFS_SigChain20HzFilter_None 2

#define RBFS_SigChain45HzFilter_Available 1

#define RBFS_SigChain45HzFilter_None 2

#define RBFS_SigChainNoFilter_Available 1

#define RBFS_SigChainNoFilter_None 2

#endif
