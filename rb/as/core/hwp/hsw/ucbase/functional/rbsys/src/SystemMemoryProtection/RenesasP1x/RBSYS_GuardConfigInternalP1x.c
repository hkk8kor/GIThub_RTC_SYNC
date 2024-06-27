/**
 * @ingroup RBSYS
 * @{
 *
 * @file  RBSYS_GuardConfigInternalP1x.c
 * @brief Guard based System Memory Protection
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
#include "../../RBSYS_TestInjection.h" //< relative include is ugly, file should be public

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHSMsharedGRAM,
                          RBFS_SysHSMsharedGRAM_Host,
                          RBFS_SysHSMsharedGRAM_Restricted);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHsmSharedGRAMsize,
                          RBFS_SysHsmSharedGRAMsize_0K,
                          RBFS_SysHsmSharedGRAMsize_16K,
                          RBFS_SysHsmSharedGRAMsize_32K);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RestrictedExclusiveGRAMsize,
                          RBFS_RestrictedExclusiveGRAMsize_0K,
                          RBFS_RestrictedExclusiveGRAMsize_16K,
                          RBFS_RestrictedExclusiveGRAMsize_32K);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasP1xGRAM,
                          RBFS_RenesasP1xGRAM_ON,
                          RBFS_RenesasP1xGRAM_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);


#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  #include "RBSYS_GuardConfigInternalP1x.h"

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysGuardPresenceGrp1,
                            RBFS_SysGuardPresenceGrp1_YES,
                            RBFS_SysGuardPresenceGrp1_NO);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysGuardPresenceGrp2,
                            RBFS_SysGuardPresenceGrp2_YES,
                            RBFS_SysGuardPresenceGrp2_NO);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysGuardPresenceGrp3,
                            RBFS_SysGuardPresenceGrp3_YES,
                            RBFS_SysGuardPresenceGrp3_NO);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysExclusiveSPID,
                            RBFS_SysExclusiveSPID_Used,
                            RBFS_SysExclusiveSPID_NotUsed);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                            RBFS_SysEnvironment_Target,
                            RBFS_SysEnvironment_Simulation);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                            RBFS_TargetDevice_RenesasD1,
                            RBFS_TargetDevice_RenesasD2,
                            RBFS_TargetDevice_RenesasD3,
                            RBFS_TargetDevice_RenesasD4,
                            RBFS_TargetDevice_RenesasD5);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysRAMLayoutFragmentation,
                            RBFS_SysRAMLayoutFragmentation_Default,
                            RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEthSharedGRAMsize,
                            RBFS_SysEthSharedGRAMsize_0K,
                            RBFS_SysEthSharedGRAMsize_32K,
                            RBFS_SysEthSharedGRAMsize_64K,
                            RBFS_SysEthSharedGRAMsize_96K,
                            RBFS_SysEthSharedGRAMsize_128K);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_RBSYSGlobalRAMGuardsBB,
                            RBFS_RBSYSGlobalRAMGuardsBB_ON,
                            RBFS_RBSYSGlobalRAMGuardsBB_OFF);


  /* Verification of the defines RBSYS_PROTREGINITVALUE... */
  static_assert((0x060DFE1Bu &(~(RBSYS_PEID_SAFE|RBSYS_PEID_SECURE))) == RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS, "RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS check failed!");
  static_assert((0x064DFE1Bu &(~(RBSYS_PEID_SAFE|RBSYS_PEID_SECURE))) == RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS, "RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS check failed!");
  static_assert((0x060DFE17u &(~(RBSYS_PEID_SAFE|RBSYS_PEID_SECURE))) == RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS, "RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS check failed!");
  static_assert((0x064DFE17u &(~(RBSYS_PEID_SAFE|RBSYS_PEID_SECURE))) == RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS, "RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS check failed!");
  static_assert((0x060DFE0Bu &(~(RBSYS_PEID_SAFE|RBSYS_PEID_SECURE))) == RBSYS_PROTREGINITVALUE4ICUM_READ_WITHOUTPEIDFLAGS, "RBSYS_PROTREGINITVALUE4ICUM_READ_WITHOUTPEIDFLAGS check failed!");
  static_assert((0x064DFE0Bu &(~(RBSYS_PEID_SAFE|RBSYS_PEID_SECURE))) == RBSYS_PROTREGINITVALUE4ICUM_READ_WITHOUTPEIDFLAGS, "RBSYS_PROTREGINITVALUE4ICUM_READ_WITHOUTPEIDFLAGS check failed!");
  static_assert((0x060DFE07u &(~(RBSYS_PEID_SAFE|RBSYS_PEID_SECURE))) == RBSYS_PROTREGINITVALUE4ICUM_WRITE_WITHOUTPEIDFLAGS, "RBSYS_PROTREGINITVALUE4ICUM_WRITE_WITHOUTPEIDFLAGS check failed!");
  static_assert((0x064DFE07u &(~(RBSYS_PEID_SAFE|RBSYS_PEID_SECURE))) == RBSYS_PROTREGINITVALUE4ICUM_WRITE_WITHOUTPEIDFLAGS, "RBSYS_PROTREGINITVALUE4ICUM_WRITE_WITHOUTPEIDFLAGS check failed!");


  #if( (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION) || (RBFS_RBSYSGlobalRAMGuardsBB == RBFS_RBSYSGlobalRAMGuardsBB_ON) )
    /* ******************************************************************************* */
    /*  Init value for PROT Registers (Protection by PEID)                             */
    /* ******************************************************************************* */
    /*                                                                                 */
    /* In the microcontroller the following register init values exist:                */
    /*                                                                                 */
    /*  PE1/PE2 Registers:                                                             */
    /*  RD    0x060D FE1B          only PE1/PE2 access, ICUM prohibited                */
    /*  WR    0x060D FE17          only PE1/PE2 access, ICUM prohibited                */
    /*  RD    0x064D FE1B          PE1/PE2 access as well as ICUM access               */
    /*  WR    0x064D FE17          PE1/PE2 access as well as ICUM access               */
    /*  ICUMC Registers:                                                               */
    /*  RD    0x0641 FE0B          only ICUM access, PE1/PE2 prohibited                */
    /*  WR    0x0641 FE07          only ICUM access, PE1/PE2 prohibited                */
    /*  RD    0x064D FE0B          PE1/PE2 access as well as ICUM access               */
    /*  WR    0x064D FE07          PE1/PE2 access as well as ICUM access               */
    /*                                                                                 */
    /* In principle we have 4 different Init values once all PEID-Flags are zeroed.    */
    /*  PE1/PE2 Registers:                                                             */
    /*  RD    0x0601 FE1B                                                              */
    /*  WR    0x0601 FE17                                                              */
    /*  ICUMC Registers:                                                               */
    /*  RD    0x0601 FE0B                                                              */
    /*  WR    0x0601 FE07                                                              */
    /*                                                                                 */
    /* ******************************************************************************* */


    #define RBSYS_ALL_SPIDS_IN_REGISTER     0xFFFFFFFFu

    /* Hint: Initially, all RAM Sections assigned to "Restricted" SPID are assigned to "Safe and Restricted". When Guard
     *       settings are being frozen, SPID will be changed to exclusively "Restricted". -> Lukas: same opinion */

    typedef struct {
      RBSYS_GuardsList_t BAD;
      RBSYS_GuardsList_t ADV;
      RBSYS_GuardsList_t SPID;
      RBSYS_GuardsList_t PROT;
    } RBSYS_GRAMGuardSetting_t;

    #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
      static const RBSYS_GRAMGuardSetting_t RBSYS_GlobalRAMGuardsList[] = {
        /* GRAM Guard 0 */
        {
          {&MGDGRBAD0,  RBSYS_GUARDREGION0_BASEADDR},
          {&MGDGRADV0,  RBSYS_GUARD_MASK_1024KB},
          {&MGDGRSPID0, RBSYS_SPID_SAFE_MASK},
          {&MGDGRPROT0, RBSYS_GRAMGUARD_ENABLE},
        },

        /* GRAM Guard 1 */
        {
          {&MGDGRBAD1,  RBSYS_GUARDREGION1_BASEADDR},
          {&MGDGRADV1,  RBSYS_GUARD_MASK_16KB},
          #if(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_0K)

            {&MGDGRSPID1, RBSYS_SPID_SAFE_MASK},

          #elif(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_16K)

            #if(RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted)
              // allow SAFE SPID to access Restricted HSM Shared RAM for variable initialization, this section will be set to (Restricted || Secure) SPID only later on (SAFE access will be removed)
              {&MGDGRSPID1, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SECURE_MASK)},
            #else
              {&MGDGRSPID1, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},
            #endif

          #elif(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_32K)

            #if( RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_Default )
              #if(RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted)
                // allow SAFE SPID to access Restricted HSM Shared RAM for variable initialization, this section will be set to (Restricted || Secure) SPID only later on (SAFE access will be removed)
                {&MGDGRSPID1, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SECURE_MASK)},
              #else // RBFS_SysHSMsharedGRAM_Host
                {&MGDGRSPID1,  (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},
              #endif
            #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) && (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR) )
              #if( RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K )
                {&MGDGRSPID1, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_UNSAFE_MASK)},
              #else
                {&MGDGRSPID1, (RBSYS_SPID_SAFE_MASK)},
              #endif
            #endif

          #else
            /* should not be the case as the AssertSwitchSettings ensures one of the settings */
            #error ("Invalid setting of RBFS_SysHsmSharedGRAMsize!")
          #endif
          {&MGDGRPROT1, RBSYS_GRAMGUARD_ENABLE},
        },

        /* GRAM Guard 2 */
        {
          {&MGDGRBAD2,  RBSYS_GUARDREGION2_BASEADDR},
          {&MGDGRADV2,  RBSYS_GUARD_MASK_16KB},
          #if(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_0K)
            #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K)
              // allow SAFE SPID to access Restricted Exclusive RAM for variable initialization, this section will be set to Restricted SPID only later on (SAFE access will be removed)
              {&MGDGRSPID2, RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK},
            #else
              {&MGDGRSPID2, RBSYS_SPID_SAFE_MASK},
            #endif
          #elif(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_16K)
            #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K)
              // allow SAFE SPID to access Restricted Exclusive RAM for variable initialization, this section will be set to Restricted SPID only later on (SAFE access will be removed)
              {&MGDGRSPID2, RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK},
            #else
              {&MGDGRSPID2, RBSYS_SPID_SAFE_MASK},
            #endif
          #elif(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_32K)
            #if( RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_Default )
              #if(RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted)
                {&MGDGRSPID2, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SECURE_MASK)},
              #else // RBFS_SysHSMsharedGRAM_Host
                {&MGDGRSPID2, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},
              #endif
            #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) && (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR) )
              #if( RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K )
                {&MGDGRSPID2, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_UNSAFE_MASK)},
              #else
                {&MGDGRSPID2, (RBSYS_SPID_SAFE_MASK)},
              #endif
            #endif
          #else
            /* should not be the case as the AssertSwitchSettings ensures one of the settings */
            #error ("Invalid setting of RBFS_SysHsmSharedGRAMsize!")
          #endif
          {&MGDGRPROT2, (RBSYS_GRAMGUARD_ENABLE)},
        },

        /* GRAM Guard 3 */
        {
          {&MGDGRBAD3,  RBSYS_GUARDREGION3_BASEADDR},
          {&MGDGRADV3,  RBSYS_GUARD_MASK_32KB},
          #if( RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_Default )
            #if ((RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_32K) || (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K))
              {&MGDGRSPID3, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_UNSAFE_MASK)},
            #else
              #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K)
                // allow SAFE SPID to access Restricted Exclusive RAM for variable initialization, this section will be set to Restricted SPID only later on (SAFE access will be removed)
                {&MGDGRSPID3, RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK},
              #else
                {&MGDGRSPID3, RBSYS_SPID_SAFE_MASK},
              #endif
            #endif
          #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) && (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR) )
            #if ((RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_32K) || (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K) || (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K))
              {&MGDGRSPID3, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_UNSAFE_MASK)},
            #else
              {&MGDGRSPID3, RBSYS_SPID_SAFE_MASK},
            #endif
          #endif
          {&MGDGRPROT3, RBSYS_GRAMGUARD_ENABLE},
        },

        /* GRAM Guard 4 */
        {
          {&MGDGRBAD4,  RBSYS_GUARDREGION4_BASEADDR},
          {&MGDGRADV4,  RBSYS_GUARD_MASK_64KB},
          #if( RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_Default )
            #if ((RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_64K) || (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K))
              {&MGDGRSPID4, RBSYS_SPID_SAFE_MASK | RBSYS_SPID_UNSAFE_MASK},
            #else
              {&MGDGRSPID4, RBSYS_SPID_SAFE_MASK},
            #endif
          #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) && (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR) )
            #if ((RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_64K) || (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K) || (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K))
              {&MGDGRSPID4, RBSYS_SPID_SAFE_MASK | RBSYS_SPID_UNSAFE_MASK},
            #else
              {&MGDGRSPID4, RBSYS_SPID_SAFE_MASK},
            #endif
          #endif
          {&MGDGRPROT4, RBSYS_GRAMGUARD_ENABLE},
        },

        /* GRAM Guard 5 */
        {
          {&MGDGRBAD5,  RBSYS_GUARDREGION5_BASEADDR},
          {&MGDGRADV5,  RBSYS_GUARD_MASK_128KB},
          #if( RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_Default )
            #if (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K)
              {&MGDGRSPID5, RBSYS_SPID_SAFE_MASK | RBSYS_SPID_UNSAFE_MASK},
            #else
              {&MGDGRSPID5, RBSYS_SPID_SAFE_MASK},
            #endif
          #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) && (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR) )
            {&MGDGRSPID5, RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK},
          #endif
          {&MGDGRPROT5, RBSYS_GRAMGUARD_ENABLE},
        },

        /* GRAM Guard 6 */
        {
          {&MGDGRBAD6,  RBSYS_GUARDREGION6_BASEADDR},
          {&MGDGRADV6,  RBSYS_GUARD_MASK_256KB},
          {&MGDGRSPID6, RBSYS_SPID_SAFE_MASK},
          {&MGDGRPROT6, (RBSYS_GRAMGUARD_ENABLE)},
        },

        /* GRAM Guard 7 */
        {
          {&MGDGRBAD7,  RBSYS_GUARDREGION7_BASEADDR},
          {&MGDGRADV7,  RBSYS_GUARD_MASK_512KB},
          {&MGDGRSPID7, RBSYS_SPID_SAFE_MASK},
          {&MGDGRPROT7, (RBSYS_GRAMGUARD_ENABLE)},
        }
      };

      static const uint32 RBSYS_GlobalRAMGuardsListNumElements = sizeof(RBSYS_GlobalRAMGuardsList)/sizeof(RBSYS_GRAMGuardSetting_t);

      static void RBSYS_ConfigureGRAMGuards(const RBSYS_GRAMGuardSetting_t* GramGuards, uint32 num)
      {
        uint32 i;
        for( i=0; i<num; i++ )
        {
          *GramGuards[i].BAD.Guard_Register  = GramGuards[i].BAD.GuardValue;
          *GramGuards[i].ADV.Guard_Register  = GramGuards[i].ADV.GuardValue;
          *GramGuards[i].SPID.Guard_Register = GramGuards[i].SPID.GuardValue;
          *GramGuards[i].PROT.Guard_Register |= GramGuards[i].PROT.GuardValue;
        }
      }
      #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
        static boolean RBSYS_IsAnyGRAMGuardLocked(const RBSYS_GRAMGuardSetting_t* GramGuards, uint32 num)
        {
          boolean res = FALSE;
          uint32 i;
          for( i=0; i<num; i++ )
          {
            if( (*GramGuards[i].PROT.Guard_Register & RBSYS_GRAMGUARD_LOCK) != 0 )
            {
              res = TRUE;
            }
          }
          return res;
        }
      #endif //< RBFS_HexBlockBuild_APPLICATION
    #endif



    #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
      RBSECTION_START_LRAM0_BSS_NOCLEAR
        /* Steps for GRAM:
        *  1. Protect GRAM Guards via PBUS Guard
        *  2. Check if PBUS Guard setting is correct -> GRAMGuardInit_IsPBUSGuardConfigurationInvalid
        *  3. Check if any GRAM Guard is locked      -> GRAMGuardInit_IsGRAMGuardConfigurationPreconditionWrong
        *  4. Setup GRAM Guards and do not lock
        *  5. Clear GRAM
        * => Important:
        *     - Store "Precondition" result in LRAM to not zero it during Step 5.
        *     - Store result in non-initialized variables
        */
        static boolean rbsys_GRAMGuardInit_IsPBUSGuardConfigurationInvalid;
        static boolean rbsys_GRAMGuardInit_IsGRAMGuardConfigurationPreconditionWrong;
      RBSECTION_END_LRAM0_BSS_NOCLEAR

      static boolean RBSYS_GRAMGuardInit_IsGRAMGuardConfigurationPreconditionWrong(void)
      {
        return rbsys_GRAMGuardInit_IsGRAMGuardConfigurationPreconditionWrong;
      }

      static boolean RBSYS_GRAMGuardInit_IsPBUSGuardConfigurationInvalid(void)
      {
        return rbsys_GRAMGuardInit_IsPBUSGuardConfigurationInvalid;
      }
    #endif

    #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
      void RBSYS_PBUSGuardInit_ForGRAMGuard(void)
      {
          APBFSGDSPID_SP4_B = RBSYS_SPID_SAFE_MASK;                                                                                /* only allow PE1/PE2, but not ICUM access to the GRAM guard config registers */
          APBFSGDPROT_SP4_B = (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK); /* only allow PE1/PE2, but not ICUM access to the GRAM guard config registers */
          /* Note: set the guard here in any case, so we can depend on it being set at this point in time */

          RBSYS_TEST_INJECTION_PBUSGuardForGRAMManipulation();

          #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
            {
              uint32 apbfsgdspid_sp4_b = APBFSGDSPID_SP4_B;
              uint32 apbfsgdprot_sp4_b = APBFSGDPROT_SP4_B;
              if( (apbfsgdspid_sp4_b != RBSYS_SPID_SAFE_MASK) || (apbfsgdprot_sp4_b != (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)) )
              {
                rbsys_GRAMGuardInit_IsPBUSGuardConfigurationInvalid = TRUE;
              }
              else
              {
                rbsys_GRAMGuardInit_IsPBUSGuardConfigurationInvalid = FALSE; //< explicit initialization is required because of use before C-Init
              }
            }
          #endif
      }
    #else
      /* APBFSGD_SP4 has to be set inside RBSYS_PBUSGuardInit */
    #endif //< RBFS_RenesasP1xGRAM_ON

    #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
      void RBSYS_GRAMGuardInit_Impl(void)
      {
        #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
          /* Access to the GRAM Guards is restricted by PBUS Guards, but the GRAM Guards might already be locked */
          if( RBSYS_IsAnyGRAMGuardLocked(RBSYS_GlobalRAMGuardsList, RBSYS_GlobalRAMGuardsListNumElements) )
          {
            /* In case any GRAM Guard is locked already, it cannot be reconfigured => SysErrorHook */
            rbsys_GRAMGuardInit_IsGRAMGuardConfigurationPreconditionWrong = TRUE;
            /*< SysErrorHook cannot be reported at the moment. Fault State is stored for later failure report */
          }
          else
          {
            rbsys_GRAMGuardInit_IsGRAMGuardConfigurationPreconditionWrong = FALSE; //< explicit initialization is required because of use before C-Init
          }
        #endif
        RBSYS_ConfigureGRAMGuards(RBSYS_GlobalRAMGuardsList, RBSYS_GlobalRAMGuardsListNumElements);
      }
    #endif
  #endif


  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )

    #if(RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K)

      /** Hint: Reconfiguration of SPID-Mask is allowed while Guard is enabled. When modifying SPID-Mask, pay attention:
        *         - Adding additional SPIDs: Assure that guard configuration is effective before accessing with the new SPID
        *         - Removing SPIDs:          Assure that all accesses with the removed SPID are finished before
        */

      void RBSYS_RestrictedExclusiveGRAM_AllowSafeAccess(void)
      {
        #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K)
          /* uses the 16K section (guard region 2) starting at 0xFEEF8000 */
          MGDGRSPID2 =  RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK; //< still allow access from Restricted SPID in parallel
          //< Nothing is running in parallel, function is called only if BERT is running exclusively on all cores (U2A: BERT is running in parallel!)
        #endif

        #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K)
          /* uses the 32K section (guard region 3) starting at 0xFEEF0000 */
          MGDGRSPID3 =  RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK; //< still allow access from Restricted SPID in parallel
          //< Nothing is running in parallel, function is called only if BERT is running exclusively on all cores (U2A: BERT is running in parallel!)
        #endif

        RBSYS_SYNCM();
      }

      void RBSYS_RestrictedExclusiveGRAM_BlockSafeAccess(void)
      {
        RBSYS_SYNCM(); //< Ensure that accesses with SAFE-SPID are finished before removing privilege

        #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K)
          /* uses the 16K section (guard region 2) starting at 0xFEEF8000 */
          MGDGRSPID2 =  RBSYS_SPID_RESTRICTED_MASK;
        #endif

        #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K)
          /* uses the 32K section (guard region 3) starting at 0xFEEF0000 */
          MGDGRSPID3 =  RBSYS_SPID_RESTRICTED_MASK;
        #endif
      }

    #endif //< RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K

    #if( RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted )
      void RBSYS_RestrictedHSMSharedGRAM_BlockSafeAccess(void)
      {
        RBSYS_SYNCM(); //< Ensure that accesses with SAFE-SPID are finished before removing privilege

        #if( (RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_16K) || (RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_32K) )
          MGDGRSPID1 = (RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SECURE_MASK);
        #endif

        #if(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_32K)
          MGDGRSPID2 = (RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SECURE_MASK);
        #endif
      }
    #endif


    /*
     * Definition of the guards to be set EARLY during ECU startup
     *
     * Hint: Intelligent Ordering of the Guard initialization sequence does not make sense here,
     *       because all Guards are mainly protected by a One-Time-Lock Function.
     *                                                                                          */
    static const RBSYS_GuardsList_t RBSYS_PeripheralGuardList[] = {

      /* APB Guard PFSS 0 (APBFSGD...) */
      {&APBFSGDSPID_PBG_A,    RBSYS_ALL_SPIDS_IN_REGISTER},
      {&APBFSGDPROT_PBG_A,    (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&APBFSGDSPID_PBG_B,    (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},  /* allow ICUM to PE1/PE2registers (default init value) */
      {&APBFSGDPROT_PBG_B,    (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},    /* allow ICUM to PE1/PE2registers (default init value) */
      {&APBFSGDSPID_SP1_A,    RBSYS_ALL_SPIDS_IN_REGISTER},
      {&APBFSGDPROT_SP1_A,    (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&APBFSGDSPID_SP1_B,    RBSYS_SPID_SAFE_MASK},
      {&APBFSGDPROT_SP1_B,    (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
        {&APBFSGDSPID_SP2_A,    RBSYS_ALL_SPIDS_IN_REGISTER},
        {&APBFSGDPROT_SP2_A,    (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&APBFSGDSPID_SP2_B,    RBSYS_SPID_SAFE_MASK},
        {&APBFSGDPROT_SP2_B,    (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif
      {&APBFSGDSPID_SP4_A,    RBSYS_ALL_SPIDS_IN_REGISTER},
      {&APBFSGDPROT_SP4_A,    (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      #if( RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON )
        // APBFSGDSPID_SP4_B    - already set and locked by GRAM guard procedure RBSYS_GRAMGuardInit() to RBSYS_SPID_SAFE_MASK only
        // APBFSGDPROT_SP4_B    - already set and locked by GRAM guard procedure RBSYS_GRAMGuardInit() to RBSYS_PEID_SAFE only
      #else
        // In case GRAM is not used, APBFSGD_SP4 is initialized later
        {&APBFSGDSPID_SP4_B,  RBSYS_SPID_SAFE_MASK},                                                                                /* only allow PE1/PE2, but not ICUM access to the GRAM guard config registers */
        {&APBFSGDPROT_SP4_B,  (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)}, /* only allow PE1/PE2, but not ICUM access to the GRAM guard config registers */
      #endif

      /* APB Guard PFSS 1 (APBFSGD...) */
      {&APBFSGDSPID_PDMACM_A, RBSYS_ALL_SPIDS_IN_REGISTER},
      {&APBFSGDPROT_PDMACM_A, (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&APBFSGDSPID_PDMACM_B, RBSYS_SPID_SAFE_MASK},
      {&APBFSGDPROT_PDMACM_B, (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&APBFSGDSPID_PDMACH_A, RBSYS_ALL_SPIDS_IN_REGISTER},
      {&APBFSGDPROT_PDMACH_A, (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&APBFSGDSPID_PDMACH_B, RBSYS_SPID_SAFE_MASK},
      {&APBFSGDPROT_PDMACH_B, (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&APBFSGDSPID_INTC2_A,  RBSYS_ALL_SPIDS_IN_REGISTER},
      {&APBFSGDPROT_INTC2_A,  (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&APBFSGDSPID_INTC2_B,  RBSYS_SPID_SAFE_MASK},
      {&APBFSGDPROT_INTC2_B,  (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},

      /* PBus Guard 1 Group 0 (FSGD1A...) */
      {&FSGD1ASPID00,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD1APROT00,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD1ASPID01,         (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},    /* allow ICUM to PE1/PE2registers (default init value) */
      {&FSGD1APROT01,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},    /* allow ICUM to PE1/PE2registers (default init value) */
      {&FSGD1ASPID02,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD1APROT02,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD1ASPID03,         RBSYS_SPID_SAFE_MASK},
      {&FSGD1APROT03,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD1ASPID04,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD1APROT04,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD1ASPID05,         RBSYS_SPID_SAFE_MASK},
      {&FSGD1APROT05,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},   /* Enable write access of RLIN31/33 */
      #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
        {&FSGD1ASPID06,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD1APROT06,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD1ASPID07,         RBSYS_SPID_SAFE_MASK},
        {&FSGD1APROT07,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif

      /* PBus Guard 1 Group 1 (FSGD1B...) */
      {&FSGD1BSPID00,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD1BPROT00,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD1BSPID01,         RBSYS_SPID_SAFE_MASK},
      {&FSGD1BPROT01,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #if (RBFS_SysGuardPresenceGrp3 == RBFS_SysGuardPresenceGrp3_YES)
        {&FSGD1BSPID02,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD1BPROT02,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD1BSPID03,         RBSYS_SPID_SAFE_MASK},
        {&FSGD1BPROT03,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif
      #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
        {&FSGD1BSPID06,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD1BPROT06,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD1BSPID07,         RBSYS_SPID_SAFE_MASK},
        {&FSGD1BPROT07,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif
      #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
        {&FSGD1BSPID08,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD1BPROT08,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},   // currently we do not use D4_BGA-156 - if we do this in the future a "runtime if" is needed here!
        {&FSGD1BSPID09,         RBSYS_SPID_SAFE_MASK},
        {&FSGD1BPROT09,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},   // currently we do not use D4_BGA-156 - if we do this in the future a "runtime if" is needed here!
      #endif
      {&FSGD1BSPID10,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD1BPROT10,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD1BSPID11,         RBSYS_SPID_SAFE_MASK},      // restrict writes to safe applications (DMA)
      {&FSGD1BPROT11,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
        {&FSGD1BSPID12,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD1BPROT12,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD1BSPID13,         RBSYS_SPID_SAFE_MASK},     // restrict writes to safe applications (DMA)
        {&FSGD1BPROT13,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif

      /* PBus Guard 2 (FSGD2A...) */
      {&FSGD2ASPID00,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD2APROT00,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD2ASPID01,         (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},    /* allow ICUM to PE1/PE2registers (default init value) */
      {&FSGD2APROT01,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},    /* allow ICUM to PE1/PE2registers (default init value) */
      {&FSGD2ASPID02,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD2APROT02,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD2ASPID03,         RBSYS_SPID_SAFE_MASK},
      {&FSGD2APROT03,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD2ASPID04,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD2APROT04,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD2ASPID05,         RBSYS_SPID_SAFE_MASK},   // restrict writes to safe applications (DMA)
      {&FSGD2APROT05,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD2ASPID06,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD2APROT06,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD2ASPID07,         RBSYS_SPID_SAFE_MASK},
      {&FSGD2APROT07,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
        {&FSGD2ASPID08,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD2APROT08,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD2ASPID09,         RBSYS_SPID_SAFE_MASK},
        {&FSGD2APROT09,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif
      {&FSGD2ASPID10,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD2APROT10,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD2ASPID11,         RBSYS_SPID_SAFE_MASK},
      {&FSGD2APROT11,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
        {&FSGD2ASPID12,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD2APROT12,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD2ASPID13,         RBSYS_SPID_SAFE_MASK},
        {&FSGD2APROT13,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif

      /* PBus Guard 3 Group 0 (FSGD3A...) */
      {&FSGD3ASPID00,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD3APROT00,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3ASPID01,         RBSYS_SPID_SAFE_MASK},
      {&FSGD3APROT01,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3ASPID02,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD3APROT02,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3ASPID03,         RBSYS_SPID_SAFE_MASK},
      {&FSGD3APROT03,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3ASPID04,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD3APROT04,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3ASPID05,         RBSYS_SPID_SAFE_MASK},
      {&FSGD3APROT05,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3ASPID06,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD3APROT06,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3ASPID07,         RBSYS_SPID_SAFE_MASK},
      {&FSGD3APROT07,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3ASPID08,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD3APROT08,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3ASPID09,         RBSYS_SPID_SAFE_MASK},
      {&FSGD3APROT09,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
        {&FSGD3ASPID10,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD3APROT10,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD3ASPID11,         RBSYS_SPID_SAFE_MASK},
        {&FSGD3APROT11,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif
      {&FSGD3ASPID12,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD3APROT12,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3ASPID13,         RBSYS_SPID_SAFE_MASK},
      {&FSGD3APROT13,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
        {&FSGD3ASPID14,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD3APROT14,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD3ASPID15,         RBSYS_SPID_SAFE_MASK},
        {&FSGD3APROT15,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif

      /* PBus Guard 3 Group 1 (FSGD3B...) */
      {&FSGD3BSPID00,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD3BPROT00,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3BSPID01,         RBSYS_SPID_SAFE_MASK},
      {&FSGD3BPROT01,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
        {&FSGD3BSPID02,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD3BPROT02,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD3BSPID03,         RBSYS_SPID_SAFE_MASK},
        {&FSGD3BPROT03,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD3BSPID06,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD3BPROT06,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD3BSPID07,         RBSYS_SPID_SAFE_MASK},
        {&FSGD3BPROT07,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif
      #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
        {&FSGD3BSPID08,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD3BPROT08,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},    // currently we do not use D4_BGA-156 - if we do this in the future a "runtime if" is needed here!
        {&FSGD3BSPID09,         RBSYS_SPID_SAFE_MASK},
        {&FSGD3BPROT09,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},     // currently we do not use D4_BGA-156 - if we do this in the future a "runtime if" is needed here!
      #endif
      {&FSGD3BSPID10,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD3BPROT10,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3BSPID11,         RBSYS_SPID_SAFE_MASK},      // restrict writes to safe applications (DMA)
      {&FSGD3BPROT11,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3BSPID12,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD3BPROT12,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD3BSPID13,         RBSYS_SPID_SAFE_MASK},      // restrict writes to safe applications (DMA)
      {&FSGD3BPROT13,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},

      /* ********************************************************************* */
      /* read access guards for clear-by-read registers - no ICUM read allowed */
      /* ********************************************************************* */
      /* PBus Guard 4 Group 0 (FSGD4A...) */
      {&FSGD4ASPID00,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD4APROT00,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4ASPID01,         (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},                                              /* allow ICUM to PE1/PE2registers (default init value) */
      {&FSGD4APROT01,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},     /* allow ICUM to PE1/PE2registers (default init value) */
      {&FSGD4ASPID02,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD4APROT02,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4ASPID03,         RBSYS_SPID_SAFE_MASK},
      {&FSGD4APROT03,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4ASPID04,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD4APROT04,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4ASPID05,         RBSYS_SPID_SAFE_MASK},
      {&FSGD4APROT05,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4ASPID06,         RBSYS_SPID_SAFE_MASK},
      {&FSGD4APROT06,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4ASPID07,         RBSYS_SPID_SAFE_MASK},
      {&FSGD4APROT07,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
        {&FSGD4ASPID08,         RBSYS_SPID_SAFE_MASK},
        {&FSGD4APROT08,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD4ASPID09,         RBSYS_SPID_SAFE_MASK},
        {&FSGD4APROT09,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif
      {&FSGD4ASPID10,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD4APROT10,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4ASPID12,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD4APROT12,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4ASPID13,         RBSYS_SPID_SAFE_MASK},
      {&FSGD4APROT13,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4ASPID14,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD4APROT14,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4ASPID15,         RBSYS_SPID_SAFE_MASK},
      {&FSGD4APROT15,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},

      /* PBus Guard 4 Group 1 (FSGD4B...) */
      {&FSGD4BSPID00,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD4BPROT00,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4BSPID01,         RBSYS_SPID_SAFE_MASK},
      {&FSGD4BPROT01,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4BSPID02,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD4BPROT02,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4BSPID03,         RBSYS_SPID_SAFE_MASK},
      {&FSGD4BPROT03,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
        {&FSGD4BSPID04,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD4BPROT04,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD4BSPID05,         RBSYS_SPID_SAFE_MASK},
        {&FSGD4BPROT05,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif
      {&FSGD4BSPID06,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD4BPROT06,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4BSPID07,         RBSYS_SPID_SAFE_MASK},
      {&FSGD4BPROT07,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4BSPID08,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD4BPROT08,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4BSPID09,         RBSYS_SPID_SAFE_MASK},
      {&FSGD4BPROT09,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4BSPID10,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD4BPROT10,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4BSPID11,         RBSYS_SPID_SAFE_MASK},
      {&FSGD4BPROT11,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4BSPID12,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD4BPROT12,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD4BSPID13,         (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},
      {&FSGD4BPROT13,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},      /* allow ICUM to PE1/PE2registers (default init value) */

      /* PBus Guard 4 Group 2 (FSGD4C...) */
      /* Note: it is not allowed to set the ICUMC group  4C */

      /* PBus Guard 5 Group 0 (FSGD5A...) */
      {&FSGD5ASPID00,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD5APROT00,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD5ASPID01,         (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},                                              /* allow ICUM to PE1/PE2registers (default init value) */
      {&FSGD5APROT01,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},     /* allow ICUM to PE1/PE2registers (default init value) */
      #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
        {&FSGD5ASPID02,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD5APROT02,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD5ASPID03,         (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},                                                /* allow ICUM to PE1/PE2 registers */
        {&FSGD5APROT03,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},   /* allow ICUM to PE1/PE2 registers (init value modified) */
      #endif
      {&FSGD5ASPID04,         RBSYS_ALL_SPIDS_IN_REGISTER},
      {&FSGD5APROT04,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      {&FSGD5ASPID05,         (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},                                                /* allow ICUM to PE1/PE2 registers */
      {&FSGD5APROT05,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},   /* allow ICUM to PE1/PE2 registers (init value modified) */

      /* PBus Guard 5 Group 1 (FSGD5B...) */
      #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
        {&FSGD5BSPID00,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD5BPROT00,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD5BSPID01,         (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},                                              /* allow ICUM to PE1/PE2registers */
        {&FSGD5BPROT01,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},     /* allow ICUM to PE1/PE2registers (default init value) */
        {&FSGD5BSPID02,         RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGD5BPROT02,         (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGD5BSPID03,         (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK)},                                                /* allow ICUM to PE1/PE2 registers */
        {&FSGD5BPROT03,         (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},   /* allow ICUM to PE1/PE2 registers (init value modified) */
      #endif
      /* Note: it is not allowed to set the ICUMC groups  5C  and 5D  */

      /* ********************************************************************* */
      /*   H-Bus guards  (only for D3 and higher)                              */
      /* ********************************************************************* */
      #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
        {&FSGDE0SPID01,           RBSYS_SPID_SAFE_MASK},
        {&FSGDE0PROT01,           (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDF0SPID01,           RBSYS_SPID_SAFE_MASK},
        {&FSGDF0PROT01,           (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif
      #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
        {&FSGDE1SPID01,           RBSYS_SPID_SAFE_MASK},
        {&FSGDE1PROT01,           (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDF1SPID01,           RBSYS_SPID_SAFE_MASK},
        {&FSGDF1PROT01,           (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDM0SPID01,           RBSYS_SPID_SAFE_MASK},
        {&FSGDM0PROT01,           (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDM0SPID03,           RBSYS_SPID_SAFE_MASK},
        {&FSGDM0PROT03,           (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDM0SPID05,           RBSYS_SPID_SAFE_MASK},
        {&FSGDM0PROT05,           (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDM0SPID07,           RBSYS_SPID_SAFE_MASK},
        {&FSGDM0PROT07,           (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDM0SPID09,           RBSYS_SPID_SAFE_MASK},
        {&FSGDM0PROT09,           (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif

      /* ********************************************************************* */
      /*   H-Bus guards  (only for D3 and higher)                              */
      /* ********************************************************************* */
      #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
        {&FSGDE0SPID00,           RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGDE0PROT00,           (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDF0SPID00,           RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGDF0PROT00,           (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif
      #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
        {&FSGDE1SPID00,           RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGDE1PROT00,           (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDF1SPID00,           RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGDF1PROT00,           (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDM0SPID00,           RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGDM0PROT00,           (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDM0SPID02,           RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGDM0PROT02,           (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDM0SPID04,           RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGDM0PROT04,           (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDM0SPID06,           RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGDM0PROT06,           (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
        {&FSGDM0SPID08,           RBSYS_ALL_SPIDS_IN_REGISTER},
        {&FSGDM0PROT08,           (RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK)},
      #endif





      /* ********************************************************************************* */
      /* write access guards - init value re-written (for PE PROT) unless stated otherwise */
      /* ********************************************************************************* */
      /* no access to SWSRESA0 etc. for ICUM -- During Startup ICUM write access is required, but at locking time it is locked-out! */
      {&FSGD4ASPID11,             RBSYS_SPID_SAFE_MASK},
      {&FSGD4APROT11,             (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK)}
    };

    static const uint32 RBSYS_PeripheralGuardListNumElements = sizeof(RBSYS_PeripheralGuardList)/sizeof(RBSYS_GuardsList_t);

    static const RBSYS_GuardsList_t RBSYS_LRAMUnusedGuardList[] = {
      // Check if all unused Guards are disabled (register default value) */

      // PEGG0BA = 0; //< used to allow Read Access for Secure SPID (see RBSYS_PEGuardInit)
      // PEGG1BA = 0; //< used to allow Read/Write for SAFE SPID (see RBSYS_PEGuardInit)
      {&PEGG2BA, 0},
      {&PEGG3BA, 0},
      {&PEGG4BA, 0},
      {&PEGG5BA, 0},
      {&PEGG6BA, 0},
      {&PEGG7BA, 0}
    };
    static const uint32 RBSYS_LRAMUnusedGuardListNumElements = sizeof(RBSYS_LRAMUnusedGuardList)/sizeof(RBSYS_GuardsList_t);


    /**
      * @brief Check if Guard HW Registers match the specified values (tuples given by GuardElementPtr)
      *
      * @param GuardElementPtr: Array of Guard Register Configurations
      * @param NumElements:     Length of Array GuardElementPtr
      *
      * @return TRUE if all as expected, FALSE else
      */
    static boolean rbsys_VerifyGuardRegisterSettings(const RBSYS_GuardsList_t* GuardElementPtr, uint32 NumElements)
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

    /**
      * @brief Set guard registers of the passed group and the passed length to the specified values (agreed with GUAM development) in the list
      *
      * @param GuardElementPtr: Array of Guard Register Configurations
      * @param NumElements:     Length of Array GuardElementPtr
      *
      * @return void
      */
    static void rbsys_ConfigurePeripheralGuards(const RBSYS_GuardsList_t* GuardElementPtr, uint32 NumElements)
    {
      uint32 i;

      for(i=0; i<NumElements; i++)
      {
        *(GuardElementPtr[i].Guard_Register) = GuardElementPtr[i].GuardValue;
      }
    }

    void RBSYS_PeripheralGuardInit(void)
    {
      rbsys_ConfigurePeripheralGuards(&RBSYS_PeripheralGuardList[0], RBSYS_PeripheralGuardListNumElements);
    }

    boolean RBSYS_VerifyLRAMGuardSettings(void)
    {
      /* LRAM Guard Settings must be correct if
       *   - access to LRAM Guard is restricted to SAFE SPID only
       *   - LRAM Guards have not been locked before and have not been modified by unsafe Bus Masters
       */
      boolean guardSettingsValid  = rbsys_VerifyGuardRegisterSettings(&RBSYS_LRAMUnusedGuardList[0], RBSYS_LRAMUnusedGuardListNumElements);

      return (guardSettingsValid);
    }

    boolean RBSYS_VerifyGRAMGuardSettings(void)
    {
      /* GRAM Guard Settings must be correct if
       *   - access to GRAM Guard is restricted to SAFE SPID only
       *   - GRAM Guards have not been locked before
       */
      boolean areGuardSettingsWrong  = (RBSYS_GRAMGuardInit_IsPBUSGuardConfigurationInvalid() || RBSYS_GRAMGuardInit_IsGRAMGuardConfigurationPreconditionWrong());

      return (!areGuardSettingsWrong);
    }

    boolean RBSYS_VerifyPeripheralGuardSettings(void)
    {
      boolean guardSettingsValid  = rbsys_VerifyGuardRegisterSettings(&RBSYS_PeripheralGuardList[0], RBSYS_PeripheralGuardListNumElements);

      return guardSettingsValid;
    }



    #if( RBFS_SysExclusiveSPID == RBFS_SysExclusiveSPID_Used )
      #if( RBFS_SysEnvironment == RBFS_SysEnvironment_Target )
        volatile uint32 RBSYS_TrapPermissionHandlingStack[2][2];

        RBSECTION_START_SECTTYPE_NO_SDA
          volatile unsigned int* const RBSYS_TrapPermissionHandlingStack0_StartAddressPtr = &RBSYS_TrapPermissionHandlingStack[0][0];
          volatile unsigned int* const RBSYS_TrapPermissionHandlingStack1_StartAddressPtr = &RBSYS_TrapPermissionHandlingStack[1][0];
        RBSECTION_END_SECTTYPE_NO_SDA
      #endif
    #endif

  #endif // (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
#endif // (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)

/** @} */
/* End ingroup RBSYS */