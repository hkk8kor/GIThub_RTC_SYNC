/// @file rbl_CustIf_Hndl_Utils.c
/// @brief This header provides definitions for Communication control service
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Hndl_Utils.h"
#include <math.h>
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Local Definitions ***** */
/* Constants and Macro definitions */

/* Structure definitions */

/* Variables */

/* ***** END_SECTION Local Definitions ***** */
/* *********************************************************************************************************************
 * ***** API public: rbl_CustIf_Calc_Convert *****/

uint16 rbl_CustIf_Calc_Convert(float32 value, float32 formula, CompuMethod const *parameter)
{

    uint16 Phys_Value;
    float32 Converted_Value;
    float32 rawASWValue = 0.00f;

    /* divide the signal chain value receivied by corresponding sensitivity factor */
    rawASWValue = value / formula;

    /* convert the value from physical value to int */
    Converted_Value = rbl_CustIf_Calc_CompuMethod_Phy2Int(*parameter, rawASWValue);

    /* float to unsigned interger conversion */
    Phys_Value = RB_FloatToInt_f32_u16 (Converted_Value);

    return Phys_Value;
}

/* ***** END_API rbl_CustIf_Calc_Convert ***** */
/* ****************************************************************************
 * ***** API public: rbl_CustIf_Calc_CompuMethod_Phy2Int *****/

float32 rbl_CustIf_Calc_CompuMethod_Phy2Int(CompuMethod parameters, float32 phy_value)
{
    float32 phys_value, lower_limit, upper_limit  = 0.0f;
    uint32 isNaN = 0, isInf = 0;


    isNaN = (uint32) isnan(phy_value);
    isInf = (uint32) isinf(phy_value);

    if((0 != isNaN) || (0 != isInf))
    {
        phys_value = (float32)0; /* Initialising to zero */

    }
    else
    {

        // Compu method inverse for transmission
        phys_value = (phy_value - parameters.Offset) / parameters.Scale;

        // Calculate Lower and Upper limits after computation method
        lower_limit = parameters.LowerLimit;
        upper_limit = parameters.UpperLimit;

        // Validate Lower and Upper Limits
        if (phys_value < lower_limit)
        {
            phys_value = lower_limit;
        }
        else if (phys_value > upper_limit)
        {
            phys_value = upper_limit;
        }
        else
        {
            phys_value = Mfl_Round_f32(phys_value);
        }

    }

    return phys_value;
}


/* ***** END_API rbl_CustIf_Calc_CompuMethod_Phy2Int ***** */



/* ***** END_SECTION API functions ***** */
