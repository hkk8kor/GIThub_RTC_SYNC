#ifndef RBSYS_LOCKSIMPL_H__
#define RBSYS_LOCKSIMPL_H__

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




/* no other includes allowed --> see RBCMHSW_Locks.h */



/* internal implementation within RBSYS_LocksImplIntern.h */
extern void RBSYS_EnterCommonLock_intern(void);
extern void RBSYS_ExitCommonLock_intern(void);
extern void RBSYS_EnterCorelocalIntlock_intern(void);
extern void RBSYS_ExitCorelocalIntlock_intern(void);
/* to be used RBSYS internally only! for small RBSYS services; ToDo: to be reworked with MCore support */
extern void RBSYS_EnterCommonLockSysfast_intern(void);
extern void RBSYS_ExitCommonLockSysfast_intern(void);
extern void RBSYS_EnterCorelocalIntlockSysfast_intern(void);
extern void RBSYS_ExitCorelocalIntlockSysfast_intern(void);


/*
   ********** IMPORTANT *************
   **
   **   SuspendAllInterrupts are not allowed to be used in Gen9.3!!
   **   => not safe for Multi-Core systems => only the SYS lock API has to be used
   **
   ********** IMPORTANT *************
*/



/** Map common lock to implementation in RBSYS */
__attribute__((always_inline)) static inline void RBSYS_EnterCommonLock(void)
{
  RBSYS_EnterCommonLock_intern();
}
__attribute__((always_inline)) static inline void RBSYS_ExitCommonLock(void)
{
  RBSYS_ExitCommonLock_intern();
}


/** Map core local interrupt lock to implementation in RBSYS */
__attribute__((always_inline)) static inline void RBSYS_EnterCorelocalIntlock(void)
{
  RBSYS_EnterCorelocalIntlock_intern();
}
__attribute__((always_inline)) static inline void RBSYS_ExitCorelocalIntlock(void)
{
  RBSYS_ExitCorelocalIntlock_intern();
}


/** Map special fast lock to implementation in RBSYS - only for RBSYS internal services */
__attribute__((always_inline)) static inline void RBSYS_EnterCommonLockSysfast(void)
{
  RBSYS_EnterCommonLockSysfast_intern();
}
__attribute__((always_inline)) static inline void RBSYS_ExitCommonLockSysfast(void)
{
  RBSYS_ExitCommonLockSysfast_intern();
}

/** Map special fast core local interrupt lock to implementation in RBSYS - only for RBSYS/uC safety specific services */
__attribute__((always_inline)) static inline void RBSYS_EnterCorelocalIntlockSysfast(void)
{
  RBSYS_EnterCorelocalIntlockSysfast_intern();
}
__attribute__((always_inline)) static inline void RBSYS_ExitCorelocalIntlockSysfast(void)
{
  RBSYS_ExitCorelocalIntlockSysfast_intern();
}





// TODO: if nonest locks are really needed, adapt internal logic to check for right locking order
// i.e. only nonest after common lock, no lock following a nonest
//static inline void RBSYS_EnterNonestLock(volatile lockstr_t* lock)
//{
//  RBSYS_EnterNonestLock_intern(lock);
//}

//static inline void RBSYS_ExitNonestLock(volatile lockstr_t* lock)
//{
//  RBSYS_ExitNonestLock_intern(lock);
//}





/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
