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
#include "DcmDspUds_Seca_Inf.h"
#include "Rte_Dcm.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )

 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmGetUpdatedDelayForPowerOn :-\n
 *  This API is used for providing the means to the application to change the power On delay for security access service on COLD start.\n
 *  More Information :The user can change the power on Delay for the particular security level during the power on Init.
 *  Failed attempt count before the reset is restored from NVM(application) and passed as an input parameter to this appl funtion.
 *  The user can refer to this failed attempt count and accordingly return the delay for power ON.
 *  If the user does not want to change the power on Delay at this point, then no need to change the appl function as the input value DelayTime is returned by default from this appl function.
 *  DelayTime is the configured power on delay for the particular security level. Hence the configured delay shall be retained in Dcm if this appl function is not modified by the user.
 *
 * @param[in]           SecurityLevel    :    Security level for which the updated power on delay is requested.
 * @param[in]           Delaycount       :    Failed attempt count restored from NVM
 * @param[in]           DelayTime        :    configured power on Delay time in (milliseconds) for that security level
 * @param[out]          None
 * @retval              Updated power on delay time in milliseconds
 *
 */
uint32 DcmAppl_DcmGetUpdatedDelayForPowerOn(
        uint8 SecurityLevel,
        uint8 Delaycount,
        uint32 DelayTime )
{
    /* add your implementation here*/
}


#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif /*(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)*/
