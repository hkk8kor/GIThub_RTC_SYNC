#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"

#include "RBSYS_ClockSettings.h"

#if( RBFS_HSWSimulation == RBFS_HSWSimulation_ON )
  #include "SWStub_Config.h" ///< RBFS_SYSStubUseHwModels_Yes
  #if(RBFS_SYSStubUseHwModels == RBFS_SYSStubUseHwModels_Yes)
    #include "HwModels/Layouts/HwModel_SignalRouter.h"  ///< to forward the ECLK changes to current Layout
  #endif
#endif

void RBSYS_SetupECP(uint16 ECLK_KHZ_u16)
{
  #if( RBFS_SYSStubUseHwModels == RBFS_SYSStubUseHwModels_Yes )
  // just killed in HSWSim, since there is no microcontroller model.
  SigRoute_SetECLK(ECLK_KHZ_u16*1000);
  #endif
}