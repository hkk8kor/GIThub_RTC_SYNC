#ifndef TRBSYS_BOOTBLOCK_STARTUP_ADAPTOR_H__
#define TRBSYS_BOOTBLOCK_STARTUP_ADAPTOR_H__

#include "SwTest_Global.h"                      // for SWT functionality
#include "RBSYS_Config.h"


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
  extern void CallPrivate_main(void);
#endif


#endif