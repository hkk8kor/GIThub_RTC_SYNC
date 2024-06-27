/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief RBSYS related startup part for bootblock
 *
 * This module must be part of the bootblock and contains the whole uC startup and
 * controller specific initialization.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBLCF_MemoryRemap.h"



/* realized interfaces */
#include "RBSYS_BBFSW_StartupServices.h"



/* Assert supported configurations: switches, parameters, constants, ... */



/* --------------------------------------------------------------------- */
/* ---------- Handling of BB FSW INTERFACE Backup RAM area ------------- */
/* --------------------------------------------------------------------- */
RBSECTION_START_BURAM_BB_FSW_INTERFACE_BSS_NOCLEAR
  volatile RBSYS_BURAM_BB_FSW_INTERFACE_t RBSYS_BURAM_BB_FSW_INTERFACE;
RBSECTION_END_BURAM_BB_FSW_INTERFACE_BSS_NOCLEAR



/** @} */
/* End ingroup RBSYS */
