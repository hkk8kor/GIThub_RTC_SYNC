/// @file rbl_SigChain_Measure_SigFil.h
/// @brief measurements no functional code
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


#ifndef RBL_SIGCHAIN_MEASURE_SIGFIL_H__
#define RBL_SIGCHAIN_MEASURE_SIGFIL_H__

#include "CM_Basetypes_COMMON.h"
#include "rbl_ImuStdTypes.h"

/**** rbl_SigChain_FilVal - For First Filter ****/
/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 0 facA 0*/
/*NAME=rbl_SigChain_FilVal.filVal[0].facA[0]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 0 facA 1*/
/*NAME=rbl_SigChain_FilVal.filVal[0].facA[1]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 0 facB 0*/
/*NAME=rbl_SigChain_FilVal.filVal[0].facB[0]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 0 facB 1*/
/*NAME=rbl_SigChain_FilVal.filVal[0].facB[1]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 0 facB 2*/
/*NAME=rbl_SigChain_FilVal.filVal[0].facB[2]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 1 facA 0*/
/*NAME=rbl_SigChain_FilVal.filVal[1].facA[0]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 1 facA 1*/
/*NAME=rbl_SigChain_FilVal.filVal[1].facA[1]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 1 facB 0*/
/*NAME=rbl_SigChain_FilVal.filVal[1].facB[0]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 1 facB 1*/
/*NAME=rbl_SigChain_FilVal.filVal[1].facB[1]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 1 facB 2*/
/*NAME=rbl_SigChain_FilVal.filVal[1].facB[2]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
/**** rbl_SigChain_FilVal2 - For Second Filter ****/
/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 0 facA 0*/
/*NAME=rbl_SigChain_FilVal2.filVal[0].facA[0]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 0 facA 1*/
/*NAME=rbl_SigChain_FilVal2.filVal[0].facA[1]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 0 facB 0*/
/*NAME=rbl_SigChain_FilVal2.filVal[0].facB[0]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 0 facB 1*/
/*NAME=rbl_SigChain_FilVal2.filVal[0].facB[1]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 0 facB 2*/
/*NAME=rbl_SigChain_FilVal2.filVal[0].facB[2]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 1 facA 0*/
/*NAME=rbl_SigChain_FilVal2.filVal[1].facA[0]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 1 facA 1*/
/*NAME=rbl_SigChain_FilVal2.filVal[1].facA[1]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 1 facB 0*/
/*NAME=rbl_SigChain_FilVal2.filVal[1].facB[0]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 1 facB 1*/
/*NAME=rbl_SigChain_FilVal2.filVal[1].facB[1]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*COMMENT= FilterBuffer 1 facB 2*/
/*NAME=rbl_SigChain_FilVal2.filVal[1].facB[2]*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/**** rbl_SigChain_AccFlushCnt.counter ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt.counter[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt[0][0] */
/*COMMENT= Flush Counter Value of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt.counter[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt[1][0] */
/*COMMENT= Flush Counter Value of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt.counter[2][0]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt[2][0] */
/*COMMENT= Flush Counter Value of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt.counter[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt[0][1] */
/*COMMENT= Flush Counter Value of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt.counter[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt[1][1] */
/*COMMENT= Flush Counter Value of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt.counter[2][1]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt[2][1] */
/*COMMENT= Flush Counter Value of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt.counter[0][2]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt[0][2] */
/*COMMENT= Flush Counter Value of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt.counter[1][2]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt[1][2] */
/*COMMENT= Flush Counter Value of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt.counter[2][2]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt[2][2] */
/*COMMENT= Flush Counter Value of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt.counter[0][3]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt[0][3] */
/*COMMENT= Flush Counter Value of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt.counter[1][3]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt[1][3] */
/*COMMENT= Flush Counter Value of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt.counter[2][3]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt[2][3] */
/*COMMENT= Flush Counter Value of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
/**** rbl_SigChain_AccFlushCnt2.counter - Flush counter for Second Filter ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt2.counter[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt2[0][0] */
/*COMMENT= Flush Counter Value of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt2.counter[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt2[1][0] */
/*COMMENT= Flush Counter Value of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt2.counter[2][0]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt2[2][0] */
/*COMMENT= Flush Counter Value of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt2.counter[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt2[0][1] */
/*COMMENT= Flush Counter Value of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt2.counter[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt2[1][1] */
/*COMMENT= Flush Counter Value of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt2.counter[2][1]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt2[2][1] */
/*COMMENT= Flush Counter Value of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt2.counter[0][2]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt2[0][2] */
/*COMMENT= Flush Counter Value of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt2.counter[1][2]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt2[1][2] */
/*COMMENT= Flush Counter Value of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFlushCnt2.counter[2][2]*/
/*MODEL_NAME=rbl_SigChain_AccFlushCnt2[2][2] */
/*COMMENT= Flush Counter Value of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/**** rbl_SigChain_RateFlushCnt ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFlushCnt.counter[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFlushCnt[0][0]*/
/*COMMENT= Flush Counter Value of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFlushCnt.counter[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFlushCnt[1][0]*/
/*COMMENT= Flush Counter Value of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFlushCnt.counter[2][0]*/
/*MODEL_NAME=rbl_SigChain_RateFlushCnt[2][0]*/
/*COMMENT= Flush Counter Value of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
/**** rbl_SigChain_RateFlushCnt2 - For Second Filter****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFlushCnt2.counter[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFlushCnt2[0][0]*/
/*COMMENT= Flush Counter Value of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFlushCnt2.counter[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFlushCnt2[1][0]*/
/*COMMENT= Flush Counter Value of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFlushCnt2.counter[2][0]*/
/*MODEL_NAME=rbl_SigChain_RateFlushCnt2[2][0]*/
/*COMMENT= Flush Counter Value of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/**** rbl_SigChain_AccInitFlushCnt ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt.counter[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt[0][0]*/
/*COMMENT= Flush Counter Value of Initialisation of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt.counter[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt[1][0]*/
/*COMMENT= Flush Counter Value of Initialisation of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt.counter[2][0]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt[2][0]*/
/*COMMENT= Flush Counter Value of Initialisation of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt.counter[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt[0][1]*/
/*COMMENT= Flush Counter Value of Initialisation of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt.counter[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt[1][1]*/
/*COMMENT= Flush Counter Value of Initialisation of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt.counter[2][1]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt[2][1]*/
/*COMMENT= Flush Counter Value of Initialisation of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt.counter[0][2]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt[0][2]*/
/*COMMENT= Flush Counter Value of Initialisation of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt.counter[1][2]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt[1][2]*/
/*COMMENT= Flush Counter Value of Initialisation of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt.counter[2][2]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt[2][2]*/
/*COMMENT= Flush Counter Value of Initialisation of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt.counter[0][3]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt[0][3]*/
/*COMMENT= Flush Counter Value of Initialisation of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt.counter[1][3]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt[1][3]*/
/*COMMENT= Flush Counter Value of Initialisation of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt.counter[2][3]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt[2][3]*/
/*COMMENT= Flush Counter Value of Initialisation of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
/**** rbl_SigChain_AccInitFlushCnt2.counter - For Second Filter ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt2.counter[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt2[0][0]*/
/*COMMENT= Flush Counter Value of Initialisation of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt2.counter[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt2[1][0]*/
/*COMMENT= Flush Counter Value of Initialisation of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt2.counter[2][0]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt2[2][0]*/
/*COMMENT= Flush Counter Value of Initialisation of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt2.counter[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt2[0][1]*/
/*COMMENT= Flush Counter Value of Initialisation of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt2.counter[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt2[1][1]*/
/*COMMENT= Flush Counter Value of Initialisation of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt2.counter[2][1]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt2[2][1]*/
/*COMMENT= Flush Counter Value of Initialisation of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt2.counter[0][2]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt2[0][2]*/
/*COMMENT= Flush Counter Value of Initialisation of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt2.counter[1][2]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt2[1][2]*/
/*COMMENT= Flush Counter Value of Initialisation of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccInitFlushCnt2.counter[2][2]*/
/*MODEL_NAME=rbl_SigChain_AccInitFlushCnt2[2][2]*/
/*COMMENT= Flush Counter Value of Initialisation of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/**** rbl_SigChain_RateInitFlushCnt ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateInitFlushCnt.counter[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateInitFlushCnt[0][0]*/
/*COMMENT= Flush Counter Value of Initialisation of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateInitFlushCnt.counter[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateInitFlushCnt[1][0]*/
/*COMMENT= Flush Counter Value of Initialisation of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateInitFlushCnt.counter[2][0]*/
/*MODEL_NAME=rbl_SigChain_RateInitFlushCnt[2][0]*/
/*COMMENT= Flush Counter Value of Initialisation of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
/**** rbl_SigChain_RateInitFlushCnt2 - For Second Filter ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateInitFlushCnt2.counter[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateInitFlushCnt2[0][0]*/
/*COMMENT= Flush Counter Value of Initialisation of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateInitFlushCnt2.counter[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateInitFlushCnt2[1][0]*/
/*COMMENT= Flush Counter Value of Initialisation of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateInitFlushCnt2.counter[2][0]*/
/*MODEL_NAME=rbl_SigChain_RateInitFlushCnt2[2][0]*/
/*COMMENT= Flush Counter Value of Initialisation of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/* storage for filter tabs */

