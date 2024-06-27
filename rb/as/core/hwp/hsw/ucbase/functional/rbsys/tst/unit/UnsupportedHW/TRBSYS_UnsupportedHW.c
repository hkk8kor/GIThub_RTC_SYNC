#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                // for RBFS_uC, RBFS_CpuClock
#include "TRBRCFG_UnsupportedConfig.h"
#include "TRBSYS_uCRegisters.h"
#include "RBSYS_Subsystem.h"
#include "RBSYS_CpuVersions.h"

#include "Monitorings/RBSYS_UnsupportedHW.h"
#include "TRBSYS_UnsupportedHW_Adaptor.h"


/* when adapting this list, take care to also adapt the unsupportedProductIDs list below accordingly */
static RBSYS_ProductID_t supportedProductIDs[] = {
  #if(RBFS_EmulationDevice == RBFS_EmulationDevice_None)
    #if (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1)
      #if (RBFS_uCPackage == RBFS_uCPackage_QFP80)
        RBSYS_CPU_REL_D1_LQFP80_EVR_V100_IDs,          /* D1 Rev0 with eVR (embedded voltage regulator) in LQFP80 package - R7F701343   */
      #endif
      #if (RBFS_uCPackage == RBFS_uCPackage_QFP100)
        RBSYS_CPU_REL_D1_LQFP100_EVR_V100_IDs,         /* D1 Rev0 with eVR (embedded voltage regulator) in LQFP100 package - R7F701341  */
      #endif
    #elif (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2)
      #if (RBFS_uCPackage == RBFS_uCPackage_QFP100)
        RBSYS_CPU_REL_D2_LQFP100_EVR_V100_IDs,         /* D2 Rev0 with eVR (embedded voltage regulator) in LQFP100 package - R7F701339  */
      #endif
      #if (RBFS_uCPackage == RBFS_uCPackage_QFP144)
        RBSYS_CPU_REL_D2_LQFP144_EVR_V100_IDs,         /* D2 Rev0 with eVR (embedded voltage regulator) in LQFP144 package - R7F701337  */
      #endif
    #elif (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3)
      #if (RBFS_uCPackage == RBFS_uCPackage_QFP144)
        RBSYS_CPU_REL_D3_LQFP144_DPS_V100_IDs,         /* D3 Rev0 with DPS (dual power supply) in LQFP144 package - R7F701330           */
        RBSYS_CPU_REL_D3_HQFP144_EVR_V100_IDs,         /* D3 Rev0 with eVR (embedded voltage regulator) in HQFP144 package - R7F701333  */
        RBSYS_CPU_REL_D3_REV_A_LQFP144_DPS_V100_IDs,   /* D3 RevA with DPS (dual power supply) in LQFP144 package - R7F701330A          */
        RBSYS_CPU_REL_D3_REV_A_HQFP144_EVR_V100_IDs,   /* D3 RevA with eVR (embedded voltage regulator) in HQFP144 package - R7F701333A */
        #if ( (RBFS_CpuClock == RBFS_CpuClock_160MHz) \
           || ( (RBFS_CpuClock == RBFS_CpuClock_240MHz) && (RBFS_CpuClockRestriction == RBFS_CpuClockRestriction_OFF) ) \
            )
          RBSYS_CPU_REL_D3_LQFP144_EVR_V100_IDs,       /* D3 Rev0 with eVR (embedded voltage regulator) in LQFP144 package - R7F701331  */
          RBSYS_CPU_REL_D3_REV_A_LQFP144_EVR_V100_IDs, /* D3 RevA with eVR (embedded voltage regulator) in LQFP144 package - R7F701331A */
        #endif
      #endif
      #if (RBFS_uCPackage == RBFS_uCPackage_BGA156)
        RBSYS_CPU_REL_D3_REV_A_BGA156_DPS_V100_IDs,    /* D3 RevA with DPS (dual power supply) in BGA156 package - R7F701393A           */
      #endif
      #if (RBFS_uCPackage == RBFS_uCPackage_BGA292)
        RBSYS_CPU_REL_D3_BGA292_DPS_V100_IDs,          /* D3 Rev0 with DPS (dual power supply) in BGA292 package - R7F701328            */
        RBSYS_CPU_REL_D3_BGA292_EVR_V100_IDs,          /* D3 Rev0 with eVR (embedded voltage regulator) in BGA292 package - R7F701329   */
        RBSYS_CPU_REL_D3_REV_A_BGA292_DPS_V100_IDs,    /* D3 RevA with DPS (dual power supply) in BGA292 package - R7F701328A           */
        RBSYS_CPU_REL_D3_REV_A_BGA292_EVR_V100_IDs,    /* D3 RevA with eVR (embedded voltage regulator) in BGA292 package - R7F701329A  */
      #endif
    #elif (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4)
      /* D4 always comes in BGA292 package */
      RBSYS_CPU_REL_D4_REV_A_V100_IDs,                 /* D4 RevA - R7F701327A */
    #elif (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5)
      /* D5 always comes in BGA292 package */
      RBSYS_CPU_REL_D5_REV_0_V100_IDs,                 /* D5 Rev0 - R7F701326  */
    #elif (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2)
      #if (RBFS_uCPackage == RBFS_uCPackage_QFP144)
        RBSYS_CPU_REL_M2_QFP144_V100_IDs,              /* M2 in QFP144 package v1.00 - R7F702302 */
      #endif
      #if (RBFS_uCPackage == RBFS_uCPackage_BGA292)
        RBSYS_CPU_REL_M2_BGA292_V100_IDs,              /* M2 in BGA292 package v1.00 - R7F702302 */
      #endif
    #elif (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3)
      RBSYS_CPU_REL_M3_BGA292_V100_IDs,                /* M3 in BGA292 package v1.00 - R7F702301 */
      RBSYS_CPU_REL_M3_BGA292_V110_IDs,                /* M3 in BGA292 package v1.10 - R7F702301A */
      RBSYS_CPU_REL_M3_BGA292_V120_IDs,                /* M3 in BGA292 package v1.20 - R7F702301B */
    #elif ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) )
      RBSYS_CPU_REL_M6_BGA292_V100_IDs,                /* M6 in BGA292 package v1.00 - R7F702300 */
      RBSYS_CPU_REL_M6_BGA292_V110_IDs,                /* M6 in BGA516 package v1.10 - R7F702300A */
      RBSYS_CPU_REL_M6_BGA292_V120_IDs,                /* M6 in BGA516 package v1.20 - R7F702300B */
    #endif
  #endif

  #if ( ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) \
       || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2) \
       || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) ) \
     && (RBFS_EmulationDevice != RBFS_EmulationDevice_RenesasD5ED) \
      )
    #if ( (RBFS_uCPackage == RBFS_uCPackage_QFP80) \
       || (RBFS_uCPackage == RBFS_uCPackage_QFP100) \
       || (RBFS_uCPackage == RBFS_uCPackage_QFP144) \
       || (RBFS_uCPackage == RBFS_uCPackage_BGA156) \
        )
      RBSYS_CPU_REL_D3ED_V100_IDs,                     /* D3ED RevA - R7F701334A */
      RBSYS_CPU_REL_D3ED_REV_B_V100_IDs,               /* D3ED RevB - R7F701334B */
    #endif
  #endif

  #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) \
     || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) \
     || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5) \
     || (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD3ED) \
      )
    RBSYS_CPU_REL_D5EDV2_V100_IDs,                   /* D5EDv2 - R7F701325A */
    RBSYS_CPU_REL_D5EDV3_V100_IDs,                   /* D5EDv3 - R7F701325B */
  #endif

  #if ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    RBSYS_CPU_REL_M6ED_BGA292_V110_IDs,              /* M6ED in BGA292 package v1.10 - R7F702Z19A */
    RBSYS_CPU_REL_M6ED_BGA404_V110_IDs,              /* M6ED in BGA404 package v1.10 - R7F702Z19A */
    RBSYS_CPU_REL_M6ED_BGA516_V110_IDs,              /* M6ED in BGA516 package v1.10 - R7F702Z19A */
    RBSYS_CPU_REL_M6ED_BGA404_V120_IDs,              /* M6ED in BGA404 package v1.20 - R7F702Z19B */
    RBSYS_CPU_REL_M6ED_BGA516_V120_IDs,              /* M6ED in BGA516 package v1.20 - R7F702Z19B */
  #endif

  #if  (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
    RBSYS_CPU_REL_K3ED_BGA404_DPS_V100_IDs,

    #if( RBFS_EmulationDevice == RBFS_EmulationDevice_None )
      #if(RBFS_TargetDevice == RBFS_TargetDevice_RenesasK0)
        RBSYS_CPU_REL_K0_QFP144_EVR_V100_IDs,
      #elif(RBFS_TargetDevice == RBFS_TargetDevice_RenesasK1)
        RBSYS_CPU_REL_K1_QFP144_EVR_V100_IDs,
        RBSYS_CPU_REL_K1_BGA292_EVR_V100_IDs,
      #endif
    #endif

  #endif

  #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    RBSYS_CPU_STM_X7_BGA292_IDs,
    RBSYS_CPU_STM_X7_BGA516_IDs,
    // RBSYS_CPU_STM_P7_BGA292_IDs,
    RBSYS_CPU_STM_P6_BGA292_IDs,
  #endif
};

