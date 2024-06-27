#ifndef RBSYS_UCMODULEMODECTRL_H__
#define RBSYS_UCMODULEMODECTRL_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief CC-CUBE peripheral startup handling
 *
 * On Renesas CC-CUBE devices some peripherals must be explicitly switched from standby mode to run mode during startup.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_TestInjection.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);


#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  typedef enum {
    RBSYS_ModeEntryModule_Peripheral,
    RBSYS_ModeEntryModule_Domain0,
    RBSYS_ModeEntryModule_Domain1,
    RBSYS_ModeEntryModule_Domain2
  } RBSYS_ModeEntryModule_t;

  #define MCTL_MODE_DRUN              ((uint32)(0x3u << 28))
  #define MCTL_MODE_RESET_DEST        ((uint32)(0xFu << 28))
  #define MCTL_MODE_RESET_FUNCTIONAL  ((uint32)(0x0u << 28))
  #define MCTL_KEY1 ((uint32)0x5AF0u)
  #define MCTL_KEY2 ((uint32)0xA50Fu)

  typedef enum
  {
    RBSYS_ResetMode_Destructive = 0,
    RBSYS_ResetMode_Functional
  } RBSYS_ResetMode_t;

  static inline void RBSYS_ModeEntry_Switch2ResetMode(RBSYS_ResetMode_t resetMode)
  {
    if( resetMode == RBSYS_ResetMode_Destructive )
    {
      MC_ME_PER.ModeReg.MCTL = (MCTL_MODE_RESET_DEST | MCTL_KEY1);
      MC_ME_PER.ModeReg.MCTL = (MCTL_MODE_RESET_DEST | MCTL_KEY2);
    }
    else
    {
      MC_ME_PER.ModeReg.MCTL = (MCTL_MODE_RESET_FUNCTIONAL | MCTL_KEY1);
      MC_ME_PER.ModeReg.MCTL = (MCTL_MODE_RESET_FUNCTIONAL | MCTL_KEY2);
    }
  }

  static inline void RBSYS_ModeEntry_UpdateMode(RBSYS_ModeEntryModule_t module )
  {

    // MC_xx_ME   - Mode Enable:  Functional and Destructive Resets and DRUN Mode are always enabled, write is ignored
    // MC_xx_MCTL - Mode Control: Trigger DRUN Mode
    // Hint: Possible mode transitions are: any -> DRUN or DRUN -> DRUN (change is not required to take over new settings)
    switch (module)
    {
      case RBSYS_ModeEntryModule_Peripheral:
        MC_ME_PER.ModeReg.ME = 0x0000801Du;
        MC_ME_PER.ModeReg.MCTL = (MCTL_MODE_DRUN | MCTL_KEY1);
        MC_ME_PER.ModeReg.MCTL = (MCTL_MODE_DRUN | MCTL_KEY2);
        break;
      case RBSYS_ModeEntryModule_Domain0:
        MC_ME_CL0.ModeReg.ME   = 0x0000801Du;
        MC_ME_CL0.ModeReg.MCTL = (MCTL_MODE_DRUN | MCTL_KEY1);
        MC_ME_CL0.ModeReg.MCTL = (MCTL_MODE_DRUN | MCTL_KEY2);
        break;
      case RBSYS_ModeEntryModule_Domain1:
        MC_ME_CL1.ModeReg.ME = 0x0000801Du;
        MC_ME_CL1.ModeReg.MCTL = (MCTL_MODE_DRUN | MCTL_KEY1);
        MC_ME_CL1.ModeReg.MCTL = (MCTL_MODE_DRUN | MCTL_KEY2);
        break;
      case RBSYS_ModeEntryModule_Domain2:
        MC_ME_CL2.ModeReg.ME = 0x0000801Du;
        MC_ME_CL2.ModeReg.MCTL = (MCTL_MODE_DRUN | MCTL_KEY1);
        MC_ME_CL2.ModeReg.MCTL = (MCTL_MODE_DRUN | MCTL_KEY2);
        break;
      default:
        break;
    }
  }

  /* ME_GS.S_FLA is ignored - switching of NVM to Normal Mode is not relevant for us and timing may vary */
  #define RBSYS_MODE_CTRL_STATUS_BITS_MASK (0xFFF000FF)

  static inline void RBSYS_ModeEntry_WaitForStatus(RBSYS_ModeEntryModule_t module, uint32 expectedValue)
  {
    volatile uint32* statusReg;
    switch (module)
    {
      case RBSYS_ModeEntryModule_Peripheral:
        statusReg = &MC_ME_PER.ModeReg.GS;
        break;
      case RBSYS_ModeEntryModule_Domain0:
        statusReg = &MC_ME_CL0.ModeReg.GS;
        break;
      case RBSYS_ModeEntryModule_Domain1:
        statusReg = &MC_ME_CL1.ModeReg.GS;
        break;
      case RBSYS_ModeEntryModule_Domain2:
        statusReg = &MC_ME_CL2.ModeReg.GS;
        break;
      default:
        break;
    }

    while( (*statusReg & RBSYS_MODE_CTRL_STATUS_BITS_MASK) != (expectedValue & RBSYS_MODE_CTRL_STATUS_BITS_MASK) )
    {
      RBSYS_TEST_INJECTION_uCModeCtrlModelUpdate();
    };
  }

  static inline void RBSYS_ModeEntry_WaitForModeTransitionFinished(RBSYS_ModeEntryModule_t module)
  {
    volatile uint32* statusReg;
    switch (module)
    {
      case RBSYS_ModeEntryModule_Peripheral:
        statusReg = &MC_ME_PER.ModeReg.GS;
        break;
      case RBSYS_ModeEntryModule_Domain0:
        statusReg = &MC_ME_CL0.ModeReg.GS;
        break;
      case RBSYS_ModeEntryModule_Domain1:
        statusReg = &MC_ME_CL1.ModeReg.GS;
        break;
      case RBSYS_ModeEntryModule_Domain2:
        statusReg = &MC_ME_CL2.ModeReg.GS;
        break;
      default:
        break;
    }

    while( (*statusReg & (1u<<27)) != 0)
    {
      RBSYS_TEST_INJECTION_uCModeCtrlModelUpdate();
    };
  }

  /* Must be called by core 0 */
  static inline void RBSYS_EnablePeripherals(void)
  {
    //activate peripherals for DRUN mode in all Run Peripheral Control registers
    uint32 i;

    // Configure all peripheral configurations to activate peripheral in DRUN mode and disabled in LowPower Mode
    for (i = 0u; i < 8u; i++)
    {
        MC_ME_PER.ModeReg.RUN_PC[i] = 0x8u; // Activate Normal Mode for DRUN Mode
        MC_ME_PER.ModeReg.LP_PC[i] = 0x0u;  // Deactivate for Low-Power Mode
    }
    // Hint: Peripherals do select RUN_PC[0] and LP_PC[0] by default, thereby will be activated automatically

    // Request mode change to DRUN
    RBSYS_ModeEntry_UpdateMode(RBSYS_ModeEntryModule_Peripheral);

    // Wait while mode transition is ongoing, until mode is reached and for connect to oscillator
    // Hint: Peripherals will be enable before PLL has been activated. Therefore, current clock is XOSC
    RBSYS_ModeEntry_WaitForModeTransitionFinished(RBSYS_ModeEntryModule_Peripheral);
  }
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
