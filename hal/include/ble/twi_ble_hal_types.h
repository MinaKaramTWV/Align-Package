/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_ble_hal_types.h
*   @brief      This file includes different types required for BLE.
*/

#ifndef _TWI_BLE_HAL_TYPES_H_
#define _TWI_BLE_HAL_TYPES_H_
/**
*   @defgroup ble_types_group TWI BLE HAL Types
*   This is the definition of TWI HAL for BLE Types.
*   @{
*/

//***********************************************************
/*- INCLUDES -----------------------------------------------*/
//***********************************************************
#include "twi_types.h"
#include "platform_defines.h"

/********************************
 * 			MACROS
 *******************************/

/**@brief	Invalid connection handle MACRO
 */
#define	TWI_BLE_CONN_HNDL_INVALID					PLATFORM_BLE_CONN_HANDLE_INVALID

/**
 *@brief	Advertising data type, Manufacturer Specific Data "0xFF" 
 */
#define	TWI_BLE_GAP_AD_TYPE_MANFCTR_SPECIFIC_DATA	PLATFORM_BLE_GAP_AD_TYPE_MANFCTR_SPECIFIC_DATA
#define	TWI_BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME		PLATFORM_BLE_GAP_AD_TYPE_COMPLETE_NAME


/** @brief	GAP Events Base*/
#define	TWI_BLE_GAP_EVT_BASE						PLATFORM_BLE_GAP_EVT_BASE

/**	@brief	UUID size */
#define UUID_SIZE							16

/**	@brief	Scan Response MAximum Length */
#define TWI_BLE_SCAN_RESP_MAX_LEN			31

/** @brief	GATT Handle Value operations (Client Characteristic Configuration Codes) */
#define TWI_BLE_GATT_DISABLE_NTF_IND	0x00

/** @brief	Handle for NOTIFICATION operation */
#define TWI_BLE_GATT_NOTIFICATION		0x01

/** @brief	Handle for INDICATIOIN operation */
#define	TWI_BLE_GATT_INDICATION			0x02

/** @brief	GATT Write Operations  */
#define TWI_BLE_GATT_OP_INVALID							PLATFORM_BLE_GATT_OP_INVALID
#define TWI_BLE_GATT_OP_WRITE_REQ						PLATFORM_BLE_GATT_OP_WRITE_REQ
#define	TWI_BLE_GATT_OP_WRITE_CMD						PLATFORM_BLE_GATT_OP_WRITE_CMD


/**@brief BLE Disconnect Reasons
 */
#define TWI_BLE_DISCONNECT_INVALID_CMD_PARAM	        PLATFORM_BLE_DISCON_INVALID_CMD_PARAMETERS
#define TWI_BLE_DISCONNECT_REMOTE_USER					PLATFORM_BLE_DISCON_REMOTE_USER
#define TWI_BLE_DISCONNECT_LOCAL_HOST					PLATFORM_BLE_DISCON_LOCAL_HOST
#define TWI_BLE_DISCONNECT_REMOTE_DEV_PWR_OFF			PLATFORM_BLE_DISCON_RMTE_DEV_PWR_OFF
#define TWI_BLE_DISCONNECT_REMOTE_DEV_LOW_RESOURCES		PLATFORM_BLE_DISCON_REMOTE_DEV_LOW_RES
#define TWI_BLE_DISCONNECT_TIMEOUT						PLATFORM_BLE_DISCON_TIMEOUT
#define TWI_BLE_DISCONNECT_FAILED_EST                   PLATFORM_BLE_DISCON_FAILED_EST

#define BLE_ADDR_SIZE									6

/** @brief	GAP Advertise types Base*/
#define TWI_TRGT_GAP_ADV_TYPE_BASE						PLATFORM_BLE_GAP_ADV_TYPE_ADV_IND