/* The following array lists PRDNAME2, PRDNAME3 and PRDSEL3 (P1x) or PRDNUM (U2A) of devices that are explicitly not supported by the current configuration */
RBSYS_ProductID_t unsupportedProductIDs[] = {
  #if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
    RBSYS_CPU_REL_D2_LQFP144_EVR_ICUS_V100_IDs,    /* D2 Rev0 with ICU-S - R7F701336 */
    RBSYS_CPU_REL_D5EDV1_V100_IDs,                 /* D5EDv1 - R7F701325 */
    RBSYS_CPU_REL_D4_V200_IDs,                     /* D4 Rev0 - R7F701327  */
  #elif ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    RBSYS_CPU_REL_M3_BGA373_V110_IDs,              /* M3 in BGA373 package v1.10   - R7F702301A */
    RBSYS_CPU_REL_M3_BGA373_V120_IDs,              /* M3 in BGA373 package v1.20   - R7F702301B */
    RBSYS_CPU_REL_M6_BGA373_V110_IDs,              /* M6 in BGA373 package v1.10   - R7F702300A */
    RBSYS_CPU_REL_M6_BGA373_V120_IDs,              /* M6 in BGA373 package v1.20   - R7F702300B */
    RBSYS_CPU_REL_M6_BGA516_V100_IDs,              /* M6 in BGA516 package v1.00   - R7F702300 */
    RBSYS_CPU_REL_M6_BGA516_V110_IDs,              /* M6 in BGA516 package v1.10   - R7F702300A */
    RBSYS_CPU_REL_M6_BGA516_V120_IDs,              /* M6 in BGA516 package v1.20   - R7F702300B */
    RBSYS_CPU_REL_M6ED_BGA516_V100_IDs,            /* M6ED in BGA292 package v1.00 - R7F702Z19 */
    RBSYS_CPU_REL_M6ED_BGA292_V100_IDs,            /* M6ED in BGA516 package v1.00 - R7F702Z19 */
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
    RBSYS_CPU_REL_K3_BGA292_DPS_V100_IDs,          /* K3 in BGA292 package v1.00        -> not supported yet */
    RBSYS_CPU_REL_K1_BGA292_DPS_V100_IDs,          /* K1 in BGA292 package v1.00 w/ DPS -> not supported */
    RBSYS_CPU_REL_K1_BGA156_DPS_V100_IDs,          /* K1 in BGA156 package v1.00        -> not supported */
    RBSYS_CPU_REL_K1_BGA156_EVR_V100_IDs,          /* K1 in BGA156 package v1.00        -> not supported */
    RBSYS_CPU_REL_K1_QFP144_DPS_V100_IDs,          /* K1 in QFP144 package v1.00 w/ DPS -> not supported */
    RBSYS_CPU_REL_K0_BGA156_EVR_V100_IDs,          /* K0 in BGA156 package v1.00        -> not supported */
  #endif

  /* All generally supported devices that are unsupported with the current device */
  #if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
    #if ( (RBFS_uC != RBFS_uC_RenesasD1) \
       || (RBFS_uCPackage != RBFS_uCPackage_QFP80) )
      RBSYS_CPU_REL_D1_LQFP80_EVR_V100_IDs,        /* D1 Rev0 with eVR (embedded voltage regulator) in LQFP80 package - R7F701343   */
    #endif
    #if ( (RBFS_uC != RBFS_uC_RenesasD1) \
       || (RBFS_uCPackage != RBFS_uCPackage_QFP100) )
      RBSYS_CPU_REL_D1_LQFP100_EVR_V100_IDs,       /* D1 Rev0 with eVR (embedded voltage regulator) in LQFP100 package - R7F701341  */
    #endif
    #if ( (RBFS_uC != RBFS_uC_RenesasD2) \
       || (RBFS_uCPackage != RBFS_uCPackage_QFP100) )
      RBSYS_CPU_REL_D2_LQFP100_EVR_V100_IDs,       /* D2 Rev0 with eVR (embedded voltage regulator) in LQFP100 package - R7F701339  */
    #endif
    #if ( (RBFS_uC != RBFS_uC_RenesasD2) \
       || (RBFS_uCPackage != RBFS_uCPackage_QFP144) )
      RBSYS_CPU_REL_D2_LQFP144_EVR_V100_IDs,       /* D2 Rev0 with eVR (embedded voltage regulator) in LQFP144 package - R7F701337  */
    #endif
    #if ( ( (RBFS_uC != RBFS_uC_Renesas160MHzD3) && (RBFS_uC != RBFS_uC_Renesas240MHzD3) ) \
       || (RBFS_uCPackage != RBFS_uCPackage_QFP144) )
      RBSYS_CPU_REL_D3_LQFP144_DPS_V100_IDs,       /* D3 Rev0 with DPS (dual power supply) in LQFP144 package - R7F701330           */
      RBSYS_CPU_REL_D3_REV_A_LQFP144_DPS_V100_IDs, /* D3 RevA with DPS (dual power supply) in LQFP144 package - R7F701330A          */
      RBSYS_CPU_REL_D3_REV_A_HQFP144_EVR_V100_IDs, /* D3 RevA with eVR (embedded voltage regulator) in HQFP144 package - R7F701333A */
    #endif
    #if ( ( (RBFS_uC != RBFS_uC_Renesas160MHzD3) && (RBFS_uC != RBFS_uC_Renesas240MHzD3) ) \
       || (RBFS_uCPackage != RBFS_uCPackage_BGA156) )
      RBSYS_CPU_REL_D3_REV_A_BGA156_DPS_V100_IDs,  /* D3 RevA with DPS (dual power supply) in BGA156 package - R7F701393A           */
    #endif
    #if ( ( (RBFS_uC != RBFS_uC_Renesas160MHzD3) && (RBFS_uC != RBFS_uC_Renesas240MHzD3) ) \
       || (RBFS_uCPackage != RBFS_uCPackage_BGA292) )
      RBSYS_CPU_REL_D3_BGA292_DPS_V100_IDs,        /* D3 Rev0 with DPS (dual power supply) in BGA292 package - R7F701328            */
      RBSYS_CPU_REL_D3_BGA292_EVR_V100_IDs,        /* D3 Rev0 with eVR (embedded voltage regulator) in BGA292 package - R7F701329   */
      RBSYS_CPU_REL_D3_REV_A_BGA292_DPS_V100_IDs,  /* D3 RevA with DPS (dual power supply) in BGA292 package - R7F701328A           */
      RBSYS_CPU_REL_D3_REV_A_BGA292_EVR_V100_IDs,  /* D3 RevA with eVR (embedded voltage regulator) in BGA292 package - R7F701329A  */
    #endif
    #if ( ( (RBFS_uC != RBFS_uC_Renesas160MHzD3) \
         && ( (RBFS_uC != RBFS_uC_Renesas240MHzD3) || (RBFS_CpuClockRestriction != RBFS_CpuClockRestriction_OFF) ) ) \
       || (RBFS_uCPackage != RBFS_uCPackage_QFP144) )
      RBSYS_CPU_REL_D3_LQFP144_EVR_V100_IDs,       /* D3 Rev0 with eVR (embedded voltage regulator) in LQFP144 package - R7F701331  */
      RBSYS_CPU_REL_D3_REV_A_LQFP144_EVR_V100_IDs, /* D3 RevA with eVR (embedded voltage regulator) in LQFP144 package - R7F701331A */
    #endif
    #if (RBFS_uC != RBFS_uC_RenesasD4)
      RBSYS_CPU_REL_D4_REV_A_V100_IDs,             /* D4 RevA - R7F701327A */
    #endif
    #if (RBFS_uC != RBFS_uC_RenesasD5)
      RBSYS_CPU_REL_D5_REV_0_V100_IDs,             /* D5 Rev0 - R7F701326  */
    #endif
  #elif ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    #if ( (RBFS_uC != RBFS_uC_RenesasM2) \
       || (RBFS_uCPackage != RBFS_uCPackage_QFP144) )
      RBSYS_CPU_REL_M2_QFP144_V100_IDs,            /* M2 in QFP144 package v1.00 - R7F702302  */
    #endif
    #if ( (RBFS_uC != RBFS_uC_RenesasM2) \
       || (RBFS_uCPackage != RBFS_uCPackage_BGA292) )
      RBSYS_CPU_REL_M2_BGA292_V100_IDs,            /* M2 in BGA292 package v1.00 - R7F702302  */
    #endif
    #if (RBFS_uC != RBFS_uC_RenesasM3)
      RBSYS_CPU_REL_M3_BGA292_V100_IDs,            /* M3 in BGA292 package v1.00 - R7F702301  */
      RBSYS_CPU_REL_M3_BGA292_V110_IDs,            /* M3 in BGA292 package v1.10 - R7F702301A */
      RBSYS_CPU_REL_M3_BGA292_V120_IDs,            /* M3 in BGA292 package v1.20 - R7F702301B */
    #endif
    #if ( (RBFS_uC != RBFS_uC_RenesasD7) && (RBFS_uC != RBFS_uC_RenesasM6) )
      RBSYS_CPU_REL_M6_BGA292_V100_IDs,            /* M6 in BGA292 package v1.00 - R7F702300  */
      RBSYS_CPU_REL_M6_BGA292_V110_IDs,            /* M6 in BGA516 package v1.10 - R7F702300A */
      RBSYS_CPU_REL_M6_BGA292_V120_IDs,            /* M6 in BGA516 package v1.20 - R7F702300B */
    #endif
  
  #endif
};

