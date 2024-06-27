#include "RBSYS_Interrupt.h"
#include "SwTest_Global.h"
#include "RBSYS_Config.h"


/**
 * \Reference
 *
 * \Purpose
 *  Test Interfaces for Interrupt Controller Access
 *
 * \Sequence
 *  Check Address mapping of RBSYS_INTC2_EICn:
 *   - lower limit
 *   - some interrupt index in between
 *   - upper limit
 *
 * \ExpectedResult
 *  Address mapping has to fit P1x as well as U2A
 */
SWTEST void TRBSYS_Interrupts_CheckAddressMapping(void)
{
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )

    SWT_EvalEq( (uint32)&RBSYS_INTC2_EICn(RBSYS_INTC2_INDEX_MIN),   (uint32)&EICn[0]);
    SWT_EvalEq( (uint32)&RBSYS_INTC2_EICn(67),                      (uint32)&EICn[35]);
    SWT_EvalEq( (uint32)&RBSYS_INTC2_EICn(RBSYS_INTC2_INDEX_MAX),   (uint32)&EICn[213]);

  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

    SWT_EvalEq( (uint32)&RBSYS_INTC2_EICn(RBSYS_INTC2_INDEX_MIN),   (uint32)&INTC2EICn[0]);
    SWT_EvalEq( (uint32)&RBSYS_INTC2_EICn(67),                      (uint32)&INTC2EICn[35]);
    SWT_EvalEq( (uint32)&RBSYS_INTC2_EICn(RBSYS_INTC2_INDEX_MAX),   (uint32)&INTC2EICn[684]);

  #else
    SWT_Eval(TRUE);
    #warning("Stellar is not supported yet.")
  #endif
}

