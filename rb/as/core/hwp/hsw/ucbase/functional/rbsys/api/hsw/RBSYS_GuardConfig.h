#ifndef RBSYS_GUARDCONFIG_H__
#define RBSYS_GUARDCONFIG_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Guard based access protection
 *
 * The RH850 platform incorporates the memory protection function to prevent erroneous accesses to data in memories and
 * peripheral registers.
 *
 * Therefore each memory is protected by decentralized slave guards:
 * - PEG (PE guard): The local RAM of a PE is protected against illegal accesses by other bus masters
 * - GRG (global RAM guard): The global RAM is protected against illegal accesses
 * - IPG (Internal Peripheral Guard): This is an old Renesas concept which is still available for backward compatibility reasons (not used)
 * - PBG, HBG (Peripheral Guard): The control registers in the peripheral circuits and memories are protected against illegal accesses
 *
 * Additionally each PE is equipped with a Memory Protection Unit (MPU), which will be used "only" for access protection of third party SW (TPSW).
 * So in general to ensure that different, untrusted bus masters does not interfere with the operation of trusted bus master, all shared resources
 * will be protected by above described guards.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_EmulationDevice,
                          RBFS_EmulationDevice_None,
                          RBFS_EmulationDevice_RenesasD3ED,
                          RBFS_EmulationDevice_RenesasD5ED,
                          RBFS_EmulationDevice_RenesasD7ED,
                          RBFS_EmulationDevice_RenesasM6ED,
                          RBFS_EmulationDevice_RenesasK3ED,
                          RBFS_EmulationDevice_STMP7ED);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HardwareSecurityModule,
                          RBFS_HardwareSecurityModule_Supported,
                          RBFS_HardwareSecurityModule_Unsupported);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TraceMeasurement,
                          RBFS_TraceMeasurement_RuntimeConfigurable,
                          RBFS_TraceMeasurement_uCdependent);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

/**
 * @brief SPID (system protection identifier)
 *
 * Renesas guard protection is done mainly by SPID.
 * Only the peripheral guards are checking additionally the PEID (processor element identifier).
 *
 * RH850 P1x-C bus masters:
 *  Debug Unit:   PEID=0
 *  PE1:          PEID=1       SPID=[2-31]   SPID=2 used
 *  PE2:          PEID=2       SPID=[2-31]   SPID=2 used
 *  DMA:          PEID=4       SPID=[2-31]
 *  ICUM:         PEID=5       SPID=[0-1]
 *  FlexRay0/1:   PEID=4       SPID=[2-31]   SPID=3 used
 *  Ether0/1:     PEID=4       SPID=[2-31]   SPID=3 used
 *
 *  DMA is redundant (REL CC CUBE) and therefore no guard restriction necessary
 *  DMA must write to LRAM in case of D1, D2 or D3 and GRAM in case of D3, D4 or D5.
 *
 * RH850 U2A bus masters (PEID feature was removed):
 *
 *  Debug Unit:   always allowed via special setting (see guard PROT register)
 *  PE1:          SPID=[0-31]   SPID=2 used
 *  PE2:          SPID=[0-31]   SPID=2 used
 *  PE3:          SPID=[0-31]   SPID=2 used
 *  PE4:          SPID=[0-31]   SPID=2 used
 *  DTS:          SPID=[0-31]   SPID=2 used
 *  sDMA:         SPID=[0-31]   SPID=3 used
 *  ICUM:         SPID=[0-31]   SPID=26 (SPID=25 for AES Engine)
 *  FlexRay0/1:   SPID=[0-31]   SPID=3 used
 *  Ether0/1:     SPID=[0-31]   SPID=3 used
 *  AUD:                        SPID=30 set @ trace POD
 *  MAU:                        SPID=31 set @ trace POD
 *
 * RH850 U2C bus masters:
 *
 *  Debug Unit:   always allowed via special setting (see guard PROT register)
 *  PE1:          SPID=[0-31]   SPID=0 used
 *  PE2:          SPID=[0-31]   SPID=0 used
 *  DTS:          SPID=[0-31]   SPID=0 used
 *  sDMA:         SPID=[0-31]   SPID=3 used
 *  ICUM:         SPID=[0-31]   SPID=26 (same for ICUM Core, AES Engine and DMA)
 *  FlexRay0:     SPID=[0-31]   SPID=3 used
 *  Ether0/1/T1S: SPID=[0-31]   SPID=3 used
 *  CANXL0/1:     SPID=[0-31]   SPID=3 used
 *  GTM0/1:       SPID=[0-31]   SPID=3 used
 *  ACEU:         SPID=[0-31]   SPID=3 used
 *  MAU:                        SPID=31 set by Option Byte
 *
 * STM Stellar bus masters:
 *
 *  Address space is protected by Firewalls allocated on every NOC (Network on Chip) Slave port.
 *  Bus Master have a fixed MasterID (MID).
 *
 *  Cluster0 (Core0, Core1)     MID=[0-3]
 *  Cluster1 (Core2, Core3)     MID=[4-7]
 *  Cluster2 (Core4)            MID=[8-11]
 *  DME                         MID=18
 *  DSP                         MID=22
 *  HSM                         MID=24
 *  DAP0                        MID=32
 *  DAP1                        MID=33
 *  Flexray0                    MID=34
 *  Flexray1                    MID=35
 *  ZipW0                       MID=36
 *  ZipW1                       MID=37
 *  SDMMC                       MID=39
 *  TMC                         MID=48
 *  Ether0                      MID=52
 *  Ether1                      MID=53
 *  eDMA0                       MID=56
 *  eDMA1                       MID=57
 *  eDMA2                       MID=58
 *  eDMA3                       MID=59
 *  PCIe0                       MID=60
 *  PCIe1                       MID=61
 *  GTM                         MID=62
 *  DFA                         MID=63
 *
 */
