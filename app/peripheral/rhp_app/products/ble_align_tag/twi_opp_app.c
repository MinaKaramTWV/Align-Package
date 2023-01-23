/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved.					*/
/****************************************************************************/

/**
 *	@file		twi_opp_app.c
 *	@brief		This file implements the mode 2 of advertising
 *				each product will implement it by itself.
 */

/*-*********************************************************/
/*- INCLUDES ----------------------------------------------*/
/*-*********************************************************/
#include "twi_opp_app.h"
#include "twi_debug.h"
#include "twi_ble_hal.h"
#include "twi_ble_hal_conf.h"
#include "twi_destinations.h"
#include "twi_opp_cfg.h"
#include "twi_rhp_ble_align_tag.h"


/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------------*/
/*-*********************************************************/

#ifdef OPP_LOG_ENABLE
	#define OPP_APP_LOG(...)								TWI_LOGGER("[OPP_APP]: "__VA_ARGS__)
	#define OPP_APP_LOG_ERR(...)							TWI_LOGGER_ERR("[OPP_APP_ERR]: "__VA_ARGS__)
	#define OPP_APP_LOG_COMBINED(MSG,NUM)					TWI_LOGGER("[OPP_APP]: %s,%d\n",MSG,NUM)
	#define OPP_APP_LOG_BUF_HEX(MSG, HEX_BUFFER, LEN)		do											\
														{											\
															TWI_LOGGER("[OPP_APP]: ");	\
															TWI_DUMP_BUF(MSG, HEX_BUFFER, LEN);	\
														}while(0)
	#define OPP_APP_ERR_COMBINED(MSG,NUM)				TWI_LOGGER_ERR("[OPP_APP_ERR]: %s,%d\n",MSG,NUM)
#else
	#define OPP_APP_LOG(...)
	#define OPP_APP_LOG_ERR(...)
	#define OPP_APP_LOG_COMBINED(MSG,NUM)
	#define OPP_APP_LOG_BUF_HEX(MSG,BUF,LEN)
	#define OPP_APP_ERR_COMBINED(MSG,NUM)
#endif

/*************************************************************************************/



/** Destination Status truth table brief **/
#define	NORMAL_STATE_CLOUD_PDM					(0x00)

#if (TWI_ADV_MODE == TWI_ADV_MODE_2) || (TWI_ADV_MODE == TWI_ADV_MODE_BOTH)

/*-**********************************************************/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*-**********************************************************/

/*----------------------------------------------------------*/

/*-**********************************************************/
/*- GLOBAL EXTERN VARIABLES --------------------------------*/
/*-**********************************************************/

/*----------------------------------------------------------*/

/*-**********************************************************/
/*- GLOBAL CONSTANT VARIABLES ------------------------------*/
/*-**********************************************************/


/*-*********************************************************/
/*- GLOBAL STATIC VARIABLES -------------------------------*/
/*-*********************************************************/

/*-*********************************************************/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/*-*********************************************************/

#endif


/**
 * @function			twi_opp_app_format_data();
 * @brief      		This function format the data in its place in advertisng packet.
 * @param[in]  		pstr_adv_pure_data:		information of adv data.
 * @param[out]  	pstr_adv_data:			Pointer to advertising data.
 * @param[in]  		pstr_scan_rsp:			Pointer	to scan response data.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */


