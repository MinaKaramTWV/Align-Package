/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file			twi_accelerometer.c
 *	@brief			This file holds the implementation of the API used for Accelerometer usage.
 */

#if defined (LIS3DH_ACC_SENSOR)
	#include "twi_accelerometer_lis3dh_driver.h"
#elif defined (LIS2DH_ACC_SENSOR)
	#include "twi_accelerometer_lis2dh_driver.h"
#elif defined (KXTJ3_ACC_SENSOR)
	#include "twi_accelerometer_kxtj3_driver.h"
#endif

#include "twi_accelerometer.h"

/*-*****************************************************************************
* Function Name: twi_accelerometer_init								   		   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_init(tpf_accelerometer_interrupt pf_cb_int)
*
*	@brief		Function used for initialization of Accelerometer and setting it into default state
*
*	@param[in]	pf_cb_int pointer to function that user defines it for Call back when Accelerometer got action.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*	@note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_init(tpf_accelerometer_interrupt pf_cb_int)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	#if defined (LIS3DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis3dh_init((tpf_accelerometer_lis3dh_interrupt) pf_cb_int);
	#elif defined (LIS2DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis2dh_init((tpf_accelerometer_lis2dh_interrupt) pf_cb_int);
	#elif defined (KXTJ3_ACC_SENSOR)
		s32_retval = twi_accelerometer_kxtj3_init((tpf_accelerometer_kxtj3_interrupt) pf_cb_int);
	#endif

	return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_accelerometer_deinit									   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_deinit(void)
*
*	@brief		Function used for de-initialization of Accelerometer.
*
*	@param		none
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*	@note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_deinit(void)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	#if defined (LIS3DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis3dh_deinit();
	#elif defined (LIS2DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis2dh_deinit();
	#elif defined (KXTJ3_ACC_SENSOR)
		s32_retval = twi_accelerometer_kxtj3_deinit();
	#endif

	return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_accelerometer_get_6d_direction							   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_get_6d_direction(tenu_twi_accelerometer_6d_direction* penu_6d_pos)
*
*	@brief		Function used to read the movement direction for the Accelerometer.
*					Usage when the interrupt occurs.
*
*	@param[out]	penu_6d_dir	pointer to the direction of movement.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*	@note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_get_6d_direction(tenu_twi_accelerometer_6d_direction* penu_6d_dir)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	#if defined (LIS3DH_ACC_SENSOR)

		tenu_twi_accelerometer_lis3dh_6d_direction enu_6d_dir;

		enu_6d_dir = LIS3DH_NO_MOVE;

		if(NULL != penu_6d_dir)
		{
			s32_retval = twi_accelerometer_lis3dh_get_6d_direction(&enu_6d_dir);
			if(TWI_SUCCESS == s32_retval)
			{
				switch (enu_6d_dir)
				{
					case LIS3DH_MOVE_X_LOW:
						*penu_6d_dir = ACCELEROMTER_MOVE_X_LOW;
						break;
					case LIS3DH_MOVE_X_HIGH:
						*penu_6d_dir = ACCELEROMTER_MOVE_X_HIGH;
						break;
					case LIS3DH_MOVE_Y_LOW:
						*penu_6d_dir = ACCELEROMTER_MOVE_Y_LOW;
						break;
					case LIS3DH_MOVE_Y_HIGH:
						*penu_6d_dir = ACCELEROMTER_MOVE_Y_HIGH;
						break;
					case LIS3DH_MOVE_Z_LOW:
						*penu_6d_dir = ACCELEROMTER_MOVE_Z_LOW;
						break;
					case LIS3DH_MOVE_Z_HIGH:
						*penu_6d_dir = ACCELEROMTER_MOVE_Z_HIGH;
						break;
					default:
						*penu_6d_dir = ACCELEROMTER_NO_MOVE;
						break;
				}
			}
			else
			{
				s32_retval = TWI_ERROR;
			}
		}
		else
		{
			s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
		}

	#elif defined (LIS2DH_ACC_SENSOR)

		tenu_twi_accelerometer_lis2dh_6d_direction enu_6d_dir;

		enu_6d_dir = LIS2DH_NO_MOVE;

		if(NULL != penu_6d_dir)
		{
			s32_retval = twi_accelerometer_lis2dh_get_6d_direction(&enu_6d_dir);
			if(TWI_SUCCESS == s32_retval)
			{
				switch (enu_6d_dir)
				{
					case LIS2DH_MOVE_X_LOW:
						*penu_6d_dir = ACCELEROMTER_MOVE_X_LOW;
						break;
					case LIS2DH_MOVE_X_HIGH:
						*penu_6d_dir = ACCELEROMTER_MOVE_X_HIGH;
						break;
					case LIS2DH_MOVE_Y_LOW:
						*penu_6d_dir = ACCELEROMTER_MOVE_Y_LOW;
						break;
					case LIS2DH_MOVE_Y_HIGH:
						*penu_6d_dir = ACCELEROMTER_MOVE_Y_HIGH;
						break;
					case LIS2DH_MOVE_Z_LOW:
						*penu_6d_dir = ACCELEROMTER_MOVE_Z_LOW;
						break;
					case LIS2DH_MOVE_Z_HIGH:
						*penu_6d_dir = ACCELEROMTER_MOVE_Z_HIGH;
						break;
					default:
						*penu_6d_dir = ACCELEROMTER_NO_MOVE;
						break;
				}
			}
			else
			{
				s32_retval = TWI_ERROR;
			}
		}
		else
		{
			s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
		}
	#elif defined (KXTJ3_ACC_SENSOR)

		tenu_twi_accelerometer_kxtj3_6d_direction enu_6d_dir;

		enu_6d_dir = KXTJ3_NO_MOVE;

		if(NULL != penu_6d_dir)
		{
			s32_retval = twi_accelerometer_kxtj3_get_6d_direction(&enu_6d_dir);
			if(TWI_SUCCESS == s32_retval)
			{
				switch (enu_6d_dir)
				{
					case KXTJ3_MOVE_X_NEG:
						*penu_6d_dir = ACCELEROMTER_MOVE_X_LOW;
						break;
					case KXTJ3_MOVE_X_POS:
						*penu_6d_dir = ACCELEROMTER_MOVE_X_HIGH;
						break;
					case KXTJ3_MOVE_Y_NEG:
						*penu_6d_dir = ACCELEROMTER_MOVE_Y_LOW;
						break;
					case KXTJ3_MOVE_Y_POS:
						*penu_6d_dir = ACCELEROMTER_MOVE_Y_HIGH;
						break;
					case KXTJ3_MOVE_Z_NEG:
						*penu_6d_dir = ACCELEROMTER_MOVE_Z_LOW;
						break;
					case KXTJ3_MOVE_Z_POS:
						*penu_6d_dir = ACCELEROMTER_MOVE_Z_HIGH;
						break;
					default:
						*penu_6d_dir = ACCELEROMTER_NO_MOVE;
						break;
				}
			}
			else
			{
				s32_retval = TWI_ERROR;
			}
		}
		else
		{
			s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
		}
	#endif

	return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_accelerometer_get_axis_acc								   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_get_axis_acc(tenu_twi_accelerometer_axis_acceleration enu_axis_acc, twi_s16* ps16_x_axis_acc)
*
*	@brief		Function used to read the Acceleration Values for X or Y or Z axis.
*
*	@param[in]	enu_axis_acc	Acceleration type want to be get (X, Y, Z).
*								(ACCELEROMTER_X_AXIS_ACCELERATION ::), (ACCELEROMTER_Y_AXIS_ACCELERATION ::), (ACCELEROMTER_Y_AXIS_ACCELERATION ::).
*
*	@param[out]	ps16_axis_acc	pointer to value that holds the acceleration of the axis.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_get_axis_acc(tenu_twi_accelerometer_axis_acceleration enu_axis_acc, twi_s16* ps16_axis_acc)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	if(NULL != ps16_axis_acc)
	{
	#if defined (LIS3DH_ACC_SENSOR)
		switch (enu_axis_acc)
		{
			case ACCELEROMTER_X_AXIS_ACCELERATION:
				s32_retval = twi_accelerometer_lis3dh_get_axis_acc(LIS3DH_X_AXIS_ACCELERATION, ps16_axis_acc);
				break;
			case ACCELEROMTER_Y_AXIS_ACCELERATION:
				s32_retval = twi_accelerometer_lis3dh_get_axis_acc(LIS3DH_Y_AXIS_ACCELERATION, ps16_axis_acc);
				break;
			case ACCELEROMTER_Z_AXIS_ACCELERATION:
				s32_retval = twi_accelerometer_lis3dh_get_axis_acc(LIS3DH_Z_AXIS_ACCELERATION, ps16_axis_acc);
				break;
			default:
				s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
				break;
		}
	#elif defined (LIS2DH_ACC_SENSOR)
		switch (enu_axis_acc)
		{
			case ACCELEROMTER_X_AXIS_ACCELERATION:
				s32_retval = twi_accelerometer_lis2dh_get_axis_acc(LIS2DH_X_AXIS_ACCELERATION, ps16_axis_acc);
				break;
			case ACCELEROMTER_Y_AXIS_ACCELERATION:
				s32_retval = twi_accelerometer_lis2dh_get_axis_acc(LIS2DH_Y_AXIS_ACCELERATION, ps16_axis_acc);
				break;
			case ACCELEROMTER_Z_AXIS_ACCELERATION:
				s32_retval = twi_accelerometer_lis2dh_get_axis_acc(LIS2DH_Z_AXIS_ACCELERATION, ps16_axis_acc);
				break;
			default:
				s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
				break;
		}
	#elif defined (KXTJ3_ACC_SENSOR)
		switch (enu_axis_acc)
		{
			case ACCELEROMTER_X_AXIS_ACCELERATION:
				s32_retval = twi_accelerometer_kxtj3_get_axis_acc(KXTJ3_X_AXIS_ACCELERATION, ps16_axis_acc);
				break;
			case ACCELEROMTER_Y_AXIS_ACCELERATION:
				s32_retval = twi_accelerometer_kxtj3_get_axis_acc(KXTJ3_Y_AXIS_ACCELERATION, ps16_axis_acc);
				break;
			case ACCELEROMTER_Z_AXIS_ACCELERATION:
				s32_retval = twi_accelerometer_kxtj3_get_axis_acc(KXTJ3_Z_AXIS_ACCELERATION, ps16_axis_acc);
				break;
			default:
				s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
				break;
		}
	#endif
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	}
	return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_accelerometer_set_full_scale							   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_set_full_scale(tenu_twi_accelerometer_full_scale_option enu_fs)
*
*	@brief		Function used to Set the full scale of the accelerometer.
*
*	@param[in]	enu_fs	Full scale input.
*				(ACCELEROMETER_FULL_SCALE_2G ::), (ACCELEROMETER_FULL_SCALE_4G ::),
*				(ACCELEROMETER_FULL_SCALE_8G ::), (ACCELEROMETER_FULL_SCALE_16G ::)
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_set_full_scale(tenu_twi_accelerometer_full_scale_option enu_fs)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	#if defined (LIS3DH_ACC_SENSOR)
		switch (enu_fs)
		{
			case ACCELEROMETER_FULL_SCALE_2G:
				s32_retval = twi_accelerometer_lis3dh_set_full_scale(LIS3DH_FULL_SCALE_2G);
				break;
			case ACCELEROMETER_FULL_SCALE_4G:
				s32_retval = twi_accelerometer_lis3dh_set_full_scale(LIS3DH_FULL_SCALE_4G);
				break;
			case ACCELEROMETER_FULL_SCALE_8G:
				s32_retval = twi_accelerometer_lis3dh_set_full_scale(LIS3DH_FULL_SCALE_8G);
				break;
			case ACCELEROMETER_FULL_SCALE_16G:
				s32_retval = twi_accelerometer_lis3dh_set_full_scale(LIS3DH_FULL_SCALE_16G);
				break;
			default:
				s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
				break;
		}
	#elif defined (LIS2DH_ACC_SENSOR)
		switch (enu_fs)
		{
			case ACCELEROMETER_FULL_SCALE_2G:
				s32_retval = twi_accelerometer_lis2dh_set_full_scale(LIS2DH_FULL_SCALE_2G);
				break;
			case ACCELEROMETER_FULL_SCALE_4G:
				s32_retval = twi_accelerometer_lis2dh_set_full_scale(LIS2DH_FULL_SCALE_4G);
				break;
			case ACCELEROMETER_FULL_SCALE_8G:
				s32_retval = twi_accelerometer_lis2dh_set_full_scale(LIS2DH_FULL_SCALE_8G);
				break;
			case ACCELEROMETER_FULL_SCALE_16G:
				s32_retval = twi_accelerometer_lis2dh_set_full_scale(LIS2DH_FULL_SCALE_16G);
				break;
			default:
				s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
				break;
		}
	#elif defined (KXTJ3_ACC_SENSOR)
		switch (enu_fs)
		{
			/* TODO: Automate the resolution selection (Now forced 8-bits)*/
			case ACCELEROMETER_FULL_SCALE_2G:
				s32_retval = twi_accelerometer_kxtj3_set_full_scale(KXTJ3_FULL_SCALE_2G_8_BIT);
				break;
			case ACCELEROMETER_FULL_SCALE_4G:
				s32_retval = twi_accelerometer_kxtj3_set_full_scale(KXTJ3_FULL_SCALE_4G_8_BIT);
				break;
			case ACCELEROMETER_FULL_SCALE_8G:
				s32_retval = twi_accelerometer_kxtj3_set_full_scale(KXTJ3_FULL_SCALE_8G_8_BIT);
				break;
			case ACCELEROMETER_FULL_SCALE_16G:
				s32_retval = twi_accelerometer_kxtj3_set_full_scale(KXTJ3_FULL_SCALE_16G_8_BIT);
				break;
			default:
				s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
				break;
		}
	#endif


	return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_accelerometer_set_data_rate_config						   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_set_data_rate_config(tenu_twi_accelerometer_odr_cfg enu_odr)
