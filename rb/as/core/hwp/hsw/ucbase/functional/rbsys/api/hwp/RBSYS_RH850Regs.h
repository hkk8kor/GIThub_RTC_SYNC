#ifndef RBSYS_RH850REGS_H__
#define RBSYS_RH850REGS_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Renesas RH850 register definitions
 *
 * This interface export uC register definitions for RH850 provided by Renesas.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_Intrinsics.h"



/* Assert supported configurations: switches, parameters, constants, ... */
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
                          RBFS_TargetDevice_RenesasK1);

RB_ASSERT_SWITCH_SETTINGS(RBFS_EmulationDevice,
                          RBFS_EmulationDevice_None,
                          RBFS_EmulationDevice_RenesasD3ED,
                          RBFS_EmulationDevice_RenesasD5ED,
                          RBFS_EmulationDevice_RenesasD7ED,
                          RBFS_EmulationDevice_RenesasM6ED,
                          RBFS_EmulationDevice_RenesasK3ED);

RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasP1xGRAM,
                          RBFS_RenesasP1xGRAM_ON,
                          RBFS_RenesasP1xGRAM_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HSWSimulation,
                          RBFS_HSWSimulation_ON,
                          RBFS_HSWSimulation_OFF);


#if( RBFS_HSWSimulation == RBFS_HSWSimulation_OFF )
  /* -------------------------------------------------------------------------- */
  /* QAC|DEV xxxx: Header provided by Renesas                                   */
  /* -------------------------------------------------------------------------- */
  /* Msg 0660: Defining an unnamed member in a struct or union.                 */
  /*           This is a language extension.                                    */
  /* Msg 3410: Macro parameter not enclosed in ().                              */
  /* Msg 3621: Bit-fields are not allowed for Gen9/Gen9.3 code.                 */
  /* -------------------------------------------------------------------------- */
  #ifdef __QAC__
    #pragma PRQA_MESSAGES_OFF 660, 3410, 3621
  #endif


  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) \
    && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) )
    #include "dr7f701341.dvf.h"
  #endif

  #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2) \
    && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) \
      )
    #include "dr7f701337.dvf.h"
  #endif

  #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3)  \
    && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) \
      )
    #include "dr7f701328.dvf.h"
  #endif

  #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4)  \
    && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) \
      )
    #include "dr7f701327.dvf.h"
  #endif

  #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5)  \
    && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) \
      )
    #include "dr7f701326.dvf.h"
  #endif

  #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2) \
    && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) \
      )
    #include "dr7f702302i.dvf.h"
  #endif

  #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3) \
    && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) \
      )
    #include "dr7f702301ai.dvf.h"
  #endif

  #if ( ((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6))  \
    && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) \
      )
    #include "dr7f702300ai.dvf.h"
  #endif

  #if (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD3ED)
    #include "dr7f701334a.dvf.h"
  #endif

  #if (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD5ED)
    #include "dr7f701325a.dvf.h"
  #endif

  #if( (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD7ED) || (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasM6ED) )
    #include "dr7f702z19bi.dvf.h"
  #endif

  #if(RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasK3ED)
    #include "dr7f702600.dvf.h"
  #endif

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) 
    /** Product Info Area depends on SingleMap/DoubleMap mode (A or B is valid) */
    /** But: Valid Product Info (Front Page) is always mapped to 0x08030000     */
    #define PRDINFFPRDNAME1   FLASH_SCDS0PRDNAME1
    #define PRDINFFPRDNAME2   FLASH_SCDS0PRDNAME2
    #define PRDINFFPRDNAME3   FLASH_SCDS0PRDNAME3
    #define PRDINFFPRDNUM     FLASH_SCDS0PRDNUM
  #endif


  #ifdef __QAC__
    #pragma PRQA_MESSAGES_ON 660, 3410, 3621
  #endif

  /** @brief DBG_STUP — Startup Register
   *
   * Startup register provides given information from external debugging device to the CPU.
   *
   * The DBG_STUP register is core-specific, which means that the register exists for each
   * core and
   * - only the core could read his own register at address 0xFA002078 (P1x).
   * - every core can read core0's register at address 0xF9012078 (U2A).
   *
   * So this register is used in our CC-AS environment to identify an active debugger session.
   * Therefore it's necessary that each connected debugger writes a predefined value to DBG_STUP.
   * This value will be used to skip the LBIST & MBIST evaluation in our software. This is necessary,
   * because the HW BIST will be skipped in case of a connected debugger.
   *
   * @note This register can be read by 32 bits from the CPU, but write access is disabled.
   */
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
    #define DBG_STUP                (*(volatile uint32 *)0xFA002078)
  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    #define DBG_STUP                (*(volatile uint32 *)0xF9012078) //< this is related to core0
  #endif

  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    /* EPC = Emulation Peripheral Control (Unit) 
     * EPC_SVSTOP => EPC register for peripheral break control of WDTBA */
    /* todo: provide via device header file */
    #define EPC_SVSTOP58_ADDR            0xFF0B00EC
  #endif

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    /**
     * @brief The following macros are used to determine the erease counters of the system's Program Flash (Code flash).
     * For more information @see Renesas documenation of "RH850/P1x-C" chapter "33.31 Erase Counter".
     *
     * @brief VALID_FLAG_PFLASH_BANK_A_PU32 — 32 bit regsiter which define that rather area 0
     * or area 1 of bank A contains the valid erase counters. If the register contains the value 5AA5A55A,
     * area 1 is valid. Otherwise area 0 is valid.
     *
     * @brief VALID_FLAG_PFLASH_BANK_B_PU32 — 32 bit regsiter which define that rather area 0
     * or area 1 of bank B contains the valid erase counters. If the register contains the value 5AA5A55A,
     * area 1 is valid. Otherwise area 0 is valid.
     *
     * @brief ERASE_COUNTER_OFFSET_AREA0 — Offset for the first Erease Counter of AREA 0
     *
     * @brief ERASE_COUNTER_OFFSET_AREA1 — Offset for the first Erease Counter of AREA 1
     *
     * @brief PFLASH_A_ERASE_COUNTER_AREA0_PU16 — Start address of the first Erease Counter in bank A at AREA 0
     *
     * @brief PFLASH_A_ERASE_COUNTER_AREA1_PU16 — Start address of the first Erease Counter in bank A at AREA 1
     *
     * @brief PFLASH_B_ERASE_COUNTER_AREA0_PU16 — Start address of the first Erease Counter in bank B at AREA 0
     *
     * @brief PFLASH_B_ERASE_COUNTER_AREA1_PU16 — Start address of the first Erease Counter in bank B at AREA 1
     */
    #define VALID_FLAG_PFLASH_BANK_A_PU32 ((uint32 volatile *)0xFF200000)
    #define VALID_FLAG_PFLASH_BANK_B_PU32 ((uint32 volatile *)0xFF300000)

    #define ERASE_COUNTER_OFFSET_AREA0   0x00000040
    #define ERASE_COUNTER_OFFSET_AREA1   0x00000180

    #define AREA_1_IS_VALID 0x5AA5A55A

    #define PFLASH_A_ERASE_COUNTER_AREA0_PU16 ((uint16 volatile *) (0xFF200000 + ERASE_COUNTER_OFFSET_AREA0))
    #define PFLASH_A_ERASE_COUNTER_AREA1_PU16 ((uint16 volatile *) (0xFF200000 + ERASE_COUNTER_OFFSET_AREA1))
    #define PFLASH_B_ERASE_COUNTER_AREA0_PU16 ((uint16 volatile *) (0xFF300000 + ERASE_COUNTER_OFFSET_AREA0))
    #define PFLASH_B_ERASE_COUNTER_AREA1_PU16 ((uint16 volatile *) (0xFF300000 + ERASE_COUNTER_OFFSET_AREA1))
  #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    /**
     * @brief The following macros are used to determine the erease counters of the system's Program Flash (Code flash).
     * For more information @see Renesas documenation of "RH850/U2A-EVA Group" chapter "51.15 Erase Counter Area".
     *
     * @brief VALID_FLAG_PFLASH_BANK_A_PU32 — 32 bit regsiter which define that rather area 0
     * or area 1 of bank A contains the valid erase counters. If the register contains the value 5AA5A55A,
     * area 1 is valid. Otherwise area 0 is valid.
     *
     * @brief VALID_FLAG_PFLASH_BANK_B_PU32 — 32 bit regsiter which define that rather area 0
     * or area 1 of bank B contains the valid erase counters. If the register contains the value 5AA5A55A,
     * area 1 is valid. Otherwise area 0 is valid.
     *
     * @brief ERASE_COUNTER_OFFSET_AREA0 — Offset for the first Erease Counter of AREA 0
     *
     * @brief ERASE_COUNTER_OFFSET_AREA1 — Offset for the first Erease Counter of AREA 1
     *
     * @brief PFLASH_0_ERASE_COUNTER_AREA0_PU16 — Start address of the first Erease Counter in bank 0 at AREA 0
     *
     * @brief PFLASH_0_ERASE_COUNTER_AREA1_PU16 — Start address of the first Erease Counter in bank 0 at AREA 1
     *
     * @brief PFLASH_1_ERASE_COUNTER_AREA0_PU16 — Start address of the first Erease Counter in bank 1 at AREA 0
     *
     * @brief PFLASH_1_ERASE_COUNTER_AREA1_PU16 — Start address of the first Erease Counter in bank 1 at AREA 1
     *
     * @brief PFLASH_2_ERASE_COUNTER_AREA0_PU16 — Start address of the first Erease Counter in bank 2 at AREA 0
     *
     * @brief PFLASH_2_ERASE_COUNTER_AREA1_PU16 — Start address of the first Erease Counter in bank 2 at AREA 1
     *
     * @brief PFLASH_3_ERASE_COUNTER_AREA0_PU16 — Start address of the first Erease Counter in bank 3 at AREA 0
     *
     * @brief PFLASH_3_ERASE_COUNTER_AREA1_PU16 — Start address of the first Erease Counter in bank 3 at AREA 1
     */
    #define VALID_FLAG_PFLASH_BANK_0_PU32 ((uint32 volatile *)0xFF325000)
    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      #define VALID_FLAG_PFLASH_BANK_1_PU32 ((uint32 volatile *)0xFF326800)
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      #warning("Check if this does not exist for U2C"); // todo
    #endif

    #define ERASE_COUNTER_OFFSET_AREA0   0x00000800
    #define ERASE_COUNTER_OFFSET_AREA1   0x00001000

    #if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6))
        #define VALID_FLAG_PFLASH_BANK_2_PU32 ((uint32 volatile *)0xFF341000)
        #define VALID_FLAG_PFLASH_BANK_3_PU32 ((uint32 volatile *)0xFF342800)
    #endif

    #define AREA_1_IS_VALID 0x5AA5A55A

    #define PFLASH_0_ERASE_COUNTER_AREA0_PU16 ((uint16 volatile *) (0xFF325000 + ERASE_COUNTER_OFFSET_AREA0))
    #define PFLASH_0_ERASE_COUNTER_AREA1_PU16 ((uint16 volatile *) (0xFF325000 + ERASE_COUNTER_OFFSET_AREA1))
    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      #define PFLASH_1_ERASE_COUNTER_AREA0_PU16 ((uint16 volatile *) (0xFF326800 + ERASE_COUNTER_OFFSET_AREA0))
      #define PFLASH_1_ERASE_COUNTER_AREA1_PU16 ((uint16 volatile *) (0xFF326800 + ERASE_COUNTER_OFFSET_AREA1))
    #endif

    #if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6))
        #define PFLASH_2_ERASE_COUNTER_AREA0_PU16 ((uint16 volatile *) (0xFF341000 + ERASE_COUNTER_OFFSET_AREA0))
        #define PFLASH_2_ERASE_COUNTER_AREA1_PU16 ((uint16 volatile *) (0xFF341000 + ERASE_COUNTER_OFFSET_AREA1))
        #define PFLASH_3_ERASE_COUNTER_AREA0_PU16 ((uint16 volatile *) (0xFF342800 + ERASE_COUNTER_OFFSET_AREA0))
        #define PFLASH_3_ERASE_COUNTER_AREA1_PU16 ((uint16 volatile *) (0xFF342800 + ERASE_COUNTER_OFFSET_AREA1))
    #endif
  #else
    #error "Erase Counter not realized for current uCFamily."
  #endif


  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )

    /**
     * @brief The following macros are used to access undocumented locations for further info in case of Guard events.
     */
    /* debug infos for GRAM Guard events (undocumented registers) */
    #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
      #define MGDGRSLOCATION_VCI2GRAM    (*(const volatile uint32 *)0xFFC49108)
      #define MGDGRSLOCATION_PE1         (*(const volatile uint32 *)0xFFC49208)
      #if(RBFS_MCORE == RBFS_MCORE_ON)
        #define MGDGRSLOCATION_PE2         (*(const volatile uint32 *)0xFFC49308)
      #endif
      #define MGDGRSLOCATION_AXI2GRAM    (*(const volatile uint32 *)0xFFC49708)
    #endif

    /* debug infos for Slave Guard events (undocumented registers) */
    #define ERRSLV1LOCATION            (*(const volatile uint32  *)0xFFEE0108) /* ERRSLV1 */
    #define ERRSLV1AILOCATION          (*(const volatile uint32  *)0xFFEE0808) /* ERRSLV1AI */
    #define ERRSLV2LOCATION            (*(const volatile uint32  *)0xFFDDD108) /* ERRSLV2 */
    #define ERRSLV2AILOCATION          (*(const volatile uint32  *)0xFFDDD808) /* ERRSLV2AI */
    #define ERRSLV3LOCATION            (*(const volatile uint32  *)0xFFF94108) /* ERRSLV3 */
    #define ERRSLV3AILOCATION          (*(const volatile uint32  *)0xFFF94808) /* ERRSLV3AI */
    #define ERRSLV4LOCATION            (*(const volatile uint32  *)0xFFF90108) /* ERRSLV4 */
    #define ERRSLV4AILOCATION          (*(const volatile uint32  *)0xFFF90808) /* ERRSLV4AI */
    #define ERRSLV5ALOCATION           (*(const volatile uint32  *)0xFFC5A108) /* ERRSLV5A */
    #define ERRSLV5AILOCATION          (*(const volatile uint32  *)0xFFC5A808) /* ERRSLV5AI */
    #define ERRSLVHILOCATION           (*(const volatile uint32  *)0xFFFA0138) /* ERRSLVHI */
    #define ERRSLVPBAREALOCATION       (*(const volatile uint32  *)0xFFC4C888) /* ERRSLVPBAREA */
    #define ERRSLVPFSS0LOCATION        (*(const volatile uint32  *)0xFFC4C808) /* ERRSLVPFSS0 */
    #define ERRSLVPFSS1LOCATION        (*(const volatile uint32  *)0xFFC4C818) /* ERRSLVPFSS1 */


    #if ( (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2) )
      #define ERRSLV4CLOCATION           (*(const volatile uint32  *)0xFFF90508) /* ERRSLV4C */
      #define ERRSLV5BLOCATION           (*(const volatile uint32  *)0xFFC5A308) /* ERRSLV5B */
      #define ERRSLV5CLOCATION           (*(const volatile uint32  *)0xFFC5A508) /* ERRSLV5C */
      #define ERRSLV5DLOCATION           (*(const volatile uint32  *)0xFFC5A708) /* ERRSLV5D */
      #define ERRSLV5BILOCATION          (*(const volatile uint32  *)0xFFC5A908) /* ERRSLV5BI */
      #define ERRSLVDG0LOCATION          (*(const volatile uint32  *)0xFFC5AE08) /* ERRSLVDG0 */
      #define ERRSLVDG1LOCATION          (*(const volatile uint32  *)0xFFC5AF08) /* ERRSLVDG1 */
      #define ERRSLVE0LOCATION           (*(const volatile uint32  *)0xFFFA0058) /* ERRSLVE0 */
      #define ERRSLVF0LOCATION           (*(const volatile uint32  *)0xFFFA0018) /* ERRSLVF0 */

      #if (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD3)
        /* these registers are not present on D3 (and also not on D4_BGA-156 - which we currently do not have; once we would get this device-type a runtime-if would have to be added) */
        #define ERRSLVE1LOCATION           (*(const volatile uint32  *)0xFFFA0078) /* ERRSLVE1 */
        #define ERRSLVF1LOCATION           (*(const volatile uint32  *)0xFFFA0038) /* ERRSLVF1 */
        #define ERRSLVM0LOCATION           (*(const volatile uint32  *)0xFFFA00D8) /* ERRSLVM0 */
      #endif

      #define ERRSLVEILOCATION           (*(const volatile uint32  *)0xFFFA0118) /* ERRSLVEI */
      #define ERRSLVFILOCATION           (*(const volatile uint32  *)0xFFFA0108) /* ERRSLVFI */
      #define ERRSLVMILOCATION           (*(const volatile uint32  *)0xFFFA0128) /* ERRSLVMI */
      #define ERRSLVXILOCATION           (*(const volatile uint32  *)0xFFFA0148) /* ERRSLVXI */
    #endif

    /**
      * @brief Write protection unlock sequence
      *
      * Write access to a write protected register is only possible within a special protection unlock sequence,
      * which is provided via this macro. This protection mechanism is introduced to protected registers from
      * inadvertent write access. In case the protection unlock sequence is interrupted, the protection
      * unlock sequence will be repeated - therefore no lock mechanism is required.
      *
      * @param [out] PCMD   protection command register
      * @param [in]  PSTAT  protection status register
      * @param [out] REG    protected register
      * @param [in]  VAL    register value
      */
    #define WPROT(PCMD, PSTAT, REG, VAL) \
    do {                                 \
      (PCMD) = 0xA5u;                    \
      (REG) = (VAL);                     \
      (REG) = ~(VAL);                    \
      (REG) = (VAL);                     \
    } while(((PSTAT) & 0x01u)!= 0)

  #endif   /* P1x-family */

  #if(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
    /** Key Code Protection commands - This functionality is used for multiple modules inside U2A */

    /**
      * @brief Enable Access to HW Modules / Unlock Key Code Protection for HW Modules
      *
      * KeyCode Protection register is passed as an argument. After calling this function, you can directly access
      * the protected registers. This interface may only be used on KeyCode-Protection registers (e.g. ...KCPROT).
      *
      * Hint: KeyCodeProtection is only used on U2A devices
      *
      * @param KeyCodeProtectionRegister Pointer to the KeyCode Protection Registers
      *
      * @return void
      */
    __attribute__((always_inline)) static inline void RBSYS_UnlockAccessToHwModule(volatile uint32* KeyCodeProtectionRegister)
    {
      *KeyCodeProtectionRegister = 0xA5A5A501u; //< Unlock KC protection
      RBSYS_SYNCM();                            //< Ensure completion of previous write instruction to KCPROT register
    }

    /**
      * @brief Disable Access to HW Modules / Lock Key Code Protection for HW Modules
      *
      * KeyCode Protection register is passed as an argument. After calling this function, you cannot access
      * the protected registers anymore. This interface may only be used on KeyCode-Protection registers (e.g. ...KCPROT).
      *
      * Hint: KeyCodeProtection is only used on U2A devices
      *
      * @param KeyCodeProtectionRegister Pointer to the KeyCode Protection Registers
      *
      * @return void
      */
    __attribute__((always_inline)) static inline void RBSYS_LockAccessToHwModule(volatile uint32* KeyCodeProtectionRegister)
    {
      RBSYS_SYNCM();                            //< Ensure completion of all previous write instructions before locking
      *KeyCodeProtectionRegister = 0xA5A5A500u; //< Lock KC protection
      RBSYS_SYNCM();                            //< Ensure completion of previous write instruction to KCPROT register
    }

    typedef struct{
      uint32 PROT0;
      uint32 PROT1;
    } RBSYS_BARRBRG_t;

    #define RBSYS_BARRBRG ((volatile RBSYS_BARRBRG_t *)(0xFFC6A000u + 0x80u))

    #define RBSYS_INTC2INTC2GPROT_n ((volatile uint32 *)(0xFFC64100u))

    #define RBSYS_DMAC0DMAGPROT_n ((volatile uint32 *)(0xFFC69000u + 0x100u))
    #define RBSYS_DMAC1DMAGPROT_n ((volatile uint32 *)(0xFFC69400u + 0x100u))
    #define RBSYS_DTSDTSGPROT_n   ((volatile uint32 *)(0xFFC68100u))

    /* The following macro is used to access Option Bytes */
    #define RBSYS_CSAf_base (0xFF320800u)
  #endif


  /* ensure same register name of RESF/RESFC on P1x and U2A) */
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    #define RBSYS_RESF        (RESF)
    #define RBSYS_RESFC       (RESFC)
  #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    #define RBSYS_RESF        (SYSCTRLRESF)
    #define RBSYS_RESFC       (SYSCTRLRESFC)
  #endif

  /* ensure same register name of BOOTCTRL on P1x and U2A) */
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    #define RBSYS_BOOTCTRL    (BOOTCTRL)
  #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    #define RBSYS_BOOTCTRL    (SYSCTRLBOOTCTRL)
  #endif


  /* PEGuard Addresses for ASM Macro use (access width 32bit allowed for all registers) */
  #define RBSYS_ADDR_PEGG0MK 0xFFFEE680
  #define RBSYS_ADDR_PEGG0SP 0xFFFEE688
  #define RBSYS_ADDR_PEGG0BA 0xFFFEE684
  #define RBSYS_ADDR_PEGG1MK 0xFFFEE690
  #define RBSYS_ADDR_PEGG1SP 0xFFFEE698
  #define RBSYS_ADDR_PEGG1BA 0xFFFEE694

  /* PBUS Guard Addresses for ASM macro use (access width 32bit allowed for all registers) */
  #define RBSYS_ADDR_FSGD3ASPID03 0xFFF9401C
  #define RBSYS_ADDR_FSGD3APROT03 0xFFF94018

  /** U2A: This register definition is according to "Renesas U2A Hardware User Manual R01UH0820EJ0110 Rev.1.10" */

#else
  #include "RBSYSStub_RH850Regs.h"
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
