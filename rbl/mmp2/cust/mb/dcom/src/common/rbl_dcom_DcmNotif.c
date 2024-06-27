/// @file rbl_dcom_DcmNotif.c
/// @brief This module provides APIs for Service Requests for Supplier Notification
/// @copyright (C) 2010 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/**
**********************************************************************************************************************
*  Includes
**********************************************************************************************************************
*/
#include "Dcm.h"
#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Roe_Inf.h"
#include "DcmDspUds_Cdtcs_Inf.h"
//#include "Rte_Dcm.h"
#include "DcmAppl.h"
#include "rbl_dcom_MB_Pub.h"
#include "rbl_dcom_Common.h"
#include "rbl_CustIf_VehSpd_Disp_ST3.h"
#include "RBMESG_Explicit.h"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
#include "Rte_Ports_Adapter.h"
#endif
//#include "rba_DcmPma.h"


/** Start with assumption that the tester is EF8 */
uint16 dcom_Requested_Tester = DCOM_FIRST_TESTER;

/****** PUBLIC/PROTECTED API functions ***** */


#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
/** ****************************************************************************
 * ***** API public: DcmAppl_DcmNotification ***** */

Std_ReturnType DcmAppl_SupplierNotification (uint8 SID,const uint8 * RequestData,uint32 RequestLength,uint8 RequestType,
                                             uint16 ConnectionId,Dcm_NegativeResponseCodeType * ErrorCode,
                                             Dcm_ProtocolType ProtocolType,uint16 TesterSourceAddress)
{
    Std_ReturnType retVal = E_OK;
    /** Code used to remove compiler warnings */
    (void)(RequestLength);
    (void)(RequestType);
    (void)(ConnectionId);

    {
        *ErrorCode = DCOM_NO_ERROR;
    }

    return retVal;
}
/****** END_API DcmAppl_DcmNotification ***** */
#endif



/** ****************************************************************************
 * ***** API public: DcmAppl_DcmNotification ***** */

Std_ReturnType DcmAppl_ManufacturerNotification (uint8 SID,
                                                        const uint8* RequestData,
                                                        uint32 DataSize,
                                                        uint8 ReqType,
                                                        uint16 ConnectionId,
                                                        Dcm_NegativeResponseCodeType* ErrorCode,
                                                        Dcm_ProtocolType ProtocolType,
                                                        uint16 TesterSourceAddress)
{

    Std_ReturnType retVal = E_OK;
//#if (RBFS_DiagBase == RBFS_DiagBase_DiagxMB) /*For plant mode in MB Builds we need to execute via Cubas callouts*/
//    // Vehicle Speed Check if speed is greater than 10KM\h
//    if(rba_DcmPma_PlantModeStatus_b != TRUE)   /*Check Plant mode is not active*/
//    {
//        // Vehicle Speed Check if speed is greater than 10KM\h
//        if(( rbl_dcom_VehSpd_Disp_ST3 > 100U))
//        {
//            //rbl_dcom_VehSpd_Disp_ST3 = RBMESG_VehSpd_Disp_ST3;
//            if(SID == 0x11)
//            {
//                *ErrorCode = DCM_E_VEHICLESPEEDTOOHIGH;
//                retVal = E_NOT_OK;
//            }
//            else if((SID == 0x10)&&(RequestData[0]== 0x03))
//            {
//                *ErrorCode = DCM_E_VEHICLESPEEDTOOHIGH;
//                retVal = E_NOT_OK;
//            }
//            else if((SID == 0x10)&&(RequestData[0]== 0x02))
//            {
//                *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
//                retVal = E_NOT_OK;
//            }
//            else
//            {
//                //do nothing
//            }
//        }
//    }
//#endif
    return retVal;
}
/****** END_API DcmAppl_ManufacturerNotification ***** */


#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
#define Ports_Adapter_START_SEC_CODE
#include "Ports_Adapter_MemMap.h"
FUNC (Std_ReturnType, Ports_Adapter_CODE) ServiceRequestNotification_Dcm_Coding_Confirmation/* return value & FctID */
(
        VAR(uint8, AUTOMATIC) SID,
        VAR(uint8, AUTOMATIC) ReqType,
        VAR(uint16, AUTOMATIC) ConnectionId,
        VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus,
        VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,
        VAR(uint16, AUTOMATIC) TesterSourceAddress
)
{

    Std_ReturnType retValue = E_NOT_OK;

    retValue = Rte_Call_ServiceRequestNotificationCoding_Confirmation(SID,ReqType,TesterSourceAddress,ConfirmationStatus);

    return retValue;

}
#define Ports_Adapter_STOP_SEC_CODE
#include "Ports_Adapter_MemMap.h"

