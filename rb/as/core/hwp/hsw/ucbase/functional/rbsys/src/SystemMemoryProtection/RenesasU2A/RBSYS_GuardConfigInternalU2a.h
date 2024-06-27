#ifndef RBSYS_GUARDCONFIGINTERNALU2A_H__
#define RBSYS_GUARDCONFIGINTERNALU2A_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file  RBSYS_GuardConfigInternalU2A.h
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


/* used interfaces */
#include "RBSYS_uCRegisters.h"
#include "RBSYS_GuardMemoryMap.h"
#include "RBSYS_GuardConfig.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_CpuInfo.h"
#include "RBLCF_MemoryRemap.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                          RBFS_TargetDevice_RenesasD7,
                          RBFS_TargetDevice_RenesasM2,
                          RBFS_TargetDevice_RenesasM3,
                          RBFS_TargetDevice_RenesasM6);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHsmSharedGRAMsize,
                          RBFS_SysHsmSharedGRAMsize_0K,
                          RBFS_SysHsmSharedGRAMsize_16K,
                          RBFS_SysHsmSharedGRAMsize_32K);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RestrictedExclusiveGRAMsize,
                          RBFS_RestrictedExclusiveGRAMsize_0K,
                          RBFS_RestrictedExclusiveGRAMsize_16K,
                          RBFS_RestrictedExclusiveGRAMsize_64K,
                          RBFS_RestrictedExclusiveGRAMsize_32K,
                          RBFS_RestrictedExclusiveGRAMsize_128K,
                          RBFS_RestrictedExclusiveGRAMsize_256K);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHSMsharedGRAM,
                          RBFS_SysHSMsharedGRAM_Host,
                          RBFS_SysHSMsharedGRAM_Restricted);

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

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysExclusiveSPID,
                          RBFS_SysExclusiveSPID_Used,
                          RBFS_SysExclusiveSPID_NotUsed);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                          RBFS_SysEnvironment_Target,
                          RBFS_SysEnvironment_Simulation);

RB_ASSERT_SWITCH_SETTINGS(RBFS_EmulationDevice,
                          RBFS_EmulationDevice_None,
                          RBFS_EmulationDevice_RenesasD7ED,
                          RBFS_EmulationDevice_RenesasM6ED);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TraceMeasurement,
                          RBFS_TraceMeasurement_RuntimeConfigurable,
                          RBFS_TraceMeasurement_uCdependent);


typedef struct
{
  volatile uint32 *    Guard_Register;
  uint32               GuardValue;
} RBSYS_GuardsList_t;

/**
  * \brief Verifies if the PE Guards and the CSG Guards are set as desired. Background: Setting could have
  *        gone wrong if the Guards have already been locked
  *
  * \return Returns TRUE if the setting is Ok, else FALSE
  */
extern boolean RBSYS_VerifyFinalSPIDandPEGandCSGGuardSettings(void);



#if( RBFS_SysEnvironment == RBFS_SysEnvironment_Target )

  /**
   * @brief Set Core SPID to SAFE
   *
   * (see also RBSYS_setCoreSPID)
   * Setting the Core SPID to SAFE must be done in ASM because this is done before setting up the stack pointer.
   *
   * @return void
   */
  static void RBSYS_setCoreSPID2SafeSPID(void);
  asm void RBSYS_setCoreSPID2SafeSPID(void)
  {
    stsr 0,r16,1         -- r16 = SPID
    mov -32,r7           -- r7 = 0xFFFFFFE0
    and r7,r16           -- r16 &= r7
    ori 2,r16,r16        -- r16 |= 0x2   (SafeSPID)
    ldsr r16,0,1         -- SPID = r16
    syncp
    synci
  }
#else
  /* Declare assembly function as extern so that it can be stubbed in x86 testing */
  extern void RBSYS_setCoreSPID2SafeSPID(void);
#endif

/**
 * @brief Set Core SPID (system protection identifier)
 *
 * RH850 hardware restrictions on Renesas P1x family:
 *  - SPID 0..1 is reserved in hardware for ICU-M (security core).
 *    This means, that it is not possible for PEs to write "0" or "1" to SPID.
 *    If written, these value is "2".
 *  - SPID 2..31 could be used by all other bus masters.
 *
 * CC-AS SPID concept (see RBSYSspid_t):
 *   All safe bus masters will get the same SPID and all unsafe bus masters will get also a same SPID.
 *   So in general we differ only between safe, unsafe and secure bus masters.
 *
 * Attention: Has to be inline as it is used during PreOSPhase0 before Stack Pointer initialization
 *
 * @param nSPID defines the new system protection identifier
 *
 * @return void
 */
__attribute__((always_inline)) static inline void RBSYS_setCoreSPID(RBSYSspid_t nSPID)
{
  unsigned int spid;
  spid  = RBSYS_STSR(0, 1);         // read System register 0, 1 - SPID (System Protection Identifier)
  spid &= 0xFFFFFFE0u;              // mask old SPID (bit 4 to 0)
  spid |= (unsigned int)(nSPID);                  // set new SPID

  RBSYS_LDSR(0, 1, spid);           // write System register 0, 1 - SPID (System Protection Identifier)

  // introduce sync instructions after updating SPID.SPID as requested within the UM (see chapter "System Register Hazards")
  RBSYS_SYNCP();
  RBSYS_SYNCI();
}


/**
 * This function returns the current Core SPID (system protection identifier)
 *
 * @return SPID
 */
