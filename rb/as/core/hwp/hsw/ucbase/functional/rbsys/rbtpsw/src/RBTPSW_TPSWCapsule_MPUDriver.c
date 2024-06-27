/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Third party software capsule - Renesas P1x/U2A MPU driver
 *
 * This internal API provides MPU services for TPSW memory protection
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* realized interfaces */
#include "RBTPSW_TPSWCapsule_MPUDriver.h"


/* used interfaces */
#include "RBSYS_Intrinsics.h"
#include <assert.h>                           // for static_assert()
#include <stdalign.h>                         // for alignof
#include "RBTPSW_TPSWCapsule_Priv.h"
#include "RBSYS_CoreMpu.h"



/* Assert supported configurations: switches, parameters, constants, ... */

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTPSWSupport,
                          RBFS_SysTPSWSupport_YES,
                          RBFS_SysTPSWSupport_NO);

RB_ASSERT_SWITCH_SETTINGS(RBFS_FlashBank0Support,
                          RBFS_FlashBank0Support_OFF,
                          RBFS_FlashBank0Support_INACTIVE,
                          RBFS_FlashBank0Support_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_FlashBank1Support,
                          RBFS_FlashBank1Support_OFF,
                          RBFS_FlashBank1Support_INACTIVE,
                          RBFS_FlashBank1Support_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_FlashBank2Support,
                          RBFS_FlashBank2Support_OFF,
                          RBFS_FlashBank2Support_INACTIVE,
                          RBFS_FlashBank2Support_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_FlashBank3Support,
                          RBFS_FlashBank3Support_OFF,
                          RBFS_FlashBank3Support_INACTIVE,
                          RBFS_FlashBank3Support_ON);

#if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)

  // check compatibility for cast from MemoryStartAddressType to uint32 which is a typedef from rtaos
  static_assert(sizeof(MemoryStartAddressType) == sizeof(uint32), "Size of MemoryStartAddressType does not match that of uint32");
  static_assert(alignof(MemoryStartAddressType) == alignof(uint32), "Alignment of MemoryStartAddressType does not match that of uint32");

  /* ---------------------------------------------------------------------------- */

  void RBTPSW_ConfigMpu(const rbtpsw_fncall_context_t* tpsw_config, uint32 sp, uint32 sp_end, CoreIdType CoreId)
  {
    const rbtpsw_mpu_cfg_t *mpu_cfg;
    uint8 app_active;
    RBSYS_MpuRegion_t mpuCoreConfig;

    // set enable bit for mpu regions - if ei_fault is true, behavior should be the same as if application is NOT_ACTIVE
    app_active = ((tpsw_config->application->status == NOT_ACTIVE) || (tpsw_config->application->ei_fault == RBTPSW_TRUE)) ? RBTPSW_FALSE : RBTPSW_TRUE;

    // configure 1 stack region here
    {
      mpuCoreConfig.region   = RBSYS_MPU_REGION_STACK;
      mpuCoreConfig.start = sp_end;
      mpuCoreConfig.end   = sp;
      if(app_active != RBTPSW_FALSE)
      {
        mpuCoreConfig.attr = RBSYS_MPU_ATTR_DEFAULT | RBSYS_USERSTACK | RBSYS_MPU_ACCESS_E;
      }
      else
      {
        // RBSYS_BASICATTR_SV_* settings are only active in case of MPM.SVP=1
        mpuCoreConfig.attr = RBSYS_MPU_ATTR_DEFAULT | RBSYS_BASICATTR_SV_RW | RBSYS_MPU_ACCESS_E;
      }

      RBSYS_CoreMpu_SetRegion(&mpuCoreConfig);
    }

    // configure content of the mpu table
    {
      uint32 region;

      mpu_cfg = tpsw_config->application->mpu_conf;

      for(region=RBSYS_MPU_REGION_FIRSTDATA; region<=RBSYS_MPU_REGION_LASTDATA; region++)
      {
        mpuCoreConfig.region = region;
        if (mpu_cfg->Startadr != RBTPSW_MAXRAMADDRESS)
        {
          mpuCoreConfig.start = mpu_cfg->Startadr;
          mpuCoreConfig.end   = mpu_cfg->Endadr;
          if(app_active != RBTPSW_FALSE)
          {
            mpuCoreConfig.attr = RBSYS_MPU_ATTR_DEFAULT | RBSYS_USERDATA | RBSYS_MPU_ACCESS_E;
          }
          else
          {
            // RBSYS_BASICATTR_SV_* settings are only active in case of MPM.SVP=1
            mpuCoreConfig.attr = RBSYS_MPU_ATTR_DEFAULT | RBSYS_BASICATTR_SV_RW | RBSYS_MPU_ACCESS_E;
          }

          mpu_cfg++;
        }
        else
        {
          // selected mpu channel not used for this TPSW app
          mpuCoreConfig.start = (uint32)0;
          mpuCoreConfig.end   = (uint32)0;
          // RBSYS_BASICATTR_SV_* settings are only active in case of MPM.SVP=1, deactivate MPU region by not setting RBSYS_MPU_ACCESS_E
          mpuCoreConfig.attr = RBSYS_MPU_ATTR_DEFAULT | RBSYS_BASICATTR_SV_RW;
        }

        RBSYS_CoreMpu_SetRegion(&mpuCoreConfig);
      }
    }

    // No flash access anymore for tpsw in case killed (useful for cascading abort)
    // Only write the attribute. Start/End are set in init.
    {
      uint32 attr;

      if(app_active != RBTPSW_FALSE)
      {
        attr = RBSYS_MPU_ATTR_DEFAULT | RBSYS_USERFLASH | RBSYS_MPU_ACCESS_E;
      }
      else
      {
        attr = RBSYS_MPU_ATTR_DEFAULT | RBSYS_SVFLASH | RBSYS_MPU_ACCESS_E;
      }
      #if (RBFS_FlashBank0Support == RBFS_FlashBank0Support_ON)
        RBSYS_CoreMpu_SetRegionAttr(RBSYS_MPU_REGION_FLASH_0, attr);
      #endif
      #if (RBFS_FlashBank1Support == RBFS_FlashBank1Support_ON)
        RBSYS_CoreMpu_SetRegionAttr(RBSYS_MPU_REGION_FLASH_1, attr);
      #endif
      #if (RBFS_FlashBank2Support == RBFS_FlashBank2Support_ON)
        RBSYS_CoreMpu_SetRegionAttr(RBSYS_MPU_REGION_FLASH_2, attr);
      #endif
      #if (RBFS_FlashBank3Support == RBFS_FlashBank3Support_ON)
        RBSYS_CoreMpu_SetRegionAttr(RBSYS_MPU_REGION_FLASH_3, attr);
      #endif
    }
  }

#endif /* (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES) */

/** @} */
/* End ingroup RBTPSW */

