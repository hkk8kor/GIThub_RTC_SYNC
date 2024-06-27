#ifndef RBTPSW_MYTPSWX_H__
#define RBTPSW_MYTPSWX_H__

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


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_OFF,
                          RBFS_TPSWTestsuite_ON);


#if (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON)

/* Good Case - With Return */

#define BackgroundTestApp_Ret_1_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_Ret_2_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_Ret_3_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_Ret_4_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_Ret_5_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_Ret_6_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_Ret_7_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_Ret_8_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_Ret_9_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_Ret_0_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

/* Good Case - No Return */
#define BackgroundTestApp_NoRet_1_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_NoRet_2_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_NoRet_3_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_NoRet_4_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_NoRet_5_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_NoRet_6_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_NoRet_7_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_NoRet_8_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_NoRet_9_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_NoRet_0_GOODCASE_WAITINGFUNCTION_TIMELIMIT 50

#define BackgroundTestApp_WAITINGFUNCTION_TIMELIMIT 100

#define BackgroundTestApp_WAITINGFUNCTION_DYNLIMIT_RUNTIME 10

/* Bad Case - With Return */

#define BackgroundTestApp_Ret_1_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_Ret_2_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_Ret_3_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_Ret_4_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_Ret_5_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_Ret_6_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_Ret_7_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_Ret_8_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_Ret_9_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_Ret_0_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

/* Bad Case - No Return */
#define BackgroundTestApp_NoRet_1_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_NoRet_2_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_NoRet_3_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_NoRet_4_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_NoRet_5_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_NoRet_6_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_NoRet_7_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_NoRet_8_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_NoRet_9_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#define BackgroundTestApp_NoRet_0_BADCASE_WAITINGFUNCTION_TIMELIMIT 250

#endif

/** @} */
/* End ingroup 'SW-group' */

#endif /* End of multiple include protection */
