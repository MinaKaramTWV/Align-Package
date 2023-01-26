/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/
/**
 *	@file		twi_opp_proto.h
 *	@brief		This file holds API for the opportunistic state machine
 */

#ifndef TWI_OPP_PROTOCOL_H_
#define TWI_OPP_PROTOCOL_H_

/** @defgroup TWI_OPP_group TWI opportunistic module
 *	This module is responsible for changing advertising data periodically.
 * @{ */
#define TWI_OPP_SUCCESS								(TWI_SUCCESS)
#define TWI_OPP_ERROR_INVALID_INITIALIZER			(TWI_ERR_OPP_BASE)
#define TWI_OPP_ERROR_INVALID_EVT_FOR_STATE			(TWI_ERR_OPP_BASE - 1)
#define TWI_OPP_ERROR_INVALID_TRANSITION			(TWI_ERR_OPP_BASE - 2)
#define TWI_OPP_INVALID_ADV_MODE					(TWI_ERR_OPP_BASE - 3)
#define TWI_OPP_INVALID_TAG							(TWI_ERR_OPP_BASE - 4)
//***********************************************************
/*- INCLUDES ----------------------------------------------*/
//***********************************************************
#include "twi_common.h"
#include "timer_mgmt.h"
#include "twi_ble_hal.h"
#include "twi_ble_hal_conf.h"
#include "twi_destinations.h"

/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------------*/
/*-*********************************************************/

/*-*********************************************************/
/*- ENUMERATIONS ------------------------------------------*/
/*-*********************************************************/
/**
 * @enum           tenu_twi_opp_dest_state
 * @brief          enumeration of the possible states of the destinations
 */
typedef enum
{
	OPP_DEST_STATE_NDS, 		/**< @brief No Data State */
	OPP_DEST_STATE_DS, 			/**< @brief Data State */
	OPP_DEST_STATE_AS, 			/**< @brief Alert State */
	OPP_DEST_STATE_INVALID 		/**< @brief To indicate an invalid state */
} tenu_twi_opp_dest_state;

/**
 * @enum           _tenu_twi_opp_evt
 * @brief          enumeration of the possible events to trigger the state machine
 */
typedef enum
{
	OPP_SEND_ALERT, 		/**< @brief Send alert event */
	OPP_SEND_DATA, 			/**< @brief data alert event*/
	OPP_ALERT_SUCCESS, 		/**< @brief Event indicating that sending alert succeeded */
	OPP_DATA_SUCCESS, 		/**< @brief Event indicating that sending data succeeded  */
	OPP_EVT_INVALID 		/**< @brief Invalid Event */
} tenu_twi_opp_evt;

/** @brief The exceptional mode: ON or OFF. */
typedef enum
{
	OPP_EXP_MODE_OFF = 0,
	OPP_EXP_MODE_ON,
	OPP_INVALID_EXP_MODE,
}tenu_exp_mode;

/** @brief The opportunistic state: TEMP, BASIC, or NUDGE. */
typedef enum
{
	OPP_TEMP_STATE = 0,
	OPP_BASIC_STATE,
	OPP_NUDGE_STATE,
	OPP_INVALID_STATE,
}tenu_state;

/** @brief The opportunistic advertising mode: Mode1, Mode 2. */
typedef enum
{
	TWI_ADVERTISING_MODE_1 = 0,
	TWI_ADVERTISING_MODE_2,
	TWI_ADVERTISING_MODE_INVALID,
}tenu_twi_adv_mode;
/*-*********************************************************/
/*- STRUCTS AND UNIONS ------------------------------------*/
/*-*********************************************************/

typedef struct
{
	/** @brief Advertising mode : Mode1, Mode 2 **/
	tenu_twi_adv_mode	enu_twi_adv_mode;
	struct
	{
		/** @brief The exceptional mode: ON or OFF. */
		tenu_exp_mode 			enu_exp_mode;

		/** @brief The opportunistic state: TEMP, BASIC, or NUDGE. */
		tenu_state 				enu_state;

		/** @brief The current advertised beacon index. */
		twi_u8 					u8_beacon_idx;

		/**	@brief	This is a Boolean that indicates the Swap Timer update is fired. */
		twi_bool				b_swap_timer_update;

	}str_twi_mode_one_info;

	/** @brief The current state of each destination: NDS, DS, or AS. */
	tenu_twi_opp_dest_state	aenu_dest_states[OUTPUT_DESTS_NUM];

	/** @brief This is a Boolean that indicates that all destinations are in NDS. */
	twi_bool 				b_is_all_dest_in_nds;

}tstr_twi_opp_status;

