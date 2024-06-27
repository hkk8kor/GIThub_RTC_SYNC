/// @file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The file consists of the API's for Read Data by Identifier DID's identified for Customer Diagnostics for MB
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "rbl_dcom_Lib.h"
#include "rbl_dcom_MB_Pub.h"
#include "rbl_dcom_SWVersion.h"
#include "RBLCF_Hexblocks_Iterator.h"
#include "RBCM_CSWPrSettings_MMP2.h"

#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
#include "Rte_rbl_SwcDiagAdapter_Srv.h"
#endif

/*
**********************************************************************************************************************
* Macros
**********************************************************************************************************************
*/

/*
***************************************************
* Variables
**********************************************************************************************************************
*/

uint8 DCOM_SupplierPubKey_Sig_RAM_Mirror[258]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static uint16 DID0x01A2_DataLength = 0x00u;

#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
RBSECTION_START_REMAP_RODATA(.blockinterfacest_fsw_01)
#endif /* RBFS_Bootblock == RBFS_Bootblock_Enabled */
// volatile is required to prevent optimisation

static volatile const dcom_ApplHeader_tst dcom_ApplHeader_st =
{
	{DCOM_SOFTWARE_VERSION_YEAR,DCOM_SOFTWARE_VERSION_WEEK,DCOM_SOFTWARE_VERSION_PATCH_LEVEL},
	{RBL_IMUPLADATASWNR},
	{DCOM_SUPPLIERID_HIGHBYTE, DCOM_SUPPLIERID_LOWBYTE},
	{DCOM_DDSPCKG_YEAR,DCOM_DDSPCKG_MONTH},
	{DCOM_SUPPLIERID_HIGHBYTE,DCOM_SUPPLIERID_LOWBYTE}
};

#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
RBSECTION_END_REMAP_RODATA
#endif /* RBFS_Bootblock == RBFS_Bootblock_Enabled */


static void BootAddressRead(dcom_BootHeader_tst **PTR_BootHeaderInfo_tst)
{

    #if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
    /*MISRA Deviation ID : MMP2.11-001*//* MR12 RULE 11.4 VIOLATION : DCOM_BOOTLOADER_ADDRESS this is known 32-bit address in BL Range and conversion
    to pointer to read the data from address,the cast (dcom_BootHeader_tst *) is known and required to decode the data from
    32 bit address to structure type*/
    *PTR_BootHeaderInfo_tst = (dcom_BootHeader_tst *)( *(uint32*) DCOM_BOOTLOADER_ADDRESS);

    #endif
}

static Std_ReturnType BootAddressRangeCheck(dcom_BootHeader_tst  * const *PTR_BootHeaderInfo_tst)
{
	Std_ReturnType retVal = E_NOT_OK;
	#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
	/*MISRA Deviation ID : MMP2.11-001*//** MR12 RULE 11.4 VIOLATION: DCOM_APPLICATION_ENDADDRESS this is known 32-bit address in BL Range and conversion
    of PTR_BootHeaderInfo_tst structure pointer to 32 bit value to check the current BL address is in range. */
	if((*PTR_BootHeaderInfo_tst!=NULL_PTR)&&((uint32)*PTR_BootHeaderInfo_tst<=(uint32)DCOM_APPLICATION_ENDADDRESS))
	{
		retVal = E_OK;
	}
	#endif
	return retVal;

}
/* ****************************************************************************
 *  ***** API public: dcom_ActiveDiagnosticSession_F100_ReadData ***** */

Std_ReturnType dcom_ActiveDiagnosticSession_F100_ReadData (uint8 * Data)
{
	Dcm_SesCtrlType activeSession;
	Std_ReturnType   retVal = E_NOT_OK;

	if(Data != NULL_PTR)
    {
		/* return value not required. This is to Read the current active session */
		(void)Dcm_GetSesCtrlType(&activeSession);

		/* Read the Active Diagnostc info  */
		/*Active Diagnostic Status Application*/
		Data[0] = DCOM_ACTIVE_DIAG_STATUS_APPL;
		/*Active Diagnostic Variant*/
		Data[1] = DCOM_ACTIVE_DIAG_VARIANT;
		/*Active Diagnostic Version*/
		Data[2] = DCOM_ACTIVE_DIAG_VERSION;
		/*Active Session*/
		Data[3] = activeSession;

		retVal = E_OK;
    }

    return retVal;
}

