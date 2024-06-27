#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"

#include "RBSYS_SystemTimer.h"
#include "TRBSYS_SystemTimer.h"
#include "TRBSYS_Intrinsics.h"
#include "RBSYS_CpuInfo.h"
#include "TRBSYS_CpuInfo.h"


void TRBSYS_setSynctimeTickCtr(uint32 nValue)
{
  RBSYS_SystemTimerSynctimeCnt = nValue;
}

void TRBSYS_setRealtimeTickCtr(uint32 nValue)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    RBSYS_SystemTimerRealtimeCnt = nValue;
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    uint32 core_id_initial = RBSYS_getCoreID();

    /* All Cores have different RealTime Counters which are all supplied by the same time bus. Therefore, all counters
     * have to be adapted */
    uint32 core_id_iter;
    for( core_id_iter = 0; core_id_iter < RB_NUM_CORES; core_id_iter++ )
    {
      TRBSYS_setCoreID(core_id_iter);
      TRBSYS_SetSystemRegister64(15, 0, nValue, 14);
    }

    TRBSYS_setCoreID(core_id_initial);
  #endif
}


void TRBSYS_SetTimeInUsec(uint32 value)
{
  TRBSYS_setRealtimeTickCtr( value * RBSYS_TIMERTICKS_PER_US );
}

uint32 TRBSYS_GetTimeInUsec(void)
{
  return RBSYS_SystemTimerRealtimeCnt * RBSYS_TIMERTICKS_PER_US;
}

void TRBSYS_RealtimeTickCtrAddTicks(uint32 value)
{
  TRBSYS_setRealtimeTickCtr(RBSYS_SystemTimerRealtimeCnt + value);
}