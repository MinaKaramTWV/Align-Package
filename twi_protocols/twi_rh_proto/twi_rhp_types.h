/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file					twi_rhp_types.h
 ** @brief					This file includes the types for the Remote HAL Protocol
 */

#ifndef TWI_RHP_TYPES_H_
#define TWI_RHP_TYPES_H_

/** @defgroup TWI_RHP_TYPES_group TWI RHP Types.
 * It contains structures and Enums that are used by RHP layer
 * @{
 */
 
/***********************************************************/
/*- INCLUDES ----------------------------------------------*/
/***********************************************************/

#include "twi_common.h"
#include "twi_stack_types.h"
#include "twi_fifo.h"
#include "timer_mgmt.h"
#include "twi_destinations.h"

#ifdef TWI_RHP_HW_WIFI
#include "twi_wifi_common.h"
#endif 

#ifdef TWI_RHP_REPORT
#include "twi_rhp_rprtng_util_cmn.h"
#endif

#ifdef TWI_VITA_SDK
#include "twi_vita_sdk_app_events.h"
#else
#include "twi_sdk_app_events.h"
#endif
/*-***********************************************************/
/*- Global MACROS -------------------------------------------*/
/*-***********************************************************/

/**
*   @defgroup twi_rhp_group RHP module return values
*   @{
*/
#define TWI_RHP_HW_INIT_ERROR										(TWI_RHP_ERR_BASE - 1)
#define TWI_RHP_TRIGGERS_INIT_ERROR									(TWI_RHP_ERR_BASE - 2)
#define TWI_RHP_LOGGER_INIT_ERROR									(TWI_RHP_ERR_BASE - 3)
#define TWI_RHP_STATUS_INIT_ERROR									(TWI_RHP_ERR_BASE - 4)
#define TWI_RHP_INVALID_FEATURE_ERROR								(TWI_RHP_ERR_BASE - 5)
#define TWI_RHP_INVALID_ATTRIB_ERROR								(TWI_RHP_ERR_BASE - 6)
#define TWI_RHP_REGISTER_HW_INT_ERROR								(TWI_RHP_ERR_BASE - 7)
#define TWI_RHP_READ_HW_ERROR										(TWI_RHP_ERR_BASE - 8)
#define TWI_RHP_WRITE_HW_ERROR										(TWI_RHP_ERR_BASE - 9)
#define TWI_RHP_ERROR_PERMISSIONS									(TWI_RHP_ERR_BASE - 10)
#define TWI_RHP_ERROR_CMD_FORMAT									(TWI_RHP_ERR_BASE - 11)
#define TWI_RHP_ERROR_INVALID_VALUE									(TWI_RHP_ERR_BASE - 12)
#define TWI_RHP_ERROR_INVALID_CMD									(TWI_RHP_ERR_BASE - 13)
#define TWI_RHP_ERROR_EXECUTE_UNKNOWN_CMD							(TWI_RHP_ERR_BASE - 14)
#define TWI_RHP_ERROR_NO_STATUS_MSG									(TWI_RHP_ERR_BASE - 15)
#define TWI_RHP_ERROR_NOT_CLEAR_TO_SEND								(TWI_RHP_ERR_BASE - 16)
#define TWI_RHP_ERROR_NOT_READY_TO_SEND								(TWI_RHP_ERR_BASE - 17)
#define TWI_RHP_ERROR_EXECUTE_UNALLOWED_CMD							(TWI_RHP_ERR_BASE - 18)
#define TWI_RHP_ERROR_BUSY											(TWI_RHP_ERR_BASE - 19)
#define TWI_RHP_ERROR_TRIGGERS_EXCEED_LIMIT							(TWI_RHP_ERR_BASE - 20)
#define TWI_RHP_ERROR_INVALID_SAVE_BUF   							(TWI_RHP_ERR_BASE - 21)
#define TWI_ERROR_INVALID_INDEX										(TWI_RHP_ERR_BASE - 22)

/** @} */


#define TWI_RHP_APP_RESERVED_TRIGGER_NUM							(255)			/**< @brief This trigger number is reserved to the application "product" */
		
#define TWI_RHP_HW_ACC_SENSOR_NO_NOTIFY								0x00
#define TWI_RHP_HW_ACC_SENSOR_MOVEMENT_NOTIFY						0x01
#define TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY					0x02
#define TWI_RHP_HW_ACC_SENSOR_FREE_FALL_NOTIFY						0x04
#define TWI_RHP_HW_ACC_SENSOR_SHOCK_NOTIFY							0x08
#if defined (TWI_ACC_ENABLE_FIFO_CONTENT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
#define TWI_RHP_HW_ACC_SENSOR_FIFO_BUF_SIZE							96
#endif

#define RHP_FEAT_ATTR_VALUE(pstr_feature, u8_feature_attr_indx)		((pstr_feature)->apstr_logger_attributes[u8_feature_attr_indx]->pstr_value)
#define RHP_LOG_ATTR_VALUE(pstr_logger, enu_logger_attr_indx)		((pstr_logger)->apstr_logger_attributes[(twi_u8)enu_logger_attr_indx]->pstr_value)
#define RHP_LOG_ATTR(pstr_logger, enu_logger_attr_indx)		        ((pstr_logger)->apstr_logger_attributes[(twi_u8)enu_logger_attr_indx])
#define RHP_TRIG_ATTR_VALUE(pstr_trigger, enu_trigger_attr_indx)	((pstr_trigger)->apstr_trigger_attributes[(twi_u8)enu_trigger_attr_indx]->pstr_value)
#define RHP_STATS_ATTR_VALUE(pstr_status, enu_status_attribute)		((pstr_status)->apstr_status_attributes[(twi_u8)enu_status_attribute]->pstr_value)
#define RHP_RPRTNG_ATTR_VALUE(pstr_report, enu_report_attr_indx)	((pstr_report)->apstr_report_attributes[(twi_u8)enu_report_attr_indx]->pstr_value)
#define RHP_RPRTNG_ATTR(pstr_report, enu_report_attr_indx)	((pstr_report)->apstr_report_attributes[(twi_u8)enu_report_attr_indx])


/* MACROS RELATED TO SCANNING USING RHP */
#define	DVC_BLE_ADDR_SIZE											6				/**< @brief This is the size of BLE address of any device.*/
#define	DVC_BLE_ADDR_TYPE_SIZE										1				/**< @brief This is the size of BLE address Type of any device.*/
#define	DVC_TWI_ID_SIZE												4
#define	PROFILE_ID_SIZE												2
#define	DVC_UUID16_SIZE												2
#define	DVC_RSSI_SIZE												1
#define	DVC_UUID128_SIZE											16
#define	DVC_TYPE_SIZE												1
#define	DVC_LOCK_SIZE												1

/*
 * HEX array that will be the Value of SCAN_RESULT array.
 * ___________________________________________________________________________________________________________________________________________________________________________________________________
 * 	0	|	1	|	2	|	3	|	4	|	5	|		6		|	7	|	8	|	9	|	10	|	11	|	12	|	13	|	14	|	15		|	16 		   |	 17		 |	 33		 |
 * ___________________________________________________________________________________________________________________________________________________________________________________________________
 * <----------------BLE ADDRESS-------------------->|<--ADDR TYPE-->|<-------- TWI ID ------------->|<-PROFILE ID-->|<- SRVC UUID ->|<-- RSSI-->|<--- Type --->|<-- 16 byte UUID-->   |<-- Lock-->   |
 *
 */
#define	DVC_BLE_ADDR_BYTE_NUM										0				/**< @brief This is the Byte number of BLE-ADDRESS in the Raw data array of the SCAN_RESULT attribute Value .*/
#define	DVC_BLE_ADDR_TYPE_BYTE_NUM									6				/**< @brief This is the Byte number of BLE-ADDRESS type in the Raw data array of the SCAN_RESULT attribute Value .*/
#define	DVC_TWI_ID_BYTE_NUM											7				/**< @brief This is the Byte number of TWI_ID in the Raw data array of the SCAN_RESULT attribute Value .*/
#define	PROFILE_ID_BYTE_NUM											11				/**< @brief This is the Byte number of PROFILE_ID in the Raw data array of the SCAN_RESULT attribute Value .*/
#define	DVC_SRVC_UUID16_BYTE_NUM									13				/**< @brief This is the Byte number of Service UUID in the Raw data array of the SCAN_RESULT attribute Value .*/
#define	DVC_RSSI_BYTE_NUM											15				/**< @brief This is the Byte number of RSSI in the Raw data array of the SCAN_RESULT attribute Value .*/
#define	DVC_TYPE_BYTE_NUM											16				/**< @brief This is the Byte number of device type in the Raw data array of the SCAN_RESULT attribute Value .*/
#define	DVC_UUID128_BYTE_NUM										17				/**< @brief This is the Byte number of uuid128 in the Raw data array of the SCAN_RESULT attribute Value .*/

/*lock in the buffer is set directly after tstr_scannedd_ble_dvc, so its index equal sum of buffer elements size*/
#define	DVC_BEACON_LOCK_BYTE_NUM									(								\
																			DVC_BLE_ADDR_SIZE + 	 \
																			DVC_BLE_ADDR_TYPE_SIZE + \
																			DVC_TWI_ID_SIZE +		 \
																			PROFILE_ID_SIZE +		 \
																			DVC_UUID16_SIZE + 		 \
																			DVC_RSSI_SIZE +			 \
																			DVC_TYPE_SIZE +			 \
																			DVC_UUID128_SIZE  		 \
																	)


#define BLE_CONNECT_ADDRESS_SIZE									(DVC_BLE_ADDR_SIZE + DVC_BLE_ADDR_TYPE_SIZE)

#define	RHP_INV_PRNT_IDX											(-1)			/**< @brief This is the invalid parent number,
																						this is used to indicate that the command doesn't contain feature number.*/
#define	RHP_INV_ATTR_IDX											(-1)			/**< @brief This is the invalid attribute number,
																						this is used to indicate that the command doesn't contain attribute number.*/

#define RHP_INVALID_TIMESTAMP										(0xFFFFFFFF)	/**< @brief Invalid Timestamp number.*/

#define GW_BEACON_UUID												0xF2, 0xD6, 0x1D, 0x58, \
																	0xD1, 0x50, 0x4E, 0xFA, \
																	0x96, 0xF6, 0x32, 0x36, \
																	0xE4, 0x73, 0xD0, 0x0B			/**< @brief This is the GW beacon UUID.*/

#define TWI_RHP_RESERVED_FEATURE_NUM								(0xFF)
#define TWI_RHP_OTA_FEATRE_NUM                                      (0xFE)

#define UTC_TIME_RQST_VAL											0xFFFFFFFF	/*this value used to indicate that time handler need to request UTC time*/

#define SDK_OP_CODE_LOC												(0)

#define SDK_DATA_LOC												  (1)

#define SDK_OP_CODE_SIZE                      (1)

#define TWI_ID_SIZE														(4)

/*Used to skip initialization of a logger without rearranging remaining Loggers */
#define SKIP_LOGGER_INIT_TAG                             ((void *)0xFFFFFFFE)
/*-***********************************************************/
/*- ENUMERTAIONS --------------------------------------------*/
/*-***********************************************************/

/*-**********************/
/*- VALUE --------------*/
/*-**********************/

/**
*	@enum		tenu_value_type
*	@brief		enumeration that represents attributes' value-types.
*/
typedef enum
{
	BOOLEAN,		/**< @brief Boolean Value */
	U8,				/**< @brief 8-bit unsigned Value */
	PU8,			/**< @brief pointer to 8-bit unsigned Value */
	S8,				/**< @brief 8-bit signed Value*/
	PS8,			/**< @brief pointer to 8-bit signed Value*/
	U16,			/**< @brief 16-bit unsigned Value*/
	PU16,			/**< @brief pointer to 16-bit unsigned Value*/
	S16,			/**< @brief 16-bit signed Value*/
	PS16,			/**< @brief pointer to 16-bit signed Value*/
	U32,			/**< @brief 32-bit unsigned Value*/
	PU32,			/**< @brief pointer to 32-bit unsigned Value*/
	S32,			/**< @brief 32-bit unsigned Value*/
	PS32,			/**< @brief pointer to 32-bit unsigned Value*/
	U64,			/**< @brief 64-bit unsigned Value*/
	PU64,			/**< @brief pointer to 64-bit unsigned Value*/
	S64,			/**< @brief 64-bit signed Value*/
	PS64,			/**< @brief pointer to 64-bit signed Value*/
	FLOAT,			/**< @brief FLOAT Value*/
	HEX				/**< @brief HEX Value*/
} tenu_value_type;

/**
*	@enum		_tenu_compare_type
*	@brief		enumeration that represents attributes' comparison-types.
*/
typedef enum
{
	GT,			/**< @brief Greater than */
	ET,			/**< @brief Equal to */
	LT,			/**< @brief Less than */
	GTOET,		/**< @brief Greater than or Equal to*/
	NET,		/**< @brief Not equal to*/
	LSOET,		/**< @brief Less than or equal to */
	NUM_COMPARE /**< @brief Number of compare types */
} tenu_compare_type;

/**
*	@enum		_tenu_computation_type
*	@brief		enumeration that represents computation that can be done on attributes' values.
*/
typedef enum
{

	ADD, 			/**< @brief Add two values */
	SUB, 			/**< @brief Subtract the second value from the first */
	MUL, 			/**< @brief Multiply two values */
	MOD, 			/**< @brief First value % the second value */
	NUM_COMPUTE, 	/**< @brief Number of computation types */
	NO_COMPUTE 		/**< @brief Invalid computation value */
} tenu_computation_type;