twi_s32 twi_opp_app_format_data(twi_const tstr_twi_opp_adv_pure_data* pstr_adv_pure_data,
									tstr_twi_adv_data* pstr_adv_data,tstr_twi_adv_data* pstr_scan_rsp)
{
	twi_s32 s32_result;
	s32_result = TWI_SUCCESS;

		
	#if (TWI_ADV_MODE == TWI_ADV_MODE_2) || (TWI_ADV_MODE == TWI_ADV_MODE_BOTH)
	if( (NULL != pstr_adv_pure_data) && (NULL != pstr_adv_data) &&
		(0 != pstr_adv_data->u8_manu_adv_data_size)&&(NULL != pstr_adv_data->pu8_manu_adv_data)&&
		(0 != pstr_adv_data->u8_incomplete_128uuid_size)&&(NULL != pstr_adv_data->pu8_incomplete_128uuid))
	{
		tstr_twi_manu_data*	 pstr_manu;
		pstr_manu = (tstr_twi_manu_data*)pstr_adv_data->pu8_manu_adv_data;
					TWI_LOGGER ("pstr_manu->u16_manu_data_sz = %d\r\n",pstr_manu->u16_manu_data_sz);
					TWI_LOGGER ("pstr_manu->u16_company_identifier = %d\r\n",pstr_manu->u16_company_identifier);
					TWI_LOGGER ("pstr_manu->pu8_manu_data = %d\r\n",pstr_manu->pu8_manu_data);

		if((0 != pstr_manu->u16_manu_data_sz) && (NULL != pstr_manu->pu8_manu_data)
			&& (COMPANY_IDENTIFIER_TWI == pstr_manu->u16_company_identifier) )
		{


			tstr_twi_manu_data_mode_2_info* pstr_twi_beacon;
			tstr_twi_srvc_128_data_mode_2_info * pstr_twi_srvc_128_data;
			twi_u16 u16_temp =0;

			pstr_twi_beacon =(tstr_twi_manu_data_mode_2_info*)pstr_manu->pu8_manu_data;
			pstr_twi_srvc_128_data = (tstr_twi_srvc_128_data_mode_2_info *)pstr_adv_data->pu8_incomplete_128uuid;

				TWI_LOGGER("pstr_adv_pure_data->u16_device_serial_msb = %d\r\n",pstr_adv_pure_data->u16_device_serial_msb);
				TWI_LOGGER("pstr_adv_pure_data->u16_device_serial_lsb = %d\r\n",pstr_adv_pure_data->u16_device_serial_lsb);
			
			/*set manufacture data*/
			u16_temp = HTONS(pstr_adv_pure_data->u16_device_serial_msb);
			TWI_MEMCPY(pstr_twi_beacon->au8_twi_id, &u16_temp,2);
			u16_temp = HTONS(pstr_adv_pure_data->u16_device_serial_lsb);
			TWI_MEMCPY(&pstr_twi_beacon->au8_twi_id[2], &u16_temp,2);

#ifdef ADV_PKT_COUNTER_ENABLED
			pstr_twi_beacon->u8_adv_count = pstr_adv_pure_data->u8_adv_count ;		/** Advertising count **/
#endif

			pstr_twi_srvc_128_data->u8_dstn_stats_brief = 1;

		}
		else
		{


			s32_result = TWI_ERROR_INVALID_ARGUMENTS;
		}
	}
	else
	{
		s32_result = TWI_ERROR_INVALID_ARGUMENTS;
	}
#endif
	return s32_result;
}


/**
 * @function			twi_opp_app_update_adv_count();
 * @brief      		This function update advertising packet count field.
 * @param[in]  		u8_adv_count:				adv_count in adv packet
 * @param[in]  		pstr_adv_data:			Pointer to advertising data.
 * @param[in]  		pstr_scan_rsp:			Pointer	to scan response data.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */

twi_s32 twi_opp_app_update_adv_count(twi_const twi_u8 u8_adv_count,tstr_twi_adv_data* pstr_adv_data,tstr_twi_adv_data* pstr_scan_rsp)
{
	twi_s32 s32_result;
	s32_result = TWI_SUCCESS;
#ifdef ADV_PKT_COUNTER_ENABLED
#if (TWI_ADV_MODE == TWI_ADV_MODE_2) || (TWI_ADV_MODE == TWI_ADV_MODE_BOTH)

	if(NULL != pstr_adv_data)
	{
		tstr_twi_manu_data*	 pstr_manu;
		pstr_manu = (tstr_twi_manu_data*)pstr_adv_data->pu8_manu_adv_data;

		if((0 != pstr_manu->u16_manu_data_sz) && (NULL != pstr_manu->pu8_manu_data)
			&& (COMPANY_IDENTIFIER_TWI == pstr_manu->u16_company_identifier) )
		{
			tstr_twi_manu_data_mode_2_info* pstr_twi_beacon;
			pstr_twi_beacon =(tstr_twi_manu_data_mode_2_info*)pstr_manu->pu8_manu_data;

			pstr_twi_beacon->u8_adv_count = u8_adv_count;		/** Advertising count **/
		}
		else
		{
			s32_result = TWI_ERROR_INVALID_ARGUMENTS;
		}
	}
	else
	{
		s32_result = TWI_ERROR_INVALID_ARGUMENTS;
	}
#endif
#endif
	return s32_result;
}

