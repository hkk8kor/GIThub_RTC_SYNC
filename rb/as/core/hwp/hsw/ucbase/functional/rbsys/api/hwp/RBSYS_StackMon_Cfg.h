#ifndef RBSYS_STACKMON_CFG_H__
#define RBSYS_STACKMON_CFG_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Stack monitoring config
 *
 * This interface provides the configuration for CUBAS stack monitoring module rba_MultiStackTrace
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_CpuInfo.h"
#include "../../src/Monitorings/RBSYS_StackHandling.h"


RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);



//Set to STD_ON if this module has to be enabled, else STD_OFF
#define RBSYS_RBA_MULTISTACKTRACE_CFG_ENABLE          STD_ON    // checkword test
#define RBSYS_RBA_MULTISTACKTRACE_CFG_ENABLETRACE     STD_ON    // fill level
#define RBSYS_RBA_MULTISTACKTRACE_CFG_PATTERNINIT     STD_OFF   // init with DEFAULTFILLUPVALUE not required due HW RAM zeroing

#define RBSYS_RBA_MULTISTACKTRACE_CFG_DEFAULTFILLUPVALUE ((uint32)0x0)  // "FILL"  => must be set to 0 in case of HW zeroing and _PATTERNINIT = _OFF
#define RBSYS_RBA_MULTISTACKTRACE_CFG_LIMITHIGH          ((uint32)0x3179656B)  // "key1" for checkword test
#define RBSYS_RBA_MULTISTACKTRACE_CFG_LIMITLOW           ((uint32)0x3279656B)  // "key2"



#if (RBFS_MCORE == RBFS_MCORE_OFF)
  #define RBSYS_NUMBER_OF_STACKS   (1)
#else
  #define RBSYS_NUMBER_OF_STACKS   (2)
#endif



#define RBSYS_Stack0_StackId     (0)
#define RBSYS_Stack0_CoreId      ((uint32)RBSYS_CORE_ID_0)
#define RBSYS_Stack0_Start       ((uint32*)&RB_Stack0_FSW[RB_STACK0_START])
#define RBSYS_Stack0_End         ((uint32*)&RB_Stack0_FSW[RB_STACK_LOWCHK0])
#define RBSYS_Stack0_Limit0      ((uint32*)&RB_Stack0_FSW[RB_STACK_LOWCHK0])
#define RBSYS_Stack0_Limit1      ((uint32*)&RB_Stack0_FSW[RB_STACK_LOWCHK1])
#define RBSYS_Stack0_Limit2      ((uint32*)&RB_Stack0_FSW[RB_STACK0_UPPERCHK])  // _Limit may not be equal to _Start


#if (RBFS_MCORE == RBFS_MCORE_OFF)

  #define RBSYS_Stack1_StackId
  #define RBSYS_Stack1_CoreId
  #define RBSYS_Stack1_Start
  #define RBSYS_Stack1_End
  #define RBSYS_Stack1_Limit0
  #define RBSYS_Stack1_Limit1
  #define RBSYS_Stack1_Limit2

#else

  #define RBSYS_Stack1_StackId     (1)
  #define RBSYS_Stack1_CoreId      ((uint32)RBSYS_CORE_ID_1)
  #define RBSYS_Stack1_Start       ((uint32*)&RB_Stack1_FSW[RB_STACK1_START])
  #define RBSYS_Stack1_End         ((uint32*)&RB_Stack1_FSW[RB_STACK_LOWCHK0])
  #define RBSYS_Stack1_Limit0      ((uint32*)&RB_Stack1_FSW[RB_STACK_LOWCHK0])
  #define RBSYS_Stack1_Limit1      ((uint32*)&RB_Stack1_FSW[RB_STACK_LOWCHK1])
  #define RBSYS_Stack1_Limit2      ((uint32*)&RB_Stack1_FSW[RB_STACK1_UPPERCHK])

#endif





/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
