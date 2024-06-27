/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief System Start-up
 *
 * Handling of the system start-up and uC configuration
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_CoreInit.h"
#include "RBSYS_CpuInfo.h"
#include "Monitorings/RBSYS_StackHandling.h"
#include "Monitorings/RBSYS_ErrorHooks.h"
#include "SystemMemoryProtection/RBSYS_GuardConfigCommon.h"
#include "RBSYS_GuardConfig.h"
#include "Statistics/RBSYS_StartupTimingIntern.h"
#include "RBSYS_uCRegisters.h"
#include "RBSYS_TimerSetup.h"
#include "RBSYS_SystemTimer.h"
#include "RBSYS_CacheControlIntern.h"
#include "Os.h"
#include "Os_ConfigInterrupts.h"              // for Os_InitializeVectorTable on U2A port
#include "RBSYS_RAMBackupServiceIntern.h"
#include "RBSYS_MultiCoreSyncIntern.h"
#include "RBSYS_ClockSettings.h"
#include "RBSYS_ClockSettingsIntern.h"
#include "RBSYS_FPU.h"
#include "RBLCF_MemoryMap.h"
#include "RBSYS_CpuVersions.h"
#include "RBSYS_Intrinsics.h"
#include "../rtaos/src/RBSYS_OsConfig.h"      // for RBSYS_Os_AwaitStartup
#include "RBSYS_BBFSW_StartupServices.h"
#include "RBSYS_uCResetCtrl.h"
#include "RBSYS_uCResetInternal.h"
#include "RBSYS_uCResetInfo.h"
#include "RBSYS_CoreMpu.h"


/* realized interfaces */
#include "RBSYS_FSWStartup.h"
#include "RBSYS_GHS_ProgramStartup.h"
#include "RBSYS_PlantStartupCtrl.h"
#include "RBSYS_Subsystem.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysOverwriteEBASE,
                          RBFS_SysOverwriteEBASE_ON,
                          RBFS_SysOverwriteEBASE_OFF);

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

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWSVPRestrictions,
                          RBFS_TPSWSVPRestrictions_OFF,
                          RBFS_TPSWSVPRestrictions_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasP1xGRAM,
                          RBFS_RenesasP1xGRAM_ON,
                          RBFS_RenesasP1xGRAM_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_DataFlashECC,
                          RBFS_DataFlashECC_Disabled,
                          RBFS_DataFlashECC_Enabled);

RB_ASSERT_SWITCH_SETTINGS(RBFS_CompilationLanguage,
                          RBFS_CompilationLanguage_PureC,
                          RBFS_CompilationLanguage_PureCPP,
                          RBFS_CompilationLanguage_MixedCandCPP);

RB_ASSERT_SWITCH_SETTINGS(RBFS_CPUMisalignedAccessSupport,
                          RBFS_CPUMisalignedAccessSupport_ON,
                          RBFS_CPUMisalignedAccessSupport_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_BackupRAMLayout,
                          RBFS_BackupRAMLayout_Legacy,
                          RBFS_BackupRAMLayout_V1);

RB_ASSERT_SWITCH_SETTINGS(RBFS_ReprogDriverSupport,
                          RBFS_ReprogDriverSupport_ON,
                          RBFS_ReprogDriverSupport_OFF);


/******************************************************************************/
/* merge proc header includes                                                 */
/******************************************************************************/
/*ROOT_SECTION: HeaderIncludes_Root |#include "|" */
/*PROC_EP: HeaderIncludes */
/*ROOT_SECTION_END: */


static void RBSYS_StartupPreOSPhase1(void);
static void RBSYS_StartupPreOSPhase2(void);
static void RBSYS_StartupPreOSPhase3(void);


/**
 * @brief Start CPU1
 *
 * This interface triggers the start-up of CPU1.
 * Precondition: CPU1 must be enabled via FlashOption bytes
 *
 * @return void
 */
#if (RBFS_MCORE == RBFS_MCORE_ON)
/* Function shall not be inlined, because exit point is used for
 * breakpoint configuration within GHS debugger scripts */
static __attribute__((noinline)) void RBSYS_StartPE2(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

    RBSYS_BOOTCTRL |= RBSYS_BOOT_CPU1;

  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

    //todo: maybe only do this if core 1 not running yet
    //configure core 1 to reset on next mode change and set start address
    MC_ME_CL0.CoreReg.CADDR[1] = ((uint32)&FSWStart) | 0x1;
    //configure core 1 to run in DRUN
    MC_ME_CL0.CoreReg.CCTL[0] = 0x8u;  // This is CCTL1 (index 0), it comes before CCTL0 (index 1)

    //request mode change to DRUN
    RBSYS_ModeEntry_UpdateMode(RBSYS_ModeEntryModule_Domain0);

    // wait while mode transition is ongoing
    RBSYS_ModeEntry_WaitForStatus(RBSYS_ModeEntryModule_Domain0, 0x30130072u);

    //disable reset of core 1 on mode change
    MC_ME_CL0.CoreReg.CADDR[1] &= 0xFFFFFFFEu;

  #endif

  // Additionally, release other cores (may be auto-started due to limitation if Debugger is connected - will then be blocked in loop)
  RBSYS_MultiCoreSync_ReleaseCore1();
}
#endif



