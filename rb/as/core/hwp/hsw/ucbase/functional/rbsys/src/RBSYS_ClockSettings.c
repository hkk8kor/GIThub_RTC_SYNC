/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"
#include "RBSYS_TestInjection.h"


/* used interfaces */
#include "RBSYS_uCRegisters.h"    // peripheral labels
#include "RBSYS_Intrinsics.h"
#include "RBSYS_CpuVersions.h"  // RBSYS_CPU_REL_D3ED and RBSYS_CPU_REL_D5ED
#include "RBSYS_SystemTimer.h"  // RBSYS_waitUsecLoop



/* realized interfaces */
#include "RBSYS_ClockSettingsIntern.h"
#include "RBSYS_ClockSettings.h"
#include "RBSYS_Subsystem.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

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

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCWatchdog,
                          RBFS_uCWatchdog_Enabled,
                          RBFS_uCWatchdog_Disabled);

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

  typedef struct
  {
    uint32 PLLDividerRegValue;
    uint32 CpuClockFrequencyMHz;
  } rbsys_PLLClockDividerSequenceState_t;

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

  typedef struct
  {
    uint32 PLLDividerRegValue;
    uint32 SSCGDividerRegValue;
    uint32 CpuClockFrequencyMHz;
  } rbsys_PLLClockDividerSequenceState_t;

  typedef struct
  {
    uint32 IOSCDividerRegValue;
    uint32 CpuClockFrequencyMHz;
  } rbsys_IOSCClockDividerSequenceState_t;