/* ***** END_API dcom_ActiveDiagnosticSession_F100_ReadData ***** */

/* ****************************************************************************
 * ***** API public: dcom_DDS_Package_Release_F10D_ReadData *****  */

Std_ReturnType dcom_DDS_Package_Release_F10D_ReadData (uint8 * Data)
{
	Std_ReturnType   retVal = E_NOT_OK;
	dcom_BootHeader_tst *PTR_BootHeaderInfo_tst = NULL_PTR;

	/*To Copy Bootloader address to local sturcture pointer*/
	BootAddressRead(&PTR_BootHeaderInfo_tst);

    if(Data != NULL_PTR)
    {
        /* Application Software */
        Data[0] = dcom_ApplHeader_st.ApplDdsPackageReleaseOfApplication[0];
        /* Application Software */
        Data[1] = dcom_ApplHeader_st.ApplDdsPackageReleaseOfApplication[1];

#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)

        if( E_OK == BootAddressRangeCheck(&PTR_BootHeaderInfo_tst))
        {
            /* To access data from this pointer */
            Data[2] = PTR_BootHeaderInfo_tst->BootDdsPackageReleaseInfo[0];
            /* To access data from this pointer */
            Data[3] = PTR_BootHeaderInfo_tst->BootDdsPackageReleaseInfo[1];

            retVal = E_OK;
        }

#endif
    }

    return retVal;

}

/* ***** END_API  dcom_DDS_Package_Release_F10D_ReadData ***** */


/* ****************************************************************************
 * ***** API public: dcom_Diagnostic_Trace_Memory_102_ReadData ***** */

Std_ReturnType dcom_Diagnostic_Trace_Memory_102_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
		/* Read Diagnosis Tracing Memory Data from NvM */
		retVal =dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_DiagTraceMem ,
		Data,NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_DiagTraceMem, DCOM_READ_PDMEMPTY);
    }

    return retVal;
}

/* ***** END_API  dcom_Diagnostic_Trace_Memory_0102_ReadData ***** */


/* ****************************************************************************
 * ***** API public: dcom_Ecu_Extract_Version_EF00_ReadData ***** */

Std_ReturnType dcom_Ecu_Extract_Version_EF00_ReadData (uint8 * Data)
{
    Std_ReturnType retVal = E_NOT_OK;
    uint8 i;
    dcom_EcuExtractVersion_tst dcom_EcuExtractVersion_st =
    {
        {DCOM_ECU_EXTRACT_MAJOR_VERSION},{DCOM_ECU_EXTRACT_MINOR_VERSION},{DCOM_ECU_EXTRACT_PATCH_VERSION},
		{DCOM_ECU_EXTRACT_INFO_ID_TYPE},{DCOM_ECU_EXTRACT_INFO_XDIS_VERSION},
		{DCOM_ECU_EXTRACT_INFO_EXPORT_DATE},{DCOM_ECU_EXT_INFO_ECU_NAME},
		{DCOM_ECU_EXTRACT_INFO_CHECKSUM}
    };

	if(Data != NULL_PTR)
    {
		/*To update ECU Extract Version*/
		/*ECU Extract Major Version*/
        Data[0] = dcom_EcuExtractVersion_st.EcuMajorVersion;
		/*ECU Extract Minor Version*/
        Data[1] = dcom_EcuExtractVersion_st.EcuMinorVersion;
		/*ECU Extract Patch Level*/
        Data[2] = dcom_EcuExtractVersion_st.EcuPatchLevel;
		/*ECU Extract identification Type*/
        Data[3] = dcom_EcuExtractVersion_st.EcuIdentificationType;

		/*ECU XDIS Version*/
		for(i=0;i<10;i++)
        {
            Data[4+i] = dcom_EcuExtractVersion_st.EcuXDISVersion[i];
        }

		/*ECU Export Date*/
		for(i=0;i<10;i++)
        {
            Data[14+i] = dcom_EcuExtractVersion_st.EcuExportDate[i];
        }

		/*ECU Name*/
		for(i=0;i<30;i++)
        {
            Data[24+i] = dcom_EcuExtractVersion_st.EcuName[i];
        }

		/*ECU Check Sum*/
		for(i=0;i<40;i++)
        {
            Data[54+i] = dcom_EcuExtractVersion_st.EcuCheckSum[i];
        }

		retVal = E_OK;
    }

       return retVal;
}

