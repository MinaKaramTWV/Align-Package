/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

#ifndef TWI_BLE_HAL_CONF_H_
#define TWI_BLE_HAL_CONF_H_
/****************************************************************************/
/**
 ** @file					twi_ble_hal_conf.h
 ** @brief					This file holds the BLE-HAL configurations that are needed by the BLE-HAL user.
 **
 */
/*-*********************************************************/
/*- INCLUDES -------------------------------------------*/
/*-*********************************************************/

/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------*/
/*-*********************************************************/

#ifndef TWI_APP_DEVICE_NAME
#define	TWI_APP_DEVICE_NAME           		"TWI BOARD"
#endif

/*
 *  Configuration parameter, it indicates the Number of Central Links, i.e Kit operating as Central Role
 *  This number will affect the calculation of RAM Usage of SoftDevice, so we need to recalculate the memory
 *  and update it in the Linker Directive file.
 */
#define	CENTRAL_LINK_COUNT					1

/*
 * Configuration parameter, it indicates the Number of Peripheral Links, i.e Kit Operating as Peripheral Role
 * This number will affect the calculation of RAM Usage of SoftDevice, so we need to recalculate the memory
 *  and update it in the Linker Directive file.
 */
#define	PERIPHERAL_LINK_COUNT				1

#define CENTRAL_SEC_COUNT					1

#ifdef REGRESSION_TEST

	#define	TWI_BLE_DEFAULT_TX_POWER		TWI_BLE_MIN_TX_POWER

#else

	#define	TWI_BLE_DEFAULT_TX_POWER		TWI_BLE_MAX_TX_POWER

#endif

#define TWI_BLE_DEFAULT_ADV_INTERVAL_MS		760		/* 760 ms, BLE Advertising Rate in MS as per BLE standard (20 ms:10.24 Seconds).  */
#define TWI_BLE_DEFAULT_ADV_REPEAT_S		0		/* 0 seconds, BLE Repeat Rate in Seconds, repeat the advertising each Repeat Interval, if 0 Continue Advertising. */
#define TWI_BLE_DEFAULT_PKTS_NUMBER			0		/* 0 packets,  Number of BLE packets each repeat interval, no meaning id case of Repeat interval is 0. */

#define TWI_BLE_DEFAULT_ADV_TYPE			TWI_BLE_ADV_CONN

/* Scanning parameters Default Values */
#define	DEFAULT_SCAN_TIMEOUT				2000						/**< Determines scan ON/OFF interval in units of milli seconds.*/
#define	DEFAULT_SCAN_INTERVAL               0x00A0                  /**< Determines scan interval in units of 0.625 millisecond. this is 100 ms */
#define	DEFAULT_SCAN_WINDOW                 0x0050                  /**< Determines scan window in units of 0.625 millisecond. this is 50 ms */

/* Connection Scanning parameters Values */
#define	CONN_SCAN_INTERVAL              	0x0078              			    /**< Determines scan interval in units of 0.625 millisecond. this is 75 ms */
#define	CONN_SCAN_WINDOW                	0x0078              			    /**< Determines scan window in units of 0.625 millisecond. this is 75 ms */
#define	CONN_SCAN_TIMEOUT_MS               	(1000)								/**< Determines scan timeout in units of milli seconds.*/
#define	CONN_SCAN_TIMEOUT                	(CONN_SCAN_TIMEOUT_MS / 1000)		/**< Determines scan timeout in units of seconds.*/
/* Connection parameters default values*/
#define DEFAULT_CEN_MIN_CONNECTION_INTERVAL     (75)					/**< Determines central maximum connection interval in millisecond MULTIPLIED BY 10. */
#define DEFAULT_CEN_MAX_CONNECTION_INTERVAL     (500)					/**< Determines central maximum connection interval in millisecond MULTIPLIED BY 10. */
#define DEFAULT_CEN_SLAVE_LATENCY           	0						/**< Determines central slave latency in counts of connection events. */
#define DEFAULT_CEN_SUPERVISION_TIMEOUT        	(200)             		/**< Determines central supervision time-out in units of 10 millisecond. */

#define DONT_CARE_CONN_PARAM						(0xFFFF)			/**<If any connection parameter equals to this value, that means it keeps the current connection parameter as it is. */

#define CLASSIC_MODE_PER_MIN_CONN_INTRVAL_10XMSEC		(250)
#define CLASSIC_MODE_PER_MAX_CONN_INTRVAL_10XMSEC		(500)

