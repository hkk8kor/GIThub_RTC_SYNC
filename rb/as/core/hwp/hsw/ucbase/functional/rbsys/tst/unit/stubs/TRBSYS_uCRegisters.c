#include "SwTest_Global.h"                      // for SWT functionality

#include "TRBSYS_uCRegisters.h"
#include "RBSYS_Config.h"

/* stub uC registers */
#if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  volatile uint32 EIBD41  = 0;
  volatile uint32 EIBD42  = 0;
  volatile uint32 EIBD43  = 0;
#elif ( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  volatile uint32 INTC2EIBD221  = 0;
  volatile uint32 INTC2EIBD222  = 0;
  volatile uint32 INTC2EIBD223  = 0;
#elif ( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  volatile SENT_t SENT_0;
#endif

#if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  uint16 EICn[214] = {0};
#else
  uint16 INTC2EICn[685] = {0};
#endif


#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  volatile uint32 MSR_LM3  = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 MSR_LM4  = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 MSR_LM5  = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 MSR_LM6  = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 MSR_LM7  = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 MSR_LM8  = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 MSR_LM10 = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 MSR_LM11 = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 MSR_LM12 = TRBSYS_DUMMY_DEFAULT;

  volatile uint32 SWLRESS3  = 0;
  volatile uint32 SWLRESS4  = 0;
  volatile uint32 SWLRESS5  = 0;
  volatile uint32 SWLRESS6  = 0;
  volatile uint32 SWLRESS7  = 0;
  volatile uint32 SWLRESS8  = 0;
  volatile uint32 SWLRESS10 = 0;
  volatile uint32 SWLRESS11 = 0;
  volatile uint32 SWLRESS12 = 0;

  volatile uint32 GREG8  = 0;
  volatile uint32 OPBT0  = 0;
  volatile uint32 OPBT1  = 0;
  volatile uint32 OPBT14 = 0;
  volatile uint32 OPBT15 = 0;
#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) 
  volatile uint32 SYSCTRLMSRKCPROT = 0;

  volatile uint32 SYSCTRLMSR_RSCFD    = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_GTM      = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_RSENT    = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_MSPI     = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_RLIN3    = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_ADCJ_AWO = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_ADCJ_ISO = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_ETNB     = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_FLXA     = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_RHSIF    = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_TAUD     = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_OSTM     = TRBSYS_DUMMY_DEFAULT;

  volatile uint32 SYSCTRLSWMRESS_RSCFD    = 0;
  volatile uint32 SYSCTRLSWMRESS_GTM      = 0;
  volatile uint32 SYSCTRLSWMRESS_RSENT    = 0;
  volatile uint32 SYSCTRLSWMRESS_MSPI     = 0;
  volatile uint32 SYSCTRLSWMRESS_RLIN3    = 0;
  volatile uint32 SYSCTRLSWMRESS_ADCJ_AWO = 0;
  volatile uint32 SYSCTRLSWMRESS_ADCJ_ISO = 0;
  volatile uint32 SYSCTRLSWMRESS_FLXA     = 0;
  volatile uint32 SYSCTRLSWMRESS_ETNB     = 0;
  volatile uint32 SYSCTRLSWMRESS_RHSIF    = 0;
  volatile uint32 SYSCTRLSWMRESS_TAUD     = 0;
  volatile uint32 SYSCTRLSWMRESS_OSTM     = 0;