/* ***** END_API dcom_Ecu_Extract_Version_EF00_ReadData ***** */


/* ****************************************************************************
 * ***** API public: dcom_ECUSerialNumber_F18C_ReadData ***** */

Std_ReturnType dcom_ECUSerialNumber_F18C_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /*Call to NvM Read Generic api for reading the ECU serial Number*/
        retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_ECU_SerialNr,
		Data,NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_ECU_SerialNr, DCOM_READ_PDMEMPTY_ASCII_NULL);
    }

    return retVal;

}

/* ***** END_API dcom_ECUSerialNumber_F18C_ReadData ***** */


/* ****************************************************************************
 * ***** API public: dcom_HardwareSupplier_F154_ReadData ***** */

Std_ReturnType dcom_HardwareSupplier_F154_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /* Read the HW Supplier Information Info */
        Data[0] = dcom_ApplHeader_st.ApplHwSupplierInformation[0];
        Data[1] = dcom_ApplHeader_st.ApplHwSupplierInformation[1];

		retVal = E_OK;
    }

    return retVal;
}

/* ***** END_API dcom_HardwareSupplier_F154_ReadData ***** */


/* ****************************************************************************
 * ***** API public: dcom_HardwareVersion_F150_ReadData ***** */

Std_ReturnType dcom_HardwareVersion_F150_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /*Call to NvM Read Generic api for reading the HW Version Info */
        retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_rbl_HwVers,
		Data,NVM_CFG_NV_BLOCK_LENGTH_rbl_HwVers, DCOM_READ_PDMEMPTY);
    }
    return retVal;
}

/* ***** END_API dcom_HardwareVersion_F150_ReadData ***** */


/* ****************************************************************************
 * ***** API public: dcom_MercedesCarGroupHardware_F111_ReadData ***** */

Std_ReturnType dcom_MercedesCarGroupHardware_F111_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /*Call to NvM Read Generic api for reading the Mercedes Car Group Hardware Part Number Info */
        retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_HW_PartNumber,
		Data,NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_HW_PartNumber, DCOM_READ_PDMEMPTY_ASCII_NULL);
    }

    return retVal;
}

/* ***** END_API dcom_MercedesCarGroupHardware_F111_ReadData ***** */


/* ****************************************************************************
 * ***** API public:dcom_Read_Software_Fingerprint_s_Bootloader_Data_F15B_ReadData***** */

Std_ReturnType dcom_Read_Software_Fingerprint_s_Bootloader_Data_F15B_ReadData(uint8 * Data)
{
   Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /*Call to NvM Read Generic api for reading the SW fingerPrint  */
        retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_FLASH_MB_SWFingerprint_LB0,
        Data,NVM_CFG_NV_BLOCK_LENGTH_FLASH_MB_SWFingerprint_LB0, DCOM_READ_PDMEMPTY);
    }

     return retVal;
}

/* ***** END_API dcom_Read_Software_Fingerprint_s_Bootloader_Data_F15B_ReadData ***** */


/* ****************************************************************************
 * ***** API public:dcom_Read_Software_Fingerprint_s_F15B_ReadData ***** */

Std_ReturnType dcom_Read_Software_Fingerprint_s_Application_Data_F15B_ReadData(uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /*Call to NvM Read Generic api for reading the SW fingerPrint  */
        retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_FLASH_MB_SWFingerprint_LB1,
		Data,NVM_CFG_NV_BLOCK_LENGTH_FLASH_MB_SWFingerprint_LB1, DCOM_READ_PDMEMPTY);
    }

     return retVal;

}

/* ***** END_API dcom_Read_Software_Fingerprint_s_F15B_ReadData ***** */


/* ****************************************************************************
 * ***** API public:dcom_ReprogrammingAttemptCounter_Bootloader_Data_0100_ReadData***** */

