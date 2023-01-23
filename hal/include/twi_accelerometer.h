/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file			twi_accelerometer.h
 *
 *	@brief			This file holds the needed definitions for the Accelerometer "LIS3DH" chip driver.
 *
 *
 *
 *
 */
#ifndef TWI_ACCELEROMETER_H_
#define TWI_ACCELEROMETER_H_


/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/
#include "twi_common.h"

/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------------*/
/*-*********************************************************/

/*-***********************************************************/
/*- ENUMS ---------------------------------------------------*/
/*-***********************************************************/

/**
* Enumeration for the Accelerometer Full Scale Option.
*/
typedef enum
{
	ACCELEROMETER_FULL_SCALE_2G	= 0,	/**< full scale -/+ 2G */

	ACCELEROMETER_FULL_SCALE_4G,		/**< full scale -/+ 4G */

	ACCELEROMETER_FULL_SCALE_8G,		/**< full scale -/+ 8G */

	ACCELEROMETER_FULL_SCALE_16G		/**< full scale -/+ 16G */
}tenu_twi_accelerometer_full_scale_option;

/**
* Enumeration for the Accelerometer Data Rate Configuration.
*/
typedef enum
{
	ACCELEROMETER_ODR_1Hz		= 1,	/**< Data rate = 1Hz */

	ACCELEROMETER_ODR_10Hz		= 2,	/**< Data rate = 10Hz */

	ACCELEROMETER_ODR_25Hz		= 3,	/**< Data rate = 25Hz */

	ACCELEROMETER_ODR_50Hz		= 4,	/**< Data rate = 50Hz */

	ACCELEROMETER_ODR_100Hz		= 5,	/**< Data rate = 100Hz */

	ACCELEROMETER_ODR_200Hz		= 6,	/**< Data rate = 200Hz */

	ACCELEROMETER_ODR_400Hz		= 7	/**< Data rate = 400Hz */
}tenu_twi_accelerometer_odr_cfg;

/**
* Enumeration for the Accelerometer movement 6D Positions.
*/
typedef enum
{
	ACCELEROMTER_NO_MOVE = 0,	/**< No move */

	ACCELEROMTER_MOVE_X_LOW,	/**< X low position */

	ACCELEROMTER_MOVE_X_HIGH,	/**< X high position */

	ACCELEROMTER_MOVE_Y_LOW,	/**< Y low position */

	ACCELEROMTER_MOVE_Y_HIGH,	/**< Y high position */

	ACCELEROMTER_MOVE_Z_LOW,	/**< Z low position */

	ACCELEROMTER_MOVE_Z_HIGH	/**< Z high position */
}tenu_twi_accelerometer_6d_direction;

/**
* Enumeration for the Accelerometer detection options.
*/
typedef enum
{
	ACCELEROMTER_DETECT_FREE_FALL = 0,	/**< Free fall detection */

	ACCELEROMTER_DETECT_MOVEMENT,		/**< Movement detection */

	ACCELEROMTER_DETECT_POSITION,		/**< Position detection */

	ACCELEROMTER_DETECT_SHOCK,			/**< Shock detection */

	ACCELEROMTER_NO_DETECT				/**< No detection */
}tenu_twi_accelerometer_detection_option;

/**
* Enumeration for the Accelerometer axis acceleration.
*/
typedef enum
{
	ACCELEROMTER_X_AXIS_ACCELERATION,		/**< X axis acceleration */

	ACCELEROMTER_Y_AXIS_ACCELERATION,		/**< Y axis acceleration */

	ACCELEROMTER_Z_AXIS_ACCELERATION,		/**< Z axis acceleration */

}tenu_twi_accelerometer_axis_acceleration;

/**
* Enumeration for the Accelerometer interrupt case.
*/
typedef enum
{
	ACCELEROMTER_FALL       =   0x01,	    	        /**< Free Fall. */

	ACCELEROMTER_MOVED      =   0x02, 		            /**< Movement. */

	ACCELEROMTER_SHOCKED    =   0x04,		            /**< Shock. */
}tenu_twi_accelerometer_interrupt_cause;
/*-**********************************************************/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*-**********************************************************/
typedef twi_s32(*tpf_accelerometer_interrupt)(void* pvalue);

/*-***********************************************************/
/*- STRUCTS AND UNIONS --------------------------------------*/
/*-***********************************************************/

/*******************************************************************************
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
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_init(tpf_accelerometer_interrupt pf_cb_int);

/*******************************************************************************
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
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_deinit(void);

/*******************************************************************************
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
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_get_6d_direction(tenu_twi_accelerometer_6d_direction* penu_6d_dir);

/*******************************************************************************
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
twi_s32 twi_accelerometer_get_axis_acc(tenu_twi_accelerometer_axis_acceleration enu_axis_acc, twi_s16* ps16_axis_acc);

/*******************************************************************************
* Function Name: twi_accelerometer_set_full_scale							   *
********************************************************************************
*	@function	twi_s32 twi_accelerometer_set_full_scale(tenu_twi_accelerometer_full_scale_option enu_fs)
*
*	@brief		Function used to Set the full scale of the accelerometer.
*
*	@param[in]	enu_fs	Full scale input.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
twi_s32 twi_accelerometer_set_full_scale(tenu_twi_accelerometer_full_scale_option enu_fs);

/*******************************************************************************
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
twi_s32 twi_accelerometer_set_data_rate_config(tenu_twi_accelerometer_odr_cfg enu_odr);

/*******************************************************************************
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
twi_s32 twi_accelerometer_set_interrupt_thershold(twi_u8 u8_th_val);

/*******************************************************************************
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
twi_s32 twi_accelerometer_set_shock_thershold(twi_u8 u8_th_val);

/*******************************************************************************
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
twi_s32 twi_accelerometer_set_shock_duration(twi_u8 u8_th_val);

/*******************************************************************************
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
twi_s32 twi_accelerometer_set_interrupt_duration(twi_u8 u8_duration_val);

/*******************************************************************************
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
twi_s32 twi_accelerometer_detect_mode(tenu_twi_accelerometer_detection_option enu_detect_op);

/*******************************************************************************
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
twi_s32 twi_accelerometer_get_interrupt_cause(twi_u8 *pu8_interrupt_cause);

/********************************************************************************
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
twi_s32 twi_accelerometer_get_fifo_content(twi_u8 u8_needed_levels_num, twi_s16 *ps16_acc_fifo_buf, twi_u8* pu8_actual_levels_num);

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
twi_s32 twi_accelerometer_get_num_of_fifo_levels(twi_u8* pu8_actual_levels_num);

/********************************************************************************
* Function Name: twi_accelerometer_check_validity_config				   		*
*********************************************************************************
*	@function	twi_accelerometer_check_validity_config(twi_bool* pb_validity)
*
*	@brief		Function used for validity configration of the Accelerometer.
*
*	@param[out]		pb_validity	    the accelerometer configration validity, valid or not.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*******************************************************************************/
twi_s32 twi_accelerometer_check_validity_config(twi_bool* pb_validity);

#endif /* TWI_ACCELEROMETER_H_ */
