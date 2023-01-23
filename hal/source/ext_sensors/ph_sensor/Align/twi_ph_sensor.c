/****************************************************************************/
/* Copyright (c) 2022 Thirdwayv, Inc. All Rights Reserved.                  */
/****************************************************************************/

/**
 *	@file					twi_ph_sensor.c
 *
 *	@brief					This file includes implementation of Align pH Sensor
 */

/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/
#include "twi_adc.h"
#include "platform_defines.h"
#include "twi_ph_sensor.h"
/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/

#ifdef  PH_SENSE_LOG_ENABLE
	#include"twi_debug.h"
	#define	PH_SENSE_LOG(...)								TWI_LOGGER("[PH_SENSE]: "__VA_ARGS__)
	#define	PH_SENSOR_LOG_COMBINED(STRING,INT)				TWI_LOGGER("[PH_SENSOR]: %s,%d\n", STRING, INT)

	#define PH_SENSE_LOG_ERR(...)							TWI_LOGGER_ERR("[PH_SENSE_ERR]: "__VA_ARGS__)
	#define PH_SENSOR_LOG_ERROR_COMBINED(STRING, INT)		TWI_LOGGER_ERR("[PH_SENSOR_ERR]: %s,%d\n", STRING, INT)

	#define PH_SENSE_LOG_SUCCESS(...)						TWI_LOGGER_SUCCESS("[PH_SENSOR_SUCC]: "__VA_ARGS__)
	#define PH_SENSOR_LOG_SUCCESS_COMBINED(STRING, INT)		TWI_LOGGER_SUCCESS("[PH_SENSOR_SUCC]: %s,%d\n", STRING, INT)
#else
	#define	PH_SENSE_LOG(...)
	#define	PH_SENSOR_LOG_COMBINED(STRING,INT)

	#define PH_SENSE_LOG_ERR(...)
	#define PH_SENSOR_LOG_ERROR_COMBINED(STRING, INT)

	#define PH_SENSE_LOG_SUCCESS(...)						
	#define PH_SENSOR_LOG_SUCCESS_COMBINED(STRING, INT)		
#endif

#if defined NRF52
#define PH_PIN_ADC_CH_CONFIGS                   TWI_ADC_RES_8_BITS             |       \
                                                TWI_ADC_VIN_EXTERNAL_INPUT      |       \
                                                TWI_ADC_VIN_GAIN_ONE_SIXTH      |       \
                                                TWI_ADC_VREF_INTERNAL_REF       |       \
                                                TWI_ADC_VREF_DIVIDER_THREE_THIRD

#define PH_REF_PIN_ADC_CH_CONFIGS               TWI_ADC_RES_8_BITS             |       \
                                                TWI_ADC_VIN_EXTERNAL_INPUT      |       \
                                                TWI_ADC_VIN_GAIN_ONE_SIXTH      |       \
                                                TWI_ADC_VREF_INTERNAL_REF       |       \
                                                TWI_ADC_VREF_DIVIDER_THREE_THIRD
#else
#error Need to define NRF52.
#endif

#define MAX_ADC_PH_VALUE						(600) /*1000mV*/
#define MIN_ADC_PH_VALUE						(-600) /*1000mV*/

/*---------------------------------------------------------*/
/*- Global Variables --------------------------------------*/
/*---------------------------------------------------------*/
twi_bool gb_ph_sensor_is_init = TWI_FALSE;

/*---------------------------------------------------------*/
/*- API's Implementation ----------------------------------*/
/*---------------------------------------------------------*/

/*
 *	@function	twi_s32 twi_ph_sensor_init(void)
 *  @brief		Function used for initialization of pH sensor.
 *  @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */
twi_s32 twi_ph_sensor_init(void)
{
	twi_s32 s32_retval = TWI_SUCCESS;

	gb_ph_sensor_is_init =	TWI_TRUE;

	return s32_retval;
}

/*
 *	@function	twi_s32 twi_ph_sensor_deinit(void)
 *  @brief		Function used for de-initialization of pH Sensor.
 *  @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */
twi_s32 twi_ph_sensor_deinit(void)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;
	
	gb_ph_sensor_is_init =	TWI_FALSE;

	return s32_retval;
}

