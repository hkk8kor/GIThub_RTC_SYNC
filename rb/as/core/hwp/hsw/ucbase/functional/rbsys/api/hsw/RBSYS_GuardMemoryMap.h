#ifndef RBSYS_GUARDMEMORYMAP_H__
#define RBSYS_GUARDMEMORYMAP_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Memory map restrictions due to GRAM guard
 *
 * This interface provides as result of the guard configuration the restricted memory map
 * for unsafe bus masters like HSM.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


/* NO:    RB_ASSERT_SWITCH_SETTINGS  due to similar use as  RBLCF_LDAddOn.h  !!!!!!!!!!
 * Only C preprocessor directives such as #define, #include, #if, and #ifdef should be evaluted and included in the LD file.
 * All others (e.g. enum, extern declaration, RB_ASSERT_SWITCH_SETTINGS...) must be removed while preprocessing, otherwise linker will abort.
 *
 * Only for MTC 10.6 or later can the linker handling interpret all the syntax in RBSYS_Config.h
 * Therefore we include here for backwards compatibility only the linker compatible files for the required project config (RB_Config.h) and
 * RBSYS internal defaulting (RBSYS_DefaultElementsPure.h)! */
#include "RB_Config.h"                          ///< for RBFS_HardwareSecurityModule, RBFS_RestrictedExclusiveGRAMsize
#include "RBSYS_DefaultElementsPure.h"          ///< for RBFS_SysEthSharedGRAMsize, RBFS_SysHsmSharedGRAMsize

// IMPORTANT: This file forwards the function switch RBFS_RestrictedExclusiveGRAMsize to RAMSafety


#if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  #define RBSYS_GRAMBankBStart    0xFEF00000 //< deprecated but kept for old lcf
  #define RBSYS_GRAMBankAEnd      0xFEEFFFFF
#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  #define RBSYS_CRAM0BankEnd      0xFE07FFFF
#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
  #if(RBFS_TargetDevice == RBFS_TargetDevice_RenesasK0)
    #define RBSYS_CRAM0BankEnd      0xFE027FFF
  #elif(RBFS_TargetDevice == RBFS_TargetDevice_RenesasK1)
    #define RBSYS_CRAM0BankEnd      0xFE06FFFF
  #endif
#elif( (RBFS_uCFamily == RBFS_uCFamily_STMStellar) )
  #define RBSYS_CRAM0_0Start      0x60000000
  #define RBSYS_CRAM0_0End        0x603FFFFF
  #define RBSYS_CRAM0_1Start      0x60400000
  #define RBSYS_CRAM0_1End        0x607FFFFF
#endif


/* *************************************************************************** */
/*    Shared GRAM between   HSM   and    normal SW                             */
/*                                                                             */
/*  (for this usecase only Start and Size are needed for export!)              */
/* *************************************************************************** */

#if (RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Supported)

  #if(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_16K)
    #define RBSYS_HsmSharedGRAMSize    (16*1024)
  #elif(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_32K)
    #define RBSYS_HsmSharedGRAMSize    (32*1024)
  #else
    #define RBSYS_HsmSharedGRAMSize    0
  #endif

#else
  #define RBSYS_HsmSharedGRAMSize    0
#endif

/* sections used for sharedRAM depend on sharedRAMSize - they must always be located at the end of Bank A! (only if RBFS_SysRAMLayoutFragmentation_Default) */
#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_Default) )
  #define RBSYS_HsmSharedGRAMEndAddress     (RBSYS_GRAMBankAEnd + 1)
#elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) && (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR) )
  /* Special Case "GRAM Optimized for BLDR @ D3": Shared RAM allocated at start of BankA to store bigger BLDR without fragmentation */
  #define RBSYS_HsmSharedGRAMEndAddress      0xFEEE0000
#elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
  #define RBSYS_HsmSharedGRAMEndAddress     (RBSYS_CRAM0BankEnd + 1)
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #define RBSYS_HsmSharedGRAMEndAddress     (RBSYS_CRAM0_1End + 1)
#else
  #error ("Exception: Implementation for this uCFamily is missing")
#endif

#define RBSYS_HsmSharedGRAMStartAddress   (RBSYS_HsmSharedGRAMEndAddress - RBSYS_HsmSharedGRAMSize)
/* *************************************************************************** */


