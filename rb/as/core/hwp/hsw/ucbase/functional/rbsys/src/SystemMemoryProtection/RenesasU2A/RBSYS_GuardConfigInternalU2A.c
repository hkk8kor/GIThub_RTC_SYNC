/**
 * @ingroup RBSYS
 * @{
 *
 * @file  RBSYS_GuardConfigInternalU2A.c
 * @brief Guard based System Memory Protection
 *
 * The RH850 platform incorporates the memory protection function to prevent erroneous accesses to data in memories and
 * peripheral registers.
 *
 * Therefore each memory is protected by decentralized slave guards:
 * - PEG (PE guard):                The local RAM of a PE is protected against illegal accesses by other bus masters
 * - SPIDCTL (SPID config):         System Protection Identifiers are configured in this module
 * - CRG/CSG (global RAM guard):    The global RAM is protected against illegal accesses
 * - IBG (Inter-Cluster Bus Guard): Inter-Cluster Bus connects CPU-related Modules to be shared between clusters
 * - PBG, HBG (Peripheral Guards):  The control registers in the peripheral circuits and memories are protected against illegal accesses
 * - INTC2, DTSGuard, DMAGuard:     These modules are protected by separate guards
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


#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

  #include "RBSYS_GuardConfigInternalU2A.h"

  RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                            RBFS_TargetDevice_RenesasD1,
                            RBFS_TargetDevice_RenesasD2,
                            RBFS_TargetDevice_RenesasD3,
                            RBFS_TargetDevice_RenesasD4,
                            RBFS_TargetDevice_RenesasD5,
                            RBFS_TargetDevice_RenesasM2,
                            RBFS_TargetDevice_RenesasM3,
                            RBFS_TargetDevice_RenesasM6,
                            RBFS_TargetDevice_RenesasD7,
                            RBFS_TargetDevice_STMP6);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                            RBFS_HexBlockBuild_BOOTMANAGER,
                            RBFS_HexBlockBuild_BOOTLOADER,
                            RBFS_HexBlockBuild_RBBOOTLOADER,
                            RBFS_HexBlockBuild_APPLICATION);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_BootblockEnableAsicSupport,
                            RBFS_BootblockEnableAsicSupport_ON,
                            RBFS_BootblockEnableAsicSupport_OFF);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysExclusiveSPID,
                            RBFS_SysExclusiveSPID_Used,
                            RBFS_SysExclusiveSPID_NotUsed);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                            RBFS_SysEnvironment_Target,
                            RBFS_SysEnvironment_Simulation);

  #if( (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION) \
    || (RBFS_BootblockEnableAsicSupport == RBFS_BootblockEnableAsicSupport_ON) )

    RB_ASSERT_SWITCH_SETTINGS(RBFS_HardwareSecurityModule,
                              RBFS_HardwareSecurityModule_Supported,
                              RBFS_HardwareSecurityModule_Unsupported);

    static const RBSYS_BUSGuardConfig_t rbsys_PBusGuardConfigs[] = {
      /** SPID_Register            , SPID_MASK            ,                                 PROT_Register            , PROT_Setting ,       KCPROT_Register   */
      /** PBUS Guard Group 00 - Channel 0 to 6                                                                               */
      {   RBSYS_SPID_REGAddr(00,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(00,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      {   RBSYS_SPID_REGAddr(00,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(00,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      {   RBSYS_SPID_REGAddr(00,2) , (RBSYS_SPID_SAFE_MASK /* | RBSYS_SPID_SECURE_MASK*/) , RBSYS_PROT_REGAddr(00,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)}, //< HSM needs access to BOOTCTRL to trigger Host core
      /* Explanation for 00,2 => If HSM is active, HSM does start first and has access to BOOTCTRL. After triggering startup of Core0, the access can be restricted. */
      {   RBSYS_SPID_REGAddr(00,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(00,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      {   RBSYS_SPID_REGAddr(00,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(00,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      {   RBSYS_SPID_REGAddr(00,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(00,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      {   RBSYS_SPID_REGAddr(00,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(00,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      /** PBUS Guard Group 01 - Channel 0 to 3                                                                                   */
      //{   RBSYS_SPID_REGAddr(01,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(01,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)}, //< Initialized earlier to prevent modification of other guards
      //{   RBSYS_SPID_REGAddr(01,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(01,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)}, //< Initialized earlier to prevent modification of other guards
      //{   RBSYS_SPID_REGAddr(01,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(01,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)}, //< Initialized earlier to prevent modification of other guards
      //{   RBSYS_SPID_REGAddr(01,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(01,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)}, //< Initialized earlier to prevent modification of other guards
      /** PBUS Guard Group 10 - Channel 0 to 2                                                                                                       */
      {   RBSYS_SPID_REGAddr(10,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(10,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(10)},
      {   RBSYS_SPID_REGAddr(10,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(10,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(10)},
      {   RBSYS_SPID_REGAddr(10,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(10,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(10)},
      /** PBUS Guard Group 20 - Channel 0 to 15                                                                                                      */
      {   RBSYS_SPID_REGAddr(20,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)}, // No HSM Access here!!
      {   RBSYS_SPID_REGAddr(20,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,8) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,9) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,10), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,11), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,12), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,13), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,14), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,14), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(20,15), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(20,15), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      /** PBUS Guard Group 21 - Channel 0 to 15                                                                                                      */
      {   RBSYS_SPID_REGAddr(21,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,8) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,9) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,10), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,11), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,12), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,13), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,14), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,14), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,15), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,15), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      /** PBUS Guard Group 22 - Channel 0 to 13                                                                                  */
      {   RBSYS_SPID_REGAddr(22,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,8) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,9) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,10), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,11), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,12), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(22,13), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      /** PBUS Guard Group 30 - Channel 0 to 15                                                                                                      */
      {   RBSYS_SPID_REGAddr(30,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,8) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,9) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,10), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,11), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,12), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,13), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,14), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,14), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(30,15), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(30,15), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      /** PBUS Guard Group 31 - Channel 0 to 13                                                                                                      */
      {   RBSYS_SPID_REGAddr(31,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,8) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,9) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,10), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,11), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,12), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(31,13), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      /** PBUS Guard Group 32 - Channel 0 to 15                                                                                                      */
      {   RBSYS_SPID_REGAddr(32,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,8) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,9) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,10), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,11), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,12), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,13), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,14), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,14), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(32,15), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(32,15), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      /** PBUS Guard Group 33 - Channel 0 to 5                                                                                                      */
      {   RBSYS_SPID_REGAddr(33,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(33,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(33,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(33,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(33,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(33,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(33,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(33,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(33,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(33,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      {   RBSYS_SPID_REGAddr(33,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(33,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      /** PBUS Guard Group 40 - Channel 0 to 7                                                                                                      */
      {   RBSYS_SPID_REGAddr(40,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      /** PBUS Guard Group 50 - Channel 0 to 15                                                                                                      */
      {   RBSYS_SPID_REGAddr(50,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,8) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,9) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,10), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,11), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,12), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,13), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,14), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,14), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(50,15), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(50,15), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      /** PBUS Guard Group 51 - Channel 0 to 15                                                                                                      */
      {   RBSYS_SPID_REGAddr(51,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,8) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,9) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,10), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,11), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,12), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,13), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,14), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,14), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,15), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,15), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      /** PBUS Guard Group 52 - Channel 0 to 15                                                                                                      */
      {   RBSYS_SPID_REGAddr(52,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,8) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,9) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,10), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,11), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,12), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,13), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,14), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,14), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,15), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,15), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      /** PBUS Guard Group 53 - Channel 0 to 6                                                                                                      */
      {   RBSYS_SPID_REGAddr(53,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(53,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(53,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(53,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(53,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(53,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(53,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(53,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(53,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(53,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(53,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(53,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(53,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(53,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      /** PBUS Guard Group 6L0 - Channel 0 to 6                                                                                                     */
      {   RBSYS_SPID_REGAddr(6L0,0) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(6L0,0), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6L0)},
      {   RBSYS_SPID_REGAddr(6L0,1) , (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK) ,     RBSYS_PROT_REGAddr(6L0,1), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6L0)}, //< HSM needs access to Password Protection registers
      {   RBSYS_SPID_REGAddr(6L0,2) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(6L0,2), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6L0)},
      {   RBSYS_SPID_REGAddr(6L0,3) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(6L0,3), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6L0)},
      {   RBSYS_SPID_REGAddr(6L0,4) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(6L0,4), RBSYS_PROT_EnReadLock,     RBSYS_KCPROT_REGAddr(6L0)}, // ADC is read by DMA - restrict this if not needed
      {   RBSYS_SPID_REGAddr(6L0,5) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(6L0,5), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6L0)},
      {   RBSYS_SPID_REGAddr(6L0,6) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(6L0,6), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6L0)},
      /** PBUS Guard Group 6L1 - Channel 0 to 3                                                                                                     */
      #if( RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Unsupported )
        {   RBSYS_SPID_REGAddr(6L1,0) , (RBSYS_SPID_SAFE_MASK) ,                            RBSYS_PROT_REGAddr(6L1,0), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6L1)},
        {   RBSYS_SPID_REGAddr(6L1,1) , (RBSYS_SPID_SAFE_MASK) ,                            RBSYS_PROT_REGAddr(6L1,1), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6L1)},
        {   RBSYS_SPID_REGAddr(6L1,2) , (RBSYS_SPID_SAFE_MASK) ,                            RBSYS_PROT_REGAddr(6L1,2), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6L1)},
        {   RBSYS_SPID_REGAddr(6L1,3) , (RBSYS_SPID_SAFE_MASK) ,                            RBSYS_PROT_REGAddr(6L1,3), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6L1)},
      #else
        // We cannot modify PBG6L1 because PBG6L1_0 protects itself and PBG6L1_1,2,3 from being accessed by Unsecure Busmasters (PBG6L1_0.SEC is 0 if HSM is enabled)
      #endif
      /** PBUS Guard Group 6H0 - Channel 0 to 2                                                                                                     */
      {   RBSYS_SPID_REGAddr(6H0,0) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(6H0,0), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6H0)},
      {   RBSYS_SPID_REGAddr(6H0,1) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(6H0,1), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6H0)},
      {   RBSYS_SPID_REGAddr(6H0,2) , (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_UnsafeDMA_MASK) ,  RBSYS_PROT_REGAddr(6H0,2), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(6H0)}, //< Safety: GTM is not used safety critically
      /** PBUS Guard Group 70 - Channel 0 to 4                                                                                                      */
      {   RBSYS_SPID_REGAddr(70,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(70,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(70)},
      {   RBSYS_SPID_REGAddr(70,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(70,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(70)},
      {   RBSYS_SPID_REGAddr(70,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(70,2) , RBSYS_PROT_EnReadLock,     RBSYS_KCPROT_REGAddr(70)}, // ADC is read by DMA - restrict this if not needed
      {   RBSYS_SPID_REGAddr(70,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(70,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(70)},
      {   RBSYS_SPID_REGAddr(70,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(70,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(70)},
      /** PBUS Guard Group 80 - Channel 0 to 10                                                                                                     */
      {   RBSYS_SPID_REGAddr(80,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(80,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(80)},
      {   RBSYS_SPID_REGAddr(80,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(80,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(80)},
      {   RBSYS_SPID_REGAddr(80,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(80,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(80)},
      {   RBSYS_SPID_REGAddr(80,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(80,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(80)},
      {   RBSYS_SPID_REGAddr(80,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(80,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(80)},
      {   RBSYS_SPID_REGAddr(80,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(80,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(80)},
      {   RBSYS_SPID_REGAddr(80,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(80,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(80)},
      {   RBSYS_SPID_REGAddr(80,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(80,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(80)},
      {   RBSYS_SPID_REGAddr(80,8) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(80,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(80)},
      {   RBSYS_SPID_REGAddr(80,9) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(80,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(80)},
      {   RBSYS_SPID_REGAddr(80,10), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(80,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(80)},
      /** PBUS Guard Group 90 - Channel 0 to 7                                                                                                      */
      {   RBSYS_SPID_REGAddr(90,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)},
      {   RBSYS_SPID_REGAddr(90,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)},
      {   RBSYS_SPID_REGAddr(90,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)},
      //{   RBSYS_SPID_REGAddr(90,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)}, //< Initialized earlier to prevent modification of other guards
      {   RBSYS_SPID_REGAddr(90,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)},
      {   RBSYS_SPID_REGAddr(90,5) , (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK),       RBSYS_PROT_REGAddr(90,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)}, // HSM needs access to own Command register
      {   RBSYS_SPID_REGAddr(90,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)},
      {   RBSYS_SPID_REGAddr(90,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)}
    };

    void RBSYS_PBUSGuardInit(void)
    {
      rbsys_InitializeGuards(rbsys_PBusGuardConfigs, sizeof(rbsys_PBusGuardConfigs)/sizeof(RBSYS_BUSGuardConfig_t));
    }

    static const RBSYS_BUSGuardConfig_t rbsys_PBusGuardConfigs_ForPEGuard[] = {
      /* Restrict Write Access to PEGuard Registers */
      {   RBSYS_SPID_REGAddr(01,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(01,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      {   RBSYS_SPID_REGAddr(01,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(01,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasM2 ) //< PBG01.2 and PBG01.3 are not implemented for M2
        { RBSYS_SPID_REGAddr(01,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(01,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
        { RBSYS_SPID_REGAddr(01,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(01,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      #endif
      /* Restrict Write Access to SPIDCTL Registers */
      {   RBSYS_SPID_REGAddr(90,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)},
    };

    static const RBSYS_BUSGuardConfig_t rbsys_HBusGuardConfigs[] = {
      /** SPID_Register,        SPID_MASK,                   PROT_Register,         PROT_Setting,       KCPROT_Register   */
      #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasM2 )
        { &HBG91HBGPROT1,       RBSYS_SPID_SAFE_MASK,        &HBG91HBGPROT0,        RBSYS_PROT_EnLock,        &HBGHBGERRSLV91HBGKCPROT}, // RHSIF0 "Renesas High-Speed Serial I/F"
      #endif
      {   &HBG92HBGPROT1,       RBSYS_SPID_SAFE_MASK,        &HBG92HBGPROT0,        RBSYS_PROT_EnLock,        &HBGHBGERRSLV92HBGKCPROT}, // FLXA0
      #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasM2 )
        { &HBG93HBGPROT1,       RBSYS_SPID_SAFE_MASK,        &HBG93HBGPROT0,        RBSYS_PROT_EnLock,        &HBGHBGERRSLV93HBGKCPROT}, // FLXA1
      #endif
      {   &HBG96HBGPROT1,       RBSYS_SPID_SAFE_MASK,        &HBG96HBGPROT0,        RBSYS_PROT_EnLock,        &HBGHBGERRSLV96HBGKCPROT}, // SFMA0 "Serial Flash Memory Interface A"
    };

    void RBSYS_HBusGuardInit(void)
    {
      rbsys_InitializeGuards(rbsys_HBusGuardConfigs, sizeof(rbsys_HBusGuardConfigs)/sizeof(RBSYS_BUSGuardConfig_t));
    }

  #endif // (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION) || (RBFS_BootblockEnableAsicSupport == RBFS_BootblockEnableAsicSupport_ON)

  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )

    RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHsmSharedGRAMsize,
                              RBFS_SysHsmSharedGRAMsize_0K,
                              RBFS_SysHsmSharedGRAMsize_16K,
                              RBFS_SysHsmSharedGRAMsize_32K);

    RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHSMsharedGRAM,
                              RBFS_SysHSMsharedGRAM_Host,
                              RBFS_SysHSMsharedGRAM_Restricted);

    RB_ASSERT_SWITCH_SETTINGS(RBFS_RestrictedExclusiveGRAMsize,
                              RBFS_RestrictedExclusiveGRAMsize_0K,
                              RBFS_RestrictedExclusiveGRAMsize_64K,
                              RBFS_RestrictedExclusiveGRAMsize_128K,
                              RBFS_RestrictedExclusiveGRAMsize_256K);

    RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasU2aCRAM0,
                              RBFS_RenesasU2aCRAM0_ON,
                              RBFS_RenesasU2aCRAM0_OFF);

    RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasU2aCRAM1,
                              RBFS_RenesasU2aCRAM1_ON,
                              RBFS_RenesasU2aCRAM1_OFF);

    RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasU2aCRAM2,
                              RBFS_RenesasU2aCRAM2_ON,
                              RBFS_RenesasU2aCRAM2_OFF);

    RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasU2aCRAM3,
                              RBFS_RenesasU2aCRAM3_ON,
                              RBFS_RenesasU2aCRAM3_OFF);

    RB_ASSERT_SWITCH_SETTINGS(RBFS_EmulationDevice,
                              RBFS_EmulationDevice_None,
                              RBFS_EmulationDevice_RenesasD7ED,
                              RBFS_EmulationDevice_RenesasM6ED);


    boolean RBSYS_VerifyFinalHBUSGuardSettings(void)
    {
      return rbsys_VerifyGuardSettings(rbsys_HBusGuardConfigs, sizeof(rbsys_HBusGuardConfigs)/sizeof(RBSYS_BUSGuardConfig_t));
    }

    boolean RBSYS_VerifyFinalPBUSGuardSettings(void)
    {
      boolean isPBUSGuardSettingOk, isPBUSGuardSettingPreInitOk;

      isPBUSGuardSettingPreInitOk = rbsys_VerifyGuardSettings( rbsys_PBusGuardConfigs_ForPEGuard, sizeof(rbsys_PBusGuardConfigs_ForPEGuard)/sizeof(RBSYS_BUSGuardConfig_t));
      isPBUSGuardSettingOk        = rbsys_VerifyGuardSettings( rbsys_PBusGuardConfigs,            sizeof(rbsys_PBusGuardConfigs)/sizeof(RBSYS_BUSGuardConfig_t));

      return (isPBUSGuardSettingPreInitOk && isPBUSGuardSettingOk);
    }

    void RBSYS_GRAMGuardLock(void)
    {
      /** Only CSGs are locked  separately. CRG is locked by setting the PBG for the CRG registers */
      uint32 i;

      #if(RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON)
        RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG0CRGKCPROT);
        GUARD_CRAMCSG0CSGPROT0 |= RBSYS_CRAMGUARD_LOCK;
        GUARD_CRAMCSG0CSGPROT1 |= RBSYS_CRAMGUARD_LOCK;
        GUARD_CRAMCSG0CSGPROT2 |= RBSYS_CRAMGUARD_LOCK;
        GUARD_CRAMCSG0CSGPROT3 |= RBSYS_CRAMGUARD_LOCK;
        RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG0CRGKCPROT);
      #endif

      #if(RBFS_RenesasU2aCRAM1 == RBFS_RenesasU2aCRAM1_ON)
        RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG1CRGKCPROT);
        GUARD_CRAMCSG1CSGPROT0 |= RBSYS_CRAMGUARD_LOCK;
        GUARD_CRAMCSG1CSGPROT1 |= RBSYS_CRAMGUARD_LOCK;
        GUARD_CRAMCSG1CSGPROT2 |= RBSYS_CRAMGUARD_LOCK;
        GUARD_CRAMCSG1CSGPROT3 |= RBSYS_CRAMGUARD_LOCK;
        RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG1CRGKCPROT);
      #endif

      #if(RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON)
        RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG2CRGKCPROT);
        GUARD_CRAMCSG2CSGPROT0 |= RBSYS_CRAMGUARD_LOCK;
        GUARD_CRAMCSG2CSGPROT1 |= RBSYS_CRAMGUARD_LOCK;
        GUARD_CRAMCSG2CSGPROT2 |= RBSYS_CRAMGUARD_LOCK;
        GUARD_CRAMCSG2CSGPROT3 |= RBSYS_CRAMGUARD_LOCK;
        RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG2CRGKCPROT);
      #endif

      #if(RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON)
        RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG3CRGKCPROT);
        GUARD_CRAMCSG3CSGPROT0 |= RBSYS_CRAMGUARD_LOCK;
        GUARD_CRAMCSG3CSGPROT1 |= RBSYS_CRAMGUARD_LOCK;
        GUARD_CRAMCSG3CSGPROT2 |= RBSYS_CRAMGUARD_LOCK;
        GUARD_CRAMCSG3CSGPROT3 |= RBSYS_CRAMGUARD_LOCK;
        RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG3CRGKCPROT);
      #endif
    }


    /**
      * @brief Check guard registers of the passed group and the passed length for the specified values (agreed with GUAM development) in the list
      *
      * @param void
      *
      * @return TRUE if all as expected, FALSE else
      */
    static boolean RBSYS_VerifyFrozenGuards(const RBSYS_GuardsList_t* GuardElementPtr, uint32 NumElements)
    {
      uint32 i;
      boolean result = TRUE;

      for(i=0; i<NumElements; i++)
      {
        if(*(GuardElementPtr[i].Guard_Register) != GuardElementPtr[i].GuardValue)
        {
          result = FALSE;
        }
      }
      return result;
    }


    static const RBSYS_GuardsList_t RBSYS_GuardsFreezeListAll[] = {
      /* CRAM Guards CSG (4 Slave Guards x 4 channels)
        Only CSG0_0 is set in case HSM is used. All others shall be disabled. */
      #if(RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON)
        #if( RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K )
          {&GUARD_CRAMCSG0CSGBAD0, RBSYS_CSG0_GUARDREGION0_BASEADDR & RBSYS_CSG0_VALID_BITS},
          {&GUARD_CRAMCSG0CSGADV0, RBSYS_CSG0_GUARDREGION0_MASK & RBSYS_CSG0_VALID_BITS},
          #if( RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted )
            {&GUARD_CRAMCSG0CSGSPID0, (RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SECURE_MASK)},
          #else
            {&GUARD_CRAMCSG0CSGSPID0, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},
          #endif
          {&GUARD_CRAMCSG0CSGPROT0, RBSYS_CRAMGUARD_ENABLE | RBSYS_CRAMGUARD_LOCK},
        #else
          { &GUARD_CRAMCSG0CSGPROT0, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        #endif
        { &GUARD_CRAMCSG0CSGPROT1, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        { &GUARD_CRAMCSG0CSGPROT2, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        { &GUARD_CRAMCSG0CSGPROT3, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
      #endif
      #if(RBFS_RenesasU2aCRAM1 == RBFS_RenesasU2aCRAM1_ON)
        { &GUARD_CRAMCSG1CSGPROT0, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        { &GUARD_CRAMCSG1CSGPROT1, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        { &GUARD_CRAMCSG1CSGPROT2, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        { &GUARD_CRAMCSG1CSGPROT3, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
      #endif
      #if(RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON)
        { &GUARD_CRAMCSG2CSGPROT0, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        { &GUARD_CRAMCSG2CSGPROT1, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        { &GUARD_CRAMCSG2CSGPROT2, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        { &GUARD_CRAMCSG2CSGPROT3, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
      #endif
      #if(RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON)
        { &GUARD_CRAMCSG3CSGPROT0, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        { &GUARD_CRAMCSG3CSGPROT1, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        { &GUARD_CRAMCSG3CSGPROT2, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        { &GUARD_CRAMCSG3CSGPROT3, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
      #endif

      /* PE Guards PEG (2 Used PEs with one Guard each x 8 Channels)
        Only every first channel is used to protect the whole LRAM */
      // GUARD_PE0CL0PEGxx0 -> LRAM 0 Guard (see RBSYS_PEGuardInit)
      // GUARD_PE0CL0PEGxx1 -> Core 0 INTC1 Guard (see RBSYS_PEGuardInit)
      {&GUARD_PE0CL0PEGPROT2, 0x00000000u}, /* all other channels are disabled */
      {&GUARD_PE0CL0PEGPROT3, 0x00000000u},
      {&GUARD_PE0CL0PEGPROT4, 0x00000000u},
      {&GUARD_PE0CL0PEGPROT5, 0x00000000u},
      {&GUARD_PE0CL0PEGPROT6, 0x00000000u},
      {&GUARD_PE0CL0PEGPROT7, 0x00000000u},

      // GUARD_PE1CL0PEGxx0 -> LRAM 1 Guard (see RBSYS_PEGuardInit)
      // GUARD_PE1CL0PEGxx1 -> Core 1 INTC1 Guard (see RBSYS_PEGuardInit)
      {&GUARD_PE1CL0PEGPROT2, 0x00000000u}, /* all other channels are disabled */
      {&GUARD_PE1CL0PEGPROT3, 0x00000000u},
      {&GUARD_PE1CL0PEGPROT4, 0x00000000u},
      {&GUARD_PE1CL0PEGPROT5, 0x00000000u},
      {&GUARD_PE1CL0PEGPROT6, 0x00000000u},
      {&GUARD_PE1CL0PEGPROT7, 0x00000000u},

      // SPID Masks have to be verified
      { &SPIDCTLBM00SPIDMSK, (1u<<SafeSPID) | (1u<<RestrictedSPID) }, // CPU0
      { &SPIDCTLBM01SPIDMSK, (1u<<SafeSPID) | (1u<<RestrictedSPID) }, // CPU1
      #if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6))       //< Core 2/3 are only available on D7
        { &SPIDCTLBM02SPIDMSK,  0u                                 }, // CPU2 -> unused
        { &SPIDCTLBM03SPIDMSK,  0u                                 }, // CPU3 -> unused
      #endif
      #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasM2 )
        { &SPIDCTLBM17SPIDMSK, (1u<<UnSafeSPID)                      }, // GBit Ethernet
        { &SPIDCTLBM19SPIDMSK, (1u<<UnSafeSPID)                      }, // RHSIF0
        { &SPIDCTLBM22SPIDMSK, (1u<<UnSafeSPID)                      }, // FlexRay1
      #endif
      { &SPIDCTLBM23SPIDMSK, (1u<<UnSafeSPID)                      }, // FlexRay0
      { &SPIDCTLBM24SPIDMSK, (1u<<UnSafeSPID)                      }, // Fast Ethernet
      { &SPIDCTLBM25SPIDMSK, RBSYS_SPID_SECURE_SPIDs               }, // ICUM_AES0
      { &SPIDCTLBM26SPIDMSK, RBSYS_SPID_SECURE_SPIDs               }, // ICUMHA
      { &SPIDCTLBM27SPIDMSK, (1u<<DmaUnsafeSPID)                   }, // sDMAC1
      { &SPIDCTLBM28SPIDMSK, (1u<<DmaUnsafeSPID)                   }, // sDMAC0
      { &SPIDCTLBM29SPIDMSK, (1u<<SafeSPID)                        }, // DTS
      #if( (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD7ED) || (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasM6ED) )
        { &SPIDCTLBM30SPIDMSK, RBSYS_SPID_Measurement_MASK         }, // AUD - Advanced User Debugger (only on M6ED)
      #endif
      { &SPIDCTLBM31SPIDMSK, RBSYS_SPID_Measurement_MASK           }  // MAU - Memory Access Unit
    };

    boolean RBSYS_VerifyFinalSPIDandPEGandCSGGuardSettings(void)
    {
      return RBSYS_VerifyFrozenGuards(&RBSYS_GuardsFreezeListAll[0], sizeof(RBSYS_GuardsFreezeListAll)/sizeof(RBSYS_GuardsList_t));
    }

    #if (  (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K) \
        && (RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON))

      void RBSYS_RestrictedExclusiveGRAM_AllowSafeAccess(void)
      {
        #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
          RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG3CRGKCPROT);
          GUARD_CRAMCRG3CRGPROT0 &= ~RBSYS_CRAMGUARD_ENABLE;
          GUARD_CRAMCRG3CRGSPID0 = RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK;
          //< BERT is running in parallel to other SW components (on other cores), therefore RESTRICTED AND SAFE has to be allowed
          GUARD_CRAMCRG3CRGPROT0 |= RBSYS_CRAMGUARD_ENABLE;
          RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG3CRGKCPROT);
        #endif
      }


      void RBSYS_RestrictedExclusiveGRAM_BlockSafeAccess(void)
      {
        #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
          RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG3CRGKCPROT);
          GUARD_CRAMCRG3CRGPROT0 &= ~RBSYS_CRAMGUARD_ENABLE;
          GUARD_CRAMCRG3CRGSPID0 = RBSYS_SPID_RESTRICTED_MASK;
          GUARD_CRAMCRG3CRGPROT0 |= RBSYS_CRAMGUARD_ENABLE;
          RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG3CRGKCPROT);
        #endif
      }

    #endif //< RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K

    #if (  (RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted) \
        && (RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON))
      /**
        * @brief Finally sets the SPID setting for Restricted HSM Shared GRAM (if configured)
        *
        * Restricted HSM Shared GRAM is configured to be shared between RESTRICTED, SAFE and SECURE SPID by default.
        * SAFE SPID is allowed to write into this area to support the initialization of variables with SAFE SPID.
        * When calling this API, SAFE SPID will be removed from the list of permitted SPIDs.
        *
        * @param void
        *
        * @return void
        */
      void RBSYS_RestrictedHSMSharedGRAM_BlockSafeAccess(void)
      {
        #if( RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K )
          RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG0CRGKCPROT);

          GUARD_CRAMCSG0CSGPROT0 &= ~RBSYS_CRAMGUARD_ENABLE;
          GUARD_CRAMCSG0CSGSPID0 = (RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SECURE_MASK);
          GUARD_CRAMCSG0CSGPROT0 |= RBSYS_CRAMGUARD_ENABLE;

          RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG0CRGKCPROT);
        #endif
      }
    #endif //< RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted

    #if( RBFS_SysExclusiveSPID == RBFS_SysExclusiveSPID_Used )
      #if( RBFS_SysEnvironment == RBFS_SysEnvironment_Target )
        volatile uint32 RBSYS_TrapPermissionHandlingStack[2][2];

        RBSECTION_START_SECTTYPE_NO_SDA
          volatile unsigned int* const RBSYS_TrapPermissionHandlingStack0_StartAddressPtr = &RBSYS_TrapPermissionHandlingStack[0][0];
          volatile unsigned int* const RBSYS_TrapPermissionHandlingStack1_StartAddressPtr = &RBSYS_TrapPermissionHandlingStack[1][0];
        RBSECTION_END_SECTTYPE_NO_SDA
      #endif
    #endif

  #endif //< RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION


#endif

/** @} */
/* End ingroup RBSYS */