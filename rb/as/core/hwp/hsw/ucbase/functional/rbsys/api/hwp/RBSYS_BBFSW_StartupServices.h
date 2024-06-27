#ifndef RBSYS_BBFSW_STARTUPSERVICES_H__
#define RBSYS_BBFSW_STARTUPSERVICES_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Provides interfaces to BB<->FSW BackupRAM
 *
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_Intrinsics.h"
#include "RBLCF_MemoryRemap.h"
#include "RBSYS_uCRegisters.h"
#include "RB_MemoryBarrier.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysBootblockSupport,
                          RBFS_SysBootblockSupport_OFF,
                          RBFS_SysBootblockSupport_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_pTSWSupport,
                          RBFS_pTSWSupport_ON,
                          RBFS_pTSWSupport_OFF);
RB_ASSERT_SWITCH_SETTINGS(RBFS_BackdoorBootblock,
                          RBFS_BackdoorBootblock_NO,
                          RBFS_BackdoorBootblock_YES);
RB_ASSERT_SWITCH_SETTINGS(RBFS_BackupRAMLayout,
                          RBFS_BackupRAMLayout_Legacy,
                          RBFS_BackupRAMLayout_V1);



/* --------------------------------------------------------------------- */
/* ---------- Handling of BB FSW INTERFACE Backup RAM area ------------- */
/* --------------------------------------------------------------------- */

/** -----------------------------ATTENTION-----------------------------
  * Do not change the following patterns. They may be used independently from 
  * Application SW in the Bootblock and may then differ. E.g. Reprogramming
  * may then no longer be possible.
  * ------------------------------------------------------------------- */

/* Keys for Bootblock request - must be stored over SW reset within BB FSW INTERFACE Backup RAM area */
#define RBSYS_SKIP_BOOTBLOCK                (0xAAAAAAAAu)   // Bootblock or FSW triggers reset, which jumps directly to FSW

#if (RBFS_SysBootblockSupport == RBFS_SysBootblockSupport_ON)
  #define RBSYS_BB_RUN_BOOTBLOCK            (0x55555555u)   // Bootblock triggers reset to Bootblock

  #define RBSYS_FSW_RUN_RB_BOOTBLOCK        (0x12345678u)   // FSW triggers reset to RB Bootblock
  #define RBSYS_FSW_RUN_OEM_BOOTBLOCK       (0x00000000u)   // FSW triggers reset to OEM Bootblock

  // deprecated macro RBSYS_FSW_RUN_BOOTBLOCK required for backwards compatibility
  #define RBSYS_FSW_RUN_BOOTBLOCK           RBSYS_FSW_RUN_OEM_BOOTBLOCK
#endif



#if (RBFS_pTSWSupport == RBFS_pTSWSupport_ON)
  #define RBSYS_SKIP_TCSW                   (0x00000000u)   // skip TC-SW and run ePSW
  #define RBSYS_RUN_TCSW                    (0x12344321u)   // run TC-SW and skip ePSW
#endif


#if (RBFS_BackdoorBootblock == RBFS_BackdoorBootblock_YES)
  #define RBSYS_ASIC_IN_TESTMODE            (0xBA5E0511u)   // Asic has come up in Testmode
  #define RBSYS_ASIC_NOT_IN_TESTMODE        (0x00000000u)   // Asic has not come up in Testmode
#endif


/*
 * Memory section BURAM_BB_FSW_INTERFACE within linker directive file is a special Backup RAM area
 * required for sharing data between BB and FSW. Therefore this structure must be fix
 * due to independent updates of BB and/or FSW
 */
#if( RBFS_BackupRAMLayout == RBFS_BackupRAMLayout_Legacy )

  typedef struct
  {
    uint32 BootblockRequest;

    #if (RBFS_pTSWSupport == RBFS_pTSWSupport_ON)
      uint32 TCSWStartupRequest;
    #endif

    #if (RBFS_BackdoorBootblock == RBFS_BackdoorBootblock_YES)
      uint32 BaseOsRequest;
    #endif
  } RBSYS_BURAM_BB_FSW_INTERFACE_t;

#elif( RBFS_BackupRAMLayout == RBFS_BackupRAMLayout_V1 )

  typedef struct
  {
    /** Attention: When adding / removing items from BURAM interface, address of existing items should remain same */
    /* Address 0x0 */
    uint32 BootblockRequest;

    /* Address 0x4 */
    #if (RBFS_pTSWSupport == RBFS_pTSWSupport_ON)
      uint32 TCSWStartupRequest; //< Use only if RBFS_pTSWSupport_ON
    #else
      uint32 reserved1;
    #endif

    /* Address 0x8 */
    #if (RBFS_BackdoorBootblock == RBFS_BackdoorBootblock_YES)
      uint32 BaseOsRequest;      //< Use only if RBFS_BackdoorBootblock_YES
    #else
      uint32 reserved2;
    #endif

    /* Address 0xC */
    uint32 ResetFlags;           //< Central Reset Information for RBSYS-only, shall be copied to FSW-BURAM for client use

    /* Address 0x10 */
    uint32 uCSafetyNotificationData[4]; //< 4 x 4Byte general purpose memory for storing RBECM's uCSafetyNotification Information for Application

  } RBSYS_BURAM_BB_FSW_INTERFACE_t;

