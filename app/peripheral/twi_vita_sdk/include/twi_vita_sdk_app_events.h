/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file					twi_vita_sdk_app_events.h
 ** @brief      			This file Contains configuration macros for the application layers requests from TWI VITA SDK.
 */

#ifndef TWI_VITA_SDK_APP_EVENTS_H_
#define TWI_VITA_SDK_APP_EVENTS_H_

/***********************************************************/
/*- INCLUDES ----------------------------------------------*/
/***********************************************************/

/*-***********************************************************/
/*- Global MACROS --------------------------------------------*/
/*-***********************************************************/

#define RHP_SEND_STATUS_DATA                0
#define RHP_SEND_ALERT_DATA                 1
#define RHP_SEND_NO_DATA                    2
#define RHP_RQST_LOCK_STATUS                3

#define TWI_SDK_REQ_0					    RHP_SEND_STATUS_DATA
#define TWI_SDK_REQ_1					    RHP_SEND_ALERT_DATA
#define TWI_SDK_REQ_2					    RHP_SEND_NO_DATA
#define TWI_SDK_REQ_3					    RHP_RQST_LOCK_STATUS

/*-**********************************************************/
/*- GLOBAL EXTERN VARIABLES --------------------------------*/
/*-**********************************************************/

/*-***********************************************************/
/*- STRUCTS AND UNIONS --------------------------------------*/
/*-***********************************************************/

/*-***********************************************************/
/*- FUNCTIONS' PROTOTYPES -----------------------------------*/
/*-***********************************************************/

#endif /* TWI_VITA_SDK_APP_EVENTS_H_ */

