#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                      ///< for RBFS_uC

#include "RBSYS_uCRegisters.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_CpuVersions.h"
#include "TRBSYS_CpuVersions.h"
#include "TRBSYS_LocksHelper.h"

#include "RBSYS_CacheControl.h"
#include "RBSYS_CacheControlIntern.h"


#if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)

  /**
   * \Reference
   *  RBSYS_WTBufErrataHandling, Gen_SWCS_HSW_uC_Base_SYS-257
   *
   * \Purpose
   *  Valdiate WT buffer handling on a not affected device
   *
   * \Sequence
   *  Simulate CPU type as D5EDv3 v1.00
   *  Call function RBSYS_WTBufErrataHandling
   *
   * \ExpectedResult
   *  SYNCP is not called
   *  GRAMC_WTBCONFIG0 must be set to 1
   *       bit 31 to 1 = reserved (all 0's)
   *       bit 0 (WTBufMode) This bit sets whether to enable WT Buf
   *                   0: disable WT buffer
   *                   1: enable WT buffer
   */
  SWTEST void TRBSYS_WTBufErrataHandling(void)
  {
    TRBSYS_SetCPU_D5EDV3_V100();

    RBSYS_WTBufErrataHandling();

    // no device is effected by errata
    SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 0);
    SWT_EvalEq(GRAMC_WTBCONFIG0, 0x1u);
  }


  #if (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3)

    /**
     * \Reference
     *  RBSYS_WTBufErrataHandling, Gen_SWCS_HSW_uC_Base_SYS-257
     *
     * \Purpose
     *  Valdiate WT buffer handling on D3 devices
     *
     * \Sequence
     *  Simulate CPU type as
     *     - D3_LQFP144_DPS_V100
     *     - D3_BGA292_DPS_V100
     *     - D3_BGA292_EVR_V100
     *     - D3_LQFP144_EVR_V100
     *     - D3_HQFP144_EVR_V100
     *  Call for each CPU type the function RBSYS_WTBufErrataHandling
     *
     * \ExpectedResult
     *  SYNCP must be called once
     *  GRAMC_WTBCONFIG0 must be set to 0
     *       bit 31 to 1 = reserved (all 0's)
     *       bit 0 (WTBufMode) This bit sets whether to enable WT Buf
     *                   0: disable WT buffer
     *                   1: enable WT buffer
     */
    SWTEST void TRBSYS_WTBufErrataHandling_D3(void)
    {
      //D3_LQFP144_DPS_V100
      TRBSYS_SetCPU_D3_LQFP144_DPS_V100();

      RBSYS_WTBufErrataHandling();

      SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 1);
      SWT_EvalEq(GRAMC_WTBCONFIG0, 0);

      // D3_BGA292_DPS_V100
      TRBSYS_SetCPU_D3_BGA292_DPS_V100();

      RBSYS_WTBufErrataHandling();

      SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 2);
      SWT_EvalEq(GRAMC_WTBCONFIG0, 0);

      // D3_BGA292_EVR_V100
      TRBSYS_SetCPU_D3_BGA292_EVR_V100();

      RBSYS_WTBufErrataHandling();

      SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 3);
      SWT_EvalEq(GRAMC_WTBCONFIG0, 0);

      // D3_LQFP144_EVR_V100
      TRBSYS_SetCPU_D3_LQFP144_EVR_V100();

      RBSYS_WTBufErrataHandling();

      SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 4);
      SWT_EvalEq(GRAMC_WTBCONFIG0, 0);

      // D3_HQFP144_EVR_V100
      TRBSYS_SetCPU_D3_HQFP144_EVR_V100();

      RBSYS_WTBufErrataHandling();

      SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 5);
      SWT_EvalEq(GRAMC_WTBCONFIG0, 0);
    }


    /**
     * \Reference
     *  RBSYS_WTBufErrataHandling, Gen_SWCS_HSW_uC_Base_SYS-257
     *
     * \Purpose
     *  Valdiate WT buffer handling on D3ED devices
     *
     * \Sequence
     *  Simulate CPU type as D3ED v1.00
     *  Call function RBSYS_WTBufErrataHandling
     *
     * \ExpectedResult
     *  SYNCP must be called once
     *  GRAMC_WTBCONFIG0 must be set to 0
     *       bit 31 to 1 = reserved (all 0's)
     *       bit 0 (WTBufMode) This bit sets whether to enable WT Buf
     *                   0: disable WT buffer
     *                   1: enable WT buffer
     */
    SWTEST void TRBSYS_WTBufErrataHandling_D3ED(void)
    {
      TRBSYS_SetCPU_D3ED_V100();

      RBSYS_WTBufErrataHandling();

      SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 1);
      SWT_EvalEq(GRAMC_WTBCONFIG0, 0);
    }

  #endif

  /**
   * \Reference
   *  RBSYS_WTBufErrataHandling, Gen_SWCS_HSW_uC_Base_SYS-257
   *
   * \Purpose
   *  Valdiate WT buffer handling on D5EDv2 devices
   *
   * \Sequence
   *  Simulate CPU type as D5EDv2 v1.00
   *  Call function RBSYS_WTBufErrataHandling
   *
   * \ExpectedResult
   *  SYNCP must be called once
   *  GRAMC_WTBCONFIG0 must be set to 0
   *       bit 31 to 1 = reserved (all 0's)
   *       bit 0 (WTBufMode) This bit sets whether to enable WT Buf
   *                   0: disable WT buffer
   *                   1: enable WT buffer
   */
  SWTEST void TRBSYS_WTBufErrataHandling_D5ED(void)
  {
    TRBSYS_SetCPU_D5EDV2_V100();

    RBSYS_WTBufErrataHandling();

    SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 1);
    SWT_EvalEq(GRAMC_WTBCONFIG0, 0);
  }


  /**
   * \Reference
   *  RBSYS_flushWriteThroughBuffer, Gen_SWCS_HSW_uC_Base_SYS-264
   *
   * \Purpose
   *  Validate function to flush the WT buffer
   *
   * \Sequence
   *  Call function RBSYS_flushWriteThroughBuffer
   *
   * \ExpectedResult
   *  There must be a read access to WTBCONFIG2 register
   *  SYNCM and SYNCP must be called once
   *  Core-local lock must be called once (enter + exit)
   */
  SWTEST void TRBSYS_flushWriteThroughBuffer(void)
  {
    RBSYS_flushWriteThroughBuffer();

    SWT_EvalEq(TRBSYS_GetReadCnt_WTBCONFIG2(), 1);

    SWT_EvalEq(TRBSYS_Get_SYNCM_CNT(), 1);
    SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 1);

    SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
    SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);
  }

