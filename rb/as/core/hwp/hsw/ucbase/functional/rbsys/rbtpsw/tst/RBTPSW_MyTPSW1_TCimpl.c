/**
 * @ingroup 'SW-group'
 * @{
 *
 * \file
 * \brief 'Short description of this module, up to 80 characters
 *
 * 'Detailed description of this module, several lines/paragraphes'
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* used interfaces */


/* realized interfaces */
#include "RBTPSW_MyTPSWCapsule.h"
#include "RBTPSW_MyTPSW1.h"
#include "RBTPSW_MyTPSW2.h"
#include "RBTPSW_MyTPSW3.h"

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_OFF,
                          RBFS_TPSWTestsuite_ON);


#if (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON)

uint32 TPSW1_ErrorCounter_UL = 0;

void TPSW1_TPSW3_WaitingFunction_Switch2Trust_GC(void)
{
    /* Testcase description:  */
    /* Desired Reaction:      */
    TPSW3_WaitingFunction_Switch2Trust_t mytime;

    mytime.untrustedTimeBefore = 50u;
    mytime.trustedTime = 50u;
    mytime.untrustedTimeAfter = 50u;

    (void)RBTPSW_CALL(TPSW3_WaitingFunction_Switch2Trust(&mytime));

    if(TPSW3_WaitingFunction_Switch2Trust_State != 5u) {TrustedData = 0;}
}

void TPSW1_TPSW3_WaitingFunction_Switch2Trust_BC1(void)
{
    /* Testcase description:  */
    /* Desired Reaction:      */
    TPSW3_WaitingFunction_Switch2Trust_t mytime;

    mytime.untrustedTimeBefore = 1000u;
    mytime.trustedTime = 50u;
    mytime.untrustedTimeAfter = 50u;

    (void)RBTPSW_CALL(TPSW3_WaitingFunction_Switch2Trust(&mytime));

    if(TPSW3_WaitingFunction_Switch2Trust_State != 0) {TrustedData = 0;}
}


void TPSW1_TPSW3_WaitingFunction_Switch2Trust_BC2(void)
{
    /* Testcase description:  */
    /* Desired Reaction:      */
    TPSW3_WaitingFunction_Switch2Trust_t mytime;

    mytime.untrustedTimeBefore = 50u;
    mytime.trustedTime = 1000u;
    mytime.untrustedTimeAfter = 50u;

    (void)RBTPSW_CALL(TPSW3_WaitingFunction_Switch2Trust(&mytime));

    if(TPSW3_WaitingFunction_Switch2Trust_State != 3u) {TrustedData = 0;}
}


void TPSW1_TPSW3_WaitingFunction_Switch2Trust_BC3(void)
{
    /* Testcase description:  */
    /* Desired Reaction:      */
    TPSW3_WaitingFunction_Switch2Trust_t mytime;

    mytime.untrustedTimeBefore = 50u;
    mytime.trustedTime = 50u;
    mytime.untrustedTimeAfter = 1000u;

    (void)RBTPSW_CALL(TPSW3_WaitingFunction_Switch2Trust(&mytime));

    if(TPSW3_WaitingFunction_Switch2Trust_State != 4u) {TrustedData = 0;}
}

void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_GoodCase_Tp(void)
{
    /* Testcase description:  */
    /* Desired Reaction:      */
    TPSW3_WaitingFunction_Switch2Trust_t mytime;

    mytime.untrustedTimeBefore = 50u;
    mytime.trustedTime = 50u;
    mytime.untrustedTimeAfter = 50u;

    (void)RBTPSW_CALL(TPSW3_TPSW2_WaitingFunction_UTTP(&mytime));

    if(TPSW3_WaitingFunction_UTTP_State != 5u) {TrustedData = 0;}
}

void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase1_Tp(void)
{
    /* Testcase description:  */
    /* Desired Reaction:      */
    TPSW3_WaitingFunction_Switch2Trust_t mytime;

    mytime.untrustedTimeBefore = 1000u;
    mytime.trustedTime = 50u;
    mytime.untrustedTimeAfter = 50u;

    (void)RBTPSW_CALL(TPSW3_TPSW2_WaitingFunction_UTTP(&mytime));

    if(TPSW3_WaitingFunction_UTTP_State != 0) {TrustedData = 0;}
}


