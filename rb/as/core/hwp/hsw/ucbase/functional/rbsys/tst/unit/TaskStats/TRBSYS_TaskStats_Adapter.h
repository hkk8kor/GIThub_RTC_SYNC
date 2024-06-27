#ifndef TRBSYS_TASKSTATS_ADAPTOR_H__
#define TRBSYS_TASKSTATS_ADAPTOR_H__

#include "csw/RBSYS_TaskInfo.h"       // ensure include of original RBSYS header instead of CoreStub

#include "TRBSYS_Os.h"
#include "Statistics/RBSYS_TaskStats.h"
#include "RBSYS_OSServices.h"




/********************************************************/
/*                Get private variables                 */
/********************************************************/
int GetPrivate_RBSYS_TASKSTAT_TASKSIZE(void);
int GetPrivate_RBSYS_TASKSTAT_ISRSIZE(void);

TaskType GetPrivate_RBSYS_taskstatsTasks_task(int index);
RBSYS_taskstats_ids_t GetPrivate_RBSYS_taskstatsTasks_id(int index);

ISRType GetPrivate_RBSYS_taskstatsIsrs_isr(int index);
RBSYS_taskstats_ids_t GetPrivate_RBSYS_taskstatsIsrs_id(int index);


/********************************************************/
/*                Set private variables                 */
/********************************************************/

/********************************************************/
/*              Access private Functions                */
/********************************************************/


#endif