#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )



  typedef enum
  {
    rbsys_ClockGearSequenceDirection_GearUp,
    rbsys_ClockGearSequenceDirection_GearDown
  } rbsys_ClockGearSequenceDirection_t;

  static rbsys_PLLClockDividerSequenceState_t rbsys_PLLClockDividerSequence_FindNextState(const rbsys_PLLClockDividerSequenceState_t* sequence,
                                                                                          uint32                                      length,
                                                                                          rbsys_ClockGearSequenceDirection_t          direction,
                                                                                          uint8                                       currentPLLDivider)
  {
    const uint32 numStates = length;
    rbsys_PLLClockDividerSequenceState_t nextState = {0u};

    uint32 i;
    for( i=0; i<numStates; i++ )
    {
      if( sequence[i].PLLDividerRegValue == currentPLLDivider )
      {
        if( direction == rbsys_ClockGearSequenceDirection_GearDown )
        {
          nextState = sequence[i+1];
        }
        else
        {
          nextState = sequence[i-1];
        }
      }
    }
    return nextState;
  }

  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

    static const rbsys_PLLClockDividerSequenceState_t rbsys_PLLClockDividerSequence[] = {{0x01u, 400u},
                                                                                         {0x02u, 200u}};
    #define DIV_SEQ_NUM_STATES (sizeof(rbsys_PLLClockDividerSequence)/sizeof(rbsys_PLLClockDividerSequenceState_t))

    static inline boolean rbsys_IsPLLClockDividerFullyGearedDown(void)
    {
      #define LEAST_FREQ_STATE (rbsys_PLLClockDividerSequence[DIV_SEQ_NUM_STATES-1])

      return ((SYSCTRLCLKD_PLLC & 0xFu) == LEAST_FREQ_STATE.PLLDividerRegValue);
    }

    static inline boolean rbsys_IsPLLClockDividerFullyGearedUp(void)
    {
      #define MAX_FREQ_STATE   (rbsys_PLLClockDividerSequence[0])

      return ((SYSCTRLCLKD_PLLC & 0xFu) == MAX_FREQ_STATE.PLLDividerRegValue);
    }

    static inline boolean rbsys_AreAllPLLsInSync(void)
    {
      return ((SYSCTRLCLKD_PLLS & 0x2u) == 0x2u);
    }

    static rbsys_PLLClockDividerSequenceState_t rbsys_PLLClockDividerSequence_GetNextState(rbsys_ClockGearSequenceDirection_t direction, uint8 currentDivider)
    {
      static_assert(sizeof(rbsys_PLLClockDividerSequence) == (2*sizeof(rbsys_PLLClockDividerSequenceState_t)), "Size of rbsys_PLLClockDividerSequence implausible");
      const uint32 numStates = 2;

      return rbsys_PLLClockDividerSequence_FindNextState(rbsys_PLLClockDividerSequence, numStates, direction, currentDivider);
    }

  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

    static rbsys_IOSCClockDividerSequenceState_t rbsys_IOSCClockDividerSequence_FindNextState(const rbsys_IOSCClockDividerSequenceState_t* sequence,
                                                                                             uint32                                       length,
                                                                                             rbsys_ClockGearSequenceDirection_t           direction,
                                                                                             uint8                                        currentIOSCDivider)
    {
      const uint32 numStates = length;
      rbsys_IOSCClockDividerSequenceState_t nextState = {0u};

      uint32 i;
      for( i=0; i<numStates; i++ )
      {
        if( sequence[i].IOSCDividerRegValue == currentIOSCDivider )
        {
          if( direction == rbsys_ClockGearSequenceDirection_GearDown )
          {
            nextState = sequence[i+1];
          }
          else
          {
            nextState = sequence[i-1];
          }
        }
      }
      return nextState;
    }

    //                                                                                   PLL_DIV, SSCG_DIV, CPU_FREQ
    static const rbsys_PLLClockDividerSequenceState_t rbsys_PLLClockDividerSequence[] = {{0x00u,   0x00u,    320u},
                                                                                         {0x0Eu,   0x0Eu,    280u},
                                                                                         {0x0Cu,   0x0Cu,    240u},
                                                                                         {0x0Au,   0x0Au,    200u},
                                                                                         {0x08u,   0x08u,    160u},
                                                                                         {0x06u,   0x06u,    120u},
                                                                                         {0x04u,   0x05u,    100u}};
    #define DIV_SEQ_NUM_STATES (sizeof(rbsys_PLLClockDividerSequence)/sizeof(rbsys_PLLClockDividerSequenceState_t))

    static inline boolean rbsys_IsPLLClockDividerFullyGearedDown(void)
    {
      #define LEAST_FREQ_STATE (rbsys_PLLClockDividerSequence[DIV_SEQ_NUM_STATES-1])

      return (((SYSCTRLCLKD_PLLC & 0xFu) == LEAST_FREQ_STATE.PLLDividerRegValue) && ((SYSCTRLCLKD_SSCGC & 0xFu) == LEAST_FREQ_STATE.SSCGDividerRegValue));
    }

    static inline boolean rbsys_IsPLLClockDividerFullyGearedUp(void)
    {
      #define MAX_FREQ_STATE   (rbsys_PLLClockDividerSequence[0])

      return (((SYSCTRLCLKD_PLLC & 0xFu) == MAX_FREQ_STATE.PLLDividerRegValue) && ((SYSCTRLCLKD_SSCGC & 0xFu) == MAX_FREQ_STATE.SSCGDividerRegValue));
    }

    static inline boolean rbsys_AreAllPLLsInSync(void)
    {
      return ( ((SYSCTRLCLKD_PLLS & 0x2u) == 0x2u) && ((SYSCTRLCLKD_SSCGS & 0x2u) == 0x2u) );
    }


    static const rbsys_IOSCClockDividerSequenceState_t rbsys_HSIOSCClockDividerSequence[] =  {{0x00u, 100u},
                                                                                              {0x01u,  50u},
                                                                                              {0x02u,  10u}};



    static rbsys_PLLClockDividerSequenceState_t rbsys_PLLClockDividerSequence_GetNextState(rbsys_ClockGearSequenceDirection_t direction, uint8 currentPLLDivider)
    {
      static_assert( sizeof(rbsys_PLLClockDividerSequence)  == 7*sizeof(rbsys_PLLClockDividerSequenceState_t), "Size of rbsys_PLLClockDividerSequence implausible" );
      const uint32 numStates = 7;

      return rbsys_PLLClockDividerSequence_FindNextState(rbsys_PLLClockDividerSequence, numStates, direction, currentPLLDivider);
    }

    static rbsys_IOSCClockDividerSequenceState_t rbsys_HSIOSCClockDividerSequence_GetNextDivider(rbsys_ClockGearSequenceDirection_t direction, uint8 currentDivider)
    {
      static_assert(sizeof(rbsys_HSIOSCClockDividerSequence) == 3*sizeof(rbsys_IOSCClockDividerSequenceState_t), "Size of rbsys_HSIOSCClockDividerSequence implausible");
      const uint32 numStates = 3;

      return rbsys_IOSCClockDividerSequence_FindNextState(rbsys_HSIOSCClockDividerSequence, numStates, direction, currentDivider);
    }
  #endif

  /**
    * The following procedure for setting clocks is according to Clock Supply Application Note Rev.1.10 p.24.
    * (There is another description of the gear up in U2A HW UM 1.10 p. 1063, but it is less detailed)
    *
    * @startuml
    * (*) --> RBSYS_SetupClocks_RenesasU2A
    * --> Enable Write Access
    * if "Is CPU operating on PLL?"
    *   note right: In case CPU is already operated on PLL, MainOSC can be considered fine.
    *   --> [yes] Gear up PLL
    * else
    *   [no] if "Is Main Oscillator started?"
    *     --> MainOSC started
    *   else
    *     --> [no] Start MainOSC
    *     --> MainOSC started
    *   endif
    *   if "Is PLL started?"
    *     --> PLL started
    *   else
    *     --> [no] Start PLL
    *     --> PLL started
    *   endif
    *   --> Gear down PLL
    *   note right: PLL frequency is lowered to match the transition frequency
    *   --> Gear up Internal Oscillator
    *   note right: IOSC frequency is increased to match the transition frequency
    *   --> Switch from IOSC to PLL
    *   note right: IOSC and PLL frequency should match now - do transition
    *   --> Gear up PLL
    * endif
    * note right: Increase PLL frequency to match the final system clock frequency
    * --> Disable Write Access
    * --> (*)
    * @enduml
    *
    * ATTENTION: When updating this functionality, notify XC-ECO to update their PLL Startup Code for TrustedBoot on HSM-side as well!
    * ToDo: rename more generically
    */

  /** Clocks are not fully set up - therefore special wait-function - based on snooze instrinsic - is used */
  static void rbsys_SetupClocks_SnoozeUsecLoop(uint32 time_usec, uint32 cpu_freq_MHz)
  {

    /* 1 Snooze = 32 CPU ticks
     * Example:                        (40us * 400*ticks/us) / 32 ticks) + 1 => +1 for ceiling       */
    uint32 loops = (uint32)(( (uint32)(time_usec * cpu_freq_MHz) ) / 32) + 1;
    RBSYS_SNOOZE_LOOP((sint32)loops);
  }


  void RBSYS_SetupClocks_RenesasU2A(void)
  {
    /* todo: check for common name for U2A and U2C */

    uint32 currentCPUFrequency = 0;

    // Release write protection of clock control registers.
    RBSYS_EnableWriteAccessToClockController();

    // In case the CPU is not operating on the PLL
    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      if (SYSCTRLCKSC_CPUS != 0x0u)
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      if ((SYSCTRLCKSC_CLEANS != 0x0u) || (SYSCTRLCKSC_SSCGS != 0x0u))
    #endif
    {

      // Start Main OSC. Procedure for starting the Main OSC according to U2A HW UM 1.10 p.1020 note 2 steps 1 to 4
      if (SYSCTRLMOSCS == 0x0u)                                 // 1. Confirm that the Main OSC is stopped (MOSCS.MOSCEN = 0 & MOSCS.MOSCSTAB = 0).
      {
        SYSCTRLMOSCE   = 0x1u;                                  // 2. Start the Main OSC (MOSCE.MOSCENTRG = 1).
        RBSYS_TEST_INJECTION_ClockModelUpdate();

        // Wait until Main OSC is stable.
        while (SYSCTRLMOSCS != 0x3u)                            // 3. Confirm that the Main OSC has been stable (MOSCS.MOSCEN = 1 & MOSCS.MOSCSTAB = 1).
        {
          RBSYS_snooze();
          RBSYS_TEST_INJECTION_ClockModelUpdate();
        }
        RBSYS_SNOOZE_AT_LEAST_1_4US_AT_100MHZ();                // 4. Wait 1.4us or Read the "MOSCS.MOSCSTAB = 1" four times.
        // Hint: CPU frequency can be <= 100MHz (assume 100MHz as worst case for snooze time)
      }

      // Start PLL. Procedure for starting the PLL according to U2A HW UM 1.10 p.1017 note 2 steps 1 to 5
                                                                // 1. Confirm that the Main OSC is stable. Done by previous procedure.
                                                                //    As only this function configures Main OSC and PLL,
                                                                //    the waiting for a stable Main OSC above is executed before this procedure.
      if (SYSCTRLPLLS == 0x0u)                                  // 2. Confirm that the PLL is stopped (PLLS.PLLCLKEN = 0 & PLLS.PLLCLKSTAB = 0).
      {
        SYSCTRLPLLE    = 0x1u;                                  // 3. Start the PLL (PLLE.PLLENTRG = 1).
        RBSYS_TEST_INJECTION_ClockModelUpdate();

        // Wait until PLL is stable.
        while (SYSCTRLPLLS != 0x3u)                             // 4. Confirm that the PLL has been stable (PLLS.PLLCLKEN = 1 & PLLS.PLLCLKSTAB = 1).
        {
          RBSYS_snooze();
          RBSYS_TEST_INJECTION_ClockModelUpdate();
        }
        RBSYS_SNOOZE_AT_LEAST_1_4US_AT_100MHZ();                // 5. Wait 1.4us or Read the "PLLS.PLLCLKSTAB = 1" four times.
        // Hint: CPU frequency can be <= 100MHz (assume 100MHz as worst case for snooze time)
      }
      // U2C: SSCG has to be used as well and is enabled via PLL register above as well.
    }

    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

      // Ramp Up behaviour of PLL
      /*
        @startuml

        left to right direction

        Reset --> State0
        State0 : Source = HSIOSC
        State0 : Freq   = 100MHz
        Reset <-[#red]- State0

        State0 --> State1
        State1 : Source = PLL
        State1 : Freq   = 200MHz
        Reset --> State1
        Reset <-[#red]- State1

        State1 --> State2
        State2 : Source = PLL
        State2 : Freq   = 400MHz
        Reset --> State2
        Reset <-[#red]- State2

        @enduml

        ATTENTION: Application Reset does not reset PLL, SYS_CLK config, HSIOSC config. Therefore, Clock Ramp-Up
        may be partially
      */

      // See U2A HW User Manual R01UH0820EJ0130 13.6.5
      // PLL Clock Divider has to be increased/reduced step by step      1/2,    1/1
      // PLL Clock Divider has to be increased/reduced step by step      200MHz, 400MHz

      {
        // Repeatedly gear down PLL while not fully geared down
        while( ! rbsys_IsPLLClockDividerFullyGearedDown() )
        {
          rbsys_PLLClockDividerSequenceState_t nextState;

          // Wait Until Clock divider is synchronized
          while ((SYSCTRLCLKD_PLLS & 0x2u) != 0x2u)
          {
            RBSYS_snooze();
            RBSYS_TEST_INJECTION_ClockModelUpdate();
          }

          // Change PLL divider
          nextState = rbsys_PLLClockDividerSequence_GetNextState(rbsys_ClockGearSequenceDirection_GearDown, (uint8)(SYSCTRLCLKD_PLLC & 0xFFu) );
          SYSCTRLCLKD_PLLC = nextState.PLLDividerRegValue;
          RBSYS_TEST_INJECTION_ClockModelUpdate();

          // Wait Until Clock divider is synchronized
          while( !rbsys_AreAllPLLsInSync() )
          {
            RBSYS_snooze();
            RBSYS_TEST_INJECTION_ClockModelUpdate();
          }

          // Wait at least 100us
          currentCPUFrequency = nextState.CpuClockFrequencyMHz;
          rbsys_SetupClocks_SnoozeUsecLoop(100, currentCPUFrequency);
        }

        currentCPUFrequency = 200;


        SYSCTRLCKSC_CPUC = 0x0u;                                   // Change CPU_CLK to PLL
        RBSYS_TEST_INJECTION_ClockModelUpdate();

        // Verify CLK_PLLO is selected as clock source.
        while ((SYSCTRLCKSC_CPUS & 0x1u) != 0x0u)
        {
          RBSYS_snooze();
          RBSYS_TEST_INJECTION_ClockModelUpdate();
        }
        // Wait 100us after Verifying. (System Clock is still at 200MHz)
        rbsys_SetupClocks_SnoozeUsecLoop(100, currentCPUFrequency);

        // Change division ratio of PLL from 1/2 to 1/1. Procdedure according to U2A HW UM 1.10 p.1027 Cautions 2. and 3.
                                                                    // Caution 2. Confirm that PLL is stable. Done by previous procedure.
                                                                    // Caution 3. Confirm that clock divider is stable.

        // Repeatedly gear up PLL while not fully geared up
        while( ! rbsys_IsPLLClockDividerFullyGearedUp() )
        {
          rbsys_PLLClockDividerSequenceState_t nextState;

          // Wait Until Clock divider is synchronized
          while( ! rbsys_AreAllPLLsInSync() )
          {
            RBSYS_snooze();
            RBSYS_TEST_INJECTION_ClockModelUpdate();
          }

          // Change PLL divider
          nextState = rbsys_PLLClockDividerSequence_GetNextState(rbsys_ClockGearSequenceDirection_GearUp, (uint8)(SYSCTRLCLKD_PLLC & 0xFFu));
          SYSCTRLCLKD_PLLC = nextState.PLLDividerRegValue;
          RBSYS_TEST_INJECTION_ClockModelUpdate();

          // Wait Until Clock divider is synchronized
          while( ! rbsys_AreAllPLLsInSync() )
          {
            RBSYS_snooze();
            RBSYS_TEST_INJECTION_ClockModelUpdate();
          }

          // Wait at least 100us
          currentCPUFrequency = nextState.CpuClockFrequencyMHz;
          rbsys_SetupClocks_SnoozeUsecLoop(100, currentCPUFrequency);
        }
      }

    #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

      {
        // Ramp Up behaviour of PLL
        /*
          @startuml

          left to right direction

          Reset --> State1
          State1 : Source = HSIOSC / 10
          State1 : Freq   = 10 MHz
          Reset <-[#red]- State1

          State1 --> State2
          State2 : Source = HSIOSC / 2
          State2 : Freq   = 50MHz
          Reset --> State2
          Reset <-[#red]- State2

          State2 --> State3
          State3 : Source = HSIOSC
          State3 : Freq   = 100MHz
          Reset --> State3
          Reset <-[#red]- State3

          State3 --> State4
          State4 : Source = PLL
          State4 : Freq   = 100MHz
          Reset --> State4
          Reset <-[#red]- State4

          State4 --> State5
          State5 : Source = PLL
          State5 : Freq   = 120MHz
          Reset --> State5
          Reset <-[#red]- State5

          State5 --> State6
          State6 : Source = PLL
          State6 : Freq   = 160MHz
          Reset --> State6
          Reset <-[#red]- State6

          State6 --> State7
          State7 : Source = PLL
          State7 : Freq   = 200MHz
          Reset --> State7
          Reset <-[#red]- State7

          State7 --> State8
          State8 : Source = PLL
          State8 : Freq   = 240MHz
          Reset --> State8
          Reset <-[#red]- State8

          State8 --> State9
          State9 : Source = PLL
          State9 : Freq   = 280MHz
          Reset --> State9
          Reset <-[#red]- State9

          State9 --> State10
          State10 : Source = PLL
          State10 : Freq   = 320MHz
          Reset --> State10
          Reset <-[#red]- State10

          @enduml

          ATTENTION: Application Reset does not reset PLL, SYS_CLK config, HSIOSC config. Therefore, Clock Ramp-Up
          may be partially
        */

        /** Procedure according to U2C HW User Manual R01UH1027EJ0040 13.6.4
         *
         * SSCG Clock Divider has to be increased/reduced step by step      16/16,  14/16,  12/16,  10/16,  8/16,   6/16,   5/16
         * SSCG Clock Divider has to be increased/reduced step by step      320MHz, 280MHz, 240MHz, 200MHz, 160MHz, 120MHz, 100MHz
         *
         * PLL  Clock Divider has to be increased/reduced step by step      16/16,  14/16,  12/16,  10/16,  8/16,   6/16,   4/16
         * PLL  Clock Divider has to be increased/reduced step by step      400MHz, 350MHz, 300MHz, 250MHz, 200MHz, 150MHz, 100MHz
         *
         * HSIOSC Clock Divider has to be increased/reduced step by step    1/1,    1/2,    1/10
         * HSIOSC Clock Divider has to be increased/reduced step by step    200MHz, 100MHz, 20MHz
         */

        // Wait Until PLL and SSCG Clock dividers are synchronized
        while( !rbsys_AreAllPLLsInSync() )
        {
          RBSYS_snooze();
          RBSYS_TEST_INJECTION_ClockModelUpdate();
        }

        // Repeatedly gear down PLL and SSCG while not fully geared down
        while( !rbsys_IsPLLClockDividerFullyGearedDown() )
        {
          rbsys_PLLClockDividerSequenceState_t nextState;

          // Change PLL divider
          nextState = rbsys_PLLClockDividerSequence_GetNextState(rbsys_ClockGearSequenceDirection_GearDown, (uint8)(SYSCTRLCLKD_PLLC & 0xFFu));
          SYSCTRLCLKD_PLLC = nextState.PLLDividerRegValue;
          SYSCTRLCLKD_SSCGC = nextState.SSCGDividerRegValue;
          RBSYS_TEST_INJECTION_ClockModelUpdate();

          // Wait Until Clock divider is synchronized
          while ( !rbsys_AreAllPLLsInSync() )
          {
            RBSYS_snooze();
            RBSYS_TEST_INJECTION_ClockModelUpdate();
          }

          // Wait at least 20us
          currentCPUFrequency = nextState.CpuClockFrequencyMHz;
          rbsys_SetupClocks_SnoozeUsecLoop(20, currentCPUFrequency);
        }

        // Wait Until Clock divider is synchronized
        while ((SYSCTRLCLKD_HSIOSCS & 0x2u) != 0x2u)
        {
          RBSYS_snooze();
          RBSYS_TEST_INJECTION_ClockModelUpdate();
        }

        // Repeatedly gear up HSIOSC while not fully geared up
        while( SYSCTRLCLKD_HSIOSCC != 0x00 )
        {
          rbsys_IOSCClockDividerSequenceState_t nextState;

          // Change HSIOSC divider
          nextState = rbsys_HSIOSCClockDividerSequence_GetNextDivider(rbsys_ClockGearSequenceDirection_GearUp, SYSCTRLCLKD_HSIOSCC);
          SYSCTRLCLKD_HSIOSCC = nextState.IOSCDividerRegValue;

          // Wait Until Clock divider is synchronized
          while ((SYSCTRLCLKD_HSIOSCS & 0x2u) != 0x2u)
          {
            RBSYS_snooze();
            RBSYS_TEST_INJECTION_ClockModelUpdate();
          }

          // Wait at least 20us
          currentCPUFrequency = nextState.CpuClockFrequencyMHz;
          rbsys_SetupClocks_SnoozeUsecLoop(20, currentCPUFrequency);
        }

        // Select
        //  - PLL as input for System_Clock_Clean
        //  - SSCG as input for System_Clock (w/ optional FM)
        SYSCTRLCKSC_CLEANC = 0x00u;
        SYSCTRLCKSC_SSCGC = 0x00u;
        RBSYS_TEST_INJECTION_ClockModelUpdate();

        // Wait until PLL is selected as System Clock
        while( (SYSCTRLCKSC_CLEANS != 0x00u) || (SYSCTRLCKSC_SSCGS != 0x00u) )
        {
          RBSYS_snooze();
          RBSYS_TEST_INJECTION_ClockModelUpdate();
        }

        // Wait Until PLL and SSCG Clock dividers are synchronized
        while( !rbsys_AreAllPLLsInSync() )
        {
          RBSYS_snooze();
          RBSYS_TEST_INJECTION_ClockModelUpdate();
        }

        // Repeatedly gear up PLL while not fully geared up
        while( !rbsys_IsPLLClockDividerFullyGearedUp() )
        {
          rbsys_PLLClockDividerSequenceState_t nextState;

          // Change PLL divider
          nextState = rbsys_PLLClockDividerSequence_GetNextState(rbsys_ClockGearSequenceDirection_GearUp, (uint8)(SYSCTRLCLKD_PLLC & 0xFFu));
          SYSCTRLCLKD_PLLC = nextState.PLLDividerRegValue;
          SYSCTRLCLKD_SSCGC = nextState.SSCGDividerRegValue;
          RBSYS_TEST_INJECTION_ClockModelUpdate();

          // Wait Until PLL and SSCG Clock dividers are synchronized
          while( !rbsys_AreAllPLLsInSync() )
          {
            RBSYS_snooze();
            RBSYS_TEST_INJECTION_ClockModelUpdate();
          }

          // Wait at least 20us
          currentCPUFrequency = nextState.CpuClockFrequencyMHz;
          rbsys_SetupClocks_SnoozeUsecLoop(20, currentCPUFrequency);
        }
      }
    #endif

    // Set write protection of clock control registers.
    RBSYS_DisableWriteAccessToClockController();
  }
