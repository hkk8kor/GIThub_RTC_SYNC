#ifndef TRBSYS_CONFIGELEMENTS_H__
#define TRBSYS_CONFIGELEMENTS_H__


#define RBFS_TargetDevice_RenesasD1 1
#define RBFS_TargetDevice_RenesasD2 2
#define RBFS_TargetDevice_RenesasD3 3
#define RBFS_TargetDevice_RenesasD4 4
#define RBFS_TargetDevice_RenesasD5 5
#define RBFS_TargetDevice_RenesasD7 8
#define RBFS_TargetDevice_RenesasM2 6
#define RBFS_TargetDevice_RenesasM3 7
#define RBFS_TargetDevice_RenesasM6 8
#define RBFS_TargetDevice_STMP2     9
#define RBFS_TargetDevice_STMP3     10
#define RBFS_TargetDevice_STMP6     11
#define RBFS_TargetDevice_RenesasK0 12
#define RBFS_TargetDevice_RenesasK1 13


#define RBFS_uCFamily_RenesasP1x    1
#define RBFS_uCFamily_RenesasU2A    2
#define RBFS_uCFamily_STMStellar    3
#define RBFS_uCFamily_RenesasU2C    4


#define RBFS_EmulationDevice_None           1
#define RBFS_EmulationDevice_RenesasD3ED    2
#define RBFS_EmulationDevice_RenesasD5ED    3
#define RBFS_EmulationDevice_RenesasD7ED    4
#define RBFS_EmulationDevice_RenesasM6ED    4
#define RBFS_EmulationDevice_STMP3ED        5
#define RBFS_EmulationDevice_STMP7ED        6
#define RBFS_EmulationDevice_RenesasK3ED    7


/** Renesas uC Device RH850 D1 (=> without Aurora high-speed measurement support) */
#define RBFS_uC_RenesasD1                     1
/** Renesas uC Device RH850 D3ED in D1 mode (=> with Aurora high-speed measurement support and additional Variable RAM) */
#define RBFS_uC_RenesasD1onD3ED               2
/** Renesas uC Device RH850 D2 (=> without Aurora high-speed measurement support) */
#define RBFS_uC_RenesasD2                     3
/** Renesas uC Device RH850 D3ED in D2 mode (=> with Aurora high-speed measurement support and additional Variable RAM) */
#define RBFS_uC_RenesasD2onD3ED               4


/***************************************************************************************
 * D3 frequency could be configured to 160MHz or 240MHz. Therefore this device config is
 * available for RBSYS UnitTests with both frequencies to cover the complete UT variance
 * using "Variance Execution"
 ***************************************************************************************/

/** Renesas uC Device RH850 D3 (=> without Aurora high-speed measurement support) */
#define RBFS_uC_Renesas160MHzD3               5
/** Renesas uC Device RH850 D3ED in D3 mode (=> with Aurora high-speed measurement support and additional Variable RAM) */
#define RBFS_uC_Renesas160MHzD3onD3ED         6
/** Renesas uC Device RH850 D5ED in D3 mode (=> with Aurora high-speed measurement support and additional Variable RAM) */
#define RBFS_uC_Renesas160MHzD3onD5ED         7
/** Renesas uC Device RH850 D3 (=> without Aurora high-speed measurement support) */
#define RBFS_uC_Renesas240MHzD3               8
/** Renesas uC Device RH850 D3ED in D3 mode (=> with Aurora high-speed measurement support and additional Variable RAM) */
#define RBFS_uC_Renesas240MHzD3onD3ED         9
/** Renesas uC Device RH850 D5ED in D3 mode (=> with Aurora high-speed measurement support and additional Variable RAM) */
#define RBFS_uC_Renesas240MHzD3onD5ED         10


