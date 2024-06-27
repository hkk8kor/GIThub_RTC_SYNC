/*
 * This is Compiler.h for target platform: RH850x2GHS/U2C4
 */

#ifndef COMPILER_H
#define COMPILER_H

/* [COMPILER010] The compiler */
#define _GREENHILLS_C_RH850X2GHS_
/* [COMPILER043] Published information : sample */
#define COMPILER_VENDOR_ID (11U)
#define COMPILER_AR_MAJOR_VERSION (4U)
#define COMPILER_AR_MINOR_VERSION (5U)
#define COMPILER_AR_PATCH_VERSION (0U)
#define COMPILER_SW_MAJOR_VERSION (0U)
#define COMPILER_SW_MINOR_VERSION (0U)
#define COMPILER_SW_PATCH_VERSION (0U)

#include <Compiler_Cfg.h>

#define AUTOMATIC  /* [COMPILER046] [COMPILER036] Used for local non static variables */
#define TYPEDEF  /* [COMPILER059] Type definitions where no memory qualifier can be specified. */
#define STATIC static /* [COMPILER049] */
#define NULL_PTR ((void *)0) /* [COMPILER051] */
#define INLINE  /* [COMPILER057] */
#define LOCAL_INLINE  /* [COMPILER060] */

#define FUNC(rettype, memclass) rettype memclass /* [COMPILER001] */
#define P2VAR(ptrtype, memclass, ptrclass) ptrclass ptrtype * memclass /* [COMPILER006] */
#define P2CONST(ptrtype, memclass, ptrclass) const ptrclass ptrtype * memclass /* [COMPILER013] */
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrclass ptrtype * const memclass /* [COMPILER031] */
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const memclass ptrtype * const ptrclass /* [COMPILER032] */
#define P2FUNC(rettype, ptrclass, fctname) ptrclass rettype (*fctname) /* [COMPILER039] */
#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const ptrclass fctname) /* [COMPILER065] */
#define CONST(ctype, memclass)  memclass const ctype /* [COMPILER023] */
#define VAR(vtype, memclass)  memclass vtype /* [COMPILER026] */
#define FUNC_P2CONST(rettype, ptrclass, memclass) const ptrclass rettype * memclass /* [COMPILER061] [$UKS 1769] */
#define FUNC_P2VAR(rettype, ptrclass, memclass) ptrclass rettype * memclass /* [COMPILER063] [$UKS 1770] */

#endif /* COMPILER_H */
