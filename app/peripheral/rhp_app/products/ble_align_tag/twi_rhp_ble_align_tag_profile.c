/****************************************************************************/
/* Copyright (c) 2022 Thirdwayv, Inc. All Rights Reserved. */
/****************************************************************************/
/**
 *	@file       twi_rhp_ble_align_tag_profile.c
 *	@brief      Generated Code for RHP Layer Structures.
 */

#include "twi_rhp_types.h"
#include "twi_ble_hal_conf.h"
#include "twi_rhp_ble_align_tag.h"
#include "platform_pins.h"

#define FEATURE_0_ATTR_COUNT TWI_ARRAY_LEN(gapstr_feat_0_attributes)
#define FEATURE_1_ATTR_COUNT TWI_ARRAY_LEN(gapstr_feat_1_attributes)
#define FEATURE_2_ATTR_COUNT TWI_ARRAY_LEN(gapstr_feat_2_attributes)
#define FEATURE_3_ATTR_COUNT TWI_ARRAY_LEN(gapstr_feat_3_attributes)
#define FEATURE_4_ATTR_COUNT TWI_ARRAY_LEN(gapstr_feat_4_attributes)
#define NUM_LOGGERS				2
#define TOTAL_NUM_LOGGER_ATTR 	(NUM_LOGGERS * (twi_u8)LOGGER_INVALID_ATTR_INDEX)

#define TOTAL_NUM_HW_ATTR	(FEATURE_0_ATTR_COUNT + FEATURE_1_ATTR_COUNT+ FEATURE_2_ATTR_COUNT+ FEATURE_3_ATTR_COUNT + FEATURE_4_ATTR_COUNT)


#define FW_VERSION_ATTR			(1)
#define NUM_FEATURES TWI_ARRAY_LEN(gapstr_features)
#define	NUM_OF_TRIGS_TO_SAVE		1
#define	NUM_DEST1_LOGGERS			(0)		
#define TRIGS_BUFF_SIZE				NUM_OF_TRIGS_TO_SAVE * sizeof(tstr_rhp_trig_settings)


#define TOTAL_NUM_ATTR		(														\
								TOTAL_NUM_HW_ATTR	+ TOTAL_NUM_LOGGER_ATTR +		\
								FW_VERSION_ATTR										\
							)
#define ATT_0_1_VAL_SIZE			(sizeof(twi_u8))
#define ATT_0_2_VAL_SIZE			(sizeof(twi_u8))

#define	ATTRS_BUFF_SIZE				(ATT_0_1_VAL_SIZE + ATT_0_2_VAL_SIZE	)
#define	LOGGER_0_ATTR_TO_LOG_COUNT	1
#define	LOGGER_1_ATTR_TO_LOG_COUNT	1

#define NRF52_PAGE_SIZE		(4096)
/* We have 35 free Flash pages */
/* 8 pages for Save settings with tlv or 2 pages for normal save settings */
#define ALIGN_LOGGER_0_PAGES		(26)
#define ALIGN_LOGGER_1_PAGES		(1)

/*-**********************************************************/
/*						Trigger	0							*/
/*-**********************************************************/
#define TRIG_0_0_PTR NULL
#define TRIG_0_0_COUNT 0
#define TRIG_0_1_PTR NULL
#define TRIG_0_1_COUNT 0
/*-**********************************************************/
/*						Trigger	1							*/
/*-**********************************************************/
#define TRIG_1_0_PTR NULL
#define TRIG_1_0_COUNT 0
#define TRIG_1_1_PTR NULL
#define TRIG_1_1_COUNT 0

/*-***********************************************************/

#define TRIGGER_POINTER_ARRAY_0_0 NULL
#define TRIGGER_POINTER_ARRAY_0_0_COUNT 0
#define TRIGGER_POINTER_ARRAY_1_0 NULL
#define TRIGGER_POINTER_ARRAY_1_0_COUNT 0
#define TRIGGER_POINTER_ARRAY_CLOUD_DEST_NEED_TO_PUSH_SEND_COUNT	0
#define TRIGGER_POINTER_ARRAY_DEST1_NEED_TO_PUSH_SEND_COUNT	0


#define INDICATE_HW_COUNT 		TWI_ARRAY_LEN(gapstr_indct_hw_attrs)

#define	NUM_OF_ATTRS_TO_SAVE		TWI_ARRAY_LEN(gapstr_save_attrs)

/*-**********************************************************/
/*						LOGGER	0							*/
/*-**********************************************************/
#define NUM_OF_LOGGERS_TO_SAVE		(2)
#define NUM_CLOUD_DEST_LOGGERS		(NUM_LOGGERS)
/*-**********************************************************/
/* Must write pu8_twi_sas_sender_id value in one line as this line parsed with the generator APP and modify it */
twi_u8 pu8_twi_sas_sender_id[4] = {0xFF, 0xFF, 0xFF, 0xFE};
const tstr_twi_rhp_trigger* const* const geappstr_triggers_for_need_to_push_send[OUTPUT_DESTS_NUM] = {TRIGGER_POINTER_ARRAY_DEST1_NEED_TO_PUSH_SEND_COUNT};
const twi_u8 geau8_num_triggers_need_to_push_send[OUTPUT_DESTS_NUM] = {	TRIGGER_POINTER_ARRAY_CLOUD_DEST_NEED_TO_PUSH_SEND_COUNT};

/*********************************************************************************************************/
/************************************************FEATURE 0 (BLE)******************************************/
/*********************************************************************************************************/

/* BLE Parameters */

/* BLE START/STOP Advertising Control */


tstr_twi_rhp_value gstr_attr_node_0_0_value =
{
	.enu_type = U8,
	.uni_value.u8_int = (twi_u8) BLE_ADVERTISE_START,				/* It's initially Stopped ADVERTISING. */
};
const tstr_twi_hardware gstr_attr_node_0_0_hardware =
{
	.enu_type = PERIPHERAL,
	.enu_subtype = BLE_START_STOP_ADV,
	.pstr_gpio_pins = NULL,
};
const tstr_twi_rhp_attr gstr_attr_node_0_0 = {
	.attr_index = ATTRIBUTE_ZERO_IDX,
	.parent_index = FEATURE_ZERO_IDX,
	.enu_attr_type = FEATURE_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_attr_node_0_0_value,
	.pstr_hardware = &gstr_attr_node_0_0_hardware,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_0_0,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_0_0_COUNT,
};

