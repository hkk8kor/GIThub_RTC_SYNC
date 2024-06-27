/// @file rbl_CustIf_Main.c
/// @brief The file consists of the API's for Read Data by Identifier DID's identified for Customer Diagnostics
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


/* ***** Includes ***** */
#include "rbl_CustIf_Pub.h"
#include "rbl_CustIf_OsPub.h"
#include "rbl_CustIf_Main.h"
#include "rbl_CustIf_ImuOutPutStdTypes.h"
#include "rbl_CustIf_FBL_Cfg_Star3_ST3.h"
#include "rbl_CustIf_DIAG_Stat_ST3.h"
#include "rbl_CustIf_Ign_Stat_ST3.h"
#include "rbl_CustIf_DI_OdoSpeedometer_ST3.h"
#include "rbl_CustIf_VehSpd_Disp_ST3.h"
#include "rbl_CustIf_ECU_Stat_IMU_X_ST3.h"
#include "rbl_CustIf_Measurement.h"
#include "rbl_CustIf_PT4_PTCoor4_ST3.h"
#include "rbl_CustIf_PN14_Master_Stat1_ST3.h"
#include "rbl_CustIf_BCS_Whl_Msg1_BTC_ST3.h"
#include "rbl_CustIf_Meas_IMU_X_ST3.h"

#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
    #include "rbl_CustIf_VSS_TP_Auth_ST3.h"
    #include "rbl_CustIf_VSS_TP_RealTmOffset_ST3.h"
    #include "rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3.h"
    #include "rbl_CustIf_VSS_TP_SharedSecret_ST3.h"
    #include "rbl_CustIf_VSS_TP_VIN_ST3.h"
#endif

#if(RBFS_MMP2 == RBFS_MMP2_IMUA)
    #include "rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3.h"
#endif
#if(RBFS_MMP2 == RBFS_MMP2_IMUB)
    #include "rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3.h"
#endif

#if(RBFS_DrivingCANSignals == RBFS_DrivingCANSignals_ON)
    #include "rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3.h"
    #include "rbl_CustIf_IMU_D_Stat_ST3.h"
    #include "rbl_CustIf_ECU_Stat_IMU_D_ST3.h"
#endif

#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
 #include "rbl_CustIf_GTS_Monitoring.h"
 #include "rbl_CustIf_TiSync.h"
#endif
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Local Definitions ***** */
/* Constants and Macro definitions */

/* Variables */
static uint8 rbl_CustIf_SysSt = RBL_CUSTIF_SYSTEM_STATE_NORMAL ;

/* Variables used for test mode measurement */
#if (RBFS_ConfigurationType == RBFS_ConfigurationType_DEVELOP)
static uint32 rbl_CustIf_SwtTestModEna;
static rbl_ImuStdTypes_ImuSignalSet_t rbl_CustIf_filtered_ImuSignalSet_st_test;
static rbl_ImuStdTypes_ImuSignalSet_t rbl_CustIf_Derived_ImuSignalSet_st_test;
#endif

/* Structure definitions */

/* ***** PUBLIC/PROTECTED API functions ***** */
/* *********************************************************************************************************************
 * ***** API public: rbl_CustIf_10ms_Proc *****/

void rbl_CustIf_10ms_Proc(void)
{

}

/* ***** END_API rbl_CustIf_10ms_Proc ***** */

/* *********************************************************************************************************************
 ***** API public: rbl_CustIf_5ms_Proc *****/

void rbl_CustIf_5ms_Proc(void)
{

    /* pdu update services will be called every 5ms for both IMU A and IMU B for both Fast normal pdu */
    /* receive filtered and derived signal data from signal chain */
    RBMESG_DefineMESGDef(SigChain_FinalFil);

    RBMESG_DefineMESGDef(SigChain_FinalDer);

    /* Receive input signals from filter 2 For Driving CAN pdu's */
    RBMESG_DefineMESGDef(SigChain_FinalFil2);

    RBMESG_DefineMESGDef(SigChain_FinalDer2);

    /* Get the derived signal Data from Signal Chain */
    RBMESG_RcvMESGDef(SigChain_FinalDer);

    /* Get the Filtered signal Data from Signal Chain */
    RBMESG_RcvMESGDef(SigChain_FinalFil);

    /* Get the derived signal Data from Signal Chain(filter2) for driving Can */
    RBMESG_RcvMESGDef(SigChain_FinalDer2);

    /* Get the Filtered signal Data from Signal Chain (filter2) for driving Can*/
    RBMESG_RcvMESGDef(SigChain_FinalFil2);

    //Update the data in to the PDU
#if (RBFS_ConfigurationType == RBFS_ConfigurationType_DEVELOP)
    if(rbl_CustIf_SwtTestModEna == RBL_IMUSTDTYPES_TEST_MOD_ENAD)
    {
        // For Test mode functions
        rbl_CustIf_IMU_Output_ST3_PDU_Update(&rbl_CustIf_filtered_ImuSignalSet_st_test, &rbl_CustIf_Derived_ImuSignalSet_st_test);
    }
    else
#endif
    {
        rbl_CustIf_IMU_Output_ST3_PDU_Update(&l_SigChain_FinalFil, &l_SigChain_FinalDer);

#if(RBFS_DrivingCANSignals == RBFS_DrivingCANSignals_ON)
        rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update(&l_SigChain_FinalFil2, &l_SigChain_FinalDer2);
        rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3(&l_SigChain_FinalFil2);
#endif

    }

}

