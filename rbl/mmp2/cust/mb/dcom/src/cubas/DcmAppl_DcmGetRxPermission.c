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
 *  @ingroup DCM_TPL
 *  DcmAppl_DcmGetRxPermission:-\n
 *  This API is called by Dcm_StartOfReception before processing the new request. The use case for such an API is rejection/accepting Rx Requests arriving from particular protocols,
 *  for different variants of the same software.Integrator has to add code to check the receiving protocol based on the passed ProtocolId.\n
 *  The user may return E_NOT_OK if the request is to be rejected. Else, E_OK must be returned.It must be noted that all return values other than E_OK (Including DCM_E_PENDING) are treated alike,
 *  and the request will be rejected for all return values other than E_OK.If no info data is given, that the user might get here a NULL pointer.
 *
 * @param[in]     ProtocolId : The protocol id
 * @param[in]     DcmRxPduId : Pdu Id corresponding to the received Pdu
 * @param[in]     TpSduLength : Total message length of the request to be received
 * @param[in]     info : Contains the information about received message
 * @param[out]    None
 * @retval            E_OK      : The Rx Request can be accepted and processed
 * @retval            E_NOT_OK  : The Rx Request is rejected
 *
 */
Std_ReturnType DcmAppl_DcmGetRxPermission (
        Dcm_ProtocolType ProtocolId,
        PduIdType DcmRxPduId,
        const PduInfoType * info,
        PduLengthType TpSduLength)
{

    /*User has to add code here to check the receiving protocol based on the passed ProtocolId
      The user may return E_NOT_OK if the request is to be rejected. Else, E_OK must be returned.
      It must be noted that all return values other than E_OK (Including DCM_E_PENDING) are treated
      alike, and the request will be rejected for all return values other than E_OK*/

    /*  CODE EXAMPLE
        if(ProtocolId == DCM_OBD_ON_CAN)
        {
            return (E_NOT_OK);
        }
        */
    return E_OK;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
