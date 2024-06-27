#include "SwTest_Global.h"
#include "Dem.h"
#include "RBDSM_SWT_Node.h"

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_MMP_SignalChain
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_MMP_SignalChain(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_RBL_Nvm_SigChain_Content
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_SignalChain, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_MMP_SignalChain
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_MMP_SignalChain(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_MMP_SyncError
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_SignalChain, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_MMP_SignalChainMonitors
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_MMP_SignalChainMonitors(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_RBL_FrequencyFailure_Smu0,
        DemConf_DemEventParameter_RBL_FrequencyFailure_Smu1,
        DemConf_DemEventParameter_RBL_FrequencyFailure_Smu2,
        DemConf_DemEventParameter_RBL_AmbientTemperatureFault
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_SignalChainMonitors, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_MMP_SignalChainMonitors
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_MMP_SignalChainMonitors(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_MMP_Nvm_SigChnMonContents
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_SignalChainMonitors, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_MMP_TracebilityData
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_MMP_TracebilityData(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_RBL_Nvm_ProcProgsId,
        DemConf_DemEventParameter_RBL_Nvm_SnsrSerlNr,
        DemConf_DemEventParameter_RBL_Nvm_RbPartNr,
        DemConf_DemEventParameter_RBL_Nvm_RbAsblyPartNr,
        DemConf_DemEventParameter_RBL_Nvm_ProdDate,
        DemConf_DemEventParameter_RBL_Nvm_PlaIdNr,
        DemConf_DemEventParameter_RBL_Nvm_PcbDmc,
        DemConf_DemEventParameter_RBL_Nvm_HwVersNr,
        #if (RBFS_Customer == RBFS_Customer_GM)
          DemConf_DemEventParameter_RBL_Nvm_GmPartNrDls,
        #endif
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_TracebilityData, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_MMP_TracebilityData
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_MMP_TracebilityData(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        DemConf_DemComponent_Ecu
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_TracebilityData, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_Det
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_Det(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_DET_ReportError
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_Det, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_Det
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_Det(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        DemConf_DemComponent_Ecu
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_Det, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_MMP_SensorModuleError
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_MMP_SensorModuleError(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_RBL_ChannelInvalid_Smu0_Acc1,
        DemConf_DemEventParameter_RBL_ChannelInvalid_Smu0_Acc2,
        DemConf_DemEventParameter_RBL_ChannelInvalid_Smu0_Acc3,
        DemConf_DemEventParameter_RBL_ChannelInvalid_Smu0_Rate1,
        DemConf_DemEventParameter_RBL_ChannelInvalid_Smu1_Acc1,
        DemConf_DemEventParameter_RBL_ChannelInvalid_Smu1_Acc2,
        DemConf_DemEventParameter_RBL_ChannelInvalid_Smu1_Acc3,
        DemConf_DemEventParameter_RBL_ChannelInvalid_Smu1_Rate1,
        DemConf_DemEventParameter_RBL_ChannelInvalid_Smu2_Acc1,
        DemConf_DemEventParameter_RBL_ChannelInvalid_Smu2_Acc2,
        DemConf_DemEventParameter_RBL_ChannelInvalid_Smu2_Acc3,
        DemConf_DemEventParameter_RBL_ChannelInvalid_Smu2_Rate1,
        DemConf_DemEventParameter_RBL_MechOverload_Smu0_Acc1,
        DemConf_DemEventParameter_RBL_MechOverload_Smu0_Acc2,
        DemConf_DemEventParameter_RBL_MechOverload_Smu0_Acc3 ,
        DemConf_DemEventParameter_RBL_MechOverload_Smu0_Rate1 ,
        DemConf_DemEventParameter_RBL_MechOverload_Smu1_Acc1,
        DemConf_DemEventParameter_RBL_MechOverload_Smu1_Acc2,
        DemConf_DemEventParameter_RBL_MechOverload_Smu1_Acc3,
        DemConf_DemEventParameter_RBL_MechOverload_Smu1_Rate1,
        DemConf_DemEventParameter_RBL_MechOverload_Smu2_Acc1,
        DemConf_DemEventParameter_RBL_MechOverload_Smu2_Acc2,
        DemConf_DemEventParameter_RBL_MechOverload_Smu2_Acc3,
        DemConf_DemEventParameter_RBL_MechOverload_Smu2_Rate1,
        DemConf_DemEventParameter_RBL_TemperatureRangeExceeded_Smu0,
        DemConf_DemEventParameter_RBL_TemperatureRangeExceeded_Smu1,
        DemConf_DemEventParameter_RBL_TemperatureRangeExceeded_Smu2
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_SensorModuleError, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_MMP_SensorModuleError
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_MMP_SensorModuleError(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_MMP_CommunicationFailure
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_SensorModuleError, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

#if(RBFS_DynamicCanId == RBFS_DynamicCanId_ON)
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_MMP2_NetConfig
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_MMP2_NetConfig(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_RBL_NET_DynamicCanId
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP2_NetConfig, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_MMP2_NetConfig
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_MMP2_NetConfig(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        DemConf_DemComponent_Ecu
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP2_NetConfig, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

#endif

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_Security
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_Security(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_SEC_SecureBlockCheckFailed,
            DemConf_DemEventParameter_SEC_AuthBlockCheckFailed,
            DemConf_DemEventParameter_SEC_RtmdCheckFailed,
            DemConf_DemEventParameter_SEC_RbSecBaseInternalErrorState,
            DemConf_DemEventParameter_SEC_RbSecAccInternalErrorState,
            DemConf_DemEventParameter_SEC_LifecyclePrivileged
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_Security, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_Ecu
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_Security(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        DemConf_DemComponent_Ecu
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_Security, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_Ecu
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_Ecu(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_AssertionFailed,
        DemConf_DemEventParameter_RB_UnsupportedHW,
        DemConf_DemEventParameter_RBSupplyASICInitFailure,
		#if(RBFS_SUPPLYBASEU5VConfigCS990 != RBFS_SUPPLYBASEU5VConfigCS990_NotUsed && RBFS_SUPPLYBASEU5VConfigCS990 != RBFS_SUPPLYBASEU5VConfigCS990_NA)
        DemConf_DemEventParameter_RBSUPPLY_U5VTestFailure,
        DemConf_DemEventParameter_RBSUPPLY_U5VOutOfRange,
		#endif
        DemConf_DemEventParameter_RbfslEcuEClockTestFails,
        DemConf_DemEventParameter_RbfslEcuWrongBistCmdTestFails,
        DemConf_DemEventParameter_RbfslEcuFastWdTestFails,
        DemConf_DemEventParameter_RbfslEcuBistFailureCtrTestFails,
        DemConf_DemEventParameter_RbfslEcuErrpinCounterTestFails,
        DemConf_DemEventParameter_RbfslEcuEnableElLowFails,
        DemConf_DemEventParameter_RbfslDecoupleBitTestFails,
        DemConf_DemEventParameter_RbfslEcuEnableElHighFails,
        DemConf_DemEventParameter_RbfslEcuWdStartuptestFails,
        DemConf_DemEventParameter_RbfslEcuWdStatusContinuousError,
        DemConf_DemEventParameter_RbfslEcuEnContinuousError,
        DemConf_DemEventParameter_RbmicAsicClkInError,
        DemConf_DemEventParameter_RbmicAsicInitTestError,
        DemConf_DemEventParameter_RbmicSpiTransferError,
        DemConf_DemEventParameter_RbWdhAsicWdErrorCntStuck,
        DemConf_DemEventParameter_RbWdhAsicWdErrorCntLimit,
        DemConf_DemEventParameter_RbWdhAsicWdCmdMissing,
        DemConf_DemEventParameter_RbWdhTaskMonConCnt,
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_Ecu, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_Ecu
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_Ecu(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        DemConf_DemComponent_uC
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_Ecu, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_Network
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_Network(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_RBNET_Undervoltage,
        DemConf_DemEventParameter_RBNET_Overvoltage
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_Network, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_Network
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_Network(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        DemConf_DemComponent_Ecu
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_Network, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_NetworkCAN
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_NetworkCAN(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_CAN_E_TIMEOUT
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_NetworkCAN, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_NetworkCAN
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_NetworkCAN(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        DemConf_DemComponent_Network
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_NetworkCAN, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_NetworkCAN0
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_NetworkCAN0(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_CANSM_E_BUSOFF_NETWORK_0
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_NetworkCAN0, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_NetworkCAN0
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_NetworkCAN0(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        DemConf_DemComponent_NetworkCAN
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_NetworkCAN0, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}


#if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_NetworkCAN1
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_NetworkCAN1(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_CANSM_E_BUSOFF_NETWORK_1,
        DemConf_DemEventParameter_CANTRCV_TJA_E_NO_TRCV_CONTROL_CH0

    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_NetworkCAN1, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_NetworkCAN1
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_NetworkCAN1(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        DemConf_DemComponent_NetworkCAN
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_NetworkCAN1, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

#endif

#if(RBFS_ThirdCanSupport == RBFS_ThirdCanSupport_Yes)

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_NetworkCAN2
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_NetworkCAN2(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_CANSM_E_BUSOFF_NETWORK_2,
        DemConf_DemEventParameter_CANTRCV_TJA_E_NO_TRCV_CONTROL_CH1

    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_NetworkCAN2, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_NetworkCAN2
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_NetworkCAN2(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        DemConf_DemComponent_NetworkCAN
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_NetworkCAN2, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

#endif

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_SMM_DegradeSystem
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_SMM_DegradeSystem(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_SMM_OneRequestsInit
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_SMM_DegradeSystem, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_SMM_DegradeSystem
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_SMM_DegradeSystem(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        DemConf_DemComponent_Ecu
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_SMM_DegradeSystem, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_uCMemoryGuard
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_uCMemoryGuard(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_RBuCSafetyNotificationGRAM,
        DemConf_DemEventParameter_RBuCSafetyNotification
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_uCMemoryGuard, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_uCMemoryGuard
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_uCMemoryGuard(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        DemConf_DemComponent_uC
    };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_uCMemoryGuard, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_uC
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_uC(void)
{
    Dem_EventIdType FwNodeMap[] = {
        DemConf_DemEventParameter_RBuCSupplyError,
        DemConf_DemEventParameter_RBHWBISTError,
        DemConf_DemEventParameter_RBRAMFailure,
        DemConf_DemEventParameter_RBFlashFailure,
        DemConf_DemEventParameter_RBuCSafetyFault,
        DemConf_DemEventParameter_RBuCSafetyLogicFault,
        DemConf_DemEventParameter_RBCPUException,
        DemConf_DemEventParameter_RBSYS_StackOverUnderFlow,
        DemConf_DemEventParameter_RBSYS_SYSErrorHook,
        DemConf_DemEventParameter_RBSYS_OSErrorHook,
        DemConf_DemEventParameter_RBSYS_TaskOverRun,
        DemConf_DemEventParameter_RBOSTaskSchemeError,
        DemConf_DemEventParameter_RBSYS_TaskJitter,
        DemConf_DemEventParameter_RBDmaTransferError,
        DemConf_DemEventParameter_RbmicAsicOscillatorError,
        DemConf_DemEventParameter_RBuCRegisterFault,
        DemConf_DemEventParameter_RB_UnsupportedSeriesHW
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_uC, &FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}


#if (RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_SSA
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_SSA(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_SSA_Event_DTC_9a6857,
            DemConf_DemEventParameter_SSA_Event_DTC_D12081,
            DemConf_DemEventParameter_SSA_Event_DTC_D12083,
            DemConf_DemEventParameter_SSA_Event_DTC_D12087
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_SSA,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_SSA
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_SSA(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_Ecu
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_SSA, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

#endif

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_CommunicationFailure
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_CommunicationFailure(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_CommunicationFailure_Smu0,
            DemConf_DemEventParameter_RBL_CommunicationFailure_Smu1,
            DemConf_DemEventParameter_RBL_CommunicationFailure_Smu2
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_CommunicationFailure,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_CommunicationFailure
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_CommunicationFailure(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_MMP_ReInitError
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_CommunicationFailure, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_NvMFreqContent
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_NvMFreqContent(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_Nvm_RefFreq_Content,
            #if (RBFS_AmbientTempMon != RBFS_AmbientTempMon_AmbTMonOff)
            DemConf_DemEventParameter_RBL_Nvm_AmbTempMon_Content
            #endif
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_Nvm_SigChnMonContents,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_Nvm_SigChnMonContents
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_Nvm_SigChnMonContents(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_MMP_ReInitError
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_Nvm_SigChnMonContents, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_SyncError
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_SyncError(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_SyncOnSmu_Timeout
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_SyncError,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_SyncError
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_SyncError(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_Ecu
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_SyncError, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}


#if(RBFS_DiagBase != RBFS_DiagBase_DiagxRBxPlant)

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_StbM
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_StbM(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_STBM_NO_INIT_SYNC_TIMEOUT,
            DemConf_DemEventParameter_RBL_STBM_SYNC_LOST_TIMEOUT,
            DemConf_DemEventParameter_RBL_CUSTIF_STBM_TIMELEAP
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_StbM,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

#if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_StbM
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_StbM(void)
{
    Dem_ComponentIdType ParentNodes[] = {

        #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
            DemConf_DemComponent_NetworkCAN1
        #endif
        #if (RBFS_MMP2 == RBFS_MMP2_IMUB)
            DemConf_DemComponent_NetworkCAN0
        #endif

       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_StbM, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

#endif

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_GTS_Cloning
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_GTS_Cloning(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_STBM_TIME_COPY,
            DemConf_DemEventParameter_RBL_STBM_RATE_COPY
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_GTS_Cloning,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_GTS_Cloning
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_GTS_Cloning(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_MMP_StbM
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_GTS_Cloning, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_Ign_Stat_ST3
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_Ign_Stat_ST3(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_CUSTIF_TIMEOUT_Ign_Stat_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SAFETY_Ign_Stat_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SQC_Ign_Stat_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_Ign_Stat_ST3
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_Ign_Stat_ST3,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

#if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_Ign_Stat_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_Ign_Stat_ST3(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
            DemConf_DemComponent_NetworkCAN1
        #endif
        #if (RBFS_MMP2 == RBFS_MMP2_IMUB)
            DemConf_DemComponent_NetworkCAN0
        #endif
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_Ign_Stat_ST3, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}
#endif

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_PN14_Master_Stat1_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_PN14_Master_Stat1_ST3(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_CUSTIF_TIMEOUT_PN14_Master_Stat1_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_PN14_Master_Stat1_ST3
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_PN14_Master_Stat1_ST3,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

#if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_PN14_Master_Stat1_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_PN14_Master_Stat1_ST3(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
            DemConf_DemComponent_NetworkCAN1
        #endif
        #if (RBFS_MMP2 == RBFS_MMP2_IMUB)
            DemConf_DemComponent_NetworkCAN0
        #endif
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_PN14_Master_Stat1_ST3, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}
#endif
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_PT4_PTCoor4_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_PT4_PTCoor4_ST3(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_CUSTIF_TIMEOUT_PT4_PTCoor4_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SAFETY_PT4_PTCoor4_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SQC_PT4_PTCoor4_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_PT4_PTCoor4_ST3
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_PT4_PTCoor4_ST3,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

#if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_PT4_PTCoor4_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_PT4_PTCoor4_ST3(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
            DemConf_DemComponent_NetworkCAN1
        #endif
        #if (RBFS_MMP2 == RBFS_MMP2_IMUB)
            DemConf_DemComponent_NetworkCAN0
        #endif
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_PT4_PTCoor4_ST3, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}
#endif
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_DIAG_Stat_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_DIAG_Stat_ST3(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_CUSTIF_TIMEOUT_DIAG_Stat_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_DIAG_Stat_ST3
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_DIAG_Stat_ST3,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

#if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_DIAG_Stat_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_DIAG_Stat_ST3(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
            DemConf_DemComponent_NetworkCAN1
        #endif
        #if (RBFS_MMP2 == RBFS_MMP2_IMUB)
            DemConf_DemComponent_NetworkCAN0
        #endif
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_DIAG_Stat_ST3, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}
#endif

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_BCS_Whl_Msg1_BTC_ST3
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_BCS_Whl_Msg1_BTC_ST3(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_CUSTIF_TIMEOUT_BCS_Whl_Msg1_BTC_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SAFETY_BCS_Whl_Msg1_BTC_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SQC_BCS_Whl_Msg1_BTC_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_BCS_Whl_Msg1_BTC_ST3
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_BCS_Whl_Msg1_BTC_ST3,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

#if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_BCS_Whl_Msg1_BTC_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_BCS_Whl_Msg1_BTC_ST3(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
            DemConf_DemComponent_NetworkCAN1
        #endif
        #if (RBFS_MMP2 == RBFS_MMP2_IMUB)
            DemConf_DemComponent_NetworkCAN0
        #endif
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_BCS_Whl_Msg1_BTC_ST3, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}
#endif
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_FBL_Cfg_Star3_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_FBL_Cfg_Star3_ST3(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_CUSTIF_TIMEOUT_FBL_Cfg_Star3_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_FBL_Cfg_Star3_ST3
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_FBL_Cfg_Star3_ST3,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

#if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_FBL_Cfg_Star3_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_FBL_Cfg_Star3_ST3(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
            DemConf_DemComponent_NetworkCAN1
        #endif
        #if (RBFS_MMP2 == RBFS_MMP2_IMUB)
            DemConf_DemComponent_NetworkCAN0
        #endif
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_FBL_Cfg_Star3_ST3, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}
#endif

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_DI_OdoSpeedometer_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_DI_OdoSpeedometer_ST3(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_CUSTIF_TIMEOUT_DI_OdoSpeedometer_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SAFETY_DI_OdoSpeedometer_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SQC_DI_OdoSpeedometer_ST3
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_DI_OdoSpeedometer_ST3,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

#if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_DI_OdoSpeedometer_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_DI_OdoSpeedometer_ST3(void)
{
    Dem_ComponentIdType ParentNodes[] = {
        #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
            DemConf_DemComponent_NetworkCAN1
        #endif
        #if (RBFS_MMP2 == RBFS_MMP2_IMUB)
            DemConf_DemComponent_NetworkCAN0
        #endif
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_DI_OdoSpeedometer_ST3, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}
#endif

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3
 *
 */
#if (RBFS_MMP2 == RBFS_MMP2_IMUA)
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_CUSTIF_SAFETY_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SQC_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_TIMEOUT_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_NetworkCAN1
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}
#endif

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_HAD_Stat_IDC_M_FSI_Pr5_ST3
 *
 */
#if (RBFS_MMP2 == RBFS_MMP2_IMUB)
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_HAD_Stat_IDC_M_FSI_Pr5_ST3(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_CUSTIF_SAFETY_HAD_Stat_IDC_M_FSI_Pr5_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SQC_HAD_Stat_IDC_M_FSI_Pr5_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_TIMEOUT_HAD_Stat_IDC_M_FSI_Pr5_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_HAD_Stat_IDC_M_FSI_Pr5_ST3
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_HAD_Stat_IDC_M_FSI_Pr5_ST3,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_HAD_Stat_IDC_M_FSI_Pr5_ST3
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_HAD_Stat_IDC_M_FSI_Pr5_ST3(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_NetworkCAN0
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_HAD_Stat_IDC_M_FSI_Pr5_ST3, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}
#endif


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_DI_OdoSpeedometer_Signal
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_DI_OdoSpeedometer_Signal(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_DI_OdoSpeedometer_ST3,
            DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_VEHSPD_DISP_ST3
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_DI_OdoSpeedometer_Signal,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_DI_OdoSpeedometer_Signal
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_DI_OdoSpeedometer_Signal(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_MMP_DI_OdoSpeedometer_ST3
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_DI_OdoSpeedometer_Signal, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

#endif
/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_ReInitError
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_ReInitError(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_ReInitOccured_Smu0,
            DemConf_DemEventParameter_RBL_ReInitOccured_Smu1,
            DemConf_DemEventParameter_RBL_ReInitOccured_Smu2
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_ReInitError,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_ReInitError
 *
 */

SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_ReInitError(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_MMP_SyncError
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_ReInitError, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_TPSW
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_TPSW(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBL_SwcDiag_MemoryViolation
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_TPSW,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_TPSW
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_TPSW(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_Ecu
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_TPSW, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}


/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_FWMapping_Variant_Coding
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_Variant_Coding(void)
{
    Dem_EventIdType FwNodeMap[] = {
#if (RBFS_MMP2 == RBFS_MMP2_IMUB)
            DemConf_DemEventParameter_RBL_NVM_Variant_handler,
#endif
            DemConf_DemEventParameter_SSA_Event_DTC_164456

    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_Variant_Coding,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_Variant_Coding
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_Variant_Coding(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_Ecu
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_Variant_Coding, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

SWTEST void RBDSM_SWT_PRJ_Node_FWMapping_NoDTC(void)
{
    Dem_EventIdType FwNodeMap[] = {
            DemConf_DemEventParameter_RBSUPPLYIREFOutOfRange,
            DemConf_DemEventParameter_RBChargePumpFailure,
            DemConf_DemEventParameter_RBEcuBandgap,
            DemConf_DemEventParameter_RBAdcPinTest,
            DemConf_DemEventParameter_RBAdcSelftestC5P,
            DemConf_DemEventParameter_RBAdcPeripheralFault,
            DemConf_DemEventParameter_RBMICSYS_OC_AsicMalfunction,
            DemConf_DemEventParameter_RBNvM_WriteCycleExceed,
            DemConf_DemEventParameter_RBChargePumpUndervoltage
    };
    Nodes_SWT_FWMapping_SimTest(DemConf_DemComponent_MMP_NoDTC,&FwNodeMap[0], (sizeof(FwNodeMap)/sizeof(Dem_EventIdType)));
}

/** @testlists  RBDSM_SWT_PRJ_Node
 *
 * TESTNAME     : RBDSM_SWT_PRJ_Node_ParentNode_Variant_Coding
 *
 */
SWTEST void RBDSM_SWT_PRJ_Node_ParentNode_NoDTC(void)
{
    Dem_ComponentIdType ParentNodes[] = {
            DemConf_DemComponent_Ecu
       };
    Nodes_SWT_NodeParentCheck_SimTest(DemConf_DemComponent_MMP_NoDTC, &ParentNodes[0], (sizeof(ParentNodes)/sizeof(Dem_ComponentIdType)));
}

