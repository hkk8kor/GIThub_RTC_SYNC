#ifndef RBSYS_PERFORMANCECOUNTER_H__
#define RBSYS_PERFORMANCECOUNTER_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Process header for task performance counter monitoring
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
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SYSDebugFeatures,
                          RBFS_SYSDebugFeatures_ON,
                          RBFS_SYSDebugFeatures_OFF);

#if(RBFS_SYSDebugFeatures == RBFS_SYSDebugFeatures_ON)

  #if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    /**
    * TMU of P1x is not accessible from the CPU, it is only supposed to be used by external components like emulator debugger.
    * Therefore no performance counter monitoring is possible.
    * ATTENTION: When using an external debugger, TMU cannot count some code flash related events correctly, see HW Erratum RB117.
    */
  #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) || (RBFS_uCFamily == RBFS_uCFamily_STMStellar))
    typedef struct  /*TOOL_SCAN*/
    {
      #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        float32 ipc;
        float32 is_hit_rate;
        float32 cpu_stall_rate;
        #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
          float32 branch_prediction_hit_rate;
        #endif
      #elif (RBFS_uCFamily == RBFS_uCFamily_STMStellar)
        float32 ipc;
        float32 is_hit_rate;
        float32 da_hit_rate;
        float32 cpu_stall_rate_frontend;
        float32 cpu_stall_rate_backend;
        float32 branch_prediction_hit_rate;
      #endif
    }RBSYS_PerformanceCounterMetrics_t;

    typedef struct
    {
      // Used to limit the configuration of the performance counters to the first execution on every PE
      boolean initialized;
      // Used to delay reading and resetting of performance counters + calculation of metrics by 12 task executions
      uint32 execution_cnt;
    }RBSYS_PerformanceCounterMonitoringInfo_t;
  #else
    #error ("Performance Counter is not implemented for this uCFamily.")
  #endif /* RBFS_uCFamily */
#endif /* RBFS_SYSDebugFeatures_ON */

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
