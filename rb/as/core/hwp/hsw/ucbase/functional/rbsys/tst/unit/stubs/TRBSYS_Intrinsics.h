#ifndef TRBSYS_INTRINSICS_H__
#define TRBSYS_INTRINSICS_H__

#include "SwTest_Global.h"
#include "RBSYS_Config.h"
#include "TRBSYS_Helper.h"

extern void RBSYS_memory_changed(void);
extern uint32 RBSYS_getLinkPointer(void);
void TRBSYS_setLinkPointer(int nLinkPointer);
extern int RBSYS_LDL_W(int *p);
extern int RBSYS_STC_W(int d, int *p);
#define RBSYS_CAST2LDLSTC_TYPE(var) ((int *) (var))
extern uint32 TRBSYS_GetSnoozeCounter(void);

extern void TRBSYS_SetAbortSnoozeLoop(void);
extern uint32 TRBSYS_GetSnoozeLoopCounter(void);
extern void RBSYS_SNOOZE_LOOP(int cnt);

#define TRBSYS_SNOOZE_LOOP_TICKS     10
extern void RBSYS_snooze(void);

extern uint16 TRBSYS_wait_time;
extern uint16 TRBSYS_GetWaitUsecLoop_ExpiredTime(void);

extern TRBSYS_Callback_t TRBSYS_SYNCM_Callback;
extern void RBSYS_SYNCM(void);
extern void RBSYS_SYNCP(void);
extern void RBSYS_SYNCI(void);
extern unsigned int RBSYS_STSR(int regID, int selID);
extern void RBSYS_LDSR(int regID, int selID, unsigned int val);


/* helper functions */
extern int TRBSYS_Get_SYNCM_CNT(void);
extern int TRBSYS_Get_SYNCP_CNT(void);
extern int TRBSYS_Get_SYNCI_CNT(void);

extern void TRBSYS_Clear_SYNCP_CNT(void);

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  #define REG_ID_MAX     40
  #define SEL_ID_MAX     20
  extern void TRBSYS_SetSystemRegister(int regID, int selID, unsigned int val);
  extern uint32 TRBSYS_GetSystemRegister(int regID, int selID);
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  extern void TRBSYS_SetSystemRegister(uint32 coproc, uint32 opcode1, uint32 val, uint32 CRn, uint32 CRm, uint32 opcode2);
  extern void TRBSYS_SetSystemRegister64(uint32 coproc, uint32 opcode, uint64 val64, uint32 CRm);
  extern uint32 TRBSYS_GetSystemRegister(uint32 coproc, uint32 opcode1, uint32 CRn, uint32 CRm, uint32 opcode2);
  extern uint64 TRBSYS_GetSystemRegister64(uint32 coproc, uint32 opcode, uint32 CRm);
#endif

extern void RBSYS_SET1(volatile char *addr, int bitnum);
extern void RBSYS_CLR1(volatile char *addr, int bitnum);

extern void TRBSYS_SET1_Overwrite_ZFlag(int value);

extern void RBSYS_DI(void);
extern void RBSYS_EI(void);


#define OPCODE1_MAX   7
#define CRN_MAX      16
#define CRM_MAX      16
#define OPCODE2_MAX   8
extern uint64 TRBSYS_SystemRegister_STMStellar[OPCODE1_MAX][CRN_MAX][CRM_MAX][OPCODE2_MAX][RB_NUM_CORES];
extern uint32 RBSYS_MRC(uint32 coproc, uint32 opcode1, uint32 CRn, uint32 CRm, uint32 opcode2);
extern uint32 RBSYS_MRRC(uint32 coproc, uint32 opcode, uint32 CRm);

typedef struct
{
  uint32 coproc;
  uint32 opcode1;
  uint64 val;
  uint32 CRn;
  uint32 CRm;
  uint32 opcode2;
}TRBSYS_SystemRegister_WriteAccess;
extern TRBSYS_SystemRegister_WriteAccess TRBSYS_SystemRegister_STMStellar_WriteAccesses[4000];
extern uint32 TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx;

extern void RBSYS_MCR(uint32 coproc, uint32 opcode1, uint32 val, uint32 CRn, uint32 CRm, uint32 opcode2);
extern void RBSYS_MCRR(uint32 coproc, uint32 opcode, uint64 val64, uint32 CRm);

extern void RBSYS_VMSR(uint32 regnum, uint32 val);

extern void RBSYS_DSB(void);
extern uint32 TRBSYS_Get_DSB_Cnt(void);
extern void RBSYS_ISB(void);
extern uint32 TRBSYS_Get_ISB_Cnt(void);

extern int RBSYS_LDREX(const int* addr);
extern int RBSYS_STREX(int value, int* addr);
extern void RBSYS_CLREX(void);
extern void RBSYS_HVC(int code);

extern void TRBSYS_Intrinsics_SetRegisterSetIndex(uint32 coreRegisterSetIndex);

#endif
