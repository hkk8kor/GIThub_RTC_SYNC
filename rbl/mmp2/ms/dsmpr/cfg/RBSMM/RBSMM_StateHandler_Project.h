#ifndef RBSMM_STATEHANDLER_PROJECT_H__
#define RBSMM_STATEHANDLER_PROJECT_H__

/**********************************************************************************/
/* [COPYRIGHT]                                                                    */
/* Robert Bosch GmbH reserves all rights even in the event of industrial          */
/* property rights. We reserve all rights of disposal such as copying and         */
/* passing on to third parties.                                                   */
/* [COPYRIGHT_END]                                                                */
/**********************************************************************************/

#include "RBSMM.h"

#if (RBFS_SystemModeManager == RBFS_SystemModeManager_Yes)

/******************************************************************************/
/* constant definitions for customer specific delay times  */
/******************************************************************************/
/* minimum stay time in NET_OFF during shutdown.
 * formular: (x msec/10 msec)
 * Default: 0 msec
 * */
#define  C_MinAlivetimeNetOff        ((uint32)(0/10))

/* minimum stay time in NET_ON
 * formular: (x msec/10 msec)
 * Default: 0 msec
 * */
#define  C_MinAlivetimeNetOn         ((uint32)(0/10))

/* minimum degrade time of ASW if request < NORMAL
 * formular: (x msec/10 msec)
 * Default: 500 msec
 * */
#define  C_MinDelayActivationOfASW   ((uint16)(500/10))

#define STATEHANDLER_CALLBACK_INTERFACE_V9_3
/******************************************************************************/
/* function implemented customer specific to make the RBSMM more flexible for   */
/* parameter handling                                                         */
/******************************************************************************/

LOCAL_INLINE boolean RBSMM_StateHandler__ModeTransitionAllowed(void)
{
	boolean ModeTransitionAllowed = FALSE;

	/* ModeTransitionAllowed can be manipulated project specific */
	/* if (condition_PRJ && (RBSMM_StateHandler__getSystemModeAliveTime == 0)) ModeTransitionAllowed=TRUE; */
	/* Review 207068
	   Finding : Issue No. 007
	   Fix : Addition of new public interface for checking SystemModeAliveTime expiry
	*/
	ModeTransitionAllowed = RBSMM_StateHandler__SystemModeAliveTimeExpired();

	return ModeTransitionAllowed;
}
/*****************************************************************/
/* state transition callbacks                                    */
/*****************************************************************/

// All generic hooks are moved to a productline specific part of the RBSMM configuration
/* callback function at transition from NET_ON to NORMAL*/
LOCAL_INLINE void RBSMM_StateHandler__Transition_NetOn_Normal_Prj(void)
{

}

/* callback function at transition from NET_ON to NET_OFF*/
LOCAL_INLINE void RBSMM_StateHandler__Transition_NetOn_NetOff_Prj(void)
{

}

/* callback function at transition from NORMAL to NET_ON*/
LOCAL_INLINE void RBSMM_StateHandler__Transition_Normal_NetOn_Prj(void)
{

}


/* callback function at transition from NET_OFF to OFF*/
LOCAL_INLINE void RBSMM_StateHandler__Transition_NetOff_Off_Prj(void)
{

}

/* callback function at transition from NET_OFF to NET_ON*/
LOCAL_INLINE void RBSMM_StateHandler__Transition_NetOff_NetOn_Prj(void)
{

}
/* callback function at transition from INIT to NET_OFF */
LOCAL_INLINE void RBSMM_StateHandler__Transition_Init_NetOff_Prj(void)
{
}
LOCAL_INLINE void RBSMM_StateHandler__Transition_Off_NetOff_Prj(void)
{

}
/* callback functions for system submode transitions */
LOCAL_INLINE void RBSMM_StateHandler__Transition_HWOff_PrepareHWOff_Prj(void)
{
}

LOCAL_INLINE void RBSMM_StateHandler__Transition_PrepareHWOff_CtrlOff_Prj(void)
{
}

LOCAL_INLINE void RBSMM_StateHandler__Transition_PrepareHWOff_HWOff_Prj(void)
{
}

LOCAL_INLINE void RBSMM_StateHandler__Transition_CtrlOff_PrepareHWOff_Prj(void)
{
}
// if no productline specfic callback is defined the project specific hook can mapped to generic callback
// note: generic callbacks of the productline implementation always  call the project specific hook
// these defines can also be used if no projectline specific hook is defined.

/* Misra Rule 8.10 An inline function shall be declared with the static storage class
   Misra Rule Rule 8.8 The static storage class specifier shall be used in all declarations of objects and
   functions that have internal linkage

   Fix : Macros for project specific SMM transitions are removed from RBSMM_StateHandler_Project.h
   Refer RBSMM_StateHandler_PL.h for further details
 */
#endif
#endif