static inline RBSYSspid_t RBSYS_getCoreSPID(void)
{
  unsigned int spid = RBSYS_STSR(0, 1);                   // read System register 0, 1 - SPID (System Protection Identifier)
  spid &= 0x1Fu;                                          // mask out SPID (bit 4 to 0)

  return (RBSYSspid_t)spid;
}

  typedef struct
  {
    volatile uint32 *SPID_Register;
    const    uint32  SPID_Mask;
    volatile uint32 *PROT_Register;
    const    uint32  PROT_Setting;
    volatile uint32 *KCPROT_Register;
  } RBSYS_BUSGuardConfig_t;

  /** \brief RBSYS-internal helper function to configure a list of guards */
  __attribute__((always_inline)) static inline void rbsys_InitializeGuards(const RBSYS_BUSGuardConfig_t* const configs, uint32 len)
  {
    uint32 i;
    for( i=0; i<len; i++)
    {
      RBSYS_UnlockAccessToHwModule(configs[i].KCPROT_Register);
      *configs[i].SPID_Register   = configs[i].SPID_Mask;
      *configs[i].PROT_Register   = configs[i].PROT_Setting;
      RBSYS_LockAccessToHwModule(configs[i].KCPROT_Register);
    }
  }

  static inline boolean rbsys_VerifyGuardSettings(const RBSYS_BUSGuardConfig_t* const configs, uint32 len)
  {
    boolean isGuardSettingOk = TRUE;

    uint32 i;
    for( i=0; i<len; i++)
    {
      boolean isSPIDCorrupted, isPROTCorrupted, isKCPROTCorrupted;

      /* Compare register value to requested value */
      isSPIDCorrupted   = (*configs[i].SPID_Register != configs[i].SPID_Mask);
      isPROTCorrupted   = (*configs[i].PROT_Register != configs[i].PROT_Setting);
      isKCPROTCorrupted = (*configs[i].KCPROT_Register != 0x00000000u);

      if( isSPIDCorrupted || isPROTCorrupted || isKCPROTCorrupted )
      {
        isGuardSettingOk = FALSE;
      }
    }

    return isGuardSettingOk;
  }

  /**  Explanation: If you want to enable read for DMA:
    *     configure SPID = SAFE & !DMA + restrict Write Requests
    *     => This will forbid DMA Write Access and implicitely allow Read access
    *
    *  Explanation: If you want to enable write for DMA:
    *     configure SPID = SAFE | DMA + restrict read and write operations
    *     => This will exlicitly allow DMA Write and Read Accesses
    *      ===== ALTHOUGH Read may not be needed!!! ====
    */

  #define RBSYS_GUARD_READ_EN    ((uint32) 1u<<0)
  #define RBSYS_GUARD_WRITE_EN   ((uint32) 1u<<1)
  #define RBSYS_GUARD_UM_ACC_EN  ((uint32) 1u<<4)
  #define RBSYS_GUARD_DEBUG_EN   ((uint32) 1u<<6)
  #define RBSYS_GUARD_EN         ((uint32) 1u<<8)
  #define RBSYS_GUARD_MPIDOff    (16u) // used by DTS-/sDMAC-/INTC2-

  /* Guards may only be locked inside the Application. Reason: Application may overwrite the Guard settings given by Bootblock */
  #if( RBFS_HexBlockBuild != RBFS_HexBlockBuild_APPLICATION )
    #define RBSYS_PROT_EnLock     (RBSYS_GUARD_DEBUG_EN | RBSYS_GUARD_EN | RBSYS_GUARD_UM_ACC_EN)
    #define RBSYS_PROT_EnReadLock (RBSYS_GUARD_READ_EN | RBSYS_PROT_EnLock)
  #else
    #define RBSYS_GUARD_LOCK      ((uint32) 1u<<31)
    #define RBSYS_PROT_EnLock     (RBSYS_GUARD_DEBUG_EN | RBSYS_GUARD_EN | RBSYS_GUARD_LOCK | RBSYS_GUARD_UM_ACC_EN)
    #define RBSYS_PROT_EnReadLock (RBSYS_GUARD_READ_EN | RBSYS_PROT_EnLock)
  #endif

  /**
  * @brief Set SPID for all Bus Masters (e.g. system protection identifier for Flexray, Ethernet, RHSIF, ICUM, ...)
  *
  * - SPID mask is initialized for all Bus Masters and locked to prevent further modification.
  * - SPID is initialized for all Bus Masters (except DTS and CPUs - which will initialize it on their own)
  *
  * @return void
  */
  static inline void RBSYS_SetBusMasterIDs(void)
  {
    /* SPID Masking: SPID Module will inhibit that the modules (e.g. DMA) set their SPID to a prohibited SPID (decided by SPID-Mask) */
    RBSYS_UnlockAccessToHwModule(&SPIDCTLSPIDKCPROT);

    /** Set Bus Master SPIDs */
    #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasM2 ) //< GbEthernet, RHSIF0 and Flexray1 are not implemented on M2
      SPIDCTLBM17SPID = (uint32)UnSafeSPID;           // GBit Ethernet
      SPIDCTLBM19SPID = (uint32)UnSafeSPID;           // RHSIF0
      SPIDCTLBM22SPID = (uint32)UnSafeSPID;           // FlexRay1
    #endif
    SPIDCTLBM23SPID = (uint32)UnSafeSPID;           // FlexRay0
    SPIDCTLBM24SPID = (uint32)UnSafeSPID;           // Fast Ethernet
    SPIDCTLBM25SPID = (uint32)SecureSPID_AESEngine; // ICUM_AES0
    SPIDCTLBM26SPID = (uint32)SecureSPID;           // ICUM_HA
    /* Attention: Some BusMaster can change their SPID (e.g. CPU) or their SPIDs are stored inside the respective module (e.g. DMA) -> covered by SPID Masking below */

    /** Set Allowed Bus Master SPIDs */
    SPIDCTLBM00SPIDMSK = (1u<<SafeSPID) | (1u<<RestrictedSPID); // CPU0
    SPIDCTLBM01SPIDMSK = (1u<<SafeSPID) | (1u<<RestrictedSPID); // CPU1
    #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) )     //< Core 2/3 are only available on D7
      SPIDCTLBM02SPIDMSK = 0u;                                  // CPU2 -> unused
      SPIDCTLBM03SPIDMSK = 0u;                                  // CPU3 -> unused
    #endif
    #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasM2 ) //< GbEthernet, RHSIF0 and Flexray1 are not implemented on M2
      SPIDCTLBM17SPIDMSK = (1u<<UnSafeSPID);              // GBit Ethernet
      SPIDCTLBM19SPIDMSK = (1u<<UnSafeSPID);              // RHSIF0
      SPIDCTLBM22SPIDMSK = (1u<<UnSafeSPID);              // FlexRay1
    #endif
    SPIDCTLBM23SPIDMSK = (1u<<UnSafeSPID);              // FlexRay0
    SPIDCTLBM24SPIDMSK = (1u<<UnSafeSPID);              // Fast Ethernet
    SPIDCTLBM25SPIDMSK = RBSYS_SPID_SECURE_SPIDs;       // ICUM_AES0 - 0 of HSM is inactive
    SPIDCTLBM26SPIDMSK = RBSYS_SPID_SECURE_SPIDs;       // ICUMHA    - 0 of HSM is inactive
    SPIDCTLBM27SPIDMSK = (1u<<DmaUnsafeSPID);           // sDMAC1
    SPIDCTLBM28SPIDMSK = (1u<<DmaUnsafeSPID);           // sDMAC0
    SPIDCTLBM29SPIDMSK = (1u<<SafeSPID);                // DTS
    #if( (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD7ED) || (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasM6ED) )
      SPIDCTLBM30SPIDMSK = RBSYS_SPID_Measurement_MASK; // AUD - Advanced User Debugger - 0 if Measurement is inactive
    #endif
    SPIDCTLBM31SPIDMSK = RBSYS_SPID_Measurement_MASK;   // MAU - Memory Access Unit     - 0 if Measurement is inactive

    /** Lock Allowed Bus Master SPIDs */
    SPIDCTLBM00SPIDMSKLOCK = 0x01u;
    SPIDCTLBM01SPIDMSKLOCK = 0x01u;
    #if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6)) //< Core 2/3 are only available on D7
      SPIDCTLBM02SPIDMSKLOCK = 0x01u;
      SPIDCTLBM03SPIDMSKLOCK = 0x01u;
    #endif
    #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasM2 ) //< GbEthernet, RHSIF0 and Flexray1 are not implemented on M2
      SPIDCTLBM17SPIDMSKLOCK = 0x01u;
      SPIDCTLBM19SPIDMSKLOCK = 0x01u;
      SPIDCTLBM22SPIDMSKLOCK = 0x01u;
    #endif
    SPIDCTLBM23SPIDMSKLOCK = 0x01u;
    SPIDCTLBM24SPIDMSKLOCK = 0x01u;
    SPIDCTLBM25SPIDMSKLOCK = 0x01u;
    SPIDCTLBM26SPIDMSKLOCK = 0x01u;
    SPIDCTLBM27SPIDMSKLOCK = 0x01u;
    SPIDCTLBM28SPIDMSKLOCK = 0x01u;
    SPIDCTLBM29SPIDMSKLOCK = 0x01u;
    #if( (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD7ED) || (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasM6ED) )
      SPIDCTLBM30SPIDMSKLOCK = 0x01u;
    #endif
    SPIDCTLBM31SPIDMSKLOCK = 0x01u;

    RBSYS_LockAccessToHwModule(&SPIDCTLSPIDKCPROT);
  }

  /** \brief Configures all HBUS Guards */
  extern void RBSYS_HBusGuardInit(void);

  /** \brief Verifies the setting of all HBUS Guards */
  extern boolean RBSYS_VerifyFinalHBUSGuardSettings(void);


