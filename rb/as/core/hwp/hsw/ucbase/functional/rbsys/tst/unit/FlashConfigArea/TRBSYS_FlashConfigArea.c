#include "SwTest_Global.h"                      // for SWT functionality
#include "RBSYS_Config.h"                       ///< for RBFS_uCFamily_RenesasP1x
#include "TRBSYS_FlashConfigArea_Adaptor.h"

#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
  #include "RBSYS_FlashConfigArea.h"

  /**
  * \Reference
  *  RBSYS_FlashConfigArea_GetCurrentValue,
  *  RBSYS_FlashConfigArea_GetValidValues,
  *  RBSYS_FlashConfigArea_GetValidValuesSize,
  *  Gen_SWCS_HSW_uC_Base_SYS-231
  *
  * \Purpose
  * Check that getter functions return the correct values
  *
  * \Sequence
  * Set Values of Option Bytes
  * Call getter function for all Option Bytes
  * Call gett functions for valid values list
  *
  * \ExpectedResult
  * The getter functions return the correct value
  */
  SWTEST void TRBSYS_FlashConfigArea_Getter(void)
  {
    uint32 i;
    uint32 ** TRBSYS_ListOfAddresses = TRBSYS_getListOfAddresses();

    for(i = 0; i < (uint32)RBSYS_FlashConfigAreaSetting_MaxNumberOfSettings; i++)
    {
      *TRBSYS_ListOfAddresses[i] = 0x11111111 * i;
      SWT_EvalEq(RBSYS_FlashConfigArea_GetCurrentValue((RBSYS_FlashConfigAreaSetting_t) i), 0x11111111 * i);
    }

    SWT_EvalEq((uint32)RBSYS_FlashConfigArea_GetValidValues(), (uint32)TRBSYS_getListOfValidOpbt());
    SWT_EvalEq(RBSYS_FlashConfigArea_GetValidValuesSize(), TRBSYS_getListOfValidOpbtSize());
  }

  /**
  * \Reference
  *  RBSYS_FlashConfigArea_GetValidValues,
  *  RBSYS_FlashConfigArea_GetValidValuesSize,
  *  Gen_SWCS_HSW_uC_Base_SYS-231
  *
  * \Purpose
  * Check that currently configured option byte values are also in valid option byte values list
  *
  * \Sequence
  * Get list of valid option byte values and list of configured option byte values
  * Look for configured option byte values in valid option byte values list
  *
  * \ExpectedResult
  * Every configured option byte value is also in valid option byte value list
  */
  SWTEST void TRBSYS_FlashConfigArea_ConfiguredValuesInValidList(void)
  {
    const RBSYS_FlashConfigAreaSetting_t settingsToTest[] = {
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        RBSYS_FlashConfigAreaSetting_ResetVector,
        RBSYS_FlashConfigAreaSetting_OPBT1,
        RBSYS_FlashConfigAreaSetting_OPBT14,
        RBSYS_FlashConfigAreaSetting_OPBT15,
      #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        RBSYS_FlashConfigAreaSetting_ResetVectorPE0,
        RBSYS_FlashConfigAreaSetting_ResetVectorPE1,
        RBSYS_FlashConfigAreaSetting_ResetVectorPE2,
        RBSYS_FlashConfigAreaSetting_ResetVectorPE3,
        RBSYS_FlashConfigAreaSetting_OPBT0,
        RBSYS_FlashConfigAreaSetting_OPBT1,
        RBSYS_FlashConfigAreaSetting_OPBT2,
        RBSYS_FlashConfigAreaSetting_OPBT3,
        RBSYS_FlashConfigAreaSetting_OPBT4,
        RBSYS_FlashConfigAreaSetting_OPBT6,
        RBSYS_FlashConfigAreaSetting_OPBT7,
        RBSYS_FlashConfigAreaSetting_OPBT8,
        RBSYS_FlashConfigAreaSetting_OPBT9,
        RBSYS_FlashConfigAreaSetting_OPBT10,
        RBSYS_FlashConfigAreaSetting_OPBT10,
        RBSYS_FlashConfigAreaSetting_OPBT11,
        RBSYS_FlashConfigAreaSetting_OPBT12,
        RBSYS_FlashConfigAreaSetting_OPBT13,
        RBSYS_FlashConfigAreaSetting_OPBT14,
        RBSYS_FlashConfigAreaSetting_OPBT16,
        RBSYS_FlashConfigAreaSetting_OPBT17,
        RBSYS_FlashConfigAreaSetting_OPBT18,
        RBSYS_FlashConfigAreaSetting_OPBT19,
        RBSYS_FlashConfigAreaSetting_OPBT20,
        RBSYS_FlashConfigAreaSetting_OPBT21,
        RBSYS_FlashConfigAreaSetting_OPBT22,
        RBSYS_FlashConfigAreaSetting_OPBT23,
      #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
        RBSYS_FlashConfigAreaSetting_ResetVectorPE0,
        RBSYS_FlashConfigAreaSetting_ResetVectorPE1,
        RBSYS_FlashConfigAreaSetting_ResetVectorPE2,
        RBSYS_FlashConfigAreaSetting_ResetVectorPE3,
        RBSYS_FlashConfigAreaSetting_OPBT0,
        RBSYS_FlashConfigAreaSetting_OPBT1,
        RBSYS_FlashConfigAreaSetting_OPBT2,
        RBSYS_FlashConfigAreaSetting_OPBT3,
        RBSYS_FlashConfigAreaSetting_OPBT4,
        RBSYS_FlashConfigAreaSetting_OPBT6,
        RBSYS_FlashConfigAreaSetting_OPBT7,
        RBSYS_FlashConfigAreaSetting_OPBT8,
        RBSYS_FlashConfigAreaSetting_OPBT9,
        RBSYS_FlashConfigAreaSetting_OPBT10,
        RBSYS_FlashConfigAreaSetting_OPBT10,
        RBSYS_FlashConfigAreaSetting_OPBT11,
        RBSYS_FlashConfigAreaSetting_OPBT12,
        RBSYS_FlashConfigAreaSetting_OPBT13,
        RBSYS_FlashConfigAreaSetting_OPBT14,
        RBSYS_FlashConfigAreaSetting_OPBT16,
        RBSYS_FlashConfigAreaSetting_OPBT17,
        RBSYS_FlashConfigAreaSetting_OPBT18,
        RBSYS_FlashConfigAreaSetting_OPBT19,
        RBSYS_FlashConfigAreaSetting_OPBT20,
        RBSYS_FlashConfigAreaSetting_OPBT21,
        RBSYS_FlashConfigAreaSetting_OPBT22,
        RBSYS_FlashConfigAreaSetting_OPBT23,
      #endif
    };
    uint32 i,j;
    const RBSYS_FlashConfigArea_ExpectedValues_t* validOpbtValues = RBSYS_FlashConfigArea_GetValidValues();
    uint32 validOpbtValuesSize = RBSYS_FlashConfigArea_GetValidValuesSize();

    for(i = 0; i < sizeof(settingsToTest)/sizeof(settingsToTest[0]); i++)
    {
      uint32 configuredOpbtValue = TBRSYS_getConfiguredOpbtValue(settingsToTest[i]);
      boolean result = FALSE;
      for(j = 0; j < validOpbtValuesSize; j++)
      {
        if((settingsToTest[i] == validOpbtValues[j].type) && (configuredOpbtValue == validOpbtValues[j].value))
        {
          result = TRUE;
          break;
        }
      }
      SWT_Eval(result);
    }
  }