#define FAST_MODE_PER_MIN_CONN_INTRVAL_10XMSEC			(DONT_CARE_CONN_PARAM)
#define FAST_MODE_PER_MAX_CONN_INTRVAL_10XMSEC			(DONT_CARE_CONN_PARAM)

#define DEFAULT_SLAVE_LATENCY           		(0)						/**< Determines slave latency in counts of connection events. */
#define DEFAULT_SUPERVISION_TIMEOUT        		(500)             		/**< Determines supervision time-out in units of 10 millisecond. */


#ifndef DEFAULT_CONN_MGMT_MIN_CONN_INTRVAL_10XMSEC
	#define	DEFAULT_CONN_MGMT_MIN_CONN_INTRVAL_10XMSEC		FAST_MODE_PER_MIN_CONN_INTRVAL_10XMSEC
#endif

#ifndef	DEFAULT_CONN_MGMT_MAX_CONN_INTRVAL_10XMSEC
	#define	DEFAULT_CONN_MGMT_MAX_CONN_INTRVAL_10XMSEC		FAST_MODE_PER_MAX_CONN_INTRVAL_10XMSEC
#endif

#ifndef DEFAULT_CONN_MGMT_SLAVE_LATENCY
	#define DEFAULT_CONN_MGMT_SLAVE_LATENCY					DEFAULT_SLAVE_LATENCY
#endif

#ifndef DEFAULT_CONN_MGMT_SUPERVISION_TIMEOUT_MSEC
	#define	DEFAULT_CONN_MGMT_SUPERVISION_TIMEOUT_MSEC		(DEFAULT_SUPERVISION_TIMEOUT*10)
#endif

#if defined(TWI_CONN_PARAM_MGMT) || defined (TWI_HW_BLE_FULL_FUNCTION)
#define CONNECTION_PARAM_LEN			(8)
#endif

#define	TWI_BLE_MIN_TX_POWER				PLATFORM_BLE_MIN_TX_PWR			/**< -30 dbm, This is the minimum transmission power, used in case of regression test only.*/
#define	TWI_BLE_MAX_TX_POWER				PLATFORM_BLE_MAX_TX_PWR			/**< +4 dbm, This is Radio transmit power in dBm, This value will limit the range of BLE.*/

/**< The advertising interval for connect-able advertisement. This value can vary between 0x0020 and 0x4000 in 0.625 ms units (20ms to 10.24s). */
#define	TWI_BLE_MIN_ADV_INT					PLATFORM_BLE_MIN_ADV_INT_MS				/* 20ms */
#define	TWI_BLE_MAX_ADV_INT					PLATFORM_BLE_MAX_ADV_INT_MS				/* 10 sec */

/**< 4 bytes for minor and major(adv data) in advertising. */
#define TWI_ADV_DATA_LEN					4

#define	APP_TIMER_PRESCALER					0

/**< Time for which the device must be advertising in connect-able mode (in seconds). 0 disables time-out. */
#define TWI_APP_ADV_TIMEOUT_IN_SECS  		0			/* So the advertising doesn't run out */

#if defined(nordic_sdk_16_0_0)
#define TWI_APP_ADV_TIMEOUT_IN_10_MSECS 	0 			/* So the advertising doesn't run out */
/**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (20 seconds). */
#define FIRST_CONN_PARAMS_UPDATE_DELAY  	APP_TIMER_TICKS(20000)
/**< Time between each call to sd_ble_gap_conn_param_update after the first call (5 seconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY   	APP_TIMER_TICKS(5000)
#else
/**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (20 seconds). */
#define FIRST_CONN_PARAMS_UPDATE_DELAY  	APP_TIMER_TICKS(20000, APP_TIMER_PRESCALER)
/**< Time between each call to sd_ble_gap_conn_param_update after the first call (5 seconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY   	APP_TIMER_TICKS(5000, APP_TIMER_PRESCALER)
#endif
/**< Number of attempts before giving up the connection parameter negotiation. */
#define MAX_CONN_PARAMS_UPDATE_COUNT   	 	0
/**< length of scan response. */
#define BEACON_SCAN_RES_LENGTH				5
/**< Max length of scan response app specific. */
#define TWI_SCAN_RESP_APP_SPEC_MAX_LEN		(9)

#define TWI_MAX_ADV_DATA_LEN_BYTES			(31)
#define TWI_MAX_SCN_RSP_DATA_LEN_BYTES		(31)
#define LENGTH_PLUS_TYPE_ADV_BYTES_LEN		(2)		/*1st byte: length of the element (excluding the length byte itself)
 	 	 	 	 	 	 	 	 	 	 	 	 	  2nd byte: AD type � specifies what data is included in the element*/



