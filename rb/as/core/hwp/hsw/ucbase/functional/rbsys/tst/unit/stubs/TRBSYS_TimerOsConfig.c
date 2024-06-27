#include "RBSYS_Config.h"

#if( RBFS_TaskSync == RBFS_TaskSync_ON )

  #include "RBSYS_SystemTimer.h"

  #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    static uint32 TRBSYS_SynctimeAdaptedTicks = 0;

    uint32 RBSYS_GetSynctimeAdaptedTicks(void)
    {
      return TRBSYS_SynctimeAdaptedTicks;
    }
  #endif

#endif