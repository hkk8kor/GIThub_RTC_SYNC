/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Branch to application software
 *
 * This module must be part of the bootblock and contains the branch from bootblock
 * to application software.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_BBFSW_StartupServices.h"
#include "RBSYS_GHS_ProgramStartup.h"

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_STMStellar);

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #include "../../RBSYS_CoreInit.h"
#endif

/* realized interfaces */
#include "RBSYS_BBFSW_jump.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysBootblockBuild,
                          RBFS_SysBootblockBuild_Active,
                          RBFS_SysBootblockBuild_NotActive);

RB_ASSERT_SWITCH_SETTINGS(RBFS_BootblockSysStartupCode,
                          RBFS_BootblockSysStartupCode_ON,
                          RBFS_BootblockSysStartupCode_OFF);


#if ( (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active) \
   && (RBFS_BootblockSysStartupCode == RBFS_BootblockSysStartupCode_ON) )

  RB_ASSERT_SWITCH_SETTINGS(RBFS_pTSWSupport,
                            RBFS_pTSWSupport_ON,
                            RBFS_pTSWSupport_OFF);

  /* -------------------------------------------------------------------------- */
  /* QAC|DEV 0009: In-line assembly embedded in normal C code                   */
  /* -------------------------------------------------------------------------- */
  /* Msg 1006: In-line assembler construct is a language extension.             */
  /* -------------------------------------------------------------------------- */
  #ifdef __QAC__
    #pragma PRQA_MESSAGES_OFF 1006
  #endif


  /**
   * @brief Leave bootblock and jump to application software (FSW).
   *
   * @return void
   */
  RBSYS_ATTR_NO_PROLOGUE
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
    asm (" .globl _FSWStart");
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    asm (" .globl FSWStart");
  #endif
  static void RBSYS_BBJumpToFSW(void)
  {
    // assembler lang is used to assure a goto-statement here. Stack shall not be retained, return is not allowed.
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
      asm (" jr32 _FSWStart");
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      asm (" b FSWStart");
    #endif
  }


  #if (RBFS_pTSWSupport == RBFS_pTSWSupport_ON)
    /**
     * @brief Leave bootblock and jump to the test software for ECU plant (ePSW).
     *
     * @return void
     */
    RBSYS_ATTR_NO_PROLOGUE
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
      asm (" .globl _ePSWStart");
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      asm (" .globl ePSWStart");
    #endif
    static void RBSYS_BBJumpToEPSW(void)
    {
      #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
        asm (" jr32 _ePSWStart");
      #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        asm (" b ePSWStart");
      #endif
    }
    /**
     * @brief Leave bootblock and jump to the test software for HU plant (TCSW).
     *
     * @return void
     */
    RBSYS_ATTR_NO_PROLOGUE
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
      asm (" .globl _TCSWStart");
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      asm (" .globl TCSWStart");
    #endif
    static void RBSYS_BBJumpToTCSW(void)
    {
      #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
        asm (" jr32 _TCSWStart");
      #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        asm (" b TCSWStart");
      #endif
    }
  #endif


  #ifdef __QAC__
    #pragma PRQA_MESSAGES_ON 1006
  #endif


  /**
   * @brief Leave bootblock and jump to the application software.
   *
   * @note This function shall only be called by the bootblock!
   *
   * @return void
   */
  void RBSYS_BBJumpToApplication(void)
  {
    #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      /* Stellar: Startup has to be entered in Hypervisor Mode to be able to write EL2 registers */
      RBSYS_SwitchSVToHV();
    #endif

    #if (RBFS_pTSWSupport == RBFS_pTSWSupport_ON)
      // in case of a pTSW the default software is ePSW
      if (RBSYS_getTCSWStartupRequest() == RBSYS_RUN_TCSW)
      {
        RBSYS_BBJumpToTCSW();
      }
      else
      {
        RBSYS_BBJumpToEPSW();
      }
    #else
      {
        RBSYS_BBJumpToFSW();
      }
    #endif
  }


#endif


/** @} */
/* End ingroup RBSYS */
