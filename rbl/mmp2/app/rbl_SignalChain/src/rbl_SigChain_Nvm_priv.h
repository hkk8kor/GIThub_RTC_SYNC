/// @file 
/// @brief internal nvm header, functions may NOT be used by other components
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef RBL_SIGCHAIN_NVM_PRIV_H
#define RBL_SIGCHAIN_NVM_PRIV_H

#include "Nvm.h"

/* --------------------- nvm valid marker, written during init ---------------------------------*/

/// nvm valid marker
extern boolean rbl_SigChain_AlgnAccSnvtyNvmVld;
/// nvm valid marker
extern boolean rbl_SigChain_Algn_RateSnvtyNvmVld;

#if (RBFS_NvmBasedFilter == RBFS_NvmBasedFilter_ON)
extern boolean rbl_SigChain_SigFilNvmVld;
/// nvm valid marker
extern uint8 rbl_SigChain_PickFilValue[2];
#endif
/// @c_file rbl_SigChain_Nvm.c

/// @pre called by pdm item specific read callback function. ServiceId must be NVM_SERVICE_ID_READ_ALL
/// @param[in] ServiceId
/// @param[in] JobResult
///
/// @return boolean true if JobResult is NVM_REQ_OK

/// @details wrapper for nvm read callbacks, to get a TRUE if the NVM item was read successfully.

boolean rbl_SigChain_NvmValidCheck(uint8 ServiceId, NvM_RequestResultType JobResult);


/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre checked during init phase
/// @return boolean true if all nvm items are valid
/// @details as the values needed for the TCO and TCS correction are in several array, it is checked, if all members in all arrays are TRUE
/// the arrays that are checked are
/// * @ref rbl_SigChain_TCSAccVld
/// * @ref rbl_SigChain_TCOAccVld
/// * @ref rbl_SigChain_TCSRateVld
/// * @ref rbl_SigChain_TCORateVld
boolean rbl_SigChain_TCOSAllNvmItemsValid(void);

#if (RBFS_NvmBasedFilter == RBFS_NvmBasedFilter_ON)

#define RBL_SIGCHAIN_NOFILTER          0x0000U
#define RBL_SIGCHAIN_20HZFILTER        0x0001U
#define RBL_SIGCHAIN_45HZFILTER        0x0002U
#endif /*#if (RBFS_NvmBasedFilter == RBFS_NvmBasedFilter_ON)*/

#endif /* End of multiple include protection */