#define RBSYS_GUARD_DefaultMPID0 ( ((uint32)1u<<RBSYS_GUARD_MPIDOff) | RBSYS_GUARD_EN | RBSYS_GUARD_DEBUG_EN | RBSYS_GUARD_UM_ACC_EN | RBSYS_GUARD_READ_EN )

/** \brief Configures all Interrupt Controller related guards */
static inline void RBSYS_INTCGuardInit(void)
{
    uint32 i;

    RBSYS_UnlockAccessToHwModule(&GUARD_INTC2INTC2GKCPROT);
    GUARD_INTC2INTC2GMPID0 = SafeSPID;
    GUARD_INTC2INTC2GPROT_GR = RBSYS_GUARD_DefaultMPID0;  // Global Registers
    GUARD_INTC2INTC2GPROT_IMR = RBSYS_GUARD_DefaultMPID0; // Interrupt Mask Registers
    for(i=32; i<=767; i++) // see Table 44.343 @ R01UH0820EJ0060 HW User Manual
    {
      RBSYS_INTC2INTC2GPROT_n[i] = RBSYS_GUARD_DefaultMPID0;
    }
    RBSYS_LockAccessToHwModule(&GUARD_INTC2INTC2GKCPROT);

}

/** \brief Configures all IBUS related guards */
static inline void RBSYS_IBusGuardInit(void)
{
    /** Barrier Sync Guard  - currently not used, therefore set to RBSYS_SPID_SAFE_MASK */
    uint32 i;

    #define RBSYS_IBUSGuard_PROT0_DEFAULT (RBSYS_GUARD_EN | RBSYS_GUARD_DEBUG_EN | RBSYS_GUARD_UM_ACC_EN | RBSYS_GUARD_READ_EN)

    RBSYS_UnlockAccessToHwModule(&GUARD_BARRBRGKCPROT);
    for( i=0; i<16; i++ )
    {
      RBSYS_BARRBRG[i].PROT0 = RBSYS_IBUSGuard_PROT0_DEFAULT;
      RBSYS_BARRBRG[i].PROT1 = RBSYS_SPID_SAFE_MASK;
    }
    GUARD_BARRBRGPROT0_16 = RBSYS_IBUSGuard_PROT0_DEFAULT;
    GUARD_BARRBRGPROT1_16 = RBSYS_SPID_SAFE_MASK;
    RBSYS_LockAccessToHwModule(&GUARD_BARRBRGKCPROT);


    // IPIR Guard (Interprocessor Interrupt function)
    RBSYS_UnlockAccessToHwModule(&GUARD_IPIRIPIGKCPROT);
    // IPIR Guard for Core 0
    GUARD_IPIRIPIGPROT1_R0 = RBSYS_SPID_SAFE_MASK;
    GUARD_IPIRIPIGPROT0_R0 = RBSYS_IBUSGuard_PROT0_DEFAULT;
    GUARD_IPIRIPIGPROT1_T0 = RBSYS_SPID_SAFE_MASK;
    GUARD_IPIRIPIGPROT0_T0 = RBSYS_IBUSGuard_PROT0_DEFAULT;
    // IPIR Guard for Core 1
    GUARD_IPIRIPIGPROT1_R1 = RBSYS_SPID_SAFE_MASK;
    GUARD_IPIRIPIGPROT0_R1 = RBSYS_IBUSGuard_PROT0_DEFAULT;
    GUARD_IPIRIPIGPROT1_T1 = RBSYS_SPID_SAFE_MASK;
    GUARD_IPIRIPIGPROT0_T1 = RBSYS_IBUSGuard_PROT0_DEFAULT;
    #if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6)) //< todo! see https://sbta.renesas.eu/mantis_bosch/view.php?id=8909
      // IPIR Guard for Core 2
      GUARD_IPIRIPIGPROT1_R2 = RBSYS_SPID_SAFE_MASK;
      GUARD_IPIRIPIGPROT0_R2 = RBSYS_IBUSGuard_PROT0_DEFAULT;
      GUARD_IPIRIPIGPROT1_T2 = RBSYS_SPID_SAFE_MASK;
      GUARD_IPIRIPIGPROT0_T2 = RBSYS_IBUSGuard_PROT0_DEFAULT;
      // IPIR Guard for Core 3
      GUARD_IPIRIPIGPROT1_R3 = RBSYS_SPID_SAFE_MASK;
      GUARD_IPIRIPIGPROT0_R3 = RBSYS_IBUSGuard_PROT0_DEFAULT;
      GUARD_IPIRIPIGPROT1_T3 = RBSYS_SPID_SAFE_MASK;
      GUARD_IPIRIPIGPROT0_T3 = RBSYS_IBUSGuard_PROT0_DEFAULT;
    #endif

    // IPIR Guard for Common Registers
    GUARD_IPIRIPIGPROT1_4 = RBSYS_SPID_SAFE_MASK;
    GUARD_IPIRIPIGPROT0_4 = RBSYS_IBUSGuard_PROT0_DEFAULT;
    RBSYS_LockAccessToHwModule(& GUARD_IPIRIPIGKCPROT);


    /** TPTM Guard (Timing Protection Timer Module) */
    RBSYS_UnlockAccessToHwModule(&GUARD_TPTMTPTGKCPROT);
    GUARD_TPTMTPTGPROT1_0 = RBSYS_SPID_SAFE_MASK;
    GUARD_TPTMTPTGPROT0_0 = RBSYS_IBUSGuard_PROT0_DEFAULT;
    GUARD_TPTMTPTGPROT1_1 = RBSYS_SPID_SAFE_MASK;
    GUARD_TPTMTPTGPROT0_1 = RBSYS_IBUSGuard_PROT0_DEFAULT;
    #if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6)) //< Core 2/3 are only available on D7
      GUARD_TPTMTPTGPROT1_2 = RBSYS_SPID_SAFE_MASK;
      GUARD_TPTMTPTGPROT0_2 = RBSYS_IBUSGuard_PROT0_DEFAULT;
      GUARD_TPTMTPTGPROT1_3 = RBSYS_SPID_SAFE_MASK;
      GUARD_TPTMTPTGPROT0_3 = RBSYS_IBUSGuard_PROT0_DEFAULT;
    #endif
    GUARD_TPTMTPTGPROT1_8 = RBSYS_SPID_SAFE_MASK;
    GUARD_TPTMTPTGPROT0_8 = RBSYS_IBUSGuard_PROT0_DEFAULT;
    GUARD_TPTMTPTGPROT1_9 = RBSYS_SPID_SAFE_MASK;
    GUARD_TPTMTPTGPROT0_9 = RBSYS_IBUSGuard_PROT0_DEFAULT;
    RBSYS_LockAccessToHwModule(&GUARD_TPTMTPTGKCPROT);
}

