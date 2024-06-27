#ifndef RBSYS_CONFIGELEMENTS_H__
#define RBSYS_CONFIGELEMENTS_H__

/**
 * @file
 * @brief Provides RBSYS specific switch settings for project configuration
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */



/** @addtogroup HSW_uCBase_ConfigElements
    @{

      @defgroup HSW_RBSYS_ConfigElements RBSYS Start-up and OS handling
      @brief RBSYS encapsulates the operating system port (RTA-OS from ETAS) and provides the taskscheme.
      It handles furthermore the system start-up and uC configuration involved with this job.
    @}
*/

  /**
    @addtogroup HSW_RBSYS_ConfigElements
    @{
  */

  /** @defgroup RBFS_SYSDebugFeatures RBSYS debug features

  RBSYS specific debug feature will be set to _OFF for RBFS_BUILDTYPE_RELEASE.
  Using a different setting for this build type is prohibited!

  @{
  */

  /** RBSYS specific debug features enabled */
  #define RBFS_SYSDebugFeatures_ON   1

  /** RBSYS specific debug features disabled */
  #define RBFS_SYSDebugFeatures_OFF  2

  /** @} */ // ingroup  RBFS_SYSDebugFeatures



  /** @defgroup RBFS_SysSystemLoadCalc RBSYS SystemLoad calculation

  RBSYS specifies the update rate of the SystemLoad calculation from rba_runtime.
  The options for our Brake Systems are either fine grained updates every 20 ms to detect peak
  situations or updates every 120ms as average time related to our lowest prio task (x24).
  For VMPS only a third option with 1000ms was introduced to cover their task scheme extension.

  @{
  */

  /** RBSYS SystemLoad calculated each 20ms (calculation every second x2) */
  #define RBFS_SysSystemLoadCalc_20ms   1

  /** RBSYS SystemLoad calculated each 120ms (calculation every twelfth x2) */
  #define RBFS_SysSystemLoadCalc_120ms  2

  /** RBSYS SystemLoad calculated each 1000ms (calculation every hundredth x2 - only for VMPS) */
  #define RBFS_SysSystemLoadCalc_1000ms  3

  /** @} */ // ingroup  RBFS_SysSystemLoadCalc



  /** @defgroup RBFS_BootblockSysStartupCode RBSYS start-up Code for bootblock

  This switch configures the availability of the RBSYS provided start-up code for bootblock builds.
  The setting depends on the usage of a boot loader in combination with or without a boot manager:

  1.) Boot manager & boot loader:
        Only boot manager needs to activate the start-up code

  2.) Only boot loader (without boot manager):
        Boot loader needs to activate the start-up code

  To be configured by Bootblock-PR.

  @{
  */

  /** RBSYS start-up code active in bootblock */
  #define RBFS_BootblockSysStartupCode_ON 1

  /** RBSYS start-up code inactive in bootblock */
  #define RBFS_BootblockSysStartupCode_OFF  2

  /** @} */ // ingroup  RBFS_BootblockSysStartupCode



  /** @defgroup RBFS_FlxrTaskSync RBSYS FlexRay Task Synchronization

  On FlexRay systems this switch enables the possibility/interface
  to synchronize the task scheme to the FlexRay bus time.

  To be configured by NET-PR.

  Hint: deprecated, use RBFS_TaskSync below.

  @{
  */

  /** Default: Task scheme based on system timer (normal SYS scheduling). */
  #define RBFS_FlxrTaskSync_OFF 1

  /** Since this task scheme synchronization to FlexRay can
      alter SYS task scheduling, it is preferred not to use. */
  #define RBFS_FlxrTaskSync_ON  2

  /** @} */ // ingroup  RBFS_FlxrTaskSync



  /** @defgroup RBFS_TaskSync RBSYS Task Synchronization

  This switch enables the possibility/interface
  to synchronize the task scheme to an arbitrary bus time.

  To be configured by NET-PR.

  @{
  */

  /** Default: Task scheme based on system timer (normal SYS scheduling). */
  #define RBFS_TaskSync_OFF 1

  /** Since this task scheme synchronization can
      alter SYS task scheduling, it is preferred not to use. */
  #define RBFS_TaskSync_ON  2

  /** @} */ // ingroup  RBFS_TaskSync



  /** @defgroup RBFS_TPSWCapsule RBSYS Third Party Software

  This switch configures the availability of the Third Party Software (TPSW) framework,
  which provides the APIs and functionality to integrate TPSW with a corresponding MPU
  capsules.

  Hint: For details about this feature see TPSW Capsule design document (in RBSYS folder)
  Hint: Enhanced Isolation is active within RTAOS (since ALM Epic 1538627) and therefore redundant checks have been removed with ALM Task 2390947

  To be configured by CSW-PR.

  @{
  */

  /** Third party SW capsule disabled */
  #define RBFS_TPSWCapsule_OFF      1

  /** Third party SW capsule support: Memory protection */
  #define RBFS_TPSWCapsule_SC3      2

  /** Third party SW capsule support: Memory + Runtime protection */
  #define RBFS_TPSWCapsule_SC4      3

  /** @} */ // ingroup  RBFS_TPSWCapsule



  /** @defgroup RBFS_TPSWTestsuite RBSYS Third Party Software testsuite

  This switch configures the availability of the Third Party Software (TPSW) testsuite,
  which is only used for development purpose.

  Hint: Take care - setting must be _OFF in case of customer project or of course series builds!
  Therefore the switch will be configured per default to RBFS_TPSWTestsuite_OFF

  To be configured only by RBSYS-CR (disabled per default)

  @{
  */

  /** TPSW test suite disabled */
  #define RBFS_TPSWTestsuite_OFF  1

  /** TPSW test suite including testcases enabled */
  #define RBFS_TPSWTestsuite_ON   2

  /** @} */ // ingroup  RBFS_TPSWTestsuite



  /** @defgroup RBFS_SysSignalOsArVersion RBSYS OS AUTOSAR version

  At least EcuM is strongly coupled to AR version defines.
  RBSYS will therefore signal different versions, because from
  API and functionality the latest is always usable
  just the version is signalled as required.

  More projects are based on 4.0.2 therefore default currently configured
  to this. Nevertheless the impact is just two allow compilation of components
  having coupled there release to OS-AR-Version. There is no functional impact.

  @{
  */

  /** OS AUTOSAR 4.0.2 */
  #define RBFS_SysSignalOsArVersion_4x0x2 1
  /** OS AUTOSAR 4.2.2 */
  #define RBFS_SysSignalOsArVersion_4x2x2 2
  /** OS AUTOSAR 4.5.0 */
  #define RBFS_SysSignalOsArVersion_4x5x0 3

  /** @} */ // ingroup  RBFS_SysSignalOsArVersion



  /** @defgroup RBFS_TPSWSVPRestrictions RBSYS Third Party Software supervisor mode restrictions

  This switch configures the availability of additional memory access restrictions in supervisor mode.
  Additional CPU supervisor mode restrictions are:
   - MPM.SVP = 1 (=> MPU active in supervisor mode)
   - whole RAM non-executable

  To be configured by CSW-PR (only after discussion with RBSYS-CR)

  @{
  */

  /** TPSW supervisor mode restrictions disabled (default) */
  #define RBFS_TPSWSVPRestrictions_OFF  1
  /** TPSW supervisor mode restrictions enabled */
  #define RBFS_TPSWSVPRestrictions_ON   2

  /** @} */ // ingroup  RBFS_TPSWSVPRestrictions



  /** @defgroup RBFS_SysHsmSharedGRAMsize RBSYS size of GRAM shared between PEs and HSM (ICU-M)

  This switch configures the size of GRAM shared between PEs and HSM (ICU-M).
  It is only relevant in case of RBFS_RenesasP1xGRAM_ON  && RBFS_HardwareSecurityModule_Supported.

  @{
  */

  /** Shared GRAM with HSM is of size 0K -> No shared GRAM */
  #define RBFS_SysHsmSharedGRAMsize_0K    1
  /** Shared GRAM with HSM is of size 16K */
  #define RBFS_SysHsmSharedGRAMsize_16K   2
  /** Shared GRAM with HSM is of size 32K */
  #define RBFS_SysHsmSharedGRAMsize_32K   3

  /** @} */ // ingroup  RBFS_SysHsmSharedGRAMsize



  /** @defgroup RBFS_SysMaxTaskx1Jitter RBSYS x1 task jitter monitoring threshold

  This switch configures the max. allowed jitter of the IO sensitive part within the x1 task.
  For the max. allowed task scheme adaptation see #RBSYS_TASKSCHEME_ADJUST_MAX_PERCENT.

  @{
  */

  /** 5% + max task scheme adaptation of task x1 is jitter monitored */
  #define RBFS_SysMaxTaskx1Jitter_5         1

  /** 15% + max task scheme adaptation of task x1 is jitter monitored */
  #define RBFS_SysMaxTaskx1Jitter_15        2

  /** Series setting of jitter monitoring:
      Jitter is still available on measurement variable, but failure
      reporting is disabled (therefore no percentage info required) */
  #define RBFS_SysMaxTaskx1Jitter_SERIES    3


  /** @} */ // ingroup  RBFS_SysMaxTaskx1Jitter

  /** @defgroup RBFS_SysOverwriteEBASE RBSYS EBASE Manipulation API

  Setting this switch to _ON will enable the interface to change EBASE (Exception Vector Base Address)

  @{
  */
  /** The standard CC-AS strategy concerning interrupt vector table is that bootmanager/bootloader routes the
    interrupts and exceptions directly to application software and therefore the EBASE
    (exception base register) is configured to address 0 within the OS (which is also the HW default).

    - This concept will not work for special usecases like the pTSW, which includes two separate SW builds -
    one ePSW and one TC-SW build. The bootmanager will route his interrupt vectors only to one (default) partition,
    therefore it's neccessary to overwrite the EBASE register at least for the other partition.

    - Another usecase could be a bootmanger, which does not route the interrupt vectors to the application.
    This could be the case on CC-PS products like VMPS or MMP2.

    - In FOTA Enhanced flash bank A can be programmed during normal operation, so the interrupt vector must
    be positioned on flash bank B.
  */

  /** Overwrite EBASE register from OS configuration (see above) */
  #define RBFS_SysOverwriteEBASE_ON     1
  /** Do not overwrite EBASE register from OS configuration (default) */
  #define RBFS_SysOverwriteEBASE_OFF    2

  /** @} */ // ingroup  RBFS_SysOverwriteEBASE



  /** @defgroup RBFS_SysEthernetSupport RBSYS support for Ethernet module

  Setting this switch to _ON will provide a SYS configuration which supports Ethernet:

  The support includes the feature(s):

   - Enables the Ethernet module via Flash Option Bytes

  @{
  */

  /** Ethernet support in RBSYS is enabled */
  #define RBFS_SysEthernetSupport_ON     1
  /** Ethernet support in RBSYS is disabled */
  #define RBFS_SysEthernetSupport_OFF    2

  /** @} */ // ingroup  RBFS_SysEthernetSupport



  /** @defgroup RBFS_SysEthSharedGRAMsize RBSYS size of GRAM shared between PEs and Ethernet

   * - shared RAM for access by the unsafe Ethernet client on D3/D4/D5. This switch configures the size of GRAM shared between PEs and Ethernet.

  @{
  */

  /** Shared GRAM with Ethernet is of size 0K -> No shared GRAM with Ethernet */
  #define RBFS_SysEthSharedGRAMsize_0K    1
  /** Shared GRAM with Ethernet is of size 32K */
  #define RBFS_SysEthSharedGRAMsize_32K   2
  /** Shared GRAM with Ethernet is of size 64K */
  #define RBFS_SysEthSharedGRAMsize_64K   3
  /** Shared GRAM with Ethernet is of size 96K - Attention: This setting is not available for M3/M6. Choose 128K instead. */
  #define RBFS_SysEthSharedGRAMsize_96K   4
  /** Shared GRAM with Ethernet is of size 128K */
  #define RBFS_SysEthSharedGRAMsize_128K  5

  /** @} */ // ingroup  RBFS_SysEthSharedGRAMsize




  /** @defgroup RBFS_RestrictedExclusiveGRAMsize RBSYS size of GRAM exclusive for the Restricted SPID

  This switch configures the size of GRAM exclusive for the Restricted SPID.

  Restricted Exclusive GRAM will always be accessible to read accesses.
  Hint: P1x does not support restricting read accesses. U2A would support read AND write restriction but read is granted
  in general to have the same behavior.

  IMPORTANT: It will also be forwarded via the RBSYS_GuardMemoryMap.h interface to RAMSafety!

  @{
  */

  /** Exclusive GRAM for the Restricted SPID is of size 0K -> No exclusive GRAM for the Restricted SPID */
  #define RBFS_RestrictedExclusiveGRAMsize_0K    1
  /** Exclusive GRAM for the Restricted SPID is of size 16K - Attention: This setting is not available for U2A. Choose 64/128/256K instead.  */
  #define RBFS_RestrictedExclusiveGRAMsize_16K   2
  /** Exclusive GRAM for the Restricted SPID is of size 32K - Attention: This setting is not available for U2A. Choose 64/128/256K instead.  */
  #define RBFS_RestrictedExclusiveGRAMsize_32K   3
  /** Exclusive GRAM for the Restricted SPID is of size 64K - Attention: This setting is only available for U2A-M2. */
  #define RBFS_RestrictedExclusiveGRAMsize_64K   4
  /** Exclusive GRAM for the Restricted SPID is of size 128K - Attention: This setting is only available for U2A-M3. */
  #define RBFS_RestrictedExclusiveGRAMsize_128K  5
  /** Exclusive GRAM for the Restricted SPID is of size 256K - Attention: This setting is only available for U2A-M6. */
  #define RBFS_RestrictedExclusiveGRAMsize_256K  6


  /** @} */ // ingroup  RBFS_RestrictedExclusiveGRAMsize



  /** @defgroup RBFS_SysHSMsharedGRAM RBSYS attribute to specify the shared GRAM partner of HSM

  This specifies the shared GRAM partner of HSM.

  @{
  */

  /** HSM shares its GRAM with the Host using RBSYS_SPID_SAFE (default) */
  #define RBFS_SysHSMsharedGRAM_Host         1
  /** HSM shares its GRAM with the Restricted SPID (RBSYS_SPID_RESTRICTED) */
  #define RBFS_SysHSMsharedGRAM_Restricted   2

  /** @} */ // ingroup  RBFS_SysHSMsharedGRAM


  /** @defgroup RBFS_TriggerTimerSupport RBSYS setting to enable TriggerTimer interfaces

  This feature, although generic, is used by project MMP2 to trigger SPI transmission at a certain time.
  (background: Sensor data has to be read out via SPI in equidistant time steps.)
  @{
  */

  /** TriggerTimer is supported / interfaces are available */
  #define RBFS_TriggerTimerSupport_On  1
  /** TriggerTimer is not supported */
  #define RBFS_TriggerTimerSupport_Off 2

  /** @} */ // ingroup  RBFS_TriggerTimerSupport


  /** @defgroup RBFS_SysResettableSlackTimesSupport RBSYS setting to enable resettable SlackTimeMin

  This feature is used to measure SlackTimeMin for different driving scenarios without the need to reset
  the SlackTimeMin by a Power Cycle.
  @{
  */

  /** Resettable SlackTimeMin is supported and interfaces are enabled */
  #define RBFS_SysResettableSlackTimesSupport_ON  1
  /** Resettable SlackTimeMin is not supported */
  #define RBFS_SysResettableSlackTimesSupport_OFF 2

  /** @} */ // ingroup  RBFS_SysResettableSlackTimesSupport


  /** @defgroup RBFS_RBSYSGlobalRAMGuardsBB RBSYS setting to enable RAM guards for GRAM/CRAM in Bootblock

  @{
  */

  /** RAM guards for GRAM/CRAM in Bootblock are enabled */
  #define RBFS_RBSYSGlobalRAMGuardsBB_ON  1
  /** RAM guards for GRAM/CRAM in Bootblock are NOT enabled */
  #define RBFS_RBSYSGlobalRAMGuardsBB_OFF 2

  /** @} */ // ingroup  RBFS_RBSYSGlobalRAMGuardsBB


  /** @defgroup RBFS_RBSYSSecureBootStartup RBSYS setting (derived only) indicating whether HSM or Host is started first

  @{
  */

  /** HSM will start the host core once software is validated */
  #define RBFS_RBSYSSecureBootStartup_HSMonly    1
  /** Host Core has to be started at startup */
  #define RBFS_RBSYSSecureBootStartup_HSMandHost 2

  /** @} */ // ingroup  RBFS_RBSYSSecureBootStartup




  /** @defgroup RBFS_CPUMisalignedAccessSupport Setting to allow misaligned accesses by CPU

  @{
  */

  /** Misaligned accesses are allowed */
  #define RBFS_CPUMisalignedAccessSupport_ON    1
  /** Misaligned accesses are forbidden -> Reaction: e.g. MAE Exception */
  #define RBFS_CPUMisalignedAccessSupport_OFF   2

  /** @} */ // ingroup  RBFS_CPUMisalignedAccessSupport




  /** @defgroup RBFS_CpuClockRestriction Setting to allow restricted CPU clock configurations (e.g. 240MHz on certain D3 devices)

  Attention: Only MMP2 is allowed to set RBFS_CpuClockRestriction_OFF, as they have confirmed that this thermal restriction does not apply in their case.
             Brake systems are only allowed to set RBFS_CpuClockRestriction_OFF if this is allowed by the HW-PCM (and this is allowed by realiability team 
               -> thermal assessment required ).

  @{
  */

  /** Restricted CPU clocks are forbidden */
  #define RBFS_CpuClockRestriction_Default    1
  /** Restricted CPU clocks are allowed */
  #define RBFS_CpuClockRestriction_OFF        2

  /** @} */ // ingroup  RBFS_CpuClockRestriction



  /** @defgroup RBFS_SysUnittestSimulationModel Setting to switch on HW simulation models for unittests

  Attention: Must only be set by RBSYS itself for Unittesting purpose!!

  @{
  */

  /** Use Unittest Simulation Callbacks for RBSYS Internal Testing */
  #define RBFS_SysUnittestSimulationModel_ON    1
  /** Do not use Unittest Simulation Callbacks for RBSYS Internal Testing */
  #define RBFS_SysUnittestSimulationModel_OFF   2

  /** @} */ // ingroup  RBFS_SysUnittestSimulationModel



  /** @} */ // ingroup  HSW_RBSYS_ConfigElements

#endif /* End of multiple include protection */
