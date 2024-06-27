/* BASDKey_start */
/*<BASDKey>
**********************************************************************************************************************
*
* COPYRIGHT RESERVED, 2022 Robert Bosch GmbH. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************/
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "DcmDspUds_Seca_Inf.h"
#include "Rte_Dcm.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )



 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmGetUpdatedDelayTime :-\n
 *  Request to application to provide the updated delay time in milliseconds.\n
 *  More Information :-When the delay count is exceeded the delay timer should be started for the corresponding security level.
 *  If the delay count is exceeded this API is called with input parameter DelayTime (configured in SECA configuration) so that the application can change the
 *  Delay time if needed, depending on the number of times delay timer is activated.\n
 *  Ex: Delay Timer value for Security level 0x01 is 100ms, Delay count configured is 0x03.
 *  If Number of attempts performed to unlock security level is 3 the delay timer should be started.
 *  Call the API DcmAppl_DcmGetUpdatedDelayTime(Delay Time) which can change the delay time value and returns the updated delay time (Delay Time * n) where n = 1,2,3 etc.
 *  This API will return the same value sent to this function if the time is not changed by user.
 *
 * @param[in]           SecurityLevel      :  Security level for which the updated delay count is requested.
 * @param[in]           Delaycount         :  Number of times delay timer is activated
 * @param[in]           DelayTime          :  Delay time (ms) introduced after failed access attempts
 * @param[out]          None
 * @retval              Updated Delay time or power on delay time in milliseconds
 *
 */
uint32 DcmAppl_DcmGetUpdatedDelayTime(
        uint8 SecurityLevel,
        uint8 Delaycount,
        uint32 DelayTime )
{
    /* add your implementation here*/
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif /*(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)*/