void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase2_Tp(void)
{
    /* Testcase description:  */
    /* Desired Reaction:      */
    TPSW3_WaitingFunction_Switch2Trust_t mytime;

    mytime.untrustedTimeBefore = 150u;
    mytime.trustedTime = 1000u;
    mytime.untrustedTimeAfter = 50u;

    (void)RBTPSW_CALL(TPSW3_TPSW2_WaitingFunction_UTTP(&mytime));

    if(TPSW3_WaitingFunction_UTTP_State != 2u) {TrustedData = 0;}
}


void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase3_Tp(void)
{
    /* Testcase description:  */
    /* Desired Reaction:      */
    TPSW3_WaitingFunction_Switch2Trust_t mytime;

    mytime.untrustedTimeBefore = 50u;
    mytime.trustedTime = 50u;
    mytime.untrustedTimeAfter = 1000u;

    (void)RBTPSW_CALL(TPSW3_TPSW2_WaitingFunction_UTTP(&mytime));

    if(TPSW3_WaitingFunction_UTTP_State != 4u) {TrustedData = 0;}
}


void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_GoodCase_NoTp(void)
{
    {
        TPSW3_WaitingFunction_Switch2Trust_t mytime;

        mytime.untrustedTimeBefore = 50u;
        mytime.trustedTime = 50u;
        mytime.untrustedTimeAfter = 50u;

        (void)RBTPSW_CALL(TPSW3_TPSW2_WaitingFunction_UTTP_NoTp(&mytime));

        if(TPSW3_WaitingFunction_UTTP_State != 5u) {TrustedData = 0;}
    }
}


void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase1_NoTp(void)
{
    {
        TPSW3_WaitingFunction_Switch2Trust_t mytime;

        mytime.untrustedTimeBefore = 1000u;
        mytime.trustedTime = 50u;
        mytime.untrustedTimeAfter = 50u;

        (void)RBTPSW_CALL(TPSW3_TPSW2_WaitingFunction_UTTP_NoTp(&mytime));

        if(TPSW3_WaitingFunction_UTTP_State != 0) {TrustedData = 0;}
    }
}

void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase2_NoTp(void)
{
    {
        TPSW3_WaitingFunction_Switch2Trust_t mytime;

        mytime.untrustedTimeBefore = 50u;
        mytime.trustedTime = 1000u;
        mytime.untrustedTimeAfter = 50u;

        (void)RBTPSW_CALL(TPSW3_TPSW2_WaitingFunction_UTTP_NoTp(&mytime));

        if(TPSW3_WaitingFunction_UTTP_State != 3u) {TrustedData = 0;}
    }
}

void TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase3_NoTp(void)
{
    {
        TPSW3_WaitingFunction_Switch2Trust_t mytime;

        mytime.untrustedTimeBefore = 50u;
        mytime.trustedTime = 50u;
        mytime.untrustedTimeAfter = 1000u;

        (void)RBTPSW_CALL(TPSW3_TPSW2_WaitingFunction_UTTP_NoTp(&mytime));

        if(TPSW3_WaitingFunction_UTTP_State != 4u) {TrustedData = 0;}
    }
}

void TPSW1_TPSW3_UTTP_GoodCase(void)
{
    {
        TPSW3_WaitingFunction_Switch2Trust_t mytime;

        mytime.untrustedTimeBefore = 50u;
        mytime.trustedTime = 50u;
        mytime.untrustedTimeAfter = 50u;

        (void)RBTPSW_CALL(TPSW3_WaitingFunction_UTTP(&mytime));

        if(TPSW3_WaitingFunction_UTTP_State != 5u) {TrustedData = 0;}
    }
}

void TPSW1_TPSW3_UTTP_BadCase1(void)
{
    {
        TPSW3_WaitingFunction_Switch2Trust_t mytime;

        mytime.untrustedTimeBefore = 1000u;
        mytime.trustedTime = 50u;
        mytime.untrustedTimeAfter = 50u;

        (void)RBTPSW_CALL(TPSW3_WaitingFunction_UTTP(&mytime));

        if(TPSW3_WaitingFunction_UTTP_State != 0) {TrustedData = 0;}
    }
}

void TPSW1_TPSW3_UTTP_BadCase2(void)
{
    {
        TPSW3_WaitingFunction_Switch2Trust_t mytime;

        mytime.untrustedTimeBefore = 50u;
        mytime.trustedTime = 1000u;
        mytime.untrustedTimeAfter = 50u;

        (void)RBTPSW_CALL(TPSW3_WaitingFunction_UTTP(&mytime));

        if(TPSW3_WaitingFunction_UTTP_State != 2u) {TrustedData = 0;}
    }
}

