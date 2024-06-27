/// @file rbl_SigChain_Measure_TestInjSigSet.h
/// @brief measurements no functional code
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


#ifndef RBL_SIGCHAIN_MEASURE_TESTINJSIGSET_H__
#define RBL_SIGCHAIN_MEASURE_TESTINJSIGSET_H__

#include "CM_Basetypes_COMMON.h"
#include "rbl_ImuStdTypes.h"

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.temp[0].value*/
/*COMMENT=Temperature signal 0*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.temp[0].status*/
/*COMMENT=Status of temperature signal 0*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.temp[0].smx*/
/*COMMENT=SMI which provides temperature signal 0*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.temp[1].value*/
/*COMMENT=Temperature signal 1*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.temp[1].status*/
/*COMMENT=Status of temperature signal 1*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.temp[1].smx*/
/*COMMENT=SMI which provides temperature signal 1*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.temp[2].value*/
/*COMMENT=Temperature signal 2*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.temp[2].status*/
/*COMMENT=Status of temperature signal 2*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.temp[2].smx*/
/*COMMENT=SMI which provides temperature signal 2*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.temp[3].status*/
/*COMMENT=Status of temperature signal 3*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.temp[3].value*/
/*COMMENT=Temperature signal 3*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.temp[3].smx*/
/*COMMENT=SMI which provides temperature signal 3*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/***** rbl_SigChain_TestInjSigSet ******/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[0][0].value*/
/*COMMENT=first Acceleration in X direction*/
/*FORMULA=NF_RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_TO_G*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[0][0].status*/
/*COMMENT=Status for first Acceleration in X direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[0][0].smx*/
/*COMMENT=Source SMI for first Acceleration in X direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[0][1].value*/
/*COMMENT=second Acceleration in X direction*/
/*FORMULA=NF_RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_TO_G*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[0][1].status*/
/*COMMENT=Status for second Acceleration in X direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[0][1].smx*/
/*COMMENT=Source SMI for second Acceleration in X direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[0][2].value*/
/*COMMENT=third Acceleration in X direction*/
/*FORMULA=NF_RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_TO_G*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[0][2].status*/
/*COMMENT=Status for third Acceleration in X direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[0][2].smx*/
/*COMMENT=Source SMI for third Acceleration in X direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[0][3].value*/
/*COMMENT=fourth Acceleration in X direction*/
/*FORMULA=NF_RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_TO_G*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[0][3].status*/
/*COMMENT=Status for fourth Acceleration in X direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[0][3].smx*/
/*COMMENT=Source SMI for fourth Acceleration in X direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[1][0].value*/
/*COMMENT=first Acceleration in Y direction*/
/*FORMULA=NF_RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_TO_G*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[1][0].status*/
/*COMMENT=Status for first Acceleration in Y direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[1][0].smx*/
/*COMMENT=Source SMI for first Acceleration in Y direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[1][1].value*/
/*COMMENT=second Acceleration in Y direction*/
/*FORMULA=NF_RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_TO_G*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[1][1].status*/
/*COMMENT=Status for second Acceleration in Y direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[1][1].smx*/
/*COMMENT=Source SMI for second Acceleration in Y direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[1][2].value*/
/*COMMENT=third Acceleration in Y direction*/
/*FORMULA=NF_RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_TO_G*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[1][2].status*/
/*COMMENT=Status for third Acceleration in Y direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[1][2].smx*/
/*COMMENT=Source SMI for third Acceleration in Y direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[1][3].value*/
/*COMMENT=fourth Acceleration in Y direction*/
/*FORMULA=NF_RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_TO_G*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[1][3].status*/
/*COMMENT=Status for fourth Acceleration in Y direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[1][3].smx*/
/*COMMENT=Source SMI for fourth Acceleration in Y direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[2][0].value*/
/*COMMENT=first Acceleration in Z direction*/
/*FORMULA=NF_RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_TO_G*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[2][0].status*/
/*COMMENT=Status for first Acceleration in Z direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[2][0].smx*/
/*COMMENT=Source SMI for first Acceleration in Z direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[2][1].value*/
/*COMMENT=second Acceleration in Z direction*/
/*FORMULA=NF_RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_TO_G*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[2][1].status*/
/*COMMENT=Status for second Acceleration in Z direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[2][1].smx*/
/*COMMENT=Source SMI for second Acceleration in Z direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[2][2].value*/
/*COMMENT=third Acceleration in Z direction*/
/*FORMULA=NF_RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_TO_G*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[2][2].status*/
/*COMMENT=Status for third Acceleration in Z direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[2][2].smx*/
/*COMMENT=Source SMI for third Acceleration in Z direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[2][3].value*/
/*COMMENT=fourth Acceleration in Z direction*/
/*FORMULA=NF_RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_TO_G*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[2][3].status*/
/*COMMENT=Status for fourth Acceleration in Z direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.acc[2][3].smx*/
/*COMMENT=Source SMI for fourth Acceleration in Z direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.rate[0][0].value*/
/*COMMENT=first Rotation in X direction*/
/*FORMULA=RBL_IMUSTDTYPES_SENSITIVITY_ROT_LSB_PER_DEG*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.rate[0][0].status*/
/*COMMENT=Status for first Rotation in X direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.rate[0][0].smx*/
/*COMMENT=Source SMI for first Rotation in X direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.rate[1][0].value*/
/*COMMENT=first Rotation in Y direction*/
/*FORMULA=RBL_IMUSTDTYPES_SENSITIVITY_ROT_LSB_PER_DEG*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.rate[1][0].status*/
/*COMMENT=Status for first Rotation in Y direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.rate[1][0].smx*/
/*COMMENT=Source SMI for first Rotation in Y direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.rate[2][0].value*/
/*COMMENT=first Rotation in Z direction*/
/*FORMULA=RBL_IMUSTDTYPES_SENSITIVITY_ROT_LSB_PER_DEG*/
/*DATA_TYPE=FLOAT*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.rate[2][0].status*/
/*COMMENT=Status for first Rotation in Z direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.rate[2][0].smx*/
/*COMMENT=Source SMI for first Rotation in Z direction*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_TestInjSigSet.timeStamp*/
/*COMMENT=IMU signals timestamp*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#endif /* RBL_MMP2_APP_RBL_SIGNALCHAIN_SRC_RBMESG_RBL_SIGCHAIN_SIGNALSET_H_ */