/* process tables for corresponding startup phase filled via MergeProc */
static void RBSYS_StartupProcs_PreCInit(void)
{
  /*ROOT_SECTION: SPG_PreCInit_Root | |(); */
  /*PROC_EP: SPG_PreCInit */
  /*ROOT_SECTION_END: */
}

static void RBSYS_StartupProcs_HostCycurHsmInit(void)
{
  /*ROOT_SECTION: SPG_HostCycurHsmInit_Root | |(); */
  /*PROC_EP: SPG_HostCycurHsmInit */
  /*ROOT_SECTION_END: */
}

static void RBSYS_StartupProcs_PreReprogCheck(void)
{
  /*ROOT_SECTION: SPG_PreReprogCheck_Root | |(); */
  /*PROC_EP: SPG_PreReprogCheck */
  /*ROOT_SECTION_END: */
}

static void RBSYS_StartupProcs_PrePlantCheck(void)
{
  /*ROOT_SECTION: SPG_PrePlantCheck_Root | |(); */
  /*PROC_EP: SPG_PrePlantCheck */
  /*ROOT_SECTION_END: */
}

#if(RBFS_ReprogDriverSupport == RBFS_ReprogDriverSupport_ON)
  static void RBSYS_StartupProcs_PreReprogSession(void)
  {
    /*ROOT_SECTION: SPG_PreReprogSession_Root | |(); */
    /*PROC_EP: SPG_PreReprogSession */
    /*ROOT_SECTION_END: */
  }
#endif

static void RBSYS_StartupProcs_Vx1000PreReprogSession(void)
{
  /*ROOT_SECTION: SPG_Vx1000PreReprogSession_Root | |(); */
  /*PROC_EP: SPG_Vx1000PreReprogSession */
  /*ROOT_SECTION_END: */
}

static void RBSYS_StartupProcs_Vx1000ParHandlingSession(void)
{
  /*ROOT_SECTION: SPG_Vx1000ParHandlingSession_Root | |(); */
  /*PROC_EP: SPG_Vx1000ParHandlingSession */
  /*ROOT_SECTION_END: */
}

static void RBSYS_StartupProcs_PreSafetyAlwaysExecute(void)
{
  /*ROOT_SECTION: SPG_RBSYS_PreSafetyAlwaysExecute_Root | |(); */
  /*PROC_EP: SPG_RBSYS_PreSafetyAlwaysExecute */
  /*ROOT_SECTION_END: */
}

static void RBSYS_StartupProcs_PreSafety(void)
{
  /*ROOT_SECTION: SPG_PreSafety_Root | |(); */
  /*PROC_EP: SPG_PreSafety */
  /*ROOT_SECTION_END: */
}

static void RBSYS_StartupProcs_SafetyC0(void)
{
  /*ROOT_SECTION: SPG_SafetyC0_Root | |(); */
  /*PROC_EP: SPG_SafetyC0 */
  /*ROOT_SECTION_END: */
}

#if (RBFS_MCORE == RBFS_MCORE_ON)
  static void RBSYS_StartupProcs_SafetyC1(void)
  {
    /*ROOT_SECTION: SPG_SafetyC1_Root | |(); */
    /*PROC_EP: SPG_SafetyC1 */
    /*ROOT_SECTION_END: */
  }
#endif

static void RBSYS_StartupProcs_PreOSStart(void)
{
  /*ROOT_SECTION: SPG_PreOSStart_Root | |(); */
  /*PROC_EP: SPG_PreOSStart */
  /*ROOT_SECTION_END: */
}

#if (RBFS_MCORE == RBFS_MCORE_ON)
  static void RBSYS_StartupProcs_PreOSStartC1(void)
  {
    /*ROOT_SECTION: SPG_PreOSStartC1_Root | |(); */
    /*PROC_EP: SPG_PreOSStartC1 */
    /*ROOT_SECTION_END: */
  }
#endif

/* messages for startup flow and OS mode decision */
RBMESG_DefineMESG(RBMESG_RBSYSPlantModeRequest);
/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_RBSYSPlantModeRequest*/
/*COMMENT=Sampled once at power up only*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/

// ToDo: check if explicit MT trigger is possible before or after SW reset
RBMESG_DefineMESG(RBMESG_RBSYSBaseOSRequestbySW_u32);
/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_RBSYSBaseOSRequestbySW_u32*/
/*COMMENT=Sampled once at power up only*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/


RBMESG_DefineMESG(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);
/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32*/
/*COMMENT=Copied once at power up only*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/


RBMESG_DefineMESG(RBMESG_RBSYSBaseOSbySW);
/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_RBSYSBaseOSbySW*/
/*COMMENT=BaseOS requested through SW trigger, set once at startup*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/

RBMESG_DefineMESG(RBMESG_RBSYSBaseOSActive);
/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_RBSYSBaseOSActive*/
/*COMMENT=System started in BaseOS mode, set once at startup*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/


#if(RBFS_ReprogDriverSupport == RBFS_ReprogDriverSupport_ON)
  /* Following concept is chosen for flash reprog session via RB diagnosis to
  * ensure that both cores are under control of the reprog driver:
  * In case of a flash reprog session, basic flash driver must be downloaded via
  * diagnosis service into DLM RAM (done in BaseOS). Afterwards a flash request is
  * written into Backup RAM and a SW reset is issued without RAM zeroing to keep
  * downloaded reprog driver still available. Project dependent configuration concerning
  * clocks must be known by the generic flash reprog driver, therefore following
  * interface is agreed between ECC6 (HSW) and ECC8 (responsible for reprog-driver)
  * for branching to reprog driver during our startup after SW reset with reprog request: */
  typedef void (*RBSYS_ReprogDriver_fptr_t)(uint32 cpu_clk, uint32 can_clk);
 #endif