/** \brief Configures all DMA Guards - Only Safe Bus Masters shall be able to configure the DMA modules */
static inline void RBSYS_DMAGuardInit(void)
{
    uint32 i;

    /** DTS / sDMAC: Safe only */
    /** ----------------- sDMAC0 ----------------- */
    RBSYS_UnlockAccessToHwModule(&GUARD_DMAC0DMAGKCPROT);
    GUARD_DMAC0DMAGMPID0 = SafeSPID;
    GUARD_DMAC0DMAGPROT_GR = RBSYS_GUARD_DefaultMPID0;
    GUARD_DMAC0DMAGPROT_DP = RBSYS_GUARD_DefaultMPID0;
    for(i=0; i<16; i++)
    {
      RBSYS_DMAC0DMAGPROT_n[i] = RBSYS_GUARD_DefaultMPID0;
    }
    RBSYS_LockAccessToHwModule(&GUARD_DMAC0DMAGKCPROT);
    /** ----------------- sDMAC1 ----------------- */
    RBSYS_UnlockAccessToHwModule(&GUARD_DMAC1DMAGKCPROT);
    GUARD_DMAC1DMAGMPID0 = SafeSPID;
    GUARD_DMAC1DMAGPROT_GR = RBSYS_GUARD_DefaultMPID0;
    GUARD_DMAC1DMAGPROT_DP = RBSYS_GUARD_DefaultMPID0;
    for(i=0; i<16; i++)
    {
      RBSYS_DMAC1DMAGPROT_n[i] = RBSYS_GUARD_DefaultMPID0;
    }
    RBSYS_LockAccessToHwModule(&GUARD_DMAC1DMAGKCPROT);

    /** ----------------- DTS ----------------- */
    RBSYS_UnlockAccessToHwModule(&GUARD_DTSDTSGKCPROT);
    GUARD_DTSDTSGMPID0 = SafeSPID;
    GUARD_DTSDTSGPROT_GR = RBSYS_GUARD_DefaultMPID0;
    for(i=0; i<128; i++)
    {
      RBSYS_DTSDTSGPROT_n[i] = RBSYS_GUARD_DefaultMPID0;
    }
    RBSYS_LockAccessToHwModule(&GUARD_DTSDTSGKCPROT);
}




#if( RBFS_SysEnvironment == RBFS_SysEnvironment_Target )
  /**
  * @brief Set PE Guard
  *
  * Each PE has a guard that controls the access to the local RAM. Eight regions are available per PE
  * to configure access by other bus masters. After reset, region 0 is enabled and allows read only access
  * to local RAM by SPID 0 and 1 (HSM).
  *
  * In case regions have overlapping address ranges, the resulting access permission is a union of the
  * individual permissions. For example, if one region allows access for SPID 1 only, and the other one for
  * SPID 2 only, the overlapping address ranges can be accessed by SPID 1 and 2.
  *
  * Setting up these Guards must be done in ASM because this is done before setting up the stack pointer.
  *
  * Hint: PEGuards are not opened for Restricted SPID because one Core can always access its own LRAM. A Core shall
  *       not be able to access another Core's LRAM while executing with Restricted SPID.
  *
  * @param void
  *
  * @return void
  */
  static void RBSYS_PEGuardInit(void);
  asm void RBSYS_PEGuardInit(void)
  {
%lab PEGuardInitPE0, %lab PEGuardInitPE1, %lab Exit

    mov 0xA5A5A501, r27     -- KCPROT Enable Write Access
    mov 0xA5A5A500, r28     -- KCPROT Disable Write Access
  #if( (RBFS_EmulationDevice != RBFS_EmulationDevice_None) || (RBFS_TraceMeasurement == RBFS_TraceMeasurement_RuntimeConfigurable) )
    mov 0xC0000004,r15      -- Safe SPID Mask (1<<2) and Trace Measurement Modules SPIDs
  #else
    mov 0x00000004,r15      -- Safe SPID Mask (1<<2)
  #endif
    mov 0x00000151,r16      -- PROT: RBSYS_PEG_EN | RBSYS_PEG_DBG_EN | RBSYS_PEG_UM_EN | RBSYS_PEG_RD_EN

    -- check core ID
    stsr 0,r12,2
    cmp zero,r12
    bne PEGuardInitPE1  -- if( CoreID != 0 ) goto PEGuardInitPE1; else continue

  PEGuardInitPE0:
    mov 0xFFC6C000, ep

    -- Disable Write Protection for Core 0 PEG
    sst.w r27, 0[ep]
    syncm

    -- Setup Guards: LRAM
    mov 0x01C00000, r17
    sst.w r17, 72[ep]      -- PE0CL0PEGBAD0  = 0x01C00000
    mov 0x03FF0000, r17
    sst.w r17, 76[ep]      -- PE0CL0PEGADV0  = 0x03FF0000u
    sst.w r15, 68[ep]      -- PE0CL0PEGSPID0 = Safe
    sst.w r16, 64[ep]      -- PE0CL0PEGPROT0 = RBSYS_PEG_EN | RBSYS_PEG_DBG_EN | RBSYS_PEG_UM_EN | RBSYS_PEG_RD_EN

    -- Setup Guards: INTC1
    mov 0x03FC4000, r17
    sst.w r17, 88[ep]      -- PE0CL0PEGBAD1  = 0x03FC4000
    mov 0x03FFC000, r17
    sst.w r17, 92[ep]      -- PE0CL0PEGADV1  = 0x03FFC000u
    sst.w r15, 84[ep]      -- PE0CL0PEGSPID1 = Safe
    sst.w r16, 80[ep]      -- PE0CL0PEGPROT1 = RBSYS_PEG_EN | RBSYS_PEG_DBG_EN | RBSYS_PEG_UM_EN | RBSYS_PEG_RD_EN

    -- Enable Write Protection
    sst.w r28, 0[ep]
    syncm

    br Exit


  PEGuardInitPE1:
    mov 0xFFC6C100, ep

    -- Disable Write Protection for Core 1 PEG
    sst.w r27, 0[ep]
    syncm

    -- Setup Guards: LRAM
    mov 0x01A00000, r17
    sst.w r17, 72[ep]      -- PE1CL0PEGBAD0  = 0x01A00000
    mov 0x03FF0000, r17
    sst.w r17, 76[ep]      -- PE1CL0PEGADV0  = 0x03FF0000u
    sst.w r15, 68[ep]      -- PE1CL0PEGSPID0 = Safe
    sst.w r16, 64[ep]      -- PE1CL0PEGPROT0 = RBSYS_PEG_EN | RBSYS_PEG_DBG_EN | RBSYS_PEG_UM_EN | RBSYS_PEG_RD_EN

    -- Setup Guards: INTC1
    mov 0x03FC8000, r17
    sst.w r17, 88[ep]      -- PE1CL0PEGBAD1  = 0x03FC8000
    mov 0x03FFC000, r17
    sst.w r17, 92[ep]      -- PE1CL0PEGADV1  = 0x03FFC000u
    sst.w r15, 84[ep]      -- PE1CL0PEGSPID1 = Safe
    sst.w r16, 80[ep]      -- PE1CL0PEGPROT1 = RBSYS_PEG_EN | RBSYS_PEG_DBG_EN | RBSYS_PEG_UM_EN | RBSYS_PEG_RD_EN

    -- Enable Write Protection
    sst.w r28, 0[ep]
    syncm

    br Exit

  Exit:
    syncm                 -- assure that all memory writes are finished
  }
