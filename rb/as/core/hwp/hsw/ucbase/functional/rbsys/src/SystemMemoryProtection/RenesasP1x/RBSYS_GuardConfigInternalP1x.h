#ifndef RBSYS_GUARDCONFIGINTERNALP1X_H__
#define RBSYS_GUARDCONFIGINTERNALP1X_H__


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


/* used interfaces */
#include "RBSYS_uCRegisters.h"
#include "RBSYS_GuardMemoryMap.h"
#include "RBSYS_GuardConfig.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_CpuInfo.h"
#include "RBLCF_MemoryRemap.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                          RBFS_TargetDevice_RenesasD1,
                          RBFS_TargetDevice_RenesasD2,
                          RBFS_TargetDevice_RenesasD3,
                          RBFS_TargetDevice_RenesasD4,
                          RBFS_TargetDevice_RenesasD5);

RB_ASSERT_SWITCH_SETTINGS(RBFS_EmulationDevice,
                          RBFS_EmulationDevice_None,
                          RBFS_EmulationDevice_RenesasD3ED,
                          RBFS_EmulationDevice_RenesasD5ED);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasP1xGRAM,
                          RBFS_RenesasP1xGRAM_ON,
                          RBFS_RenesasP1xGRAM_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHsmSharedGRAMsize,
                          RBFS_SysHsmSharedGRAMsize_0K,
                          RBFS_SysHsmSharedGRAMsize_16K,
                          RBFS_SysHsmSharedGRAMsize_32K);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEthSharedGRAMsize,
                          RBFS_SysEthSharedGRAMsize_0K,
                          RBFS_SysEthSharedGRAMsize_32K,
                          RBFS_SysEthSharedGRAMsize_64K,
                          RBFS_SysEthSharedGRAMsize_96K,
                          RBFS_SysEthSharedGRAMsize_128K);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RestrictedExclusiveGRAMsize,
                          RBFS_RestrictedExclusiveGRAMsize_0K,
                          RBFS_RestrictedExclusiveGRAMsize_16K,
                          RBFS_RestrictedExclusiveGRAMsize_32K,
                          RBFS_RestrictedExclusiveGRAMsize_128K,
                          RBFS_RestrictedExclusiveGRAMsize_256K);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHSMsharedGRAM,
                          RBFS_SysHSMsharedGRAM_Host,
                          RBFS_SysHSMsharedGRAM_Restricted);

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

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysRAMLayoutFragmentation,
                          RBFS_SysRAMLayoutFragmentation_Default,
                          RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RBSYSGlobalRAMGuardsBB,
                          RBFS_RBSYSGlobalRAMGuardsBB_ON,
                          RBFS_RBSYSGlobalRAMGuardsBB_OFF);

/* **************************************************************************************** */
/*        Feature Switches for Sys Guard Groups                                             */
/* **************************************************************************************** */

/** all controllers but D1 and D2 have this guard register - Grp1 = Not D1 to D2, i.e. D3 and higher */
#define RBFS_SysGuardPresenceGrp1_YES      1
#define RBFS_SysGuardPresenceGrp1_NO       2
/** all controllers but D1 to D3 have this guard register  - Grp2 = Not D1 to D3, i.e. D4 and higher */
#define RBFS_SysGuardPresenceGrp2_YES      1
#define RBFS_SysGuardPresenceGrp2_NO       2
/** all controllers but D1 to D4 have this guard register  - Grp3 = Not D1 to D4, i.e. D5 and higher */
#define RBFS_SysGuardPresenceGrp3_YES      1
#define RBFS_SysGuardPresenceGrp3_NO       2

#if((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) \
 && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2) \
 && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD3) \
 && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD4))
  /* it is not D1 to D4, but higher - all add-on groups are present */
  #define RBFS_SysGuardPresenceGrp3   RBFS_SysGuardPresenceGrp3_YES
  #define RBFS_SysGuardPresenceGrp2   RBFS_SysGuardPresenceGrp2_YES
  #define RBFS_SysGuardPresenceGrp1   RBFS_SysGuardPresenceGrp1_YES
