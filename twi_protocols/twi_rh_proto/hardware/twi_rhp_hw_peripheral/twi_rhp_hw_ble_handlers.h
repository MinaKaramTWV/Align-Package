/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file					twi_rhp_hw_ble_handlers.h
 ** @brief					This file includes the interface for the hardware with Remote HAL Protocol
 */

#ifndef TWI_RHP_HW_BLE_HANDLERS_H_
#define TWI_RHP_HW_BLE_HANDLERS_H_

//***********************************************************
/*- INCLUDES -----------------------------------------------*/
//***********************************************************

#include "twi_rhp_types.h"
#include "twi_ble_hal_types.h"

/************************************************************/
/*- GLOBAL EXTERN VARIABLES --------------------------------*/
/************************************************************/

extern const tstrt_hardware_handlers estr_ble_start_stop_adv_handlers;
#if defined(TWI_BLE_ENABLE_ADV_INTERVAL) || defined (TWI_HW_BLE_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_ble_adv_interval_handlers;
#endif
#if defined(TWI_BLE_ENABLE_TX_POWER_HANDLER) || defined (TWI_HW_BLE_FULL_FUNCTION) 
extern const tstrt_hardware_handlers estr_ble_tx_pwr_handlers;
#endif
#if defined(TWI_BLE_ENABLE_APP_DATA_HANDLERS) || defined (TWI_HW_BLE_FULL_FUNCTION)  
extern const tstrt_hardware_handlers estr_ble_app_data_handlers;
#endif
#if defined(BLE_CENTRAL_ROLE_SUPPORTED) || defined (TWI_HW_BLE_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_ble_scan_operation_handlers;
extern const tstrt_hardware_handlers estr_ble_scan_result_handlers;
extern const tstrt_hardware_handlers estr_ble_central_connect_address_handlers;
extern const tstrt_hardware_handlers estr_ble_central_connect_operation_handlers;
extern const tstrt_hardware_handlers estr_ble_central_connect_status_handlers;
#endif
#if defined(TWI_BLE_PER_CONN_OPE) || defined (TWI_HW_BLE_FULL_FUNCTION) 
extern const tstrt_hardware_handlers estr_ble_peripheral_connect_operation_handlers;
#endif
extern const tstrt_hardware_handlers estr_ble_peripheral_connect_status_handlers;
#if defined(ADVERTISE_WITHOUT_AML_AND_OPP) || defined (TWI_HW_BLE_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_ble_peripheral_adv_data;
#endif
#if (defined(ADV_PKT_COUNTER_ENABLED) && !defined(ADVERTISE_WITHOUT_AML_AND_OPP)) || defined (TWI_HW_BLE_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_ble_peripheral_adv_pkt_count_handlers;
#endif
extern const tstrt_hardware_handlers estr_ble_peripheral_always_connected_mode_handlers;
#if defined(TWI_CONN_PARAM_MGMT) || defined (TWI_HW_BLE_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_ble_request_conn_param_handlers;
extern const tstrt_hardware_handlers estr_ble_current_conn_param_handlers;
#endif
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
 *	@function	void twi_rhp_hw_on_ble_evt(tstr_twi_ble_evt * pstr_ble_evt);
 *	@brief      This function called when an event on BLE happens
 *	@param[in]  pstr_ble_evt	Pointer to structure holds the BLE event information.
 */
void twi_rhp_hw_on_ble_evt(tstr_twi_ble_evt * pstr_ble_evt);

/**
 *	@function	twi_s32 twi_rhp_hw_ble_dispatch(void);
 *	@brief      This function for do the postponed events for BLE handlers
 */
void twi_rhp_hw_ble_dispatch(void);

#endif /* TWI_RHP_HW_BLE_HANDLERS_H_ */