#endif


RBSECTION_START_BURAM_BB_FSW_INTERFACE_BSS_NOCLEAR
extern volatile RBSYS_BURAM_BB_FSW_INTERFACE_t RBSYS_BURAM_BB_FSW_INTERFACE;
RBSECTION_END_BURAM_BB_FSW_INTERFACE_BSS_NOCLEAR


/**
 * @brief setBootblockRequest
 *
 * @param request [in] #RBSYS_SKIP_BOOTBLOCK if Bootblock must be skipped,
 *         otherwise #RBSYS_BB_RUN_BOOTBLOCK or #RBSYS_FSW_RUN_BOOTBLOCK (==#RBSYS_FSW_RUN_OEM_BOOTBLOCK) / #RBSYS_FSW_RUN_RB_BOOTBLOCK depending on context who triggers the reset with Bootblock for which intent
 *
 * @return void
 */
static inline void RBSYS_setBootblockRequest(uint32 request)
{
  RBSYS_BURAM_BB_FSW_INTERFACE.BootblockRequest = request;

  // sync instruction to ensure write back to Backup RAM before triggering SW reset
  RB_FullHardwareMemoryBarrier();
}


/**
 * @brief getBootblockRequest
 *
 * @return #RBSYS_SKIP_BOOTBLOCK if Bootblock must be skipped,
 *         otherwise #RBSYS_BB_RUN_BOOTBLOCK or #RBSYS_FSW_RUN_BOOTBLOCK(==#RBSYS_FSW_RUN_OEM_BOOTBLOCK) / #RBSYS_FSW_RUN_RB_BOOTBLOCK depending on context who triggers the reset with Bootblock for which intent
 */
static inline uint32 RBSYS_getBootblockRequest(void)
{
  return RBSYS_BURAM_BB_FSW_INTERFACE.BootblockRequest;
}


#if (RBFS_pTSWSupport == RBFS_pTSWSupport_ON)

  /**
   * @brief setTCSWStartupRequest
   *
   * @param request [in] RBSYS_SKIP_TCSW if test software for HU plant (TC-SW) must be skipped,
   *         otherwise #RBSYS_RUN_TCSW to run the TC-SW after SW reset.
   *
   * @return void
   */
  static inline void RBSYS_setTCSWStartupRequest(uint32 request)
  {
    RBSYS_BURAM_BB_FSW_INTERFACE.TCSWStartupRequest = request;

    // sync instruction to ensure write back to Backup RAM before triggering SW reset
    RB_FullHardwareMemoryBarrier();
  }


  /**
   * @brief getTCSWStartupRequest
   *
   * @return the TC-SW start-up context requested by application:
   *         #RBSYS_SKIP_TCSW if test software for HU plant (TC-SW) must be skipped,
   *         otherwise #RBSYS_RUN_TCSW to run the TC-SW after SW reset.
   */
  static inline uint32 RBSYS_getTCSWStartupRequest(void)
  {
    return RBSYS_BURAM_BB_FSW_INTERFACE.TCSWStartupRequest;
  }

#endif


#if (RBFS_BackdoorBootblock == RBFS_BackdoorBootblock_YES)

  /**
   * @brief setBaseOsRequest
   *
   * @param request [in] #RBSYS_ASIC_IN_TESTMODE if in a backdoor bootblock configuration the Asic has come up
   *         with active testmode. To reset it (which is also the startup default of 0) the value #RBSYS_ASIC_NOT_IN_TESTMODE is used.
   *
   * @return void
   */
  static inline void RBSYS_setBaseOsRequest(uint32 request)
  {
    RBSYS_BURAM_BB_FSW_INTERFACE.BaseOsRequest = request;

    // sync instruction to ensure write back to Backup RAM before triggering SW reset
    RB_FullHardwareMemoryBarrier();
  }


  /**
   * @brief getBaseOsRequest
   *
   * @return the Testmode indication for the Asic which must be saved in a backdoor bootblock configuration
   *         so that it is not lost by the reset required to leave the Backdoor bootloader.
   */
  static inline uint32 RBSYS_getBaseOsRequest(void)
  {
    return RBSYS_BURAM_BB_FSW_INTERFACE.BaseOsRequest;
  }

#endif

#if( RBFS_BackupRAMLayout == RBFS_BackupRAMLayout_V1 )
  /**
    * @brief Write data into uCSafetyNotificationData storage for Application
    * 
    * Hint: Shall normally only be used in Bootloader.
    * @return void
    */
  static inline void RBSYS_SetuCSafetyNotificationData_ByIndex(uint32 index, uint32 data)
  {
    assert(index < 4);
    RBSYS_BURAM_BB_FSW_INTERFACE.uCSafetyNotificationData[index] = data;
  }

  /**
    * @brief Read data from uCSafetyNotificationData storage in Application
    * 
    * Hint: Shall normally only be used in Application.
    * @return uint32 data
    */
  static inline uint32 RBSYS_GetuCSafetyNotificationData_ByIndex(uint32 index)
  {
    assert(index < 4);
    return RBSYS_BURAM_BB_FSW_INTERFACE.uCSafetyNotificationData[index];
  }
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
