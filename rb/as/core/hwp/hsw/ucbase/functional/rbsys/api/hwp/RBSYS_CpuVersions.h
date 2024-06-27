#ifndef RBSYS_CPUVERSIONS_H__
#define RBSYS_CPUVERSIONS_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Check for unsupported HW
 *
 * This interface provides for the device and SW compatibility check the corresponding
 * version IDs.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_uCRegisters.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_CpuClockRestriction,
                          RBFS_CpuClockRestriction_Default,
                          RBFS_CpuClockRestriction_OFF);



#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  /**
   * @brief Get the product version of the uC
   *
   * The function reads from register PRDSEL3 located at address 0xFFCD00C8 bit 16 to 27.
   * These number reflects the version coded via 3 hex nibbles:
   *   Bit 24 to 27: Main version number
   *   Bit 16 to 23: Sub version number
   *
   *        e.g 0x100
   *              |||______
   *              ||______ |
   *              |____   ||
   *                   |  ||
   *                   1. 00
   */
  #define RBSYS_CPU_PRODUCT_VERSION         ( (PRDSEL3 & 0x0FFF0000u) >>16)

  /** Forwarded for P1x/U2A consistency */
  #define RBSYS_uC_PRDNAME2 PRDNAME2
  #define RBSYS_uC_PRDNAME3 PRDNAME3


  /** Commonly used expressions for below defines */
  #define RBSYS_CPU_ID_STRUCT(ucName)       {RBSYS_PRDNAME2_##ucName, RBSYS_PRDNAME3_##ucName, RBSYS_VERSION_##ucName}
  #define RBSYS_CPU_ID_CHECK(ucName)      ( (RBSYS_CPU_PRODUCT_VERSION == RBSYS_VERSION_##ucName) && \
                                            (RBSYS_uC_PRDNAME2 == RBSYS_PRDNAME2_##ucName) && \
                                            (RBSYS_uC_PRDNAME3 == RBSYS_PRDNAME3_##ucName) )


  /* Hint: PRDNAME1 and PRDNAME4 is identical for all RENESAS CC Cube devices - therefore ignored for verification */


  /** Product name for CC CUBE device Renesas D1 Rev0 with eVR (embedded voltage regulator)
   *  in LQFP80 package v1.00 - R7F701343 */
  #define RBSYS_PRDNAME2_D1_LQFP80_EVR_V100             (0x34333130u)
  #define RBSYS_PRDNAME3_D1_LQFP80_EVR_V100             (0x20202033u)
  #define RBSYS_VERSION_D1_LQFP80_EVR_V100              (0x100u)
  #define RBSYS_CPU_REL_D1_LQFP80_EVR_V100_IDs          RBSYS_CPU_ID_STRUCT(D1_LQFP80_EVR_V100)
  #define RBSYS_CPU_REL_D1_LQFP80_EVR_V100              RBSYS_CPU_ID_CHECK(D1_LQFP80_EVR_V100)

  /** Product name for CC CUBE device Renesas D1 Rev0 with eVR (embedded voltage regulator)
   *  in LQFP100 package v1.00 - R7F701341 */
  #define RBSYS_PRDNAME2_D1_LQFP100_EVR_V100            (0x34333130u)
  #define RBSYS_PRDNAME3_D1_LQFP100_EVR_V100            (0x20202031u)
  #define RBSYS_VERSION_D1_LQFP100_EVR_V100             (0x100u)
  #define RBSYS_CPU_REL_D1_LQFP100_EVR_V100_IDs         RBSYS_CPU_ID_STRUCT(D1_LQFP100_EVR_V100)
  #define RBSYS_CPU_REL_D1_LQFP100_EVR_V100             RBSYS_CPU_ID_CHECK(D1_LQFP100_EVR_V100)

  /** Product name for CC CUBE device Renesas D2 Rev0 with eVR and ICU-S (embedded voltage regulator)
   *  in LQFP144 package v1.00 - R7F701336. CAUTION: ICU-S is not supported by emulation devices therefore could not be used by us */
  #define RBSYS_PRDNAME2_D2_LQFP144_EVR_ICUS_V100       (0x33333130u)
  #define RBSYS_PRDNAME3_D2_LQFP144_EVR_ICUS_V100       (0x20202036u)
  #define RBSYS_VERSION_D2_LQFP144_EVR_ICUS_V100        (0x100u)
  #define RBSYS_CPU_REL_D2_LQFP144_EVR_ICUS_V100_IDs    RBSYS_CPU_ID_STRUCT(D2_LQFP144_EVR_ICUS_V100)
  #define RBSYS_CPU_REL_D2_LQFP144_EVR_ICUS_V100        RBSYS_CPU_ID_CHECK(D2_LQFP144_EVR_ICUS_V100)

  /** Product name for CC CUBE device Renesas D2 Rev0 with eVR (embedded voltage regulator)
   *  in LQFP144 package v1.00 - R7F701337 */
  #define RBSYS_PRDNAME2_D2_LQFP144_EVR_V100            (0x33333130u)
  #define RBSYS_PRDNAME3_D2_LQFP144_EVR_V100            (0x20202037u)
  #define RBSYS_VERSION_D2_LQFP144_EVR_V100             (0x100u)
  #define RBSYS_CPU_REL_D2_LQFP144_EVR_V100_IDs         RBSYS_CPU_ID_STRUCT(D2_LQFP144_EVR_V100)
  #define RBSYS_CPU_REL_D2_LQFP144_EVR_V100             RBSYS_CPU_ID_CHECK(D2_LQFP144_EVR_V100)

  /** Product name for CC CUBE device Renesas D2 Rev0 with eVR (embedded voltage regulator)
   *  in LQFP100 package v1.00 - R7F701339 */
  #define RBSYS_PRDNAME2_D2_LQFP100_EVR_V100            (0x33333130u)
  #define RBSYS_PRDNAME3_D2_LQFP100_EVR_V100            (0x20202039u)
  #define RBSYS_VERSION_D2_LQFP100_EVR_V100             (0x100u)
  #define RBSYS_CPU_REL_D2_LQFP100_EVR_V100_IDs         RBSYS_CPU_ID_STRUCT(D2_LQFP100_EVR_V100)
  #define RBSYS_CPU_REL_D2_LQFP100_EVR_V100             RBSYS_CPU_ID_CHECK(D2_LQFP100_EVR_V100)

  /** Product name for CC CUBE device Renesas D3 Rev0 with DPS (dual power supply)
   *  in LQFP144 package v1.00 - R7F701330 */
  #define RBSYS_PRDNAME2_D3_LQFP144_DPS_V100            (0x33333130u)
  #define RBSYS_PRDNAME3_D3_LQFP144_DPS_V100            (0x20202030u)
  #define RBSYS_VERSION_D3_LQFP144_DPS_V100             (0x100u)
  #define RBSYS_CPU_REL_D3_LQFP144_DPS_V100_IDs         RBSYS_CPU_ID_STRUCT(D3_LQFP144_DPS_V100)
  #define RBSYS_CPU_REL_D3_LQFP144_DPS_V100             RBSYS_CPU_ID_CHECK(D3_LQFP144_DPS_V100)

  /** Product name for CC CUBE device Renesas D3 Rev0 with DPS (dual power supply)
   *  in BGA292 package v1.00 - R7F701328 */
  #define RBSYS_PRDNAME2_D3_BGA292_DPS_V100             (0x32333130u)
  #define RBSYS_PRDNAME3_D3_BGA292_DPS_V100             (0x20202038u)
  #define RBSYS_VERSION_D3_BGA292_DPS_V100              (0x100u)
  #define RBSYS_CPU_REL_D3_BGA292_DPS_V100_IDs          RBSYS_CPU_ID_STRUCT(D3_BGA292_DPS_V100)
  #define RBSYS_CPU_REL_D3_BGA292_DPS_V100              RBSYS_CPU_ID_CHECK(D3_BGA292_DPS_V100)

  /** Product name for CC CUBE device Renesas D3 Rev0 with eVR (embedded voltage regulator)
   *  in LQFP144 package v1.00 - R7F701331 */
  #define RBSYS_PRDNAME2_D3_LQFP144_EVR_V100            (0x33333130u)
  #define RBSYS_PRDNAME3_D3_LQFP144_EVR_V100            (0x20202031u)
  #define RBSYS_VERSION_D3_LQFP144_EVR_V100             (0x100u)
  #define RBSYS_CPU_REL_D3_LQFP144_EVR_V100_IDs         RBSYS_CPU_ID_STRUCT(D3_LQFP144_EVR_V100)
  #define RBSYS_CPU_REL_D3_LQFP144_EVR_V100             RBSYS_CPU_ID_CHECK(D3_LQFP144_EVR_V100)

  /** Product name for CC CUBE device Renesas D3 Rev0 with eVR (embedded voltage regulator)
   *  in HQFP144 package v1.00 - R7F701333 */
  #define RBSYS_PRDNAME2_D3_HQFP144_EVR_V100            (0x33333130u)
  #define RBSYS_PRDNAME3_D3_HQFP144_EVR_V100            (0x20202033u)
  #define RBSYS_VERSION_D3_HQFP144_EVR_V100             (0x100u)
  #define RBSYS_CPU_REL_D3_HQFP144_EVR_V100_IDs         RBSYS_CPU_ID_STRUCT(D3_HQFP144_EVR_V100)
  #define RBSYS_CPU_REL_D3_HQFP144_EVR_V100             RBSYS_CPU_ID_CHECK(D3_HQFP144_EVR_V100)

  /** Product name for CC CUBE device Renesas D3 Rev0 with eVR (embedded voltage regulator)
   *  in BGA292 package v1.00 - R7F701329 */
  #define RBSYS_PRDNAME2_D3_BGA292_EVR_V100             (0x32333130u)
  #define RBSYS_PRDNAME3_D3_BGA292_EVR_V100             (0x20202039u)
  #define RBSYS_VERSION_D3_BGA292_EVR_V100              (0x100u)
  #define RBSYS_CPU_REL_D3_BGA292_EVR_V100_IDs          RBSYS_CPU_ID_STRUCT(D3_BGA292_EVR_V100)
  #define RBSYS_CPU_REL_D3_BGA292_EVR_V100              RBSYS_CPU_ID_CHECK(D3_BGA292_EVR_V100)

  /** Product name for CC CUBE device Renesas D3 RevA with DPS (dual power supply)
   *  in LQFP144 package v1.00 - R7F701330A */
  #define RBSYS_PRDNAME2_D3_REV_A_LQFP144_DPS_V100      (0x33333130u)
  #define RBSYS_PRDNAME3_D3_REV_A_LQFP144_DPS_V100      (0x20204130u)
  #define RBSYS_VERSION_D3_REV_A_LQFP144_DPS_V100       (0x100u)
  #define RBSYS_CPU_REL_D3_REV_A_LQFP144_DPS_V100_IDs   RBSYS_CPU_ID_STRUCT(D3_REV_A_LQFP144_DPS_V100)
  #define RBSYS_CPU_REL_D3_REV_A_LQFP144_DPS_V100       RBSYS_CPU_ID_CHECK(D3_REV_A_LQFP144_DPS_V100)

  /** Product name for CC CUBE device Renesas D3 RevA with DPS (dual power supply)
   *  in BGA156 package v1.00 - R7F701394A */
  #define RBSYS_PRDNAME2_D3_REV_A_BGA156_DPS_V100       (0x39333130u)
  #define RBSYS_PRDNAME3_D3_REV_A_BGA156_DPS_V100       (0x20204134u)
  #define RBSYS_VERSION_D3_REV_A_BGA156_DPS_V100        (0x100u)
  #define RBSYS_CPU_REL_D3_REV_A_BGA156_DPS_V100_IDs    RBSYS_CPU_ID_STRUCT(D3_REV_A_BGA156_DPS_V100)
  #define RBSYS_CPU_REL_D3_REV_A_BGA156_DPS_V100        RBSYS_CPU_ID_CHECK(D3_REV_A_BGA156_DPS_V100)

  /** Product name for CC CUBE device Renesas D3 RevA with DPS (dual power supply)
   *  in BGA292 package v1.00 - R7F701328A */
  #define RBSYS_PRDNAME2_D3_REV_A_BGA292_DPS_V100       (0x32333130u)
  #define RBSYS_PRDNAME3_D3_REV_A_BGA292_DPS_V100       (0x20204138u)
  #define RBSYS_VERSION_D3_REV_A_BGA292_DPS_V100        (0x100u)
  #define RBSYS_CPU_REL_D3_REV_A_BGA292_DPS_V100_IDs    RBSYS_CPU_ID_STRUCT(D3_REV_A_BGA292_DPS_V100)
  #define RBSYS_CPU_REL_D3_REV_A_BGA292_DPS_V100        RBSYS_CPU_ID_CHECK(D3_REV_A_BGA292_DPS_V100)

  /** Product name for CC CUBE device Renesas D3 RevA with eVR (embedded voltage regulator)
   *  in LQFP144 package v1.00 - R7F701331A */
  #define RBSYS_PRDNAME2_D3_REV_A_LQFP144_EVR_V100      (0x33333130u)
  #define RBSYS_PRDNAME3_D3_REV_A_LQFP144_EVR_V100      (0x20204131u)
  #define RBSYS_VERSION_D3_REV_A_LQFP144_EVR_V100       (0x100u)
  #define RBSYS_CPU_REL_D3_REV_A_LQFP144_EVR_V100_IDs   RBSYS_CPU_ID_STRUCT(D3_REV_A_LQFP144_EVR_V100)
  #define RBSYS_CPU_REL_D3_REV_A_LQFP144_EVR_V100       RBSYS_CPU_ID_CHECK(D3_REV_A_LQFP144_EVR_V100)

  /** Product name for CC CUBE device Renesas D3 RevA with eVR (embedded voltage regulator)
   *  in HQFP144 package v1.00 - R7F701333A */
  #define RBSYS_PRDNAME2_D3_REV_A_HQFP144_EVR_V100      (0x33333130u)
  #define RBSYS_PRDNAME3_D3_REV_A_HQFP144_EVR_V100      (0x20204133u)
  #define RBSYS_VERSION_D3_REV_A_HQFP144_EVR_V100       (0x100u)
  #define RBSYS_CPU_REL_D3_REV_A_HQFP144_EVR_V100_IDs   RBSYS_CPU_ID_STRUCT(D3_REV_A_HQFP144_EVR_V100)
  #define RBSYS_CPU_REL_D3_REV_A_HQFP144_EVR_V100       RBSYS_CPU_ID_CHECK(D3_REV_A_HQFP144_EVR_V100)

  /** Product name for CC CUBE device Renesas D3 RevA with eVR (embedded voltage regulator)
   *  in BGA292 package v1.00 - R7F701329A */
  #define RBSYS_PRDNAME2_D3_REV_A_BGA292_EVR_V100       (0x32333130u)
  #define RBSYS_PRDNAME3_D3_REV_A_BGA292_EVR_V100       (0x20204139u)
  #define RBSYS_VERSION_D3_REV_A_BGA292_EVR_V100        (0x100u)
  #define RBSYS_CPU_REL_D3_REV_A_BGA292_EVR_V100_IDs    RBSYS_CPU_ID_STRUCT(D3_REV_A_BGA292_EVR_V100)
  #define RBSYS_CPU_REL_D3_REV_A_BGA292_EVR_V100        RBSYS_CPU_ID_CHECK(D3_REV_A_BGA292_EVR_V100)

  /** Product name for CC CUBE device Renesas D4 RevA in BGA292 package v1.00 - R7F701327A */
  #define RBSYS_PRDNAME2_D4_REV_A_V100                  (0x32333130u)
  #define RBSYS_PRDNAME3_D4_REV_A_V100                  (0x20204137u)
  #define RBSYS_VERSION_D4_REV_A_V100                   (0x100u)
  #define RBSYS_CPU_REL_D4_REV_A_V100_IDs               RBSYS_CPU_ID_STRUCT(D4_REV_A_V100)
  #define RBSYS_CPU_REL_D4_REV_A_V100                   RBSYS_CPU_ID_CHECK(D4_REV_A_V100)

  /** Product name for CC CUBE device Renesas D5 Rev0 - v1.00 - R7F701326 */
  #define RBSYS_PRDNAME2_D5_REV_0_V100                  (0x32333130u)
  #define RBSYS_PRDNAME3_D5_REV_0_V100                  (0x20202036u)
  #define RBSYS_VERSION_D5_REV_0_V100                   (0x100u)
  #define RBSYS_CPU_REL_D5_REV_0_V100_IDs               RBSYS_CPU_ID_STRUCT(D5_REV_0_V100)
  #define RBSYS_CPU_REL_D5_REV_0_V100                   RBSYS_CPU_ID_CHECK(D5_REV_0_V100)

  /** Product name for CC CUBE device Renesas D3ED RevA v1.00 - R7F701334A */
  #define RBSYS_PRDNAME2_D3ED_V100                      (0x33333130u)
  #define RBSYS_PRDNAME3_D3ED_V100                      (0x20204134u)
  #define RBSYS_VERSION_D3ED_V100                       (0x100u)
  #define RBSYS_CPU_REL_D3ED_V100_IDs                   RBSYS_CPU_ID_STRUCT(D3ED_V100)
  #define RBSYS_CPU_REL_D3ED_V100                       RBSYS_CPU_ID_CHECK(D3ED_V100)

  /** Product name for CC CUBE device Renesas D3ED RevB v1.00 - R7F701334B */
  #define RBSYS_PRDNAME2_D3ED_REV_B_V100                (0x33333130u)
  #define RBSYS_PRDNAME3_D3ED_REV_B_V100                (0x20204234u)
  #define RBSYS_VERSION_D3ED_REV_B_V100                 (0x100u)
  #define RBSYS_CPU_REL_D3ED_REV_B_V100_IDs             RBSYS_CPU_ID_STRUCT(D3ED_REV_B_V100)
  #define RBSYS_CPU_REL_D3ED_REV_B_V100                 RBSYS_CPU_ID_CHECK(D3ED_REV_B_V100)

  /** Product name for CC CUBE device Renesas D5EDv2 v1.00 - R7F701325A */
  #define RBSYS_PRDNAME2_D5EDV2_V100                    (0x32333130u)
  #define RBSYS_PRDNAME3_D5EDV2_V100                    (0x20204135u)
  #define RBSYS_VERSION_D5EDV2_V100                     (0x100u)
  #define RBSYS_CPU_REL_D5EDV2_V100_IDs                 RBSYS_CPU_ID_STRUCT(D5EDV2_V100)
  #define RBSYS_CPU_REL_D5EDV2_V100                     RBSYS_CPU_ID_CHECK(D5EDV2_V100)

  /** Product name for CC CUBE device Renesas D5EDv3 v1.00 - R7F701325B */
  #define RBSYS_PRDNAME2_D5EDV3_V100                    (0x32333130u)
  #define RBSYS_PRDNAME3_D5EDV3_V100                    (0x20204235u)
  #define RBSYS_VERSION_D5EDV3_V100                     (0x100u)
  #define RBSYS_CPU_REL_D5EDV3_V100_IDs                 RBSYS_CPU_ID_STRUCT(D5EDV3_V100)
  #define RBSYS_CPU_REL_D5EDV3_V100                     RBSYS_CPU_ID_CHECK(D5EDV3_V100)



  /* collect supported product revisions from corresponding silicon */
  #define RBSYS_CPU_REL_D1_REV_0                    (RBSYS_CPU_REL_D1_LQFP80_EVR_V100 || RBSYS_CPU_REL_D1_LQFP100_EVR_V100)

  #define RBSYS_CPU_REL_D2_REV_0                    (RBSYS_CPU_REL_D2_LQFP144_EVR_V100 || RBSYS_CPU_REL_D2_LQFP100_EVR_V100)

  #define RBSYS_CPU_REL_D3_REV_0                    (RBSYS_CPU_REL_D3_LQFP144_DPS_V100 || RBSYS_CPU_REL_D3_BGA292_DPS_V100 \
                                                  || RBSYS_CPU_REL_D3_LQFP144_EVR_V100 || RBSYS_CPU_REL_D3_BGA292_EVR_V100 \
                                                  || RBSYS_CPU_REL_D3_HQFP144_EVR_V100)

  #define RBSYS_CPU_REL_D3_REV_A                    (RBSYS_CPU_REL_D3_REV_A_LQFP144_DPS_V100 || RBSYS_CPU_REL_D3_REV_A_BGA292_DPS_V100 \
                                                  || RBSYS_CPU_REL_D3_REV_A_LQFP144_EVR_V100 || RBSYS_CPU_REL_D3_REV_A_BGA292_EVR_V100 \
                                                  || RBSYS_CPU_REL_D3_REV_A_HQFP144_EVR_V100 || RBSYS_CPU_REL_D3_REV_A_BGA156_DPS_V100)

  #define RBSYS_CPU_REL_D1                          (RBSYS_CPU_REL_D1_REV_0)

  #define RBSYS_CPU_REL_D2                          (RBSYS_CPU_REL_D2_REV_0)

  #define RBSYS_CPU_REL_D3                          (RBSYS_CPU_REL_D3_REV_0 || RBSYS_CPU_REL_D3_REV_A)

  /* Renesas D3 devices which are limited to 160MHz */
  #if (RBFS_CpuClockRestriction == RBFS_CpuClockRestriction_Default)
    #define RBSYS_CPU_REL_D3_MAX_160MHZ               (RBSYS_CPU_REL_D3_LQFP144_EVR_V100 || RBSYS_CPU_REL_D3_REV_A_LQFP144_EVR_V100)
  #endif

  #define RBSYS_CPU_REL_D3ED                        (RBSYS_CPU_REL_D3ED_V100 || RBSYS_CPU_REL_D3ED_REV_B_V100)

  /* Attention: Renesas D4 device within BGA156 package is not supported (see also current limitation of guard configuration) */
  #define RBSYS_CPU_REL_D4                          (RBSYS_CPU_REL_D4_REV_A_V100)

  #define RBSYS_CPU_REL_D5                          (RBSYS_CPU_REL_D5_REV_0_V100)

  #define RBSYS_CPU_REL_D5EDV2                      (RBSYS_CPU_REL_D5EDV2_V100)
  #define RBSYS_CPU_REL_D5EDV3                      (RBSYS_CPU_REL_D5EDV3_V100)
  #define RBSYS_CPU_REL_D5ED                        (RBSYS_CPU_REL_D5EDV2 || RBSYS_CPU_REL_D5EDV3)