/*-**********************/
/*- HARDWARE -----------*/
/*-**********************/

/**
*	@enum		tenu_type
*	@brief		enumeration that represents HW types.
*/
typedef enum
{
	DIGITAL,
	ANALOG,
	PERIPHERAL,
	SENSOR,
	WAKE_UP_SENSOR,
	ACTUATOR,
	WAKE_UP_ACTUATOR,
	ABSTRACT,
	TYPE_INVALID
} tenu_type;


/**
*	@enum		tenu_subtype
*	@brief		enumeration that represents HW sub-types.
*/
typedef enum
{
	/* Digital Start */
#ifdef TWI_RHP_HW_DIGITAL
	TWI_RHP_SUBTYPE_GPIO,
	GPIO_PULL,
	LED,
	PBTN,
	PWM,
#endif

	/* Digital End */

	/* Analogue Start */
#ifdef TWI_RHP_HW_ADC
	ADC,
#endif
#if 0
	DAC,
#endif
	/* Analogue End */

	/* Peripheral Start */
#if 0
	SPI,
	UART,
	I2C,
	SPIS,
	MEMORY,
#endif

#ifdef TWI_RHP_HW_WIFI
	WIFI_START_SCAN,
	WIFI_SCAN_RESULT,
	WIFI_CONN_OPER,
	WIFI_CONNECT_STATUS,
	WIFI_SSID,
	WIFI_PSWD,
	WIFI_SEC_TYPE,
	WIFI_SIGNAL_STRENGTH,
	WIFI_PWR_MODE,
	WIFI_PROVISION_STATUS,
#endif

	/* BLE */
#ifdef TWI_RHP_HW_BLE
	BLE_START_STOP_ADV,
#if defined(TWI_BLE_ENABLE_ADV_INTERVAL) || defined (TWI_HW_BLE_FULL_FUNCTION)
	BLE_ADV_INTERVAL,
#endif
#if defined(TWI_BLE_ENABLE_TX_POWER_HANDLER) || defined (TWI_HW_BLE_FULL_FUNCTION) 
	BLE_TX_PWR,
#endif
#if defined(TWI_BLE_ENABLE_APP_DATA_HANDLERS) || defined (TWI_HW_BLE_FULL_FUNCTION) 
	BLE_APP_DATA,
#endif
#if defined(BLE_CENTRAL_ROLE_SUPPORTED) || defined (TWI_HW_BLE_FULL_FUNCTION) 
	BLE_SCAN_OPERATION,
	BLE_SCAN_RESULT,
	BLE_CENTRAL_CONNECT_ADDRESS,
	BLE_CENTRAL_CONNECT_OPERATION,
	BLE_CENTRAL_CONNECT_STATUS,
#endif 
#if defined(TWI_BLE_PER_CONN_OPE) || defined (TWI_HW_BLE_FULL_FUNCTION) 
	BLE_PERIPHERAL_CONNECT_OPERATION,
#endif
	BLE_PERIPHERAL_CONNECT_STATUS,
#if defined(ADVERTISE_WITHOUT_AML_AND_OPP) || defined (TWI_HW_BLE_FULL_FUNCTION)
    BLE_PERIPHERAL_ADV_DATA,
#endif
#if (defined(ADV_PKT_COUNTER_ENABLED) && !defined(ADVERTISE_WITHOUT_AML_AND_OPP)) || defined (TWI_HW_BLE_FULL_FUNCTION)
	BLE_PERIPHERAL_ADV_PKT_COUNT,
#endif	
	BLE_ALWAYS_CONNECTED_MODE,
#if defined(TWI_CONN_PARAM_MGMT) || defined (TWI_HW_BLE_FULL_FUNCTION)	
	BLE_REQUEST_CONN_PARAM,
	BLE_CURRENT_CONN_PARAM,
#endif
#endif
#ifdef TWI_RHP_HW_NFC
	NFC_SPI_READ_WRITE,
	NFC_INTERNAL_COMMAND,
#endif
#ifdef TWI_RHP_HW_NFC_READER
	NFC_READER_READ_WRITE,
	NFC_READER_POLL,
	NFC_READER_READ_ID,
#endif


	/* Peripheral End */


	/* Sensor Start */
#ifdef TWI_RHP_HW_TEMP_SENSOR
	TEMP_SENSOR,
#endif

#ifdef TWI_RHP_HW_FORCE_SENSOR
	FORCE_SENSOR,
#endif

#ifdef TWI_RHP_HW_HUMIDITY_SENSOR
	HUMIDITY_SENSOR,
#endif

#ifdef TWI_RHP_HW_BAT_SENSOR
	BAT_SENSOR,
#endif
#ifdef TWI_RHP_HW_LIGHT_SENSOR
	LIGHT_SENSOR,
#endif
#ifdef TWI_RHP_HW_PRESSURE_SENSOR
	PRESSURE_SENSOR,
	PRESSURE_SENSOR_CALIB_ERR,
	PRESSURE_SENSOR_CALIB_REF,
#endif
		/*	Accelerometer subtypes 	*/
#ifdef TWI_RHP_HW_ACC_SENSOR
	/*	Accelerometer subtypes 	*/
	#if defined (TWI_ACC_ENABLE_NOTIFICATION_CAUSE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
	ACC_SENSOR_NOTIFICATIONS_CAUSE,
	#endif
	#if defined (TWI_ACC_ENABLE_NOTIFICATION_REASON_DETECT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
	ACC_SENSOR_NOTIFICATIONS,
	#endif
    #if defined (TWI_ACC_ENABLE_CONFIGRATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
	ACC_SENSOR_CONFIGRATION,
    #endif
	#if defined (TWI_ACC_ENABLE_CONTROL_ODR_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
	ACC_SENSOR_ODR,  
	#endif
	#if defined (TWI_ACC_ENABLE_CONTROL_SENSITIVITY_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
	ACC_SENSOR_SENSITIVITY,
	#endif
	#if defined (TWI_ACC_ENABLE_CONTROL_MOVE_DURATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
	ACC_SENSOR_MOVEMENT_DURATION_SEC,
	#endif
	#if defined (TWI_ACC_ENABLE_CONTROL_SHOCK_LEVEL_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
	ACC_SENSOR_SHOCK_LEVEL,
	#endif
	#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
	ACC_SENSOR_NOT_MOVED_PERIOD_MS,	
	#endif
	#if defined (TWI_ACC_ENABLE_3_AXSIS_ACCELERATION_READING_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
	ACC_SENSOR_X_ACC,
	ACC_SENSOR_Y_ACC,
	ACC_SENSOR_Z_ACC,
	#endif
	#if defined (TWI_ACC_ENABLE_FIFO_CONTENT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
	ACC_SENSOR_FIFO_CONTENT,
	ACC_SENSOR_NUM_OF_FIFO_LEVELS,
	#endif
	#if defined (TWI_ACC_ENABLE_TILT_ANGLE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
	ACC_SENSOR_TILT_ANGLE,
	#endif
#endif

#ifdef TWI_RHP_HW_PH_SENSOR
	PH_SENSOR,
#endif

#if 0
	CUSTOM,
#endif
	/* Sensor End */

	/* Actuator Start */
		/* CUST1 */
#ifdef TWI_RHP_HW_CUST1
	CUST1_ATT_0_0,
	CUST1_ATT_0_1,
	CUST1_ATT_0_2,
	CUST1_ATT_0_3,
	CUST1_ATT_0_4,
	CUST1_ATT_0_5,
	CUST1_ATT_0_6,
#if defined(TWI_RHP_HW_CUST1_PRODUCT1)|| defined(TWI_RHP_HW_CUST1_PRODUCT3)
	CUST1_ATT_0_7,
#endif
#ifdef TWI_RHP_HW_CUST1_PRODUCT2
	CUST1_ATT_2_0,  /*history buffer idx and length */
	CUST1_ATT_2_1,		/*history buffer data */
	CUST1_ATT_3_0,
	CUST1_ATT_3_1,
	CUST1_ATT_3_2,
	CUST1_ATT_3_3,
	CUST1_ATT_3_4,
	CUST1_ATT_3_5,
    CUST1_ATT_3_6,
    CUST1_ATT_3_7,
	CUST1_ATT_3_8,
    CUST1_ATT_3_9,
    CUST1_ATT_3_10,
    CUST1_ATT_3_11,
	CUST1_ATT_4_0,
    CUST1_ATT_4_1,
    CUST1_ATT_4_2,
    CUST1_ATT_4_3,
#endif
#endif

		/*	E_PAPER subtypes */
#ifdef TWI_RHP_HW_EPD
	EPD_RLE_IMG_SAVE,
	EPD_MAX_FRAGMENT_LENGTH,
	EPD_WRITTING_ERROR,
	EPD_PANEL_UPDATE,
	EPD_PANEL_UPDATE_STATUS,
	EPD_STORAGE_FLUSH,
#endif
	/* Actuator End */

/* Abstract Start */
#ifdef TWI_RHP_HW_TIME
	TIME,
#endif
	/* Abstract End */
#ifdef TWI_RHP_HW_SI4455
	SUBGHZ_SCAN_OPERATION,
	SUBGHZ_SCAN_RESULT,
	SUBGHZ_START_STOP_ADV,
	SUBGHZ_ADV_INTERVAL,
#endif

#ifdef TWI_RHP_HW_GLAS_CART
	GLAS_CART_BATTERY,
	GLAS_CART_LOCKING_MODE,
	GLAS_CART_ENERGY_MODE,
	GLAS_CART_POD_DATA,
	GLAS_CART_STATUS,
    GLAS_CART_LOGS,
	GLAS_CART_INTERNAL_STATUS,
#endif
#ifdef TWI_RHP_PILL_DISPENSER
	PILL_DISPENSER_CMD,
#endif
	SUBTYPE_INVALID
} tenu_subtype;


/**
*	@enum		tenu_gpio_pull
*	@brief		enumeration that represents GPIO pull configuration.
*/
typedef enum
{
	GPIO_PULL_UP,
	GPIO_PULL_DOWN,
	GPIO_NO_PULL,
	INVALID_GPIO_PULL
} tenu_gpio_pull;

/**
 *	@enum		_tenu_op_source
 *	@brief		enumeration of the possible sources that can update the value of an attribute
 */
typedef enum
{
    BLE_COMMAND =0,
	INTERNAL_ACTION,
    INTERNAL_PROFILE,
    INTERNAL_SETTINGS,
    INTERNAL_TRIGGERS,
    INTERNAL_LOGGER,
    EXTERNAL_BLE,
} tenu_op_source;

/**
*	@enum		tenu_led_function
*	@brief		enumeration that represents LEDs' states.
*/
typedef enum
{
	LED_OFF,
	LED_ON,
	LED_TOGGLE,
	LED_BLINK_SLOW,
	LED_BLINK_NORMAL,
	LED_BLINK_FAST,
	LED_FLASH,
	LED_INVALID_FUNCTION
} tenu_led_function;

/**
*	@enum		tenu_gpio_interrupt_type
*	@brief		enumeration that represents different interrupt types.
*/
typedef enum
{
	RISING_EDGE,
	FALLING_EDGE,
	BOTH_EDGES,
	HIGH_LEVEL,
	LOW_LEVEL,
	INVALID_GPIO_INTERRUPT
} tenu_gpio_interrupt_type;

/**
*	@enum		tenu_pbtn_status
*	@brief		enumeration that represents different PBTNs' states.
*/
typedef enum
{
	PBTN_NOT_PRESSED,
	PBTN_PRESSED,
	PBTN_SHORT_PRESS,
	PBTN_LONG_PRESS,
	INVALID_PBTN_STATUS
} tenu_pbtn_status;

/**
*	@enum		tenu_pbtn_interrupt_type
*	@brief		enumeration that represents different PBTNs' interrupt types.
*/
typedef enum
{
	ON_SHORT_PRESS,
	ON_LONG_PRESS,
	ON_BOTH,
	INVALID_PBTN_INTERRUPT
} tenu_pbtn_interrupt_type;

/**
*	@enum		tenu_adc_bit_width
*	@brief		enumeration that represents ADC bit-width
*/
typedef enum
{
	EIGHT_ADC_BITS,
	NINE_ADC_BITS,
	TEN_ADC_BITS,
	INVALID_BIT_WIDTH
} tenu_adc_bit_width;

/**
*	@enum		tenu_adc_voltage_divider
*	@brief		enumeration that represents ADC Voltage divider values
*/
typedef enum
{
	ONE_THIRD,
	ONE_HALF,
	TWO_THIRD,
	THREE_THIRD,
	INVALID_VOLTAGE_DIVIDER
} tenu_adc_voltage_divider;

/**
 *	@enum		tenu_ble_advertise_oper
 *	@brief		Enum to define the BLE advertising operations.
 */
typedef enum
{
	BLE_ADVERTISE_DO_NOTHING = 0,
	BLE_ADVERTISE_STOP,
	BLE_ADVERTISE_START,
	BLE_ADVERTISE_RELEASE				/**< @brief This releases advertising, leaving its control to the Advertising Management Layer */
}tenu_ble_advertise_oper;

/**
 *	@enum		tenu_subghz_advertise_oper
 *	@brief		Enum to define the subghz advertising operations.
 */
