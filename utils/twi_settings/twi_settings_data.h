/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file		twi_settings_data.h
 *	@brief		This file contains the settings' structures of different modules in the System.
 */
/****************************************************************************/
/****************************************************************************/

#ifndef _TWI_SETTINGS_DATA_H_
#define _TWI_SETTINGS_DATA_H_

//***********************************************************
/*- INCLUDES -----------------------------------------------*/
//***********************************************************
#include "twi_types.h"
#include "twi_destinations.h"
#include "twi_common.h"

//***********************************************************
/*- CONSTANTS ----------------------------------------------*/
//***********************************************************
#define TWI_AKA_SQN_SZ										(6)

//***********************************************************
/*- PRIMITIVE TYPES ----------------------------------------*/
//***********************************************************

//***********************************************************
/*- ENUMS --------------------------------------------------*/
//***********************************************************

/*-**********************************************************/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*-**********************************************************/

/**
 *	@struct		_tstr_hw_led_settings
 *	@brief		structure that holds the settings that should be saved and loaded for LEDs in the system
 */

TWI_PACK(typedef struct 
{
	/**@brief This is the state of the LED.*/
	twi_u8				u8_led_value;
	/**@brief  This is the value of LED's Rate*/
	twi_u32				u32_led_rate_value;
	/**@brief  This is the value of LED's On Period.*/
	twi_u32				u32_led_on_period;
})tstr_hw_led_settings;

/**
 *	@struct		_tstr_rhp_trigger_settings
 *	@brief		structure that holds the settings that should be saved and loaded for RHP Triggers.
 */


TWI_PACK(typedef struct 
{
	/**@brief  This is the trigger's previous state*/
	twi_bool			b_prev_state;
	/**@brief  This is the value of the trigger's TRIGGER_IS_ENABLED attribute*/
	twi_bool			b_trig_enabled;
	/**@brief  This is the trigger's Alert/Message actions status. Each bit represents an Alert/Message action: 0 -> applied or 1 -> not applied yet*/
	twi_u8				u8_trig_alrt_msg_actions_status;
	/**@brief  This is the trigger's evaluation Rate*/
	twi_u32				u32_trig_eval_rate;
})tstr_rhp_trig_settings;


/**
 *	@struct		_tstr_rhp_logger_settings
 *	@brief		structure that holds the settings that should be saved and loaded of Logger module. This structure is used to determine the
 *				the size of settings buffer, and to know the order of settings while saving/loading them.
 */
 
TWI_PACK(typedef struct  
{
	/**@brief This is the total number of logs since the time of start logging.*/
	twi_u32					u32_total_num_logs;
	/**@brief This is the software timer for report interval.*/
	twi_u32					u32_report_counter;
	/**@brief This is the number of unread logs since the last reading operation.*/
	twi_u32					u32_num_of_unread_logs;
	/**@brief This is the logging interval.*/
	twi_u32					u32_logging_interval;
	/**@brief This is the report interval.*/
	twi_u32					u32_report_interval;
	/**@brief This is the read index of the logs.*/
	twi_u32					u32_read_idx;
	/**@brief This tracks the time from start logging.*/
	twi_u32					u32_time_from_start;
	/**@brief This tracks the last-report timestamp.*/
	twi_u32					u32_lst_rprt_timestmp;
	/**@brief This tracks the time to start logging.*/
	twi_u32					u32_time_to_start;
	/**@brief This U8 indicates either the types of the logger (Event Based or Timer Based).*/
	twi_u8					u8_logger_type;
	/**@brief This is the logs data format.*/
	twi_u8					u8_logs_format;
	/**@brief This U8 indicates the status of the logger.*/
	twi_u8					u8_logger_status;
	/**@brief This BOOLEAN indicates the logger needs to push logs.*/
	twi_bool				b_need_to_push;
})tstr_rhp_logger_settings;

/**
 *	@struct		_tstr_fifo_settings
 *	@brief		structure that holds the settings that should be saved and loaded of FIFO module. This structure is used to determine the
 *				the size of settings buffer, and to know the order of settings while saving/loading them.
 */
 