/** Renesas uC Device RH850 D4 (=> without Aurora high-speed measurement support) */
#define RBFS_uC_RenesasD4                     11
/** Renesas uC Device RH850 D5ED in D4 mode (=> with Aurora high-speed measurement support and additional Variable RAM) */
#define RBFS_uC_RenesasD4onD5ED               12
/** Renesas uC Device RH850 D5 (=> without Aurora high-speed measurement support) */
#define RBFS_uC_RenesasD5                     13
/** Renesas uC Device RH850 D5ED in D5 mode (=> with Aurora high-speed measurement support and additional Variable RAM) */
#define RBFS_uC_RenesasD5onD5ED               14


/** Renesas uC Device RH850 M2 (=> without Aurora high-speed measurement support) */
#define RBFS_uC_RenesasM2                     15
/** Renesas uC Device RH850 M6ED in M3 mode (only M2 ressource set is being used) (=> with Aurora high-speed measurement support) */
#define RBFS_uC_RenesasM2onM6ED               16
/** Renesas uC Device RH850 M3 (=> without Aurora high-speed measurement support) */
#define RBFS_uC_RenesasM3                     17
/** Renesas uC Device RH850 M6ED in M3 mode (=> with Aurora high-speed measurement support) */
#define RBFS_uC_RenesasM3onM6ED               18
/** Renesas uC Device RH850 M6 (=> without Aurora high-speed measurement support) */
#define RBFS_uC_RenesasD7                     19
#define RBFS_uC_RenesasM6                     19
/** Renesas uC Device RH850 M6ED in M6 mode (=> with Aurora high-speed measurement support) */
#define RBFS_uC_RenesasD7onD7ED               20
#define RBFS_uC_RenesasM6onM6ED               20

/** ST Microelectronics uC Device Stellar P7ED used with P6 software (=> with Aurora high-speed measurement support) */
#define RBFS_uC_STMP6onP7ED                   21
/** ST Microelectronics uC Device Stellar P6 (=> without Aurora high-speed measurement support) */
#define RBFS_uC_STMP6                         22

/** Renesas uC Device RH850 K0 (=> without Aurora high-speed measurement support) */
#define RBFS_uC_RenesasK0                     23
/** Renesas uC Device RH850 K0 in K3ED mode (=> with Aurora high-speed measurement support) */
#define RBFS_uC_RenesasK0onK3ED               24
/** Renesas uC Device RH850 K1 (=> without Aurora high-speed measurement support) */
#define RBFS_uC_RenesasK1                     25
/** Renesas uC Device RH850 K1 in K3ED mode (=> with Aurora high-speed measurement support) */
#define RBFS_uC_RenesasK1onK3ED               26

/* defines for variance execution over a single uC familiy */
#define RBFS_uCRenesasP1x_D1                     1
#define RBFS_uCRenesasP1x_D1onD3ED               2
#define RBFS_uCRenesasP1x_D2                     3
#define RBFS_uCRenesasP1x_D2onD3ED               4
#define RBFS_uCRenesasP1x_160MHzD3               5
#define RBFS_uCRenesasP1x_160MHzD3onD3ED         6
#define RBFS_uCRenesasP1x_160MHzD3onD5ED         7
#define RBFS_uCRenesasP1x_240MHzD3               8
#define RBFS_uCRenesasP1x_240MHzD3onD3ED         9
#define RBFS_uCRenesasP1x_240MHzD3onD5ED         10
#define RBFS_uCRenesasP1x_D4                     11
#define RBFS_uCRenesasP1x_D4onD5ED               12
#define RBFS_uCRenesasP1x_D5                     13
#define RBFS_uCRenesasP1x_D5onD5ED               14

#define RBFS_uCRenesasU2A_M2                     1
#define RBFS_uCRenesasU2A_M2onM6ED               2
#define RBFS_uCRenesasU2A_M3                     3
#define RBFS_uCRenesasU2A_M3onM6ED               4
#define RBFS_uCRenesasU2A_D7                     5
#define RBFS_uCRenesasU2A_M6                     5
#define RBFS_uCRenesasU2A_D7onD7ED               6
#define RBFS_uCRenesasU2A_M6onM6ED               6