#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)

  volatile uint32 SYSCTRLMSRKCPROT = 0;

  volatile uint32 SYSCTRLMSR_RSCFD    = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_GTM      = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_RSENT    = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_MSPI     = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_RLIN3    = TRBSYS_DUMMY_DEFAULT;
  
  volatile uint32 SYSCTRLMSR_ADCK_AWO = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_ADCK_ISO = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_FLXA     = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_ETN_T1S  = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_ETN      = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_TAUD     = TRBSYS_DUMMY_DEFAULT;
  volatile uint32 SYSCTRLMSR_OSTM     = TRBSYS_DUMMY_DEFAULT;

  volatile uint32 SYSCTRLSWMRESS_RSCFD    = 0;
  volatile uint32 SYSCTRLSWMRESS_GTM      = 0;
  volatile uint32 SYSCTRLSWMRESS_RSENT    = 0;
  volatile uint32 SYSCTRLSWMRESS_MSPI     = 0;
  volatile uint32 SYSCTRLSWMRESS_RLIN3    = 0;
  volatile uint32 SYSCTRLSWMRESS_ADCK_AWO = 0;
  volatile uint32 SYSCTRLSWMRESS_ADCK_ISO = 0;
  volatile uint32 SYSCTRLSWMRESS_FLXA     = 0;
  volatile uint32 SYSCTRLSWMRESS_ETN_T1S  = 0;
  volatile uint32 SYSCTRLSWMRESS_ETN      = 0;
  volatile uint32 SYSCTRLSWMRESS_TAUD     = 0;
  volatile uint32 SYSCTRLSWMRESS_OSTM     = 0;
#endif

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  uint16 TAUD0TT      = 0x0;
  uint16 TAUD0TE      = 0x5555u;
  uint8  TAUD0CSR0    = 0x0;
  uint16 TAUD0CDR0    = 0x0;
  uint16 TAUD0CMORx[32] = {0,0,0x4000,0,0,0x4000,0,0,0x4000,0,0,0x4000,0,0,0x4000,0,0,0x4000,0,0,0x4000,0,0,0x4000};
  uint8  TAUD0CMUR0   = 0x0;
  uint16 TAUD0TS      = 0x0;
  uint16 TAUD0TPS     = 0x0;
  uint32 PIC1REG31    = 0x0;
  uint32 PIC1REG30    = 0xFFFFFFFFu;
  uint32 PIC1TAUD0SEL = 0xFFFFFFFFu;
  uint8  PIC1INI01    = 0x2;
#endif

/* stub uC registers */
uint32 CLKD0DIV     = 1u;
uint32 pysCLKD0STAT = 3u;

uint32 CLKD1DIV     = 1u;
uint32 pysCLKD1STAT = 3u;

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )

  uint32 CLKD2DIV     = 1u;
  uint32 CKSC2C       = 4u;
  uint32 pysCLKD2STAT = 3u;

#elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

  uint32 SYSCTRLCLKKCPROT1  = 0u;
  uint32 SYSCTRLCKSC_CPUC   = 1u;
  uint32 SYSCTRLCKSC_CPUS   = 1u;
  uint32 SYSCTRLMOSCE       = 0u;
  uint32 SYSCTRLMOSCS       = 0u;
  uint32 SYSCTRLPLLE        = 0u;
  uint32 SYSCTRLPLLS        = 0u;
  uint32 SYSCTRLCLKD_PLLC   = 1u;
  uint32 SYSCTRLCLKD_PLLS   = 3u;
  uint32 SYSCTRLCLKD_HSIOSCS = 0u;
  uint32 SYSCTRLCLKD_HSIOSCC = 0u;

  uint32 SYSCTRLCKSC_SSCGC   = 1u;
  uint32 SYSCTRLCLKD_SSCGC   = 0u;
  uint32 SYSCTRLCKSC_SSCGS   = 1u;
  uint32 SYSCTRLCLKD_SSCGS   = 2u;

  uint32 SYSCTRLCKSC_FOUT0C = 1u;
  uint32 SYSCTRLCKSC_FOUT0S = 1u;
  uint32 SYSCTRLCLKD_FOUT0C = 0u;
  uint32 SYSCTRLCLKD_FOUT0S = 1u;

  uint32 SYSCTRLCKSC_EXTCLK0C = 4u;
  uint32 SYSCTRLCKSC_EXTCLK0S = 4u;
  uint32 SYSCTRLCLKD_EXTCLK0C = 0u;
  uint32 SYSCTRLCLKD_EXTCLK0S = 1u;

  uint32 SYSCTRLCKSC_WDTS = 0u;

#endif


