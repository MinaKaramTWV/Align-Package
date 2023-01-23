/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
*   @file       twi_bat_sensor.c
*   @brief      This file contains TWI battery sensor HAL implementation.
*/

/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/

#include "twi_bat_sensor.h"
#include "twi_adc.h"
#include "platform_defines.h"
#include "platform_pins.h"

/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/

#define BAT_ADC_VIN_CH                          1
#define BAT_ADC_VREF_CH                         1
#if defined NRF51
#define BAT_ADC_CH_CONFIGS                      TWI_ADC_RES_10_BITS             |       \
                                                TWI_ADC_VIN_VCC_INPUT           |       \
                                                TWI_ADC_VIN_GAIN_ONE_THIRD      |       \
                                                TWI_ADC_VREF_INTERNAL_REF       |       \
                                                TWI_ADC_VREF_DIVIDER_THREE_THIRD
#elif defined NRF52
#define BAT_ADC_CH_CONFIGS                      TWI_ADC_RES_10_BITS             |       \
                                                TWI_ADC_VIN_VCC_INPUT           |       \
                                                TWI_ADC_VIN_GAIN_ONE_SIXTH      |       \
                                                TWI_ADC_VREF_INTERNAL_REF       |       \
                                                TWI_ADC_VREF_DIVIDER_THREE_THIRD
#else
#error Need to define either NRF51 or NRF52.
#endif
#define MUL36(VAR)                              (((VAR) << 5) + ((VAR) << 2))
#define MUL3600(VAR)                            (((VAR) << 11) + ((VAR) << 10) + ((VAR) << 9) + ((VAR) << 4))
/*real_part = u32_result * 12 * 3 / 10 / 1024.*/
#define GET_ADC_RESULT_REAL_PART(u32_result)    ((MUL36(u32_result) >> 10) / 10)
/*frac_part = (u32_result * 12 * 3 * 1000 / 10 / 1024) % 1000.*/
#define GET_ADC_RESULT_FRAC_PART(u32_result)    ((MUL3600(u32_result) >> 10) % 1000)

/*---------------------------------------------------------*/
/*- GLOBAL STATIC VARIABLES -------------------------------*/
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
/*- APIs IMPLEMENTATION -----------------------------------*/
/*---------------------------------------------------------*/
/*
*   @brief      This is a function that initialize the battery sensor.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_bat_sensor_init(void)
{
    /*Do Nothing*/
    return TWI_SUCCESS;
}
/*
*   @brief      This is a function that gets the battery voltage level. The battery level will be (*pu32_real + *pu32_frac / 100).
*   @param[out]  pu32_real  The real part of the battery level.
*   @param[out]  pu32_frac  The fraction part of the battery level.
*   @retval     ::TWI_SUCCESS, ::TWI_ERROR_INVALID_CONFIG,
*               ::TWI_ERROR_HW_TIMEOUT, ::TWI_ERROR_ALREADY_RESERVED,
*               ::TWI_ERROR_INVALID_ARGUMENTS.
*/
twi_s32 twi_bat_sensor_read(twi_u32 *pu32_real, twi_u32 *pu32_frac)
{
    twi_s32 s32_retval;
    
    s32_retval = TWI_SUCCESS;
    
    /*Check parameters are a valid parameters.*/
    if((NULL != pu32_real) && (NULL != pu32_frac))
    {
        twi_u32 u32_result = 0;
        
        /*The parameters are valid.*/
        s32_retval = twi_adc_start(BAT_ADC_VIN_CH, ADC_DONOT_USE_DIFF_CHANNEL, BAT_ADC_VREF_CH, BAT_ADC_CH_CONFIGS, &u32_result);
        if(TWI_SUCCESS == s32_retval)
        {
            /*We could get the battery level.*/
            
            /*Calculate the real and fraction parts of the battery level.*/
            *pu32_real = GET_ADC_RESULT_REAL_PART(u32_result);
            *pu32_frac = GET_ADC_RESULT_FRAC_PART(u32_result);
        }
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }
  
    return s32_retval;
}

/*
 *	@function	twi_s32 twi_bat_prcntg_calculate(twi_u16 u16_readings_in_mv, twi_u8* pu8_battery_percenatge,twi_u8* pu8_battery_charge_state)
 *	@brief      This API shall be used by battery Handler to get the percentage value of battery voltage
 *	@param[in] 	u16_readings_in_mv: the mV reading from HW battery Handler.
 *	@param[out] pu8_battery_percenatge: returns the battery percentage.
 *	@param[out] pu8_battery_charge_state: returns the battery charging state.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_bat_prcntg_calculate(twi_u16 u16_readings_in_mv, twi_u8* pu8_battery_percenatge,twi_u8* pu8_battery_charge_state)
{
    /*Not Supported*/
    return TWI_ERROR_NOT_SUPPORTED_FEATURE;
}