Std_ReturnType dcom_ReprogrammingAttemptCounter_Bootloader_Data_0100_ReadData(uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /* Read Number of reprogramming Attempt from NvM --> Data[0]HB and Data[1]LB */
        retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_ReprogAttCounter_LB0,
        Data,NVM_CFG_NV_BLOCK_LENGTH_DCOM_ReprogAttCounter_LB0 , DCOM_READ_PDMEMPTY);

        if(retVal == E_OK)
        {
            /* The Maximum number of reprogramming attempts is 1000 (0x03E8)*/
            Data[2] = (uint8)DCOM_MAX_REPROG_ATT_MSB;
            Data[3] = (uint8)DCOM_MAX_REPROG_ATT_LSB;
        }
    }

    return retVal;
}

/* ***** END_API dcom_ReprogrammingAttemptCounter_Bootloader_Data_0100_ReadData ***** */


/* ****************************************************************************
 * ***** API public: dcom_ReprogrammingAttemptCounter_0100_ReadData ***** */

Std_ReturnType dcom_ReprogrammingAttemptCounter_Application_Data_0100_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /* Read Number of reprogramming Attempt from NvM --> Data[0]HB and Data[1]LB */
        retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_ReprogAttCounter_LB1,
		Data,NVM_CFG_NV_BLOCK_LENGTH_DCOM_ReprogAttCounter_LB1 , DCOM_READ_PDMEMPTY);

        if(retVal == E_OK)
        {
            /* The Maximum number of reprogramming attempts is 1000 (0x03E8)*/
            Data[2] = (uint8)DCOM_MAX_REPROG_ATT_MSB;
            Data[3] = (uint8)DCOM_MAX_REPROG_ATT_LSB;
        }
    }

    return retVal;
}

/* ***** END_API dcom_ReprogrammingAttemptCounter_0100_ReadData ***** */

/* ****************************************************************************
 * ***** API public: dcom_SoftwareSupplier_Bootloader_F155_ReadData ***** */

Std_ReturnType dcom_SoftwareSupplier_Bootloader_F155_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;
    if(Data != NULL_PTR)
    {
        /* Read the Boot SW supplier Info */
        Data[0] = DCOM_SUPPLIERID_HIGHBYTE;
        Data[1] = DCOM_SUPPLIERID_LOWBYTE;

        retVal = E_OK;
     }
    return retVal;
}

/* ***** END_API dcom_SoftwareSupplier_Bootloader_F155_ReadData ***** */

/* ****************************************************************************
 * ***** API public: dcom_SoftwareSupplier_Application_F155_ReadData ***** */

Std_ReturnType dcom_SoftwareSupplier_Application_F155_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /* Read the SW supplier Info */
        Data[0] = dcom_ApplHeader_st.ApplSwSupplierInformation[0];
        Data[1] = dcom_ApplHeader_st.ApplSwSupplierInformation[1];

        retVal = E_OK;
    }

    return retVal;
}

/* ***** END_API dcom_SoftwareSupplier_Application_F155_ReadData ***** */

/* ****************************************************************************
 * ***** API public: dcom_Diagnostic_Extract_Version_EF01_ReadData ***** */

Std_ReturnType dcom_Diagnostic_Extract_Version_EF01_ReadData (uint8 * Data)
{
    Std_ReturnType retVal = E_NOT_OK;
    uint8 i;
    dcom_DiagnosticExtractVersion_tst dcom_DiagnosticExtractVersion_st =
    {
        {DCOM_DIAGNOSTIC_EXTRACT_MAJOR_VERSION},{DCOM_DIAGNOSTIC_EXTRACT_MINOR_VERSION},
		{DCOM_DIAGNOSTIC_EXTRACT_PATCH_VERSION},{DCOM_DIAGNOSTIC_EXTRACT_CANDELA_VERSION},
        {DCOM_DIAGNOSTIC_EXTRACT_DDM_VERSION},{DCOM_DIAGNOSTIC_EXTRACT_EXPORTED_DIAGNOSTIC_VARIANT}
    };

	if(Data != NULL_PTR)
	{
		/*To update Diagnostic Extract Version*/
		/*Diagnostic Extract Major Version*/
		Data[0]=dcom_DiagnosticExtractVersion_st.DiagnosticExtractMajorVersion;
		/*Diagnostic Extract Minor Version*/
		Data[1]=dcom_DiagnosticExtractVersion_st.DiagnosticExtractMinorVersion;
		/*Diagnostic Extract Patch Version*/
		Data[2]=dcom_DiagnosticExtractVersion_st.DiagnosticExtractPatchVersion;

		/*Diagnostic Extract Candela Version*/
		for(i=0;i<10;i++)
		{
			Data[3+i] = dcom_DiagnosticExtractVersion_st.DiagnosticExtractCandelaVersion[i];
		}

		/*Diagnostic Extract DDM Version*/
		for(i=0;i<10;i++)
		{
			Data[13+i] = dcom_DiagnosticExtractVersion_st.DiagnosticExtractDDMVersion[i];
		}

		/*Diagnostic Extract Exported Diagnostic Variant*/
		for(i=0;i<30;i++)
		{
			Data[23+i] = dcom_DiagnosticExtractVersion_st.DiagnosticExtractExportedDiagnosticVariant[i];
		}

		retVal = E_OK;
    }

	return retVal;
}

