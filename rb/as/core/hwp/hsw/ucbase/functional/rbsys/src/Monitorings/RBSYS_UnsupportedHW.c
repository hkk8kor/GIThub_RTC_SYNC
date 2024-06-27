/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Device and SW compatibility check
 *
 * This module checks whether the flashed SW is compatible to the real device or not.
 * In case of incompatibility an error will be reported.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_CpuVersions.h"
#include "RBRCFG_UnsupportedConfig.h"
#include "RBSYS_ClockSettings.h" //< for RBSYS_CPU_CLK_KHZ


/* realized interfaces */
#include "RBSYS_UnsupportedHW.h"
#include "RBSYS_Subsystem.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                          RBFS_TargetDevice_RenesasD1,
                          RBFS_TargetDevice_RenesasD2,
                          RBFS_TargetDevice_RenesasD3,
                          RBFS_TargetDevice_RenesasD4,
                          RBFS_TargetDevice_RenesasD5,
                          RBFS_TargetDevice_RenesasD7,
                          RBFS_TargetDevice_RenesasM2,
                          RBFS_TargetDevice_RenesasM3,
                          RBFS_TargetDevice_RenesasM6,
                          RBFS_TargetDevice_RenesasK0,
                          RBFS_TargetDevice_RenesasK1,
                          RBFS_TargetDevice_STMP6);

RB_ASSERT_SWITCH_SETTINGS(RBFS_EmulationDevice,
                          RBFS_EmulationDevice_None,
                          RBFS_EmulationDevice_RenesasD3ED,
                          RBFS_EmulationDevice_RenesasD5ED,
                          RBFS_EmulationDevice_RenesasD7ED,
                          RBFS_EmulationDevice_RenesasM6ED,
                          RBFS_EmulationDevice_RenesasK3ED,
                          RBFS_EmulationDevice_STMP7ED);

RB_ASSERT_SWITCH_SETTINGS(RBFS_CpuClock,
                          RBFS_CpuClock_80MHz,
                          RBFS_CpuClock_160MHz,
                          RBFS_CpuClock_240MHz,
                          RBFS_CpuClock_320MHz,
                          RBFS_CpuClock_400MHz);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_CpuClockRestriction,
                          RBFS_CpuClockRestriction_Default,
                          RBFS_CpuClockRestriction_OFF);

#if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) \
  || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2) \
  || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) \
  || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2) \
   )
  RB_ASSERT_SWITCH_SETTINGS(RBFS_uCPackage,
                            RBFS_uCPackage_BGA156,
                            RBFS_uCPackage_BGA292,
                            RBFS_uCPackage_QFP80,
                            RBFS_uCPackage_QFP100,
                            RBFS_uCPackage_QFP144);
#endif


// Usage of UnsupportedCPU ID has to be statically registered (globally, not inside a function)
RBRCFG_STATIC_REGISTER_CONF_ID(RBRCFG_ConfId_UnsupportedCPU);


/* ------------------------------------------------------------------------------------------------
   SW workaround for GHS compiler incident 65175:
   __attribute__((used)) will not work as expected on current available GHS compiler suite.
   Due to an internal compiler issue it's not possible to declare the measurement variable
   RBSYS_uCProductName4MM6 as static. The compiler will still remove the whole variable even with
   usage of the attribute used because there is no visible reference. This problem was fixed in the
   v2016.5 final release, but as long as we are using 2015.1. we've to keep the external visibility.

  static __attribute__((used)) RBSYS_ProductName4MM6_t RBSYS_uCProductName4MM6;
   --------------------------------------------------------------------------------------------- */
__attribute__((used)) RBSYS_ProductName4MM6_t RBSYS_uCProductName4MM6;
/* uC HW Device information */

