/**********************************************************************************/
/* [COPYRIGHT]                                                                    */
/* Robert Bosch GmbH reserves all rights even in the event of industrial          */
/* property rights. We reserve all rights of disposal such as copying and         */
/* passing on to third parties.                                                   */
/* [COPYRIGHT_END]                                                                */
/**********************************************************************************/
/*
 * ComScl_Appl_ChecksumLib.h
 */
#ifndef COMSCL_APPL_CHECKSUMLIB_H
#define COMSCL_APPL_CHECKSUMLIB_H

#include "RB_AsapTypes.h"

#include "rba_ComScl_ChecksumLib.h"

boolean CRC_Standard(const uint8* PduPtr, uint8 len_u8, uint8 strt_u8, uint8 sigLen_u8, uint8* l_Checksum_UB);

boolean CRC_Function(const uint8* PduPtr, uint8 len_u8, uint8 strt_u8, uint8 sigLen_u8, uint8* l_Checksum_UB);

#endif
/* COMSCL_APPL_CHECKSUMLIB_H */