#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)

  /** Forwarded for P1x/U2A consistency */
  #define RBSYS_uC_PRDNAME2 PRDINFFPRDNAME2
  #define RBSYS_uC_PRDNAME3 PRDINFFPRDNAME3
  #define RBSYS_uC_PRDNUM   PRDINFFPRDNUM

  #define RBSYS_CPU_PRODUCT_VERSION              ( (RBSYS_uC_PRDNUM & 0x000F0000u) >>16 )


  /** Commonly used expressions for below defines */
  #define RBSYS_CPU_ID_STRUCT(ucName)       {RBSYS_PRDNAME2_##ucName, RBSYS_PRDNAME3_##ucName, RBSYS_PRDNUM_##ucName}
  #define RBSYS_CPU_ID_CHECK(ucName)      ( (RBSYS_uC_PRDNAME2 == RBSYS_PRDNAME2_##ucName) && \
                                            (RBSYS_uC_PRDNAME3 == RBSYS_PRDNAME3_##ucName) && \
                                            (RBSYS_uC_PRDNUM   == RBSYS_PRDNUM_##ucName) )

  /** Product name for CC CUBE+ device Renesas M6ED in BGA516 package v1.10 - R7F702Z19 -> supported */
  #define RBSYS_PRDNAME2_M6ED_BGA516_V110           (0x315A3230u)
  #define RBSYS_PRDNAME3_M6ED_BGA516_V110           (0x20204139u)
  #define RBSYS_PRDNUM_M6ED_BGA516_V110             (0x0001840Bu)
  #define RBSYS_CPU_REL_M6ED_BGA516_V110_IDs        RBSYS_CPU_ID_STRUCT(M6ED_BGA516_V110)
  #define RBSYS_CPU_REL_M6ED_BGA516_V110            RBSYS_CPU_ID_CHECK(M6ED_BGA516_V110)

  /** Product name for CC CUBE+ device Renesas M6ED in BGA404 package v1.10 - R7F702Z19A -> supported */
  #define RBSYS_PRDNAME2_M6ED_BGA404_V110           (0x315A3230u)
  #define RBSYS_PRDNAME3_M6ED_BGA404_V110           (0x20204139u)
  #define RBSYS_PRDNUM_M6ED_BGA404_V110             (0x0001840Cu)
  #define RBSYS_CPU_REL_M6ED_BGA404_V110_IDs        RBSYS_CPU_ID_STRUCT(M6ED_BGA404_V110)
  #define RBSYS_CPU_REL_M6ED_BGA404_V110            RBSYS_CPU_ID_CHECK(M6ED_BGA404_V110)

  /** Add note: Trace Measurement is not supported because no bonds to ECU - same pinout as M6 BGA292 -> supported */
  /** Product name for CC CUBE+ device Renesas M6ED in BGA292 package v1.10 - R7F702Z19A */
  #define RBSYS_PRDNAME2_M6ED_BGA292_V110           (0x315A3230u)
  #define RBSYS_PRDNAME3_M6ED_BGA292_V110           (0x20204139u)
  #define RBSYS_PRDNUM_M6ED_BGA292_V110             (0x0001840Du)
  #define RBSYS_CPU_REL_M6ED_BGA292_V110_IDs        RBSYS_CPU_ID_STRUCT(M6ED_BGA292_V110)
  #define RBSYS_CPU_REL_M6ED_BGA292_V110            RBSYS_CPU_ID_CHECK(M6ED_BGA292_V110)

  /** Product name for CC CUBE+ device Renesas M6ED in BGA516 package v1.20 - R7F702Z19B -> supported */
  #define RBSYS_PRDNAME2_M6ED_BGA516_V120           (0x315A3230u)
  #define RBSYS_PRDNAME3_M6ED_BGA516_V120           (0x20204239u)
  #define RBSYS_PRDNUM_M6ED_BGA516_V120             (0x00018449u)
  #define RBSYS_CPU_REL_M6ED_BGA516_V120_IDs        RBSYS_CPU_ID_STRUCT(M6ED_BGA516_V120)
  #define RBSYS_CPU_REL_M6ED_BGA516_V120            RBSYS_CPU_ID_CHECK(M6ED_BGA516_V120)

  /** Product name for CC CUBE+ device Renesas M6ED in BGA404 package v1.20 - R7F702Z19B -> supported */
  #define RBSYS_PRDNAME2_M6ED_BGA404_V120           (0x315A3230u)
  #define RBSYS_PRDNAME3_M6ED_BGA404_V120           (0x20204239u)
  #define RBSYS_PRDNUM_M6ED_BGA404_V120             (0x0001844Au)
  #define RBSYS_CPU_REL_M6ED_BGA404_V120_IDs        RBSYS_CPU_ID_STRUCT(M6ED_BGA404_V120)
  #define RBSYS_CPU_REL_M6ED_BGA404_V120            RBSYS_CPU_ID_CHECK(M6ED_BGA404_V120)

  /** Product name for CC CUBE+ device Renesas M6 in BGA516 package v1.00 - R7F702300 -> not supported */
  #define RBSYS_PRDNAME2_M6_BGA516_V100             (0x30333230u)
  #define RBSYS_PRDNAME3_M6_BGA516_V100             (0x20202030u)
  #define RBSYS_PRDNUM_M6_BGA516_V100               (0x00018406u)
  #define RBSYS_CPU_REL_M6_BGA516_V100_IDs          RBSYS_CPU_ID_STRUCT(M6_BGA516_V100)
  #define RBSYS_CPU_REL_M6_BGA516_V100              RBSYS_CPU_ID_CHECK(M6_BGA516_V100)

  /** Product name for CC CUBE+ device Renesas M6 in BGA292 package v1.00 - R7F702300 -> supported */
  #define RBSYS_PRDNAME2_M6_BGA292_V100             (0x30333230u)
  #define RBSYS_PRDNAME3_M6_BGA292_V100             (0x20202030u)
  #define RBSYS_PRDNUM_M6_BGA292_V100               (0x00018407u)
  #define RBSYS_CPU_REL_M6_BGA292_V100_IDs          RBSYS_CPU_ID_STRUCT(M6_BGA292_V100)
  #define RBSYS_CPU_REL_M6_BGA292_V100              RBSYS_CPU_ID_CHECK(M6_BGA292_V100)

  /** Product name for CC CUBE+ device Renesas M6 in BGA516 package v1.10 - R7F702300A -> not supported */
  #define RBSYS_PRDNAME2_M6_BGA516_V110             (0x30333230u)
  #define RBSYS_PRDNAME3_M6_BGA516_V110             (0x20204130u)
  #define RBSYS_PRDNUM_M6_BGA516_V110               (0x0001844Bu)
  #define RBSYS_CPU_REL_M6_BGA516_V110_IDs          RBSYS_CPU_ID_STRUCT(M6_BGA516_V110)
  #define RBSYS_CPU_REL_M6_BGA516_V110              RBSYS_CPU_ID_CHECK(M6_BGA516_V110)

  /** Product name for CC CUBE+ device Renesas M6 in BGA373 package v1.10 - R7F702300A -> not supported */
  #define RBSYS_PRDNAME2_M6_BGA373_V110             (0x30333230u)
  #define RBSYS_PRDNAME3_M6_BGA373_V110             (0x20204130u)
  #define RBSYS_PRDNUM_M6_BGA373_V110               (0x0001844Cu)
  #define RBSYS_CPU_REL_M6_BGA373_V110_IDs          RBSYS_CPU_ID_STRUCT(M6_BGA373_V110)
  #define RBSYS_CPU_REL_M6_BGA373_V110              RBSYS_CPU_ID_CHECK(M6_BGA373_V110)

  /** Product name for CC CUBE+ device Renesas M6 in BGA292 package v1.10 - R7F702300A -> supported */
  #define RBSYS_PRDNAME2_M6_BGA292_V110             (0x30333230u)
  #define RBSYS_PRDNAME3_M6_BGA292_V110             (0x20204130u)
  #define RBSYS_PRDNUM_M6_BGA292_V110               (0x0001844Du)
  #define RBSYS_CPU_REL_M6_BGA292_V110_IDs          RBSYS_CPU_ID_STRUCT(M6_BGA292_V110)
  #define RBSYS_CPU_REL_M6_BGA292_V110              RBSYS_CPU_ID_CHECK(M6_BGA292_V110)

  /** Product name for CC CUBE+ device Renesas M6 in BGA516 package v1.20 - R7F702300B -> not supported */
  #define RBSYS_PRDNAME2_M6_BGA516_V120             (0x30333230u)
  #define RBSYS_PRDNAME3_M6_BGA516_V120             (0x20204230u)
  #define RBSYS_PRDNUM_M6_BGA516_V120               (0x0001847Du)
  #define RBSYS_CPU_REL_M6_BGA516_V120_IDs          RBSYS_CPU_ID_STRUCT(M6_BGA516_V120)
  #define RBSYS_CPU_REL_M6_BGA516_V120              RBSYS_CPU_ID_CHECK(M6_BGA516_V120)

  /** Product name for CC CUBE+ device Renesas M6 in BGA373 package v1.20 - R7F702300B -> not supported */
  #define RBSYS_PRDNAME2_M6_BGA373_V120             (0x30333230u)
  #define RBSYS_PRDNAME3_M6_BGA373_V120             (0x20204230u)
  #define RBSYS_PRDNUM_M6_BGA373_V120               (0x0001847Eu)
  #define RBSYS_CPU_REL_M6_BGA373_V120_IDs          RBSYS_CPU_ID_STRUCT(M6_BGA373_V120)
  #define RBSYS_CPU_REL_M6_BGA373_V120              RBSYS_CPU_ID_CHECK(M6_BGA373_V120)

  /** Product name for CC CUBE+ device Renesas M6 in BGA292 package v1.20 - R7F702300B -> supported */
  #define RBSYS_PRDNAME2_M6_BGA292_V120             (0x30333230u)
  #define RBSYS_PRDNAME3_M6_BGA292_V120             (0x20204230u)
  #define RBSYS_PRDNUM_M6_BGA292_V120               (0x0001847Fu)
  #define RBSYS_CPU_REL_M6_BGA292_V120_IDs          RBSYS_CPU_ID_STRUCT(M6_BGA292_V120)
  #define RBSYS_CPU_REL_M6_BGA292_V120              RBSYS_CPU_ID_CHECK(M6_BGA292_V120)

  /** Product name for CC CUBE+ device Renesas M2 in BGA292 package v1.00 - R7F702302 -> supported */
  #define RBSYS_PRDNAME2_M2_BGA292_V100             (0x30333230u)
  #define RBSYS_PRDNAME3_M2_BGA292_V100             (0x20202032u)
  #define RBSYS_PRDNUM_M2_BGA292_V100               (0x00018420u)
  #define RBSYS_CPU_REL_M2_BGA292_V100_IDs          RBSYS_CPU_ID_STRUCT(M2_BGA292_V100)
  #define RBSYS_CPU_REL_M2_BGA292_V100              RBSYS_CPU_ID_CHECK(M2_BGA292_V100)

  /** Product name for CC CUBE+ device Renesas M2 in QFP package v1.00 - R7F702302 -> supported */
  #define RBSYS_PRDNAME2_M2_QFP144_V100             (0x30333230u)
  #define RBSYS_PRDNAME3_M2_QFP144_V100             (0x20202032u)
  #define RBSYS_PRDNUM_M2_QFP144_V100               (0x00018424u)
  #define RBSYS_CPU_REL_M2_QFP144_V100_IDs          RBSYS_CPU_ID_STRUCT(M2_QFP144_V100)
  #define RBSYS_CPU_REL_M2_QFP144_V100              RBSYS_CPU_ID_CHECK(M2_QFP144_V100)

  /** Product name for CC CUBE+ device Renesas M3 in BGA292 package v1.00 - R7F702301 -> supported */
  #define RBSYS_PRDNAME2_M3_BGA292_V100             (0x30333230u)
  #define RBSYS_PRDNAME3_M3_BGA292_V100             (0x20202031u)
  #define RBSYS_PRDNUM_M3_BGA292_V100               (0x00018408u)
  #define RBSYS_CPU_REL_M3_BGA292_V100_IDs          RBSYS_CPU_ID_STRUCT(M3_BGA292_V100)
  #define RBSYS_CPU_REL_M3_BGA292_V100              RBSYS_CPU_ID_CHECK(M3_BGA292_V100)

  /** Product name for CC CUBE+ device Renesas M3 in BGA373 package v1.10 - R7F702301A -> not supported */
  #define RBSYS_PRDNAME2_M3_BGA373_V110             (0x30333230u)
  #define RBSYS_PRDNAME3_M3_BGA373_V110             (0x20204131u)
  #define RBSYS_PRDNUM_M3_BGA373_V110               (0x0001844Eu)
  #define RBSYS_CPU_REL_M3_BGA373_V110_IDs          RBSYS_CPU_ID_STRUCT(M3_BGA373_V110)
  #define RBSYS_CPU_REL_M3_BGA373_V110              RBSYS_CPU_ID_CHECK(M3_BGA373_V110)

  /** Product name for CC CUBE+ device Renesas M3 in BGA292 package v1.10 - R7F702301A -> supported */
  #define RBSYS_PRDNAME2_M3_BGA292_V110             (0x30333230u)
  #define RBSYS_PRDNAME3_M3_BGA292_V110             (0x20204131u)
  #define RBSYS_PRDNUM_M3_BGA292_V110               (0x0001844Fu)
  #define RBSYS_CPU_REL_M3_BGA292_V110_IDs          RBSYS_CPU_ID_STRUCT(M3_BGA292_V110)
  #define RBSYS_CPU_REL_M3_BGA292_V110              RBSYS_CPU_ID_CHECK(M3_BGA292_V110)

  /** Product name for CC CUBE+ device Renesas M3 in BGA373 package v1.20 - R7F702301B -> not supported */
  #define RBSYS_PRDNAME2_M3_BGA373_V120             (0x30333230u)
  #define RBSYS_PRDNAME3_M3_BGA373_V120             (0x20204231u)
  #define RBSYS_PRDNUM_M3_BGA373_V120               (0x00018480u)
  #define RBSYS_CPU_REL_M3_BGA373_V120_IDs          RBSYS_CPU_ID_STRUCT(M3_BGA373_V120)
  #define RBSYS_CPU_REL_M3_BGA373_V120              RBSYS_CPU_ID_CHECK(M3_BGA373_V120)

  /** Product name for CC CUBE+ device Renesas M3 in BGA292 package v1.20 - R7F702301B -> supported */
  #define RBSYS_PRDNAME2_M3_BGA292_V120             (0x30333230u)
  #define RBSYS_PRDNAME3_M3_BGA292_V120             (0x20204231u)
  #define RBSYS_PRDNUM_M3_BGA292_V120               (0x00018481u)
  #define RBSYS_CPU_REL_M3_BGA292_V120_IDs          RBSYS_CPU_ID_STRUCT(M3_BGA292_V120)
  #define RBSYS_CPU_REL_M3_BGA292_V120              RBSYS_CPU_ID_CHECK(M3_BGA292_V120)



  /** Product Version summary for M6ED V1.1 devices */
  #define RBSYS_CPU_REL_M6ED_V110                   ( RBSYS_CPU_REL_M6ED_BGA516_V110 \
                                                   || RBSYS_CPU_REL_M6ED_BGA404_V110 \
                                                   || RBSYS_CPU_REL_M6ED_BGA292_V110 )

  #define RBSYS_CPU_REL_M6ED_V120                   ( RBSYS_CPU_REL_M6ED_BGA516_V120 \
                                                   || RBSYS_CPU_REL_M6ED_BGA404_V120 )


  /** Product name for CC CUBE+ device Renesas M2 */
  #define RBSYS_CPU_REL_M2                          (RBSYS_CPU_REL_M2_BGA292_V100 || RBSYS_CPU_REL_M2_QFP144_V100)

  /** Product name for CC CUBE+ device Renesas M3 */
  #define RBSYS_CPU_REL_M3                          (RBSYS_CPU_REL_M3_BGA292_V100 || RBSYS_CPU_REL_M3_BGA292_V110 || RBSYS_CPU_REL_M3_BGA292_V120)

  /** Product name for CC CUBE+ device Renesas M6 */
  #define RBSYS_CPU_REL_M6                          (RBSYS_CPU_REL_M6_BGA292_V100 || RBSYS_CPU_REL_M6_BGA292_V110 || RBSYS_CPU_REL_M6_BGA292_V120)

  /** Product name for CC CUBE+ device Renesas M6ED */
  #define RBSYS_CPU_REL_M6ED                        ( RBSYS_CPU_REL_M6ED_V110 \
                                                   || RBSYS_CPU_REL_M6ED_V120 )


  /** for backwards compatibility to old D7 nomenclature */
  #define RBSYS_CPU_REL_D7ED_BGA516_V110  RBSYS_CPU_REL_M6ED_BGA516_V110
  #define RBSYS_CPU_REL_D7ED_BGA404_V110  RBSYS_CPU_REL_M6ED_BGA404_V110
  #define RBSYS_CPU_REL_D7ED_BGA292_V110  RBSYS_CPU_REL_M6ED_BGA292_V110
  #define RBSYS_CPU_REL_D7ED_BGA516_V120  RBSYS_CPU_REL_M6ED_BGA516_V120
  #define RBSYS_CPU_REL_D7ED_BGA404_V120  RBSYS_CPU_REL_M6ED_BGA404_V120
  #define RBSYS_CPU_REL_D7_BGA516_V100    RBSYS_CPU_REL_M6_BGA516_V100
  #define RBSYS_CPU_REL_D7_BGA292_V100    RBSYS_CPU_REL_M6_BGA292_V100
  #define RBSYS_CPU_REL_D7_BGA516_V110    RBSYS_CPU_REL_M6_BGA516_V110
  #define RBSYS_CPU_REL_D7_BGA404_V110    RBSYS_CPU_REL_M6_BGA373_V110 //< 404 is 373 in fact
  #define RBSYS_CPU_REL_D7_BGA292_V110    RBSYS_CPU_REL_M6_BGA292_V110
  #define RBSYS_CPU_REL_D7ED_V110         RBSYS_CPU_REL_M6ED_V110
  #define RBSYS_CPU_REL_D7ED_V120         RBSYS_CPU_REL_M6ED_V120
  #define RBSYS_CPU_REL_D7                RBSYS_CPU_REL_M6
  #define RBSYS_CPU_REL_D7ED              RBSYS_CPU_REL_M6ED

