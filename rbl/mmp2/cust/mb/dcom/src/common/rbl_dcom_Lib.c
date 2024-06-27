/// @file rbl_dcom_Lib.c
/// @brief This module provides library functions that are used across Customer diagnostics
/// @copyright (C) 2018 Robert Bosch GmbH.
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

/*
**********************************************************************************************************************
* Variables
**********************************************************************************************************************
*/

static dcom_NvMReadWriteType_tst dcom_EepromReadByPdmState = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;
static dcom_NvMReadWriteType_tst dcom_EepromWriteByPdmState = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;

/*
**********************************************************************************************************************
* Functions
**********************************************************************************************************************
*/

/* ****************************************************************************
 * ***** API public: dcom_Lib_ReadNvMData ***** */

Std_ReturnType dcom_Lib_ReadNvMData(NvM_BlockIdType Block_Id, uint8* Data, uint8 NvM_Length,uint8 Fill_NvM)
{
    Std_ReturnType retVal;
    static NvM_RequestResultType l_NvM_Result;
    uint8 i;
    static uint8 l_EEPROMRetryLimit;

    retVal = DCM_E_PENDING;

    switch(dcom_EepromReadByPdmState)
    {
        case dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest:
        {
            // return value not required since error status would suffice
            (void)NvM_GetErrorStatus(Block_Id,&l_NvM_Result);
            /* Check if the Block Id is already in Queue */
            if (NVM_REQ_PENDING != l_NvM_Result)
            {
                if(NvM_ReadBlock(Block_Id,Data) == E_OK)
                {
                    /*Move to Next state*/
                    l_EEPROMRetryLimit = 0;
                    dcom_EepromReadByPdmState = dcom_NvMGetErrorStatus_AfterReadOrWriteRequest;
                }
                else
                {
                    l_EEPROMRetryLimit++;
                    /*Abort Read if Attempts exceed*/
                    if (l_EEPROMRetryLimit > 2)
                    {
                        dcom_EepromReadByPdmState = dcom_Error_ReadOrWriteNVMBlock;
                    }
                }
            }
            else
            {
                l_EEPROMRetryLimit++;
                /* NvM already in Queue, Abort Read if attempts exceed*/
                if (l_EEPROMRetryLimit > 5)
                {
                    dcom_EepromReadByPdmState = dcom_Error_ReadOrWriteNVMBlock;
                }
            }
        }
        break;

        case dcom_NvMGetErrorStatus_AfterReadOrWriteRequest:
        {
            // return value not required since this function provides NVM read status
            (void)NvM_GetErrorStatus(Block_Id,&l_NvM_Result);
            switch (l_NvM_Result)
            {
                case E_OK:
                {
                    /*Move to Next State*/
                    dcom_EepromReadByPdmState  = dcom_Done_ReadOrWriteNVMBlock;
                }
                break;

                case NVM_REQ_PENDING:
                break;

                case NVM_REQ_INTEGRITY_FAILED:
                case NVM_REQ_NV_INVALIDATED:
                {
                    /*NvM Empty: Fill with Default Values*/
                    for(i = (uint8)0; i < NvM_Length; i++)
                    {
                        Data[i] = Fill_NvM;
                    }
                    l_EEPROMRetryLimit = 0;
                    dcom_EepromReadByPdmState = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;
                    retVal = E_OK;
                }
                break;

                default:
                {
                    dcom_EepromReadByPdmState = dcom_Error_ReadOrWriteNVMBlock;
                }
                break;
            }
        }
        break;

        case dcom_Done_ReadOrWriteNVMBlock:
        {
            /*Reset State Machine*/
            l_EEPROMRetryLimit = 0;
            dcom_EepromReadByPdmState = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;
            retVal = E_OK;
        }
        break;

        case dcom_Error_ReadOrWriteNVMBlock:
        default:
        {
            /*Reset State Machine*/
            l_EEPROMRetryLimit = 0;
            dcom_EepromReadByPdmState = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;
            retVal = E_NOT_OK;
        }
        break;
    }

    /* Return status of read */
    return retVal;
}

/* ***** END_API dcom_Lib_ReadNvMData ***** */

/* ****************************************************************************
 * ***** API public: dcom_Lib_WriteNvMData ***** */

