#ifndef TRBSYS_RAMBACKUPSERVICEINTERN_H__
#define TRBSYS_RAMBACKUPSERVICEINTERN_H__

#include "SwTest_Global.h"
#include "RBSYS_Config.h"

extern uint32 TRBSYS_saveBaseOSRequestToBackupRAM_callCount;

extern void RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM(uint32 request);
extern uint32 RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM_callcount;

extern uint32 TRBSYS_ClearFSWBackupRAM_callCount;

extern uint32 TRBSYS_restoreBaseOSRequestFromBackupRAM_cnt;

extern uint32 TRBSYS_restoreSkipBootblockRequesterFromBackupRAM_cnt;


#endif /* End of multiple include protection */
