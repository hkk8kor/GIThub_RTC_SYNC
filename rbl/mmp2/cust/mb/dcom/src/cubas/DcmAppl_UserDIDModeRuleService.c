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
#include "DcmDspUds_Uds_Inf.h"
#include "Rte_Dcm.h"

#if (((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
 /**
 * @ingroup DCM_TPL
 * DcmAppl_UserDIDModeRuleService :-\n
 * This API is invoked to do specific checks on the DID read/write/control operation before processing the service.The ErrorCode parameter(Nrc_u8) needs to be updated by the application in case of failed checks.
 *
 * @param[in]     did_u16 : Did under processing
 * @param[in]     dataDirection_en: Indicates whether the DID is read/written/controlled (DCM_SUPPORT_READ/DCM_SUPPORT_WRITE/DCM_SUPPORT_IOCONTROL)
 * @param[out]    Nrc_u8 : NRC to be set by the application
 * @retval               E_OK   : DID specific checks passed successfully \n
 * @retval               E_NOT_OK  : DID specific checks failed\n
 *
 */
Std_ReturnType DcmAppl_UserDIDModeRuleService(Dcm_NegativeResponseCodeType * Nrc_u8, uint16 did_u16,Dcm_Direction_t dataDirection_en)
{
    /* add your implementation here*/
    return E_OK;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif

