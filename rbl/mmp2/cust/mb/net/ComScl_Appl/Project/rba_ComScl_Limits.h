/*
 ********************************************************************************************************************** 
 *
 * COPYRIGHT RESERVED, 2019 Robert Bosch GmbH. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 ********************************************************************************************************************** 
 */
/*<VersionHead>
 * This File is generated using BCT Tool (automatically filled in) as listed below.
 *
 * $Generator__: rba_ComScl / AR42.7.0.0	Module Package Version
 * $Editor_____: AEEE-Pro_2019.1.0 		Tool Version
 * $Model______: 1.0.0.0 					ECU Parameter Definition Version
 *
 </VersionHead>
 */
#ifndef RBA_COMSCL_LIMITS_H
#define RBA_COMSCL_LIMITS_H
#include "ComStack_Types.h"
/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
 */
#define RBA_COMSCL_UINT8_MAX (255)
#define RBA_COMSCL_UINT8_MIN (0)
#define RBA_COMSCL_UINT16_MAX (65535)
#define RBA_COMSCL_UINT16_MIN (0)
#define RBA_COMSCL_UINT32_MAX (4294967295uL)
#define RBA_COMSCL_UINT32_MIN (0)
#define RBA_COMSCL_SINT8_MAX (127)
#define RBA_COMSCL_SINT8_MIN (-128)
#define RBA_COMSCL_SINT16_MAX (32767)
#define RBA_COMSCL_SINT16_MIN (-32768)
#define RBA_COMSCL_SINT32_MAX (2147483647)
#define RBA_COMSCL_SINT32_MIN (-(RBA_COMSCL_SINT32_MAX)-1L)
#define RBA_COMSCL_FLOAT32_MAX (3.4028234663852886E38)
#define RBA_COMSCL_FLOAT32_MIN (-3.4028234663852886E38)
/*
 **********************************************************************************************************************
 * Prototypes
 **********************************************************************************************************************
 */
LOCAL_INLINE sint16 rba_ComScl_LimitMax_u16s16_s16(uint16 value, sint16 max_value);
LOCAL_INLINE uint8 rba_ComScl_LimitMax_u8u8_u8(uint8 value, uint8 max_value);
LOCAL_INLINE uint16 rba_ComScl_LimitMin_s16u16_u16(sint16 value, uint16 min_value);
LOCAL_INLINE sint16 rba_ComScl_Limit_s32s16s16_s16(sint32 value, sint16 min_value, sint16 max_value);
LOCAL_INLINE uint16 rba_ComScl_Limit_s32u16u16_u16(sint32 value, uint16 min_value, uint16 max_value);
LOCAL_INLINE uint16 rba_ComScl_Limit_u32u16u16_u16(uint32 value, uint16 min_value, uint16 max_value);
LOCAL_INLINE uint8 rba_ComScl_Limit_u32u8u8_u8(uint32 value, uint8 min_value, uint8 max_value);
/*
 **********************************************************************************************************************
 * Implementations
 **********************************************************************************************************************
 */
/**
 **********************************************************************************************************************
 * rba_ComScl_LimitMax_u16s16_s16
 *
 * \brief Limits a uint16 input value to a sint16 output upper limit
 *
 * If input less than or equal to max_value. Function returns input value.
 * If input greater than or equal to max_value. Function returns max_value.
 * If input greater than or equal to max sint16. Function returns max_value.
 *
 * \param   uint16 value      Input value
 * \param   sint16 max_value  Upper limit
 * \return  sint16           
 **********************************************************************************************************************
 */
LOCAL_INLINE sint16 rba_ComScl_LimitMax_u16s16_s16(uint16 value, sint16 max_value)
{
    return (value >= (uint16) RBA_COMSCL_SINT16_MAX) ? (max_value) : (((sint16) value >= max_value) ? (max_value) : ((sint16) value));
}
/**
 **********************************************************************************************************************
 * rba_ComScl_LimitMax_u8u8_u8
 *
 * \brief Limits a uint8 input value to a uint8 output upper limit
 *
 * If input less than or equal to max_value. Function returns input value.
 * If input greater than or equal to max_value. Function returns max_value.
 *
 * \param   uint8 value      Input value
 * \param   uint8 max_value  Upper limit
 * \return  uint8           
 **********************************************************************************************************************
 */
LOCAL_INLINE uint8 rba_ComScl_LimitMax_u8u8_u8(uint8 value, uint8 max_value)
{
    return (value >= max_value) ? (max_value) : (value);
}
/**
 **********************************************************************************************************************
 * rba_ComScl_LimitMin_s16u16_u16
 *
 * \brief Limits a sint16 input value to a uint16 output lower limit
 *
 * If input greater than or equal to min_value. Function returns input value.
 * If input less than or equal to min_value. Function returns min_value.
 * If input less than or equal to min uint16. Function returns min_value.
 *
 * \param   sint16 value      Input value
 * \param   uint16 min_value  Lower limit
 * \return  uint16           
 **********************************************************************************************************************
 */
