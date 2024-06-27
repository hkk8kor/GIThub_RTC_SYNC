#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                       ///< for RBFS_pTSWSupport

/* used interfaces */
#include "RBSYS_Intrinsics.h"
#include "RBLCF_MemoryRemap.h"

#include "RBSYS_BBFSW_StartupServices.h"




/**
 * \Reference
 *  RBSYS_setBootblockRequest, RBSYS_getBootblockRequest
 *
 * \Purpose
 *  Verify the bootblock request functionallity
 *
 * \Sequence
 *  Call function RBSYS_setBootblockRequest with a defined request parameter
 *
 * \ExpectedResult
 *  RBSYS_getBootblockRequest must return the defined request parameter
 */
SWTEST void TRBSYS_setBootblockRequest(void)
{
  uint32 request = 100;

  RBSYS_setBootblockRequest(request);

  SWT_EvalEq(RBSYS_getBootblockRequest(), request);
}


#if (RBFS_pTSWSupport == RBFS_pTSWSupport_ON)

  /**
   * \Reference
   *  RBSYS_setTCSWStartupRequest, RBSYS_getTCSWStartupRequest
   *
   * \Purpose
   *  Verify the TCSW request functionallity
   *
   * \Sequence
   *  Call function RBSYS_setTCSWStartupRequest with a defined request parameter
   *
   * \ExpectedResult
   *  RBSYS_getTCSWStartupRequest must return the defined request parameter
   */
  SWTEST void TRBSYS_setTCSWStartupRequest(void)
  {
    uint32 request = 111;

    RBSYS_setTCSWStartupRequest(request);

    SWT_EvalEq(RBSYS_getTCSWStartupRequest(), request);
  }

#endif



#if (RBFS_BackdoorBootblock == RBFS_BackdoorBootblock_YES)

  /**
   * \Reference
   *  RBSYS_setBaseOsRequest, RBSYS_getBaseOsRequest, Gen_SWCS_HSW_uC_Base_SYS-270
   *
   * \Purpose
   *  Verify the backdoor bootblock's BaseOs request functionallity
   *
   * \Sequence
   *  Call function RBSYS_setBaseOsRequest with a defined request parameter
   *
   * \ExpectedResult
   *  RBSYS_getBaseOsRequest must return the defined request parameter
   */
  SWTEST void TRBSYS_setBaseOsRequest(void)
  {
    uint32 request = 777;

    RBSYS_setBaseOsRequest(request);

    SWT_EvalEq(RBSYS_getBaseOsRequest(), request);
  }

#endif


#if( RBFS_BackupRAMLayout == RBFS_BackupRAMLayout_V1 )
  /**
   * \Reference
   *  RBSYS_SetuCSafetyNotificationData_ByIndex, RBSYS_GetuCSafetyNotificationData_ByIndex
   *
   * \Purpose
   *  Store and Retrieve data from BBFSW BackupRAM for uCSafetyNotification (user: RBECM)
   *
   * \Sequence
   *  Call RBSYS_SetuCSafetyNotificationData_ByIndex with sample data
   *  Call RBSYS_GetuCSafetyNotificationData_ByIndex
   *  result: Shall read the same sample data
   *
   *  + Test index sanity checks to garantuee robustness against access outside boundaries
   *
   * \ExpectedResult
   *  see \Sequence
   */
  SWTEST void TRBSYS_GetSetuCSafetyNotificationData(void)
  {
    RBSYS_SetuCSafetyNotificationData_ByIndex(0,0xAAAAAAAAu);
    RBSYS_SetuCSafetyNotificationData_ByIndex(1,0xBBBBBBBBu);
    RBSYS_SetuCSafetyNotificationData_ByIndex(2,0xCCCCCCCCu);
    RBSYS_SetuCSafetyNotificationData_ByIndex(3,0xDDDDDDDDu);

    SWT_EvalEq( RBSYS_GetuCSafetyNotificationData_ByIndex(0), 0xAAAAAAAAu);
    SWT_EvalEq( RBSYS_GetuCSafetyNotificationData_ByIndex(1), 0xBBBBBBBBu);
    SWT_EvalEq( RBSYS_GetuCSafetyNotificationData_ByIndex(2), 0xCCCCCCCCu);
    SWT_EvalEq( RBSYS_GetuCSafetyNotificationData_ByIndex(3), 0xDDDDDDDDu);
    
    SWT_AssertCheckStart("RBSYS_SetuCSafetyNotificationData_ByIndex", "index < 4");
    RBSYS_SetuCSafetyNotificationData_ByIndex(4,0x12312312);
    SWT_AssertCheckEnd();

    
    SWT_AssertCheckStart("RBSYS_GetuCSafetyNotificationData_ByIndex", "index < 4");
    RBSYS_GetuCSafetyNotificationData_ByIndex(4);
    SWT_AssertCheckEnd();
  }
#endif


