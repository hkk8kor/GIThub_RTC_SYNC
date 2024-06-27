/* BASDKey_start */
/*<BASDKey>
**********************************************************************************************************************
*
* COPYRIGHT RESERVED, 2022 Robert Bosch GmbH. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************/

#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"

#if ((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)))

 /**
 * @ingroup DCM_TPL
 * DcmAppl_Switch_DcmResponseOnEvent :-\n
 * This api is called to notify the application regarding change in event status of  Roe DID or Roe DTC
 *
 * @param[in]     RoeEventId_u8 : Event Identifier of the DID/DTC
 *                RoeEventStatus_en : Event Status (DCM_ROE_STARTED/DCM_ROE_STOPPED/DCM_ROE_CLEARED)
 * @retval        None
 *
 */
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
void DcmAppl_Switch_DcmResponseOnEvent(uint8 RoeEventId_u8 , Dcm_DspRoeEventState_ten RoeEventStatus_en)
{
    /* add your implementation here*/

}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"


#endif /* ((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF))) */
