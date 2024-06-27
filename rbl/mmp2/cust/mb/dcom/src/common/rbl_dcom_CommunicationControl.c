/// @file rbl_dcom_CommunicationControl.c
/// @brief This module provides API for Communication Control Service(0x28)
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/*
**********************************************************************************************************************
*  Includes
**********************************************************************************************************************
*/
//#include "rbl_dcom_Common.h"
#include "rbl_dcom_CommunicationControl.h"
#include "RbPduHandler.h"


/* ***** PUBLIC/PROTECTED API functions ***** */

/* ****************************************************************************
 * ***** API public: DcmAppl_DcmCommControlConditionCheck ***** */

Std_ReturnType DcmAppl_DcmCommControlConditionCheck(uint8 ControlType_u8, uint8 DataCommType_u8,
const uint8* RequestData, uint16 RequestLength, Dcm_NegativeResponseCodeType*dataNegRespCode_u8)
{
    Std_ReturnType retVal = E_NOT_OK;
	/* To avoid warnings */
    (void)RequestData;
    (void)RequestLength;

    if (DCOM_COMMUNICATION_MESSAGES_NORMAL == DataCommType_u8)
    {
        retVal = E_OK;
    }
    else
    {
        /* NRC 0x31 shall be sent for the Communication Type other than Normal Messages */
        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
    }

    return retVal;
}

/* ***** END_API DcmAppl_DcmCommControlConditionCheck ***** */

/* ****************************************************************************
 * ***** API public: DcmAppl_DcmSwitchCommunicationControl ***** */

void DcmAppl_DcmSwitchCommunicationControl(uint8 NetworkID,Dcm_CommunicationModeType RequestedMode)
{
    /* To avoid warnings */
    (void)(NetworkID);
    (void)(RequestedMode);

}

/* ***** END_API DcmAppl_DcmSwitchCommunicationControl ***** */

#if((DCM_CFG_RTESUPPORT_ENABLED==DCM_CFG_OFF))
/* ****************************************************************************
 * ***** API public: DcmAppl_DcmIsComModeDefault ***** */

boolean DcmAppl_DcmIsComModeDefault(uint8 NetworkID)
{
    boolean retVal = TRUE;
    /* To avoid warnings */
    (void)(NetworkID);

    return retVal;
}
/* ***** END_API DcmAppl_DcmIsComModeDefault ***** */
#endif
