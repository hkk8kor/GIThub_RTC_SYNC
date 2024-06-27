#ifndef RBSYS_TASKSYNC_H__
#define RBSYS_TASKSYNC_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * \file
 * \brief Task Sync services
 *
 * This interface provides the possibility for task scheme adaptation.
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSync,
                          RBFS_TaskSync_ON,
                          RBFS_TaskSync_OFF);


#if (RBFS_TaskSync == RBFS_TaskSync_ON)

  /* adapts task scheme timebase with given value; adaptation is done
     cyclically until given value has been reached. The parameter is
     limited internally to the maximum system adjust value; a call during
     running adaptation reinits this process;
     parameter: positive value: task scheme acceleration, negative: deceleration;
     parameter must be in RTI ticks (see macro C_TimerTicksPerus_UL)  */
  void RBSYS_SRMS_adapt_timebase(sint32 ticks_to_adapt);

  /* requested adaptation ticks left; i.e. ==0 when done */
  sint32 RBSYS_SRMS_adapt_ticks_left(void);

  /* Function returns timer ticks to next x1 basecycle activation - only to be called within the x1 task */
  extern uint32 RBSYS_GetTimeToNextBaseCycle(void);


  /* only for internal test usage */
  extern uint16 RBSYS_SRMS_test_advance_ticks;
  extern uint16 RBSYS_SRMS_test_retard_ticks;

#endif

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
