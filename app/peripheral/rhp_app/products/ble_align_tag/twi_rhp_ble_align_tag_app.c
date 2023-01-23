/****************************************************************************/
/* Copyright (c) 2022 Thirdwayv, Inc. All Rights Reserved.					*/
/****************************************************************************/
/*-*********************************************************/
/*- INCLUDES ----------------------------------------------*/
/*-*********************************************************/
#include <stdlib.h>
#include "twi_rhp.h"
#include "twi_rhp_ble_align_tag.h"
#include "twi_debug.h"
#include "twi_common.h"
#include "twi_timer.h"
#include "twi_opp_proto.h"
#include "twi_opp_cfg.h"
#include "twi_formatters.h"
#include "twi_power_mgmt.h"
#include "twi_system.h"
#include "twi_ble_hal.h"
#include "twi_ble_aml.h"
#ifdef APP_SELF_HANDLE_LOGGER_UTC
	#include "twi_utc.h"
#endif
/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------------*/
/*-*********************************************************/
#define RHP_APP_LOG_ENABLE
#ifdef RHP_APP_LOG_ENABLE
	#define RHP_APP_LOG(...)				        TWI_LOGGER("[ALIGN_TAG_APP]: "__VA_ARGS__)
	#define RHP_APP_LOG_HEX(MSG, HEX_BUFFER, LEN)	do													\
														{												\
															TWI_LOGGER("[ALIGN_TAG_APP]: ");	\
															TWI_DUMP_BUF(MSG, HEX_BUFFER, LEN);			\
														}while(0)
	#define RHP_APP_LOG_ERR(...)					TWI_LOGGER_ERR("[[ALIGN_TAG_APP_ERR]: "__VA_ARGS__)
#else
	#define RHP_APP_LOG(...)
	#define RHP_APP_LOG_HEX(...)
	#define RHP_APP_LOG_ERR(...)
#endif
#define BLE_START_STOP_ADV_ATTRIBUTE				gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_ZERO_IDX]->ppstr_attributes[ATTRIBUTE_ZERO_IDX]
#define BLE_SET_ADV_DATA_ATTRIBUTE	    			gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_ZERO_IDX]->ppstr_attributes[ATTRIBUTE_ONE_IDX]
#define BLE_PERIPHERAL_CONNECT_STATUS           	gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_ZERO_IDX]->ppstr_attributes[ATTRIBUTE_THREE_IDX]
#define BATTERY_SENSOR_ATTRIBUTE	    			gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_ONE_IDX]->ppstr_attributes[ATTRIBUTE_ZERO_IDX]
#define TEMPERATURE_SENSOR_ATTRIBUTE	    		gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_ONE_IDX]->ppstr_attributes[ATTRIBUTE_ONE_IDX]
#define PRESSURE_SENSOR_ATTRIBUTE	    			gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_ONE_IDX]->ppstr_attributes[ATTRIBUTE_TWO_IDX]
#define FORCE_SENSOR_ATTRIBUTE	    				gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_ONE_IDX]->ppstr_attributes[ATTRIBUTE_THREE_IDX]
#define PH_SENSOR_ATTRIBUTE	    					gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_ONE_IDX]->ppstr_attributes[ATTRIBUTE_FOUR_IDX]
#define X_ACC_SENSOR_ATTRIBUTE	    				gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_TWO_IDX]->ppstr_attributes[ATTRIBUTE_ZERO_IDX]
#define Y_ACC_SENSOR_ATTRIBUTE	    				gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_TWO_IDX]->ppstr_attributes[ATTRIBUTE_ONE_IDX]
#define Z_ACC_SENSOR_ATTRIBUTE	    				gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_TWO_IDX]->ppstr_attributes[ATTRIBUTE_TWO_IDX]
#define SENSORS_LOGGED_DATA	    					gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_FOUR_IDX]->ppstr_attributes[ATTRIBUTE_ZERO_IDX]
#define SENSORS_SESSION_STATUS		    			gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_THREE_IDX]->ppstr_attributes[ATTRIBUTE_ZERO_IDX]
#define ALIGN_TAG_OPERATION_MODE		    		gstr_profile.pstr_hardware_in->ppstr_features[FEATURE_THREE_IDX]->ppstr_attributes[ATTRIBUTE_ONE_IDX]

#define DEVICE_OPERATING_MODE                   	(((tstr_align_session_status*)(SENSORS_SESSION_STATUS->pstr_value->uni_value.str_hex_array.pu8_data))->u8_operation_mode)
#define LOGGER_0_SESSION_ACC_READING                (((tstr_align_session_status*)(SENSORS_SESSION_STATUS->pstr_value->uni_value.str_hex_array.pu8_data))->u8_n0)
#define LOGGER_0_SESSION_PRESS_READING              (((tstr_align_session_status*)(SENSORS_SESSION_STATUS->pstr_value->uni_value.str_hex_array.pu8_data))->u8_m0)
#define LOGGER_0_SESSION_FORCE_READING              (((tstr_align_session_status*)(SENSORS_SESSION_STATUS->pstr_value->uni_value.str_hex_array.pu8_data))->u8_l0)
#define LOGGER_0_SESSION_TEMP_READING               (((tstr_align_session_status*)(SENSORS_SESSION_STATUS->pstr_value->uni_value.str_hex_array.pu8_data))->u8_y0)
#define LOGGER_0_SESSION_PH_READING                 (((tstr_align_session_status*)(SENSORS_SESSION_STATUS->pstr_value->uni_value.str_hex_array.pu8_data))->u8_z0)
#define LOGGER_1_SESSION_ACC_READING                (((tstr_align_session_status*)(SENSORS_SESSION_STATUS->pstr_value->uni_value.str_hex_array.pu8_data))->u8_n1)
#define LOGGER_1_SESSION_PRESS_READING              (((tstr_align_session_status*)(SENSORS_SESSION_STATUS->pstr_value->uni_value.str_hex_array.pu8_data))->u8_m1)
#define LOGGER_1_SESSION_FORCE_READING              (((tstr_align_session_status*)(SENSORS_SESSION_STATUS->pstr_value->uni_value.str_hex_array.pu8_data))->u8_l1)
#define LOGGER_1_SESSION_TEMP_READING               (((tstr_align_session_status*)(SENSORS_SESSION_STATUS->pstr_value->uni_value.str_hex_array.pu8_data))->u8_y1)
#define LOGGER_1_SESSION_PH_READING                 (((tstr_align_session_status*)(SENSORS_SESSION_STATUS->pstr_value->uni_value.str_hex_array.pu8_data))->u8_z1)

#define GET_LOGGER_0_SESSSION_STATUS		    	((gstr_profile.pstr_loggers_in->ppstr_loggers[ALIGN_LOGGER_INDEX_ZERO]->apstr_logger_attributes[LOGGER_STATUS])->pstr_value->uni_value.u8_int)
#define GET_LOGGER_1_SESSSION_STATUS		    	((gstr_profile.pstr_loggers_in->ppstr_loggers[ALIGN_LOGGER_INDEX_ONE]->apstr_logger_attributes[LOGGER_STATUS])->pstr_value->uni_value.u8_int)

#define ONE_MIN_PERIOD                        		(60*1000)  		/* 60 Seconds */
#define ONE_SEC_PERIOD                        		(1000)  		/* 1 Second */
#define _100_MS_PERIOD                        		(100)  			/* 100 MSeconds */

#define ACC_DATA_INDEX                        		(0)
#define PRESS_DATA_INDEX                      		(ACC_DATA_SIZE_PER_LOGGING_INTERVAL)
#define FORCE_DATA_INDEX                     		(PRESS_DATA_INDEX + PRESS_DATA_SIZE_PER_LOGGING_INTERVAL)
#define TEMP_DATA_INDEX                      		(FORCE_DATA_INDEX + FORCE_DATA_SIZE_PER_LOGGING_INTERVAL)
#define PH_DATA_INDEX                      			(TEMP_DATA_INDEX + TEMP_DATA_SIZE_PER_LOGGING_INTERVAL)

#define NUDGE_RETRY_TIME_MS                     	(5 * 1000) 	/* 5 Seconds*/
#define FAST_NUDGE_RETRY_TIME_MS                   	(100) 		/* 100 ms*/

#define BATTERY_PERC_UPDATE_PARENT_IDX           	(1)
#define BATTERY_PERC_UPDATE_ATT_IDX               	(0)

#define IS_DEVICE_CONNECTED                         (twi_ble_is_connected(BLE_PERIPHERAL_ROLE_SUPPORTED))

#define RESET_SENSOR_DATA(ARRAY)  					(TWI_MEMSET(ARRAY,0xFF,sizeof(ARRAY)))

#ifdef APP_SELF_HANDLE_LOGGER_UTC
	#define DEFULT_UTC_TIME_SEC               		(1654041600) /* Wednesday, June 1, 2022 2:00:00 AM GMT+02:00 */
#endif

#define NUMBER_OF_PACKETS_TO_REPORT    				(10)
#define SENSORS_ARE_NOT_READY 						(0x00)
#define SENSORS_ARE_READY 							(0x1F)

#define ACC_VALUE_UPPER_LIMIT     					(8000)
#define PRESS_VALUE_UPPER_LIMIT     				(110000)
#define PRESS_VALUE_LOWER_LIMIT     				(90000)
#define FORCE_VALUE_UPPER_LIMIT     				(1000)
#define TEMP_VALUE_UPPER_LIMIT     					(40)
#define TEMP_VALUE_LOWER_LIMIT     					(20)

/* Synchronizing Sensor Data */ 
/* FW should replace it with a predefined value to keep the total number of logs synchronized with time from the start value */
#define ACC_SENSOR_AXIS_ERROR_VALUE					(0xFFFF)
#define PRESS_SENSOR_ERROR_VALUE					(0xFFFFFFFF)
#define FORCE_SENSOR_ERROR_VALUE					(0xFFFF)
#define TEMP_SENSOR_ERROR_VALUE						(0xFFFF)
#define PH_SENSOR_ERROR_VALUE						(0xFF)

#ifdef TEST_TRI_WAVE
	#define MAX_COUNTING_VALUE							(255)
	#define MIN_COUNTING_VALUE							(0)
#endif

#ifdef TEST_GPIOS_SNIFFING
	#define H_RATE_RACING_START_CH0				(twi_gpio_set(TWI_PORTA , TWI_PIN17))
	#define H_RATE_RACING_STOP_CH0				(twi_gpio_clear(TWI_PORTA , TWI_PIN17))

	#define START_TAKE_LOGS_CH3					(twi_gpio_set(TWI_PORTA , TWI_PIN20))
	#define TAKE_LOGS_DONE_CH3					(twi_gpio_clear(TWI_PORTA , TWI_PIN20))

	#define DISPATCH_START_CH4					/*(twi_gpio_set(TWI_PORTA , TWI_PIN7))*/
	#define DISPATCH_END_CH4					/*(twi_gpio_clear(TWI_PORTA , TWI_PIN7))*/

	#define READ_ATT_START_CH4					(twi_gpio_set(TWI_PORTA , TWI_PIN7))
	#define READ_ATT_END_CH4					(twi_gpio_clear(TWI_PORTA , TWI_PIN7))
#endif
/*-*********************************************************/
/*- STRUCTS AND UNIONS ------------------------------------*/
/*-*********************************************************/
/**
 *	@enum		tenu_nudge_opcodes
 *	@brief		enum that contains available nudge opcodes
 */
typedef enum
{
    BATTERY_PERC_UPDATE_OPCODE = 0,           
    INVALID_NUDGE_OPCODE,         
}tenu_nudge_opcodes;

/**
 *	@enum		tenu_align_logger_index
 *	@brief		enum that contains available nudge logger index
 */
typedef enum
{
    ALIGN_LOGGER_INDEX_ZERO = 0,         
	ALIGN_LOGGER_INDEX_ONE,  
    INVALID_ALIGN_LOGGER_INDEX,         
}tenu_align_logger_index;

/**
 *	@enum		tenu_align_sensor_idxs
 *	@brief		enum that contains available nudge logger index
 */
typedef enum
{
    ALIGN_ACC_SENSOR_IDX = 0,         
	ALIGN_PRESS_SENSOR_IDX,  
    ALIGN_FORCE_SENSOR_IDX,   
	ALIGN_TEMP_SENSOR_IDX,
	ALIGN_PH_SENSOR_IDX,      
}tenu_align_sensor_idxs;

#ifdef TEST_TRI_WAVE
/**
 *	@enum		tenu_data_counting_mode
 *	@brief		enum that contains data counting mode (Up or Down)
 */
typedef enum
{
    PH_COUNT_UP = 0,           
    PH_COUNT_DOWN,
	TEMP_COUNT_UP,
	TEMP_COUNT_DOWN,
	FORCE_COUNT_UP,
	FORCE_COUNT_DOWN,
	PRESS_COUNT_UP,
	PRESS_COUNT_DOWN,
	ACC_COUNT_UP,
	ACC_COUNT_DOWN,       
}tenu_data_counting_mode;
#endif

/**
 *	@struct		tstr_fw_version
 *	@brief		structure that holds FW version
 */

TWI_PACK (typedef struct
{
	twi_u8	u8_fw_major_version;
	twi_u8	u8_fw_minor_version;
    twi_u8  u8_fw_patch_version;
})tstr_fw_version;