static void startup_prc_calls(const PRC_PTR proc_table[])
{
  uint32 process_id = 0;
  while ( proc_table[process_id] != NULL )
  {
    proc_table[process_id]();
    process_id++;
  }
}


/*
@startuml
(*) --> "Initialize Core registers (General Purpose, Exception registers, Base Pointer, Core MPU, Cache)"
note right: Early startup is coded in ASM (to avoid local RAM accesses)
"Initialize Core registers (General Purpose, Exception registers, Base Pointer, Core MPU, Cache)" --> "Initialize Small Data Area registers"
"Initialize Small Data Area registers" --> "Initialize Core SPID"
"Initialize Core SPID" --> "Protect Local RAM Guards"
"Protect Local RAM Guards" --> "Protect Local RAM (+ allow Access from other Host Cores)"
"Protect Local RAM (+ allow Access from other Host Cores)" --> "Is Local RAM auto-zeroed and not used before"
if "Is Local RAM auto-zeroed and not used before"
  -right--> [no] "Clear Local RAM (zeroing)"
  "Clear Local RAM (zeroing)" --> Initialize Stack Pointer
else
  --> Initialize Stack Pointer
endif
note right: From now on, everything is coded in C

--> ===B1===
-[#blue]-> Initialize Clock Tree, PLLs
-[#blue]-> Initialize Peripheral SPIDs
-[#blue]-> Protect Global RAM Guards
-[#blue]-> Protect Global RAM
if "Is Global RAM auto-zeroed and not used before"
  -right[#blue]--> [no] "Clear Global RAM (zeroing)"
  -[#blue]-> Identify Reset Source (PowerOn, Terminal, SW Reset, ...)
else
  -[#blue]-> Identify Reset Source (PowerOn, Terminal, SW Reset, ...)
endif

-[#blue]-> ===B2===
===B1=== -[#red]-> ===B2===

--> Mask Interrupts, Fatal Error Interrupts
--> Configure Alignment Reaction

--> ===B3===
-[#blue]-> uC WTB Erratum fix, Instruction Cache handling (Emulation usecase)
-[#blue]-> ===B4===
===B3=== -[#red]-> ===B4===

--> Start other Cores
note right: Every other Core is started here (follow black and red line)

--> Synchronize Cores (0)

--> HW BIST evaluation (+ pattern test)

--> Initialize Stack Pointer'
note right: Stack is zeroed by HW BIST handling, but Stack Pointer is not updated
--> Synchronize Cores (1)

--> ===B5===
-[#blue]-> Initialize remaining Peripheral Guards (PBUS, HBUS, IBUS, INTC-Guards, DMA-Guard)
-[#blue]-> ===B6===
===B5=== -[#red]-> ===B6===

--> Synchronize Cores (2)
--> Call _start
--> Initialize Floating Point Unit

--> ===B7===
-[#blue]-> C++: Call Constructors
-[#blue]-> ===B8===
===B7=== -[#red]-> ===B8===

--> Synchronize Cores (3)

--> ===B9===
-[#blue]-> Identify Operation Mode (BaseOS / ControlMode)
-[#blue]-> Call HSM init processes (for Control Mode)
-[#blue]-> ===B10===
===B9=== -[#red]-> ===B10===

--> Initialize Exception Vector Base Address (EBASE)

--> CC-specific programming preperation (Vector, ReprogDriver, ...)

--> Synchronize Cores (4)

--> ===B11===
-[#blue]-> Restore BaseOS request
-[#blue]-> "PreSafetyAlwaysExecute: Configure basic ECM FEInt reaction"
-[#blue]-> ===B12===
===B11=== -[#red]-> ===B12===

--> Synchronize Cores (5)

if "BaseOS active?"
  note right: Skip Safety Tests in case of e.g. field return analysis
  -right--> [yes] RBSYS Failureword handling
else
  --> [no] ===B13===
  -[#blue]-> PreSafety: Configure ECM completely
  -[#blue]-> ===B14===
  ===B13=== -right[#red]-> ===B14===

  --> Synchronize Cores (6)

  --> ===B15===
  -[#blue]-> Safety Tests Core 0
  -[#blue]-> ===B16===

  ===B15=== -[#red]-> Safety Tests Core 1
  -[#red]-> ===B16===

  --> Synchronize Cores (7)
  --> Cleanup after Safety Tests (e.g. Clear FEIC)
  --> RBSYS Failureword handling
endif

--> Synchronize Cores (8)

--> Os_CacheCoreID
--> Os_InitializeVectorTable
--> ===B17===
-[#blue]-> Os_StartCore
-[#blue]-> ===B18===
===B17=== -[#red]-> Os_AwaitStartup
-[#red]-> ===B18===

--> Os_StartOS
--> (*)

legend top right
  | Arrow Color | Core  |
  |<#blue>      | 0     |
  |<#red>       | 1...n |
  |<#black>     | all   |
endlegend

@enduml
*/



