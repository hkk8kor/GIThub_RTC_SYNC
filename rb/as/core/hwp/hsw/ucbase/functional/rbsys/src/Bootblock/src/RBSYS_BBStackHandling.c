/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Stack handling for bootblock
 *
 * Stack handling and allocation of bootblock software. Stack size must be a part of project specific configuration.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBLCF_MemoryRemap.h"


/* realized interfaces */
#include "RBSYS_BBStackHandling.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysBootblockBuild,
                          RBFS_SysBootblockBuild_Active,
                          RBFS_SysBootblockBuild_NotActive);

RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);




#if (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active)

  RBSECTION_START_STACK_CPU0_NOCLEAR
  static volatile unsigned int RB_Stack0_Bootblock[RB_STACK_SIZE_BOOTBLOCK/4];     // stack for core 0
  RBSECTION_END_STACK_CPU0_NOCLEAR

  /* place pointer in .text to have it before c-init is done */
  RBSECTION_START_SECTTYPE_NO_SDA
  volatile unsigned int* const RB_SP0_Bootblock = &RB_Stack0_Bootblock[(RB_STACK_SIZE_BOOTBLOCK/4)-1];
  RBSECTION_END_SECTTYPE_NO_SDA


  #if (RBFS_MCORE == RBFS_MCORE_ON)

    RBSECTION_START_STACK_CPU1_NOCLEAR
    static volatile unsigned int RB_Stack1_Bootblock[RB_STACK_SIZE_BOOTBLOCK/4];   // stack for core 1
    RBSECTION_END_STACK_CPU1_NOCLEAR

    RBSECTION_START_SECTTYPE_NO_SDA
    volatile unsigned int* const RB_SP1_Bootblock = &RB_Stack1_Bootblock[(RB_STACK_SIZE_BOOTBLOCK/4)-1];
    RBSECTION_END_SECTTYPE_NO_SDA

  #else  // set stackpointer 1 to be FS independent in .850 CPUInit file

    RBSECTION_START_SECTTYPE_NO_SDA
    volatile unsigned int* const RB_SP1_Bootblock = &RB_Stack0_Bootblock[(RB_STACK_SIZE_BOOTBLOCK/4)-1];
    RBSECTION_END_SECTTYPE_NO_SDA

  #endif

#endif  // (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active)




/** @} */
/* End ingroup RBSYS */