/**
 * \Reference
 *  RBSYS_UnsupportedHW, Gen_SWCS_HSW_uC_Base_SYS-246
 *
 * \Purpose
 *  SW build executed on supported HW
 *
 * \Sequence
 *  For all device the SW build supports:
 *    Configure valid product name 2
 *    Configure valid product name 3
 *    Configure valid product version (P1x) or PRDNUM (U2A)
 *    Call process RBSYS_PRC_UnsupportedHW
 *
 * \ExpectedResult
 *  Good check report with following debug data
 *  for P1x:
 *    Bit[31..20] corresponds to Bits [11..0] of PRDNAME3 Register; via PRDNAME3 it's possible to identify the used device.
 *    Bit[19..8]  product version
 *    Bit[7..4]   SW build's RBFS_TargetDevice
 *    Bit[3..0]   SW build's RBFS_EmulationDevice
 *  for U2A:
 *    Bit[31..12] corresponds to Bits [19..0] of PRDNUM Register; via PRDNUM it's possible to identify the used device
 *    Bit[11..8]  unused
 *    Bit[7..4]   SW build's RBFS_TargetDevice
 *    Bit[3..0]   SW build's RBFS_EmulationDevice
 */
SWTEST void TRBSYS_UnsupportedHW_NoError(void)
{
  int i;
  for(i=0; i < (sizeof(supportedProductIDs)/sizeof(supportedProductIDs[0])); i++)
  {
    #if ( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
          || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      RBSYS_uC_PRDNAME2 = supportedProductIDs[i].prdname2;
      RBSYS_uC_PRDNAME3 = supportedProductIDs[i].prdname3;
    #endif
    #if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      PRDSEL3 = supportedProductIDs[i].version << 16u;
    #elif (( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      RBSYS_uC_PRDNUM = supportedProductIDs[i].version;
    #endif
    #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      SIUL2_0.MIDR1 = supportedProductIDs[i].midr1;
      SIUL2_0.MIDR2 = supportedProductIDs[i].midr2;
    #endif

    RBSYS_PRC_UnsupportedHW();

    SWT_EvalEq(stubConfId, RBRCFG_ConfId_UnsupportedCPU);
    SWT_EvalEq(stubIsUnsupportedCPU, FALSE);
    #if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      SWT_EvalEqX(stubDebug,    ((supportedProductIDs[i].prdname3 & 0xFFF) << 20)
                              | ((supportedProductIDs[i].version) << 8)
                              | ((RBFS_TargetDevice & 0xF) << 4)
                              | (RBFS_EmulationDevice & 0xF)
                              );
    #elif (( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      SWT_EvalEqX(stubDebug,    ((supportedProductIDs[i].version & 0xFFFFF) << 12)
                              | ((RBFS_TargetDevice & 0xF) << 4)
                              | (RBFS_EmulationDevice & 0xF)
                              );
    #elif ( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      SWT_EvalEqX(stubDebug,    ((supportedProductIDs[i].midr1 & 0x0FFF0000u) << 4)
                              | ((supportedProductIDs[i].midr1 & 0x00007800u) << 5)
                              | ((supportedProductIDs[i].midr1 & 0x000000FFu) << 8)
                              | ((RBFS_TargetDevice & 0xF) << 4)
                              | (RBFS_EmulationDevice & 0xF)
                              );
    #endif
  }
}


