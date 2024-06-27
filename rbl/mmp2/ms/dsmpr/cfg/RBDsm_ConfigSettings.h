#ifndef RBDSM_CONFIGSETTINGS_H__
#define RBDSM_CONFIGSETTINGS_H__

/**********************************************************************************/
/* [COPYRIGHT]                                                                    */
/* Robert Bosch GmbH reserves all rights even in the event of industrial          */
/* property rights. We reserve all rights of disposal such as copying and         */
/* passing on to third parties.                                                   */
/* [COPYRIGHT_END]                                                                */
/**********************************************************************************/
#include "Cfg_MTC_ConfigurationDefines.cfg"
#include "Det/RBDET_ConfigSettings.h"
#include "STM/RBSTM_ConfigSettings.h"
#include "RB_DsmPr_ConfigElements_MMP2.h"
#include "RBVoltageHandler/RBVoltageHandler_ConfigSettings.h"


  // RBSMM
  #include "rbl/mmp2/ms/dsmpr/cfg/rbsmm/RBSMM_ConfigSettings.h"

  // required for compilation: RBEMM_Config.h included by FW-Used-Generator.
  // required - RBFS_EMM not checked before ... in RBEMM_Config.h

#include "rb/as/core/app/dsm/rbdet/api/RBDET_Config.h"

#include "rb/as/core/app/dsm/api/RBDSM_ConfigElements.h"

#ifndef RBFS_DSMSimulation
  #if (RBFS_ConfigurationType == RBFS_ConfigurationType_DEVELOP)
    #if (RBFS_DEVELOP == RBFS_DEVELOP_DSMSimBuild)
        #define RBFS_DSMSimulation RBFS_DSMSimulation_ON
        #define RBFS_HSWSimExcludeSoftEcu RBFS_HSWSimExcludeSoftEcu_On
    #else
        #define RBFS_DSMSimulation RBFS_DSMSimulation_OFF
    #endif
  #else
    #define RBFS_DSMSimulation RBFS_DSMSimulation_OFF
  #endif ///< RBFS_ConfigurationType == RBFS_ConfigurationType_DEVELOP)
#endif ///< #ifndef RBFS_DSMSimulation

#if (RBFS_DSMSimulation == RBFS_DSMSimulation_OFF)
  #define RBFS_DiamantProOnlineGeneration    RBFS_DiamantProOnlineGeneration_Yes
#else
  #define RBFS_DiamantProOnlineGeneration   RBFS_DiamantProOnlineGeneration_No
#endif

/* ------------------------------------------------------------------------ */
// Function Switch for usage of DSMDecentralizedGraphSupport
/* ------------------------------------------------------------------------ */
#define RBFS_DSMDecentralizedGraphSupport RBFS_DSMDecentralizedGraphSupport_On

//Enabling IUMPR feature for PSW MS OBD testing topic - This is only a temporary workaround until official IUMPR monitoring are available
#ifndef RBFS_RBOBDIUMPRHandler
        #define RBFS_RBOBDIUMPRHandler RBFS_RBOBDIUMPRHandler_PROJECTSPECIFIC
#endif
/* ------------------------------------------------------------------------ */
/* RBFS_ARDsmInterface                                             */
/* ------------------------------------------------------------------------ */
#define RBFS_ARDsmInterface RBFS_ARDsmInterface_42
/*DE|setting if AR4.2 interface is used. */

#ifndef RBFS_RBRSSRedundantPath
    #define RBFS_RBRSSRedundantPath RBFS_RBRSSRedundantPath_OFF
#endif

#ifndef RBFS_DSMDoorsGeneratedTest
    #define RBFS_DSMDoorsGeneratedTest RBFS_DSMDoorsGeneratedTest_ON
#endif

//Temperory solution for the switch activation in the dsmpr
#define RBFS_RBAPLPLANTDemIfForAR426 RBFS_RBAPLPLANTDemIfForAR426_ON

#ifndef RBFS_DSMPostBuildSupport
#define RBFS_DSMPostBuildSupport RBFS_DSMPostBuildSupport_Off
#endif

#ifdef  RBFS_ApbDynConfig
 #if(RBFS_ApbDynConfig == RBFS_ApbDynConfig_Yes)
  #define RBFS_RBVarSupport RBFS_RBVarSupport_Yes
 #else
  #define RBFS_RBVarSupport RBFS_RBVarSupport_No
 #endif
#else
 #define RBFS_RBVarSupport RBFS_RBVarSupport_No
#endif

#endif
