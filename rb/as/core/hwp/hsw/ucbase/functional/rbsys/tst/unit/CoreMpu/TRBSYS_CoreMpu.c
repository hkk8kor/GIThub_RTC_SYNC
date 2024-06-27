/**
 * @ingroup RBSYS
 * @{
 *
 * \file
 * \brief Unit test for CoreMpu
 *
 * This unit test checks the correct behaviour of the RBSYS CoreMpu management service
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "SwTest_Global.h"          // for SWT functionality
#include "RBSYS_Config.h"          // for RBFS_uCFamily, RBFS_SYSDebugFeatures

/* used interfaces */
#include "RBSYS_CoreMpu.h"
#include "TRBSYS_Intrinsics.h"
#include "TRBLCF_MemoryMap.h"



/**
  * \TestCaseName TRBSYS_CheckDefaultMpuConfiguration
  *
  * \Reference
  *
  * \Purpose Check Default Mpu Configuration
  *
  * \Sequence
  * Evaluate for every MPU section:
  *    StartAddress + Size == EndAddress + 1
  *    (Example: Region of size 1k from 0x000...3FF)
  *
  * \ExpectedResult
  *   see \Sequence
  */
SWTEST void TRBSYS_CheckDefaultMpuConfiguration(void)
{
  uint32 numSections = RBSYS_MpuRegionConfigSize;
  uint32 i;

  for( i=0; i<numSections; i++ )
  {
    #if (RBFS_uCFamily == RBFS_uCFamily_STMStellar)
      uint32 startAddr = RBSYS_MpuRegionConfig[i].start;
      uint32 endAddr   = RBSYS_MpuRegionConfig[i].end;
      uint32 size      = RBSYS_MpuRegionConfig[i].size;
      SWT_EvalEqX( startAddr + size, endAddr + 1);
    #else
      uint32 region = RBSYS_MpuRegionConfig[i].region;
      uint32 start  = RBSYS_MpuRegionConfig[i].start;
      uint32 end    = RBSYS_MpuRegionConfig[i].end;
      uint32 attr   = RBSYS_MpuRegionConfig[i].attr;
      SWT_Eval( (start < end) || (start == 0 && end == 0)) ;
      SWT_Eval( region < 16 );
    #endif
  }
}

