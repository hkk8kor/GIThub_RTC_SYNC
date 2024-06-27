#include "TRBSYS_TestInjection.h"
#include "TRBSYS_uCRegisters.h"
#include "RBSYS_Config.h"
#include "RBSYS_CpuInfo.h"

PRC_PTR* TRBSYS_IdleCfg = NULL;

bool TRBSYS_InjectValues = FALSE;
uint32 TRBSYS_InjectTicks = 1;

void TRBSYS_CoreSyncRegisterUpdate(void)
{
  #define RBSYS_REG_CORE0_ARRIVED  (*reg0)
  #define RBSYS_REG_CORE1_ARRIVED  (*reg1)
  #define RBSYS_REG_CORE0_FINISHED (*reg2)

  volatile uint32 *reg0, *reg1, *reg2;
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    reg0 = &EIBD41;
    reg1 = &EIBD42;
    reg2 = &EIBD43;
  #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    reg0 = &INTC2EIBD221;
    reg1 = &INTC2EIBD222;
    reg2 = &INTC2EIBD223;
  #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
    reg0 = &(SENT_0.CH[0].CONFIG);
    reg1 = &(SENT_0.CH[1].CONFIG);
    reg2 = &(SENT_0.CH[2].CONFIG);
  #endif
  if(RBSYS_getCoreID() == RBSYS_CORE_ID_0)
  {
    RBSYS_REG_CORE1_ARRIVED = TRBSYS_SYNCREGDEFAULT | 7u;
  }
  else
  {
    if((RBSYS_REG_CORE0_ARRIVED & 7u) != 7u)
    {
      RBSYS_REG_CORE0_ARRIVED = TRBSYS_SYNCREGDEFAULT | 7u;
    }
    else
    {
      RBSYS_REG_CORE0_FINISHED = TRBSYS_SYNCREGDEFAULT | 7u;
    }
  }

}




TRBSYS_Callback_t TestInjectionCallback_PBUSGuardForGRAMManipulation = NULL;

void RBSYS_TEST_INJECTION_PBUSGuardForGRAMManipulation(void)
{
  if( TestInjectionCallback_PBUSGuardForGRAMManipulation != NULL )
  {
    TestInjectionCallback_PBUSGuardForGRAMManipulation();
  }
}



uint32 TRBSYS_TicksForPreempt = 0;
uint32 TRBSYS_TicksPerLoop = 1;



uint32 TRBSYS_EndlessLoopCount = 0;




// Store last values of registers in order to detect a change
static uint32 CLKD0DIV_before;
static uint32 CLKD1DIV_before;
static uint32 CLKD2DIV_before;
static uint32 CKSC2C_before;

static uint32 SYSCTRLCLKD_PLLC_before;
static uint32 SYSCTRLCLKD_PLLC_cnt;
static uint32 SYSCTRLCKSC_CPUC_before;
static uint32 SYSCTRLCLKD_HSIOSCC_before;
static uint32 SYSCTRLCLKD_HSIOSCC_cnt;
static uint32 SYSCTRLCLKD_EXTCLK0C_before;
static uint32 SYSCTRLCKSC_EXTCLK0C_before;
static uint32 SYSCTRLCLKD_FOUT0C_before;
static uint32 SYSCTRLCKSC_FOUT0C_before;
static uint32 SYSCTRLCKSC_SSCGC_before;


/**
 * Stores the initial state of the registers to not detect every deviation from the reset values as change.
 * Call this after all registers have been assigned their initial value and before calling the function under test.
 */
void TRBSYS_ClockModelInit(void)
{
#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  CLKD0DIV_before = CLKD0DIV;
  CLKD1DIV_before = CLKD1DIV;
  CLKD2DIV_before = CLKD2DIV;
  CKSC2C_before   = CKSC2C;
#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  SYSCTRLCLKD_PLLC_before     = SYSCTRLCLKD_PLLC;
  SYSCTRLCKSC_CPUC_before     = SYSCTRLCKSC_CPUC;
  SYSCTRLCLKD_HSIOSCC_before  = SYSCTRLCLKD_HSIOSCC;
  SYSCTRLCLKD_EXTCLK0C_before = SYSCTRLCLKD_EXTCLK0C;
  SYSCTRLCKSC_EXTCLK0C_before = SYSCTRLCKSC_EXTCLK0C;
  SYSCTRLCLKD_FOUT0C_before   = SYSCTRLCLKD_FOUT0C;
  SYSCTRLCKSC_FOUT0C_before   = SYSCTRLCKSC_FOUT0C;
  SYSCTRLCKSC_SSCGC_before    = SYSCTRLCKSC_SSCGC;
#endif
}

