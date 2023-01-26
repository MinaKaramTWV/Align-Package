/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_bat_sensor.h
*   @brief      This file contains TWI Battery HAL.
*/

#ifndef _TWI_BAT_SENSOR_H_
#define _TWI_BAT_SENSOR_H_
/**
*   @defgroup bat_group TWI Battery HAL
*   This is the definition of TWI HAL for Battery sensor.
*   @{
*/

/*----------------------------------------------------------*/
/*- INCLUDES -----------------------------------------------*/
/*----------------------------------------------------------*/

#include "twi_common.h"

/*----------------------------------------------------------*/
/*- CONSTANTS ----------------------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*- ENUMS ----------------------------------------------*/
/*----------------------------------------------------------*/
typedef enum
{
    BATTERY_CHARGE_STATE_DISCHARGING =1,
    BATTERY_CHARGE_STATE_CHARGING =2,
    BATTERY_CHARGE_FULLY_CHARGED =3,
    BATTERY_CHARGE_NOT_SUPPORTED = 0xFF,
} teun_batt_charge_state;
/*----------------------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/
/*----------------------------------------------------------*/
/**
*   @brief      This is a function that initialize the battery sensor.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_bat_sensor_init(void);

/**
*   @brief      This is a function that gets the battery voltage level. The battery level will be (*pu32_real + *pu32_frac / 100).
*   @param[out]  pu32_real  The real part of the battery level.
*   @param[out]  pu32_frac  The fraction part of the battery level.
*   @retval     ::TWI_SUCCESS, ::TWI_ERROR_INVALID_CONFIG,
*               ::TWI_ERROR_HW_TIMEOUT, ::TWI_ERROR_ALREADY_RESERVED,
*               ::TWI_ERROR_INVALID_ARGUMENTS.
*/
twi_s32 twi_bat_sensor_read(twi_u32 *pu32_real, twi_u32 *pu32_frac);

/**
 *	@function	twi_s32 twi_bat_prcntg_calculate(twi_u16 u16_readings_in_mv, twi_u8* pu8_battery_percenatge,twi_u8* pu8_battery_charge_state)
 *	@brief      This API shall be used by battery Handler to get the percentage value of battery voltage
 *	@param[in] 	u16_readings_in_mv: the mV reading from HW battery Handler.
 *	@param[out] pu8_battery_percenatge: returns the battery percentage.
 *	@param[out] pu8_battery_charge_state: returns the battery charging state.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_bat_prcntg_calculate(twi_u16 u16_readings_in_mv, twi_u8* pu8_battery_percenatge,twi_u8* pu8_battery_charge_state);
/** @} */   /*bat_group*/

#endif  /*_TWI_BAT_SENSOR_H_*/