#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_STMStellar) )



  /* *************************************************************************** */
  /*    Exclusive GRAM in case of the 'Restricted SPID'- feature                 */
  /*                                                                             */
  /*  (for this usecase Start and Size are needed for export as well as the      */
  /*   size for in-between parts where the Host can allocate GRAM!)              */
  /* *************************************************************************** */

  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )

    #if (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K)
      #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K)
        /* use the 16K section (guard region 2) starting at 0xFEEF8000 */
        #define RBSYS_RestrictedExclusiveGRAMStartAddress   0xFEEF8000
        #define RBSYS_RestrictedExclusiveGRAMSize    (16*1024)
      #elif(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K)
        /* use the 32K section (guard region 3) starting at 0xFEEF0000 */
        #define RBSYS_RestrictedExclusiveGRAMStartAddress   0xFEEF0000
        #define RBSYS_RestrictedExclusiveGRAMSize    (32*1024)
      #else  // should not be possible, only coded because this file cannot have AssertSwitchSettings due to older MTCs
        #define RBSYS_RestrictedExclusiveGRAMStartAddress   0xFEF00000
        #define RBSYS_RestrictedExclusiveGRAMSize    0
      #endif

      /* the upper part2 (above guard region for exclusive Restricted SPID use) left for normal GRAM is the distance of RBSYS_RestrictedExclusiveGRAMStartAddress from RBSYS_GRAMBankBStart minus RBSYS_RestrictedExclusiveGRAMSize minus possible HSM shared GRAM */
      #define RBSYS_UpperPart2BankAGRAMSize    (RBSYS_GRAMBankBStart - RBSYS_RestrictedExclusiveGRAMStartAddress - RBSYS_RestrictedExclusiveGRAMSize - RBSYS_HsmSharedGRAMSize)

    #else
    /* define start of GRAM Bank B as start for length 0 */
      #define RBSYS_RestrictedExclusiveGRAMStartAddress   0xFEF00000
      #define RBSYS_RestrictedExclusiveGRAMSize    0
      #define RBSYS_UpperPart2BankAGRAMSize        0
    #endif

  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

    #define RBSYS_RestrictedExclusiveGRAMStartAddress     0xFE800000
    #if( RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_64K )
      #define RBSYS_RestrictedExclusiveGRAMSize    (64*1024)
    #elif( RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_128K )
      #define RBSYS_RestrictedExclusiveGRAMSize    (128*1024)
    #elif( RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_256K )
      #define RBSYS_RestrictedExclusiveGRAMSize    (256*1024)
    #endif

  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

    #if  ( RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_0K )
      #define RBSYS_RestrictedExclusiveGRAMSize    (0*1024)
    #elif  ( RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K )
      #define RBSYS_RestrictedExclusiveGRAMSize    (16*1024)
    #elif( RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K )
      #define RBSYS_RestrictedExclusiveGRAMSize    (32*1024)
    #elif( RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_64K )
      #define RBSYS_RestrictedExclusiveGRAMSize    (64*1024)
    #else
      #error ("Wrong configuration of RestrictedExclusiveGRAMsize for this uCFamily")
    #endif
    #define RBSYS_RestrictedExclusiveGRAMStartAddress   (RBSYS_HsmSharedGRAMStartAddress - RBSYS_RestrictedExclusiveGRAMSize)

  #else
    #error ("Exception: Implementation for this uCFamily is missing")
  #endif
  /* *************************************************************************** */

  /* *************************************************************************** */
  /*    Shared GRAM between   Ethernet   and    normal SW                        */
  /*                                                                             */
  /*  (for this usecase Start and Size are needed for export as well as the      */
  /*   size for in-between parts where the Host can allocate GRAM!)              */
  /* *************************************************************************** */

  #if (RBFS_SysEthSharedGRAMsize != RBFS_SysEthSharedGRAMsize_0K)

    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
      #if(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_32K)
        /* use the 32K section (guard region 3) starting at 0xFEEF0000 */
        #define RBSYS_EthernetSharedGRAMStartAddress   0xFEEF0000
        #define RBSYS_EthernetSharedGRAMSize    (32*1024)
      #elif(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_64K)
        /* use the 64K section (guard region 4) starting at 0xFEEE0000 */
        #define RBSYS_EthernetSharedGRAMStartAddress   0xFEEE0000
        #define RBSYS_EthernetSharedGRAMSize    (64*1024)
      #elif(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K)
        /* use the 64K section (guard region 4) and the 32K (guard region 3) starting at 0xFEEE0000 */
        #define RBSYS_EthernetSharedGRAMStartAddress   0xFEEE0000
        #define RBSYS_EthernetSharedGRAMSize    (96*1024)
      #elif (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K)
        #define RBSYS_EthernetSharedGRAMSize    (128*1024)

        #if( RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_Default )
          /* use the 128K section (guard region 5) starting at 0xFEEC0000 */
          #define RBSYS_EthernetSharedGRAMStartAddress   0xFEEC0000
        #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) && (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR) )
          /* use the 64K+32K+16K+16K sections (guard region 4,3,2,1) starting at 0xFEEE0000 */
          #define RBSYS_EthernetSharedGRAMStartAddress   0xFEEE0000
        #endif
      #else // should not be possible, only coded because this file cannot have AssertSwitchSettings due to older MTCs
        #define RBSYS_EthernetSharedGRAMStartAddress   0xFEF00000
        #define RBSYS_EthernetSharedGRAMSize    0
      #endif

      /* the upper part (above guard regions for shared Ethernet) left for normal GRAM is the distance of RBSYS_EthernetSharedGRAMStartAddress from RBSYS_GRAMBankBStart minus RBSYS_EthernetSharedGRAMSize minus possible HSM shared GRAM minus possible exclusive Restricted SPID GRAM minus a possible UpperPart2 */
      #define RBSYS_UpperPartBankAGRAMSize    (RBSYS_GRAMBankBStart - RBSYS_EthernetSharedGRAMStartAddress - RBSYS_EthernetSharedGRAMSize - RBSYS_HsmSharedGRAMSize - RBSYS_RestrictedExclusiveGRAMSize - RBSYS_UpperPart2BankAGRAMSize)

    #elif( (RBFS_uCFamily == RBFS_uCFamily_STMStellar) )

      #if(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_32K)
        #define RBSYS_EthernetSharedGRAMSize    (32*1024)
      #elif(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_64K)
        #define RBSYS_EthernetSharedGRAMSize    (64*1024)
      #elif(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K)
        #define RBSYS_EthernetSharedGRAMSize    (96*1024)
      #elif (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K)
        #define RBSYS_EthernetSharedGRAMSize    (128*1024)
      #endif

      #define RBSYS_EthernetSharedGRAMStartAddress   (RBSYS_RestrictedExclusiveGRAMStartAddress - RBSYS_EthernetSharedGRAMSize)

    #endif
  #else

    // dummy address for start of section with length 0
    #define RBSYS_EthernetSharedGRAMStartAddress 0x00000000
    #define RBSYS_EthernetSharedGRAMSize    0
    #define RBSYS_UpperPartBankAGRAMSize    0
  #endif
  /* *************************************************************************** */

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

  /* *************************************************************************** */
  /*    Shared GRAM between   Ethernet   and    normal SW                        */
  /*                                                                             */
  /*  (for this usecase Start and Size are needed for export as well as the      */
  /*   size for in-between parts where the Host can allocate GRAM!)              */
  /* *************************************************************************** */
  #if(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_32K)
    #define RBSYS_EthernetSharedGRAMSize    (32*1024)
  #else
    #define RBSYS_EthernetSharedGRAMSize    0
  #endif
  #define RBSYS_EthernetSharedGRAMStartAddress   (RBSYS_HsmSharedGRAMStartAddress - RBSYS_EthernetSharedGRAMSize)
  /* *************************************************************************** */


  /* *************************************************************************** */
  /*    Exclusive GRAM in case of the 'Restricted SPID'- feature                 */
  /*                                                                             */
  /*  (for this usecase Start and Size are needed for export as well as the      */
  /*   size for in-between parts where the Host can allocate GRAM!)              */
  /* *************************************************************************** */
  #if( RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K )
    #define RBSYS_RestrictedExclusiveGRAMSize         (16*1024)
  #elif( RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K )
    #define RBSYS_RestrictedExclusiveGRAMSize         (32*1024)
  #else
    #define RBSYS_RestrictedExclusiveGRAMSize         (0)
  #endif
  #define RBSYS_RestrictedExclusiveGRAMStartAddress   (RBSYS_EthernetSharedGRAMStartAddress - RBSYS_RestrictedExclusiveGRAMSize)
  /* *************************************************************************** */