RBSYS_ATTR_NO_PROLOGUE
__attribute__((noinline)) void RBSYS_StartupPreOSPhase0(void)
{
  /* START of "Do NOT use Local RAM" section: All functions inside this block must be always_inline, SP is not yet initialized ... */

  /* uC register initialization required independent of bootblock availability */
  RBSYS_registerInit();

  #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
    /* initialize Small Data Area (SDA) base registers (gp/tp) within Application context */
    RBSYS_SDA_registerInit();

    // Configure and activate core MPU restricting code execution to ROM only
    RBSYS_CoreMpu_Init();
  #endif


  /* P1x: Basic guard initialization must be done before PE2 (core1) is enabled via RBSYS_StartPE2().
   At least local RAM of PE1 (core0) must be opened for PE2, because Backup RAM belongs to that and
   is accessed during bootblock start-up */
  /* U2A: Basic guard initialization should be done before zeroing the RAM; todo: Protect CRAM before zeroing! */

  /// Set Own Core SPID -> Protect LRAM Guard -> Protect LRAM -> Clear LRAM
  RBSYS_BasicGuardInit();
  RBSYS_ClearLRAM();                /* LRAM Zeroing is performed under certain conditions only (see RBSYS_ClearLRAM) */

  /// Access to the Stack is restricted now -> Reinitialize Stack Pointer to default
  RBSYS_stackInit(RB_SP0_FSW, RB_SP1_FSW);

  /* END of   "Do NOT use Local RAM"  section: All functions inside this block must be always_inline, SP is not yet initialized ... */

  /* START of "Do NOT use Global RAM" section: All functions inside this block must not use global variables */
  /* ATTENTION: Core 0 is allowed to use GRAM because GRAM Zeroing is done from the same core. */

  if(RBSYS_getCoreID() == RBSYS_CORE_ID_0)
  {
    #if(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
      RBSYS_SetupClocks_RenesasU2A(); /* Ramp up Clock to be operated from PLL (if not done by hardware). Must be before start of TPTM (TPTM is based on CPU_CLK) */
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      RBSYS_SetWaitStatesForOperationAtLowSpeed();
      RBSYS_SetupPLLs(); /* Ramp up Clock to be operated from PLL. Must be before RBSYS_ClearGRAM */
      // todo: resort this, could be optimiyed by first configuring PLLs
      RBSYS_EnablePeripherals();
      RBSYS_DisableWatchdog();
      RBSYS_ConfigureResetReactions();
    #endif


    RBSYS_SetBusMasterIDs();        /* set the applicable IDs (e.g. Flexray, Ethernet etc.) to unsafe as precondition for below guard configuration. */
    RBSYS_GRAMGuardInit();          /* protect access to Global RAM Guards and to Global RAM itself */
    RBSYS_ClearGRAM();              /* Global RAM Zeroing is performed under certain conditions only (see RBSYS_ClearGRAM) */

    RBSYS_SetupPeripheralClocks();  /* Setup Peripheral frequencies */

    #if( RBFS_BackupRAMLayout == RBFS_BackupRAMLayout_V1 )
      RBSYS_BackupRAM_FSW_ResetFlagHandlingForRBECM();
    #endif

    // Cleanup Reset factors - when using RBSYS_isSWReset* APIs before, be aware of this clearing logic
    RBSYS_ClearResetFactorsAtStartup(); //< only needed for Application Stand-alone builds (else done within Bootblock already)
  }

  #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    RBSYS_OtherGuardsInit(); // Enable access to LLPP and Flash interface
  #endif

  RBSYS_StartupPreOSPhase1();
}