static uint32 TRBSYS_CLKD0STAT_ReadCnt = 0u;
static uint32 TRBSYS_CLKD1STAT_ReadCnt = 0u;
static uint32 TRBSYS_CLKD2STAT_ReadCnt = 0u;

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
uint32 TRBSYS_ReadCLKD0STAT(void)
{
  TRBSYS_CLKD0STAT_ReadCnt++;
  return pysCLKD0STAT;
}

uint32 TRBSYS_ReadCLKD1STAT(void)
{
  TRBSYS_CLKD1STAT_ReadCnt++;
  return pysCLKD1STAT;
}

uint32 TRBSYS_ReadCLKD2STAT(void)
{
  TRBSYS_CLKD2STAT_ReadCnt++;
  return pysCLKD2STAT;
}

int TRBSYS_GetReadCnt_CLKD0STAT(void)
{
  return TRBSYS_CLKD0STAT_ReadCnt;
}

int TRBSYS_GetReadCnt_CLKD1STAT(void)
{
  return TRBSYS_CLKD1STAT_ReadCnt;
}

int TRBSYS_GetReadCnt_CLKD2STAT(void)
{
  return TRBSYS_CLKD2STAT_ReadCnt;
}

#endif

#include "TRBSYS_Intrinsics.h"

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  /* stub uC registers */
  uint32 GRAMC_WTBCONFIG0 = 1u;
  static uint32 TRBSYS_GRAMC_WTBCONFIG2_ReadCnt = 0u;


  boolean TRBSYS_ReadWTBCONFIG2(void)
  {
    // ensure that SYNCM is called before
    if (TRBSYS_Get_SYNCM_CNT() == 1)
    {
      TRBSYS_GRAMC_WTBCONFIG2_ReadCnt++;
    }

    return TRUE;
  }


  int TRBSYS_GetReadCnt_WTBCONFIG2(void)
  {
    return TRBSYS_GRAMC_WTBCONFIG2_ReadCnt;
  }
#endif

/* stub uC registers */
#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  uint32 STM0TS = 0;
  uint32 STM0TT = 0;
  uint32 STM0CSTR = 0;
  uint32 STM0CKSEL = 0;
  uint32 STM0CNT1 = 0;
  uint32 STM0CNT2 = 0;
  uint32 STM0CNT0L = 0;
  uint32 STM0CNT0H = 0;
  uint32 STM0CMP0AL = 0;
  uint32 STM0CMP0AH = 0;
  uint32 STM0IS = 0;
  uint32 STM0RM = 0;
  uint32 STM0STC = 0;
  uint32 STM0CMP1A = 0;
  uint32 STM0CMP1B = 0;
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  uint32 TPTMPE0TPTM0USTP   = 0;
  uint32 TPTMPE0TPTM0USTR   = 0;
  uint32 TPTMPE0TPTM0URRUN  = 0;
  uint32 TPTMPE0TPTM0URUN = 0;
  uint32 TPTMPE0TPTM0UIEN = 0;
  uint32 TPTMPE0TPTM0UDIV = 0;
  uint32 TPTMPE0TPTM0UCNT0 = 0;
  uint32 TPTMPE0TPTM0UCNT1 = 0;
  uint32 TPTMPE0TPTM0UCMP00;
  uint32 TPTMPE0TPTM0UCMP01;
#endif



#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  volatile uint32 RESF;
  volatile uint32 RESFC;
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  volatile uint32 SYSCTRLRESF;
  volatile uint32 SYSCTRLRESFC;
#endif

uint32 STAC_LM0 = 0;
uint32 STAC_GRAM = 0;
uint32 SWARESA0 = 0;
uint32 SWSRESA0 = 0;
uint32 SYSCTRLRESKCPROT0 = 0;
uint32 SYSCTRLSWARESA = 0;
uint32 SYSCTRLSWSRESA = 0;
uint32 BSEQ0CTL = 0;
uint32 SYS0BSEQ0CTL = 0;

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  uint32 BOOTCTRL = 0;
#endif

#if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  uint32 SYSCTRLBOOTCTRL = 0;
#endif