/*------------------------------------------------------------*/
/*- Feature 0 , Attribute 1 (BLE Advertising Data) -----------*/ 
/*------------------------------------------------------------*/
tstr_twi_rhp_value gstr_attr_node_0_1_value = 
{
	.enu_type	= HEX,
	.uni_value.str_hex_array= {
                                 .pu8_data = NULL,
                                 .u16_len  = 0,
                              },    
};

const tstr_twi_hardware gstr_attr_node_0_1_hardware = {
	.enu_type = PERIPHERAL,
	.enu_subtype = BLE_PERIPHERAL_ADV_DATA,
	.pstr_gpio_pins = NULL,
};

const tstr_twi_rhp_attr gstr_attr_node_0_1 = {
	.attr_index = ATTRIBUTE_ONE_IDX,
	.parent_index = FEATURE_ZERO_IDX,
	.enu_attr_type = FEATURE_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_attr_node_0_1_value,
	.pstr_hardware = &gstr_attr_node_0_1_hardware,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,
};

/*------------------------------------------------------------*/
/*- Feature 0 , Attribute 2 (BLE Always Connected) -----------*/ 
/*------------------------------------------------------------*/
tstr_twi_rhp_value gstr_attr_node_0_2_value = {
	.enu_type = BOOLEAN,
	.uni_value.b_boolean = TWI_TRUE,
};
const tstr_twi_hardware gstr_attr_node_0_2_hardware = {
	.enu_type = PERIPHERAL,
	.enu_subtype = (tenu_subtype)BLE_ALWAYS_CONNECTED_MODE,
	.pstr_gpio_pins = NULL,
};
const tstr_twi_rhp_attr gstr_attr_node_0_2 = {
	.attr_index = ATTRIBUTE_TWO_IDX,
	.parent_index = FEATURE_ZERO_IDX,
	.enu_attr_type = FEATURE_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_attr_node_0_2_value,
	.pstr_hardware = &gstr_attr_node_0_2_hardware,
	.enu_permission = READ_AND_WRITE_INTERNALLY,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,
};

/*------------------------------------------------------------*/
/*- Feature 0 , Attribute 3 (BLE Connection Status) ----------*/ 
/*------------------------------------------------------------*/
tstr_twi_rhp_value gstr_attr_node_0_3_value =
{
	.enu_type = U8,
	.uni_value.u8_int = BLE_CONN_PERIPHERAL_DISCONNECTED,				/* It's initially Disconnected */
};

const tstr_twi_hardware gstr_attr_node_0_3_hardware =
{
	.enu_type = PERIPHERAL,
	.enu_subtype = BLE_PERIPHERAL_CONNECT_STATUS,
	.pstr_gpio_pins = NULL,
};

const tstr_twi_rhp_attr gstr_attr_node_0_3 =
{
	.attr_index = ATTRIBUTE_THREE_IDX,
	.parent_index = FEATURE_ZERO_IDX,
	.enu_attr_type = FEATURE_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_attr_node_0_3_value,
	.pstr_hardware = &gstr_attr_node_0_3_hardware,
	.enu_permission = READ_ONLY,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,
};

const tstr_twi_rhp_attr* const gapstr_feat_0_attributes[] = {
	&gstr_attr_node_0_0,
	&gstr_attr_node_0_1,
	&gstr_attr_node_0_2,
	&gstr_attr_node_0_3,
};
const tstr_twi_rhp_feature gstr_feature_node_0 = {
	.feature_index = FEATURE_ZERO_IDX,
	.u8_num_attributes = FEATURE_0_ATTR_COUNT,
	.ppstr_attributes = gapstr_feat_0_attributes,
};


/*********************************************************************************************************/
/************************************************FEATURE 1************************************************/
/*********************************************************************************************************/
tstr_twi_rhp_value gstr_attr_node_1_0_value = {
		.enu_type = U16,
#ifdef USE_BATT_SENSOR
		.uni_value.u16_int = 0
#else
		.uni_value.u16_int = DISCHARGING_STATUS_FULL_BATTERY
#endif
};
#ifdef USE_BATT_SENSOR
const tstr_twi_hardware gstr_attr_node_1_0_hardware = {
		.enu_type = SENSOR,
		.enu_subtype = BAT_SENSOR,
		.pstr_gpio_pins = NULL
};
#endif
const tstr_twi_rhp_attr gstr_attr_node_1_0 = {
	.attr_index = ATTRIBUTE_ZERO_IDX,
	.parent_index = FEATURE_ONE_IDX,
    .enu_attr_type = FEATURE_ATTR,
    .b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_attr_node_1_0_value,
#ifdef USE_BATT_SENSOR
	.pstr_hardware = &gstr_attr_node_1_0_hardware,
#else
	.pstr_hardware = NULL,
#endif
	.enu_permission = READ_ONLY,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,

};

tstr_twi_rhp_value gstr_attr_node_1_1_value = {
	.enu_type = S16,
	.uni_value.s16_int = 0,
};
#ifdef USE_TEMP_SENSOR
const tstr_twi_hardware gstr_attr_node_1_1_hardware = {
		.enu_type = SENSOR,
		.enu_subtype = TEMP_SENSOR,
		.pstr_gpio_pins = NULL
};
#endif
const tstr_twi_rhp_attr gstr_attr_node_1_1 = {
	.attr_index = ATTRIBUTE_ONE_IDX,
	.parent_index = FEATURE_ONE_IDX,
    .enu_attr_type = FEATURE_ATTR,
    .b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_attr_node_1_1_value,
#ifdef USE_TEMP_SENSOR
	.pstr_hardware = &gstr_attr_node_1_1_hardware,
#else
	.pstr_hardware = NULL,

#endif
	.enu_permission = READ_ONLY,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,
};

