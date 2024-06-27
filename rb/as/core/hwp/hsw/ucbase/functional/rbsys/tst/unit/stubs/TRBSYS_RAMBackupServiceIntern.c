#include "RBSYS_Config.h"
#include "RBSYS_RAMBackupServiceIntern.h"
#include "TRBSYS_RAMBackupServiceIntern.h"
#include "RBSYS_PlantStartupCtrl.h"

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
  uint32 TRBSYS_saveBaseOSRequestToBackupRAM_callCount = 0;
  void RBSYS_saveBaseOSRequestToBackupRAM(void)
  {
    TRBSYS_saveBaseOSRequestToBackupRAM_callCount++;
  }

  uint32 RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM_callcount = 0;
  void RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM(uint32 request)
  {
    RBMESG_DefineMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32) = request;
    RBMESG_SendMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);
    RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM_callcount++;
  }

  uint32 TRBSYS_ClearFSWBackupRAM_callCount = 0;
  void RBSYS_ClearFSWBackupRAM(void)
  {
    TRBSYS_ClearFSWBackupRAM_callCount++;
  }


  uint32 TRBSYS_restoreBaseOSRequestFromBackupRAM_cnt = 0;
  void RBSYS_restoreBaseOSRequestFromBackupRAM(void)
  {
    TRBSYS_restoreBaseOSRequestFromBackupRAM_cnt++;
  }

  uint32 TRBSYS_restoreSkipBootblockRequesterFromBackupRAM_cnt = 0;
  void RBSYS_restoreSkipBootblockRequesterFromBackupRAM(void)
  {
    TRBSYS_restoreSkipBootblockRequesterFromBackupRAM_cnt++;
  }

  void RBSYS_BackupRAM_FSW_UpdateResetFlagsForRBECM(uint32 dummy)
  {

  }
#endif