#endif


#if( ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)) \
  && (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION) )
  /**
   * @brief Process for Checking Settings and Status of PLL Clock Tree
   *
   * @return void
   */
  void RBSYS_PRC_CheckClockTreeSettings(void)
  {
    RBSYS_CheckClockTreeConfiguration();
  }
#endif

void RBSYS_SetupECP(uint16 ECLK_KHZ)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)

    /* SW workaround for Renesas HW Errata RB095 "updating failure of ECLK"
     *
     * ECLK has the possibility that write access to clock divider register CLKD2DIV and CLKD3DIV
     * is ignored internally when the setting of ECLK is reprogrammed.
     * Programming from initial state after reset is successful without this limitation.
     */
    int i;
    for(i = 0; i < 2; i++)
    {
      CLKD2DIV = (RBSYS_CPU_CLK_KHZ/ECLK_KHZ);    // divide CPU clock "CLK_CPU" to reach requested ECLK frequency
      (void) CLKD2DIV;                            // read back CLKD2DIV - confirming of register write

      CKSC2C   = 0x5;                             // select clock source "CLK_CPU" for ECLK -> SIKO requirement
      RBSYS_TEST_INJECTION_ClockModelUpdate();

      /* wait until clock is active and clock output corresponds to the actual divisor setting */
      while((CLKD2STAT & 0x3u) != 0x3u)
      {
        RBSYS_TEST_INJECTION_ClockModelUpdate();
      }

      /* insert 4 times dummy reads of CLKD2STAT requested as workaround for hw limitiation */
      (void) CLKD2STAT;
      (void) CLKD2STAT;
      (void) CLKD2STAT;
      (void) CLKD2STAT;
    }

  #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
      || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
      #define RBSYS_ECLK_CLKSEL_CTRL (SYSCTRLCKSC_FOUT0C)
      #define RBSYS_ECLK_CLKSEL_STAT (SYSCTRLCKSC_FOUT0S)
      #define ECLK_CLKSEL_HBUS       (0x1)
      #define RBSYS_ECLK_CLKDIV_CTRL (SYSCTRLCLKD_FOUT0C)
      #define RBSYS_ECLK_CLKDIV_STAT (SYSCTRLCLKD_FOUT0S)
    #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
      #define RBSYS_ECLK_CLKSEL_CTRL (SYSCTRLCKSC_EXTCLK0C)
      #define RBSYS_ECLK_CLKSEL_STAT (SYSCTRLCKSC_EXTCLK0S)
      #define ECLK_CLKSEL_HBUS       (0x4)
      #define RBSYS_ECLK_CLKDIV_CTRL (SYSCTRLCLKD_EXTCLK0C)
      #define RBSYS_ECLK_CLKDIV_STAT (SYSCTRLCLKD_EXTCLK0S)
    #endif

    /** ECLK is only configured to HSB once, further calls will only change the Frequency Divider */
    static boolean rbsys_IsEClockSourceSelected = FALSE;

    RBSYS_EnableWriteAccessToClockController();

    /// Procedure from U2A HW UM Rev1.10 chapter 13.6.1.2 / U2C HW UM Rev0.40 chapter 13.6.1.2.

    if( ! rbsys_IsEClockSourceSelected )
    {
      /** Clock is default deactivated - nevertheless check as requested in manual */
      RBSYS_ECLK_CLKDIV_CTRL = 0;                                   // stop the clock output
      RBSYS_TEST_INJECTION_ClockModelUpdate();
      // wait until clock is stopped
      while((RBSYS_ECLK_CLKDIV_STAT & 0x3u) != 0x1u)                // wait for output to stop
      {
        RBSYS_TEST_INJECTION_ClockModelUpdate();
      }

      RBSYS_ECLK_CLKSEL_CTRL = ECLK_CLKSEL_HBUS;                    // keep CLK_HSB as ECLK source (80MHz)
      rbsys_IsEClockSourceSelected = TRUE;                          // do this only once to avoid stopping the ECLK
      RBSYS_TEST_INJECTION_ClockModelUpdate();
      // wait for completion of selection
      while((RBSYS_ECLK_CLKSEL_STAT & 0xFu) != ECLK_CLKSEL_HBUS)    // wait for CLK_HSB to be confirmed
      {
        RBSYS_TEST_INJECTION_ClockModelUpdate();
      }
    }

    RBSYS_ECLK_CLKDIV_CTRL = (uint16)(RBSYS_HSB_CLK_KHZ/ECLK_KHZ);  // divide HSB clock "CLK_HSB" to reach requested ECLK frequency
    RBSYS_TEST_INJECTION_ClockModelUpdate();
    // wait while DIV is synchronizing
    while( (RBSYS_ECLK_CLKDIV_STAT & 0x3u) != 0x3u)                 // wait for output divider to synchronize
    {
      RBSYS_TEST_INJECTION_ClockModelUpdate();
    }

    RBSYS_DisableWriteAccessToClockController();

  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

    uint32 divider = (400000 / ECLK_KHZ); /* 400,000 [kHz] / ECLK [kHz] */

    assert( divider <= 512 ); // Divider of SYSCLK0 can be configured to 1..512
    /* Hint: -> Divider cannot be below 8 as SYSCLK maximum is 50MHz */

    MC_CGM_PERIPHERAL_DOMAIN.AC6_SC  = (2u << 24);                         // select PLL0 PHI as clock source for SYSCLK0 (used as ECLK)
    while(MC_CGM_PERIPHERAL_DOMAIN.AC6_SS != (2u << 24)){}                 // wait until clock is selected
    MC_CGM_PERIPHERAL_DOMAIN.AC6_DC0  = (CGM_DC_DIVENABLE | ((divider-1) << CGM_DC_DIV_Offset));

  #else
    #error ("Setting of ECLK is not implemented for this uC family")
  #endif

}






