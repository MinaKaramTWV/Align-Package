/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file					twi_rhp.h
 ** @brief					This file includes the interface of the Remote HAL Protocol that can be used from the app-specific file.
 */

#ifndef TWI_RHP_H_
#define TWI_RHP_H_

/** @defgroup TWI_RHP_group TWI RHP-APP Interface.
 * It contains functions, structures and Enums that can be used by the application specific file that describes the application behavior together with its profile.
 * @{
 */
/***********************************************************/
/*- INCLUDES ----------------------------------------------*/
/***********************************************************/

#include "twi_common.h"
#include "twi_rhp_types.h"
#include "twi_power_mgmt.h"

/*-***********************************************************/
/*- Global MACROS --------------------------------------------*/
/*-***********************************************************/

/** @brief This macro gets the next engine mode*/
#define GET_NXT_ENG_MODE(CUR_MODE)			( ((CUR_MODE + 1) == INVALID_MODE )? 0 : (CUR_MODE + 1) )

/*-***********************************************************/
/*- ENUMERATIONS --------------------------------------------*/
/*-***********************************************************/

/**
 *	@enum		tenu_rhp_engine_cmd_status
 *	@brief		enumeration of possible RHP engine commands permissions
 */
typedef enum
{
	NOT_ALLOWED_RHP_CMD = 0,
	ALLOWED_RHP_CMD,
	UNRELATED_RHP_CMD
}tenu_rhp_engine_cmd_status;


/*-***********************************************************/
/*- STRUCTS AND UNIONS --------------------------------------*/
/*-***********************************************************/

typedef void(*tpf_twi_engine_sys_mode_cb)(tenu_rhp_engine_sys_mode enu_engine_mode);

/**
 *	@enum		_tstr_twi_rhp_rcv_app_msg
 *	@brief		structure of received msg which is sent to app specific file
 */
typedef struct
{
	/** @brief Pointer to receiver id. */
	twi_u8* 				pu8_sender_id;
	/** @brief Pointer to message. */
	tstr_twi_rhp_msg* 		pstr_msg;
}tstr_twi_rhp_rx_app_msg;

/**
 *	@struct		_tstr_rhp_app_save_setting
 *	@brief		This structure holds the App settings to be saved by settings module.
 */
typedef struct
{
	twi_bool	b_save_in_progress;
	twi_u8		u8_need_to_save;
	twi_u16		u16_buf_len;
	twi_u8*		pu8_buf;
}tstr_rhp_app_save_setting;

/**
 *	@struct		tstr_twi_rhp_app_in
 *	@brief		This structure holds the App Configurations to be passed to app.
 */
typedef struct
{
    tenu_power_mgmt_wakeup_reason enu_wakeup_reason;
}tstr_twi_rhp_app_in;

/**
 *	@struct		tstr_twi_rhp_app_load_in
 *	@brief		This structure holds the Load Configurations to be passed to app load.
 */
typedef struct
{
    tenu_power_mgmt_wakeup_reason enu_wakeup_reason;
}tstr_twi_rhp_app_load_in;
/*-***********************************************************/
/*- FUNCTIONS' PROTOTYPES -----------------------------------*/
/*-***********************************************************/
/**
 * @function	twi_rhp_app_pre_sys_init
 * @brief		This function is implemented by the application to pre system initialize the app-specific file.
 * @return     	::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_app_pre_sys_init(void);

/**
 * @function	twi_rhp_app_init
 * @brief		This function is implemented by the application to initialize the app-specific file.
 * @return     	::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_app_init(const tstr_twi_rhp_app_in* pstr_twi_rhp_app_in, tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy);


/**
 * @function	twi_rhp_app_deinit
 * @brief		This function is implemented by the application to de-initialize the app-specific file.
 * @return     	::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
void twi_rhp_app_deinit(void);
/**
 * @function    twi_rhp_app_load
 * @brief       This function loads app-specific data from flash memory
 * @return      ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_app_load(const tstr_twi_rhp_app_load_in* pstr_twi_rhp_app_load_in);
/**
 * @function		twi_rhp_engine_get_att_update_handler
 * @brief			This function is implemented by the application to handle the updating of attribute value to be get from RHP Engine.
 * @param[in]		pstr_twi_rhp_attr		: Pointer to the att.
 * @return     		::void
 */
