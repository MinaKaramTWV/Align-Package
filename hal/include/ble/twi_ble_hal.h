/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file					twi_ble_hal.h
 ** @brief					This file implements API for the BLE-HAL Header File.
 **
 */

#ifndef _TWI_BLE_HAL_H_
#define _TWI_BLE_HAL_H_
/**
*   @defgroup ble_group TWI BLE HAL
*   This is the definition of TWI HAL for BLE.
*   @{
*/

/*TWI Includes */
#include "twi_ble_hal_types.h"
#include "twi_types.h"
#include "twi_retval.h"

/********************************
 * 			MACROS
 *******************************/

/**
*   @defgroup twi_ble_hal_group BLE HAL module return values
*   BLE HAL return values.
*   @{
*/
#define	TWI_ERR_BLE_HAL_INIT				(TWI_ERR_BLE_HAL_BASE - 1)
#define	TWI_ERR_BLE_HAL_CHAR_ADD			(TWI_ERR_BLE_HAL_BASE - 2)
#define	TWI_ERR_BLE_HAL_DIS					(TWI_ERR_BLE_HAL_BASE - 3)
#define	TWI_ERR_BLE_HAL_SET_ADV_DATA		(TWI_ERR_BLE_HAL_BASE - 4)
#define	TWI_ERR_BLE_HAL_STARTING_ADV		(TWI_ERR_BLE_HAL_BASE - 5)
#define	TWI_ERR_BLE_HAL_STOPPING_ADV		(TWI_ERR_BLE_HAL_BASE - 6)
#define	TWI_ERR_BLE_HAL_ADD_SVC				(TWI_ERR_BLE_HAL_BASE - 7)
#define	TWI_ERR_BLE_HAL_SND_PKT				(TWI_ERR_BLE_HAL_BASE - 8)
#define	TWI_ERR_BLE_HAL_SET_TX_PWR			(TWI_ERR_BLE_HAL_BASE - 9)
#define	TWI_ERR_BLE_HAL_SET_ADV_INT			(TWI_ERR_BLE_HAL_BASE - 10)
#define	TWI_ERR_BLE_HAL_NOT_SUPPORTED		(TWI_ERR_BLE_HAL_BASE - 11)
#define	TWI_ERR_BLE_HAL_START_SCAN			(TWI_ERR_BLE_HAL_BASE - 12)
#define	TWI_ERR_BLE_HAL_STOP_SCAN			(TWI_ERR_BLE_HAL_BASE - 13)
#define	TWI_ERR_BLE_HAL_CONNECT				(TWI_ERR_BLE_HAL_BASE - 14)
#define	TWI_ERR_BLE_HAL_CANCEL_CONN			(TWI_ERR_BLE_HAL_BASE - 15)
#define	TWI_ERR_BLE_HAL_HV_CONFIRM			(TWI_ERR_BLE_HAL_BASE - 16)
#define	TWI_ERR_BLE_HAL_INIT_DISCOVERY_MOD	(TWI_ERR_BLE_HAL_BASE - 17)
#define	TWI_ERR_BLE_HAL_REG_DISCOVERY		(TWI_ERR_BLE_HAL_BASE - 18)
#define	TWI_ERR_BLE_HAL_START_DISCOVERY		(TWI_ERR_BLE_HAL_BASE - 19)
#define TWI_ERR_BLE_HAL_INVALID_CONN_HANDLE	(TWI_ERR_BLE_HAL_BASE - 20)
#define TWI_ERR_BLE_HAL_ERR_INVALID_STATE	(TWI_ERR_BLE_HAL_BASE - 21)
#define TWI_ERR_BLE_HAL_NRF_BUSY			(TWI_ERR_BLE_HAL_BASE - 22)
#define	TWI_ERR_BLE_HAL_GET_BLE_ADDR		(TWI_ERR_BLE_HAL_BASE - 23)
#define TWI_ERR_BLE_HAL_REQ_ABORTED         (TWI_ERR_BLE_HAL_BASE - 24)
#define TWI_ERR_BLE_HAL_INVALID_ADDR		(TWI_ERR_BLE_HAL_BASE - 25)
#define TWI_ERR_BLE_HAL_NO_MEM				(TWI_ERR_BLE_HAL_BASE - 26)
#define TWI_ERR_BLE_HAL_TIMEOUT				(TWI_ERR_BLE_HAL_BASE - 27)
#define TWI_ERR_BLE_HAL_INVALID_ROLE		(TWI_ERR_BLE_HAL_BASE - 28)
#define TWI_ERR_BLE_HAL_SET_NAME         	(TWI_ERR_BLE_HAL_BASE - 29)
#define TWI_ERR_BLE_HAL_INV_TIMEOUT			(TWI_ERR_BLE_HAL_BASE - 30)
#define	TWI_ERR_BLE_HAL_NOT_ENOUGH_LEN_ADV	(TWI_ERR_BLE_HAL_BASE - 31)
#define	TWI_ERR_BLE_HAL_SET_CONN_PARAM		(TWI_ERR_BLE_HAL_BASE - 32)
#define TWI_ERR_BLE_HAL_UPDATE_PHY        	(TWI_ERR_BLE_HAL_BASE - 33)

