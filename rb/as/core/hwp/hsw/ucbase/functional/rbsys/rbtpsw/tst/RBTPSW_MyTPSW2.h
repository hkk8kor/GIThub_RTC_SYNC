#ifndef RBTPSW_MYTPSW2_H__
#define RBTPSW_MYTPSW2_H__

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


RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWCapsule,
                          RBFS_TPSWCapsule_OFF,
                          RBFS_TPSWCapsule_SC3,
                          RBFS_TPSWCapsule_SC4);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_OFF,
                          RBFS_TPSWTestsuite_ON);


#if (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON)

RBTPSW_DECLARE_MPUTABLE_LCFENTRY(MYTPSW2_GLOBAL_LCF)

typedef struct{
  uint32 a;
  int8_t b;
} mytest_t;


#if (RBFS_MCORE == RBFS_MCORE_ON)
extern volatile uint32 MYTPSW2_LRAM0_Table[];
extern volatile uint32 MYTPSW2_LRAM1_Table[];
#endif

extern uint32 TPSW2_TestCaseId;
extern uint32 TPSW2_TestSuiteExecutionCount;
extern uint32 TPSW2_ErrorCounter_UL;

#define TPSW2_TIMINGANDMPUABORT_TIMELIMIT 100
#define TPSW2_MPUEXCP_TIMELIMIT 50

void TPSW2_WaitingFunction(uint32  Limit);

#define TPSW2_WaitingFunction_TP_TimeLimit 200

#define TPSW2_DATATABLESIZE 100
extern uint32 TPSW2_DataTable[TPSW2_DATATABLESIZE];

extern volatile uint32 MYTPSW2_Data;

RBTPSW_DECLARE_MPUTABLE_LCFENTRY(MYTPSW2_LCF)
RBTPSW_DECLARE_MPUTABLE_LCFENTRY(MYTPSW2_GLOBAL_LCF)
#if (RBFS_MCORE == RBFS_MCORE_ON)
RBTPSW_DECLARE_MPUTABLE_LCFENTRY(MYTPSW2_LOCAL0_LCF)
RBTPSW_DECLARE_MPUTABLE_LCFENTRY(MYTPSW2_LOCAL1_LCF)
#endif



#endif

/** @} */
/* End ingroup 'SW-group' */

#endif /* End of multiple include protection */