#ifdef TWI_UPDATE_GET_ATTRIBUTE
void twi_rhp_engine_get_att_update_handler(const tstr_twi_rhp_attr * pstr_twi_rhp_attr);
#endif
/**
 * @function		twi_rhp_engine_evt_handler
 * @brief			This function is implemented by the application to handle events that will be sent to it from RHP Engine.
 * @param[in]		enu_engine_evt	: Engine Event.
 * @param[in]		pv_evt_data		: Engine Event Data.
 * @return     		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
void twi_rhp_engine_evt_handler(tenu_rhp_engine_evt_type enu_engine_evt, void* pv_evt_data);

/**
 * @function		twi_rhp_app_evt_handler
 * @brief			This function is implemented by the application to handle events that will be sent to it from the profile.
 * @param[in]		u8_app_event:		Application Event index.
 * @param[in]		u8_attr_num:		Number of attributes.
 * @param[in,out]	ppstr_attrs:		Array of attributes sent as event data.
 */
void twi_rhp_app_evt_handler(twi_u8 u8_app_event, twi_u8 u8_attr_num, const tstr_twi_rhp_attr* const* ppstr_attrs);

/**
 * @function		twi_rhp_app_dispatch
 * @brief			This function is implemented by the application to be called in the program main loop.
 * @return     		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
void twi_rhp_app_dispatch(void);

/**
 * @function		twi_rhp_write_attr
 * @brief			Write an attribute function.
 * @param[in]		pstr_attr:		Attribute to be written.
 * @param[in]		pstr_value:		value to be written to the attribute.
 * @return     		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_write_attr(const tstr_twi_rhp_attr *pstr_attr, const tstr_twi_rhp_value *pstr_value);

/**
 * @function		twi_rhp_get_attr_ptr
 * @brief			get an attribute pointer.
 * @param[IN]		enu_attribute_type:	attr type.
 * @param[IN]		u8_feat_idx:	feature index.
 * @param[IN]		u8_attr_idx:	attribute index.
 * @return     		pstr_attr:		Attribute pointer to be got, NULL in case of error or not found.
 */
const tstr_twi_rhp_attr* twi_rhp_get_attr_ptr(tenu_rhp_attribute_type enu_attribute_type, twi_u8 u8_feat_idx, twi_u8 attr_idx);

/**
 * @function		twi_rhp_read_attr
 * @brief			Read an attribute function.
 * @param[in]		pstr_attr:		Attribute to be read.
 * @param[out]		pstr_value:		value to read in it.
 * @return     		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_read_attr(const tstr_twi_rhp_attr *pstr_attr, tstr_twi_rhp_value *pstr_value);

/**
 * @function		twi_rhp_send_action
 * @brief			Send alert/message message
 * @param[in]		enu_action_type: 	This is the action type (Alert/Message).
 * @param[in]		u8_action_idx: 		Index of the Alert/Message. Each alert/msg has to have a unique index.
 * @param[in]		u8_output_destinations: U8 that represents the channels that will be used to forward this action.
 * @param[in]		pau8_dest_recv_twi_id: Array of TWI_IDs each one is used as a receiver TWI_ID in sending the Alert/Message. 
 * @param[in]		ppstr_action_attrs: Array of attributes that will be sent in the alert/message.
 * @param[in]		u8_action_attrs_num: number of attributes to be sent in the alert/msg message.
 * @return     		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_send_action(tenu_action_type enu_action_type, twi_u8 u8_action_idx, twi_u8 u8_output_destinations,
								const tau8_twi_id *pau8_dest_recv_twi_id, const tstr_twi_rhp_attr* const* ppstr_action_attrs, twi_u8 u8_action_attrs_num);

/**
 * @function		twi_rhp_send_notify_status
 * @brief			This function is used to send and/or Notify the connected peer with the status message
 * @return     		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_send_notify_status(void);

/**
 * @function		twi_rhp_enter_deep_sleep
 * @brief			Enter the deep sleep mode
 * @return     		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_enter_deep_sleep(void);

/**
 * @function		twi_rhp_event_logger_log
 * @brief			Take a log from an event-based logger
 * @param[in]		u8_logger_idx: Logger index
 * @return     		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_event_logger_log(twi_u8 u8_logger_idx);

/**
 * @function		twi_rhp_adv_beacon
 * @brief			Advertise beacon
 * @param[in]		u8_beacon_idx: 			Beacon Index.
 * 											If the u8_min_timeout_sec = u8_max_timeout_sec = 0, then this is an index of the adv_beacon Array.
 * 											Otherwise it is an index of nudge_beacon array.
 * @param[in]		u8_min_timeout_sec: 	This is the non-interruptible period in seconds.
 * 											It is guaranteed to nudge the beacon with this time even if there is new nudge request.
 * @param[in]		u8_max_timeout_sec: 	This is the maximum period of nudging.
 * 											If there is no new nudge request during this period,
 * 											the beacon will continue to nudge till the end of this period.
 * @return     		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_adv_beacon(twi_u8 u8_beacon_idx, twi_u8 u8_min_timeout_sec, twi_u8 u8_max_timeout_sec);

/**
 * @function		twi_rhp_start_advertise
 * @brief			Start advertising Data/Alert beacons for the given destinations
 * @param[in]		u8_destinations: 		Destinations to start advertising for them
 * @param[in]		enu_adv_state: 			State to be advertised. For more information see @ref tenu_adv_state
 */
