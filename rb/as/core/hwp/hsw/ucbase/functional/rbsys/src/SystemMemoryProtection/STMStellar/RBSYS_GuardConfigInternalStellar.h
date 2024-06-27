#ifndef RBSYS_GUARDCONFIGINTERNALSTELLAR_H__
#define RBSYS_GUARDCONFIGINTERNALSTELLAR_H__

  /**
    * @ingroup RBSYS
    * @{
    *
    * @file  RBSYS_GuardConfigInternalStellar.h
    * @brief
    *
    * The STM Stellar platform incorporates the memory protection function to prevent erroneous accesses to data in memories and
    * peripheral registers.
    *
    * @copyright
    * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
    * We reserve all rights of disposal such as copying and passing on to third parties.
    */

  #include "RBSYS_Config.h"

  #include "Std_Types.h"
  #include "RBSYS_Intrinsics.h"
  #include "RBSYS_uCRegisters.h"
  #include "RBSYS_GuardConfig.h"

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                            RBFS_SysEnvironment_Target,
                            RBFS_SysEnvironment_Simulation);

  /* Must be called by every core */
  static inline void RBSYS_OtherGuardsInit(void)
  {
    uint32 regValue;

    //IMP_PERIPHPREGIONR: Enable ENABLEEL2 and ENABLEEL10, todo: really needed?
    //This enables access to LLPP (low latency peripheral port = core local peripherals) for EL0-2 which e.g. contains cross core interrupts
    regValue = RBSYS_MRC(15,0,15,0,0);
    regValue |= (0x1 << 1) | 0x1;
    RBSYS_MCR(15, 0, regValue, 15, 0, 0);

    //IMP_FLASHIFREGIONR: Enable ENABLE, todo: really needed?
    //This enables the flash interface, according to the address in IMP_FLASHIFREGIONR this seems to be the code flash
    regValue = RBSYS_MRC(15,0,15,0,1);
    regValue |= 0x1;
    RBSYS_MCR(15, 0, regValue, 15, 0, 1);
  }

#if( RBFS_SysEnvironment == RBFS_SysEnvironment_Target )
  /* Must be called by every core */
  static_assert(RB_NUM_CORES <= 2, "RBSYS_LRAMGuardInit only supports 2 cores");
  static void RBSYS_LRAMGuardInit(void);
  asm void RBSYS_LRAMGuardInit(void)
  {
%lab init_tcmCore0 %lab init_tcmCore1 %lab end
    ; get core ID
    mrc p15, 0, r0, c0, c0, 5   ; Read MPIDR
    and r0, 0xFF

    ;  IMP_SLAVEPCTLR: Enable unprivileged access to core TCMs from other bus masters
    ;  Must be configured on every core
    mrc     p15, 0, r1, c11, c0, 0  ; read SLAVEPCTLR
    orr     r1, r1, (0x3)          ; Enable unprivileged access to core TCMs from other bus masters (EL0, EL1, EL2)
    mcr     p15, 0, r1, c11, c0, 0  ; write SLAVEPCTLR

    ; initialize TCMs, must be configured on every core
init_tcmCore0:
    cmp r0, RBSYS_CORE_ID_0
    bne init_tcmCore1

    ; A TCM REGION R: Load base address, Enable enable bit Enable EL2, EL1 and EL0
    movw    r0, %lo(C0_CPU0_tcma_start)
    movt    r0, %hi(C0_CPU0_tcma_start)
    orr     r0, r0, (0x7 << 2)             ; set size to 64KB
    orr     r0, r0, 0x3                    ; Enable bits EL2 and EL10
    mcr     p15, 0, r0, c9, c1, 0           ; write ATCMREGIONR

    ; B TCM REGION R: Load base address, Enable enable bit Enable EL2, EL1 and EL0
    movw    r0, %lo(C0_CPU0_tcmb_start)
    movt    r0, %hi(C0_CPU0_tcmb_start)
    orr     r0, r0, (0x5 << 2)             ; set size to 16KB
    orr     r0, r0, 0x3                    ; Enable bits EL2 and EL10
    mcr     p15, 0, r0, c9, c1, 1           ; write BTCMREGIONR

    ; C TCM REGION R: Load base address, Enable enable bit Enable EL2, EL1 and EL0
    movw    r0, %lo(C0_CPU0_tcmc_start)
    movt    r0, %hi(C0_CPU0_tcmc_start)
    orr     r0, r0, (0x5 << 2)             ; set size to 16KB
    orr     r0, r0, 0x3                    ; Enable bits EL2 and EL10
    mcr     p15, 0, r0, c9, c1, 2           ; write CTCMREGIONR

    b end
init_tcmCore1:
    ; A TCM REGION R: Load base address, Enable enable bit Enable EL2, EL1 and EL0
    movw    r0, %lo(C0_CPU1_tcma_start)
    movt    r0, %hi(C0_CPU1_tcma_start)
    orr     r0, r0, (0x7 << 2)             ; set size to 64KB
    orr     r0, r0, 0x3                    ; Enable bits EL2 and EL10
    mcr     p15, 0, r0, c9, c1, 0           ; write ATCMREGIONR

    ; B TCM REGION R: Load base address, Enable enable bit Enable EL2, EL1 and EL0
    movw    r0, %lo(C0_CPU1_tcmb_start)
    movt    r0, %hi(C0_CPU1_tcmb_start)
    orr     r0, r0, (0x5 << 2)             ; set size to 16KB
    orr     r0, r0, 0x3                    ; Enable bits EL2 and EL10
    mcr     p15, 0, r0, c9, c1, 1           ; write BTCMREGIONR

    ; C TCM REGION R: Load base address, Enable enable bit Enable EL2, EL1 and EL0
    movw    r0, %lo(C0_CPU1_tcmc_start)
    movt    r0, %hi(C0_CPU1_tcmc_start)
    orr     r0, r0, (0x5 << 2)             ; set size to 16KB
    orr     r0, r0, 0x3                    ; Enable bits EL2 and EL10
    mcr     p15, 0, r0, c9, c1, 2           ; write CTCMREGIONR
end:
  }