/* ***** END_API dcom_Diagnostic_Extract_Version_EF01_ReadData ***** */


/* ****************************************************************************
 * ***** API public: dcom_ECU_Name_F104_ReadData ***** */

Std_ReturnType dcom_ECU_Name_F104_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;
    uint8 i;
    dcom_EcuName_tst dcom_EcuName_st =
    {
		{DCOM_IMU_ECU_NAME}
    };

    if(Data != NULL_PTR)
    {
		/*ECU Name*/
        for(i=0;i<10;i++)
        {
            Data[i] = dcom_EcuName_st.ImuEcuName[i];
        }

		retVal = E_OK;
    }

	return retVal;
}

/* ***** END_API dcom_ECU_Name_F104_ReadData ***** */


/* ****************************************************************************
 * ***** API public: dcom_MercedesCarGroupSoftware_F121_ReadData ***** */

Std_ReturnType dcom_MercedesCarGroupSoftware_F121_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;
    uint8 i;
    dcom_BootHeader_tst *PTR_BootHeaderInfo_tst = NULL_PTR;

    /*To Copy Bootloader address to local sturcture pointer*/
    BootAddressRead(&PTR_BootHeaderInfo_tst);

    if(Data != NULL_PTR)
    {

#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)

        if( E_OK == BootAddressRangeCheck(&PTR_BootHeaderInfo_tst))
        {
            /* Read the Mercedes Car Group SW Part Number information of Bootloader Data  */
            for(i=0;i<10;i++)
            {
                Data[i] = PTR_BootHeaderInfo_tst->BootSwPartNumber[i];
            }

            retVal = E_OK;
        }
#endif
        /* Read the Mercedes Car Group SW Part Number information of Application data  */
        for(i=0;i<10;i++)
        {
            Data[10+i] = dcom_ApplHeader_st.ApplSwPartNumber[i];
        }

    }

    return retVal;
}

/* ***** END_API dcom_MercedesCarGroupSoftware_F121_ReadData ***** */

/* ****************************************************************************
 * ***** API public: dcom_Minimum_Software_Version_Bootloader_EF05_ReadData ***** */

Std_ReturnType dcom_Minimum_Software_Version_Bootloader_EF05_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /*Call to NvM Read Generic api for reading Minimum software version for Bootloader Logical Block  */
         retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_MinimumSWVersion_LB0,
                Data, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_MinimumSWVersion_LB0, DCOM_READ_PDMEMPTY);

    }
    return retVal;
}

/* ***** END_API dcom_Minimum_Software_Version_Bootloader_EF05_ReadData ***** */

/* ****************************************************************************
 *
 * ***** API public: dcom_Minimum_Software_Version_Application_EF05_ReadData ***** */

Std_ReturnType dcom_Minimum_Software_Version_Application_EF05_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /*Call to NvM Read Generic api for reading Minimum software version for Application Logical Block  */
         retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_MinimumSWVersion,
                Data, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_MinimumSWVersion, DCOM_READ_PDMEMPTY);

    }
    return retVal;
}

/* ***** END_API dcom_Minimum_Software_Version_Application_EF05_ReadData ***** */

/* ****************************************************************************
 * ***** API public: dcom_BootLoaderSoftwareVersion_F151_F153_ReadData  ***** */

