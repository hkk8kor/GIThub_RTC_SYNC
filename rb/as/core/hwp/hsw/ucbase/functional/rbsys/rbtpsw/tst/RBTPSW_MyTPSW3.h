#ifndef RBTPSW_MYTPSW3_H__
#define RBTPSW_MYTPSW3_H__

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

#define TPSW3_WAITINGFUNCTION_TIMELIMIT 200

typedef struct {
    uint32 untrustedTimeBefore;
    uint32 trustedTime;
    uint32 untrustedTimeAfter;
} TPSW3_WaitingFunction_Switch2Trust_t;

#define TPSW3_WaitingFunction_Switch2Trust_TimeLimit 300
extern volatile uint32 TPSW3_WaitingFunction_Switch2Trust_State;

#define TPSW3_WaitingFunction_UTnoTP_TimeLimit 1000
extern volatile uint32 TPSW3_WaitingFunction_UTnoTP_State;

#define TPSW3_WaitingFunction_UTTP_TimeLimit 300
extern volatile uint32 TPSW3_WaitingFunction_UTTP_State;

#define TPSW3_WaitingFunction_UTTP_NoTp_TimeLimit 300

#define TPSW3_LOCAL_ARRAY 500
extern uint8 TPSW3_dummydata;

#endif //RBFS_TPSWTestsuite_ON

/** @} */
/* End ingroup 'SW-group' */

#endif /* End of multiple include protection */
