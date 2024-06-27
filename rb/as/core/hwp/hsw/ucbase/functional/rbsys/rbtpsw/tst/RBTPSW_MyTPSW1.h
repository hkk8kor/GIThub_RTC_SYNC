#ifndef RBTPSW_MYTPSW1_H__
#define RBTPSW_MYTPSW1_H__

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
#include "Os.h"


RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_OFF,
                          RBFS_TPSWTestsuite_ON);


#if (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON)

typedef void vvfunc_t(void);

void TPSW1_TestGoodCases(void);
void TPSW1_TPSW3_WaitingFunction_Switch2Trust_GC(void);
void TPSW1_TPSW3_WaitingFunction_Switch2Trust_BC1(void);
void TPSW1_TPSW3_WaitingFunction_Switch2Trust_BC2(void);
void TPSW1_TPSW3_WaitingFunction_Switch2Trust_BC3(void);
void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_GoodCase_Tp(void);
void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase1_Tp(void);
void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase2_Tp(void);
void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase3_Tp(void);
void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_GoodCase_NoTp(void);
void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase1_NoTp(void);
void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase2_NoTp(void);
void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase3_NoTp(void);
void TPSW1_TPSW3_UTTP_GoodCase(void);
void TPSW1_TPSW3_UTTP_BadCase1(void);
void TPSW1_TPSW3_UTTP_BadCase2(void);
void TPSW1_TPSW3_UTTP_BadCase3(void);


extern volatile boolean TPSW1_ActiveWaiting;
extern volatile boolean TPSW1_ActiveWaitingPreemptedCoreAck;
extern volatile boolean TPSW1_ActiveWaitingMultiCoreAck;
extern uint32 TPSW1_ErrorCounter_UL;

extern uint32 TPSW1_ForceTestId;

#endif

/** @} */
/* End ingroup 'SW-group' */

#endif /* End of multiple include protection */
