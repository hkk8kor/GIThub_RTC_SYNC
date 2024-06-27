#ifndef RBTPSW_TPSWCAPSULE_EXCHANDLER_RENESASU2A_H__
#define RBTPSW_TPSWCAPSULE_EXCHANDLER_RENESASU2A_H__

/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Third party software capsule - exception handler for Renesas U2A
 *
 * This module provides the exception handling for the TPSW framework
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* used interfaces */
#include "Os.h"
#include "../../src/RBSYS_ExceptionHandler.h"
#include <assert.h>                           // for static_assert()
#include "RBSYS_CoreMpu.h"


RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A);
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
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWSVPRestrictions,
                          RBFS_TPSWSVPRestrictions_ON,
                          RBFS_TPSWSVPRestrictions_OFF);

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)


/* MPU region attribute value for non-execution in case of FP exception */
#define RBTPSW_MPAT_NX_VALUE_FLASH           0x0000C0A8 /* UM: -, SV: RX, E, RG, WG bit set (SV settings are only active if MPM.SVP==1) */
static_assert((RBSYS_MPU_ATTR_DEFAULT | RBSYS_SVFLASH | RBSYS_MPU_ACCESS_E) == RBTPSW_MPAT_NX_VALUE_FLASH, "MPU attributes for non-execution in case of FP exception are wrong");
/* MPU region attribute value for non-access in case of FP exception */
#if (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON)
  #define RBTPSW_MPAT_NA_VALUE_DATA            0x0000C098 /* UM: -, SV: RW,  E, RG, WG bit set (SV settings are only active if MPM.SVP==1) */
#else
  #define RBTPSW_MPAT_NA_VALUE_DATA            0x0000C0B8 /* UM: -, SV: RWX,  E, RG, WG bit set (SV settings are only active if MPM.SVP==1) */
#endif
static_assert((RBSYS_MPU_ATTR_DEFAULT | RBSYS_SVDATA | RBSYS_MPU_ACCESS_E) == RBTPSW_MPAT_NA_VALUE_DATA, "MPU attributes for non-access in case of FP exception are wrong");


/* Sanity checks for TPSW exception handler */
static_assert(E_OS_PROTECTION_EXCEPTION == 18, "E_OS_PROTECTION_EXCEPTION is not equal to 18! Os error code must be updated in RBTPSW_FE_TPSWENTRY()!");
static_assert(RBSYS_MPU_NUMBER_DATAREGIONS == 4, "RBSYS_MPU_NUMBER_DATAREGIONS is not equal to 4! RBTPSW_EXCFPP_TPSWENTRY() must be adapted!");


// no extern from Os.h
extern void Os_abort(void);



/**********************************************************************
 * RBTPSW_FE_TPSWENTRY()
 * Must be called at the very beginning of the MAE and RIE exceptions.
 * If exception comes from user mode then go to Os_abort(),
 * else continue to RBSYS.
 * This asm macro cannot have any stack consumption as we don't
 * know if the sp is correct at this time.
 **********************************************************************/
static void RBTPSW_FE_TPSWENTRY(void);
asm void RBTPSW_FE_TPSWENTRY(void)
{
%lab end

    ldsr r10,FEWR,0    -- save r10 into FEWR
    stsr FEPSW,r10,0   -- store FEPSW into r10
    shr  31,r10        -- CY = 1 if UM (bit 30) is set
    stsr FEWR,r10,0    -- restore r10
    bnc  end           -- if (CY == 0) continue to sys
    mov  18,r29        -- error code for os is stored in r29. This must be reviewed after each Os update.
    jr   _Os_abort     -- else go to TPSW through Os_abort

  end:
}



/**********************************************************************
 * RBTPSW_EXCFPP_TPSWENTRY()
 * Must be called at the very beginning of the FPP exceptions.
 * If exception comes from user mode then forbid execution and return
 * from interrupt (mpu exc will be triggered), else continue to RBSYS.
 * This asm macro cannot have any stack consumption as we don't
 * know if the sp is correct at this time.
 **********************************************************************/
