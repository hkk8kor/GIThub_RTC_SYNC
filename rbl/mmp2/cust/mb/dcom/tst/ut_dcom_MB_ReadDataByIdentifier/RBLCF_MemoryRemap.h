/* ************************************************************************** *
 *
 *  Copyright (c) 2018 Robert Bosch GmbH, Germany
 *  All rights reserved.
 *
 * ************************************************************************** */

/* dcom_PLATF_ReadWriteDataByIdentifier.h
 *
 * Description:
 *    <This header files provide macros and variable definitions for the Platform DIDs>
 *
 * Author: uds3kor
 */

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/

/*
uint32 DCOM_BOOTLOADER_ADDRESS_STUBBED[1];
#define DCOM_BOOTLOADER_ADDRESS  DCOM_BOOTLOADER_ADDRESS_STUBBED
#define DCOM_APPLICATION_ENDADDRESS     0x001D7FFFU
*/

dcom_BootHeader_tst *DCOM_BOOTLOADER_ADDRESS_STUBBED;
dcom_BootHeader_tst *DCOM_APPLICATION_ENDADDRESS_STUBBED;

#define DCOM_BOOTLOADER_ADDRESS  &DCOM_BOOTLOADER_ADDRESS_STUBBED
#define DCOM_APPLICATION_ENDADDRESS     DCOM_APPLICATION_ENDADDRESS_STUBBED
/*
**********************************************************************************************************************
* Enumeration definitions
**********************************************************************************************************************
*/


/*
**********************************************************************************************************************
* Variables
**********************************************************************************************************************
*/

#ifndef RBLCF_MEMORYREMAP_H__
#define RBLCF_MEMORYREMAP_H__

/**
 * @ingroup RBLCF
 * @{
 *
 * @file
 * @brief Remapping of linker sections
 *
 * Due to the fact that code in general should be compiler suite independent, the remapping of linker sections
 * (which depends on compiler/linker syntax) will be abstracted for the platform within this interface.
 *
 *
 * @note
 * Abbreviations & Definitions:\n\n
 * BB       - Bootblock\n
 * BMGR     - Bootmanager\n
 * BLDR     - Bootloader\n
 * CAL      - Calibration Block\n
 * CSW      - Complete Software\n
 * FSW      - Functional Software Block\n
 * HexBlock - Defined part of a hexfile; a hexfile contains 1-n complete memory segments of current device\n
 * HSW      - Hardware Related Software\n
 * HSM      - Hardware Security Module (Renesas implementation of the HSM is called ICU-M => Intelligent Cryptographic Unit - Master)\n
 * LCF      - Linker Command File -> now Linker Directive File (*.ld)\n
 * LD       - Linker Directive File (*.ld) -> former Linker Command File\n
 * MTC      - Make Tool Chain\n
 * PSW      - Platform Software\n
 * RBBLDR   - Robert Bosch Bootloader\n
 * SCM      - Software Configuration Management\n
 * SDA      - Small Data Area compiler optimization\n
 * TSI      - Test and Service Interface\n
 * TPSW     - Third Party Software\n
 * uC       - Microcontroller\n
 *
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBLCF_Config.h"


/* used interfaces */

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_Bootblock,
                          RBFS_Bootblock_Enabled,
                          RBFS_Bootblock_Disabled);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HardwareSecurityModule,
                          RBFS_HardwareSecurityModule_Supported,
                          RBFS_HardwareSecurityModule_Unsupported);

RB_ASSERT_SWITCH_SETTINGS(RBFS_EmulationDevice,
                          RBFS_EmulationDevice_None,
                          RBFS_EmulationDevice_RenesasD3ED,
                          RBFS_EmulationDevice_RenesasD5ED,
                          RBFS_EmulationDevice_RenesasD7ED);

RB_ASSERT_SWITCH_SETTINGS(RBFS_LocalRamCore1Support,
                          RBFS_LocalRamCore1Support_ON,
                          RBFS_LocalRamCore1Support_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_LocalRamCore2Support,
                          RBFS_LocalRamCore2Support_ON,
                          RBFS_LocalRamCore2Support_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_LocalRamCore3Support,
                          RBFS_LocalRamCore3Support_ON,
                          RBFS_LocalRamCore3Support_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_GlobalRamSupport,
                          RBFS_GlobalRamSupport_ON,
                          RBFS_GlobalRamSupport_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_ClusterRam0Support,
                          RBFS_ClusterRam0Support_ON,
                          RBFS_ClusterRam0Support_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_ClusterRam1Support,
                          RBFS_ClusterRam1Support_ON,
                          RBFS_ClusterRam1Support_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_ClusterRam2Support,
                          RBFS_ClusterRam2Support_ON,
                          RBFS_ClusterRam2Support_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_ClusterRam3Support,
                          RBFS_ClusterRam3Support_ON,
                          RBFS_ClusterRam3Support_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RBBootloader,
                          RBFS_RBBootloader_Yes,
                          RBFS_RBBootloader_No);

RB_ASSERT_SWITCH_SETTINGS(RBFS_OEMBootloader,
                          RBFS_OEMBootloader_Yes,
                          RBFS_OEMBootloader_No);

// so far the PREMIUM configuration is not supported!
RB_ASSERT_SWITCH_SETTINGS(RBFS_FOTA,
                          RBFS_FOTA_OFF,
                          RBFS_FOTA_BASE,
                          RBFS_FOTA_BASEPLUS,
                          RBFS_FOTA_ENHANCED);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A);