#define TWI_MAX_GATT_SERVICES				(1)
#define TWI_MAX_GATT_CHARS					(0)
#define TWI_MIN_MTU_GATT_CHARS				(1)
#define TWI_MAX_MTU_GATT_CHARS				(2)
#define TWI_MAX_GATT_NOTIFY_INDICATE_CHARS	(3)
#define TWI_MAX_GATT_128_BIT_UUID_CHARS		(3)
#define TWI_MAX_GATT_16_BIT_UUID_CHARS		(0)
#define TWI_MAX_GATT_ATTRIBUTES				(	2*TWI_MAX_GATT_CHARS					+\
												3*TWI_MAX_GATT_NOTIFY_INDICATE_CHARS	)

/* The used Resolutions in BLE HALs*/
#define TWI_RESOLUTION_1_25			1250
#define TWI_RESOLUTION_0_625		625
#define TWI_RESOLUTION_10			10000

/**@brief To convert milliseconds to ticks.
 * @param[in] TIME          Number of milliseconds to convert.
 * @param[in] RESOLUTION    Unit to be converted to in [us/ticks]. (RESOLUTION = Real_resolution*1000). This means resolution of 0.625 = 625.
 */
#define TWI_MSEC_TO_UNITS(TIME, RESOLUTION) (((TIME) * 1000) / (RESOLUTION))

/**@brief To convert ticks to milliseconds.
 * @param[in] UINTS          Number of ticks to convert.
 * @param[in] RESOLUTION    Unit to be converted to in [us/ticks]. (RESOLUTION = Real_resolution*1000). This means resolution of 0.625 = 625.
 */
#define TWI_UINTS_TO_MSEC(UINTS, RESOLUTION) (((RESOLUTION) * (UINTS)) / (1000))
/*
 * Recommended parameters by Apple:
 * --------------------------------
 * -> Interval Max * (Slave Latency + 1) =< 2 seconds
 * -> Interval Min => 20 ms
 * -> Interval Min + 20 ms =< Interval Max Slave Latency =< 4
 * -> connSupervisionTimeout =< 6 seconds
 * -> Interval Max * (Slave Latency + 1) * 3 < connSupervisionTimeout
 * For more details refer to: https://developer.apple.com/hardwaredrivers/BluetoothDesignGuidelines.pdf
 *
 * Recommended parameters with Nordic Chip:
 *------------------------------------
 * (1 + Conn_Latency) * Conn_Interval_Max * 2 < Supervision_Timeout where: Supervision_Timeout & Conn_Interval_Max are in milliseconds
 * For more details refer to: https://developer.nordicsemi.com/nRF51_SDK/nRF51_SDK_v8.x.x/doc/8.0.0/s110/html/a00220.html
 */
 
#define MIN_CONN_INTERVAL               TWI_MSEC_TO_UNITS(25, TWI_RESOLUTION_1_25)           /*< Minimum acceptable connection interval (0.025 seconds).*/
#define MAX_CONN_INTERVAL               TWI_MSEC_TO_UNITS(1900, TWI_RESOLUTION_1_25)         /*< Maximum acceptable connection interval (1.9 second).*/
#define SLAVE_LATENCY                   0                                         		     /*< Slave latency.*/
#define CONN_SUP_TIMEOUT                TWI_MSEC_TO_UNITS(6000, TWI_RESOLUTION_10)           /*< Connection supervisory timeout (5 seconds).*/

#if ((defined (S132)) || (defined(NXP_QN908X)) || (defined(BLUENRG2_DEVICE)))
#define TWI_BLE_GATT_MTU_SIZE			247
#else
#define TWI_BLE_GATT_MTU_SIZE			23
#endif
#define TWI_BLE_LL_MAX_PDU_SIZE			251
#define BLE_GATT_HEADER_LEN				3
#define BLE_MAC_ADDR_LEN                6

#define BLE_UUID_BASE                    0x5F, 0xDC, 0xD0, 0x03,\
                                            0x1E, 0x75, 0x7E, 0x8B,\
                                            0x64, 0x44, 0xED, 0xE3,\
                                            0x5F, 0x73, 0x7E, 0x1A,     /**< @brief TP Service 128-UUID */


#endif /*TWI_BLE_HAL_CONF_H_*/
