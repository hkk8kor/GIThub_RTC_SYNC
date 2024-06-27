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
 *  DcmAppl_DcmSecurityLevelLocked:-\n
 *  For each security level the number of unsuccessful attempts after which the security level is locked will be configured (Lock Count).
 *  If this Lock count is reached, the corresponding security level will be locked and a notification is given to application is given using this API.
 *  Integrator can perform required operations based on the notification.\n
 *
 *  Ex: Lock count configured for Security Level 0x01 is 0x02.\n
 *  Tester sends to ECU, 2 key request with invalid Key. ECU sees that the number of attempts has been reached and locks the security level.
 *  A notification will be given to application using the API DcmAppl_DcmSecurityLevelLocked.
 *
 * @param[in]       SecTabIdx : Index of the Security Table in configuration(Security level)\n
 * @param[out]      None
 * @retval          None
 *
 */
void DcmAppl_DcmSecurityLevelLocked(uint8 SecTabIdx)
{
    /* add your implementation here*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif /*(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)*/