//***********************************************************
/*- ENUMS --------------------------------------------------*/
//***********************************************************


 /**
 *	@enum		tenu_twi_ble_addr_type
 *	@brief		enumerator of BLE Addr Type.
 */
 typedef enum
 {
	TWI_BLE_BLE_ADDR_INVALID,		
 	TWI_BLE_BLE_ADDR_RANDOM_STATIC,					/**< @brief RANDOM Static BLE Address.*/
 	TWI_BLE_BLE_ADDR_PUBLIC,						/**< @brief PUBLIC Address.*/
 } tenu_twi_ble_addr_type;
 
/**
 *	@enum		tenu_twi_ble_evts
 *	@brief		Enum that holds BLE events coming from BLE Stack
 */
typedef enum
{
    TWI_BLE_EVT_INVALID = 0,
	TWI_BLE_EVT_CONNECTED = 1,
	TWI_BLE_EVT_DISCONNECTED,
	TWI_BLE_EVT_WRITE,
	TWI_BLE_EVT_TX_COMPLETED,
	TWI_BLE_EVT_HVX_IND,
	TWI_BLE_EVT_HVX_NTF,
	TWI_BLE_EVT_HVC,
	TWI_BLE_EVT_READ_RSP,
	TWI_BLE_EVT_SEC_PARAMS_REQUEST,
	TWI_BLE_EVT_SYS_ATTR_MISSING,
	TWI_BLE_EVT_AUTH_STATUS,
	TWI_BLE_EVT_SEC_INFO_REQUEST,
	TWI_BLE_EVT_TIMEOUT,
	TWI_BLE_EVT_ADV_REPORT,
	TWI_BLE_EVT_WRITE_RSP,
    TWI_BLE_EVT_WRITE_RSP_ERR,
	TWI_BLE_EVT_PAIRING_SUCCESS,
	TWI_BLE_EVT_BOND_SUCCESS,
	TWI_BLE_EVT_DISCOVERY_SUCCESS,
	TWI_BLE_EVT_DISCOVERY_SRV_ERR,
	TWI_BLE_EVT_DISCOVERY_ERR,
	TWI_BLE_EVT_MTU_CHANGED,
    TWI_BLE_EVT_CONN_PARAM_UPDATED,
	TWI_BLE_EVT_CONN_RSSI,
	TWI_BLE_EVT_CONN_PARAM_REQUEST,
} tenu_twi_ble_evts;

 /**
 *	@enum		tenu_twi_ble_role
 *	@brief		enumerator of BLE Role.
 */
 typedef enum
 {
    TWI_BLE_ROLE_INVALID = 0,
 	TWI_BLE_ROLE_PERIPHERAL = 1,					/**< @brief This is the Peripheral role.*/
 	TWI_BLE_ROLE_CENTRAL							/**< @brief This is the Central role.*/
 }tenu_twi_ble_role;

 /**
 *	@enum		_tenu_twi_ble_timeout_type
 *	@brief		Enumerator that determine the type of Timeout Event
 */
 typedef enum
 {
	 TWI_BLE_TIMEOUT_ADV = 1,				/**< @brief Advertising Timeout Event.*/
     TWI_BLE_ABORTED_ADV,				    /**< @brief Advertising Timeout Event.*/
	 TWI_BLE_TIMEOUT_SCAN,					/**< @brief Scanning Timeout Event.*/
	 TWI_BLE_TIMEOUT_SEC_REQUEST,			/**< @brief Security request Timeout. */
     TWI_BLE_ABORTED_SCAN,					/**< @brief Scanning Abort Event.*/
	 TWI_BLE_TIMEOUT_CONN,					/**< @brief Establishing Connection Timeout Event.*/
     TWI_BLE_ABORTED_CONN,					/**< @brief Establishing Connection Timeout Event.*/
	 TWI_BLE_TIMEOUT_INVALID				/**< @brief Unsupported Timeout Event.*/
 }tenu_twi_ble_timeout_type;

 /**
 * @enum	   tenu_twi_ble_adv_types
 * @brief	   Enum that holds BLE advertising types
 */
