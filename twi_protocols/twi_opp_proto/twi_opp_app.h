/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/
/**
 *	@file		twi_opp_app.h
 *	@brief		This file implements the mode 2 of advertising
 *				each product will implement it by itself.
 */

#ifndef TWI_OPP_APP_H_
#define TWI_OPP_APP_H_

/** @defgroup TWI_OPP_APP_group TWI opportunistic module
 *	This module is responsible for set and advertising data for mode 2.
 * @{ */
 
//***********************************************************
/*- INCLUDES ----------------------------------------------*/
//***********************************************************
#include "twi_common.h"
#include "twi_opp_proto.h"
#include "twi_opp_cfg.h"

/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------------*/
/*-*********************************************************/

/*-**********************************************************/
/*- ENUMERATIONS -------------------------------------------*/
/*-**********************************************************/
/** @brief Using for mapping between data tags and adv mode 1 */
typedef enum
{
	TWI_MODE_1_INVALID_DATA = 0,
	TWI_MODE_1_ADV_DATA,
	TWI_MODE_1_SCAN_RSP,
}tenu_twi_adv_mode_1_map;


/*-*********************************************************/
/*- STRUCTS AND UNIONS ------------------------------------*/
/*-*********************************************************/
/**
 *	@struct		tstr_twi_opp_adv_pure_data
 *	@brief		structure used to store adv data
 */
typedef struct
{
	tenu_twi_opp_dest_state	aenu_dest_states[OUTPUT_DESTS_NUM];
#ifdef ADV_PKT_COUNTER_ENABLED
	twi_u8	u8_adv_count;
#endif
	twi_u16 u16_profile_id;
	twi_u16 u16_device_serial_msb;
	twi_u16 u16_device_serial_lsb;
	twi_u8*	pu8_app_spec_data;
}tstr_twi_opp_adv_pure_data;

/*-*********************************************************/
/*- FUNCTION DECLARATIONS ---------------------------------*/
/*-*********************************************************/
#if (TWI_ADV_MODE == TWI_ADV_MODE_2) || (TWI_ADV_MODE == TWI_ADV_MODE_BOTH)
/**
 * @function			twi_opp_app_format_data();
 * @brief      		This function format the data in its place in advertising packet.
 * @param[in]  		pstr_adv_pure_data:		information of adv data.
 * @param[in]  		pstr_adv_data:			Pointer to advertising data.
 * @param[in]  		pstr_scan_rsp:			Pointer	to scan response data.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_opp_app_format_data(twi_const tstr_twi_opp_adv_pure_data* pstr_adv_pure_data,
									tstr_twi_adv_data* pstr_adv_data,tstr_twi_adv_data* pstr_scan_rsp);

/**
 * @function			twi_opp_app_update_adv_count();
 * @brief      		This function update advertising packet count field.
 * @param[in]  		u8_adv_count:				adv_count in adv packet
 * @param[in]  		pstr_adv_data:			Pointer to advertising data.
 * @param[in]  		pstr_scan_rsp:			Pointer	to scan response data.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */

twi_s32 twi_opp_app_update_adv_count(twi_const twi_u8 u8_adv_count,tstr_twi_adv_data* pstr_adv_data,tstr_twi_adv_data* pstr_scan_rsp);
#endif

/** @} */ /* TWI_OPP_APP_group */
#endif /* TWI_OPP_APP_H_ */
