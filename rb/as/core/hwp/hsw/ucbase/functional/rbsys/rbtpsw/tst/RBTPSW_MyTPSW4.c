/**
 * @ingroup 'SW-group'
 * @{
 *
 * \file
 * \brief 'Short description of this module, up to 80 characters
 *
 * 'Detailed description of this module, several lines/paragraphes'
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_uCRegisters.h"  // peripheral labels


/* realized interfaces */
#include "RBTPSW_MyTPSWCapsule.h"
#include "RBTPSW_MyTPSW4.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_OFF,
                          RBFS_TPSWTestsuite_ON);


#if (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON)

/*
TPSW4 has no lcf entry. The TPSW4_data[] array is opened with the RBTPSW_MPUCONFIG_BYADDRESS() macro.
*/
uint32 TPSW4_data[TPSW4_DATASIZE];

void TPSW4_OutOfRange(void)
{
  /* Intentional write off the array range of TPSW4_data[]
   * Error 175: "Subscript out of range" (175)" should be ignored by compiler */
  #ifdef __ghs__
  #pragma ghs nowarning 175
  #endif

  TPSW4_data[TPSW4_DATASIZE] = 0; // illegal access

  #ifdef __ghs__
  #pragma ghs endnowarning 175
  #endif
}


void TPSW4_P2CONST_Param      (P2CONST(uint32, , )      param) {}
void TPSW4_CONSTP2VAR_Param   (CONSTP2VAR(uint32, , )   param) {}
void TPSW4_CONSTP2CONST_Param (CONSTP2CONST(uint32, , ) param) {}

#endif

/** @} */
/* End ingroup 'SW-group' */