/**
 *	@struct		tstr_app_dispatch_flags
 *	@brief		structure that holds All the flags that will be handled in the dispatcher
 */
typedef struct
{
	twi_u8 gu8_sensor_data_is_ready;
	twi_u8 gu8_get_sensor_data;
	twi_bool gb_notify_battery_percentage;
	twi_bool gb_logger_index_zero_report;
	twi_bool gb_logger_index_one_report;
	twi_u8   au8_nudge_data_retry_timer_fired[INVALID_NUDGE_OPCODE];     
	twi_u8   au8_nudge_logs_retry_timer_fired[INVALID_ALIGN_LOGGER_INDEX];   
	twi_u8   au8_nudge_data_succeeded[INVALID_NUDGE_OPCODE];  
	twi_u8   au8_nudge_logs_succeeded[INVALID_ALIGN_LOGGER_INDEX];  
}tstr_app_dispatch_flags;

/**
 *	@struct		tstr_nudge_data_parameters
 *	@brief		Structure used to hold the parameters used in nudging to retry nudging the mobile in case of nudge failed and the mobile didn't send the ack message
 */
typedef struct
{
    twi_u8 u8_op_code;
    twi_u8 u8_parent_index;
    twi_u8 u8_attribute_index;
    twi_bool b_is_nudge_in_progress;
}tstr_nudge_data_parameters;

/**
 *	@struct		tstr_nudge_data_parameters
 *	@brief		Structure used to hold the parameters used in nudging to retry nudging the mobile in case of nudge failed and the mobile didn't send the ack message
 */
typedef struct
{
    twi_u8 u8_tp_logger_index;
    twi_u8 u8_tp_notify_destenation;
    twi_bool b_is_nudge_in_progress;
}tstr_nudge_logs_parameters;

/*-*********************************************************/
/*- LOCAL FUNCTION DECLARATIONS ---------------------------*/
/*-*********************************************************/
static void start_advr_logic(void);
static twi_s32 twi_ble_aml_cb(twi_u8 * pu8_adv_data , twi_u16 u16_data_sz);
static void timer_high_rate_callback (void *pv);
static void timer_low_rate_callback (void *pv);
static twi_s32 nudge_peer_data(twi_u8 u8_opcode,twi_u8 u8_parent_idx, twi_u8 u8_att_idx);
static twi_s32 nudge_peer_logs(twi_u8 u8_logger_index, twi_u8 u8_notify_dest);
static twi_s32 handle_nudge_data_device_failure(twi_u8 u8_opcode);
static twi_s32 handle_nudge_logs_device_failure(twi_u8 u8_logger_index);
static void nudge_data_retry_timer_callback (void* pv);
static void nudge_logs_retry_timer_callback (void* pv);
static void init_global_variables(void* pv);
static twi_s32 packet_formation();
static twi_u8 get_operating_mode(void);
static twi_s32 session_status_update(twi_u8 u8_mode_of_operation);
//void acc_data_ready (void);

/*-*********************************************************/
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/*-*********************************************************/
extern const tstr_twi_rhp_profile gstr_profile;
extern twi_u8 pu8_twi_sas_sender_id[];
/*-*********************************************************/
/*- GLOBAL CONSTANT VARIABLES -----------------------------*/
/*-*********************************************************/

/*-*********************************************************/
/*- GLOBAL VARIABLES --------------------------------------*/
/*-*********************************************************/
static tpf_rqst_ntfy_rhp_engn gpf_rqst_ntfy;
static tstr_timer_mgmt_timer    gstr_high_rate_timer = {0};      /* To get the accelerometer and pressure values */
static tstr_timer_mgmt_timer    gstr_low_rate_timer = {0};	     /* To get the force and temp and PH values */
static tstr_app_dispatch_flags                  gstr_app_dispatcher_flags;
static twi_u8 gu8_acc_readings_counter = 0;
static twi_u8 gu8_press_readings_counter = 0;
static twi_u8 gu8_force_readings_counter = 0;
static twi_u8 gu8_temp_readings_counter = 0;
static twi_u8 gu8_ph_readings_counter = 0;
static twi_u8 gau8_total_logged_data[TOTAL_DATA_SIZE_PER_LOGGING_INTERVAL] 	= {0};
static twi_u8 gau8_acc_logged_data[ACC_DATA_SIZE_PER_LOGGING_INTERVAL] 		= {0};
static twi_u8 gau8_press_logged_data[PRESS_DATA_SIZE_PER_LOGGING_INTERVAL] 	= {0};
static twi_u8 gau8_force_logged_data[FORCE_DATA_SIZE_PER_LOGGING_INTERVAL] 	= {0};
static twi_u8 gau8_temp_logged_data[TEMP_DATA_SIZE_PER_LOGGING_INTERVAL] 	= {0};
static twi_u8 gau8_ph_logged_data[PH_DATA_SIZE_PER_LOGGING_INTERVAL] 		= {0};
static twi_bool gb_running_mode = TWI_FALSE;
static tstr_timer_mgmt_timer        gastr_nudge_data_retry_timer[INVALID_NUDGE_OPCODE];	    	/*Timer structure used to retry nudging*/
static tstr_nudge_data_parameters 	gastr_nudging_data_parameters[INVALID_NUDGE_OPCODE];		/*Initially filling the nudging parameters structure with zeros*/
static tstr_timer_mgmt_timer       	gastr_nudge_logs_retry_timer[INVALID_ALIGN_LOGGER_INDEX];	/*Timer structure used to retry nudging*/
static tstr_nudge_logs_parameters   gastr_nudging_logs_parameters[INVALID_ALIGN_LOGGER_INDEX];	/*Initially filling the nudging parameters structure with zeros*/
static twi_u8 gu8_unreaded_packets = 0;

/*-*********************************************************/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/*-*********************************************************/
static void start_advr_logic(void)
{
	tstr_twi_rhp_value str_tmp_val;
	TWI_MEMSET(&str_tmp_val, 0, sizeof(tstr_twi_rhp_value));
	str_tmp_val.enu_type = U8;
	str_tmp_val.uni_value.u8_int = (twi_u8)BLE_ADVERTISE_START;
	twi_rhp_write_attr(BLE_START_STOP_ADV_ATTRIBUTE, &str_tmp_val);
}

static twi_s32 twi_ble_aml_cb(twi_u8 * pu8_adv_data , twi_u16 u16_data_sz)
{
    twi_s32 s32_retval = TWI_SUCCESS;
    tstr_twi_rhp_value str_adv_data_val;
    TWI_MEMSET(&str_adv_data_val , 0 ,sizeof(tstr_twi_rhp_value));   
    str_adv_data_val.enu_type = HEX;
    str_adv_data_val.uni_value.str_hex_array.u16_len = u16_data_sz;
    str_adv_data_val.uni_value.str_hex_array.pu8_data = pu8_adv_data;
    s32_retval = twi_rhp_write_attr(BLE_SET_ADV_DATA_ATTRIBUTE, &str_adv_data_val);
    TWI_ASSERT(TWI_SUCCESS == s32_retval);
    return s32_retval;
}

static void timer_high_rate_callback (void *pv)
{
#ifdef TEST_GPIOS_SNIFFING	
	if((GET_BIT_STATUS(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_ACC_SENSOR_IDX)) ||
	(GET_BIT_STATUS(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_PRESS_SENSOR_IDX)))
	{
		H_RATE_RACING_START_CH0;
	}
	else
	{
		H_RATE_RACING_STOP_CH0;
	}
#endif
	TWI_SET_BIT(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_ACC_SENSOR_IDX);
	TWI_SET_BIT(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_PRESS_SENSOR_IDX);
}

static void timer_low_rate_callback (void *pv)
{
	TWI_SET_BIT(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_FORCE_SENSOR_IDX);
	TWI_SET_BIT(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_TEMP_SENSOR_IDX);
	TWI_SET_BIT(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_PH_SENSOR_IDX);
}

static twi_s32 nudge_peer_logs(twi_u8 u8_logger_index, twi_u8 u8_notify_dest)
{	
	twi_s32 s32_retval = TWI_ERROR;
	tstr_notifiy_request str_rqst_ntfy;
	tstr_twi_ntfy_cnnctd_rqst_data str_ntfy_rqst_data;
	TWI_MEMSET(&str_rqst_ntfy, 0, sizeof(tstr_notifiy_request));
	RHP_APP_LOG("Start Nudge Peer logs with logger index 0x%X, notify destination #%d\r\n",u8_logger_index,u8_notify_dest);

	str_ntfy_rqst_data.enu_evt_type =  NTFY_HAS_LOGS_EVT;
	str_ntfy_rqst_data.u8_output_destinations = u8_notify_dest;
	str_ntfy_rqst_data.uni_evt_data.u8_logger_idx = u8_logger_index;
	str_ntfy_rqst_data.enu_nudge_priority = NUDGE_PRIORITY_HIGH;
	str_rqst_ntfy.pv_data = &str_ntfy_rqst_data;
	str_rqst_ntfy.enu_type = NOTIFY_CONNECTED_PEER;

    if(TWI_FALSE == gastr_nudging_logs_parameters[u8_logger_index].b_is_nudge_in_progress)
    {
        gastr_nudging_logs_parameters[u8_logger_index].b_is_nudge_in_progress = TWI_TRUE;
        gastr_nudging_logs_parameters[u8_logger_index].u8_tp_logger_index = u8_logger_index;
        gastr_nudging_logs_parameters[u8_logger_index].u8_tp_notify_destenation = u8_notify_dest;
    }
    else
    {
        RHP_APP_LOG_ERR("Nudging Structure Already Filled!\n");
    }

    /*Start the nudging timer*/
    s32_retval = start_timer(&gastr_nudge_logs_retry_timer[u8_logger_index], (twi_s8*) "Nudge Retry Timer", TWI_TIMER_TYPE_ONE_SHOT, (twi_u32) NUDGE_RETRY_TIME_MS, nudge_logs_retry_timer_callback, &gastr_nudging_logs_parameters[u8_logger_index].u8_tp_logger_index);
    if(s32_retval != TWI_SUCCESS)
    {
        RHP_APP_LOG_ERR("Failed to start the Nudge Retry Timer With Err = %d\r\n", s32_retval);
    }

    if(NULL!= gpf_rqst_ntfy)
    {
        s32_retval= gpf_rqst_ntfy(&str_rqst_ntfy);
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }
    return s32_retval;    
}

static twi_s32 nudge_peer_data(twi_u8 u8_opcode,twi_u8 u8_parent_idx, twi_u8 u8_att_idx)
{
    twi_s32 s32_retval = TWI_ERROR;
    tstr_notifiy_request	str_rqst_ntfy;
    tstr_twi_ntfy_cnnctd_rqst_data str_ntfy_rqst_data;
	TWI_MEMSET(&str_rqst_ntfy, 0, sizeof(tstr_notifiy_request));
    RHP_APP_LOG("Start Nudge Peer data with op Code 0x%X, Parent#%d, Att# %d \r\n",u8_opcode,u8_parent_idx,u8_att_idx);
    
    str_ntfy_rqst_data.enu_evt_type =  NTFY_HAS_SPECIFIC_DATA_EVT;
    str_ntfy_rqst_data.uni_evt_data.str_has_specfic_msg_data.u8_opcode = u8_opcode;
    str_ntfy_rqst_data.uni_evt_data.str_has_specfic_msg_data.u8_parent_idx 	= u8_parent_idx;
    str_ntfy_rqst_data.uni_evt_data.str_has_specfic_msg_data.u8_specific_msg_idx = u8_att_idx;
    str_ntfy_rqst_data.enu_nudge_priority = NUDGE_PRIORITY_HIGH;
    str_rqst_ntfy.pv_data =(void*)&str_ntfy_rqst_data;
    str_rqst_ntfy.enu_type = NOTIFY_CONNECTED_PEER;
    /*Filling the nudging retry structure after checking that there is no pending failed nudges*/
    if(TWI_FALSE == gastr_nudging_data_parameters[u8_opcode].b_is_nudge_in_progress)
    {
        gastr_nudging_data_parameters[u8_opcode].b_is_nudge_in_progress = TWI_TRUE;
        gastr_nudging_data_parameters[u8_opcode].u8_op_code = u8_opcode;
        gastr_nudging_data_parameters[u8_opcode].u8_parent_index = u8_parent_idx;
        gastr_nudging_data_parameters[u8_opcode].u8_attribute_index = u8_att_idx;
    }
    else
    {
        RHP_APP_LOG_ERR("Nudging Structure Already Filled!\n");
    }

    /*Start the nudging timer*/
    s32_retval = start_timer(&gastr_nudge_data_retry_timer[u8_opcode], (twi_s8*) "Nudge Retry Timer", TWI_TIMER_TYPE_ONE_SHOT, (twi_u32) NUDGE_RETRY_TIME_MS, nudge_data_retry_timer_callback, &gastr_nudging_data_parameters[u8_opcode].u8_op_code);
    if(s32_retval != TWI_SUCCESS)
    {
        RHP_APP_LOG_ERR("Failed to start the Nudge Retry Timer With Err = %d\r\n", s32_retval);
    }

    if(NULL!= gpf_rqst_ntfy)
    {
        s32_retval= gpf_rqst_ntfy(&str_rqst_ntfy);
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }
    return s32_retval;
}