/* The GHS syntax for assigning data to custom sections in C language is:
   #pragma ghs section [secttype="sectname"]

   Hint: The C99 _Pragma preprocessing operator is also accepted


   -------------------------------------------------------------------------
   | secttype  | Default Section | Description                             |
   -------------------------------------------------------------------------
   | bss       | .bss            | zero initialized data                   |
   | data      | .data           | explicitly initialized data             |
   | text      | .text           | program code area                       |
   | rodata    | .rodata         | constant data                           |
   | sbss      | .sbss           | zero initialized data in SDA area       |
   | sdata     | .sdata          | explicitly initialized data in SDA area |
   | rosdata   | .rosdata        | constant data in SDA area               |
   -------------------------------------------------------------------------

   To be compiler independent within our software the raw pragma directive
   should not be used. Therefore this interface provides an abstraction of
   the compiler syntax for section assignment.

   Please take care, assigning data to custom specific sections
   (e.g. 3rd party software or code generators) must always consider the
   Small Data Area (SDA) optimization.

   If the SDA optimization is enabled the compiler re-allocates data from
   the primary sections to the equivalent SDA sections:

   ---------------------------------------------
   | primary section | equivalent SDA section  |
   ---------------------------------------------
   | .bss            | .sbss                   |
   | .data           | .sdata                  |
   | .rodata         | .rosdata                |
   ---------------------------------------------

   This special SDA sections can be accessed by using an offset from a base address.
   The offset is either 16 or 23-bit and a signed value. Therefore the base pointers
   are normally placed in the middle of the SDA related sections. By default SDA can
   address 64 KB (+/- 32kB) of data (16-bit). With the compiler option -large_sda
   8MB (+/- 4 MB) could be addressed (23-bit). In most cases, data in this block can
   be accessed more efficiently than other data using for example absolute addressing.

   But to be independent of the SDA setting specified by our MTC and possible future
   changes respectively there are two options how to re-allocate symbols:

   -------------------------------------------------------------------------------------

    Option 1 (preferred solution):

      Exclude in general data from SDA area and use only the default section for re-
      mapping. But take care that the declaration must be considered in this case.
      This means you need for the definition the #pragma ghs startdata / enddata
      together with the #pragma ghs section directive and in addition for the
      declaration the #pragma ghs startdata / enddata.

      Hint: A #pragma ghs section directive on a declaration has no effect => it will be ignored

      Example:

        h-file:
          #pragma ghs startdata
          extern int foo_a;
          extern int foo_b;
          extern const int foo_c;
          #pragma ghs enddata

        c-file:
          #pragma ghs startdata                       // exclude data from SDA (Small Data Area)
          #pragma ghs section data =".my_data"        // assign explicitly initialized data into .my_data
          int foo_a = 4;
          #pragma ghs section data = default
          #pragma ghs enddata                         // from now on go back to default allocation rules

          #pragma ghs startdata                       // exclude data from SDA (Small Data Area)
          #pragma ghs section bss =".my_bss"           // assign zero initialized data into .my_bss
          int foo_b;
          #pragma ghs section bss = default
          #pragma ghs enddata                         // from now on go back to default allocation rules

          #pragma ghs startdata                       // exclude data from SDA (Small Data Area)
          #pragma ghs section rodata =".my_rodata"    // assign constant data into .my_rodata
          const int foo_c;
          #pragma ghs section rodata = default
          #pragma ghs enddata                         // from now on go back to default allocation rules

    !!! Please use the provided macros below and don't use the pragmas directly within your code !!!
    Using the pragma statements directly is not MISRA compliant!

    Advantage:    - Equivalent SDA section do not need to be considered within linker directive file
                  - Memory allocation within linker directive file is independent of RAM/ROM SDA base register

    Disadvantage: - Each declaration must be considered for re-allocated symbols and requires the #pragma directive

   -------------------------------------------------------------------------------------

    Option 2:

      Re-allocate always primary section together with equivalent SDA section like in the
      below example

        h-file:
          extern int foo_a;
          extern int foo_b;
          extern const int foo_c;

        c-file:
          #pragma ghs section data  =".my_data"       // assign explicitly initialized data into .my_data
          #pragma ghs section sdata =".my_sdata"      // assign explicitly initialized data into .my_sdata
          int foo_a = 4;
          #pragma ghs section sdata = default
          #pragma ghs section data  = default         // from now on go back to default allocation rules

          #pragma ghs section bss  =".my_bss"         // assign zero initialized data into .my_bss
          #pragma ghs section sbss =".my_sbss"        // assign zero initialized data into .my_sbss
          int foo_b;
          #pragma ghs section sbss = default
          #pragma ghs section bss  = default          // from now on go back to default allocation rules

          #pragma ghs section rodata =".my_rodata"    // assign constant data into .my_rodata
          #pragma ghs section rosdata =".my_rosdata"  // assign constant data into .my_rodata
          const int foo_c;
          #pragma ghs section rosdata = default
          #pragma ghs section rodata = default        // from now on go back to default allocation rules

    !!! Please use the provided macros below and don't use the pragmas directly within your code !!!
        Using the pragma statements directly is not MISRA compliant!

    Advantage:    - Only the definition requires the #pragma directive and the declaration do not need to be considered

    Disadvantage: - Requires always two different user sections within linker directive file
                  - Memory allocation is dependent of RAM/ROM SDA base register
                    (only +/- 32kB could be addressed with SDA or +/- 4 MB in case of -large_sda)

    -------------------------------------------------------------------------------------

    More details could be found in the GHS compiler manual under
    "C:\MTC10Tools\Compiler_GHS\[used version]\manuals\build_v800.pdf"
*/



// mapping to C99 pragma directive
#define PRAGMA(x) _Pragma(#x)


// exclude data from SDA (Small Data Area) ------------ ATTENTION: deprecated version !!!!!!!!   For MISRA compliance use  RBSECTION_START_SECTTYPE_NO_SDA/RBSECTION_END_SECTTYPE_NO_SDA
#define START_SECTTYPE_NO_SDA       PRAGMA( ghs startdata )
#define END_SECTTYPE_NO_SDA         PRAGMA( ghs enddata )



// exclude data from SDA (Small Data Area) ------------  MISRA compliant version !!!!!!!!
#define RBSECTION_START_SECTTYPE_NO_SDA       PRAGMA( ghs startdata )
#define RBSECTION_END_SECTTYPE_NO_SDA         PRAGMA( ghs enddata )


/**
 * @brief Exclude explicitly initialized data from SDA and assign it to user specific linker section
 *
 * Example:
 *
 *    h-file:
 *      RBSECTION_START_REMAP_DATA(.my_data)
 *      extern int foo_a
 *      RBSECTION_END_REMAP_DATA
 *
 *    c-file:
 *      RBSECTION_START_REMAP_DATA(.my_data)
 *      int foo_a = 4;
 *      RBSECTION_END_REMAP_DATA
 *
 *      ==> Explicitly initialized data "foo_a" will be allocated within user specific linker section .my_data
 *
 *   @param[in] x   user specific linker section
 *
 */