#define RBFS_uCSTMStellar_P6onP7ED               1
#define RBFS_uCSTMStellar_P6                     2


/** Build configuration type for Single Core system */
#define RBFS_ConfigCore_SingleCore          1
/** Build configuration type for Multi Core system */
#define RBFS_ConfigCore_MultiCore           2


/** Micro controller: single core (1 core in lockstep) */
#define RBFS_MCORE_OFF  1
/** Micro controller: multi core (2 cores, each in lockstep) */
#define RBFS_MCORE_ON   2


/** 0.5ms task not used */
#define RBFS_SysTask0p5ms_OFF  1
/** 0.5ms task used*/
#define RBFS_SysTask0p5ms_ON   2


/** Flexray supported */
#define RBFS_FlexraySupport_Yes     1
/** Flexray not supported */
#define RBFS_FlexraySupport_No      2


/** Task scheme based on system timer (normal SYS scheduling) */
#define RBFS_TaskSync_OFF 1
/** Task scheme synchronization to an arbitrary bus time */
#define RBFS_TaskSync_ON  2


/** RBSYS does not provide a FlexRay Task */
#define RBFS_SysFlxrTask_OFF  1
/** RBSYS has to provide a FlexRay Task */
#define RBFS_SysFlxrTask_ON   2


/** Standard task scheme - envelope for all brake system products */
#define RBFS_TaskSchemeExtension_None                            1
/** Task scheme extenstion for CC-PS product VMPS only: Addional VMPS specific tasks incl. a different task distribution */
#define RBFS_TaskSchemeExtension_VMPS                            2
/**< Task scheme extension, no hypervisor, currently for JLR only: Additional JLR specific tasks incl. a different task distribution (Brake System on core 0, Vehicle Supervisor Control (VSC) SW on core 1) */
#define RBFS_TaskSchemeExtension_HostCore0GuestCore1             3
/**< Task scheme extenstion for Airbag 15 only: Additional Airbag 15 specific tasks incl. a different task distribution */
#define RBFS_TaskSchemeExtension_AB15                            4


/** project without bootblock support */
#define RBFS_SysBootblockSupport_OFF  1
/** project with bootblock support */
#define RBFS_SysBootblockSupport_ON   2


/** current build is no bootblock build */
#define RBFS_SysBootblockBuild_Active      1
/** current build is a bootblock build */
#define RBFS_SysBootblockBuild_NotActive   2


/** 5% + max flexray adaptation of task x1 is jitter monitored */
#define RBFS_SysMaxTaskx1Jitter_5         1
/** 15% + max flexray adaptation of task x1 is jitter monitored */
#define RBFS_SysMaxTaskx1Jitter_15        2
/** Series setting of jitter montioring (failure reporting disabled) */
#define RBFS_SysMaxTaskx1Jitter_SERIES    3

/** Third party SW capsule disabled */
#define RBFS_TPSWCapsule_OFF      1
/** Third party SW capsule support: Memory protection */
#define RBFS_TPSWCapsule_SC3      2
/** Third party SW capsule support: Memory + Runtime protection */
#define RBFS_TPSWCapsule_SC4      3


/** TPSW supervisor mode restrictions disabled (default) */
#define RBFS_TPSWSVPRestrictions_OFF  1
/** TPSW supervisor mode restrictions enabled */
#define RBFS_TPSWSVPRestrictions_ON   2


/** pTSW build active */
#define RBFS_pTSWSupport_ON     1
/** No pTSW build active */
#define RBFS_pTSWSupport_OFF    2


/** All cores are running with 80MHz*/
#define RBFS_CpuClock_80MHz     1
/** All cores are running with 160MHz*/
#define RBFS_CpuClock_160MHz    2
/** All cores are running with 240MHz*/
#define RBFS_CpuClock_240MHz    3
/** All cores are running with 320MHz*/
#define RBFS_CpuClock_320MHz    4
/** All cores are running with 400MHz*/
#define RBFS_CpuClock_400MHz    5


