#ifndef TRBHSWESR_FAILUREHANDLING_H__
#define TRBHSWESR_FAILUREHANDLING_H__

#include "Dem.h"

typedef Dem_DebugDataType RBHSWDEM_DebugDataType_t;

static inline void RBHSWESR_ReportElShutdownErrorWithEnvData(Dem_EventIdType          EventId,
                                                             Dem_EventStatusType      EventStatus,
                                                             RBHSWDEM_DebugDataType_t debug0,
                                                             RBHSWDEM_DebugDataType_t debug1)
{
  Dem_ReportErrorStatusWithEnvData(EventId, EventStatus, (Dem_DebugDataType)debug0, (Dem_DebugDataType)debug1);
}

static inline void RBHSWESR_ReportElShutdownError(Dem_EventIdType     EventId,
                                                  Dem_EventStatusType EventStatus)
{
  Dem_ReportErrorStatus(EventId, EventStatus);
}

#endif
