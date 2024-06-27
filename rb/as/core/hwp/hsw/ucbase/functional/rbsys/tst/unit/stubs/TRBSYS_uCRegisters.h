#ifndef TRBSYS_UCREGISTERS_H__
#define TRBSYS_UCREGISTERS_H__

#include "SwTest_Global.h"
#include "RBSYS_Config.h"


#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  #define TRBSYS_DUMMY_DEFAULT          0xFFFFFFFFu
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  #define TRBSYS_DUMMY_DEFAULT          0x7FFFFFFFu
#endif

#if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  extern volatile uint32 EIBD41;
  extern volatile uint32 EIBD42;
  extern volatile uint32 EIBD43;

  #define TRBSYS_SYNCREG1 EIBD41
  #define TRBSYS_SYNCREG2 EIBD42
  #define TRBSYS_SYNCREG3 EIBD43
  #define TRBSYS_SYNCREGDEFAULT (0x1u)
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  extern volatile uint32 INTC2EIBD221;
  extern volatile uint32 INTC2EIBD222;
  extern volatile uint32 INTC2EIBD223;

  #define TRBSYS_SYNCREG1 INTC2EIBD221
  #define TRBSYS_SYNCREG2 INTC2EIBD222
  #define TRBSYS_SYNCREG3 INTC2EIBD223
  #define TRBSYS_SYNCREGDEFAULT (0x0u)
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
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
  } SENT_t;
  extern volatile SENT_t SENT_0;

  #define TRBSYS_SYNCREG1  (SENT_0.CH[0].CONFIG)
  #define TRBSYS_SYNCREG2  (SENT_0.CH[1].CONFIG)
  #define TRBSYS_SYNCREG3  (SENT_0.CH[2].CONFIG)

  #define TRBSYS_SYNCREGDEFAULT (0x104u)
#endif

#if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  extern uint16 EICn[214];
  #define EIC32 (EICn[0])
#else
  extern uint16 INTC2EICn[685];
  #define INTC2EIC32 (INTC2EICn[0])
#endif

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  extern volatile uint32 MSR_LM3;
  extern volatile uint32 MSR_LM4;
  extern volatile uint32 MSR_LM5;
  extern volatile uint32 MSR_LM6;
  extern volatile uint32 MSR_LM7;
  extern volatile uint32 MSR_LM8;
  extern volatile uint32 MSR_LM10;
  extern volatile uint32 MSR_LM11;
  extern volatile uint32 MSR_LM12;

  extern volatile uint32 SWLRESS3;
  extern volatile uint32 SWLRESS4;
  extern volatile uint32 SWLRESS5;
  extern volatile uint32 SWLRESS6;
  extern volatile uint32 SWLRESS7;
  extern volatile uint32 SWLRESS8;
  extern volatile uint32 SWLRESS10;
  extern volatile uint32 SWLRESS11;
  extern volatile uint32 SWLRESS12;

  extern volatile uint32 GREG8;
  extern volatile uint32 OPBT0;
  extern volatile uint32 OPBT1;
  extern volatile uint32 OPBT14;
  extern volatile uint32 OPBT15;
  
#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  extern volatile uint32 SYSCTRLMSRKCPROT;

  extern volatile uint32 SYSCTRLMSR_RSCFD;
  extern volatile uint32 SYSCTRLMSR_GTM;
  extern volatile uint32 SYSCTRLMSR_RSENT;
  extern volatile uint32 SYSCTRLMSR_MSPI;
  extern volatile uint32 SYSCTRLMSR_RLIN3;
  extern volatile uint32 SYSCTRLMSR_ADCJ_AWO;
  extern volatile uint32 SYSCTRLMSR_ADCJ_ISO;
  extern volatile uint32 SYSCTRLMSR_FLXA;
  extern volatile uint32 SYSCTRLMSR_ETNB;
  extern volatile uint32 SYSCTRLMSR_RHSIF;
  extern volatile uint32 SYSCTRLMSR_TAUD;
  extern volatile uint32 SYSCTRLMSR_OSTM;

  extern volatile uint32 SYSCTRLSWMRESS_RSCFD;
  extern volatile uint32 SYSCTRLSWMRESS_GTM;
  extern volatile uint32 SYSCTRLSWMRESS_RSENT;
  extern volatile uint32 SYSCTRLSWMRESS_MSPI;
  extern volatile uint32 SYSCTRLSWMRESS_RLIN3;
  extern volatile uint32 SYSCTRLSWMRESS_ADCJ_AWO;
  extern volatile uint32 SYSCTRLSWMRESS_ADCJ_ISO;
  extern volatile uint32 SYSCTRLSWMRESS_FLXA;
  extern volatile uint32 SYSCTRLSWMRESS_ETNB;
  extern volatile uint32 SYSCTRLSWMRESS_RHSIF;
  extern volatile uint32 SYSCTRLSWMRESS_TAUD;
  extern volatile uint32 SYSCTRLSWMRESS_OSTM;

#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
  extern volatile uint32 SYSCTRLMSRKCPROT;

  extern volatile uint32 SYSCTRLMSR_RSCFD;
  extern volatile uint32 SYSCTRLMSR_GTM;
  extern volatile uint32 SYSCTRLMSR_RSENT;
  extern volatile uint32 SYSCTRLMSR_MSPI;
  extern volatile uint32 SYSCTRLMSR_RLIN3;
  extern volatile uint32 SYSCTRLMSR_ADCK_AWO;
  extern volatile uint32 SYSCTRLMSR_ADCK_ISO;
  extern volatile uint32 SYSCTRLMSR_FLXA;
  extern volatile uint32 SYSCTRLMSR_ETN_T1S;
  extern volatile uint32 SYSCTRLMSR_ETN;
  extern volatile uint32 SYSCTRLMSR_TAUD;
  extern volatile uint32 SYSCTRLMSR_OSTM;

  extern volatile uint32 SYSCTRLSWMRESS_RSCFD;
  extern volatile uint32 SYSCTRLSWMRESS_GTM;
  extern volatile uint32 SYSCTRLSWMRESS_RSENT;
  extern volatile uint32 SYSCTRLSWMRESS_MSPI;
  extern volatile uint32 SYSCTRLSWMRESS_RLIN3;
  extern volatile uint32 SYSCTRLSWMRESS_ADCK_AWO;
  extern volatile uint32 SYSCTRLSWMRESS_ADCK_ISO;
  extern volatile uint32 SYSCTRLSWMRESS_FLXA;
  extern volatile uint32 SYSCTRLSWMRESS_ETNF;
  extern volatile uint32 SYSCTRLSWMRESS_ETND;
  extern volatile uint32 SYSCTRLSWMRESS_RHSIF;
  extern volatile uint32 SYSCTRLSWMRESS_TAUD;
  extern volatile uint32 SYSCTRLSWMRESS_OSTM;
#endif


#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  extern uint16 TAUD0TT;
  extern uint16 TAUD0TE;
  extern uint8  TAUD0CSR0;
  extern uint16 TAUD0CDR0;
  extern uint16 TAUD0CMORx[32];
  #define TAUD0CMOR0 (TAUD0CMORx[0])
  extern uint8  TAUD0CMUR0;
  extern uint16 TAUD0TS;
  extern uint16 TAUD0TPS;
  extern uint32 PIC1REG31;
  extern uint32 PIC1REG30;
  extern uint32 PIC1TAUD0SEL;
  extern uint8  PIC1INI01;
#endif



extern uint32 CLKD0DIV;
extern uint32 CLKD0STAT;

extern uint32 CLKD1DIV;
extern uint32 CLKD1STAT;

extern uint32 CLKD2DIV;
extern uint32 CKSC2C;
extern uint32 pysCLKD0STAT;
extern uint32 pysCLKD1STAT;
extern uint32 pysCLKD2STAT;

extern int TRBSYS_GetReadCnt_CLKD0STAT(void);
extern int TRBSYS_GetReadCnt_CLKD1STAT(void);
extern int TRBSYS_GetReadCnt_CLKD2STAT(void);

extern uint32 TRBSYS_ReadCLKD0STAT(void);
extern uint32 TRBSYS_ReadCLKD1STAT(void);
extern uint32 TRBSYS_ReadCLKD2STAT(void);
#define CLKD0STAT  TRBSYS_ReadCLKD0STAT()
#define CLKD1STAT  TRBSYS_ReadCLKD1STAT()
#define CLKD2STAT  TRBSYS_ReadCLKD2STAT()


extern uint32 SYSCTRLCLKKCPROT1 ;
extern uint32 SYSCTRLCKSC_CPUS  ;
extern uint32 SYSCTRLMOSCS      ;
extern uint32 SYSCTRLMOSCE      ;
extern uint32 SYSCTRLPLLS       ;
extern uint32 SYSCTRLPLLE       ;
extern uint32 SYSCTRLCLKD_PLLC  ;
extern uint32 SYSCTRLCLKD_PLLS  ;
extern uint32 SYSCTRLCKSC_CPUC  ;
extern uint32 SYSCTRLCLKD_HSIOSCC;
extern uint32 SYSCTRLCLKD_HSIOSCS;
extern uint32 SYSCTRLCKSC_SSCGC;
extern uint32 SYSCTRLCLKD_SSCGC;
extern uint32 SYSCTRLCKSC_SSCGS;
extern uint32 SYSCTRLCLKD_SSCGS;

extern uint32 SYSCTRLCKSC_FOUT0C;
extern uint32 SYSCTRLCKSC_FOUT0S;
extern uint32 SYSCTRLCLKD_FOUT0C;
extern uint32 SYSCTRLCLKD_FOUT0S;

extern uint32 SYSCTRLCKSC_EXTCLK0C;
extern uint32 SYSCTRLCKSC_EXTCLK0S;
extern uint32 SYSCTRLCLKD_EXTCLK0C;
extern uint32 SYSCTRLCLKD_EXTCLK0S;

extern uint32 SYSCTRLCKSC_WDTS;

static inline void RBSYS_UnlockAccessToHwModule(volatile uint32* KeyCodeProtectionRegister)
{
  *KeyCodeProtectionRegister = 0xA5A5A501u; //< Unlock KC protection
}

static inline void RBSYS_LockAccessToHwModule(volatile uint32* KeyCodeProtectionRegister)
{
  *KeyCodeProtectionRegister = 0xA5A5A500u; //< Lock KC protection
}

extern uint32 GRAMC_WTBCONFIG0;

extern boolean TRBSYS_ReadWTBCONFIG2(void);
extern int TRBSYS_GetReadCnt_WTBCONFIG2(void);
#define GRAMC_WTBCONFIG2  TRBSYS_ReadWTBCONFIG2()




/** @brief This file stubs accesses to RBSYS_uCRegisters.h */

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  extern uint32 STM0TS;
  extern uint32 STM0TT;
  extern uint32 STM0CSTR;
  extern uint32 STM0CKSEL;
  extern uint32 STM0CNT1;
  extern uint32 STM0CNT2;
  extern uint32 STM0CNT0L;
  extern uint32 STM0CNT0H;
  extern uint32 STM0CMP0AL;
  extern uint32 STM0CMP0AH;
  extern uint32 STM0IS;
  extern uint32 STM0RM;
  extern uint32 STM0STC;
  extern uint32 STM0CMP1A;
  extern uint32 STM0CMP1B;
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  extern uint32 TPTMPE0TPTM0USTP;
  extern uint32 TPTMPE0TPTM0USTR;
  extern uint32 TPTMPE0TPTM0URRUN;
  extern uint32 TPTMPE0TPTM0URUN;
  extern uint32 TPTMPE0TPTM0UIEN;
  extern uint32 TPTMPE0TPTM0USTR;
  extern uint32 TPTMPE0TPTM0UDIV;
  extern uint32 TPTMPE0TPTM0UCNT0;
  extern uint32 TPTMPE0TPTM0UCNT1;
  extern uint32 TPTMPE0TPTM0UCMP00;
  extern uint32 TPTMPE0TPTM0UCMP01;
#endif


#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  #define RBSYS_RESF        (RESF)
  #define RBSYS_RESFC       (RESFC)
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  #define RBSYS_RESF        (SYSCTRLRESF)
  #define RBSYS_RESFC       (SYSCTRLRESFC)
#endif

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  extern volatile uint32 RESF;
  extern volatile uint32 RESFC;
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  extern volatile uint32 SYSCTRLRESF;
  extern volatile uint32 SYSCTRLRESFC;
#endif

extern uint32 STAC_LM0;
extern uint32 STAC_GRAM;
extern uint32 SWARESA0;
extern uint32 SWSRESA0;
extern uint32 SYSCTRLRESKCPROT0;
extern uint32 SYSCTRLSWARESA;
extern uint32 SYSCTRLSWSRESA;
extern uint32 BSEQ0CTL;
extern uint32 SYS0BSEQ0CTL;

extern void TRBSYS_setRESF(uint32 nRESF);



#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  #define RBSYS_BOOTCTRL BOOTCTRL
  extern uint32 BOOTCTRL;
#endif

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  extern uint32 SYSCTRLBOOTCTRL;

  /* ensure same register name of BOOTCTRL on P1x and U2A) */
  #define RBSYS_BOOTCTRL          SYSCTRLBOOTCTRL
#endif

#if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  /** Product name for CC CUBE device Renesas D5EDv1 - R7F701345 - not supported*/
  #define RBSYS_PRDNAME2_D5EDV1                     (0x32333130u)
  #define RBSYS_PRDNAME3_D5EDV1                     (0x20202035u)
  #define RBSYS_VERSION_D5EDV1                      (0x100)
  #define RBSYS_CPU_REL_D5EDV1_V100_IDs             {RBSYS_PRDNAME2_D5EDV1, RBSYS_PRDNAME3_D5EDV1, RBSYS_VERSION_D5EDV1}

  /** Product name for CC CUBE device Renesas D4 Rev0 in BGA292 package v2.00 - R7F701327 - not supported*/
  #define RBSYS_PRDNAME2_D4_V200                    (0x32333130u)
  #define RBSYS_PRDNAME3_D4_V200                    (0x20202037u)
  #define RBSYS_VERSION_D4_V200                     (0x200u)
  #define RBSYS_CPU_REL_D4_V200_IDs                 {RBSYS_PRDNAME2_D4_V200, RBSYS_PRDNAME3_D4_V200, RBSYS_VERSION_D4_V200}

#elif ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  /** Product name for CC CUBE+ device Renesas M6ED in BGA516 package v1.00 - R7F702Z19 - not supported*/
  #define RBSYS_PRDNAME2_M6ED_BGA516_V100           (0x315A3230u)
  #define RBSYS_PRDNAME3_M6ED_BGA516_V100           (0x20204139u)
  #define RBSYS_PRDNUM_M6ED_BGA516_V100             (0x000183FFu)
  #define RBSYS_CPU_REL_M6ED_BGA516_V100_IDs        {RBSYS_PRDNAME2_M6ED_BGA516_V100, RBSYS_PRDNAME3_M6ED_BGA516_V100, RBSYS_PRDNUM_M6ED_BGA516_V100}

  /** Product name for CC CUBE+ device Renesas M6ED in BGA292 package v1.00 - R7F702Z19 - not supported*/
  #define RBSYS_PRDNAME2_M6ED_BGA292_V100           (0x315A3230u)
  #define RBSYS_PRDNAME3_M6ED_BGA292_V100           (0x20204139u)
  #define RBSYS_PRDNUM_M6ED_BGA292_V100             (0x00018400u)
  #define RBSYS_CPU_REL_M6ED_BGA292_V100_IDs        {RBSYS_PRDNAME2_M6ED_BGA292_V100, RBSYS_PRDNAME3_M6ED_BGA292_V100, RBSYS_PRDNUM_M6ED_BGA292_V100}
#endif

#if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  extern uint32 PRDNAME2;
  extern uint32 PRDNAME3;
  extern uint32 PRDSEL3;
#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  extern uint32 PRDINFFPRDNAME2;
  extern uint32 PRDINFFPRDNAME3;
  extern uint32 PRDINFFPRDNUM;
#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
  extern uint32 PRDINFfPRDNAME2;
  extern uint32 PRDINFfPRDNAME3;
  extern uint32 PRDINFfPRDNUM;
#endif

#if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  extern uint32 CHIPID1LL;
  extern uint32 CHIPID1LH;
  extern uint32 CHIPID1HL;
  extern uint32 CHIPID1HH;
#endif



#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )

typedef struct
{                                                          /* Module           */
    uint32 PROT00;                                       /* PROT00           */
    uint32 SPID00;                                       /* SPID00           */
    uint32 PROT01;                                       /* PROT01           */
    uint32 SPID01;                                       /* SPID01           */
    uint32 PROT02;                                       /* PROT02           */
    uint32 SPID02;                                       /* SPID02           */
    uint32 PROT03;                                       /* PROT03           */
    uint32 SPID03;                                       /* SPID03           */
    uint32 PROT04;                                       /* PROT04           */
    uint32 SPID04;                                       /* SPID04           */
    uint32 PROT05;                                       /* PROT05           */
    uint32 SPID05;                                       /* SPID05           */
} __type76;

typedef struct
{                                                          /* Module           */
    uint32 PROT00;                                       /* PROT00           */
    uint32 SPID00;                                       /* SPID00           */
    uint32 PROT01;                                       /* PROT01           */
    uint32 SPID01;                                       /* SPID01           */
    uint32 PROT02;                                       /* PROT02           */
    uint32 SPID02;                                       /* SPID02           */
    uint32 PROT03;                                       /* PROT03           */
    uint32 SPID03;                                       /* SPID03           */
} __type78;

typedef struct
{                                                          /* Module           */
    uint32 PROT00;                                       /* PROT00           */
    uint32 SPID00;                                       /* SPID00           */
    uint32 PROT01;                                       /* PROT01           */
    uint32 SPID01;                                       /* SPID01           */
} __type79;

typedef struct
{                                                          /* Module           */
    uint32 PROT00;                                       /* PROT00           */
    uint32 SPID00;                                       /* SPID00           */
    uint32 PROT01;                                       /* PROT01           */
    uint32 SPID01;                                       /* SPID01           */
    uint32 PROT02;                                       /* PROT02           */
    uint32 SPID02;                                       /* SPID02           */
    uint32 PROT03;                                       /* PROT03           */
    uint32 SPID03;                                       /* SPID03           */
    uint32 PROT04;                                       /* PROT04           */
    uint32 SPID04;                                       /* SPID04           */
    uint32 PROT05;                                       /* PROT05           */
    uint32 SPID05;                                       /* SPID05           */
    uint32 PROT06;                                       /* PROT06           */
    uint32 SPID06;                                       /* SPID06           */
    uint32 PROT07;                                       /* PROT07           */
    uint32 SPID07;                                       /* SPID07           */
    uint32 PROT08;                                       /* PROT08           */
    uint32 SPID08;                                       /* SPID08           */
    uint32 PROT09;                                       /* PROT09           */
    uint32 SPID09;                                       /* SPID09           */
    uint32 PROT10;                                       /* PROT10           */
    uint32 SPID10;                                       /* SPID10           */
    uint32 PROT11;                                       /* PROT11           */
    uint32 SPID11;                                       /* SPID11           */
    uint32 PROT12;                                       /* PROT12           */
    uint32 SPID12;                                       /* SPID12           */
    uint32 PROT13;                                       /* PROT13           */
    uint32 SPID13;                                       /* SPID13           */
} __type96;

typedef struct
{                                                          /* Module           */
    uint32 PROT00;                                       /* PROT00           */
    uint32 SPID00;                                       /* SPID00           */
    uint32 PROT01;                                       /* PROT01           */
    uint32 SPID01;                                       /* SPID01           */
    uint32 PROT02;                                       /* PROT02           */
    uint32 SPID02;                                       /* SPID02           */
    uint32 PROT03;                                       /* PROT03           */
    uint32 SPID03;                                       /* SPID03           */
    uint32 PROT04;                                       /* PROT04           */
    uint32 SPID04;                                       /* SPID04           */
    uint32 PROT05;                                       /* PROT05           */
    uint32 SPID05;                                       /* SPID05           */
    uint32 PROT06;                                       /* PROT06           */
    uint32 SPID06;                                       /* SPID06           */
    uint32 PROT07;                                       /* PROT07           */
    uint32 SPID07;                                       /* SPID07           */
} __type100;

typedef struct
{                                                          /* Module           */
    uint32 PROT00;                                       /* PROT00           */
    uint32 SPID00;                                       /* SPID00           */
    uint32 PROT01;                                       /* PROT01           */
    uint32 SPID01;                                       /* SPID01           */
    uint32 PROT02;                                       /* PROT02           */
    uint32 SPID02;                                       /* SPID02           */
    uint32 PROT03;                                       /* PROT03           */
    uint32 SPID03;                                       /* SPID03           */
    uint8  dummy305[16];                                   /* Reserved         */
    uint32 PROT06;                                       /* PROT06           */
    uint32 SPID06;                                       /* SPID06           */
    uint32 PROT07;                                       /* PROT07           */
    uint32 SPID07;                                       /* SPID07           */
    uint32 PROT08;                                       /* PROT08           */
    uint32 SPID08;                                       /* SPID08           */
    uint32 PROT09;                                       /* PROT09           */
    uint32 SPID09;                                       /* SPID09           */
    uint32 PROT10;                                       /* PROT10           */
    uint32 SPID10;                                       /* SPID10           */
    uint32 PROT11;                                       /* PROT11           */
    uint32 SPID11;                                       /* SPID11           */
    uint32 PROT12;                                       /* PROT12           */
    uint32 SPID12;                                       /* SPID12           */
    uint32 PROT13;                                       /* PROT13           */
    uint32 SPID13;                                       /* SPID13           */
} __type101;

typedef struct
{                                                          /* Module           */
    uint32 PROT00;                                       /* PROT00           */
    uint32 SPID00;                                       /* SPID00           */
    uint32 PROT01;                                       /* PROT01           */
    uint32 SPID01;                                       /* SPID01           */
    uint32 PROT02;                                       /* PROT02           */
    uint32 SPID02;                                       /* SPID02           */
    uint32 PROT03;                                       /* PROT03           */
    uint32 SPID03;                                       /* SPID03           */
    uint32 PROT04;                                       /* PROT04           */
    uint32 SPID04;                                       /* SPID04           */
    uint32 PROT05;                                       /* PROT05           */
    uint32 SPID05;                                       /* SPID05           */
    uint32 PROT06;                                       /* PROT06           */
    uint32 SPID06;                                       /* SPID06           */
    uint32 PROT07;                                       /* PROT07           */
    uint32 SPID07;                                       /* SPID07           */
    uint32 PROT08;                                       /* PROT08           */
    uint32 SPID08;                                       /* SPID08           */
    uint32 PROT09;                                       /* PROT09           */
    uint32 SPID09;                                       /* SPID09           */
    uint32 PROT10;                                       /* PROT10           */
    uint32 SPID10;                                       /* SPID10           */
    uint32 PROT11;                                       /* PROT11           */
    uint32 SPID11;                                       /* SPID11           */
    uint32 PROT12;                                       /* PROT12           */
    uint32 SPID12;                                       /* SPID12           */
    uint32 PROT13;                                       /* PROT13           */
    uint32 SPID13;                                       /* SPID13           */
    uint32 PROT14;                                       /* PROT14           */
    uint32 SPID14;                                       /* SPID14           */
    uint32 PROT15;                                       /* PROT15           */
    uint32 SPID15;                                       /* SPID15           */
} __type105;

typedef struct
{                                                          /* Module           */
    uint32 RG0;                                            /* RG0              */
    uint32 RG1;                                            /* RG1              */
    uint32 RG2;                                            /* RG2              */
    uint32 RG3;                                            /* RG3              */
    uint32 RG4;                                            /* RG4              */
    uint32 RG5;                                            /* RG5              */
    uint32 RG6;                                            /* RG6              */
    uint32 RG7;                                            /* RG7              */
} __type111;

typedef struct
{                                                          /* Module           */
    uint32 PROT00;                                       /* PROT00           */
    uint32 SPID00;                                       /* SPID00           */
    uint32 PROT01;                                       /* PROT01           */
    uint32 SPID01;                                       /* SPID01           */
} T_FSGDF0;

typedef struct
{                                                          /* Module           */
    uint32 PROT00;                                       /* PROT00           */
    uint32 SPID00;                                       /* SPID00           */
    uint32 PROT01;                                       /* PROT01           */
    uint32 SPID01;                                       /* SPID01           */
    uint32 PROT02;                                       /* PROT02           */
    uint32 SPID02;                                       /* SPID02           */
    uint32 PROT03;                                       /* PROT03           */
    uint32 SPID03;                                       /* SPID03           */
    uint32 PROT04;                                       /* PROT04           */
    uint32 SPID04;                                       /* SPID04           */
    uint32 PROT05;                                       /* PROT05           */
    uint32 SPID05;                                       /* SPID05           */
    uint32 PROT06;                                       /* PROT06           */
    uint32 SPID06;                                       /* SPID06           */
    uint32 PROT07;                                       /* PROT07           */
    uint32 SPID07;                                       /* SPID07           */
    uint32 PROT08;                                       /* PROT08           */
    uint32 SPID08;                                       /* SPID08           */
    uint32 PROT09;                                       /* PROT09           */
    uint32 SPID09;                                       /* SPID09           */
} T_FSGDM0;



extern __type100 FSGD1A;
extern __type101 FSGD1B;
extern __type96  FSGD2A;
extern __type105 FSGD3A;
extern __type101 FSGD3B;
extern __type105 FSGD4A;
extern __type96  FSGD4B;
extern __type96  FSGD4C;
extern __type76  FSGD5A;
extern __type78  FSGD5B;
extern __type79  FSGD5C;
extern __type78  FSGD5D;
extern T_FSGDF0  FSGDE0;  /* E and F have the same type */
extern T_FSGDF0  FSGDE1;
extern T_FSGDF0  FSGDF0;
extern T_FSGDF0  FSGDF1;
extern T_FSGDM0  FSGDM0;



extern __type111 HSSPID;

extern uint32 PEGG0MK;
extern uint32 PEGG0SP;
extern uint32 PEGG1MK;
extern uint32 PEGG1SP;

extern uint32 PEGG0BA;
extern uint32 PEGG1BA;
extern uint32 PEGG2BA;
extern uint32 PEGG3BA;
extern uint32 PEGG4BA;
extern uint32 PEGG5BA;
extern uint32 PEGG6BA;
extern uint32 PEGG7BA;

extern uint32 MGDGRBAD0;
extern uint32 MGDGRADV0;
extern uint32 MGDGRSPID0;
extern uint32 MGDGRPROT0;
extern uint32 MGDGRBAD1;
extern uint32 MGDGRADV1;
extern uint32 MGDGRSPID1;
extern uint32 MGDGRPROT1;
extern uint32 MGDGRBAD2;
extern uint32 MGDGRADV2;
extern uint32 MGDGRSPID2;
extern uint32 MGDGRPROT2;
extern uint32 MGDGRBAD3;
extern uint32 MGDGRADV3;
extern uint32 MGDGRSPID3;
extern uint32 MGDGRPROT3;
extern uint32 MGDGRBAD4;
extern uint32 MGDGRADV4;
extern uint32 MGDGRSPID4;
extern uint32 MGDGRPROT4;
extern uint32 MGDGRBAD5;
extern uint32 MGDGRADV5;
extern uint32 MGDGRSPID5;
extern uint32 MGDGRPROT5;
extern uint32 MGDGRBAD6;
extern uint32 MGDGRADV6;
extern uint32 MGDGRSPID6;
extern uint32 MGDGRPROT6;
extern uint32 MGDGRBAD7;
extern uint32 MGDGRADV7;
extern uint32 MGDGRSPID7;
extern uint32 MGDGRPROT7;

extern uint32 APBFSGDPROT_PDMACM_A;
extern uint32 APBFSGDPROT_PDMACM_B;
extern uint32 APBFSGDPROT_PDMACH_A;
extern uint32 APBFSGDPROT_PDMACH_B;
extern uint32 APBFSGDPROT_INTC2_A;
extern uint32 APBFSGDPROT_INTC2_B;
extern uint32 APBFSGDPROT_PBG_A;
extern uint32 APBFSGDPROT_PBG_B;
extern uint32 APBFSGDPROT_SP1_A;
extern uint32 APBFSGDPROT_SP1_B;
extern uint32 APBFSGDPROT_SP2_A;
extern uint32 APBFSGDPROT_SP2_B;
extern uint32 APBFSGDPROT_SP4_A;
extern uint32 APBFSGDPROT_SP4_B;

extern uint32 APBFSGDSPID_PDMACM_A;
extern uint32 APBFSGDSPID_PDMACM_B;
extern uint32 APBFSGDSPID_PDMACH_A;
extern uint32 APBFSGDSPID_PDMACH_B;
extern uint32 APBFSGDSPID_INTC2_A;
extern uint32 APBFSGDSPID_INTC2_B;
extern uint32 APBFSGDSPID_PBG_A;
extern uint32 APBFSGDSPID_PBG_B;
extern uint32 APBFSGDSPID_SP1_A;
extern uint32 APBFSGDSPID_SP1_B;
extern uint32 APBFSGDSPID_SP2_A;
extern uint32 APBFSGDSPID_SP2_B;
extern uint32 APBFSGDSPID_SP4_A;
extern uint32 APBFSGDSPID_SP4_B;


#define FSGD1APROT00 FSGD1A.PROT00
#define FSGD1APROT01 FSGD1A.PROT01
#define FSGD1APROT02 FSGD1A.PROT02
#define FSGD1APROT03 FSGD1A.PROT03
#define FSGD1APROT04 FSGD1A.PROT04
#define FSGD1APROT05 FSGD1A.PROT05
#define FSGD1APROT06 FSGD1A.PROT06
#define FSGD1APROT07 FSGD1A.PROT07

#define FSGD1BPROT00 FSGD1B.PROT00
#define FSGD1BPROT01 FSGD1B.PROT01
#define FSGD1BPROT02 FSGD1B.PROT02
#define FSGD1BPROT03 FSGD1B.PROT03
#define FSGD1BPROT06 FSGD1B.PROT06
#define FSGD1BPROT07 FSGD1B.PROT07
#define FSGD1BPROT08 FSGD1B.PROT08
#define FSGD1BPROT09 FSGD1B.PROT09
#define FSGD1BPROT10 FSGD1B.PROT10
#define FSGD1BPROT11 FSGD1B.PROT11
#define FSGD1BPROT12 FSGD1B.PROT12
#define FSGD1BPROT13 FSGD1B.PROT13

#define FSGD2APROT00 FSGD2A.PROT00
#define FSGD2APROT01 FSGD2A.PROT01
#define FSGD2APROT02 FSGD2A.PROT02
#define FSGD2APROT03 FSGD2A.PROT03
#define FSGD2APROT04 FSGD2A.PROT04
#define FSGD2APROT05 FSGD2A.PROT05
#define FSGD2APROT06 FSGD2A.PROT06
#define FSGD2APROT07 FSGD2A.PROT07
#define FSGD2APROT08 FSGD2A.PROT08
#define FSGD2APROT09 FSGD2A.PROT09
#define FSGD2APROT10 FSGD2A.PROT10
#define FSGD2APROT11 FSGD2A.PROT11
#define FSGD2APROT12 FSGD2A.PROT12
#define FSGD2APROT13 FSGD2A.PROT13

#define FSGD3APROT00 FSGD3A.PROT00
#define FSGD3APROT01 FSGD3A.PROT01
#define FSGD3APROT02 FSGD3A.PROT02
#define FSGD3APROT03 FSGD3A.PROT03
#define FSGD3APROT04 FSGD3A.PROT04
#define FSGD3APROT05 FSGD3A.PROT05
#define FSGD3APROT06 FSGD3A.PROT06
#define FSGD3APROT07 FSGD3A.PROT07
#define FSGD3APROT08 FSGD3A.PROT08
#define FSGD3APROT09 FSGD3A.PROT09
#define FSGD3APROT10 FSGD3A.PROT10
#define FSGD3APROT11 FSGD3A.PROT11
#define FSGD3APROT12 FSGD3A.PROT12
#define FSGD3APROT13 FSGD3A.PROT13
#define FSGD3APROT14 FSGD3A.PROT14
#define FSGD3APROT15 FSGD3A.PROT15

#define FSGD3BPROT00 FSGD3B.PROT00
#define FSGD3BPROT01 FSGD3B.PROT01
#define FSGD3BPROT02 FSGD3B.PROT02
#define FSGD3BPROT03 FSGD3B.PROT03
#define FSGD3BPROT06 FSGD3B.PROT06
#define FSGD3BPROT07 FSGD3B.PROT07
#define FSGD3BPROT08 FSGD3B.PROT08
#define FSGD3BPROT09 FSGD3B.PROT09
#define FSGD3BPROT10 FSGD3B.PROT10
#define FSGD3BPROT11 FSGD3B.PROT11
#define FSGD3BPROT12 FSGD3B.PROT12
#define FSGD3BPROT13 FSGD3B.PROT13

#define FSGD4APROT00 FSGD4A.PROT00
#define FSGD4APROT01 FSGD4A.PROT01
#define FSGD4APROT02 FSGD4A.PROT02
#define FSGD4APROT03 FSGD4A.PROT03
#define FSGD4APROT04 FSGD4A.PROT04
#define FSGD4APROT05 FSGD4A.PROT05
#define FSGD4APROT06 FSGD4A.PROT06
#define FSGD4APROT07 FSGD4A.PROT07
#define FSGD4APROT08 FSGD4A.PROT08
#define FSGD4APROT09 FSGD4A.PROT09
#define FSGD4APROT10 FSGD4A.PROT10
#define FSGD4APROT11 FSGD4A.PROT11
#define FSGD4APROT12 FSGD4A.PROT12
#define FSGD4APROT13 FSGD4A.PROT13
#define FSGD4APROT14 FSGD4A.PROT14
#define FSGD4APROT15 FSGD4A.PROT15

#define FSGD4BPROT00 FSGD4B.PROT00
#define FSGD4BPROT01 FSGD4B.PROT01
#define FSGD4BPROT02 FSGD4B.PROT02
#define FSGD4BPROT03 FSGD4B.PROT03
#define FSGD4BPROT04 FSGD4B.PROT04
#define FSGD4BPROT05 FSGD4B.PROT05
#define FSGD4BPROT06 FSGD4B.PROT06
#define FSGD4BPROT07 FSGD4B.PROT07
#define FSGD4BPROT08 FSGD4B.PROT08
#define FSGD4BPROT09 FSGD4B.PROT09
#define FSGD4BPROT10 FSGD4B.PROT10
#define FSGD4BPROT11 FSGD4B.PROT11
#define FSGD4BPROT12 FSGD4B.PROT12
#define FSGD4BPROT13 FSGD4B.PROT13

#define FSGD4CPROT00 FSGD4C.PROT00
#define FSGD4CPROT01 FSGD4C.PROT01
#define FSGD4CPROT02 FSGD4C.PROT02
#define FSGD4CPROT03 FSGD4C.PROT03
#define FSGD4CPROT04 FSGD4C.PROT04
#define FSGD4CPROT05 FSGD4C.PROT05
#define FSGD4CPROT06 FSGD4C.PROT06
#define FSGD4CPROT07 FSGD4C.PROT07
#define FSGD4CPROT08 FSGD4C.PROT08
#define FSGD4CPROT09 FSGD4C.PROT09
#define FSGD4CPROT10 FSGD4C.PROT10
#define FSGD4CPROT11 FSGD4C.PROT11
#define FSGD4CPROT12 FSGD4C.PROT12
#define FSGD4CPROT13 FSGD4C.PROT13

#define FSGD5APROT00 FSGD5A.PROT00
#define FSGD5APROT01 FSGD5A.PROT01
#define FSGD5APROT02 FSGD5A.PROT02
#define FSGD5APROT03 FSGD5A.PROT03
#define FSGD5APROT04 FSGD5A.PROT04
#define FSGD5APROT05 FSGD5A.PROT05

#define FSGD5BPROT00 FSGD5B.PROT00
#define FSGD5BPROT01 FSGD5B.PROT01
#define FSGD5BPROT02 FSGD5B.PROT02
#define FSGD5BPROT03 FSGD5B.PROT03

#define FSGD5CPROT00 FSGD5C.PROT00
#define FSGD5CPROT01 FSGD5C.PROT01

#define FSGD5DPROT00 FSGD5D.PROT00
#define FSGD5DPROT01 FSGD5D.PROT01
#define FSGD5DPROT02 FSGD5D.PROT02
#define FSGD5DPROT03 FSGD5D.PROT03

#define FSGDE0PROT00 FSGDE0.PROT00
#define FSGDE0PROT01 FSGDE0.PROT01
#define FSGDE1PROT00 FSGDE1.PROT00
#define FSGDE1PROT01 FSGDE1.PROT01
#define FSGDF0PROT00 FSGDF0.PROT00
#define FSGDF0PROT01 FSGDF0.PROT01
#define FSGDF1PROT00 FSGDF1.PROT00
#define FSGDF1PROT01 FSGDF1.PROT01
#define FSGDM0PROT00 FSGDM0.PROT00
#define FSGDM0PROT01 FSGDM0.PROT01
#define FSGDM0PROT02 FSGDM0.PROT02
#define FSGDM0PROT03 FSGDM0.PROT03
#define FSGDM0PROT04 FSGDM0.PROT04
#define FSGDM0PROT05 FSGDM0.PROT05
#define FSGDM0PROT06 FSGDM0.PROT06
#define FSGDM0PROT07 FSGDM0.PROT07
#define FSGDM0PROT08 FSGDM0.PROT08
#define FSGDM0PROT09 FSGDM0.PROT09


#define FSGD1ASPID00 FSGD1A.SPID00
#define FSGD1ASPID01 FSGD1A.SPID01
#define FSGD1ASPID02 FSGD1A.SPID02
#define FSGD1ASPID03 FSGD1A.SPID03
#define FSGD1ASPID04 FSGD1A.SPID04
#define FSGD1ASPID05 FSGD1A.SPID05
#define FSGD1ASPID06 FSGD1A.SPID06
#define FSGD1ASPID07 FSGD1A.SPID07

#define FSGD1BSPID00 FSGD1B.SPID00
#define FSGD1BSPID01 FSGD1B.SPID01
#define FSGD1BSPID02 FSGD1B.SPID02
#define FSGD1BSPID03 FSGD1B.SPID03
#define FSGD1BSPID06 FSGD1B.SPID06
#define FSGD1BSPID07 FSGD1B.SPID07
#define FSGD1BSPID08 FSGD1B.SPID08
#define FSGD1BSPID09 FSGD1B.SPID09
#define FSGD1BSPID10 FSGD1B.SPID10
#define FSGD1BSPID11 FSGD1B.SPID11
#define FSGD1BSPID12 FSGD1B.SPID12
#define FSGD1BSPID13 FSGD1B.SPID13

#define FSGD2ASPID00 FSGD2A.SPID00
#define FSGD2ASPID01 FSGD2A.SPID01
#define FSGD2ASPID02 FSGD2A.SPID02
#define FSGD2ASPID03 FSGD2A.SPID03
#define FSGD2ASPID04 FSGD2A.SPID04
#define FSGD2ASPID05 FSGD2A.SPID05
#define FSGD2ASPID06 FSGD2A.SPID06
#define FSGD2ASPID07 FSGD2A.SPID07
#define FSGD2ASPID08 FSGD2A.SPID08
#define FSGD2ASPID09 FSGD2A.SPID09
#define FSGD2ASPID10 FSGD2A.SPID10
#define FSGD2ASPID11 FSGD2A.SPID11
#define FSGD2ASPID12 FSGD2A.SPID12
#define FSGD2ASPID13 FSGD2A.SPID13

#define FSGD3ASPID00 FSGD3A.SPID00
#define FSGD3ASPID01 FSGD3A.SPID01
#define FSGD3ASPID02 FSGD3A.SPID02
#define FSGD3ASPID03 FSGD3A.SPID03
#define FSGD3ASPID04 FSGD3A.SPID04
#define FSGD3ASPID05 FSGD3A.SPID05
#define FSGD3ASPID06 FSGD3A.SPID06
#define FSGD3ASPID07 FSGD3A.SPID07
#define FSGD3ASPID08 FSGD3A.SPID08
#define FSGD3ASPID09 FSGD3A.SPID09
#define FSGD3ASPID10 FSGD3A.SPID10
#define FSGD3ASPID11 FSGD3A.SPID11
#define FSGD3ASPID12 FSGD3A.SPID12
#define FSGD3ASPID13 FSGD3A.SPID13
#define FSGD3ASPID14 FSGD3A.SPID14
#define FSGD3ASPID15 FSGD3A.SPID15

#define FSGD3BSPID00 FSGD3B.SPID00
#define FSGD3BSPID01 FSGD3B.SPID01
#define FSGD3BSPID02 FSGD3B.SPID02
#define FSGD3BSPID03 FSGD3B.SPID03
#define FSGD3BSPID06 FSGD3B.SPID06
#define FSGD3BSPID07 FSGD3B.SPID07
#define FSGD3BSPID08 FSGD3B.SPID08
#define FSGD3BSPID09 FSGD3B.SPID09
#define FSGD3BSPID10 FSGD3B.SPID10
#define FSGD3BSPID11 FSGD3B.SPID11
#define FSGD3BSPID12 FSGD3B.SPID12
#define FSGD3BSPID13 FSGD3B.SPID13

#define FSGD4ASPID00 FSGD4A.SPID00
#define FSGD4ASPID01 FSGD4A.SPID01
#define FSGD4ASPID02 FSGD4A.SPID02
#define FSGD4ASPID03 FSGD4A.SPID03
#define FSGD4ASPID04 FSGD4A.SPID04
#define FSGD4ASPID05 FSGD4A.SPID05
#define FSGD4ASPID06 FSGD4A.SPID06
#define FSGD4ASPID07 FSGD4A.SPID07
#define FSGD4ASPID08 FSGD4A.SPID08
#define FSGD4ASPID09 FSGD4A.SPID09
#define FSGD4ASPID10 FSGD4A.SPID10
#define FSGD4ASPID11 FSGD4A.SPID11
#define FSGD4ASPID12 FSGD4A.SPID12
#define FSGD4ASPID13 FSGD4A.SPID13
#define FSGD4ASPID14 FSGD4A.SPID14
#define FSGD4ASPID15 FSGD4A.SPID15

#define FSGD4BSPID00 FSGD4B.SPID00
#define FSGD4BSPID01 FSGD4B.SPID01
#define FSGD4BSPID02 FSGD4B.SPID02
#define FSGD4BSPID03 FSGD4B.SPID03
#define FSGD4BSPID04 FSGD4B.SPID04
#define FSGD4BSPID05 FSGD4B.SPID05
#define FSGD4BSPID06 FSGD4B.SPID06
#define FSGD4BSPID07 FSGD4B.SPID07
#define FSGD4BSPID08 FSGD4B.SPID08
#define FSGD4BSPID09 FSGD4B.SPID09
#define FSGD4BSPID10 FSGD4B.SPID10
#define FSGD4BSPID11 FSGD4B.SPID11
#define FSGD4BSPID12 FSGD4B.SPID12
#define FSGD4BSPID13 FSGD4B.SPID13

#define FSGD4CSPID00 FSGD4C.SPID00
#define FSGD4CSPID01 FSGD4C.SPID01
#define FSGD4CSPID02 FSGD4C.SPID02
#define FSGD4CSPID03 FSGD4C.SPID03
#define FSGD4CSPID04 FSGD4C.SPID04
#define FSGD4CSPID05 FSGD4C.SPID05
#define FSGD4CSPID06 FSGD4C.SPID06
#define FSGD4CSPID07 FSGD4C.SPID07
#define FSGD4CSPID08 FSGD4C.SPID08
#define FSGD4CSPID09 FSGD4C.SPID09
#define FSGD4CSPID10 FSGD4C.SPID10
#define FSGD4CSPID11 FSGD4C.SPID11
#define FSGD4CSPID12 FSGD4C.SPID12
#define FSGD4CSPID13 FSGD4C.SPID13

#define FSGD5ASPID00 FSGD5A.SPID00
#define FSGD5ASPID01 FSGD5A.SPID01
#define FSGD5ASPID02 FSGD5A.SPID02
#define FSGD5ASPID03 FSGD5A.SPID03
#define FSGD5ASPID04 FSGD5A.SPID04
#define FSGD5ASPID05 FSGD5A.SPID05

#define FSGD5BSPID00 FSGD5B.SPID00
#define FSGD5BSPID01 FSGD5B.SPID01
#define FSGD5BSPID02 FSGD5B.SPID02
#define FSGD5BSPID03 FSGD5B.SPID03

#define FSGD5CSPID00 FSGD5C.SPID00
#define FSGD5CSPID01 FSGD5C.SPID01

#define FSGD5DSPID00 FSGD5D.SPID00
#define FSGD5DSPID01 FSGD5D.SPID01
#define FSGD5DSPID02 FSGD5D.SPID02
#define FSGD5DSPID03 FSGD5D.SPID03

#define FSGDE0SPID00 FSGDE0.SPID00
#define FSGDE0SPID01 FSGDE0.SPID01
#define FSGDE1SPID00 FSGDE1.SPID00
#define FSGDE1SPID01 FSGDE1.SPID01
#define FSGDF0SPID00 FSGDF0.SPID00
#define FSGDF0SPID01 FSGDF0.SPID01
#define FSGDF1SPID00 FSGDF1.SPID00
#define FSGDF1SPID01 FSGDF1.SPID01
#define FSGDM0SPID00 FSGDM0.SPID00
#define FSGDM0SPID01 FSGDM0.SPID01
#define FSGDM0SPID02 FSGDM0.SPID02
#define FSGDM0SPID03 FSGDM0.SPID03
#define FSGDM0SPID04 FSGDM0.SPID04
#define FSGDM0SPID05 FSGDM0.SPID05
#define FSGDM0SPID06 FSGDM0.SPID06
#define FSGDM0SPID07 FSGDM0.SPID07
#define FSGDM0SPID08 FSGDM0.SPID08
#define FSGDM0SPID09 FSGDM0.SPID09

#define HSSPIDRG0 HSSPID.RG0
#define HSSPIDRG1 HSSPID.RG1
#define HSSPIDRG2 HSSPID.RG2
#define HSSPIDRG3 HSSPID.RG3
#define HSSPIDRG4 HSSPID.RG4
#define HSSPIDRG5 HSSPID.RG5
#define HSSPIDRG6 HSSPID.RG6
#define HSSPIDRG7 HSSPID.RG7


#else
/*    U2A  Register stubbing */




typedef struct
{                                                          /* Module           */
  uint32 PEGKCPROT;                                      /* PEGKCPROT        */
  uint8  dummy2420[60];                                  /* Reserved         */
  uint32 PEGPROT0;                                       /* PEGPROT0         */
  uint32 PEGSPID0;                                       /* PEGSPID0         */
  uint32 PEGBAD0;                                        /* PEGBAD0          */
  uint32 PEGADV0;                                        /* PEGADV0          */
  uint32 PEGPROT1;                                       /* PEGPROT1         */
  uint32 PEGSPID1;                                       /* PEGSPID1         */
  uint32 PEGBAD1;                                        /* PEGBAD1          */
  uint32 PEGADV1;                                        /* PEGADV1          */
  uint32 PEGPROT2;                                       /* PEGPROT2         */
  uint32 PEGSPID2;                                       /* PEGSPID2         */
  uint32 PEGBAD2;                                        /* PEGBAD2          */
  uint32 PEGADV2;                                        /* PEGADV2          */
  uint32 PEGPROT3;                                       /* PEGPROT3         */
  uint32 PEGSPID3;                                       /* PEGSPID3         */
  uint32 PEGBAD3;                                        /* PEGBAD3          */
  uint32 PEGADV3;                                        /* PEGADV3          */
  uint32 PEGPROT4;                                       /* PEGPROT4         */
  uint32 PEGSPID4;                                       /* PEGSPID4         */
  uint32 PEGBAD4;                                        /* PEGBAD4          */
  uint32 PEGADV4;                                        /* PEGADV4          */
  uint32 PEGPROT5;                                       /* PEGPROT5         */
  uint32 PEGSPID5;                                       /* PEGSPID5         */
  uint32 PEGBAD5;                                        /* PEGBAD5          */
  uint32 PEGADV5;                                        /* PEGADV5          */
  uint32 PEGPROT6;                                       /* PEGPROT6         */
  uint32 PEGSPID6;                                       /* PEGSPID6         */
  uint32 PEGBAD6;                                        /* PEGBAD6          */
  uint32 PEGADV6;                                        /* PEGADV6          */
  uint32 PEGPROT7;                                       /* PEGPROT7         */
  uint32 PEGSPID7;                                       /* PEGSPID7         */
  uint32 PEGBAD7;                                        /* PEGBAD7          */
  uint32 PEGADV7;                                        /* PEGADV7          */
} T_GUARD_PE0CL0;
typedef struct
{                                                          /* Module           */
  uint32 PEGKCPROT;                                      /* PEGKCPROT        */
  uint8  dummy2420[60];                                  /* Reserved         */
  uint32 PEGPROT0;                                       /* PEGPROT0         */
  uint32 PEGSPID0;                                       /* PEGSPID0         */
  uint32 PEGBAD0;                                        /* PEGBAD0          */
  uint32 PEGADV0;                                        /* PEGADV0          */
  uint32 PEGPROT1;                                       /* PEGPROT1         */
  uint32 PEGSPID1;                                       /* PEGSPID1         */
  uint32 PEGBAD1;                                        /* PEGBAD1          */
  uint32 PEGADV1;                                        /* PEGADV1          */
  uint32 PEGPROT2;                                       /* PEGPROT2         */
  uint32 PEGSPID2;                                       /* PEGSPID2         */
  uint32 PEGBAD2;                                        /* PEGBAD2          */
  uint32 PEGADV2;                                        /* PEGADV2          */
  uint32 PEGPROT3;                                       /* PEGPROT3         */
  uint32 PEGSPID3;                                       /* PEGSPID3         */
  uint32 PEGBAD3;                                        /* PEGBAD3          */
  uint32 PEGADV3;                                        /* PEGADV3          */
  uint32 PEGPROT4;                                       /* PEGPROT4         */
  uint32 PEGSPID4;                                       /* PEGSPID4         */
  uint32 PEGBAD4;                                        /* PEGBAD4          */
  uint32 PEGADV4;                                        /* PEGADV4          */
  uint32 PEGPROT5;                                       /* PEGPROT5         */
  uint32 PEGSPID5;                                       /* PEGSPID5         */
  uint32 PEGBAD5;                                        /* PEGBAD5          */
  uint32 PEGADV5;                                        /* PEGADV5          */
  uint32 PEGPROT6;                                       /* PEGPROT6         */
  uint32 PEGSPID6;                                       /* PEGSPID6         */
  uint32 PEGBAD6;                                        /* PEGBAD6          */
  uint32 PEGADV6;                                        /* PEGADV6          */
  uint32 PEGPROT7;                                       /* PEGPROT7         */
  uint32 PEGSPID7;                                       /* PEGSPID7         */
  uint32 PEGBAD7;                                        /* PEGBAD7          */
  uint32 PEGADV7;                                        /* PEGADV7          */
} T_GUARD_PE1CL0;


#define GUARD_PE0CL0PEGPROT0  GUARD_PE0CL0.PEGPROT0
#define GUARD_PE0CL0PEGSPID0  GUARD_PE0CL0.PEGSPID0
#define GUARD_PE0CL0PEGBAD0   GUARD_PE0CL0.PEGBAD0
#define GUARD_PE0CL0PEGADV0   GUARD_PE0CL0.PEGADV0
#define GUARD_PE0CL0PEGPROT1  GUARD_PE0CL0.PEGPROT1
#define GUARD_PE0CL0PEGSPID1  GUARD_PE0CL0.PEGSPID1
#define GUARD_PE0CL0PEGBAD1   GUARD_PE0CL0.PEGBAD1
#define GUARD_PE0CL0PEGADV1   GUARD_PE0CL0.PEGADV1
#define GUARD_PE0CL0PEGPROT2  GUARD_PE0CL0.PEGPROT2
#define GUARD_PE0CL0PEGSPID2  GUARD_PE0CL0.PEGSPID2
#define GUARD_PE0CL0PEGBAD2   GUARD_PE0CL0.PEGBAD2
#define GUARD_PE0CL0PEGADV2   GUARD_PE0CL0.PEGADV2
#define GUARD_PE0CL0PEGPROT3  GUARD_PE0CL0.PEGPROT3
#define GUARD_PE0CL0PEGSPID3  GUARD_PE0CL0.PEGSPID3
#define GUARD_PE0CL0PEGBAD3   GUARD_PE0CL0.PEGBAD3
#define GUARD_PE0CL0PEGADV3   GUARD_PE0CL0.PEGADV3
#define GUARD_PE0CL0PEGPROT4  GUARD_PE0CL0.PEGPROT4
#define GUARD_PE0CL0PEGSPID4  GUARD_PE0CL0.PEGSPID4
#define GUARD_PE0CL0PEGBAD4   GUARD_PE0CL0.PEGBAD4
#define GUARD_PE0CL0PEGADV4   GUARD_PE0CL0.PEGADV4
#define GUARD_PE0CL0PEGPROT5  GUARD_PE0CL0.PEGPROT5
#define GUARD_PE0CL0PEGSPID5  GUARD_PE0CL0.PEGSPID5
#define GUARD_PE0CL0PEGBAD5   GUARD_PE0CL0.PEGBAD5
#define GUARD_PE0CL0PEGADV5   GUARD_PE0CL0.PEGADV5
#define GUARD_PE0CL0PEGPROT6  GUARD_PE0CL0.PEGPROT6
#define GUARD_PE0CL0PEGSPID6  GUARD_PE0CL0.PEGSPID6
#define GUARD_PE0CL0PEGBAD6   GUARD_PE0CL0.PEGBAD6
#define GUARD_PE0CL0PEGADV6   GUARD_PE0CL0.PEGADV6
#define GUARD_PE0CL0PEGPROT7  GUARD_PE0CL0.PEGPROT7
#define GUARD_PE0CL0PEGSPID7  GUARD_PE0CL0.PEGSPID7
#define GUARD_PE0CL0PEGBAD7   GUARD_PE0CL0.PEGBAD7
#define GUARD_PE0CL0PEGADV7   GUARD_PE0CL0.PEGADV7


#define GUARD_PE1CL0PEGPROT0  GUARD_PE1CL0.PEGPROT0
#define GUARD_PE1CL0PEGSPID0  GUARD_PE1CL0.PEGSPID0
#define GUARD_PE1CL0PEGBAD0   GUARD_PE1CL0.PEGBAD0
#define GUARD_PE1CL0PEGADV0   GUARD_PE1CL0.PEGADV0
#define GUARD_PE1CL0PEGPROT1  GUARD_PE1CL0.PEGPROT1
#define GUARD_PE1CL0PEGSPID1  GUARD_PE1CL0.PEGSPID1
#define GUARD_PE1CL0PEGBAD1   GUARD_PE1CL0.PEGBAD1
#define GUARD_PE1CL0PEGADV1   GUARD_PE1CL0.PEGADV1
#define GUARD_PE1CL0PEGPROT2  GUARD_PE1CL0.PEGPROT2
#define GUARD_PE1CL0PEGSPID2  GUARD_PE1CL0.PEGSPID2
#define GUARD_PE1CL0PEGBAD2   GUARD_PE1CL0.PEGBAD2
#define GUARD_PE1CL0PEGADV2   GUARD_PE1CL0.PEGADV2
#define GUARD_PE1CL0PEGPROT3  GUARD_PE1CL0.PEGPROT3
#define GUARD_PE1CL0PEGSPID3  GUARD_PE1CL0.PEGSPID3
#define GUARD_PE1CL0PEGBAD3   GUARD_PE1CL0.PEGBAD3
#define GUARD_PE1CL0PEGADV3   GUARD_PE1CL0.PEGADV3
#define GUARD_PE1CL0PEGPROT4  GUARD_PE1CL0.PEGPROT4
#define GUARD_PE1CL0PEGSPID4  GUARD_PE1CL0.PEGSPID4
#define GUARD_PE1CL0PEGBAD4   GUARD_PE1CL0.PEGBAD4
#define GUARD_PE1CL0PEGADV4   GUARD_PE1CL0.PEGADV4
#define GUARD_PE1CL0PEGPROT5  GUARD_PE1CL0.PEGPROT5
#define GUARD_PE1CL0PEGSPID5  GUARD_PE1CL0.PEGSPID5
#define GUARD_PE1CL0PEGBAD5   GUARD_PE1CL0.PEGBAD5
#define GUARD_PE1CL0PEGADV5   GUARD_PE1CL0.PEGADV5
#define GUARD_PE1CL0PEGPROT6  GUARD_PE1CL0.PEGPROT6
#define GUARD_PE1CL0PEGSPID6  GUARD_PE1CL0.PEGSPID6
#define GUARD_PE1CL0PEGBAD6   GUARD_PE1CL0.PEGBAD6
#define GUARD_PE1CL0PEGADV6   GUARD_PE1CL0.PEGADV6
#define GUARD_PE1CL0PEGPROT7  GUARD_PE1CL0.PEGPROT7
#define GUARD_PE1CL0PEGSPID7  GUARD_PE1CL0.PEGSPID7
#define GUARD_PE1CL0PEGBAD7   GUARD_PE1CL0.PEGBAD7
#define GUARD_PE1CL0PEGADV7   GUARD_PE1CL0.PEGADV7

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
  } T_PBG00;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
  } T_PBG01;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
  } T_PBG10;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
      uint8  dummy4714[128];                                 /* Reserved         */
  } T_PBG20;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
      uint8  dummy4715[128];                                 /* Reserved         */
  } T_PBG21;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
  } T_PBG22;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
      uint8  dummy2494[128];                                 /* Reserved         */
  } T_PBG30;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
      uint8  dummy2495[128];                                 /* Reserved         */
  } T_PBG31;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
      uint8  dummy2496[128];                                 /* Reserved         */
  } T_PBG32;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
  } T_PBG33;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
  } T_PBG40;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
      uint8  dummy2573[128];                                 /* Reserved         */
  } T_PBG50;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
      uint8  dummy2574[128];                                 /* Reserved         */
  } T_PBG51;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
      uint8  dummy2575[128];                                 /* Reserved         */
  } T_PBG52;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
  } T_PBG53;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
  } T_PBG6H0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
      uint8  dummy2706[384];                                 /* Reserved         */
  } T_PBG6L0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
  } T_PBG6L1;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
  } T_PBG70;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
  } T_PBG80;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                 /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                 /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                 /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                 /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                 /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                 /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                 /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                 /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                 /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                 /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                 /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                 /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                 /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                 /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                 /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                 /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                 /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                 /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                 /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                 /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                /* PBGPROT1_15      */
  } T_PBG90;
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV00;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint8  dummy4462[8];                                   /* Reserved         */
      uint32 PBGPROT0_7;                                    /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                    /* PBGPROT1_7       */
  } R_PBG00;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
  } R_PBG01;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
  } R_PBG10;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV10;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                    /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                    /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                    /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                    /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                    /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                    /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                   /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                   /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                   /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                   /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                   /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                   /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                   /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                   /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                   /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                   /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                   /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                   /* PBGPROT1_15      */
  } R_PBG20;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                    /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                    /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                    /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                    /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                    /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                    /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                   /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                   /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                   /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                   /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                   /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                   /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                   /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                   /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                   /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                   /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                   /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                   /* PBGPROT1_15      */
  } R_PBG21;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                    /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                    /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                    /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                    /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                    /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                    /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                   /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                   /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                   /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                   /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                   /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                   /* PBGPROT1_12      */
  } R_PBG22;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV20;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                    /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                    /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                    /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                    /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                    /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                    /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                   /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                   /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                   /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                   /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                   /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                   /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                   /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                   /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                   /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                   /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                   /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                   /* PBGPROT1_15      */
  } R_PBG30;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
  } R_PBG31;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV30;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                    /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                    /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                    /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                    /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                    /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                    /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                   /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                   /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                   /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                   /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                   /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                   /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                   /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                   /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                   /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                   /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                   /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                   /* PBGPROT1_15      */
  } R_PBG40;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
  } R_PBG41;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV40;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                    /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                    /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                    /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                    /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                    /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                    /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                   /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                   /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                   /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                   /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                   /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                   /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                   /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                   /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                   /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                   /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                   /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                   /* PBGPROT1_15      */
  } R_PBG50;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                    /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                    /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                    /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                    /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                    /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                    /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                   /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                   /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                   /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                   /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                   /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                   /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                   /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                   /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                   /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                   /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                   /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                   /* PBGPROT1_15      */
  } R_PBG51;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
  } R_PBG52;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV50;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
  } R_PBG60;
  typedef struct
  {                                                          /* Module           */
      uint32 APECKCPROT;                                    /* APECKCPROT       */
  } R_PB6ECC;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
  } R_PBG61;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
      uint8  dummy4767[36];                                  /* Reserved         */
  } R_PBGERRSLV60;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV61;

  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
  } R_PBG7L0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV7L0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
  } R_PBG7H0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV7H0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
  } R_PBG8H0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV8H0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                    /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                    /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                    /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                    /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                    /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                    /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                   /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                   /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                   /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                   /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                   /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                   /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                   /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                   /* PBGPROT1_13      */
  } R_PBG8L0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV8L0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
  } R_PBG90;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV90;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
  } R_PBG91;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV91;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                    /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                    /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                    /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                    /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                    /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                    /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                   /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                   /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                   /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                   /* PBGPROT1_11      */
      uint8  dummy1471[8];                                   /* Reserved         */
      uint32 PBGPROT0_13;                                   /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                   /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                   /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                   /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                   /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                   /* PBGPROT1_15      */
  } R_PBG100;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
  } R_PBG101;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV100;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
      uint32 PBGPROT0_7;                                    /* PBGPROT0_7       */
      uint32 PBGPROT1_7;                                    /* PBGPROT1_7       */
      uint32 PBGPROT0_8;                                    /* PBGPROT0_8       */
      uint32 PBGPROT1_8;                                    /* PBGPROT1_8       */
      uint32 PBGPROT0_9;                                    /* PBGPROT0_9       */
      uint32 PBGPROT1_9;                                    /* PBGPROT1_9       */
      uint32 PBGPROT0_10;                                   /* PBGPROT0_10      */
      uint32 PBGPROT1_10;                                   /* PBGPROT1_10      */
      uint32 PBGPROT0_11;                                   /* PBGPROT0_11      */
      uint32 PBGPROT1_11;                                   /* PBGPROT1_11      */
      uint32 PBGPROT0_12;                                   /* PBGPROT0_12      */
      uint32 PBGPROT1_12;                                   /* PBGPROT1_12      */
      uint32 PBGPROT0_13;                                   /* PBGPROT0_13      */
      uint32 PBGPROT1_13;                                   /* PBGPROT1_13      */
      uint32 PBGPROT0_14;                                   /* PBGPROT0_14      */
      uint32 PBGPROT1_14;                                   /* PBGPROT1_14      */
      uint32 PBGPROT0_15;                                   /* PBGPROT0_15      */
      uint32 PBGPROT1_15;                                   /* PBGPROT1_15      */
  } R_PBG11H0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
      uint32 PBGPROT0_2;                                    /* PBGPROT0_2       */
      uint32 PBGPROT1_2;                                    /* PBGPROT1_2       */
      uint32 PBGPROT0_3;                                    /* PBGPROT0_3       */
      uint32 PBGPROT1_3;                                    /* PBGPROT1_3       */
      uint32 PBGPROT0_4;                                    /* PBGPROT0_4       */
      uint32 PBGPROT1_4;                                    /* PBGPROT1_4       */
      uint32 PBGPROT0_5;                                    /* PBGPROT0_5       */
      uint32 PBGPROT1_5;                                    /* PBGPROT1_5       */
      uint32 PBGPROT0_6;                                    /* PBGPROT0_6       */
      uint32 PBGPROT1_6;                                    /* PBGPROT1_6       */
  } R_PBG11H1;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV11H0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGPROT0_0;                                    /* PBGPROT0_0       */
      uint32 PBGPROT1_0;                                    /* PBGPROT1_0       */
      uint32 PBGPROT0_1;                                    /* PBGPROT0_1       */
      uint32 PBGPROT1_1;                                    /* PBGPROT1_1       */
  } R_PBG11L0;
  typedef struct
  {                                                          /* Module           */
      uint32 PBGOVFCLR;                                     /* PBGOVFCLR        */
      uint32 PBGOVFSTAT;                                    /* PBGOVFSTAT       */
      uint32 PBGERRADDR;                                    /* PBGERRADDR       */
      uint32 PBGERRTYPE;                                    /* PBGERRTYPE       */
      uint32 PBGSPIDERRCLR;                                 /* PBGSPIDERRCLR    */
      uint32 PBGSPIDERRSTAT;                                /* PBGSPIDERRSTAT   */
      uint32 PBGKCPROT;                                     /* PBGKCPROT        */
  } R_PBGERRSLV11L0;
#endif

typedef struct
{                                                          /* Module           */
    uint32 CSGPROT0;                                      /* CSGPROT0         */
    uint32 CSGSPID0;                                      /* CSGSPID0         */
    uint32 CSGBAD0;                                       /* CSGBAD0          */
    uint32 CSGADV0;                                       /* CSGADV0          */
    uint8  dummy2440[16];                                  /* Reserved         */
    uint32 CSGPROT1;                                      /* CSGPROT1         */
    uint32 CSGSPID1;                                      /* CSGSPID1         */
    uint32 CSGBAD1;                                       /* CSGBAD1          */
    uint32 CSGADV1;                                       /* CSGADV1          */
    uint8  dummy2441[16];                                  /* Reserved         */
    uint32 CSGPROT2;                                      /* CSGPROT2         */
    uint32 CSGSPID2;                                      /* CSGSPID2         */
    uint32 CSGBAD2;                                       /* CSGBAD2          */
    uint32 CSGADV2;                                       /* CSGADV2          */
    uint8  dummy2442[16];                                  /* Reserved         */
    uint32 CSGPROT3;                                      /* CSGPROT3         */
    uint32 CSGSPID3;                                      /* CSGSPID3         */
    uint32 CSGBAD3;                                       /* CSGBAD3          */
    uint32 CSGADV3;                                       /* CSGADV3          */
    uint8  dummy2443[400];                                 /* Reserved         */
} T_GUARD_CRAMCSG0;
typedef struct
{                                                          /* Module           */
    uint32 CSGPROT0;                                      /* CSGPROT0         */
    uint32 CSGSPID0;                                      /* CSGSPID0         */
    uint32 CSGBAD0;                                       /* CSGBAD0          */
    uint32 CSGADV0;                                       /* CSGADV0          */
    uint8  dummy2444[16];                                  /* Reserved         */
    uint32 CSGPROT1;                                      /* CSGPROT1         */
    uint32 CSGSPID1;                                      /* CSGSPID1         */
    uint32 CSGBAD1;                                       /* CSGBAD1          */
    uint32 CSGADV1;                                       /* CSGADV1          */
    uint8  dummy2445[16];                                  /* Reserved         */
    uint32 CSGPROT2;                                      /* CSGPROT2         */
    uint32 CSGSPID2;                                      /* CSGSPID2         */
    uint32 CSGBAD2;                                       /* CSGBAD2          */
    uint32 CSGADV2;                                       /* CSGADV2          */
    uint8  dummy2446[16];                                  /* Reserved         */
    uint32 CSGPROT3;                                      /* CSGPROT3         */
    uint32 CSGSPID3;                                      /* CSGSPID3         */
    uint32 CSGBAD3;                                       /* CSGBAD3          */
    uint32 CSGADV3;                                       /* CSGADV3          */
    uint8  dummy2447[400];                                 /* Reserved         */
} T_GUARD_CRAMCSG1;
typedef struct
{                                                          /* Module           */
    uint32 CSGPROT0;                                      /* CSGPROT0         */
    uint32 CSGSPID0;                                      /* CSGSPID0         */
    uint32 CSGBAD0;                                       /* CSGBAD0          */
    uint32 CSGADV0;                                       /* CSGADV0          */
    uint8  dummy2448[16];                                  /* Reserved         */
    uint32 CSGPROT1;                                      /* CSGPROT1         */
    uint32 CSGSPID1;                                      /* CSGSPID1         */
    uint32 CSGBAD1;                                       /* CSGBAD1          */
    uint32 CSGADV1;                                       /* CSGADV1          */
    uint8  dummy2449[16];                                  /* Reserved         */
    uint32 CSGPROT2;                                      /* CSGPROT2         */
    uint32 CSGSPID2;                                      /* CSGSPID2         */
    uint32 CSGBAD2;                                       /* CSGBAD2          */
    uint32 CSGADV2;                                       /* CSGADV2          */
    uint8  dummy2450[16];                                  /* Reserved         */
    uint32 CSGPROT3;                                      /* CSGPROT3         */
    uint32 CSGSPID3;                                      /* CSGSPID3         */
    uint32 CSGBAD3;                                       /* CSGBAD3          */
    uint32 CSGADV3;                                       /* CSGADV3          */
    uint8  dummy2451[400];                                 /* Reserved         */
} T_GUARD_CRAMCSG2;
typedef struct
{                                                          /* Module           */
    uint32 CSGPROT0;                                      /* CSGPROT0         */
    uint32 CSGSPID0;                                      /* CSGSPID0         */
    uint32 CSGBAD0;                                       /* CSGBAD0          */
    uint32 CSGADV0;                                       /* CSGADV0          */
    uint8  dummy2452[16];                                  /* Reserved         */
    uint32 CSGPROT1;                                      /* CSGPROT1         */
    uint32 CSGSPID1;                                      /* CSGSPID1         */
    uint32 CSGBAD1;                                       /* CSGBAD1          */
    uint32 CSGADV1;                                       /* CSGADV1          */
    uint8  dummy2453[16];                                  /* Reserved         */
    uint32 CSGPROT2;                                      /* CSGPROT2         */
    uint32 CSGSPID2;                                      /* CSGSPID2         */
    uint32 CSGBAD2;                                       /* CSGBAD2          */
    uint32 CSGADV2;                                       /* CSGADV2          */
    uint8  dummy2454[16];                                  /* Reserved         */
    uint32 CSGPROT3;                                      /* CSGPROT3         */
    uint32 CSGSPID3;                                      /* CSGSPID3         */
    uint32 CSGBAD3;                                       /* CSGBAD3          */
    uint32 CSGADV3;                                       /* CSGADV3          */
} T_GUARD_CRAMCSG3;
typedef struct
{                                                          /* Module           */
    uint32 CRGKCPROT;                                  /* CRGKCPROT        */
    uint8  dummy2423[12];                                  /* Reserved         */
    uint32 CRGPROT0;                                   /* CRGPROT0         */
    uint32 CRGSPID0;                                   /* CRGSPID0         */
    uint32 CRGBAD0;                                    /* CRGBAD0          */
    uint32 CRGADV0;                                    /* CRGADV0          */
    uint32 CRGIVCSPID0;                                /* CRGIVCSPID0      */
    uint8  dummy2424[12];                                  /* Reserved         */
    uint32 CRGPROT1;                                   /* CRGPROT1         */
    uint32 CRGSPID1;                                   /* CRGSPID1         */
    uint32 CRGBAD1;                                    /* CRGBAD1          */
    uint32 CRGADV1;                                    /* CRGADV1          */
    uint32 CRGIVCSPID1;                                /* CRGIVCSPID1      */
    uint8  dummy2425[12];                                  /* Reserved         */
    uint32 CRGPROT2;                                   /* CRGPROT2         */
    uint32 CRGSPID2;                                   /* CRGSPID2         */
    uint32 CRGBAD2;                                    /* CRGBAD2          */
    uint32 CRGADV2;                                    /* CRGADV2          */
    uint32 CRGIVCSPID2;                                /* CRGIVCSPID2      */
    uint8  dummy2426[12];                                  /* Reserved         */
    uint32 CRGPROT3;                                   /* CRGPROT3         */
    uint32 CRGSPID3;                                   /* CRGSPID3         */
    uint32 CRGBAD3;                                    /* CRGBAD3          */
    uint32 CRGADV3;                                    /* CRGADV3          */
    uint32 CRGIVCSPID3;                                /* CRGIVCSPID3      */
    uint8  dummy2427[12];                                  /* Reserved         */
    uint32 CRGPROT4;                                   /* CRGPROT4         */
    uint32 CRGSPID4;                                   /* CRGSPID4         */
    uint32 CRGBAD4;                                    /* CRGBAD4          */
    uint32 CRGADV4;                                    /* CRGADV4          */
    uint32 CRGIVCSPID4;                                /* CRGIVCSPID4      */
    uint8  dummy2428[12];                                  /* Reserved         */
    uint32 CRGPROT5;                                   /* CRGPROT5         */
    uint32 CRGSPID5;                                   /* CRGSPID5         */
    uint32 CRGBAD5;                                    /* CRGBAD5          */
    uint32 CRGADV5;                                    /* CRGADV5          */
    uint32 CRGIVCSPID5;                                /* CRGIVCSPID5      */
    uint8  dummy2429[12];                                  /* Reserved         */
    uint32 CRGPROT6;                                   /* CRGPROT6         */
    uint32 CRGSPID6;                                   /* CRGSPID6         */
    uint32 CRGBAD6;                                    /* CRGBAD6          */
    uint32 CRGADV6;                                    /* CRGADV6          */
    uint32 CRGIVCSPID6;                                /* CRGIVCSPID6      */
    uint8  dummy2430[12];                                  /* Reserved         */
    uint32 CRGPROT7;                                   /* CRGPROT7         */
    uint32 CRGSPID7;                                   /* CRGSPID7         */
    uint32 CRGBAD7;                                    /* CRGBAD7          */
    uint32 CRGADV7;                                    /* CRGADV7          */
    uint32 CRGIVCSPID7;                                /* CRGIVCSPID7      */
} T_GUARD_CRAMCRG0;
typedef struct
{                                                          /* Module           */
    uint32 CRGKCPROT;                                  /* CRGKCPROT        */
    uint8  dummy2431[12];                                  /* Reserved         */
    uint32 CRGPROT0;                                   /* CRGPROT0         */
    uint32 CRGSPID0;                                   /* CRGSPID0         */
    uint32 CRGBAD0;                                    /* CRGBAD0          */
    uint32 CRGADV0;                                    /* CRGADV0          */
    uint32 CRGIVCSPID0;                                /* CRGIVCSPID0      */
    uint8  dummy2432[12];                                  /* Reserved         */
    uint32 CRGPROT1;                                   /* CRGPROT1         */
    uint32 CRGSPID1;                                   /* CRGSPID1         */
    uint32 CRGBAD1;                                    /* CRGBAD1          */
    uint32 CRGADV1;                                    /* CRGADV1          */
    uint32 CRGIVCSPID1;                                /* CRGIVCSPID1      */
    uint8  dummy2433[12];                                  /* Reserved         */
    uint32 CRGPROT2;                                   /* CRGPROT2         */
    uint32 CRGSPID2;                                   /* CRGSPID2         */
    uint32 CRGBAD2;                                    /* CRGBAD2          */
    uint32 CRGADV2;                                    /* CRGADV2          */
    uint32 CRGIVCSPID2;                                /* CRGIVCSPID2      */
    uint8  dummy2434[12];                                  /* Reserved         */
    uint32 CRGPROT3;                                   /* CRGPROT3         */
    uint32 CRGSPID3;                                   /* CRGSPID3         */
    uint32 CRGBAD3;                                    /* CRGBAD3          */
    uint32 CRGADV3;                                    /* CRGADV3          */
    uint32 CRGIVCSPID3;                                /* CRGIVCSPID3      */
    uint8  dummy2435[12];                                  /* Reserved         */
    uint32 CRGPROT4;                                   /* CRGPROT4         */
    uint32 CRGSPID4;                                   /* CRGSPID4         */
    uint32 CRGBAD4;                                    /* CRGBAD4          */
    uint32 CRGADV4;                                    /* CRGADV4          */
    uint32 CRGIVCSPID4;                                /* CRGIVCSPID4      */
    uint8  dummy2436[12];                                  /* Reserved         */
    uint32 CRGPROT5;                                   /* CRGPROT5         */
    uint32 CRGSPID5;                                   /* CRGSPID5         */
    uint32 CRGBAD5;                                    /* CRGBAD5          */
    uint32 CRGADV5;                                    /* CRGADV5          */
    uint32 CRGIVCSPID5;                                /* CRGIVCSPID5      */
    uint8  dummy2437[12];                                  /* Reserved         */
    uint32 CRGPROT6;                                   /* CRGPROT6         */
    uint32 CRGSPID6;                                   /* CRGSPID6         */
    uint32 CRGBAD6;                                    /* CRGBAD6          */
    uint32 CRGADV6;                                    /* CRGADV6          */
    uint32 CRGIVCSPID6;                                /* CRGIVCSPID6      */
    uint8  dummy2438[12];                                  /* Reserved         */
    uint32 CRGPROT7;                                   /* CRGPROT7         */
    uint32 CRGSPID7;                                   /* CRGSPID7         */
    uint32 CRGBAD7;                                    /* CRGBAD7          */
    uint32 CRGADV7;                                    /* CRGADV7          */
    uint32 CRGIVCSPID7;                                /* CRGIVCSPID7      */
} T_GUARD_CRAMCRG1;
typedef struct
{                                                          /* Module           */
    uint32 CRGKCPROT;                                  /* CRGKCPROT        */
    uint8  dummy2439[12];                                  /* Reserved         */
    uint32 CRGPROT0;                                   /* CRGPROT0         */
    uint32 CRGSPID0;                                   /* CRGSPID0         */
    uint32 CRGBAD0;                                    /* CRGBAD0          */
    uint32 CRGADV0;                                    /* CRGADV0          */
    uint32 CRGIVCSPID0;                                /* CRGIVCSPID0      */
    uint8  dummy2440[12];                                  /* Reserved         */
    uint32 CRGPROT1;                                   /* CRGPROT1         */
    uint32 CRGSPID1;                                   /* CRGSPID1         */
    uint32 CRGBAD1;                                    /* CRGBAD1          */
    uint32 CRGADV1;                                    /* CRGADV1          */
    uint32 CRGIVCSPID1;                                /* CRGIVCSPID1      */
    uint8  dummy2441[12];                                  /* Reserved         */
    uint32 CRGPROT2;                                   /* CRGPROT2         */
    uint32 CRGSPID2;                                   /* CRGSPID2         */
    uint32 CRGBAD2;                                    /* CRGBAD2          */
    uint32 CRGADV2;                                    /* CRGADV2          */
    uint32 CRGIVCSPID2;                                /* CRGIVCSPID2      */
    uint8  dummy2442[12];                                  /* Reserved         */
    uint32 CRGPROT3;                                   /* CRGPROT3         */
    uint32 CRGSPID3;                                   /* CRGSPID3         */
    uint32 CRGBAD3;                                    /* CRGBAD3          */
    uint32 CRGADV3;                                    /* CRGADV3          */
    uint32 CRGIVCSPID3;                                /* CRGIVCSPID3      */
    uint8  dummy2443[12];                                  /* Reserved         */
    uint32 CRGPROT4;                                   /* CRGPROT4         */
    uint32 CRGSPID4;                                   /* CRGSPID4         */
    uint32 CRGBAD4;                                    /* CRGBAD4          */
    uint32 CRGADV4;                                    /* CRGADV4          */
    uint32 CRGIVCSPID4;                                /* CRGIVCSPID4      */
    uint8  dummy2444[12];                                  /* Reserved         */
    uint32 CRGPROT5;                                   /* CRGPROT5         */
    uint32 CRGSPID5;                                   /* CRGSPID5         */
    uint32 CRGBAD5;                                    /* CRGBAD5          */
    uint32 CRGADV5;                                    /* CRGADV5          */
    uint32 CRGIVCSPID5;                                /* CRGIVCSPID5      */
    uint8  dummy2445[12];                                  /* Reserved         */
    uint32 CRGPROT6;                                   /* CRGPROT6         */
    uint32 CRGSPID6;                                   /* CRGSPID6         */
    uint32 CRGBAD6;                                    /* CRGBAD6          */
    uint32 CRGADV6;                                    /* CRGADV6          */
    uint32 CRGIVCSPID6;                                /* CRGIVCSPID6      */
    uint8  dummy2446[12];                                  /* Reserved         */
    uint32 CRGPROT7;                                   /* CRGPROT7         */
    uint32 CRGSPID7;                                   /* CRGSPID7         */
    uint32 CRGBAD7;                                    /* CRGBAD7          */
    uint32 CRGADV7;                                    /* CRGADV7          */
    uint32 CRGIVCSPID7;                                /* CRGIVCSPID7      */
} T_GUARD_CRAMCRG2;
typedef struct
{                                                          /* Module           */
    uint32 CRGKCPROT;                                  /* CRGKCPROT        */
    uint8  dummy2447[12];                                  /* Reserved         */
    uint32 CRGPROT0;                                   /* CRGPROT0         */
    uint32 CRGSPID0;                                   /* CRGSPID0         */
    uint32 CRGBAD0;                                    /* CRGBAD0          */
    uint32 CRGADV0;                                    /* CRGADV0          */
    uint32 CRGIVCSPID0;                                /* CRGIVCSPID0      */
    uint8  dummy2448[12];                                  /* Reserved         */
    uint32 CRGPROT1;                                   /* CRGPROT1         */
    uint32 CRGSPID1;                                   /* CRGSPID1         */
    uint32 CRGBAD1;                                    /* CRGBAD1          */
    uint32 CRGADV1;                                    /* CRGADV1          */
    uint32 CRGIVCSPID1;                                /* CRGIVCSPID1      */
    uint8  dummy2449[12];                                  /* Reserved         */
    uint32 CRGPROT2;                                   /* CRGPROT2         */
    uint32 CRGSPID2;                                   /* CRGSPID2         */
    uint32 CRGBAD2;                                    /* CRGBAD2          */
    uint32 CRGADV2;                                    /* CRGADV2          */
    uint32 CRGIVCSPID2;                                /* CRGIVCSPID2      */
    uint8  dummy2450[12];                                  /* Reserved         */
    uint32 CRGPROT3;                                   /* CRGPROT3         */
    uint32 CRGSPID3;                                   /* CRGSPID3         */
    uint32 CRGBAD3;                                    /* CRGBAD3          */
    uint32 CRGADV3;                                    /* CRGADV3          */
    uint32 CRGIVCSPID3;                                /* CRGIVCSPID3      */
    uint8  dummy2451[12];                                  /* Reserved         */
    uint32 CRGPROT4;                                   /* CRGPROT4         */
    uint32 CRGSPID4;                                   /* CRGSPID4         */
    uint32 CRGBAD4;                                    /* CRGBAD4          */
    uint32 CRGADV4;                                    /* CRGADV4          */
    uint32 CRGIVCSPID4;                                /* CRGIVCSPID4      */
    uint8  dummy2452[12];                                  /* Reserved         */
    uint32 CRGPROT5;                                   /* CRGPROT5         */
    uint32 CRGSPID5;                                   /* CRGSPID5         */
    uint32 CRGBAD5;                                    /* CRGBAD5          */
    uint32 CRGADV5;                                    /* CRGADV5          */
    uint32 CRGIVCSPID5;                                /* CRGIVCSPID5      */
    uint8  dummy2453[12];                                  /* Reserved         */
    uint32 CRGPROT6;                                   /* CRGPROT6         */
    uint32 CRGSPID6;                                   /* CRGSPID6         */
    uint32 CRGBAD6;                                    /* CRGBAD6          */
    uint32 CRGADV6;                                    /* CRGADV6          */
    uint32 CRGIVCSPID6;                                /* CRGIVCSPID6      */
    uint8  dummy2454[12];                                  /* Reserved         */
    uint32 CRGPROT7;                                   /* CRGPROT7         */
    uint32 CRGSPID7;                                   /* CRGSPID7         */
    uint32 CRGBAD7;                                    /* CRGBAD7          */
    uint32 CRGADV7;                                    /* CRGADV7          */
    uint32 CRGIVCSPID7;                                /* CRGIVCSPID7      */
} T_GUARD_CRAMCRG3;

#define PBG00PBGPROT1_0 PBG00.PBGPROT1_0
#define PBG00PBGPROT0_0 PBG00.PBGPROT0_0
#define PBG00PBGPROT1_1 PBG00.PBGPROT1_1
#define PBG00PBGPROT0_1 PBG00.PBGPROT0_1
#define PBG00PBGPROT1_2 PBG00.PBGPROT1_2
#define PBG00PBGPROT0_2 PBG00.PBGPROT0_2
#define PBG00PBGPROT1_3 PBG00.PBGPROT1_3
#define PBG00PBGPROT0_3 PBG00.PBGPROT0_3
#define PBG00PBGPROT1_4 PBG00.PBGPROT1_4
#define PBG00PBGPROT0_4 PBG00.PBGPROT0_4
#define PBG00PBGPROT1_5 PBG00.PBGPROT1_5
#define PBG00PBGPROT0_5 PBG00.PBGPROT0_5
#define PBG00PBGPROT1_6 PBG00.PBGPROT1_6
#define PBG00PBGPROT0_6 PBG00.PBGPROT0_6

#define PBG01PBGPROT1_0 PBG01.PBGPROT1_0
#define PBG01PBGPROT0_0 PBG01.PBGPROT0_0
#define PBG01PBGPROT1_1 PBG01.PBGPROT1_1
#define PBG01PBGPROT0_1 PBG01.PBGPROT0_1
#define PBG01PBGPROT1_2 PBG01.PBGPROT1_2
#define PBG01PBGPROT0_2 PBG01.PBGPROT0_2
#define PBG01PBGPROT1_3 PBG01.PBGPROT1_3
#define PBG01PBGPROT0_3 PBG01.PBGPROT0_3

#define PBG10PBGPROT1_0 PBG10.PBGPROT1_0
#define PBG10PBGPROT0_0 PBG10.PBGPROT0_0
#define PBG10PBGPROT1_1 PBG10.PBGPROT1_1
#define PBG10PBGPROT0_1 PBG10.PBGPROT0_1
#define PBG10PBGPROT1_2 PBG10.PBGPROT1_2
#define PBG10PBGPROT0_2 PBG10.PBGPROT0_2

#define PBG20PBGPROT1_0  PBG20.PBGPROT1_0
#define PBG20PBGPROT0_0  PBG20.PBGPROT0_0
#define PBG20PBGPROT1_1  PBG20.PBGPROT1_1
#define PBG20PBGPROT0_1  PBG20.PBGPROT0_1
#define PBG20PBGPROT1_2  PBG20.PBGPROT1_2
#define PBG20PBGPROT0_2  PBG20.PBGPROT0_2
#define PBG20PBGPROT1_3  PBG20.PBGPROT1_3
#define PBG20PBGPROT0_3  PBG20.PBGPROT0_3
#define PBG20PBGPROT1_4  PBG20.PBGPROT1_4
#define PBG20PBGPROT0_4  PBG20.PBGPROT0_4
#define PBG20PBGPROT1_5  PBG20.PBGPROT1_5
#define PBG20PBGPROT0_5  PBG20.PBGPROT0_5
#define PBG20PBGPROT1_6  PBG20.PBGPROT1_6
#define PBG20PBGPROT0_6  PBG20.PBGPROT0_6
#define PBG20PBGPROT1_7  PBG20.PBGPROT1_7
#define PBG20PBGPROT0_7  PBG20.PBGPROT0_7
#define PBG20PBGPROT1_8  PBG20.PBGPROT1_8
#define PBG20PBGPROT0_8  PBG20.PBGPROT0_8
#define PBG20PBGPROT1_9  PBG20.PBGPROT1_9
#define PBG20PBGPROT0_9  PBG20.PBGPROT0_9
#define PBG20PBGPROT1_10 PBG20.PBGPROT1_10
#define PBG20PBGPROT0_10 PBG20.PBGPROT0_10
#define PBG20PBGPROT1_11 PBG20.PBGPROT1_11
#define PBG20PBGPROT0_11 PBG20.PBGPROT0_11
#define PBG20PBGPROT1_12 PBG20.PBGPROT1_12
#define PBG20PBGPROT0_12 PBG20.PBGPROT0_12
#define PBG20PBGPROT1_13 PBG20.PBGPROT1_13
#define PBG20PBGPROT0_13 PBG20.PBGPROT0_13
#define PBG20PBGPROT1_14 PBG20.PBGPROT1_14
#define PBG20PBGPROT0_14 PBG20.PBGPROT0_14
#define PBG20PBGPROT1_15 PBG20.PBGPROT1_15
#define PBG20PBGPROT0_15 PBG20.PBGPROT0_15

#define PBG21PBGPROT1_0  PBG21.PBGPROT1_0
#define PBG21PBGPROT0_0  PBG21.PBGPROT0_0
#define PBG21PBGPROT1_1  PBG21.PBGPROT1_1
#define PBG21PBGPROT0_1  PBG21.PBGPROT0_1
#define PBG21PBGPROT1_2  PBG21.PBGPROT1_2
#define PBG21PBGPROT0_2  PBG21.PBGPROT0_2
#define PBG21PBGPROT1_3  PBG21.PBGPROT1_3
#define PBG21PBGPROT0_3  PBG21.PBGPROT0_3
#define PBG21PBGPROT1_4  PBG21.PBGPROT1_4
#define PBG21PBGPROT0_4  PBG21.PBGPROT0_4
#define PBG21PBGPROT1_5  PBG21.PBGPROT1_5
#define PBG21PBGPROT0_5  PBG21.PBGPROT0_5
#define PBG21PBGPROT1_6  PBG21.PBGPROT1_6
#define PBG21PBGPROT0_6  PBG21.PBGPROT0_6
#define PBG21PBGPROT1_7  PBG21.PBGPROT1_7
#define PBG21PBGPROT0_7  PBG21.PBGPROT0_7
#define PBG21PBGPROT1_8  PBG21.PBGPROT1_8
#define PBG21PBGPROT0_8  PBG21.PBGPROT0_8
#define PBG21PBGPROT1_9  PBG21.PBGPROT1_9
#define PBG21PBGPROT0_9  PBG21.PBGPROT0_9
#define PBG21PBGPROT1_10 PBG21.PBGPROT1_10
#define PBG21PBGPROT0_10 PBG21.PBGPROT0_10
#define PBG21PBGPROT1_11 PBG21.PBGPROT1_11
#define PBG21PBGPROT0_11 PBG21.PBGPROT0_11
#define PBG21PBGPROT1_12 PBG21.PBGPROT1_12
#define PBG21PBGPROT0_12 PBG21.PBGPROT0_12
#define PBG21PBGPROT1_13 PBG21.PBGPROT1_13
#define PBG21PBGPROT0_13 PBG21.PBGPROT0_13
#define PBG21PBGPROT1_14 PBG21.PBGPROT1_14
#define PBG21PBGPROT0_14 PBG21.PBGPROT0_14
#define PBG21PBGPROT1_15 PBG21.PBGPROT1_15
#define PBG21PBGPROT0_15 PBG21.PBGPROT0_15

#define PBG22PBGPROT1_0  PBG22.PBGPROT1_0
#define PBG22PBGPROT0_0  PBG22.PBGPROT0_0
#define PBG22PBGPROT1_1  PBG22.PBGPROT1_1
#define PBG22PBGPROT0_1  PBG22.PBGPROT0_1
#define PBG22PBGPROT1_2  PBG22.PBGPROT1_2
#define PBG22PBGPROT0_2  PBG22.PBGPROT0_2
#define PBG22PBGPROT1_3  PBG22.PBGPROT1_3
#define PBG22PBGPROT0_3  PBG22.PBGPROT0_3
#define PBG22PBGPROT1_4  PBG22.PBGPROT1_4
#define PBG22PBGPROT0_4  PBG22.PBGPROT0_4
#define PBG22PBGPROT1_5  PBG22.PBGPROT1_5
#define PBG22PBGPROT0_5  PBG22.PBGPROT0_5
#define PBG22PBGPROT1_6  PBG22.PBGPROT1_6
#define PBG22PBGPROT0_6  PBG22.PBGPROT0_6
#define PBG22PBGPROT1_7  PBG22.PBGPROT1_7
#define PBG22PBGPROT0_7  PBG22.PBGPROT0_7
#define PBG22PBGPROT1_8  PBG22.PBGPROT1_8
#define PBG22PBGPROT0_8  PBG22.PBGPROT0_8
#define PBG22PBGPROT1_9  PBG22.PBGPROT1_9
#define PBG22PBGPROT0_9  PBG22.PBGPROT0_9
#define PBG22PBGPROT1_10 PBG22.PBGPROT1_10
#define PBG22PBGPROT0_10 PBG22.PBGPROT0_10
#define PBG22PBGPROT1_11 PBG22.PBGPROT1_11
#define PBG22PBGPROT0_11 PBG22.PBGPROT0_11
#define PBG22PBGPROT1_12 PBG22.PBGPROT1_12
#define PBG22PBGPROT0_12 PBG22.PBGPROT0_12
#define PBG22PBGPROT1_13 PBG22.PBGPROT1_13
#define PBG22PBGPROT0_13 PBG22.PBGPROT0_13
#define PBG22PBGPROT1_14 PBG22.PBGPROT1_14
#define PBG22PBGPROT0_14 PBG22.PBGPROT0_14
#define PBG22PBGPROT1_15 PBG22.PBGPROT1_15
#define PBG22PBGPROT0_15 PBG22.PBGPROT0_15

#define PBG30PBGPROT1_0  PBG30.PBGPROT1_0
#define PBG30PBGPROT0_0  PBG30.PBGPROT0_0
#define PBG30PBGPROT1_1  PBG30.PBGPROT1_1
#define PBG30PBGPROT0_1  PBG30.PBGPROT0_1
#define PBG30PBGPROT1_2  PBG30.PBGPROT1_2
#define PBG30PBGPROT0_2  PBG30.PBGPROT0_2
#define PBG30PBGPROT1_3  PBG30.PBGPROT1_3
#define PBG30PBGPROT0_3  PBG30.PBGPROT0_3
#define PBG30PBGPROT1_4  PBG30.PBGPROT1_4
#define PBG30PBGPROT0_4  PBG30.PBGPROT0_4
#define PBG30PBGPROT1_5  PBG30.PBGPROT1_5
#define PBG30PBGPROT0_5  PBG30.PBGPROT0_5
#define PBG30PBGPROT1_6  PBG30.PBGPROT1_6
#define PBG30PBGPROT0_6  PBG30.PBGPROT0_6
#define PBG30PBGPROT1_7  PBG30.PBGPROT1_7
#define PBG30PBGPROT0_7  PBG30.PBGPROT0_7
#define PBG30PBGPROT1_8  PBG30.PBGPROT1_8
#define PBG30PBGPROT0_8  PBG30.PBGPROT0_8
#define PBG30PBGPROT1_9  PBG30.PBGPROT1_9
#define PBG30PBGPROT0_9  PBG30.PBGPROT0_9
#define PBG30PBGPROT1_10 PBG30.PBGPROT1_10
#define PBG30PBGPROT0_10 PBG30.PBGPROT0_10
#define PBG30PBGPROT1_11 PBG30.PBGPROT1_11
#define PBG30PBGPROT0_11 PBG30.PBGPROT0_11
#define PBG30PBGPROT1_12 PBG30.PBGPROT1_12
#define PBG30PBGPROT0_12 PBG30.PBGPROT0_12
#define PBG30PBGPROT1_13 PBG30.PBGPROT1_13
#define PBG30PBGPROT0_13 PBG30.PBGPROT0_13
#define PBG30PBGPROT1_14 PBG30.PBGPROT1_14
#define PBG30PBGPROT0_14 PBG30.PBGPROT0_14
#define PBG30PBGPROT1_15 PBG30.PBGPROT1_15
#define PBG30PBGPROT0_15 PBG30.PBGPROT0_15

#define PBG31PBGPROT1_0  PBG31.PBGPROT1_0
#define PBG31PBGPROT0_0  PBG31.PBGPROT0_0
#define PBG31PBGPROT1_1  PBG31.PBGPROT1_1
#define PBG31PBGPROT0_1  PBG31.PBGPROT0_1
#define PBG31PBGPROT1_2  PBG31.PBGPROT1_2
#define PBG31PBGPROT0_2  PBG31.PBGPROT0_2
#define PBG31PBGPROT1_3  PBG31.PBGPROT1_3
#define PBG31PBGPROT0_3  PBG31.PBGPROT0_3
#define PBG31PBGPROT1_4  PBG31.PBGPROT1_4
#define PBG31PBGPROT0_4  PBG31.PBGPROT0_4
#define PBG31PBGPROT1_5  PBG31.PBGPROT1_5
#define PBG31PBGPROT0_5  PBG31.PBGPROT0_5
#define PBG31PBGPROT1_6  PBG31.PBGPROT1_6
#define PBG31PBGPROT0_6  PBG31.PBGPROT0_6
#define PBG31PBGPROT1_7  PBG31.PBGPROT1_7
#define PBG31PBGPROT0_7  PBG31.PBGPROT0_7
#define PBG31PBGPROT1_8  PBG31.PBGPROT1_8
#define PBG31PBGPROT0_8  PBG31.PBGPROT0_8
#define PBG31PBGPROT1_9  PBG31.PBGPROT1_9
#define PBG31PBGPROT0_9  PBG31.PBGPROT0_9
#define PBG31PBGPROT1_10 PBG31.PBGPROT1_10
#define PBG31PBGPROT0_10 PBG31.PBGPROT0_10
#define PBG31PBGPROT1_11 PBG31.PBGPROT1_11
#define PBG31PBGPROT0_11 PBG31.PBGPROT0_11
#define PBG31PBGPROT1_12 PBG31.PBGPROT1_12
#define PBG31PBGPROT0_12 PBG31.PBGPROT0_12
#define PBG31PBGPROT1_13 PBG31.PBGPROT1_13
#define PBG31PBGPROT0_13 PBG31.PBGPROT0_13
#define PBG31PBGPROT1_14 PBG31.PBGPROT1_14
#define PBG31PBGPROT0_14 PBG31.PBGPROT0_14
#define PBG31PBGPROT1_15 PBG31.PBGPROT1_15
#define PBG31PBGPROT0_15 PBG31.PBGPROT0_15

#define PBG32PBGPROT1_0  PBG32.PBGPROT1_0
#define PBG32PBGPROT0_0  PBG32.PBGPROT0_0
#define PBG32PBGPROT1_1  PBG32.PBGPROT1_1
#define PBG32PBGPROT0_1  PBG32.PBGPROT0_1
#define PBG32PBGPROT1_2  PBG32.PBGPROT1_2
#define PBG32PBGPROT0_2  PBG32.PBGPROT0_2
#define PBG32PBGPROT1_3  PBG32.PBGPROT1_3
#define PBG32PBGPROT0_3  PBG32.PBGPROT0_3
#define PBG32PBGPROT1_4  PBG32.PBGPROT1_4
#define PBG32PBGPROT0_4  PBG32.PBGPROT0_4
#define PBG32PBGPROT1_5  PBG32.PBGPROT1_5
#define PBG32PBGPROT0_5  PBG32.PBGPROT0_5
#define PBG32PBGPROT1_6  PBG32.PBGPROT1_6
#define PBG32PBGPROT0_6  PBG32.PBGPROT0_6
#define PBG32PBGPROT1_7  PBG32.PBGPROT1_7
#define PBG32PBGPROT0_7  PBG32.PBGPROT0_7
#define PBG32PBGPROT1_8  PBG32.PBGPROT1_8
#define PBG32PBGPROT0_8  PBG32.PBGPROT0_8
#define PBG32PBGPROT1_9  PBG32.PBGPROT1_9
#define PBG32PBGPROT0_9  PBG32.PBGPROT0_9
#define PBG32PBGPROT1_10 PBG32.PBGPROT1_10
#define PBG32PBGPROT0_10 PBG32.PBGPROT0_10
#define PBG32PBGPROT1_11 PBG32.PBGPROT1_11
#define PBG32PBGPROT0_11 PBG32.PBGPROT0_11
#define PBG32PBGPROT1_12 PBG32.PBGPROT1_12
#define PBG32PBGPROT0_12 PBG32.PBGPROT0_12
#define PBG32PBGPROT1_13 PBG32.PBGPROT1_13
#define PBG32PBGPROT0_13 PBG32.PBGPROT0_13
#define PBG32PBGPROT1_14 PBG32.PBGPROT1_14
#define PBG32PBGPROT0_14 PBG32.PBGPROT0_14
#define PBG32PBGPROT1_15 PBG32.PBGPROT1_15
#define PBG32PBGPROT0_15 PBG32.PBGPROT0_15

#define PBG33PBGPROT1_0  PBG33.PBGPROT1_0
#define PBG33PBGPROT0_0  PBG33.PBGPROT0_0
#define PBG33PBGPROT1_1  PBG33.PBGPROT1_1
#define PBG33PBGPROT0_1  PBG33.PBGPROT0_1
#define PBG33PBGPROT1_2  PBG33.PBGPROT1_2
#define PBG33PBGPROT0_2  PBG33.PBGPROT0_2
#define PBG33PBGPROT1_3  PBG33.PBGPROT1_3
#define PBG33PBGPROT0_3  PBG33.PBGPROT0_3
#define PBG33PBGPROT1_4  PBG33.PBGPROT1_4
#define PBG33PBGPROT0_4  PBG33.PBGPROT0_4
#define PBG33PBGPROT1_5  PBG33.PBGPROT1_5
#define PBG33PBGPROT0_5  PBG33.PBGPROT0_5
#define PBG33PBGPROT1_6  PBG33.PBGPROT1_6
#define PBG33PBGPROT0_6  PBG33.PBGPROT0_6
#define PBG33PBGPROT1_7  PBG33.PBGPROT1_7
#define PBG33PBGPROT0_7  PBG33.PBGPROT0_7
#define PBG33PBGPROT1_8  PBG33.PBGPROT1_8
#define PBG33PBGPROT0_8  PBG33.PBGPROT0_8
#define PBG33PBGPROT1_9  PBG33.PBGPROT1_9
#define PBG33PBGPROT0_9  PBG33.PBGPROT0_9
#define PBG33PBGPROT1_10 PBG33.PBGPROT1_10
#define PBG33PBGPROT0_10 PBG33.PBGPROT0_10
#define PBG33PBGPROT1_11 PBG33.PBGPROT1_11
#define PBG33PBGPROT0_11 PBG33.PBGPROT0_11
#define PBG33PBGPROT1_12 PBG33.PBGPROT1_12
#define PBG33PBGPROT0_12 PBG33.PBGPROT0_12
#define PBG33PBGPROT1_13 PBG33.PBGPROT1_13
#define PBG33PBGPROT0_13 PBG33.PBGPROT0_13
#define PBG33PBGPROT1_14 PBG33.PBGPROT1_14
#define PBG33PBGPROT0_14 PBG33.PBGPROT0_14
#define PBG33PBGPROT1_15 PBG33.PBGPROT1_15
#define PBG33PBGPROT0_15 PBG33.PBGPROT0_15

#define PBG40PBGPROT1_0  PBG40.PBGPROT1_0
#define PBG40PBGPROT0_0  PBG40.PBGPROT0_0
#define PBG40PBGPROT1_1  PBG40.PBGPROT1_1
#define PBG40PBGPROT0_1  PBG40.PBGPROT0_1
#define PBG40PBGPROT1_2  PBG40.PBGPROT1_2
#define PBG40PBGPROT0_2  PBG40.PBGPROT0_2
#define PBG40PBGPROT1_3  PBG40.PBGPROT1_3
#define PBG40PBGPROT0_3  PBG40.PBGPROT0_3
#define PBG40PBGPROT1_4  PBG40.PBGPROT1_4
#define PBG40PBGPROT0_4  PBG40.PBGPROT0_4
#define PBG40PBGPROT1_5  PBG40.PBGPROT1_5
#define PBG40PBGPROT0_5  PBG40.PBGPROT0_5
#define PBG40PBGPROT1_6  PBG40.PBGPROT1_6
#define PBG40PBGPROT0_6  PBG40.PBGPROT0_6
#define PBG40PBGPROT1_7  PBG40.PBGPROT1_7
#define PBG40PBGPROT0_7  PBG40.PBGPROT0_7
#define PBG40PBGPROT1_8  PBG40.PBGPROT1_8
#define PBG40PBGPROT0_8  PBG40.PBGPROT0_8
#define PBG40PBGPROT1_9  PBG40.PBGPROT1_9
#define PBG40PBGPROT0_9  PBG40.PBGPROT0_9
#define PBG40PBGPROT1_10 PBG40.PBGPROT1_10
#define PBG40PBGPROT0_10 PBG40.PBGPROT0_10
#define PBG40PBGPROT1_11 PBG40.PBGPROT1_11
#define PBG40PBGPROT0_11 PBG40.PBGPROT0_11
#define PBG40PBGPROT1_12 PBG40.PBGPROT1_12
#define PBG40PBGPROT0_12 PBG40.PBGPROT0_12
#define PBG40PBGPROT1_13 PBG40.PBGPROT1_13
#define PBG40PBGPROT0_13 PBG40.PBGPROT0_13
#define PBG40PBGPROT1_14 PBG40.PBGPROT1_14
#define PBG40PBGPROT0_14 PBG40.PBGPROT0_14
#define PBG40PBGPROT1_15 PBG40.PBGPROT1_15
#define PBG40PBGPROT0_15 PBG40.PBGPROT0_15

#define PBG50PBGPROT1_0  PBG50.PBGPROT1_0
#define PBG50PBGPROT0_0  PBG50.PBGPROT0_0
#define PBG50PBGPROT1_1  PBG50.PBGPROT1_1
#define PBG50PBGPROT0_1  PBG50.PBGPROT0_1
#define PBG50PBGPROT1_2  PBG50.PBGPROT1_2
#define PBG50PBGPROT0_2  PBG50.PBGPROT0_2
#define PBG50PBGPROT1_3  PBG50.PBGPROT1_3
#define PBG50PBGPROT0_3  PBG50.PBGPROT0_3
#define PBG50PBGPROT1_4  PBG50.PBGPROT1_4
#define PBG50PBGPROT0_4  PBG50.PBGPROT0_4
#define PBG50PBGPROT1_5  PBG50.PBGPROT1_5
#define PBG50PBGPROT0_5  PBG50.PBGPROT0_5
#define PBG50PBGPROT1_6  PBG50.PBGPROT1_6
#define PBG50PBGPROT0_6  PBG50.PBGPROT0_6
#define PBG50PBGPROT1_7  PBG50.PBGPROT1_7
#define PBG50PBGPROT0_7  PBG50.PBGPROT0_7
#define PBG50PBGPROT1_8  PBG50.PBGPROT1_8
#define PBG50PBGPROT0_8  PBG50.PBGPROT0_8
#define PBG50PBGPROT1_9  PBG50.PBGPROT1_9
#define PBG50PBGPROT0_9  PBG50.PBGPROT0_9
#define PBG50PBGPROT1_10 PBG50.PBGPROT1_10
#define PBG50PBGPROT0_10 PBG50.PBGPROT0_10
#define PBG50PBGPROT1_11 PBG50.PBGPROT1_11
#define PBG50PBGPROT0_11 PBG50.PBGPROT0_11
#define PBG50PBGPROT1_12 PBG50.PBGPROT1_12
#define PBG50PBGPROT0_12 PBG50.PBGPROT0_12
#define PBG50PBGPROT1_13 PBG50.PBGPROT1_13
#define PBG50PBGPROT0_13 PBG50.PBGPROT0_13
#define PBG50PBGPROT1_14 PBG50.PBGPROT1_14
#define PBG50PBGPROT0_14 PBG50.PBGPROT0_14
#define PBG50PBGPROT1_15 PBG50.PBGPROT1_15
#define PBG50PBGPROT0_15 PBG50.PBGPROT0_15

#define PBG51PBGPROT1_0  PBG51.PBGPROT1_0
#define PBG51PBGPROT0_0  PBG51.PBGPROT0_0
#define PBG51PBGPROT1_1  PBG51.PBGPROT1_1
#define PBG51PBGPROT0_1  PBG51.PBGPROT0_1
#define PBG51PBGPROT1_2  PBG51.PBGPROT1_2
#define PBG51PBGPROT0_2  PBG51.PBGPROT0_2
#define PBG51PBGPROT1_3  PBG51.PBGPROT1_3
#define PBG51PBGPROT0_3  PBG51.PBGPROT0_3
#define PBG51PBGPROT1_4  PBG51.PBGPROT1_4
#define PBG51PBGPROT0_4  PBG51.PBGPROT0_4
#define PBG51PBGPROT1_5  PBG51.PBGPROT1_5
#define PBG51PBGPROT0_5  PBG51.PBGPROT0_5
#define PBG51PBGPROT1_6  PBG51.PBGPROT1_6
#define PBG51PBGPROT0_6  PBG51.PBGPROT0_6
#define PBG51PBGPROT1_7  PBG51.PBGPROT1_7
#define PBG51PBGPROT0_7  PBG51.PBGPROT0_7
#define PBG51PBGPROT1_8  PBG51.PBGPROT1_8
#define PBG51PBGPROT0_8  PBG51.PBGPROT0_8
#define PBG51PBGPROT1_9  PBG51.PBGPROT1_9
#define PBG51PBGPROT0_9  PBG51.PBGPROT0_9
#define PBG51PBGPROT1_10 PBG51.PBGPROT1_10
#define PBG51PBGPROT0_10 PBG51.PBGPROT0_10
#define PBG51PBGPROT1_11 PBG51.PBGPROT1_11
#define PBG51PBGPROT0_11 PBG51.PBGPROT0_11
#define PBG51PBGPROT1_12 PBG51.PBGPROT1_12
#define PBG51PBGPROT0_12 PBG51.PBGPROT0_12
#define PBG51PBGPROT1_13 PBG51.PBGPROT1_13
#define PBG51PBGPROT0_13 PBG51.PBGPROT0_13
#define PBG51PBGPROT1_14 PBG51.PBGPROT1_14
#define PBG51PBGPROT0_14 PBG51.PBGPROT0_14
#define PBG51PBGPROT1_15 PBG51.PBGPROT1_15
#define PBG51PBGPROT0_15 PBG51.PBGPROT0_15

#define PBG52PBGPROT1_0  PBG52.PBGPROT1_0
#define PBG52PBGPROT0_0  PBG52.PBGPROT0_0
#define PBG52PBGPROT1_1  PBG52.PBGPROT1_1
#define PBG52PBGPROT0_1  PBG52.PBGPROT0_1
#define PBG52PBGPROT1_2  PBG52.PBGPROT1_2
#define PBG52PBGPROT0_2  PBG52.PBGPROT0_2
#define PBG52PBGPROT1_3  PBG52.PBGPROT1_3
#define PBG52PBGPROT0_3  PBG52.PBGPROT0_3
#define PBG52PBGPROT1_4  PBG52.PBGPROT1_4
#define PBG52PBGPROT0_4  PBG52.PBGPROT0_4
#define PBG52PBGPROT1_5  PBG52.PBGPROT1_5
#define PBG52PBGPROT0_5  PBG52.PBGPROT0_5
#define PBG52PBGPROT1_6  PBG52.PBGPROT1_6
#define PBG52PBGPROT0_6  PBG52.PBGPROT0_6
#define PBG52PBGPROT1_7  PBG52.PBGPROT1_7
#define PBG52PBGPROT0_7  PBG52.PBGPROT0_7
#define PBG52PBGPROT1_8  PBG52.PBGPROT1_8
#define PBG52PBGPROT0_8  PBG52.PBGPROT0_8
#define PBG52PBGPROT1_9  PBG52.PBGPROT1_9
#define PBG52PBGPROT0_9  PBG52.PBGPROT0_9
#define PBG52PBGPROT1_10 PBG52.PBGPROT1_10
#define PBG52PBGPROT0_10 PBG52.PBGPROT0_10
#define PBG52PBGPROT1_11 PBG52.PBGPROT1_11
#define PBG52PBGPROT0_11 PBG52.PBGPROT0_11
#define PBG52PBGPROT1_12 PBG52.PBGPROT1_12
#define PBG52PBGPROT0_12 PBG52.PBGPROT0_12
#define PBG52PBGPROT1_13 PBG52.PBGPROT1_13
#define PBG52PBGPROT0_13 PBG52.PBGPROT0_13
#define PBG52PBGPROT1_14 PBG52.PBGPROT1_14
#define PBG52PBGPROT0_14 PBG52.PBGPROT0_14
#define PBG52PBGPROT1_15 PBG52.PBGPROT1_15
#define PBG52PBGPROT0_15 PBG52.PBGPROT0_15

#define PBG53PBGPROT1_0  PBG53.PBGPROT1_0
#define PBG53PBGPROT0_0  PBG53.PBGPROT0_0
#define PBG53PBGPROT1_1  PBG53.PBGPROT1_1
#define PBG53PBGPROT0_1  PBG53.PBGPROT0_1
#define PBG53PBGPROT1_2  PBG53.PBGPROT1_2
#define PBG53PBGPROT0_2  PBG53.PBGPROT0_2
#define PBG53PBGPROT1_3  PBG53.PBGPROT1_3
#define PBG53PBGPROT0_3  PBG53.PBGPROT0_3
#define PBG53PBGPROT1_4  PBG53.PBGPROT1_4
#define PBG53PBGPROT0_4  PBG53.PBGPROT0_4
#define PBG53PBGPROT1_5  PBG53.PBGPROT1_5
#define PBG53PBGPROT0_5  PBG53.PBGPROT0_5
#define PBG53PBGPROT1_6  PBG53.PBGPROT1_6
#define PBG53PBGPROT0_6  PBG53.PBGPROT0_6
#define PBG53PBGPROT1_7  PBG53.PBGPROT1_7
#define PBG53PBGPROT0_7  PBG53.PBGPROT0_7
#define PBG53PBGPROT1_8  PBG53.PBGPROT1_8
#define PBG53PBGPROT0_8  PBG53.PBGPROT0_8
#define PBG53PBGPROT1_9  PBG53.PBGPROT1_9
#define PBG53PBGPROT0_9  PBG53.PBGPROT0_9
#define PBG53PBGPROT1_10 PBG53.PBGPROT1_10
#define PBG53PBGPROT0_10 PBG53.PBGPROT0_10
#define PBG53PBGPROT1_11 PBG53.PBGPROT1_11
#define PBG53PBGPROT0_11 PBG53.PBGPROT0_11
#define PBG53PBGPROT1_12 PBG53.PBGPROT1_12
#define PBG53PBGPROT0_12 PBG53.PBGPROT0_12
#define PBG53PBGPROT1_13 PBG53.PBGPROT1_13
#define PBG53PBGPROT0_13 PBG53.PBGPROT0_13
#define PBG53PBGPROT1_14 PBG53.PBGPROT1_14
#define PBG53PBGPROT0_14 PBG53.PBGPROT0_14
#define PBG53PBGPROT1_15 PBG53.PBGPROT1_15
#define PBG53PBGPROT0_15 PBG53.PBGPROT0_15

#define PBG6L0PBGPROT1_0  PBG6L0.PBGPROT1_0
#define PBG6L0PBGPROT0_0  PBG6L0.PBGPROT0_0
#define PBG6L0PBGPROT1_1  PBG6L0.PBGPROT1_1
#define PBG6L0PBGPROT0_1  PBG6L0.PBGPROT0_1
#define PBG6L0PBGPROT1_2  PBG6L0.PBGPROT1_2
#define PBG6L0PBGPROT0_2  PBG6L0.PBGPROT0_2
#define PBG6L0PBGPROT1_3  PBG6L0.PBGPROT1_3
#define PBG6L0PBGPROT0_3  PBG6L0.PBGPROT0_3
#define PBG6L0PBGPROT1_4  PBG6L0.PBGPROT1_4
#define PBG6L0PBGPROT0_4  PBG6L0.PBGPROT0_4
#define PBG6L0PBGPROT1_5  PBG6L0.PBGPROT1_5
#define PBG6L0PBGPROT0_5  PBG6L0.PBGPROT0_5
#define PBG6L0PBGPROT1_6  PBG6L0.PBGPROT1_6
#define PBG6L0PBGPROT0_6  PBG6L0.PBGPROT0_6
#define PBG6L0PBGPROT1_7  PBG6L0.PBGPROT1_7
#define PBG6L0PBGPROT0_7  PBG6L0.PBGPROT0_7
#define PBG6L0PBGPROT1_8  PBG6L0.PBGPROT1_8
#define PBG6L0PBGPROT0_8  PBG6L0.PBGPROT0_8
#define PBG6L0PBGPROT1_9  PBG6L0.PBGPROT1_9
#define PBG6L0PBGPROT0_9  PBG6L0.PBGPROT0_9
#define PBG6L0PBGPROT1_10 PBG6L0.PBGPROT1_10
#define PBG6L0PBGPROT0_10 PBG6L0.PBGPROT0_10
#define PBG6L0PBGPROT1_11 PBG6L0.PBGPROT1_11
#define PBG6L0PBGPROT0_11 PBG6L0.PBGPROT0_11
#define PBG6L0PBGPROT1_12 PBG6L0.PBGPROT1_12
#define PBG6L0PBGPROT0_12 PBG6L0.PBGPROT0_12
#define PBG6L0PBGPROT1_13 PBG6L0.PBGPROT1_13
#define PBG6L0PBGPROT0_13 PBG6L0.PBGPROT0_13
#define PBG6L0PBGPROT1_14 PBG6L0.PBGPROT1_14
#define PBG6L0PBGPROT0_14 PBG6L0.PBGPROT0_14
#define PBG6L0PBGPROT1_15 PBG6L0.PBGPROT1_15
#define PBG6L0PBGPROT0_15 PBG6L0.PBGPROT0_15

#define PBG6L1PBGPROT1_0  PBG6L1.PBGPROT1_0
#define PBG6L1PBGPROT0_0  PBG6L1.PBGPROT0_0
#define PBG6L1PBGPROT1_1  PBG6L1.PBGPROT1_1
#define PBG6L1PBGPROT0_1  PBG6L1.PBGPROT0_1
#define PBG6L1PBGPROT1_2  PBG6L1.PBGPROT1_2
#define PBG6L1PBGPROT0_2  PBG6L1.PBGPROT0_2
#define PBG6L1PBGPROT1_3  PBG6L1.PBGPROT1_3
#define PBG6L1PBGPROT0_3  PBG6L1.PBGPROT0_3
#define PBG6L1PBGPROT1_4  PBG6L1.PBGPROT1_4
#define PBG6L1PBGPROT0_4  PBG6L1.PBGPROT0_4
#define PBG6L1PBGPROT1_5  PBG6L1.PBGPROT1_5
#define PBG6L1PBGPROT0_5  PBG6L1.PBGPROT0_5
#define PBG6L1PBGPROT1_6  PBG6L1.PBGPROT1_6
#define PBG6L1PBGPROT0_6  PBG6L1.PBGPROT0_6
#define PBG6L1PBGPROT1_7  PBG6L1.PBGPROT1_7
#define PBG6L1PBGPROT0_7  PBG6L1.PBGPROT0_7
#define PBG6L1PBGPROT1_8  PBG6L1.PBGPROT1_8
#define PBG6L1PBGPROT0_8  PBG6L1.PBGPROT0_8
#define PBG6L1PBGPROT1_9  PBG6L1.PBGPROT1_9
#define PBG6L1PBGPROT0_9  PBG6L1.PBGPROT0_9
#define PBG6L1PBGPROT1_10 PBG6L1.PBGPROT1_10
#define PBG6L1PBGPROT0_10 PBG6L1.PBGPROT0_10
#define PBG6L1PBGPROT1_11 PBG6L1.PBGPROT1_11
#define PBG6L1PBGPROT0_11 PBG6L1.PBGPROT0_11
#define PBG6L1PBGPROT1_12 PBG6L1.PBGPROT1_12
#define PBG6L1PBGPROT0_12 PBG6L1.PBGPROT0_12
#define PBG6L1PBGPROT1_13 PBG6L1.PBGPROT1_13
#define PBG6L1PBGPROT0_13 PBG6L1.PBGPROT0_13
#define PBG6L1PBGPROT1_14 PBG6L1.PBGPROT1_14
#define PBG6L1PBGPROT0_14 PBG6L1.PBGPROT0_14
#define PBG6L1PBGPROT1_15 PBG6L1.PBGPROT1_15
#define PBG6L1PBGPROT0_15 PBG6L1.PBGPROT0_15

#define PBG6H0PBGPROT1_0  PBG6H0.PBGPROT1_0
#define PBG6H0PBGPROT0_0  PBG6H0.PBGPROT0_0
#define PBG6H0PBGPROT1_1  PBG6H0.PBGPROT1_1
#define PBG6H0PBGPROT0_1  PBG6H0.PBGPROT0_1
#define PBG6H0PBGPROT1_2  PBG6H0.PBGPROT1_2
#define PBG6H0PBGPROT0_2  PBG6H0.PBGPROT0_2
#define PBG6H0PBGPROT1_3  PBG6H0.PBGPROT1_3
#define PBG6H0PBGPROT0_3  PBG6H0.PBGPROT0_3
#define PBG6H0PBGPROT1_4  PBG6H0.PBGPROT1_4
#define PBG6H0PBGPROT0_4  PBG6H0.PBGPROT0_4
#define PBG6H0PBGPROT1_5  PBG6H0.PBGPROT1_5
#define PBG6H0PBGPROT0_5  PBG6H0.PBGPROT0_5
#define PBG6H0PBGPROT1_6  PBG6H0.PBGPROT1_6
#define PBG6H0PBGPROT0_6  PBG6H0.PBGPROT0_6
#define PBG6H0PBGPROT1_7  PBG6H0.PBGPROT1_7
#define PBG6H0PBGPROT0_7  PBG6H0.PBGPROT0_7
#define PBG6H0PBGPROT1_8  PBG6H0.PBGPROT1_8
#define PBG6H0PBGPROT0_8  PBG6H0.PBGPROT0_8
#define PBG6H0PBGPROT1_9  PBG6H0.PBGPROT1_9
#define PBG6H0PBGPROT0_9  PBG6H0.PBGPROT0_9
#define PBG6H0PBGPROT1_10 PBG6H0.PBGPROT1_10
#define PBG6H0PBGPROT0_10 PBG6H0.PBGPROT0_10
#define PBG6H0PBGPROT1_11 PBG6H0.PBGPROT1_11
#define PBG6H0PBGPROT0_11 PBG6H0.PBGPROT0_11
#define PBG6H0PBGPROT1_12 PBG6H0.PBGPROT1_12
#define PBG6H0PBGPROT0_12 PBG6H0.PBGPROT0_12
#define PBG6H0PBGPROT1_13 PBG6H0.PBGPROT1_13
#define PBG6H0PBGPROT0_13 PBG6H0.PBGPROT0_13
#define PBG6H0PBGPROT1_14 PBG6H0.PBGPROT1_14
#define PBG6H0PBGPROT0_14 PBG6H0.PBGPROT0_14
#define PBG6H0PBGPROT1_15 PBG6H0.PBGPROT1_15
#define PBG6H0PBGPROT0_15 PBG6H0.PBGPROT0_15

#define PBG70PBGPROT1_0  PBG70.PBGPROT1_0
#define PBG70PBGPROT0_0  PBG70.PBGPROT0_0
#define PBG70PBGPROT1_1  PBG70.PBGPROT1_1
#define PBG70PBGPROT0_1  PBG70.PBGPROT0_1
#define PBG70PBGPROT1_2  PBG70.PBGPROT1_2
#define PBG70PBGPROT0_2  PBG70.PBGPROT0_2
#define PBG70PBGPROT1_3  PBG70.PBGPROT1_3
#define PBG70PBGPROT0_3  PBG70.PBGPROT0_3
#define PBG70PBGPROT1_4  PBG70.PBGPROT1_4
#define PBG70PBGPROT0_4  PBG70.PBGPROT0_4
#define PBG70PBGPROT1_5  PBG70.PBGPROT1_5
#define PBG70PBGPROT0_5  PBG70.PBGPROT0_5
#define PBG70PBGPROT1_6  PBG70.PBGPROT1_6
#define PBG70PBGPROT0_6  PBG70.PBGPROT0_6
#define PBG70PBGPROT1_7  PBG70.PBGPROT1_7
#define PBG70PBGPROT0_7  PBG70.PBGPROT0_7
#define PBG70PBGPROT1_8  PBG70.PBGPROT1_8
#define PBG70PBGPROT0_8  PBG70.PBGPROT0_8
#define PBG70PBGPROT1_9  PBG70.PBGPROT1_9
#define PBG70PBGPROT0_9  PBG70.PBGPROT0_9
#define PBG70PBGPROT1_10 PBG70.PBGPROT1_10
#define PBG70PBGPROT0_10 PBG70.PBGPROT0_10
#define PBG70PBGPROT1_11 PBG70.PBGPROT1_11
#define PBG70PBGPROT0_11 PBG70.PBGPROT0_11
#define PBG70PBGPROT1_12 PBG70.PBGPROT1_12
#define PBG70PBGPROT0_12 PBG70.PBGPROT0_12
#define PBG70PBGPROT1_13 PBG70.PBGPROT1_13
#define PBG70PBGPROT0_13 PBG70.PBGPROT0_13
#define PBG70PBGPROT1_14 PBG70.PBGPROT1_14
#define PBG70PBGPROT0_14 PBG70.PBGPROT0_14
#define PBG70PBGPROT1_15 PBG70.PBGPROT1_15
#define PBG70PBGPROT0_15 PBG70.PBGPROT0_15

#define PBG80PBGPROT1_0  PBG80.PBGPROT1_0
#define PBG80PBGPROT0_0  PBG80.PBGPROT0_0
#define PBG80PBGPROT1_1  PBG80.PBGPROT1_1
#define PBG80PBGPROT0_1  PBG80.PBGPROT0_1
#define PBG80PBGPROT1_2  PBG80.PBGPROT1_2
#define PBG80PBGPROT0_2  PBG80.PBGPROT0_2
#define PBG80PBGPROT1_3  PBG80.PBGPROT1_3
#define PBG80PBGPROT0_3  PBG80.PBGPROT0_3
#define PBG80PBGPROT1_4  PBG80.PBGPROT1_4
#define PBG80PBGPROT0_4  PBG80.PBGPROT0_4
#define PBG80PBGPROT1_5  PBG80.PBGPROT1_5
#define PBG80PBGPROT0_5  PBG80.PBGPROT0_5
#define PBG80PBGPROT1_6  PBG80.PBGPROT1_6
#define PBG80PBGPROT0_6  PBG80.PBGPROT0_6
#define PBG80PBGPROT1_7  PBG80.PBGPROT1_7
#define PBG80PBGPROT0_7  PBG80.PBGPROT0_7
#define PBG80PBGPROT1_8  PBG80.PBGPROT1_8
#define PBG80PBGPROT0_8  PBG80.PBGPROT0_8
#define PBG80PBGPROT1_9  PBG80.PBGPROT1_9
#define PBG80PBGPROT0_9  PBG80.PBGPROT0_9
#define PBG80PBGPROT1_10 PBG80.PBGPROT1_10
#define PBG80PBGPROT0_10 PBG80.PBGPROT0_10
#define PBG80PBGPROT1_11 PBG80.PBGPROT1_11
#define PBG80PBGPROT0_11 PBG80.PBGPROT0_11
#define PBG80PBGPROT1_12 PBG80.PBGPROT1_12
#define PBG80PBGPROT0_12 PBG80.PBGPROT0_12
#define PBG80PBGPROT1_13 PBG80.PBGPROT1_13
#define PBG80PBGPROT0_13 PBG80.PBGPROT0_13
#define PBG80PBGPROT1_14 PBG80.PBGPROT1_14
#define PBG80PBGPROT0_14 PBG80.PBGPROT0_14
#define PBG80PBGPROT1_15 PBG80.PBGPROT1_15
#define PBG80PBGPROT0_15 PBG80.PBGPROT0_15

#define PBG90PBGPROT1_0  PBG90.PBGPROT1_0
#define PBG90PBGPROT0_0  PBG90.PBGPROT0_0
#define PBG90PBGPROT1_1  PBG90.PBGPROT1_1
#define PBG90PBGPROT0_1  PBG90.PBGPROT0_1
#define PBG90PBGPROT1_2  PBG90.PBGPROT1_2
#define PBG90PBGPROT0_2  PBG90.PBGPROT0_2
#define PBG90PBGPROT1_3  PBG90.PBGPROT1_3
#define PBG90PBGPROT0_3  PBG90.PBGPROT0_3
#define PBG90PBGPROT1_4  PBG90.PBGPROT1_4
#define PBG90PBGPROT0_4  PBG90.PBGPROT0_4
#define PBG90PBGPROT1_5  PBG90.PBGPROT1_5
#define PBG90PBGPROT0_5  PBG90.PBGPROT0_5
#define PBG90PBGPROT1_6  PBG90.PBGPROT1_6
#define PBG90PBGPROT0_6  PBG90.PBGPROT0_6
#define PBG90PBGPROT1_7  PBG90.PBGPROT1_7
#define PBG90PBGPROT0_7  PBG90.PBGPROT0_7
#define PBG90PBGPROT1_8  PBG90.PBGPROT1_8
#define PBG90PBGPROT0_8  PBG90.PBGPROT0_8
#define PBG90PBGPROT1_9  PBG90.PBGPROT1_9
#define PBG90PBGPROT0_9  PBG90.PBGPROT0_9
#define PBG90PBGPROT1_10 PBG90.PBGPROT1_10
#define PBG90PBGPROT0_10 PBG90.PBGPROT0_10
#define PBG90PBGPROT1_11 PBG90.PBGPROT1_11
#define PBG90PBGPROT0_11 PBG90.PBGPROT0_11
#define PBG90PBGPROT1_12 PBG90.PBGPROT1_12
#define PBG90PBGPROT0_12 PBG90.PBGPROT0_12
#define PBG90PBGPROT1_13 PBG90.PBGPROT1_13
#define PBG90PBGPROT0_13 PBG90.PBGPROT0_13
#define PBG90PBGPROT1_14 PBG90.PBGPROT1_14
#define PBG90PBGPROT0_14 PBG90.PBGPROT0_14
#define PBG90PBGPROT1_15 PBG90.PBGPROT1_15
#define PBG90PBGPROT0_15 PBG90.PBGPROT0_15

#define GUARD_CRAMCRG0CRGADV0  GUARD_CRAMCRG0.CRGADV0
#define GUARD_CRAMCRG0CRGSPID0 GUARD_CRAMCRG0.CRGSPID0
#define GUARD_CRAMCRG0CRGBAD0  GUARD_CRAMCRG0.CRGBAD0
#define GUARD_CRAMCRG0CRGPROT0 GUARD_CRAMCRG0.CRGPROT0
#define GUARD_CRAMCRG0CRGADV1  GUARD_CRAMCRG0.CRGADV1
#define GUARD_CRAMCRG0CRGSPID1 GUARD_CRAMCRG0.CRGSPID1
#define GUARD_CRAMCRG0CRGBAD1  GUARD_CRAMCRG0.CRGBAD1
#define GUARD_CRAMCRG0CRGPROT1 GUARD_CRAMCRG0.CRGPROT1
#define GUARD_CRAMCRG1CRGADV0  GUARD_CRAMCRG1.CRGADV0
#define GUARD_CRAMCRG1CRGSPID0 GUARD_CRAMCRG1.CRGSPID0
#define GUARD_CRAMCRG1CRGBAD0  GUARD_CRAMCRG1.CRGBAD0
#define GUARD_CRAMCRG1CRGPROT0 GUARD_CRAMCRG1.CRGPROT0
#define GUARD_CRAMCRG2CRGADV0  GUARD_CRAMCRG2.CRGADV0
#define GUARD_CRAMCRG2CRGSPID0 GUARD_CRAMCRG2.CRGSPID0
#define GUARD_CRAMCRG2CRGBAD0  GUARD_CRAMCRG2.CRGBAD0
#define GUARD_CRAMCRG2CRGPROT0 GUARD_CRAMCRG2.CRGPROT0
#define GUARD_CRAMCRG2CRGADV1  GUARD_CRAMCRG2.CRGADV1
#define GUARD_CRAMCRG2CRGSPID1 GUARD_CRAMCRG2.CRGSPID1
#define GUARD_CRAMCRG2CRGBAD1  GUARD_CRAMCRG2.CRGBAD1
#define GUARD_CRAMCRG2CRGPROT1 GUARD_CRAMCRG2.CRGPROT1
#define GUARD_CRAMCRG3CRGADV0  GUARD_CRAMCRG3.CRGADV0
#define GUARD_CRAMCRG3CRGSPID0 GUARD_CRAMCRG3.CRGSPID0
#define GUARD_CRAMCRG3CRGBAD0  GUARD_CRAMCRG3.CRGBAD0
#define GUARD_CRAMCRG3CRGPROT0 GUARD_CRAMCRG3.CRGPROT0
#define GUARD_CRAMCRG3CRGADV1  GUARD_CRAMCRG3.CRGADV1
#define GUARD_CRAMCRG3CRGSPID1 GUARD_CRAMCRG3.CRGSPID1
#define GUARD_CRAMCRG3CRGBAD1  GUARD_CRAMCRG3.CRGBAD1
#define GUARD_CRAMCRG3CRGPROT1 GUARD_CRAMCRG3.CRGPROT1

#define GUARD_CRAMCSG0CSGPROT0 GUARD_CRAMCSG0.CSGPROT0
#define GUARD_CRAMCSG0CSGSPID0 GUARD_CRAMCSG0.CSGSPID0
#define GUARD_CRAMCSG0CSGBAD0  GUARD_CRAMCSG0.CSGBAD0
#define GUARD_CRAMCSG0CSGADV0  GUARD_CRAMCSG0.CSGADV0
#define GUARD_CRAMCSG0CSGPROT1 GUARD_CRAMCSG0.CSGPROT1
#define GUARD_CRAMCSG0CSGSPID1 GUARD_CRAMCSG0.CSGSPID1
#define GUARD_CRAMCSG0CSGBAD1  GUARD_CRAMCSG0.CSGBAD1
#define GUARD_CRAMCSG0CSGADV1  GUARD_CRAMCSG0.CSGADV1
#define GUARD_CRAMCSG0CSGPROT2 GUARD_CRAMCSG0.CSGPROT2
#define GUARD_CRAMCSG0CSGSPID2 GUARD_CRAMCSG0.CSGSPID2
#define GUARD_CRAMCSG0CSGBAD2  GUARD_CRAMCSG0.CSGBAD2
#define GUARD_CRAMCSG0CSGADV2  GUARD_CRAMCSG0.CSGADV2
#define GUARD_CRAMCSG0CSGPROT3 GUARD_CRAMCSG0.CSGPROT3
#define GUARD_CRAMCSG0CSGSPID3 GUARD_CRAMCSG0.CSGSPID3
#define GUARD_CRAMCSG0CSGBAD3  GUARD_CRAMCSG0.CSGBAD3
#define GUARD_CRAMCSG0CSGADV3  GUARD_CRAMCSG0.CSGADV3


#define GUARD_CRAMCSG1CSGPROT0 GUARD_CRAMCSG1.CSGPROT0
#define GUARD_CRAMCSG1CSGSPID0 GUARD_CRAMCSG1.CSGSPID0
#define GUARD_CRAMCSG1CSGBAD0  GUARD_CRAMCSG1.CSGBAD0
#define GUARD_CRAMCSG1CSGADV0  GUARD_CRAMCSG1.CSGADV0
#define GUARD_CRAMCSG1CSGPROT1 GUARD_CRAMCSG1.CSGPROT1
#define GUARD_CRAMCSG1CSGSPID1 GUARD_CRAMCSG1.CSGSPID1
#define GUARD_CRAMCSG1CSGBAD1  GUARD_CRAMCSG1.CSGBAD1
#define GUARD_CRAMCSG1CSGADV1  GUARD_CRAMCSG1.CSGADV1
#define GUARD_CRAMCSG1CSGPROT2 GUARD_CRAMCSG1.CSGPROT2
#define GUARD_CRAMCSG1CSGSPID2 GUARD_CRAMCSG1.CSGSPID2
#define GUARD_CRAMCSG1CSGBAD2  GUARD_CRAMCSG1.CSGBAD2
#define GUARD_CRAMCSG1CSGADV2  GUARD_CRAMCSG1.CSGADV2
#define GUARD_CRAMCSG1CSGPROT3 GUARD_CRAMCSG1.CSGPROT3
#define GUARD_CRAMCSG1CSGSPID3 GUARD_CRAMCSG1.CSGSPID3
#define GUARD_CRAMCSG1CSGBAD3  GUARD_CRAMCSG1.CSGBAD3
#define GUARD_CRAMCSG1CSGADV3  GUARD_CRAMCSG1.CSGADV3


#define GUARD_CRAMCSG2CSGPROT0 GUARD_CRAMCSG2.CSGPROT0
#define GUARD_CRAMCSG2CSGSPID0 GUARD_CRAMCSG2.CSGSPID0
#define GUARD_CRAMCSG2CSGBAD0  GUARD_CRAMCSG2.CSGBAD0
#define GUARD_CRAMCSG2CSGADV0  GUARD_CRAMCSG2.CSGADV0
#define GUARD_CRAMCSG2CSGPROT1 GUARD_CRAMCSG2.CSGPROT1
#define GUARD_CRAMCSG2CSGSPID1 GUARD_CRAMCSG2.CSGSPID1
#define GUARD_CRAMCSG2CSGBAD1  GUARD_CRAMCSG2.CSGBAD1
#define GUARD_CRAMCSG2CSGADV1  GUARD_CRAMCSG2.CSGADV1
#define GUARD_CRAMCSG2CSGPROT2 GUARD_CRAMCSG2.CSGPROT2
#define GUARD_CRAMCSG2CSGSPID2 GUARD_CRAMCSG2.CSGSPID2
#define GUARD_CRAMCSG2CSGBAD2  GUARD_CRAMCSG2.CSGBAD2
#define GUARD_CRAMCSG2CSGADV2  GUARD_CRAMCSG2.CSGADV2
#define GUARD_CRAMCSG2CSGPROT3 GUARD_CRAMCSG2.CSGPROT3
#define GUARD_CRAMCSG2CSGSPID3 GUARD_CRAMCSG2.CSGSPID3
#define GUARD_CRAMCSG2CSGBAD3  GUARD_CRAMCSG2.CSGBAD3
#define GUARD_CRAMCSG2CSGADV3  GUARD_CRAMCSG2.CSGADV3


#define GUARD_CRAMCSG3CSGPROT0 GUARD_CRAMCSG3.CSGPROT0
#define GUARD_CRAMCSG3CSGSPID0 GUARD_CRAMCSG3.CSGSPID0
#define GUARD_CRAMCSG3CSGBAD0  GUARD_CRAMCSG3.CSGBAD0
#define GUARD_CRAMCSG3CSGADV0  GUARD_CRAMCSG3.CSGADV0
#define GUARD_CRAMCSG3CSGPROT1 GUARD_CRAMCSG3.CSGPROT1
#define GUARD_CRAMCSG3CSGSPID1 GUARD_CRAMCSG3.CSGSPID1
#define GUARD_CRAMCSG3CSGBAD1  GUARD_CRAMCSG3.CSGBAD1
#define GUARD_CRAMCSG3CSGADV1  GUARD_CRAMCSG3.CSGADV1
#define GUARD_CRAMCSG3CSGPROT2 GUARD_CRAMCSG3.CSGPROT2
#define GUARD_CRAMCSG3CSGSPID2 GUARD_CRAMCSG3.CSGSPID2
#define GUARD_CRAMCSG3CSGBAD2  GUARD_CRAMCSG3.CSGBAD2
#define GUARD_CRAMCSG3CSGADV2  GUARD_CRAMCSG3.CSGADV2
#define GUARD_CRAMCSG3CSGPROT3 GUARD_CRAMCSG3.CSGPROT3
#define GUARD_CRAMCSG3CSGSPID3 GUARD_CRAMCSG3.CSGSPID3
#define GUARD_CRAMCSG3CSGBAD3  GUARD_CRAMCSG3.CSGBAD3
#define GUARD_CRAMCSG3CSGADV3  GUARD_CRAMCSG3.CSGADV3

typedef struct {
  uint32 PROT;  // Protection Reg
  uint32 SPID;  // Software programmable ID
  uint32 BAD;   // Base Address
  uint32 ADV;   // Address Mask
  uint8 unused_or_undefined[16];
} RBSYS_CSGGuard_t;

typedef struct {
  RBSYS_CSGGuard_t Module[4];
} RBSYS_CSGGuardGroup_t;

extern T_GUARD_PE0CL0 GUARD_PE0CL0;
extern uint32 GUARD_PE0CL0PEGKCPROT;
extern T_GUARD_PE1CL0 GUARD_PE1CL0;
extern uint32 GUARD_PE1CL0PEGKCPROT;

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    extern T_PBG00 PBG00;
    extern uint32 PBGERRSLV00PBGKCPROT;
    extern T_PBG01 PBG01;
    extern uint32 PBGERRSLV01PBGKCPROT;
    extern T_PBG10 PBG10;
    extern uint32 PBGERRSLV10PBGKCPROT;
    extern T_PBG20 PBG20;
    extern uint32 PBGERRSLV20PBGKCPROT;
    extern T_PBG21 PBG21;
    extern uint32 PBGERRSLV21PBGKCPROT;
    extern T_PBG22 PBG22;
    extern uint32 PBGERRSLV22PBGKCPROT;
    extern T_PBG30 PBG30;
    extern uint32 PBGERRSLV30PBGKCPROT;
    extern T_PBG31 PBG31;
    extern uint32 PBGERRSLV31PBGKCPROT;
    extern T_PBG32 PBG32;
    extern uint32 PBGERRSLV32PBGKCPROT;
    extern T_PBG33 PBG33;
    extern uint32 PBGERRSLV33PBGKCPROT;
    extern T_PBG40 PBG40;
    extern uint32 PBGERRSLV40PBGKCPROT;
    extern T_PBG50 PBG50;
    extern uint32 PBGERRSLV50PBGKCPROT;
    extern T_PBG51 PBG51;
    extern uint32 PBGERRSLV51PBGKCPROT;
    extern T_PBG52 PBG52;
    extern uint32 PBGERRSLV52PBGKCPROT;
    extern T_PBG53 PBG53;
    extern uint32 PBGERRSLV53PBGKCPROT;
    extern T_PBG6L0 PBG6L0;
    extern uint32 PBGERRSLV6L0PBGKCPROT;
    extern T_PBG6L1 PBG6L1;
    extern uint32 PBGERRSLV6L1PBGKCPROT;
    extern T_PBG6H0 PBG6H0;
    extern uint32 PBGERRSLV6H0PBGKCPROT;
    extern T_PBG70 PBG70;
    extern uint32 PBGERRSLV70PBGKCPROT;
    extern T_PBG80 PBG80;
    extern uint32 PBGERRSLV80PBGKCPROT;
    extern T_PBG90 PBG90;
    extern uint32 PBGERRSLV90PBGKCPROT;
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

    extern  R_PBG00     PBG00;
    extern  uint32      PBGERRSLV00PBGKCPROT;
    extern  R_PBG01     PBG01;
    extern  uint32      PBGERRSLV01PBGKCPROT;
    extern  R_PBG10     PBG10;
    extern  uint32      PBGERRSLV10PBGKCPROT;
    extern  R_PBG20     PBG20;
    extern  uint32      PBGERRSLV20PBGKCPROT;
    extern  R_PBG21     PBG21;
    extern  uint32      PBGERRSLV21PBGKCPROT;
    extern  R_PBG22     PBG22;
    extern  uint32      PBGERRSLV22PBGKCPROT;
    extern  R_PBG30     PBG30;
    extern  uint32      PBGERRSLV30PBGKCPROT;
    extern  R_PBG31     PBG31;
    extern  uint32      PBGERRSLV31PBGKCPROT;
    extern  R_PBG40     PBG40;
    extern  uint32      PBGERRSLV40PBGKCPROT;
    extern  R_PBG41     PBG41;
    extern  uint32      PBGERRSLV41PBGKCPROT;
    extern  R_PBG50     PBG50;
    extern  uint32      PBGERRSLV50PBGKCPROT;
    extern  R_PBG51     PBG51;
    extern  uint32      PBGERRSLV51PBGKCPROT;
    extern  R_PBG52     PBG52;
    extern  uint32      PBGERRSLV52PBGKCPROT;
    extern  R_PBG60     PBG60;
    extern  uint32      PBGERRSLV60PBGKCPROT;
    extern  R_PBG61     PBG61;
    extern  uint32      PBGERRSLV61PBGKCPROT;
    extern  R_PBG7H0    PBG7H0;
    extern  uint32      PBGERRSLV7H0PBGKCPROT;
    extern  R_PBG7L0    PBG7L0;
    extern  uint32      PBGERRSLV7L0PBGKCPROT;
    extern  R_PBG8H0    PBG8H0;
    extern  uint32      PBGERRSLV8H0PBGKCPROT;
    extern  R_PBG8L0    PBG8L0;
    extern  uint32      PBGERRSLV8L0PBGKCPROT;
    extern  R_PBG90     PBG90;
    extern  uint32      PBGERRSLV90PBGKCPROT;
    extern  R_PBG91     PBG91;
    extern  uint32      PBGERRSLV91PBGKCPROT;
    extern  R_PBG100    PBG100;
    extern  uint32      PBGERRSLV100PBGKCPROT;
    extern  R_PBG101    PBG101;
    extern  uint32      PBGERRSLV101PBGKCPROT;
    extern  R_PBG11H0   PBG11H0;
    extern  uint32      PBGERRSLV11H0PBGKCPROT;
    extern  R_PBG11H1   PBG11H1;
    extern  uint32      PBGERRSLV11H1PBGKCPROT;
    extern  R_PBG11L0   PBG11L0;
    extern  uint32      PBGERRSLV11L0PBGKCPROT;


    #define PBG41PBGPROT0_0 PBG41.PBGPROT0_0
    #define PBG41PBGPROT1_0 PBG41.PBGPROT1_0

    #define PBG60PBGPROT0_0 PBG60.PBGPROT0_0
    #define PBG60PBGPROT1_0 PBG60.PBGPROT1_0
    #define PBG60PBGPROT0_1 PBG60.PBGPROT0_1
    #define PBG60PBGPROT1_1 PBG60.PBGPROT1_1
    #define PBG60PBGPROT0_2 PBG60.PBGPROT0_2
    #define PBG60PBGPROT1_2 PBG60.PBGPROT1_2
    #define PBG60PBGPROT0_3 PBG60.PBGPROT0_3
    #define PBG60PBGPROT1_3 PBG60.PBGPROT1_3
    #define PBG60PBGPROT0_4 PBG60.PBGPROT0_4
    #define PBG60PBGPROT1_4 PBG60.PBGPROT1_4
    #define PBG60PBGPROT0_5 PBG60.PBGPROT0_5
    #define PBG60PBGPROT1_5 PBG60.PBGPROT1_5
    #define PBG61PBGPROT0_0 PBG61.PBGPROT0_0
    #define PBG61PBGPROT1_0 PBG61.PBGPROT1_0
    #define PBG61PBGPROT0_1 PBG61.PBGPROT0_1
    #define PBG61PBGPROT1_1 PBG61.PBGPROT1_1
    #define PBG61PBGPROT0_2 PBG61.PBGPROT0_2
    #define PBG61PBGPROT1_2 PBG61.PBGPROT1_2

    #define PBG7H0PBGPROT0_0 PBG7H0.PBGPROT0_0
    #define PBG7H0PBGPROT1_0 PBG7H0.PBGPROT1_0
    #define PBG7H0PBGPROT0_1 PBG7H0.PBGPROT0_1
    #define PBG7H0PBGPROT1_1 PBG7H0.PBGPROT1_1

    #define PBG7L0PBGPROT0_0 PBG7L0.PBGPROT0_0
    #define PBG7L0PBGPROT1_0 PBG7L0.PBGPROT1_0
    #define PBG7L0PBGPROT0_1 PBG7L0.PBGPROT0_1
    #define PBG7L0PBGPROT1_1 PBG7L0.PBGPROT1_1
    #define PBG7L0PBGPROT0_2 PBG7L0.PBGPROT0_2
    #define PBG7L0PBGPROT1_2 PBG7L0.PBGPROT1_2

    #define PBG8H0PBGPROT0_0 PBG8H0.PBGPROT0_0
    #define PBG8H0PBGPROT1_0 PBG8H0.PBGPROT1_0
    #define PBG8H0PBGPROT0_1 PBG8H0.PBGPROT0_1
    #define PBG8H0PBGPROT1_1 PBG8H0.PBGPROT1_1
    #define PBG8H0PBGPROT0_2 PBG8H0.PBGPROT0_2
    #define PBG8H0PBGPROT1_2 PBG8H0.PBGPROT1_2
    #define PBG8H0PBGPROT0_3 PBG8H0.PBGPROT0_3
    #define PBG8H0PBGPROT1_3 PBG8H0.PBGPROT1_3
    #define PBG8H0PBGPROT0_4 PBG8H0.PBGPROT0_4
    #define PBG8H0PBGPROT1_4 PBG8H0.PBGPROT1_4
    #define PBG8H0PBGPROT0_5 PBG8H0.PBGPROT0_5
    #define PBG8H0PBGPROT1_5 PBG8H0.PBGPROT1_5

    #define PBG8L0PBGPROT0_0 PBG8L0.PBGPROT0_0
    #define PBG8L0PBGPROT1_0 PBG8L0.PBGPROT1_0
    #define PBG8L0PBGPROT0_1 PBG8L0.PBGPROT0_1
    #define PBG8L0PBGPROT1_1 PBG8L0.PBGPROT1_1
    #define PBG8L0PBGPROT0_2 PBG8L0.PBGPROT0_2
    #define PBG8L0PBGPROT1_2 PBG8L0.PBGPROT1_2
    #define PBG8L0PBGPROT0_3 PBG8L0.PBGPROT0_3
    #define PBG8L0PBGPROT1_3 PBG8L0.PBGPROT1_3
    #define PBG8L0PBGPROT0_4 PBG8L0.PBGPROT0_4
    #define PBG8L0PBGPROT1_4 PBG8L0.PBGPROT1_4
    #define PBG8L0PBGPROT0_5 PBG8L0.PBGPROT0_5
    #define PBG8L0PBGPROT1_5 PBG8L0.PBGPROT1_5
    #define PBG8L0PBGPROT0_6 PBG8L0.PBGPROT0_6
    #define PBG8L0PBGPROT1_6 PBG8L0.PBGPROT1_6
    #define PBG8L0PBGPROT0_7 PBG8L0.PBGPROT0_7
    #define PBG8L0PBGPROT1_7 PBG8L0.PBGPROT1_7
    #define PBG8L0PBGPROT0_8 PBG8L0.PBGPROT0_8
    #define PBG8L0PBGPROT1_8 PBG8L0.PBGPROT1_8
    #define PBG8L0PBGPROT0_9 PBG8L0.PBGPROT0_9
    #define PBG8L0PBGPROT1_9 PBG8L0.PBGPROT1_9
    #define PBG8L0PBGPROT0_10 PBG8L0.PBGPROT0_10
    #define PBG8L0PBGPROT1_10 PBG8L0.PBGPROT1_10
    #define PBG8L0PBGPROT0_11 PBG8L0.PBGPROT0_11
    #define PBG8L0PBGPROT1_11 PBG8L0.PBGPROT1_11
    #define PBG8L0PBGPROT0_12 PBG8L0.PBGPROT0_12
    #define PBG8L0PBGPROT1_12 PBG8L0.PBGPROT1_12
    #define PBG8L0PBGPROT0_13 PBG8L0.PBGPROT0_13
    #define PBG8L0PBGPROT1_13 PBG8L0.PBGPROT1_13

    #define PBG100PBGPROT0_0 PBG100.PBGPROT0_0
    #define PBG100PBGPROT1_0 PBG100.PBGPROT1_0
    #define PBG100PBGPROT0_1 PBG100.PBGPROT0_1
    #define PBG100PBGPROT1_1 PBG100.PBGPROT1_1
    #define PBG100PBGPROT0_2 PBG100.PBGPROT0_2
    #define PBG100PBGPROT1_2 PBG100.PBGPROT1_2
    #define PBG100PBGPROT0_3 PBG100.PBGPROT0_3
    #define PBG100PBGPROT1_3 PBG100.PBGPROT1_3
    #define PBG100PBGPROT0_4 PBG100.PBGPROT0_4
    #define PBG100PBGPROT1_4 PBG100.PBGPROT1_4
    #define PBG100PBGPROT0_5 PBG100.PBGPROT0_5
    #define PBG100PBGPROT1_5 PBG100.PBGPROT1_5
    #define PBG100PBGPROT0_6 PBG100.PBGPROT0_6
    #define PBG100PBGPROT1_6 PBG100.PBGPROT1_6
    #define PBG100PBGPROT0_7 PBG100.PBGPROT0_7
    #define PBG100PBGPROT1_7 PBG100.PBGPROT1_7
    #define PBG100PBGPROT0_8 PBG100.PBGPROT0_8
    #define PBG100PBGPROT1_8 PBG100.PBGPROT1_8
    #define PBG100PBGPROT0_9 PBG100.PBGPROT0_9
    #define PBG100PBGPROT1_9 PBG100.PBGPROT1_9
    #define PBG100PBGPROT0_10 PBG100.PBGPROT0_10
    #define PBG100PBGPROT1_10 PBG100.PBGPROT1_10
    #define PBG100PBGPROT0_11 PBG100.PBGPROT0_11
    #define PBG100PBGPROT1_11 PBG100.PBGPROT1_11
    #define PBG100PBGPROT0_13 PBG100.PBGPROT0_13
    #define PBG100PBGPROT1_13 PBG100.PBGPROT1_13
    #define PBG100PBGPROT0_14 PBG100.PBGPROT0_14
    #define PBG100PBGPROT1_14 PBG100.PBGPROT1_14
    #define PBG100PBGPROT0_15 PBG100.PBGPROT0_15
    #define PBG100PBGPROT1_15 PBG100.PBGPROT1_15
    #define PBG101PBGPROT0_0 PBG101.PBGPROT0_0
    #define PBG101PBGPROT1_0 PBG101.PBGPROT1_0
    #define PBG101PBGPROT0_1 PBG101.PBGPROT0_1
    #define PBG101PBGPROT1_1 PBG101.PBGPROT1_1
    #define PBG101PBGPROT0_2 PBG101.PBGPROT0_2
    #define PBG101PBGPROT1_2 PBG101.PBGPROT1_2
    #define PBG101PBGPROT0_3 PBG101.PBGPROT0_3
    #define PBG101PBGPROT1_3 PBG101.PBGPROT1_3
    #define PBG101PBGPROT0_4 PBG101.PBGPROT0_4
    #define PBG101PBGPROT1_4 PBG101.PBGPROT1_4
    #define PBG101PBGPROT0_5 PBG101.PBGPROT0_5
    #define PBG101PBGPROT1_5 PBG101.PBGPROT1_5
    #define PBG101PBGPROT0_6 PBG101.PBGPROT0_6
    #define PBG101PBGPROT1_6 PBG101.PBGPROT1_6

    #define PBG11H0PBGPROT0_0 PBG11H0.PBGPROT0_0
    #define PBG11H0PBGPROT1_0 PBG11H0.PBGPROT1_0
    #define PBG11H0PBGPROT0_1 PBG11H0.PBGPROT0_1
    #define PBG11H0PBGPROT1_1 PBG11H0.PBGPROT1_1
    #define PBG11H0PBGPROT0_2 PBG11H0.PBGPROT0_2
    #define PBG11H0PBGPROT1_2 PBG11H0.PBGPROT1_2
    #define PBG11H0PBGPROT0_3 PBG11H0.PBGPROT0_3
    #define PBG11H0PBGPROT1_3 PBG11H0.PBGPROT1_3
    #define PBG11H0PBGPROT0_4 PBG11H0.PBGPROT0_4
    #define PBG11H0PBGPROT1_4 PBG11H0.PBGPROT1_4
    #define PBG11H0PBGPROT0_5 PBG11H0.PBGPROT0_5
    #define PBG11H0PBGPROT1_5 PBG11H0.PBGPROT1_5
    #define PBG11H0PBGPROT0_6 PBG11H0.PBGPROT0_6
    #define PBG11H0PBGPROT1_6 PBG11H0.PBGPROT1_6
    #define PBG11H0PBGPROT0_7 PBG11H0.PBGPROT0_7
    #define PBG11H0PBGPROT1_7 PBG11H0.PBGPROT1_7
    #define PBG11H0PBGPROT0_8 PBG11H0.PBGPROT0_8
    #define PBG11H0PBGPROT1_8 PBG11H0.PBGPROT1_8
    #define PBG11H0PBGPROT0_9 PBG11H0.PBGPROT0_9
    #define PBG11H0PBGPROT1_9 PBG11H0.PBGPROT1_9
    #define PBG11H0PBGPROT0_10 PBG11H0.PBGPROT0_10
    #define PBG11H0PBGPROT1_10 PBG11H0.PBGPROT1_10
    #define PBG11H0PBGPROT0_11 PBG11H0.PBGPROT0_11
    #define PBG11H0PBGPROT1_11 PBG11H0.PBGPROT1_11
    #define PBG11H0PBGPROT0_12 PBG11H0.PBGPROT0_12
    #define PBG11H0PBGPROT1_12 PBG11H0.PBGPROT1_12
    #define PBG11H0PBGPROT0_13 PBG11H0.PBGPROT0_13
    #define PBG11H0PBGPROT1_13 PBG11H0.PBGPROT1_13
    #define PBG11H0PBGPROT0_14 PBG11H0.PBGPROT0_14
    #define PBG11H0PBGPROT1_14 PBG11H0.PBGPROT1_14
    #define PBG11H0PBGPROT0_15 PBG11H0.PBGPROT0_15
    #define PBG11H0PBGPROT1_15 PBG11H0.PBGPROT1_15
    #define PBG11H1PBGPROT0_0 PBG11H1.PBGPROT0_0
    #define PBG11H1PBGPROT1_0 PBG11H1.PBGPROT1_0
    #define PBG11H1PBGPROT0_1 PBG11H1.PBGPROT0_1
    #define PBG11H1PBGPROT1_1 PBG11H1.PBGPROT1_1
    #define PBG11H1PBGPROT0_2 PBG11H1.PBGPROT0_2
    #define PBG11H1PBGPROT1_2 PBG11H1.PBGPROT1_2
    #define PBG11H1PBGPROT0_3 PBG11H1.PBGPROT0_3
    #define PBG11H1PBGPROT1_3 PBG11H1.PBGPROT1_3
    #define PBG11H1PBGPROT0_4 PBG11H1.PBGPROT0_4
    #define PBG11H1PBGPROT1_4 PBG11H1.PBGPROT1_4
    #define PBG11H1PBGPROT0_5 PBG11H1.PBGPROT0_5
    #define PBG11H1PBGPROT1_5 PBG11H1.PBGPROT1_5
    #define PBG11H1PBGPROT0_6 PBG11H1.PBGPROT0_6
    #define PBG11H1PBGPROT1_6 PBG11H1.PBGPROT1_6

    #define PBG11L0PBGPROT0_0 PBG11L0.PBGPROT0_0
    #define PBG11L0PBGPROT1_0 PBG11L0.PBGPROT1_0
    #define PBG11L0PBGPROT0_1 PBG11L0.PBGPROT0_1
    #define PBG11L0PBGPROT1_1 PBG11L0.PBGPROT1_1

#endif

extern T_GUARD_CRAMCRG0 GUARD_CRAMCRG0;
extern uint32 GUARD_CRAMCRG0CRGKCPROT;
extern T_GUARD_CRAMCRG1 GUARD_CRAMCRG1;
extern uint32 GUARD_CRAMCRG1CRGKCPROT;
extern T_GUARD_CRAMCRG2 GUARD_CRAMCRG2;
extern uint32 GUARD_CRAMCRG2CRGKCPROT;
extern T_GUARD_CRAMCRG3 GUARD_CRAMCRG3;
extern uint32 GUARD_CRAMCRG3CRGKCPROT;
extern T_GUARD_CRAMCSG0 GUARD_CRAMCSG0;
extern T_GUARD_CRAMCSG1 GUARD_CRAMCSG1;
extern T_GUARD_CRAMCSG2 GUARD_CRAMCSG2;
extern T_GUARD_CRAMCSG3 GUARD_CRAMCSG3;



#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  typedef struct
  {                                                          /* Module           */
      uint32 BM17SPID;                                      /* BM17SPID         */
      uint8  dummy251[4];                                    /* Reserved         */
      uint32 BM19SPID;                                      /* BM19SPID         */
      uint8  dummy252[8];                                    /* Reserved         */
      uint32 BM22SPID;                                      /* BM22SPID         */
      uint32 BM23SPID;                                      /* BM23SPID         */
      uint32 BM24SPID;                                      /* BM24SPID         */
      uint32 BM25SPID;                                      /* BM25SPID         */
      uint32 BM26SPID;                                      /* BM26SPID         */
      uint8  dummy253[12];                                   /* Reserved         */
      uint32 BM30SPID;                                      /* BM30SPID         */
      uint8  dummy254[132];                                  /* Reserved         */
      uint32 BM00SPIDMSK;                                   /* BM00SPIDMSK      */
      uint32 BM01SPIDMSK;                                   /* BM01SPIDMSK      */
      uint32 BM02SPIDMSK;                                   /* BM02SPIDMSK      */
      uint32 BM03SPIDMSK;                                   /* BM03SPIDMSK      */
      uint8  dummy255[52];                                   /* Reserved         */
      uint32 BM17SPIDMSK;                                   /* BM17SPIDMSK      */
      uint8  dummy256[4];                                    /* Reserved         */
      uint32 BM19SPIDMSK;                                   /* BM19SPIDMSK      */
      uint8  dummy257[8];                                    /* Reserved         */
      uint32 BM22SPIDMSK;                                   /* BM22SPIDMSK      */
      uint32 BM23SPIDMSK;                                   /* BM23SPIDMSK      */
      uint32 BM24SPIDMSK;                                   /* BM24SPIDMSK      */
      uint32 BM25SPIDMSK;                                   /* BM25SPIDMSK      */
      uint32 BM26SPIDMSK;                                   /* BM26SPIDMSK      */
      uint32 BM27SPIDMSK;                                   /* BM27SPIDMSK      */
      uint32 BM28SPIDMSK;                                   /* BM28SPIDMSK      */
      uint32 BM29SPIDMSK;                                   /* BM29SPIDMSK      */
      uint32 BM30SPIDMSK;                                   /* BM30SPIDMSK      */
      uint32 BM31SPIDMSK;                                   /* BM31SPIDMSK      */
      uint8  dummy258[128];                                  /* Reserved         */
      uint32 BM00SPIDMSKLOCK;                               /* BM00SPIDMSKLOCK  */
      uint32 BM01SPIDMSKLOCK;                               /* BM01SPIDMSKLOCK  */
      uint32 BM02SPIDMSKLOCK;                               /* BM02SPIDMSKLOCK  */
      uint32 BM03SPIDMSKLOCK;                               /* BM03SPIDMSKLOCK  */
      uint8  dummy259[52];                                   /* Reserved         */
      uint32 BM17SPIDMSKLOCK;                               /* BM17SPIDMSKLOCK  */
      uint8  dummy260[4];                                    /* Reserved         */
      uint32 BM19SPIDMSKLOCK;                               /* BM19SPIDMSKLOCK  */
      uint8  dummy261[8];                                    /* Reserved         */
      uint32 BM22SPIDMSKLOCK;                               /* BM22SPIDMSKLOCK  */
      uint32 BM23SPIDMSKLOCK;                               /* BM23SPIDMSKLOCK  */
      uint32 BM24SPIDMSKLOCK;                               /* BM24SPIDMSKLOCK  */
      uint32 BM25SPIDMSKLOCK;                               /* BM25SPIDMSKLOCK  */
      uint32 BM26SPIDMSKLOCK;                               /* BM26SPIDMSKLOCK  */
      uint32 BM27SPIDMSKLOCK;                               /* BM27SPIDMSKLOCK  */
      uint32 BM28SPIDMSKLOCK;                               /* BM28SPIDMSKLOCK  */
      uint32 BM29SPIDMSKLOCK;                               /* BM29SPIDMSKLOCK  */
      uint32 BM30SPIDMSKLOCK;                               /* BM30SPIDMSKLOCK  */
      uint32 BM31SPIDMSKLOCK;                               /* BM31SPIDMSKLOCK  */
      uint8  dummy262[128];                                  /* Reserved         */
      uint32 SPIDKCPROT;                                    /* SPIDKCPROT       */
  } R_SPIDCTL;

  #define SPIDCTL               (GUARD_SPIDCTL) /* SPIDCTL */

  #define SPIDCTLBM17SPID SPIDCTL.BM17SPID
  #define SPIDCTLBM19SPID SPIDCTL.BM19SPID
  #define SPIDCTLBM22SPID SPIDCTL.BM22SPID
  #define SPIDCTLBM23SPID SPIDCTL.BM23SPID
  #define SPIDCTLBM24SPID SPIDCTL.BM24SPID
  #define SPIDCTLBM25SPID SPIDCTL.BM25SPID
  #define SPIDCTLBM26SPID SPIDCTL.BM26SPID
  #define SPIDCTLBM30SPID SPIDCTL.BM30SPID
  #define SPIDCTLBM00SPIDMSK SPIDCTL.BM00SPIDMSK
  #define SPIDCTLBM01SPIDMSK SPIDCTL.BM01SPIDMSK
  #define SPIDCTLBM02SPIDMSK SPIDCTL.BM02SPIDMSK
  #define SPIDCTLBM03SPIDMSK SPIDCTL.BM03SPIDMSK
  #define SPIDCTLBM17SPIDMSK SPIDCTL.BM17SPIDMSK
  #define SPIDCTLBM19SPIDMSK SPIDCTL.BM19SPIDMSK
  #define SPIDCTLBM22SPIDMSK SPIDCTL.BM22SPIDMSK
  #define SPIDCTLBM23SPIDMSK SPIDCTL.BM23SPIDMSK
  #define SPIDCTLBM24SPIDMSK SPIDCTL.BM24SPIDMSK
  #define SPIDCTLBM25SPIDMSK SPIDCTL.BM25SPIDMSK
  #define SPIDCTLBM26SPIDMSK SPIDCTL.BM26SPIDMSK
  #define SPIDCTLBM27SPIDMSK SPIDCTL.BM27SPIDMSK
  #define SPIDCTLBM28SPIDMSK SPIDCTL.BM28SPIDMSK
  #define SPIDCTLBM29SPIDMSK SPIDCTL.BM29SPIDMSK
  #define SPIDCTLBM30SPIDMSK SPIDCTL.BM30SPIDMSK
  #define SPIDCTLBM31SPIDMSK SPIDCTL.BM31SPIDMSK
  #define SPIDCTLBM00SPIDMSKLOCK SPIDCTL.BM00SPIDMSKLOCK
  #define SPIDCTLBM01SPIDMSKLOCK SPIDCTL.BM01SPIDMSKLOCK
  #define SPIDCTLBM02SPIDMSKLOCK SPIDCTL.BM02SPIDMSKLOCK
  #define SPIDCTLBM03SPIDMSKLOCK SPIDCTL.BM03SPIDMSKLOCK
  #define SPIDCTLBM17SPIDMSKLOCK SPIDCTL.BM17SPIDMSKLOCK
  #define SPIDCTLBM19SPIDMSKLOCK SPIDCTL.BM19SPIDMSKLOCK
  #define SPIDCTLBM22SPIDMSKLOCK SPIDCTL.BM22SPIDMSKLOCK
  #define SPIDCTLBM23SPIDMSKLOCK SPIDCTL.BM23SPIDMSKLOCK
  #define SPIDCTLBM24SPIDMSKLOCK SPIDCTL.BM24SPIDMSKLOCK
  #define SPIDCTLBM25SPIDMSKLOCK SPIDCTL.BM25SPIDMSKLOCK
  #define SPIDCTLBM26SPIDMSKLOCK SPIDCTL.BM26SPIDMSKLOCK
  #define SPIDCTLBM27SPIDMSKLOCK SPIDCTL.BM27SPIDMSKLOCK
  #define SPIDCTLBM28SPIDMSKLOCK SPIDCTL.BM28SPIDMSKLOCK
  #define SPIDCTLBM29SPIDMSKLOCK SPIDCTL.BM29SPIDMSKLOCK
  #define SPIDCTLBM30SPIDMSKLOCK SPIDCTL.BM30SPIDMSKLOCK
  #define SPIDCTLBM31SPIDMSKLOCK SPIDCTL.BM31SPIDMSKLOCK
  #define SPIDCTLSPIDKCPROT SPIDCTL.SPIDKCPROT
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  typedef struct
  {                                                          /* Module           */
      uint32 BM10SPID;                                      /* BM10SPID         */
      uint32 BM11SPID;                                      /* BM11SPID         */
      uint8  dummy112[36];                                   /* Reserved         */
      uint32 BM21SPID;                                      /* BM21SPID         */
      uint32 BM22SPID;                                      /* BM22SPID         */
      uint32 BM23SPID;                                      /* BM23SPID         */
      uint8  dummy113[12];                                   /* Reserved         */
      uint32 BM27SPID;                                      /* BM27SPID         */
      uint32 BM28SPID;                                      /* BM28SPID         */
      uint32 BM29SPID;                                      /* BM29SPID         */
      uint32 BM30SPID;                                      /* BM30SPID         */
      uint8  dummy114[4];                                    /* Reserved         */
      uint32 BM32SPID;                                      /* BM32SPID         */
      uint32 BM33SPID;                                      /* BM33SPID         */
      uint32 BM34SPID;                                      /* BM34SPID         */
      uint32 BM35SPID;                                      /* BM35SPID         */
      uint32 BM36SPID;                                      /* BM36SPID         */
      uint32 BM37SPID;                                      /* BM37SPID         */
      uint8  dummy115[20];                                   /* Reserved         */
      uint32 BM43SPID;                                      /* BM43SPID         */
      uint8  dummy116[80];                                   /* Reserved         */
      uint32 BM00SPIDMSK;                                   /* BM00SPIDMSK      */
      uint32 BM01SPIDMSK;                                   /* BM01SPIDMSK      */
      uint32 BM02SPIDMSK;                                   /* BM02SPIDMSK      */
      uint32 BM03SPIDMSK;                                   /* BM03SPIDMSK      */
      uint8  dummy117[24];                                   /* Reserved         */
      uint32 BM10SPIDMSK;                                   /* BM10SPIDMSK      */
      uint32 BM11SPIDMSK;                                   /* BM11SPIDMSK      */
      uint8  dummy118[36];                                   /* Reserved         */
      uint32 BM21SPIDMSK;                                   /* BM21SPIDMSK      */
      uint32 BM22SPIDMSK;                                   /* BM22SPIDMSK      */
      uint32 BM23SPIDMSK;                                   /* BM23SPIDMSK      */
      uint8  dummy119[12];                                   /* Reserved         */
      uint32 BM27SPIDMSK;                                   /* BM27SPIDMSK      */
      uint32 BM28SPIDMSK;                                   /* BM28SPIDMSK      */
      uint32 BM29SPIDMSK;                                   /* BM29SPIDMSK      */
      uint32 BM30SPIDMSK;                                   /* BM30SPIDMSK      */
      uint8  dummy120[4];                                    /* Reserved         */
      uint32 BM32SPIDMSK;                                   /* BM32SPIDMSK      */
      uint32 BM33SPIDMSK;                                   /* BM33SPIDMSK      */
      uint32 BM34SPIDMSK;                                   /* BM34SPIDMSK      */
      uint32 BM35SPIDMSK;                                   /* BM35SPIDMSK      */
      uint32 BM36SPIDMSK;                                   /* BM36SPIDMSK      */
      uint32 BM37SPIDMSK;                                   /* BM37SPIDMSK      */
      uint32 BM38SPIDMSK;                                   /* BM38SPIDMSK      */
      uint32 BM39SPIDMSK;                                   /* BM39SPIDMSK      */
      uint32 BM40SPIDMSK;                                   /* BM40SPIDMSK      */
      uint8  dummy121[4];                                    /* Reserved         */
      uint32 BM42SPIDMSK;                                   /* BM42SPIDMSK      */
      uint32 BM43SPIDMSK;                                   /* BM43SPIDMSK      */
      uint8  dummy122[80];                                   /* Reserved         */
      uint32 BM00SPIDMSKLOCK;                               /* BM00SPIDMSKLOCK  */
      uint32 BM01SPIDMSKLOCK;                               /* BM01SPIDMSKLOCK  */
      uint32 BM02SPIDMSKLOCK;                               /* BM02SPIDMSKLOCK  */
      uint32 BM03SPIDMSKLOCK;                               /* BM03SPIDMSKLOCK  */
      uint8  dummy123[24];                                   /* Reserved         */
      uint32 BM10SPIDMSKLOCK;                               /* BM10SPIDMSKLOCK  */
      uint32 BM11SPIDMSKLOCK;                               /* BM11SPIDMSKLOCK  */
      uint8  dummy124[36];                                   /* Reserved         */
      uint32 BM21SPIDMSKLOCK;                               /* BM21SPIDMSKLOCK  */
      uint32 BM22SPIDMSKLOCK;                               /* BM22SPIDMSKLOCK  */
      uint32 BM23SPIDMSKLOCK;                               /* BM23SPIDMSKLOCK  */
      uint8  dummy125[12];                                   /* Reserved         */
      uint32 BM27SPIDMSKLOCK;                               /* BM27SPIDMSKLOCK  */
      uint32 BM28SPIDMSKLOCK;                               /* BM28SPIDMSKLOCK  */
      uint32 BM29SPIDMSKLOCK;                               /* BM29SPIDMSKLOCK  */
      uint32 BM30SPIDMSKLOCK;                               /* BM30SPIDMSKLOCK  */
      uint8  dummy126[4];                                    /* Reserved         */
      uint32 BM32SPIDMSKLOCK;                               /* BM32SPIDMSKLOCK  */
      uint32 BM33SPIDMSKLOCK;                               /* BM33SPIDMSKLOCK  */
      uint32 BM34SPIDMSKLOCK;                               /* BM34SPIDMSKLOCK  */
      uint32 BM35SPIDMSKLOCK;                               /* BM35SPIDMSKLOCK  */
      uint32 BM36SPIDMSKLOCK;                               /* BM36SPIDMSKLOCK  */
      uint32 BM37SPIDMSKLOCK;                               /* BM37SPIDMSKLOCK  */
      uint32 BM38SPIDMSKLOCK;                               /* BM38SPIDMSKLOCK  */
      uint32 BM39SPIDMSKLOCK;                               /* BM39SPIDMSKLOCK  */
      uint32 BM40SPIDMSKLOCK;                               /* BM40SPIDMSKLOCK  */
      uint8  dummy127[4];                                    /* Reserved         */
      uint32 BM42SPIDMSKLOCK;                               /* BM42SPIDMSKLOCK  */
      uint32 BM43SPIDMSKLOCK;                               /* BM43SPIDMSKLOCK  */
      uint8  dummy128[80];                                   /* Reserved         */
      uint32 SPIDKCPROT;                                    /* SPIDKCPROT       */
  } R_SPIDCTL;

  extern volatile R_SPIDCTL GUARD_SPIDCTL;
  #define SPIDCTL               (GUARD_SPIDCTL) /* SPIDCTL */

  #define SPIDCTLBM10SPID SPIDCTL.BM10SPID
    #define SPIDCTLBM11SPID SPIDCTL.BM11SPID
    #define SPIDCTLBM21SPID SPIDCTL.BM21SPID
    #define SPIDCTLBM22SPID SPIDCTL.BM22SPID
    #define SPIDCTLBM23SPID SPIDCTL.BM23SPID
    #define SPIDCTLBM27SPID SPIDCTL.BM27SPID
    #define SPIDCTLBM28SPID SPIDCTL.BM28SPID
    #define SPIDCTLBM29SPID SPIDCTL.BM29SPID
    #define SPIDCTLBM30SPID SPIDCTL.BM30SPID
    #define SPIDCTLBM32SPID SPIDCTL.BM32SPID
    #define SPIDCTLBM33SPID SPIDCTL.BM33SPID
    #define SPIDCTLBM34SPID SPIDCTL.BM34SPID
    #define SPIDCTLBM35SPID SPIDCTL.BM35SPID
    #define SPIDCTLBM36SPID SPIDCTL.BM36SPID
    #define SPIDCTLBM37SPID SPIDCTL.BM37SPID
    #define SPIDCTLBM43SPID SPIDCTL.BM43SPID
    #define SPIDCTLBM00SPIDMSK SPIDCTL.BM00SPIDMSK
    #define SPIDCTLBM01SPIDMSK SPIDCTL.BM01SPIDMSK
    #define SPIDCTLBM02SPIDMSK SPIDCTL.BM02SPIDMSK
    #define SPIDCTLBM03SPIDMSK SPIDCTL.BM03SPIDMSK
    #define SPIDCTLBM10SPIDMSK SPIDCTL.BM10SPIDMSK
    #define SPIDCTLBM11SPIDMSK SPIDCTL.BM11SPIDMSK
    #define SPIDCTLBM21SPIDMSK SPIDCTL.BM21SPIDMSK
    #define SPIDCTLBM22SPIDMSK SPIDCTL.BM22SPIDMSK
    #define SPIDCTLBM23SPIDMSK SPIDCTL.BM23SPIDMSK
    #define SPIDCTLBM27SPIDMSK SPIDCTL.BM27SPIDMSK
    #define SPIDCTLBM28SPIDMSK SPIDCTL.BM28SPIDMSK
    #define SPIDCTLBM29SPIDMSK SPIDCTL.BM29SPIDMSK
    #define SPIDCTLBM30SPIDMSK SPIDCTL.BM30SPIDMSK
    #define SPIDCTLBM32SPIDMSK SPIDCTL.BM32SPIDMSK
    #define SPIDCTLBM33SPIDMSK SPIDCTL.BM33SPIDMSK
    #define SPIDCTLBM34SPIDMSK SPIDCTL.BM34SPIDMSK
    #define SPIDCTLBM35SPIDMSK SPIDCTL.BM35SPIDMSK
    #define SPIDCTLBM36SPIDMSK SPIDCTL.BM36SPIDMSK
    #define SPIDCTLBM37SPIDMSK SPIDCTL.BM37SPIDMSK
    #define SPIDCTLBM38SPIDMSK SPIDCTL.BM38SPIDMSK
    #define SPIDCTLBM39SPIDMSK SPIDCTL.BM39SPIDMSK
    #define SPIDCTLBM40SPIDMSK SPIDCTL.BM40SPIDMSK
    #define SPIDCTLBM42SPIDMSK SPIDCTL.BM42SPIDMSK
    #define SPIDCTLBM43SPIDMSK SPIDCTL.BM43SPIDMSK
    #define SPIDCTLBM00SPIDMSKLOCK SPIDCTL.BM00SPIDMSKLOCK
    #define SPIDCTLBM01SPIDMSKLOCK SPIDCTL.BM01SPIDMSKLOCK
    #define SPIDCTLBM02SPIDMSKLOCK SPIDCTL.BM02SPIDMSKLOCK
    #define SPIDCTLBM03SPIDMSKLOCK SPIDCTL.BM03SPIDMSKLOCK
    #define SPIDCTLBM10SPIDMSKLOCK SPIDCTL.BM10SPIDMSKLOCK
    #define SPIDCTLBM11SPIDMSKLOCK SPIDCTL.BM11SPIDMSKLOCK
    #define SPIDCTLBM21SPIDMSKLOCK SPIDCTL.BM21SPIDMSKLOCK
    #define SPIDCTLBM22SPIDMSKLOCK SPIDCTL.BM22SPIDMSKLOCK
    #define SPIDCTLBM23SPIDMSKLOCK SPIDCTL.BM23SPIDMSKLOCK
    #define SPIDCTLBM27SPIDMSKLOCK SPIDCTL.BM27SPIDMSKLOCK
    #define SPIDCTLBM28SPIDMSKLOCK SPIDCTL.BM28SPIDMSKLOCK
    #define SPIDCTLBM29SPIDMSKLOCK SPIDCTL.BM29SPIDMSKLOCK
    #define SPIDCTLBM30SPIDMSKLOCK SPIDCTL.BM30SPIDMSKLOCK
    #define SPIDCTLBM32SPIDMSKLOCK SPIDCTL.BM32SPIDMSKLOCK
    #define SPIDCTLBM33SPIDMSKLOCK SPIDCTL.BM33SPIDMSKLOCK
    #define SPIDCTLBM34SPIDMSKLOCK SPIDCTL.BM34SPIDMSKLOCK
    #define SPIDCTLBM35SPIDMSKLOCK SPIDCTL.BM35SPIDMSKLOCK
    #define SPIDCTLBM36SPIDMSKLOCK SPIDCTL.BM36SPIDMSKLOCK
    #define SPIDCTLBM37SPIDMSKLOCK SPIDCTL.BM37SPIDMSKLOCK
    #define SPIDCTLBM38SPIDMSKLOCK SPIDCTL.BM38SPIDMSKLOCK
    #define SPIDCTLBM39SPIDMSKLOCK SPIDCTL.BM39SPIDMSKLOCK
    #define SPIDCTLBM40SPIDMSKLOCK SPIDCTL.BM40SPIDMSKLOCK
    #define SPIDCTLBM42SPIDMSKLOCK SPIDCTL.BM42SPIDMSKLOCK
    #define SPIDCTLBM43SPIDMSKLOCK SPIDCTL.BM43SPIDMSKLOCK
    #define SPIDCTLSPIDKCPROT SPIDCTL.SPIDKCPROT

#endif




typedef struct
{                                                          /* Module           */
    uint32 HBGPROT0;                                      /* HBGPROT0         */
    uint32 HBGPROT1;                                      /* HBGPROT1         */
} R_HBG90;
typedef struct
{                                                          /* Module           */
    uint32 HBGPROT0;                                      /* HBGPROT0         */
    uint32 HBGPROT1;                                      /* HBGPROT1         */
} R_HBG91;
typedef struct
{                                                          /* Module           */
    uint32 HBGPROT0;                                      /* HBGPROT0         */
    uint32 HBGPROT1;                                      /* HBGPROT1         */
} R_HBG92;
typedef struct
{                                                          /* Module           */
    uint32 HBGPROT0;                                      /* HBGPROT0         */
    uint32 HBGPROT1;                                      /* HBGPROT1         */
} R_HBG93;
typedef struct
{                                                          /* Module           */
    uint32 HBGPROT0;                                      /* HBGPROT0         */
    uint32 HBGPROT1;                                      /* HBGPROT1         */
} R_HBG96;


extern volatile R_HBG90 GUARD_HBG90;
extern volatile R_HBG91 GUARD_HBG91;
extern volatile R_HBG92 GUARD_HBG92;
extern volatile R_HBG93 GUARD_HBG93;
extern volatile R_HBG96 GUARD_HBG96;


#define HBG90                (GUARD_HBG90) /* HBG90 */
#define HBG91                (GUARD_HBG91) /* HBG91 */
#define HBG92                (GUARD_HBG92) /* HBG92 */
#define HBG93                (GUARD_HBG93) /* HBG93 */
#define HBG96                (GUARD_HBG96) /* HBG96 */

#define HBG90HBGPROT0 HBG90.HBGPROT0
#define HBG90HBGPROT1 HBG90.HBGPROT1
#define HBG91HBGPROT0 HBG91.HBGPROT0
#define HBG91HBGPROT1 HBG91.HBGPROT1
#define HBG92HBGPROT0 HBG92.HBGPROT0
#define HBG92HBGPROT1 HBG92.HBGPROT1
#define HBG93HBGPROT0 HBG93.HBGPROT0
#define HBG93HBGPROT1 HBG93.HBGPROT1
#define HBG96HBGPROT0 HBG96.HBGPROT0
#define HBG96HBGPROT1 HBG96.HBGPROT1


typedef struct
{                                                          /* Module           */
    uint32 HBGOVFCLR;                                     /* HBGOVFCLR        */
    uint32 HBGOVFSTAT;                                    /* HBGOVFSTAT       */
    uint32 HBGERRADDR;                                     /* HBGERRADDR       */
    uint32 HBGERRTYPE;                                    /* HBGERRTYPE       */
    uint32 HBGSPIDERRCLR;                                  /* HBGSPIDERRCLR    */
    uint32 HBGSPIDERRSTAT;                                 /* HBGSPIDERRSTAT   */
    uint32 HBGKCPROT;                                      /* HBGKCPROT        */
} R_HBGHBGERRSLV92;
typedef struct
{                                                          /* Module           */
    uint32 HBGOVFCLR;                                     /* HBGOVFCLR        */
    uint32 HBGOVFSTAT;                                    /* HBGOVFSTAT       */
    uint32 HBGERRADDR;                                     /* HBGERRADDR       */
    uint32 HBGERRTYPE;                                    /* HBGERRTYPE       */
    uint32 HBGSPIDERRCLR;                                  /* HBGSPIDERRCLR    */
    uint32 HBGSPIDERRSTAT;                                 /* HBGSPIDERRSTAT   */
    uint32 HBGKCPROT;                                      /* HBGKCPROT        */
} R_HBGHBGERRSLV93;
typedef struct
{                                                          /* Module           */
    uint32 HBGOVFCLR;                                     /* HBGOVFCLR        */
    uint32 HBGOVFSTAT;                                    /* HBGOVFSTAT       */
    uint32 HBGERRADDR;                                     /* HBGERRADDR       */
    uint32 HBGERRTYPE;                                    /* HBGERRTYPE       */
    uint32 HBGSPIDERRCLR;                                  /* HBGSPIDERRCLR    */
    uint32 HBGSPIDERRSTAT;                                 /* HBGSPIDERRSTAT   */
    uint32 HBGKCPROT;                                      /* HBGKCPROT        */
} R_HBGHBGERRSLV96;
typedef struct
{                                                          /* Module           */
    uint32 HBGOVFCLR;                                     /* HBGOVFCLR        */
    uint32 HBGOVFSTAT;                                    /* HBGOVFSTAT       */
    uint32 HBGERRADDR;                                     /* HBGERRADDR       */
    uint32 HBGERRTYPE;                                    /* HBGERRTYPE       */
    uint32 HBGSPIDERRCLR;                                  /* HBGSPIDERRCLR    */
    uint32 HBGSPIDERRSTAT;                                 /* HBGSPIDERRSTAT   */
    uint32 HBGKCPROT;                                      /* HBGKCPROT        */
} R_HBGHBGERRSLV91;
typedef struct
{                                                          /* Module           */
    uint32 HBGOVFCLR;                                     /* HBGOVFCLR        */
    uint32 HBGOVFSTAT;                                    /* HBGOVFSTAT       */
    uint32 HBGERRADDR;                                     /* HBGERRADDR       */
    uint32 HBGERRTYPE;                                    /* HBGERRTYPE       */
    uint32 HBGSPIDERRCLR;                                  /* HBGSPIDERRCLR    */
    uint32 HBGSPIDERRSTAT;                                 /* HBGSPIDERRSTAT   */
    uint32 HBGKCPROT;                                      /* HBGKCPROT        */
} R_HBGHBGERRSLV90;

extern volatile R_HBGHBGERRSLV90 GUARD_HBGHBGERRSLV90;
extern volatile R_HBGHBGERRSLV91 GUARD_HBGHBGERRSLV91;
extern volatile R_HBGHBGERRSLV92 GUARD_HBGHBGERRSLV92;
extern volatile R_HBGHBGERRSLV93 GUARD_HBGHBGERRSLV93;
extern volatile R_HBGHBGERRSLV96 GUARD_HBGHBGERRSLV96;



#define HBGHBGERRSLV90HBGKCPROT GUARD_HBGHBGERRSLV90.HBGKCPROT
#define HBGHBGERRSLV91HBGKCPROT GUARD_HBGHBGERRSLV91.HBGKCPROT
#define HBGHBGERRSLV92HBGKCPROT GUARD_HBGHBGERRSLV92.HBGKCPROT
#define HBGHBGERRSLV93HBGKCPROT GUARD_HBGHBGERRSLV93.HBGKCPROT
#define HBGHBGERRSLV96HBGKCPROT GUARD_HBGHBGERRSLV96.HBGKCPROT

#define HBGERRSLV90HBGKCPROT HBGHBGERRSLV90HBGKCPROT
#define HBGERRSLV91HBGKCPROT HBGHBGERRSLV91HBGKCPROT
#define HBGERRSLV92HBGKCPROT HBGHBGERRSLV92HBGKCPROT
#define HBGERRSLV93HBGKCPROT HBGHBGERRSLV93HBGKCPROT
#define HBGERRSLV96HBGKCPROT HBGHBGERRSLV96HBGKCPROT

typedef struct
{                                                          /* Module           */
    uint32 INTC2GOVFCLR;                                  /* INTC2GOVFCLR     */
    uint32 INTC2GOVFSTAT;                                 /* INTC2GOVFSTAT    */
    uint32 INTC2GERRADDR;                                 /* INTC2GERRADDR    */
    uint32 INTC2GERRTYPE;                                 /* INTC2GERRTYPE    */
    uint32 INTC2GSPIDERRCLR;                              /* INTC2GSPIDERRCLR */
    uint32 INTC2GSPIDERRSTAT;                             /* INTC2GSPIDERRSTAT */
    uint32 INTC2GKCPROT;                                  /* INTC2GKCPROT     */
    uint8  dummy2418[36];                                  /* Reserved         */
    uint32 INTC2GMPID0;                                   /* INTC2GMPID0      */
    uint32 INTC2GMPID1;                                   /* INTC2GMPID1      */
    uint32 INTC2GMPID2;                                   /* INTC2GMPID2      */
    uint32 INTC2GMPID3;                                   /* INTC2GMPID3      */
    uint32 INTC2GMPID4;                                   /* INTC2GMPID4      */
    uint32 INTC2GMPID5;                                   /* INTC2GMPID5      */
    uint32 INTC2GMPID6;                                   /* INTC2GMPID6      */
    uint32 INTC2GMPID7;                                   /* INTC2GMPID7      */
    uint8  dummy2419[144];                                 /* Reserved         */
    uint32 INTC2GPROT_GR;                                 /* INTC2GPROT_GR    */
    uint32 INTC2GPROT_IMR;                                /* INTC2GPROT_IMR   */
    uint8  dummy2420[136];                                 /* Reserved         */
    uint32 INTC2GPROT_032;                                /* INTC2GPROT_032   */
    uint32 INTC2GPROT_033;                                /* INTC2GPROT_033   */
    uint32 INTC2GPROT_034;                                /* INTC2GPROT_034   */
    uint32 INTC2GPROT_035;                                /* INTC2GPROT_035   */
    uint32 INTC2GPROT_036;                                /* INTC2GPROT_036   */
    uint32 INTC2GPROT_037;                                /* INTC2GPROT_037   */
    uint32 INTC2GPROT_038;                                /* INTC2GPROT_038   */
    uint32 INTC2GPROT_039;                                /* INTC2GPROT_039   */
    uint32 INTC2GPROT_040;                                /* INTC2GPROT_040   */
    uint32 INTC2GPROT_041;                                /* INTC2GPROT_041   */
    uint32 INTC2GPROT_042;                                /* INTC2GPROT_042   */
    uint32 INTC2GPROT_043;                                /* INTC2GPROT_043   */
    uint32 INTC2GPROT_044;                                /* INTC2GPROT_044   */
    uint32 INTC2GPROT_045;                                /* INTC2GPROT_045   */
    uint32 INTC2GPROT_046;                                /* INTC2GPROT_046   */
    uint32 INTC2GPROT_047;                                /* INTC2GPROT_047   */
    uint32 INTC2GPROT_048;                                /* INTC2GPROT_048   */
    uint32 INTC2GPROT_049;                                /* INTC2GPROT_049   */
    uint32 INTC2GPROT_050;                                /* INTC2GPROT_050   */
    uint32 INTC2GPROT_051;                                /* INTC2GPROT_051   */
    uint32 INTC2GPROT_052;                                /* INTC2GPROT_052   */
    uint32 INTC2GPROT_053;                                /* INTC2GPROT_053   */
    uint32 INTC2GPROT_054;                                /* INTC2GPROT_054   */
    uint32 INTC2GPROT_055;                                /* INTC2GPROT_055   */
    uint32 INTC2GPROT_056;                                /* INTC2GPROT_056   */
    uint32 INTC2GPROT_057;                                /* INTC2GPROT_057   */
    uint32 INTC2GPROT_058;                                /* INTC2GPROT_058   */
    uint32 INTC2GPROT_059;                                /* INTC2GPROT_059   */
    uint32 INTC2GPROT_060;                                /* INTC2GPROT_060   */
    uint32 INTC2GPROT_061;                                /* INTC2GPROT_061   */
    uint32 INTC2GPROT_062;                                /* INTC2GPROT_062   */
    uint32 INTC2GPROT_063;                                /* INTC2GPROT_063   */
    uint32 INTC2GPROT_064;                                /* INTC2GPROT_064   */
    uint32 INTC2GPROT_065;                                /* INTC2GPROT_065   */
    uint32 INTC2GPROT_066;                                /* INTC2GPROT_066   */
    uint32 INTC2GPROT_067;                                /* INTC2GPROT_067   */
    uint32 INTC2GPROT_068;                                /* INTC2GPROT_068   */
    uint32 INTC2GPROT_069;                                /* INTC2GPROT_069   */
    uint32 INTC2GPROT_070;                                /* INTC2GPROT_070   */
    uint32 INTC2GPROT_071;                                /* INTC2GPROT_071   */
    uint32 INTC2GPROT_072;                                /* INTC2GPROT_072   */
    uint32 INTC2GPROT_073;                                /* INTC2GPROT_073   */
    uint32 INTC2GPROT_074;                                /* INTC2GPROT_074   */
    uint32 INTC2GPROT_075;                                /* INTC2GPROT_075   */
    uint32 INTC2GPROT_076;                                /* INTC2GPROT_076   */
    uint32 INTC2GPROT_077;                                /* INTC2GPROT_077   */
    uint32 INTC2GPROT_078;                                /* INTC2GPROT_078   */
    uint32 INTC2GPROT_079;                                /* INTC2GPROT_079   */
    uint32 INTC2GPROT_080;                                /* INTC2GPROT_080   */
    uint32 INTC2GPROT_081;                                /* INTC2GPROT_081   */
    uint32 INTC2GPROT_082;                                /* INTC2GPROT_082   */
    uint32 INTC2GPROT_083;                                /* INTC2GPROT_083   */
    uint32 INTC2GPROT_084;                                /* INTC2GPROT_084   */
    uint32 INTC2GPROT_085;                                /* INTC2GPROT_085   */
    uint32 INTC2GPROT_086;                                /* INTC2GPROT_086   */
    uint32 INTC2GPROT_087;                                /* INTC2GPROT_087   */
    uint32 INTC2GPROT_088;                                /* INTC2GPROT_088   */
    uint32 INTC2GPROT_089;                                /* INTC2GPROT_089   */
    uint32 INTC2GPROT_090;                                /* INTC2GPROT_090   */
    uint32 INTC2GPROT_091;                                /* INTC2GPROT_091   */
    uint32 INTC2GPROT_092;                                /* INTC2GPROT_092   */
    uint32 INTC2GPROT_093;                                /* INTC2GPROT_093   */
    uint32 INTC2GPROT_094;                                /* INTC2GPROT_094   */
    uint32 INTC2GPROT_095;                                /* INTC2GPROT_095   */
    uint32 INTC2GPROT_096;                                /* INTC2GPROT_096   */
    uint32 INTC2GPROT_097;                                /* INTC2GPROT_097   */
    uint32 INTC2GPROT_098;                                /* INTC2GPROT_098   */
    uint32 INTC2GPROT_099;                                /* INTC2GPROT_099   */
    uint32 INTC2GPROT_100;                                /* INTC2GPROT_100   */
    uint32 INTC2GPROT_101;                                /* INTC2GPROT_101   */
    uint32 INTC2GPROT_102;                                /* INTC2GPROT_102   */
    uint32 INTC2GPROT_103;                                /* INTC2GPROT_103   */
    uint32 INTC2GPROT_104;                                /* INTC2GPROT_104   */
    uint32 INTC2GPROT_105;                                /* INTC2GPROT_105   */
    uint32 INTC2GPROT_106;                                /* INTC2GPROT_106   */
    uint32 INTC2GPROT_107;                                /* INTC2GPROT_107   */
    uint32 INTC2GPROT_108;                                /* INTC2GPROT_108   */
    uint32 INTC2GPROT_109;                                /* INTC2GPROT_109   */
    uint32 INTC2GPROT_110;                                /* INTC2GPROT_110   */
    uint32 INTC2GPROT_111;                                /* INTC2GPROT_111   */
    uint32 INTC2GPROT_112;                                /* INTC2GPROT_112   */
    uint32 INTC2GPROT_113;                                /* INTC2GPROT_113   */
    uint32 INTC2GPROT_114;                                /* INTC2GPROT_114   */
    uint32 INTC2GPROT_115;                                /* INTC2GPROT_115   */
    uint32 INTC2GPROT_116;                                /* INTC2GPROT_116   */
    uint32 INTC2GPROT_117;                                /* INTC2GPROT_117   */
    uint32 INTC2GPROT_118;                                /* INTC2GPROT_118   */
    uint32 INTC2GPROT_119;                                /* INTC2GPROT_119   */
    uint32 INTC2GPROT_120;                                /* INTC2GPROT_120   */
    uint32 INTC2GPROT_121;                                /* INTC2GPROT_121   */
    uint32 INTC2GPROT_122;                                /* INTC2GPROT_122   */
    uint32 INTC2GPROT_123;                                /* INTC2GPROT_123   */
    uint32 INTC2GPROT_124;                                /* INTC2GPROT_124   */
    uint32 INTC2GPROT_125;                                /* INTC2GPROT_125   */
    uint32 INTC2GPROT_126;                                /* INTC2GPROT_126   */
    uint32 INTC2GPROT_127;                                /* INTC2GPROT_127   */
    uint32 INTC2GPROT_128;                                /* INTC2GPROT_128   */
    uint32 INTC2GPROT_129;                                /* INTC2GPROT_129   */
    uint32 INTC2GPROT_130;                                /* INTC2GPROT_130   */
    uint32 INTC2GPROT_131;                                /* INTC2GPROT_131   */
    uint32 INTC2GPROT_132;                                /* INTC2GPROT_132   */
    uint32 INTC2GPROT_133;                                /* INTC2GPROT_133   */
    uint32 INTC2GPROT_134;                                /* INTC2GPROT_134   */
    uint32 INTC2GPROT_135;                                /* INTC2GPROT_135   */
    uint32 INTC2GPROT_136;                                /* INTC2GPROT_136   */
    uint32 INTC2GPROT_137;                                /* INTC2GPROT_137   */
    uint32 INTC2GPROT_138;                                /* INTC2GPROT_138   */
    uint32 INTC2GPROT_139;                                /* INTC2GPROT_139   */
    uint32 INTC2GPROT_140;                                /* INTC2GPROT_140   */
    uint32 INTC2GPROT_141;                                /* INTC2GPROT_141   */
    uint32 INTC2GPROT_142;                                /* INTC2GPROT_142   */
    uint32 INTC2GPROT_143;                                /* INTC2GPROT_143   */
    uint32 INTC2GPROT_144;                                /* INTC2GPROT_144   */
    uint32 INTC2GPROT_145;                                /* INTC2GPROT_145   */
    uint32 INTC2GPROT_146;                                /* INTC2GPROT_146   */
    uint32 INTC2GPROT_147;                                /* INTC2GPROT_147   */
    uint32 INTC2GPROT_148;                                /* INTC2GPROT_148   */
    uint32 INTC2GPROT_149;                                /* INTC2GPROT_149   */
    uint32 INTC2GPROT_150;                                /* INTC2GPROT_150   */
    uint32 INTC2GPROT_151;                                /* INTC2GPROT_151   */
    uint32 INTC2GPROT_152;                                /* INTC2GPROT_152   */
    uint32 INTC2GPROT_153;                                /* INTC2GPROT_153   */
    uint32 INTC2GPROT_154;                                /* INTC2GPROT_154   */
    uint32 INTC2GPROT_155;                                /* INTC2GPROT_155   */
    uint32 INTC2GPROT_156;                                /* INTC2GPROT_156   */
    uint32 INTC2GPROT_157;                                /* INTC2GPROT_157   */
    uint32 INTC2GPROT_158;                                /* INTC2GPROT_158   */
    uint32 INTC2GPROT_159;                                /* INTC2GPROT_159   */
    uint32 INTC2GPROT_160;                                /* INTC2GPROT_160   */
    uint32 INTC2GPROT_161;                                /* INTC2GPROT_161   */
    uint32 INTC2GPROT_162;                                /* INTC2GPROT_162   */
    uint32 INTC2GPROT_163;                                /* INTC2GPROT_163   */
    uint32 INTC2GPROT_164;                                /* INTC2GPROT_164   */
    uint32 INTC2GPROT_165;                                /* INTC2GPROT_165   */
    uint32 INTC2GPROT_166;                                /* INTC2GPROT_166   */
    uint32 INTC2GPROT_167;                                /* INTC2GPROT_167   */
    uint32 INTC2GPROT_168;                                /* INTC2GPROT_168   */
    uint32 INTC2GPROT_169;                                /* INTC2GPROT_169   */
    uint32 INTC2GPROT_170;                                /* INTC2GPROT_170   */
    uint32 INTC2GPROT_171;                                /* INTC2GPROT_171   */
    uint32 INTC2GPROT_172;                                /* INTC2GPROT_172   */
    uint32 INTC2GPROT_173;                                /* INTC2GPROT_173   */
    uint32 INTC2GPROT_174;                                /* INTC2GPROT_174   */
    uint32 INTC2GPROT_175;                                /* INTC2GPROT_175   */
    uint32 INTC2GPROT_176;                                /* INTC2GPROT_176   */
    uint32 INTC2GPROT_177;                                /* INTC2GPROT_177   */
    uint32 INTC2GPROT_178;                                /* INTC2GPROT_178   */
    uint32 INTC2GPROT_179;                                /* INTC2GPROT_179   */
    uint32 INTC2GPROT_180;                                /* INTC2GPROT_180   */
    uint32 INTC2GPROT_181;                                /* INTC2GPROT_181   */
    uint32 INTC2GPROT_182;                                /* INTC2GPROT_182   */
    uint32 INTC2GPROT_183;                                /* INTC2GPROT_183   */
    uint32 INTC2GPROT_184;                                /* INTC2GPROT_184   */
    uint32 INTC2GPROT_185;                                /* INTC2GPROT_185   */
    uint32 INTC2GPROT_186;                                /* INTC2GPROT_186   */
    uint32 INTC2GPROT_187;                                /* INTC2GPROT_187   */
    uint32 INTC2GPROT_188;                                /* INTC2GPROT_188   */
    uint32 INTC2GPROT_189;                                /* INTC2GPROT_189   */
    uint32 INTC2GPROT_190;                                /* INTC2GPROT_190   */
    uint32 INTC2GPROT_191;                                /* INTC2GPROT_191   */
    uint32 INTC2GPROT_192;                                /* INTC2GPROT_192   */
    uint32 INTC2GPROT_193;                                /* INTC2GPROT_193   */
    uint32 INTC2GPROT_194;                                /* INTC2GPROT_194   */
    uint32 INTC2GPROT_195;                                /* INTC2GPROT_195   */
    uint32 INTC2GPROT_196;                                /* INTC2GPROT_196   */
    uint32 INTC2GPROT_197;                                /* INTC2GPROT_197   */
    uint32 INTC2GPROT_198;                                /* INTC2GPROT_198   */
    uint32 INTC2GPROT_199;                                /* INTC2GPROT_199   */
    uint32 INTC2GPROT_200;                                /* INTC2GPROT_200   */
    uint32 INTC2GPROT_201;                                /* INTC2GPROT_201   */
    uint32 INTC2GPROT_202;                                /* INTC2GPROT_202   */
    uint32 INTC2GPROT_203;                                /* INTC2GPROT_203   */
    uint32 INTC2GPROT_204;                                /* INTC2GPROT_204   */
    uint32 INTC2GPROT_205;                                /* INTC2GPROT_205   */
    uint32 INTC2GPROT_206;                                /* INTC2GPROT_206   */
    uint32 INTC2GPROT_207;                                /* INTC2GPROT_207   */
    uint32 INTC2GPROT_208;                                /* INTC2GPROT_208   */
    uint32 INTC2GPROT_209;                                /* INTC2GPROT_209   */
    uint32 INTC2GPROT_210;                                /* INTC2GPROT_210   */
    uint32 INTC2GPROT_211;                                /* INTC2GPROT_211   */
    uint32 INTC2GPROT_212;                                /* INTC2GPROT_212   */
    uint32 INTC2GPROT_213;                                /* INTC2GPROT_213   */
    uint32 INTC2GPROT_214;                                /* INTC2GPROT_214   */
    uint32 INTC2GPROT_215;                                /* INTC2GPROT_215   */
    uint32 INTC2GPROT_216;                                /* INTC2GPROT_216   */
    uint32 INTC2GPROT_217;                                /* INTC2GPROT_217   */
    uint32 INTC2GPROT_218;                                /* INTC2GPROT_218   */
    uint32 INTC2GPROT_219;                                /* INTC2GPROT_219   */
    uint32 INTC2GPROT_220;                                /* INTC2GPROT_220   */
    uint32 INTC2GPROT_221;                                /* INTC2GPROT_221   */
    uint32 INTC2GPROT_222;                                /* INTC2GPROT_222   */
    uint32 INTC2GPROT_223;                                /* INTC2GPROT_223   */
    uint32 INTC2GPROT_224;                                /* INTC2GPROT_224   */
    uint32 INTC2GPROT_225;                                /* INTC2GPROT_225   */
    uint32 INTC2GPROT_226;                                /* INTC2GPROT_226   */
    uint32 INTC2GPROT_227;                                /* INTC2GPROT_227   */
    uint32 INTC2GPROT_228;                                /* INTC2GPROT_228   */
    uint32 INTC2GPROT_229;                                /* INTC2GPROT_229   */
    uint32 INTC2GPROT_230;                                /* INTC2GPROT_230   */
    uint32 INTC2GPROT_231;                                /* INTC2GPROT_231   */
    uint32 INTC2GPROT_232;                                /* INTC2GPROT_232   */
    uint32 INTC2GPROT_233;                                /* INTC2GPROT_233   */
    uint32 INTC2GPROT_234;                                /* INTC2GPROT_234   */
    uint32 INTC2GPROT_235;                                /* INTC2GPROT_235   */
    uint32 INTC2GPROT_236;                                /* INTC2GPROT_236   */
    uint32 INTC2GPROT_237;                                /* INTC2GPROT_237   */
    uint32 INTC2GPROT_238;                                /* INTC2GPROT_238   */
    uint32 INTC2GPROT_239;                                /* INTC2GPROT_239   */
    uint32 INTC2GPROT_240;                                /* INTC2GPROT_240   */
    uint32 INTC2GPROT_241;                                /* INTC2GPROT_241   */
    uint32 INTC2GPROT_242;                                /* INTC2GPROT_242   */
    uint32 INTC2GPROT_243;                                /* INTC2GPROT_243   */
    uint32 INTC2GPROT_244;                                /* INTC2GPROT_244   */
    uint32 INTC2GPROT_245;                                /* INTC2GPROT_245   */
    uint32 INTC2GPROT_246;                                /* INTC2GPROT_246   */
    uint32 INTC2GPROT_247;                                /* INTC2GPROT_247   */
    uint32 INTC2GPROT_248;                                /* INTC2GPROT_248   */
    uint32 INTC2GPROT_249;                                /* INTC2GPROT_249   */
    uint32 INTC2GPROT_250;                                /* INTC2GPROT_250   */
    uint32 INTC2GPROT_251;                                /* INTC2GPROT_251   */
    uint32 INTC2GPROT_252;                                /* INTC2GPROT_252   */
    uint32 INTC2GPROT_253;                                /* INTC2GPROT_253   */
    uint32 INTC2GPROT_254;                                /* INTC2GPROT_254   */
    uint32 INTC2GPROT_255;                                /* INTC2GPROT_255   */
    uint32 INTC2GPROT_256;                                /* INTC2GPROT_256   */
    uint32 INTC2GPROT_257;                                /* INTC2GPROT_257   */
    uint32 INTC2GPROT_258;                                /* INTC2GPROT_258   */
    uint32 INTC2GPROT_259;                                /* INTC2GPROT_259   */
    uint32 INTC2GPROT_260;                                /* INTC2GPROT_260   */
    uint32 INTC2GPROT_261;                                /* INTC2GPROT_261   */
    uint32 INTC2GPROT_262;                                /* INTC2GPROT_262   */
    uint32 INTC2GPROT_263;                                /* INTC2GPROT_263   */
    uint32 INTC2GPROT_264;                                /* INTC2GPROT_264   */
    uint32 INTC2GPROT_265;                                /* INTC2GPROT_265   */
    uint32 INTC2GPROT_266;                                /* INTC2GPROT_266   */
    uint32 INTC2GPROT_267;                                /* INTC2GPROT_267   */
    uint32 INTC2GPROT_268;                                /* INTC2GPROT_268   */
    uint32 INTC2GPROT_269;                                /* INTC2GPROT_269   */
    uint32 INTC2GPROT_270;                                /* INTC2GPROT_270   */
    uint32 INTC2GPROT_271;                                /* INTC2GPROT_271   */
    uint32 INTC2GPROT_272;                                /* INTC2GPROT_272   */
    uint32 INTC2GPROT_273;                                /* INTC2GPROT_273   */
    uint32 INTC2GPROT_274;                                /* INTC2GPROT_274   */
    uint32 INTC2GPROT_275;                                /* INTC2GPROT_275   */
    uint32 INTC2GPROT_276;                                /* INTC2GPROT_276   */
    uint32 INTC2GPROT_277;                                /* INTC2GPROT_277   */
    uint32 INTC2GPROT_278;                                /* INTC2GPROT_278   */
    uint32 INTC2GPROT_279;                                /* INTC2GPROT_279   */
    uint32 INTC2GPROT_280;                                /* INTC2GPROT_280   */
    uint32 INTC2GPROT_281;                                /* INTC2GPROT_281   */
    uint32 INTC2GPROT_282;                                /* INTC2GPROT_282   */
    uint32 INTC2GPROT_283;                                /* INTC2GPROT_283   */
    uint32 INTC2GPROT_284;                                /* INTC2GPROT_284   */
    uint32 INTC2GPROT_285;                                /* INTC2GPROT_285   */
    uint32 INTC2GPROT_286;                                /* INTC2GPROT_286   */
    uint32 INTC2GPROT_287;                                /* INTC2GPROT_287   */
    uint32 INTC2GPROT_288;                                /* INTC2GPROT_288   */
    uint32 INTC2GPROT_289;                                /* INTC2GPROT_289   */
    uint32 INTC2GPROT_290;                                /* INTC2GPROT_290   */
    uint32 INTC2GPROT_291;                                /* INTC2GPROT_291   */
    uint32 INTC2GPROT_292;                                /* INTC2GPROT_292   */
    uint32 INTC2GPROT_293;                                /* INTC2GPROT_293   */
    uint32 INTC2GPROT_294;                                /* INTC2GPROT_294   */
    uint32 INTC2GPROT_295;                                /* INTC2GPROT_295   */
    uint32 INTC2GPROT_296;                                /* INTC2GPROT_296   */
    uint32 INTC2GPROT_297;                                /* INTC2GPROT_297   */
    uint32 INTC2GPROT_298;                                /* INTC2GPROT_298   */
    uint32 INTC2GPROT_299;                                /* INTC2GPROT_299   */
    uint32 INTC2GPROT_300;                                /* INTC2GPROT_300   */
    uint32 INTC2GPROT_301;                                /* INTC2GPROT_301   */
    uint32 INTC2GPROT_302;                                /* INTC2GPROT_302   */
    uint32 INTC2GPROT_303;                                /* INTC2GPROT_303   */
    uint32 INTC2GPROT_304;                                /* INTC2GPROT_304   */
    uint32 INTC2GPROT_305;                                /* INTC2GPROT_305   */
    uint32 INTC2GPROT_306;                                /* INTC2GPROT_306   */
    uint32 INTC2GPROT_307;                                /* INTC2GPROT_307   */
    uint32 INTC2GPROT_308;                                /* INTC2GPROT_308   */
    uint32 INTC2GPROT_309;                                /* INTC2GPROT_309   */
    uint32 INTC2GPROT_310;                                /* INTC2GPROT_310   */
    uint32 INTC2GPROT_311;                                /* INTC2GPROT_311   */
    uint32 INTC2GPROT_312;                                /* INTC2GPROT_312   */
    uint32 INTC2GPROT_313;                                /* INTC2GPROT_313   */
    uint32 INTC2GPROT_314;                                /* INTC2GPROT_314   */
    uint32 INTC2GPROT_315;                                /* INTC2GPROT_315   */
    uint32 INTC2GPROT_316;                                /* INTC2GPROT_316   */
    uint32 INTC2GPROT_317;                                /* INTC2GPROT_317   */
    uint32 INTC2GPROT_318;                                /* INTC2GPROT_318   */
    uint32 INTC2GPROT_319;                                /* INTC2GPROT_319   */
    uint32 INTC2GPROT_320;                                /* INTC2GPROT_320   */
    uint32 INTC2GPROT_321;                                /* INTC2GPROT_321   */
    uint32 INTC2GPROT_322;                                /* INTC2GPROT_322   */
    uint32 INTC2GPROT_323;                                /* INTC2GPROT_323   */
    uint32 INTC2GPROT_324;                                /* INTC2GPROT_324   */
    uint32 INTC2GPROT_325;                                /* INTC2GPROT_325   */
    uint32 INTC2GPROT_326;                                /* INTC2GPROT_326   */
    uint32 INTC2GPROT_327;                                /* INTC2GPROT_327   */
    uint32 INTC2GPROT_328;                                /* INTC2GPROT_328   */
    uint32 INTC2GPROT_329;                                /* INTC2GPROT_329   */
    uint32 INTC2GPROT_330;                                /* INTC2GPROT_330   */
    uint32 INTC2GPROT_331;                                /* INTC2GPROT_331   */
    uint32 INTC2GPROT_332;                                /* INTC2GPROT_332   */
    uint32 INTC2GPROT_333;                                /* INTC2GPROT_333   */
    uint32 INTC2GPROT_334;                                /* INTC2GPROT_334   */
    uint32 INTC2GPROT_335;                                /* INTC2GPROT_335   */
    uint32 INTC2GPROT_336;                                /* INTC2GPROT_336   */
    uint32 INTC2GPROT_337;                                /* INTC2GPROT_337   */
    uint32 INTC2GPROT_338;                                /* INTC2GPROT_338   */
    uint32 INTC2GPROT_339;                                /* INTC2GPROT_339   */
    uint32 INTC2GPROT_340;                                /* INTC2GPROT_340   */
    uint32 INTC2GPROT_341;                                /* INTC2GPROT_341   */
    uint32 INTC2GPROT_342;                                /* INTC2GPROT_342   */
    uint32 INTC2GPROT_343;                                /* INTC2GPROT_343   */
    uint32 INTC2GPROT_344;                                /* INTC2GPROT_344   */
    uint32 INTC2GPROT_345;                                /* INTC2GPROT_345   */
    uint32 INTC2GPROT_346;                                /* INTC2GPROT_346   */
    uint32 INTC2GPROT_347;                                /* INTC2GPROT_347   */
    uint32 INTC2GPROT_348;                                /* INTC2GPROT_348   */
    uint32 INTC2GPROT_349;                                /* INTC2GPROT_349   */
    uint32 INTC2GPROT_350;                                /* INTC2GPROT_350   */
    uint32 INTC2GPROT_351;                                /* INTC2GPROT_351   */
    uint32 INTC2GPROT_352;                                /* INTC2GPROT_352   */
    uint32 INTC2GPROT_353;                                /* INTC2GPROT_353   */
    uint32 INTC2GPROT_354;                                /* INTC2GPROT_354   */
    uint32 INTC2GPROT_355;                                /* INTC2GPROT_355   */
    uint32 INTC2GPROT_356;                                /* INTC2GPROT_356   */
    uint32 INTC2GPROT_357;                                /* INTC2GPROT_357   */
    uint32 INTC2GPROT_358;                                /* INTC2GPROT_358   */
    uint32 INTC2GPROT_359;                                /* INTC2GPROT_359   */
    uint32 INTC2GPROT_360;                                /* INTC2GPROT_360   */
    uint32 INTC2GPROT_361;                                /* INTC2GPROT_361   */
    uint32 INTC2GPROT_362;                                /* INTC2GPROT_362   */
    uint32 INTC2GPROT_363;                                /* INTC2GPROT_363   */
    uint32 INTC2GPROT_364;                                /* INTC2GPROT_364   */
    uint32 INTC2GPROT_365;                                /* INTC2GPROT_365   */
    uint32 INTC2GPROT_366;                                /* INTC2GPROT_366   */
    uint32 INTC2GPROT_367;                                /* INTC2GPROT_367   */
    uint32 INTC2GPROT_368;                                /* INTC2GPROT_368   */
    uint32 INTC2GPROT_369;                                /* INTC2GPROT_369   */
    uint32 INTC2GPROT_370;                                /* INTC2GPROT_370   */
    uint32 INTC2GPROT_371;                                /* INTC2GPROT_371   */
    uint32 INTC2GPROT_372;                                /* INTC2GPROT_372   */
    uint32 INTC2GPROT_373;                                /* INTC2GPROT_373   */
    uint32 INTC2GPROT_374;                                /* INTC2GPROT_374   */
    uint32 INTC2GPROT_375;                                /* INTC2GPROT_375   */
    uint32 INTC2GPROT_376;                                /* INTC2GPROT_376   */
    uint32 INTC2GPROT_377;                                /* INTC2GPROT_377   */
    uint32 INTC2GPROT_378;                                /* INTC2GPROT_378   */
    uint32 INTC2GPROT_379;                                /* INTC2GPROT_379   */
    uint32 INTC2GPROT_380;                                /* INTC2GPROT_380   */
    uint32 INTC2GPROT_381;                                /* INTC2GPROT_381   */
    uint32 INTC2GPROT_382;                                /* INTC2GPROT_382   */
    uint32 INTC2GPROT_383;                                /* INTC2GPROT_383   */
    uint32 INTC2GPROT_384;                                /* INTC2GPROT_384   */
    uint32 INTC2GPROT_385;                                /* INTC2GPROT_385   */
    uint32 INTC2GPROT_386;                                /* INTC2GPROT_386   */
    uint32 INTC2GPROT_387;                                /* INTC2GPROT_387   */
    uint32 INTC2GPROT_388;                                /* INTC2GPROT_388   */
    uint32 INTC2GPROT_389;                                /* INTC2GPROT_389   */
    uint32 INTC2GPROT_390;                                /* INTC2GPROT_390   */
    uint32 INTC2GPROT_391;                                /* INTC2GPROT_391   */
    uint32 INTC2GPROT_392;                                /* INTC2GPROT_392   */
    uint32 INTC2GPROT_393;                                /* INTC2GPROT_393   */
    uint32 INTC2GPROT_394;                                /* INTC2GPROT_394   */
    uint32 INTC2GPROT_395;                                /* INTC2GPROT_395   */
    uint32 INTC2GPROT_396;                                /* INTC2GPROT_396   */
    uint32 INTC2GPROT_397;                                /* INTC2GPROT_397   */
    uint32 INTC2GPROT_398;                                /* INTC2GPROT_398   */
    uint32 INTC2GPROT_399;                                /* INTC2GPROT_399   */
    uint32 INTC2GPROT_400;                                /* INTC2GPROT_400   */
    uint32 INTC2GPROT_401;                                /* INTC2GPROT_401   */
    uint32 INTC2GPROT_402;                                /* INTC2GPROT_402   */
    uint32 INTC2GPROT_403;                                /* INTC2GPROT_403   */
    uint32 INTC2GPROT_404;                                /* INTC2GPROT_404   */
    uint32 INTC2GPROT_405;                                /* INTC2GPROT_405   */
    uint32 INTC2GPROT_406;                                /* INTC2GPROT_406   */
    uint32 INTC2GPROT_407;                                /* INTC2GPROT_407   */
    uint32 INTC2GPROT_408;                                /* INTC2GPROT_408   */
    uint32 INTC2GPROT_409;                                /* INTC2GPROT_409   */
    uint32 INTC2GPROT_410;                                /* INTC2GPROT_410   */
    uint32 INTC2GPROT_411;                                /* INTC2GPROT_411   */
    uint32 INTC2GPROT_412;                                /* INTC2GPROT_412   */
    uint32 INTC2GPROT_413;                                /* INTC2GPROT_413   */
    uint32 INTC2GPROT_414;                                /* INTC2GPROT_414   */
    uint32 INTC2GPROT_415;                                /* INTC2GPROT_415   */
    uint32 INTC2GPROT_416;                                /* INTC2GPROT_416   */
    uint32 INTC2GPROT_417;                                /* INTC2GPROT_417   */
    uint32 INTC2GPROT_418;                                /* INTC2GPROT_418   */
    uint32 INTC2GPROT_419;                                /* INTC2GPROT_419   */
    uint32 INTC2GPROT_420;                                /* INTC2GPROT_420   */
    uint32 INTC2GPROT_421;                                /* INTC2GPROT_421   */
    uint32 INTC2GPROT_422;                                /* INTC2GPROT_422   */
    uint32 INTC2GPROT_423;                                /* INTC2GPROT_423   */
    uint32 INTC2GPROT_424;                                /* INTC2GPROT_424   */
    uint32 INTC2GPROT_425;                                /* INTC2GPROT_425   */
    uint32 INTC2GPROT_426;                                /* INTC2GPROT_426   */
    uint32 INTC2GPROT_427;                                /* INTC2GPROT_427   */
    uint32 INTC2GPROT_428;                                /* INTC2GPROT_428   */
    uint32 INTC2GPROT_429;                                /* INTC2GPROT_429   */
    uint32 INTC2GPROT_430;                                /* INTC2GPROT_430   */
    uint32 INTC2GPROT_431;                                /* INTC2GPROT_431   */
    uint32 INTC2GPROT_432;                                /* INTC2GPROT_432   */
    uint32 INTC2GPROT_433;                                /* INTC2GPROT_433   */
    uint32 INTC2GPROT_434;                                /* INTC2GPROT_434   */
    uint32 INTC2GPROT_435;                                /* INTC2GPROT_435   */
    uint32 INTC2GPROT_436;                                /* INTC2GPROT_436   */
    uint32 INTC2GPROT_437;                                /* INTC2GPROT_437   */
    uint32 INTC2GPROT_438;                                /* INTC2GPROT_438   */
    uint32 INTC2GPROT_439;                                /* INTC2GPROT_439   */
    uint32 INTC2GPROT_440;                                /* INTC2GPROT_440   */
    uint32 INTC2GPROT_441;                                /* INTC2GPROT_441   */
    uint32 INTC2GPROT_442;                                /* INTC2GPROT_442   */
    uint32 INTC2GPROT_443;                                /* INTC2GPROT_443   */
    uint32 INTC2GPROT_444;                                /* INTC2GPROT_444   */
    uint32 INTC2GPROT_445;                                /* INTC2GPROT_445   */
    uint32 INTC2GPROT_446;                                /* INTC2GPROT_446   */
    uint32 INTC2GPROT_447;                                /* INTC2GPROT_447   */
    uint32 INTC2GPROT_448;                                /* INTC2GPROT_448   */
    uint32 INTC2GPROT_449;                                /* INTC2GPROT_449   */
    uint32 INTC2GPROT_450;                                /* INTC2GPROT_450   */
    uint32 INTC2GPROT_451;                                /* INTC2GPROT_451   */
    uint32 INTC2GPROT_452;                                /* INTC2GPROT_452   */
    uint32 INTC2GPROT_453;                                /* INTC2GPROT_453   */
    uint32 INTC2GPROT_454;                                /* INTC2GPROT_454   */
    uint32 INTC2GPROT_455;                                /* INTC2GPROT_455   */
    uint32 INTC2GPROT_456;                                /* INTC2GPROT_456   */
    uint32 INTC2GPROT_457;                                /* INTC2GPROT_457   */
    uint32 INTC2GPROT_458;                                /* INTC2GPROT_458   */
    uint32 INTC2GPROT_459;                                /* INTC2GPROT_459   */
    uint32 INTC2GPROT_460;                                /* INTC2GPROT_460   */
    uint32 INTC2GPROT_461;                                /* INTC2GPROT_461   */
    uint32 INTC2GPROT_462;                                /* INTC2GPROT_462   */
    uint32 INTC2GPROT_463;                                /* INTC2GPROT_463   */
    uint32 INTC2GPROT_464;                                /* INTC2GPROT_464   */
    uint32 INTC2GPROT_465;                                /* INTC2GPROT_465   */
    uint32 INTC2GPROT_466;                                /* INTC2GPROT_466   */
    uint32 INTC2GPROT_467;                                /* INTC2GPROT_467   */
    uint32 INTC2GPROT_468;                                /* INTC2GPROT_468   */
    uint32 INTC2GPROT_469;                                /* INTC2GPROT_469   */
    uint32 INTC2GPROT_470;                                /* INTC2GPROT_470   */
    uint32 INTC2GPROT_471;                                /* INTC2GPROT_471   */
    uint32 INTC2GPROT_472;                                /* INTC2GPROT_472   */
    uint32 INTC2GPROT_473;                                /* INTC2GPROT_473   */
    uint32 INTC2GPROT_474;                                /* INTC2GPROT_474   */
    uint32 INTC2GPROT_475;                                /* INTC2GPROT_475   */
    uint32 INTC2GPROT_476;                                /* INTC2GPROT_476   */
    uint32 INTC2GPROT_477;                                /* INTC2GPROT_477   */
    uint32 INTC2GPROT_478;                                /* INTC2GPROT_478   */
    uint32 INTC2GPROT_479;                                /* INTC2GPROT_479   */
    uint32 INTC2GPROT_480;                                /* INTC2GPROT_480   */
    uint32 INTC2GPROT_481;                                /* INTC2GPROT_481   */
    uint32 INTC2GPROT_482;                                /* INTC2GPROT_482   */
    uint32 INTC2GPROT_483;                                /* INTC2GPROT_483   */
    uint32 INTC2GPROT_484;                                /* INTC2GPROT_484   */
    uint32 INTC2GPROT_485;                                /* INTC2GPROT_485   */
    uint32 INTC2GPROT_486;                                /* INTC2GPROT_486   */
    uint32 INTC2GPROT_487;                                /* INTC2GPROT_487   */
    uint32 INTC2GPROT_488;                                /* INTC2GPROT_488   */
    uint32 INTC2GPROT_489;                                /* INTC2GPROT_489   */
    uint32 INTC2GPROT_490;                                /* INTC2GPROT_490   */
    uint32 INTC2GPROT_491;                                /* INTC2GPROT_491   */
    uint32 INTC2GPROT_492;                                /* INTC2GPROT_492   */
    uint32 INTC2GPROT_493;                                /* INTC2GPROT_493   */
    uint32 INTC2GPROT_494;                                /* INTC2GPROT_494   */
    uint32 INTC2GPROT_495;                                /* INTC2GPROT_495   */
    uint32 INTC2GPROT_496;                                /* INTC2GPROT_496   */
    uint32 INTC2GPROT_497;                                /* INTC2GPROT_497   */
    uint32 INTC2GPROT_498;                                /* INTC2GPROT_498   */
    uint32 INTC2GPROT_499;                                /* INTC2GPROT_499   */
    uint32 INTC2GPROT_500;                                /* INTC2GPROT_500   */
    uint32 INTC2GPROT_501;                                /* INTC2GPROT_501   */
    uint32 INTC2GPROT_502;                                /* INTC2GPROT_502   */
    uint32 INTC2GPROT_503;                                /* INTC2GPROT_503   */
    uint32 INTC2GPROT_504;                                /* INTC2GPROT_504   */
    uint32 INTC2GPROT_505;                                /* INTC2GPROT_505   */
    uint32 INTC2GPROT_506;                                /* INTC2GPROT_506   */
    uint32 INTC2GPROT_507;                                /* INTC2GPROT_507   */
    uint32 INTC2GPROT_508;                                /* INTC2GPROT_508   */
    uint32 INTC2GPROT_509;                                /* INTC2GPROT_509   */
    uint32 INTC2GPROT_510;                                /* INTC2GPROT_510   */
    uint32 INTC2GPROT_511;                                /* INTC2GPROT_511   */
    uint32 INTC2GPROT_512;                                /* INTC2GPROT_512   */
    uint32 INTC2GPROT_513;                                /* INTC2GPROT_513   */
    uint32 INTC2GPROT_514;                                /* INTC2GPROT_514   */
    uint32 INTC2GPROT_515;                                /* INTC2GPROT_515   */
    uint32 INTC2GPROT_516;                                /* INTC2GPROT_516   */
    uint32 INTC2GPROT_517;                                /* INTC2GPROT_517   */
    uint32 INTC2GPROT_518;                                /* INTC2GPROT_518   */
    uint32 INTC2GPROT_519;                                /* INTC2GPROT_519   */
    uint32 INTC2GPROT_520;                                /* INTC2GPROT_520   */
    uint32 INTC2GPROT_521;                                /* INTC2GPROT_521   */
    uint32 INTC2GPROT_522;                                /* INTC2GPROT_522   */
    uint32 INTC2GPROT_523;                                /* INTC2GPROT_523   */
    uint32 INTC2GPROT_524;                                /* INTC2GPROT_524   */
    uint32 INTC2GPROT_525;                                /* INTC2GPROT_525   */
    uint32 INTC2GPROT_526;                                /* INTC2GPROT_526   */
    uint32 INTC2GPROT_527;                                /* INTC2GPROT_527   */
    uint32 INTC2GPROT_528;                                /* INTC2GPROT_528   */
    uint32 INTC2GPROT_529;                                /* INTC2GPROT_529   */
    uint32 INTC2GPROT_530;                                /* INTC2GPROT_530   */
    uint32 INTC2GPROT_531;                                /* INTC2GPROT_531   */
    uint32 INTC2GPROT_532;                                /* INTC2GPROT_532   */
    uint32 INTC2GPROT_533;                                /* INTC2GPROT_533   */
    uint32 INTC2GPROT_534;                                /* INTC2GPROT_534   */
    uint32 INTC2GPROT_535;                                /* INTC2GPROT_535   */
    uint32 INTC2GPROT_536;                                /* INTC2GPROT_536   */
    uint32 INTC2GPROT_537;                                /* INTC2GPROT_537   */
    uint32 INTC2GPROT_538;                                /* INTC2GPROT_538   */
    uint32 INTC2GPROT_539;                                /* INTC2GPROT_539   */
    uint32 INTC2GPROT_540;                                /* INTC2GPROT_540   */
    uint32 INTC2GPROT_541;                                /* INTC2GPROT_541   */
    uint32 INTC2GPROT_542;                                /* INTC2GPROT_542   */
    uint32 INTC2GPROT_543;                                /* INTC2GPROT_543   */
    uint32 INTC2GPROT_544;                                /* INTC2GPROT_544   */
    uint32 INTC2GPROT_545;                                /* INTC2GPROT_545   */
    uint32 INTC2GPROT_546;                                /* INTC2GPROT_546   */
    uint32 INTC2GPROT_547;                                /* INTC2GPROT_547   */
    uint32 INTC2GPROT_548;                                /* INTC2GPROT_548   */
    uint32 INTC2GPROT_549;                                /* INTC2GPROT_549   */
    uint32 INTC2GPROT_550;                                /* INTC2GPROT_550   */
    uint32 INTC2GPROT_551;                                /* INTC2GPROT_551   */
    uint32 INTC2GPROT_552;                                /* INTC2GPROT_552   */
    uint32 INTC2GPROT_553;                                /* INTC2GPROT_553   */
    uint32 INTC2GPROT_554;                                /* INTC2GPROT_554   */
    uint32 INTC2GPROT_555;                                /* INTC2GPROT_555   */
    uint32 INTC2GPROT_556;                                /* INTC2GPROT_556   */
    uint32 INTC2GPROT_557;                                /* INTC2GPROT_557   */
    uint32 INTC2GPROT_558;                                /* INTC2GPROT_558   */
    uint32 INTC2GPROT_559;                                /* INTC2GPROT_559   */
    uint32 INTC2GPROT_560;                                /* INTC2GPROT_560   */
    uint32 INTC2GPROT_561;                                /* INTC2GPROT_561   */
    uint32 INTC2GPROT_562;                                /* INTC2GPROT_562   */
    uint32 INTC2GPROT_563;                                /* INTC2GPROT_563   */
    uint32 INTC2GPROT_564;                                /* INTC2GPROT_564   */
    uint32 INTC2GPROT_565;                                /* INTC2GPROT_565   */
    uint32 INTC2GPROT_566;                                /* INTC2GPROT_566   */
    uint32 INTC2GPROT_567;                                /* INTC2GPROT_567   */
    uint32 INTC2GPROT_568;                                /* INTC2GPROT_568   */
    uint32 INTC2GPROT_569;                                /* INTC2GPROT_569   */
    uint32 INTC2GPROT_570;                                /* INTC2GPROT_570   */
    uint32 INTC2GPROT_571;                                /* INTC2GPROT_571   */
    uint32 INTC2GPROT_572;                                /* INTC2GPROT_572   */
    uint32 INTC2GPROT_573;                                /* INTC2GPROT_573   */
    uint32 INTC2GPROT_574;                                /* INTC2GPROT_574   */
    uint32 INTC2GPROT_575;                                /* INTC2GPROT_575   */
    uint32 INTC2GPROT_576;                                /* INTC2GPROT_576   */
    uint32 INTC2GPROT_577;                                /* INTC2GPROT_577   */
    uint32 INTC2GPROT_578;                                /* INTC2GPROT_578   */
    uint32 INTC2GPROT_579;                                /* INTC2GPROT_579   */
    uint32 INTC2GPROT_580;                                /* INTC2GPROT_580   */
    uint32 INTC2GPROT_581;                                /* INTC2GPROT_581   */
    uint32 INTC2GPROT_582;                                /* INTC2GPROT_582   */
    uint32 INTC2GPROT_583;                                /* INTC2GPROT_583   */
    uint32 INTC2GPROT_584;                                /* INTC2GPROT_584   */
    uint32 INTC2GPROT_585;                                /* INTC2GPROT_585   */
    uint32 INTC2GPROT_586;                                /* INTC2GPROT_586   */
    uint32 INTC2GPROT_587;                                /* INTC2GPROT_587   */
    uint32 INTC2GPROT_588;                                /* INTC2GPROT_588   */
    uint32 INTC2GPROT_589;                                /* INTC2GPROT_589   */
    uint32 INTC2GPROT_590;                                /* INTC2GPROT_590   */
    uint32 INTC2GPROT_591;                                /* INTC2GPROT_591   */
    uint32 INTC2GPROT_592;                                /* INTC2GPROT_592   */
    uint32 INTC2GPROT_593;                                /* INTC2GPROT_593   */
    uint32 INTC2GPROT_594;                                /* INTC2GPROT_594   */
    uint32 INTC2GPROT_595;                                /* INTC2GPROT_595   */
    uint32 INTC2GPROT_596;                                /* INTC2GPROT_596   */
    uint32 INTC2GPROT_597;                                /* INTC2GPROT_597   */
    uint32 INTC2GPROT_598;                                /* INTC2GPROT_598   */
    uint32 INTC2GPROT_599;                                /* INTC2GPROT_599   */
    uint32 INTC2GPROT_600;                                /* INTC2GPROT_600   */
    uint32 INTC2GPROT_601;                                /* INTC2GPROT_601   */
    uint32 INTC2GPROT_602;                                /* INTC2GPROT_602   */
    uint32 INTC2GPROT_603;                                /* INTC2GPROT_603   */
    uint32 INTC2GPROT_604;                                /* INTC2GPROT_604   */
    uint32 INTC2GPROT_605;                                /* INTC2GPROT_605   */
    uint32 INTC2GPROT_606;                                /* INTC2GPROT_606   */
    uint32 INTC2GPROT_607;                                /* INTC2GPROT_607   */
    uint32 INTC2GPROT_608;                                /* INTC2GPROT_608   */
    uint32 INTC2GPROT_609;                                /* INTC2GPROT_609   */
    uint32 INTC2GPROT_610;                                /* INTC2GPROT_610   */
    uint32 INTC2GPROT_611;                                /* INTC2GPROT_611   */
    uint32 INTC2GPROT_612;                                /* INTC2GPROT_612   */
    uint32 INTC2GPROT_613;                                /* INTC2GPROT_613   */
    uint32 INTC2GPROT_614;                                /* INTC2GPROT_614   */
    uint32 INTC2GPROT_615;                                /* INTC2GPROT_615   */
    uint32 INTC2GPROT_616;                                /* INTC2GPROT_616   */
    uint32 INTC2GPROT_617;                                /* INTC2GPROT_617   */
    uint32 INTC2GPROT_618;                                /* INTC2GPROT_618   */
    uint32 INTC2GPROT_619;                                /* INTC2GPROT_619   */
    uint32 INTC2GPROT_620;                                /* INTC2GPROT_620   */
    uint32 INTC2GPROT_621;                                /* INTC2GPROT_621   */
    uint32 INTC2GPROT_622;                                /* INTC2GPROT_622   */
    uint32 INTC2GPROT_623;                                /* INTC2GPROT_623   */
    uint32 INTC2GPROT_624;                                /* INTC2GPROT_624   */
    uint32 INTC2GPROT_625;                                /* INTC2GPROT_625   */
    uint32 INTC2GPROT_626;                                /* INTC2GPROT_626   */
    uint32 INTC2GPROT_627;                                /* INTC2GPROT_627   */
    uint32 INTC2GPROT_628;                                /* INTC2GPROT_628   */
    uint32 INTC2GPROT_629;                                /* INTC2GPROT_629   */
    uint32 INTC2GPROT_630;                                /* INTC2GPROT_630   */
    uint32 INTC2GPROT_631;                                /* INTC2GPROT_631   */
    uint32 INTC2GPROT_632;                                /* INTC2GPROT_632   */
    uint32 INTC2GPROT_633;                                /* INTC2GPROT_633   */
    uint32 INTC2GPROT_634;                                /* INTC2GPROT_634   */
    uint32 INTC2GPROT_635;                                /* INTC2GPROT_635   */
    uint32 INTC2GPROT_636;                                /* INTC2GPROT_636   */
    uint32 INTC2GPROT_637;                                /* INTC2GPROT_637   */
    uint32 INTC2GPROT_638;                                /* INTC2GPROT_638   */
    uint32 INTC2GPROT_639;                                /* INTC2GPROT_639   */
    uint32 INTC2GPROT_640;                                /* INTC2GPROT_640   */
    uint32 INTC2GPROT_641;                                /* INTC2GPROT_641   */
    uint32 INTC2GPROT_642;                                /* INTC2GPROT_642   */
    uint32 INTC2GPROT_643;                                /* INTC2GPROT_643   */
    uint32 INTC2GPROT_644;                                /* INTC2GPROT_644   */
    uint32 INTC2GPROT_645;                                /* INTC2GPROT_645   */
    uint32 INTC2GPROT_646;                                /* INTC2GPROT_646   */
    uint32 INTC2GPROT_647;                                /* INTC2GPROT_647   */
    uint32 INTC2GPROT_648;                                /* INTC2GPROT_648   */
    uint32 INTC2GPROT_649;                                /* INTC2GPROT_649   */
    uint32 INTC2GPROT_650;                                /* INTC2GPROT_650   */
    uint32 INTC2GPROT_651;                                /* INTC2GPROT_651   */
    uint32 INTC2GPROT_652;                                /* INTC2GPROT_652   */
    uint32 INTC2GPROT_653;                                /* INTC2GPROT_653   */
    uint32 INTC2GPROT_654;                                /* INTC2GPROT_654   */
    uint32 INTC2GPROT_655;                                /* INTC2GPROT_655   */
    uint32 INTC2GPROT_656;                                /* INTC2GPROT_656   */
    uint32 INTC2GPROT_657;                                /* INTC2GPROT_657   */
    uint32 INTC2GPROT_658;                                /* INTC2GPROT_658   */
    uint32 INTC2GPROT_659;                                /* INTC2GPROT_659   */
    uint32 INTC2GPROT_660;                                /* INTC2GPROT_660   */
    uint32 INTC2GPROT_661;                                /* INTC2GPROT_661   */
    uint32 INTC2GPROT_662;                                /* INTC2GPROT_662   */
    uint32 INTC2GPROT_663;                                /* INTC2GPROT_663   */
    uint32 INTC2GPROT_664;                                /* INTC2GPROT_664   */
    uint32 INTC2GPROT_665;                                /* INTC2GPROT_665   */
    uint32 INTC2GPROT_666;                                /* INTC2GPROT_666   */
    uint32 INTC2GPROT_667;                                /* INTC2GPROT_667   */
    uint32 INTC2GPROT_668;                                /* INTC2GPROT_668   */
    uint32 INTC2GPROT_669;                                /* INTC2GPROT_669   */
    uint32 INTC2GPROT_670;                                /* INTC2GPROT_670   */
    uint32 INTC2GPROT_671;                                /* INTC2GPROT_671   */
    uint32 INTC2GPROT_672;                                /* INTC2GPROT_672   */
    uint32 INTC2GPROT_673;                                /* INTC2GPROT_673   */
    uint32 INTC2GPROT_674;                                /* INTC2GPROT_674   */
    uint32 INTC2GPROT_675;                                /* INTC2GPROT_675   */
    uint32 INTC2GPROT_676;                                /* INTC2GPROT_676   */
    uint32 INTC2GPROT_677;                                /* INTC2GPROT_677   */
    uint32 INTC2GPROT_678;                                /* INTC2GPROT_678   */
    uint32 INTC2GPROT_679;                                /* INTC2GPROT_679   */
    uint32 INTC2GPROT_680;                                /* INTC2GPROT_680   */
    uint32 INTC2GPROT_681;                                /* INTC2GPROT_681   */
    uint32 INTC2GPROT_682;                                /* INTC2GPROT_682   */
    uint32 INTC2GPROT_683;                                /* INTC2GPROT_683   */
    uint32 INTC2GPROT_684;                                /* INTC2GPROT_684   */
    uint32 INTC2GPROT_685;                                /* INTC2GPROT_685   */
    uint32 INTC2GPROT_686;                                /* INTC2GPROT_686   */
    uint32 INTC2GPROT_687;                                /* INTC2GPROT_687   */
    uint32 INTC2GPROT_688;                                /* INTC2GPROT_688   */
    uint32 INTC2GPROT_689;                                /* INTC2GPROT_689   */
    uint32 INTC2GPROT_690;                                /* INTC2GPROT_690   */
    uint32 INTC2GPROT_691;                                /* INTC2GPROT_691   */
    uint32 INTC2GPROT_692;                                /* INTC2GPROT_692   */
    uint32 INTC2GPROT_693;                                /* INTC2GPROT_693   */
    uint32 INTC2GPROT_694;                                /* INTC2GPROT_694   */
    uint32 INTC2GPROT_695;                                /* INTC2GPROT_695   */
    uint32 INTC2GPROT_696;                                /* INTC2GPROT_696   */
    uint32 INTC2GPROT_697;                                /* INTC2GPROT_697   */
    uint32 INTC2GPROT_698;                                /* INTC2GPROT_698   */
    uint32 INTC2GPROT_699;                                /* INTC2GPROT_699   */
    uint32 INTC2GPROT_700;                                /* INTC2GPROT_700   */
    uint32 INTC2GPROT_701;                                /* INTC2GPROT_701   */
    uint32 INTC2GPROT_702;                                /* INTC2GPROT_702   */
    uint32 INTC2GPROT_703;                                /* INTC2GPROT_703   */
    uint32 INTC2GPROT_704;                                /* INTC2GPROT_704   */
    uint32 INTC2GPROT_705;                                /* INTC2GPROT_705   */
    uint32 INTC2GPROT_706;                                /* INTC2GPROT_706   */
    uint32 INTC2GPROT_707;                                /* INTC2GPROT_707   */
    uint32 INTC2GPROT_708;                                /* INTC2GPROT_708   */
    uint32 INTC2GPROT_709;                                /* INTC2GPROT_709   */
    uint32 INTC2GPROT_710;                                /* INTC2GPROT_710   */
    uint32 INTC2GPROT_711;                                /* INTC2GPROT_711   */
    uint32 INTC2GPROT_712;                                /* INTC2GPROT_712   */
    uint32 INTC2GPROT_713;                                /* INTC2GPROT_713   */
    uint32 INTC2GPROT_714;                                /* INTC2GPROT_714   */
    uint32 INTC2GPROT_715;                                /* INTC2GPROT_715   */
    uint32 INTC2GPROT_716;                                /* INTC2GPROT_716   */
    uint32 INTC2GPROT_717;                                /* INTC2GPROT_717   */
    uint32 INTC2GPROT_718;                                /* INTC2GPROT_718   */
    uint32 INTC2GPROT_719;                                /* INTC2GPROT_719   */
    uint32 INTC2GPROT_720;                                /* INTC2GPROT_720   */
    uint32 INTC2GPROT_721;                                /* INTC2GPROT_721   */
    uint32 INTC2GPROT_722;                                /* INTC2GPROT_722   */
    uint32 INTC2GPROT_723;                                /* INTC2GPROT_723   */
    uint32 INTC2GPROT_724;                                /* INTC2GPROT_724   */
    uint32 INTC2GPROT_725;                                /* INTC2GPROT_725   */
    uint32 INTC2GPROT_726;                                /* INTC2GPROT_726   */
    uint32 INTC2GPROT_727;                                /* INTC2GPROT_727   */
    uint32 INTC2GPROT_728;                                /* INTC2GPROT_728   */
    uint32 INTC2GPROT_729;                                /* INTC2GPROT_729   */
    uint32 INTC2GPROT_730;                                /* INTC2GPROT_730   */
    uint32 INTC2GPROT_731;                                /* INTC2GPROT_731   */
    uint32 INTC2GPROT_732;                                /* INTC2GPROT_732   */
    uint32 INTC2GPROT_733;                                /* INTC2GPROT_733   */
    uint32 INTC2GPROT_734;                                /* INTC2GPROT_734   */
    uint32 INTC2GPROT_735;                                /* INTC2GPROT_735   */
    uint32 INTC2GPROT_736;                                /* INTC2GPROT_736   */
    uint32 INTC2GPROT_737;                                /* INTC2GPROT_737   */
    uint32 INTC2GPROT_738;                                /* INTC2GPROT_738   */
    uint32 INTC2GPROT_739;                                /* INTC2GPROT_739   */
    uint32 INTC2GPROT_740;                                /* INTC2GPROT_740   */
    uint32 INTC2GPROT_741;                                /* INTC2GPROT_741   */
    uint32 INTC2GPROT_742;                                /* INTC2GPROT_742   */
    uint32 INTC2GPROT_743;                                /* INTC2GPROT_743   */
    uint32 INTC2GPROT_744;                                /* INTC2GPROT_744   */
    uint32 INTC2GPROT_745;                                /* INTC2GPROT_745   */
    uint32 INTC2GPROT_746;                                /* INTC2GPROT_746   */
    uint32 INTC2GPROT_747;                                /* INTC2GPROT_747   */
    uint32 INTC2GPROT_748;                                /* INTC2GPROT_748   */
    uint32 INTC2GPROT_749;                                /* INTC2GPROT_749   */
    uint32 INTC2GPROT_750;                                /* INTC2GPROT_750   */
    uint32 INTC2GPROT_751;                                /* INTC2GPROT_751   */
    uint32 INTC2GPROT_752;                                /* INTC2GPROT_752   */
    uint32 INTC2GPROT_753;                                /* INTC2GPROT_753   */
    uint32 INTC2GPROT_754;                                /* INTC2GPROT_754   */
    uint32 INTC2GPROT_755;                                /* INTC2GPROT_755   */
    uint32 INTC2GPROT_756;                                /* INTC2GPROT_756   */
    uint32 INTC2GPROT_757;                                /* INTC2GPROT_757   */
    uint32 INTC2GPROT_758;                                /* INTC2GPROT_758   */
    uint32 INTC2GPROT_759;                                /* INTC2GPROT_759   */
    uint32 INTC2GPROT_760;                                /* INTC2GPROT_760   */
    uint32 INTC2GPROT_761;                                /* INTC2GPROT_761   */
    uint32 INTC2GPROT_762;                                /* INTC2GPROT_762   */
    uint32 INTC2GPROT_763;                                /* INTC2GPROT_763   */
    uint32 INTC2GPROT_764;                                /* INTC2GPROT_764   */
    uint32 INTC2GPROT_765;                                /* INTC2GPROT_765   */
    uint32 INTC2GPROT_766;                                /* INTC2GPROT_766   */
    uint32 INTC2GPROT_767;                                /* INTC2GPROT_767   */
} R_GUARD_INTC2;


extern volatile R_GUARD_INTC2 GUARD_INTC2;

#define GUARD_INTC2INTC2GKCPROT GUARD_INTC2.INTC2GKCPROT
#define GUARD_INTC2INTC2GMPID0 GUARD_INTC2.INTC2GMPID0
#define GUARD_INTC2INTC2GMPID1 GUARD_INTC2.INTC2GMPID1
#define GUARD_INTC2INTC2GMPID2 GUARD_INTC2.INTC2GMPID2
#define GUARD_INTC2INTC2GMPID3 GUARD_INTC2.INTC2GMPID3
#define GUARD_INTC2INTC2GMPID4 GUARD_INTC2.INTC2GMPID4
#define GUARD_INTC2INTC2GMPID5 GUARD_INTC2.INTC2GMPID5
#define GUARD_INTC2INTC2GMPID6 GUARD_INTC2.INTC2GMPID6
#define GUARD_INTC2INTC2GMPID7 GUARD_INTC2.INTC2GMPID7
#define GUARD_INTC2INTC2GPROT_GR GUARD_INTC2.INTC2GPROT_GR
#define GUARD_INTC2INTC2GPROT_IMR GUARD_INTC2.INTC2GPROT_IMR




typedef struct
{                                                          /* Module           */
    uint32 DTSGOVFCLR;                                    /* DTSGOVFCLR       */
    uint32 DTSGOVFSTAT;                                   /* DTSGOVFSTAT      */
    uint32 DTSGERRADDR;                                   /* DTSGERRADDR      */
    uint32 DTSGERRTYPE;                                   /* DTSGERRTYPE      */
    uint32 DTSGSPIDERRCLR;                                /* DTSGSPIDERRCLR   */
    uint32 DTSGSPIDERRSTAT;                               /* DTSGSPIDERRSTAT  */
    uint32 DTSGKCPROT;                                    /* DTSGKCPROT       */
    uint8  dummy2421[36];                                  /* Reserved         */
    uint32 DTSGMPID0;                                     /* DTSGMPID0        */
    uint32 DTSGMPID1;                                     /* DTSGMPID1        */
    uint32 DTSGMPID2;                                     /* DTSGMPID2        */
    uint32 DTSGMPID3;                                     /* DTSGMPID3        */
    uint32 DTSGMPID4;                                     /* DTSGMPID4        */
    uint32 DTSGMPID5;                                     /* DTSGMPID5        */
    uint32 DTSGMPID6;                                     /* DTSGMPID6        */
    uint32 DTSGMPID7;                                     /* DTSGMPID7        */
    uint8  dummy2422[144];                                 /* Reserved         */
    uint32 DTSGPROT_GR;                                   /* DTSGPROT_GR      */
    uint8  dummy2423[12];                                  /* Reserved         */
    uint32 DTSGPROT_000;                                  /* DTSGPROT_000     */
    uint32 DTSGPROT_001;                                  /* DTSGPROT_001     */
    uint32 DTSGPROT_002;                                  /* DTSGPROT_002     */
    uint32 DTSGPROT_003;                                  /* DTSGPROT_003     */
    uint32 DTSGPROT_004;                                  /* DTSGPROT_004     */
    uint32 DTSGPROT_005;                                  /* DTSGPROT_005     */
    uint32 DTSGPROT_006;                                  /* DTSGPROT_006     */
    uint32 DTSGPROT_007;                                  /* DTSGPROT_007     */
    uint32 DTSGPROT_008;                                  /* DTSGPROT_008     */
    uint32 DTSGPROT_009;                                  /* DTSGPROT_009     */
    uint32 DTSGPROT_010;                                  /* DTSGPROT_010     */
    uint32 DTSGPROT_011;                                  /* DTSGPROT_011     */
    uint32 DTSGPROT_012;                                  /* DTSGPROT_012     */
    uint32 DTSGPROT_013;                                  /* DTSGPROT_013     */
    uint32 DTSGPROT_014;                                  /* DTSGPROT_014     */
    uint32 DTSGPROT_015;                                  /* DTSGPROT_015     */
    uint32 DTSGPROT_016;                                  /* DTSGPROT_016     */
    uint32 DTSGPROT_017;                                  /* DTSGPROT_017     */
    uint32 DTSGPROT_018;                                  /* DTSGPROT_018     */
    uint32 DTSGPROT_019;                                  /* DTSGPROT_019     */
    uint32 DTSGPROT_020;                                  /* DTSGPROT_020     */
    uint32 DTSGPROT_021;                                  /* DTSGPROT_021     */
    uint32 DTSGPROT_022;                                  /* DTSGPROT_022     */
    uint32 DTSGPROT_023;                                  /* DTSGPROT_023     */
    uint32 DTSGPROT_024;                                  /* DTSGPROT_024     */
    uint32 DTSGPROT_025;                                  /* DTSGPROT_025     */
    uint32 DTSGPROT_026;                                  /* DTSGPROT_026     */
    uint32 DTSGPROT_027;                                  /* DTSGPROT_027     */
    uint32 DTSGPROT_028;                                  /* DTSGPROT_028     */
    uint32 DTSGPROT_029;                                  /* DTSGPROT_029     */
    uint32 DTSGPROT_030;                                  /* DTSGPROT_030     */
    uint32 DTSGPROT_031;                                  /* DTSGPROT_031     */
    uint32 DTSGPROT_032;                                  /* DTSGPROT_032     */
    uint32 DTSGPROT_033;                                  /* DTSGPROT_033     */
    uint32 DTSGPROT_034;                                  /* DTSGPROT_034     */
    uint32 DTSGPROT_035;                                  /* DTSGPROT_035     */
    uint32 DTSGPROT_036;                                  /* DTSGPROT_036     */
    uint32 DTSGPROT_037;                                  /* DTSGPROT_037     */
    uint32 DTSGPROT_038;                                  /* DTSGPROT_038     */
    uint32 DTSGPROT_039;                                  /* DTSGPROT_039     */
    uint32 DTSGPROT_040;                                  /* DTSGPROT_040     */
    uint32 DTSGPROT_041;                                  /* DTSGPROT_041     */
    uint32 DTSGPROT_042;                                  /* DTSGPROT_042     */
    uint32 DTSGPROT_043;                                  /* DTSGPROT_043     */
    uint32 DTSGPROT_044;                                  /* DTSGPROT_044     */
    uint32 DTSGPROT_045;                                  /* DTSGPROT_045     */
    uint32 DTSGPROT_046;                                  /* DTSGPROT_046     */
    uint32 DTSGPROT_047;                                  /* DTSGPROT_047     */
    uint32 DTSGPROT_048;                                  /* DTSGPROT_048     */
    uint32 DTSGPROT_049;                                  /* DTSGPROT_049     */
    uint32 DTSGPROT_050;                                  /* DTSGPROT_050     */
    uint32 DTSGPROT_051;                                  /* DTSGPROT_051     */
    uint32 DTSGPROT_052;                                  /* DTSGPROT_052     */
    uint32 DTSGPROT_053;                                  /* DTSGPROT_053     */
    uint32 DTSGPROT_054;                                  /* DTSGPROT_054     */
    uint32 DTSGPROT_055;                                  /* DTSGPROT_055     */
    uint32 DTSGPROT_056;                                  /* DTSGPROT_056     */
    uint32 DTSGPROT_057;                                  /* DTSGPROT_057     */
    uint32 DTSGPROT_058;                                  /* DTSGPROT_058     */
    uint32 DTSGPROT_059;                                  /* DTSGPROT_059     */
    uint32 DTSGPROT_060;                                  /* DTSGPROT_060     */
    uint32 DTSGPROT_061;                                  /* DTSGPROT_061     */
    uint32 DTSGPROT_062;                                  /* DTSGPROT_062     */
    uint32 DTSGPROT_063;                                  /* DTSGPROT_063     */
    uint32 DTSGPROT_064;                                  /* DTSGPROT_064     */
    uint32 DTSGPROT_065;                                  /* DTSGPROT_065     */
    uint32 DTSGPROT_066;                                  /* DTSGPROT_066     */
    uint32 DTSGPROT_067;                                  /* DTSGPROT_067     */
    uint32 DTSGPROT_068;                                  /* DTSGPROT_068     */
    uint32 DTSGPROT_069;                                  /* DTSGPROT_069     */
    uint32 DTSGPROT_070;                                  /* DTSGPROT_070     */
    uint32 DTSGPROT_071;                                  /* DTSGPROT_071     */
    uint32 DTSGPROT_072;                                  /* DTSGPROT_072     */
    uint32 DTSGPROT_073;                                  /* DTSGPROT_073     */
    uint32 DTSGPROT_074;                                  /* DTSGPROT_074     */
    uint32 DTSGPROT_075;                                  /* DTSGPROT_075     */
    uint32 DTSGPROT_076;                                  /* DTSGPROT_076     */
    uint32 DTSGPROT_077;                                  /* DTSGPROT_077     */
    uint32 DTSGPROT_078;                                  /* DTSGPROT_078     */
    uint32 DTSGPROT_079;                                  /* DTSGPROT_079     */
    uint32 DTSGPROT_080;                                  /* DTSGPROT_080     */
    uint32 DTSGPROT_081;                                  /* DTSGPROT_081     */
    uint32 DTSGPROT_082;                                  /* DTSGPROT_082     */
    uint32 DTSGPROT_083;                                  /* DTSGPROT_083     */
    uint32 DTSGPROT_084;                                  /* DTSGPROT_084     */
    uint32 DTSGPROT_085;                                  /* DTSGPROT_085     */
    uint32 DTSGPROT_086;                                  /* DTSGPROT_086     */
    uint32 DTSGPROT_087;                                  /* DTSGPROT_087     */
    uint32 DTSGPROT_088;                                  /* DTSGPROT_088     */
    uint32 DTSGPROT_089;                                  /* DTSGPROT_089     */
    uint32 DTSGPROT_090;                                  /* DTSGPROT_090     */
    uint32 DTSGPROT_091;                                  /* DTSGPROT_091     */
    uint32 DTSGPROT_092;                                  /* DTSGPROT_092     */
    uint32 DTSGPROT_093;                                  /* DTSGPROT_093     */
    uint32 DTSGPROT_094;                                  /* DTSGPROT_094     */
    uint32 DTSGPROT_095;                                  /* DTSGPROT_095     */
    uint32 DTSGPROT_096;                                  /* DTSGPROT_096     */
    uint32 DTSGPROT_097;                                  /* DTSGPROT_097     */
    uint32 DTSGPROT_098;                                  /* DTSGPROT_098     */
    uint32 DTSGPROT_099;                                  /* DTSGPROT_099     */
    uint32 DTSGPROT_100;                                  /* DTSGPROT_100     */
    uint32 DTSGPROT_101;                                  /* DTSGPROT_101     */
    uint32 DTSGPROT_102;                                  /* DTSGPROT_102     */
    uint32 DTSGPROT_103;                                  /* DTSGPROT_103     */
    uint32 DTSGPROT_104;                                  /* DTSGPROT_104     */
    uint32 DTSGPROT_105;                                  /* DTSGPROT_105     */
    uint32 DTSGPROT_106;                                  /* DTSGPROT_106     */
    uint32 DTSGPROT_107;                                  /* DTSGPROT_107     */
    uint32 DTSGPROT_108;                                  /* DTSGPROT_108     */
    uint32 DTSGPROT_109;                                  /* DTSGPROT_109     */
    uint32 DTSGPROT_110;                                  /* DTSGPROT_110     */
    uint32 DTSGPROT_111;                                  /* DTSGPROT_111     */
    uint32 DTSGPROT_112;                                  /* DTSGPROT_112     */
    uint32 DTSGPROT_113;                                  /* DTSGPROT_113     */
    uint32 DTSGPROT_114;                                  /* DTSGPROT_114     */
    uint32 DTSGPROT_115;                                  /* DTSGPROT_115     */
    uint32 DTSGPROT_116;                                  /* DTSGPROT_116     */
    uint32 DTSGPROT_117;                                  /* DTSGPROT_117     */
    uint32 DTSGPROT_118;                                  /* DTSGPROT_118     */
    uint32 DTSGPROT_119;                                  /* DTSGPROT_119     */
    uint32 DTSGPROT_120;                                  /* DTSGPROT_120     */
    uint32 DTSGPROT_121;                                  /* DTSGPROT_121     */
    uint32 DTSGPROT_122;                                  /* DTSGPROT_122     */
    uint32 DTSGPROT_123;                                  /* DTSGPROT_123     */
    uint32 DTSGPROT_124;                                  /* DTSGPROT_124     */
    uint32 DTSGPROT_125;                                  /* DTSGPROT_125     */
    uint32 DTSGPROT_126;                                  /* DTSGPROT_126     */
    uint32 DTSGPROT_127;                                  /* DTSGPROT_127     */
} R_GUARD_DTS;

typedef struct
{                                                          /* Module           */
    uint32 BRGOVFCLR;                                     /* BRGOVFCLR        */
    uint32 BRGOVFSTAT;                                    /* BRGOVFSTAT       */
    uint32 BRGERRADDR;                                    /* BRGERRADDR       */
    uint32 BRGERRTYPE;                                    /* BRGERRTYPE       */
    uint32 BRGSPIDERRCLR;                                 /* BRGSPIDERRCLR    */
    uint32 BRGSPIDERRSTAT;                                /* BRGSPIDERRSTAT   */
    uint32 BRGKCPROT;                                     /* BRGKCPROT        */
    uint8  dummy2431[100];                                 /* Reserved         */
    uint32 BRGPROT0_0;                                    /* BRGPROT0_0       */
    uint32 BRGPROT1_0;                                    /* BRGPROT1_0       */
    uint32 BRGPROT0_1;                                    /* BRGPROT0_1       */
    uint32 BRGPROT1_1;                                    /* BRGPROT1_1       */
    uint32 BRGPROT0_2;                                    /* BRGPROT0_2       */
    uint32 BRGPROT1_2;                                    /* BRGPROT1_2       */
    uint32 BRGPROT0_3;                                    /* BRGPROT0_3       */
    uint32 BRGPROT1_3;                                    /* BRGPROT1_3       */
    uint32 BRGPROT0_4;                                    /* BRGPROT0_4       */
    uint32 BRGPROT1_4;                                    /* BRGPROT1_4       */
    uint32 BRGPROT0_5;                                    /* BRGPROT0_5       */
    uint32 BRGPROT1_5;                                    /* BRGPROT1_5       */
    uint32 BRGPROT0_6;                                    /* BRGPROT0_6       */
    uint32 BRGPROT1_6;                                    /* BRGPROT1_6       */
    uint32 BRGPROT0_7;                                    /* BRGPROT0_7       */
    uint32 BRGPROT1_7;                                    /* BRGPROT1_7       */
    uint32 BRGPROT0_8;                                    /* BRGPROT0_8       */
    uint32 BRGPROT1_8;                                    /* BRGPROT1_8       */
    uint32 BRGPROT0_9;                                    /* BRGPROT0_9       */
    uint32 BRGPROT1_9;                                    /* BRGPROT1_9       */
    uint32 BRGPROT0_10;                                   /* BRGPROT0_10      */
    uint32 BRGPROT1_10;                                   /* BRGPROT1_10      */
    uint32 BRGPROT0_11;                                   /* BRGPROT0_11      */
    uint32 BRGPROT1_11;                                   /* BRGPROT1_11      */
    uint32 BRGPROT0_12;                                   /* BRGPROT0_12      */
    uint32 BRGPROT1_12;                                   /* BRGPROT1_12      */
    uint32 BRGPROT0_13;                                   /* BRGPROT0_13      */
    uint32 BRGPROT1_13;                                   /* BRGPROT1_13      */
    uint32 BRGPROT0_14;                                   /* BRGPROT0_14      */
    uint32 BRGPROT1_14;                                   /* BRGPROT1_14      */
    uint32 BRGPROT0_15;                                   /* BRGPROT0_15      */
    uint32 BRGPROT1_15;                                   /* BRGPROT1_15      */
    uint32 BRGPROT0_16;                                   /* BRGPROT0_16      */
    uint32 BRGPROT1_16;                                   /* BRGPROT1_16      */
} R_GUARD_BARR;
typedef struct
{                                                          /* Module           */
    uint32 IPIGOVFCLR;                                    /* IPIGOVFCLR       */
    uint32 IPIGOVFSTAT;                                   /* IPIGOVFSTAT      */
    uint32 IPIGERRADDR;                                   /* IPIGERRADDR      */
    uint32 IPIGERRTYPE;                                   /* IPIGERRTYPE      */
    uint32 IPIGSPIDERRCLR;                                /* IPIGSPIDERRCLR   */
    uint32 IPIGSPIDERRSTAT;                               /* IPIGSPIDERRSTAT  */
    uint32 IPIGKCPROT;                                    /* IPIGKCPROT       */
    uint8  dummy2432[100];                                 /* Reserved         */
    uint32 IPIGPROT0_R0;                                  /* IPIGPROT0_R0     */
    uint32 IPIGPROT1_R0;                                  /* IPIGPROT1_R0     */
    uint32 IPIGPROT0_T0;                                  /* IPIGPROT0_T0     */
    uint32 IPIGPROT1_T0;                                  /* IPIGPROT1_T0     */
    uint32 IPIGPROT0_R1;                                  /* IPIGPROT0_R1     */
    uint32 IPIGPROT1_R1;                                  /* IPIGPROT1_R1     */
    uint32 IPIGPROT0_T1;                                  /* IPIGPROT0_T1     */
    uint32 IPIGPROT1_T1;                                  /* IPIGPROT1_T1     */
    uint32 IPIGPROT0_R2;                                  /* IPIGPROT0_R2     */
    uint32 IPIGPROT1_R2;                                  /* IPIGPROT1_R2     */
    uint32 IPIGPROT0_T2;                                  /* IPIGPROT0_T2     */
    uint32 IPIGPROT1_T2;                                  /* IPIGPROT1_T2     */
    uint32 IPIGPROT0_R3;                                  /* IPIGPROT0_R3     */
    uint32 IPIGPROT1_R3;                                  /* IPIGPROT1_R3     */
    uint32 IPIGPROT0_T3;                                  /* IPIGPROT0_T3     */
    uint32 IPIGPROT1_T3;                                  /* IPIGPROT1_T3     */
    uint32 IPIGPROT0_4;                                   /* IPIGPROT0_4      */
    uint32 IPIGPROT1_4;                                   /* IPIGPROT1_4      */
} R_GUARD_IPIR;

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  typedef struct
  {                                                          /* Module           */
      uint32 TPTGOVFCLR;                                    /* TPTGOVFCLR       */
      uint32 TPTGOVFSTAT;                                   /* TPTGOVFSTAT      */
      uint32 TPTGERRADDR;                                   /* TPTGERRADDR      */
      uint32 TPTGERRTYPE;                                   /* TPTGERRTYPE      */
      uint32 TPTGSPIDERRCLR;                                /* TPTGSPIDERRCLR   */
      uint32 TPTGSPIDERRSTAT;                               /* TPTGSPIDERRSTAT  */
      uint32 TPTGKCPROT;                                    /* TPTGKCPROT       */
      uint8  dummy2433[100];                                 /* Reserved         */
      uint32 TPTGPROT0_0;                                   /* TPTGPROT0_0      */
      uint32 TPTGPROT1_0;                                   /* TPTGPROT1_0      */
      uint32 TPTGPROT0_1;                                   /* TPTGPROT0_1      */
      uint32 TPTGPROT1_1;                                   /* TPTGPROT1_1      */
      uint32 TPTGPROT0_2;                                   /* TPTGPROT0_2      */
      uint32 TPTGPROT1_2;                                   /* TPTGPROT1_2      */
      uint32 TPTGPROT0_3;                                   /* TPTGPROT0_3      */
      uint32 TPTGPROT1_3;                                   /* TPTGPROT1_3      */
      uint8  dummy2434[32];                                  /* Reserved         */
      uint32 TPTGPROT0_8;                                   /* TPTGPROT0_8      */
      uint32 TPTGPROT1_8;                                   /* TPTGPROT1_8      */
      uint32 TPTGPROT0_9;                                   /* TPTGPROT0_9      */
      uint32 TPTGPROT1_9;                                   /* TPTGPROT1_9      */
  } R_GUARD_TPTM;

  #define GUARD_TPTMTPTGOVFCLR GUARD_TPTM.TPTGOVFCLR
  #define GUARD_TPTMTPTGOVFSTAT GUARD_TPTM.TPTGOVFSTAT
  #define GUARD_TPTMTPTGERRADDR GUARD_TPTM.TPTGERRADDR
  #define GUARD_TPTMTPTGERRTYPE GUARD_TPTM.TPTGERRTYPE
  #define GUARD_TPTMTPTGSPIDERRCLR GUARD_TPTM.TPTGSPIDERRCLR
  #define GUARD_TPTMTPTGSPIDERRSTAT GUARD_TPTM.TPTGSPIDERRSTAT
  #define GUARD_TPTMTPTGKCPROT GUARD_TPTM.TPTGKCPROT
  #define GUARD_TPTMTPTGPROT0_0 GUARD_TPTM.TPTGPROT0_0
  #define GUARD_TPTMTPTGPROT1_0 GUARD_TPTM.TPTGPROT1_0
  #define GUARD_TPTMTPTGPROT0_1 GUARD_TPTM.TPTGPROT0_1
  #define GUARD_TPTMTPTGPROT1_1 GUARD_TPTM.TPTGPROT1_1
  #define GUARD_TPTMTPTGPROT0_2 GUARD_TPTM.TPTGPROT0_2
  #define GUARD_TPTMTPTGPROT1_2 GUARD_TPTM.TPTGPROT1_2
  #define GUARD_TPTMTPTGPROT0_3 GUARD_TPTM.TPTGPROT0_3
  #define GUARD_TPTMTPTGPROT1_3 GUARD_TPTM.TPTGPROT1_3
  #define GUARD_TPTMTPTGPROT0_8 GUARD_TPTM.TPTGPROT0_8
  #define GUARD_TPTMTPTGPROT1_8 GUARD_TPTM.TPTGPROT1_8
  #define GUARD_TPTMTPTGPROT0_9 GUARD_TPTM.TPTGPROT0_9
  #define GUARD_TPTMTPTGPROT1_9 GUARD_TPTM.TPTGPROT1_9

  typedef struct
  {                                                          /* Module           */
      uint32 DMAGOVFCLR;                                    /* DMAGOVFCLR       */
      uint32 DMAGOVFSTAT;                                   /* DMAGOVFSTAT      */
      uint32 DMAGERRADDR;                                   /* DMAGERRADDR      */
      uint32 DMAGERRTYPE;                                   /* DMAGERRTYPE      */
      uint32 DMAGSPIDERRCLR;                                /* DMAGSPIDERRCLR   */
      uint32 DMAGSPIDERRSTAT;                               /* DMAGSPIDERRSTAT  */
      uint32 DMAGKCPROT;                                    /* DMAGKCPROT       */
      uint8  dummy2424[36];                                  /* Reserved         */
      uint32 DMAGMPID0;                                     /* DMAGMPID0        */
      uint32 DMAGMPID1;                                     /* DMAGMPID1        */
      uint32 DMAGMPID2;                                     /* DMAGMPID2        */
      uint32 DMAGMPID3;                                     /* DMAGMPID3        */
      uint32 DMAGMPID4;                                     /* DMAGMPID4        */
      uint32 DMAGMPID5;                                     /* DMAGMPID5        */
      uint32 DMAGMPID6;                                     /* DMAGMPID6        */
      uint32 DMAGMPID7;                                     /* DMAGMPID7        */
      uint8  dummy2425[144];                                 /* Reserved         */
      uint32 DMAGPROT_GR;                                   /* DMAGPROT_GR      */
      uint32 DMAGPROT_DP;                                   /* DMAGPROT_DP      */
      uint8  dummy2426[8];                                   /* Reserved         */
      uint32 DMAGPROT_000;                                  /* DMAGPROT_000     */
      uint32 DMAGPROT_001;                                  /* DMAGPROT_001     */
      uint32 DMAGPROT_002;                                  /* DMAGPROT_002     */
      uint32 DMAGPROT_003;                                  /* DMAGPROT_003     */
      uint32 DMAGPROT_004;                                  /* DMAGPROT_004     */
      uint32 DMAGPROT_005;                                  /* DMAGPROT_005     */
      uint32 DMAGPROT_006;                                  /* DMAGPROT_006     */
      uint32 DMAGPROT_007;                                  /* DMAGPROT_007     */
      uint32 DMAGPROT_008;                                  /* DMAGPROT_008     */
      uint32 DMAGPROT_009;                                  /* DMAGPROT_009     */
      uint32 DMAGPROT_010;                                  /* DMAGPROT_010     */
      uint32 DMAGPROT_011;                                  /* DMAGPROT_011     */
      uint32 DMAGPROT_012;                                  /* DMAGPROT_012     */
      uint32 DMAGPROT_013;                                  /* DMAGPROT_013     */
      uint32 DMAGPROT_014;                                  /* DMAGPROT_014     */
      uint32 DMAGPROT_015;                                  /* DMAGPROT_015     */
      uint8  dummy2427[704];                                 /* Reserved         */
  } R_GUARD_DMAC0;
  typedef struct
  {                                                          /* Module           */
      uint32 DMAGOVFCLR;                                    /* DMAGOVFCLR       */
      uint32 DMAGOVFSTAT;                                   /* DMAGOVFSTAT      */
      uint32 DMAGERRADDR;                                   /* DMAGERRADDR      */
      uint32 DMAGERRTYPE;                                   /* DMAGERRTYPE      */
      uint32 DMAGSPIDERRCLR;                                /* DMAGSPIDERRCLR   */
      uint32 DMAGSPIDERRSTAT;                               /* DMAGSPIDERRSTAT  */
      uint32 DMAGKCPROT;                                    /* DMAGKCPROT       */
      uint8  dummy2428[36];                                  /* Reserved         */
      uint32 DMAGMPID0;                                     /* DMAGMPID0        */
      uint32 DMAGMPID1;                                     /* DMAGMPID1        */
      uint32 DMAGMPID2;                                     /* DMAGMPID2        */
      uint32 DMAGMPID3;                                     /* DMAGMPID3        */
      uint32 DMAGMPID4;                                     /* DMAGMPID4        */
      uint32 DMAGMPID5;                                     /* DMAGMPID5        */
      uint32 DMAGMPID6;                                     /* DMAGMPID6        */
      uint32 DMAGMPID7;                                     /* DMAGMPID7        */
      uint8  dummy2429[144];                                 /* Reserved         */
      uint32 DMAGPROT_GR;                                   /* DMAGPROT_GR      */
      uint32 DMAGPROT_DP;                                   /* DMAGPROT_DP      */
      uint8  dummy2430[8];                                   /* Reserved         */
      uint32 DMAGPROT_000;                                  /* DMAGPROT_000     */
      uint32 DMAGPROT_001;                                  /* DMAGPROT_001     */
      uint32 DMAGPROT_002;                                  /* DMAGPROT_002     */
      uint32 DMAGPROT_003;                                  /* DMAGPROT_003     */
      uint32 DMAGPROT_004;                                  /* DMAGPROT_004     */
      uint32 DMAGPROT_005;                                  /* DMAGPROT_005     */
      uint32 DMAGPROT_006;                                  /* DMAGPROT_006     */
      uint32 DMAGPROT_007;                                  /* DMAGPROT_007     */
      uint32 DMAGPROT_008;                                  /* DMAGPROT_008     */
      uint32 DMAGPROT_009;                                  /* DMAGPROT_009     */
      uint32 DMAGPROT_010;                                  /* DMAGPROT_010     */
      uint32 DMAGPROT_011;                                  /* DMAGPROT_011     */
      uint32 DMAGPROT_012;                                  /* DMAGPROT_012     */
      uint32 DMAGPROT_013;                                  /* DMAGPROT_013     */
      uint32 DMAGPROT_014;                                  /* DMAGPROT_014     */
      uint32 DMAGPROT_015;                                  /* DMAGPROT_015     */
  } R_GUARD_DMAC1;

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

  typedef struct
  {                                                          /* Module           */
      uint32 TPTGOVFCLR;                                    /* TPTGOVFCLR       */
      uint32 TPTGOVFSTAT;                                   /* TPTGOVFSTAT      */
      uint32 TPTGERRADDR;                                   /* TPTGERRADDR      */
      uint32 TPTGERRTYPE;                                   /* TPTGERRTYPE      */
      uint32 TPTGSPIDERRCLR;                                /* TPTGSPIDERRCLR   */
      uint32 TPTGSPIDERRSTAT;                               /* TPTGSPIDERRSTAT  */
      uint32 TPTGKCPROT;                                    /* TPTGKCPROT       */
      uint8  dummy4459[100];                                 /* Reserved         */
      uint32 TPTGPROT0_IF0;                                 /* TPTGPROT0_IF0    */
      uint32 TPTGPROT1_IF0;                                 /* TPTGPROT1_IF0    */
      uint32 TPTGPROT0_IF1;                                 /* TPTGPROT0_IF1    */
      uint32 TPTGPROT1_IF1;                                 /* TPTGPROT1_IF1    */
      uint32 TPTGPROT0_IF2;                                 /* TPTGPROT0_IF2    */
      uint32 TPTGPROT1_IF2;                                 /* TPTGPROT1_IF2    */
      uint32 TPTGPROT0_IF3;                                 /* TPTGPROT0_IF3    */
      uint32 TPTGPROT1_IF3;                                 /* TPTGPROT1_IF3    */
      uint8  dummy4460[32];                                  /* Reserved         */
      uint32 TPTGPROT0_U0;                                  /* TPTGPROT0_U0     */
      uint32 TPTGPROT1_U0;                                  /* TPTGPROT1_U0     */
      uint32 TPTGPROT0_U1;                                  /* TPTGPROT0_U1     */
      uint32 TPTGPROT1_U1;                                  /* TPTGPROT1_U1     */
      uint32 TPTGPROT0_U2;                                  /* TPTGPROT0_U2     */
      uint32 TPTGPROT1_U2;                                  /* TPTGPROT1_U2     */
      uint32 TPTGPROT0_U3;                                  /* TPTGPROT0_U3     */
      uint32 TPTGPROT1_U3;                                  /* TPTGPROT1_U3     */
      uint8  dummy4461[32];                                  /* Reserved         */
      uint32 TPTGPROT0_U8;                                  /* TPTGPROT0_U8     */
      uint32 TPTGPROT1_U8;                                  /* TPTGPROT1_U8     */
      uint32 TPTGPROT0_U9;                                  /* TPTGPROT0_U9     */
      uint32 TPTGPROT1_U9;                                  /* TPTGPROT1_U9     */
  } R_GUARD_TPTM;

  #define GUARD_TPTMTPTGOVFCLR GUARD_TPTM.TPTGOVFCLR
  #define GUARD_TPTMTPTGOVFSTAT GUARD_TPTM.TPTGOVFSTAT
  #define GUARD_TPTMTPTGERRADDR GUARD_TPTM.TPTGERRADDR
  #define GUARD_TPTMTPTGERRTYPE GUARD_TPTM.TPTGERRTYPE
  #define GUARD_TPTMTPTGSPIDERRCLR GUARD_TPTM.TPTGSPIDERRCLR
  #define GUARD_TPTMTPTGSPIDERRSTAT GUARD_TPTM.TPTGSPIDERRSTAT
  #define GUARD_TPTMTPTGKCPROT GUARD_TPTM.TPTGKCPROT
  #define GUARD_TPTMTPTGPROT0_IF0 GUARD_TPTM.TPTGPROT0_IF0
  #define GUARD_TPTMTPTGPROT1_IF0 GUARD_TPTM.TPTGPROT1_IF0
  #define GUARD_TPTMTPTGPROT0_IF1 GUARD_TPTM.TPTGPROT0_IF1
  #define GUARD_TPTMTPTGPROT1_IF1 GUARD_TPTM.TPTGPROT1_IF1
  #define GUARD_TPTMTPTGPROT0_IF2 GUARD_TPTM.TPTGPROT0_IF2
  #define GUARD_TPTMTPTGPROT1_IF2 GUARD_TPTM.TPTGPROT1_IF2
  #define GUARD_TPTMTPTGPROT0_IF3 GUARD_TPTM.TPTGPROT0_IF3
  #define GUARD_TPTMTPTGPROT1_IF3 GUARD_TPTM.TPTGPROT1_IF3
  #define GUARD_TPTMTPTGPROT0_U0 GUARD_TPTM.TPTGPROT0_U0
  #define GUARD_TPTMTPTGPROT1_U0 GUARD_TPTM.TPTGPROT1_U0
  #define GUARD_TPTMTPTGPROT0_U1 GUARD_TPTM.TPTGPROT0_U1
  #define GUARD_TPTMTPTGPROT1_U1 GUARD_TPTM.TPTGPROT1_U1
  #define GUARD_TPTMTPTGPROT0_U2 GUARD_TPTM.TPTGPROT0_U2
  #define GUARD_TPTMTPTGPROT1_U2 GUARD_TPTM.TPTGPROT1_U2
  #define GUARD_TPTMTPTGPROT0_U3 GUARD_TPTM.TPTGPROT0_U3
  #define GUARD_TPTMTPTGPROT1_U3 GUARD_TPTM.TPTGPROT1_U3
  #define GUARD_TPTMTPTGPROT0_U8 GUARD_TPTM.TPTGPROT0_U8
  #define GUARD_TPTMTPTGPROT1_U8 GUARD_TPTM.TPTGPROT1_U8
  #define GUARD_TPTMTPTGPROT0_U9 GUARD_TPTM.TPTGPROT0_U9
  #define GUARD_TPTMTPTGPROT1_U9 GUARD_TPTM.TPTGPROT1_U9

  typedef struct
  {                                                          /* Module           */
      uint32 DMAGOVFCLR;                                    /* DMAGOVFCLR       */
      uint32 DMAGOVFSTAT;                                   /* DMAGOVFSTAT      */
      uint32 DMAGERRADDR;                                   /* DMAGERRADDR      */
      uint32 DMAGERRTYPE;                                   /* DMAGERRTYPE      */
      uint32 DMAGSPIDERRCLR;                                /* DMAGSPIDERRCLR   */
      uint32 DMAGSPIDERRSTAT;                               /* DMAGSPIDERRSTAT  */
      uint32 DMAGKCPROT;                                    /* DMAGKCPROT       */
      uint8  dummy4450[36];                                  /* Reserved         */
      uint32 DMAGMPID0;                                     /* DMAGMPID0        */
      uint32 DMAGMPID1;                                     /* DMAGMPID1        */
      uint32 DMAGMPID2;                                     /* DMAGMPID2        */
      uint32 DMAGMPID3;                                     /* DMAGMPID3        */
      uint32 DMAGMPID4;                                     /* DMAGMPID4        */
      uint32 DMAGMPID5;                                     /* DMAGMPID5        */
      uint32 DMAGMPID6;                                     /* DMAGMPID6        */
      uint32 DMAGMPID7;                                     /* DMAGMPID7        */
      uint8  dummy4451[144];                                 /* Reserved         */
      uint32 DMAGPROT_GR;                                   /* DMAGPROT_GR      */
      uint32 DMAGPROT_DP;                                   /* DMAGPROT_DP      */
      uint32 DMAGPROT_CR;                                   /* DMAGPROT_CR      */
      uint8  dummy4452[4];                                   /* Reserved         */
      uint32 DMAGPROT_000;                                  /* DMAGPROT_000     */
      uint32 DMAGPROT_001;                                  /* DMAGPROT_001     */
      uint32 DMAGPROT_002;                                  /* DMAGPROT_002     */
      uint32 DMAGPROT_003;                                  /* DMAGPROT_003     */
      uint32 DMAGPROT_004;                                  /* DMAGPROT_004     */
      uint32 DMAGPROT_005;                                  /* DMAGPROT_005     */
      uint32 DMAGPROT_006;                                  /* DMAGPROT_006     */
      uint32 DMAGPROT_007;                                  /* DMAGPROT_007     */
      uint32 DMAGPROT_008;                                  /* DMAGPROT_008     */
      uint32 DMAGPROT_009;                                  /* DMAGPROT_009     */
      uint32 DMAGPROT_010;                                  /* DMAGPROT_010     */
      uint32 DMAGPROT_011;                                  /* DMAGPROT_011     */
      uint32 DMAGPROT_012;                                  /* DMAGPROT_012     */
      uint32 DMAGPROT_013;                                  /* DMAGPROT_013     */
      uint32 DMAGPROT_014;                                  /* DMAGPROT_014     */
      uint32 DMAGPROT_015;                                  /* DMAGPROT_015     */
      uint8  dummy4453[704];                                 /* Reserved         */
  } R_GUARD_DMAC0;
  typedef struct
  {                                                          /* Module           */
      uint32 DMAGOVFCLR;                                    /* DMAGOVFCLR       */
      uint32 DMAGOVFSTAT;                                   /* DMAGOVFSTAT      */
      uint32 DMAGERRADDR;                                   /* DMAGERRADDR      */
      uint32 DMAGERRTYPE;                                   /* DMAGERRTYPE      */
      uint32 DMAGSPIDERRCLR;                                /* DMAGSPIDERRCLR   */
      uint32 DMAGSPIDERRSTAT;                               /* DMAGSPIDERRSTAT  */
      uint32 DMAGKCPROT;                                    /* DMAGKCPROT       */
      uint8  dummy4454[36];                                  /* Reserved         */
      uint32 DMAGMPID0;                                     /* DMAGMPID0        */
      uint32 DMAGMPID1;                                     /* DMAGMPID1        */
      uint32 DMAGMPID2;                                     /* DMAGMPID2        */
      uint32 DMAGMPID3;                                     /* DMAGMPID3        */
      uint32 DMAGMPID4;                                     /* DMAGMPID4        */
      uint32 DMAGMPID5;                                     /* DMAGMPID5        */
      uint32 DMAGMPID6;                                     /* DMAGMPID6        */
      uint32 DMAGMPID7;                                     /* DMAGMPID7        */
      uint8  dummy4455[144];                                 /* Reserved         */
      uint32 DMAGPROT_GR;                                   /* DMAGPROT_GR      */
      uint32 DMAGPROT_DP;                                   /* DMAGPROT_DP      */
      uint32 DMAGPROT_CR;                                   /* DMAGPROT_CR      */
      uint8  dummy4456[4];                                   /* Reserved         */
      uint32 DMAGPROT_000;                                  /* DMAGPROT_000     */
      uint32 DMAGPROT_001;                                  /* DMAGPROT_001     */
      uint32 DMAGPROT_002;                                  /* DMAGPROT_002     */
      uint32 DMAGPROT_003;                                  /* DMAGPROT_003     */
      uint32 DMAGPROT_004;                                  /* DMAGPROT_004     */
      uint32 DMAGPROT_005;                                  /* DMAGPROT_005     */
      uint32 DMAGPROT_006;                                  /* DMAGPROT_006     */
      uint32 DMAGPROT_007;                                  /* DMAGPROT_007     */
      uint32 DMAGPROT_008;                                  /* DMAGPROT_008     */
      uint32 DMAGPROT_009;                                  /* DMAGPROT_009     */
      uint32 DMAGPROT_010;                                  /* DMAGPROT_010     */
      uint32 DMAGPROT_011;                                  /* DMAGPROT_011     */
      uint32 DMAGPROT_012;                                  /* DMAGPROT_012     */
      uint32 DMAGPROT_013;                                  /* DMAGPROT_013     */
      uint32 DMAGPROT_014;                                  /* DMAGPROT_014     */
      uint32 DMAGPROT_015;                                  /* DMAGPROT_015     */
  } R_GUARD_DMAC1;

  #define GUARD_DMAC0DMAGPROT_CR GUARD_DMAC0.DMAGPROT_CR
  #define GUARD_DMAC1DMAGPROT_CR GUARD_DMAC1.DMAGPROT_CR
#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  extern volatile R_SPIDCTL GUARD_SPIDCTL;
  extern volatile R_GUARD_DTS   GUARD_DTS;
  extern volatile R_GUARD_DMAC0 GUARD_DMAC0;
  extern volatile R_GUARD_DMAC1 GUARD_DMAC1;
  extern volatile R_GUARD_BARR  GUARD_BARR;
  extern volatile R_GUARD_IPIR  GUARD_IPIR;
  extern volatile R_GUARD_TPTM  GUARD_TPTM;
#endif

typedef struct{
  uint32 PROT0;
  uint32 PROT1;
} RBSYS_BARRBRG_t;
extern volatile RBSYS_BARRBRG_t rbsys_barrbrg[16];

#define RBSYS_BARRBRG (rbsys_barrbrg)

extern volatile uint32 rbsys_intc2guards[767];
#define RBSYS_INTC2INTC2GPROT_n (rbsys_intc2guards)

extern volatile uint32 rbsys_dmac0guard[32];
extern volatile uint32 rbsys_dmac1guard[32];
extern volatile uint32 rbsys_dtsguard[128];

#define RBSYS_DMAC0DMAGPROT_n (rbsys_dmac0guard)
#define RBSYS_DMAC1DMAGPROT_n (rbsys_dmac1guard)
#define RBSYS_DTSDTSGPROT_n   (rbsys_dtsguard)


#define GUARD_DTSDTSGOVFCLR GUARD_DTS.DTSGOVFCLR
#define GUARD_DTSDTSGOVFSTAT GUARD_DTS.DTSGOVFSTAT
#define GUARD_DTSDTSGERRADDR GUARD_DTS.DTSGERRADDR
#define GUARD_DTSDTSGERRTYPE GUARD_DTS.DTSGERRTYPE
#define GUARD_DTSDTSGSPIDERRCLR GUARD_DTS.DTSGSPIDERRCLR
#define GUARD_DTSDTSGSPIDERRSTAT GUARD_DTS.DTSGSPIDERRSTAT
#define GUARD_DTSDTSGKCPROT GUARD_DTS.DTSGKCPROT
#define GUARD_DTSDTSGMPID0 GUARD_DTS.DTSGMPID0
#define GUARD_DTSDTSGMPID1 GUARD_DTS.DTSGMPID1
#define GUARD_DTSDTSGMPID2 GUARD_DTS.DTSGMPID2
#define GUARD_DTSDTSGMPID3 GUARD_DTS.DTSGMPID3
#define GUARD_DTSDTSGMPID4 GUARD_DTS.DTSGMPID4
#define GUARD_DTSDTSGMPID5 GUARD_DTS.DTSGMPID5
#define GUARD_DTSDTSGMPID6 GUARD_DTS.DTSGMPID6
#define GUARD_DTSDTSGMPID7 GUARD_DTS.DTSGMPID7
#define GUARD_DTSDTSGPROT_GR GUARD_DTS.DTSGPROT_GR
#define GUARD_DTSDTSGPROT_000 GUARD_DTS.DTSGPROT_000
#define GUARD_DTSDTSGPROT_001 GUARD_DTS.DTSGPROT_001
#define GUARD_DTSDTSGPROT_002 GUARD_DTS.DTSGPROT_002
#define GUARD_DTSDTSGPROT_003 GUARD_DTS.DTSGPROT_003
#define GUARD_DTSDTSGPROT_004 GUARD_DTS.DTSGPROT_004
#define GUARD_DTSDTSGPROT_005 GUARD_DTS.DTSGPROT_005
#define GUARD_DTSDTSGPROT_006 GUARD_DTS.DTSGPROT_006
#define GUARD_DTSDTSGPROT_007 GUARD_DTS.DTSGPROT_007
#define GUARD_DTSDTSGPROT_008 GUARD_DTS.DTSGPROT_008
#define GUARD_DTSDTSGPROT_009 GUARD_DTS.DTSGPROT_009
#define GUARD_DTSDTSGPROT_010 GUARD_DTS.DTSGPROT_010
#define GUARD_DTSDTSGPROT_011 GUARD_DTS.DTSGPROT_011
#define GUARD_DTSDTSGPROT_012 GUARD_DTS.DTSGPROT_012
#define GUARD_DTSDTSGPROT_013 GUARD_DTS.DTSGPROT_013
#define GUARD_DTSDTSGPROT_014 GUARD_DTS.DTSGPROT_014
#define GUARD_DTSDTSGPROT_015 GUARD_DTS.DTSGPROT_015
#define GUARD_DTSDTSGPROT_016 GUARD_DTS.DTSGPROT_016
#define GUARD_DTSDTSGPROT_017 GUARD_DTS.DTSGPROT_017
#define GUARD_DTSDTSGPROT_018 GUARD_DTS.DTSGPROT_018
#define GUARD_DTSDTSGPROT_019 GUARD_DTS.DTSGPROT_019
#define GUARD_DTSDTSGPROT_020 GUARD_DTS.DTSGPROT_020
#define GUARD_DTSDTSGPROT_021 GUARD_DTS.DTSGPROT_021
#define GUARD_DTSDTSGPROT_022 GUARD_DTS.DTSGPROT_022
#define GUARD_DTSDTSGPROT_023 GUARD_DTS.DTSGPROT_023
#define GUARD_DTSDTSGPROT_024 GUARD_DTS.DTSGPROT_024
#define GUARD_DTSDTSGPROT_025 GUARD_DTS.DTSGPROT_025
#define GUARD_DTSDTSGPROT_026 GUARD_DTS.DTSGPROT_026
#define GUARD_DTSDTSGPROT_027 GUARD_DTS.DTSGPROT_027
#define GUARD_DTSDTSGPROT_028 GUARD_DTS.DTSGPROT_028
#define GUARD_DTSDTSGPROT_029 GUARD_DTS.DTSGPROT_029
#define GUARD_DTSDTSGPROT_030 GUARD_DTS.DTSGPROT_030
#define GUARD_DTSDTSGPROT_031 GUARD_DTS.DTSGPROT_031
#define GUARD_DTSDTSGPROT_032 GUARD_DTS.DTSGPROT_032
#define GUARD_DTSDTSGPROT_033 GUARD_DTS.DTSGPROT_033
#define GUARD_DTSDTSGPROT_034 GUARD_DTS.DTSGPROT_034
#define GUARD_DTSDTSGPROT_035 GUARD_DTS.DTSGPROT_035
#define GUARD_DTSDTSGPROT_036 GUARD_DTS.DTSGPROT_036
#define GUARD_DTSDTSGPROT_037 GUARD_DTS.DTSGPROT_037
#define GUARD_DTSDTSGPROT_038 GUARD_DTS.DTSGPROT_038
#define GUARD_DTSDTSGPROT_039 GUARD_DTS.DTSGPROT_039
#define GUARD_DTSDTSGPROT_040 GUARD_DTS.DTSGPROT_040
#define GUARD_DTSDTSGPROT_041 GUARD_DTS.DTSGPROT_041
#define GUARD_DTSDTSGPROT_042 GUARD_DTS.DTSGPROT_042
#define GUARD_DTSDTSGPROT_043 GUARD_DTS.DTSGPROT_043
#define GUARD_DTSDTSGPROT_044 GUARD_DTS.DTSGPROT_044
#define GUARD_DTSDTSGPROT_045 GUARD_DTS.DTSGPROT_045
#define GUARD_DTSDTSGPROT_046 GUARD_DTS.DTSGPROT_046
#define GUARD_DTSDTSGPROT_047 GUARD_DTS.DTSGPROT_047
#define GUARD_DTSDTSGPROT_048 GUARD_DTS.DTSGPROT_048
#define GUARD_DTSDTSGPROT_049 GUARD_DTS.DTSGPROT_049
#define GUARD_DTSDTSGPROT_050 GUARD_DTS.DTSGPROT_050
#define GUARD_DTSDTSGPROT_051 GUARD_DTS.DTSGPROT_051
#define GUARD_DTSDTSGPROT_052 GUARD_DTS.DTSGPROT_052
#define GUARD_DTSDTSGPROT_053 GUARD_DTS.DTSGPROT_053
#define GUARD_DTSDTSGPROT_054 GUARD_DTS.DTSGPROT_054
#define GUARD_DTSDTSGPROT_055 GUARD_DTS.DTSGPROT_055
#define GUARD_DTSDTSGPROT_056 GUARD_DTS.DTSGPROT_056
#define GUARD_DTSDTSGPROT_057 GUARD_DTS.DTSGPROT_057
#define GUARD_DTSDTSGPROT_058 GUARD_DTS.DTSGPROT_058
#define GUARD_DTSDTSGPROT_059 GUARD_DTS.DTSGPROT_059
#define GUARD_DTSDTSGPROT_060 GUARD_DTS.DTSGPROT_060
#define GUARD_DTSDTSGPROT_061 GUARD_DTS.DTSGPROT_061
#define GUARD_DTSDTSGPROT_062 GUARD_DTS.DTSGPROT_062
#define GUARD_DTSDTSGPROT_063 GUARD_DTS.DTSGPROT_063
#define GUARD_DTSDTSGPROT_064 GUARD_DTS.DTSGPROT_064
#define GUARD_DTSDTSGPROT_065 GUARD_DTS.DTSGPROT_065
#define GUARD_DTSDTSGPROT_066 GUARD_DTS.DTSGPROT_066
#define GUARD_DTSDTSGPROT_067 GUARD_DTS.DTSGPROT_067
#define GUARD_DTSDTSGPROT_068 GUARD_DTS.DTSGPROT_068
#define GUARD_DTSDTSGPROT_069 GUARD_DTS.DTSGPROT_069
#define GUARD_DTSDTSGPROT_070 GUARD_DTS.DTSGPROT_070
#define GUARD_DTSDTSGPROT_071 GUARD_DTS.DTSGPROT_071
#define GUARD_DTSDTSGPROT_072 GUARD_DTS.DTSGPROT_072
#define GUARD_DTSDTSGPROT_073 GUARD_DTS.DTSGPROT_073
#define GUARD_DTSDTSGPROT_074 GUARD_DTS.DTSGPROT_074
#define GUARD_DTSDTSGPROT_075 GUARD_DTS.DTSGPROT_075
#define GUARD_DTSDTSGPROT_076 GUARD_DTS.DTSGPROT_076
#define GUARD_DTSDTSGPROT_077 GUARD_DTS.DTSGPROT_077
#define GUARD_DTSDTSGPROT_078 GUARD_DTS.DTSGPROT_078
#define GUARD_DTSDTSGPROT_079 GUARD_DTS.DTSGPROT_079
#define GUARD_DTSDTSGPROT_080 GUARD_DTS.DTSGPROT_080
#define GUARD_DTSDTSGPROT_081 GUARD_DTS.DTSGPROT_081
#define GUARD_DTSDTSGPROT_082 GUARD_DTS.DTSGPROT_082
#define GUARD_DTSDTSGPROT_083 GUARD_DTS.DTSGPROT_083
#define GUARD_DTSDTSGPROT_084 GUARD_DTS.DTSGPROT_084
#define GUARD_DTSDTSGPROT_085 GUARD_DTS.DTSGPROT_085
#define GUARD_DTSDTSGPROT_086 GUARD_DTS.DTSGPROT_086
#define GUARD_DTSDTSGPROT_087 GUARD_DTS.DTSGPROT_087
#define GUARD_DTSDTSGPROT_088 GUARD_DTS.DTSGPROT_088
#define GUARD_DTSDTSGPROT_089 GUARD_DTS.DTSGPROT_089
#define GUARD_DTSDTSGPROT_090 GUARD_DTS.DTSGPROT_090
#define GUARD_DTSDTSGPROT_091 GUARD_DTS.DTSGPROT_091
#define GUARD_DTSDTSGPROT_092 GUARD_DTS.DTSGPROT_092
#define GUARD_DTSDTSGPROT_093 GUARD_DTS.DTSGPROT_093
#define GUARD_DTSDTSGPROT_094 GUARD_DTS.DTSGPROT_094
#define GUARD_DTSDTSGPROT_095 GUARD_DTS.DTSGPROT_095
#define GUARD_DTSDTSGPROT_096 GUARD_DTS.DTSGPROT_096
#define GUARD_DTSDTSGPROT_097 GUARD_DTS.DTSGPROT_097
#define GUARD_DTSDTSGPROT_098 GUARD_DTS.DTSGPROT_098
#define GUARD_DTSDTSGPROT_099 GUARD_DTS.DTSGPROT_099
#define GUARD_DTSDTSGPROT_100 GUARD_DTS.DTSGPROT_100
#define GUARD_DTSDTSGPROT_101 GUARD_DTS.DTSGPROT_101
#define GUARD_DTSDTSGPROT_102 GUARD_DTS.DTSGPROT_102
#define GUARD_DTSDTSGPROT_103 GUARD_DTS.DTSGPROT_103
#define GUARD_DTSDTSGPROT_104 GUARD_DTS.DTSGPROT_104
#define GUARD_DTSDTSGPROT_105 GUARD_DTS.DTSGPROT_105
#define GUARD_DTSDTSGPROT_106 GUARD_DTS.DTSGPROT_106
#define GUARD_DTSDTSGPROT_107 GUARD_DTS.DTSGPROT_107
#define GUARD_DTSDTSGPROT_108 GUARD_DTS.DTSGPROT_108
#define GUARD_DTSDTSGPROT_109 GUARD_DTS.DTSGPROT_109
#define GUARD_DTSDTSGPROT_110 GUARD_DTS.DTSGPROT_110
#define GUARD_DTSDTSGPROT_111 GUARD_DTS.DTSGPROT_111
#define GUARD_DTSDTSGPROT_112 GUARD_DTS.DTSGPROT_112
#define GUARD_DTSDTSGPROT_113 GUARD_DTS.DTSGPROT_113
#define GUARD_DTSDTSGPROT_114 GUARD_DTS.DTSGPROT_114
#define GUARD_DTSDTSGPROT_115 GUARD_DTS.DTSGPROT_115
#define GUARD_DTSDTSGPROT_116 GUARD_DTS.DTSGPROT_116
#define GUARD_DTSDTSGPROT_117 GUARD_DTS.DTSGPROT_117
#define GUARD_DTSDTSGPROT_118 GUARD_DTS.DTSGPROT_118
#define GUARD_DTSDTSGPROT_119 GUARD_DTS.DTSGPROT_119
#define GUARD_DTSDTSGPROT_120 GUARD_DTS.DTSGPROT_120
#define GUARD_DTSDTSGPROT_121 GUARD_DTS.DTSGPROT_121
#define GUARD_DTSDTSGPROT_122 GUARD_DTS.DTSGPROT_122
#define GUARD_DTSDTSGPROT_123 GUARD_DTS.DTSGPROT_123
#define GUARD_DTSDTSGPROT_124 GUARD_DTS.DTSGPROT_124
#define GUARD_DTSDTSGPROT_125 GUARD_DTS.DTSGPROT_125
#define GUARD_DTSDTSGPROT_126 GUARD_DTS.DTSGPROT_126
#define GUARD_DTSDTSGPROT_127 GUARD_DTS.DTSGPROT_127
#define GUARD_DMAC0DMAGOVFCLR GUARD_DMAC0.DMAGOVFCLR
#define GUARD_DMAC0DMAGOVFSTAT GUARD_DMAC0.DMAGOVFSTAT
#define GUARD_DMAC0DMAGERRADDR GUARD_DMAC0.DMAGERRADDR
#define GUARD_DMAC0DMAGERRTYPE GUARD_DMAC0.DMAGERRTYPE
#define GUARD_DMAC0DMAGSPIDERRCLR GUARD_DMAC0.DMAGSPIDERRCLR
#define GUARD_DMAC0DMAGSPIDERRSTAT GUARD_DMAC0.DMAGSPIDERRSTAT
#define GUARD_DMAC0DMAGKCPROT GUARD_DMAC0.DMAGKCPROT
#define GUARD_DMAC0DMAGMPID0 GUARD_DMAC0.DMAGMPID0
#define GUARD_DMAC0DMAGMPID1 GUARD_DMAC0.DMAGMPID1
#define GUARD_DMAC0DMAGMPID2 GUARD_DMAC0.DMAGMPID2
#define GUARD_DMAC0DMAGMPID3 GUARD_DMAC0.DMAGMPID3
#define GUARD_DMAC0DMAGMPID4 GUARD_DMAC0.DMAGMPID4
#define GUARD_DMAC0DMAGMPID5 GUARD_DMAC0.DMAGMPID5
#define GUARD_DMAC0DMAGMPID6 GUARD_DMAC0.DMAGMPID6
#define GUARD_DMAC0DMAGMPID7 GUARD_DMAC0.DMAGMPID7
#define GUARD_DMAC0DMAGPROT_GR GUARD_DMAC0.DMAGPROT_GR
#define GUARD_DMAC0DMAGPROT_DP GUARD_DMAC0.DMAGPROT_DP
#define GUARD_DMAC0DMAGPROT_000 GUARD_DMAC0.DMAGPROT_000
#define GUARD_DMAC0DMAGPROT_001 GUARD_DMAC0.DMAGPROT_001
#define GUARD_DMAC0DMAGPROT_002 GUARD_DMAC0.DMAGPROT_002
#define GUARD_DMAC0DMAGPROT_003 GUARD_DMAC0.DMAGPROT_003
#define GUARD_DMAC0DMAGPROT_004 GUARD_DMAC0.DMAGPROT_004
#define GUARD_DMAC0DMAGPROT_005 GUARD_DMAC0.DMAGPROT_005
#define GUARD_DMAC0DMAGPROT_006 GUARD_DMAC0.DMAGPROT_006
#define GUARD_DMAC0DMAGPROT_007 GUARD_DMAC0.DMAGPROT_007
#define GUARD_DMAC0DMAGPROT_008 GUARD_DMAC0.DMAGPROT_008
#define GUARD_DMAC0DMAGPROT_009 GUARD_DMAC0.DMAGPROT_009
#define GUARD_DMAC0DMAGPROT_010 GUARD_DMAC0.DMAGPROT_010
#define GUARD_DMAC0DMAGPROT_011 GUARD_DMAC0.DMAGPROT_011
#define GUARD_DMAC0DMAGPROT_012 GUARD_DMAC0.DMAGPROT_012
#define GUARD_DMAC0DMAGPROT_013 GUARD_DMAC0.DMAGPROT_013
#define GUARD_DMAC0DMAGPROT_014 GUARD_DMAC0.DMAGPROT_014
#define GUARD_DMAC0DMAGPROT_015 GUARD_DMAC0.DMAGPROT_015
#define GUARD_DMAC1DMAGOVFCLR GUARD_DMAC1.DMAGOVFCLR
#define GUARD_DMAC1DMAGOVFSTAT GUARD_DMAC1.DMAGOVFSTAT
#define GUARD_DMAC1DMAGERRADDR GUARD_DMAC1.DMAGERRADDR
#define GUARD_DMAC1DMAGERRTYPE GUARD_DMAC1.DMAGERRTYPE
#define GUARD_DMAC1DMAGSPIDERRCLR GUARD_DMAC1.DMAGSPIDERRCLR
#define GUARD_DMAC1DMAGSPIDERRSTAT GUARD_DMAC1.DMAGSPIDERRSTAT
#define GUARD_DMAC1DMAGKCPROT GUARD_DMAC1.DMAGKCPROT
#define GUARD_DMAC1DMAGMPID0 GUARD_DMAC1.DMAGMPID0
#define GUARD_DMAC1DMAGMPID1 GUARD_DMAC1.DMAGMPID1
#define GUARD_DMAC1DMAGMPID2 GUARD_DMAC1.DMAGMPID2
#define GUARD_DMAC1DMAGMPID3 GUARD_DMAC1.DMAGMPID3
#define GUARD_DMAC1DMAGMPID4 GUARD_DMAC1.DMAGMPID4
#define GUARD_DMAC1DMAGMPID5 GUARD_DMAC1.DMAGMPID5
#define GUARD_DMAC1DMAGMPID6 GUARD_DMAC1.DMAGMPID6
#define GUARD_DMAC1DMAGMPID7 GUARD_DMAC1.DMAGMPID7
#define GUARD_DMAC1DMAGPROT_GR GUARD_DMAC1.DMAGPROT_GR
#define GUARD_DMAC1DMAGPROT_DP GUARD_DMAC1.DMAGPROT_DP
#define GUARD_DMAC1DMAGPROT_000 GUARD_DMAC1.DMAGPROT_000
#define GUARD_DMAC1DMAGPROT_001 GUARD_DMAC1.DMAGPROT_001
#define GUARD_DMAC1DMAGPROT_002 GUARD_DMAC1.DMAGPROT_002
#define GUARD_DMAC1DMAGPROT_003 GUARD_DMAC1.DMAGPROT_003
#define GUARD_DMAC1DMAGPROT_004 GUARD_DMAC1.DMAGPROT_004
#define GUARD_DMAC1DMAGPROT_005 GUARD_DMAC1.DMAGPROT_005
#define GUARD_DMAC1DMAGPROT_006 GUARD_DMAC1.DMAGPROT_006
#define GUARD_DMAC1DMAGPROT_007 GUARD_DMAC1.DMAGPROT_007
#define GUARD_DMAC1DMAGPROT_008 GUARD_DMAC1.DMAGPROT_008
#define GUARD_DMAC1DMAGPROT_009 GUARD_DMAC1.DMAGPROT_009
#define GUARD_DMAC1DMAGPROT_010 GUARD_DMAC1.DMAGPROT_010
#define GUARD_DMAC1DMAGPROT_011 GUARD_DMAC1.DMAGPROT_011
#define GUARD_DMAC1DMAGPROT_012 GUARD_DMAC1.DMAGPROT_012
#define GUARD_DMAC1DMAGPROT_013 GUARD_DMAC1.DMAGPROT_013
#define GUARD_DMAC1DMAGPROT_014 GUARD_DMAC1.DMAGPROT_014
#define GUARD_DMAC1DMAGPROT_015 GUARD_DMAC1.DMAGPROT_015
#define GUARD_BARRBRGOVFCLR GUARD_BARR.BRGOVFCLR
#define GUARD_BARRBRGOVFSTAT GUARD_BARR.BRGOVFSTAT
#define GUARD_BARRBRGERRADDR GUARD_BARR.BRGERRADDR
#define GUARD_BARRBRGERRTYPE GUARD_BARR.BRGERRTYPE
#define GUARD_BARRBRGSPIDERRCLR GUARD_BARR.BRGSPIDERRCLR
#define GUARD_BARRBRGSPIDERRSTAT GUARD_BARR.BRGSPIDERRSTAT
#define GUARD_BARRBRGKCPROT GUARD_BARR.BRGKCPROT
#define GUARD_BARRBRGPROT0_0 GUARD_BARR.BRGPROT0_0
#define GUARD_BARRBRGPROT1_0 GUARD_BARR.BRGPROT1_0
#define GUARD_BARRBRGPROT0_1 GUARD_BARR.BRGPROT0_1
#define GUARD_BARRBRGPROT1_1 GUARD_BARR.BRGPROT1_1
#define GUARD_BARRBRGPROT0_2 GUARD_BARR.BRGPROT0_2
#define GUARD_BARRBRGPROT1_2 GUARD_BARR.BRGPROT1_2
#define GUARD_BARRBRGPROT0_3 GUARD_BARR.BRGPROT0_3
#define GUARD_BARRBRGPROT1_3 GUARD_BARR.BRGPROT1_3
#define GUARD_BARRBRGPROT0_4 GUARD_BARR.BRGPROT0_4
#define GUARD_BARRBRGPROT1_4 GUARD_BARR.BRGPROT1_4
#define GUARD_BARRBRGPROT0_5 GUARD_BARR.BRGPROT0_5
#define GUARD_BARRBRGPROT1_5 GUARD_BARR.BRGPROT1_5
#define GUARD_BARRBRGPROT0_6 GUARD_BARR.BRGPROT0_6
#define GUARD_BARRBRGPROT1_6 GUARD_BARR.BRGPROT1_6
#define GUARD_BARRBRGPROT0_7 GUARD_BARR.BRGPROT0_7
#define GUARD_BARRBRGPROT1_7 GUARD_BARR.BRGPROT1_7
#define GUARD_BARRBRGPROT0_8 GUARD_BARR.BRGPROT0_8
#define GUARD_BARRBRGPROT1_8 GUARD_BARR.BRGPROT1_8
#define GUARD_BARRBRGPROT0_9 GUARD_BARR.BRGPROT0_9
#define GUARD_BARRBRGPROT1_9 GUARD_BARR.BRGPROT1_9
#define GUARD_BARRBRGPROT0_10 GUARD_BARR.BRGPROT0_10
#define GUARD_BARRBRGPROT1_10 GUARD_BARR.BRGPROT1_10
#define GUARD_BARRBRGPROT0_11 GUARD_BARR.BRGPROT0_11
#define GUARD_BARRBRGPROT1_11 GUARD_BARR.BRGPROT1_11
#define GUARD_BARRBRGPROT0_12 GUARD_BARR.BRGPROT0_12
#define GUARD_BARRBRGPROT1_12 GUARD_BARR.BRGPROT1_12
#define GUARD_BARRBRGPROT0_13 GUARD_BARR.BRGPROT0_13
#define GUARD_BARRBRGPROT1_13 GUARD_BARR.BRGPROT1_13
#define GUARD_BARRBRGPROT0_14 GUARD_BARR.BRGPROT0_14
#define GUARD_BARRBRGPROT1_14 GUARD_BARR.BRGPROT1_14
#define GUARD_BARRBRGPROT0_15 GUARD_BARR.BRGPROT0_15
#define GUARD_BARRBRGPROT1_15 GUARD_BARR.BRGPROT1_15
#define GUARD_BARRBRGPROT0_16 GUARD_BARR.BRGPROT0_16
#define GUARD_BARRBRGPROT1_16 GUARD_BARR.BRGPROT1_16
#define GUARD_IPIRIPIGOVFCLR GUARD_IPIR.IPIGOVFCLR
#define GUARD_IPIRIPIGOVFSTAT GUARD_IPIR.IPIGOVFSTAT
#define GUARD_IPIRIPIGERRADDR GUARD_IPIR.IPIGERRADDR
#define GUARD_IPIRIPIGERRTYPE GUARD_IPIR.IPIGERRTYPE
#define GUARD_IPIRIPIGSPIDERRCLR GUARD_IPIR.IPIGSPIDERRCLR
#define GUARD_IPIRIPIGSPIDERRSTAT GUARD_IPIR.IPIGSPIDERRSTAT
#define GUARD_IPIRIPIGKCPROT GUARD_IPIR.IPIGKCPROT
#define GUARD_IPIRIPIGPROT0_R0 GUARD_IPIR.IPIGPROT0_R0
#define GUARD_IPIRIPIGPROT1_R0 GUARD_IPIR.IPIGPROT1_R0
#define GUARD_IPIRIPIGPROT0_T0 GUARD_IPIR.IPIGPROT0_T0
#define GUARD_IPIRIPIGPROT1_T0 GUARD_IPIR.IPIGPROT1_T0
#define GUARD_IPIRIPIGPROT0_R1 GUARD_IPIR.IPIGPROT0_R1
#define GUARD_IPIRIPIGPROT1_R1 GUARD_IPIR.IPIGPROT1_R1
#define GUARD_IPIRIPIGPROT0_T1 GUARD_IPIR.IPIGPROT0_T1
#define GUARD_IPIRIPIGPROT1_T1 GUARD_IPIR.IPIGPROT1_T1
#define GUARD_IPIRIPIGPROT0_R2 GUARD_IPIR.IPIGPROT0_R2
#define GUARD_IPIRIPIGPROT1_R2 GUARD_IPIR.IPIGPROT1_R2
#define GUARD_IPIRIPIGPROT0_T2 GUARD_IPIR.IPIGPROT0_T2
#define GUARD_IPIRIPIGPROT1_T2 GUARD_IPIR.IPIGPROT1_T2
#define GUARD_IPIRIPIGPROT0_R3 GUARD_IPIR.IPIGPROT0_R3
#define GUARD_IPIRIPIGPROT1_R3 GUARD_IPIR.IPIGPROT1_R3
#define GUARD_IPIRIPIGPROT0_T3 GUARD_IPIR.IPIGPROT0_T3
#define GUARD_IPIRIPIGPROT1_T3 GUARD_IPIR.IPIGPROT1_T3
#define GUARD_IPIRIPIGPROT0_4 GUARD_IPIR.IPIGPROT0_4
#define GUARD_IPIRIPIGPROT1_4 GUARD_IPIR.IPIGPROT1_4









#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) ||(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  extern uint32 TRBSYS_ConfigurationSettingsArea[1024];
  #define RBSYS_CSAf_base ((uint32)&TRBSYS_ConfigurationSettingsArea)
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  #define SYSCTRLCKSC_CLEANS SYSCTRLCKSC_CPUS
  #define SYSCTRLCKSC_CLEANC SYSCTRLCKSC_CPUC
#endif


#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  typedef struct {
    uint32 NSC_DEBUG_CFG;
    uint32 NSC_CFG;
    uint32 NSC_STATUS;
    uint32 NSC_CTRL;
    uint32 NSC_LWORD_READ;
    uint32 NSC_HWORD_READ;
    uint32 NSC_LWORD_RELOAD;
    uint32 NSC_HWORD_RELOAD;
    uint32 NSC_INCSTEP_CFG;
    uint32 NSC_STATUS_CH2;
    uint32 NSC_CTRL_CH2;
    uint32 NSC_LWORD_READ_CH2;
    uint32 NSC_HWORD_READ_CH2;
    uint32 NSC_LWORD_READ_NOLATCH;
    uint32 NSC_HWORD_READ_NOLATCH;
    uint32 NSC_LWORD_READ_CH2_NOLATCH;
    uint32 NSC_HWORD_READ_CH2_NOLATCH;
    uint8 ADR_reserved0[188];
    uint32 EXNTP_DEBUG_CFG;
    uint32 EXNTP_CFG;
    uint32 EXNTP_STATUS;
    uint32 EXNTP_CTRL;
    uint32 EXNTP_READ_NANOSECOND;
    uint32 EXNTP_READ_SECOND;
    uint32 EXNTP_READ_EXSECOND;
    uint32 EXNTP_RELOAD_NANOSECOND;
    uint32 EXNTP_RELOAD_SECOND;
    uint32 EXNTP_RELOAD_EXSECOND;
    uint32 EXNTP_INCSTEP_CFG;
    uint32 EXNTP_EVENT_GEN_CFG;
    uint32 EXNTP_READ_NANOSECOND_NOLATCH;
    uint32 EXNTP_READ_SECOND_NOLATCH;
    uint32 EXNTP_READ_EXSECOND_NOLATCH;
    uint8 ADR_reserved1[4];
    struct {
        uint32 DEBUG_CFG;
        uint32 CFG;
        uint32 STATUS;
        uint32 CTRL;
        uint32 LWORD_READ;
        uint32 HWORD_READ;
        uint32 LWORD_RELOAD;
        uint32 HWORD_RELOAD;
        uint32 EVENT_GEN_CFG;
        uint32 INCSTEP_CFG;
        uint32 LWORD_READ_NOLATCH;
        uint32 HWORD_READ_NOLATCH;
        uint8 GST_reserved2[16];
    } OTC[4];
    struct {
        uint32 DEBUG_CFG;
        uint32 CFG;
        uint32 STATUS;
        uint32 CTRL;
        uint32 RELOAD_VALUE;
        uint32 EXPIRY_CFG;
        uint32 COMPARE_1_CFG;
        uint32 COMPARE_2_CFG;
        uint32 COMPARE_3_CFG;
        uint32 COMPARE_4_CFG;
        uint32 INT_PULSE_EN_CFG;
        uint32 INT_STATUS;
        uint32 INT_CLR;
        uint32 EVENT_GEN_CFG;
        uint32 READ;
        uint8 GST_reserved3[4];
    } ARC[10];
    uint8 ADR_reserved4[1408];
    struct {
        uint32 UPDATE_EVENT_STRETCH_CFG;
        uint32 SOURCE_SEL_CFG;
        uint32 BIT_SEL_CFG;
        uint8 GST_reserved5[4];
    } TS[6];
    uint8 ADR_reserved6[32];
    uint32 GLBL_FRZ_IN_DBG_1_CFG;
    uint32 GLBL_FRZ_IN_DBG_2_CFG;
    uint32 GLBL_LATCH_CTRL;
    uint32 GLBL_LATCH_CLR;
    uint32 CLK_CTRL;
    uint8 ADR_reserved7[44];
    uint32 OCU_COMPARE_START_LWORD;
    uint32 OCU_COMPARE_START_HWORD;
    uint32 OCU_COMPARE_DELTA_CFG;
    uint8 ADR_reserved8[244];
    struct {
        uint32 STRETCH_CYCLE_CFG1;
        uint32 STRETCH_CYCLE_CFG2;
        uint32 STRETCH_EN_CFG;
        uint8 GST_reserved9[20];
    } ARC_TRIG[10];
  } GST_t;

  extern volatile GST_t GST_0;


typedef struct
{
    volatile uint32 GS;                      //[0x000] : Global Status Register
    volatile uint32 MCTL;                    //[0x004] : Mode Control Register
    volatile uint32 ME;                      //[0x008] : Mode Enable Register
    volatile uint32 IS;                      //[0x00C] : Interrupt Status Register
    volatile uint32 IM;                      //[0x010] : Interrupt Mask Register
    volatile uint32 IMTS;                    //[0x014] : Invalid Mode Transition Status Register
    volatile uint32 DMTS;                    //[0x018] : Debug Mode Transition Status Register
    volatile uint32 RESERVED0[1];            //[0x01C...0x01F] : reserved space
    volatile uint32 RESET_MC;                //[0x020] : RESET Mode Configuration Register
    volatile uint32 TEST_MC;                 //[0x024] : TEST Mode Configuration Register
    volatile uint32 SAFE_MC;                 //[0x028] : SAFE Mode Configuration Register
    volatile uint32 DRUN_MC;                 //[0x02C] : DRUN Mode Configuration Register
    volatile uint32 RUN0_MC;                 //[0x030] : RUNn Mode Configuration Registers
    volatile uint32 RUN1_MC;                 //[0x034] : RUNn Mode Configuration Registers
    volatile uint32 RUN2_MC;                 //[0x038] : RUNn Mode Configuration Registers
    volatile uint32 RUN3_MC;                 //[0x03C] : RUNn Mode Configuration Registers
    volatile uint32 RESERVED1[5];            //[0x040...0x053] : reserved space
    volatile uint32 STANDBY0_MC;             //[0x054] : STANDBY0_MC
    volatile uint32 RESERVED2[10];           //[0x058...0x07F] : reserved space
    volatile uint32 RUN_PC[8];               //[0x080...0x09C] : Run Peripheral Configuration Registers
    volatile uint32 LP_PC[8];                //[0x0A0...0x0BC] : Low-Power Peripheral Configuration Registers
    volatile uint32 RESERVED3[64];           //[0x0C0...0x1BF] : reserved space
} rba_Reg_MC_ME_ModeReg_tst;

typedef struct
{
    volatile uint32 CS;                      //[0x1C0] : Core Status Register
    volatile uint16 CCTL[2];                 //[0x1C4...0x1C6] : CORE Control Register
    volatile uint16 RESERVED0[12];           //[0x1C8...0x1DF] : reserved space
    volatile uint32 CADDR[2];                //[0x1E0...0x1E7] : CORE Address Register: 0: core0 of cluster, 1: core1 of cluster
    volatile uint32 RESERVED1[6];            //[0x1E8...0x1FF] : reserved space
    volatile uint32 PSx_M0[8];               //[0x200...0x21C] : Peripheral status register for MODS0 - AIPS0
    volatile uint32 PSx_M1[8];               //[0x220...0x23C] : Peripheral status register for MODS1 - AIPS1
    volatile uint32 PSx_M2[8];               //[0x240...0x25C] : Peripheral status register for MODS2 - AIPS2
    volatile uint32 PSx_M3[8];               //[0x260...0x27C] : Peripheral status register for MODS3 - AIPS3
    volatile uint32 PSx_M4[8];               //[0x280...0x29C] : Peripheral status register for MODS4 - AIPS4
    volatile uint32 PSx_M5[8];               //[0x2A0...0x2BC] : Peripheral status register for MODS5 - AIPS5
    volatile uint32 RESERVED2[80];           //[0x2C0...0x3FC] : reserved space
} rba_Reg_MC_ME_CoreReg_tst;

typedef struct
{
    rba_Reg_MC_ME_ModeReg_tst   ModeReg;     // mode registers
    rba_Reg_MC_ME_CoreReg_tst   CoreReg;     // core registers
    volatile uint8 PCTL[1536];               //[0x400...0x9FC] : PCTL0..1535
} rba_Reg_MC_ME_tst;


  extern volatile rba_Reg_MC_ME_tst MC_ME_PER;
  extern volatile rba_Reg_MC_ME_tst MC_ME_CL0;
  extern volatile rba_Reg_MC_ME_tst MC_ME_CL1;
  extern volatile rba_Reg_MC_ME_tst MC_ME_CL2;

  typedef struct {
      uint32 PLL0CR;
      uint32 PLL0SR;
      uint32 PLL0DV;
      uint8 ADR_reserved0[24];

      uint32 PLL1SR;
      uint32 PLL1DV;
      uint32 PLL1FM;
  }PLLDIG_PERIPHERAL_DOMAIN_t;
  extern volatile PLLDIG_PERIPHERAL_DOMAIN_t PLLDIG_PERIPHERAL_DOMAIN;


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

  typedef struct {
    uint32 CR;
    uint32 MEM_SCRB;
  }PRAMC_AXI_tag;
  typedef struct {
    uint32 PRCR1;
  }PRAMC_tag;
  extern volatile PRAMC_AXI_tag PRAM_0;
  extern volatile PRAMC_AXI_tag PRAM_1;
  extern volatile PRAMC_AXI_tag PRAM_2;
  extern volatile PRAMC_AXI_tag PRAM_3;
  extern volatile PRAMC_AXI_tag PRAM_4;
  extern volatile PRAMC_tag PRAM_5;
  extern volatile PRAMC_tag PRAM_6;
  extern volatile PRAMC_tag PRAM_7;
  extern volatile PRAMC_tag PRAM_8;
  extern volatile PRAMC_AXI_tag PRAM_9;
  extern volatile PRAMC_AXI_tag PRAM_10;
  extern volatile PRAMC_AXI_tag PRAM_12;

  typedef struct  {
    uint32 CR;
    uint32 MEM_SCRB;
  }OVLY_PRAM_tag;
  extern volatile OVLY_PRAM_tag OVLY_PRAM_0;
  extern volatile OVLY_PRAM_tag OVLY_PRAM_1;
  extern volatile OVLY_PRAM_tag OVLY_PRAM_2;
  extern volatile OVLY_PRAM_tag OVLY_PRAM_3;
  extern volatile OVLY_PRAM_tag OVLY_PRAM_4;
  extern volatile OVLY_PRAM_tag OVLY_PRAM_5;

  typedef struct {
    uint32 PFCR1;
    uint32 PFCR2;
    uint32 PFCR3;
    uint32 PFSR;
    uint32 FLTENA;
    uint32 FLTFRC;
    uint32 FLTSCR;
    uint32 FLTADR;
    uint8 ADR_reserved0[752];

    uint32 PFCMC;
    uint32 PFCMOC;
    uint32 PFCHC;
    uint32 PFCHOC;
    uint32 PFFHC;
    uint32 PFFHOC;
    uint8 ADR_reserved1[8];

    uint32 PFPFC;
    uint32 PFPFOC;
    uint32 PFPFHC;
    uint32 PFPFHOC;
  }NVM_CTRL_tag;
  extern volatile NVM_CTRL_tag NVM_CTRL_0_0;
  extern volatile NVM_CTRL_tag NVM_CTRL_0_1;
  extern volatile NVM_CTRL_tag NVM_CTRL_1_0;
  extern volatile NVM_CTRL_tag NVM_CTRL_1_1;
  extern volatile NVM_CTRL_tag NVM_CTRL_2_0;
  extern volatile NVM_CTRL_tag NVM_CTRL_2_1;

  typedef struct {
    uint32 CR;
    uint32 IR;
    uint32 TO;
    uint32 WN;
    uint32 SR;
    uint32 CO;
    uint32 SK;
  }SWT_tag;
  extern volatile SWT_tag SWT_SYS_0;

  typedef struct {
    uint32 DES;
    uint8 ADR_reserved0[764];
    uint32 FES;
    uint8 ADR_reserved1[60];
    uint32 FESS;
  }MC_RGM_DOMAIN_tag;
  extern volatile MC_RGM_DOMAIN_tag MC_RGM_CL0;
  extern volatile MC_RGM_DOMAIN_tag MC_RGM_CL1;
  extern volatile MC_RGM_DOMAIN_tag MC_RGM_CL2;

  typedef struct {
    uint32 DES;
    uint8 ADR_reserved0[12];

    uint32 DERD;
    uint8 ADR_reserved1[12];

    uint32 DEAR;
    uint8 ADR_reserved2[12];

    uint32 DBRE;
    uint8 ADR_reserved3[716];

    uint32 FES;
    uint8 ADR_reserved4[12];

    uint32 FERD;
    uint8 ADR_reserved5[12];

    uint32 FEAR;
    uint8 ADR_reserved6[12];

    uint32 FBRE;
    uint8 ADR_reserved7[12];

    uint32 FESS;
    uint8 ADR_reserved8[707];

    uint8 FRET;
    uint8 ADR_reserved9[3];

    uint8 DRET;
    uint8 ADR_reserved10[3];

    uint8 EROEC;
    uint32 PRST0_M0;
    uint32 PRST1_M0;
    uint32 PRST2_M0;
    uint32 PRST3_M0;
    uint32 PRST4_M0;
    uint32 PRST5_M0;
    uint32 PRST6_M0;
    uint32 PRST7_M0;
    uint32 PSTAT0_M0;
    uint32 PSTAT1_M0;
    uint32 PSTAT2_M0;
    uint32 PSTAT3_M0;
    uint32 PSTAT4_M0;
    uint32 PSTAT5_M0;
    uint32 PSTAT6_M0;
    uint32 PSTAT7_M0;
    uint8 ADR_reserved11[4];

    uint32 PRST1_M1;
    uint32 PRST2_M1;
    uint32 PRST3_M1;
    uint32 PRST4_M1;
    uint32 PRST5_M1;
    uint32 PRST6_M1;
    uint32 PRST7_M1;
    uint8 ADR_reserved12[4];

    uint32 PSTAT1_M1;
    uint32 PSTAT2_M1;
    uint32 PSTAT3_M1;
    uint32 PSTAT4_M1;
    uint32 PSTAT5_M1;
    uint32 PSTAT6_M1;
    uint32 PSTAT7_M1;
    uint8 ADR_reserved13[4];

    uint32 PRST1_M2;
    uint8 ADR_reserved14[12];

    uint32 PRST5_M2;
    uint32 PRST6_M2;
    uint32 PRST7_M2;
    uint8 ADR_reserved15[4];

    uint32 PSTAT1_M2;
    uint8 ADR_reserved16[12];

    uint32 PSTAT5_M2;
    uint32 PSTAT6_M2;
    uint32 PSTAT7_M2;
    uint8 ADR_reserved17[4];

    uint32 PRST1_M3;
    uint8 ADR_reserved18[12];

    uint32 PRST5_M3;
    uint32 PRST6_M3;
    uint32 PRST7_M3;
    uint8 ADR_reserved19[4];

    uint32 PSTAT1_M3;
    uint8 ADR_reserved20[12];

    uint32 PSTAT5_M3;
    uint32 PSTAT6_M3;
    uint32 PSTAT7_M3;
    uint8 ADR_reserved21[8];

    uint32 PRST2_M4;
    uint8 ADR_reserved22[12];

    uint32 PRST6_M4;
    uint32 PRST7_M4;
    uint8 ADR_reserved23[8];

    uint32 PSTAT2_M4;
    uint8 ADR_reserved24[12];

    uint32 PSTAT6_M4;
    uint32 PSTAT7_M4;
    uint8 ADR_reserved25[8];

    uint32 PRST2_M5;
    uint32 PRST3_M5;
    uint8 ADR_reserved26[4];

    uint32 PRST5_M5;
    uint32 PRST6_M5;
    uint32 PRST7_M5;
    uint8 ADR_reserved27[8];

    uint32 PSTAT2_M5;
    uint32 PSTAT3_M5;
    uint8 ADR_reserved28[4];

    uint32 PSTAT5_M5;
    uint32 PSTAT6_M5;
    uint32 PSTAT7_M5;
  }MC_RGM_PERIPHERAL_DOMAIN_tag;
  extern volatile MC_RGM_PERIPHERAL_DOMAIN_tag MC_RGM_PER;

  typedef struct {
    uint8 ADR_reserved0[259];

    uint8 PCS_SDUR;
    uint32 PCS_DIVC1;
    uint32 PCS_DIVE1;
    uint32 PCS_DIVS1;
    uint32 PCS_DIVC2;
    uint32 PCS_DIVE2;
    uint32 PCS_DIVS2;
    uint32 PCS_DIVC3;
    uint32 PCS_DIVE3;
    uint32 PCS_DIVS3;
    uint32 PCS_DIVC4;
    uint32 PCS_DIVE4;
    uint32 PCS_DIVS4;
    uint32 PCS_DIVC5;
    uint32 PCS_DIVE5;
    uint32 PCS_DIVS5;
    uint8 ADR_reserved1[144];

    uint32 SC_DIV_RC;
    uint32 DIV_UPD_TYPE;
    uint32 DIV_UPD_TRIG;
    uint32 DIV_UPD_STAT;
    uint8 ADR_reserved2[4];

    uint32 SC_SS;
    uint32 SC_DC[5];
    uint8 ADR_reserved3[4];

    uint32 AC0_SC;
    uint32 AC0_SS;
  } MC_CGM_DOMAIN_0_t;

  typedef struct  {
    uint8 ADR_reserved0[259];

    uint8 PCS_SDUR;
    uint32 PCS_DIVC1;
    uint32 PCS_DIVE1;
    uint32 PCS_DIVS1;
    uint32 PCS_DIVC2;
    uint32 PCS_DIVE2;
    uint32 PCS_DIVS2;
    uint32 PCS_DIVC3;
    uint32 PCS_DIVE3;
    uint32 PCS_DIVS3;
    uint32 PCS_DIVC4;
    uint32 PCS_DIVE4;
    uint32 PCS_DIVS4;
    uint32 PCS_DIVC5;
    uint32 PCS_DIVE5;
    uint32 PCS_DIVS5;
    uint8 ADR_reserved1[144];

    uint32 SC_DIV_RC;
    uint32 DIV_UPD_TYPE;
    uint32 DIV_UPD_TRIG;
    uint32 DIV_UPD_STAT;
    uint8 ADR_reserved2[4];

    uint32 SC_SS;
    uint32 SC_DC[2];
    uint8 ADR_reserved3[16];

    uint32 AC0_SC;
    uint32 AC0_SS;
  } MC_CGM_DOMAIN_1_2_t;

  typedef struct {
    uint8 ADR_reserved0[128];

    uint32 AC5_CDC0;
    uint32 AC5_CDC1;
    uint32 AC5_CDC2;
    uint8 ADR_reserved1[4];

    uint32 AC5_CDC10;
    uint32 AC5_CDC11;
    uint32 AC5_CDC12;
    uint32 AC5_CDC13;
    uint32 AC5_CDC20;
    uint32 AC5_CDC21;
    uint32 AC5_CDC22;
    uint32 AC5_CDC23;
    uint8 ADR_reserved2[83];

    uint8 PCS_SDUR;
    uint32 PCS_DIVC1;
    uint32 PCS_DIVE1;
    uint32 PCS_DIVS1;
    uint32 PCS_DIVC2;
    uint32 PCS_DIVE2;
    uint32 PCS_DIVS2;
    uint32 PCS_DIVC3;
    uint32 PCS_DIVE3;
    uint32 PCS_DIVS3;
    uint8 ADR_reserved3[96];

    uint32 PCS_DIVC12;
    uint32 PCS_DIVE12;
    uint32 PCS_DIVS12;
    uint8 ADR_reserved4[60];

    uint32 SC_DIV_RC;
    uint32 DIV_UPD_TYPE;
    uint32 DIV_UPD_TRIG;
    uint32 DIV_UPD_STAT;
    uint8 ADR_reserved5[4];

    uint32 SC_SS;
    uint32 SC_DC0;
    uint8 ADR_reserved6[52];

    uint32 AC1_SC;
    uint32 AC1_SS;
    uint8 ADR_reserved7[32];

    uint32 AC2_DC0;
    uint8 ADR_reserved8[20];

    uint32 AC3_SC;
    uint32 AC3_SS;
    uint32 AC3_DC[4];
    uint8 ADR_reserved9[8];

    uint32 AC4_SC;
    uint32 AC4_SS;
    uint32 AC4_DC0;
    uint8 ADR_reserved10[28];

    uint32 AC5_DC0;
    uint32 AC5_DC1;
    uint32 AC5_DC2;
    uint8 ADR_reserved11[12];

    uint32 AC6_SC;
    uint32 AC6_SS;
    uint32 AC6_DC0;
    uint8 ADR_reserved12[20];

    uint32 AC7_SC;
    uint32 AC7_SS;
    uint32 AC7_DC0;
    uint8 ADR_reserved13[20];

    uint32 AC8_SC;
    uint32 AC8_SS;
    uint32 AC8_DC[2];
    uint8 ADR_reserved14[16];

    uint32 AC9_SC;
    uint32 AC9_SS;
    uint32 AC9_DC0;
    uint32 AC9_DC1;
    uint8 ADR_reserved15[16];

    uint32 AC10_SC;
    uint32 AC10_SS;
    uint32 AC10_DC0;
    uint8 ADR_reserved16[20];

    uint32 AC11_SC;
    uint32 AC11_SS;
    uint32 AC11_DC[3];
    uint8 ADR_reserved17[12];

    uint32 AC12_SC;
    uint32 AC12_SS;
    uint32 AC12_DC[5];
    uint8 ADR_reserved18[4];

    uint32 AC13_SC;
    uint32 AC13_SS;
    uint32 AC13_DC0;
  }MC_CGM_PERIPHERAL_DOMAIN_t;

  extern volatile MC_CGM_DOMAIN_0_t          MC_CGM_DOMAIN_0;
  extern volatile MC_CGM_DOMAIN_1_2_t        MC_CGM_DOMAIN_1;
  extern volatile MC_CGM_DOMAIN_1_2_t        MC_CGM_DOMAIN_2;
  extern volatile MC_CGM_PERIPHERAL_DOMAIN_t MC_CGM_PERIPHERAL_DOMAIN;

#endif

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  extern uint32 IMR0;
  extern uint32 IMR1;
  extern uint32 IMR2;
  extern uint32 IMR3;
  extern uint32 IMR4;
  extern uint32 IMR5;
  extern uint32 IMR6;
  extern uint32 IMR7;
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  extern uint32 INTC2IMR1;
  extern uint32 INTC2IMR2;
  extern uint32 INTC2IMR3;
  extern uint32 INTC2IMR4;
  extern uint32 INTC2IMR5;
  extern uint32 INTC2IMR6;
  extern uint32 INTC2IMR7;
  extern uint32 INTC2IMR8;
  extern uint32 INTC2IMR9;
  extern uint32 INTC2IMR10;
  extern uint32 INTC2IMR11;
  extern uint32 INTC2IMR12;
  extern uint32 INTC2IMR13;
  extern uint32 INTC2IMR14;
  extern uint32 INTC2IMR15;
  extern uint32 INTC2IMR16;
  extern uint32 INTC2IMR17;
  extern uint32 INTC2IMR18;
  extern uint32 INTC2IMR19;
  extern uint32 INTC2IMR20;
  extern uint32 INTC2IMR21;
  extern uint32 INTC2IMR22;
  extern uint32 INTC2IMR23;
#endif

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  extern uint32 INTC1_SELFIMR0;
#endif

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  extern uint32 FEINTFMSK0;
  extern uint32 FEINTFMSK1;
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  extern uint32 FEINC_PE0FEINTMSK;
  extern uint32 FEINC_PE1FEINTMSK;
#endif

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  extern uint32 PRDSEL3;
  extern uint32 PRDNAME2;
  extern uint32 PRDNAME3;
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  extern uint32 PRDINFFPRDNAME2;
  extern uint32 PRDINFFPRDNAME3;
  extern uint32 PRDINFFPRDNUM;
#endif


#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  extern uint32 SINTR0;
#elif ( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  extern uint32 EINTSINTR0;
#endif


#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  typedef struct
  {
      volatile uint32 RESERVED0[1];            //[0x71168000...0x71168003] : reserved space
      volatile uint32 MIDR1;                   //[0x71168004] : MIDR1
      volatile uint32 MIDR2;                   //[0x71168008] : MIDR2
      volatile uint32 RESERVED1[1];            //[0x7116800C...0x7116800F] : reserved space
      volatile uint32 DISR0;                   //[0x71168010] : DISR0
      volatile uint32 RESERVED2[1];            //[0x71168014...0x71168017] : reserved space
      volatile uint32 DIRER0;                  //[0x71168018] : DIRER0
      volatile uint32 RESERVED3[1];            //[0x7116801C...0x7116801F] : reserved space
      volatile uint32 DIRSR0;                  //[0x71168020] : DIRSR0
      volatile uint32 RESERVED4[1];            //[0x71168024...0x71168027] : reserved space
      volatile uint32 IREER0;                  //[0x71168028] : IREER0
      volatile uint32 RESERVED5[1];            //[0x7116802C...0x7116802F] : reserved space
      volatile uint32 IFEER0;                  //[0x71168030] : IFEER0
      volatile uint32 RESERVED6[1];            //[0x71168034...0x71168037] : reserved space
      volatile uint32 IFER0;                   //[0x71168038] : IFER0
      volatile uint32 RESERVED7[1];            //[0x7116803C...0x7116803F] : reserved space
      volatile uint32 IFMCR[16];               //[0x71168040...0x7116807C] : IFMCR0
      volatile uint32 RESERVED8[16];           //[0x71168080...0x711680BF] : reserved space
      volatile uint32 IFCPR;                   //[0x711680C0] : IFCPR
      volatile uint32 RESERVED9[15];           //[0x711680C4...0x711680FF] : reserved space
      volatile uint32 SCR0;                    //[0x71168100] : SCR0
      volatile uint32 RESERVED10[31];          //[0x71168104...0x7116817F] : reserved space
      volatile uint32 IPFCPR[4];               //[0x71168180...0x7116818C] : IPFCPR0
      volatile uint32 RESERVED11[44];          //[0x71168190...0x7116823F] : reserved space
      /* all MSCR_IO and MSCR_MUX macros are mapped to MSCR. MSCR_IO is the superset of MSCR_IO and MSCR_MUX */
      /* In MSCR_MUX only SSS and INV bits are present. This bits are at the same position as for MSCR_IO    */
      volatile uint32 MSCR[1024];              //[0x71168240...0x7116923F] : join MSCR_IO and MSCR_MUX to simplify coding
      volatile uint32 RESERVED12[48];          //[0x71169240...0x711692FF] : reserved space
      volatile uint8 GPDO[512];                //[0x71169300...0x711694FF]
      volatile uint8 GPDI[512];                //[0x71169500...0x711696FF]
      volatile uint16 PGPDO[32];               //[0x71169700...0x7116973F]
      volatile uint16 PGPDI[32];               //[0x71169740...0x7116977E]
      volatile uint32 MPGPDO[32];              //[0x71169780...0x711697FC]
  } rba_Reg_SIUL2_tst;
  extern rba_Reg_SIUL2_tst SIUL2_0;


  #define     RBA_REG_FIREWALL_MAX_REGIONS     8u
  #define     RBA_REG_FIREWALL_MAX_BUSMASTER  64u

  typedef struct {
    volatile uint32 CONF;          //[0x7BD01000] : EL1_CONF_REG_0
    volatile uint32 ADDR_START;    //[0x7BD01004] : EL1_ADDR_START_0
    volatile uint32 ADDR_SIZE;     //[0x7BD01008] : EL1_ADDR_SIZE_0
    volatile uint32 RESERVED11[1]; //[0x7BD0100C...0x7BD0100F] : reserved space
  } rba_Reg_Firewall_El1_Addr_tst;


  typedef struct {
    volatile uint32 MSTR_0;            //[0x7BD01200] : EL1_MSTR_0_0
    volatile uint32 MSTR_1;            //[0x7BD01204] : EL1_MSTR_1_0
    volatile uint32 MSTR_2;            //[0x7BD01208] : EL1_MSTR_2_0
    volatile uint32 MSTR_3;            //[0x7BD0120C] : EL1_MSTR_3_0
    volatile uint32 MSTR_4;            //[0x7BD01210] : EL1_MSTR_4_0
    volatile uint32 MSTR_5;            //[0x7BD01214] : EL1_MSTR_5_0
    volatile uint32 MSTR_6;            //[0x7BD01218] : EL1_MSTR_6_0
    volatile uint32 MSTR_7;            //[0x7BD0121C] : EL1_MSTR_7_0
    volatile uint32 MSTR_8;            //[0x7BD01220] : EL1_MSTR_8_0
    volatile uint32 MSTR_9;            //[0x7BD01224] : EL1_MSTR_9_0
    volatile uint32 MSTR_10;           //[0x7BD01228] : EL1_MSTR_10_0
    volatile uint32 MSTR_11;           //[0x7BD0122C] : EL1_MSTR_11_0
    volatile uint32 RESERVED19[6];           //[0x7BD01230...0x7BD01247] : reserved space
    volatile uint32 MSTR_18;           //[0x7BD01248] : EL1_MSTR_18_0
    volatile uint32 RESERVED20[3];           //[0x7BD0124C...0x7BD01257] : reserved space
    volatile uint32 MSTR_22;           //[0x7BD01258] : EL1_MSTR_22_0
    volatile uint32 RESERVED21[1];           //[0x7BD0125C...0x7BD0125F] : reserved space
    volatile uint32 MSTR_24;           //[0x7BD01260] : EL1_MSTR_24_0
    volatile uint32 RESERVED22[7];           //[0x7BD01264...0x7BD0127F] : reserved space
    volatile uint32 MSTR_32;           //[0x7BD01280] : EL1_MSTR_32_0
    volatile uint32 MSTR_33;           //[0x7BD01284] : EL1_MSTR_33_0
    volatile uint32 MSTR_34;           //[0x7BD01288] : EL1_MSTR_34_0
    volatile uint32 MSTR_35;           //[0x7BD0128C] : EL1_MSTR_35_0
    volatile uint32 MSTR_36;           //[0x7BD01290] : EL1_MSTR_36_0
    volatile uint32 MSTR_37;           //[0x7BD01294] : EL1_MSTR_37_0
    volatile uint32 RESERVED23[10];           //[0x7BD01298...0x7BD012BF] : reserved space
    volatile uint32 MSTR_48;           //[0x7BD012C0] : EL1_MSTR_48_0
    volatile uint32 RESERVED24[3];           //[0x7BD012C4...0x7BD012CF] : reserved space
    volatile uint32 MSTR_52;           //[0x7BD012D0] : EL1_MSTR_52_0
    volatile uint32 RESERVED25[3];           //[0x7BD012D8...0x7BD012DF] : reserved space
    volatile uint32 MSTR_56;           //[0x7BD012E0] : EL1_MSTR_56_0
    volatile uint32 MSTR_57;           //[0x7BD012E4] : EL1_MSTR_57_0
    volatile uint32 MSTR_58;           //[0x7BD012E8] : EL1_MSTR_58_0
    volatile uint32 MSTR_59;           //[0x7BD012EC] : EL1_MSTR_59_0
    volatile uint32 RESERVED26[2];           //[0x7BD013F0...0x7BD013F7] : reserved space
    volatile uint32 MSTR_62;           //[0x7BD012F8] : EL1_MSTR_62_0
    volatile uint32 MSTR_63;           //[0x7BD012FC] : EL1_MSTR_63_0
  } rba_Reg_Firewall_El1_Mstr_tst;

  typedef struct {
    volatile uint32 FW_ERROR_STATUS;         //[0x7BD00000] : FW_ERROR_STATUS
    volatile uint32 RESERVED0[3];            //[0x7BD00004...0x7BD0000F] : reserved space
    volatile uint32 FW_EL2_ERROR_STATUS;     //[0x7BD00010] : FW_EL2_ERROR_STATUS
    volatile uint32 FW_EL2_ERROR_TYPE_STATUS;//[0x7BD00014] : FW_EL2_ERROR_TYPE_STATUS
    volatile uint32 FW_EL2_ERROR_ID_STATUS;  //[0x7BD00018] : FW_EL2_ERROR_ID_STATUS
    volatile uint32 FW_EL2_ERROR_ADDR_STATUS;//[0x7BD0001C] : FW_EL2_ERROR_ADDR_STATUS
    volatile uint32 FW_EL1_ERROR_STATUS;     //[0x7BD00020] : FW_EL1_ERROR_STATUS
    volatile uint32 FW_EL1_ERROR_TYPE_STATUS;//[0x7BD00024] : FW_EL1_ERROR_TYPE_STATUS
    volatile uint32 FW_EL1_ERROR_ID_STATUS;  //[0x7BD00028] : FW_EL1_ERROR_ID_STATUS
    volatile uint32 FW_EL1_ERROR_ADDR_STATUS;//[0x7BD0002C] : FW_EL1_ERROR_ADDR_STATUS
    volatile uint32 FW_ECC_PAR_ERROR_STATUS; //[0x7BD00030] : FW_ECC_PAR_ERROR_STATUS
    volatile uint32 FW_ECC_PAR_ERR_ID;       //[0x7BD00034] : FW_ECC_PAR_ERR_ID
    volatile uint32 RESERVED1[50];           //[0x7BD00038...0x7BD000FF] : reserved space
    volatile uint32 FW_CONFIG_REG;           //[0x7BD00100] : FW_CONFIG_REG
    volatile uint32 FW_EL2_CONFIG_REG;       //[0x7BD00104] : FW_EL2_CONFIG_REG
    volatile uint32 FW_EL1_CONFIG_REG;       //[0x7BD00108] : FW_EL1_CONFIG_REG
    volatile uint32 RESERVED2[61];           //[0x7BD0010C...0x7BD001FF] : reserved space
    volatile uint32 EL2_ADDR_START_0;        //[0x7BD00200] : EL2_ADDR_START_0
    volatile uint32 EL2_ADDR_SIZE_0;         //[0x7BD00204] : EL2_ADDR_SIZE_0
    volatile uint32 EL2_VMID_WR_0;           //[0x7BD00208] : EL2_VMID_WR_0
    volatile uint32 EL2_VMID_0_RD_0;         //[0x7BD0020C] : EL2_VMID_0_RD_0
    volatile uint32 EL2_VMID_1_RD_0;         //[0x7BD00210] : EL2_VMID_1_RD_0
    volatile uint32 EL2_VMID_2_RD_0;         //[0x7BD00214] : EL2_VMID_2_RD_0
    volatile uint32 EL2_VMID_3_RD_0;         //[0x7BD00218] : EL2_VMID_3_RD_0
    volatile uint32 EL2_VMID_4_RD_0;         //[0x7BD0021C] : EL2_VMID_4_RD_0
    volatile uint32 EL2_VMID_5_RD_0;         //[0x7BD00220] : EL2_VMID_5_RD_0
    volatile uint32 EL2_REGION_CONF_0;       //[0x7BD00224] : EL2_REGION_CONF_0
    volatile uint32 RESERVED3[6];            //[0x7BD00228...0x7BD0023F] : reserved space
    volatile uint32 EL2_ADDR_START_1;        //[0x7BD00240] : EL2_ADDR_START_1
    volatile uint32 EL2_ADDR_SIZE_1;         //[0x7BD00244] : EL2_ADDR_SIZE_1
    volatile uint32 EL2_VMID_WR_1;           //[0x7BD00248] : EL2_VMID_WR_1
    volatile uint32 EL2_VMID_0_RD_1;         //[0x7BD0024C] : EL2_VMID_0_RD_1
    volatile uint32 EL2_VMID_1_RD_1;         //[0x7BD00250] : EL2_VMID_1_RD_1
    volatile uint32 EL2_VMID_2_RD_1;         //[0x7BD00254] : EL2_VMID_2_RD_1
    volatile uint32 EL2_VMID_3_RD_1;         //[0x7BD00258] : EL2_VMID_3_RD_1
    volatile uint32 EL2_VMID_4_RD_1;         //[0x7BD0025C] : EL2_VMID_4_RD_1
    volatile uint32 EL2_VMID_5_RD_1;         //[0x7BD00260] : EL2_VMID_5_RD_1
    volatile uint32 EL2_REGION_CONF_1;       //[0x7BD00264] : EL2_REGION_CONF_1
    volatile uint32 RESERVED4[6];            //[0x7BD00268...0x7BD0027F] : reserved space
    volatile uint32 EL2_ADDR_START_2;        //[0x7BD00280] : EL2_ADDR_START_2
    volatile uint32 EL2_ADDR_SIZE_2;         //[0x7BD00284] : EL2_ADDR_SIZE_2
    volatile uint32 EL2_VMID_WR_2;           //[0x7BD00288] : EL2_VMID_WR_2
    volatile uint32 EL2_VMID_0_RD_2;         //[0x7BD0028C] : EL2_VMID_0_RD_2
    volatile uint32 EL2_VMID_1_RD_2;         //[0x7BD00290] : EL2_VMID_1_RD_2
    volatile uint32 EL2_VMID_2_RD_2;         //[0x7BD00294] : EL2_VMID_2_RD_2
    volatile uint32 EL2_VMID_3_RD_2;         //[0x7BD00298] : EL2_VMID_3_RD_2
    volatile uint32 EL2_VMID_4_RD_2;         //[0x7BD0029C] : EL2_VMID_4_RD_2
    volatile uint32 EL2_VMID_5_RD_2;         //[0x7BD002A0] : EL2_VMID_5_RD_2
    volatile uint32 EL2_REGION_CONF_2;       //[0x7BD002A4] : EL2_REGION_CONF_2
    volatile uint32 RESERVED5[6];            //[0x7BD002A8...0x7BD002BF] : reserved space
    volatile uint32 EL2_ADDR_START_3;        //[0x7BD002C0] : EL2_ADDR_START_3
    volatile uint32 EL2_ADDR_SIZE_3;         //[0x7BD002C4] : EL2_ADDR_SIZE_3
    volatile uint32 EL2_VMID_WR_3;           //[0x7BD002C8] : EL2_VMID_WR_3
    volatile uint32 EL2_VMID_0_RD_3;         //[0x7BD002CC] : EL2_VMID_0_RD_3
    volatile uint32 EL2_VMID_1_RD_3;         //[0x7BD002D0] : EL2_VMID_1_RD_3
    volatile uint32 EL2_VMID_2_RD_3;         //[0x7BD002D4] : EL2_VMID_2_RD_3
    volatile uint32 EL2_VMID_3_RD_3;         //[0x7BD002D8] : EL2_VMID_3_RD_3
    volatile uint32 EL2_VMID_4_RD_3;         //[0x7BD002DC] : EL2_VMID_4_RD_3
    volatile uint32 EL2_VMID_5_RD_3;         //[0x7BD002E0] : EL2_VMID_5_RD_3
    volatile uint32 EL2_REGION_CONF_3;       //[0x7BD002E4] : EL2_REGION_CONF_3
    volatile uint32 RESERVED6[6];            //[0x7BD002E8...0x7BD002FF] : reserved space
    volatile uint32 EL2_ADDR_START_4;        //[0x7BD00300] : EL2_ADDR_START_4
    volatile uint32 EL2_ADDR_SIZE_4;         //[0x7BD00304] : EL2_ADDR_SIZE_4
    volatile uint32 EL2_VMID_WR_4;           //[0x7BD00308] : EL2_VMID_WR_4
    volatile uint32 EL2_VMID_0_RD_4;         //[0x7BD0030C] : EL2_VMID_0_RD_4
    volatile uint32 EL2_VMID_1_RD_4;         //[0x7BD00310] : EL2_VMID_1_RD_4
    volatile uint32 EL2_VMID_2_RD_4;         //[0x7BD00314] : EL2_VMID_2_RD_4
    volatile uint32 EL2_VMID_3_RD_4;         //[0x7BD00318] : EL2_VMID_3_RD_4
    volatile uint32 EL2_VMID_4_RD_4;         //[0x7BD0031C] : EL2_VMID_4_RD_4
    volatile uint32 EL2_VMID_5_RD_4;         //[0x7BD00320] : EL2_VMID_5_RD_4
    volatile uint32 EL2_REGION_CONF_4;       //[0x7BD00324] : EL2_REGION_CONF_4
    volatile uint32 RESERVED7[6];            //[0x7BD00328...0x7BD0033F] : reserved space
    volatile uint32 EL2_ADDR_START_5;        //[0x7BD00340] : EL2_ADDR_START_5
    volatile uint32 EL2_ADDR_SIZE_5;         //[0x7BD00344] : EL2_ADDR_SIZE_5
    volatile uint32 EL2_VMID_WR_5;           //[0x7BD00348] : EL2_VMID_WR_5
    volatile uint32 EL2_VMID_0_RD_5;         //[0x7BD0034C] : EL2_VMID_0_RD_5
    volatile uint32 EL2_VMID_1_RD_5;         //[0x7BD00350] : EL2_VMID_1_RD_5
    volatile uint32 EL2_VMID_2_RD_5;         //[0x7BD00354] : EL2_VMID_2_RD_5
    volatile uint32 EL2_VMID_3_RD_5;         //[0x7BD00358] : EL2_VMID_3_RD_5
    volatile uint32 EL2_VMID_4_RD_5;         //[0x7BD0035C] : EL2_VMID_4_RD_5
    volatile uint32 EL2_VMID_5_RD_5;         //[0x7BD00360] : EL2_VMID_5_RD_5
    volatile uint32 EL2_REGION_CONF_5;       //[0x7BD00364] : EL2_REGION_CONF_5
    volatile uint32 RESERVED8[6];            //[0x7BD00368...0x7BD0037F] : reserved space
    volatile uint32 EL2_ADDR_START_6;        //[0x7BD00380] : EL2_ADDR_START_6
    volatile uint32 EL2_ADDR_SIZE_6;         //[0x7BD00384] : EL2_ADDR_SIZE_6
    volatile uint32 EL2_VMID_WR_6;           //[0x7BD00388] : EL2_VMID_WR_6
    volatile uint32 EL2_VMID_0_RD_6;         //[0x7BD0038C] : EL2_VMID_0_RD_6
    volatile uint32 EL2_VMID_1_RD_6;         //[0x7BD00390] : EL2_VMID_1_RD_6
    volatile uint32 EL2_VMID_2_RD_6;         //[0x7BD00394] : EL2_VMID_2_RD_6
    volatile uint32 EL2_VMID_3_RD_6;         //[0x7BD00398] : EL2_VMID_3_RD_6
    volatile uint32 EL2_VMID_4_RD_6;         //[0x7BD0039C] : EL2_VMID_4_RD_6
    volatile uint32 EL2_VMID_5_RD_6;         //[0x7BD003A0] : EL2_VMID_5_RD_6
    volatile uint32 EL2_REGION_CONF_6;       //[0x7BD003A4] : EL2_REGION_CONF_6
    volatile uint32 RESERVED9[6];            //[0x7BD003A8...0x7BD003BF] : reserved space
    volatile uint32 EL2_ADDR_START_7;        //[0x7BD003C0] : EL2_ADDR_START_7
    volatile uint32 EL2_ADDR_SIZE_7;         //[0x7BD003C4] : EL2_ADDR_SIZE_7
    volatile uint32 EL2_VMID_WR_7;           //[0x7BD003C8] : EL2_VMID_WR_7
    volatile uint32 EL2_VMID_0_RD_7;         //[0x7BD003CC] : EL2_VMID_0_RD_7
    volatile uint32 EL2_VMID_1_RD_7;         //[0x7BD003D0] : EL2_VMID_1_RD_7
    volatile uint32 EL2_VMID_2_RD_7;         //[0x7BD003D4] : EL2_VMID_2_RD_7
    volatile uint32 EL2_VMID_3_RD_7;         //[0x7BD003D8] : EL2_VMID_3_RD_7
    volatile uint32 EL2_VMID_4_RD_7;         //[0x7BD003DC] : EL2_VMID_4_RD_7
    volatile uint32 EL2_VMID_5_RD_7;         //[0x7BD003E0] : EL2_VMID_5_RD_7
    volatile uint32 EL2_REGION_CONF_7;       //[0x7BD003E4] : EL2_REGION_CONF_7
    volatile uint32 RESERVED10[774];         //[0x7BD003E8...0x7BD00FFF] : reserved space
    volatile rba_Reg_Firewall_El1_Addr_tst EL1_REG[RBA_REG_FIREWALL_MAX_REGIONS];
    volatile uint32 RESERVED18[96];          //[0x7BD01080...0x7BD011FF] : reserved space
    volatile uint32 EL1_MSTR[RBA_REG_FIREWALL_MAX_REGIONS][RBA_REG_FIREWALL_MAX_BUSMASTER];
  } rba_Reg_FIREWALL_tst;

  extern rba_Reg_FIREWALL_tst AESLIGHT0_FIREWALL;
  extern rba_Reg_FIREWALL_tst AESLIGHT1_FIREWALL;
  extern rba_Reg_FIREWALL_tst AESLIGHT2_FIREWALL;
  extern rba_Reg_FIREWALL_tst AESLIGHT3_FIREWALL;
  extern rba_Reg_FIREWALL_tst AIPS0_FIREWALL;
  extern rba_Reg_FIREWALL_tst AIPS1_FIREWALL;
  extern rba_Reg_FIREWALL_tst AIPS2_FIREWALL;
  extern rba_Reg_FIREWALL_tst AIPS3_FIREWALL;
  extern rba_Reg_FIREWALL_tst AIPS4_FIREWALL;
  extern rba_Reg_FIREWALL_tst DAP_FIREWALL;
  extern rba_Reg_FIREWALL_tst DFA_FIREWALL;
  extern rba_Reg_FIREWALL_tst DME_FIREWALL;
  extern rba_Reg_FIREWALL_tst DSPH_FIREWALL;
  extern rba_Reg_FIREWALL_tst GTM_FIREWALL;
  extern rba_Reg_FIREWALL_tst HSM_FIREWALL;
  extern rba_Reg_FIREWALL_tst KITE0_FIREWALL;
  extern rba_Reg_FIREWALL_tst KITE1_FIREWALL;
  extern rba_Reg_FIREWALL_tst KITE2_FIREWALL;
  extern rba_Reg_FIREWALL_tst NVM_FIREWALL;
  extern rba_Reg_FIREWALL_tst OCT_SPI_FIREWALL;
  extern rba_Reg_FIREWALL_tst SYSRAM0_FIREWALL;
  extern rba_Reg_FIREWALL_tst SYSRAM1_FIREWALL;
  extern rba_Reg_FIREWALL_tst TMC0_FIREWALL;
  extern rba_Reg_FIREWALL_tst TMC1_FIREWALL;
  extern rba_Reg_FIREWALL_tst TMC2_FIREWALL;

  extern rba_Reg_FIREWALL_tst* TRBSYS_uCRegister_Firewalls[];
  extern uint32 TRBSYS_uCRegister_FirewallsCnt;

#endif


extern volatile uint32 ECCDFDFKCPROT;
extern uint32 ECCDFDFECCCTL;



#endif
