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
#include "Rte_Dcm.h"

 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmConfirmation_GeneralReject :-\n
 * This API is invoked as an indication called by DSD after sending the GeneralReject response due to max number of configured NRC 0x78 reached.Based on the "status" integrator can perform required actions.\n
 *
 * @param[in]     idContext  : Current context identifier which can be used to retrieve the relation between request and confirmation.Within the confirmation, the Dcm_MsgContext\n
 *                             is no more available, so the idContext can be used to represent this relation.
 * @param[in]     dcmRxPduId : DcmRxPduId on which the request was received. The source of the request can have consequences for message processing.\n
 * @param[in]     status     : Status indication about confirmation (differentiate failure indication and normal confirmation) / The parameter "Result" of "Dcm_TpTxConfirmation" shall be forwarded\n
 *                              to status depending if a positive or negative responses was sent before.
 * @param[out]    None
 * @retval        None
 *
 */
void DcmAppl_DcmConfirmation_GeneralReject (uint8 SID, uint8 ReqType,uint16 ConnectionId,Dcm_ConfirmationStatusType ConfirmationStatus,Dcm_ProtocolType ProtocolType,uint16 TesterSourceAddress)
{
    /* add your implementation here*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