/** @} */   /* twi_ble_hal_group */

/** @brief Convert mSec. to be in 0.625 mSec. Unit. */
#define MS_TO_625US(u16_ms)							(MUL1000(u16_ms) / 625)
#ifdef	BLE_HAL_LOG_ENABLE
#define CFG_DBG_PRINT
/* This is the macro that used in this module and it logs a prefix for this module at each log */
#define BLE_HAL_LOG(...)												TWI_LOGGER("[BLE]: "__VA_ARGS__)
#define BLE_HAL_LOG_ERR(...)				    				TWI_LOGGER_ERR("[BLE]:"__VA_ARGS__)
#define BLE_HAL_LOG_HEX(MSG, HEX_BUFFER, LEN)		TWI_DUMP_BUF("[BLE]: "MSG, HEX_BUFFER, LEN)
#else
/* This is an empty implementation to solve errors in case of we turning the logging off */
#define BLE_HAL_LOG(...)		
#define BLE_HAL_LOG_ERR(...)		
#define BLE_HAL_LOG_HEX(MSG, HEX_BUFFER, LEN)
#endif

#ifdef BLE_SCAN_LOGGER_ENABLE
#define BLE_SCAN_LOGGER(...)						BLE_HAL_LOG(__VA_ARGS__)
#define BLE_SCAN_LOGGER_HEX(MSG, HEX_BUFFER, LEN)	BLE_HAL_LOG_HEX(MSG, HEX_BUFFER, LEN)
#else
#define BLE_SCAN_LOGGER(...)
#define BLE_SCAN_LOGGER_HEX(...)
#endif


/*This error codes are for mapping from different platforms to Nordic to return the same error codes*/
#define TWI_CONN_PARAM_REQ_FAILED		(0x01)										/**@brief it returns non-zero in case of falied as NXP does **/
#define TWI_CONN_PARAM_REQ_SUCCESS		(0x00)		
#define TWI_CONN_PARAM_REQ_UNACCEPT_INT (0xCB)										/**@brief  unexpexted intialization error  **/
#define TWI_CONN_PARAM_REQ_COLLISION    (0xBA)										/**@brief  collision error  **/
#define TWI_CONN_PARAM_REQ_DISALLOWED   (0x43)										/**@brief  disallowed update*/ 
/********************************
 * 			Enumeration
 *******************************/

/********************************
 * 		Data Structures
 *******************************/

/*****************************************************************************************
 * 							Functions' Prototypes
 *****************************************************************************************/

/** @brief Application stack event handler */
 typedef	void	(*tpf_twi_ble_event_handler) (tstr_twi_ble_evt *pstr_ble_evt);
 
