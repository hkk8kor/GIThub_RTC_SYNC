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

#if (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

 /**
 * @ingroup DCM_TPL
 * DcmAppl_UserDTCSettingEnableModeRuleService :-\n
 * This API is invoked to check for conditions to decide if DTC Setting state needs to be enabled
 *
 * @param[in]     None
 * @param[out]    None
 * @retval        E_OK   : Check to decide if the DTC setting state needs to be enabled passed successfully \n
 * @retval        E_NOT_OK  : Check to decide if the DTC setting state needs to be enabled  failed \n
 *
 */
Std_ReturnType DcmAppl_UserDTCSettingEnableModeRuleService(void)
{
    /* add your implementation here*/
    return E_OK;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif

