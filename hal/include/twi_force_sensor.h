/****************************************************************************/
/* Copyright (c) 2022 Thirdwayv, Inc. All Rights Reserved.			*/
/****************************************************************************/

/**
 *	@file					twi_force_sensor.h
 *
 *	@brief					This file contains TWI force sensor HAL.
 *
 *
 */
 
#ifndef TWI_FORCE_SENSOR_H_INCLUDED
#define TWI_FORCE_SENSOR_H_INCLUDED

/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/
#include "twi_common.h"

/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/



/*-***********************************************************/
/*- ENUMS ---------------------------------------------------*/
/*-***********************************************************/

/*-**********************************************************/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*-**********************************************************/

/*-***********************************************************/
/*- STRUCTS AND UNIONS --------------------------------------*/
/*-***********************************************************/

/*-***********************************************************/
/*- API's Prototypes ----------------------------------------*/
/*-***********************************************************/

/**
*	@function	twi_s32 twi_force_sensor_init(void)
*
*	@brief		- Function used for initialization of Force sensor.
*
*   @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */
twi_s32 twi_force_sensor_init(void);

/**
 * @brief Read Force sensor 
 * @param[out] twi_s16* : Force sensor value.
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_force_sensor_read(twi_s16 *ps16_value);

/**
 * @brief Function that is used to de-initialize force Sensor
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_force_sensor_deinit(void);

#endif /* TWI_FORCE_SENSOR_H_INCLUDED */
