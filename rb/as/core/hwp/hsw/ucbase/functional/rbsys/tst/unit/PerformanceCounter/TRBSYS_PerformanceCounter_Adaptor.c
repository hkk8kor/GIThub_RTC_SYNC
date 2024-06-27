#include "RBSYS_PerformanceCounter.c"



#include "TRBSYS_PerformanceCounter_Adaptor.h"
#include "RBSYS_Config.h"

#if(((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) || (RBFS_uCFamily == RBFS_uCFamily_STMStellar)) && RBFS_SYSDebugFeatures == RBFS_SYSDebugFeatures_ON)

RBSYS_PerformanceCounterMetrics_t TRBSYS_PerformanceCounterGetMetrics(unsigned int coreId)
{
  return RBSYS_PerformanceCounterMetrics[coreId];
}

RBSYS_PerformanceCounterMonitoringInfo_t TRBSYS_PerformanceCounterGetMonitoringInfo(unsigned int coreId)
{
  return RBSYS_PerformanceCounterMonitoringInfo[coreId];
}

#endif