/*[[MEASUREMENT_TYPEDEF*/
/*TYPE=RBSYS_ProductName4MM6_t*/
/*NAME=RBSYS_uCProductName4MM6*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/


static const RBSYS_ProductID_t RBSYS_SupportedProductIDs[] = {
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )

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
      || (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD5ED) \
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
  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

    #if(RBFS_EmulationDevice == RBFS_EmulationDevice_None)

      #if(RBFS_TargetDevice == RBFS_TargetDevice_RenesasK0)
        RBSYS_CPU_REL_K0_QFP144_EVR_V100_IDs,         /* K0 in QFP144 package v1.00 - R7F702615 */
      #elif(RBFS_TargetDevice == RBFS_TargetDevice_RenesasK1)
        RBSYS_CPU_REL_K1_BGA292_EVR_V100_IDs,         /* K1 in BGA292 package v1.00 - R7F702613 */
        RBSYS_CPU_REL_K1_QFP144_EVR_V100_IDs,         /* K1 in QFP144 package v1.00 - R7F702614 */
      #endif
    #endif

    RBSYS_CPU_REL_K3ED_BGA404_DPS_V100_IDs,           /* K3ED in BGA404 package v1.00 - R7F702Z32 */
  
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

    RBSYS_CPU_STM_X7_BGA516_IDs,                       /* X7 in BGA516 package */
    RBSYS_CPU_STM_X7_BGA292_IDs,                       /* X7 in BGA292 package */
    RBSYS_CPU_STM_P7_BGA292_IDs,                       /* P7 in BGA292 package */
    RBSYS_CPU_STM_P6_BGA292_IDs                        /* P6 in BGA292 package */

  #endif
};

static boolean rbsys_UnsupportedHW_VerifyActualDeviceID(const RBSYS_ProductID_t* expectedValue, const RBSYS_ProductID_t* actualValue)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    return  ((expectedValue->prdname2 == actualValue->prdname2)
          && (expectedValue->prdname3 == actualValue->prdname3)
          && (expectedValue->version  == actualValue->version ));
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    return  ((expectedValue->midr1    == actualValue->midr1)
          && (expectedValue->midr2    == actualValue->midr2));
  #endif
}


/**
 * @brief Check unsupported uC
 *
 * RBSYS_PRC_UnsupportedHW is checking whether the flashed software is compatible to the used uC.
 * In case of incompatibility an error (RB_UnsupportedHW) will be reported.
 *
 * Emulation Design: http://rb-cs-nat.bosch.com/natweb/?pid=527&nid=193&vid=4&sid=3&cid=-1
 *
 * @return void
 */