*
*	@brief		Function used to set the Accelerometer Data rate configuration.
*
*	@param[in]	enu_odr	enum variable (Data Rate CFG) must be one of the following:
*						(ACCELEROMETER_ODR_1Hz ::), (ACCELEROMETER_ODR_10Hz ::), (ACCELEROMETER_ODR_25Hz ::), (ACCELEROMETER_ODR_50Hz ::),
*						(ACCELEROMETER_ODR_100Hz ::), (ACCELEROMETER_ODR_200Hz ::), (ACCELEROMETER_ODR_400Hz::)
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_set_data_rate_config(tenu_twi_accelerometer_odr_cfg enu_odr)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	#if defined (LIS3DH_ACC_SENSOR)
		switch (enu_odr)
		{
			case ACCELEROMETER_ODR_1Hz:
				s32_retval = twi_accelerometer_lis3dh_set_data_rate_config(LIS3DH_ODR_1Hz);
				break;
			case ACCELEROMETER_ODR_10Hz:
				s32_retval = twi_accelerometer_lis3dh_set_data_rate_config(LIS3DH_ODR_10Hz);
				break;
			case ACCELEROMETER_ODR_25Hz:
				s32_retval = twi_accelerometer_lis3dh_set_data_rate_config(LIS3DH_ODR_25Hz);
				break;
			case ACCELEROMETER_ODR_50Hz:
				s32_retval = twi_accelerometer_lis3dh_set_data_rate_config(LIS3DH_ODR_50Hz);
				break;
			case ACCELEROMETER_ODR_100Hz:
				s32_retval = twi_accelerometer_lis3dh_set_data_rate_config(LIS3DH_ODR_100Hz);
				break;
			case ACCELEROMETER_ODR_200Hz:
				s32_retval = twi_accelerometer_lis3dh_set_data_rate_config(LIS3DH_ODR_200Hz);
				break;
			case ACCELEROMETER_ODR_400Hz:
				s32_retval = twi_accelerometer_lis3dh_set_data_rate_config(LIS3DH_ODR_400Hz);
				break;
			default:
				s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
				break;
		}
	#elif defined (LIS2DH_ACC_SENSOR)
		switch (enu_odr)
		{
			case ACCELEROMETER_ODR_1Hz:
				s32_retval = twi_accelerometer_lis2dh_set_data_rate_config(LIS2DH_ODR_1Hz);
				break;
			case ACCELEROMETER_ODR_10Hz:
				s32_retval = twi_accelerometer_lis2dh_set_data_rate_config(LIS2DH_ODR_10Hz);
				break;
			case ACCELEROMETER_ODR_25Hz:
				s32_retval = twi_accelerometer_lis2dh_set_data_rate_config(LIS2DH_ODR_25Hz);
				break;
			case ACCELEROMETER_ODR_50Hz:
				s32_retval = twi_accelerometer_lis2dh_set_data_rate_config(LIS2DH_ODR_50Hz);
				break;
			case ACCELEROMETER_ODR_100Hz:
				s32_retval = twi_accelerometer_lis2dh_set_data_rate_config(LIS2DH_ODR_100Hz);
				break;
			case ACCELEROMETER_ODR_200Hz:
				s32_retval = twi_accelerometer_lis2dh_set_data_rate_config(LIS2DH_ODR_200Hz);
				break;
			case ACCELEROMETER_ODR_400Hz:
				s32_retval = twi_accelerometer_lis2dh_set_data_rate_config(LIS2DH_ODR_400Hz);
				break;
			default:
				s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
				break;
		}
	#elif defined (KXTJ3_ACC_SENSOR)
		switch (enu_odr)
		{
			case ACCELEROMETER_ODR_1Hz:
				s32_retval = twi_accelerometer_kxtj3_set_data_rate_config(KXTJ3_ODR_1_563Hz); /* There is no 1HZ ODR in KXTJ3 ACC*/
				break;
			case ACCELEROMETER_ODR_10Hz:
				s32_retval = twi_accelerometer_kxtj3_set_data_rate_config(KXTJ3_ODR_12_5Hz); /* There is no 10HZ ODR in KXTJ3 ACC*/
				break;
			case ACCELEROMETER_ODR_25Hz:
				s32_retval = twi_accelerometer_kxtj3_set_data_rate_config(KXTJ3_ODR_25Hz);
				break;
			case ACCELEROMETER_ODR_50Hz:
				s32_retval = twi_accelerometer_kxtj3_set_data_rate_config(KXTJ3_ODR_50Hz);
				break;
			case ACCELEROMETER_ODR_100Hz:
				s32_retval = twi_accelerometer_kxtj3_set_data_rate_config(KXTJ3_ODR_100Hz);
				break;
			case ACCELEROMETER_ODR_200Hz:
				s32_retval = twi_accelerometer_kxtj3_set_data_rate_config(KXTJ3_ODR_200Hz);
				break;
			case ACCELEROMETER_ODR_400Hz:
				s32_retval = twi_accelerometer_kxtj3_set_data_rate_config(KXTJ3_ODR_400Hz);
				break;
			default:
				s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
				break;
		}
	#endif

	return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_accelerometer_set_interrupt_thershold			   		   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_set_interrupt_thershold(twi_u8 u8_th_val)