#if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  uint32 PRDNAME2 = 0;
  uint32 PRDNAME3 = 0;
  uint32 PRDSEL3 = 0;
#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  uint32 PRDINFFPRDNAME2 = 0;
  uint32 PRDINFFPRDNAME3 = 0;
  uint32 PRDINFFPRDNUM = 0;
#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
  uint32 PRDINFfPRDNAME2 = 0;
  uint32 PRDINFfPRDNAME3 = 0;
  uint32 PRDINFfPRDNUM = 0;
#endif

#if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  uint32 CHIPID1LL = 0;
  uint32 CHIPID1LH = 0;
  uint32 CHIPID1HL = 0;
  uint32 CHIPID1HH = 0;
#endif


#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )

uint32 PEGG0MK = 0;
uint32 PEGG0SP = 0;
uint32 PEGG1MK = 0;
uint32 PEGG1SP = 0;

uint32 PEGG0BA = 0;
uint32 PEGG1BA = 0;
uint32 PEGG2BA = 0;
uint32 PEGG3BA = 0;
uint32 PEGG4BA = 0;
uint32 PEGG5BA = 0;
uint32 PEGG6BA = 0;
uint32 PEGG7BA = 0;

uint32 MGDGRBAD0;
uint32 MGDGRADV0;
uint32 MGDGRSPID0;
uint32 MGDGRPROT0;
uint32 MGDGRBAD1;
uint32 MGDGRADV1;
uint32 MGDGRSPID1;
uint32 MGDGRPROT1;
uint32 MGDGRBAD2;
uint32 MGDGRADV2;
uint32 MGDGRSPID2;
uint32 MGDGRPROT2;
uint32 MGDGRBAD3;
uint32 MGDGRADV3;
uint32 MGDGRSPID3;
uint32 MGDGRPROT3;
uint32 MGDGRBAD4;
uint32 MGDGRADV4;
uint32 MGDGRSPID4;
uint32 MGDGRPROT4;
uint32 MGDGRBAD5;
uint32 MGDGRADV5;
uint32 MGDGRSPID5;
uint32 MGDGRPROT5;
uint32 MGDGRBAD6;
uint32 MGDGRADV6;
uint32 MGDGRSPID6;
uint32 MGDGRPROT6;
uint32 MGDGRBAD7;
uint32 MGDGRADV7;
uint32 MGDGRSPID7;
uint32 MGDGRPROT7;

uint32 APBFSGDPROT_PDMACM_A;
uint32 APBFSGDPROT_PDMACM_B;
uint32 APBFSGDPROT_PDMACH_A;
uint32 APBFSGDPROT_PDMACH_B;
uint32 APBFSGDPROT_INTC2_A;
uint32 APBFSGDPROT_INTC2_B;
uint32 APBFSGDPROT_PBG_A;
uint32 APBFSGDPROT_PBG_B;
uint32 APBFSGDPROT_SP1_A;
uint32 APBFSGDPROT_SP1_B;
uint32 APBFSGDPROT_SP2_A;
uint32 APBFSGDPROT_SP2_B;
uint32 APBFSGDPROT_SP4_A;
uint32 APBFSGDPROT_SP4_B;

uint32 APBFSGDSPID_PDMACM_A;
uint32 APBFSGDSPID_PDMACM_B;
uint32 APBFSGDSPID_PDMACH_A;
uint32 APBFSGDSPID_PDMACH_B;
uint32 APBFSGDSPID_INTC2_A;
uint32 APBFSGDSPID_INTC2_B;
uint32 APBFSGDSPID_PBG_A;
uint32 APBFSGDSPID_PBG_B;
uint32 APBFSGDSPID_SP1_A;
uint32 APBFSGDSPID_SP1_B;
uint32 APBFSGDSPID_SP2_A;
uint32 APBFSGDSPID_SP2_B;
uint32 APBFSGDSPID_SP4_A;
uint32 APBFSGDSPID_SP4_B;