#else
  /* Declare assembly function as extern so that it can be stubbed in x86 testing */
  extern void RBSYS_PEGuardInit(void);
#endif


  #define RBSYS_SPID_REG(PBUSGuard_Group, PBUSGuard_Channel) PBUSGuard_Group##PBGPROT1_##PBUSGuard_Channel
  #define RBSYS_SPID_REGAddr(PBUSGuard_Group, PBUSGuard_Channel) (&PBG##PBUSGuard_Group##PBGPROT1_##PBUSGuard_Channel)
  #define RBSYS_PROT_REG(PBUSGuard_Group, PBUSGuard_Channel) PBUSGuard_Group##PBGPROT0_##PBUSGuard_Channel
  #define RBSYS_PROT_REGAddr(PBUSGuard_Group, PBUSGuard_Channel) (&PBG##PBUSGuard_Group##PBGPROT0_##PBUSGuard_Channel)
  #define RBSYS_KCPROT_REGAddr(PBUSGuard_Group) (&PBGERRSLV##PBUSGuard_Group##PBGKCPROT)


  extern boolean RBSYS_VerifyFinalPBUSGuardSettings(void);


#if( RBFS_SysEnvironment == RBFS_SysEnvironment_Target )
  /**
  * @brief Setup PBUS Guards to protect other Guard configurations
  *
  * - Access to LRAM Guards has to be restricted
  * - Access to SPIDs has to be restricted
  *
  * Hint:
  *  - Core 0 will setup PBG01.0, PBG01.2, PBG01.3, PBG90.3 (PEG for Core0,2,3 and SPIDCTL)
  *  - Core 1 will setup PBG01.1 (PEG for Core 1)
  *
  * Attention: This function shall be called on both Cores! This function can be called in parallel on both Cores
  *            -> considered in design!
  *
  * Setting up these Guards must be done in ASM because this is done before setting up the stack pointer.
  *
  * @param void
  *
  * @return void
  */
  static void RBSYS_PBUSGuardInit_ForPEGuard(void);
  asm void RBSYS_PBUSGuardInit_ForPEGuard(void)
  {
%lab Core0 %lab Core1 %lab Exit

    mov 0xA5A5A501, r27     -- KCPROT Enable Write Access
    mov 0xA5A5A500, r28     -- KCPROT Disable Write Access
  #if( (RBFS_EmulationDevice != RBFS_EmulationDevice_None) || (RBFS_TraceMeasurement == RBFS_TraceMeasurement_RuntimeConfigurable) )
    mov 0xC0000004,r15      -- Safe SPID Mask (1<<2) and Trace Measurement Modules SPIDs
  #else
    mov 0x00000004,r15      -- Safe SPID Mask (1<<2)
  #endif
  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
    mov 0x80000150,r16      -- RBSYS_PROT_EnLock -- Lock Bit set for APPLICATION
  #else
    mov 0x00000150,r16      -- RBSYS_PROT_EnLock -- Lock Bit not set for other than APPLICATION
  #endif

    -- check Core ID
    stsr 0,r12,2            -- r12 = CoreID
    cmp zero,r12            -- CoreID == 0?
    bne Core1                -- if( CoreID != 0 ) => Core1

  Core0:
    -- Disable Write Protection for PBG00 and PBG01 (same KeyCode Protection for both, see HW UM v1.10 Table 44.413 Note 2)
    mov 0xFFC6B018, ep
    sst.w r27,0[ep]         -- PBG0x.KCPROT = 0xA5A5A501
    syncm

    -- Setup Guards PBG01 Channel 0,2,3
    mov 0xFFC6B100, ep
    sst.w r15,4[ep]       -- PBG01.SPID0 = SafeSPIDMask
    sst.w r16,0[ep]       -- PBG01.PROT0 = RBSYS_PROT_EnLock

    #if( RBFS_TargetDevice != RBFS_TargetDevice_RenesasM2 )
      -- Hint: Core 0 does take care of Core 2 & 3 as well as these are unsupported at the moment
      sst.w r15,20[ep]       -- PBG01.SPID2 = SafeSPIDMask
      sst.w r16,16[ep]       -- PBG01.PROT2 = RBSYS_PROT_EnLock

      sst.w r15,28[ep]       -- PBG01.SPID3 = SafeSPIDMask
      sst.w r16,24[ep]       -- PBG01.PROT3 = RBSYS_PROT_EnLock
      -- Hint: These registers are not implemented for M2
    #endif

    -- CANNOT ENABLE WRITE PROTECTION AS OTHER CORE IS RUNNING IN PARALLEL - will be enabled later (when other PBGs are set up)
    -- -- Enable Write Protection for PBG00
    -- mov 0xFFC6B018, ep
    -- sst.w r28,0[ep]         -- PBG00.KCPROT = 0xA5A5A500
    -- syncm

    -- Disable Write Protection for PBG90
    mov 0xFF0A1418, ep
    sst.w r27,0[ep]         -- PBG90.KCPROT = 0xA5A5A501
    syncm

    -- Setup Guard PBG90 Channel 3
    mov 0xFF0A1300, ep
    sst.w r15, 28[ep]       -- PBG90.SPID3 = SafeSPIDMask
    sst.w r16, 24[ep]       -- PBG90.PROT3 = RBSYS_PROT_EnLock

    -- Enable Write Protection for PBG90
    mov 0xFF0A1418, ep
    sst.w r28,0[ep]         -- PBG90.KCPROT = 0xA5A5A500
    syncm

    br Exit

  Core1:
    -- Disable Write Protection for PBG00
    mov 0xFFC6B018, ep
    sst.w r27,0[ep]         -- PBG00.KCPROT = 0xA5A5A501
    syncm

    -- Setup Guards PBG01 Channel 1

    sst.w r15,244[ep]       -- PBG01.SPID1 = SafeSPIDMask
    sst.w r16,240[ep]       -- PBG01.PROT1 = RBSYS_PROT_EnLock

    -- CANNOT ENABLE WRITE PROTECTION AS OTHER CORE IS RUNNING IN PARALLEL - will be enabled later (when other PBGs are set up)
    -- -- Enable Write Protection for PBG00
    -- mov 0xFFC6B018, ep
    -- sst.w r28,0[ep]         -- PBG00.KCPROT = 0xA5A5A500
    -- syncm

    br Exit

  Exit:
    syncm                 -- assure that all memory writes are finished
  }
#else
  /* Declare assembly function as extern so that it can be stubbed in x86 testing */
  extern void RBSYS_PBUSGuardInit_ForPEGuard(void);
#endif

/**
  * @brief Setup PBUS Guards to protect other GRAM Guard configurations
  *
  * @param void
  *
  * @return void
  */
