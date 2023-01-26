/****************************************************************************/
/* Copyright (c) 2021 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
*   @file       twi_ext_bat_sensor.c
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
#define EXT_BAT_SENSOR_LOG_ENABLE
#ifdef EXT_BAT_SENSOR_LOG_ENABLE
    #define EXT_BAT_SENSOR_LOG(...)								TWI_LOGGER("[EXT_BAT_SENSOR]: " __VA_ARGS__)
	#define EXT_BAT_SENSOR_LOG_COMBINED(STRING,INT)				TWI_LOGGER("[EXT_BAT_SENSOR]: %s,%d\n", STRING, INT)

	#define EXT_BAT_SENSOR_LOG_ERROR(...)						TWI_LOGGER_ERR("[EXT_BAT_SENSOR_ERR]: " __VA_ARGS__)
    #define EXT_BAT_SENSOR_LOG_ERROR_COMBINED(STRING, INT)		TWI_LOGGER_ERR("[EXT_BAT_SENSOR_ERR]: %s,%d\n", STRING, INT)
#else
    #define EXT_BAT_SENSOR_LOG(...)
	#define EXT_BAT_SENSOR_LOG_COMBINED(STRING,INT)

	#define EXT_BAT_SENSOR_LOG_ERROR(...)
    #define EXT_BAT_SENSOR_LOG_ERROR_COMBINED(STRING, INT)
#endif

#if defined (EXTERNAL_BATTERY_MEASUREMENT) || defined (EXTERNAL_IPILL_BATTERY_MEASUREMENT)  
#define BAT_ADC_VIN_CH                          3
#else
#define BAT_ADC_VIN_CH                          0
#endif
#define BAT_ADC_VREF_CH                         1
#if defined NRF51
#define BAT_ADC_CH_CONFIGS                      TWI_ADC_RES_10_BITS             |       \
                                                TWI_ADC_VIN_VCC_INPUT           |       \
                                                TWI_ADC_VIN_GAIN_ONE_THIRD      |       \
                                                TWI_ADC_VREF_INTERNAL_REF       |       \
                                                TWI_ADC_VREF_DIVIDER_THREE_THIRD
#elif defined NRF52
#ifdef EXTERNAL_BATTERY_MEASUREMENT
#define BAT_ADC_CH_CONFIGS                      TWI_ADC_RES_10_BITS             |       \
                                                TWI_ADC_VIN_EXTERNAL_INPUT      |       \
                                                TWI_ADC_VIN_GAIN_ONE_SIXTH      |       \
                                                TWI_ADC_VREF_INTERNAL_REF       |       \
                                                TWI_ADC_VREF_DIVIDER_THREE_THIRD
#elif EXTERNAL_IPILL_BATTERY_MEASUREMENT
#define BAT_ADC_CH_CONFIGS                      TWI_ADC_RES_10_BITS             |       \
                                                TWI_ADC_VIN_EXTERNAL_INPUT      |       \
                                                TWI_ADC_VIN_GAIN_ONE_SIXTH      |       \
                                                TWI_ADC_VREF_INTERNAL_REF       |       \
                                                TWI_ADC_VREF_DIVIDER_THREE_THIRD
#else
#define BAT_ADC_CH_CONFIGS                      TWI_ADC_RES_10_BITS             |       \
                                                TWI_ADC_VIN_VCC_INPUT           |       \
                                                TWI_ADC_VIN_GAIN_ONE_SIXTH      |       \
                                                TWI_ADC_VREF_INTERNAL_REF       |       \
                                                TWI_ADC_VREF_DIVIDER_THREE_THIRD
#endif
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
    twi_s32 s32_retval = TWI_SUCCESS;
#ifdef EXTERNAL_BATTERY_MEASUREMENT
    do
    {
        s32_retval = twi_gpio_init();
        TWI_ERROR_BREAK(s32_retval);
        s32_retval = twi_gpio_select(TWI_BAT_REF_EN_PORT, TWI_BAT_REF_EN_PIN);
        TWI_ERROR_BREAK(s32_retval);
        s32_retval = twi_gpio_set_configure(TWI_BAT_REF_EN_PORT, TWI_BAT_REF_EN_PIN, TWI_GPIO_DIR_OUT, TWI_PIN_FUNC_GPIO, TWI_INVALID_CHANNEL_NUM);
        TWI_ERROR_BREAK(s32_retval);
        s32_retval = twi_gpio_clear(TWI_BAT_REF_EN_PORT, TWI_BAT_REF_EN_PIN);
        TWI_ERROR_BREAK(s32_retval);
    } while (0);
#endif
    return s32_retval;
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
#ifdef EXTERNAL_BATTERY_MEASUREMENT
    s32_retval = twi_gpio_set(TWI_BAT_REF_EN_PORT,TWI_BAT_REF_EN_PIN);
#endif
    if (TWI_SUCCESS == s32_retval)
    {

        /*Check parameters are a valid parameters.*/
        if((NULL != pu32_real) && (NULL != pu32_frac))
        {
            twi_u32 u32_result = 0;
            
            /*The parameters are valid.*/
            s32_retval = twi_adc_start(BAT_ADC_VIN_CH, ADC_DONOT_USE_DIFF_CHANNEL,BAT_ADC_VREF_CH, BAT_ADC_CH_CONFIGS, &u32_result);
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
    }
