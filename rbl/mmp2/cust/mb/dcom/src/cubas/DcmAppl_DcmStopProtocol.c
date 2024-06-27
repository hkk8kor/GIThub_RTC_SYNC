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

#include "Rte_Dcm.h"


#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "rba_DiagAdapt.h"
#endif

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmStopProtocol :-\n
 * This API is invoked if a running diagnostic requested is preempted by a higher priority request (of an other protocol, e.g. OBD),
 * application is requested to abort further processing of running request and finish with Dcm_ProcessingDone().\n
 * With this callback function, application can shutdown during protocol preemption.
 * @param[in]       ProtocolID                : Name of the protocol (IDs configured within DCM_PROTOCOL_ID)
 * @param[in]       TesterSourceAddress       : Active Tester Source Address
 * @param[in]       ConnectionId              : Active Connection ID
 * @param[out]      None
 * @retval          E_OK : Always it will return this value.
 */
Std_ReturnType DcmAppl_DcmStopProtocol(Dcm_ProtocolType ProtocolID,uint16 TesterSourceAddress, uint16 ConnectionId)
{
    /* add your implementation here*/

    /*example code*/
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    rba_DiagAdapt_StopProtocol(ProtocolID);
#endif
    /*end example code*/
    return E_OK;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