typedef enum
{
	SUBGHZ_ADVERTISE_STOP = 0,
	SUBGHZ_ADVERTISE_START,
}tenu_subghz_advertise_oper;
/**
*	@enum		tenu_scanning_type
*	@brief		enumeration that represents different Scanning operations.
*/
typedef enum
{
	BLE_STOP_SCANNING = 0,
	BLE_START_PASSIVE_SCANNING,
	BLE_START_ACTIVE_SCANNING,
	BLE_INVALID_SCANNING
} tenu_scanning_type;

/**
*	@enum		tenu_subghz_scanning_type
*	@brief		enumeration that represents different Scanning operations.
*/
typedef enum
{
	SUBGHZ_STOP_SCANNING = 0,
	SUBGHZ_START_SCANNING,
	SUBGHZ_INVALID_SCANNING
} tenu_subghz_scanning_type;

/**
*	@enum		tenu_accelerometer_sensitivity
*	@brief		enumeration that represents different accelerometer's sensitivity.
*/
typedef enum
{
	DEFAULT_SENSE,	/**< @brief Default sensitivity */
	LOW_SENSE,		/**< @brief Low sensitivity */
	MEDIUM_SENSE,	/**< @brief Medium sensitivity */
	HIGH_SENSE		/**< @brief High sensitivity */
}tenu_accelerometer_sensitivity;

/**
*	@enum		tenu_accelerometer_alignment
*	@brief		enumeration that represents different Accelerometer alignment..
*/
typedef enum
{
	PSITIVE_X_UP,	/**< @brief +X Direction up.*/
	NEGATIVE_X_UP,	/**< @brief -X Direction up.*/
	PSITIVE_Y_UP,	/**< @brief +Y Direction up.*/
	NEGATIVE_Y_UP,	/**< @brief -Y Direction up.*/
	PSITIVE_Z_UP,	/**< @brief +Z Direction up.*/
	NEGATIVE_Z_UP	/**< @brief -Z Direction up.*/
}tenu_accelerometer_alignment;

/**
 *	@enum		tenu_wifi_pwr_mode
 *	@brief		Enum to define WiFi power modes
 */
typedef enum
{
	WIFI_PWR_OFF,
	WIFI_PWR_ON,
	WIFI_PWR_INVALID
} tenu_wifi_pwr_mode;

/**
 *	@enum		tenu_wifi_conn_oper
 *	@brief		Enum to define WiFi connection operations
 */
typedef enum
{
	WIFI_CONN_OPER_IDLE = 0,
	WIFI_CONN_OPER_BEGIN_CONNECT,
	WIFI_CONN_OPER_BEGIN_DISCONNECT
}tenu_wifi_conn_oper;

/**
 *	@enum		tenu_wifi_prov_status
 *	@brief		Enum to define WiFi provisioning status
 */
typedef enum
{
	WIFI_PROV_IN_PROGRESS = 0,
	WIFI_PROV_VALID,
	WIFI_PROV_INVALID
}tenu_wifi_prov_status;

/**
 *	@enum		tenu_wifi_scan_results_rssi_sort_type
 *	@brief		Enum to define WiFi scan results sorting type based on rssi
 */
typedef enum
{
	WIFI_SCAN_RESULTS_RSSI_SORT_NONE = 0,
	WIFI_SCAN_RESULTS_RSSI_SORT_ASCENDING,
	WIFI_SCAN_RESULTS_RSSI_SORT_DESCENDING
}tenu_wifi_scan_results_rssi_sort_type;

/**
 *	@enum		tenu_ble_central_conn_oper
 *	@brief		Enum to define BLE central connection operations
 */
typedef enum
{
	BLE_CONN_OPER_CENTRAL_IDLE = 0,
	BLE_CONN_OPER_BEGIN_CENTRAL_CONNECT,
	BLE_CONN_OPER_BEGIN_CENTRAL_DISCONNECT
}tenu_ble_central_conn_oper;

/**
 *	@enum		tenu_ble_peripheral_conn_oper
 *	@brief		Enum to define BLE central connection operations
 */
typedef enum
{
	BLE_CONN_OPER_PERIPHERAL_IDLE = 0,
	BLE_CONN_OPER_BEGIN_PERIPHERAL_DISCONNECT
}tenu_ble_peripheral_conn_oper;

/**
 *	@enum		tenu_ble_central_conn_status
 *	@brief		Enum to define the BLE Central connection status
 */
typedef enum
{
	BLE_CONN_CENTRAL_CONNECT_IN_PROGRESS = 0,
	BLE_CONN_CENTRAL_CONNECTED,
	BLE_CONN_CENTRAL_DISCONNECTED
}tenu_ble_central_conn_status;

/**
 *	@enum		tenu_ble_peripheral_conn_status
 *	@brief		Enum to define the BLE peripheral connection status
 */
typedef enum
{
	BLE_CONN_PERIPHERAL_DISCONNECTED = 0,
	BLE_CONN_PERIPHERAL_CONNECTED
}tenu_ble_peripheral_conn_status;

/**
 *	@brief		Enumeration that represents Options for controlling hardware handlers.
 */
typedef enum
{

    CTRL_OP_ATT_INITIALIZE = 0,      /**< @brief Hardware Handler initialization,
                                            used while upper layer need to initialize any hardware handler. */


	CTRL_OP_ATT_READ,					/**< @brief Handler read attribute,
									  used while upper layer need to read an attribute. */

	CTRL_OP_ATT_WRITE,					/**< @brief Handler write attribute,
									  used while upper layer need to write an attribute. */

	CTRL_OP_ATT_SAFETY_ERROR,			/**< @brief Handler Safety Error,
									  used while upper layer need to notify any handler with error in the safety tests. */

	CTRL_OP_GET_ATT_POINTER,                /**< @brief Handler ATT pointer,
                                      used while upper layer need to get a pointer to any ATT in the handler. */
#if defined(OTA_SUPPORT) || defined(RHP_GET_OTA_UPDATE_REQ_STATUS)
	CTRL_OP_OTA_UPDATE,
#endif
}tenu_io_ctrl_op;

/**
 *	@enum		tenu_nfc_internal_cmd
 *	@brief		Enum to define NFC internal command values
 */
typedef enum
{
	NFC_INTERNAL_CMD_NONE,
	NFC_INTERNAL_CMD_FNSH_ADV,
	NFC_INTERNAL_CMD_STRT_LNG_ADV,
	NFC_INTERNAL_CMD_STRT_SHRT_ADV,
	NFC_INTERNAL_CMD_INVALID
} tenu_nfc_internal_cmd;

#if defined(OTA_SUPPORT) || defined(RHP_GET_OTA_UPDATE_REQ_STATUS)
/**
 *  @brief      Enumeration that represents Module's states.
 */
typedef enum{
    MODULE_STATE_READY = 0x0,
    MODULE_STATE_NOT_READY,
    MODULE_STATE_HAVE_LOGS,
    MODULE_STATE_LOW_BATTERY,
}tenu_module_state;
#endif

#ifdef TWI_RHP_HW_BAT_SENSOR
typedef enum 
{
	BAT_SENSOR_USE_MILLI_VOLT = 0,
	BAT_SENSOR_USE_PERCENTAGE,
	BAT_SENSOR_INVALID_MODE
}tenu_bat_sensor_result_unit;
#endif		
/*-**********************/
/*- Report_Utility -----*/
/*-**********************/
/**
 *	@enum		tenu_report_type
 *	@brief		enumeration for the report entity type
 */
typedef enum
{
	/** @brief miscellaneous-data module */
	REPORT_MISC_DATA = 0,
	/** @brief PW-data module */
	REPORT_PW_DATA,
	/** @brief Variable length-data module */
	REPORT_VAR_LEN_DATA,
	REPORT_INVALID_TYPE
}tenu_report_type;


/**
 *	@enum		tenu_report_attribute_index
 *	@brief		enumeration for the report members
 */
typedef enum
{
	/** @brief PU8 attribute (R): The record size in bytes */
	REPORT_RECORD_SIZE = 0,
	/** @brief U16 attribute (R/W): The read size in records */
	REPORT_READ_COUNT,
	/** @brief U32 attribute (R/W): The read offset */
	REPORT_READ_OFFSET,
	/** @brief PU32 attribute (R): The total number of logged records */
	REPORT_TOTAL_LOGGED_RECORDS,
	/** @brief PU32 attribute (R): The offset of the first available record */
	REPORT_FRST_AVLBL_RECORD_OFFSET,
	/** @brief HEX attribute (R): The read data */
	REPORT_RECORD_DATA,
	REPORT_INVALID_ATTR_INDEX
}tenu_report_attribute_index;

/*-**********************/
/*- LOGGER -------------*/
/*-**********************/
#if	( defined(ENABLE_LOGGER_CRC_16) ||  defined(ENABLE_LOGGER_CRC_32) )	
/**
 *	@enum		tenu_logger_crc
 *	@brief		enumeration for the logger CRC feature
 */
typedef enum
{

	/** @brief Logger Has No CRC */
	LOGGER_CRC_DISABLED = 0,
   	/** @brief Logger computes 16-bit CRC, save it in flash with the log, to be verified upon reading the log. The CRC is not included in the sent packet, i.e. verification is done only on the FW side*/
	LOGGER_CRC_16,
   	/** @brief Logger computes 32-bit CRC, save it in flash with the log, to be verified upon reading the log. The CRC is not included in the sent packet, i.e. verification is done only on the FW side*/
	LOGGER_CRC_32,
   	/** @brief Logger computes 16-bit CRC, save it in flash with the log, to be verified upon reading the log. The CRC will be included in the sent packet, i.e. verification is to be done on both the FW and the mobile/GW sides*/
	LOGGER_CRC_16_CRC_INCLUDED,
   	/** @brief Logger computes 16-bit CRC, save it in flash with the log, to be verified upon reading the log. The CRC will be included in the sent packet, i.e. verification is to be done on both the FW and the mobile/GW sides*/
	LOGGER_CRC_32_CRC_INCLUDED,		
} tenu_logger_crc;
#endif


/**
 *	@enum		tenu_logger_attribute_index
 *	@brief		enumeration for the logger members
 */
typedef enum
{
	/** @brief U32 attribute: The logger last-time-report timestamp value */
	LOGGER_LAST_REPORT_TIMESTAMP = 0,
   	/** @brief ::U8 attribute: This attribute describes the type of the logger: ::TIMER_BASED_LOGGER or ::EVENT_BASED_LOGGER. */
	LOGGER_TYPE,
	/** @brief ::U32 attribute: The interval between each log for the attribute */
	LOGGER_INTERVAL,
	/** @brief ::U32 attribute: This attribute is used for sending a report to Server/Mobile every interval >= ::LOGGER_REPORT_INTERVAL */
	LOGGER_REPORT_INTERVAL,
	/** @brief ::U8 attribute: The Status of logging (start logging, stop logging, or reach maximum memory).
	 * 	  To start logging, set the command with ::LOGGER_STARTED.
	 * 	  To stop  logging, set the command with ::LOGGER_STOPPED.
	 *    If the logger reached the maximum available memory it will be set to ::LOGGER_REACHED_MAX_MEMORY
	 */
	LOGGER_STATUS,
	/** @brief ::U32 attribute: This attribute keeps track of the number of readings taken since the start of the logging session.
	 *    This attribute can only be reset to 0 if that data has been offloaded.
	 */
	LOGGER_NUM_UNREAD_LOGS,
	/** @brief  ::U32 attribute: This attribute indicates the user read index. It's incremented after each read. */
	LOGGER_READ_IDX,
	/** @brief U32 attribute: This is an attribute that determines the maximum number of logs that can be logged into flash.
	 */
	LOGGER_MAX_NUM_LOGS,
	/** @brief ::U32 attribute: This attribute keeps track of the time of logging in sec. */
	LOGGER_TIME_FROM_START,
   	/** @brief ::HEX attribute: This attribute contains the logs of the logger */
	LOGGER_LOGS,
   	/** @brief ::U8 attribute: This attribute describes the logs format based on the type of the hardware attribute we want to log */
	LOGGER_LOG_FORMAT,
   	/** @brief ::U32 attribute: This is a R/W attribute defines the time to start logging, in case of ::LOGGER_DELAYED_START, in seconds.
	*	It represents the number of remaining seconds to start the logger.
	*	If the Logger status is ::LOGGER_STARTED, the attribute value will be 0x00000000.
	*	If the Logger status is ::LOGGER_STOPPED_EXTERNALLY, the attribute value will be 0xFFFFFFFF.
	*	If the Logger status is ::LOGGER_REACHED_MAX_MEMORY, the attribute value will be 0xFFFFFFFF.
	*/
	LOGGER_TIME_TO_START,
	LOGGER_N_TO_KEEP,
    LOGGER_INVALID_ATTR_INDEX
}tenu_logger_attribute_index;

/**
 *	@enum		tenu_logger_circular_overwrite
 *	@brief		enumeration of the Logger's Overwrite modes
 */
typedef enum
{
	LOGGER_NO_OVERWRITE_MODE,				/**< @brief In this mode, Logger stops when number of logs reaches maximum available memory space, No overwriting*/
	LOGGER_CAREFUL_OVERWRITE_MODE,			/**< @brief In this mode, Logger overwrites the read logs only and stops logging when there is no read logs to overwrite them within the available memory space */
	LOGGER_CARELESS_OVERWRITE_MODE			/**< @brief In this mode, Logger overwrites logs regardless they were read or not and it never stops logging */
} tenu_logger_circular_overwrite;

/**
 *	@enum		tenu_default_log_format
 *	@brief		enumeration for default logs format
 */