Std_ReturnType dcom_Lib_WriteNvMData(NvM_BlockIdType Block_Id, const uint8* Data,
Dcm_NegativeResponseCodeType * ErrorCode)
{
    Std_ReturnType retVal;
    static NvM_RequestResultType l_NvM_Result;
    static uint8 l_EEPROMRetryLimit;

    retVal = DCM_E_PENDING;

    switch(dcom_EepromWriteByPdmState)
    {
        case dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest:
        {
            /* Return value not required since error status would suffice */
            (void)NvM_GetErrorStatus(Block_Id,&l_NvM_Result);
            /* Check if BlockId is already in queue */
            if(NVM_REQ_PENDING != l_NvM_Result)
            {
                /* Write to NvM Block */
                if(NvM_WriteBlock(Block_Id,Data) == E_OK)
                {
                    /* Move to next state */
                    l_EEPROMRetryLimit = 0;
                    dcom_EepromWriteByPdmState = dcom_NvMGetErrorStatus_AfterReadOrWriteRequest;
                }

                else
                {
                    l_EEPROMRetryLimit++;
                    /* Abort process if maximum attempts are reached */
                    if(l_EEPROMRetryLimit > 2)
                    {
                        dcom_EepromWriteByPdmState = dcom_Error_ReadOrWriteNVMBlock;
                    }
                }
            }

            else
            {
                l_EEPROMRetryLimit++;
                /* NvM already in Queue, Abort Write if attempts exceed */
                if(l_EEPROMRetryLimit > 5)
                {
                    /* Report an error */
                    dcom_EepromWriteByPdmState = dcom_Error_ReadOrWriteNVMBlock;
                }
            }
        }
        break;

        case dcom_NvMGetErrorStatus_AfterReadOrWriteRequest:
        {
            /* Return value not required since NvM write status is being updated */
            (void)NvM_GetErrorStatus(Block_Id,&l_NvM_Result);
            switch(l_NvM_Result)
            {
                case E_OK:
                {
                    /* move to next state */
                    dcom_EepromWriteByPdmState = dcom_Done_ReadOrWriteNVMBlock;
                }
                break;

                case NVM_REQ_PENDING:
                break;

                default:
                {
                    /* Report error */
                    l_EEPROMRetryLimit = 0;
                    dcom_EepromWriteByPdmState = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;
                    *ErrorCode =  DCM_E_GENERALPROGRAMMINGFAILURE;
                    retVal = E_NOT_OK;
                }
                break;
            }
        }
        break;

        case dcom_Done_ReadOrWriteNVMBlock:
        {
            l_EEPROMRetryLimit = 0;
            dcom_EepromWriteByPdmState = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;
            retVal = E_OK;
        }
        break;

        case dcom_Error_ReadOrWriteNVMBlock:
        default:
        {
            l_EEPROMRetryLimit = 0;
            dcom_EepromWriteByPdmState = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;
            *ErrorCode =  DCM_E_CONDITIONSNOTCORRECT;
            retVal = E_NOT_OK;
        }
        break;
    }

    return retVal;
}

/* ***** END_API dcom_Lib_WriteNvMData ***** */

/* ****************************************************************************
 * ***** API public: RBAPLHELP_isSpeedLimitExceeded_B ***** */

boolean dcom_isSpeedLimitExceeded (uint16 l_Value)
{
     boolean l_Result_B = FALSE;

     /* Read vehicle speed  */
     RBMESG_DefineMESGDef(VehSpd_Disp_ST3);

     // Recevie message from VehSpd_Disp_ST3 vehicle display speed
     RBMESG_RcvMESGDef(VehSpd_Disp_ST3);

     /* vehicle speed check with the l_Value */
     if (l_VehSpd_Disp_ST3 == 255U)
     {
         l_Result_B = FALSE;
     }
     else if ((uint16)l_VehSpd_Disp_ST3 > l_Value)
     {
         l_Result_B = TRUE;
     }
     else
     {
         /* Nothing To Do */
     }

     return l_Result_B;
}

/* ***** END_API RBAPLHELP_isSpeedLimitExceeded_B ***** */

/* ****************************************************************************
 * ***** API public: dcom_Lib_HexNibble2ASCII ***** */
uint8 dcom_Lib_HexNibble2ASCII (uint8 t_Nibble_UB)
{
    uint8 ret = (uint8)((t_Nibble_UB & 0x0Fu) + (uint8)0x30);

    if (ret > 0x39)
    {
        ret += 0x07;
    }
    return ret;
}

/* ***** END_API dcom_Lib_HexNibble2ASCII ***** */
