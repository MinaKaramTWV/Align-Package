/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_hal_sys_init.c
*   @brief      This file initializes TWI software stack over the BLE chip.
*/

#ifndef _TWI_HAL_SYS_INIT_H_
#define _TWI_HAL_SYS_INIT_H_
/**
*   @defgroup hal_sys_init_group TWI HAL system initialization
*   This is the definition of TWI HAL system initialization.
*   @{
*/

/*----------------------------------------------------------*/
/*- INCLUDES -----------------------------------------------*/
/*----------------------------------------------------------*/

#include "twi_common.h"
#include "platform_defines.h"

/*----------------------------------------------------------*/
/*- MACROS -------------------------------------------------*/
/*----------------------------------------------------------*/


/*----------------------------------------------------------*/
/*- CONSTANTS ----------------------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/
/*----------------------------------------------------------*/

/**
*   @brief      This function initializes the HAL of the system.
*   @return     ::TWI_SUCCESS, ::TWI_ERROR_INVALID_ARGUMENTS, ::TWI_ERROR_NOT_INITIALIZED.
*/
twi_s32 twi_hal_sys_init(void);

/**
*   @brief      This function de-initializes the HAL of the system.
*   @return     ::TWI_SUCCESS, ::TWI_ERROR_INVALID_ARGUMENTS, ::TWI_ERROR_NOT_INITIALIZED.
*/
twi_s32 twi_hal_sys_deinit(void);

/** @} */   /*hal_sys_init_group*/

#endif  /*_TWI_HAL_SYS_INIT_H_*/