/**
 * Updates a model of the clock module.
 * As the actual behaviour and relations between the registers are not described in the UM in detail,
 * this simulation makes some assumptions.
 */
void TRBSYS_ClockModelUpdate(void)
{
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
    // Clock divider is being changed
    if(CLKD0DIV != CLKD0DIV_before)
    {
      if((pysCLKD0STAT & 0x2) == 0x0 || CLKD0DIV == 0)
      {
        SWT_Eval(FALSE && "Error, CLKD0DIV should not have been written while CLKS0SYNC is de-asserted or CLKD0DIV is not allowed to be 0");
      }
      pysCLKD0STAT = 0x1; // "Clock output does not correspond to the actual divisor setting in CLKD2DIV"
    }
    else
    {
      pysCLKD0STAT = 0x3; // "Clock output corresponds to the actual divisor setting in CLKD2DIV"
    }

    // Clock divider is being changed
    if(CLKD1DIV != CLKD1DIV_before)
    {
      if((pysCLKD1STAT & 0x2) == 0x0 || CLKD1DIV == 0)
      {
        SWT_Eval(FALSE && "Error, CLKD1DIV should not have been written while CLKS1SYNC is de-asserted or CLKD1DIV is not allowed to be 0");
      }
      pysCLKD1STAT = 0x1; // "Clock output does not correspond to the actual divisor setting in CLKD2DIV"
    }
    else
    {
      pysCLKD1STAT = 0x3; // "Clock output corresponds to the actual divisor setting in CLKD2DIV"
    }

    // Clock divider or clock source is being changed
    if(CKSC2C != CKSC2C_before || CLKD2DIV != CLKD2DIV_before)
    {
      if((pysCLKD2STAT & 0x2) == 0x0)
      {
        SWT_Eval(FALSE && "Error, CLKD2DIV should not have been written while CLKS2SYNC is de-asserted");
      }
      if(CLKD2DIV == 0)
      {
        pysCLKD2STAT = 0x0; // Clock inactive and "Clock output does not correspond to the actual divisor setting in CLKD2DIV"
      }
      else
      {
        pysCLKD2STAT = 0x1; // "Clock output does not correspond to the actual divisor setting in CLKD2DIV"
      }
    }
    else
    {
      pysCLKD2STAT = 0x3; // "Clock output corresponds to the actual divisor setting in CLKD2DIV"
    }

    // store current value of registers for the next update
    CLKD0DIV_before = CLKD0DIV;
    CLKD1DIV_before = CLKD1DIV;
    CLKD2DIV_before = CLKD2DIV;
    CKSC2C_before   = CKSC2C;
  #endif

  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    // Main OSC is being enabled or disabled
    if(SYSCTRLMOSCE != 0)
    {
      if(SYSCTRLMOSCE == 1 && (SYSCTRLMOSCS & 0x1) == 0) // Main OSC is being enabled
      {
        SYSCTRLMOSCS = 1; // Main OSC is enabled (directly shows last operation on MOSCE)
      }
      else if(SYSCTRLMOSCE == 2 && (SYSCTRLMOSCS & 0x1) == 1) // Main OSC is being disabled
      {
        if((SYSCTRLPLLS & 1) == 1)
        {
          SYSCTRLMOSCS &= 2u; // Main OSC is disabled but "MOSCS.MOSCSTAB is kept high even if setting MOSCE.MOSCDISTRG to 1 when PLL is operating MOSCS.MOSCEN is cleared to 0."
        }
        else
        {
          SYSCTRLMOSCS = 0u; // Main OSC is disabled (directly shows last operation on MOSCE)
        }
      }
      SYSCTRLMOSCE = 0u; // Main OSC trigger are only writable, reset to 0
    }
    else if(SYSCTRLMOSCS == 1) // Main OSC is enabled for some time and stabilizes
    {
      SYSCTRLMOSCS = 3u; // Main OSC is enabled and stable
    }

    // PLL is being enabled or disabled
    if(SYSCTRLPLLE != 0)
    {
      if(SYSCTRLPLLE == 1 && (SYSCTRLPLLS & 0x1) == 0) // PLL clock is being enabled
      {
        SYSCTRLPLLS = 1; // PLL clock is enabled
      }
      else if(SYSCTRLPLLE == 2 && (SYSCTRLPLLS & 0x1) == 1) // PLL clock is being disabled
      {
        if(SYSCTRLCKSC_CPUC == 0)
        {
          SYSCTRLPLLS &= 2u; // PLL clock is disabled but "PLLS.PLLSTAB is kept high even if setting PLLE.PLLDISTRG to 1 when PLL is selected for System clock source PLLS.PLLCLKEN is cleared to 0."
        }
        else
        {
          SYSCTRLPLLS = 0u; // PLL clock is disabled
        }
      }
      SYSCTRLPLLE = 0; // PLL clock trigger are only writable, reset to 0
    }
    else if(SYSCTRLPLLS == 1) // PLL clock is enabled for some time and stabilizes
    {
      SYSCTRLPLLS = 3u; // PLL clock is enabled and stable
    }

    // IOSC Clock divider is being changed
    if( SYSCTRLCLKD_HSIOSCC != SYSCTRLCLKD_HSIOSCC_before )
    {
      SYSCTRLCLKD_HSIOSCS = 0u; // clock divider is syncing
      SYSCTRLCLKD_HSIOSCC_cnt = 0u;
    }
    else if( SYSCTRLCLKD_HSIOSCC_cnt < 3 )
    {
      SYSCTRLCLKD_HSIOSCC_cnt++; // update of clock divider is not immediate
    }
    else
    {
      SYSCTRLCLKD_HSIOSCS = 2u; // Clock divider is stable after some time
    }

    // PLL Clock divider is being changed
    if(SYSCTRLCLKD_PLLC != SYSCTRLCLKD_PLLC_before)
    {
      SYSCTRLCLKD_PLLS = 1u; // Clock divider is syncing
      SYSCTRLCLKD_PLLC_cnt = 0u;
    }
    else if(SYSCTRLCLKD_PLLC_cnt < 3)
    {
      SYSCTRLCLKD_PLLC_cnt++;
    }
    else // Clock divider stabilizes after some time
    {
      SYSCTRLCLKD_PLLS = 3u; // Clock divider is stable
    }

    // Clock source is being changed
    if(SYSCTRLCKSC_CPUC != SYSCTRLCKSC_CPUC_before)
    {
      // Don't propagate change immediately
    }
    else
    {
      SYSCTRLCKSC_CPUS = SYSCTRLCKSC_CPUC;
    }
    if(SYSCTRLCKSC_SSCGC != SYSCTRLCKSC_SSCGC_before)
    {
      // Don't propagate change immediately
    }
    else
    {
      SYSCTRLCKSC_SSCGS = SYSCTRLCKSC_SSCGC;
    }

    // External clock divider is being changed
    if(SYSCTRLCLKD_EXTCLK0C != SYSCTRLCLKD_EXTCLK0C_before)
    {
      SYSCTRLCLKD_EXTCLK0S &= 2u; // Clock divider is syncing
    }
    else if(SYSCTRLCLKD_EXTCLK0C == 0)
    {
      SYSCTRLCLKD_EXTCLK0S = 1u; // Clock divider stopped
    }
    else
    {
      SYSCTRLCLKD_EXTCLK0S = 3u; // Frequency output is ongoing and clock divider stable
    }

    // External clock divider is being changed
    if(SYSCTRLCLKD_FOUT0C != SYSCTRLCLKD_FOUT0C_before)
    {
      SYSCTRLCLKD_FOUT0S &= 2u; // Clock divider is syncing
    }
    else if(SYSCTRLCLKD_FOUT0C == 0)
    {
      SYSCTRLCLKD_FOUT0S = 1u; // Clock divider stopped
    }
    else
    {
      SYSCTRLCLKD_FOUT0S = 3u; // Frequency output is ongoing and clock divider stable
    }

    if( SYSCTRLCKSC_EXTCLK0C != SYSCTRLCKSC_EXTCLK0C_before )
    {
      // Don't propagate change immediately
    }
    else
    {
      SYSCTRLCKSC_EXTCLK0S = SYSCTRLCKSC_EXTCLK0C;
    }

    // External clock source is being changed
    if(SYSCTRLCKSC_FOUT0C != SYSCTRLCKSC_FOUT0C_before)
    {
      // Don't propagate change immediately
    }
    else
    {
      SYSCTRLCKSC_FOUT0S = SYSCTRLCKSC_FOUT0C;
    }

    // store current value of registers for the next update
    SYSCTRLCKSC_CPUC_before     = SYSCTRLCKSC_CPUC;
    SYSCTRLCKSC_SSCGC_before    = SYSCTRLCKSC_SSCGC;
    SYSCTRLCLKD_PLLC_before     = SYSCTRLCLKD_PLLC;
    SYSCTRLCLKD_HSIOSCC_before  = SYSCTRLCLKD_HSIOSCC;
    SYSCTRLCLKD_EXTCLK0C_before = SYSCTRLCLKD_EXTCLK0C;
    SYSCTRLCKSC_EXTCLK0C_before = SYSCTRLCKSC_EXTCLK0C;
    SYSCTRLCLKD_FOUT0C_before   = SYSCTRLCLKD_FOUT0C;
    SYSCTRLCKSC_FOUT0C_before   = SYSCTRLCKSC_FOUT0C;
  #endif

  #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    MC_CGM_PERIPHERAL_DOMAIN.AC1_SS = MC_CGM_PERIPHERAL_DOMAIN.AC1_SC; //< AUX CLK 1 Status = Control

    /* writing any value to DIV_UPD_TRIG, updates dividers (shown in DIV_UPD_STAT) according to configuration DIV_UPD_TYPE */
    if( MC_CGM_PERIPHERAL_DOMAIN.DIV_UPD_TRIG != 0x0u )
    {
      MC_CGM_PERIPHERAL_DOMAIN.DIV_UPD_STAT = MC_CGM_PERIPHERAL_DOMAIN.DIV_UPD_TYPE;
    }
    else
    {
      MC_CGM_PERIPHERAL_DOMAIN.DIV_UPD_STAT = 0x0; // Update is completed once DIV_UPD_TRIG has been reset (at next Model Update)
    }

    MC_CGM_PERIPHERAL_DOMAIN.DIV_UPD_TRIG = 0x0; // DIV_UPD_TRIG is write only and Update Trigger is asserted instantly

    /* If PLL0 is switched on and selected, set Status to 'locked' */
    if( ((MC_ME_PER.ModeReg.DRUN_MC & MC_PLL0_ON) == MC_PLL0_ON) &&
        ((MC_ME_PER.ModeReg.DRUN_MC & MC_SYSCLK_PLL0) == MC_SYSCLK_PLL0) )
    {
      PLLDIG_PERIPHERAL_DOMAIN.PLL0SR |= (1<<2);
    }
  #endif
}