/* called when stacks are set-up by all PEs */
RBSYS_ATTR_NO_PROLOGUE
static __attribute__((noinline)) void RBSYS_StartupPreOSPhase1(void)
{
  unsigned int core_id = RBSYS_getCoreID();

  if( RBSYS_getCoreID() == RBSYS_CORE_ID_0 )
  {
    /* explicitly set Operation Mode to _PreInit here */
    RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_PreInit);
  }

  #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
    /* configure only ECM interrupts as FEINT ==> must be done before STM initialization */
    RBSYS_maskFEINT();

    /* Disable manually all interrupts to ensure that INTS are really locked during startup phase
      in case bootblock has wrongly enabled. Function to be executed on all cores */
    RBSYS_maskInts();
  #endif

  #if (RBFS_CPUMisalignedAccessSupport == RBFS_CPUMisalignedAccessSupport_ON)
    /* configure behaviour for misaligned r/w accesses - supported only on P1x */
    RBSYS_ConfigureAlignmentReaction();
  #endif

  if (core_id == RBSYS_CORE_ID_0)
  {
    #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
      /* SW workaround for RH850 Write Transaction Buffer limitation (see Renesas Errata RB113)
         Hint: It's important to call this function before PE2 and other bus masters are enabled
         (except ICUM) to avoid further synchronization (GRAM must not be accessed while disabling WT Buffer!). */
      RBSYS_WTBufErrataHandling();
    #endif

    #if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))
      /* configure clock tree to ensure cycle accurancy between production and emulation device */
      RBSYS_SetupClocks_RenesasP1x();
      RBSYS_DisableInstructionCache();
    #endif
  }

  /* STM must be initialized after masking FEINT */
  RBSYS_InitTimers();

  if( core_id == RBSYS_CORE_ID_0 )
  {
    #if (RBFS_MCORE == RBFS_MCORE_ON)
      /* due to current constraints it must be ensured that PE2 is started minimum 50us after PE1 */
      RBSYS_waitUsecLoop(50);

      /* enable here PE2 in case of MCore - only PE1 is required for real bootblock functionality, PE2 skips bootblock and jumps directly to FSW */
      RBSYS_StartPE2();
    #endif
  }

  #if (RBFS_MCORE == RBFS_MCORE_ON)
    /* Special workaround for multi core systems:
     * - Workaround for VLAB uC Simulation or connected GHS debugger, which may start all cores together
     *   independent of SW trigger via RBSYS_StartPE2(). Ensure that other cores wait until RBSYS_StartPE2() was called.
     * Hint: On U2A CRAM might not be initialized from Core 0 yet so all cores need to be synchronized here.
     */
    RBSYS_InitMultiCoreSync(); // must be called after RBSYS_BasicGuardInit which permit access to foreign local RAM
    RBSYS_StartupSyncBarrier(RBSYS_AfterStartPE2);
  #endif

  /* END of   "Do NOT use Global RAM" section: All functions inside this block must not use global variables */


  /* HWBIST Attention: Take care that only stack is initialized but no c_init
   *
   * 1st step: HWBIST (LBIST+MBIST) evaluation
   * 2nd step: SW pattern test in ASM only in case of memory faults detected by MBIST
   *
   * Tests are to be called individually on each core for LRAMs but on GRAM/CRAM tests can be called by any one of the cores.
   * The Test is destructive and has the possibility to corrupt the stack!
   *
   * SW pattern test must jump back from ASM to address given as parameter (RBSYS_StartupPreOSPhase2) due to possible destructive test of LRAM
   */
  {
    /*ROOT_SECTION: SPG_HWBistEval_Root | |(&RBSYS_StartupPreOSPhase2); */
    /*PROC_EP: SPG_HWBistInitialEvalAndSWPatternTest */
    /*ROOT_SECTION_END: */
  }

  RBSYS_StartupPreOSPhase2();
}

RBSYS_ATTR_NO_PROLOGUE
static __attribute__((noinline)) void RBSYS_StartupPreOSPhase2(void)
{
  // reset stack to initial values due possible destructive RAM test, which jumps hard to here ! invalid c-environment !
  RBSYS_stackInit(RB_SP0_FSW, RB_SP1_FSW);
  RBSYS_StartupPreOSPhase3();
}

/* called when stacks are set-up by all PEs */
RBSYS_ATTR_NO_PROLOGUE
static __attribute__((noinline)) void RBSYS_StartupPreOSPhase3(void)
{
  unsigned int core_id = RBSYS_getCoreID();

  #if (RBFS_MCORE == RBFS_MCORE_ON)
    /* RBSYS_InitMultiCoreSync() must be called a second time.
     * This second sync via registers is required because the HWBIST does not synchronize the cores after the (destructive) SW pattern test */
    RBSYS_InitMultiCoreSync();

    // from now on it is allowed to use MultiCoreSync feature via RBSYS_StartupSyncBarrier(phase)
    RBSYS_StartupSyncBarrier(RBSYS_AfterBootblock);
  #endif

  if(core_id == RBSYS_CORE_ID_0)
  {
    /** Initialize remaining PBUS guards after intialization of the RAM and when cores are in sync */
    RBSYS_EnhancedGuardInit();
  }

  #if( RBFS_MCORE == RBFS_MCORE_ON )
    /* cores must be synchronized here to assure that none of the cores is using the GRAM/CRAM while setting up the guards */
    RBSYS_StartupSyncBarrier(RBSYS_AfterGRAMGuardInit);
  #endif

  if (core_id == RBSYS_CORE_ID_0)
  {
    /* Core0: Loop through processes of PreCinit list */
    RBSYS_StartupProcs_PreCInit();

    RBSYS_SetStartupTimestamp(RBSYS_TimestampBeforeCinit);
  }

  // calls the GHS cinit routine which finally calls main function
  _start();
}


static volatile uint32 RBSYS_resetFlags4MM6;  /* variable only used for measurement, but neither it nor its assignment shall be optimized away */
/* used uC reset flags - see RBSYS_CpuInfo.h */

/*[[MEASUREMENT*/
/*NAME=RBSYS_resetFlags4MM6*/
/*COMMENT=Reset-information based on Reset-flags of uC*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/


/* -------------------------------------------------------------------------- */
/* QAC|DEV xxxx: main() function with 3 arguments (freestanding environment)  */
/* -------------------------------------------------------------------------- */
/* Msg 0601: Function 'main()' is not of type 'int (void)' or                 */
/*           'int (int, char *[])                                             */
/* In a freestanding environment the name and type of the function called     */
/* at program startup are implementation-defined. (according C Standard)      */
/* -------------------------------------------------------------------------- */
#ifdef __QAC__
  #pragma PRQA_MESSAGES_OFF 601