typedef enum
{
	TWI_BLE_ADV_CONN   =   TWI_TRGT_GAP_ADV_TYPE_BASE,	   /**< @brief Connectable undirected. */
	TWI_BLE_ADV_CONN_DIRECT,							   /**< @brief Connectable directed. */
	TWI_BLE_ADV_SCAN,									   /**< @brief Scannable undirected. */
	TWI_BLE_ADV_NONCONN,								   /**< @brief Non connectable undirected. */
	TWI_BLE_ADV_UNCHANGED = 255,						   /**< @brief Advertise with the previous advertising type */
}tenu_twi_ble_adv_types;

/*advertise Complete Local Name if needed*/
  typedef enum tenu_adv_name
  	{
  		TWI_BLE_ADVDATA_NO_NAME,				/**< Include no device name in advertising data. */
  		TWI_BLE_ADVDATA_SHORT_NAME,				/**< Include short device name in advertising data. */
  		TWI_BLE_ADVDATA_FULL_NAME				/**< Include full device name in advertising data. */
  	}tenu_adv_name;
//***********************************************************
/*- STRUCTS AND UNIONS -------------------------------------*/
//***********************************************************
/**
 *	@struct		_tstr_twi_conn_params
 *	@brief		This structure holds connection parameters information
 */
 typedef struct
 {
 	twi_u16	u16_min_conn_interval_10xms;		/**< @brief Minimum Connection Interval in 1.25 ms units, see @ref BLE_GAP_CP_LIMITS.*/
 	twi_u16	u16_max_conn_interval_10xms;		/**< @brief Maximum Connection Interval in 1.25 ms units, see @ref BLE_GAP_CP_LIMITS.*/
 	twi_u16	u16_slave_latency;			/**< @brief Slave Latency in number of connection events, see @ref BLE_GAP_CP_LIMITS.*/
 	twi_u16	u16_superv_timeout_ms;			/**< @brief Connection Supervision Timeout in ms units, see @ref BLE_GAP_CP_LIMITS.*/
 } tstr_twi_conn_params;

/**
 *	@struct		tstr_twi_ble_on_connect
 *	@brief		Structure holds parameters of the coming BLE on_connect event
 */

