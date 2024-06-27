#ifndef RBSYS_PLANTSTARTUPCTRL_H__
#define RBSYS_PLANTSTARTUPCTRL_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Interface to influence the startup flow dependent on the start-up request
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */
#include "RBSYS_Config.h"


/* used interfaces */


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_ReprogDriverSupport,
                          RBFS_ReprogDriverSupport_ON,
                          RBFS_ReprogDriverSupport_OFF);



#define RBSYS_BaseOSRequest                 (0xABCDABCDu)
#if(RBFS_ReprogDriverSupport == RBFS_ReprogDriverSupport_ON)
  #define RBSYS_ReprogRequest               (0xDCBADBCAu)
#endif
#define RBSYS_Vx1000ReprogRequested         (0xbcda1000u)
#define RBSYS_Vx1000ParHandlingRequested    (0xbcda2000u)
#define RBSYS_DefaultOSRequest              (0x00000000u)




// originator of a SW-triggered reset is FSW
#define RBSYS_SKIP_BOOTBLOCKTrigbyFSW       (0xFFA5FFA5u)   // FSW triggers reset, which jumps directly to FSW
#define RBSYS_WITH_BOOTBLOCKTrigbyFSW       (0x00000000u)   // FSW triggers reset, which goes to Bootblock - must be 0 (as RAM zeroing)
#define RBSYS_SKIP_BOOTBLOCKTrigResetValue  (0x00000000u)   // reset Backup RAM to zeroed state - must be 0 (as RAM zeroing)


/* Indicates if the latest SW-reset was triggered (with skip Bootblock) by FSW or Bootblock. */
RBMESG_DefineMESGType_u32(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);
RBMESG_DeclareMESG(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);


/* Messages to influence startup flow => ASIC has detected plant mode during startup */
RBMESG_DefineMESGType_B(RBMESG_RBSYSPlantModeRequest);
RBMESG_DeclareMESG(RBMESG_RBSYSPlantModeRequest);

/* Indicates that a BaseOS instead a normal OS startup is requested in next CPU reset cycle (i.e. after next SW reset). */
/* It is set via RBSYS_requestBaseOSAfterSWReset and reset during next startup */
RBMESG_DefineMESGType_u32(RBMESG_RBSYSBaseOSRequestbySW_u32);
RBMESG_DeclareMESG(RBMESG_RBSYSBaseOSRequestbySW_u32);

/* This flag shows that BaseOS entry in this CPU reset cycle was demanded by SW (set before last SW reset) */
RBMESG_DefineMESGType_B(RBMESG_RBSYSBaseOSbySW);
RBMESG_DeclareMESG(RBMESG_RBSYSBaseOSbySW);

/* This flag shows that BaseOS is active (i.e. BaseOS was started or will start in this CPU reset cycle) */
RBMESG_DefineMESGType_B(RBMESG_RBSYSBaseOSActive);
RBMESG_DeclareMESG(RBMESG_RBSYSBaseOSActive);




/**
 * @brief RBSYS_requestBaseOSAfterSWReset(void)
 *
 * Official interface to trigger BaseOS instead of normal OS startup in next CPU reset (i.e. after next SW reset)
 *
 * @return void
 */
static inline void RBSYS_requestBaseOSAfterSWReset(void)
{
  /* use a specific pattern */
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32) = RBSYS_BaseOSRequest;
  RBMESG_SendMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
}

#if(RBFS_ReprogDriverSupport == RBFS_ReprogDriverSupport_ON)
  /**
   * @brief RBSYS_requestReprogSessionAfterSWReset(void)
   *
   * Official interface to trigger a branch to flash reprog driver within DLM area after next SW reset
   * --> the user has to take care, that the download area is populated with valid reprog driver!!! (e.g. by previous download of code)
   *
   * ToDo: remove this function if reprog driver is not supported, currently still called by RBAPLPLANT
   *
   * @return void
   */
  static inline void RBSYS_requestReprogSessionAfterSWReset(void)
  {
    /* use a specific pattern */
    RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32) = RBSYS_ReprogRequest;
    RBMESG_SendMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
  }
#endif

/**
 * @brief RBSYS_requestVx1000ParHandlingAfterSWReset(void)
 *
 * Official interface to prepare online parameter handling via VX1000 after next SW Reset
 *
 * @return void
 */
static inline void RBSYS_requestVx1000ParHandlingAfterSWReset(void)
{
  /* use a specific pattern */
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32) = RBSYS_Vx1000ParHandlingRequested;
  RBMESG_SendMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
}

/**
 * @brief RBSYS_requestVx1000ReprogSessionAfterSWReset(void)
 *
 * Official interface to prepare flash reprog via VX1000 after next SW Reset
 * --> The download area is populated with valid reprog driver by VX1000
 *
 * @return void
 */
static inline void RBSYS_requestVx1000ReprogSessionAfterSWReset(void)
{
  /* use a specific pattern */
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32) = RBSYS_Vx1000ReprogRequested;
  RBMESG_SendMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
}

/**
 * @brief isBaseOSActive(void)
 *
 * @return TRUE if BaseOS is active, otherwise FALSE
 */
static inline boolean RBSYS_isBaseOSActive(void)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSActive);
  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSActive);
  return l_RBMESG_RBSYSBaseOSActive;
}



/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