#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)

  /** Forwarded for P1x/U2A/U2C consistency */
  #define RBSYS_uC_PRDNAME2 PRDINFfPRDNAME2
  #define RBSYS_uC_PRDNAME3 PRDINFfPRDNAME3
  #define RBSYS_uC_PRDNUM   PRDINFfPRDNUM

  #define RBSYS_CPU_PRODUCT_VERSION              ( (RBSYS_uC_PRDNUM & 0x000F0000u) >>16 )

  /** Commonly used expressions for below defines */
  #define RBSYS_CPU_ID_STRUCT(ucName)       {RBSYS_PRDNAME2_##ucName, RBSYS_PRDNAME3_##ucName, RBSYS_PRDNUM_##ucName}
  #define RBSYS_CPU_ID_CHECK(ucName)      ( (RBSYS_uC_PRDNAME2 == RBSYS_PRDNAME2_##ucName) && \
                                            (RBSYS_uC_PRDNAME3 == RBSYS_PRDNAME3_##ucName) && \
                                            (RBSYS_uC_PRDNUM   == RBSYS_PRDNUM_##ucName) )

  /** Product name for Renesas U2C device K3ED in BGA404 package and DPS v100  - R7F702Z32FDBF-C -> supported */
  #define RBSYS_PRDNAME2_K3ED_BGA404_DPS_V100             (0x335A3230u)
  #define RBSYS_PRDNAME3_K3ED_BGA404_DPS_V100             (0x20202032u)
  #define RBSYS_PRDNUM_K3ED_BGA404_DPS_V100               (0x000185E4u)
  #define RBSYS_CPU_REL_K3ED_BGA404_DPS_V100_IDs          RBSYS_CPU_ID_STRUCT(K3ED_BGA404_DPS_V100)
  #define RBSYS_CPU_REL_K3ED_BGA404_DPS_V100              RBSYS_CPU_ID_CHECK(K3ED_BGA404_DPS_V100)

  /** Product name for Renesas U2C device K3 in BGA292 package and DPS v100 - R7F702600FABB-C -> not supported*/
  #define RBSYS_PRDNAME2_K3_BGA292_DPS_V100               (0x30363230u)
  #define RBSYS_PRDNAME3_K3_BGA292_DPS_V100               (0x20202030u)
  #define RBSYS_PRDNUM_K3_BGA292_DPS_V100                 (0x00018486u)
  #define RBSYS_CPU_REL_K3_BGA292_DPS_V100_IDs            RBSYS_CPU_ID_STRUCT(K3_BGA292_DPS_V100)
  #define RBSYS_CPU_REL_K3_BGA292_DPS_V100                RBSYS_CPU_ID_CHECK(K3_BGA292_DPS_V100)

  /** Product name for Renesas U2C device K1 in BGA292 package and DPS v100 - R7F702606FABB-C -> not supported*/
  #define RBSYS_PRDNAME2_K1_BGA292_DPS_V100               (0x30363230u)
  #define RBSYS_PRDNAME3_K1_BGA292_DPS_V100               (0x20202036u)
  #define RBSYS_PRDNUM_K1_BGA292_DPS_V100                 (0x00018661u)
  #define RBSYS_CPU_REL_K1_BGA292_DPS_V100_IDs            RBSYS_CPU_ID_STRUCT(K1_BGA292_DPS_V100)
  #define RBSYS_CPU_REL_K1_BGA292_DPS_V100                RBSYS_CPU_ID_CHECK(K1_BGA292_DPS_V100)

  /** Product name for Renesas U2C device K1 in BGA156 package and DPS v100 - R7F702606FABD-C -> not supported*/
  #define RBSYS_PRDNAME2_K1_BGA156_DPS_V100               (0x30363230u)
  #define RBSYS_PRDNAME3_K1_BGA156_DPS_V100               (0x20202036u)
  #define RBSYS_PRDNUM_K1_BGA156_DPS_V100                 (0x00018663u)
  #define RBSYS_CPU_REL_K1_BGA156_DPS_V100_IDs            RBSYS_CPU_ID_STRUCT(K1_BGA156_DPS_V100)
  #define RBSYS_CPU_REL_K1_BGA156_DPS_V100                RBSYS_CPU_ID_CHECK(K1_BGA156_DPS_V100)

  /** Product name for Renesas U2C device K1 in QFP144 package and DPS v100 - R7F702606FAFM-C -> not supported*/
  #define RBSYS_PRDNAME2_K1_QFP144_DPS_V100               (0x30363230u)
  #define RBSYS_PRDNAME3_K1_QFP144_DPS_V100               (0x20202036u)
  #define RBSYS_PRDNUM_K1_QFP144_DPS_V100                 (0x00018666u)
  #define RBSYS_CPU_REL_K1_QFP144_DPS_V100_IDs            RBSYS_CPU_ID_STRUCT(K1_QFP144_DPS_V100)
  #define RBSYS_CPU_REL_K1_QFP144_DPS_V100                RBSYS_CPU_ID_CHECK(K1_QFP144_DPS_V100)

  /** Product name for Renesas U2C device K1 in BGA292 package and eVR v100 - R7F702613FABB-C -> supported */
  #define RBSYS_PRDNAME2_K1_BGA292_EVR_V100               (0x31363230u)
  #define RBSYS_PRDNAME3_K1_BGA292_EVR_V100               (0x20202033u)
  #define RBSYS_PRDNUM_K1_BGA292_EVR_V100                 (0x0001866Fu)
  #define RBSYS_CPU_REL_K1_BGA292_EVR_V100_IDs            RBSYS_CPU_ID_STRUCT(K1_BGA292_EVR_V100)
  #define RBSYS_CPU_REL_K1_BGA292_EVR_V100                RBSYS_CPU_ID_CHECK(K1_BGA292_EVR_V100)

  /** Product name for Renesas U2C device K1 in BGA156 package and eVR v100 - R7F702613FABD-C -> not supported*/
  #define RBSYS_PRDNAME2_K1_BGA156_EVR_V100               (0x31363230u)
  #define RBSYS_PRDNAME3_K1_BGA156_EVR_V100               (0x20202033u)
  #define RBSYS_PRDNUM_K1_BGA156_EVR_V100                 (0x00018671u)
  #define RBSYS_CPU_REL_K1_BGA156_EVR_V100_IDs            RBSYS_CPU_ID_STRUCT(K1_BGA156_EVR_V100)
  #define RBSYS_CPU_REL_K1_BGA156_EVR_V100                RBSYS_CPU_ID_CHECK(K1_BGA156_EVR_V100)

  /** Product name for Renesas U2C device K1 in QFP144 package and eVR v100 - R7F702614FAFM-C -> supported */
  #define RBSYS_PRDNAME2_K1_QFP144_EVR_V100               (0x31363230u)
  #define RBSYS_PRDNAME3_K1_QFP144_EVR_V100               (0x20202034u)
  #define RBSYS_PRDNUM_K1_QFP144_EVR_V100                 (0x00018677u)
  #define RBSYS_CPU_REL_K1_QFP144_EVR_V100_IDs            RBSYS_CPU_ID_STRUCT(K1_QFP144_EVR_V100)
  #define RBSYS_CPU_REL_K1_QFP144_EVR_V100                RBSYS_CPU_ID_CHECK(K1_QFP144_EVR_V100)

  /** Product name for Renesas U2C device K0 in BGA156 package and eVR v100 - R7F702608FABD-C -> not supported*/
  #define RBSYS_PRDNAME2_K0_BGA156_EVR_V100               (0x30363230u)
  #define RBSYS_PRDNAME3_K0_BGA156_EVR_V100               (0x20202038u)
  #define RBSYS_PRDNUM_K0_BGA156_EVR_V100                 (0x00018669u)
  #define RBSYS_CPU_REL_K0_BGA156_EVR_V100_IDs            RBSYS_CPU_ID_STRUCT(K0_BGA156_EVR_V100)
  #define RBSYS_CPU_REL_K0_BGA156_EVR_V100                RBSYS_CPU_ID_CHECK(K0_BGA156_EVR_V100)

  /** Product name for Renesas U2C device K0 in QFP144 package and eVR v100 - R7F702615FAFM-C -> supported */
  #define RBSYS_PRDNAME2_K0_QFP144_EVR_V100               (0x31363230u)
  #define RBSYS_PRDNAME3_K0_QFP144_EVR_V100               (0x20202035u)
  #define RBSYS_PRDNUM_K0_QFP144_EVR_V100                 (0x00018678u)
  #define RBSYS_CPU_REL_K0_QFP144_EVR_V100_IDs            RBSYS_CPU_ID_STRUCT(K0_QFP144_EVR_V100)
  #define RBSYS_CPU_REL_K0_QFP144_EVR_V100                RBSYS_CPU_ID_CHECK(K0_QFP144_EVR_V100)


#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  /** Commonly used expressions for below defines */
  #define RBSYS_CPU_ID_STRUCT(ucName)       {RBSYS_CPU_MIDR1_##ucName, RBSYS_CPU_MIDR2_##ucName}
  #define RBSYS_CPU_ID_CHECK(ucName)      ( (SIUL2_0.MIDR1 == RBSYS_CPU_MIDR1_##ucName) && \
                                            (SIUL2_0.MIDR2 == RBSYS_CPU_MIDR2_##ucName) )


  /** From ST28 ADD Rev. 6.7 -> TN1342 Rev4 */
  /** Product name for STM Stellar device STM X7 in BGA292 package (version independent??) -> supported */
  #define RBSYS_CPU_MIDR1_X7_BGA292           (0x2A472000u)
  #define RBSYS_CPU_MIDR2_X7_BGA292           (0xD1005300u)
  #define RBSYS_CPU_STM_X7_BGA292_IDs         RBSYS_CPU_ID_STRUCT(X7_BGA516)
  #define RBSYS_CPU_STM_X7_BGA292             RBSYS_CPU_ID_CHECK(X7_BGA516)

  /** Product name for STM Stellar device STM X7 in BGA516 package (version independent??) -> supported */
  #define RBSYS_CPU_MIDR1_X7_BGA516           (0x2A477000u)
  #define RBSYS_CPU_MIDR2_X7_BGA516           (0xD1005300u)
  #define RBSYS_CPU_STM_X7_BGA516_IDs         RBSYS_CPU_ID_STRUCT(X7_BGA516)
  #define RBSYS_CPU_STM_X7_BGA516             RBSYS_CPU_ID_CHECK(X7_BGA516)

  /** Product name for STM Stellar device STM P7 in BGA292 package (version independent??) -> supported */
  #define RBSYS_CPU_MIDR1_P7_BGA292           (0x26472000u)
  #define RBSYS_CPU_MIDR2_P7_BGA292           (0xD1005000u)
  #define RBSYS_CPU_STM_P7_BGA292_IDs         RBSYS_CPU_ID_STRUCT(P7_BGA292)
  #define RBSYS_CPU_STM_P7_BGA292             RBSYS_CPU_ID_CHECK(P7_BGA292)

  /** From ST28 ADD Rev. 6.7 -> TN1385 Rev1 */
  /** Product name for STM Stellar device STM P6 in BGA292 package (version independent??) -> supported */
  #define RBSYS_CPU_MIDR1_P6_BGA292           (0x26462100u)
  #define RBSYS_CPU_MIDR2_P6_BGA292           (0xD0005000u)
  #define RBSYS_CPU_STM_P6_BGA292_IDs         RBSYS_CPU_ID_STRUCT(P6_BGA292)
  #define RBSYS_CPU_STM_P6_BGA292             RBSYS_CPU_ID_CHECK(P6_BGA292)


  /** Product name for Unicon device STM Stellar X7 (P7G7) */
  #define RBSYS_CPU_STM_X7                        (RBSYS_CPU_STM_X7_BGA516 || RBSYS_CPU_STM_X7_BGA292)
  /** Product name for Unicon device STM Stellar P7 */
  #define RBSYS_CPU_STM_P7                        (RBSYS_CPU_STM_P7_BGA292)
  /** Product name for Unicon device STM Stellar P6 */
  #define RBSYS_CPU_STM_P6                        (RBSYS_CPU_STM_P6_BGA292)

#else
  #error ("Definition of Unsupported uC HW is missing for this uCFamily")
#endif


/**
  * @brief Returns whether the device is an emulation device
  *
  * @return TRUE if the device is an emulation device, otherwise FALSE
  */
static inline boolean RBSYS_IsEmulationDevice(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    return (RBSYS_CPU_REL_D3ED || RBSYS_CPU_REL_D5ED);
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    return (RBSYS_CPU_REL_M6ED);
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
    return TRUE; //todo: fix
  #elif (RBFS_uCFamily == RBFS_uCFamily_STMStellar)
    return (RBSYS_CPU_STM_X7 || RBSYS_CPU_STM_P7);
  #endif
}

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