#endif

RBSYS_ATTR_NO_PROLOGUE
int main(int argc, char ** argv, char **envp)
{
  unsigned int core_id;

  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
  RBMESG_DefineMESGDef(RBMESG_RBSYSPlantModeRequest);
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSActive);

  core_id = RBSYS_getCoreID();

  /// Prepare Float Point Unit before _main (C++ constructors may use Floating Point instructions)
  RBSYS_InitFPU(); // initialize and activate core-specific Hardware Floating Point Unit (done on each core)

  #if( (RBFS_CompilationLanguage == RBFS_CompilationLanguage_PureCPP) \
    || (RBFS_CompilationLanguage == RBFS_CompilationLanguage_MixedCandCPP) )
    if( core_id == RBSYS_CORE_ID_0 )
    {
      _main(); // call C++ constructors from one core (Core 0)
    }
  #endif

  /* ensure that cinit has finished */
  /** Hint: from here on, C++ objects are initialized and may be used */
  RBSYS_StartupSyncBarrier(RBSYS_AfterCinit);

  if (core_id == RBSYS_CORE_ID_0)
  {
    RBSYS_SetStartupTimestamp(RBSYS_TimestampAfterCinit);
  }


  if (core_id == RBSYS_CORE_ID_0)
  {
    /* in case of SW reset recover message RBMESG_RBSYSBaseOSRequestbySW_u32 and RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32 from Backup RAM - reset Requester after retrieval */
    if (RBSYS_isSWResetByApplicationReset())
    {
      RBSYS_restoreBaseOSRequestFromBackupRAM();
      RBSYS_restoreSkipBootblockRequesterFromBackupRAM();
    }

    /* get info if reprog session was requested by software in last reset cycle (was recovered after RAM init) */
    RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);

    /** HSM will not be initialized if we have a reprog request:
     *    isSWReset && (ReprogRequestViaXCP || ReprogRequestViaDiag)
     *  Reason: HSM will block the reprogramming if it is already active    */
    if (!(RBSYS_isSWResetByApplicationReset() &&
          ( (l_RBMESG_RBSYSBaseOSRequestbySW_u32 == RBSYS_Vx1000ReprogRequested)
      #if(RBFS_ReprogDriverSupport == RBFS_ReprogDriverSupport_ON)
          ||(l_RBMESG_RBSYSBaseOSRequestbySW_u32 == RBSYS_ReprogRequest) )))
      #else
          )))
      #endif
    {
      /* Core0: Loop through processes of HostCycurHsmInit list */
      RBSYS_StartupProcs_HostCycurHsmInit();
    }
  }

  #if (RBFS_SysOverwriteEBASE == RBFS_SysOverwriteEBASE_ON)
    /* initialize EBASE before OS configuration to support uC safety startup test
     * due the assert handling to be called after cinit */
    RBSYS_InitEBASE((uint32)&FSWStart);
    /* Hint: Interrupts are disabled here - no DI necessary (BMGR will not activate interrupts) */
  #endif

  // setup ECP and execute processes of PreReprogCheck only on Core 0
  if (core_id == RBSYS_CORE_ID_0)
  {
    /* (re-)configure ECLK to default value (independent of bootblock), but activated after port initialization via RBPORT_PrcInit() */
    RBSYS_SetupECP(RBSYS_ECLK_DEFAULT_KHZ);

    /* Core0: Loop through processes of PreReprogCheck list */
    RBSYS_StartupProcs_PreReprogCheck();
  }

  /* sync barrier to ensure that Core1 has info if branch to reprog driver was requested */
  RBSYS_StartupSyncBarrier(RBSYS_ReprogDecision);

  /* get info if reprog session was requested by software in last reset cycle (was recovered after RAM init) */
  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);

  #if(RBFS_ReprogDriverSupport == RBFS_ReprogDriverSupport_ON)
    /*****************************************************************/
    /* flash re-programming session (via RB Diag) requested?         */
    /*****************************************************************/
    if (RBSYS_isSWResetByApplicationReset() && (l_RBMESG_RBSYSBaseOSRequestbySW_u32 == RBSYS_ReprogRequest))
    {
      RBSYS_ReprogDriver_fptr_t RBSYS_ReprogDriver = (RBSYS_ReprogDriver_fptr_t)RBLCF_getStartAddress_DLM_RAM();

      #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON))
        RBSYS_CoreMpu_AllowRamExecution();
      #endif

      /* Core0: Loop through processes of PreReprogSession list */
      RBSYS_StartupProcs_PreReprogSession();

      /* now branch to the ReprogDriver already available in DLM_RAM */
      RBSYS_ReprogDriver(RBSYS_CPU_CLK_KHZ, RBSYS_CAN_CLK_KHZ);

      /* Hint: ReprogDriver does not return here, it will trigger a System Reset 2 after successful flash re-programming */
    }
    else
  #endif
  /*****************************************************************/
  /* flash re-programming session (via VX1000) requested?         */
  /*****************************************************************/
  if (RBSYS_isSWResetByApplicationReset() && (l_RBMESG_RBSYSBaseOSRequestbySW_u32 == RBSYS_Vx1000ReprogRequested))
  {
    RBSYS_StartupProcs_Vx1000PreReprogSession();

    //----------------------------------------------------------------------------------------------------------------------------------------------
    // the execution of the code should not come to this location
    // only in case that the signalling between Vx1000 and ECU during reprog request handling failed;
    // thus Vx1000 could not taker over uC for what ever reason
    // => request BOS and if no diag session is requested within 500ms
    // do a SW reset to ControlMode
    //----------------------------------------------------------------------------------------------------------------------------------------------
    // Why going via BOS to ControlMode and not directly to ControlMode?
    // 1. VX1000 mailbox contains information to indicate "Ready for Reprog". At this point in time the VX1000 could
    //    interfere the system in a not predictable way. Thus going over BOS and via another SWReset to ControlMode to indicate VX1000
    //    a SWReset via Reset_Out and to re-init (clear) the Mailbox.
    // 2. Because the timing requirements for starting in ControlMode are violated at this point in time. Thus start to BOS and then
    //    ControlMode
    //----------------------------------------------------------------------------------------------------------------------------------------------

    RBSYS_requestBaseOSAfterSWReset();
  }
  /*****************************************************************/
  /* flash overlay handling via VX1000 requested?                  */
  /*****************************************************************/
  else if (RBSYS_isSWResetByApplicationReset() && (l_RBMESG_RBSYSBaseOSRequestbySW_u32 == RBSYS_Vx1000ParHandlingRequested))
  {
    // SW is comming from a SW reset
    // exec c_Vx1000ParHandlingSession then
    // boot in control mode and it is presumed that
    // control mode was active when the Flash overlay was requested => no change of OS mode
    // the rest of the overlay configuration has been done during vx1000 handshake
    // executedin this OS cycle before c_init

    RBSYS_StartupProcs_Vx1000ParHandlingSession();
  }
  else
  {
    /* all if … else if constructs shall be terminated with an else statement */
  }


  if (core_id == RBSYS_CORE_ID_0)
  {
    /* Core0: Loop through processes of PrePlantCheck list */
    RBSYS_StartupProcs_PrePlantCheck();

    /*************************************************************************/
    /* now decide which OS mode will start (normal operating mode or BaseOS) */
    /*************************************************************************/

    /* get info if BaseOS was requested by software in last reset cycle (was recovered after RAM init) */
    RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);

    if (RBSYS_isSWResetByApplicationReset() && (l_RBMESG_RBSYSBaseOSRequestbySW_u32 == RBSYS_BaseOSRequest))
    {
      /* BaseOS requested by SW */
      RBMESG_SendMESG(RBMESG_RBSYSBaseOSbySW, TRUE);
      RBMESG_SendMESG(RBMESG_RBSYSBaseOSActive, TRUE);

      /* reset SW request message */
      l_RBMESG_RBSYSBaseOSRequestbySW_u32 = RBSYS_DefaultOSRequest;
      RBMESG_SendMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
    }

    /* get info if ASIC detected plant mode request */
    RBMESG_RcvMESGDef(RBMESG_RBSYSPlantModeRequest);
    if (l_RBMESG_RBSYSPlantModeRequest)
    {
      /* BaseOS requested by ASIC */
      RBMESG_SendMESG(RBMESG_RBSYSBaseOSActive, TRUE);
    }


    /** ECM will not be configured for BaseOS, only FEInt for CoreSync during Reset will be enabled */
    RBSYS_StartupProcs_PreSafetyAlwaysExecute();
  }

  //sync barrier to ensure that Core1 get BaseOs decision - BaseOS decision will be handled completely by Core0
  RBSYS_StartupSyncBarrier(RBSYS_BaseOsDecision);

  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSActive);

  if (!l_RBMESG_RBSYSBaseOSActive) // safety etc. only in case of normal operating mode
  {
    if (core_id == RBSYS_CORE_ID_0)
    {
      RBSYS_SetStartupTimestamp(RBSYS_TimestampBeforeSafety);

      /* Core0: Loop through processes of PreSafety list*/
      RBSYS_StartupProcs_PreSafety();
    }

    //sync barrier to ensure that PreSafety on Core0 has finished before uC safety in general starts
    RBSYS_StartupSyncBarrier(RBSYS_BeforeSafety);

    if (core_id == RBSYS_CORE_ID_0)
    {
      /* Core0: Loop through processes of SafetyC0 list */
      RBSYS_StartupProcs_SafetyC0();
    }

    #if (RBFS_MCORE == RBFS_MCORE_ON)
      if (core_id == RBSYS_CORE_ID_1)
      {
        /* Core1: Loop through processes of SafetyC1 list */
        RBSYS_StartupProcs_SafetyC1();
      }
    #endif


    //sync barrier to ensure that complete uC safety has finished before calling processes of PreOSStart
    RBSYS_StartupSyncBarrier(RBSYS_BeforePreOS);

    #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
      // clear FEIC (FE level exception cause) register after uC safety start-up tests on each core
      RBSYS_ClearFEIC();
    #endif

    if (core_id == RBSYS_CORE_ID_0)
    {
      RBSYS_SetStartupTimestamp(RBSYS_TimestampAfterSafety);
    }


    if (core_id == RBSYS_CORE_ID_0)
    {
      RBSYS_resetFlags4MM6 = RBSYS_GetCurrentResetFlagsForMM6();

      if (!RBSYS_isSWResetTriggeredByFSW())
      {
          RBSYS_resetFlags4MM6 = (RBSYS_resetFlags4MM6 | 0x80000000u);  /* set highest Bit31 if SWreset was triggered by Bootblock */
      }

      /* Core0: Loop through processes of PreOSStart list */
      RBSYS_StartupProcs_PreOSStart();
    }

    #if (RBFS_MCORE == RBFS_MCORE_ON)
      if (core_id == RBSYS_CORE_ID_1)
      {
        /* Core1: Loop through processes of PreOSStartC1 list */
        RBSYS_StartupProcs_PreOSStartC1();
      }
    #endif
  }


  /*****************************************************************/
  /* Initial handling of RBSYS related failure words               */
  /*****************************************************************/
  if (core_id == RBSYS_CORE_ID_0)
  {
    if(!RBSYS_IsSYSErrorHookFailureReported())
    {
      /* Principle everything for interrupt and lock related aspects (failure word RBSYS_SYSErrorHook) is fine, before interrupt module is initialized at startup */
      RBSYS_setGoodCheckRequest(DemConf_DemEventParameter_RBSYS_SYSErrorHook);
    }

    /* Principle OS has no error by definition before it starts */
    RBSYS_setGoodCheckRequest(DemConf_DemEventParameter_RBSYS_OSErrorHook);
    RBSYS_setGoodCheckRequest(DemConf_DemEventParameter_RBSYS_TaskOverRun);
  }


  /* own sync mechanism is used to ensure efficient sync (wait loop done on local RAM)
   * from OS point no synchronization needed - done inside StartCore/StartOS
   */
  RBSYS_StartupSyncBarrier(RBSYS_BeforeOS);

  if (core_id == RBSYS_CORE_ID_0)
  {
    RBSYS_SetStartupTimestamp(RBSYS_TimestampBeforeOS);
  }

  #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    /* Stellar port of RTAOS caches core IDs in system registers that are accessible in user mode */
    Os_CacheCoreID();
  #endif

  /* Hint: EBASE (exception handler vector address register) is configured within OS directly to address 0x0 */
  Os_InitializeVectorTable();     // must be called on both cores!

  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  {
    uint32 ebase = RBSYS_STSR(RBSYS_EBASE_REGID, RBSYS_EBASE_SELID);
    assert( (ebase & RBSYS_EBASE_RINT_MASK) == 0x1u ); //< Table Reference Method should not be used for P1x due to a HW limitation, see Task 2783441 (RINT == 1)
  }
  #endif

  #if (RBFS_SysOverwriteEBASE == RBFS_SysOverwriteEBASE_ON)
    /* todo: see 1030656: [RBSYS] Increase SW quality - use linker label FSWStart within OS config for setting the EBASE */

    RBSYS_DI();                          // Disable Interrupts to set EBASE (see e.g. P1x UM V1.20 p.254)
    RBSYS_InitEBASE((uint32)&FSWStart);  // overwrite OS configuration and use directly application interrupt vector table instead of bootblock vector as EBASE
    RBSYS_EI();                          // Os_InitializeVectorTable will enable interrupts, thereby it's ok to enable the interrupts in any case
  #endif

  #if( RBFS_DataFlashECC == RBFS_DataFlashECC_Disabled )
    if (core_id == RBSYS_CORE_ID_0)
    {
      RBSYS_deactivateDataFlashECC();
    }
  #endif


  #if (RBFS_MCORE == RBFS_MCORE_ON)
    if (core_id == RBSYS_CORE_ID_0)
    {
      // call OS function StartCore from core 0
      StatusType status;
      StartCore(RBSYS_CORE_ID_0, &status);
      StartCore(RBSYS_CORE_ID_1, &status);
    }
    else
    {
      // Block Core until Master Core (0) is releasing it
      RBSYS_Os_AwaitStartup();
    }

  #endif

  /* start Operating System (jump to RBSYS_Dyn) -> never returns here */
  StartOS(OSDEFAULTAPPMODE);


  /* return statement unreachable (=> failure case) */
  return 1;

} /* end of main() */


#ifdef __QAC__
  #pragma PRQA_MESSAGES_ON 601
#endif


/**
 * @brief Clearing of microcontroller cold start reset flags
 *
 * This process clears the microcontroller cold start reset flags so
 * a reset occuring after this process will be considered to be a soft reset.
 *
 * Reset Flags serve as a trigger condition for SafetyTests and shall be cleared afterwards (to not execute SafetyTests
 * again) => Reset Flags are cleared only in Control Mode!
 *
 * @return void
 */
void RBSYS_PRC_ClearColdStartResetFlags(void)
{
  /* clear "Power-On" and "BIST" reset flags as indication that we passed this point within this power cycle (=> evaluated by uC Safety layer)  */
  /* Note: both must be cleared at the same time, due to uC-safety evaluation (see Epic 14871).                                                 */
  /* Note: SystemReset Flag has to be cleared - see defect 1070341                                                                              */
  RBSYS_ClearResetFactorsAfterSafetyTests();
}



/** @} */
/* End ingroup RBSYS */
