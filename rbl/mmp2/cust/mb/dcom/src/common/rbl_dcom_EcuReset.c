/// @file rbl_dcom_EcuReset.c
/// @brief This module provides APIs for Ecu Reset service
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
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"
#include "DcmAppl.h"
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF))
#include "rbl_dcom_Common.h"
#include "rba_DcmPma.h"
#include "RB_SWReset.h"
#include "RBEMM_DCOM.h"

/*
**********************************************************************************************************************
* Variables
**********************************************************************************************************************
*/
static Std_ReturnType dcom_SoftResetstatus = E_OK;

static Std_ReturnType dcom_SoftResetRdy_check(void);



/* ***** PUBLIC/PROTECTED API functions ***** */

/* ****************************************************************************
 * ***** API public: DcmAppl_Switch_DcmExecuteEcuReset ***** */
void DcmAppl_Switch_DcmExecuteEcuReset(uint8 ResetType_u8)
{

    if(((rba_DcmPma_PlantModeStatus_b != TRUE) && (ResetType_u8 == DCOM_HARD_RESET))
    || (ResetType_u8 == DCOM_SOFT_RESET))
    {
        /** disable watchdog and reset **/
        RB_performSWResetSkipBootBlock();
    }

}
 /* ***** END_API DcmAppl_Switch_DcmExecuteEcuReset ***** */

/* ****************************************************************************
 * ***** API public: DcmAppl_DcmEcuResetPreparation ***** */

Std_ReturnType DcmAppl_DcmEcuResetPreparation(uint8 ResetType, Dcm_NegativeResponseCodeType*ErrorCode)
{
    Std_ReturnType retVal = E_OK;
    *ErrorCode = DCOM_NO_ERROR;

    if (ResetType == DCOM_SOFT_RESET)
    {
        retVal = dcom_SoftResetRdy_check() ;
    }

    return retVal;
}
/* ***** END_API dcom_EcuResetPreparation ***** */

/* ****************************************************************************
 * ***** API Private: dcom_SoftResetRdy_check ***** */

static Std_ReturnType dcom_SoftResetRdy_check(void)
{
    if (dcom_SoftResetstatus == E_OK)
    {
        if (TRUE == RBEMM_DCOM_SpecialServiceNvMWriteAll_Start())
        {
            dcom_SoftResetstatus = DCM_E_PENDING;
        }
        else
        {
            dcom_SoftResetstatus = E_NOT_OK;
        }
    }
    else if (dcom_SoftResetstatus == DCM_E_PENDING)
    {
        if (TRUE == RBEMM_DCOM_SpecialServiceNvMWriteAll_CheckIsFinished())
        {
            dcom_SoftResetstatus= E_OK;
        }
    }
    else
    {
        /* Do Nothing */
    }

    return dcom_SoftResetstatus ;
}
/* ***** END_API dcom_SoftResetRdy_check ***** */

#endif
