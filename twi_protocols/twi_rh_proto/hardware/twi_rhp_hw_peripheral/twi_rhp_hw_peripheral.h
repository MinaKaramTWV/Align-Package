/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file					twi_rhp_hw_peripheral.h
 ** @brief					This file includes the interface for the hardware with Remote HAL Protocol
 */

#ifndef TWI_RHP_HW_PERIPHERAL_H_
#define TWI_RHP_HW_PERIPHERAL_H_

//***********************************************************
/*- INCLUDES -----------------------------------------------*/
//***********************************************************
#ifdef TWI_RHP_HW_BLE
	#include "twi_rhp_hw_ble_handlers.h"
#endif

#ifdef TWI_RHP_HW_WIFI
	#include "twi_rhp_hw_wifi_handlers.h"
#endif

#ifdef TWI_RHP_HW_NFC
	#include "twi_rhp_hw_nfc_handlers.h"
#endif
#ifdef TWI_RHP_HW_NFC_READER
#include "twi_rhp_hw_nfc_reader_handler.h"
#endif
//***********************************************************
/*- CONSTANTS ----------------------------------------------*/
//***********************************************************

/*-***********************************************************/
/*- STRUCTS AND UNIONS --------------------------------------*/
/*-***********************************************************/

/*-***********************************************************/
/*- FUNCTIONS' PROTOTYPES -----------------------------------*/
/*-***********************************************************/

void twi_rhp_hw_peripheral_dispatch(void);

#endif /* TWI_RHP_HW_PERIPHERAL_H_ */
