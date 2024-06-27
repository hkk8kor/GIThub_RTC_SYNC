#include "SwTest_Global.h"

#include "RBSYS_Config.h" ///< for RBFS_TargetDevice, RBFS_RenesasP1xGRAM, RBFS_SysHsmSharedGRAMsize


// access API for api header under test
#include "TRBSYS_GuardConfig_Adaptor.h"


#include "TRBSYS_Intrinsics.h"
#include "TRBSYS_CpuInfo.h"
#include "TRBSYS_uCRegisters.h"
#include "RBSYS_Subsystem.h"
#include "TRBSYS_TestInjection.h"

#if(RBFS_uCFamily != RBFS_uCFamily_STMStellar )

  #if(RBFS_TRBSYSGuardVariance == RBFS_TRBSYSGuardVariance_supported)

    #include "SystemMemoryProtection/RBSYS_GuardConfigCommon.h"
    #include "RBSYS_GuardConfig.h"
    #include "RBSYS_GuardMemoryMap.h"
    #include "RBSYS_RestrictedSPID.h"

    #include "RBHSWDEM_Facade.h"
    #include "DemStub_Helper.h"
    #include "RBSYS_ErrorHooks.h"

    #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
      /**
      * \TestCaseName TRBSYS_GuardConfig_001
      *
      * \Reference
      * RBSYS_setCoreSPID, RBSYS_getCoreSPID, Gen_SWCS_HSW_uC_Base_SYS-287
      *
      * \Purpose Test functionality of setting/getting the SPID for the core in/from MCFG0 register
      *
      * \Sequence
      *  1. call the function RBSYS_setCoreSPID
      *  2. check that the value is put into Bits 16..20 (5Bits) of the register (P1x) Bits 0..4 (5Bits) U2A
      *  3. call the function RBSYS_getCoreSPID
      *  4. check that the formerly set value is returned
      *
      * \ExpectedResult
      * The system register (stubbed) is set to the expected value in the relevant 5 Bits.
      *
      */
      SWTEST void TRBSYS_GuardConfig_001(void)
      {
        uint32 mySPID = 7;
        uint32 myCheckSPID = 0;

        call_RBSYS_setCoreSPID(mySPID);

        #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
            SWT_EvalEqX(((TRBSYS_GetSystemRegister(0,1) >> 16) & 0x1F), 7);
        #endif

        #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
            SWT_EvalEqX((TRBSYS_GetSystemRegister(0,1) & 0x1F), 7);
        #endif

        myCheckSPID = call_RBSYS_getCoreSPID();
        SWT_EvalEqX(mySPID, myCheckSPID);
      }


      /* Function is implemented in assembler and therefore can only be tested on Target Build */
      #if( RBFS_SysEnvironment == RBFS_SysEnvironment_Target )
        /**
        * \TestCaseName TRBSYS_GuardConfig_002
        *
        * \Reference
        * RBSYS_PEGuardInit,Gen_SWCS_HSW_uC_Base_SYS-287
        *
        * \Purpose Test functionality of the RBSYS_PEGuardInit (i.e. all expected registers are set to the expected values)
        *
        * \Sequence
        *  1. call the function RBSYS_PEGuardInit
        *  2. check that the expected values are put into the registers
        *
        * \ExpectedResult
        * All affected registers must be set to the expected values.
        *
        */
        SWTEST void TRBSYS_GuardConfig_002(void)
        {
          #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
            call_RBSYS_PEGuardInit();
            SWT_EvalEqX(PEGG0MK, 0x003FF000u);
            SWT_EvalEqX(PEGG0SP, 0x3u);
            SWT_EvalEqX(PEGG0BA, 0xFE800003u);
            SWT_EvalEqX(PEGG1MK, 0x003FF000u);
            SWT_EvalEqX(PEGG1SP, 0x4u);
            SWT_EvalEqX(PEGG1BA, 0xFE800007u);
          #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
            TRBSYS_setCoreID(0);
            call_RBSYS_PEGuardInit();
            SWT_EvalEqX(GUARD_PE0CL0PEGSPID0, 0xC0000004u); // MAU / AUD / SAFE
            SWT_EvalEqX(GUARD_PE1CL0PEGSPID0, 0);
            TRBSYS_setCoreID(1);
            GUARD_PE0CL0PEGSPID0 = 0;  // reset value to verify that it is not set
            call_RBSYS_PEGuardInit();
            SWT_EvalEqX(GUARD_PE0CL0PEGSPID0, 0);
            SWT_EvalEqX(GUARD_PE1CL0PEGSPID0, 0xC0000004u); // MAU / AUD / SAFE
          #endif
        }
      #endif

      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        /**
        * \TestCaseName TRBSYS_GuardConfig_004
        *
        * \Reference
        * RBSYS_PBUSGuardInit, Gen_SWCS_HSW_uC_Base_SYS-287
        *
        * \Purpose Test functionality of the RBSYS_PBUSGuardInit (i.e. all expected registers are set to the expected values)
        *
        * \Sequence
        *  1. call the function RBSYS_PBUSGuardInit
        *  2. check that DMA relevant Bits are set as expected
        *
        * \ExpectedResult
        * All affected registers must be set to the expected values.
        *
        */
        SWTEST void TRBSYS_GuardConfig_004(void)
        {
          FSGD1APROT04 = 0x75u;
          FSGD1APROT05 = 0x76u;
          FSGD1BPROT10 = 0x77u;
          FSGD1BPROT11 = 0x88u;
          FSGD1BPROT12 = 0x99u;
          FSGD1BPROT13 = 0x11u;
          FSGD2APROT04 = 0x22u;
          FSGD2APROT05 = 0x33u;
          FSGD2APROT06 = 0x44u;
          FSGD3BPROT10 = 0x55u;
          FSGD3BPROT11 = 0x66u;
          FSGD3BPROT12 = 0xAAu;
          FSGD3BPROT13 = 0xBBu;
          FSGD4APROT06 = 0xCCu;
          FSGD4APROT08 = 0xDDu;

          FSGD1ASPID05 = 0;
          FSGD1BSPID11 = 0;
          FSGD1BSPID13 = 0;
          FSGD2ASPID05 = 0;
          FSGD3BSPID11 = 0;
          FSGD3BSPID13 = 0;

          call_RBSYS_PBUSGuardInit();
          SWT_EvalEqX(FSGD1APROT04, 0x200075u);
          SWT_EvalEqX(FSGD1ASPID05, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD1APROT05, 0x200076u);
          SWT_EvalEqX(FSGD1BPROT10, 0x200077u);
          SWT_EvalEqX(FSGD1BSPID11, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD1BPROT11, 0x200088u);

          //Renesas devices D1 and D2 do only have CSIH0 - CSIH2
          #if((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2))
            SWT_EvalEqX(FSGD1BPROT12, 0x200099u);
            SWT_EvalEqX(FSGD1BSPID13, RBSYS_SPID_SAFE_MASK);
            SWT_EvalEqX(FSGD1BPROT13, 0x200011u);
          #else
            SWT_EvalEqX(FSGD1BPROT12, 0x99u);
            SWT_EvalEqX(FSGD1BSPID13, 0);
            SWT_EvalEqX(FSGD1BPROT13, 0x11u);
          #endif

          SWT_EvalEqX(FSGD2APROT04, 0x200022u);
          SWT_EvalEqX(FSGD2ASPID05, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD2APROT05, 0x200033u);
          SWT_EvalEqX(FSGD2APROT06, 0x200044u);
          SWT_EvalEqX(FSGD3BPROT10, 0x200055u);
          SWT_EvalEqX(FSGD3BSPID11, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3BPROT11, 0x200066u);
          SWT_EvalEqX(FSGD3BPROT12, 0x2000AAu);
          SWT_EvalEqX(FSGD3BSPID13, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3BPROT13, 0x2000BBu);
          SWT_EvalEqX(FSGD4APROT06, 0x2000CCu);

          // Renesas devices D1 and D2 do only have one ADC unit
          #if((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2))
            SWT_EvalEqX(FSGD4A.PROT08, 0x2000DDu);
          #else
            SWT_EvalEqX(FSGD4APROT08, 0xDDu);
          #endif
        }
      #endif


      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        /**
        * \TestCaseName TRBSYS_GuardConfig_005
        *
        * \Reference
        * RBSYS_GRAMGuardInit, Gen_SWCS_HSW_uC_Base_SYS-287, Gen_SWCS_HSW_uC_Base_SYS-303, Gen_SWCS_HSW_uC_Base_SYS-306, Gen_SWCS_HSW_uC_Base_SYS-307
        *
        * \Purpose Test functionality of the RBSYS_GRAMGuardInit (i.e. all expected registers are set to the expected values)
        *
        * \Sequence
        *  1. call the function RBSYS_GRAMGuardInit
        *  2. check that the expected values are put into the registers
        *
        * \ExpectedResult
        * All affected registers must be set to the expected values.
        *
        */
        SWTEST void TRBSYS_GuardConfig_005(void)
        {
          MGDGRPROT0 = 0x11u;
          MGDGRPROT1 = 0x22u;
          MGDGRPROT2 = 0x33u;
          MGDGRPROT3 = 0x44u;
          MGDGRPROT4 = 0x55u;
          MGDGRPROT5 = 0x66u;
          MGDGRPROT6 = 0x77u;
          MGDGRPROT7 = 0x88u;
          APBFSGDPROT_SP4_B = 0;

          RBSYS_SetBusMasterIDs();
          RBSYS_GRAMGuardInit();

          SWT_EvalEqX(APBFSGDPROT_SP4_B, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));

          #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)

            SWT_EvalEqX(MGDGRBAD0, 0x00100000u);
            SWT_EvalEqX(MGDGRADV0, 0x00100000u);

            SWT_EvalEqX(MGDGRBAD1, 0x000FC000u);
            SWT_EvalEqX(MGDGRADV1, 0x001FC000u);

            SWT_EvalEqX(MGDGRBAD2, 0x000F8000u);
            SWT_EvalEqX(MGDGRADV2, 0x001FC000u);

            SWT_EvalEqX(MGDGRBAD3, 0x000F0000u);
            SWT_EvalEqX(MGDGRADV3, 0x001F8000u);

            SWT_EvalEqX(MGDGRBAD4, 0x000E0000u);
            SWT_EvalEqX(MGDGRADV4, 0x001F0000u);

            SWT_EvalEqX(MGDGRBAD5, 0x000C0000u);
            SWT_EvalEqX(MGDGRADV5, 0x001E0000u);

            SWT_EvalEqX(MGDGRBAD6, 0x00080000u);
            SWT_EvalEqX(MGDGRADV6, 0x001C0000u);

            SWT_EvalEqX(MGDGRBAD7, 0x00000000u);
            SWT_EvalEqX(MGDGRADV7, 0x00180000u);


            SWT_EvalEqX(MGDGRSPID0, 0x4u);

            #if(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_0K)
              SWT_EvalEqX(MGDGRSPID1, 0x4u);
              SWT_EvalEqX(MGDGRSPID2, 0x4u);
            #elif(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_16K)
              #if(RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted)
              SWT_EvalEqX(MGDGRSPID1, 0x17u);
              #else
              SWT_EvalEqX(MGDGRSPID1, 0x7u);
              #endif
              #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K)
              SWT_EvalEqX(MGDGRSPID2, 0x10u);
              #else
              SWT_EvalEqX(MGDGRSPID2, 0x4u);
              #endif
            #elif(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_32K)
              #if(RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted)
                SWT_EvalEqX(MGDGRSPID1, 0x17u);
                SWT_EvalEqX(MGDGRSPID2, 0x17u);
              #else
                #if( (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR) && (RBFS_SysEthSharedGRAMsize != RBFS_SysEthSharedGRAMsize_128K) )
                  SWT_EvalEqX(MGDGRSPID1, 0x4u); //SAFE
                  SWT_EvalEqX(MGDGRSPID2, 0x4u); //SAFE
                #else
                  SWT_EvalEqX(MGDGRSPID1, 0x7u); //SAFE+SECURE
                  SWT_EvalEqX(MGDGRSPID2, 0x7u); //SAFE+SECURE
                #endif
              #endif
            #else
              /* should not be the case as the AssertSwitchSettings ensures one of the settings */
              #error ("Invalid setting of RBFS_SysHsmSharedGRAMsize!")
            #endif

            #if ((RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_32K) \
              || (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K) \
              || ((RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR)&&(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K)) \
                )
              SWT_EvalEqX(MGDGRSPID3, 0xCu);
            #else
              #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K)
                SWT_EvalEqX(MGDGRSPID3, 0x14u); //< SAFE or RESTRICTED
              #else
                SWT_EvalEqX(MGDGRSPID3, 0x4u);
              #endif
            #endif
            #if ((RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_64K) \
              || (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K) \
              || ((RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR)&&(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K)) \
                )
              SWT_EvalEqX(MGDGRSPID4, 0xCu);
            #else
              SWT_EvalEqX(MGDGRSPID4, 0x4u);
            #endif
            #if (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K) && (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_Default)
              SWT_EvalEqX(MGDGRSPID5, 0xCu);
            #elif( RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR )
              SWT_EvalEqX(MGDGRSPID5, 0x7u);
            #else
              SWT_EvalEqX(MGDGRSPID5, 0x4u);
            #endif
            SWT_EvalEqX(MGDGRSPID6, 0x4u);
            SWT_EvalEqX(MGDGRSPID7, 0x4u);

            SWT_EvalEqX(MGDGRPROT0, 0x40000011u);
            SWT_EvalEqX(MGDGRPROT1, 0x40000022u);
            SWT_EvalEqX(MGDGRPROT2, 0x40000033u);
            SWT_EvalEqX(MGDGRPROT3, 0x40000044u);
            SWT_EvalEqX(MGDGRPROT4, 0x40000055u);
            SWT_EvalEqX(MGDGRPROT5, 0x40000066u);
            SWT_EvalEqX(MGDGRPROT6, 0x40000077u);
            SWT_EvalEqX(MGDGRPROT7, 0x40000088u);

          #else
            /* no setting/modification of registers */
            SWT_EvalEqX(MGDGRBAD0, 0);
            SWT_EvalEqX(MGDGRADV0, 0);
            SWT_EvalEqX(MGDGRBAD1, 0);
            SWT_EvalEqX(MGDGRADV1, 0);
            SWT_EvalEqX(MGDGRBAD2, 0);
            SWT_EvalEqX(MGDGRADV2, 0);
            SWT_EvalEqX(MGDGRBAD3, 0);
            SWT_EvalEqX(MGDGRADV3, 0);
            SWT_EvalEqX(MGDGRBAD4, 0);
            SWT_EvalEqX(MGDGRADV4, 0);
            SWT_EvalEqX(MGDGRBAD5, 0);
            SWT_EvalEqX(MGDGRADV5, 0);
            SWT_EvalEqX(MGDGRBAD6, 0);
            SWT_EvalEqX(MGDGRADV6, 0);
            SWT_EvalEqX(MGDGRBAD7, 0);
            SWT_EvalEqX(MGDGRADV7, 0);


            SWT_EvalEqX(MGDGRSPID0, 0);
            SWT_EvalEqX(MGDGRSPID1, 0);
            SWT_EvalEqX(MGDGRSPID2, 0);
            SWT_EvalEqX(MGDGRSPID3, 0);
            SWT_EvalEqX(MGDGRSPID4, 0);
            SWT_EvalEqX(MGDGRSPID5, 0);
            SWT_EvalEqX(MGDGRSPID6, 0);
            SWT_EvalEqX(MGDGRSPID7, 0);

            SWT_EvalEqX(MGDGRPROT0, 0x11u);
            SWT_EvalEqX(MGDGRPROT1, 0x22u);
            SWT_EvalEqX(MGDGRPROT2, 0x33u);
            SWT_EvalEqX(MGDGRPROT3, 0x44u);
            SWT_EvalEqX(MGDGRPROT4, 0x55u);
            SWT_EvalEqX(MGDGRPROT5, 0x66u);
            SWT_EvalEqX(MGDGRPROT6, 0x77u);
            SWT_EvalEqX(MGDGRPROT7, 0x88u);

          #endif
        }
      #endif



      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      /**
      * \TestCaseName TRBSYS_GuardConfig_007
      *
      * \Reference
      * RBSYS_BasicGuardInit, Gen_SWCS_HSW_uC_Base_SYS-287, Gen_SWCS_HSW_uC_Base_SYS-303, Gen_SWCS_HSW_uC_Base_SYS-306, Gen_SWCS_HSW_uC_Base_SYS-307
      *
      * \Purpose Test functionality of the RBSYS_BasicGuardInit (i.e. RBSYS_setCoreSPID, RBSYS_PEGuardInit are called, RBSYS_PBUSGuardInit and RBSYS_GRAMGuardInit only for core 0)
      *
      * \Sequence
      *  1. call the function RBSYS_BasicGuardInit
      *  2. check that all registers are set (indirectly by the called functions)
      *
      * \ExpectedResult
      * All affected registers must be set to the expected values.
      *
      */
      SWTEST void TRBSYS_GuardConfig_007(void)
      {
          /* init registers */
          FSGD1B.PROT10 = 0x77u;
          FSGD1B.PROT11 = 0x88u;
          FSGD1B.PROT12 = 0x99u;
          FSGD1B.PROT13 = 0x11u;
          FSGD2A.PROT04 = 0x22u;
          FSGD2A.PROT05 = 0x33u;
          FSGD2A.PROT06 = 0x44u;
          FSGD3B.PROT10 = 0x55u;
          FSGD3B.PROT11 = 0x66u;
          FSGD3B.PROT12 = 0xAAu;
          FSGD3B.PROT13 = 0xBBu;
          FSGD4A.PROT06 = 0xCCu;
          FSGD4A.PROT08 = 0xDDu;
          MGDGRPROT0 = 0x11u;
          MGDGRPROT1 = 0x22u;
          MGDGRPROT2 = 0x33u;
          MGDGRPROT3 = 0x44u;
          MGDGRPROT4 = 0x55u;
          MGDGRPROT5 = 0x66u;
          MGDGRPROT6 = 0x77u;
          MGDGRPROT7 = 0x88u;
          HSSPIDRG0 = 0;
          HSSPIDRG1 = 0;
          HSSPIDRG2 = 0;
          HSSPIDRG3 = 0;
          HSSPIDRG4 = 0;
          HSSPIDRG5 = 0;
          HSSPIDRG6 = 0;
          HSSPIDRG7 = 0;

          /* ******************* */
          /* set Core to 0 */
          /* ******************* */
          TRBSYS_setCoreID(0);

          RBSYS_BasicGuardInit();
          RBSYS_SetBusMasterIDs();
          RBSYS_GRAMGuardInit();
          RBSYS_EnhancedGuardInit();

          /* RBSYS_EnhancedGuardInit does guard itself against being called from Core != Core 0 */
          TRBSYS_setCoreID(1);
          RBSYS_EnhancedGuardInit();
          TRBSYS_setCoreID(0);

          #if( RBFS_SysEnvironment == RBFS_SysEnvironment_Target ) //< Core SPID is set via ASM function which can only be tested in target build
            /* ********************************* */
            /* RBSYS_setCoreSPID to 2 (SafeSPID) */
            /* ********************************* */
            SWT_EvalEqX(((TRBSYS_GetSystemRegister(0,1) >> 16) & 0x1F), 2);
          #endif

          /* ******************** */
          /* RBSYS_setUnsafeSPIDs */
          /* ******************** */
          #if( (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2) \
            || (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD3ED) \
            )
            SWT_EvalEqX(HSSPIDRG0, UnSafeSPID);
            SWT_EvalEqX(HSSPIDRG2, UnSafeSPID);
            SWT_EvalEqX(HSSPIDRG4, UnSafeSPID);
            SWT_EvalEqX(HSSPIDRG5, UnSafeSPID);

            #if ((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5))
              SWT_EvalEqX(HSSPIDRG1, UnSafeSPID);
              SWT_EvalEqX(HSSPIDRG3, UnSafeSPID);
              SWT_EvalEqX(HSSPIDRG6, UnSafeSPID);
              SWT_EvalEqX(HSSPIDRG7, UnSafeSPID);
            #else
              SWT_EvalEqX(HSSPIDRG1, 0);
              SWT_EvalEqX(HSSPIDRG3, 0);
              SWT_EvalEqX(HSSPIDRG6, 0);
              SWT_EvalEqX(HSSPIDRG7, 0);
            #endif
          #else
            SWT_EvalEqX(HSSPIDRG0, 0);
            SWT_EvalEqX(HSSPIDRG1, 0);
            SWT_EvalEqX(HSSPIDRG2, 0);
            SWT_EvalEqX(HSSPIDRG3, 0);
            SWT_EvalEqX(HSSPIDRG4, 0);
            SWT_EvalEqX(HSSPIDRG5, 0);
            SWT_EvalEqX(HSSPIDRG6, 0);
            SWT_EvalEqX(HSSPIDRG7, 0);
          #endif

          /* ***************** */
          /* RBSYS_PEGuardInit */
          /* ***************** */
          SWT_EvalEqX(PEGG0MK, 0x003FF000u);
          SWT_EvalEqX(PEGG0SP, 0x3u);
          SWT_EvalEqX(PEGG0BA, 0xFE800003u);
          SWT_EvalEqX(PEGG1MK, 0x003FF000u);
          SWT_EvalEqX(PEGG1SP, 0x4u);
          SWT_EvalEqX(PEGG1BA, 0xFE800007u);

          /* ******************* */
          /* RBSYS_PBUSGuardInit */
          /* ******************* */
          SWT_EvalEqX(FSGD1B.PROT10, 0x200077u);
          SWT_EvalEqX(FSGD1B.PROT11, 0x200088u);

          //Renesas devices D1 and D2 do only have CSIH0 - CSIH2
          #if((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2))
            SWT_EvalEqX(FSGD1B.PROT12, 0x200099u);
            SWT_EvalEqX(FSGD1B.PROT13, 0x200011u);
          #else
            SWT_EvalEqX(FSGD1B.PROT12, 0x99u);
            SWT_EvalEqX(FSGD1B.PROT13, 0x11u);
          #endif

          SWT_EvalEqX(FSGD2A.PROT04, 0x200022u);
          SWT_EvalEqX(FSGD2A.PROT05, 0x200033u);
          SWT_EvalEqX(FSGD2A.PROT06, 0x200044u);
          SWT_EvalEqX(FSGD3B.PROT10, 0x200055u);
          SWT_EvalEqX(FSGD3B.PROT11, 0x200066u);
          SWT_EvalEqX(FSGD3B.PROT12, 0x2000AAu);
          SWT_EvalEqX(FSGD3B.PROT13, 0x2000BBu);
          SWT_EvalEqX(FSGD4A.PROT06, 0x2000CCu);

          // Renesas devices D1 and D2 do only have one ADC unit
          #if((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2))
            SWT_EvalEqX(FSGD4A.PROT08, 0x2000DDu);
          #else
            SWT_EvalEqX(FSGD4A.PROT08, 0xDDu);
          #endif

            /* ******************* */
            /* RBSYS_GRAMGuardInit */
            /* ******************* */
          SWT_EvalEqX(APBFSGDPROT_SP4_B, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));

        #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)

          SWT_EvalEqX(MGDGRBAD0, 0x00100000u);
          SWT_EvalEqX(MGDGRADV0, 0x00100000u);

          SWT_EvalEqX(MGDGRBAD1, 0x000FC000u);
          SWT_EvalEqX(MGDGRADV1, 0x001FC000u);

          SWT_EvalEqX(MGDGRBAD2, 0x000F8000u);
          SWT_EvalEqX(MGDGRADV2, 0x001FC000u);

          SWT_EvalEqX(MGDGRBAD3, 0x000F0000u);
          SWT_EvalEqX(MGDGRADV3, 0x001F8000u);

          SWT_EvalEqX(MGDGRBAD4, 0x000E0000u);
          SWT_EvalEqX(MGDGRADV4, 0x001F0000u);

          SWT_EvalEqX(MGDGRBAD5, 0x000C0000u);
          SWT_EvalEqX(MGDGRADV5, 0x001E0000u);

          SWT_EvalEqX(MGDGRBAD6, 0x00080000u);
          SWT_EvalEqX(MGDGRADV6, 0x001C0000u);

          SWT_EvalEqX(MGDGRBAD7, 0x00000000u);
          SWT_EvalEqX(MGDGRADV7, 0x00180000u);


          SWT_EvalEqX(MGDGRSPID0, 0x4u);

          #if(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_0K)
            SWT_EvalEqX(MGDGRSPID1, 0x4u);
            SWT_EvalEqX(MGDGRSPID2, 0x4u);
          #elif(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_16K)
            #if(RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted)
            SWT_EvalEqX(MGDGRSPID1, 0x17u);
            #else
            SWT_EvalEqX(MGDGRSPID1, 0x7u);
            #endif
            #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K)
            SWT_EvalEqX(MGDGRSPID2, 0x10u);
            #else
            SWT_EvalEqX(MGDGRSPID2, 0x4u);
            #endif
          #elif(RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_32K)
            #if(RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted)
            SWT_EvalEqX(MGDGRSPID1, 0x17u);
            SWT_EvalEqX(MGDGRSPID2, 0x17u);
            #else
              #if( (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR) && (RBFS_SysEthSharedGRAMsize != RBFS_SysEthSharedGRAMsize_128K) )
                SWT_EvalEqX(MGDGRSPID1, 0x4u); //SAFE
                SWT_EvalEqX(MGDGRSPID2, 0x4u); //SAFE
              #else
                SWT_EvalEqX(MGDGRSPID1, 0x7u); //SAFE+SECURE
                SWT_EvalEqX(MGDGRSPID2, 0x7u); //SAFE+SECURE
              #endif
            #endif
          #else
            /* should not be the case as the AssertSwitchSettings ensures one of the settings */
            #error ("Invalid setting of RBFS_SysHsmSharedGRAMsize!")
          #endif

          #if ((RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_32K) \
            || (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K) \
            || ((RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR)&&(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K)) \
              )
            SWT_EvalEqX(MGDGRSPID3, 0xCu);
          #else
            #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K)
            SWT_EvalEqX(MGDGRSPID3, 0x14u); //< SAFE or RESTRICTED
            #else
            SWT_EvalEqX(MGDGRSPID3, 0x4u);
            #endif
          #endif
          #if ((RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_64K) \
            || (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K) \
            || ((RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR)&&(RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K)) \
              )
            SWT_EvalEqX(MGDGRSPID4, 0xCu);
          #else
            SWT_EvalEqX(MGDGRSPID4, 0x4u);
          #endif
          #if (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K) && (RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_Default)
            SWT_EvalEqX(MGDGRSPID5, 0xCu);
          #elif( RBFS_SysRAMLayoutFragmentation == RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR )
            SWT_EvalEqX(MGDGRSPID5, 0x7u);
          #else
            SWT_EvalEqX(MGDGRSPID5, 0x4u);
          #endif
          SWT_EvalEqX(MGDGRSPID6, 0x4u);
          SWT_EvalEqX(MGDGRSPID7, 0x4u);


          SWT_EvalEqX(MGDGRPROT0, 0x40000011u);
          SWT_EvalEqX(MGDGRPROT1, 0x40000022u);
          SWT_EvalEqX(MGDGRPROT2, 0x40000033u);
          SWT_EvalEqX(MGDGRPROT3, 0x40000044u);
          SWT_EvalEqX(MGDGRPROT4, 0x40000055u);
          SWT_EvalEqX(MGDGRPROT5, 0x40000066u);
          SWT_EvalEqX(MGDGRPROT6, 0x40000077u);
          SWT_EvalEqX(MGDGRPROT7, 0x40000088u);

        #else
          /* no setting/modification of registers */
          SWT_EvalEqX(MGDGRBAD0, 0);
          SWT_EvalEqX(MGDGRADV0, 0);
          SWT_EvalEqX(MGDGRBAD1, 0);
          SWT_EvalEqX(MGDGRADV1, 0);
          SWT_EvalEqX(MGDGRBAD2, 0);
          SWT_EvalEqX(MGDGRADV2, 0);
          SWT_EvalEqX(MGDGRBAD3, 0);
          SWT_EvalEqX(MGDGRADV3, 0);
          SWT_EvalEqX(MGDGRBAD4, 0);
          SWT_EvalEqX(MGDGRADV4, 0);
          SWT_EvalEqX(MGDGRBAD5, 0);
          SWT_EvalEqX(MGDGRADV5, 0);
          SWT_EvalEqX(MGDGRBAD6, 0);
          SWT_EvalEqX(MGDGRADV6, 0);
          SWT_EvalEqX(MGDGRBAD7, 0);
          SWT_EvalEqX(MGDGRADV7, 0);


          SWT_EvalEqX(MGDGRSPID0, 0);
          SWT_EvalEqX(MGDGRSPID1, 0);
          SWT_EvalEqX(MGDGRSPID2, 0);
          SWT_EvalEqX(MGDGRSPID3, 0);
          SWT_EvalEqX(MGDGRSPID4, 0);
          SWT_EvalEqX(MGDGRSPID5, 0);
          SWT_EvalEqX(MGDGRSPID6, 0);
          SWT_EvalEqX(MGDGRSPID7, 0);

          SWT_EvalEqX(MGDGRPROT0, 0x11u);
          SWT_EvalEqX(MGDGRPROT1, 0x22u);
          SWT_EvalEqX(MGDGRPROT2, 0x33u);
          SWT_EvalEqX(MGDGRPROT3, 0x44u);
          SWT_EvalEqX(MGDGRPROT4, 0x55u);
          SWT_EvalEqX(MGDGRPROT5, 0x66u);
          SWT_EvalEqX(MGDGRPROT6, 0x77u);
          SWT_EvalEqX(MGDGRPROT7, 0x88u);

        #endif


          /* re-init registers */
          FSGD1B.PROT10 = 0x77u;
          FSGD1B.PROT11 = 0x88u;
          FSGD1B.PROT12 = 0x99u;
          FSGD1B.PROT13 = 0x11u;
          FSGD2A.PROT04 = 0x22u;
          FSGD2A.PROT05 = 0x33u;
          FSGD2A.PROT06 = 0x44u;
          FSGD3B.PROT10 = 0x55u;
          FSGD3B.PROT11 = 0x66u;
          FSGD3B.PROT12 = 0xAAu;
          FSGD3B.PROT13 = 0xBBu;
          FSGD4A.PROT06 = 0xCCu;
          FSGD4A.PROT08 = 0xDDu;
          MGDGRBAD0 = 0;
          MGDGRBAD1 = 0;
          MGDGRBAD2 = 0;
          MGDGRBAD3 = 0;
          MGDGRBAD4 = 0;
          MGDGRBAD5 = 0;
          MGDGRBAD6 = 0;
          MGDGRBAD7 = 0;
          MGDGRADV0 = 0;
          MGDGRADV1 = 0;
          MGDGRADV2 = 0;
          MGDGRADV3 = 0;
          MGDGRADV4 = 0;
          MGDGRADV5 = 0;
          MGDGRADV6 = 0;
          MGDGRADV7 = 0;
          MGDGRSPID0 = 0;
          MGDGRSPID1 = 0;
          MGDGRSPID2 = 0;
          MGDGRSPID3 = 0;
          MGDGRSPID4 = 0;
          MGDGRSPID5 = 0;
          MGDGRSPID6 = 0;
          MGDGRSPID7 = 0;
          MGDGRPROT0 = 0x11u;
          MGDGRPROT1 = 0x22u;
          MGDGRPROT2 = 0x33u;
          MGDGRPROT3 = 0x44u;
          MGDGRPROT4 = 0x55u;
          MGDGRPROT5 = 0x66u;
          MGDGRPROT6 = 0x77u;
          MGDGRPROT7 = 0x88u;
          HSSPIDRG0 = 0;
          HSSPIDRG1 = 0;
          HSSPIDRG2 = 0;
          HSSPIDRG3 = 0;
          HSSPIDRG4 = 0;
          HSSPIDRG5 = 0;
          HSSPIDRG6 = 0;
          HSSPIDRG7 = 0;


        /* ******************* */
        /* set Core to 1 */
        /* ******************* */
        TRBSYS_setCoreID(1);

        RBSYS_BasicGuardInit();

        #if( RBFS_SysEnvironment == RBFS_SysEnvironment_Target ) //< Core SPID is set via ASM function which can only be tested in target build
          /* ********************************* */
          /* RBSYS_setCoreSPID to 2 (SafeSPID) */
          /* ********************************* */
          SWT_EvalEqX(((TRBSYS_GetSystemRegister(0,1) >> 16) & 0x1F), 2);
        #endif

        /* ******************** */
        /* RBSYS_setUnsafeSPIDs */
        /* ******************** */
        // Only done for core 0
        SWT_EvalEqX(HSSPIDRG0, 0);
        SWT_EvalEqX(HSSPIDRG1, 0);
        SWT_EvalEqX(HSSPIDRG2, 0);
        SWT_EvalEqX(HSSPIDRG3, 0);
        SWT_EvalEqX(HSSPIDRG4, 0);
        SWT_EvalEqX(HSSPIDRG5, 0);
        SWT_EvalEqX(HSSPIDRG6, 0);
        SWT_EvalEqX(HSSPIDRG7, 0);

        /* ***************** */
        /* RBSYS_PEGuardInit */
        /* ***************** */
        SWT_EvalEqX(PEGG0MK, 0x003FF000u);
        SWT_EvalEqX(PEGG0SP, 0x3u);
        SWT_EvalEqX(PEGG0BA, 0xFE800003u);
        SWT_EvalEqX(PEGG1MK, 0x003FF000u);
        SWT_EvalEqX(PEGG1SP, 0x4u);
        SWT_EvalEqX(PEGG1BA, 0xFE800007u);

        /* ************************************************* */
        /* RBSYS_PBUSGuardInit   registers not set on core 1 */
        /* ************************************************* */
        SWT_EvalEqX(FSGD1B.PROT10, 0x77u);
        SWT_EvalEqX(FSGD1B.PROT11, 0x88u);
        SWT_EvalEqX(FSGD1B.PROT12, 0x99u);
        SWT_EvalEqX(FSGD1B.PROT13, 0x11u);
        SWT_EvalEqX(FSGD2A.PROT04, 0x22u);
        SWT_EvalEqX(FSGD2A.PROT05, 0x33u);
        SWT_EvalEqX(FSGD2A.PROT06, 0x44u);
        SWT_EvalEqX(FSGD3B.PROT10, 0x55u);
        SWT_EvalEqX(FSGD3B.PROT11, 0x66u);
        SWT_EvalEqX(FSGD3B.PROT12, 0xAAu);
        SWT_EvalEqX(FSGD3B.PROT13, 0xBBu);
        SWT_EvalEqX(FSGD4A.PROT06, 0xCCu);
        SWT_EvalEqX(FSGD4A.PROT08, 0xDDu);

        /* ************************************************* */
        /* RBSYS_GRAMGuardInit   registers not set on core 1 */
        /* ************************************************* */
        SWT_EvalEqX(APBFSGDPROT_SP4_B, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));

        /* no setting/modification of registers */
        SWT_EvalEqX(MGDGRBAD0, 0);
        SWT_EvalEqX(MGDGRADV0, 0);
        SWT_EvalEqX(MGDGRBAD1, 0);
        SWT_EvalEqX(MGDGRADV1, 0);
        SWT_EvalEqX(MGDGRBAD2, 0);
        SWT_EvalEqX(MGDGRADV2, 0);
        SWT_EvalEqX(MGDGRBAD3, 0);
        SWT_EvalEqX(MGDGRADV3, 0);
        SWT_EvalEqX(MGDGRBAD4, 0);
        SWT_EvalEqX(MGDGRADV4, 0);
        SWT_EvalEqX(MGDGRBAD5, 0);
        SWT_EvalEqX(MGDGRADV5, 0);
        SWT_EvalEqX(MGDGRBAD6, 0);
        SWT_EvalEqX(MGDGRADV6, 0);
        SWT_EvalEqX(MGDGRBAD7, 0);
        SWT_EvalEqX(MGDGRADV7, 0);


        SWT_EvalEqX(MGDGRSPID0, 0);
        SWT_EvalEqX(MGDGRSPID1, 0);
        SWT_EvalEqX(MGDGRSPID2, 0);
        SWT_EvalEqX(MGDGRSPID3, 0);
        SWT_EvalEqX(MGDGRSPID4, 0);
        SWT_EvalEqX(MGDGRSPID5, 0);
        SWT_EvalEqX(MGDGRSPID6, 0);
        SWT_EvalEqX(MGDGRSPID7, 0);

        SWT_EvalEqX(MGDGRPROT0, 0x11u);
        SWT_EvalEqX(MGDGRPROT1, 0x22u);
        SWT_EvalEqX(MGDGRPROT2, 0x33u);
        SWT_EvalEqX(MGDGRPROT3, 0x44u);
        SWT_EvalEqX(MGDGRPROT4, 0x55u);
        SWT_EvalEqX(MGDGRPROT5, 0x66u);
        SWT_EvalEqX(MGDGRPROT6, 0x77u);
        SWT_EvalEqX(MGDGRPROT7, 0x88u);
      }
      #endif


      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      /**
      * \TestCaseName TRBSYS_GuardConfig_008
      *
      * \Reference
      * RBSYS_PRC_FSW_FinalGuard_Init, Gen_SWCS_HSW_uC_Base_SYS-287,Gen_SWCS_HSW_uC_Base_SYS-306, Gen_SWCS_HSW_uC_Base_SYS-307
      *
      * \Purpose Test functionality of the RBSYS_FSW_FinalGuardInit (RBSYS_GRAMGuardLock only for core 0)
      *
      * \Sequence
      *  1. call the function RBSYS_FSW_FinalGuardInit
      *  2. check that all registers are locked as expected
      *  3. Run the verify function also with manipulated values, i.e. not-as-expected
      *
      * \ExpectedResult
      * All all guard registers must be locked as expected. *
      */
      SWTEST void TRBSYS_GuardConfig_008(void)
      {
        /* init registers */
        MGDGRPROT0 = 0x11u;
        MGDGRPROT1 = 0x22u;
        MGDGRPROT2 = 0x33u;
        MGDGRPROT3 = 0x44u;
        MGDGRPROT4 = 0x55u;
        MGDGRPROT5 = 0x66u;
        MGDGRPROT6 = 0x77u;
        MGDGRPROT7 = 0x88u;

        APBFSGDPROT_PDMACM_A = 0;
        APBFSGDPROT_PDMACM_B = 0;
        APBFSGDPROT_PDMACH_A = 0;
        APBFSGDPROT_PDMACH_B = 0;
        APBFSGDPROT_INTC2_A = 0;
        APBFSGDPROT_INTC2_B = 0;
        APBFSGDPROT_PBG_A = 0;
        APBFSGDPROT_PBG_B = 0;
        APBFSGDPROT_SP1_A = 0;
        APBFSGDPROT_SP1_B = 0;
        APBFSGDPROT_SP2_A = 0;
        APBFSGDPROT_SP2_B = 0;
        APBFSGDPROT_SP4_A = 0;
        APBFSGDPROT_SP4_B = 0;
        FSGD1APROT00 = 0;
        FSGD1APROT01 = 0;
        FSGD1APROT02 = 0;
        FSGD1APROT03 = 0;
        FSGD1APROT04 = 0;
        FSGD1APROT05 = 0;
        FSGD1APROT06 = 0;
        FSGD1APROT07 = 0;
        FSGD1BPROT00 = 0;
        FSGD1BPROT01 = 0;
        FSGD1BPROT02 = 0;
        FSGD1BPROT03 = 0;
        FSGD1BPROT06 = 0;
        FSGD1BPROT07 = 0;
        FSGD1BPROT08 = 0;
        FSGD1BPROT09 = 0;
        FSGD1BPROT10 = 0;
        FSGD1BPROT11 = 0;
        FSGD1BPROT12 = 0;
        FSGD1BPROT13 = 0;
        FSGD2APROT00 = 0;
        FSGD2APROT01 = 0;
        FSGD2APROT02 = 0;
        FSGD2APROT03 = 0;
        FSGD2APROT04 = 0;
        FSGD2APROT05 = 0;
        FSGD2APROT06 = 0;
        FSGD2APROT07 = 0;
        FSGD2APROT08 = 0;
        FSGD2APROT09 = 0;
        FSGD2APROT10 = 0;
        FSGD2APROT11 = 0;
        FSGD2APROT12 = 0;
        FSGD2APROT13 = 0;
        FSGD3APROT00 = 0;
        FSGD3APROT01 = 0;
        FSGD3APROT02 = 0;
        FSGD3APROT03 = 0;
        FSGD3APROT04 = 0;
        FSGD3APROT05 = 0;
        FSGD3APROT06 = 0;
        FSGD3APROT07 = 0;
        FSGD3APROT08 = 0;
        FSGD3APROT09 = 0;
        FSGD3APROT10 = 0;
        FSGD3APROT11 = 0;
        FSGD3APROT12 = 0;
        FSGD3APROT13 = 0;
        FSGD3APROT14 = 0;
        FSGD3APROT15 = 0;
        FSGD3BPROT00 = 0;
        FSGD3BPROT01 = 0;
        FSGD3BPROT02 = 0;
        FSGD3BPROT03 = 0;
        FSGD3BPROT06 = 0;
        FSGD3BPROT07 = 0;
        FSGD3BPROT08 = 0;
        FSGD3BPROT09 = 0;
        FSGD3BPROT10 = 0;
        FSGD3BPROT11 = 0;
        FSGD3BPROT12 = 0;
        FSGD3BPROT13 = 0;
        FSGD4APROT00 = 0;
        FSGD4APROT01 = 0;
        FSGD4APROT02 = 0;
        FSGD4APROT03 = 0;
        FSGD4APROT04 = 0;
        FSGD4APROT05 = 0;
        FSGD4APROT06 = 0;
        FSGD4APROT07 = 0;
        FSGD4APROT08 = 0;
        FSGD4APROT09 = 0;
        FSGD4APROT10 = 0;
        FSGD4APROT11 = 0;
        FSGD4APROT12 = 0;
        FSGD4APROT13 = 0;
        FSGD4APROT14 = 0;
        FSGD4APROT15 = 0;
        FSGD4BPROT00 = 0;
        FSGD4BPROT01 = 0;
        FSGD4BPROT02 = 0;
        FSGD4BPROT03 = 0;
        FSGD4BPROT04 = 0;
        FSGD4BPROT05 = 0;
        FSGD4BPROT06 = 0;
        FSGD4BPROT07 = 0;
        FSGD4BPROT08 = 0;
        FSGD4BPROT09 = 0;
        FSGD4BPROT10 = 0;
        FSGD4BPROT11 = 0;
        FSGD4BPROT12 = 0;
        FSGD4BPROT13 = 0;
        FSGD4CPROT00 = 0;
        FSGD4CPROT01 = 0;
        FSGD4CPROT02 = 0;
        FSGD4CPROT03 = 0;
        FSGD4CPROT04 = 0;
        FSGD4CPROT05 = 0;
        FSGD4CPROT06 = 0;
        FSGD4CPROT07 = 0;
        FSGD4CPROT08 = 0;
        FSGD4CPROT09 = 0;
        FSGD4CPROT10 = 0;
        FSGD4CPROT11 = 0;
        FSGD4CPROT12 = 0;
        FSGD4CPROT13 = 0;
        FSGD5APROT00 = 0;
        FSGD5APROT01 = 0;
        FSGD5APROT02 = 0;
        FSGD5APROT03 = 0;
        FSGD5APROT04 = 0;
        FSGD5APROT05 = 0;
        FSGD5BPROT00 = 0;
        FSGD5BPROT01 = 0;
        FSGD5BPROT02 = 0;
        FSGD5BPROT03 = 0;
        FSGD5CPROT00 = 0;
        FSGD5CPROT01 = 0;
        FSGD5DPROT00 = 0;
        FSGD5DPROT01 = 0;
        FSGD5DPROT02 = 0;
        FSGD5DPROT03 = 0;

        APBFSGDSPID_PDMACM_A = 0;
        APBFSGDSPID_PDMACM_B = 0;
        APBFSGDSPID_PDMACH_A = 0;
        APBFSGDSPID_PDMACH_B = 0;
        APBFSGDSPID_INTC2_A = 0;
        APBFSGDSPID_INTC2_B = 0;
        APBFSGDSPID_PBG_A = 0;
        APBFSGDSPID_PBG_B = 0;
        APBFSGDSPID_SP1_A = 0;
        APBFSGDSPID_SP1_B = 0;
        APBFSGDSPID_SP2_A = 0;
        APBFSGDSPID_SP2_B = 0;
        APBFSGDSPID_SP4_A = 0;
        APBFSGDSPID_SP4_B = 0;
        FSGD1ASPID00 = 0;
        FSGD1ASPID01 = 0;
        FSGD1ASPID02 = 0;
        FSGD1ASPID03 = 0;
        FSGD1ASPID04 = 0;
        FSGD1ASPID05 = 0;
        FSGD1ASPID06 = 0;
        FSGD1ASPID07 = 0;
        FSGD1BSPID00 = 0;
        FSGD1BSPID01 = 0;
        FSGD1BSPID02 = 0;
        FSGD1BSPID03 = 0;
        FSGD1BSPID06 = 0;
        FSGD1BSPID07 = 0;
        FSGD1BSPID08 = 0;
        FSGD1BSPID09 = 0;
        FSGD1BSPID10 = 0;
        FSGD1BSPID11 = 0;
        FSGD1BSPID12 = 0;
        FSGD1BSPID13 = 0;
        FSGD2ASPID00 = 0;
        FSGD2ASPID01 = 0;
        FSGD2ASPID02 = 0;
        FSGD2ASPID03 = 0;
        FSGD2ASPID04 = 0;
        FSGD2ASPID05 = 0;
        FSGD2ASPID06 = 0;
        FSGD2ASPID07 = 0;
        FSGD2ASPID08 = 0;
        FSGD2ASPID09 = 0;
        FSGD2ASPID10 = 0;
        FSGD2ASPID11 = 0;
        FSGD2ASPID12 = 0;
        FSGD2ASPID13 = 0;
        FSGD3ASPID00 = 0;
        FSGD3ASPID01 = 0;
        FSGD3ASPID02 = 0;
        FSGD3ASPID03 = 0;
        FSGD3ASPID04 = 0;
        FSGD3ASPID05 = 0;
        FSGD3ASPID06 = 0;
        FSGD3ASPID07 = 0;
        FSGD3ASPID08 = 0;
        FSGD3ASPID09 = 0;
        FSGD3ASPID10 = 0;
        FSGD3ASPID11 = 0;
        FSGD3ASPID12 = 0;
        FSGD3ASPID13 = 0;
        FSGD3ASPID14 = 0;
        FSGD3ASPID15 = 0;
        FSGD3BSPID00 = 0;
        FSGD3BSPID01 = 0;
        FSGD3BSPID02 = 0;
        FSGD3BSPID03 = 0;
        FSGD3BSPID06 = 0;
        FSGD3BSPID07 = 0;
        FSGD3BSPID08 = 0;
        FSGD3BSPID09 = 0;
        FSGD3BSPID10 = 0;
        FSGD3BSPID11 = 0;
        FSGD3BSPID12 = 0;
        FSGD3BSPID13 = 0;
        FSGD4ASPID00 = 0;
        FSGD4ASPID01 = 0;
        FSGD4ASPID02 = 0;
        FSGD4ASPID03 = 0;
        FSGD4ASPID04 = 0;
        FSGD4ASPID05 = 0;
        FSGD4ASPID06 = 0;
        FSGD4ASPID07 = 0;
        FSGD4ASPID08 = 0;
        FSGD4ASPID09 = 0;
        FSGD4ASPID10 = 0;
        FSGD4ASPID11 = 0;
        FSGD4ASPID12 = 0;
        FSGD4ASPID13 = 0;
        FSGD4ASPID14 = 0;
        FSGD4ASPID15 = 0;
        FSGD4BSPID00 = 0;
        FSGD4BSPID01 = 0;
        FSGD4BSPID02 = 0;
        FSGD4BSPID03 = 0;
        FSGD4BSPID04 = 0;
        FSGD4BSPID05 = 0;
        FSGD4BSPID06 = 0;
        FSGD4BSPID07 = 0;
        FSGD4BSPID08 = 0;
        FSGD4BSPID09 = 0;
        FSGD4BSPID10 = 0;
        FSGD4BSPID11 = 0;
        FSGD4BSPID12 = 0;
        FSGD4BSPID13 = 0;
        FSGD4CSPID00 = 0;
        FSGD4CSPID01 = 0;
        FSGD4CSPID02 = 0;
        FSGD4CSPID03 = 0;
        FSGD4CSPID04 = 0;
        FSGD4CSPID05 = 0;
        FSGD4CSPID06 = 0;
        FSGD4CSPID07 = 0;
        FSGD4CSPID08 = 0;
        FSGD4CSPID09 = 0;
        FSGD4CSPID10 = 0;
        FSGD4CSPID11 = 0;
        FSGD4CSPID12 = 0;
        FSGD4CSPID13 = 0;
        FSGD5ASPID00 = 0;
        FSGD5ASPID01 = 0;
        FSGD5ASPID02 = 0;
        FSGD5ASPID03 = 0;
        FSGD5ASPID04 = 0;
        FSGD5ASPID05 = 0;
        FSGD5BSPID00 = 0;
        FSGD5BSPID01 = 0;
        FSGD5BSPID02 = 0;
        FSGD5BSPID03 = 0;
        FSGD5CSPID00 = 0;
        FSGD5CSPID01 = 0;
        FSGD5DSPID00 = 0;
        FSGD5DSPID01 = 0;
        FSGD5DSPID02 = 0;
        FSGD5DSPID03 = 0;

        FSGDE0SPID01 = 0;
        FSGDE0PROT01 = 0;
        FSGDF0SPID01 = 0;
        FSGDF0PROT01 = 0;
        FSGDE1SPID01 = 0;
        FSGDE1PROT01 = 0;
        FSGDF1SPID01 = 0;
        FSGDF1PROT01 = 0;
        FSGDM0SPID01 = 0;
        FSGDM0PROT01 = 0;
        FSGDM0SPID03 = 0;
        FSGDM0PROT03 = 0;
        FSGDM0SPID05 = 0;
        FSGDM0PROT05 = 0;
        FSGDM0SPID07 = 0;
        FSGDM0PROT07 = 0;
        FSGDM0SPID09 = 0;
        FSGDM0PROT09 = 0;
        FSGDE0SPID00 = 0;
        FSGDE0PROT00 = 0;
        FSGDF0SPID00 = 0;
        FSGDF0PROT00 = 0;
        FSGDE1SPID00 = 0;
        FSGDE1PROT00 = 0;
        FSGDF1SPID00 = 0;
        FSGDF1PROT00 = 0;
        FSGDM0SPID00 = 0;
        FSGDM0PROT00 = 0;
        FSGDM0SPID02 = 0;
        FSGDM0PROT02 = 0;
        FSGDM0SPID04 = 0;
        FSGDM0PROT04 = 0;
        FSGDM0SPID06 = 0;
        FSGDM0PROT06 = 0;
        FSGDM0SPID08 = 0;
        FSGDM0PROT08 = 0;


        /* ******************* */
        /* set Core to 0 */
        /* ******************* */
        TRBSYS_setCoreID(0);

        RBSYS_PRC_FSW_FinalGuard_Init();

        /* ******************* */
        /* RBSYS_GRAMGuardLock */
        /* ******************* */

        /* no setting/modification of registers -> GRAM Guards are locked upon initialization */
        SWT_EvalEqX(MGDGRPROT0, 0x11u);
        SWT_EvalEqX(MGDGRPROT1, 0x22u);
        SWT_EvalEqX(MGDGRPROT2, 0x33u);
        SWT_EvalEqX(MGDGRPROT3, 0x44u);
        SWT_EvalEqX(MGDGRPROT4, 0x55u);
        SWT_EvalEqX(MGDGRPROT5, 0x66u);
        SWT_EvalEqX(MGDGRPROT6, 0x77u);
        SWT_EvalEqX(MGDGRPROT7, 0x88u);

        /* ********************************************************************************* */
        /* write access guards - init value re-written (for PE PROT) unless stated otherwise */
        /* ********************************************************************************* */

          SWT_EvalEqX(APBFSGDSPID_PDMACM_B, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(APBFSGDPROT_PDMACM_B, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(APBFSGDSPID_PDMACH_B, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(APBFSGDPROT_PDMACH_B, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(APBFSGDSPID_INTC2_B , RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(APBFSGDPROT_INTC2_B, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(APBFSGDSPID_PBG_B   , (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK));                                             /* allow ICUM to PE1/PE2registers (default init value) */
          SWT_EvalEqX(APBFSGDPROT_PBG_B, (0x0601FE17u | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));   /* allow ICUM to PE1/PE2registers (default init value) */
          SWT_EvalEqX(APBFSGDSPID_SP1_B   , RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(APBFSGDPROT_SP1_B, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(APBFSGDSPID_SP2_B   , RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(APBFSGDPROT_SP2_B, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(APBFSGDSPID_SP2_B   , 0); // unmodified
          SWT_EvalEqX(APBFSGDPROT_SP2_B, 0); // unmodified
        #endif
          SWT_EvalEqX(APBFSGDSPID_SP4_B, 0);   /* unmodified !!!! */
          SWT_EvalEqX(APBFSGDPROT_SP4_B, 0);   /* unmodified !!!! */
          SWT_EvalEqX(FSGD1ASPID01, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK));                                                /* allow ICUM to PE1/PE2registers (default init value) */
          SWT_EvalEqX(FSGD1APROT01, (0x0601FE17u | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));   /* allow ICUM to PE1/PE2registers (default init value) */
          SWT_EvalEqX(FSGD1ASPID03, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD1APROT03, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD1ASPID05, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD1APROT05, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(FSGD1ASPID07, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD1APROT07, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD1ASPID07, 0); // unmodified
          SWT_EvalEqX(FSGD1APROT07, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD1BSPID01, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD1BPROT01, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp3 == RBFS_SysGuardPresenceGrp3_YES)
          SWT_EvalEqX(FSGD1BSPID03, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD1BPROT03, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD1BSPID03, 0); // unmodified
          SWT_EvalEqX(FSGD1BPROT03, 0); // unmodified
        #endif
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD1BSPID07, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD1BPROT07, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD1BSPID07, 0); // unmodified
          SWT_EvalEqX(FSGD1BPROT07, 0); // unmodified
        #endif
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(FSGD1BSPID09, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD1BPROT09, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));   // currently we do not use D4_BGA-156 - if we do this in the future a "runtime if" is needed here!
        #else
          SWT_EvalEqX(FSGD1BSPID09, 0); // unmodified
          SWT_EvalEqX(FSGD1BPROT09, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD1BSPID11, RBSYS_SPID_SAFE_MASK);    // restrict writes to safe applications (DMA)
          SWT_EvalEqX(FSGD1BPROT11, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD1BSPID13, RBSYS_SPID_SAFE_MASK);    // restrict writes to safe applications (DMA)
          SWT_EvalEqX(FSGD1BPROT13, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD1BSPID13, 0); // unmodified
          SWT_EvalEqX(FSGD1BPROT13, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD2ASPID01, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK));                                                /* allow ICUM to PE1/PE2registers (default init value) */
          SWT_EvalEqX(FSGD2APROT01, (0x0601FE17u | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));   /* allow ICUM to PE1/PE2registers (default init value) */
          SWT_EvalEqX(FSGD2ASPID03, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD2APROT03, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD2ASPID05, RBSYS_SPID_SAFE_MASK);    // restrict writes to safe applications (DMA)
          SWT_EvalEqX(FSGD2APROT05, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD2ASPID07, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD2APROT07, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(FSGD2ASPID09, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD2APROT09, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD2ASPID09, 0); // unmodified
          SWT_EvalEqX(FSGD2APROT09, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD2ASPID11, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD2APROT11, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(FSGD2ASPID13, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD2APROT13, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD2ASPID13, 0); // unmodified
          SWT_EvalEqX(FSGD2APROT13, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD3ASPID01, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3APROT01, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD3ASPID03, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3APROT03, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD3ASPID05, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3APROT05, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD3ASPID07, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3APROT07, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD3ASPID09, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3APROT09, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD3ASPID11, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3APROT11, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD3ASPID11, 0); // unmodified
          SWT_EvalEqX(FSGD3APROT11, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD3ASPID13, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3APROT13, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD3ASPID15, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3APROT15, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD3ASPID15, 0); // unmodified
          SWT_EvalEqX(FSGD3APROT15, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD3BSPID01, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3BPROT01, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD3BSPID03, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3BPROT03, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD3BSPID07, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3BPROT07, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD3BSPID03, 0); // unmodified
          SWT_EvalEqX(FSGD3BPROT03, 0); // unmodified
          SWT_EvalEqX(FSGD3BSPID07, 0); // unmodified
          SWT_EvalEqX(FSGD3BPROT07, 0); // unmodified
        #endif
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(FSGD3BSPID09, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD3BPROT09, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));   // currently we do not use D4_BGA-156 - if we do this in the future a "runtime if" is needed here!
        #else
          SWT_EvalEqX(FSGD3BSPID09, 0); // unmodified
          SWT_EvalEqX(FSGD3BPROT09, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD3BSPID11, RBSYS_SPID_SAFE_MASK);    // restrict writes to safe applications (DMA)
          SWT_EvalEqX(FSGD3BPROT11, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD3BSPID13, RBSYS_SPID_SAFE_MASK);    // restrict writes to safe applications (DMA)
          SWT_EvalEqX(FSGD3BPROT13, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4ASPID01, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK));                                                /* allow ICUM to PE1/PE2registers (default init value) */
          SWT_EvalEqX(FSGD4APROT01, (0x0601FE17u | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));   /* allow ICUM to PE1/PE2registers (default init value) */
          SWT_EvalEqX(FSGD4ASPID03, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4APROT03, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4ASPID05, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4APROT05, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4ASPID07, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4APROT07, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD4ASPID09, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4APROT09, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD4ASPID09, 0); // unmodified
          SWT_EvalEqX(FSGD4APROT09, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD4ASPID11, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4APROT11, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4ASPID13, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4APROT13, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4ASPID15, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4APROT15, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4BSPID01, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4BPROT01, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4BSPID03, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4BPROT03, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD4BSPID05, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4BPROT05, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD4BSPID05, 0); // unmodified
          SWT_EvalEqX(FSGD4BPROT05, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD4BSPID07, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4BPROT07, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4BSPID09, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4BPROT09, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4BSPID11, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4BPROT11, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4BSPID13, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK));
          SWT_EvalEqX(FSGD4BPROT13, (0x0601FE17u | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));   /* allow ICUM to PE1/PE2registers (default init value) */
          SWT_EvalEqX(FSGD4CSPID01, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT01, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CSPID03, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT03, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CSPID05, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT05, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CSPID07, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT07, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CSPID09, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT09, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CSPID11, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT11, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CSPID13, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT13, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD5ASPID01, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK));                                                /* allow ICUM to PE1/PE2 registers (default init value) */
          SWT_EvalEqX(FSGD5APROT01, (0x0601FE17u | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));   /* allow ICUM to PE1/PE2 registers (default init value) */
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD5ASPID03, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK));                                                /* allow ICUM to PE1/PE2 registers */
          SWT_EvalEqX(FSGD5APROT03, (0x0601FE17u | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));   /* allow ICUM to PE1/PE2 registers (init value modified) */
        #else
          SWT_EvalEqX(FSGD5ASPID03, 0); // unmodified
          SWT_EvalEqX(FSGD5APROT03, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD5ASPID05, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK));                                                /* allow ICUM to PE1/PE2 registers */
          SWT_EvalEqX(FSGD5APROT05, (0x0601FE17u | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));   /* allow ICUM to PE1/PE2 registers (init value modified) */
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD5BSPID01, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK));                                                /* allow ICUM to PE1/PE2 registers */
          SWT_EvalEqX(FSGD5BPROT01, (0x0601FE17u | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));   /* allow ICUM to PE1/PE2 registers (default init value) */
          SWT_EvalEqX(FSGD5BSPID03, (RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK));                                                /* allow ICUM to PE1/PE2 registers */
          SWT_EvalEqX(FSGD5BPROT03, (0x0601FE17u | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));   /* allow ICUM to PE1/PE2 registers (init value modified) */
        #else
          SWT_EvalEqX(FSGD5BSPID01, 0); // unmodified
          SWT_EvalEqX(FSGD5BPROT01, 0); // unmodified
          SWT_EvalEqX(FSGD5BSPID03, 0); // unmodified
          SWT_EvalEqX(FSGD5BPROT03, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD5CSPID01, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD5CPROT01, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD5DSPID01, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD5DPROT01, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD5DSPID03, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD5DPROT03, 0); // unmodified  as ICUMC stuff is not set

        /* ********************************************************* */
        /* read access guards - in general: allow read for everybody */
        /* ********************************************************* */
          SWT_EvalEqX(APBFSGDSPID_PDMACM_A, 0xFFFFFFFF);
          SWT_EvalEqX(APBFSGDPROT_PDMACM_A, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(APBFSGDSPID_PDMACH_A, 0xFFFFFFFF);
          SWT_EvalEqX(APBFSGDPROT_PDMACH_A, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(APBFSGDSPID_INTC2_A, 0xFFFFFFFF);
          SWT_EvalEqX(APBFSGDPROT_INTC2_A, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(APBFSGDSPID_PBG_A, 0xFFFFFFFF);
          SWT_EvalEqX(APBFSGDPROT_PBG_A, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(APBFSGDSPID_SP1_A, 0xFFFFFFFF);
          SWT_EvalEqX(APBFSGDPROT_SP1_A, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(APBFSGDSPID_SP2_A, 0xFFFFFFFF);
          SWT_EvalEqX(APBFSGDPROT_SP2_A, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(APBFSGDSPID_SP2_A, 0); // unmodified
          SWT_EvalEqX(APBFSGDPROT_SP2_A, 0); // unmodified
        #endif
          SWT_EvalEqX(APBFSGDSPID_SP4_A, 0xFFFFFFFF);
          SWT_EvalEqX(APBFSGDPROT_SP4_A, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD1ASPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD1APROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD1ASPID02, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD1APROT02, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD1ASPID04, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD1APROT04, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(FSGD1ASPID06, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD1APROT06, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD1ASPID06, 0); // unmodified
          SWT_EvalEqX(FSGD1APROT06, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD1BSPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD1BPROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp3 == RBFS_SysGuardPresenceGrp3_YES)
          SWT_EvalEqX(FSGD1BSPID02, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD1BPROT02, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD1BSPID02, 0); // unmodified
          SWT_EvalEqX(FSGD1BPROT02, 0); // unmodified
        #endif
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD1BSPID06, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD1BPROT06, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD1BSPID06, 0); // unmodified
          SWT_EvalEqX(FSGD1BPROT06, 0); // unmodified
        #endif
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(FSGD1BSPID08, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD1BPROT08, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));   // currently we do not use D4_BGA-156 - if we do this in the future a "runtime if" is needed here!
        #else
          SWT_EvalEqX(FSGD1BSPID08, 0); // unmodified
          SWT_EvalEqX(FSGD1BPROT08, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD1BSPID10, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD1BPROT10, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD1BSPID12, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD1BPROT12, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD1BSPID12, 0); // unmodified
          SWT_EvalEqX(FSGD1BPROT12, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD2ASPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD2APROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD2ASPID02, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD2APROT02, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD2ASPID04, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD2APROT04, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD2ASPID06, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD2APROT06, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(FSGD2ASPID08, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD2APROT08, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD2ASPID08, 0); // unmodified
          SWT_EvalEqX(FSGD2APROT08, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD2ASPID10, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD2APROT10, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(FSGD2ASPID12, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD2APROT12, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD2ASPID12, 0); // unmodified
          SWT_EvalEqX(FSGD2APROT12, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD3ASPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3APROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD3ASPID02, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3APROT02, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD3ASPID04, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3APROT04, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD3ASPID06, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3APROT06, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD3ASPID08, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3APROT08, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD3ASPID10, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3APROT10, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD3ASPID10, 0); // unmodified
          SWT_EvalEqX(FSGD3APROT10, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD3ASPID12, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3APROT12, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD3ASPID14, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3APROT14, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD3ASPID14, 0); // unmodified
          SWT_EvalEqX(FSGD3APROT14, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD3BSPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3BPROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD3BSPID02, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3BPROT02, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD3BSPID06, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3BPROT06, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD3BSPID02, 0); // unmodified
          SWT_EvalEqX(FSGD3BPROT02, 0); // unmodified
          SWT_EvalEqX(FSGD3BSPID06, 0); // unmodified
          SWT_EvalEqX(FSGD3BPROT06, 0); // unmodified
        #endif
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(FSGD3BSPID08, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3BPROT08, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));   // currently we do not use D4_BGA-156 - if we do this in the future a "runtime if" is needed here!
        #else
          SWT_EvalEqX(FSGD3BSPID08, 0); // unmodified
          SWT_EvalEqX(FSGD3BPROT08, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD3BSPID10, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3BPROT10, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD3BSPID12, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD3BPROT12, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4ASPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4APROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4ASPID02, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4APROT02, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4ASPID04, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4APROT04, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4ASPID10, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4APROT10, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4ASPID12, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4APROT12, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4ASPID14, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4APROT14, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4BSPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4BPROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4BSPID02, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4BPROT02, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD4BSPID04, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4BPROT04, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD4BSPID04, 0); // unmodified
          SWT_EvalEqX(FSGD4BPROT04, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD4BSPID06, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4BPROT06, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4BSPID08, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4BPROT08, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4BSPID10, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4BPROT10, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4BSPID12, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD4BPROT12, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD4CSPID00, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT00, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CSPID02, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT02, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CSPID04, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT04, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CSPID06, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT06, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CSPID08, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT08, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CSPID10, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT10, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CSPID12, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD4CPROT12, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD5ASPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD5APROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD5ASPID02, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD5APROT02, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD5ASPID02, 0); // unmodified
          SWT_EvalEqX(FSGD5APROT02, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD5ASPID04, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD5APROT04, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD5BSPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD5BPROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGD5BSPID02, 0xFFFFFFFF);
          SWT_EvalEqX(FSGD5BPROT02, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD5BSPID00, 0); // unmodified
          SWT_EvalEqX(FSGD5BPROT00, 0); // unmodified
          SWT_EvalEqX(FSGD5BSPID02, 0); // unmodified
          SWT_EvalEqX(FSGD5BPROT02, 0); // unmodified
        #endif
          SWT_EvalEqX(FSGD5CSPID00, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD5CPROT00, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD5DSPID00, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD5DPROT00, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD5DSPID02, 0); // unmodified  as ICUMC stuff is not set
          SWT_EvalEqX(FSGD5DPROT02, 0); // unmodified  as ICUMC stuff is not set

          /* ********************************************************************* */
          /*                  H-Bus guards                                         */
          /* ********************************************************************* */
          /* write */
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGDE0SPID01, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGDE0PROT01, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDF0SPID01, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGDF0PROT01, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGDE0SPID01, 0); // unmodified
          SWT_EvalEqX(FSGDE0PROT01, 0); // unmodified
          SWT_EvalEqX(FSGDF0SPID01, 0); // unmodified
          SWT_EvalEqX(FSGDF0PROT01, 0); // unmodified
        #endif
        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(FSGDE1SPID01, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGDE1PROT01, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDF1SPID01, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGDF1PROT01, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDM0SPID01, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGDM0PROT01, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDM0SPID03, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGDM0PROT03, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDM0SPID05, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGDM0PROT05, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDM0SPID07, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGDM0PROT07, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDM0SPID09, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGDM0PROT09, (0x0601FE17u | RBSYS_PEID_SAFE | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGDE1SPID01, 0); // unmodified
          SWT_EvalEqX(FSGDE1PROT01, 0); // unmodified
          SWT_EvalEqX(FSGDF1SPID01, 0); // unmodified
          SWT_EvalEqX(FSGDF1PROT01, 0); // unmodified
          SWT_EvalEqX(FSGDM0SPID01, 0); // unmodified
          SWT_EvalEqX(FSGDM0PROT01, 0); // unmodified
          SWT_EvalEqX(FSGDM0SPID03, 0); // unmodified
          SWT_EvalEqX(FSGDM0PROT03, 0); // unmodified
          SWT_EvalEqX(FSGDM0SPID05, 0); // unmodified
          SWT_EvalEqX(FSGDM0PROT05, 0); // unmodified
          SWT_EvalEqX(FSGDM0SPID07, 0); // unmodified
          SWT_EvalEqX(FSGDM0PROT07, 0); // unmodified
          SWT_EvalEqX(FSGDM0SPID09, 0); // unmodified
          SWT_EvalEqX(FSGDM0PROT09, 0); // unmodified
        #endif


          /* read */
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGDE0SPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGDE0PROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDF0SPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGDF0PROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGDE0SPID00, 0); // unmodified
          SWT_EvalEqX(FSGDE0PROT00, 0); // unmodified
          SWT_EvalEqX(FSGDF0SPID00, 0); // unmodified
          SWT_EvalEqX(FSGDF0PROT00, 0); // unmodified
        #endif

        #if (RBFS_SysGuardPresenceGrp2 == RBFS_SysGuardPresenceGrp2_YES)
          SWT_EvalEqX(FSGDE1SPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGDE1PROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDF1SPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGDF1PROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDM0SPID00, 0xFFFFFFFF);
          SWT_EvalEqX(FSGDM0PROT00, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDM0SPID02, 0xFFFFFFFF);
          SWT_EvalEqX(FSGDM0PROT02, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDM0SPID04, 0xFFFFFFFF);
          SWT_EvalEqX(FSGDM0PROT04, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDM0SPID06, 0xFFFFFFFF);
          SWT_EvalEqX(FSGDM0PROT06, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
          SWT_EvalEqX(FSGDM0SPID08, 0xFFFFFFFF);
          SWT_EvalEqX(FSGDM0PROT08, (0x0601FE1Bu | RBSYS_PEID_SECURE | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGDE1SPID00, 0); // unmodified
          SWT_EvalEqX(FSGDE1PROT00, 0); // unmodified
          SWT_EvalEqX(FSGDF1SPID00, 0); // unmodified
          SWT_EvalEqX(FSGDF1PROT00, 0); // unmodified
          SWT_EvalEqX(FSGDM0SPID00, 0); // unmodified
          SWT_EvalEqX(FSGDM0PROT00, 0); // unmodified
          SWT_EvalEqX(FSGDM0SPID02, 0); // unmodified
          SWT_EvalEqX(FSGDM0PROT02, 0); // unmodified
          SWT_EvalEqX(FSGDM0SPID04, 0); // unmodified
          SWT_EvalEqX(FSGDM0PROT04, 0); // unmodified
          SWT_EvalEqX(FSGDM0SPID06, 0); // unmodified
          SWT_EvalEqX(FSGDM0PROT06, 0); // unmodified
          SWT_EvalEqX(FSGDM0SPID08, 0); // unmodified
          SWT_EvalEqX(FSGDM0PROT08, 0); // unmodified
        #endif



        /* ********************************************************************* */
        /* read access guards for clear-by-read registers - no ICUM read allowed */
        /* ********************************************************************* */
          SWT_EvalEqX(FSGD4ASPID06, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4APROT06, (0x0601FE1Bu | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #if (RBFS_SysGuardPresenceGrp1 == RBFS_SysGuardPresenceGrp1_YES)
          SWT_EvalEqX(FSGD4ASPID08, RBSYS_SPID_SAFE_MASK);
          SWT_EvalEqX(FSGD4APROT08, (0x0601FE1Bu | RBSYS_PEID_SAFE | RBSYS_PEID_PEID4 | RBSYS_GUARDPROTREGISTER_LOCK));
        #else
          SWT_EvalEqX(FSGD4ASPID08, 0); // unmodified
          SWT_EvalEqX(FSGD4APROT08, 0); // unmodified
        #endif


        /* ***************************************************************************** */
        /*   Call Verify function explicitly                                             */
        /* ***************************************************************************** */

        RBSYS_BasicGuardInit();
        RBSYS_SetBusMasterIDs();
        RBSYS_GRAMGuardInit();
        RBSYS_EnhancedGuardInit();
        RBSYS_PRC_FSW_FinalGuard_Init();

        /* call also the overall check process */
        RBSYS_PRC_FSW_VerifyFinalGuardSettings();
        SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
        SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
        SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);

        /* Manipulate the expected value of a Pre-List value (use register present on all device types) */
        FSGD4BSPID11 = (RBSYS_SPID_SAFE_MASK | 0x77000000);

        /* call also the overall check process */
        RBSYS_PRC_FSW_VerifyFinalGuardSettings();
        SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
        SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_GuardConfigurationFailed);
        SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (1<<2) /* PBG Config Invalid */);

        FSGD4BSPID11 = RBSYS_SPID_SAFE_MASK;    // Reset the manipulated value
        DemStub_EnvReset(); // Reset DemStub

        /* Manipulate the expected value of a Post-List value (use register present on all device types) */
        FSGD4ASPID11 = (RBSYS_SPID_SAFE_MASK | 0x77000000);
        /* call also the overall check process */
        RBSYS_PRC_FSW_VerifyFinalGuardSettings();
        SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
        SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_GuardConfigurationFailed);
        SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (1<<2) /* PBG Config Invalid */);

        DemStub_EnvReset(); // Reset DemStub

        /* Leave the expected value of a Post-List value manipulated and manipulate the expected value of a Pre-List value again */
        FSGD4BSPID11 = (RBSYS_SPID_SAFE_MASK | 0x77000000);

        /* call also the overall check process */
        RBSYS_PRC_FSW_VerifyFinalGuardSettings();
        SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
        SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_GuardConfigurationFailed);
        SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (1<<2) /* PBG Config Invalid */);

        /* Check that no failure entry is done on core1 */
        TRBSYS_setCoreID(1);

        DemStub_EnvReset(); // Reset DemStub

        /* call also the overall check process and see that no failure is entered on core 1 */
        RBSYS_PRC_FSW_VerifyFinalGuardSettings();

        SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
        SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
        SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);


        TRBSYS_setCoreID(0);
        FSGD4BSPID11 = RBSYS_SPID_SAFE_MASK;    // Reset the manipulated value
        FSGD4ASPID11 = RBSYS_SPID_SAFE_MASK;    // Reset the manipulated value


        /* re-init registers */
        PEGG0BA = 0;
        PEGG1BA = 0;
        PEGG2BA = 0;
        PEGG3BA = 0;
        PEGG4BA = 0;
        PEGG5BA = 0;
        PEGG6BA = 0;
        PEGG7BA = 0;
        MGDGRPROT0 = 0x00u;
        MGDGRPROT1 = 0x00u;
        MGDGRPROT2 = 0x00u;
        MGDGRPROT3 = 0x00u;
        MGDGRPROT4 = 0x00u;
        MGDGRPROT5 = 0x00u;
        MGDGRPROT6 = 0x00u;
        MGDGRPROT7 = 0x00u;

        APBFSGDPROT_PDMACM_A = 0;
        APBFSGDPROT_PDMACM_B = 0;
        APBFSGDPROT_PDMACH_A = 0;
        APBFSGDPROT_PDMACH_B = 0;
        APBFSGDPROT_INTC2_A = 0;
        APBFSGDPROT_INTC2_B = 0;
        APBFSGDPROT_PBG_A = 0;
        APBFSGDPROT_PBG_B = 0;
        APBFSGDPROT_SP1_A = 0;
        APBFSGDPROT_SP1_B = 0;
        APBFSGDPROT_SP2_A = 0;
        APBFSGDPROT_SP2_B = 0;
        APBFSGDPROT_SP4_A = 0;
        APBFSGDPROT_SP4_B = 0;
        FSGD1APROT00 = 0;
        FSGD1APROT01 = 0;
        FSGD1APROT02 = 0;
        FSGD1APROT03 = 0;
        FSGD1APROT04 = 0;
        FSGD1APROT05 = 0;
        FSGD1APROT06 = 0;
        FSGD1APROT07 = 0;
        FSGD1BPROT00 = 0;
        FSGD1BPROT01 = 0;
        FSGD1BPROT02 = 0;
        FSGD1BPROT03 = 0;
        FSGD1BPROT06 = 0;
        FSGD1BPROT07 = 0;
        FSGD1BPROT08 = 0;
        FSGD1BPROT09 = 0;
        FSGD1BPROT10 = 0;
        FSGD1BPROT11 = 0;
        FSGD1BPROT12 = 0;
        FSGD1BPROT13 = 0;
        FSGD2APROT00 = 0;
        FSGD2APROT01 = 0;
        FSGD2APROT02 = 0;
        FSGD2APROT03 = 0;
        FSGD2APROT04 = 0;
        FSGD2APROT05 = 0;
        FSGD2APROT06 = 0;
        FSGD2APROT07 = 0;
        FSGD2APROT08 = 0;
        FSGD2APROT09 = 0;
        FSGD2APROT10 = 0;
        FSGD2APROT11 = 0;
        FSGD2APROT12 = 0;
        FSGD2APROT13 = 0;
        FSGD3APROT00 = 0;
        FSGD3APROT01 = 0;
        FSGD3APROT02 = 0;
        FSGD3APROT03 = 0;
        FSGD3APROT04 = 0;
        FSGD3APROT05 = 0;
        FSGD3APROT06 = 0;
        FSGD3APROT07 = 0;
        FSGD3APROT08 = 0;
        FSGD3APROT09 = 0;
        FSGD3APROT10 = 0;
        FSGD3APROT11 = 0;
        FSGD3APROT12 = 0;
        FSGD3APROT13 = 0;
        FSGD3APROT14 = 0;
        FSGD3APROT15 = 0;
        FSGD3BPROT00 = 0;
        FSGD3BPROT01 = 0;
        FSGD3BPROT02 = 0;
        FSGD3BPROT03 = 0;
        FSGD3BPROT06 = 0;
        FSGD3BPROT07 = 0;
        FSGD3BPROT08 = 0;
        FSGD3BPROT09 = 0;
        FSGD3BPROT10 = 0;
        FSGD3BPROT11 = 0;
        FSGD3BPROT12 = 0;
        FSGD3BPROT13 = 0;
        FSGD4APROT00 = 0;
        FSGD4APROT01 = 0;
        FSGD4APROT02 = 0;
        FSGD4APROT03 = 0;
        FSGD4APROT04 = 0;
        FSGD4APROT05 = 0;
        FSGD4APROT06 = 0;
        FSGD4APROT07 = 0;
        FSGD4APROT08 = 0;
        FSGD4APROT09 = 0;
        FSGD4APROT10 = 0;
        FSGD4APROT11 = 0;
        FSGD4APROT12 = 0;
        FSGD4APROT13 = 0;
        FSGD4APROT14 = 0;
        FSGD4APROT15 = 0;
        FSGD4BPROT00 = 0;
        FSGD4BPROT01 = 0;
        FSGD4BPROT02 = 0;
        FSGD4BPROT03 = 0;
        FSGD4BPROT04 = 0;
        FSGD4BPROT05 = 0;
        FSGD4BPROT06 = 0;
        FSGD4BPROT07 = 0;
        FSGD4BPROT08 = 0;
        FSGD4BPROT09 = 0;
        FSGD4BPROT10 = 0;
        FSGD4BPROT11 = 0;
        FSGD4BPROT12 = 0;
        FSGD4BPROT13 = 0;
        FSGD4CPROT00 = 0;
        FSGD4CPROT01 = 0;
        FSGD4CPROT02 = 0;
        FSGD4CPROT03 = 0;
        FSGD4CPROT04 = 0;
        FSGD4CPROT05 = 0;
        FSGD4CPROT06 = 0;
        FSGD4CPROT07 = 0;
        FSGD4CPROT08 = 0;
        FSGD4CPROT09 = 0;
        FSGD4CPROT10 = 0;
        FSGD4CPROT11 = 0;
        FSGD4CPROT12 = 0;
        FSGD4CPROT13 = 0;
        FSGD5APROT00 = 0;
        FSGD5APROT01 = 0;
        FSGD5APROT02 = 0;
        FSGD5APROT03 = 0;
        FSGD5APROT04 = 0;
        FSGD5APROT05 = 0;
        FSGD5BPROT00 = 0;
        FSGD5BPROT01 = 0;
        FSGD5BPROT02 = 0;
        FSGD5BPROT03 = 0;
        FSGD5CPROT00 = 0;
        FSGD5CPROT01 = 0;
        FSGD5DPROT00 = 0;
        FSGD5DPROT01 = 0;
        FSGD5DPROT02 = 0;
        FSGD5DPROT03 = 0;

        APBFSGDSPID_PDMACM_A = 0;
        APBFSGDSPID_PDMACM_B = 0;
        APBFSGDSPID_PDMACH_A = 0;
        APBFSGDSPID_PDMACH_B = 0;
        APBFSGDSPID_INTC2_A = 0;
        APBFSGDSPID_INTC2_B = 0;
        APBFSGDSPID_PBG_A = 0;
        APBFSGDSPID_PBG_B = 0;
        APBFSGDSPID_SP1_A = 0;
        APBFSGDSPID_SP1_B = 0;
        APBFSGDSPID_SP2_A = 0;
        APBFSGDSPID_SP2_B = 0;
        APBFSGDSPID_SP4_A = 0;
        APBFSGDSPID_SP4_B = 0;
        FSGD1ASPID00 = 0;
        FSGD1ASPID01 = 0;
        FSGD1ASPID02 = 0;
        FSGD1ASPID03 = 0;
        FSGD1ASPID04 = 0;
        FSGD1ASPID05 = 0;
        FSGD1ASPID06 = 0;
        FSGD1ASPID07 = 0;
        FSGD1BSPID00 = 0;
        FSGD1BSPID01 = 0;
        FSGD1BSPID02 = 0;
        FSGD1BSPID03 = 0;
        FSGD1BSPID06 = 0;
        FSGD1BSPID07 = 0;
        FSGD1BSPID08 = 0;
        FSGD1BSPID09 = 0;
        FSGD1BSPID10 = 0;
        FSGD1BSPID11 = 0;
        FSGD1BSPID12 = 0;
        FSGD1BSPID13 = 0;
        FSGD2ASPID00 = 0;
        FSGD2ASPID01 = 0;
        FSGD2ASPID02 = 0;
        FSGD2ASPID03 = 0;
        FSGD2ASPID04 = 0;
        FSGD2ASPID05 = 0;
        FSGD2ASPID06 = 0;
        FSGD2ASPID07 = 0;
        FSGD2ASPID08 = 0;
        FSGD2ASPID09 = 0;
        FSGD2ASPID10 = 0;
        FSGD2ASPID11 = 0;
        FSGD2ASPID12 = 0;
        FSGD2ASPID13 = 0;
        FSGD3ASPID00 = 0;
        FSGD3ASPID01 = 0;
        FSGD3ASPID02 = 0;
        FSGD3ASPID03 = 0;
        FSGD3ASPID04 = 0;
        FSGD3ASPID05 = 0;
        FSGD3ASPID06 = 0;
        FSGD3ASPID07 = 0;
        FSGD3ASPID08 = 0;
        FSGD3ASPID09 = 0;
        FSGD3ASPID10 = 0;
        FSGD3ASPID11 = 0;
        FSGD3ASPID12 = 0;
        FSGD3ASPID13 = 0;
        FSGD3ASPID14 = 0;
        FSGD3ASPID15 = 0;
        FSGD3BSPID00 = 0;
        FSGD3BSPID01 = 0;
        FSGD3BSPID02 = 0;
        FSGD3BSPID03 = 0;
        FSGD3BSPID06 = 0;
        FSGD3BSPID07 = 0;
        FSGD3BSPID08 = 0;
        FSGD3BSPID09 = 0;
        FSGD3BSPID10 = 0;
        FSGD3BSPID11 = 0;
        FSGD3BSPID12 = 0;
        FSGD3BSPID13 = 0;
        FSGD4ASPID00 = 0;
        FSGD4ASPID01 = 0;
        FSGD4ASPID02 = 0;
        FSGD4ASPID03 = 0;
        FSGD4ASPID04 = 0;
        FSGD4ASPID05 = 0;
        FSGD4ASPID06 = 0;
        FSGD4ASPID07 = 0;
        FSGD4ASPID08 = 0;
        FSGD4ASPID09 = 0;
        FSGD4ASPID10 = 0;
        FSGD4ASPID11 = 0;
        FSGD4ASPID12 = 0;
        FSGD4ASPID13 = 0;
        FSGD4ASPID14 = 0;
        FSGD4ASPID15 = 0;
        FSGD4BSPID00 = 0;
        FSGD4BSPID01 = 0;
        FSGD4BSPID02 = 0;
        FSGD4BSPID03 = 0;
        FSGD4BSPID04 = 0;
        FSGD4BSPID05 = 0;
        FSGD4BSPID06 = 0;
        FSGD4BSPID07 = 0;
        FSGD4BSPID08 = 0;
        FSGD4BSPID09 = 0;
        FSGD4BSPID10 = 0;
        FSGD4BSPID11 = 0;
        FSGD4BSPID12 = 0;
        FSGD4BSPID13 = 0;
        FSGD4CSPID00 = 0;
        FSGD4CSPID01 = 0;
        FSGD4CSPID02 = 0;
        FSGD4CSPID03 = 0;
        FSGD4CSPID04 = 0;
        FSGD4CSPID05 = 0;
        FSGD4CSPID06 = 0;
        FSGD4CSPID07 = 0;
        FSGD4CSPID08 = 0;
        FSGD4CSPID09 = 0;
        FSGD4CSPID10 = 0;
        FSGD4CSPID11 = 0;
        FSGD4CSPID12 = 0;
        FSGD4CSPID13 = 0;
        FSGD5ASPID00 = 0;
        FSGD5ASPID01 = 0;
        FSGD5ASPID02 = 0;
        FSGD5ASPID03 = 0;
        FSGD5ASPID04 = 0;
        FSGD5ASPID05 = 0;
        FSGD5BSPID00 = 0;
        FSGD5BSPID01 = 0;
        FSGD5BSPID02 = 0;
        FSGD5BSPID03 = 0;
        FSGD5CSPID00 = 0;
        FSGD5CSPID01 = 0;
        FSGD5DSPID00 = 0;
        FSGD5DSPID01 = 0;
        FSGD5DSPID02 = 0;
        FSGD5DSPID03 = 0;



        /* ******************* */
        /* set Core to 1 */
        /* ******************* */
        #if( RBFS_MCORE == RBFS_MCORE_ON )
          TRBSYS_setCoreID(1);

          RBSYS_PRC_FSW_FinalGuard_Init();
          /* RBSYS_PRC_FSW_FinalGuard_Init shall
          *  - deactivate and lock the own Cores unused PEGuards
          *  - Core0 only: Enable Exclusive SPID Sections
          *  - Core0 only: Lock GRAM Guards if necessary by design (U2a only)
          *  - Core0 only: Initialize Remaining PBUS Guards (P1x only)
          */


          /* ************************************************* */
          /* RBSYS_GRAMGuardInit   registers not set on core 1 */
          /* ************************************************* */
          /* no setting/modification of registers */
          SWT_EvalEqX(MGDGRPROT0, 0x00u);
          SWT_EvalEqX(MGDGRPROT1, 0x00u);
          SWT_EvalEqX(MGDGRPROT2, 0x00u);
          SWT_EvalEqX(MGDGRPROT3, 0x00u);
          SWT_EvalEqX(MGDGRPROT4, 0x00u);
          SWT_EvalEqX(MGDGRPROT5, 0x00u);
          SWT_EvalEqX(MGDGRPROT6, 0x00u);
          SWT_EvalEqX(MGDGRPROT7, 0x00u);


          /* ******************************************* */
          /* write access guards - all not set on core 1 */
          /* ******************************************* */

          SWT_EvalEqX(APBFSGDSPID_PDMACM_B, 0);
          SWT_EvalEqX(APBFSGDPROT_PDMACM_B, 0);
          SWT_EvalEqX(APBFSGDSPID_PDMACH_B, 0);
          SWT_EvalEqX(APBFSGDPROT_PDMACH_B, 0);
          SWT_EvalEqX(APBFSGDSPID_INTC2_B, 0);
          SWT_EvalEqX(APBFSGDPROT_INTC2_B, 0);
          SWT_EvalEqX(APBFSGDSPID_PBG_B, 0);
          SWT_EvalEqX(APBFSGDPROT_PBG_B, 0);
          SWT_EvalEqX(APBFSGDSPID_SP1_B, 0);
          SWT_EvalEqX(APBFSGDPROT_SP1_B, 0);
          SWT_EvalEqX(APBFSGDSPID_SP2_B, 0);
          SWT_EvalEqX(APBFSGDPROT_SP2_B, 0);
          SWT_EvalEqX(APBFSGDSPID_SP4_B, 0);
          SWT_EvalEqX(APBFSGDPROT_SP4_B, 0);
          SWT_EvalEqX(FSGD1ASPID01, 0);
          SWT_EvalEqX(FSGD1APROT01, 0);
          SWT_EvalEqX(FSGD1ASPID03, 0);
          SWT_EvalEqX(FSGD1APROT03, 0);
          SWT_EvalEqX(FSGD1ASPID05, 0);
          SWT_EvalEqX(FSGD1APROT05, 0);
          SWT_EvalEqX(FSGD1ASPID07, 0);
          SWT_EvalEqX(FSGD1APROT07, 0);
          SWT_EvalEqX(FSGD1BSPID01, 0);
          SWT_EvalEqX(FSGD1BPROT01, 0);
          SWT_EvalEqX(FSGD1BSPID03, 0);
          SWT_EvalEqX(FSGD1BPROT03, 0);
          SWT_EvalEqX(FSGD1BSPID07, 0);
          SWT_EvalEqX(FSGD1BPROT07, 0);
          SWT_EvalEqX(FSGD1BSPID09, 0);
          SWT_EvalEqX(FSGD1BPROT09, 0);
          SWT_EvalEqX(FSGD1BSPID11, 0);
          SWT_EvalEqX(FSGD1BPROT11, 0);
          SWT_EvalEqX(FSGD1BSPID13, 0);
          SWT_EvalEqX(FSGD1BPROT13, 0);
          SWT_EvalEqX(FSGD2ASPID01, 0);
          SWT_EvalEqX(FSGD2APROT01, 0);
          SWT_EvalEqX(FSGD2ASPID03, 0);
          SWT_EvalEqX(FSGD2APROT03, 0);
          SWT_EvalEqX(FSGD2ASPID05, 0);
          SWT_EvalEqX(FSGD2APROT05, 0);
          SWT_EvalEqX(FSGD2ASPID07, 0);
          SWT_EvalEqX(FSGD2APROT07, 0);
          SWT_EvalEqX(FSGD2ASPID09, 0);
          SWT_EvalEqX(FSGD2APROT09, 0);
          SWT_EvalEqX(FSGD2ASPID11, 0);
          SWT_EvalEqX(FSGD2APROT11, 0);
          SWT_EvalEqX(FSGD2ASPID13, 0);
          SWT_EvalEqX(FSGD2APROT13, 0);
          SWT_EvalEqX(FSGD3ASPID01, 0);
          SWT_EvalEqX(FSGD3APROT01, 0);
          SWT_EvalEqX(FSGD3ASPID03, 0);
          SWT_EvalEqX(FSGD3APROT03, 0);
          SWT_EvalEqX(FSGD3ASPID05, 0);
          SWT_EvalEqX(FSGD3APROT05, 0);
          SWT_EvalEqX(FSGD3ASPID07, 0);
          SWT_EvalEqX(FSGD3APROT07, 0);
          SWT_EvalEqX(FSGD3ASPID09, 0);
          SWT_EvalEqX(FSGD3APROT09, 0);
          SWT_EvalEqX(FSGD3ASPID11, 0);
          SWT_EvalEqX(FSGD3APROT11, 0);
          SWT_EvalEqX(FSGD3ASPID13, 0);
          SWT_EvalEqX(FSGD3APROT13, 0);
          SWT_EvalEqX(FSGD3ASPID15, 0);
          SWT_EvalEqX(FSGD3APROT15, 0);
          SWT_EvalEqX(FSGD3BSPID01, 0);
          SWT_EvalEqX(FSGD3BPROT01, 0);
          SWT_EvalEqX(FSGD3BSPID03, 0);
          SWT_EvalEqX(FSGD3BPROT03, 0);
          SWT_EvalEqX(FSGD3BSPID07, 0);
          SWT_EvalEqX(FSGD3BPROT07, 0);
          SWT_EvalEqX(FSGD3BSPID09, 0);
          SWT_EvalEqX(FSGD3BPROT09, 0);
          SWT_EvalEqX(FSGD3BSPID11, 0);
          SWT_EvalEqX(FSGD3BPROT11, 0);
          SWT_EvalEqX(FSGD3BSPID13, 0);
          SWT_EvalEqX(FSGD3BPROT13, 0);
          SWT_EvalEqX(FSGD4ASPID01, 0);
          SWT_EvalEqX(FSGD4APROT01, 0);
          SWT_EvalEqX(FSGD4ASPID03, 0);
          SWT_EvalEqX(FSGD4APROT03, 0);
          SWT_EvalEqX(FSGD4ASPID05, 0);
          SWT_EvalEqX(FSGD4APROT05, 0);
          SWT_EvalEqX(FSGD4ASPID07, 0);
          SWT_EvalEqX(FSGD4APROT07, 0);
          SWT_EvalEqX(FSGD4ASPID09, 0);
          SWT_EvalEqX(FSGD4APROT09, 0);
          SWT_EvalEqX(FSGD4ASPID11, 0);
          SWT_EvalEqX(FSGD4APROT11, 0);
          SWT_EvalEqX(FSGD4ASPID13, 0);
          SWT_EvalEqX(FSGD4APROT13, 0);
          SWT_EvalEqX(FSGD4ASPID15, 0);
          SWT_EvalEqX(FSGD4APROT15, 0);
          SWT_EvalEqX(FSGD4BSPID01, 0);
          SWT_EvalEqX(FSGD4BPROT01, 0);
          SWT_EvalEqX(FSGD4BSPID03, 0);
          SWT_EvalEqX(FSGD4BPROT03, 0);
          SWT_EvalEqX(FSGD4BSPID05, 0);
          SWT_EvalEqX(FSGD4BPROT05, 0);
          SWT_EvalEqX(FSGD4BSPID07, 0);
          SWT_EvalEqX(FSGD4BPROT07, 0);
          SWT_EvalEqX(FSGD4BSPID09, 0);
          SWT_EvalEqX(FSGD4BPROT09, 0);
          SWT_EvalEqX(FSGD4BSPID11, 0);
          SWT_EvalEqX(FSGD4BPROT11, 0);
          SWT_EvalEqX(FSGD4BSPID13, 0);
          SWT_EvalEqX(FSGD4BPROT13, 0);
          SWT_EvalEqX(FSGD4CSPID01, 0);
          SWT_EvalEqX(FSGD4CPROT01, 0);
          SWT_EvalEqX(FSGD4CSPID03, 0);
          SWT_EvalEqX(FSGD4CPROT03, 0);
          SWT_EvalEqX(FSGD4CSPID05, 0);
          SWT_EvalEqX(FSGD4CPROT05, 0);
          SWT_EvalEqX(FSGD4CSPID07, 0);
          SWT_EvalEqX(FSGD4CPROT07, 0);
          SWT_EvalEqX(FSGD4CSPID09, 0);
          SWT_EvalEqX(FSGD4CPROT09, 0);
          SWT_EvalEqX(FSGD4CSPID11, 0);
          SWT_EvalEqX(FSGD4CPROT11, 0);
          SWT_EvalEqX(FSGD4CSPID13, 0);
          SWT_EvalEqX(FSGD4CPROT13, 0);
          SWT_EvalEqX(FSGD5ASPID01, 0);
          SWT_EvalEqX(FSGD5APROT01, 0);
          SWT_EvalEqX(FSGD5ASPID03, 0);
          SWT_EvalEqX(FSGD5APROT03, 0);
          SWT_EvalEqX(FSGD5ASPID05, 0);
          SWT_EvalEqX(FSGD5APROT05, 0);
          SWT_EvalEqX(FSGD5BSPID01, 0);
          SWT_EvalEqX(FSGD5BPROT01, 0);
          SWT_EvalEqX(FSGD5BSPID03, 0);
          SWT_EvalEqX(FSGD5BPROT03, 0);
          SWT_EvalEqX(FSGD5CSPID01, 0);
          SWT_EvalEqX(FSGD5CPROT01, 0);
          SWT_EvalEqX(FSGD5DSPID01, 0);
          SWT_EvalEqX(FSGD5DPROT01, 0);
          SWT_EvalEqX(FSGD5DSPID03, 0);
          SWT_EvalEqX(FSGD5DPROT03, 0);

          /* ************************************** */
          /* read access guards - not set on core 1 */
          /* ************************************** */
          SWT_EvalEqX(APBFSGDSPID_PDMACM_A, 0);
          SWT_EvalEqX(APBFSGDPROT_PDMACM_A, 0);
          SWT_EvalEqX(APBFSGDSPID_PDMACH_A, 0);
          SWT_EvalEqX(APBFSGDPROT_PDMACH_A, 0);
          SWT_EvalEqX(APBFSGDSPID_INTC2_A, 0);
          SWT_EvalEqX(APBFSGDPROT_INTC2_A, 0);
          SWT_EvalEqX(APBFSGDSPID_PBG_A, 0);
          SWT_EvalEqX(APBFSGDPROT_PBG_A, 0);
          SWT_EvalEqX(APBFSGDSPID_SP1_A, 0);
          SWT_EvalEqX(APBFSGDPROT_SP1_A, 0);
          SWT_EvalEqX(APBFSGDSPID_SP2_A, 0);
          SWT_EvalEqX(APBFSGDPROT_SP2_A, 0);
          SWT_EvalEqX(APBFSGDSPID_SP4_A, 0);
          SWT_EvalEqX(APBFSGDPROT_SP4_A, 0);
          SWT_EvalEqX(FSGD1ASPID00, 0);
          SWT_EvalEqX(FSGD1APROT00, 0);
          SWT_EvalEqX(FSGD1ASPID02, 0);
          SWT_EvalEqX(FSGD1APROT02, 0);
          SWT_EvalEqX(FSGD1ASPID04, 0);
          SWT_EvalEqX(FSGD1APROT04, 0);
          SWT_EvalEqX(FSGD1ASPID06, 0);
          SWT_EvalEqX(FSGD1APROT06, 0);
          SWT_EvalEqX(FSGD1BSPID00, 0);
          SWT_EvalEqX(FSGD1BPROT00, 0);
          SWT_EvalEqX(FSGD1BSPID02, 0);
          SWT_EvalEqX(FSGD1BPROT02, 0);
          SWT_EvalEqX(FSGD1BSPID06, 0);
          SWT_EvalEqX(FSGD1BPROT06, 0);
          SWT_EvalEqX(FSGD1BSPID08, 0);
          SWT_EvalEqX(FSGD1BPROT08, 0);
          SWT_EvalEqX(FSGD1BSPID10, 0);
          SWT_EvalEqX(FSGD1BPROT10, 0);
          SWT_EvalEqX(FSGD1BSPID12, 0);
          SWT_EvalEqX(FSGD1BPROT12, 0);
          SWT_EvalEqX(FSGD2ASPID00, 0);
          SWT_EvalEqX(FSGD2APROT00, 0);
          SWT_EvalEqX(FSGD2ASPID02, 0);
          SWT_EvalEqX(FSGD2APROT02, 0);
          SWT_EvalEqX(FSGD2ASPID04, 0);
          SWT_EvalEqX(FSGD2APROT04, 0);
          SWT_EvalEqX(FSGD2ASPID06, 0);
          SWT_EvalEqX(FSGD2APROT06, 0);
          SWT_EvalEqX(FSGD2ASPID08, 0);
          SWT_EvalEqX(FSGD2APROT08, 0);
          SWT_EvalEqX(FSGD2ASPID10, 0);
          SWT_EvalEqX(FSGD2APROT10, 0);
          SWT_EvalEqX(FSGD2ASPID12, 0);
          SWT_EvalEqX(FSGD2APROT12, 0);
          SWT_EvalEqX(FSGD3ASPID00, 0);
          SWT_EvalEqX(FSGD3APROT00, 0);
          SWT_EvalEqX(FSGD3ASPID02, 0);
          SWT_EvalEqX(FSGD3APROT02, 0);
          SWT_EvalEqX(FSGD3ASPID04, 0);
          SWT_EvalEqX(FSGD3APROT04, 0);
          SWT_EvalEqX(FSGD3ASPID06, 0);
          SWT_EvalEqX(FSGD3APROT06, 0);
          SWT_EvalEqX(FSGD3ASPID08, 0);
          SWT_EvalEqX(FSGD3APROT08, 0);
          SWT_EvalEqX(FSGD3ASPID10, 0);
          SWT_EvalEqX(FSGD3APROT10, 0);
          SWT_EvalEqX(FSGD3ASPID12, 0);
          SWT_EvalEqX(FSGD3APROT12, 0);
          SWT_EvalEqX(FSGD3ASPID14, 0);
          SWT_EvalEqX(FSGD3APROT14, 0);
          SWT_EvalEqX(FSGD3BSPID00, 0);
          SWT_EvalEqX(FSGD3BPROT00, 0);
          SWT_EvalEqX(FSGD3BSPID02, 0);
          SWT_EvalEqX(FSGD3BPROT02, 0);
          SWT_EvalEqX(FSGD3BSPID06, 0);
          SWT_EvalEqX(FSGD3BPROT06, 0);
          SWT_EvalEqX(FSGD3BSPID08, 0);
          SWT_EvalEqX(FSGD3BPROT08, 0);
          SWT_EvalEqX(FSGD3BSPID10, 0);
          SWT_EvalEqX(FSGD3BPROT10, 0);
          SWT_EvalEqX(FSGD3BSPID12, 0);
          SWT_EvalEqX(FSGD3BPROT12, 0);
          SWT_EvalEqX(FSGD4ASPID00, 0);
          SWT_EvalEqX(FSGD4APROT00, 0);
          SWT_EvalEqX(FSGD4ASPID02, 0);
          SWT_EvalEqX(FSGD4APROT02, 0);
          SWT_EvalEqX(FSGD4ASPID04, 0);
          SWT_EvalEqX(FSGD4APROT04, 0);
          SWT_EvalEqX(FSGD4ASPID10, 0);
          SWT_EvalEqX(FSGD4APROT10, 0);
          SWT_EvalEqX(FSGD4ASPID12, 0);
          SWT_EvalEqX(FSGD4APROT12, 0);
          SWT_EvalEqX(FSGD4ASPID14, 0);
          SWT_EvalEqX(FSGD4APROT14, 0);
          SWT_EvalEqX(FSGD4BSPID00, 0);
          SWT_EvalEqX(FSGD4BPROT00, 0);
          SWT_EvalEqX(FSGD4BSPID02, 0);
          SWT_EvalEqX(FSGD4BPROT02, 0);
          SWT_EvalEqX(FSGD4BSPID04, 0);
          SWT_EvalEqX(FSGD4BPROT04, 0);
          SWT_EvalEqX(FSGD4BSPID06, 0);
          SWT_EvalEqX(FSGD4BPROT06, 0);
          SWT_EvalEqX(FSGD4BSPID08, 0);
          SWT_EvalEqX(FSGD4BPROT08, 0);
          SWT_EvalEqX(FSGD4BSPID10, 0);
          SWT_EvalEqX(FSGD4BPROT10, 0);
          SWT_EvalEqX(FSGD4BSPID12, 0);
          SWT_EvalEqX(FSGD4BPROT12, 0);
          SWT_EvalEqX(FSGD4CSPID00, 0);
          SWT_EvalEqX(FSGD4CPROT00, 0);
          SWT_EvalEqX(FSGD4CSPID02, 0);
          SWT_EvalEqX(FSGD4CPROT02, 0);
          SWT_EvalEqX(FSGD4CSPID04, 0);
          SWT_EvalEqX(FSGD4CPROT04, 0);
          SWT_EvalEqX(FSGD4CSPID06, 0);
          SWT_EvalEqX(FSGD4CPROT06, 0);
          SWT_EvalEqX(FSGD4CSPID08, 0);
          SWT_EvalEqX(FSGD4CPROT08, 0);
          SWT_EvalEqX(FSGD4CSPID10, 0);
          SWT_EvalEqX(FSGD4CPROT10, 0);
          SWT_EvalEqX(FSGD4CSPID12, 0);
          SWT_EvalEqX(FSGD4CPROT12, 0);
          SWT_EvalEqX(FSGD5ASPID00, 0);
          SWT_EvalEqX(FSGD5APROT00, 0);
          SWT_EvalEqX(FSGD5ASPID02, 0);
          SWT_EvalEqX(FSGD5APROT02, 0);
          SWT_EvalEqX(FSGD5ASPID04, 0);
          SWT_EvalEqX(FSGD5APROT04, 0);
          SWT_EvalEqX(FSGD5BSPID00, 0);
          SWT_EvalEqX(FSGD5BPROT00, 0);
          SWT_EvalEqX(FSGD5BSPID02, 0);
          SWT_EvalEqX(FSGD5BPROT02, 0);
          SWT_EvalEqX(FSGD5CSPID00, 0);
          SWT_EvalEqX(FSGD5CPROT00, 0);
          SWT_EvalEqX(FSGD5DSPID00, 0);
          SWT_EvalEqX(FSGD5DPROT00, 0);
          SWT_EvalEqX(FSGD5DSPID02, 0);
          SWT_EvalEqX(FSGD5DPROT02, 0);

          /* ********************************************************************* */
          /* read access guards for clear-by-read registers - not set on core 1    */
          /* ********************************************************************* */
          SWT_EvalEqX(FSGD4ASPID06, 0);
          SWT_EvalEqX(FSGD4APROT06, 0);
          SWT_EvalEqX(FSGD4ASPID08, 0);
          SWT_EvalEqX(FSGD4APROT08, 0);
        #endif //< RBFS_MCORE_ON
      }  // TRBSYS_GuardConfig_008
      #endif   // P1x-family




      #if(RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K)

        /* ********************************************************************************************* */
        /* Test the interface functions for the Restricted SPID feature for GRAM                         */
        /* ********************************************************************************************* */



        #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
          /**
          * \TestCaseName TRBSYS_GuardConfig_009
          *
          * \Reference
          * RBSYS_RestrictedExclusiveGRAM_AllowSafeAccess, RBSYS_RestrictedExclusiveGRAM_BlockSafeAccess, Gen_SWCS_HSW_uC_Base_SYS-306
          *
          * \Purpose Test functionality of RBSYS_RestrictedExclusiveGRAM_AllowSafeAccess and RBSYS_RestrictedExclusiveGRAM_BlockSafeAccess
          *
          * \Sequence
          *  0. Initialize the access to Restricted SPID
          *  1. call the function RBSYS_RestrictedExclusiveGRAM_AllowSafeAccess
          *  2. call the function RBSYS_RestrictedExclusiveGRAM_BlockSafeAccess
          *
          * \ExpectedResult
          * The affected GRAM areas are successfully toggled from RestrictedSPID to SafeSPID and back
          */
          SWTEST void TRBSYS_GuardConfig_009(void)
          {
            /* Init */
            #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K)
              /* uses the 16K section (guard region 2) starting at 0xFEEF8000 */
              MGDGRSPID2 =  RBSYS_SPID_RESTRICTED_MASK;
              MGDGRSPID3 =  RBSYS_SPID_SAFE_MASK;
            #endif
            #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K)
              /* uses the 32K section (guard region 3) starting at 0xFEEF0000 */
              MGDGRSPID2 =  RBSYS_SPID_SAFE_MASK;
              MGDGRSPID3 =  RBSYS_SPID_RESTRICTED_MASK;
            #endif
              /* do not Init MGDGRPROTx to see which is really left 'enabled' due to the function call */

              RBSYS_RestrictedExclusiveGRAM_AllowSafeAccess();

            /* Now both are SafeSPID regardless of what they were before */
            #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K)
              /* uses the 16K section (guard region 2) starting at 0xFEEF8000 */
              SWT_EvalEqX(MGDGRSPID2, RBSYS_SPID_SAFE_MASK);
              SWT_EvalEqX(MGDGRSPID3, RBSYS_SPID_SAFE_MASK);
            #endif
            #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K)
              /* uses the 32K section (guard region 3) starting at 0xFEEF0000 */
              SWT_EvalEqX(MGDGRSPID2, RBSYS_SPID_SAFE_MASK);
              SWT_EvalEqX(MGDGRSPID3, RBSYS_SPID_SAFE_MASK | RBSYS_SPID_RESTRICTED_MASK);
            #endif


            RBSYS_RestrictedExclusiveGRAM_BlockSafeAccess();
            /* Now both are again their expected config for Restricted SPID depending on the area */
            #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K)
              /* uses the 16K section (guard region 2) starting at 0xFEEF8000 */
              SWT_EvalEqX(MGDGRSPID2, RBSYS_SPID_RESTRICTED_MASK);
              SWT_EvalEqX(MGDGRSPID3, RBSYS_SPID_SAFE_MASK);
            #endif
            #if(RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K)
              /* uses the 32K section (guard region 3) starting at 0xFEEF0000 */
              SWT_EvalEqX(MGDGRSPID2, RBSYS_SPID_SAFE_MASK);
              SWT_EvalEqX(MGDGRSPID3, RBSYS_SPID_RESTRICTED_MASK);
            #endif
          }    // TRBSYS_GuardConfig_009
        #endif   // P1x-family

        /**
          * \TestCaseName TRBSYS_GuardConfig_010
          *
          * \Reference
          * RBSYS_setCoreSPID2RestrictedSPID, RBSYS_resetCoreSPID2SafeSPID,Gen_SWCS_HSW_uC_Base_SYS-306
          *
          * \Purpose Test functionality of RBSYS_setCoreSPID2RestrictedSPID and RBSYS_resetCoreSPID2SafeSPID
          *
          * \Sequence
          *  0. Initialize the core to Safe SPID
          *  1. call the function RBSYS_setCoreSPID2RestrictedSPID
          *  2. call the function RBSYS_resetCoreSPID2SafeSPID
          *
          * \ExpectedResult
          * The core will toggle its SPID accordingly
          */
        SWTEST void TRBSYS_GuardConfig_010(void)
        {
          /* Init */
          #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
            TRBSYS_SetSystemRegister(0,1, (2 << 16));  // actually 5 Bits are the SPID, i.e. B'00010
          #endif
          #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
            TRBSYS_SetSystemRegister(0,1, 2);  // actually 5 Bits are the SPID, i.e. B'00010
          #endif
          #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
            TRBSYS_SetSystemRegister(0,1, 0);  // actually 5 Bits are the SPID, i.e. B'00000
          #endif

          RBSYS_setCoreSPID2RestrictedSPID();
          #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
            SWT_EvalEqX(((TRBSYS_GetSystemRegister(0,1) >> 16) & 0x1F), 4);  // actually 5 Bits are the SPID, i.e. B'00100
          #endif
          #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
            SWT_EvalEqX((TRBSYS_GetSystemRegister(0,1) & 0x1F), 4);  // actually 5 Bits are the SPID, i.e. B'00100
          #endif

          RBSYS_resetCoreSPID2SafeSPID();
          #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
            SWT_EvalEqX(((TRBSYS_GetSystemRegister(0,1) >> 16) & 0x1F), 2);  // actually 5 Bits are the SPID, i.e. B'00010
          #endif
          #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
            SWT_EvalEqX((TRBSYS_GetSystemRegister(0,1) & 0x1F), 2);  // actually 5 Bits are the SPID, i.e. B'00010
          #endif
          #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
            SWT_EvalEqX((TRBSYS_GetSystemRegister(0,1) & 0x1F), 0);  // actually 5 Bits are the SPID, i.e. B'00000
          #endif


          /*  *********  Testing of the asserts ******* */

          /* 1. call RBSYS_setCoreSPID2RestrictedSPID when it is already Restricted -> assert */
          /* Init */
          #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
            TRBSYS_SetSystemRegister(0,1, (4 << 16));  // actually 5 Bits are the SPID, i.e. B'00100
          #endif
          #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
            TRBSYS_SetSystemRegister(0,1, 4);  // actually 5 Bits are the SPID, i.e. B'00100
          #endif

          SWT_AssertCheckStart("RBSYS_setCoreSPID2RestrictedSPID", "RBSYS_getCoreSPID() == SafeSPID");
          RBSYS_setCoreSPID2RestrictedSPID();
          SWT_AssertCheckEnd();


          /* 2. call RBSYS_resetCoreSPID2SafeSPID when it is already Safe -> assert */
            /* Init */
          #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
            TRBSYS_SetSystemRegister(0,1, (2 << 16));  // actually 5 Bits are the SPID, i.e. B'00010
          #endif
          #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
            TRBSYS_SetSystemRegister(0, 1, 2);  // actually 5 Bits are the SPID, i.e. B'00010
          #endif

          SWT_AssertCheckStart("RBSYS_resetCoreSPID2SafeSPID", "RBSYS_getCoreSPID() == RestrictedSPID");
          RBSYS_resetCoreSPID2SafeSPID();

          SWT_AssertCheckEnd();
        }     // TRBSYS_GuardConfig_010
      #endif  // Restricted SPID feature for GRAM

      #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
        /**
          * \TestCaseName TRBSYS_GuardConfig_009a
          *
          * \Reference
          * RBSYS_PRC_FSW_VerifyFinalGuardSettings
          *
          * \Purpose Test error detection functionality for wrong precondition of Guard configuration registers
          *
          * \Sequence
          *  0. Set Lock-Bit of a GRAM Guard
          *  1. Call Guard Configuration (complete) -> should detect that Guards could not be configured properly
          *  2. Call RBSYS_PRC_FSW_VerifyFinalGuardSettings -> should report SysErrorHook based on the feedback of Step 1.)
          *
          * \ExpectedResult
          *  SysErrorHook with DebugData "GuardConfigurationFailed"
          */
        SWTEST void TRBSYS_GuardConfig_009a(void)
        {
          MGDGRPROT0 = (1<<31); // Lock-Bit set

          RBSYS_BasicGuardInit();
          RBSYS_SetBusMasterIDs();
          RBSYS_GRAMGuardInit();
          RBSYS_EnhancedGuardInit();
          RBSYS_PRC_FSW_FinalGuard_Init();

          /* call also the overall check process */
          RBSYS_PRC_FSW_VerifyFinalGuardSettings();
          SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
          SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_GuardConfigurationFailed);
          SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (1<<1) /* GRG Config Invalid */);

          MGDGRPROT0 = 0;      // Reset the manipulated value
          DemStub_EnvReset();  // Reset DemStub
        }

        static void trbsys_GuardConfig_009b_GrgPbgSPIDRegStuckAt0(void)
        {
          APBFSGDSPID_SP4_B = 0;
        }

        /**
          * \TestCaseName TRBSYS_GuardConfig_009b
          *
          * \Reference
          * RBSYS_PRC_FSW_VerifyFinalGuardSettings
          *
          * \Purpose Test error detection functionality for wrong configuration of Guard configuration registers
          *
          * \Sequence
          *  0. Add manipulation callback for PBUS Guard configuration (will manipulate once PBG configuration is started)
          *  1. Call Guard Configuration (complete)
          *  2. Call RBSYS_PRC_FSW_VerifyFinalGuardSettings -> should report SysErrorHook as final settings are invalid
          *
          * \ExpectedResult
          *  SysErrorHook with DebugData "GuardConfigurationFailed"
          */
        SWTEST void TRBSYS_GuardConfig_009b(void)
        {
          TestInjectionCallback_PBUSGuardForGRAMManipulation = &trbsys_GuardConfig_009b_GrgPbgSPIDRegStuckAt0;

          RBSYS_BasicGuardInit();
          RBSYS_SetBusMasterIDs();
          RBSYS_GRAMGuardInit();
          RBSYS_EnhancedGuardInit();
          RBSYS_PRC_FSW_FinalGuard_Init();

          /* call also the overall check process */
          RBSYS_PRC_FSW_VerifyFinalGuardSettings();
          SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
          SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_GuardConfigurationFailed);
          SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (1<<1) /* GRG Config Invalid */);

          MGDGRPROT0 = 0;    // Reset the manipulated value
          DemStub_EnvReset(); // Reset DemStub
        }

        static void trbsys_GuardConfig_009c_GrgPbgPROTRegStuckAt0(void)
        {
          APBFSGDPROT_SP4_B = 0;
        }
        
        /**
          * \TestCaseName TRBSYS_GuardConfig_009c
          *
          * \Reference
          * RBSYS_PRC_FSW_VerifyFinalGuardSettings
          *
          * \Purpose Test error detection functionality for wrong configuration of Guard configuration registers
          *
          * \Sequence
          *  0. Add manipulation callback for PBUS Guard configuration (will manipulate once PBG configuration is started)
          *  1. Call Guard Configuration (complete)
          *  2. Call RBSYS_PRC_FSW_VerifyFinalGuardSettings -> should report SysErrorHook as final settings are invalid
          *
          * \ExpectedResult
          *  SysErrorHook with DebugData "GuardConfigurationFailed"
          */
        SWTEST void TRBSYS_GuardConfig_009c(void)
        {
          TestInjectionCallback_PBUSGuardForGRAMManipulation = &trbsys_GuardConfig_009c_GrgPbgPROTRegStuckAt0;

          RBSYS_BasicGuardInit();
          RBSYS_SetBusMasterIDs();
          RBSYS_GRAMGuardInit();
          RBSYS_EnhancedGuardInit();
          RBSYS_PRC_FSW_FinalGuard_Init();

          /* call also the overall check process */
          RBSYS_PRC_FSW_VerifyFinalGuardSettings();
          SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
          SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_GuardConfigurationFailed);
          SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (1<<1) /* GRG Config Invalid */);

          MGDGRPROT0 = 0;    // Reset the manipulated value
          DemStub_EnvReset(); // Reset DemStub
        }

        /**
          * \TestCaseName TRBSYS_GuardConfig_009d
          *
          * \Reference
          * RBSYS_PRC_FSW_VerifyFinalGuardSettings
          *
          * \Purpose Test error detection functionality for wrong configuration of Guard configuration registers
          *
          * \Sequence
          *  0. Manipulate a PEGuard configuration register (xxBA-Register)
          *  1. Call Guard Configuration (complete)
          *  2. Call RBSYS_PRC_FSW_VerifyFinalGuardSettings -> should report SysErrorHook as final settings are invalid
          *
          * \ExpectedResult
          *  SysErrorHook with DebugData "GuardConfigurationFailed"
          */
        SWTEST void TRBSYS_GuardConfig_009d(void)
        {
          /************ Core 0 ************/
          TRBSYS_setCoreID(0);
          PEGG2BA = 0xAAAAAAAAu;

          RBSYS_BasicGuardInit();
          RBSYS_SetBusMasterIDs();
          RBSYS_GRAMGuardInit();
          RBSYS_EnhancedGuardInit();
          RBSYS_PRC_FSW_FinalGuard_Init();

          /* call also the overall check process */
          RBSYS_PRC_FSW_VerifyFinalGuardSettings();
          SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
          SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_GuardConfigurationFailed);
          SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (0<<24)|(1<<0) /* LRAM Guard Config Invalid on Core 0 */);

          DemStub_EnvReset(); // Reset DemStub

          
          /************ Core 1 ************/
          TRBSYS_setCoreID(1);
          PEGG4BA = 0x55555555u;

          RBSYS_BasicGuardInit();
          // RBSYS_GRAMGuardInit();      //< only executed on Core 0
          // RBSYS_EnhancedGuardInit();  //< only executed on Core 0
          RBSYS_PRC_FSW_FinalGuard_Init();

          /* call also the overall check process */
          RBSYS_PRC_FSW_VerifyFinalGuardSettings();
          SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
          SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_GuardConfigurationFailed);
          SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (1<<24)|(1<<0) /* LRAM Guard Config Invalid on Core 1 */);

          DemStub_EnvReset(); // Reset DemStub
        }
      
      #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      
        static void trbsys_CorrectSettingOfKCProtRegister(void)
        {
          GUARD_DTSDTSGKCPROT     &= 0x00000001u;
          GUARD_DMAC0DMAGKCPROT   &= 0x00000001u;
          GUARD_DMAC1DMAGKCPROT   &= 0x00000001u;
          GUARD_BARRBRGKCPROT     &= 0x00000001u;
          GUARD_IPIRIPIGKCPROT    &= 0x00000001u;
          GUARD_TPTMTPTGKCPROT    &= 0x00000001u;
          GUARD_PE0CL0PEGKCPROT   &= 0x00000001u;
          GUARD_PE1CL0PEGKCPROT   &= 0x00000001u;
          GUARD_CRAMCRG0CRGKCPROT &= 0x00000001u;
          GUARD_CRAMCRG1CRGKCPROT &= 0x00000001u;
          GUARD_CRAMCRG2CRGKCPROT &= 0x00000001u;
          GUARD_CRAMCRG3CRGKCPROT &= 0x00000001u;

          #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
            PBGERRSLV00PBGKCPROT    &= 0x00000001u;
            PBGERRSLV10PBGKCPROT    &= 0x00000001u;
            PBGERRSLV20PBGKCPROT    &= 0x00000001u;
            PBGERRSLV30PBGKCPROT    &= 0x00000001u;
            PBGERRSLV40PBGKCPROT    &= 0x00000001u;
            PBGERRSLV50PBGKCPROT    &= 0x00000001u;
            PBGERRSLV6L0PBGKCPROT   &= 0x00000001u;
            PBGERRSLV6L1PBGKCPROT   &= 0x00000001u;
            PBGERRSLV6H0PBGKCPROT   &= 0x00000001u;
            PBGERRSLV70PBGKCPROT    &= 0x00000001u;
            PBGERRSLV80PBGKCPROT    &= 0x00000001u;
            PBGERRSLV90PBGKCPROT    &= 0x00000001u;
          #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
            PBGERRSLV00PBGKCPROT    &= 0x00000001u;
            PBGERRSLV01PBGKCPROT    &= 0x00000001u;
            PBGERRSLV10PBGKCPROT    &= 0x00000001u;
            PBGERRSLV20PBGKCPROT    &= 0x00000001u;
            PBGERRSLV21PBGKCPROT    &= 0x00000001u;
            PBGERRSLV22PBGKCPROT    &= 0x00000001u;
            PBGERRSLV30PBGKCPROT    &= 0x00000001u;
            PBGERRSLV31PBGKCPROT    &= 0x00000001u;
            PBGERRSLV40PBGKCPROT    &= 0x00000001u;
            PBGERRSLV41PBGKCPROT    &= 0x00000001u;
            PBGERRSLV50PBGKCPROT    &= 0x00000001u;
            PBGERRSLV51PBGKCPROT    &= 0x00000001u;
            PBGERRSLV52PBGKCPROT    &= 0x00000001u;
            PBGERRSLV60PBGKCPROT    &= 0x00000001u;
            PBGERRSLV61PBGKCPROT    &= 0x00000001u;
            PBGERRSLV7H0PBGKCPROT   &= 0x00000001u;
            PBGERRSLV7L0PBGKCPROT   &= 0x00000001u;
            PBGERRSLV8H0PBGKCPROT   &= 0x00000001u;
            PBGERRSLV8L0PBGKCPROT   &= 0x00000001u;
            PBGERRSLV90PBGKCPROT    &= 0x00000001u;
            PBGERRSLV91PBGKCPROT    &= 0x00000001u;
            PBGERRSLV100PBGKCPROT   &= 0x00000001u;
            PBGERRSLV101PBGKCPROT   &= 0x00000001u;
            PBGERRSLV11H0PBGKCPROT  &= 0x00000001u;
            PBGERRSLV11H1PBGKCPROT  &= 0x00000001u;
            PBGERRSLV11L0PBGKCPROT  &= 0x00000001u;
          #endif

          HBGHBGERRSLV91HBGKCPROT &= 0x00000001u;
          HBGHBGERRSLV92HBGKCPROT &= 0x00000001u;
          HBGHBGERRSLV93HBGKCPROT &= 0x00000001u;
          HBGHBGERRSLV96HBGKCPROT &= 0x00000001u;
        }

        /**
          * \TestCaseName TRBSYS_GuardConfig_VerifyFinalU2AGuardSettings
          *
          * \Reference
          * RBSYS_BasicGuardInit, RBSYS_EnhancedGuardInit, RBSYS_PRC_FSW_VerifyFinalGuardSettings
          *
          * \Purpose Test if all Guards are setup correctly and setting is checked against the input
          *
          * \Sequence
          *  0. Set Core 0
          *  1. call RBSYS_BasicGuardInit
          *  2. Set Core 1
          *  3. call RBSYS_BasicGuardInit
          *  4. call RBSYS_EnhancedGuardInit
          *  5. call RBSYS_PRC_FSW_FinalGuard_Init
          *  6. call RBSYS_PRC_FSW_VerifyFinalGuardSettings -> no Error Hook
          *  7. Manipulate a Guard setting
          *  8. call RBSYS_PRC_FSW_VerifyFinalGuardSettings -> Error Hook
          *  9. Set Core 1
          * 10. call RBSYS_PRC_FSW_VerifyFinalGuardSettings -> no Error Hook because called from wrong core
          * 11. Test Restricted Exclusive GRAM deactivation APIs
          *
          * \ExpectedResult
          * The core will toggle its SPID accordingly
          */
        SWTEST void TRBSYS_GuardConfig_VerifyFinalU2AGuardSettings(void)
        {
          TRBSYS_setCoreID(0);
          RBSYS_BasicGuardInit();
          TRBSYS_setCoreID(1);
          RBSYS_BasicGuardInit();


          TRBSYS_setCoreID(0);
          RBSYS_SetBusMasterIDs();
          RBSYS_GRAMGuardInit();
          RBSYS_EnhancedGuardInit();

          /* RBSYS_EnhancedGuardInit does guard itself against being called from Core != Core 0 */
          TRBSYS_setCoreID(1);
          RBSYS_EnhancedGuardInit();
          TRBSYS_setCoreID(0);

          #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
            // Any RAM Guard that is assigned to Resticted SPID shall not be locked until FinalGuard_Init
            // Any RAM Guard that is assigned to Resticted SPID shall be assigned to SAFE SPID as well until FinalGuard_Init
            #if( (RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K) && (RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted) )
              SWT_EvalEqX(GUARD_CRAMCSG0CSGPROT0, 0x00000151u);
              SWT_EvalEqX(GUARD_CRAMCSG0CSGSPID0, RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK);
            #endif
            #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
              SWT_EvalEqX(GUARD_CRAMCRG3CRGPROT0, 0x00000151u);
              SWT_EvalEqX(GUARD_CRAMCRG3CRGSPID0, RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SAFE_MASK);
            #endif
          #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
            // Any RAM Guard that is assigned to Resticted SPID shall not be locked until FinalGuard_Init
            // Any RAM Guard that is assigned to Resticted SPID shall be assigned to SAFE SPID as well until FinalGuard_Init
            #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
              SWT_EvalEqX(GUARD_CRAMCSG0CSGPROT0, 0x00000151u);
              SWT_EvalEqX(GUARD_CRAMCSG0CSGSPID0, RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SAFE_MASK);
            #endif
            #if( (RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K) && (RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted) )
              SWT_EvalEqX(GUARD_CRAMCSG0CSGPROT2, 0x00000151u);
              SWT_EvalEqX(GUARD_CRAMCSG0CSGSPID2, RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SAFE_MASK | RBSYS_SPID_SECURE_MASK);
            #endif
          #endif
          

          /* Sanity check: CRAM Guards shall not be locked + Exclusive SPID Sections shall not be activated from Core 1 */
          TRBSYS_setCoreID(1);
          RBSYS_PRC_FSW_FinalGuard_Init();
          SWT_EvalEqX(GUARD_CRAMCSG0CSGPROT0 & RBSYS_CRAMGUARD_LOCK, 0);                               //< one lock bit as an example
          #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
            #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
              SWT_EvalEqX(GUARD_CRAMCRG3CRGSPID0, RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SAFE_MASK);  //< Safe Access shall still be allowed
            #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
              SWT_EvalEqX(GUARD_CRAMCSG0CSGSPID0, RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SAFE_MASK);  //< Safe Access shall still be allowed
            #endif
          #endif
          TRBSYS_setCoreID(0);


          RBSYS_PRC_FSW_FinalGuard_Init();

          #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
            #if( (RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K) && (RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted) )
              SWT_EvalEqX(GUARD_CRAMCSG0CSGPROT0, 0x80000151u);
              SWT_EvalEqX(GUARD_CRAMCSG0CSGSPID0, RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SECURE_MASK);
            #endif
            #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
              SWT_EvalEqX(GUARD_CRAMCRG3CRGPROT0, 0x00000151u);
              SWT_EvalEqX(GUARD_CRAMCRG3CRGSPID0, RBSYS_SPID_RESTRICTED_MASK);
            #endif
          #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
            // #if( (RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K) && (RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted) )
            //   SWT_EvalEqX(GUARD_CRAMCSG0CSGPROT2, 0x80000151u);
            //   SWT_EvalEqX(GUARD_CRAMCSG0CSGSPID2, RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SECURE_MASK);
            // #endif
            // #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
            //   SWT_EvalEqX(GUARD_CRAMCRG0CRGPROT0, 0x00000151u);
            //   SWT_EvalEqX(GUARD_CRAMCRG0CRGSPID0, RBSYS_SPID_RESTRICTED_MASK);
            // #endif
            #warning("todo: Implement CSG Guards...")
          #endif

          /* KCPROT Setting is invalid (Only Bit 0 can be read) */
          trbsys_CorrectSettingOfKCProtRegister();
            
          /* Verification */
          RBSYS_PRC_FSW_VerifyFinalGuardSettings();
          SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);

          /* Manipulation PEGuard */
          {
            uint32 orig = GUARD_PE0CL0PEGPROT2;
            GUARD_PE0CL0PEGPROT2 = 0x13371337u;
            RBSYS_PRC_FSW_VerifyFinalGuardSettings();
            SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
            GUARD_PE0CL0PEGPROT2 = orig;
          }

          /* Manipulation PBUSGuard for PEGuard */
          {
            uint32 orig = PBG01.PBGPROT0_0;
            DemStub_EnvReset(); // Reset DemStub
            PBG01.PBGPROT0_0 = 0;
            RBSYS_PRC_FSW_VerifyFinalGuardSettings();
            SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
            PBG01.PBGPROT0_0 = orig;
          }

          /* Manipulation PBUSGuard */
          {
            uint32 orig = PBG00.PBGPROT0_1;
            DemStub_EnvReset(); // Reset DemStub
            PBG00.PBGPROT0_1 = 0;
            RBSYS_PRC_FSW_VerifyFinalGuardSettings();
            SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
            PBG00.PBGPROT0_1 = orig;
          }

          #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
            /* Manipulation HBUSGuard */
            {
              uint32 orig = HBG92HBGPROT0;
              DemStub_EnvReset(); // Reset DemStub
              HBG92HBGPROT0 = 0;
              RBSYS_PRC_FSW_VerifyFinalGuardSettings();
              SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
              HBG92HBGPROT0 = orig;
            }
          #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
            #warning("HBG for U2C is not enabled yet. see issue description")
          #endif

          /* Called from wrong core */
          DemStub_EnvReset(); // Reset DemStub
          TRBSYS_setCoreID(1);
          RBSYS_PRC_FSW_VerifyFinalGuardSettings();
          SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);

          #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
            /* Restricted Exclusive GRAM: Allow Safe Access */
            RBSYS_RestrictedExclusiveGRAM_AllowSafeAccess();
            #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
              SWT_EvalEqX(GUARD_CRAMCRG3CRGSPID0, RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SAFE_MASK);  //< Safe Access shall still be allowed
            #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
              SWT_EvalEqX(GUARD_CRAMCSG0CSGSPID0, RBSYS_SPID_RESTRICTED_MASK | RBSYS_SPID_SAFE_MASK);  //< Safe Access shall still be allowed
            #endif

            /* Restricted Exclusive GRAM: Block Safe Access again */
            RBSYS_RestrictedExclusiveGRAM_BlockSafeAccess();
            #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
              SWT_EvalEqX(GUARD_CRAMCRG3CRGSPID0, RBSYS_SPID_RESTRICTED_MASK);
            #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
              SWT_EvalEqX(GUARD_CRAMCSG0CSGSPID0, RBSYS_SPID_RESTRICTED_MASK);
            #endif
          #endif
        }
      #endif

    #elif( (RBFS_HexBlockBuild == RBFS_HexBlockBuild_BOOTLOADER) \
        || (RBFS_HexBlockBuild == RBFS_HexBlockBuild_RBBOOTLOADER) \
      )
      #include "RBSYS_GuardConfigCommon.h"
      /**
        * \TestCaseName TRBSYS_GuardConfigCommon_EnhancedGuardInit
        *
        * \Reference
        * RBSYS_EnhancedGuardInit
        *
        * \Purpose Test if RBSYS_EnhancedGuardInit does call necessary initialization functions correctly
        *
        * \Sequence
        *  0. Set Core != 0
        *  1. call RBSYS_EnhancedGuardInit
        *  2. Verify: Guard Configuration not changed
        *  3. Set Core 0
        *  4. call RBSYS_EnhancedGuardInit
        *  5. Verify: if Memory Sync Command is called before Guards are being initialized
        *  6. Verify: if PBUS Guard Initialization has been called
        *
        * \ExpectedResult
        * see \Sequence
        */
      SWTEST void TRBSYS_GuardConfig_BB_EnhancedGuardInit(void)
      #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
        {
          #if(RBFS_MCORE == RBFS_MCORE_ON)
            TRBSYS_setCoreID(RBSYS_CORE_ID_1);
            RBSYS_EnhancedGuardInit();
            //  2. Verify: Guard Configuration not changed
            SWT_EvalEqX(FSGD1ASPID05, 0); //< example for one PBUS Guard SPID
            SWT_EvalEqX(FSGD1APROT04, 0); //< example for one PBUS Guard PROT
          #endif

          TRBSYS_setCoreID(RBSYS_CORE_ID_0);
          RBSYS_EnhancedGuardInit();

          //  5. Verify: if SYNCM is called before Guards are being initialized
          SWT_Eval(TRBSYS_Get_SYNCM_CNT() >= 2); //< is called at least before and after change of Memory Protection, order assured by review

          //  6. Verify: if PBUS Guard Initialization has been called
          SWT_EvalEqX(FSGD1ASPID05, RBSYS_SPID_SAFE_MASK);     //< example for first PBUS Guard SPID
          SWT_EvalEqX(FSGD1APROT04, RBSYS_PEID_PEID4);         //< example for first PBUS Guard PROT

          SWT_EvalEqX(FSGD3BSPID13, RBSYS_SPID_SAFE_MASK);     //< example for last PBUS Guard SPID
          SWT_EvalEqX(FSGD3BPROT13, RBSYS_PEID_PEID4);         //< example for last PBUS Guard PROT

          // 7. Verify: if GRAM Guard Initialization has been called
          #if( RBFS_RBSYSGlobalRAMGuardsBB == RBFS_RBSYSGlobalRAMGuardsBB_ON )
            SWT_Eval(MGDGRADV0 != 0);                          //< example for one GRAM Guard
          #endif
        }
      #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        {
          uint32 index_lastitem;
          const RBSYS_BUSGuardConfig_t* trbsys_PBusGuardConfigs = TRBSYS_GetPBUSGuardsPointer();

          TRBSYS_setCoreID(RBSYS_CORE_ID_1);
          RBSYS_EnhancedGuardInit();
          //  2. Verify: Guard Configuration not changed
          SWT_EvalEqX(*trbsys_PBusGuardConfigs[0].SPID_Register, 0); //< example for one PBUS Guard SPID
          SWT_EvalEqX(*trbsys_PBusGuardConfigs[0].PROT_Register, 0); //< example for one PBUS Guard PROT

          TRBSYS_setCoreID(RBSYS_CORE_ID_0);
          RBSYS_EnhancedGuardInit();

          //  5. Verify: if SYNCM is called before Guards are being initialized
          SWT_Eval(TRBSYS_Get_SYNCM_CNT() >= 2); //< is called at least before and after change of Memory Protection, order assured by review

          //  6. Verify: if PBUS Guard Initialization has been called
          SWT_EvalEqX(*trbsys_PBusGuardConfigs[0].SPID_Register, trbsys_PBusGuardConfigs[0].SPID_Mask);    //< example for first PBUS Guard SPID
          SWT_EvalEqX(*trbsys_PBusGuardConfigs[0].PROT_Register, trbsys_PBusGuardConfigs[0].PROT_Setting); //< example for first PBUS Guard PROT

          index_lastitem = TRBSYS_GetNumOfPBUSGuards() -1;
          SWT_EvalEqX(*trbsys_PBusGuardConfigs[index_lastitem].SPID_Register, trbsys_PBusGuardConfigs[index_lastitem].SPID_Mask);    //< example for last PBUS Guard SPID
          SWT_EvalEqX(*trbsys_PBusGuardConfigs[index_lastitem].PROT_Register, trbsys_PBusGuardConfigs[index_lastitem].PROT_Setting); //< example for last PBUS Guard PROT

          // 7. Verify: if GRAM Guard Initialization has been called
          #if (RBFS_RBSYSGlobalRAMGuardsBB == RBFS_RBSYSGlobalRAMGuardsBB_ON)
            SWT_Eval(GUARD_CRAMCRG0CRGSPID0 != 0);
          #endif
        }
      #else
        /**
          * \TestCaseName TRBSYS_Dummy
          *
          * \Reference
          * Dummy
          *
          *
          * \Purpose Dummy testcase for Bootmanager configuration
          *
          * \Sequence
          *
          *
          * \ExpectedResult
          *
          */
          SWTEST void TRBSYS_Dummy(void)
          {
              SWT_EvalEx(TRUE, "Feature not Available");
          }
      #endif

    #elif( RBFS_HexBlockBuild == RBFS_HexBlockBuild_BOOTMANAGER )
      #include "RBSYS_GuardConfigCommon.h"
      /**
        * \TestCaseName TRBSYS_GuardConfigCommon_LRAMGRAMGuards
        *
        * \Reference
        * RBSYS_BasicGuardInit, RBSYS_GRAMGuardInit
        *
        * \Purpose Test if RBSYS_BasicGuardInit and RBSYS_GRAMGuardInit do necessary initializations correctly
        *
        * \Sequence
        *  0. Set Core != 0
        *  1. call RBSYS_BasicGuardInit
        *  (2. call RBSYS_GRAMGuardInit -> must not be called on Core other than Core 0)
        *  3. Verify: Guard Configuration not changed
        *  4. Set Core 0
        *  5. call RBSYS_BasicGuardInit
        *  6. call RBSYS_GRAMGuardInit
        *  7. Verify: if SPIDs of Unsafe BusMasters are set
        *  8. Verify: if Guard Initialization has been completed
        *
        * \ExpectedResult
        * see \Sequence
        */
      SWTEST void TRBSYS_GuardConfigBB_LRAMGRAMGuards(void)
      #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
        {
          #if(RBFS_MCORE == RBFS_MCORE_ON)
            TRBSYS_setCoreID(RBSYS_CORE_ID_1);
            RBSYS_BasicGuardInit();
            
            //  3. Verify: Guard Configuration not changed
            SWT_Eval(PEGG0MK != 0);                                   //< each Core will only change its own "SELF"-Registers (same address on all cores)
            PEGG0MK = 0;
          #endif

          TRBSYS_setCoreID(RBSYS_CORE_ID_0);
          RBSYS_BasicGuardInit();
          RBSYS_SetBusMasterIDs();
          #if( RBFS_RBSYSGlobalRAMGuardsBB == RBFS_RBSYSGlobalRAMGuardsBB_ON )
            RBSYS_GRAMGuardInit();
          #endif

          //  7. Verify: if Unsafe SPIDs are set
          #if(((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2)) \
            || (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD3ED) \
              )
            SWT_EvalEqX(HSSPIDRG0, (uint32)UnSafeSPID);
          #endif

          //  8. Verify: if Guard Initialization has been called
          SWT_Eval(PEGG0MK != 0);   //< example for LRAM Guard (original implementation in asm)
          #if( RBFS_RBSYSGlobalRAMGuardsBB == RBFS_RBSYSGlobalRAMGuardsBB_ON )
            SWT_Eval(MGDGRADV0 != 0);                                 //< example for one GRAM Guard
          #endif
        }
      #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        {
          TRBSYS_setCoreID(RBSYS_CORE_ID_1);
          RBSYS_BasicGuardInit();

          //  3. Verify: Guard Configuration not changed
          SWT_Eval(GUARD_PE0CL0PEGSPID0 == 0);   //< example for LRAM Guard (original implementation in asm)
          SWT_Eval(GUARD_PE1CL0PEGSPID0 != 0);   //< example for LRAM Guard (original implementation in asm)
          
          TRBSYS_setCoreID(RBSYS_CORE_ID_0);
          RBSYS_BasicGuardInit();
          RBSYS_SetBusMasterIDs();
          #if( RBFS_RBSYSGlobalRAMGuardsBB == RBFS_RBSYSGlobalRAMGuardsBB_ON )
            RBSYS_GRAMGuardInit();
          #endif

          //  7. Verify: if Unsafe SPIDs are set
          SWT_EvalEqX( SPIDCTLBM26SPID, (uint32)SecureSPID );

          //  8. Verify: if GRAM Guard Initialization has been called (including Guard of Guards) -> if feature active only!
          SWT_Eval( GUARD_PE0CL0PEGSPID0 != 0 );   //< example for LRAM Guard (original implementation in asm)
          #if (RBFS_RBSYSGlobalRAMGuardsBB == RBFS_RBSYSGlobalRAMGuardsBB_ON)
            SWT_Eval(GUARD_CRAMCRG0CRGSPID0 != 0);
          #endif
        }
      #endif
    #endif



  #else   //  --- RBFS_TRBSYSGuardVariance_unsupported

  /**
   * \TestCaseName TRBSYS_GuardConfig_FeatureNotAvailable
   *
   * \Reference
   * Dummy
   *
   *
   * \Purpose Dummy testcase if no successful build possible due to sanity checks
   *
   * \Sequence
   *
   *
   * \ExpectedResult
   *
   */

  SWTEST void TRBSYS_GuardConfig_FeatureNotAvailable(void)
  {
      SWT_EvalEx(TRUE, "Feature not Available");
  }


  #endif

