/******************************************************************************/
/* DISCLAIMER                                                                 */
/* This software is supplied by Renesas Electronics Corporation and is only   */
/* intended for use with Renesas products. No other uses are authorized.This  */
/* software is owned by Renesas Electronics Corporation and is protected      */
/* under all applicable laws, including copyright laws.                       */
/* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES          */
/* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING  */
/* BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR */
/* PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY           */
/* DISCLAIMED.                                                                */
/* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS     */
/* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE       */
/* LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL      */
/* DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS    */
/* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.           */
/* Renesas reserves the right, without notice, to make changes to this        */
/* software and to discontinue the availability of this software.             */
/* By using this software, you agree to the additional terms and conditions   */
/* found by accessing the following link:                                     */
/* http://www.renesas.com/disclaimer                                          */
/*                                                                            */
/* Device     : RH/RH850G3M/R7F701337                                         */
/* File Name  : dr7f701337.dvf.h                                          */
/* Abstract   : Definition of I/O Register without BIT definitions            */
/* History    : V1.10  [Device File version]                                  */
/* Options    : -ghs_pragma_io=off -anonymous=off -indent=4 -structure=on -ty */
/*              pedef=on -def=on -autosar=on -modulearray=on -const=off -bitf */
/*              ield=off -bitsfr=off -share_structure=off -tagname_T=on -df=. */
/*              \dr7f701337.dvf -o=..\output\update\inc_nobit\dr7f701337. */
/*              dvf.h                                                         */
/* Date       : 8/26/2022                                                     */
/* Version    : V1.16.00.02  [df2iodef.exe version]                           */
/* This is a typical example.                                                 */
/*                                                                            */
/******************************************************************************/
#ifndef DR7F701337_DVF_H__
#define DR7F701337_DVF_H__


typedef union
{                                                          /* IOR              */
    uint8  ui8;                                          /* 8-bit Access     */
} R_type0;
typedef union
{                                                          /* IOR              */
    uint32 ui32;                                         /* 32-bit Access    */
    uint16 ui16[2];                                      /* 16-bit Access    */
    uint8  ui8[4];                                       /* 8-bit Access     */
} R_type1;
typedef union
{                                                          /* IOR              */
    uint16 ui16;                                         /* 16-bit Access    */
    uint8  ui8[2];                                       /* 8-bit Access     */
    struct
    {
        union
        {                                                  /* IOR              */
            uint8  ui8;                                  /*  8-bit Access    */
        } LBRP0;
        union
        {                                                  /* IOR              */
            uint8  ui8;                                  /*  8-bit Access    */
        } LBRP1;
    } REGS8;
} R_type2;
typedef union
{                                                          /* IOR              */
    uint16 ui16;                                         /* 16-bit Access    */
    uint8  ui8[2];                                       /* 8-bit Access     */
} R_type3;
typedef union
{                                                          /* IOR              */
    uint32 ui32;                                         /* 32-bit Access    */
    uint8  ui8[4];                                       /* 8-bit Access     */
} R_type4;
typedef union
{                                                          /* IOR              */
    uint32 ui32;                                         /* 32-bit Access    */
    uint16 ui16[2];                                      /* 16-bit Access    */
} R_type5;

/* Module structure */

typedef struct
{                                                          /* Module           */
    uint32 CNT;                                            /* CNT              */
    uint32 PCMD;                                           /* PCMD             */
    uint32 PS;                                             /* PS               */
} R_FLMD;
typedef struct
{                                                          /* Module           */
    uint8  FPMON;                                          /* FPMON            */
    uint8  dummy0[15];                                     /* Reserved         */
    uint8  FASTAT;                                         /* FASTAT           */
    uint8  dummy1[3];                                      /* Reserved         */
    uint8  FAEINT;                                         /* FAEINT           */
    uint8  dummy2[27];                                     /* Reserved         */
    uint32 FSADDR;                                         /* FSADDR           */
    uint32 FEADDR;                                         /* FEADDR           */
    uint8  dummy3[28];                                     /* Reserved         */
    uint16 FCURAME;                                        /* FCURAME          */
    uint8  dummy4[2];                                      /* Reserved         */
    uint16 FRAMMCR;                                        /* FRAMMCR          */
    uint8  dummy5[6];                                      /* Reserved         */
    uint16 FPROTDR0;                                       /* FPROTDR0         */
    uint8  dummy6[2];                                      /* Reserved         */
    uint32 FPROTCR0;                                       /* FPROTCR0         */
    uint32 FPROTCR1;                                       /* FPROTCR1         */
    uint8  dummy7[20];                                     /* Reserved         */
    uint32 FSTATR;                                         /* FSTATR           */
    uint16 FENTRYR;                                        /* FENTRYR          */
    uint8  dummy8[6];                                      /* Reserved         */
    uint16 FSUINITR;                                       /* FSUINITR         */
    uint8  dummy9[2];                                      /* Reserved         */
    uint8  FLKSTAT;                                        /* FLKSTAT          */
    uint8  dummy10[3];                                     /* Reserved         */
    uint32 FRFSTEADR;                                      /* FRFSTEADR        */
    uint8  FRTSTAT;                                        /* FRTSTAT          */
    uint8  dummy11[3];                                     /* Reserved         */
    uint8  FRTEINT;                                        /* FRTEINT          */
    uint8  dummy12[3];                                     /* Reserved         */
    uint16 FCMDR;                                          /* FCMDR            */
    uint8  dummy13[14];                                    /* Reserved         */
    uint16 FRAMECCR;                                       /* FRAMECCR         */
    uint8  dummy14[14];                                    /* Reserved         */
    uint16 FPESTAT;                                        /* FPESTAT          */
    uint8  dummy15[2];                                     /* Reserved         */
    uint16 FCNFPRGCNT;                                     /* FCNFPRGCNT       */
    uint8  dummy16[10];                                    /* Reserved         */
    uint8  FBCCNT;                                         /* FBCCNT           */
    uint8  dummy17[3];                                     /* Reserved         */
    uint8  FBCSTAT;                                        /* FBCSTAT          */
    uint8  dummy18[3];                                     /* Reserved         */
    uint32 FPSADDR;                                        /* FPSADDR          */
    uint8  dummy19[4];                                     /* Reserved         */
    uint16 FCPSR;                                          /* FCPSR            */
    uint8  dummy20[2];                                     /* Reserved         */
    uint16 FPCKAR;                                         /* FPCKAR           */
    uint8  dummy21[26];                                    /* Reserved         */
    uint16 FECCEMON;                                       /* FECCEMON         */
    uint8  dummy22[2];                                     /* Reserved         */
    uint16 FECCTMD;                                        /* FECCTMD          */
    uint8  dummy23[2];                                     /* Reserved         */
    uint16 FDMYECC;                                        /* FDMYECC          */
} R_FACI0;
typedef struct
{                                                          /* Module           */
    R_type0 CTL;                                           /* CTL              */
    uint8  dummy24[3];                                     /* Reserved         */
    uint16 EN;                                             /* EN               */
    uint8  dummy25[6];                                     /* Reserved         */
    R_type0 ENL;                                           /* ENL              */
} R_DNFA2;
typedef struct
{                                                          /* Module           */
    R_type0 CTL;                                           /* CTL              */
    uint8  dummy26[3];                                     /* Reserved         */
    uint16 EN;                                             /* EN               */
    uint8  dummy27[6];                                     /* Reserved         */
    R_type0 ENL;                                           /* ENL              */
} R_DNFA3;
typedef struct
{                                                          /* Module           */
    R_type0 CTL;                                           /* CTL              */
    uint8  dummy28[3];                                     /* Reserved         */
    uint16 EN;                                             /* EN               */
    uint8  dummy29[6];                                     /* Reserved         */
    R_type0 ENL;                                           /* ENL              */
} R_DNFA5;
typedef struct
{                                                          /* Module           */
    R_type0 CTL;                                           /* CTL              */
    uint8  dummy30[3];                                     /* Reserved         */
    uint16 EN;                                             /* EN               */
    uint8  dummy31[6];                                     /* Reserved         */
    R_type0 ENL;                                           /* ENL              */
} R_DNFA7;
typedef struct
{                                                          /* Module           */
    R_type0 CTL0;                                          /* CTL0             */
    uint8  dummy32[3];                                     /* Reserved         */
    R_type0 CTL1;                                          /* CTL1             */
    uint8  dummy33[3];                                     /* Reserved         */
    R_type0 CTL2;                                          /* CTL2             */
    uint8  dummy34[3];                                     /* Reserved         */
    R_type0 CTL3;                                          /* CTL3             */
    uint8  dummy35[3];                                     /* Reserved         */
    R_type0 CTL4;                                          /* CTL4             */
    uint8  dummy36[3];                                     /* Reserved         */
    R_type0 CTL5;                                          /* CTL5             */
    uint8  dummy37[3];                                     /* Reserved         */
    R_type0 CTL6;                                          /* CTL6             */
    uint8  dummy38[3];                                     /* Reserved         */
    R_type0 CTL7;                                          /* CTL7             */
} R_FCLA0;
typedef struct
{                                                          /* Module           */
    R_type0 CTL0;                                          /* CTL0             */
} R_FCLA1;
typedef struct
{                                                          /* Module           */
    R_type0 CTL0;                                          /* CTL0             */
    uint8  dummy39[3];                                     /* Reserved         */
    R_type0 CTL1;                                          /* CTL1             */
} R_FCLA2;
typedef struct
{                                                          /* Module           */
    R_type0 CTL0;                                          /* CTL0             */
    uint8  dummy40[3];                                     /* Reserved         */
    R_type0 CTL1;                                          /* CTL1             */
} R_FCLA3;
typedef struct
{                                                          /* Module           */
    R_type0 CTL0;                                          /* CTL0             */
    uint8  dummy41[3];                                     /* Reserved         */
    R_type0 CTL1;                                          /* CTL1             */
    uint8  dummy42[3];                                     /* Reserved         */
    R_type0 CTL2;                                          /* CTL2             */
    uint8  dummy43[3];                                     /* Reserved         */
    R_type0 CTL3;                                          /* CTL3             */
} R_FCLA5;
typedef struct
{                                                          /* Module           */
    R_type1 PROT00;                                        /* PROT00           */
    R_type1 SPID00;                                        /* SPID00           */
    R_type1 PROT01;                                        /* PROT01           */
    R_type1 SPID01;                                        /* SPID01           */
    uint8  dummy44[16];                                    /* Reserved         */
    R_type1 PROT04;                                        /* PROT04           */
    R_type1 SPID04;                                        /* SPID04           */
    R_type1 PROT05;                                        /* PROT05           */
    R_type1 SPID05;                                        /* SPID05           */
} R_FSGD5A;
typedef struct
{                                                          /* Module           */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy45[3];                                     /* Reserved         */
    uint32 STAT;                                           /* STAT             */
    uint8  dummy46[4];                                     /* Reserved         */
    uint32 TYPE;                                           /* TYPE             */
} R_ERRSLV5A;
typedef struct
{                                                          /* Module           */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy47[3];                                     /* Reserved         */
    uint32 STAT;                                           /* STAT             */
    uint8  dummy48[4];                                     /* Reserved         */
    uint32 TYPE;                                           /* TYPE             */
} R_ERRSLV5AI;
typedef struct
{                                                          /* Module           */
    uint32 CTL;                                            /* CTL              */
    uint32 TMC;                                            /* TMC              */
    uint32 TRC;                                            /* TRC              */
    uint32 TED;                                            /* TED              */
    uint32 EAD0;                                           /* EAD0             */
} R_ECCCSIH0;
typedef struct
{                                                          /* Module           */
    uint32 CTL;                                            /* CTL              */
    uint32 TMC;                                            /* TMC              */
    uint32 TRC;                                            /* TRC              */
    uint32 TED;                                            /* TED              */
    uint32 EAD0;                                           /* EAD0             */
} R_ECCCSIH2;
typedef struct
{                                                          /* Module           */
    uint32 CTL;                                            /* CTL              */
    uint32 TMC;                                            /* TMC              */
    uint32 TRC;                                            /* TRC              */
    uint32 TED;                                            /* TED              */
    uint32 EAD0;                                           /* EAD0             */
} R_ECCTTCAN0;
typedef struct
{                                                          /* Module           */
    uint32 CTL;                                            /* CTL              */
    uint32 TMC;                                            /* TMC              */
    uint32 TRC;                                            /* TRC              */
    uint32 TED;                                            /* TED              */
    uint32 EAD0;                                           /* EAD0             */
} R_ECCCSIH1;
typedef struct
{                                                          /* Module           */
    uint32 CTL;                                            /* CTL              */
    uint32 TMC;                                            /* TMC              */
    uint32 TRC;                                            /* TRC              */
    uint32 TED;                                            /* TED              */
    uint32 EAD0;                                           /* EAD0             */
} R_ECCMCAN0;
typedef struct
{                                                          /* Module           */
    R_type0 CTL0;                                          /* CTL0             */
    uint8  dummy49[15];                                    /* Reserved         */
    uint32 CTL1;                                           /* CTL1             */
    uint16 CTL2;                                           /* CTL2             */
    uint8  dummy50[4074];                                  /* Reserved         */
    uint32 MCTL1;                                          /* MCTL1            */
    uint32 MCTL2;                                          /* MCTL2            */
    uint32 TX0W;                                           /* TX0W             */
    uint16 TX0H;                                           /* TX0H             */
    uint8  dummy51[2];                                     /* Reserved         */
    uint32 RX0W;                                           /* RX0W             */
    uint16 RX0H;                                           /* RX0H             */
    uint8  dummy52[2];                                     /* Reserved         */
    uint32 MRWP0;                                          /* MRWP0            */
    uint32 STR0;                                           /* STR0             */
    uint16 STCR0;                                          /* STCR0            */
    uint8  dummy53[30];                                    /* Reserved         */
    uint16 MCTL0;                                          /* MCTL0            */
    uint8  dummy54[2];                                     /* Reserved         */
    uint32 CFG0;                                           /* CFG0             */
    uint32 CFG1;                                           /* CFG1             */
    uint32 CFG2;                                           /* CFG2             */
    uint32 CFG3;                                           /* CFG3             */
    uint32 CFG4;                                           /* CFG4             */
    uint32 CFG5;                                           /* CFG5             */
    uint32 CFG6;                                           /* CFG6             */
    uint32 CFG7;                                           /* CFG7             */
    uint8  dummy55[4];                                     /* Reserved         */
    uint16 BRS0;                                           /* BRS0             */
    uint8  dummy56[2];                                     /* Reserved         */
    uint16 BRS1;                                           /* BRS1             */
    uint8  dummy57[2];                                     /* Reserved         */
    uint16 BRS2;                                           /* BRS2             */
    uint8  dummy58[2];                                     /* Reserved         */
    uint16 BRS3;                                           /* BRS3             */
} R_CSIH1;
typedef struct
{                                                          /* Module           */
    uint32 CTL;                                            /* CTL              */
    uint32 TCTL0;                                          /* TCTL0            */
    uint32 TCTL1;                                          /* TCTL1            */
    uint32 TCTL2;                                          /* TCTL2            */
    uint32 TCTL3;                                          /* TCTL3            */
    uint32 TCTL4;                                          /* TCTL4            */
    uint32 TCTL5;                                          /* TCTL5            */
    uint32 TCTL6;                                          /* TCTL6            */
    uint32 TCTL7;                                          /* TCTL7            */
    uint32 TTX0;                                           /* TTX0             */
    uint32 TTX1;                                           /* TTX1             */
    uint32 TTX2;                                           /* TTX2             */
    uint32 TTX3;                                           /* TTX3             */
    uint32 TTX4;                                           /* TTX4             */
    uint32 TTX5;                                           /* TTX5             */
    uint32 TTX6;                                           /* TTX6             */
    uint32 TTX7;                                           /* TTX7             */
    uint32 RX;                                             /* RX               */
    uint32 TCNT0;                                          /* TCNT0            */
    uint32 TCNT1;                                          /* TCNT1            */
    uint32 TCNT2;                                          /* TCNT2            */
    uint32 TCNT3;                                          /* TCNT3            */
    uint32 TCNT4;                                          /* TCNT4            */
    uint32 TCNT5;                                          /* TCNT5            */
    uint32 TCNT6;                                          /* TCNT6            */
    uint32 TCNT7;                                          /* TCNT7            */
    uint32 STR0;                                           /* STR0             */
    uint32 STR1;                                           /* STR1             */
    uint32 STC;                                            /* STC              */
} R_PMMA1;
typedef struct
{                                                          /* Module           */
    uint8  dummy59[1];                                     /* Reserved         */
    uint8  LWBR;                                           /* LWBR             */
    R_type2 LBRP01;                                        /* LBRP01           */
    uint8  LSTC;                                           /* LSTC             */
    uint8  dummy60[3];                                     /* Reserved         */
    uint8  LMD;                                            /* LMD              */
    uint8  LBFC;                                           /* LBFC             */
    uint8  LSC;                                            /* LSC              */
    uint8  LWUP;                                           /* LWUP             */
    uint8  LIE;                                            /* LIE              */
    uint8  LEDE;                                           /* LEDE             */
    uint8  LCUC;                                           /* LCUC             */
    uint8  dummy61[1];                                     /* Reserved         */
    uint8  LTRC;                                           /* LTRC             */
    uint8  LMST;                                           /* LMST             */
    uint8  LST;                                            /* LST              */
    uint8  LEST;                                           /* LEST             */
    uint8  LDFC;                                           /* LDFC             */
    uint8  LIDB;                                           /* LIDB             */
    uint8  LCBR;                                           /* LCBR             */
    uint8  LUDB0;                                          /* LUDB0            */
    uint8  LDBR1;                                          /* LDBR1            */
    uint8  LDBR2;                                          /* LDBR2            */
    uint8  LDBR3;                                          /* LDBR3            */
    uint8  LDBR4;                                          /* LDBR4            */
    uint8  LDBR5;                                          /* LDBR5            */
    uint8  LDBR6;                                          /* LDBR6            */
    uint8  LDBR7;                                          /* LDBR7            */
    uint8  LDBR8;                                          /* LDBR8            */
    uint8  LUOER;                                          /* LUOER            */
    uint8  LUOR1;                                          /* LUOR1            */
    uint8  dummy62[2];                                     /* Reserved         */
    R_type3 LUTDR;                                         /* LUTDR            */
    R_type3 LURDR;                                         /* LURDR            */
    R_type3 LUWTDR;                                        /* LUWTDR           */
} R_RLN31;
typedef struct
{                                                          /* Module           */
    R_type1 TSPC;                                          /* TSPC             */
    R_type1 TSC;                                           /* TSC              */
    uint8  dummy63[8];                                     /* Reserved         */
    R_type1 CC;                                            /* CC               */
    R_type1 BRP;                                           /* BRP              */
    R_type1 IDE;                                           /* IDE              */
    R_type1 MDC;                                           /* MDC              */
    R_type1 SPCT;                                          /* SPCT             */
    R_type1 MST;                                           /* MST              */
    R_type1 CS;                                            /* CS               */
    R_type1 CSC;                                           /* CSC              */
    R_type1 SRTS;                                          /* SRTS             */
    uint32 SRXD;                                           /* SRXD             */
    R_type1 CPL;                                           /* CPL              */
    R_type1 ML;                                            /* ML               */
    R_type1 FRTS;                                          /* FRTS             */
    uint32 FRXD;                                           /* FRXD             */
    uint8  dummy64[184];                                   /* Reserved         */
} R_RSENT0;
typedef struct
{                                                          /* Module           */
    R_type1 TSPC;                                          /* TSPC             */
    R_type1 TSC;                                           /* TSC              */
    uint8  dummy65[8];                                     /* Reserved         */
    R_type1 CC;                                            /* CC               */
    R_type1 BRP;                                           /* BRP              */
    R_type1 IDE;                                           /* IDE              */
    R_type1 MDC;                                           /* MDC              */
    R_type1 SPCT;                                          /* SPCT             */
    R_type1 MST;                                           /* MST              */
    R_type1 CS;                                            /* CS               */
    R_type1 CSC;                                           /* CSC              */
    R_type1 SRTS;                                          /* SRTS             */
    uint32 SRXD;                                           /* SRXD             */
    R_type1 CPL;                                           /* CPL              */
    R_type1 ML;                                            /* ML               */
    R_type1 FRTS;                                          /* FRTS             */
    uint32 FRXD;                                           /* FRXD             */
    uint8  dummy66[184];                                   /* Reserved         */
} R_RSENT1;
typedef struct
{                                                          /* Module           */
    R_type1 TSPC;                                          /* TSPC             */
    R_type1 TSC;                                           /* TSC              */
    uint8  dummy67[8];                                     /* Reserved         */
    R_type1 CC;                                            /* CC               */
    R_type1 BRP;                                           /* BRP              */
    R_type1 IDE;                                           /* IDE              */
    R_type1 MDC;                                           /* MDC              */
    R_type1 SPCT;                                          /* SPCT             */
    R_type1 MST;                                           /* MST              */
    R_type1 CS;                                            /* CS               */
    R_type1 CSC;                                           /* CSC              */
    R_type1 SRTS;                                          /* SRTS             */
    uint32 SRXD;                                           /* SRXD             */
    R_type1 CPL;                                           /* CPL              */
    R_type1 ML;                                            /* ML               */
    R_type1 FRTS;                                          /* FRTS             */
    uint32 FRXD;                                           /* FRXD             */
    uint8  dummy68[184];                                   /* Reserved         */
} R_RSENT2;
typedef struct
{                                                          /* Module           */
    R_type1 TSPC;                                          /* TSPC             */
    R_type1 TSC;                                           /* TSC              */
    uint8  dummy69[8];                                     /* Reserved         */
    R_type1 CC;                                            /* CC               */
    R_type1 BRP;                                           /* BRP              */
    R_type1 IDE;                                           /* IDE              */
    R_type1 MDC;                                           /* MDC              */
    R_type1 SPCT;                                          /* SPCT             */
    R_type1 MST;                                           /* MST              */
    R_type1 CS;                                            /* CS               */
    R_type1 CSC;                                           /* CSC              */
    R_type1 SRTS;                                          /* SRTS             */
    uint32 SRXD;                                           /* SRXD             */
    R_type1 CPL;                                           /* CPL              */
    R_type1 ML;                                            /* ML               */
    R_type1 FRTS;                                          /* FRTS             */
    uint32 FRXD;                                           /* FRXD             */
} R_RSENT3;
typedef struct
{                                                          /* Module           */
    uint8  R0;                                             /* R0               */
    uint8  dummy70[3];                                     /* Reserved         */
    uint8  R1;                                             /* R1               */
    uint8  dummy71[3];                                     /* Reserved         */
    uint8  R2;                                             /* R2               */
} R_SINT;
typedef struct
{                                                          /* Module           */
    R_type1 CREL;                                          /* CREL             */
    R_type1 ENDN;                                          /* ENDN             */
    uint8  dummy72[4];                                     /* Reserved         */
    R_type1 DBTP;                                          /* DBTP             */
    R_type1 TEST;                                          /* TEST             */
    R_type1 RWD;                                           /* RWD              */
    R_type1 CCCR;                                          /* CCCR             */
    R_type1 NBTP;                                          /* NBTP             */
    R_type1 TSCC;                                          /* TSCC             */
    R_type1 TSCV;                                          /* TSCV             */
    R_type1 TOCC;                                          /* TOCC             */
    R_type1 TOCV;                                          /* TOCV             */
    uint8  dummy73[16];                                    /* Reserved         */
    R_type1 ECR;                                           /* ECR              */
    R_type1 PSR;                                           /* PSR              */
    R_type1 TDCR;                                          /* TDCR             */
    uint8  dummy74[4];                                     /* Reserved         */
    R_type1 IR;                                            /* IR               */
    R_type1 IE;                                            /* IE               */
    R_type1 ILS;                                           /* ILS              */
    R_type1 ILE;                                           /* ILE              */
    uint8  dummy75[32];                                    /* Reserved         */
    R_type1 GFC;                                           /* GFC              */
    R_type1 SIDFC;                                         /* SIDFC            */
    R_type1 XIDFC;                                         /* XIDFC            */
    uint8  dummy76[4];                                     /* Reserved         */
    R_type1 XIDAM;                                         /* XIDAM            */
    R_type1 HPMS;                                          /* HPMS             */
    R_type1 NDAT1;                                         /* NDAT1            */
    R_type1 NDAT2;                                         /* NDAT2            */
    R_type1 RXF0C;                                         /* RXF0C            */
    R_type1 RXF0S;                                         /* RXF0S            */
    R_type1 RXF0A;                                         /* RXF0A            */
    R_type1 RXBC;                                          /* RXBC             */
    R_type1 RXF1C;                                         /* RXF1C            */
    R_type1 RXF1S;                                         /* RXF1S            */
    R_type1 RXF1A;                                         /* RXF1A            */
    R_type1 RXESC;                                         /* RXESC            */
    R_type1 TXBC;                                          /* TXBC             */
    R_type1 TXFQS;                                         /* TXFQS            */
    R_type1 TXESC;                                         /* TXESC            */
    R_type1 TXBRP;                                         /* TXBRP            */
    R_type1 TXBAR;                                         /* TXBAR            */
    R_type1 TXBCR;                                         /* TXBCR            */
    R_type1 TXBTO;                                         /* TXBTO            */
    R_type1 TXBCF;                                         /* TXBCF            */
    R_type1 TXBTIE;                                        /* TXBTIE           */
    R_type1 TXBCIE;                                        /* TXBCIE           */
    uint8  dummy77[8];                                     /* Reserved         */
    R_type1 TXEFC;                                         /* TXEFC            */
    R_type1 TXEFS;                                         /* TXEFS            */
    R_type1 TXEFA;                                         /* TXEFA            */
    uint8  dummy78[4];                                     /* Reserved         */
    R_type1 TTTMC;                                         /* TTTMC            */
    R_type1 TTRMC;                                         /* TTRMC            */
    R_type1 TTOCF;                                         /* TTOCF            */
    R_type1 TTMLM;                                         /* TTMLM            */
    R_type1 TURCF;                                         /* TURCF            */
    R_type1 TTOCN;                                         /* TTOCN            */
    R_type1 TTGTP;                                         /* TTGTP            */
    R_type1 TTTMK;                                         /* TTTMK            */
    R_type1 TTIR;                                          /* TTIR             */
    R_type1 TTIE;                                          /* TTIE             */
    R_type1 TTILS;                                         /* TTILS            */
    R_type1 TTOST;                                         /* TTOST            */
    R_type1 TURNA;                                         /* TURNA            */
    R_type1 TTLGT;                                         /* TTLGT            */
    R_type1 TTCTC;                                         /* TTCTC            */
    R_type1 TTCPT;                                         /* TTCPT            */
    R_type1 TTCSM;                                         /* TTCSM            */
} R_MTTCAN0;
typedef struct
{                                                          /* Module           */
    uint32 CIN;                                            /* CIN              */
    uint32 COUT;                                           /* COUT             */
    uint8  dummy79[24];                                    /* Reserved         */
    uint8  CTL;                                            /* CTL              */
} R_DCRB0;
typedef struct
{                                                          /* Module           */
    uint32 ESET;                                           /* ESET             */
    uint32 ECLR;                                           /* ECLR             */
    uint32 ESSTR0;                                         /* ESSTR0           */
    uint32 ESSTR1;                                         /* ESSTR1           */
    uint32 ESSTR2;                                         /* ESSTR2           */
    uint32 PCMD0;                                          /* PCMD0            */
} R_ECMM0;
typedef struct
{                                                          /* Module           */
    uint32 ESET;                                           /* ESET             */
    uint32 ECLR;                                           /* ECLR             */
    uint32 ESSTR0;                                         /* ESSTR0           */
    uint32 ESSTR1;                                         /* ESSTR1           */
    uint32 ESSTR2;                                         /* ESSTR2           */
    uint32 PCMD0;                                          /* PCMD0            */
} R_ECMC0;
typedef struct
{                                                          /* Module           */
    uint32 EPCFG;                                          /* EPCFG            */
    uint32 MICFG0;                                         /* MICFG0           */
    uint32 MICFG1;                                         /* MICFG1           */
    uint32 MICFG2;                                         /* MICFG2           */
    uint32 NMICFG0;                                        /* NMICFG0          */
    uint32 NMICFG1;                                        /* NMICFG1          */
    uint32 NMICFG2;                                        /* NMICFG2          */
    uint32 IRCFG0;                                         /* IRCFG0           */
    uint32 IRCFG1;                                         /* IRCFG1           */
    uint32 IRCFG2;                                         /* IRCFG2           */
    uint32 EMK0;                                           /* EMK0             */
    uint32 EMK1;                                           /* EMK1             */
    uint32 EMK2;                                           /* EMK2             */
    uint32 ESSTC0;                                         /* ESSTC0           */
    uint32 ESSTC1;                                         /* ESSTC1           */
    uint32 ESSTC2;                                         /* ESSTC2           */
    uint32 PCMD1;                                          /* PCMD1            */
    uint8  PS;                                             /* PS               */
    uint8  dummy80[3];                                     /* Reserved         */
    uint32 PE0;                                            /* PE0              */
    uint32 PE1;                                            /* PE1              */
    uint32 PE2;                                            /* PE2              */
    uint32 DTMCTL;                                         /* DTMCTL           */
    uint16 DTMR;                                           /* DTMR             */
    uint8  dummy81[2];                                     /* Reserved         */
    uint32 DTMCMP;                                         /* DTMCMP           */
    uint32 DTMCFG0;                                        /* DTMCFG0          */
    uint32 DTMCFG1;                                        /* DTMCFG1          */
    uint32 DTMCFG2;                                        /* DTMCFG2          */
    uint32 DTMCFG3;                                        /* DTMCFG3          */
    uint32 DTMCFG4;                                        /* DTMCFG4          */
    uint32 DTMCFG5;                                        /* DTMCFG5          */
    uint32 EOCCFG;                                         /* EOCCFG           */
    uint32 PEM;                                            /* PEM              */
} R_ECM0;
typedef struct
{                                                          /* Module           */
    uint32 TRGPREMUX0;                                     /* TRGPREMUX0       */
    uint8  dummy82[12];                                    /* Reserved         */
    uint32 TRGMUX0;                                        /* TRGMUX0          */
    uint8  dummy83[4];                                     /* Reserved         */
    uint32 EDGSEL0;                                        /* EDGSEL0          */
    uint8  dummy84[4];                                     /* Reserved         */
    uint32 ENP2TIM0;                                       /* ENP2TIM0         */
    uint32 ENP2TIM1;                                       /* ENP2TIM1         */
    uint32 ENHIZDTM;                                       /* ENHIZDTM         */
} R_PIC2C;
typedef struct
{                                                          /* Module           */
    R_type0 CTL0;                                          /* CTL0             */
    uint8  dummy85[15];                                    /* Reserved         */
    uint32 CTL1;                                           /* CTL1             */
    uint16 CTL2;                                           /* CTL2             */
    uint8  dummy86[4074];                                  /* Reserved         */
    uint32 MCTL1;                                          /* MCTL1            */
    uint32 MCTL2;                                          /* MCTL2            */
    uint32 TX0W;                                           /* TX0W             */
    uint16 TX0H;                                           /* TX0H             */
    uint8  dummy87[2];                                     /* Reserved         */
    uint32 RX0W;                                           /* RX0W             */
    uint16 RX0H;                                           /* RX0H             */
    uint8  dummy88[2];                                     /* Reserved         */
    uint32 MRWP0;                                          /* MRWP0            */
    uint32 STR0;                                           /* STR0             */
    uint16 STCR0;                                          /* STCR0            */
    uint8  dummy89[30];                                    /* Reserved         */
    uint16 MCTL0;                                          /* MCTL0            */
    uint8  dummy90[2];                                     /* Reserved         */
    uint32 CFG0;                                           /* CFG0             */
    uint32 CFG1;                                           /* CFG1             */
    uint32 CFG2;                                           /* CFG2             */
    uint32 CFG3;                                           /* CFG3             */
    uint32 CFG4;                                           /* CFG4             */
    uint32 CFG5;                                           /* CFG5             */
    uint32 CFG6;                                           /* CFG6             */
    uint32 CFG7;                                           /* CFG7             */
    uint8  dummy91[4];                                     /* Reserved         */
    uint16 BRS0;                                           /* BRS0             */
    uint8  dummy92[2];                                     /* Reserved         */
    uint16 BRS1;                                           /* BRS1             */
    uint8  dummy93[2];                                     /* Reserved         */
    uint16 BRS2;                                           /* BRS2             */
    uint8  dummy94[2];                                     /* Reserved         */
    uint16 BRS3;                                           /* BRS3             */
} R_CSIH0;
typedef struct
{                                                          /* Module           */
    uint32 CTL;                                            /* CTL              */
    uint32 TCTL0;                                          /* TCTL0            */
    uint32 TCTL1;                                          /* TCTL1            */
    uint32 TCTL2;                                          /* TCTL2            */
    uint32 TCTL3;                                          /* TCTL3            */
    uint32 TCTL4;                                          /* TCTL4            */
    uint32 TCTL5;                                          /* TCTL5            */
    uint32 TCTL6;                                          /* TCTL6            */
    uint32 TCTL7;                                          /* TCTL7            */
    uint32 TTX0;                                           /* TTX0             */
    uint32 TTX1;                                           /* TTX1             */
    uint32 TTX2;                                           /* TTX2             */
    uint32 TTX3;                                           /* TTX3             */
    uint32 TTX4;                                           /* TTX4             */
    uint32 TTX5;                                           /* TTX5             */
    uint32 TTX6;                                           /* TTX6             */
    uint32 TTX7;                                           /* TTX7             */
    uint32 RX;                                             /* RX               */
    uint32 TCNT0;                                          /* TCNT0            */
    uint32 TCNT1;                                          /* TCNT1            */
    uint32 TCNT2;                                          /* TCNT2            */
    uint32 TCNT3;                                          /* TCNT3            */
    uint32 TCNT4;                                          /* TCNT4            */
    uint32 TCNT5;                                          /* TCNT5            */
    uint32 TCNT6;                                          /* TCNT6            */
    uint32 TCNT7;                                          /* TCNT7            */
    uint32 STR0;                                           /* STR0             */
    uint32 STR1;                                           /* STR1             */
    uint32 STC;                                            /* STC              */
} R_PMMA0;
typedef struct
{                                                          /* Module           */
    R_type0 CTL0;                                          /* CTL0             */
    uint8  dummy95[15];                                    /* Reserved         */
    uint32 CTL1;                                           /* CTL1             */
    uint16 CTL2;                                           /* CTL2             */
    uint8  dummy96[4074];                                  /* Reserved         */
    uint32 MCTL1;                                          /* MCTL1            */
    uint32 MCTL2;                                          /* MCTL2            */
    uint32 TX0W;                                           /* TX0W             */
    uint16 TX0H;                                           /* TX0H             */
    uint8  dummy97[2];                                     /* Reserved         */
    uint32 RX0W;                                           /* RX0W             */
    uint16 RX0H;                                           /* RX0H             */
    uint8  dummy98[2];                                     /* Reserved         */
    uint32 MRWP0;                                          /* MRWP0            */
    uint32 STR0;                                           /* STR0             */
    uint16 STCR0;                                          /* STCR0            */
    uint8  dummy99[30];                                    /* Reserved         */
    uint16 MCTL0;                                          /* MCTL0            */
    uint8  dummy100[2];                                    /* Reserved         */
    uint32 CFG0;                                           /* CFG0             */
    uint32 CFG1;                                           /* CFG1             */
    uint32 CFG2;                                           /* CFG2             */
    uint32 CFG3;                                           /* CFG3             */
    uint32 CFG4;                                           /* CFG4             */
    uint32 CFG5;                                           /* CFG5             */
    uint32 CFG6;                                           /* CFG6             */
    uint32 CFG7;                                           /* CFG7             */
    uint8  dummy101[4];                                    /* Reserved         */
    uint16 BRS0;                                           /* BRS0             */
    uint8  dummy102[2];                                    /* Reserved         */
    uint16 BRS1;                                           /* BRS1             */
    uint8  dummy103[2];                                    /* Reserved         */
    uint16 BRS2;                                           /* BRS2             */
    uint8  dummy104[2];                                    /* Reserved         */
    uint16 BRS3;                                           /* BRS3             */
} R_CSIH2;
typedef struct
{                                                          /* Module           */
    uint32 CTL;                                            /* CTL              */
    uint32 TCTL0;                                          /* TCTL0            */
    uint32 TCTL1;                                          /* TCTL1            */
    uint32 TCTL2;                                          /* TCTL2            */
    uint32 TCTL3;                                          /* TCTL3            */
    uint32 TCTL4;                                          /* TCTL4            */
    uint32 TCTL5;                                          /* TCTL5            */
    uint32 TCTL6;                                          /* TCTL6            */
    uint32 TCTL7;                                          /* TCTL7            */
    uint32 TTX0;                                           /* TTX0             */
    uint32 TTX1;                                           /* TTX1             */
    uint32 TTX2;                                           /* TTX2             */
    uint32 TTX3;                                           /* TTX3             */
    uint32 TTX4;                                           /* TTX4             */
    uint32 TTX5;                                           /* TTX5             */
    uint32 TTX6;                                           /* TTX6             */
    uint32 TTX7;                                           /* TTX7             */
    uint32 RX;                                             /* RX               */
    uint32 TCNT0;                                          /* TCNT0            */
    uint32 TCNT1;                                          /* TCNT1            */
    uint32 TCNT2;                                          /* TCNT2            */
    uint32 TCNT3;                                          /* TCNT3            */
    uint32 TCNT4;                                          /* TCNT4            */
    uint32 TCNT5;                                          /* TCNT5            */
    uint32 TCNT6;                                          /* TCNT6            */
    uint32 TCNT7;                                          /* TCNT7            */
    uint32 STR0;                                           /* STR0             */
    uint32 STR1;                                           /* STR1             */
    uint32 STC;                                            /* STC              */
} R_PMMA2;
typedef struct
{                                                          /* Module           */
    uint8  dummy105[1];                                    /* Reserved         */
    uint8  LWBR;                                           /* LWBR             */
    R_type2 LBRP01;                                        /* LBRP01           */
    uint8  LSTC;                                           /* LSTC             */
    uint8  dummy106[3];                                    /* Reserved         */
    uint8  LMD;                                            /* LMD              */
    uint8  LBFC;                                           /* LBFC             */
    uint8  LSC;                                            /* LSC              */
    uint8  LWUP;                                           /* LWUP             */
    uint8  LIE;                                            /* LIE              */
    uint8  LEDE;                                           /* LEDE             */
    uint8  LCUC;                                           /* LCUC             */
    uint8  dummy107[1];                                    /* Reserved         */
    uint8  LTRC;                                           /* LTRC             */
    uint8  LMST;                                           /* LMST             */
    uint8  LST;                                            /* LST              */
    uint8  LEST;                                           /* LEST             */
    uint8  LDFC;                                           /* LDFC             */
    uint8  LIDB;                                           /* LIDB             */
    uint8  LCBR;                                           /* LCBR             */
    uint8  LUDB0;                                          /* LUDB0            */
    uint8  LDBR1;                                          /* LDBR1            */
    uint8  LDBR2;                                          /* LDBR2            */
    uint8  LDBR3;                                          /* LDBR3            */
    uint8  LDBR4;                                          /* LDBR4            */
    uint8  LDBR5;                                          /* LDBR5            */
    uint8  LDBR6;                                          /* LDBR6            */
    uint8  LDBR7;                                          /* LDBR7            */
    uint8  LDBR8;                                          /* LDBR8            */
    uint8  LUOER;                                          /* LUOER            */
    uint8  LUOR1;                                          /* LUOR1            */
    uint8  dummy108[2];                                    /* Reserved         */
    R_type3 LUTDR;                                         /* LUTDR            */
    R_type3 LURDR;                                         /* LURDR            */
    R_type3 LUWTDR;                                        /* LUWTDR           */
} R_RLN30;
typedef struct
{                                                          /* Module           */
    R_type4 CKSEL;                                         /* CKSEL            */
    uint8  dummy109[12];                                   /* Reserved         */
    R_type4 TS;                                            /* TS               */
    R_type4 TT;                                            /* TT               */
    R_type4 CSTR;                                          /* CSTR             */
    uint8  dummy110[4];                                    /* Reserved         */
    uint32 STR;                                            /* STR              */
    uint32 STC;                                            /* STC              */
    uint8  dummy111[8];                                    /* Reserved         */
    R_type4 IS;                                            /* IS               */
    R_type4 RM;                                            /* RM               */
    uint8  dummy112[8];                                    /* Reserved         */
    uint32 CNT0L;                                          /* CNT0L            */
    uint32 CNT0H;                                          /* CNT0H            */
    uint8  dummy113[8];                                    /* Reserved         */
    uint32 CMP0AL;                                         /* CMP0AL           */
    uint32 CMP0AH;                                         /* CMP0AH           */
    uint32 CMP0BL;                                         /* CMP0BL           */
    uint32 CMP0BH;                                         /* CMP0BH           */
    uint32 CMP0CL;                                         /* CMP0CL           */
    uint32 CMP0CH;                                         /* CMP0CH           */
    uint32 CMP0DL;                                         /* CMP0DL           */
    uint32 CMP0DH;                                         /* CMP0DH           */
    uint32 CNT1;                                           /* CNT1             */
    uint8  dummy114[12];                                   /* Reserved         */
    uint32 CMP1A;                                          /* CMP1A            */
    uint32 CMP1B;                                          /* CMP1B            */
    uint32 CMP1C;                                          /* CMP1C            */
    uint32 CMP1D;                                          /* CMP1D            */
    uint32 CNT2;                                           /* CNT2             */
    uint8  dummy115[12];                                   /* Reserved         */
    uint32 CMP2A;                                          /* CMP2A            */
    uint32 CMP2B;                                          /* CMP2B            */
    uint32 CMP2C;                                          /* CMP2C            */
    uint32 CMP2D;                                          /* CMP2D            */
    uint32 CNT3;                                           /* CNT3             */
    uint8  dummy116[12];                                   /* Reserved         */
    uint32 CMP3A;                                          /* CMP3A            */
    uint32 CMP3B;                                          /* CMP3B            */
    uint32 CMP3C;                                          /* CMP3C            */
    uint32 CMP3D;                                          /* CMP3D            */
} R_STM0;
typedef struct
{                                                          /* Module           */
    R_type1 PROT00;                                        /* PROT00           */
    R_type1 SPID00;                                        /* SPID00           */
    R_type1 PROT01;                                        /* PROT01           */
    R_type1 SPID01;                                        /* SPID01           */
    R_type1 PROT02;                                        /* PROT02           */
    R_type1 SPID02;                                        /* SPID02           */
    R_type1 PROT03;                                        /* PROT03           */
    R_type1 SPID03;                                        /* SPID03           */
    R_type1 PROT04;                                        /* PROT04           */
    R_type1 SPID04;                                        /* SPID04           */
    R_type1 PROT05;                                        /* PROT05           */
    R_type1 SPID05;                                        /* SPID05           */
    R_type1 PROT06;                                        /* PROT06           */
    R_type1 SPID06;                                        /* SPID06           */
    R_type1 PROT07;                                        /* PROT07           */
    R_type1 SPID07;                                        /* SPID07           */
    uint8  dummy117[16];                                   /* Reserved         */
    R_type1 PROT10;                                        /* PROT10           */
    R_type1 SPID10;                                        /* SPID10           */
    R_type1 PROT11;                                        /* PROT11           */
    R_type1 SPID11;                                        /* SPID11           */
} R_FSGD2A;
typedef struct
{                                                          /* Module           */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy118[3];                                    /* Reserved         */
    uint32 STAT;                                           /* STAT             */
    uint8  dummy119[4];                                    /* Reserved         */
    uint32 TYPE;                                           /* TYPE             */
} R_ERRSLV2;
typedef struct
{                                                          /* Module           */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy120[3];                                    /* Reserved         */
    uint32 STAT;                                           /* STAT             */
    uint8  dummy121[4];                                    /* Reserved         */
    uint32 TYPE;                                           /* TYPE             */
} R_ERRSLV2AI;
typedef struct
{                                                          /* Module           */
    uint32 GTMREV;                                         /* GTMREV           */
    uint32 GTMRST;                                         /* GTMRST           */
    uint32 GTMCTRL;                                        /* GTMCTRL          */
    uint32 GTMAEIADDRXPT;                                  /* GTMAEIADDRXPT    */
    uint32 GTMIRQNOTIFY;                                   /* GTMIRQNOTIFY     */
    uint32 GTMIRQEN;                                       /* GTMIRQEN         */
    uint32 GTMIRQFORCINT;                                  /* GTMIRQFORCINT    */
    uint32 GTMIRQMODE;                                     /* GTMIRQMODE       */
    uint32 GTMEIRQEN;                                      /* GTMEIRQEN        */
    uint32 GTMHWCONF;                                      /* GTMHWCONF        */
    uint8  dummy122[8];                                    /* Reserved         */
    uint32 GTMBRIDGEMODE;                                  /* GTMBRIDGEMODE    */
    uint32 GTMBRIDGEPTR1;                                  /* GTMBRIDGEPTR1    */
    uint32 GTMBRIDGEPTR2;                                  /* GTMBRIDGEPTR2    */
    uint8  dummy123[4];                                    /* Reserved         */
    uint32 GTMTIM0AUXINSRC;                                /* GTMTIM0AUXINSRC  */
    uint32 GTMTIM1AUXINSRC;                                /* GTMTIM1AUXINSRC  */
    uint8  dummy124[20];                                   /* Reserved         */
    uint32 GTMEXTCAPEN0;                                   /* GTMEXTCAPEN0     */
    uint8  dummy125[56];                                   /* Reserved         */
    uint32 GTMATOM0OUT;                                    /* GTMATOM0OUT      */
    uint8  dummy126[100];                                  /* Reserved         */
    uint32 TBUCHEN;                                        /* TBUCHEN          */
    uint32 TBU0CTRL;                                       /* TBU0CTRL         */
    uint32 TBU0BASE;                                       /* TBU0BASE         */
    uint32 TBU1CTRL;                                       /* TBU1CTRL         */
    uint32 TBU1BASE;                                       /* TBU1BASE         */
    uint8  dummy127[108];                                  /* Reserved         */
    uint32 MONSTATUS;                                      /* MONSTATUS        */
    uint32 MONACTIVITY0;                                   /* MONACTIVITY0     */
    uint8  dummy128[4];                                    /* Reserved         */
    uint32 MONACTIVITYMCS0;                                /* MONACTIVITYMCS0  */
    uint8  dummy129[112];                                  /* Reserved         */
    uint32 CMPEN;                                          /* CMPEN            */
    uint32 CMPIRQNOTIFY;                                   /* CMPIRQNOTIFY     */
    uint32 CMPIRQEN;                                       /* CMPIRQEN         */
    uint32 CMPIRQFORCINT;                                  /* CMPIRQFORCINT    */
    uint32 CMPIRQMODE;                                     /* CMPIRQMODE       */
    uint32 CMPEIRQEN;                                      /* CMPEIRQEN        */
    uint8  dummy130[104];                                  /* Reserved         */
    uint32 ARUACCESS;                                      /* ARUACCESS        */
    uint32 ARUDATAH;                                       /* ARUDATAH         */
    uint32 ARUDATAL;                                       /* ARUDATAL         */
    uint32 ARUDBGACCESS0;                                  /* ARUDBGACCESS0    */
    uint32 ARUDBGDATA0H;                                   /* ARUDBGDATA0H     */
    uint32 ARUDBGDATA0L;                                   /* ARUDBGDATA0L     */
    uint32 ARUDBGACCESS1;                                  /* ARUDBGACCESS1    */
    uint32 ARUDBGDATA1H;                                   /* ARUDBGDATA1H     */
    uint32 ARUDBGDATA1L;                                   /* ARUDBGDATA1L     */
    uint32 ARUIRQNOTIFY;                                   /* ARUIRQNOTIFY     */
    uint32 ARUIRQEN;                                       /* ARUIRQEN         */
    uint32 ARUIRQFORCINT;                                  /* ARUIRQFORCINT    */
    uint32 ARUIRQMODE;                                     /* ARUIRQMODE       */
    uint32 ARUCADDREND;                                    /* ARUCADDREND      */
    uint8  dummy131[72];                                   /* Reserved         */
    uint32 CMUCLKEN;                                       /* CMUCLKEN         */
    uint32 CMUGCLKNUM;                                     /* CMUGCLKNUM       */
    uint32 CMUGCLKDEN;                                     /* CMUGCLKDEN       */
    uint32 CMUCLK0CTRL;                                    /* CMUCLK0CTRL      */
    uint32 CMUCLK1CTRL;                                    /* CMUCLK1CTRL      */
    uint32 CMUCLK2CTRL;                                    /* CMUCLK2CTRL      */
    uint32 CMUCLK3CTRL;                                    /* CMUCLK3CTRL      */
    uint32 CMUCLK4CTRL;                                    /* CMUCLK4CTRL      */
    uint32 CMUCLK5CTRL;                                    /* CMUCLK5CTRL      */
    uint32 CMUCLK6CTRL;                                    /* CMUCLK6CTRL      */
    uint32 CMUCLK7CTRL;                                    /* CMUCLK7CTRL      */
    uint8  dummy132[28];                                   /* Reserved         */
    uint32 CMUGLBCTRL;                                     /* CMUGLBCTRL       */
    uint8  dummy133[692];                                  /* Reserved         */
    uint32 ICMIRQG0;                                       /* ICMIRQG0         */
    uint8  dummy134[4];                                    /* Reserved         */
    uint32 ICMIRQG2;                                       /* ICMIRQG2         */
    uint8  dummy135[4];                                    /* Reserved         */
    uint32 ICMIRQG4;                                       /* ICMIRQG4         */
    uint8  dummy136[16];                                   /* Reserved         */
    uint32 ICMIRQG9;                                       /* ICMIRQG9         */
    uint8  dummy137[8];                                    /* Reserved         */
    uint32 ICMIRQGMEI;                                     /* ICMIRQGMEI       */
    uint8  dummy138[4];                                    /* Reserved         */
    uint32 ICMIRQGCEI1;                                    /* ICMIRQGCEI1      */
    uint8  dummy139[4];                                    /* Reserved         */
    uint32 ICMIRQGCEI3;                                    /* ICMIRQGCEI3      */
    uint8  dummy140[4];                                    /* Reserved         */
    uint32 ICMIRQGMCS0CI;                                  /* ICMIRQGMCS0CI    */
    uint8  dummy141[24];                                   /* Reserved         */
    uint32 ICMIRQGMCS0CEI;                                 /* ICMIRQGMCS0CEI   */
    uint8  dummy142[2456];                                 /* Reserved         */
    uint32 TIM00GPR0;                                      /* TIM00GPR0        */
    uint32 TIM00GPR1;                                      /* TIM00GPR1        */
    uint32 TIM00CNT;                                       /* TIM00CNT         */
    uint32 TIM00ECNT;                                      /* TIM00ECNT        */
    uint32 TIM00CNTS;                                      /* TIM00CNTS        */
    uint32 TIM00TDUC;                                      /* TIM00TDUC        */
    uint32 TIM00TDUV;                                      /* TIM00TDUV        */
    uint32 TIM00FLTRE;                                     /* TIM00FLTRE       */
    uint32 TIM00FLTFE;                                     /* TIM00FLTFE       */
    uint32 TIM00CTRL;                                      /* TIM00CTRL        */
    uint32 TIM00ECTRL;                                     /* TIM00ECTRL       */
    uint32 TIM00IRQNOTIFY;                                 /* TIM00IRQNOTIFY   */
    uint32 TIM00IRQEN;                                     /* TIM00IRQEN       */
    uint32 TIM00IRQFORCINT;                                /* TIM00IRQFORCINT  */
    uint32 TIM00IRQMODE;                                   /* TIM00IRQMODE     */
    uint32 TIM00EIRQEN;                                    /* TIM00EIRQEN      */
    uint8  dummy143[52];                                   /* Reserved         */
    uint32 TIM0INPVAL;                                     /* TIM0INPVAL       */
    uint32 TIM0INSRC;                                      /* TIM0INSRC        */
    uint32 TIM0RST;                                        /* TIM0RST          */
    uint32 TIM01GPR0;                                      /* TIM01GPR0        */
    uint32 TIM01GPR1;                                      /* TIM01GPR1        */
    uint32 TIM01CNT;                                       /* TIM01CNT         */
    uint32 TIM01ECNT;                                      /* TIM01ECNT        */
    uint32 TIM01CNTS;                                      /* TIM01CNTS        */
    uint32 TIM01TDUC;                                      /* TIM01TDUC        */
    uint32 TIM01TDUV;                                      /* TIM01TDUV        */
    uint32 TIM01FLTRE;                                     /* TIM01FLTRE       */
    uint32 TIM01FLTFE;                                     /* TIM01FLTFE       */
    uint32 TIM01CTRL;                                      /* TIM01CTRL        */
    uint32 TIM01ECTRL;                                     /* TIM01ECTRL       */
    uint32 TIM01IRQNOTIFY;                                 /* TIM01IRQNOTIFY   */
    uint32 TIM01IRQEN;                                     /* TIM01IRQEN       */
    uint32 TIM01IRQFORCINT;                                /* TIM01IRQFORCINT  */
    uint32 TIM01IRQMODE;                                   /* TIM01IRQMODE     */
    uint32 TIM01EIRQEN;                                    /* TIM01EIRQEN      */
    uint8  dummy144[64];                                   /* Reserved         */
    uint32 TIM02GPR0;                                      /* TIM02GPR0        */
    uint32 TIM02GPR1;                                      /* TIM02GPR1        */
    uint32 TIM02CNT;                                       /* TIM02CNT         */
    uint32 TIM02ECNT;                                      /* TIM02ECNT        */
    uint32 TIM02CNTS;                                      /* TIM02CNTS        */
    uint32 TIM02TDUC;                                      /* TIM02TDUC        */
    uint32 TIM02TDUV;                                      /* TIM02TDUV        */
    uint32 TIM02FLTRE;                                     /* TIM02FLTRE       */
    uint32 TIM02FLTFE;                                     /* TIM02FLTFE       */
    uint32 TIM02CTRL;                                      /* TIM02CTRL        */
    uint32 TIM02ECTRL;                                     /* TIM02ECTRL       */
    uint32 TIM02IRQNOTIFY;                                 /* TIM02IRQNOTIFY   */
    uint32 TIM02IRQEN;                                     /* TIM02IRQEN       */
    uint32 TIM02IRQFORCINT;                                /* TIM02IRQFORCINT  */
    uint32 TIM02IRQMODE;                                   /* TIM02IRQMODE     */
    uint32 TIM02EIRQEN;                                    /* TIM02EIRQEN      */
    uint8  dummy145[64];                                   /* Reserved         */
    uint32 TIM03GPR0;                                      /* TIM03GPR0        */
    uint32 TIM03GPR1;                                      /* TIM03GPR1        */
    uint32 TIM03CNT;                                       /* TIM03CNT         */
    uint32 TIM03ECNT;                                      /* TIM03ECNT        */
    uint32 TIM03CNTS;                                      /* TIM03CNTS        */
    uint32 TIM03TDUC;                                      /* TIM03TDUC        */
    uint32 TIM03TDUV;                                      /* TIM03TDUV        */
    uint32 TIM03FLTRE;                                     /* TIM03FLTRE       */
    uint32 TIM03FLTFE;                                     /* TIM03FLTFE       */
    uint32 TIM03CTRL;                                      /* TIM03CTRL        */
    uint32 TIM03ECTRL;                                     /* TIM03ECTRL       */
    uint32 TIM03IRQNOTIFY;                                 /* TIM03IRQNOTIFY   */
    uint32 TIM03IRQEN;                                     /* TIM03IRQEN       */
    uint32 TIM03IRQFORCINT;                                /* TIM03IRQFORCINT  */
    uint32 TIM03IRQMODE;                                   /* TIM03IRQMODE     */
    uint32 TIM03EIRQEN;                                    /* TIM03EIRQEN      */
    uint8  dummy146[64];                                   /* Reserved         */
    uint32 TIM04GPR0;                                      /* TIM04GPR0        */
    uint32 TIM04GPR1;                                      /* TIM04GPR1        */
    uint32 TIM04CNT;                                       /* TIM04CNT         */
    uint32 TIM04ECNT;                                      /* TIM04ECNT        */
    uint32 TIM04CNTS;                                      /* TIM04CNTS        */
    uint32 TIM04TDUC;                                      /* TIM04TDUC        */
    uint32 TIM04TDUV;                                      /* TIM04TDUV        */
    uint32 TIM04FLTRE;                                     /* TIM04FLTRE       */
    uint32 TIM04FLTFE;                                     /* TIM04FLTFE       */
    uint32 TIM04CTRL;                                      /* TIM04CTRL        */
    uint32 TIM04ECTRL;                                     /* TIM04ECTRL       */
    uint32 TIM04IRQNOTIFY;                                 /* TIM04IRQNOTIFY   */
    uint32 TIM04IRQEN;                                     /* TIM04IRQEN       */
    uint32 TIM04IRQFORCINT;                                /* TIM04IRQFORCINT  */
    uint32 TIM04IRQMODE;                                   /* TIM04IRQMODE     */
    uint32 TIM04EIRQEN;                                    /* TIM04EIRQEN      */
    uint8  dummy147[64];                                   /* Reserved         */
    uint32 TIM05GPR0;                                      /* TIM05GPR0        */
    uint32 TIM05GPR1;                                      /* TIM05GPR1        */
    uint32 TIM05CNT;                                       /* TIM05CNT         */
    uint32 TIM05ECNT;                                      /* TIM05ECNT        */
    uint32 TIM05CNTS;                                      /* TIM05CNTS        */
    uint32 TIM05TDUC;                                      /* TIM05TDUC        */
    uint32 TIM05TDUV;                                      /* TIM05TDUV        */
    uint32 TIM05FLTRE;                                     /* TIM05FLTRE       */
    uint32 TIM05FLTFE;                                     /* TIM05FLTFE       */
    uint32 TIM05CTRL;                                      /* TIM05CTRL        */
    uint32 TIM05ECTRL;                                     /* TIM05ECTRL       */
    uint32 TIM05IRQNOTIFY;                                 /* TIM05IRQNOTIFY   */
    uint32 TIM05IRQEN;                                     /* TIM05IRQEN       */
    uint32 TIM05IRQFORCINT;                                /* TIM05IRQFORCINT  */
    uint32 TIM05IRQMODE;                                   /* TIM05IRQMODE     */
    uint32 TIM05EIRQEN;                                    /* TIM05EIRQEN      */
    uint8  dummy148[64];                                   /* Reserved         */
    uint32 TIM06GPR0;                                      /* TIM06GPR0        */
    uint32 TIM06GPR1;                                      /* TIM06GPR1        */
    uint32 TIM06CNT;                                       /* TIM06CNT         */
    uint32 TIM06ECNT;                                      /* TIM06ECNT        */
    uint32 TIM06CNTS;                                      /* TIM06CNTS        */
    uint32 TIM06TDUC;                                      /* TIM06TDUC        */
    uint32 TIM06TDUV;                                      /* TIM06TDUV        */
    uint32 TIM06FLTRE;                                     /* TIM06FLTRE       */
    uint32 TIM06FLTFE;                                     /* TIM06FLTFE       */
    uint32 TIM06CTRL;                                      /* TIM06CTRL        */
    uint32 TIM06ECTRL;                                     /* TIM06ECTRL       */
    uint32 TIM06IRQNOTIFY;                                 /* TIM06IRQNOTIFY   */
    uint32 TIM06IRQEN;                                     /* TIM06IRQEN       */
    uint32 TIM06IRQFORCINT;                                /* TIM06IRQFORCINT  */
    uint32 TIM06IRQMODE;                                   /* TIM06IRQMODE     */
    uint32 TIM06EIRQEN;                                    /* TIM06EIRQEN      */
    uint8  dummy149[64];                                   /* Reserved         */
    uint32 TIM07GPR0;                                      /* TIM07GPR0        */
    uint32 TIM07GPR1;                                      /* TIM07GPR1        */
    uint32 TIM07CNT;                                       /* TIM07CNT         */
    uint32 TIM07ECNT;                                      /* TIM07ECNT        */
    uint32 TIM07CNTS;                                      /* TIM07CNTS        */
    uint32 TIM07TDUC;                                      /* TIM07TDUC        */
    uint32 TIM07TDUV;                                      /* TIM07TDUV        */
    uint32 TIM07FLTRE;                                     /* TIM07FLTRE       */
    uint32 TIM07FLTFE;                                     /* TIM07FLTFE       */
    uint32 TIM07CTRL;                                      /* TIM07CTRL        */
    uint32 TIM07ECTRL;                                     /* TIM07ECTRL       */
    uint32 TIM07IRQNOTIFY;                                 /* TIM07IRQNOTIFY   */
    uint32 TIM07IRQEN;                                     /* TIM07IRQEN       */
    uint32 TIM07IRQFORCINT;                                /* TIM07IRQFORCINT  */
    uint32 TIM07IRQMODE;                                   /* TIM07IRQMODE     */
    uint32 TIM07EIRQEN;                                    /* TIM07EIRQEN      */
    uint8  dummy150[1088];                                 /* Reserved         */
    uint32 TIM10GPR0;                                      /* TIM10GPR0        */
    uint32 TIM10GPR1;                                      /* TIM10GPR1        */
    uint32 TIM10CNT;                                       /* TIM10CNT         */
    uint32 TIM10ECNT;                                      /* TIM10ECNT        */
    uint32 TIM10CNTS;                                      /* TIM10CNTS        */
    uint32 TIM10TDUC;                                      /* TIM10TDUC        */
    uint32 TIM10TDUV;                                      /* TIM10TDUV        */
    uint32 TIM10FLTRE;                                     /* TIM10FLTRE       */
    uint32 TIM10FLTFE;                                     /* TIM10FLTFE       */
    uint32 TIM10CTRL;                                      /* TIM10CTRL        */
    uint32 TIM10ECTRL;                                     /* TIM10ECTRL       */
    uint32 TIM10IRQNOTIFY;                                 /* TIM10IRQNOTIFY   */
    uint32 TIM10IRQEN;                                     /* TIM10IRQEN       */
    uint32 TIM10IRQFORCINT;                                /* TIM10IRQFORCINT  */
    uint32 TIM10IRQMODE;                                   /* TIM10IRQMODE     */
    uint32 TIM10EIRQEN;                                    /* TIM10EIRQEN      */
    uint8  dummy151[52];                                   /* Reserved         */
    uint32 TIM1INPVAL;                                     /* TIM1INPVAL       */
    uint32 TIM1INSRC;                                      /* TIM1INSRC        */
    uint32 TIM1RST;                                        /* TIM1RST          */
    uint32 TIM11GPR0;                                      /* TIM11GPR0        */
    uint32 TIM11GPR1;                                      /* TIM11GPR1        */
    uint32 TIM11CNT;                                       /* TIM11CNT         */
    uint32 TIM11ECNT;                                      /* TIM11ECNT        */
    uint32 TIM11CNTS;                                      /* TIM11CNTS        */
    uint32 TIM11TDUC;                                      /* TIM11TDUC        */
    uint32 TIM11TDUV;                                      /* TIM11TDUV        */
    uint32 TIM11FLTRE;                                     /* TIM11FLTRE       */
    uint32 TIM11FLTFE;                                     /* TIM11FLTFE       */
    uint32 TIM11CTRL;                                      /* TIM11CTRL        */
    uint32 TIM11ECTRL;                                     /* TIM11ECTRL       */
    uint32 TIM11IRQNOTIFY;                                 /* TIM11IRQNOTIFY   */
    uint32 TIM11IRQEN;                                     /* TIM11IRQEN       */
    uint32 TIM11IRQFORCINT;                                /* TIM11IRQFORCINT  */
    uint32 TIM11IRQMODE;                                   /* TIM11IRQMODE     */
    uint32 TIM11EIRQEN;                                    /* TIM11EIRQEN      */
    uint8  dummy152[64];                                   /* Reserved         */
    uint32 TIM12GPR0;                                      /* TIM12GPR0        */
    uint32 TIM12GPR1;                                      /* TIM12GPR1        */
    uint32 TIM12CNT;                                       /* TIM12CNT         */
    uint32 TIM12ECNT;                                      /* TIM12ECNT        */
    uint32 TIM12CNTS;                                      /* TIM12CNTS        */
    uint32 TIM12TDUC;                                      /* TIM12TDUC        */
    uint32 TIM12TDUV;                                      /* TIM12TDUV        */
    uint32 TIM12FLTRE;                                     /* TIM12FLTRE       */
    uint32 TIM12FLTFE;                                     /* TIM12FLTFE       */
    uint32 TIM12CTRL;                                      /* TIM12CTRL        */
    uint32 TIM12ECTRL;                                     /* TIM12ECTRL       */
    uint32 TIM12IRQNOTIFY;                                 /* TIM12IRQNOTIFY   */
    uint32 TIM12IRQEN;                                     /* TIM12IRQEN       */
    uint32 TIM12IRQFORCINT;                                /* TIM12IRQFORCINT  */
    uint32 TIM12IRQMODE;                                   /* TIM12IRQMODE     */
    uint32 TIM12EIRQEN;                                    /* TIM12EIRQEN      */
    uint8  dummy153[64];                                   /* Reserved         */
    uint32 TIM13GPR0;                                      /* TIM13GPR0        */
    uint32 TIM13GPR1;                                      /* TIM13GPR1        */
    uint32 TIM13CNT;                                       /* TIM13CNT         */
    uint32 TIM13ECNT;                                      /* TIM13ECNT        */
    uint32 TIM13CNTS;                                      /* TIM13CNTS        */
    uint32 TIM13TDUC;                                      /* TIM13TDUC        */
    uint32 TIM13TDUV;                                      /* TIM13TDUV        */
    uint32 TIM13FLTRE;                                     /* TIM13FLTRE       */
    uint32 TIM13FLTFE;                                     /* TIM13FLTFE       */
    uint32 TIM13CTRL;                                      /* TIM13CTRL        */
    uint32 TIM13ECTRL;                                     /* TIM13ECTRL       */
    uint32 TIM13IRQNOTIFY;                                 /* TIM13IRQNOTIFY   */
    uint32 TIM13IRQEN;                                     /* TIM13IRQEN       */
    uint32 TIM13IRQFORCINT;                                /* TIM13IRQFORCINT  */
    uint32 TIM13IRQMODE;                                   /* TIM13IRQMODE     */
    uint32 TIM13EIRQEN;                                    /* TIM13EIRQEN      */
    uint8  dummy154[64];                                   /* Reserved         */
    uint32 TIM14GPR0;                                      /* TIM14GPR0        */
    uint32 TIM14GPR1;                                      /* TIM14GPR1        */
    uint32 TIM14CNT;                                       /* TIM14CNT         */
    uint32 TIM14ECNT;                                      /* TIM14ECNT        */
    uint32 TIM14CNTS;                                      /* TIM14CNTS        */
    uint32 TIM14TDUC;                                      /* TIM14TDUC        */
    uint32 TIM14TDUV;                                      /* TIM14TDUV        */
    uint32 TIM14FLTRE;                                     /* TIM14FLTRE       */
    uint32 TIM14FLTFE;                                     /* TIM14FLTFE       */
    uint32 TIM14CTRL;                                      /* TIM14CTRL        */
    uint32 TIM14ECTRL;                                     /* TIM14ECTRL       */
    uint32 TIM14IRQNOTIFY;                                 /* TIM14IRQNOTIFY   */
    uint32 TIM14IRQEN;                                     /* TIM14IRQEN       */
    uint32 TIM14IRQFORCINT;                                /* TIM14IRQFORCINT  */
    uint32 TIM14IRQMODE;                                   /* TIM14IRQMODE     */
    uint32 TIM14EIRQEN;                                    /* TIM14EIRQEN      */
    uint8  dummy155[64];                                   /* Reserved         */
    uint32 TIM15GPR0;                                      /* TIM15GPR0        */
    uint32 TIM15GPR1;                                      /* TIM15GPR1        */
    uint32 TIM15CNT;                                       /* TIM15CNT         */
    uint32 TIM15ECNT;                                      /* TIM15ECNT        */
    uint32 TIM15CNTS;                                      /* TIM15CNTS        */
    uint32 TIM15TDUC;                                      /* TIM15TDUC        */
    uint32 TIM15TDUV;                                      /* TIM15TDUV        */
    uint32 TIM15FLTRE;                                     /* TIM15FLTRE       */
    uint32 TIM15FLTFE;                                     /* TIM15FLTFE       */
    uint32 TIM15CTRL;                                      /* TIM15CTRL        */
    uint32 TIM15ECTRL;                                     /* TIM15ECTRL       */
    uint32 TIM15IRQNOTIFY;                                 /* TIM15IRQNOTIFY   */
    uint32 TIM15IRQEN;                                     /* TIM15IRQEN       */
    uint32 TIM15IRQFORCINT;                                /* TIM15IRQFORCINT  */
    uint32 TIM15IRQMODE;                                   /* TIM15IRQMODE     */
    uint32 TIM15EIRQEN;                                    /* TIM15EIRQEN      */
    uint8  dummy156[64];                                   /* Reserved         */
    uint32 TIM16GPR0;                                      /* TIM16GPR0        */
    uint32 TIM16GPR1;                                      /* TIM16GPR1        */
    uint32 TIM16CNT;                                       /* TIM16CNT         */
    uint32 TIM16ECNT;                                      /* TIM16ECNT        */
    uint32 TIM16CNTS;                                      /* TIM16CNTS        */
    uint32 TIM16TDUC;                                      /* TIM16TDUC        */
    uint32 TIM16TDUV;                                      /* TIM16TDUV        */
    uint32 TIM16FLTRE;                                     /* TIM16FLTRE       */
    uint32 TIM16FLTFE;                                     /* TIM16FLTFE       */
    uint32 TIM16CTRL;                                      /* TIM16CTRL        */
    uint32 TIM16ECTRL;                                     /* TIM16ECTRL       */
    uint32 TIM16IRQNOTIFY;                                 /* TIM16IRQNOTIFY   */
    uint32 TIM16IRQEN;                                     /* TIM16IRQEN       */
    uint32 TIM16IRQFORCINT;                                /* TIM16IRQFORCINT  */
    uint32 TIM16IRQMODE;                                   /* TIM16IRQMODE     */
    uint32 TIM16EIRQEN;                                    /* TIM16EIRQEN      */
    uint8  dummy157[64];                                   /* Reserved         */
    uint32 TIM17GPR0;                                      /* TIM17GPR0        */
    uint32 TIM17GPR1;                                      /* TIM17GPR1        */
    uint32 TIM17CNT;                                       /* TIM17CNT         */
    uint32 TIM17ECNT;                                      /* TIM17ECNT        */
    uint32 TIM17CNTS;                                      /* TIM17CNTS        */
    uint32 TIM17TDUC;                                      /* TIM17TDUC        */
    uint32 TIM17TDUV;                                      /* TIM17TDUV        */
    uint32 TIM17FLTRE;                                     /* TIM17FLTRE       */
    uint32 TIM17FLTFE;                                     /* TIM17FLTFE       */
    uint32 TIM17CTRL;                                      /* TIM17CTRL        */
    uint32 TIM17ECTRL;                                     /* TIM17ECTRL       */
    uint32 TIM17IRQNOTIFY;                                 /* TIM17IRQNOTIFY   */
    uint32 TIM17IRQEN;                                     /* TIM17IRQEN       */
    uint32 TIM17IRQFORCINT;                                /* TIM17IRQFORCINT  */
    uint32 TIM17IRQMODE;                                   /* TIM17IRQMODE     */
    uint32 TIM17EIRQEN;                                    /* TIM17EIRQEN      */
    uint8  dummy158[46144];                                /* Reserved         */
    uint32 ATOM00RDADDR;                                   /* ATOM00RDADDR     */
    uint32 ATOM00CTRL;                                     /* ATOM00CTRL       */
    uint32 ATOM00SR0;                                      /* ATOM00SR0        */
    uint32 ATOM00SR1;                                      /* ATOM00SR1        */
    uint32 ATOM00CM0;                                      /* ATOM00CM0        */
    uint32 ATOM00CM1;                                      /* ATOM00CM1        */
    uint32 ATOM00CN0;                                      /* ATOM00CN0        */
    uint32 ATOM00STAT;                                     /* ATOM00STAT       */
    uint32 ATOM00IRQNOTIFY;                                /* ATOM00IRQNOTIFY  */
    uint32 ATOM00IRQEN;                                    /* ATOM00IRQEN      */
    uint32 ATOM00IRQFORCINT;                               /* ATOM00IRQFORCINT */
    uint32 ATOM00IRQMODE;                                  /* ATOM00IRQMODE    */
    uint8  dummy159[16];                                   /* Reserved         */
    uint32 ATOM0AGCGLBCTRL;                                /* ATOM0AGCGLBCTRL  */
    uint32 ATOM0AGCENDISCTRL;                              /* ATOM0AGCENDISCTRL */
    uint32 ATOM0AGCENDISSTAT;                              /* ATOM0AGCENDISSTAT */
    uint32 ATOM0AGCACTTB;                                  /* ATOM0AGCACTTB    */
    uint32 ATOM0AGCOUTENCTRL;                              /* ATOM0AGCOUTENCTRL */
    uint32 ATOM0AGCOUTENSTAT;                              /* ATOM0AGCOUTENSTAT */
    uint32 ATOM0AGCFUPDCTRL;                               /* ATOM0AGCFUPDCTRL */
    uint32 ATOM0AGCINTTRIG;                                /* ATOM0AGCINTTRIG  */
    uint8  dummy160[32];                                   /* Reserved         */
    uint32 ATOM01RDADDR;                                   /* ATOM01RDADDR     */
    uint32 ATOM01CTRL;                                     /* ATOM01CTRL       */
    uint32 ATOM01SR0;                                      /* ATOM01SR0        */
    uint32 ATOM01SR1;                                      /* ATOM01SR1        */
    uint32 ATOM01CM0;                                      /* ATOM01CM0        */
    uint32 ATOM01CM1;                                      /* ATOM01CM1        */
    uint32 ATOM01CN0;                                      /* ATOM01CN0        */
    uint32 ATOM01STAT;                                     /* ATOM01STAT       */
    uint32 ATOM01IRQNOTIFY;                                /* ATOM01IRQNOTIFY  */
    uint32 ATOM01IRQEN;                                    /* ATOM01IRQEN      */
    uint32 ATOM01IRQFORCINT;                               /* ATOM01IRQFORCINT */
    uint32 ATOM01IRQMODE;                                  /* ATOM01IRQMODE    */
    uint8  dummy161[80];                                   /* Reserved         */
    uint32 ATOM02RDADDR;                                   /* ATOM02RDADDR     */
    uint32 ATOM02CTRL;                                     /* ATOM02CTRL       */
    uint32 ATOM02SR0;                                      /* ATOM02SR0        */
    uint32 ATOM02SR1;                                      /* ATOM02SR1        */
    uint32 ATOM02CM0;                                      /* ATOM02CM0        */
    uint32 ATOM02CM1;                                      /* ATOM02CM1        */
    uint32 ATOM02CN0;                                      /* ATOM02CN0        */
    uint32 ATOM02STAT;                                     /* ATOM02STAT       */
    uint32 ATOM02IRQNOTIFY;                                /* ATOM02IRQNOTIFY  */
    uint32 ATOM02IRQEN;                                    /* ATOM02IRQEN      */
    uint32 ATOM02IRQFORCINT;                               /* ATOM02IRQFORCINT */
    uint32 ATOM02IRQMODE;                                  /* ATOM02IRQMODE    */
    uint8  dummy162[80];                                   /* Reserved         */
    uint32 ATOM03RDADDR;                                   /* ATOM03RDADDR     */
    uint32 ATOM03CTRL;                                     /* ATOM03CTRL       */
    uint32 ATOM03SR0;                                      /* ATOM03SR0        */
    uint32 ATOM03SR1;                                      /* ATOM03SR1        */
    uint32 ATOM03CM0;                                      /* ATOM03CM0        */
    uint32 ATOM03CM1;                                      /* ATOM03CM1        */
    uint32 ATOM03CN0;                                      /* ATOM03CN0        */
    uint32 ATOM03STAT;                                     /* ATOM03STAT       */
    uint32 ATOM03IRQNOTIFY;                                /* ATOM03IRQNOTIFY  */
    uint32 ATOM03IRQEN;                                    /* ATOM03IRQEN      */
    uint32 ATOM03IRQFORCINT;                               /* ATOM03IRQFORCINT */
    uint32 ATOM03IRQMODE;                                  /* ATOM03IRQMODE    */
    uint8  dummy163[80];                                   /* Reserved         */
    uint32 ATOM04RDADDR;                                   /* ATOM04RDADDR     */
    uint32 ATOM04CTRL;                                     /* ATOM04CTRL       */
    uint32 ATOM04SR0;                                      /* ATOM04SR0        */
    uint32 ATOM04SR1;                                      /* ATOM04SR1        */
    uint32 ATOM04CM0;                                      /* ATOM04CM0        */
    uint32 ATOM04CM1;                                      /* ATOM04CM1        */
    uint32 ATOM04CN0;                                      /* ATOM04CN0        */
    uint32 ATOM04STAT;                                     /* ATOM04STAT       */
    uint32 ATOM04IRQNOTIFY;                                /* ATOM04IRQNOTIFY  */
    uint32 ATOM04IRQEN;                                    /* ATOM04IRQEN      */
    uint32 ATOM04IRQFORCINT;                               /* ATOM04IRQFORCINT */
    uint32 ATOM04IRQMODE;                                  /* ATOM04IRQMODE    */
    uint8  dummy164[80];                                   /* Reserved         */
    uint32 ATOM05RDADDR;                                   /* ATOM05RDADDR     */
    uint32 ATOM05CTRL;                                     /* ATOM05CTRL       */
    uint32 ATOM05SR0;                                      /* ATOM05SR0        */
    uint32 ATOM05SR1;                                      /* ATOM05SR1        */
    uint32 ATOM05CM0;                                      /* ATOM05CM0        */
    uint32 ATOM05CM1;                                      /* ATOM05CM1        */
    uint32 ATOM05CN0;                                      /* ATOM05CN0        */
    uint32 ATOM05STAT;                                     /* ATOM05STAT       */
    uint32 ATOM05IRQNOTIFY;                                /* ATOM05IRQNOTIFY  */
    uint32 ATOM05IRQEN;                                    /* ATOM05IRQEN      */
    uint32 ATOM05IRQFORCINT;                               /* ATOM05IRQFORCINT */
    uint32 ATOM05IRQMODE;                                  /* ATOM05IRQMODE    */
    uint8  dummy165[80];                                   /* Reserved         */
    uint32 ATOM06RDADDR;                                   /* ATOM06RDADDR     */
    uint32 ATOM06CTRL;                                     /* ATOM06CTRL       */
    uint32 ATOM06SR0;                                      /* ATOM06SR0        */
    uint32 ATOM06SR1;                                      /* ATOM06SR1        */
    uint32 ATOM06CM0;                                      /* ATOM06CM0        */
    uint32 ATOM06CM1;                                      /* ATOM06CM1        */
    uint32 ATOM06CN0;                                      /* ATOM06CN0        */
    uint32 ATOM06STAT;                                     /* ATOM06STAT       */
    uint32 ATOM06IRQNOTIFY;                                /* ATOM06IRQNOTIFY  */
    uint32 ATOM06IRQEN;                                    /* ATOM06IRQEN      */
    uint32 ATOM06IRQFORCINT;                               /* ATOM06IRQFORCINT */
    uint32 ATOM06IRQMODE;                                  /* ATOM06IRQMODE    */
    uint8  dummy166[80];                                   /* Reserved         */
    uint32 ATOM07RDADDR;                                   /* ATOM07RDADDR     */
    uint32 ATOM07CTRL;                                     /* ATOM07CTRL       */
    uint32 ATOM07SR0;                                      /* ATOM07SR0        */
    uint32 ATOM07SR1;                                      /* ATOM07SR1        */
    uint32 ATOM07CM0;                                      /* ATOM07CM0        */
    uint32 ATOM07CM1;                                      /* ATOM07CM1        */
    uint32 ATOM07CN0;                                      /* ATOM07CN0        */
    uint32 ATOM07STAT;                                     /* ATOM07STAT       */
    uint32 ATOM07IRQNOTIFY;                                /* ATOM07IRQNOTIFY  */
    uint32 ATOM07IRQEN;                                    /* ATOM07IRQEN      */
    uint32 ATOM07IRQFORCINT;                               /* ATOM07IRQFORCINT */
    uint32 ATOM07IRQMODE;                                  /* ATOM07IRQMODE    */
    uint8  dummy167[1104];                                 /* Reserved         */
    uint32 ATOM10RDADDR;                                   /* ATOM10RDADDR     */
    uint32 ATOM10CTRL;                                     /* ATOM10CTRL       */
    uint32 ATOM10SR0;                                      /* ATOM10SR0        */
    uint32 ATOM10SR1;                                      /* ATOM10SR1        */
    uint32 ATOM10CM0;                                      /* ATOM10CM0        */
    uint32 ATOM10CM1;                                      /* ATOM10CM1        */
    uint32 ATOM10CN0;                                      /* ATOM10CN0        */
    uint32 ATOM10STAT;                                     /* ATOM10STAT       */
    uint32 ATOM10IRQNOTIFY;                                /* ATOM10IRQNOTIFY  */
    uint32 ATOM10IRQEN;                                    /* ATOM10IRQEN      */
    uint32 ATOM10IRQFORCINT;                               /* ATOM10IRQFORCINT */
    uint32 ATOM10IRQMODE;                                  /* ATOM10IRQMODE    */
    uint8  dummy168[16];                                   /* Reserved         */
    uint32 ATOM1AGCGLBCTRL;                                /* ATOM1AGCGLBCTRL  */
    uint32 ATOM1AGCENDISCTRL;                              /* ATOM1AGCENDISCTRL */
    uint32 ATOM1AGCENDISSTAT;                              /* ATOM1AGCENDISSTAT */
    uint32 ATOM1AGCACTTB;                                  /* ATOM1AGCACTTB    */
    uint32 ATOM1AGCOUTENCTRL;                              /* ATOM1AGCOUTENCTRL */
    uint32 ATOM1AGCOUTENSTAT;                              /* ATOM1AGCOUTENSTAT */
    uint32 ATOM1AGCFUPDCTRL;                               /* ATOM1AGCFUPDCTRL */
    uint32 ATOM1AGCINTTRIG;                                /* ATOM1AGCINTTRIG  */
    uint8  dummy169[32];                                   /* Reserved         */
    uint32 ATOM11RDADDR;                                   /* ATOM11RDADDR     */
    uint32 ATOM11CTRL;                                     /* ATOM11CTRL       */
    uint32 ATOM11SR0;                                      /* ATOM11SR0        */
    uint32 ATOM11SR1;                                      /* ATOM11SR1        */
    uint32 ATOM11CM0;                                      /* ATOM11CM0        */
    uint32 ATOM11CM1;                                      /* ATOM11CM1        */
    uint32 ATOM11CN0;                                      /* ATOM11CN0        */
    uint32 ATOM11STAT;                                     /* ATOM11STAT       */
    uint32 ATOM11IRQNOTIFY;                                /* ATOM11IRQNOTIFY  */
    uint32 ATOM11IRQEN;                                    /* ATOM11IRQEN      */
    uint32 ATOM11IRQFORCINT;                               /* ATOM11IRQFORCINT */
    uint32 ATOM11IRQMODE;                                  /* ATOM11IRQMODE    */
    uint8  dummy170[80];                                   /* Reserved         */
    uint32 ATOM12RDADDR;                                   /* ATOM12RDADDR     */
    uint32 ATOM12CTRL;                                     /* ATOM12CTRL       */
    uint32 ATOM12SR0;                                      /* ATOM12SR0        */
    uint32 ATOM12SR1;                                      /* ATOM12SR1        */
    uint32 ATOM12CM0;                                      /* ATOM12CM0        */
    uint32 ATOM12CM1;                                      /* ATOM12CM1        */
    uint32 ATOM12CN0;                                      /* ATOM12CN0        */
    uint32 ATOM12STAT;                                     /* ATOM12STAT       */
    uint32 ATOM12IRQNOTIFY;                                /* ATOM12IRQNOTIFY  */
    uint32 ATOM12IRQEN;                                    /* ATOM12IRQEN      */
    uint32 ATOM12IRQFORCINT;                               /* ATOM12IRQFORCINT */
    uint32 ATOM12IRQMODE;                                  /* ATOM12IRQMODE    */
    uint8  dummy171[80];                                   /* Reserved         */
    uint32 ATOM13RDADDR;                                   /* ATOM13RDADDR     */
    uint32 ATOM13CTRL;                                     /* ATOM13CTRL       */
    uint32 ATOM13SR0;                                      /* ATOM13SR0        */
    uint32 ATOM13SR1;                                      /* ATOM13SR1        */
    uint32 ATOM13CM0;                                      /* ATOM13CM0        */
    uint32 ATOM13CM1;                                      /* ATOM13CM1        */
    uint32 ATOM13CN0;                                      /* ATOM13CN0        */
    uint32 ATOM13STAT;                                     /* ATOM13STAT       */
    uint32 ATOM13IRQNOTIFY;                                /* ATOM13IRQNOTIFY  */
    uint32 ATOM13IRQEN;                                    /* ATOM13IRQEN      */
    uint32 ATOM13IRQFORCINT;                               /* ATOM13IRQFORCINT */
    uint32 ATOM13IRQMODE;                                  /* ATOM13IRQMODE    */
    uint8  dummy172[23632];                                /* Reserved         */
    uint32 DTM24CTRL;                                      /* DTM24CTRL        */
    uint32 DTM24CHCTRL1;                                   /* DTM24CHCTRL1     */
    uint32 DTM24CHCTRL2;                                   /* DTM24CHCTRL2     */
    uint32 DTM24CHCTRL2SR;                                 /* DTM24CHCTRL2SR   */
    uint32 DTM24PSCTRL;                                    /* DTM24PSCTRL      */
    uint32 DTM240DTV;                                      /* DTM240DTV        */
    uint32 DTM241DTV;                                      /* DTM241DTV        */
    uint32 DTM242DTV;                                      /* DTM242DTV        */
    uint32 DTM243DTV;                                      /* DTM243DTV        */
    uint32 DTM24CHSR;                                      /* DTM24CHSR        */
    uint8  dummy173[88];                                   /* Reserved         */
    uint32 DTM26CTRL;                                      /* DTM26CTRL        */
    uint32 DTM26CHCTRL1;                                   /* DTM26CHCTRL1     */
    uint32 DTM26CHCTRL2;                                   /* DTM26CHCTRL2     */
    uint32 DTM26CHCTRL2SR;                                 /* DTM26CHCTRL2SR   */
    uint32 DTM26PSCTRL;                                    /* DTM26PSCTRL      */
    uint32 DTM260DTV;                                      /* DTM260DTV        */
    uint32 DTM261DTV;                                      /* DTM261DTV        */
    uint32 DTM262DTV;                                      /* DTM262DTV        */
    uint32 DTM263DTV;                                      /* DTM263DTV        */
    uint32 DTM26CHSR;                                      /* DTM26CHSR        */
    uint8  dummy174[117080];                               /* Reserved         */
    uint32 MCS00R0;                                        /* MCS00R0          */
    uint32 MCS00R1;                                        /* MCS00R1          */
    uint32 MCS00R2;                                        /* MCS00R2          */
    uint32 MCS00R3;                                        /* MCS00R3          */
    uint32 MCS00R4;                                        /* MCS00R4          */
    uint32 MCS00R5;                                        /* MCS00R5          */
    uint32 MCS00R6;                                        /* MCS00R6          */
    uint32 MCS00R7;                                        /* MCS00R7          */
    uint32 MCS00CTRL;                                      /* MCS00CTRL        */
    uint32 MCS00ACB;                                       /* MCS00ACB         */
    uint32 MCS0CTRG;                                       /* MCS0CTRG         */
    uint32 MCS0STRG;                                       /* MCS0STRG         */
    uint8  dummy175[12];                                   /* Reserved         */
    uint32 MCS00MHB;                                       /* MCS00MHB         */
    uint32 MCS00PC;                                        /* MCS00PC          */
    uint32 MCS00IRQNOTIFY;                                 /* MCS00IRQNOTIFY   */
    uint32 MCS00IRQEN;                                     /* MCS00IRQEN       */
    uint32 MCS00IRQFORCINT;                                /* MCS00IRQFORCINT  */
    uint32 MCS00IRQMODE;                                   /* MCS00IRQMODE     */
    uint32 MCS00EIRQEN;                                    /* MCS00EIRQEN      */
    uint8  dummy176[12];                                   /* Reserved         */
    uint32 MCS0CTRLSTAT;                                   /* MCS0CTRLSTAT     */
    uint32 MCS0RESET;                                      /* MCS0RESET        */
    uint32 MCS0CAT;                                        /* MCS0CAT          */
    uint32 MCS0CWT;                                        /* MCS0CWT          */
    uint8  dummy177[8];                                    /* Reserved         */
    uint32 MCS0ERR;                                        /* MCS0ERR          */
    uint32 MCS01R0;                                        /* MCS01R0          */
    uint32 MCS01R1;                                        /* MCS01R1          */
    uint32 MCS01R2;                                        /* MCS01R2          */
    uint32 MCS01R3;                                        /* MCS01R3          */
    uint32 MCS01R4;                                        /* MCS01R4          */
    uint32 MCS01R5;                                        /* MCS01R5          */
    uint32 MCS01R6;                                        /* MCS01R6          */
    uint32 MCS01R7;                                        /* MCS01R7          */
    uint32 MCS01CTRL;                                      /* MCS01CTRL        */
    uint32 MCS01ACB;                                       /* MCS01ACB         */
    uint8  dummy178[20];                                   /* Reserved         */
    uint32 MCS01MHB;                                       /* MCS01MHB         */
    uint32 MCS01PC;                                        /* MCS01PC          */
    uint32 MCS01IRQNOTIFY;                                 /* MCS01IRQNOTIFY   */
    uint32 MCS01IRQEN;                                     /* MCS01IRQEN       */
    uint32 MCS01IRQFORCINT;                                /* MCS01IRQFORCINT  */
    uint32 MCS01IRQMODE;                                   /* MCS01IRQMODE     */
    uint32 MCS01EIRQEN;                                    /* MCS01EIRQEN      */
    uint8  dummy179[40];                                   /* Reserved         */
    uint32 MCS02R0;                                        /* MCS02R0          */
    uint32 MCS02R1;                                        /* MCS02R1          */
    uint32 MCS02R2;                                        /* MCS02R2          */
    uint32 MCS02R3;                                        /* MCS02R3          */
    uint32 MCS02R4;                                        /* MCS02R4          */
    uint32 MCS02R5;                                        /* MCS02R5          */
    uint32 MCS02R6;                                        /* MCS02R6          */
    uint32 MCS02R7;                                        /* MCS02R7          */
    uint32 MCS02CTRL;                                      /* MCS02CTRL        */
    uint32 MCS02ACB;                                       /* MCS02ACB         */
    uint8  dummy180[20];                                   /* Reserved         */
    uint32 MCS02MHB;                                       /* MCS02MHB         */
    uint32 MCS02PC;                                        /* MCS02PC          */
    uint32 MCS02IRQNOTIFY;                                 /* MCS02IRQNOTIFY   */
    uint32 MCS02IRQEN;                                     /* MCS02IRQEN       */
    uint32 MCS02IRQFORCINT;                                /* MCS02IRQFORCINT  */
    uint32 MCS02IRQMODE;                                   /* MCS02IRQMODE     */
    uint32 MCS02EIRQEN;                                    /* MCS02EIRQEN      */
    uint8  dummy181[40];                                   /* Reserved         */
    uint32 MCS03R0;                                        /* MCS03R0          */
    uint32 MCS03R1;                                        /* MCS03R1          */
    uint32 MCS03R2;                                        /* MCS03R2          */
    uint32 MCS03R3;                                        /* MCS03R3          */
    uint32 MCS03R4;                                        /* MCS03R4          */
    uint32 MCS03R5;                                        /* MCS03R5          */
    uint32 MCS03R6;                                        /* MCS03R6          */
    uint32 MCS03R7;                                        /* MCS03R7          */
    uint32 MCS03CTRL;                                      /* MCS03CTRL        */
    uint32 MCS03ACB;                                       /* MCS03ACB         */
    uint8  dummy182[20];                                   /* Reserved         */
    uint32 MCS03MHB;                                       /* MCS03MHB         */
    uint32 MCS03PC;                                        /* MCS03PC          */
    uint32 MCS03IRQNOTIFY;                                 /* MCS03IRQNOTIFY   */
    uint32 MCS03IRQEN;                                     /* MCS03IRQEN       */
    uint32 MCS03IRQFORCINT;                                /* MCS03IRQFORCINT  */
    uint32 MCS03IRQMODE;                                   /* MCS03IRQMODE     */
    uint32 MCS03EIRQEN;                                    /* MCS03EIRQEN      */
    uint8  dummy183[40];                                   /* Reserved         */
    uint32 MCS04R0;                                        /* MCS04R0          */
    uint32 MCS04R1;                                        /* MCS04R1          */
    uint32 MCS04R2;                                        /* MCS04R2          */
    uint32 MCS04R3;                                        /* MCS04R3          */
    uint32 MCS04R4;                                        /* MCS04R4          */
    uint32 MCS04R5;                                        /* MCS04R5          */
    uint32 MCS04R6;                                        /* MCS04R6          */
    uint32 MCS04R7;                                        /* MCS04R7          */
    uint32 MCS04CTRL;                                      /* MCS04CTRL        */
    uint32 MCS04ACB;                                       /* MCS04ACB         */
    uint8  dummy184[20];                                   /* Reserved         */
    uint32 MCS04MHB;                                       /* MCS04MHB         */
    uint32 MCS04PC;                                        /* MCS04PC          */
    uint32 MCS04IRQNOTIFY;                                 /* MCS04IRQNOTIFY   */
    uint32 MCS04IRQEN;                                     /* MCS04IRQEN       */
    uint32 MCS04IRQFORCINT;                                /* MCS04IRQFORCINT  */
    uint32 MCS04IRQMODE;                                   /* MCS04IRQMODE     */
    uint32 MCS04EIRQEN;                                    /* MCS04EIRQEN      */
    uint8  dummy185[40];                                   /* Reserved         */
    uint32 MCS05R0;                                        /* MCS05R0          */
    uint32 MCS05R1;                                        /* MCS05R1          */
    uint32 MCS05R2;                                        /* MCS05R2          */
    uint32 MCS05R3;                                        /* MCS05R3          */
    uint32 MCS05R4;                                        /* MCS05R4          */
    uint32 MCS05R5;                                        /* MCS05R5          */
    uint32 MCS05R6;                                        /* MCS05R6          */
    uint32 MCS05R7;                                        /* MCS05R7          */
    uint32 MCS05CTRL;                                      /* MCS05CTRL        */
    uint32 MCS05ACB;                                       /* MCS05ACB         */
    uint8  dummy186[20];                                   /* Reserved         */
    uint32 MCS05MHB;                                       /* MCS05MHB         */
    uint32 MCS05PC;                                        /* MCS05PC          */
    uint32 MCS05IRQNOTIFY;                                 /* MCS05IRQNOTIFY   */
    uint32 MCS05IRQEN;                                     /* MCS05IRQEN       */
    uint32 MCS05IRQFORCINT;                                /* MCS05IRQFORCINT  */
    uint32 MCS05IRQMODE;                                   /* MCS05IRQMODE     */
    uint32 MCS05EIRQEN;                                    /* MCS05EIRQEN      */
    uint8  dummy187[40];                                   /* Reserved         */
    uint32 MCS06R0;                                        /* MCS06R0          */
    uint32 MCS06R1;                                        /* MCS06R1          */
    uint32 MCS06R2;                                        /* MCS06R2          */
    uint32 MCS06R3;                                        /* MCS06R3          */
    uint32 MCS06R4;                                        /* MCS06R4          */
    uint32 MCS06R5;                                        /* MCS06R5          */
    uint32 MCS06R6;                                        /* MCS06R6          */
    uint32 MCS06R7;                                        /* MCS06R7          */
    uint32 MCS06CTRL;                                      /* MCS06CTRL        */
    uint32 MCS06ACB;                                       /* MCS06ACB         */
    uint8  dummy188[20];                                   /* Reserved         */
    uint32 MCS06MHB;                                       /* MCS06MHB         */
    uint32 MCS06PC;                                        /* MCS06PC          */
    uint32 MCS06IRQNOTIFY;                                 /* MCS06IRQNOTIFY   */
    uint32 MCS06IRQEN;                                     /* MCS06IRQEN       */
    uint32 MCS06IRQFORCINT;                                /* MCS06IRQFORCINT  */
    uint32 MCS06IRQMODE;                                   /* MCS06IRQMODE     */
    uint32 MCS06EIRQEN;                                    /* MCS06EIRQEN      */
    uint8  dummy189[40];                                   /* Reserved         */
    uint32 MCS07R0;                                        /* MCS07R0          */
    uint32 MCS07R1;                                        /* MCS07R1          */
    uint32 MCS07R2;                                        /* MCS07R2          */
    uint32 MCS07R3;                                        /* MCS07R3          */
    uint32 MCS07R4;                                        /* MCS07R4          */
    uint32 MCS07R5;                                        /* MCS07R5          */
    uint32 MCS07R6;                                        /* MCS07R6          */
    uint32 MCS07R7;                                        /* MCS07R7          */
    uint32 MCS07CTRL;                                      /* MCS07CTRL        */
    uint32 MCS07ACB;                                       /* MCS07ACB         */
    uint8  dummy190[20];                                   /* Reserved         */
    uint32 MCS07MHB;                                       /* MCS07MHB         */
    uint32 MCS07PC;                                        /* MCS07PC          */
    uint32 MCS07IRQNOTIFY;                                 /* MCS07IRQNOTIFY   */
    uint32 MCS07IRQEN;                                     /* MCS07IRQEN       */
    uint32 MCS07IRQFORCINT;                                /* MCS07IRQFORCINT  */
    uint32 MCS07IRQMODE;                                   /* MCS07IRQMODE     */
    uint32 MCS07EIRQEN;                                    /* MCS07EIRQEN      */
    uint8  dummy191[40];                                   /* Reserved         */
    uint32 MCS08R0;                                        /* MCS08R0          */
    uint32 MCS08R1;                                        /* MCS08R1          */
    uint32 MCS08R2;                                        /* MCS08R2          */
    uint32 MCS08R3;                                        /* MCS08R3          */
    uint32 MCS08R4;                                        /* MCS08R4          */
    uint32 MCS08R5;                                        /* MCS08R5          */
    uint32 MCS08R6;                                        /* MCS08R6          */
    uint32 MCS08R7;                                        /* MCS08R7          */
    uint32 MCS08CTRL;                                      /* MCS08CTRL        */
    uint32 MCS08ACB;                                       /* MCS08ACB         */
    uint8  dummy192[20];                                   /* Reserved         */
    uint32 MCS08MHB;                                       /* MCS08MHB         */
    uint32 MCS08PC;                                        /* MCS08PC          */
    uint32 MCS08IRQNOTIFY;                                 /* MCS08IRQNOTIFY   */
    uint32 MCS08IRQEN;                                     /* MCS08IRQEN       */
    uint32 MCS08IRQFORCINT;                                /* MCS08IRQFORCINT  */
    uint32 MCS08IRQMODE;                                   /* MCS08IRQMODE     */
    uint32 MCS08EIRQEN;                                    /* MCS08EIRQEN      */
} R_GTM0;
typedef struct
{                                                          /* Module           */
    uint32 CTL;                                            /* CTL              */
    uint32 TMC;                                            /* TMC              */
    uint32 TRC;                                            /* TRC              */
    uint32 TED;                                            /* TED              */
    uint32 EAD0;                                           /* EAD0             */
    uint8  dummy193[236];                                  /* Reserved         */
} R_ECCGTM0;
typedef struct
{                                                          /* Module           */
    uint32 CTL;                                            /* CTL              */
    uint32 TMC;                                            /* TMC              */
    uint32 TRC;                                            /* TRC              */
    uint32 TED;                                            /* TED              */
    uint32 EAD0;                                           /* EAD0             */
} R_ECCGTM1;
typedef struct
{                                                          /* Module           */
    uint8  WDTE;                                           /* WDTE             */
    uint8  dummy194[3];                                    /* Reserved         */
    uint8  EVAC;                                           /* EVAC             */
    uint8  dummy195[3];                                    /* Reserved         */
    uint8  REF;                                            /* REF              */
    uint8  dummy196[3];                                    /* Reserved         */
    uint8  MD;                                             /* MD               */
} R_WDTA0;
typedef struct
{                                                          /* Module           */
    uint32 CLR;                                            /* CLR              */
    uint32 STS0;                                           /* STS0             */
    uint32 STS1;                                           /* STS1             */
    uint32 STSC;                                           /* STSC             */
    uint32 WDTE;                                           /* WDTE             */
    uint32 MD;                                             /* MD               */
    uint8  dummy197[8];                                    /* Reserved         */
    uint32 PCAD;                                           /* PCAD             */
} R_SWD0;
typedef struct
{                                                          /* Module           */
    R_type1 PROT00;                                        /* PROT00           */
    R_type1 SPID00;                                        /* SPID00           */
    R_type1 PROT01;                                        /* PROT01           */
    R_type1 SPID01;                                        /* SPID01           */
    R_type1 PROT02;                                        /* PROT02           */
    R_type1 SPID02;                                        /* SPID02           */
    R_type1 PROT03;                                        /* PROT03           */
    R_type1 SPID03;                                        /* SPID03           */
    R_type1 PROT04;                                        /* PROT04           */
    R_type1 SPID04;                                        /* SPID04           */
    R_type1 PROT05;                                        /* PROT05           */
    R_type1 SPID05;                                        /* SPID05           */
} R_FSGD1A;
typedef struct
{                                                          /* Module           */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy198[3];                                    /* Reserved         */
    uint32 STAT;                                           /* STAT             */
    uint8  dummy199[4];                                    /* Reserved         */
    uint32 TYPE;                                           /* TYPE             */
} R_ERRSLV1;
typedef struct
{                                                          /* Module           */
    R_type1 PROT00;                                        /* PROT00           */
    R_type1 SPID00;                                        /* SPID00           */
    R_type1 PROT01;                                        /* PROT01           */
    R_type1 SPID01;                                        /* SPID01           */
    uint8  dummy200[64];                                   /* Reserved         */
    R_type1 PROT10;                                        /* PROT10           */
    R_type1 SPID10;                                        /* SPID10           */
    R_type1 PROT11;                                        /* PROT11           */
    R_type1 SPID11;                                        /* SPID11           */
} R_FSGD1B;
typedef struct
{                                                          /* Module           */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy201[3];                                    /* Reserved         */
    uint32 STAT;                                           /* STAT             */
    uint8  dummy202[4];                                    /* Reserved         */
    uint32 TYPE;                                           /* TYPE             */
} R_ERRSLV1AI;
typedef struct
{                                                          /* Module           */
    R_type1 CREL;                                          /* CREL             */
    R_type1 ENDN;                                          /* ENDN             */
    uint8  dummy203[4];                                    /* Reserved         */
    R_type1 DBTP;                                          /* DBTP             */
    R_type1 TEST;                                          /* TEST             */
    R_type1 RWD;                                           /* RWD              */
    R_type1 CCCR;                                          /* CCCR             */
    R_type1 NBTP;                                          /* NBTP             */
    R_type1 TSCC;                                          /* TSCC             */
    R_type1 TSCV;                                          /* TSCV             */
    R_type1 TOCC;                                          /* TOCC             */
    R_type1 TOCV;                                          /* TOCV             */
    uint8  dummy204[16];                                   /* Reserved         */
    R_type1 ECR;                                           /* ECR              */
    R_type1 PSR;                                           /* PSR              */
    R_type1 TDCR;                                          /* TDCR             */
    uint8  dummy205[4];                                    /* Reserved         */
    R_type1 IR;                                            /* IR               */
    R_type1 IE;                                            /* IE               */
    R_type1 ILS;                                           /* ILS              */
    R_type1 ILE;                                           /* ILE              */
    uint8  dummy206[32];                                   /* Reserved         */
    R_type1 GFC;                                           /* GFC              */
    R_type1 SIDFC;                                         /* SIDFC            */
    R_type1 XIDFC;                                         /* XIDFC            */
    uint8  dummy207[4];                                    /* Reserved         */
    R_type1 XIDAM;                                         /* XIDAM            */
    R_type1 HPMS;                                          /* HPMS             */
    R_type1 NDAT1;                                         /* NDAT1            */
    R_type1 NDAT2;                                         /* NDAT2            */
    R_type1 RXF0C;                                         /* RXF0C            */
    R_type1 RXF0S;                                         /* RXF0S            */
    R_type1 RXF0A;                                         /* RXF0A            */
    R_type1 RXBC;                                          /* RXBC             */
    R_type1 RXF1C;                                         /* RXF1C            */
    R_type1 RXF1S;                                         /* RXF1S            */
    R_type1 RXF1A;                                         /* RXF1A            */
    R_type1 RXESC;                                         /* RXESC            */
    R_type1 TXBC;                                          /* TXBC             */
    R_type1 TXFQS;                                         /* TXFQS            */
    R_type1 TXESC;                                         /* TXESC            */
    R_type1 TXBRP;                                         /* TXBRP            */
    R_type1 TXBAR;                                         /* TXBAR            */
    R_type1 TXBCR;                                         /* TXBCR            */
    R_type1 TXBTO;                                         /* TXBTO            */
    R_type1 TXBCF;                                         /* TXBCF            */
    R_type1 TXBTIE;                                        /* TXBTIE           */
    R_type1 TXBCIE;                                        /* TXBCIE           */
    uint8  dummy208[8];                                    /* Reserved         */
    R_type1 TXEFC;                                         /* TXEFC            */
    R_type1 TXEFS;                                         /* TXEFS            */
    R_type1 TXEFA;                                         /* TXEFA            */
} R_MCAN0;
typedef struct
{                                                          /* Module           */
    uint32 CIN;                                            /* CIN              */
    uint32 COUT;                                           /* COUT             */
    uint8  dummy209[24];                                   /* Reserved         */
    uint8  CTL;                                            /* CTL              */
} R_DCRB1;
typedef struct
{                                                          /* Module           */
    uint8  CTL0;                                           /* CTL0             */
    uint8  dummy210[7];                                    /* Reserved         */
    uint16 CMPL;                                           /* CMPL             */
    uint8  dummy211[2];                                    /* Reserved         */
    uint16 CMPH;                                           /* CMPH             */
    uint8  dummy212[2];                                    /* Reserved         */
    uint8  PCMD;                                           /* PCMD             */
    uint8  dummy213[3];                                    /* Reserved         */
    uint8  PS;                                             /* PS               */
    uint8  dummy214[3];                                    /* Reserved         */
    uint8  EMU0;                                           /* EMU0             */
    uint8  dummy215[231];                                  /* Reserved         */
} R_CLMA0;
typedef struct
{                                                          /* Module           */
    uint8  CTL0;                                           /* CTL0             */
    uint8  dummy216[7];                                    /* Reserved         */
    uint16 CMPL;                                           /* CMPL             */
    uint8  dummy217[2];                                    /* Reserved         */
    uint16 CMPH;                                           /* CMPH             */
    uint8  dummy218[2];                                    /* Reserved         */
    uint8  PCMD;                                           /* PCMD             */
    uint8  dummy219[3];                                    /* Reserved         */
    uint8  PS;                                             /* PS               */
    uint8  dummy220[3];                                    /* Reserved         */
    uint8  EMU0;                                           /* EMU0             */
    uint8  dummy221[231];                                  /* Reserved         */
} R_CLMA1;
typedef struct
{                                                          /* Module           */
    uint8  CTL0;                                           /* CTL0             */
    uint8  dummy222[7];                                    /* Reserved         */
    uint16 CMPL;                                           /* CMPL             */
    uint8  dummy223[2];                                    /* Reserved         */
    uint16 CMPH;                                           /* CMPH             */
    uint8  dummy224[2];                                    /* Reserved         */
    uint8  PCMD;                                           /* PCMD             */
    uint8  dummy225[3];                                    /* Reserved         */
    uint8  PS;                                             /* PS               */
    uint8  dummy226[3];                                    /* Reserved         */
    uint8  EMU0;                                           /* EMU0             */
    uint8  dummy227[231];                                  /* Reserved         */
} R_CLMA2;
typedef struct
{                                                          /* Module           */
    uint8  CTL0;                                           /* CTL0             */
    uint8  dummy228[7];                                    /* Reserved         */
    uint16 CMPL;                                           /* CMPL             */
    uint8  dummy229[2];                                    /* Reserved         */
    uint16 CMPH;                                           /* CMPH             */
    uint8  dummy230[2];                                    /* Reserved         */
    uint8  PCMD;                                           /* PCMD             */
    uint8  dummy231[3];                                    /* Reserved         */
    uint8  PS;                                             /* PS               */
    uint8  dummy232[3];                                    /* Reserved         */
    uint8  EMU0;                                           /* EMU0             */
} R_CLMA3;
typedef struct
{                                                          /* Module           */
    R_type1 PROT00;                                        /* PROT00           */
    R_type1 SPID00;                                        /* SPID00           */
    R_type1 PROT01;                                        /* PROT01           */
    R_type1 SPID01;                                        /* SPID01           */
    R_type1 PROT02;                                        /* PROT02           */
    R_type1 SPID02;                                        /* SPID02           */
    R_type1 PROT03;                                        /* PROT03           */
    R_type1 SPID03;                                        /* SPID03           */
    R_type1 PROT04;                                        /* PROT04           */
    R_type1 SPID04;                                        /* SPID04           */
    R_type1 PROT05;                                        /* PROT05           */
    R_type1 SPID05;                                        /* SPID05           */
    R_type1 PROT06;                                        /* PROT06           */
    R_type1 SPID06;                                        /* SPID06           */
    R_type1 PROT07;                                        /* PROT07           */
    R_type1 SPID07;                                        /* SPID07           */
    uint8  dummy233[16];                                   /* Reserved         */
    R_type1 PROT10;                                        /* PROT10           */
    R_type1 SPID10;                                        /* SPID10           */
    R_type1 PROT11;                                        /* PROT11           */
    R_type1 SPID11;                                        /* SPID11           */
    R_type1 PROT12;                                        /* PROT12           */
    R_type1 SPID12;                                        /* SPID12           */
    R_type1 PROT13;                                        /* PROT13           */
    R_type1 SPID13;                                        /* SPID13           */
    R_type1 PROT14;                                        /* PROT14           */
    R_type1 SPID14;                                        /* SPID14           */
    R_type1 PROT15;                                        /* PROT15           */
    R_type1 SPID15;                                        /* SPID15           */
} R_FSGD4A;
typedef struct
{                                                          /* Module           */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy234[3];                                    /* Reserved         */
    uint32 STAT;                                           /* STAT             */
    uint8  dummy235[4];                                    /* Reserved         */
    uint32 TYPE;                                           /* TYPE             */
} R_ERRSLV4;
typedef struct
{                                                          /* Module           */
    R_type1 PROT00;                                        /* PROT00           */
    R_type1 SPID00;                                        /* SPID00           */
    R_type1 PROT01;                                        /* PROT01           */
    R_type1 SPID01;                                        /* SPID01           */
    R_type1 PROT02;                                        /* PROT02           */
    R_type1 SPID02;                                        /* SPID02           */
    R_type1 PROT03;                                        /* PROT03           */
    R_type1 SPID03;                                        /* SPID03           */
    uint8  dummy236[16];                                   /* Reserved         */
    R_type1 PROT06;                                        /* PROT06           */
    R_type1 SPID06;                                        /* SPID06           */
    R_type1 PROT07;                                        /* PROT07           */
    R_type1 SPID07;                                        /* SPID07           */
    R_type1 PROT08;                                        /* PROT08           */
    R_type1 SPID08;                                        /* SPID08           */
    R_type1 PROT09;                                        /* PROT09           */
    R_type1 SPID09;                                        /* SPID09           */
    R_type1 PROT10;                                        /* PROT10           */
    R_type1 SPID10;                                        /* SPID10           */
    R_type1 PROT11;                                        /* PROT11           */
    R_type1 SPID11;                                        /* SPID11           */
    R_type1 PROT12;                                        /* PROT12           */
    R_type1 SPID12;                                        /* SPID12           */
    R_type1 PROT13;                                        /* PROT13           */
    R_type1 SPID13;                                        /* SPID13           */
} R_FSGD4B;
typedef struct
{                                                          /* Module           */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy237[3];                                    /* Reserved         */
    uint32 STAT;                                           /* STAT             */
    uint8  dummy238[4];                                    /* Reserved         */
    uint32 TYPE;                                           /* TYPE             */
} R_ERRSLV4AI;
typedef struct
{                                                          /* Module           */
    uint32 VCR0;                                           /* VCR0             */
    uint32 VCR1;                                           /* VCR1             */
    uint32 VCR2;                                           /* VCR2             */
    uint32 VCR3;                                           /* VCR3             */
    uint32 VCR4;                                           /* VCR4             */
    uint32 VCR5;                                           /* VCR5             */
    uint32 VCR6;                                           /* VCR6             */
    uint32 VCR7;                                           /* VCR7             */
    uint32 VCR8;                                           /* VCR8             */
    uint32 VCR9;                                           /* VCR9             */
    uint32 VCR10;                                          /* VCR10            */
    uint32 VCR11;                                          /* VCR11            */
    uint32 VCR12;                                          /* VCR12            */
    uint32 VCR13;                                          /* VCR13            */
    uint32 VCR14;                                          /* VCR14            */
    uint32 VCR15;                                          /* VCR15            */
    uint32 VCR16;                                          /* VCR16            */
    uint32 VCR17;                                          /* VCR17            */
    uint32 VCR18;                                          /* VCR18            */
    uint32 VCR19;                                          /* VCR19            */
    uint32 VCR20;                                          /* VCR20            */
    uint32 VCR21;                                          /* VCR21            */
    uint32 VCR22;                                          /* VCR22            */
    uint32 VCR23;                                          /* VCR23            */
    uint32 VCR24;                                          /* VCR24            */
    uint32 VCR25;                                          /* VCR25            */
    uint32 VCR26;                                          /* VCR26            */
    uint32 VCR27;                                          /* VCR27            */
    uint32 VCR28;                                          /* VCR28            */
    uint32 VCR29;                                          /* VCR29            */
    uint32 VCR30;                                          /* VCR30            */
    uint32 VCR31;                                          /* VCR31            */
    uint8  dummy239[128];                                  /* Reserved         */
    uint32 DR00;                                           /* DR00             */
    uint32 DR02;                                           /* DR02             */
    uint32 DR04;                                           /* DR04             */
    uint32 DR06;                                           /* DR06             */
    uint32 DR08;                                           /* DR08             */
    uint32 DR10;                                           /* DR10             */
    uint32 DR12;                                           /* DR12             */
    uint32 DR14;                                           /* DR14             */
    uint32 DR16;                                           /* DR16             */
    uint32 DR18;                                           /* DR18             */
    uint32 DR20;                                           /* DR20             */
    uint32 DR22;                                           /* DR22             */
    uint32 DR24;                                           /* DR24             */
    uint32 DR26;                                           /* DR26             */
    uint32 DR28;                                           /* DR28             */
    uint32 DR30;                                           /* DR30             */
    uint8  dummy240[192];                                  /* Reserved         */
    uint32 DIR0;                                           /* DIR0             */
    uint32 DIR1;                                           /* DIR1             */
    uint32 DIR2;                                           /* DIR2             */
    uint32 DIR3;                                           /* DIR3             */
    uint32 DIR4;                                           /* DIR4             */
    uint32 DIR5;                                           /* DIR5             */
    uint32 DIR6;                                           /* DIR6             */
    uint32 DIR7;                                           /* DIR7             */
    uint32 DIR8;                                           /* DIR8             */
    uint32 DIR9;                                           /* DIR9             */
    uint32 DIR10;                                          /* DIR10            */
    uint32 DIR11;                                          /* DIR11            */
    uint32 DIR12;                                          /* DIR12            */
    uint32 DIR13;                                          /* DIR13            */
    uint32 DIR14;                                          /* DIR14            */
    uint32 DIR15;                                          /* DIR15            */
    uint32 DIR16;                                          /* DIR16            */
    uint32 DIR17;                                          /* DIR17            */
    uint32 DIR18;                                          /* DIR18            */
    uint32 DIR19;                                          /* DIR19            */
    uint32 DIR20;                                          /* DIR20            */
    uint32 DIR21;                                          /* DIR21            */
    uint32 DIR22;                                          /* DIR22            */
    uint32 DIR23;                                          /* DIR23            */
    uint32 DIR24;                                          /* DIR24            */
    uint32 DIR25;                                          /* DIR25            */
    uint32 DIR26;                                          /* DIR26            */
    uint32 DIR27;                                          /* DIR27            */
    uint32 DIR28;                                          /* DIR28            */
    uint32 DIR29;                                          /* DIR29            */
    uint32 DIR30;                                          /* DIR30            */
    uint32 DIR31;                                          /* DIR31            */
    uint8  dummy241[128];                                  /* Reserved         */
    uint8  ADSYNSTCR;                                      /* ADSYNSTCR        */
    uint8  dummy242[3];                                    /* Reserved         */
    uint8  ADTSYNSTCR;                                     /* ADTSYNSTCR       */
    uint8  dummy243[123];                                  /* Reserved         */
    uint8  ADHALTR;                                        /* ADHALTR          */
    uint8  dummy244[3];                                    /* Reserved         */
    uint8  ADCR1;                                          /* ADCR1            */
    uint8  dummy245[3];                                    /* Reserved         */
    uint8  MPXCURCR;                                       /* MPXCURCR         */
    uint8  dummy246[3];                                    /* Reserved         */
    uint32 MPXCURR;                                        /* MPXCURR          */
    uint8  MPXOWR;                                         /* MPXOWR           */
    uint8  dummy247[7];                                    /* Reserved         */
    uint8  ADCR2;                                          /* ADCR2            */
    uint8  dummy248[7];                                    /* Reserved         */
    uint8  ADENDP0;                                        /* ADENDP0          */
    uint8  dummy249[31];                                   /* Reserved         */
    uint8  SFTCR;                                          /* SFTCR            */
    uint8  dummy250[3];                                    /* Reserved         */
    uint8  TDCR;                                           /* TDCR             */
    uint8  dummy251[7];                                    /* Reserved         */
    R_type5 ULLMTBR0;                                      /* ULLMTBR0         */
    R_type5 ULLMTBR1;                                      /* ULLMTBR1         */
    R_type5 ULLMTBR2;                                      /* ULLMTBR2         */
    uint8  ECR;                                            /* ECR              */
    uint8  dummy252[3];                                    /* Reserved         */
    uint8  ULER;                                           /* ULER             */
    uint8  dummy253[3];                                    /* Reserved         */
    uint8  OWER;                                           /* OWER             */
    uint8  dummy254[3];                                    /* Reserved         */
    uint8  PER;                                            /* PER              */
    uint8  dummy255[3];                                    /* Reserved         */
    uint8  IDER;                                           /* IDER             */
    uint8  dummy256[23];                                   /* Reserved         */
    uint8  THSMPSTCR;                                      /* THSMPSTCR        */
    uint8  dummy257[3];                                    /* Reserved         */
    uint8  THSTPCR;                                        /* THSTPCR          */
    uint8  dummy258[3];                                    /* Reserved         */
    uint8  THCR;                                           /* THCR             */
    uint8  dummy259[7];                                    /* Reserved         */
    uint8  THAHLDSTCR;                                     /* THAHLDSTCR       */
    uint8  dummy260[3];                                    /* Reserved         */
    uint8  THBHLDSTCR;                                     /* THBHLDSTCR       */
    uint8  dummy261[11];                                   /* Reserved         */
    uint8  THACR;                                          /* THACR            */
    uint8  dummy262[3];                                    /* Reserved         */
    uint8  THBCR;                                          /* THBCR            */
    uint8  dummy263[11];                                   /* Reserved         */
    uint8  THER;                                           /* THER             */
    uint8  dummy264[3];                                    /* Reserved         */
    uint16 THGSR;                                          /* THGSR            */
    uint8  dummy265[74];                                   /* Reserved         */
    uint8  SGSTCR0;                                        /* SGSTCR0          */
    uint8  dummy266[15];                                   /* Reserved         */
    uint8  SGCR0;                                          /* SGCR0            */
    uint8  dummy267[3];                                    /* Reserved         */
    uint8  SGVCSP0;                                        /* SGVCSP0          */
    uint8  dummy268[3];                                    /* Reserved         */
    uint8  SGVCEP0;                                        /* SGVCEP0          */
    uint8  dummy269[3];                                    /* Reserved         */
    uint8  SGMCYCR0;                                       /* SGMCYCR0         */
    uint8  dummy270[7];                                    /* Reserved         */
    uint8  SGSR0;                                          /* SGSR0            */
    uint8  dummy271[11];                                   /* Reserved         */
    uint8  ULLMSR0;                                        /* ULLMSR0          */
    uint8  dummy272[79];                                   /* Reserved         */
    uint8  SGSTCR1;                                        /* SGSTCR1          */
    uint8  dummy273[15];                                   /* Reserved         */
    uint8  SGCR1;                                          /* SGCR1            */
    uint8  dummy274[3];                                    /* Reserved         */
    uint8  SGVCSP1;                                        /* SGVCSP1          */
    uint8  dummy275[3];                                    /* Reserved         */
    uint8  SGVCEP1;                                        /* SGVCEP1          */
    uint8  dummy276[3];                                    /* Reserved         */
    uint8  SGMCYCR1;                                       /* SGMCYCR1         */
    uint8  dummy277[7];                                    /* Reserved         */
    uint8  SGSR1;                                          /* SGSR1            */
    uint8  dummy278[11];                                   /* Reserved         */
    uint8  ULLMSR1;                                        /* ULLMSR1          */
    uint8  dummy279[79];                                   /* Reserved         */
    uint8  SGSTCR2;                                        /* SGSTCR2          */
    uint8  dummy280[15];                                   /* Reserved         */
    uint8  SGCR2;                                          /* SGCR2            */
    uint8  dummy281[3];                                    /* Reserved         */
    uint8  SGVCSP2;                                        /* SGVCSP2          */
    uint8  dummy282[3];                                    /* Reserved         */
    uint8  SGVCEP2;                                        /* SGVCEP2          */
    uint8  dummy283[3];                                    /* Reserved         */
    uint8  SGMCYCR2;                                       /* SGMCYCR2         */
    uint8  dummy284[7];                                    /* Reserved         */
    uint8  SGSR2;                                          /* SGSR2            */
    uint8  dummy285[11];                                   /* Reserved         */
    uint8  ULLMSR2;                                        /* ULLMSR2          */
    uint8  dummy286[79];                                   /* Reserved         */
    uint8  SGSTCR3;                                        /* SGSTCR3          */
    uint8  dummy287[7];                                    /* Reserved         */
    uint8  ADTSTCR3;                                       /* ADTSTCR3         */
    uint8  dummy288[3];                                    /* Reserved         */
    uint8  ADTENDCR3;                                      /* ADTENDCR3        */
    uint8  dummy289[3];                                    /* Reserved         */
    uint8  SGCR3;                                          /* SGCR3            */
    uint8  dummy290[3];                                    /* Reserved         */
    uint8  SGVCSP3;                                        /* SGVCSP3          */
    uint8  dummy291[3];                                    /* Reserved         */
    uint8  SGVCEP3;                                        /* SGVCEP3          */
    uint8  dummy292[3];                                    /* Reserved         */
    uint8  SGMCYCR3;                                       /* SGMCYCR3         */
    uint8  dummy293[7];                                    /* Reserved         */
    uint8  SGSR3;                                          /* SGSR3            */
    uint8  dummy294[3];                                    /* Reserved         */
    uint32 ADTIPR3;                                        /* ADTIPR3          */
    uint32 ADTPRR3;                                        /* ADTPRR3          */
    uint8  ULLMSR3;                                        /* ULLMSR3          */
    uint8  dummy295[79];                                   /* Reserved         */
    uint8  SGSTCR4;                                        /* SGSTCR4          */
    uint8  dummy296[7];                                    /* Reserved         */
    uint8  ADTSTCR4;                                       /* ADTSTCR4         */
    uint8  dummy297[3];                                    /* Reserved         */
    uint8  ADTENDCR4;                                      /* ADTENDCR4        */
    uint8  dummy298[3];                                    /* Reserved         */
    uint8  SGCR4;                                          /* SGCR4            */
    uint8  dummy299[3];                                    /* Reserved         */
    uint8  SGVCSP4;                                        /* SGVCSP4          */
    uint8  dummy300[3];                                    /* Reserved         */
    uint8  SGVCEP4;                                        /* SGVCEP4          */
    uint8  dummy301[3];                                    /* Reserved         */
    uint8  SGMCYCR4;                                       /* SGMCYCR4         */
    uint8  dummy302[7];                                    /* Reserved         */
    uint8  SGSR4;                                          /* SGSR4            */
    uint8  dummy303[3];                                    /* Reserved         */
    uint32 ADTIPR4;                                        /* ADTIPR4          */
    uint32 ADTPRR4;                                        /* ADTPRR4          */
    uint8  ULLMSR4;                                        /* ULLMSR4          */
} R_ADCF0;
typedef struct
{                                                          /* Module           */
    uint8  OTSTCR;                                         /* OTSTCR           */
    uint8  dummy304[3];                                    /* Reserved         */
    uint8  OTENDCR;                                        /* OTENDCR          */
    uint8  dummy305[3];                                    /* Reserved         */
    uint8  OTCR;                                           /* OTCR             */
    uint8  dummy306[3];                                    /* Reserved         */
    uint8  OTFCR;                                          /* OTFCR            */
    uint8  dummy307[3];                                    /* Reserved         */
    uint8  OTFR;                                           /* OTFR             */
    uint8  dummy308[3];                                    /* Reserved         */
    uint8  OTSTR;                                          /* OTSTR            */
    uint8  dummy309[3];                                    /* Reserved         */
    uint16 OTDR;                                           /* OTDR             */
    uint8  dummy310[2];                                    /* Reserved         */
    uint16 HTBRAU;                                         /* HTBRAU           */
    uint8  dummy311[2];                                    /* Reserved         */
    uint16 HTBRAL;                                         /* HTBRAL           */
    uint8  dummy312[2];                                    /* Reserved         */
    uint16 HTBRBU;                                         /* HTBRBU           */
    uint8  dummy313[2];                                    /* Reserved         */
    uint16 HTBRBL;                                         /* HTBRBL           */
    uint8  dummy314[2];                                    /* Reserved         */
    uint16 LTBRAU;                                         /* LTBRAU           */
    uint8  dummy315[2];                                    /* Reserved         */
    uint16 LTBRAL;                                         /* LTBRAL           */
    uint8  dummy316[2];                                    /* Reserved         */
    uint16 TDLR;                                           /* TDLR             */
    uint8  dummy317[2];                                    /* Reserved         */
    uint16 COEFFRA;                                        /* COEFFRA          */
    uint8  dummy318[2];                                    /* Reserved         */
    uint16 COEFFRB;                                        /* COEFFRB          */
    uint8  dummy319[2];                                    /* Reserved         */
    uint16 COEFFRC;                                        /* COEFFRC          */
} R_OTS0;
typedef struct
{                                                          /* Module           */
    R_type1 PROT00;                                        /* PROT00           */
    R_type1 SPID00;                                        /* SPID00           */
    R_type1 PROT01;                                        /* PROT01           */
    R_type1 SPID01;                                        /* SPID01           */
    R_type1 PROT02;                                        /* PROT02           */
    R_type1 SPID02;                                        /* SPID02           */
    R_type1 PROT03;                                        /* PROT03           */
    R_type1 SPID03;                                        /* SPID03           */
    R_type1 PROT04;                                        /* PROT04           */
    R_type1 SPID04;                                        /* SPID04           */
    R_type1 PROT05;                                        /* PROT05           */
    R_type1 SPID05;                                        /* SPID05           */
    R_type1 PROT06;                                        /* PROT06           */
    R_type1 SPID06;                                        /* SPID06           */
    R_type1 PROT07;                                        /* PROT07           */
    R_type1 SPID07;                                        /* SPID07           */
    R_type1 PROT08;                                        /* PROT08           */
    R_type1 SPID08;                                        /* SPID08           */
    R_type1 PROT09;                                        /* PROT09           */
    R_type1 SPID09;                                        /* SPID09           */
    uint8  dummy320[16];                                   /* Reserved         */
    R_type1 PROT12;                                        /* PROT12           */
    R_type1 SPID12;                                        /* SPID12           */
    R_type1 PROT13;                                        /* PROT13           */
    R_type1 SPID13;                                        /* SPID13           */
} R_FSGD3A;
typedef struct
{                                                          /* Module           */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy321[3];                                    /* Reserved         */
    uint32 STAT;                                           /* STAT             */
    uint8  dummy322[4];                                    /* Reserved         */
    uint32 TYPE;                                           /* TYPE             */
} R_ERRSLV3;
typedef struct
{                                                          /* Module           */
    R_type1 PROT00;                                        /* PROT00           */
    R_type1 SPID00;                                        /* SPID00           */
    R_type1 PROT01;                                        /* PROT01           */
    R_type1 SPID01;                                        /* SPID01           */
    uint8  dummy323[64];                                   /* Reserved         */
    R_type1 PROT10;                                        /* PROT10           */
    R_type1 SPID10;                                        /* SPID10           */
    R_type1 PROT11;                                        /* PROT11           */
    R_type1 SPID11;                                        /* SPID11           */
    R_type1 PROT12;                                        /* PROT12           */
    R_type1 SPID12;                                        /* SPID12           */
    R_type1 PROT13;                                        /* PROT13           */
    R_type1 SPID13;                                        /* SPID13           */
} R_FSGD3B;
typedef struct
{                                                          /* Module           */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy324[3];                                    /* Reserved         */
    uint32 STAT;                                           /* STAT             */
    uint8  dummy325[4];                                    /* Reserved         */
    uint32 TYPE;                                           /* TYPE             */
} R_ERRSLV3AI;
typedef struct
{                                                          /* Module           */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy326[3];                                    /* Reserved         */
    uint32 STAT;                                           /* STAT             */
    uint8  dummy327[4];                                    /* Reserved         */
    uint32 TYPE;                                           /* TYPE             */
} R_ERRSLVHI;
typedef struct
{                                                          /* Module           */
    uint8  dummy328[2];                                    /* Reserved         */
    uint16 ECRUM;                                          /* ECRUM            */
    uint8  dummy329[4];                                    /* Reserved         */
    uint32 ADRUM;                                          /* ADRUM            */
    uint8  dummy330[1];                                    /* Reserved         */
    R_type0 ENUM;                                          /* ENUM             */
    uint8  dummy331[18];                                   /* Reserved         */
    R_type0 PMTUM0;                                        /* PMTUM0           */
    R_type0 PMTUM1;                                        /* PMTUM1           */
    R_type0 PMTUM2;                                        /* PMTUM2           */
    R_type0 PMTUM3;                                        /* PMTUM3           */
    R_type0 PMTUM4;                                        /* PMTUM4           */
} R_IPG;
typedef struct
{                                                          /* Module           */
    R_type1 G0MK;                                          /* G0MK             */
    R_type1 G0BA;                                          /* G0BA             */
    R_type1 G0SP;                                          /* G0SP             */
    uint8  dummy332[4];                                    /* Reserved         */
    R_type1 G1MK;                                          /* G1MK             */
    R_type1 G1BA;                                          /* G1BA             */
    R_type1 G1SP;                                          /* G1SP             */
    uint8  dummy333[4];                                    /* Reserved         */
    R_type1 G2MK;                                          /* G2MK             */
    R_type1 G2BA;                                          /* G2BA             */
    R_type1 G2SP;                                          /* G2SP             */
    uint8  dummy334[4];                                    /* Reserved         */
    R_type1 G3MK;                                          /* G3MK             */
    R_type1 G3BA;                                          /* G3BA             */
    R_type1 G3SP;                                          /* G3SP             */
    uint8  dummy335[4];                                    /* Reserved         */
    R_type1 G4MK;                                          /* G4MK             */
    R_type1 G4BA;                                          /* G4BA             */
    R_type1 G4SP;                                          /* G4SP             */
    uint8  dummy336[4];                                    /* Reserved         */
    R_type1 G5MK;                                          /* G5MK             */
    R_type1 G5BA;                                          /* G5BA             */
    R_type1 G5SP;                                          /* G5SP             */
    uint8  dummy337[4];                                    /* Reserved         */
    R_type1 G6MK;                                          /* G6MK             */
    R_type1 G6BA;                                          /* G6BA             */
    R_type1 G6SP;                                          /* G6SP             */
    uint8  dummy338[4];                                    /* Reserved         */
    R_type1 G7MK;                                          /* G7MK             */
    R_type1 G7BA;                                          /* G7BA             */
    R_type1 G7SP;                                          /* G7SP             */
} R_PEG;
typedef struct
{                                                          /* Module           */
    uint16 CONT;                                           /* CONT             */
    uint16 FLAG;                                           /* FLAG             */
    uint16 TYPE;                                           /* TYPE             */
    uint16 SIDE;                                           /* SIDE             */
    R_type5 ADDR;                                          /* ADDR             */
} R_SEG;


#define SELFID0                (*(volatile uint32 *)0xFFA08000)
#define SELFID1                (*(volatile uint32 *)0xFFA08004)
#define SELFID2                (*(volatile uint32 *)0xFFA08008)
#define SELFID3                (*(volatile uint32 *)0xFFA0800C)
#define SELFID4                (*(volatile uint32 *)0xFFA08010)
#define SELFID5                (*(volatile uint32 *)0xFFA08014)
#define SELFID6                (*(volatile uint32 *)0xFFA08018)
#define SELFID7                (*(volatile uint32 *)0xFFA0801C)
#define CFRDID0                (*(volatile uint32 *)0xFFA08020)
#define CFRDID1                (*(volatile uint32 *)0xFFA08024)
#define CFRDID2                (*(volatile uint32 *)0xFFA08028)
#define CFRDID3                (*(volatile uint32 *)0xFFA0802C)
#define CFRDID4                (*(volatile uint32 *)0xFFA08030)
#define CFRDID5                (*(volatile uint32 *)0xFFA08034)
#define CFRDID6                (*(volatile uint32 *)0xFFA08038)
#define CFRDID7                (*(volatile uint32 *)0xFFA0803C)
#define DFRDID0                (*(volatile uint32 *)0xFFA08040)
#define DFRDID1                (*(volatile uint32 *)0xFFA08044)
#define DFRDID2                (*(volatile uint32 *)0xFFA08048)
#define DFRDID3                (*(volatile uint32 *)0xFFA0804C)
#define DFRDID4                (*(volatile uint32 *)0xFFA08050)
#define DFRDID5                (*(volatile uint32 *)0xFFA08054)
#define DFRDID6                (*(volatile uint32 *)0xFFA08058)
#define DFRDID7                (*(volatile uint32 *)0xFFA0805C)
#define CFPEID0                (*(volatile uint32 *)0xFFA08060)
#define CFPEID1                (*(volatile uint32 *)0xFFA08064)
#define CFPEID2                (*(volatile uint32 *)0xFFA08068)
#define CFPEID3                (*(volatile uint32 *)0xFFA0806C)
#define CFPEID4                (*(volatile uint32 *)0xFFA08070)
#define CFPEID5                (*(volatile uint32 *)0xFFA08074)
#define CFPEID6                (*(volatile uint32 *)0xFFA08078)
#define CFPEID7                (*(volatile uint32 *)0xFFA0807C)
#define DFPEID0                (*(volatile uint32 *)0xFFA08080)
#define DFPEID1                (*(volatile uint32 *)0xFFA08084)
#define DFPEID2                (*(volatile uint32 *)0xFFA08088)
#define DFPEID3                (*(volatile uint32 *)0xFFA0808C)
#define DFPEID4                (*(volatile uint32 *)0xFFA08090)
#define DFPEID5                (*(volatile uint32 *)0xFFA08094)
#define DFPEID6                (*(volatile uint32 *)0xFFA08098)
#define DFPEID7                (*(volatile uint32 *)0xFFA0809C)
#define CUSTID                 (*(volatile uint32 *)0xFFA080A0)
#define DEGEMU                 (*(volatile uint32 *)0xFFA080A4)
#define SELSECLOCK             (*(volatile uint32 *)0xFFA080A8)
#define IDSTATUS               (*(volatile uint32 *)0xFFA080AC)
#define P0                     (*(volatile uint16 *)0xFFC10000)
#define PSR0                   (*(volatile uint32 *)0xFFC10004)
#define PNOT0                  (*(volatile uint16 *)0xFFC10008)
#define PPR0                   (*(volatile uint16 *)0xFFC1000C)
#define PM0                    (*(volatile uint16 *)0xFFC10010)
#define PMC0                   (*(volatile uint16 *)0xFFC10014)
#define PFC0                   (*(volatile uint16 *)0xFFC10018)
#define PFCE0                  (*(volatile uint16 *)0xFFC1001C)
#define PMSR0                  (*(volatile uint32 *)0xFFC10020)
#define PMCSR0                 (*(volatile uint32 *)0xFFC10024)
#define PINV0                  (*(volatile uint16 *)0xFFC10030)
#define P1                     (*(volatile uint16 *)0xFFC10040)
#define PSR1                   (*(volatile uint32 *)0xFFC10044)
#define PNOT1                  (*(volatile uint16 *)0xFFC10048)
#define PPR1                   (*(volatile uint16 *)0xFFC1004C)
#define PM1                    (*(volatile uint16 *)0xFFC10050)
#define PMC1                   (*(volatile uint16 *)0xFFC10054)
#define PFC1                   (*(volatile uint16 *)0xFFC10058)
#define PFCE1                  (*(volatile uint16 *)0xFFC1005C)
#define PMSR1                  (*(volatile uint32 *)0xFFC10060)
#define PMCSR1                 (*(volatile uint32 *)0xFFC10064)
#define PINV1                  (*(volatile uint16 *)0xFFC10070)
#define P2                     (*(volatile uint16 *)0xFFC10080)
#define PSR2                   (*(volatile uint32 *)0xFFC10084)
#define PNOT2                  (*(volatile uint16 *)0xFFC10088)
#define PPR2                   (*(volatile uint16 *)0xFFC1008C)
#define PM2                    (*(volatile uint16 *)0xFFC10090)
#define PMC2                   (*(volatile uint16 *)0xFFC10094)
#define PFC2                   (*(volatile uint16 *)0xFFC10098)
#define PFCE2                  (*(volatile uint16 *)0xFFC1009C)
#define PMSR2                  (*(volatile uint32 *)0xFFC100A0)
#define PMCSR2                 (*(volatile uint32 *)0xFFC100A4)
#define PINV2                  (*(volatile uint16 *)0xFFC100B0)
#define P3                     (*(volatile uint16 *)0xFFC100C0)
#define PSR3                   (*(volatile uint32 *)0xFFC100C4)
#define PNOT3                  (*(volatile uint16 *)0xFFC100C8)
#define PPR3                   (*(volatile uint16 *)0xFFC100CC)
#define PM3                    (*(volatile uint16 *)0xFFC100D0)
#define PMC3                   (*(volatile uint16 *)0xFFC100D4)
#define PFC3                   (*(volatile uint16 *)0xFFC100D8)
#define PFCE3                  (*(volatile uint16 *)0xFFC100DC)
#define PMSR3                  (*(volatile uint32 *)0xFFC100E0)
#define PMCSR3                 (*(volatile uint32 *)0xFFC100E4)
#define PINV3                  (*(volatile uint16 *)0xFFC100F0)
#define P4                     (*(volatile uint16 *)0xFFC10100)
#define PSR4                   (*(volatile uint32 *)0xFFC10104)
#define PNOT4                  (*(volatile uint16 *)0xFFC10108)
#define PPR4                   (*(volatile uint16 *)0xFFC1010C)
#define PM4                    (*(volatile uint16 *)0xFFC10110)
#define PMC4                   (*(volatile uint16 *)0xFFC10114)
#define PFC4                   (*(volatile uint16 *)0xFFC10118)
#define PFCE4                  (*(volatile uint16 *)0xFFC1011C)
#define PMSR4                  (*(volatile uint32 *)0xFFC10120)
#define PMCSR4                 (*(volatile uint32 *)0xFFC10124)
#define PINV4                  (*(volatile uint16 *)0xFFC10130)
#define P5                     (*(volatile uint16 *)0xFFC10140)
#define PSR5                   (*(volatile uint32 *)0xFFC10144)
#define PNOT5                  (*(volatile uint16 *)0xFFC10148)
#define PPR5                   (*(volatile uint16 *)0xFFC1014C)
#define PM5                    (*(volatile uint16 *)0xFFC10150)
#define PMC5                   (*(volatile uint16 *)0xFFC10154)
#define PFC5                   (*(volatile uint16 *)0xFFC10158)
#define PFCE5                  (*(volatile uint16 *)0xFFC1015C)
#define PMSR5                  (*(volatile uint32 *)0xFFC10160)
#define PMCSR5                 (*(volatile uint32 *)0xFFC10164)
#define PINV5                  (*(volatile uint16 *)0xFFC10170)
#define P6                     (*(volatile uint16 *)0xFFC10180)
#define PSR6                   (*(volatile uint32 *)0xFFC10184)
#define PNOT6                  (*(volatile uint16 *)0xFFC10188)
#define PPR6                   (*(volatile uint16 *)0xFFC1018C)
#define PM6                    (*(volatile uint16 *)0xFFC10190)
#define PMC6                   (*(volatile uint16 *)0xFFC10194)
#define PFC6                   (*(volatile uint16 *)0xFFC10198)
#define PFCE6                  (*(volatile uint16 *)0xFFC1019C)
#define PMSR6                  (*(volatile uint32 *)0xFFC101A0)
#define PMCSR6                 (*(volatile uint32 *)0xFFC101A4)
#define PINV6                  (*(volatile uint16 *)0xFFC101B0)
#define PCR0_0                 (*(volatile uint32 *)0xFFC12000)
#define PCR0_1                 (*(volatile uint32 *)0xFFC12004)
#define PCR0_2                 (*(volatile uint32 *)0xFFC12008)
#define PCR0_3                 (*(volatile uint32 *)0xFFC1200C)
#define PCR0_4                 (*(volatile uint32 *)0xFFC12010)
#define PCR0_5                 (*(volatile uint32 *)0xFFC12014)
#define PCR0_6                 (*(volatile uint32 *)0xFFC12018)
#define PCR0_7                 (*(volatile uint32 *)0xFFC1201C)
#define PCR0_8                 (*(volatile uint32 *)0xFFC12020)
#define PCR0_9                 (*(volatile uint32 *)0xFFC12024)
#define PCR0_10                (*(volatile uint32 *)0xFFC12028)
#define PCR0_13                (*(volatile uint32 *)0xFFC12034)
#define PCR0_14                (*(volatile uint32 *)0xFFC12038)
#define PCR1_1                 (*(volatile uint32 *)0xFFC12044)
#define PCR1_2                 (*(volatile uint32 *)0xFFC12048)
#define PCR1_3                 (*(volatile uint32 *)0xFFC1204C)
#define PCR1_4                 (*(volatile uint32 *)0xFFC12050)
#define PCR2_0                 (*(volatile uint32 *)0xFFC12080)
#define PCR2_1                 (*(volatile uint32 *)0xFFC12084)
#define PCR2_2                 (*(volatile uint32 *)0xFFC12088)
#define PCR2_3                 (*(volatile uint32 *)0xFFC1208C)
#define PCR2_4                 (*(volatile uint32 *)0xFFC12090)
#define PCR2_5                 (*(volatile uint32 *)0xFFC12094)
#define PCR2_6                 (*(volatile uint32 *)0xFFC12098)
#define PCR2_7                 (*(volatile uint32 *)0xFFC1209C)
#define PCR2_8                 (*(volatile uint32 *)0xFFC120A0)
#define PCR2_9                 (*(volatile uint32 *)0xFFC120A4)
#define PCR2_10                (*(volatile uint32 *)0xFFC120A8)
#define PCR2_11                (*(volatile uint32 *)0xFFC120AC)
#define PCR2_12                (*(volatile uint32 *)0xFFC120B0)
#define PCR2_13                (*(volatile uint32 *)0xFFC120B4)
#define PCR2_14                (*(volatile uint32 *)0xFFC120B8)
#define PCR2_15                (*(volatile uint32 *)0xFFC120BC)
#define PCR3_0                 (*(volatile uint32 *)0xFFC120C0)
#define PCR3_1                 (*(volatile uint32 *)0xFFC120C4)
#define PCR3_2                 (*(volatile uint32 *)0xFFC120C8)
#define PCR3_3                 (*(volatile uint32 *)0xFFC120CC)
#define PCR3_4                 (*(volatile uint32 *)0xFFC120D0)
#define PCR3_5                 (*(volatile uint32 *)0xFFC120D4)
#define PCR3_6                 (*(volatile uint32 *)0xFFC120D8)
#define PCR3_7                 (*(volatile uint32 *)0xFFC120DC)
#define PCR3_8                 (*(volatile uint32 *)0xFFC120E0)
#define PCR3_9                 (*(volatile uint32 *)0xFFC120E4)
#define PCR3_10                (*(volatile uint32 *)0xFFC120E8)
#define PCR3_11                (*(volatile uint32 *)0xFFC120EC)
#define PCR3_12                (*(volatile uint32 *)0xFFC120F0)
#define PCR3_13                (*(volatile uint32 *)0xFFC120F4)
#define PCR3_14                (*(volatile uint32 *)0xFFC120F8)
#define PCR4_0                 (*(volatile uint32 *)0xFFC12100)
#define PCR4_1                 (*(volatile uint32 *)0xFFC12104)
#define PCR4_2                 (*(volatile uint32 *)0xFFC12108)
#define PCR4_3                 (*(volatile uint32 *)0xFFC1210C)
#define PCR4_4                 (*(volatile uint32 *)0xFFC12110)
#define PCR4_5                 (*(volatile uint32 *)0xFFC12114)
#define PCR4_6                 (*(volatile uint32 *)0xFFC12118)
#define PCR4_7                 (*(volatile uint32 *)0xFFC1211C)
#define PCR4_8                 (*(volatile uint32 *)0xFFC12120)
#define PCR4_9                 (*(volatile uint32 *)0xFFC12124)
#define PCR4_10                (*(volatile uint32 *)0xFFC12128)
#define PCR4_11                (*(volatile uint32 *)0xFFC1212C)
#define PCR4_12                (*(volatile uint32 *)0xFFC12130)
#define PCR4_13                (*(volatile uint32 *)0xFFC12134)
#define PCR4_14                (*(volatile uint32 *)0xFFC12138)
#define PCR5_0                 (*(volatile uint32 *)0xFFC12140)
#define PCR5_1                 (*(volatile uint32 *)0xFFC12144)
#define PCR5_4                 (*(volatile uint32 *)0xFFC12150)
#define PCR5_5                 (*(volatile uint32 *)0xFFC12154)
#define PCR5_6                 (*(volatile uint32 *)0xFFC12158)
#define PCR5_7                 (*(volatile uint32 *)0xFFC1215C)
#define PCR5_8                 (*(volatile uint32 *)0xFFC12160)
#define PCR5_9                 (*(volatile uint32 *)0xFFC12164)
#define PCR5_10                (*(volatile uint32 *)0xFFC12168)
#define PCR5_11                (*(volatile uint32 *)0xFFC1216C)
#define PCR5_12                (*(volatile uint32 *)0xFFC12170)
#define PCR5_13                (*(volatile uint32 *)0xFFC12174)
#define PCR5_14                (*(volatile uint32 *)0xFFC12178)
#define PCR5_15                (*(volatile uint32 *)0xFFC1217C)
#define PCR6_0                 (*(volatile uint32 *)0xFFC12180)
#define PCR6_1                 (*(volatile uint32 *)0xFFC12184)
#define PCR6_2                 (*(volatile uint32 *)0xFFC12188)
#define PCR6_3                 (*(volatile uint32 *)0xFFC1218C)
#define PIBC0                  (*(volatile uint16 *)0xFFC14000)
#define PBDC0                  (*(volatile uint16 *)0xFFC14004)
#define PIPC0                  (*(volatile uint16 *)0xFFC14008)
#define PU0                    (*(volatile uint16 *)0xFFC1400C)
#define PD0                    (*(volatile uint16 *)0xFFC14010)
#define PODC0                  (*(volatile uint32 *)0xFFC14014)
#define PDSC0                  (*(volatile uint32 *)0xFFC14018)
#define PIS0                   (*(volatile uint16 *)0xFFC1401C)
#define PUCC0                  (*(volatile uint32 *)0xFFC14028)
#define PODCE0                 (*(volatile uint32 *)0xFFC14038)
#define PIBC1                  (*(volatile uint16 *)0xFFC14040)
#define PBDC1                  (*(volatile uint16 *)0xFFC14044)
#define PIPC1                  (*(volatile uint16 *)0xFFC14048)
#define PU1                    (*(volatile uint16 *)0xFFC1404C)
#define PD1                    (*(volatile uint16 *)0xFFC14050)
#define PODC1                  (*(volatile uint32 *)0xFFC14054)
#define PDSC1                  (*(volatile uint32 *)0xFFC14058)
#define PIS1                   (*(volatile uint16 *)0xFFC1405C)
#define PUCC1                  (*(volatile uint32 *)0xFFC14068)
#define PODCE1                 (*(volatile uint32 *)0xFFC14078)
#define PIBC2                  (*(volatile uint16 *)0xFFC14080)
#define PBDC2                  (*(volatile uint16 *)0xFFC14084)
#define PIPC2                  (*(volatile uint16 *)0xFFC14088)
#define PU2                    (*(volatile uint16 *)0xFFC1408C)
#define PD2                    (*(volatile uint16 *)0xFFC14090)
#define PODC2                  (*(volatile uint32 *)0xFFC14094)
#define PDSC2                  (*(volatile uint32 *)0xFFC14098)
#define PIS2                   (*(volatile uint16 *)0xFFC1409C)
#define PUCC2                  (*(volatile uint32 *)0xFFC140A8)
#define PODCE2                 (*(volatile uint32 *)0xFFC140B8)
#define PIBC3                  (*(volatile uint16 *)0xFFC140C0)
#define PBDC3                  (*(volatile uint16 *)0xFFC140C4)
#define PIPC3                  (*(volatile uint16 *)0xFFC140C8)
#define PU3                    (*(volatile uint16 *)0xFFC140CC)
#define PD3                    (*(volatile uint16 *)0xFFC140D0)
#define PODC3                  (*(volatile uint32 *)0xFFC140D4)
#define PDSC3                  (*(volatile uint32 *)0xFFC140D8)
#define PIS3                   (*(volatile uint16 *)0xFFC140DC)
#define PUCC3                  (*(volatile uint32 *)0xFFC140E8)
#define PODCE3                 (*(volatile uint32 *)0xFFC140F8)
#define PIBC4                  (*(volatile uint16 *)0xFFC14100)
#define PBDC4                  (*(volatile uint16 *)0xFFC14104)
#define PIPC4                  (*(volatile uint16 *)0xFFC14108)
#define PU4                    (*(volatile uint16 *)0xFFC1410C)
#define PD4                    (*(volatile uint16 *)0xFFC14110)
#define PODC4                  (*(volatile uint32 *)0xFFC14114)
#define PDSC4                  (*(volatile uint32 *)0xFFC14118)
#define PIS4                   (*(volatile uint16 *)0xFFC1411C)
#define PUCC4                  (*(volatile uint32 *)0xFFC14128)
#define PODCE4                 (*(volatile uint32 *)0xFFC14138)
#define PIBC5                  (*(volatile uint16 *)0xFFC14140)
#define PBDC5                  (*(volatile uint16 *)0xFFC14144)
#define PIPC5                  (*(volatile uint16 *)0xFFC14148)
#define PU5                    (*(volatile uint16 *)0xFFC1414C)
#define PD5                    (*(volatile uint16 *)0xFFC14150)
#define PODC5                  (*(volatile uint32 *)0xFFC14154)
#define PDSC5                  (*(volatile uint32 *)0xFFC14158)
#define PIS5                   (*(volatile uint16 *)0xFFC1415C)
#define PUCC5                  (*(volatile uint32 *)0xFFC14168)
#define PODCE5                 (*(volatile uint32 *)0xFFC14178)
#define PIBC6                  (*(volatile uint16 *)0xFFC14180)
#define PBDC6                  (*(volatile uint16 *)0xFFC14184)
#define PIPC6                  (*(volatile uint16 *)0xFFC14188)
#define PU6                    (*(volatile uint16 *)0xFFC1418C)
#define PD6                    (*(volatile uint16 *)0xFFC14190)
#define PODC6                  (*(volatile uint32 *)0xFFC14194)
#define PDSC6                  (*(volatile uint32 *)0xFFC14198)
#define PIS6                   (*(volatile uint16 *)0xFFC1419C)
#define PUCC6                  (*(volatile uint32 *)0xFFC141A8)
#define PODCE6                 (*(volatile uint32 *)0xFFC141B8)
#define JP0                    (*(volatile uint8  *)0xFFC20000)
#define JPSR0                  (*(volatile uint32 *)0xFFC20004)
#define JPNOT0                 (*(volatile uint8  *)0xFFC20008)
#define JPPR0                  (*(volatile uint8  *)0xFFC2000C)
#define JPM0                   (*(volatile uint8  *)0xFFC20010)
#define JPMC0                  (*(volatile uint8  *)0xFFC20014)
#define JPFCE0                 (*(volatile uint8  *)0xFFC2001C)
#define JPMSR0                 (*(volatile uint32 *)0xFFC20020)
#define JPMCSR0                (*(volatile uint32 *)0xFFC20024)
#define JPINV0                 (*(volatile uint8  *)0xFFC20030)
#define JPCR0_0                (*(volatile uint32 *)0xFFC22000)
#define JPCR0_1                (*(volatile uint32 *)0xFFC22004)
#define JPCR0_2                (*(volatile uint32 *)0xFFC22008)
#define JPCR0_3                (*(volatile uint32 *)0xFFC2200C)
#define JPCR0_4                (*(volatile uint32 *)0xFFC22010)
#define JPCR0_5                (*(volatile uint32 *)0xFFC22014)
#define JPIBC0                 (*(volatile uint8  *)0xFFC24000)
#define JPBDC0                 (*(volatile uint8  *)0xFFC24004)
#define JPU0                   (*(volatile uint8  *)0xFFC2400C)
#define JPD0                   (*(volatile uint8  *)0xFFC24010)
#define JPODC0                 (*(volatile uint32 *)0xFFC24014)
#define JPDSC0                 (*(volatile uint32 *)0xFFC24018)
#define JPIS0                  (*(volatile uint8  *)0xFFC2401C)
#define JPUCC0                 (*(volatile uint32 *)0xFFC24028)
#define JPODCE0                (*(volatile uint32 *)0xFFC24038)
#define MGDCFCTL_VCI2CFB       (*(volatile uint32 *)0xFFC48100)
#define MGDCFSTAT_VCI2CFB      (*(volatile uint32 *)0xFFC48104)
#define MGDCFTYPE_VCI2CFB      (*(volatile uint32 *)0xFFC4810C)
#define MGDCFCTL_PE1           (*(volatile uint32 *)0xFFC48200)
#define MGDCFSTAT_PE1          (*(volatile uint32 *)0xFFC48204)
#define MGDCFTYPE_PE1          (*(volatile uint32 *)0xFFC4820C)
#define MGDGRSCTL_VCI2GRAM     (*(volatile uint32 *)0xFFC49100)
#define MGDGRSSTAT_VCI2GRAM    (*(volatile uint32 *)0xFFC49104)
#define MGDGRSTYPE_VCI2GRAM    (*(volatile uint32 *)0xFFC4910C)
#define MGDGRSCTL_PE1          (*(volatile uint32 *)0xFFC49200)
#define MGDGRSSTAT_PE1         (*(volatile uint32 *)0xFFC49204)
#define MGDGRSTYPE_PE1         (*(volatile uint32 *)0xFFC4920C)
#define PGERRSTATCTL_PE1       (*(volatile uint32 *)0xFFC4A200)
#define PGERRSTAT_PE1          (*(volatile uint32 *)0xFFC4A204)
#define PGERRINFO_PE1          (*(volatile uint32 *)0xFFC4A208)
#define APBFSGDPROT_PDMACM_A   (*(volatile uint32 *)0xFFC4C000)
#define APBFSGDSPID_PDMACM_A   (*(volatile uint32 *)0xFFC4C004)
#define APBFSGDPROT_PDMACM_B   (*(volatile uint32 *)0xFFC4C008)
#define APBFSGDSPID_PDMACM_B   (*(volatile uint32 *)0xFFC4C00C)
#define APBFSGDPROT_PDMACH_A   (*(volatile uint32 *)0xFFC4C010)
#define APBFSGDSPID_PDMACH_A   (*(volatile uint32 *)0xFFC4C014)
#define APBFSGDPROT_PDMACH_B   (*(volatile uint32 *)0xFFC4C018)
#define APBFSGDSPID_PDMACH_B   (*(volatile uint32 *)0xFFC4C01C)
#define APBFSGDPROT_INTC2_A    (*(volatile uint32 *)0xFFC4C020)
#define APBFSGDSPID_INTC2_A    (*(volatile uint32 *)0xFFC4C024)
#define APBFSGDPROT_INTC2_B    (*(volatile uint32 *)0xFFC4C028)
#define APBFSGDSPID_INTC2_B    (*(volatile uint32 *)0xFFC4C02C)
#define APBFSGDPROT_PBG_A      (*(volatile uint32 *)0xFFC4C040)
#define APBFSGDSPID_PBG_A      (*(volatile uint32 *)0xFFC4C044)
#define APBFSGDPROT_PBG_B      (*(volatile uint32 *)0xFFC4C048)
#define APBFSGDSPID_PBG_B      (*(volatile uint32 *)0xFFC4C04C)
#define APBFSGDPROT_SP1_A      (*(volatile uint32 *)0xFFC4C050)
#define APBFSGDSPID_SP1_A      (*(volatile uint32 *)0xFFC4C054)
#define APBFSGDPROT_SP1_B      (*(volatile uint32 *)0xFFC4C058)
#define APBFSGDSPID_SP1_B      (*(volatile uint32 *)0xFFC4C05C)
#define APBFSGDPROT_SP4_A      (*(volatile uint32 *)0xFFC4C070)
#define APBFSGDSPID_SP4_A      (*(volatile uint32 *)0xFFC4C074)
#define APBFSGDPROT_SP4_B      (*(volatile uint32 *)0xFFC4C078)
#define APBFSGDSPID_SP4_B      (*(volatile uint32 *)0xFFC4C07C)
#define ERRSLVCTL_PFSS0        (*(volatile uint32 *)0xFFC4C800)
#define ERRSLVSTAT_PFSS0       (*(volatile uint32 *)0xFFC4C804)
#define ERRSLVTYPE_PFSS0       (*(volatile uint32 *)0xFFC4C80C)
#define ERRSLVCTL_PFSS1        (*(volatile uint32 *)0xFFC4C810)
#define ERRSLVSTAT_PFSS1       (*(volatile uint32 *)0xFFC4C814)
#define ERRSLVTYPE_PFSS1       (*(volatile uint32 *)0xFFC4C81C)
#define ERRSLVCTL_PBAREA       (*(volatile uint32 *)0xFFC4C880)
#define ERRSLVSTAT_PBAREA      (*(volatile uint32 *)0xFFC4C884)
#define ERRSLVTYPE_PBAREA      (*(volatile uint32 *)0xFFC4C88C)
#define PDMA_COMP_CNTRL        (*(volatile uint32 *)0xFFC4CA00)
#define EPC                    (*(volatile uint32 *)0xFFC58020)
#define ROMMRWE_BA             (*(volatile uint8  *)0xFFC59000)
#define ROMMR_BA               (*(volatile uint16 *)0xFFC59004)
#define FCUFAREA               (*(volatile uint8  *)0xFFC59008)
#define ROMMRWE_DCIB0          (*(volatile uint8  *)0xFFC59800)
#define ROMMR_DCIB0            (*(volatile uint16 *)0xFFC59804)
#define EEPRDCYCL0             (*(volatile uint8  *)0xFFC59810)
#define DFECCCTL0              (*(volatile uint32 *)0xFFC5B000)
#define DFERSTR0               (*(volatile uint32 *)0xFFC5B004)
#define DFERSTC0               (*(volatile uint32 *)0xFFC5B008)
#define DFOVFSTR0              (*(volatile uint32 *)0xFFC5B00C)
#define DFOVFSTC0              (*(volatile uint32 *)0xFFC5B010)
#define DFERRINT0              (*(volatile uint32 *)0xFFC5B014)
#define DFEADR0                (*(volatile uint32 *)0xFFC5B018)
#define DFTSTCTL0              (*(volatile uint32 *)0xFFC5B01C)
#define UCFERRINT              (*(volatile uint32 *)0xFFC62000)
#define UCFSERSTCLR            (*(volatile uint32 *)0xFFC62004)
#define UCFDERSTCLR            (*(volatile uint32 *)0xFFC62008)
#define UCFOVFSTR              (*(volatile uint32 *)0xFFC6200C)
#define UCFSERSTR              (*(volatile uint32 *)0xFFC62020)
#define UCFDERSTR              (*(volatile uint32 *)0xFFC62030)
#define UCF1SEDADR             (*(volatile uint32 *)0xFFC62040)
#define UCF2SEDADR             (*(volatile uint32 *)0xFFC62044)
#define UCF3SEDADR             (*(volatile uint32 *)0xFFC62048)
#define UCF4SEDADR             (*(volatile uint32 *)0xFFC6204C)
#define UCFDEDADR              (*(volatile uint32 *)0xFFC620C0)
#define CFAPCTL                (*(volatile uint32 *)0xFFC62100)
#define CFECCCTL_VCI2CFBA      (*(volatile uint32 *)0xFFC62200)
#define CFSTSTCTL_VCI2CFBA     (*(volatile uint32 *)0xFFC622F0)
#define CFECCCTL_PE1           (*(volatile uint32 *)0xFFC62400)
#define CFSTSTCTL_PE1          (*(volatile uint32 *)0xFFC624F0)
#define CFECCCTL_VCI2CFBB      (*(volatile uint32 *)0xFFC62C00)
#define CFERRINT_VCI2CFBB      (*(volatile uint32 *)0xFFC62C04)
#define CFERSTCLR_VCI2CFBB     (*(volatile uint32 *)0xFFC62C08)
#define CFOVFSTR_VCI2CFBB      (*(volatile uint32 *)0xFFC62C0C)
#define CFERSTR_VCI2CFBB       (*(volatile uint32 *)0xFFC62C10)
#define CFEADR0_VCI2CFBB       (*(volatile uint32 *)0xFFC62C50)
#define IFECCCTL_PE1           (*(volatile uint32 *)0xFFC63400)
#define IFERRINT_PE1           (*(volatile uint32 *)0xFFC63404)
#define IFERSTCLR_PE1          (*(volatile uint32 *)0xFFC63408)
#define IFOVFSTR_PE1           (*(volatile uint32 *)0xFFC6340C)
#define IFERSTR_PE1            (*(volatile uint32 *)0xFFC63410)
#define IFERADR_PE1            (*(volatile uint32 *)0xFFC63450)
#define LRECCCTL_PE1           (*(volatile uint32 *)0xFFC65400)
#define LRERRINT_PE1           (*(volatile uint32 *)0xFFC65404)
#define LRSERSTCLR_PE1         (*(volatile uint32 *)0xFFC65408)
#define LRDERSTCLR_PE1         (*(volatile uint32 *)0xFFC6540C)
#define LROVFSTR_PE1           (*(volatile uint32 *)0xFFC65410)
#define LRSERSTR_PE1           (*(volatile uint32 *)0xFFC65440)
#define LRDERSTR_PE1           (*(volatile uint32 *)0xFFC65450)
#define LR1SEDADR0_PE1         (*(volatile uint32 *)0xFFC65460)
#define LR1SEDADR1_PE1         (*(volatile uint32 *)0xFFC65464)
#define LR1SEDADR2_PE1         (*(volatile uint32 *)0xFFC65468)
#define LR1SEDADR3_PE1         (*(volatile uint32 *)0xFFC6546C)
#define LR2SEDADR0_PE1         (*(volatile uint32 *)0xFFC65470)
#define LR2SEDADR1_PE1         (*(volatile uint32 *)0xFFC65474)
#define LR2SEDADR2_PE1         (*(volatile uint32 *)0xFFC65478)
#define LR2SEDADR3_PE1         (*(volatile uint32 *)0xFFC6547C)
#define LR3SEDADR0_PE1         (*(volatile uint32 *)0xFFC65480)
#define LR3SEDADR1_PE1         (*(volatile uint32 *)0xFFC65484)
#define LR3SEDADR2_PE1         (*(volatile uint32 *)0xFFC65488)
#define LR3SEDADR3_PE1         (*(volatile uint32 *)0xFFC6548C)
#define LR4SEDADR0_PE1         (*(volatile uint32 *)0xFFC65490)
#define LR4SEDADR1_PE1         (*(volatile uint32 *)0xFFC65494)
#define LR4SEDADR2_PE1         (*(volatile uint32 *)0xFFC65498)
#define LR4SEDADR3_PE1         (*(volatile uint32 *)0xFFC6549C)
#define LR5SEDADR0_PE1         (*(volatile uint32 *)0xFFC654A0)
#define LR5SEDADR1_PE1         (*(volatile uint32 *)0xFFC654A4)
#define LR5SEDADR2_PE1         (*(volatile uint32 *)0xFFC654A8)
#define LR5SEDADR3_PE1         (*(volatile uint32 *)0xFFC654AC)
#define LR6SEDADR0_PE1         (*(volatile uint32 *)0xFFC654B0)
#define LR6SEDADR1_PE1         (*(volatile uint32 *)0xFFC654B4)
#define LR6SEDADR2_PE1         (*(volatile uint32 *)0xFFC654B8)
#define LR6SEDADR3_PE1         (*(volatile uint32 *)0xFFC654BC)
#define LR7SEDADR0_PE1         (*(volatile uint32 *)0xFFC654C0)
#define LR7SEDADR1_PE1         (*(volatile uint32 *)0xFFC654C4)
#define LR7SEDADR2_PE1         (*(volatile uint32 *)0xFFC654C8)
#define LR7SEDADR3_PE1         (*(volatile uint32 *)0xFFC654CC)
#define LR8SEDADR0_PE1         (*(volatile uint32 *)0xFFC654D0)
#define LR8SEDADR1_PE1         (*(volatile uint32 *)0xFFC654D4)
#define LR8SEDADR2_PE1         (*(volatile uint32 *)0xFFC654D8)
#define LR8SEDADR3_PE1         (*(volatile uint32 *)0xFFC654DC)
#define LRDEDADR0_PE1          (*(volatile uint32 *)0xFFC654E0)
#define LRDEDADR1_PE1          (*(volatile uint32 *)0xFFC654E4)
#define LRDEDADR2_PE1          (*(volatile uint32 *)0xFFC654E8)
#define LRDEDADR3_PE1          (*(volatile uint32 *)0xFFC654EC)
#define LRTSTCTL_PE1           (*(volatile uint32 *)0xFFC65604)
#define LRTDATBF0_PE1          (*(volatile uint32 *)0xFFC65608)
#define LRTDATBF1_PE1          (*(volatile uint32 *)0xFFC6560C)
#define LSSECCCTL_PE1          (*(volatile uint32 *)0xFFC66000)
#define LSSERRINT_PE1          (*(volatile uint32 *)0xFFC66004)
#define LSSERSTCLR_PE1         (*(volatile uint32 *)0xFFC66008)
#define LSSOVFSTR_PE1          (*(volatile uint32 *)0xFFC6600C)
#define LSSERSTR_PE1           (*(volatile uint32 *)0xFFC66010)
#define LSSEADR_PE1            (*(volatile uint32 *)0xFFC66050)
#define LSMECCCTL_PE1          (*(volatile uint32 *)0xFFC66400)
#define LSMERRINT_PE1          (*(volatile uint32 *)0xFFC66404)
#define LSMERSTCLR_PE1         (*(volatile uint32 *)0xFFC66408)
#define LSMOVFSTR_PE1          (*(volatile uint32 *)0xFFC6640C)
#define LSMERSTR_PE1           (*(volatile uint32 *)0xFFC66410)
#define LSMEADR_PE1            (*(volatile uint32 *)0xFFC66450)
#define VPECCCTL_SG0           (*(volatile uint32 *)0xFFC67000)
#define VPERRINT_SG0           (*(volatile uint32 *)0xFFC67004)
#define VPERSTCLR_SG0          (*(volatile uint32 *)0xFFC67008)
#define VPOVFSTR_SG0           (*(volatile uint32 *)0xFFC6700C)
#define VPERSTR_SG0            (*(volatile uint32 *)0xFFC67010)
#define VPEADR_SG0             (*(volatile uint32 *)0xFFC67050)
#define VPECCCTL_SG1           (*(volatile uint32 *)0xFFC67400)
#define VPERRINT_SG1           (*(volatile uint32 *)0xFFC67404)
#define VPERSTCLR_SG1          (*(volatile uint32 *)0xFFC67408)
#define VPOVFSTR_SG1           (*(volatile uint32 *)0xFFC6740C)
#define VPERSTR_SG1            (*(volatile uint32 *)0xFFC67410)
#define VPEADR_SG1             (*(volatile uint32 *)0xFFC67450)
#define VPECCCTL_SG2           (*(volatile uint32 *)0xFFC67800)
#define VPERRINT_SG2           (*(volatile uint32 *)0xFFC67804)
#define VPERSTCLR_SG2          (*(volatile uint32 *)0xFFC67808)
#define VPOVFSTR_SG2           (*(volatile uint32 *)0xFFC6780C)
#define VPERSTR_SG2            (*(volatile uint32 *)0xFFC67810)
#define VPEADR_SG2             (*(volatile uint32 *)0xFFC67850)
#define VPECCCTL_SG3           (*(volatile uint32 *)0xFFC67C00)
#define VPERRINT_SG3           (*(volatile uint32 *)0xFFC67C04)
#define VPERSTCLR_SG3          (*(volatile uint32 *)0xFFC67C08)
#define VPOVFSTR_SG3           (*(volatile uint32 *)0xFFC67C0C)
#define VPERSTR_SG3            (*(volatile uint32 *)0xFFC67C10)
#define VPEADR_SG3             (*(volatile uint32 *)0xFFC67C50)
#define VPECCCTL_SG5           (*(volatile uint32 *)0xFFC68400)
#define VPERRINT_SG5           (*(volatile uint32 *)0xFFC68404)
#define VPERSTCLR_SG5          (*(volatile uint32 *)0xFFC68408)
#define VPOVFSTR_SG5           (*(volatile uint32 *)0xFFC6840C)
#define VPERSTR_SG5            (*(volatile uint32 *)0xFFC68410)
#define VPEADR_SG5             (*(volatile uint32 *)0xFFC68450)
#define VPECCCTL_TERM_SG7      (*(volatile uint32 *)0xFFC68E00)
#define VPERRINT_TERM_SG7      (*(volatile uint32 *)0xFFC68E04)
#define VPERSTCLR_TERM_SG7     (*(volatile uint32 *)0xFFC68E08)
#define VPOVFSTR_TERM_SG7      (*(volatile uint32 *)0xFFC68E0C)
#define VPERSTR_TERM_SG7       (*(volatile uint32 *)0xFFC68E10)
#define VPEADR_TERM_SG7        (*(volatile uint32 *)0xFFC68E50)
#define VPECCCTL_VCI2VPI       (*(volatile uint32 *)0xFFC69000)
#define VPERRINT_VCI2VPI       (*(volatile uint32 *)0xFFC69004)
#define VPERSTCLR_VCI2VPI      (*(volatile uint32 *)0xFFC69008)
#define VPOVFSTR_VCI2VPI       (*(volatile uint32 *)0xFFC6900C)
#define VPERSTR_VCI2VPI        (*(volatile uint32 *)0xFFC69010)
#define VPERADR0_VCI2VPI       (*(volatile uint32 *)0xFFC69050)
#define VCECCCTL_PDMA          (*(volatile uint32 *)0xFFC6A000)
#define VCERRINT_PDMA          (*(volatile uint32 *)0xFFC6A004)
#define VCERSTCLR_PDMA         (*(volatile uint32 *)0xFFC6A008)
#define VCOVFSTR_PDMA          (*(volatile uint32 *)0xFFC6A00C)
#define VCERSTR_PDMA           (*(volatile uint32 *)0xFFC6A010)
#define VCEADR_PDMA            (*(volatile uint32 *)0xFFC6A050)
#define APECCCTL_PFSS          (*(volatile uint32 *)0xFFC6C000)
#define APERRINT_PFSS          (*(volatile uint32 *)0xFFC6C004)
#define APERSTCLR_PFSS         (*(volatile uint32 *)0xFFC6C008)
#define APOVFSTR_PFSS          (*(volatile uint32 *)0xFFC6C00C)
#define APERSTR_PFSS           (*(volatile uint32 *)0xFFC6C010)
#define APEADR_PFSS            (*(volatile uint32 *)0xFFC6C050)
#define APEC0ECCCTL            (*(volatile uint32 *)0xFFCB8000)
#define APEC0ERRINT            (*(volatile uint32 *)0xFFCB8004)
#define APEC0STCLR             (*(volatile uint32 *)0xFFCB8008)
#define APEC0OVFSTR            (*(volatile uint32 *)0xFFCB800C)
#define APEC01STERSTR          (*(volatile uint32 *)0xFFCB8010)
#define APEC01STEADR0          (*(volatile uint32 *)0xFFCB8050)
#define GREG8                  (*(volatile uint32 *)0xFFCD0020)
#define OPBT0                  (*(volatile uint32 *)0xFFCD0030)
#define OPBT1                  (*(volatile uint32 *)0xFFCD0034)
#define OPBT2                  (*(volatile uint32 *)0xFFCD0038)
#define OPBT13                 (*(volatile uint32 *)0xFFCD0064)
#define OPBT14                 (*(volatile uint32 *)0xFFCD0068)
#define OPBT15                 (*(volatile uint32 *)0xFFCD006C)
#define PRDSEL1                (*(volatile uint32 *)0xFFCD00C0)
#define PRDSEL2                (*(volatile uint32 *)0xFFCD00C4)
#define PRDSEL3                (*(volatile uint32 *)0xFFCD00C8)
#define PRDSEL4                (*(volatile uint32 *)0xFFCD00CC)
#define PRDNAME1               (*(volatile uint32 *)0xFFCD00D0)
#define PRDNAME2               (*(volatile uint32 *)0xFFCD00D4)
#define PRDNAME3               (*(volatile uint32 *)0xFFCD00D8)
#define PRDNAME4               (*(volatile uint32 *)0xFFCD00DC)
#define CHIPID1LL              (*(volatile uint32 *)0xFFCD00E0)
#define CHIPID1LH              (*(volatile uint32 *)0xFFCD00E4)
#define CHIPID1HL              (*(volatile uint32 *)0xFFCD00E8)
#define CHIPID1HH              (*(volatile uint32 *)0xFFCD00EC)
#define CHIPID2LL              (*(volatile uint32 *)0xFFCD00F0)
#define CHIPID2LH              (*(volatile uint32 *)0xFFCD00F4)
#define TESRSLT1LL             (*(volatile uint32 *)0xFFCD0100)
#define TESRSLT2HL             (*(volatile uint32 *)0xFFCD0118)
#define TESRSLT3LL             (*(volatile uint32 *)0xFFCD0120)
#define TESRSLT3LH             (*(volatile uint32 *)0xFFCD0124)
#define TESRSLT3HL             (*(volatile uint32 *)0xFFCD0128)
#define TESRSLT3HH             (*(volatile uint32 *)0xFFCD012C)
#define TESRSLT4LL             (*(volatile uint32 *)0xFFCD0130)
#define TESRSLT4LH             (*(volatile uint32 *)0xFFCD0134)
#define TESRSLT4HL             (*(volatile uint32 *)0xFFCD0138)
#define TESRSLT4HH             (*(volatile uint32 *)0xFFCD013C)
#define EMLK                   (*(volatile uint32 *)0xFFCD0140)
#define APEC4ECCCTL            (*(volatile uint32 *)0xFFCD8000)
#define APEC4ERRINT            (*(volatile uint32 *)0xFFCD8004)
#define APEC4STCLR             (*(volatile uint32 *)0xFFCD8008)
#define APEC4OVFSTR            (*(volatile uint32 *)0xFFCD800C)
#define APEC41STERSTR          (*(volatile uint32 *)0xFFCD8010)
#define APEC41STEADR0          (*(volatile uint32 *)0xFFCD8050)
#define APEC5ECCCTL            (*(volatile uint32 *)0xFFCD8200)
#define APEC5ERRINT            (*(volatile uint32 *)0xFFCD8204)
#define APEC5STCLR             (*(volatile uint32 *)0xFFCD8208)
#define APEC5OVFSTR            (*(volatile uint32 *)0xFFCD820C)
#define APEC51STERSTR          (*(volatile uint32 *)0xFFCD8210)
#define APEC51STEADR0          (*(volatile uint32 *)0xFFCD8250)
#define LBISTREF1              (*(volatile uint32 *)0xFFCDA000)
#define LBISTREF2              (*(volatile uint32 *)0xFFCDA004)
#define MBISTREF1              (*(volatile uint32 *)0xFFCDA008)
#define MBISTREF2              (*(volatile uint32 *)0xFFCDA00C)
#define LBISTSIG1              (*(volatile uint32 *)0xFFCDA010)
#define LBISTSIG2              (*(volatile uint32 *)0xFFCDA014)
#define MBISTSIG1              (*(volatile uint32 *)0xFFCDA018)
#define MBISTSIG2              (*(volatile uint32 *)0xFFCDA01C)
#define MBISTFTAGL1            (*(volatile uint32 *)0xFFCDA020)
#define MBISTFTAGH1            (*(volatile uint32 *)0xFFCDA024)
#define MBISTFTAGL2            (*(volatile uint32 *)0xFFCDA028)
#define MBISTFTAGH2            (*(volatile uint32 *)0xFFCDA02C)
#define BSEQ0ST                (*(volatile uint32 *)0xFFCDA030)
#define BSEQ0STB               (*(volatile uint32 *)0xFFCDA034)
#define BISTST                 (*(volatile uint32 *)0xFFCDA038)
#define RSENT0TSSEL            (*(volatile uint32 *)0xFFCDCF00)
#define RSENT1TSSEL            (*(volatile uint32 *)0xFFCDCF04)
#define RSENT2TSSEL            (*(volatile uint32 *)0xFFCDCF08)
#define RSENT3TSSEL            (*(volatile uint32 *)0xFFCDCF0C)
#define PINT0                  (*(volatile uint32 *)0xFFD40000)
#define PINT1                  (*(volatile uint32 *)0xFFD40004)
#define PINT2                  (*(volatile uint32 *)0xFFD40008)
#define PINT3                  (*(volatile uint32 *)0xFFD4000C)
#define PINT4                  (*(volatile uint32 *)0xFFD40010)
#define PINT5                  (*(volatile uint32 *)0xFFD40014)
#define PINT6                  (*(volatile uint32 *)0xFFD40018)
#define PINT7                  (*(volatile uint32 *)0xFFD4001C)
#define PINTCLR0               (*(volatile uint32 *)0xFFD40020)
#define PINTCLR1               (*(volatile uint32 *)0xFFD40024)
#define PINTCLR2               (*(volatile uint32 *)0xFFD40028)
#define PINTCLR3               (*(volatile uint32 *)0xFFD4002C)
#define PINTCLR4               (*(volatile uint32 *)0xFFD40030)
#define PINTCLR5               (*(volatile uint32 *)0xFFD40034)
#define PINTCLR6               (*(volatile uint32 *)0xFFD40038)
#define PINTCLR7               (*(volatile uint32 *)0xFFD4003C)
#define DTSTRGSEL0             (*(volatile uint32 *)0xFFD41000)
#define DTSTRGSEL1             (*(volatile uint32 *)0xFFD41004)
#define DTSTRGSEL2             (*(volatile uint32 *)0xFFD41008)
#define DTSTRGSEL3             (*(volatile uint32 *)0xFFD4100C)
#define FEINTF0                (*(volatile uint32 *)0xFFD42000)
#define FEINTFMSK0             (*(volatile uint32 *)0xFFD42004)
#define FEINTFC0               (*(volatile uint32 *)0xFFD42008)
#define APEC1ECCCTL            (*(volatile uint32 *)0xFFE88000)
#define APEC1ERRINT            (*(volatile uint32 *)0xFFE88004)
#define APEC1STCLR             (*(volatile uint32 *)0xFFE88008)
#define APEC1OVFSTR            (*(volatile uint32 *)0xFFE8800C)
#define APEC11STERSTR          (*(volatile uint32 *)0xFFE88010)
#define APEC11STEADR0          (*(volatile uint32 *)0xFFE88050)
#define APEC2ECCCTL            (*(volatile uint32 *)0xFFE88200)
#define APEC2ERRINT            (*(volatile uint32 *)0xFFE88204)
#define APEC2STCLR             (*(volatile uint32 *)0xFFE88208)
#define APEC2OVFSTR            (*(volatile uint32 *)0xFFE8820C)
#define APEC21STERSTR          (*(volatile uint32 *)0xFFE88210)
#define APEC21STEADR0          (*(volatile uint32 *)0xFFE88250)
#define MODE                   (*(volatile uint32 *)0xFFF80104)
#define BSEQ0CTL               (*(volatile uint32 *)0xFFF80200)
#define RESF                   (*(volatile uint32 *)0xFFF81000)
#define RESFC                  (*(volatile uint32 *)0xFFF81008)
#define SWSRESA0               (*(volatile uint32 *)0xFFF81100)
#define SWARESA0               (*(volatile uint32 *)0xFFF81200)
#define STAC_DTSRAM            (*(volatile uint32 *)0xFFF81320)
#define STAC_LM0               (*(volatile uint32 *)0xFFF81520)
#define SWLRESA3               (*(volatile uint32 *)0xFFF81708)
#define SWLRESS3               (*(volatile uint32 *)0xFFF8170C)
#define MSR_LM3                (*(volatile uint32 *)0xFFF81710)
#define STAC_LM3               (*(volatile uint32 *)0xFFF81720)
#define SWLRESA5               (*(volatile uint32 *)0xFFF81908)
#define SWLRESS5               (*(volatile uint32 *)0xFFF8190C)
#define MSR_LM5                (*(volatile uint32 *)0xFFF81910)
#define STAC_LM5               (*(volatile uint32 *)0xFFF81920)
#define SWLRESA7               (*(volatile uint32 *)0xFFF81B08)
#define SWLRESS7               (*(volatile uint32 *)0xFFF81B0C)
#define MSR_LM7                (*(volatile uint32 *)0xFFF81B10)
#define SWLRESA10              (*(volatile uint32 *)0xFFF81E08)
#define SWLRESS10              (*(volatile uint32 *)0xFFF81E0C)
#define MSR_LM10               (*(volatile uint32 *)0xFFF81E10)
#define STAC_LM10              (*(volatile uint32 *)0xFFF81E20)
#define SWLRESA11              (*(volatile uint32 *)0xFFF81F08)
#define SWLRESS11              (*(volatile uint32 *)0xFFF81F0C)
#define MSR_LM11               (*(volatile uint32 *)0xFFF81F10)
#define SWLRESA12              (*(volatile uint32 *)0xFFF82008)
#define SWLRESS12              (*(volatile uint32 *)0xFFF8200C)
#define MSR_LM12               (*(volatile uint32 *)0xFFF82010)
#define FHVE3                  (*(volatile uint32 *)0xFFF82410)
#define RESC                   (*(volatile uint32 *)0xFFF82800)
#define CVMF                   (*(volatile uint8  *)0xFFF82C00)
#define CVMDE                  (*(volatile uint8  *)0xFFF82C04)
#define CVMDL                  (*(volatile uint8  *)0xFFF82C08)
#define CVMDMASK               (*(volatile uint8  *)0xFFF82C0C)
#define CVMDIAG                (*(volatile uint8  *)0xFFF82C10)
#define CVMMON                 (*(volatile uint8  *)0xFFF82C14)
#define CVMFC                  (*(volatile uint8  *)0xFFF82C18)
#define CVMDEW                 (*(volatile uint8  *)0xFFF82C1C)
#define CVMTRMON               (*(volatile uint8  *)0xFFF82C24)
#define CVMTRCHK               (*(volatile uint8  *)0xFFF82C28)
#define CLMATEST               (*(volatile uint32 *)0xFFF83000)
#define CLMATESTS              (*(volatile uint32 *)0xFFF83004)
#define CKSC4C                 (*(volatile uint32 *)0xFFF84000)
#define CKSC4S                 (*(volatile uint32 *)0xFFF84008)
#define CLKD0DIV               (*(volatile uint32 *)0xFFF88800)
#define CLKD0STAT              (*(volatile uint32 *)0xFFF88804)
#define CLKD1DIV               (*(volatile uint32 *)0xFFF88808)
#define CLKD1STAT              (*(volatile uint32 *)0xFFF8880C)
#define CLKD2DIV               (*(volatile uint32 *)0xFFF88810)
#define CLKD2STAT              (*(volatile uint32 *)0xFFF88814)
#define CLKD3DIV               (*(volatile uint32 *)0xFFF88818)
#define CLKD3STAT              (*(volatile uint32 *)0xFFF8881C)
#define CKSC0C                 (*(volatile uint32 *)0xFFF89000)
#define CKSC0S                 (*(volatile uint32 *)0xFFF89008)
#define CKSC2C                 (*(volatile uint32 *)0xFFF89080)
#define CKSC2S                 (*(volatile uint32 *)0xFFF89088)
#define CKSC3C                 (*(volatile uint32 *)0xFFF890C0)
#define CKSC3S                 (*(volatile uint32 *)0xFFF890C8)
#define FHVE15                 (*(volatile uint32 *)0xFFF8A430)
#define APEC3ECCCTL            (*(volatile uint32 *)0xFFF98000)
#define APEC3ERRINT            (*(volatile uint32 *)0xFFF98004)
#define APEC3STCLR             (*(volatile uint32 *)0xFFF98008)
#define APEC3OVFSTR            (*(volatile uint32 *)0xFFF9800C)
#define APEC31STERSTR          (*(volatile uint32 *)0xFFF98010)
#define APEC31STEADR0          (*(volatile uint32 *)0xFFF98050)
#define EIC0                   (*(volatile uint16 *)0xFFFEEA00)
#define EIC0L                  (*(volatile uint8  *)0xFFFEEA00)
#define EIC0H                  (*(volatile uint8  *)0xFFFEEA01)
#define EIC1                   (*(volatile uint16 *)0xFFFEEA02)
#define EIC1L                  (*(volatile uint8  *)0xFFFEEA02)
#define EIC1H                  (*(volatile uint8  *)0xFFFEEA03)
#define EIC2                   (*(volatile uint16 *)0xFFFEEA04)
#define EIC2L                  (*(volatile uint8  *)0xFFFEEA04)
#define EIC2H                  (*(volatile uint8  *)0xFFFEEA05)
#define EIC3                   (*(volatile uint16 *)0xFFFEEA06)
#define EIC3L                  (*(volatile uint8  *)0xFFFEEA06)
#define EIC3H                  (*(volatile uint8  *)0xFFFEEA07)
#define EIC4                   (*(volatile uint16 *)0xFFFEEA08)
#define EIC4L                  (*(volatile uint8  *)0xFFFEEA08)
#define EIC4H                  (*(volatile uint8  *)0xFFFEEA09)
#define EIC5                   (*(volatile uint16 *)0xFFFEEA0A)
#define EIC5L                  (*(volatile uint8  *)0xFFFEEA0A)
#define EIC5H                  (*(volatile uint8  *)0xFFFEEA0B)
#define EIC6                   (*(volatile uint16 *)0xFFFEEA0C)
#define EIC6L                  (*(volatile uint8  *)0xFFFEEA0C)
#define EIC6H                  (*(volatile uint8  *)0xFFFEEA0D)
#define EIC7                   (*(volatile uint16 *)0xFFFEEA0E)
#define EIC7L                  (*(volatile uint8  *)0xFFFEEA0E)
#define EIC7H                  (*(volatile uint8  *)0xFFFEEA0F)
#define EIC8                   (*(volatile uint16 *)0xFFFEEA10)
#define EIC8L                  (*(volatile uint8  *)0xFFFEEA10)
#define EIC8H                  (*(volatile uint8  *)0xFFFEEA11)
#define EIC9                   (*(volatile uint16 *)0xFFFEEA12)
#define EIC9L                  (*(volatile uint8  *)0xFFFEEA12)
#define EIC9H                  (*(volatile uint8  *)0xFFFEEA13)
#define EIC10                  (*(volatile uint16 *)0xFFFEEA14)
#define EIC10L                 (*(volatile uint8  *)0xFFFEEA14)
#define EIC10H                 (*(volatile uint8  *)0xFFFEEA15)
#define EIC11                  (*(volatile uint16 *)0xFFFEEA16)
#define EIC11L                 (*(volatile uint8  *)0xFFFEEA16)
#define EIC11H                 (*(volatile uint8  *)0xFFFEEA17)
#define EIC12                  (*(volatile uint16 *)0xFFFEEA18)
#define EIC12L                 (*(volatile uint8  *)0xFFFEEA18)
#define EIC12H                 (*(volatile uint8  *)0xFFFEEA19)
#define EIC13                  (*(volatile uint16 *)0xFFFEEA1A)
#define EIC13L                 (*(volatile uint8  *)0xFFFEEA1A)
#define EIC13H                 (*(volatile uint8  *)0xFFFEEA1B)
#define EIC14                  (*(volatile uint16 *)0xFFFEEA1C)
#define EIC14L                 (*(volatile uint8  *)0xFFFEEA1C)
#define EIC14H                 (*(volatile uint8  *)0xFFFEEA1D)
#define EIC15                  (*(volatile uint16 *)0xFFFEEA1E)
#define EIC15L                 (*(volatile uint8  *)0xFFFEEA1E)
#define EIC15H                 (*(volatile uint8  *)0xFFFEEA1F)
#define EIC16                  (*(volatile uint16 *)0xFFFEEA20)
#define EIC16L                 (*(volatile uint8  *)0xFFFEEA20)
#define EIC16H                 (*(volatile uint8  *)0xFFFEEA21)
#define EIC17                  (*(volatile uint16 *)0xFFFEEA22)
#define EIC17L                 (*(volatile uint8  *)0xFFFEEA22)
#define EIC17H                 (*(volatile uint8  *)0xFFFEEA23)
#define EIC18                  (*(volatile uint16 *)0xFFFEEA24)
#define EIC18L                 (*(volatile uint8  *)0xFFFEEA24)
#define EIC18H                 (*(volatile uint8  *)0xFFFEEA25)
#define EIC19                  (*(volatile uint16 *)0xFFFEEA26)
#define EIC19L                 (*(volatile uint8  *)0xFFFEEA26)
#define EIC19H                 (*(volatile uint8  *)0xFFFEEA27)
#define EIC20                  (*(volatile uint16 *)0xFFFEEA28)
#define EIC20L                 (*(volatile uint8  *)0xFFFEEA28)
#define EIC20H                 (*(volatile uint8  *)0xFFFEEA29)
#define EIC21                  (*(volatile uint16 *)0xFFFEEA2A)
#define EIC21L                 (*(volatile uint8  *)0xFFFEEA2A)
#define EIC21H                 (*(volatile uint8  *)0xFFFEEA2B)
#define EIC22                  (*(volatile uint16 *)0xFFFEEA2C)
#define EIC22L                 (*(volatile uint8  *)0xFFFEEA2C)
#define EIC22H                 (*(volatile uint8  *)0xFFFEEA2D)
#define EIC23                  (*(volatile uint16 *)0xFFFEEA2E)
#define EIC23L                 (*(volatile uint8  *)0xFFFEEA2E)
#define EIC23H                 (*(volatile uint8  *)0xFFFEEA2F)
#define EIC24                  (*(volatile uint16 *)0xFFFEEA30)
#define EIC24L                 (*(volatile uint8  *)0xFFFEEA30)
#define EIC24H                 (*(volatile uint8  *)0xFFFEEA31)
#define EIC25                  (*(volatile uint16 *)0xFFFEEA32)
#define EIC25L                 (*(volatile uint8  *)0xFFFEEA32)
#define EIC25H                 (*(volatile uint8  *)0xFFFEEA33)
#define EIC26                  (*(volatile uint16 *)0xFFFEEA34)
#define EIC26L                 (*(volatile uint8  *)0xFFFEEA34)
#define EIC26H                 (*(volatile uint8  *)0xFFFEEA35)
#define EIC27                  (*(volatile uint16 *)0xFFFEEA36)
#define EIC27L                 (*(volatile uint8  *)0xFFFEEA36)
#define EIC27H                 (*(volatile uint8  *)0xFFFEEA37)
#define EIC28                  (*(volatile uint16 *)0xFFFEEA38)
#define EIC28L                 (*(volatile uint8  *)0xFFFEEA38)
#define EIC28H                 (*(volatile uint8  *)0xFFFEEA39)
#define EIC29                  (*(volatile uint16 *)0xFFFEEA3A)
#define EIC29L                 (*(volatile uint8  *)0xFFFEEA3A)
#define EIC29H                 (*(volatile uint8  *)0xFFFEEA3B)
#define EIC30                  (*(volatile uint16 *)0xFFFEEA3C)
#define EIC30L                 (*(volatile uint8  *)0xFFFEEA3C)
#define EIC30H                 (*(volatile uint8  *)0xFFFEEA3D)
#define EIC31                  (*(volatile uint16 *)0xFFFEEA3E)
#define EIC31L                 (*(volatile uint8  *)0xFFFEEA3E)
#define EIC31H                 (*(volatile uint8  *)0xFFFEEA3F)
#define FNC                    (*(volatile uint16 *)0xFFFEEA78)
#define FNCH                   (*(volatile uint8  *)0xFFFEEA79)
#define FIC                    (*(volatile uint16 *)0xFFFEEA7A)
#define FICH                   (*(volatile uint8  *)0xFFFEEA7B)
#define IMR0                   (*(volatile uint32 *)0xFFFEEAF0)
#define EIBD0                  (*(volatile uint32 *)0xFFFEEB00)
#define EIBD1                  (*(volatile uint32 *)0xFFFEEB04)
#define EIBD2                  (*(volatile uint32 *)0xFFFEEB08)
#define EIBD3                  (*(volatile uint32 *)0xFFFEEB0C)
#define EIBD4                  (*(volatile uint32 *)0xFFFEEB10)
#define EIBD5                  (*(volatile uint32 *)0xFFFEEB14)
#define EIBD6                  (*(volatile uint32 *)0xFFFEEB18)
#define EIBD7                  (*(volatile uint32 *)0xFFFEEB1C)
#define EIBD8                  (*(volatile uint32 *)0xFFFEEB20)
#define EIBD9                  (*(volatile uint32 *)0xFFFEEB24)
#define EIBD10                 (*(volatile uint32 *)0xFFFEEB28)
#define EIBD11                 (*(volatile uint32 *)0xFFFEEB2C)
#define EIBD12                 (*(volatile uint32 *)0xFFFEEB30)
#define EIBD13                 (*(volatile uint32 *)0xFFFEEB34)
#define EIBD14                 (*(volatile uint32 *)0xFFFEEB38)
#define EIBD15                 (*(volatile uint32 *)0xFFFEEB3C)
#define EIBD16                 (*(volatile uint32 *)0xFFFEEB40)
#define EIBD17                 (*(volatile uint32 *)0xFFFEEB44)
#define EIBD18                 (*(volatile uint32 *)0xFFFEEB48)
#define EIBD19                 (*(volatile uint32 *)0xFFFEEB4C)
#define EIBD20                 (*(volatile uint32 *)0xFFFEEB50)
#define EIBD21                 (*(volatile uint32 *)0xFFFEEB54)
#define EIBD22                 (*(volatile uint32 *)0xFFFEEB58)
#define EIBD23                 (*(volatile uint32 *)0xFFFEEB5C)
#define EIBD24                 (*(volatile uint32 *)0xFFFEEB60)
#define EIBD25                 (*(volatile uint32 *)0xFFFEEB64)
#define EIBD26                 (*(volatile uint32 *)0xFFFEEB68)
#define EIBD27                 (*(volatile uint32 *)0xFFFEEB6C)
#define EIBD28                 (*(volatile uint32 *)0xFFFEEB70)
#define EIBD29                 (*(volatile uint32 *)0xFFFEEB74)
#define EIBD30                 (*(volatile uint32 *)0xFFFEEB78)
#define EIBD31                 (*(volatile uint32 *)0xFFFEEB7C)
#define CMPTST0                (*(volatile uint32 *)0xFFFEED00)
#define CMPTST1                (*(volatile uint32 *)0xFFFEED04)
#define TM_VER                 (*(volatile uint32 *)0xFFFF7800)
#define TM_CC                  (*(volatile uint32 *)0xFFFF7808)
#define TMA_ME                 (*(volatile uint32 *)0xFFFF7810)
#define TMA_MS                 (*(volatile uint32 *)0xFFFF7814)
#define TMA_MA0                (*(volatile uint32 *)0xFFFF7840)
#define DMACTL                 (*(volatile uint32 *)0xFFFF8000)
#define DTSCTL1                (*(volatile uint32 *)0xFFFF8010)
#define DTSCTL2                (*(volatile uint32 *)0xFFFF8014)
#define DTSSTS                 (*(volatile uint32 *)0xFFFF8018)
#define DMACER                 (*(volatile uint32 *)0xFFFF8020)
#define DTSER1                 (*(volatile uint32 *)0xFFFF8024)
#define DTSER2                 (*(volatile uint32 *)0xFFFF8028)
#define DTSERC                 (*(volatile uint32 *)0xFFFF802C)
#define DM0CMV                 (*(volatile uint32 *)0xFFFF8030)
#define DTSCMV                 (*(volatile uint32 *)0xFFFF8038)
#define CMVC                   (*(volatile uint32 *)0xFFFF803C)
#define TFRSTS                 (*(volatile uint32 *)0xFFFF804C)
#define DTSPR0                 (*(volatile uint32 *)0xFFFF8060)
#define DTSPR1                 (*(volatile uint32 *)0xFFFF8064)
#define DTSPR2                 (*(volatile uint32 *)0xFFFF8068)
#define DTSPR3                 (*(volatile uint32 *)0xFFFF806C)
#define DTSPR4                 (*(volatile uint32 *)0xFFFF8070)
#define DTSPR5                 (*(volatile uint32 *)0xFFFF8074)
#define DTSPR6                 (*(volatile uint32 *)0xFFFF8078)
#define DTSPR7                 (*(volatile uint32 *)0xFFFF807C)
#define DTRECCTL               (*(volatile uint32 *)0xFFFF8080)
#define DTRERINT               (*(volatile uint32 *)0xFFFF8084)
#define DTRTSCTL               (*(volatile uint32 *)0xFFFF8094)
#define DTRTWDAT               (*(volatile uint32 *)0xFFFF8098)
#define DTRTRDAT               (*(volatile uint32 *)0xFFFF809C)
#define ADECCTCL               (*(volatile uint32 *)0xFFFF80A0)
#define ADECCTDT               (*(volatile uint32 *)0xFFFF80A4)
#define DM00CM                 (*(volatile uint32 *)0xFFFF8100)
#define DM01CM                 (*(volatile uint32 *)0xFFFF8104)
#define DM02CM                 (*(volatile uint32 *)0xFFFF8108)
#define DM03CM                 (*(volatile uint32 *)0xFFFF810C)
#define DM04CM                 (*(volatile uint32 *)0xFFFF8110)
#define DM05CM                 (*(volatile uint32 *)0xFFFF8114)
#define DM06CM                 (*(volatile uint32 *)0xFFFF8118)
#define DM07CM                 (*(volatile uint32 *)0xFFFF811C)
#define DTS000CM               (*(volatile uint32 *)0xFFFF8200)
#define DTS001CM               (*(volatile uint32 *)0xFFFF8204)
#define DTS002CM               (*(volatile uint32 *)0xFFFF8208)
#define DTS003CM               (*(volatile uint32 *)0xFFFF820C)
#define DTS004CM               (*(volatile uint32 *)0xFFFF8210)
#define DTS005CM               (*(volatile uint32 *)0xFFFF8214)
#define DTS006CM               (*(volatile uint32 *)0xFFFF8218)
#define DTS007CM               (*(volatile uint32 *)0xFFFF821C)
#define DTS008CM               (*(volatile uint32 *)0xFFFF8220)
#define DTS009CM               (*(volatile uint32 *)0xFFFF8224)
#define DTS010CM               (*(volatile uint32 *)0xFFFF8228)
#define DTS011CM               (*(volatile uint32 *)0xFFFF822C)
#define DTS012CM               (*(volatile uint32 *)0xFFFF8230)
#define DTS013CM               (*(volatile uint32 *)0xFFFF8234)
#define DTS014CM               (*(volatile uint32 *)0xFFFF8238)
#define DTS015CM               (*(volatile uint32 *)0xFFFF823C)
#define DTS016CM               (*(volatile uint32 *)0xFFFF8240)
#define DTS017CM               (*(volatile uint32 *)0xFFFF8244)
#define DTS018CM               (*(volatile uint32 *)0xFFFF8248)
#define DTS019CM               (*(volatile uint32 *)0xFFFF824C)
#define DTS020CM               (*(volatile uint32 *)0xFFFF8250)
#define DTS021CM               (*(volatile uint32 *)0xFFFF8254)
#define DTS022CM               (*(volatile uint32 *)0xFFFF8258)
#define DTS023CM               (*(volatile uint32 *)0xFFFF825C)
#define DTS024CM               (*(volatile uint32 *)0xFFFF8260)
#define DTS025CM               (*(volatile uint32 *)0xFFFF8264)
#define DTS026CM               (*(volatile uint32 *)0xFFFF8268)
#define DTS027CM               (*(volatile uint32 *)0xFFFF826C)
#define DTS028CM               (*(volatile uint32 *)0xFFFF8270)
#define DTS029CM               (*(volatile uint32 *)0xFFFF8274)
#define DTS030CM               (*(volatile uint32 *)0xFFFF8278)
#define DTS031CM               (*(volatile uint32 *)0xFFFF827C)
#define DTS032CM               (*(volatile uint32 *)0xFFFF8280)
#define DTS033CM               (*(volatile uint32 *)0xFFFF8284)
#define DTS034CM               (*(volatile uint32 *)0xFFFF8288)
#define DTS035CM               (*(volatile uint32 *)0xFFFF828C)
#define DTS036CM               (*(volatile uint32 *)0xFFFF8290)
#define DTS037CM               (*(volatile uint32 *)0xFFFF8294)
#define DTS038CM               (*(volatile uint32 *)0xFFFF8298)
#define DTS039CM               (*(volatile uint32 *)0xFFFF829C)
#define DTS040CM               (*(volatile uint32 *)0xFFFF82A0)
#define DTS041CM               (*(volatile uint32 *)0xFFFF82A4)
#define DTS042CM               (*(volatile uint32 *)0xFFFF82A8)
#define DTS043CM               (*(volatile uint32 *)0xFFFF82AC)
#define DTS044CM               (*(volatile uint32 *)0xFFFF82B0)
#define DTS045CM               (*(volatile uint32 *)0xFFFF82B4)
#define DTS046CM               (*(volatile uint32 *)0xFFFF82B8)
#define DTS047CM               (*(volatile uint32 *)0xFFFF82BC)
#define DTS048CM               (*(volatile uint32 *)0xFFFF82C0)
#define DTS049CM               (*(volatile uint32 *)0xFFFF82C4)
#define DTS050CM               (*(volatile uint32 *)0xFFFF82C8)
#define DTS051CM               (*(volatile uint32 *)0xFFFF82CC)
#define DTS052CM               (*(volatile uint32 *)0xFFFF82D0)
#define DTS053CM               (*(volatile uint32 *)0xFFFF82D4)
#define DTS054CM               (*(volatile uint32 *)0xFFFF82D8)
#define DTS055CM               (*(volatile uint32 *)0xFFFF82DC)
#define DTS056CM               (*(volatile uint32 *)0xFFFF82E0)
#define DTS057CM               (*(volatile uint32 *)0xFFFF82E4)
#define DTS058CM               (*(volatile uint32 *)0xFFFF82E8)
#define DTS059CM               (*(volatile uint32 *)0xFFFF82EC)
#define DTS060CM               (*(volatile uint32 *)0xFFFF82F0)
#define DTS061CM               (*(volatile uint32 *)0xFFFF82F4)
#define DTS062CM               (*(volatile uint32 *)0xFFFF82F8)
#define DTS063CM               (*(volatile uint32 *)0xFFFF82FC)
#define DTS064CM               (*(volatile uint32 *)0xFFFF8300)
#define DTS065CM               (*(volatile uint32 *)0xFFFF8304)
#define DTS066CM               (*(volatile uint32 *)0xFFFF8308)
#define DTS067CM               (*(volatile uint32 *)0xFFFF830C)
#define DTS068CM               (*(volatile uint32 *)0xFFFF8310)
#define DTS069CM               (*(volatile uint32 *)0xFFFF8314)
#define DTS070CM               (*(volatile uint32 *)0xFFFF8318)
#define DTS071CM               (*(volatile uint32 *)0xFFFF831C)
#define DTS072CM               (*(volatile uint32 *)0xFFFF8320)
#define DTS073CM               (*(volatile uint32 *)0xFFFF8324)
#define DTS074CM               (*(volatile uint32 *)0xFFFF8328)
#define DTS075CM               (*(volatile uint32 *)0xFFFF832C)
#define DTS076CM               (*(volatile uint32 *)0xFFFF8330)
#define DTS077CM               (*(volatile uint32 *)0xFFFF8334)
#define DTS078CM               (*(volatile uint32 *)0xFFFF8338)
#define DTS079CM               (*(volatile uint32 *)0xFFFF833C)
#define DTS080CM               (*(volatile uint32 *)0xFFFF8340)
#define DTS081CM               (*(volatile uint32 *)0xFFFF8344)
#define DTS082CM               (*(volatile uint32 *)0xFFFF8348)
#define DTS083CM               (*(volatile uint32 *)0xFFFF834C)
#define DTS084CM               (*(volatile uint32 *)0xFFFF8350)
#define DTS085CM               (*(volatile uint32 *)0xFFFF8354)
#define DTS086CM               (*(volatile uint32 *)0xFFFF8358)
#define DTS087CM               (*(volatile uint32 *)0xFFFF835C)
#define DTS088CM               (*(volatile uint32 *)0xFFFF8360)
#define DTS089CM               (*(volatile uint32 *)0xFFFF8364)
#define DTS090CM               (*(volatile uint32 *)0xFFFF8368)
#define DTS091CM               (*(volatile uint32 *)0xFFFF836C)
#define DTS092CM               (*(volatile uint32 *)0xFFFF8370)
#define DTS093CM               (*(volatile uint32 *)0xFFFF8374)
#define DTS094CM               (*(volatile uint32 *)0xFFFF8378)
#define DTS095CM               (*(volatile uint32 *)0xFFFF837C)
#define DTS096CM               (*(volatile uint32 *)0xFFFF8380)
#define DTS097CM               (*(volatile uint32 *)0xFFFF8384)
#define DTS098CM               (*(volatile uint32 *)0xFFFF8388)
#define DTS099CM               (*(volatile uint32 *)0xFFFF838C)
#define DTS100CM               (*(volatile uint32 *)0xFFFF8390)
#define DTS101CM               (*(volatile uint32 *)0xFFFF8394)
#define DTS102CM               (*(volatile uint32 *)0xFFFF8398)
#define DTS103CM               (*(volatile uint32 *)0xFFFF839C)
#define DTS104CM               (*(volatile uint32 *)0xFFFF83A0)
#define DTS105CM               (*(volatile uint32 *)0xFFFF83A4)
#define DTS106CM               (*(volatile uint32 *)0xFFFF83A8)
#define DTS107CM               (*(volatile uint32 *)0xFFFF83AC)
#define DTS108CM               (*(volatile uint32 *)0xFFFF83B0)
#define DTS109CM               (*(volatile uint32 *)0xFFFF83B4)
#define DTS110CM               (*(volatile uint32 *)0xFFFF83B8)
#define DTS111CM               (*(volatile uint32 *)0xFFFF83BC)
#define DTS112CM               (*(volatile uint32 *)0xFFFF83C0)
#define DTS113CM               (*(volatile uint32 *)0xFFFF83C4)
#define DTS114CM               (*(volatile uint32 *)0xFFFF83C8)
#define DTS115CM               (*(volatile uint32 *)0xFFFF83CC)
#define DTS116CM               (*(volatile uint32 *)0xFFFF83D0)
#define DTS117CM               (*(volatile uint32 *)0xFFFF83D4)
#define DTS118CM               (*(volatile uint32 *)0xFFFF83D8)
#define DTS119CM               (*(volatile uint32 *)0xFFFF83DC)
#define DTS120CM               (*(volatile uint32 *)0xFFFF83E0)
#define DTS121CM               (*(volatile uint32 *)0xFFFF83E4)
#define DTS122CM               (*(volatile uint32 *)0xFFFF83E8)
#define DTS123CM               (*(volatile uint32 *)0xFFFF83EC)
#define DTS124CM               (*(volatile uint32 *)0xFFFF83F0)
#define DTS125CM               (*(volatile uint32 *)0xFFFF83F4)
#define DTS126CM               (*(volatile uint32 *)0xFFFF83F8)
#define DTS127CM               (*(volatile uint32 *)0xFFFF83FC)
#define DSA0                   (*(volatile uint32 *)0xFFFF8400)
#define DDA0                   (*(volatile uint32 *)0xFFFF8404)
#define DTC0                   (*(volatile uint32 *)0xFFFF8408)
#define DTCT0                  (*(volatile uint32 *)0xFFFF840C)
#define DRSA0                  (*(volatile uint32 *)0xFFFF8410)
#define DRDA0                  (*(volatile uint32 *)0xFFFF8414)
#define DRTC0                  (*(volatile uint32 *)0xFFFF8418)
#define DTCC0                  (*(volatile uint32 *)0xFFFF841C)
#define DCEN0                  (*(volatile uint32 *)0xFFFF8420)
#define DCST0                  (*(volatile uint32 *)0xFFFF8424)
#define DCSTS0                 (*(volatile uint32 *)0xFFFF8428)
#define DCSTC0                 (*(volatile uint32 *)0xFFFF842C)
#define DTFR0                  (*(volatile uint32 *)0xFFFF8430)
#define DTFRRQ0                (*(volatile uint32 *)0xFFFF8434)
#define DTFRRQC0               (*(volatile uint32 *)0xFFFF8438)
#define DSA1                   (*(volatile uint32 *)0xFFFF8440)
#define DDA1                   (*(volatile uint32 *)0xFFFF8444)
#define DTC1                   (*(volatile uint32 *)0xFFFF8448)
#define DTCT1                  (*(volatile uint32 *)0xFFFF844C)
#define DRSA1                  (*(volatile uint32 *)0xFFFF8450)
#define DRDA1                  (*(volatile uint32 *)0xFFFF8454)
#define DRTC1                  (*(volatile uint32 *)0xFFFF8458)
#define DTCC1                  (*(volatile uint32 *)0xFFFF845C)
#define DCEN1                  (*(volatile uint32 *)0xFFFF8460)
#define DCST1                  (*(volatile uint32 *)0xFFFF8464)
#define DCSTS1                 (*(volatile uint32 *)0xFFFF8468)
#define DCSTC1                 (*(volatile uint32 *)0xFFFF846C)
#define DTFR1                  (*(volatile uint32 *)0xFFFF8470)
#define DTFRRQ1                (*(volatile uint32 *)0xFFFF8474)
#define DTFRRQC1               (*(volatile uint32 *)0xFFFF8478)
#define DSA2                   (*(volatile uint32 *)0xFFFF8480)
#define DDA2                   (*(volatile uint32 *)0xFFFF8484)
#define DTC2                   (*(volatile uint32 *)0xFFFF8488)
#define DTCT2                  (*(volatile uint32 *)0xFFFF848C)
#define DRSA2                  (*(volatile uint32 *)0xFFFF8490)
#define DRDA2                  (*(volatile uint32 *)0xFFFF8494)
#define DRTC2                  (*(volatile uint32 *)0xFFFF8498)
#define DTCC2                  (*(volatile uint32 *)0xFFFF849C)
#define DCEN2                  (*(volatile uint32 *)0xFFFF84A0)
#define DCST2                  (*(volatile uint32 *)0xFFFF84A4)
#define DCSTS2                 (*(volatile uint32 *)0xFFFF84A8)
#define DCSTC2                 (*(volatile uint32 *)0xFFFF84AC)
#define DTFR2                  (*(volatile uint32 *)0xFFFF84B0)
#define DTFRRQ2                (*(volatile uint32 *)0xFFFF84B4)
#define DTFRRQC2               (*(volatile uint32 *)0xFFFF84B8)
#define DSA3                   (*(volatile uint32 *)0xFFFF84C0)
#define DDA3                   (*(volatile uint32 *)0xFFFF84C4)
#define DTC3                   (*(volatile uint32 *)0xFFFF84C8)
#define DTCT3                  (*(volatile uint32 *)0xFFFF84CC)
#define DRSA3                  (*(volatile uint32 *)0xFFFF84D0)
#define DRDA3                  (*(volatile uint32 *)0xFFFF84D4)
#define DRTC3                  (*(volatile uint32 *)0xFFFF84D8)
#define DTCC3                  (*(volatile uint32 *)0xFFFF84DC)
#define DCEN3                  (*(volatile uint32 *)0xFFFF84E0)
#define DCST3                  (*(volatile uint32 *)0xFFFF84E4)
#define DCSTS3                 (*(volatile uint32 *)0xFFFF84E8)
#define DCSTC3                 (*(volatile uint32 *)0xFFFF84EC)
#define DTFR3                  (*(volatile uint32 *)0xFFFF84F0)
#define DTFRRQ3                (*(volatile uint32 *)0xFFFF84F4)
#define DTFRRQC3               (*(volatile uint32 *)0xFFFF84F8)
#define DSA4                   (*(volatile uint32 *)0xFFFF8500)
#define DDA4                   (*(volatile uint32 *)0xFFFF8504)
#define DTC4                   (*(volatile uint32 *)0xFFFF8508)
#define DTCT4                  (*(volatile uint32 *)0xFFFF850C)
#define DRSA4                  (*(volatile uint32 *)0xFFFF8510)
#define DRDA4                  (*(volatile uint32 *)0xFFFF8514)
#define DRTC4                  (*(volatile uint32 *)0xFFFF8518)
#define DTCC4                  (*(volatile uint32 *)0xFFFF851C)
#define DCEN4                  (*(volatile uint32 *)0xFFFF8520)
#define DCST4                  (*(volatile uint32 *)0xFFFF8524)
#define DCSTS4                 (*(volatile uint32 *)0xFFFF8528)
#define DCSTC4                 (*(volatile uint32 *)0xFFFF852C)
#define DTFR4                  (*(volatile uint32 *)0xFFFF8530)
#define DTFRRQ4                (*(volatile uint32 *)0xFFFF8534)
#define DTFRRQC4               (*(volatile uint32 *)0xFFFF8538)
#define DSA5                   (*(volatile uint32 *)0xFFFF8540)
#define DDA5                   (*(volatile uint32 *)0xFFFF8544)
#define DTC5                   (*(volatile uint32 *)0xFFFF8548)
#define DTCT5                  (*(volatile uint32 *)0xFFFF854C)
#define DRSA5                  (*(volatile uint32 *)0xFFFF8550)
#define DRDA5                  (*(volatile uint32 *)0xFFFF8554)
#define DRTC5                  (*(volatile uint32 *)0xFFFF8558)
#define DTCC5                  (*(volatile uint32 *)0xFFFF855C)
#define DCEN5                  (*(volatile uint32 *)0xFFFF8560)
#define DCST5                  (*(volatile uint32 *)0xFFFF8564)
#define DCSTS5                 (*(volatile uint32 *)0xFFFF8568)
#define DCSTC5                 (*(volatile uint32 *)0xFFFF856C)
#define DTFR5                  (*(volatile uint32 *)0xFFFF8570)
#define DTFRRQ5                (*(volatile uint32 *)0xFFFF8574)
#define DTFRRQC5               (*(volatile uint32 *)0xFFFF8578)
#define DSA6                   (*(volatile uint32 *)0xFFFF8580)
#define DDA6                   (*(volatile uint32 *)0xFFFF8584)
#define DTC6                   (*(volatile uint32 *)0xFFFF8588)
#define DTCT6                  (*(volatile uint32 *)0xFFFF858C)
#define DRSA6                  (*(volatile uint32 *)0xFFFF8590)
#define DRDA6                  (*(volatile uint32 *)0xFFFF8594)
#define DRTC6                  (*(volatile uint32 *)0xFFFF8598)
#define DTCC6                  (*(volatile uint32 *)0xFFFF859C)
#define DCEN6                  (*(volatile uint32 *)0xFFFF85A0)
#define DCST6                  (*(volatile uint32 *)0xFFFF85A4)
#define DCSTS6                 (*(volatile uint32 *)0xFFFF85A8)
#define DCSTC6                 (*(volatile uint32 *)0xFFFF85AC)
#define DTFR6                  (*(volatile uint32 *)0xFFFF85B0)
#define DTFRRQ6                (*(volatile uint32 *)0xFFFF85B4)
#define DTFRRQC6               (*(volatile uint32 *)0xFFFF85B8)
#define DSA7                   (*(volatile uint32 *)0xFFFF85C0)
#define DDA7                   (*(volatile uint32 *)0xFFFF85C4)
#define DTC7                   (*(volatile uint32 *)0xFFFF85C8)
#define DTCT7                  (*(volatile uint32 *)0xFFFF85CC)
#define DRSA7                  (*(volatile uint32 *)0xFFFF85D0)
#define DRDA7                  (*(volatile uint32 *)0xFFFF85D4)
#define DRTC7                  (*(volatile uint32 *)0xFFFF85D8)
#define DTCC7                  (*(volatile uint32 *)0xFFFF85DC)
#define DCEN7                  (*(volatile uint32 *)0xFFFF85E0)
#define DCST7                  (*(volatile uint32 *)0xFFFF85E4)
#define DCSTS7                 (*(volatile uint32 *)0xFFFF85E8)
#define DCSTC7                 (*(volatile uint32 *)0xFFFF85EC)
#define DTFR7                  (*(volatile uint32 *)0xFFFF85F0)
#define DTFRRQ7                (*(volatile uint32 *)0xFFFF85F4)
#define DTFRRQC7               (*(volatile uint32 *)0xFFFF85F8)
#define DTSA000                (*(volatile uint32 *)0xFFFF9000)
#define DTDA000                (*(volatile uint32 *)0xFFFF9004)
#define DTTC000                (*(volatile uint32 *)0xFFFF9008)
#define DTTCT000               (*(volatile uint32 *)0xFFFF900C)
#define DTRSA000               (*(volatile uint32 *)0xFFFF9010)
#define DTRDA000               (*(volatile uint32 *)0xFFFF9014)
#define DTRTC000               (*(volatile uint32 *)0xFFFF9018)
#define DTTCC000               (*(volatile uint32 *)0xFFFF901C)
#define DTFSL000               (*(volatile uint32 *)0xFFFF9020)
#define DTFST000               (*(volatile uint32 *)0xFFFF9024)
#define DTFSS000               (*(volatile uint32 *)0xFFFF9028)
#define DTFSC000               (*(volatile uint32 *)0xFFFF902C)
#define DTSA001                (*(volatile uint32 *)0xFFFF9040)
#define DTDA001                (*(volatile uint32 *)0xFFFF9044)
#define DTTC001                (*(volatile uint32 *)0xFFFF9048)
#define DTTCT001               (*(volatile uint32 *)0xFFFF904C)
#define DTRSA001               (*(volatile uint32 *)0xFFFF9050)
#define DTRDA001               (*(volatile uint32 *)0xFFFF9054)
#define DTRTC001               (*(volatile uint32 *)0xFFFF9058)
#define DTTCC001               (*(volatile uint32 *)0xFFFF905C)
#define DTFSL001               (*(volatile uint32 *)0xFFFF9060)
#define DTFST001               (*(volatile uint32 *)0xFFFF9064)
#define DTFSS001               (*(volatile uint32 *)0xFFFF9068)
#define DTFSC001               (*(volatile uint32 *)0xFFFF906C)
#define DTSA002                (*(volatile uint32 *)0xFFFF9080)
#define DTDA002                (*(volatile uint32 *)0xFFFF9084)
#define DTTC002                (*(volatile uint32 *)0xFFFF9088)
#define DTTCT002               (*(volatile uint32 *)0xFFFF908C)
#define DTRSA002               (*(volatile uint32 *)0xFFFF9090)
#define DTRDA002               (*(volatile uint32 *)0xFFFF9094)
#define DTRTC002               (*(volatile uint32 *)0xFFFF9098)
#define DTTCC002               (*(volatile uint32 *)0xFFFF909C)
#define DTFSL002               (*(volatile uint32 *)0xFFFF90A0)
#define DTFST002               (*(volatile uint32 *)0xFFFF90A4)
#define DTFSS002               (*(volatile uint32 *)0xFFFF90A8)
#define DTFSC002               (*(volatile uint32 *)0xFFFF90AC)
#define DTSA003                (*(volatile uint32 *)0xFFFF90C0)
#define DTDA003                (*(volatile uint32 *)0xFFFF90C4)
#define DTTC003                (*(volatile uint32 *)0xFFFF90C8)
#define DTTCT003               (*(volatile uint32 *)0xFFFF90CC)
#define DTRSA003               (*(volatile uint32 *)0xFFFF90D0)
#define DTRDA003               (*(volatile uint32 *)0xFFFF90D4)
#define DTRTC003               (*(volatile uint32 *)0xFFFF90D8)
#define DTTCC003               (*(volatile uint32 *)0xFFFF90DC)
#define DTFSL003               (*(volatile uint32 *)0xFFFF90E0)
#define DTFST003               (*(volatile uint32 *)0xFFFF90E4)
#define DTFSS003               (*(volatile uint32 *)0xFFFF90E8)
#define DTFSC003               (*(volatile uint32 *)0xFFFF90EC)
#define DTSA004                (*(volatile uint32 *)0xFFFF9100)
#define DTDA004                (*(volatile uint32 *)0xFFFF9104)
#define DTTC004                (*(volatile uint32 *)0xFFFF9108)
#define DTTCT004               (*(volatile uint32 *)0xFFFF910C)
#define DTRSA004               (*(volatile uint32 *)0xFFFF9110)
#define DTRDA004               (*(volatile uint32 *)0xFFFF9114)
#define DTRTC004               (*(volatile uint32 *)0xFFFF9118)
#define DTTCC004               (*(volatile uint32 *)0xFFFF911C)
#define DTFSL004               (*(volatile uint32 *)0xFFFF9120)
#define DTFST004               (*(volatile uint32 *)0xFFFF9124)
#define DTFSS004               (*(volatile uint32 *)0xFFFF9128)
#define DTFSC004               (*(volatile uint32 *)0xFFFF912C)
#define DTSA005                (*(volatile uint32 *)0xFFFF9140)
#define DTDA005                (*(volatile uint32 *)0xFFFF9144)
#define DTTC005                (*(volatile uint32 *)0xFFFF9148)
#define DTTCT005               (*(volatile uint32 *)0xFFFF914C)
#define DTRSA005               (*(volatile uint32 *)0xFFFF9150)
#define DTRDA005               (*(volatile uint32 *)0xFFFF9154)
#define DTRTC005               (*(volatile uint32 *)0xFFFF9158)
#define DTTCC005               (*(volatile uint32 *)0xFFFF915C)
#define DTFSL005               (*(volatile uint32 *)0xFFFF9160)
#define DTFST005               (*(volatile uint32 *)0xFFFF9164)
#define DTFSS005               (*(volatile uint32 *)0xFFFF9168)
#define DTFSC005               (*(volatile uint32 *)0xFFFF916C)
#define DTSA006                (*(volatile uint32 *)0xFFFF9180)
#define DTDA006                (*(volatile uint32 *)0xFFFF9184)
#define DTTC006                (*(volatile uint32 *)0xFFFF9188)
#define DTTCT006               (*(volatile uint32 *)0xFFFF918C)
#define DTRSA006               (*(volatile uint32 *)0xFFFF9190)
#define DTRDA006               (*(volatile uint32 *)0xFFFF9194)
#define DTRTC006               (*(volatile uint32 *)0xFFFF9198)
#define DTTCC006               (*(volatile uint32 *)0xFFFF919C)
#define DTFSL006               (*(volatile uint32 *)0xFFFF91A0)
#define DTFST006               (*(volatile uint32 *)0xFFFF91A4)
#define DTFSS006               (*(volatile uint32 *)0xFFFF91A8)
#define DTFSC006               (*(volatile uint32 *)0xFFFF91AC)
#define DTSA007                (*(volatile uint32 *)0xFFFF91C0)
#define DTDA007                (*(volatile uint32 *)0xFFFF91C4)
#define DTTC007                (*(volatile uint32 *)0xFFFF91C8)
#define DTTCT007               (*(volatile uint32 *)0xFFFF91CC)
#define DTRSA007               (*(volatile uint32 *)0xFFFF91D0)
#define DTRDA007               (*(volatile uint32 *)0xFFFF91D4)
#define DTRTC007               (*(volatile uint32 *)0xFFFF91D8)
#define DTTCC007               (*(volatile uint32 *)0xFFFF91DC)
#define DTFSL007               (*(volatile uint32 *)0xFFFF91E0)
#define DTFST007               (*(volatile uint32 *)0xFFFF91E4)
#define DTFSS007               (*(volatile uint32 *)0xFFFF91E8)
#define DTFSC007               (*(volatile uint32 *)0xFFFF91EC)
#define DTSA008                (*(volatile uint32 *)0xFFFF9200)
#define DTDA008                (*(volatile uint32 *)0xFFFF9204)
#define DTTC008                (*(volatile uint32 *)0xFFFF9208)
#define DTTCT008               (*(volatile uint32 *)0xFFFF920C)
#define DTRSA008               (*(volatile uint32 *)0xFFFF9210)
#define DTRDA008               (*(volatile uint32 *)0xFFFF9214)
#define DTRTC008               (*(volatile uint32 *)0xFFFF9218)
#define DTTCC008               (*(volatile uint32 *)0xFFFF921C)
#define DTFSL008               (*(volatile uint32 *)0xFFFF9220)
#define DTFST008               (*(volatile uint32 *)0xFFFF9224)
#define DTFSS008               (*(volatile uint32 *)0xFFFF9228)
#define DTFSC008               (*(volatile uint32 *)0xFFFF922C)
#define DTSA009                (*(volatile uint32 *)0xFFFF9240)
#define DTDA009                (*(volatile uint32 *)0xFFFF9244)
#define DTTC009                (*(volatile uint32 *)0xFFFF9248)
#define DTTCT009               (*(volatile uint32 *)0xFFFF924C)
#define DTRSA009               (*(volatile uint32 *)0xFFFF9250)
#define DTRDA009               (*(volatile uint32 *)0xFFFF9254)
#define DTRTC009               (*(volatile uint32 *)0xFFFF9258)
#define DTTCC009               (*(volatile uint32 *)0xFFFF925C)
#define DTFSL009               (*(volatile uint32 *)0xFFFF9260)
#define DTFST009               (*(volatile uint32 *)0xFFFF9264)
#define DTFSS009               (*(volatile uint32 *)0xFFFF9268)
#define DTFSC009               (*(volatile uint32 *)0xFFFF926C)
#define DTSA010                (*(volatile uint32 *)0xFFFF9280)
#define DTDA010                (*(volatile uint32 *)0xFFFF9284)
#define DTTC010                (*(volatile uint32 *)0xFFFF9288)
#define DTTCT010               (*(volatile uint32 *)0xFFFF928C)
#define DTRSA010               (*(volatile uint32 *)0xFFFF9290)
#define DTRDA010               (*(volatile uint32 *)0xFFFF9294)
#define DTRTC010               (*(volatile uint32 *)0xFFFF9298)
#define DTTCC010               (*(volatile uint32 *)0xFFFF929C)
#define DTFSL010               (*(volatile uint32 *)0xFFFF92A0)
#define DTFST010               (*(volatile uint32 *)0xFFFF92A4)
#define DTFSS010               (*(volatile uint32 *)0xFFFF92A8)
#define DTFSC010               (*(volatile uint32 *)0xFFFF92AC)
#define DTSA011                (*(volatile uint32 *)0xFFFF92C0)
#define DTDA011                (*(volatile uint32 *)0xFFFF92C4)
#define DTTC011                (*(volatile uint32 *)0xFFFF92C8)
#define DTTCT011               (*(volatile uint32 *)0xFFFF92CC)
#define DTRSA011               (*(volatile uint32 *)0xFFFF92D0)
#define DTRDA011               (*(volatile uint32 *)0xFFFF92D4)
#define DTRTC011               (*(volatile uint32 *)0xFFFF92D8)
#define DTTCC011               (*(volatile uint32 *)0xFFFF92DC)
#define DTFSL011               (*(volatile uint32 *)0xFFFF92E0)
#define DTFST011               (*(volatile uint32 *)0xFFFF92E4)
#define DTFSS011               (*(volatile uint32 *)0xFFFF92E8)
#define DTFSC011               (*(volatile uint32 *)0xFFFF92EC)
#define DTSA012                (*(volatile uint32 *)0xFFFF9300)
#define DTDA012                (*(volatile uint32 *)0xFFFF9304)
#define DTTC012                (*(volatile uint32 *)0xFFFF9308)
#define DTTCT012               (*(volatile uint32 *)0xFFFF930C)
#define DTRSA012               (*(volatile uint32 *)0xFFFF9310)
#define DTRDA012               (*(volatile uint32 *)0xFFFF9314)
#define DTRTC012               (*(volatile uint32 *)0xFFFF9318)
#define DTTCC012               (*(volatile uint32 *)0xFFFF931C)
#define DTFSL012               (*(volatile uint32 *)0xFFFF9320)
#define DTFST012               (*(volatile uint32 *)0xFFFF9324)
#define DTFSS012               (*(volatile uint32 *)0xFFFF9328)
#define DTFSC012               (*(volatile uint32 *)0xFFFF932C)
#define DTSA013                (*(volatile uint32 *)0xFFFF9340)
#define DTDA013                (*(volatile uint32 *)0xFFFF9344)
#define DTTC013                (*(volatile uint32 *)0xFFFF9348)
#define DTTCT013               (*(volatile uint32 *)0xFFFF934C)
#define DTRSA013               (*(volatile uint32 *)0xFFFF9350)
#define DTRDA013               (*(volatile uint32 *)0xFFFF9354)
#define DTRTC013               (*(volatile uint32 *)0xFFFF9358)
#define DTTCC013               (*(volatile uint32 *)0xFFFF935C)
#define DTFSL013               (*(volatile uint32 *)0xFFFF9360)
#define DTFST013               (*(volatile uint32 *)0xFFFF9364)
#define DTFSS013               (*(volatile uint32 *)0xFFFF9368)
#define DTFSC013               (*(volatile uint32 *)0xFFFF936C)
#define DTSA014                (*(volatile uint32 *)0xFFFF9380)
#define DTDA014                (*(volatile uint32 *)0xFFFF9384)
#define DTTC014                (*(volatile uint32 *)0xFFFF9388)
#define DTTCT014               (*(volatile uint32 *)0xFFFF938C)
#define DTRSA014               (*(volatile uint32 *)0xFFFF9390)
#define DTRDA014               (*(volatile uint32 *)0xFFFF9394)
#define DTRTC014               (*(volatile uint32 *)0xFFFF9398)
#define DTTCC014               (*(volatile uint32 *)0xFFFF939C)
#define DTFSL014               (*(volatile uint32 *)0xFFFF93A0)
#define DTFST014               (*(volatile uint32 *)0xFFFF93A4)
#define DTFSS014               (*(volatile uint32 *)0xFFFF93A8)
#define DTFSC014               (*(volatile uint32 *)0xFFFF93AC)
#define DTSA015                (*(volatile uint32 *)0xFFFF93C0)
#define DTDA015                (*(volatile uint32 *)0xFFFF93C4)
#define DTTC015                (*(volatile uint32 *)0xFFFF93C8)
#define DTTCT015               (*(volatile uint32 *)0xFFFF93CC)
#define DTRSA015               (*(volatile uint32 *)0xFFFF93D0)
#define DTRDA015               (*(volatile uint32 *)0xFFFF93D4)
#define DTRTC015               (*(volatile uint32 *)0xFFFF93D8)
#define DTTCC015               (*(volatile uint32 *)0xFFFF93DC)
#define DTFSL015               (*(volatile uint32 *)0xFFFF93E0)
#define DTFST015               (*(volatile uint32 *)0xFFFF93E4)
#define DTFSS015               (*(volatile uint32 *)0xFFFF93E8)
#define DTFSC015               (*(volatile uint32 *)0xFFFF93EC)
#define DTSA016                (*(volatile uint32 *)0xFFFF9400)
#define DTDA016                (*(volatile uint32 *)0xFFFF9404)
#define DTTC016                (*(volatile uint32 *)0xFFFF9408)
#define DTTCT016               (*(volatile uint32 *)0xFFFF940C)
#define DTRSA016               (*(volatile uint32 *)0xFFFF9410)
#define DTRDA016               (*(volatile uint32 *)0xFFFF9414)
#define DTRTC016               (*(volatile uint32 *)0xFFFF9418)
#define DTTCC016               (*(volatile uint32 *)0xFFFF941C)
#define DTFSL016               (*(volatile uint32 *)0xFFFF9420)
#define DTFST016               (*(volatile uint32 *)0xFFFF9424)
#define DTFSS016               (*(volatile uint32 *)0xFFFF9428)
#define DTFSC016               (*(volatile uint32 *)0xFFFF942C)
#define DTSA017                (*(volatile uint32 *)0xFFFF9440)
#define DTDA017                (*(volatile uint32 *)0xFFFF9444)
#define DTTC017                (*(volatile uint32 *)0xFFFF9448)
#define DTTCT017               (*(volatile uint32 *)0xFFFF944C)
#define DTRSA017               (*(volatile uint32 *)0xFFFF9450)
#define DTRDA017               (*(volatile uint32 *)0xFFFF9454)
#define DTRTC017               (*(volatile uint32 *)0xFFFF9458)
#define DTTCC017               (*(volatile uint32 *)0xFFFF945C)
#define DTFSL017               (*(volatile uint32 *)0xFFFF9460)
#define DTFST017               (*(volatile uint32 *)0xFFFF9464)
#define DTFSS017               (*(volatile uint32 *)0xFFFF9468)
#define DTFSC017               (*(volatile uint32 *)0xFFFF946C)
#define DTSA018                (*(volatile uint32 *)0xFFFF9480)
#define DTDA018                (*(volatile uint32 *)0xFFFF9484)
#define DTTC018                (*(volatile uint32 *)0xFFFF9488)
#define DTTCT018               (*(volatile uint32 *)0xFFFF948C)
#define DTRSA018               (*(volatile uint32 *)0xFFFF9490)
#define DTRDA018               (*(volatile uint32 *)0xFFFF9494)
#define DTRTC018               (*(volatile uint32 *)0xFFFF9498)
#define DTTCC018               (*(volatile uint32 *)0xFFFF949C)
#define DTFSL018               (*(volatile uint32 *)0xFFFF94A0)
#define DTFST018               (*(volatile uint32 *)0xFFFF94A4)
#define DTFSS018               (*(volatile uint32 *)0xFFFF94A8)
#define DTFSC018               (*(volatile uint32 *)0xFFFF94AC)
#define DTSA019                (*(volatile uint32 *)0xFFFF94C0)
#define DTDA019                (*(volatile uint32 *)0xFFFF94C4)
#define DTTC019                (*(volatile uint32 *)0xFFFF94C8)
#define DTTCT019               (*(volatile uint32 *)0xFFFF94CC)
#define DTRSA019               (*(volatile uint32 *)0xFFFF94D0)
#define DTRDA019               (*(volatile uint32 *)0xFFFF94D4)
#define DTRTC019               (*(volatile uint32 *)0xFFFF94D8)
#define DTTCC019               (*(volatile uint32 *)0xFFFF94DC)
#define DTFSL019               (*(volatile uint32 *)0xFFFF94E0)
#define DTFST019               (*(volatile uint32 *)0xFFFF94E4)
#define DTFSS019               (*(volatile uint32 *)0xFFFF94E8)
#define DTFSC019               (*(volatile uint32 *)0xFFFF94EC)
#define DTSA020                (*(volatile uint32 *)0xFFFF9500)
#define DTDA020                (*(volatile uint32 *)0xFFFF9504)
#define DTTC020                (*(volatile uint32 *)0xFFFF9508)
#define DTTCT020               (*(volatile uint32 *)0xFFFF950C)
#define DTRSA020               (*(volatile uint32 *)0xFFFF9510)
#define DTRDA020               (*(volatile uint32 *)0xFFFF9514)
#define DTRTC020               (*(volatile uint32 *)0xFFFF9518)
#define DTTCC020               (*(volatile uint32 *)0xFFFF951C)
#define DTFSL020               (*(volatile uint32 *)0xFFFF9520)
#define DTFST020               (*(volatile uint32 *)0xFFFF9524)
#define DTFSS020               (*(volatile uint32 *)0xFFFF9528)
#define DTFSC020               (*(volatile uint32 *)0xFFFF952C)
#define DTSA021                (*(volatile uint32 *)0xFFFF9540)
#define DTDA021                (*(volatile uint32 *)0xFFFF9544)
#define DTTC021                (*(volatile uint32 *)0xFFFF9548)
#define DTTCT021               (*(volatile uint32 *)0xFFFF954C)
#define DTRSA021               (*(volatile uint32 *)0xFFFF9550)
#define DTRDA021               (*(volatile uint32 *)0xFFFF9554)
#define DTRTC021               (*(volatile uint32 *)0xFFFF9558)
#define DTTCC021               (*(volatile uint32 *)0xFFFF955C)
#define DTFSL021               (*(volatile uint32 *)0xFFFF9560)
#define DTFST021               (*(volatile uint32 *)0xFFFF9564)
#define DTFSS021               (*(volatile uint32 *)0xFFFF9568)
#define DTFSC021               (*(volatile uint32 *)0xFFFF956C)
#define DTSA022                (*(volatile uint32 *)0xFFFF9580)
#define DTDA022                (*(volatile uint32 *)0xFFFF9584)
#define DTTC022                (*(volatile uint32 *)0xFFFF9588)
#define DTTCT022               (*(volatile uint32 *)0xFFFF958C)
#define DTRSA022               (*(volatile uint32 *)0xFFFF9590)
#define DTRDA022               (*(volatile uint32 *)0xFFFF9594)
#define DTRTC022               (*(volatile uint32 *)0xFFFF9598)
#define DTTCC022               (*(volatile uint32 *)0xFFFF959C)
#define DTFSL022               (*(volatile uint32 *)0xFFFF95A0)
#define DTFST022               (*(volatile uint32 *)0xFFFF95A4)
#define DTFSS022               (*(volatile uint32 *)0xFFFF95A8)
#define DTFSC022               (*(volatile uint32 *)0xFFFF95AC)
#define DTSA023                (*(volatile uint32 *)0xFFFF95C0)
#define DTDA023                (*(volatile uint32 *)0xFFFF95C4)
#define DTTC023                (*(volatile uint32 *)0xFFFF95C8)
#define DTTCT023               (*(volatile uint32 *)0xFFFF95CC)
#define DTRSA023               (*(volatile uint32 *)0xFFFF95D0)
#define DTRDA023               (*(volatile uint32 *)0xFFFF95D4)
#define DTRTC023               (*(volatile uint32 *)0xFFFF95D8)
#define DTTCC023               (*(volatile uint32 *)0xFFFF95DC)
#define DTFSL023               (*(volatile uint32 *)0xFFFF95E0)
#define DTFST023               (*(volatile uint32 *)0xFFFF95E4)
#define DTFSS023               (*(volatile uint32 *)0xFFFF95E8)
#define DTFSC023               (*(volatile uint32 *)0xFFFF95EC)
#define DTSA024                (*(volatile uint32 *)0xFFFF9600)
#define DTDA024                (*(volatile uint32 *)0xFFFF9604)
#define DTTC024                (*(volatile uint32 *)0xFFFF9608)
#define DTTCT024               (*(volatile uint32 *)0xFFFF960C)
#define DTRSA024               (*(volatile uint32 *)0xFFFF9610)
#define DTRDA024               (*(volatile uint32 *)0xFFFF9614)
#define DTRTC024               (*(volatile uint32 *)0xFFFF9618)
#define DTTCC024               (*(volatile uint32 *)0xFFFF961C)
#define DTFSL024               (*(volatile uint32 *)0xFFFF9620)
#define DTFST024               (*(volatile uint32 *)0xFFFF9624)
#define DTFSS024               (*(volatile uint32 *)0xFFFF9628)
#define DTFSC024               (*(volatile uint32 *)0xFFFF962C)
#define DTSA025                (*(volatile uint32 *)0xFFFF9640)
#define DTDA025                (*(volatile uint32 *)0xFFFF9644)
#define DTTC025                (*(volatile uint32 *)0xFFFF9648)
#define DTTCT025               (*(volatile uint32 *)0xFFFF964C)
#define DTRSA025               (*(volatile uint32 *)0xFFFF9650)
#define DTRDA025               (*(volatile uint32 *)0xFFFF9654)
#define DTRTC025               (*(volatile uint32 *)0xFFFF9658)
#define DTTCC025               (*(volatile uint32 *)0xFFFF965C)
#define DTFSL025               (*(volatile uint32 *)0xFFFF9660)
#define DTFST025               (*(volatile uint32 *)0xFFFF9664)
#define DTFSS025               (*(volatile uint32 *)0xFFFF9668)
#define DTFSC025               (*(volatile uint32 *)0xFFFF966C)
#define DTSA026                (*(volatile uint32 *)0xFFFF9680)
#define DTDA026                (*(volatile uint32 *)0xFFFF9684)
#define DTTC026                (*(volatile uint32 *)0xFFFF9688)
#define DTTCT026               (*(volatile uint32 *)0xFFFF968C)
#define DTRSA026               (*(volatile uint32 *)0xFFFF9690)
#define DTRDA026               (*(volatile uint32 *)0xFFFF9694)
#define DTRTC026               (*(volatile uint32 *)0xFFFF9698)
#define DTTCC026               (*(volatile uint32 *)0xFFFF969C)
#define DTFSL026               (*(volatile uint32 *)0xFFFF96A0)
#define DTFST026               (*(volatile uint32 *)0xFFFF96A4)
#define DTFSS026               (*(volatile uint32 *)0xFFFF96A8)
#define DTFSC026               (*(volatile uint32 *)0xFFFF96AC)
#define DTSA027                (*(volatile uint32 *)0xFFFF96C0)
#define DTDA027                (*(volatile uint32 *)0xFFFF96C4)
#define DTTC027                (*(volatile uint32 *)0xFFFF96C8)
#define DTTCT027               (*(volatile uint32 *)0xFFFF96CC)
#define DTRSA027               (*(volatile uint32 *)0xFFFF96D0)
#define DTRDA027               (*(volatile uint32 *)0xFFFF96D4)
#define DTRTC027               (*(volatile uint32 *)0xFFFF96D8)
#define DTTCC027               (*(volatile uint32 *)0xFFFF96DC)
#define DTFSL027               (*(volatile uint32 *)0xFFFF96E0)
#define DTFST027               (*(volatile uint32 *)0xFFFF96E4)
#define DTFSS027               (*(volatile uint32 *)0xFFFF96E8)
#define DTFSC027               (*(volatile uint32 *)0xFFFF96EC)
#define DTSA028                (*(volatile uint32 *)0xFFFF9700)
#define DTDA028                (*(volatile uint32 *)0xFFFF9704)
#define DTTC028                (*(volatile uint32 *)0xFFFF9708)
#define DTTCT028               (*(volatile uint32 *)0xFFFF970C)
#define DTRSA028               (*(volatile uint32 *)0xFFFF9710)
#define DTRDA028               (*(volatile uint32 *)0xFFFF9714)
#define DTRTC028               (*(volatile uint32 *)0xFFFF9718)
#define DTTCC028               (*(volatile uint32 *)0xFFFF971C)
#define DTFSL028               (*(volatile uint32 *)0xFFFF9720)
#define DTFST028               (*(volatile uint32 *)0xFFFF9724)
#define DTFSS028               (*(volatile uint32 *)0xFFFF9728)
#define DTFSC028               (*(volatile uint32 *)0xFFFF972C)
#define DTSA029                (*(volatile uint32 *)0xFFFF9740)
#define DTDA029                (*(volatile uint32 *)0xFFFF9744)
#define DTTC029                (*(volatile uint32 *)0xFFFF9748)
#define DTTCT029               (*(volatile uint32 *)0xFFFF974C)
#define DTRSA029               (*(volatile uint32 *)0xFFFF9750)
#define DTRDA029               (*(volatile uint32 *)0xFFFF9754)
#define DTRTC029               (*(volatile uint32 *)0xFFFF9758)
#define DTTCC029               (*(volatile uint32 *)0xFFFF975C)
#define DTFSL029               (*(volatile uint32 *)0xFFFF9760)
#define DTFST029               (*(volatile uint32 *)0xFFFF9764)
#define DTFSS029               (*(volatile uint32 *)0xFFFF9768)
#define DTFSC029               (*(volatile uint32 *)0xFFFF976C)
#define DTSA030                (*(volatile uint32 *)0xFFFF9780)
#define DTDA030                (*(volatile uint32 *)0xFFFF9784)
#define DTTC030                (*(volatile uint32 *)0xFFFF9788)
#define DTTCT030               (*(volatile uint32 *)0xFFFF978C)
#define DTRSA030               (*(volatile uint32 *)0xFFFF9790)
#define DTRDA030               (*(volatile uint32 *)0xFFFF9794)
#define DTRTC030               (*(volatile uint32 *)0xFFFF9798)
#define DTTCC030               (*(volatile uint32 *)0xFFFF979C)
#define DTFSL030               (*(volatile uint32 *)0xFFFF97A0)
#define DTFST030               (*(volatile uint32 *)0xFFFF97A4)
#define DTFSS030               (*(volatile uint32 *)0xFFFF97A8)
#define DTFSC030               (*(volatile uint32 *)0xFFFF97AC)
#define DTSA031                (*(volatile uint32 *)0xFFFF97C0)
#define DTDA031                (*(volatile uint32 *)0xFFFF97C4)
#define DTTC031                (*(volatile uint32 *)0xFFFF97C8)
#define DTTCT031               (*(volatile uint32 *)0xFFFF97CC)
#define DTRSA031               (*(volatile uint32 *)0xFFFF97D0)
#define DTRDA031               (*(volatile uint32 *)0xFFFF97D4)
#define DTRTC031               (*(volatile uint32 *)0xFFFF97D8)
#define DTTCC031               (*(volatile uint32 *)0xFFFF97DC)
#define DTFSL031               (*(volatile uint32 *)0xFFFF97E0)
#define DTFST031               (*(volatile uint32 *)0xFFFF97E4)
#define DTFSS031               (*(volatile uint32 *)0xFFFF97E8)
#define DTFSC031               (*(volatile uint32 *)0xFFFF97EC)
#define DTSA032                (*(volatile uint32 *)0xFFFF9800)
#define DTDA032                (*(volatile uint32 *)0xFFFF9804)
#define DTTC032                (*(volatile uint32 *)0xFFFF9808)
#define DTTCT032               (*(volatile uint32 *)0xFFFF980C)
#define DTRSA032               (*(volatile uint32 *)0xFFFF9810)
#define DTRDA032               (*(volatile uint32 *)0xFFFF9814)
#define DTRTC032               (*(volatile uint32 *)0xFFFF9818)
#define DTTCC032               (*(volatile uint32 *)0xFFFF981C)
#define DTFSL032               (*(volatile uint32 *)0xFFFF9820)
#define DTFST032               (*(volatile uint32 *)0xFFFF9824)
#define DTFSS032               (*(volatile uint32 *)0xFFFF9828)
#define DTFSC032               (*(volatile uint32 *)0xFFFF982C)
#define DTSA033                (*(volatile uint32 *)0xFFFF9840)
#define DTDA033                (*(volatile uint32 *)0xFFFF9844)
#define DTTC033                (*(volatile uint32 *)0xFFFF9848)
#define DTTCT033               (*(volatile uint32 *)0xFFFF984C)
#define DTRSA033               (*(volatile uint32 *)0xFFFF9850)
#define DTRDA033               (*(volatile uint32 *)0xFFFF9854)
#define DTRTC033               (*(volatile uint32 *)0xFFFF9858)
#define DTTCC033               (*(volatile uint32 *)0xFFFF985C)
#define DTFSL033               (*(volatile uint32 *)0xFFFF9860)
#define DTFST033               (*(volatile uint32 *)0xFFFF9864)
#define DTFSS033               (*(volatile uint32 *)0xFFFF9868)
#define DTFSC033               (*(volatile uint32 *)0xFFFF986C)
#define DTSA034                (*(volatile uint32 *)0xFFFF9880)
#define DTDA034                (*(volatile uint32 *)0xFFFF9884)
#define DTTC034                (*(volatile uint32 *)0xFFFF9888)
#define DTTCT034               (*(volatile uint32 *)0xFFFF988C)
#define DTRSA034               (*(volatile uint32 *)0xFFFF9890)
#define DTRDA034               (*(volatile uint32 *)0xFFFF9894)
#define DTRTC034               (*(volatile uint32 *)0xFFFF9898)
#define DTTCC034               (*(volatile uint32 *)0xFFFF989C)
#define DTFSL034               (*(volatile uint32 *)0xFFFF98A0)
#define DTFST034               (*(volatile uint32 *)0xFFFF98A4)
#define DTFSS034               (*(volatile uint32 *)0xFFFF98A8)
#define DTFSC034               (*(volatile uint32 *)0xFFFF98AC)
#define DTSA035                (*(volatile uint32 *)0xFFFF98C0)
#define DTDA035                (*(volatile uint32 *)0xFFFF98C4)
#define DTTC035                (*(volatile uint32 *)0xFFFF98C8)
#define DTTCT035               (*(volatile uint32 *)0xFFFF98CC)
#define DTRSA035               (*(volatile uint32 *)0xFFFF98D0)
#define DTRDA035               (*(volatile uint32 *)0xFFFF98D4)
#define DTRTC035               (*(volatile uint32 *)0xFFFF98D8)
#define DTTCC035               (*(volatile uint32 *)0xFFFF98DC)
#define DTFSL035               (*(volatile uint32 *)0xFFFF98E0)
#define DTFST035               (*(volatile uint32 *)0xFFFF98E4)
#define DTFSS035               (*(volatile uint32 *)0xFFFF98E8)
#define DTFSC035               (*(volatile uint32 *)0xFFFF98EC)
#define DTSA036                (*(volatile uint32 *)0xFFFF9900)
#define DTDA036                (*(volatile uint32 *)0xFFFF9904)
#define DTTC036                (*(volatile uint32 *)0xFFFF9908)
#define DTTCT036               (*(volatile uint32 *)0xFFFF990C)
#define DTRSA036               (*(volatile uint32 *)0xFFFF9910)
#define DTRDA036               (*(volatile uint32 *)0xFFFF9914)
#define DTRTC036               (*(volatile uint32 *)0xFFFF9918)
#define DTTCC036               (*(volatile uint32 *)0xFFFF991C)
#define DTFSL036               (*(volatile uint32 *)0xFFFF9920)
#define DTFST036               (*(volatile uint32 *)0xFFFF9924)
#define DTFSS036               (*(volatile uint32 *)0xFFFF9928)
#define DTFSC036               (*(volatile uint32 *)0xFFFF992C)
#define DTSA037                (*(volatile uint32 *)0xFFFF9940)
#define DTDA037                (*(volatile uint32 *)0xFFFF9944)
#define DTTC037                (*(volatile uint32 *)0xFFFF9948)
#define DTTCT037               (*(volatile uint32 *)0xFFFF994C)
#define DTRSA037               (*(volatile uint32 *)0xFFFF9950)
#define DTRDA037               (*(volatile uint32 *)0xFFFF9954)
#define DTRTC037               (*(volatile uint32 *)0xFFFF9958)
#define DTTCC037               (*(volatile uint32 *)0xFFFF995C)
#define DTFSL037               (*(volatile uint32 *)0xFFFF9960)
#define DTFST037               (*(volatile uint32 *)0xFFFF9964)
#define DTFSS037               (*(volatile uint32 *)0xFFFF9968)
#define DTFSC037               (*(volatile uint32 *)0xFFFF996C)
#define DTSA038                (*(volatile uint32 *)0xFFFF9980)
#define DTDA038                (*(volatile uint32 *)0xFFFF9984)
#define DTTC038                (*(volatile uint32 *)0xFFFF9988)
#define DTTCT038               (*(volatile uint32 *)0xFFFF998C)
#define DTRSA038               (*(volatile uint32 *)0xFFFF9990)
#define DTRDA038               (*(volatile uint32 *)0xFFFF9994)
#define DTRTC038               (*(volatile uint32 *)0xFFFF9998)
#define DTTCC038               (*(volatile uint32 *)0xFFFF999C)
#define DTFSL038               (*(volatile uint32 *)0xFFFF99A0)
#define DTFST038               (*(volatile uint32 *)0xFFFF99A4)
#define DTFSS038               (*(volatile uint32 *)0xFFFF99A8)
#define DTFSC038               (*(volatile uint32 *)0xFFFF99AC)
#define DTSA039                (*(volatile uint32 *)0xFFFF99C0)
#define DTDA039                (*(volatile uint32 *)0xFFFF99C4)
#define DTTC039                (*(volatile uint32 *)0xFFFF99C8)
#define DTTCT039               (*(volatile uint32 *)0xFFFF99CC)
#define DTRSA039               (*(volatile uint32 *)0xFFFF99D0)
#define DTRDA039               (*(volatile uint32 *)0xFFFF99D4)
#define DTRTC039               (*(volatile uint32 *)0xFFFF99D8)
#define DTTCC039               (*(volatile uint32 *)0xFFFF99DC)
#define DTFSL039               (*(volatile uint32 *)0xFFFF99E0)
#define DTFST039               (*(volatile uint32 *)0xFFFF99E4)
#define DTFSS039               (*(volatile uint32 *)0xFFFF99E8)
#define DTFSC039               (*(volatile uint32 *)0xFFFF99EC)
#define DTSA040                (*(volatile uint32 *)0xFFFF9A00)
#define DTDA040                (*(volatile uint32 *)0xFFFF9A04)
#define DTTC040                (*(volatile uint32 *)0xFFFF9A08)
#define DTTCT040               (*(volatile uint32 *)0xFFFF9A0C)
#define DTRSA040               (*(volatile uint32 *)0xFFFF9A10)
#define DTRDA040               (*(volatile uint32 *)0xFFFF9A14)
#define DTRTC040               (*(volatile uint32 *)0xFFFF9A18)
#define DTTCC040               (*(volatile uint32 *)0xFFFF9A1C)
#define DTFSL040               (*(volatile uint32 *)0xFFFF9A20)
#define DTFST040               (*(volatile uint32 *)0xFFFF9A24)
#define DTFSS040               (*(volatile uint32 *)0xFFFF9A28)
#define DTFSC040               (*(volatile uint32 *)0xFFFF9A2C)
#define DTSA041                (*(volatile uint32 *)0xFFFF9A40)
#define DTDA041                (*(volatile uint32 *)0xFFFF9A44)
#define DTTC041                (*(volatile uint32 *)0xFFFF9A48)
#define DTTCT041               (*(volatile uint32 *)0xFFFF9A4C)
#define DTRSA041               (*(volatile uint32 *)0xFFFF9A50)
#define DTRDA041               (*(volatile uint32 *)0xFFFF9A54)
#define DTRTC041               (*(volatile uint32 *)0xFFFF9A58)
#define DTTCC041               (*(volatile uint32 *)0xFFFF9A5C)
#define DTFSL041               (*(volatile uint32 *)0xFFFF9A60)
#define DTFST041               (*(volatile uint32 *)0xFFFF9A64)
#define DTFSS041               (*(volatile uint32 *)0xFFFF9A68)
#define DTFSC041               (*(volatile uint32 *)0xFFFF9A6C)
#define DTSA042                (*(volatile uint32 *)0xFFFF9A80)
#define DTDA042                (*(volatile uint32 *)0xFFFF9A84)
#define DTTC042                (*(volatile uint32 *)0xFFFF9A88)
#define DTTCT042               (*(volatile uint32 *)0xFFFF9A8C)
#define DTRSA042               (*(volatile uint32 *)0xFFFF9A90)
#define DTRDA042               (*(volatile uint32 *)0xFFFF9A94)
#define DTRTC042               (*(volatile uint32 *)0xFFFF9A98)
#define DTTCC042               (*(volatile uint32 *)0xFFFF9A9C)
#define DTFSL042               (*(volatile uint32 *)0xFFFF9AA0)
#define DTFST042               (*(volatile uint32 *)0xFFFF9AA4)
#define DTFSS042               (*(volatile uint32 *)0xFFFF9AA8)
#define DTFSC042               (*(volatile uint32 *)0xFFFF9AAC)
#define DTSA043                (*(volatile uint32 *)0xFFFF9AC0)
#define DTDA043                (*(volatile uint32 *)0xFFFF9AC4)
#define DTTC043                (*(volatile uint32 *)0xFFFF9AC8)
#define DTTCT043               (*(volatile uint32 *)0xFFFF9ACC)
#define DTRSA043               (*(volatile uint32 *)0xFFFF9AD0)
#define DTRDA043               (*(volatile uint32 *)0xFFFF9AD4)
#define DTRTC043               (*(volatile uint32 *)0xFFFF9AD8)
#define DTTCC043               (*(volatile uint32 *)0xFFFF9ADC)
#define DTFSL043               (*(volatile uint32 *)0xFFFF9AE0)
#define DTFST043               (*(volatile uint32 *)0xFFFF9AE4)
#define DTFSS043               (*(volatile uint32 *)0xFFFF9AE8)
#define DTFSC043               (*(volatile uint32 *)0xFFFF9AEC)
#define DTSA044                (*(volatile uint32 *)0xFFFF9B00)
#define DTDA044                (*(volatile uint32 *)0xFFFF9B04)
#define DTTC044                (*(volatile uint32 *)0xFFFF9B08)
#define DTTCT044               (*(volatile uint32 *)0xFFFF9B0C)
#define DTRSA044               (*(volatile uint32 *)0xFFFF9B10)
#define DTRDA044               (*(volatile uint32 *)0xFFFF9B14)
#define DTRTC044               (*(volatile uint32 *)0xFFFF9B18)
#define DTTCC044               (*(volatile uint32 *)0xFFFF9B1C)
#define DTFSL044               (*(volatile uint32 *)0xFFFF9B20)
#define DTFST044               (*(volatile uint32 *)0xFFFF9B24)
#define DTFSS044               (*(volatile uint32 *)0xFFFF9B28)
#define DTFSC044               (*(volatile uint32 *)0xFFFF9B2C)
#define DTSA045                (*(volatile uint32 *)0xFFFF9B40)
#define DTDA045                (*(volatile uint32 *)0xFFFF9B44)
#define DTTC045                (*(volatile uint32 *)0xFFFF9B48)
#define DTTCT045               (*(volatile uint32 *)0xFFFF9B4C)
#define DTRSA045               (*(volatile uint32 *)0xFFFF9B50)
#define DTRDA045               (*(volatile uint32 *)0xFFFF9B54)
#define DTRTC045               (*(volatile uint32 *)0xFFFF9B58)
#define DTTCC045               (*(volatile uint32 *)0xFFFF9B5C)
#define DTFSL045               (*(volatile uint32 *)0xFFFF9B60)
#define DTFST045               (*(volatile uint32 *)0xFFFF9B64)
#define DTFSS045               (*(volatile uint32 *)0xFFFF9B68)
#define DTFSC045               (*(volatile uint32 *)0xFFFF9B6C)
#define DTSA046                (*(volatile uint32 *)0xFFFF9B80)
#define DTDA046                (*(volatile uint32 *)0xFFFF9B84)
#define DTTC046                (*(volatile uint32 *)0xFFFF9B88)
#define DTTCT046               (*(volatile uint32 *)0xFFFF9B8C)
#define DTRSA046               (*(volatile uint32 *)0xFFFF9B90)
#define DTRDA046               (*(volatile uint32 *)0xFFFF9B94)
#define DTRTC046               (*(volatile uint32 *)0xFFFF9B98)
#define DTTCC046               (*(volatile uint32 *)0xFFFF9B9C)
#define DTFSL046               (*(volatile uint32 *)0xFFFF9BA0)
#define DTFST046               (*(volatile uint32 *)0xFFFF9BA4)
#define DTFSS046               (*(volatile uint32 *)0xFFFF9BA8)
#define DTFSC046               (*(volatile uint32 *)0xFFFF9BAC)
#define DTSA047                (*(volatile uint32 *)0xFFFF9BC0)
#define DTDA047                (*(volatile uint32 *)0xFFFF9BC4)
#define DTTC047                (*(volatile uint32 *)0xFFFF9BC8)
#define DTTCT047               (*(volatile uint32 *)0xFFFF9BCC)
#define DTRSA047               (*(volatile uint32 *)0xFFFF9BD0)
#define DTRDA047               (*(volatile uint32 *)0xFFFF9BD4)
#define DTRTC047               (*(volatile uint32 *)0xFFFF9BD8)
#define DTTCC047               (*(volatile uint32 *)0xFFFF9BDC)
#define DTFSL047               (*(volatile uint32 *)0xFFFF9BE0)
#define DTFST047               (*(volatile uint32 *)0xFFFF9BE4)
#define DTFSS047               (*(volatile uint32 *)0xFFFF9BE8)
#define DTFSC047               (*(volatile uint32 *)0xFFFF9BEC)
#define DTSA048                (*(volatile uint32 *)0xFFFF9C00)
#define DTDA048                (*(volatile uint32 *)0xFFFF9C04)
#define DTTC048                (*(volatile uint32 *)0xFFFF9C08)
#define DTTCT048               (*(volatile uint32 *)0xFFFF9C0C)
#define DTRSA048               (*(volatile uint32 *)0xFFFF9C10)
#define DTRDA048               (*(volatile uint32 *)0xFFFF9C14)
#define DTRTC048               (*(volatile uint32 *)0xFFFF9C18)
#define DTTCC048               (*(volatile uint32 *)0xFFFF9C1C)
#define DTFSL048               (*(volatile uint32 *)0xFFFF9C20)
#define DTFST048               (*(volatile uint32 *)0xFFFF9C24)
#define DTFSS048               (*(volatile uint32 *)0xFFFF9C28)
#define DTFSC048               (*(volatile uint32 *)0xFFFF9C2C)
#define DTSA049                (*(volatile uint32 *)0xFFFF9C40)
#define DTDA049                (*(volatile uint32 *)0xFFFF9C44)
#define DTTC049                (*(volatile uint32 *)0xFFFF9C48)
#define DTTCT049               (*(volatile uint32 *)0xFFFF9C4C)
#define DTRSA049               (*(volatile uint32 *)0xFFFF9C50)
#define DTRDA049               (*(volatile uint32 *)0xFFFF9C54)
#define DTRTC049               (*(volatile uint32 *)0xFFFF9C58)
#define DTTCC049               (*(volatile uint32 *)0xFFFF9C5C)
#define DTFSL049               (*(volatile uint32 *)0xFFFF9C60)
#define DTFST049               (*(volatile uint32 *)0xFFFF9C64)
#define DTFSS049               (*(volatile uint32 *)0xFFFF9C68)
#define DTFSC049               (*(volatile uint32 *)0xFFFF9C6C)
#define DTSA050                (*(volatile uint32 *)0xFFFF9C80)
#define DTDA050                (*(volatile uint32 *)0xFFFF9C84)
#define DTTC050                (*(volatile uint32 *)0xFFFF9C88)
#define DTTCT050               (*(volatile uint32 *)0xFFFF9C8C)
#define DTRSA050               (*(volatile uint32 *)0xFFFF9C90)
#define DTRDA050               (*(volatile uint32 *)0xFFFF9C94)
#define DTRTC050               (*(volatile uint32 *)0xFFFF9C98)
#define DTTCC050               (*(volatile uint32 *)0xFFFF9C9C)
#define DTFSL050               (*(volatile uint32 *)0xFFFF9CA0)
#define DTFST050               (*(volatile uint32 *)0xFFFF9CA4)
#define DTFSS050               (*(volatile uint32 *)0xFFFF9CA8)
#define DTFSC050               (*(volatile uint32 *)0xFFFF9CAC)
#define DTSA051                (*(volatile uint32 *)0xFFFF9CC0)
#define DTDA051                (*(volatile uint32 *)0xFFFF9CC4)
#define DTTC051                (*(volatile uint32 *)0xFFFF9CC8)
#define DTTCT051               (*(volatile uint32 *)0xFFFF9CCC)
#define DTRSA051               (*(volatile uint32 *)0xFFFF9CD0)
#define DTRDA051               (*(volatile uint32 *)0xFFFF9CD4)
#define DTRTC051               (*(volatile uint32 *)0xFFFF9CD8)
#define DTTCC051               (*(volatile uint32 *)0xFFFF9CDC)
#define DTFSL051               (*(volatile uint32 *)0xFFFF9CE0)
#define DTFST051               (*(volatile uint32 *)0xFFFF9CE4)
#define DTFSS051               (*(volatile uint32 *)0xFFFF9CE8)
#define DTFSC051               (*(volatile uint32 *)0xFFFF9CEC)
#define DTSA052                (*(volatile uint32 *)0xFFFF9D00)
#define DTDA052                (*(volatile uint32 *)0xFFFF9D04)
#define DTTC052                (*(volatile uint32 *)0xFFFF9D08)
#define DTTCT052               (*(volatile uint32 *)0xFFFF9D0C)
#define DTRSA052               (*(volatile uint32 *)0xFFFF9D10)
#define DTRDA052               (*(volatile uint32 *)0xFFFF9D14)
#define DTRTC052               (*(volatile uint32 *)0xFFFF9D18)
#define DTTCC052               (*(volatile uint32 *)0xFFFF9D1C)
#define DTFSL052               (*(volatile uint32 *)0xFFFF9D20)
#define DTFST052               (*(volatile uint32 *)0xFFFF9D24)
#define DTFSS052               (*(volatile uint32 *)0xFFFF9D28)
#define DTFSC052               (*(volatile uint32 *)0xFFFF9D2C)
#define DTSA053                (*(volatile uint32 *)0xFFFF9D40)
#define DTDA053                (*(volatile uint32 *)0xFFFF9D44)
#define DTTC053                (*(volatile uint32 *)0xFFFF9D48)
#define DTTCT053               (*(volatile uint32 *)0xFFFF9D4C)
#define DTRSA053               (*(volatile uint32 *)0xFFFF9D50)
#define DTRDA053               (*(volatile uint32 *)0xFFFF9D54)
#define DTRTC053               (*(volatile uint32 *)0xFFFF9D58)
#define DTTCC053               (*(volatile uint32 *)0xFFFF9D5C)
#define DTFSL053               (*(volatile uint32 *)0xFFFF9D60)
#define DTFST053               (*(volatile uint32 *)0xFFFF9D64)
#define DTFSS053               (*(volatile uint32 *)0xFFFF9D68)
#define DTFSC053               (*(volatile uint32 *)0xFFFF9D6C)
#define DTSA054                (*(volatile uint32 *)0xFFFF9D80)
#define DTDA054                (*(volatile uint32 *)0xFFFF9D84)
#define DTTC054                (*(volatile uint32 *)0xFFFF9D88)
#define DTTCT054               (*(volatile uint32 *)0xFFFF9D8C)
#define DTRSA054               (*(volatile uint32 *)0xFFFF9D90)
#define DTRDA054               (*(volatile uint32 *)0xFFFF9D94)
#define DTRTC054               (*(volatile uint32 *)0xFFFF9D98)
#define DTTCC054               (*(volatile uint32 *)0xFFFF9D9C)
#define DTFSL054               (*(volatile uint32 *)0xFFFF9DA0)
#define DTFST054               (*(volatile uint32 *)0xFFFF9DA4)
#define DTFSS054               (*(volatile uint32 *)0xFFFF9DA8)
#define DTFSC054               (*(volatile uint32 *)0xFFFF9DAC)
#define DTSA055                (*(volatile uint32 *)0xFFFF9DC0)
#define DTDA055                (*(volatile uint32 *)0xFFFF9DC4)
#define DTTC055                (*(volatile uint32 *)0xFFFF9DC8)
#define DTTCT055               (*(volatile uint32 *)0xFFFF9DCC)
#define DTRSA055               (*(volatile uint32 *)0xFFFF9DD0)
#define DTRDA055               (*(volatile uint32 *)0xFFFF9DD4)
#define DTRTC055               (*(volatile uint32 *)0xFFFF9DD8)
#define DTTCC055               (*(volatile uint32 *)0xFFFF9DDC)
#define DTFSL055               (*(volatile uint32 *)0xFFFF9DE0)
#define DTFST055               (*(volatile uint32 *)0xFFFF9DE4)
#define DTFSS055               (*(volatile uint32 *)0xFFFF9DE8)
#define DTFSC055               (*(volatile uint32 *)0xFFFF9DEC)
#define DTSA056                (*(volatile uint32 *)0xFFFF9E00)
#define DTDA056                (*(volatile uint32 *)0xFFFF9E04)
#define DTTC056                (*(volatile uint32 *)0xFFFF9E08)
#define DTTCT056               (*(volatile uint32 *)0xFFFF9E0C)
#define DTRSA056               (*(volatile uint32 *)0xFFFF9E10)
#define DTRDA056               (*(volatile uint32 *)0xFFFF9E14)
#define DTRTC056               (*(volatile uint32 *)0xFFFF9E18)
#define DTTCC056               (*(volatile uint32 *)0xFFFF9E1C)
#define DTFSL056               (*(volatile uint32 *)0xFFFF9E20)
#define DTFST056               (*(volatile uint32 *)0xFFFF9E24)
#define DTFSS056               (*(volatile uint32 *)0xFFFF9E28)
#define DTFSC056               (*(volatile uint32 *)0xFFFF9E2C)
#define DTSA057                (*(volatile uint32 *)0xFFFF9E40)
#define DTDA057                (*(volatile uint32 *)0xFFFF9E44)
#define DTTC057                (*(volatile uint32 *)0xFFFF9E48)
#define DTTCT057               (*(volatile uint32 *)0xFFFF9E4C)
#define DTRSA057               (*(volatile uint32 *)0xFFFF9E50)
#define DTRDA057               (*(volatile uint32 *)0xFFFF9E54)
#define DTRTC057               (*(volatile uint32 *)0xFFFF9E58)
#define DTTCC057               (*(volatile uint32 *)0xFFFF9E5C)
#define DTFSL057               (*(volatile uint32 *)0xFFFF9E60)
#define DTFST057               (*(volatile uint32 *)0xFFFF9E64)
#define DTFSS057               (*(volatile uint32 *)0xFFFF9E68)
#define DTFSC057               (*(volatile uint32 *)0xFFFF9E6C)
#define DTSA058                (*(volatile uint32 *)0xFFFF9E80)
#define DTDA058                (*(volatile uint32 *)0xFFFF9E84)
#define DTTC058                (*(volatile uint32 *)0xFFFF9E88)
#define DTTCT058               (*(volatile uint32 *)0xFFFF9E8C)
#define DTRSA058               (*(volatile uint32 *)0xFFFF9E90)
#define DTRDA058               (*(volatile uint32 *)0xFFFF9E94)
#define DTRTC058               (*(volatile uint32 *)0xFFFF9E98)
#define DTTCC058               (*(volatile uint32 *)0xFFFF9E9C)
#define DTFSL058               (*(volatile uint32 *)0xFFFF9EA0)
#define DTFST058               (*(volatile uint32 *)0xFFFF9EA4)
#define DTFSS058               (*(volatile uint32 *)0xFFFF9EA8)
#define DTFSC058               (*(volatile uint32 *)0xFFFF9EAC)
#define DTSA059                (*(volatile uint32 *)0xFFFF9EC0)
#define DTDA059                (*(volatile uint32 *)0xFFFF9EC4)
#define DTTC059                (*(volatile uint32 *)0xFFFF9EC8)
#define DTTCT059               (*(volatile uint32 *)0xFFFF9ECC)
#define DTRSA059               (*(volatile uint32 *)0xFFFF9ED0)
#define DTRDA059               (*(volatile uint32 *)0xFFFF9ED4)
#define DTRTC059               (*(volatile uint32 *)0xFFFF9ED8)
#define DTTCC059               (*(volatile uint32 *)0xFFFF9EDC)
#define DTFSL059               (*(volatile uint32 *)0xFFFF9EE0)
#define DTFST059               (*(volatile uint32 *)0xFFFF9EE4)
#define DTFSS059               (*(volatile uint32 *)0xFFFF9EE8)
#define DTFSC059               (*(volatile uint32 *)0xFFFF9EEC)
#define DTSA060                (*(volatile uint32 *)0xFFFF9F00)
#define DTDA060                (*(volatile uint32 *)0xFFFF9F04)
#define DTTC060                (*(volatile uint32 *)0xFFFF9F08)
#define DTTCT060               (*(volatile uint32 *)0xFFFF9F0C)
#define DTRSA060               (*(volatile uint32 *)0xFFFF9F10)
#define DTRDA060               (*(volatile uint32 *)0xFFFF9F14)
#define DTRTC060               (*(volatile uint32 *)0xFFFF9F18)
#define DTTCC060               (*(volatile uint32 *)0xFFFF9F1C)
#define DTFSL060               (*(volatile uint32 *)0xFFFF9F20)
#define DTFST060               (*(volatile uint32 *)0xFFFF9F24)
#define DTFSS060               (*(volatile uint32 *)0xFFFF9F28)
#define DTFSC060               (*(volatile uint32 *)0xFFFF9F2C)
#define DTSA061                (*(volatile uint32 *)0xFFFF9F40)
#define DTDA061                (*(volatile uint32 *)0xFFFF9F44)
#define DTTC061                (*(volatile uint32 *)0xFFFF9F48)
#define DTTCT061               (*(volatile uint32 *)0xFFFF9F4C)
#define DTRSA061               (*(volatile uint32 *)0xFFFF9F50)
#define DTRDA061               (*(volatile uint32 *)0xFFFF9F54)
#define DTRTC061               (*(volatile uint32 *)0xFFFF9F58)
#define DTTCC061               (*(volatile uint32 *)0xFFFF9F5C)
#define DTFSL061               (*(volatile uint32 *)0xFFFF9F60)
#define DTFST061               (*(volatile uint32 *)0xFFFF9F64)
#define DTFSS061               (*(volatile uint32 *)0xFFFF9F68)
#define DTFSC061               (*(volatile uint32 *)0xFFFF9F6C)
#define DTSA062                (*(volatile uint32 *)0xFFFF9F80)
#define DTDA062                (*(volatile uint32 *)0xFFFF9F84)
#define DTTC062                (*(volatile uint32 *)0xFFFF9F88)
#define DTTCT062               (*(volatile uint32 *)0xFFFF9F8C)
#define DTRSA062               (*(volatile uint32 *)0xFFFF9F90)
#define DTRDA062               (*(volatile uint32 *)0xFFFF9F94)
#define DTRTC062               (*(volatile uint32 *)0xFFFF9F98)
#define DTTCC062               (*(volatile uint32 *)0xFFFF9F9C)
#define DTFSL062               (*(volatile uint32 *)0xFFFF9FA0)
#define DTFST062               (*(volatile uint32 *)0xFFFF9FA4)
#define DTFSS062               (*(volatile uint32 *)0xFFFF9FA8)
#define DTFSC062               (*(volatile uint32 *)0xFFFF9FAC)
#define DTSA063                (*(volatile uint32 *)0xFFFF9FC0)
#define DTDA063                (*(volatile uint32 *)0xFFFF9FC4)
#define DTTC063                (*(volatile uint32 *)0xFFFF9FC8)
#define DTTCT063               (*(volatile uint32 *)0xFFFF9FCC)
#define DTRSA063               (*(volatile uint32 *)0xFFFF9FD0)
#define DTRDA063               (*(volatile uint32 *)0xFFFF9FD4)
#define DTRTC063               (*(volatile uint32 *)0xFFFF9FD8)
#define DTTCC063               (*(volatile uint32 *)0xFFFF9FDC)
#define DTFSL063               (*(volatile uint32 *)0xFFFF9FE0)
#define DTFST063               (*(volatile uint32 *)0xFFFF9FE4)
#define DTFSS063               (*(volatile uint32 *)0xFFFF9FE8)
#define DTFSC063               (*(volatile uint32 *)0xFFFF9FEC)
#define DTSA064                (*(volatile uint32 *)0xFFFFA000)
#define DTDA064                (*(volatile uint32 *)0xFFFFA004)
#define DTTC064                (*(volatile uint32 *)0xFFFFA008)
#define DTTCT064               (*(volatile uint32 *)0xFFFFA00C)
#define DTRSA064               (*(volatile uint32 *)0xFFFFA010)
#define DTRDA064               (*(volatile uint32 *)0xFFFFA014)
#define DTRTC064               (*(volatile uint32 *)0xFFFFA018)
#define DTTCC064               (*(volatile uint32 *)0xFFFFA01C)
#define DTFSL064               (*(volatile uint32 *)0xFFFFA020)
#define DTFST064               (*(volatile uint32 *)0xFFFFA024)
#define DTFSS064               (*(volatile uint32 *)0xFFFFA028)
#define DTFSC064               (*(volatile uint32 *)0xFFFFA02C)
#define DTSA065                (*(volatile uint32 *)0xFFFFA040)
#define DTDA065                (*(volatile uint32 *)0xFFFFA044)
#define DTTC065                (*(volatile uint32 *)0xFFFFA048)
#define DTTCT065               (*(volatile uint32 *)0xFFFFA04C)
#define DTRSA065               (*(volatile uint32 *)0xFFFFA050)
#define DTRDA065               (*(volatile uint32 *)0xFFFFA054)
#define DTRTC065               (*(volatile uint32 *)0xFFFFA058)
#define DTTCC065               (*(volatile uint32 *)0xFFFFA05C)
#define DTFSL065               (*(volatile uint32 *)0xFFFFA060)
#define DTFST065               (*(volatile uint32 *)0xFFFFA064)
#define DTFSS065               (*(volatile uint32 *)0xFFFFA068)
#define DTFSC065               (*(volatile uint32 *)0xFFFFA06C)
#define DTSA066                (*(volatile uint32 *)0xFFFFA080)
#define DTDA066                (*(volatile uint32 *)0xFFFFA084)
#define DTTC066                (*(volatile uint32 *)0xFFFFA088)
#define DTTCT066               (*(volatile uint32 *)0xFFFFA08C)
#define DTRSA066               (*(volatile uint32 *)0xFFFFA090)
#define DTRDA066               (*(volatile uint32 *)0xFFFFA094)
#define DTRTC066               (*(volatile uint32 *)0xFFFFA098)
#define DTTCC066               (*(volatile uint32 *)0xFFFFA09C)
#define DTFSL066               (*(volatile uint32 *)0xFFFFA0A0)
#define DTFST066               (*(volatile uint32 *)0xFFFFA0A4)
#define DTFSS066               (*(volatile uint32 *)0xFFFFA0A8)
#define DTFSC066               (*(volatile uint32 *)0xFFFFA0AC)
#define DTSA067                (*(volatile uint32 *)0xFFFFA0C0)
#define DTDA067                (*(volatile uint32 *)0xFFFFA0C4)
#define DTTC067                (*(volatile uint32 *)0xFFFFA0C8)
#define DTTCT067               (*(volatile uint32 *)0xFFFFA0CC)
#define DTRSA067               (*(volatile uint32 *)0xFFFFA0D0)
#define DTRDA067               (*(volatile uint32 *)0xFFFFA0D4)
#define DTRTC067               (*(volatile uint32 *)0xFFFFA0D8)
#define DTTCC067               (*(volatile uint32 *)0xFFFFA0DC)
#define DTFSL067               (*(volatile uint32 *)0xFFFFA0E0)
#define DTFST067               (*(volatile uint32 *)0xFFFFA0E4)
#define DTFSS067               (*(volatile uint32 *)0xFFFFA0E8)
#define DTFSC067               (*(volatile uint32 *)0xFFFFA0EC)
#define DTSA068                (*(volatile uint32 *)0xFFFFA100)
#define DTDA068                (*(volatile uint32 *)0xFFFFA104)
#define DTTC068                (*(volatile uint32 *)0xFFFFA108)
#define DTTCT068               (*(volatile uint32 *)0xFFFFA10C)
#define DTRSA068               (*(volatile uint32 *)0xFFFFA110)
#define DTRDA068               (*(volatile uint32 *)0xFFFFA114)
#define DTRTC068               (*(volatile uint32 *)0xFFFFA118)
#define DTTCC068               (*(volatile uint32 *)0xFFFFA11C)
#define DTFSL068               (*(volatile uint32 *)0xFFFFA120)
#define DTFST068               (*(volatile uint32 *)0xFFFFA124)
#define DTFSS068               (*(volatile uint32 *)0xFFFFA128)
#define DTFSC068               (*(volatile uint32 *)0xFFFFA12C)
#define DTSA069                (*(volatile uint32 *)0xFFFFA140)
#define DTDA069                (*(volatile uint32 *)0xFFFFA144)
#define DTTC069                (*(volatile uint32 *)0xFFFFA148)
#define DTTCT069               (*(volatile uint32 *)0xFFFFA14C)
#define DTRSA069               (*(volatile uint32 *)0xFFFFA150)
#define DTRDA069               (*(volatile uint32 *)0xFFFFA154)
#define DTRTC069               (*(volatile uint32 *)0xFFFFA158)
#define DTTCC069               (*(volatile uint32 *)0xFFFFA15C)
#define DTFSL069               (*(volatile uint32 *)0xFFFFA160)
#define DTFST069               (*(volatile uint32 *)0xFFFFA164)
#define DTFSS069               (*(volatile uint32 *)0xFFFFA168)
#define DTFSC069               (*(volatile uint32 *)0xFFFFA16C)
#define DTSA070                (*(volatile uint32 *)0xFFFFA180)
#define DTDA070                (*(volatile uint32 *)0xFFFFA184)
#define DTTC070                (*(volatile uint32 *)0xFFFFA188)
#define DTTCT070               (*(volatile uint32 *)0xFFFFA18C)
#define DTRSA070               (*(volatile uint32 *)0xFFFFA190)
#define DTRDA070               (*(volatile uint32 *)0xFFFFA194)
#define DTRTC070               (*(volatile uint32 *)0xFFFFA198)
#define DTTCC070               (*(volatile uint32 *)0xFFFFA19C)
#define DTFSL070               (*(volatile uint32 *)0xFFFFA1A0)
#define DTFST070               (*(volatile uint32 *)0xFFFFA1A4)
#define DTFSS070               (*(volatile uint32 *)0xFFFFA1A8)
#define DTFSC070               (*(volatile uint32 *)0xFFFFA1AC)
#define DTSA071                (*(volatile uint32 *)0xFFFFA1C0)
#define DTDA071                (*(volatile uint32 *)0xFFFFA1C4)
#define DTTC071                (*(volatile uint32 *)0xFFFFA1C8)
#define DTTCT071               (*(volatile uint32 *)0xFFFFA1CC)
#define DTRSA071               (*(volatile uint32 *)0xFFFFA1D0)
#define DTRDA071               (*(volatile uint32 *)0xFFFFA1D4)
#define DTRTC071               (*(volatile uint32 *)0xFFFFA1D8)
#define DTTCC071               (*(volatile uint32 *)0xFFFFA1DC)
#define DTFSL071               (*(volatile uint32 *)0xFFFFA1E0)
#define DTFST071               (*(volatile uint32 *)0xFFFFA1E4)
#define DTFSS071               (*(volatile uint32 *)0xFFFFA1E8)
#define DTFSC071               (*(volatile uint32 *)0xFFFFA1EC)
#define DTSA072                (*(volatile uint32 *)0xFFFFA200)
#define DTDA072                (*(volatile uint32 *)0xFFFFA204)
#define DTTC072                (*(volatile uint32 *)0xFFFFA208)
#define DTTCT072               (*(volatile uint32 *)0xFFFFA20C)
#define DTRSA072               (*(volatile uint32 *)0xFFFFA210)
#define DTRDA072               (*(volatile uint32 *)0xFFFFA214)
#define DTRTC072               (*(volatile uint32 *)0xFFFFA218)
#define DTTCC072               (*(volatile uint32 *)0xFFFFA21C)
#define DTFSL072               (*(volatile uint32 *)0xFFFFA220)
#define DTFST072               (*(volatile uint32 *)0xFFFFA224)
#define DTFSS072               (*(volatile uint32 *)0xFFFFA228)
#define DTFSC072               (*(volatile uint32 *)0xFFFFA22C)
#define DTSA073                (*(volatile uint32 *)0xFFFFA240)
#define DTDA073                (*(volatile uint32 *)0xFFFFA244)
#define DTTC073                (*(volatile uint32 *)0xFFFFA248)
#define DTTCT073               (*(volatile uint32 *)0xFFFFA24C)
#define DTRSA073               (*(volatile uint32 *)0xFFFFA250)
#define DTRDA073               (*(volatile uint32 *)0xFFFFA254)
#define DTRTC073               (*(volatile uint32 *)0xFFFFA258)
#define DTTCC073               (*(volatile uint32 *)0xFFFFA25C)
#define DTFSL073               (*(volatile uint32 *)0xFFFFA260)
#define DTFST073               (*(volatile uint32 *)0xFFFFA264)
#define DTFSS073               (*(volatile uint32 *)0xFFFFA268)
#define DTFSC073               (*(volatile uint32 *)0xFFFFA26C)
#define DTSA074                (*(volatile uint32 *)0xFFFFA280)
#define DTDA074                (*(volatile uint32 *)0xFFFFA284)
#define DTTC074                (*(volatile uint32 *)0xFFFFA288)
#define DTTCT074               (*(volatile uint32 *)0xFFFFA28C)
#define DTRSA074               (*(volatile uint32 *)0xFFFFA290)
#define DTRDA074               (*(volatile uint32 *)0xFFFFA294)
#define DTRTC074               (*(volatile uint32 *)0xFFFFA298)
#define DTTCC074               (*(volatile uint32 *)0xFFFFA29C)
#define DTFSL074               (*(volatile uint32 *)0xFFFFA2A0)
#define DTFST074               (*(volatile uint32 *)0xFFFFA2A4)
#define DTFSS074               (*(volatile uint32 *)0xFFFFA2A8)
#define DTFSC074               (*(volatile uint32 *)0xFFFFA2AC)
#define DTSA075                (*(volatile uint32 *)0xFFFFA2C0)
#define DTDA075                (*(volatile uint32 *)0xFFFFA2C4)
#define DTTC075                (*(volatile uint32 *)0xFFFFA2C8)
#define DTTCT075               (*(volatile uint32 *)0xFFFFA2CC)
#define DTRSA075               (*(volatile uint32 *)0xFFFFA2D0)
#define DTRDA075               (*(volatile uint32 *)0xFFFFA2D4)
#define DTRTC075               (*(volatile uint32 *)0xFFFFA2D8)
#define DTTCC075               (*(volatile uint32 *)0xFFFFA2DC)
#define DTFSL075               (*(volatile uint32 *)0xFFFFA2E0)
#define DTFST075               (*(volatile uint32 *)0xFFFFA2E4)
#define DTFSS075               (*(volatile uint32 *)0xFFFFA2E8)
#define DTFSC075               (*(volatile uint32 *)0xFFFFA2EC)
#define DTSA076                (*(volatile uint32 *)0xFFFFA300)
#define DTDA076                (*(volatile uint32 *)0xFFFFA304)
#define DTTC076                (*(volatile uint32 *)0xFFFFA308)
#define DTTCT076               (*(volatile uint32 *)0xFFFFA30C)
#define DTRSA076               (*(volatile uint32 *)0xFFFFA310)
#define DTRDA076               (*(volatile uint32 *)0xFFFFA314)
#define DTRTC076               (*(volatile uint32 *)0xFFFFA318)
#define DTTCC076               (*(volatile uint32 *)0xFFFFA31C)
#define DTFSL076               (*(volatile uint32 *)0xFFFFA320)
#define DTFST076               (*(volatile uint32 *)0xFFFFA324)
#define DTFSS076               (*(volatile uint32 *)0xFFFFA328)
#define DTFSC076               (*(volatile uint32 *)0xFFFFA32C)
#define DTSA077                (*(volatile uint32 *)0xFFFFA340)
#define DTDA077                (*(volatile uint32 *)0xFFFFA344)
#define DTTC077                (*(volatile uint32 *)0xFFFFA348)
#define DTTCT077               (*(volatile uint32 *)0xFFFFA34C)
#define DTRSA077               (*(volatile uint32 *)0xFFFFA350)
#define DTRDA077               (*(volatile uint32 *)0xFFFFA354)
#define DTRTC077               (*(volatile uint32 *)0xFFFFA358)
#define DTTCC077               (*(volatile uint32 *)0xFFFFA35C)
#define DTFSL077               (*(volatile uint32 *)0xFFFFA360)
#define DTFST077               (*(volatile uint32 *)0xFFFFA364)
#define DTFSS077               (*(volatile uint32 *)0xFFFFA368)
#define DTFSC077               (*(volatile uint32 *)0xFFFFA36C)
#define DTSA078                (*(volatile uint32 *)0xFFFFA380)
#define DTDA078                (*(volatile uint32 *)0xFFFFA384)
#define DTTC078                (*(volatile uint32 *)0xFFFFA388)
#define DTTCT078               (*(volatile uint32 *)0xFFFFA38C)
#define DTRSA078               (*(volatile uint32 *)0xFFFFA390)
#define DTRDA078               (*(volatile uint32 *)0xFFFFA394)
#define DTRTC078               (*(volatile uint32 *)0xFFFFA398)
#define DTTCC078               (*(volatile uint32 *)0xFFFFA39C)
#define DTFSL078               (*(volatile uint32 *)0xFFFFA3A0)
#define DTFST078               (*(volatile uint32 *)0xFFFFA3A4)
#define DTFSS078               (*(volatile uint32 *)0xFFFFA3A8)
#define DTFSC078               (*(volatile uint32 *)0xFFFFA3AC)
#define DTSA079                (*(volatile uint32 *)0xFFFFA3C0)
#define DTDA079                (*(volatile uint32 *)0xFFFFA3C4)
#define DTTC079                (*(volatile uint32 *)0xFFFFA3C8)
#define DTTCT079               (*(volatile uint32 *)0xFFFFA3CC)
#define DTRSA079               (*(volatile uint32 *)0xFFFFA3D0)
#define DTRDA079               (*(volatile uint32 *)0xFFFFA3D4)
#define DTRTC079               (*(volatile uint32 *)0xFFFFA3D8)
#define DTTCC079               (*(volatile uint32 *)0xFFFFA3DC)
#define DTFSL079               (*(volatile uint32 *)0xFFFFA3E0)
#define DTFST079               (*(volatile uint32 *)0xFFFFA3E4)
#define DTFSS079               (*(volatile uint32 *)0xFFFFA3E8)
#define DTFSC079               (*(volatile uint32 *)0xFFFFA3EC)
#define DTSA080                (*(volatile uint32 *)0xFFFFA400)
#define DTDA080                (*(volatile uint32 *)0xFFFFA404)
#define DTTC080                (*(volatile uint32 *)0xFFFFA408)
#define DTTCT080               (*(volatile uint32 *)0xFFFFA40C)
#define DTRSA080               (*(volatile uint32 *)0xFFFFA410)
#define DTRDA080               (*(volatile uint32 *)0xFFFFA414)
#define DTRTC080               (*(volatile uint32 *)0xFFFFA418)
#define DTTCC080               (*(volatile uint32 *)0xFFFFA41C)
#define DTFSL080               (*(volatile uint32 *)0xFFFFA420)
#define DTFST080               (*(volatile uint32 *)0xFFFFA424)
#define DTFSS080               (*(volatile uint32 *)0xFFFFA428)
#define DTFSC080               (*(volatile uint32 *)0xFFFFA42C)
#define DTSA081                (*(volatile uint32 *)0xFFFFA440)
#define DTDA081                (*(volatile uint32 *)0xFFFFA444)
#define DTTC081                (*(volatile uint32 *)0xFFFFA448)
#define DTTCT081               (*(volatile uint32 *)0xFFFFA44C)
#define DTRSA081               (*(volatile uint32 *)0xFFFFA450)
#define DTRDA081               (*(volatile uint32 *)0xFFFFA454)
#define DTRTC081               (*(volatile uint32 *)0xFFFFA458)
#define DTTCC081               (*(volatile uint32 *)0xFFFFA45C)
#define DTFSL081               (*(volatile uint32 *)0xFFFFA460)
#define DTFST081               (*(volatile uint32 *)0xFFFFA464)
#define DTFSS081               (*(volatile uint32 *)0xFFFFA468)
#define DTFSC081               (*(volatile uint32 *)0xFFFFA46C)
#define DTSA082                (*(volatile uint32 *)0xFFFFA480)
#define DTDA082                (*(volatile uint32 *)0xFFFFA484)
#define DTTC082                (*(volatile uint32 *)0xFFFFA488)
#define DTTCT082               (*(volatile uint32 *)0xFFFFA48C)
#define DTRSA082               (*(volatile uint32 *)0xFFFFA490)
#define DTRDA082               (*(volatile uint32 *)0xFFFFA494)
#define DTRTC082               (*(volatile uint32 *)0xFFFFA498)
#define DTTCC082               (*(volatile uint32 *)0xFFFFA49C)
#define DTFSL082               (*(volatile uint32 *)0xFFFFA4A0)
#define DTFST082               (*(volatile uint32 *)0xFFFFA4A4)
#define DTFSS082               (*(volatile uint32 *)0xFFFFA4A8)
#define DTFSC082               (*(volatile uint32 *)0xFFFFA4AC)
#define DTSA083                (*(volatile uint32 *)0xFFFFA4C0)
#define DTDA083                (*(volatile uint32 *)0xFFFFA4C4)
#define DTTC083                (*(volatile uint32 *)0xFFFFA4C8)
#define DTTCT083               (*(volatile uint32 *)0xFFFFA4CC)
#define DTRSA083               (*(volatile uint32 *)0xFFFFA4D0)
#define DTRDA083               (*(volatile uint32 *)0xFFFFA4D4)
#define DTRTC083               (*(volatile uint32 *)0xFFFFA4D8)
#define DTTCC083               (*(volatile uint32 *)0xFFFFA4DC)
#define DTFSL083               (*(volatile uint32 *)0xFFFFA4E0)
#define DTFST083               (*(volatile uint32 *)0xFFFFA4E4)
#define DTFSS083               (*(volatile uint32 *)0xFFFFA4E8)
#define DTFSC083               (*(volatile uint32 *)0xFFFFA4EC)
#define DTSA084                (*(volatile uint32 *)0xFFFFA500)
#define DTDA084                (*(volatile uint32 *)0xFFFFA504)
#define DTTC084                (*(volatile uint32 *)0xFFFFA508)
#define DTTCT084               (*(volatile uint32 *)0xFFFFA50C)
#define DTRSA084               (*(volatile uint32 *)0xFFFFA510)
#define DTRDA084               (*(volatile uint32 *)0xFFFFA514)
#define DTRTC084               (*(volatile uint32 *)0xFFFFA518)
#define DTTCC084               (*(volatile uint32 *)0xFFFFA51C)
#define DTFSL084               (*(volatile uint32 *)0xFFFFA520)
#define DTFST084               (*(volatile uint32 *)0xFFFFA524)
#define DTFSS084               (*(volatile uint32 *)0xFFFFA528)
#define DTFSC084               (*(volatile uint32 *)0xFFFFA52C)
#define DTSA085                (*(volatile uint32 *)0xFFFFA540)
#define DTDA085                (*(volatile uint32 *)0xFFFFA544)
#define DTTC085                (*(volatile uint32 *)0xFFFFA548)
#define DTTCT085               (*(volatile uint32 *)0xFFFFA54C)
#define DTRSA085               (*(volatile uint32 *)0xFFFFA550)
#define DTRDA085               (*(volatile uint32 *)0xFFFFA554)
#define DTRTC085               (*(volatile uint32 *)0xFFFFA558)
#define DTTCC085               (*(volatile uint32 *)0xFFFFA55C)
#define DTFSL085               (*(volatile uint32 *)0xFFFFA560)
#define DTFST085               (*(volatile uint32 *)0xFFFFA564)
#define DTFSS085               (*(volatile uint32 *)0xFFFFA568)
#define DTFSC085               (*(volatile uint32 *)0xFFFFA56C)
#define DTSA086                (*(volatile uint32 *)0xFFFFA580)
#define DTDA086                (*(volatile uint32 *)0xFFFFA584)
#define DTTC086                (*(volatile uint32 *)0xFFFFA588)
#define DTTCT086               (*(volatile uint32 *)0xFFFFA58C)
#define DTRSA086               (*(volatile uint32 *)0xFFFFA590)
#define DTRDA086               (*(volatile uint32 *)0xFFFFA594)
#define DTRTC086               (*(volatile uint32 *)0xFFFFA598)
#define DTTCC086               (*(volatile uint32 *)0xFFFFA59C)
#define DTFSL086               (*(volatile uint32 *)0xFFFFA5A0)
#define DTFST086               (*(volatile uint32 *)0xFFFFA5A4)
#define DTFSS086               (*(volatile uint32 *)0xFFFFA5A8)
#define DTFSC086               (*(volatile uint32 *)0xFFFFA5AC)
#define DTSA087                (*(volatile uint32 *)0xFFFFA5C0)
#define DTDA087                (*(volatile uint32 *)0xFFFFA5C4)
#define DTTC087                (*(volatile uint32 *)0xFFFFA5C8)
#define DTTCT087               (*(volatile uint32 *)0xFFFFA5CC)
#define DTRSA087               (*(volatile uint32 *)0xFFFFA5D0)
#define DTRDA087               (*(volatile uint32 *)0xFFFFA5D4)
#define DTRTC087               (*(volatile uint32 *)0xFFFFA5D8)
#define DTTCC087               (*(volatile uint32 *)0xFFFFA5DC)
#define DTFSL087               (*(volatile uint32 *)0xFFFFA5E0)
#define DTFST087               (*(volatile uint32 *)0xFFFFA5E4)
#define DTFSS087               (*(volatile uint32 *)0xFFFFA5E8)
#define DTFSC087               (*(volatile uint32 *)0xFFFFA5EC)
#define DTSA088                (*(volatile uint32 *)0xFFFFA600)
#define DTDA088                (*(volatile uint32 *)0xFFFFA604)
#define DTTC088                (*(volatile uint32 *)0xFFFFA608)
#define DTTCT088               (*(volatile uint32 *)0xFFFFA60C)
#define DTRSA088               (*(volatile uint32 *)0xFFFFA610)
#define DTRDA088               (*(volatile uint32 *)0xFFFFA614)
#define DTRTC088               (*(volatile uint32 *)0xFFFFA618)
#define DTTCC088               (*(volatile uint32 *)0xFFFFA61C)
#define DTFSL088               (*(volatile uint32 *)0xFFFFA620)
#define DTFST088               (*(volatile uint32 *)0xFFFFA624)
#define DTFSS088               (*(volatile uint32 *)0xFFFFA628)
#define DTFSC088               (*(volatile uint32 *)0xFFFFA62C)
#define DTSA089                (*(volatile uint32 *)0xFFFFA640)
#define DTDA089                (*(volatile uint32 *)0xFFFFA644)
#define DTTC089                (*(volatile uint32 *)0xFFFFA648)
#define DTTCT089               (*(volatile uint32 *)0xFFFFA64C)
#define DTRSA089               (*(volatile uint32 *)0xFFFFA650)
#define DTRDA089               (*(volatile uint32 *)0xFFFFA654)
#define DTRTC089               (*(volatile uint32 *)0xFFFFA658)
#define DTTCC089               (*(volatile uint32 *)0xFFFFA65C)
#define DTFSL089               (*(volatile uint32 *)0xFFFFA660)
#define DTFST089               (*(volatile uint32 *)0xFFFFA664)
#define DTFSS089               (*(volatile uint32 *)0xFFFFA668)
#define DTFSC089               (*(volatile uint32 *)0xFFFFA66C)
#define DTSA090                (*(volatile uint32 *)0xFFFFA680)
#define DTDA090                (*(volatile uint32 *)0xFFFFA684)
#define DTTC090                (*(volatile uint32 *)0xFFFFA688)
#define DTTCT090               (*(volatile uint32 *)0xFFFFA68C)
#define DTRSA090               (*(volatile uint32 *)0xFFFFA690)
#define DTRDA090               (*(volatile uint32 *)0xFFFFA694)
#define DTRTC090               (*(volatile uint32 *)0xFFFFA698)
#define DTTCC090               (*(volatile uint32 *)0xFFFFA69C)
#define DTFSL090               (*(volatile uint32 *)0xFFFFA6A0)
#define DTFST090               (*(volatile uint32 *)0xFFFFA6A4)
#define DTFSS090               (*(volatile uint32 *)0xFFFFA6A8)
#define DTFSC090               (*(volatile uint32 *)0xFFFFA6AC)
#define DTSA091                (*(volatile uint32 *)0xFFFFA6C0)
#define DTDA091                (*(volatile uint32 *)0xFFFFA6C4)
#define DTTC091                (*(volatile uint32 *)0xFFFFA6C8)
#define DTTCT091               (*(volatile uint32 *)0xFFFFA6CC)
#define DTRSA091               (*(volatile uint32 *)0xFFFFA6D0)
#define DTRDA091               (*(volatile uint32 *)0xFFFFA6D4)
#define DTRTC091               (*(volatile uint32 *)0xFFFFA6D8)
#define DTTCC091               (*(volatile uint32 *)0xFFFFA6DC)
#define DTFSL091               (*(volatile uint32 *)0xFFFFA6E0)
#define DTFST091               (*(volatile uint32 *)0xFFFFA6E4)
#define DTFSS091               (*(volatile uint32 *)0xFFFFA6E8)
#define DTFSC091               (*(volatile uint32 *)0xFFFFA6EC)
#define DTSA092                (*(volatile uint32 *)0xFFFFA700)
#define DTDA092                (*(volatile uint32 *)0xFFFFA704)
#define DTTC092                (*(volatile uint32 *)0xFFFFA708)
#define DTTCT092               (*(volatile uint32 *)0xFFFFA70C)
#define DTRSA092               (*(volatile uint32 *)0xFFFFA710)
#define DTRDA092               (*(volatile uint32 *)0xFFFFA714)
#define DTRTC092               (*(volatile uint32 *)0xFFFFA718)
#define DTTCC092               (*(volatile uint32 *)0xFFFFA71C)
#define DTFSL092               (*(volatile uint32 *)0xFFFFA720)
#define DTFST092               (*(volatile uint32 *)0xFFFFA724)
#define DTFSS092               (*(volatile uint32 *)0xFFFFA728)
#define DTFSC092               (*(volatile uint32 *)0xFFFFA72C)
#define DTSA093                (*(volatile uint32 *)0xFFFFA740)
#define DTDA093                (*(volatile uint32 *)0xFFFFA744)
#define DTTC093                (*(volatile uint32 *)0xFFFFA748)
#define DTTCT093               (*(volatile uint32 *)0xFFFFA74C)
#define DTRSA093               (*(volatile uint32 *)0xFFFFA750)
#define DTRDA093               (*(volatile uint32 *)0xFFFFA754)
#define DTRTC093               (*(volatile uint32 *)0xFFFFA758)
#define DTTCC093               (*(volatile uint32 *)0xFFFFA75C)
#define DTFSL093               (*(volatile uint32 *)0xFFFFA760)
#define DTFST093               (*(volatile uint32 *)0xFFFFA764)
#define DTFSS093               (*(volatile uint32 *)0xFFFFA768)
#define DTFSC093               (*(volatile uint32 *)0xFFFFA76C)
#define DTSA094                (*(volatile uint32 *)0xFFFFA780)
#define DTDA094                (*(volatile uint32 *)0xFFFFA784)
#define DTTC094                (*(volatile uint32 *)0xFFFFA788)
#define DTTCT094               (*(volatile uint32 *)0xFFFFA78C)
#define DTRSA094               (*(volatile uint32 *)0xFFFFA790)
#define DTRDA094               (*(volatile uint32 *)0xFFFFA794)
#define DTRTC094               (*(volatile uint32 *)0xFFFFA798)
#define DTTCC094               (*(volatile uint32 *)0xFFFFA79C)
#define DTFSL094               (*(volatile uint32 *)0xFFFFA7A0)
#define DTFST094               (*(volatile uint32 *)0xFFFFA7A4)
#define DTFSS094               (*(volatile uint32 *)0xFFFFA7A8)
#define DTFSC094               (*(volatile uint32 *)0xFFFFA7AC)
#define DTSA095                (*(volatile uint32 *)0xFFFFA7C0)
#define DTDA095                (*(volatile uint32 *)0xFFFFA7C4)
#define DTTC095                (*(volatile uint32 *)0xFFFFA7C8)
#define DTTCT095               (*(volatile uint32 *)0xFFFFA7CC)
#define DTRSA095               (*(volatile uint32 *)0xFFFFA7D0)
#define DTRDA095               (*(volatile uint32 *)0xFFFFA7D4)
#define DTRTC095               (*(volatile uint32 *)0xFFFFA7D8)
#define DTTCC095               (*(volatile uint32 *)0xFFFFA7DC)
#define DTFSL095               (*(volatile uint32 *)0xFFFFA7E0)
#define DTFST095               (*(volatile uint32 *)0xFFFFA7E4)
#define DTFSS095               (*(volatile uint32 *)0xFFFFA7E8)
#define DTFSC095               (*(volatile uint32 *)0xFFFFA7EC)
#define DTSA096                (*(volatile uint32 *)0xFFFFA800)
#define DTDA096                (*(volatile uint32 *)0xFFFFA804)
#define DTTC096                (*(volatile uint32 *)0xFFFFA808)
#define DTTCT096               (*(volatile uint32 *)0xFFFFA80C)
#define DTRSA096               (*(volatile uint32 *)0xFFFFA810)
#define DTRDA096               (*(volatile uint32 *)0xFFFFA814)
#define DTRTC096               (*(volatile uint32 *)0xFFFFA818)
#define DTTCC096               (*(volatile uint32 *)0xFFFFA81C)
#define DTFSL096               (*(volatile uint32 *)0xFFFFA820)
#define DTFST096               (*(volatile uint32 *)0xFFFFA824)
#define DTFSS096               (*(volatile uint32 *)0xFFFFA828)
#define DTFSC096               (*(volatile uint32 *)0xFFFFA82C)
#define DTSA097                (*(volatile uint32 *)0xFFFFA840)
#define DTDA097                (*(volatile uint32 *)0xFFFFA844)
#define DTTC097                (*(volatile uint32 *)0xFFFFA848)
#define DTTCT097               (*(volatile uint32 *)0xFFFFA84C)
#define DTRSA097               (*(volatile uint32 *)0xFFFFA850)
#define DTRDA097               (*(volatile uint32 *)0xFFFFA854)
#define DTRTC097               (*(volatile uint32 *)0xFFFFA858)
#define DTTCC097               (*(volatile uint32 *)0xFFFFA85C)
#define DTFSL097               (*(volatile uint32 *)0xFFFFA860)
#define DTFST097               (*(volatile uint32 *)0xFFFFA864)
#define DTFSS097               (*(volatile uint32 *)0xFFFFA868)
#define DTFSC097               (*(volatile uint32 *)0xFFFFA86C)
#define DTSA098                (*(volatile uint32 *)0xFFFFA880)
#define DTDA098                (*(volatile uint32 *)0xFFFFA884)
#define DTTC098                (*(volatile uint32 *)0xFFFFA888)
#define DTTCT098               (*(volatile uint32 *)0xFFFFA88C)
#define DTRSA098               (*(volatile uint32 *)0xFFFFA890)
#define DTRDA098               (*(volatile uint32 *)0xFFFFA894)
#define DTRTC098               (*(volatile uint32 *)0xFFFFA898)
#define DTTCC098               (*(volatile uint32 *)0xFFFFA89C)
#define DTFSL098               (*(volatile uint32 *)0xFFFFA8A0)
#define DTFST098               (*(volatile uint32 *)0xFFFFA8A4)
#define DTFSS098               (*(volatile uint32 *)0xFFFFA8A8)
#define DTFSC098               (*(volatile uint32 *)0xFFFFA8AC)
#define DTSA099                (*(volatile uint32 *)0xFFFFA8C0)
#define DTDA099                (*(volatile uint32 *)0xFFFFA8C4)
#define DTTC099                (*(volatile uint32 *)0xFFFFA8C8)
#define DTTCT099               (*(volatile uint32 *)0xFFFFA8CC)
#define DTRSA099               (*(volatile uint32 *)0xFFFFA8D0)
#define DTRDA099               (*(volatile uint32 *)0xFFFFA8D4)
#define DTRTC099               (*(volatile uint32 *)0xFFFFA8D8)
#define DTTCC099               (*(volatile uint32 *)0xFFFFA8DC)
#define DTFSL099               (*(volatile uint32 *)0xFFFFA8E0)
#define DTFST099               (*(volatile uint32 *)0xFFFFA8E4)
#define DTFSS099               (*(volatile uint32 *)0xFFFFA8E8)
#define DTFSC099               (*(volatile uint32 *)0xFFFFA8EC)
#define DTSA100                (*(volatile uint32 *)0xFFFFA900)
#define DTDA100                (*(volatile uint32 *)0xFFFFA904)
#define DTTC100                (*(volatile uint32 *)0xFFFFA908)
#define DTTCT100               (*(volatile uint32 *)0xFFFFA90C)
#define DTRSA100               (*(volatile uint32 *)0xFFFFA910)
#define DTRDA100               (*(volatile uint32 *)0xFFFFA914)
#define DTRTC100               (*(volatile uint32 *)0xFFFFA918)
#define DTTCC100               (*(volatile uint32 *)0xFFFFA91C)
#define DTFSL100               (*(volatile uint32 *)0xFFFFA920)
#define DTFST100               (*(volatile uint32 *)0xFFFFA924)
#define DTFSS100               (*(volatile uint32 *)0xFFFFA928)
#define DTFSC100               (*(volatile uint32 *)0xFFFFA92C)
#define DTSA101                (*(volatile uint32 *)0xFFFFA940)
#define DTDA101                (*(volatile uint32 *)0xFFFFA944)
#define DTTC101                (*(volatile uint32 *)0xFFFFA948)
#define DTTCT101               (*(volatile uint32 *)0xFFFFA94C)
#define DTRSA101               (*(volatile uint32 *)0xFFFFA950)
#define DTRDA101               (*(volatile uint32 *)0xFFFFA954)
#define DTRTC101               (*(volatile uint32 *)0xFFFFA958)
#define DTTCC101               (*(volatile uint32 *)0xFFFFA95C)
#define DTFSL101               (*(volatile uint32 *)0xFFFFA960)
#define DTFST101               (*(volatile uint32 *)0xFFFFA964)
#define DTFSS101               (*(volatile uint32 *)0xFFFFA968)
#define DTFSC101               (*(volatile uint32 *)0xFFFFA96C)
#define DTSA102                (*(volatile uint32 *)0xFFFFA980)
#define DTDA102                (*(volatile uint32 *)0xFFFFA984)
#define DTTC102                (*(volatile uint32 *)0xFFFFA988)
#define DTTCT102               (*(volatile uint32 *)0xFFFFA98C)
#define DTRSA102               (*(volatile uint32 *)0xFFFFA990)
#define DTRDA102               (*(volatile uint32 *)0xFFFFA994)
#define DTRTC102               (*(volatile uint32 *)0xFFFFA998)
#define DTTCC102               (*(volatile uint32 *)0xFFFFA99C)
#define DTFSL102               (*(volatile uint32 *)0xFFFFA9A0)
#define DTFST102               (*(volatile uint32 *)0xFFFFA9A4)
#define DTFSS102               (*(volatile uint32 *)0xFFFFA9A8)
#define DTFSC102               (*(volatile uint32 *)0xFFFFA9AC)
#define DTSA103                (*(volatile uint32 *)0xFFFFA9C0)
#define DTDA103                (*(volatile uint32 *)0xFFFFA9C4)
#define DTTC103                (*(volatile uint32 *)0xFFFFA9C8)
#define DTTCT103               (*(volatile uint32 *)0xFFFFA9CC)
#define DTRSA103               (*(volatile uint32 *)0xFFFFA9D0)
#define DTRDA103               (*(volatile uint32 *)0xFFFFA9D4)
#define DTRTC103               (*(volatile uint32 *)0xFFFFA9D8)
#define DTTCC103               (*(volatile uint32 *)0xFFFFA9DC)
#define DTFSL103               (*(volatile uint32 *)0xFFFFA9E0)
#define DTFST103               (*(volatile uint32 *)0xFFFFA9E4)
#define DTFSS103               (*(volatile uint32 *)0xFFFFA9E8)
#define DTFSC103               (*(volatile uint32 *)0xFFFFA9EC)
#define DTSA104                (*(volatile uint32 *)0xFFFFAA00)
#define DTDA104                (*(volatile uint32 *)0xFFFFAA04)
#define DTTC104                (*(volatile uint32 *)0xFFFFAA08)
#define DTTCT104               (*(volatile uint32 *)0xFFFFAA0C)
#define DTRSA104               (*(volatile uint32 *)0xFFFFAA10)
#define DTRDA104               (*(volatile uint32 *)0xFFFFAA14)
#define DTRTC104               (*(volatile uint32 *)0xFFFFAA18)
#define DTTCC104               (*(volatile uint32 *)0xFFFFAA1C)
#define DTFSL104               (*(volatile uint32 *)0xFFFFAA20)
#define DTFST104               (*(volatile uint32 *)0xFFFFAA24)
#define DTFSS104               (*(volatile uint32 *)0xFFFFAA28)
#define DTFSC104               (*(volatile uint32 *)0xFFFFAA2C)
#define DTSA105                (*(volatile uint32 *)0xFFFFAA40)
#define DTDA105                (*(volatile uint32 *)0xFFFFAA44)
#define DTTC105                (*(volatile uint32 *)0xFFFFAA48)
#define DTTCT105               (*(volatile uint32 *)0xFFFFAA4C)
#define DTRSA105               (*(volatile uint32 *)0xFFFFAA50)
#define DTRDA105               (*(volatile uint32 *)0xFFFFAA54)
#define DTRTC105               (*(volatile uint32 *)0xFFFFAA58)
#define DTTCC105               (*(volatile uint32 *)0xFFFFAA5C)
#define DTFSL105               (*(volatile uint32 *)0xFFFFAA60)
#define DTFST105               (*(volatile uint32 *)0xFFFFAA64)
#define DTFSS105               (*(volatile uint32 *)0xFFFFAA68)
#define DTFSC105               (*(volatile uint32 *)0xFFFFAA6C)
#define DTSA106                (*(volatile uint32 *)0xFFFFAA80)
#define DTDA106                (*(volatile uint32 *)0xFFFFAA84)
#define DTTC106                (*(volatile uint32 *)0xFFFFAA88)
#define DTTCT106               (*(volatile uint32 *)0xFFFFAA8C)
#define DTRSA106               (*(volatile uint32 *)0xFFFFAA90)
#define DTRDA106               (*(volatile uint32 *)0xFFFFAA94)
#define DTRTC106               (*(volatile uint32 *)0xFFFFAA98)
#define DTTCC106               (*(volatile uint32 *)0xFFFFAA9C)
#define DTFSL106               (*(volatile uint32 *)0xFFFFAAA0)
#define DTFST106               (*(volatile uint32 *)0xFFFFAAA4)
#define DTFSS106               (*(volatile uint32 *)0xFFFFAAA8)
#define DTFSC106               (*(volatile uint32 *)0xFFFFAAAC)
#define DTSA107                (*(volatile uint32 *)0xFFFFAAC0)
#define DTDA107                (*(volatile uint32 *)0xFFFFAAC4)
#define DTTC107                (*(volatile uint32 *)0xFFFFAAC8)
#define DTTCT107               (*(volatile uint32 *)0xFFFFAACC)
#define DTRSA107               (*(volatile uint32 *)0xFFFFAAD0)
#define DTRDA107               (*(volatile uint32 *)0xFFFFAAD4)
#define DTRTC107               (*(volatile uint32 *)0xFFFFAAD8)
#define DTTCC107               (*(volatile uint32 *)0xFFFFAADC)
#define DTFSL107               (*(volatile uint32 *)0xFFFFAAE0)
#define DTFST107               (*(volatile uint32 *)0xFFFFAAE4)
#define DTFSS107               (*(volatile uint32 *)0xFFFFAAE8)
#define DTFSC107               (*(volatile uint32 *)0xFFFFAAEC)
#define DTSA108                (*(volatile uint32 *)0xFFFFAB00)
#define DTDA108                (*(volatile uint32 *)0xFFFFAB04)
#define DTTC108                (*(volatile uint32 *)0xFFFFAB08)
#define DTTCT108               (*(volatile uint32 *)0xFFFFAB0C)
#define DTRSA108               (*(volatile uint32 *)0xFFFFAB10)
#define DTRDA108               (*(volatile uint32 *)0xFFFFAB14)
#define DTRTC108               (*(volatile uint32 *)0xFFFFAB18)
#define DTTCC108               (*(volatile uint32 *)0xFFFFAB1C)
#define DTFSL108               (*(volatile uint32 *)0xFFFFAB20)
#define DTFST108               (*(volatile uint32 *)0xFFFFAB24)
#define DTFSS108               (*(volatile uint32 *)0xFFFFAB28)
#define DTFSC108               (*(volatile uint32 *)0xFFFFAB2C)
#define DTSA109                (*(volatile uint32 *)0xFFFFAB40)
#define DTDA109                (*(volatile uint32 *)0xFFFFAB44)
#define DTTC109                (*(volatile uint32 *)0xFFFFAB48)
#define DTTCT109               (*(volatile uint32 *)0xFFFFAB4C)
#define DTRSA109               (*(volatile uint32 *)0xFFFFAB50)
#define DTRDA109               (*(volatile uint32 *)0xFFFFAB54)
#define DTRTC109               (*(volatile uint32 *)0xFFFFAB58)
#define DTTCC109               (*(volatile uint32 *)0xFFFFAB5C)
#define DTFSL109               (*(volatile uint32 *)0xFFFFAB60)
#define DTFST109               (*(volatile uint32 *)0xFFFFAB64)
#define DTFSS109               (*(volatile uint32 *)0xFFFFAB68)
#define DTFSC109               (*(volatile uint32 *)0xFFFFAB6C)
#define DTSA110                (*(volatile uint32 *)0xFFFFAB80)
#define DTDA110                (*(volatile uint32 *)0xFFFFAB84)
#define DTTC110                (*(volatile uint32 *)0xFFFFAB88)
#define DTTCT110               (*(volatile uint32 *)0xFFFFAB8C)
#define DTRSA110               (*(volatile uint32 *)0xFFFFAB90)
#define DTRDA110               (*(volatile uint32 *)0xFFFFAB94)
#define DTRTC110               (*(volatile uint32 *)0xFFFFAB98)
#define DTTCC110               (*(volatile uint32 *)0xFFFFAB9C)
#define DTFSL110               (*(volatile uint32 *)0xFFFFABA0)
#define DTFST110               (*(volatile uint32 *)0xFFFFABA4)
#define DTFSS110               (*(volatile uint32 *)0xFFFFABA8)
#define DTFSC110               (*(volatile uint32 *)0xFFFFABAC)
#define DTSA111                (*(volatile uint32 *)0xFFFFABC0)
#define DTDA111                (*(volatile uint32 *)0xFFFFABC4)
#define DTTC111                (*(volatile uint32 *)0xFFFFABC8)
#define DTTCT111               (*(volatile uint32 *)0xFFFFABCC)
#define DTRSA111               (*(volatile uint32 *)0xFFFFABD0)
#define DTRDA111               (*(volatile uint32 *)0xFFFFABD4)
#define DTRTC111               (*(volatile uint32 *)0xFFFFABD8)
#define DTTCC111               (*(volatile uint32 *)0xFFFFABDC)
#define DTFSL111               (*(volatile uint32 *)0xFFFFABE0)
#define DTFST111               (*(volatile uint32 *)0xFFFFABE4)
#define DTFSS111               (*(volatile uint32 *)0xFFFFABE8)
#define DTFSC111               (*(volatile uint32 *)0xFFFFABEC)
#define DTSA112                (*(volatile uint32 *)0xFFFFAC00)
#define DTDA112                (*(volatile uint32 *)0xFFFFAC04)
#define DTTC112                (*(volatile uint32 *)0xFFFFAC08)
#define DTTCT112               (*(volatile uint32 *)0xFFFFAC0C)
#define DTRSA112               (*(volatile uint32 *)0xFFFFAC10)
#define DTRDA112               (*(volatile uint32 *)0xFFFFAC14)
#define DTRTC112               (*(volatile uint32 *)0xFFFFAC18)
#define DTTCC112               (*(volatile uint32 *)0xFFFFAC1C)
#define DTFSL112               (*(volatile uint32 *)0xFFFFAC20)
#define DTFST112               (*(volatile uint32 *)0xFFFFAC24)
#define DTFSS112               (*(volatile uint32 *)0xFFFFAC28)
#define DTFSC112               (*(volatile uint32 *)0xFFFFAC2C)
#define DTSA113                (*(volatile uint32 *)0xFFFFAC40)
#define DTDA113                (*(volatile uint32 *)0xFFFFAC44)
#define DTTC113                (*(volatile uint32 *)0xFFFFAC48)
#define DTTCT113               (*(volatile uint32 *)0xFFFFAC4C)
#define DTRSA113               (*(volatile uint32 *)0xFFFFAC50)
#define DTRDA113               (*(volatile uint32 *)0xFFFFAC54)
#define DTRTC113               (*(volatile uint32 *)0xFFFFAC58)
#define DTTCC113               (*(volatile uint32 *)0xFFFFAC5C)
#define DTFSL113               (*(volatile uint32 *)0xFFFFAC60)
#define DTFST113               (*(volatile uint32 *)0xFFFFAC64)
#define DTFSS113               (*(volatile uint32 *)0xFFFFAC68)
#define DTFSC113               (*(volatile uint32 *)0xFFFFAC6C)
#define DTSA114                (*(volatile uint32 *)0xFFFFAC80)
#define DTDA114                (*(volatile uint32 *)0xFFFFAC84)
#define DTTC114                (*(volatile uint32 *)0xFFFFAC88)
#define DTTCT114               (*(volatile uint32 *)0xFFFFAC8C)
#define DTRSA114               (*(volatile uint32 *)0xFFFFAC90)
#define DTRDA114               (*(volatile uint32 *)0xFFFFAC94)
#define DTRTC114               (*(volatile uint32 *)0xFFFFAC98)
#define DTTCC114               (*(volatile uint32 *)0xFFFFAC9C)
#define DTFSL114               (*(volatile uint32 *)0xFFFFACA0)
#define DTFST114               (*(volatile uint32 *)0xFFFFACA4)
#define DTFSS114               (*(volatile uint32 *)0xFFFFACA8)
#define DTFSC114               (*(volatile uint32 *)0xFFFFACAC)
#define DTSA115                (*(volatile uint32 *)0xFFFFACC0)
#define DTDA115                (*(volatile uint32 *)0xFFFFACC4)
#define DTTC115                (*(volatile uint32 *)0xFFFFACC8)
#define DTTCT115               (*(volatile uint32 *)0xFFFFACCC)
#define DTRSA115               (*(volatile uint32 *)0xFFFFACD0)
#define DTRDA115               (*(volatile uint32 *)0xFFFFACD4)
#define DTRTC115               (*(volatile uint32 *)0xFFFFACD8)
#define DTTCC115               (*(volatile uint32 *)0xFFFFACDC)
#define DTFSL115               (*(volatile uint32 *)0xFFFFACE0)
#define DTFST115               (*(volatile uint32 *)0xFFFFACE4)
#define DTFSS115               (*(volatile uint32 *)0xFFFFACE8)
#define DTFSC115               (*(volatile uint32 *)0xFFFFACEC)
#define DTSA116                (*(volatile uint32 *)0xFFFFAD00)
#define DTDA116                (*(volatile uint32 *)0xFFFFAD04)
#define DTTC116                (*(volatile uint32 *)0xFFFFAD08)
#define DTTCT116               (*(volatile uint32 *)0xFFFFAD0C)
#define DTRSA116               (*(volatile uint32 *)0xFFFFAD10)
#define DTRDA116               (*(volatile uint32 *)0xFFFFAD14)
#define DTRTC116               (*(volatile uint32 *)0xFFFFAD18)
#define DTTCC116               (*(volatile uint32 *)0xFFFFAD1C)
#define DTFSL116               (*(volatile uint32 *)0xFFFFAD20)
#define DTFST116               (*(volatile uint32 *)0xFFFFAD24)
#define DTFSS116               (*(volatile uint32 *)0xFFFFAD28)
#define DTFSC116               (*(volatile uint32 *)0xFFFFAD2C)
#define DTSA117                (*(volatile uint32 *)0xFFFFAD40)
#define DTDA117                (*(volatile uint32 *)0xFFFFAD44)
#define DTTC117                (*(volatile uint32 *)0xFFFFAD48)
#define DTTCT117               (*(volatile uint32 *)0xFFFFAD4C)
#define DTRSA117               (*(volatile uint32 *)0xFFFFAD50)
#define DTRDA117               (*(volatile uint32 *)0xFFFFAD54)
#define DTRTC117               (*(volatile uint32 *)0xFFFFAD58)
#define DTTCC117               (*(volatile uint32 *)0xFFFFAD5C)
#define DTFSL117               (*(volatile uint32 *)0xFFFFAD60)
#define DTFST117               (*(volatile uint32 *)0xFFFFAD64)
#define DTFSS117               (*(volatile uint32 *)0xFFFFAD68)
#define DTFSC117               (*(volatile uint32 *)0xFFFFAD6C)
#define DTSA118                (*(volatile uint32 *)0xFFFFAD80)
#define DTDA118                (*(volatile uint32 *)0xFFFFAD84)
#define DTTC118                (*(volatile uint32 *)0xFFFFAD88)
#define DTTCT118               (*(volatile uint32 *)0xFFFFAD8C)
#define DTRSA118               (*(volatile uint32 *)0xFFFFAD90)
#define DTRDA118               (*(volatile uint32 *)0xFFFFAD94)
#define DTRTC118               (*(volatile uint32 *)0xFFFFAD98)
#define DTTCC118               (*(volatile uint32 *)0xFFFFAD9C)
#define DTFSL118               (*(volatile uint32 *)0xFFFFADA0)
#define DTFST118               (*(volatile uint32 *)0xFFFFADA4)
#define DTFSS118               (*(volatile uint32 *)0xFFFFADA8)
#define DTFSC118               (*(volatile uint32 *)0xFFFFADAC)
#define DTSA119                (*(volatile uint32 *)0xFFFFADC0)
#define DTDA119                (*(volatile uint32 *)0xFFFFADC4)
#define DTTC119                (*(volatile uint32 *)0xFFFFADC8)
#define DTTCT119               (*(volatile uint32 *)0xFFFFADCC)
#define DTRSA119               (*(volatile uint32 *)0xFFFFADD0)
#define DTRDA119               (*(volatile uint32 *)0xFFFFADD4)
#define DTRTC119               (*(volatile uint32 *)0xFFFFADD8)
#define DTTCC119               (*(volatile uint32 *)0xFFFFADDC)
#define DTFSL119               (*(volatile uint32 *)0xFFFFADE0)
#define DTFST119               (*(volatile uint32 *)0xFFFFADE4)
#define DTFSS119               (*(volatile uint32 *)0xFFFFADE8)
#define DTFSC119               (*(volatile uint32 *)0xFFFFADEC)
#define DTSA120                (*(volatile uint32 *)0xFFFFAE00)
#define DTDA120                (*(volatile uint32 *)0xFFFFAE04)
#define DTTC120                (*(volatile uint32 *)0xFFFFAE08)
#define DTTCT120               (*(volatile uint32 *)0xFFFFAE0C)
#define DTRSA120               (*(volatile uint32 *)0xFFFFAE10)
#define DTRDA120               (*(volatile uint32 *)0xFFFFAE14)
#define DTRTC120               (*(volatile uint32 *)0xFFFFAE18)
#define DTTCC120               (*(volatile uint32 *)0xFFFFAE1C)
#define DTFSL120               (*(volatile uint32 *)0xFFFFAE20)
#define DTFST120               (*(volatile uint32 *)0xFFFFAE24)
#define DTFSS120               (*(volatile uint32 *)0xFFFFAE28)
#define DTFSC120               (*(volatile uint32 *)0xFFFFAE2C)
#define DTSA121                (*(volatile uint32 *)0xFFFFAE40)
#define DTDA121                (*(volatile uint32 *)0xFFFFAE44)
#define DTTC121                (*(volatile uint32 *)0xFFFFAE48)
#define DTTCT121               (*(volatile uint32 *)0xFFFFAE4C)
#define DTRSA121               (*(volatile uint32 *)0xFFFFAE50)
#define DTRDA121               (*(volatile uint32 *)0xFFFFAE54)
#define DTRTC121               (*(volatile uint32 *)0xFFFFAE58)
#define DTTCC121               (*(volatile uint32 *)0xFFFFAE5C)
#define DTFSL121               (*(volatile uint32 *)0xFFFFAE60)
#define DTFST121               (*(volatile uint32 *)0xFFFFAE64)
#define DTFSS121               (*(volatile uint32 *)0xFFFFAE68)
#define DTFSC121               (*(volatile uint32 *)0xFFFFAE6C)
#define DTSA122                (*(volatile uint32 *)0xFFFFAE80)
#define DTDA122                (*(volatile uint32 *)0xFFFFAE84)
#define DTTC122                (*(volatile uint32 *)0xFFFFAE88)
#define DTTCT122               (*(volatile uint32 *)0xFFFFAE8C)
#define DTRSA122               (*(volatile uint32 *)0xFFFFAE90)
#define DTRDA122               (*(volatile uint32 *)0xFFFFAE94)
#define DTRTC122               (*(volatile uint32 *)0xFFFFAE98)
#define DTTCC122               (*(volatile uint32 *)0xFFFFAE9C)
#define DTFSL122               (*(volatile uint32 *)0xFFFFAEA0)
#define DTFST122               (*(volatile uint32 *)0xFFFFAEA4)
#define DTFSS122               (*(volatile uint32 *)0xFFFFAEA8)
#define DTFSC122               (*(volatile uint32 *)0xFFFFAEAC)
#define DTSA123                (*(volatile uint32 *)0xFFFFAEC0)
#define DTDA123                (*(volatile uint32 *)0xFFFFAEC4)
#define DTTC123                (*(volatile uint32 *)0xFFFFAEC8)
#define DTTCT123               (*(volatile uint32 *)0xFFFFAECC)
#define DTRSA123               (*(volatile uint32 *)0xFFFFAED0)
#define DTRDA123               (*(volatile uint32 *)0xFFFFAED4)
#define DTRTC123               (*(volatile uint32 *)0xFFFFAED8)
#define DTTCC123               (*(volatile uint32 *)0xFFFFAEDC)
#define DTFSL123               (*(volatile uint32 *)0xFFFFAEE0)
#define DTFST123               (*(volatile uint32 *)0xFFFFAEE4)
#define DTFSS123               (*(volatile uint32 *)0xFFFFAEE8)
#define DTFSC123               (*(volatile uint32 *)0xFFFFAEEC)
#define DTSA124                (*(volatile uint32 *)0xFFFFAF00)
#define DTDA124                (*(volatile uint32 *)0xFFFFAF04)
#define DTTC124                (*(volatile uint32 *)0xFFFFAF08)
#define DTTCT124               (*(volatile uint32 *)0xFFFFAF0C)
#define DTRSA124               (*(volatile uint32 *)0xFFFFAF10)
#define DTRDA124               (*(volatile uint32 *)0xFFFFAF14)
#define DTRTC124               (*(volatile uint32 *)0xFFFFAF18)
#define DTTCC124               (*(volatile uint32 *)0xFFFFAF1C)
#define DTFSL124               (*(volatile uint32 *)0xFFFFAF20)
#define DTFST124               (*(volatile uint32 *)0xFFFFAF24)
#define DTFSS124               (*(volatile uint32 *)0xFFFFAF28)
#define DTFSC124               (*(volatile uint32 *)0xFFFFAF2C)
#define DTSA125                (*(volatile uint32 *)0xFFFFAF40)
#define DTDA125                (*(volatile uint32 *)0xFFFFAF44)
#define DTTC125                (*(volatile uint32 *)0xFFFFAF48)
#define DTTCT125               (*(volatile uint32 *)0xFFFFAF4C)
#define DTRSA125               (*(volatile uint32 *)0xFFFFAF50)
#define DTRDA125               (*(volatile uint32 *)0xFFFFAF54)
#define DTRTC125               (*(volatile uint32 *)0xFFFFAF58)
#define DTTCC125               (*(volatile uint32 *)0xFFFFAF5C)
#define DTFSL125               (*(volatile uint32 *)0xFFFFAF60)
#define DTFST125               (*(volatile uint32 *)0xFFFFAF64)
#define DTFSS125               (*(volatile uint32 *)0xFFFFAF68)
#define DTFSC125               (*(volatile uint32 *)0xFFFFAF6C)
#define DTSA126                (*(volatile uint32 *)0xFFFFAF80)
#define DTDA126                (*(volatile uint32 *)0xFFFFAF84)
#define DTTC126                (*(volatile uint32 *)0xFFFFAF88)
#define DTTCT126               (*(volatile uint32 *)0xFFFFAF8C)
#define DTRSA126               (*(volatile uint32 *)0xFFFFAF90)
#define DTRDA126               (*(volatile uint32 *)0xFFFFAF94)
#define DTRTC126               (*(volatile uint32 *)0xFFFFAF98)
#define DTTCC126               (*(volatile uint32 *)0xFFFFAF9C)
#define DTFSL126               (*(volatile uint32 *)0xFFFFAFA0)
#define DTFST126               (*(volatile uint32 *)0xFFFFAFA4)
#define DTFSS126               (*(volatile uint32 *)0xFFFFAFA8)
#define DTFSC126               (*(volatile uint32 *)0xFFFFAFAC)
#define DTSA127                (*(volatile uint32 *)0xFFFFAFC0)
#define DTDA127                (*(volatile uint32 *)0xFFFFAFC4)
#define DTTC127                (*(volatile uint32 *)0xFFFFAFC8)
#define DTTCT127               (*(volatile uint32 *)0xFFFFAFCC)
#define DTRSA127               (*(volatile uint32 *)0xFFFFAFD0)
#define DTRDA127               (*(volatile uint32 *)0xFFFFAFD4)
#define DTRTC127               (*(volatile uint32 *)0xFFFFAFD8)
#define DTTCC127               (*(volatile uint32 *)0xFFFFAFDC)
#define DTFSL127               (*(volatile uint32 *)0xFFFFAFE0)
#define DTFST127               (*(volatile uint32 *)0xFFFFAFE4)
#define DTFSS127               (*(volatile uint32 *)0xFFFFAFE8)
#define DTFSC127               (*(volatile uint32 *)0xFFFFAFEC)
#define EIC32                  (*(volatile uint16 *)0xFFFFB040)
#define EIC32L                 (*(volatile uint8  *)0xFFFFB040)
#define EIC32H                 (*(volatile uint8  *)0xFFFFB041)
#define EIC33                  (*(volatile uint16 *)0xFFFFB042)
#define EIC33L                 (*(volatile uint8  *)0xFFFFB042)
#define EIC33H                 (*(volatile uint8  *)0xFFFFB043)
#define EIC34                  (*(volatile uint16 *)0xFFFFB044)
#define EIC34L                 (*(volatile uint8  *)0xFFFFB044)
#define EIC34H                 (*(volatile uint8  *)0xFFFFB045)
#define EIC35                  (*(volatile uint16 *)0xFFFFB046)
#define EIC35L                 (*(volatile uint8  *)0xFFFFB046)
#define EIC35H                 (*(volatile uint8  *)0xFFFFB047)
#define EIC36                  (*(volatile uint16 *)0xFFFFB048)
#define EIC36L                 (*(volatile uint8  *)0xFFFFB048)
#define EIC36H                 (*(volatile uint8  *)0xFFFFB049)
#define EIC37                  (*(volatile uint16 *)0xFFFFB04A)
#define EIC37L                 (*(volatile uint8  *)0xFFFFB04A)
#define EIC37H                 (*(volatile uint8  *)0xFFFFB04B)
#define EIC38                  (*(volatile uint16 *)0xFFFFB04C)
#define EIC38L                 (*(volatile uint8  *)0xFFFFB04C)
#define EIC38H                 (*(volatile uint8  *)0xFFFFB04D)
#define EIC39                  (*(volatile uint16 *)0xFFFFB04E)
#define EIC39L                 (*(volatile uint8  *)0xFFFFB04E)
#define EIC39H                 (*(volatile uint8  *)0xFFFFB04F)
#define EIC40                  (*(volatile uint16 *)0xFFFFB050)
#define EIC40L                 (*(volatile uint8  *)0xFFFFB050)
#define EIC40H                 (*(volatile uint8  *)0xFFFFB051)
#define EIC41                  (*(volatile uint16 *)0xFFFFB052)
#define EIC41L                 (*(volatile uint8  *)0xFFFFB052)
#define EIC41H                 (*(volatile uint8  *)0xFFFFB053)
#define EIC42                  (*(volatile uint16 *)0xFFFFB054)
#define EIC42L                 (*(volatile uint8  *)0xFFFFB054)
#define EIC42H                 (*(volatile uint8  *)0xFFFFB055)
#define EIC43                  (*(volatile uint16 *)0xFFFFB056)
#define EIC43L                 (*(volatile uint8  *)0xFFFFB056)
#define EIC43H                 (*(volatile uint8  *)0xFFFFB057)
#define EIC44                  (*(volatile uint16 *)0xFFFFB058)
#define EIC44L                 (*(volatile uint8  *)0xFFFFB058)
#define EIC44H                 (*(volatile uint8  *)0xFFFFB059)
#define EIC45                  (*(volatile uint16 *)0xFFFFB05A)
#define EIC45L                 (*(volatile uint8  *)0xFFFFB05A)
#define EIC45H                 (*(volatile uint8  *)0xFFFFB05B)
#define EIC46                  (*(volatile uint16 *)0xFFFFB05C)
#define EIC46L                 (*(volatile uint8  *)0xFFFFB05C)
#define EIC46H                 (*(volatile uint8  *)0xFFFFB05D)
#define EIC47                  (*(volatile uint16 *)0xFFFFB05E)
#define EIC47L                 (*(volatile uint8  *)0xFFFFB05E)
#define EIC47H                 (*(volatile uint8  *)0xFFFFB05F)
#define EIC48                  (*(volatile uint16 *)0xFFFFB060)
#define EIC48L                 (*(volatile uint8  *)0xFFFFB060)
#define EIC48H                 (*(volatile uint8  *)0xFFFFB061)
#define EIC49                  (*(volatile uint16 *)0xFFFFB062)
#define EIC49L                 (*(volatile uint8  *)0xFFFFB062)
#define EIC49H                 (*(volatile uint8  *)0xFFFFB063)
#define EIC50                  (*(volatile uint16 *)0xFFFFB064)
#define EIC50L                 (*(volatile uint8  *)0xFFFFB064)
#define EIC50H                 (*(volatile uint8  *)0xFFFFB065)
#define EIC51                  (*(volatile uint16 *)0xFFFFB066)
#define EIC51L                 (*(volatile uint8  *)0xFFFFB066)
#define EIC51H                 (*(volatile uint8  *)0xFFFFB067)
#define EIC52                  (*(volatile uint16 *)0xFFFFB068)
#define EIC52L                 (*(volatile uint8  *)0xFFFFB068)
#define EIC52H                 (*(volatile uint8  *)0xFFFFB069)
#define EIC53                  (*(volatile uint16 *)0xFFFFB06A)
#define EIC53L                 (*(volatile uint8  *)0xFFFFB06A)
#define EIC53H                 (*(volatile uint8  *)0xFFFFB06B)
#define EIC54                  (*(volatile uint16 *)0xFFFFB06C)
#define EIC54L                 (*(volatile uint8  *)0xFFFFB06C)
#define EIC54H                 (*(volatile uint8  *)0xFFFFB06D)
#define EIC55                  (*(volatile uint16 *)0xFFFFB06E)
#define EIC55L                 (*(volatile uint8  *)0xFFFFB06E)
#define EIC55H                 (*(volatile uint8  *)0xFFFFB06F)
#define EIC56                  (*(volatile uint16 *)0xFFFFB070)
#define EIC56L                 (*(volatile uint8  *)0xFFFFB070)
#define EIC56H                 (*(volatile uint8  *)0xFFFFB071)
#define EIC57                  (*(volatile uint16 *)0xFFFFB072)
#define EIC57L                 (*(volatile uint8  *)0xFFFFB072)
#define EIC57H                 (*(volatile uint8  *)0xFFFFB073)
#define EIC58                  (*(volatile uint16 *)0xFFFFB074)
#define EIC58L                 (*(volatile uint8  *)0xFFFFB074)
#define EIC58H                 (*(volatile uint8  *)0xFFFFB075)
#define EIC59                  (*(volatile uint16 *)0xFFFFB076)
#define EIC59L                 (*(volatile uint8  *)0xFFFFB076)
#define EIC59H                 (*(volatile uint8  *)0xFFFFB077)
#define EIC60                  (*(volatile uint16 *)0xFFFFB078)
#define EIC60L                 (*(volatile uint8  *)0xFFFFB078)
#define EIC60H                 (*(volatile uint8  *)0xFFFFB079)
#define EIC61                  (*(volatile uint16 *)0xFFFFB07A)
#define EIC61L                 (*(volatile uint8  *)0xFFFFB07A)
#define EIC61H                 (*(volatile uint8  *)0xFFFFB07B)
#define EIC62                  (*(volatile uint16 *)0xFFFFB07C)
#define EIC62L                 (*(volatile uint8  *)0xFFFFB07C)
#define EIC62H                 (*(volatile uint8  *)0xFFFFB07D)
#define EIC63                  (*(volatile uint16 *)0xFFFFB07E)
#define EIC63L                 (*(volatile uint8  *)0xFFFFB07E)
#define EIC63H                 (*(volatile uint8  *)0xFFFFB07F)
#define EIC64                  (*(volatile uint16 *)0xFFFFB080)
#define EIC64L                 (*(volatile uint8  *)0xFFFFB080)
#define EIC64H                 (*(volatile uint8  *)0xFFFFB081)
#define EIC65                  (*(volatile uint16 *)0xFFFFB082)
#define EIC65L                 (*(volatile uint8  *)0xFFFFB082)
#define EIC65H                 (*(volatile uint8  *)0xFFFFB083)
#define EIC66                  (*(volatile uint16 *)0xFFFFB084)
#define EIC66L                 (*(volatile uint8  *)0xFFFFB084)
#define EIC66H                 (*(volatile uint8  *)0xFFFFB085)
#define EIC67                  (*(volatile uint16 *)0xFFFFB086)
#define EIC67L                 (*(volatile uint8  *)0xFFFFB086)
#define EIC67H                 (*(volatile uint8  *)0xFFFFB087)
#define EIC68                  (*(volatile uint16 *)0xFFFFB088)
#define EIC68L                 (*(volatile uint8  *)0xFFFFB088)
#define EIC68H                 (*(volatile uint8  *)0xFFFFB089)
#define EIC69                  (*(volatile uint16 *)0xFFFFB08A)
#define EIC69L                 (*(volatile uint8  *)0xFFFFB08A)
#define EIC69H                 (*(volatile uint8  *)0xFFFFB08B)
#define EIC70                  (*(volatile uint16 *)0xFFFFB08C)
#define EIC70L                 (*(volatile uint8  *)0xFFFFB08C)
#define EIC70H                 (*(volatile uint8  *)0xFFFFB08D)
#define EIC71                  (*(volatile uint16 *)0xFFFFB08E)
#define EIC71L                 (*(volatile uint8  *)0xFFFFB08E)
#define EIC71H                 (*(volatile uint8  *)0xFFFFB08F)
#define EIC72                  (*(volatile uint16 *)0xFFFFB090)
#define EIC72L                 (*(volatile uint8  *)0xFFFFB090)
#define EIC72H                 (*(volatile uint8  *)0xFFFFB091)
#define EIC73                  (*(volatile uint16 *)0xFFFFB092)
#define EIC73L                 (*(volatile uint8  *)0xFFFFB092)
#define EIC73H                 (*(volatile uint8  *)0xFFFFB093)
#define EIC74                  (*(volatile uint16 *)0xFFFFB094)
#define EIC74L                 (*(volatile uint8  *)0xFFFFB094)
#define EIC74H                 (*(volatile uint8  *)0xFFFFB095)
#define EIC75                  (*(volatile uint16 *)0xFFFFB096)
#define EIC75L                 (*(volatile uint8  *)0xFFFFB096)
#define EIC75H                 (*(volatile uint8  *)0xFFFFB097)
#define EIC76                  (*(volatile uint16 *)0xFFFFB098)
#define EIC76L                 (*(volatile uint8  *)0xFFFFB098)
#define EIC76H                 (*(volatile uint8  *)0xFFFFB099)
#define EIC77                  (*(volatile uint16 *)0xFFFFB09A)
#define EIC77L                 (*(volatile uint8  *)0xFFFFB09A)
#define EIC77H                 (*(volatile uint8  *)0xFFFFB09B)
#define EIC78                  (*(volatile uint16 *)0xFFFFB09C)
#define EIC78L                 (*(volatile uint8  *)0xFFFFB09C)
#define EIC78H                 (*(volatile uint8  *)0xFFFFB09D)
#define EIC79                  (*(volatile uint16 *)0xFFFFB09E)
#define EIC79L                 (*(volatile uint8  *)0xFFFFB09E)
#define EIC79H                 (*(volatile uint8  *)0xFFFFB09F)
#define EIC80                  (*(volatile uint16 *)0xFFFFB0A0)
#define EIC80L                 (*(volatile uint8  *)0xFFFFB0A0)
#define EIC80H                 (*(volatile uint8  *)0xFFFFB0A1)
#define EIC81                  (*(volatile uint16 *)0xFFFFB0A2)
#define EIC81L                 (*(volatile uint8  *)0xFFFFB0A2)
#define EIC81H                 (*(volatile uint8  *)0xFFFFB0A3)
#define EIC82                  (*(volatile uint16 *)0xFFFFB0A4)
#define EIC82L                 (*(volatile uint8  *)0xFFFFB0A4)
#define EIC82H                 (*(volatile uint8  *)0xFFFFB0A5)
#define EIC83                  (*(volatile uint16 *)0xFFFFB0A6)
#define EIC83L                 (*(volatile uint8  *)0xFFFFB0A6)
#define EIC83H                 (*(volatile uint8  *)0xFFFFB0A7)
#define EIC84                  (*(volatile uint16 *)0xFFFFB0A8)
#define EIC84L                 (*(volatile uint8  *)0xFFFFB0A8)
#define EIC84H                 (*(volatile uint8  *)0xFFFFB0A9)
#define EIC85                  (*(volatile uint16 *)0xFFFFB0AA)
#define EIC85L                 (*(volatile uint8  *)0xFFFFB0AA)
#define EIC85H                 (*(volatile uint8  *)0xFFFFB0AB)
#define EIC86                  (*(volatile uint16 *)0xFFFFB0AC)
#define EIC86L                 (*(volatile uint8  *)0xFFFFB0AC)
#define EIC86H                 (*(volatile uint8  *)0xFFFFB0AD)
#define EIC87                  (*(volatile uint16 *)0xFFFFB0AE)
#define EIC87L                 (*(volatile uint8  *)0xFFFFB0AE)
#define EIC87H                 (*(volatile uint8  *)0xFFFFB0AF)
#define EIC88                  (*(volatile uint16 *)0xFFFFB0B0)
#define EIC88L                 (*(volatile uint8  *)0xFFFFB0B0)
#define EIC88H                 (*(volatile uint8  *)0xFFFFB0B1)
#define EIC89                  (*(volatile uint16 *)0xFFFFB0B2)
#define EIC89L                 (*(volatile uint8  *)0xFFFFB0B2)
#define EIC89H                 (*(volatile uint8  *)0xFFFFB0B3)
#define EIC90                  (*(volatile uint16 *)0xFFFFB0B4)
#define EIC90L                 (*(volatile uint8  *)0xFFFFB0B4)
#define EIC90H                 (*(volatile uint8  *)0xFFFFB0B5)
#define EIC91                  (*(volatile uint16 *)0xFFFFB0B6)
#define EIC91L                 (*(volatile uint8  *)0xFFFFB0B6)
#define EIC91H                 (*(volatile uint8  *)0xFFFFB0B7)
#define EIC92                  (*(volatile uint16 *)0xFFFFB0B8)
#define EIC92L                 (*(volatile uint8  *)0xFFFFB0B8)
#define EIC92H                 (*(volatile uint8  *)0xFFFFB0B9)
#define EIC93                  (*(volatile uint16 *)0xFFFFB0BA)
#define EIC93L                 (*(volatile uint8  *)0xFFFFB0BA)
#define EIC93H                 (*(volatile uint8  *)0xFFFFB0BB)
#define EIC94                  (*(volatile uint16 *)0xFFFFB0BC)
#define EIC94L                 (*(volatile uint8  *)0xFFFFB0BC)
#define EIC94H                 (*(volatile uint8  *)0xFFFFB0BD)
#define EIC95                  (*(volatile uint16 *)0xFFFFB0BE)
#define EIC95L                 (*(volatile uint8  *)0xFFFFB0BE)
#define EIC95H                 (*(volatile uint8  *)0xFFFFB0BF)
#define EIC96                  (*(volatile uint16 *)0xFFFFB0C0)
#define EIC96L                 (*(volatile uint8  *)0xFFFFB0C0)
#define EIC96H                 (*(volatile uint8  *)0xFFFFB0C1)
#define EIC97                  (*(volatile uint16 *)0xFFFFB0C2)
#define EIC97L                 (*(volatile uint8  *)0xFFFFB0C2)
#define EIC97H                 (*(volatile uint8  *)0xFFFFB0C3)
#define EIC98                  (*(volatile uint16 *)0xFFFFB0C4)
#define EIC98L                 (*(volatile uint8  *)0xFFFFB0C4)
#define EIC98H                 (*(volatile uint8  *)0xFFFFB0C5)
#define EIC99                  (*(volatile uint16 *)0xFFFFB0C6)
#define EIC99L                 (*(volatile uint8  *)0xFFFFB0C6)
#define EIC99H                 (*(volatile uint8  *)0xFFFFB0C7)
#define EIC100                 (*(volatile uint16 *)0xFFFFB0C8)
#define EIC100L                (*(volatile uint8  *)0xFFFFB0C8)
#define EIC100H                (*(volatile uint8  *)0xFFFFB0C9)
#define EIC101                 (*(volatile uint16 *)0xFFFFB0CA)
#define EIC101L                (*(volatile uint8  *)0xFFFFB0CA)
#define EIC101H                (*(volatile uint8  *)0xFFFFB0CB)
#define EIC102                 (*(volatile uint16 *)0xFFFFB0CC)
#define EIC102L                (*(volatile uint8  *)0xFFFFB0CC)
#define EIC102H                (*(volatile uint8  *)0xFFFFB0CD)
#define EIC103                 (*(volatile uint16 *)0xFFFFB0CE)
#define EIC103L                (*(volatile uint8  *)0xFFFFB0CE)
#define EIC103H                (*(volatile uint8  *)0xFFFFB0CF)
#define EIC104                 (*(volatile uint16 *)0xFFFFB0D0)
#define EIC104L                (*(volatile uint8  *)0xFFFFB0D0)
#define EIC104H                (*(volatile uint8  *)0xFFFFB0D1)
#define EIC105                 (*(volatile uint16 *)0xFFFFB0D2)
#define EIC105L                (*(volatile uint8  *)0xFFFFB0D2)
#define EIC105H                (*(volatile uint8  *)0xFFFFB0D3)
#define EIC106                 (*(volatile uint16 *)0xFFFFB0D4)
#define EIC106L                (*(volatile uint8  *)0xFFFFB0D4)
#define EIC106H                (*(volatile uint8  *)0xFFFFB0D5)
#define EIC107                 (*(volatile uint16 *)0xFFFFB0D6)
#define EIC107L                (*(volatile uint8  *)0xFFFFB0D6)
#define EIC107H                (*(volatile uint8  *)0xFFFFB0D7)
#define EIC108                 (*(volatile uint16 *)0xFFFFB0D8)
#define EIC108L                (*(volatile uint8  *)0xFFFFB0D8)
#define EIC108H                (*(volatile uint8  *)0xFFFFB0D9)
#define EIC109                 (*(volatile uint16 *)0xFFFFB0DA)
#define EIC109L                (*(volatile uint8  *)0xFFFFB0DA)
#define EIC109H                (*(volatile uint8  *)0xFFFFB0DB)
#define EIC110                 (*(volatile uint16 *)0xFFFFB0DC)
#define EIC110L                (*(volatile uint8  *)0xFFFFB0DC)
#define EIC110H                (*(volatile uint8  *)0xFFFFB0DD)
#define EIC111                 (*(volatile uint16 *)0xFFFFB0DE)
#define EIC111L                (*(volatile uint8  *)0xFFFFB0DE)
#define EIC111H                (*(volatile uint8  *)0xFFFFB0DF)
#define EIC112                 (*(volatile uint16 *)0xFFFFB0E0)
#define EIC112L                (*(volatile uint8  *)0xFFFFB0E0)
#define EIC112H                (*(volatile uint8  *)0xFFFFB0E1)
#define EIC113                 (*(volatile uint16 *)0xFFFFB0E2)
#define EIC113L                (*(volatile uint8  *)0xFFFFB0E2)
#define EIC113H                (*(volatile uint8  *)0xFFFFB0E3)
#define EIC114                 (*(volatile uint16 *)0xFFFFB0E4)
#define EIC114L                (*(volatile uint8  *)0xFFFFB0E4)
#define EIC114H                (*(volatile uint8  *)0xFFFFB0E5)
#define EIC115                 (*(volatile uint16 *)0xFFFFB0E6)
#define EIC115L                (*(volatile uint8  *)0xFFFFB0E6)
#define EIC115H                (*(volatile uint8  *)0xFFFFB0E7)
#define EIC116                 (*(volatile uint16 *)0xFFFFB0E8)
#define EIC116L                (*(volatile uint8  *)0xFFFFB0E8)
#define EIC116H                (*(volatile uint8  *)0xFFFFB0E9)
#define EIC117                 (*(volatile uint16 *)0xFFFFB0EA)
#define EIC117L                (*(volatile uint8  *)0xFFFFB0EA)
#define EIC117H                (*(volatile uint8  *)0xFFFFB0EB)
#define EIC118                 (*(volatile uint16 *)0xFFFFB0EC)
#define EIC118L                (*(volatile uint8  *)0xFFFFB0EC)
#define EIC118H                (*(volatile uint8  *)0xFFFFB0ED)
#define EIC119                 (*(volatile uint16 *)0xFFFFB0EE)
#define EIC119L                (*(volatile uint8  *)0xFFFFB0EE)
#define EIC119H                (*(volatile uint8  *)0xFFFFB0EF)
#define EIC120                 (*(volatile uint16 *)0xFFFFB0F0)
#define EIC120L                (*(volatile uint8  *)0xFFFFB0F0)
#define EIC120H                (*(volatile uint8  *)0xFFFFB0F1)
#define EIC121                 (*(volatile uint16 *)0xFFFFB0F2)
#define EIC121L                (*(volatile uint8  *)0xFFFFB0F2)
#define EIC121H                (*(volatile uint8  *)0xFFFFB0F3)
#define EIC122                 (*(volatile uint16 *)0xFFFFB0F4)
#define EIC122L                (*(volatile uint8  *)0xFFFFB0F4)
#define EIC122H                (*(volatile uint8  *)0xFFFFB0F5)
#define EIC123                 (*(volatile uint16 *)0xFFFFB0F6)
#define EIC123L                (*(volatile uint8  *)0xFFFFB0F6)
#define EIC123H                (*(volatile uint8  *)0xFFFFB0F7)
#define EIC124                 (*(volatile uint16 *)0xFFFFB0F8)
#define EIC124L                (*(volatile uint8  *)0xFFFFB0F8)
#define EIC124H                (*(volatile uint8  *)0xFFFFB0F9)
#define EIC125                 (*(volatile uint16 *)0xFFFFB0FA)
#define EIC125L                (*(volatile uint8  *)0xFFFFB0FA)
#define EIC125H                (*(volatile uint8  *)0xFFFFB0FB)
#define EIC126                 (*(volatile uint16 *)0xFFFFB0FC)
#define EIC126L                (*(volatile uint8  *)0xFFFFB0FC)
#define EIC126H                (*(volatile uint8  *)0xFFFFB0FD)
#define EIC127                 (*(volatile uint16 *)0xFFFFB0FE)
#define EIC127L                (*(volatile uint8  *)0xFFFFB0FE)
#define EIC127H                (*(volatile uint8  *)0xFFFFB0FF)
#define EIC128                 (*(volatile uint16 *)0xFFFFB100)
#define EIC128L                (*(volatile uint8  *)0xFFFFB100)
#define EIC128H                (*(volatile uint8  *)0xFFFFB101)
#define EIC129                 (*(volatile uint16 *)0xFFFFB102)
#define EIC129L                (*(volatile uint8  *)0xFFFFB102)
#define EIC129H                (*(volatile uint8  *)0xFFFFB103)
#define EIC130                 (*(volatile uint16 *)0xFFFFB104)
#define EIC130L                (*(volatile uint8  *)0xFFFFB104)
#define EIC130H                (*(volatile uint8  *)0xFFFFB105)
#define EIC131                 (*(volatile uint16 *)0xFFFFB106)
#define EIC131L                (*(volatile uint8  *)0xFFFFB106)
#define EIC131H                (*(volatile uint8  *)0xFFFFB107)
#define EIC132                 (*(volatile uint16 *)0xFFFFB108)
#define EIC132L                (*(volatile uint8  *)0xFFFFB108)
#define EIC132H                (*(volatile uint8  *)0xFFFFB109)
#define EIC133                 (*(volatile uint16 *)0xFFFFB10A)
#define EIC133L                (*(volatile uint8  *)0xFFFFB10A)
#define EIC133H                (*(volatile uint8  *)0xFFFFB10B)
#define EIC134                 (*(volatile uint16 *)0xFFFFB10C)
#define EIC134L                (*(volatile uint8  *)0xFFFFB10C)
#define EIC134H                (*(volatile uint8  *)0xFFFFB10D)
#define EIC135                 (*(volatile uint16 *)0xFFFFB10E)
#define EIC135L                (*(volatile uint8  *)0xFFFFB10E)
#define EIC135H                (*(volatile uint8  *)0xFFFFB10F)
#define EIC136                 (*(volatile uint16 *)0xFFFFB110)
#define EIC136L                (*(volatile uint8  *)0xFFFFB110)
#define EIC136H                (*(volatile uint8  *)0xFFFFB111)
#define EIC137                 (*(volatile uint16 *)0xFFFFB112)
#define EIC137L                (*(volatile uint8  *)0xFFFFB112)
#define EIC137H                (*(volatile uint8  *)0xFFFFB113)
#define EIC138                 (*(volatile uint16 *)0xFFFFB114)
#define EIC138L                (*(volatile uint8  *)0xFFFFB114)
#define EIC138H                (*(volatile uint8  *)0xFFFFB115)
#define EIC139                 (*(volatile uint16 *)0xFFFFB116)
#define EIC139L                (*(volatile uint8  *)0xFFFFB116)
#define EIC139H                (*(volatile uint8  *)0xFFFFB117)
#define EIC140                 (*(volatile uint16 *)0xFFFFB118)
#define EIC140L                (*(volatile uint8  *)0xFFFFB118)
#define EIC140H                (*(volatile uint8  *)0xFFFFB119)
#define EIC141                 (*(volatile uint16 *)0xFFFFB11A)
#define EIC141L                (*(volatile uint8  *)0xFFFFB11A)
#define EIC141H                (*(volatile uint8  *)0xFFFFB11B)
#define EIC142                 (*(volatile uint16 *)0xFFFFB11C)
#define EIC142L                (*(volatile uint8  *)0xFFFFB11C)
#define EIC142H                (*(volatile uint8  *)0xFFFFB11D)
#define EIC143                 (*(volatile uint16 *)0xFFFFB11E)
#define EIC143L                (*(volatile uint8  *)0xFFFFB11E)
#define EIC143H                (*(volatile uint8  *)0xFFFFB11F)
#define EIC144                 (*(volatile uint16 *)0xFFFFB120)
#define EIC144L                (*(volatile uint8  *)0xFFFFB120)
#define EIC144H                (*(volatile uint8  *)0xFFFFB121)
#define EIC145                 (*(volatile uint16 *)0xFFFFB122)
#define EIC145L                (*(volatile uint8  *)0xFFFFB122)
#define EIC145H                (*(volatile uint8  *)0xFFFFB123)
#define EIC146                 (*(volatile uint16 *)0xFFFFB124)
#define EIC146L                (*(volatile uint8  *)0xFFFFB124)
#define EIC146H                (*(volatile uint8  *)0xFFFFB125)
#define EIC147                 (*(volatile uint16 *)0xFFFFB126)
#define EIC147L                (*(volatile uint8  *)0xFFFFB126)
#define EIC147H                (*(volatile uint8  *)0xFFFFB127)
#define EIC148                 (*(volatile uint16 *)0xFFFFB128)
#define EIC148L                (*(volatile uint8  *)0xFFFFB128)
#define EIC148H                (*(volatile uint8  *)0xFFFFB129)
#define EIC149                 (*(volatile uint16 *)0xFFFFB12A)
#define EIC149L                (*(volatile uint8  *)0xFFFFB12A)
#define EIC149H                (*(volatile uint8  *)0xFFFFB12B)
#define EIC150                 (*(volatile uint16 *)0xFFFFB12C)
#define EIC150L                (*(volatile uint8  *)0xFFFFB12C)
#define EIC150H                (*(volatile uint8  *)0xFFFFB12D)
#define EIC151                 (*(volatile uint16 *)0xFFFFB12E)
#define EIC151L                (*(volatile uint8  *)0xFFFFB12E)
#define EIC151H                (*(volatile uint8  *)0xFFFFB12F)
#define EIC152                 (*(volatile uint16 *)0xFFFFB130)
#define EIC152L                (*(volatile uint8  *)0xFFFFB130)
#define EIC152H                (*(volatile uint8  *)0xFFFFB131)
#define EIC153                 (*(volatile uint16 *)0xFFFFB132)
#define EIC153L                (*(volatile uint8  *)0xFFFFB132)
#define EIC153H                (*(volatile uint8  *)0xFFFFB133)
#define EIC154                 (*(volatile uint16 *)0xFFFFB134)
#define EIC154L                (*(volatile uint8  *)0xFFFFB134)
#define EIC154H                (*(volatile uint8  *)0xFFFFB135)
#define EIC155                 (*(volatile uint16 *)0xFFFFB136)
#define EIC155L                (*(volatile uint8  *)0xFFFFB136)
#define EIC155H                (*(volatile uint8  *)0xFFFFB137)
#define EIC156                 (*(volatile uint16 *)0xFFFFB138)
#define EIC156L                (*(volatile uint8  *)0xFFFFB138)
#define EIC156H                (*(volatile uint8  *)0xFFFFB139)
#define EIC157                 (*(volatile uint16 *)0xFFFFB13A)
#define EIC157L                (*(volatile uint8  *)0xFFFFB13A)
#define EIC157H                (*(volatile uint8  *)0xFFFFB13B)
#define EIC158                 (*(volatile uint16 *)0xFFFFB13C)
#define EIC158L                (*(volatile uint8  *)0xFFFFB13C)
#define EIC158H                (*(volatile uint8  *)0xFFFFB13D)
#define EIC159                 (*(volatile uint16 *)0xFFFFB13E)
#define EIC159L                (*(volatile uint8  *)0xFFFFB13E)
#define EIC159H                (*(volatile uint8  *)0xFFFFB13F)
#define EIC160                 (*(volatile uint16 *)0xFFFFB140)
#define EIC160L                (*(volatile uint8  *)0xFFFFB140)
#define EIC160H                (*(volatile uint8  *)0xFFFFB141)
#define EIC161                 (*(volatile uint16 *)0xFFFFB142)
#define EIC161L                (*(volatile uint8  *)0xFFFFB142)
#define EIC161H                (*(volatile uint8  *)0xFFFFB143)
#define EIC162                 (*(volatile uint16 *)0xFFFFB144)
#define EIC162L                (*(volatile uint8  *)0xFFFFB144)
#define EIC162H                (*(volatile uint8  *)0xFFFFB145)
#define EIC163                 (*(volatile uint16 *)0xFFFFB146)
#define EIC163L                (*(volatile uint8  *)0xFFFFB146)
#define EIC163H                (*(volatile uint8  *)0xFFFFB147)
#define EIC164                 (*(volatile uint16 *)0xFFFFB148)
#define EIC164L                (*(volatile uint8  *)0xFFFFB148)
#define EIC164H                (*(volatile uint8  *)0xFFFFB149)
#define EIC165                 (*(volatile uint16 *)0xFFFFB14A)
#define EIC165L                (*(volatile uint8  *)0xFFFFB14A)
#define EIC165H                (*(volatile uint8  *)0xFFFFB14B)
#define EIC166                 (*(volatile uint16 *)0xFFFFB14C)
#define EIC166L                (*(volatile uint8  *)0xFFFFB14C)
#define EIC166H                (*(volatile uint8  *)0xFFFFB14D)
#define EIC167                 (*(volatile uint16 *)0xFFFFB14E)
#define EIC167L                (*(volatile uint8  *)0xFFFFB14E)
#define EIC167H                (*(volatile uint8  *)0xFFFFB14F)
#define EIC168                 (*(volatile uint16 *)0xFFFFB150)
#define EIC168L                (*(volatile uint8  *)0xFFFFB150)
#define EIC168H                (*(volatile uint8  *)0xFFFFB151)
#define EIC169                 (*(volatile uint16 *)0xFFFFB152)
#define EIC169L                (*(volatile uint8  *)0xFFFFB152)
#define EIC169H                (*(volatile uint8  *)0xFFFFB153)
#define EIC170                 (*(volatile uint16 *)0xFFFFB154)
#define EIC170L                (*(volatile uint8  *)0xFFFFB154)
#define EIC170H                (*(volatile uint8  *)0xFFFFB155)
#define EIC171                 (*(volatile uint16 *)0xFFFFB156)
#define EIC171L                (*(volatile uint8  *)0xFFFFB156)
#define EIC171H                (*(volatile uint8  *)0xFFFFB157)
#define EIC172                 (*(volatile uint16 *)0xFFFFB158)
#define EIC172L                (*(volatile uint8  *)0xFFFFB158)
#define EIC172H                (*(volatile uint8  *)0xFFFFB159)
#define EIC173                 (*(volatile uint16 *)0xFFFFB15A)
#define EIC173L                (*(volatile uint8  *)0xFFFFB15A)
#define EIC173H                (*(volatile uint8  *)0xFFFFB15B)
#define EIC174                 (*(volatile uint16 *)0xFFFFB15C)
#define EIC174L                (*(volatile uint8  *)0xFFFFB15C)
#define EIC174H                (*(volatile uint8  *)0xFFFFB15D)
#define EIC175                 (*(volatile uint16 *)0xFFFFB15E)
#define EIC175L                (*(volatile uint8  *)0xFFFFB15E)
#define EIC175H                (*(volatile uint8  *)0xFFFFB15F)
#define EIC176                 (*(volatile uint16 *)0xFFFFB160)
#define EIC176L                (*(volatile uint8  *)0xFFFFB160)
#define EIC176H                (*(volatile uint8  *)0xFFFFB161)
#define EIC177                 (*(volatile uint16 *)0xFFFFB162)
#define EIC177L                (*(volatile uint8  *)0xFFFFB162)
#define EIC177H                (*(volatile uint8  *)0xFFFFB163)
#define EIC178                 (*(volatile uint16 *)0xFFFFB164)
#define EIC178L                (*(volatile uint8  *)0xFFFFB164)
#define EIC178H                (*(volatile uint8  *)0xFFFFB165)
#define EIC179                 (*(volatile uint16 *)0xFFFFB166)
#define EIC179L                (*(volatile uint8  *)0xFFFFB166)
#define EIC179H                (*(volatile uint8  *)0xFFFFB167)
#define EIC180                 (*(volatile uint16 *)0xFFFFB168)
#define EIC180L                (*(volatile uint8  *)0xFFFFB168)
#define EIC180H                (*(volatile uint8  *)0xFFFFB169)
#define EIC181                 (*(volatile uint16 *)0xFFFFB16A)
#define EIC181L                (*(volatile uint8  *)0xFFFFB16A)
#define EIC181H                (*(volatile uint8  *)0xFFFFB16B)
#define EIC182                 (*(volatile uint16 *)0xFFFFB16C)
#define EIC182L                (*(volatile uint8  *)0xFFFFB16C)
#define EIC182H                (*(volatile uint8  *)0xFFFFB16D)
#define EIC183                 (*(volatile uint16 *)0xFFFFB16E)
#define EIC183L                (*(volatile uint8  *)0xFFFFB16E)
#define EIC183H                (*(volatile uint8  *)0xFFFFB16F)
#define EIC184                 (*(volatile uint16 *)0xFFFFB170)
#define EIC184L                (*(volatile uint8  *)0xFFFFB170)
#define EIC184H                (*(volatile uint8  *)0xFFFFB171)
#define EIC185                 (*(volatile uint16 *)0xFFFFB172)
#define EIC185L                (*(volatile uint8  *)0xFFFFB172)
#define EIC185H                (*(volatile uint8  *)0xFFFFB173)
#define EIC186                 (*(volatile uint16 *)0xFFFFB174)
#define EIC186L                (*(volatile uint8  *)0xFFFFB174)
#define EIC186H                (*(volatile uint8  *)0xFFFFB175)
#define EIC187                 (*(volatile uint16 *)0xFFFFB176)
#define EIC187L                (*(volatile uint8  *)0xFFFFB176)
#define EIC187H                (*(volatile uint8  *)0xFFFFB177)
#define EIC188                 (*(volatile uint16 *)0xFFFFB178)
#define EIC188L                (*(volatile uint8  *)0xFFFFB178)
#define EIC188H                (*(volatile uint8  *)0xFFFFB179)
#define EIC189                 (*(volatile uint16 *)0xFFFFB17A)
#define EIC189L                (*(volatile uint8  *)0xFFFFB17A)
#define EIC189H                (*(volatile uint8  *)0xFFFFB17B)
#define EIC190                 (*(volatile uint16 *)0xFFFFB17C)
#define EIC190L                (*(volatile uint8  *)0xFFFFB17C)
#define EIC190H                (*(volatile uint8  *)0xFFFFB17D)
#define EIC191                 (*(volatile uint16 *)0xFFFFB17E)
#define EIC191L                (*(volatile uint8  *)0xFFFFB17E)
#define EIC191H                (*(volatile uint8  *)0xFFFFB17F)
#define EIC192                 (*(volatile uint16 *)0xFFFFB180)
#define EIC192L                (*(volatile uint8  *)0xFFFFB180)
#define EIC192H                (*(volatile uint8  *)0xFFFFB181)
#define EIC193                 (*(volatile uint16 *)0xFFFFB182)
#define EIC193L                (*(volatile uint8  *)0xFFFFB182)
#define EIC193H                (*(volatile uint8  *)0xFFFFB183)
#define EIC194                 (*(volatile uint16 *)0xFFFFB184)
#define EIC194L                (*(volatile uint8  *)0xFFFFB184)
#define EIC194H                (*(volatile uint8  *)0xFFFFB185)
#define EIC195                 (*(volatile uint16 *)0xFFFFB186)
#define EIC195L                (*(volatile uint8  *)0xFFFFB186)
#define EIC195H                (*(volatile uint8  *)0xFFFFB187)
#define EIC196                 (*(volatile uint16 *)0xFFFFB188)
#define EIC196L                (*(volatile uint8  *)0xFFFFB188)
#define EIC196H                (*(volatile uint8  *)0xFFFFB189)
#define EIC197                 (*(volatile uint16 *)0xFFFFB18A)
#define EIC197L                (*(volatile uint8  *)0xFFFFB18A)
#define EIC197H                (*(volatile uint8  *)0xFFFFB18B)
#define EIC198                 (*(volatile uint16 *)0xFFFFB18C)
#define EIC198L                (*(volatile uint8  *)0xFFFFB18C)
#define EIC198H                (*(volatile uint8  *)0xFFFFB18D)
#define EIC199                 (*(volatile uint16 *)0xFFFFB18E)
#define EIC199L                (*(volatile uint8  *)0xFFFFB18E)
#define EIC199H                (*(volatile uint8  *)0xFFFFB18F)
#define EIC200                 (*(volatile uint16 *)0xFFFFB190)
#define EIC200L                (*(volatile uint8  *)0xFFFFB190)
#define EIC200H                (*(volatile uint8  *)0xFFFFB191)
#define EIC201                 (*(volatile uint16 *)0xFFFFB192)
#define EIC201L                (*(volatile uint8  *)0xFFFFB192)
#define EIC201H                (*(volatile uint8  *)0xFFFFB193)
#define EIC202                 (*(volatile uint16 *)0xFFFFB194)
#define EIC202L                (*(volatile uint8  *)0xFFFFB194)
#define EIC202H                (*(volatile uint8  *)0xFFFFB195)
#define EIC203                 (*(volatile uint16 *)0xFFFFB196)
#define EIC203L                (*(volatile uint8  *)0xFFFFB196)
#define EIC203H                (*(volatile uint8  *)0xFFFFB197)
#define EIC204                 (*(volatile uint16 *)0xFFFFB198)
#define EIC204L                (*(volatile uint8  *)0xFFFFB198)
#define EIC204H                (*(volatile uint8  *)0xFFFFB199)
#define EIC205                 (*(volatile uint16 *)0xFFFFB19A)
#define EIC205L                (*(volatile uint8  *)0xFFFFB19A)
#define EIC205H                (*(volatile uint8  *)0xFFFFB19B)
#define EIC206                 (*(volatile uint16 *)0xFFFFB19C)
#define EIC206L                (*(volatile uint8  *)0xFFFFB19C)
#define EIC206H                (*(volatile uint8  *)0xFFFFB19D)
#define EIC207                 (*(volatile uint16 *)0xFFFFB19E)
#define EIC207L                (*(volatile uint8  *)0xFFFFB19E)
#define EIC207H                (*(volatile uint8  *)0xFFFFB19F)
#define EIC208                 (*(volatile uint16 *)0xFFFFB1A0)
#define EIC208L                (*(volatile uint8  *)0xFFFFB1A0)
#define EIC208H                (*(volatile uint8  *)0xFFFFB1A1)
#define EIC209                 (*(volatile uint16 *)0xFFFFB1A2)
#define EIC209L                (*(volatile uint8  *)0xFFFFB1A2)
#define EIC209H                (*(volatile uint8  *)0xFFFFB1A3)
#define EIC210                 (*(volatile uint16 *)0xFFFFB1A4)
#define EIC210L                (*(volatile uint8  *)0xFFFFB1A4)
#define EIC210H                (*(volatile uint8  *)0xFFFFB1A5)
#define EIC211                 (*(volatile uint16 *)0xFFFFB1A6)
#define EIC211L                (*(volatile uint8  *)0xFFFFB1A6)
#define EIC211H                (*(volatile uint8  *)0xFFFFB1A7)
#define EIC212                 (*(volatile uint16 *)0xFFFFB1A8)
#define EIC212L                (*(volatile uint8  *)0xFFFFB1A8)
#define EIC212H                (*(volatile uint8  *)0xFFFFB1A9)
#define EIC213                 (*(volatile uint16 *)0xFFFFB1AA)
#define EIC213L                (*(volatile uint8  *)0xFFFFB1AA)
#define EIC213H                (*(volatile uint8  *)0xFFFFB1AB)
#define EIC214                 (*(volatile uint16 *)0xFFFFB1AC)
#define EIC214L                (*(volatile uint8  *)0xFFFFB1AC)
#define EIC214H                (*(volatile uint8  *)0xFFFFB1AD)
#define EIC215                 (*(volatile uint16 *)0xFFFFB1AE)
#define EIC215L                (*(volatile uint8  *)0xFFFFB1AE)
#define EIC215H                (*(volatile uint8  *)0xFFFFB1AF)
#define EIC216                 (*(volatile uint16 *)0xFFFFB1B0)
#define EIC216L                (*(volatile uint8  *)0xFFFFB1B0)
#define EIC216H                (*(volatile uint8  *)0xFFFFB1B1)
#define EIC217                 (*(volatile uint16 *)0xFFFFB1B2)
#define EIC217L                (*(volatile uint8  *)0xFFFFB1B2)
#define EIC217H                (*(volatile uint8  *)0xFFFFB1B3)
#define EIC218                 (*(volatile uint16 *)0xFFFFB1B4)
#define EIC218L                (*(volatile uint8  *)0xFFFFB1B4)
#define EIC218H                (*(volatile uint8  *)0xFFFFB1B5)
#define EIC219                 (*(volatile uint16 *)0xFFFFB1B6)
#define EIC219L                (*(volatile uint8  *)0xFFFFB1B6)
#define EIC219H                (*(volatile uint8  *)0xFFFFB1B7)
#define EIC220                 (*(volatile uint16 *)0xFFFFB1B8)
#define EIC220L                (*(volatile uint8  *)0xFFFFB1B8)
#define EIC220H                (*(volatile uint8  *)0xFFFFB1B9)
#define EIC221                 (*(volatile uint16 *)0xFFFFB1BA)
#define EIC221L                (*(volatile uint8  *)0xFFFFB1BA)
#define EIC221H                (*(volatile uint8  *)0xFFFFB1BB)
#define EIC222                 (*(volatile uint16 *)0xFFFFB1BC)
#define EIC222L                (*(volatile uint8  *)0xFFFFB1BC)
#define EIC222H                (*(volatile uint8  *)0xFFFFB1BD)
#define EIC223                 (*(volatile uint16 *)0xFFFFB1BE)
#define EIC223L                (*(volatile uint8  *)0xFFFFB1BE)
#define EIC223H                (*(volatile uint8  *)0xFFFFB1BF)
#define EIC224                 (*(volatile uint16 *)0xFFFFB1C0)
#define EIC224L                (*(volatile uint8  *)0xFFFFB1C0)
#define EIC224H                (*(volatile uint8  *)0xFFFFB1C1)
#define EIC225                 (*(volatile uint16 *)0xFFFFB1C2)
#define EIC225L                (*(volatile uint8  *)0xFFFFB1C2)
#define EIC225H                (*(volatile uint8  *)0xFFFFB1C3)
#define EIC226                 (*(volatile uint16 *)0xFFFFB1C4)
#define EIC226L                (*(volatile uint8  *)0xFFFFB1C4)
#define EIC226H                (*(volatile uint8  *)0xFFFFB1C5)
#define EIC227                 (*(volatile uint16 *)0xFFFFB1C6)
#define EIC227L                (*(volatile uint8  *)0xFFFFB1C6)
#define EIC227H                (*(volatile uint8  *)0xFFFFB1C7)
#define EIC228                 (*(volatile uint16 *)0xFFFFB1C8)
#define EIC228L                (*(volatile uint8  *)0xFFFFB1C8)
#define EIC228H                (*(volatile uint8  *)0xFFFFB1C9)
#define EIC229                 (*(volatile uint16 *)0xFFFFB1CA)
#define EIC229L                (*(volatile uint8  *)0xFFFFB1CA)
#define EIC229H                (*(volatile uint8  *)0xFFFFB1CB)
#define EIC230                 (*(volatile uint16 *)0xFFFFB1CC)
#define EIC230L                (*(volatile uint8  *)0xFFFFB1CC)
#define EIC230H                (*(volatile uint8  *)0xFFFFB1CD)
#define EIC231                 (*(volatile uint16 *)0xFFFFB1CE)
#define EIC231L                (*(volatile uint8  *)0xFFFFB1CE)
#define EIC231H                (*(volatile uint8  *)0xFFFFB1CF)
#define EIC232                 (*(volatile uint16 *)0xFFFFB1D0)
#define EIC232L                (*(volatile uint8  *)0xFFFFB1D0)
#define EIC232H                (*(volatile uint8  *)0xFFFFB1D1)
#define EIC233                 (*(volatile uint16 *)0xFFFFB1D2)
#define EIC233L                (*(volatile uint8  *)0xFFFFB1D2)
#define EIC233H                (*(volatile uint8  *)0xFFFFB1D3)
#define EIC234                 (*(volatile uint16 *)0xFFFFB1D4)
#define EIC234L                (*(volatile uint8  *)0xFFFFB1D4)
#define EIC234H                (*(volatile uint8  *)0xFFFFB1D5)
#define EIC235                 (*(volatile uint16 *)0xFFFFB1D6)
#define EIC235L                (*(volatile uint8  *)0xFFFFB1D6)
#define EIC235H                (*(volatile uint8  *)0xFFFFB1D7)
#define EIC236                 (*(volatile uint16 *)0xFFFFB1D8)
#define EIC236L                (*(volatile uint8  *)0xFFFFB1D8)
#define EIC236H                (*(volatile uint8  *)0xFFFFB1D9)
#define EIC237                 (*(volatile uint16 *)0xFFFFB1DA)
#define EIC237L                (*(volatile uint8  *)0xFFFFB1DA)
#define EIC237H                (*(volatile uint8  *)0xFFFFB1DB)
#define EIC238                 (*(volatile uint16 *)0xFFFFB1DC)
#define EIC238L                (*(volatile uint8  *)0xFFFFB1DC)
#define EIC238H                (*(volatile uint8  *)0xFFFFB1DD)
#define EIC239                 (*(volatile uint16 *)0xFFFFB1DE)
#define EIC239L                (*(volatile uint8  *)0xFFFFB1DE)
#define EIC239H                (*(volatile uint8  *)0xFFFFB1DF)
#define EIC240                 (*(volatile uint16 *)0xFFFFB1E0)
#define EIC240L                (*(volatile uint8  *)0xFFFFB1E0)
#define EIC240H                (*(volatile uint8  *)0xFFFFB1E1)
#define EIC241                 (*(volatile uint16 *)0xFFFFB1E2)
#define EIC241L                (*(volatile uint8  *)0xFFFFB1E2)
#define EIC241H                (*(volatile uint8  *)0xFFFFB1E3)
#define EIC242                 (*(volatile uint16 *)0xFFFFB1E4)
#define EIC242L                (*(volatile uint8  *)0xFFFFB1E4)
#define EIC242H                (*(volatile uint8  *)0xFFFFB1E5)
#define EIC243                 (*(volatile uint16 *)0xFFFFB1E6)
#define EIC243L                (*(volatile uint8  *)0xFFFFB1E6)
#define EIC243H                (*(volatile uint8  *)0xFFFFB1E7)
#define EIC244                 (*(volatile uint16 *)0xFFFFB1E8)
#define EIC244L                (*(volatile uint8  *)0xFFFFB1E8)
#define EIC244H                (*(volatile uint8  *)0xFFFFB1E9)
#define EIC245                 (*(volatile uint16 *)0xFFFFB1EA)
#define EIC245L                (*(volatile uint8  *)0xFFFFB1EA)
#define EIC245H                (*(volatile uint8  *)0xFFFFB1EB)
#define IMR1                   (*(volatile uint32 *)0xFFFFB404)
#define IMR2                   (*(volatile uint32 *)0xFFFFB408)
#define IMR3                   (*(volatile uint32 *)0xFFFFB40C)
#define IMR4                   (*(volatile uint32 *)0xFFFFB410)
#define IMR5                   (*(volatile uint32 *)0xFFFFB414)
#define IMR6                   (*(volatile uint32 *)0xFFFFB418)
#define IMR7                   (*(volatile uint32 *)0xFFFFB41C)
#define EIBD32                 (*(volatile uint32 *)0xFFFFB880)
#define EIBD33                 (*(volatile uint32 *)0xFFFFB884)
#define EIBD34                 (*(volatile uint32 *)0xFFFFB888)
#define EIBD35                 (*(volatile uint32 *)0xFFFFB88C)
#define EIBD36                 (*(volatile uint32 *)0xFFFFB890)
#define EIBD37                 (*(volatile uint32 *)0xFFFFB894)
#define EIBD38                 (*(volatile uint32 *)0xFFFFB898)
#define EIBD39                 (*(volatile uint32 *)0xFFFFB89C)
#define EIBD40                 (*(volatile uint32 *)0xFFFFB8A0)
#define EIBD41                 (*(volatile uint32 *)0xFFFFB8A4)
#define EIBD42                 (*(volatile uint32 *)0xFFFFB8A8)
#define EIBD43                 (*(volatile uint32 *)0xFFFFB8AC)
#define EIBD44                 (*(volatile uint32 *)0xFFFFB8B0)
#define EIBD45                 (*(volatile uint32 *)0xFFFFB8B4)
#define EIBD46                 (*(volatile uint32 *)0xFFFFB8B8)
#define EIBD47                 (*(volatile uint32 *)0xFFFFB8BC)
#define EIBD48                 (*(volatile uint32 *)0xFFFFB8C0)
#define EIBD49                 (*(volatile uint32 *)0xFFFFB8C4)
#define EIBD50                 (*(volatile uint32 *)0xFFFFB8C8)
#define EIBD51                 (*(volatile uint32 *)0xFFFFB8CC)
#define EIBD52                 (*(volatile uint32 *)0xFFFFB8D0)
#define EIBD53                 (*(volatile uint32 *)0xFFFFB8D4)
#define EIBD54                 (*(volatile uint32 *)0xFFFFB8D8)
#define EIBD55                 (*(volatile uint32 *)0xFFFFB8DC)
#define EIBD56                 (*(volatile uint32 *)0xFFFFB8E0)
#define EIBD57                 (*(volatile uint32 *)0xFFFFB8E4)
#define EIBD58                 (*(volatile uint32 *)0xFFFFB8E8)
#define EIBD59                 (*(volatile uint32 *)0xFFFFB8EC)
#define EIBD60                 (*(volatile uint32 *)0xFFFFB8F0)
#define EIBD61                 (*(volatile uint32 *)0xFFFFB8F4)
#define EIBD62                 (*(volatile uint32 *)0xFFFFB8F8)
#define EIBD63                 (*(volatile uint32 *)0xFFFFB8FC)
#define EIBD64                 (*(volatile uint32 *)0xFFFFB900)
#define EIBD65                 (*(volatile uint32 *)0xFFFFB904)
#define EIBD66                 (*(volatile uint32 *)0xFFFFB908)
#define EIBD67                 (*(volatile uint32 *)0xFFFFB90C)
#define EIBD68                 (*(volatile uint32 *)0xFFFFB910)
#define EIBD69                 (*(volatile uint32 *)0xFFFFB914)
#define EIBD70                 (*(volatile uint32 *)0xFFFFB918)
#define EIBD71                 (*(volatile uint32 *)0xFFFFB91C)
#define EIBD72                 (*(volatile uint32 *)0xFFFFB920)
#define EIBD73                 (*(volatile uint32 *)0xFFFFB924)
#define EIBD74                 (*(volatile uint32 *)0xFFFFB928)
#define EIBD75                 (*(volatile uint32 *)0xFFFFB92C)
#define EIBD76                 (*(volatile uint32 *)0xFFFFB930)
#define EIBD77                 (*(volatile uint32 *)0xFFFFB934)
#define EIBD78                 (*(volatile uint32 *)0xFFFFB938)
#define EIBD79                 (*(volatile uint32 *)0xFFFFB93C)
#define EIBD80                 (*(volatile uint32 *)0xFFFFB940)
#define EIBD81                 (*(volatile uint32 *)0xFFFFB944)
#define EIBD82                 (*(volatile uint32 *)0xFFFFB948)
#define EIBD83                 (*(volatile uint32 *)0xFFFFB94C)
#define EIBD84                 (*(volatile uint32 *)0xFFFFB950)
#define EIBD85                 (*(volatile uint32 *)0xFFFFB954)
#define EIBD86                 (*(volatile uint32 *)0xFFFFB958)
#define EIBD87                 (*(volatile uint32 *)0xFFFFB95C)
#define EIBD88                 (*(volatile uint32 *)0xFFFFB960)
#define EIBD89                 (*(volatile uint32 *)0xFFFFB964)
#define EIBD90                 (*(volatile uint32 *)0xFFFFB968)
#define EIBD91                 (*(volatile uint32 *)0xFFFFB96C)
#define EIBD92                 (*(volatile uint32 *)0xFFFFB970)
#define EIBD93                 (*(volatile uint32 *)0xFFFFB974)
#define EIBD94                 (*(volatile uint32 *)0xFFFFB978)
#define EIBD95                 (*(volatile uint32 *)0xFFFFB97C)
#define EIBD96                 (*(volatile uint32 *)0xFFFFB980)
#define EIBD97                 (*(volatile uint32 *)0xFFFFB984)
#define EIBD98                 (*(volatile uint32 *)0xFFFFB988)
#define EIBD99                 (*(volatile uint32 *)0xFFFFB98C)
#define EIBD100                (*(volatile uint32 *)0xFFFFB990)
#define EIBD101                (*(volatile uint32 *)0xFFFFB994)
#define EIBD102                (*(volatile uint32 *)0xFFFFB998)
#define EIBD103                (*(volatile uint32 *)0xFFFFB99C)
#define EIBD104                (*(volatile uint32 *)0xFFFFB9A0)
#define EIBD105                (*(volatile uint32 *)0xFFFFB9A4)
#define EIBD106                (*(volatile uint32 *)0xFFFFB9A8)
#define EIBD107                (*(volatile uint32 *)0xFFFFB9AC)
#define EIBD108                (*(volatile uint32 *)0xFFFFB9B0)
#define EIBD109                (*(volatile uint32 *)0xFFFFB9B4)
#define EIBD110                (*(volatile uint32 *)0xFFFFB9B8)
#define EIBD111                (*(volatile uint32 *)0xFFFFB9BC)
#define EIBD112                (*(volatile uint32 *)0xFFFFB9C0)
#define EIBD113                (*(volatile uint32 *)0xFFFFB9C4)
#define EIBD114                (*(volatile uint32 *)0xFFFFB9C8)
#define EIBD115                (*(volatile uint32 *)0xFFFFB9CC)
#define EIBD116                (*(volatile uint32 *)0xFFFFB9D0)
#define EIBD117                (*(volatile uint32 *)0xFFFFB9D4)
#define EIBD118                (*(volatile uint32 *)0xFFFFB9D8)
#define EIBD119                (*(volatile uint32 *)0xFFFFB9DC)
#define EIBD120                (*(volatile uint32 *)0xFFFFB9E0)
#define EIBD121                (*(volatile uint32 *)0xFFFFB9E4)
#define EIBD122                (*(volatile uint32 *)0xFFFFB9E8)
#define EIBD123                (*(volatile uint32 *)0xFFFFB9EC)
#define EIBD124                (*(volatile uint32 *)0xFFFFB9F0)
#define EIBD125                (*(volatile uint32 *)0xFFFFB9F4)
#define EIBD126                (*(volatile uint32 *)0xFFFFB9F8)
#define EIBD127                (*(volatile uint32 *)0xFFFFB9FC)
#define EIBD128                (*(volatile uint32 *)0xFFFFBA00)
#define EIBD129                (*(volatile uint32 *)0xFFFFBA04)
#define EIBD130                (*(volatile uint32 *)0xFFFFBA08)
#define EIBD131                (*(volatile uint32 *)0xFFFFBA0C)
#define EIBD132                (*(volatile uint32 *)0xFFFFBA10)
#define EIBD133                (*(volatile uint32 *)0xFFFFBA14)
#define EIBD134                (*(volatile uint32 *)0xFFFFBA18)
#define EIBD135                (*(volatile uint32 *)0xFFFFBA1C)
#define EIBD136                (*(volatile uint32 *)0xFFFFBA20)
#define EIBD137                (*(volatile uint32 *)0xFFFFBA24)
#define EIBD138                (*(volatile uint32 *)0xFFFFBA28)
#define EIBD139                (*(volatile uint32 *)0xFFFFBA2C)
#define EIBD140                (*(volatile uint32 *)0xFFFFBA30)
#define EIBD141                (*(volatile uint32 *)0xFFFFBA34)
#define EIBD142                (*(volatile uint32 *)0xFFFFBA38)
#define EIBD143                (*(volatile uint32 *)0xFFFFBA3C)
#define EIBD144                (*(volatile uint32 *)0xFFFFBA40)
#define EIBD145                (*(volatile uint32 *)0xFFFFBA44)
#define EIBD146                (*(volatile uint32 *)0xFFFFBA48)
#define EIBD147                (*(volatile uint32 *)0xFFFFBA4C)
#define EIBD148                (*(volatile uint32 *)0xFFFFBA50)
#define EIBD149                (*(volatile uint32 *)0xFFFFBA54)
#define EIBD150                (*(volatile uint32 *)0xFFFFBA58)
#define EIBD151                (*(volatile uint32 *)0xFFFFBA5C)
#define EIBD152                (*(volatile uint32 *)0xFFFFBA60)
#define EIBD153                (*(volatile uint32 *)0xFFFFBA64)
#define EIBD154                (*(volatile uint32 *)0xFFFFBA68)
#define EIBD155                (*(volatile uint32 *)0xFFFFBA6C)
#define EIBD156                (*(volatile uint32 *)0xFFFFBA70)
#define EIBD157                (*(volatile uint32 *)0xFFFFBA74)
#define EIBD158                (*(volatile uint32 *)0xFFFFBA78)
#define EIBD159                (*(volatile uint32 *)0xFFFFBA7C)
#define EIBD160                (*(volatile uint32 *)0xFFFFBA80)
#define EIBD161                (*(volatile uint32 *)0xFFFFBA84)
#define EIBD162                (*(volatile uint32 *)0xFFFFBA88)
#define EIBD163                (*(volatile uint32 *)0xFFFFBA8C)
#define EIBD164                (*(volatile uint32 *)0xFFFFBA90)
#define EIBD165                (*(volatile uint32 *)0xFFFFBA94)
#define EIBD166                (*(volatile uint32 *)0xFFFFBA98)
#define EIBD167                (*(volatile uint32 *)0xFFFFBA9C)
#define EIBD168                (*(volatile uint32 *)0xFFFFBAA0)
#define EIBD169                (*(volatile uint32 *)0xFFFFBAA4)
#define EIBD170                (*(volatile uint32 *)0xFFFFBAA8)
#define EIBD171                (*(volatile uint32 *)0xFFFFBAAC)
#define EIBD172                (*(volatile uint32 *)0xFFFFBAB0)
#define EIBD173                (*(volatile uint32 *)0xFFFFBAB4)
#define EIBD174                (*(volatile uint32 *)0xFFFFBAB8)
#define EIBD175                (*(volatile uint32 *)0xFFFFBABC)
#define EIBD176                (*(volatile uint32 *)0xFFFFBAC0)
#define EIBD177                (*(volatile uint32 *)0xFFFFBAC4)
#define EIBD178                (*(volatile uint32 *)0xFFFFBAC8)
#define EIBD179                (*(volatile uint32 *)0xFFFFBACC)
#define EIBD180                (*(volatile uint32 *)0xFFFFBAD0)
#define EIBD181                (*(volatile uint32 *)0xFFFFBAD4)
#define EIBD182                (*(volatile uint32 *)0xFFFFBAD8)
#define EIBD183                (*(volatile uint32 *)0xFFFFBADC)
#define EIBD184                (*(volatile uint32 *)0xFFFFBAE0)
#define EIBD185                (*(volatile uint32 *)0xFFFFBAE4)
#define EIBD186                (*(volatile uint32 *)0xFFFFBAE8)
#define EIBD187                (*(volatile uint32 *)0xFFFFBAEC)
#define EIBD188                (*(volatile uint32 *)0xFFFFBAF0)
#define EIBD189                (*(volatile uint32 *)0xFFFFBAF4)
#define EIBD190                (*(volatile uint32 *)0xFFFFBAF8)
#define EIBD191                (*(volatile uint32 *)0xFFFFBAFC)
#define EIBD192                (*(volatile uint32 *)0xFFFFBB00)
#define EIBD193                (*(volatile uint32 *)0xFFFFBB04)
#define EIBD194                (*(volatile uint32 *)0xFFFFBB08)
#define EIBD195                (*(volatile uint32 *)0xFFFFBB0C)
#define EIBD196                (*(volatile uint32 *)0xFFFFBB10)
#define EIBD197                (*(volatile uint32 *)0xFFFFBB14)
#define EIBD198                (*(volatile uint32 *)0xFFFFBB18)
#define EIBD199                (*(volatile uint32 *)0xFFFFBB1C)
#define EIBD200                (*(volatile uint32 *)0xFFFFBB20)
#define EIBD201                (*(volatile uint32 *)0xFFFFBB24)
#define EIBD202                (*(volatile uint32 *)0xFFFFBB28)
#define EIBD203                (*(volatile uint32 *)0xFFFFBB2C)
#define EIBD204                (*(volatile uint32 *)0xFFFFBB30)
#define EIBD205                (*(volatile uint32 *)0xFFFFBB34)
#define EIBD206                (*(volatile uint32 *)0xFFFFBB38)
#define EIBD207                (*(volatile uint32 *)0xFFFFBB3C)
#define EIBD208                (*(volatile uint32 *)0xFFFFBB40)
#define EIBD209                (*(volatile uint32 *)0xFFFFBB44)
#define EIBD210                (*(volatile uint32 *)0xFFFFBB48)
#define EIBD211                (*(volatile uint32 *)0xFFFFBB4C)
#define EIBD212                (*(volatile uint32 *)0xFFFFBB50)
#define EIBD213                (*(volatile uint32 *)0xFFFFBB54)
#define EIBD214                (*(volatile uint32 *)0xFFFFBB58)
#define EIBD215                (*(volatile uint32 *)0xFFFFBB5C)
#define EIBD216                (*(volatile uint32 *)0xFFFFBB60)
#define EIBD217                (*(volatile uint32 *)0xFFFFBB64)
#define EIBD218                (*(volatile uint32 *)0xFFFFBB68)
#define EIBD219                (*(volatile uint32 *)0xFFFFBB6C)
#define EIBD220                (*(volatile uint32 *)0xFFFFBB70)
#define EIBD221                (*(volatile uint32 *)0xFFFFBB74)
#define EIBD222                (*(volatile uint32 *)0xFFFFBB78)
#define EIBD223                (*(volatile uint32 *)0xFFFFBB7C)
#define EIBD224                (*(volatile uint32 *)0xFFFFBB80)
#define EIBD225                (*(volatile uint32 *)0xFFFFBB84)
#define EIBD226                (*(volatile uint32 *)0xFFFFBB88)
#define EIBD227                (*(volatile uint32 *)0xFFFFBB8C)
#define EIBD228                (*(volatile uint32 *)0xFFFFBB90)
#define EIBD229                (*(volatile uint32 *)0xFFFFBB94)
#define EIBD230                (*(volatile uint32 *)0xFFFFBB98)
#define EIBD231                (*(volatile uint32 *)0xFFFFBB9C)
#define EIBD232                (*(volatile uint32 *)0xFFFFBBA0)
#define EIBD233                (*(volatile uint32 *)0xFFFFBBA4)
#define EIBD234                (*(volatile uint32 *)0xFFFFBBA8)
#define EIBD235                (*(volatile uint32 *)0xFFFFBBAC)
#define EIBD236                (*(volatile uint32 *)0xFFFFBBB0)
#define EIBD237                (*(volatile uint32 *)0xFFFFBBB4)
#define EIBD238                (*(volatile uint32 *)0xFFFFBBB8)
#define EIBD239                (*(volatile uint32 *)0xFFFFBBBC)
#define EIBD240                (*(volatile uint32 *)0xFFFFBBC0)
#define EIBD241                (*(volatile uint32 *)0xFFFFBBC4)
#define EIBD242                (*(volatile uint32 *)0xFFFFBBC8)
#define EIBD243                (*(volatile uint32 *)0xFFFFBBCC)
#define EIBD244                (*(volatile uint32 *)0xFFFFBBD0)
#define EIBD245                (*(volatile uint32 *)0xFFFFBBD4)

#define FLMD        (*(volatile R_FLMD      *)0xFFA00000) /* FLMD */
#define FACI0       (*(volatile R_FACI0     *)0xFFA10000) /* FACI0 */
#define DNFA2       (*(volatile R_DNFA2     *)0xFFC30200) /* DNFA2 */
#define DNFA3       (*(volatile R_DNFA3     *)0xFFC30300) /* DNFA3 */
#define DNFA5       (*(volatile R_DNFA5     *)0xFFC30500) /* DNFA5 */
#define DNFA7       (*(volatile R_DNFA7     *)0xFFC30700) /* DNFA7 */
#define FCLA0       (*(volatile R_FCLA0     *)0xFFC34000) /* FCLA0 */
#define FCLA1       (*(volatile R_FCLA1     *)0xFFC34100) /* FCLA1 */
#define FCLA2       (*(volatile R_FCLA2     *)0xFFC34200) /* FCLA2 */
#define FCLA3       (*(volatile R_FCLA3     *)0xFFC34300) /* FCLA3 */
#define FCLA5       (*(volatile R_FCLA5     *)0xFFC34500) /* FCLA5 */
#define FSGD5A      (*(volatile R_FSGD5A    *)0xFFC5A000) /* FSGD5A */
#define ERRSLV5A    (*(volatile R_ERRSLV5A  *)0xFFC5A100) /* ERRSLV5A */
#define ERRSLV5AI   (*(volatile R_ERRSLV5AI *)0xFFC5A800) /* ERRSLV5AI */
#define ECCCSIH0    (*(volatile R_ECCCSIH0  *)0xFFC70000) /* ECCCSIH0 */
#define ECCCSIH2    (*(volatile R_ECCCSIH2  *)0xFFC70100) /* ECCCSIH2 */
#define ECCTTCAN0   (*(volatile R_ECCTTCAN0 *)0xFFC71000) /* ECCTTCAN0 */
#define ECCCSIH1    (*(volatile R_ECCCSIH1  *)0xFFC78000) /* ECCCSIH1 */
#define ECCMCAN0    (*(volatile R_ECCMCAN0  *)0xFFC79000) /* ECCMCAN0 */
#define CSIH1       (*(volatile R_CSIH1     *)0xFFCA0000) /* CSIH1 */
#define PMMA1       (*(volatile R_PMMA1     *)0xFFCA2000) /* PMMA1 */
#define RLN31       (*(volatile R_RLN31     *)0xFFCAC000) /* RLN31 */
#define RSENT0      (*(volatile R_RSENT0    *)0xFFCDC000) /* RSENT0 */
#define RSENT1      (*(volatile R_RSENT1    *)0xFFCDC100) /* RSENT1 */
#define RSENT2      (*(volatile R_RSENT2    *)0xFFCDC200) /* RSENT2 */
#define RSENT3      (*(volatile R_RSENT3    *)0xFFCDC300) /* RSENT3 */
#define SINT        (*(volatile R_SINT      *)0xFFCDE000) /* SINT */
#define MTTCAN0     (*(volatile R_MTTCAN0   *)0xFFD30000) /* MTTCAN0 */
#define DCRB0       (*(volatile R_DCRB0     *)0xFFD50000) /* DCRB0 */
#define ECMM0       (*(volatile R_ECMM0     *)0xFFD60000) /* ECMM0 */
#define ECMC0       (*(volatile R_ECMC0     *)0xFFD61000) /* ECMC0 */
#define ECM0        (*(volatile R_ECM0      *)0xFFD62000) /* ECM0 */
#define PIC2C       (*(volatile R_PIC2C     *)0xFFD68000) /* PIC2C */
#define CSIH0       (*(volatile R_CSIH0     *)0xFFD80000) /* CSIH0 */
#define PMMA0       (*(volatile R_PMMA0     *)0xFFD82000) /* PMMA0 */
#define CSIH2       (*(volatile R_CSIH2     *)0xFFD83000) /* CSIH2 */
#define PMMA2       (*(volatile R_PMMA2     *)0xFFD85000) /* PMMA2 */
#define RLN30       (*(volatile R_RLN30     *)0xFFD8C000) /* RLN30 */
#define STM0        (*(volatile R_STM0      *)0xFFDD8000) /* STM0 */
#define FSGD2A      (*(volatile R_FSGD2A    *)0xFFDDD000) /* FSGD2A */
#define ERRSLV2     (*(volatile R_ERRSLV2   *)0xFFDDD100) /* ERRSLV2 */
#define ERRSLV2AI   (*(volatile R_ERRSLV2AI *)0xFFDDD800) /* ERRSLV2AI */
#define GTM0        (*(volatile R_GTM0      *)0xFFE00000) /* GTM0 */
#define ECCGTM0     (*(volatile R_ECCGTM0   *)0xFFE80000) /* ECCGTM0 */
#define ECCGTM1     (*(volatile R_ECCGTM1   *)0xFFE80100) /* ECCGTM1 */
#define WDTA0       (*(volatile R_WDTA0     *)0xFFED0000) /* WDTA0 */
#define SWD0        (*(volatile R_SWD0      *)0xFFED8000) /* SWD0 */
#define FSGD1A      (*(volatile R_FSGD1A    *)0xFFEE0000) /* FSGD1A */
#define ERRSLV1     (*(volatile R_ERRSLV1   *)0xFFEE0100) /* ERRSLV1 */
#define FSGD1B      (*(volatile R_FSGD1B    *)0xFFEE0200) /* FSGD1B */
#define ERRSLV1AI   (*(volatile R_ERRSLV1AI *)0xFFEE0800) /* ERRSLV1AI */
#define MCAN0       (*(volatile R_MCAN0     *)0xFFEF0000) /* MCAN0 */
#define DCRB1       (*(volatile R_DCRB1     *)0xFFF70000) /* DCRB1 */
#define CLMA0       (*(volatile R_CLMA0     *)0xFFF83100) /* CLMA0 */
#define CLMA1       (*(volatile R_CLMA1     *)0xFFF83200) /* CLMA1 */
#define CLMA2       (*(volatile R_CLMA2     *)0xFFF83300) /* CLMA2 */
#define CLMA3       (*(volatile R_CLMA3     *)0xFFF83400) /* CLMA3 */
#define FSGD4A      (*(volatile R_FSGD4A    *)0xFFF90000) /* FSGD4A */
#define ERRSLV4     (*(volatile R_ERRSLV4   *)0xFFF90100) /* ERRSLV4 */
#define FSGD4B      (*(volatile R_FSGD4B    *)0xFFF90200) /* FSGD4B */
#define ERRSLV4AI   (*(volatile R_ERRSLV4AI *)0xFFF90800) /* ERRSLV4AI */
#define ADCF0       (*(volatile R_ADCF0     *)0xFFF91000) /* ADCF0 */
#define OTS0        (*(volatile R_OTS0      *)0xFFF93000) /* OTS0 */
#define FSGD3A      (*(volatile R_FSGD3A    *)0xFFF94000) /* FSGD3A */
#define ERRSLV3     (*(volatile R_ERRSLV3   *)0xFFF94100) /* ERRSLV3 */
#define FSGD3B      (*(volatile R_FSGD3B    *)0xFFF94200) /* FSGD3B */
#define ERRSLV3AI   (*(volatile R_ERRSLV3AI *)0xFFF94800) /* ERRSLV3AI */
#define ERRSLVHI    (*(volatile R_ERRSLVHI  *)0xFFFA0130) /* ERRSLVHI */
#define IPG         (*(volatile R_IPG       *)0xFFFEE000) /* IPG */
#define PEG         (*(volatile R_PEG       *)0xFFFEE680) /* PEG */
#define SEG         (*(volatile R_SEG       *)0xFFFEE980) /* SEG */

#define RSENT       ((volatile R_RSENT0 *)0xFFCDC000) /* RSENT[4] */
#define ECCGTM      ((volatile R_ECCGTM0 *)0xFFE80000) /* ECCGTM[2] */
#define CLMA        ((volatile R_CLMA0 *)0xFFF83100) /* CLMA[4] */

#define FLMDCNT FLMD.CNT
#define FLMDPCMD FLMD.PCMD
#define FLMDPS FLMD.PS
#define FACI0FPMON FACI0.FPMON
#define FACI0FASTAT FACI0.FASTAT
#define FACI0FAEINT FACI0.FAEINT
#define FACI0FSADDR FACI0.FSADDR
#define FACI0FEADDR FACI0.FEADDR
#define FACI0FCURAME FACI0.FCURAME
#define FACI0FRAMMCR FACI0.FRAMMCR
#define FACI0FPROTDR0 FACI0.FPROTDR0
#define FACI0FPROTCR0 FACI0.FPROTCR0
#define FACI0FPROTCR1 FACI0.FPROTCR1
#define FACI0FSTATR FACI0.FSTATR
#define FACI0FENTRYR FACI0.FENTRYR
#define FACI0FSUINITR FACI0.FSUINITR
#define FACI0FLKSTAT FACI0.FLKSTAT
#define FACI0FRFSTEADR FACI0.FRFSTEADR
#define FACI0FRTSTAT FACI0.FRTSTAT
#define FACI0FRTEINT FACI0.FRTEINT
#define FACI0FCMDR FACI0.FCMDR
#define FACI0FRAMECCR FACI0.FRAMECCR
#define FACI0FPESTAT FACI0.FPESTAT
#define FACI0FCNFPRGCNT FACI0.FCNFPRGCNT
#define FACI0FBCCNT FACI0.FBCCNT
#define FACI0FBCSTAT FACI0.FBCSTAT
#define FACI0FPSADDR FACI0.FPSADDR
#define FACI0FCPSR FACI0.FCPSR
#define FACI0FPCKAR FACI0.FPCKAR
#define FACI0FECCEMON FACI0.FECCEMON
#define FACI0FECCTMD FACI0.FECCTMD
#define FACI0FDMYECC FACI0.FDMYECC
#define DNFA2CTL DNFA2.CTL.ui8
#define DNFA2EN DNFA2.EN
#define DNFA2ENL DNFA2.ENL.ui8
#define DNFA3CTL DNFA3.CTL.ui8
#define DNFA3EN DNFA3.EN
#define DNFA3ENL DNFA3.ENL.ui8
#define DNFA5CTL DNFA5.CTL.ui8
#define DNFA5EN DNFA5.EN
#define DNFA5ENL DNFA5.ENL.ui8
#define DNFA7CTL DNFA7.CTL.ui8
#define DNFA7EN DNFA7.EN
#define DNFA7ENL DNFA7.ENL.ui8
#define FCLA0CTL0 FCLA0.CTL0.ui8
#define FCLA0CTL1 FCLA0.CTL1.ui8
#define FCLA0CTL2 FCLA0.CTL2.ui8
#define FCLA0CTL3 FCLA0.CTL3.ui8
#define FCLA0CTL4 FCLA0.CTL4.ui8
#define FCLA0CTL5 FCLA0.CTL5.ui8
#define FCLA0CTL6 FCLA0.CTL6.ui8
#define FCLA0CTL7 FCLA0.CTL7.ui8
#define FCLA1CTL0 FCLA1.CTL0.ui8
#define FCLA2CTL0 FCLA2.CTL0.ui8
#define FCLA2CTL1 FCLA2.CTL1.ui8
#define FCLA3CTL0 FCLA3.CTL0.ui8
#define FCLA3CTL1 FCLA3.CTL1.ui8
#define FCLA5CTL0 FCLA5.CTL0.ui8
#define FCLA5CTL1 FCLA5.CTL1.ui8
#define FCLA5CTL2 FCLA5.CTL2.ui8
#define FCLA5CTL3 FCLA5.CTL3.ui8
#define FSGD5APROT00 FSGD5A.PROT00.ui32
#define FSGD5APROT00L FSGD5A.PROT00.ui16[0]
#define FSGD5APROT00LL FSGD5A.PROT00.ui8[0]
#define FSGD5APROT00LH FSGD5A.PROT00.ui8[1]
#define FSGD5APROT00H FSGD5A.PROT00.ui16[1]
#define FSGD5APROT00HL FSGD5A.PROT00.ui8[2]
#define FSGD5APROT00HH FSGD5A.PROT00.ui8[3]
#define FSGD5ASPID00 FSGD5A.SPID00.ui32
#define FSGD5ASPID00L FSGD5A.SPID00.ui16[0]
#define FSGD5ASPID00LL FSGD5A.SPID00.ui8[0]
#define FSGD5ASPID00LH FSGD5A.SPID00.ui8[1]
#define FSGD5ASPID00H FSGD5A.SPID00.ui16[1]
#define FSGD5ASPID00HL FSGD5A.SPID00.ui8[2]
#define FSGD5ASPID00HH FSGD5A.SPID00.ui8[3]
#define FSGD5APROT01 FSGD5A.PROT01.ui32
#define FSGD5APROT01L FSGD5A.PROT01.ui16[0]
#define FSGD5APROT01LL FSGD5A.PROT01.ui8[0]
#define FSGD5APROT01LH FSGD5A.PROT01.ui8[1]
#define FSGD5APROT01H FSGD5A.PROT01.ui16[1]
#define FSGD5APROT01HL FSGD5A.PROT01.ui8[2]
#define FSGD5APROT01HH FSGD5A.PROT01.ui8[3]
#define FSGD5ASPID01 FSGD5A.SPID01.ui32
#define FSGD5ASPID01L FSGD5A.SPID01.ui16[0]
#define FSGD5ASPID01LL FSGD5A.SPID01.ui8[0]
#define FSGD5ASPID01LH FSGD5A.SPID01.ui8[1]
#define FSGD5ASPID01H FSGD5A.SPID01.ui16[1]
#define FSGD5ASPID01HL FSGD5A.SPID01.ui8[2]
#define FSGD5ASPID01HH FSGD5A.SPID01.ui8[3]
#define FSGD5APROT04 FSGD5A.PROT04.ui32
#define FSGD5APROT04L FSGD5A.PROT04.ui16[0]
#define FSGD5APROT04LL FSGD5A.PROT04.ui8[0]
#define FSGD5APROT04LH FSGD5A.PROT04.ui8[1]
#define FSGD5APROT04H FSGD5A.PROT04.ui16[1]
#define FSGD5APROT04HL FSGD5A.PROT04.ui8[2]
#define FSGD5APROT04HH FSGD5A.PROT04.ui8[3]
#define FSGD5ASPID04 FSGD5A.SPID04.ui32
#define FSGD5ASPID04L FSGD5A.SPID04.ui16[0]
#define FSGD5ASPID04LL FSGD5A.SPID04.ui8[0]
#define FSGD5ASPID04LH FSGD5A.SPID04.ui8[1]
#define FSGD5ASPID04H FSGD5A.SPID04.ui16[1]
#define FSGD5ASPID04HL FSGD5A.SPID04.ui8[2]
#define FSGD5ASPID04HH FSGD5A.SPID04.ui8[3]
#define FSGD5APROT05 FSGD5A.PROT05.ui32
#define FSGD5APROT05L FSGD5A.PROT05.ui16[0]
#define FSGD5APROT05LL FSGD5A.PROT05.ui8[0]
#define FSGD5APROT05LH FSGD5A.PROT05.ui8[1]
#define FSGD5APROT05H FSGD5A.PROT05.ui16[1]
#define FSGD5APROT05HL FSGD5A.PROT05.ui8[2]
#define FSGD5APROT05HH FSGD5A.PROT05.ui8[3]
#define FSGD5ASPID05 FSGD5A.SPID05.ui32
#define FSGD5ASPID05L FSGD5A.SPID05.ui16[0]
#define FSGD5ASPID05LL FSGD5A.SPID05.ui8[0]
#define FSGD5ASPID05LH FSGD5A.SPID05.ui8[1]
#define FSGD5ASPID05H FSGD5A.SPID05.ui16[1]
#define FSGD5ASPID05HL FSGD5A.SPID05.ui8[2]
#define FSGD5ASPID05HH FSGD5A.SPID05.ui8[3]
#define ERRSLV5ACTL ERRSLV5A.CTL
#define ERRSLV5ASTAT ERRSLV5A.STAT
#define ERRSLV5ATYPE ERRSLV5A.TYPE
#define ERRSLV5AICTL ERRSLV5AI.CTL
#define ERRSLV5AISTAT ERRSLV5AI.STAT
#define ERRSLV5AITYPE ERRSLV5AI.TYPE
#define ECCCSIH0CTL ECCCSIH0.CTL
#define ECCCSIH0TMC ECCCSIH0.TMC
#define ECCCSIH0TRC ECCCSIH0.TRC
#define ECCCSIH0TED ECCCSIH0.TED
#define ECCCSIH0EAD0 ECCCSIH0.EAD0
#define ECCCSIH2CTL ECCCSIH2.CTL
#define ECCCSIH2TMC ECCCSIH2.TMC
#define ECCCSIH2TRC ECCCSIH2.TRC
#define ECCCSIH2TED ECCCSIH2.TED
#define ECCCSIH2EAD0 ECCCSIH2.EAD0
#define ECCTTCAN0CTL ECCTTCAN0.CTL
#define ECCTTCAN0TMC ECCTTCAN0.TMC
#define ECCTTCAN0TRC ECCTTCAN0.TRC
#define ECCTTCAN0TED ECCTTCAN0.TED
#define ECCTTCAN0EAD0 ECCTTCAN0.EAD0
#define ECCCSIH1CTL ECCCSIH1.CTL
#define ECCCSIH1TMC ECCCSIH1.TMC
#define ECCCSIH1TRC ECCCSIH1.TRC
#define ECCCSIH1TED ECCCSIH1.TED
#define ECCCSIH1EAD0 ECCCSIH1.EAD0
#define ECCMCAN0CTL ECCMCAN0.CTL
#define ECCMCAN0TMC ECCMCAN0.TMC
#define ECCMCAN0TRC ECCMCAN0.TRC
#define ECCMCAN0TED ECCMCAN0.TED
#define ECCMCAN0EAD0 ECCMCAN0.EAD0
#define CSIH1CTL0 CSIH1.CTL0.ui8
#define CSIH1CTL1 CSIH1.CTL1
#define CSIH1CTL2 CSIH1.CTL2
#define CSIH1MCTL1 CSIH1.MCTL1
#define CSIH1MCTL2 CSIH1.MCTL2
#define CSIH1TX0W CSIH1.TX0W
#define CSIH1TX0H CSIH1.TX0H
#define CSIH1RX0W CSIH1.RX0W
#define CSIH1RX0H CSIH1.RX0H
#define CSIH1MRWP0 CSIH1.MRWP0
#define CSIH1STR0 CSIH1.STR0
#define CSIH1STCR0 CSIH1.STCR0
#define CSIH1MCTL0 CSIH1.MCTL0
#define CSIH1CFG0 CSIH1.CFG0
#define CSIH1CFG1 CSIH1.CFG1
#define CSIH1CFG2 CSIH1.CFG2
#define CSIH1CFG3 CSIH1.CFG3
#define CSIH1CFG4 CSIH1.CFG4
#define CSIH1CFG5 CSIH1.CFG5
#define CSIH1CFG6 CSIH1.CFG6
#define CSIH1CFG7 CSIH1.CFG7
#define CSIH1BRS0 CSIH1.BRS0
#define CSIH1BRS1 CSIH1.BRS1
#define CSIH1BRS2 CSIH1.BRS2
#define CSIH1BRS3 CSIH1.BRS3
#define PMMA1CTL PMMA1.CTL
#define PMMA1TCTL0 PMMA1.TCTL0
#define PMMA1TCTL1 PMMA1.TCTL1
#define PMMA1TCTL2 PMMA1.TCTL2
#define PMMA1TCTL3 PMMA1.TCTL3
#define PMMA1TCTL4 PMMA1.TCTL4
#define PMMA1TCTL5 PMMA1.TCTL5
#define PMMA1TCTL6 PMMA1.TCTL6
#define PMMA1TCTL7 PMMA1.TCTL7
#define PMMA1TTX0 PMMA1.TTX0
#define PMMA1TTX1 PMMA1.TTX1
#define PMMA1TTX2 PMMA1.TTX2
#define PMMA1TTX3 PMMA1.TTX3
#define PMMA1TTX4 PMMA1.TTX4
#define PMMA1TTX5 PMMA1.TTX5
#define PMMA1TTX6 PMMA1.TTX6
#define PMMA1TTX7 PMMA1.TTX7
#define PMMA1RX PMMA1.RX
#define PMMA1TCNT0 PMMA1.TCNT0
#define PMMA1TCNT1 PMMA1.TCNT1
#define PMMA1TCNT2 PMMA1.TCNT2
#define PMMA1TCNT3 PMMA1.TCNT3
#define PMMA1TCNT4 PMMA1.TCNT4
#define PMMA1TCNT5 PMMA1.TCNT5
#define PMMA1TCNT6 PMMA1.TCNT6
#define PMMA1TCNT7 PMMA1.TCNT7
#define PMMA1STR0 PMMA1.STR0
#define PMMA1STR1 PMMA1.STR1
#define PMMA1STC PMMA1.STC
#define RLN31LWBR RLN31.LWBR
#define RLN31LBRP01 RLN31.LBRP01.ui16
#define RLN31LBRP0 RLN31.LBRP01.ui8[0]
#define RLN31LBRP1 RLN31.LBRP01.ui8[1]
#define RLN31LSTC RLN31.LSTC
#define RLN31LMD RLN31.LMD
#define RLN31LBFC RLN31.LBFC
#define RLN31LSC RLN31.LSC
#define RLN31LWUP RLN31.LWUP
#define RLN31LIE RLN31.LIE
#define RLN31LEDE RLN31.LEDE
#define RLN31LCUC RLN31.LCUC
#define RLN31LTRC RLN31.LTRC
#define RLN31LMST RLN31.LMST
#define RLN31LST RLN31.LST
#define RLN31LEST RLN31.LEST
#define RLN31LDFC RLN31.LDFC
#define RLN31LIDB RLN31.LIDB
#define RLN31LCBR RLN31.LCBR
#define RLN31LUDB0 RLN31.LUDB0
#define RLN31LDBR1 RLN31.LDBR1
#define RLN31LDBR2 RLN31.LDBR2
#define RLN31LDBR3 RLN31.LDBR3
#define RLN31LDBR4 RLN31.LDBR4
#define RLN31LDBR5 RLN31.LDBR5
#define RLN31LDBR6 RLN31.LDBR6
#define RLN31LDBR7 RLN31.LDBR7
#define RLN31LDBR8 RLN31.LDBR8
#define RLN31LUOER RLN31.LUOER
#define RLN31LUOR1 RLN31.LUOR1
#define RLN31LUTDR RLN31.LUTDR.ui16
#define RLN31LUTDRL RLN31.LUTDR.ui8[0]
#define RLN31LUTDRH RLN31.LUTDR.ui8[1]
#define RLN31LURDR RLN31.LURDR.ui16
#define RLN31LURDRL RLN31.LURDR.ui8[0]
#define RLN31LURDRH RLN31.LURDR.ui8[1]
#define RLN31LUWTDR RLN31.LUWTDR.ui16
#define RLN31LUWTDRL RLN31.LUWTDR.ui8[0]
#define RLN31LUWTDRH RLN31.LUWTDR.ui8[1]
#define RSENT0TSPC RSENT0.TSPC.ui32
#define RSENT0TSPCL RSENT0.TSPC.ui16[0]
#define RSENT0TSPCLL RSENT0.TSPC.ui8[0]
#define RSENT0TSPCLH RSENT0.TSPC.ui8[1]
#define RSENT0TSPCH RSENT0.TSPC.ui16[1]
#define RSENT0TSPCHL RSENT0.TSPC.ui8[2]
#define RSENT0TSC RSENT0.TSC.ui32
#define RSENT0TSCL RSENT0.TSC.ui16[0]
#define RSENT0TSCLL RSENT0.TSC.ui8[0]
#define RSENT0TSCLH RSENT0.TSC.ui8[1]
#define RSENT0TSCH RSENT0.TSC.ui16[1]
#define RSENT0TSCHL RSENT0.TSC.ui8[2]
#define RSENT0TSCHH RSENT0.TSC.ui8[3]
#define RSENT0CC RSENT0.CC.ui32
#define RSENT0CCL RSENT0.CC.ui16[0]
#define RSENT0CCLL RSENT0.CC.ui8[0]
#define RSENT0CCLH RSENT0.CC.ui8[1]
#define RSENT0BRP RSENT0.BRP.ui32
#define RSENT0BRPL RSENT0.BRP.ui16[0]
#define RSENT0BRPLL RSENT0.BRP.ui8[0]
#define RSENT0BRPLH RSENT0.BRP.ui8[1]
#define RSENT0BRPH RSENT0.BRP.ui16[1]
#define RSENT0BRPHL RSENT0.BRP.ui8[2]
#define RSENT0BRPHH RSENT0.BRP.ui8[3]
#define RSENT0IDE RSENT0.IDE.ui32
#define RSENT0IDEL RSENT0.IDE.ui16[0]
#define RSENT0IDELL RSENT0.IDE.ui8[0]
#define RSENT0IDELH RSENT0.IDE.ui8[1]
#define RSENT0MDC RSENT0.MDC.ui32
#define RSENT0MDCL RSENT0.MDC.ui16[0]
#define RSENT0MDCLL RSENT0.MDC.ui8[0]
#define RSENT0SPCT RSENT0.SPCT.ui32
#define RSENT0SPCTL RSENT0.SPCT.ui16[0]
#define RSENT0SPCTLL RSENT0.SPCT.ui8[0]
#define RSENT0MST RSENT0.MST.ui32
#define RSENT0MSTL RSENT0.MST.ui16[0]
#define RSENT0MSTLL RSENT0.MST.ui8[0]
#define RSENT0CS RSENT0.CS.ui32
#define RSENT0CSL RSENT0.CS.ui16[0]
#define RSENT0CSLL RSENT0.CS.ui8[0]
#define RSENT0CSLH RSENT0.CS.ui8[1]
#define RSENT0CSC RSENT0.CSC.ui32
#define RSENT0CSCL RSENT0.CSC.ui16[0]
#define RSENT0CSCLL RSENT0.CSC.ui8[0]
#define RSENT0CSCLH RSENT0.CSC.ui8[1]
#define RSENT0SRTS RSENT0.SRTS.ui32
#define RSENT0SRTSL RSENT0.SRTS.ui16[0]
#define RSENT0SRTSLL RSENT0.SRTS.ui8[0]
#define RSENT0SRTSLH RSENT0.SRTS.ui8[1]
#define RSENT0SRTSH RSENT0.SRTS.ui16[1]
#define RSENT0SRTSHL RSENT0.SRTS.ui8[2]
#define RSENT0SRTSHH RSENT0.SRTS.ui8[3]
#define RSENT0SRXD RSENT0.SRXD
#define RSENT0CPL RSENT0.CPL.ui32
#define RSENT0CPLL RSENT0.CPL.ui16[0]
#define RSENT0CPLLL RSENT0.CPL.ui8[0]
#define RSENT0CPLLH RSENT0.CPL.ui8[1]
#define RSENT0CPLH RSENT0.CPL.ui16[1]
#define RSENT0CPLHL RSENT0.CPL.ui8[2]
#define RSENT0ML RSENT0.ML.ui32
#define RSENT0MLL RSENT0.ML.ui16[0]
#define RSENT0MLLL RSENT0.ML.ui8[0]
#define RSENT0MLLH RSENT0.ML.ui8[1]
#define RSENT0MLH RSENT0.ML.ui16[1]
#define RSENT0MLHL RSENT0.ML.ui8[2]
#define RSENT0FRTS RSENT0.FRTS.ui32
#define RSENT0FRTSL RSENT0.FRTS.ui16[0]
#define RSENT0FRTSLL RSENT0.FRTS.ui8[0]
#define RSENT0FRTSLH RSENT0.FRTS.ui8[1]
#define RSENT0FRTSH RSENT0.FRTS.ui16[1]
#define RSENT0FRTSHL RSENT0.FRTS.ui8[2]
#define RSENT0FRTSHH RSENT0.FRTS.ui8[3]
#define RSENT0FRXD RSENT0.FRXD
#define RSENT1TSPC RSENT1.TSPC.ui32
#define RSENT1TSPCL RSENT1.TSPC.ui16[0]
#define RSENT1TSPCLL RSENT1.TSPC.ui8[0]
#define RSENT1TSPCLH RSENT1.TSPC.ui8[1]
#define RSENT1TSPCH RSENT1.TSPC.ui16[1]
#define RSENT1TSPCHL RSENT1.TSPC.ui8[2]
#define RSENT1TSC RSENT1.TSC.ui32
#define RSENT1TSCL RSENT1.TSC.ui16[0]
#define RSENT1TSCLL RSENT1.TSC.ui8[0]
#define RSENT1TSCLH RSENT1.TSC.ui8[1]
#define RSENT1TSCH RSENT1.TSC.ui16[1]
#define RSENT1TSCHL RSENT1.TSC.ui8[2]
#define RSENT1TSCHH RSENT1.TSC.ui8[3]
#define RSENT1CC RSENT1.CC.ui32
#define RSENT1CCL RSENT1.CC.ui16[0]
#define RSENT1CCLL RSENT1.CC.ui8[0]
#define RSENT1CCLH RSENT1.CC.ui8[1]
#define RSENT1BRP RSENT1.BRP.ui32
#define RSENT1BRPL RSENT1.BRP.ui16[0]
#define RSENT1BRPLL RSENT1.BRP.ui8[0]
#define RSENT1BRPLH RSENT1.BRP.ui8[1]
#define RSENT1BRPH RSENT1.BRP.ui16[1]
#define RSENT1BRPHL RSENT1.BRP.ui8[2]
#define RSENT1BRPHH RSENT1.BRP.ui8[3]
#define RSENT1IDE RSENT1.IDE.ui32
#define RSENT1IDEL RSENT1.IDE.ui16[0]
#define RSENT1IDELL RSENT1.IDE.ui8[0]
#define RSENT1IDELH RSENT1.IDE.ui8[1]
#define RSENT1MDC RSENT1.MDC.ui32
#define RSENT1MDCL RSENT1.MDC.ui16[0]
#define RSENT1MDCLL RSENT1.MDC.ui8[0]
#define RSENT1SPCT RSENT1.SPCT.ui32
#define RSENT1SPCTL RSENT1.SPCT.ui16[0]
#define RSENT1SPCTLL RSENT1.SPCT.ui8[0]
#define RSENT1MST RSENT1.MST.ui32
#define RSENT1MSTL RSENT1.MST.ui16[0]
#define RSENT1MSTLL RSENT1.MST.ui8[0]
#define RSENT1CS RSENT1.CS.ui32
#define RSENT1CSL RSENT1.CS.ui16[0]
#define RSENT1CSLL RSENT1.CS.ui8[0]
#define RSENT1CSLH RSENT1.CS.ui8[1]
#define RSENT1CSC RSENT1.CSC.ui32
#define RSENT1CSCL RSENT1.CSC.ui16[0]
#define RSENT1CSCLL RSENT1.CSC.ui8[0]
#define RSENT1CSCLH RSENT1.CSC.ui8[1]
#define RSENT1SRTS RSENT1.SRTS.ui32
#define RSENT1SRTSL RSENT1.SRTS.ui16[0]
#define RSENT1SRTSLL RSENT1.SRTS.ui8[0]
#define RSENT1SRTSLH RSENT1.SRTS.ui8[1]
#define RSENT1SRTSH RSENT1.SRTS.ui16[1]
#define RSENT1SRTSHL RSENT1.SRTS.ui8[2]
#define RSENT1SRTSHH RSENT1.SRTS.ui8[3]
#define RSENT1SRXD RSENT1.SRXD
#define RSENT1CPL RSENT1.CPL.ui32
#define RSENT1CPLL RSENT1.CPL.ui16[0]
#define RSENT1CPLLL RSENT1.CPL.ui8[0]
#define RSENT1CPLLH RSENT1.CPL.ui8[1]
#define RSENT1CPLH RSENT1.CPL.ui16[1]
#define RSENT1CPLHL RSENT1.CPL.ui8[2]
#define RSENT1ML RSENT1.ML.ui32
#define RSENT1MLL RSENT1.ML.ui16[0]
#define RSENT1MLLL RSENT1.ML.ui8[0]
#define RSENT1MLLH RSENT1.ML.ui8[1]
#define RSENT1MLH RSENT1.ML.ui16[1]
#define RSENT1MLHL RSENT1.ML.ui8[2]
#define RSENT1FRTS RSENT1.FRTS.ui32
#define RSENT1FRTSL RSENT1.FRTS.ui16[0]
#define RSENT1FRTSLL RSENT1.FRTS.ui8[0]
#define RSENT1FRTSLH RSENT1.FRTS.ui8[1]
#define RSENT1FRTSH RSENT1.FRTS.ui16[1]
#define RSENT1FRTSHL RSENT1.FRTS.ui8[2]
#define RSENT1FRTSHH RSENT1.FRTS.ui8[3]
#define RSENT1FRXD RSENT1.FRXD
#define RSENT2TSPC RSENT2.TSPC.ui32
#define RSENT2TSPCL RSENT2.TSPC.ui16[0]
#define RSENT2TSPCLL RSENT2.TSPC.ui8[0]
#define RSENT2TSPCLH RSENT2.TSPC.ui8[1]
#define RSENT2TSPCH RSENT2.TSPC.ui16[1]
#define RSENT2TSPCHL RSENT2.TSPC.ui8[2]
#define RSENT2TSC RSENT2.TSC.ui32
#define RSENT2TSCL RSENT2.TSC.ui16[0]
#define RSENT2TSCLL RSENT2.TSC.ui8[0]
#define RSENT2TSCLH RSENT2.TSC.ui8[1]
#define RSENT2TSCH RSENT2.TSC.ui16[1]
#define RSENT2TSCHL RSENT2.TSC.ui8[2]
#define RSENT2TSCHH RSENT2.TSC.ui8[3]
#define RSENT2CC RSENT2.CC.ui32
#define RSENT2CCL RSENT2.CC.ui16[0]
#define RSENT2CCLL RSENT2.CC.ui8[0]
#define RSENT2CCLH RSENT2.CC.ui8[1]
#define RSENT2BRP RSENT2.BRP.ui32
#define RSENT2BRPL RSENT2.BRP.ui16[0]
#define RSENT2BRPLL RSENT2.BRP.ui8[0]
#define RSENT2BRPLH RSENT2.BRP.ui8[1]
#define RSENT2BRPH RSENT2.BRP.ui16[1]
#define RSENT2BRPHL RSENT2.BRP.ui8[2]
#define RSENT2BRPHH RSENT2.BRP.ui8[3]
#define RSENT2IDE RSENT2.IDE.ui32
#define RSENT2IDEL RSENT2.IDE.ui16[0]
#define RSENT2IDELL RSENT2.IDE.ui8[0]
#define RSENT2IDELH RSENT2.IDE.ui8[1]
#define RSENT2MDC RSENT2.MDC.ui32
#define RSENT2MDCL RSENT2.MDC.ui16[0]
#define RSENT2MDCLL RSENT2.MDC.ui8[0]
#define RSENT2SPCT RSENT2.SPCT.ui32
#define RSENT2SPCTL RSENT2.SPCT.ui16[0]
#define RSENT2SPCTLL RSENT2.SPCT.ui8[0]
#define RSENT2MST RSENT2.MST.ui32
#define RSENT2MSTL RSENT2.MST.ui16[0]
#define RSENT2MSTLL RSENT2.MST.ui8[0]
#define RSENT2CS RSENT2.CS.ui32
#define RSENT2CSL RSENT2.CS.ui16[0]
#define RSENT2CSLL RSENT2.CS.ui8[0]
#define RSENT2CSLH RSENT2.CS.ui8[1]
#define RSENT2CSC RSENT2.CSC.ui32
#define RSENT2CSCL RSENT2.CSC.ui16[0]
#define RSENT2CSCLL RSENT2.CSC.ui8[0]
#define RSENT2CSCLH RSENT2.CSC.ui8[1]
#define RSENT2SRTS RSENT2.SRTS.ui32
#define RSENT2SRTSL RSENT2.SRTS.ui16[0]
#define RSENT2SRTSLL RSENT2.SRTS.ui8[0]
#define RSENT2SRTSLH RSENT2.SRTS.ui8[1]
#define RSENT2SRTSH RSENT2.SRTS.ui16[1]
#define RSENT2SRTSHL RSENT2.SRTS.ui8[2]
#define RSENT2SRTSHH RSENT2.SRTS.ui8[3]
#define RSENT2SRXD RSENT2.SRXD
#define RSENT2CPL RSENT2.CPL.ui32
#define RSENT2CPLL RSENT2.CPL.ui16[0]
#define RSENT2CPLLL RSENT2.CPL.ui8[0]
#define RSENT2CPLLH RSENT2.CPL.ui8[1]
#define RSENT2CPLH RSENT2.CPL.ui16[1]
#define RSENT2CPLHL RSENT2.CPL.ui8[2]
#define RSENT2ML RSENT2.ML.ui32
#define RSENT2MLL RSENT2.ML.ui16[0]
#define RSENT2MLLL RSENT2.ML.ui8[0]
#define RSENT2MLLH RSENT2.ML.ui8[1]
#define RSENT2MLH RSENT2.ML.ui16[1]
#define RSENT2MLHL RSENT2.ML.ui8[2]
#define RSENT2FRTS RSENT2.FRTS.ui32
#define RSENT2FRTSL RSENT2.FRTS.ui16[0]
#define RSENT2FRTSLL RSENT2.FRTS.ui8[0]
#define RSENT2FRTSLH RSENT2.FRTS.ui8[1]
#define RSENT2FRTSH RSENT2.FRTS.ui16[1]
#define RSENT2FRTSHL RSENT2.FRTS.ui8[2]
#define RSENT2FRTSHH RSENT2.FRTS.ui8[3]
#define RSENT2FRXD RSENT2.FRXD
#define RSENT3TSPC RSENT3.TSPC.ui32
#define RSENT3TSPCL RSENT3.TSPC.ui16[0]
#define RSENT3TSPCLL RSENT3.TSPC.ui8[0]
#define RSENT3TSPCLH RSENT3.TSPC.ui8[1]
#define RSENT3TSPCH RSENT3.TSPC.ui16[1]
#define RSENT3TSPCHL RSENT3.TSPC.ui8[2]
#define RSENT3TSC RSENT3.TSC.ui32
#define RSENT3TSCL RSENT3.TSC.ui16[0]
#define RSENT3TSCLL RSENT3.TSC.ui8[0]
#define RSENT3TSCLH RSENT3.TSC.ui8[1]
#define RSENT3TSCH RSENT3.TSC.ui16[1]
#define RSENT3TSCHL RSENT3.TSC.ui8[2]
#define RSENT3TSCHH RSENT3.TSC.ui8[3]
#define RSENT3CC RSENT3.CC.ui32
#define RSENT3CCL RSENT3.CC.ui16[0]
#define RSENT3CCLL RSENT3.CC.ui8[0]
#define RSENT3CCLH RSENT3.CC.ui8[1]
#define RSENT3BRP RSENT3.BRP.ui32
#define RSENT3BRPL RSENT3.BRP.ui16[0]
#define RSENT3BRPLL RSENT3.BRP.ui8[0]
#define RSENT3BRPLH RSENT3.BRP.ui8[1]
#define RSENT3BRPH RSENT3.BRP.ui16[1]
#define RSENT3BRPHL RSENT3.BRP.ui8[2]
#define RSENT3BRPHH RSENT3.BRP.ui8[3]
#define RSENT3IDE RSENT3.IDE.ui32
#define RSENT3IDEL RSENT3.IDE.ui16[0]
#define RSENT3IDELL RSENT3.IDE.ui8[0]
#define RSENT3IDELH RSENT3.IDE.ui8[1]
#define RSENT3MDC RSENT3.MDC.ui32
#define RSENT3MDCL RSENT3.MDC.ui16[0]
#define RSENT3MDCLL RSENT3.MDC.ui8[0]
#define RSENT3SPCT RSENT3.SPCT.ui32
#define RSENT3SPCTL RSENT3.SPCT.ui16[0]
#define RSENT3SPCTLL RSENT3.SPCT.ui8[0]
#define RSENT3MST RSENT3.MST.ui32
#define RSENT3MSTL RSENT3.MST.ui16[0]
#define RSENT3MSTLL RSENT3.MST.ui8[0]
#define RSENT3CS RSENT3.CS.ui32
#define RSENT3CSL RSENT3.CS.ui16[0]
#define RSENT3CSLL RSENT3.CS.ui8[0]
#define RSENT3CSLH RSENT3.CS.ui8[1]
#define RSENT3CSC RSENT3.CSC.ui32
#define RSENT3CSCL RSENT3.CSC.ui16[0]
#define RSENT3CSCLL RSENT3.CSC.ui8[0]
#define RSENT3CSCLH RSENT3.CSC.ui8[1]
#define RSENT3SRTS RSENT3.SRTS.ui32
#define RSENT3SRTSL RSENT3.SRTS.ui16[0]
#define RSENT3SRTSLL RSENT3.SRTS.ui8[0]
#define RSENT3SRTSLH RSENT3.SRTS.ui8[1]
#define RSENT3SRTSH RSENT3.SRTS.ui16[1]
#define RSENT3SRTSHL RSENT3.SRTS.ui8[2]
#define RSENT3SRTSHH RSENT3.SRTS.ui8[3]
#define RSENT3SRXD RSENT3.SRXD
#define RSENT3CPL RSENT3.CPL.ui32
#define RSENT3CPLL RSENT3.CPL.ui16[0]
#define RSENT3CPLLL RSENT3.CPL.ui8[0]
#define RSENT3CPLLH RSENT3.CPL.ui8[1]
#define RSENT3CPLH RSENT3.CPL.ui16[1]
#define RSENT3CPLHL RSENT3.CPL.ui8[2]
#define RSENT3ML RSENT3.ML.ui32
#define RSENT3MLL RSENT3.ML.ui16[0]
#define RSENT3MLLL RSENT3.ML.ui8[0]
#define RSENT3MLLH RSENT3.ML.ui8[1]
#define RSENT3MLH RSENT3.ML.ui16[1]
#define RSENT3MLHL RSENT3.ML.ui8[2]
#define RSENT3FRTS RSENT3.FRTS.ui32
#define RSENT3FRTSL RSENT3.FRTS.ui16[0]
#define RSENT3FRTSLL RSENT3.FRTS.ui8[0]
#define RSENT3FRTSLH RSENT3.FRTS.ui8[1]
#define RSENT3FRTSH RSENT3.FRTS.ui16[1]
#define RSENT3FRTSHL RSENT3.FRTS.ui8[2]
#define RSENT3FRTSHH RSENT3.FRTS.ui8[3]
#define RSENT3FRXD RSENT3.FRXD
#define SINTR0 SINT.R0
#define SINTR1 SINT.R1
#define SINTR2 SINT.R2
#define MTTCAN0CREL MTTCAN0.CREL.ui32
#define MTTCAN0CRELL MTTCAN0.CREL.ui16[0]
#define MTTCAN0CRELLL MTTCAN0.CREL.ui8[0]
#define MTTCAN0CRELLH MTTCAN0.CREL.ui8[1]
#define MTTCAN0CRELH MTTCAN0.CREL.ui16[1]
#define MTTCAN0CRELHL MTTCAN0.CREL.ui8[2]
#define MTTCAN0CRELHH MTTCAN0.CREL.ui8[3]
#define MTTCAN0ENDN MTTCAN0.ENDN.ui32
#define MTTCAN0ENDNL MTTCAN0.ENDN.ui16[0]
#define MTTCAN0ENDNLL MTTCAN0.ENDN.ui8[0]
#define MTTCAN0ENDNLH MTTCAN0.ENDN.ui8[1]
#define MTTCAN0ENDNH MTTCAN0.ENDN.ui16[1]
#define MTTCAN0ENDNHL MTTCAN0.ENDN.ui8[2]
#define MTTCAN0ENDNHH MTTCAN0.ENDN.ui8[3]
#define MTTCAN0DBTP MTTCAN0.DBTP.ui32
#define MTTCAN0DBTPL MTTCAN0.DBTP.ui16[0]
#define MTTCAN0DBTPLL MTTCAN0.DBTP.ui8[0]
#define MTTCAN0DBTPLH MTTCAN0.DBTP.ui8[1]
#define MTTCAN0DBTPH MTTCAN0.DBTP.ui16[1]
#define MTTCAN0DBTPHL MTTCAN0.DBTP.ui8[2]
#define MTTCAN0DBTPHH MTTCAN0.DBTP.ui8[3]
#define MTTCAN0TEST MTTCAN0.TEST.ui32
#define MTTCAN0TESTL MTTCAN0.TEST.ui16[0]
#define MTTCAN0TESTLL MTTCAN0.TEST.ui8[0]
#define MTTCAN0TESTLH MTTCAN0.TEST.ui8[1]
#define MTTCAN0RWD MTTCAN0.RWD.ui32
#define MTTCAN0RWDL MTTCAN0.RWD.ui16[0]
#define MTTCAN0RWDLL MTTCAN0.RWD.ui8[0]
#define MTTCAN0RWDLH MTTCAN0.RWD.ui8[1]
#define MTTCAN0CCCR MTTCAN0.CCCR.ui32
#define MTTCAN0CCCRL MTTCAN0.CCCR.ui16[0]
#define MTTCAN0CCCRLL MTTCAN0.CCCR.ui8[0]
#define MTTCAN0CCCRLH MTTCAN0.CCCR.ui8[1]
#define MTTCAN0NBTP MTTCAN0.NBTP.ui32
#define MTTCAN0NBTPL MTTCAN0.NBTP.ui16[0]
#define MTTCAN0NBTPLL MTTCAN0.NBTP.ui8[0]
#define MTTCAN0NBTPLH MTTCAN0.NBTP.ui8[1]
#define MTTCAN0NBTPH MTTCAN0.NBTP.ui16[1]
#define MTTCAN0NBTPHL MTTCAN0.NBTP.ui8[2]
#define MTTCAN0NBTPHH MTTCAN0.NBTP.ui8[3]
#define MTTCAN0TSCC MTTCAN0.TSCC.ui32
#define MTTCAN0TSCCL MTTCAN0.TSCC.ui16[0]
#define MTTCAN0TSCCLL MTTCAN0.TSCC.ui8[0]
#define MTTCAN0TSCCLH MTTCAN0.TSCC.ui8[1]
#define MTTCAN0TSCCH MTTCAN0.TSCC.ui16[1]
#define MTTCAN0TSCCHL MTTCAN0.TSCC.ui8[2]
#define MTTCAN0TSCCHH MTTCAN0.TSCC.ui8[3]
#define MTTCAN0TSCV MTTCAN0.TSCV.ui32
#define MTTCAN0TSCVL MTTCAN0.TSCV.ui16[0]
#define MTTCAN0TSCVLL MTTCAN0.TSCV.ui8[0]
#define MTTCAN0TSCVLH MTTCAN0.TSCV.ui8[1]
#define MTTCAN0TOCC MTTCAN0.TOCC.ui32
#define MTTCAN0TOCCL MTTCAN0.TOCC.ui16[0]
#define MTTCAN0TOCCLL MTTCAN0.TOCC.ui8[0]
#define MTTCAN0TOCCLH MTTCAN0.TOCC.ui8[1]
#define MTTCAN0TOCCH MTTCAN0.TOCC.ui16[1]
#define MTTCAN0TOCCHL MTTCAN0.TOCC.ui8[2]
#define MTTCAN0TOCCHH MTTCAN0.TOCC.ui8[3]
#define MTTCAN0TOCV MTTCAN0.TOCV.ui32
#define MTTCAN0TOCVL MTTCAN0.TOCV.ui16[0]
#define MTTCAN0TOCVLL MTTCAN0.TOCV.ui8[0]
#define MTTCAN0TOCVLH MTTCAN0.TOCV.ui8[1]
#define MTTCAN0ECR MTTCAN0.ECR.ui32
#define MTTCAN0ECRL MTTCAN0.ECR.ui16[0]
#define MTTCAN0ECRLL MTTCAN0.ECR.ui8[0]
#define MTTCAN0ECRLH MTTCAN0.ECR.ui8[1]
#define MTTCAN0ECRH MTTCAN0.ECR.ui16[1]
#define MTTCAN0ECRHL MTTCAN0.ECR.ui8[2]
#define MTTCAN0ECRHH MTTCAN0.ECR.ui8[3]
#define MTTCAN0PSR MTTCAN0.PSR.ui32
#define MTTCAN0PSRL MTTCAN0.PSR.ui16[0]
#define MTTCAN0PSRLL MTTCAN0.PSR.ui8[0]
#define MTTCAN0PSRLH MTTCAN0.PSR.ui8[1]
#define MTTCAN0TDCR MTTCAN0.TDCR.ui32
#define MTTCAN0TDCRL MTTCAN0.TDCR.ui16[0]
#define MTTCAN0TDCRLL MTTCAN0.TDCR.ui8[0]
#define MTTCAN0TDCRLH MTTCAN0.TDCR.ui8[1]
#define MTTCAN0IR MTTCAN0.IR.ui32
#define MTTCAN0IRL MTTCAN0.IR.ui16[0]
#define MTTCAN0IRLL MTTCAN0.IR.ui8[0]
#define MTTCAN0IRLH MTTCAN0.IR.ui8[1]
#define MTTCAN0IRH MTTCAN0.IR.ui16[1]
#define MTTCAN0IRHL MTTCAN0.IR.ui8[2]
#define MTTCAN0IRHH MTTCAN0.IR.ui8[3]
#define MTTCAN0IE MTTCAN0.IE.ui32
#define MTTCAN0IEL MTTCAN0.IE.ui16[0]
#define MTTCAN0IELL MTTCAN0.IE.ui8[0]
#define MTTCAN0IELH MTTCAN0.IE.ui8[1]
#define MTTCAN0IEH MTTCAN0.IE.ui16[1]
#define MTTCAN0IEHL MTTCAN0.IE.ui8[2]
#define MTTCAN0IEHH MTTCAN0.IE.ui8[3]
#define MTTCAN0ILS MTTCAN0.ILS.ui32
#define MTTCAN0ILSL MTTCAN0.ILS.ui16[0]
#define MTTCAN0ILSLL MTTCAN0.ILS.ui8[0]
#define MTTCAN0ILSLH MTTCAN0.ILS.ui8[1]
#define MTTCAN0ILSH MTTCAN0.ILS.ui16[1]
#define MTTCAN0ILSHL MTTCAN0.ILS.ui8[2]
#define MTTCAN0ILSHH MTTCAN0.ILS.ui8[3]
#define MTTCAN0ILE MTTCAN0.ILE.ui32
#define MTTCAN0ILEL MTTCAN0.ILE.ui16[0]
#define MTTCAN0ILELL MTTCAN0.ILE.ui8[0]
#define MTTCAN0ILELH MTTCAN0.ILE.ui8[1]
#define MTTCAN0GFC MTTCAN0.GFC.ui32
#define MTTCAN0GFCL MTTCAN0.GFC.ui16[0]
#define MTTCAN0GFCLL MTTCAN0.GFC.ui8[0]
#define MTTCAN0GFCLH MTTCAN0.GFC.ui8[1]
#define MTTCAN0SIDFC MTTCAN0.SIDFC.ui32
#define MTTCAN0SIDFCL MTTCAN0.SIDFC.ui16[0]
#define MTTCAN0SIDFCLL MTTCAN0.SIDFC.ui8[0]
#define MTTCAN0SIDFCLH MTTCAN0.SIDFC.ui8[1]
#define MTTCAN0SIDFCH MTTCAN0.SIDFC.ui16[1]
#define MTTCAN0SIDFCHL MTTCAN0.SIDFC.ui8[2]
#define MTTCAN0SIDFCHH MTTCAN0.SIDFC.ui8[3]
#define MTTCAN0XIDFC MTTCAN0.XIDFC.ui32
#define MTTCAN0XIDFCL MTTCAN0.XIDFC.ui16[0]
#define MTTCAN0XIDFCLL MTTCAN0.XIDFC.ui8[0]
#define MTTCAN0XIDFCLH MTTCAN0.XIDFC.ui8[1]
#define MTTCAN0XIDFCH MTTCAN0.XIDFC.ui16[1]
#define MTTCAN0XIDFCHL MTTCAN0.XIDFC.ui8[2]
#define MTTCAN0XIDFCHH MTTCAN0.XIDFC.ui8[3]
#define MTTCAN0XIDAM MTTCAN0.XIDAM.ui32
#define MTTCAN0XIDAML MTTCAN0.XIDAM.ui16[0]
#define MTTCAN0XIDAMLL MTTCAN0.XIDAM.ui8[0]
#define MTTCAN0XIDAMLH MTTCAN0.XIDAM.ui8[1]
#define MTTCAN0XIDAMH MTTCAN0.XIDAM.ui16[1]
#define MTTCAN0XIDAMHL MTTCAN0.XIDAM.ui8[2]
#define MTTCAN0XIDAMHH MTTCAN0.XIDAM.ui8[3]
#define MTTCAN0HPMS MTTCAN0.HPMS.ui32
#define MTTCAN0HPMSL MTTCAN0.HPMS.ui16[0]
#define MTTCAN0HPMSLL MTTCAN0.HPMS.ui8[0]
#define MTTCAN0HPMSLH MTTCAN0.HPMS.ui8[1]
#define MTTCAN0NDAT1 MTTCAN0.NDAT1.ui32
#define MTTCAN0NDAT1L MTTCAN0.NDAT1.ui16[0]
#define MTTCAN0NDAT1LL MTTCAN0.NDAT1.ui8[0]
#define MTTCAN0NDAT1LH MTTCAN0.NDAT1.ui8[1]
#define MTTCAN0NDAT1H MTTCAN0.NDAT1.ui16[1]
#define MTTCAN0NDAT1HL MTTCAN0.NDAT1.ui8[2]
#define MTTCAN0NDAT1HH MTTCAN0.NDAT1.ui8[3]
#define MTTCAN0NDAT2 MTTCAN0.NDAT2.ui32
#define MTTCAN0NDAT2L MTTCAN0.NDAT2.ui16[0]
#define MTTCAN0NDAT2LL MTTCAN0.NDAT2.ui8[0]
#define MTTCAN0NDAT2LH MTTCAN0.NDAT2.ui8[1]
#define MTTCAN0NDAT2H MTTCAN0.NDAT2.ui16[1]
#define MTTCAN0NDAT2HL MTTCAN0.NDAT2.ui8[2]
#define MTTCAN0NDAT2HH MTTCAN0.NDAT2.ui8[3]
#define MTTCAN0RXF0C MTTCAN0.RXF0C.ui32
#define MTTCAN0RXF0CL MTTCAN0.RXF0C.ui16[0]
#define MTTCAN0RXF0CLL MTTCAN0.RXF0C.ui8[0]
#define MTTCAN0RXF0CLH MTTCAN0.RXF0C.ui8[1]
#define MTTCAN0RXF0CH MTTCAN0.RXF0C.ui16[1]
#define MTTCAN0RXF0CHL MTTCAN0.RXF0C.ui8[2]
#define MTTCAN0RXF0CHH MTTCAN0.RXF0C.ui8[3]
#define MTTCAN0RXF0S MTTCAN0.RXF0S.ui32
#define MTTCAN0RXF0SL MTTCAN0.RXF0S.ui16[0]
#define MTTCAN0RXF0SLL MTTCAN0.RXF0S.ui8[0]
#define MTTCAN0RXF0SLH MTTCAN0.RXF0S.ui8[1]
#define MTTCAN0RXF0SH MTTCAN0.RXF0S.ui16[1]
#define MTTCAN0RXF0SHL MTTCAN0.RXF0S.ui8[2]
#define MTTCAN0RXF0SHH MTTCAN0.RXF0S.ui8[3]
#define MTTCAN0RXF0A MTTCAN0.RXF0A.ui32
#define MTTCAN0RXF0AL MTTCAN0.RXF0A.ui16[0]
#define MTTCAN0RXF0ALL MTTCAN0.RXF0A.ui8[0]
#define MTTCAN0RXF0ALH MTTCAN0.RXF0A.ui8[1]
#define MTTCAN0RXBC MTTCAN0.RXBC.ui32
#define MTTCAN0RXBCL MTTCAN0.RXBC.ui16[0]
#define MTTCAN0RXBCLL MTTCAN0.RXBC.ui8[0]
#define MTTCAN0RXBCLH MTTCAN0.RXBC.ui8[1]
#define MTTCAN0RXF1C MTTCAN0.RXF1C.ui32
#define MTTCAN0RXF1CL MTTCAN0.RXF1C.ui16[0]
#define MTTCAN0RXF1CLL MTTCAN0.RXF1C.ui8[0]
#define MTTCAN0RXF1CLH MTTCAN0.RXF1C.ui8[1]
#define MTTCAN0RXF1CH MTTCAN0.RXF1C.ui16[1]
#define MTTCAN0RXF1CHL MTTCAN0.RXF1C.ui8[2]
#define MTTCAN0RXF1CHH MTTCAN0.RXF1C.ui8[3]
#define MTTCAN0RXF1S MTTCAN0.RXF1S.ui32
#define MTTCAN0RXF1SL MTTCAN0.RXF1S.ui16[0]
#define MTTCAN0RXF1SLL MTTCAN0.RXF1S.ui8[0]
#define MTTCAN0RXF1SLH MTTCAN0.RXF1S.ui8[1]
#define MTTCAN0RXF1SH MTTCAN0.RXF1S.ui16[1]
#define MTTCAN0RXF1SHL MTTCAN0.RXF1S.ui8[2]
#define MTTCAN0RXF1SHH MTTCAN0.RXF1S.ui8[3]
#define MTTCAN0RXF1A MTTCAN0.RXF1A.ui32
#define MTTCAN0RXF1AL MTTCAN0.RXF1A.ui16[0]
#define MTTCAN0RXF1ALL MTTCAN0.RXF1A.ui8[0]
#define MTTCAN0RXF1ALH MTTCAN0.RXF1A.ui8[1]
#define MTTCAN0RXESC MTTCAN0.RXESC.ui32
#define MTTCAN0RXESCL MTTCAN0.RXESC.ui16[0]
#define MTTCAN0RXESCLL MTTCAN0.RXESC.ui8[0]
#define MTTCAN0RXESCLH MTTCAN0.RXESC.ui8[1]
#define MTTCAN0TXBC MTTCAN0.TXBC.ui32
#define MTTCAN0TXBCL MTTCAN0.TXBC.ui16[0]
#define MTTCAN0TXBCLL MTTCAN0.TXBC.ui8[0]
#define MTTCAN0TXBCLH MTTCAN0.TXBC.ui8[1]
#define MTTCAN0TXBCH MTTCAN0.TXBC.ui16[1]
#define MTTCAN0TXBCHL MTTCAN0.TXBC.ui8[2]
#define MTTCAN0TXBCHH MTTCAN0.TXBC.ui8[3]
#define MTTCAN0TXFQS MTTCAN0.TXFQS.ui32
#define MTTCAN0TXFQSL MTTCAN0.TXFQS.ui16[0]
#define MTTCAN0TXFQSLL MTTCAN0.TXFQS.ui8[0]
#define MTTCAN0TXFQSLH MTTCAN0.TXFQS.ui8[1]
#define MTTCAN0TXFQSH MTTCAN0.TXFQS.ui16[1]
#define MTTCAN0TXFQSHL MTTCAN0.TXFQS.ui8[2]
#define MTTCAN0TXFQSHH MTTCAN0.TXFQS.ui8[3]
#define MTTCAN0TXESC MTTCAN0.TXESC.ui32
#define MTTCAN0TXESCL MTTCAN0.TXESC.ui16[0]
#define MTTCAN0TXESCLL MTTCAN0.TXESC.ui8[0]
#define MTTCAN0TXESCLH MTTCAN0.TXESC.ui8[1]
#define MTTCAN0TXBRP MTTCAN0.TXBRP.ui32
#define MTTCAN0TXBRPL MTTCAN0.TXBRP.ui16[0]
#define MTTCAN0TXBRPLL MTTCAN0.TXBRP.ui8[0]
#define MTTCAN0TXBRPLH MTTCAN0.TXBRP.ui8[1]
#define MTTCAN0TXBRPH MTTCAN0.TXBRP.ui16[1]
#define MTTCAN0TXBRPHL MTTCAN0.TXBRP.ui8[2]
#define MTTCAN0TXBRPHH MTTCAN0.TXBRP.ui8[3]
#define MTTCAN0TXBAR MTTCAN0.TXBAR.ui32
#define MTTCAN0TXBARL MTTCAN0.TXBAR.ui16[0]
#define MTTCAN0TXBARLL MTTCAN0.TXBAR.ui8[0]
#define MTTCAN0TXBARLH MTTCAN0.TXBAR.ui8[1]
#define MTTCAN0TXBARH MTTCAN0.TXBAR.ui16[1]
#define MTTCAN0TXBARHL MTTCAN0.TXBAR.ui8[2]
#define MTTCAN0TXBARHH MTTCAN0.TXBAR.ui8[3]
#define MTTCAN0TXBCR MTTCAN0.TXBCR.ui32
#define MTTCAN0TXBCRL MTTCAN0.TXBCR.ui16[0]
#define MTTCAN0TXBCRLL MTTCAN0.TXBCR.ui8[0]
#define MTTCAN0TXBCRLH MTTCAN0.TXBCR.ui8[1]
#define MTTCAN0TXBCRH MTTCAN0.TXBCR.ui16[1]
#define MTTCAN0TXBCRHL MTTCAN0.TXBCR.ui8[2]
#define MTTCAN0TXBCRHH MTTCAN0.TXBCR.ui8[3]
#define MTTCAN0TXBTO MTTCAN0.TXBTO.ui32
#define MTTCAN0TXBTOL MTTCAN0.TXBTO.ui16[0]
#define MTTCAN0TXBTOLL MTTCAN0.TXBTO.ui8[0]
#define MTTCAN0TXBTOLH MTTCAN0.TXBTO.ui8[1]
#define MTTCAN0TXBTOH MTTCAN0.TXBTO.ui16[1]
#define MTTCAN0TXBTOHL MTTCAN0.TXBTO.ui8[2]
#define MTTCAN0TXBTOHH MTTCAN0.TXBTO.ui8[3]
#define MTTCAN0TXBCF MTTCAN0.TXBCF.ui32
#define MTTCAN0TXBCFL MTTCAN0.TXBCF.ui16[0]
#define MTTCAN0TXBCFLL MTTCAN0.TXBCF.ui8[0]
#define MTTCAN0TXBCFLH MTTCAN0.TXBCF.ui8[1]
#define MTTCAN0TXBCFH MTTCAN0.TXBCF.ui16[1]
#define MTTCAN0TXBCFHL MTTCAN0.TXBCF.ui8[2]
#define MTTCAN0TXBCFHH MTTCAN0.TXBCF.ui8[3]
#define MTTCAN0TXBTIE MTTCAN0.TXBTIE.ui32
#define MTTCAN0TXBTIEL MTTCAN0.TXBTIE.ui16[0]
#define MTTCAN0TXBTIELL MTTCAN0.TXBTIE.ui8[0]
#define MTTCAN0TXBTIELH MTTCAN0.TXBTIE.ui8[1]
#define MTTCAN0TXBTIEH MTTCAN0.TXBTIE.ui16[1]
#define MTTCAN0TXBTIEHL MTTCAN0.TXBTIE.ui8[2]
#define MTTCAN0TXBTIEHH MTTCAN0.TXBTIE.ui8[3]
#define MTTCAN0TXBCIE MTTCAN0.TXBCIE.ui32
#define MTTCAN0TXBCIEL MTTCAN0.TXBCIE.ui16[0]
#define MTTCAN0TXBCIELL MTTCAN0.TXBCIE.ui8[0]
#define MTTCAN0TXBCIELH MTTCAN0.TXBCIE.ui8[1]
#define MTTCAN0TXBCIEH MTTCAN0.TXBCIE.ui16[1]
#define MTTCAN0TXBCIEHL MTTCAN0.TXBCIE.ui8[2]
#define MTTCAN0TXBCIEHH MTTCAN0.TXBCIE.ui8[3]
#define MTTCAN0TXEFC MTTCAN0.TXEFC.ui32
#define MTTCAN0TXEFCL MTTCAN0.TXEFC.ui16[0]
#define MTTCAN0TXEFCLL MTTCAN0.TXEFC.ui8[0]
#define MTTCAN0TXEFCLH MTTCAN0.TXEFC.ui8[1]
#define MTTCAN0TXEFCH MTTCAN0.TXEFC.ui16[1]
#define MTTCAN0TXEFCHL MTTCAN0.TXEFC.ui8[2]
#define MTTCAN0TXEFCHH MTTCAN0.TXEFC.ui8[3]
#define MTTCAN0TXEFS MTTCAN0.TXEFS.ui32
#define MTTCAN0TXEFSL MTTCAN0.TXEFS.ui16[0]
#define MTTCAN0TXEFSLL MTTCAN0.TXEFS.ui8[0]
#define MTTCAN0TXEFSLH MTTCAN0.TXEFS.ui8[1]
#define MTTCAN0TXEFSH MTTCAN0.TXEFS.ui16[1]
#define MTTCAN0TXEFSHL MTTCAN0.TXEFS.ui8[2]
#define MTTCAN0TXEFSHH MTTCAN0.TXEFS.ui8[3]
#define MTTCAN0TXEFA MTTCAN0.TXEFA.ui32
#define MTTCAN0TXEFAL MTTCAN0.TXEFA.ui16[0]
#define MTTCAN0TXEFALL MTTCAN0.TXEFA.ui8[0]
#define MTTCAN0TXEFALH MTTCAN0.TXEFA.ui8[1]
#define MTTCAN0TTTMC MTTCAN0.TTTMC.ui32
#define MTTCAN0TTTMCL MTTCAN0.TTTMC.ui16[0]
#define MTTCAN0TTTMCLL MTTCAN0.TTTMC.ui8[0]
#define MTTCAN0TTTMCLH MTTCAN0.TTTMC.ui8[1]
#define MTTCAN0TTTMCH MTTCAN0.TTTMC.ui16[1]
#define MTTCAN0TTTMCHL MTTCAN0.TTTMC.ui8[2]
#define MTTCAN0TTTMCHH MTTCAN0.TTTMC.ui8[3]
#define MTTCAN0TTRMC MTTCAN0.TTRMC.ui32
#define MTTCAN0TTRMCL MTTCAN0.TTRMC.ui16[0]
#define MTTCAN0TTRMCLL MTTCAN0.TTRMC.ui8[0]
#define MTTCAN0TTRMCLH MTTCAN0.TTRMC.ui8[1]
#define MTTCAN0TTRMCH MTTCAN0.TTRMC.ui16[1]
#define MTTCAN0TTRMCHL MTTCAN0.TTRMC.ui8[2]
#define MTTCAN0TTRMCHH MTTCAN0.TTRMC.ui8[3]
#define MTTCAN0TTOCF MTTCAN0.TTOCF.ui32
#define MTTCAN0TTOCFL MTTCAN0.TTOCF.ui16[0]
#define MTTCAN0TTOCFLL MTTCAN0.TTOCF.ui8[0]
#define MTTCAN0TTOCFLH MTTCAN0.TTOCF.ui8[1]
#define MTTCAN0TTOCFH MTTCAN0.TTOCF.ui16[1]
#define MTTCAN0TTOCFHL MTTCAN0.TTOCF.ui8[2]
#define MTTCAN0TTOCFHH MTTCAN0.TTOCF.ui8[3]
#define MTTCAN0TTMLM MTTCAN0.TTMLM.ui32
#define MTTCAN0TTMLML MTTCAN0.TTMLM.ui16[0]
#define MTTCAN0TTMLMLL MTTCAN0.TTMLM.ui8[0]
#define MTTCAN0TTMLMLH MTTCAN0.TTMLM.ui8[1]
#define MTTCAN0TTMLMH MTTCAN0.TTMLM.ui16[1]
#define MTTCAN0TTMLMHL MTTCAN0.TTMLM.ui8[2]
#define MTTCAN0TTMLMHH MTTCAN0.TTMLM.ui8[3]
#define MTTCAN0TURCF MTTCAN0.TURCF.ui32
#define MTTCAN0TURCFL MTTCAN0.TURCF.ui16[0]
#define MTTCAN0TURCFLL MTTCAN0.TURCF.ui8[0]
#define MTTCAN0TURCFLH MTTCAN0.TURCF.ui8[1]
#define MTTCAN0TURCFH MTTCAN0.TURCF.ui16[1]
#define MTTCAN0TURCFHL MTTCAN0.TURCF.ui8[2]
#define MTTCAN0TURCFHH MTTCAN0.TURCF.ui8[3]
#define MTTCAN0TTOCN MTTCAN0.TTOCN.ui32
#define MTTCAN0TTOCNL MTTCAN0.TTOCN.ui16[0]
#define MTTCAN0TTOCNLL MTTCAN0.TTOCN.ui8[0]
#define MTTCAN0TTOCNLH MTTCAN0.TTOCN.ui8[1]
#define MTTCAN0TTGTP MTTCAN0.TTGTP.ui32
#define MTTCAN0TTGTPL MTTCAN0.TTGTP.ui16[0]
#define MTTCAN0TTGTPLL MTTCAN0.TTGTP.ui8[0]
#define MTTCAN0TTGTPLH MTTCAN0.TTGTP.ui8[1]
#define MTTCAN0TTGTPH MTTCAN0.TTGTP.ui16[1]
#define MTTCAN0TTGTPHL MTTCAN0.TTGTP.ui8[2]
#define MTTCAN0TTGTPHH MTTCAN0.TTGTP.ui8[3]
#define MTTCAN0TTTMK MTTCAN0.TTTMK.ui32
#define MTTCAN0TTTMKL MTTCAN0.TTTMK.ui16[0]
#define MTTCAN0TTTMKLL MTTCAN0.TTTMK.ui8[0]
#define MTTCAN0TTTMKLH MTTCAN0.TTTMK.ui8[1]
#define MTTCAN0TTTMKH MTTCAN0.TTTMK.ui16[1]
#define MTTCAN0TTTMKHL MTTCAN0.TTTMK.ui8[2]
#define MTTCAN0TTTMKHH MTTCAN0.TTTMK.ui8[3]
#define MTTCAN0TTIR MTTCAN0.TTIR.ui32
#define MTTCAN0TTIRL MTTCAN0.TTIR.ui16[0]
#define MTTCAN0TTIRLL MTTCAN0.TTIR.ui8[0]
#define MTTCAN0TTIRLH MTTCAN0.TTIR.ui8[1]
#define MTTCAN0TTIRH MTTCAN0.TTIR.ui16[1]
#define MTTCAN0TTIRHL MTTCAN0.TTIR.ui8[2]
#define MTTCAN0TTIRHH MTTCAN0.TTIR.ui8[3]
#define MTTCAN0TTIE MTTCAN0.TTIE.ui32
#define MTTCAN0TTIEL MTTCAN0.TTIE.ui16[0]
#define MTTCAN0TTIELL MTTCAN0.TTIE.ui8[0]
#define MTTCAN0TTIELH MTTCAN0.TTIE.ui8[1]
#define MTTCAN0TTIEH MTTCAN0.TTIE.ui16[1]
#define MTTCAN0TTIEHL MTTCAN0.TTIE.ui8[2]
#define MTTCAN0TTIEHH MTTCAN0.TTIE.ui8[3]
#define MTTCAN0TTILS MTTCAN0.TTILS.ui32
#define MTTCAN0TTILSL MTTCAN0.TTILS.ui16[0]
#define MTTCAN0TTILSLL MTTCAN0.TTILS.ui8[0]
#define MTTCAN0TTILSLH MTTCAN0.TTILS.ui8[1]
#define MTTCAN0TTILSH MTTCAN0.TTILS.ui16[1]
#define MTTCAN0TTILSHL MTTCAN0.TTILS.ui8[2]
#define MTTCAN0TTILSHH MTTCAN0.TTILS.ui8[3]
#define MTTCAN0TTOST MTTCAN0.TTOST.ui32
#define MTTCAN0TTOSTL MTTCAN0.TTOST.ui16[0]
#define MTTCAN0TTOSTLL MTTCAN0.TTOST.ui8[0]
#define MTTCAN0TTOSTLH MTTCAN0.TTOST.ui8[1]
#define MTTCAN0TTOSTH MTTCAN0.TTOST.ui16[1]
#define MTTCAN0TTOSTHL MTTCAN0.TTOST.ui8[2]
#define MTTCAN0TTOSTHH MTTCAN0.TTOST.ui8[3]
#define MTTCAN0TURNA MTTCAN0.TURNA.ui32
#define MTTCAN0TURNAL MTTCAN0.TURNA.ui16[0]
#define MTTCAN0TURNALL MTTCAN0.TURNA.ui8[0]
#define MTTCAN0TURNALH MTTCAN0.TURNA.ui8[1]
#define MTTCAN0TURNAH MTTCAN0.TURNA.ui16[1]
#define MTTCAN0TURNAHL MTTCAN0.TURNA.ui8[2]
#define MTTCAN0TURNAHH MTTCAN0.TURNA.ui8[3]
#define MTTCAN0TTLGT MTTCAN0.TTLGT.ui32
#define MTTCAN0TTLGTL MTTCAN0.TTLGT.ui16[0]
#define MTTCAN0TTLGTLL MTTCAN0.TTLGT.ui8[0]
#define MTTCAN0TTLGTLH MTTCAN0.TTLGT.ui8[1]
#define MTTCAN0TTLGTH MTTCAN0.TTLGT.ui16[1]
#define MTTCAN0TTLGTHL MTTCAN0.TTLGT.ui8[2]
#define MTTCAN0TTLGTHH MTTCAN0.TTLGT.ui8[3]
#define MTTCAN0TTCTC MTTCAN0.TTCTC.ui32
#define MTTCAN0TTCTCL MTTCAN0.TTCTC.ui16[0]
#define MTTCAN0TTCTCLL MTTCAN0.TTCTC.ui8[0]
#define MTTCAN0TTCTCLH MTTCAN0.TTCTC.ui8[1]
#define MTTCAN0TTCTCH MTTCAN0.TTCTC.ui16[1]
#define MTTCAN0TTCTCHL MTTCAN0.TTCTC.ui8[2]
#define MTTCAN0TTCTCHH MTTCAN0.TTCTC.ui8[3]
#define MTTCAN0TTCPT MTTCAN0.TTCPT.ui32
#define MTTCAN0TTCPTL MTTCAN0.TTCPT.ui16[0]
#define MTTCAN0TTCPTLL MTTCAN0.TTCPT.ui8[0]
#define MTTCAN0TTCPTLH MTTCAN0.TTCPT.ui8[1]
#define MTTCAN0TTCPTH MTTCAN0.TTCPT.ui16[1]
#define MTTCAN0TTCPTHL MTTCAN0.TTCPT.ui8[2]
#define MTTCAN0TTCPTHH MTTCAN0.TTCPT.ui8[3]
#define MTTCAN0TTCSM MTTCAN0.TTCSM.ui32
#define MTTCAN0TTCSML MTTCAN0.TTCSM.ui16[0]
#define MTTCAN0TTCSMLL MTTCAN0.TTCSM.ui8[0]
#define MTTCAN0TTCSMLH MTTCAN0.TTCSM.ui8[1]
#define DCRB0CIN DCRB0.CIN
#define DCRB0COUT DCRB0.COUT
#define DCRB0CTL DCRB0.CTL
#define ECMM0ESET ECMM0.ESET
#define ECMM0ECLR ECMM0.ECLR
#define ECMM0ESSTR0 ECMM0.ESSTR0
#define ECMM0ESSTR1 ECMM0.ESSTR1
#define ECMM0ESSTR2 ECMM0.ESSTR2
#define ECMM0PCMD0 ECMM0.PCMD0
#define ECMC0ESET ECMC0.ESET
#define ECMC0ECLR ECMC0.ECLR
#define ECMC0ESSTR0 ECMC0.ESSTR0
#define ECMC0ESSTR1 ECMC0.ESSTR1
#define ECMC0ESSTR2 ECMC0.ESSTR2
#define ECMC0PCMD0 ECMC0.PCMD0
#define ECM0EPCFG ECM0.EPCFG
#define ECM0MICFG0 ECM0.MICFG0
#define ECM0MICFG1 ECM0.MICFG1
#define ECM0MICFG2 ECM0.MICFG2
#define ECM0NMICFG0 ECM0.NMICFG0
#define ECM0NMICFG1 ECM0.NMICFG1
#define ECM0NMICFG2 ECM0.NMICFG2
#define ECM0IRCFG0 ECM0.IRCFG0
#define ECM0IRCFG1 ECM0.IRCFG1
#define ECM0IRCFG2 ECM0.IRCFG2
#define ECM0EMK0 ECM0.EMK0
#define ECM0EMK1 ECM0.EMK1
#define ECM0EMK2 ECM0.EMK2
#define ECM0ESSTC0 ECM0.ESSTC0
#define ECM0ESSTC1 ECM0.ESSTC1
#define ECM0ESSTC2 ECM0.ESSTC2
#define ECM0PCMD1 ECM0.PCMD1
#define ECM0PS ECM0.PS
#define ECM0PE0 ECM0.PE0
#define ECM0PE1 ECM0.PE1
#define ECM0PE2 ECM0.PE2
#define ECM0DTMCTL ECM0.DTMCTL
#define ECM0DTMR ECM0.DTMR
#define ECM0DTMCMP ECM0.DTMCMP
#define ECM0DTMCFG0 ECM0.DTMCFG0
#define ECM0DTMCFG1 ECM0.DTMCFG1
#define ECM0DTMCFG2 ECM0.DTMCFG2
#define ECM0DTMCFG3 ECM0.DTMCFG3
#define ECM0DTMCFG4 ECM0.DTMCFG4
#define ECM0DTMCFG5 ECM0.DTMCFG5
#define ECM0EOCCFG ECM0.EOCCFG
#define ECM0PEM ECM0.PEM
#define PIC2CTRGPREMUX0 PIC2C.TRGPREMUX0
#define PIC2CTRGMUX0 PIC2C.TRGMUX0
#define PIC2CEDGSEL0 PIC2C.EDGSEL0
#define PIC2CENP2TIM0 PIC2C.ENP2TIM0
#define PIC2CENP2TIM1 PIC2C.ENP2TIM1
#define PIC2CENHIZDTM PIC2C.ENHIZDTM
#define CSIH0CTL0 CSIH0.CTL0.ui8
#define CSIH0CTL1 CSIH0.CTL1
#define CSIH0CTL2 CSIH0.CTL2
#define CSIH0MCTL1 CSIH0.MCTL1
#define CSIH0MCTL2 CSIH0.MCTL2
#define CSIH0TX0W CSIH0.TX0W
#define CSIH0TX0H CSIH0.TX0H
#define CSIH0RX0W CSIH0.RX0W
#define CSIH0RX0H CSIH0.RX0H
#define CSIH0MRWP0 CSIH0.MRWP0
#define CSIH0STR0 CSIH0.STR0
#define CSIH0STCR0 CSIH0.STCR0
#define CSIH0MCTL0 CSIH0.MCTL0
#define CSIH0CFG0 CSIH0.CFG0
#define CSIH0CFG1 CSIH0.CFG1
#define CSIH0CFG2 CSIH0.CFG2
#define CSIH0CFG3 CSIH0.CFG3
#define CSIH0CFG4 CSIH0.CFG4
#define CSIH0CFG5 CSIH0.CFG5
#define CSIH0CFG6 CSIH0.CFG6
#define CSIH0CFG7 CSIH0.CFG7
#define CSIH0BRS0 CSIH0.BRS0
#define CSIH0BRS1 CSIH0.BRS1
#define CSIH0BRS2 CSIH0.BRS2
#define CSIH0BRS3 CSIH0.BRS3
#define PMMA0CTL PMMA0.CTL
#define PMMA0TCTL0 PMMA0.TCTL0
#define PMMA0TCTL1 PMMA0.TCTL1
#define PMMA0TCTL2 PMMA0.TCTL2
#define PMMA0TCTL3 PMMA0.TCTL3
#define PMMA0TCTL4 PMMA0.TCTL4
#define PMMA0TCTL5 PMMA0.TCTL5
#define PMMA0TCTL6 PMMA0.TCTL6
#define PMMA0TCTL7 PMMA0.TCTL7
#define PMMA0TTX0 PMMA0.TTX0
#define PMMA0TTX1 PMMA0.TTX1
#define PMMA0TTX2 PMMA0.TTX2
#define PMMA0TTX3 PMMA0.TTX3
#define PMMA0TTX4 PMMA0.TTX4
#define PMMA0TTX5 PMMA0.TTX5
#define PMMA0TTX6 PMMA0.TTX6
#define PMMA0TTX7 PMMA0.TTX7
#define PMMA0RX PMMA0.RX
#define PMMA0TCNT0 PMMA0.TCNT0
#define PMMA0TCNT1 PMMA0.TCNT1
#define PMMA0TCNT2 PMMA0.TCNT2
#define PMMA0TCNT3 PMMA0.TCNT3
#define PMMA0TCNT4 PMMA0.TCNT4
#define PMMA0TCNT5 PMMA0.TCNT5
#define PMMA0TCNT6 PMMA0.TCNT6
#define PMMA0TCNT7 PMMA0.TCNT7
#define PMMA0STR0 PMMA0.STR0
#define PMMA0STR1 PMMA0.STR1
#define PMMA0STC PMMA0.STC
#define CSIH2CTL0 CSIH2.CTL0.ui8
#define CSIH2CTL1 CSIH2.CTL1
#define CSIH2CTL2 CSIH2.CTL2
#define CSIH2MCTL1 CSIH2.MCTL1
#define CSIH2MCTL2 CSIH2.MCTL2
#define CSIH2TX0W CSIH2.TX0W
#define CSIH2TX0H CSIH2.TX0H
#define CSIH2RX0W CSIH2.RX0W
#define CSIH2RX0H CSIH2.RX0H
#define CSIH2MRWP0 CSIH2.MRWP0
#define CSIH2STR0 CSIH2.STR0
#define CSIH2STCR0 CSIH2.STCR0
#define CSIH2MCTL0 CSIH2.MCTL0
#define CSIH2CFG0 CSIH2.CFG0
#define CSIH2CFG1 CSIH2.CFG1
#define CSIH2CFG2 CSIH2.CFG2
#define CSIH2CFG3 CSIH2.CFG3
#define CSIH2CFG4 CSIH2.CFG4
#define CSIH2CFG5 CSIH2.CFG5
#define CSIH2CFG6 CSIH2.CFG6
#define CSIH2CFG7 CSIH2.CFG7
#define CSIH2BRS0 CSIH2.BRS0
#define CSIH2BRS1 CSIH2.BRS1
#define CSIH2BRS2 CSIH2.BRS2
#define CSIH2BRS3 CSIH2.BRS3
#define PMMA2CTL PMMA2.CTL
#define PMMA2TCTL0 PMMA2.TCTL0
#define PMMA2TCTL1 PMMA2.TCTL1
#define PMMA2TCTL2 PMMA2.TCTL2
#define PMMA2TCTL3 PMMA2.TCTL3
#define PMMA2TCTL4 PMMA2.TCTL4
#define PMMA2TCTL5 PMMA2.TCTL5
#define PMMA2TCTL6 PMMA2.TCTL6
#define PMMA2TCTL7 PMMA2.TCTL7
#define PMMA2TTX0 PMMA2.TTX0
#define PMMA2TTX1 PMMA2.TTX1
#define PMMA2TTX2 PMMA2.TTX2
#define PMMA2TTX3 PMMA2.TTX3
#define PMMA2TTX4 PMMA2.TTX4
#define PMMA2TTX5 PMMA2.TTX5
#define PMMA2TTX6 PMMA2.TTX6
#define PMMA2TTX7 PMMA2.TTX7
#define PMMA2RX PMMA2.RX
#define PMMA2TCNT0 PMMA2.TCNT0
#define PMMA2TCNT1 PMMA2.TCNT1
#define PMMA2TCNT2 PMMA2.TCNT2
#define PMMA2TCNT3 PMMA2.TCNT3
#define PMMA2TCNT4 PMMA2.TCNT4
#define PMMA2TCNT5 PMMA2.TCNT5
#define PMMA2TCNT6 PMMA2.TCNT6
#define PMMA2TCNT7 PMMA2.TCNT7
#define PMMA2STR0 PMMA2.STR0
#define PMMA2STR1 PMMA2.STR1
#define PMMA2STC PMMA2.STC
#define RLN30LWBR RLN30.LWBR
#define RLN30LBRP01 RLN30.LBRP01.ui16
#define RLN30LBRP0 RLN30.LBRP01.ui8[0]
#define RLN30LBRP1 RLN30.LBRP01.ui8[1]
#define RLN30LSTC RLN30.LSTC
#define RLN30LMD RLN30.LMD
#define RLN30LBFC RLN30.LBFC
#define RLN30LSC RLN30.LSC
#define RLN30LWUP RLN30.LWUP
#define RLN30LIE RLN30.LIE
#define RLN30LEDE RLN30.LEDE
#define RLN30LCUC RLN30.LCUC
#define RLN30LTRC RLN30.LTRC
#define RLN30LMST RLN30.LMST
#define RLN30LST RLN30.LST
#define RLN30LEST RLN30.LEST
#define RLN30LDFC RLN30.LDFC
#define RLN30LIDB RLN30.LIDB
#define RLN30LCBR RLN30.LCBR
#define RLN30LUDB0 RLN30.LUDB0
#define RLN30LDBR1 RLN30.LDBR1
#define RLN30LDBR2 RLN30.LDBR2
#define RLN30LDBR3 RLN30.LDBR3
#define RLN30LDBR4 RLN30.LDBR4
#define RLN30LDBR5 RLN30.LDBR5
#define RLN30LDBR6 RLN30.LDBR6
#define RLN30LDBR7 RLN30.LDBR7
#define RLN30LDBR8 RLN30.LDBR8
#define RLN30LUOER RLN30.LUOER
#define RLN30LUOR1 RLN30.LUOR1
#define RLN30LUTDR RLN30.LUTDR.ui16
#define RLN30LUTDRL RLN30.LUTDR.ui8[0]
#define RLN30LUTDRH RLN30.LUTDR.ui8[1]
#define RLN30LURDR RLN30.LURDR.ui16
#define RLN30LURDRL RLN30.LURDR.ui8[0]
#define RLN30LURDRH RLN30.LURDR.ui8[1]
#define RLN30LUWTDR RLN30.LUWTDR.ui16
#define RLN30LUWTDRL RLN30.LUWTDR.ui8[0]
#define RLN30LUWTDRH RLN30.LUWTDR.ui8[1]
#define STM0CKSEL STM0.CKSEL.ui32
#define STM0CKSELLL STM0.CKSEL.ui8[0]
#define STM0TS STM0.TS.ui32
#define STM0TSLL STM0.TS.ui8[0]
#define STM0TT STM0.TT.ui32
#define STM0TTLL STM0.TT.ui8[0]
#define STM0CSTR STM0.CSTR.ui32
#define STM0CSTRLL STM0.CSTR.ui8[0]
#define STM0STR STM0.STR
#define STM0STC STM0.STC
#define STM0IS STM0.IS.ui32
#define STM0ISLL STM0.IS.ui8[0]
#define STM0ISLH STM0.IS.ui8[1]
#define STM0RM STM0.RM.ui32
#define STM0RMLL STM0.RM.ui8[0]
#define STM0CNT0L STM0.CNT0L
#define STM0CNT0H STM0.CNT0H
#define STM0CMP0AL STM0.CMP0AL
#define STM0CMP0AH STM0.CMP0AH
#define STM0CMP0BL STM0.CMP0BL
#define STM0CMP0BH STM0.CMP0BH
#define STM0CMP0CL STM0.CMP0CL
#define STM0CMP0CH STM0.CMP0CH
#define STM0CMP0DL STM0.CMP0DL
#define STM0CMP0DH STM0.CMP0DH
#define STM0CNT1 STM0.CNT1
#define STM0CMP1A STM0.CMP1A
#define STM0CMP1B STM0.CMP1B
#define STM0CMP1C STM0.CMP1C
#define STM0CMP1D STM0.CMP1D
#define STM0CNT2 STM0.CNT2
#define STM0CMP2A STM0.CMP2A
#define STM0CMP2B STM0.CMP2B
#define STM0CMP2C STM0.CMP2C
#define STM0CMP2D STM0.CMP2D
#define STM0CNT3 STM0.CNT3
#define STM0CMP3A STM0.CMP3A
#define STM0CMP3B STM0.CMP3B
#define STM0CMP3C STM0.CMP3C
#define STM0CMP3D STM0.CMP3D
#define FSGD2APROT00 FSGD2A.PROT00.ui32
#define FSGD2APROT00L FSGD2A.PROT00.ui16[0]
#define FSGD2APROT00LL FSGD2A.PROT00.ui8[0]
#define FSGD2APROT00LH FSGD2A.PROT00.ui8[1]
#define FSGD2APROT00H FSGD2A.PROT00.ui16[1]
#define FSGD2APROT00HL FSGD2A.PROT00.ui8[2]
#define FSGD2APROT00HH FSGD2A.PROT00.ui8[3]
#define FSGD2ASPID00 FSGD2A.SPID00.ui32
#define FSGD2ASPID00L FSGD2A.SPID00.ui16[0]
#define FSGD2ASPID00LL FSGD2A.SPID00.ui8[0]
#define FSGD2ASPID00LH FSGD2A.SPID00.ui8[1]
#define FSGD2ASPID00H FSGD2A.SPID00.ui16[1]
#define FSGD2ASPID00HL FSGD2A.SPID00.ui8[2]
#define FSGD2ASPID00HH FSGD2A.SPID00.ui8[3]
#define FSGD2APROT01 FSGD2A.PROT01.ui32
#define FSGD2APROT01L FSGD2A.PROT01.ui16[0]
#define FSGD2APROT01LL FSGD2A.PROT01.ui8[0]
#define FSGD2APROT01LH FSGD2A.PROT01.ui8[1]
#define FSGD2APROT01H FSGD2A.PROT01.ui16[1]
#define FSGD2APROT01HL FSGD2A.PROT01.ui8[2]
#define FSGD2APROT01HH FSGD2A.PROT01.ui8[3]
#define FSGD2ASPID01 FSGD2A.SPID01.ui32
#define FSGD2ASPID01L FSGD2A.SPID01.ui16[0]
#define FSGD2ASPID01LL FSGD2A.SPID01.ui8[0]
#define FSGD2ASPID01LH FSGD2A.SPID01.ui8[1]
#define FSGD2ASPID01H FSGD2A.SPID01.ui16[1]
#define FSGD2ASPID01HL FSGD2A.SPID01.ui8[2]
#define FSGD2ASPID01HH FSGD2A.SPID01.ui8[3]
#define FSGD2APROT02 FSGD2A.PROT02.ui32
#define FSGD2APROT02L FSGD2A.PROT02.ui16[0]
#define FSGD2APROT02LL FSGD2A.PROT02.ui8[0]
#define FSGD2APROT02LH FSGD2A.PROT02.ui8[1]
#define FSGD2APROT02H FSGD2A.PROT02.ui16[1]
#define FSGD2APROT02HL FSGD2A.PROT02.ui8[2]
#define FSGD2APROT02HH FSGD2A.PROT02.ui8[3]
#define FSGD2ASPID02 FSGD2A.SPID02.ui32
#define FSGD2ASPID02L FSGD2A.SPID02.ui16[0]
#define FSGD2ASPID02LL FSGD2A.SPID02.ui8[0]
#define FSGD2ASPID02LH FSGD2A.SPID02.ui8[1]
#define FSGD2ASPID02H FSGD2A.SPID02.ui16[1]
#define FSGD2ASPID02HL FSGD2A.SPID02.ui8[2]
#define FSGD2ASPID02HH FSGD2A.SPID02.ui8[3]
#define FSGD2APROT03 FSGD2A.PROT03.ui32
#define FSGD2APROT03L FSGD2A.PROT03.ui16[0]
#define FSGD2APROT03LL FSGD2A.PROT03.ui8[0]
#define FSGD2APROT03LH FSGD2A.PROT03.ui8[1]
#define FSGD2APROT03H FSGD2A.PROT03.ui16[1]
#define FSGD2APROT03HL FSGD2A.PROT03.ui8[2]
#define FSGD2APROT03HH FSGD2A.PROT03.ui8[3]
#define FSGD2ASPID03 FSGD2A.SPID03.ui32
#define FSGD2ASPID03L FSGD2A.SPID03.ui16[0]
#define FSGD2ASPID03LL FSGD2A.SPID03.ui8[0]
#define FSGD2ASPID03LH FSGD2A.SPID03.ui8[1]
#define FSGD2ASPID03H FSGD2A.SPID03.ui16[1]
#define FSGD2ASPID03HL FSGD2A.SPID03.ui8[2]
#define FSGD2ASPID03HH FSGD2A.SPID03.ui8[3]
#define FSGD2APROT04 FSGD2A.PROT04.ui32
#define FSGD2APROT04L FSGD2A.PROT04.ui16[0]
#define FSGD2APROT04LL FSGD2A.PROT04.ui8[0]
#define FSGD2APROT04LH FSGD2A.PROT04.ui8[1]
#define FSGD2APROT04H FSGD2A.PROT04.ui16[1]
#define FSGD2APROT04HL FSGD2A.PROT04.ui8[2]
#define FSGD2APROT04HH FSGD2A.PROT04.ui8[3]
#define FSGD2ASPID04 FSGD2A.SPID04.ui32
#define FSGD2ASPID04L FSGD2A.SPID04.ui16[0]
#define FSGD2ASPID04LL FSGD2A.SPID04.ui8[0]
#define FSGD2ASPID04LH FSGD2A.SPID04.ui8[1]
#define FSGD2ASPID04H FSGD2A.SPID04.ui16[1]
#define FSGD2ASPID04HL FSGD2A.SPID04.ui8[2]
#define FSGD2ASPID04HH FSGD2A.SPID04.ui8[3]
#define FSGD2APROT05 FSGD2A.PROT05.ui32
#define FSGD2APROT05L FSGD2A.PROT05.ui16[0]
#define FSGD2APROT05LL FSGD2A.PROT05.ui8[0]
#define FSGD2APROT05LH FSGD2A.PROT05.ui8[1]
#define FSGD2APROT05H FSGD2A.PROT05.ui16[1]
#define FSGD2APROT05HL FSGD2A.PROT05.ui8[2]
#define FSGD2APROT05HH FSGD2A.PROT05.ui8[3]
#define FSGD2ASPID05 FSGD2A.SPID05.ui32
#define FSGD2ASPID05L FSGD2A.SPID05.ui16[0]
#define FSGD2ASPID05LL FSGD2A.SPID05.ui8[0]
#define FSGD2ASPID05LH FSGD2A.SPID05.ui8[1]
#define FSGD2ASPID05H FSGD2A.SPID05.ui16[1]
#define FSGD2ASPID05HL FSGD2A.SPID05.ui8[2]
#define FSGD2ASPID05HH FSGD2A.SPID05.ui8[3]
#define FSGD2APROT06 FSGD2A.PROT06.ui32
#define FSGD2APROT06L FSGD2A.PROT06.ui16[0]
#define FSGD2APROT06LL FSGD2A.PROT06.ui8[0]
#define FSGD2APROT06LH FSGD2A.PROT06.ui8[1]
#define FSGD2APROT06H FSGD2A.PROT06.ui16[1]
#define FSGD2APROT06HL FSGD2A.PROT06.ui8[2]
#define FSGD2APROT06HH FSGD2A.PROT06.ui8[3]
#define FSGD2ASPID06 FSGD2A.SPID06.ui32
#define FSGD2ASPID06L FSGD2A.SPID06.ui16[0]
#define FSGD2ASPID06LL FSGD2A.SPID06.ui8[0]
#define FSGD2ASPID06LH FSGD2A.SPID06.ui8[1]
#define FSGD2ASPID06H FSGD2A.SPID06.ui16[1]
#define FSGD2ASPID06HL FSGD2A.SPID06.ui8[2]
#define FSGD2ASPID06HH FSGD2A.SPID06.ui8[3]
#define FSGD2APROT07 FSGD2A.PROT07.ui32
#define FSGD2APROT07L FSGD2A.PROT07.ui16[0]
#define FSGD2APROT07LL FSGD2A.PROT07.ui8[0]
#define FSGD2APROT07LH FSGD2A.PROT07.ui8[1]
#define FSGD2APROT07H FSGD2A.PROT07.ui16[1]
#define FSGD2APROT07HL FSGD2A.PROT07.ui8[2]
#define FSGD2APROT07HH FSGD2A.PROT07.ui8[3]
#define FSGD2ASPID07 FSGD2A.SPID07.ui32
#define FSGD2ASPID07L FSGD2A.SPID07.ui16[0]
#define FSGD2ASPID07LL FSGD2A.SPID07.ui8[0]
#define FSGD2ASPID07LH FSGD2A.SPID07.ui8[1]
#define FSGD2ASPID07H FSGD2A.SPID07.ui16[1]
#define FSGD2ASPID07HL FSGD2A.SPID07.ui8[2]
#define FSGD2ASPID07HH FSGD2A.SPID07.ui8[3]
#define FSGD2APROT10 FSGD2A.PROT10.ui32
#define FSGD2APROT10L FSGD2A.PROT10.ui16[0]
#define FSGD2APROT10LL FSGD2A.PROT10.ui8[0]
#define FSGD2APROT10LH FSGD2A.PROT10.ui8[1]
#define FSGD2APROT10H FSGD2A.PROT10.ui16[1]
#define FSGD2APROT10HL FSGD2A.PROT10.ui8[2]
#define FSGD2APROT10HH FSGD2A.PROT10.ui8[3]
#define FSGD2ASPID10 FSGD2A.SPID10.ui32
#define FSGD2ASPID10L FSGD2A.SPID10.ui16[0]
#define FSGD2ASPID10LL FSGD2A.SPID10.ui8[0]
#define FSGD2ASPID10LH FSGD2A.SPID10.ui8[1]
#define FSGD2ASPID10H FSGD2A.SPID10.ui16[1]
#define FSGD2ASPID10HL FSGD2A.SPID10.ui8[2]
#define FSGD2ASPID10HH FSGD2A.SPID10.ui8[3]
#define FSGD2APROT11 FSGD2A.PROT11.ui32
#define FSGD2APROT11L FSGD2A.PROT11.ui16[0]
#define FSGD2APROT11LL FSGD2A.PROT11.ui8[0]
#define FSGD2APROT11LH FSGD2A.PROT11.ui8[1]
#define FSGD2APROT11H FSGD2A.PROT11.ui16[1]
#define FSGD2APROT11HL FSGD2A.PROT11.ui8[2]
#define FSGD2APROT11HH FSGD2A.PROT11.ui8[3]
#define FSGD2ASPID11 FSGD2A.SPID11.ui32
#define FSGD2ASPID11L FSGD2A.SPID11.ui16[0]
#define FSGD2ASPID11LL FSGD2A.SPID11.ui8[0]
#define FSGD2ASPID11LH FSGD2A.SPID11.ui8[1]
#define FSGD2ASPID11H FSGD2A.SPID11.ui16[1]
#define FSGD2ASPID11HL FSGD2A.SPID11.ui8[2]
#define FSGD2ASPID11HH FSGD2A.SPID11.ui8[3]
#define ERRSLV2CTL ERRSLV2.CTL
#define ERRSLV2STAT ERRSLV2.STAT
#define ERRSLV2TYPE ERRSLV2.TYPE
#define ERRSLV2AICTL ERRSLV2AI.CTL
#define ERRSLV2AISTAT ERRSLV2AI.STAT
#define ERRSLV2AITYPE ERRSLV2AI.TYPE
#define GTM0GTMREV GTM0.GTMREV
#define GTM0GTMRST GTM0.GTMRST
#define GTM0GTMCTRL GTM0.GTMCTRL
#define GTM0GTMAEIADDRXPT GTM0.GTMAEIADDRXPT
#define GTM0GTMIRQNOTIFY GTM0.GTMIRQNOTIFY
#define GTM0GTMIRQEN GTM0.GTMIRQEN
#define GTM0GTMIRQFORCINT GTM0.GTMIRQFORCINT
#define GTM0GTMIRQMODE GTM0.GTMIRQMODE
#define GTM0GTMEIRQEN GTM0.GTMEIRQEN
#define GTM0GTMHWCONF GTM0.GTMHWCONF
#define GTM0GTMBRIDGEMODE GTM0.GTMBRIDGEMODE
#define GTM0GTMBRIDGEPTR1 GTM0.GTMBRIDGEPTR1
#define GTM0GTMBRIDGEPTR2 GTM0.GTMBRIDGEPTR2
#define GTM0GTMTIM0AUXINSRC GTM0.GTMTIM0AUXINSRC
#define GTM0GTMTIM1AUXINSRC GTM0.GTMTIM1AUXINSRC
#define GTM0GTMEXTCAPEN0 GTM0.GTMEXTCAPEN0
#define GTM0GTMATOM0OUT GTM0.GTMATOM0OUT
#define GTM0TBUCHEN GTM0.TBUCHEN
#define GTM0TBU0CTRL GTM0.TBU0CTRL
#define GTM0TBU0BASE GTM0.TBU0BASE
#define GTM0TBU1CTRL GTM0.TBU1CTRL
#define GTM0TBU1BASE GTM0.TBU1BASE
#define GTM0MONSTATUS GTM0.MONSTATUS
#define GTM0MONACTIVITY0 GTM0.MONACTIVITY0
#define GTM0MONACTIVITYMCS0 GTM0.MONACTIVITYMCS0
#define GTM0CMPEN GTM0.CMPEN
#define GTM0CMPIRQNOTIFY GTM0.CMPIRQNOTIFY
#define GTM0CMPIRQEN GTM0.CMPIRQEN
#define GTM0CMPIRQFORCINT GTM0.CMPIRQFORCINT
#define GTM0CMPIRQMODE GTM0.CMPIRQMODE
#define GTM0CMPEIRQEN GTM0.CMPEIRQEN
#define GTM0ARUACCESS GTM0.ARUACCESS
#define GTM0ARUDATAH GTM0.ARUDATAH
#define GTM0ARUDATAL GTM0.ARUDATAL
#define GTM0ARUDBGACCESS0 GTM0.ARUDBGACCESS0
#define GTM0ARUDBGDATA0H GTM0.ARUDBGDATA0H
#define GTM0ARUDBGDATA0L GTM0.ARUDBGDATA0L
#define GTM0ARUDBGACCESS1 GTM0.ARUDBGACCESS1
#define GTM0ARUDBGDATA1H GTM0.ARUDBGDATA1H
#define GTM0ARUDBGDATA1L GTM0.ARUDBGDATA1L
#define GTM0ARUIRQNOTIFY GTM0.ARUIRQNOTIFY
#define GTM0ARUIRQEN GTM0.ARUIRQEN
#define GTM0ARUIRQFORCINT GTM0.ARUIRQFORCINT
#define GTM0ARUIRQMODE GTM0.ARUIRQMODE
#define GTM0ARUCADDREND GTM0.ARUCADDREND
#define GTM0CMUCLKEN GTM0.CMUCLKEN
#define GTM0CMUGCLKNUM GTM0.CMUGCLKNUM
#define GTM0CMUGCLKDEN GTM0.CMUGCLKDEN
#define GTM0CMUCLK0CTRL GTM0.CMUCLK0CTRL
#define GTM0CMUCLK1CTRL GTM0.CMUCLK1CTRL
#define GTM0CMUCLK2CTRL GTM0.CMUCLK2CTRL
#define GTM0CMUCLK3CTRL GTM0.CMUCLK3CTRL
#define GTM0CMUCLK4CTRL GTM0.CMUCLK4CTRL
#define GTM0CMUCLK5CTRL GTM0.CMUCLK5CTRL
#define GTM0CMUCLK6CTRL GTM0.CMUCLK6CTRL
#define GTM0CMUCLK7CTRL GTM0.CMUCLK7CTRL
#define GTM0CMUGLBCTRL GTM0.CMUGLBCTRL
#define GTM0ICMIRQG0 GTM0.ICMIRQG0
#define GTM0ICMIRQG2 GTM0.ICMIRQG2
#define GTM0ICMIRQG4 GTM0.ICMIRQG4
#define GTM0ICMIRQG9 GTM0.ICMIRQG9
#define GTM0ICMIRQGMEI GTM0.ICMIRQGMEI
#define GTM0ICMIRQGCEI1 GTM0.ICMIRQGCEI1
#define GTM0ICMIRQGCEI3 GTM0.ICMIRQGCEI3
#define GTM0ICMIRQGMCS0CI GTM0.ICMIRQGMCS0CI
#define GTM0ICMIRQGMCS0CEI GTM0.ICMIRQGMCS0CEI
#define GTM0TIM00GPR0 GTM0.TIM00GPR0
#define GTM0TIM00GPR1 GTM0.TIM00GPR1
#define GTM0TIM00CNT GTM0.TIM00CNT
#define GTM0TIM00ECNT GTM0.TIM00ECNT
#define GTM0TIM00CNTS GTM0.TIM00CNTS
#define GTM0TIM00TDUC GTM0.TIM00TDUC
#define GTM0TIM00TDUV GTM0.TIM00TDUV
#define GTM0TIM00FLTRE GTM0.TIM00FLTRE
#define GTM0TIM00FLTFE GTM0.TIM00FLTFE
#define GTM0TIM00CTRL GTM0.TIM00CTRL
#define GTM0TIM00ECTRL GTM0.TIM00ECTRL
#define GTM0TIM00IRQNOTIFY GTM0.TIM00IRQNOTIFY
#define GTM0TIM00IRQEN GTM0.TIM00IRQEN
#define GTM0TIM00IRQFORCINT GTM0.TIM00IRQFORCINT
#define GTM0TIM00IRQMODE GTM0.TIM00IRQMODE
#define GTM0TIM00EIRQEN GTM0.TIM00EIRQEN
#define GTM0TIM0INPVAL GTM0.TIM0INPVAL
#define GTM0TIM0INSRC GTM0.TIM0INSRC
#define GTM0TIM0RST GTM0.TIM0RST
#define GTM0TIM01GPR0 GTM0.TIM01GPR0
#define GTM0TIM01GPR1 GTM0.TIM01GPR1
#define GTM0TIM01CNT GTM0.TIM01CNT
#define GTM0TIM01ECNT GTM0.TIM01ECNT
#define GTM0TIM01CNTS GTM0.TIM01CNTS
#define GTM0TIM01TDUC GTM0.TIM01TDUC
#define GTM0TIM01TDUV GTM0.TIM01TDUV
#define GTM0TIM01FLTRE GTM0.TIM01FLTRE
#define GTM0TIM01FLTFE GTM0.TIM01FLTFE
#define GTM0TIM01CTRL GTM0.TIM01CTRL
#define GTM0TIM01ECTRL GTM0.TIM01ECTRL
#define GTM0TIM01IRQNOTIFY GTM0.TIM01IRQNOTIFY
#define GTM0TIM01IRQEN GTM0.TIM01IRQEN
#define GTM0TIM01IRQFORCINT GTM0.TIM01IRQFORCINT
#define GTM0TIM01IRQMODE GTM0.TIM01IRQMODE
#define GTM0TIM01EIRQEN GTM0.TIM01EIRQEN
#define GTM0TIM02GPR0 GTM0.TIM02GPR0
#define GTM0TIM02GPR1 GTM0.TIM02GPR1
#define GTM0TIM02CNT GTM0.TIM02CNT
#define GTM0TIM02ECNT GTM0.TIM02ECNT
#define GTM0TIM02CNTS GTM0.TIM02CNTS
#define GTM0TIM02TDUC GTM0.TIM02TDUC
#define GTM0TIM02TDUV GTM0.TIM02TDUV
#define GTM0TIM02FLTRE GTM0.TIM02FLTRE
#define GTM0TIM02FLTFE GTM0.TIM02FLTFE
#define GTM0TIM02CTRL GTM0.TIM02CTRL
#define GTM0TIM02ECTRL GTM0.TIM02ECTRL
#define GTM0TIM02IRQNOTIFY GTM0.TIM02IRQNOTIFY
#define GTM0TIM02IRQEN GTM0.TIM02IRQEN
#define GTM0TIM02IRQFORCINT GTM0.TIM02IRQFORCINT
#define GTM0TIM02IRQMODE GTM0.TIM02IRQMODE
#define GTM0TIM02EIRQEN GTM0.TIM02EIRQEN
#define GTM0TIM03GPR0 GTM0.TIM03GPR0
#define GTM0TIM03GPR1 GTM0.TIM03GPR1
#define GTM0TIM03CNT GTM0.TIM03CNT
#define GTM0TIM03ECNT GTM0.TIM03ECNT
#define GTM0TIM03CNTS GTM0.TIM03CNTS
#define GTM0TIM03TDUC GTM0.TIM03TDUC
#define GTM0TIM03TDUV GTM0.TIM03TDUV
#define GTM0TIM03FLTRE GTM0.TIM03FLTRE
#define GTM0TIM03FLTFE GTM0.TIM03FLTFE
#define GTM0TIM03CTRL GTM0.TIM03CTRL
#define GTM0TIM03ECTRL GTM0.TIM03ECTRL
#define GTM0TIM03IRQNOTIFY GTM0.TIM03IRQNOTIFY
#define GTM0TIM03IRQEN GTM0.TIM03IRQEN
#define GTM0TIM03IRQFORCINT GTM0.TIM03IRQFORCINT
#define GTM0TIM03IRQMODE GTM0.TIM03IRQMODE
#define GTM0TIM03EIRQEN GTM0.TIM03EIRQEN
#define GTM0TIM04GPR0 GTM0.TIM04GPR0
#define GTM0TIM04GPR1 GTM0.TIM04GPR1
#define GTM0TIM04CNT GTM0.TIM04CNT
#define GTM0TIM04ECNT GTM0.TIM04ECNT
#define GTM0TIM04CNTS GTM0.TIM04CNTS
#define GTM0TIM04TDUC GTM0.TIM04TDUC
#define GTM0TIM04TDUV GTM0.TIM04TDUV
#define GTM0TIM04FLTRE GTM0.TIM04FLTRE
#define GTM0TIM04FLTFE GTM0.TIM04FLTFE
#define GTM0TIM04CTRL GTM0.TIM04CTRL
#define GTM0TIM04ECTRL GTM0.TIM04ECTRL
#define GTM0TIM04IRQNOTIFY GTM0.TIM04IRQNOTIFY
#define GTM0TIM04IRQEN GTM0.TIM04IRQEN
#define GTM0TIM04IRQFORCINT GTM0.TIM04IRQFORCINT
#define GTM0TIM04IRQMODE GTM0.TIM04IRQMODE
#define GTM0TIM04EIRQEN GTM0.TIM04EIRQEN
#define GTM0TIM05GPR0 GTM0.TIM05GPR0
#define GTM0TIM05GPR1 GTM0.TIM05GPR1
#define GTM0TIM05CNT GTM0.TIM05CNT
#define GTM0TIM05ECNT GTM0.TIM05ECNT
#define GTM0TIM05CNTS GTM0.TIM05CNTS
#define GTM0TIM05TDUC GTM0.TIM05TDUC
#define GTM0TIM05TDUV GTM0.TIM05TDUV
#define GTM0TIM05FLTRE GTM0.TIM05FLTRE
#define GTM0TIM05FLTFE GTM0.TIM05FLTFE
#define GTM0TIM05CTRL GTM0.TIM05CTRL
#define GTM0TIM05ECTRL GTM0.TIM05ECTRL
#define GTM0TIM05IRQNOTIFY GTM0.TIM05IRQNOTIFY
#define GTM0TIM05IRQEN GTM0.TIM05IRQEN
#define GTM0TIM05IRQFORCINT GTM0.TIM05IRQFORCINT
#define GTM0TIM05IRQMODE GTM0.TIM05IRQMODE
#define GTM0TIM05EIRQEN GTM0.TIM05EIRQEN
#define GTM0TIM06GPR0 GTM0.TIM06GPR0
#define GTM0TIM06GPR1 GTM0.TIM06GPR1
#define GTM0TIM06CNT GTM0.TIM06CNT
#define GTM0TIM06ECNT GTM0.TIM06ECNT
#define GTM0TIM06CNTS GTM0.TIM06CNTS
#define GTM0TIM06TDUC GTM0.TIM06TDUC
#define GTM0TIM06TDUV GTM0.TIM06TDUV
#define GTM0TIM06FLTRE GTM0.TIM06FLTRE
#define GTM0TIM06FLTFE GTM0.TIM06FLTFE
#define GTM0TIM06CTRL GTM0.TIM06CTRL
#define GTM0TIM06ECTRL GTM0.TIM06ECTRL
#define GTM0TIM06IRQNOTIFY GTM0.TIM06IRQNOTIFY
#define GTM0TIM06IRQEN GTM0.TIM06IRQEN
#define GTM0TIM06IRQFORCINT GTM0.TIM06IRQFORCINT
#define GTM0TIM06IRQMODE GTM0.TIM06IRQMODE
#define GTM0TIM06EIRQEN GTM0.TIM06EIRQEN
#define GTM0TIM07GPR0 GTM0.TIM07GPR0
#define GTM0TIM07GPR1 GTM0.TIM07GPR1
#define GTM0TIM07CNT GTM0.TIM07CNT
#define GTM0TIM07ECNT GTM0.TIM07ECNT
#define GTM0TIM07CNTS GTM0.TIM07CNTS
#define GTM0TIM07TDUC GTM0.TIM07TDUC
#define GTM0TIM07TDUV GTM0.TIM07TDUV
#define GTM0TIM07FLTRE GTM0.TIM07FLTRE
#define GTM0TIM07FLTFE GTM0.TIM07FLTFE
#define GTM0TIM07CTRL GTM0.TIM07CTRL
#define GTM0TIM07ECTRL GTM0.TIM07ECTRL
#define GTM0TIM07IRQNOTIFY GTM0.TIM07IRQNOTIFY
#define GTM0TIM07IRQEN GTM0.TIM07IRQEN
#define GTM0TIM07IRQFORCINT GTM0.TIM07IRQFORCINT
#define GTM0TIM07IRQMODE GTM0.TIM07IRQMODE
#define GTM0TIM07EIRQEN GTM0.TIM07EIRQEN
#define GTM0TIM10GPR0 GTM0.TIM10GPR0
#define GTM0TIM10GPR1 GTM0.TIM10GPR1
#define GTM0TIM10CNT GTM0.TIM10CNT
#define GTM0TIM10ECNT GTM0.TIM10ECNT
#define GTM0TIM10CNTS GTM0.TIM10CNTS
#define GTM0TIM10TDUC GTM0.TIM10TDUC
#define GTM0TIM10TDUV GTM0.TIM10TDUV
#define GTM0TIM10FLTRE GTM0.TIM10FLTRE
#define GTM0TIM10FLTFE GTM0.TIM10FLTFE
#define GTM0TIM10CTRL GTM0.TIM10CTRL
#define GTM0TIM10ECTRL GTM0.TIM10ECTRL
#define GTM0TIM10IRQNOTIFY GTM0.TIM10IRQNOTIFY
#define GTM0TIM10IRQEN GTM0.TIM10IRQEN
#define GTM0TIM10IRQFORCINT GTM0.TIM10IRQFORCINT
#define GTM0TIM10IRQMODE GTM0.TIM10IRQMODE
#define GTM0TIM10EIRQEN GTM0.TIM10EIRQEN
#define GTM0TIM1INPVAL GTM0.TIM1INPVAL
#define GTM0TIM1INSRC GTM0.TIM1INSRC
#define GTM0TIM1RST GTM0.TIM1RST
#define GTM0TIM11GPR0 GTM0.TIM11GPR0
#define GTM0TIM11GPR1 GTM0.TIM11GPR1
#define GTM0TIM11CNT GTM0.TIM11CNT
#define GTM0TIM11ECNT GTM0.TIM11ECNT
#define GTM0TIM11CNTS GTM0.TIM11CNTS
#define GTM0TIM11TDUC GTM0.TIM11TDUC
#define GTM0TIM11TDUV GTM0.TIM11TDUV
#define GTM0TIM11FLTRE GTM0.TIM11FLTRE
#define GTM0TIM11FLTFE GTM0.TIM11FLTFE
#define GTM0TIM11CTRL GTM0.TIM11CTRL
#define GTM0TIM11ECTRL GTM0.TIM11ECTRL
#define GTM0TIM11IRQNOTIFY GTM0.TIM11IRQNOTIFY
#define GTM0TIM11IRQEN GTM0.TIM11IRQEN
#define GTM0TIM11IRQFORCINT GTM0.TIM11IRQFORCINT
#define GTM0TIM11IRQMODE GTM0.TIM11IRQMODE
#define GTM0TIM11EIRQEN GTM0.TIM11EIRQEN
#define GTM0TIM12GPR0 GTM0.TIM12GPR0
#define GTM0TIM12GPR1 GTM0.TIM12GPR1
#define GTM0TIM12CNT GTM0.TIM12CNT
#define GTM0TIM12ECNT GTM0.TIM12ECNT
#define GTM0TIM12CNTS GTM0.TIM12CNTS
#define GTM0TIM12TDUC GTM0.TIM12TDUC
#define GTM0TIM12TDUV GTM0.TIM12TDUV
#define GTM0TIM12FLTRE GTM0.TIM12FLTRE
#define GTM0TIM12FLTFE GTM0.TIM12FLTFE
#define GTM0TIM12CTRL GTM0.TIM12CTRL
#define GTM0TIM12ECTRL GTM0.TIM12ECTRL
#define GTM0TIM12IRQNOTIFY GTM0.TIM12IRQNOTIFY
#define GTM0TIM12IRQEN GTM0.TIM12IRQEN
#define GTM0TIM12IRQFORCINT GTM0.TIM12IRQFORCINT
#define GTM0TIM12IRQMODE GTM0.TIM12IRQMODE
#define GTM0TIM12EIRQEN GTM0.TIM12EIRQEN
#define GTM0TIM13GPR0 GTM0.TIM13GPR0
#define GTM0TIM13GPR1 GTM0.TIM13GPR1
#define GTM0TIM13CNT GTM0.TIM13CNT
#define GTM0TIM13ECNT GTM0.TIM13ECNT
#define GTM0TIM13CNTS GTM0.TIM13CNTS
#define GTM0TIM13TDUC GTM0.TIM13TDUC
#define GTM0TIM13TDUV GTM0.TIM13TDUV
#define GTM0TIM13FLTRE GTM0.TIM13FLTRE
#define GTM0TIM13FLTFE GTM0.TIM13FLTFE
#define GTM0TIM13CTRL GTM0.TIM13CTRL
#define GTM0TIM13ECTRL GTM0.TIM13ECTRL
#define GTM0TIM13IRQNOTIFY GTM0.TIM13IRQNOTIFY
#define GTM0TIM13IRQEN GTM0.TIM13IRQEN
#define GTM0TIM13IRQFORCINT GTM0.TIM13IRQFORCINT
#define GTM0TIM13IRQMODE GTM0.TIM13IRQMODE
#define GTM0TIM13EIRQEN GTM0.TIM13EIRQEN
#define GTM0TIM14GPR0 GTM0.TIM14GPR0
#define GTM0TIM14GPR1 GTM0.TIM14GPR1
#define GTM0TIM14CNT GTM0.TIM14CNT
#define GTM0TIM14ECNT GTM0.TIM14ECNT
#define GTM0TIM14CNTS GTM0.TIM14CNTS
#define GTM0TIM14TDUC GTM0.TIM14TDUC
#define GTM0TIM14TDUV GTM0.TIM14TDUV
#define GTM0TIM14FLTRE GTM0.TIM14FLTRE
#define GTM0TIM14FLTFE GTM0.TIM14FLTFE
#define GTM0TIM14CTRL GTM0.TIM14CTRL
#define GTM0TIM14ECTRL GTM0.TIM14ECTRL
#define GTM0TIM14IRQNOTIFY GTM0.TIM14IRQNOTIFY
#define GTM0TIM14IRQEN GTM0.TIM14IRQEN
#define GTM0TIM14IRQFORCINT GTM0.TIM14IRQFORCINT
#define GTM0TIM14IRQMODE GTM0.TIM14IRQMODE
#define GTM0TIM14EIRQEN GTM0.TIM14EIRQEN
#define GTM0TIM15GPR0 GTM0.TIM15GPR0
#define GTM0TIM15GPR1 GTM0.TIM15GPR1
#define GTM0TIM15CNT GTM0.TIM15CNT
#define GTM0TIM15ECNT GTM0.TIM15ECNT
#define GTM0TIM15CNTS GTM0.TIM15CNTS
#define GTM0TIM15TDUC GTM0.TIM15TDUC
#define GTM0TIM15TDUV GTM0.TIM15TDUV
#define GTM0TIM15FLTRE GTM0.TIM15FLTRE
#define GTM0TIM15FLTFE GTM0.TIM15FLTFE
#define GTM0TIM15CTRL GTM0.TIM15CTRL
#define GTM0TIM15ECTRL GTM0.TIM15ECTRL
#define GTM0TIM15IRQNOTIFY GTM0.TIM15IRQNOTIFY
#define GTM0TIM15IRQEN GTM0.TIM15IRQEN
#define GTM0TIM15IRQFORCINT GTM0.TIM15IRQFORCINT
#define GTM0TIM15IRQMODE GTM0.TIM15IRQMODE
#define GTM0TIM15EIRQEN GTM0.TIM15EIRQEN
#define GTM0TIM16GPR0 GTM0.TIM16GPR0
#define GTM0TIM16GPR1 GTM0.TIM16GPR1
#define GTM0TIM16CNT GTM0.TIM16CNT
#define GTM0TIM16ECNT GTM0.TIM16ECNT
#define GTM0TIM16CNTS GTM0.TIM16CNTS
#define GTM0TIM16TDUC GTM0.TIM16TDUC
#define GTM0TIM16TDUV GTM0.TIM16TDUV
#define GTM0TIM16FLTRE GTM0.TIM16FLTRE
#define GTM0TIM16FLTFE GTM0.TIM16FLTFE
#define GTM0TIM16CTRL GTM0.TIM16CTRL
#define GTM0TIM16ECTRL GTM0.TIM16ECTRL
#define GTM0TIM16IRQNOTIFY GTM0.TIM16IRQNOTIFY
#define GTM0TIM16IRQEN GTM0.TIM16IRQEN
#define GTM0TIM16IRQFORCINT GTM0.TIM16IRQFORCINT
#define GTM0TIM16IRQMODE GTM0.TIM16IRQMODE
#define GTM0TIM16EIRQEN GTM0.TIM16EIRQEN
#define GTM0TIM17GPR0 GTM0.TIM17GPR0
#define GTM0TIM17GPR1 GTM0.TIM17GPR1
#define GTM0TIM17CNT GTM0.TIM17CNT
#define GTM0TIM17ECNT GTM0.TIM17ECNT
#define GTM0TIM17CNTS GTM0.TIM17CNTS
#define GTM0TIM17TDUC GTM0.TIM17TDUC
#define GTM0TIM17TDUV GTM0.TIM17TDUV
#define GTM0TIM17FLTRE GTM0.TIM17FLTRE
#define GTM0TIM17FLTFE GTM0.TIM17FLTFE
#define GTM0TIM17CTRL GTM0.TIM17CTRL
#define GTM0TIM17ECTRL GTM0.TIM17ECTRL
#define GTM0TIM17IRQNOTIFY GTM0.TIM17IRQNOTIFY
#define GTM0TIM17IRQEN GTM0.TIM17IRQEN
#define GTM0TIM17IRQFORCINT GTM0.TIM17IRQFORCINT
#define GTM0TIM17IRQMODE GTM0.TIM17IRQMODE
#define GTM0TIM17EIRQEN GTM0.TIM17EIRQEN
#define GTM0ATOM00RDADDR GTM0.ATOM00RDADDR
#define GTM0ATOM00CTRL GTM0.ATOM00CTRL
#define GTM0ATOM00SR0 GTM0.ATOM00SR0
#define GTM0ATOM00SR1 GTM0.ATOM00SR1
#define GTM0ATOM00CM0 GTM0.ATOM00CM0
#define GTM0ATOM00CM1 GTM0.ATOM00CM1
#define GTM0ATOM00CN0 GTM0.ATOM00CN0
#define GTM0ATOM00STAT GTM0.ATOM00STAT
#define GTM0ATOM00IRQNOTIFY GTM0.ATOM00IRQNOTIFY
#define GTM0ATOM00IRQEN GTM0.ATOM00IRQEN
#define GTM0ATOM00IRQFORCINT GTM0.ATOM00IRQFORCINT
#define GTM0ATOM00IRQMODE GTM0.ATOM00IRQMODE
#define GTM0ATOM0AGCGLBCTRL GTM0.ATOM0AGCGLBCTRL
#define GTM0ATOM0AGCENDISCTRL GTM0.ATOM0AGCENDISCTRL
#define GTM0ATOM0AGCENDISSTAT GTM0.ATOM0AGCENDISSTAT
#define GTM0ATOM0AGCACTTB GTM0.ATOM0AGCACTTB
#define GTM0ATOM0AGCOUTENCTRL GTM0.ATOM0AGCOUTENCTRL
#define GTM0ATOM0AGCOUTENSTAT GTM0.ATOM0AGCOUTENSTAT
#define GTM0ATOM0AGCFUPDCTRL GTM0.ATOM0AGCFUPDCTRL
#define GTM0ATOM0AGCINTTRIG GTM0.ATOM0AGCINTTRIG
#define GTM0ATOM01RDADDR GTM0.ATOM01RDADDR
#define GTM0ATOM01CTRL GTM0.ATOM01CTRL
#define GTM0ATOM01SR0 GTM0.ATOM01SR0
#define GTM0ATOM01SR1 GTM0.ATOM01SR1
#define GTM0ATOM01CM0 GTM0.ATOM01CM0
#define GTM0ATOM01CM1 GTM0.ATOM01CM1
#define GTM0ATOM01CN0 GTM0.ATOM01CN0
#define GTM0ATOM01STAT GTM0.ATOM01STAT
#define GTM0ATOM01IRQNOTIFY GTM0.ATOM01IRQNOTIFY
#define GTM0ATOM01IRQEN GTM0.ATOM01IRQEN
#define GTM0ATOM01IRQFORCINT GTM0.ATOM01IRQFORCINT
#define GTM0ATOM01IRQMODE GTM0.ATOM01IRQMODE
#define GTM0ATOM02RDADDR GTM0.ATOM02RDADDR
#define GTM0ATOM02CTRL GTM0.ATOM02CTRL
#define GTM0ATOM02SR0 GTM0.ATOM02SR0
#define GTM0ATOM02SR1 GTM0.ATOM02SR1
#define GTM0ATOM02CM0 GTM0.ATOM02CM0
#define GTM0ATOM02CM1 GTM0.ATOM02CM1
#define GTM0ATOM02CN0 GTM0.ATOM02CN0
#define GTM0ATOM02STAT GTM0.ATOM02STAT
#define GTM0ATOM02IRQNOTIFY GTM0.ATOM02IRQNOTIFY
#define GTM0ATOM02IRQEN GTM0.ATOM02IRQEN
#define GTM0ATOM02IRQFORCINT GTM0.ATOM02IRQFORCINT
#define GTM0ATOM02IRQMODE GTM0.ATOM02IRQMODE
#define GTM0ATOM03RDADDR GTM0.ATOM03RDADDR
#define GTM0ATOM03CTRL GTM0.ATOM03CTRL
#define GTM0ATOM03SR0 GTM0.ATOM03SR0
#define GTM0ATOM03SR1 GTM0.ATOM03SR1
#define GTM0ATOM03CM0 GTM0.ATOM03CM0
#define GTM0ATOM03CM1 GTM0.ATOM03CM1
#define GTM0ATOM03CN0 GTM0.ATOM03CN0
#define GTM0ATOM03STAT GTM0.ATOM03STAT
#define GTM0ATOM03IRQNOTIFY GTM0.ATOM03IRQNOTIFY
#define GTM0ATOM03IRQEN GTM0.ATOM03IRQEN
#define GTM0ATOM03IRQFORCINT GTM0.ATOM03IRQFORCINT
#define GTM0ATOM03IRQMODE GTM0.ATOM03IRQMODE
#define GTM0ATOM04RDADDR GTM0.ATOM04RDADDR
#define GTM0ATOM04CTRL GTM0.ATOM04CTRL
#define GTM0ATOM04SR0 GTM0.ATOM04SR0
#define GTM0ATOM04SR1 GTM0.ATOM04SR1
#define GTM0ATOM04CM0 GTM0.ATOM04CM0
#define GTM0ATOM04CM1 GTM0.ATOM04CM1
#define GTM0ATOM04CN0 GTM0.ATOM04CN0
#define GTM0ATOM04STAT GTM0.ATOM04STAT
#define GTM0ATOM04IRQNOTIFY GTM0.ATOM04IRQNOTIFY
#define GTM0ATOM04IRQEN GTM0.ATOM04IRQEN
#define GTM0ATOM04IRQFORCINT GTM0.ATOM04IRQFORCINT
#define GTM0ATOM04IRQMODE GTM0.ATOM04IRQMODE
#define GTM0ATOM05RDADDR GTM0.ATOM05RDADDR
#define GTM0ATOM05CTRL GTM0.ATOM05CTRL
#define GTM0ATOM05SR0 GTM0.ATOM05SR0
#define GTM0ATOM05SR1 GTM0.ATOM05SR1
#define GTM0ATOM05CM0 GTM0.ATOM05CM0
#define GTM0ATOM05CM1 GTM0.ATOM05CM1
#define GTM0ATOM05CN0 GTM0.ATOM05CN0
#define GTM0ATOM05STAT GTM0.ATOM05STAT
#define GTM0ATOM05IRQNOTIFY GTM0.ATOM05IRQNOTIFY
#define GTM0ATOM05IRQEN GTM0.ATOM05IRQEN
#define GTM0ATOM05IRQFORCINT GTM0.ATOM05IRQFORCINT
#define GTM0ATOM05IRQMODE GTM0.ATOM05IRQMODE
#define GTM0ATOM06RDADDR GTM0.ATOM06RDADDR
#define GTM0ATOM06CTRL GTM0.ATOM06CTRL
#define GTM0ATOM06SR0 GTM0.ATOM06SR0
#define GTM0ATOM06SR1 GTM0.ATOM06SR1
#define GTM0ATOM06CM0 GTM0.ATOM06CM0
#define GTM0ATOM06CM1 GTM0.ATOM06CM1
#define GTM0ATOM06CN0 GTM0.ATOM06CN0
#define GTM0ATOM06STAT GTM0.ATOM06STAT
#define GTM0ATOM06IRQNOTIFY GTM0.ATOM06IRQNOTIFY
#define GTM0ATOM06IRQEN GTM0.ATOM06IRQEN
#define GTM0ATOM06IRQFORCINT GTM0.ATOM06IRQFORCINT
#define GTM0ATOM06IRQMODE GTM0.ATOM06IRQMODE
#define GTM0ATOM07RDADDR GTM0.ATOM07RDADDR
#define GTM0ATOM07CTRL GTM0.ATOM07CTRL
#define GTM0ATOM07SR0 GTM0.ATOM07SR0
#define GTM0ATOM07SR1 GTM0.ATOM07SR1
#define GTM0ATOM07CM0 GTM0.ATOM07CM0
#define GTM0ATOM07CM1 GTM0.ATOM07CM1
#define GTM0ATOM07CN0 GTM0.ATOM07CN0
#define GTM0ATOM07STAT GTM0.ATOM07STAT
#define GTM0ATOM07IRQNOTIFY GTM0.ATOM07IRQNOTIFY
#define GTM0ATOM07IRQEN GTM0.ATOM07IRQEN
#define GTM0ATOM07IRQFORCINT GTM0.ATOM07IRQFORCINT
#define GTM0ATOM07IRQMODE GTM0.ATOM07IRQMODE
#define GTM0ATOM10RDADDR GTM0.ATOM10RDADDR
#define GTM0ATOM10CTRL GTM0.ATOM10CTRL
#define GTM0ATOM10SR0 GTM0.ATOM10SR0
#define GTM0ATOM10SR1 GTM0.ATOM10SR1
#define GTM0ATOM10CM0 GTM0.ATOM10CM0
#define GTM0ATOM10CM1 GTM0.ATOM10CM1
#define GTM0ATOM10CN0 GTM0.ATOM10CN0
#define GTM0ATOM10STAT GTM0.ATOM10STAT
#define GTM0ATOM10IRQNOTIFY GTM0.ATOM10IRQNOTIFY
#define GTM0ATOM10IRQEN GTM0.ATOM10IRQEN
#define GTM0ATOM10IRQFORCINT GTM0.ATOM10IRQFORCINT
#define GTM0ATOM10IRQMODE GTM0.ATOM10IRQMODE
#define GTM0ATOM1AGCGLBCTRL GTM0.ATOM1AGCGLBCTRL
#define GTM0ATOM1AGCENDISCTRL GTM0.ATOM1AGCENDISCTRL
#define GTM0ATOM1AGCENDISSTAT GTM0.ATOM1AGCENDISSTAT
#define GTM0ATOM1AGCACTTB GTM0.ATOM1AGCACTTB
#define GTM0ATOM1AGCOUTENCTRL GTM0.ATOM1AGCOUTENCTRL
#define GTM0ATOM1AGCOUTENSTAT GTM0.ATOM1AGCOUTENSTAT
#define GTM0ATOM1AGCFUPDCTRL GTM0.ATOM1AGCFUPDCTRL
#define GTM0ATOM1AGCINTTRIG GTM0.ATOM1AGCINTTRIG
#define GTM0ATOM11RDADDR GTM0.ATOM11RDADDR
#define GTM0ATOM11CTRL GTM0.ATOM11CTRL
#define GTM0ATOM11SR0 GTM0.ATOM11SR0
#define GTM0ATOM11SR1 GTM0.ATOM11SR1
#define GTM0ATOM11CM0 GTM0.ATOM11CM0
#define GTM0ATOM11CM1 GTM0.ATOM11CM1
#define GTM0ATOM11CN0 GTM0.ATOM11CN0
#define GTM0ATOM11STAT GTM0.ATOM11STAT
#define GTM0ATOM11IRQNOTIFY GTM0.ATOM11IRQNOTIFY
#define GTM0ATOM11IRQEN GTM0.ATOM11IRQEN
#define GTM0ATOM11IRQFORCINT GTM0.ATOM11IRQFORCINT
#define GTM0ATOM11IRQMODE GTM0.ATOM11IRQMODE
#define GTM0ATOM12RDADDR GTM0.ATOM12RDADDR
#define GTM0ATOM12CTRL GTM0.ATOM12CTRL
#define GTM0ATOM12SR0 GTM0.ATOM12SR0
#define GTM0ATOM12SR1 GTM0.ATOM12SR1
#define GTM0ATOM12CM0 GTM0.ATOM12CM0
#define GTM0ATOM12CM1 GTM0.ATOM12CM1
#define GTM0ATOM12CN0 GTM0.ATOM12CN0
#define GTM0ATOM12STAT GTM0.ATOM12STAT
#define GTM0ATOM12IRQNOTIFY GTM0.ATOM12IRQNOTIFY
#define GTM0ATOM12IRQEN GTM0.ATOM12IRQEN
#define GTM0ATOM12IRQFORCINT GTM0.ATOM12IRQFORCINT
#define GTM0ATOM12IRQMODE GTM0.ATOM12IRQMODE
#define GTM0ATOM13RDADDR GTM0.ATOM13RDADDR
#define GTM0ATOM13CTRL GTM0.ATOM13CTRL
#define GTM0ATOM13SR0 GTM0.ATOM13SR0
#define GTM0ATOM13SR1 GTM0.ATOM13SR1
#define GTM0ATOM13CM0 GTM0.ATOM13CM0
#define GTM0ATOM13CM1 GTM0.ATOM13CM1
#define GTM0ATOM13CN0 GTM0.ATOM13CN0
#define GTM0ATOM13STAT GTM0.ATOM13STAT
#define GTM0ATOM13IRQNOTIFY GTM0.ATOM13IRQNOTIFY
#define GTM0ATOM13IRQEN GTM0.ATOM13IRQEN
#define GTM0ATOM13IRQFORCINT GTM0.ATOM13IRQFORCINT
#define GTM0ATOM13IRQMODE GTM0.ATOM13IRQMODE
#define GTM0DTM24CTRL GTM0.DTM24CTRL
#define GTM0DTM24CHCTRL1 GTM0.DTM24CHCTRL1
#define GTM0DTM24CHCTRL2 GTM0.DTM24CHCTRL2
#define GTM0DTM24CHCTRL2SR GTM0.DTM24CHCTRL2SR
#define GTM0DTM24PSCTRL GTM0.DTM24PSCTRL
#define GTM0DTM240DTV GTM0.DTM240DTV
#define GTM0DTM241DTV GTM0.DTM241DTV
#define GTM0DTM242DTV GTM0.DTM242DTV
#define GTM0DTM243DTV GTM0.DTM243DTV
#define GTM0DTM24CHSR GTM0.DTM24CHSR
#define GTM0DTM26CTRL GTM0.DTM26CTRL
#define GTM0DTM26CHCTRL1 GTM0.DTM26CHCTRL1
#define GTM0DTM26CHCTRL2 GTM0.DTM26CHCTRL2
#define GTM0DTM26CHCTRL2SR GTM0.DTM26CHCTRL2SR
#define GTM0DTM26PSCTRL GTM0.DTM26PSCTRL
#define GTM0DTM260DTV GTM0.DTM260DTV
#define GTM0DTM261DTV GTM0.DTM261DTV
#define GTM0DTM262DTV GTM0.DTM262DTV
#define GTM0DTM263DTV GTM0.DTM263DTV
#define GTM0DTM26CHSR GTM0.DTM26CHSR
#define GTM0MCS00R0 GTM0.MCS00R0
#define GTM0MCS00R1 GTM0.MCS00R1
#define GTM0MCS00R2 GTM0.MCS00R2
#define GTM0MCS00R3 GTM0.MCS00R3
#define GTM0MCS00R4 GTM0.MCS00R4
#define GTM0MCS00R5 GTM0.MCS00R5
#define GTM0MCS00R6 GTM0.MCS00R6
#define GTM0MCS00R7 GTM0.MCS00R7
#define GTM0MCS00CTRL GTM0.MCS00CTRL
#define GTM0MCS00ACB GTM0.MCS00ACB
#define GTM0MCS0CTRG GTM0.MCS0CTRG
#define GTM0MCS0STRG GTM0.MCS0STRG
#define GTM0MCS00MHB GTM0.MCS00MHB
#define GTM0MCS00PC GTM0.MCS00PC
#define GTM0MCS00IRQNOTIFY GTM0.MCS00IRQNOTIFY
#define GTM0MCS00IRQEN GTM0.MCS00IRQEN
#define GTM0MCS00IRQFORCINT GTM0.MCS00IRQFORCINT
#define GTM0MCS00IRQMODE GTM0.MCS00IRQMODE
#define GTM0MCS00EIRQEN GTM0.MCS00EIRQEN
#define GTM0MCS0CTRLSTAT GTM0.MCS0CTRLSTAT
#define GTM0MCS0RESET GTM0.MCS0RESET
#define GTM0MCS0CAT GTM0.MCS0CAT
#define GTM0MCS0CWT GTM0.MCS0CWT
#define GTM0MCS0ERR GTM0.MCS0ERR
#define GTM0MCS01R0 GTM0.MCS01R0
#define GTM0MCS01R1 GTM0.MCS01R1
#define GTM0MCS01R2 GTM0.MCS01R2
#define GTM0MCS01R3 GTM0.MCS01R3
#define GTM0MCS01R4 GTM0.MCS01R4
#define GTM0MCS01R5 GTM0.MCS01R5
#define GTM0MCS01R6 GTM0.MCS01R6
#define GTM0MCS01R7 GTM0.MCS01R7
#define GTM0MCS01CTRL GTM0.MCS01CTRL
#define GTM0MCS01ACB GTM0.MCS01ACB
#define GTM0MCS01MHB GTM0.MCS01MHB
#define GTM0MCS01PC GTM0.MCS01PC
#define GTM0MCS01IRQNOTIFY GTM0.MCS01IRQNOTIFY
#define GTM0MCS01IRQEN GTM0.MCS01IRQEN
#define GTM0MCS01IRQFORCINT GTM0.MCS01IRQFORCINT
#define GTM0MCS01IRQMODE GTM0.MCS01IRQMODE
#define GTM0MCS01EIRQEN GTM0.MCS01EIRQEN
#define GTM0MCS02R0 GTM0.MCS02R0
#define GTM0MCS02R1 GTM0.MCS02R1
#define GTM0MCS02R2 GTM0.MCS02R2
#define GTM0MCS02R3 GTM0.MCS02R3
#define GTM0MCS02R4 GTM0.MCS02R4
#define GTM0MCS02R5 GTM0.MCS02R5
#define GTM0MCS02R6 GTM0.MCS02R6
#define GTM0MCS02R7 GTM0.MCS02R7
#define GTM0MCS02CTRL GTM0.MCS02CTRL
#define GTM0MCS02ACB GTM0.MCS02ACB
#define GTM0MCS02MHB GTM0.MCS02MHB
#define GTM0MCS02PC GTM0.MCS02PC
#define GTM0MCS02IRQNOTIFY GTM0.MCS02IRQNOTIFY
#define GTM0MCS02IRQEN GTM0.MCS02IRQEN
#define GTM0MCS02IRQFORCINT GTM0.MCS02IRQFORCINT
#define GTM0MCS02IRQMODE GTM0.MCS02IRQMODE
#define GTM0MCS02EIRQEN GTM0.MCS02EIRQEN
#define GTM0MCS03R0 GTM0.MCS03R0
#define GTM0MCS03R1 GTM0.MCS03R1
#define GTM0MCS03R2 GTM0.MCS03R2
#define GTM0MCS03R3 GTM0.MCS03R3
#define GTM0MCS03R4 GTM0.MCS03R4
#define GTM0MCS03R5 GTM0.MCS03R5
#define GTM0MCS03R6 GTM0.MCS03R6
#define GTM0MCS03R7 GTM0.MCS03R7
#define GTM0MCS03CTRL GTM0.MCS03CTRL
#define GTM0MCS03ACB GTM0.MCS03ACB
#define GTM0MCS03MHB GTM0.MCS03MHB
#define GTM0MCS03PC GTM0.MCS03PC
#define GTM0MCS03IRQNOTIFY GTM0.MCS03IRQNOTIFY
#define GTM0MCS03IRQEN GTM0.MCS03IRQEN
#define GTM0MCS03IRQFORCINT GTM0.MCS03IRQFORCINT
#define GTM0MCS03IRQMODE GTM0.MCS03IRQMODE
#define GTM0MCS03EIRQEN GTM0.MCS03EIRQEN
#define GTM0MCS04R0 GTM0.MCS04R0
#define GTM0MCS04R1 GTM0.MCS04R1
#define GTM0MCS04R2 GTM0.MCS04R2
#define GTM0MCS04R3 GTM0.MCS04R3
#define GTM0MCS04R4 GTM0.MCS04R4
#define GTM0MCS04R5 GTM0.MCS04R5
#define GTM0MCS04R6 GTM0.MCS04R6
#define GTM0MCS04R7 GTM0.MCS04R7
#define GTM0MCS04CTRL GTM0.MCS04CTRL
#define GTM0MCS04ACB GTM0.MCS04ACB
#define GTM0MCS04MHB GTM0.MCS04MHB
#define GTM0MCS04PC GTM0.MCS04PC
#define GTM0MCS04IRQNOTIFY GTM0.MCS04IRQNOTIFY
#define GTM0MCS04IRQEN GTM0.MCS04IRQEN
#define GTM0MCS04IRQFORCINT GTM0.MCS04IRQFORCINT
#define GTM0MCS04IRQMODE GTM0.MCS04IRQMODE
#define GTM0MCS04EIRQEN GTM0.MCS04EIRQEN
#define GTM0MCS05R0 GTM0.MCS05R0
#define GTM0MCS05R1 GTM0.MCS05R1
#define GTM0MCS05R2 GTM0.MCS05R2
#define GTM0MCS05R3 GTM0.MCS05R3
#define GTM0MCS05R4 GTM0.MCS05R4
#define GTM0MCS05R5 GTM0.MCS05R5
#define GTM0MCS05R6 GTM0.MCS05R6
#define GTM0MCS05R7 GTM0.MCS05R7
#define GTM0MCS05CTRL GTM0.MCS05CTRL
#define GTM0MCS05ACB GTM0.MCS05ACB
#define GTM0MCS05MHB GTM0.MCS05MHB
#define GTM0MCS05PC GTM0.MCS05PC
#define GTM0MCS05IRQNOTIFY GTM0.MCS05IRQNOTIFY
#define GTM0MCS05IRQEN GTM0.MCS05IRQEN
#define GTM0MCS05IRQFORCINT GTM0.MCS05IRQFORCINT
#define GTM0MCS05IRQMODE GTM0.MCS05IRQMODE
#define GTM0MCS05EIRQEN GTM0.MCS05EIRQEN
#define GTM0MCS06R0 GTM0.MCS06R0
#define GTM0MCS06R1 GTM0.MCS06R1
#define GTM0MCS06R2 GTM0.MCS06R2
#define GTM0MCS06R3 GTM0.MCS06R3
#define GTM0MCS06R4 GTM0.MCS06R4
#define GTM0MCS06R5 GTM0.MCS06R5
#define GTM0MCS06R6 GTM0.MCS06R6
#define GTM0MCS06R7 GTM0.MCS06R7
#define GTM0MCS06CTRL GTM0.MCS06CTRL
#define GTM0MCS06ACB GTM0.MCS06ACB
#define GTM0MCS06MHB GTM0.MCS06MHB
#define GTM0MCS06PC GTM0.MCS06PC
#define GTM0MCS06IRQNOTIFY GTM0.MCS06IRQNOTIFY
#define GTM0MCS06IRQEN GTM0.MCS06IRQEN
#define GTM0MCS06IRQFORCINT GTM0.MCS06IRQFORCINT
#define GTM0MCS06IRQMODE GTM0.MCS06IRQMODE
#define GTM0MCS06EIRQEN GTM0.MCS06EIRQEN
#define GTM0MCS07R0 GTM0.MCS07R0
#define GTM0MCS07R1 GTM0.MCS07R1
#define GTM0MCS07R2 GTM0.MCS07R2
#define GTM0MCS07R3 GTM0.MCS07R3
#define GTM0MCS07R4 GTM0.MCS07R4
#define GTM0MCS07R5 GTM0.MCS07R5
#define GTM0MCS07R6 GTM0.MCS07R6
#define GTM0MCS07R7 GTM0.MCS07R7
#define GTM0MCS07CTRL GTM0.MCS07CTRL
#define GTM0MCS07ACB GTM0.MCS07ACB
#define GTM0MCS07MHB GTM0.MCS07MHB
#define GTM0MCS07PC GTM0.MCS07PC
#define GTM0MCS07IRQNOTIFY GTM0.MCS07IRQNOTIFY
#define GTM0MCS07IRQEN GTM0.MCS07IRQEN
#define GTM0MCS07IRQFORCINT GTM0.MCS07IRQFORCINT
#define GTM0MCS07IRQMODE GTM0.MCS07IRQMODE
#define GTM0MCS07EIRQEN GTM0.MCS07EIRQEN
#define GTM0MCS08R0 GTM0.MCS08R0
#define GTM0MCS08R1 GTM0.MCS08R1
#define GTM0MCS08R2 GTM0.MCS08R2
#define GTM0MCS08R3 GTM0.MCS08R3
#define GTM0MCS08R4 GTM0.MCS08R4
#define GTM0MCS08R5 GTM0.MCS08R5
#define GTM0MCS08R6 GTM0.MCS08R6
#define GTM0MCS08R7 GTM0.MCS08R7
#define GTM0MCS08CTRL GTM0.MCS08CTRL
#define GTM0MCS08ACB GTM0.MCS08ACB
#define GTM0MCS08MHB GTM0.MCS08MHB
#define GTM0MCS08PC GTM0.MCS08PC
#define GTM0MCS08IRQNOTIFY GTM0.MCS08IRQNOTIFY
#define GTM0MCS08IRQEN GTM0.MCS08IRQEN
#define GTM0MCS08IRQFORCINT GTM0.MCS08IRQFORCINT
#define GTM0MCS08IRQMODE GTM0.MCS08IRQMODE
#define GTM0MCS08EIRQEN GTM0.MCS08EIRQEN
#define ECCGTM0CTL ECCGTM0.CTL
#define ECCGTM0TMC ECCGTM0.TMC
#define ECCGTM0TRC ECCGTM0.TRC
#define ECCGTM0TED ECCGTM0.TED
#define ECCGTM0EAD0 ECCGTM0.EAD0
#define ECCGTM1CTL ECCGTM1.CTL
#define ECCGTM1TMC ECCGTM1.TMC
#define ECCGTM1TRC ECCGTM1.TRC
#define ECCGTM1TED ECCGTM1.TED
#define ECCGTM1EAD0 ECCGTM1.EAD0
#define WDTA0WDTE WDTA0.WDTE
#define WDTA0EVAC WDTA0.EVAC
#define WDTA0REF WDTA0.REF
#define WDTA0MD WDTA0.MD
#define SWD0CLR SWD0.CLR
#define SWD0STS0 SWD0.STS0
#define SWD0STS1 SWD0.STS1
#define SWD0STSC SWD0.STSC
#define SWD0WDTE SWD0.WDTE
#define SWD0MD SWD0.MD
#define SWD0PCAD SWD0.PCAD
#define FSGD1APROT00 FSGD1A.PROT00.ui32
#define FSGD1APROT00L FSGD1A.PROT00.ui16[0]
#define FSGD1APROT00LL FSGD1A.PROT00.ui8[0]
#define FSGD1APROT00LH FSGD1A.PROT00.ui8[1]
#define FSGD1APROT00H FSGD1A.PROT00.ui16[1]
#define FSGD1APROT00HL FSGD1A.PROT00.ui8[2]
#define FSGD1APROT00HH FSGD1A.PROT00.ui8[3]
#define FSGD1ASPID00 FSGD1A.SPID00.ui32
#define FSGD1ASPID00L FSGD1A.SPID00.ui16[0]
#define FSGD1ASPID00LL FSGD1A.SPID00.ui8[0]
#define FSGD1ASPID00LH FSGD1A.SPID00.ui8[1]
#define FSGD1ASPID00H FSGD1A.SPID00.ui16[1]
#define FSGD1ASPID00HL FSGD1A.SPID00.ui8[2]
#define FSGD1ASPID00HH FSGD1A.SPID00.ui8[3]
#define FSGD1APROT01 FSGD1A.PROT01.ui32
#define FSGD1APROT01L FSGD1A.PROT01.ui16[0]
#define FSGD1APROT01LL FSGD1A.PROT01.ui8[0]
#define FSGD1APROT01LH FSGD1A.PROT01.ui8[1]
#define FSGD1APROT01H FSGD1A.PROT01.ui16[1]
#define FSGD1APROT01HL FSGD1A.PROT01.ui8[2]
#define FSGD1APROT01HH FSGD1A.PROT01.ui8[3]
#define FSGD1ASPID01 FSGD1A.SPID01.ui32
#define FSGD1ASPID01L FSGD1A.SPID01.ui16[0]
#define FSGD1ASPID01LL FSGD1A.SPID01.ui8[0]
#define FSGD1ASPID01LH FSGD1A.SPID01.ui8[1]
#define FSGD1ASPID01H FSGD1A.SPID01.ui16[1]
#define FSGD1ASPID01HL FSGD1A.SPID01.ui8[2]
#define FSGD1ASPID01HH FSGD1A.SPID01.ui8[3]
#define FSGD1APROT02 FSGD1A.PROT02.ui32
#define FSGD1APROT02L FSGD1A.PROT02.ui16[0]
#define FSGD1APROT02LL FSGD1A.PROT02.ui8[0]
#define FSGD1APROT02LH FSGD1A.PROT02.ui8[1]
#define FSGD1APROT02H FSGD1A.PROT02.ui16[1]
#define FSGD1APROT02HL FSGD1A.PROT02.ui8[2]
#define FSGD1APROT02HH FSGD1A.PROT02.ui8[3]
#define FSGD1ASPID02 FSGD1A.SPID02.ui32
#define FSGD1ASPID02L FSGD1A.SPID02.ui16[0]
#define FSGD1ASPID02LL FSGD1A.SPID02.ui8[0]
#define FSGD1ASPID02LH FSGD1A.SPID02.ui8[1]
#define FSGD1ASPID02H FSGD1A.SPID02.ui16[1]
#define FSGD1ASPID02HL FSGD1A.SPID02.ui8[2]
#define FSGD1ASPID02HH FSGD1A.SPID02.ui8[3]
#define FSGD1APROT03 FSGD1A.PROT03.ui32
#define FSGD1APROT03L FSGD1A.PROT03.ui16[0]
#define FSGD1APROT03LL FSGD1A.PROT03.ui8[0]
#define FSGD1APROT03LH FSGD1A.PROT03.ui8[1]
#define FSGD1APROT03H FSGD1A.PROT03.ui16[1]
#define FSGD1APROT03HL FSGD1A.PROT03.ui8[2]
#define FSGD1APROT03HH FSGD1A.PROT03.ui8[3]
#define FSGD1ASPID03 FSGD1A.SPID03.ui32
#define FSGD1ASPID03L FSGD1A.SPID03.ui16[0]
#define FSGD1ASPID03LL FSGD1A.SPID03.ui8[0]
#define FSGD1ASPID03LH FSGD1A.SPID03.ui8[1]
#define FSGD1ASPID03H FSGD1A.SPID03.ui16[1]
#define FSGD1ASPID03HL FSGD1A.SPID03.ui8[2]
#define FSGD1ASPID03HH FSGD1A.SPID03.ui8[3]
#define FSGD1APROT04 FSGD1A.PROT04.ui32
#define FSGD1APROT04L FSGD1A.PROT04.ui16[0]
#define FSGD1APROT04LL FSGD1A.PROT04.ui8[0]
#define FSGD1APROT04LH FSGD1A.PROT04.ui8[1]
#define FSGD1APROT04H FSGD1A.PROT04.ui16[1]
#define FSGD1APROT04HL FSGD1A.PROT04.ui8[2]
#define FSGD1APROT04HH FSGD1A.PROT04.ui8[3]
#define FSGD1ASPID04 FSGD1A.SPID04.ui32
#define FSGD1ASPID04L FSGD1A.SPID04.ui16[0]
#define FSGD1ASPID04LL FSGD1A.SPID04.ui8[0]
#define FSGD1ASPID04LH FSGD1A.SPID04.ui8[1]
#define FSGD1ASPID04H FSGD1A.SPID04.ui16[1]
#define FSGD1ASPID04HL FSGD1A.SPID04.ui8[2]
#define FSGD1ASPID04HH FSGD1A.SPID04.ui8[3]
#define FSGD1APROT05 FSGD1A.PROT05.ui32
#define FSGD1APROT05L FSGD1A.PROT05.ui16[0]
#define FSGD1APROT05LL FSGD1A.PROT05.ui8[0]
#define FSGD1APROT05LH FSGD1A.PROT05.ui8[1]
#define FSGD1APROT05H FSGD1A.PROT05.ui16[1]
#define FSGD1APROT05HL FSGD1A.PROT05.ui8[2]
#define FSGD1APROT05HH FSGD1A.PROT05.ui8[3]
#define FSGD1ASPID05 FSGD1A.SPID05.ui32
#define FSGD1ASPID05L FSGD1A.SPID05.ui16[0]
#define FSGD1ASPID05LL FSGD1A.SPID05.ui8[0]
#define FSGD1ASPID05LH FSGD1A.SPID05.ui8[1]
#define FSGD1ASPID05H FSGD1A.SPID05.ui16[1]
#define FSGD1ASPID05HL FSGD1A.SPID05.ui8[2]
#define FSGD1ASPID05HH FSGD1A.SPID05.ui8[3]
#define ERRSLV1CTL ERRSLV1.CTL
#define ERRSLV1STAT ERRSLV1.STAT
#define ERRSLV1TYPE ERRSLV1.TYPE
#define FSGD1BPROT00 FSGD1B.PROT00.ui32
#define FSGD1BPROT00L FSGD1B.PROT00.ui16[0]
#define FSGD1BPROT00LL FSGD1B.PROT00.ui8[0]
#define FSGD1BPROT00LH FSGD1B.PROT00.ui8[1]
#define FSGD1BPROT00H FSGD1B.PROT00.ui16[1]
#define FSGD1BPROT00HL FSGD1B.PROT00.ui8[2]
#define FSGD1BPROT00HH FSGD1B.PROT00.ui8[3]
#define FSGD1BSPID00 FSGD1B.SPID00.ui32
#define FSGD1BSPID00L FSGD1B.SPID00.ui16[0]
#define FSGD1BSPID00LL FSGD1B.SPID00.ui8[0]
#define FSGD1BSPID00LH FSGD1B.SPID00.ui8[1]
#define FSGD1BSPID00H FSGD1B.SPID00.ui16[1]
#define FSGD1BSPID00HL FSGD1B.SPID00.ui8[2]
#define FSGD1BSPID00HH FSGD1B.SPID00.ui8[3]
#define FSGD1BPROT01 FSGD1B.PROT01.ui32
#define FSGD1BPROT01L FSGD1B.PROT01.ui16[0]
#define FSGD1BPROT01LL FSGD1B.PROT01.ui8[0]
#define FSGD1BPROT01LH FSGD1B.PROT01.ui8[1]
#define FSGD1BPROT01H FSGD1B.PROT01.ui16[1]
#define FSGD1BPROT01HL FSGD1B.PROT01.ui8[2]
#define FSGD1BPROT01HH FSGD1B.PROT01.ui8[3]
#define FSGD1BSPID01 FSGD1B.SPID01.ui32
#define FSGD1BSPID01L FSGD1B.SPID01.ui16[0]
#define FSGD1BSPID01LL FSGD1B.SPID01.ui8[0]
#define FSGD1BSPID01LH FSGD1B.SPID01.ui8[1]
#define FSGD1BSPID01H FSGD1B.SPID01.ui16[1]
#define FSGD1BSPID01HL FSGD1B.SPID01.ui8[2]
#define FSGD1BSPID01HH FSGD1B.SPID01.ui8[3]
#define FSGD1BPROT10 FSGD1B.PROT10.ui32
#define FSGD1BPROT10L FSGD1B.PROT10.ui16[0]
#define FSGD1BPROT10LL FSGD1B.PROT10.ui8[0]
#define FSGD1BPROT10LH FSGD1B.PROT10.ui8[1]
#define FSGD1BPROT10H FSGD1B.PROT10.ui16[1]
#define FSGD1BPROT10HL FSGD1B.PROT10.ui8[2]
#define FSGD1BPROT10HH FSGD1B.PROT10.ui8[3]
#define FSGD1BSPID10 FSGD1B.SPID10.ui32
#define FSGD1BSPID10L FSGD1B.SPID10.ui16[0]
#define FSGD1BSPID10LL FSGD1B.SPID10.ui8[0]
#define FSGD1BSPID10LH FSGD1B.SPID10.ui8[1]
#define FSGD1BSPID10H FSGD1B.SPID10.ui16[1]
#define FSGD1BSPID10HL FSGD1B.SPID10.ui8[2]
#define FSGD1BSPID10HH FSGD1B.SPID10.ui8[3]
#define FSGD1BPROT11 FSGD1B.PROT11.ui32
#define FSGD1BPROT11L FSGD1B.PROT11.ui16[0]
#define FSGD1BPROT11LL FSGD1B.PROT11.ui8[0]
#define FSGD1BPROT11LH FSGD1B.PROT11.ui8[1]
#define FSGD1BPROT11H FSGD1B.PROT11.ui16[1]
#define FSGD1BPROT11HL FSGD1B.PROT11.ui8[2]
#define FSGD1BPROT11HH FSGD1B.PROT11.ui8[3]
#define FSGD1BSPID11 FSGD1B.SPID11.ui32
#define FSGD1BSPID11L FSGD1B.SPID11.ui16[0]
#define FSGD1BSPID11LL FSGD1B.SPID11.ui8[0]
#define FSGD1BSPID11LH FSGD1B.SPID11.ui8[1]
#define FSGD1BSPID11H FSGD1B.SPID11.ui16[1]
#define FSGD1BSPID11HL FSGD1B.SPID11.ui8[2]
#define FSGD1BSPID11HH FSGD1B.SPID11.ui8[3]
#define ERRSLV1AICTL ERRSLV1AI.CTL
#define ERRSLV1AISTAT ERRSLV1AI.STAT
#define ERRSLV1AITYPE ERRSLV1AI.TYPE
#define MCAN0CREL MCAN0.CREL.ui32
#define MCAN0CRELL MCAN0.CREL.ui16[0]
#define MCAN0CRELLL MCAN0.CREL.ui8[0]
#define MCAN0CRELLH MCAN0.CREL.ui8[1]
#define MCAN0CRELH MCAN0.CREL.ui16[1]
#define MCAN0CRELHL MCAN0.CREL.ui8[2]
#define MCAN0CRELHH MCAN0.CREL.ui8[3]
#define MCAN0ENDN MCAN0.ENDN.ui32
#define MCAN0ENDNL MCAN0.ENDN.ui16[0]
#define MCAN0ENDNLL MCAN0.ENDN.ui8[0]
#define MCAN0ENDNLH MCAN0.ENDN.ui8[1]
#define MCAN0ENDNH MCAN0.ENDN.ui16[1]
#define MCAN0ENDNHL MCAN0.ENDN.ui8[2]
#define MCAN0ENDNHH MCAN0.ENDN.ui8[3]
#define MCAN0DBTP MCAN0.DBTP.ui32
#define MCAN0DBTPL MCAN0.DBTP.ui16[0]
#define MCAN0DBTPLL MCAN0.DBTP.ui8[0]
#define MCAN0DBTPLH MCAN0.DBTP.ui8[1]
#define MCAN0DBTPH MCAN0.DBTP.ui16[1]
#define MCAN0DBTPHL MCAN0.DBTP.ui8[2]
#define MCAN0DBTPHH MCAN0.DBTP.ui8[3]
#define MCAN0TEST MCAN0.TEST.ui32
#define MCAN0TESTL MCAN0.TEST.ui16[0]
#define MCAN0TESTLL MCAN0.TEST.ui8[0]
#define MCAN0TESTLH MCAN0.TEST.ui8[1]
#define MCAN0RWD MCAN0.RWD.ui32
#define MCAN0RWDL MCAN0.RWD.ui16[0]
#define MCAN0RWDLL MCAN0.RWD.ui8[0]
#define MCAN0RWDLH MCAN0.RWD.ui8[1]
#define MCAN0CCCR MCAN0.CCCR.ui32
#define MCAN0CCCRL MCAN0.CCCR.ui16[0]
#define MCAN0CCCRLL MCAN0.CCCR.ui8[0]
#define MCAN0CCCRLH MCAN0.CCCR.ui8[1]
#define MCAN0NBTP MCAN0.NBTP.ui32
#define MCAN0NBTPL MCAN0.NBTP.ui16[0]
#define MCAN0NBTPLL MCAN0.NBTP.ui8[0]
#define MCAN0NBTPLH MCAN0.NBTP.ui8[1]
#define MCAN0NBTPH MCAN0.NBTP.ui16[1]
#define MCAN0NBTPHL MCAN0.NBTP.ui8[2]
#define MCAN0NBTPHH MCAN0.NBTP.ui8[3]
#define MCAN0TSCC MCAN0.TSCC.ui32
#define MCAN0TSCCL MCAN0.TSCC.ui16[0]
#define MCAN0TSCCLL MCAN0.TSCC.ui8[0]
#define MCAN0TSCCLH MCAN0.TSCC.ui8[1]
#define MCAN0TSCCH MCAN0.TSCC.ui16[1]
#define MCAN0TSCCHL MCAN0.TSCC.ui8[2]
#define MCAN0TSCCHH MCAN0.TSCC.ui8[3]
#define MCAN0TSCV MCAN0.TSCV.ui32
#define MCAN0TSCVL MCAN0.TSCV.ui16[0]
#define MCAN0TSCVLL MCAN0.TSCV.ui8[0]
#define MCAN0TSCVLH MCAN0.TSCV.ui8[1]
#define MCAN0TOCC MCAN0.TOCC.ui32
#define MCAN0TOCCL MCAN0.TOCC.ui16[0]
#define MCAN0TOCCLL MCAN0.TOCC.ui8[0]
#define MCAN0TOCCLH MCAN0.TOCC.ui8[1]
#define MCAN0TOCCH MCAN0.TOCC.ui16[1]
#define MCAN0TOCCHL MCAN0.TOCC.ui8[2]
#define MCAN0TOCCHH MCAN0.TOCC.ui8[3]
#define MCAN0TOCV MCAN0.TOCV.ui32
#define MCAN0TOCVL MCAN0.TOCV.ui16[0]
#define MCAN0TOCVLL MCAN0.TOCV.ui8[0]
#define MCAN0TOCVLH MCAN0.TOCV.ui8[1]
#define MCAN0ECR MCAN0.ECR.ui32
#define MCAN0ECRL MCAN0.ECR.ui16[0]
#define MCAN0ECRLL MCAN0.ECR.ui8[0]
#define MCAN0ECRLH MCAN0.ECR.ui8[1]
#define MCAN0ECRH MCAN0.ECR.ui16[1]
#define MCAN0ECRHL MCAN0.ECR.ui8[2]
#define MCAN0ECRHH MCAN0.ECR.ui8[3]
#define MCAN0PSR MCAN0.PSR.ui32
#define MCAN0PSRL MCAN0.PSR.ui16[0]
#define MCAN0PSRLL MCAN0.PSR.ui8[0]
#define MCAN0PSRLH MCAN0.PSR.ui8[1]
#define MCAN0TDCR MCAN0.TDCR.ui32
#define MCAN0TDCRL MCAN0.TDCR.ui16[0]
#define MCAN0TDCRLL MCAN0.TDCR.ui8[0]
#define MCAN0TDCRLH MCAN0.TDCR.ui8[1]
#define MCAN0IR MCAN0.IR.ui32
#define MCAN0IRL MCAN0.IR.ui16[0]
#define MCAN0IRLL MCAN0.IR.ui8[0]
#define MCAN0IRLH MCAN0.IR.ui8[1]
#define MCAN0IRH MCAN0.IR.ui16[1]
#define MCAN0IRHL MCAN0.IR.ui8[2]
#define MCAN0IRHH MCAN0.IR.ui8[3]
#define MCAN0IE MCAN0.IE.ui32
#define MCAN0IEL MCAN0.IE.ui16[0]
#define MCAN0IELL MCAN0.IE.ui8[0]
#define MCAN0IELH MCAN0.IE.ui8[1]
#define MCAN0IEH MCAN0.IE.ui16[1]
#define MCAN0IEHL MCAN0.IE.ui8[2]
#define MCAN0IEHH MCAN0.IE.ui8[3]
#define MCAN0ILS MCAN0.ILS.ui32
#define MCAN0ILSL MCAN0.ILS.ui16[0]
#define MCAN0ILSLL MCAN0.ILS.ui8[0]
#define MCAN0ILSLH MCAN0.ILS.ui8[1]
#define MCAN0ILSH MCAN0.ILS.ui16[1]
#define MCAN0ILSHL MCAN0.ILS.ui8[2]
#define MCAN0ILSHH MCAN0.ILS.ui8[3]
#define MCAN0ILE MCAN0.ILE.ui32
#define MCAN0ILEL MCAN0.ILE.ui16[0]
#define MCAN0ILELL MCAN0.ILE.ui8[0]
#define MCAN0ILELH MCAN0.ILE.ui8[1]
#define MCAN0GFC MCAN0.GFC.ui32
#define MCAN0GFCL MCAN0.GFC.ui16[0]
#define MCAN0GFCLL MCAN0.GFC.ui8[0]
#define MCAN0GFCLH MCAN0.GFC.ui8[1]
#define MCAN0SIDFC MCAN0.SIDFC.ui32
#define MCAN0SIDFCL MCAN0.SIDFC.ui16[0]
#define MCAN0SIDFCLL MCAN0.SIDFC.ui8[0]
#define MCAN0SIDFCLH MCAN0.SIDFC.ui8[1]
#define MCAN0SIDFCH MCAN0.SIDFC.ui16[1]
#define MCAN0SIDFCHL MCAN0.SIDFC.ui8[2]
#define MCAN0SIDFCHH MCAN0.SIDFC.ui8[3]
#define MCAN0XIDFC MCAN0.XIDFC.ui32
#define MCAN0XIDFCL MCAN0.XIDFC.ui16[0]
#define MCAN0XIDFCLL MCAN0.XIDFC.ui8[0]
#define MCAN0XIDFCLH MCAN0.XIDFC.ui8[1]
#define MCAN0XIDFCH MCAN0.XIDFC.ui16[1]
#define MCAN0XIDFCHL MCAN0.XIDFC.ui8[2]
#define MCAN0XIDFCHH MCAN0.XIDFC.ui8[3]
#define MCAN0XIDAM MCAN0.XIDAM.ui32
#define MCAN0XIDAML MCAN0.XIDAM.ui16[0]
#define MCAN0XIDAMLL MCAN0.XIDAM.ui8[0]
#define MCAN0XIDAMLH MCAN0.XIDAM.ui8[1]
#define MCAN0XIDAMH MCAN0.XIDAM.ui16[1]
#define MCAN0XIDAMHL MCAN0.XIDAM.ui8[2]
#define MCAN0XIDAMHH MCAN0.XIDAM.ui8[3]
#define MCAN0HPMS MCAN0.HPMS.ui32
#define MCAN0HPMSL MCAN0.HPMS.ui16[0]
#define MCAN0HPMSLL MCAN0.HPMS.ui8[0]
#define MCAN0HPMSLH MCAN0.HPMS.ui8[1]
#define MCAN0NDAT1 MCAN0.NDAT1.ui32
#define MCAN0NDAT1L MCAN0.NDAT1.ui16[0]
#define MCAN0NDAT1LL MCAN0.NDAT1.ui8[0]
#define MCAN0NDAT1LH MCAN0.NDAT1.ui8[1]
#define MCAN0NDAT1H MCAN0.NDAT1.ui16[1]
#define MCAN0NDAT1HL MCAN0.NDAT1.ui8[2]
#define MCAN0NDAT1HH MCAN0.NDAT1.ui8[3]
#define MCAN0NDAT2 MCAN0.NDAT2.ui32
#define MCAN0NDAT2L MCAN0.NDAT2.ui16[0]
#define MCAN0NDAT2LL MCAN0.NDAT2.ui8[0]
#define MCAN0NDAT2LH MCAN0.NDAT2.ui8[1]
#define MCAN0NDAT2H MCAN0.NDAT2.ui16[1]
#define MCAN0NDAT2HL MCAN0.NDAT2.ui8[2]
#define MCAN0NDAT2HH MCAN0.NDAT2.ui8[3]
#define MCAN0RXF0C MCAN0.RXF0C.ui32
#define MCAN0RXF0CL MCAN0.RXF0C.ui16[0]
#define MCAN0RXF0CLL MCAN0.RXF0C.ui8[0]
#define MCAN0RXF0CLH MCAN0.RXF0C.ui8[1]
#define MCAN0RXF0CH MCAN0.RXF0C.ui16[1]
#define MCAN0RXF0CHL MCAN0.RXF0C.ui8[2]
#define MCAN0RXF0CHH MCAN0.RXF0C.ui8[3]
#define MCAN0RXF0S MCAN0.RXF0S.ui32
#define MCAN0RXF0SL MCAN0.RXF0S.ui16[0]
#define MCAN0RXF0SLL MCAN0.RXF0S.ui8[0]
#define MCAN0RXF0SLH MCAN0.RXF0S.ui8[1]
#define MCAN0RXF0SH MCAN0.RXF0S.ui16[1]
#define MCAN0RXF0SHL MCAN0.RXF0S.ui8[2]
#define MCAN0RXF0SHH MCAN0.RXF0S.ui8[3]
#define MCAN0RXF0A MCAN0.RXF0A.ui32
#define MCAN0RXF0AL MCAN0.RXF0A.ui16[0]
#define MCAN0RXF0ALL MCAN0.RXF0A.ui8[0]
#define MCAN0RXF0ALH MCAN0.RXF0A.ui8[1]
#define MCAN0RXBC MCAN0.RXBC.ui32
#define MCAN0RXBCL MCAN0.RXBC.ui16[0]
#define MCAN0RXBCLL MCAN0.RXBC.ui8[0]
#define MCAN0RXBCLH MCAN0.RXBC.ui8[1]
#define MCAN0RXF1C MCAN0.RXF1C.ui32
#define MCAN0RXF1CL MCAN0.RXF1C.ui16[0]
#define MCAN0RXF1CLL MCAN0.RXF1C.ui8[0]
#define MCAN0RXF1CLH MCAN0.RXF1C.ui8[1]
#define MCAN0RXF1CH MCAN0.RXF1C.ui16[1]
#define MCAN0RXF1CHL MCAN0.RXF1C.ui8[2]
#define MCAN0RXF1CHH MCAN0.RXF1C.ui8[3]
#define MCAN0RXF1S MCAN0.RXF1S.ui32
#define MCAN0RXF1SL MCAN0.RXF1S.ui16[0]
#define MCAN0RXF1SLL MCAN0.RXF1S.ui8[0]
#define MCAN0RXF1SLH MCAN0.RXF1S.ui8[1]
#define MCAN0RXF1SH MCAN0.RXF1S.ui16[1]
#define MCAN0RXF1SHL MCAN0.RXF1S.ui8[2]
#define MCAN0RXF1SHH MCAN0.RXF1S.ui8[3]
#define MCAN0RXF1A MCAN0.RXF1A.ui32
#define MCAN0RXF1AL MCAN0.RXF1A.ui16[0]
#define MCAN0RXF1ALL MCAN0.RXF1A.ui8[0]
#define MCAN0RXF1ALH MCAN0.RXF1A.ui8[1]
#define MCAN0RXESC MCAN0.RXESC.ui32
#define MCAN0RXESCL MCAN0.RXESC.ui16[0]
#define MCAN0RXESCLL MCAN0.RXESC.ui8[0]
#define MCAN0RXESCLH MCAN0.RXESC.ui8[1]
#define MCAN0TXBC MCAN0.TXBC.ui32
#define MCAN0TXBCL MCAN0.TXBC.ui16[0]
#define MCAN0TXBCLL MCAN0.TXBC.ui8[0]
#define MCAN0TXBCLH MCAN0.TXBC.ui8[1]
#define MCAN0TXBCH MCAN0.TXBC.ui16[1]
#define MCAN0TXBCHL MCAN0.TXBC.ui8[2]
#define MCAN0TXBCHH MCAN0.TXBC.ui8[3]
#define MCAN0TXFQS MCAN0.TXFQS.ui32
#define MCAN0TXFQSL MCAN0.TXFQS.ui16[0]
#define MCAN0TXFQSLL MCAN0.TXFQS.ui8[0]
#define MCAN0TXFQSLH MCAN0.TXFQS.ui8[1]
#define MCAN0TXFQSH MCAN0.TXFQS.ui16[1]
#define MCAN0TXFQSHL MCAN0.TXFQS.ui8[2]
#define MCAN0TXFQSHH MCAN0.TXFQS.ui8[3]
#define MCAN0TXESC MCAN0.TXESC.ui32
#define MCAN0TXESCL MCAN0.TXESC.ui16[0]
#define MCAN0TXESCLL MCAN0.TXESC.ui8[0]
#define MCAN0TXESCLH MCAN0.TXESC.ui8[1]
#define MCAN0TXBRP MCAN0.TXBRP.ui32
#define MCAN0TXBRPL MCAN0.TXBRP.ui16[0]
#define MCAN0TXBRPLL MCAN0.TXBRP.ui8[0]
#define MCAN0TXBRPLH MCAN0.TXBRP.ui8[1]
#define MCAN0TXBRPH MCAN0.TXBRP.ui16[1]
#define MCAN0TXBRPHL MCAN0.TXBRP.ui8[2]
#define MCAN0TXBRPHH MCAN0.TXBRP.ui8[3]
#define MCAN0TXBAR MCAN0.TXBAR.ui32
#define MCAN0TXBARL MCAN0.TXBAR.ui16[0]
#define MCAN0TXBARLL MCAN0.TXBAR.ui8[0]
#define MCAN0TXBARLH MCAN0.TXBAR.ui8[1]
#define MCAN0TXBARH MCAN0.TXBAR.ui16[1]
#define MCAN0TXBARHL MCAN0.TXBAR.ui8[2]
#define MCAN0TXBARHH MCAN0.TXBAR.ui8[3]
#define MCAN0TXBCR MCAN0.TXBCR.ui32
#define MCAN0TXBCRL MCAN0.TXBCR.ui16[0]
#define MCAN0TXBCRLL MCAN0.TXBCR.ui8[0]
#define MCAN0TXBCRLH MCAN0.TXBCR.ui8[1]
#define MCAN0TXBCRH MCAN0.TXBCR.ui16[1]
#define MCAN0TXBCRHL MCAN0.TXBCR.ui8[2]
#define MCAN0TXBCRHH MCAN0.TXBCR.ui8[3]
#define MCAN0TXBTO MCAN0.TXBTO.ui32
#define MCAN0TXBTOL MCAN0.TXBTO.ui16[0]
#define MCAN0TXBTOLL MCAN0.TXBTO.ui8[0]
#define MCAN0TXBTOLH MCAN0.TXBTO.ui8[1]
#define MCAN0TXBTOH MCAN0.TXBTO.ui16[1]
#define MCAN0TXBTOHL MCAN0.TXBTO.ui8[2]
#define MCAN0TXBTOHH MCAN0.TXBTO.ui8[3]
#define MCAN0TXBCF MCAN0.TXBCF.ui32
#define MCAN0TXBCFL MCAN0.TXBCF.ui16[0]
#define MCAN0TXBCFLL MCAN0.TXBCF.ui8[0]
#define MCAN0TXBCFLH MCAN0.TXBCF.ui8[1]
#define MCAN0TXBCFH MCAN0.TXBCF.ui16[1]
#define MCAN0TXBCFHL MCAN0.TXBCF.ui8[2]
#define MCAN0TXBCFHH MCAN0.TXBCF.ui8[3]
#define MCAN0TXBTIE MCAN0.TXBTIE.ui32
#define MCAN0TXBTIEL MCAN0.TXBTIE.ui16[0]
#define MCAN0TXBTIELL MCAN0.TXBTIE.ui8[0]
#define MCAN0TXBTIELH MCAN0.TXBTIE.ui8[1]
#define MCAN0TXBTIEH MCAN0.TXBTIE.ui16[1]
#define MCAN0TXBTIEHL MCAN0.TXBTIE.ui8[2]
#define MCAN0TXBTIEHH MCAN0.TXBTIE.ui8[3]
#define MCAN0TXBCIE MCAN0.TXBCIE.ui32
#define MCAN0TXBCIEL MCAN0.TXBCIE.ui16[0]
#define MCAN0TXBCIELL MCAN0.TXBCIE.ui8[0]
#define MCAN0TXBCIELH MCAN0.TXBCIE.ui8[1]
#define MCAN0TXBCIEH MCAN0.TXBCIE.ui16[1]
#define MCAN0TXBCIEHL MCAN0.TXBCIE.ui8[2]
#define MCAN0TXBCIEHH MCAN0.TXBCIE.ui8[3]
#define MCAN0TXEFC MCAN0.TXEFC.ui32
#define MCAN0TXEFCL MCAN0.TXEFC.ui16[0]
#define MCAN0TXEFCLL MCAN0.TXEFC.ui8[0]
#define MCAN0TXEFCLH MCAN0.TXEFC.ui8[1]
#define MCAN0TXEFCH MCAN0.TXEFC.ui16[1]
#define MCAN0TXEFCHL MCAN0.TXEFC.ui8[2]
#define MCAN0TXEFCHH MCAN0.TXEFC.ui8[3]
#define MCAN0TXEFS MCAN0.TXEFS.ui32
#define MCAN0TXEFSL MCAN0.TXEFS.ui16[0]
#define MCAN0TXEFSLL MCAN0.TXEFS.ui8[0]
#define MCAN0TXEFSLH MCAN0.TXEFS.ui8[1]
#define MCAN0TXEFSH MCAN0.TXEFS.ui16[1]
#define MCAN0TXEFSHL MCAN0.TXEFS.ui8[2]
#define MCAN0TXEFSHH MCAN0.TXEFS.ui8[3]
#define MCAN0TXEFA MCAN0.TXEFA.ui32
#define MCAN0TXEFAL MCAN0.TXEFA.ui16[0]
#define MCAN0TXEFALL MCAN0.TXEFA.ui8[0]
#define MCAN0TXEFALH MCAN0.TXEFA.ui8[1]
#define DCRB1CIN DCRB1.CIN
#define DCRB1COUT DCRB1.COUT
#define DCRB1CTL DCRB1.CTL
#define CLMA0CTL0 CLMA0.CTL0
#define CLMA0CMPL CLMA0.CMPL
#define CLMA0CMPH CLMA0.CMPH
#define CLMA0PCMD CLMA0.PCMD
#define CLMA0PS CLMA0.PS
#define CLMA0EMU0 CLMA0.EMU0
#define CLMA1CTL0 CLMA1.CTL0
#define CLMA1CMPL CLMA1.CMPL
#define CLMA1CMPH CLMA1.CMPH
#define CLMA1PCMD CLMA1.PCMD
#define CLMA1PS CLMA1.PS
#define CLMA1EMU0 CLMA1.EMU0
#define CLMA2CTL0 CLMA2.CTL0
#define CLMA2CMPL CLMA2.CMPL
#define CLMA2CMPH CLMA2.CMPH
#define CLMA2PCMD CLMA2.PCMD
#define CLMA2PS CLMA2.PS
#define CLMA2EMU0 CLMA2.EMU0
#define CLMA3CTL0 CLMA3.CTL0
#define CLMA3CMPL CLMA3.CMPL
#define CLMA3CMPH CLMA3.CMPH
#define CLMA3PCMD CLMA3.PCMD
#define CLMA3PS CLMA3.PS
#define CLMA3EMU0 CLMA3.EMU0
#define FSGD4APROT00 FSGD4A.PROT00.ui32
#define FSGD4APROT00L FSGD4A.PROT00.ui16[0]
#define FSGD4APROT00LL FSGD4A.PROT00.ui8[0]
#define FSGD4APROT00LH FSGD4A.PROT00.ui8[1]
#define FSGD4APROT00H FSGD4A.PROT00.ui16[1]
#define FSGD4APROT00HL FSGD4A.PROT00.ui8[2]
#define FSGD4APROT00HH FSGD4A.PROT00.ui8[3]
#define FSGD4ASPID00 FSGD4A.SPID00.ui32
#define FSGD4ASPID00L FSGD4A.SPID00.ui16[0]
#define FSGD4ASPID00LL FSGD4A.SPID00.ui8[0]
#define FSGD4ASPID00LH FSGD4A.SPID00.ui8[1]
#define FSGD4ASPID00H FSGD4A.SPID00.ui16[1]
#define FSGD4ASPID00HL FSGD4A.SPID00.ui8[2]
#define FSGD4ASPID00HH FSGD4A.SPID00.ui8[3]
#define FSGD4APROT01 FSGD4A.PROT01.ui32
#define FSGD4APROT01L FSGD4A.PROT01.ui16[0]
#define FSGD4APROT01LL FSGD4A.PROT01.ui8[0]
#define FSGD4APROT01LH FSGD4A.PROT01.ui8[1]
#define FSGD4APROT01H FSGD4A.PROT01.ui16[1]
#define FSGD4APROT01HL FSGD4A.PROT01.ui8[2]
#define FSGD4APROT01HH FSGD4A.PROT01.ui8[3]
#define FSGD4ASPID01 FSGD4A.SPID01.ui32
#define FSGD4ASPID01L FSGD4A.SPID01.ui16[0]
#define FSGD4ASPID01LL FSGD4A.SPID01.ui8[0]
#define FSGD4ASPID01LH FSGD4A.SPID01.ui8[1]
#define FSGD4ASPID01H FSGD4A.SPID01.ui16[1]
#define FSGD4ASPID01HL FSGD4A.SPID01.ui8[2]
#define FSGD4ASPID01HH FSGD4A.SPID01.ui8[3]
#define FSGD4APROT02 FSGD4A.PROT02.ui32
#define FSGD4APROT02L FSGD4A.PROT02.ui16[0]
#define FSGD4APROT02LL FSGD4A.PROT02.ui8[0]
#define FSGD4APROT02LH FSGD4A.PROT02.ui8[1]
#define FSGD4APROT02H FSGD4A.PROT02.ui16[1]
#define FSGD4APROT02HL FSGD4A.PROT02.ui8[2]
#define FSGD4APROT02HH FSGD4A.PROT02.ui8[3]
#define FSGD4ASPID02 FSGD4A.SPID02.ui32
#define FSGD4ASPID02L FSGD4A.SPID02.ui16[0]
#define FSGD4ASPID02LL FSGD4A.SPID02.ui8[0]
#define FSGD4ASPID02LH FSGD4A.SPID02.ui8[1]
#define FSGD4ASPID02H FSGD4A.SPID02.ui16[1]
#define FSGD4ASPID02HL FSGD4A.SPID02.ui8[2]
#define FSGD4ASPID02HH FSGD4A.SPID02.ui8[3]
#define FSGD4APROT03 FSGD4A.PROT03.ui32
#define FSGD4APROT03L FSGD4A.PROT03.ui16[0]
#define FSGD4APROT03LL FSGD4A.PROT03.ui8[0]
#define FSGD4APROT03LH FSGD4A.PROT03.ui8[1]
#define FSGD4APROT03H FSGD4A.PROT03.ui16[1]
#define FSGD4APROT03HL FSGD4A.PROT03.ui8[2]
#define FSGD4APROT03HH FSGD4A.PROT03.ui8[3]
#define FSGD4ASPID03 FSGD4A.SPID03.ui32
#define FSGD4ASPID03L FSGD4A.SPID03.ui16[0]
#define FSGD4ASPID03LL FSGD4A.SPID03.ui8[0]
#define FSGD4ASPID03LH FSGD4A.SPID03.ui8[1]
#define FSGD4ASPID03H FSGD4A.SPID03.ui16[1]
#define FSGD4ASPID03HL FSGD4A.SPID03.ui8[2]
#define FSGD4ASPID03HH FSGD4A.SPID03.ui8[3]
#define FSGD4APROT04 FSGD4A.PROT04.ui32
#define FSGD4APROT04L FSGD4A.PROT04.ui16[0]
#define FSGD4APROT04LL FSGD4A.PROT04.ui8[0]
#define FSGD4APROT04LH FSGD4A.PROT04.ui8[1]
#define FSGD4APROT04H FSGD4A.PROT04.ui16[1]
#define FSGD4APROT04HL FSGD4A.PROT04.ui8[2]
#define FSGD4APROT04HH FSGD4A.PROT04.ui8[3]
#define FSGD4ASPID04 FSGD4A.SPID04.ui32
#define FSGD4ASPID04L FSGD4A.SPID04.ui16[0]
#define FSGD4ASPID04LL FSGD4A.SPID04.ui8[0]
#define FSGD4ASPID04LH FSGD4A.SPID04.ui8[1]
#define FSGD4ASPID04H FSGD4A.SPID04.ui16[1]
#define FSGD4ASPID04HL FSGD4A.SPID04.ui8[2]
#define FSGD4ASPID04HH FSGD4A.SPID04.ui8[3]
#define FSGD4APROT05 FSGD4A.PROT05.ui32
#define FSGD4APROT05L FSGD4A.PROT05.ui16[0]
#define FSGD4APROT05LL FSGD4A.PROT05.ui8[0]
#define FSGD4APROT05LH FSGD4A.PROT05.ui8[1]
#define FSGD4APROT05H FSGD4A.PROT05.ui16[1]
#define FSGD4APROT05HL FSGD4A.PROT05.ui8[2]
#define FSGD4APROT05HH FSGD4A.PROT05.ui8[3]
#define FSGD4ASPID05 FSGD4A.SPID05.ui32
#define FSGD4ASPID05L FSGD4A.SPID05.ui16[0]
#define FSGD4ASPID05LL FSGD4A.SPID05.ui8[0]
#define FSGD4ASPID05LH FSGD4A.SPID05.ui8[1]
#define FSGD4ASPID05H FSGD4A.SPID05.ui16[1]
#define FSGD4ASPID05HL FSGD4A.SPID05.ui8[2]
#define FSGD4ASPID05HH FSGD4A.SPID05.ui8[3]
#define FSGD4APROT06 FSGD4A.PROT06.ui32
#define FSGD4APROT06L FSGD4A.PROT06.ui16[0]
#define FSGD4APROT06LL FSGD4A.PROT06.ui8[0]
#define FSGD4APROT06LH FSGD4A.PROT06.ui8[1]
#define FSGD4APROT06H FSGD4A.PROT06.ui16[1]
#define FSGD4APROT06HL FSGD4A.PROT06.ui8[2]
#define FSGD4APROT06HH FSGD4A.PROT06.ui8[3]
#define FSGD4ASPID06 FSGD4A.SPID06.ui32
#define FSGD4ASPID06L FSGD4A.SPID06.ui16[0]
#define FSGD4ASPID06LL FSGD4A.SPID06.ui8[0]
#define FSGD4ASPID06LH FSGD4A.SPID06.ui8[1]
#define FSGD4ASPID06H FSGD4A.SPID06.ui16[1]
#define FSGD4ASPID06HL FSGD4A.SPID06.ui8[2]
#define FSGD4ASPID06HH FSGD4A.SPID06.ui8[3]
#define FSGD4APROT07 FSGD4A.PROT07.ui32
#define FSGD4APROT07L FSGD4A.PROT07.ui16[0]
#define FSGD4APROT07LL FSGD4A.PROT07.ui8[0]
#define FSGD4APROT07LH FSGD4A.PROT07.ui8[1]
#define FSGD4APROT07H FSGD4A.PROT07.ui16[1]
#define FSGD4APROT07HL FSGD4A.PROT07.ui8[2]
#define FSGD4APROT07HH FSGD4A.PROT07.ui8[3]
#define FSGD4ASPID07 FSGD4A.SPID07.ui32
#define FSGD4ASPID07L FSGD4A.SPID07.ui16[0]
#define FSGD4ASPID07LL FSGD4A.SPID07.ui8[0]
#define FSGD4ASPID07LH FSGD4A.SPID07.ui8[1]
#define FSGD4ASPID07H FSGD4A.SPID07.ui16[1]
#define FSGD4ASPID07HL FSGD4A.SPID07.ui8[2]
#define FSGD4ASPID07HH FSGD4A.SPID07.ui8[3]
#define FSGD4APROT10 FSGD4A.PROT10.ui32
#define FSGD4APROT10L FSGD4A.PROT10.ui16[0]
#define FSGD4APROT10LL FSGD4A.PROT10.ui8[0]
#define FSGD4APROT10LH FSGD4A.PROT10.ui8[1]
#define FSGD4APROT10H FSGD4A.PROT10.ui16[1]
#define FSGD4APROT10HL FSGD4A.PROT10.ui8[2]
#define FSGD4APROT10HH FSGD4A.PROT10.ui8[3]
#define FSGD4ASPID10 FSGD4A.SPID10.ui32
#define FSGD4ASPID10L FSGD4A.SPID10.ui16[0]
#define FSGD4ASPID10LL FSGD4A.SPID10.ui8[0]
#define FSGD4ASPID10LH FSGD4A.SPID10.ui8[1]
#define FSGD4ASPID10H FSGD4A.SPID10.ui16[1]
#define FSGD4ASPID10HL FSGD4A.SPID10.ui8[2]
#define FSGD4ASPID10HH FSGD4A.SPID10.ui8[3]
#define FSGD4APROT11 FSGD4A.PROT11.ui32
#define FSGD4APROT11L FSGD4A.PROT11.ui16[0]
#define FSGD4APROT11LL FSGD4A.PROT11.ui8[0]
#define FSGD4APROT11LH FSGD4A.PROT11.ui8[1]
#define FSGD4APROT11H FSGD4A.PROT11.ui16[1]
#define FSGD4APROT11HL FSGD4A.PROT11.ui8[2]
#define FSGD4APROT11HH FSGD4A.PROT11.ui8[3]
#define FSGD4ASPID11 FSGD4A.SPID11.ui32
#define FSGD4ASPID11L FSGD4A.SPID11.ui16[0]
#define FSGD4ASPID11LL FSGD4A.SPID11.ui8[0]
#define FSGD4ASPID11LH FSGD4A.SPID11.ui8[1]
#define FSGD4ASPID11H FSGD4A.SPID11.ui16[1]
#define FSGD4ASPID11HL FSGD4A.SPID11.ui8[2]
#define FSGD4ASPID11HH FSGD4A.SPID11.ui8[3]
#define FSGD4APROT12 FSGD4A.PROT12.ui32
#define FSGD4APROT12L FSGD4A.PROT12.ui16[0]
#define FSGD4APROT12LL FSGD4A.PROT12.ui8[0]
#define FSGD4APROT12LH FSGD4A.PROT12.ui8[1]
#define FSGD4APROT12H FSGD4A.PROT12.ui16[1]
#define FSGD4APROT12HL FSGD4A.PROT12.ui8[2]
#define FSGD4APROT12HH FSGD4A.PROT12.ui8[3]
#define FSGD4ASPID12 FSGD4A.SPID12.ui32
#define FSGD4ASPID12L FSGD4A.SPID12.ui16[0]
#define FSGD4ASPID12LL FSGD4A.SPID12.ui8[0]
#define FSGD4ASPID12LH FSGD4A.SPID12.ui8[1]
#define FSGD4ASPID12H FSGD4A.SPID12.ui16[1]
#define FSGD4ASPID12HL FSGD4A.SPID12.ui8[2]
#define FSGD4ASPID12HH FSGD4A.SPID12.ui8[3]
#define FSGD4APROT13 FSGD4A.PROT13.ui32
#define FSGD4APROT13L FSGD4A.PROT13.ui16[0]
#define FSGD4APROT13LL FSGD4A.PROT13.ui8[0]
#define FSGD4APROT13LH FSGD4A.PROT13.ui8[1]
#define FSGD4APROT13H FSGD4A.PROT13.ui16[1]
#define FSGD4APROT13HL FSGD4A.PROT13.ui8[2]
#define FSGD4APROT13HH FSGD4A.PROT13.ui8[3]
#define FSGD4ASPID13 FSGD4A.SPID13.ui32
#define FSGD4ASPID13L FSGD4A.SPID13.ui16[0]
#define FSGD4ASPID13LL FSGD4A.SPID13.ui8[0]
#define FSGD4ASPID13LH FSGD4A.SPID13.ui8[1]
#define FSGD4ASPID13H FSGD4A.SPID13.ui16[1]
#define FSGD4ASPID13HL FSGD4A.SPID13.ui8[2]
#define FSGD4ASPID13HH FSGD4A.SPID13.ui8[3]
#define FSGD4APROT14 FSGD4A.PROT14.ui32
#define FSGD4APROT14L FSGD4A.PROT14.ui16[0]
#define FSGD4APROT14LL FSGD4A.PROT14.ui8[0]
#define FSGD4APROT14LH FSGD4A.PROT14.ui8[1]
#define FSGD4APROT14H FSGD4A.PROT14.ui16[1]
#define FSGD4APROT14HL FSGD4A.PROT14.ui8[2]
#define FSGD4APROT14HH FSGD4A.PROT14.ui8[3]
#define FSGD4ASPID14 FSGD4A.SPID14.ui32
#define FSGD4ASPID14L FSGD4A.SPID14.ui16[0]
#define FSGD4ASPID14LL FSGD4A.SPID14.ui8[0]
#define FSGD4ASPID14LH FSGD4A.SPID14.ui8[1]
#define FSGD4ASPID14H FSGD4A.SPID14.ui16[1]
#define FSGD4ASPID14HL FSGD4A.SPID14.ui8[2]
#define FSGD4ASPID14HH FSGD4A.SPID14.ui8[3]
#define FSGD4APROT15 FSGD4A.PROT15.ui32
#define FSGD4APROT15L FSGD4A.PROT15.ui16[0]
#define FSGD4APROT15LL FSGD4A.PROT15.ui8[0]
#define FSGD4APROT15LH FSGD4A.PROT15.ui8[1]
#define FSGD4APROT15H FSGD4A.PROT15.ui16[1]
#define FSGD4APROT15HL FSGD4A.PROT15.ui8[2]
#define FSGD4APROT15HH FSGD4A.PROT15.ui8[3]
#define FSGD4ASPID15 FSGD4A.SPID15.ui32
#define FSGD4ASPID15L FSGD4A.SPID15.ui16[0]
#define FSGD4ASPID15LL FSGD4A.SPID15.ui8[0]
#define FSGD4ASPID15LH FSGD4A.SPID15.ui8[1]
#define FSGD4ASPID15H FSGD4A.SPID15.ui16[1]
#define FSGD4ASPID15HL FSGD4A.SPID15.ui8[2]
#define FSGD4ASPID15HH FSGD4A.SPID15.ui8[3]
#define ERRSLV4CTL ERRSLV4.CTL
#define ERRSLV4STAT ERRSLV4.STAT
#define ERRSLV4TYPE ERRSLV4.TYPE
#define FSGD4BPROT00 FSGD4B.PROT00.ui32
#define FSGD4BPROT00L FSGD4B.PROT00.ui16[0]
#define FSGD4BPROT00LL FSGD4B.PROT00.ui8[0]
#define FSGD4BPROT00LH FSGD4B.PROT00.ui8[1]
#define FSGD4BPROT00H FSGD4B.PROT00.ui16[1]
#define FSGD4BPROT00HL FSGD4B.PROT00.ui8[2]
#define FSGD4BPROT00HH FSGD4B.PROT00.ui8[3]
#define FSGD4BSPID00 FSGD4B.SPID00.ui32
#define FSGD4BSPID00L FSGD4B.SPID00.ui16[0]
#define FSGD4BSPID00LL FSGD4B.SPID00.ui8[0]
#define FSGD4BSPID00LH FSGD4B.SPID00.ui8[1]
#define FSGD4BSPID00H FSGD4B.SPID00.ui16[1]
#define FSGD4BSPID00HL FSGD4B.SPID00.ui8[2]
#define FSGD4BSPID00HH FSGD4B.SPID00.ui8[3]
#define FSGD4BPROT01 FSGD4B.PROT01.ui32
#define FSGD4BPROT01L FSGD4B.PROT01.ui16[0]
#define FSGD4BPROT01LL FSGD4B.PROT01.ui8[0]
#define FSGD4BPROT01LH FSGD4B.PROT01.ui8[1]
#define FSGD4BPROT01H FSGD4B.PROT01.ui16[1]
#define FSGD4BPROT01HL FSGD4B.PROT01.ui8[2]
#define FSGD4BPROT01HH FSGD4B.PROT01.ui8[3]
#define FSGD4BSPID01 FSGD4B.SPID01.ui32
#define FSGD4BSPID01L FSGD4B.SPID01.ui16[0]
#define FSGD4BSPID01LL FSGD4B.SPID01.ui8[0]
#define FSGD4BSPID01LH FSGD4B.SPID01.ui8[1]
#define FSGD4BSPID01H FSGD4B.SPID01.ui16[1]
#define FSGD4BSPID01HL FSGD4B.SPID01.ui8[2]
#define FSGD4BSPID01HH FSGD4B.SPID01.ui8[3]
#define FSGD4BPROT02 FSGD4B.PROT02.ui32
#define FSGD4BPROT02L FSGD4B.PROT02.ui16[0]
#define FSGD4BPROT02LL FSGD4B.PROT02.ui8[0]
#define FSGD4BPROT02LH FSGD4B.PROT02.ui8[1]
#define FSGD4BPROT02H FSGD4B.PROT02.ui16[1]
#define FSGD4BPROT02HL FSGD4B.PROT02.ui8[2]
#define FSGD4BPROT02HH FSGD4B.PROT02.ui8[3]
#define FSGD4BSPID02 FSGD4B.SPID02.ui32
#define FSGD4BSPID02L FSGD4B.SPID02.ui16[0]
#define FSGD4BSPID02LL FSGD4B.SPID02.ui8[0]
#define FSGD4BSPID02LH FSGD4B.SPID02.ui8[1]
#define FSGD4BSPID02H FSGD4B.SPID02.ui16[1]
#define FSGD4BSPID02HL FSGD4B.SPID02.ui8[2]
#define FSGD4BSPID02HH FSGD4B.SPID02.ui8[3]
#define FSGD4BPROT03 FSGD4B.PROT03.ui32
#define FSGD4BPROT03L FSGD4B.PROT03.ui16[0]
#define FSGD4BPROT03LL FSGD4B.PROT03.ui8[0]
#define FSGD4BPROT03LH FSGD4B.PROT03.ui8[1]
#define FSGD4BPROT03H FSGD4B.PROT03.ui16[1]
#define FSGD4BPROT03HL FSGD4B.PROT03.ui8[2]
#define FSGD4BPROT03HH FSGD4B.PROT03.ui8[3]
#define FSGD4BSPID03 FSGD4B.SPID03.ui32
#define FSGD4BSPID03L FSGD4B.SPID03.ui16[0]
#define FSGD4BSPID03LL FSGD4B.SPID03.ui8[0]
#define FSGD4BSPID03LH FSGD4B.SPID03.ui8[1]
#define FSGD4BSPID03H FSGD4B.SPID03.ui16[1]
#define FSGD4BSPID03HL FSGD4B.SPID03.ui8[2]
#define FSGD4BSPID03HH FSGD4B.SPID03.ui8[3]
#define FSGD4BPROT06 FSGD4B.PROT06.ui32
#define FSGD4BPROT06L FSGD4B.PROT06.ui16[0]
#define FSGD4BPROT06LL FSGD4B.PROT06.ui8[0]
#define FSGD4BPROT06LH FSGD4B.PROT06.ui8[1]
#define FSGD4BPROT06H FSGD4B.PROT06.ui16[1]
#define FSGD4BPROT06HL FSGD4B.PROT06.ui8[2]
#define FSGD4BPROT06HH FSGD4B.PROT06.ui8[3]
#define FSGD4BSPID06 FSGD4B.SPID06.ui32
#define FSGD4BSPID06L FSGD4B.SPID06.ui16[0]
#define FSGD4BSPID06LL FSGD4B.SPID06.ui8[0]
#define FSGD4BSPID06LH FSGD4B.SPID06.ui8[1]
#define FSGD4BSPID06H FSGD4B.SPID06.ui16[1]
#define FSGD4BSPID06HL FSGD4B.SPID06.ui8[2]
#define FSGD4BSPID06HH FSGD4B.SPID06.ui8[3]
#define FSGD4BPROT07 FSGD4B.PROT07.ui32
#define FSGD4BPROT07L FSGD4B.PROT07.ui16[0]
#define FSGD4BPROT07LL FSGD4B.PROT07.ui8[0]
#define FSGD4BPROT07LH FSGD4B.PROT07.ui8[1]
#define FSGD4BPROT07H FSGD4B.PROT07.ui16[1]
#define FSGD4BPROT07HL FSGD4B.PROT07.ui8[2]
#define FSGD4BPROT07HH FSGD4B.PROT07.ui8[3]
#define FSGD4BSPID07 FSGD4B.SPID07.ui32
#define FSGD4BSPID07L FSGD4B.SPID07.ui16[0]
#define FSGD4BSPID07LL FSGD4B.SPID07.ui8[0]
#define FSGD4BSPID07LH FSGD4B.SPID07.ui8[1]
#define FSGD4BSPID07H FSGD4B.SPID07.ui16[1]
#define FSGD4BSPID07HL FSGD4B.SPID07.ui8[2]
#define FSGD4BSPID07HH FSGD4B.SPID07.ui8[3]
#define FSGD4BPROT08 FSGD4B.PROT08.ui32
#define FSGD4BPROT08L FSGD4B.PROT08.ui16[0]
#define FSGD4BPROT08LL FSGD4B.PROT08.ui8[0]
#define FSGD4BPROT08LH FSGD4B.PROT08.ui8[1]
#define FSGD4BPROT08H FSGD4B.PROT08.ui16[1]
#define FSGD4BPROT08HL FSGD4B.PROT08.ui8[2]
#define FSGD4BPROT08HH FSGD4B.PROT08.ui8[3]
#define FSGD4BSPID08 FSGD4B.SPID08.ui32
#define FSGD4BSPID08L FSGD4B.SPID08.ui16[0]
#define FSGD4BSPID08LL FSGD4B.SPID08.ui8[0]
#define FSGD4BSPID08LH FSGD4B.SPID08.ui8[1]
#define FSGD4BSPID08H FSGD4B.SPID08.ui16[1]
#define FSGD4BSPID08HL FSGD4B.SPID08.ui8[2]
#define FSGD4BSPID08HH FSGD4B.SPID08.ui8[3]
#define FSGD4BPROT09 FSGD4B.PROT09.ui32
#define FSGD4BPROT09L FSGD4B.PROT09.ui16[0]
#define FSGD4BPROT09LL FSGD4B.PROT09.ui8[0]
#define FSGD4BPROT09LH FSGD4B.PROT09.ui8[1]
#define FSGD4BPROT09H FSGD4B.PROT09.ui16[1]
#define FSGD4BPROT09HL FSGD4B.PROT09.ui8[2]
#define FSGD4BPROT09HH FSGD4B.PROT09.ui8[3]
#define FSGD4BSPID09 FSGD4B.SPID09.ui32
#define FSGD4BSPID09L FSGD4B.SPID09.ui16[0]
#define FSGD4BSPID09LL FSGD4B.SPID09.ui8[0]
#define FSGD4BSPID09LH FSGD4B.SPID09.ui8[1]
#define FSGD4BSPID09H FSGD4B.SPID09.ui16[1]
#define FSGD4BSPID09HL FSGD4B.SPID09.ui8[2]
#define FSGD4BSPID09HH FSGD4B.SPID09.ui8[3]
#define FSGD4BPROT10 FSGD4B.PROT10.ui32
#define FSGD4BPROT10L FSGD4B.PROT10.ui16[0]
#define FSGD4BPROT10LL FSGD4B.PROT10.ui8[0]
#define FSGD4BPROT10LH FSGD4B.PROT10.ui8[1]
#define FSGD4BPROT10H FSGD4B.PROT10.ui16[1]
#define FSGD4BPROT10HL FSGD4B.PROT10.ui8[2]
#define FSGD4BPROT10HH FSGD4B.PROT10.ui8[3]
#define FSGD4BSPID10 FSGD4B.SPID10.ui32
#define FSGD4BSPID10L FSGD4B.SPID10.ui16[0]
#define FSGD4BSPID10LL FSGD4B.SPID10.ui8[0]
#define FSGD4BSPID10LH FSGD4B.SPID10.ui8[1]
#define FSGD4BSPID10H FSGD4B.SPID10.ui16[1]
#define FSGD4BSPID10HL FSGD4B.SPID10.ui8[2]
#define FSGD4BSPID10HH FSGD4B.SPID10.ui8[3]
#define FSGD4BPROT11 FSGD4B.PROT11.ui32
#define FSGD4BPROT11L FSGD4B.PROT11.ui16[0]
#define FSGD4BPROT11LL FSGD4B.PROT11.ui8[0]
#define FSGD4BPROT11LH FSGD4B.PROT11.ui8[1]
#define FSGD4BPROT11H FSGD4B.PROT11.ui16[1]
#define FSGD4BPROT11HL FSGD4B.PROT11.ui8[2]
#define FSGD4BPROT11HH FSGD4B.PROT11.ui8[3]
#define FSGD4BSPID11 FSGD4B.SPID11.ui32
#define FSGD4BSPID11L FSGD4B.SPID11.ui16[0]
#define FSGD4BSPID11LL FSGD4B.SPID11.ui8[0]
#define FSGD4BSPID11LH FSGD4B.SPID11.ui8[1]
#define FSGD4BSPID11H FSGD4B.SPID11.ui16[1]
#define FSGD4BSPID11HL FSGD4B.SPID11.ui8[2]
#define FSGD4BSPID11HH FSGD4B.SPID11.ui8[3]
#define FSGD4BPROT12 FSGD4B.PROT12.ui32
#define FSGD4BPROT12L FSGD4B.PROT12.ui16[0]
#define FSGD4BPROT12LL FSGD4B.PROT12.ui8[0]
#define FSGD4BPROT12LH FSGD4B.PROT12.ui8[1]
#define FSGD4BPROT12H FSGD4B.PROT12.ui16[1]
#define FSGD4BPROT12HL FSGD4B.PROT12.ui8[2]
#define FSGD4BPROT12HH FSGD4B.PROT12.ui8[3]
#define FSGD4BSPID12 FSGD4B.SPID12.ui32
#define FSGD4BSPID12L FSGD4B.SPID12.ui16[0]
#define FSGD4BSPID12LL FSGD4B.SPID12.ui8[0]
#define FSGD4BSPID12LH FSGD4B.SPID12.ui8[1]
#define FSGD4BSPID12H FSGD4B.SPID12.ui16[1]
#define FSGD4BSPID12HL FSGD4B.SPID12.ui8[2]
#define FSGD4BSPID12HH FSGD4B.SPID12.ui8[3]
#define FSGD4BPROT13 FSGD4B.PROT13.ui32
#define FSGD4BPROT13L FSGD4B.PROT13.ui16[0]
#define FSGD4BPROT13LL FSGD4B.PROT13.ui8[0]
#define FSGD4BPROT13LH FSGD4B.PROT13.ui8[1]
#define FSGD4BPROT13H FSGD4B.PROT13.ui16[1]
#define FSGD4BPROT13HL FSGD4B.PROT13.ui8[2]
#define FSGD4BPROT13HH FSGD4B.PROT13.ui8[3]
#define FSGD4BSPID13 FSGD4B.SPID13.ui32
#define FSGD4BSPID13L FSGD4B.SPID13.ui16[0]
#define FSGD4BSPID13LL FSGD4B.SPID13.ui8[0]
#define FSGD4BSPID13LH FSGD4B.SPID13.ui8[1]
#define FSGD4BSPID13H FSGD4B.SPID13.ui16[1]
#define FSGD4BSPID13HL FSGD4B.SPID13.ui8[2]
#define FSGD4BSPID13HH FSGD4B.SPID13.ui8[3]
#define ERRSLV4AICTL ERRSLV4AI.CTL
#define ERRSLV4AISTAT ERRSLV4AI.STAT
#define ERRSLV4AITYPE ERRSLV4AI.TYPE
#define ADCF0VCR0 ADCF0.VCR0
#define ADCF0VCR1 ADCF0.VCR1
#define ADCF0VCR2 ADCF0.VCR2
#define ADCF0VCR3 ADCF0.VCR3
#define ADCF0VCR4 ADCF0.VCR4
#define ADCF0VCR5 ADCF0.VCR5
#define ADCF0VCR6 ADCF0.VCR6
#define ADCF0VCR7 ADCF0.VCR7
#define ADCF0VCR8 ADCF0.VCR8
#define ADCF0VCR9 ADCF0.VCR9
#define ADCF0VCR10 ADCF0.VCR10
#define ADCF0VCR11 ADCF0.VCR11
#define ADCF0VCR12 ADCF0.VCR12
#define ADCF0VCR13 ADCF0.VCR13
#define ADCF0VCR14 ADCF0.VCR14
#define ADCF0VCR15 ADCF0.VCR15
#define ADCF0VCR16 ADCF0.VCR16
#define ADCF0VCR17 ADCF0.VCR17
#define ADCF0VCR18 ADCF0.VCR18
#define ADCF0VCR19 ADCF0.VCR19
#define ADCF0VCR20 ADCF0.VCR20
#define ADCF0VCR21 ADCF0.VCR21
#define ADCF0VCR22 ADCF0.VCR22
#define ADCF0VCR23 ADCF0.VCR23
#define ADCF0VCR24 ADCF0.VCR24
#define ADCF0VCR25 ADCF0.VCR25
#define ADCF0VCR26 ADCF0.VCR26
#define ADCF0VCR27 ADCF0.VCR27
#define ADCF0VCR28 ADCF0.VCR28
#define ADCF0VCR29 ADCF0.VCR29
#define ADCF0VCR30 ADCF0.VCR30
#define ADCF0VCR31 ADCF0.VCR31
#define ADCF0DR00 ADCF0.DR00
#define ADCF0DR02 ADCF0.DR02
#define ADCF0DR04 ADCF0.DR04
#define ADCF0DR06 ADCF0.DR06
#define ADCF0DR08 ADCF0.DR08
#define ADCF0DR10 ADCF0.DR10
#define ADCF0DR12 ADCF0.DR12
#define ADCF0DR14 ADCF0.DR14
#define ADCF0DR16 ADCF0.DR16
#define ADCF0DR18 ADCF0.DR18
#define ADCF0DR20 ADCF0.DR20
#define ADCF0DR22 ADCF0.DR22
#define ADCF0DR24 ADCF0.DR24
#define ADCF0DR26 ADCF0.DR26
#define ADCF0DR28 ADCF0.DR28
#define ADCF0DR30 ADCF0.DR30
#define ADCF0DIR0 ADCF0.DIR0
#define ADCF0DIR1 ADCF0.DIR1
#define ADCF0DIR2 ADCF0.DIR2
#define ADCF0DIR3 ADCF0.DIR3
#define ADCF0DIR4 ADCF0.DIR4
#define ADCF0DIR5 ADCF0.DIR5
#define ADCF0DIR6 ADCF0.DIR6
#define ADCF0DIR7 ADCF0.DIR7
#define ADCF0DIR8 ADCF0.DIR8
#define ADCF0DIR9 ADCF0.DIR9
#define ADCF0DIR10 ADCF0.DIR10
#define ADCF0DIR11 ADCF0.DIR11
#define ADCF0DIR12 ADCF0.DIR12
#define ADCF0DIR13 ADCF0.DIR13
#define ADCF0DIR14 ADCF0.DIR14
#define ADCF0DIR15 ADCF0.DIR15
#define ADCF0DIR16 ADCF0.DIR16
#define ADCF0DIR17 ADCF0.DIR17
#define ADCF0DIR18 ADCF0.DIR18
#define ADCF0DIR19 ADCF0.DIR19
#define ADCF0DIR20 ADCF0.DIR20
#define ADCF0DIR21 ADCF0.DIR21
#define ADCF0DIR22 ADCF0.DIR22
#define ADCF0DIR23 ADCF0.DIR23
#define ADCF0DIR24 ADCF0.DIR24
#define ADCF0DIR25 ADCF0.DIR25
#define ADCF0DIR26 ADCF0.DIR26
#define ADCF0DIR27 ADCF0.DIR27
#define ADCF0DIR28 ADCF0.DIR28
#define ADCF0DIR29 ADCF0.DIR29
#define ADCF0DIR30 ADCF0.DIR30
#define ADCF0DIR31 ADCF0.DIR31
#define ADCF0ADSYNSTCR ADCF0.ADSYNSTCR
#define ADCF0ADTSYNSTCR ADCF0.ADTSYNSTCR
#define ADCF0ADHALTR ADCF0.ADHALTR
#define ADCF0ADCR1 ADCF0.ADCR1
#define ADCF0MPXCURCR ADCF0.MPXCURCR
#define ADCF0MPXCURR ADCF0.MPXCURR
#define ADCF0MPXOWR ADCF0.MPXOWR
#define ADCF0ADCR2 ADCF0.ADCR2
#define ADCF0ADENDP0 ADCF0.ADENDP0
#define ADCF0SFTCR ADCF0.SFTCR
#define ADCF0TDCR ADCF0.TDCR
#define ADCF0ULLMTBR0 ADCF0.ULLMTBR0.ui32
#define ADCF0ULLMTBR0L ADCF0.ULLMTBR0.ui16[0]
#define ADCF0ULLMTBR0H ADCF0.ULLMTBR0.ui16[1]
#define ADCF0ULLMTBR1 ADCF0.ULLMTBR1.ui32
#define ADCF0ULLMTBR1L ADCF0.ULLMTBR1.ui16[0]
#define ADCF0ULLMTBR1H ADCF0.ULLMTBR1.ui16[1]
#define ADCF0ULLMTBR2 ADCF0.ULLMTBR2.ui32
#define ADCF0ULLMTBR2L ADCF0.ULLMTBR2.ui16[0]
#define ADCF0ULLMTBR2H ADCF0.ULLMTBR2.ui16[1]
#define ADCF0ECR ADCF0.ECR
#define ADCF0ULER ADCF0.ULER
#define ADCF0OWER ADCF0.OWER
#define ADCF0PER ADCF0.PER
#define ADCF0IDER ADCF0.IDER
#define ADCF0THSMPSTCR ADCF0.THSMPSTCR
#define ADCF0THSTPCR ADCF0.THSTPCR
#define ADCF0THCR ADCF0.THCR
#define ADCF0THAHLDSTCR ADCF0.THAHLDSTCR
#define ADCF0THBHLDSTCR ADCF0.THBHLDSTCR
#define ADCF0THACR ADCF0.THACR
#define ADCF0THBCR ADCF0.THBCR
#define ADCF0THER ADCF0.THER
#define ADCF0THGSR ADCF0.THGSR
#define ADCF0SGSTCR0 ADCF0.SGSTCR0
#define ADCF0SGCR0 ADCF0.SGCR0
#define ADCF0SGVCSP0 ADCF0.SGVCSP0
#define ADCF0SGVCEP0 ADCF0.SGVCEP0
#define ADCF0SGMCYCR0 ADCF0.SGMCYCR0
#define ADCF0SGSR0 ADCF0.SGSR0
#define ADCF0ULLMSR0 ADCF0.ULLMSR0
#define ADCF0SGSTCR1 ADCF0.SGSTCR1
#define ADCF0SGCR1 ADCF0.SGCR1
#define ADCF0SGVCSP1 ADCF0.SGVCSP1
#define ADCF0SGVCEP1 ADCF0.SGVCEP1
#define ADCF0SGMCYCR1 ADCF0.SGMCYCR1
#define ADCF0SGSR1 ADCF0.SGSR1
#define ADCF0ULLMSR1 ADCF0.ULLMSR1
#define ADCF0SGSTCR2 ADCF0.SGSTCR2
#define ADCF0SGCR2 ADCF0.SGCR2
#define ADCF0SGVCSP2 ADCF0.SGVCSP2
#define ADCF0SGVCEP2 ADCF0.SGVCEP2
#define ADCF0SGMCYCR2 ADCF0.SGMCYCR2
#define ADCF0SGSR2 ADCF0.SGSR2
#define ADCF0ULLMSR2 ADCF0.ULLMSR2
#define ADCF0SGSTCR3 ADCF0.SGSTCR3
#define ADCF0ADTSTCR3 ADCF0.ADTSTCR3
#define ADCF0ADTENDCR3 ADCF0.ADTENDCR3
#define ADCF0SGCR3 ADCF0.SGCR3
#define ADCF0SGVCSP3 ADCF0.SGVCSP3
#define ADCF0SGVCEP3 ADCF0.SGVCEP3
#define ADCF0SGMCYCR3 ADCF0.SGMCYCR3
#define ADCF0SGSR3 ADCF0.SGSR3
#define ADCF0ADTIPR3 ADCF0.ADTIPR3
#define ADCF0ADTPRR3 ADCF0.ADTPRR3
#define ADCF0ULLMSR3 ADCF0.ULLMSR3
#define ADCF0SGSTCR4 ADCF0.SGSTCR4
#define ADCF0ADTSTCR4 ADCF0.ADTSTCR4
#define ADCF0ADTENDCR4 ADCF0.ADTENDCR4
#define ADCF0SGCR4 ADCF0.SGCR4
#define ADCF0SGVCSP4 ADCF0.SGVCSP4
#define ADCF0SGVCEP4 ADCF0.SGVCEP4
#define ADCF0SGMCYCR4 ADCF0.SGMCYCR4
#define ADCF0SGSR4 ADCF0.SGSR4
#define ADCF0ADTIPR4 ADCF0.ADTIPR4
#define ADCF0ADTPRR4 ADCF0.ADTPRR4
#define ADCF0ULLMSR4 ADCF0.ULLMSR4
#define OTS0OTSTCR OTS0.OTSTCR
#define OTS0OTENDCR OTS0.OTENDCR
#define OTS0OTCR OTS0.OTCR
#define OTS0OTFCR OTS0.OTFCR
#define OTS0OTFR OTS0.OTFR
#define OTS0OTSTR OTS0.OTSTR
#define OTS0OTDR OTS0.OTDR
#define OTS0HTBRAU OTS0.HTBRAU
#define OTS0HTBRAL OTS0.HTBRAL
#define OTS0HTBRBU OTS0.HTBRBU
#define OTS0HTBRBL OTS0.HTBRBL
#define OTS0LTBRAU OTS0.LTBRAU
#define OTS0LTBRAL OTS0.LTBRAL
#define OTS0TDLR OTS0.TDLR
#define OTS0COEFFRA OTS0.COEFFRA
#define OTS0COEFFRB OTS0.COEFFRB
#define OTS0COEFFRC OTS0.COEFFRC
#define FSGD3APROT00 FSGD3A.PROT00.ui32
#define FSGD3APROT00L FSGD3A.PROT00.ui16[0]
#define FSGD3APROT00LL FSGD3A.PROT00.ui8[0]
#define FSGD3APROT00LH FSGD3A.PROT00.ui8[1]
#define FSGD3APROT00H FSGD3A.PROT00.ui16[1]
#define FSGD3APROT00HL FSGD3A.PROT00.ui8[2]
#define FSGD3APROT00HH FSGD3A.PROT00.ui8[3]
#define FSGD3ASPID00 FSGD3A.SPID00.ui32
#define FSGD3ASPID00L FSGD3A.SPID00.ui16[0]
#define FSGD3ASPID00LL FSGD3A.SPID00.ui8[0]
#define FSGD3ASPID00LH FSGD3A.SPID00.ui8[1]
#define FSGD3ASPID00H FSGD3A.SPID00.ui16[1]
#define FSGD3ASPID00HL FSGD3A.SPID00.ui8[2]
#define FSGD3ASPID00HH FSGD3A.SPID00.ui8[3]
#define FSGD3APROT01 FSGD3A.PROT01.ui32
#define FSGD3APROT01L FSGD3A.PROT01.ui16[0]
#define FSGD3APROT01LL FSGD3A.PROT01.ui8[0]
#define FSGD3APROT01LH FSGD3A.PROT01.ui8[1]
#define FSGD3APROT01H FSGD3A.PROT01.ui16[1]
#define FSGD3APROT01HL FSGD3A.PROT01.ui8[2]
#define FSGD3APROT01HH FSGD3A.PROT01.ui8[3]
#define FSGD3ASPID01 FSGD3A.SPID01.ui32
#define FSGD3ASPID01L FSGD3A.SPID01.ui16[0]
#define FSGD3ASPID01LL FSGD3A.SPID01.ui8[0]
#define FSGD3ASPID01LH FSGD3A.SPID01.ui8[1]
#define FSGD3ASPID01H FSGD3A.SPID01.ui16[1]
#define FSGD3ASPID01HL FSGD3A.SPID01.ui8[2]
#define FSGD3ASPID01HH FSGD3A.SPID01.ui8[3]
#define FSGD3APROT02 FSGD3A.PROT02.ui32
#define FSGD3APROT02L FSGD3A.PROT02.ui16[0]
#define FSGD3APROT02LL FSGD3A.PROT02.ui8[0]
#define FSGD3APROT02LH FSGD3A.PROT02.ui8[1]
#define FSGD3APROT02H FSGD3A.PROT02.ui16[1]
#define FSGD3APROT02HL FSGD3A.PROT02.ui8[2]
#define FSGD3APROT02HH FSGD3A.PROT02.ui8[3]
#define FSGD3ASPID02 FSGD3A.SPID02.ui32
#define FSGD3ASPID02L FSGD3A.SPID02.ui16[0]
#define FSGD3ASPID02LL FSGD3A.SPID02.ui8[0]
#define FSGD3ASPID02LH FSGD3A.SPID02.ui8[1]
#define FSGD3ASPID02H FSGD3A.SPID02.ui16[1]
#define FSGD3ASPID02HL FSGD3A.SPID02.ui8[2]
#define FSGD3ASPID02HH FSGD3A.SPID02.ui8[3]
#define FSGD3APROT03 FSGD3A.PROT03.ui32
#define FSGD3APROT03L FSGD3A.PROT03.ui16[0]
#define FSGD3APROT03LL FSGD3A.PROT03.ui8[0]
#define FSGD3APROT03LH FSGD3A.PROT03.ui8[1]
#define FSGD3APROT03H FSGD3A.PROT03.ui16[1]
#define FSGD3APROT03HL FSGD3A.PROT03.ui8[2]
#define FSGD3APROT03HH FSGD3A.PROT03.ui8[3]
#define FSGD3ASPID03 FSGD3A.SPID03.ui32
#define FSGD3ASPID03L FSGD3A.SPID03.ui16[0]
#define FSGD3ASPID03LL FSGD3A.SPID03.ui8[0]
#define FSGD3ASPID03LH FSGD3A.SPID03.ui8[1]
#define FSGD3ASPID03H FSGD3A.SPID03.ui16[1]
#define FSGD3ASPID03HL FSGD3A.SPID03.ui8[2]
#define FSGD3ASPID03HH FSGD3A.SPID03.ui8[3]
#define FSGD3APROT04 FSGD3A.PROT04.ui32
#define FSGD3APROT04L FSGD3A.PROT04.ui16[0]
#define FSGD3APROT04LL FSGD3A.PROT04.ui8[0]
#define FSGD3APROT04LH FSGD3A.PROT04.ui8[1]
#define FSGD3APROT04H FSGD3A.PROT04.ui16[1]
#define FSGD3APROT04HL FSGD3A.PROT04.ui8[2]
#define FSGD3APROT04HH FSGD3A.PROT04.ui8[3]
#define FSGD3ASPID04 FSGD3A.SPID04.ui32
#define FSGD3ASPID04L FSGD3A.SPID04.ui16[0]
#define FSGD3ASPID04LL FSGD3A.SPID04.ui8[0]
#define FSGD3ASPID04LH FSGD3A.SPID04.ui8[1]
#define FSGD3ASPID04H FSGD3A.SPID04.ui16[1]
#define FSGD3ASPID04HL FSGD3A.SPID04.ui8[2]
#define FSGD3ASPID04HH FSGD3A.SPID04.ui8[3]
#define FSGD3APROT05 FSGD3A.PROT05.ui32
#define FSGD3APROT05L FSGD3A.PROT05.ui16[0]
#define FSGD3APROT05LL FSGD3A.PROT05.ui8[0]
#define FSGD3APROT05LH FSGD3A.PROT05.ui8[1]
#define FSGD3APROT05H FSGD3A.PROT05.ui16[1]
#define FSGD3APROT05HL FSGD3A.PROT05.ui8[2]
#define FSGD3APROT05HH FSGD3A.PROT05.ui8[3]
#define FSGD3ASPID05 FSGD3A.SPID05.ui32
#define FSGD3ASPID05L FSGD3A.SPID05.ui16[0]
#define FSGD3ASPID05LL FSGD3A.SPID05.ui8[0]
#define FSGD3ASPID05LH FSGD3A.SPID05.ui8[1]
#define FSGD3ASPID05H FSGD3A.SPID05.ui16[1]
#define FSGD3ASPID05HL FSGD3A.SPID05.ui8[2]
#define FSGD3ASPID05HH FSGD3A.SPID05.ui8[3]
#define FSGD3APROT06 FSGD3A.PROT06.ui32
#define FSGD3APROT06L FSGD3A.PROT06.ui16[0]
#define FSGD3APROT06LL FSGD3A.PROT06.ui8[0]
#define FSGD3APROT06LH FSGD3A.PROT06.ui8[1]
#define FSGD3APROT06H FSGD3A.PROT06.ui16[1]
#define FSGD3APROT06HL FSGD3A.PROT06.ui8[2]
#define FSGD3APROT06HH FSGD3A.PROT06.ui8[3]
#define FSGD3ASPID06 FSGD3A.SPID06.ui32
#define FSGD3ASPID06L FSGD3A.SPID06.ui16[0]
#define FSGD3ASPID06LL FSGD3A.SPID06.ui8[0]
#define FSGD3ASPID06LH FSGD3A.SPID06.ui8[1]
#define FSGD3ASPID06H FSGD3A.SPID06.ui16[1]
#define FSGD3ASPID06HL FSGD3A.SPID06.ui8[2]
#define FSGD3ASPID06HH FSGD3A.SPID06.ui8[3]
#define FSGD3APROT07 FSGD3A.PROT07.ui32
#define FSGD3APROT07L FSGD3A.PROT07.ui16[0]
#define FSGD3APROT07LL FSGD3A.PROT07.ui8[0]
#define FSGD3APROT07LH FSGD3A.PROT07.ui8[1]
#define FSGD3APROT07H FSGD3A.PROT07.ui16[1]
#define FSGD3APROT07HL FSGD3A.PROT07.ui8[2]
#define FSGD3APROT07HH FSGD3A.PROT07.ui8[3]
#define FSGD3ASPID07 FSGD3A.SPID07.ui32
#define FSGD3ASPID07L FSGD3A.SPID07.ui16[0]
#define FSGD3ASPID07LL FSGD3A.SPID07.ui8[0]
#define FSGD3ASPID07LH FSGD3A.SPID07.ui8[1]
#define FSGD3ASPID07H FSGD3A.SPID07.ui16[1]
#define FSGD3ASPID07HL FSGD3A.SPID07.ui8[2]
#define FSGD3ASPID07HH FSGD3A.SPID07.ui8[3]
#define FSGD3APROT08 FSGD3A.PROT08.ui32
#define FSGD3APROT08L FSGD3A.PROT08.ui16[0]
#define FSGD3APROT08LL FSGD3A.PROT08.ui8[0]
#define FSGD3APROT08LH FSGD3A.PROT08.ui8[1]
#define FSGD3APROT08H FSGD3A.PROT08.ui16[1]
#define FSGD3APROT08HL FSGD3A.PROT08.ui8[2]
#define FSGD3APROT08HH FSGD3A.PROT08.ui8[3]
#define FSGD3ASPID08 FSGD3A.SPID08.ui32
#define FSGD3ASPID08L FSGD3A.SPID08.ui16[0]
#define FSGD3ASPID08LL FSGD3A.SPID08.ui8[0]
#define FSGD3ASPID08LH FSGD3A.SPID08.ui8[1]
#define FSGD3ASPID08H FSGD3A.SPID08.ui16[1]
#define FSGD3ASPID08HL FSGD3A.SPID08.ui8[2]
#define FSGD3ASPID08HH FSGD3A.SPID08.ui8[3]
#define FSGD3APROT09 FSGD3A.PROT09.ui32
#define FSGD3APROT09L FSGD3A.PROT09.ui16[0]
#define FSGD3APROT09LL FSGD3A.PROT09.ui8[0]
#define FSGD3APROT09LH FSGD3A.PROT09.ui8[1]
#define FSGD3APROT09H FSGD3A.PROT09.ui16[1]
#define FSGD3APROT09HL FSGD3A.PROT09.ui8[2]
#define FSGD3APROT09HH FSGD3A.PROT09.ui8[3]
#define FSGD3ASPID09 FSGD3A.SPID09.ui32
#define FSGD3ASPID09L FSGD3A.SPID09.ui16[0]
#define FSGD3ASPID09LL FSGD3A.SPID09.ui8[0]
#define FSGD3ASPID09LH FSGD3A.SPID09.ui8[1]
#define FSGD3ASPID09H FSGD3A.SPID09.ui16[1]
#define FSGD3ASPID09HL FSGD3A.SPID09.ui8[2]
#define FSGD3ASPID09HH FSGD3A.SPID09.ui8[3]
#define FSGD3APROT12 FSGD3A.PROT12.ui32
#define FSGD3APROT12L FSGD3A.PROT12.ui16[0]
#define FSGD3APROT12LL FSGD3A.PROT12.ui8[0]
#define FSGD3APROT12LH FSGD3A.PROT12.ui8[1]
#define FSGD3APROT12H FSGD3A.PROT12.ui16[1]
#define FSGD3APROT12HL FSGD3A.PROT12.ui8[2]
#define FSGD3APROT12HH FSGD3A.PROT12.ui8[3]
#define FSGD3ASPID12 FSGD3A.SPID12.ui32
#define FSGD3ASPID12L FSGD3A.SPID12.ui16[0]
#define FSGD3ASPID12LL FSGD3A.SPID12.ui8[0]
#define FSGD3ASPID12LH FSGD3A.SPID12.ui8[1]
#define FSGD3ASPID12H FSGD3A.SPID12.ui16[1]
#define FSGD3ASPID12HL FSGD3A.SPID12.ui8[2]
#define FSGD3ASPID12HH FSGD3A.SPID12.ui8[3]
#define FSGD3APROT13 FSGD3A.PROT13.ui32
#define FSGD3APROT13L FSGD3A.PROT13.ui16[0]
#define FSGD3APROT13LL FSGD3A.PROT13.ui8[0]
#define FSGD3APROT13LH FSGD3A.PROT13.ui8[1]
#define FSGD3APROT13H FSGD3A.PROT13.ui16[1]
#define FSGD3APROT13HL FSGD3A.PROT13.ui8[2]
#define FSGD3APROT13HH FSGD3A.PROT13.ui8[3]
#define FSGD3ASPID13 FSGD3A.SPID13.ui32
#define FSGD3ASPID13L FSGD3A.SPID13.ui16[0]
#define FSGD3ASPID13LL FSGD3A.SPID13.ui8[0]
#define FSGD3ASPID13LH FSGD3A.SPID13.ui8[1]
#define FSGD3ASPID13H FSGD3A.SPID13.ui16[1]
#define FSGD3ASPID13HL FSGD3A.SPID13.ui8[2]
#define FSGD3ASPID13HH FSGD3A.SPID13.ui8[3]
#define ERRSLV3CTL ERRSLV3.CTL
#define ERRSLV3STAT ERRSLV3.STAT
#define ERRSLV3TYPE ERRSLV3.TYPE
#define FSGD3BPROT00 FSGD3B.PROT00.ui32
#define FSGD3BPROT00L FSGD3B.PROT00.ui16[0]
#define FSGD3BPROT00LL FSGD3B.PROT00.ui8[0]
#define FSGD3BPROT00LH FSGD3B.PROT00.ui8[1]
#define FSGD3BPROT00H FSGD3B.PROT00.ui16[1]
#define FSGD3BPROT00HL FSGD3B.PROT00.ui8[2]
#define FSGD3BPROT00HH FSGD3B.PROT00.ui8[3]
#define FSGD3BSPID00 FSGD3B.SPID00.ui32
#define FSGD3BSPID00L FSGD3B.SPID00.ui16[0]
#define FSGD3BSPID00LL FSGD3B.SPID00.ui8[0]
#define FSGD3BSPID00LH FSGD3B.SPID00.ui8[1]
#define FSGD3BSPID00H FSGD3B.SPID00.ui16[1]
#define FSGD3BSPID00HL FSGD3B.SPID00.ui8[2]
#define FSGD3BSPID00HH FSGD3B.SPID00.ui8[3]
#define FSGD3BPROT01 FSGD3B.PROT01.ui32
#define FSGD3BPROT01L FSGD3B.PROT01.ui16[0]
#define FSGD3BPROT01LL FSGD3B.PROT01.ui8[0]
#define FSGD3BPROT01LH FSGD3B.PROT01.ui8[1]
#define FSGD3BPROT01H FSGD3B.PROT01.ui16[1]
#define FSGD3BPROT01HL FSGD3B.PROT01.ui8[2]
#define FSGD3BPROT01HH FSGD3B.PROT01.ui8[3]
#define FSGD3BSPID01 FSGD3B.SPID01.ui32
#define FSGD3BSPID01L FSGD3B.SPID01.ui16[0]
#define FSGD3BSPID01LL FSGD3B.SPID01.ui8[0]
#define FSGD3BSPID01LH FSGD3B.SPID01.ui8[1]
#define FSGD3BSPID01H FSGD3B.SPID01.ui16[1]
#define FSGD3BSPID01HL FSGD3B.SPID01.ui8[2]
#define FSGD3BSPID01HH FSGD3B.SPID01.ui8[3]
#define FSGD3BPROT10 FSGD3B.PROT10.ui32
#define FSGD3BPROT10L FSGD3B.PROT10.ui16[0]
#define FSGD3BPROT10LL FSGD3B.PROT10.ui8[0]
#define FSGD3BPROT10LH FSGD3B.PROT10.ui8[1]
#define FSGD3BPROT10H FSGD3B.PROT10.ui16[1]
#define FSGD3BPROT10HL FSGD3B.PROT10.ui8[2]
#define FSGD3BPROT10HH FSGD3B.PROT10.ui8[3]
#define FSGD3BSPID10 FSGD3B.SPID10.ui32
#define FSGD3BSPID10L FSGD3B.SPID10.ui16[0]
#define FSGD3BSPID10LL FSGD3B.SPID10.ui8[0]
#define FSGD3BSPID10LH FSGD3B.SPID10.ui8[1]
#define FSGD3BSPID10H FSGD3B.SPID10.ui16[1]
#define FSGD3BSPID10HL FSGD3B.SPID10.ui8[2]
#define FSGD3BSPID10HH FSGD3B.SPID10.ui8[3]
#define FSGD3BPROT11 FSGD3B.PROT11.ui32
#define FSGD3BPROT11L FSGD3B.PROT11.ui16[0]
#define FSGD3BPROT11LL FSGD3B.PROT11.ui8[0]
#define FSGD3BPROT11LH FSGD3B.PROT11.ui8[1]
#define FSGD3BPROT11H FSGD3B.PROT11.ui16[1]
#define FSGD3BPROT11HL FSGD3B.PROT11.ui8[2]
#define FSGD3BPROT11HH FSGD3B.PROT11.ui8[3]
#define FSGD3BSPID11 FSGD3B.SPID11.ui32
#define FSGD3BSPID11L FSGD3B.SPID11.ui16[0]
#define FSGD3BSPID11LL FSGD3B.SPID11.ui8[0]
#define FSGD3BSPID11LH FSGD3B.SPID11.ui8[1]
#define FSGD3BSPID11H FSGD3B.SPID11.ui16[1]
#define FSGD3BSPID11HL FSGD3B.SPID11.ui8[2]
#define FSGD3BSPID11HH FSGD3B.SPID11.ui8[3]
#define FSGD3BPROT12 FSGD3B.PROT12.ui32
#define FSGD3BPROT12L FSGD3B.PROT12.ui16[0]
#define FSGD3BPROT12LL FSGD3B.PROT12.ui8[0]
#define FSGD3BPROT12LH FSGD3B.PROT12.ui8[1]
#define FSGD3BPROT12H FSGD3B.PROT12.ui16[1]
#define FSGD3BPROT12HL FSGD3B.PROT12.ui8[2]
#define FSGD3BPROT12HH FSGD3B.PROT12.ui8[3]
#define FSGD3BSPID12 FSGD3B.SPID12.ui32
#define FSGD3BSPID12L FSGD3B.SPID12.ui16[0]
#define FSGD3BSPID12LL FSGD3B.SPID12.ui8[0]
#define FSGD3BSPID12LH FSGD3B.SPID12.ui8[1]
#define FSGD3BSPID12H FSGD3B.SPID12.ui16[1]
#define FSGD3BSPID12HL FSGD3B.SPID12.ui8[2]
#define FSGD3BSPID12HH FSGD3B.SPID12.ui8[3]
#define FSGD3BPROT13 FSGD3B.PROT13.ui32
#define FSGD3BPROT13L FSGD3B.PROT13.ui16[0]
#define FSGD3BPROT13LL FSGD3B.PROT13.ui8[0]
#define FSGD3BPROT13LH FSGD3B.PROT13.ui8[1]
#define FSGD3BPROT13H FSGD3B.PROT13.ui16[1]
#define FSGD3BPROT13HL FSGD3B.PROT13.ui8[2]
#define FSGD3BPROT13HH FSGD3B.PROT13.ui8[3]
#define FSGD3BSPID13 FSGD3B.SPID13.ui32
#define FSGD3BSPID13L FSGD3B.SPID13.ui16[0]
#define FSGD3BSPID13LL FSGD3B.SPID13.ui8[0]
#define FSGD3BSPID13LH FSGD3B.SPID13.ui8[1]
#define FSGD3BSPID13H FSGD3B.SPID13.ui16[1]
#define FSGD3BSPID13HL FSGD3B.SPID13.ui8[2]
#define FSGD3BSPID13HH FSGD3B.SPID13.ui8[3]
#define ERRSLV3AICTL ERRSLV3AI.CTL
#define ERRSLV3AISTAT ERRSLV3AI.STAT
#define ERRSLV3AITYPE ERRSLV3AI.TYPE
#define ERRSLVHICTL ERRSLVHI.CTL
#define ERRSLVHISTAT ERRSLVHI.STAT
#define ERRSLVHITYPE ERRSLVHI.TYPE
#define IPGECRUM IPG.ECRUM
#define IPGADRUM IPG.ADRUM
#define IPGENUM IPG.ENUM.ui8
#define IPGPMTUM0 IPG.PMTUM0.ui8
#define IPGPMTUM1 IPG.PMTUM1.ui8
#define IPGPMTUM2 IPG.PMTUM2.ui8
#define IPGPMTUM3 IPG.PMTUM3.ui8
#define IPGPMTUM4 IPG.PMTUM4.ui8
#define PEGG0MK PEG.G0MK.ui32
#define PEGG0MKL PEG.G0MK.ui16[0]
#define PEGG0MKLL PEG.G0MK.ui8[0]
#define PEGG0MKLH PEG.G0MK.ui8[1]
#define PEGG0MKH PEG.G0MK.ui16[1]
#define PEGG0MKHL PEG.G0MK.ui8[2]
#define PEGG0MKHH PEG.G0MK.ui8[3]
#define PEGG0BA PEG.G0BA.ui32
#define PEGG0BAL PEG.G0BA.ui16[0]
#define PEGG0BALL PEG.G0BA.ui8[0]
#define PEGG0BALH PEG.G0BA.ui8[1]
#define PEGG0BAH PEG.G0BA.ui16[1]
#define PEGG0BAHL PEG.G0BA.ui8[2]
#define PEGG0BAHH PEG.G0BA.ui8[3]
#define PEGG0SP PEG.G0SP.ui32
#define PEGG0SPL PEG.G0SP.ui16[0]
#define PEGG0SPLL PEG.G0SP.ui8[0]
#define PEGG0SPLH PEG.G0SP.ui8[1]
#define PEGG0SPH PEG.G0SP.ui16[1]
#define PEGG0SPHL PEG.G0SP.ui8[2]
#define PEGG0SPHH PEG.G0SP.ui8[3]
#define PEGG1MK PEG.G1MK.ui32
#define PEGG1MKL PEG.G1MK.ui16[0]
#define PEGG1MKLL PEG.G1MK.ui8[0]
#define PEGG1MKLH PEG.G1MK.ui8[1]
#define PEGG1MKH PEG.G1MK.ui16[1]
#define PEGG1MKHL PEG.G1MK.ui8[2]
#define PEGG1MKHH PEG.G1MK.ui8[3]
#define PEGG1BA PEG.G1BA.ui32
#define PEGG1BAL PEG.G1BA.ui16[0]
#define PEGG1BALL PEG.G1BA.ui8[0]
#define PEGG1BALH PEG.G1BA.ui8[1]
#define PEGG1BAH PEG.G1BA.ui16[1]
#define PEGG1BAHL PEG.G1BA.ui8[2]
#define PEGG1BAHH PEG.G1BA.ui8[3]
#define PEGG1SP PEG.G1SP.ui32
#define PEGG1SPL PEG.G1SP.ui16[0]
#define PEGG1SPLL PEG.G1SP.ui8[0]
#define PEGG1SPLH PEG.G1SP.ui8[1]
#define PEGG1SPH PEG.G1SP.ui16[1]
#define PEGG1SPHL PEG.G1SP.ui8[2]
#define PEGG1SPHH PEG.G1SP.ui8[3]
#define PEGG2MK PEG.G2MK.ui32
#define PEGG2MKL PEG.G2MK.ui16[0]
#define PEGG2MKLL PEG.G2MK.ui8[0]
#define PEGG2MKLH PEG.G2MK.ui8[1]
#define PEGG2MKH PEG.G2MK.ui16[1]
#define PEGG2MKHL PEG.G2MK.ui8[2]
#define PEGG2MKHH PEG.G2MK.ui8[3]
#define PEGG2BA PEG.G2BA.ui32
#define PEGG2BAL PEG.G2BA.ui16[0]
#define PEGG2BALL PEG.G2BA.ui8[0]
#define PEGG2BALH PEG.G2BA.ui8[1]
#define PEGG2BAH PEG.G2BA.ui16[1]
#define PEGG2BAHL PEG.G2BA.ui8[2]
#define PEGG2BAHH PEG.G2BA.ui8[3]
#define PEGG2SP PEG.G2SP.ui32
#define PEGG2SPL PEG.G2SP.ui16[0]
#define PEGG2SPLL PEG.G2SP.ui8[0]
#define PEGG2SPLH PEG.G2SP.ui8[1]
#define PEGG2SPH PEG.G2SP.ui16[1]
#define PEGG2SPHL PEG.G2SP.ui8[2]
#define PEGG2SPHH PEG.G2SP.ui8[3]
#define PEGG3MK PEG.G3MK.ui32
#define PEGG3MKL PEG.G3MK.ui16[0]
#define PEGG3MKLL PEG.G3MK.ui8[0]
#define PEGG3MKLH PEG.G3MK.ui8[1]
#define PEGG3MKH PEG.G3MK.ui16[1]
#define PEGG3MKHL PEG.G3MK.ui8[2]
#define PEGG3MKHH PEG.G3MK.ui8[3]
#define PEGG3BA PEG.G3BA.ui32
#define PEGG3BAL PEG.G3BA.ui16[0]
#define PEGG3BALL PEG.G3BA.ui8[0]
#define PEGG3BALH PEG.G3BA.ui8[1]
#define PEGG3BAH PEG.G3BA.ui16[1]
#define PEGG3BAHL PEG.G3BA.ui8[2]
#define PEGG3BAHH PEG.G3BA.ui8[3]
#define PEGG3SP PEG.G3SP.ui32
#define PEGG3SPL PEG.G3SP.ui16[0]
#define PEGG3SPLL PEG.G3SP.ui8[0]
#define PEGG3SPLH PEG.G3SP.ui8[1]
#define PEGG3SPH PEG.G3SP.ui16[1]
#define PEGG3SPHL PEG.G3SP.ui8[2]
#define PEGG3SPHH PEG.G3SP.ui8[3]
#define PEGG4MK PEG.G4MK.ui32
#define PEGG4MKL PEG.G4MK.ui16[0]
#define PEGG4MKLL PEG.G4MK.ui8[0]
#define PEGG4MKLH PEG.G4MK.ui8[1]
#define PEGG4MKH PEG.G4MK.ui16[1]
#define PEGG4MKHL PEG.G4MK.ui8[2]
#define PEGG4MKHH PEG.G4MK.ui8[3]
#define PEGG4BA PEG.G4BA.ui32
#define PEGG4BAL PEG.G4BA.ui16[0]
#define PEGG4BALL PEG.G4BA.ui8[0]
#define PEGG4BALH PEG.G4BA.ui8[1]
#define PEGG4BAH PEG.G4BA.ui16[1]
#define PEGG4BAHL PEG.G4BA.ui8[2]
#define PEGG4BAHH PEG.G4BA.ui8[3]
#define PEGG4SP PEG.G4SP.ui32
#define PEGG4SPL PEG.G4SP.ui16[0]
#define PEGG4SPLL PEG.G4SP.ui8[0]
#define PEGG4SPLH PEG.G4SP.ui8[1]
#define PEGG4SPH PEG.G4SP.ui16[1]
#define PEGG4SPHL PEG.G4SP.ui8[2]
#define PEGG4SPHH PEG.G4SP.ui8[3]
#define PEGG5MK PEG.G5MK.ui32
#define PEGG5MKL PEG.G5MK.ui16[0]
#define PEGG5MKLL PEG.G5MK.ui8[0]
#define PEGG5MKLH PEG.G5MK.ui8[1]
#define PEGG5MKH PEG.G5MK.ui16[1]
#define PEGG5MKHL PEG.G5MK.ui8[2]
#define PEGG5MKHH PEG.G5MK.ui8[3]
#define PEGG5BA PEG.G5BA.ui32
#define PEGG5BAL PEG.G5BA.ui16[0]
#define PEGG5BALL PEG.G5BA.ui8[0]
#define PEGG5BALH PEG.G5BA.ui8[1]
#define PEGG5BAH PEG.G5BA.ui16[1]
#define PEGG5BAHL PEG.G5BA.ui8[2]
#define PEGG5BAHH PEG.G5BA.ui8[3]
#define PEGG5SP PEG.G5SP.ui32
#define PEGG5SPL PEG.G5SP.ui16[0]
#define PEGG5SPLL PEG.G5SP.ui8[0]
#define PEGG5SPLH PEG.G5SP.ui8[1]
#define PEGG5SPH PEG.G5SP.ui16[1]
#define PEGG5SPHL PEG.G5SP.ui8[2]
#define PEGG5SPHH PEG.G5SP.ui8[3]
#define PEGG6MK PEG.G6MK.ui32
#define PEGG6MKL PEG.G6MK.ui16[0]
#define PEGG6MKLL PEG.G6MK.ui8[0]
#define PEGG6MKLH PEG.G6MK.ui8[1]
#define PEGG6MKH PEG.G6MK.ui16[1]
#define PEGG6MKHL PEG.G6MK.ui8[2]
#define PEGG6MKHH PEG.G6MK.ui8[3]
#define PEGG6BA PEG.G6BA.ui32
#define PEGG6BAL PEG.G6BA.ui16[0]
#define PEGG6BALL PEG.G6BA.ui8[0]
#define PEGG6BALH PEG.G6BA.ui8[1]
#define PEGG6BAH PEG.G6BA.ui16[1]
#define PEGG6BAHL PEG.G6BA.ui8[2]
#define PEGG6BAHH PEG.G6BA.ui8[3]
#define PEGG6SP PEG.G6SP.ui32
#define PEGG6SPL PEG.G6SP.ui16[0]
#define PEGG6SPLL PEG.G6SP.ui8[0]
#define PEGG6SPLH PEG.G6SP.ui8[1]
#define PEGG6SPH PEG.G6SP.ui16[1]
#define PEGG6SPHL PEG.G6SP.ui8[2]
#define PEGG6SPHH PEG.G6SP.ui8[3]
#define PEGG7MK PEG.G7MK.ui32
#define PEGG7MKL PEG.G7MK.ui16[0]
#define PEGG7MKLL PEG.G7MK.ui8[0]
#define PEGG7MKLH PEG.G7MK.ui8[1]
#define PEGG7MKH PEG.G7MK.ui16[1]
#define PEGG7MKHL PEG.G7MK.ui8[2]
#define PEGG7MKHH PEG.G7MK.ui8[3]
#define PEGG7BA PEG.G7BA.ui32
#define PEGG7BAL PEG.G7BA.ui16[0]
#define PEGG7BALL PEG.G7BA.ui8[0]
#define PEGG7BALH PEG.G7BA.ui8[1]
#define PEGG7BAH PEG.G7BA.ui16[1]
#define PEGG7BAHL PEG.G7BA.ui8[2]
#define PEGG7BAHH PEG.G7BA.ui8[3]
#define PEGG7SP PEG.G7SP.ui32
#define PEGG7SPL PEG.G7SP.ui16[0]
#define PEGG7SPLL PEG.G7SP.ui8[0]
#define PEGG7SPLH PEG.G7SP.ui8[1]
#define PEGG7SPH PEG.G7SP.ui16[1]
#define PEGG7SPHL PEG.G7SP.ui8[2]
#define PEGG7SPHH PEG.G7SP.ui8[3]
#define SEGCONT SEG.CONT
#define SEGFLAG SEG.FLAG
#define SEGTYPE SEG.TYPE
#define SEGSIDE SEG.SIDE
#define SEGADDR SEG.ADDR.ui32
#define SEGADDRL SEG.ADDR.ui16[0]
#define SEGADDRH SEG.ADDR.ui16[1]
#endif