typedef struct
{
	twi_u8					au8_bluetooth_addr	[BLE_ADDR_SIZE];			/**< bluetooth address of the device.*/
	tenu_twi_ble_role		twi_ble_role;
	tstr_twi_conn_params	str_twi_ble_conn_param;
}tstr_twi_ble_on_connect;

 /**
  *	@struct		_tstr_twi_ble_evt
  *	@brief		Structure holds parameters of the coming BLE event
  */

 typedef	struct
 {
 	tenu_twi_ble_evts 	enu_evt;			/**< @brief BLE event in progress */
 	tenu_twi_ble_role	enu_conn_type;		/**< @brief Connection type */
 	twi_u16				u16_len;			/**< @brief length of the data sent */
 	twi_u16				u16_event_handle;	/**< @brief handle of the characteristic or service that needs data */
 	twi_u16				u16_conn_hndl;		/**< @brief Connection handle */
	twi_u8				*pu8_data;			/**< @brief data attached to the BLE event if any */
 } tstr_twi_ble_evt;

 /**
  ** @Struct	_tstr_twi_perm
  ** @brief		This Structure holds the permissions of the characteristic
  */
 //lint -save -e46
 // we can't update that is the communication protocol
  typedef struct
  {
  	twi_u8 	u8_read			 :1;			/**< @brief READ permission, to enable reading characteristic */
 	twi_u8 	u8_write		 :1;			/**< @brief WRITE permission, to enable writing to characteristic */
    twi_u8  u8_write_wo_resp :1;            /**< @brief WRITE WITHOUT RESPONSE permission, to enable writing to characteristic without response */
 	twi_u8 	u8_indicate		 :1;			/**< @brief INDICATE permission, to enable Indicate-able for characteristic */
 	twi_u8 	u8_notify		 :1;			/**< @brief NOTIFY permission, to enable Notifiable characteristic */
  }tstr_twi_perm;
 //lint -restore
 /**
  ** @struct			    _tstr_twi_gatts_char_handels
  ** @brief					This structure holds the description of the characteristics
  **
  */
 typedef struct
 {
   twi_u16           u16_value_handle;			/**< @brief Handle to the characteristic value. */
   twi_u16           u16_user_desc_handle;   	/**< @brief Handle to the User Description descriptor, or ::TWI_BLE_GATT_HANDLE_INVALID if not present. */
   twi_u16           u16_cccd_handle;        	/**< @brief Handle to the Client Characteristic Configuration Descriptor, or ::TWI_BLE_GATT_HANDLE_INVALID if not present. */
   twi_u16           u16_sccd_handle;        	/**< @brief Handle to the Server Characteristic Configuration Descriptor, or ::TWI_BLE_GATT_HANDLE_INVALID if not present. */
 } tstr_twi_gatts_char_handels;

 /**
  ** @struct			        _tstr_twi_char
  ** @brief					This structure holds the descriptionof the characteristic
  **
  */
  typedef struct
  {
 	twi_u8							u8_uuid_type;			/**< @brief Type of characteristic's UUID */
 	twi_u16							u16_uuid;				/**< @brief Characteristic's UUID */
 	tstr_twi_gatts_char_handels		*str_char_handles;		/**< @brief Pointer to a structure holding characteristic's handles' data */
 	tstr_twi_perm					str_char_perm;			/**< @brief Pointer to the characteristic's permissions' structure */
 	twi_u16							u16_init_length;     	/**< @brief Char initial length in bytes */
 	twi_u16							u16_max_length;			/**< @brief Char max length in bytes */
 } tstr_twi_char;

 /**
  ** @struct		_tstr_twi_service
  ** @brief		This structure holds the description of the service
  **
  */
  typedef struct
  {
 	twi_u8				u8_no_of_char;				/**< @brief Number of characteristics in service. */
	twi_u16				u16_uuid;					/**< @brief 16-bit service UUID */
 	twi_u8				*pu8_uuid_type;				/**< @brief Service's UUID type. */
 	twi_u8				*pu8_128uuid;
 	twi_u16				*pu16_svc_handle;			/**< @brief Service Handle. */
 	tstr_twi_char		*pstr_chars;				/**< @brief Pointer to array of structures, each hold a single characteristic's parameters. */
  }tstr_twi_service;

  /**
   *	@struct 	tstr_twi_manu_data
   *	@brief		structure used to the manufacturer(_manu_) specific data for the beacon
   */
  typedef struct
  {
  	twi_u16			u16_company_identifier; 		/**< @brief Unsigned company identifier. */
  	twi_u16			u16_manu_data_sz;				/**< @brief length of the beacon data. */
  	twi_u8 	*pu8_manu_data;					/**< @brief Pointer to the beacon data. */
  } tstr_twi_manu_data;

  /**
  *	@struct 	_tstr_twi_adv_data
  *	@brief		structure used to define advertising data either for advertise packet or scan response
  */
  typedef struct
  {
  	/*advertise Complete Local Name if needed*/
    tenu_adv_name		enu_adv_name_type;				/**< @brief type of name if No Name, short name or Full name.*/

  	/*advertise Manufacturer Specific Data if needed*/
  	twi_u8				u8_manu_adv_data_size;			/**< @brief Size of the manufacturer advertise data.*/

  	/*advertise Incomplete List of 16-bit Service Class UUIDs if needed*/
  	twi_u8				u8_incomplete_16uuid_size;		/**< @brief Size of the Incomplete List of 16-bit Service advertise data.*/

  	/*advertise Complete List of 16-bit Service Class UUIDs if needed*/
  	twi_u8				u8_complete_16uuid_size;		/**< @brief Size of the Complete List of 16-bit Service advertise data.*/

  	/*advertise Incomplete List of 128-bit Service Class UUIDs if needed*/
	twi_u8				u8_incomplete_128uuid_size;		/**< @brief Size of the Incomplete List of 16-bit Service advertise data.*/

	/*advertise Complete List of 128-bit Service Class UUIDs if needed*/
	twi_u8	u8_complete_128uuid_size;		/**< @brief Size of the Complete List of 16-bit Service advertise data.*/

  	twi_const twi_u8	*pu8_device_name;				/**< @brief Pointer to the name of device.*/

  	twi_u8				*pu8_manu_adv_data;				/**< @brief Pointer to the manufacturer advertise data.*/

  	twi_u8				*pu8_incomplete_16uuid;			/**< @brief Pointer to the Incomplete List of 16-bit Service advertise data.*/

  	twi_u8				*pu8_complete_16uuid;			/**< @brief Pointer to the Complete List of 16-bit Service advertise data.*/

  	twi_u8				*pu8_complete_128uuid;			/**< @brief Pointer to the Complete List of 128-bit Service advertise data.*/

  	twi_u8				*pu8_incomplete_128uuid;		/**< @brief Pointer to the Complete List of 128-bit Service advertise data.*/
  }tstr_twi_adv_data;

  /**
   *@struct	_tstr_twi_gatts_write_params.
   *@brief	GATT HVx (write) parameters.
   */
 typedef struct
 {
 	tenu_twi_ble_role	enu_role;			/**< @brief Role that indicate either to use on gatts or gattc.*/
 	twi_u16				u16_handle;			/**< @brief Characteristic's Value Handle. */
 	twi_u16				u16_srvc_handle;	/**< @brief Handler of the Service that contains the Characteristic defined by u16_handle. */
 	twi_u8        		u8_type;			/**< @brief Indication or Notification. */
 	twi_u16      		*pu16_len;			/**< @brief Length in bytes to be written. */
 	twi_u8        		*pu8_data;			/**< @brief Actual data content, use NULL to use the current attribute value. */
 } tstr_twi_gatt_write_params;

