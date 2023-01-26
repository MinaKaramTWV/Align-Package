/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file		twi_ble_aml.h
 ** @brief      This file implements advertising mangment version 2 Header File.
 */
#ifndef __TWI_BLE_AML__
#define __TWI_BLE_AML__
/***********************************************************/
/*- INCLUDES ----------------------------------------------*/
/***********************************************************/
#include "twi_common.h"
#include "twi_retval.h"
#include "twi_profile_ids.h"

/*-***********************************************************/
/*- Global MACROS --------------------------------------------*/
/*-***********************************************************/
#define TWI_ID_SIZE                                         (4)
#define FIXED_PART_128_UUID_SIZE                            (9)
#define FIXED_PART_128_UUID					0x73, 0xEA, 0x48, 0x39, \
											0xC5, 0x3D, 0x92, 0x1F,0xCE, 	/**< @brief	fixed part 128 uuids**/
#define MAX_AVA_MANU_DATA_SZ								(4)
/*-***********************************************************/
/*- ENUMERATIONS --------------------------------------------*/
/*-***********************************************************/


/*-**********************************************************/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*-**********************************************************/
typedef twi_s32 (*tpf_aml_cb)(twi_u8 *, twi_u16);

TWI_PACK(typedef struct
{
	twi_u8			u8_dstn_stats_brief;								/**<@brief brief of destination status*/
	twi_u8  		au8_twi_id[TWI_ID_SIZE];
	twi_u16			u16_profile_id;										/**<@brief product profile id. */
	twi_u8			au8_fixed_part_128_uuid[FIXED_PART_128_UUID_SIZE];	/**<@brief fixed part in 128 UUIDs*/
})tstr_twi_srvc_128_data_mode_2_info;

TWI_PACK(typedef struct
{
	twi_u8 				u8_rcvd;
	twi_u8 				u8_adv_count;
	twi_u8 				au8_manu_data[MAX_AVA_MANU_DATA_SZ];
})tstr_twi_manu_data_mode_2_info;

/**
 *	@struct	tstr_twi_aml_in
 *	@brief	structure that is used to initialize the module.
 */
typedef struct
{
	/** @brief profile id from RHP layer*/
	twi_u16 u16_profile_id;
	/** @brief manufacturer data to be advertised (max available 4 bytes)*/
	twi_u8 au8_manu_data[MAX_AVA_MANU_DATA_SZ];
	/** @brief This call back function that carry the advertise data*/
	tpf_aml_cb pf_aml_cb;
}tstr_twi_aml_in;
/*-***********************************************************/
/*- FUNCTIONS' PROTOTYPES -----------------------------------*/
/*-***********************************************************/
/**
 * @function		twi_aml_init;
 * @brief      		This function initialize the ble aml module.
 * @param[in]  		pstr_twi_aml_in: pointer to the structure that is used to initialize the module.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_aml_init(tstr_twi_aml_in* pstr_twi_aml_in);
#ifdef ADV_PKT_COUNTER_ENABLED
/**
 * @function		twi_aml_set_adv_pkt_count_time;
 * @brief      		This function update advertising packet count field.
 * @param[in]  		u32_adv_pkt_count_timeout:	the time of updating adv packet.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_aml_set_adv_pkt_count_time(twi_u32 u32_adv_pkt_count_timeout);

/**
 * @function		twi_aml_reset_adv_pkt_count_time;
 * @brief      		This function reset advertising packet timer.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_aml_reset_adv_pkt_count_time(void);

/**
 * @function		twi_aml_stop_adv_pkt_count_timer(void)
 * @brief      		This function to stop advertising packet timer.
 */
void twi_aml_stop_adv_pkt_count_timer(void);
#endif

/*
 * @function		twi_aml_change_device_serial
 * @brief      		This function changes the device serial, TWI_ID
 * @param[in]  		pu8_dvc_serial       The New Device Serial.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_aml_change_device_serial(twi_u8 * pu8_dvc_serial);

/*
 * @function		twi_aml_get_device_serial
 * @brief      		This function gets the device serial, TWI_ID
 * @param[in]  		pu8_dvc_serial_buff       The Buffer that the Device Serial will be copied in.
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_aml_get_device_serial(twi_u8 * pu8_dvc_serial_buff);

/*
 * @function		twi_aml_change_dst_status
 * @brief			This function is used to advertise new dst_statu.
 * @param[in]		u8_dst_idx: Index of the destination that generates that event.
 * @param[in]		u8_dst_status: u8_dst_status value
 * @return     		::TWI_SUCCESS in case of success, otherwise, @ref twi_retval.h.
 */
twi_s32 twi_aml_change_dst_status(twi_u8 u8_dst_idx ,twi_u8 u8_dst_status);


/*
 * @function		void   twi_aml_dispatch(void)
 * @brief			Dispatch function of TWI aml module.
 */
void twi_aml_dispatch(void);


#endif /*__TWI_BLE_AML__*/
