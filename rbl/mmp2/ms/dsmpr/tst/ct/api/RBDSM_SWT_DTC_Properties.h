#ifndef RBDSM_SWT_DTC_PROPERTIES_H_
#define RBDSM_SWT_DTC_PROPERTIES_H_

#include "Std_Types.h"

typedef struct  {
   uint32 DTC_ID;
   boolean curable;
}Map_DTC_properties;

#if (RBFS_MMP2 == RBFS_MMP2_IMUA) // with DualCan support On

#define NUMBER_OF_EVENTS 153


const Map_DTC_properties EventID[NUMBER_OF_EVENTS]= {{0x000000,0}, // dummy event
                                                     {0x452049,0}, // RBuCSupplyError
                                                     {0x452049,0}, // RBHWBISTError
                                                     {0x452044,0}, // RBRAMFailure
                                                     {0x452045,0}, // RBFlashFailure
                                                     {0x452049,0}, // RBuCSafetyFault
                                                     {0x452049,0}, // RBuCSafetyLogicFault
                                                     {0x452049,0}, // RBCPUException
                                                     {0x452049,0}, // RBSYS_StackOverUnderFlow
                                                     {0x452049,0}, // RBSYS_SYSErrorHook
                                                     {0x452049,0}, // RBSYS_OSErrorHook
                                                     {0x452049,0}, // RBSYS_TaskOverRun
                                                     {0x452049,0}, // RBOSTaskSchemeError
                                                     {0x452049,0}, // RBSYS_TaskJitter
                                                     {0x452049,0}, // RBDmaTransferError
                                                     {0x452049,0}, // RbmicAsicOscillatorError
                                                     {0x452042,0}, // RBuCRegisterFault
                                                     {0x452056,0}, // RB_UnsupportedSeriesHW
                                                     {0x452004,0}, // AssertionFailed
                                                     {0x452056,0}, // RB_UnsupportedHW
                                                     {0x452096,0}, // RBSupplyASICInitFailure
                                                     #if(RBFS_SUPPLYBASEU5VConfigCS990 != RBFS_SUPPLYBASEU5VConfigCS990_NotUsed && RBFS_SUPPLYBASEU5VConfigCS990 != RBFS_SUPPLYBASEU5VConfigCS990_NA)
                                                     {0x452096,0}, // RBSUPPLY_U5VTestFailure
                                                     {0x45201C,0}, // RBSUPPLY_U5VOutOfRange
                                                     #endif
                                                     {0x452047,0}, // RbfslEcuEClockTestFails
                                                     {0x452047,0}, // RbfslEcuWrongBistCmdTestFails
                                                     {0x452047,0}, // RbfslEcuFastWdTestFails
                                                     {0x452047,0}, // RbfslEcuBistFailureCtrTestFails
                                                     {0x452047,0}, // RbfslEcuErrpinCounterTestFails
                                                     {0x452047,0}, // RbfslEcuEnableElLowFails
                                                     {0x452047,0}, // RbfslDecoupleBitTestFails
                                                     {0x452047,0}, // RbfslEcuEnableElHighFails
                                                     {0x452047,0}, // RbfslEcuWdStartuptestFails
                                                     {0x452047,0}, // RbfslEcuEnContinuousError
                                                     {0x452047,0}, // RbfslEcuWdStatusContinuousError
                                                     {0x452064,0}, // RbmicAsicClkInError
                                                     {0x452064,0}, // RbmicAsicInitTestError
                                                     {0x452064,0}, // RbmicSpiTransferError
                                                     {0x452047,0}, // RbWdhAsicWdErrorCntStuck
                                                     {0x452047,0}, // RbWdhAsicWdErrorCntLimit
                                                     {0x452047,0}, // RbWdhAsicWdCmdMissing
                                                     #if(RBFS_MCORE == RBFS_MCORE_ON)
                                                     {0x452047,0}, // RbWdhSwBistConCnt
                                                     #endif
                                                     {0x452047,0}, // RbWdhTaskMonConCnt
                                                     {0x452046,0}, // RBuCSafetyNotificationGRAM
                                                     {0x452046,0}, // RBuCSafetyNotification
                                                     {0x000000,0}, // DET_ReportError
                                                     {0x000000,0}, // RBSUPPLYIREFOutOfRange
                                                     {0x000000,0}, // RBChargePumpFailure
                                                     {0x000000,0}, // RBEcuBandgap
                                                     {0x000000,0}, // RBAdcPinTest
                                                     {0x000000,0}, // RBAdcSelftestC5P
                                                     {0x000000,0}, // RBAdcPeripheralFault
                                                     {0x000000,0}, // RBMICSYS_OC_AsicMalfunction
                                                     {0x000000,0}, // RBNvM_WriteCycleExceed
                                                     {0x000000,1}, // RBChargePumpUndervoltage
                                                     #if(RBFS_DynamicCanId == RBFS_DynamicCanId_ON)
                                                     {0x000000,0}, // RBL_NET_DynamicCanId
                                                     #endif
                                                     {0x451C04,0}, //RBL_SyncOnSmu_Timeout
                                                     {0x452048,0}, //RBL_SwcDiag_MemoryViolation
                                                     {0x451D56,0}, // RBL_Nvm_HwVersNr
                                                     {0x451D56,0}, // RBL_Nvm_PcbDmc
                                                     {0x451D56,0}, // RBL_Nvm_PlaIdNr
                                                     {0x451D56,0}, // RBL_Nvm_ProcProgsId
                                                     {0x451D56,0}, // RBL_Nvm_ProdDate
                                                     {0x451D56,0}, // RBL_Nvm_RbAsblyPartNr
                                                     {0x451D56,0}, // RBL_Nvm_RbPartNr
                                                     {0x451D56,0}, // RBL_Nvm_SnsrSerlNr
                                                     #if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
                                                     {0x164456,0}, // SSA_DTC_1644564
                                                     #endif
                                                     {0xD1C316,1}, // RBNET_Undervoltage
                                                     {0xD1C417,1}, // RBNET_Overvoltage
                                                     {0x000000,1}, // SMM_OneRequestsInit
                                                     #if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
                                                     {0x9A6857,1}, //SSA_Event_DTC_9a6857
                                                     {0xD12081,1}, //SSA_Event_DTC_D12081
                                                     {0xD12083,1}, //SSA_Event_DTC_D12083
                                                     {0xD12087,1}, //SSA_Event_DTC_D12087
                                                     #endif
                                                     #if (RBFS_BUILDTYPE != RBFS_BUILDTYPE_RELEASE)
                                                     {0x000000,0}, //SEC_SecureBlockCheckFailed
                                                     {0x000000,0}, //SEC_AuthBlockCheckFailed
                                                     {0x000000,0}, //SEC_RtmdCheckFailed
                                                     {0x000000,0}, //SEC_RbSecBaseInternalErrorState
                                                     {0x000000,0}, //SEC_RbSecAccInternalErrorState
                                                     #endif
                                                     {0x000000,1}, //SEC_LifecyclePrivileged
                                                     {0x451C04,0}, //RBL_ReInitOccured_Smu0
                                                     {0x451C04,0}, //RBL_ReInitOccured_Smu1
                                                     {0x451C04,0}, //RBL_ReInitOccured_Smu2
                                                     {0x451D56,0}, //RBL_Nvm_SigChain_Content
                                                     {0x452096,0}, //CAN_E_TIME_OUT
                                                     {0x451C83,1}, //RBL_CommunicationFailure_Smu0
                                                     {0x451C83,1}, //RBL_CommunicationFailure_Smu1
                                                     {0x451C83,1}, //RBL_CommunicationFailure_Smu2
                                                     {0x451D56,0}, //RBL_Nvm_AmbTempMon_Content
                                                     {0x451D56,0}, //RBL_Nvm_RefFreq_Content
                                                     {0x452088,1}, // CANSM_E_BUSOFF_NETWORK_0
                                                     #if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)
                                                     {0x452096,0}, // CANTRCV_TJA_E_NO_TRCV_CONTROL_CH0
                                                     {0x452088,1}, // CANSM_E_BUSOFF_NETWORK_1
                                                     #endif
                                                     {0xC25E87,1}, //RBL_CUSTIF_TIMEOUT_BCS_Whl_Msg1_BTC_ST3
                                                     {0xC25E83,1}, //RBL_CUSTIF_SAFETY_BCS_Whl_Msg1_BTC_ST3
                                                     {0xC25E82,1}, //RBL_CUSTIF_SQC_BCS_Whl_Msg1_BTC_ST3
                                                     {0xC25E86,1}, //RBL_CUSTIF_SIGNAL_INVALID_BCS_Whl_Msg1_BTC_ST3
                                                     {0xC14687,1}, //RBL_CUSTIF_TIMEOUT_DIAG_Stat_ST3
                                                     {0xC14686,1}, //RBL_CUSTIF_SIGNAL_INVALID_DIAG_Stat_ST3
                                                     {0xC15587,1}, //RBL_CUSTIF_TIMEOUT_DI_OdoSpeedometer_ST3
                                                     {0xC15583,1}, //RBL_CUSTIF_SAFETY_DI_OdoSpeedometer_ST3
                                                     {0xC15582,1}, //RBL_CUSTIF_SQC_DI_OdoSpeedometer_ST3
                                                     {0xC14687,1},//RBL_CUSTIF_TIMEOUT_FBL_Cfg_Star3_ST3
                                                     {0xC14686,1},//RBL_CUSTIF_SIGNAL_INVALID_FBL_Cfg_Star3_ST3
                                                     {0xD11B87,1},//RBL_CUSTIF_TIMEOUT_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3
                                                     {0xD11B83,1},//RBL_CUSTIF_SAFETY_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3
                                                     {0xD11B82,1},//RBL_CUSTIF_SQC_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3
                                                     {0xD11B86,1},//RBL_CUSTIF_SIGNAL_INVALID_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3
                                                     {0xC14687,1}, //RBL_CUSTIF_TIMEOUT_Ign_Stat_ST3
                                                     {0xC14683,1}, //RBL_CUSTIF_SAFETY_Ign_Stat_ST3
                                                     {0xC14682,1}, //RBL_CUSTIF_SQC_Ign_Stat_ST3
                                                     {0xC14686,1}, //RBL_CUSTIF_SIGNAL_INVALID_Ign_Stat_ST3
                                                     {0xC14687,1}, //RBL_CUSTIF_TIMEOUT_PN14_Master_Stat1_ST3
                                                     {0xC14686,1}, //RBL_CUSTIF_SIGNAL_INVALID_PN14_Master_Stat1_ST3
                                                     {0xC11587,1}, //RBL_CUSTIF_TIMEOUT_PT4_PTCoor4_ST3
                                                     {0xC11583,1}, //RBL_CUSTIF_SAFETY_PT4_PTCoor4_ST3
                                                     {0xC11582,1}, //RBL_CUSTIF_SQC_PT4_PTCoor4_ST3
                                                     {0xC11586,1}, //RBL_CUSTIF_SIGNAL_INVALID_PT4_PTCoor4_ST3
                                                     {0x451C29,1}, //RBL_ChannelInvalid_Smu0_Acc1
                                                     {0x451C29,1}, //RBL_ChannelInvalid_Smu0_Acc2
                                                     {0x451C29,1}, //RBL_ChannelInvalid_Smu0_Acc3
                                                     {0x451C29,1}, //RBL_ChannelInvalid_Smu0_Rate1
                                                     {0x000000,1}, //RBL_ChannelInvalid_Smu1_Acc1
                                                     {0x000000,1}, //RBL_ChannelInvalid_Smu1_Acc2
                                                     {0x000000,1}, //RBL_ChannelInvalid_Smu1_Acc3
                                                     {0x451C29,1}, //RBL_ChannelInvalid_Smu1_Rate1
                                                     {0x000000,1}, //RBL_ChannelInvalid_Smu2_Acc1
                                                     {0x000000,1}, //RBL_ChannelInvalid_Smu2_Acc2
                                                     {0x000000,1}, //RBL_ChannelInvalid_Smu2_Acc3
                                                     {0x451C29,1}, //RBL_ChannelInvalid_Smu2_Rate1
                                                     {0x451C9A,1}, //RBL_MechOverload_Smu0_Acc1
                                                     {0x451C9A,1}, //RBL_MechOverload_Smu0_Acc2
                                                     {0x451C9A,1}, //RBL_MechOverload_Smu0_Acc3
                                                     {0x451C9A,1}, //RBL_MechOverload_Smu0_Rate1
                                                     {0x000000,1}, //RBL_MechOverload_Smu1_Acc1
                                                     {0x000000,1}, //RBL_MechOverload_Smu1_Acc2
                                                     {0x000000,1}, //RBL_MechOverload_Smu1_Acc3
                                                     {0x451C9A,1}, //RBL_MechOverload_Smu1_Rate1
                                                     {0x000000,1}, //RBL_MechOverload_Smu2_Acc1
                                                     {0x000000,1}, //RBL_MechOverload_Smu2_Acc2
                                                     {0x000000,1}, //RBL_MechOverload_Smu2_Acc3
                                                     {0x451C9A,1}, //RBL_MechOverload_Smu2_Rate1
                                                     {0x451C98,1}, //RBL_TemperatureRangeExceeded_Smu0
                                                     {0x451C98,1}, //RBL_TemperatureRangeExceeded_Smu1
                                                     {0x451C98,1}, //RBL_TemperatureRangeExceeded_Smu2
                                                     {0x451C98,1}, //RBL_AmbientTemperatureFault
                                                     {0x451C38,1}, //RBL_FrequencyFailure_Smu0
                                                     {0x451C38,1}, //RBL_FrequencyFailure_Smu1
                                                     {0x451C38,1}, //RBL_FrequencyFailure_Smu2
                                                     #if(RBFS_ThirdCanSupport == RBFS_ThirdCanSupport_Yes)
                                                     {0x452096,0}, // CANTRCV_TJA_E_NO_TRCV_CONTROL_CH1
                                                     {0x452088,1}, // CANSM_E_BUSOFF_NETWORK_2
                                                     #endif
                                                     {0x501687,1}, //RBL_STBM_NO_INIT_SYNC_TIMEOUT
                                                     {0x501687,1}, //RBL_STBM_SYNC_LOST_TIMEOUT
                                                     {0x501687,1}, //RBL_CUSTIF_STBM_TIMELEAP
                                                     {0xC15586,1}, //RBL_CUSTIF_SIGNAL_INVALID_DI_OdoSpeedometer_ST3
                                                     {0xC15586,1}, //RBL_CUSTIF_SIGNAL_INVALID_VEHSPD_DISP_ST3
                                                     {0x452004,1}, //RBL_STBM_RATE_COPY
                                                     {0x452004,1}, //RBL_STBM_TIME_COPY
};

