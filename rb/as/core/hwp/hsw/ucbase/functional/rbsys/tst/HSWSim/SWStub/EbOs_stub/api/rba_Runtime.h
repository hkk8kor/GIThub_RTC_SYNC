#ifndef RBA_RUNTIME_H__
#define RBA_RUNTIME_H__

/** 
 * @file
 * @brief Header (stubs) provides interfaces for EbOs runtime measurement.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

/// rba_Runtime_Types.h

#include "Std_Types.h" ///< for uint32 etc.

/**********************
 * MT measure element *
 **********************/

/* Simple structure for MT measurements */
typedef struct
{
    /* Runtime, only updated from outside measure in reentrant case */
    uint32 tiActRT_u32;
    uint32 tiMinRT_u32;
    uint32 tiMaxRT_u32;

    /* Call distance, only updated from outside measure in reentrant case */
    uint32 tiActCD_u32;

    /* Call counter, reentrant calls not included */
    uint32 ctCalls_u32;

    /* Internal values */
    /* Start timestamp of current call of the free running counter */
    uint32 tiCallBeginFree_u32;

    /* Start timestamp of current call of the net runtime timestamp from Os_GetExecutionTime */
    uint32 tiCallBegin_u32;

    /* Id/timestamp for interrupt correction */
    uint32 intCorr_u32;
} rba_Runtime_MTValues_t;

/// take over from rba_Runtime.h original in CUBAS (PSW_Int 4-Apr-2019)
/* Normal version for task/isr bodies
 * Parameter must be pointer to rba_Runtime_MTValues_t */
#define rba_Runtime_MTStartMeasure(x) /* dead */
#define rba_Runtime_MTEndMeasure(x) /* dead */


#endif