*
*	@brief		Function used to set the threshold of the interrupt accelerometer.
*				The threshold value depends on the full scale value (It's 7 bits only full scale 2^7 = 128).
*				Threshold LSB value = 128/Full scale. The next table indicates the threshold LSB values.
*					 _______________________________________________
*					|				|								|
*					|	Full Scale	|	Threshold LSB value (mg)	|
*					|_______________|_______________________________|
*					|	  -/+2g		|			15.625				|
*					|_______________|_______________________________|
*					|	  -/+4g		|			31.25				|
*					|_______________|_______________________________|
*					|	  -/+8g		|			 62.5				|
*					|_______________|_______________________________|
*					|	 -/+16g		|			 125				|
*					|_______________|_______________________________|
*
*	@param[in]	u8_th_val	Threshold value for Interrupt 1 (value from 0 to 127) else error value should be returned.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_set_interrupt_thershold(twi_u8 u8_th_val)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	#if defined (LIS3DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis3dh_set_interrupt_thershold(u8_th_val);
	#elif defined (LIS2DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis2dh_set_interrupt_thershold(u8_th_val);
	#elif defined (KXTJ3_ACC_SENSOR)
		s32_retval = twi_accelerometer_kxtj3_set_interrupt_thershold(u8_th_val);
	#endif

	return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_accelerometer_set_shock_thershold				   		   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_set_shock_thershold(twi_u8 u8_th_val)
*
*	@brief		Function used to set the shock threshold of the interrupt accelerometer.
*				The threshold value depends on the full scale value (It's 7 bits only full scale 2^7 = 128).
*				Threshold LSB value = 128/Full scale. The next table indicates the threshold LSB values.
*					 _______________________________________________
*					|				|								|
*					|	Full Scale	|	Threshold LSB value (mg)	|
*					|_______________|_______________________________|
*					|	  -/+2g		|			15.625				|
*					|_______________|_______________________________|
*					|	  -/+4g		|			31.25				|
*					|_______________|_______________________________|
*					|	  -/+8g		|			 62.5				|
*					|_______________|_______________________________|
*					|	 -/+16g		|			 125				|
*					|_______________|_______________________________|
*
*	@param[in]	u8_th_val	Threshold value for Interrupt 1 (value from 0 to 127) else error value should be returned.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_set_shock_thershold(twi_u8 u8_th_val)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	#if defined (LIS3DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis3dh_set_shock_thershold(u8_th_val);
	#elif defined (LIS2DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis2dh_set_shock_thershold(u8_th_val);
	#elif defined (KXTJ3_ACC_SENSOR)
		/* Un-supported Feature */
		s32_retval = twi_accelerometer_kxtj3_set_shock_thershold(u8_th_val);
	#endif

	return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_accelerometer_set_shock_duration						   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_set_shock_duration(twi_u8 u8_th_val)
*
*	@brief		Function used to set the Set the minimum duration of the Shock Interrupt 1 event to be recognized for the accelerometer "LIS3DH".
*				The duration value depends on the ODR value (It's 7 bits only full scale 2^7 = 128).
*				Duration LSB value = 1/ODR. The next table indicates the duration LSB values.
*					 ___________________________________________
*					|				|							|
*					|	 ODR (Hz)	|	Duration LSB value (ms)	|
*					|_______________|___________________________|
*					|	  	1		|			1000			|
*					|_______________|___________________________|
*					|	  	10		|			100				|
*					|_______________|___________________________|
*					|	  	25		|			40				|
*					|_______________|___________________________|
*					|	 	50		|			20				|
*					|_______________|___________________________|
*					|	 	100		|			10				|
*					|_______________|___________________________|
*					|	 	200		|			5				|
*					|_______________|___________________________|
*					|	 	400		|			2.5				|
*					|_______________|___________________________|
*
*	@param[in]	u8_duration_val	Duration value for Interrupt 1 (value from 0 to 127) else error value should be returned.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_set_shock_duration(twi_u8 u8_th_val)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	#if defined (LIS3DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis3dh_set_shock_duration(u8_th_val);
	#elif defined (LIS2DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis2dh_set_shock_duration(u8_th_val);
	#elif defined (KXTJ3_ACC_SENSOR)
		/* Un-supported Feature */
		s32_retval = twi_accelerometer_kxtj3_set_shock_duration(u8_th_val);
	#endif

	return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_accelerometer_set_interrupt_duration					   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_set_interrupt_duration(twi_u8 u8_duration_val)
*
*	@brief		Function used to set the Set the minimum duration of the Interrupt 1 event to be recognized for the accelerometer.
*				The duration value depends on the ODR value (It's 7 bits only full scale 2^7 = 128).
*				Duration LSB value = 1/ODR. The next table indicates the duration LSB values.
*					 ___________________________________________
*					|				|							|
*					|	 ODR (Hz)	|	Duration LSB value (ms)	|
*					|_______________|___________________________|
*					|	  	1		|			1000			|
*					|_______________|___________________________|
*					|	  	10		|			100				|
*					|_______________|___________________________|
*					|	  	25		|			40				|
*					|_______________|___________________________|
*					|	 	50		|			20				|
*					|_______________|___________________________|
*					|	 	100		|			10				|
*					|_______________|___________________________|
*					|	 	200		|			5				|
*					|_______________|___________________________|
*					|	 	400		|			2.5				|
*					|_______________|___________________________|

*
*	@param[in]	u8_duration_val	Duration value for Interrupt 1 (value from 0 to 127) else error value should be returned.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_set_interrupt_duration(twi_u8 u8_duration_val)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	#if defined (LIS3DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis3dh_set_interrupt_duration(u8_duration_val);
	#elif defined (LIS2DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis2dh_set_interrupt_duration(u8_duration_val);
	#elif defined (KXTJ3_ACC_SENSOR)
		s32_retval = twi_accelerometer_kxtj3_set_interrupt_duration(u8_duration_val);
	#endif

	return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_accelerometer_detect_mode								   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_detect_mode(tenu_twi_accelerometer_detection_option enu_detect_op)
*
*	@brief		Function used to Set the detection mode of the accelerometer.
*
*	@param[in]	enu_detect_op	Detection option input must be one of the following:
*									(ACCELEROMTER_DETECT_FREE_FALL ::),	(ACCELEROMTER_DETECT_MOVEMENT ::)
*									(ACCELEROMTER_DETECT_POSITION ::), (ACCELEROMTER_DETECT_SHOCK ::), (ACCELEROMTER_NO_DETECT ::)
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_detect_mode(tenu_twi_accelerometer_detection_option enu_detect_op)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	#if defined (LIS3DH_ACC_SENSOR)
		switch (enu_detect_op)
		{
			case ACCELEROMTER_DETECT_FREE_FALL:
				s32_retval = twi_accelerometer_lis3dh_free_fall_detect();
				break;
			case ACCELEROMTER_DETECT_MOVEMENT:
				s32_retval = twi_accelerometer_lis3dh_movement_detect();
				break;
			case ACCELEROMTER_DETECT_POSITION:
				s32_retval = twi_accelerometer_lis3dh_position_detect();
				break;
			case ACCELEROMTER_DETECT_SHOCK:
				s32_retval = twi_accelerometer_lis3dh_shock_detect();
				break;
			default:
				s32_retval = twi_accelerometer_lis3dh_no_detect();
				break;
		}
	#elif defined (LIS2DH_ACC_SENSOR)
		switch (enu_detect_op)
		{
			case ACCELEROMTER_DETECT_FREE_FALL:
				s32_retval = twi_accelerometer_lis2dh_free_fall_detect();
				break;
			case ACCELEROMTER_DETECT_MOVEMENT:
				s32_retval = twi_accelerometer_lis2dh_movement_detect();
				break;
			case ACCELEROMTER_DETECT_POSITION:
				s32_retval = twi_accelerometer_lis2dh_position_detect();
				break;
			case ACCELEROMTER_DETECT_SHOCK:
				s32_retval = twi_accelerometer_lis2dh_shock_detect();
				break;
			default:
				s32_retval = twi_accelerometer_lis2dh_no_detect();
				break;
		}
	#elif defined (KXTJ3_ACC_SENSOR)
		switch (enu_detect_op)
		{
			case ACCELEROMTER_DETECT_FREE_FALL:
				/* Un-supported Feature */
				s32_retval = twi_accelerometer_kxtj3_free_fall_detect();
				break;
			case ACCELEROMTER_DETECT_MOVEMENT:
				s32_retval = twi_accelerometer_kxtj3_movement_detect();
				break;
			case ACCELEROMTER_DETECT_POSITION:
				/* Un-supported Feature */
				s32_retval = twi_accelerometer_kxtj3_position_detect();
				break;
			case ACCELEROMTER_DETECT_SHOCK:
				/* Un-supported Feature */
				s32_retval = twi_accelerometer_kxtj3_shock_detect();
				break;
			default:
				s32_retval = twi_accelerometer_kxtj3_no_detect();
				break;
		}
	#endif

	return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_accelerometer_get_interrupt_cause						   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_get_interrupt_cause(twi_u8 *pu8_interrupt_cause)
*
*	@brief		Function used to Get the cause of the interrupt of the accelerometer.
*
*	@param[out]	pu8_interrupt_cause	    filled with the cause of interrupt. It is an ORed flags of tenu_twi_accelerometer_interrupt_cause.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must call it once after the interrupt to re-enable the interrupt again. The interrupt cause is latched till call that function.
*               You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_get_interrupt_cause(twi_u8 *pu8_interrupt_cause)
{
	twi_s32 s32_retval;

#if defined (LIS3DH_ACC_SENSOR) || defined (LIS2DH_ACC_SENSOR) || defined (KXTJ3_ACC_SENSOR)
	twi_u8 u8_interrupt_cause;
#endif

	s32_retval = TWI_SUCCESS;

    if(NULL != pu8_interrupt_cause)
    {
        *pu8_interrupt_cause = 0;
        
		#if defined (LIS3DH_ACC_SENSOR)

            s32_retval = twi_accelerometer_lis3dh_get_interrupt_cause(&u8_interrupt_cause);
            if(u8_interrupt_cause & ACCELEROMTER_LIS3DH_FALL)
            {
                *pu8_interrupt_cause |= ACCELEROMTER_FALL;
            }
            if(u8_interrupt_cause & ACCELEROMTER_LIS3DH_MOVED)
            {
                *pu8_interrupt_cause |= ACCELEROMTER_MOVED;
            }
            if(u8_interrupt_cause & ACCELEROMTER_LIS3DH_SHOCKED)
            {
                *pu8_interrupt_cause |= ACCELEROMTER_SHOCKED;
            }
		#elif defined (LIS2DH_ACC_SENSOR)

            s32_retval = twi_accelerometer_lis2dh_get_interrupt_cause(&u8_interrupt_cause);
            if(u8_interrupt_cause & ACCELEROMTER_LIS2DH_FALL)
            {
                *pu8_interrupt_cause |= ACCELEROMTER_FALL;
            }
            if(u8_interrupt_cause & ACCELEROMTER_LIS2DH_MOVED)
            {
                *pu8_interrupt_cause |= ACCELEROMTER_MOVED;
            }
            if(u8_interrupt_cause & ACCELEROMTER_LIS2DH_SHOCKED)
            {
                *pu8_interrupt_cause |= ACCELEROMTER_SHOCKED;
            }
		#elif defined (KXTJ3_ACC_SENSOR)

            s32_retval = twi_accelerometer_kxtj3_get_interrupt_cause(&u8_interrupt_cause);
            if(u8_interrupt_cause & ACCELEROMTER_KXTJ3_FALL)
            {
                *pu8_interrupt_cause |= ACCELEROMTER_FALL;
            }
            if(u8_interrupt_cause & ACCELEROMTER_KXTJ3_MOVED)
            {
                *pu8_interrupt_cause |= ACCELEROMTER_MOVED;
            }
            if(u8_interrupt_cause & ACCELEROMTER_KXTJ3_SHOCKED)
            {
                *pu8_interrupt_cause |= ACCELEROMTER_SHOCKED;
            }
        #endif
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }

	return s32_retval;
}

/*-******************************************************************************
* Function Name: twi_accelerometer_get_fifo_content				   		*
*********************************************************************************
*	@function	twi_s32 twi_accelerometer_get_fifo_content(twi_u8 u8_needed_levels_num, twi_s16 *ps16_acc_fifo_buf, twi_u8* pu8_actual_levels_num)
*
*	@brief		Function used to Get the content of the FIFO.
*				Each level is consist of the acceleration of the three axes (x, y, z) and each is represented in s16.
*				The level is consist of 6 bytes of 3 words.
*
*	@param[in]		u8_needed_levels_num	    the number of level to read.
*	@param[in,out]	ps16_acc_fifo_buf   		the FIFO buffer.
*	@param[out]		pu8_actual_levels_num	    the actual number or read levels.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_get_fifo_content(twi_u8 u8_needed_levels_num, twi_s16 *ps16_acc_fifo_buf, twi_u8* pu8_actual_levels_num)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	#if defined (LIS3DH_ACC_SENSOR)
		/*TODO: Implement this function for LIS3DH Accelerometer and call it here. */
	#elif defined (LIS2DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis2dh_get_fifo_content(u8_needed_levels_num, ps16_acc_fifo_buf, pu8_actual_levels_num);
	#elif defined (KXTJ3_ACC_SENSOR)
		/* Un-supported Feature */
		s32_retval = twi_accelerometer_kxtj3_get_fifo_content(u8_needed_levels_num, ps16_acc_fifo_buf, pu8_actual_levels_num);
	#endif

	return s32_retval;
}

/********************************************************************************
* Function Name: twi_accelerometer_get_num_of_fifo_levels				   		*
*********************************************************************************
*	@function	twi_s32 twi_accelerometer_get_num_of_fifo_levels(twi_u8* pu8_actual_levels_num)
*
*	@brief		Function used to Get the actual number of the FIFO levels.
*
*	@param[out]		pu8_actual_levels_num	    the actual number or read levels.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_get_num_of_fifo_levels(twi_u8* pu8_actual_levels_num)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	#if defined (LIS3DH_ACC_SENSOR)
		/*TODO: Implement this function for LIS3DH Accelerometer and call it here. */
	#elif defined (LIS2DH_ACC_SENSOR)
		s32_retval = twi_accelerometer_lis2dh_get_num_of_fifo_levels(pu8_actual_levels_num);
	#elif defined (KXTJ3_ACC_SENSOR)
		/* Un-supported Feature */
		s32_retval = twi_accelerometer_kxtj3_get_num_of_fifo_levels(pu8_actual_levels_num);
	#endif

	return s32_retval;
}

/********************************************************************************
* Function Name: twi_accelerometer_check_validity_config				   		*
*********************************************************************************
*	@function	twi_accelerometer_check_validity_config(twi_bool* pb_validity)
*
*	@brief		Function used for validity configration of the Accelerometer.
*
*	@param[out]		pb_validity	the accelerometer configration validity, valid or not.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*******************************************************************************/
twi_s32 twi_accelerometer_check_validity_config(twi_bool* pb_validity)
{
	twi_s32 s32_retval = TWI_SUCCESS;
    if(NULL != pb_validity)
    {	
#if defined (LIS3DH_ACC_SENSOR)
		/*TODO: Implement this function for LIS3DH Accelerometer and call it here. */
#elif defined (LIS2DH_ACC_SENSOR)
        s32_retval = twi_accelerometer_lis2dh_check_validity_config(pb_validity);
#elif defined (KXTJ3_ACC_SENSOR)
        s32_retval = twi_accelerometer_kxtj3_check_validity_config(pb_validity);
#endif
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }
	return s32_retval;
}
