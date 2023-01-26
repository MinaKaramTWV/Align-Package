/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. */
/****************************************************************************/
/**
 ** @file					twi_rhp_hw_digital_handlers.h
 ** @brief					This file includes the interface for the hardware with Remote HAL Protocol
 */

#ifndef TWI_RHP_HW_DIGITAL_HANDLERS_H_
#define TWI_RHP_HW_DIGITAL_HANDLERS_H_

//***********************************************************
/*- INCLUDES -----------------------------------------------*/
//***********************************************************

#include "twi_rhp_types.h"

/************************************************************/
/*- GLOBAL EXTERN VARIABLES --------------------------------*/
/************************************************************/

extern const tstrt_hardware_handlers estr_gpio_handlers;
extern const tstrt_hardware_handlers estr_gpio_pull_handlers;
extern const tstrt_hardware_handlers estr_led_handlers;
extern const tstrt_hardware_handlers estr_pbtn_handlers;
extern const tstrt_hardware_handlers estr_pwm_handlers;

/************************************************************/
/*- CONSTANTS ----------------------------------------------*/
/************************************************************/

/*-***********************************************************/
/*- STRUCTS AND UNIONS --------------------------------------*/
/*-***********************************************************/

/*-***********************************************************/
/*- FUNCTIONS' PROTOTYPES -----------------------------------*/
/*-***********************************************************/

#endif /* TWI_RHP_HW_DIGITAL_HANDLERS_H_ */
