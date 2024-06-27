#ifndef RBSYS_GUARDCONFIGCOMMON_H__
#define RBSYS_GUARDCONFIGCOMMON_H__

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

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  #include "RenesasP1x/RBSYS_GuardConfigInternalP1x.h"
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  #include "RenesasU2A/RBSYS_GuardConfigInternalU2A.h"
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  #include "RenesasU2C/RBSYS_GuardConfigInternalU2C.h"
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #include "STMStellar/RBSYS_GuardConfigInternalStellar.h"
#endif

/* used interfaces */
#include "RBSYS_uCRegisters.h"
#include "RBSYS_GuardMemoryMap.h"
#include "RBSYS_GuardConfig.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_CpuInfo.h"


/* Assert supported configurations: switches, parameters, constants, ... */

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysExclusiveSPID,
                          RBFS_SysExclusiveSPID_Used,
                          RBFS_SysExclusiveSPID_NotUsed);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                          RBFS_SysEnvironment_Target,
                          RBFS_SysEnvironment_Simulation);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RBSYSGlobalRAMGuardsBB,
                          RBFS_RBSYSGlobalRAMGuardsBB_ON,
                          RBFS_RBSYSGlobalRAMGuardsBB_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasP1xGRAM,
                          RBFS_RenesasP1xGRAM_ON,
                          RBFS_RenesasP1xGRAM_OFF);


#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
  /**
    * @brief Enhanced guard configuration
    *
    * PEGuards are already configured within BasicGuardInit
    *
    * This function will configure all PBUS Guards, HBus Guards, INTC Guards, IBus Guards, DMA Guard.
    *
    * Hint: This function shall be called by core 0.
    * Hint: This function can be used in Bootblock ( -> only to be used by RBBootblockHSW! )
    *       as well as in Application              ( -> only to be used by RBSYS internally! ).
    *
    * @param void
    *
    * @return void
    */
  extern void RBSYS_EnhancedGuardInit(void);
#endif


#if( (RBFS_SysExclusiveSPID == RBFS_SysExclusiveSPID_Used) && (RBFS_SysEnvironment == RBFS_SysEnvironment_Target) )
  // Implementation of RBSYS_TRAP_PERMISSION_ENTRY / _LEAVE will be provided uC-specifically
#else
  // Host Cores will always have SAFE SPID, therefore no further action is required (empty macros)
  #define RBSYS_TRAP_PERMISSION_ENTRY()
  #define RBSYS_TRAP_PERMISSION_LEAVE()
#endif


/**
* @brief Application and Bootblock PE related guard configuration
*
* Restrict access from unsafe bus masters to required slaves via guards.
* We don't rely on bootblock handling, therefore a complete re-configuration
* is done in application mode.
*
* Difference between BB and Application:
*    Guards must not be locked in Bootblock, to allow an update of the Application without updating the Bootblock SW!!
*
* Hint: This function has to be called on every core separately.
* Hint: This abstraction cannot be handled via inline functions because Stack is not yet set up (macro replacement results in ASM macros)!
*
* ToDo: Core SPID is being set without restricting access to SPIDCTL. Wrong setting of Core SPID will be seen anyways
*       but there may be a smart approach to even cover a manipulation of the Core SPID.
*
* @param void
*
* @return void
*/
#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

  #define RBSYS_BasicGuardInit() \
  {\
    RBSYS_SYNCM();\
    RBSYS_setCoreSPID2SafeSPID();\
    RBSYS_PBUSGuardInit_ForPEGuard();\
    RBSYS_PEGuardInit();\
    RBSYS_SYNCM();\
  }

#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  #define RBSYS_BasicGuardInit() \
  {\
    RBSYS_DSB();\
    RBSYS_LRAMGuardInit();\
    RBSYS_DSB();\
  }

#endif

#if( (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION) || (RBFS_RBSYSGlobalRAMGuardsBB == RBFS_RBSYSGlobalRAMGuardsBB_ON) )

  #if( (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) \
    || (RBFS_uCFamily == RBFS_uCFamily_STMStellar) )
    /**
      * @brief Global RAM (GRAM/CRAM) related guard configuration (for Bootblock AND Application)
      *
      * We don't rely on bootblock handling, therefore a complete re-configuration is done in Application (FSW).
      *
      * Hint: This function shall only be called on Core 0!
      *
      * @param void
      *
      * @return void
      */
    static inline void RBSYS_GRAMGuardInit(void)
    {
      RBSYS_PBUSGuardInit_ForGRAMGuard();      /* protect GRAM/CRAM Guards */
      RBSYS_GRAMGuardInit_Impl();              /* protect GRAM/CRAM */
    }
  #elif( (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_OFF) || (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) )
    /* provide interface to keep envelope implementation in startup */
    #define RBSYS_GRAMGuardInit()
  #endif

#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
