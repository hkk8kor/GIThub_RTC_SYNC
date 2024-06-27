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
 * DcmAppl_DcmRespWarmInit :-\n
 * This API will be called for every Jump To Boot transition.User needs to modify this API only if User specific service is used for Jump to Boot.
 * If the user specific service is used for Jump to Boot using Warm Init, the necessary state changes for the service needs to be changed in this api to transmit
 * the final response before performing the reset operation.
 *
 * @param[in]       None
 * @param[out]      None
 * @retval          None
 */
void DcmAppl_DcmRespWarmInit(void)
{
    /* add your implementation here*/

    /* If the user specific service is used for Jump to Boot using Warm Init, the necessary
     * state changes for the service needs to be changed here to transmit the final response
     * before performing the reset operation.
     */
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif

