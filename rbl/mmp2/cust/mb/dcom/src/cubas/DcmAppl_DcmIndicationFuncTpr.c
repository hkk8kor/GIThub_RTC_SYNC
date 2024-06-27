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
 *  @ingroup DCM_TPL
 *  DcmAppl_DcmIndicationFuncTpr:-\n
 *  This API is called by DCM if function functional tester present request is received with suppress positive bit set in the request.\n
 *  User has to add code if some action is intended.
 *
 * @param[in]   None
 *
 * @param[out]  None
 *
 * @retval      None
 *
  */
void DcmAppl_DcmIndicationFuncTpr(void)
{
    /* add your implementation here*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
