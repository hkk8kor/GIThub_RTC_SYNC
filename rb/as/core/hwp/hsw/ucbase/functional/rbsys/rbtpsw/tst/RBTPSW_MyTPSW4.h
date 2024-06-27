#ifndef RBTPSW_MYTPSW4_H__
#define RBTPSW_MYTPSW4_H__

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
#include "Compiler.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_OFF,
                          RBFS_TPSWTestsuite_ON);


#if (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON)

#define TPSW4_DATASIZE 20

extern uint32 TPSW4_data[TPSW4_DATASIZE];

void TPSW4_OutOfRange(void);

void TPSW4_P2CONST_Param      (P2CONST(uint32, , )      param);
void TPSW4_CONSTP2VAR_Param   (CONSTP2VAR(uint32, , )   param);
void TPSW4_CONSTP2CONST_Param (CONSTP2CONST(uint32, , ) param);

#endif

/** @} */
/* End ingroup 'SW-group' */

#endif /* End of multiple include protection */
