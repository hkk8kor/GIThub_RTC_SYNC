/* Set default to INVALID_ISR as this is not a recoverable ISR */
#define OS_CAT1_ID_InvalidInt ((uint32)INVALID_ISR)
#define OS_CAT1_TRACKER_InvalidInt Os_RunningCat1ISR
#define OS_CAT1_ID_b_EXCFPP (1U)
#define OS_CAT1_TRACKER_b_EXCFPP Os_RunningCat1ISR
#define OS_CAT1_ID_EXCFETRAP (2U)
#define OS_CAT1_TRACKER_EXCFETRAP Os_RunningCat1ISR
#define OS_CAT1_ID_EXCHVTRAP (3U)
#define OS_CAT1_TRACKER_EXCHVTRAP Os_RunningCat1ISR
#define OS_CAT1_ID_EXCMDP (4U)
#define OS_CAT1_TRACKER_EXCMDP Os_RunningCat1ISR
#define OS_CAT1_ID_EXCPIE (5U)
#define OS_CAT1_TRACKER_EXCPIE Os_RunningCat1ISR
#define OS_CAT1_ID_EXCUCPOP (6U)
#define OS_CAT1_TRACKER_EXCUCPOP Os_RunningCat1ISR
#define OS_CAT1_ID_b_EXCDEBUG (7U)
#define OS_CAT1_TRACKER_b_EXCDEBUG Os_RunningCat1ISR
#define OS_CAT1_ID_b_EXCFEINT (8U)
#define OS_CAT1_TRACKER_b_EXCFEINT Os_RunningCat1ISR
#define OS_CAT1_ID_b_EXCMAE (9U)
#define OS_CAT1_TRACKER_b_EXCMAE Os_RunningCat1ISR
#define OS_CAT1_ID_b_EXCRIE (10U)
#define OS_CAT1_TRACKER_b_EXCRIE Os_RunningCat1ISR
#define OS_CAT1_ID_EXCFENMI (11U)
#define OS_CAT1_TRACKER_EXCFENMI Os_RunningCat1ISR
#define OS_CAT1_ID_b_EXCSYSERR (12U)
#define OS_CAT1_TRACKER_b_EXCSYSERR Os_RunningCat1ISR
#define OS_TARGET_RH850GHS


/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern void b_EXCFPP(void); /*lint -esym(752,b_EXCFPP) allow to be unreferenced */
extern void EXCFETRAP(void); /*lint -esym(752,EXCFETRAP) allow to be unreferenced */
extern void EXCHVTRAP(void); /*lint -esym(752,EXCHVTRAP) allow to be unreferenced */
extern void EXCMDP(void); /*lint -esym(752,EXCMDP) allow to be unreferenced */
extern void EXCPIE(void); /*lint -esym(752,EXCPIE) allow to be unreferenced */
extern void EXCUCPOP(void); /*lint -esym(752,EXCUCPOP) allow to be unreferenced */
extern void b_EXCDEBUG(void); /*lint -esym(752,b_EXCDEBUG) allow to be unreferenced */
extern void b_EXCFEINT(void); /*lint -esym(752,b_EXCFEINT) allow to be unreferenced */
extern void b_EXCMAE(void); /*lint -esym(752,b_EXCMAE) allow to be unreferenced */
extern void b_EXCRIE(void); /*lint -esym(752,b_EXCRIE) allow to be unreferenced */
extern void EXCFENMI(void); /*lint -esym(752,EXCFENMI) allow to be unreferenced */
extern void b_EXCSYSERR(void); /*lint -esym(752,b_EXCSYSERR) allow to be unreferenced */
extern void InvalidInt(void); /*lint -esym(752,InvalidInt) allow to be unreferenced */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