#elif((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) \
   && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2) \
   && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD3))
  /* it is not D1 to D3, but it is D4 - highest add-on group not present */
  #define RBFS_SysGuardPresenceGrp3   RBFS_SysGuardPresenceGrp3_NO
  #define RBFS_SysGuardPresenceGrp2   RBFS_SysGuardPresenceGrp2_YES
  #define RBFS_SysGuardPresenceGrp1   RBFS_SysGuardPresenceGrp1_YES
#elif((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) \
   && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2))
  /* it is not D1 to D2, but it is D3 - two highest add-on groups not present */
  #define RBFS_SysGuardPresenceGrp3   RBFS_SysGuardPresenceGrp3_NO
  #define RBFS_SysGuardPresenceGrp2   RBFS_SysGuardPresenceGrp2_NO
  #define RBFS_SysGuardPresenceGrp1   RBFS_SysGuardPresenceGrp1_YES
#else
  /* it is D1 or D2 - all add-on groups not present */
  #define RBFS_SysGuardPresenceGrp3   RBFS_SysGuardPresenceGrp3_NO
  #define RBFS_SysGuardPresenceGrp2   RBFS_SysGuardPresenceGrp2_NO
  #define RBFS_SysGuardPresenceGrp1   RBFS_SysGuardPresenceGrp1_NO
#endif

typedef struct
{
  volatile uint32 *    Guard_Register;
  uint32               GuardValue;
} RBSYS_GuardsList_t;

/**
  * @brief Set and Lock all peripheral guard registers (PBUS and HBUS) to the specified values (agreed with GUAM development)
  *
  * @param void
  * @return void
  */
extern void RBSYS_PeripheralGuardInit(void);

/**
  * @brief Check if all PBUS & HBUS Guards have been initialized to the specified values 
  *        Potential scenario: PBUS & HBUS Guards could not have been initialized because Unsafe bus masters have corrupted the configuration
  *
  * @param void
  * @return TRUE if all as expected, else FALSE
  */
extern boolean RBSYS_VerifyPeripheralGuardSettings(void);


/**
  * @brief Check if all prerequisites are fulfilled to garantuee correct LRAM Guard settings
  *
  * @param void
  * @return TRUE if all as expected, else FALSE
  */
extern boolean RBSYS_VerifyLRAMGuardSettings(void);

/**
  * @brief Check if all prerequisites are fulfilled to garantuee correct GRAM Guard settings
  *
  * @param void
  * @return TRUE if all as expected, else FALSE
  */
extern boolean RBSYS_VerifyGRAMGuardSettings(void);


#if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)

  /* ********************************************************************************** */
  /*   Sanity Checks for the switches in combination with the 'Restricted SPID'-feature */
  /* ********************************************************************************** */

  #if( (RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_32K) && (RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K) )
    #error ("RBFS_SysHsmSharedGRAMsize_32K cannot be combined with RBFS_RestrictedExclusiveGRAMsize_16K in generic GRAM layout !!!")
  #endif

  #if( (RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K) && \
       ( (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_32K) || (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K) ) \
     )
    #error ("RBFS_RestrictedExclusiveGRAMsize_32K cannot be combined with RBFS_SysEthSharedGRAMsize_32K nor with RBFS_SysEthSharedGRAMsize_96K in generic GRAM layout !!!  (EthSharedGRAMsizes of 64K or 128K are possible)")
  #endif

  /* Define the Base Address Offset for GRAM */
  #define RBSYS_GRAMguardBaseAddrOffset    0xFEE00000u

#endif

/* the normal Guard registers have the lock Bit in the Bit 31 position, e.g. APBFSGDPROTxxxx, FSGDxxxPROTxxx */
#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
  #define RBSYS_GUARDPROTREGISTER_LOCK              ((uint32) 1u << 31)
#else
  #define RBSYS_GUARDPROTREGISTER_LOCK              (0u)      //< Guards may only be locked inside the Application
#endif


/* macros for PEID Bit in P-bus FS Guard Protection Setting Register (e.g. APBFSGDPROTxxxx, FSGDxxxPROTxxx) */
/* Note: on P1x  Core0, Core1 and DMA are all safe                          */
/*       However as DMA shares its PEID with Ethernet/Flexray it is handled */
/*       separately. When allowing DMA access (particularly for write) it   */
/*       has to be ensured that via SPID configuration only RBSYS_SPID_SAFE_MASK */
/*       is allowed.                                                        */
#define RBSYS_PEID_SAFE          (((uint32) 1u << 18) | ((uint32) 1u << 19))
#define RBSYS_PEID_SECURE        ( (uint32) 1u << 22 )
#define RBSYS_PEID_PEID4         ( (uint32) 1u << 21 )