#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  #define TRBSYS_ProductID_SIZE 12
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #define TRBSYS_ProductID_SIZE 8
#endif
typedef union
{
  RBSYS_ProductID_t prodID;
  uint32 items[sizeof(RBSYS_ProductID_t) / 4];
} TRBSYS_ProductID_t;

/* We want to change every input for the Unsupported HW monitoring (separately and combined => "bitfield '000','001'...'111' if number of inputs is 3) */

#define NUM_OF_INPUTS       (sizeof(RBSYS_ProductID_t)/4)
#define NUM_OF_COMBINATIONS (0x1u << NUM_OF_INPUTS)    /* 2 ^ NUM_OF_INPUTS */


/**
 * \Reference
 *  RBSYS_UnsupportedHW, Gen_SWCS_HSW_uC_Base_SYS-246
 *
 * \Purpose
 *  SW build must be executed on unsupported HW with invalid product name 2
 *
 * \Sequence
 *  For all device the SW build supports:
 *    Configure invalid product name 2
 *    Configure valid product name 3
 *    Configure valid product version (P1x) or PRDNUM (U2A)
 *    Call process RBSYS_PRC_UnsupportedHW
 *
 * \ExpectedResult
 *  Unsupported HW error with following debug data
 *  for P1x:
 *    Bit[31..20] corresponds to Bits [11..0] of PRDNAME3 Register; via PRDNAME3 it's possible to identify the used device.
 *    Bit[19..8]  product version
 *    Bit[7..4]   SW build's RBFS_TargetDevice
 *    Bit[3..0]   SW build's RBFS_EmulationDevice
 *  for U2A:
 *    Bit[31..12] corresponds to Bits [19..0] of PRDNUM Register; via PRDNUM it's possible to identify the used device
 *    Bit[11..8]  unused
 *    Bit[7..4]   SW build's RBFS_TargetDevice
 *    Bit[3..0]   SW build's RBFS_EmulationDevice
 */
