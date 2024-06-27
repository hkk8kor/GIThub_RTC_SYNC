/// @file rbl_dcom_MB_RWDBI_VariantCoding.h
/// @brief The file provide the macros and variables for Varinat coding read and write file.
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_DCOM_MB_RWDBI_VARIANTCODING_H_
#define RBL_DCOM_MB_RWDBI_VARIANTCODING_H_

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/

/*
**********************************************************************************************************************
*  Constants and Macro definitions
**********************************************************************************************************************
*/
# define RBL_DCOM_AMG_VARINAT_CODING_U8     (2U)
# define RBL_DCOM_CALID_NUM_ITEMS_U8        (1U)
# define RBL_MB_VARIANT                     (0x00U)
# define RBL_AMG_VARIANT                    (0x01U)

/**
**********************************************************************************************************************
* Variables
**********************************************************************************************************************
*/

#if (RBFS_MMP2 == RBFS_MMP2_IMUB)
/*CAL ID  Ram Block*/
extern uint8 rbl_Mirrordcom_CalId_u8[16];

/*AMG SWITCH varinat coding RAM block*/
extern uint8 rbl_dcom_MirrorAMGVarSwitch_u8[1];
#endif

#endif /* RBL_DCOM_MB_RWDBI_VARIANTCODING_H_ */