static inline void RBSYS_PBUSGuardInit_ForGRAMGuard(void)
{
  // guards are included inside RBSYS_PBUSGuardInit_ForPEGuard
}

/**
 * @brief Set PBUS Guard
 *
 * In case of HSM the PBUS Guard has to be set (and later locked) to prevent
 * e.g. unintended reset triggering by writing to the appropriate registers.
 *
 * @param void
 *
 * @return void
 */
extern void RBSYS_PBUSGuardInit(void);


#define RBSYS_CRAMGUARD_ENABLE           (RBSYS_GUARD_EN | RBSYS_GUARD_DEBUG_EN | RBSYS_GUARD_UM_ACC_EN | RBSYS_GUARD_READ_EN)       // Cluster RAM guard enable + User Mode access enabled + read access always allowed

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION ) //< Guards may only be locked inside the Application
  #define RBSYS_CRAMGUARD_LOCK             (RBSYS_GUARD_LOCK)
#else
  #define RBSYS_CRAMGUARD_LOCK             (0u)
#endif


#define RBSYS_GUARD_MASK_8KB       (0x001FE000u)
#define RBSYS_GUARD_MASK_16KB      (0x001FC000u)
#define RBSYS_GUARD_MASK_32KB      (0x001F8000u)
#define RBSYS_GUARD_MASK_64KB      (0x001F0000u)
#define RBSYS_GUARD_MASK_128KB     (0x001E0000u)
#define RBSYS_GUARD_MASK_256KB     (0x001C0000u)
#define RBSYS_GUARD_MASK_512KB     (0x00180000u)
#define RBSYS_GUARD_MASK_1024KB    (0x00100000u)
#define RBSYS_GUARD_MASK_2048KB    (0x00000000u)

/**
 * @brief Set GRAM Guard
 *
 * In case of unsafe bus masters like HSM or Flexray TU the GRAM guard has to be set to prevent
 * unintended write access. In case HSM is active write access is only allowed to special shared GRAM area.
 *
 * - The GRAM guard has eight memory regions that can be protected
 * - It can protect only against write access, read access is always possible by all bus masters
 * - Protection is based on SPID (PEID is not relevant)
 * - In case regions have overlapping address ranges, each region will be individually guarded.
 *   For example, if one region allows access for SPID 1 only, and the other one for SPID 2 only, the
 *   overlapping address regions cannot be accessed neither by SPID 1 nor 2.
 *
 * Attention: Consider HW-Erratum RB126!
 *
 * We use a static GRAM guard sectioning:
 *
 *   Generic CC Cube + Layout                                    Base-Address            Mask             assigned to         restriction possibilities
 *   =================                                       (offset 0xFEE00000)                          guard region        ( - switch settings combinations assign different access attributes to the areas;
 *                                                                                                                              - some switch combinations are not possible (-> sanity check); priority is: B > D > C > A;
 *                                                                                                                              - for more details refer to
 *                                                                                                                              file://///bosch.com/dfsrb/DfsDE/DIV/CS/DE_CS$/Tech/HSW_Doc/Evo17/06_SW-Development/50_SW-Groups/uC_Functional/RBSYS/HSM%20stuff/GRAMguardsMemoryLayout.xlsx )
 *
 *   0xFE000000 to 0xFE07FFFF       (CRAM 0 - 512KB)             0x00000000                     0x00180000                //overlaps        CRG0.0               A
 *   ...        to ...              (CRAM 0 - 8KB)               End -HSMSharedGRAMSize -8KB    0x001FE000                //overlapsCRG0    CRG0.1               E
 *   ...        to [defined by (1)] (CRAM 0 - 16/32KB)           End -HSMSharedGRAMSize         0x001F[C/8]000            //excludesCRG0    CSG0.0               B
 *    (1) = RBFS_SysHsmSharedGRAMsize, RBFS_SysHSMsharedGRAM (Can be restricted, thereby CSG is needed)
 *
 *   0xFE100000 to 0xFE17FFFF       (CRAM 1 - 512KB)             0x00000000                     0x00180000                //                CRG1.0               A
 *
 *   0xFE400000 to 0xFE5FFFFF       (CRAM 2 - 2MB)               0x00000000                     0x00000000                //overlaps        CRG2.0               A
 *
 *   Hint: always consider BURAM section at last 1KB of CRAM2 (M2: CRAM3)
 *
 *   0xFE800000 to 0xFE83FFFF       (CRAM 3 - 256KB)             0x00000000                     0x001C0000                //                CRG3.0              A / D
 *
 *   Hint: CRAM2 = 1MB for M3, 2MB for D7; CRAM3 = 128KB for M3, 256KB for M6
 *
 * Restrictions:
 *  A: Host (RBSYS_SPID_SAFE_MASK)
 *  B: HSM (RBSYS_SPID_SECURE_MASK)
 *  C: Ethernet (RBSYS_SPID_UNSAFE_MASK)
 *  D: Host (RBSYS_SPID_RESTRICTED_MASK)
 *  E: sDMA (RBSYS_SPID_DMA) (only for U2A as DMA is unsafe)
 *
 * Independent of the fact whether physical memory (GRAM) is available, the guards are configured in a generic way.
 * Safe bus masters are ASIL-D compliant (no illegal access happens!) and all unsafe bus masters must be mapped to a dedicated
 * area (which must exist physically on the used device) and therefore the Reserved areas are handled as blocked areas.
 *
 * @param void
 *
 * @return void
 */


