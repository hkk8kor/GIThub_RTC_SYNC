#include "RBSYS_Config.h"
#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  #include "FlashOptions/Renesas_P1x/RBSYS_FlashOptionBytes.c"
#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  #include "FlashOptions/Renesas_U2A/RBSYS_OPBT_U2a.c"
#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
  #include "FlashOptions/Renesas_U2C/RBSYS_OPBT_U2c.c"
#elif (RBFS_uCFamily == RBFS_uCFamily_STMStellar)
  #include "FlashOptions/STM_Stellar/RBSYS_FlashConfigArea_Stellar.c"
#endif



#include "TRBSYS_FlashConfigArea_Adaptor.h"
#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  uint32 TRBSYS_currentOpbtValues[RBSYS_FlashConfigAreaSetting_MaxNumberOfSettings] =
  {
    PE_RESET_VECTOR,
    RBSYS_OPBT0,
    RBSYS_OPBT1,
    RBSYS_OPBT14,
    RBSYS_OPBT15
  };
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  uint32 TRBSYS_currentOpbtValues[RBSYS_FlashConfigAreaSetting_MaxNumberOfSettings] =
  {
    RESET_VECTOR_PE0,
    RESET_VECTOR_PE1,
    RESET_VECTOR_PE2,
    RESET_VECTOR_PE3,
    OPBT0,
    OPBT1,
    OPBT2,
    OPBT3,
    OPBT4,
    OPBT6,
    OPBT7,
    OPBT8,
    OPBT9,
    OPBT10,
    OPBT11,
    OPBT12,
    OPBT13,
    OPBT14,
    OPBT16,
    OPBT17,
    OPBT18,
    OPBT19,
    OPBT20,
    OPBT21,
    OPBT22,
    OPBT23
  };
#endif

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  uint32 ** TRBSYS_getListOfAddresses(void)
  {
    return (uint32 **)RBSYS_OPBT_Addresses;
  }

  const RBSYS_FlashConfigArea_ExpectedValues_t* TRBSYS_getListOfValidOpbt(void)
  {
    return &RBSYS_OPBT_ExpectedValues[0];
  }

  uint32 TRBSYS_getListOfValidOpbtSize(void)
  {
    return RBSYS_OPBT_EXPECTEDVALUES_SIZE;
  }

  uint32 TBRSYS_getConfiguredOpbtValue(RBSYS_FlashConfigAreaSetting_t opbt_id)
  {
    return TRBSYS_currentOpbtValues[opbt_id];
  }
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  uint32* TRBSYS_GetFlashConfigurationArea(void)
  {
    return (uint32*)&RBSYS_DCFArea;
  }

  void TRbsys_dummyfunction_fixcoveragereport(void)
  {
    rbsys_dummyfunction_fixcoveragereport();
  }
#endif
