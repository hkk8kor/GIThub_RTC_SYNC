/// @file rbl_net_OsPub.h
/// @brief This Header provides Interface to the operating system
/// @copyright (C) 2023 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_NET_OSPUB_H__
#define RBL_NET_OSPUB_H__

/* ***** SECTION Includes ***** */

/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/* Enumerations */

/* Structure definitions */

/* Variables definitions */

/* ***** END_SECTION Definitions ***** */


/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file rbl_net_Main.c
/// @brief The Function calls PNC main function
/// @pre Called every 10ms from proc service
/// @param[in] void
/// @return void
/// @details The PNC functions being called are as below:
/// ComM_MainFunc_PNC_Id_8() ,ComM_MainFunc_PNC_Id_23(), ComM_MainFunc_PNC_Id_28(), ComM_MainFunc_PNC_Id_31(), rbl_net_NwStartCheck();
void rbl_net_10ms_Proc(void);

/* ***** END_SECTION API functions ***** */

#endif /* RBL_NET_OSPUB_H__ */