#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  typedef enum
  {
    SecureSPID0 = 0,           /**< reserved for ICU-M */
    SecureSPID1,               /**< reserved for ICU-M */
    SafeSPID,                  /**< safe bus masters (used for CPU0, CPU1 and DMA, which are all redundant */
    UnSafeSPID,                /**< unsafe bus masters (e.g. Flexray, Ethernet, ...) */
    RestrictedSPID             /**< special usecase if customer projects require a dedicated restricted RAM area */
  }RBSYSspid_t;
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  typedef enum
  {
    SafeSPID = 2,              /**< safe bus masters (used for CPU0, CPU1 and DTS, which are all redundant */
    UnSafeSPID = 3,            /**< unsafe bus masters (e.g. Flexray, Ethernet, ...) */
    RestrictedSPID = 4,        /**< special usecase if customer projects require a dedicated restricted RAM area */
    DmaUnsafeSPID = 5,         /**< separate SPID is needed for DMA because it is not lock-stepped for U2A (but DTS is)*/
    SecureSPID_AESEngine = 25, /**< reserved for ICU-M AES Engine */
    SecureSPID = 26            /**< reserved for ICU-M HA */
    #if( (RBFS_EmulationDevice != RBFS_EmulationDevice_None) || (RBFS_TraceMeasurement == RBFS_TraceMeasurement_RuntimeConfigurable) )
     ,AUDSPID = 30,   /**< SPID for AUD (can be used via XCP for measurement) must be set for U2A */
      MAUSPID = 31    /**< SPID for MAU (always used via XCP for measurement) must be set for U2A */
    #endif
  }RBSYSspid_t;
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  //todo: check whether this is still correct for U2C
  typedef enum
  {
    SafeSPID = 0,              /**< safe bus masters (used for CPU0, CPU1 and DTS, which are all redundant */
    UnSafeSPID = 3,            /**< unsafe bus masters (e.g. Flexray, Ethernet, ...) */
    RestrictedSPID = 4,        /**< special usecase if customer projects require a dedicated restricted RAM area */
    DmaUnsafeSPID = 5,         /**< separate SPID is needed for DMA because it is not lock-stepped for U2C (but DTS is)*/
    SecureSPID = 26            /**< reserved for ICUM HB Core, AES Engine, DMA */
    #if( (RBFS_EmulationDevice != RBFS_EmulationDevice_None) || (RBFS_TraceMeasurement == RBFS_TraceMeasurement_RuntimeConfigurable) )
      ,MAUSPID = 31            /**< SPID for MAU (always used via XCP for measurement) must be set for U2C */
    #endif
  }RBSYSspid_t;
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  typedef enum
  {
    RBSYS_NOCMasterID_Cluster0_Port0  = 0,  /* MasterID 0-3 */
    RBSYS_NOCMasterID_Cluster0_Port1  = 1,
    RBSYS_NOCMasterID_Cluster0_Port2  = 2,
    RBSYS_NOCMasterID_Cluster0_Port3  = 3,
    RBSYS_NOCMasterID_Cluster1_Port0  = 4,  /* MasterID 4-7 */
    RBSYS_NOCMasterID_Cluster1_Port1  = 5,
    RBSYS_NOCMasterID_Cluster1_Port2  = 6,
    RBSYS_NOCMasterID_Cluster1_Port3  = 7,
    RBSYS_NOCMasterID_Cluster2_Port0  = 8,  /* MasterID 8-11 */
    RBSYS_NOCMasterID_Cluster2_Port1  = 9,
    RBSYS_NOCMasterID_Cluster2_Port2  = 10,
    RBSYS_NOCMasterID_Cluster2_Port3  = 11,
    RBSYS_NOCMasterID_DME             = 18,
    RBSYS_NOCMasterID_DSPH            = 22,
    RBSYS_NOCMasterID_HSM             = 24,
    RBSYS_NOCMasterID_DAP0            = 32,
    RBSYS_NOCMasterID_DAP1            = 33,
    RBSYS_NOCMasterID_Flexray0        = 34,
    RBSYS_NOCMasterID_Flexray1        = 35,
    RBSYS_NOCMasterID_ZipW0           = 36,
    RBSYS_NOCMasterID_ZipW1           = 37,
    RBSYS_NOCMasterID_SDMMC           = 39,
    RBSYS_NOCMasterID_TMC             = 48,
    RBSYS_NOCMasterID_Ether0          = 52,
    RBSYS_NOCMasterID_Ether1          = 53,
    RBSYS_NOCMasterID_eDMA0           = 56,
    RBSYS_NOCMasterID_eDMA1           = 57,
    RBSYS_NOCMasterID_eDMA2           = 58,
    RBSYS_NOCMasterID_eDMA3           = 59,
    RBSYS_NOCMasterID_PCIe0           = 60,
    RBSYS_NOCMasterID_PCIe1           = 61,
    RBSYS_NOCMasterID_GTM             = 62,
    RBSYS_NOCMasterID_DFA             = 63
  } RBSYS_NOCMasterID_t;