#endif

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))

  /**
   * \Reference
   *  Gen_SWCS_HSW_uC_Base_SYS-325
   *
   * \Purpose
   * Check that Map Mode is set correctly in Flash Option Bytes according to RBFS_CodeFlashMemoryMode
   *
   * \Sequence
   *
   * \ExpectedResult
   * RBFS_CodeFlashMemoryMode_DoubleMap: MAPMODE in OPBT12 is set to double map mode
   * RBFS_CodeFlashMemoryMode_SingleMap: MAPMODE in OPBT12 is set to single map mode
   */
  SWTEST void TRBSYS_FlashConfigArea_PremiumFOTA(void)
  {
    #if( RBFS_CodeFlashMemoryMode == RBFS_CodeFlashMemoryMode_DoubleMap )
      SWT_EvalEq(TBRSYS_getConfiguredOpbtValue(RBSYS_FlashConfigAreaSetting_OPBT12) & 0x3u, 0x0u);
    #elif( RBFS_CodeFlashMemoryMode == RBFS_CodeFlashMemoryMode_SingleMap )
      SWT_EvalEq(TBRSYS_getConfiguredOpbtValue(RBSYS_FlashConfigAreaSetting_OPBT12) & 0x3u, 0x1u);
    #endif
  }

#endif

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  #include "RBSYS_FSWStartup.h"

  const uint32 FSWStart = 0x13371337u;


  /**
   * \Reference
   *
   * \Purpose
   * Check value of Reset Vector related DCF Options
   *
   * \Sequence
   *
   * \ExpectedResult
   */
  SWTEST void TRBSYS_FlashConfigArea_ResetVectorValid(void)
  {
    uint32* DCFArea = TRBSYS_GetFlashConfigurationArea();

    DCFArea = (uint32*)((uint32)DCFArea + 0x7E00);

    SWT_EvalEq(DCFArea[1], (uint32)&FSWStart);    // BootVector Core 0: 0x7E04
    SWT_EvalEq(DCFArea[3], (uint32)0xFFFFFFFFu);  // BootVector Core 1: invalid (0xFFFFFFFFu), will be set once starting the Core
    SWT_EvalEq(DCFArea[5], (uint32)0xFFFFFFFFu);  // BootVector Core 2: invalid (0xFFFFFFFFu), will be set once starting the Core
    SWT_EvalEq(DCFArea[7], (uint32)0xFFFFFFFFu);  // BootVector Core 3: invalid (0xFFFFFFFFu), will be set once starting the Core
    SWT_EvalEq(DCFArea[9], (uint32)0xFFFFFFFFu);  // BootVector Core 4: invalid (0xFFFFFFFFu), will be set once starting the Core
    SWT_EvalEq(DCFArea[11], (uint32)0xFFFFFFFFu); // BootVector Core 5: invalid (0xFFFFFFFFu), will be set once starting the Core

    TRbsys_dummyfunction_fixcoveragereport();
  }

#endif
