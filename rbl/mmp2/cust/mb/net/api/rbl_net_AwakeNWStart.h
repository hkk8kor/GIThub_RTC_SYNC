/// @file rbl_net_AwakeNWStart.h
/// @brief This Header provides Interface to the operating system
/// @copyright (C) 2024 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_NET_AWAKENWSTART_H__
#define RBL_NET_AWAKENWSTART_H__

/* ***** SECTION Includes ***** */
#include "Platform_Types.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */
#define RBL_NET_AWAKE_NWSTART_TIME  302u

/* Enumerations */
///Definition for Gts Monitoring State Machine
typedef enum
{
	RBL_NET_NWSTART_INIT,
	RBL_NET_NWSTART_ONGOING,
	RBL_NET_NWSTART_COMPLETED
}RBL_NET_NWSTART_STATE;


/// @c_file rbl_net_AwakeNWStart.C
/// @brief The Function basically used to get the Network start Check
/// @pre None
/// @param[in] void
/// @return void
/// @startuml
/// rbl_net_NwStartCheck.puml
/// @enduml
void rbl_net_NwStartCheck(void);


/// @c_file rbl_net_AwakeNWStart.C
/// @brief The Function is used to get the Awake start staus of the signal.
/// @pre None
/// @param[in] void
/// @return boolean NwStart_State
/// @startuml
/// rbl_net_GetAwakeNwStartStatus.puml
/// @enduml
boolean rbl_net_GetAwakeNwStartStatus(void);



/* ***** END_SECTION API functions ***** */

#endif /* RBL_NET_AWAKENWSTART_H__ */
