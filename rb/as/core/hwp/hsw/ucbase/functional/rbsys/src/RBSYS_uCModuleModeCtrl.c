/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief CC-CUBE peripheral startup handling
 *
 * On Renesas CC-CUBE devices some peripherals must be explicitly switched from standby mode to run mode during startup.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "Monitorings/RBSYS_ErrorHooks.h"
#include "RBSYS_SystemTimer.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_uCRegisters.h"


/* realized interfaces */
#include "RBSYS_uCModuleEnable.h"   //< external functionality
#include "RBSYS_uCModuleModeCtrl.h" //< internal functionality
#include "RBSYS_Subsystem.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                          RBFS_TargetDevice_RenesasD1,
                          RBFS_TargetDevice_RenesasD2,
                          RBFS_TargetDevice_RenesasD3,
                          RBFS_TargetDevice_RenesasD4,
                          RBFS_TargetDevice_RenesasD5,
                          RBFS_TargetDevice_RenesasD7,
                          RBFS_TargetDevice_RenesasM2,
                          RBFS_TargetDevice_RenesasM3,
                          RBFS_TargetDevice_RenesasM6,
                          RBFS_TargetDevice_RenesasK0,
                          RBFS_TargetDevice_RenesasK1,
                          RBFS_TargetDevice_STMP6);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HSWSimulation,
                          RBFS_HSWSimulation_ON,
                          RBFS_HSWSimulation_OFF);


#if( RBFS_HSWSimulation == RBFS_HSWSimulation_OFF )

  #include "RBSYS_TestInjection.h"

  /**
  * @brief Enable write access to "Module Standby Register"
  *
  * Enable access protection of Module Standby Registers on RH850/U2A via MSRKCPROT
  * (Module Standby Register Key Code Protection Register).
  *
  * @return void
  */
  static void RBSYS_EnableWriteAccessToModuleStandbyRegister(void)
  {
    #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      RBSYS_UnlockAccessToHwModule(&SYSCTRLMSRKCPROT);
    #endif
  }



  /**
  * @brief Disable write access to "Module Standby Register"
  *
  * Disable access protection of Module Standby Registers on RH850/U2A via MSRKCPROT
  * (Module Standby Register Key Code Protection Register).
  *
  * @return void
  */
  static void RBSYS_DisableWriteAccessToModuleStandbyRegister(void)
  {
    #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      RBSYS_LockAccessToHwModule(&SYSCTRLMSRKCPROT);
    #endif
  }



  /**
  * @brief Generic function to set a peripheral module to run mode
  *
  * RH850 devices must explicitly switch peripherals from standby mode to run mode before first usage.
  *
  * @param standbyRegister must be the address of the corresponding Module Standby Register
  * @param resetStatusRegister must be the address of the corresponding Software Limited Reset Status Register
  * @param bitmask of the corresponding Software Limited Reset Status Register
  *
  * @return void
  */
  static void RBSYS_SetPeripheralToRunMode(volatile uint32* standbyRegister, volatile const uint32* resetStatusRegister, uint32 bitmask)
  {
    if ((*resetStatusRegister & bitmask) == 0)
    {
      uint32 timestamp;
      uint32 timeout = 0;

      RBSYS_EnableWriteAccessToModuleStandbyRegister();

      *standbyRegister &= (~bitmask);                 /* enable clock supply for corresponding peripheral - will be set to run mode */

      RBSYS_DisableWriteAccessToModuleStandbyRegister();

      RBSYS_SchM_Enter_CoreLocalLock();     /* required to ensure that timeout monitoring is not interrupted */

      RBSYS_startUsecTimer(&timestamp);

      RBSYS_TEST_INJECTION_DelayRunMode();

      while (((*standbyRegister & bitmask) != 0) && (timeout == 0))
      {
        RBSYS_TEST_INJECTION_ProgressTime();
        timeout = RBSYS_isUsecTimerElapsed(&timestamp, 30);  /* timeout smaller than maximum allowed lock time */
        RBSYS_TEST_INJECTION_SetRunMode();
      }

      RBSYS_SchM_Exit_CoreLocalLock();

    #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)  // no failure handling in bootblock builds
      if (timeout != 0)
      {
        /* trigger directly failure entry to avoid follow up failures on peripheral driver ... */
        RBSYS_setSYSErrorHook(RBSYS_Error_PeripheralResetTimeOut, (uint32)standbyRegister);
      }
    #endif
    }
  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)  // no failure handling in bootblock builds
    else
    {
      /* it's forbidden to set peripheral to run mode while reset is being processed */
      RBSYS_setSYSErrorHook(RBSYS_Error_PeripheralReset, (uint32)standbyRegister);
    }
  #endif
  }
