#ifndef RBTPSW_TPSWCAPSULE_EXCHANDLER_RENESASP1X_H__
#define RBTPSW_TPSWCAPSULE_EXCHANDLER_RENESASP1X_H__

/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Third party software capsule - exception handler for Renesas P1x
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
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWSVPRestrictions,
                          RBFS_TPSWSVPRestrictions_ON,
                          RBFS_TPSWSVPRestrictions_OFF);


#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)

/* MPU region attribute value for non-execution in case of FP exception */
#define RBTPSW_MPAT_NX_VALUE_FLASH           0x000000E8 /* UM: -, SV: RX, E, G bit set (SV settings are only active if MPM.SVP==1) */
static_assert((RBSYS_MPU_ATTR_DEFAULT | RBSYS_SVFLASH | RBSYS_MPU_ACCESS_E) ==  RBTPSW_MPAT_NX_VALUE_FLASH, "MPU attributes for non-execution in case of FP exception are wrong");

/* MPU region attribute value for non-access in case of FP exception */
#if (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON)
  #define RBTPSW_MPAT_NA_VALUE_DATA            0x000000D8 /* UM: -, SV: RW,  E, G bit set (SV settings are only active if MPM.SVP==1) */
#else
  #define RBTPSW_MPAT_NA_VALUE_DATA            0x000000F8 /* UM: -, SV: RWX,  E, G bit set (SV settings are only active if MPM.SVP==1) */
#endif
static_assert((RBSYS_MPU_ATTR_DEFAULT | RBSYS_SVDATA | RBSYS_MPU_ACCESS_E) == RBTPSW_MPAT_NA_VALUE_DATA, "MPU attributes for non-access in case of FP exception are wrong");

/* Calculate RegId and SelId of mpu registers */
#define RBTPSW_MPU_REGID(region_id)          ((((region_id) * 4u) % 32u) + 2u)
#define RBTPSW_MPU_SELID(region_id)          ((((region_id) * 4u) / 32u) + 6u)



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
 *
 * A Fatal Error has ocurred and the stack pointer might be corrupted. At this time, we cannot evaluate the root cause
 * of the FE Exception. To be absolutely sure to not cause further exceptions, the handler is implemented in asm. This
 * asm macro must not have any stack consumption.
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
 *
 * An FPP Exception has ocurred and the stack pointer might be corrupted. At this time, we cannot evaluate the root cause
 * of the FPP Exception. To be absolutely sure to not cause further exceptions, the handler is implemented in asm. This
 * asm macro must not have any stack consumption.
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

  tpsw_abort:                              -- forbid execution on all channels
    mov RBTPSW_MPAT_NX_VALUE_FLASH,r10     -- UM: -, SV: RX, channel active
                                           --       (SV settings are only active if MPM.SVP==1)
#if (RBFS_FlashBank0Support == RBFS_FlashBank0Support_ON)
    ldsr r10,RBTPSW_MPU_REGID(RBSYS_MPU_REGION_FLASH_0),RBTPSW_MPU_SELID(RBSYS_MPU_REGION_FLASH_0)    -- flash bank 0 (channel 1)
#endif
#if (RBFS_FlashBank1Support == RBFS_FlashBank1Support_ON)
    ldsr r10,RBTPSW_MPU_REGID(RBSYS_MPU_REGION_FLASH_1),RBTPSW_MPU_SELID(RBSYS_MPU_REGION_FLASH_1)    -- flash bank 1 (channel 2)
#endif
    mov RBTPSW_MPAT_NA_VALUE_DATA,r10      -- UM: -, SV: RW, channel active
                                           --       (SV settings are only active if MPM.SVP==1)
    ldsr r10,RBTPSW_MPU_REGID(RBSYS_MPU_REGION_DATA0),RBTPSW_MPU_SELID(RBSYS_MPU_REGION_DATA0)      -- MPU table entry 0 (channel 7)
    ldsr r10,RBTPSW_MPU_REGID(RBSYS_MPU_REGION_DATA1),RBTPSW_MPU_SELID(RBSYS_MPU_REGION_DATA1)      -- MPU table entry 1 (channel 8)
    ldsr r10,RBTPSW_MPU_REGID(RBSYS_MPU_REGION_DATA2),RBTPSW_MPU_SELID(RBSYS_MPU_REGION_DATA2)      -- MPU table entry 2 (channel 9)
    ldsr r10,RBTPSW_MPU_REGID(RBSYS_MPU_REGION_DATA3),RBTPSW_MPU_SELID(RBSYS_MPU_REGION_DATA3)      -- MPU table entry 3 (channel 10)
    syncp                                  -- see "RH850G3M User's Manual: Hardware" revision 1.30, p.255 "System Register Hazards"
    synci                                  -- see "RH850G3M User's Manual: Hardware" revision 1.30, p.255 "System Register Hazards"
    stsr EIWR,r10,0                        -- restore r10
    eiret                                  -- back to TPSW --> MPU exception will be generated as flash execution is forbidden.
                                           -- in the protectionhook(), the fpu registers are read
  end:
}


#endif /* (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) */


/** @} */
/* End ingroup RBTPSW */

#endif /* End of multiple include protection */