LOCAL_INLINE uint16 rba_ComScl_LimitMin_s16u16_u16(sint16 value, uint16 min_value)
{
    return (value <= (sint16) RBA_COMSCL_UINT16_MIN) ? (min_value) : (((uint16) value <= min_value) ? (min_value) : ((uint16) value));
}
/**
 **********************************************************************************************************************
 * rba_ComScl_Limit_s32s16s16_s16
 *
 * \brief Limits a sint32 input value to a sint16 output lower and upper limit
 *
 * Case 1: If min_value less than or equal to max_value
 * Function returns input value if it is between lower an upper limit. Otherwise a limited value will be returned.
 * Case 2: If min_value greater than max_value
 * Default return value is Input value
 *
 * \param   sint32 value      Input value
 * \param   sint16 max_value  Upper limit
 * \return  sint16     Return Input value if it is between min_value and max_value. If Input value is greater 
 * \return                than upper limit max_value will be returned. If Input value is less than lower limit 
 * \return                min_value will be returned. If min_value greater than max_value 
 * \return                then the default return value is Input value
 **********************************************************************************************************************
 */
LOCAL_INLINE sint16 rba_ComScl_Limit_s32s16s16_s16(sint32 value, sint16 min_value, sint16 max_value)
{
    return (value <= (sint32) RBA_COMSCL_SINT16_MIN) ? (min_value) :
            ((value >= (sint32) RBA_COMSCL_SINT16_MAX) ? (max_value) :
                    (((min_value > max_value) ? ((sint16) value) : ((value <= min_value) ? (min_value) : ((value >= max_value) ? (max_value) : ((sint16) value))))));
}
/**
 **********************************************************************************************************************
 * rba_ComScl_Limit_s32u16u16_u16
 *
 * \brief Limits a sint32 input value to a uint16 output lower and upper limit
 *
 * Case 1: If min_value less than or equal to max_value
 * Function returns input value if it is between lower an upper limit. Otherwise a limited value will be returned.
 * Case 2: If min_value greater than max_value
 * Default return value is Input value
 *
 * \param   sint32 value      Input value
 * \param   uint16 max_value  Upper limit
 * \return  uint16     Return Input value if it is between min_value and max_value. If Input value is greater 
 * \return                than upper limit max_value will be returned. If Input value is less than lower limit 
 * \return                min_value will be returned. If min_value greater than max_value 
 * \return                then the default return value is Input value
 **********************************************************************************************************************
 */
LOCAL_INLINE uint16 rba_ComScl_Limit_s32u16u16_u16(sint32 value, uint16 min_value, uint16 max_value)
{
    return (value <= (sint32) RBA_COMSCL_UINT16_MIN) ? (min_value) :
            ((value >= (sint32) RBA_COMSCL_UINT16_MAX) ? (max_value) :
                    (((min_value > max_value) ? ((uint16) value) : (((uint16) value <= min_value) ? (min_value) : (((uint16) value >= max_value) ? (max_value) : ((uint16) value))))));
}
/**
 **********************************************************************************************************************
 * rba_ComScl_Limit_u32u16u16_u16
 *
 * \brief Limits a uint32 input value to a uint16 output lower and upper limit
 *
 * Case 1: If min_value less than or equal to max_value
 * Function returns input value if it is between lower an upper limit. Otherwise a limited value will be returned.
 * Case 2: If min_value greater than max_value
 * Default return value is Input value
 *
 * \param   uint32 value      Input value
 * \param   uint16 max_value  Upper limit
 * \return  uint16     Return Input value if it is between min_value and max_value. If Input value is greater 
 * \return                than upper limit max_value will be returned. If Input value is less than lower limit 
 * \return                min_value will be returned. If min_value greater than max_value 
 * \return                then the default return value is Input value
 **********************************************************************************************************************
 */
LOCAL_INLINE uint16 rba_ComScl_Limit_u32u16u16_u16(uint32 value, uint16 min_value, uint16 max_value)
{
    return (value >= (uint32) RBA_COMSCL_UINT16_MAX) ? (max_value) :
            (((min_value > max_value) ? ((uint16) value) : ((value <= min_value) ? (min_value) : ((value >= max_value) ? (max_value) : ((uint16) value)))));
}
/**
 **********************************************************************************************************************
 * rba_ComScl_Limit_u32u8u8_u8
 *
 * \brief Limits a uint32 input value to a uint8 output lower and upper limit
 *
 * Case 1: If min_value less than or equal to max_value
 * Function returns input value if it is between lower an upper limit. Otherwise a limited value will be returned.
 * Case 2: If min_value greater than max_value
 * Default return value is Input value
 *
 * \param   uint32 value      Input value
 * \param   uint8 max_value  Upper limit
 * \return  uint8     Return Input value if it is between min_value and max_value. If Input value is greater 
 * \return                than upper limit max_value will be returned. If Input value is less than lower limit 
 * \return                min_value will be returned. If min_value greater than max_value 
 * \return                then the default return value is Input value
 **********************************************************************************************************************
 */
LOCAL_INLINE uint8 rba_ComScl_Limit_u32u8u8_u8(uint32 value, uint8 min_value, uint8 max_value)
{
    return (value >= (uint32) RBA_COMSCL_UINT8_MAX) ? (max_value) :
            (((min_value > max_value) ? ((uint8) value) : ((value <= min_value) ? (min_value) : ((value >= max_value) ? (max_value) : ((uint8) value)))));
}
#endif /* RBA_COMSCL_LIMITS_H */
