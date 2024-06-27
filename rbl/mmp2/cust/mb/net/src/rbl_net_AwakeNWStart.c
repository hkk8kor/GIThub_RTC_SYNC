/// @file rbl_net_AwakeNWStart.C
/// @brief The file consists of the NWStart functions for Net module
/// @copyright (C) 2023 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


/* ***** Includes ***** */
#include "rbl_net_AwakeNWStart.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Local Definitions ***** */

/* Variables */
static RBL_NET_NWSTART_STATE rbl_net_NwStartCheck_State = RBL_NET_NWSTART_INIT;


/* *********************************************************************************************************************
 * ***** API public: rbl_net_GetAwakeNwStartStatus *****/
boolean rbl_net_GetAwakeNwStartStatus(void)
{
	boolean NwStart_State = FALSE;

	if(RBL_NET_NWSTART_ONGOING == rbl_net_NwStartCheck_State)
	{
		NwStart_State = TRUE;
	}

	return NwStart_State;
}
/* ***** END_API rbl_net_GetAwakeNwStartStatus ***** */


/* ***** API public: rbl_net_NwStartCheck *****/
void rbl_net_NwStartCheck(void)
{
    static uint16 NwStartCnt = 0;

    switch (rbl_net_NwStartCheck_State)
    {

		case RBL_NET_NWSTART_INIT:
            /* First run, change state to Ongoing */
            rbl_net_NwStartCheck_State  = RBL_NET_NWSTART_ONGOING;
            break;

        case RBL_NET_NWSTART_ONGOING:
            /* Check for TStartupSleepDelayMin time */
            if ( RBL_NET_AWAKE_NWSTART_TIME < NwStartCnt )
            {
                rbl_net_NwStartCheck_State = RBL_NET_NWSTART_COMPLETED;
            }
            //Increment the counter
            NwStartCnt++;
            break;

        case RBL_NET_NWSTART_COMPLETED:
            /* set state completed */
            rbl_net_NwStartCheck_State = RBL_NET_NWSTART_COMPLETED;
            break;

        default:
            /* By default set state completed */
            rbl_net_NwStartCheck_State = RBL_NET_NWSTART_COMPLETED;
            break;
    }

}
/* ***** END_API rbl_net_NwStartCheck ***** */
