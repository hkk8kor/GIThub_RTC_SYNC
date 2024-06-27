#ifndef RBSYS_OPBT_U2A_SANITYCHECK_H__
#define RBSYS_OPBT_U2A_SANITYCHECK_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Sanity checks for HCUHEX file generation
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"

/* used interfaces */
#include "RBSYS_OPBT_U2C_config.h"


/* NO_TOOL_SCAN */
/* REASON: Sanity check */

#if( (RESET_VECTOR_PE0 & 0x00FFFE00u) != RESET_VECTOR_PE0 )
  #error "RESET_VECTOR_PE0 out of bounds or wrong alignment"
#endif

#if( (RESET_VECTOR_PE1 & 0x00FFFE00u) != RESET_VECTOR_PE1 )
  #error "RESET_VECTOR_PE0 out of bounds or wrong alignment"
#endif

#if( (RESET_VECTOR_PE2 & 0x00FFFE00u) != RESET_VECTOR_PE2 )
  #error "RESET_VECTOR_PE0 out of bounds or wrong alignment"
#endif

#if( (RESET_VECTOR_PE3 & 0x00FFFE00u) != RESET_VECTOR_PE3 )
  #error "RESET_VECTOR_PE0 out of bounds or wrong alignment"
#endif

/* Hint: Some settings are reserved within Host User Manual and are only described within Security User Manual. */

/* NO_TOOL_SCAN_END */


#endif