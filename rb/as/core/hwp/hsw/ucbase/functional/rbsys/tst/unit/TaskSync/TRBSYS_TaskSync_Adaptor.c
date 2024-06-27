#include "RBSYS_TaskSync.c"



#include "TRBSYS_TaskSync_Adaptor.h"
#include "RBSYS_Config.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/
#if (RBFS_TaskSync == RBFS_TaskSync_ON)

  int GetPrivate_RBSYS_SRMS_CYCLETIME_US(void)
  {
    return RBSYS_SRMS_CYCLETIME_US;
  }

  int GetPrivate_RBSYS_SRMSMAXCORRECTION_TICKS(void)
  {
    return RBSYS_SRMSMAXCORRECTION_TICKS;
  }

  int GetPrivate_RBSYS_SRMSMAXCORRECTION_US(void)
  {
    return RBSYS_SRMSMAXCORRECTION_US;
  }

  int GetPrivate_RBSYS_SRMS_ticks_to_adapt(void)
  {
    return RBSYS_SRMS_ticks_to_adapt;
  }

  int GetPrivate_RBSYS_SRMS_overall_adapted_ticks(void)
  {
    return RBSYS_SRMS_overall_adapted_ticks;
  }

#endif

/********************************************************/
/*                Set private variables                 */
/********************************************************/


/********************************************************/
/*              Access private Functions                */
/********************************************************/