__type100 FSGD1A;
__type101 FSGD1B;
__type96  FSGD2A;
__type105 FSGD3A;
__type101 FSGD3B;
__type105 FSGD4A;
__type96  FSGD4B;
__type96  FSGD4C;
__type76  FSGD5A;
__type78  FSGD5B;
__type79  FSGD5C;
__type78  FSGD5D;

T_FSGDF0  FSGDE0;  /* E and F have the same type */
T_FSGDF0  FSGDE1;
T_FSGDF0  FSGDF0;
T_FSGDF0  FSGDF1;
T_FSGDM0  FSGDM0;


__type111 HSSPID;

#else

/*    U2A  Register stubbing */

T_GUARD_PE0CL0 GUARD_PE0CL0;
uint32 GUARD_PE0CL0PEGKCPROT;
T_GUARD_PE1CL0 GUARD_PE1CL0;
uint32 GUARD_PE1CL0PEGKCPROT;


#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  T_PBG00 PBG00;
  uint32 PBGERRSLV00PBGKCPROT;
  T_PBG01 PBG01;
  uint32 PBGERRSLV01PBGKCPROT;
  T_PBG10 PBG10;
  uint32 PBGERRSLV10PBGKCPROT;
  T_PBG20 PBG20;
  uint32 PBGERRSLV20PBGKCPROT;
  T_PBG21 PBG21;
  uint32 PBGERRSLV21PBGKCPROT;
  T_PBG22 PBG22;
  uint32 PBGERRSLV22PBGKCPROT;
  T_PBG30 PBG30;
  uint32 PBGERRSLV30PBGKCPROT;
  T_PBG31 PBG31;
  uint32 PBGERRSLV31PBGKCPROT;
  T_PBG32 PBG32;
  uint32 PBGERRSLV32PBGKCPROT;
  T_PBG33 PBG33;
  uint32 PBGERRSLV33PBGKCPROT;
  T_PBG40 PBG40;
  uint32 PBGERRSLV40PBGKCPROT;
  T_PBG50 PBG50;
  uint32 PBGERRSLV50PBGKCPROT;
  T_PBG51 PBG51;
  uint32 PBGERRSLV51PBGKCPROT;
  T_PBG52 PBG52;
  uint32 PBGERRSLV52PBGKCPROT;
  T_PBG53 PBG53;
  uint32 PBGERRSLV53PBGKCPROT;
  T_PBG6L0 PBG6L0;
  uint32 PBGERRSLV6L0PBGKCPROT;
  T_PBG6L1 PBG6L1;
  uint32 PBGERRSLV6L1PBGKCPROT;
  T_PBG6H0 PBG6H0;
  uint32 PBGERRSLV6H0PBGKCPROT;
  T_PBG70 PBG70;
  uint32 PBGERRSLV70PBGKCPROT;
  T_PBG80 PBG80;
  uint32 PBGERRSLV80PBGKCPROT;
  T_PBG90 PBG90;
  uint32 PBGERRSLV90PBGKCPROT;

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

  R_PBG00     PBG00;
  uint32      PBGERRSLV00PBGKCPROT;
  R_PBG01     PBG01;
  uint32      PBGERRSLV01PBGKCPROT;
  R_PBG10     PBG10;
  uint32      PBGERRSLV10PBGKCPROT;
  R_PBG20     PBG20;
  uint32      PBGERRSLV20PBGKCPROT;
  R_PBG21     PBG21;
  uint32      PBGERRSLV21PBGKCPROT;
  R_PBG22     PBG22;
  uint32      PBGERRSLV22PBGKCPROT;
  R_PBG30     PBG30;
  uint32      PBGERRSLV30PBGKCPROT;
  R_PBG31     PBG31;
  uint32      PBGERRSLV31PBGKCPROT;
  R_PBG40     PBG40;
  uint32      PBGERRSLV40PBGKCPROT;
  R_PBG41     PBG41;
  uint32      PBGERRSLV41PBGKCPROT;
  R_PBG50     PBG50;
  uint32      PBGERRSLV50PBGKCPROT;
  R_PBG51     PBG51;
  uint32      PBGERRSLV51PBGKCPROT;
  R_PBG52     PBG52;
  uint32      PBGERRSLV52PBGKCPROT;
  R_PBG60     PBG60;
  uint32      PBGERRSLV60PBGKCPROT;
  R_PBG61     PBG61;
  uint32      PBGERRSLV61PBGKCPROT;
  R_PBG7H0    PBG7H0;
  uint32      PBGERRSLV7H0PBGKCPROT;
  R_PBG7L0    PBG7L0;
  uint32      PBGERRSLV7L0PBGKCPROT;
  R_PBG8H0    PBG8H0;
  uint32      PBGERRSLV8H0PBGKCPROT;
  R_PBG8L0    PBG8L0;
  uint32      PBGERRSLV8L0PBGKCPROT;
  R_PBG90     PBG90;
  uint32      PBGERRSLV90PBGKCPROT;
  R_PBG91     PBG91;
  uint32      PBGERRSLV91PBGKCPROT;
  R_PBG100    PBG100;
  uint32      PBGERRSLV100PBGKCPROT;
  R_PBG101    PBG101;
  uint32      PBGERRSLV101PBGKCPROT;
  R_PBG11H0   PBG11H0;
  uint32      PBGERRSLV11H0PBGKCPROT;
  R_PBG11H1   PBG11H1;
  uint32      PBGERRSLV11H1PBGKCPROT;
  R_PBG11L0   PBG11L0;
  uint32      PBGERRSLV11L0PBGKCPROT;

