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
 * @ingroup DCM_TPL
 * DcmAppl_DcmComModeError :-\n
 * This api is called by DCM to inform application that DCM is not in FULL COMMUNICATION or unable to move to
 * FULL COMMUNICATION MODE for the channel which is having the passed NetworkId.\n
 *
 *  @param[in]         NetworkId : Identifies the channel for which the error has ocured.\n
 *  @param[out]        None
 *  @retval            None\n
 *
 *
 */
void DcmAppl_DcmComModeError (uint8 NetworkId)
{
    /* add your implementation here*/
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
