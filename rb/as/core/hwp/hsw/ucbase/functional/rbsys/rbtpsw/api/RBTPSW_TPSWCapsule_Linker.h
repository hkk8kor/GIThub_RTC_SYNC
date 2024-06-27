#ifndef RBTPSW_TPSWCAPSULE_LINKER_H__
#define RBTPSW_TPSWCAPSULE_LINKER_H__

/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Linker add-on for TPSW framework
 *
 * Integration of untrusted applications must be done within linker directive file with this special provided macros.
 * Linker generated symbols for start- and end-address are used to configure corresponding MPU channels.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


/* Take care - no other header includes are allowed here as long as MTC less than 10.6 is used.
 * For further details see comment within "RBLCF_LDAddOn.h".
 */


#define RBTPSW_SECTION_START(name)  .name##_ALIGN_START  align(4) : {} > .  \
                                    _RBTPSW_LINKERSYMBOL_##name##_start = .;

#define RBTPSW_SECTION_END(name)    .name##_ALIGN_END  align(4) : {} > .  \
                                    _RBTPSW_LINKERSYMBOL_##name##_end = .;\
                                    . = . + 4; /* This to prevent two neighbor TPSWs to share their end/start address*/\
                                               /* (last address register describes last VALID address). */


/************************************************************
Both macros RBTPSW_SECTION_START/RBTPSW_SECTION_END must be
used to define corresponding TPSW sections in your linker file.

For example:

    RBTPSW_SECTION_START(MYTPSW1_LCF)

    .MYTPSW1_DATA  align(4)  :
    {
        RBTPSW_MyTPSW1.o (.data)
        RBTPSW_MyTPSW1.o (.sdata)
    } > .

    .MYTPSW1_BSS  align(4)  :
    {
        RBTPSW_MyTPSW1.o (.bss)
        RBTPSW_MyTPSW1.o (.sbss)
    } > .

    RBTPSW_SECTION_END(MYTPSW1_LCF)

*************************************************************/

/** @} */
/* End ingroup RBTPSW */

#endif /* End of multiple include protection */
