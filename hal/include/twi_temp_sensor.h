/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_temp_sensor.h
*   @brief      This file contains TWI temperature sensor HAL.
*/

#ifndef _TWI_TEMP_SENSOR_H_
#define _TWI_TEMP_SENSOR_H_
/**
*   @defgroup temp_sensor_group TWI temperature sensor HAL
*   This is the definition of TWI HAL for temperature sensor.
*   @{
*/

/*----------------------------------------------------------*/
/*- INCLUDES -----------------------------------------------*/
/*----------------------------------------------------------*/

#include "twi_common.h"

/*----------------------------------------------------------*/
/*- MACROS -------------------------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*- CONSTANTS ----------------------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*----------------------------------------------------------*/

/*-*********************************************************/
/*- FUNCTION-LIKE MACROS ----------------------------------*/
/*-*********************************************************/
#define GET_TEMP_REAL_PART(s16_temp_val)	(s16_temp_val/100)
#define GET_TEMP_FRAC_PART(s16_temp_val)	(ABS(s16_temp_val%100))
/*----------------------------------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/
/*----------------------------------------------------------*/

/**-*****************************************************************************
* Function Name: twi_temp_sensor_init								   *
********************************************************************************
*	@function	twi_s32 twi_temp_sensor_init(void)
*
*	@brief		- Function used for initialization of Temperature sensor.
*
*   @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
*
*
*
*******************************************************************************/
twi_s32 twi_temp_sensor_init(void);
/**-*****************************************************************************
* Function Name: twi_temp_sensor_deinit							   *
********************************************************************************
*	@function	twi_s32 twi_temp_sensor_deinit(void)
*
*	@brief		Function used for de-initialization of Temperature sensor.
*
*	@param		none
*
*   @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
*
*
*
*******************************************************************************/
twi_s32 twi_temp_sensor_deinit(void);

/**
*   @brief      This is a function that gets the temperature in °C.
*   @param[out]  ps16_temp_value is the temperature*100
*   @retval     ::TWI_SUCCESS, ::TWI_ERROR_INTERNAL_ERROR,
*               ::TWI_ERROR_HW_TIMEOUT, ::TWI_ERROR_INVALID_ARGUMENTS.
*/
twi_s32 twi_temp_sensor_read(twi_s16 *ps16_temp_val);

/**
*   @brief      This is a function that dispatch global flags.
*   @param[out]  void.
*   @retval      void.
*/
void twi_temp_sensor_dispatch(void);

/** @} */   /*temp_sensor_group*/

#endif  /*_TWI_TEMP_SENSOR_H_*/
