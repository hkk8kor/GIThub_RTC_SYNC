/**********************************************************************************************************************
*
* COPYRIGHT RESERVED, Robert Bosch GmbH, 2023. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************/


/*****************************************************************************************
 * Header Includes *
 *****************************************************************************************/

#include "Std_Types.h"
#include "BswM.h"
#include "BswM_Prv.h"

/***********************************************************
* Function name: void BswM_Appl_IncompatibleGenerator( void )
* Description: Function called by BswM in case of version incompatibility in the post-build generate.
* This an empty function. User will write the error handler code here.
* Return value: None
* Remarks:
***********************************************************/

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

void BswM_Appl_IncompatibleGenerator( void )
{
    /* Fill the error handling code to handle the version mis-match in the post-build structure */
    return;
}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"


/*
 **********************************************************************************************************************
*/