#else
  /* Declare assembly function as extern so that it can be stubbed in x86 testing */
  extern void RBSYS_LRAMGuardInit(void);
#endif

// All BusMaster IDs are fixed and cannot be modified
#define RBSYS_SetBusMasterIDs()


extern void RBSYS_PeripheralGuardsInit(void);

/* Content of Register FW_EL2_ERROR_TYPE_STATUS */
#define RBSYS_FIREWALL_EL2_ERRORTYPE_PARTITIONERROR        (0x1)   /* Initiator VMID does not have access to the region */
#define RBSYS_FIREWALL_EL2_ERRORTYPE_ILLEGALVMID           (0x2)   /* Access from Non-R52 Master having same VMID has Hypervisor */
#define RBSYS_FIREWALL_EL2_ERRORTYPE_MEMORYMISMATCH        (0x4)   /* R52 MPU setting does not match the MEM_TYPE field of the region */
#define RBSYS_FIREWALL_EL2_ERRORTYPE_VMIDPRIVILEGEMISMATCH (0x8)   /* Hypervisor does not have privilege access */
#define RBSYS_FIREWALL_EL2_ERRORTYPE_TXINVALID             (0x10)  /* Master is initiating access to outside of boundary */
#define RBSYS_FIREWALL_EL2_ERRORTYPE_UNSAFEHVACCESS        (0x20)  /* An UNSAFE R52 with HV mode is accessing a SAFE region */
#define RBSYS_FIREWALL_EL2_ERRORTYPE_UNSAFEMSTRACCESS      (0x40)  /* An UNSAFE R52 w/o HV mode is accessing a SAFE region */
#define RBSYS_FIREWALL_EL2_ERRORTYPE_REGIONNOTHIT          (0x80)  /* No Firewall region is configured for the target address */
#define RBSYS_FIREWALL_EL2_ERRORTYPE_MULTIREGION           (0x100) /* Multiple Firewall regions are configured for the target address */

/* Content of Register FW_EL1_ERROR_TYPE_STATUS */
#define RBSYS_FIREWALL_EL1_ERRORTYPE_READACCESS            (0x1)   /* Master does not have read access to the region */
#define RBSYS_FIREWALL_EL1_ERRORTYPE_WRITEACCESS           (0x2)   /* Master does not have write access to the region */
#define RBSYS_FIREWALL_EL1_ERRORTYPE_EXECACCESS            (0x4)   /* Master does not have execution access to the region */
#define RBSYS_FIREWALL_EL1_ERRORTYPE_REGIONNOTHIT          (0x8)   /* No Firewall region is configured for the target address */
#define RBSYS_FIREWALL_EL1_ERRORTYPE_TXINVALID             (0x10)  /* Master is initiating access to outside of boundary */
#define RBSYS_FIREWALL_EL1_ERRORTYPE_MULTIREGION           (0x20)  /* Multiple Firewall regions are configured for the target address */


#define RBSYS_FIREWALL_CONFIG_ENABLE    (0x1)
#define RBSYS_FIREWALL_CONFIG_DISABLE   (0x0)
#define RBSYS_FIREWALL_EL1_CONF_ENABLE  (0x1)
#define RBSYS_FIREWALL_EL1_CONF_DISABLE (0x0)
#define RBSYS_FIREWALL_EL2_CONF_ENABLE  (0x1)
#define RBSYS_FIREWALL_EL2_CONF_DISABLE (0x0)


#define RBSYS_FIREWALL_EL1_MSTRACC_BLOCKED (0x0)
#define RBSYS_FIREWALL_EL1_MSTRACC_R       (0x1)
#define RBSYS_FIREWALL_EL1_MSTRACC_RW      (0x3)
#define RBSYS_FIREWALL_EL1_MSTRACC_RX      (0x5)

/* Access to GRAM is protected via R52-MPU and via NOC for any outside modules
 *  - MPU: Not relevant, as this can only be configured by the specific Cluster CPU
 *  - NOC: Registers can only be written by R52 itself (which is safe) */
#define RBSYS_PBUSGuardInit_ForGRAMGuard()

extern void RBSYS_GRAMGuardInit_Impl(void);




/** @} */
/* End ingroup RBSYS */

#endif