SWTEST void TRBSYS_UnsupportedHW_Error(void)
{
  int i;
  for(i = 0; i < (sizeof(supportedProductIDs)/sizeof(supportedProductIDs[0])); i++)
  {
    int combination;
    for(combination = 1; combination < NUM_OF_COMBINATIONS; combination++) /* skip 0, to always modify */
    {
      int j;
      TRBSYS_ProductID_t param;

      param.prodID = supportedProductIDs[i];

      for(j = 0; j < NUM_OF_INPUTS; j++)
      {
        if((combination & (1u << j)) != 0u)
        {
          param.items[j] = 0x12345678u;
        }
      }
      #if ( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
      || (RBFS_uCFamily_RenesasU2C) )
        RBSYS_uC_PRDNAME2 = param.prodID.prdname2;
        RBSYS_uC_PRDNAME3 = param.prodID.prdname3;
      #endif
      #if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
        PRDSEL3 = param.prodID.version << 16u;
      #elif (( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
        RBSYS_uC_PRDNUM = param.prodID.version;
      #endif
      #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        SIUL2_0.MIDR1 = param.prodID.midr1;
        SIUL2_0.MIDR2 = param.prodID.midr2;
      #endif

      RBSYS_PRC_UnsupportedHW();

      SWT_EvalEq(stubConfId, RBRCFG_ConfId_UnsupportedCPU);
      SWT_EvalEq(stubIsUnsupportedCPU, TRUE);
      #if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
        SWT_EvalEqX(stubDebug,    ((param.prodID.prdname3 & 0xFFF) << 20)
                                | ((param.prodID.version & 0xFFF)  << 8)
                                | ((RBFS_TargetDevice & 0xF) << 4)
                                | (RBFS_EmulationDevice & 0xF)
                                );
      #elif (( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        SWT_EvalEqX(stubDebug,    ((param.prodID.version & 0xFFFFF) << 12)
                                | ((RBFS_TargetDevice & 0xF) << 4)
                                | (RBFS_EmulationDevice & 0xF)
                                );
      #elif ( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        SWT_EvalEqX(stubDebug,    ((param.prodID.midr1 & 0x0FFF0000u) << 4)
                                | ((param.prodID.midr1 & 0x00007800u) << 5)
                                | ((param.prodID.midr1 & 0x000000FFu) << 8)
                                | ((RBFS_TargetDevice & 0xF) << 4)
                                | (RBFS_EmulationDevice & 0xF)
                                );
      #endif
    }
  }
}


