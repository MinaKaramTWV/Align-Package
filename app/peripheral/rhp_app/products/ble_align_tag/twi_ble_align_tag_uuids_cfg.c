/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/*
 * twi_nfc_ble_align_tag_cfg.c
 *
 */

 /*-*********************************************************/
/*- INCLUDES ----------------------------------------------*/
/*-*********************************************************/
#include "twi_rhp_ble_align_tag.h"

/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------------*/
/*-*********************************************************/
// #define OPP_NDS_UUID_CNT					1						/**< This is the number of advertising UUIDs.*/
// /*-**********************************************************/
// /*- Global Variables ---------------------------------------*/
// /*-**********************************************************/

// twi_const	twi_u8							eu8_nudge_uuids_number			= OPP_NUDGE_UUID_CNT;
// twi_const	twi_u8							eu8_nudge_min_timeout_sec		= 5;
// twi_const	twi_u8							eu8_nudge_max_timeout_sec		= 5;

/*
 *	These Variables are used in twi_tp_ble_conn.c
 *	As Configuration for disconnection time-out
 *	for both peripheral and central
 * */
twi_const	twi_u8							eu8_per_idle_timeout			= PER_IDLE_TIMEOUT;
twi_const	twi_u8							eu8_cen_idle_timeout			= CEN_IDLE_TIMEOUT;

// twi_const	tenu_twi_aml_smart_mode			eenu_conf_aml_smart_mode 		= AML_SMART_MODE_OFF;
// twi_const 	tenu_twi_aml_modes				eenu_aml_defualt_mode 			= AML_MODE_RF_ON; 		

// twi_const 	twi_u16 						eu16_uuid_profile_defined_word	= PROFILE_ID;


// #if (TWI_ADV_MODE == TWI_ADV_MODE_1) || (TWI_ADV_MODE == TWI_ADV_MODE_BOTH)
// tstr_twi_ibeacon_info	str_apple_beacon =		/**< @brief Structure that holds beacon data.*/
// {
// 	.u8_data_type 		= BEACON_DEVICE_TYPE,
// 	.u8_adv_data_len	= BEACON_ADV_DATA_LENGTH,
// 	.au8_uuid			= {BLE_NDS_BEACON_UUID},
// 	.u16_major			= BEACON_MAJOR_VALUE,
// 	.u16_minor			= BEACON_MINOR_VALUE,
// 	.s8_measured_rssi	= BEACON_MEASURED_RSSI
// };

// tstr_twi_manu_data str_apple_manuf =
// {
// 	.u16_company_identifier = COMPANY_IDENTIFIER_APPLE,
// 	.u16_manu_data_sz = sizeof(str_apple_beacon),
// 	.pu8_manu_data = (twi_u8*)&str_apple_beacon,
// };

// CRITICAL_VAR tstr_twi_adv_data str_apple_adv_data =
// {
// 	.pu8_manu_adv_data = (twi_u8*)&str_apple_manuf,
// 	.u8_manu_adv_data_size = sizeof(str_apple_beacon) + COMPANY_IDENTIFIER_LENGTH,
// 	.enu_adv_name_type = TWI_BLE_ADVDATA_NO_NAME,
// 	.u8_incomplete_16uuid_size = 0,
// 	.u8_complete_16uuid_size = 0,
// 	.u8_incomplete_128uuid_size = 0,
// 	.u8_complete_128uuid_size = 0,
// 	.pu8_device_name = NULL,
// 	.pu8_complete_16uuid = NULL,
// 	.pu8_incomplete_16uuid = NULL,
// 	.pu8_complete_128uuid = NULL,
// 	.pu8_incomplete_128uuid = NULL,
// };

// tstr_twi_twiBeacon_info str_twi_beacon ={
// 		.u16_data_info = TWI_APP_ADV_DATA_INFO,
// 		.u16_profile_id = PROFILE_ID,
// 		.u8_dstn_status_msb = 0,
// 		.u8_dstn_status_lsb = 0,
// };

// CRITICAL_VAR tstr_twi_adv_data str_service_uuid_adv_data =
// {
// 	.pu8_complete_16uuid = (twi_u8*)&str_twi_beacon,
// 	.u8_complete_16uuid_size = sizeof(str_twi_beacon),
// 	.enu_adv_name_type = TWI_BLE_ADVDATA_NO_NAME,
// 	.u8_incomplete_16uuid_size = 0,
// 	.u8_manu_adv_data_size = 0,
// 	.u8_incomplete_128uuid_size = 0,
// 	.u8_complete_128uuid_size = 0,
// 	.pu8_device_name = NULL,
// 	.pu8_manu_adv_data = NULL,
// 	.pu8_incomplete_16uuid = NULL,
// 	.pu8_complete_128uuid = NULL,
// 	.pu8_incomplete_128uuid = NULL,

// };

// /*
//  * @brief  this array contains the beacons that are advertised by opportunistic*/

// tstr_twi_adv_data* epastr_adv_data_list[] =
// {
// 	&str_apple_adv_data,
// };