#else
  #error ("Exception: Implementation for this uCFamily is missing")
#endif


#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )

  #define RBSYS_SPID_SAFE_MASK            ( 1u << SafeSPID )
  #define RBSYS_SPID_SECURE_MASK          ((1u << SecureSPID0) | (1u << SecureSPID1))
  #define RBSYS_SPID_UNSAFE_MASK          ( 1u << UnSafeSPID )
  #define RBSYS_SPID_RESTRICTED_MASK      ( 1u << RestrictedSPID )

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

  #if( (RBFS_EmulationDevice != RBFS_EmulationDevice_None) || (RBFS_TraceMeasurement == RBFS_TraceMeasurement_RuntimeConfigurable) )
    #define RBSYS_SPID_MAU_MASK             ( (uint32) 1u << MAUSPID )
    #define RBSYS_SPID_AUD_MASK             ( (uint32) 1u << AUDSPID )
  #else
    #define RBSYS_SPID_MAU_MASK             ( 0u )
    #define RBSYS_SPID_AUD_MASK             ( 0u )
  #endif

  /* Hint: For U2A, Access via AUD (Advanced User Debugger) and MAU (Memory Access Unit) has to be granted for XCP measurements */
  #define RBSYS_SPID_Measurement_MASK     (RBSYS_SPID_MAU_MASK | RBSYS_SPID_AUD_MASK)

  #define RBSYS_SPID_SAFE_MASK            (( 1u << SafeSPID) | RBSYS_SPID_Measurement_MASK)
  #if( RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Supported )
    #define RBSYS_SPID_SECURE_MASK          (( (uint32) 1u << SecureSPID) | ( (uint32) 1u << SecureSPID_AESEngine) | RBSYS_SPID_Measurement_MASK)
    #define RBSYS_SPID_SECURE_SPIDs         (( (uint32) 1u << SecureSPID) | ( (uint32) 1u << SecureSPID_AESEngine))
  #else
    #define RBSYS_SPID_SECURE_MASK          (RBSYS_SPID_Measurement_MASK)
    #define RBSYS_SPID_SECURE_SPIDs         (0u)
  #endif
  #define RBSYS_SPID_UNSAFE_MASK          (( 1u << UnSafeSPID)  | RBSYS_SPID_Measurement_MASK)
  #define RBSYS_SPID_RESTRICTED_MASK      (( 1u << RestrictedSPID) | RBSYS_SPID_Measurement_MASK)
  #define RBSYS_SPID_UnsafeDMA_MASK       ( 1u << DmaUnsafeSPID )
  
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

  #if( (RBFS_EmulationDevice != RBFS_EmulationDevice_None) || (RBFS_TraceMeasurement == RBFS_TraceMeasurement_RuntimeConfigurable) )
    #define RBSYS_SPID_MAU_MASK             ( (uint32) 1u << MAUSPID )
  #else
    #define RBSYS_SPID_MAU_MASK             ( 0u )
  #endif

  /* Hint: For U2C, Access via MAU (Memory Access Unit) has to be granted for XCP measurements */
  #define RBSYS_SPID_Measurement_MASK     (RBSYS_SPID_MAU_MASK)

  #define RBSYS_SPID_SAFE_MASK            (( 1u << SafeSPID) | RBSYS_SPID_Measurement_MASK)
  #if( RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Supported )
    #define RBSYS_SPID_SECURE_MASK          ( ((uint32) 1u << SecureSPID)  | RBSYS_SPID_Measurement_MASK)
    #define RBSYS_SPID_SECURE_SPIDs         ( ((uint32) 1u << SecureSPID)) )
  #else
    #define RBSYS_SPID_SECURE_MASK          (RBSYS_SPID_Measurement_MASK)
    #define RBSYS_SPID_SECURE_SPIDs         (0u)
  #endif
  #define RBSYS_SPID_UNSAFE_MASK          (( 1u << UnSafeSPID)  | RBSYS_SPID_Measurement_MASK)
  #define RBSYS_SPID_RESTRICTED_MASK      (( 1u << RestrictedSPID) | RBSYS_SPID_Measurement_MASK)
  #define RBSYS_SPID_UnsafeDMA_MASK       ( 1u << DmaUnsafeSPID )

#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  // Stellar: Masks are not required as access is configured individually
#else
  #error ("Exception: Implementation for this uCFamily is missing")
#endif

#if( RBFS_HexBlockBuild != RBFS_HexBlockBuild_APPLICATION )
  /**
    * @brief Enhanced guard configuration
    *
    * PEGuards are already configured within BasicGuardInit
    *
    * This function will configure all PBUS Guards, HBus Guards, INTC Guards, IBus Guards, DMA Guard.
    *
    * Hint: This function shall be called by core 0.
    * Hint: This function can be used in Bootblock ( -> only to be used by RBBootblockHSW! )
    *       as well as in Application              ( -> only to be used by RBSYS internally! ).
    *
    * @param void
    *
    * @return void
    */
  extern void RBSYS_EnhancedGuardInit(void);
#endif

#endif //< multi-include-protection