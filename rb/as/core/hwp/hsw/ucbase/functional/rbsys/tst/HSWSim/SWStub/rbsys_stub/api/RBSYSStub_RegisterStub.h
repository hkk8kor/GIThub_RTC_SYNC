#ifndef RBSYSSTUB_REGISTERSTUB_H__
#define RBSYSSTUB_REGISTERSTUB_H__

#include "RBSYS_Config.h"

extern uint32 SYSSim_TickCtr;
extern uint32* RBSYS_getSynctimeTickCtrStub(void);


#if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  /**
   * This is only a stub for INTC2 EIC32-245.
   * EIC0 to EIC31 belong to INTC1 and would need to exist per core.
   * EIC32 to EIC255 belong to INTC2, EIC246 to EIC255 are reserved.
   */
  extern uint16 EICn[214];
  #define EIC32 (*(uint16*)(&EICn[0]))

  #define STM0CNT1 (*(RBSYS_getSynctimeTickCtrStub())) // pointer needed as APPLIF dereferences RBSYS_SystemTimerSynctimeCnt
  #define STM0CNT2 (*(RBSYS_getSynctimeTickCtrStub()))
  extern uint32 RESF;
  extern uint32 RESFC;
  #define RBSYS_RESF  RESF
  #define RBSYS_RESFC RESFC
  extern uint8  SINTR0;

  extern uint32 MSR_LM3;
  extern uint32 SWLRESS3;
  extern uint32 MSR_LM5;
  extern uint32 SWLRESS5;
  extern uint32 MSR_LM7;
  extern uint32 SWLRESS7;
  extern uint32 MSR_LM10;
  extern uint32 SWLRESS10;
  extern uint32 MSR_LM11;
  extern uint32 SWLRESS11;
  extern uint32 MSR_LM12;
  extern uint32 SWLRESS12;
  extern uint32 MSR_LM4;
  extern uint32 SWLRESS4;
  extern uint32 MSR_LM6;
  extern uint32 SWLRESS6;
  extern uint32 MSR_LM8;
  extern uint32 SWLRESS8;

  extern uint32 PFCE0;
  extern uint32 PFC0;
  extern uint32 PM0;
  extern uint32 PMC0;
  extern uint32 PMC4;
  extern uint32 PSR4;

  extern uint32 OTS0OTSTCR;
  extern uint32 OTS0OTENDCR;
  extern uint32 OTS0OTCR;
  extern uint32 OTS0OTFCR;
  extern uint32 OTS0OTFR;
  extern uint32 OTS0OTSTR;
  extern uint32 OTS0OTDR;
  extern uint32 OTS0HTBRAU;
  extern uint32 OTS0HTBRAL;
  extern uint32 OTS0HTBRBU;
  extern uint32 OTS0HTBRBL;
  extern uint32 OTS0LTBRAU;
  extern uint32 OTS0LTBRAL;
  extern uint32 OTS0TDLR;
  extern uint32 OTS0COEFFRA;
  extern uint32 OTS0COEFFRB;
  extern uint32 OTS0COEFFRC;

  extern uint32 TMA_MS;
  extern uint32 TMB_MS;

  extern uint32 STM1CNT1;
  extern uint32 STM1STC;
  extern uint32 STM1TT;
  extern uint32 STM1TS;
  extern uint32 STM1IS;

  extern uint32 PRDSEL3;
  extern uint32 PRDNAME2;
  extern uint32 PRDNAME3;

  extern uint32 PE2ICUS;
  extern uint32 PE2ICUF;
  extern uint32 PE2ICUFS;
  extern uint32 PE2ICUIE;

  extern uint32 ICUMACTFLAG;
  extern uint32 ICU2PES;
  extern uint32 ICU2PEFC;
  extern uint32 ICU2PEF;
  extern uint32 ICU2PEIE;

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  /**
   * This is only a stub for INTC2 EIC32-716.
   * EIC0 to EIC31 belong to INTC1 and would need to exist per core.
   * EIC32 to EIC767 belong to INTC2, EIC717 to EIC767 are reserved.
   */
  extern uint16 INTC2EICn[685];
  #define INTC2EIC32 (*(uint16*)(&INTC2EICn[0]))

  #define TPTMPE0TPTM0UCNT0 (*(RBSYS_getSynctimeTickCtrStub())) // pointer needed as APPLIF dereferences RBSYS_SystemTimerSynctimeCnt
  #define TPTMPE0TPTM0UCNT1 (*(RBSYS_getSynctimeTickCtrStub()))
  extern uint32 SYSCTRLRESF;
  extern uint32 SYSCTRLRESFC;
  #define RBSYS_RESF  SYSCTRLRESF
  #define RBSYS_RESFC SYSCTRLRESFC
  extern uint8  EINTSINTR0;

  extern uint32 SYSCTRLMSR_OSTM;
  extern uint32 SYSCTRLSWMRESS_OSTM;
  extern uint32 SYSCTRLMSR_RSCFD;
  extern uint32 SYSCTRLSWMRESS_RSCFD;
  extern uint32 SYSCTRLMSR_GTM;
  extern uint32 SYSCTRLSWMRESS_GTM;
  extern uint32 SYSCTRLMSR_RSENT;
  extern uint32 SYSCTRLSWMRESS_RSENT;
  extern uint32 SYSCTRLMSR_MSPI;
  extern uint32 SYSCTRLSWMRESS_MSPI;
  extern uint32 SYSCTRLMSR_RLIN3;
  extern uint32 SYSCTRLSWMRESS_RLIN3;
  extern uint32 SYSCTRLMSR_ADCJ_AWO;
  extern uint32 SYSCTRLSWMRESS_ADCJ_AWO;
  extern uint32 SYSCTRLMSR_ADCJ_ISO;
  extern uint32 SYSCTRLSWMRESS_ADCJ_ISO;
  extern uint32 SYSCTRLMSR_FLXA;
  extern uint32 SYSCTRLSWMRESS_FLXA;
  extern uint32 SYSCTRLMSR_ETNB;
  extern uint32 SYSCTRLSWMRESS_ETNB;
  extern uint32 SYSCTRLMSR_RHSIF;
  extern uint32 SYSCTRLSWMRESS_RHSIF;
  extern uint32 SYSCTRLMSR_TAUD;
  extern uint32 SYSCTRLSWMRESS_TAUD;

  extern uint32 SCDS0CFMAPSTT;///< used by aplplant.

  extern uint32 TAUJ1TPS;
  extern uint32 TAUJ1BRS;
  extern uint32 TAUJ1TOE;
  extern uint32 TAUJ1CMOR0;
  extern uint32 TAUJ1CMUR0;
  extern uint32 TAUJ1TS;

  extern uint32 TAUJ2TPS;
  extern uint32 TAUJ2BRS;
  extern uint32 TAUJ2TOE;
  extern uint32 TAUJ2CMOR0;
  extern uint32 TAUJ2CMUR0;
  extern uint32 TAUJ2CMOR1;
  extern uint32 TAUJ2CMUR1;
  extern uint32 TAUJ2CMOR2;
  extern uint32 TAUJ2CMUR2;
  extern uint32 TAUJ2CMOR3;
  extern uint32 TAUJ2CMUR3;
  extern uint32 TAUJ2TS;

  extern uint32 TAUA0CMOR8;
  extern uint32 TAUA0CMUR8;
  extern uint32 TAUA0TOE;
  extern uint32 TAUA0CDR8;
  extern uint32 TAUA0TS;
  extern uint32 TAUA0CNT8;
  extern uint32 TAUA0CNT9;
  extern uint32 TAUA0CDR9;// avoid endless loop in RFPLowPulseTest
  extern uint32 TAUA0TT;

  /// uctemp regs also used by RBuCTEMP on U2A.
  /// (hexbuilds already successful)
  extern uint32 OTS0OTSTCR;
  extern uint32 OTS0OTENDCR;
  extern uint32 OTS0OTCR;
  extern uint32 OTS0OTFCR;
  extern uint32 OTS0OTFR;
  extern uint32 OTS0OTSTR;
  extern uint32 OTS0OTDR;
  extern uint32 OTS0HTBRAU;
  extern uint32 OTS0HTBRAL;
  extern uint32 OTS0HTBRBU;
  extern uint32 OTS0HTBRBL;
  extern uint32 OTS0LTBRAU;
  extern uint32 OTS0LTBRAL;
  extern uint32 OTS0TDLR;
  extern uint32 OTS0COEFFRA;
  extern uint32 OTS0COEFFRB;
  extern uint32 OTS0COEFFRC;

  extern uint32 PRDINFFPRDNAME2;
  extern uint32 PRDINFFPRDNAME3;
  extern uint32 PRDINFFPRDNUM;

#else
    #warning ("RBSYSStub_RegisterStub.h empty for this uCFamily.")
#endif



#endif