typedef enum
{
	DEFAULT_LOG_FORMAT_1_RAW_DATA = 0,		/**< @brief Default Log Raw data Format */
	DEFAULT_LOG_FORMAT_RSVD0,
	DEFAULT_LOG_FORMAT_RSVD1,
	DEFAULT_LOG_FORMAT_RSVD2,
	DEFAULT_LOG_FORMAT_RSVD3,
	DEFAULT_LOG_FORMAT_RSVD4,
	DEFAULT_LOG_FORMAT_RSVD5,
	DEFAULT_LOG_FORMAT_RSVD6
}tenu_default_log_format;

/**
 *	@enum		tenu_temp_log_format
 *	@brief		enumeration for the temperature logs format
 */
typedef enum
{
	TEMP_LOG_FORMAT_2_BYTES_RAW_DATA = DEFAULT_LOG_FORMAT_1_RAW_DATA,	/**< @brief	Temperature is represented in 2 Bytes as it's from sensor, temperature * 100 */
	TEMP_LOG_FORMAT_1_BYTE_7_1,				/**< @brief Temperature is represented in 1 Bytes 7 bits MSB for integer part with +40 increase & 1 bit for fraction part 0.5 */
	TEMP_LOG_FORMAT_1_BYTE_INT,				/**< @brief Temperature is represented in 1 Byte integer part only */
	TEMP_LOG_FORMAT_4_BIT_COMPRESSED,		/**< @todo(Not implemented) */
	TEMP_LOG_FORMAT_RSVD0,
	TEMP_LOG_FORMAT_RSVD1,
	TEMP_LOG_FORMAT_RSVD2,
	TEMP_LOG_FORMAT_RSVD3
}tenu_temp_log_format;

/**
 *	@enum		tenu_logger_status
 *	@brief		enumeration for the Logger type
 */
typedef enum
{
	TIMER_BASED_LOGGER = 0,			/**< @brief Timer Based Logger. */
	EVENT_BASED_LOGGER				/**< @brief Event Based Logger. */
}tenu_logger_type;

/**
 *	@enum		tenu_logger_status
 *	@brief		enumeration for the Logger status
 */
typedef enum
{
	LOGGER_STOPPED_EXTERNALLY = 0,	/**< @brief Logger is stopped from the Engine. */
	LOGGER_STARTED,					/**< @brief Logger is running. */
	LOGGER_REACHED_MAX_MEMORY,		/**< @brief Logger stopped because it reaches Maximum memory. */
	LOGGER_DELAYED_START,			/**< @brief Time Logger will start after seconds defined in the ::LOGGER_TIME_TO_START attribute.*/
	LOGGER_INVALID_STATUS			/**< @brief Invalid status. */
}tenu_logger_status;

/*-**********************/
/*- TRIGGER-------------*/
/*-**********************/

/**
 *	@enum		tenu_twi_rhp_condition_type
 *	@brief		enumeration for defining the condition type
 */
typedef enum
{
	AND_COND_TYP = 0,
	OR_COND_TYP
}tenu_twi_rhp_condition_type;

/**
 *	@enum		tenu_adv_state
 *	@brief		enumeration for defining the state to be advertised
 */
typedef enum
{
	ADV_DATA_STATE = 0,
	ADV_ALERT_STATE,
	ADV_INVALID_STATE,
}tenu_adv_state;

/**
 *	@enum		tenu_trigger_actions_applying_rate
 *	@brief		enumeration for the trigger's actions applying rate
 */
typedef enum
{
	/** @brief The actions will be applied each time the evaluated trigger becomes true. */
	TRIGGER_APPLY_ACTIONS_MULTIPLE = 0,
	/** @brief The actions will be applied only if it is first time for the trigger's conditions were met to be true.
	*	The actions will be applied again in case the trigger's conditions goes from being true to false, and then returns true again.
	*/
	TRIGGER_APPLY_ACTIONS_SINGLE,
	/** @brief INVALID Actions-applying rate */
    TRIGGER_INVALID_ACTIONS_APPLYING_RATE
}tenu_trigger_actions_applying_rate;

/**
 *	@enum		tenu_trigger_attribute_index
 *	@brief		enumeration for the trigger members
 */
typedef enum
{
	/** @brief Boolean value attribute that indicates the trigger is enabled or not.*/
	TRIGGER_IS_ENABLED = 0,
	/** @brief ::U32 value attribute that defines the number of seconds after which RHP should poll and evaluate trigger */
	TRIGGER_EVALUATION_RATE_MS,
    TRIGGER_INVALID_ATTR_INDEX
}tenu_trigger_attribute_index;

/**
 *	@enum		tenu_action_type
 *	@brief		enumeration of the type of actions that can be executed as a result of a trigger
 */
typedef enum
{
	SET_ATTRIBUTE_ACTION = 0,
	SET_MULTIPLE_ATTRIBUTE_ACTION,
	ALERT_ACTION,
	STATUS_ACTION,
	MESSAGE_ACTION,
    ENTER_DEEP_SLEEP_MODE_ACTION,
    /** @todo TODO: Add a new trigger action: EXIT_DEEP_SLEEP_MODE */
	EVENT_BASED_LOGGER_TAKE_LOG_ACTION,
	ADVERTISE_BEACON_ACTION,
	ADVERTISE_EVENT_UUID_ACTION,
	START_ADVERTISE_STATE_ACTION,
	STOP_ADVERTISE_STATE_ACTION,
	NOTIFY_APP_ACTION
} tenu_action_type;

/*-**********************/
/*- Mode Exception -----*/
/*-**********************/

/**
 *	@enum		tenu_rhp_engine_sys_mode
 *	@brief		enumeration of possible Engine modes
 */
typedef enum
{
	/*********************************************************************************************************************************************
	 * ****************** Important Note *********************************************************************************************************
	 * This is the enum of engine modes, modes declaration must be in the same order as you want your engine to follow
	 * For Example, if enum declare MNFCTR_MODE, then PAIR_MODE, then NORMAL_MODE.
	 * so your engine modes will be manufacture then pair then finally running
	 *********************************************************************************************************************************************/
#ifdef TWI_MNFCTR_MODE
	MNFCTR_MODE,
#endif
#ifdef TWI_PAIR_MODE
	PAIR_MODE,
#endif
	RUNNING_MODE,
	INVALID_MODE
}tenu_rhp_engine_sys_mode;

/*-**********************/
/*- STATUS ------------*/
/*-**********************/

/**
 *	@enum		tenu_status_attribute_index
 *	@brief		enumeration for the status members
 */
typedef enum
{
	/** @brief ::U32 value attribute that defines the number of seconds after which the status should execute action */
	STATUS_REFRESH_RATE_SEC = 0,
    STATUS_INVALID_ATTR_INDEX
}tenu_status_attribute_index;

/*-**********************/
/*- GENERAL ------------*/
/*-**********************/

/**
 *	@enum		tenu_rhp_sts_lgr_alrt_msg_type
 *	@brief		enumeration of the available Status, Logger, Alert, or Message types that can be at the profile
 */
typedef enum
{
    PUSH_ITEM = 0,
    NTFY_CNNCTD_ITEM,
    PUSH_AND_NTFY_CNNCTD_ITEM,
    INVALID_ITEM
}tenu_rhp_sts_lgr_alrt_msg_type;

/**
 *	@enum		_tenu_rhp_direct_send_status
 *	@brief		enumeration of possible direct send status types
 */
typedef enum
{
	MSG_SEND_SUCCEEDED = 0,
	MSG_SEND_FAILED ,
	INVALID_SEND_STATUS
}tenu_rhp_direct_send_status;

/**
*	@enum		tenu_hw_deinit_reason
*	@brief		enumeration of Hardware De-initialization reasons
*/
typedef enum
{
	HW_DEINIT_FOR_DEEP_SLEEP = 0,		/**< @brief This is de-initialization for entering deep sleep .*/
	HW_DEINIT_FOR_SW_RESET,				/**< This is de-initialization for software reset.*/
	HW_DEINIT_INVALID_REASON			/**< @brief Invalid de-initialization reason.*/
}tenu_hw_deinit_reason;

/**
 *	@enum		tenu_rhp_request_type
 *	@brief		enumeration of the rhp request type (send Alert, send Status, advertise Event)
 */
typedef enum
{
	RHP_HANDLE_SEND_REQ = 0,
	RHP_HANDLE_APP_RQST,
	RHP_HANDLE_HANDLERS_RQST,
} tenu_rhp_request_type;

typedef enum
{
	AML_SEND_ALERT, 		/**< @brief Send alert event */
	AML_SEND_DATA, 			/**< @brief data alert event*/
	AML_ALERT_SUCCESS, 		/**< @brief Event indicating that sending alert succeeded */
	AML_DATA_SUCCESS, 		/**< @brief Event indicating that sending data succeeded  */
	AML_EVT_INVALID 		/**< @brief Invalid Event */
} tenu_twi_ble_hal_evt;

/**
 *	@enum		tenu_rhp_attribute_type
 *	@brief		enumeration of the available attributes types in the RHP profile
 */
typedef enum
{
    FEATURE_ATTR = 0,
    REPORT_ATTR,
    LOGGER_ATTR,
    TRIGGER_ATTR,
    VERSION_ATTR,
    STATUS_ATTR,
    INVALID_ATTR
}tenu_rhp_attribute_type;

/**
 *	@enum		_tenu_permissions
 *	@brief		enumeration of possible permissions for the hardware
 */
typedef enum
{
	READ_ONLY,
	READ_AND_WRITE,
	READ_AND_INDICATE,
	READ_AND_WRITE_AND_INDICATE,
	READ_AND_WRITE_INTERNALLY,
    PROTECTED,
} tenu_permission;

/**
 *	@enum		_tenu_rhp_request_notify_type
 *	@brief		enumeration of possible requestions/notifications for the RHP Engine
 */
typedef enum
{
	ATTR_CHANGED,
	WRITE_ATTR,
	READ_ATTR,
#ifdef TWI_PAIR_MODE
    BLE_UNPAIRED,
#endif
#ifdef TWI_RHP_TRIGGER
	TWI_RQST_NTFY_DEEP_SLEEP,
	ADVERTISE_BEACON,
	ADVERTISE_EVENT_UUID,
	STOP_ADVERTISE_STATE,
	START_ADVERTISE_STATE,
#endif

#if defined(TWI_RHP_LOGGER) && defined(SW_RESET_TIME_MINUTES)
	CLEAR_TO_RESET,
#endif
	SEND,
	UNDO_SEND,
	NOTIFY_CONNECTED_PEER,
#ifdef TWI_RHP_STATUS
	SEND_NOTIFY_STATUS,
#endif
	GET_SYS_STATUS,
	GET_SYS_MODE,
	GET_FW_VERSION,
#if defined(OTA_SUPPORT) || defined(RHP_GET_OTA_UPDATE_REQ_STATUS)
	OTA_FW_UPDATE,
#endif
	TB_LOGGER_IS_LOGGING,
	EVENT_LOGGER_LOGGING_DONE, /*Event based Logger is done to ready take another log */
#ifdef TWI_RHP_TRIGGER
	CHECK_ACTIVE_LOGGERS,
#ifdef TWI_RHP_LOGGER
	EVENT_BASED_LOGGER_TAKE_LOG,
#endif
#endif
	APP_NOTIFY_SDK,
	APP_RQST_SDK,
	HANDLER_RQST_SDK,
    HANDLER_RQST_APP,
	ENABLE_ALWAYS_CONNECTED_MODE,
	DISABLE_ALWAYS_CONNECTED_MODE,
} tenu_rhp_request_notify_type;


/**
 *	@enum		tenu_handler_request
 *	@brief		enumeration of possible handlers that request the App
 */
typedef enum
{
	GLAS_HW_CART,
    ACCELEROMETER_HW,
} tenu_handler_request;

/**
 *	@enum		tenu_rhp_rqst_msg_type
 *	@brief		enumeration of possible SEND Request types
 */
typedef enum
{
	MSG,
	ALERT,
	LOGS,
	GENERAL
}tenu_rhp_rqst_msg_type;

/** @brief
* Different message formats are stated as follows:
*
* G - GET, S - SET, v - Value, V - Version
*-------------------------------------------------------------------------------------------------------------------------
*	Type\ Used with	|	VERSION	|	SATUS	|	FEATR	|	FEATR_ATTR	|	TRGR	|	TRGR_ATTR	|	LOGR	|	LOGR_ATTR	|
*   ---------------	|	------- | ---------	| ---------	| -------------	|	-------	| 	----------	| 	-----	|	---------	|
* GET_CMD			|	 GV		|	  G		|	 G0		|	   G0.0		|	GT0		|   GT0.0		|	GL0		|	   GL0.0	|
* SET_CMD			|	  -		|	  -		|	 -		|	  S0.0=v	|	 -		|   ST0.0=v		|    -		|     SL0.0=v	|
* RSP_MSG			|   V=0.0.0	|	  -		|	 -		|	  0.0=v		|    -		|   T0.0=v		|    -		|      L0.0=v	|
* MSG_MSG			|     -		|	Message	| Format	|	 is			|	  M0.0	|     -			|    -		|    	-		|
* ALT_MSG			|   ALERT	| 	Message	| Format	|	 is			|	  A0.0	|     -			|    -		|    	-		|
*****************************************************************************************************************
*/
typedef enum
{
	GET_CMD = 0,		/**< @brief This message is a GET command */
	SET_CMD,			/**< @brief This message is a SET command */
    GETE_CMD,		    /**< @brief This message is a GET command with error responce*/
	SETE_CMD,			/**< @brief This message is a SET command with error responce*/
	RSP_MSG,			/**< @brief This message is a Response Message */
	GERR_MSG,           /**< @brief This message is an get execution status Message */
	SERR_MSG,           /**< @brief This message is an set execution status Message */
	INV_MSG
}tenu_twi_rhp_msg_type;

