#include "RBSYS_Config.h"

#if(RBFS_TRBSYSGuardVariance == RBFS_TRBSYSGuardVariance_supported)

// Wrap UnitUnderTest
#include "SystemMemoryProtection/RBSYS_GuardConfigCommon.c"


#if(   RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  #include "SystemMemoryProtection/RenesasP1x/RBSYS_GuardConfigInternalP1x.c"
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  #include "SystemMemoryProtection/RenesasU2A/RBSYS_GuardConfigInternalU2A.c"
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  #include "SystemMemoryProtection/RenesasU2C/RBSYS_GuardConfigInternalU2C.c"
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #include "SystemMemoryProtection/STMStellar/RBSYS_GuardConfigInternalStellar.c" //< todo: provide Unittests once file contains something
#endif



// Access API for private variables and functions
#include "TRBSYS_GuardConfig_Adaptor.h"
#include "TRBSYS_CpuInfo.h"
#include "RBSYS_CoreInit.h"



/* ************************************************ */
/*    indirect calls to achieve coverage reporting  */
/* ************************************************ */

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  void call_RBSYS_setCoreSPID(uint32 nSPID)
  {
    RBSYS_setCoreSPID((RBSYSspid_t) nSPID);
  }

  uint32 call_RBSYS_getCoreSPID(void)
  {
    return ((uint32)RBSYS_getCoreSPID());
  }
#endif


#if( RBFS_SysEnvironment == RBFS_SysEnvironment_Target )
  void call_RBSYS_PEGuardInit(void)
  {
    RBSYS_PEGuardInit();
  }
#endif

#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )

  void call_RBSYS_PBUSGuardInit(void)
  {
    RBSYS_PBUSGuardInit();
  }

  void RBSYS_setCoreSPID2SafeSPID(void)
  {
    /* original function is implemented in asm and therefore has to be stubbed */
  }


  void RBSYS_PEGuardInit(void)
  {
    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      PEGG0MK = 0x003FF000u;
      PEGG0SP = RBSYS_SPID_SECURE_MASK;
      PEGG0BA = (0xFE800000u | RBSYS_PEG_READ_ACCESS | RBSYS_PEG_ENABLE);
      PEGG1MK = 0x003FF000u;
      PEGG1SP = RBSYS_SPID_SAFE_MASK;
      PEGG1BA = (0xFE800000u | RBSYS_PEG_WRITE_ACCESS | RBSYS_PEG_READ_ACCESS | RBSYS_PEG_ENABLE);
      /* PEGuard configuration is written in ASM and therefore cannot be checked. Mock is not required as well because
        there is no verification routine for these Guard settings. The correct settings is assured by System Design
        (setting of parent guard is done before setting of child guard). */
    #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      /* PEGuard configuration is written in ASM and therefore cannot be checked. Mock is not required as well because
        there is no verification routine for these Guard settings. The correct settings is assured by System Design
        (setting of parent guard is done before setting of child guard). */
      if (RBSYS_getCoreID() == RBSYS_CORE_ID_0)
      {
        /** PE0 Guard for LRAM 0xFDC00000 to 0xFDC0FFFF (+ PE0.INTC1) */
        /*  Attention: allow read for all bus masters -> needed by HSM */
        // RBSYS_UnlockAccessToHwModule(&GUARD_PE0CL0PEGKCPROT);                                           // enable writing protected registers
        GUARD_PE0CL0PEGSPID0  = RBSYS_SPID_SAFE_MASK;
        GUARD_PE0CL0PEGPROT0  = 0x00000151;
        GUARD_PE0CL0PEGBAD0   = 0x01C00000;                                                             // access base address for LRAM 0
        GUARD_PE0CL0PEGADV0   = 0x03FF0000;                                                             // access address valid bits -> all

        /** Guard PE0 INTC1 */
        GUARD_PE0CL0PEGSPID1  = RBSYS_SPID_SAFE_MASK;
        GUARD_PE0CL0PEGPROT1  = 0x00000151;
        GUARD_PE0CL0PEGBAD1   = 0x03FC4000;                                                             // access base address for INTC1
        GUARD_PE0CL0PEGADV1   = 0x03FFC000;                                                             // access address valid bits -> 16KB

        // RBSYS_LockAccessToHwModule(&GUARD_PE0CL0PEGKCPROT);                                             // disable writing protected registers
      }
      else
      {
        /** PE1 Guard for LRAM 0xFDA00000 to 0xFDA0FFFF (+ PE1.INTC1) */
        /*  Attention: allow read for all bus masters -> needed by HSM */
        // RBSYS_UnlockAccessToHwModule(&GUARD_PE1CL0PEGKCPROT);                                           // enable writing protected registers
        GUARD_PE1CL0PEGSPID0  = RBSYS_SPID_SAFE_MASK;
        GUARD_PE1CL0PEGPROT0  = 0x00000151;
        GUARD_PE1CL0PEGBAD0   = 0x01C00000;                                                             // access base address for LRAM 1
        GUARD_PE1CL0PEGADV0   = 0x03FF0000;                                                             // access address valid bits -> all

        /** Guard PE1 INTC1 */
        GUARD_PE1CL0PEGSPID1  = RBSYS_SPID_SAFE_MASK;
        GUARD_PE1CL0PEGPROT1  = 0x00000151;
        GUARD_PE1CL0PEGBAD1   = 0x03FC4000;                                                             // access base address for INTC1
        GUARD_PE1CL0PEGADV1   = 0x03FFC000;                                                             // access address valid bits -> 16KB

        // RBSYS_LockAccessToHwModule(&GUARD_PE1CL0PEGKCPROT);                                             // disable writing protected registers
      }
    #endif
  }

  void RBSYS_PBUSGuardInit_ForPEGuard(void)
  {
    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      /* original function is implemented in asm and therefore has to be stubbed */
      FSGD3ASPID03 = RBSYS_SPID_SAFE_MASK;
      FSGD3APROT03 = (RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK);
    #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      rbsys_InitializeGuards(rbsys_PBusGuardConfigs_ForPEGuard, sizeof(rbsys_PBusGuardConfigs_ForPEGuard)/sizeof(RBSYS_BUSGuardConfig_t));
    #endif
  }