TWI_PACK(typedef struct 
{
	/**@brief This the number of available data in the FIFO ready to be read.*/
	twi_u32					u32_number_of_available_data;
	/**@brief This the number of free bytes in the FIFO.*/
	twi_u32					u32_num_free_bytes;
	/**@brief This the number of free pages in the FIFO.*/
	twi_u32					u32_num_free_pages;
	/**@brief The Read Index of the flash.*/
	twi_u32					u32_read_idx;
	/**@brief The Read Page Index of the flash.*/
	twi_u32					u32_read_page_idx;
	/**@brief The Write Index of the flash.*/
	twi_u32					u32_write_idx;
	/**@brief The Write Page Index of the flash.*/
	twi_u32					u32_write_page_idx;
	/**@brief The oldest valid page */
	twi_u32					u32_origin_page_idx;
	/**@brief The total number of valid data bytes in FIFO */
	twi_u32					u32_num_valid_bytes;
}) tstr_fifo_settings;


/**
 *	@struct		tstr_opp_settings
 *	@brief		structure that holds the settings that should be saved and loaded of OPP module.
 */

TWI_PACK(typedef struct  
{
	twi_u8	u8_highest_priority;
	twi_u16	u16_min_conn_interval_10xms;
	twi_u16	u16_max_conn_interval_10xms;
	twi_u16	u16_slave_latency;
	twi_u16	u16_superv_timeout_ms;
}) tstr_conn_param_mgmt_settings;

/**
 *	@struct		tstr_opp_settings
 *	@brief		structure that holds the settings that should be saved and loaded of OPP module.
 */

TWI_PACK(typedef struct  
{
	/**@brief This the index of NDS advertising Beacon.*/
	twi_u8	u8_nds_adv_beacon_idx;
	twi_u8	u8_adv_mode;
}) tstr_opp_settings;

/**
 *	@struct		tstr_utc_settings
 *	@brief		structure that holds the settings that should be saved and loaded of UTC module.
 */

TWI_PACK(typedef struct  
{
	twi_bool	b_is_utc_ref_set;
	twi_u32 	u32_utc_time_sec;
})tstr_utc_settings;

/**
 *	@struct		tstr_rhp_status_settings
 *	@brief		structure that holds the settings that should be saved and loaded of STATUS module. This structure is used to determine the
 *				the size of settings buffer, and to know the order of settings in saving and loading them.
 */
 
TWI_PACK(typedef struct
{
	twi_u32	u32_status_refresh_rate;
}) tstr_rhp_status_settings;

/**
 *	@struct		tstr_gw_wifi_settings
 *	@brief		structure that holds the settings of WiFi, i.e SSID,PASSWD.
 */
 
TWI_PACK(typedef struct 
{
	twi_u8				enu_sec_type;
	twi_u8 				au8_ssid[32];
	twi_u8				u8_ssid_len;
	twi_u8 				au8_pswd[64];
	twi_u8				u8_pswd_len;
})tstr_gw_wifi_settings;

/**
 *	@struct		tstr_sec_mngr_settings
 *	@brief		structure that holds the settings that should be saved and loaded of security manager module.
 */
 
TWI_PACK(typedef struct  
{
	twi_u8			au8_seq_no[OUTPUT_DESTS_NUM * TWI_AKA_SQN_SZ];				/**< @brief Session SEQ Number, this number is used inside the EAP_AKA module.*/
})tstr_sec_mngr_settings;

/**
 *	@struct		tstr_engine_settings
 *	@brief		structure that holds the settings that should be saved and loaded of engine module.
 */
 
TWI_PACK(typedef struct   
{
	twi_u16 	u16_dest_adv_state;				/**< @brief This is a bitwise flags that defines if the application/profile has requested to advertise DATA/ALERT.*/
})tstr_engine_settings;


/**
 *	@struct		tstr_tp_mngr_settings
 *	@brief		structure that holds the settings that should be saved and loaded of tp_mngr module.
 */

TWI_PACK(typedef struct
{
	twi_u8	u8_idle_per_timeout;
}) tstr_tp_mngr_settings;

TWI_PACK(typedef struct
{
	twi_u32	u32_offest;	
    twi_u32 u32_total_logged_records;
    twi_u16 u16_count;
}) tstr_rprt_settings;

#endif /* _TWI_SETTINGS_DATA_H_ */