/** Global RAM Support OFF */
#define RBFS_RenesasP1xGRAM_OFF   1
/** Global RAM Support ON */
#define RBFS_RenesasP1xGRAM_ON    2


/** Overwrite EBASE register from OS configuration in case of ePSW or TC-SW */
#define RBFS_SysOverwriteEBASE_ON                             1
/** Do not overwrite EBASE register from OS configuration */
#define RBFS_SysOverwriteEBASE_OFF                            2


/** RBSYS start-up code active in bootblock */
#define RBFS_BootblockSysStartupCode_ON                       1
/** RBSYS start-up code inactive in bootblock */
#define RBFS_BootblockSysStartupCode_OFF                      2


/** Debug features to check unbalanced locks after each process */
#define RBFS_SysDebugUnbalancedLock_ON   1
/** Debug features must be switched off for series builds (still active on task granularity) */
#define RBFS_SysDebugUnbalancedLock_OFF  2


/** Debug features to store for each task the longest running process using code instrumentation
    from rba_Runtime and prepare data for MM6 (see measurement variable RBSYS_DebugInfo_MaxProcPerTask) */
#define RBFS_SysDebugProcRuntime_ON   1
/** Debug features must be switched off for series builds - requires additional (critical) runtime */
#define RBFS_SysDebugProcRuntime_OFF  2


/** Current build is for a boot manager */
#define RBFS_HexBlockBuild_BOOTMANAGER   1
/** Current build is for an OEM-boot loader */
#define RBFS_HexBlockBuild_BOOTLOADER    2
/** Current build is for the application (driving software) */
#define RBFS_HexBlockBuild_APPLICATION   3
/** Current build is for a RB boot loader */
#define RBFS_HexBlockBuild_RBBOOTLOADER  4

#define RBFS_BootblockEnableAsicSupport_ON  1
#define RBFS_BootblockEnableAsicSupport_OFF 2


/* hexblock configs supported in Gen9.3 */
#define RBFS_HexBlockConfig_BMGR                              1
#define RBFS_HexBlockConfig_BLDR                              2
#define RBFS_HexBlockConfig_RBBLDR                            3
#define RBFS_HexBlockConfig_FSW                               4
#define RBFS_HexBlockConfig_BLDRxFSW                          5
#define RBFS_HexBlockConfig_BLDRxFSWxCAL                      6
#define RBFS_HexBlockConfig_BMGRxBLDRxFSW                     7
#define RBFS_HexBlockConfig_BMGRxRBBLDRxFSW                   8
#define RBFS_HexBlockConfig_BMGRxRBBLDRxBLDRxFSW              9
#define RBFS_HexBlockConfig_BMGRxBLDRxFSWxCAL                 10
#define RBFS_HexBlockConfig_BMGRxRBBLDRxBLDRxFSWxCAL          11
#define RBFS_HexBlockConfig_FSWxHSM                           12
#define RBFS_HexBlockConfig_BMGRxRBBLDRxFSWxHSM               13
#define RBFS_HexBlockConfig_BMGRxRBBLDRxBLDRxFSWxHSM          14
#define RBFS_HexBlockConfig_BMGRxRBBLDRxBLDRxFSWxCALxHSM      15
#define RBFS_HexBlockConfig_FSWxFSW                           16
#define RBFS_HexBlockConfig_BLDRxFSWxFSW                      17
#define RBFS_HexBlockConfig_BLDRxFSWxFSWxCAL                  18
#define RBFS_HexBlockConfig_BMGRxBLDRxFSWxFSW                 19
#define RBFS_HexBlockConfig_BMGRxRBBLDRxFSWxFSW               20
#define RBFS_HexBlockConfig_BMGRxRBBLDRxBLDRxFSWxFSW          21
#define RBFS_HexBlockConfig_BMGRxBLDRxFSWxFSWxCAL             22
#define RBFS_HexBlockConfig_BMGRxRBBLDRxBLDRxFSWxFSWxCAL      23
#define RBFS_HexBlockConfig_FSWxFSWxHSM                       24
#define RBFS_HexBlockConfig_BMGRxRBBLDRxFSWxFSWxHSM           25
#define RBFS_HexBlockConfig_BMGRxRBBLDRxBLDRxFSWxFSWxHSM      26
#define RBFS_HexBlockConfig_BMGRxRBBLDRxBLDRxFSWxFSWxCALxHSM  27
#define RBFS_HexBlockConfig_Customized                        28


