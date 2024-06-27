/**********************************************************************************************************************
*
* COPYRIGHT RESERVED, 2022 Robert Bosch GmbH. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************/
#include "Dcm.h"

#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)


/* example implementation; proposals are available below; several additional headerfiles from other components might be needed!!!
//Configured wait time is 100ms converted to Proc cycles
#define DCMAPPL_WAITTIME (100000/DCM_CFG_TASK_TIME_US)

#define DCMAPPL_FRIF_CONTROLLER_INDEX 0x0
#define DCMAPPL_FRSM_NETWORK_HANDLE 0

#define DCMAPPL_SOLUTION1_ENABLED STD_ON
#define DCMAPPL_SOLUTION2_ENABLED STD_ON
#define DCMAPPL_SOLUTION3_ENABLED STD_ON

static uint32 DcmAppl_WaitTimeFlexSync_u32;
end example*/


 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 *  @ingroup DCM_TPL
 *  DcmAppl_DcmGetPermTxWarmResp:-\n
 *  This function is called to get the permission for transmission of the Warm response/Warm request stored in Boot.
 *  This function should check if the FlexRay / CAN is already in Full communication mode (or synchronized)
 *  to transmit the warm response/warm request. The information on the Protocol, Controller Index and the FlexRay Network handle Information
 *  needs to de derived by the user/application to know the lower medium CAN / FLEXRAY from the configuration.
 *  If the warm response/warm request needs to be sent over CAN, return TRUE immediately.If Flexray protocol is used then application should wait till the Flexray is synchronized
 *  before sending the value as TRUE. Also a maximum time limit needs to be introduced within which FlexRay should be synchronized for this API provides permission. Once the timer is
 *  expired then E_NOT_OK will be returned from this API. \n
 *
 *  @param[in]      None
 *  @param[out]     None
 *  @retval         E_OK: Permission is available for Warm response transmission \n
 *  @retval         DCM_E_PENDING: FlexRay is not synchronized yet. Need more time. \n
 *  @retval         E_NOT_OK: FlexRay is not synchronized even after maximum wait time or harware errors\n
 */