#else
  #error("Missing implementation for this RBFS_uCFamily setting")
#endif

#if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
  /* ***************************************************************************** */
  /* Functions for RAMSafety to modify GRAM guard for access by Safe-SPID and back */
  /* ***************************************************************************** */

  /**
    * @brief Set RestrictedExclusiveGRAM area from "Restricted" SPID to ("Safe" + "Restricted") SPID
    *
    * API is only allowed to be called by RBRAMSafety to reconfigure the restricted exclusive GRAM guard area for Safe-Access during cyclic RAM test.
    * The user (here: RBRAMSafety) must ensure that this API is called at least under core local lock to suppress any kind of interruption.
    * Further on it must be ensured that no other bus master will access this area with the "Restricted" SPID till it's reconfigured again.
    *
    * @return void
    */
  extern void RBSYS_RestrictedExclusiveGRAM_AllowSafeAccess(void);

  /**
    * @brief Set allowed SPIDs of RestrictedExclusiveGRAM area from ("Safe" + "Restricted") SPID to "Restricted" SPID
    *
    * API is only allowed to be called by RBRAMSafety to reconfigure the restricted exclusive GRAM guard area for Safe-Access during cyclic RAM test.
    *
    * @return void
    */
  extern void RBSYS_RestrictedExclusiveGRAM_BlockSafeAccess(void);