/* ***** END_API rbl_CustIf_5ms_Proc ***** */

/* *********************************************************************************************************************
 ***** API public: rbl_CustIf_GetSystemState *****/

uint8 rbl_CustIf_GetSystemState(void)
{
  return rbl_CustIf_SysSt;
}

/* ***** END_API rbl_CustIf_GetSystemState ***** */
/* *********************************************************************************************************************
 ***** API public: rbl_CustIf_20ms_Proc *****/

void rbl_CustIf_20ms_Proc(void)
{
    /*  Reception PDU  */
    /*  calling the FBL_Cfg_Star3_ST3 receive PDU service every 20 ms */
    rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();

    /*  calling the DIAG_Stat_ST3 receive PDU service every 20 ms */
    rbl_CustIf_DIAG_Stat_ST3_PDU_Receive();

    /*  calling the Ign_Stat_ST3 receive PDU service every 20 ms */
    rbl_CustIf_Ign_Stat_ST3_PDU_Receive();

    /*  calling the DI_OdoSpeedometer_ST3 receive PDU service every 20 ms */
    rbl_CustIf_DI_OdoSpeedometer_ST3_PDU_Receive();

    /*  calling the VehSpd_Disp_ST3 receive signal service every 20 ms */
    rbl_CustIf_VehSpd_Disp_ST3_Receive();

    /*  calling the PT4_PTCoor4_ST3 receive PDU service every 20 ms */
    rbl_CustIf_PT4_PTCoor4_ST3_PDU_Receive();

    /*  calling the PN14_Master_Stat1_ST3 receive PDU service every 20 ms */
    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

    /* calling the BCS_Whl_Msg1_BTC_ST3 receive pdu every 20 ms */
    rbl_CustIf_BCS_Whl_Msg1_BTC_ST3_Receive();

#if(RBFS_MMP2 == RBFS_MMP2_IMUA)
    /*  calling the ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3 receive PDU service every 20 ms */
    rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3_PDU_Receive ();
#endif

#if(RBFS_MMP2 == RBFS_MMP2_IMUB)
    /*  calling the ADAS_HAD_Stat_IDC_M_FSI_ST3 receive PDU service every 20 ms */
    rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_PDU_Receive();
#endif

    /*  transmitted PDU  */
    /*  calling the ECU_Stat_IMU_A_ST3 Update/transmit PDU service every 20 ms */
    rbl_CustIf_ECU_Stat_IMU_X_ST3_PDU_Update();


#if(RBFS_DrivingCANSignals == RBFS_DrivingCANSignals_ON)
      rbl_CustIf_ECU_Stat_IMU_D_ST3_PDU_Update();
#endif
}

/* ***** END_API rbl_CustIf_20ms_Proc ***** */

/* *********************************************************************************************************************
 ***** API public: rbl_CustIf_Monitoring_20ms_Proc *****/

void rbl_CustIf_Monitoring_20ms_Proc(void)
{

#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
   /*Monitoring Global Time Synchronisation every 20ms*/
    rbl_CustIf_GTS_Monitoring();

    /*Check Global Time Synchronisation localfallback*/
    rbl_CustIf_GTS_LocalFallBackCheck();

#if(RBFS_MMP2 == RBFS_MMP2_IMUB)
    /*Monitoring Global Time Synchronisation every 20ms*/
    rbl_CustIf_GTS_Monitoring_AMG();

    /*Check Global Time Synchronisation localfallback*/
    rbl_CustIf_GTS_LocalFallBackCheck_AMG();
#endif

#endif

}

/* ***** END_API rbl_CustIf_Monitoring_20ms_Proc ***** */
/* ***** END_SECTION API functions ***** */