Std_ReturnType DcmAppl_DcmGetPermTxWarmResp(void)
{

    /* add your implementation here
     * below, you there are several examples available*/



    /* The information on the Protocol, Controller Index and the FlexRay Network handle Information
       needs to de derived by the user/application to know the lower medium CAN / FLEXRAY.
       from the configuration */
    /* If the warm response/warm request needs to be sent over CAN, return TRUE immediately*/

    /* If Flexray protocol is used then application should wait till the Flexray is synchronized
       before sending the value as TRUE. Also a maximum time limit needs to be introduced within
       which FlexRay should be synchronized for this API provides permission. Once the timer is
       expired then E_NOT_OK will be returned from this API */

    /* Returns from this API */
    /* E_OK:     Permission is available for Warm response transmission
       DCM_E_PENDING:FlexRay is not synchronized yet. Need more time.
       E_NOT_OK: FlexRay is not synchronized even after maximum wait time or harware errors */


    /*Std_ReturnType retVal;
    VAR(Std_ReturnType,AUTOMATIC)   retFlexStatus;
    Fr_POCStatusType POCStatusPtr;
    Fr_SyncStateType FlexSyncState;
    ComM_ModeType ComM_Mode;*/

    /*#if(DCMAPPL_SOLUTION1_ENABLED != STD_OFF)*/
    /*
    *******************************************************************
     SOLUTION 1: Using the FrIf API FrIf_GetPOCStatus
    *******************************************************************
    */
    /* If the Flash programming is active over Flexray medium */
    /* Controller index should be known to the user */
    /*retFlexStatus = FrIf_GetPOCStatus(DCMAPPL_FRIF_CONTROLLER_INDEX, &POCStatusPtr);*/

    /* If the status is read correctly and FlexRay is synchronous */
    /*if(retFlexStatus == E_OK)*/
    /*{ */
        /*if(POCStatusPtr.State == FR_POCSTATE_NORMAL_ACTIVE)*/
        /*{*/
            /*retVal = E_OK;*/
            /* Reset the timer variable */
            /*DcmAppl_WaitTimeFlexSync_u32 = 0;*/
        /*} */
        /*else */
        /*{*/
            /*if(DcmAppl_WaitTimeFlexSync_u32 != DCMAPPL_WAITTIME) */
            /*{ */
                /*retVal = DCM_E_PENDING;*/
                /* Increment timer variable */
                /*DcmAppl_WaitTimeFlexSync_u32++;  */
            /*} */
            /*else */
            /*{ */
                /*retVal = E_NOT_OK;*/
                /* Reset the timer variable */
                /*DcmAppl_WaitTimeFlexSync_u32 = 0;*/
            /*}*/
        /*} */
    /*} */
    /*else */
    /*{ */
        /*retVal = E_NOT_OK;*/
        /* Reset the timer variable */
        /*DcmAppl_WaitTimeFlexSync_u32 = 0;*/
    /*}*/
    /*return(retVal);*/
    /*#endif */

    /*#if(DCMAPPL_SOLUTION2_ENABLED != STD_OFF)*/
    /*
    *******************************************************************
     SOLUTION 2: Using the FrIf API FrIf_GetSyncState
    *******************************************************************
    */
    /* FR_ASYNC: The local FlexRay CC is asynchronous to the FR global time. */
    /* FR_SYNC:  The local FlexRay CC is synchronous to the FR global time */

    /* If the Flash programming is active over Flexray medium */
    /* Controller index should be known to the user */
    /*retFlexStatus = FrIf_GetSyncState(DCMAPPL_FRIF_CONTROLLER_INDEX, &FlexSyncState);*/

    /* If the status is read correctly and FlexRay is synchronous */
    /*if(retFlexStatus == E_OK)*/
    /*{*/
        /*if(FlexSyncState == FR_SYNC)*/
        /*{*/
            /*retVal = E_OK;*/
            /* Reset the timer variable */
            /*DcmAppl_WaitTimeFlexSync_u32 = 0;*/
        /*}*/
        /*else*/  /* FR_ASYNC */
        /*{*/
            /*if(DcmAppl_WaitTimeFlexSync_u32 != DCMAPPL_WAITTIME)*/
            /*{*/
                /*retVal = DCM_E_PENDING;*/
                /* Increment timer variable */
                /*DcmAppl_WaitTimeFlexSync_u32++;*/
            /*}*/
            /*else*/
            /*{*/
                /*retVal = E_NOT_OK;*/
                /* Reset the timer variable */
                /*DcmAppl_WaitTimeFlexSync_u32 = 0;*/
            /*}*/
        /*}*/
    /*}*/
    /*else*/
    /*{*/
        /*retVal = E_NOT_OK;*/
        /* Reset the timer variable */
        /*DcmAppl_WaitTimeFlexSync_u32 = 0;*/
    /*}*/
    /*return(retVal);*/
    /*#endif*/

    /*#if(DCMAPPL_SOLUTION1_ENABLED != STD_OFF)*/
    /*
    *******************************************************************
     SOLUTION 3: Using the FrSm API FrSm_GetCurrentComMode
    *******************************************************************
    */
    /* COMM_FULL_COMMUNICATION:  ComM is working in full communication mode */
    /* COMM_SLIENT_COMMUNICATION:ComM is working in silent communication mode */
    /* COMM_NO_COMMUNICATION:    ComM is working in no communication mode */

    /* If the Flash programming is active over Flexray medium */
    /* Controller index should be known to the user */
    /*retFlexStatus = FrSm_GetCurrentComMode(DCMAPPL_FRSM_NETWORK_HANDLE, &ComM_Mode);*/

    /* If the status is read correctly and FlexRay is synchronous */
    /*if(retFlexStatus == E_OK)*/
    /*{*/
        /*if(ComM_Mode == COMM_FULL_COMMUNICATION)*/
        /*{*/
            /*retVal = E_OK;*/
            /* Reset the timer variable */
            /*DcmAppl_WaitTimeFlexSync_u32 = 0;*/
        /*}*/
        /*else*/
        /*{ */
            /*if(DcmAppl_WaitTimeFlexSync_u32 != DCMAPPL_WAITTIME)*/
            /*{*/
                /*retVal = DCM_E_PENDING;*/
                /* Increment timer variable */
                /*DcmAppl_WaitTimeFlexSync_u32++; */
            /*}*/
            /*else */
            /*{*/
                /*retVal = E_NOT_OK;*/
                /* Reset the timer variable */
                /*DcmAppl_WaitTimeFlexSync_u32 = 0;*/
            /*}*/
        /*}*/
    /*}*/
    /*else*/
    /*{*/
        /*retVal = E_NOT_OK;*/
        /* Reset the timer variable */
        /*DcmAppl_WaitTimeFlexSync_u32 = 0;*/
    /*}*/
    /*return(retVal);*/
    /*#endif*/
    return E_OK;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

#endif