#endif


T_GUARD_CRAMCRG0 GUARD_CRAMCRG0;
uint32 GUARD_CRAMCRG0CRGKCPROT;
T_GUARD_CRAMCRG1 GUARD_CRAMCRG1;
uint32 GUARD_CRAMCRG1CRGKCPROT;
T_GUARD_CRAMCRG2 GUARD_CRAMCRG2;
uint32 GUARD_CRAMCRG2CRGKCPROT;
T_GUARD_CRAMCRG3 GUARD_CRAMCRG3;
uint32 GUARD_CRAMCRG3CRGKCPROT;
T_GUARD_CRAMCSG0 GUARD_CRAMCSG0;
T_GUARD_CRAMCSG1 GUARD_CRAMCSG1;
T_GUARD_CRAMCSG2 GUARD_CRAMCSG2;
T_GUARD_CRAMCSG3 GUARD_CRAMCSG3;


volatile R_HBG90 GUARD_HBG90;
volatile R_HBG91 GUARD_HBG91;
volatile R_HBG92 GUARD_HBG92;
volatile R_HBG93 GUARD_HBG93;
volatile R_HBG96 GUARD_HBG96;

volatile R_HBGHBGERRSLV90 GUARD_HBGHBGERRSLV90;
volatile R_HBGHBGERRSLV91 GUARD_HBGHBGERRSLV91;
volatile R_HBGHBGERRSLV92 GUARD_HBGHBGERRSLV92;
volatile R_HBGHBGERRSLV93 GUARD_HBGHBGERRSLV93;
volatile R_HBGHBGERRSLV96 GUARD_HBGHBGERRSLV96;

volatile R_GUARD_INTC2 GUARD_INTC2;


#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  volatile R_SPIDCTL GUARD_SPIDCTL;
  volatile R_GUARD_DTS   GUARD_DTS;
  volatile R_GUARD_DMAC0 GUARD_DMAC0;
  volatile R_GUARD_DMAC1 GUARD_DMAC1;
  volatile R_GUARD_BARR  GUARD_BARR;
  volatile R_GUARD_IPIR  GUARD_IPIR;
  volatile R_GUARD_TPTM  GUARD_TPTM;
#endif

volatile RBSYS_BARRBRG_t rbsys_barrbrg[16];
volatile uint32 rbsys_intc2guards[767];

volatile uint32 rbsys_dmac0guard[32];
volatile uint32 rbsys_dmac1guard[32];
volatile uint32 rbsys_dtsguard[128];

