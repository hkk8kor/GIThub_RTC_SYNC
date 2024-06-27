#include "RBSYS_Config.h"

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  #include "RBSYS_FlashConfigArea.h"

  extern uint32 ** TRBSYS_getListOfAddresses(void);
  extern uint32 TBRSYS_getConfiguredOpbtValue(RBSYS_FlashConfigAreaSetting_t opbt_id);

  extern const RBSYS_FlashConfigArea_ExpectedValues_t* TRBSYS_getListOfValidOpbt(void);
  extern uint32 TRBSYS_getListOfValidOpbtSize(void);

#endif

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  extern uint32* TRBSYS_GetFlashConfigurationArea(void);
  extern void TRbsys_dummyfunction_fixcoveragereport(void);
#endif