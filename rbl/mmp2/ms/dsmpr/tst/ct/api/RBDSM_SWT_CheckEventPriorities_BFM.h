#ifndef RBDSM_SWT_CHECKEVENTPRIORITIES_BFM_H_
#define RBDSM_SWT_CHECKEVENTPRIORITIES_BFM_H_

#include "Std_Types.h"

#if(RBFS_DSMSimulation == RBFS_DSMSimulation_ON)
void DSMSim_PriorityDisabled(Dem_EventIdType EventId1, Dem_EventIdType EventId2,Dem_EventIdType EventId3,Dem_EventIdType EventId4,Dem_EventIdType EventId5,Dem_EventIdType EventId6,Dem_EventIdType EventId7,Dem_EventIdType EventId8,Dem_EventIdType EventId9,Dem_EventIdType EventId10 );
void DSMSim_NodePriority(Dem_EventIdType EventId1, Dem_EventIdType EventId2,Dem_EventIdType EventId3,Dem_EventIdType EventId4 );
#endif

#endif /* RBDSM_SWT_CHECKEVENTPRIORITIES_BFM_H_ */