void TPSW1_TPSW3_UTTP_BadCase3(void)
{
    {
        TPSW3_WaitingFunction_Switch2Trust_t mytime;

        mytime.untrustedTimeBefore = 50u;
        mytime.trustedTime = 50u;
        mytime.untrustedTimeAfter = 1000u;

        (void)RBTPSW_CALL(TPSW3_WaitingFunction_UTTP(&mytime));

        if(TPSW3_WaitingFunction_UTTP_State != 4u) {TrustedData = 0;}
    }
}

void TPSW1_TestGoodCases(void)
{
    uint32 result0, result1, result2, result3, result4, result5, result6, result7, result8, result9, result9u8;

    /* Testcase description:  test every function call good cases (T-UT, 0-6 param, without return value) */
    /* Desired Reaction: no reaction. TPSW1_ErrorCounter_UL must always be equal to 0                     */
    {
        RBTPSW_CALL(TPSW2_1Param_V (1u));
        RBTPSW_CALL(TPSW2_2Param_V (1u, 2u));
        RBTPSW_CALL(TPSW2_3Param_V (1u, 2u, 3u));
        RBTPSW_CALL(TPSW2_4Param_V (1u, 2u, 3u, 4u));
        RBTPSW_CALL(TPSW2_5Param_V (1u, 2u, 3u, 4u, 5u));
        RBTPSW_CALL(TPSW2_6Param_V (1u, 2u, 3u, 4u, 5u, 6u));
        RBTPSW_CALL(TPSW2_7Param_V (1u, 2u, 3u, 4u, 5u, 6u, 7u));
        RBTPSW_CALL(TPSW2_8Param_V (1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u));
        RBTPSW_CALL(TPSW2_9Param_V (1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u));
        RBTPSW_CALL(TPSW2_9Param_U8_V (1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u));
    }

    /* Testcase description:  test every function call good cases (T-UT, 0-6 param, with return value) */
    /* Desired Reaction: no reaction. TPSW1_ErrorCounter_UL must always be equal to 0                  */
    {
        mytest_t structure;
        structure.a = 10u;
        structure.b = 20;
        structure = RBTPSW_CALL(TPSW2_struct_ST(structure));
        if  (
              (structure.a != 11u)
            ||(structure.b != 21)
          )
        {
            TPSW1_ErrorCounter_UL++;
        }


        result0 = RBTPSW_CALL(TPSW2_0Param_UL());
        result1 = RBTPSW_CALL(TPSW2_1Param_UL(1u));
        result2 = RBTPSW_CALL(TPSW2_2Param_UL(1u, 2u));
        result3 = RBTPSW_CALL(TPSW2_3Param_UL(1u, 2u, 3u));
        result4 = RBTPSW_CALL(TPSW2_4Param_UL(1u, 2u, 3u, 4u));
        result5 = RBTPSW_CALL(TPSW2_5Param_UL(1u, 2u, 3u, 4u, 5u));
        result6 = RBTPSW_CALL(TPSW2_6Param_UL(1u, 2u, 3u, 4u, 5u, 6u));
        result7 = RBTPSW_CALL(TPSW2_7Param_UL(1u, 2u, 3u, 4u, 5u, 6u, 7u));
        result8 = RBTPSW_CALL(TPSW2_8Param_UL(1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u));
        result9 = RBTPSW_CALL(TPSW2_9Param_UL(1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u));
        result9u8 = RBTPSW_CALL(TPSW2_9Param_U8(1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u));
        /* test if all return values are ok */
        if  (
                  (result0 != 0xFFFFFFFFu)
                ||(result1 != 1u)
                ||(result2 != 2u)
                ||(result3 != 3u)
                ||(result4 != 4u)
                ||(result5 != 5u)
                ||(result6 != 6u)
                ||(result7 != 7u)
                ||(result8 != 8u)
                ||(result9 != 9u)
                ||(result9u8 != 9u)
            )
        {
            TPSW1_ErrorCounter_UL++;
        }
    }

    /* Testcase description:  test every function call good cases (UT-T, 0-6 param, with and without return value) */
    /* Desired Reaction: no reaction. TPSW1_ErrorCounter_UL must always be equal to 0                              */
    {
        RBTPSW_CALL(TRUSTED_1Param_V (1u));
        RBTPSW_CALL(TRUSTED_2Param_V (1u, 2u));
        RBTPSW_CALL(TRUSTED_3Param_V (1u, 2u, 3u));
        RBTPSW_CALL(TRUSTED_4Param_V (1u, 2u, 3u, 4u));
        RBTPSW_CALL(TRUSTED_5Param_V (1u, 2u, 3u, 4u, 5u));
        RBTPSW_CALL(TRUSTED_6Param_V (1u, 2u, 3u, 4u, 5u, 6u));
        RBTPSW_CALL(TRUSTED_7Param_V (1u, 2u, 3u, 4u, 5u, 6u, 7u));
        RBTPSW_CALL(TRUSTED_8Param_V (1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u));
        RBTPSW_CALL(TRUSTED_9Param_V (1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u));
        RBTPSW_CALL(TRUSTED_9Param_U8_V (1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u));
        result0 = RBTPSW_CALL(TRUSTED_0Param_UL());
        result1 = RBTPSW_CALL(TRUSTED_1Param_UL(1u));
        result2 = RBTPSW_CALL(TRUSTED_2Param_UL(1u, 2u));
        result3 = RBTPSW_CALL(TRUSTED_3Param_UL(1u, 2u, 3u));
        result4 = RBTPSW_CALL(TRUSTED_4Param_UL(1u, 2u, 3u, 4u));
        result5 = RBTPSW_CALL(TRUSTED_5Param_UL(1u, 2u, 3u, 4u, 5u));
        result6 = RBTPSW_CALL(TRUSTED_6Param_UL(1u, 2u, 3u, 4u, 5u, 6u));
        result7 = RBTPSW_CALL(TRUSTED_7Param_UL(1u, 2u, 3u, 4u, 5u, 6u, 7u));
        result8 = RBTPSW_CALL(TRUSTED_8Param_UL(1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u));
        result9 = RBTPSW_CALL(TRUSTED_9Param_UL(1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u));
        result9u8 = RBTPSW_CALL(TRUSTED_9Param_U8(1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u));
        /* test if all return values are ok */
        if  (
                  (result0 != 0xFFFFFFFFu)
                ||(result1 != 1u)
                ||(result2 != 2u)
                ||(result3 != 3u)
                ||(result4 != 4u)
                ||(result5 != 5u)
                ||(result6 != 6u)
                ||(result7 != 7u)
                ||(result8 != 8u)
                ||(result9 != 9u)
                ||(result9u8 != 9u)
            )
        {
            TPSW1_ErrorCounter_UL++;
        }
    }

    {
      /*******************************************************************/
      /* Test of CPYPTR Helper                                           */
      /*******************************************************************/
      {
        uint8_t p_in = 1u, p_out = 0, p_inout = 10u;

        (void)RBTPSW_CALL(TPSW2_CPYPTR_UL(&p_in, &p_out, &p_inout));

        if (  (p_out   != 50u)
            ||(p_inout != 11u))
        {
          TPSW1_ErrorCounter_UL++;
        }
      }
    }


    /* Testcase description:  test every manipulators                                    */
    /* Desired Reaction: no reaction. TPSW1_ErrorCounter_UL must always be equal to 0    */
    {
        uint32 i;
        /*******************************************************************/
        /* Test of CPYARRAY_BYLENGTH Helper                                */
        /*******************************************************************/
        {
            uint32 length_in = 8u, length_out = 40u, length_inout = 6u;
            mytest_t mytest1_array_in[8];
            mytest_t mytest1_array_out[40];
            mytest_t mytest1_array_inout[10];

            /* array init */
            mytest1_array_in[0].a = 1; mytest1_array_in[0].b = -1;
            mytest1_array_in[1].a = 2; mytest1_array_in[1].b = -2;
            mytest1_array_in[2].a = 3; mytest1_array_in[2].b = -3;
            mytest1_array_in[3].a = 4; mytest1_array_in[3].b = -4;
            mytest1_array_in[4].a = 5; mytest1_array_in[4].b = -5;
            mytest1_array_in[5].a = 6; mytest1_array_in[5].b = -6;
            mytest1_array_in[6].a = 7; mytest1_array_in[6].b = -7;
            mytest1_array_in[7].a = 8; mytest1_array_in[7].b = -8;

            mytest1_array_inout[0].a = 1; mytest1_array_inout[0].b = -1;
            mytest1_array_inout[1].a = 2; mytest1_array_inout[1].b = -2;
            mytest1_array_inout[2].a = 3; mytest1_array_inout[2].b = -3;
            mytest1_array_inout[3].a = 4; mytest1_array_inout[3].b = -4;
            mytest1_array_inout[4].a = 5; mytest1_array_inout[4].b = -5;
            mytest1_array_inout[5].a = 6; mytest1_array_inout[5].b = -6;
            mytest1_array_inout[6].a = 7; mytest1_array_inout[6].b = -7;
            mytest1_array_inout[7].a = 8; mytest1_array_inout[7].b = -8;

            (void)RBTPSW_CALL(TPSW2_CPYARRAY_BYLENGTH_UL(length_in, mytest1_array_in, length_out, mytest1_array_out, length_inout, mytest1_array_inout));

            /* check out array */
            for (i=0;i<length_out;i++)
            {
              if((mytest1_array_out[i].a != i) || (mytest1_array_out[i].b != -((int32_t)i)))
              {
                TPSW1_ErrorCounter_UL++;
              }
            }

            /* check inout array */
            for (i=0;i<length_inout;i++)
            {
              if((mytest1_array_inout[i].a != (1+(i+1))) || (mytest1_array_inout[i].b != (int32_t)(1-((int32_t)i+1))))
              {
                TPSW1_ErrorCounter_UL++;
              }
            }
        }


        /*******************************************************************/
        /* Test of CPYARRAY_FIRSTELEM Helper                               */
        /*******************************************************************/
        {
            /* array init */
            uint32 uint32_array_in[50] = {10u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u, 16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u, 24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u, 32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u, 40u, 41u, 42u, 43u, 44u, 45u, 46u, 47u, 48u, 49u};
            uint32 uint32_array_out[50];
            uint32 uint32_array_inout[50] = {12u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u, 16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u, 24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u, 32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u, 40u, 41u, 42u, 43u, 44u, 45u, 46u, 47u, 48u, 49u};

            (void)RBTPSW_CALL(TPSW2_CPYARRAY_FIRSTELEM_UL(uint32_array_in, uint32_array_out, uint32_array_inout));

            /* check out array */
            for(i=1u;i<=uint32_array_out[0];i++)
            {
              if (uint32_array_out[i] != ((uint32_array_out[0]+1)-i))

              {
                TPSW1_ErrorCounter_UL++;
              }

            }

            if (uint32_array_out[0] != 48u)
            {
                TPSW1_ErrorCounter_UL++;
            }

            /* check inout array */
            for(i=1u;i<=uint32_array_inout[0];i++)
            {
              if (uint32_array_inout[i] != (i+1u))
              {
                TPSW1_ErrorCounter_UL++;
              }
            }
        }


        /*******************************************************************/
        /* Test of CPYARRAY_0TERM Helper                                   */
        /*******************************************************************/
        {
            /* array init */
            uint8_t uint8_array_in[50] = {1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u, 16u, 17u, 18u, 0u, 18u, 19u, 20u, 21u, 22u, 23u, 24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u, 32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u, 40u, 41u, 42u, 43u, 44u, 45u, 46u, 47u, 48u};
            uint8_t uint8_array_out[50];
            uint8_t uint8_array_inout[50] = {1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u, 16u, 17u, 18u, 19u, 0u, 21u, 20u, 21u, 22u, 23u, 24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u, 32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u, 40u, 41u, 42u, 43u, 44u, 45u, 46u, 47u, 48u};

            (void)RBTPSW_CALL(TPSW2_CPYARRAY_0TERM_UL(uint8_array_in, uint8_array_out, uint8_array_inout));

            /* check out array */
            i = 0;
            while (uint8_array_out[i] != 0)
            {
              if ((uint8_array_out[i] != (i+1u)))
              {
                TPSW1_ErrorCounter_UL++;
              }
              i++;
            }
            if (i != 40)
            {
              TPSW1_ErrorCounter_UL++;
            }

            /* check inout array */
            i = 0;
            while (uint8_array_inout[i] != 0)
            {
              if ((uint8_array_inout[i] != (i+2u)))
              {
                TPSW1_ErrorCounter_UL++;
              }
              i++;
            }
            if (i != (19u + 1u))
            {
              TPSW1_ErrorCounter_UL++;
            }
        }

        /*******************************************************************/
        /* CPY PTR and CPY ARRAY                                           */
        /*******************************************************************/
        {
            uint32 Length = 100u;
            uint32 Array[10];

            RBTPSW_CALL(TPSW2_GetPower2(&Length, Array));

            if(Length != 10u)
            {
                TPSW1_ErrorCounter_UL++;
            }

            for (i=1u;i<Length;i++)
            {
                if(Array[i] != (Array[i-1]*2u))
                {
                    TPSW1_ErrorCounter_UL++;
                }
            }
        }
    }
}

#endif

/** @} */
/* End ingroup 'SW-group' */