typedef enum
{
	VERSION = 0,			/**< @brief Version */
	SATUS,					/**< @brief Status */
	SATUS_ATTR,				/**< @brief Status Attribute */
	FEATR,					/**< @brief Feature */
	FEATR_ATTR,				/**< @brief Feature Attribute */
	TRGR,					/**< @brief Trigger */
	TRGR_ATTR,				/**< @brief Trigger Attribute */
	LOGR,					/**< @brief Logger */
	LOGR_ATTR,				/**< @brief Logger Attribute */
	MANUFACTURING_ATTR,     /**< @brief Manufacturer Attribute that is set in the manufacturing process*/
	RPRT,					/**< @brief REPORTING UTILITR  */
	RPRT_ATTR,              /**< @brief REPORTING UTILITR Attribute  */
	PAIRING_ATTR,			/**< @brief Pairing Attribute that is set in the pairing process */
	SEC_PAIRING_ATTR,		/**< @brief Security Pairing Attribute that is set in the pairing process */
	MSG_MSG,				/**< @brief This message is a Generic App Message */
	ALT_MSG,				/**< @brief This message is an Alert Message */
	INVALID					/**< @brief Invalid Sub_type*/
}tenu_twi_rhp_msg_sub_type;

/**
 *	@enum		tenu_scan_node_type
 *	@brief		enum to show scan node types
 */
typedef enum
{
	INVALID_NODE = 0,
	PERIPHERAL_NODE,
	GATEWAY_NODE
} tenu_scan_node_type;

/**
 *	@enum		tenu_rhp_rsrvd_feat_attrbs
 *	@brief		enumeration of the the message sending type
*/
typedef enum
{
	RHP_RSVD_ATTR_CLOUD_DEST_NEED_TO_SEND_NUM = 0x00,
	RHP_RSVD_ATTR_DEST1_NEED_TO_SEND_NUM,
    RHP_RSVD_ATTR_UTC_NUM,
	RHP_RSVD_ATTR_ERR_STATUS_REPLY_NUM,
	RHP_RSVD_ATTR_TIMEZONE_NUM,
	RHP_RSVD_ATTR_INVALID_NUM
}tenu_rhp_rsrvd_feat_attrbs;


/**
 *  @enum       tenu_rhp_ota_feat_attrbs
 *  @brief      enumeration of the the message sending type
*/
typedef enum
{
    RHP_OTA_ATTR_CMD = 0x00,

    RHP_OTA_ATTR_INVALID_NUM
}tenu_rhp_ota_feat_attrbs;

/**
 *	@enum		tenu_send_data_type
 *	@brief		enumeration of messages' sending types
*/
typedef enum
{
	SEND_TYPE_INVALID = 0,
	SEND_TYPE_PUSH,					/**< @brief This type will be used with the data that the engine needs to send to server.*/
	SEND_TYPE_RESPONSE,				/**< @brief This is the type of data that is sent as a response to a GET COMMAND.*/
	SEND_TYPE_APPLICATION			/**< @brief This is the application-specific request of sending data.*/
}tenu_send_data_type;

/**
 *	@enum		tenu_rhp_saftey_error
 *	@brief		Enum indicates System Safety error types
 */
typedef enum
{
	TWI_RHP_SAFETY_BROWN_OUT_DETECT = 0,
	TWI_RHP_SAFETY_BROWN_OUT_RESET,
	TWI_RHP_SAFETY_WDT_FIRED,
	TWI_RHP_SAFETY_SW_RESET,
	TWI_RHP_SAFETY_NORMAL_POWER_UP,
	TWI_RHP_SAFETY_EXTERNAL_PIN_RESET,
	TWI_RHP_SAFETY_SYS_RESET,
	TWI_RHP_SAFETY_CRITICAL_VAR_MISMATCH,
	TWI_RHP_SAFETY_ERR_COUNT
}tenu_rhp_saftey_error;

/**
 *	@enum		tenu_rhp_dst0_cmds_list_type
 *	@brief		enumeration of the DST0 Msg list types
 */
typedef enum
{
	RHP_DST0_ALLOWED_LIST = 0,
	RHP_DST0_NOT_ALLOWED_LIST,
}tenu_rhp_dst0_cmds_list_type;

/**
 *	@enum		tenu_attr_resp_type
 *	@brief		enumeration of attribute responses types
 */
typedef enum
{
	ATTR_RESP_TYPE = 0,
	SET_ERR_RESP_TYPE,
}tenu_attr_resp_type;

#if defined(TWI_VITA_SDK)
/**
 *	@enum		tenu_twi_vita_sdk_evt
 *	@brief		enumeration of wrapped vita sdk events
 */
typedef enum
{
	TWI_EVENT_LOCK = 0,			
	TWI_EVENT_UNLOCK,	
	TWI_EVENT_PAIRING_FAILED,	
	TWI_EVENT_UNPAIRING,
	TWI_EVENT_SERVER_CRTG_VERIFICATION_RESULT, 
	TWI_EVENT_SDK_CRTG_VERIFICATION_RESULT,
#ifdef SUPPORT_OTA_SERVICE_MANAGER
    TWI_EVENT_OTA_SERVICE_MANAGER,
    TWI_EVENT_OTA_GET_SYSTEM_STATUS,
#endif
	TWI_EVENT_CHANGE_DEVICE_SERIAL,
    TWI_EVENT_CHANGE_DST_STATUS,
}tenu_twi_vita_sdk_evt;


/**
 *	@enum		tenu_twi_vita_app_evt
 *	@brief		enumeration of wrapped vita app events
 */
typedef enum
{
    TWI_EVENT_CRTG_INSERTED = 0,
	TWI_EVENT_CRTG_REMOVED,
    TWI_EVENT_LOCK_HANDLED,  
	TWI_EVENT_UPDATE_SDK_STATE,
	TWI_EVENT_CONTROL_SECURITY,
	TWI_EVENT_TWI_ID_CHANGE,
	TWI_EVENT_DISCONNECT,
	TWI_EVENT_GENERATE_PUBLIC_DATA,
#ifdef SUPPORT_OTA_SERVICE_MANAGER
	TWI_EVENT_RQST_OTA_INFO_VERIFICATION,
	TWI_EVENT_SEND_OTA_SYS_STATE,
#endif

}tenu_twi_vita_app_evt;

#endif

/**
 *	@enum		tenu_rhp_req_sub_type
 *	@brief		enumeration of wrapped vita app requests
 */
typedef enum
{
    TWI_EVENT_REQ_0 = TWI_SDK_REQ_0,
	TWI_EVENT_REQ_1 = TWI_SDK_REQ_1,
	TWI_EVENT_REQ_2 = TWI_SDK_REQ_2,
	TWI_EVENT_REQ_3 = TWI_SDK_REQ_3,
}tenu_rhp_req_sub_type;

/**
 *	@enum		_tenu_rhp_engine_evt_type
 *	@brief		enumeration of possible Engine events' types
 */
typedef enum
{
	MSG_RECEIVED = 0,
	APP_SAVE_SETTINGS_SUCCESS,
	PUSH_SEND_COMPLETED,
	ATTRIBUTE_CHANGED_INTERNALLY,
	ATTRIBUTE_CHANGED_EXTERNALLY,
	MANUFACTURE_DATA_RCVD,
	PAIRING_DATA_RCVD,
	MANUFACTURE_DATA_QUERY,
	PAIRING_DATA_QUERY,
	TIMER_BASED_LOGGER_IS_LOGGING,
	EVENT_LOGGING_IS_DONE,
	LOGGER_IS_REPORTING,
	BLE_EVT,
#ifdef TWI_PAIR_MODE
    BLE_SYS_UNPAIR,
#endif
	SYS_MODE_CHANGED,
	SDK_REQUEST,
    ATTRIBUTE_REQUESTED,
	NUDGE_CONNECTED_DEVICE_SUCCESS, /*Event used to notify the application with nudge peer finished successfully after receiving the ack message*/
	HANDLER_REQUEST,
	INVALID_EVT
}tenu_rhp_engine_evt_type;

typedef twi_u8 tau8_twi_id[TWI_ID_SIZE];

/*-***********************************************************/
/*- STRUCTS AND UNIONS --------------------------------------*/
/*-***********************************************************/

typedef struct _tstr_twi_rhp_attr tstr_twi_rhp_attr;
typedef struct _tstr_notifiy_request tstr_notifiy_request;
typedef struct _tstr_handler_rqst_app tstr_handler_rqst_app;
typedef twi_s32(*tpf_rqst_ntfy_rhp_engn)(tstr_notifiy_request *pstr_rqst_ntfy);

/*-**********************/
/*- VALUE --------------*/
/*-**********************/

/**
 *	@struct		tstr_twi_rhp_resp
 *	@brief		structure that holds attribute response info
 */
TWI_PACK(typedef  struct 
{
	TWI_PACK(union
	{
		twi_const tstr_twi_rhp_attr*    pstr_attr;
		TWI_PACK(struct
		{
			twi_u8					u8_attr_num;
			twi_u8					u8_trigger_idx;
			twi_u8					u8_action_idx;
		})str_action_info;
	})							uni_resp_data;
	twi_s32                         s32_error_status; /*status of execution of Set/Get commands*/
	tenu_attr_resp_type             enu_resp_type;
    tenu_twi_rhp_msg_sub_type       enu_msg_sub_type;
    tenu_twi_rhp_msg_type           enu_msg_type;
})tstr_twi_rhp_resp;


/**
 *	@struct		tstr_rhp_req_data
 *	@brief		structure to hold RHP app request data
 */
typedef struct
{
	tenu_rhp_req_sub_type enu_rhp_req_sub_type;
	twi_u8 * pu8_data;
	twi_u16 u16_len;
}tstr_rhp_req_data;

/**
 *	@struct		_tstr_twi_float
 *	@brief		structure to represent fixed point float
 */
typedef struct
{
	/** @brief integer part */
	twi_s16 s16_int_part;
	/** @brief The fractional part */
	twi_u16 u16_frac_part;
	/** @brief divisor is 10 raised to this value */
	twi_u8 u8_div_exp;
} tstr_twi_float;

/**
 *	@struct		_tstr_twi_u8_array
 *	@brief		structure to represent a byte array
 */
typedef struct
{
	/** @brief number of bytes in array */
	twi_u16 u16_len;
	/** @brief pointer to the bytes */
	twi_u8 * pu8_data;
} tstr_twi_u8_array;

/**
 *	@struct		_tstr_twi_rhp_value
 *	@brief		structure to represent a value for an attribute
 */
typedef struct
{
	/** @brief byte to specify type */
	tenu_value_type enu_type;
	/** @brief union that holds that values */
	union
	{
		/** @brief boolean value */
		twi_bool b_boolean;
		/** @brief unsigned 8-bit int value */
		twi_u8 u8_int;
		/** @brief pointer to unsigned 8-bit int value */
		twi_u8* pu8_int;

		/** @brief signed 8-bit int value */
		twi_s8 s8_int;
		/** @brief pointer to signed 8-bit int value */
		twi_s8* ps8_int;

		/** @brief unsigned 16-bit int value */
		twi_u16 u16_int;
		/** @brief pointer to unsigned 16-bit int value */
		twi_u16* pu16_int;

		/** @brief signed 16-bit int value */
		twi_s16 s16_int;
		/** @brief pointer to signed 16-bit int value */
		twi_s16* ps16_int;

		/** @brief unsigned 32-bit int value */
		twi_u32 u32_int;
		/** @brief pointer to unsigned 32-bit int value */
		twi_u32* pu32_int;

		/** @brief signed 32-bit int value */
		twi_s32 s32_int;
		/** @brief pointer to signed 32-bit int value */
		twi_s32* ps32_int;

		/** @brief unsigned 64-bit int value */
		twi_u64 u64_int;
		/** @brief pointer to unsigned 64-bit int value */
		twi_u64* pu64_int;

		/** @brief signed 64-bit int value */
		twi_s64 s64_int;
		/** @brief pointer to signed 64-bit int value */
		twi_s64* ps64_int;

		/** @brief fixed point float value */
		tstr_twi_float str_flt_float;
		/** @brief hex value */
		tstr_twi_u8_array str_hex_array;
	} uni_value;
} tstr_twi_rhp_value;

/**
 *	@struct		_tstr_twi_rhp_computed_value
 *	@brief		structure that holds the computation info to be done with two values.
 */
typedef struct
{
	/** @brief enumeration of the computation to execute */
	tenu_computation_type enu_compute_type;
	/** @brief First value in the computation */
	tstr_twi_rhp_value * pstr_value_one;
	/** @brief Second value in the computation */
	tstr_twi_rhp_value * pstr_value_two;
} tstr_twi_rhp_computed_value;

/**
 *	@struct		_tstr_twi_rhp_condition
 *	@brief		structure that holds the trigger's condition info.
 */
typedef struct
{
	/** @brief Context of the comparison in the trigger */
	twi_u8 u8_comparison_index;
	/** @brief enumeration of the comparison to execute */
	tenu_compare_type enu_compare_type;
	/** @brief first computed value in the comparison */
	twi_const tstr_twi_rhp_computed_value * pstr_computed_value_one;
	/** @brief second computed value in the comparison */
	twi_const tstr_twi_rhp_computed_value * pstr_computed_value_two;
} tstr_twi_rhp_condition;


