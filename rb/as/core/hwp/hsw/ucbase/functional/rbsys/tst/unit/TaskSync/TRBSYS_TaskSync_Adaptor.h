#ifndef TRBSYS_TASKSYNC_ADAPTOR_H__
#define TRBSYS_TASKSYNC_ADAPTOR_H__

#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/
#if (RBFS_TaskSync == RBFS_TaskSync_ON)
  extern int GetPrivate_RBSYS_SRMS_CYCLETIME_US(void);
  extern int GetPrivate_RBSYS_SRMSMAXCORRECTION_TICKS(void);
  extern int GetPrivate_RBSYS_SRMSMAXCORRECTION_US(void);
  extern int GetPrivate_RBSYS_SRMS_ticks_to_adapt(void);
  extern int GetPrivate_RBSYS_SRMS_overall_adapted_ticks(void);
#endif

/********************************************************/
/*                Set private variables                 */
/********************************************************/


/********************************************************/
/*              Access private Functions                */
/********************************************************/


#endif