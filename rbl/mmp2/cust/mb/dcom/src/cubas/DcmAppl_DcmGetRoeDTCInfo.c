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


#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF))

#if (DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)

 /**
 * @ingroup DCM_TPL
 * DcmAppl_DcmGetRoeDTCInfo :-\n
 * The API will be invoked in the init to recover Roe Events and its states from NvM in case of OnDTCStatusChange.
 *
 * @param[in]      RoeeventID : Event Id of Roe Event.
 * @param[out]    RoeEventStatus : Status of Roe Event. The possible values of RoeEventStatus is DCM_ROE_CLEARED, DCM_ROE_STOPPED and DCM_ROE_STARTED
 * @param[out]    SourceAddress : Tester Source Address. Source of the address value is from configuration parameter DcmDslProtocolRxTesterSourceAddr
 * @param[out]    StatusMask : DTC Status Mask information
 * @param[out]    dspRoeCtrlStorageState_b : Storage bit information of the control request
 * @param[out]   dspRoeSetUpStorageState_b : Storage bit information of the set up request
 * @param[out]    dspRoeSession_b : If the current session is Default session, than this parameter will be  true
 * @retval        Std_ReturnType
  *
 */
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
Std_ReturnType DcmAppl_DcmGetRoeDTCInfo(uint8 RoeeventID,
                                                Dcm_DspRoeEventState_ten * RoeEventStatus,
                                                uint8 * RoeEventWindowTime_u8,
                                                uint16 * SourceAddress,
                                                uint8 * StatusMask,
                                                boolean * dspRoeCtrlStorageState_b,
                                                boolean * dspRoeSetUpStorageState_b,
                                                boolean * dspRoeSession_b)
{

    /* add your implementation here*/

}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

#endif
#endif
