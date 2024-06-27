/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief OS sanity checks

 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include <assert.h>           // for static_assert()

/* include OS headers (Os.h, Os_ConfigInterrupts.h) and compiler headers (v800_ghs.h, ghs_barrier.h)
 * to verify compiler function declaration used directly within OS. OS per guidline will not include
 * the compiler headers and therefore this sanity check is required to identify a mismatch by the
 * used OS intrinsics
 *
 * This is ensured by GHS compiler diagnostic #147 (not_compatible_with_previous_decl)
 * => declaration is incompatible with entity-kind "entity"
 */
#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  #include <v800_ghs.h>
#elif (RBFS_uCFamily == RBFS_uCFamily_STMStellar)
  #include <arm_ghs.h>
#endif
#include <ghs_barrier.h>
#include "Os.h"
#include "Os_ConfigInterrupts.h"
#include "RBSYS_OsServices.h"
#include "RBSYS_CpuInfo.h"

/* realized interfaces */

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSchemeExtension,
                          RBFS_TaskSchemeExtension_None,
                          RBFS_TaskSchemeExtension_VMPS,
                          RBFS_TaskSchemeExtension_HostCore0GuestCore1,
                          RBFS_TaskSchemeExtension_AB15);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTPSWSupport,
                          RBFS_SysTPSWSupport_YES,
                          RBFS_SysTPSWSupport_NO);
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTask0p5ms,
                          RBFS_SysTask0p5ms_ON,
                          RBFS_SysTask0p5ms_OFF);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysFlxrTask,
                          RBFS_SysFlxrTask_ON,
                          RBFS_SysFlxrTask_OFF);


/* Sanity check for OS lib to ensure consistency between OS and standard platform typedefs. */
static_assert( sizeof(uint8_least)  == sizeof(unsigned long), "OS used typedef must fit to standard platform typedef");
static_assert( sizeof(uint16_least) == sizeof(unsigned long), "OS used typedef must fit to standard platform typedef");
static_assert( sizeof(uint32_least) == sizeof(unsigned long), "OS used typedef must fit to standard platform typedef");
static_assert( sizeof(sint8_least)  == sizeof(signed long), "OS used typedef must fit to standard platform typedef");
static_assert( sizeof(sint16_least) == sizeof(signed long), "OS used typedef must fit to standard platform typedef");
static_assert( sizeof(sint32_least) == sizeof(signed long), "OS used typedef must fit to standard platform typedef");



/* NO_TOOL_SCAN */
/* REASON: GenProDB requires RBFS_ function switch in #if condition */

#if ((OS_CORE_ID_0 != 0U) || (OS_CORE_ID_1 != 1U))
  #error ("OS_CORE_ID will not match with expected core id!")
#endif

#if ((RBSYS_CORE_ID_0 != 0U) || (RBSYS_CORE_ID_1 != 1U))
  #error ("RBSYS_CORE_ID will not match with expected core id!")
#endif

#if (RB_NUM_CORES != OS_NUM_CORES)
  #error ("OS_NUM_CORES will not match with expected RB_NUM_CORES!")
#endif

#if(RBFS_MCORE == RBFS_MCORE_ON)
  #if (OS_CORE_FOR_TaskInit == OS_CORE_FOR_TaskInitP)
    #error ("Tasks Init and InitP must be executed on different cores!")
  #endif

  #if (OS_CORE_FOR_TaskBaseCtrlCycx2 == OS_CORE_FOR_TaskBaseCtrlCycx2p)
    #error ("Tasks x2 and x2p must be executed on different cores!")
  #endif

  #if ((RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS) || (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1))
    #if ((RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON) && (OS_CORE_FOR_Task0p5ms != OS_CORE_ID_0))
      #error ("Task 500us must be executed on core 0!")
    #endif
    #if (OS_CORE_FOR_Task1ms != OS_CORE_ID_0)
      #error ("Task 1ms must be executed on core 0!")
    #endif
    #if (OS_CORE_FOR_TaskBaseCtrlCycx1High != OS_CORE_ID_0)
      #error ("Task x1High must be executed on core 0!")
    #endif
    #if ((RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON) && (OS_CORE_FOR_TaskFlexray != OS_CORE_ID_0))
      #error ("Task Flexray must be executed on core 0!")
    #endif
    #if (OS_CORE_FOR_TaskBaseCtrlCycx1Low != OS_CORE_ID_0)
      #error ("Task x1Low must be executed on core 0!")
    #endif
    #if (OS_CORE_FOR_TaskBaseCtrlCycx2 != OS_CORE_ID_0)
      #error ("Task x2 must be executed on core 0!")
    #endif
    #if (OS_CORE_FOR_TaskBaseCtrlCycx2p != OS_CORE_ID_1)
      #error ("Task x2p must be executed on core 1!")
    #endif
    #if (OS_CORE_FOR_TaskBaseCtrlCycx4 != OS_CORE_ID_0)
      #error ("Task x4 must be executed on core 0!")
    #endif
    #if (OS_CORE_FOR_TaskBaseCtrlCycx8 != OS_CORE_ID_0)
      #error ("Task x8 must be executed on core 0!")
    #endif
    #if (OS_CORE_FOR_TaskBaseCtrlCycx24 != OS_CORE_ID_0)
      #error ("Task x24 must be executed on core 0!")
    #endif
  #endif

  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
    #if (OS_CORE_FOR_TaskBaseCtrlCycx4 == OS_CORE_FOR_TaskBaseCtrlCycx4pLow)
      #error ("Tasks x4 and x4pLow must be executed on different cores!")
    #endif
  #endif

  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
    #if (OS_CORE_FOR_TaskBaseCtrlCycx1Guest != OS_CORE_ID_1)
      #error ("Task x1Guest must be executed on core 1!")
    #endif
    #if (OS_CORE_FOR_TaskBaseCtrlCycx2Guest != OS_CORE_ID_1)
      #error ("Task x2Guest  must be executed on core 1!")
    #endif
    #if (OS_CORE_FOR_TaskBaseCtrlCycx4Guest != OS_CORE_ID_1)
      #error ("Task x4Guest  must be executed on core 1!")
    #endif
    #if (OS_CORE_FOR_TaskBaseCtrlCycx10Guest != OS_CORE_ID_1)
      #error ("Task x10Guest  must be executed on core 1!")
    #endif
    #if (OS_CORE_FOR_TaskBaseCtrlCycx20Guest != OS_CORE_ID_1)
      #error ("Task x20Guest  must be executed on core 1!")
    #endif
  #endif

  #if(RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)
    #if (OS_CORE_FOR_TaskTPSWKillCore0 != OS_CORE_ID_0)
      #error ("Task TPSWKillCore0 must be executed on core 0!")
    #endif

    #if (OS_CORE_FOR_TaskTPSWKillCore1 != OS_CORE_ID_1)
      #error ("Task TPSWKillCore1 must be executed on core 1!")
    #endif
  #endif
#endif

/* NO_TOOL_SCAN_END */

/** @} */
/* End ingroup RBSYS */

