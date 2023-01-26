/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file		twi_ble_adv_scan.h
 *	@brief		This file holds the declarations and definitions for parsing and composing for the BLE advertising packet formats.
 *	@author		Abdulla Murad
 */

#ifndef __TWI_BLE_ADV_SCAN__
#define __TWI_BLE_ADV_SCAN__

/*-*********************************************************/
/*- INCLUDES ----------------------------------------------*/
/*-*********************************************************/

#include "twi_types.h"
#include "twi_retval.h"
#include "twi_ble_company_ids.h"
#include "twi_profile_ids.h"
/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------------*/
/*-*********************************************************/
#define TWI_BLE_ADV_DEVICE_FOUND	(TWI_ERR_BLE_ADV_SCAN_BASE - 1)
#define TWI_BLE_ADV_INVALID_DEVICE	(TWI_ERR_BLE_ADV_SCAN_BASE - 2)

#define TWI_MAX_ADV_DATA_LEN 		(31)
#define TWI_ID_SIZE									(4)
/*-*********************************************************/
/*- FUNCTIONS PROTOTYPES ----------------------------------*/
/*-*********************************************************/
typedef struct _tstr_ble_adv_scan_evt tstr_ble_adv_scan_evt;

typedef twi_s32 (*tpf_ble_adv_scan_cb)(tstr_ble_adv_scan_evt * pstr_ble_evt_scan, twi_u8 const * const pu8_payload, twi_u8 u8_len , twi_bool b_scan_rsp);

/*-*********************************************************/
/*- STRUCTS, UNIONS, and ENUMS ----------------------------*/
/*-*********************************************************/
typedef enum
{
	FLAGS = 0x01,
	INCOMPLETE_LIST_16_BIT_SERVICE_CLASS_UUIDS = 0x02,
	COMPLETE_LIST_16_BIT_SERVICE_CLASS_UUIDS = 0x03,
	INCOMPLETE_LIST_32_BIT_SERVICE_CLASS_UUIDS = 0x04,
	COMPLETE_LIST_32_BIT_SERVICE_CLASS_UUIDS = 0x05,
	INCOMPLETE_LIST_128_BIT_SERVICE_CLASS_UUIDS = 0x06,
	COMPLETE_LIST_128_BIT_SERVICE_CLASS_UUIDS = 0x07,
	SHORTENED_LOCAL_NAME = 0x08,
	COMPLETE_LOCAL_NAME = 0x09,
	TX_POWER_LEVEL = 0x0A,
	SERVICE_DATA_16_BIT_UUID = 0x16,
	SERVICE_DATA_32_BIT_UUID = 0x20,
	SERVICE_DATA_128_BIT_UUID = 0x21,
	MANUFACTURE_SPECIFIC_DATA = 0xFF,
}tenu_ad_types_t;

struct _tstr_ble_adv_scan_evt
{
	tenu_ad_types_t enu_ble_adv_scan_type;
	tenu_manfact_spefic_comp_id enu_manfact_spefic_comp_id;
};

typedef struct
{
	twi_u8 u8_len;
	tenu_ad_types_t enu_ble_adv_scan_type;
	tenu_manfact_spefic_comp_id enu_manfact_spefic_comp_id;
	twi_u8 const * pu8_ad_data;
}tstr_ad_element_t;

typedef struct
{
	tstr_ad_element_t * pstr_ad_element;
	twi_u8 u8_num_of_elements;
	tpf_ble_adv_scan_cb pf_ble_adv_scan_cb;
}tstr_ble_adv_scan_t;


/*-*********************************************************/
/*- APIs DECLARATIONS -------------------------------------*/
/*-*********************************************************/

/**
 *	@brief			This function used for validate the advertising or scanning Context.
 *	@param[in]		pstr_ble_adv_scan	pointer to structure holds the advertising\scanning context information.
 *	@return			::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 *	@author			Abdulla Murad
 */
twi_s32 twi_ble_adv_scan_init(tstr_ble_adv_scan_t * const pstr_ble_adv_scan);

/**
 *	@brief			This function used for parsing the advertising packet and notifying the calling layer with every type from the advertising packet.
 *	@param[in]		pstr_ble_adv_scan	pointer to structure holds the advertising\scanning context information.
 *	@param[in]		pu8_payload			pointer to array holds the advertising packet need to be parsed.
 *	@param[in]		u8_len				length of the advertising packet.
 *  @param[in]		b_scan_rsp			boolean to indicate the type of the packet (adv/scan response)
 *	@return			::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 *	@author			Abdulla Murad
 */
twi_s32 twi_ble_scan_notify(tstr_ble_adv_scan_t * const pstr_ble_adv_scan, 
									twi_u8 const * const pu8_payload, twi_u8 u8_len , twi_bool b_scan_rsp);

/**
 *	@brief			This function used for composing the advertising packet as BLE Air Format.
 *	@param[in]		pstr_ble_adv_scan	pointer to structure holds the advertising\scanning context information.
 *	@param[out]		pu8_payload			pointer to array should be filled with the formated advertising packet.
 *	@param[in]		u8_max_len			The Max length of the advertising packet buffer (Should be ::TWI_MAX_ADV_DATA_LEN).
 *	@param[out]		pu8_len				The output length of the formated advertising packet.
 *	@return			::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 *	@author			Abdulla Murad
 */
twi_s32 twi_ble_adv_compile(tstr_ble_adv_scan_t * const pstr_ble_adv_scan, twi_u8 * const pu8_payload, twi_u8 u8_max_len, twi_u8* pu8_len);

#endif /* __TWI_BLE_ADV_SCAN__ */