static twi_s32 handle_nudge_data_device_failure(twi_u8 u8_opcode)
{
    twi_s32 s32_retval = TWI_ERROR;
    s32_retval = stop_timer(&gastr_nudge_data_retry_timer[u8_opcode]);
    if(s32_retval != TWI_SUCCESS)
    {
        RHP_APP_LOG_ERR("Failed to stop nudging timer with Error %d!\r\n", s32_retval);
    }
    else
    {
        RHP_APP_LOG("Elements in str_temp_nudge_parameters! au8_nudge_in_progress = %d, u8_op_code = %d, u8_parent_index = %d, u8_attribute_index = %d\n", gastr_nudging_data_parameters[u8_opcode].b_is_nudge_in_progress, gastr_nudging_data_parameters[u8_opcode].u8_op_code, gastr_nudging_data_parameters[u8_opcode].u8_parent_index, gastr_nudging_data_parameters[u8_opcode].u8_attribute_index);
        s32_retval = nudge_peer_data(gastr_nudging_data_parameters[u8_opcode].u8_op_code, gastr_nudging_data_parameters[u8_opcode].u8_parent_index, gastr_nudging_data_parameters[u8_opcode].u8_attribute_index);
        if(s32_retval != TWI_SUCCESS)
        {
            /*No action is needed, as we will retry on to nudge on our own inside the nudge peer function*/
        }
    }
        
    return s32_retval;
}

static twi_s32 handle_nudge_logs_device_failure(twi_u8 u8_logger_index)
{
	twi_s32 s32_retval = TWI_ERROR;
    s32_retval = stop_timer(&gastr_nudge_logs_retry_timer[u8_logger_index]);
    if(s32_retval != TWI_SUCCESS)
    {
        RHP_APP_LOG_ERR("Failed to stop nudging timer with Error %d!\r\n", s32_retval);
    }
    else
    {
        RHP_APP_LOG("Elements in str_temp_nudge_parameters! au8_nudge_in_progress = %d, u8_tp_logger_index = %d, u8_tp_notify_destenation = %d\n", gastr_nudging_logs_parameters[u8_logger_index].b_is_nudge_in_progress, gastr_nudging_logs_parameters[u8_logger_index].u8_tp_logger_index, gastr_nudging_logs_parameters[u8_logger_index].u8_tp_notify_destenation);
        s32_retval = nudge_peer_logs(gastr_nudging_logs_parameters[u8_logger_index].u8_tp_logger_index, gastr_nudging_logs_parameters[u8_logger_index].u8_tp_notify_destenation);
        if(s32_retval != TWI_SUCCESS)
        {
            /*No action is needed, as we will retry on to nudge on our own inside the nudge peer function*/
        }
    }
        
    return s32_retval;
}

/*Nudge timer fire callback. In this function we will raise a flag and will handle it in the app dispatcher*/
static void nudge_data_retry_timer_callback (void* pv)
{
    if (TWI_TRUE == IS_DEVICE_CONNECTED)
    {
		TWI_ASSERT(pv != NULL);
		gstr_app_dispatcher_flags.au8_nudge_data_retry_timer_fired[*(twi_u8*)pv] = TWI_TRUE;
        RHP_APP_LOG("%d \n",gstr_app_dispatcher_flags.au8_nudge_data_retry_timer_fired[0]);
        RHP_APP_LOG("Retry Nudging data \r\n",gstr_app_dispatcher_flags.au8_nudge_data_retry_timer_fired[*(twi_u8*)pv]);
    }
    else
    {
        RHP_APP_LOG_ERR("No need to retry Nudging as it is not Connected %d \r\n",gstr_app_dispatcher_flags.au8_nudge_data_retry_timer_fired[*(twi_u8*)pv]);
		twi_s32 s32_retval = TWI_ERROR;
        s32_retval = stop_timer(&gastr_nudge_data_retry_timer[*(twi_u8*)pv]);
        if(s32_retval != TWI_SUCCESS)
        {
            RHP_APP_LOG_ERR("Failed to stop the Fast Nudge Retry Timer With Err = %d\r\n", s32_retval);
        }
        s32_retval = start_timer(&gastr_nudge_data_retry_timer[*(twi_u8*)pv], (twi_s8*) "Fast Nudge Retry Timer", TWI_TIMER_TYPE_ONE_SHOT, (twi_u32) FAST_NUDGE_RETRY_TIME_MS, nudge_data_retry_timer_callback, &gastr_nudging_data_parameters[*(twi_u8*)pv].u8_op_code);
        if(s32_retval != TWI_SUCCESS)
        {
            RHP_APP_LOG_ERR("Failed to start the Fast Nudge Retry Timer With Err = %d\r\n", s32_retval);
        }
    }
}

static void nudge_logs_retry_timer_callback (void* pv)
{
	if (TWI_TRUE == IS_DEVICE_CONNECTED)
    {
		TWI_ASSERT(pv != NULL);
		gstr_app_dispatcher_flags.au8_nudge_logs_retry_timer_fired[*(twi_u8*)pv] = TWI_TRUE;
        RHP_APP_LOG("%d %d \n"
        ,gstr_app_dispatcher_flags.au8_nudge_logs_retry_timer_fired[0]
        ,gstr_app_dispatcher_flags.au8_nudge_logs_retry_timer_fired[1]);
        RHP_APP_LOG("Retry Nudging logs report %d \r\n",gstr_app_dispatcher_flags.au8_nudge_logs_retry_timer_fired[*(twi_u8*)pv]);
    }
    else
    {
        RHP_APP_LOG_ERR("No need to retry Nudging as it is not Connected %d \r\n",gstr_app_dispatcher_flags.au8_nudge_logs_retry_timer_fired[*(twi_u8*)pv]);
		twi_s32 s32_retval = TWI_ERROR;
        s32_retval = stop_timer(&gastr_nudge_logs_retry_timer[*(twi_u8*)pv]);
	    if(s32_retval != TWI_SUCCESS)
        {
            RHP_APP_LOG_ERR("Failed to stop the Fast Nudge Retry Timer With Err = %d\r\n", s32_retval);
        }
        s32_retval = start_timer(&gastr_nudge_logs_retry_timer[*(twi_u8*)pv], (twi_s8*) "Fast Nudge Retry Timer", TWI_TIMER_TYPE_ONE_SHOT, (twi_u32) FAST_NUDGE_RETRY_TIME_MS, nudge_logs_retry_timer_callback, &gastr_nudging_logs_parameters[*(twi_u8*)pv].u8_tp_logger_index);
        if(s32_retval != TWI_SUCCESS)
        {
            RHP_APP_LOG_ERR("Failed to start the Fast Nudge Retry Timer With Err = %d\r\n", s32_retval);
        }
    }

}

static void init_global_variables(void* pv)
{
	gstr_app_dispatcher_flags.gu8_sensor_data_is_ready = SENSORS_ARE_NOT_READY;
	gstr_app_dispatcher_flags.gu8_get_sensor_data = SENSORS_ARE_NOT_READY;
	gstr_app_dispatcher_flags.gb_notify_battery_percentage = TWI_FALSE;
	gstr_app_dispatcher_flags.gb_logger_index_zero_report = TWI_FALSE;
	gstr_app_dispatcher_flags.gb_logger_index_one_report = TWI_FALSE;
	gpf_rqst_ntfy = NULL;

	TWI_MEMSET(gstr_app_dispatcher_flags.au8_nudge_data_retry_timer_fired,0x00,INVALID_NUDGE_OPCODE);
	TWI_MEMSET(gstr_app_dispatcher_flags.au8_nudge_logs_retry_timer_fired,0x00,INVALID_ALIGN_LOGGER_INDEX);
    TWI_MEMSET(gstr_app_dispatcher_flags.au8_nudge_data_succeeded,0x00,INVALID_NUDGE_OPCODE);
	TWI_MEMSET(gstr_app_dispatcher_flags.au8_nudge_logs_succeeded,0x00,INVALID_ALIGN_LOGGER_INDEX);

	TWI_MEMSET(&gstr_high_rate_timer, 0, sizeof(tstr_timer_mgmt_timer));
	TWI_MEMSET(&gstr_low_rate_timer, 0, sizeof(tstr_timer_mgmt_timer));

	gu8_acc_readings_counter = 0;
	gu8_press_readings_counter = 0;
	gu8_force_readings_counter = 0;
	gu8_temp_readings_counter = 0;
	gu8_ph_readings_counter = 0;
}

static twi_s32 packet_formation()
{
	twi_s32 s32_retval = TWI_ERROR;

#ifdef PACKET_DATA_TESTING
	RHP_APP_LOG("-------------- \r\n");
    /************ Test the n reading of acc in the packet ************/
	twi_u8 u8_n = 0; /* n = 0:9 (10 readings) */ 

	/* PPI Testing */
	/*twi_s16 s16_acc_val = (twi_s16) (gau8_total_logged_data[0 + u8_n*ACC_READING_SIZE] | (gau8_total_logged_data[1 + u8_n*ACC_READING_SIZE] << 8));
	twi_s16 s16_x_axis_acc_mg = (twi_s16) (((MUL1000(s16_acc_val) << 1) >> 15));

	s16_acc_val = (twi_s16) (gau8_total_logged_data[2 + u8_n*ACC_READING_SIZE] | (gau8_total_logged_data[3 + u8_n*ACC_READING_SIZE] << 8));
	twi_s16 s16_y_axis_acc_mg = (twi_s16) (((MUL1000(s16_acc_val) << 1) >> 15));

	s16_acc_val = (twi_s16) (gau8_total_logged_data[4 + u8_n*ACC_READING_SIZE] | (gau8_total_logged_data[5 + u8_n*ACC_READING_SIZE] << 8));
	twi_s16 s16_z_axis_acc_mg = (twi_s16) (((MUL1000(s16_acc_val) << 1) >> 15));

	if ((ABS(s16_x_axis_acc_mg) < 250) && (ABS(s16_z_axis_acc_mg) < 250) && (s16_y_axis_acc_mg < 0 ))
	{
        RHP_APP_LOG("A = Vertical \r\n");
    }
	else if ((ABS(s16_x_axis_acc_mg) < 250) && (ABS(s16_y_axis_acc_mg) < 250) && (s16_z_axis_acc_mg > 0 ))
	{
        RHP_APP_LOG("A = Horizontal \r\n");
    }
    else
    {
        RHP_APP_LOG("A = Unknown \r\n");
    }*/

	/* CPU involved testing */
	twi_s16 s16_x_axis_acc_mg = gau8_total_logged_data[0+u8_n*ACC_READING_SIZE+ACC_DATA_INDEX] << 8 | gau8_total_logged_data[1+u8_n*ACC_READING_SIZE+ACC_DATA_INDEX];
	twi_s16 s16_y_axis_acc_mg = gau8_total_logged_data[2+u8_n*ACC_READING_SIZE+ACC_DATA_INDEX] << 8 | gau8_total_logged_data[3+u8_n*ACC_READING_SIZE+ACC_DATA_INDEX];
	twi_s16 s16_z_axis_acc_mg = gau8_total_logged_data[4+u8_n*ACC_READING_SIZE+ACC_DATA_INDEX] << 8 | gau8_total_logged_data[5+u8_n*ACC_READING_SIZE+ACC_DATA_INDEX];

	if ((ABS(s16_x_axis_acc_mg) < 250) && (ABS(s16_z_axis_acc_mg) < 250) && (s16_y_axis_acc_mg < 0 ))
	{
        RHP_APP_LOG("A = Vertical \r\n");
    }
	else if ((ABS(s16_x_axis_acc_mg) < 250) && (ABS(s16_y_axis_acc_mg) < 250) && (s16_z_axis_acc_mg > 0 ))
	{
        RHP_APP_LOG("A = Horizontal \r\n");
    }
    else
    {
        RHP_APP_LOG("A = Unknown \r\n");
    }

	/************ Test the m reading of pressure in the packet ************/
	twi_u8 u8_m = 0; /* m = 0:9 (10 readings) */ 

	twi_u32 u32_press_value =   (gau8_total_logged_data[0+u8_m*PRESS_READING_SIZE+PRESS_DATA_INDEX] << 24) |
								(gau8_total_logged_data[1+u8_m*PRESS_READING_SIZE+PRESS_DATA_INDEX] << 16) |
								(gau8_total_logged_data[2+u8_m*PRESS_READING_SIZE+PRESS_DATA_INDEX] << 8)  |
							  	(gau8_total_logged_data[3+u8_m*PRESS_READING_SIZE+PRESS_DATA_INDEX]);

	twi_u32 u32_press_int = u32_press_value / 100;
	twi_u16 u16_press_frac = u32_press_value % 100;
	RHP_APP_LOG("P = %d.%d\r\n", u32_press_int, u16_press_frac);

	/************ Test the l reading of force in the packet ************/
	twi_u8 u8_l = 0; /* l = 0 (1 readings) */
	RHP_APP_LOG("F = %d\r\n", (twi_s16) (gau8_total_logged_data[0+u8_l*FORCE_READING_SIZE+FORCE_DATA_INDEX] << 8 | gau8_total_logged_data[1+u8_l*FORCE_READING_SIZE+FORCE_DATA_INDEX]));

	/************ Test the y reading of temp in the packet ************/
	twi_u8 u8_y = 0; /* y = 0 (1 readings) */
	RHP_APP_LOG("T = %d\r\n", gau8_total_logged_data[0+u8_y*TEMP_READING_SIZE+TEMP_DATA_INDEX] << 8 | gau8_total_logged_data[1+u8_y*TEMP_READING_SIZE+TEMP_DATA_INDEX]);

	/************ Test the z reading of ph in the packet ************/
	twi_u8 u8_z = 0; /* z = 0 (1 readings) */
	RHP_APP_LOG("H = %d\r\n", gau8_total_logged_data[u8_z*PH_READING_SIZE+PH_DATA_INDEX]);

	RHP_APP_LOG("-------------- \r\n");
#endif

	tstr_twi_rhp_value str_tmp_val;
	TWI_MEMSET(&str_tmp_val, 0, sizeof(tstr_twi_rhp_value));
	str_tmp_val.enu_type = HEX;
	str_tmp_val.uni_value.str_hex_array.u16_len = sizeof(gau8_total_logged_data);
	str_tmp_val.uni_value.str_hex_array.pu8_data = (twi_u8*) gau8_total_logged_data;
	do
	{
		s32_retval = twi_rhp_write_attr(SENSORS_LOGGED_DATA, &str_tmp_val);
		TWI_ERROR_BREAK(s32_retval);
	} while (0);

	return s32_retval;
}

