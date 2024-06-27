#ifndef RBSYS_TASKJITTER_H__
#define RBSYS_TASKJITTER_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Process header for task jitter monitoring
 *
 * This interface contains for the monitoring process an extern declaration.
 * The interface itself must be merged via header entry in RBSYS_Subsystem.proc with
 * mergeproc into final RBSYS_Dyn.c
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysMaxTaskx1Jitter,
                          RBFS_SysMaxTaskx1Jitter_5,
                          RBFS_SysMaxTaskx1Jitter_15,
                          RBFS_SysMaxTaskx1Jitter_SERIES);



/* Original Request:
   5% + maximal task scheme adaptation of task x1 is jitter monitored:
   It came out of a signal chain analysis for Gen9 (still valid for 9.3), that a 5% maximum jitter
   shall be reached for WSS. On Gen9 VLV chain stated an additional jitter sensitivity for 10%,
   which was reduced to 5% on Gen9.3.
   During flexray sync investigations it has been agreed to add the task scheme adjust factor
   on top of the 5% for WSS (=> this is done here indirectly with using the synchronized timer).

   In iBooster projects:
   15% + maximal task scheme adaptation of task x1 is jitter monitored:
   There is no such signal chain requirement for the x1 task for iBooster system,
   hence it is suggested to remove the monitoring. The 5% task jitter monitoring was
   causing robustness issue in iBooster projects.
   Instead of completely removing the monitoring, the threshold is kept to a much higher value -
   15% (at least one 500usec task duration).

   Update:
   Both signal chains "VLV" and "WSS", which had requested the monitoring in the past,
   has agreed on disabling the monitoring on series (see EPIC 710301) due to the Defect 633440!
   The jitter monitoring will be kept on "development" builds!
*/

#if (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_5)
  #define JITTER_LIMIT_TASK_X1_PERCENT            (0.05)
#elif (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_15)
  #define JITTER_LIMIT_TASK_X1_PERCENT            (0.15)
#endif

#if (  (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_5)  \
    || (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_15) \
    )
  #define JITTER_LIMIT_TASK_X1_US ( JITTER_LIMIT_TASK_X1_PERCENT * (float64)C_BaseCtrlTaskCycx1_UL * 1000.0 )
  #define JITTER_LIMIT_TASK_X1    ((sint32)RBSYS_convertUsecToTimerTicks( (uint32)(JITTER_LIMIT_TASK_X1_US) ))
#endif

#define TIMERTICKS_PER_TASK_X1  ((sint32)RBSYS_convertUsecToTimerTicks((C_BaseCtrlTaskCycx1_UL * 1000)))





/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