#endif



#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  /* Issue with Stellar NOC Firewall regions: StartAddress + Size may not exceed UINT32_MAX */

  #define RBSYS_Cluster0_REGION_0_START (0x00000000)
  #define RBSYS_Cluster0_REGION_0_SIZE  (0x28800000) // until end of NVM_0_1

  #define RBSYS_Cluster0_REGION_1_START (RBSYS_Cluster0_REGION_0_START + RBSYS_Cluster0_REGION_0_SIZE)
  #define RBSYS_Cluster0_REGION_1_SIZE  ((RBSYS_CRAM0_1End - RBSYS_Cluster0_REGION_1_START) + 1 - RBSYS_EthernetSharedGRAMSize - RBSYS_HsmSharedGRAMSize - RBSYS_RestrictedExclusiveGRAMSize)
  // Example:  SIZE = 0x607FFFFF - 0x00000000 + 1 - 0 - 0 - 0 = 0x60800000  -> covers Address space 0x00000000 - 0x607FFFFF

  #define RBSYS_Cluster0_REGION_LAST_START (RBSYS_CRAM0_1End + 1)
  #define RBSYS_Cluster0_REGION_LAST_SIZE  (0xFFFFFFC0 - RBSYS_Cluster0_REGION_LAST_START)
  // Example:  SIZE = 0xFFFFFFC0 - 0x60800000 = 0x9F7FFFC0 -> covers Address space 0x60800000 - 0xFFFFFFC0

  #define RBSYS_Cluster1_REGION_0_START (0x00000000)
  #define RBSYS_Cluster1_REGION_0_SIZE  (0x29000000)

  #define RBSYS_Cluster1_REGION_1_START (RBSYS_Cluster1_REGION_0_START + RBSYS_Cluster1_REGION_0_SIZE)
  #define RBSYS_Cluster1_REGION_1_SIZE  (0xFFFFFFC0 - RBSYS_Cluster1_REGION_1_START)
  // NVM_1_0, NVM_1_1 shall be executable, whereas other memory shall be accessible only

  #define RBSYS_Cluster2_REGION_0_START (0x00000000)
  #define RBSYS_Cluster2_REGION_0_SIZE  (0x29800000)

  #define RBSYS_Cluster2_REGION_1_START (RBSYS_Cluster2_REGION_0_START + RBSYS_Cluster2_REGION_0_SIZE)
  #define RBSYS_Cluster2_REGION_1_SIZE  (0xFFFFFFC0 - RBSYS_Cluster2_REGION_1_START)
  // NVM_2_0, NVM_2_1 shall be executable, whereas other memory shall be accessible only

#endif

/* *************************************************************************** */



/* *************************************************************************** */
/*    Shared CRAM between   DMA   and    normal SW                             */
/*                                                                             */
/*  (for this usecase Start and Size are needed for export as well as the      */
/*   size for in-between parts where the Host can allocate GRAM!)              */
/*   Attention: only needed for U2A because DMA is not a safe busmaster        */
/* *************************************************************************** */

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

  #define RBSYS_DMASharedRAMSize                (8*1024)
  #if( RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_0K )
    #define RBSYS_DMASharedRAMStartAddress        (0xFE080000 - RBSYS_DMASharedRAMSize)
  #elif( RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_16K )
    #define RBSYS_DMASharedRAMStartAddress        (0xFE080000 - (16*1024) - RBSYS_DMASharedRAMSize)
  #elif( RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_32K )
    #define RBSYS_DMASharedRAMStartAddress        (0xFE080000 - (32*1024) - RBSYS_DMASharedRAMSize)
  #endif
  #define RBSYS_DMASharedRAMEndAddress          (RBSYS_DMASharedRAMStartAddress + RBSYS_DMASharedRAMSize)

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

  #define RBSYS_DMASharedRAMSize                (8*1024)
  #define RBSYS_DMASharedRAMStartAddress        (RBSYS_RestrictedExclusiveGRAMStartAddress - RBSYS_DMASharedRAMSize)
  #define RBSYS_DMASharedRAMEndAddress          (RBSYS_DMASharedRAMStartAddress + RBSYS_DMASharedRAMSize)

#endif

/* *************************************************************************** */

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
