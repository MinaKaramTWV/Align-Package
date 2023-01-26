/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file		twi_conn_param_mgmt_default_priorities.h
*   @brief		This layer is responsible of set default priorities for the layers using connection parameters.
*   @details	Connection paramter mgmt layer takes priorties in set connection parameter.
*				No layer can update connection parameters if there is another layer has a higher priority.
*/
#ifndef _TWI_CONN_PARAM_MGMT_DEFAULT_PRIORITIES_H_
#define _TWI_CONN_PARAM_MGMT_DEFAULT_PRIORITIES_H_
/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/

/** @todo if you want to release the priority from a layer, you have to track all layer if it has requested updating connection parameters **/
/** For now, it tracks the highest prioity only and no one can release it. **/

#define TWI_CONN_PARAM_LOWEST_PRIORITY						(0x00)										/** @brief: Lowest priorty**/
#define TWI_CONN_PARAM_HIGHEST_PRIORITY						(0xFF)										/** @brief: Highest priorty**/


#ifndef TWI_CONN_PARAM_APPLICATION_PRIORITY
	#define TWI_CONN_PARAM_APPLICATION_PRIORITY				(TWI_CONN_PARAM_HIGHEST_PRIORITY)			/** @brief: application layer like app_conn has a highest priorty **/
#endif

#ifndef TWI_CONN_PARAM_TP_PRIORITY
	#define TWI_CONN_PARAM_TP_PRIORITY						(TWI_CONN_PARAM_HIGHEST_PRIORITY - 1)		/** @brief: TP has a 2nd priorty **/
#endif


#endif /*_TWI_CONN_PARAM_MGMT_DEFAULT_PRIORITIES_H_*/