/**
 *	@struct		_tstr_twi_scan_params
 *	@brief		This structure holds scan information
 */
 typedef struct
 {
 	twi_u16	u16_scan_interval;		/**< @brief Scan interval. */
 	twi_u16	u16_scan_window;		/**< @brief Scan window. */
 	twi_u32	u32_timeout_ms;			/**< @brief Scan timeout between 0x0001 and 0x3FFF in milli seconds, 0x0000 disables timeout.*/
 	twi_bool b_active_scan;
 } tstr_twi_scan_params;

 /**
  *	@struct		_tstr_twi_ble_addr
  *	@brief		This structure holds the BLE address of the peripheral device
  */
 typedef struct
 {
 	twi_u8*	pu8_ble_address;				/**< @brief This is a pointer to the BLE address type, it's size BLE_ADDR_SIZE.*/
 	twi_u8	u8_address_type;				/**< @brief This is BLE address type.*/
 }tstr_twi_ble_addr;

 /**
  *	@struct		_tstr_twi_ble_adv_data
  *	@brief		This structure holds advertising event data
  */
 //lint -save -e46
 //can't be fixed now
 typedef struct
 {
 	tstr_twi_ble_addr*	pstr_ble_addr;
 	twi_s8				s8_rssi;
 	twi_u8				scan_rsp:1;
 	twi_u8				data_len:5;
#if defined(nordic_sdk_16_0_0)
 	ble_gap_adv_report_type_t type;
#else
 	twi_u8				type:2;
#endif
 	twi_u8*				pu8_data;
 }tstr_twi_ble_adv_data;
 //lint -restore

 /**
  *	@struct		_tstr_twi_ble_uuid128
  *	@brief		128 bit UUID values.
  */
 typedef struct
 {
     twi_u8			 au8_uuid128[16]; /**< @brief Little-Endian UUID bytes. */
 } tstr_twi_ble_uuid128;

 /** @} */   /*ble_types_group*/

#ifdef BLE_PERIPHERAL_ROLE_SUPPORTED
	typedef enum
	{
		TWI_BLE_ADV_TYPE = 0x02,
		TWI_BLE_SCAN_RSP_TYPE,
	}tenu_adv_or_scanrsp;
#endif


#endif /* _TWI_BLE_HAL_TYPES_H_ */