#define RBSYS_PROTREGINITVALUE4PE_READ_WITHOUTPEIDFLAGS        0x0601FE1Bu
#define RBSYS_PROTREGINITVALUE4PE_WRITE_WITHOUTPEIDFLAGS       0x0601FE17u
#define RBSYS_PROTREGINITVALUE4ICUM_READ_WITHOUTPEIDFLAGS      0x0601FE0Bu
#define RBSYS_PROTREGINITVALUE4ICUM_WRITE_WITHOUTPEIDFLAGS     0x0601FE07u




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
 * @param nSPID defines the new system protection identifier
 *
 * @return void
 */
__attribute__((always_inline)) static inline void RBSYS_setCoreSPID(RBSYSspid_t nSPID)
{
  unsigned int mcfg0;
  mcfg0  = RBSYS_STSR(0, 1);        // read System register 0, 1 - MCFG0 (Machine configuration)
  mcfg0 &= 0xFFE0FFFFu;             // mask old SPID (bit 20 to 16)
  mcfg0 |= ((uint32) nSPID << 16);           // set new SPID

  RBSYS_LDSR(0, 1, mcfg0);          // write System register 0, 1 - MCFG0 (Machine configuration)

  // introduce sync instructions after updating MCFG0.SPID as requested within the UM (see chapter "System Register Hazards")
  RBSYS_SYNCP();
  RBSYS_SYNCI();
}


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
    stsr 0,r16,1         -- r16 = MCFG0
    mov 0xFFE0FFFF,r7    -- r7 = 0xFFE0FFFF
    and r7,r16           -- r16 &= r7
    mov 0x00020000,r7    -- r7 = 0x00020000 (2 << 16)
    or r7,r16            -- r16 |= r7   (SafeSPID)
    ldsr r16,0,1         -- SPID = r16
    syncp
    synci
  }
#else
  /* Declare assembly function as extern so that it can be stubbed in x86 testing */
  extern void RBSYS_setCoreSPID2SafeSPID(void);
#endif


/**
 * This function returns the current Core SPID (system protection identifier)
 *
 * @return SPID
 */
static inline RBSYSspid_t RBSYS_getCoreSPID(void)
{
  unsigned int mcfg0 = RBSYS_STSR(0, 1);                  // read System register 0, 1 - MCFG0 (Machine configuration)
  unsigned int spid = (mcfg0 & 0x001F0000u) >> 16;        // mask out SPID (bit 20 to 16)

  return (RBSYSspid_t)spid;
}

/**
 * @brief Set SPID for unsafe bus masters (system protection identifier for Flexray0/1,Ethernet0/1,HS-USRT0-3)
 *
 * It has to be made sure that the unsafe bus masters are initialized with unsafe SPID.
 * D1 and D2 do not have these registers, but if they are emulated on D3ED (which has them) they must be configured there as well!
 *
 * @return void
 */
