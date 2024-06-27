// rename RBSYS main function to avoid issue with existing main function from test environment
#define main main2

// define FSWStart which would have been defined in RBSYS_FSWStartVect.850
#include "Platform_Types.h"
const uint32 FSWStart = 0;

// suppress warning about unsupported pragma for GCC
#include "RBSYS_GHS_ProgramStartup.h"
#undef RBSYS_ATTR_NO_PROLOGUE
#define RBSYS_ATTR_NO_PROLOGUE

#include "RBSYS_FSWStartup.c"



#include "TRBSYS_FSWStartup_Adaptor.h"
#include "RBSYS_Config.h"

uint32 TRBBOOTBLOCKHSW_BaseOsRequest;


/********************************************************/
/*                Get private variables                 */
/********************************************************/


/********************************************************/
/*                Set private variables                 */
/********************************************************/


/********************************************************/
/*              Access private Functions                */
/********************************************************/
void CallPrivate_RBSYS_StartupPreOSPhase0(void)
{
  RBSYS_StartupPreOSPhase0();
}

void CallPrivate_main(void)
{
  int argc = 1;
  char *argv[2];
  char *envp[2];

  main(argc, argv, envp);
}

void CallPrivate_RBSYS_PRC_ClearColdStartResetFlags(void)
{
    RBSYS_PRC_ClearColdStartResetFlags();
}

void CallPrivate_startup_prc_calls(const PRC_PTR proc_table[])
{
  startup_prc_calls(proc_table);
}

uint32 CallPrivate_RBSYS_getResetFlags4MM6(void)
{
    return RBSYS_resetFlags4MM6;
}