// #ifndef TWI_BLE_DISABLE_SCAN_RESPONSE
// tstr_twi_scan_rspns_mode_1_info str_twi_scan_rspns_mode_1_info;

// tstr_twi_adv_data str_scan_response_data =
// {
// 	.pu8_complete_16uuid = (twi_u8*)&str_twi_scan_rspns_mode_1_info,
// 	.u8_complete_16uuid_size = BEACON_SCAN_RES_LENGTH * UUID16_SIZE,
// 	.enu_adv_name_type = TWI_BLE_ADVDATA_NO_NAME,
// 	.u8_incomplete_16uuid_size = 0,
// 	.u8_manu_adv_data_size = 0,
// 	.u8_incomplete_128uuid_size = 0,
// 	.u8_complete_128uuid_size = 0,
// 	.pu8_device_name = NULL,
// 	.pu8_manu_adv_data = NULL,
// 	.pu8_incomplete_16uuid = NULL,
// 	.pu8_complete_128uuid = NULL,
// 	.pu8_incomplete_128uuid = NULL,
// };
// #endif
// /*
//  * @brief  this array contains the beacons the scan response will be advertised by opportunistic
//  * */

// tstr_twi_adv_data* epstr_scan_response =
// #ifndef TWI_BLE_DISABLE_SCAN_RESPONSE
// 		&str_scan_response_data;
// #else
// 		NULL;
// #endif


// const twi_u8 eu8_num_beacons 			= TWI_ARRAY_LEN(epastr_adv_data_list);

// #endif


// /***************************************** Advertising Mode 2 ******************************************************************/
// #if (TWI_ADV_MODE == TWI_ADV_MODE_2) || (TWI_ADV_MODE == TWI_ADV_MODE_BOTH)

// tstr_twi_manu_data_mode_2_info str_twi_manu_data_mode_2_info;

// static tstr_twi_manu_data str_twi_manuf =
// {
// 	.u16_company_identifier = COMPANY_IDENTIFIER_TWI,
// 	.u16_manu_data_sz = sizeof(str_twi_manu_data_mode_2_info),
// 	.pu8_manu_data = (twi_u8*)&str_twi_manu_data_mode_2_info,
// };

// tstr_twi_srvc_128_data_mode_2_info	str_twi_srvc_128_data_mode_2_info = 	/**< @brief Structure that holds 128 uuids data data.*/
// {
// 	.au8_fixed_part_128_uuid	= {FIXED_PART_128_UUID},
// 	.u16_profile_id				= PROFILE_ID,
// 	.u32_rcvd					= 0,
// 	.u8_dstn_stats_brief		= 0,
// };

// static tstr_twi_adv_data str_adv_data_mode_2 =
// {
// 	.pu8_manu_adv_data = (twi_u8*)&str_twi_manuf,
// 	.u8_manu_adv_data_size = sizeof(str_twi_manu_data_mode_2_info) + COMPANY_IDENTIFIER_LENGTH,

// 	.pu8_incomplete_128uuid = (twi_u8*)&str_twi_srvc_128_data_mode_2_info,
// 	.u8_incomplete_128uuid_size = sizeof(str_twi_srvc_128_data_mode_2_info),

// 	.pu8_complete_16uuid = NULL,
// 	.u8_complete_16uuid_size = 0,

// 	.pu8_incomplete_16uuid = NULL,
// 	.u8_incomplete_16uuid_size = 0,

// 	.pu8_complete_128uuid = NULL,
// 	.u8_complete_128uuid_size = 0,

// 	.enu_adv_name_type = TWI_BLE_ADVDATA_NO_NAME,  /* TWI_BLE_ADVDATA_FULL_NAME*/
// 	.pu8_device_name = NULL, /*au8_device_name,*/
// };

// tstr_twi_adv_data* epstr_adv_data_mode_2 = &str_adv_data_mode_2; /****** MODE_2*******/


// #ifndef TWI_BLE_DISABLE_SCAN_RESPONSE


// static tstr_twi_adv_data str_scan_response_mode_2 =
// {
// 	.pu8_complete_16uuid = NULL,
// 	.u8_complete_16uuid_size = 0,
// 	.enu_adv_name_type = TWI_BLE_ADVDATA_FULL_NAME, /* TWI_BLE_ADVDATA_NO_NAME, */
// 	.u8_incomplete_16uuid_size = 0,
// 	.u8_manu_adv_data_size = 0,
// 	.u8_incomplete_128uuid_size = 0,
// 	.u8_complete_128uuid_size = 0,
// 	.pu8_device_name = au8_device_name,
// 	.pu8_manu_adv_data = NULL,
// 	.pu8_incomplete_16uuid = NULL,
// 	.pu8_complete_128uuid = NULL,
// 	.pu8_incomplete_128uuid = NULL,
// };
// #endif
// /*
//  * @brief  this array contains the beacons the scan response will be advertised by opportunistic
//  * */

// tstr_twi_adv_data* epstr_scan_response_mode_2 =
// #ifndef TWI_BLE_DISABLE_SCAN_RESPONSE
// 		&str_scan_response_mode_2;
// #else
// 		NULL;
// #endif

// /*******************************************************************************************************************************/
// #endif



