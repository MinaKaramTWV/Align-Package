/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file					twi_app_conn_common.h
 ** @brief					This file holds the common defines or structures used in the App layers.
 **
 */

#ifndef TWI_APP_CONN_COMMON_H_
#define TWI_APP_CONN_COMMON_H_

/*-*********************************************************/
/*- INCLUDES ----------------------------------------------*/
/*-*********************************************************/

#include "twi_types.h"
#include "twi_sas_ids.h"

/*-***********************************************************/
/*- LOCAL MACROS --------------------------------------------*/
/*-***********************************************************/


/*-***********************************************************/
/*- ENUMS ---------------------------------------------------*/
/*-***********************************************************/



/*-*********************************************************/
/*- STRUCTS AND UNIONS ------------------------------------*/
/*-*********************************************************/

/**
 * @brief structure holds device configuration
 */
typedef struct
{
	twi_bool						b_sending;
	twi_u16							u16_app_id;
	void(*pf_send_complete)(twi_bool b_success);
} tstr_twi_device_config;

/**
 *	@struct		tstr_twi_cnncted_dvc_info
 *	@brief		structure to represent the information of the peer device.
 */
TWI_PACK(typedef struct
{
	/** @brief Supported destinations with the peer device. */
	twi_u8 			u8_dest_idx;
	/** @brief Peer's TWI-ID */
	twi_u8	au8_twi_id[TWI_ID_SIZE];
})tstr_twi_cnncted_dvc_info;

#endif /* TWI_APP_CONN_COMMON_H_ */
