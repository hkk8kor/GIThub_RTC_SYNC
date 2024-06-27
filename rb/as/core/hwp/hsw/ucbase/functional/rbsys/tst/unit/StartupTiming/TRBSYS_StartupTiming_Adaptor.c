#include "RBSYS_StartupTiming.c"



#include "TRBSYS_StartupTiming_Adaptor.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/
uint32* GetPrivate_RBSYS_StartupTimestamp(void)
{
  return &RBSYS_StartupTimestamp[0];
}

uint32* GetPrivate_RBSYS_InitTaskTimestamp(void)
{
  return &RBSYS_InitTaskTimestamp[0];
}
/********************************************************/
/*                Set private variables                 */
/********************************************************/
/********************************************************/
/*              Access private Functions                */
/********************************************************/
