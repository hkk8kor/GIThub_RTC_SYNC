/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief This module is responsible to set and lock the guards (particularly important in the context of HSM-environments!).
 *
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* realized interfaces */
#include "RBSYS_GuardConfigCommon.h"
#include "RBSYS_GuardMemoryMap.h"
#include "RBSYS_RestrictedSPID.h"
#include "RBSYS_Subsystem.h"


/* used interfaces */
#include "RBSYS_uCRegisters.h"
#include "RBSYS_CpuInfo.h"
#include "RB_MemoryBarrier.h"

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
  #include "Monitorings/RBSYS_ErrorHooks.h"
#endif



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysExclusiveSPID,
                          RBFS_SysExclusiveSPID_Used,
                          RBFS_SysExclusiveSPID_NotUsed);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHSMsharedGRAM,
                          RBFS_SysHSMsharedGRAM_Host,
                          RBFS_SysHSMsharedGRAM_Restricted);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RestrictedExclusiveGRAMsize,
                          RBFS_RestrictedExclusiveGRAMsize_0K,
                          RBFS_RestrictedExclusiveGRAMsize_16K,
                          RBFS_RestrictedExclusiveGRAMsize_32K,
                          RBFS_RestrictedExclusiveGRAMsize_64K,
                          RBFS_RestrictedExclusiveGRAMsize_128K,
                          RBFS_RestrictedExclusiveGRAMsize_256K);

RB_ASSERT_SWITCH_SETTINGS(RBFS_BootblockEnableAsicSupport,
                          RBFS_BootblockEnableAsicSupport_ON,
                          RBFS_BootblockEnableAsicSupport_OFF);


#if( (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION) || (RBFS_BootblockEnableAsicSupport == RBFS_BootblockEnableAsicSupport_ON) )
  void RBSYS_EnhancedGuardInit(void)
  {
    #if( (RBFS_HexBlockBuild == RBFS_HexBlockBuild_BOOTLOADER) || (RBFS_HexBlockBuild == RBFS_HexBlockBuild_RBBOOTLOADER) )

      RB_ASSERT_SWITCH_SETTINGS(RBFS_RBSYSGlobalRAMGuardsBB,
                                RBFS_RBSYSGlobalRAMGuardsBB_ON,
                                RBFS_RBSYSGlobalRAMGuardsBB_OFF);

      #if( RBFS_RBSYSGlobalRAMGuardsBB == RBFS_RBSYSGlobalRAMGuardsBB_ON )
        /// BMGR is setting up the GRAM Guards according to its settings
        /// OEMBLDR / RBBLDR have to overwrite these settings according to their settings 
        RBSYS_GRAMGuardInit();
      #endif
    #endif

      if( RBSYS_getCoreID() == RBSYS_CORE_ID_0 )
      {
        RB_FullHardwareMemoryBarrier();     // ensure that all data accesses are finished before (re-)configuration

        // Peripheral guards are programmed only by master core (see calling location)
        #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
          RBSYS_PBUSGuardInit();          //< U2A: Once PBUS Guards are fully initialized, Other guards can be initialized without interference of unsafe busmasters
          RBSYS_HBusGuardInit();
          #if(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
            /** Hint: This is covered by PBus Guards on P1x */
            RBSYS_IBusGuardInit();
            RBSYS_INTCGuardInit();
            RBSYS_DMAGuardInit();
          #endif
        #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
          /* On Stellar, all cross-module accesses are routed via the FlexNOC, therefore enable all Guards at once */
          RBSYS_PeripheralGuardsInit();
        #else
          #error("Unsupported RBFS_uCFamily")
        #endif

        RB_FullHardwareMemoryBarrier();    // wait for completion of all data transfers to peripheral registers, which ensures completion of whole System MPU (re-)configuration
      }
  }
#endif


