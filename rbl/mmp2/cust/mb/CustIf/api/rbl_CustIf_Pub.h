/// @file rbl_CustIf_Pub.h
/// @brief This header provides definitions for Communication control service
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_CUSTIF_PUB_H__
#define RBL_CUSTIF_PUB_H__

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"

/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */
#define RBL_CUSTIF_SYSTEM_STATE_NORMAL   0U
#define RBL_CUSTIF_SYSTEM_STATE_DEGRADED 1U

/* Enumerations */

/* Structure definitions */

/* ***** END_SECTION Definitions ***** */


/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/* API to get the system state  */
/// @c_file rbl_CustIf_Main.c
/// @brief The Function gets the system state
/// @pre none
/// @param[in] void
/// @return uint8 : Returns the current system state
/// @retval RBL_CUSTIF_SYSTEM_STATE_NORMAL if state is Normal
/// @retval RBL_CUSTIF_SYSTEM_STATE_DEGRADED if state is Degraded

uint8 rbl_CustIf_GetSystemState(void);

/* ***** END_SECTION API functions ***** */

#endif /* RBL_CUSTIF_PUB_H__ */
