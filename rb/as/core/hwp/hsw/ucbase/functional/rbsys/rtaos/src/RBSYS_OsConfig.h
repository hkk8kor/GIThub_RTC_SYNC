#ifndef RBSYS_OSCONFIG_H__
#define RBSYS_OSCONFIG_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief RBSYS relevant OS configuration
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"
#include "Os.h"
#include "RBSYS_OsServices.h"


/* used interfaces */


/* Assert supported configurations: switches, parameters, constants, ... */

RB_ASSERT_SWITCH_SETTINGS(RBFS_HSWSimulation,
                          RBFS_HSWSimulation_OFF,
                          RBFS_HSWSimulation_ON);

#if( RBFS_HSWSimulation == RBFS_HSWSimulation_OFF )

  RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                            RBFS_uCFamily_RenesasP1x,
                            RBFS_uCFamily_RenesasU2A,
                            RBFS_uCFamily_RenesasU2C,
                            RBFS_uCFamily_STMStellar);
  RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                            RBFS_MCORE_ON,
                            RBFS_MCORE_OFF);

  /************************************************************************************************/
  /* The declarations below are required for OS callbacks to                                      */
  /*   - avoid MisraC2012-8.4 "Missing declaration for function definition"                       */
  /*   - suppress GHS compiler diagnostic #1800-D "function defined without a prototype"          */
  /*                                                                                              */
  /* Hint: All declarations below must be reviewed after each OS update.                          */
  /************************************************************************************************/



  #if (RBFS_MCORE == RBFS_MCORE_ON)
    /** @brief Encapsulation for Os_*AwaitStartup (difference in naming between Renesas and STM port)
      * todo: Remove this once common API is provided by OS                                         */
    static inline void RBSYS_Os_AwaitStartup(void)
    {
      #if(( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
        (void)Os_AwaitStartup();
      #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        Os_StartCoreGate();
      #else
        #error ("Select correct Os_AwaitStartup API to be used for this OS port")
      #endif
    }
  #endif
#endif //< RBFS_HSWSimulation_ON

/**
  * @brief  Set the current RBSYS Operation Mode {PreInit, Init, Cyclic} once a transition to a new phase has happened.
  *
  * Attention: This API may only be used RBSYS-internally!
  *
  * @param Current RBSYS Operation Mode [RBSYS_OperationMode_n]
  */
extern void RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_n mode);


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