#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
  /**
  * @brief Set and Lock all PBUS and HBUS guard registers to the specified values (agreed with GUAM development)
  *
  * @param void
  *
  * @return void
  */
  static void RBSYS_SetAndLockPeripheralGuardRegisters(void)
  {
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    RBSYS_PeripheralGuardInit();
    // toDo:  check which parts of the PBG Initialization can be moved to PBus-guard init
    /*< must be located late in startup, because GUAM needs access during init (agreement with Escrypt) */

  #elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
    /** PBUS Guards are all intialized by RBSYS_EnhancedGuardInit */
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    /** NOC Memory Protections are all initialized by RBSYS_GRAMGuardInit and RBSYS_EnhancedGuardInit */
  #else
    assert(0); // not yet supported for this uCFamily
  #endif
  }

  #if( RBFS_SysExclusiveSPID == RBFS_SysExclusiveSPID_Used )
    /// @brief Enables all GRAM guards which are configured to use Exclusive SPID instead of SAFE SPID
    static inline void RBSYS_ExclusiveSPID_EnableGRAMGuards(void)
    {
      #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
        RBSYS_RestrictedExclusiveGRAM_BlockSafeAccess();
      #endif

      #if( RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted )
        RBSYS_RestrictedHSMSharedGRAM_BlockSafeAccess();
      #endif
    }

    #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      #warning("ExclusiveSPID feature is not yet supported for Stellar")
    #endif
  #endif




  /**
  * @brief This function must be called at the end of init task after SPG_CUBAS_Communication_Init (which contains PRC_RBSEC_Init via SPG_RBSEC_SecCommunication_Init).
  *
  * ATTENTION: This function must be called on all Cores!
  *
  * @return void
  */
  void RBSYS_PRC_FSW_FinalGuard_Init(void)
  {
    // GRAM and peripheral guards are programmed only by master core
    if (RBSYS_getCoreID() == RBSYS_CORE_ID_0)
    {
      /* Restricted Exclusive RAM was open for SAFE SPID up to now, to allow variable initialization */
      #if( RBFS_SysExclusiveSPID == RBFS_SysExclusiveSPID_Used )
        RBSYS_ExclusiveSPID_EnableGRAMGuards();
        #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
          #warning("Exclusive SPID feature is not supported for Stellar (yet)")
        #endif
      #endif
      #if(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
        RBSYS_GRAMGuardLock(); //< todo: do not lock GRAM Guards as clarified with Safety Team
      #endif
      RBSYS_SetAndLockPeripheralGuardRegisters();
    }
  }

  /**
  * @brief This function must be called after RBSYS_PRC_FSW_FinalGuard_Init.
  *
  * ATTENTION: This function must be called on all Cores!
  *
  * @return void
  */
  void RBSYS_PRC_FSW_VerifyFinalGuardSettings(void)
  {
    uint32 failedGuardConfigFlags = 0x0u;

    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      /* Has to be executed on both cores! */
      if( RBSYS_VerifyLRAMGuardSettings() == FALSE )
      {
        failedGuardConfigFlags |= (1u<<0);
      }

      /* Has to be executed on Core 0 only! */
      if (RBSYS_getCoreID() == RBSYS_CORE_ID_0)
      {
        // GRAM and peripheral guards are programmed only by master core and also only checked there
        if( RBSYS_VerifyGRAMGuardSettings() == FALSE )
        {
          failedGuardConfigFlags |= (1u<<1);
        }

        if( RBSYS_VerifyPeripheralGuardSettings() == FALSE ) /* contains PBus and HBus Guard settings */
        {
          failedGuardConfigFlags |= (1u<<2);
        }
      }
    #elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
      if( RBSYS_getCoreID() == RBSYS_CORE_ID_0 )
      {
        /* Concept for U2A:
        *  Assumption:
        *    Guard settings can be overwritten by Unsafe Busmasters while access to the guards itself is not restricted.
        *  U2A-Guard-Implementation:
        *    - PBUS-Guards are guarding itself and all other Guards ("Guard of Guards").
        *    - Other Guards cannot be locked individually (except CSG)
        *
        *  Implementation concept:
        *    - PBUS-Guards are initialized before initializing other guards
        *      => other Guards can be set correctly because only SAFE BusMaster is able to access them.
        *    - As long as we can prove that PBGs are set correctly, all other Guards must have been set correctly.
        *
        *  Special Implementation:
        *    - PE-Guards have to be checked separately because PBG is not yet set when initializing PEG
        *    - CRAM-CSGuards have to be checked separately because CSG could have been locked separately by Unsafe Busmasters
        */
        if( RBSYS_VerifyFinalPBUSGuardSettings() == FALSE )
        {
          failedGuardConfigFlags |= (0x1u<<0);
        }

        /* SPID Setting is given but can be prevented by setting SPID Masks. These Masks can be locked and therefore have to be verified */
        /* CSG Setting has to be checked additionally because CSGs can be locked by a Lock-Bit (see R01UH0820EJ0100 Rev.1.00 p.6071) */
        /* PE Guard Setting: Only 2 channels are used. All other channels shall be unused. */
        if( RBSYS_VerifyFinalSPIDandPEGandCSGGuardSettings() == FALSE )
        {
          failedGuardConfigFlags |= (0x1u<<1);
        }

        #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
          /* HBG Setting has to be checked additionally because HBGs can be locked by a Lock-Bit (see R01UH0820EJ0100 Rev.1.00 p.6178) */
          if( RBSYS_VerifyFinalHBUSGuardSettings() == FALSE )
          {
            failedGuardConfigFlags |= (0x1u<<2);
          }
        #else
          #warning("HBGs are not implemented for U2C in VLAB yet.")
        #endif

        if( failedGuardConfigFlags != 0 )
        {
          RBSYS_setSYSErrorHook(RBSYS_Error_GuardConfigurationFailed, failedGuardConfigFlags);
        }
      }
    #else
      assert(0); //< todo: Unicon support
    #endif

    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      /* P1x: Both Cores are checking their own LRAM Guard Settings -> therefore, both Cores have to call following function
      * U2A: Core 0 is checking all Guard settings -> nevertheless, both Cores will call following function */
      if( failedGuardConfigFlags != 0 )
      {
        RBSYS_setSYSErrorHook(RBSYS_Error_GuardConfigurationFailed, failedGuardConfigFlags | (RBSYS_getCoreID()<<24));
      }
    #else
      #warning("Memory Protection Verification concept for Stellar is not yet implemented.")
    #endif
  }
