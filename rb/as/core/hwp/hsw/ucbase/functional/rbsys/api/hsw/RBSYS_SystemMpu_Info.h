#ifndef RBSYS_SYSTEMMPU_INFO_H__
#define RBSYS_SYSTEMMPU_INFO_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file  RBSYS_SystemMpu_Info.h
 * @brief Provides interfaces to read SystemMPU Status register and generate debug data for failure entries
 *
 * Generic Interface to read out failure information from the SystemMPU. Previously handled inside rbecm, target is to shift the
 * implementation for other Stellar and other uCs to rbsys SystemMPU, to use synergies with SystemMPU initialization implementation.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */
  
#include "Std_Types.h"

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  typedef enum
  {
    RBSYS_SystemMPUPrivilegeLevel_EL01,
    RBSYS_SystemMPUPrivilegeLevel_EL2
  } RBSYS_SystemMPUPrivilegeLevel_t;
  
  typedef struct
  {
    // RBSYS_NOCRegionType_n RegionType; //=> cannot find out the region index in all cases, therefore cannot find out the region type
    uint32 Address;
    uint32 InitiatorId;
    uint32 StatusRegister;
  } RBSYS_SystemMPU_AccessViolation_t;
  
  
  typedef enum
  {
    RBSYS_SystemMPU_FailureType_APIMisuse,
    RBSYS_SystemMPU_FailureType_FirewallError,
    RBSYS_SystemMPU_FailureType_Undefined
  } RBSYS_SystemMPU_FailureType_t;
  
  
  /** 
   *  @brief Read out System MPU failures from Firewall with given index [NocFirewallId]
   * 
   *  @param NocFirewallId [in]: Index of firewall (see corresponding RM, e.g. RM0496 Rev 2 p.171 )
   *  @param exceptionLevel [in]: either EL0/1 or EL2
   *  @param AccessViolation [out]: Access violation information
   *  @return Validity of [out] param AccessViolation
   */
  extern RBSYS_SystemMPU_FailureType_t RBSYS_GetSystemMpuFailure(uint32 NocFirewallId, RBSYS_SystemMPUPrivilegeLevel_t exceptionLevel, RBSYS_SystemMPU_AccessViolation_t* AccessViolation /*out*/);
    
  
  /** 
   * @brief Conversion function to extract debug data "debug0" and "debug1" from RBSYS_SystemMPU_AccessViolation_t 
   * 
   * @param violation [in]: Access violation information
   * @param debug0 [out]: Debug Information for DEM
   * @param debug1 [out]: Debug Information for DEM
   * 
   * Attention: Must only be called with a properly initialized and valid RBSYS_SystemMPU_AccessViolation_t object 
   *            => RBSYS_GetSystemMpuFailure with return value 'RBSYS_SystemMPU_FailureType_FirewallError'
   */
  extern void RBSYS_GenerateSystemMpuFailureDebugData(RBSYS_SystemMPU_AccessViolation_t* violation, uint32* debug0, uint32* debug1);


  /**
   * @brief Clears all failure indicators in all Firewalls
   */
  extern void RBSYS_ClearAllFirewallStatusRegisters(void);

#endif



/**
 * Example of usage:
 * 
 * static RBSYS_SystemMPU_AccessViolation_t violation; //< could be used as static measurement variable
 *
 * montoring...
 * if( RBSYS_SystemMPU_FailureType_FirewallError == RBSYS_GetSystemMpuFailure(15, RBSYS_SystemMPUPrivilegeLevel_EL01, &violation) )
 * {
 *   uint32 debug0, debug1;
 *   RBSYS_GenerateSystemMpuFailureDebugData(&violation, &debug0, &debug1);
 * }
 * else
 * {
 *   // komisches Verhalten von device
 * }
 * ...monitoring
 * 
 * 
*/


/** @} */
/* End ingroup RBSYS */

#endif