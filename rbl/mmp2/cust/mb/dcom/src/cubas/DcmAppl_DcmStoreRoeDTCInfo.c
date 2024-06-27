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

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)


 /**
 * @ingroup DCM_TPL
 * DcmAppl_DcmStoreRDTCInfo :-\n
 * The API will be invoked for persistent setup /start / stop / clear in case of OnDTCStatusChange..
 *
 * @param[in]        RoeeventID : Event Id of Roe Event
 * @param[in]       RoeEventStatus : Status of Roe Event. The possible values of RoeEventStatus is DCM_ROE_CLEARED, DCM_ROE_STOPPED and DCM_ROE_STARTED
 * @param[in]       SourceAddress : Tester Source Address.Source of the address value is from configuration parameter DcmDslProtocolRxTesterSourceAddr.
 * @param[in]       StatusMask : DTC Status Mask information
 * @param[in]       dspRoeStorageState_b : Storage bit information
 * @param[in]       OpStatus : Information of the opstatus
 * @param[in]       dspRoeSession_b : If the current session is Default session, than this parameter will be  true
 * @param[inout]    None
 * @param[out]      ErrorCode: Reason for not setting up the requested event
 * @retval          Std_ReturnType
 *                  E_OK   :    storing event successful.
 *                    E_NOT_OK  : Storing event not ok.
 *                  DCM_E_PENDING: Need more time to store the event
 */
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
Std_ReturnType DcmAppl_DcmStoreRoeDTCInfo( uint8 RoeeventID,
                                                             Dcm_DspRoeEventState_ten RoeEventStatus,
                                                             uint16 SourceAddress,
                                                             uint8 StatusMask,
                                                             boolean dspRoeStorageState_b,
                                                             Dcm_OpStatusType OpStatus,
                                                             boolean dspRoeSession_b,
                                                             Dcm_NegativeResponseCodeType * ErrorCode)
{
    /* add your implementation here*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

#endif
#endif
#endif