/*-**********************/
/*- HARDWARE -----------*/
/*-**********************/
#if defined (TWI_ACC_ENABLE_FIFO_CONTENT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
/**
 *	@struct		_tstr_twi_acc_fifo_content
 *	@brief		structure that holds the Accelerometer's FIFO info.
 */
typedef struct
{
	twi_u16		u16_fifo_levels_num;
	twi_s16		as16_acc_fifo_content[TWI_RHP_HW_ACC_SENSOR_FIFO_BUF_SIZE];
}tstr_twi_acc_fifo_content;
#endif

#if defined (TWI_ACC_ENABLE_CONFIGRATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
/**
*	@enum		tenu_acc_config_type
*	@brief		enumeration that represents acc configurations.
*/
typedef enum
{
	ACC_HARDWARE_CONFIG,		/**< @brief Write/Read the configuration on the acc hardware */
	ACC_INTERRUPT_HANDLING,		/**< @brief Write/Read the configuration of the acc interrupt handling */
} tenu_acc_config_type;

/**
 *	@struct		tstr_acc_config
 *	@brief		structure to represent acc configurations
 */
typedef struct
{
	/** @brief byte to specify type */
	tenu_acc_config_type enu_acc_config_type;
	/** @brief union that holds that values */
	union
	{
		/** @brief boolean value for handing interrupts of the acc*/
		twi_bool b_disable_interrupt_handling;
	} uni_config;
} tstr_acc_config;
#endif

typedef struct
{
	twi_u8 u8_pin;
	twi_u8 u8_port;
}tstr_twi_gpio_pin;

/**
 *	@struct		_tstr_twi_hardware
 *	@brief		structure that holds RHP representation for any HW.
 */

typedef struct
{
	tenu_type enu_type;
	tenu_subtype enu_subtype;
	const tstr_twi_gpio_pin* pstr_gpio_pins;
	twi_u8						*pau8_settings_buff;	/**< @brief This buffer holds the settings that will be saved in the flash memory. */
	union _uni_init_options
	{
		struct _gpio_init_options
		{
			tenu_gpio_interrupt_type 	enu_gpio_interrupt_type;
			tenu_gpio_pull			 	enu_initial_gpio_pull;
		} gpio_init_options;
		struct _pbtn_init_options
		{
			twi_bool					b_pulled_up;
			twi_bool					b_external_pull;
			twi_u8 						u8_debounce_delay_ms;
			twi_u16 					u16_long_press_time_ms; 				/**< @brief how long is LONG_PRESS in milliseconds */
			tenu_pbtn_interrupt_type 	enu_pbtn_interrupt_type;
			tstr_timer_mgmt_timer*		pstr_pbtn_timer;		/**< @brief PBTN's de-bounce Timer. >*/
    		
		} pbtn_init_options;
		struct _led_init_options
		{
			twi_bool 					b_inverted;
			tstr_timer_mgmt_timer*		pstr_led_timer;			/**< @brief LED's blinking/flashing Timer. >*/
			tstr_twi_rhp_value*			pstr_led_on_period_ms; 	/**< @brief  How many milliseconds should the LED illuminate each "pstr_led_rate_ms" milliseconds */
			tstr_twi_rhp_value*			pstr_led_rate_ms;			/**< @brief Time interval between each two consecutive ON periods in milliseconds*/
		} led_init_options;
		struct _pwm_init_options
		{
			twi_u8 						u8_duty_cycle_prcntg; /**< @brief  Duty cycle in percentage */
			twi_u32 					u32_freq_hz;  /**< @brief  frequency in Hz. */
		} pwm_init_options;
		struct _adc_init_options
		{
			twi_bool 					b_use_external_vref;
			tenu_adc_bit_width 			enu_bit_width;
			tenu_adc_voltage_divider 	enu_vref_divider;
			tenu_adc_voltage_divider 	enu_vin_divider;
            tstr_twi_float 				str_vref_value;
		} adc_init_options;
		struct _acc_sensor_tilt_angle_options
		{
			tenu_accelerometer_alignment 	enu_accelerometer_alignment;
		} acc_sensor_tilt_angle_init_options;
		struct _light_sensor_init_options
		{
			twi_u8 						u8_sampling_interval_s;
		} light_sensor_init_options;
		struct _ble_scan_operation_init_options
		{
			twi_u16 					u16_scan_interval_ms;
			twi_u16 					u16_scan_window_ms;
#ifdef nordic_sdk_16_0_0
			twi_u16 					u16_scan_timeout_ms;
#else
			twi_u16 					u16_scan_timeout_s;
#endif
		} ble_scan_operation_init_options;
		struct _radio_init_options
		{
			twi_u16 u16_scan_interval_ms;
			twi_u16 u16_scan_window_ms; 
			twi_u16 u16_scan_timeout_ms;

		} radio_init_options;
		struct _ble_scan_result_init_options
		{
			twi_u16 * pu16_prof_ids_filter_list;
			twi_u16  u16_prof_id_list_len;
		} ble_scan_result_init_options;
		struct _ble_app_data_options
		{
			tstr_twi_rhp_value*			pstr_app_data_tag;
		} ble_app_data_options;
#ifdef TWI_RHP_HW_WIFI
		struct _wifi_scan_results_options
		{
			twi_u16 u16_num_required_scan_results;
			tenu_wifi_scan_results_rssi_sort_type enu_rssi_sort;
		} wifi_scan_results_options;

		struct _wifi_scan_start_options
		{
			twi_u16 u16_scan_timeout_ms;
			tenu_wifi_scan_ch enu_scan_ch;
			tenu_wifi_scan_mode scan_mode;
		} wifi_scan_start_options;
#endif
		struct 
		{
			twi_u16 u16_acc_shock_th_mg;
		}acc_config;
#ifdef TWI_RHP_HW_BAT_SENSOR
		struct _bat_sensor_options
		{
			tenu_bat_sensor_result_unit enu_bat_sensor_result_unit;
		} bat_sensor_options;
#endif		
	} uni_init_options;
} tstr_twi_hardware;

/**
 *	@struct		tstr_twi_rhp_indicate_hw
 *	@brief		structure to represent data needed by any indicate hardware
 */
typedef struct
{
	/** @brief Count of the HW that have a permission of type READ_AND_INDICATE or READ_AND_WRITE_AND_INDICATE. */
	twi_u8 						u8_indct_hw_cnt;
	/** @brief Array of a pointers of attributes to be used to save the arguments of the interrupt callback.*/
    const tstr_twi_rhp_attr**	ppstr_indct_hw_attrs;
} tstr_twi_rhp_indct_hw;

typedef union _tuni_crtl_hw_data
{
	struct
	{
		const tstr_twi_rhp_attr * pstr_attr;
		tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn;
		tstr_twi_rhp_indct_hw* pstr_indct_hw;
	}str_hw_intialize_op;

	struct
	{
		const tstr_twi_rhp_attr * pstr_feature_attr;
		tstr_twi_rhp_value* pstr_value;
        tenu_op_source enu_op_src;
	}tstr_hw_read_write_op;

	struct
	{
		tenu_rhp_saftey_error enu_safety_err;
	}str_safety_error_op;
	
	struct{
		twi_u8 u8_feat_index;
	    twi_u8 u8_att_index;
	    tstr_twi_rhp_attr* pstr_rhp_att;
	}str_att_get_att_ptr_op;
#if defined(OTA_SUPPORT) || defined(RHP_GET_OTA_UPDATE_REQ_STATUS)
	struct{
	        tenu_module_state enu_module_state;
	}str_ota_request;
#endif
}tuni_io_ctrl_op_data;

/**
 *	@struct		_tstrt_hardware_handlers
 *	@brief		structure that holds RHP HW handlers' functions.
 */
typedef struct
{
	twi_s32(*initialize_hardware)   (const tstr_twi_hardware * pstr_hardware,tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn,tstr_twi_rhp_indct_hw* pstr_indct_hw,tenu_permission enu_permission);

	twi_s32(*deinitialize_hardware) (const tstr_twi_hardware * pstr_hardware);

	twi_s32(*read_hardware_value)   (const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src);

	twi_s32(*write_hardware_value)  (const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src);

}tstrt_hardware_handlers;

/**
 *	@struct		_tstr_twi_rhp_feature
 *	@brief		structure to represent a feature
 */
typedef struct
{
	/** @brief index of the feature in the context of the profile */
	twi_u8										feature_index;
	/** @brief number of attributes in the features */
	twi_u8										u8_num_attributes;
	/** @brief pointer to the array of attribute pointers */
	twi_const tstr_twi_rhp_attr* twi_const*		ppstr_attributes;
} tstr_twi_rhp_feature;

/**
 *	@struct		tstr_twi_hardwares_save_settings_info
 *	@brief		Structure holds the information needed for save setting for the Hardwares
 */
typedef struct
{
	/** @brief number of saved attributes */
	twi_u8							u8_num_saved_attrs;

	/** @brief Save Setting Buffer size */
	twi_u16							u16_save_buf_size;

	/** @brief Array of saved attributes pointers want to be saved */
	const tstr_twi_rhp_attr* const*	ppstr_saved_attr;

	/** @brief Pointer to the array of Attributes' Settings to be saved */
	twi_u8 *						pau8_save_attrs_buf;
}tstr_twi_hardwares_save_settings_info;

/**
 *	@struct		_tstr_twi_rhp_hardware_in
 *	@brief		input structure to initialize hardware module
 */
 typedef struct
{
	/** @brief number of features in this profile */
	twi_u8									u8_num_features;

	/** @brief array of feature pointers */
	const tstr_twi_rhp_feature*	const*		ppstr_features;

	/** @brief Array of a pointers of attributes to be used to save the arguments of the interrupt callback.*/
	tstr_twi_rhp_indct_hw*					pstr_indct_hw;

	/** @brief Structure holds the information needed for save setting for the hardware */
	tstr_twi_hardwares_save_settings_info*	pstr_hardwares_save_settings;
} tstr_twi_rhp_hardware_in;

/**
 *	@struct		_tstr_twi_rhp_report
 *	@brief		structure to represent a report utility entity of a certain profile
 */
typedef struct
{
	/** @brief The type of the reporting entity. */
	tenu_report_type				enu_type;
	/** @brief This is the report index. */
	twi_u8							u8_report_index;
	/** @brief U16 Represents the last number of records that was read by the reporting module */
	twi_u16							*pu16_last_read_count;
	/** @brief ::U8 that represents the channels that will be used to forward this action.
			each bit represents a channel. 0 --> Not a valid channel, 1 --> a valid channel. */
	const twi_u8					u8_output_destinations;
	/** @brief Array of the reporting attrebutes. */
	const tstr_twi_rhp_attr*		apstr_report_attributes[REPORT_INVALID_ATTR_INDEX];

#if defined(TWI_RHP_REPORT_MISC)|| defined(TWI_RHP_REPORT_PWDATA)|| defined(TWI_RHP_REPORT_ELV)
	/** @brief a set of pointers that point to the module-related data structure. */
	union
	{
		tstr_twi_misc_data*	pstr_misc_data;
		tstr_twi_pwdata_data* pstr_pwdata_data;
		tstr_twi_elv_data* pstr_elv_data;
	}uni_module_data;
#endif
}tstr_twi_rhp_report;
/****************************************************************************************************************************/
typedef struct
{
	/** brief Number of rprts that need to be saved */
	twi_u8	u8_num_save_rprts;
	/** brief Save Settings Buffer size */
	twi_u16	u16_save_buf_size;
    twi_u8* pau8_rprts_idx;
    /** brief Pointer to the array of rprts' Settings to be saved */
    twi_u8* pau8_save_rprts_buf;
}tstr_twi_reporting_utility_save_settings_info;


/**
 *	@struct		tstr_twi_rhp_reports_in
 *	@brief		structure to  the information for the reports' module.
 */
typedef struct
{
	/** @brief number of reports in the system */
	twi_u8									u8_num_reports;

	/** @brief Array of reports pointers */

	const tstr_twi_rhp_report* const*		ppstr_reports;

	/** @brief Pointer to array that holds the attributes of the reports that need to send */
	tstr_twi_rhp_attr **					appstr_reports_attr_dispatch[OUTPUT_DESTS_NUM];
    tstr_twi_reporting_utility_save_settings_info* pstr_reporting_utility_save_settings;
}tstr_twi_rhp_reports_in;

/*-**********************/
/*- LOGGER -------------*/
/*-**********************/

typedef twi_s32(*tpf_twi_logger_cb)(tstr_twi_rhp_attr * pstr_logger_attr, void *pv_user_data);

/**
 *	@struct		_tstr_twi_rhp_logger
 *	@brief		structure to represent a logger of a certain profile
 */