#endif


#if(   (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) \
    )
  /**
   * \Reference
   *  RBSYS_invalidateInstructionCache
   *
   * \Purpose
   *  Validate function to invalidate the instruction cache
   *
   * \Sequence
   *  Call function RBSYS_invalidateInstructionCache
   *
   * \ExpectedResult
   *  SYNCP and SYNCI must be called once
   *  Core-local lock must be called once (enter + exit)
   */
  SWTEST void TRBSYS_invalidateInstructionCache(void)
  {
    RBSYS_invalidateInstructionCache();

    SWT_EvalEq(TRBSYS_Get_SYNCM_CNT(), 1);
    SWT_EvalEq(TRBSYS_Get_SYNCI_CNT(), 1);
    SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
    SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);
  }
#endif



#if(   (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2) \
    )

  /* ICCTRL — Instruction cache control
   * Bit0 (ICHEN) This bit indicates valid/invalid status of instruction cache.
   *      0: Instruction cache is invalid
   *      1: Instruction cache is valid
   *      This bit is read as the previous value until the setting is actually reflected in the instruction cache.
   */
  #define ICCTRL_CACHE_ENABLE   0xFFFFFFFFu
  #define ICCTRL_CACHE_DISABLE  0xFFFFFFFEu

  /**
   * \Reference
   *  RBSYS_DisableInstructionCache, Gen_SWCS_HSW_uC_Base_SYS-255
   *
   * \Purpose
   *  Validate function to disable the instruction cache
   *
   * \Sequence
   *  Set device typ to D3ED
   *  Simulate enabled instruction cache within system register 24, 4 (ICCTRL => Instruction cache control)
   *  Call function RBSYS_DisableInstructionCache
   *
   * \ExpectedResult
   *  Bit 0 within ICCTRL must be set to 0 to disables the instruction cache
   *  SYNCP and SYNCI must be called once
   */
  SWTEST void TRBSYS_DisableInstructionCache_D3ED(void)
  {
    TRBSYS_SetCPU_D3ED();

    TRBSYS_SetSystemRegister(24, 4, ICCTRL_CACHE_ENABLE);

    RBSYS_DisableInstructionCache();

    SWT_EvalEq(RBSYS_STSR(24, 4), ICCTRL_CACHE_DISABLE);
    SWT_EvalEq(TRBSYS_Get_SYNCM_CNT(), 1);
    SWT_EvalEq(TRBSYS_Get_SYNCI_CNT(), 1);
  }

  /**
   * \Reference
   *  RBSYS_DisableInstructionCache, Gen_SWCS_HSW_uC_Base_SYS-255
   *
   * \Purpose
   *  Validate function to disable the instruction cache
   *
   * \Sequence
   *  Set device typ to D5ED
   *  Simulate enabled instruction cache within system register 24, 4 (ICCTRL => Instruction cache control)
   *  Call function RBSYS_DisableInstructionCache
   *
   * \ExpectedResult
   *  Bit 0 within ICCTRL must be set to 0 to disables the instruction cache
   *  SYNCP and SYNCI must be called once
   */
  SWTEST void TRBSYS_DisableInstructionCache_D5ED(void)
  {
    TRBSYS_SetCPU_D5ED();

    TRBSYS_SetSystemRegister(24, 4, ICCTRL_CACHE_ENABLE);

    RBSYS_DisableInstructionCache();

    SWT_EvalEq(RBSYS_STSR(24, 4), ICCTRL_CACHE_DISABLE);
    SWT_EvalEq(TRBSYS_Get_SYNCM_CNT(), 1);
    SWT_EvalEq(TRBSYS_Get_SYNCI_CNT(), 1);
  }