#define RBFS_HardwareSecurityModule_Unsupported    1
#define RBFS_HardwareSecurityModule_Supported      2

#define RBFS_SysHsmSharedGRAMsize_0K    1
#define RBFS_SysHsmSharedGRAMsize_16K   2
#define RBFS_SysHsmSharedGRAMsize_32K   3

#define RBFS_TPSWTestsuite_OFF  1
#define RBFS_TPSWTestsuite_ON   2

#define RBFS_BackdoorBootblock_NO                  1
#define RBFS_BackdoorBootblock_YES                 2


#define RBFS_SysEthSharedGRAMsize_0K    1
#define RBFS_SysEthSharedGRAMsize_32K   2
#define RBFS_SysEthSharedGRAMsize_64K   3
#define RBFS_SysEthSharedGRAMsize_96K   4
#define RBFS_SysEthSharedGRAMsize_128K  5

#define RBFS_RestrictedExclusiveGRAMsize_0K    1
#define RBFS_RestrictedExclusiveGRAMsize_16K   2
#define RBFS_RestrictedExclusiveGRAMsize_32K   3
#define RBFS_RestrictedExclusiveGRAMsize_64K   4
#define RBFS_RestrictedExclusiveGRAMsize_128K  5
#define RBFS_RestrictedExclusiveGRAMsize_256K  6

#define RBFS_SysHSMsharedGRAM_Host         1
#define RBFS_SysHSMsharedGRAM_Restricted   2



#define RBFS_RenesasU2aCRAM0_ON          1
#define RBFS_RenesasU2aCRAM0_OFF         2

#define RBFS_RenesasU2aCRAM1_ON          1
#define RBFS_RenesasU2aCRAM1_OFF         2

#define RBFS_RenesasU2aCRAM2_ON          1
#define RBFS_RenesasU2aCRAM2_OFF         2

#define RBFS_RenesasU2aCRAM3_ON          1
#define RBFS_RenesasU2aCRAM3_OFF         2

#define RBFS_RenesasU2cCRAM0_ON          1
#define RBFS_RenesasU2cCRAM0_OFF         2

#define RBFS_DataFlashECC_Disabled          1
#define RBFS_DataFlashECC_Enabled           2


#define RBFS_SYSDebugFeatures_ON            1
#define RBFS_SYSDebugFeatures_OFF           2

#define RBFS_TriggerTimerSupport_On  1
#define RBFS_TriggerTimerSupport_Off 2


#define RBFS_CompilationLanguage_PureC          1
#define RBFS_CompilationLanguage_PureCPP        2
#define RBFS_CompilationLanguage_MixedCandCPP   3

#define RBFS_SysResettableSlackTimesSupport_ON  1
#define RBFS_SysResettableSlackTimesSupport_OFF 2


/** Ethernet support in RBSYS is enabled */
#define RBFS_SysEthernetSupport_ON     1
/** Ethernet support in RBSYS is disabled */
#define RBFS_SysEthernetSupport_OFF    2

/* Ethernet communication is not supported */
#define RBFS_Ethernet_Disabled      1
/* Ethernet communication is supported */
#define RBFS_Ethernet_Enabled      2