/*
 *	@function	twi_s32 twi_ph_sensor_read(twi_u8 *pu8_ph_val)
 *  @brief		Function used for reading current pH sensor".
 *  @param[out] pu8_ph_val   The pH value read from the pH sensor.
 *  @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */
twi_s32 twi_ph_sensor_read(twi_u8 *pu8_ph_val)
{
	twi_s32 s32_retval = TWI_SUCCESS;
	
	twi_u32 u32_pin_result = 0;
	twi_u32 u32_ref_pin_result = 0;

	twi_s32 s32_result_mv = 0;
	twi_u32 u32_pin_result_mv = 0;
	twi_u32 u32_ref_pin_result_mv = 0;

	if(NULL != pu8_ph_val)
	{
		if(TWI_TRUE == gb_ph_sensor_is_init)
		{
			/* Start sampling form pin */
			s32_retval = twi_adc_start(PH_PIN_ADC_VIN_CH, ADC_DONOT_USE_DIFF_CHANNEL, PH_ADC_VREF_CH, PH_PIN_ADC_CH_CONFIGS, &u32_pin_result);
			if(TWI_SUCCESS == s32_retval)
			{
				PH_SENSE_LOG("ADC Pin value of pH Sensor: %d \n",u32_pin_result);

				u32_pin_result *=1000; /*x1000 to with millivolts*/

				/*RESULT = [V(P) – V(N) ] * 2^(RESOLUTION - m) * GAIN/REFERENCE */
				/* m = 0 for single ended, m = 1 for differential */
				/*V(P-N) = u32_pin_result * 6 *0.6 /(2^8) */
				u32_pin_result_mv = (u32_pin_result * 36) /(10*(1<<8));	
				PH_SENSE_LOG("Pin Value = %d mV \n",u32_pin_result_mv);
			}

			/* Start sampling form Reference pin */
			s32_retval = twi_adc_start(PH_REF_PIN_ADC_VIN_CH, ADC_DONOT_USE_DIFF_CHANNEL, PH_ADC_VREF_CH, PH_REF_PIN_ADC_CH_CONFIGS, &u32_ref_pin_result);
			if(TWI_SUCCESS == s32_retval)
			{
				PH_SENSE_LOG("ADC Ref Pin value of pH Sensor: %d \n",u32_ref_pin_result);

				u32_ref_pin_result *=1000; /*x1000 to with millivolts*/
				
				/*RESULT = [V(P) – V(N) ] * 2^(RESOLUTION - m) * GAIN/REFERENCE */
				/* m = 0 for single ended, m = 1 for differential */
				/*V(P-N) = u32_ref_pin_result * 6 *0.6 /(2^8) */
				u32_ref_pin_result_mv = (u32_ref_pin_result * 36) /(10*(1<<8));
				PH_SENSE_LOG("Ref Pin Value = %d mV \n",u32_ref_pin_result_mv);
			}

			s32_result_mv = u32_pin_result_mv - u32_ref_pin_result_mv;	
			PH_SENSE_LOG("Result Value = %d mV \n",s32_result_mv);

			if(s32_result_mv < MAX_ADC_PH_VALUE && s32_result_mv > MIN_ADC_PH_VALUE)
			{
				/*We could get the pH level.*/
				/*y(mV) = -71.466 x(pH) + 506.26 */
				*pu8_ph_val = (s32_result_mv * (1000) - 506260) / -71466 ;
				PH_SENSE_LOG("Value of pH Sensor = %d \n",*pu8_ph_val);
			}
			else
			{
				PH_SENSE_LOG_ERR("Failed Reading pH Sensor value\n");
			}
		}
		else
		{
			PH_SENSE_LOG_ERR("Failed Reading pH Sensor ret %d \n",s32_retval);
			s32_retval = TWI_ERROR_NOT_INITIALIZED;
		}
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	}

	return s32_retval;
}

/*
 *   @brief      This is a function that dispatch global flags.
 *   @param[out]  void.
 *   @retval      void.
 */
void twi_ph_sensor_dispatch(void)
{
	/*Do Nothing.*/
}