/**
   * \Reference
   *  RBSYS_DisableInstructionCache, Gen_SWCS_HSW_uC_Base_SYS-255
   *
   * \Purpose
   *  Prove that instruction cache won't be disabled for non emulation devices
   *
   * \Sequence
   *  Set device typ as not D3ED and not D5ED
   *  Simulate enabled instruction cache within system register 24, 4 (ICCTRL => Instruction cache control)
   *  Call function RBSYS_DisableInstructionCache
   *
   * \ExpectedResult
   *  Bit 0 within ICCTRL must still be set to 1 (instruction cache enable)
   *  SYNCP and SYNCI must not be called (=0)
   */
  SWTEST void TRBSYS_DisableInstructionCache_NonEmuDevice(void)
  {

    TRBSYS_SetSystemRegister(24, 4, ICCTRL_CACHE_ENABLE);

    RBSYS_DisableInstructionCache();

    SWT_EvalEq(RBSYS_STSR(24, 4), ICCTRL_CACHE_ENABLE);
    SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 0);
    SWT_EvalEq(TRBSYS_Get_SYNCI_CNT(), 0);
  }

#endif


/* CDBCR — Data buffer control register
 * Bit0 (CDBEN):
 *      This bit specifies enables or disables of the data buffer.
 *         0: Data buffer is disabled.
 *         1: Data buffer is enabled.
 * Bit1 (CDBCLR):
 *      When this bit is set to 1, data buffer is all cleared. This bit is always read as 0.
 */
#define CDBCR_DATA_BUFFER_DEFAULT   0x1u
#define CDBCR_DATA_BUFFER_CLEARED   0x3u

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
/**
 * \Reference
 *  RBSYS_clearDataBuffer, Gen_SWCS_HSW_uC_Base_SYS-265
 *
 * \Purpose
 *  Verify the service to clear the core specific code flash data buffer
 *
 * \Sequence
 *  Simulate default content of system register 24, 13 (CDBCR => Data buffer control register)
 *
 * \ExpectedResult
 *  Bit 1 within CDBCR must be set to 1 to clear the data buffer. In HW this bit is always read as 0 -
 *  this is not considered here.
 *  Core-local lock must be called once (enter + exit)
 *  RBSYS_SYNCP() must be called once
 */