typedef struct
{
	/** @brief pointer to temp buffer used when logging from N_TO_KEEP attribute. Must point to aligned buffer */
	twi_u8							*pu8_n_to_keep_buf;
	/** @brief length of the temporary buffer used to log N_TO_KEEP data */
	twi_u16							u16_n_to_keep_buf_len;
    /** @brief This attribute decides whether the logger will record a value on start */
    twi_bool                        b_log_on_start;
	/** @brief ::U8 that represents the channels that will be used to forward this action.
			each bit represents a channel. 0 --> Not a valid channel, 1 --> a valid channel. */
	const twi_u8					u8_output_destinations;	
	/** @brief This flag indicates if there is a saving operation on this logger or not */
	twi_bool						b_save_inprogress;
	/** @brief This flag indicates that the logger has unread logs and its report interval timer was fired. */
	twi_bool						b_need_to_push;
    /** @brief This flag indicates that the logger had taken log and need to notify. */
	twi_bool						b_need_to_ntfy;
    /**@brief This BOOLEAN indicates the logger doesn't need to push all logs on one request*/
	twi_bool				        b_no_push_logs;
	/** @brief The State of logging overwrite
	 * enable or disable circular logging overwrite and its type.
	 * We have two types of overwriting.
	 */
	tenu_logger_circular_overwrite	enu_circular_overwrite;

#if defined(OTA_SUPPORT) || defined(RHP_GET_OTA_UPDATE_REQ_STATUS)
	/** @brief This flag indicates that the logger needs to check if has logs before entering OTA mode. */
	twi_bool b_ota_check_logs;
#endif

#if	( defined(ENABLE_LOGGER_CRC_16) ||  defined(ENABLE_LOGGER_CRC_32) )
	/** @brief This is the logger index. */
	tenu_logger_crc					enu_crc_enable;
#endif
	/** @brief This is the number of invalid read logs, i.e Has invalid CRC. */
	twi_u32							u32_last_invalid_read_logs_num;				/* number of invalid logs that was read this time from this logger, io.e. for the last send operation */
	/** @brief This is the logger index. */
	twi_u8							u8_logger_index;
	/** @brief This is an ORed flags that represent the current status of the logger. */
	twi_u8							u8_logger_status_flags;
	/** @brief This is the check point save flag, when the module needs to save itself, it raises this flag */
	twi_u8							u8_is_need_to_save;
	/** @brief This indicates the log size */
	twi_u16							u16_log_size;
	/** @brief This indicates the maximum memory size */
	twi_u32							u32_max_memory_size;
	/** @brief This attribute holds the current count of logger timer for reading logs. */
	twi_u32							u32_log_counter;
    /** @brief This attribute holds the number of logs to notify at it. */
	twi_u32							u32_num_log_ntfy;
	/** @brief This attribute holds the current count of logger timer for reporting logs. */
	twi_u32							u32_report_counter;
	/** @brief This indicates the total number of logs in the last send operation */
	twi_u32							u32_last_read_logs_num;
	/**@brief number of needed fifo callback which equal to number of attributes + 1(in case of event base which is time )
	 * to increment total logger unread logs by one
	 */
	twi_u32							u32_num_needed_cb;
	/** @brief This attribute keeps track of the number of all the logs that were taken since the start of this logging session.
	 *    This attribute can not be reset.
	 */
	twi_u32							u32_total_num_logs;
	/** @brief This indicates ::LOGGER_TIME_FROM_START of the last ::EVENT_BASED_LOGGER log. */
	twi_u32							u32_last_event_log_time;
	/** @brief This is the number of logs returned when ::LOGGER_NUM_LOGS_TO_KEEP is read */
	const twi_u32					u32_n_logs_to_keep;
	/** @brief The number of remaining logs to be sent */
	twi_u32							u32_remaining_n_logs;
	/** @brief The read index of the n logs to keep */
	twi_u32							u32_n_to_keep_r_idx;
	/** @brief N logs sent last time */
	twi_u32							u32_last_n_logs_sent;
	/** @brief Offset in fifo from virtual read index to seek in order to read N logs */
	twi_s32							s32_offset_from_vridx;
	/** @brief n logs that exist currently in flash */
	twi_u32							u32_available_n_logs;
	/** @brief a refernec for the logger start time, this parmater enter the time from start calculations for EVENT based loggers */
	twi_u32							u32_start_time_ref_sec;
	/** @brief Array of All attributes in the logger */
	const tstr_twi_rhp_attr*		apstr_logger_attributes[LOGGER_INVALID_ATTR_INDEX];
	/** @brief number of attributes want to be logged */
	twi_u8							u8_num_attr_to_log;
	/** @brief array of attributes want to be logged */
	const tstr_twi_rhp_attr* const*	ppstr_attribute_to_log;
	/** @brief an array of TWI_IDs to push logs to them. Each element is specified to a destination.
			If the TWI_ID is set to ::INVALID_TWI_ID, the send will be to the connected device's TWI_ID. */
	const tau8_twi_id				* pau8_dest_recv_twi_id;
	/** @brief This attribute holds the structure of the FIFO control for the logger. */
	tstr_twi_fifo_ctrl				str_fifo_ctrl;
	/** @brief last attributes values saved in the flash memory. */
	tstr_twi_rhp_value*				pstr_last_write_value;
#ifdef SAVE_SYSTEM_SETTINGS
	/** @brief This buffer holds the settings that will be saved in the flash memory. */
	twi_u8*		                    pu8_setting_buf;
#endif
}tstr_twi_rhp_logger;

/**
 *	@struct		tstr_twi_loggers_save_settings_info
 *	@brief		Structure that holds the information needed for saving the settings of the loggers.
 */
typedef struct
{
	/** @brief Number of loggers that need to be saved */
	twi_u8	u8_num_save_loggers;

	/** @brief Pointer to array holds the indices of the loggers that need to be saved */
	twi_u8*	pau8_loggers_idx;
}tstr_twi_loggers_save_settings_info;

/**
 *	@struct		tstr_twi_rhp_loggers_in
 *	@brief		structure to  the information for the loggers' module.
 */
typedef struct
{
	/** @brief number of triggers in the system */
	twi_u8									u8_num_loggers;

	/** @brief Array of trigger pointers */
	tstr_twi_rhp_logger* const*				ppstr_loggers;

	/** @brief Pointer to array that holds the attributes of the loggers that need to send */
	tstr_twi_rhp_attr **					appstr_logger_attr_dispatch[OUTPUT_DESTS_NUM];

	/** @brief Structure holds the information needed for save setting for the loggers */
	tstr_twi_loggers_save_settings_info*	pstr_loggers_save_settings;
}tstr_twi_rhp_loggers_in;

/*-**********************/
/*- TRIGGER ------------*/
/*-**********************/

/**
 *	@struct		_tstr_twi_rhp_action
 *	@brief		structure to represent an action
 */
typedef struct
{
	/** @brief index of action in context of trigger */
	twi_u8				u8_action_index;
	/** @brief index of the trigger */
	twi_u8				u8_parent_trigger_index;
	/** @brief type of action to execute */
	tenu_action_type	enu_action_type;
	/** @brief target of the actions */
	union _uni_target
	{
		/** @brief structure that holds the arguments of a send action */
		struct _tstr_alrt_msg_args
		{
			/** @brief 	enumeration that represents type of the status: Push status, Notify Connected Status, or Push and Notify Connected status. */
			twi_const tstr_twi_rhp_value* twi_const			pstr_alrt_msg_type;
			/** @brief ::U8 that represents the channels that will be used to forward this action.
						each bit represents a channel. 0 --> Not a valid channel, 1 --> a valid channel. */
			twi_const twi_u8								u8_output_destinations;
			/** @brief number of attributes in the message to be sent */
			twi_const twi_u8								u8_num_attributes_to_include;
			/** @brief array of pointers to the attributes to include in message */
			twi_const tstr_twi_rhp_attr* twi_const*			ppstr_attributes_to_include;
			/** @brief an array of TWI_IDs. Each element is specified to a destination.
					If the TWI_ID is set to ::INVALID_TWI_ID, the send will be to the connected device's TWI_ID. */
			twi_const tau8_twi_id*							pau8_dest_recv_twi_id;
		} str_alrt_msg_args;
		/** @brief struct to include the arguments of a set action */
		struct _tstr_set_args
		{
			/** @brief The attribute(s) to set */
			union _uni_attr_to_set
			{
				twi_const tstr_twi_rhp_attr*       			pstr_attribute;
				struct _tstr_multiple_attributes
				{
					twi_const twi_u8						u8_attributes_num;
					twi_const tstr_twi_rhp_attr* twi_const*	ppstr_attributes;
				}str_multiple_attributes;
			}uni_attr_to_set;
			/** @brief The value to set it with */
			twi_const tstr_twi_rhp_computed_value*			pstr_computed_value;
		} str_set_args;
		/** @brief structure that holds the arguments of take log action */
		struct _tstr_take_log_args
		{
			tstr_twi_rhp_logger*							pstr_event_based_logger;
		}tstr_take_log_args;
		struct _tstr_adv_beacon_args
		{
			twi_const tstr_twi_rhp_value*					pstr_beacon_idx;
			twi_const tstr_twi_rhp_value*					pstr_min_timeout_sec;
			twi_const tstr_twi_rhp_value*					pstr_max_timeout_sec;
		}str_adv_beacon_args;
		struct _tstr_adv_state_args
		{
			/** @brief ::U8 that represents the channels that will be used to forward this action.
					each bit represents a channel. 0 --> Not a valid channel, 1 --> a valid channel. */
			twi_u8											u8_output_destinations;
			tenu_adv_state  								enu_state;
		}str_adv_state_args;
		/** @brief structure that holds the arguments of a notify app action */
		struct _tstr_notify_app_args
		{
			twi_u8											u8_app_event;
			twi_u8											u8_attrs_num;
			const tstr_twi_rhp_attr*const*					ppstr_attrs;
		}tstr_notify_app_args;
	} uni_target;
} tstr_twi_rhp_action;

/**
 *	@struct		_tstr_twi_rhp_trigger
 *	@brief		structure holds trigger info.
 */
typedef struct
{
	/** @brief index of the trigger in the context of the profile*/
	twi_const twi_u8                                u8_trigger_index;
	/** @brief number of attributes linked to this trigger */
	twi_u8                                          u8_num_attributes_to_update;
	/** @brief number of conditions to evaluate in this trigger  */
	twi_u8                                          u8_num_conditions;
	/** @brief number of actions to execute if trigger evaluates to true */
	twi_u8                                          u8_num_actions;
	/** @brief Rate of applying the actions of the trigger.
	 * If it is ::TRIGGER_APPLY_ACTIONS_SINGLE, the actions will be applied only if it is first time for the trigger's conditions to be true.
	 *  The actions will be applied again in case the trigger's conditions were me to be false then true again.
	 * If it is ::TRIGGER_APPLY_ACTIONS_MULTIPLE, the actions will be applied each time the evaluated trigger's conditions become true.
	 */
	tenu_trigger_actions_applying_rate				enu_actions_applying_rate;
	/** @brief Array of All attributes in the trigger */
	twi_const tstr_twi_rhp_attr*         			apstr_trigger_attributes[TRIGGER_INVALID_ATTR_INDEX];
	/** @brief attributes to read before evaluating the trigger */
	twi_const tstr_twi_rhp_attr* twi_const*    		ppstr_attributes_to_update;
	/** @brief condition type */
	tenu_twi_rhp_condition_type 					enu_condition_type;
	/** @brief array of pointers to conditions to evaluate */
	twi_const tstr_twi_rhp_condition* twi_const*    ppstr_conditions;
	/** @brief array of action pointers to be executed if trigger evaluates to true */
	twi_const tstr_twi_rhp_action* twi_const*       ppstr_actions;
}tstr_twi_rhp_trigger;

/**
 *	@struct		tstr_twi_rhp_trigger_data
 *	@brief		Structure to represent a trigger data
 */
typedef struct
{
	/** @brief The previous state of the trigger. The initial value has to be ::TWI_FALSE. */
	twi_bool 				b_trigger_prev_state;
	/** @brief Alert/Message actions status. Each bit represents an Alert/Message action: 0 -> applied or 1 -> not applied yet. */
	twi_u8					u8_alrt_msg_actions_status;
	/** @brief Pointer to attribute that need to be excluded (because it is the reason of evaluation, to avoid infinite loop)while evaluation time. */
	tstr_twi_rhp_attr*		pstr_exclude_triggered_att;
	/** @brief Timer to be used to evaluate the trigger. */
	tstr_timer_mgmt_timer	str_refresh_timer;
}tstr_twi_rhp_trigger_data;

/**
 *	@struct		tstr_twi_triggers_save_settings_info
 *	@brief		Structure holds the information needed for save setting for the triggers
 */
typedef struct
{
	/** brief Number of triggers that need to be saved */
	twi_u8	u8_num_save_trigs;
	/** brief Save Settings Buffer size */
	twi_u16	u16_save_buf_size;
	/** brief Pointer to array that holds the indices of the triggers that need to be saved */
	twi_u8*	pau8_trigs_idx;
	/** brief Pointer to the array of Triggers' Settings to be saved */
	twi_u8*	pau8_save_trigs_buf;
}tstr_twi_triggers_save_settings_info;

/**
 *	@struct		tstr_twi_rhp_triggers_in
 *	@brief		structure to represent the information for the triggers module.
 */
typedef struct
{
	/** @brief number of triggers in the system */
	twi_u8									u8_num_triggers;
	/** @brief Number of flags for triggers (needed for evaluation triggers / execution actions) */
	twi_u8									u8_num_triggers_flags;
	/** @brief Array of pointers holds the status of each trigger need to be evaluated or not */
	twi_u16 *								pu16_eval_triggers_flag;
	/** @brief Array of pointers holds the status of each trigger need to execute its action or not */
	twi_u16 *								pu16_execute_actions_flag;
	/** @brief Array of trigger pointers */
	const tstr_twi_rhp_trigger*	const*		ppstr_triggers;
	/** @brief Array of triggers data */
	tstr_twi_rhp_trigger_data*				pstr_triggers_data;
	/** @brief Structure holds the information needed for save setting for the triggers */
	tstr_twi_triggers_save_settings_info*	pstr_triggers_save_settings;

}tstr_twi_rhp_triggers_in;