#else //< RBFS_uCFamily != RBFS_uCFamily_STMStellar

  void RBSYS_LRAMGuardInit(void)
  {
    uint32 slavepctlr = RBSYS_MRC(15,0,11,0,0);
    slavepctlr |= 0x3;
    RBSYS_MCR(15,0,slavepctlr,11,0,0);

    if( RBSYS_getCoreID() == RBSYS_CORE_ID_0 )
    {
      RBSYS_MCR(15, 0, C0_CPU0_tcma_start, 9, 1, 0);
      RBSYS_MCR(15, 0, C0_CPU0_tcmb_start, 9, 1, 1);
      RBSYS_MCR(15, 0, C0_CPU0_tcmc_start, 9, 1, 2);
    }
    else /* RBSYS_CORE_ID_1 */
    {
      RBSYS_MCR(15, 0, C0_CPU1_tcma_start, 9, 1, 0);
      RBSYS_MCR(15, 0, C0_CPU1_tcmb_start, 9, 1, 1);
      RBSYS_MCR(15, 0, C0_CPU1_tcmc_start, 9, 1, 2);
    }
  }
  #warning("GuardConfig does not test variant STMStellar yet.")

#endif

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  uint32 TRBSYS_GetNumOfPBUSGuards(void)
  {
    return sizeof(rbsys_PBusGuardConfigs)/sizeof(RBSYS_BUSGuardConfig_t);
  }
  const RBSYS_BUSGuardConfig_t* TRBSYS_GetPBUSGuardsPointer(void)
  {
    return rbsys_PBusGuardConfigs;
  }
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  void TRBSYS_Callrbsys_NOCFirewallConfigure(const TRBSYS_NOCFirewallConfig_t* config)
  {
    rbsys_NOCFirewallConfigure((RBSYS_NOCFirewallConfig_t*)config);
  }

  void TRBSYS_GuardConfig_InvalidRegionTypeConfiguration(void)
  {
    static const RBSYS_NOCFirewallRegionConfig_t rbsys_Cluster0_FirewallRegions[] =  RBSYS_FIREWALL_REGIONS_WHOLE_ADDRESS_SPACE(RBSYS_NOCRegionType_OtherMemorySafeAndUnsafe);
    RBSYS_NOCFirewallCfg(Cluster0, RBSYS_NOCTarget_Cluster0Backdoor);
    rbsys_NOCFirewallConfigure(&rbsys_Cluster0_Firewall);
  }
#endif


#endif
