#ifndef TRB_PRJ_CONFIGELEMENTS_H__
#define TRB_PRJ_CONFIGELEMENTS_H__





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




/** Flexray supported */
#define RBFS_FlexraySupport_Yes     1
/** Flexray not supported */
#define RBFS_FlexraySupport_No      2



/** Standard task scheme - envelope for all brake system products */
#define RBFS_TaskSchemeExtension_None                            1
/** Task scheme extenstion for CC-PS product VMPS only: Addional VMPS specific tasks incl. a different task distribution */
#define RBFS_TaskSchemeExtension_VMPS                            2
/**< Task scheme extension, no hypervisor, currently for JLR only: Additional JLR specific tasks incl. a different task distribution (Brake System on core 0, Vehicle Supervisor Control (VSC) SW on core 1) */
#define RBFS_TaskSchemeExtension_HostCore0GuestCore1             3
/**< Task scheme extenstion for Airbag 15 only: Additional Airbag 15 specific tasks incl. a different task distribution */
#define RBFS_TaskSchemeExtension_AB15                            4

/** pTSW build active */
#define RBFS_pTSWSupport_ON     1
/** No pTSW build active */
#define RBFS_pTSWSupport_OFF    2



#define RBFS_Task0p5ms_ON       1
#define RBFS_Task0p5ms_OFF      2

#define RBFS_HswCompilerRuntimeChecks_On        1
#define RBFS_HswCompilerRuntimeChecks_Off       2

#define RBFS_T1FlexSupport_No                   1
#define RBFS_T1FlexSupport_Yes                  2

#define RBFS_DownloadModuleSupport_NO           1
#define RBFS_DownloadModuleSupport_YES          2    



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

#define RBFS_BackdoorBootblock_NO                  1
#define RBFS_BackdoorBootblock_YES                 2

#define RBFS_Compiler_GHS                          1
#define RBFS_Compiler_GCC4HSim                     2
#define RBFS_Compiler_GCC4BSWSim                   3
#define RBFS_Compiler_GHS2018                      4
#define RBFS_Compiler_GHS2021                      5
#define RBFS_Compiler_GCC4                         6
#define RBFS_Compiler_TDM5                         7

#define RBFS_CompilationLanguage_PureC          1
#define RBFS_CompilationLanguage_PureCPP        2
#define RBFS_CompilationLanguage_MixedCandCPP   3

#define RBFS_Ethernet_Disabled      1
#define RBFS_Ethernet_Enabled      2

#define RBFS_FOTA_OFF        1
#define RBFS_FOTA_BASE       2
#define RBFS_FOTA_BASEPLUS   3
#define RBFS_FOTA_ENHANCED   4
#define RBFS_FOTA_PREMIUM    5

#define RBFS_HswRecoveryReset_Enabled  1
#define RBFS_HswRecoveryReset_Disabled 2

#define RBFS_TraceMeasurement_uCdependent            1
#define RBFS_TraceMeasurement_RuntimeConfigurable    2

#define RBFS_HydrActSystem_Unused                         1
#define RBFS_HydrActSystem_ABS                            2
#define RBFS_HydrActSystem_ESP                            3
#define RBFS_HydrActSystem_ESPhev                         4
#define RBFS_HydrActSystem_ESPhevX                        5
#define RBFS_HydrActSystem_IPB                            6
#define RBFS_HydrActSystem_DPB                            7
#define RBFS_HydrActSystem_RBU                            8
#define RBFS_HydrActSystem_ABSM1CH                        9
#define RBFS_HydrActSystem_ABSM2CH                        10
#define RBFS_HydrActSystem_ABSME2CHSEMI                   11
#define RBFS_HydrActSystem_ABSME2CHFULL                   12
#define RBFS_HydrActSystem_ABSME3CH                       13


#define RBFS_CyberSecurityBoot_NonTrusted                 1
#define RBFS_CyberSecurityBoot_Trusted                    2
#define RBFS_CyberSecurityBoot_Gracious                   3
#define RBFS_CyberSecurityBoot_Staged                     4
#define RBFS_CyberSecurityBoot_Concurrent                 5
#define RBFS_CyberSecurityBoot_Secure                     6


#define RBFS_Bootblock_Enabled                            1
#define RBFS_Bootblock_Disabled                           2

#define RBFS_DataFlashSupport_No              1
#define RBFS_DataFlashSupport_Yes             2

#define RBFS_HSWSimulation_ON   1
#define RBFS_HSWSimulation_OFF  2

#define RBFS_BackupRAMLayout_Legacy 1
#define RBFS_BackupRAMLayout_V1     2

#define RBFS_CodeFlashMemoryMode_SingleMap     1
#define RBFS_CodeFlashMemoryMode_DoubleMap     2

#define RBFS_ReprogDriverSupport_ON    1
#define RBFS_ReprogDriverSupport_OFF   2


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

#define RBFS_uCandPackage_K0QFP144                         37
#define RBFS_uCandPackage_K0onK3EDBGA404                   38
#define RBFS_uCandPackage_K1QFP144                         39
#define RBFS_uCandPackage_K1BGA292                         40
#define RBFS_uCandPackage_K1onK3EDBGA404                   41

#define RBFS_CANCommunicationDuringInitTask_Enabled  1
#define RBFS_CANCommunicationDuringInitTask_Disabled 2


#define RBFS_uCWatchdog_Enabled  1
#define RBFS_uCWatchdog_Disabled 2

#define RBFS_RAMLayoutFragmentation_Default                    1
#define RBFS_RAMLayoutFragmentation_GRAMOptimizedForBLDR       2


#endif