#ifdef EXTERNAL_BATTERY_MEASUREMENT
     s32_retval = twi_gpio_clear(TWI_BAT_REF_EN_PORT,TWI_BAT_REF_EN_PIN);
#endif
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
    twi_s32 s32_retval = TWI_SUCCESS;
    twi_s8 s8_bat_perc = 0;
    static twi_s8 s8_prev_bat_perv = 100; /*Max Value*/
    /*in PILRO_003 the Battery Reading is divided by 2, so we need to get the actual value of battery voltage*/
    if ((pu8_battery_percenatge != NULL) && (pu8_battery_charge_state != NULL))
    {
#ifdef EXTERNAL_BATTERY_MEASUREMENT
        twi_u16 u16_battery_value_mv = u16_readings_in_mv*2;
        s32_retval = TWI_SUCCESS;
        /*Project does not support rechargable batteries*/
        *pu8_battery_charge_state = BATTERY_CHARGE_STATE_DISCHARGING;
        EXT_BAT_SENSOR_LOG("Battery voltage = %d mV \r\n",u16_battery_value_mv);
        /*Battery % calculations*/
        /*knowing that y=mx+b, so to get x = (y-b)/m and we will multiply (b,and m by 1000 as Y value (u16_battery_value_mv) in mV not V)  
        we can lineraize the discharging curve to 3 regions, REGION A 100%-91%,REGION B 90%-10%,REGION C 0%-9%*/
        /*ٌRegion A formula  m = 0.033, b=1.17 */
        /*ٌRegion B formula  m = 0.009, b=3.31 */
        /*ٌRegion C formula  m = 0.038, b=2.997 */
        if (u16_battery_value_mv>= 4160)
        {
            s8_bat_perc = (u16_battery_value_mv - 1170)/33;
        }
        else if (u16_battery_value_mv>= 3317)
        {
            s8_bat_perc = (u16_battery_value_mv - 3310)/9;
        }
        else
        {
            s8_bat_perc = (u16_battery_value_mv - 2997)/38;
        }
        if (s8_bat_perc > 100)
        {
            s8_bat_perc = 100;
        }
        if (s8_bat_perc <= 0)
        {
            s8_bat_perc = 1;
        }
#elif EXTERNAL_IPILL_BATTERY_MEASUREMENT
        twi_u16 u16_battery_value_mv = u16_readings_in_mv*3;
        *pu8_battery_charge_state = BATTERY_CHARGE_STATE_DISCHARGING;
        EXT_BAT_SENSOR_LOG("Battery voltage = %d mV \r\n",u16_battery_value_mv);
        /*Battery % calculations*/
        /*knowing that y=mx+b, so to get x = (y-b)/m and we will multiply (b,and m by 1000 as Y value (u16_battery_value_mv) in mV not V) */
        /* we can lineraize the discharging curve to 3 regions, REGION A 100%-98%,REGION B 98%-10%,REGION C 10%-0% */
        /*ٌ Region A formula  m = 0.452, b=35.876 */
        /*ٌ Region B formula  m = 0.016, b=7.317  */
        /*ٌ Region C formula  m = 0.200, b=5.050  */
        if (u16_battery_value_mv>= 8535)
        {
            s8_bat_perc = (u16_battery_value_mv + 35876)/452;
        }
        else if (u16_battery_value_mv>= 7000)
        {
            s8_bat_perc = (u16_battery_value_mv - 7317)/16;
        }
        else
        {
            s8_bat_perc = (u16_battery_value_mv - 5050)/200;
        }

        if (s8_bat_perc > 100)
        {
            s8_bat_perc = 100;
        }
        if (s8_bat_perc <= 0)
        {
            s8_bat_perc = 1;
        }
#else
    twi_u16 u16_battery_value_mv = u16_readings_in_mv;
	EXT_BAT_SENSOR_LOG("Battery voltage = %d mV \r\n",u16_battery_value_mv);
    *pu8_battery_charge_state = BATTERY_CHARGE_STATE_DISCHARGING;
    s8_bat_perc = (u16_battery_value_mv-1500)/(19);       /*Linearization for TAGPCC_001, So we follow (Reading-Minimum(1500)/(Max(3400)- Minimum(1500))) = 0.XY,then *100 =XV%*/
#endif
        if (s8_prev_bat_perv < s8_bat_perc )
        {
        	EXT_BAT_SENSOR_LOG("Battery voltage %d Exceeds the previous one = %d \r\n",s8_bat_perc,s8_prev_bat_perv);
            s8_bat_perc = s8_prev_bat_perv;
        }
        else
        {
            /*Do nothing*/
        }
        s8_prev_bat_perv = s8_bat_perc;
        *pu8_battery_percenatge = s8_bat_perc;
        EXT_BAT_SENSOR_LOG("Battery Percentage = %d %% \r\n",*pu8_battery_percenatge);
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }
    return s32_retval;
}
