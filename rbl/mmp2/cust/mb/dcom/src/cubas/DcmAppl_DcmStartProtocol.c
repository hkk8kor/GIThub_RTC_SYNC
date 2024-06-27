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

#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "rba_DiagAdapt.h"
#endif

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmStartProtocol :-\n
 * With this callback function, application can check whether the conditions for further processing of the protocol identified by the passed ProtocolID.\n
 * Application can reject further processing of requested protocol due to failed conditions.
 *
 * @param[in]       ProtocolID                : Name of the protocol (IDs configured within DCM_PROTOCOL_ID)
 * @param[in]       TesterSourceAddress       : Active Tester Source Address
 * @param[in]       ConnectionId              : Active Connection ID
 * @param[out]      None
 * @retval          DCM_E_OK                  : conditions in application allows further processing of protocol\n
 * @retval          DCM_E_PROTOCOL_NOT_ALLOWED: conditions in application does not allow further processing of protocol
 */

Std_ReturnType DcmAppl_DcmStartProtocol(Dcm_ProtocolType ProtocolID,uint16 TesterSourceAddress, uint16 ConnectionId)
{
    /* add your implementation here*/

    /*example code*/
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    rba_DiagAdapt_StartProtocol(ProtocolID);
#endif
    /*end example code*/
    return E_OK;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

