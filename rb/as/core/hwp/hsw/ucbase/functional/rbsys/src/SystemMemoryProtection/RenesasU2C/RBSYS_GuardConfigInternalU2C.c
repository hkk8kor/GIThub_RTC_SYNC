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


#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

  #include "RBSYS_GuardConfigInternalU2C.h"

  RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                            RBFS_TargetDevice_RenesasK0,
                            RBFS_TargetDevice_RenesasK1);

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
      /** PBUS Guard Group 00 - Channel 0 to 3                                                                               */
      //  {   RBSYS_SPID_REGAddr(00,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(00,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)}, //< Initialized earlier to prevent modification of other guards
      {   RBSYS_SPID_REGAddr(00,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(00,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      {   RBSYS_SPID_REGAddr(00,2) , (RBSYS_SPID_SAFE_MASK /* | RBSYS_SPID_SECURE_MASK*/) , RBSYS_PROT_REGAddr(00,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)}, //< HSM needs access to BOOTCTRL to trigger Host core
      /* Explanation for 00,2 => If HSM is active, HSM does start first and has access to BOOTCTRL. After triggering startup of Core0, the access can be restricted. */
      {   RBSYS_SPID_REGAddr(00,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(00,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      /** PBUS Guard Group 01 - Channel 0 to 1                                                                                   */
      //{   RBSYS_SPID_REGAddr(01,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(01,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)}, //< Initialized earlier to prevent modification of other guards
      //{   RBSYS_SPID_REGAddr(01,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(01,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)}, //< Initialized earlier to prevent modification of other guards
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
      // "Reserved": {   RBSYS_SPID_REGAddr(21,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,8) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,9) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      // "Reserved": {   RBSYS_SPID_REGAddr(21,10), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,11), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,12), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,13), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      // "Reserved": {   RBSYS_SPID_REGAddr(21,14), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,14), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      {   RBSYS_SPID_REGAddr(21,15), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(21,15), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
      /** PBUS Guard Group 22 - Channel 0 to 12                                                                                  */
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
      // "Reserved": {   RBSYS_SPID_REGAddr(22,12), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(22,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(20)},
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
      /** PBUS Guard Group 31 - Channel 0                                                                                                      */
      {   RBSYS_SPID_REGAddr(31,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(31,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(30)},
      /** PBUS Guard Group 40 - Channel 0 to 15                                                                                                      */
      {   RBSYS_SPID_REGAddr(40,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,7) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,8) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,9) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(40,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,10) , RBSYS_SPID_SAFE_MASK,                                 RBSYS_PROT_REGAddr(40,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,11) , RBSYS_SPID_SAFE_MASK,                                 RBSYS_PROT_REGAddr(40,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,12) , RBSYS_SPID_SAFE_MASK,                                 RBSYS_PROT_REGAddr(40,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,13) , RBSYS_SPID_SAFE_MASK,                                 RBSYS_PROT_REGAddr(40,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,14) , RBSYS_SPID_SAFE_MASK,                                 RBSYS_PROT_REGAddr(40,14), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      {   RBSYS_SPID_REGAddr(40,15) , RBSYS_SPID_SAFE_MASK,                                 RBSYS_PROT_REGAddr(40,15), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
      /** PBUS Guard Group 41 - Channel 0                                                                                                      */
      {   RBSYS_SPID_REGAddr(41,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(41,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(40)},
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
      // "Reserved": {   RBSYS_SPID_REGAddr(51,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,0) , RBSYS_PROT_EnReadLock,     RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      // "Reserved": {   RBSYS_SPID_REGAddr(51,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
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
      // "Reserved": {   RBSYS_SPID_REGAddr(51,13), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      // "Reserved": {   RBSYS_SPID_REGAddr(51,14), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,14), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(51,15), RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(51,15), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      /** PBUS Guard Group 52 - Channel 0 to 5                                                                                                      */
      {   RBSYS_SPID_REGAddr(52,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,2) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      {   RBSYS_SPID_REGAddr(52,5) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(52,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(50)},
      /** PBUS Guard Group 60 - Channel 0 to 5                                                                                                     */
      {   RBSYS_SPID_REGAddr(60,0) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(60,0), RBSYS_PROT_EnLock,           RBSYS_KCPROT_REGAddr(60)},
      {   RBSYS_SPID_REGAddr(60,1) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(60,1), RBSYS_PROT_EnLock,           RBSYS_KCPROT_REGAddr(60)},
      {   RBSYS_SPID_REGAddr(60,2) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(60,2), RBSYS_PROT_EnLock,           RBSYS_KCPROT_REGAddr(60)},
      {   RBSYS_SPID_REGAddr(60,3) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(60,3), RBSYS_PROT_EnLock,           RBSYS_KCPROT_REGAddr(60)},
      {   RBSYS_SPID_REGAddr(60,4) , (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK) ,     RBSYS_PROT_REGAddr(60,4), RBSYS_PROT_EnLock,           RBSYS_KCPROT_REGAddr(60)}, //< HSM needs access to Password Protection registers
      {   RBSYS_SPID_REGAddr(60,5) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(60,5), RBSYS_PROT_EnLock,           RBSYS_KCPROT_REGAddr(60)},
      /** PBUS Guard Group 61 - Channel 0 to 2                                                                                                     */
      {   RBSYS_SPID_REGAddr(61,0) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(61,0), RBSYS_PROT_EnLock,           RBSYS_KCPROT_REGAddr(61)},
      {   RBSYS_SPID_REGAddr(61,1) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(61,1), RBSYS_PROT_EnLock,           RBSYS_KCPROT_REGAddr(61)},
      #if( RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Unsupported )
        {   RBSYS_SPID_REGAddr(61,2) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(61,2), RBSYS_PROT_EnLock,           RBSYS_KCPROT_REGAddr(61)},
      #endif
      /** PBUS Guard Group 7H0 - Channel 0 to 1                                                                                                     */
      {   RBSYS_SPID_REGAddr(7H0,0) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(7H0,0), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(7H0)},
      {   RBSYS_SPID_REGAddr(7H0,1) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(7H0,1), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(7H0)},
      /** PBUS Guard Group 7L0 - Channel 0 to 2                                                                                                     */
      {   RBSYS_SPID_REGAddr(7L0,0) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(7L0,0), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(7L0)},
      {   RBSYS_SPID_REGAddr(7L0,1) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(7L0,1), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(7L0)},
      {   RBSYS_SPID_REGAddr(7L0,2) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(7L0,2), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(7L0)},
      /** PBUS Guard Group 8H0 - Channel 0 to 5                                                                                                     */
      {   RBSYS_SPID_REGAddr(8H0,0) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8H0,0), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8H0)},
      {   RBSYS_SPID_REGAddr(8H0,1) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8H0,1), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8H0)},
      {   RBSYS_SPID_REGAddr(8H0,2) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8H0,2), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8H0)},
      {   RBSYS_SPID_REGAddr(8H0,3) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8H0,3), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8H0)},
      {   RBSYS_SPID_REGAddr(8H0,4) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8H0,4), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8H0)},
      {   RBSYS_SPID_REGAddr(8H0,5) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8H0,5), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8H0)},
      /** PBUS Guard Group 8L0 - Channel 0 to 13                                                                                                     */
      {   RBSYS_SPID_REGAddr(8L0,0) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,0),  RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      {   RBSYS_SPID_REGAddr(8L0,1) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,1),  RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      {   RBSYS_SPID_REGAddr(8L0,2) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,2),  RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      {   RBSYS_SPID_REGAddr(8L0,3) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,3),  RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      {   RBSYS_SPID_REGAddr(8L0,4) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,4),  RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      {   RBSYS_SPID_REGAddr(8L0,5) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,5),  RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      {   RBSYS_SPID_REGAddr(8L0,6) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,6),  RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      {   RBSYS_SPID_REGAddr(8L0,7) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,7),  RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      {   RBSYS_SPID_REGAddr(8L0,8) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,8),  RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      {   RBSYS_SPID_REGAddr(8L0,9) , (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,9),  RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      {   RBSYS_SPID_REGAddr(8L0,10), (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      {   RBSYS_SPID_REGAddr(8L0,11), (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      {   RBSYS_SPID_REGAddr(8L0,12), (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      // "Reserved": {   RBSYS_SPID_REGAddr(8L0,13), (RBSYS_SPID_SAFE_MASK) ,                              RBSYS_PROT_REGAddr(8L0,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(8L0)},
      /** PBUS Guard Group 90 - Channel 0 to 6                                                                                                      */
      //{   RBSYS_SPID_REGAddr(90,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)}, //< Initialized earlier to prevent modification of other guards
      {   RBSYS_SPID_REGAddr(90,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)},
      {   RBSYS_SPID_REGAddr(90,2) , (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK) ,      RBSYS_PROT_REGAddr(90,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)}, // HSM needs access to own Command register
      //{   RBSYS_SPID_REGAddr(90,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)}, //< Initialized earlier to prevent modification of other guards
      {   RBSYS_SPID_REGAddr(90,4) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)},
      {   RBSYS_SPID_REGAddr(90,5) , RBSYS_SPID_SAFE_MASK,                                  RBSYS_PROT_REGAddr(90,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)},
      // "Reserved": {   RBSYS_SPID_REGAddr(90,6) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)},
      /** PBUS Guard Group 91 (todo: can we even control this? HSM only registers)                                                                                                      */
      /** PBUS Guard Group 100 - Channel 0 to 15                                                                                                      */
      {   RBSYS_SPID_REGAddr(100,0) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,1) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,2) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,3) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,4) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,5) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,6) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,7) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,8) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,9) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,10), RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,11), RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      // Todo: This channel is missing in the device header file and the UM: {   RBSYS_SPID_REGAddr(100,12), RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,13), RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,14), RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,14), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(100,15), RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(100,15), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      /** PBUS Guard Group 101 - Channel 0 to 6                                                                                                      */
      {   RBSYS_SPID_REGAddr(101,0) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(101,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(101,1) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(101,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(101,2) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(101,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(101,3) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(101,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(101,4) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(101,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(101,5) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(101,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      {   RBSYS_SPID_REGAddr(101,6) , RBSYS_SPID_SAFE_MASK ,                                RBSYS_PROT_REGAddr(101,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(100)},
      /** PBUS Guard Group 11H0 - Channel 0 to 15                                                                                                      */
      {   RBSYS_SPID_REGAddr(11H0,0) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,1) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,2) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,3) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      // "Reserved": {   RBSYS_SPID_REGAddr(11H0,4) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,5) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      // "Reserved": {   RBSYS_SPID_REGAddr(11H0,6) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,7) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,7) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,8) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,8) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,9) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,9) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,10), RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,10), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,11), RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,11), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,12), RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,12), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,13), RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,13), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,14), RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,14), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H0,15), RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H0,15), RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      /** PBUS Guard Group 11H1 - Channel 0 to 6                                                                                                      */
      // "Reserved": {   RBSYS_SPID_REGAddr(11H1,0) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H1,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      // "Reserved": {   RBSYS_SPID_REGAddr(11H1,1) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H1,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H1,2) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H1,2) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H1,3) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H1,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H1,4) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H1,4) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H1,5) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H1,5) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      {   RBSYS_SPID_REGAddr(11H1,6) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11H1,6) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11H0)},
      /** PBUS Guard Group 11L0 - Channel 0 to 1                                                                                                      */
      {   RBSYS_SPID_REGAddr(11L0,0) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11L0,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11L0)},
      {   RBSYS_SPID_REGAddr(11L0,1) , RBSYS_SPID_SAFE_MASK ,                               RBSYS_PROT_REGAddr(11L0,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(11L0)},
    };

    void RBSYS_PBUSGuardInit(void)
    {
      rbsys_InitializeGuards(rbsys_PBusGuardConfigs, sizeof(rbsys_PBusGuardConfigs)/sizeof(RBSYS_BUSGuardConfig_t));
    }

    static const RBSYS_BUSGuardConfig_t rbsys_PBusGuardConfigs_ForPEGuard[] = {
      /* Restrict Write Access to PEGuard Registers */
      {   RBSYS_SPID_REGAddr(00,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(00,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      {   RBSYS_SPID_REGAddr(01,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(01,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      {   RBSYS_SPID_REGAddr(01,1) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(01,1) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(00)},
      /* Restrict Write Access to SPIDCTL Registers */
      {   RBSYS_SPID_REGAddr(90,0) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,0) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)},
      {   RBSYS_SPID_REGAddr(90,3) , RBSYS_SPID_SAFE_MASK ,                                 RBSYS_PROT_REGAddr(90,3) , RBSYS_PROT_EnLock,         RBSYS_KCPROT_REGAddr(90)},
    };

    static const RBSYS_BUSGuardConfig_t rbsys_HBusGuardConfigs[] = {
      /** SPID_Register,        SPID_MASK,                   PROT_Register,         PROT_Setting,       KCPROT_Register   */
      #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasK0 )
        { &HBG90HBGPROT1,       RBSYS_SPID_SAFE_MASK,        &HBG90HBGPROT0,        RBSYS_PROT_EnLock,        &HBGERRSLV90HBGKCPROT}, // FLXA0
      #endif
      {   &HBG91HBGPROT1,       RBSYS_SPID_SAFE_MASK,        &HBG91HBGPROT0,        RBSYS_PROT_EnLock,        &HBGERRSLV91HBGKCPROT}, // SFMA0 "Serial Flash Memory Interface A"
      {   &HBG92HBGPROT1,       RBSYS_SPID_SAFE_MASK,        &HBG92HBGPROT0,        RBSYS_PROT_EnLock,        &HBGERRSLV92HBGKCPROT}, // CANXL0
      #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasK0 )
        { &HBG93HBGPROT1,       RBSYS_SPID_SAFE_MASK,        &HBG93HBGPROT0,        RBSYS_PROT_EnLock,        &HBGERRSLV93HBGKCPROT}, // CANXL1
      #endif
      {   &HBG96HBGPROT1,       RBSYS_SPID_SAFE_MASK,        &HBG96HBGPROT0,        RBSYS_PROT_EnLock,        &HBGERRSLV96HBGKCPROT}, // Retention RAM
    };

    void RBSYS_HBusGuardInit(void)
    {
      // rbsys_InitializeGuards(rbsys_HBusGuardConfigs, sizeof(rbsys_HBusGuardConfigs)/sizeof(RBSYS_BUSGuardConfig_t));
    }

  #endif // (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION) || (RBFS_BootblockEnableAsicSupport == RBFS_BootblockEnableAsicSupport_ON)

  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )

    RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHsmSharedGRAMsize,
                              RBFS_SysHsmSharedGRAMsize_0K,
                              RBFS_SysHsmSharedGRAMsize_32K);

    RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHSMsharedGRAM,
                              RBFS_SysHSMsharedGRAM_Host,
                              RBFS_SysHSMsharedGRAM_Restricted);

    RB_ASSERT_SWITCH_SETTINGS(RBFS_RestrictedExclusiveGRAMsize,
                              RBFS_RestrictedExclusiveGRAMsize_0K,
                              RBFS_RestrictedExclusiveGRAMsize_16K,
                              RBFS_RestrictedExclusiveGRAMsize_32K);

    RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasU2cCRAM0,
                              RBFS_RenesasU2cCRAM0_ON,
                              RBFS_RenesasU2cCRAM0_OFF);


    void RBSYS_GRAMGuardLock(void)
    {
      /** Only CSGs are locked  separately. CRG is locked by setting the PBG for the CRG registers */

      // todo: Simulation does not implement CSGs yet...

      // #if(RBFS_RenesasU2cCRAM0 == RBFS_RenesasU2cCRAM0_ON)
      //   RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG0CRGKCPROT);
      //   GUARD_CRAMCSG0CSGPROT0 |= RBSYS_CRAMGUARD_LOCK;
      //   GUARD_CRAMCSG0CSGPROT1 |= RBSYS_CRAMGUARD_LOCK;
      //   GUARD_CRAMCSG0CSGPROT2 |= RBSYS_CRAMGUARD_LOCK;
      //   GUARD_CRAMCSG0CSGPROT3 |= RBSYS_CRAMGUARD_LOCK;
      //   RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG0CRGKCPROT);
      // #endif

      #warning("Todo: Implement CSG GRAM Guards")
    }





    static const RBSYS_GuardsList_t RBSYS_GuardsFreezeListAll[] = {
      /* CRAM Guards CSG (1 CRAM Guard with 4 channels) */
      #if(RBFS_RenesasU2cCRAM0 == RBFS_RenesasU2cCRAM0_ON)
      
        // todo: Simulation does not implement CSGs yet...

        // #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
        //   {&GUARD_CRAMCSG0CSGBAD0,  RBSYS_CSG0_GUARDREGION0_BASEADDR & RBSYS_CSG0_VALID_BITS},
        //   {&GUARD_CRAMCSG0CSGADV0,  RBSYS_CSG0_GUARDREGION0_MASK & RBSYS_CSG0_VALID_BITS},
        //   {&GUARD_CRAMCSG0CSGSPID0, RBSYS_SPID_Restricted_MASK},
        //   {&GUARD_CRAMCSG0CSGPROT0, RBSYS_CRAMGUARD_ENABLE}, //< do not lock, BERT has to change the SPID to allow SAFE accesses
        // #else
        //   { &GUARD_CRAMCSG0CSGPROT0, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        // #endif

        // #if( RBFS_SysEthSharedGRAMsize != RBFS_SysEthSharedGRAMsize_0K )
        //   {&GUARD_CRAMCSG0CSGBAD1,  RBSYS_CSG0_GUARDREGION1_BASEADDR & RBSYS_CSG0_VALID_BITS},
        //   {&GUARD_CRAMCSG0CSGADV1,  RBSYS_CSG0_GUARDREGION1_MASK & RBSYS_CSG0_VALID_BITS},
        //   {&GUARD_CRAMCSG0CSGSPID1, RBSYS_SPID_Unsafe_MASK},
        //   {&GUARD_CRAMCSG0CSGPROT1, RBSYS_CRAMGUARD_ENABLE | RBSYS_CRAMGUARD_LOCK},
        // #else
        //   { &GUARD_CRAMCSG0CSGPROT1, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        // #endif

        // #if( RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K )
        //   {&GUARD_CRAMCSG0CSGBAD2, RBSYS_CSG0_GUARDREGION2_BASEADDR & RBSYS_CSG0_VALID_BITS},
        //   {&GUARD_CRAMCSG0CSGADV2, RBSYS_CSG0_GUARDREGION2_MASK & RBSYS_CSG0_VALID_BITS},
        //   #if( RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted )
        //     {&GUARD_CRAMCSG0CSGSPID2, (RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SECURE_MASK)},
        //   #else
        //     {&GUARD_CRAMCSG0CSGSPID2, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},
        //   #endif
        //   {&GUARD_CRAMCSG0CSGPROT2, RBSYS_CRAMGUARD_ENABLE | RBSYS_CRAMGUARD_LOCK},
        // #else
        //   { &GUARD_CRAMCSG0CSGPROT2, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
        // #endif

        // { &GUARD_CRAMCSG0CSGPROT3, RBSYS_CRAMGUARD_LOCK & ~RBSYS_GUARD_EN}, // disabled & locked
      #endif

      /* PE Guards PEG (2 Used PEs with one Guard each x 8 Channels)
        Only every first channel is used to protect the whole LRAM */
      // GUARD_PE0CL0PEGxx0 -> LRAM 0 Guard (see RBSYS_PEGuardInit)
      // GUARD_PE0CL0PEGxx1 -> Core 0 INTC1 Guard (see RBSYS_PEGuardInit)
      {&GUARD_PE0CL0PEGPROT2, 0x00000000u}, /* all other channels are disabled */
      {&GUARD_PE0CL0PEGPROT3, 0x00000000u},
      // todo: simulation does not implement 8 PEG channels
      // {&GUARD_PE0CL0PEGPROT4, 0x00000000u},
      // {&GUARD_PE0CL0PEGPROT5, 0x00000000u},
      // {&GUARD_PE0CL0PEGPROT6, 0x00000000u},
      // {&GUARD_PE0CL0PEGPROT7, 0x00000000u},

      // GUARD_PE1CL0PEGxx0 -> LRAM 1 Guard (see RBSYS_PEGuardInit)
      // GUARD_PE1CL0PEGxx1 -> Core 1 INTC1 Guard (see RBSYS_PEGuardInit)
      {&GUARD_PE1CL0PEGPROT2, 0x00000000u}, /* all other channels are disabled */
      {&GUARD_PE1CL0PEGPROT3, 0x00000000u},
      // todo: simulation does not implement 8 PEG channels
      // {&GUARD_PE1CL0PEGPROT4, 0x00000000u},
      // {&GUARD_PE1CL0PEGPROT5, 0x00000000u},
      // {&GUARD_PE1CL0PEGPROT6, 0x00000000u},
      // {&GUARD_PE1CL0PEGPROT7, 0x00000000u},

      // SPID Masks have to be verified
      { &SPIDCTLBM00SPIDMSK, (1u<<SafeSPID) | (1u<<RestrictedSPID) }, // CPU0
      #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasK0 )
        { &SPIDCTLBM01SPIDMSK, (1u<<SafeSPID) | (1u<<RestrictedSPID) }, // CPU1
      #endif
      { &SPIDCTLBM10SPIDMSK, (1u<<UnSafeSPID)                      }, // GTM Cluster 0
      { &SPIDCTLBM11SPIDMSK, (1u<<UnSafeSPID)                      }, // GTM Cluster 1
      { &SPIDCTLBM22SPIDMSK, (1u<<UnSafeSPID)                      }, // Ethernet T1S
      { &SPIDCTLBM23SPIDMSK, (1u<<UnSafeSPID)                      }, // ACEU -> todo: could this be safe?
      #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasK0 )
        { &SPIDCTLBM29SPIDMSK, (1u<<UnSafeSPID)                      }, // CANXL 1
      #endif
      { &SPIDCTLBM30SPIDMSK, (1u<<UnSafeSPID)                      }, // CANXL 0
      #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasK0 )
        { &SPIDCTLBM32SPIDMSK, (1u<<UnSafeSPID)                      }, // Flexray0
      #endif
      #if( (RBFS_TargetDevice != RBFS_TargetDevice_RenesasK0) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasK1) )
        { &SPIDCTLBM33SPIDMSK, (1u<<UnSafeSPID)                      }, // EthernetD1
      #endif
      #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasK0 )
        { &SPIDCTLBM34SPIDMSK, (1u<<UnSafeSPID)                      }, // EthernetD0
      #endif

      { &SPIDCTLBM35SPIDMSK, (1u<<SecureSPID)                      }, // ICUM Core
      { &SPIDCTLBM36SPIDMSK, (1u<<SecureSPID)                      }, // ICUM AES Engine
      { &SPIDCTLBM37SPIDMSK, (1u<<SecureSPID)                      }, // ICUM DMA
      { &SPIDCTLBM43SPIDMSK, (1u<<31u)                             }  // ICUM Debug Master
    };

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

    boolean RBSYS_VerifyFinalSPIDandPEGandCSGGuardSettings(void)
    {
      return RBSYS_VerifyFrozenGuards(&RBSYS_GuardsFreezeListAll[0], sizeof(RBSYS_GuardsFreezeListAll)/sizeof(RBSYS_GuardsList_t));
    }

    #warning("HBGs are not implemented for U2C in VLAB yet.")
    // boolean RBSYS_VerifyFinalHBUSGuardSettings(void)
    // {
    //   // return rbsys_VerifyGuardSettings(rbsys_HBusGuardConfigs, sizeof(rbsys_HBusGuardConfigs)/sizeof(RBSYS_BUSGuardConfig_t));
    //   return TRUE;
    // }

    boolean RBSYS_VerifyFinalPBUSGuardSettings(void)
    {
      boolean isPBUSGuardSettingOk, isPBUSGuardSettingPreInitOk;

      isPBUSGuardSettingPreInitOk = rbsys_VerifyGuardSettings( rbsys_PBusGuardConfigs_ForPEGuard, sizeof(rbsys_PBusGuardConfigs_ForPEGuard)/sizeof(RBSYS_BUSGuardConfig_t));
      isPBUSGuardSettingOk        = rbsys_VerifyGuardSettings( rbsys_PBusGuardConfigs,            sizeof(rbsys_PBusGuardConfigs)/sizeof(RBSYS_BUSGuardConfig_t));

      return (isPBUSGuardSettingPreInitOk && isPBUSGuardSettingOk);
    }


    #if (  (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K) \
        && (RBFS_RenesasU2cCRAM0 == RBFS_RenesasU2cCRAM0_ON))

      void RBSYS_RestrictedExclusiveGRAM_AllowSafeAccess(void)
      {
        #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
          RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG0CRGKCPROT);
          GUARD_CRAMCSG0CSGPROT0 &= ~RBSYS_CRAMGUARD_ENABLE;
          GUARD_CRAMCSG0CSGSPID0 = RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK;
          //< BERT is running in parallel to other SW components (on other cores), therefore RESTRICTED AND SAFE has to be allowed
          GUARD_CRAMCSG0CSGPROT0 |= RBSYS_CRAMGUARD_ENABLE;
          RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG0CRGKCPROT);
        #endif
      }


      void RBSYS_RestrictedExclusiveGRAM_BlockSafeAccess(void)
      {
        #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
          RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG0CRGKCPROT);
          GUARD_CRAMCSG0CSGPROT0 &= ~RBSYS_CRAMGUARD_ENABLE;
          GUARD_CRAMCSG0CSGSPID0 = RBSYS_SPID_RESTRICTED_MASK;
          GUARD_CRAMCSG0CSGPROT0 |= RBSYS_CRAMGUARD_ENABLE;
          RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG0CRGKCPROT);
        #endif
      }

    #endif //< RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K

    #if (  (RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted) \
        && (RBFS_RenesasU2cCRAM0 == RBFS_RenesasU2cCRAM0_ON))
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

          GUARD_CRAMCSG0CSGPROT2 &= ~RBSYS_CRAMGUARD_ENABLE;
          GUARD_CRAMCSG0CSGSPID2 = (RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SECURE_MASK);
          GUARD_CRAMCSG0CSGPROT2 |= RBSYS_CRAMGUARD_ENABLE;

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