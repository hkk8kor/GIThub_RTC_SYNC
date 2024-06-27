#ifndef RBSYS_STMSTELLARREGS_H__
#define RBSYS_STMSTELLARREGS_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief STM Stellar register definitions
 *
 * This interface export uC register definitions for Stellar provided by STM.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_HSWSimulation,
                          RBFS_HSWSimulation_ON,
                          RBFS_HSWSimulation_OFF);


#if( RBFS_HSWSimulation == RBFS_HSWSimulation_OFF )

  #define MC_SYSCLK_IRCOSC ((uint32)0<<0)
  #define MC_SYSCLK_XOSC   ((uint32)1<<0)
  #define MC_SYSCLK_PLL0   ((uint32)2<<0)

  #define MC_IROSC_ON      ((uint32)1<<4)
  #define MC_XOSC_ON       ((uint32)1<<5)
  #define MC_PLL0_ON       ((uint32)1<<6)
  #define MC_FLAON_NORMAL  ((uint32)3<<16) //< is non-relevant for ME_PE
  #define MC_MVR_ON        ((uint32)1<<20)
  #define MC_PDO_OFF       ((uint32)0<<23)

  #define MC_PWRLVL_0      ((uint32)0<<28)
  #define MC_PWRLVL_1      ((uint32)1<<28)

#endif

#include "Mcu_Cfg_Machine.h"
#include "rba_Reg.h"

#include RBA_REG_CAN_H
#include RBA_REG_CEM_H
#include RBA_REG_CMU_H
#include RBA_REG_CORTEXM4INTEGRATIONCS_H
#include RBA_REG_CRC_H
#include RBA_REG_DMAMUX_H
#include RBA_REG_DMA_H
#include RBA_REG_DSPI_H
#include RBA_REG_DTS_H
#include RBA_REG_FCCU2_H
#include RBA_REG_FIREWALL_H
#include RBA_REG_GIC_H
#include RBA_REG_GST_H
#include RBA_REG_GTM_H
#include RBA_REG_I2C_H
#include RBA_REG_IBCM_H
#include RBA_REG_LFAST_H
#include RBA_REG_LINFLEXD0_H
#include RBA_REG_LINFLEXD_H
#include RBA_REG_MC_CGM_DOMAIN_H
#include RBA_REG_MC_CGM_PER_H
#include RBA_REG_MC_ME_H
#include RBA_REG_MC_RGM_H
#include RBA_REG_MEMU2_H
#include RBA_REG_MSC_H
#include RBA_REG_NOC_H
#include RBA_REG_NVM_CTRL_H
#include RBA_REG_NVM_H
#include RBA_REG_OVLY_CTRL_H
#include RBA_REG_OVLY_PRAM_H
#include RBA_REG_PBRIDGE_H
#include RBA_REG_PLLDIG_H
#include RBA_REG_PMCDIG_H
#include RBA_REG_PRAM_H
#include RBA_REG_SARADCQ_H
#include RBA_REG_SARADC_H
#include RBA_REG_SDADC_H
#include RBA_REG_SIPI_H
#include RBA_REG_SIUL2_0_H
#include RBA_REG_SIUL2_2_H
#include RBA_REG_SPIQ_H
#include RBA_REG_SSCM_H
#include RBA_REG_STCU3_H
#include RBA_REG_SWT_H
#include RBA_REG_TNDCM_H
#include RBA_REG_VMID_H
#include RBA_REG_OSCAR_H

// These seem to be missing in the generated file "rba_Reg_Cfg.h"
// #include "rba_Reg_Prv_mc_rgm_domain_0_st_dev528n_c2.h"
// #include "rba_Reg_Prv_mc_rgm_domain_1_st_dev528n_c2.h"
// #include "rba_Reg_Prv_mc_rgm_domain_2_st_dev528n_c2.h"


typedef struct {
  uint32 GBL_CTRL;
  uint32 CHNL_EN;
  uint32 GBL_STATUS;
  uint32 FMSG_RDY;
  uint32 SMSG_RDY;
  uint32 ERR_STATUS_ALL;
  uint32 DATA_CTRL1;
  uint32 DATA_CTRL2;
  uint32 DATA_RESORT1;
  uint32 DATA_RESORT2;
  uint32 FDMA_CTRL;
  uint32 SDMA_CTRL;
  uint8 ADR_reserved0[4];

  uint32 FRDY_IE;
  uint32 SRDY_IE;
  uint8 ADR_reserved1[4];

  uint32 DMA_FMSG_DATA;
  uint32 DMA_FMSG_CRC;
  uint32 DMA_FMSG_TS;
  uint32 DMA_FMSG_DATA2;
  uint32 DMA_SMSG_BIT3;
  uint32 DMA_SMSG_BIT2;
  uint32 DMA_SMSG_TS;
  uint8 ADR_reserved4[4];

  struct {
    uint32 CLK_CTRL;
    uint32 STATUS;
    uint32 CONFIG;
    uint8 SENT_reserved5[4];
  } CH[15];

  uint8 ADR_reserved6[16];

  struct {
    uint32 CH_FMSG_DATA;
    uint32 CH_FMSG_CRC;
    uint32 CH_FMSG_TS;
    uint32 CH_SMSG_BIT3;
    uint32 CH_SMSG_BIT2;
    uint32 CH_SMSG_TS;
    uint8 SENT_reserved9[8];
  } CH_MSG[15];

  uint8 ADR_reserved10[28];

  uint32 CH_FMSG_DATA2[15];
  uint8 ADR_reserved11[4];

  uint32 CH_CNTR[15];
} SENT_tag;

#define SENT_0 (*(volatile SENT_tag *) 0x70ee8000)
#define SENT_1 (*(volatile SENT_tag *) 0x714e8000)

// Mapping to our names - todo: remove
#define MC_CGM_PERIPHERAL_DOMAIN  MC_CGM_PER
#define PLLDIG_PERIPHERAL_DOMAIN  PLLDIG_PER
#define Q_tag    rba_Reg_SPIQ_tst
#define SPIQ_t   rba_Reg_SPIQ_tst

#endif