/** \brief Initializes all relevant Global RAM guards */
static inline void RBSYS_GRAMGuardInit_Impl(void)
{
  /* Hint: PBUS Guards are set up before. Therefore, checking the GRAM Guard registers is not required afterwards. */

  /** todo: wait for VLAB implementation of CSG Guard, currently same GRD config as for P1x is implemented */

  #define RBSYS_CRG0_GUARDREGION0_BASEADDR             0x00000000u
  #define RBSYS_CRG0_GUARDREGION0_MASK                 RBSYS_GUARD_MASK_512KB
  #if(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_16K)
    #define RBSYS_CSG0_GUARDREGION0_BASEADDR           (0x00080000u - RBSYS_HsmSharedGRAMSize)
    #define RBSYS_CSG0_GUARDREGION0_MASK               RBSYS_GUARD_MASK_16KB
  #elif(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_32K)
    #define RBSYS_CSG0_GUARDREGION0_BASEADDR           (0x00080000u - RBSYS_HsmSharedGRAMSize)
    #define RBSYS_CSG0_GUARDREGION0_MASK               RBSYS_GUARD_MASK_32KB
  #endif
  #define RBSYS_CRG0_GUARDREGION1_BASEADDR             (0x00080000u - RBSYS_HsmSharedGRAMSize - RBSYS_DMASharedRAMSize)
  #define RBSYS_CRG0_GUARDREGION1_MASK                 RBSYS_GUARD_MASK_8KB
  #define RBSYS_CRG0_VALID_BITS                       0x0007FF00u
  #define RBSYS_CSG0_VALID_BITS                       0x0007FF00u

  #define RBSYS_CRG1_GUARDREGION0_BASEADDR            0x00000000u
  #define RBSYS_CRG1_GUARDREGION0_MASK                RBSYS_GUARD_MASK_512KB
  #define RBSYS_CRG1_VALID_BITS                       0x0007FF00u

  #define RBSYS_CRG2_GUARDREGION0_BASEADDR            0x00000000u
  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3) )
    #define RBSYS_CRG2_GUARDREGION0_MASK                RBSYS_GUARD_MASK_1024KB
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) \
      || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) )
    #define RBSYS_CRG2_GUARDREGION0_MASK                RBSYS_GUARD_MASK_2048KB
  #endif
  #define RBSYS_CRG2_VALID_BITS                       0x001FFF00u

  #define RBSYS_CRG3_GUARDREGION0_BASEADDR            0x00000000u
  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3) )
    #define RBSYS_CRG3_GUARDREGION0_MASK                RBSYS_GUARD_MASK_128KB
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) \
      || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) )
    #define RBSYS_CRG3_GUARDREGION0_MASK                RBSYS_GUARD_MASK_256KB
  #elif( RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2 )
    #if( RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_0K )
      #define RBSYS_CRG3_GUARDREGION0_MASK                RBSYS_GUARD_MASK_128KB
    #else
      #define RBSYS_CRG3_GUARDREGION0_MASK                RBSYS_GUARD_MASK_64KB
      #define RBSYS_CRG3_GUARDREGION1_BASEADDR            0x00010000u
      #define RBSYS_CRG3_GUARDREGION1_MASK                RBSYS_GUARD_MASK_64KB
    #endif
  #endif

  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2) ) //< Todo: Clarify w/ REL why M3 has 256KB configurable range
    #define RBSYS_CRG3_VALID_BITS                       0x0001FF00u //< 128KB configurable range
  #else
    #define RBSYS_CRG3_VALID_BITS                       0x0003FF00u //< 256KB configurable range
  #endif


  /******************************************************************************************************************************/
  /******************************************************** Cluster RAM 0 *******************************************************/
  /******************************************************************************************************************************/
  #if( RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON )

    RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG0CRGKCPROT);

    GUARD_CRAMCRG0CRGBAD0  = RBSYS_CRG0_GUARDREGION0_BASEADDR & RBSYS_CRG0_VALID_BITS;
    GUARD_CRAMCRG0CRGADV0  = RBSYS_CRG0_GUARDREGION0_MASK & RBSYS_CRG0_VALID_BITS;
    GUARD_CRAMCRG0CRGSPID0 = RBSYS_SPID_SAFE_MASK;

    GUARD_CRAMCRG0CRGBAD1  = RBSYS_CRG0_GUARDREGION1_BASEADDR & RBSYS_CRG0_VALID_BITS;
    GUARD_CRAMCRG0CRGADV1  = RBSYS_CRG0_GUARDREGION1_MASK & RBSYS_CRG0_VALID_BITS;
    GUARD_CRAMCRG0CRGSPID1 = RBSYS_SPID_UnsafeDMA_MASK;

    #if( RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K )
      GUARD_CRAMCSG0CSGBAD0  = RBSYS_CSG0_GUARDREGION0_BASEADDR & RBSYS_CSG0_VALID_BITS;
      GUARD_CRAMCSG0CSGADV0  = RBSYS_CSG0_GUARDREGION0_MASK & RBSYS_CSG0_VALID_BITS;
      #if( RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted )
        // allow SAFE SPID to access Restricted HSM Shared RAM for variable initialization, this section will be set to (Restricted || Secure) SPID only later on (SAFE access will be removed)
        GUARD_CRAMCSG0CSGSPID0 = (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SECURE_MASK);
      #else
        GUARD_CRAMCSG0CSGSPID0 = (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK);
      #endif
      GUARD_CRAMCSG0CSGPROT0 |= RBSYS_CRAMGUARD_ENABLE;
    #endif

    GUARD_CRAMCRG0CRGPROT0 |= RBSYS_CRAMGUARD_ENABLE;
    GUARD_CRAMCRG0CRGPROT1 |= RBSYS_CRAMGUARD_ENABLE;

    RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG0CRGKCPROT);

  #endif

  /******************************************************************************************************************************/
  /******************************************************** Cluster RAM 1 *******************************************************/
  /******************************************************************************************************************************/
  #if( RBFS_RenesasU2aCRAM1 == RBFS_RenesasU2aCRAM1_ON )

    RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG1CRGKCPROT);

    GUARD_CRAMCRG1CRGBAD0 = RBSYS_CRG1_GUARDREGION0_BASEADDR & RBSYS_CRG1_VALID_BITS;
    GUARD_CRAMCRG1CRGADV0 = RBSYS_CRG1_GUARDREGION0_MASK & RBSYS_CRG1_VALID_BITS;
    GUARD_CRAMCRG1CRGSPID0 = RBSYS_SPID_SAFE_MASK;

    GUARD_CRAMCRG1CRGPROT0 |= RBSYS_CRAMGUARD_ENABLE;

    RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG1CRGKCPROT);

  #endif

  /******************************************************************************************************************************/
  /******************************************************** Cluster RAM 2 *******************************************************/
  /******************************************************************************************************************************/
  #if( RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON )

    RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG2CRGKCPROT);

    GUARD_CRAMCRG2CRGBAD0  = RBSYS_CRG2_GUARDREGION0_BASEADDR & RBSYS_CRG2_VALID_BITS;
    GUARD_CRAMCRG2CRGADV0  = RBSYS_CRG2_GUARDREGION0_MASK & RBSYS_CRG2_VALID_BITS;
    GUARD_CRAMCRG2CRGSPID0 = RBSYS_SPID_SAFE_MASK;
    GUARD_CRAMCRG2CRGPROT0 |= RBSYS_CRAMGUARD_ENABLE;

    RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG2CRGKCPROT);

  #endif

  /******************************************************************************************************************************/
  /******************************************************** Cluster RAM 3 *******************************************************/
  /******************************************************************************************************************************/
  #if( RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON )

    RBSYS_UnlockAccessToHwModule(&GUARD_CRAMCRG3CRGKCPROT);

    #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3) \
      || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) \
      || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) )
      GUARD_CRAMCRG3CRGBAD0 = RBSYS_CRG3_GUARDREGION0_BASEADDR & RBSYS_CRG3_VALID_BITS;
      GUARD_CRAMCRG3CRGADV0 = RBSYS_CRG3_GUARDREGION0_MASK & RBSYS_CRG3_VALID_BITS;
      #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
        // allow SAFE SPID to access Restricted Exclusive RAM for variable initialization, this section will be set to Restricted SPID only later on (SAFE access will be removed)
        GUARD_CRAMCRG3CRGSPID0 = RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK;
      #else
        GUARD_CRAMCRG3CRGSPID0 = RBSYS_SPID_SAFE_MASK;
      #endif
      GUARD_CRAMCRG3CRGPROT0 |= RBSYS_CRAMGUARD_ENABLE;
    #elif( RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2 )
      GUARD_CRAMCRG3CRGBAD0 = RBSYS_CRG3_GUARDREGION0_BASEADDR & RBSYS_CRG3_VALID_BITS;
      GUARD_CRAMCRG3CRGADV0 = RBSYS_CRG3_GUARDREGION0_MASK & RBSYS_CRG3_VALID_BITS;

      #if( RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_0K )
        /* Safe RAM: 128K */
        GUARD_CRAMCRG3CRGSPID0 = RBSYS_SPID_SAFE_MASK;
      #else
        /* Restricted Exclusive RAM: 64K */
        // allow SAFE SPID to access Restricted Exclusive RAM for variable initialization, this section will be set to Restricted SPID only later on (SAFE access will be removed)
        GUARD_CRAMCRG3CRGSPID0 = RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK;

        /* Safe RAM: 64K */
        GUARD_CRAMCRG3CRGBAD1 = RBSYS_CRG3_GUARDREGION1_BASEADDR & RBSYS_CRG3_VALID_BITS;
        GUARD_CRAMCRG3CRGADV1 = RBSYS_CRG3_GUARDREGION1_MASK & RBSYS_CRG3_VALID_BITS;
        GUARD_CRAMCRG3CRGSPID1 = RBSYS_SPID_SAFE_MASK;
        GUARD_CRAMCRG3CRGPROT1 |= RBSYS_CRAMGUARD_ENABLE;
      #endif

      GUARD_CRAMCRG3CRGPROT0 |= RBSYS_CRAMGUARD_ENABLE;
    #endif

    RBSYS_LockAccessToHwModule(&GUARD_CRAMCRG3CRGKCPROT);

  #endif
}


  /**
  * @brief Lock GRAM Guard
  *
  * Each GRAM guard must be locked to avoid further changes. After reset, the GRAM guard registers can be
  * re-written as long as this function is not called. Once it's called, all further write accesses to
  * GRAM guard registers are ignored. Please take care, this function must only be called after RBSYS_GRAMGuardInit_Impl().
  *
  * Hint: This function must not be called in bootblock!
  *
  * @param void
  *
  * @return void
  */
  extern void RBSYS_GRAMGuardLock(void);