tstr_twi_rhp_value gstr_attr_node_1_2_value = {
	.enu_type = U32,
	.uni_value.u32_int = 0,
};
#ifdef USE_PRESSURE_SENSOR
const tstr_twi_hardware gstr_attr_node_1_2_hardware = {
		.enu_type = SENSOR,
		.enu_subtype = PRESSURE_SENSOR,
		.pstr_gpio_pins = NULL
};
#endif
const tstr_twi_rhp_attr gstr_attr_node_1_2 = {
	.attr_index = ATTRIBUTE_TWO_IDX,
	.parent_index = FEATURE_ONE_IDX,
    .enu_attr_type = FEATURE_ATTR,
    .b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_attr_node_1_2_value,
#ifdef USE_PRESSURE_SENSOR
	.pstr_hardware = &gstr_attr_node_1_2_hardware,
#else 
	.pstr_hardware = NULL,
#endif
	.enu_permission = READ_ONLY,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,

};

tstr_twi_rhp_value gstr_attr_node_1_3_value = {
	.enu_type = S16,
	.uni_value.s16_int = 0,
};
#ifdef USE_FORCE_SENSOR
const tstr_twi_hardware gstr_attr_node_1_3_hardware = {
		.enu_type = SENSOR,
		.enu_subtype = FORCE_SENSOR,
		.pstr_gpio_pins = NULL
};
#endif
const tstr_twi_rhp_attr gstr_attr_node_1_3 = {
	.attr_index = ATTRIBUTE_THREE_IDX,
	.parent_index = FEATURE_ONE_IDX,
    .enu_attr_type = FEATURE_ATTR,
    .b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_attr_node_1_3_value,
#ifdef USE_FORCE_SENSOR
	.pstr_hardware = &gstr_attr_node_1_3_hardware,
#else
	.pstr_hardware = NULL,
#endif
	.enu_permission = READ_ONLY,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,

};

tstr_twi_rhp_value gstr_attr_node_1_4_value = {
	.enu_type = U8,
	.uni_value.u8_int = 0,
};
#ifdef USE_PH_SENSOR
const tstr_twi_hardware gstr_attr_node_1_4_hardware = {
		.enu_type = SENSOR,
		.enu_subtype = PH_SENSOR,
		.pstr_gpio_pins = NULL
};
#endif
const tstr_twi_rhp_attr gstr_attr_node_1_4 = {
	.attr_index = ATTRIBUTE_FOUR_IDX,
	.parent_index = FEATURE_ONE_IDX,
    .enu_attr_type = FEATURE_ATTR,
    .b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_attr_node_1_4_value,
#ifdef USE_PH_SENSOR
	.pstr_hardware = &gstr_attr_node_1_4_hardware,
#else
	.pstr_hardware = NULL,
#endif
	.enu_permission = READ_ONLY,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,

};

const tstr_twi_rhp_attr* const gapstr_feat_1_attributes[] = {
	&gstr_attr_node_1_0, /*Battery*/
	&gstr_attr_node_1_1, /*Temp Sensor*/
	&gstr_attr_node_1_2, /*Pressure Sensor*/
	&gstr_attr_node_1_3, /*Force Sensor*/
	&gstr_attr_node_1_4, /*pH Sensor*/
};
const tstr_twi_rhp_feature gstr_feature_node_1 = {
	.feature_index = FEATURE_ONE_IDX,
	.u8_num_attributes = FEATURE_1_ATTR_COUNT,
	.ppstr_attributes = gapstr_feat_1_attributes,
};
/*********************************************************************************************************/
/************************************************ FEATURE 1 **********************************************/
/************************************************ ACC Sensor *********************************************/
/*********************************************************************************************************/
/*------------------------------------------------------------*/
/*- Feature 2 , Attribute 0 (Accelereometer X-axis Reading) --*/ 
/*------------------------------------------------------------*/

tstr_twi_rhp_value gstr_attr_node_2_0_value = {
	.enu_type = S16,
	.uni_value.s16_int = 0,
};

#if defined(TWI_ENABLE_ACC_HW_SETUP)
const tstr_twi_hardware gstr_attr_node_2_0_hardware = {
	.enu_type = SENSOR,
	.enu_subtype = ACC_SENSOR_X_ACC,
	.pstr_gpio_pins = NULL,
};
#endif

const tstr_twi_rhp_attr gstr_attr_node_2_0= {						
	.attr_index						= ATTRIBUTE_ZERO_IDX,
	.parent_index					= FEATURE_TWO_IDX,
	.enu_attr_type					= FEATURE_ATTR,
	.b_has_active_loggers 			= TWI_FALSE,
	.pstr_value 					= &gstr_attr_node_2_0_value,   
#if defined(TWI_ENABLE_ACC_HW_SETUP)
	.pstr_hardware					= &gstr_attr_node_2_0_hardware,
#else
	.pstr_hardware =  NULL,
#endif
	.enu_permission					= READ_ONLY,
	.ppstr_triggers 				= NULL,
	.u8_num_triggers_on_attribute 	= 0,
};

/*------------------------------------------------------------*/
/*- Feature 2 , Attribute 1 (Accelereometer Y-axis Reading) --*/ 
/*------------------------------------------------------------*/

tstr_twi_rhp_value gstr_attr_node_2_1_value = {
	.enu_type = S16,
	.uni_value.s16_int = 0,
};

#if defined(TWI_ENABLE_ACC_HW_SETUP)
const tstr_twi_hardware gstr_attr_node_2_1_hardware = {
	.enu_type = SENSOR,
	.enu_subtype = ACC_SENSOR_Y_ACC,
	.pstr_gpio_pins = NULL,
};
#endif

const tstr_twi_rhp_attr gstr_attr_node_2_1= {						
	.attr_index						= ATTRIBUTE_ONE_IDX,
	.parent_index					= FEATURE_TWO_IDX,
	.enu_attr_type					= FEATURE_ATTR,
	.b_has_active_loggers 			= TWI_FALSE,
	.pstr_value 					= &gstr_attr_node_2_1_value, 
#if defined(TWI_ENABLE_ACC_HW_SETUP)  
	.pstr_hardware					= &gstr_attr_node_2_1_hardware,
#else
	.pstr_hardware =  NULL,
#endif
	.enu_permission					= READ_ONLY,
	.ppstr_triggers 				= NULL,
	.u8_num_triggers_on_attribute 	= 0,
};

