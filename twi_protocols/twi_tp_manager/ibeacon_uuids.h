/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 * @file	ibeacon_uuids.h
 *	@brief	This file contains Basic UUIDs needed.
 */
 

#ifndef _IBEACON_UUIDS_H_
#define _IBEACON_UUIDS_H_

/*-**********************************************************/
/*- INCLUDES -----------------------------------------------*/
/*-**********************************************************/

#include "twi_types.h"
#include "twi_sas_ids.h"
#include "twi_ble_hal_conf.h"
#include "twi_common.h"

/*-**********************************************************/
/*- CONSTANTS ----------------------------------------------*/
/*-**********************************************************/

#define	UUIDS_NUMBER						5														/**< @brief	This is the number of UUIDs declared in this file.*/
						
#define UUID16_SIZE							2														/**< @brief	Size of 16-bit UUID. */
#define UUID128_SIZE						16														/**< @brief	Size of 128-bit UUID.*/

#define BEACON_DEVICE_TYPE               	0x02													/**< @brief 0x02 refers to beacon. */
#define BEACON_ADV_DATA_LENGTH           	0x15													/**< @brief	Length of manufacturer specific data in the advertisement. */
#define BEACON_INFO_LENGTH        			sizeof(tstr_twi_ibeacon_info)							/**< @brief	Total length of information advertised by the beacon. */
#define BEACON_MAJOR_VALUE               	0x00, 0x00												/**< @brief	Major value used to identify beacons. */
#define BEACON_MINOR_VALUE               	0x00, 0x00												/**< @brief	Minor value used to identify beacons. */
#define BEACON_ONE_METER_PASS_LOSS			70														/**< @brief	Pass Loss in One Meter: L = 30 + 20 log(4 * pi * d / lamda)*/
#define BEACON_MEASURED_RSSI             	TWI_BLE_DEFAULT_TX_POWER - BEACON_ONE_METER_PASS_LOSS	/**< @brief	The beacon's measured RSSI at 1 meter distance in dBm. */
#define COMPANY_IDENTIFIER_APPLE			((twi_u16) 0x004C)										/**< @brief	Company identifier for Apple. Required for Beacons */
#define COMPANY_IDENTIFIER_INSULET			((twi_u16) 0x0360)										/**< @brief	Company identifier for Apple. Required for Beacons */
#define COMPANY_IDENTIFIER_TWI				((twi_u16) 0x0772)										/**< @brief	Company identifier for Apple. Required for Beacons */
#define COMPANY_IDENTIFIER_LENGTH			(2)

/*	There is Data/Alert UUID bit form: A - Alert, D - Data:
 *+------+----------+-----------+---------------------------------------------------------------------+
 *	Byte:|	0 - 11	|	12 - 13	|								14 - 15							  	  |	
 *+------+----------+-----------+----+----+----+----+----+----+---+---+---+---+---+---+---+---+---+---+
 *	Bits:|    ALL   |    ALL    | 15 | 14 | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 *+------+----------+-----------+----+----+----+----+----+----+---+---+---+---+---+---+---+---+---+---+
 *		 | 			|  			|  A |  D |  A |  D |  A |  D | A | D |	  | A | D | A | D | A | D |	  |
 *		 | Constant	|  App Word +----+----+----+----+----+----+---+---+RSV+---+---+---+---+---+---+TMP|
 *		 |			|			|  DEST6  |  DEST5  |  DEST4  | DEST3 |	  | DEST2 | DEST1 | DEST0 |	  |
 *+------+----------+-----------+---------+---------+---------+-------+---+-------+-------+-------+---+
 */
 
#define UUID_TEMP_BIT_POS								(0)
#define UUID_DEST_BITS_POS(u8_dest_idx)					(((u8_dest_idx) < 3)? (((u8_dest_idx) << 1) + 1) : (((u8_dest_idx) - 3) << 1))
#define UUID_DEST_DATA_BIT_POS(u8_dest_idx)				(UUID_DEST_BITS_POS(u8_dest_idx))
#define UUID_DEST_ALERT_BIT_POS(u8_dest_idx)			(UUID_DEST_BITS_POS(u8_dest_idx) + 1)

