/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*  @file	twi_nvds_tags.h
*  @brief	This file contains tlv security flash tags needed to be saved.
*/

#ifndef _TWI_NVDS_TAGS_H_
#define _TWI_NVDS_TAGS_H_

/** @defgroup _TWI_NVDS_TAGS_group TWI security flash tags.
 * This file contains tlv security flash tags needed to be saved.
 * @{
 */
/*-***********************************************************/
/*- INCLUDES ------------------------------------------------*/
/*-***********************************************************/

#include "twi_types.h"
#include "twi_retval.h"
#include "twi_nvds_conf.h"


/*-*********************************************************/
/*- ENUMS -------------------------------------------------*/
/*-*********************************************************/

/*-*********************************************************/
/*- PRIMITIVE TYPES ---------------------------------------*/
/*-*********************************************************/
/*lint -save -e488*/
typedef enum
{
	TWI_NVDS_START,
	TWI_NVDS_SEQ_NUM_ID,       /**< @brief Session establishment sequence number data ID. */
	TWI_NVDS_LTK_ID,           /**< @brief Security LTK data ID. */
	TWI_NVDS_PEER_CERT_FIRST_CNTXT,  /**< @brief Security Certificate data ID. */
	TWI_NVDS_PEER_CERT_LAST_CNTXT = TWI_NVDS_PEER_CERT_FIRST_CNTXT + TWI_NVDS_MAX_CNTXT_CNT - 1,
	TWI_NVDS_MY_PUBLIC,
	TWI_NVDS_MY_NONCE,
	TWI_NVDS_PEER_PUBLIC,
	TWI_NVDS_PEER_NONCE,
	TWI_NVDS_PRIVATE_KEY,
	TWI_NVDS_SHARED_KEY,
	TWI_NVDS_LTK,
	TWI_NVDS_MY_PUBLIC_DASH,
	TWI_NVDS_PEER_PUBLIC_DASH,
	TWI_NVDS_CONTROLLER_ID,
	TWI_NVDS_FIRMWARE_ID,
	TWI_NVDS_PASSWORD,
	TWI_NVDS_ENCRYPTED_PASSWORD,
	TWI_NVDS_PASSWORD_ENCRYPT_KEY,
	TWI_NVDS_wN,
	TWI_NVDS_KCONF,
	TWI_NVDS_MACKEY,
	TWI_NVDS_PAIR_DATA_CNT,
    TWI_NVDS_SDK_DATA,
    TWI_NVDS_COUNTERFEIT_DATA,
	TWI_NVDS_PEER_TWI_ID,
	TWI_NVDS_INVALID_ID   /**< @brief Invalid data ID. */
}tenu_tlv_nvds_tag;
/*lint -restore*/
/*-*********************************************************/
/*- STRUCTS AND UNIONS ------------------------------------*/
/*-*********************************************************/



/** @}*/
#endif		/* _TWI_NVDS_TAGS_H_ */