/**
*	@function	twi_ble_start_scan(tstr_twi_scan_params* pstr_scan_param)
*	@brief		This function starts a BLE scan.
*	@Param[in]	pstr_scan_param		Pointer to Structure holds scan parameters.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
 twi_s32 twi_ble_start_scan(tstr_twi_scan_params* pstr_scan_param);

/**
*	@function	twi_ble_stop_scan( void )
*	@brief		This function stops a BLE scan.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
 twi_s32 twi_ble_stop_scan( void );

 /**
*	@function	twi_ble_connect( twi_u8* pu8_ble_addr, tstr_twi_conn_params* pstr_conn_param)
*	@brief		This function establishes a BLE connection with the BLE address of the peripheral device.
*	@param[in]	pstr_ble_addr: 		a pointer to the BLE address of the peripheral device that central will connect to.
*	@param[in]	pstr_conn_param:	a pointer to the connection parameters.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
 twi_s32 twi_ble_connect( tstr_twi_ble_addr* pstr_ble_addr, tstr_twi_conn_params* pstr_conn_param);

 /**
 *	@function	twi_ble_cancel_connection( void )
 *	@brief		This function Cancels the current running connection procedure.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
 twi_s32 twi_ble_cancel_connection( void );

 /**
 *	@function	twi_ble_hv_confirm(twi_u16 u16_conn_handle, twi_u16 u16_handle)
 *	@brief		This function Sends the confirmation of indication to the peripheral device
 *  @param[in]  u16_conn_handle: The connection handle identifying the connection to perform this procedure on.
 *  @param[in]  u16_confirm_handle: The handle of the attribute in the indication.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
 twi_s32 twi_ble_hv_confirm(twi_u16 u16_conn_handle, twi_u16 u16_confirm_handle);

 /**
 *	@function	twi_ble_add_vs_uuid(tstr_twi_ble_uuid128* pstr_uuid128, twi_u8* pu8_uuid_type)
 *	@brief		This function is used to add a vendor specific UUID
 *  @param[in]   pstr_uuid128 :   Pointer to a Vendor Specific UUID.
 *  @param[out]  pu8_uuid_type :  Pointer to a type field corresponding to this UUID will be stored.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
 twi_s32 twi_ble_add_vs_uuid(tstr_twi_ble_uuid128* pstr_uuid128, twi_u8* pu8_uuid_type);

 /**
 *	@function	twi_ble_init_discovery_module(twi_u16  u16_uuid, twi_u8  u8_uuid_type)
 *	@brief		This function is used to initialize the discovery module that is used to discover services
 *				and chars in the peripheral device.
 * 	@param[in]   u16_uuid :   	UUID to search for while discovering services
 * 	@param[in ]  u8_uuid_type :  uuid type
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
 twi_s32 twi_ble_init_discovery_module(twi_u16  u16_uuid, twi_u8  u8_uuid_type);

 /**
 *	@function	twi_ble_start_discovery(twi_u16	u16_conn_handle)
 *	@brief		This function is used to start discover services and chars at the peripheral device.
 *	@param[in]	u16_conn_handle:	connection handle that discovery module will work on it.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
 twi_s32 twi_ble_start_discovery(twi_u16	u16_conn_handle);

 /**
*	@function	twi_ble_set_adv_data
*	@brief		This function sets the advertisement data.
*	@param[in]	pstr_adv_data		pointer to advertise data.
*	@param[in]	pstr_scan_resp 		pointer to Scan response data.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
 twi_s32 twi_ble_set_adv_data(tstr_twi_adv_data* pstr_adv_data, tstr_twi_adv_data* pstr_scan_resp);

 /**
*	@function	twi_ble_set_adv_data_direct
*	@brief		This function sets the advertisement data.
*	@info		To clear the advertising data and set it to a 0-length packet, simply provide a valid pointer (pu8_adv_payload/pu8_scan_res_payload) with its corresponding length set to 0.
*				The call will fail if pu8_adv_payload and pu8_scan_res_payload are both NULL since this would have no effect.
*	@param[in]	pu8_adv_payload	pointer to advertise data.
*	@info		Raw data to be placed in advertising packet. If NULL, no changes are made to the current advertising packet data.
*	@param[in]	u8_adv_len 		length of the advertising data.
*	@INFO		Data length for pu8_adv_payload. Max size: BLE_GAP_ADV_MAX_SIZE octets. Should be 0 if pu8_adv_payload is NULL, can be 0 if p_data is not NULL
*	@param[in]	pu8_scan_res_payload	pointer to scan response data.
*	@info		Raw data to be placed in scan response packet. If NULL, no changes are made to the current scan response packet data.
*	@param[in]	u8_scan_res_len 		length of the scan response data.
*	@INFO		Data length for pu8_scan_res_payload. Max size: BLE_GAP_ADV_MAX_SIZE octets. Should be 0 if pu8_scan_res_payload is NULL, can be 0 if p_data is not NULL.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_ble_set_adv_data_direct(twi_u8 * pu8_adv_payload, twi_u8 u8_adv_len, twi_u8 * pu8_scan_res_payload, twi_u8 u8_scan_res_len);

 /**
*	@function	twi_ble_start_adv
*	@brief		This function starts advertising of advertisement data.
*	@param[in]	enu_adv_type : 			advertise type.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
 twi_s32 twi_ble_start_adv (tenu_twi_ble_adv_types enu_adv_type);
 
 /**
*	@function	twi_ble_stop_adv
*	@brief		This function stops advertising.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
 twi_s32 twi_ble_stop_adv (void);

 /**
*	@function	twi_ble_set_adv_int
*	@brief		This function Sets the advertising interval.
*	@param[in]	u16_adv_int	:	the new advertising interval
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32	twi_ble_set_adv_int(twi_u16	u16_adv_int);

/**
*	@function	twi_ble_get_adv_int(twi_u16	*pu16_adv_int)
*	@brief		This function Gets the advertising interval.
*	@param[in]	u16_adv_int	:	return current advertising interval
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32	twi_ble_get_adv_int(twi_u16	*pu16_adv_int);


 /**
*	@function	twi_ble_disconnect
*	@brief		This function disconnects the node from the connecting device
*	@param[in]	u16_conn_handle	:	Connection Handle that will be disconnected from.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
 twi_s32 twi_ble_disconnect(twi_u16 u16_conn_handle);
 
/**
*	@function	twi_ble_gatts_sys_attr_set(twi_u8 const * const pu8_sys_attr_data, twi_u16 len, twi_u16 conn_handle)
*	@brief		This function sets system attributes
*	@param[in]	pu8_sys_attr_data :	pointer to the system attributes to be set.
*	@param[in]	len :	length of system attributes.
*	@param[in]	conn_handle :	connection handle.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/

 twi_s32 twi_ble_gatts_sys_attr_set(twi_u8 const * const pu8_sys_attr_data, twi_u16 len, twi_u16 conn_handle);
 
 /**
*	@function	twi_ble_gap_sec_info_reply(twi_u16 conn_handle)
*	@brief		This function Replies with GAP security information, it replies to a ::BLE_GAP_EVT_SEC_INFO_REQUEST 
*	@param[in]	conn_handle	:		Connection handle
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/

 twi_s32 twi_ble_gap_sec_info_reply(twi_u16 conn_handle);

/**
*	@function	twi_ble_add_services(tstr_twi_service *pstr_svc, twi_u8 u8_no_of_svc)
*	@brief		This function adds services and their characteristics.
*	@param[in]	pstr_svc :			pointer to array of structures, each holding services' data.
*	@param[in]	u8_no_of_svc :		Number of services to be added
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/ 
twi_s32	twi_ble_add_services(tstr_twi_service *pstr_svc, twi_u8 u8_no_of_svc);

/**
*	@function	twi_ble_gatt_write(twi_u16  u16_conn_handle, tstr_twi_gatt_write_params *pstr_write_params)
*	@brief		This function sends a given packet over a specific characteristic
*	@param[in]	u16_conn_handle :		Handle of the characteristic to be added to.
*	@param[in]	pstr_write_params :		Pointer to the structure holding parameters needed for write process.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/

twi_s32	twi_ble_gatt_write(twi_u16  u16_conn_handle, tstr_twi_gatt_write_params *pstr_write_params);
/**
*	@function	twi_ble_get_con_rssi
*	@brief		This function get the rssi of the current conn
*	@details	In Dialog, the Transmission Power is set to 0dbm and can not be changed PROGRAMMATICALLY
*	@param[in]	u16_conn_handle		Connection handle
*/
 