Std_ReturnType dcom_BootSoftwareVersion_F151_F153_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;
    dcom_BootHeader_tst *PTR_BootHeaderInfo_tst = NULL_PTR;

    /*To Copy Bootloader address to local sturcture pointer*/
    BootAddressRead(&PTR_BootHeaderInfo_tst);

    if(Data != NULL_PTR)
    {

#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)

        if( E_OK == BootAddressRangeCheck(&PTR_BootHeaderInfo_tst))
        {

            Data[0] = PTR_BootHeaderInfo_tst->BootSwVersion[0];
            Data[1] = PTR_BootHeaderInfo_tst->BootSwVersion[1];
            Data[2] = PTR_BootHeaderInfo_tst->BootSwVersion[2];

            retVal = E_OK;
        }
#endif

    }

    return retVal;
}

/* ***** END_API dcom_BootLoaderSoftwareVersion_F151_F153_ReadData  ***** */


/* ****************************************************************************
 * ***** API public: dcom_SoftwareVersion_Application_F151_ReadData ***** */

Std_ReturnType dcom_SoftwareVersion_Application_F151_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /* Read the SW Version Info */
		/*Software Version Year*/
        Data[0] = DCOM_SOFTWARE_VERSION_YEAR;
        /*Software Version Week*/
        Data[1] = DCOM_SOFTWARE_VERSION_WEEK;
		/*Software Version Patch Level*/
        Data[2] = DCOM_SOFTWARE_VERSION_PATCH_LEVEL;

        retVal = E_OK;
    }

    return retVal;
}

/* ***** END_API dcom_SoftwareVersion_Application_F151_ReadData ***** */


/* ****************************************************************************
 * ***** API public: dcom_StandardApplicationSWPackageSWVersion_EF03_ReadData ***** */

Std_ReturnType dcom_StandardApplicationSWPackageSWVersion_EF03_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /* Shall be in the BCD format*/
        /* Release Major Version */
        Data[0]  = (uint8) DCOM_SWRELEASE_MAJORVERSION;
        /* Release Minor Version */
        Data[1]  = (uint8) DCOM_SWRELEASE_MINORVERSION;
        /* Release Patch level */
        Data[2]  = (uint8) DCOM_SWSPRINT_MAJORVERSION;
        /* Release Build Version */
        Data[3]  = (uint8) DCOM_SWSPRINT_MINORVERSION;

        retVal = E_OK;
    }

    return retVal;
}

/* ***** END_API  dcom_StandardApplicationSWPackageSWVersion_EF03_ReadData ***** */


/* *******************************************************************************************
 * ***** API public: dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData ***** */

Std_ReturnType dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal  = E_NOT_OK;
    uint8 i;
    uint8 l_dcom_DeviceId[4] = {0, 0, 0, 0};
    RBLCF_HexBlockLayout_t l_dcom_HexBlock;

    if(Data != NULL_PTR)
    {
        /* Micro Controller Identification*/
        RBLCF_GetFirstHexBlock(&l_dcom_HexBlock);
        while (l_dcom_HexBlock.hasNext)
        {
            if((l_dcom_HexBlock.HexInfoRef->BlockStructureID == RBLCF_HEXINFOTYPE_FSW)
             ||(l_dcom_HexBlock.HexInfoRef->BlockStructureID == RBLCF_HEXINFOTYPE_COMPLETE))
            {
                //we have found an FSW or Complete block - we take the data from that block
                break;
            }
            RBLCF_GetNextHexBlock(&l_dcom_HexBlock);
        }

        memcpy(l_dcom_DeviceId,(const uint8*)(&l_dcom_HexBlock.HexBlockRef->DeviceID),
		sizeof(l_dcom_HexBlock.HexBlockRef->DeviceID));


        for(i=0;i<12;i++)
        {
            Data[i]=DCOM_READ_PDMEMPTY_ASCII_NULL;
        }
        Data[12] = dcom_Lib_HexNibble2ASCII (l_dcom_DeviceId[3] >> 4);
        Data[13] = dcom_Lib_HexNibble2ASCII (l_dcom_DeviceId[3] & 0x0Fu);
        Data[14] = dcom_Lib_HexNibble2ASCII (l_dcom_DeviceId[2] >> 4);
        Data[15] = dcom_Lib_HexNibble2ASCII (l_dcom_DeviceId[2] & 0x0Fu);
        Data[16] = dcom_Lib_HexNibble2ASCII (l_dcom_DeviceId[1] >> 4);
        Data[17] = dcom_Lib_HexNibble2ASCII (l_dcom_DeviceId[1] & 0x0Fu);
        Data[18] = dcom_Lib_HexNibble2ASCII (l_dcom_DeviceId[0] >> 4);
        Data[19] = dcom_Lib_HexNibble2ASCII (l_dcom_DeviceId[0] & 0x0Fu);

        retVal = E_OK;
    }

    return retVal;
}

