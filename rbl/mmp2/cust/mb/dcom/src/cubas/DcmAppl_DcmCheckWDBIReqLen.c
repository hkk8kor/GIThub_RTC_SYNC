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
#include "DcmDspUds_Wdbi_Inf.h"
#include "Rte_Dcm.h"




#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

/**
 * @ingroup DCM_TPL
 *  DcmAppl_DcmCheckWDBIReqLen :-\n
 *  This function is used by the application to perform the exact length checkfor the request in case variable length signals are configured for the requested DID.\n
 *  As per the current implementation of WDBI service in Dcm, if there is one variable length signal configured, then no other signals are allowed to be configured for that DID.\n
 *  So, the passed length parameter to this callback function shall include the request length of only one variable length signal.
 *
 * @param[in]        nrDID_u16  : Received DID in the request \n
 * @param[in]        dataReqLen_u32 : Length of the received request excluding the DID(length of the variable length signal in the request).\n
 * @param[out]       None
 * @retval           E_OK:     If the request length is correct.\n
 * @retval           E_NOT_OK: If the request length is incorrect.In this case, Dcm shall trigger NRC 0x13(DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT) in the response
 *
 */
Std_ReturnType DcmAppl_DcmCheckWDBIReqLen(uint16 nrDID_u16, uint32 dataReqLen_u32)
{
    /* add your implementation here*/
    return E_OK;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif /* #if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) */