SWTEST void TRBSYS_clearDataBuffer(void)
{
  TRBSYS_SetSystemRegister(24, 13, CDBCR_DATA_BUFFER_DEFAULT);

  RBSYS_clearDataBuffer();

  SWT_EvalEq(RBSYS_STSR(24, 13), CDBCR_DATA_BUFFER_CLEARED);

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  SWT_EvalEq(TRBSYS_Get_SYNCP_CNT(), 1);
}




#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  /**
  * \Reference
  *  RBSYS_invalidateDataCache, Gen_SWCS_HSW_uC_Base_SYS-265
  *
  * \Purpose
  *  Verify the service to clear (here: invalidate) the core specific code flash data cache
  *
  * \Sequence
  *  Provide X7 configuration of the cache sets/ways
  *  Verify if all necessary dcisw commands have been issued (order doesnt matter)
  *
  * \ExpectedResult
  *  dcisw commands for all sets/ways have been issued
  */
  SWTEST void TRBSYS_invalidateDataBuffer(void)
  {
    uint32 numOfWays = 4;
    uint32 numOfSets = 128;

    uint32 way_idx, set_idx, counter = 0;

    RBSYS_MCR(15, 1, (numOfSets-1) << 13, 0, 0, 0); // write CCISW
    counter++;

    RBSYS_invalidateDataCache();
    
    /* CCSELR register set to 0x0 (select Data Cache) */
    SWT_EvalEqX( TRBSYS_SystemRegister_STMStellar_WriteAccesses[counter].coproc,  15);
    SWT_EvalEqX( TRBSYS_SystemRegister_STMStellar_WriteAccesses[counter].opcode1, 2);
    SWT_EvalEqX( TRBSYS_SystemRegister_STMStellar_WriteAccesses[counter].val,     0x0);
    SWT_EvalEqX( TRBSYS_SystemRegister_STMStellar_WriteAccesses[counter].CRn,     0);
    SWT_EvalEqX( TRBSYS_SystemRegister_STMStellar_WriteAccesses[counter].CRm,     0);
    SWT_EvalEqX( TRBSYS_SystemRegister_STMStellar_WriteAccesses[counter].opcode2, 0);
    counter++;

    for( way_idx = 0; way_idx < numOfWays; way_idx++ )
    {
      for( set_idx = 0; set_idx < numOfSets; set_idx++ )
      {
        /* from R52 Reference Manual: Associativity:  0x3  => The cache has four ways. */
        /* from R52 Reference Manual: Line size:      0x3  => 16 words (64B) per cache line */
        /* from R52 Reference Manual: Number of Sets: 0x7F => 128 sets per way */
        /* Which leads to the following encoding of DCISW:
          - [31:30] Way
          - [12:6]  Set */
        

        /* DCISW Command:       Bit[31:30] Way  | Bit[12:6] Set            | Bit[3:1] Level -> Level 1 Cache */
        uint32 dcisw_command = ((way_idx << 30) | ((set_idx << 6) & 0x1FC0u) | (0x0 << 1));

        SWT_EvalEqX( TRBSYS_SystemRegister_STMStellar_WriteAccesses[counter].coproc,  15);
        SWT_EvalEqX( TRBSYS_SystemRegister_STMStellar_WriteAccesses[counter].opcode1, 0);
        SWT_EvalEqX( TRBSYS_SystemRegister_STMStellar_WriteAccesses[counter].val,     dcisw_command);
        SWT_EvalEqX( TRBSYS_SystemRegister_STMStellar_WriteAccesses[counter].CRn,     7);
        SWT_EvalEqX( TRBSYS_SystemRegister_STMStellar_WriteAccesses[counter].CRm,     6);
        SWT_EvalEqX( TRBSYS_SystemRegister_STMStellar_WriteAccesses[counter].opcode2, 2);

        counter++;
      }
    }


    SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
    SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

    SWT_EvalEq(TRBSYS_Get_DSB_Cnt(), 2);
  }

#endif