/** @brief This is a callback function that is called by the opportunistic when its current status changes.*/
typedef void (*tpf_twi_opp_status_cb) (tstr_twi_opp_status* pstr_opp_current_status);

/**
 *	@struct		tstr_twi_app_adv_data
 *	@brief		structure which has advertising data
 */
typedef struct
{
	twi_u8 		au8_buf[TWI_ADV_DATA_LEN];	/**< @brief This data is used in the advertising packet. */
	twi_u8 		u8_app_len ;			/**< @brief This is length of "application" data used in the advertising packet.*/
}tstr_twi_app_adv_data;

/**
 *	@struct		tstr_twi_opp_in
 *	@brief		structure used to initialize the module
 */
typedef struct
{
	/** @brief  profile id from RHP layer. */
	twi_u16 				u16_profile_id;
	/** @brief 	Initial ANDROID/APPLE beacons swapping interval.
		This is the interval that will be used to swap between Apple and Android beacons. */
	twi_u16 				u16_init_beacon_swap_int_ms;
	/** @brief  serial number to be used as public ID for this device. */
	const twi_u8* 			pu8_device_serial;
	/** @brief Pointer to the CB Function */
	tpf_twi_opp_status_cb	pf_opp_state_cb;
} tstr_twi_opp_in;

typedef struct
{
	twi_u8*	pu8_app_data;
	twi_u8	u8_length;
	twi_u8	u8_tag;
}tstr_twi_app_spec_data;

/*-*********************************************************/
/*- FUNCTION DECLARATIONS ---------------------------------*/
/*-*********************************************************/

/**
 * @function		twi_s32   twi_opp_init(twi_const tstr_twi_opp_in * pstr_in)
 * @brief      		This function initializes the opportunistic module.
 * @param[in]  		*pstr_in        Pointer to module input structure.
 * @param[out] 		**ppstr_out		Pointer to pointer to structure that holds module's APIs.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_opp_init(twi_const tstr_twi_opp_in * pstr_in);

/**
 * @function		twi_s32   twi_opp_change_device_serial(twi_const twi_u8* pu8_device_serial)
 * @brief      		This function changes the device serial, TWI_ID
 * @param[in]  		pu8_device_serial       The New Device Serial.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_opp_change_device_serial(twi_const twi_u8* pu8_device_serial);

/**
 * @function		twi_s32   twi_opp_new_opp_event(twi_u8 u8_dest_idx, tenu_twi_opp_evt enu_evt)
 * @brief			This function is used to advertise new event according to the opp state machine.
 * @param[in]		u8_dest_idx: Index of the destination that generates that event.
 * @param[in]		enu_evt: Type of event
 * @return			::TWI_OPP_SUCCESS if the opportunistic state machine indicates it's a valid transition.
 */
twi_s32 twi_opp_new_opp_event(twi_u8 u8_dest_idx, tenu_twi_opp_evt enu_evt);

/**
 * @function		twi_s32 twi_opp_start_exp_mode(void)
 * @brief			This function changes the mode of the opportunistic state machine to the exceptional mode.
 * @return			::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
 twi_s32 twi_opp_start_exp_mode(void);
 
 /**
  * @function		twi_s32 twi_opp_set_twiBeacon_app_adv_data(twi_u32 u32_app_data)
  * @brief			This function sets the user data for twi beacon to be advertised.
  * @param[in]		pu8_adv_data: 	pointer to adv data which will be inserted in the advertised data.
  * @param[in]		u8_size: 	size of the advertised data.
  * @return			::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
  */
 twi_s32 twi_opp_set_twiBeacon_app_adv_data(twi_u8* pu8_adv_data,twi_u8 u8_size);

/**
 *	@function	twi_opp_set_beacon_swap_int
 *	@brief		This function Sets the Android/APPLE beacons swap interval.
 *	@param[in]	u16_adv_int		the new advertising interval
 *	@return		::TWI_SUCCESS in case of success, otherwise, refer to @twi_retval.h.
 */
twi_s32	twi_opp_set_beacon_swap_int(twi_u16	u16_adv_int);