twi_s32	twi_ble_get_con_rssi(twi_u16 u16_conn_handle);
/**
*	@function	twi_ble_gap_tx_power_set(twi_s8 s8_tx_power)
*	@brief		This function sets transmission power
*	@param[in]	s8_tx_power		Transmission power needed to be set
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32	twi_ble_gap_tx_power_set(twi_s8 s8_tx_power);

/**
*	@function	twi_ble_get_tx_power
*	@brief		This function Gets the Tx power.
*	@param[out]	ps8_tx_pwr		Return Current Transmission power
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32	twi_ble_get_tx_power(twi_s8	*ps8_tx_pwr);

/**
*	@function		twi_ble_is_advertising(void)
*	@brief			This function gets advertising status
*   @return         returns ::TWI_TRUE 	In case advertising started, ::TWI_FALSE in case it's not advertising.
*/
twi_bool twi_ble_is_advertising(void);

/**
*	@function		twi_ble_is_scanning(void)
*	@brief			This function gets Scanning status
*	@return			returns ::TWI_TRUE In case Scanning started, ::TWI_FALSE in case it's not advertising.
*/
twi_bool twi_ble_is_scanning(void);

/**
*	@function	twi_ble_init(tpf_twi_ble_event_handler pf_ble_evt_handler)
*	@brief		This function initializes the BLE-HAL.
*	@param[in]	pf_ble_evt_handler :		A pointer to function needs to be returned to from the ble_event handler
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_ble_init(tpf_twi_ble_event_handler pf_ble_evt_handler);

/**
*	@function	twi_ble_set_dvc_name(const twi_u8* pu8_name)
*	@brief		This rename the device.
*/
twi_s32 twi_ble_set_dvc_name(const twi_u8* pu8_name);

