#include "TRBSYS_Dyn_Adaptor.h" // need TRBSYS_DYN_ADAPTOR_H__ in TRBSYS_Os.h
#include "csw/RBSYS_TaskInfo.h" // ensure include of original RBSYS header instead of CoreStub
#define __interrupt
#include "RBSYS_Dyn.c"



#include "RBSYS_Config.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/
const PRC_PTR* GetPrivate_prclist_taskinit(void)
{
  return prclist_taskinit;
}

#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  const PRC_PTR* GetPrivate_prclist_task0p5ms(void)
  {
    return prclist_task0p5ms;
  }
#endif

const PRC_PTR* GetPrivate_prclist_task1ms(void)
{
  return prclist_task1ms;
}

const PRC_PTR* GetPrivate_prclist_taskx1h(void)
{
  return prclist_taskx1h;
}

const PRC_PTR* GetPrivate_prclist_taskx1l(void)
{
  return prclist_taskx1l;
}

const PRC_PTR* GetPrivate_prclist_taskx2(void)
{
  return prclist_taskx2;
}

#if (RBFS_MCORE == RBFS_MCORE_ON)
  const PRC_PTR* GetPrivate_prclist_taskx2p(void)
  {
    return prclist_taskx2p;
  }
#endif

const PRC_PTR* GetPrivate_prclist_taskx4(void)
{
  return prclist_taskx4;
}

const PRC_PTR* GetPrivate_prclist_taskx8(void)
{
  return prclist_taskx8;
}

const PRC_PTR* GetPrivate_prclist_taskx24(void)
{
  return prclist_taskx24;
}

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  const PRC_PTR* GetPrivate_prclist_taskx4pl(void)
  {
    return prclist_taskx4pl;
  }

  const PRC_PTR* GetPrivate_prclist_taskx200bg(void)
  {
    return prclist_taskx200bg;
  }

  const PRC_PTR* GetPrivate_prclist_taskExtPrio1(void)
  {
    return prclist_taskeventprio1;
  }

  const PRC_PTR* GetPrivate_prclist_taskExtPrio2(void)
  {
    return prclist_taskeventprio2;
  }
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  const PRC_PTR* GetPrivate_prclist_taskx1guest(void)
  {
    return prclist_taskx1guest;
  }
  const PRC_PTR* GetPrivate_prclist_taskx2guest(void)
  {
    return prclist_taskx2guest;
  }
  const PRC_PTR* GetPrivate_prclist_taskx4guest(void)
  {
    return prclist_taskx4guest;
  }
  const PRC_PTR* GetPrivate_prclist_taskx10guest(void)
  {
    return prclist_taskx10guest;
  }
  const PRC_PTR* GetPrivate_prclist_taskx20guest(void)
  {
    return prclist_taskx20guest;
  }
#endif



const PRC_PTR* GetPrivate_c_TaskInit(void)
{
  return c_TaskInit;
}

#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  const PRC_PTR* GetPrivate_c_Task0p5ms(void)
  {
    return c_Task0p5ms;
  }
#endif

const PRC_PTR* GetPrivate_c_Task1ms(void)
{
  return c_Task1ms;
}

const PRC_PTR* GetPrivate_c_Taskx1h(void)
{
  return c_Taskx1h;
}

const PRC_PTR* GetPrivate_c_Taskx1l(void)
{
  return c_Taskx1l;
}

const PRC_PTR* GetPrivate_c_Taskx2(void)
{
  return c_Taskx2;
}

#if (RBFS_MCORE == RBFS_MCORE_ON)
  const PRC_PTR* GetPrivate_c_Taskx2p(void)
  {
    return c_Taskx2p;
  }
#endif

const PRC_PTR* GetPrivate_c_Taskx4(void)
{
  return c_Taskx4;
}

const PRC_PTR* GetPrivate_c_Taskx8(void)
{
  return c_Taskx8;
}

const PRC_PTR* GetPrivate_c_Taskx24(void)
{
  return c_Taskx24;
}

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  const PRC_PTR* GetPrivate_c_Taskx4pl(void)
  {
    return c_Taskx4pl;
  }

  const PRC_PTR* GetPrivate_c_Taskx200bg(void)
  {
    return c_Taskx200bg;
  }

  const PRC_PTR* GetPrivate_c_TaskExtPrio1(void)
  {
    return c_TaskEventExtPrio1;
  }

  const PRC_PTR* GetPrivate_c_TaskExtPrio2(void)
  {
    return c_TaskEventExtPrio2;
  }
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  const PRC_PTR* GetPrivate_c_Taskx1Guest(void)
  {
    return c_Taskx1Guest;
  }
  const PRC_PTR* GetPrivate_c_Taskx2Guest(void)
  {
    return c_Taskx2Guest;
  }
  const PRC_PTR* GetPrivate_c_Taskx4Guest(void)
  {
    return c_Taskx4Guest;
  }
  const PRC_PTR* GetPrivate_c_Taskx10Guest(void)
  {
    return c_Taskx10Guest;
  }
  const PRC_PTR* GetPrivate_c_Taskx20Guest(void)
  {
    return c_Taskx20Guest;
  }
#endif



const PRC_PTR* GetPrivate_c_TaskInitBaseOS(void)
{
  return c_TaskInitBaseOS;
}

#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  const PRC_PTR* GetPrivate_c_Task0p5msBaseOS(void)
  {
    return c_Task0p5msBaseOS;
  }
#endif

const PRC_PTR* GetPrivate_c_Task1msBaseOS(void)
{
  return c_Task1msBaseOS;
}

