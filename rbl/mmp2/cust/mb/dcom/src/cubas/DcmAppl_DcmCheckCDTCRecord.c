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
 * @ingroup DCM_TPL
 * DcmAppl_DcmCheckCDTCRecord:-\n
 * This api should check the validity of the controlOptionRecord passed in the CDTC request.
 * @param[in]   ControlOptionRecord : Constant pointer to DTCSessionControlOptionRecord in request\n
 * @param[in]   Length              : Variable to hold length of contrl option record in request\n
 * @param[out]  ErrorCode           : Pointer to Negative Response Code, OUT Parameter\n
 *
 * @retval      E_OK : If contents of ControlOptionRecord is valid.\n
 * @retval      E_NOT_OK : If contents of ControlOptionRecord is invalid.\n
 */
Std_ReturnType DcmAppl_DcmCheckCDTCRecord (
                                    const uint8 * ControlOptionRecord,
                                    uint8 Length,
                                    Dcm_NegativeResponseCodeType * ErrorCode
                                                                )
{
    /* add your implementation here*/
    return E_OK;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif /* (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) */