#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
  /**
    * \TestCaseName TRBSYS_CoreMpu_SetRegion
    *
    * \Reference RBSYS_CoreMpu_SetRegion
    *
    * \Purpose check that RBSYS_CoreMpu_SetRegion is working correctly
    *
    * \Sequence
    * 1) call RBSYS_CoreMpu_SetRegionAttr with valid arguments
    * 2) P1x only: call RBSYS_CoreMpu_SetRegionAttr with too high region index (on U2A/U2C the index is limited by the bits writable in the MPIDX register)
    *
    * \ExpectedResult
    * 1) MPUA, MPAT, MPLA (all) and MPIDX (U2A/U2C) are correctly set, SYNCP and SYNCI are called
    * 2) no MPUA, MPAT, MPLA register is overwritten
    *
    */
  SWTEST void TRBSYS_CoreMpu_SetRegion(void)
  {
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      uint32 i;
      RBSYS_MpuRegion_t config;
      for(i = 0; i < 16; i++)
      {
        config = (RBSYS_MpuRegion_t){i, 0x1000 * 2 * i, (0x1000 * 2 * i) + 0x1000, 0x1111 * i};
        RBSYS_CoreMpu_SetRegion(&config);
        SWT_EvalEqX(RBSYS_STSR(((i * 4) % 32) + 0, ((i * 4) / 32) + 6), 0x1000 * 2 * i);
        SWT_EvalEqX(RBSYS_STSR(((i * 4) % 32) + 1, ((i * 4) / 32) + 6), (0x1000 * 2 * i) + 0x1000);
        SWT_EvalEqX(RBSYS_STSR(((i * 4) % 32) + 2, ((i * 4) / 32) + 6), 0x1111 * i);
        SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), i + 1);
        SWT_EvalEq(TRBSYS_Get_SYNCI_CNT(), i + 1);
      }
      // execute default case which should do nothing
      config = (RBSYS_MpuRegion_t){16, 0x1000 * 2 * 16, (0x1000 * 2 * 16) + 0x1000, 0x1111 * 16};
      RBSYS_CoreMpu_SetRegion(&config);
      for(i = 0; i < 16; i++)
      {
        SWT_EvalNeqX(RBSYS_STSR(((i * 4) % 32) + 0, ((i * 4) / 32) + 6), 0x1111 * 16);
        SWT_EvalNeqX(RBSYS_STSR(((i * 4) % 32) + 1, ((i * 4) / 32) + 6), 0x1111 * 16);
        SWT_EvalNeqX(RBSYS_STSR(((i * 4) % 32) + 2, ((i * 4) / 32) + 6), 0x1111 * 16);
      }
      SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 17);
      SWT_EvalEq(TRBSYS_Get_SYNCI_CNT(), 17);

    #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      RBSYS_MpuRegion_t config = {1, 0x1111, 0x2222, 0x3333};
      RBSYS_CoreMpu_SetRegion(&config);
      SWT_EvalEqX(RBSYS_STSR(16, 5), 1);
      SWT_EvalEqX(RBSYS_STSR(20, 5), 0x1111);
      SWT_EvalEqX(RBSYS_STSR(21, 5), 0x2222);
      SWT_EvalEqX(RBSYS_STSR(22, 5), 0x3333);
      SWT_EvalEq(TRBSYS_Get_SYNCI_CNT(), 1);
    #endif
  }

  /**
    * \TestCaseName TRBSYS_CoreMpu_SetRegionAttr
    *
    * \Reference RBSYS_CoreMpu_SetRegionAttr
    *
    * \Purpose check that RBSYS_CoreMpu_SetRegionAttr is working correctly
    *
    * \Sequence
    * 1) call RBSYS_CoreMpu_SetRegionAttr with valid arguments
    * 2) P1x only: call RBSYS_CoreMpu_SetRegionAttr with too high region index (on U2A/U2C the index is limited by the bits writable in the MPIDX register)
    *
    * \ExpectedResult
    * 1) MPAT (all) and MPIDX (U2A/U2C) are correctly set, SYNCP and SYNCI are called
    * 2) no MPAT register is overwritten
    *
    */
  SWTEST void TRBSYS_CoreMpu_SetRegionAttr(void)
  {
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      uint32 i;
      for(i = 0; i < 16; i++)
      {
        RBSYS_CoreMpu_SetRegionAttr(i, 0x1111 * i);
        SWT_EvalEqX(RBSYS_STSR(((i * 4) % 32) + 2, ((i * 4) / 32) + 6), 0x1111 * i);
        SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), i + 1);
        SWT_EvalEq(TRBSYS_Get_SYNCI_CNT(), i + 1);
      }
      // execute default case which should do nothing
      RBSYS_CoreMpu_SetRegionAttr(16, 0x1111 * 16);
      for(i = 0; i < 16; i++)
      {
        SWT_EvalNeqX(RBSYS_STSR(((i * 4) % 32) + 2, ((i * 4) / 32) + 6), 0x1111 * 16);
      }
      SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 17);
      SWT_EvalEq(TRBSYS_Get_SYNCI_CNT(), 17);
    #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      RBSYS_CoreMpu_SetRegionAttr(1, 0x1111);
      SWT_EvalEqX(RBSYS_STSR(16, 5), 1);
      SWT_EvalEqX(RBSYS_STSR(22, 5), 0x1111);
      SWT_EvalEq(TRBSYS_Get_SYNCI_CNT(), 1);
    #endif
  }

  #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON))
    /**
      * \TestCaseName TRBSYS_CoreMpu_AllowRamExecution
      *
      * \Reference RBSYS_CoreMpu_AllowRamExecution
      *
      * \Purpose Check RBSYS_CoreMpu_AllowRamExecution is working correctly
      *
      * \Sequence
      * call RBSYS_CoreMpu_AllowRamExecution
      *
      * \ExpectedResult
      * MPU attributes are set correctly to allow execution
      *
      */
    SWTEST void TRBSYS_CoreMpu_AllowRamExecution(void)
    {
      RBSYS_CoreMpu_AllowRamExecution();

      #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
        SWT_EvalEq(RBSYS_STSR(14, 6), RBSYS_MPU_ATTR_DEFAULT | RBSYS_BASICATTR_SV_RWX | RBSYS_MPU_ACCESS_E);
      #endif
      SWT_EvalEq(RBSYS_STSR(18, 6), RBSYS_MPU_ATTR_DEFAULT | RBSYS_BASICATTR_SV_RWX | RBSYS_MPU_ACCESS_E);
      #if (RBFS_LocalRamCore1Support == RBFS_LocalRamCore1Support_ON)
        SWT_EvalEq(RBSYS_STSR(22, 6), RBSYS_MPU_ATTR_DEFAULT | RBSYS_BASICATTR_SV_RWX | RBSYS_MPU_ACCESS_E);
      #endif
    }
  #endif
#endif

/** @} */
/* End ingroup RBSYS */