void twi_rhp_start_advertise(twi_u8 u8_destinations, tenu_adv_state enu_adv_state);

/**
 * @function		twi_rhp_stop_advertise
 * @brief			Stop advertising Data/Alert beacons for the given destinations
 * @param[in]		u8_destinations: 		Destinations to stop advertising for them
 * @param[in]		enu_adv_state: 			State to stop advertising for it. For more information see @ref tenu_adv_state
 */
void twi_rhp_stop_advertise(twi_u8 u8_destinations, tenu_adv_state enu_adv_state);

/**
 * @function		twi_s32	twi_rhp_change_device_twi_id(twi_const twi_u8* pu8_device_twi_id)
 * @brief      		This function changes the device TWI-ID
 * @param[in]  		pu8_device_twi_id       The New Device TWI-ID.
 * @return     		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_change_device_twi_id(twi_const twi_u8* pu8_device_twi_id);

/**
 *	@function	twi_s32 twi_rhp_direct_send(twi_u32 u32_rcv_twi_id, const tstr_twi_rhp_msg** ppstr_msg_list, twi_u16 u16_num_msg)
 *	@brief		Function used to send list of commands defined by the application.
 *	@param[in]	u32_rcv_twi_id				TWI-ID of receiver that the app wants to send these messages to.
 *	@param[in]	tstr_twi_rhp_send_info		List of messages the app wants to send and its callback.
 *	@param[in]	u8_num_msg					Number of messages want to send.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_direct_send(twi_u32 u32_rcv_twi_id, const tstr_twi_rhp_send_info* pstr_msg_info, twi_u8 u8_num_msg);

/**
 * @function		twi_rhp_is_clear_to_send
 * @brief			Check if the RHP Engine is clear to send.
 * @param[out]		pb_is_cts: 					::TWI_TRUE if the engine is clear to send, ::TWI_FALSE otherwise.
 * @param[out]		pu8_output_dest_idx			The index of destination that is clear to send.
 * @param[out]		pu8_peer_twi_id:			Array of U8 that represents TWI_ID of the peer device. This pointer should pointing to an array with size ::TWI_ID_SIZE.
 * @return     		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_is_clear_to_send(twi_bool* pb_is_cts, twi_u8* pu8_output_dest_idx, twi_u8* pu8_peer_twi_id);

/**
 *	@function	twi_s32 twi_rhp_app_save_settings
 *	@brief		This function is used to save application settings.
 *	@param[in]	pau8_settings_buf		pointer to the buffer to be saved into.
 *	@param[in]	u16_buf_len				Length of the buffer
 */
void twi_rhp_app_save_settings(twi_u8 *pu8_settings_buf, twi_u16 u16_buf_len, void *pv);

/**
 *	@function	twi_s32 twi_rhp_app_load_settings
 *	@brief		Function used to load application settings.
 *	@param[in]	pau8_settings_buf		pointer to the buffer to load into.
 *	@param[in]	u16_buf_len				Length of the buffer
 * @return     	::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_app_load_settings(twi_u8 *pu8_settings_buf, twi_u16 u16_buf_len);

/**
 *	@brief		This function Manages the saving process for App, it checks if the app needs to save twice or more, it will manage to let the app save the latest data once.
 *	@param[in]	b_save_in_progress		A boolean that the user should create to indicate whether this module called ::twi_settings_save() and it returned with ::TWI_SUCCESS.
 *	@param[out]	pu8_need_to_save_cnt	Pointer to a counter that the user will create to indicate how many times this module needed to save.
 * @return     	::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_app_save_settings_counter(twi_bool b_save_in_progress, twi_u8 *pu8_need_to_save_cnt);

/**
 *	@brief		This function Manages the App saving process, it checks if the module still needs to save.
 *	@param[out]	pu8_need_to_save_cnt			Pointer to a counter that the user will create to indicate how many times this module needed to save.
 */
void twi_rhp_app_settings_still_need_to_save(twi_u8 *pu8_need_to_save_cnt);

/** @} */
#endif /* TWI_RHP_H_ */
