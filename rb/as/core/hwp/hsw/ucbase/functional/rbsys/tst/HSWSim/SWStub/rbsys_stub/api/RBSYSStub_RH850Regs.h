#ifndef RBSYSSTUB_RH850REGS_H__
#define RBSYSSTUB_RH850REGS_H__


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"

/* used interfaces */
#include "RBSYSStub_RegisterStub.h"

/* original RBSYS_RH850Regs.h forwards intrinsics */
#include "RBSYS_Intrinsics.h"

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)

  extern uint32* VALID_FLAG_PFLASH_BANK_A_PU32;
  extern uint32* VALID_FLAG_PFLASH_BANK_B_PU32;

  #define ERASE_COUNTER_OFFSET_AREA0   0x00000040
  #define ERASE_COUNTER_OFFSET_AREA1   0x00000041

  extern uint32 AREA_1_IS_VALID;

  extern uint16 Stub_EA_Bank_A[334];
  extern uint16 Stub_EA_Bank_B[334];
  #define PFLASH_A_ERASE_COUNTER_AREA0_PU16 ((uint16 volatile *) (Stub_EA_Bank_A + ERASE_COUNTER_OFFSET_AREA0))
  #define PFLASH_A_ERASE_COUNTER_AREA1_PU16 ((uint16 volatile *) (Stub_EA_Bank_A + ERASE_COUNTER_OFFSET_AREA1))
  #define PFLASH_B_ERASE_COUNTER_AREA0_PU16 ((uint16 volatile *) (Stub_EA_Bank_B + ERASE_COUNTER_OFFSET_AREA0))
  #define PFLASH_B_ERASE_COUNTER_AREA1_PU16 ((uint16 volatile *) (Stub_EA_Bank_B + ERASE_COUNTER_OFFSET_AREA1))

#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)

  extern uint32* VALID_FLAG_PFLASH_BANK_0_PU32;
  extern uint32* VALID_FLAG_PFLASH_BANK_1_PU32;

  #define ERASE_COUNTER_OFFSET_AREA0   0x00000800
  #define ERASE_COUNTER_OFFSET_AREA1   0x00001000

  extern uint32* VALID_FLAG_PFLASH_BANK_2_PU32;
  extern uint32* VALID_FLAG_PFLASH_BANK_3_PU32;

  extern uint32 AREA_1_IS_VALID;

  extern uint16 Stub_EA_Bank_A_0[70];
  extern uint16 Stub_EA_Bank_A_1[70];
  extern uint16 Stub_EA_Bank_B_0[70];
  extern uint16 Stub_EA_Bank_B_1[70];
  extern uint16 Stub_EA_Bank_C_0[70];
  extern uint16 Stub_EA_Bank_C_1[70];
  extern uint16 Stub_EA_Bank_D_0[70];
  extern uint16 Stub_EA_Bank_D_1[70];

  #define PFLASH_0_ERASE_COUNTER_AREA0_PU16 ((uint16 volatile *) (Stub_EA_Bank_A_0))
  #define PFLASH_0_ERASE_COUNTER_AREA1_PU16 ((uint16 volatile *) (Stub_EA_Bank_A_1))
  #define PFLASH_1_ERASE_COUNTER_AREA0_PU16 ((uint16 volatile *) (Stub_EA_Bank_B_0))
  #define PFLASH_1_ERASE_COUNTER_AREA1_PU16 ((uint16 volatile *) (Stub_EA_Bank_B_1))
  #define PFLASH_2_ERASE_COUNTER_AREA0_PU16 ((uint16 volatile *) (Stub_EA_Bank_C_0))
  #define PFLASH_2_ERASE_COUNTER_AREA1_PU16 ((uint16 volatile *) (Stub_EA_Bank_C_1))
  #define PFLASH_3_ERASE_COUNTER_AREA0_PU16 ((uint16 volatile *) (Stub_EA_Bank_D_0))
  #define PFLASH_3_ERASE_COUNTER_AREA1_PU16 ((uint16 volatile *) (Stub_EA_Bank_D_1))

#else
    #error "Erase Counter not realized for current uCFamily."
#endif


#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  __attribute__((always_inline)) static inline void RBSYS_UnlockAccessToHwModule(volatile uint32* KeyCodeProtectionRegister)
  {
  }

  __attribute__((always_inline)) static inline void RBSYS_LockAccessToHwModule(volatile uint32* KeyCodeProtectionRegister)
  {
  }
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
