#ifndef TRBSYS_FSWSTARTUP_ADAPTOR_H__
#define TRBSYS_FSWSTARTUP_ADAPTOR_H__

#include "SwTest_Global.h"                      // for SWT functionality
#include "RBSYS_Config.h"


extern const uint32 FSWStart;


/********************************************************/
/*                Get private variables                 */
/********************************************************/


/********************************************************/
/*                Set private variables                 */
/********************************************************/


/********************************************************/
/*              Access private Functions                */
/********************************************************/
extern void CallPrivate_RBSYS_StartupPreOSPhase0(void);
extern void CallPrivate_main(void);
extern void CallPrivate_RBSYS_PRC_ClearColdStartResetFlags(void);
extern void CallPrivate_startup_prc_calls(const PRC_PTR proc_table[]);

extern uint32 CallPrivate_RBSYS_getResetFlags4MM6(void);

#endif
