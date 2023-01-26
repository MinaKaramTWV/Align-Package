/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/*-***************************************************************************/
/**
 *	@file		twi_rhp_hardware.h
 *	@brief		This file is the header file of the hardware module of the Remote HAL Protocol
 */

#ifndef TWI_RHP_HARDWARE_H_
#define TWI_RHP_HARDWARE_H_

/** @defgroup TWI_RHP_HW_group TWI RHP Hardware
* @{
*/

//***********************************************************/
/*- INCLUDES -----------------------------------------------*/
//***********************************************************/

#include "twi_common.h"
#include "twi_rhp_types.h"

/*-***********************************************************/
/*- ENUMERATIONS --------------------------------------------*/
/*-***********************************************************/

/*-***********************************************************/
/*- STRUCTS AND UNIONS --------------------------------------*/
/*-***********************************************************/

/*-***********************************************************/
/*- FUNCTIONS' PROTOTYPES -----------------------------------*/
/*-***********************************************************/

/**
 * @function		twi_rhp_hardware_ble_evt
 * @brief			This function is to catch BLE Events, if needed
 */
void twi_rhp_hardware_ble_evt(void *pstr_evt);

/**
 * @function		twi_rhp_hardware_init
 * @brief			initializer of this layer
 * @param[in]		pstr_in: pointer to the input structure
 * @param[in]		pf_rqst_ntfy: Pointer to CB function of RHP engine.
 * @return 			::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
twi_s32 twi_rhp_hardware_init(const tstr_twi_rhp_hardware_in * pstr_in, tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy);

/**
 * @function		twi_rhp_hardware_deinit
 * @brief			de-initializer for this layer
 */
void twi_rhp_hardware_deinit(tenu_hw_deinit_reason enu_hw_deinit_reason);

/**
 *	@function	twi_s32 twi_rhp_hardware_io_crtl(tenu_io_ctrl_op ctrl_op, tuni_crtl_hw_data * puni_ctrl_data)
 *
 *	@brief		Control Hardware
 *
 *	@param[in]	enu_ctrl_op: enum indicate the hardware control operation type.
 *	@param[in]	puni_ctrl_data: Pointer to union holds data of HW operation based on operation type.
 *
 *	@return 	::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 *
 */
twi_s32 twi_rhp_hardware_io_crtl(tenu_io_ctrl_op enu_ctrl_op, tuni_io_ctrl_op_data * puni_ctrl_data);

/**
 *	@function	twi_s32 twi_rhp_hw_notify(tenu_rhp_engine_evt_type enu_engine_evt, void* pv_evt_data)
 *
 *	@brief		Notify the HW layer with application events
 *
 *	@param[in]	enu_engine_evt: enum that holds different application events.
 *	@param[in]	pv_evt_data: corresponding data to each event.
 *
 *	@return 	::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 *
 */

twi_s32 twi_rhp_hw_notify(tenu_rhp_engine_evt_type enu_engine_evt, void* pv_evt_data);

/**
 * @function		twi_rhp_hw_dispatch
 * @brief			Dispatcher
 */
void twi_rhp_hw_dispatch(void);

#ifdef SAVE_SYSTEM_SETTINGS
/**
 * 	@function	twi_s32 twi_rhp_hardware_save_settings(void)
 *	@brief		This function used to save the Hardware settings in the flash memory.
 *  @return 		::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
twi_s32 twi_rhp_hardware_save_settings(void);

/**
 *	@function	twi_s32 twi_rhp_hardware_load_settings(void)
 * 	@brief		This function used to load the Hardware settings from the flash memory.
 *  @return 		::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
twi_s32 twi_rhp_hardware_load_settings(void);
#endif

/** @} */ /*TWI_RHP_HW_group*/
#endif /* TWI_RHP_HARDWARE_H_ */
