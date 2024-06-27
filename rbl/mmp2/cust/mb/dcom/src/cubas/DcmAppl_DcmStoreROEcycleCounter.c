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
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && ((DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)))

 /**
 * @ingroup DCM_TPL
 * DcmAppl_DcmStoreROEcycleCounter :-\n
 * The API will be invoked to store the CycleValue in NvM
 *
 * @param[in]      RoeeventID : Event Id of Roe Event.
 * @param[in]     CycleValue : CycleValue of eventWindowTime.
 *                CycleValue=0x02 (EventWindowTime is Infinity)
 *                CycleValue=0x03 (EventWindowTime is CurrentCycle)
 *                CycleValue=0x04 (EventWindowTime is CurrentAndFollowingCycle)
 *                CycleValue=0x00 (EventWindowTime is not set)
 * @param[in]     OpStatus:  Information of the opstatus
 * @param[out]    ErrorCode: Reason for not setting up the requested event
 *
 * @retval        void
 *
 */
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
void DcmAppl_DcmStoreROEcycleCounter(uint8 RoeeventID, uint8 CycleValue )
{
    /* add your implementation here*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

#endif
#endif