#if( RBFS_SysExclusiveSPID == RBFS_SysExclusiveSPID_Used )
  #if( RBFS_SysEnvironment == RBFS_SysEnvironment_Target )
    extern volatile uint32 RBSYS_TrapPermissionHandlingStack[2][2];

    static_assert(sizeof(RBSYS_TrapPermissionHandlingStack) == 2*2*4, "Size of RBSYS_TrapPermissionHandlingStack is invalid. Potential Stack overrun.");
    static_assert(RB_NUM_CORES <= 2, "Exclusive SPID Permission Handling does support max. 2 Cores.");

    // Stack Pointer can be allocated anywhere -> avoid SDA addressing in assembler code
    RBSECTION_START_SECTTYPE_NO_SDA
      extern volatile unsigned int* const RBSYS_TrapPermissionHandlingStack0_StartAddressPtr;
      extern volatile unsigned int* const RBSYS_TrapPermissionHandlingStack1_StartAddressPtr;
    RBSECTION_END_SECTTYPE_NO_SDA


    /**
      * @brief Enter SAFE Master privileges
      *
      * Parts of SW can be executed with SPID (System Protection ID) different than SAFE. In case an interrupt is acknowledged
      * while SPID != SAFE, SAFE SPID has to be set before using any registers / protected memory region
      *
      * Hint: This function must be followed up by RBSYS_TRAP_PERMISSION_LEAVE to restore the original privileges and restore the context.
      *
      * @param void
      * @return void
      */
    static void RBSYS_TRAP_PERMISSION_ENTRY(void);
    asm void RBSYS_TRAP_PERMISSION_ENTRY(void)
    {
%lab Core0 %lab Core1 %lab StackAccess %lab end
      syncm                 -- assure that all memory writes are finished

      ldsr r9,EIWR,0         -- EIWR = r9
      stsr 0,r9,1            -- r9 = SPID
      ldsr r9,FEWR,0         -- FEWR = r9

      -- Attention: 0x00000002 is the "value after reset" for SPID, so Read-Modify-Write is not needed here
      mov 0x00000002,r9      -- r9 = 0x00000002
      ldsr r9,0,1            -- SPID = r9

      synci                  -- See U2A UM Rev. 1.10 p.434: Explicit SYNCI is required after updating SPID

      -- Get Core specific Stack
      stsr 0,r9,2
      cmp zero,r9
      bne Core1              -- if( CoreID != 0 ) goto Core1; else continue
Core0:
      mov ep,r9
      mov _RBSYS_TrapPermissionHandlingStack0_StartAddressPtr,ep
      br StackAccess
Core1:
      mov ep,r9             -- r9 = EP (current Element Pointer)
      mov _RBSYS_TrapPermissionHandlingStack1_StartAddressPtr,ep
      br StackAccess

StackAccess:
      sld.w 0[ep],ep        -- EP = *StackStartAddress
      sst.w r9, (0)[ep]     -- Stack[0] = r9 (original EP)
      stsr FEWR,r9,0        -- r9 = FEWR (original SPID)
      sst.w r9, (4)[ep]     -- Stack[1] = r9 (original SPID)

      sld.w (0)[ep], ep     -- EP = Stack[0] (original EP)
      stsr EIWR,r9,0        -- r9 = EIWR (original r9)

      syncm                 -- assure that SPID setting is effective before doing something else
end:
%error
    }
    //< todo: check if one out of General Purpose Registers r20-r29 can be used. Saving to stack could be handled via "prepare" instruction then.

    /**
      * @brief Leave SAFE Master privileges
      *
      * Parts of SW can be executed with SPID (System Protection ID) different than SAFE. In case an interrupt is acknowledged
      * while SPID != SAFE, SAFE SPID has to be set before using any registers / protected memory region. After interrupt handling is completed,
      * previous SPID has to be restored and context has to be restored.
      *
      * Hint: This function must be preceded by RBSYS_TRAP_PERMISSION_ENTRY to store the original privileges on the stack.
      *
      * @param void
      * @return void
      */
    static void RBSYS_TRAP_PERMISSION_LEAVE(void);
    asm void RBSYS_TRAP_PERMISSION_LEAVE(void)
    {
%lab Core0 %lab Core1 %lab StackAccess %lab end
      syncm                -- assure that all memory writes are finished

      ldsr r9,EIWR,0       -- EIWR = r9 (original r9)
      ldsr ep,FEWR,0       -- FEWR = EP (original EP)


      -- Get Core specific Stack
      stsr 0,r9,2
      cmp zero,r9
      bne Core1            -- if( CoreID != 0 ) goto Core1; else continue
Core0:
      mov _RBSYS_TrapPermissionHandlingStack0_StartAddressPtr,ep
      br StackAccess
Core1:
      mov _RBSYS_TrapPermissionHandlingStack1_StartAddressPtr,ep
      br StackAccess

StackAccess:
      sld.w 0[ep],ep       -- EP = *StackStartAddress
      sld.w (4)[ep], r9    -- r9 = Stack[1] (original SPID)
      ldsr r9,0,1          -- SPID = r9 (original SPID)

      synci                -- See U2A UM Rev. 1.10 p.434: Explicit SYNCI is required after updating SPID

      stsr EIWR,r9,0       -- r9 = EIWR (original r9)
      stsr FEWR,ep,0       -- EP = FEWR (original EP)

      syncm                -- assure that SPID setting is effective before doing something else
end:
%error
    }
  #endif
#endif


#if( RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted )
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
  extern void RBSYS_RestrictedHSMSharedGRAM_BlockSafeAccess(void);
#endif


/** @} */
/* End ingroup RBSYS */


#endif