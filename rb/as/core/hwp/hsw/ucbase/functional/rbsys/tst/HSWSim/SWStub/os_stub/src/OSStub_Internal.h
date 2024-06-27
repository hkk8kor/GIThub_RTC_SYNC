#ifndef OSSTUB_INTERNAL_H__
#define OSSTUB_INTERNAL_H__

/** @brief shares functionality between RBSYSStub and OSStub. */

extern uint32 OSSim_PseudoTickCounter_GetTicks(void);

extern void OSSim_PseudoTickCounter_PseudoIncrement(void);

#endif