/**
 * \Reference
 *  RBSYS_UnsupportedHW, Gen_SWCS_HSW_uC_Base_SYS-246, Gen_SWCS_HSW_uC_Base_SYS-249
 *
 * \Purpose
 *  SW build executed on explicitly not supported HW
 *
 * \Sequence
 *  For all device the SW build does explicitly not support:
 *    Configure valid product name 2
 *    Configure valid product name 3
 *    Configure valid product version (P1x) or PRDNUM (U2A)
 *    Call process RBSYS_PRC_UnsupportedHW
 *
 * \ExpectedResult
 *  Unsupported HW error with following debug data
 *  for P1x:
 *    Bit[31..20] corresponds to Bits [11..0] of PRDNAME3 Register; via PRDNAME3 it's possible to identify the used device.
 *    Bit[19..8]  product version
 *    Bit[7..4]   SW build's RBFS_TargetDevice
 *    Bit[3..0]   SW build's RBFS_EmulationDevice
 *  for U2A:
 *    Bit[31..12] corresponds to Bits [19..0] of PRDNUM Register; via PRDNUM it's possible to identify the used device
 *    Bit[11..8]  unused
 *    Bit[7..4]   SW build's RBFS_TargetDevice
 *    Bit[3..0]   SW build's RBFS_EmulationDevice
 */