#if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))

  void RBSYS_SetupClocks_RenesasP1x(void)
  {
    if(RBSYS_CPU_REL_D3ED || RBSYS_CPU_REL_D5ED)
    {
      /* Configure CLKiDIV in case of D1/D2-SW running on a D3ED or D5ED.
       * Detection during runtime is required, due to trace based failure analysis of a series D1/D2-SW on
       * an Emulation-Device
       */

      //CPU_CLK=80MHz, CLK_HSB=80MHz, CLK_LSB=40MHz
      CLKD0DIV = 0x3u;
      RBSYS_TEST_INJECTION_ClockModelUpdate();
      while((CLKD0STAT & 0x3u) != 0x3u)
      {
        RBSYS_TEST_INJECTION_ClockModelUpdate();
      }

      // CLKP_C=80MHz, CLKP_H1=80MHz, CLKP_H2=80MHz, CLKP_L=40MHz CLKP_T=40MHz
      CLKD1DIV = 0x2u;
      RBSYS_TEST_INJECTION_ClockModelUpdate();
      while((CLKD1STAT & 0x3u) != 0x3u)
      {
        RBSYS_TEST_INJECTION_ClockModelUpdate();
      }
    }
  }

#endif


#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  /* Setup all PeripheralClocks centrally */
  void RBSYS_SetupPeripheralClocks(void)
  {
    /* Update Dividers synchronously via DIV_UPD_TRIG registers */
    MC_CGM_DOMAIN_0.DIV_UPD_TYPE = 0x80000000u;
    MC_CGM_DOMAIN_1.DIV_UPD_TYPE = 0x80000000u;
    MC_CGM_DOMAIN_2.DIV_UPD_TYPE = 0x80000000u;

    /* TODO: Shall be done before switching clock source to PLL!!! */
    MC_CGM_DOMAIN_0.SC_DC[0] = (CGM_DC_DIVENABLE | CGM_DC_DIV8);           // DIV_SYS_CLK_0/PCLKDBG_0 = 50MHz  (400/8) -> Divider has to be set to 8 in any case!
    MC_CGM_DOMAIN_0.SC_DC[1] = (CGM_DC_DIVENABLE | CGM_DC_DIV2);           // AIPS_LLPP0              = 200MHz (400/2)
    MC_CGM_DOMAIN_0.SC_DC[2] = (CGM_DC_DIVENABLE | CGM_DC_DIV8);           // LBIST_SLOW              = 50MHz  (400/8)
    MC_CGM_DOMAIN_0.SC_DC[3] = (CGM_DC_DIVENABLE | CGM_DC_DIV8);           // MBIST_SLOW              = 50MHz  (400/8)
    MC_CGM_DOMAIN_0.SC_DC[4] = (CGM_DC_DIVENABLE | CGM_DC_DIV4);           // NVM_WR                  = 100MHz (400/4) -> Divider has to be set to 4 in any case!

    MC_CGM_DOMAIN_1.SC_DC[0] = (CGM_DC_DIVENABLE | CGM_DC_DIV8);           // DIV_SYS_CLK_1/PCLKDBG_1 = 50MHz  (400/8) -> Divider has to be set to 8 in any case!
    MC_CGM_DOMAIN_1.SC_DC[1] = (CGM_DC_DIVENABLE | CGM_DC_DIV2);           // AIPS_LLPP1              = 200MHz (400/2)

    MC_CGM_DOMAIN_2.SC_DC[0] = (CGM_DC_DIVENABLE | CGM_DC_DIV8);           // DIV_SYS_CLK_2/PCLKDBG_2 = 50MHz  (400/8) -> Divider has to be set to 8 in any case!
    MC_CGM_DOMAIN_2.SC_DC[1] = (CGM_DC_DIVENABLE | CGM_DC_DIV2);           // AIPS_LLPP2              = 200MHz (400/2)

    /* Trigger Clock divider update (Hint: Not required for Auxiliary Clocks below!)*/
    MC_CGM_DOMAIN_0.DIV_UPD_TRIG = 0xFEEDFACEu;
    MC_CGM_DOMAIN_1.DIV_UPD_TRIG = 0xFEEDFACEu;
    MC_CGM_DOMAIN_2.DIV_UPD_TRIG = 0xFEEDFACEu;

    /* Configure FRAY_CLK */
    MC_CGM_PERIPHERAL_DOMAIN.AC2_DC0  = (CGM_DC_DIVENABLE | CGM_DC_DIV5); // FRAY = 80MHz (400/5)

    /* Configure GTM_CLK and ADC_CLK */
    MC_CGM_PERIPHERAL_DOMAIN.AC3_SC  = (2u << 24);                         // select PLL0 PHI as clock source for GTM, SDADC, SARADC
    while(MC_CGM_PERIPHERAL_DOMAIN.AC3_SS != (2u << 24)){}                 // wait until clock is selected, todo: might not be needed
    MC_CGM_PERIPHERAL_DOMAIN.AC3_DC[0]  = (CGM_DC_DIVENABLE | CGM_DC_DIV2);  // GTM0   = 200MHz   (400/2)
    MC_CGM_PERIPHERAL_DOMAIN.AC3_DC[1]  = (CGM_DC_DIVENABLE | CGM_DC_DIV25); // SDADC  = 16MHz    (400/25)
    MC_CGM_PERIPHERAL_DOMAIN.AC3_DC[2]  = (CGM_DC_DIVENABLE | CGM_DC_DIV12); // SARADC = 33.33MHz (400/12)
    // MC_CGM_PERIPHERAL_DOMAIN.AC3_DC[3]  = (CGM_DC_DIVENABLE | CGM_DC_DIV4);  // GTM1   = 100MHz   (400/4) /* doesnt exist on P6 */

    /* AC4,5,7 not configured as not required at the moment (AC6 is configured in different function) */

    /* Configure CAN_CLK (1) */
    MC_CGM_PERIPHERAL_DOMAIN.AC8_SC  = (2u << 24);                         // select PLL0 PHI as clock source for CAN 0 and CAN2
    while(MC_CGM_PERIPHERAL_DOMAIN.AC8_SS != (2u << 24)){}                 // wait until clock is selected, todo: might not be needed
    MC_CGM_PERIPHERAL_DOMAIN.AC8_DC[0] = (CGM_DC_DIVENABLE | CGM_DC_DIV5);   // CAN_CLK0 = 80MHz (400/5)
    MC_CGM_PERIPHERAL_DOMAIN.AC8_DC[1] = (CGM_DC_DIVENABLE | CGM_DC_DIV5);   // CAN_CLK2 = 80MHz (400/5)

    /* Configure CAN_CLK (2) */
    MC_CGM_PERIPHERAL_DOMAIN.AC9_SC  = (2u << 24);                         // select PLL0 PHI as clock source for CAN 1 and CANXL
    while(MC_CGM_PERIPHERAL_DOMAIN.AC9_SS != (2u << 24)){}                 // wait until clock is selected, todo: might not be needed
    MC_CGM_PERIPHERAL_DOMAIN.AC9_DC0 = (CGM_DC_DIVENABLE | CGM_DC_DIV5);   // CAN_CLK1   = 80MHz (400/5)
    MC_CGM_PERIPHERAL_DOMAIN.AC9_DC1 = (CGM_DC_DIVENABLE | CGM_DC_DIV5);   // CANXL_CLK  = 80MHz (400/5) //< P6 specific change, X7 does combine CAN_CLK1 and CANXL_CLK in DC0


    /* Configure SPI_CLK */
    MC_CGM_PERIPHERAL_DOMAIN.AC10_SC  = (2u << 24);                        // select PLL0 PHI as clock source for SPI_CLK
    while(MC_CGM_PERIPHERAL_DOMAIN.AC10_SS != (2u << 24)){}                // wait until clock is selected, todo: might not be needed
    MC_CGM_PERIPHERAL_DOMAIN.AC10_DC0 = (CGM_DC_DIVENABLE | CGM_DC_DIV5);  // SPI   = 80MHz    (400/5)

    /* Configure TIME_BASE_CLK */
    MC_CGM_PERIPHERAL_DOMAIN.AC11_SC  = (2u << 24);                        // select PLL0 PHI as clock source for TIME_BASE_CLK
    while(MC_CGM_PERIPHERAL_DOMAIN.AC11_SS != (2u << 24)){}                // wait until clock is selected, todo: might not be needed
    MC_CGM_PERIPHERAL_DOMAIN.AC11_DC[0] = (CGM_DC_DIVENABLE | CGM_DC_DIV4);  // TIME_BASE = 100MHz (400/4)
    /* AC11_DC1/2 are missing -> todo: not required? (P6 spec doesnt even mention those anymore) */

    /* Configure LIN, SENT, OSPI, MSCP Clocks */
    MC_CGM_PERIPHERAL_DOMAIN.AC12_SC  = (2u << 24);                       // select PLL0 PHI as clock source
    while(MC_CGM_PERIPHERAL_DOMAIN.AC12_SS != (2u << 24)){}               // wait until clock is selected, todo: might not be needed
    MC_CGM_PERIPHERAL_DOMAIN.AC12_DC[0] = (CGM_DC_DIVENABLE | CGM_DC_DIV4); // LIN = 100MHz
    MC_CGM_PERIPHERAL_DOMAIN.AC12_DC[1] = (CGM_DC_DIVENABLE | CGM_DC_DIV2); // MSC = 200MHz
    MC_CGM_PERIPHERAL_DOMAIN.AC12_DC[2] = (CGM_DC_DIVENABLE | CGM_DC_DIV8); // SENT = 50MHz
    MC_CGM_PERIPHERAL_DOMAIN.AC12_DC[3] = (CGM_DC_DIVENABLE | CGM_DC_DIV2); // OSPI = 200MHz
    MC_CGM_PERIPHERAL_DOMAIN.AC12_DC[5] = (CGM_DC_DIVENABLE | CGM_DC_DIV4); // MSCP = 100MHz

    MC_CGM_PERIPHERAL_DOMAIN.AC13_SC  = (2u << 24);                       // select PLL0 PHI as clock source
    while(MC_CGM_PERIPHERAL_DOMAIN.AC13_SS != (2u << 24)){}               // wait until clock is selected, todo: might not be needed
    MC_CGM_PERIPHERAL_DOMAIN.AC13_DC0 = (CGM_DC_DIVENABLE | CGM_DC_DIV4); // ETN = 100MHz (400/4)
  }

#endif

#if ((RBFS_uCWatchdog == RBFS_uCWatchdog_Enabled) && ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)))
  RBSYS_CLK_WDT_Divider_t RBSYS_getClkWdtDivider(void)
  {
    uint32 wdts = SYSCTRLCKSC_WDTS;
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      if(wdts == 2)
      {
        return RBSYS_CLK_WDT_DIVIDER_800;
      }
      else
    #endif
    if(wdts == 1)
    {
      return RBSYS_CLK_WDT_DIVIDER_640;
    }
    else
    {
      return RBSYS_CLK_WDT_DIVIDER_20;
    }
  }
#endif

/** @} */
/* End ingroup RBSYS */
