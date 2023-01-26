/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file			twi_app_buff_confg.h
 ** @brief			This file contain the configuration of the sending buffer.
 **
 */
#ifndef TWI_APP_BUFF_CONFG_H__
#define TWI_APP_BUFF_CONFG_H__


/*-***********************************************************/
/*- LOCAL MACROS --------------------------------------------*/
/*-***********************************************************/

/**
* @brief The RHP status buffer length.
*/

/* TODO: This define must be adjusted after adjusting the sending operation between NFC and BLE chips */	
#if defined ULP_SYSTEM_LOGGER	
#define TWI_APP_RHP_DATA_BUF_LEN		(2560)	
#elif  defined TWI_NFC_GW_PROJECT   	
#define TWI_APP_RHP_DATA_BUF_LEN 		(512)	
#elif defined BLE_ALIGN_TAG         
#define TWI_APP_RHP_DATA_BUF_LEN 		(1150)	    
#else	
#define TWI_APP_RHP_DATA_BUF_LEN		(320)	
#endif


#endif  /* twi_app_buff_confg.h */
