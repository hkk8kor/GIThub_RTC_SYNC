/**********************************************************************************************************************
 *
 * COPYRIGHT RESERVED, 2010 Robert Bosch GmbH. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 **********************************************************************************************************************/
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"

#include "Rte_Dcm.h"
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "rba_DiagAdapt.h"
#endif



#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmConfirmation_DcmNegResp :-\n
 * This API is invoked as an indication called by DSD after sending the DSD generated Neg response and after sending the General rejectresponse by DSL.\n
 *
 * @param[in]     idContext   :  Current context identifier which can be used to retrieve the relation between request and confirmation.Within the confirmation, the Dcm_MsgContext\n
 *                               is no more available, so the idContext can be used to represent this relation.
 * @param[in]     dcmRxPduId  :  DcmRxPduId on which the request was received. The source of the request can have consequences for message processing.The idContext is also part of the Dcm_MsgContext.\n
 * @param[in]     status      :  Status indication about confirmation (differentiate failure indication and normal confirmation) / The parameter "Result" of "Dcm_TpTxConfirmation" shall be forwarded\n
 *                               to status depending if a positive or negative responses was sent before.\n
 * @param[out]    None
 * @retval        None
 *
 */
void DcmAppl_DcmConfirmation_DcmNegResp(uint8 SID, uint8 ReqType,uint16 ConnectionId,Dcm_ConfirmationStatusType ConfirmationStatus,Dcm_ProtocolType ProtocolType,uint16 TesterSourceAddress)
{
    /* add your implementation here*/

    /*example code*/
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    rba_DiagAdapt_Confirmation(ConfirmationStatus);
#endif
    /*end example code*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"


