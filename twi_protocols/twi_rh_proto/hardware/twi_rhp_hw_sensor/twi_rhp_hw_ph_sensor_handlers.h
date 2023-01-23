/*-**************************************************************************-*/
/*- Copyright 2022 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file	    twi_rhp_hw_ph_sensor_handlers.h
 ** @brief		This file includes the interface for the hardware with Remote HAL Protocol
 */

#ifndef TWI_RHP_HW_PH_SENSOR_HANDLERS_H_
#define TWI_RHP_HW_PH_SENSOR_HANDLERS_H_

//***********************************************************
/*- INCLUDES -----------------------------------------------*/
//***********************************************************

#include "twi_rhp_types.h"

/************************************************************/
/*- GLOBAL EXTERN VARIABLES --------------------------------*/
/************************************************************/

extern const tstrt_hardware_handlers estr_ph_sensor_handlers;

/************************************************************/
/*- CONSTANTS ----------------------------------------------*/
/************************************************************/

/*-***********************************************************/
/*- STRUCTS AND UNIONS --------------------------------------*/
/*-***********************************************************/

/*-***********************************************************/
/*- FUNCTIONS' PROTOTYPES -----------------------------------*/
/*-***********************************************************/
/**
 * @function		twi_rhp_hw_ph_sensor_dispatch
 * @brief			Dispatcher
 */
void twi_rhp_hw_ph_sensor_dispatch(void);

#endif /* TWI_RHP_HW_PH_SENSOR_HANDLERS_H_ */