#define Ports_Adapter_START_SEC_CODE
#include "Ports_Adapter_MemMap.h"
FUNC (Std_ReturnType, Ports_Adapter_CODE) ServiceRequestNotification_Dcm_Coding_Indication/* return value & FctID */
(
        VAR(uint8, AUTOMATIC) SID,
        P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) RequestData,
        VAR(uint32, AUTOMATIC) DataSize,
        VAR(uint8, AUTOMATIC) ReqType,
        VAR(uint16, AUTOMATIC) ConnectionId,
        P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode,
        VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,
        VAR(uint16, AUTOMATIC) TesterSourceAddress
)
{
    Std_ReturnType retValue = E_NOT_OK;

    retValue = Rte_Call_ServiceRequestNotificationCoding_Indication(SID,RequestData,DataSize,ReqType,TesterSourceAddress,ErrorCode);


#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
        if (DCOM_SECOND_TESTER == TesterSourceAddress)
        {
            dcom_Requested_Tester = DCOM_SECOND_TESTER;
        }
        else
#endif
        {
            dcom_Requested_Tester = DCOM_FIRST_TESTER;
        }


    return retValue;

}
#define Ports_Adapter_STOP_SEC_CODE
#include "Ports_Adapter_MemMap.h"

#define Ports_Adapter_START_SEC_CODE
#include "Ports_Adapter_MemMap.h"
FUNC (Std_ReturnType, Ports_Adapter_CODE) ServiceRequestNotification_Dcm_RightsM_Confirmation/* return value & FctID */
(
        VAR(uint8, AUTOMATIC) SID,
        VAR(uint8, AUTOMATIC) ReqType,
        VAR(uint16, AUTOMATIC) ConnectionId,
        VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus,
        VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,
        VAR(uint16, AUTOMATIC) TesterSourceAddress
)
{
    /* Local Data Declaration */
    Std_ReturnType retValue = E_NOT_OK;

    (void)ConnectionId;
    (void)ProtocolType;

#if(RBFS_HSWSimulation != RBFS_HSWSimulation_ON)
    if(    (SID == 0x80)
            || (rba_DcmPma_PlantModeStatus_b == TRUE)
    )
    {
        retValue = RTE_E_OK;
    }
    else
    {
        retValue = Rte_Call_ServiceRequestNotificationRightsM_Confirmation(SID,ReqType,TesterSourceAddress,ConfirmationStatus);
    }
#else
    retVal = RTE_E_OK;
#endif

    return retValue;

}
#define Ports_Adapter_STOP_SEC_CODE
#include "Ports_Adapter_MemMap.h"

#define Ports_Adapter_START_SEC_CODE
#include "Ports_Adapter_MemMap.h"
FUNC (Std_ReturnType, Ports_Adapter_CODE) ServiceRequestNotification_Dcm_RightsM_Indication/* return value & FctID */
(
        VAR(uint8, AUTOMATIC) SID,
        P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) RequestData,
        VAR(uint32, AUTOMATIC) DataSize,
        VAR(uint8, AUTOMATIC) ReqType,
        VAR(uint16, AUTOMATIC) ConnectionId,
        P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode,
        VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,
        VAR(uint16, AUTOMATIC) TesterSourceAddress
)
{

    Std_ReturnType retValue = E_NOT_OK;

    (void)ConnectionId;
    (void)ProtocolType;


#if(RBFS_HSWSimulation != RBFS_HSWSimulation_ON)
    if(    (SID == 0x80)
            || (rba_DcmPma_PlantModeStatus_b == TRUE)
    )
    {
        retValue = RTE_E_OK;
    }
    else
    {
        retValue = Rte_Call_ServiceRequestNotificationRightsM_Indication(SID, RequestData, DataSize, ReqType, TesterSourceAddress, ErrorCode);
    }
#else
    retValue = RTE_E_OK;
#endif

#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
        if (DCOM_SECOND_TESTER == TesterSourceAddress)
        {
            dcom_Requested_Tester = DCOM_SECOND_TESTER;
        }
        else
#endif
        {
            dcom_Requested_Tester = DCOM_FIRST_TESTER;
        }


    return retValue;

}
#define Ports_Adapter_STOP_SEC_CODE
#include "Ports_Adapter_MemMap.h"
#endif