/* ***** END_API  dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData ***** */


/* *************************************************************************************************
 * ***** API public: dcom_StandardApplicationSWPackageSupplierIdentification_EF03_ReadData ***** */

Std_ReturnType dcom_StandardApplicationSWPackageSupplierIdentification_EF03_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /* Supplier Identification is 0x0003 */
        /* Supplier Identification MSB*/
        Data[0] = dcom_ApplHeader_st.ApplSwSupplierInformation[0];
        /* Supplier Identification LSB*/
        Data[1] = dcom_ApplHeader_st.ApplSwSupplierInformation[1];

        retVal = E_OK;
    }

    return retVal;

}
/* ***** END_API  dcom_StandardApplicationSWPackageSupplierIdentification_EF03_ReadData ***** */

/* *************************************************************************************************
 * ***** API public: dcom_StandardApplicationSWPackage_AUTOSAR_Platform_EF03_ReadData ***** */

Std_ReturnType dcom_StandardApplicationSWPackage_AUTOSAR_Platform_EF03_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
           /*IMU supports Classic AUTOSAR Platfrom*/
        Data[0] = DCOM_AUTOSAR_CLASSIC;

        retVal = E_OK;
    }

    return retVal;

}
/* ***** END_API  dcom_StandardApplicationSWPackage_AUTOSAR_Platform_EF03_ReadData ***** */


/* *************************************************************************************
 * ***** API public: dcom_Supported_Configuration_Mechanisms_F131_ReadData ***** */

Std_ReturnType dcom_Supported_Configuration_Mechanisms_F131_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /*Updates Supported Configuration Mechanisms */
        Data[0] = 0x00;

		retVal = E_OK;

    }
    return retVal;
}

/* ***** END_API dcom_Supported_Configuration_Mechanisms_F131_ReadData ***** */


/* *******************************************************************************
 * ***** API public: dcom_VedocRelavantHardwarePartNumber_F103_ReadData ***** */

Std_ReturnType dcom_VedocRelavantHardwarePartNumber_F103_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;
    if(Data != NULL_PTR)
    {
        /* Call to NvM Read Generic api for reading the Vedoc relavant HW Part Number */
        retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_HW_PartNumber,
		Data,NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_HW_PartNumber,DCOM_READ_PDMEMPTY_ASCII_NULL);
    }

    return retVal;
}

/* ***** END_API  dcom_VedocRelavantHardwarePartNumber_F103_ReadData ***** */


/* *******************************************************************************************
 * ***** API public: dcom_VedocRelavantHardwareSupplierIdentification_F103_ReadData ***** */

Std_ReturnType dcom_VedocRelavantHardwareSupplierIdentification_F103_ReadData (uint8 * Data)
{
    uint8 byte_01;
    uint8 byte_02;
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        Data[0] = (uint8)DCOM_READ_PDMEMPTY_ASCII_NULL;

        /* --- HW Supplier is set to 0003h for Bosch --- */
        byte_01 = DCOM_SUPPLIERID_HIGHBYTE >> 4;
        byte_02 = DCOM_SUPPLIERID_HIGHBYTE & 0x0Fu;

        Data[1] = dcom_Lib_HexNibble2ASCII (byte_01);
        Data[2] = dcom_Lib_HexNibble2ASCII (byte_02);

        byte_01 = DCOM_SUPPLIERID_LOWBYTE >> 4;
        byte_02 = DCOM_SUPPLIERID_LOWBYTE & 0x0Fu;

        Data[3] = dcom_Lib_HexNibble2ASCII (byte_01);
        Data[4] = dcom_Lib_HexNibble2ASCII (byte_02);

        retVal = E_OK;
    }

    return retVal;
}
/* ***** END_API  dcom_VedocRelavantHardwareSupplierIdentification_F103_ReadData ***** */