/**
 *	@function	 twi_s32   twi_opp_adv_beacon(twi_u8 u8_beacon_idx, twi_u8 u8_beacon_max_timeout_sec, twi_u8 u8_beacon_min_timeout_sec)
 *	@brief		 Function used to advertise beacon of specific index.
 *	@param[in]	 u8_beacon_idx				 Index of the beacon to be advertised.
 *	@param[in]	 u8_beacon_min_timeout_sec	 This is the time of the none interruptible period.
 *											 It is guaranteed to nudge the beacon with this time even if there is new nudge request.
 *	@param[in]	 u8_beacon_max_timeout_sec	 This is the total period of nudging.
 *											 If there is no new nudge request during this period,
 *											 the beacon will continue nudge till the end of this period.
 *	@return 	::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_opp_adv_beacon(twi_u8 u8_beacon_idx, twi_u8 u8_beacon_min_timeout_sec, twi_u8 u8_beacon_max_timeout_sec);

/**
 * @function		void   twi_opp_dispatch(void)
 * @brief			Dispatch function of TWI opportunistic module.
 */
void twi_opp_dispatch(void);

 /**
 * @function		twi_opp_config_transition_timing
 * @brief      		This function Re-configures the opp layer
 * @param[in]  		u16_basic_states_timeout    Time (IN SECONDS) of advertising the basic states before changing the adv data to temp states.
 * @param[in]	 	u16_temp_states_timeout		Time (IN SECONDS) of advertising the temp states before changing the adv data to basic states.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_opp_config_transition_timing(twi_u16 u16_basic_states_timeout, twi_u16 u16_temp_states_timeout);

/**
* @function			twi_opp_set_app_spec_data(twi_u8* pu8_app_data,twi_u8 u8_length,twi_u8 u8_tag)
* @brief      		This function set app specific data in the right place depends on adv mode
* @param[in]  		pu8_app_data: 	Pointer to app data.
* @param[in]  		u8_length: 		app data length.
* @param[in]  		u8_tag:		 	tag of app data.
* @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
*/
twi_s32 twi_opp_set_app_spec_data(twi_u8* pu8_app_data,twi_u8 u8_length,twi_u8 u8_tag);

/**
 * @function		twi_opp_get_app_spec_data(twi_u8* pu8_app_data,twi_u8 u8_length,twi_u8 u8_tag)
 * @brief      		This function get app specific data depends on adv mode
 * @param[in]  		u8_tag:		 	tag of app data.
 * @param[out]  	pu8_app_data: 	Pointer to app data.
 * @param[out]  	pu8_length: 	Pointer to app data length.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
*/
twi_s32 twi_opp_get_app_spec_data(twi_u8* pu8_app_data,twi_u8* pu8_length,twi_u8 u8_tag);

/**
* @function		twi_opp_change_adv_mode
* @brief      		This function switch between advertising modes
* @param[in]  		tenu_twi_adv_mode enu_twi_adv_mode (TWI_ADVERTISING_MODE_1,TWI_ADVERTISING_MODE_2)
* @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
*/
twi_s32 twi_opp_change_adv_mode(tenu_twi_adv_mode enu_twi_adv_mode);

/**
 * @function		twi_opp_proto_update_adv_count;
 * @brief      		This function update advertising packet count field.
 * @param[in]  		u32_adv_pkt_time_ms:	the time of updating adv packet.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_opp_proto_update_adv_count(twi_u32 u32_adv_pkt_time_ms);

/**
 * @function		twi_opp_proto_disable_adv_pkt_count;
 * @brief      		This function disable advertising packet count field.
 */
void twi_opp_proto_disable_adv_pkt_count(void);

/**
 * @function		twi_opp_proto_get_adv_pkt_count;
 * @brief      		This function get advertising packet count field.
 */
void twi_opp_proto_get_adv_pkt_count(twi_u32 * u32_adv_pkt_time_ms);

/**
 * @function		twi_opp_proto_reset_adv_pkt_count_timer;
 * @brief      		This function reset advertising packet timer.
 */
void twi_opp_proto_reset_adv_pkt_count_timer(void);

#if defined (SAVE_SYSTEM_SETTINGS)
/**
 *	@function	twi_s32 twi_opp_load_settings(void)
 *	@brief		This function is used to load the OPP settings from the flash memory.
 *	@return     ::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_opp_load_settings(void);
#endif

/** @} */ /* TWI_OPP_group */
#endif /* TWI_OPP_PROTOCOL_H_ */
