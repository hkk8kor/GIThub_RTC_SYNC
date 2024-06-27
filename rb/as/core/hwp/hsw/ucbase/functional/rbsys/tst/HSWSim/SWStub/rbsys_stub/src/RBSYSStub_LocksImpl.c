/**
 * @ingroup RBSYS
 * @{
 *
 * \file
 * \brief Lock implementation
 *
 * 'Detailed description of this module, several lines/paragraphes'
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* used interfaces */
//#include "RBSYS_Intrinsics.h"
//#include "RBSYS_SystemTimer.h"

#include "Os.h"  // tmp solution: use raw os intlocks


/* realized interfaces */
#include "RBSYS_LocksImpl.h"

#include "RBSYSStub_EntryPoint.h" ///< realize


/*
   ********** IMPORTANT *************
   **
   **   SuspendAllInterrupts  are not allowed to be used in Evo17/Gen10!!
   **   => not safe for Multi-Core systems => only the SYS lock API has to be used
   **
	 ********** IMPORTANT *************
*/


#if 0 // not sim
static uint32_t sys_lock_nesting_cnt;
static uint32_t sys_tmp_locktime;
static uint32_t sys_tmp_lockaddr;
#endif

uint32_t sys_max_locktime;
uint32_t sys_max_lockaddr;


/*
	- tmp solution: use raw OS locks with own nesting counter!! i.e. OS has own and this code ...
	- final impl. to be checked with new OS and MCore/spinlock features
	- info: OS works on PMR mask instead of ID-bit
*/
#define SuspendAllInterrupts Os_SuspendAllInterrupts
#define ResumeAllInterrupts Os_ResumeAllInterrupts

static uint32 rbsysStub_CommonLock_Count;
static uint32 rbsysStub_CoreLocalLock_Count;
static uint32 rbsysStub_CommonFastLock_Count;

void RBSYS_EnterCommonLock_intern(void)
{
  rbsysStub_CommonLock_Count++;

  #if 0
	unsigned int lp;

	lp = RBSYS_getLp();
	if (sys_lock_nesting_cnt == 0)
	{
    SuspendAllInterrupts(); // os uses own counter, so has to be called symetrically with ResumeInts
    sys_tmp_locktime = RBSYS_getRealtimeTickCtr();
		sys_tmp_lockaddr = lp;
	}
	sys_lock_nesting_cnt++;
  #endif
}

void RBSYS_ExitCommonLock_intern(void)
{
  #if 0
	sys_lock_nesting_cnt--;
	if (sys_lock_nesting_cnt == 0)
	{
		uint32_t new_time = RBSYS_getRealtimeTickCtr() - sys_tmp_locktime;
		if (new_time > sys_max_locktime)
		{
			sys_max_locktime = new_time;
			sys_max_lockaddr = sys_tmp_lockaddr;
		}
    ResumeAllInterrupts();
  }
  #endif
}

void RBSYS_EnterCorelocalIntlock_intern(void)
{
  rbsysStub_CoreLocalLock_Count++;
}

void RBSYS_ExitCorelocalIntlock_intern(void)
{
  // Nothing to do
}


void RBSYS_EnterCommonLockSysfast_intern(void)
{
  rbsysStub_CommonFastLock_Count++;

  #if 0
	if (sys_lock_nesting_cnt == 0)
	{
    SuspendAllInterrupts();
	}
	sys_lock_nesting_cnt++;
  #endif
}

void RBSYS_ExitCommonLockSysfast_intern(void)
{
  #if 0
	sys_lock_nesting_cnt--;
	if (sys_lock_nesting_cnt == 0)
	{
    ResumeAllInterrupts();
  }
  #endif
}



#define SYS_MAX_LOCKTIME_US  50

#if 0 ///< not used in sim
static void PRC_SYS_check_lock_state(void)
{
	if (sys_lock_nesting_cnt != 0)
	{
		// error: unbalanced: TODO: add DSM call with meaningful debug info
		SYS_SetFL();
	}

	if (sys_max_locktime > (SYS_MAX_LOCKTIME_US*RBSYS_TIMERTICKS_PER_US))
	{
	  // error: too long: TODO: add DSM call with meaningful debug info
		SYS_SetFL();
	}
}
#endif


/** @} */
/* End ingroup RBSYS */