/* *******************************************************************************
 * ***** API public: dcom_VedocRelavantECUSerialNumber_F103_ReadData ***** */

Std_ReturnType dcom_VedocRelavantECUSerialNumber_F103_ReadData (uint8 * Data)
{

    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /*Call to NvM Read Generic api for reading the Vedoc relavant ECU Serial Number */
        retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_ECU_SerialNr,
		Data,NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_ECU_SerialNr,DCOM_READ_PDMEMPTY_ASCII_NULL);
    }

    return retVal;
}

/* ***** END_API  dcom_VedocRelavantECUSerialNumber_F103_ReadData ***** */




/* ****************************************************************************
 * ***** API public: dcom_VehicleOdometerLowResolution_10A_ReadData ***** */

Std_ReturnType dcom_VehicleOdometerLowResolution_10A_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)

        /* reading the odometer in low resolution from SWCDiag*/
        retVal = rbl_SwcDiagAdapter_ReadOdometerData(Data);

#endif
    }

    return retVal;
}

/* ***** END_API  dcom_VehicleOdometerLowResolution_10A_ReadData ***** */




/* ****************************************************************************
 * ***** API public: dcom_CurrentOperatingTime_133_ReadData ***** */

Std_ReturnType dcom_CurrentOperatingTime_133_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)

        /* reading the operting time from SWCDiag*/
        retVal = rbl_SwcDiagAdapter_ReadOperatingTimeData(Data);
#endif
    }

    return retVal;
}

/* ***** END_API  dcom_CurrentOperatingTime_133_ReadData ***** */

/* ****************************************************************************
 * ***** API public: dcom_ActivateSupplierSpecificMessages_012A_ReadData ***** */
Std_ReturnType dcom_ActivateSupplierSpecificMessages_012A_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_NOT_OK;

    if(Data != NULL_PTR)
    {
        /*Call to NvM Read Generic api for reading the Supplier Specific Message Mode */
        retVal = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_ActivateSupplierMsgs,
                Data,NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_ActivateSupplierMsgs,DCOM_READ_PDMEMPTY);
    }

    return retVal;
}
/* ***** END_API  dcom_ActivateSupplierSpecificMessages_012A_ReadData ***** */

 /* ***** API public: dcom_ActivateSupplierSpecificMessages_012A_ReadData ***** */
Std_ReturnType dcom_Trust_Model_CSR_Supplier_Signature_01A2_ReadData (uint8 * Data)
{
    Std_ReturnType   retVal = E_OK;

    if(Data != NULL_PTR)
    {
        /*Copying the RAM mirror Data to DCM Biffer*/
        memcpy(Data,DCOM_SupplierPubKey_Sig_RAM_Mirror,DID0x01A2_DataLength);
    }

    return retVal;
}
/* ***** END_API  dcom_ActivateSupplierSpecificMessages_012A_ReadData ***** */

/* ***** API public: dcom_Trust_Model_CSR_Supplier_Signature_01A2_ReadDataLength ***** */
Std_ReturnType dcom_Trust_Model_CSR_Supplier_Signature_01A2_ReadDataLength (uint16 * DidLength)
{
    Std_ReturnType   retVal = E_NOT_OK;
    uint8 Supplier_PublicKey =0x00;
    uint8 Supplier_Signature =0x00;

    Supplier_PublicKey = DCOM_SupplierPubKey_Sig_RAM_Mirror[0];
    if(Supplier_PublicKey <=128u)
    {
        Supplier_Signature = DCOM_SupplierPubKey_Sig_RAM_Mirror[Supplier_PublicKey+1];

        if( Supplier_Signature <= 128u )
        {
            DID0x01A2_DataLength = (Supplier_PublicKey + Supplier_Signature)+2u;
            retVal = E_OK;
        }
        else
        {
            retVal = E_NOT_OK;
        }

    }
    else
    {
        retVal = E_NOT_OK;
    }

    *DidLength = DID0x01A2_DataLength;

    return retVal;
}
/* ***** END_API  dcom_Trust_Model_CSR_Supplier_Signature_01A2_ReadDataLength ***** */
