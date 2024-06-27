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
#include "Dcm_Types.h"
#include "DcmDspUds_Uds_Prot.h"
#include "Rte_Dcm.h"

/* legacy header, change in RBAPLPLANT is needed to get rid of this legacy */
#include "RBAPLHELP_ServiceStateHandler.h"

#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "rba_DiagAdapt.h"
#endif



#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmConfirmation :-\n
 *  This function confirms the successful transmission or a transmission error of a diagnostic service.This is the right time to perform any application state transitions.\n
 *  The idContext and the dcmRxPduId are required to identify the message which was processed.This information can be used to figure out the relation to any data provided by the application.\n
 *  This function is only called if processing of the service itself was done within the application.Based on the "status" integrator can perform required actions.\n
 *
 *
 * @param[in]     idContext    : Current context identifier which can be used to retrieve the relation between request and confirmation.Within the confirmation, the Dcm_MsgContext\n
 *                                is no more available, so the idContext can be used to represent this relation.
 *
 * @param[in]     dcmRxPduId   : DcmRxPduId on which the request was received. The source of the request can have  consequences for message processing.The idContext is also part of the Dcm_MsgContext.\n
 *
 * @param[in]     SourceAddress : Tester source address\n
 * @param[in]     status        : Status indication about confirmation (differentiate failure indication and normal confirmation) / The parameter "Result" of "Dcm_TpTxConfirmation" shall be forwarded\n
 *                                 to status depending if a positive or negative responses was sent before.
 *
 * @param[out]    None
 * @retval        None
 *
 */
void DcmAppl_DcmConfirmation (uint8 SID, uint8 ReqType,uint16 ConnectionId,Dcm_ConfirmationStatusType ConfirmationStatus,
                              Dcm_ProtocolType ProtocolType,uint16 TesterSourceAddress)
{


    /* add your implementation here*/

    /* example code: call DiagAdapt, if this component is used*/
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    rba_DiagAdapt_Confirmation(ConfirmationStatus);
#endif
    /*end example code*/

    /* example code for PMA interaction: this part is needed to make PMA running properly*/
#if(RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED != DCM_CFG_OFF)
    if (SID == RBA_DCMPMA_SID_PLANTMODEACTIVATION)
    {
        if((ConfirmationStatus == DCM_RES_POS_OK) && (rba_DcmPma_PlantModeActivation_en == RBA_DCMPMA_PLANTMODE_INIT2))
        {
            /* switch to plant mode*/

            rba_DcmPma_PlantModeActivation (TRUE);
        }
    }
    (void)ReqType;
    (void)TesterSourceAddress;
#endif
  if (rba_DcmPma_PlantModeStatus_b == TRUE)
  {
      APLPLANT_DcmConfirmation (SID,ReqType,ConnectionId,ConfirmationStatus,ProtocolType,TesterSourceAddress);
  }

}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

/* NO_TOOL_SCAN_END: */