void TRBSYS_uCModeCtrlModelUpdate(void)
{
  #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    /* take over status from request (DRUN Mode is fixed) */
    MC_ME_PER.ModeReg.GS       = (MC_ME_PER.ModeReg.DRUN_MC & 0x089000FF) | (0x3<<28); //< attention: GS
    MC_ME_CL0.ModeReg.GS       = (MC_ME_CL0.ModeReg.DRUN_MC & 0x089300FF) | (0x3<<28);
    MC_ME_CL1.ModeReg.GS       = (MC_ME_CL1.ModeReg.DRUN_MC & 0x089300FF) | (0x3<<28);
    MC_ME_CL2.ModeReg.GS       = (MC_ME_CL2.ModeReg.DRUN_MC & 0x089300FF) | (0x3<<28);
  #endif
}

#include "RBSYS_TimerOsConfig.h"
void RBSYS_TEST_INJECTION_ProgressTime(void)
{
  if( RBSYS_SYNCTIME_STP != RBSYS_SYNCTIME_STPVAL )
  {
    RBSYS_SystemTimerSynctimeCnt += TRBSYS_InjectTicks;
  }
  TRBSYS_RealtimeTickCtrAddTicks(TRBSYS_InjectTicks);
}

uint32 TRBSYS_loop_cnt = 1;