const PRC_PTR* GetPrivate_c_Taskx1hBaseOS(void)
{
  return c_Taskx1hBaseOS;
}
const PRC_PTR* GetPrivate_c_Taskx1lBaseOS(void)
{
  return c_Taskx1lBaseOS;
}

const PRC_PTR* GetPrivate_c_Taskx2BaseOS(void)
{
  return c_Taskx2BaseOS;
}

#if (RBFS_MCORE == RBFS_MCORE_ON)
  const PRC_PTR* GetPrivate_c_Taskx2pBaseOS(void)
  {
    return c_Taskx2pBaseOS;
  }
#endif

const PRC_PTR* GetPrivate_c_Taskx4BaseOS(void)
{
  return c_Taskx4BaseOS;
}

const PRC_PTR* GetPrivate_c_Taskx8BaseOS(void)
{
  return c_Taskx8BaseOS;
}

const PRC_PTR* GetPrivate_c_Taskx24BaseOS(void)
{
  return c_Taskx24BaseOS;
}

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  const PRC_PTR* GetPrivate_c_Taskx4plBaseOS(void)
  {
    return c_Taskx4plBaseOS;
  }

  const PRC_PTR* GetPrivate_c_Taskx200bgBaseOS(void)
  {
    return c_Taskx200bgBaseOS;
  }

  const PRC_PTR* GetPrivate_c_TaskExtPrio1BaseOS(void)
  {
    return c_TaskEventExtPrio1BaseOS;
  }

  const PRC_PTR* GetPrivate_c_TaskExtPrio2BaseOS(void)
  {
    return c_TaskEventExtPrio2BaseOS;
  }
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  const PRC_PTR* GetPrivate_c_Taskx1GuestBaseOS(void)
  {
    return c_Taskx1GuestBaseOS;
  }
  const PRC_PTR* GetPrivate_c_Taskx2GuestBaseOS(void)
  {
    return c_Taskx2GuestBaseOS;
  }
  const PRC_PTR* GetPrivate_c_Taskx4GuestBaseOS(void)
  {
    return c_Taskx4GuestBaseOS;
  }
  const PRC_PTR* GetPrivate_c_Taskx10GuestBaseOS(void)
  {
    return c_Taskx10GuestBaseOS;
  }
  const PRC_PTR* GetPrivate_c_Taskx20GuestBaseOS(void)
  {
    return c_Taskx20GuestBaseOS;
  }
#endif



uint32 GetPrivate_RBSYS_ISRcnt_1ms(void)
{
  return RBSYS_ISRcnt_1ms;
}

uint32 GetPrivate_RBSYS_ISRcnt_x1(void)
{
  return RBSYS_ISRcnt_x1;
}

#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
  uint32 GetPrivate_RBSYS_ISRcnt_SWINT0(void)
  {
    return RBSYS_ISRcnt_SWINT0;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_FLX0LINE0(void)
  {
    return RBSYS_ISRcnt_FLX0LINE0;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_FLX1LINE0(void)
  {
    return RBSYS_ISRcnt_FLX1LINE0;
  }
#endif

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  uint32 GetPrivate_RBSYS_ISRcnt_MTTCANI0(void)
  {
    return RBSYS_ISRcnt_MTTCANI0;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_MCAN0I0(void)
  {
    return RBSYS_ISRcnt_MCAN0I0;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_MCAN1I0(void)
  {
    return RBSYS_ISRcnt_MCAN1I0;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_MCAN2I0(void)
  {
    return RBSYS_ISRcnt_MCAN2I0;
  }
#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  uint32 GetPrivate_RBSYS_ISRcnt_CAN0REC(void)
  {
    return RBSYS_ISRcnt_CAN0REC;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_CAN0TRX(void)
  {
    return RBSYS_ISRcnt_CAN0TRX;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_CAN1REC(void)
  {
    return RBSYS_ISRcnt_CAN1REC;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_CAN1TRX(void)
  {
    return RBSYS_ISRcnt_CAN1TRX;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_CAN2REC(void)
  {
    return RBSYS_ISRcnt_CAN2REC;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_CAN2TRX(void)
  {
    return RBSYS_ISRcnt_CAN2TRX;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_CAN6REC(void)
  {
    return RBSYS_ISRcnt_CAN6REC;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_CAN6TRX(void)
  {
    return RBSYS_ISRcnt_CAN6TRX;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_CAN8REC(void)
  {
    return RBSYS_ISRcnt_CAN8REC;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_CAN8TRX(void)
  {
    return RBSYS_ISRcnt_CAN8TRX;
  }
#endif


#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  uint32 GetPrivate_RBSYS_ISRcnt_RLIN30RX(void)
  {
    return RBSYS_ISRcnt_RLIN30RX;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_RLIN30STATUS(void)
  {
    return RBSYS_ISRcnt_RLIN30STATUS;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_RLIN31RX(void)
  {
    return RBSYS_ISRcnt_RLIN31RX;
  }

  uint32 GetPrivate_RBSYS_ISRcnt_RLIN31STATUS(void)
  {
    return RBSYS_ISRcnt_RLIN31STATUS;
  }
#endif


#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  uint32 GetPrivate_RBSYS_TASKcnt_x200bg_skippedActivation(void)
  {
    return RBSYS_TASKcnt_x200bg_skippedActivation;
  }
#endif

/********************************************************/
/*                Set private variables                 */
/********************************************************/


/********************************************************/
/*              Access private Functions                */
/********************************************************/

void CallPrivate_taskbody_prc_calls(const PRC_PTR proc_table[])
{
  taskbody_prc_calls(proc_table);
}

void CallPrivate_set_prclist_default(void)
{
  set_prclist_default();
}
