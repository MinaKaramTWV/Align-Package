/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/*
 * twi_pressure_sensor.h
 *
 *  Created on: Apr 19, 2016
 *      Author: ahmed.samir
 */

#ifndef _TWI_PRESSURE_SENSOR_H_
#define _TWI_PRESSURE_SENSOR_H_

//***********************************************************
/*- INCLUDES -----------------------------------------------*/
//***********************************************************
#include "twi_types.h"

/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/


//***********************************************************
/*- PRIMITIVE TYPES ----------------------------------------*/
//***********************************************************

//***********************************************************
/*- ENUMS --------------------------------------------------*/
//***********************************************************

//***********************************************************
/*- STRUCTS AND UNIONS -------------------------------------*/
//***********************************************************


//***********************************************************
/*- FUNCTION-LIKE MACROS -----------------------------------*/
//***********************************************************

//***********************************************************
/*- FUNCTION DECLARATIONS ----------------------------------*/
//***********************************************************

/**-*****************************************************************************
* Function Name: twi_pressure_sensor_init								   *
********************************************************************************
*	@function	twi_s32 twi_pressure_sensor_init(void)
*
*	@brief		- Function used for initialization of Barometer Pressure sensor.
*
*   @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
*
*
*
*******************************************************************************/
twi_s32 twi_pressure_sensor_init(void);

/**-*****************************************************************************
* Function Name: twi_pressure_sensor_deinit							   *
********************************************************************************
*	@function	twi_s32 twi_pressure_sensor_deinit(void)
*
*	@brief		Function used for de-initialization of Barometer Pressure sensor.
*
*   @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
*
*
*
*******************************************************************************/
twi_s32 twi_pressure_sensor_deinit(void);

/**-*****************************************************************************
* Function Name: twi_pressure_sensor_calib_err_set
********************************************************************************
*	@function	twi_s32 twi_pressure_sensor_calib_err_set(void)
*
*	@brief		Function used for calibraing the sensor.
*
*	@return		Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
*
*
*
*******************************************************************************/
twi_s32 twi_pressure_sensor_calib_err_set(twi_s32 s32_press_calib_error);
/**-*****************************************************************************
* Function Name: twi_pressure_sensor_calib_err_get
********************************************************************************
*	@function	twi_s32 twi_pressure_sensor_calib_err_get(void)
*
*	@brief		Function used for calibraing the sensor.
*
*	@return		Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
*
*
*
*******************************************************************************/
twi_s32 twi_pressure_sensor_calib_err_get(twi_s32 * ps32_press_calib_error);

/*-*****************************************************************************
* Function Name: twi_pressure_read							   *
********************************************************************************
*	@function	 twi_pressure_sensor_read(twi_s8 *pu16_press_int, twi_u8 *pu8_temp_fraction)
*
*	@brief		 Function used for reading pressure value from sensor in hPa.
*
*   @param[out]  pu16_press_int		:  This is the integer part of pressure.
*
*   @param[out]  pu8_press_frac		:  This is the fraction part of pressure, 2 digit only after fraction.
*
*   @return      Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
*
*
*
*******************************************************************************/
twi_s32 twi_pressure_sensor_read(twi_u16 *pu16_press_int, twi_u8 *pu8_press_frac);


#endif /* _TWI_PRESSURE_SENSOR_H_ */