#define RBSECTION_START_REMAP_DATA(x)         RBSECTION_START_SECTTYPE_NO_SDA                     \
                                              PRAGMA ( ghs section data = #x )

#define RBSECTION_END_REMAP_DATA              PRAGMA( ghs section data = default )      \
                                              RBSECTION_END_SECTTYPE_NO_SDA


/**
 * @brief Exclude zero initialized data from SDA and assign it to user specific linker section
 *
 * Example:
 *
 *    h-file:
 *      RBSECTION_START_REMAP_BSS(.my_bss)
 *      extern int foo_b;
 *      RBSECTION_END_REMAP_BSS
 *
 *    c-file:
 *      RBSECTION_START_REMAP_BSS(.my_bss)
 *      int foo_b;
 *      RBSECTION_END_REMAP_BSS
 *
 *      ==> Zero initialized data "foo_b" will be allocated within user specific linker section .my_bss
 *
 *   @param[in] x   user specific linker section
 *
 */
#define RBSECTION_START_REMAP_BSS(x)          RBSECTION_START_SECTTYPE_NO_SDA                     \
                                              PRAGMA ( ghs section bss = #x )

#define RBSECTION_END_REMAP_BSS               PRAGMA( ghs section bss = default )       \
                                              RBSECTION_END_SECTTYPE_NO_SDA


/**
 * @brief Exclude const data from SDA and assign it to user specific linker section
 *
 * Example:
 *
 *    h-file:
 *      RBSECTION_START_REMAP_RODATA(.my_rodata)
 *      extern const int foo_c;
 *      RBSECTION_END_REMAP_RODATA
 *
 *    c-file:
 *      RBSECTION_START_REMAP_RODATA(.my_rodata)
 *      const int foo_c = 4;
 *      RBSECTION_END_REMAP_RODATA
 *
 *      ==> Const data "foo_c" will be allocated within user specific linker section .my_rodata
 *
 *   @param[in] x   user specific linker section
 *
 */
#define RBSECTION_START_REMAP_RODATA(x)       RBSECTION_START_SECTTYPE_NO_SDA                     \
                                              PRAGMA ( ghs section rodata = #x )

#define RBSECTION_END_REMAP_RODATA            PRAGMA( ghs section rodata = default )    \
                                              RBSECTION_END_SECTTYPE_NO_SDA


/**
 * @brief Assign code to user specific linker section
 *
 * Example:
 *
 *    h-file:
 *      RBSECTION_START_REMAP_TEXT(.my_text)
 *      extern void foo(void);
 *      RBSECTION_END_REMAP_TEXT
 *
 *    c-file:
 *      RBSECTION_START_REMAP_TEXT(.my_text)
 *      void foo(void){...}
 *      RBSECTION_END_REMAP_TEXT
 *
 *      ==> Function foo will be allocated within user specific linker section .my_text
 *
 *   @param[in] x   user specific linker section
 *
 */
#define RBSECTION_START_REMAP_TEXT(x)         PRAGMA ( ghs section text = #x )

#define RBSECTION_END_REMAP_TEXT              PRAGMA( ghs section text = default )




/* ------------------------------------------------------------------------------------------------
    Bootmanager / bootloader remapping
   --------------------------------------------------------------------------------------------- */

#if (RBFS_Bootblock == RBFS_Bootblock_Enabled)
  /* remapping of rodata (read-only initialized data) to bootmanager */
  #define RBSECTION_START_BMGR_RODATA               RBSECTION_START_REMAP_RODATA(.bmgr)
  #define RBSECTION_END_BMGR_RODATA                 RBSECTION_END_REMAP_RODATA

  /* remapping of check structure to bootmanager */
  #define RBSECTION_START_CHECKST_BMGR_RODATA       RBSECTION_START_REMAP_RODATA(.checkst_bmgr)
  #define RBSECTION_END_CHECKST_BMGR_RODATA         RBSECTION_END_REMAP_RODATA

  /* remapping of hexblock structure to bootmanager */
  #define RBSECTION_START_HEXBLOCKST_BMGR_RODATA    RBSECTION_START_REMAP_RODATA(.hexblockst_bmgr)
  #define RBSECTION_END_HEXBLOCKST_BMGR_RODATA      RBSECTION_END_REMAP_RODATA

  /* remapping of signature structures to bootmanager */
  #define RBSECTION_START_CERT_BMGR_RODATA          RBSECTION_START_REMAP_RODATA(.cert_bmgr)
  #define RBSECTION_END_CERT_BMGR_RODATA            RBSECTION_END_REMAP_RODATA
  #define RBSECTION_START_SIG_BMGR_RODATA           RBSECTION_START_REMAP_RODATA(.sig_bmgr)
  #define RBSECTION_END_SIG_BMGR_RODATA             RBSECTION_END_REMAP_RODATA
  #define RBSECTION_START_CERTINFO_BMGR_RODATA      RBSECTION_START_REMAP_RODATA(.certinfo_bmgr)
  #define RBSECTION_END_CERTINFO_BMGR_RODATA        RBSECTION_END_REMAP_RODATA

  #if (RBFS_OEMBootloader  == RBFS_OEMBootloader_Yes)
    /* remapping of rodata (read-only initialized data) to OEM bootloader */
    #define RBSECTION_START_BLDR_RODATA               RBSECTION_START_REMAP_RODATA(.bldr)
    #define RBSECTION_END_BLDR_RODATA                 RBSECTION_END_REMAP_RODATA

    /* remapping of check structure to OEM bootloader */
    #define RBSECTION_START_CHECKST_BLDR_RODATA       RBSECTION_START_REMAP_RODATA(.checkst_bldr)
    #define RBSECTION_END_CHECKST_BLDR_RODATA         RBSECTION_END_REMAP_RODATA

    /* remapping of hexblock structure to OEM bootloader */
    #define RBSECTION_START_HEXBLOCKST_BLDR_RODATA    RBSECTION_START_REMAP_RODATA(.hexblockst_bldr)
    #define RBSECTION_END_HEXBLOCKST_BLDR_RODATA      RBSECTION_END_REMAP_RODATA

    /* remapping of signature structures to OEM bootloader */
    #define RBSECTION_START_CERT_BLDR_RODATA          RBSECTION_START_REMAP_RODATA(.cert_bldr)
    #define RBSECTION_END_CERT_BLDR_RODATA            RBSECTION_END_REMAP_RODATA
    #define RBSECTION_START_SIG_BLDR_RODATA           RBSECTION_START_REMAP_RODATA(.sig_bldr)
    #define RBSECTION_END_SIG_BLDR_RODATA             RBSECTION_END_REMAP_RODATA
    #define RBSECTION_START_CERTINFO_BLDR_RODATA      RBSECTION_START_REMAP_RODATA(.certinfo_bldr)
    #define RBSECTION_END_CERTINFO_BLDR_RODATA        RBSECTION_END_REMAP_RODATA
  #endif

  #if (RBFS_RBBootloader  == RBFS_RBBootloader_Yes)
    /* remapping of rodata (read-only initialized data) to RB bootloader */
    #define RBSECTION_START_RBBLDR_RODATA               RBSECTION_START_REMAP_RODATA(.rbbldr)
    #define RBSECTION_END_RBBLDR_RODATA                 RBSECTION_END_REMAP_RODATA

    /* remapping of check structure to RB bootloader */
    #define RBSECTION_START_CHECKST_RBBLDR_RODATA       RBSECTION_START_REMAP_RODATA(.checkst_rbbldr)
    #define RBSECTION_END_CHECKST_RBBLDR_RODATA         RBSECTION_END_REMAP_RODATA

    /* remapping of hexblock structure to RB bootloader */
    #define RBSECTION_START_HEXBLOCKST_RBBLDR_RODATA    RBSECTION_START_REMAP_RODATA(.hexblockst_rbbldr)
    #define RBSECTION_END_HEXBLOCKST_RBBLDR_RODATA      RBSECTION_END_REMAP_RODATA

    /* remapping of signature structures to RB bootloader */
    #define RBSECTION_START_CERT_RBBLDR_RODATA          RBSECTION_START_REMAP_RODATA(.cert_rbbldr)
    #define RBSECTION_END_CERT_RBBLDR_RODATA            RBSECTION_END_REMAP_RODATA
    #define RBSECTION_START_SIG_RBBLDR_RODATA           RBSECTION_START_REMAP_RODATA(.sig_rbbldr)
    #define RBSECTION_END_SIG_RBBLDR_RODATA             RBSECTION_END_REMAP_RODATA
    #define RBSECTION_START_CERTINFO_RBBLDR_RODATA      RBSECTION_START_REMAP_RODATA(.certinfo_rbbldr)
    #define RBSECTION_END_CERTINFO_RBBLDR_RODATA        RBSECTION_END_REMAP_RODATA
  #endif


#endif

/* remapping Backup RAM area used for sharing data between bootblock and FSW */
#define RBSECTION_START_BURAM_BB_FSW_INTERFACE_BSS_NOCLEAR      RBSECTION_START_REMAP_BSS(.buram_bb_fsw_interface_noclear)
#define RBSECTION_END_BURAM_BB_FSW_INTERFACE_BSS_NOCLEAR        RBSECTION_END_REMAP_BSS

/* remapping Backup RAM for bootblock */
#define RBSECTION_START_BURAM_BB_BSS_NOCLEAR        RBSECTION_START_REMAP_BSS(.buram_bb_noclear)
#define RBSECTION_END_BURAM_BB_BSS_NOCLEAR          RBSECTION_END_REMAP_BSS


/* ------------------------------------------------------------------------------------------------
    Generic remapping
   --------------------------------------------------------------------------------------------- */

/* remapping RAM sections */
#define RBSECTION_START_STACK_CPU0_NOCLEAR          RBSECTION_START_REMAP_BSS(.lram0_stack_noclear)
#define RBSECTION_END_STACK_CPU0_NOCLEAR            RBSECTION_END_REMAP_BSS

#define RBSECTION_START_LRAM0_BSS_CLEAR             RBSECTION_START_REMAP_BSS(.lram0_bss_clear)
#define RBSECTION_END_LRAM0_BSS_CLEAR               RBSECTION_END_REMAP_BSS

#define RBSECTION_START_LRAM0_BSS_NOCLEAR           RBSECTION_START_REMAP_BSS(.lram0_bss_noclear)
#define RBSECTION_END_LRAM0_BSS_NOCLEAR             RBSECTION_END_REMAP_BSS

#define RBSECTION_START_LRAM0_DATA                  RBSECTION_START_REMAP_DATA(.lram0_data)
#define RBSECTION_END_LRAM0_DATA                    RBSECTION_END_REMAP_DATA

#if (RBFS_LocalRamCore1Support == RBFS_LocalRamCore1Support_ON)
  #define RBSECTION_START_STACK_CPU1_NOCLEAR          RBSECTION_START_REMAP_BSS(.lram1_stack_noclear)
  #define RBSECTION_END_STACK_CPU1_NOCLEAR            RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_LRAM1_BSS_CLEAR             RBSECTION_START_REMAP_BSS(.lram1_bss_clear)
  #define RBSECTION_END_LRAM1_BSS_CLEAR               RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_LRAM1_BSS_NOCLEAR           RBSECTION_START_REMAP_BSS(.lram1_bss_noclear)
  #define RBSECTION_END_LRAM1_BSS_NOCLEAR             RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_LRAM1_DATA                  RBSECTION_START_REMAP_DATA(.lram1_data)
  #define RBSECTION_END_LRAM1_DATA                    RBSECTION_END_REMAP_DATA
#endif

#if (RBFS_LocalRamCore2Support == RBFS_LocalRamCore2Support_ON)
  #define RBSECTION_START_STACK_CPU2_NOCLEAR          RBSECTION_START_REMAP_BSS(.lram2_stack_noclear)
  #define RBSECTION_END_STACK_CPU2_NOCLEAR            RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_LRAM2_BSS_CLEAR             RBSECTION_START_REMAP_BSS(.lram2_bss_clear)
  #define RBSECTION_END_LRAM2_BSS_CLEAR               RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_LRAM2_BSS_NOCLEAR           RBSECTION_START_REMAP_BSS(.lram2_bss_noclear)
  #define RBSECTION_END_LRAM2_BSS_NOCLEAR             RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_LRAM2_DATA                  RBSECTION_START_REMAP_DATA(.lram2_data)
  #define RBSECTION_END_LRAM2_DATA                    RBSECTION_END_REMAP_DATA
#endif

#if (RBFS_LocalRamCore3Support == RBFS_LocalRamCore3Support_ON)
  #define RBSECTION_START_STACK_CPU3_NOCLEAR          RBSECTION_START_REMAP_BSS(.lram3_stack_noclear)
  #define RBSECTION_END_STACK_CPU3_NOCLEAR            RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_LRAM3_BSS_CLEAR             RBSECTION_START_REMAP_BSS(.lram3_bss_clear)
  #define RBSECTION_END_LRAM3_BSS_CLEAR               RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_LRAM3_BSS_NOCLEAR           RBSECTION_START_REMAP_BSS(.lram3_bss_noclear)
  #define RBSECTION_END_LRAM3_BSS_NOCLEAR             RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_LRAM3_DATA                  RBSECTION_START_REMAP_DATA(.lram3_data)
  #define RBSECTION_END_LRAM3_DATA                    RBSECTION_END_REMAP_DATA
#endif


#if (RBFS_ClusterRam0Support == RBFS_ClusterRam0Support_ON)
  #define RBSECTION_START_CRAM0_BSS_CLEAR             RBSECTION_START_REMAP_BSS(.cram0_bss_clear)
  #define RBSECTION_END_CRAM0_BSS_CLEAR               RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_CRAM0_BSS_NOCLEAR           RBSECTION_START_REMAP_BSS(.cram0_bss_noclear)
  #define RBSECTION_END_CRAM0_BSS_NOCLEAR             RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_CRAM0_DATA                  RBSECTION_START_REMAP_DATA(.cram0_data)
  #define RBSECTION_END_CRAM0_DATA                    RBSECTION_END_REMAP_DATA
#endif

#if (RBFS_ClusterRam1Support == RBFS_ClusterRam1Support_ON)
  #define RBSECTION_START_CRAM1_BSS_CLEAR             RBSECTION_START_REMAP_BSS(.cram1_bss_clear)
  #define RBSECTION_END_CRAM1_BSS_CLEAR               RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_CRAM1_BSS_NOCLEAR           RBSECTION_START_REMAP_BSS(.cram1_bss_noclear)
  #define RBSECTION_END_CRAM1_BSS_NOCLEAR             RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_CRAM1_DATA                  RBSECTION_START_REMAP_DATA(.cram1_data)
  #define RBSECTION_END_CRAM1_DATA                    RBSECTION_END_REMAP_DATA
#endif

#if (RBFS_ClusterRam2Support == RBFS_ClusterRam2Support_ON)
  #define RBSECTION_START_CRAM2_BSS_CLEAR             RBSECTION_START_REMAP_BSS(.cram2_bss_clear)
  #define RBSECTION_END_CRAM2_BSS_CLEAR               RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_CRAM2_BSS_NOCLEAR           RBSECTION_START_REMAP_BSS(.cram2_bss_noclear)
  #define RBSECTION_END_CRAM2_BSS_NOCLEAR             RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_CRAM2_DATA                  RBSECTION_START_REMAP_DATA(.cram2_data)
  #define RBSECTION_END_CRAM2_DATA                    RBSECTION_END_REMAP_DATA
#endif

#if (RBFS_ClusterRam3Support == RBFS_ClusterRam3Support_ON)
  #define RBSECTION_START_CRAM3_BSS_CLEAR             RBSECTION_START_REMAP_BSS(.cram3_bss_clear)
  #define RBSECTION_END_CRAM3_BSS_CLEAR               RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_CRAM3_BSS_NOCLEAR           RBSECTION_START_REMAP_BSS(.cram3_bss_noclear)
  #define RBSECTION_END_CRAM3_BSS_NOCLEAR             RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_CRAM3_DATA                  RBSECTION_START_REMAP_DATA(.cram3_data)
  #define RBSECTION_END_CRAM3_DATA                    RBSECTION_END_REMAP_DATA
#endif


#if (RBFS_GlobalRamSupport == RBFS_GlobalRamSupport_ON)
  #define RBSECTION_START_GRAM_BSS_NOCLEAR            RBSECTION_START_REMAP_BSS(.gram_bss_noclear)
  #define RBSECTION_END_GRAM_BSS_NOCLEAR              RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_GRAM_BANK_A_BSS_CLEAR       RBSECTION_START_REMAP_BSS(.gram_bank_a_bss_clear)
  #define RBSECTION_END_GRAM_BANK_A_BSS_CLEAR         RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_GRAM_BANK_B_BSS_CLEAR       RBSECTION_START_REMAP_BSS(.gram_bank_b_bss_clear)
  #define RBSECTION_END_GRAM_BANK_B_BSS_CLEAR         RBSECTION_END_REMAP_BSS
#endif

/* Linker sections on P1x at GRAM are allocated on U2A at CRAM0 */
#if (RBFS_ClusterRam0Support == RBFS_ClusterRam0Support_ON)
  #define RBSECTION_START_GRAM_BSS_NOCLEAR            RBSECTION_START_CRAM0_BSS_NOCLEAR
  #define RBSECTION_END_GRAM_BSS_NOCLEAR              RBSECTION_END_CRAM0_BSS_NOCLEAR

  #define RBSECTION_START_GRAM_BANK_A_BSS_CLEAR       RBSECTION_START_CRAM0_BSS_CLEAR
  #define RBSECTION_END_GRAM_BANK_A_BSS_CLEAR         RBSECTION_END_CRAM0_BSS_CLEAR

  #define RBSECTION_START_GRAM_BANK_B_BSS_CLEAR       RBSECTION_START_CRAM0_BSS_CLEAR
  #define RBSECTION_END_GRAM_BANK_B_BSS_CLEAR         RBSECTION_END_CRAM0_BSS_CLEAR
#endif


/* remapping of DLM structure (DLM area must be a noclear section, because downloaded reprog driver must be still available after software reset) */
#define RBSECTION_START_DLM_BSS_NOCLEAR             RBSECTION_START_REMAP_BSS(.dlm_noclear)
#define RBSECTION_END_DLM_BSS_NOCLEAR               RBSECTION_END_REMAP_BSS


#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  /* remapping of DMA buffers (RAM) to dedicated DMA RAM section because of unsafe DMA */
  #define RBSECTION_START_DMA_BSS                   RBSECTION_START_REMAP_BSS(.dma_bss)
  #define RBSECTION_END_DMA_BSS                     RBSECTION_END_REMAP_BSS
#else
  /* for P1x: no remapping of DMA buffers needed as DMA is safe */
  #define RBSECTION_START_DMA_BSS
  #define RBSECTION_END_DMA_BSS
#endif

/* remapping of text section for special startup-code executed out of RAM */
#define RBSECTION_START_GRAM_TEXT                   RBSECTION_START_REMAP_TEXT(.gram_text)
#define RBSECTION_END_GRAM_TEXT                     RBSECTION_END_REMAP_TEXT


/* ------------------------------------------------------------------------------------------------
    ASW (application software)  C parameter  and  ASCET parameter remapping
   --------------------------------------------------------------------------------------------- */

/* remapping for initialized ASW C parameters - initialized ASCET parameters are also mapped to this section */
#define RBSECTION_START_ASW_RAM_INIT                RBSECTION_START_REMAP_DATA(.asw_ram_init)
#define RBSECTION_END_ASW_RAM_INIT                  RBSECTION_END_REMAP_DATA

/* remapping for uninitialized ASW C parameters - uninitialized ASCET parameters are also mapped to this section */
#define RBSECTION_START_ASW_RAM_NOINIT                  RBSECTION_START_REMAP_BSS(.asw_ram_noinit)
#define RBSECTION_END_ASW_RAM_NOINIT                    RBSECTION_END_REMAP_BSS

/* remapping for constant ASW C and ASCET parameters */
#define RBSECTION_START_ASW_CONST                       RBSECTION_START_REMAP_RODATA(.ascet_const)
#define RBSECTION_END_ASW_CONST                         RBSECTION_END_REMAP_RODATA

/* remapping for the three usecases above with flexible section names */
#define RBSECTION_START_ASW_RAM_INIT_CUSTOMIZED(x)      RBSECTION_START_REMAP_DATA(.asw_ram_init_##x)
#define RBSECTION_END_ASW_RAM_INIT_CUSTOMIZED(x)        RBSECTION_END_REMAP_DATA

#define RBSECTION_START_ASW_RAM_NOINIT_CUSTOMIZED(x)    RBSECTION_START_REMAP_BSS(.asw_ram_noinit_##x)
#define RBSECTION_END_ASW_RAM_NOINIT_CUSTOMIZED(x)      RBSECTION_END_REMAP_BSS

#define RBSECTION_START_ASW_CONST_CUSTOMIZED(x)         RBSECTION_START_REMAP_RODATA(.ascet_const_##x)
#define RBSECTION_END_ASW_CONST_CUSTOMIZED(x)           RBSECTION_END_REMAP_RODATA


/* ------------------------------------------------------------------------------------------------
    FSW (application software) remapping
   --------------------------------------------------------------------------------------------- */

/* remapping of rodata (read-only initialized data) to first code block */
#define RBSECTION_START_FSW_01_RODATA               RBSECTION_START_REMAP_RODATA(.fsw_01)
#define RBSECTION_END_FSW_01_RODATA                 RBSECTION_END_REMAP_RODATA

/* remapping of check structure to first code block */
#define RBSECTION_START_CHECKST_FSW_01_RODATA       RBSECTION_START_REMAP_RODATA(.checkst_fsw_01)
#define RBSECTION_END_CHECKST_FSW_01_RODATA         RBSECTION_END_REMAP_RODATA

/* remapping of hexblock structure to first code block */
#define RBSECTION_START_HEXBLOCKST_FSW_01_RODATA    RBSECTION_START_REMAP_RODATA(.hexblockst_fsw_01)
#define RBSECTION_END_HEXBLOCKST_FSW_01_RODATA      RBSECTION_END_REMAP_RODATA

/* remapping of signature structures to first code block */
#define RBSECTION_START_CERT_FSW_01_RODATA          RBSECTION_START_REMAP_RODATA(.cert_fsw_01)
#define RBSECTION_END_CERT_FSW_01_RODATA            RBSECTION_END_REMAP_RODATA
#define RBSECTION_START_SIG_FSW_01_RODATA           RBSECTION_START_REMAP_RODATA(.sig_fsw_01)
#define RBSECTION_END_SIG_FSW_01_RODATA             RBSECTION_END_REMAP_RODATA
#define RBSECTION_START_CERTINFO_FSW_01_RODATA      RBSECTION_START_REMAP_RODATA(.certinfo_fsw_01)
#define RBSECTION_END_CERTINFO_FSW_01_RODATA        RBSECTION_END_REMAP_RODATA

/* remapping of rodata (read-only initialized data) to second code block */
#define RBSECTION_START_FSW_02_RODATA               RBSECTION_START_REMAP_RODATA(.fsw_02)
#define RBSECTION_END_FSW_02_RODATA                 RBSECTION_END_REMAP_RODATA

/* remapping of check structure to second code block */
#define RBSECTION_START_CHECKST_FSW_02_RODATA       RBSECTION_START_REMAP_RODATA(.checkst_fsw_02)
#define RBSECTION_END_CHECKST_FSW_02_RODATA         RBSECTION_END_REMAP_RODATA

/* remapping of hexblock structure to second code block */
#define RBSECTION_START_HEXBLOCKST_FSW_02_RODATA    RBSECTION_START_REMAP_RODATA(.hexblockst_fsw_02)
#define RBSECTION_END_HEXBLOCKST_FSW_02_RODATA      RBSECTION_END_REMAP_RODATA

/* remapping of signature structures to second code block */
#define RBSECTION_START_CERT_FSW_02_RODATA          RBSECTION_START_REMAP_RODATA(.cert_fsw_02)
#define RBSECTION_END_CERT_FSW_02_RODATA            RBSECTION_END_REMAP_RODATA
#define RBSECTION_START_SIG_FSW_02_RODATA           RBSECTION_START_REMAP_RODATA(.sig_fsw_02)
#define RBSECTION_END_SIG_FSW_02_RODATA             RBSECTION_END_REMAP_RODATA
#define RBSECTION_START_CERTINFO_FSW_02_RODATA      RBSECTION_START_REMAP_RODATA(.certinfo_fsw_02)
#define RBSECTION_END_CERTINFO_FSW_02_RODATA        RBSECTION_END_REMAP_RODATA



/* remapping Backup RAM for FSW */
#define RBSECTION_START_BURAM_FSW_BSS_NOCLEAR       RBSECTION_START_REMAP_BSS(.buram_fsw_noclear)
#define RBSECTION_END_BURAM_FSW_BSS_NOCLEAR         RBSECTION_END_REMAP_BSS


/* ------------------------------------------------------------------------------------------------
    TSI (diagnosis software) remapping
   --------------------------------------------------------------------------------------------- */

/* remapping of rodata (read-only initialized data) to diagnosis code block */
#define RBSECTION_START_TSI_RODATA                  RBSECTION_START_REMAP_RODATA(.tsi)
#define RBSECTION_END_TSI_RODATA                    RBSECTION_END_REMAP_RODATA

/* remapping of check structure to diagnosis code block */
#define RBSECTION_START_CHECKST_TSI_RODATA          RBSECTION_START_REMAP_RODATA(.checkst_tsi)
#define RBSECTION_END_CHECKST_TSI_RODATA            RBSECTION_END_REMAP_RODATA

/* remapping of hexblock structure to diagnosis code block */
#define RBSECTION_START_HEXBLOCKST_TSI_RODATA       RBSECTION_START_REMAP_RODATA(.hexblockst_tsi)
#define RBSECTION_END_HEXBLOCKST_TSI_RODATA         RBSECTION_END_REMAP_RODATA

/* remapping of signature structures to diagnosis code block */
#define RBSECTION_START_CERT_TSI_RODATA             RBSECTION_START_REMAP_RODATA(.cert_tsi)
#define RBSECTION_END_CERT_TSI_RODATA               RBSECTION_END_REMAP_RODATA
#define RBSECTION_START_SIG_TSI_RODATA              RBSECTION_START_REMAP_RODATA(.sig_tsi)
#define RBSECTION_END_SIG_TSI_RODATA                RBSECTION_END_REMAP_RODATA
#define RBSECTION_START_CERTINFO_TSI_RODATA         RBSECTION_START_REMAP_RODATA(.certinfo_tsi)
#define RBSECTION_END_CERTINFO_TSI_RODATA           RBSECTION_END_REMAP_RODATA

/* ------------------------------------------------------------------------------------------------
    Emulation device specific remapping
   --------------------------------------------------------------------------------------------- */

#if ( (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD3ED) \
    ||(RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD5ED) \
    ||(RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD7ED) \
    )
  /* remapping of XCP structure */
  #define RBSECTION_START_XCP_BSS_NOCLEAR           RBSECTION_START_REMAP_BSS(.xcp_noclear)
  #define RBSECTION_END_XCP_BSS_NOCLEAR             RBSECTION_END_REMAP_BSS

  /* remapping of XCP timing mon structure */
  #define RBSECTION_START_XCPPERF_BSS_NOCLEAR       RBSECTION_START_REMAP_BSS(.xcpperf_noclear)
  #define RBSECTION_END_XCPPERF_BSS_NOCLEAR         RBSECTION_END_REMAP_BSS

  /* remapping of Variable RAM */
  #define RBSECTION_START_VARIABLE_RAM_BSS_CLEAR    RBSECTION_START_REMAP_BSS(.variable_ram_bss_clear)
  #define RBSECTION_END_VARIABLE_RAM_BSS_CLEAR      RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_VARIABLE_RAM_BSS_NOCLEAR  RBSECTION_START_REMAP_BSS(.variable_ram_bss_noclear)
  #define RBSECTION_END_VARIABLE_RAM_BSS_NOCLEAR    RBSECTION_END_REMAP_BSS

  #define RBSECTION_START_VARIABLE_RAM_DATA         RBSECTION_START_REMAP_DATA(.variable_ram_data)
  #define RBSECTION_END_VARIABLE_RAM_DATA           RBSECTION_END_REMAP_DATA
#endif


/* ------------------------------------------------------------------------------------------------
    CAL block 1 remapping
   --------------------------------------------------------------------------------------------- */

/* remapping of rodata (read-only initialized data) to calibration block 1 */
#define RBSECTION_START_CAL1_RODATA                 RBSECTION_START_REMAP_RODATA(.cal1)
#define RBSECTION_END_CAL1_RODATA                   RBSECTION_END_REMAP_RODATA

/* remapping of check structure to calibration block 1 */
#define RBSECTION_START_CHECKST_CAL1_RODATA         RBSECTION_START_REMAP_RODATA(.checkst_cal1)
#define RBSECTION_END_CHECKST_CAL1_RODATA           RBSECTION_END_REMAP_RODATA

/* remapping of hexblock structure to calibration block 1 */
#define RBSECTION_START_HEXBLOCKST_CAL1_RODATA      RBSECTION_START_REMAP_RODATA(.hexblockst_cal1)
#define RBSECTION_END_HEXBLOCKST_CAL1_RODATA        RBSECTION_END_REMAP_RODATA

/* remapping of signature structures to calibration block 1 */
#define RBSECTION_START_CERT_CAL1_RODATA          RBSECTION_START_REMAP_RODATA(.cert_cal1)
#define RBSECTION_END_CERT_CAL1_RODATA            RBSECTION_END_REMAP_RODATA
#define RBSECTION_START_SIG_CAL1_RODATA           RBSECTION_START_REMAP_RODATA(.sig_cal1)
#define RBSECTION_END_SIG_CAL1_RODATA             RBSECTION_END_REMAP_RODATA
#define RBSECTION_START_CERTINFO_CAL1_RODATA      RBSECTION_START_REMAP_RODATA(.certinfo_cal1)
#define RBSECTION_END_CERTINFO_CAL1_RODATA        RBSECTION_END_REMAP_RODATA

/* deprecated (for backward compatibility only) */
#define RBSECTION_START_CAL_RODATA                  RBSECTION_START_CAL1_RODATA
#define RBSECTION_END_CAL_RODATA                    RBSECTION_END_CAL1_RODATA
#define RBSECTION_START_CHECKST_CAL_RODATA          RBSECTION_START_CHECKST_CAL1_RODATA
#define RBSECTION_END_CHECKST_CAL_RODATA            RBSECTION_END_CHECKST_CAL1_RODATA
#define RBSECTION_START_HEXBLOCKST_CAL_RODATA       RBSECTION_START_HEXBLOCKST_CAL1_RODATA
#define RBSECTION_END_HEXBLOCKST_CAL_RODATA         RBSECTION_END_HEXBLOCKST_CAL1_RODATA


/* ------------------------------------------------------------------------------------------------
    CAL block 2 remapping
   --------------------------------------------------------------------------------------------- */

/* remapping of rodata (read-only initialized data) to calibration block 2 */
#define RBSECTION_START_CAL2_RODATA                 RBSECTION_START_REMAP_RODATA(.cal2)
#define RBSECTION_END_CAL2_RODATA                   RBSECTION_END_REMAP_RODATA

/* remapping of check structure to calibration block 2 */
#define RBSECTION_START_CHECKST_CAL2_RODATA         RBSECTION_START_REMAP_RODATA(.checkst_cal2)
#define RBSECTION_END_CHECKST_CAL2_RODATA           RBSECTION_END_REMAP_RODATA

/* remapping of hexblock structure to calibration block 2 */
#define RBSECTION_START_HEXBLOCKST_CAL2_RODATA      RBSECTION_START_REMAP_RODATA(.hexblockst_cal2)
#define RBSECTION_END_HEXBLOCKST_CAL2_RODATA        RBSECTION_END_REMAP_RODATA

/* remapping of signature structures to calibration block 2 */
#define RBSECTION_START_CERT_CAL2_RODATA          RBSECTION_START_REMAP_RODATA(.cert_cal2)
#define RBSECTION_END_CERT_CAL2_RODATA            RBSECTION_END_REMAP_RODATA
#define RBSECTION_START_SIG_CAL2_RODATA           RBSECTION_START_REMAP_RODATA(.sig_cal2)
#define RBSECTION_END_SIG_CAL2_RODATA             RBSECTION_END_REMAP_RODATA
#define RBSECTION_START_CERTINFO_CAL2_RODATA      RBSECTION_START_REMAP_RODATA(.certinfo_cal2)
#define RBSECTION_END_CERTINFO_CAL2_RODATA        RBSECTION_END_REMAP_RODATA

/* ------------------------------------------------------------------------------------------------
    Hardware Security Module (HSM) remapping
   --------------------------------------------------------------------------------------------- */

#if(RBFS_HardwareSecurityModule ==  RBFS_HardwareSecurityModule_Supported)
  /* remapping of rodata (read-only initialized data) to HSM block */
  #define RBSECTION_START_HSM_RODATA                RBSECTION_START_REMAP_RODATA(.hsm_text)
  #define RBSECTION_END_HSM_RODATA                  RBSECTION_END_REMAP_RODATA

  /* remapping of check structure to HSM block */
  #define RBSECTION_START_CHECKST_HSM_RODATA        RBSECTION_START_REMAP_RODATA(.checkst_hsm)
  #define RBSECTION_END_CHECKST_HSM_RODATA          RBSECTION_END_REMAP_RODATA

  /* remapping of hexinfo structure to HSM block */
  #define RBSECTION_START_HEXINFO_HSM_RODATA        RBSECTION_START_REMAP_RODATA(.hexinfo_hsm)
  #define RBSECTION_END_HEXINFO_HSM_RODATA          RBSECTION_END_REMAP_RODATA

  /* remapping of hexblock structure to HSM block */
  #define RBSECTION_START_HEXBLOCKST_HSM_RODATA     RBSECTION_START_REMAP_RODATA(.hexblockst_hsm)
  #define RBSECTION_END_HEXBLOCKST_HSM_RODATA       RBSECTION_END_REMAP_RODATA
  /* remapping of rodata (read-only initialized data) to HSM boot block */
  #define RBSECTION_START_HSMBOOTCODE_RODATA        RBSECTION_START_REMAP_RODATA(.hsm_boot)
  #define RBSECTION_END_HSMBOOTCODE_RODATA          RBSECTION_END_REMAP_RODATA
#endif


/* ------------------------------------------------------------------------------------------------
    FOTA Backup Block remapping
   --------------------------------------------------------------------------------------------- */

#if ((RBFS_FOTA == RBFS_FOTA_BASEPLUS) || (RBFS_FOTA == RBFS_FOTA_ENHANCED))
  /* remapping of rodata (read-only initialized data) to FOTA block */
  #define RBSECTION_START_FOTABACKUP_RODATA             RBSECTION_START_REMAP_RODATA(.fotabackup_text)
  #define RBSECTION_END_FOTABACKUP_RODATA               RBSECTION_END_REMAP_RODATA

  /* remapping of check structure to FOTA block */
  #define RBSECTION_START_CHECKST_FOTABACKUP_RODATA     RBSECTION_START_REMAP_RODATA(.checkst_fotabackup)
  #define RBSECTION_END_CHECKST_FOTABACKUP_RODATA       RBSECTION_END_REMAP_RODATA

  /* remapping of hexinfo structure to FOTA block */
  #define RBSECTION_START_HEXINFO_FOTABACKUP_RODATA     RBSECTION_START_REMAP_RODATA(.hexinfo_fotabackup)
  #define RBSECTION_END_HEXINFO_FOTABACKUP_RODATA       RBSECTION_END_REMAP_RODATA

  /* remapping of hexblock structure to FOTA block */
  #define RBSECTION_START_HEXBLOCKST_FOTABACKUP_RODATA  RBSECTION_START_REMAP_RODATA(.hexblockst_fotabackup)
  #define RBSECTION_END_HEXBLOCKST_FOTABACKUP_RODATA    RBSECTION_END_REMAP_RODATA

  /* remapping of signature structures to FOTA code block */
  #define RBSECTION_START_CERT_FOTABACKUP_RODATA          RBSECTION_START_REMAP_RODATA(.cert_fotabackup)
  #define RBSECTION_END_CERT_FOTABACKUP_RODATA            RBSECTION_END_REMAP_RODATA
  #define RBSECTION_START_SIG_FOTABACKUP_RODATA           RBSECTION_START_REMAP_RODATA(.sig_fotabackup)
  #define RBSECTION_END_SIG_FOTABACKUP_RODATA             RBSECTION_END_REMAP_RODATA
  #define RBSECTION_START_CERTINFO_FOTABACKUP_RODATA      RBSECTION_START_REMAP_RODATA(.certinfo_fotabackup)
  #define RBSECTION_END_CERTINFO_FOTABACKUP_RODATA        RBSECTION_END_REMAP_RODATA

#endif


#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
/* ------------------------------------------------------------------------------------------------
    HCUHEX remapping
   --------------------------------------------------------------------------------------------- */

/* remapping Flash-Option-Byte structure*/
#define RBSECTION_START_HCU_CONFIG                  RBSECTION_START_REMAP_RODATA(.hcu_config)
#define RBSECTION_END_HCU_CONFIG                    RBSECTION_END_REMAP_RODATA

/* remapping OTP-Bits structure*/
#define RBSECTION_START_HCU_OTP                     RBSECTION_START_REMAP_RODATA(.hcu_otp)
#define RBSECTION_END_HCU_OTP                       RBSECTION_END_REMAP_RODATA

/* remapping Lock-Bits structure*/
#define RBSECTION_START_HCU_LOCKBITS                RBSECTION_START_REMAP_RODATA(.hcu_lockbits)
#define RBSECTION_END_HCU_LOCKBITS                  RBSECTION_END_REMAP_RODATA

#endif

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
/* ------------------------------------------------------------------------------------------------
    Option Bytes remapping for U2A
   --------------------------------------------------------------------------------------------- */

/* remapping CSA OTP-Bits structure*/
#define RBSECTION_START_CSA_OTP                     RBSECTION_START_REMAP_RODATA(.csa_otp)
#define RBSECTION_END_CSA_OTP                       RBSECTION_END_REMAP_RODATA

/* remapping CSA Flash-Option-Byte structure*/
#define RBSECTION_START_CSA_CONFIG                  RBSECTION_START_REMAP_RODATA(.csa_config)
#define RBSECTION_END_CSA_CONFIG                    RBSECTION_END_REMAP_RODATA

/* remapping SSA OTP-Bits structure*/
#define RBSECTION_START_SSA_OTP                     RBSECTION_START_REMAP_RODATA(.ssa_otp)
#define RBSECTION_END_SSA_OTP                       RBSECTION_END_REMAP_RODATA
/* remapping SSA Flash-Option-Byte structure*/
#define RBSECTION_START_SSA_CONFIG1                 RBSECTION_START_REMAP_RODATA(.ssa_config1)
#define RBSECTION_END_SSA_CONFIG1                   RBSECTION_END_REMAP_RODATA
#define RBSECTION_START_SSA_CONFIG2                 RBSECTION_START_REMAP_RODATA(.ssa_config2)
#define RBSECTION_END_SSA_CONFIG2                   RBSECTION_END_REMAP_RODATA

/* remapping BPA0 OTP-Bits user area structure*/
#define RBSECTION_START_BPA0_OTP                     RBSECTION_START_REMAP_RODATA(.bpa0_otp)
#define RBSECTION_END_BPA0_OTP                       RBSECTION_END_REMAP_RODATA
/* remapping BPA0 Flash-Option-Byte structure OTP ext. + CustID etc .*/
#define RBSECTION_START_BPA0_CONFIG1                RBSECTION_START_REMAP_RODATA(.bpa0_config1)
#define RBSECTION_END_BPA0_CONFIG1                  RBSECTION_END_REMAP_RODATA
#define RBSECTION_START_BPA0_CONFIG2                RBSECTION_START_REMAP_RODATA(.bpa0_config2)
#define RBSECTION_END_BPA0_CONFIG2                  RBSECTION_END_REMAP_RODATA

/* remapping BPA1 OTP-Bits user area structure*/
#define RBSECTION_START_BPA1_OTP                    RBSECTION_START_REMAP_RODATA(.bpa1_otp)
#define RBSECTION_END_BPA1_OTP                      RBSECTION_END_REMAP_RODATA
/* remapping BPA1 Flash-Option-Byte structure*/
#define RBSECTION_START_BPA1_CONFIG                 RBSECTION_START_REMAP_RODATA(.bpa1_config)
#define RBSECTION_END_BPA1_CONFIG                   RBSECTION_END_REMAP_RODATA

#endif

/** @} */
/* End ingroup RBLCF */

#endif /* End of multiple include protection */
