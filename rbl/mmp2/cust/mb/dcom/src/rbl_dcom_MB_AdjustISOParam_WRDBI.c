/// @file rbl_dcom_MB_AdjustISOParam_WRDBI.c
/// @brief The file consists of the API's for Adjust ISOParam WRDBI DID's identified for Customer Diagnostics for MB
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
#include "CanTp.h"
/* */


/* ****************************************************************************
* ***** API public: dcom_CanTp_ReadParameter_010B_ReadData ***** */

Std_ReturnType dcom_CanTp_ReadParameter_010B_ReadData(uint8 * Data)
{
    Std_ReturnType   retVal ;
    Std_ReturnType   retVal1 = E_NOT_OK;
    Std_ReturnType   retVal2 = E_NOT_OK;
    uint16 block_size;
    uint16 st_min;

    if(Data != NULL_PTR)
    {
        switch(dcom_Requested_Tester)
        {

            case DCOM_FIRST_TESTER:
                /* Read the Block Size Info */
                retVal1 = CanTp_ReadParameter(CanTpConf_CanTpRxNSdu_CanTpRxNSdu_MB_DiagExt_PHY, TP_BS,&block_size);
                /* Read the STmin Info */
                retVal2 = CanTp_ReadParameter(CanTpConf_CanTpRxNSdu_CanTpRxNSdu_MB_DiagExt_PHY, TP_STMIN,&st_min);
                break;

#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
            case DCOM_SECOND_TESTER:
                /* Read the Block Size Info */
                retVal1 = CanTp_ReadParameter(CanTpConf_CanTpRxNSdu_CanTpRxNSdu_MB_DiagInt_PHY, TP_BS, &block_size);
                /* Read the STmin Info */
                retVal2 = CanTp_ReadParameter(CanTpConf_CanTpRxNSdu_CanTpRxNSdu_MB_DiagInt_PHY, TP_STMIN, &st_min);
                break;
#endif
            default:
                retVal = E_NOT_OK;
                break;

        }

        if((retVal1 == E_OK)&&(retVal2 == E_OK))
        {
            Data[0]= (uint8)block_size;
            Data[1]= (uint8)st_min;
            retVal = E_OK;
        }

    }

    return retVal;
}

/* ***** END_API  dcom_CanTp_ReadParameter_010B_ReadData ***** */

/* ****************************************************************************
* ***** API public: dcom_CanTp_ChangeParameter_010B_WriteData ***** */

Std_ReturnType dcom_CanTp_ChangeParameter_010B_WriteData(const uint8 * Data, Dcm_NegativeResponseCodeType * ErrorCode)
{
    Std_ReturnType   retVal;
    Std_ReturnType   retVal1 = E_NOT_OK;
    Std_ReturnType   retVal2 = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        if(((0x00 <= Data[1]) && ( Data[1] <= 0x7F)) || ((0xF1 <= Data[1]) &&  ( Data[1] <= 0xF9)))
      {
        switch(dcom_Requested_Tester)
        {

            case DCOM_FIRST_TESTER:
                /* write the Block Size Info */
                retVal1 = CanTp_ChangeParameter(CanTpConf_CanTpRxNSdu_CanTpRxNSdu_MB_DiagExt_PHY, TP_BS, Data[0]);
                /* write the STmin Info */
                retVal2 = CanTp_ChangeParameter(CanTpConf_CanTpRxNSdu_CanTpRxNSdu_MB_DiagExt_PHY, TP_STMIN, Data[1]);
                break;

#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
            case DCOM_SECOND_TESTER:
                /* write the Block Size Info */
                retVal1 = CanTp_ChangeParameter(CanTpConf_CanTpRxNSdu_CanTpRxNSdu_MB_DiagInt_PHY, TP_BS, Data[0]);
                /* write the STmin Info */
                retVal2 = CanTp_ChangeParameter(CanTpConf_CanTpRxNSdu_CanTpRxNSdu_MB_DiagInt_PHY, TP_STMIN, Data[1]);
                break;
#endif
            default:
                *ErrorCode = 0;
                retVal = E_NOT_OK;
                break;
           }



    }
    else
    {
        *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
        retVal = E_NOT_OK;
    }

        if((retVal1 == E_OK)&&(retVal2 == E_OK))
        {
            retVal = E_OK;
        }

    }

    return retVal;
}

/* ***** END_API  dcom_CanTp_ChangeParameter_010B_WriteData ***** */