SWTEST void TRBSYS_UnsupportedHW_UnsupportedDevice_Error(void)
{
  int i;
  for(i = 0; i < (sizeof(unsupportedProductIDs)/sizeof(unsupportedProductIDs[0])); i++)
  {
    int combination;
    for(combination = 1; combination < NUM_OF_COMBINATIONS; combination++)
    {
      int j;
      TRBSYS_ProductID_t param;
      param.prodID = supportedProductIDs[i];
      for(j = 0; j < NUM_OF_INPUTS; j++)
      {
        if((combination & (1u << j)) != 0u)
        {
          param.items[j] = 0x12345678u;
        }
      }

      #if ( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
            || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
        RBSYS_uC_PRDNAME2 = param.prodID.prdname2;
        RBSYS_uC_PRDNAME3 = param.prodID.prdname3;
      #endif
      #if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
        PRDSEL3 = param.prodID.version << 16u;
      #elif ( ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
        RBSYS_uC_PRDNUM = param.prodID.version;
      #endif
      #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        SIUL2_0.MIDR1 = param.prodID.midr1;
        SIUL2_0.MIDR2 = param.prodID.midr2;
      #endif

      RBSYS_PRC_UnsupportedHW();

      SWT_EvalEq(stubConfId, RBRCFG_ConfId_UnsupportedCPU);
      SWT_EvalEq(stubIsUnsupportedCPU, TRUE);
      #if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
        SWT_EvalEqX(stubDebug,    (param.prodID.prdname3 << 20)
                                | ((param.prodID.version & 0xFFF) << 8)
                                | ((RBFS_TargetDevice & 0xF) << 4)
                                | (RBFS_EmulationDevice & 0xF)
                                );
      #elif (( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        SWT_EvalEqX(stubDebug,    ((param.prodID.version & 0xFFFFF) << 12)
                                | ((RBFS_TargetDevice & 0xF) << 4)
                                | (RBFS_EmulationDevice & 0xF)
                                );
      #elif ( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        SWT_EvalEqX(stubDebug,    ((param.prodID.midr1 & 0x0FFF0000u) << 4)
                                | ((param.prodID.midr1 & 0x00007800u) << 5)
                                | ((param.prodID.midr1 & 0x000000FFu) << 8)
                                | ((RBFS_TargetDevice & 0xF) << 4)
                                | (RBFS_EmulationDevice & 0xF)
                                );
      #endif
    }
  }
  SWT_Eval(TRUE); // if list of unsupported devices is empty
}


#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
  static boolean trbsys_UnsupportedHW_IsWorkingSampleDetected(void)
  {
    return (stubConfId == RBRCFG_ConfId_UnsupportedCPU) && stubIsUnsupportedCPU;
  }
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  /**
   * \Reference
   *  TRBSYS_UnsupportedHW_WorkingSampleDetection, Gen_SWCS_HSW_uC_Base_SYS-246
   *
   * \Purpose
   *  SW build any SW run on unsupported Working Samples
   *
   * \Sequence
   *  Set CHIPID-registers to invalid values
   *  Run RBSYS_PRC_UnsupportedHW
   *  Check if the UnsupportedHW is reported to RCFG
   *
   * \ExpectedResult
   *  Unsupported HW error with following debug data:
   *
   *    Bit[31..20] corresponds to Bits [11..0] of PRDNAME3 Register; via PRDNAME3 it's possible to identify the used device
   *        D5EDv3 PRDNAME3: 0x20204235
   *    Bit[19..8]  product version 2.00;
   *    Bit[7..4] RBFS_TargetDevice_RenesasD4 or_RenesasD5 dependend on function switch setting
   *    Bit[3..0] RBFS_EmulationDevice_RenesasD5ED
   *
   *    Debug Data is check in other unittests, no need to check it again
   */
  SWTEST void TRBSYS_UnsupportedHW_WorkingSampleDetection(void)
  {
    CHIPID1LL = 0xFFFFFFFF;
    RBSYS_PRC_UnsupportedHW();
    SWT_Eval( trbsys_UnsupportedHW_IsWorkingSampleDetected() );

    CHIPID1LL = 0;
    CHIPID1LH = 0xFFFFFFFF;
    RBSYS_PRC_UnsupportedHW();
    SWT_Eval( trbsys_UnsupportedHW_IsWorkingSampleDetected() );

    CHIPID1LH = 0;
    CHIPID1HL = 0xFFFFFFFF;
    RBSYS_PRC_UnsupportedHW();
    SWT_Eval( trbsys_UnsupportedHW_IsWorkingSampleDetected() );

    CHIPID1HL = 0;
    CHIPID1HH = 0xFFFFFFFF;
    RBSYS_PRC_UnsupportedHW();
    SWT_Eval( trbsys_UnsupportedHW_IsWorkingSampleDetected() );
  }
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  /**
   * \Reference
   *  TRBSYS_UnsupportedHW_WorkingSampleDetection, Gen_SWCS_HSW_uC_Base_SYS-246
   *
   * \Purpose
   *  SW build any SW run on unsupported Working Samples
   *
   * \Sequence
   *  Set PRDNUM to unsupported working sample M6ED v1.0
   *  Check if the UnsupportedHW is reported to RCFG
   *
   * \ExpectedResult
   *  Unsupported HW error
   */
  SWTEST void TRBSYS_UnsupportedHW_WorkingSampleDetection(void)
  {
    RBSYS_uC_PRDNAME2 = 0x20202039;
    RBSYS_uC_PRDNAME3 = 0x315A3230;
    RBSYS_uC_PRDNUM = 0x000183FF; //BGA516
    RBSYS_PRC_UnsupportedHW();
    SWT_Eval( trbsys_UnsupportedHW_IsWorkingSampleDetected() );

    RBSYS_uC_PRDNAME2 = 0x20202039;
    RBSYS_uC_PRDNAME3 = 0x315A3230;
    RBSYS_uC_PRDNUM = 0x00018400; //BGA404
    RBSYS_PRC_UnsupportedHW();
    SWT_Eval( trbsys_UnsupportedHW_IsWorkingSampleDetected() );
  }
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  // todo: Apparently, there are no working samples (only WS+ rated devices) -> todo: check if this is true
#endif

