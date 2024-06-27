/**********************************************************************************************************************
*
* COPYRIGHT RESERVED, Robert Bosch GmbH, 2023. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************/

#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"
#include "DcmAppl.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
#include "rbl_SwcDiagAdapter_Srv.h"
#endif
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmControlDtcSettingEnableStatus :-\n
 * This API is called when the control dtc setting status is changed.
 * ControlDtcSettingEnableStatus is true, if Dtc setting is enabled
 * ControlDtcSettingEnableStatus is false if dtc setting is disabled.
 * Integrator can perform  further actions basecd on the  ControlDtcSettingEnableStatus\n
 *
 * @param[in]  ControlDtcSettingEnableStatus: Value to indicate whether DTC is enabled or not\n
 * @param[out] None
 * @retval None
 */
FUNC (void, DCM_APPL_CODE) DcmAppl_DcmControlDtcSettingEnableStatus(VAR(boolean,AUTOMATIC) ControlDtcSettingEnableStatus)
{
	(void)(ControlDtcSettingEnableStatus);
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	rbl_SwcDiagAdapter_DcmControlDtcSettingEnableStatus(ControlDtcSettingEnableStatus);
#endif
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) */
