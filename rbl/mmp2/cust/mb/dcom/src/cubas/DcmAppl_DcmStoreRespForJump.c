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

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)



 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmStoreRespForJump :-\n
 * This API is invoked for Storing of Response information when user specific service is used for Jumping to Boot.\n
 * This API should fill in SID|0x40 and response bytes for response. Dcm will only pass the structure
 * for the user to update. It is the responsibility of the user to fill in the correct data.\n
 *     1. Fill ProgConditions->SubFncId     with Subfunc\n
 *     2. Fill ProgConditions->SID          with SID\n
 *     3. Fill ProgConditions.ReqResBuf[0]  with response bytes\n
 *     4. Fill ProgConditions->ReqResLen    with response length\n
 *
 *  Ex:  Response-> Fill SID|0x40, Subfunc, Request Bytes if any\n
 * Response Len needs to be filled. Response length also includes SID and Subfunc.\n
 * If the service has only SID then Response length is 1 byte.\n
 * If the service has only response SID and subfunction in response then Response length is 2 bytes etc.\n
 *
 * Note: This API will be called for every Jump To Boot transition. User needs to modify this API
 * only if User specific service is used for Jump to Boot.\n
 *
 * @param[inout]         ProgConditions : structure for the user to update.
 * @retval               None
 */
void DcmAppl_DcmStoreRespForJump (Dcm_ProgConditionsType * ProgConditions)
{
    /* add your implementation here*/

    /* Necessary code needs to be added here to store the information
     1. Fill ProgConditions->SubFncId with Subfunc
     2. ProgConditions->SID with SID
     3. Dcm_ProgConditions_st.ReqResBuf[0] for response bytes
     4. update response length ProgConditions->ReqResLen */
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

#endif