/*------------------------------------------------------------*/
/*- Feature 2 , Attribute 2 (Accelereometer Z-axis Reading) --*/ 
/*------------------------------------------------------------*/

tstr_twi_rhp_value gstr_attr_node_2_2_value = {
	.enu_type = S16,
	.uni_value.s16_int = 0,
};

#if defined(TWI_ENABLE_ACC_HW_SETUP)
const tstr_twi_hardware gstr_attr_node_2_2_hardware = {
	.enu_type = SENSOR,
	.enu_subtype = ACC_SENSOR_Z_ACC,
	.pstr_gpio_pins = NULL,
};
#endif

const tstr_twi_rhp_attr gstr_attr_node_2_2= {						
	.attr_index						= ATTRIBUTE_TWO_IDX,
	.parent_index					= FEATURE_TWO_IDX,
	.enu_attr_type					= FEATURE_ATTR,
	.b_has_active_loggers 			= TWI_FALSE,
	.pstr_value 					= &gstr_attr_node_2_2_value,   
#if defined(TWI_ENABLE_ACC_HW_SETUP)
	.pstr_hardware					= &gstr_attr_node_2_2_hardware,
#else
	.pstr_hardware =  NULL,
#endif
	.enu_permission					= READ_ONLY,
	.ppstr_triggers 				= NULL,
	.u8_num_triggers_on_attribute 	= 0,
};


const tstr_twi_rhp_attr* const gapstr_feat_2_attributes[] =
{
	&gstr_attr_node_2_0, /*X Axis*/
	&gstr_attr_node_2_1, /*Y Axis*/
    &gstr_attr_node_2_2, /*Z Axis*/
};

const tstr_twi_rhp_feature gstr_feature_node_2 = {
	.feature_index = FEATURE_TWO_IDX,
	.u8_num_attributes = FEATURE_2_ATTR_COUNT,
	.ppstr_attributes = gapstr_feat_2_attributes,
};

/*********************************************************************************************************/
/************************************************FEATURE 3************************************************/
/*********************************************************************************************************/
tstr_align_session_status gstr_align_session_status =
{
    .u8_reserved = RESERVED_FIVE_BITS,  
    .u8_operation_mode = ALIGN_TAG_INVALID_MODE,                    
    .u8_n0 = DISABLE_SENSOR_READINGS,               
    .u8_m0 = DISABLE_SENSOR_READINGS,            
    .u8_l0 = DISABLE_SENSOR_READINGS,   
    .u8_y0 = DISABLE_SENSOR_READINGS,           
    .u8_z0 = DISABLE_SENSOR_READINGS,            
    .u8_n1 = DISABLE_SENSOR_READINGS,   
    .u8_m1 = DISABLE_SENSOR_READINGS,     
    .u8_l1 = DISABLE_SENSOR_READINGS,            
    .u8_y1 = DISABLE_SENSOR_READINGS,   
    .u8_z1 = DISABLE_SENSOR_READINGS  
};

tstr_twi_rhp_value gstr_attr_node_3_0_value = {
	.enu_type = HEX,
	.uni_value.str_hex_array.u16_len = sizeof(tstr_align_session_status),
	.uni_value.str_hex_array.pu8_data = (twi_u8 *) &gstr_align_session_status
};

const tstr_twi_rhp_attr gstr_attr_node_3_0 = {
	.attr_index = ATTRIBUTE_ZERO_IDX,
	.parent_index = FEATURE_THREE_IDX,
    .enu_attr_type = FEATURE_ATTR,
    .b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_attr_node_3_0_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_INDICATE,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,
};

tstr_twi_rhp_value gstr_attr_node_3_1_value =
{
	.enu_type = U8,
	.uni_value.u8_int = (twi_u8) ALIGN_TAG_CONTINUS_MODE,
};

const tstr_twi_rhp_attr gstr_attr_node_3_1 =
{
	.attr_index = ATTRIBUTE_ONE_IDX,
	.parent_index = FEATURE_THREE_IDX,
	.enu_attr_type = FEATURE_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_attr_node_3_1_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,
};

const tstr_twi_rhp_attr* const gapstr_feat_3_attributes[] = {
	&gstr_attr_node_3_0, /*Session status*/
	&gstr_attr_node_3_1, /*Operation mode*/
};
const tstr_twi_rhp_feature gstr_feature_node_3 = {
	.feature_index = FEATURE_THREE_IDX,
	.u8_num_attributes = FEATURE_3_ATTR_COUNT,
	.ppstr_attributes = gapstr_feat_3_attributes,
};
/*********************************************************************************************************/
/************************************************FEATURE 4************************************************/
/*********************************************************************************************************/
static twi_u8 gau8_total_logged_data[TOTAL_DATA_SIZE_PER_LOGGING_INTERVAL] = {0};

tstr_twi_rhp_value gstr_attr_node_4_0_value = {
	.enu_type = HEX,
	.uni_value.str_hex_array.u16_len = TOTAL_DATA_SIZE_PER_LOGGING_INTERVAL,
	.uni_value.str_hex_array.pu8_data = gau8_total_logged_data
};

const tstr_twi_rhp_attr gstr_attr_node_4_0 = {
	.attr_index = ATTRIBUTE_ZERO_IDX,
	.parent_index = FEATURE_FOUR_IDX,
    .enu_attr_type = FEATURE_ATTR,
    .b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_attr_node_4_0_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,

};
const tstr_twi_rhp_attr* const gapstr_feat_4_attributes[] = {
	&gstr_attr_node_4_0, /*Attribute to be logged*/
};
const tstr_twi_rhp_feature gstr_feature_node_4 = {
	.feature_index = FEATURE_FOUR_IDX,
	.u8_num_attributes = FEATURE_4_ATTR_COUNT,
	.ppstr_attributes = gapstr_feat_4_attributes,
};