static void RBTPSW_EXCFPP_TPSWENTRY(void);
asm void RBTPSW_EXCFPP_TPSWENTRY(void)
{
%lab end %lab tpsw_abort

    ldsr r10,EIWR,0            -- save r10 into EIWR
    stsr EIPSW,r10,0           -- store EIPSW into r10
    shr  31,r10                -- CY = 1 if UM is set
    bc  tpsw_abort             -- EI in user mode --> forbid flash execution to get FE level exc
    stsr EIWR,r10,0            -- restore r10 for priv mode
    jr _RBSYS_EXCFPP_Handler   -- jump to the Os FPP CAT1 handler

  tpsw_abort:                              -- forbid execution on all MPU regions
#if (RBFS_FlashBank0Support == RBFS_FlashBank0Support_ON)
    mov RBSYS_MPU_REGION_FLASH_0, r10      -- region RBSYS_MPU_REGION_FLASH_0...
    ldsr r10,16,5                          -- ... into MPIDX
    mov RBTPSW_MPAT_NX_VALUE_FLASH,r10     -- NX MPU region attribute value into r10
    ldsr r10,22,5                          -- set MPU region attribute (MPAT)
#endif
#if (RBFS_FlashBank1Support == RBFS_FlashBank1Support_ON)
    mov RBSYS_MPU_REGION_FLASH_1, r10      -- region RBSYS_MPU_REGION_FLASH_1...
    ldsr r10,16,5                          -- ... into MPIDX
    mov RBTPSW_MPAT_NX_VALUE_FLASH,r10     -- NX MPU region attribute value into r10
    ldsr r10,22,5                          -- set MPU region attribute (MPAT)
#endif
#if (RBFS_FlashBank2Support == RBFS_FlashBank2Support_ON)
    mov RBSYS_MPU_REGION_FLASH_2, r10      -- region RBSYS_MPU_REGION_FLASH_2...
    ldsr r10,16,5                          -- ... into MPIDX
    mov RBTPSW_MPAT_NX_VALUE_FLASH,r10     -- NX MPU region attribute value into r10
    ldsr r10,22,5                          -- set MPU region attribute (MPAT)
#endif
#if (RBFS_FlashBank3Support == RBFS_FlashBank3Support_ON)
    mov RBSYS_MPU_REGION_FLASH_3, r10      -- region RBSYS_MPU_REGION_FLASH_3...
    ldsr r10,16,5                          -- ... into MPIDX
    mov RBTPSW_MPAT_NX_VALUE_FLASH,r10     -- NX MPU region attribute value into r10
    ldsr r10,22,5                          -- set MPU region attribute (MPAT)
#endif
    mov RBSYS_MPU_REGION_DATA0, r10        -- region RBSYS_MPU_REGION_DATA0...
    ldsr r10,16,5                          -- ... into MPIDX
    mov RBTPSW_MPAT_NA_VALUE_DATA,r10      -- non-access attribute value into r10
    ldsr r10,22,5                          -- set MPU region attribute (MPAT)
    mov RBSYS_MPU_REGION_DATA1, r10        -- region RBSYS_MPU_REGION_DATA1...
    ldsr r10,16,5                          -- ... into MPIDX
    mov RBTPSW_MPAT_NA_VALUE_DATA,r10      -- non-access attribute value into r10
    ldsr r10,22,5                          -- set MPU region attribute (MPAT)
    mov RBSYS_MPU_REGION_DATA2, r10        -- region RBSYS_MPU_REGION_DATA2...
    ldsr r10,16,5                          -- ... into MPIDX
    mov RBTPSW_MPAT_NA_VALUE_DATA,r10      -- non-access attribute value into r10
    ldsr r10,22,5                          -- set MPU region attribute (MPAT)
    mov RBSYS_MPU_REGION_DATA3, r10        -- region RBSYS_MPU_REGION_DATA3...
    ldsr r10,16,5                          -- ... into MPIDX
    mov RBTPSW_MPAT_NA_VALUE_DATA,r10      -- non-access attribute value into r10
    ldsr r10,22,5                          -- set MPU region attribute (MPAT)
    synci                                  -- see "RH850/U2A-EVA Group User’s Manual: Hardware" revision 1.10, "3.2.7.3 Hazard Management after System Register Update"
                                           -- synci not really required, eiret is sufficient -> nevertheless, execute synci consistently after updating MPU
    stsr EIWR,r10,0                        -- restore r10
    eiret                                  -- back to TPSW --> MPU exception will be generated as flash execution is forbidden.
                                           -- in the protectionhook(), the fpu registers are read
  end:
}

#endif /* (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) */

/** @} */
/* End ingroup RBTPSW */

#endif /* End of multiple include protection */
