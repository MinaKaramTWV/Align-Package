/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_destinations.h
*   @brief      This file contains TWI Destinations definitions.
*/

#ifndef _TWI_DESTINATIONS_H_
#define _TWI_DESTINATIONS_H_

#include "twi_common.h"

/** @defgroup TWI_DESTINATIONS_group TWI Destinations Definitions.
* @{
*/
#ifndef OUTPUT_DESTS_NUM
#define OUTPUT_DESTS_NUM 												2
#endif

#define CLOUD_DEST_IDX 													0
#define OUTPUT_DEST1_IDX 												1
#define INVALID_OUTPUT_DEST_IDX 										255

#define OUTPUT_CLOUD_DEST 												0x01
#define OUTPUT_DEST1 													0x02
#define INVALID_OUTPUT_DEST 											0x00

#if (OUTPUT_DESTS_NUM == 1)
	#define MAP_DEST(u8_dest)                     						(0)
#elif(OUTPUT_DESTS_NUM > 1)
	#define MAP_DEST(u8_dest)                     						(u8_dest)
#else
	#ERROR "Invalid Num of destinations"
#endif
/** @} */

#endif  /*_TWI_DESTINATIONS_H_*/