#endif


#if( RBFS_SysExclusiveSPID == RBFS_SysExclusiveSPID_Used )

  void RBSYS_setCoreSPID2RestrictedSPID(void)
  {
    /* check that this interface is called from Safe SPID */
    /* - because changing the core SPID takes quite some time, it should not be done repeatedly/unnecessarily. */
    /*   Therfore one should have a clean handling concept for doing this with clear start and exit points!    */
    /*   To assist in having such a clean handling this assert was introduced.                                 */
    assert(RBSYS_getCoreSPID() == SafeSPID);

    RB_FullHardwareMemoryBarrier();       // ensure that all data accesses are finished before (re-)configuration

    RBSYS_setCoreSPID(RestrictedSPID);    // set SPID on current core

    RB_FullHardwareMemoryBarrier();       // wait for completion of all data transfers to peripheral registers, which ensures completion of whole guard (re-)configuration
  }


  void RBSYS_resetCoreSPID2SafeSPID(void)
  {
    /* check that this interface is called from Restricted SPID */
    /* - because changing the core SPID takes quite some time, it should not be done repeatedly/unnecessarily. */
    /*   Therfore one should have a clean handling concept for doing this with clear start and exit points!    */
    /*   To assist in having such a clean handling this assert was introduced.                                 */
    assert(RBSYS_getCoreSPID() == RestrictedSPID);

    RB_FullHardwareMemoryBarrier();    // ensure that all data accesses are finished before (re-)configuration

    RBSYS_setCoreSPID(SafeSPID);       // set SPID on current core

    RB_FullHardwareMemoryBarrier();    // wait for completion of all data transfers to peripheral registers, which ensures completion of whole guard (re-)configuration
  }

#endif



/** @} */
/* End ingroup RBSYS */
