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
 * DcmAppl_DcmModifyResponse :\n
 *  This function is provided to allow the application to conditionally modify the responses from all the services.
 *  a) For negative response, the application can modify only the NRC value.
    b) For positive response, application can add only the additional bytes to the response. But modification of the contents filled by the service is not allowed.
    c) Application is not allowed to transform the positive response to  the negative response and vice versa.\n
    d) If the project does not want the modification of the response, the Appl function need not be modified and can be retained as it is. But the *nrBufSize_pu32 (modified response length)
       has to be made zero explicitly.

 *
 * @param[in]           dataSid_u8       :   Active Service Identifier
 * @param[in]           dataNRC_u8       :   Negative response code to indicate application about the type of response\n
 *                                           i.e. whether the response is positive or negative.
 * @param[in]        adrBufPtr_pu8       :   Buffer provided to application for filling the additional information in case of positive response.\n
 *                                           Buffer provided to application for modifying the NRC value alone in case of negative response.
 * @param[inout]        nrBufSize_pu32   :   [in] Available response buffer length\n
 *                                           [out] Response length filled by application
 *
 * @retval              None
 */
void DcmAppl_DcmModifyResponse(uint8 dataSid_u8,
        uint8 dataNRC_u8,
        const uint8 * adrBufPtr_pu8,
        uint32 * nrBufSize_pu32)
{
    /*Statements are added just to avoid warning*/
    (void)dataSid_u8;
    (void)dataNRC_u8;
    (void)adrBufPtr_pu8;

    /* In case the application wants to modify the response bytes it should update this variable with the length
     * of bytes added , else response length is zero by default */
    *nrBufSize_pu32 = 0;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