#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  uint32 TRBSYS_ConfigurationSettingsArea[1024];
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar  )
  volatile GST_t GST_0;
  volatile rba_Reg_MC_ME_tst MC_ME_PER;
  volatile MC_CGM_PERIPHERAL_DOMAIN_t MC_CGM_PERIPHERAL_DOMAIN;
  volatile rba_Reg_MC_ME_tst MC_ME_CL0;
  volatile rba_Reg_MC_ME_tst MC_ME_CL1;
  volatile rba_Reg_MC_ME_tst MC_ME_CL2;
  volatile PLLDIG_PERIPHERAL_DOMAIN_t PLLDIG_PERIPHERAL_DOMAIN;


  volatile PRAMC_AXI_tag PRAM_0;
  volatile PRAMC_AXI_tag PRAM_1;
  volatile PRAMC_AXI_tag PRAM_2;
  volatile PRAMC_AXI_tag PRAM_3;
  volatile PRAMC_AXI_tag PRAM_4;
  volatile PRAMC_tag PRAM_5;
  volatile PRAMC_tag PRAM_6;
  volatile PRAMC_tag PRAM_7;
  volatile PRAMC_tag PRAM_8;
  volatile PRAMC_AXI_tag PRAM_9;
  volatile PRAMC_AXI_tag PRAM_10;
  volatile PRAMC_AXI_tag PRAM_12;
  volatile OVLY_PRAM_tag OVLY_PRAM_0;
  volatile OVLY_PRAM_tag OVLY_PRAM_1;
  volatile OVLY_PRAM_tag OVLY_PRAM_2;
  volatile OVLY_PRAM_tag OVLY_PRAM_3;
  volatile OVLY_PRAM_tag OVLY_PRAM_4;
  volatile OVLY_PRAM_tag OVLY_PRAM_5;

  volatile NVM_CTRL_tag NVM_CTRL_0_0;
  volatile NVM_CTRL_tag NVM_CTRL_0_1;
  volatile NVM_CTRL_tag NVM_CTRL_1_0;
  volatile NVM_CTRL_tag NVM_CTRL_1_1;
  volatile NVM_CTRL_tag NVM_CTRL_2_0;
  volatile NVM_CTRL_tag NVM_CTRL_2_1;

  volatile SWT_tag SWT_SYS_0;

  volatile MC_RGM_DOMAIN_tag MC_RGM_CL0;
  volatile MC_RGM_DOMAIN_tag MC_RGM_CL1;
  volatile MC_RGM_DOMAIN_tag MC_RGM_CL2;
  volatile MC_RGM_PERIPHERAL_DOMAIN_tag MC_RGM_PER;

  volatile MC_CGM_DOMAIN_0_t          MC_CGM_DOMAIN_0;
  volatile MC_CGM_DOMAIN_1_2_t        MC_CGM_DOMAIN_1;
  volatile MC_CGM_DOMAIN_1_2_t        MC_CGM_DOMAIN_2;
  volatile MC_CGM_PERIPHERAL_DOMAIN_t MC_CGM_PERIPHERAL_DOMAIN;

#endif

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  uint32 IMR0;
  uint32 IMR1;
  uint32 IMR2;
  uint32 IMR3;
  uint32 IMR4;
  uint32 IMR5;
  uint32 IMR6;
  uint32 IMR7;
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  uint32 INTC2IMR1;
  uint32 INTC2IMR2;
  uint32 INTC2IMR3;
  uint32 INTC2IMR4;
  uint32 INTC2IMR5;
  uint32 INTC2IMR6;
  uint32 INTC2IMR7;
  uint32 INTC2IMR8;
  uint32 INTC2IMR9;
  uint32 INTC2IMR10;
  uint32 INTC2IMR11;
  uint32 INTC2IMR12;
  uint32 INTC2IMR13;
  uint32 INTC2IMR14;
  uint32 INTC2IMR15;
  uint32 INTC2IMR16;
  uint32 INTC2IMR17;
  uint32 INTC2IMR18;
  uint32 INTC2IMR19;
  uint32 INTC2IMR20;
  uint32 INTC2IMR21;
  uint32 INTC2IMR22;
  uint32 INTC2IMR23;