/*-**********************/
/*- STATUS -------------*/
/*-**********************/

/**
 *	@struct		_tstr_twi_rhp_status
 *	@brief		structure to represent a status of a certain profile
 */
typedef struct
{
	/** @brief index of the status in the context of the profile*/
	twi_u8										u8_status_idx;
	/** @brief 	enumeration that represents type of the status: Push status, Notify Connected Status, or Push and Notify Connected status. */
	tenu_rhp_sts_lgr_alrt_msg_type				enu_status_type;
	/** @brief 	U8 that represents the channels that will be used to forward this status.
			each bit represents a channel. 0 --> Not a valid channel, 1 --> a valid channel. */
	twi_const twi_u8							u8_output_destinations;
	/** @brief number of number of attributes in the status message */
	twi_const twi_u8							u8_num_attributes;
	/** @brief Array of All attributes in the status */
	twi_const tstr_twi_rhp_attr*         		apstr_status_attributes[STATUS_INVALID_ATTR_INDEX];
	/** @brief Pointer to the array of pointers to the attributes to include in the status message */
	twi_const tstr_twi_rhp_attr* twi_const*		ppstr_attribute;
	/** @brief an array of TWI_IDs. Each element is specified to a destination.
			If the TWI_ID is set to ::INVALID_TWI_ID, the send will be to the connected device's TWI_ID. */
	twi_const tau8_twi_id						*pau8_dest_recv_twi_id;
	/** @brief Timer to be used to send the status. */
    tstr_timer_mgmt_timer						str_periodic_status_timer;
} tstr_twi_rhp_status;


/**
 *	@struct		tstr_twi_status_save_settings_info
 *	@brief		Structure holds the information needed for save setting for the status
 */
typedef struct
{
	/** brief Number of status that need to be saved */
	twi_u8	u8_num_save_stats;
	/** brief Save Settings Buffer size */
	twi_u16	u16_save_buf_size;
	/** brief Pointer to array that holds the indices of the status that need to be saved */
	twi_u8*	pau8_stats_idx;
	/** brief Pointer to the array of status Settings to be saved */
	twi_u8*	pau8_save_stats_buf;
}tstr_twi_status_save_settings_info;

/**
 *	@struct		tstr_twi_rhp_status_in
 *	@brief		structure to represent the information for the Status module.
 */
typedef struct
{
	/** @brief number of status in the system */
	twi_u8									u8_num_status;
	/** @brief Number of flags for Status (needed for execute the status) */
	twi_u8									u8_num_status_flags;
	/** @brief Array of pointers holds the status of each status need to execute its action or not */
	twi_u8 *								pu8_execute_status_flag;
	/** @brief Array of status pointers */
	tstr_twi_rhp_status* const*				ppstr_status;
	/** @brief Structure holds the information needed for save setting for the status */
	tstr_twi_status_save_settings_info*		pstr_status_save_settings;
}tstr_twi_rhp_status_in;

/*-**********************/
/*- GENERAL ------------*/
/*-**********************/

typedef void(*tpf_twi_rhp_engine_send_cb)(tenu_rhp_direct_send_status enu_send_status, void* pv_evt_data);

typedef struct
{
	/** @brief message type. */
	tenu_twi_rhp_msg_type 		enu_msg_type;
	/** @brief message subtype. */
	tenu_twi_rhp_msg_sub_type	enu_msg_sub_type;
	/** @brief parent index. */
	twi_s16						s16_prnt_idx;
	/** @brief attribute index. */
	twi_s16						s16_attr_idx;
	/** @brief length of value. */
	twi_u16						u16_val_len;
	/** @brief buffer that contains the stringed value. */
	twi_u8*						pu8_val_buf;
}tstr_twi_rhp_msg;

typedef struct
{
	/** @brief pointer to direct message structure. */
	tstr_twi_rhp_msg * pstr_msg_list;
	/** @brief direct msg callback. */
	tpf_twi_rhp_engine_send_cb pf_msg_cb;
}tstr_twi_rhp_send_info;

/**
 *	@struct		_tstr_send_rqst_data
 *	@brief		structure that holds SEND request data
 */
typedef struct
{
	tenu_rhp_rqst_msg_type		enu_msg_type;
	union _uni_msg_data
	{
		struct
		{
			twi_u32 u32_rcv_twi_id;
			const tstr_twi_rhp_send_info* pstr_msg_info;
			twi_u8 u8_num_msg;
		}str_general_msg_data;

		struct _str_alert_msg_data
		{
			twi_u8*					pu8_alrt_msg_actions_status;
			twi_const tstr_twi_rhp_action * pstr_action;
		}str_alert_msg_data;

		tstr_twi_rhp_logger*			pstr_logger;

	}uni_msg_data;
}tstr_send_rqst_data, tstr_undo_send_rqst_data;

/**
 *	@struct		tstr_set_attribute_action_data
 *	@brief		structure that holds set attribute action data
 */
typedef struct
{
	twi_const tstr_twi_rhp_attr * pstr_attr;
	tstr_twi_rhp_value * pstr_value;
}tstr_set_attribute_action_data;

/**
 *	@struct		_tstr_get_sys_status_rqst_data
 *	@brief		structure that holds GET_SYS_STATUS request data
 */
typedef struct _tstr_get_sys_status_rqst_data
{
	tenu_rhp_engine_sys_mode	enu_mode;
	tenu_send_data_type			enu_last_send_type;
	tenu_send_data_type			enu_curr_send_type;
	twi_bool					b_is_last_send_succeeded;
	twi_bool					b_is_sending;
	twi_bool					b_setting_is_saving;
	twi_bool					ab_pending_psh[OUTPUT_DESTS_NUM];
	twi_bool					b_pending_rsp;
	twi_bool					b_pending_app;
}tstr_get_sys_status_rqst_data;

/**
 *	@struct		_tstr_get_fw_version_rqst_data
 *	@brief		structure that holds GET_FW_VERION request data
 */
typedef struct _tstr_get_fw_version_rqst_data
{
	twi_u8	u8_fw_major_version;
	twi_u8	u8_fw_minor_version;
    twi_u8  u8_fw_patch_version;
}tstr_get_fw_version_rqst_data;

/**
 *	@struct		_tstr_notifiy_request
 *	@brief		structure that represents a notification/request to RHP Engine
 */
struct _tstr_notifiy_request
{
	tenu_rhp_request_notify_type	enu_type;
	void*							pv_data;
};

/**
 *	@struct		_tstr_handler_rqst_app
 *	@brief		structure that represents a request from the handler to the app
 */
struct _tstr_handler_rqst_app
{
	tenu_handler_request	        enu_handler;
    twi_u8                          u8_opcode;
	void*							pv_data;
};

/**
 *	@struct		_tstr_twi_rhp_attr
 *	@brief		structure that holds attribute info
 */
struct _tstr_twi_rhp_attr
{
	/** @brief Boolean that indicates if there is any active logger on that attribute or not. */
	twi_bool									b_has_active_loggers;
	/** @brief Index of the attribute inside the parent feature, trigger, or logger */
	twi_const twi_u8							attr_index;
	/** @brief Index of the parent that includes attribute */
	twi_const twi_u8							parent_index;
	/** @brief number of triggers that must be checked when this value is updated */
	twi_u8										u8_num_triggers_on_attribute;
	/** @brief determines the type of this attribute */
    tenu_rhp_attribute_type						enu_attr_type;
	/** @brief determines the permissions of this attribute */
	tenu_permission								enu_permission;
	/** @brief determines the hardware associated with this attribute */
	const tstr_twi_hardware*					pstr_hardware;
	/** @brief pointer to the structure that holds the value of the attribute */
	tstr_twi_rhp_value *						pstr_value;
	/** @brief array of pointers to the triggers to check every time this attribute changes */
	twi_const tstr_twi_rhp_trigger* twi_const*	ppstr_triggers;
};

/**
 *	@struct		tstr_twi_rhp_check_active_loggers
 *	@brief		structure that holds check active loggers action data
 */
typedef struct
{
	twi_const tstr_twi_rhp_attr * pstr_update;
	twi_bool b_result;
}tstr_twi_rhp_check_active_loggers;

/**
 *	@struct		tstr_twi_rhp_read_att
 *	@brief		structure that holds read attribute action data
 */
typedef struct
{
	twi_const tstr_twi_rhp_attr * pstr_update;

}tstr_twi_rhp_read_att;

/**
 *	@struct		tstr_twi_rhp_advertise_beacon
 *	@brief		structure that holds advertise beacon action data
 */
typedef struct
{
	twi_const tstr_twi_rhp_action * pstr_action;

}tstr_twi_rhp_advertise_beacon;

/**
 *	@struct		tstr_twi_rhp_dst0_cmds_list
 *	@brief		structure represents DST0 command list configuration
 */
typedef struct
{
	/** @brief 	Enum that represents the type of the following list allowed command or un-allowed command in the running mode. */
	const tenu_rhp_dst0_cmds_list_type enu_cmds_list_type;

	/** @brief number of number of Command Allowed or Un-Allowed in the running mode. */
	const twi_u16 u16_num_cmds;

	/** @brief Pointer to the list of Allowed or Un-Allowed Msgs in the running mode.
	 *  		If this list is NULL, this means that all commands are Allowed or Un-Allowed based on the list type.
	 */
	const tstr_twi_rhp_msg* const* ppstr_msg_list;
} tstr_twi_rhp_dst0_cmds_list;

/**
 *	@struct		_tstr_twi_rhp_profile
 *	@brief		structure to represent the profile of the device
 */
typedef struct
{
	/** @brief Flag that define if that profile will start in the deep sleep mode or not */
	twi_bool							b_start_in_deep_sleep;
	/** @brief number of total attributes to dispatch on in this profile */
	twi_u8								u8_num_attr_in_dispatch;
	/** @brief Pointer holds the string of the FirmWare major version */
	twi_u8								u8_fw_major_version;
	/** @brief Pointer holds the string of the FirmWare minor version */
	twi_u8 								u8_fw_minor_version;
    /** @brief Pointer holds the string of the FirmWare patch version */
    twi_u8                              u8_fw_patch_version;
	/** @brief globally unique profile identifier */
	twi_u16								u16_profile_id;
	/** @brief pointer to the Status IN structure */
	const tstr_twi_rhp_status_in*		pstr_status_in;
	/** @brief RHP Hardware IN module. */
	const tstr_twi_rhp_hardware_in*		pstr_hardware_in;
	/** @brief Pointer to structure  that holds all information for the trigger module */
	const tstr_twi_rhp_triggers_in *	pstr_triggers_in;
	/** @brief RHP Logger IN module. */
	const tstr_twi_rhp_loggers_in*		pstr_loggers_in;
	/** @brief RHP Report IN module. */
	const tstr_twi_rhp_reports_in*		pstr_reports_in;
	/** @brief number of exceptions messages in the manufacturing */
	twi_u8								u8_num_mnfctr_except;
	/** @brief Array of exceptions messages in the manufacturing */
	const tstr_twi_rhp_msg*	const*		ppstr_mnfctr_except;
	/** @brief number of exceptions messages in the pairing */
	twi_u8								u8_num_pair_except;
	/** @brief Array of exceptions messages in the pairing */
	const tstr_twi_rhp_msg*	const*		ppstr_pair_except;
	/** @brief array of responses to include in response */
	tstr_twi_rhp_resp *					pstr_responses_queue;
	/** @brief Pointer holds structure to the cofig of DST0 CMDs  */
	const tstr_twi_rhp_dst0_cmds_list * pstr_dst0_cmds_confg;
} tstr_twi_rhp_profile;

/**
 *	@struct		_tstr_twi_scanned_dvc
 *	@brief		structure to represent the info of BLE device RHP may use in its applications
 */
 
TWI_PACK(typedef struct 
{
	twi_u8	au8_dvc_ble_addr[DVC_BLE_ADDR_SIZE];
	twi_u8	u8_dvc_ble_addr_type;
	twi_u8	au8_dvc_twi_id[DVC_TWI_ID_SIZE];
	twi_u8	au8_profile_id[PROFILE_ID_SIZE];
	twi_u8	au8_srvc_uuid[DVC_UUID16_SIZE];
	twi_s8	s8_dvc_rssi;
	tenu_scan_node_type enu_dvc_type;	/** @brief gateway or peripheral*/
	twi_u8	au8_adv_uuid[DVC_UUID128_SIZE];
}) tstr_scanned_ble_dvc;

/**
 *	@struct		_tstr_twi_guarded_ble_dvc
 *	@brief		structure to represent the info of BLE device with boolean lock
 */
 
TWI_PACK(typedef struct 
{
	tstr_scanned_ble_dvc 	str_scanned_dvc;
	twi_bool 				b_locked;
}) tstr_twi_guarded_ble_dvc;
/**
 *	@struct		_tstr_twi_ble_adv_data
 *	@brief		structure to represent the Ble advertise data
 */
TWI_PACK(typedef struct  _tstr_twi_ble_adv_data
{
	twi_u8 *	pu8_twi_srvc_128_data_mode_2_info ;
	twi_u8		u8_twi_srvc_128_data_mode_2_info_sz;
	twi_u8 *    pu8_twi_manu_data_mode_2_info ;
	twi_u8 		u8_twi_manu_data_mode_2_info_sz ;
	twi_u8 *	pu8_scan_response_data;
	twi_u8		u8_scan_response_data_sz;		
})tstr_twi_ble_perpheral_adv_data;
/** @} */ /* TWI_RHP_TYPES_group*/
#endif /* TWI_RHP_TYPES_H_ */