#define UUID_TEMP_BYTE_IDX								(15)
#define UUID_DEST_BYTE_IDX(u8_dest_idx)					(((u8_dest_idx) < 3)? 15 : 14)
#define UUID_DEST_LSB_IDX								15
#define UUID_DEST_MSB_IDX								14

/* this is the data info structure in twiBeacon
+--+----+----+----+----+--------------------------
 *		1 byte
 *---+----+----+----+-----------------------------
 *|  3 bits 	|  2 bits 	 |  3 bits
 *---+----+----+----+-----------------------------
 *|  Version 	| TWI ID LEN | Reserved
 *---+----+----+----+-----------------------------
*/
#define TWI_BEACON_COMPOS_INFO(VER)						( (VER << 5)| ( ( TWI_ID_SIZE >> 3) << 3) )

/*	There is TP Service ID form for Data/Alert:	A - Alert, D - Data:
 *+------+---------+----+----+----+----+---+---+---+---+---+---+---+---+---+---+
 *	Bits:|  15-14  | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 *+------+---------+----+----+----+----+---+---+---+---+---+---+---+---+---+---+
 *		 |		   |  A |  D |  A |  D | A | D | A | D | A | D | A | D | A | D |
 *Value: |    11   +----+----+----+----+---+---+---+---+---+---+---+---+---+---+
 *		 |		   |  DEST6  |  DEST5  | DEST4 | DEST4 | DEST2 | DEST1 | DEST0 |
 *+------+---------+----+----+----+----+---+---+---+---+---+---+---+---+---+---+
 */
#define SERVICE_ID_DEST_BITS_POS(u8_dest_idx)			((u8_dest_idx) << 1)
#define SERVICE_ID_DEST_DATA_BIT_POS(u8_dest_idx)		(SERVICE_ID_DEST_BITS_POS(u8_dest_idx))
#define SERVICE_ID_DEST_ALERT_BIT_POS(u8_dest_idx)		(SERVICE_ID_DEST_BITS_POS(u8_dest_idx) + 1)

#define UUID_PROFILE_DEFINED_WORD_MSB_IDX				12
#define UUID_PROFILE_DEFINED_WORD_LSB_IDX				13
#define NDS_UUID_APP_DEFINED_WORD_MSB_IDX				14
#define NDS_UUID_APP_DEFINED_WORD_LSB_IDX				15
#define NUDGE_UUID_APP_DEFINED_WORD_MSB_IDX				14
#define NUDGE_UUID_APP_DEFINED_WORD_LSB_IDX				15
#define GDC_UUID_APP_DEFINED_WORD_MSB_IDX				14
#define GDC_UUID_APP_DEFINED_WORD_LSB_IDX				15
#define DES_UUID_APP_DEFINED_WORD_MSB_IDX				14
#define DES_UUID_APP_DEFINED_WORD_LSB_IDX				15

#define DEFAULT_UUID_PROFILE_DEFINED_WORD				0xFFFE
#define DEFAULT_ADV_BEACON_APP_WORD						0x2A07

#define MAX_ADV_MANFC_APP_SPEC_LEN				23 - TWI_ID_SIZE

#if defined(NURSE_TAG) || defined(CREDIT_CARD)

#define BLE_NDS_BEACON_UUID					0x71, 0xB1, 0x89, 0xEE,	\
											0x25, 0x2A, 0x4C, 0x78,	\
											0x86, 0xA3, 0x3E, 0xDE,	\
											0x00, 0x00, 0x00, 0x00 		/**< @brief	NoData Ranging Beacon */
#else
/* Bytes 10-11 are common in all beacons and equals 7C:2A. These bytes make these beacons unique from the old version ones. */
#define BLE_NDS_BEACON_UUID					0x4E, 0x54, 0xFD, 0x0F, \
											0xD2, 0x70, 0x4D, 0x04, \
											0x98, 0x38, 0x7C, 0x2A, \
											0x00, 0x00, 0x00, 0x00 		/**< @brief	NoData Ranging Beacon */
#endif

#define BLE_AS_DS_BEACON_UUID				0x95, 0xA1, 0x89, 0xEE, \
											0x25, 0x2A, 0x4C, 0x78, \
											0x86, 0xA3, 0x7C, 0x2A, \
											0x00, 0x00, 0x00, 0x00		/**< @brief	AS and/or DS basic and/or temp Beacons */

