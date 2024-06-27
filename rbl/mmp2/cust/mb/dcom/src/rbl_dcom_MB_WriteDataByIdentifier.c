/// @file rbl_dcom_MB_WriteDataByIdentifier.c
/// @brief The file consists of the API's for Write Data by Identifier DID's identified for Customer Diagnostics for MB
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
#include "rbl_dcom_Lib.h"
#include "rbl_dcom_MB_Pub.h"

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

/* RAM block for Active Supplier specifc message mode */
uint8 rbl_dcom_MirrorActvtDbgFrmsAppl_u8[1] = {1}; // Default Initalize with Active mode.

/* ***** PUBLIC/PROTECTED API functions ***** */

/* ****************************************************************************
 * ***** API public: dcom_DiagnosticTraceMemory_102_WriteData ***** */

Std_ReturnType dcom_DiagnosticTraceMemory_102_WriteData(const uint8 * Data,Dcm_NegativeResponseCodeType * ErrorCode)
{

    Std_ReturnType retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /* Write Diagnosis Tracing Memory Data from NvM item:DAG_DiagTraceMem */
        retVal = dcom_Lib_WriteNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_DiagTraceMem , Data, ErrorCode);
    }

    return retVal;

}

/* ***** END_API dcom_DiagnosticTraceMemory_0102_WriteData ***** */

/* ****************************************************************************
 * ***** API public: dcom_ActivateSupplierSpecificMessages_012A_WriteData ***** */
Std_ReturnType dcom_ActivateSupplierSpecificMessages_012A_WriteData(const uint8 * Data,Dcm_NegativeResponseCodeType * ErrorCode)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /*Check the Requested Data is in range */
        if(Data[0] < RBL_DCOM_INVALID_SPLR_MSGS_U8)
        {
            rbl_dcom_MirrorActvtDbgFrmsAppl_u8[0] = Data[0];
            /* Write Activate supplier specific messages mode Data to NvM block*/
            retVal = dcom_Lib_WriteNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_ActivateSupplierMsgs,Data,ErrorCode);
        }
        else
        {
            *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
            retVal = E_NOT_OK;
        }
    }
    else
    {
        *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        retVal = E_NOT_OK;
    }

    return retVal;
}

/* ***** END_API dcom_ActivateSupplierSpecificMessages_012A_WriteData ***** */

/* ****************************************************************************
 * ***** API public: dcom_Trust_Model_CSR_Supplier_Signature_01A2_WriteData ***** */
Std_ReturnType dcom_Trust_Model_CSR_Supplier_Signature_01A2_WriteData(const uint8 * Data,uint16 DataLength, Dcm_NegativeResponseCodeType * ErrorCode)
{
    Std_ReturnType retVal = E_NOT_OK;


    if(Data != NULL_PTR)
    {
        memcpy(DCOM_SupplierPubKey_Sig_RAM_Mirror,Data,DataLength);

        retVal = dcom_Lib_WriteNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_SupplierPublicKey_Signature,Data,ErrorCode);
    }
    return retVal;
}
/* ***** END_API dcom_Trust_Model_CSR_Supplier_Signature_01A2_WriteData ***** */