static inline void RBSYS_SetBusMasterIDs(void)
{
  #if(((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2)) \
   || (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD3ED) \
     )
     HSSPIDRG0 = (uint32)UnSafeSPID;
     HSSPIDRG2 = (uint32)UnSafeSPID;
     HSSPIDRG4 = (uint32)UnSafeSPID;
     HSSPIDRG5 = (uint32)UnSafeSPID;

    #if ((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5))
     /* according to Renesas information these registers can only be written, in case the feature is present, which is not for D3 or D3ED */
     /* Note: currently we do not use D4_BGA-156 - if we do this in the future a "runtime if" is needed here!  */
       HSSPIDRG1 = (uint32)UnSafeSPID;
       HSSPIDRG3 = (uint32)UnSafeSPID;
       HSSPIDRG6 = (uint32)UnSafeSPID;
       HSSPIDRG7 = (uint32)UnSafeSPID;
    #endif
  #endif
}


  /** \brief Configures all HBUS Guards */
  static inline void RBSYS_HBusGuardInit(void)
  {
    // done later inside RBSYS_PRC_FSW_FinalGuard_Init (see RBSYS_SetAndLockPeripheralGuardRegisters)
  }

  /* PEGGnBA - PE Guard Area n Base Setting Register: */
  #define RBSYS_PEG_ENABLE            (1u << 0)      // PE guard protection area enable
  #define RBSYS_PEG_READ_ACCESS       (1u << 1)      // Enables read access to PE guard protection area
  #define RBSYS_PEG_WRITE_ACCESS      (1u << 2)      // Enables write access to PE guard protection area

  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
    #define RBSYS_PEG_LOCK              (0x10)       // Enables write protect to the registers (PEGGnBA, PEGGnMK, PEGGnSP)
  #else //< Bootmanager, Bootloader, RBBootloader
    #define RBSYS_PEG_LOCK              (0)          // DOES NOT Enable write protect to the registers (PEGGnBA, PEGGnMK, PEGGnSP), 
                                                     // because Application may require to change the value!!!
  #endif

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
    -- PEG Area 0: Allow read access to complete LRAM from Secure SPID
    mov 0x003FF000, r1
    st.w r1,RBSYS_ADDR_PEGG0MK[zero]   -- PEGG0MK = 0x003FF000
    mov 0x3, r1
    st.w r1,RBSYS_ADDR_PEGG0SP[zero]   -- PEGG0SP = RBSYS_SPID_SECURE_MASK
    mov 0xFE800003, r1
    st.w r1,RBSYS_ADDR_PEGG0BA[zero]   -- PEGG0BA = (0xFE800000u | RBSYS_PEG_READ_ACCESS | RBSYS_PEG_ENABLE)

    -- PEG Area 1: Allow r/w access to complete LRAM from SAFE SPID
    mov 0x003FF000, r1
    st.w r1,RBSYS_ADDR_PEGG1MK[zero]   -- PEGG1MK = 0x003FF000
    mov 0x4, r1
    st.w r1,RBSYS_ADDR_PEGG1SP[zero]   -- PEGG1SP = RBSYS_SPID_SAFE_MASK
    mov 0xFE800007, r1
    st.w r1,RBSYS_ADDR_PEGG1BA[zero]   -- PEGG1BA = (0xFE800000u | RBSYS_PEG_WRITE_ACCESS | RBSYS_PEG_READ_ACCESS | RBSYS_PEG_ENABLE)


    syncm                              -- assure that all memory writes are finished
  }
#else
  /* Declare assembly function as extern so that it can be stubbed in x86 testing */
  extern void RBSYS_PEGuardInit(void);
#endif




#if( RBFS_SysEnvironment == RBFS_SysEnvironment_Target )
  /**
  * @brief Setup PBUS Guards to protect other Guard configurations
  *
  * - Access to SPIDs has to be restricted
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
    mov 4,r1
    st.w r1,RBSYS_ADDR_FSGD3ASPID03[zero]  -- FSGD3ASPID03 = RBSYS_SPID_SAFE_MASK
  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
    mov 0x860DFE17,r1         -- FSGD3APROT03 = 0x860DFE17 -- Lock Bit set for APPLICATION
  #else
    mov 0x060DFE17,r1         -- FSGD3APROT03 = 0x060DFE17 -- Lock Bit not set for other than APPLICATION
  #endif
    st.w r1,RBSYS_ADDR_FSGD3APROT03[zero]

    syncm                     -- assure that all memory writes are finished
  }
#else
  /* Declare assembly function as extern so that it can be stubbed in x86 testing */
  extern void RBSYS_PBUSGuardInit_ForPEGuard(void);
