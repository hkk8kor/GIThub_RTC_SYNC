#ifndef RBSYS_RUNTIMEMEASURE_H__
#define RBSYS_RUNTIMEMEASURE_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Interface to map relevant hooks from RBSYS to rba_Runtime
 *
 * The rba_Runtime provided by CUBAS\EbOS uses the timing monitoring features of RTA-OS.  
 * To detect all preemptions (start and end), it's necessary to have hooks called 
 * from the OS when Tasks, cross core interrupts and CAT2 interrupts occur.
 * CAT1 interrupts are not considered at all.
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"

#include "Os.h"
#include "rba_Runtime.h"

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);





/**
 * @brief Task start hook for rba_runtime
 *
 * @return void
 */
static inline void RBSYS_RuntimeMeasure_TaskStart(TaskType task)
{
  rba_Runtime_TaskStart(task);
}

/**
 * @brief Task end hook for rba_runtime used to monitor the runtime and response time of the configured tasks.
 *
 * @return void
 */
static inline void RBSYS_RuntimeMeasure_TaskEnd(TaskType task)
{
  rba_Runtime_TaskEnd(task);
}

/**
 * @brief ISR start hook for rba_runtime
 *
 * @return void
 */
static inline void RBSYS_RuntimeMeasure_IsrStart(ISRType isr)
{
  rba_Runtime_IsrStart(isr);
}

/**
 * @brief ISR end hook for rba_runtime used to monitor the runtime and response time of the configured ISRs.
 *
 * @return void
 */
static inline void RBSYS_RuntimeMeasure_IsrEnd(ISRType isr)
{
  rba_Runtime_IsrEnd(isr);
}

#if (RBFS_MCORE == RBFS_MCORE_ON)

  /**
   * @brief Cross core interrupt start hook for rba_runtime
   *
   * @return void
   */
  static inline void RBSYS_RuntimeMeasure_CrossCoreIntStart(void)
  {
    rba_Runtime_CrossCoreIntStart();
  }
  
  /**
   * @brief Cross core interrupt end hook for rba_runtime used to monitor the runtime and response time of the configured cross core interrupt.
   *
   * @return void
   */
  static inline void RBSYS_RuntimeMeasure_CrossCoreIntEnd(void)
  {
    rba_Runtime_CrossCoreIntEnd();
  }

#endif



/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
