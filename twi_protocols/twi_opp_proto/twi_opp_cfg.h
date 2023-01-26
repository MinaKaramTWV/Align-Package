/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
 *	@file		twi_opp_cfg.h
 *	@brief		This file holds the configuration parameters of the opportunistic protocol.
 */

#ifndef TWI_OPP_CFG_H_
#define TWI_OPP_CFG_H_

/*-*********************************************************/
/*- INCLUDES ----------------------------------------------*/
/*-*********************************************************/

#include "ibeacon_uuids.h"


/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------------*/
/*-*********************************************************/
#define OPP_UUID_SIZE						UUID128_SIZE
#define APP_SCAN_RES_MAX_LEN				(TWI_BLE_SCAN_RESP_MAX_LEN - (BEACON_SCAN_RES_LENGTH << 1))

#define OPP_NDS_DEFAULT_IDX					0

#define OPP_DEFUALT_BASIC_STATES_TIMEOUT	30					/**< @brief  Basic beacons (DS/AS) will be advertised for only 30 seconds */
#define OPP_DEFUALT_TEMP_STATES_TIMEOUT		300				    /**< @brief  Temp beacons (DST/AST) will be advertised for 5 minutes */

#ifndef OPP_NUDGE_UUID_CNT
	#define	OPP_NUDGE_UUID_CNT 	0								/**< This is the number of nudging UUIDs.*/
#endif

#ifdef ADV_PKT_COUNTER_ENABLED
#define OPP_DEFUALT_ADV_PKT_COUNT_TIMEOUT	(120000) /* 2 minutes */
#endif

#define TWI_ADV_MODE_1						1
#define TWI_ADV_MODE_2						2
#define TWI_ADV_MODE_BOTH					3

#ifndef TWI_ADV_MODE
	#define	TWI_ADV_MODE TWI_ADV_MODE_1
#endif

#ifndef NUM_OF_TAGS
	#define	NUM_OF_TAGS 	0
#endif

#ifndef TWI_ADVERTISING_MODE_DEFAULT
	#define	TWI_ADVERTISING_MODE_DEFAULT 	TWI_ADV_MODE_1
#endif

#define FIXED_PART_128_UUID					0x73, 0xEA, 0x48, 0x39, \
											0xC5, 0x3D, 0x92, 0x1F,0xCE, 	/**< @brief	fixed part 128 uuids*/

/*-**********************************************************/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*-**********************************************************/
typedef struct
{
	twi_u8 		au8_apple_uuid[OPP_UUID_SIZE];			/**< @brief  Apple Beacon UUID */
	twi_u8 		u8_twi_adv_typ_msb;						/**< @brief  advertise type for twi beacon MSB */
	twi_u8 		u8_twi_adv_typ_lsb;						/**< @brief  advertise type for twi beacon LSB */
	twi_u16 	u16_service_id;							/**< @brief  The service ID, this info is put into scan response */
} tstr_twi_opp_uuid_and_service;

#endif /* TWI_OPP_CFG_H_ */