#else
  static void RBSYS_SetPeripheralToRunMode(volatile uint32* standbyRegister, volatile const uint32* resetStatusRegister, uint32 bitmask){}
#endif



void RBSYS_CAN_SetToRunMode(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    RBSYS_SetPeripheralToRunMode(&MSR_LM3, &SWLRESS3, 0x1u);
  #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_RSCFD, &SYSCTRLSWMRESS_RSCFD, 0x3u);
  #endif
}

void RBSYS_GTM_SetToRunMode(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    RBSYS_SetPeripheralToRunMode(&MSR_LM5, &SWLRESS5, 0x1u);
  #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_GTM, &SYSCTRLSWMRESS_GTM, 0x1u);
  #endif
}

void RBSYS_SENT_SetToRunMode(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    RBSYS_SetPeripheralToRunMode(&MSR_LM7, &SWLRESS7, 0x1u);
  #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_RSENT, &SYSCTRLSWMRESS_RSENT, 0xFFu);
  #endif
}

void RBSYS_SPI_SetToRunMode(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    RBSYS_SetPeripheralToRunMode(&MSR_LM10, &SWLRESS10, 0x1u);
  #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_MSPI, &SYSCTRLSWMRESS_MSPI, 0x3FFu);
  #endif
}

void RBSYS_RLIN3_SetToRunMode(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    RBSYS_SetPeripheralToRunMode(&MSR_LM11, &SWLRESS11, 0x1u);
  #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_RLIN3, &SYSCTRLSWMRESS_RLIN3, 0xFFFFFFu);
  #endif
}

void RBSYS_ADC_SetToRunMode(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    RBSYS_SetPeripheralToRunMode(&MSR_LM12, &SWLRESS12, 0x1u);
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_ADCJ_AWO, &SYSCTRLSWMRESS_ADCJ_AWO, 0x1u);
    RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_ADCJ_ISO, &SYSCTRLSWMRESS_ADCJ_ISO, 0x3u);
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
    RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_ADCK_AWO, &SYSCTRLSWMRESS_ADCK_AWO, 0x1u); 
    RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_ADCK_ISO, &SYSCTRLSWMRESS_ADCK_ISO, 0x3u);
  #endif
}


/* For Renesas devices D1 and D2, there are no module standby registers avalable */

#if((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2))
  void RBSYS_FlexRay_SetToRunMode(void)
  {
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      RBSYS_SetPeripheralToRunMode(&MSR_LM4, &SWLRESS4, 0x1u);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) 
      RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_FLXA, &SYSCTRLSWMRESS_FLXA, 0x3u);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_FLXA, &SYSCTRLSWMRESS_FLXA, 0x1u);
    #endif
  }

  void RBSYS_Ethernet_SetToRunMode(void)
  {
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      RBSYS_SetPeripheralToRunMode(&MSR_LM6, &SWLRESS6, 0x1u);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_ETNB, &SYSCTRLSWMRESS_ETNB, 0x3u);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_ETN, &SYSCTRLSWMRESS_ETN, 0x3u);
      RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_ETN_T1S, &SYSCTRLSWMRESS_ETN_T1S, 0x3u);
    #endif
  }
 
  #if((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
    void RBSYS_HSUSRT_SetToRunMode(void)
    {
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        RBSYS_SetPeripheralToRunMode(&MSR_LM8, &SWLRESS8, 0x1u);
      #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_RHSIF, &SYSCTRLSWMRESS_RHSIF, 0x1u);
      #endif
    }
  #endif

#endif

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  void RBSYS_TAUD0_SetToRunMode(void)
  {
    RBSYS_SetPeripheralToRunMode(&SYSCTRLMSR_TAUD, &SYSCTRLSWMRESS_TAUD, 0x1u);
  }
#endif

#if(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
  void RBSYS_PRC_ModeChangeAfterFCCUInit(void)
  {
    // Request mode change to DRUN
    RBSYS_ModeEntry_UpdateMode(RBSYS_ModeEntryModule_Peripheral);

    // Wait while mode transition is ongoing, until mode is reached
    RBSYS_ModeEntry_WaitForModeTransitionFinished(RBSYS_ModeEntryModule_Peripheral);
  }
#endif



/** @} */
/* End ingroup RBSYS */
