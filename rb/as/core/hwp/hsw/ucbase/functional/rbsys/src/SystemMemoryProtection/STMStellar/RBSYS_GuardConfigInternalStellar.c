/**
 * @ingroup RBSYS
 * @{
 *
 * @file  RBSYS_GuardConfigInternalStellar.c
 * @brief
 *
 * The STM Stellar platform incorporates the memory protection function to prevent erroneous accesses to data in memories and
 * peripheral registers.
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

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEthSharedGRAMsize,
                            RBFS_SysEthSharedGRAMsize_0K,
                            RBFS_SysEthSharedGRAMsize_32K,
                            RBFS_SysEthSharedGRAMsize_64K,
                            RBFS_SysEthSharedGRAMsize_96K,
                            RBFS_SysEthSharedGRAMsize_128K);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_RestrictedExclusiveGRAMsize,
                            RBFS_RestrictedExclusiveGRAMsize_0K);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHsmSharedGRAMsize,
                            RBFS_SysHsmSharedGRAMsize_0K,
                            RBFS_SysHsmSharedGRAMsize_16K,
                            RBFS_SysHsmSharedGRAMsize_32K);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHSMsharedGRAM,
                            RBFS_SysHSMsharedGRAM_Host);

  /* Overview on Hardware Implementation of the FlexNOC Firewalls
    @startuml
    FlexNOC --> "33" NOCMaster : contains
    FlexNOC --> "25" NOCSlave : contains
    NOCMaster --> NOCSlave : accesses

    NOCSlave "1" <-- "1" Firewall : protects
    Firewall "1" --> "8" Region
    Region : StartAddr
    Region : Size
    Region : MasterPermissionConfig[33]
    @enduml
  */


  #include "RBSYS_GuardConfigInternalStellar.h"
  #include "RBSYS_GuardMemoryMap.h"
  #include "RBSYS_CoreInit.h"
  #include "RBSYS_SystemMpu_Info.h"

  /* Class diagram for FlexNOC Firewalls connectivity "diagram"
    @startuml
    RBSYS_NOCInitiator --> AccessMask
    RBSYS_NOCInitiator --> MasterID

    RBSYS_NOCTarget : NOCFirewall (HWPtr)
    RBSYS_NOCTarget : ConnectedNOCInitiators (bitfield)
    RBSYS_NOCTarget : Num of FW regions (uint32)

    RBSYS_NOCInitiator "1" --> "1" ACCESS_MASK_BusMaster_x
    RBSYS_NOCTarget "1" --> "1..32" ACCESS_MASK_BusMaster_x : contains
    @enduml
  */



  typedef struct
  {
    const uint32 AccessMask;
    const uint32 MasterID;
  } RBSYS_NOCInitiator_t;

  /* These have to be unique - is used as "bitfield" on NOCTarget side */
  #define  ACCESS_DAP0       ((uint32)0x1 << 0)
  #define  ACCESS_DAP1       ((uint32)0x1 << 1)
  #define  ACCESS_FR0        ((uint32)0x1 << 2)
  #define  ACCESS_FR1        ((uint32)0x1 << 3)
  #define  ACCESS_ETH0       ((uint32)0x1 << 4)
  #define  ACCESS_ETH1       ((uint32)0x1 << 5)
  #define  ACCESS_eDMA0      ((uint32)0x1 << 6)
  #define  ACCESS_eDMA1      ((uint32)0x1 << 7)
  #define  ACCESS_eDMA2      ((uint32)0x1 << 8)
  #define  ACCESS_eDMA3      ((uint32)0x1 << 9)
  #define  ACCESS_ZIP0       ((uint32)0x1 << 10)
  #define  ACCESS_ZIP1       ((uint32)0x1 << 11)
  #define  ACCESS_TMC        ((uint32)0x1 << 12)
  #define  ACCESS_GTM        ((uint32)0x1 << 13)
  #define  ACCESS_DME        ((uint32)0x1 << 14)
  #define  ACCESS_DSPH       ((uint32)0x1 << 15)
  #define  ACCESS_DFA        ((uint32)0x1 << 16)
  #define  ACCESS_Cluster0_0 ((uint32)0x1 << 17)
  #define  ACCESS_Cluster0_1 ((uint32)0x1 << 18)
  #define  ACCESS_Cluster0_2 ((uint32)0x1 << 19)
  #define  ACCESS_Cluster0_3 ((uint32)0x1 << 20)
  #define  ACCESS_Cluster1_0 ((uint32)0x1 << 21)
  #define  ACCESS_Cluster1_1 ((uint32)0x1 << 22)
  #define  ACCESS_Cluster1_2 ((uint32)0x1 << 23)
  #define  ACCESS_Cluster1_3 ((uint32)0x1 << 24)
  #define  ACCESS_Cluster2_0 ((uint32)0x1 << 25)
  #define  ACCESS_Cluster2_1 ((uint32)0x1 << 26)
  #define  ACCESS_Cluster2_2 ((uint32)0x1 << 27)
  #define  ACCESS_Cluster2_3 ((uint32)0x1 << 28)
  #define  ACCESS_HSM        ((uint32)0x1 << 29)

  /*                                                                 Access Mask,         MasterID (HW)           */
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_DAP0       = {ACCESS_DAP0,         RBSYS_NOCMasterID_DAP0 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_DAP1       = {ACCESS_DAP1,         RBSYS_NOCMasterID_DAP1 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Flexray0   = {ACCESS_FR0,          RBSYS_NOCMasterID_Flexray0 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Flexray1   = {ACCESS_FR1,          RBSYS_NOCMasterID_Flexray1 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Ether0     = {ACCESS_ETH0,         RBSYS_NOCMasterID_Ether0 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Ether1     = {ACCESS_ETH1,         RBSYS_NOCMasterID_Ether1 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_eDMA0      = {ACCESS_eDMA0,        RBSYS_NOCMasterID_eDMA0 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_eDMA1      = {ACCESS_eDMA1,        RBSYS_NOCMasterID_eDMA1 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_eDMA2      = {ACCESS_eDMA2,        RBSYS_NOCMasterID_eDMA2 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_eDMA3      = {ACCESS_eDMA3,        RBSYS_NOCMasterID_eDMA3 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_ZIP0       = {ACCESS_ZIP0,         RBSYS_NOCMasterID_ZipW0 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_ZIP1       = {ACCESS_ZIP1,         RBSYS_NOCMasterID_ZipW1 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_TMC        = {ACCESS_TMC ,         RBSYS_NOCMasterID_TMC };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_GTM        = {ACCESS_GTM ,         RBSYS_NOCMasterID_GTM };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_DME        = {ACCESS_DME ,         RBSYS_NOCMasterID_DME };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_DSPH       = {ACCESS_DSPH,         RBSYS_NOCMasterID_DSPH };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_DFA        = {ACCESS_DFA ,         RBSYS_NOCMasterID_DFA };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Cluster0_0 = {ACCESS_Cluster0_0,   RBSYS_NOCMasterID_Cluster0_Port0 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Cluster0_1 = {ACCESS_Cluster0_1,   RBSYS_NOCMasterID_Cluster0_Port1 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Cluster0_2 = {ACCESS_Cluster0_2,   RBSYS_NOCMasterID_Cluster0_Port2 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Cluster0_3 = {ACCESS_Cluster0_3,   RBSYS_NOCMasterID_Cluster0_Port3 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Cluster1_0 = {ACCESS_Cluster1_0,   RBSYS_NOCMasterID_Cluster1_Port0 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Cluster1_1 = {ACCESS_Cluster1_1,   RBSYS_NOCMasterID_Cluster1_Port1 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Cluster1_2 = {ACCESS_Cluster1_2,   RBSYS_NOCMasterID_Cluster1_Port2 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Cluster1_3 = {ACCESS_Cluster1_3,   RBSYS_NOCMasterID_Cluster1_Port3 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Cluster2_0 = {ACCESS_Cluster2_0,   RBSYS_NOCMasterID_Cluster2_Port0 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Cluster2_1 = {ACCESS_Cluster2_1,   RBSYS_NOCMasterID_Cluster2_Port1 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Cluster2_2 = {ACCESS_Cluster2_2,   RBSYS_NOCMasterID_Cluster2_Port2 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_Cluster2_3 = {ACCESS_Cluster2_3,   RBSYS_NOCMasterID_Cluster2_Port3 };
  static const RBSYS_NOCInitiator_t RBSYS_NOCInitiator_HSM        = {ACCESS_HSM,          RBSYS_NOCMasterID_HSM };
  #define RBSYS_NOCInitiator_NumOfInitiators (30)

  static_assert(RBSYS_NOCInitiator_NumOfInitiators <= 32, "Too many initiators for connectivity matrix!");



  typedef struct
  {
    volatile rba_Reg_FIREWALL_tst * fwPtr;
    uint32                          ConnectedNOCInitiators;
    uint32                          numOfFirewallRegions;
  } RBSYS_NOCTarget_t;

  /*                                                                  FIREWALL-Pointer,     List of connected Initiators,                                                                                                                                                                                                                                                                                                                                                                                                                                                               Number of Firewall channels                                                                                                                                                                                                                                                                                            , Number of Regions for Firewall */
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_GTM              = { &GTM_FIREWALL,        (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 |                                                       ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 8 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_AIPS0            = { &AIPS0_FIREWALL,      (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 | ACCESS_ZIP0 | ACCESS_ZIP1 |              ACCESS_GTM | ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 1 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_AIPS1            = { &AIPS1_FIREWALL,      (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 | ACCESS_ZIP0 | ACCESS_ZIP1 |              ACCESS_GTM | ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 1 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_AIPS2            = { &AIPS2_FIREWALL,      (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 | ACCESS_ZIP0 | ACCESS_ZIP1 |              ACCESS_GTM | ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 1 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_AIPS3            = { &AIPS3_FIREWALL,      (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 | ACCESS_ZIP0 | ACCESS_ZIP1 |              ACCESS_GTM | ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 1 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_AIPS4            = { &AIPS4_FIREWALL,      (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 | ACCESS_ZIP0 | ACCESS_ZIP1 |              ACCESS_GTM | ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 1 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_DAP              = { &DAP_FIREWALL,        (                                                                    ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 | ACCESS_ZIP0 | ACCESS_ZIP1 |                           ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 1 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_SYSRAM0          = { &SYSRAM0_FIREWALL,    (ACCESS_DAP0 | ACCESS_DAP1 | ACCESS_FR0 | ACCESS_FR1 | ACCESS_ETH0 | ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 | ACCESS_ZIP0 | ACCESS_ZIP1 | ACCESS_TMC | ACCESS_GTM | ACCESS_DME | ACCESS_DSPH | ACCESS_DFA | ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 8 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_SYSRAM1          = { &SYSRAM1_FIREWALL,    (ACCESS_DAP0 | ACCESS_DAP1 | ACCESS_FR0 | ACCESS_FR1 | ACCESS_ETH0 | ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 | ACCESS_ZIP0 | ACCESS_ZIP1 | ACCESS_TMC | ACCESS_GTM | ACCESS_DME | ACCESS_DSPH | ACCESS_DFA | ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 8 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_DME              = { &DME_FIREWALL,        (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 |                                                                    ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 2 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_DSPH             = { &DSPH_FIREWALL,       (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 | ACCESS_ZIP0 | ACCESS_ZIP1 |              ACCESS_GTM | ACCESS_DME |                            ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 2 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_AESLIGHT0        = { &AESLIGHT0_FIREWALL,  (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 |                                                       ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 1 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_AESLIGHT1        = { &AESLIGHT1_FIREWALL,  (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 |                                                       ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 1 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_AESLIGHT2        = { &AESLIGHT2_FIREWALL,  (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 |                                                       ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 1 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_AESLIGHT3        = { &AESLIGHT3_FIREWALL,  (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 |                                                       ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 1 };
  /* Firewalls: no configurable NOC firewall */
  //static const RBSYS_NOCTarget_t RBSYS_NOCTarget_FirewallConfig   = { &FIREWALL_FIREWALL,   (ACCESS_DAP0 | ACCESS_DAP1 |                                                                                                                                                                                                   ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1                                                      , 2 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_Cluster0Backdoor = { &KITE0_FIREWALL,      (ACCESS_DAP0 | ACCESS_DAP1 | ACCESS_FR0 | ACCESS_FR1 | ACCESS_ETH0 | ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 | ACCESS_ZIP0 | ACCESS_ZIP1 |              ACCESS_GTM | ACCESS_DME | ACCESS_DSPH | ACCESS_DFA |                                                                                 ACCESS_Cluster1_0 | ACCESS_Cluster1_1 | ACCESS_Cluster1_2 | ACCESS_Cluster1_3 | ACCESS_Cluster2_0 | ACCESS_Cluster2_1 | ACCESS_Cluster2_2 | ACCESS_Cluster2_3 | ACCESS_HSM), 8 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_DFA              = { &DFA_FIREWALL,        (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 |                                          ACCESS_GTM | ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 2 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_NVMWR            = { &NVM_FIREWALL,        (ACCESS_DAP0 | ACCESS_DAP1 |                                                                                                                                                           ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 4 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_TMC0             = { &TMC0_FIREWALL,       (                                                                                                                                                            ACCESS_TMC),                                                                                                                                                                                                                                                                                                                   2 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_Cluster1Backdoor = { &KITE1_FIREWALL,      (ACCESS_DAP0 | ACCESS_DAP1 | ACCESS_FR0 | ACCESS_FR1 | ACCESS_ETH0 | ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 | ACCESS_ZIP0 | ACCESS_ZIP1 |              ACCESS_GTM | ACCESS_DME | ACCESS_DSPH | ACCESS_DFA | ACCESS_Cluster0_0 | ACCESS_Cluster0_1 | ACCESS_Cluster0_2 | ACCESS_Cluster0_3 |                                                                                 ACCESS_Cluster2_0 | ACCESS_Cluster2_1 | ACCESS_Cluster2_2 | ACCESS_Cluster2_3 | ACCESS_HSM), 8 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_TMC1             = { &TMC1_FIREWALL,       (                                                                                                                                                            ACCESS_TMC),                                                                                                                                                                                                                                                                                                                   2 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_Cluster2Backdoor = { &KITE2_FIREWALL,      (ACCESS_DAP0 | ACCESS_DAP1 | ACCESS_FR0 | ACCESS_FR1 | ACCESS_ETH0 | ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 | ACCESS_ZIP0 | ACCESS_ZIP1 |              ACCESS_GTM | ACCESS_DME | ACCESS_DSPH | ACCESS_DFA | ACCESS_Cluster0_0 | ACCESS_Cluster0_1 | ACCESS_Cluster0_2 | ACCESS_Cluster0_3 | ACCESS_Cluster1_0 | ACCESS_Cluster1_1 | ACCESS_Cluster1_2 | ACCESS_Cluster1_3 |                                                                                 ACCESS_HSM), 8 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_TMC2             = { &TMC2_FIREWALL,       (                                                                                                                                                            ACCESS_TMC),                                                                                                                                                                                                                                                                                                                   2 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_HSM              = { &HSM_FIREWALL,        (ACCESS_DAP0 | ACCESS_DAP1 |                                         ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 |                                                       ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1),                                                      2 };
  static const RBSYS_NOCTarget_t RBSYS_NOCTarget_OCTOSPI          = { &OCT_SPI_FIREWALL,    (ACCESS_DAP0 | ACCESS_DAP1 |                           ACCESS_ETH0 | ACCESS_eDMA0 | ACCESS_eDMA1 | ACCESS_eDMA2 | ACCESS_eDMA3 |                                                       ACCESS_DME | ACCESS_DSPH |              ACCESS_Cluster0_0 | ACCESS_Cluster0_1 |                                         ACCESS_Cluster1_0 | ACCESS_Cluster1_1 |                                         ACCESS_Cluster2_0 | ACCESS_Cluster2_1 |                                         ACCESS_HSM), 4 };


  static boolean rbsys_IsMasterConnected2Target(const RBSYS_NOCTarget_t* target, const RBSYS_NOCInitiator_t* initiator)
  {
    /* check if Initiator.AccessMask is in list of connected Initiators (BitMask) */
    return ( ( target->ConnectedNOCInitiators & initiator->AccessMask ) != 0 );
  }

  typedef enum
  {
    RBSYS_NOCRegionType_ClusterCodeFlash,
    RBSYS_NOCRegionType_ClusterMemorySafeOnly,
    RBSYS_NOCRegionType_ClusterMemorySafeAndSecure,
    RBSYS_NOCRegionType_ClusterMemorySafeAndUnsafe,
    RBSYS_NOCRegionType_OtherMemorySafeOnly,
    RBSYS_NOCRegionType_OtherMemorySafeAndUnsafe,
    RBSYS_NOCRegionType_Unused
  } RBSYS_NOCRegionType_n;

  typedef struct
  {
    uint32 StartAddr;
    uint32 Size;
    RBSYS_NOCRegionType_n RegionType;
  } RBSYS_NOCFirewallRegionConfig_t;

  typedef struct
  {
    const RBSYS_NOCFirewallRegionConfig_t* regions;
    const RBSYS_NOCTarget_t* target;
    uint32 numRegions;
  } RBSYS_NOCFirewallConfig_t;

  #define RBSYS_NOCFirewallCfg(name, target) static const RBSYS_NOCFirewallConfig_t rbsys_##name##_Firewall = {rbsys_##name##_FirewallRegions, &target, (sizeof(rbsys_##name##_FirewallRegions)/sizeof(RBSYS_NOCFirewallRegionConfig_t)) }


  /* ---------------- Cluster and RAM Guard configuration ---------------- */
  /* Cluster 1 Address Space: CRAM0_1 partially shared with UNSAFE ans SECURE Bus Masters */
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_Cluster0_FirewallRegions[] = {
                                  /* Region 0: From 0x0000 To NVM_0_1_END */
                                  { RBSYS_Cluster0_REGION_0_START, RBSYS_Cluster0_REGION_0_SIZE,  RBSYS_NOCRegionType_ClusterCodeFlash },

                                  /* Region 1: From NVM_0_1_END To Special Areas */
                                  { RBSYS_Cluster0_REGION_1_START, RBSYS_Cluster0_REGION_1_SIZE,  RBSYS_NOCRegionType_ClusterMemorySafeOnly },

                                  /* Region 2: 32/64/96/128K Ethernet Shared RAM */
                                  #if( RBFS_SysEthSharedGRAMsize != RBFS_SysEthSharedGRAMsize_0K )
                                    { RBSYS_EthernetSharedGRAMStartAddress, RBSYS_EthernetSharedGRAMSize, RBSYS_NOCRegionType_ClusterMemorySafeAndUnsafe },
                                  #endif

                                  /* Region 3: 16/32/64K Restricted Exclusive RAM */
                                  #if (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K)
                                    { RBSYS_RestrictedExclusiveGRAMStartAddress, RBSYS_RestrictedExclusiveGRAMSize, RBSYS_NOCRegionType_ClusterMemorySafeOnly },
                                  #endif

                                  /* Region 4: 16/32K HSM RAM Shared with SAFE xor Restricted Host */
                                  #if( RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K )
                                    #if( RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Host )
                                      { RBSYS_HsmSharedGRAMStartAddress, RBSYS_HsmSharedGRAMSize, RBSYS_NOCRegionType_ClusterMemorySafeAndSecure },
                                    #else
                                      { RBSYS_HsmSharedGRAMStartAddress, RBSYS_HsmSharedGRAMSize, RBSYS_NOCRegionType_ClusterMemorySafeAndSecure },
                                      #warning("Restricted Exclusive GRAM is not supported yet.")
                                    #endif
                                  #endif

                                  /* Region 5: Remaining memory space*/
                                  { RBSYS_Cluster0_REGION_LAST_START, RBSYS_Cluster0_REGION_LAST_SIZE, RBSYS_NOCRegionType_ClusterMemorySafeOnly },
                                };
  RBSYS_NOCFirewallCfg(Cluster0, RBSYS_NOCTarget_Cluster0Backdoor);

  /** In fact, the following regions do not cover address space 0xFFFFFFC0 - 0xFFFFFFFF. But as no module is mapped to
    * this address space, no firewall will receive the request anyways. */
  #define RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RegionType) {{ 0x00000000u, 0xFFFFFFC0u,  RegionType }}


  /* Cluster 1 Address Space (No special areas, cover full address space)  */
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_Cluster1_FirewallRegions[] = {
    /* Region 0: From 0x00000000 to NVM_0_1_End */
    { RBSYS_Cluster1_REGION_0_START, RBSYS_Cluster1_REGION_0_SIZE, RBSYS_NOCRegionType_ClusterCodeFlash },
    /* Region 1: Remaining memory space */
    { RBSYS_Cluster1_REGION_1_START, RBSYS_Cluster1_REGION_1_SIZE, RBSYS_NOCRegionType_ClusterMemorySafeOnly }
  };
  RBSYS_NOCFirewallCfg(Cluster1, RBSYS_NOCTarget_Cluster1Backdoor);

  /* Cluster 2 Address Space (No special areas, cover full address space)  */
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_Cluster2_FirewallRegions[] = {
    /* Region 0: From 0x00000000 to NVM_0_1_End */
    { RBSYS_Cluster2_REGION_0_START, RBSYS_Cluster2_REGION_0_SIZE, RBSYS_NOCRegionType_ClusterCodeFlash },
    /* Region 1: Remaining memory space */
    { RBSYS_Cluster2_REGION_1_START, RBSYS_Cluster2_REGION_1_SIZE, RBSYS_NOCRegionType_ClusterMemorySafeOnly }
  };
  RBSYS_NOCFirewallCfg(Cluster2, RBSYS_NOCTarget_Cluster2Backdoor);

  /* SYSRAM_0 */
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_SYSRAM0_FirewallRegions[]  = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  RBSYS_NOCFirewallCfg(SYSRAM0, RBSYS_NOCTarget_SYSRAM0);

  /* SYSRAM_1 */
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_SYSRAM1_FirewallRegions[]  = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  RBSYS_NOCFirewallCfg(SYSRAM1, RBSYS_NOCTarget_SYSRAM1);


  /* AESLIGHT Engines (accessed by Host only) */
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_AESLIGHT0_FirewallRegions[] = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_AESLIGHT1_FirewallRegions[] = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_AESLIGHT2_FirewallRegions[] = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_AESLIGHT3_FirewallRegions[] = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  RBSYS_NOCFirewallCfg(AESLIGHT0, RBSYS_NOCTarget_AESLIGHT0);
  RBSYS_NOCFirewallCfg(AESLIGHT1, RBSYS_NOCTarget_AESLIGHT1);
  RBSYS_NOCFirewallCfg(AESLIGHT2, RBSYS_NOCTarget_AESLIGHT2);
  RBSYS_NOCFirewallCfg(AESLIGHT3, RBSYS_NOCTarget_AESLIGHT3);

  /* DSP_H (accessed by Host only) */
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_DSPH_FirewallRegions[] = { {0x00000000u, 0xFFFFFFC0u,  RBSYS_NOCRegionType_OtherMemorySafeOnly } };
  RBSYS_NOCFirewallCfg(DSPH, RBSYS_NOCTarget_DSPH);

  /* GTM (accessed by Host only) */
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_GTM_FirewallRegions[] = { {0x00000000u, 0xFFFFFFC0u,  RBSYS_NOCRegionType_OtherMemorySafeOnly } };
  RBSYS_NOCFirewallCfg(GTM, RBSYS_NOCTarget_GTM);

  /* AIPS 0-4 Address Space (accessed by Host only, to be checked if Unsafe/Secure Masters require access) */
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_AIPS0_FirewallRegions[]  = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_AIPS1_FirewallRegions[]  = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_AIPS2_FirewallRegions[]  = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_AIPS3_FirewallRegions[]  = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_AIPS4_FirewallRegions[]  = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  RBSYS_NOCFirewallCfg(AIPS0, RBSYS_NOCTarget_AIPS0);
  RBSYS_NOCFirewallCfg(AIPS1, RBSYS_NOCTarget_AIPS1);
  RBSYS_NOCFirewallCfg(AIPS2, RBSYS_NOCTarget_AIPS2);
  RBSYS_NOCFirewallCfg(AIPS3, RBSYS_NOCTarget_AIPS3);
  #warning("AIPS4 is missing the connectivity matrix of P6")
  RBSYS_NOCFirewallCfg(AIPS4, RBSYS_NOCTarget_AIPS4);

  /* Todo: Several modules may need access to certain sections of the AIPS0-4. Check necessity once users are available. */

  /* HSM Address Space (Host-HSM-Bridge is controlled by Host only) -> todo: check if these are bridge registers only and access of SAFE is fine */
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_HSM_FirewallRegions[] =  RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  RBSYS_NOCFirewallCfg(HSM, RBSYS_NOCTarget_HSM);

  /* Host NVM Write Port (accessed by Host only) */
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_NVM_FirewallRegions[] =  RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeOnly);
  RBSYS_NOCFirewallCfg(NVM, RBSYS_NOCTarget_NVMWR);

  /* Unused Peripheral Modules -> access removed */
  // static const RBSYS_NOCFirewallRegionConfig_t rbsys_PCIE0_FirewallRegions[]       = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_Unused); // PCIe0 is not used //< not supported on P6, do not configure as envelope strategy
  // static const RBSYS_NOCFirewallRegionConfig_t rbsys_PCIE0_CFG_FirewallRegions[]   = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_Unused); // PCIe0 is not used //< not supported on P6, do not configure as envelope strategy
  // static const RBSYS_NOCFirewallRegionConfig_t rbsys_PCIE1_FirewallRegions[]       = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_Unused); // PCIe1 is not used //< not supported on P6, do not configure as envelope strategy
  // static const RBSYS_NOCFirewallRegionConfig_t rbsys_PCIE1_CFG_FirewallRegions[]   = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_Unused); // PCIe1 is not used //< not supported on P6, do not configure as envelope strategy
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_TMC0_FirewallRegions[]       = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_Unused); // Trace Control Modules are only configured by external Debugger
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_TMC1_FirewallRegions[]       = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_Unused); // Trace Control Modules are only configured by external Debugger
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_TMC2_FirewallRegions[]       = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_Unused); // Trace Control Modules are only configured by external Debugger
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_OCTOSPI_FirewallRegions[]    = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_Unused); // OctoSPI is not used
  // static const RBSYS_NOCFirewallRegionConfig_t rbsys_SDMMC_FirewallRegions[]       = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_Unused); // SDMMC is not used //< not supported on P6, do not configure as envelope strategy
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_DAP_FirewallRegions[]        = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_Unused); // Debug Access Port is only used by external Debugger
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_DFA_FirewallRegions[]        = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_Unused); // Data Flow Architecture is not used
  static const RBSYS_NOCFirewallRegionConfig_t rbsys_DME_FirewallRegions[]        = RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_Unused); // Data Move Engine is not used at the moment
  // RBSYS_NOCFirewallCfg(PCIE0,      &PCIE0_FIREWALL);
  // RBSYS_NOCFirewallCfg(PCIE0_CFG,  &PCIE0_CFG_FIREWALL);
  // RBSYS_NOCFirewallCfg(PCIE1,      &PCIE1_FIREWALL);
  // RBSYS_NOCFirewallCfg(PCIE1_CFG,  &PCIE1_CFG_FIREWALL);
  RBSYS_NOCFirewallCfg(TMC0,       RBSYS_NOCTarget_TMC0);
  RBSYS_NOCFirewallCfg(TMC1,       RBSYS_NOCTarget_TMC1);
  RBSYS_NOCFirewallCfg(TMC2,       RBSYS_NOCTarget_TMC2);
  RBSYS_NOCFirewallCfg(OCTOSPI,    RBSYS_NOCTarget_OCTOSPI);
  // RBSYS_NOCFirewallCfg(SDMMC,      &SDMMC);
  RBSYS_NOCFirewallCfg(DAP,        RBSYS_NOCTarget_DAP);
  RBSYS_NOCFirewallCfg(DFA,        RBSYS_NOCTarget_DFA);
  RBSYS_NOCFirewallCfg(DME,        RBSYS_NOCTarget_DME);



  static const RBSYS_NOCFirewallConfig_t* const rbsys_AllNOCFirewallsIndexed[] = 
  {
    /* These indices must correspond to the NOC firewall instance indices (see RM0496 Rev 2 p.171) */
    /* 0*/ &rbsys_AESLIGHT0_Firewall,
    /* 1*/ &rbsys_AESLIGHT1_Firewall,
    /* 2*/ &rbsys_AESLIGHT2_Firewall,
    /* 3*/ &rbsys_AESLIGHT3_Firewall,
    /* 4*/ &rbsys_AIPS0_Firewall,
    /* 5*/ &rbsys_AIPS1_Firewall,
    /* 6*/ &rbsys_AIPS2_Firewall,
    /* 7*/ &rbsys_AIPS3_Firewall,
    /* 8*/ &rbsys_AIPS4_Firewall,
    /* 9*/ &rbsys_DAP_Firewall,
    /*10*/ &rbsys_DFA_Firewall,
    /*11*/ &rbsys_DME_Firewall,
    /*12*/ &rbsys_DSPH_Firewall,
    /*13*/ &rbsys_GTM_Firewall,
    /*14*/ &rbsys_HSM_Firewall,
    /*15*/ &rbsys_Cluster0_Firewall,
    /*16*/ &rbsys_Cluster1_Firewall,
    /*17*/ &rbsys_Cluster2_Firewall,
    /*18*/ NULL_PTR, // Firewall for NOC configuration registers (todo: check if this exists)
    /*19*/ &rbsys_NVM_Firewall,
    /*20*/ &rbsys_OCTOSPI_Firewall,
    /*21*/ NULL_PTR, // no firewall implemented
    /*22*/ NULL_PTR, // no firewall implemented
    /*23*/ NULL_PTR, // no firewall implemented
    /*24*/ NULL_PTR, // no firewall implemented
    /*25*/ NULL_PTR, // no firewall implemented
    /*26*/ &rbsys_SYSRAM0_Firewall,
    /*27*/ &rbsys_SYSRAM1_Firewall,
    /*28*/ &rbsys_TMC0_Firewall,
    /*29*/ &rbsys_TMC1_Firewall,
    /*30*/ &rbsys_TMC2_Firewall,
  };
  static const uint32 rbsys_AllNOCFirewallsIndexed_MaxIndex = sizeof(rbsys_AllNOCFirewallsIndexed) / sizeof(rbsys_AllNOCFirewallsIndexed[0]);
  


  RBSYS_SystemMPU_FailureType_t RBSYS_GetSystemMpuFailure(uint32 NocFirewallId, RBSYS_SystemMPUPrivilegeLevel_t exceptionLevel, RBSYS_SystemMPU_AccessViolation_t* AccessViolation /*out*/)
  {
    RBSYS_SystemMPU_FailureType_t result = RBSYS_SystemMPU_FailureType_APIMisuse;

    if( NocFirewallId < rbsys_AllNOCFirewallsIndexed_MaxIndex)
    {
      const RBSYS_NOCFirewallConfig_t* const fwConf = rbsys_AllNOCFirewallsIndexed[NocFirewallId];

      if( fwConf != NULL_PTR )
      {
        volatile rba_Reg_FIREWALL_tst * fwPtr = fwConf->target->fwPtr;
        result = RBSYS_SystemMPU_FailureType_Undefined; // No Active Failure in this Firewall

        RBSYS_SwitchSVToHV();

        switch( exceptionLevel )
        {
          case RBSYS_SystemMPUPrivilegeLevel_EL01:
            if( fwPtr->FW_EL1_ERROR_TYPE_STATUS != 0 )
            {
              AccessViolation->StatusRegister = fwPtr->FW_EL1_ERROR_TYPE_STATUS;
              AccessViolation->InitiatorId =    fwPtr->FW_EL1_ERROR_ID_STATUS;
              AccessViolation->Address =        fwPtr->FW_EL1_ERROR_ADDR_STATUS;
              result = RBSYS_SystemMPU_FailureType_FirewallError; // Active Failure in EL1 Firewall
            }
          break;
          case RBSYS_SystemMPUPrivilegeLevel_EL2:
            if( fwPtr->FW_EL2_ERROR_TYPE_STATUS != 0 )
            {
              AccessViolation->StatusRegister = fwPtr->FW_EL2_ERROR_TYPE_STATUS;
              AccessViolation->InitiatorId =    fwPtr->FW_EL2_ERROR_ID_STATUS;
              AccessViolation->Address =        fwPtr->FW_EL2_ERROR_ADDR_STATUS;
              result = RBSYS_SystemMPU_FailureType_FirewallError; // Active Failure in EL2 Firewall
            }
            break;
          default:
              // assert(0); --> avoid assert here to lower the amount of code executed in HV mode
          break;
        }

        RBSYS_SwitchHVToSV();
      }
    }

    return result;
  }

  void RBSYS_GenerateSystemMpuFailureDebugData(RBSYS_SystemMPU_AccessViolation_t* violation, uint32* debug0, uint32* debug1)
  {
    uint32 masterID_6bit =   (violation->InitiatorId    & 0x00007E00) >> 9;
    uint32 masterVMID_9bit = (violation->InitiatorId    & 0x000001FF) >> 0;
    uint32 status_9bit =     (violation->StatusRegister & 0x000001FF) >> 0;
    *debug0 = (masterID_6bit << 24) | (masterVMID_9bit << 12) | (status_9bit << 0);
    *debug1 = violation->Address;
  }

  void RBSYS_ClearAllFirewallStatusRegisters(void)
  {
    uint32 i;

    RBSYS_SwitchSVToHV();

    for( i=0; i<rbsys_AllNOCFirewallsIndexed_MaxIndex; i++ )
    {
      const RBSYS_NOCFirewallConfig_t* const fwConf = rbsys_AllNOCFirewallsIndexed[i];

      if( fwConf != NULL_PTR )
      {
        volatile rba_Reg_FIREWALL_tst * fwPtr = fwConf->target->fwPtr;

        fwPtr->FW_ERROR_STATUS = 0x00000001u; //< write 1 clears all
        /* todo: RM mentions "2. Check and clear mission fault registers" -> clarify what has to be done here */
      }
    }

    RBSYS_SwitchHVToSV();
  }



  /** @short Helper function to avoid writing non-available registers (see "attention" below) */
  static void rbsys_ConfigureFirewallMasterPermission(const RBSYS_NOCTarget_t* NOCTarget,
                                                      const RBSYS_NOCInitiator_t* NOCInitiator,
                                                      uint32 regionIdx,
                                                      uint32 masterPermission)
  {
    /* Attention: NOC Firewall registers do not exist, if the Master is not connected to the Slave! */
    if( rbsys_IsMasterConnected2Target(NOCTarget, NOCInitiator) )
    {
      NOCTarget->fwPtr->EL1_MSTR[regionIdx][NOCInitiator->MasterID] = masterPermission;
    }
  }


  /** @short Configure FlexNOC Firewall with predefined setting
    *
    * @param configuration Predefined firewall config
    */
  static void rbsys_NOCFirewallConfigure(const RBSYS_NOCFirewallConfig_t* configuration)
  {
    uint32 currentRegion;

    const RBSYS_NOCTarget_t* target = configuration->target;

    volatile rba_Reg_FIREWALL_tst * fwPtr = target->fwPtr;

    /* Disable Firewall */
    fwPtr->FW_CONFIG_REG = RBSYS_FIREWALL_CONFIG_DISABLE;
    // while( fwPtr->FW_CONFIG_REG != RBSYS_FIREWALL_CONFIG_DISABLE ){}

    /* EL2-Mode is not used at the moment, therefore ignored right now */
    fwPtr->FW_EL2_CONFIG_REG = RBSYS_FIREWALL_EL2_CONF_DISABLE;

    /* Disable EL1 Checks */
    fwPtr->FW_EL1_CONFIG_REG = RBSYS_FIREWALL_EL1_CONF_DISABLE;
    // while( fwPtr->FW_EL1_CONFIG_REG != RBSYS_FIREWALL_EL1_CONF_DISABLE ){}

    assert( configuration->numRegions <= target->numOfFirewallRegions ); //< ensure that number of region configurations is <= number of regions

    // Enable configured regions
    for( currentRegion = 0; currentRegion < configuration->numRegions; currentRegion++ )
    {
      RBSYS_NOCRegionType_n regionType;
      uint32 mstrAccess_KITE_AXIM = 0, mstrAccess_KITE_AXIF = 0, mstrAccess_SAFE, mstrAccess_SECURE, mstrAccess_UNSAFE;

      /* Disable Region */
      fwPtr->EL1_REG[currentRegion].CONF = RBSYS_FIREWALL_EL1_CONF_DISABLE;
      // while( fwPtr->EL1_REG[currentRegion].CONF != RBSYS_FIREWALL_EL1_CONF_DISABLE ){}

      /* Configure Permission Settings */
      regionType = configuration->regions[currentRegion].RegionType;

      switch(regionType)
      {
        case RBSYS_NOCRegionType_ClusterCodeFlash:
          mstrAccess_KITE_AXIM  = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          mstrAccess_KITE_AXIF  = RBSYS_FIREWALL_EL1_MSTRACC_RX;
          mstrAccess_SAFE       = RBSYS_FIREWALL_EL1_MSTRACC_R;
          mstrAccess_SECURE     = RBSYS_FIREWALL_EL1_MSTRACC_R;
          mstrAccess_UNSAFE     = RBSYS_FIREWALL_EL1_MSTRACC_R;
          break;
        case RBSYS_NOCRegionType_ClusterMemorySafeOnly:
          mstrAccess_KITE_AXIM  = RBSYS_FIREWALL_EL1_MSTRACC_RW;
          mstrAccess_KITE_AXIF  = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          mstrAccess_SAFE       = RBSYS_FIREWALL_EL1_MSTRACC_RW;
          mstrAccess_SECURE     = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          mstrAccess_UNSAFE     = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          break;
        case RBSYS_NOCRegionType_ClusterMemorySafeAndSecure:
          mstrAccess_KITE_AXIM  = RBSYS_FIREWALL_EL1_MSTRACC_RW;
          mstrAccess_KITE_AXIF  = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          mstrAccess_SAFE       = RBSYS_FIREWALL_EL1_MSTRACC_RW;
          mstrAccess_SECURE     = RBSYS_FIREWALL_EL1_MSTRACC_RW;
          mstrAccess_UNSAFE     = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          break;
        case RBSYS_NOCRegionType_ClusterMemorySafeAndUnsafe:
          mstrAccess_KITE_AXIM  = RBSYS_FIREWALL_EL1_MSTRACC_RW;
          mstrAccess_KITE_AXIF  = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          mstrAccess_SAFE       = RBSYS_FIREWALL_EL1_MSTRACC_RW;
          mstrAccess_SECURE     = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          mstrAccess_UNSAFE     = RBSYS_FIREWALL_EL1_MSTRACC_RW;
          break;
        case RBSYS_NOCRegionType_OtherMemorySafeOnly:
          mstrAccess_KITE_AXIM  = RBSYS_FIREWALL_EL1_MSTRACC_RW;
          mstrAccess_KITE_AXIF  = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          mstrAccess_SAFE       = RBSYS_FIREWALL_EL1_MSTRACC_RW;
          mstrAccess_SECURE     = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          mstrAccess_UNSAFE     = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          break;
        // not used yet - commented out because of missing UT coverage
        // case RBSYS_NOCRegionType_OtherMemorySafeAndUnsafe:
        //   mstrAccess_KITE_AXIM  = RBSYS_FIREWALL_EL1_MSTRACC_RW;
        //   mstrAccess_KITE_AXIF  = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
        //   mstrAccess_SAFE       = RBSYS_FIREWALL_EL1_MSTRACC_RW;
        //   mstrAccess_SECURE     = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
        //   mstrAccess_UNSAFE     = RBSYS_FIREWALL_EL1_MSTRACC_RW;
        //   break;
        case RBSYS_NOCRegionType_Unused:
          mstrAccess_KITE_AXIM  = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          mstrAccess_KITE_AXIF  = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          mstrAccess_SAFE       = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          mstrAccess_SECURE     = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          mstrAccess_UNSAFE     = RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED;
          break;
        default:
          assert(0);
          break;
      }



      // Accesses from Cluster 0
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Cluster0_0, currentRegion, mstrAccess_KITE_AXIM); // Core 0 AXIM Port
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Cluster0_1, currentRegion, mstrAccess_KITE_AXIM); // Core 1 AXIM Port
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Cluster0_2, currentRegion, mstrAccess_KITE_AXIF); // Core 0 AXIF Port
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Cluster0_3, currentRegion, mstrAccess_KITE_AXIF); // Core 1 AXIF Port

      // Accesses from Cluster 1
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Cluster1_0, currentRegion, mstrAccess_KITE_AXIM); // Core 2 AXIM Port
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Cluster1_1, currentRegion, mstrAccess_KITE_AXIM); // Core 3 AXIM Port
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Cluster1_2, currentRegion, mstrAccess_KITE_AXIF); // Core 2 AXIF Port
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Cluster1_3, currentRegion, mstrAccess_KITE_AXIF); // Core 3 AXIF Port

      // Accesses from Cluster 2
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Cluster2_0, currentRegion, mstrAccess_KITE_AXIM); // Core 4 AXIM Port
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Cluster2_1, currentRegion, mstrAccess_KITE_AXIM); // Core 5 AXIM Port
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Cluster2_2, currentRegion, mstrAccess_KITE_AXIF); // Core 4 AXIF Port
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Cluster2_3, currentRegion, mstrAccess_KITE_AXIF); // Core 5 AXIF Port

      // Other SAFE Busmasters
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_eDMA0, currentRegion, mstrAccess_SAFE);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_eDMA1, currentRegion, mstrAccess_SAFE);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_eDMA2, currentRegion, mstrAccess_SAFE);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_eDMA3, currentRegion, mstrAccess_SAFE);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_DME,   currentRegion, mstrAccess_SAFE);

      // Other SECURE Busmasters
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_HSM,   currentRegion, mstrAccess_SECURE);

      // Other UNSAFE Busmasters
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Ether0,   currentRegion, mstrAccess_UNSAFE);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_DSPH,     currentRegion, mstrAccess_UNSAFE);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Flexray0, currentRegion, mstrAccess_UNSAFE);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_Flexray1, currentRegion, mstrAccess_UNSAFE);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_GTM,      currentRegion, mstrAccess_UNSAFE);

      // Generally Blocked Busmasters
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_DAP0,  currentRegion, RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_DAP1,  currentRegion, RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_ZIP0,  currentRegion, RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_ZIP1,  currentRegion, RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_TMC,   currentRegion, RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED);
      rbsys_ConfigureFirewallMasterPermission(target, &RBSYS_NOCInitiator_DFA,   currentRegion, RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED);

      /* Configure Start / End address */
      fwPtr->EL1_REG[currentRegion].ADDR_START  = configuration->regions[currentRegion].StartAddr;
      fwPtr->EL1_REG[currentRegion].ADDR_SIZE   = configuration->regions[currentRegion].Size;

      /* Enable Region */
      fwPtr->EL1_REG[currentRegion].CONF        = RBSYS_FIREWALL_EL1_CONF_ENABLE;
    } //< loop regions

    // Disable remaining regions
    currentRegion = configuration->numRegions; //< e.g. start from index 3 if 3 regions are used
    for(; currentRegion < target->numOfFirewallRegions; currentRegion++ )
    {
      fwPtr->EL1_REG[currentRegion].CONF = RBSYS_FIREWALL_EL1_CONF_DISABLE;
    }

    fwPtr->FW_EL1_CONFIG_REG = RBSYS_FIREWALL_EL1_CONF_ENABLE;
    fwPtr->FW_CONFIG_REG = RBSYS_FIREWALL_CONFIG_ENABLE;

    RBSYS_DSB(); //< ensure that configuration is written to register
    RBSYS_ISB(); //< clear pipeline to avoid using prefetched instructions (prefetched with old config)
  }


  /* TODO: Cluster NOC Guards should be enabled before opening up the LRAM to other BusMasters, otherwise might compromise the LRAM zeroing done before */
  void RBSYS_GRAMGuardInit_Impl(void)
  {
    RBSYS_SwitchSVToHV();

    /* Cluster RAMs (Cluster Access in general) */
    rbsys_NOCFirewallConfigure(&rbsys_Cluster0_Firewall);   // Host-Clusters are controlled by Host only
    rbsys_NOCFirewallConfigure(&rbsys_Cluster1_Firewall);   // Host-Clusters are controlled by Host only
    rbsys_NOCFirewallConfigure(&rbsys_Cluster2_Firewall);   // Host-Clusters are controlled by Host only
    // /* SYSRAM */
    rbsys_NOCFirewallConfigure(&rbsys_SYSRAM0_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_SYSRAM1_Firewall);

    RBSYS_SwitchHVToSV();
  }

  void RBSYS_PeripheralGuardsInit(void)
  {
    /* For Stellar, Accesses from all unsafe Busmasters ("Initiators") are routed through the NOC. Therefore, GRAM Guards etc. are
     * mainly realized in the FlexNOC via slave ("Target") side memory protections */

    RBSYS_SwitchSVToHV();

    rbsys_NOCFirewallConfigure(&rbsys_AESLIGHT0_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_AESLIGHT1_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_AESLIGHT2_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_AESLIGHT3_Firewall);
    // rbsys_NOCFirewallConfigure(&rbsys_PCIE0_Firewall);     //< not supported on P6, do not configure as envelope strategy
    // rbsys_NOCFirewallConfigure(&rbsys_PCIE0_CFG_Firewall); //< not supported on P6, do not configure as envelope strategy
    // rbsys_NOCFirewallConfigure(&rbsys_PCIE1_Firewall);     //< not supported on P6, do not configure as envelope strategy
    // rbsys_NOCFirewallConfigure(&rbsys_PCIE1_CFG_Firewall); //< not supported on P6, do not configure as envelope strategy
    rbsys_NOCFirewallConfigure(&rbsys_TMC0_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_TMC1_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_TMC2_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_OCTOSPI_Firewall);
    // rbsys_NOCFirewallConfigure(&rbsys_SDMMC_Firewall);     //< not supported on P6, do not configure as envelope strategy
    rbsys_NOCFirewallConfigure(&rbsys_DAP_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_DFA_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_DSPH_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_DME_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_GTM_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_AIPS0_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_AIPS1_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_AIPS2_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_AIPS3_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_AIPS4_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_NVM_Firewall);
    rbsys_NOCFirewallConfigure(&rbsys_HSM_Firewall);

    RBSYS_SwitchHVToSV();

    // /* Further Todos:
    //   - allow R and W access from HSM to specific registers
    //   - ...*/
  }
#endif


/** @} */
/* End ingroup RBSYS */