static twi_u8 get_operating_mode(void)
{
	twi_s32 s32_retval = TWI_ERROR;
	twi_u8 u8_mode_of_operation = ALIGN_TAG_INVALID_MODE;
	tstr_twi_rhp_value str_tmp_val;
	TWI_MEMSET(&str_tmp_val, 0, sizeof(tstr_twi_rhp_value));
	do
	{
		s32_retval = twi_rhp_read_attr(ALIGN_TAG_OPERATION_MODE, &str_tmp_val);
		TWI_ERROR_BREAK(s32_retval);
	} while (0);

	u8_mode_of_operation = str_tmp_val.uni_value.u8_int;

	return u8_mode_of_operation;
}

static twi_s32 session_status_update(twi_u8 u8_mode_of_operation)
{
	twi_s32 s32_retval = TWI_ERROR;
	tstr_twi_rhp_value str_tmp_val;
	tstr_align_session_status str_align_session_status;
	TWI_MEMSET(&str_tmp_val, 0, sizeof(tstr_twi_rhp_value));
	str_tmp_val.enu_type = HEX;

    str_align_session_status.u8_reserved = RESERVED_FIVE_BITS;  
    str_align_session_status.u8_operation_mode = u8_mode_of_operation;                   
    str_align_session_status.u8_n0 = (twi_u8) ACC_NUMBER_OF_READINGS;             
   	str_align_session_status.u8_m0 = (twi_u8) PRESS_NUMBER_OF_READINGS;            
    str_align_session_status.u8_l0 = (twi_u8) FORCE_NUMBER_OF_READINGS;   
    str_align_session_status.u8_y0 = (twi_u8) TEMP_NUMBER_OF_READINGS;          
    str_align_session_status.u8_z0 = (twi_u8) PH_NUMBER_OF_READINGS;          
    str_align_session_status.u8_n1 = (twi_u8) DISABLE_SENSOR_READINGS;   
    str_align_session_status.u8_m1 = (twi_u8) DISABLE_SENSOR_READINGS;     
    str_align_session_status.u8_l1 = (twi_u8) DISABLE_SENSOR_READINGS;            
    str_align_session_status.u8_y1 = (twi_u8) DISABLE_SENSOR_READINGS;  
    str_align_session_status.u8_z1 = (twi_u8) DISABLE_SENSOR_READINGS;

	str_tmp_val.uni_value.str_hex_array.u16_len = sizeof(tstr_align_session_status);
	str_tmp_val.uni_value.str_hex_array.pu8_data = (twi_u8*) &str_align_session_status;

	do
	{
		s32_retval = twi_rhp_write_attr(SENSORS_SESSION_STATUS, &str_tmp_val);
		TWI_ERROR_BREAK(s32_retval);
	} while (0);

	return s32_retval;
}

/*void acc_data_ready (void)
{
	TWI_SET_BIT(gstr_app_dispatcher_flags.gu8_sensor_data_is_ready,ALIGN_ACC_SENSOR_IDX);
}*/

/*-*********************************************************/
/*- APIs IMPLEMENTATION -----------------------------------*/
/*-*********************************************************/

twi_s32 twi_rhp_app_init(const tstr_twi_rhp_app_in* pstr_twi_rhp_app_in, tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy)
{ 
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;
    tstr_twi_aml_in str_twi_aml_in = {0};
    tstr_fw_version str_fw_version = {0};

	start_advr_logic();

	do
    {
        s32_retval = timer_mgmt_init();
        TWI_ERROR_BREAK(s32_retval);
        /*Initialize Version Structure*/
        str_fw_version.u8_fw_major_version = TWI_FW_MAJOR_VERSION;
        str_fw_version.u8_fw_minor_version = TWI_FW_MINOR_VERSION;
        str_fw_version.u8_fw_patch_version = TWI_FW_PATCH_VERSION;

#ifdef APP_SELF_HANDLE_LOGGER_UTC
		s32_retval = twi_utc_set_ref(DEFULT_UTC_TIME_SEC);
    	TWI_ERROR_BREAK(s32_retval);
#endif 

		init_global_variables(NULL);

        /*Initialize AML layer*/
        str_twi_aml_in.pf_aml_cb = twi_ble_aml_cb;
        str_twi_aml_in.u16_profile_id = PROFILE_ID;
        TWI_MEMCPY(&str_twi_aml_in.au8_manu_data[0], &str_fw_version, sizeof(tstr_fw_version));
        s32_retval = twi_aml_init(&str_twi_aml_in);
        TWI_ERROR_BREAK(s32_retval);

		if((NULL != pstr_twi_rhp_app_in) && (NULL!= pf_rqst_ntfy))
        {
            gpf_rqst_ntfy = pf_rqst_ntfy; 
        }
        else
        {
            s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
            break;
        }

		s32_retval = twi_aml_change_device_serial(pu8_twi_sas_sender_id);
        TWI_ERROR_BREAK(s32_retval);

		s32_retval = session_status_update(get_operating_mode()); 
		if (s32_retval == TWI_SUCCESS)
		{
			RHP_APP_LOG("The session status is succesuflly updated \r\n");
		}
		else 
		{
			RHP_APP_LOG_ERR("The session status updating is failed with ERR %d \r\n",s32_retval);
		}

#ifdef INSTANCE_SENSORS_READING
		s32_retval = start_timer(&gstr_high_rate_timer, (twi_s8*) "100 ms Timer", TWI_TIMER_TYPE_PERIODIC, (twi_u32) _100_MS_PERIOD, timer_high_rate_callback, NULL);
		TWI_ERROR_BREAK(s32_retval);

		s32_retval = start_timer(&gstr_low_rate_timer, (twi_s8*) "one sec Timer", TWI_TIMER_TYPE_PERIODIC, (twi_u32) ONE_SEC_PERIOD, timer_low_rate_callback, NULL);
		TWI_ERROR_BREAK(s32_retval);
#endif

#ifdef TEST_GPIOS_SNIFFING
		twi_gpio_init();
		TWI_ERROR_BREAK(s32_retval);

		twi_gpio_select(TWI_PORTA, TWI_PIN17);
		TWI_ERROR_BREAK(s32_retval);
		twi_gpio_set_configure(TWI_PORTA, TWI_PIN17, TWI_GPIO_DIR_OUT, TWI_PIN_FUNC_GPIO, TWI_INVALID_CHANNEL_NUM);
		TWI_ERROR_BREAK(s32_retval);
		twi_gpio_clear(TWI_PORTA , TWI_PIN17);
		TWI_ERROR_BREAK(s32_retval);
		
		twi_gpio_select(TWI_PORTA, TWI_PIN20);
		TWI_ERROR_BREAK(s32_retval);
		twi_gpio_set_configure(TWI_PORTA, TWI_PIN20, TWI_GPIO_DIR_OUT, TWI_PIN_FUNC_GPIO, TWI_INVALID_CHANNEL_NUM);
		TWI_ERROR_BREAK(s32_retval);
		twi_gpio_clear(TWI_PORTA , TWI_PIN20);
		TWI_ERROR_BREAK(s32_retval);

		twi_gpio_select(TWI_PORTA, TWI_PIN7);
		TWI_ERROR_BREAK(s32_retval);
		twi_gpio_set_configure(TWI_PORTA, TWI_PIN7, TWI_GPIO_DIR_OUT, TWI_PIN_FUNC_GPIO, TWI_INVALID_CHANNEL_NUM);
		TWI_ERROR_BREAK(s32_retval);
		twi_gpio_clear(TWI_PORTA , TWI_PIN7);
		TWI_ERROR_BREAK(s32_retval);
#endif
	}while (0);
	
	return TWI_SUCCESS;
}

void twi_rhp_app_deinit(void)
{
	/* TODO */
}

