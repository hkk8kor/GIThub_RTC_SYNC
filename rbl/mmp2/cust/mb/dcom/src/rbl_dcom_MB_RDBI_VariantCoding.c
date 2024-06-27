/// @file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The file consists of the API's for Varinat coding Read Data by Identifier DID's identified for Customer Diagnostics for MB
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
#include "rbl_dcom_MB_RWDBI_VariantCoding.h"

/*
**********************************************************************************************************************
* Macros
**********************************************************************************************************************
*/

/* ****************************************************************************
 * ***** API public: dcom_AMG_SWITCH_0400_ReadData ***** */
Std_ReturnType dcom_AMG_SWITCH_0400_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
       {
           /*Call to NvM Read Generic api for reading the MB AMG VARINAT CODING */
           retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_AMG_SWITCH,
           Data,NVM_CFG_NV_BLOCK_LENGTH_DCOM_AMG_SWITCH,DCOM_READ_PDMEMPTY);
       }

    return retVal;
}
/* ***** END_API  dcom_AMG_SWITCH_0400_ReadData ***** */

/* ****************************************************************************
 * ***** API public: dcom_Calibration_Identifications_E104_ReadData ***** */
Std_ReturnType dcom_Calibration_Identifications_E104_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

        if(Data != NULL_PTR)
           {
               /*Call to NvM Read Generic api for reading the Calibration Identification */
               retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_CALID,
               Data,NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_CALID,DCOM_READ_PDMEMPTY);
           }

        return retVal;
}
/* ***** END_API  dcom_Calibration_Identifications_E104_ReadData ***** */

