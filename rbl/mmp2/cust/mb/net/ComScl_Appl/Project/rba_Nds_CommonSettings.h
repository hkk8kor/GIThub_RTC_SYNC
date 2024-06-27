/*<RBHead>
 *************************************************************************
 *                                                                       *
 *                      ROBERT BOSCH GMBH                                *
 *                          STUTTGART                                    *
 *                                                                       *
 *          Alle Rechte vorbehalten - All rights reserved                *
 *                                                                       *
 *************************************************************************

 *************************************************************************
 *    Administrative Information (automatically filled in by eASEE)      *
 *************************************************************************
 *
 * $Filename__:$
 *
 * $Author____:$
 *
 * $Function__:$
 *
 *************************************************************************
 * $Domain____:$
 * $User______:$
 * $Date______:$
 * $Class_____:$
 * $Name______:$
 * $Variant___:$
 * $Revision__:$
 * $Type______:$
 * $State_____:$
 * $Generated_:$
 *************************************************************************
 *
 * $UniqueName:$
 * $Component_:$
 *
 *
 *************************************************************************
 * List Of Changes
 *
 * $History___:
 *
 *
 * $
 *
 *************************************************************************
</RBHead>*/

#ifndef RBA_NDS_COMMONSETTINGS_H_
#define RBA_NDS_COMMONSETTINGS_H_

//#include "rba_SCL_Subsystem.h"
#include "CanIf.h"
#include "Com_Cfg.h"
#include "Com_Cbk.h"
#include "ASWIF_CommonConfig.h"
#include "Com_Cfg.h"
#include "ComScl_Appl_AliveCounterLib.h"
#include "ComScl_Appl_ChecksumLib.h"
#include "RBSMM.h"
//#include "Net_Global.h"
#include "DIA_MonitoringInfo_Common.h"
#include "ComScl_SubSystemProc.h"
#include "Dem_EventFHandling.h"
#include "rbl_CustIf_ImuOutPutStdTypes.h"
#include "rbl_CustIf_Ign_Stat_ST3.h"
#include "rbl_CustIf_PT4_PTCoor4_ST3.h"
#include "rbl_CustIf_PN14_Master_Stat1_ST3.h"
#include "rbl_CustIf_DIAG_Stat_ST3.h"
#include "rbl_CustIf_FBL_Cfg_Star3_ST3.h"
#include "rbl_CustIf_DI_OdoSpeedometer_ST3.h"
#include "rbl_CustIf_VehSpd_Disp_ST3.h"
#include "rbl_CustIf_BCS_Whl_Msg1_BTC_ST3.h"
#include "rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3.h"
#include "rbl_CustIf_IMU_D_Stat_ST3.h"

#if (RBFS_MMP2 == RBFS_MMP2_IMUA)
 #include "rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3.h"
#endif
#if (RBFS_MMP2 == RBFS_MMP2_IMUB)
 #include "rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3.h"
#endif


#if (RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
#include "rbl_CustIf_VSS_TP_Auth_ST3.h"
#include "rbl_CustIf_VSS_TP_RealTmOffset_ST3.h"
#include "rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3.h"
#include "rbl_CustIf_VSS_TP_SharedSecret_ST3.h"
#include "rbl_CustIf_VSS_TP_VIN_ST3.h"
#endif

#include "ComScl_Scl_MappingSignals_Rx.h"
#include "ComScl_RawSignals.h"
#include "ComScl_Flags.h"
//#include "RBHMI_Configuration_PRJ.h"
//#include "RBHMI_ConfigOutputDriver_PRJ.h"
//#include "ComScl_UserCallouts.h"
#if(RBFS_SensorMMxEnable == RBFS_SensorMMxEnable_YES)
#include "RBNetYRS_ExternIF.h"
#endif
#if(RBFS_RISSupport == RBFS_RISSupport_Yes)
    #include "RBRIS_Global.h"
#endif
//#include "ComScl_ChecksumLib_Hev.h"
//#include "ComScl_UserCallouts.h"
//#include "Comscl_Checksum_Tx.h"

#endif /* RBA_NDS_COMMONSETTINGS_H_ */
