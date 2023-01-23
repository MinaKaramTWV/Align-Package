/****************************************************************************/
/* Copyright (c) 2022 Thirdwayv, Inc. All Rights Reserved.                  */
/****************************************************************************/

/**
 *	@file					twi_ph_sensor.h
 *
 *	@brief					Header file includes implementation of Align pH Sensor
 */

/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/
#include "twi_adc.h"
#include "platform_defines.h"

/*---------------------------------------------------------*/
/*- API's Prototypes --------------------------------------*/
/*---------------------------------------------------------*/

/**
 *	@function	twi_s32 twi_ph_sensor_init(void)
 *  @brief		Function used for initialization of pH sensor.
 *  @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */
twi_s32 twi_ph_sensor_init(void);

/**
 *	@function	twi_s32 twi_ph_sensor_deinit(void)
 *  @brief		Function used for de-initialization of pH sensor.
 *  @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */
twi_s32 twi_ph_sensor_deinit(void);

/**
 *	@function	twi_s32 twi_ph_sensor_read(twi_u8 *pu8_ph_val)
 *  @brief		Function used for reading current pH sensor".
 *  @param[out] pu8_ph_val   The pH value read from the pH sensor.
 *  @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */
twi_s32 twi_ph_sensor_read(twi_u8 *pu8_ph_val);

/**
 *   @brief      This is a function that dispatch global flags.
 *   @param[out]  void.
 *   @retval      void.
 */
void twi_ph_sensor_dispatch(void);

