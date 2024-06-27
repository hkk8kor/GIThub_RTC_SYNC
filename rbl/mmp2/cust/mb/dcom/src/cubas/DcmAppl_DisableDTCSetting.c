/**********************************************************************************************************************
*
* COPYRIGHT RESERVED, 2022 Robert Bosch GmbH. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************/
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "DcmDspUds_Cdtcs_Inf.h"
#include "Rte_Dcm.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 *@ingroup DCM_TPL
 * DcmAppl_DisableDTCSetting:-\n
 * This api is called to get permission to disable DTC Setting.
 *
 * @param[inout]   ErrorCode: Pointer to Negative Response Code.
 * @retval      None
 *
 *
 */
void DcmAppl_DisableDTCSetting ( Dcm_NegativeResponseCodeType * ErrorCode )
{
    /* add your implementation here*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

#endif /* (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) */

