/// @file rbl_net_Main.c
/// @brief The file consists of the proc functions for Dcom module
/// @copyright (C) 2023 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


/* ***** Includes ***** */
#include "rbl_net_OsPub.h"
#include "ComM.h"
#include "rbl_net_AwakeNWStart.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Local Definitions ***** */
/* Constants and Macro definitions */

/* Variables */


/* Structure definitions */

/* ***** PUBLIC/PROTECTED API functions ***** */
/* *********************************************************************************************************************
 * ***** API public: rbl_net_10ms_Proc *****/

void rbl_net_10ms_Proc(void)
{
    ComM_MainFunc_PNC_Id_8();
    ComM_MainFunc_PNC_Id_23();
    ComM_MainFunc_PNC_Id_28();
    ComM_MainFunc_PNC_Id_31();

	rbl_net_NwStartCheck();
}
/* ***** END_API rbl_net_10ms_Proc ***** */

/* ***** END_SECTION API functions ***** */
