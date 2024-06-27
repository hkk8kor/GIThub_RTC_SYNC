#ifndef TRBSYS_DYN_ADAPTOR_H__
#define TRBSYS_DYN_ADAPTOR_H__

#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"


extern void SetPrivate_RBSYS_TaskChain_X1L_ActiveInThisCycle(boolean value);
extern boolean GetPrivate_RBSYS_TaskChain_X1L_ActiveInThisCycle(void);


/********************************************************/
/*                Get private variables                 */
/********************************************************/
extern const PRC_PTR* GetPrivate_prclist_taskinit(void);
#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  extern const PRC_PTR* GetPrivate_prclist_task0p5ms(void);
#endif
extern const PRC_PTR* GetPrivate_prclist_task1ms(void);
extern const PRC_PTR* GetPrivate_prclist_taskx1h(void);
extern const PRC_PTR* GetPrivate_prclist_taskx1l(void);
extern const PRC_PTR* GetPrivate_prclist_taskx2(void);
#if (RBFS_MCORE == RBFS_MCORE_ON)
  extern const PRC_PTR* GetPrivate_prclist_taskx2p(void);
#endif
extern const PRC_PTR* GetPrivate_prclist_taskx4(void);
extern const PRC_PTR* GetPrivate_prclist_taskx8(void);
extern const PRC_PTR* GetPrivate_prclist_taskx24(void);
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  extern const PRC_PTR* GetPrivate_prclist_taskx4pl(void);
  extern const PRC_PTR* GetPrivate_prclist_taskx200bg(void);
  extern const PRC_PTR* GetPrivate_prclist_taskExtPrio1(void);
  extern const PRC_PTR* GetPrivate_prclist_taskExtPrio2(void);
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  extern const PRC_PTR* GetPrivate_prclist_taskx1guest(void);
  extern const PRC_PTR* GetPrivate_prclist_taskx2guest(void);
  extern const PRC_PTR* GetPrivate_prclist_taskx4guest(void);
  extern const PRC_PTR* GetPrivate_prclist_taskx10guest(void);
  extern const PRC_PTR* GetPrivate_prclist_taskx20guest(void);
#endif



extern const PRC_PTR* GetPrivate_c_TaskInit(void);
#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  extern const PRC_PTR* GetPrivate_c_Task0p5ms(void);
#endif
extern const PRC_PTR* GetPrivate_c_Task1ms(void);
extern const PRC_PTR* GetPrivate_c_Taskx1h(void);
extern const PRC_PTR* GetPrivate_c_Taskx1l(void);
extern const PRC_PTR* GetPrivate_c_Taskx2(void);
#if (RBFS_MCORE == RBFS_MCORE_ON)
  extern const PRC_PTR* GetPrivate_c_Taskx2p(void);
#endif
extern const PRC_PTR* GetPrivate_c_Taskx4(void);
extern const PRC_PTR* GetPrivate_c_Taskx8(void);
extern const PRC_PTR* GetPrivate_c_Taskx24(void);
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  extern const PRC_PTR* GetPrivate_c_Taskx4pl(void);
  extern const PRC_PTR* GetPrivate_c_Taskx200bg(void);
  extern const PRC_PTR* GetPrivate_c_TaskExtPrio1(void);
  extern const PRC_PTR* GetPrivate_c_TaskExtPrio2(void);
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  extern const PRC_PTR* GetPrivate_c_Taskx1Guest(void);
  extern const PRC_PTR* GetPrivate_c_Taskx2Guest(void);
  extern const PRC_PTR* GetPrivate_c_Taskx4Guest(void);
  extern const PRC_PTR* GetPrivate_c_Taskx10Guest(void);
  extern const PRC_PTR* GetPrivate_c_Taskx20Guest(void);
#endif



extern const PRC_PTR* GetPrivate_c_TaskInitBaseOS(void);
#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  extern const PRC_PTR* GetPrivate_c_Task0p5msBaseOS(void);
#endif
extern const PRC_PTR* GetPrivate_c_Task1msBaseOS(void);
extern const PRC_PTR* GetPrivate_c_Taskx1hBaseOS(void);
extern const PRC_PTR* GetPrivate_c_Taskx1lBaseOS(void);
extern const PRC_PTR* GetPrivate_c_Taskx2BaseOS(void);
#if (RBFS_MCORE == RBFS_MCORE_ON)
  extern const PRC_PTR* GetPrivate_c_Taskx2pBaseOS(void);
#endif
extern const PRC_PTR* GetPrivate_c_Taskx4BaseOS(void);
extern const PRC_PTR* GetPrivate_c_Taskx8BaseOS(void);
extern const PRC_PTR* GetPrivate_c_Taskx24BaseOS(void);
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  extern const PRC_PTR* GetPrivate_c_Taskx4plBaseOS(void);
  extern const PRC_PTR* GetPrivate_c_Taskx200bgBaseOS(void);
  extern const PRC_PTR* GetPrivate_c_TaskExtPrio1BaseOS(void);
  extern const PRC_PTR* GetPrivate_c_TaskExtPrio2BaseOS(void);
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  extern const PRC_PTR* GetPrivate_c_Taskx1GuestBaseOS(void);
  extern const PRC_PTR* GetPrivate_c_Taskx2GuestBaseOS(void);
  extern const PRC_PTR* GetPrivate_c_Taskx4GuestBaseOS(void);
  extern const PRC_PTR* GetPrivate_c_Taskx10GuestBaseOS(void);
  extern const PRC_PTR* GetPrivate_c_Taskx20GuestBaseOS(void);
#endif



extern uint32 GetPrivate_RBSYS_ISRcnt_1ms(void);
extern uint32 GetPrivate_RBSYS_ISRcnt_x1(void);
extern uint32 GetPrivate_RBSYS_ISRcnt_SWINT0(void);
extern uint32 GetPrivate_RBSYS_ISRcnt_FLX0LINE0(void);
extern uint32 GetPrivate_RBSYS_ISRcnt_FLX1LINE0(void);
#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  extern uint32 GetPrivate_RBSYS_ISRcnt_MTTCANI0(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_MCAN0I0(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_MCAN1I0(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_MCAN2I0(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_RLIN30RX(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_RLIN30STATUS(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_RLIN31RX(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_RLIN31STATUS(void);
#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  extern uint32 GetPrivate_RBSYS_ISRcnt_CAN0REC(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_CAN0TRX(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_CAN1REC(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_CAN1TRX(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_CAN2REC(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_CAN2TRX(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_CAN6REC(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_CAN6TRX(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_CAN8REC(void);
  extern uint32 GetPrivate_RBSYS_ISRcnt_CAN8TRX(void);
#endif

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  extern uint32 GetPrivate_RBSYS_TASKcnt_x200bg_skippedActivation(void);
#endif


/********************************************************/
/*                Set private variables                 */
/********************************************************/


/********************************************************/
/*              Access private Functions                */
/********************************************************/
extern void CallPrivate_taskbody_prc_calls(const PRC_PTR proc_table[]);
extern void CallPrivate_set_prclist_default(void);

#endif