/**
*	@function	twi_ble_deinit(void)
*	@brief		This function disables/de-initializes the BLE HAL.
*/
void twi_ble_deinit(void);

/**
 *	@brief		This function sets the Node's BLE Address
 *	@param[in]	enu_addr_type :			Type of the BLE MAC adrress
 *	@param[in]	pu8_ble_mac_addr :		A pointer to BLE MAC address needed to be set
 *	@param[in]	u8_ble_size :		    size of BLE MAC address
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_ble_set_ble_addr(tenu_twi_ble_addr_type enu_addr_type, twi_u8* pu8_ble_mac_addr,twi_u8 u8_ble_size);

/**
 *	@brief		This function gets the Node's BLE Address
 *	@param[in]	pstr_ble_addr :		A pointer to current returned BLE MAC address
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_ble_get_ble_addr(tstr_twi_ble_addr* pstr_ble_addr);


/**
 *	@brief		This function reads the value of specific characteristic.
  *	@param[in]	u16_conn_hdl :		connection handle.
 *	@param[in]	u16_valhdl 	 :		Value handle of the char
 *	@param[in]	u16_offset	 :		Offset to read from
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_ble_read_char(twi_u16 u16_conn_handle,twi_u16 u16_valhdl,twi_u16 u16_offset);

/**
 *	@brief		This function pairs with the given connected address.
 *	@param[in]	u16_conn_hdl :		connection handle.
 *	@param[in]	pstr_ble_addr:		Pointer to structure of BLE address of the connected device.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_ble_start_pairing(twi_u16 u16_conn_hdl, tstr_twi_ble_addr *pstr_ble_addr);

/**
 *	@brief		This function remove pairing of a device.
 *	@param[in]	pstr_ble_addr:		Pointer to structure of BLE address.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
void twi_ble_remove_pairing(tstr_twi_ble_addr *pstr_ble_addr);
/**
 *  @brief      This function sends an MTU request to the connected device on the given connection handle.
 *  @param[in]  u16_conn_handle:    Connection handle.
 *  @param[in]  u16_mtu_size:       MTU size to request.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_ble_send_mtu_request(twi_u16 u16_conn_handle, twi_u16 u16_mtu_size);


/**
 *  @brief      This function Gets the connected (PEER) BLE address according to the role.
 *  @param[in]  enu_role:		Connection Role, i.e. central role or peripheral role.
 *  @param[out] ppstr_peer_ble_addr: Connected peer address info.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_ble_get_connctd_peer_addr(tenu_twi_ble_role enu_role, tstr_twi_ble_addr **ppstr_peer_ble_addr);


/**
 *  @brief      This function Checks if the current ble address is bonded. 
 *  @param[in] pstr_ble_addr: Connected peer address info.
 *  @return     ::TWI_TRUE in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_ble_is_bonded(tstr_twi_ble_addr *pstr_ble_addr, twi_bool * pb_is_bonded);

/**
 *  @brief      This function set connection paramters.
 *  @param[in] 	u16_conn_hdl:				Connection handle.
 *  @param[in] 	pstr_twi_ble_conn_param:	Pointer to structure holds connection parameters.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_ble_set_connection_parameters(twi_u16 u16_conn_hdl,tstr_twi_conn_params * pstr_twi_ble_conn_param);

/**
 *	@function	twi_s32 twi_ble_load_settings(void)
 *	@brief		This function is used to load the BLE settings from the flash memory.
 *	@return     ::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_ble_load_settings(void);

/**
*	@function		twi_ble_is_connected(tenu_twi_ble_role enu_ble_role)
*	@brief			This function checks if ble role is connected 
*   @param[in] 	    enu_ble_role: BLE Role.
*	@return			returns ::TWI_TRUE In case ble is connected, ::TWI_FALSE in case it's not connected.
*/
twi_bool twi_ble_is_connected(tenu_twi_ble_role enu_ble_role);

/**
*  @brief      This function is a dispatcher function for BLE HAL which is needed only in WIN platform.
*  @warning		This should be called only on windows applications, as it needed to this specific platform only
*/
void twi_ble_hal_dispatch(void);

/** @} */   /*ble_group*/


#endif // TWI_BLE_HAL_H_