/** RBSYS SystemLoad calculated each 20ms (calculation every second x2) */
#define RBFS_SysSystemLoadCalc_20ms    1
/** RBSYS SystemLoad calculated each 120ms (calculation every twelfth x2) */
#define RBFS_SysSystemLoadCalc_120ms   2
/** RBSYS SystemLoad calculated each 1000ms (calculation every hundredth x2 - only for VMPS) */
#define RBFS_SysSystemLoadCalc_1000ms  3

#define RBFS_FOTA_OFF        1
#define RBFS_FOTA_BASE       2
#define RBFS_FOTA_BASEPLUS   3
#define RBFS_FOTA_ENHANCED   4
#define RBFS_FOTA_PREMIUM    5

#define RBFS_HswRecoveryReset_Enabled  1
#define RBFS_HswRecoveryReset_Disabled 2

#define RBFS_TraceMeasurement_uCdependent            1
#define RBFS_TraceMeasurement_RuntimeConfigurable    2

/** HSM will start the host core once software is validated */
#define RBFS_RBSYSSecureBootStartup_HSMonly    1
/** Host Core has to be started at startup */
#define RBFS_RBSYSSecureBootStartup_HSMandHost 2

/** Global RAM available independent of device family */
#define RBFS_GlobalRamSupport_OFF  1
/** Global RAM not available independent of device family */
#define RBFS_GlobalRamSupport_ON   2

/** Misaligned accesses are allowed */
#define RBFS_CPUMisalignedAccessSupport_ON    1
/** Misaligned accesses are forbidden -> Reaction: e.g. MAE Exception */
#define RBFS_CPUMisalignedAccessSupport_OFF   2

#define RBFS_DataFlashSupport_No              1
#define RBFS_DataFlashSupport_Yes             2

#define RBFS_HSWSimulation_ON   1
#define RBFS_HSWSimulation_OFF  2

#define RBFS_LockTimeMonitoring_Enabled       1
#define RBFS_LockTimeMonitoring_Disabled      2

#define RBFS_SysTPSWSupport_YES 1
#define RBFS_SysTPSWSupport_NO  2

#define RBFS_BackupRAMLayout_Legacy 1
#define RBFS_BackupRAMLayout_V1     2

/** CodeFlash Memory is organized as SingleMap, i.e. one area (considered all ACTIVE by HW, but maybe configured different by SW - as in FOTAadvanced) */
#define RBFS_CodeFlashMemoryMode_SingleMap     1
/** CodeFlash Memory is organized as DoubleMap, i.e. two areas (of same size which can be exchanged by MemoryMap switching. They are considered ACTIVE and INACTIVE by HW)  */
#define RBFS_CodeFlashMemoryMode_DoubleMap     2

#define RBFS_ReprogDriverSupport_ON    1
#define RBFS_ReprogDriverSupport_OFF   2

#define RBFS_RBSYSGlobalRAMGuardsBB_ON  1
#define RBFS_RBSYSGlobalRAMGuardsBB_OFF 2

#define RBFS_SysRAMLayoutFragmentation_Default              1
#define RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR 2


#define RBFS_uCPackage_QFP80                               1
#define RBFS_uCPackage_QFP100                              2
#define RBFS_uCPackage_QFP144                              3
#define RBFS_uCPackage_BGA156                              4
#define RBFS_uCPackage_BGA292                              5


