/**********************************************************************************************************************
*
* COPYRIGHT RESERVED, Robert Bosch GmbH, 2022. All rights reserved.
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
 * DcmAppl_DcmGetNRCForMinLengthCheck :-\n
 * The API is used by application to get the NRC to be returned as minimum length check has failed for vendor specific service supporting sub function\n
 *
 * @param[in]  dataProtocolId_u8   : Protocol identifier of the protocol on which the request was received
 * @param[in]  dataSid_u8          : Service Identifier of the service in the request
 * @param[out] dataErrorCode_u8    : Pointer to Negative Response Code, OUT Parameter
 *
 * @retval     None
 *
 */
void DcmAppl_DcmGetNRCForMinLengthCheck(Dcm_ProtocolType dataProtocolId_u8, uint8 dataSid_u8,
        Dcm_NegativeResponseCodeType * dataErrorCode_u8)
{
    /* add your implementation here*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