#endif //#if (RBFS_MMP2 == RBFS_MMP2_IMUA)

#if (RBFS_MMP2 == RBFS_MMP2_IMUB)// with DualCan and ThirdCan On

#define NUMBER_OF_EVENTS 158

const Map_DTC_properties EventID[NUMBER_OF_EVENTS]= {{0x000000,0}, // dummy event
                                                     {0x452049,0}, // RBuCSupplyError
                                                     {0x452049,0}, // RBHWBISTError
                                                     {0x452044,0}, // RBRAMFailure
                                                     {0x452045,0}, // RBFlashFailure
                                                     {0x452049,0}, // RBuCSafetyFault
                                                     {0x452049,0}, // RBuCSafetyLogicFault
                                                     {0x452049,0}, // RBCPUException
                                                     {0x452049,0}, // RBSYS_StackOverUnderFlow
                                                     {0x452049,0}, // RBSYS_SYSErrorHook
                                                     {0x452049,0}, // RBSYS_OSErrorHook
                                                     {0x452049,0}, // RBSYS_TaskOverRun
                                                     {0x452049,0}, // RBOSTaskSchemeError
                                                     {0x452049,0}, // RBSYS_TaskJitter
                                                     {0x452049,0}, // RBDmaTransferError
                                                     {0x452049,0}, // RbmicAsicOscillatorError
                                                     {0x452042,0}, // RBuCRegisterFault
                                                     {0x452056,0}, // RB_UnsupportedSeriesHW
                                                     {0x452004,0}, // AssertionFailed
                                                     {0x452056,0}, // RB_UnsupportedHW
                                                     {0x452096,0}, // RBSupplyASICInitFailure
                                                     #if(RBFS_SUPPLYBASEU5VConfigCS990 != RBFS_SUPPLYBASEU5VConfigCS990_NotUsed && RBFS_SUPPLYBASEU5VConfigCS990 != RBFS_SUPPLYBASEU5VConfigCS990_NA)
                                                     {0x452096,0}, // RBSUPPLY_U5VTestFailure
                                                     {0x45201C,0}, // RBSUPPLY_U5VOutOfRange
                                                     #endif
                                                     {0x452047,0}, // RbfslEcuEClockTestFails
                                                     {0x452047,0}, // RbfslEcuWrongBistCmdTestFails
                                                     {0x452047,0}, // RbfslEcuFastWdTestFails
                                                     {0x452047,0}, // RbfslEcuBistFailureCtrTestFails
                                                     {0x452047,0}, // RbfslEcuErrpinCounterTestFails
                                                     {0x452047,0}, // RbfslEcuEnableElLowFails
                                                     {0x452047,0}, // RbfslDecoupleBitTestFails
                                                     {0x452047,0}, // RbfslEcuEnableElHighFails
                                                     {0x452047,0}, // RbfslEcuWdStartuptestFails
                                                     {0x452047,0}, // RbfslEcuEnContinuousError
                                                     {0x452047,0}, // RbfslEcuWdStatusContinuousError
                                                     {0x452064,0}, // RbmicAsicClkInError
                                                     {0x452064,0}, // RbmicAsicInitTestError
                                                     {0x452064,0}, // RbmicSpiTransferError
                                                     {0x452047,0}, // RbWdhAsicWdErrorCntStuck
                                                     {0x452047,0}, // RbWdhAsicWdErrorCntLimit
                                                     {0x452047,0}, // RbWdhAsicWdCmdMissing
                                                     {0x452047,0}, // RbWdhTaskMonConCnt
                                                     {0x452046,0}, // RBuCSafetyNotificationGRAM
                                                     {0x452046,0}, // RBuCSafetyNotification
                                                     {0x000000,0}, // DET_ReportError
                                                     {0x000000,0}, // RBSUPPLYIREFOutOfRange
                                                     {0x000000,0}, // RBChargePumpFailure
                                                     {0x000000,0}, // RBEcuBandgap
                                                     {0x000000,0}, // RBAdcPinTest
                                                     {0x000000,0}, // RBAdcSelftestC5P
                                                     {0x000000,0}, // RBAdcPeripheralFault
                                                     {0x000000,0}, // RBMICSYS_OC_AsicMalfunction
                                                     {0x000000,0}, // RBNvM_WriteCycleExceed
                                                     {0x000000,1}, // RBChargePumpUndervoltage
                                                     #if(RBFS_DynamicCanId == RBFS_DynamicCanId_ON)
                                                     {0x000000,0}, // RBL_NET_DynamicCanId
                                                     #endif
                                                     {0x451C04,0}, // RBL_SyncOnSmu_Timeout
                                                     {0x452048,0}, // RBL_SwcDiag_MemoryViolation
                                                     {0x451D56,0}, // RBL_Nvm_HwVersNr
                                                     {0x451D56,0}, // RBL_Nvm_PcbDmc
                                                     {0x451D56,0}, // RBL_Nvm_PlaIdNr
                                                     {0x451D56,0}, // RBL_Nvm_ProcProgsId
                                                     {0x451D56,0}, // RBL_Nvm_ProdDate
                                                     {0x451D56,0}, // RBL_Nvm_RbAsblyPartNr
                                                     {0x451D56,0}, // RBL_Nvm_RbPartNr
                                                     {0x451D56,0}, // RBL_Nvm_SnsrSerlNr
                                                     {0x164400,0}, // RBL_NVM_Variant_handler
                                                     #if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
                                                     {0x164456,0}, // SSA_Event_DTC_164456
                                                     #endif
                                                     {0xD1C316,1}, // RBNET_Undervoltage
                                                     {0xD1C417,1}, // RBNET_Overvoltage
                                                     {0x000000,1}, // SMM_OneRequestsInit
                                                     #if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
                                                     {0x9A6857,1}, // SSA_Event_DTC_9a6857
                                                     {0xD12081,1}, // SSA_Event_DTC_D12081
                                                     {0xD12083,1}, // SSA_Event_DTC_D12083
                                                     {0xD12087,1}, // SSA_Event_DTC_D12087
                                                     #endif
                                                     #if (RBFS_BUILDTYPE != RBFS_BUILDTYPE_RELEASE)
                                                     {0x000000,0}, // SEC_SecureBlockCheckFailed
                                                     {0x000000,0}, // SEC_AuthBlockCheckFailed
                                                     {0x000000,0}, // SEC_RtmdCheckFailed
                                                     {0x000000,0}, // SEC_RbSecBaseInternalErrorState
                                                     {0x000000,0}, // SEC_RbSecAccInternalErrorState
                                                     #endif
                                                     {0x000000,1}, // SEC_LifecyclePrivileged
                                                     {0x451C04,0}, // RBL_ReInitOccured_Smu0
                                                     {0x451C04,0}, // RBL_ReInitOccured_Smu1
                                                     {0x451C04,0}, // RBL_ReInitOccured_Smu2
                                                     {0x451D56,0}, // RBL_Nvm_SigChain_Content
                                                     {0x452096,0}, // CAN_E_TIME_OUT
                                                     {0x451C83,1}, // RBL_CommunicationFailure_Smu0
                                                     {0x451C83,1}, // RBL_CommunicationFailure_Smu1
                                                     {0x451C83,1}, // RBL_CommunicationFailure_Smu2
                                                     {0x451D56,0}, // RBL_Nvm_AmbTempMon_Content
                                                     {0x451D56,0}, // RBL_Nvm_RefFreq_Content
                                                     {0x452088,1}, // CANSM_E_BUSOFF_NETWORK_0
                                                     #if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)
                                                     {0x452096,0}, // CANTRCV_TJA_E_NO_TRCV_CONTROL_CH0
                                                     {0x452088,1}, // CANSM_E_BUSOFF_NETWORK_1
                                                     #endif
                                                     #if(RBFS_ThirdCanSupport == RBFS_ThirdCanSupport_Yes)
                                                     {0x452096,0}, // CANTRCV_TJA_E_NO_TRCV_CONTROL_CH1
                                                     {0x452088,1}, // CANSM_E_BUSOFF_NETWORK_2
                                                     #endif
                                                     {0xC25E87,1}, // RBL_CUSTIF_TIMEOUT_BCS_Whl_Msg1_BTC_ST3
                                                     {0xC25E83,1}, // RBL_CUSTIF_SAFETY_BCS_Whl_Msg1_BTC_ST3
                                                     {0xC25E82,1}, // RBL_CUSTIF_SQC_BCS_Whl_Msg1_BTC_ST3
                                                     {0xC25E86,1}, // RBL_CUSTIF_SIGNAL_INVALID_BCS_Whl_Msg1_BTC_ST3
                                                     {0xC14687,1}, // RBL_CUSTIF_TIMEOUT_DIAG_Stat_ST3
                                                     {0xC14686,1}, // RBL_CUSTIF_SIGNAL_INVALID_DIAG_Stat_ST3
                                                     {0xC15587,1}, // RBL_CUSTIF_TIMEOUT_DI_OdoSpeedometer_ST3
                                                     {0xC15583,1}, // RBL_CUSTIF_SAFETY_DI_OdoSpeedometer_ST3
                                                     {0xC15582,1}, // RBL_CUSTIF_SQC_DI_OdoSpeedometer_ST3
                                                     {0xC14687,1}, // RBL_CUSTIF_TIMEOUT_FBL_Cfg_Star3_ST3
                                                     {0xC14686,1}, // RBL_CUSTIF_SIGNAL_INVALID_FBL_Cfg_Star3_ST3
                                                     {0xD11B87,1}, //RBL_CUSTIF_TIMEOUT_HAD_Stat_IDC_M_FSI_Pr5_ST3
                                                     {0xD11B83,1}, //RBL_CUSTIF_SAFETY_HAD_Stat_IDC_M_FSI_Pr5_ST3
                                                     {0xD11B82,1}, //RBL_CUSTIF_SQC_HAD_Stat_IDC_M_FSI_Pr5_ST3
                                                     {0xD11B86,1}, //RBL_CUSTIF_SIGNAL_INVALID_HAD_Stat_IDC_M_FSI_Pr5_ST3
                                                     {0xC14687,1}, // RBL_CUSTIF_TIMEOUT_Ign_Stat_ST3
                                                     {0xC14683,1}, // RBL_CUSTIF_SAFETY_Ign_Stat_ST3
                                                     {0xC14682,1}, // RBL_CUSTIF_SQC_Ign_Stat_ST3
                                                     {0xC14686,1}, // RBL_CUSTIF_SIGNAL_INVALID_Ign_Stat_ST3
                                                     {0xC14687,1}, // RBL_CUSTIF_TIMEOUT_PN14_Master_Stat1_ST3
                                                     {0xC14686,1}, // RBL_CUSTIF_SIGNAL_INVALID_PN14_Master_Stat1_ST3
                                                     {0xC11587,1}, // RBL_CUSTIF_TIMEOUT_PT4_PTCoor4_ST3
                                                     {0xC11583,1}, // RBL_CUSTIF_SAFETY_PT4_PTCoor4_ST3
                                                     {0xC11582,1}, // RBL_CUSTIF_SQC_PT4_PTCoor4_ST3
                                                     {0xC11586,1}, // RBL_CUSTIF_SIGNAL_INVALID_PT4_PTCoor4_ST3
                                                     {0x000000,1}, // RBL_ChannelInvalid_Smu0_Acc1
                                                     {0x000000,1}, // RBL_ChannelInvalid_Smu0_Acc2
                                                     {0x000000,1}, // RBL_ChannelInvalid_Smu0_Acc3
                                                     {0x451C29,1}, // RBL_ChannelInvalid_Smu0_Rate1
                                                     {0x000000,1}, // RBL_ChannelInvalid_Smu1_Acc1
                                                     {0x000000,1}, // RBL_ChannelInvalid_Smu1_Acc2
                                                     {0x000000,1}, // RBL_ChannelInvalid_Smu1_Acc3
                                                     {0x451C29,1}, // RBL_ChannelInvalid_Smu1_Rate1
                                                     {0x451C29,1}, // RBL_ChannelInvalid_Smu2_Acc1
                                                     {0x451C29,1}, // RBL_ChannelInvalid_Smu2_Acc2
                                                     {0x451C29,1}, // RBL_ChannelInvalid_Smu2_Acc3
                                                     {0x451C29,1}, // RBL_ChannelInvalid_Smu2_Rate1
                                                     {0x000000,1}, // RBL_MechOverload_Smu0_Acc1
                                                     {0x000000,1}, // RBL_MechOverload_Smu0_Acc2
                                                     {0x000000,1}, // RBL_MechOverload_Smu0_Acc3
                                                     {0x451C9A,1}, // RBL_MechOverload_Smu0_Rate1
                                                     {0x000000,1}, // RBL_MechOverload_Smu1_Acc1
                                                     {0x000000,1}, // RBL_MechOverload_Smu1_Acc2
                                                     {0x000000,1}, // RBL_MechOverload_Smu1_Acc3
                                                     {0x451C9A,1}, // RBL_MechOverload_Smu1_Rate1
                                                     {0x451C9A,1}, // RBL_MechOverload_Smu2_Acc1
                                                     {0x451C9A,1}, // RBL_MechOverload_Smu2_Acc2
                                                     {0x451C9A,1}, // RBL_MechOverload_Smu2_Acc3
                                                     {0x451C9A,1}, // RBL_MechOverload_Smu2_Rate1
                                                     {0x451C98,1}, // RBL_TemperatureRangeExceeded_Smu0
                                                     {0x451C98,1}, // RBL_TemperatureRangeExceeded_Smu1
                                                     {0x451C98,1}, // RBL_TemperatureRangeExceeded_Smu2
                                                     {0x451C98,1}, // RBL_AmbientTemperatureFault
                                                     {0x451C38,1}, // RBL_FrequencyFailure_Smu0
                                                     {0x451C38,1}, // RBL_FrequencyFailure_Smu1
                                                     {0x451C38,1}, // RBL_FrequencyFailure_Smu2
                                                     {0x501687,1}, // RBL_STBM_NO_INIT_SYNC_TIMEOUT
                                                     {0x501687,1}, // RBL_STBM_SYNC_LOST_TIMEOUT
                                                     {0x501687,1}, // RBL_CUSTIF_STBM_TIMELEAP
                                                     {0x501687,1}, //RBL_CUSTIF_STBM_NO_INIT_SYNC_TIMEOUT_2
                                                     {0x501687,1}, //RBL_STBM_SYNC_LOST_TIMEOUT_2
                                                     {0x501687,1}, //RBL_CUSTIF_STBM_TIMELEAP_2
                                                     {0x501687,1}, //RBL_STBM_RATE_COPY_2
                                                     {0x501687,1}, //RBL_STBM_TIME_COPY_2
                                                     {0xC15586,1}, // RBL_CUSTIF_SIGNAL_INVALID_DI_OdoSpeedometer_ST3
                                                     {0xC15586,1}, // RBL_CUSTIF_SIGNAL_INVALID_VEHSPD_DISP_ST3
                                                     {0x452004,1}, // RBL_STBM_RATE_COPY
                                                     {0x452004,1}, // RBL_STBM_TIME_COPY

};
#endif //#if (RBFS_MMP2 == RBFS_MMP2_IMUB)




#endif /* RBDSM_SWT_DTC_PROPERTIES_H_ */

