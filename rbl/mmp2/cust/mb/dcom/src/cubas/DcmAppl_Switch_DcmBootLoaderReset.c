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
 * DcmAppl_Switch_DcmBootLoaderReset :-\n
 * Notify the application regarding Jump to BootLoader.Application can take the further actions.
 *
 * @param[in]     None
 * @param[out]    None
 * @retval        None
 *
 */
void DcmAppl_Switch_DcmBootLoaderReset(void)
{
    /* add your implementation here*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

#endif