#define BLE_NUDGE_BEACON_UUID				0xCF, 0x8B, 0x00, 0x01, \
											0x18, 0xF3, 0xA1, 0xB7, \
											0x4B, 0x6E, 0x7C, 0x2A, \
											0x00, 0x00, 0x00, 0x00		/**< @brief	Nudge Beacon */

#define BLE_NS_NST_BEACON_UUID				0xD7, 0x77, 0x02, 0x45, \
											0xBE, 0x6B, 0x40, 0x48, \
											0x88, 0x16, 0x7C, 0x2A, \
											0x00, 0x00, 0x77, 0xF0, 	/**< @brief	NS and/or NST Ranging Beacon */


#define BLE_INITIAL_DATA_ALERT_UUID_SERVICE	0xC000
#define BLE_NO_DATA_UUID_SERVICE			0x2470

#if (TWI_APP_ADV_DATA_LEN  <= MAX_ADV_MANFC_APP_SPEC_LEN)
	#if( (TWI_APP_ADV_DATA_LEN % 2) == 0)
		#if (TWI_APP_ADV_DATA_LEN > 0)
			#define TWI_APP_ADV_DATA_SIZE         TWI_APP_ADV_DATA_LEN
		#else
			#define TWI_APP_ADV_DATA_SIZE
		#endif
	#else
		#error "APP DATA IS NOT DIVISIBLE BY 2"
	#endif
#else
	#error "Greater Than Adv Manufc Data Len"
#endif

/*-**********************************************************/
/*------------ STRUCTS AND UNIONS --------------------------*/
/*-**********************************************************/

/**
*	@struct		tstr_twi_ibeacon_info
*	@brief		structure that holds information of iBeacon data
*/
TWI_PACK(typedef struct
{
	twi_u8			u8_data_type;				/**<@brief This is represent advertising data type, 0x02 is used*/
	twi_u8			u8_adv_data_len;			/**<@brief Length of manufacturer specific data in the advertisement. */
	twi_u8 	    au8_uuid[UUID128_SIZE];		/**<@brief UUID of beacon data.*/
	twi_u16 		u16_major;					/**<@brief Major value used to identify beacons. */
	twi_u16 		u16_minor;					/**<@brief Minor value used to identify beacons. */
	twi_s8   		s8_measured_rssi;			/**< The beacon's measured RSSI at 1 meter distance in dBm. */
})tstr_twi_ibeacon_info;

/**
*	@struct		tstr_twi_twiBeacon_info
*	@brief		structure that holds information of twi beacon data
*/
TWI_PACK(typedef  struct
{
	twi_u16			u16_data_info;											/**<@brief This is represent advertising data info |3 bits version|2 bits TWI ID LEN|3 bits RESEVE| */
	twi_u16 		u16_profile_id;											/**<@brief product profile id. */
	twi_u8 			u8_dstn_status_lsb;										/**<@brief dstn alert/data type lsb. */
	twi_u8 			u8_dstn_status_msb;										/**<@brief dstn alert/data type msb. */
	twi_u8 			au8_twi_id[TWI_ID_SIZE];								/**<@brief TWI ID. */
	twi_u8			au8_app_spec_data[TWI_APP_ADV_DATA_SIZE ];                /**<@brief Application Specific data needed to be advertised. */
})tstr_twi_twiBeacon_info;

/**
*	@struct		tstr_twi_scan_rspns_mode_1_info
*	@brief		structure that holds information of twi scan response mode_1
*/
TWI_PACK(typedef struct
{
	twi_u16			u16_uuid_service;							/**<@brief uuid serivce*/
	twi_u16 		u16_service_id;								/**<@brief serive id*/
	twi_u16 		u16_profile_id;								/**<@brief product profile id. */
	twi_u16 		u16_device_serial_msb;						/**<@brief device serial (TWI_ID) LSB*/
	twi_u16 		u16_device_serial_lsb;						/**<@brief device serial (TWI_ID) MSB*/
	twi_u16			au16_spec_data[TWI_SCAN_RESP_APP_SPEC_MAX_LEN];	/**<@brief specific_data*/

	twi_u8			u8_length_spec_data;	/**<@brief length of used specific_data*/
})tstr_twi_scan_rspns_mode_1_info;


#endif /* _IBEACON_UUIDS_H_ */
