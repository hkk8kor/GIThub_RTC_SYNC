/**********************************************************************************************************************
*
* COPYRIGHT RESERVED, 2022 Robert Bosch GmbH. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************/
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"

#include "Rte_Dcm.h"

 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmUpdateRxTable:-\n
 * This API is called by Dcm_Init function during power on,so that the application can switch the rx table(assign rx table to Dcm_Dsld_rxtable_pca),
 *  if they want, based on the ecu type(master/slave).
 *
 *
 *
 *  @param[in]         None
 *
 *  @param[out]        None
 *
 *  @retval            None
 */
void DcmAppl_DcmUpdateRxTable (void)
{
    /* add your implementation here*/

    /* User can switch the rx table, if they want, based on the ecu type(master/slave). */
    /* If the rx table is not switched by the application, it will take the rx table
     *  from the configuration*/
     /* Example code
     if ( ECU_IS_MASTER )
    {
        Dcm_Dsld_rxtable_pca = Dcm_Dsld_Conf_cs.ptr_rxtable_pca;
    }
    else
    {
        Dcm_Dsld_rxtable_pca = Dcm_Dsld_rx_table_slave_acu8;
    }
    End example code*/

}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
