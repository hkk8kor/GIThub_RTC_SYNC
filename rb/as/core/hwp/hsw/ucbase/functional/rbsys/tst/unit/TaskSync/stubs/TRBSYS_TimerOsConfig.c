#include "RBSYS_Config.h"

#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_TimerOsConfig.h"

#if (RBFS_TaskSync == RBFS_TaskSync_ON)

  #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    #include "RBSYS_SystemTimer.h"

    static uint32 TRBSYS_SynctimeAdaptedTicks = 0;
    uint32 RBSYS_GetSynctimeAdaptedTicks(void)
    {
      return TRBSYS_SynctimeAdaptedTicks;
    }
  #endif

  sint32 RBSYS_STMControlTicks(sint32 delta_ticks)
  {
    #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      TRBSYS_SynctimeAdaptedTicks += delta_ticks;
    #endif
    return delta_ticks;
  }
#endif