#else
  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )

    #include "RBSYS_SystemMpu_Info.h"

    #define MASTERACC_NONE   0x0
    #define MASTERACC_R      0x1
    #define MASTERACC_RW     0x3
    #define MASTERACC_RX     0x5

    #define MASTERID_KITE0_0 0x00000000u     // SAFE
    #define MASTERID_KITE0_1 0x00000001u     // SAFE
    #define MASTERID_KITE0_2 0x00000002u     // SAFE
    #define MASTERID_KITE0_3 0x00000003u     // SAFE
    #define MASTERID_KITE1_0 0x00000004u     // SAFE
    #define MASTERID_KITE1_1 0x00000005u     // SAFE
    #define MASTERID_KITE1_2 0x00000006u     // SAFE
    #define MASTERID_KITE1_3 0x00000007u     // SAFE
    #define MASTERID_KITE2_0 0x00000008u     // SAFE
    #define MASTERID_KITE2_1 0x00000009u     // SAFE
    #define MASTERID_KITE2_2 0x0000000Au     // SAFE
    #define MASTERID_KITE2_3 0x0000000Bu     // SAFE
    #define MASTERID_DME     0x00000012u     // SAFE
    #define MASTERID_DSPH    0x00000016u     // UNSAFE
    #define MASTERID_HSM     0x00000018u     // SECURE
    #define MASTERID_DAP0    0x00000020u     // UNSAFE
    #define MASTERID_DAP1    0x00000021u     // UNSAFE
    #define MASTERID_Flex0   0x00000022u     // UNSAFE
    #define MASTERID_Flex1   0x00000023u     // UNSAFE
    #define MASTERID_ZipW0   0x00000024u     // UNSAFE
    #define MASTERID_ZipW1   0x00000025u     // UNSAFE
    #define MASTERID_TMC     0x00000030u     // UNSAFE
    #define MASTERID_Ether0  0x00000034u     // UNSAFE
    #define MASTERID_eDMA0   0x00000038u     // SAFE
    #define MASTERID_eDMA1   0x00000039u     // SAFE
    #define MASTERID_eDMA2   0x0000003Au     // SAFE
    #define MASTERID_eDMA3   0x0000003Bu     // SAFE
    #define MASTERID_GTM_M   0x0000003Eu     // UNSAFE
    #define MASTERID_DFA     0x0000003Fu     // UNSAFE

    #define REGION_ACTIVE    0x1
    #define EL1_CHECK_ACTIVE 0x1
    #define EL2_CHECK_ACTIVE 0x1
    #define FIREWALL_ACTIVE  0x1

    /*
      Necessary Tests:
        - KITEx PFlash shall be 
          - R+X from other KITE Clusters (X from Instruction Port, R from Data Port) -> anpassen
          - R from any other BusMaster
        - KITEx other Memory shall be
          - No Access from Unsafe Busmasters
          - No Access from Secure Busmasters
          - R+W from Safe Busmasters
        - KITE0 RAM special regions shall be R/W/RW dependent on FS settings
        - Shall not be accessible by any BusMaster:
          - DAP
          - DFA
          - DME
          - OCT_SPI
          - TMC
          - TMC
          - TMC
    */

    typedef enum
    {
      TRBSYS_NOCRegionType_ClusterCodeFlash,
      TRBSYS_NOCRegionType_ClusterMemorySafeOnly,
      TRBSYS_NOCRegionType_ClusterMemorySafeAndSecure,
      TRBSYS_NOCRegionType_ClusterMemorySafeAndUnsafe,
      TRBSYS_NOCRegionType_OtherMemorySafeOnly,
      TRBSYS_NOCRegionType_OtherMemorySafeAndUnsafe,
      TRBSYS_NOCRegionType_UnusedMemory
    } TRBSYS_NOCRegionType_n;

    static void trbsys_EvalNOCFirewallRegion_Impl(rba_Reg_FIREWALL_tst* fw, uint32 regionIdx, TRBSYS_NOCRegionType_n regionType)
    {
      uint32 safeMasterKiteAXIMPrivilege, safeMasterKiteAXIFPrivilege, safeMasterOtherPrivilege, unsafeMasterPrivilege, secureMasterPrivilege;
      
      switch(regionType)
      {
        case TRBSYS_NOCRegionType_ClusterCodeFlash:
          safeMasterKiteAXIMPrivilege  = MASTERACC_NONE;  // Cluster CodeFlash is not accessible via KITE AXIM interface
          safeMasterKiteAXIFPrivilege  = MASTERACC_RX;    // Cluster CodeFlash is executable and readable by KITEs
          safeMasterOtherPrivilege     = MASTERACC_R;     // Cluster CodeFlash is readable by other SAFE BusMasters
          unsafeMasterPrivilege        = MASTERACC_R;     // Cluster CodeFlash is readable by other UNSAFE BusMasters
          secureMasterPrivilege        = MASTERACC_R;     // Cluster CodeFlash is readable by SECURE BusMasters
          break;
        case TRBSYS_NOCRegionType_ClusterMemorySafeOnly:
          safeMasterKiteAXIMPrivilege  = MASTERACC_RW;    // Cluster Memory is readable/writeable by KITEs
          safeMasterKiteAXIFPrivilege  = MASTERACC_NONE;  // Cluster Memory is not accessible via KITE AXIF interface
          safeMasterOtherPrivilege     = MASTERACC_RW;    // Cluster Memory is readable/writeable by other SAFE BusMasters
          unsafeMasterPrivilege        = MASTERACC_NONE;  // Cluster Memory is not accessible by other UNSAFE BusMasters
          secureMasterPrivilege        = MASTERACC_NONE;  // Cluster Memory is not accessible by SECURE BusMasters
          break;
        case TRBSYS_NOCRegionType_ClusterMemorySafeAndSecure:
          safeMasterKiteAXIMPrivilege  = MASTERACC_RW;    // Cluster Memory is readable/writeable by KITEs
          safeMasterKiteAXIFPrivilege  = MASTERACC_NONE;  // Cluster Memory is not accessible via KITE AXIF interface
          safeMasterOtherPrivilege     = MASTERACC_RW;    // Cluster Memory is readable/writeable by other SAFE BusMasters
          unsafeMasterPrivilege        = MASTERACC_NONE;  // Cluster Memory is not accessible by other UNSAFE BusMasters
          secureMasterPrivilege        = MASTERACC_RW;    // Cluster Memory is readable/writeable by SECURE BusMasters
          break;
        case TRBSYS_NOCRegionType_ClusterMemorySafeAndUnsafe:
          safeMasterKiteAXIMPrivilege  = MASTERACC_RW;    // Cluster Memory is readable/writeable by KITEs
          safeMasterKiteAXIFPrivilege  = MASTERACC_NONE;  // Cluster Memory is not accessible via KITE AXIF interface
          safeMasterOtherPrivilege     = MASTERACC_RW;    // Cluster Memory is readable/writeable by other SAFE BusMasters
          unsafeMasterPrivilege        = MASTERACC_RW;    // Cluster Memory is readable/writeable by other UNSAFE BusMasters
          secureMasterPrivilege        = MASTERACC_NONE;  // Cluster Memory is not accessible by SECURE BusMasters
          break;
        case TRBSYS_NOCRegionType_OtherMemorySafeOnly:
          safeMasterKiteAXIMPrivilege  = MASTERACC_RW;    // Other Memory is readable/writeable by KITEs
          safeMasterKiteAXIFPrivilege  = MASTERACC_NONE;  // Other Memory is not accessible via KITE AXIF interface
          safeMasterOtherPrivilege     = MASTERACC_RW;    // Other Memory is readable/writeable by other SAFE BusMasters
          unsafeMasterPrivilege        = MASTERACC_NONE;  // Other Memory is not accessible by other UNSAFE BusMasters
          secureMasterPrivilege        = MASTERACC_NONE;  // Other Memory is not accessible by SECURE BusMasters
          break;
        case TRBSYS_NOCRegionType_OtherMemorySafeAndUnsafe:
          safeMasterKiteAXIMPrivilege  = MASTERACC_RW;    // Other Memory is readable/writeable by KITEs
          safeMasterKiteAXIFPrivilege  = MASTERACC_NONE;  // Other Memory is not accessible via KITE AXIF interface
          safeMasterOtherPrivilege     = MASTERACC_RW;    // Other Memory is readable/writeable by other SAFE BusMasters
          unsafeMasterPrivilege        = MASTERACC_RW;    // Other Memory is readable/writeable by other UNSAFE BusMasters
          secureMasterPrivilege        = MASTERACC_NONE;  // Other Memory is not accessible by SECURE BusMasters
          break;
        case TRBSYS_NOCRegionType_UnusedMemory:
          safeMasterKiteAXIMPrivilege  = MASTERACC_NONE;  // Unused Memory is not accessible by KITEs
          safeMasterKiteAXIFPrivilege  = MASTERACC_NONE;  // Unused Memory is not accessible via KITE AXIF interface
          safeMasterOtherPrivilege     = MASTERACC_NONE;  // Unused Memory is not accessible by other SAFE BusMasters
          unsafeMasterPrivilege        = MASTERACC_NONE;  // Unused Memory is not accessible by other UNSAFE BusMasters
          secureMasterPrivilege        = MASTERACC_NONE;  // Unused Memory is not accessible by SECURE BusMasters
          break;
        default:
          assert(0);
          break;
      }

      if( fw == &KITE1_FIREWALL || fw == &KITE2_FIREWALL )
      {
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_KITE0_0], safeMasterKiteAXIMPrivilege ); // AXIM port of Core0
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_KITE0_1], safeMasterKiteAXIMPrivilege ); // AXIM port of Core1
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_KITE0_2], safeMasterKiteAXIFPrivilege ); // AXIF port of Core0
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_KITE0_3], safeMasterKiteAXIFPrivilege ); // AXIF port of Core1
      }
      if( fw == &KITE0_FIREWALL || fw == &KITE2_FIREWALL )
      {
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_KITE1_0], safeMasterKiteAXIMPrivilege ); // AXIM port of Core2
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_KITE1_1], safeMasterKiteAXIMPrivilege ); // AXIM port of Core3
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_KITE1_2], safeMasterKiteAXIFPrivilege ); // AXIF port of Core2
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_KITE1_3], safeMasterKiteAXIFPrivilege ); // AXIF port of Core3
      }
      if( fw == &KITE0_FIREWALL || fw == &KITE1_FIREWALL )
      {
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_KITE2_0], safeMasterKiteAXIMPrivilege ); // AXIM port of Core4
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_KITE2_1], safeMasterKiteAXIMPrivilege ); // AXIM port of Core5
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_KITE2_2], safeMasterKiteAXIFPrivilege ); // AXIF port of Core4
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_KITE2_3], safeMasterKiteAXIFPrivilege ); // AXIF port of Core5
      }

      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_DME],     safeMasterOtherPrivilege );
      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_DSPH],    unsafeMasterPrivilege );
      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_HSM],     secureMasterPrivilege );
      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_DAP0],    MASTERACC_NONE );
      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_DAP1],    MASTERACC_NONE );
      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_Flex0],   unsafeMasterPrivilege );
      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_Flex1],   unsafeMasterPrivilege );
      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_ZipW0],   MASTERACC_NONE );
      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_ZipW1],   MASTERACC_NONE );
      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_TMC],     MASTERACC_NONE );
      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_Ether0],  unsafeMasterPrivilege );
      if( fw != &NVM_FIREWALL ) // eDMA has access to same as R52s, except NVM WritePort
      {
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_eDMA0],   safeMasterOtherPrivilege );
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_eDMA1],   safeMasterOtherPrivilege );
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_eDMA2],   safeMasterOtherPrivilege );
        SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_eDMA3],   safeMasterOtherPrivilege );
      }
      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_GTM_M],   unsafeMasterPrivilege );
      SWT_EvalEqX( fw->EL1_MSTR[regionIdx][MASTERID_DFA],     MASTERACC_NONE );

      SWT_EvalEqX( fw->EL1_REG[regionIdx].CONF,               REGION_ACTIVE );
    }

    static void trbsys_EvalNOCFirewallEnabled(rba_Reg_FIREWALL_tst* fw)
    {
      SWT_EvalEqX( fw->FW_EL1_CONFIG_REG,             EL1_CHECK_ACTIVE);
      SWT_EvalEqX( fw->FW_EL2_CONFIG_REG,             0x00000000u);
      SWT_EvalEqX( fw->FW_CONFIG_REG,                 FIREWALL_ACTIVE);
    }

    static void trbsys_EvalNOCSlaveNotAccessibleAtAll(rba_Reg_FIREWALL_tst* fw)
    {
      trbsys_EvalNOCFirewallRegion_Impl(fw, 0, TRBSYS_NOCRegionType_UnusedMemory);

      SWT_EvalEqX( fw->EL1_REG[0].ADDR_START,         0x00000000u );
      SWT_EvalEqX( fw->EL1_REG[0].ADDR_SIZE,          0xFFFFFFC0u );

      trbsys_EvalNOCFirewallEnabled(fw);
    }

    static void trbsys_EvalNOCSlaveAccessibleBySAFEOnly(rba_Reg_FIREWALL_tst* fw)
    {
      trbsys_EvalNOCFirewallRegion_Impl(fw, 0, TRBSYS_NOCRegionType_OtherMemorySafeOnly);

      SWT_EvalEqX( fw->EL1_REG[0].ADDR_START,         0x00000000u );
      SWT_EvalEqX( fw->EL1_REG[0].ADDR_SIZE,          0xFFFFFFC0u );

      trbsys_EvalNOCFirewallEnabled(fw);
    }

    #include "stdio.h"

    static inline void pprint_firewall(rba_Reg_FIREWALL_tst* fw)
    {
      uint32 i, ii;
      printf("FW_CONFIG_REG = %u\n", fw->FW_CONFIG_REG);
      printf("FW_EL1_CONFIG_REG = %u\n", fw->FW_EL1_CONFIG_REG);

      for(i=0; i<RBA_REG_FIREWALL_MAX_REGIONS; i++)
      {
        printf("EL1_REG[%u].CONF = %u\n",        i, fw->EL1_REG[i].CONF       );
        printf("EL1_REG[%u].ADDR_START = %u\n",  i, fw->EL1_REG[i].ADDR_START );
        printf("EL1_REG[%u].ADDR_SIZE = %u\n",   i, fw->EL1_REG[i].ADDR_SIZE  );
      }
      for(i=0; i<RBA_REG_FIREWALL_MAX_REGIONS; i++)
      {
        for(ii=0; ii<RBA_REG_FIREWALL_MAX_BUSMASTER; ii++)
        {
          printf("EL1_MSTR[%u][%u] = %u\n", i, ii, fw->EL1_MSTR[i][ii]);;
        }
      }
    }

    #define PPRINT_FIREWALL(fw) \
      printf(#fw); \
      pprint_firewall(fw);

    /**
      * \TestCaseName TRBSYS_GuardConfig_NOCFirewall
      *
      * \Reference
      * RBSYS_GRAMGuardInit, RBSYS_EnhancedGuardInit ,Gen_SWCS_HSW_uC_Base_SYS-306
      *
      * \Purpose Test functionality of RBSYS_GRAMGuardInit and RBSYS_EnhancedGuardInit
      *
      * \Sequence
      *  0. Call RBSYS_GRAMGuardInit
      *  1. Evaluate if SYSRAM and ClusterRAM Memory Protection is initialized completely
      *  2. Call RBSYS_EnhancedGuardInit
      *  3. Evaluate if Peripheral Memory Protection is initialized completely
      *
      * \ExpectedResult
      * see \Sequence
      */
    SWTEST void TRBSYS_GuardConfig_NOCFirewall(void)
    {
      /** Evaluate:
        *   - Full address range for each NOC Slave is configured / restricted to accesses from SAFE BusMasters (apart from special regions)
        *   - Special regions:
        *     - HSM active: HSM Shared RAM in CRAM0_1 is accessible from SAFE and SECURE BusMaster 
        *     - Ethernet active: Ethernet Shared RAM in CRAM0_1 is accessible from SAFE and UNSAFE BusMaster
        *     - Unused NOC Slaves: Access shall be removed for any BusMaster
        *       - TMC0,1,2
        *       - OCTOSPI
        *       - DAP
        *       - DFA
        *       - DME
        */
  
      RBSYS_GRAMGuardInit();

      {
        // KITE0_FIREWALL
        uint32 idx = 0;
        
        // region 0
        trbsys_EvalNOCFirewallRegion_Impl(&KITE0_FIREWALL, idx, TRBSYS_NOCRegionType_ClusterCodeFlash);
        SWT_EvalEqX(KITE0_FIREWALL.EL1_REG[idx].ADDR_START, 0x00000000u);
        SWT_EvalEqX(KITE0_FIREWALL.EL1_REG[idx].ADDR_SIZE,  (RBSYS_Cluster0_REGION_0_SIZE) & 0xFFFFFFC0u); // size = (end - start) & 0xFFFFFFC0
        idx++;

        // region 1
        trbsys_EvalNOCFirewallRegion_Impl(&KITE0_FIREWALL, idx, TRBSYS_NOCRegionType_ClusterMemorySafeOnly);
        SWT_EvalEqX(KITE0_FIREWALL.EL1_REG[idx].ADDR_START, RBSYS_Cluster0_REGION_0_START + RBSYS_Cluster0_REGION_0_SIZE);
        SWT_EvalEqX(KITE0_FIREWALL.EL1_REG[idx].ADDR_SIZE,  (RBSYS_Cluster0_REGION_1_SIZE) & 0xFFFFFFC0u); // size = (end - start) & 0xFFFFFFC0
        idx++;

        // region 2
        #if( RBFS_SysEthSharedGRAMsize != RBFS_SysEthSharedGRAMsize_0K )
          trbsys_EvalNOCFirewallRegion_Impl(&KITE0_FIREWALL, idx, TRBSYS_NOCRegionType_ClusterMemorySafeAndUnsafe);
          SWT_EvalEqX(KITE0_FIREWALL.EL1_REG[idx].ADDR_START, RBSYS_EthernetSharedGRAMStartAddress);
          SWT_EvalEqX(KITE0_FIREWALL.EL1_REG[idx].ADDR_SIZE,  RBSYS_EthernetSharedGRAMSize & 0xFFFFFFC0u);
          idx++;
        #endif

        // region 3
        #if (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K)
          trbsys_EvalNOCFirewallRegion_Impl(&KITE0_FIREWALL, idx, TRBSYS_NOCRegionType_ClusterMemorySafeOnly);
          SWT_EvalEqX(KITE0_FIREWALL.EL1_REG[idx].ADDR_START, RBSYS_RestrictedExclusiveGRAMStartAddress);
          SWT_EvalEqX(KITE0_FIREWALL.EL1_REG[idx].ADDR_SIZE,  RBSYS_RestrictedExclusiveGRAMSize & 0xFFFFFFC0u);
          idx++;
          #warning("Restricted Exclusive GRAM feature is not supported (yet)" )
        #endif

        // region 4
        #if( RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K )
          trbsys_EvalNOCFirewallRegion_Impl(&KITE0_FIREWALL, idx, TRBSYS_NOCRegionType_ClusterMemorySafeAndSecure);
          SWT_EvalEqX(KITE0_FIREWALL.EL1_REG[idx].ADDR_START, RBSYS_HsmSharedGRAMStartAddress);
          SWT_EvalEqX(KITE0_FIREWALL.EL1_REG[idx].ADDR_SIZE,  RBSYS_HsmSharedGRAMSize & 0xFFFFFFC0u);
          idx++;
          #if( RBFS_SysHSMsharedGRAM != RBFS_SysHSMsharedGRAM_Host )
            #error("Restricted Exclusive GRAM feature is not supported (yet)" )
          #endif
        #endif

        // region 5
        trbsys_EvalNOCFirewallRegion_Impl(&KITE0_FIREWALL, idx, TRBSYS_NOCRegionType_ClusterMemorySafeOnly);
        // trbsys_EvalNOCFirewallRegion_RW_BySAFEOnly(&KITE0_FIREWALL, idx);
        SWT_EvalEqX(KITE0_FIREWALL.EL1_REG[idx].ADDR_START, RBSYS_Cluster0_REGION_LAST_START);
        SWT_EvalEqX(KITE0_FIREWALL.EL1_REG[idx].ADDR_SIZE,  RBSYS_Cluster0_REGION_LAST_SIZE & 0xFFFFFFC0u);
        idx++;

        // check if firewall is enabled
        trbsys_EvalNOCFirewallEnabled(&KITE0_FIREWALL);

        // Evaluate if full address space is covered
        SWT_EvalEqX( (0x00000000u
                    + RBSYS_Cluster0_REGION_0_SIZE 
                    + RBSYS_Cluster0_REGION_1_SIZE 
                    + RBSYS_EthernetSharedGRAMSize
                    + RBSYS_RestrictedExclusiveGRAMSize 
                    + RBSYS_HsmSharedGRAMSize), 
                    (RBSYS_Cluster0_REGION_LAST_START));
      }

      {
        // KITE1_FIREWALL
        uint32 idx = 0;
        
        // region 0
        trbsys_EvalNOCFirewallRegion_Impl(&KITE1_FIREWALL, idx, TRBSYS_NOCRegionType_ClusterCodeFlash);
        SWT_EvalEqX(KITE1_FIREWALL.EL1_REG[idx].ADDR_START, 0x00000000u);
        SWT_EvalEqX(KITE1_FIREWALL.EL1_REG[idx].ADDR_SIZE,  (0x29000000u) & 0xFFFFFFC0u); // size = (end - start) & 0xFFFFFFC0
        idx++;

        // region 1
        trbsys_EvalNOCFirewallRegion_Impl(&KITE1_FIREWALL, idx, TRBSYS_NOCRegionType_ClusterMemorySafeOnly);
        SWT_EvalEqX(KITE1_FIREWALL.EL1_REG[idx].ADDR_START, 0x29000000u);
        SWT_EvalEqX(KITE1_FIREWALL.EL1_REG[idx].ADDR_SIZE,  (0xFFFFFFC0 - 0x29000000) & 0xFFFFFFC0u); // size = (end - start) & 0xFFFFFFC0
        idx++;
      }

      {
        // KITE2_FIREWALL
        uint32 idx = 0;
        
        // region 0
        trbsys_EvalNOCFirewallRegion_Impl(&KITE2_FIREWALL, idx, TRBSYS_NOCRegionType_ClusterCodeFlash);
        SWT_EvalEqX(KITE2_FIREWALL.EL1_REG[idx].ADDR_START, 0x00000000u);
        SWT_EvalEqX(KITE2_FIREWALL.EL1_REG[idx].ADDR_SIZE,  (0x29800000) & 0xFFFFFFC0u); // size = (end - start) & 0xFFFFFFC0
        idx++;

        // region 1
        trbsys_EvalNOCFirewallRegion_Impl(&KITE2_FIREWALL, idx, TRBSYS_NOCRegionType_ClusterMemorySafeOnly);
        SWT_EvalEqX(KITE2_FIREWALL.EL1_REG[idx].ADDR_START, 0x29800000);
        SWT_EvalEqX(KITE2_FIREWALL.EL1_REG[idx].ADDR_SIZE,  (0xFFFFFFC0 - 0x29800000) & 0xFFFFFFC0u); // size = (end - start) & 0xFFFFFFC0
        idx++;
      }

      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&SYSRAM0_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&SYSRAM1_FIREWALL);

      RBSYS_EnhancedGuardInit();
      
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&AESLIGHT0_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&AESLIGHT1_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&AESLIGHT2_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&AESLIGHT3_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&AIPS0_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&AIPS1_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&AIPS2_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&AIPS3_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&AIPS4_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&DSPH_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&GTM_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&HSM_FIREWALL);
      trbsys_EvalNOCSlaveAccessibleBySAFEOnly(&NVM_FIREWALL);

      trbsys_EvalNOCSlaveNotAccessibleAtAll(&DAP_FIREWALL);
      trbsys_EvalNOCSlaveNotAccessibleAtAll(&DFA_FIREWALL);
      trbsys_EvalNOCSlaveNotAccessibleAtAll(&DME_FIREWALL);
      trbsys_EvalNOCSlaveNotAccessibleAtAll(&OCT_SPI_FIREWALL);
      trbsys_EvalNOCSlaveNotAccessibleAtAll(&TMC0_FIREWALL);
      trbsys_EvalNOCSlaveNotAccessibleAtAll(&TMC1_FIREWALL);
      trbsys_EvalNOCSlaveNotAccessibleAtAll(&TMC2_FIREWALL);

      
      PPRINT_FIREWALL(&KITE0_FIREWALL);
      PPRINT_FIREWALL(&KITE1_FIREWALL);
      PPRINT_FIREWALL(&KITE2_FIREWALL);
      PPRINT_FIREWALL(&SYSRAM0_FIREWALL);
      PPRINT_FIREWALL(&SYSRAM1_FIREWALL);
      PPRINT_FIREWALL(&AESLIGHT0_FIREWALL);
      PPRINT_FIREWALL(&AESLIGHT1_FIREWALL);
      PPRINT_FIREWALL(&AESLIGHT2_FIREWALL);
      PPRINT_FIREWALL(&AESLIGHT3_FIREWALL);
      PPRINT_FIREWALL(&AIPS0_FIREWALL);
      PPRINT_FIREWALL(&AIPS1_FIREWALL);
      PPRINT_FIREWALL(&AIPS2_FIREWALL);
      PPRINT_FIREWALL(&AIPS3_FIREWALL);
      PPRINT_FIREWALL(&AIPS4_FIREWALL);
      PPRINT_FIREWALL(&DSPH_FIREWALL);
      PPRINT_FIREWALL(&GTM_FIREWALL);
      PPRINT_FIREWALL(&HSM_FIREWALL);
      PPRINT_FIREWALL(&NVM_FIREWALL);
      PPRINT_FIREWALL(&DAP_FIREWALL);
      PPRINT_FIREWALL(&DFA_FIREWALL);
      PPRINT_FIREWALL(&DME_FIREWALL);
      PPRINT_FIREWALL(&OCT_SPI_FIREWALL);
      PPRINT_FIREWALL(&TMC0_FIREWALL);
      PPRINT_FIREWALL(&TMC1_FIREWALL);
      PPRINT_FIREWALL(&TMC2_FIREWALL);
    
      // Function can be called by both cores, but will have no effect on Core 1 for Stellar
      TRBSYS_setCoreID(1);
      RBSYS_EnhancedGuardInit();
    }

    /**
      * \TestCaseName TRBSYS_GuardConfig_InvalidSettingAssert
      *
      * \Reference
      * RBSYS_PRC_FSW_FinalGuard_Init
      *
      * \Purpose Dummy unittest for empty function RBSYS_PRC_FSW_FinalGuard_Init for uCFamily Stellar
      *
      * \Sequence
      *  Call RBSYS_PRC_FSW_FinalGuard_Init from both cores
      *
      * \ExpectedResult
      * None
      */
    SWTEST void TRBSYS_GuardConfig_InvalidSettingAssert(void)
    {
      SWT_AssertCheckStart("rbsys_NOCFirewallConfigure", "0");
      TRBSYS_GuardConfig_InvalidRegionTypeConfiguration();
      SWT_AssertCheckEnd();
    }

    /**
      * \TestCaseName TRBSYS_GuardConfig_FinalGuardInit
      *
      * \Reference
      * RBSYS_PRC_FSW_FinalGuard_Init
      *
      * \Purpose Dummy unittest for empty function RBSYS_PRC_FSW_FinalGuard_Init for uCFamily Stellar
      *
      * \Sequence
      *  Call RBSYS_PRC_FSW_FinalGuard_Init from both cores
      *
      * \ExpectedResult
      * None
      */
    SWTEST void TRBSYS_GuardConfig_FinalGuardInit(void)
    {
      // empty for Stellar, because Guards cannot be locked and are already configured by RBSYS_EnhancedGuardInit
      RBSYS_PRC_FSW_FinalGuard_Init();

      TRBSYS_setCoreID(1);
      RBSYS_PRC_FSW_FinalGuard_Init();

      SWT_Eval(TRUE);
    }
    

    /**
      * \TestCaseName TRBSYS_GuardConfig_ReadFailure
      *
      * \Reference
      * RBSYS_GetSystemMpuFailure, RBSYS_GenerateSystemMpuFailureDebugData, RBSYS_ClearAllFirewallStatusRegisters
      *
      * \Purpose Unittests for Guard Info APIs @ Stellar
      *
      * \Sequence
      *  see implementation
      *
      * \ExpectedResult
      * None
      */
    SWTEST void TRBSYS_GuardInfo_ReadFailure(void)
    {
      RBSYS_SystemMPU_AccessViolation_t violation;
      uint32 debug0, debug1;

      /* Case 0: EL1 Failure is detected correctly as Firewall Error */
      /* EL1 failure */
      KITE1_FIREWALL.FW_EL1_ERROR_TYPE_STATUS = (0x20);          // Multi Region Error
      KITE1_FIREWALL.FW_EL1_ERROR_ID_STATUS   = ((4<<9)|(0<<0)); // MID = 4, VMID = 0
      KITE1_FIREWALL.FW_EL1_ERROR_ADDR_STATUS = 0xABCDEF12;      // 32bit-address

      SWT_EvalEqX( RBSYS_SystemMPU_FailureType_FirewallError, RBSYS_GetSystemMpuFailure(16, RBSYS_SystemMPUPrivilegeLevel_EL01, &violation) );
      RBSYS_GenerateSystemMpuFailureDebugData(&violation, &debug0, &debug1);
      SWT_EvalEqX( debug0, ((4<<24) | (0<<12) | (0x20<<0)) );
      SWT_EvalEqX( debug1, (0xABCDEF12) );

      /* Case 1: EL2 Failure is detected correctly as Firewall Error */
      /* EL2 failure */
      KITE2_FIREWALL.FW_EL2_ERROR_TYPE_STATUS = (0x1);            // Partition Error
      KITE2_FIREWALL.FW_EL2_ERROR_ID_STATUS   = ((0xA<<9)|(0<<0)); // MID = 10, VMID = 0
      KITE2_FIREWALL.FW_EL2_ERROR_ADDR_STATUS = 0x12345678;        // 32bit-address

      SWT_EvalEqX( RBSYS_SystemMPU_FailureType_FirewallError, RBSYS_GetSystemMpuFailure(17, RBSYS_SystemMPUPrivilegeLevel_EL2, &violation) );
      RBSYS_GenerateSystemMpuFailureDebugData(&violation, &debug0, &debug1);
      SWT_EvalEqX( debug0, ((0xA<<24) | (0<<12) | (1<<0)));
      SWT_EvalEqX( debug1, (0x12345678) );
      
      /* Case 2: Firewall Index does not exist */
      SWT_EvalEqX( RBSYS_SystemMPU_FailureType_APIMisuse, RBSYS_GetSystemMpuFailure(32, RBSYS_SystemMPUPrivilegeLevel_EL01, &violation) );


      /* Case 3: Firewall Index does exist but has no firewall associated */
      SWT_EvalEqX( RBSYS_SystemMPU_FailureType_APIMisuse, RBSYS_GetSystemMpuFailure(21, RBSYS_SystemMPUPrivilegeLevel_EL01, &violation) );


      /* Case 4: Firewall exist but has no active failure with EL0/1 category */
      SWT_EvalEqX( RBSYS_SystemMPU_FailureType_Undefined, RBSYS_GetSystemMpuFailure(17, RBSYS_SystemMPUPrivilegeLevel_EL01, &violation) );


      /* Case 5: Firewall exist but has no active failure with EL2 category */
      SWT_EvalEqX( RBSYS_SystemMPU_FailureType_Undefined, RBSYS_GetSystemMpuFailure(16, RBSYS_SystemMPUPrivilegeLevel_EL2, &violation) );


      // /* Case 6: Function is called with wrong EL category */
      // SWT_AssertCheckStart("RBSYS_GetSystemMpuFailure", "0");
      SWT_EvalEqX( RBSYS_SystemMPU_FailureType_Undefined, RBSYS_GetSystemMpuFailure(16, RBSYS_SystemMPUPrivilegeLevel_EL2+1, &violation) );
      // SWT_AssertCheckEnd();
      // Sanity check is not done anymore to lower the amount of code executed in HV mode

      /* Case 7: Clear all Faults in all Firewalls */
      RBSYS_ClearAllFirewallStatusRegisters();

      SWT_EvalEqX( AESLIGHT0_FIREWALL.FW_ERROR_STATUS, 1 );
      SWT_EvalEqX( AESLIGHT1_FIREWALL.FW_ERROR_STATUS, 1 );
      SWT_EvalEqX( AESLIGHT2_FIREWALL.FW_ERROR_STATUS, 1 );
      SWT_EvalEqX( AESLIGHT3_FIREWALL.FW_ERROR_STATUS, 1 );
      SWT_EvalEqX( AIPS0_FIREWALL.FW_ERROR_STATUS,     1 );
      SWT_EvalEqX( AIPS1_FIREWALL.FW_ERROR_STATUS,     1 );
      SWT_EvalEqX( AIPS2_FIREWALL.FW_ERROR_STATUS,     1 );
      SWT_EvalEqX( AIPS3_FIREWALL.FW_ERROR_STATUS,     1 );
      SWT_EvalEqX( AIPS4_FIREWALL.FW_ERROR_STATUS,     1 );
      SWT_EvalEqX( DAP_FIREWALL.FW_ERROR_STATUS,       1 );
      SWT_EvalEqX( DFA_FIREWALL.FW_ERROR_STATUS,       1 );
      SWT_EvalEqX( DME_FIREWALL.FW_ERROR_STATUS,       1 );
      SWT_EvalEqX( DSPH_FIREWALL.FW_ERROR_STATUS,      1 );
      SWT_EvalEqX( GTM_FIREWALL.FW_ERROR_STATUS,       1 );
      SWT_EvalEqX( HSM_FIREWALL.FW_ERROR_STATUS,       1 );
      SWT_EvalEqX( KITE0_FIREWALL.FW_ERROR_STATUS,     1 );
      SWT_EvalEqX( KITE1_FIREWALL.FW_ERROR_STATUS,     1 );
      SWT_EvalEqX( KITE2_FIREWALL.FW_ERROR_STATUS,     1 );
      SWT_EvalEqX( NVM_FIREWALL.FW_ERROR_STATUS,       1 );
      SWT_EvalEqX( OCT_SPI_FIREWALL.FW_ERROR_STATUS,   1 );
      SWT_EvalEqX( SYSRAM0_FIREWALL.FW_ERROR_STATUS,   1 );
      SWT_EvalEqX( SYSRAM1_FIREWALL.FW_ERROR_STATUS,   1 );
      SWT_EvalEqX( TMC0_FIREWALL.FW_ERROR_STATUS,      1 );
      SWT_EvalEqX( TMC1_FIREWALL.FW_ERROR_STATUS,      1 );
      SWT_EvalEqX( TMC2_FIREWALL.FW_ERROR_STATUS,      1 );
    }


    
    
    
    /**
      * \TestCaseName TRBSYS_GuardConfig_FeatureNotSupported
      *
      * \Reference
      * Dummy
      *
      *
      * \Purpose Testcase to check if Sanitychecks for functions under development are effective
      *
      * \Sequence
      *
      *
      * \ExpectedResult
      *
      */
    SWTEST void TRBSYS_GuardConfig_CheckIfNonSupportedFunctionsAreNotCalled(void)
    {
      SWT_AssertCheckStart("RBSYS_PRC_FSW_VerifyFinalGuardSettings", "0");
      RBSYS_PRC_FSW_VerifyFinalGuardSettings();
      SWT_AssertCheckEnd();
    }
  #else
    /**
      * \TestCaseName TRBSYS_GuardConfig_FeatureNotSupported
      *
      * \Reference
      * Dummy
      *
      *
      * \Purpose Testcase to check if Sanitychecks for functions under development are effective
      *
      * \Sequence
      *
      *
      * \ExpectedResult
      *
      */
    SWTEST void TRBSYS_GuardConfig_FeatureNotSupported(void)
    {
      SWT_Eval(1);
    }
  #endif

#endif // (RBFS_uCFamily != RBFS_uCFamily_STMStellar)