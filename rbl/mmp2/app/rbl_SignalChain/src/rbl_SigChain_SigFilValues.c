/// @file rbl_SigChain_SigFilValues.c
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.



/* ***** SECTION Includes ***** */
#include "rbl_SigChain_SigFil.h"

/* Hardcoded Filter coefficients*/

#if (RBFS_SigChainNoFilter ==  RBFS_SigChainNoFilter_Available)
rbl_SigChain_FilterArray_t rbl_SigChain_FilValNoFilter = {{
	{
		{0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f}
	},
	{
	    {0.0f, 0.0f},
	    {1.0f, 0.0f, 0.0f}
	}

}};
#endif

#if (RBFS_SigChain45HzFilter == RBFS_SigChain45HzFilter_Available)
rbl_SigChain_FilterArray_t rbl_SigChain_FilVal45Hz = {{
    {
        {-1.672411f, 0.759073f},
        {0.209736f, -0.332810f, 0.209736f}
    },
    {   {-0.695131f, 0.0f},
        {0.152435f, 0.152435f, 0.0f}
    }
}};
#endif


#if (RBFS_SigChain20HzFilter == RBFS_SigChain20HzFilter_Available)

rbl_SigChain_FilterArray_t rbl_SigChain_FilVal20Hz = {{
	{
		{-1.859358f, 0.878329f},
		{0.158798f,-0.298626f, 0.158798f}
	},
	{
		{-0.855360f, 0.0f},
		{0.072320f, 0.072320f, 0.0f}
	}


}};
#endif


/* ***** END_SECTION local functions ***** */