#endif

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  uint32 INTC1_SELFIMR0;
#endif

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  uint32 FEINTFMSK0;
  uint32 FEINTFMSK1;
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  uint32 FEINC_PE0FEINTMSK;
  uint32 FEINC_PE1FEINTMSK;
#endif

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  uint32 PRDSEL3;
  uint32 PRDNAME2;
  uint32 PRDNAME3;
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  uint32 PRDINFFPRDNAME2;
  uint32 PRDINFFPRDNAME3;
  uint32 PRDINFFPRDNUM;
#endif

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  uint32 SINTR0;
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  uint32 EINTSINTR0;
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  rba_Reg_SIUL2_tst SIUL2_0;

  rba_Reg_FIREWALL_tst AESLIGHT0_FIREWALL;
  rba_Reg_FIREWALL_tst AESLIGHT1_FIREWALL;
  rba_Reg_FIREWALL_tst AESLIGHT2_FIREWALL;
  rba_Reg_FIREWALL_tst AESLIGHT3_FIREWALL;
  rba_Reg_FIREWALL_tst AIPS0_FIREWALL;
  rba_Reg_FIREWALL_tst AIPS1_FIREWALL;
  rba_Reg_FIREWALL_tst AIPS2_FIREWALL;
  rba_Reg_FIREWALL_tst AIPS3_FIREWALL;
  rba_Reg_FIREWALL_tst AIPS4_FIREWALL;
  rba_Reg_FIREWALL_tst DAP_FIREWALL;
  rba_Reg_FIREWALL_tst DFA_FIREWALL;
  rba_Reg_FIREWALL_tst DME_FIREWALL;
  rba_Reg_FIREWALL_tst DSPH_FIREWALL;
  rba_Reg_FIREWALL_tst GTM_FIREWALL;
  rba_Reg_FIREWALL_tst HSM_FIREWALL;
  rba_Reg_FIREWALL_tst KITE0_FIREWALL;
  rba_Reg_FIREWALL_tst KITE1_FIREWALL;
  rba_Reg_FIREWALL_tst KITE2_FIREWALL;
  rba_Reg_FIREWALL_tst NVM_FIREWALL;
  rba_Reg_FIREWALL_tst OCT_SPI_FIREWALL;
  rba_Reg_FIREWALL_tst SYSRAM0_FIREWALL;
  rba_Reg_FIREWALL_tst SYSRAM1_FIREWALL;
  rba_Reg_FIREWALL_tst TMC0_FIREWALL;
  rba_Reg_FIREWALL_tst TMC1_FIREWALL;
  rba_Reg_FIREWALL_tst TMC2_FIREWALL;

  rba_Reg_FIREWALL_tst* TRBSYS_uCRegister_Firewalls[] =
  {
    &AESLIGHT0_FIREWALL,
    &AESLIGHT1_FIREWALL,
    &AESLIGHT2_FIREWALL,
    &AESLIGHT3_FIREWALL,
    &AIPS0_FIREWALL,
    &AIPS1_FIREWALL,
    &AIPS2_FIREWALL,
    &AIPS3_FIREWALL,
    &AIPS4_FIREWALL,
    &DAP_FIREWALL,
    &DFA_FIREWALL,
    &DME_FIREWALL,
    &DSPH_FIREWALL,
    &GTM_FIREWALL,
    &HSM_FIREWALL,
    &KITE0_FIREWALL,
    &KITE1_FIREWALL,
    &KITE2_FIREWALL,
    &NVM_FIREWALL,
    &OCT_SPI_FIREWALL,
    &SYSRAM0_FIREWALL,
    &SYSRAM1_FIREWALL,
    &TMC0_FIREWALL,
    &TMC1_FIREWALL,
    &TMC2_FIREWALL,
  };
  uint32 TRBSYS_uCRegister_FirewallsCnt = sizeof(TRBSYS_uCRegister_Firewalls) / sizeof(rba_Reg_FIREWALL_tst*);

#endif

volatile uint32 ECCDFDFKCPROT;
uint32 ECCDFDFECCCTL;