/*********************************************************************************************************/
const tstr_twi_rhp_feature* const gapstr_features[] = {
	&gstr_feature_node_0,
	&gstr_feature_node_1,
	&gstr_feature_node_2,
	&gstr_feature_node_3,
	&gstr_feature_node_4,
};
static const tstr_twi_rhp_attr * gapstr_indct_hw_attrs[] =
{
#ifdef USE_ACC_SENSOR
	&gstr_attr_node_2_0,
	&gstr_attr_node_2_1,
	&gstr_attr_node_2_2,
#endif
#ifdef USE_PRESSURE_SENSOR
	&gstr_attr_node_1_2,
#endif
#ifdef USE_FORCE_SENSOR
	&gstr_attr_node_1_3,
#endif
#ifdef USE_PH_SENSOR
	&gstr_attr_node_1_4,
#endif
};
static tstr_twi_rhp_indct_hw srt_twi_rhp_indct_hw = {
	.ppstr_indct_hw_attrs = gapstr_indct_hw_attrs,
	.u8_indct_hw_cnt = INDICATE_HW_COUNT,
};
/*-******************************************************/
/*			LOGGER 0									*/
/*-******************************************************/
#define TRIGGER_POINTER_ARRAY_LOG_0_0 NULL
#define TRIGGER_POINTER_ARRAY_LOG_0_0_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_0_1 NULL
#define TRIGGER_POINTER_ARRAY_LOG_0_1_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_0_2 NULL
#define TRIGGER_POINTER_ARRAY_LOG_0_2_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_0_3 NULL
#define TRIGGER_POINTER_ARRAY_LOG_0_3_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_0_4 NULL
#define TRIGGER_POINTER_ARRAY_LOG_0_4_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_0_5 NULL
#define TRIGGER_POINTER_ARRAY_LOG_0_5_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_0_6 NULL
#define TRIGGER_POINTER_ARRAY_LOG_0_6_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_0_7 NULL
#define TRIGGER_POINTER_ARRAY_LOG_0_7_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_0_8 NULL
#define TRIGGER_POINTER_ARRAY_LOG_0_8_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_0_9 NULL
#define TRIGGER_POINTER_ARRAY_LOG_0_9_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_0_10 NULL
#define TRIGGER_POINTER_ARRAY_LOG_0_10_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_0_11 NULL
#define TRIGGER_POINTER_ARRAY_LOG_0_11_COUNT 0
extern tstr_twi_rhp_value gstr_log_attr_node_0_0_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_0_0;
extern tstr_twi_rhp_value gstr_log_attr_node_0_1_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_0_1;
extern tstr_twi_rhp_value gstr_log_attr_node_0_2_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_0_2;
extern tstr_twi_rhp_value gstr_log_attr_node_0_3_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_0_3;
extern tstr_twi_rhp_value gstr_log_attr_node_0_4_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_0_4;
extern tstr_twi_rhp_value gstr_log_attr_node_0_5_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_0_5;
extern tstr_twi_rhp_value gstr_log_attr_node_0_6_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_0_6;
extern tstr_twi_rhp_value gstr_log_attr_node_0_7_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_0_7;
extern tstr_twi_rhp_value gstr_log_attr_node_0_8_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_0_8;
extern tstr_twi_rhp_value gstr_log_attr_node_0_9_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_0_9;
extern tstr_twi_rhp_value gstr_log_attr_node_0_10_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_0_10;
extern tstr_twi_rhp_value gstr_log_attr_node_0_11_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_0_11;
tstr_twi_rhp_logger  gstr_logger_0;


tstr_twi_rhp_value gstr_log_attr_node_0_0_value = {
	.enu_type = U32,
	.uni_value.u32_int = RHP_INVALID_TIMESTAMP,
};