#define RBFS_uCandPackage_D1QFP80                          1
#define RBFS_uCandPackage_D1onD3EDQFP80                    2
#define RBFS_uCandPackage_D1QFP100                         3
#define RBFS_uCandPackage_D1onD3EDQFP100                   4
#define RBFS_uCandPackage_D2QFP100                         5
#define RBFS_uCandPackage_D2onD3EDQFP100                   6
#define RBFS_uCandPackage_D2QFP144                         7
#define RBFS_uCandPackage_D2onD3EDQFP144                   8
#define RBFS_uCandPackage_160MHzD3QFP144                   9
#define RBFS_uCandPackage_160MHzD3onD3EDQFP144             10
#define RBFS_uCandPackage_160MHzD3onD5EDQFP144             11
#define RBFS_uCandPackage_160MHzD3BGA156                   12
#define RBFS_uCandPackage_160MHzD3onD3EDBGA156             13
#define RBFS_uCandPackage_160MHzD3onD5EDBGA156             14
#define RBFS_uCandPackage_160MHzD3BGA292                   15
#define RBFS_uCandPackage_160MHzD3onD5EDBGA292             16
#define RBFS_uCandPackage_240MHzD3QFP144                   17
#define RBFS_uCandPackage_240MHzD3onD3EDQFP144             18
#define RBFS_uCandPackage_240MHzD3onD5EDQFP144             19
#define RBFS_uCandPackage_240MHzD3BGA156                   20
#define RBFS_uCandPackage_240MHzD3onD3EDBGA156             21
#define RBFS_uCandPackage_240MHzD3onD5EDBGA156             22
#define RBFS_uCandPackage_240MHzD3BGA292                   23
#define RBFS_uCandPackage_240MHzD3onD5EDBGA292             24
#define RBFS_uCandPackage_D4BGA292                         25
#define RBFS_uCandPackage_D4onD5EDBGA292                   26
#define RBFS_uCandPackage_D5BGA292                         27
#define RBFS_uCandPackage_D5onD5EDBGA292                   28
#define RBFS_uCandPackage_M2QFP144                         29
#define RBFS_uCandPackage_M2onM6EDQFP144                   30
#define RBFS_uCandPackage_M2BGA292                         31
#define RBFS_uCandPackage_M2onM6EDBGA292                   32
#define RBFS_uCandPackage_M3BGA292                         33
#define RBFS_uCandPackage_M3onM6EDBGA292                   34
#define RBFS_uCandPackage_M6BGA292                         35
#define RBFS_uCandPackage_M6onM6EDBGA292                   36

#define RBFS_CANCommunicationDuringInitTask_Enabled  1
#define RBFS_CANCommunicationDuringInitTask_Disabled 2

/** Restricted CPU clocks are forbidden */
#define RBFS_CpuClockRestriction_Default    1
/** Restricted CPU clocks are allowed */
#define RBFS_CpuClockRestriction_OFF        2


#define RBFS_LocalRamCore1Support_ON     1
#define RBFS_LocalRamCore1Support_OFF    2

#define RBFS_LocalRamCore2Support_ON     1
#define RBFS_LocalRamCore2Support_OFF    2

#define RBFS_LocalRamCore3Support_ON     1
#define RBFS_LocalRamCore3Support_OFF    2

#define RBFS_LocalRamCore4Support_ON     1
#define RBFS_LocalRamCore4Support_OFF    2

#define RBFS_LocalRamCore5Support_ON     1
#define RBFS_LocalRamCore5Support_OFF    2

#define RBFS_FlashBank0Support_ON        1
#define RBFS_FlashBank0Support_INACTIVE  2
#define RBFS_FlashBank0Support_OFF       3

#define RBFS_FlashBank1Support_ON        1
#define RBFS_FlashBank1Support_INACTIVE  2
#define RBFS_FlashBank1Support_OFF       3

#define RBFS_FlashBank2Support_ON        1
#define RBFS_FlashBank2Support_INACTIVE  2
#define RBFS_FlashBank2Support_OFF       3

#define RBFS_FlashBank3Support_ON        1
#define RBFS_FlashBank3Support_INACTIVE  2
#define RBFS_FlashBank3Support_OFF       3

#define RBFS_FlashBank4Support_ON        1
#define RBFS_FlashBank4Support_INACTIVE  2
#define RBFS_FlashBank4Support_OFF       3

#define RBFS_FlashBank5Support_ON        1
#define RBFS_FlashBank5Support_INACTIVE  2
#define RBFS_FlashBank5Support_OFF       3

#define RBFS_uCWatchdog_Enabled  1
#define RBFS_uCWatchdog_Disabled 2

#endif