void twi_rhp_engine_evt_handler(tenu_rhp_engine_evt_type enu_engine_evt, void* pv_evt_data)
{
	twi_s32 s32_retval = TWI_SUCCESS;
	tstr_twi_ble_evt *pstr_ble_evt 	= (tstr_twi_ble_evt*) pv_evt_data;

	switch (enu_engine_evt)
	{
		case ATTRIBUTE_CHANGED_INTERNALLY:
		case ATTRIBUTE_CHANGED_EXTERNALLY:
		{
			tstr_twi_rhp_attr * pstr_twi_rhp_attr = (tstr_twi_rhp_attr *) pv_evt_data;

			/* Sensor session status */
			if(	(pstr_twi_rhp_attr->enu_attr_type == FEATURE_ATTR) &&
				(pstr_twi_rhp_attr->parent_index == FEATURE_THREE_IDX) &&
        		(pstr_twi_rhp_attr->attr_index == ATTRIBUTE_ZERO_IDX))
			{
				RHP_APP_LOG("The session status recieved \r\n");
				RHP_APP_LOG("Session Operating Mode = %d \r\n",DEVICE_OPERATING_MODE);
				RHP_APP_LOG("L0 Acc Log Counts = %d \r\n",LOGGER_0_SESSION_ACC_READING);
				RHP_APP_LOG("L0 Press Log Counts = %d \r\n",LOGGER_0_SESSION_PRESS_READING);
				RHP_APP_LOG("L0 Temp Log Counts = %d \r\n",LOGGER_0_SESSION_TEMP_READING);
				RHP_APP_LOG("L0 Force Log Countss = %d \r\n",LOGGER_0_SESSION_FORCE_READING);
				RHP_APP_LOG("L0 PH Log Counts = %d \r\n",LOGGER_0_SESSION_PH_READING);
				RHP_APP_LOG("L1 Acc Log Counts = %d \r\n",LOGGER_1_SESSION_ACC_READING);
				RHP_APP_LOG("L1 Press Log Counts = %d \r\n",LOGGER_1_SESSION_PRESS_READING);
				RHP_APP_LOG("L1 Temp Log Counts = %d \r\n",LOGGER_1_SESSION_FORCE_READING);
				RHP_APP_LOG("L1 Force Log Counts = %d \r\n",LOGGER_1_SESSION_TEMP_READING);
				RHP_APP_LOG("L1 PH Log Counts = %d \r\n",LOGGER_1_SESSION_PH_READING);
			}

			/* Device operation mode */
			if(	(pstr_twi_rhp_attr->enu_attr_type == FEATURE_ATTR) &&
				(pstr_twi_rhp_attr->parent_index == FEATURE_THREE_IDX) &&
        		(pstr_twi_rhp_attr->attr_index == ATTRIBUTE_ONE_IDX))
			{
				twi_u8 u8_mode_of_operation = pstr_twi_rhp_attr->pstr_value->uni_value.u8_int;

				if (gb_running_mode == TWI_FALSE)
				{
					if (u8_mode_of_operation == ALIGN_TAG_CONTINUS_MODE)
					{
						RHP_APP_LOG("Operating mode =  %d \r\n",u8_mode_of_operation);
						s32_retval = session_status_update(u8_mode_of_operation);
						if (s32_retval == TWI_SUCCESS)
						{
							RHP_APP_LOG("The session status is succesuflly updated  %d \r\n");
						}
						else 
						{
							RHP_APP_LOG_ERR("The session status updating is failed with ERR %d \r\n",s32_retval);
						}
					}
					else
					{
						RHP_APP_LOG_ERR("The operating mode %d is not supported \r\n",u8_mode_of_operation);
					}
				}
				else 
				{
					RHP_APP_LOG_ERR("The operating mode can not be changed in the running mode \r\n");
				}
			}

			/*notified with the updated UTC ref time*/
			if((pstr_twi_rhp_attr->attr_index == RHP_RSVD_ATTR_UTC_NUM) && 
        	(pstr_twi_rhp_attr->parent_index == TWI_RHP_RESERVED_FEATURE_NUM))
       	 	{
                RHP_APP_LOG("The UTC refrence is updated = 0x%X (%d) \r\n",pstr_twi_rhp_attr->pstr_value->uni_value.u32_int,pstr_twi_rhp_attr->pstr_value->uni_value.u32_int);
        	}

			/* Logger 0 & 1 status */
			if(	(pstr_twi_rhp_attr->enu_attr_type == LOGGER_ATTR) &&
        		(pstr_twi_rhp_attr->attr_index == LOGGER_STATUS))
			{
				if (pstr_twi_rhp_attr->pstr_value->uni_value.u32_int == LOGGER_STARTED)
				{
					RHP_APP_LOG("Logger %d Session started \r\n",pstr_twi_rhp_attr->parent_index);
#ifndef INSTANCE_SENSORS_READING
					s32_retval = start_timer(&gstr_high_rate_timer, (twi_s8*) "100 ms Timer", TWI_TIMER_TYPE_PERIODIC, (twi_u32) _100_MS_PERIOD, timer_high_rate_callback, NULL);
					TWI_ERROR_BREAK(s32_retval);

					s32_retval = start_timer(&gstr_low_rate_timer, (twi_s8*) "one sec Timer", TWI_TIMER_TYPE_PERIODIC, (twi_u32) ONE_SEC_PERIOD, timer_low_rate_callback, NULL);
					TWI_ERROR_BREAK(s32_retval);
#endif
				}
				else if (pstr_twi_rhp_attr->pstr_value->uni_value.u32_int == LOGGER_STOPPED_EXTERNALLY)
				{
					RHP_APP_LOG("Logger %d Session stoped \r\n",pstr_twi_rhp_attr->parent_index);
#ifndef INSTANCE_SENSORS_READING
					s32_retval = stop_timer(&gstr_high_rate_timer);
					TWI_ERROR_BREAK(s32_retval);

					s32_retval = stop_timer(&gstr_low_rate_timer);
					TWI_ERROR_BREAK(s32_retval);
#endif
				}
				else if (pstr_twi_rhp_attr->pstr_value->uni_value.u32_int == LOGGER_REACHED_MAX_MEMORY)
				{
					RHP_APP_LOG_ERR("Logger %d reached max memory size \r\n",pstr_twi_rhp_attr->parent_index);
				}
				else 
				{
					RHP_APP_LOG_ERR("Unsupported logger %d session status \r\n",pstr_twi_rhp_attr->parent_index);
				}
			}

			break;
		}
		case BLE_EVT:
		{
			switch(pstr_ble_evt->enu_evt)
			{
				case TWI_BLE_EVT_DISCONNECTED:
				{

                	twi_s32 s32_retval = TWI_SUCCESS;
                	RHP_APP_LOG("Align Tag is disconnected\n");
                	tstr_twi_rhp_value str_ble_adv_val;
                	s32_retval = twi_rhp_read_attr(BLE_START_STOP_ADV_ATTRIBUTE,&str_ble_adv_val);
               		if((TWI_SUCCESS == s32_retval) && (BLE_ADVERTISE_START == str_ble_adv_val.uni_value.u8_int))
                	{
                    	s32_retval = twi_rhp_read_attr(BLE_PERIPHERAL_CONNECT_STATUS, &str_ble_adv_val);
                   	 	if((TWI_SUCCESS == s32_retval) && (str_ble_adv_val.uni_value.u8_int == BLE_CONN_PERIPHERAL_DISCONNECTED))
                    	{
                        	tenu_rhp_engine_sys_mode enu_sys_mode = INVALID_MODE;
                        	tstr_notifiy_request	str_rqst_ntfy;
   
                        	str_rqst_ntfy.enu_type = GET_SYS_MODE;
                        	str_rqst_ntfy.pv_data = &enu_sys_mode;
                        	if(NULL!= gpf_rqst_ntfy)
                        	{
                            	gpf_rqst_ntfy(&str_rqst_ntfy);  
                        	} 
                        	if(RUNNING_MODE != enu_sys_mode)
                        	{
                            
                        	}
                    	}
                    	else
                    	{	
                    	    /*Do Nothing*/
                    	}
						
                    	/*To re_start advertising after disconnection in Nordic*/
                    	s32_retval = twi_ble_start_adv(TWI_BLE_ADV_UNCHANGED);
                	}
                	twi_aml_reset_adv_pkt_count_time();
            	}
			default:
				/* Do Nothing */
				break;
			
			}
		}
		case SYS_MODE_CHANGED:
		{ 
			tenu_rhp_engine_sys_mode enu_sys_mode = *(tenu_rhp_engine_sys_mode *)pv_evt_data;
			if(RUNNING_MODE == enu_sys_mode)
			{
				RHP_APP_LOG("RUNNING_MODE.\r\n");
				gb_running_mode = TWI_TRUE;
			}
			break;
		}

		case SDK_REQUEST:
    	{
			tstr_twi_u8_array str_twi_u8_array;
        	TWI_MEMCPY(&str_twi_u8_array, pv_evt_data, sizeof(tstr_twi_u8_array));
		
       	 	if((str_twi_u8_array.pu8_data != NULL) && (str_twi_u8_array.u16_len > 0))
        	{
            	switch(str_twi_u8_array.pu8_data[SDK_OP_CODE_LOC])
            	{
					case TWI_EVENT_CHANGE_DEVICE_SERIAL:
               	 	{
                    	twi_aml_change_device_serial(&str_twi_u8_array.pu8_data[SDK_DATA_LOC]);                 
                	}
                		break;

                	case TWI_EVENT_CHANGE_DST_STATUS:
                	{
                    	if(str_twi_u8_array.pu8_data[SDK_DATA_LOC+1] < AML_EVT_INVALID)
                    	{
                        	twi_aml_change_dst_status(str_twi_u8_array.pu8_data[SDK_DATA_LOC] , str_twi_u8_array.pu8_data[SDK_DATA_LOC+1]);
                    	}                       
                	}
                		break;

                	default:
                    	break;	
				}
			}
		}

		// Here we will handle the nudge finish event raised from the RHP
    	case NUDGE_CONNECTED_DEVICE_SUCCESS:
   	 	{
        	twi_u8 u8_i  =0;
        	for(u8_i = 0 ; u8_i < INVALID_NUDGE_OPCODE ; u8_i++)
        	{
            	if(gastr_nudging_data_parameters[u8_i].b_is_nudge_in_progress == TWI_TRUE)
            	{
                	RHP_APP_LOG("NUDGE_CONNECTED_DEVICE_SUCCESS EVENT! OPCODE %d \r\n",u8_i);
                	twi_s32 s32_retval = TWI_ERROR;
                	gstr_app_dispatcher_flags.au8_nudge_data_succeeded[u8_i] = TWI_TRUE;
                	// Stop the nudge timer
                	s32_retval = stop_timer(&gastr_nudge_data_retry_timer[u8_i]);
                	TWI_ERROR_BREAK(s32_retval);
            	}
            	else
            	{
					/* Do Nothing */
                	/*RHP_APP_LOG("NUDGE with OPCODE %x DIDN'T STARTED!\r\n",u8_i);*/
            	}
       	 	}

			u8_i  =0;
			for(u8_i = 0 ; u8_i < INVALID_ALIGN_LOGGER_INDEX ; u8_i++)
        	{
            	if(gastr_nudging_logs_parameters[u8_i].b_is_nudge_in_progress == TWI_TRUE)
            	{
                	RHP_APP_LOG("NUDGE_CONNECTED_DEVICE_SUCCESS EVENT! INDEX %d \r\n",u8_i);
                	twi_s32 s32_retval = TWI_ERROR;
                	gstr_app_dispatcher_flags.au8_nudge_logs_succeeded[u8_i] = TWI_TRUE;
                	// Stop the nudge timer
                	s32_retval = stop_timer(&gastr_nudge_logs_retry_timer[u8_i]);
                	TWI_ERROR_BREAK(s32_retval);
            	}
            	else
            	{
					/* Do Nothing */
                	/*RHP_APP_LOG("NUDGE with INDEX %x DIDN'T STARTED!\r\n",u8_i);*/
            	}
       	 	}
        	break;
    	}

		case EVENT_LOGGING_IS_DONE:
		{
#ifdef TEST_GPIOS_SNIFFING
			TAKE_LOGS_DONE_CH3;
#endif	
#ifdef PACKET_DATA_TESTING
			RHP_APP_LOG("EVENT_LOGGING_IS_DONE for loger index %d \r\n",((tstr_twi_rhp_logger*)pv_evt_data)->u8_logger_index);
#endif
		}

		default:
			break;
	}
	
}

void twi_rhp_app_evt_handler(twi_u8 u8_app_event, twi_u8 u8_attr_num, const tstr_twi_rhp_attr* const * ppstr_attrs)
{
	
}

twi_s32 twi_rhp_app_load(const tstr_twi_rhp_app_load_in* pstr_twi_rhp_app_load_in)
{
	twi_s32 s32_retval = TWI_SUCCESS;

	if (GET_LOGGER_0_SESSSION_STATUS == LOGGER_STARTED)
	{
		RHP_APP_LOG("Logger 0 Session started \r\n");
#ifndef INSTANCE_SENSORS_READING
		TWI_ASSERT(TWI_SUCCESS == start_timer(&gstr_high_rate_timer, (twi_s8*) "100 ms Timer", TWI_TIMER_TYPE_PERIODIC, (twi_u32) _100_MS_PERIOD, timer_high_rate_callback, NULL));
		TWI_ASSERT(TWI_SUCCESS == start_timer(&gstr_low_rate_timer, (twi_s8*) "one sec Timer", TWI_TIMER_TYPE_PERIODIC, (twi_u32) ONE_SEC_PERIOD, timer_low_rate_callback, NULL));
#endif
	}
	else if (GET_LOGGER_0_SESSSION_STATUS == LOGGER_STOPPED_EXTERNALLY)
	{
		RHP_APP_LOG("Logger 0 Session stoped \r\n");
#ifndef INSTANCE_SENSORS_READING
		TWI_ASSERT(TWI_SUCCESS == stop_timer(&gstr_high_rate_timer));
		TWI_ASSERT(TWI_SUCCESS == stop_timer(&gstr_low_rate_timer));
#endif
	}

	return s32_retval;
}