void RBSYS_PRC_UnsupportedHW(void)
{
  boolean unsupportedHW = TRUE;
  uint32 debugData = 0;
  uint32 i;
  RBSYS_ProductID_t actualProductID;

  #if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
    actualProductID.prdname2 = RBSYS_uC_PRDNAME2;
    actualProductID.prdname3 = RBSYS_uC_PRDNAME3;
    actualProductID.version  = RBSYS_CPU_PRODUCT_VERSION;
  #elif ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
    actualProductID.prdname2 = RBSYS_uC_PRDNAME2;
    actualProductID.prdname3 = RBSYS_uC_PRDNAME3;
    actualProductID.version  = RBSYS_uC_PRDNUM;
  #elif ( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    actualProductID.midr1 = SIUL2_0.MIDR1;
    actualProductID.midr2 = SIUL2_0.MIDR2;
  #endif

  /* Compare product info registers against list of devices this SW configuration is compatible with */
  for(i=0; i < (sizeof(RBSYS_SupportedProductIDs)/sizeof(RBSYS_SupportedProductIDs[0])); i++)
  {
    if( rbsys_UnsupportedHW_VerifyActualDeviceID(&RBSYS_SupportedProductIDs[i], &actualProductID) )
    {
      /* If a match is found this device is supported */
      unsupportedHW = FALSE;
      break;
    }
  }

    RBSYS_uCProductName4MM6.DeviceID   = actualProductID;
    RBSYS_uCProductName4MM6.l_CpuClock = RBSYS_CPU_CLK_KHZ;

    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      /** Developement Devices are not supported due to different (from the target device) thresholds and tolerances */
      /** For Development Devices (Working Samples) all of these registers are 0xFFFFFFFF                            */
      if (  (CHIPID1LL == 0xFFFFFFFFu)
          ||(CHIPID1LH == 0xFFFFFFFFu)
          ||(CHIPID1HL == 0xFFFFFFFFu)
          ||(CHIPID1HH == 0xFFFFFFFFu) )
      {
        unsupportedHW = true;
      }
    #else
      // There are no working samples aside of M6ED V1.0 which is already covered above
      // Todo: Clarify for Stellar
    #endif


    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      /** @Debuginfo{RB_UnsupportedHW}
      *  @ID{RBFS_uCFamily_RenesasP1x}
      *
      *  @FWC_Requirements{ Gen_SWCS_HSW_uC_Base_SYS-246 }
      *
      *  @Data_D0{ @Bit[31..0]  see RBRCFG;
      *          }
      *  @Data_D1{ @Bit[31..20] corresponds to Bits [11..0] of PRDNAME3 Register;
      *                         via PRDNAME3 it's possible to identify the used device (see RBSYS_CpuVersions.h)
      *             @Bit[19..8]  product version;
      *            @Bit[7..4] RBFS_TargetDevice (in software configured function switch);
      *            @Bit[3..0] RBFS_EmulationDevice (in software configured function switch);
      *          }
      */
      debugData =  ((actualProductID.prdname3 & 0xFFFu) << 20);
      debugData |= ((actualProductID.version) << 8);
    #elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
      /** @Debuginfo{RB_UnsupportedHW}
      *  @ID{RBFS_uCFamily_RenesasU2A}
      *
      *  @FWC_Requirements{ Gen_SWCS_HSW_uC_Base_SYS-246 }
      *
      *  @Data_D0{ @Bit[31..0]  see RBRCFG;
      *          }
      *  @Data_D1{ @Bit[31..12] corresponds to Bits [19..0] of PRDNUM Register;
      *                         via PRDNUM it's possible to identify the used device (see RBSYS_CpuVersions.h)
      *            @Bit[11..8] unused
      *            @Bit[7..4] RBFS_TargetDevice (in software configured function switch);
      *            @Bit[3..0] RBFS_EmulationDevice (in software configured function switch);
      *          }
      */
      debugData =  ((actualProductID.version & 0xFFFFFu)<<12);
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      /** @Debuginfo{RB_UnsupportedHW}
      *   @ID{RBFS_uCFamily_STMStellar}
      *
      *   @FWC_Requirements{ Gen_SWCS_HSW_uC_Base_SYS-246 }
      *
      *   @Data_D0{ @Bit[31..0]  see RBRCFG;
      *           }
      *   @Data_D1{ @Bit[31..20] corresponds to Bits [27..16] of SIUL2.MIDR1 Register (MCU part number)
      *             @Bit[19..16] corresponds to Bits [14..11] of SIUL2.MIDR1 Register (Package setting - last bit ignored)
      *             @Bit[15..8]  corresponds to Bits [7..0] of SIUL2.MIDR1 Register   (Revision number)
      *             @Bit[7..4]   RBFS_TargetDevice (in software configured function switch);
      *             @Bit[3..0]   RBFS_EmulationDevice (in software configured function switch);
      *           }
      */
      debugData =  ((actualProductID.midr1 & 0x0FFF0000u) << 4);
      debugData |= ((actualProductID.midr1 & 0x00007800u) << 5);
      debugData |= ((actualProductID.midr1 & 0x000000FFu) << 8);
    #endif
    debugData |= ((uint32) (RBFS_TargetDevice) << 4);
    debugData |= ((uint32) (RBFS_EmulationDevice) << 0);

  RBRCFG_ReportUnsupportedConfig(RBRCFG_ConfId_UnsupportedCPU, unsupportedHW, debugData);
}

/** @} */
/* End ingroup RBSYS */
