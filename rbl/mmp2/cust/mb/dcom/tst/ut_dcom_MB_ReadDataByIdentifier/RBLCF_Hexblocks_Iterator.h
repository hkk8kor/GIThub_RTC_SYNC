#ifndef RBLCF_HEXBLOCKS_ITERATOR_H__
#define RBLCF_HEXBLOCKS_ITERATOR_H__

/**
 * @ingroup RBLCF
 * @{
 *
 * @file
 * @brief HexBlock iterator
 *
 * This interface provides an iterator over the single HexBlocks as an abstraction
 * of the CC-AS Hexfile Layout.
 *
 *
 * Referenced documents:
 * - <a href="file:///c:/MTC10Base/HexfileHandling/hexfile_handling_in_Evo17_projects.pdf">hexfile_handling_in_Evo17_projects.pdf</a>
 * - <a href="file:///c:/MTC10Base/HexfileHandling/Multi_block_hexfile_handling.pdf">Multi_block_hexfile_handling.pdf</a>
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
#include "RBLCF_HexBlocks_Structs.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_RBBootloader,
                          RBFS_RBBootloader_Yes,
                          RBFS_RBBootloader_No);

dcom_BootHeader_tst *DCOM_BOOTLOADER_ADDRESS_STUBBED;
dcom_BootHeader_tst *DCOM_APPLICATION_ENDADDRESS_STUBBED;

#define DCOM_BOOTLOADER_ADDRESS  &DCOM_BOOTLOADER_ADDRESS_STUBBED
#define DCOM_APPLICATION_ENDADDRESS     DCOM_APPLICATION_ENDADDRESS_STUBBED
/**
 * @brief HexBlock Layout Structure
 *
 * Each user of the HexBlock iterator must allocate an instance of this structure.
 * So this instance will be adapted once per iteration and provides the corresponding
 * data of one HexBlock.
 */
typedef struct
{
  uint32 HexBlockStartAdr;                      // start address of current HexBlock
  const RBLCF_HexBlockStruct_t* HexBlockRef;    // pointer to HexBlock structure
  const RBLCF_StdHexInfoStruct_t* HexInfoRef;   // pointer to HexInfo structure
  const RBLCF_StdCheckStruct_t* CheckRef;       // pointer to Check structure
  boolean hasNext;                              // successor of this HexBlock available

} RBLCF_HexBlockLayout_t;


extern void RBLCF_GetFirstHexBlock(RBLCF_HexBlockLayout_t* nHexBlock);
extern void RBLCF_GetNextHexBlock(RBLCF_HexBlockLayout_t* nHexBlock);



/*
 * ------------------------
 * Simple iterator example:
 * ------------------------
 *
 * RBLCF_HexBlockLayout_t myHexBlock;
 * ...
 * RBLCF_GetFirstHexBlock(&myHexBlock);
 * ...
 * while (myHexBlock.hasNext)
 * {
 *   RBLCF_GetNextHexBlock(&myHexBlock);
 *   ...
 * }
 *
 */



#if( RBFS_HSWSimulation == RBFS_HSWSimulation_ON )
#include "../../tst/hswsim/lcfstub/api/RBLCFStub.h" ///< forwards RBLCFSTUB_API_LEVEL
///< allows foreign components to identify API-Level of RBLCFStub
///< even before "RBLCFStub.h" was present.
///< If only "rblcf-component with RBLCFStub.h" is used everywhere.
///< this forwarding can be removed.
///< R.Flechsig 3-Aug-2017
#endif

/** @} */
/* End ingroup RBLCF */

#endif /* End of multiple include protection */
