#ifndef RBSYS_MULTICORESYNC_H__
#define RBSYS_MULTICORESYNC_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Synchronization for MultiCore
 *
 * In Multi-Core systems it is necessary to synchronize cores in different situations.
 * Therefore this general barrier synchronization is provided.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBLCF_MemoryRemap.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);


#if (RBFS_MCORE == RBFS_MCORE_ON)  /* in case of single core systems, sync functionality is not required */

  static_assert(RB_NUM_CORES <= 2, "RBSYS_MultiCoreSync only supports 2 cores");

  typedef struct
  {
    volatile uint8* ptr[RB_NUM_CORES];
  } RBSYS_SyncPhaseCounter_t;


  /**
   * @brief Public macros for defining the structure used for SyncBarriers.
   *
   * This structure is always static and the used counters can be located in either Global RAM (GRAM or CRAM) or LRAM.
   * Counters located in LRAM have the advantage, that bus traffic is minimized for the waiting core
   * as it can poll its own LRAM.
   *
   * Example:
   *    typedef enum
   *    {
   *      phase1 = 0,
   *      phase2,
   *      maxNumberOfPhases
   *    } myPhases_t;
   *    RBSYS_MULTICORESYNC_DEFINE_SYNCPHASES_GRAM(mySyncStruct, maxNumberOfPhases)
   *    void functionCore0()
   *    {
   *      RBSYS_SyncBarrier(&mySyncStruct, phase1);
   *    }
   *    void functionCore1()
   *    {
   *      RBSYS_SyncBarrier(&mySyncStruct, phase1);
   *    }
   *
   */

  #define RBSYS_MULTICORESYNC_DEFINE_SYNCPHASES_LRAM(name, numberOfPhases)\
    RBSECTION_START_LRAM1_BSS_NOCLEAR\
    static volatile uint8 name##_Core0_counter[numberOfPhases];\
    RBSECTION_END_LRAM1_BSS_NOCLEAR\
    \
    RBSECTION_START_LRAM0_BSS_NOCLEAR\
    static volatile uint8 name##_Core1_counter[numberOfPhases];\
    RBSECTION_END_LRAM0_BSS_NOCLEAR\
    \
    static const RBSYS_SyncPhaseCounter_t name = { {&name##_Core0_counter[0], &name##_Core1_counter[0]} }

  #define RBSYS_MULTICORESYNC_DEFINE_SYNCPHASES_GRAM(name, numberOfPhases)\
    RBSECTION_START_GRAM_BSS_NOCLEAR\
    static volatile uint8 name##_Core0_counter[numberOfPhases];\
    static volatile uint8 name##_Core1_counter[numberOfPhases];\
    RBSECTION_END_GRAM_BSS_NOCLEAR\
    \
    static const RBSYS_SyncPhaseCounter_t name = { {&name##_Core0_counter[0], &name##_Core1_counter[0]} }


  /**
   * @brief Synchronization mechanism for MultiCore
   *
   * If one core reached a synchronization barrier it must be ensured that the other core will also
   * reach this position before both could continue. Each core writes its own arrived status and then
   * polls the arrived status from the other core.
   *
   * Attention: Feature can be used during startup and in cyclic phase but usage of this
   *            synchronization functionality must be discussed with RBSYS responsible.
   *
   * Hint: To minimize the bus traffic use *LRAM* macros, then each core will poll the
   * arrived status from the other core in its own local RAM. This means that each core must
   * write to its arrived status variable in the local RAM of the foreign core.
   * Hint: Only allowed to be called after RBSYS_InitMultiCoreSync() is executed!
   * Hint: In case of single core systems, sync functionality will be optimized away.
   *       So it is not required to use function switch "RBFS_MCORE" for calling this function.
   *
   * @param syncphases is a pointer to the struct created with the macros above
   * @param phase is the next synchronization barrier
   *
   * @return void
   */
  extern void RBSYS_SyncBarrier(const RBSYS_SyncPhaseCounter_t* syncphases, uint8 phase);

#else
  // For single core build configurations map this function empty
  #define RBSYS_SyncBarrier(syncphases, value)
#endif

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