void twi_rhp_app_dispatch(void)
{
	twi_s32 s32_retval = TWI_ERROR;
#ifdef TEST_GPIOS_SNIFFING
	DISPATCH_START_CH4;
#endif
	/**************************************************** Nudge Battery Level ****************************************************/
    if((gstr_app_dispatcher_flags.gb_notify_battery_percentage) == TWI_TRUE)
    {
        if (IS_DEVICE_CONNECTED)
        {
            s32_retval = nudge_peer_data(BATTERY_PERC_UPDATE_OPCODE,BATTERY_PERC_UPDATE_PARENT_IDX,BATTERY_PERC_UPDATE_ATT_IDX);
            if(TWI_SUCCESS == s32_retval)
            {
                RHP_APP_LOG("Start Nudge with dispensing status update OPCODE!\r\n");
            }
            else
            {
                RHP_APP_LOG_ERR("Failed to Nudge Mobile With battery updates Status With Err = %d\r\n",s32_retval);
                /*Start the fast nudging timer*/
                s32_retval = stop_timer(&gastr_nudge_data_retry_timer[BATTERY_PERC_UPDATE_OPCODE]);
                if(s32_retval != TWI_SUCCESS)
                {
                    RHP_APP_LOG_ERR("Failed to stop the Fast Nudge Retry Timer With Err = %d\r\n", s32_retval);
                }
                s32_retval = start_timer(&gastr_nudge_data_retry_timer[BATTERY_PERC_UPDATE_OPCODE], (twi_s8*) "Fast Nudge Retry Timer", TWI_TIMER_TYPE_ONE_SHOT, (twi_u32) FAST_NUDGE_RETRY_TIME_MS, nudge_data_retry_timer_callback, &gastr_nudging_data_parameters[BATTERY_PERC_UPDATE_OPCODE].u8_op_code);
                if(s32_retval != TWI_SUCCESS)
                {
                    RHP_APP_LOG_ERR("Failed to start the Fast Nudge Retry Timer With Err = %d\r\n", s32_retval);
                }
            }
            gstr_app_dispatcher_flags.gb_notify_battery_percentage = TWI_FALSE;  
        }             
        else
        {
            RHP_APP_LOG_ERR("Not Connected, Can not nudge \n");
        }
    }

	/**************************************************** Report Logger 0 ****************************************************/
	if((gstr_app_dispatcher_flags.gb_logger_index_zero_report) == TWI_TRUE)
    {
        if (IS_DEVICE_CONNECTED && gb_running_mode)
        {
            s32_retval = nudge_peer_logs(ALIGN_LOGGER_INDEX_ZERO,OUTPUT_CLOUD_DEST);
            if(TWI_SUCCESS == s32_retval)
            {
                RHP_APP_LOG("Start logger nudge report with index %d !\r\n",ALIGN_LOGGER_INDEX_ZERO);
            }
            else
            {
                RHP_APP_LOG_ERR("Failed to Nudge Mobile With logger with index %d With Err = %d\r\n",ALIGN_LOGGER_INDEX_ZERO, s32_retval);
                /*Start the fast nudging timer*/
                s32_retval = stop_timer(&gastr_nudge_logs_retry_timer[ALIGN_LOGGER_INDEX_ZERO]);
	            if(s32_retval != TWI_SUCCESS)
                {
                    RHP_APP_LOG_ERR("Failed to stop the Fast Nudge Retry Timer With Err = %d\r\n", s32_retval);
                }
                s32_retval = start_timer(&gastr_nudge_logs_retry_timer[ALIGN_LOGGER_INDEX_ZERO], (twi_s8*) "Fast Nudge Retry Timer", TWI_TIMER_TYPE_ONE_SHOT, (twi_u32) FAST_NUDGE_RETRY_TIME_MS, nudge_logs_retry_timer_callback, &gastr_nudging_logs_parameters[ALIGN_LOGGER_INDEX_ZERO].u8_tp_logger_index);
                if(s32_retval != TWI_SUCCESS)
                {
                    RHP_APP_LOG_ERR("Failed to start the Fast Nudge Retry Timer With Err = %d\r\n", s32_retval);
                }
            }
            gstr_app_dispatcher_flags.gb_logger_index_zero_report = TWI_FALSE;  
        }             
        else
        {
            RHP_APP_LOG_ERR("Not Connected, Can not nudge \n");
        }
    }

	/**************************************************** Report Logger 1 ****************************************************/
	if((gstr_app_dispatcher_flags.gb_logger_index_one_report) == TWI_TRUE)
    {
        if (IS_DEVICE_CONNECTED && gb_running_mode)
        {
            s32_retval = nudge_peer_logs(ALIGN_LOGGER_INDEX_ONE,OUTPUT_CLOUD_DEST);
            if(TWI_SUCCESS == s32_retval)
            {
                RHP_APP_LOG("Start logger nudge report with index %d !\r\n",ALIGN_LOGGER_INDEX_ONE);
            }
            else
            {
                RHP_APP_LOG_ERR("Failed to Nudge Mobile With logger with index %d With Err = %d\r\n",ALIGN_LOGGER_INDEX_ONE, s32_retval);
                /*Start the fast nudging timer*/
                s32_retval = stop_timer(&gastr_nudge_logs_retry_timer[ALIGN_LOGGER_INDEX_ONE]);
	            if(s32_retval != TWI_SUCCESS)
                {
                    RHP_APP_LOG_ERR("Failed to stop the Fast Nudge Retry Timer With Err = %d\r\n", s32_retval);
                }
                s32_retval = start_timer(&gastr_nudge_logs_retry_timer[ALIGN_LOGGER_INDEX_ONE], (twi_s8*) "Fast Nudge Retry Timer", TWI_TIMER_TYPE_ONE_SHOT, (twi_u32) FAST_NUDGE_RETRY_TIME_MS, nudge_logs_retry_timer_callback, &gastr_nudging_logs_parameters[ALIGN_LOGGER_INDEX_ONE].u8_tp_logger_index);
                if(s32_retval != TWI_SUCCESS)
                {
                    RHP_APP_LOG_ERR("Failed to start the Fast Nudge Retry Timer With Err = %d\r\n", s32_retval);
                }
            }
            gstr_app_dispatcher_flags.gb_logger_index_one_report = TWI_FALSE;  
        }             
        else
        {
            RHP_APP_LOG_ERR("Not Connected, Can not nudge \n");
        }
    }

	/**************************************************** Get pressure Sensor Data ****************************************************/
	if(GET_BIT_STATUS(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_PRESS_SENSOR_IDX))
	{
		twi_u32 u32_little_end_data = 0;

#ifdef TEST_TRI_WAVE
		static twi_u8 u8_count = 0;
		static tenu_data_counting_mode tenu_counting_direction_flag = PRESS_COUNT_UP; 
#endif 

		TWI_CLR_BIT(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_PRESS_SENSOR_IDX);
/* Real Values */
#ifndef MOCK_SENSORS
		tstr_twi_rhp_value str_sensor_reading = {0};
		twi_s32 s32_retval = TWI_SUCCESS;

#ifdef TEST_GPIOS_SNIFFING
		READ_ATT_START_CH4;
#endif
		s32_retval = twi_rhp_read_attr(PRESSURE_SENSOR_ATTRIBUTE,&str_sensor_reading);
		if(s32_retval == TWI_SUCCESS)
		{
#ifdef TEST_GPIOS_SNIFFING
			READ_ATT_END_CH4;
#endif
#ifdef INSTANCE_SENSORS_READING
			TWI_LOGGER("Press = %d \n",str_sensor_reading.uni_value.u32_int);	
#endif	
			/* convert bytes from big endian to little endian */
			u32_little_end_data = BTOL32(str_sensor_reading.uni_value.u32_int);
		}
		else
		{
			/* Synchronizing Sensor Data */ 
			u32_little_end_data = PRESS_SENSOR_ERROR_VALUE;
			RHP_APP_LOG_ERR("Error occurs while pressure reading with error = %d, Press = %d \r\n",s32_retval, u32_little_end_data);
		}

#ifdef TEST_TRI_WAVE
		u32_little_end_data = u8_count;
		if(tenu_counting_direction_flag == PRESS_COUNT_UP)
		{
			u8_count += 1;
			if(u8_count == MAX_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = PRESS_COUNT_DOWN;
			}
		}
		else if(tenu_counting_direction_flag == PRESS_COUNT_DOWN)
		{
			u8_count -= 1;
			if(u8_count == MIN_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = PRESS_COUNT_UP;
			}
		}
		TWI_LOGGER("T.W: Press = %d \r\n",u32_little_end_data);
		u32_little_end_data = BTOL32(u32_little_end_data);
#endif
		TWI_MEMCPY(&(gau8_press_logged_data[gu8_press_readings_counter*4]), &u32_little_end_data, sizeof(twi_u32));

/* Mocked Values */
#else
		tstr_twi_rhp_value str_mocked_data_val;
		TWI_MEMSET(&str_mocked_data_val , 0 ,sizeof(tstr_twi_rhp_value));
		twi_u32 u32_random_number = rand();
		str_mocked_data_val.enu_type = U32;
	    str_mocked_data_val.uni_value.u32_int = ((u32_random_number % PRESS_VALUE_UPPER_LIMIT));
		if(str_mocked_data_val.uni_value.u32_int < PRESS_VALUE_LOWER_LIMIT)
		{
			str_mocked_data_val.uni_value.u32_int += PRESS_VALUE_LOWER_LIMIT;
		}
#ifdef INSTANCE_SENSORS_READING
			TWI_LOGGER("Press = %d \n",str_mocked_data_val.uni_value.u32_int);	
#endif	
		TWI_ASSERT(TWI_SUCCESS == twi_rhp_write_attr(PRESSURE_SENSOR_ATTRIBUTE, &str_mocked_data_val));
		/* convert bytes from big endian to little endian */
		u32_little_end_data = BTOL32(str_mocked_data_val.uni_value.u32_int);

#ifdef TEST_TRI_WAVE
			u32_little_end_data = u8_count;
			if(tenu_counting_direction_flag == PRESS_COUNT_UP)
			{
				u8_count += 1;
				if(u8_count == MAX_COUNTING_VALUE)
				{
					tenu_counting_direction_flag = PRESS_COUNT_DOWN;
				}
			}
			else if(tenu_counting_direction_flag == PRESS_COUNT_DOWN)
			{
				u8_count -= 1;
				if(u8_count == MIN_COUNTING_VALUE)
				{
					tenu_counting_direction_flag = PRESS_COUNT_UP;
				}
			}
			TWI_LOGGER("T.W: Press = %d \r\n",u32_little_end_data);
			u32_little_end_data = BTOL32(u32_little_end_data);
#endif
		TWI_MEMCPY(&(gau8_press_logged_data[gu8_press_readings_counter*4]), &u32_little_end_data, sizeof(twi_u32));
#endif

		gu8_press_readings_counter ++;

		if(gu8_press_readings_counter == PRESS_NUMBER_OF_READINGS)
		{
			TWI_MEMCPY(&(gau8_total_logged_data[PRESS_DATA_INDEX]), &gau8_press_logged_data, sizeof(gau8_press_logged_data));
			RESET_SENSOR_DATA(gau8_press_logged_data);
			TWI_SET_BIT(gstr_app_dispatcher_flags.gu8_sensor_data_is_ready,ALIGN_PRESS_SENSOR_IDX);
			gu8_press_readings_counter = 0;
		}
	}

	/**************************************************** Get accelerometer Sensor Data ****************************************************/
	if(GET_BIT_STATUS(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_ACC_SENSOR_IDX))
	{
		twi_s16 s16_little_end_data = 0;

#ifdef TEST_TRI_WAVE
		static twi_u8 u8_count = 0;
		static tenu_data_counting_mode tenu_counting_direction_flag = ACC_COUNT_UP; 
#endif 
		TWI_CLR_BIT(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_ACC_SENSOR_IDX);

/* Real Values */
#ifndef MOCK_SENSORS
		twi_s32 s32_retval = TWI_SUCCESS;
		tstr_twi_rhp_value str_sensor_reading = {0};

		/* X-Axis */
#ifdef TEST_GPIOS_SNIFFING
		READ_ATT_START_CH4;
#endif
		s32_retval = twi_rhp_read_attr(X_ACC_SENSOR_ATTRIBUTE,&str_sensor_reading);
		if(s32_retval == TWI_SUCCESS)
		{
#ifdef TEST_GPIOS_SNIFFING
			READ_ATT_END_CH4;
#endif
#ifdef INSTANCE_SENSORS_READING
			TWI_LOGGER("X-Axis = %d \n",str_sensor_reading.uni_value.s16_int);
#endif	
			/* convert bytes from big endian to little endian */
			s16_little_end_data = BTOL16(str_sensor_reading.uni_value.s16_int);
		}
		else
		{
			/* Synchronizing Sensor Data */ 
			s16_little_end_data = ACC_SENSOR_AXIS_ERROR_VALUE;
			RHP_APP_LOG_ERR("Error occurs while accelerometer x-axis reading with error = %d, X-Axis = %d \r\n",s32_retval, s16_little_end_data);
		}

#ifdef TEST_TRI_WAVE
		s16_little_end_data = u8_count;
		TWI_LOGGER("T.W: X-Axis = %d \r\n",s16_little_end_data);
		s16_little_end_data = BTOL16(s16_little_end_data);
#endif
		TWI_MEMCPY(&(gau8_acc_logged_data[(gu8_acc_readings_counter*6)]), &s16_little_end_data, sizeof(twi_u16));

		/* Y-Axis */
#ifdef TEST_GPIOS_SNIFFING
		READ_ATT_START_CH4;
#endif
		s32_retval = twi_rhp_read_attr(Y_ACC_SENSOR_ATTRIBUTE,&str_sensor_reading);
		if(s32_retval == TWI_SUCCESS)
		{
#ifdef TEST_GPIOS_SNIFFING
			READ_ATT_END_CH4;
#endif
#ifdef INSTANCE_SENSORS_READING
			TWI_LOGGER("Y-Axis = %d \n",str_sensor_reading.uni_value.s16_int);
#endif	
			/* convert bytes from big endian to little endian */
			s16_little_end_data = BTOL16(str_sensor_reading.uni_value.s16_int);
		}
		else
		{
			/* Synchronizing Sensor Data */ 
			s16_little_end_data = ACC_SENSOR_AXIS_ERROR_VALUE;
			RHP_APP_LOG_ERR("Error occurs while accelerometer y-axis reading with error = %d, Y-Axis = %d \r\n",s32_retval, s16_little_end_data);
		}

#ifdef TEST_TRI_WAVE
		s16_little_end_data = u8_count;
		TWI_LOGGER("T.W: Y-Axis = %d \r\n",s16_little_end_data);
		s16_little_end_data = BTOL16(s16_little_end_data);
#endif
		TWI_MEMCPY(&(gau8_acc_logged_data[(gu8_acc_readings_counter*6) + 2]), &s16_little_end_data, sizeof(twi_u16));

		/* Z-Axis */
#ifdef TEST_GPIOS_SNIFFING
		READ_ATT_START_CH4;
#endif
		s32_retval = twi_rhp_read_attr(Z_ACC_SENSOR_ATTRIBUTE,&str_sensor_reading);
		if(s32_retval == TWI_SUCCESS)
		{
#ifdef TEST_GPIOS_SNIFFING
			READ_ATT_END_CH4;
#endif
#ifdef INSTANCE_SENSORS_READING
			TWI_LOGGER("Z-Axis = %d \n",str_sensor_reading.uni_value.s16_int);
#endif	
			/* convert bytes from big endian to little endian */
			s16_little_end_data = BTOL16(str_sensor_reading.uni_value.s16_int);
		}
		else
		{
			/* Synchronizing Sensor Data */ 
			s16_little_end_data = ACC_SENSOR_AXIS_ERROR_VALUE;
			RHP_APP_LOG_ERR("Error occurs while accelerometer z-axis reading with error = %d, Z-Axis = %d \r\n",s32_retval, s16_little_end_data);
		}

#ifdef TEST_TRI_WAVE
		s16_little_end_data = u8_count;
		TWI_LOGGER("T.W: Z-Axis = %d \r\n",s16_little_end_data);
		s16_little_end_data = BTOL16(s16_little_end_data);

		if(tenu_counting_direction_flag == ACC_COUNT_UP)
		{
			u8_count += 1;
			if(u8_count == MAX_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = ACC_COUNT_DOWN;
			}
		}
		else if(tenu_counting_direction_flag == ACC_COUNT_DOWN)
		{
			u8_count -= 1;
			if(u8_count == MIN_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = ACC_COUNT_UP;
			}
		}
#endif
		TWI_MEMCPY(&(gau8_acc_logged_data[(gu8_acc_readings_counter*6) + 4]), &s16_little_end_data, sizeof(twi_u16));

/* Mocked Values */
#else
		tstr_twi_rhp_value str_mocked_data_val;
		TWI_MEMSET(&str_mocked_data_val , 0 ,sizeof(tstr_twi_rhp_value));
		twi_u32 u32_random_number = rand();
		str_mocked_data_val.enu_type = S16;
		str_mocked_data_val.uni_value.s16_int = ((twi_s16)(u32_random_number % ACC_VALUE_UPPER_LIMIT));
#ifdef INSTANCE_SENSORS_READING
		TWI_LOGGER("X-Axis = %d \n",str_mocked_data_val.uni_value.s16_int);	
#endif	
		TWI_ASSERT(TWI_SUCCESS == twi_rhp_write_attr(X_ACC_SENSOR_ATTRIBUTE, &str_mocked_data_val));
		/* convert bytes from big endian to little endian */
		s16_little_end_data = BTOL16(str_mocked_data_val.uni_value.s16_int);
#ifdef TEST_TRI_WAVE
		s16_little_end_data = u8_count;
		TWI_LOGGER("T.W: X-Axis = %d \r\n",s16_little_end_data);
		s16_little_end_data = BTOL16(s16_little_end_data);
#endif
		TWI_MEMCPY(&(gau8_acc_logged_data[(gu8_acc_readings_counter*6)]), &s16_little_end_data, sizeof(twi_u16));

		u32_random_number = rand();
		str_mocked_data_val.enu_type = S16;
		str_mocked_data_val.uni_value.s16_int = ((twi_s16)(u32_random_number % ACC_VALUE_UPPER_LIMIT));
#ifdef INSTANCE_SENSORS_READING
		TWI_LOGGER("Y-Axis = %d \n",str_mocked_data_val.uni_value.s16_int);	
#endif	
		TWI_ASSERT(TWI_SUCCESS == twi_rhp_write_attr(Y_ACC_SENSOR_ATTRIBUTE, &str_mocked_data_val));
		/* convert bytes from big endian to little endian */
		s16_little_end_data = BTOL16(str_mocked_data_val.uni_value.s16_int);
#ifdef TEST_TRI_WAVE
		s16_little_end_data = u8_count;
		TWI_LOGGER("T.W: Y-Axis = %d \r\n",s16_little_end_data);
		s16_little_end_data = BTOL16(s16_little_end_data);
#endif
		TWI_MEMCPY(&(gau8_acc_logged_data[(gu8_acc_readings_counter*6) + 2]), &s16_little_end_data, sizeof(twi_u16));
				
		u32_random_number = rand();
		str_mocked_data_val.enu_type = S16;
		str_mocked_data_val.uni_value.s16_int = ((twi_s16)(u32_random_number % ACC_VALUE_UPPER_LIMIT));
#ifdef INSTANCE_SENSORS_READING
		TWI_LOGGER("Z-Axis = %d \n",str_mocked_data_val.uni_value.s16_int);	
#endif	
		TWI_ASSERT(TWI_SUCCESS == twi_rhp_write_attr(Z_ACC_SENSOR_ATTRIBUTE, &str_mocked_data_val));
		/* convert bytes from big endian to little endian */
		s16_little_end_data = BTOL16(str_mocked_data_val.uni_value.s16_int);
#ifdef TEST_TRI_WAVE
		s16_little_end_data = u8_count;
		TWI_LOGGER("T.W: Z-Axis = %d \r\n",s16_little_end_data);
		s16_little_end_data = BTOL16(s16_little_end_data);

		if(tenu_counting_direction_flag == ACC_COUNT_UP)
		{
			u8_count += 1;
			if(u8_count == MAX_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = ACC_COUNT_DOWN;
			}
		}
		else if(tenu_counting_direction_flag == ACC_COUNT_DOWN)
		{
			u8_count -= 1;
			if(u8_count == MIN_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = ACC_COUNT_UP;
			}
		}
#endif
		TWI_MEMCPY(&(gau8_acc_logged_data[(gu8_acc_readings_counter*6) + 4]), &s16_little_end_data, sizeof(twi_u16));
#endif
		gu8_acc_readings_counter ++;

		if(gu8_acc_readings_counter == ACC_NUMBER_OF_READINGS)
		{
			TWI_MEMCPY(&(gau8_total_logged_data[ACC_DATA_INDEX]), &gau8_acc_logged_data, sizeof(gau8_acc_logged_data));
			RESET_SENSOR_DATA(gau8_acc_logged_data);
			TWI_SET_BIT(gstr_app_dispatcher_flags.gu8_sensor_data_is_ready,ALIGN_ACC_SENSOR_IDX);
			gu8_acc_readings_counter = 0;
		}
	}

	/**************************************************** Get Force Sensor Data ****************************************************/
	if(GET_BIT_STATUS(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_FORCE_SENSOR_IDX))
	{	
		twi_s16 s16_little_end_data = 0;
#ifdef TEST_TRI_WAVE
		static twi_u8 u8_count = 0;
		static tenu_data_counting_mode tenu_counting_direction_flag = FORCE_COUNT_UP; 
#endif 
		TWI_CLR_BIT(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_FORCE_SENSOR_IDX);

/* Real Values */
#ifndef MOCK_SENSORS
		tstr_twi_rhp_value str_sensor_reading = {0};
		twi_s32 s32_retval = TWI_SUCCESS;

#ifdef TEST_GPIOS_SNIFFING
		READ_ATT_START_CH4;
#endif
		s32_retval = twi_rhp_read_attr(FORCE_SENSOR_ATTRIBUTE,&str_sensor_reading);
		if(s32_retval == TWI_SUCCESS)
		{
#ifdef TEST_GPIOS_SNIFFING
			READ_ATT_END_CH4;
#endif
#ifdef INSTANCE_SENSORS_READING
			TWI_LOGGER("Force = %d \n",str_sensor_reading.uni_value.s16_int);	
#endif	
			/* convert bytes from big endian to little endian */
			s16_little_end_data = BTOL16(str_sensor_reading.uni_value.s16_int);
		}
		else
		{
			/* Synchronizing Sensor Data */ 
			s16_little_end_data = FORCE_SENSOR_ERROR_VALUE;
			RHP_APP_LOG_ERR("Error occurs while force reading with error = %d, force = %d \r\n",s32_retval, s16_little_end_data);
		}
#ifdef TEST_TRI_WAVE
		s16_little_end_data = u8_count;
		if(tenu_counting_direction_flag == FORCE_COUNT_UP)
		{
			u8_count += 1;
			if(u8_count == MAX_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = FORCE_COUNT_DOWN;
			}
		}
		else if(tenu_counting_direction_flag == FORCE_COUNT_DOWN)
		{
			u8_count -= 1;
			if(u8_count == MIN_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = FORCE_COUNT_UP;
			}
		}
		TWI_LOGGER("T.W: Force = %d \r\n",s16_little_end_data);
		s16_little_end_data = BTOL16(s16_little_end_data);
#endif
		TWI_MEMCPY(&(gau8_force_logged_data[gu8_force_readings_counter*2]), &s16_little_end_data, sizeof(twi_u16));

/* Mocked Values */
#else
		tstr_twi_rhp_value str_mocked_data_val;
		TWI_MEMSET(&str_mocked_data_val , 0 ,sizeof(tstr_twi_rhp_value));
		twi_u32 u32_random_number = rand();
		str_mocked_data_val.enu_type = S16;
		str_mocked_data_val.uni_value.s16_int = ((u32_random_number % FORCE_VALUE_UPPER_LIMIT));
#ifdef INSTANCE_SENSORS_READING
			TWI_LOGGER("Force = %d \n",str_mocked_data_val.uni_value.s16_int);	
#endif	
		TWI_ASSERT(TWI_SUCCESS == twi_rhp_write_attr(FORCE_SENSOR_ATTRIBUTE, &str_mocked_data_val));
		/* convert bytes from big endian to little endian */
		s16_little_end_data = BTOL16(str_mocked_data_val.uni_value.s16_int);
#ifdef TEST_TRI_WAVE
		s16_little_end_data = u8_count;
		if(tenu_counting_direction_flag == FORCE_COUNT_UP)
		{
			u8_count += 1;
			if(u8_count == MAX_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = FORCE_COUNT_DOWN;
			}
		}
		else if(tenu_counting_direction_flag == FORCE_COUNT_DOWN)
		{
			u8_count -= 1;
			if(u8_count == MIN_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = FORCE_COUNT_UP;
			}
		}
		TWI_LOGGER("T.W: Force = %d \r\n",s16_little_end_data);
		s16_little_end_data = BTOL16(s16_little_end_data);
#endif
		TWI_MEMCPY(&(gau8_force_logged_data[gu8_force_readings_counter*2]), &s16_little_end_data, sizeof(twi_u16));
#endif

		gu8_force_readings_counter ++;

		if(gu8_force_readings_counter == FORCE_NUMBER_OF_READINGS)
		{
			TWI_MEMCPY(&(gau8_total_logged_data[FORCE_DATA_INDEX]), &gau8_force_logged_data, sizeof(gau8_force_logged_data));
			RESET_SENSOR_DATA(gau8_force_logged_data);
			TWI_SET_BIT(gstr_app_dispatcher_flags.gu8_sensor_data_is_ready,ALIGN_FORCE_SENSOR_IDX);
			gu8_force_readings_counter = 0;
		}
	}

	/**************************************************** Get Temperture Sensor Data ****************************************************/
	if(GET_BIT_STATUS(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_TEMP_SENSOR_IDX))
	{
		twi_s16 s16_little_end_data = 0;
#ifdef TEST_TRI_WAVE
		static twi_u8 u8_count = 0;
		static tenu_data_counting_mode tenu_counting_direction_flag = TEMP_COUNT_UP; 
#endif 
		TWI_CLR_BIT(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_TEMP_SENSOR_IDX);

/* Real Values */
#ifndef MOCK_SENSORS	
		twi_s32 s32_retval = TWI_SUCCESS;
		tstr_twi_rhp_value str_sensor_reading = {0};

#ifdef TEST_GPIOS_SNIFFING
		READ_ATT_START_CH4;
#endif
		s32_retval = twi_rhp_read_attr(TEMPERATURE_SENSOR_ATTRIBUTE,&str_sensor_reading);
		if(s32_retval == TWI_SUCCESS)
		{
#ifdef TEST_GPIOS_SNIFFING
			READ_ATT_END_CH4;
#endif
#ifdef INSTANCE_SENSORS_READING
			TWI_LOGGER("Temp = %d \n",str_sensor_reading.uni_value.s16_int);
#endif	
			/* convert bytes from big endian to little endian */
			s16_little_end_data = BTOL16(str_sensor_reading.uni_value.s16_int);
		}
		else
		{
			/* Synchronizing Sensor Data */ 
			s16_little_end_data = TEMP_SENSOR_ERROR_VALUE;
			RHP_APP_LOG_ERR("Error occurs while temperture reading with error = %d, Temp = %d \r\n",s32_retval, s16_little_end_data);
		}
#ifdef TEST_TRI_WAVE
		s16_little_end_data = u8_count;
		if(tenu_counting_direction_flag == TEMP_COUNT_UP)
		{
			u8_count += 1;
			if(u8_count == MAX_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = TEMP_COUNT_DOWN;
			}
		}
		else if(tenu_counting_direction_flag == TEMP_COUNT_DOWN)
		{
			u8_count -= 1;
			if(u8_count == MIN_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = TEMP_COUNT_UP;
			}
		}
		TWI_LOGGER("T.W: Temp = %d \r\n",s16_little_end_data);
		s16_little_end_data = BTOL16(s16_little_end_data);
#endif
		TWI_MEMCPY(&(gau8_temp_logged_data[gu8_temp_readings_counter*2]), &s16_little_end_data, sizeof(twi_u16));

/* Mocked Values */
#else
		tstr_twi_rhp_value str_mocked_data_val;
		TWI_MEMSET(&str_mocked_data_val , 0 ,sizeof(tstr_twi_rhp_value));
		static twi_u16 s16_temperture_value = TEMP_VALUE_LOWER_LIMIT;
		str_mocked_data_val.enu_type = S16;
	    str_mocked_data_val.uni_value.s16_int = (s16_temperture_value % TEMP_VALUE_UPPER_LIMIT);
		if(str_mocked_data_val.uni_value.s16_int < TEMP_VALUE_LOWER_LIMIT)
		{
			str_mocked_data_val.uni_value.s16_int+= TEMP_VALUE_LOWER_LIMIT;
		}
		s16_temperture_value ++;
		str_mocked_data_val.uni_value.s16_int*=100;
#ifdef INSTANCE_SENSORS_READING
		TWI_LOGGER("Temp = %d \n",str_mocked_data_val.uni_value.s16_int);	
#endif	
		TWI_ASSERT(TWI_SUCCESS == twi_rhp_write_attr(TEMPERATURE_SENSOR_ATTRIBUTE, &str_mocked_data_val));
		/* convert bytes from big endian to little endian */
		s16_little_end_data = BTOL16(str_mocked_data_val.uni_value.s16_int);

#ifdef TEST_TRI_WAVE
		s16_little_end_data = u8_count;
		if(tenu_counting_direction_flag == TEMP_COUNT_UP)
		{
			u8_count += 1;
			if(u8_count == MAX_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = TEMP_COUNT_DOWN;
			}
		}
		else if(tenu_counting_direction_flag == TEMP_COUNT_DOWN)
		{
			u8_count -= 1;
			if(u8_count == MIN_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = TEMP_COUNT_UP;
			}
		}
		TWI_LOGGER("T.W: Temp = %d \r\n",s16_little_end_data);
		s16_little_end_data = BTOL16(s16_little_end_data);
#endif
		TWI_MEMCPY(&(gau8_temp_logged_data[gu8_temp_readings_counter*2]), &s16_little_end_data, sizeof(twi_u16));
#endif
		gu8_temp_readings_counter ++;

		if(gu8_temp_readings_counter == TEMP_NUMBER_OF_READINGS)
		{
			TWI_MEMCPY(&(gau8_total_logged_data[TEMP_DATA_INDEX]), &gau8_temp_logged_data, sizeof(gau8_temp_logged_data));
			RESET_SENSOR_DATA(gau8_temp_logged_data);
			TWI_SET_BIT(gstr_app_dispatcher_flags.gu8_sensor_data_is_ready,ALIGN_TEMP_SENSOR_IDX);
			gu8_temp_readings_counter = 0;
		}
	}

	/**************************************************** Get PH Sensor Data ****************************************************/
	if(GET_BIT_STATUS(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_PH_SENSOR_IDX))
	{
		twi_u8 u8_little_end_data  = 0;
#ifdef TEST_TRI_WAVE
		static twi_u8 u8_count = 0;
		static tenu_data_counting_mode tenu_counting_direction_flag = PH_COUNT_UP; 
#endif 
		TWI_CLR_BIT(gstr_app_dispatcher_flags.gu8_get_sensor_data,ALIGN_PH_SENSOR_IDX);

/* Real Values */
#ifndef MOCK_SENSORS	
		twi_s32 s32_retval = TWI_SUCCESS;
		tstr_twi_rhp_value str_sensor_reading = {0};

#ifdef TEST_GPIOS_SNIFFING
		READ_ATT_START_CH4;
#endif
		s32_retval = twi_rhp_read_attr(PH_SENSOR_ATTRIBUTE,&str_sensor_reading);
		if(s32_retval == TWI_SUCCESS)
		{
#ifdef TEST_GPIOS_SNIFFING
			READ_ATT_END_CH4;
#endif
#ifdef INSTANCE_SENSORS_READING
			TWI_LOGGER("PH = %d \n",str_sensor_reading.uni_value.u8_int);
#endif	
			/* No endianess conversion (8-bits) */
			u8_little_end_data = str_sensor_reading.uni_value.u8_int;
		}
		else
		{
			/* Synchronizing Sensor Data */ 
			u8_little_end_data = PH_SENSOR_ERROR_VALUE;
			RHP_APP_LOG_ERR("Error occurs while PH reading with error = %d, PH = %d \r\n",s32_retval, u8_little_end_data);
		}

#ifdef TEST_TRI_WAVE
		u8_little_end_data = u8_count;
		if(tenu_counting_direction_flag == PH_COUNT_UP)
		{
			u8_count += 1;
			if(u8_count == MAX_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = PH_COUNT_DOWN;
			}
		}
		else if(tenu_counting_direction_flag == PH_COUNT_DOWN)
		{
			u8_count -= 1;
			if(u8_count == MIN_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = PH_COUNT_UP;
			}
		}
		TWI_LOGGER("T.W: PH = %d \r\n",u8_little_end_data);
#endif
		TWI_MEMCPY(&(gau8_ph_logged_data[gu8_ph_readings_counter]), &u8_little_end_data, sizeof(twi_u8));

/* Mocked Values */
#else
		tstr_twi_rhp_value str_mocked_data_val;
		TWI_MEMSET(&str_mocked_data_val , 0 ,sizeof(tstr_twi_rhp_value));
		twi_u32 u32_random_number = rand();
		str_mocked_data_val.enu_type = U8;
	    str_mocked_data_val.uni_value.u8_int = ((u32_random_number%13));
		if(str_mocked_data_val.uni_value.u8_int <1)
		{
			str_mocked_data_val.uni_value.u8_int+=1;
		}
#ifdef INSTANCE_SENSORS_READING
		TWI_LOGGER("PH = %d \n",str_mocked_data_val.uni_value.u8_int);	
#endif	
		TWI_ASSERT(TWI_SUCCESS == twi_rhp_write_attr(PH_SENSOR_ATTRIBUTE, &str_mocked_data_val));
		u8_little_end_data = str_mocked_data_val.uni_value.u8_int;

#ifdef TEST_TRI_WAVE
		u8_little_end_data = u8_count;
		if(tenu_counting_direction_flag == PH_COUNT_UP)
		{
			u8_count += 1;
			if(u8_count == MAX_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = PH_COUNT_DOWN;
			}
		}
		else if(tenu_counting_direction_flag == PH_COUNT_DOWN)
		{
			u8_count -= 1;
			if(u8_count == MIN_COUNTING_VALUE)
			{
				tenu_counting_direction_flag = PH_COUNT_UP;
			}
		}
		TWI_LOGGER("T.W: PH = %d \r\n",u8_little_end_data);
#endif
		TWI_MEMCPY(&(gau8_ph_logged_data[gu8_ph_readings_counter]), &u8_little_end_data, sizeof(twi_u8));
#endif

		gu8_ph_readings_counter ++;

		if(gu8_ph_readings_counter == PH_NUMBER_OF_READINGS)
		{
			TWI_MEMCPY(&(gau8_total_logged_data[PH_DATA_INDEX]), &gau8_ph_logged_data, sizeof(gau8_ph_logged_data));
			RESET_SENSOR_DATA(gau8_ph_logged_data);
			TWI_SET_BIT(gstr_app_dispatcher_flags.gu8_sensor_data_is_ready,ALIGN_PH_SENSOR_IDX);
			gu8_ph_readings_counter = 0;
		}
	}

	/**************************************************** Nudge success handling ****************************************************/
    twi_u8 u8_i = 0;
    for ( u8_i = 0; u8_i < INVALID_NUDGE_OPCODE; u8_i++)
    {
        if((gstr_app_dispatcher_flags.au8_nudge_data_succeeded[u8_i]) == TWI_TRUE)
        {
            RHP_APP_LOG("Success Nudge with opcode %d \n",u8_i);
            // Clear the gastr_nudging_data_parameters[u8_i] elements to allow new nudging takes place
            gastr_nudging_data_parameters[u8_i].b_is_nudge_in_progress = TWI_FALSE;
            gastr_nudging_data_parameters[u8_i].u8_op_code = 0xFF;
            gastr_nudging_data_parameters[u8_i].u8_attribute_index = 0xFF;
            gastr_nudging_data_parameters[u8_i].u8_parent_index = 0xFF;
            gstr_app_dispatcher_flags.au8_nudge_data_succeeded[u8_i] = TWI_FALSE;
            if (gstr_app_dispatcher_flags.au8_nudge_data_retry_timer_fired[u8_i] == TWI_TRUE)
            {
                RHP_APP_LOG_ERR("***************** Racing Condition Detected***************** \r\n");
                gstr_app_dispatcher_flags.au8_nudge_data_retry_timer_fired[u8_i] = TWI_FALSE;
            }
        }
        else
        {
            if(gstr_app_dispatcher_flags.au8_nudge_data_retry_timer_fired[u8_i] == TWI_TRUE)
            {
                RHP_APP_LOG("Start Handling Nudge Failure Mechanism  %d !!\r\n",u8_i);
                if(gastr_nudging_data_parameters[u8_i].b_is_nudge_in_progress)
                {
                    gstr_app_dispatcher_flags.au8_nudge_data_retry_timer_fired[u8_i] = TWI_FALSE;
                    s32_retval = handle_nudge_data_device_failure(u8_i);
                    if(s32_retval != TWI_SUCCESS)
                    {
                        RHP_APP_LOG_ERR("Failed to Nudge, Need to retry, Err = %d\r\n",s32_retval);
                        /*Start the fast nudging timer*/
                        s32_retval = stop_timer(&gastr_nudge_data_retry_timer[u8_i]);
                        s32_retval = start_timer(&gastr_nudge_data_retry_timer[u8_i], (twi_s8*) "Fast Nudge Retry Timer", TWI_TIMER_TYPE_ONE_SHOT, (twi_u32) FAST_NUDGE_RETRY_TIME_MS, nudge_data_retry_timer_callback, &(gastr_nudging_data_parameters[u8_i].u8_op_code));
                        if(s32_retval != TWI_SUCCESS)
                        {
                            RHP_APP_LOG_ERR("Failed to start the Fast Nudge Retry Timer With Err = %d\r\n", s32_retval);
                        }
                    }
                }
            }
        }    
    }  

	/**************************************************** logger report success handling ****************************************************/
    twi_u8 u8_j = 0;
    for ( u8_j = 0; u8_j < INVALID_ALIGN_LOGGER_INDEX; u8_j++)
    {
        if((gstr_app_dispatcher_flags.au8_nudge_logs_succeeded[u8_j]) == TWI_TRUE)
        {
            RHP_APP_LOG("Success Nudge logger with index %d \n",u8_j);
            // Clear the gastr_nudging_logs_parameters[u8_j] elements to allow new nudging takes place
            gastr_nudging_logs_parameters[u8_j].b_is_nudge_in_progress = TWI_FALSE;
            gastr_nudging_logs_parameters[u8_j].u8_tp_logger_index = 0xFF;
            gastr_nudging_logs_parameters[u8_j].u8_tp_notify_destenation = 0xFF;
            gstr_app_dispatcher_flags.au8_nudge_logs_succeeded[u8_j] = TWI_FALSE;
            if (gstr_app_dispatcher_flags.au8_nudge_logs_retry_timer_fired[u8_j] == TWI_TRUE)
            {
                RHP_APP_LOG_ERR("***************** Racing Condition Detected ***************** \r\n");
                gstr_app_dispatcher_flags.au8_nudge_logs_retry_timer_fired[u8_j] = TWI_FALSE;
            }
        }
        else
        {
            if(gstr_app_dispatcher_flags.au8_nudge_logs_retry_timer_fired[u8_j] == TWI_TRUE)
            {
                RHP_APP_LOG("Start Handling Nudge Failure Mechanism  %d !!\r\n",u8_j);
                if(gastr_nudging_logs_parameters[u8_j].b_is_nudge_in_progress)
                {
                    gstr_app_dispatcher_flags.au8_nudge_logs_retry_timer_fired[u8_j] = TWI_FALSE;
                    s32_retval = handle_nudge_logs_device_failure(u8_j);
                    if(s32_retval != TWI_SUCCESS)
                    {
                        RHP_APP_LOG_ERR("Failed to Nudge, Need to retry, Err = %d\r\n",s32_retval);
                        /*Start the fast nudging timer*/
                        s32_retval = stop_timer(&gastr_nudge_logs_retry_timer[u8_j]);
                        s32_retval = start_timer(&gastr_nudge_logs_retry_timer[u8_j], (twi_s8*) "Fast Nudge Retry Timer", TWI_TIMER_TYPE_ONE_SHOT, (twi_u32) FAST_NUDGE_RETRY_TIME_MS, nudge_logs_retry_timer_callback, &(gastr_nudging_logs_parameters[u8_j].u8_tp_logger_index));
                        if(s32_retval != TWI_SUCCESS)
                        {
                            RHP_APP_LOG_ERR("Failed to start the Fast Nudge Retry Timer With Err = %d\r\n", s32_retval);
                        }
                    }
                }
            }
        }    
    } 
	
	/**************************************************** Packet formation ****************************************************/
	if (gstr_app_dispatcher_flags.gu8_sensor_data_is_ready == SENSORS_ARE_READY)
	{
		gstr_app_dispatcher_flags.gu8_sensor_data_is_ready = SENSORS_ARE_NOT_READY;

		TWI_ASSERT(TWI_SUCCESS == packet_formation());

        if (gb_running_mode)
        {
			/* Check if the session started or not */
			if (GET_LOGGER_0_SESSSION_STATUS == LOGGER_STARTED)
			{
				s32_retval = twi_rhp_event_logger_log(ALIGN_LOGGER_INDEX_ZERO);
				if (s32_retval != TWI_SUCCESS)
				{ 
					RHP_APP_LOG_ERR("Failed to take the event logs with Err = %d \r\n", s32_retval);
				}
				else
				{
#ifdef TEST_GPIOS_SNIFFING
					START_TAKE_LOGS_CH3;
#endif	
				}

				gu8_unreaded_packets ++;

				if ((gu8_unreaded_packets >= NUMBER_OF_PACKETS_TO_REPORT) && IS_DEVICE_CONNECTED &&
					(gastr_nudging_logs_parameters[ALIGN_LOGGER_INDEX_ZERO].b_is_nudge_in_progress == TWI_FALSE))
				{
					gu8_unreaded_packets = 0;
					gstr_app_dispatcher_flags.gb_logger_index_zero_report = TWI_TRUE;
				}
			}
			if (GET_LOGGER_1_SESSSION_STATUS == LOGGER_STARTED)
			{
				/* Disable Logger 1*/
				/* TWI_ASSERT(TWI_SUCCESS == twi_rhp_event_logger_log(ALIGN_LOGGER_INDEX_ONE)); */
				/* gstr_app_dispatcher_flags.gb_logger_index_one_report = TWI_TRUE; */
			}
		}
	}

    twi_aml_dispatch();   

#ifdef TEST_GPIOS_SNIFFING
	DISPATCH_END_CH4;
#endif
}

