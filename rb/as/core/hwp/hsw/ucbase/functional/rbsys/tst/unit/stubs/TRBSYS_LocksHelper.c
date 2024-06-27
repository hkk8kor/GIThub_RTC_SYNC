
#include "RBSYS_Config.h"

#include "TRBSYS_LocksHelper.h"
#include "RBSYS_LocksImpl.h"

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
  #include "RBSYS_LocksImplIntern.h"

  TRBSYS_LockCounter_t TRBSYS_CoreLocalLock = {0, 0};
  TRBSYS_LockCounter_t TRBSYS_CoreLocalLock_Core1 = {0, 0};
  TRBSYS_LockCounter_t TRBSYS_GlobLock = {0, 0};
  
  static RBSYS_coreintlock_t TRBSYS_CoreLocalLockCore0 = {0};
  static RBSYS_coreintlock_t TRBSYS_CoreLocalLockCore1 = {0};
  lockstr_t RBSYS_common_lock = {0};
  
  
  
  RBSYS_coreintlock_t* const RBSYS_coreintlockinfo[RB_NUM_CORES] = {
                                                  &TRBSYS_CoreLocalLockCore0
                                              #if (RBFS_MCORE == RBFS_MCORE_ON)
                                                , &TRBSYS_CoreLocalLockCore1
                                              #endif
                                                };
  
  
  
  void RBSYS_EnterCorelocalIntlock_intern(void)
  {
    TRBSYS_CoreLocalLock.fnc_call_cnt++;
    TRBSYS_CoreLocalLock.nest_cnt++;
  }
  
  void RBSYS_ExitCorelocalIntlock_intern(void)
  {
    TRBSYS_CoreLocalLock.nest_cnt--;
  }
  
  void RBSYS_EnterCommonLock_intern(void)
  {
    TRBSYS_GlobLock.fnc_call_cnt++;
    TRBSYS_GlobLock.nest_cnt++;
  }
  
  void RBSYS_ExitCommonLock_intern(void)
  {
    TRBSYS_GlobLock.nest_cnt--;
  }

#endif
