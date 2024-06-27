/// @file rbl_dcom_MB_WriteDataByIdentifier.c
/// @brief The file consists of the API's for Varinat coding Write Data by Identifier DID's identified for Customer Diagnostics for MB
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

/* RAM block for Calibration for Identification */
uint8 rbl_Mirrordcom_CalId_u8[16] = {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30}; //RAM mirror for CALID.
/* RAM block for AMG Varinat Coding Switch */
uint8 rbl_dcom_MirrorAMGVarSwitch_u8[1] = {0x00}; // RAM mirror for AMG SWITCH Default set to MB.


/* ****************************************************************************
 * ***** API public: dcom_AMG_SWITCH_0400_WriteData ***** */
Std_ReturnType dcom_AMG_SWITCH_0400_WriteData(const uint8 * Data,Dcm_NegativeResponseCodeType * ErrorCode)
{

    Std_ReturnType retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        if(Data[0] < RBL_DCOM_AMG_VARINAT_CODING_U8)
        {
            /* Write AMG VARINAT CODING Data to RAM mirror*/
            rbl_dcom_MirrorAMGVarSwitch_u8[0] =  Data[0];
            retVal = E_OK;
        }
        else
        {
            /*Request our of range if varinat is not in range*/
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
/* ***** END_API dcom_AMG_SWITCH_0400_WriteData ***** */

/* ****************************************************************************
 * ***** API public: dcom_Calibration_Identifications_F804_WriteData ***** */
Std_ReturnType dcom_Calibration_Identifications_F804_WriteData(const uint8 * Data,Dcm_NegativeResponseCodeType * ErrorCode)
{
    Std_ReturnType retVal = E_NOT_OK;
    uint8 rbl_dcom_CalIdCnt_u8 = 0 ;

        if(Data != NULL_PTR)
        {
            /*Check the number of itration is in range*/
            if(Data[0] == RBL_DCOM_CALID_NUM_ITEMS_U8)
            {
                /* Write CALID to RAM mirror*/
                for(rbl_dcom_CalIdCnt_u8 = 0; rbl_dcom_CalIdCnt_u8 < 16; rbl_dcom_CalIdCnt_u8++)
                {
                    rbl_Mirrordcom_CalId_u8[rbl_dcom_CalIdCnt_u8] = Data[rbl_dcom_CalIdCnt_u8 + 1];
                }
                retVal = E_OK;
            }
            else
            {
                /*Request our of range if Number of data iteams is not in range*/
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

/* ***** END_API dcom_Calibration_Identifications_F804_WriteData ***** */