#endif


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
static inline void RBSYS_PBUSGuardInit(void)
{
  /* Enable DMA access PEID = 4; but in case of write only for SAFE Applications.      */
  /* For reads no extra effort is made; writes need to be protected by SPID mechanism. */
  FSGD1APROT04 |= RBSYS_PEID_PEID4;  // Enable DMA read for RLIN31/33
  FSGD1ASPID05 = RBSYS_SPID_SAFE_MASK;    // restrict writes to safe applications (DMA)
  FSGD1APROT05 |= RBSYS_PEID_PEID4;  // Enable DMA write for RLIN31/33
  FSGD1BPROT10 |= RBSYS_PEID_PEID4;  // Enable DMA reads from CSIH1
  FSGD1BSPID11 = RBSYS_SPID_SAFE_MASK;    // restrict writes to safe applications (DMA)
  FSGD1BPROT11 |= RBSYS_PEID_PEID4;  // Enable DMA writes to CSIH1

  //Renesas devices D1 and D2 do only have CSIH0 - CSIH2
  #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
    FSGD1BPROT12 |= RBSYS_PEID_PEID4;  // Enable DMA reads from CSIH3
    FSGD1BSPID13 = RBSYS_SPID_SAFE_MASK;    // restrict writes to safe applications (DMA)
    FSGD1BPROT13 |= RBSYS_PEID_PEID4;  // Enable DMA writes to CSIH3
  #endif

  FSGD2APROT04 |= RBSYS_PEID_PEID4;  // Enable DMA reads from GTM
  FSGD2ASPID05 = RBSYS_SPID_SAFE_MASK;    // restrict writes to safe applications (DMA)
  FSGD2APROT05 |= RBSYS_PEID_PEID4;  // Enable DMA writes to GTM
  FSGD2APROT06 |= RBSYS_PEID_PEID4;  // Enable DMA reads to STM0
  FSGD3BPROT10 |= RBSYS_PEID_PEID4;  // Enable DMA reads from CSIH0
  FSGD3BSPID11 = RBSYS_SPID_SAFE_MASK;    // restrict writes to safe applications (DMA)
  FSGD3BPROT11 |= RBSYS_PEID_PEID4;  // Enable DMA writes to CSIH0
  FSGD3BPROT12 |= RBSYS_PEID_PEID4;  // Enable DMA reads from CSIH2
  FSGD3BSPID13 = RBSYS_SPID_SAFE_MASK;    // restrict writes to safe applications (DMA)
  FSGD3BPROT13 |= RBSYS_PEID_PEID4;  // Enable DMA writes to CSIH2
  FSGD4APROT06 |= RBSYS_PEID_PEID4;  // Enable DMA reads from ADC0

  // Renesas devices D1 and D2 do only have one ADC unit
  #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
    FSGD4APROT08 |= RBSYS_PEID_PEID4;  // Enable DMA reads from ADC1
  #endif
}


  /* MGDGRPROTx - GRAM Guard Area Base Protection Register: */
  #define RBSYS_GRAMGUARD_ENABLE            ((uint32) 1u << 30)   // Global RAM guard protection area enable

  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION ) //< Guards may only be locked inside the Application
    #define RBSYS_GRAMGUARD_LOCK            ((uint32) 1u << 31)   // Enables write protect to the registers (MGDGRPROTn, MGDGRSPIDn)
  #else
    #define RBSYS_GRAMGUARD_LOCK            (0u)
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
 *   Generic CC CUBE layout                                      Base-Address            Mask             assigned to         restriction possibilities
 *   =================                                       (offset 0xFEE00000)                          guard region        ( - switch settings combinations assign different access attributes to the areas;
 *                                                                                                                              - some switch combinations are not possible (-> sanity check); priority is: B > D > C > A;
 *                                                                                                                              - for more details refer to
 *                                                                                                                              file://///bosch.com/dfsrb/DfsDE/DIV/CS/DE_CS$/Tech/HSW_Doc/Evo17/06_SW-Development/50_SW-Groups/uC_Functional/RBSYS/HSM%20stuff/GRAMguardsMemoryLayout.xlsx )
 *   0xFEF00000  to  0xFEFFFFFF     (Bank B - complete)         0x00100000            0x00100000               0                 A
 *   0xFEEFC000  to  0xFEEFFFFF     (Bank A -  16KB)            0x000FC000            0x001FC000               1                 A / A+B / B+D
 *   0xFEEF8000  to  0xFEEFBFFF     (Bank A -  16KB)            0x000F8000            0x001FC000               2                 A / A+B / B+D / D
 *   0xFEEF0000  to  0xFEEF7FFF     (Bank A -  32KB)            0x000F0000            0x001F8000               3                 A / A+C / D
 *   0xFEEE0000  to  0xFEEEFFFF     (Bank A -  64KB)            0x000E0000            0x001F0000               4                 A / A+C
 *   0xFEEC0000  to  0xFEEDFFFF     (Bank A - 128KB)            0x000C0000            0x001E0000               5                 A / A+C
 *   0xFEE80000  to  0xFEEBFFFF     (Bank A - 256KB)            0x00080000            0x001C0000               6                 A
 *   0xFEE00000  to  0xFEE7FFFF     (Bank A - remainder)        0x00000000            0x00180000               7                 A
 *
 * Restrictions:
 *  A: Host (RBSYS_SPID_SAFE_MASK)
 *  B: HSM (RBSYS_SPID_SECURE_MASK)
 *  C: Ethernet (RBSYS_SPID_UNSAFE_MASK)
 *  D: Host (RBSYS_SPID_RESTRICTED_MASK)
 *
 * Independent of the fact whether physical memory (GRAM) is available, the guards are configured in a generic way.
 * Safe bus masters are ASIL-D compliant (no illegal access happens!) and all unsafe bus masters must be mapped to a dedicated
 * area (which must exist physically on the used device) and therefore the Reserved areas are handled as blocked areas.
 *
 * @param void
 *
 * @return void
 */

  /* Base Addresses for Guard Regions. As we follow an envelope approach, the address range of the guards can overlap the
   * real physically available addresses on the corresponding devices (see address sanity check e.g. see Guard Region 5 for D3) */

  #define RBSYS_GUARDREGION0_BASEADDR             0x00100000u
  #define RBSYS_GUARDREGION0_BASEADDR_SANITYCHECK 0x00100000u

  #define RBSYS_GUARDREGION1_BASEADDR             0x000FC000u
  #define RBSYS_GUARDREGION1_BASEADDR_SANITYCHECK 0x000FC000u

  #define RBSYS_GUARDREGION2_BASEADDR             0x000F8000u
  #define RBSYS_GUARDREGION2_BASEADDR_SANITYCHECK 0x000F8000u

  #define RBSYS_GUARDREGION3_BASEADDR             0x000F0000u
  #define RBSYS_GUARDREGION3_BASEADDR_SANITYCHECK 0x000F0000u

  #define RBSYS_GUARDREGION4_BASEADDR             0x000E0000u
  #define RBSYS_GUARDREGION4_BASEADDR_SANITYCHECK 0x000E0000u

  #define RBSYS_GUARDREGION5_BASEADDR             0x000C0000u
  #if( RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3 )
    #define RBSYS_GUARDREGION5_BASEADDR_SANITYCHECK 0x000D8000u
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) \
      || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5) )
    #define RBSYS_GUARDREGION5_BASEADDR_SANITYCHECK 0x000C0000u
  #endif

  #define RBSYS_GUARDREGION6_BASEADDR             0x00080000u
  #define RBSYS_GUARDREGION6_BASEADDR_SANITYCHECK 0x00080000u

  #define RBSYS_GUARDREGION7_BASEADDR             0x00000000u
  #define RBSYS_GUARDREGION7_BASEADDR_SANITYCHECK 0x00000000u

  #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
    /* Defines for address sanity checks - comparing the BaseAddr with the value defined in RBSYS_GuardMemoryMap.h */

    #if(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_32K)
      /* use the 32K section (guard region 3) starting at BaseAddrOffset + MGDGRBAD3: 0xFEEF0000 */
      #define RBSYS_EthSharedGRAMStartAddressSanityCheck  (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION3_BASEADDR_SANITYCHECK)
    #elif(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_64K)
      /* use the 64K section (guard region 4) starting at BaseAddrOffset + MGDGRBAD4: 0xFEEE0000 */
      #define RBSYS_EthSharedGRAMStartAddressSanityCheck  (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION4_BASEADDR_SANITYCHECK)
    #elif(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K)
      /* use the 64K section (guard region 4) and the 32K (guard region 3) starting at BaseAddrOffset + MGDGRBAD4: 0xFEEE0000 */
      #define RBSYS_EthSharedGRAMStartAddressSanityCheck  (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION4_BASEADDR_SANITYCHECK)
    #elif (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K)
      #if( RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_Default )
        /* use the 128K section (guard region 5) starting at BaseAddrOffset + MGDGRBAD5: 0xFEEC0000 */
        #define RBSYS_EthSharedGRAMStartAddressSanityCheck  (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION5_BASEADDR_SANITYCHECK)
      #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) && (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR) )
        /* use the sections 64k (guard region 4) and 32k (region 3) and 2x16k (region 2,1) starting at BaseAddrOffset + MGDGRBAD4: 0xFEEE0000 */
        #define RBSYS_EthSharedGRAMStartAddressSanityCheck  (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION4_BASEADDR_SANITYCHECK)
      #endif
    #else // RBFS_SysEthSharedGRAMsize_0K  -- for length 0 we take start GRAM-bank B - BaseAddrOffset + MGDGRBAD0
      #define RBSYS_EthSharedGRAMStartAddressSanityCheck  (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION0_BASEADDR_SANITYCHECK)
    #endif

    #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K)
      /* use the 16K section (guard region 2) starting at BaseAddrOffset + MGDGRBAD2: 0xFEEF8000 */
      #define RBSYS_RestrExclGRAMStartAddressSanityCheck   (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION2_BASEADDR_SANITYCHECK)
    #elif(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K)
      /* use the 32K section (guard region 3) starting at BaseAddrOffset + MGDGRBAD3: 0xFEEF0000 */
      #define RBSYS_RestrExclGRAMStartAddressSanityCheck   (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION3_BASEADDR_SANITYCHECK)
    #else  // RBFS_RestrictedExclusiveGRAMsize_0K  -- for length 0 we take start GRAM-bank B - BaseAddrOffset + MGDGRBAD0
      #define RBSYS_RestrExclGRAMStartAddressSanityCheck   (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION0_BASEADDR_SANITYCHECK)
    #endif

    #if(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_16K)
      /* use the 16K section (guard region 1) starting at  BaseAddrOffset + MGDGRBAD1: 0xFEEFC000u */
      #define RBSYS_HsmSharedGRAMStartAddressSanityCheck  (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION1_BASEADDR_SANITYCHECK)
    #elif(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_32K)
      #if( RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_Default )
        /* use the 16K section (guard region 2) starting at BaseAddrOffset + MGDGRBAD2: 0xFEEF8000 */
        #define RBSYS_HsmSharedGRAMStartAddressSanityCheck  (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION2_BASEADDR_SANITYCHECK)
      #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) && (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR) )
        /* use the 32K (D3 only!) section (guard region 5) starting at BaseAddrOffset + MGDGRBAD5: 0xFEEC0000 */
        #define RBSYS_HsmSharedGRAMStartAddressSanityCheck  (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION5_BASEADDR_SANITYCHECK)
      #endif
    #else  // RBFS_SysHsmSharedGRAMsize_0K  -- for length 0 we take start GRAM-bank B - BaseAddrOffset + MGDGRBAD0
      #define RBSYS_HsmSharedGRAMStartAddressSanityCheck   (RBSYS_GRAMguardBaseAddrOffset + RBSYS_GUARDREGION0_BASEADDR_SANITYCHECK)
    #endif

    #if(RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K)

      /*  ********************************************************************** */
      /*  Sanity Check for the RBSYS_HsmSharedGRAMStartAddress exported to RBLCF */
      /*  ********************************************************************** */

      /* NO_TOOL_SCAN */
      /* REASON: GenProDB requires RBFS_ function switch in #if condition */
      #if (RBSYS_HsmSharedGRAMStartAddressSanityCheck != RBSYS_HsmSharedGRAMStartAddress)
        #error ("Start of shared GRAM for HSM in RBSYS and RBLCF is inconsistent !!!")
      #endif
      /* NO_TOOL_SCAN_END */

    #endif


    /*  ******************************************************************************** */
    /*  Sanity Check for the RBSYS_RestrictedExclusiveGRAMStartAddress exported to RBLCF */
    /*  ******************************************************************************** */

    /* NO_TOOL_SCAN */
    /* REASON: GenProDB requires RBFS_ function switch in #if condition */
    #if (RBSYS_RestrExclGRAMStartAddressSanityCheck != RBSYS_RestrictedExclusiveGRAMStartAddress)
      #error ("Start of exclusive GRAM for the Restricted SPID in RBSYS and RBLCF is inconsistent !!!")
    #endif
    /* NO_TOOL_SCAN_END */


    /*  *************************************************************************** */
    /*  Sanity Check for the RBSYS_EthernetSharedGRAMStartAddress exported to RBLCF */
    /*  *************************************************************************** */

    #if (RBFS_SysEthSharedGRAMsize != RBFS_SysEthSharedGRAMsize_0K)
      /* NO_TOOL_SCAN */
      /* REASON: GenProDB requires RBFS_ function switch in #if condition */
      #if (RBSYS_EthSharedGRAMStartAddressSanityCheck != RBSYS_EthernetSharedGRAMStartAddress)
        #error ("Start of shared GRAM for Ethernet in RBSYS and RBLCF is inconsistent !!!")
      #endif
      /* NO_TOOL_SCAN_END */
    #endif

  #endif

  #if( (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION) || (RBFS_RBSYSGlobalRAMGuardsBB == RBFS_RBSYSGlobalRAMGuardsBB_ON) )
    #if( (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON) )
      /**
        * @brief Setup PBUS Guards to protect other GRAM Guard configurations
        *
        * @param void
        *
        * @return void
        */
      extern void RBSYS_PBUSGuardInit_ForGRAMGuard(void);

      /**
        * @brief Configure GRAM Guards
        *
        * Each GRAM Guard has to be configured. Access to the GRAM Guards is protected via PBus-Guard.
        * 
        * Important: Before calling this function, ensure that access to the GRAM Guards is restricted to SAFE SPID only (via corresponding PBUS Guard) !!!
        *
        * @param void
        *
        * @return void
        */
      extern void RBSYS_GRAMGuardInit_Impl(void);
    #endif
  #endif


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
      *
      * @return void
      */
    static void RBSYS_TRAP_PERMISSION_ENTRY(void);
    asm void RBSYS_TRAP_PERMISSION_ENTRY(void)
    {
%lab Core0 %lab Core1 %lab StackAccess %lab end
      syncm                 -- assure that all memory writes are finished

      ldsr r9,EIWR,0        -- EIWR = r9
      stsr 0,r9,1           -- r9 = MCFG0 (current SPID)
      ldsr r9,FEWR,0        -- FEWR = r9

      -- Attention: 0x00020004 is the "value after reset" for MCFG0 so Read-Modify-Write is not needed here
      mov 0x00020004,r9     -- r9 = 0x00020004 (Safe SPID)
      ldsr r9,0,1           -- MCFG0 = r9

      -- See P1x UM Rev. 1.30 Chapter 3.4.8 "System Register Hazards"
      syncp
      synci

      -- Get Core specific Stack
      stsr 0,r9,2           -- r9 = HTCFG0
      shr 17,r9             -- r9 >>= 17 (CY bit set if Bit 16 was '1' -> Core 0)
      bnc Core1             -- if CY == 0 (Core 1)
Core0:
      mov ep,r9             -- r9 = EP (current Element Pointer)
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
      *
      * @return void
      */
    static void RBSYS_TRAP_PERMISSION_LEAVE(void);
    asm void RBSYS_TRAP_PERMISSION_LEAVE(void)
    {
%lab Core0 %lab Core1 %lab StackAccess %lab end
      syncm                -- assure that all memory writes are finished

      ldsr r9,EIWR,0       -- EIWR = r9
      ldsr ep,FEWR,0       -- FEWR = EP

      -- Get Core specific Stack
      stsr 0,r9,2           -- r9 = HTCFG0
      shr 17,r9             -- r9 >>= 17 (CY bit set if Bit 16 was '1' -> Core 0)
      bnc Core1             -- if CY == 0 -> jump to Core1 handling
Core0:
      mov _RBSYS_TrapPermissionHandlingStack0_StartAddressPtr,ep
      br StackAccess
Core1:
      mov _RBSYS_TrapPermissionHandlingStack1_StartAddressPtr,ep
      br StackAccess

StackAccess:
      sld.w 0[ep],ep       -- EP = *StackStartAddress
      sld.w (4)[ep], r9    -- r9 = Stack[1] (original SPID)
      ldsr r9,0,1          -- MCFG0 = r9 (original SPID)

      -- See P1x UM Rev. 1.30 Chapter 3.4.8 "System Register Hazards"
      syncp
      synci

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