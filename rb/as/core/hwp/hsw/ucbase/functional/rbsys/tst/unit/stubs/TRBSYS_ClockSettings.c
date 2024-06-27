#include "RBSYS_Config.h"
#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_ClockSettings.h"
#include "RBSYS_ClockSettingsIntern.h"
#include "TRBSYS_ClockSettings.h"

#if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))
  uint32 TRBSYS_SetupClocks_RenesasP1x_cnt = 0;
  void RBSYS_SetupClocks_RenesasP1x(void)
  {
    TRBSYS_SetupClocks_RenesasP1x_cnt++;
  }
#endif

uint32 TRBSYS_SetupECP_cnt = 0;
uint32 TRBSYS_ECLK_KHZ = 0;
void RBSYS_SetupECP(uint16 nECLK)
{
  TRBSYS_ECLK_KHZ = nECLK;
  TRBSYS_SetupECP_cnt++;
}

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  void RBSYS_SetupPeripheralClocks(void){}
#endif