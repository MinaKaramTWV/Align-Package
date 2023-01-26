/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file					twi_rhp_hw_time_handlers.h
 ** @brief					This file includes the interface for the hardware with Remote HAL Protocol
 */

#ifndef TWI_RHP_HW_TIME_HANDLERS_H_
#define TWI_RHP_HW_TIME_HANDLERS_H_

//***********************************************************
/*- INCLUDES -----------------------------------------------*/
//***********************************************************

#include "twi_rhp_types.h"

/************************************************************/
/*- Macros --------------------------------*/
/************************************************************/
#define UTC_TIME_RQST_VAL			0xFFFFFFFF	/*this value used to indicate that time handler need to request UTC time*/

/************************************************************/
/*- GLOBAL EXTERN VARIABLES --------------------------------*/
/************************************************************/

extern const tstrt_hardware_handlers estr_time_handlers;

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
 *	@function	twi_s32 twi_rhp_hw_time_io_crtl(tenu_hw_ctrl_op ctrl_op, tuni_crtl_hw_data * puni_hw_data)
 *
 *	@brief		Control Hardware
 *
 *	@param[in]	enu_ctrl_op: enum indicate the hardware control operation type.
 *	@param[in]	puni_hw_data: Pointer to union holds data of HW operation based on operation type.
 *
 *	@return 	::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 *
 */
twi_s32 twi_rhp_hw_time_io_crtl(tenu_io_ctrl_op enu_ctrl_op, tuni_io_ctrl_op_data * puni_ctrl_data);

/**
 *	@function	twi_s32 twi_rhp_hw_timezone_crtl(tenu_hw_ctrl_op ctrl_op, tuni_crtl_hw_data * puni_hw_data)
 *
 *	@brief		Control timezone
 *
 *	@param[in]	enu_ctrl_op: enum indicate the hardware control operation type.
 *	@param[in]	puni_hw_data: Pointer to union holds data of HW operation based on operation type.
 *
 *	@return 	::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 *
 */
twi_s32 twi_rhp_hw_timezone_crtl(tenu_io_ctrl_op enu_ctrl_op, tuni_io_ctrl_op_data * puni_ctrl_data);

/** @brief Time Handler dispatch function */
void twi_rhp_hw_time_dispatch(void);

#endif /* TWI_RHP_HW_TIME_HANDLERS_H_ */
