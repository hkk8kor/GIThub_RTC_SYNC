/// @file rbl_dcom_MB_SSA_Functions.c
/// @copyright (C) 2023 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#include "Rte_rbl_CustIf.h"
#include "rbl_dcom_MB_Pub.h"
#include "RBSEC_Prj_Wrapper.h"
#include "rbl_dcom_Lib.h"

#define rbl_CustIf_START_SEC_CODE
#include "rbl_CustIf_MemMap.h"

FUNC (Std_ReturnType, rbl_CustIf_CODE) GenerateKeyPair/* return value & FctID */
(
        VAR(uint32, AUTOMATIC) privateKeyId,
        VAR(uint32, AUTOMATIC) publicKeyId
)
{

    /* Local Data Declaration */
    Std_ReturnType retValue = E_NOT_OK;

    retValue = RBSEC_SSA_KeyPairGenerate(privateKeyId, publicKeyId);

    return retValue;

}
#define rbl_CustIf_STOP_SEC_CODE
#include "rbl_CustIf_MemMap.h"


#define rbl_CustIf_START_SEC_CODE
#include "rbl_CustIf_MemMap.h"
FUNC (Std_ReturnType, rbl_CustIf_CODE) dcom_MB_GetDiagnosticData
(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) diagVersion, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) diagVariant)
{

    /* Local Data Declaration */
    Std_ReturnType retValue = E_NOT_OK;

    if((NULL_PTR != diagVersion) && (NULL_PTR != diagVariant))
    {
        //Update Diagnostic Version in Decimal
        *diagVersion = DCOM_ACTIVE_DIAG_VERSION;
        *diagVariant = DCOM_ACTIVE_DIAG_VARIANT;
        retValue = E_OK;
    }

    return retValue;

}
#define rbl_CustIf_STOP_SEC_CODE
#include "rbl_CustIf_MemMap.h"
#define rbl_CustIf_START_SEC_CODE
#include "rbl_CustIf_MemMap.h"
FUNC (Std_ReturnType, rbl_CustIf_CODE) dcom_MB_GetSupplierData/* return value & FctID */
(
        P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) data,
        P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) dataLength
)
{

    Std_ReturnType retVal;
    uint8 byte_01;
    uint8 byte_02;
    uint8 index_1,index_2 = 0;

    //Filling the HW part number using RAM Mirror

    for(index_1=0;index_1<NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_HW_PartNumber;index_1++)
    {
        data[index_1]= rbl_dcom_DCOM_MB_HW_PartNumber[index_1];
    }

    data[10] = (uint8)DCOM_READ_PDMEMPTY_ASCII_NULL;


    //Filling Supplier Information
    byte_01 = DCOM_SUPPLIERID_HIGHBYTE >> 4;
    byte_02 = DCOM_SUPPLIERID_HIGHBYTE & 0x0Fu;

    data[11] = dcom_Lib_HexNibble2ASCII (byte_01);
    data[12] = dcom_Lib_HexNibble2ASCII (byte_02);

    byte_01 = DCOM_SUPPLIERID_LOWBYTE >> 4;
    byte_02 = DCOM_SUPPLIERID_LOWBYTE & 0x0Fu;


    data[13] = dcom_Lib_HexNibble2ASCII (byte_01);
    data[14] = dcom_Lib_HexNibble2ASCII (byte_02);

    // Filling  the Sesnsor Serial number using RAM Mirror
    for(index_1=SupplierInfo_EndIndex;index_1<(SupplierInfo_EndIndex+NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_ECU_SerialNr);index_1++)
    {
        data[index_1]= rbl_ECU_SerialNr_RAM_Mirror[index_2];
        index_2++;
    }

    *dataLength = DID_F103_DATA_LENGTH;
    retVal = E_OK;
    return retVal;

}
#define rbl_CustIf_STOP_SEC_CODE
#include "rbl_CustIf_MemMap.h"
