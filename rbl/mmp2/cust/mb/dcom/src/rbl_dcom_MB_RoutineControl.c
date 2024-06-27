
/// @file rbl_dcom_MB_RoutineControl.c
/// @brief This module provides APIs for all the Start, Stop And RequestResult RIDs for MB
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "rbl_dcom_MB_RoutineControl.h"
#include "rbl_dcom_Lib.h"
#include "RBMESG_Explicit.h"
#include "rbl_CustIf_FBL_Cfg_Star3_ST3.h"

/*
**********************************************************************************************************************
* Macros
**********************************************************************************************************************
*/

/*
**********************************************************************************************************************
* Variables
**********************************************************************************************************************
*/
#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)
boolean dcom_CheckReprogPreConditionFullfilled = FALSE;
#endif

/* ****************************************************************************
 * ***** API public: dcom_CheckReprogrammingPreconditions_0203_Start ***** */

Std_ReturnType dcom_CheckReprogrammingPreconditions_0203_Start(Dcm_OpStatusType OpStatus, uint8 * dataOut1,
uint8 * dataOut2,uint16 * CurrentDataLength, Dcm_NegativeResponseCodeType * ErrorCode)
{
    Std_ReturnType retVal = E_OK;
    RBMESG_DefineMESGDef(Platform_Stat_Star3);
    (void) OpStatus; /*Statement is added just to avoid the warning*/
    //Recevie message from FBL_Cfg_Star3_ST3 PDU
    RBMESG_RcvMESGDef(Platform_Stat_Star3);
    *ErrorCode = DCOM_NO_ERROR;

#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)

    if ((l_Platform_Stat_Star3!=DCOM_FBL_STAR3)&& dcom_isSpeedLimitExceeded(DCOM_REPROG_SPEEDLIMIT))
    {
        *CurrentDataLength = 3;
        /* Number of Unfulfilled Preconditions*/
        dataOut2[0]= 2 ;
        /* Vehicle speed is high*/
        dataOut2[1]= DCOM_VEHICLE_SPEED_HIGH ;

        /* Platform stat st3 signal is not Star3 */
        dataOut2[2]= DCOM_FBL_CFG_STAR3;

    }
    else if ((l_Platform_Stat_Star3==DCOM_FBL_STAR3)&& dcom_isSpeedLimitExceeded(DCOM_REPROG_SPEEDLIMIT))
    {
        *CurrentDataLength = 2;
		/* Number of Unfulfilled Preconditions*/
        dataOut2[0]= 1 ;
		/* Vehicle speed is high*/
        dataOut2[1]= DCOM_VEHICLE_SPEED_HIGH ;
    }
    else if ((l_Platform_Stat_Star3!=DCOM_FBL_STAR3)&&(!dcom_isSpeedLimitExceeded(DCOM_REPROG_SPEEDLIMIT)))
    {
        *CurrentDataLength = 2;
        /* Number of Unfulfilled Preconditions*/
        dataOut2[0]= 1 ;

        /* Platform stat st3 signal is not Star3 */
        dataOut2[1]= DCOM_FBL_CFG_STAR3;
    }
    else
    {
        *CurrentDataLength = 1;
		/* Number of Unfulfilled Preconditions*/
        dataOut2[0]= 0 ;
        dcom_CheckReprogPreConditionFullfilled = TRUE;
    }
#else
    *CurrentDataLength = 3;
     dataOut2[0]=0;                                    /* Number of Unfulfilled Preconditions*/
#endif
    /* Routine sucessfully completed*/
    dataOut1[0]= DCOM_ROUTINE_SUCCESSFULLY_COMPLETED ;



    return retVal;
}
/* *************** END_API dcom_CheckReprogrammingPreconditions_0203_Start *************** */
