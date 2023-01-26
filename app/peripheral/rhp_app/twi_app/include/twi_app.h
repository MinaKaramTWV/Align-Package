/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file			twi_app.h
 ** @brief			This file is the header file of application layer APIs.
 **
 */
#ifndef TWI_APP_H__
#define TWI_APP_H__
/**
*   @defgroup app_group TWI APP
*   This is the definition of TWI APP.
*   @{
*/

/*-***********************************************************/
/*- INCLUDES ------------------------------------------------*/
/*-***********************************************************/

#include "twi_types.h"

/*-***********************************************************/
/*- LOCAL MACROS --------------------------------------------*/
/*-***********************************************************/

/**
*   @defgroup twi_app_retval_group Application layer return values
*   @{
*/
#define TWI_APP_SUCCESS		      	            (TWI_SUCCESS)
#define TWI_APP_UNINITIALIZED_MODULE      		(TWI_ERROR_APP_BASE - 1)
#define TWI_APP_INVALID_INPUT_PARAM        		(TWI_ERROR_APP_BASE - 2)
#define TWI_APP_UNINITALIZED_CALL_BACK        	(TWI_ERROR_APP_BASE - 3)
#define TWI_APP_RCI_IS_UNINITIALIZED	    	(TWI_ERROR_APP_BASE - 4)
#define TWI_APP_RCI_UNDEFINED_COMP_MSG_TYPE    	(TWI_ERROR_APP_BASE - 5)
#define TWI_APP_RCI_CMDS_INVALID_INPUT_PARAM	(TWI_ERROR_APP_BASE - 6)
#define TWI_APP_RCI_CMDS_BATTERY_READING_ERROR 	(TWI_ERROR_APP_BASE - 7)
#define TWI_APP_CONN_INVALID_INPUT_PARAM		(TWI_ERROR_APP_BASE - 8)
#define TWI_APP_CONN_MNGR_UNINITIALIZED	    	(TWI_ERROR_APP_BASE - 9)
#define TWI_APP_RCI_CMDS_ERR_STR_2_INT_CONV 	(TWI_ERROR_APP_BASE - 10)
/** @} */


/*-*********************************************************/
/*- FUNCTION DECLARATIONS ---------------------------------*/
/*-*********************************************************/

/**
 *	@function		void twi_app_init(void)
 *	@brief			This function is used for initializing the whole APP.
 *  @return     	::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_app_init(void);

/**
 *	@function		void twi_app_deinit(void)
 *	@brief			This function is used for de-initializing the whole APP.
 *  @return		void.
*/
void twi_app_deinit(void);

/**
 *	@function		void twi_app_dispatch(void)
*/
void twi_app_dispatch(void);

/** @} */   /*app_group*/

#endif  /* twi_app.h */