/**** rbl_SigChain_RateFilTabs ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[0][0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[0][0][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[1][0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[1][0][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[2][0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[2][0][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[0][0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[0][0][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[1][0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[1][0][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[2][0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[2][0][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[0][0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[0][0][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[1][0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[1][0][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[2][0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[2][0][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[0][0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[0][0][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[1][0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[1][0][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[2][0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[2][0][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[0][0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[0][0][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[1][0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[1][0][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[2][0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[2][0][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[0][0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[0][0][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[1][0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[1][0][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[2][0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[2][0][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[0][0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[0][0][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[1][0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[1][0][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[2][0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[2][0][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[0][0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[0][0][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[1][0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[1][0][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs.tabs[2][0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs[2][0][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
/**** rbl_SigChain_RateFilTabs2 - For second Filter ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[0][0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[0][0][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[1][0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[1][0][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[2][0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[2][0][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[0][0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[0][0][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[1][0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[1][0][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[2][0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[2][0][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[0][0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[0][0][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[1][0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[1][0][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[2][0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[2][0][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[0][0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[0][0][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[1][0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[1][0][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[2][0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[2][0][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[0][0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[0][0][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[1][0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[1][0][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[2][0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[2][0][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[0][0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[0][0][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[1][0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[1][0][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[2][0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[2][0][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[0][0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[0][0][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[1][0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[1][0][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[2][0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[2][0][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[0][0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[0][0][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[1][0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[1][0][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateFilTabs2.tabs[2][0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateFilTabs2[2][0][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/**** rbl_SigChain_AccFilTabs ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][0][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][0][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][0][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][1][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][1][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][1][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][2][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][2][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][2][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][3][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][3][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][3][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][3][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][3][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][3][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][0][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][0][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][0][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][1][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][1][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][1][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][1][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][1][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][1][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][2][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][2][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][2][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][2][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][2][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][2][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][3][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][3][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][3][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][3][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][3][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][3][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][3][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][3][2][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection2 of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][3][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][3][2][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection2 of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][3][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][3][2][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection2 of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][0][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][0][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][0][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][1][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][1][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][1][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][2][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][2][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][2][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][3][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][3][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][3][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][3][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][3][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][3][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][0][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][0][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][0][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][1][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][1][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][1][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][1][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][1][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][1][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][2][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][2][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][2][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][2][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][2][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][2][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][3][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][3][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][3][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][3][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][3][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][3][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][3][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][3][2][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection2 of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][3][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][3][2][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection2 of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][3][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][3][2][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection2 of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][0][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][0][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][0][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][1][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][1][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][1][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][2][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][2][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][2][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][3][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][3][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][3][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][3][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][3][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][3][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][0][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][0][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][0][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][1][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][1][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][1][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][1][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][1][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][1][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][2][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][2][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][2][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][2][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][2][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][2][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][3][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][3][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][3][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][3][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][3][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][3][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][3][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][3][2][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection2 of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][3][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][3][2][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection2 of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][3][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][3][2][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection2 of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][0][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][0][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][0][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][1][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][1][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][1][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][2][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][2][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][2][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][3][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][3][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][3][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][3][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][3][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][3][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][0][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][0][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][0][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][1][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][1][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][1][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][1][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][1][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][1][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][2][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][2][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][2][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][2][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][2][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][2][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][3][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][3][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][3][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][3][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][3][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][3][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[0][3][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[0][3][2][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection2 of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[1][3][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[1][3][2][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection2 of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs.tabs[2][3][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs[2][3][2][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection2 of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
/**** rbl_SigChain_AccFilTabs2 - For Second Filter****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][0][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][0][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][0][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][1][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][1][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][1][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][2][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][2][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][2][0][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection0 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][0][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][0][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][0][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][1][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][1][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][1][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][1][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][1][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][1][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][2][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][2][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][2][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][2][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][2][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][2][1][0][0]*/
/*COMMENT= Value of Tab0.0 in FilterSection1 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][0][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][0][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][0][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][1][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][1][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][1][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][2][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][2][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][2][0][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection0 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][0][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][0][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][0][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][1][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][1][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][1][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][1][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][1][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][1][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][2][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][2][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][2][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][2][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][2][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][2][1][1][0]*/
/*COMMENT= Value of Tab1.0 in FilterSection1 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][0][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][0][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][0][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][1][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][1][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][1][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][2][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][2][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][2][0][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection0 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][0][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][0][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][0][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][1][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][1][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][1][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][1][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][1][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][1][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][2][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][2][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][2][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][2][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][2][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][2][1][0][1]*/
/*COMMENT= Value of Tab0.1 in FilterSection1 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][0][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][0][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][0][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][1][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][1][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][1][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][2][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][2][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][2][0][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection0 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][0][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][0][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][0][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][1][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][1][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][1][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][1][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][1][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][1][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[0][2][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[0][2][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[1][2][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[1][2][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccFilTabs2.tabs[2][2][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccFilTabs2[2][2][1][1][1]*/
/*COMMENT= Value of Tab1.1 in FilterSection1 of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/**** rbl_SigChain_RateDerFilTabs ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs.tabs[0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs[0][0][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs.tabs[1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs[1][0][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs.tabs[2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs[2][0][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs.tabs[0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs[0][0][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs.tabs[1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs[1][0][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs.tabs[2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs[2][0][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs.tabs[0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs[0][0][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs.tabs[1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs[1][0][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs.tabs[2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs[2][0][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs.tabs[0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs[0][0][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs.tabs[1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs[1][0][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs.tabs[2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs[2][0][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
/**** rbl_SigChain_RateDerFilTabs2 - For Second Filter ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs2.tabs[0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs2[0][0][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs2.tabs[1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs2[1][0][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs2.tabs[2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs2[2][0][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs2.tabs[0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs2[0][0][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs2.tabs[1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs2[1][0][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs2.tabs[2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs2[2][0][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs2.tabs[0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs2[0][0][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs2.tabs[1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs2[1][0][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs2.tabs[2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs2[2][0][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs2.tabs[0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs2[0][0][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs2.tabs[1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs2[1][0][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RateDerFilTabs2.tabs[2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RateDerFilTabs2[2][0][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/**** rbl_SigChain_AccDerFilTabs ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][0][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][0][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][0][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][1][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][1][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][1][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][2][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][2][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][2][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][3].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][3][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][3].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][3][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][3].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][3][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][0][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][0][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][0][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][1][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][1][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][1][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][2][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][2][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][2][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][3].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][3][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][3].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][3][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][3].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][3][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][0][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][0][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][0][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][1][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][1][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][1][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][2][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][2][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][2][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][3].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][3][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][3].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][3][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][3].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][3][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][0][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][0][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][0][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][1][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][1][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][1][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][2][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][2][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][2][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[0][3].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[0][3][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[1][3].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[1][3][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs.tabs[2][3].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs[2][3][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
/**** rbl_SigChain_AccDerFilTabs2 - For Second Filter ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[0][0][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[1][0][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[2][0][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[0][1][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[1][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[1][1][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[2][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[2][1][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[0][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[0][2][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[1][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[1][2][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[2][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[2][2][0][0]*/
/*COMMENT= Value of Tab0.0 of DerivationSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[0][0][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[1][0][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[2][0][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[0][1][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[1][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[1][1][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[2][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[2][1][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[0][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[0][2][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[1][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[1][2][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[2][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[2][2][1][0]*/
/*COMMENT= Value of Tab1.0 of DerivationSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[0][0][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[1][0][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[2][0][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[0][1][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[1][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[1][1][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[2][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[2][1][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[0][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[0][2][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[1][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[1][2][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[2][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[2][2][0][1]*/
/*COMMENT= Value of Tab0.1 of DerivationSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[0][0][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[1][0][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[2][0][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[0][1][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[1][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[1][1][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[2][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[2][1][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[0][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[0][2][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[1][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[1][2][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccDerFilTabs2.tabs[2][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccDerFilTabs2[2][2][1][1]*/
/*COMMENT= Value of Tab1.1 of DerivationSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/**** rbl_SigChain_RatePhaCorrnTabs ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs.tabs[0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs[0][0][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs.tabs[1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs[1][0][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs.tabs[2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs[2][0][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs.tabs[0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs[0][0][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs.tabs[1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs[1][0][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs.tabs[2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs[2][0][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs.tabs[0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs[0][0][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs.tabs[1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs[1][0][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs.tabs[2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs[2][0][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs.tabs[0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs[0][0][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs.tabs[1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs[1][0][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs.tabs[2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs[2][0][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
/**** rbl_SigChain_RatePhaCorrnTabs2 - For Second Filter ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs2.tabs[0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs2[0][0][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs2.tabs[1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs2[1][0][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs2.tabs[2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs2[2][0][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs2.tabs[0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs2[0][0][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs2.tabs[1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs2[1][0][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs2.tabs[2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs2[2][0][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs2.tabs[0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs2[0][0][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs2.tabs[1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs2[1][0][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs2.tabs[2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs2[2][0][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs2.tabs[0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs2[0][0][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of RotX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs2.tabs[1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs2[1][0][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of RotY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_RatePhaCorrnTabs2.tabs[2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_RatePhaCorrnTabs2[2][0][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of RotZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

/**** rbl_SigChain_AccPhaCorrnTabs ****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][0][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][0][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][0][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][1][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][1][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][1][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][2][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][2][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][2][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][3].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][3][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][3].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][3][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][3].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][3][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][0][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][0][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][0][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][1][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][1][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][1][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][2][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][2][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][2][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][3].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][3][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][3].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][3][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][3].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][3][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][0][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][0][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][0][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][1][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][1][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][1][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][2][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][2][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][2][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][3].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][3][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][3].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][3][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][3].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][3][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][0][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][0][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][0][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][1][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][1][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][1][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][2][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][2][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][2][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[0][3].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[0][3][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccX3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[1][3].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[1][3][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccY3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs.tabs[2][3].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs[2][3][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccZ3 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
/**** rbl_SigChain_AccPhaCorrnTabs2 - For Second Filter****/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[0][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[0][0][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[1][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[1][0][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[2][0].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[2][0][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[0][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[0][1][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[1][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[1][1][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[2][1].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[2][1][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[0][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[0][2][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[1][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[1][2][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[2][2].filTabs[0][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[2][2][0][0]*/
/*COMMENT= Value of Tab0.0 of PhaseCorrSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[0][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[0][0][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[1][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[1][0][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[2][0].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[2][0][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[0][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[0][1][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[1][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[1][1][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[2][1].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[2][1][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[0][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[0][2][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[1][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[1][2][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[2][2].filTabs[1][0]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[2][2][1][0]*/
/*COMMENT= Value of Tab1.0 of PhaseCorrSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[0][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[0][0][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[1][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[1][0][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[2][0].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[2][0][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[0][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[0][1][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[1][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[1][1][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[2][1].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[2][1][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[0][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[0][2][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[1][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[1][2][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[2][2].filTabs[0][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[2][2][0][1]*/
/*COMMENT= Value of Tab0.1 of PhaseCorrSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[0][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[0][0][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccX0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[1][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[1][0][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccY0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[2][0].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[2][0][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccZ0 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[0][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[0][1][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccX1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[1][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[1][1][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccY1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[2][1].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[2][1][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccZ1 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[0][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[0][2][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccX2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[1][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[1][2][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccY2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AccPhaCorrnTabs2.tabs[2][2].filTabs[1][1]*/
/*MODEL_NAME=rbl_SigChain_AccPhaCorrnTabs2[2][2][1][1]*/
/*COMMENT= Value of Tab1.1 of PhaseCorrSection of AccZ2 */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

#endif
