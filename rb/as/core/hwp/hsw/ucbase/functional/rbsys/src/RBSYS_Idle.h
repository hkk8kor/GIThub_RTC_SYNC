#ifndef RBSYS_IDLE_H__
#define RBSYS_IDLE_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Idle handling
 *
 * This interface provides the generic idle loop together with an extension for Multi-Core systems. This extension provides the possiblility
 * to configure the speed of the idle loop depending on a rerun request, which could be used to reduce bus congestion in M-Core systems.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */


/* define allows polyspace or RBSYS UTs stubbing of idle loop */
#define SYS_ENDLESS_IDLE_LOOP     for(;;)
  
/* idle loop is not static because of polyspace analysis */
extern void sys_idle_loop(void);


extern void sys_general_idleloop(unsigned int core);
extern void sys_delayed_idleloop(unsigned int core);
extern void sys_idleloop_request_rerun(void);



/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
