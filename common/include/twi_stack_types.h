/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_stack_types.h
*   @brief      This file contains TWI Common data types definitions that are shared between the different TWI stack layers.
*/

#ifndef _TWI_STACK_TYPES_H_
#define _TWI_STACK_TYPES_H_
 
/***********************************************************/
/*- INCLUDES ----------------------------------------------*/
/***********************************************************/

#include "twi_common.h"

/** @defgroup TWI_STACK_TYPES_group TWI STACK Types.
 * It contains structures and Enums that are used by the different TWI Stack layers
 * @{
 */

/*-***********************************************************/
/*- Global MACROS -------------------------------------------*/
/*-***********************************************************/
#define PEER_TWI_ID_SIZE 		(4)
#define TWI_OTA_SYS_STATE_SZ	(1)
#define SDK_UNLOCKED_STATE      (0)
/*-***********************************************************/
/*- ENUMERTAIONS --------------------------------------------*/
/*-***********************************************************/
/**
 *	@enum		tenu_sys_status
 *	@brief		ENUM of system status.
 */
typedef enum
{
	SYS_STATE_READY = 0,
	SYS_STATE_INTERNAL_SW_ERR,
    SYS_STATE_HAVE_LOGS,
    SYS_STATE_LOW_BATTERY,
    SYS_STATE_FLASH_SAVING,
    SYS_STATE_INVALID_FW_INFO,
}tenu_sys_status;

/**
 *	@enum		tenu_sdk_locking_reasons
 *	@brief		ENUM of Locking Reasons.
 */
typedef enum
{
	LOCK_STATE_INV_CONS_INDX,
    LOCK_MAX_NUM_CONS_INDX,
    LOCK_STATE_GRACE_PERIOD_INDX,
    LOCK_PHONE_USER_INDX,
    LOCK_COUNTERFEIT_INDX,
    LOCK_MAX_USAGE_COUNT_INDX ,
    LOCK_UNPAIRING_INDX,
} tenu_sdk_locking_reasons;

/**
 *	@enum		tenu_rhp_notify_connected_evt
 *	@brief		enumeration of the rhp Notification type for the connected peer device.
 */
typedef enum
{
	NTFY_HAS_ALERT_EVT = 0,				/**< @brief Application has alert to send */
	NTFY_HAS_MSG_EVT,					/**< @brief Application has message to send */
	NTFY_HAS_LOGS_EVT,					/**< @brief Application has logs to send */
	NTFY_HAS_REPORT_EVT,				/**< @brief Application has report to send */
	NTFY_HAS_PERIDIC_NOTIFY_EVT,		/**< @brief Application want to notify */
    NTFY_HAS_SPECIFIC_DATA_EVT,          /**< @brief Application has a specific data */
    NTFY_SDK_HAS_SPECIFIC_DATA_EVT,          /**< @brief SDK has aspecific data */
    NTFY_SDK_HAS_PERIDIC_NOTIFY_EVT,		/**< @brief SDK has periodic data to notify */
	NTFY_APP_HAS_SPECIFIC_PAYLOAD_EVT,
	NTFY_DVC_SDK_STATUS, /**< @brief Application notify the state of the SDK(Paired,Unpared,Ready to pair) */
    NTFY_APP_REQUEST_SPECIFIC_DATA_EVT,     /**< @brief APP request a specific data */
} tenu_twi_ntfy_cnnctd_evt;


typedef enum
{
		UNPAIRED_STATE,
		READY_TO_PAIR_STATE,
		PAIRED_STATE
}tenu_firmware_state;

typedef enum
{
	NUDGE_PRIORITY_HIGH = 0,
	NUDGE_PRIORITY_LOW,
	NUDGE_PRIORITY_IMMEDIATE,
}tenu_nudge_priority;
/*-***********************************************************/
/*- STRUCTS AND UNIONS --------------------------------------*/
/*-***********************************************************/

/**
 *	@struct		tuni_twi_ntfy_cnnctd_evt_data
 *	@brief		Union that holds Notify events data
 */
typedef union _uni_evt_data
{
	struct
	{
		twi_u8 						u8_parent_idx;
		twi_u8 						u8_alrt_msg_idx;
	}str_has_alert_msg_data;
  struct
	{ 
		twi_u8                      u8_opcode;
		twi_u8 						u8_parent_idx;
		twi_u8                      u8_specific_msg_idx;
	}str_has_specfic_msg_data;
	
	struct
	{
		twi_u8 u8_reserved : 4 ;
        twi_u8 u8_session_availability : 1 ;
		twi_u8 u8_tp_version : 3 ;
		twi_u8	u8_firmware_state ;
		twi_u8 au8_peer_twi_id[PEER_TWI_ID_SIZE];
	}str_firmware_state;
	
	twi_u8 							u8_logger_idx;

	twi_u8 							u8_report_idx;

	twi_u8 							u8_periodic_notify_idx;

}tuni_twi_ntfy_cnnctd_evt_data;
	
/**
 *	@struct		tstr_ntfy_cnnctd_rqst_data
 *	@brief		structure that holds Notify events definition
 */
typedef struct
{
	tenu_twi_ntfy_cnnctd_evt		enu_evt_type;
	twi_u8					u8_output_destinations;
	tuni_twi_ntfy_cnnctd_evt_data		uni_evt_data;
	tenu_nudge_priority enu_nudge_priority;
}tstr_twi_ntfy_cnnctd_rqst_data;

/** @} */

#endif  /*_TWI_STACK_TYPES_H_*/
