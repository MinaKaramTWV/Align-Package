/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_conn_param_mgmt.h
*   @brief      This layer is responsible of updating connection parameter of ble connection.
*/

#ifndef _TWI_CONN_PARAM_MGMT_H_
#define _TWI_CONN_PARAM_MGMT_H_
/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/

#include "twi_common.h"
#include "twi_ble_hal_conf.h"
#include "twi_ble_hal.h"
#include "twi_conn_param_mgmt_default_priorities.h"

/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/

#define TWI_ERR_CONN_PARAM_INV_ARG								(TWI_CONN_PARAM_MGMT_ERROR_BASE-1)		/** @brief: This indicates that the paramerters sent is not vaid **/
#define TWI_ERR_CONN_PARAM_LOWER_PRIOROTY						(TWI_CONN_PARAM_MGMT_ERROR_BASE-2)		/** @brief: This indicates that which is asked to update connection parameters has a lower priority **/
#define TWI_ERR_CONN_PARAM_BLE_NOT_CONNECTED					(TWI_CONN_PARAM_MGMT_ERROR_BASE-3)		/** @brief: This indicates that BLE is not connected **/


#define CONN_PARAM_NO_TIMEOUT			(0)						/** @brief: No timeout for the requested parameters*/

/*---------------------------------------------------------*/
/*- STRUCTS -----------------------------------------------*/
/*---------------------------------------------------------*/
/**
*	@struct		tstr_cur_con_param
*	@brief		Structure holds the current connection parameters.
*/
TWI_PACK(typedef struct
{
	twi_u16		u16_conn_intrvl_10xms;							/** @brief: Connection interval*/
	twi_u16		u16_slave_latency;								/** @brief: Slave Latency*/
	twi_u16		u16_superv_timeout_ms;							/** @brief: Supervision timeout*/
})tstr_cur_con_param;

/**
*	@struct		tstr_req_con_param
*	@brief		Structure holds the requested connection parameters and other info.
*/
TWI_PACK(typedef struct
{
	twi_u8		u8_priority;									/** @brief: The priority of the connection parameters*/
	twi_u8		u8_reserved;									/** @brief: reserved*/
	twi_u16		u16_min_conn_intrvl_10xms;						/** @brief: Minimum connection interval*/
	twi_u16		u16_max_conn_intrvl_10xms;						/** @brief: Maximum connection interval*/
	twi_u16		u16_slave_latency;								/** @brief: Slave Latency*/
	twi_u16		u16_superv_timeout_ms;							/** @brief: Supervision timeout*/
	twi_u16		u16_applying_timeout_sec;						/** @brief: Applying these parametres for certain time-out*/
})tstr_req_con_param;
/*-***********************************************************/
/*- APIs PROTOTYPES -----------------------------------------*/
/*-***********************************************************/
/**
 *	@brief		Function that initializes connection parameters managment.
 *	@param[in]	None
 *  @return 	::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
twi_s32 twi_conn_param_mgmt_init(void);

/**
 *	@brief		This function is used for setting connection parameters.
 *	@param[in]	pstr_twi_conn_params Pointer to connection parameters structure.
 *	@param[in]	u8_priority: the priority of the requested layer.
 *	@param[in]	u32_timeout_sec: Set these connection interval for certain timeout.
 *  @return 	::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
twi_s32 twi_conn_param_mgmt_set_param(const tstr_twi_conn_params * pstr_twi_conn_params, twi_u8 u8_priority, twi_u32 u32_timeout_sec);

/**
 *	@brief		This function is used for getting the current connection parameters.
 *	@param[out]	pstr_twi_conn_params Pointer to connection parameters structure.
 *  @return 	::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
twi_s32 twi_conn_param_mgmt_get_current_param(tstr_twi_conn_params * pstr_twi_conn_params);

/**
 *	@brief		This function is used for getting requested connection parameters.
 *	@param[out]	pstr_twi_conn_params Pointer to connection parameters structure.
 *	@param[out]	pu8_priority Pointer to get the current higher priority.
 *	@param[out]	pu32_timeout Pointer to get the current timeout.
 *  @return 	::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
twi_s32 twi_conn_param_mgmt_get_requested_param(tstr_twi_conn_params * pstr_twi_conn_params, twi_u8 * pu8_priority, twi_u32 * pu32_timeout);

/**
 *	@brief		Function that runs the main connection parameters loop.
 *	@param[in]	None.
 */
void twi_conn_param_mgmt_dispatch(void);

/**
 *	@brief		Function for handling BLE events from the Stack.
 * 	@param[in]	pstr_ble_evt Pointer to ble events.
 */
void twi_conn_param_mgmt_on_ble_evt(tstr_twi_ble_evt * pstr_ble_evt);

#ifdef SAVE_SYSTEM_SETTINGS
/**
 *	@brief		This function loads the saved settings for the conn param mgmt layer from flash memory.
 * 	@param[in]	None
 *	@return		::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
twi_s32 twi_conn_param_mgmt_load_settings(void);
#endif

#endif /*_TWI_CONN_PARAM_MGMT_H_*/

