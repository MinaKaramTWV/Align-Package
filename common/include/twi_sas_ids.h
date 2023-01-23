/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_sas_ids.h
*   @brief      This file contains TWI SAS ID different definitions.
*/

#ifndef _TWI_SAS_IDS_H_
#define _TWI_SAS_IDS_H_

#include "twi_common.h"

/** @defgroup TWI_SAS_IDS_group TWI SAS IDs Definitions.
* @{
*/

#define TWI_ID_SIZE									(4)

#define TWI_OLD_ALERT_STATUS_SERVER_ID				{0x00, 0x00, 0x00, 0x00}
#define TWI_OLD_TEMP_LOGGER_SERVER_ID				{0x00, 0x00, 0x00, 0x00}
#define TWI_SOAP_LOGGER_SERVER_ID					{0x00, 0x00, 0x00, 0x01}
#define TWI_LIGHT_LOGGER_SERVER_ID					{0x00, 0x00, 0x00, 0x02}
#define TWI_SHIPPING_TILT_ANGLE_LOGGER_SERVER_ID	{0x00, 0x00, 0x00, 0x03}
#define TWI_SHIPPING_ACC_NOTIFY_LOGGER_SERVER_ID	{0x00, 0x00, 0x00, 0x04}
#define TWI_SHIPPING_HUM_LOGGER_SERVER_ID			{0x00, 0x00, 0x00, 0x05}
#define TWI_SHIPPING_PRESS_LOGGER_SERVER_ID			{0x00, 0x00, 0x00, 0x06}
#define TWI_SHIPPING_TEMP_LOGGER_SERVER_ID			{0x00, 0x00, 0x00, 0x07}
#define TWI_SHIPPING_ALERT_STATUS_SERVER_ID			{0x00, 0x00, 0x00, 0x08}
#define TWI_SHIPPING_BAT_LOGGER_SERVER_ID			{0x00, 0x00, 0x00, 0x09}
#define TWI_SHIPPING_LIGHT_LOGGER_SERVER_ID			{0x00, 0x00, 0x00, 0x0A}
#define TWI_INSULET_NOTIFY_LOGGER_SERVER_ID			{0x00, 0x00, 0x00, 0x0B}
#define TWI_EDWARDS_ALARMS_LOGGER_SERVER_ID			{0x00, 0x00, 0x00, 0x0C}
#define TWI_UTC_SERVER_ID							{0x00, 0x00, 0x00, 0x0D}
#define TWI_CGM_EGV_LOGGER_SERVER_ID				{0x00, 0x00, 0x00, 0x0E}
#define TWI_LABOR_TRACKING_LOGGER_SERVER_ID			{0x00, 0x00, 0x00, 0x0F}
#define TWI_ROCHE_STATUS_DATA_SERVER_ID				{0x00, 0x00, 0x00, 0x10}
#define TWI_GLAS_LOGGER_SERVER_ID					{0x00, 0x00, 0x00, 0x11}
#define TWI_ALIGN_TAG_SERVER_ID						{0x00, 0x00, 0x00, 0x12}

#define INVALID_TWI_ID_BYTE							0xFF
#define INVALID_TWI_ID								{						\
														INVALID_TWI_ID_BYTE,\
														INVALID_TWI_ID_BYTE,\
														INVALID_TWI_ID_BYTE,\
														INVALID_TWI_ID_BYTE	\
													}
/** @} */

#endif  /*_TWI_SAS_IDS_H_*/