const tstr_twi_rhp_attr gstr_log_attr_node_0_0 = {
	.attr_index = LOGGER_LAST_REPORT_TIMESTAMP,
	.parent_index = 0,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_0_0_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_ONLY,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_0_0,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_0_0_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_0_1_value = {
	.enu_type = U8,
	.uni_value.u8_int = (twi_u8)EVENT_BASED_LOGGER,
};

const tstr_twi_rhp_attr gstr_log_attr_node_0_1 = {
	.attr_index = (twi_u8)LOGGER_TYPE,
	.parent_index = 0,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_0_1_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_0_1,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_0_1_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_0_2_value = {
	.enu_type = U32,
	.uni_value.u32_int = TWI_ALIGN_TAG_LOGGER_INTERVAL_S,
};

const tstr_twi_rhp_attr gstr_log_attr_node_0_2 = {
	.attr_index = (twi_u8)LOGGER_INTERVAL,
	.parent_index = 0,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_0_2_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,
};

tstr_twi_rhp_value gstr_log_attr_node_0_3_value = {
	.enu_type = U32,
	.uni_value.u32_int = TWI_ALIGN_TAG_REPORT_INTERVAL_S,
};

const tstr_twi_rhp_attr gstr_log_attr_node_0_3 = {
	.attr_index = (twi_u8)LOGGER_REPORT_INTERVAL,
	.parent_index = 0,
    .enu_attr_type = LOGGER_ATTR,
    .b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_0_3_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_0_3,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_0_3_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_0_4_value = {
	.enu_type = U8,
	.uni_value.u8_int = (twi_u8)LOGGER_STOPPED_EXTERNALLY,
};

const tstr_twi_rhp_attr gstr_log_attr_node_0_4 = {
	.attr_index = (twi_u8)LOGGER_STATUS,
	.parent_index = 0,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_0_4_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE_AND_INDICATE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_0_4,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_0_4_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_0_5_value = {
	.enu_type = U32,
	.uni_value.u32_int = 0,
};

const tstr_twi_rhp_attr gstr_log_attr_node_0_5 = {
	.attr_index = (twi_u8)LOGGER_NUM_UNREAD_LOGS,
	.parent_index = 0,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_0_5_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_INDICATE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_0_5,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_0_5_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_0_6_value = {
	.enu_type = U32,
	.uni_value.u32_int = 0,
};

const tstr_twi_rhp_attr gstr_log_attr_node_0_6 = {
	.attr_index = (twi_u8)LOGGER_READ_IDX,
	.parent_index = 0,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_0_6_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_0_6,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_0_6_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_0_7_value = {
	.enu_type = U32,
	.uni_value.u32_int = 0,
};

const tstr_twi_rhp_attr gstr_log_attr_node_0_7 = {
	.attr_index = (twi_u8)LOGGER_MAX_NUM_LOGS,
	.parent_index = 0,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_0_7_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_ONLY,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_0_7,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_0_7_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_0_8_value = {
	.enu_type = U32,
	.uni_value.u32_int = 0,
};

const tstr_twi_rhp_attr gstr_log_attr_node_0_8 = {
	.attr_index = (twi_u8)LOGGER_TIME_FROM_START,
	.parent_index = 0,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_0_8_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_INDICATE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_0_8,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_0_8_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_0_9_value = {
	.enu_type = HEX,
	.uni_value.str_hex_array.u16_len = 0,
	.uni_value.str_hex_array.pu8_data = NULL
};

const tstr_twi_rhp_attr gstr_log_attr_node_0_9 = {
	.attr_index = (twi_u8)LOGGER_LOGS,
	.parent_index = 0,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_0_9_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_ONLY,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_0_9,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_0_9_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_0_10_value = {
	.enu_type = U8,
	.uni_value.u8_int = (twi_u8)DEFAULT_LOG_FORMAT_1_RAW_DATA,
};

const tstr_twi_rhp_attr gstr_log_attr_node_0_10 = {
	.attr_index = (twi_u8)LOGGER_LOG_FORMAT,
	.parent_index = 0,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_0_10_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_0_10,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_0_10_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_0_11_value = {
	.enu_type = U32,
	.uni_value.u32_int = 0xFFFFFFFF,
};

const tstr_twi_rhp_attr gstr_log_attr_node_0_11 = {
	.attr_index = (twi_u8)LOGGER_TIME_TO_START,
	.parent_index = 0,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_0_11_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_0_11,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_0_11_COUNT,
};

const tstr_twi_rhp_attr* const gapstr_logger_0_attr_to_log[] = {
	&gstr_attr_node_4_0,	/*Attribute to be logged*/
};

tstr_twi_rhp_value gastr_logger_0_last_wrt_value[LOGGER_0_ATTR_TO_LOG_COUNT];

const twi_u8 gaau8_log_0_dest_recv_twi_id[1][4] = {
	TWI_ALIGN_TAG_SERVER_ID,
};

#ifdef SAVE_SYSTEM_SETTINGS
static twi_u8 TWI_ALIGN gau8_logger_0_setting_buf[sizeof(tstr_rhp_logger_settings)];
#endif

tstr_twi_rhp_logger gstr_logger_0 = {
    .apstr_logger_attributes = {
        &gstr_log_attr_node_0_0,
        &gstr_log_attr_node_0_1,
        &gstr_log_attr_node_0_2,
        &gstr_log_attr_node_0_3,
        &gstr_log_attr_node_0_4,
        &gstr_log_attr_node_0_5,
        &gstr_log_attr_node_0_6,
        &gstr_log_attr_node_0_7,
        &gstr_log_attr_node_0_8,
        &gstr_log_attr_node_0_9,
        &gstr_log_attr_node_0_10,
        &gstr_log_attr_node_0_11,
        NULL
        },
#ifdef SAVE_SYSTEM_SETTINGS
    .pu8_setting_buf = gau8_logger_0_setting_buf,
#endif

	.u8_logger_index = 0,
	.u8_output_destinations = OUTPUT_CLOUD_DEST,
	.pau8_dest_recv_twi_id = gaau8_log_0_dest_recv_twi_id,
	.enu_circular_overwrite = LOGGER_CARELESS_OVERWRITE_MODE,
	.u32_total_num_logs = 0,
	.u8_num_attr_to_log = LOGGER_0_ATTR_TO_LOG_COUNT,
	.ppstr_attribute_to_log = gapstr_logger_0_attr_to_log,
	.pstr_last_write_value = gastr_logger_0_last_wrt_value,
	.u8_logger_status_flags = 0,
	.u16_log_size = TWI_ALIGN_TAG_LOG_SIZE,
	.b_need_to_push = TWI_FALSE,
    .b_no_push_logs = TWI_TRUE,
	.u32_max_memory_size = NRF52_PAGE_SIZE * ALIGN_LOGGER_0_PAGES,
	.b_log_on_start = TWI_FALSE
};

/*-******************************************************/
/*			LOGGER 1									*/
/*-******************************************************/
#define TRIGGER_POINTER_ARRAY_LOG_1_0 NULL
#define TRIGGER_POINTER_ARRAY_LOG_1_0_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_1_1 NULL
#define TRIGGER_POINTER_ARRAY_LOG_1_1_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_1_2 NULL
#define TRIGGER_POINTER_ARRAY_LOG_1_2_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_1_3 NULL
#define TRIGGER_POINTER_ARRAY_LOG_1_3_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_1_4 NULL
#define TRIGGER_POINTER_ARRAY_LOG_1_4_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_1_5 NULL
#define TRIGGER_POINTER_ARRAY_LOG_1_5_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_1_6 NULL
#define TRIGGER_POINTER_ARRAY_LOG_1_6_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_1_7 NULL
#define TRIGGER_POINTER_ARRAY_LOG_1_7_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_1_8 NULL
#define TRIGGER_POINTER_ARRAY_LOG_1_8_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_1_9 NULL
#define TRIGGER_POINTER_ARRAY_LOG_1_9_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_1_10 NULL
#define TRIGGER_POINTER_ARRAY_LOG_1_10_COUNT 0
#define TRIGGER_POINTER_ARRAY_LOG_1_11 NULL
#define TRIGGER_POINTER_ARRAY_LOG_1_11_COUNT 0
extern tstr_twi_rhp_value gstr_log_attr_node_1_0_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_1_0;
extern tstr_twi_rhp_value gstr_log_attr_node_1_1_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_1_1;
extern tstr_twi_rhp_value gstr_log_attr_node_1_2_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_1_2;
extern tstr_twi_rhp_value gstr_log_attr_node_1_3_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_1_3;
extern tstr_twi_rhp_value gstr_log_attr_node_1_4_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_1_4;
extern tstr_twi_rhp_value gstr_log_attr_node_1_5_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_1_5;
extern tstr_twi_rhp_value gstr_log_attr_node_1_6_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_1_6;
extern tstr_twi_rhp_value gstr_log_attr_node_1_7_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_1_7;
extern tstr_twi_rhp_value gstr_log_attr_node_1_8_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_1_8;
extern tstr_twi_rhp_value gstr_log_attr_node_1_9_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_1_9;
extern tstr_twi_rhp_value gstr_log_attr_node_1_10_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_1_10;
extern tstr_twi_rhp_value gstr_log_attr_node_1_11_value;
extern const tstr_twi_rhp_attr gstr_log_attr_node_1_11;
tstr_twi_rhp_logger  gstr_logger_1;


tstr_twi_rhp_value gstr_log_attr_node_1_0_value = {
	.enu_type = U32,
	.uni_value.u32_int = RHP_INVALID_TIMESTAMP,
};

const tstr_twi_rhp_attr gstr_log_attr_node_1_0 = {
	.attr_index = LOGGER_LAST_REPORT_TIMESTAMP,
	.parent_index = 1,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_1_0_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_ONLY,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_1_0,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_1_0_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_1_1_value = {
	.enu_type = U8,
	.uni_value.u8_int = (twi_u8)EVENT_BASED_LOGGER,
};

const tstr_twi_rhp_attr gstr_log_attr_node_1_1 = {
	.attr_index = (twi_u8)LOGGER_TYPE,
	.parent_index = 1,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_1_1_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_1_1,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_1_1_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_1_2_value = {
	.enu_type = U32,
	.uni_value.u32_int = TWI_ALIGN_TAG_LOGGER_INTERVAL_S,
};

const tstr_twi_rhp_attr gstr_log_attr_node_1_2 = {
	.attr_index = (twi_u8)LOGGER_INTERVAL,
	.parent_index = 1,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_1_2_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = NULL,
	.u8_num_triggers_on_attribute = 0,
};

tstr_twi_rhp_value gstr_log_attr_node_1_3_value = {
	.enu_type = U32,
	.uni_value.u32_int = TWI_ALIGN_TAG_REPORT_INTERVAL_S,
};

const tstr_twi_rhp_attr gstr_log_attr_node_1_3 = {
	.attr_index = (twi_u8)LOGGER_REPORT_INTERVAL,
	.parent_index = 1,
    .enu_attr_type = LOGGER_ATTR,
    .b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_1_3_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_1_3,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_1_3_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_1_4_value = {
	.enu_type = U8,
	.uni_value.u8_int = (twi_u8)LOGGER_STOPPED_EXTERNALLY,
};

const tstr_twi_rhp_attr gstr_log_attr_node_1_4 = {
	.attr_index = (twi_u8)LOGGER_STATUS,
	.parent_index = 1,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_1_4_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE_AND_INDICATE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_1_4,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_1_4_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_1_5_value = {
	.enu_type = U32,
	.uni_value.u32_int = 0,
};

const tstr_twi_rhp_attr gstr_log_attr_node_1_5 = {
	.attr_index = (twi_u8)LOGGER_NUM_UNREAD_LOGS,
	.parent_index = 1,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_1_5_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_INDICATE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_1_5,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_1_5_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_1_6_value = {
	.enu_type = U32,
	.uni_value.u32_int = 0,
};

const tstr_twi_rhp_attr gstr_log_attr_node_1_6 = {
	.attr_index = (twi_u8)LOGGER_READ_IDX,
	.parent_index = 1,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_1_6_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_1_6,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_1_6_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_1_7_value = {
	.enu_type = U32,
	.uni_value.u32_int = 0,
};

const tstr_twi_rhp_attr gstr_log_attr_node_1_7 = {
	.attr_index = (twi_u8)LOGGER_MAX_NUM_LOGS,
	.parent_index = 1,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_1_7_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_ONLY,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_1_7,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_1_7_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_1_8_value = {
	.enu_type = U32,
	.uni_value.u32_int = 0,
};

const tstr_twi_rhp_attr gstr_log_attr_node_1_8 = {
	.attr_index = (twi_u8)LOGGER_TIME_FROM_START,
	.parent_index = 1,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_1_8_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_INDICATE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_1_8,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_1_8_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_1_9_value = {
	.enu_type = HEX,
	.uni_value.str_hex_array.u16_len = 0,
	.uni_value.str_hex_array.pu8_data = NULL
};

const tstr_twi_rhp_attr gstr_log_attr_node_1_9 = {
	.attr_index = (twi_u8)LOGGER_LOGS,
	.parent_index = 1,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_1_9_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_ONLY,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_1_9,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_1_9_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_1_10_value = {
	.enu_type = U8,
	.uni_value.u8_int = (twi_u8)DEFAULT_LOG_FORMAT_1_RAW_DATA,
};

const tstr_twi_rhp_attr gstr_log_attr_node_1_10 = {
	.attr_index = (twi_u8)LOGGER_LOG_FORMAT,
	.parent_index = 1,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_1_10_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_1_10,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_1_10_COUNT,
};

tstr_twi_rhp_value gstr_log_attr_node_1_11_value = {
	.enu_type = U32,
	.uni_value.u32_int = 0xFFFFFFFF,
};

const tstr_twi_rhp_attr gstr_log_attr_node_1_11 = {
	.attr_index = (twi_u8)LOGGER_TIME_TO_START,
	.parent_index = 1,
	.enu_attr_type = LOGGER_ATTR,
	.b_has_active_loggers = TWI_FALSE,
	.pstr_value = &gstr_log_attr_node_1_11_value,
	.pstr_hardware = NULL,
	.enu_permission = READ_AND_WRITE,
	.ppstr_triggers = TRIGGER_POINTER_ARRAY_LOG_1_11,
	.u8_num_triggers_on_attribute = TRIGGER_POINTER_ARRAY_LOG_1_11_COUNT,
};

const tstr_twi_rhp_attr* const gapstr_logger_1_attr_to_log[] = {
	NULL,	
};

tstr_twi_rhp_value gastr_logger_1_last_wrt_value[LOGGER_1_ATTR_TO_LOG_COUNT];

const twi_u8 gaau8_log_1_dest_recv_twi_id[1][4] = {
	TWI_ALIGN_TAG_SERVER_ID,
};

#ifdef SAVE_SYSTEM_SETTINGS
static twi_u8 TWI_ALIGN gau8_logger_1_setting_buf[sizeof(tstr_rhp_logger_settings)];
#endif

tstr_twi_rhp_logger gstr_logger_1 = {
    .apstr_logger_attributes = {
        &gstr_log_attr_node_1_0,
        &gstr_log_attr_node_1_1,
        &gstr_log_attr_node_1_2,
        &gstr_log_attr_node_1_3,
        &gstr_log_attr_node_1_4,
        &gstr_log_attr_node_1_5,
        &gstr_log_attr_node_1_6,
        &gstr_log_attr_node_1_7,
        &gstr_log_attr_node_1_8,
        &gstr_log_attr_node_1_9,
        &gstr_log_attr_node_1_10,
        &gstr_log_attr_node_1_11,
        NULL
        },
#ifdef SAVE_SYSTEM_SETTINGS
    .pu8_setting_buf = gau8_logger_1_setting_buf,
#endif

	.u8_logger_index = 1,
	.u8_output_destinations = OUTPUT_CLOUD_DEST,
	.pau8_dest_recv_twi_id = gaau8_log_1_dest_recv_twi_id,
	.enu_circular_overwrite = LOGGER_CARELESS_OVERWRITE_MODE,
	.u32_total_num_logs = 0,
	.u8_num_attr_to_log = LOGGER_1_ATTR_TO_LOG_COUNT,
	.ppstr_attribute_to_log = gapstr_logger_1_attr_to_log,
	.pstr_last_write_value = gastr_logger_1_last_wrt_value,
	.u8_logger_status_flags = 0,
	.u16_log_size = TWI_ALIGN_TAG_LOG_SIZE,
	.b_need_to_push = TWI_FALSE,
    .b_no_push_logs = TWI_TRUE,
	.u32_max_memory_size = NRF52_PAGE_SIZE * ALIGN_LOGGER_1_PAGES,
	.b_log_on_start = TWI_FALSE
};

static twi_u8 gau8_save_loggers_idxs [NUM_OF_LOGGERS_TO_SAVE] =
{
	0,	/* Logger 0 */
	1,	/* Logger 1 */
};
tstr_twi_rhp_logger* const gapstr_loggers[] = {
	&gstr_logger_0,
	&gstr_logger_1,
};

static tstr_twi_rhp_resp  gastr_responses_queue[TOTAL_NUM_ATTR];
#if NUM_CLOUD_DEST_LOGGERS
static tstr_twi_rhp_attr * gapstr_cloud_dest_loggers_dispatch[NUM_CLOUD_DEST_LOGGERS];
#endif	
#if NUM_DEST1_LOGGERS	
static tstr_twi_rhp_attr * gapstr_dest1_loggers_dispatch[NUM_DEST1_LOGGERS];
#endif

static tstr_twi_loggers_save_settings_info gstr_loggers_save_settings_info =
{
	.u8_num_save_loggers = NUM_OF_LOGGERS_TO_SAVE,
	.pau8_loggers_idx = gau8_save_loggers_idxs,
};

const static tstr_twi_rhp_loggers_in gstr_loggers_in =
{
	.u8_num_loggers = NUM_LOGGERS,
	.ppstr_loggers = gapstr_loggers,
	.appstr_logger_attr_dispatch = {
#if NUM_CLOUD_DEST_LOGGERS
		gapstr_cloud_dest_loggers_dispatch, 
#endif	
#if NUM_DEST1_LOGGERS	
		gapstr_dest1_loggers_dispatch
#endif
									},
	.pstr_loggers_save_settings = &gstr_loggers_save_settings_info,
};
const tstr_twi_rhp_dst0_cmds_list gstr_dst0_cmd_list_cfg =
{
	.enu_cmds_list_type = RHP_DST0_NOT_ALLOWED_LIST,
	.u16_num_cmds = 0,
	.ppstr_msg_list = NULL,
};
static twi_u8 TWI_ALIGN	gau8_save_attrs_buf[ATTRS_BUFF_SIZE];

const tstr_twi_rhp_attr	*gapstr_save_attrs [] =
{
    &gstr_attr_node_0_0,		/* Advertising Attr*/
    &gstr_attr_node_3_0,		/* Sensor session status */
	&gstr_attr_node_3_1,		/* Mode of Operation */
};
static tstr_twi_hardwares_save_settings_info gstr_hardwares_save_settings_info =
{
	.u8_num_saved_attrs 	= TWI_ARRAY_LEN(gapstr_save_attrs),
	.u16_save_buf_size 		= ATTRS_BUFF_SIZE,
	.ppstr_saved_attr	 	= gapstr_save_attrs,
	.pau8_save_attrs_buf 	= gau8_save_attrs_buf,
};
static const tstr_twi_rhp_hardware_in gstr_hardware_in = 
{
	.u8_num_features = NUM_FEATURES,
	.ppstr_features  = gapstr_features,
	.pstr_indct_hw   = &srt_twi_rhp_indct_hw,
	.pstr_hardwares_save_settings 	= &gstr_hardwares_save_settings_info,
};

const tstr_twi_rhp_profile gstr_profile =
{
	.u16_profile_id = PROFILE_ID,
	.b_start_in_deep_sleep = TWI_FALSE,
	.pstr_status_in = NULL,
	.pstr_hardware_in = &gstr_hardware_in,
	.pstr_responses_queue = gastr_responses_queue,
	.u8_num_attr_in_dispatch = TOTAL_NUM_ATTR,
	.pstr_loggers_in = &gstr_loggers_in,
	.pstr_reports_in = NULL,
	.u8_fw_major_version = TWI_FW_MAJOR_VERSION,
	.u8_fw_minor_version = TWI_FW_MINOR_VERSION,
	.u8_fw_patch_version = TWI_FW_PATCH_VERSION,
	.pstr_triggers_in = NULL,
	.u8_num_mnfctr_except = 0,
	.ppstr_mnfctr_except = NULL,
	.u8_num_pair_except = 0,
	.ppstr_pair_except = NULL,
	.pstr_dst0_cmds_confg = &gstr_dst0_cmd_list_cfg,
};