#include "TRBSYS_UnsupportedHW_Adaptor.h"
#include "RBSYS_ClockSettings.h"

/**
 * \Reference
 *  TRBSYS_checkVariables4Measurement, Gen_SWCS_HSW_uC_Base_SYS-285
 *
 * \Purpose
 *  Call main() and see that the variable values for measurement are set correctly
 *
 * \Sequence
 *  - call main()
 *  - check that the register values are copied to the measurement variables correctly
 *
 * \ExpectedResult
 *  measurement variables contain expected content
 */
SWTEST void TRBSYS_checkVariables4Measurement(void)
{
    #if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      PRDNAME2 = 0x32333130u;
      PRDNAME3 = 0x20204135u;
      PRDSEL3  = (0x100 << 16);
    #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
      PRDINFFPRDNAME2 = 0x32333130u;
      PRDINFFPRDNAME3 = 0x20204135u;
      PRDINFFPRDNUM   = (0x1u << 16) | 0x8989u; //< PRDNUM will be copied to "PRDversion" as is (with version information + device identifier)
    #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
      PRDINFfPRDNAME2 = 0x335A3230u;
      PRDINFfPRDNAME3 = 0x20202032u;
      PRDINFfPRDNUM   = (0x1u << 16) | 0x85E4u; 
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      SIUL2_0.MIDR1 = 0x11111111u;
      SIUL2_0.MIDR1 = 0x22222222u;
    #endif


    RBSYS_PRC_UnsupportedHW();

    #if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      SWT_EvalEq(CallPrivate_RBSYS_getPRDNAME4MM6_PRDNAME2(), PRDNAME2);
      SWT_EvalEq(CallPrivate_RBSYS_getPRDNAME4MM6_PRDNAME3(), PRDNAME3);
      SWT_EvalEq(CallPrivate_RBSYS_getPRDNAME4MM6_PRDversion(), 0x100);
    #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )  
      SWT_EvalEq(CallPrivate_RBSYS_getPRDNAME4MM6_PRDNAME2(), PRDINFFPRDNAME2);
      SWT_EvalEq(CallPrivate_RBSYS_getPRDNAME4MM6_PRDNAME3(), PRDINFFPRDNAME3);
      SWT_EvalEq(CallPrivate_RBSYS_getPRDNAME4MM6_PRDversion(), 0x18989u);
    #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ) 
      SWT_EvalEq(CallPrivate_RBSYS_getPRDNAME4MM6_PRDNAME2(), PRDINFfPRDNAME2);
      SWT_EvalEq(CallPrivate_RBSYS_getPRDNAME4MM6_PRDNAME3(), PRDINFfPRDNAME3);
      SWT_EvalEq(CallPrivate_RBSYS_getPRDNAME4MM6_PRDversion(), 0x185E4u);
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      SWT_EvalEq(CallPrivate_RBSYS_getPRDNAME4MM6_MIDR1(), SIUL2_0.MIDR1);
      SWT_EvalEq(CallPrivate_RBSYS_getPRDNAME4MM6_MIDR2(), SIUL2_0.MIDR2);
    #endif
    SWT_EvalEq(CallPrivate_RBSYS_getPRDNAME4MM6_CPUclock(), RBSYS_CPU_CLK_KHZ);
}
