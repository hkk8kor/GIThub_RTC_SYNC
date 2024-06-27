// rename RBSYS main function to avoid issue with existing main function from test environment
#define main main2

// suppress warning about unsupported pragma for GCC
#include "RBSYS_GHS_ProgramStartup.h"
#undef RBSYS_ATTR_NO_PROLOGUE
#define RBSYS_ATTR_NO_PROLOGUE

// include RBSYS_Config.h for RBFS_uCFamily
#include "RBSYS_Config.h"
#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
  #include "RBSYS_Bootblock_Startup.c"



  #include "TRBSYS_Bootblock_Startup_Adaptor.h"
  /********************************************************/
  /*                Get private variables                 */
  /********************************************************/


  /********************************************************/
  /*                Set private variables                 */
  /********************************************************/


  /********************************************************/
  /*              Access private Functions                */
  /********************************************************/
  #if ((RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active) && (RBFS_BootblockSysStartupCode == RBFS_BootblockSysStartupCode_ON))
    void CallPrivate_main(void)
    {
      int argc = 1;
      char *argv[2];
      char *envp[2];

      main(argc, argv, envp);
    }
  #endif
#endif