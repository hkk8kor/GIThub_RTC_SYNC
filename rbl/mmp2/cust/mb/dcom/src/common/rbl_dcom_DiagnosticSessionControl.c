/// @file rbl_dcom_DiagnosticSessionControl.c
/// @brief This module provides APIs for Session Control service
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
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"
#include "DcmAppl.h"
#include "rbl_dcom_MB_Pub.h"

/** Active diagnostics status */
boolean rbl_dcomActiveDiagSession = FALSE;

/* ****************************************************************************
 * ***** API public: DcmAppl_DcmSesCtrlChangeIndication ***** */

void DcmAppl_DcmSesCtrlChangeIndication (Dcm_SesCtrlType SesCtrlTypeOld, Dcm_SesCtrlType SesCtrlTypeNew)
{
    (void)SesCtrlTypeOld;

    switch (SesCtrlTypeNew)
    {
        case DCM_DEFAULT_SESSION:
        {
            /* Indicate IMU is not in active diagnostics session */
			rbl_dcomActiveDiagSession = FALSE;
        }
        break;

        case DCM_EXTENDED_DIAGNOSTIC_SESSION:
        {
            /* Indicate IMU is in active diagnostics session */
			rbl_dcomActiveDiagSession = TRUE;
        }
        break;

        case DCM_PROGRAMMING_SESSION:
        {
#if (RBFS_DcomReprogResponseType != RBFS_DcomReprogResponseType_Warm)
            /** Set programming conditions **/
            dcom_SetProgConditions();
#endif
        }
        break;

#if (RBFS_DcomSupplierSession != RBFS_DcomSupplierSession_Disabled)
		case DCM_SUPPLIER_SESSION:
        {

        }
        break;
#endif
        default:
        {
         /* This case is not reachable because Invalid session requests will be responded with NRC by the DCM itself */
        }
        break;
    }

}
/* ***** END_API DcmAppl_DcmSesCtrlChangeIndication ***** */

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF))
/* ****************************************************************************
 * ***** API public: DcmAppl_DcmGetSesChgPermission ***** */

Std_ReturnType DcmAppl_DcmGetSesChgPermission(Dcm_SesCtrlType SesCtrlTypeActive, Dcm_SesCtrlType SesCtrlTypeNew,
Dcm_NegativeResponseCodeType*ErrorCode)
{
    Std_ReturnType retVal = E_OK;
    (void) SesCtrlTypeActive;
    *ErrorCode = DCOM_NO_ERROR;

    switch (SesCtrlTypeNew)
    {
        case DCM_DEFAULT_SESSION:
        {
            /*Nothing To Do */
        }
        break;

        case DCM_EXTENDED_DIAGNOSTIC_SESSION:
        {
            /* Nothing To Do */
        }
        break;

        case DCM_PROGRAMMING_SESSION:
        {
#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)
			if(dcom_CheckReprogPreConditionFullfilled == TRUE)
			{
		        dcom_CheckReprogPreConditionFullfilled = FALSE;
			}
            else
			{
				*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
				retVal = E_NOT_OK;
			}
#endif
        }
        break;

#if (RBFS_DcomSupplierSession != RBFS_DcomSupplierSession_Disabled)
		case DCM_SUPPLIER_SESSION:
        {
			/* Nothing To Do */
        }
        break;
#endif
        default:
		{
            retVal = DCM_E_SESSION_NOT_ALLOWED;
        }
		break;
    }

    return retVal;
}

/* ***** END_API DcmAppl_DcmGetSesChgPermission ***** */
#endif
