#ifndef RBEMM_EXTENDED_CALLOUTS_H__
#define RBEMM_EXTENDED_CALLOUTS_H__
/*
**********************************************************************************************************************
*
* COPYRIGHT RESERVED, 2020 Robert Bosch GmbH. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************
*/

/**********************************************************************************/
/* MANDATORY_INTERFACES:               */
#include "Std_Types.h"
#include "RBEMM_Config.h"//Manually added
#include "RBEMM_Types.h"//Manually added
/* MANDATORY_INTERFACES_END:           */
/**********************************************************************************/
/* USED_INTERFACES:                    */

/* USED_INTERFACES_END:                */
/**********************************************************************************/

extern void RBEMM_ExtRequestNetOn_ECUM_WKSOURCE_CAN_Callout(void);
extern void NM_RxIndication( const NetworkHandleType NetworkHandle);

#endif /* INCLUDE PROTECTION: RBEMM_EXTENDED_CALLOUTS_H__ */
