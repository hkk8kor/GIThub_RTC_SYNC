/// @file rbl_dcom_MB_OsPub.h
/// @brief This Header provides Interface to the operating system
/// @copyright (C) 2023 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_DCOM_MB_OSPUB_H__
#define RBL_DCOM_MB_OSPUB_H__

/* ***** SECTION Includes ***** */

/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/* Enumerations */

/* Structure definitions */

/* Variables definitions */

/* ***** END_SECTION Definitions ***** */


/* ***** PUBLIC/PROTECTED API function prototypes ***** */


/// @c_file dcom_MB_Main.c
/// @brief The Function calls Downgrade Protection Check service
/// @pre called from proc services in every 20ms
/// @param[in] void
/// @return void

void rbl_dcom_MB_20ms_Proc(void);

/// @c_file dcom_MB_Main.c
/// @brief The function is called at init for varinat monitoring
/// @pre rbl_dcom_MirrorAMGVarSwitch_u8 RAM mirror should be updated with NVM data.
/// @param[in] void
/// @return void
/// @startuml
/// !include rbl_dcom_MB_Init_Proc.puml
/// @enduml
void rbl_dcom_MB_Init_Proc(void);

/* ***** END_SECTION API functions ***** */

#endif /* RBL_DCOM_MB_OSPUB_H__ */
