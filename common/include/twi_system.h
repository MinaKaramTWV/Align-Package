/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file		twi_system.h
 *	@brief		This file includes the macros/fns that can be used in the whole system for system purpuses.
 */

 /** @defgroup TWI_SYSTEM_group TWI System Common Functions
 * @{
 */
 
#ifndef __TWI_SYSTEM_H__
#define __TWI_SYSTEM_H__

/*-*********************************************************/
/*- INCLUDES ----------------------------------------------*/
/*-*********************************************************/ 

/*-*********************************************************/
/*- FUNCTION-LIKE MACROS ----------------------------------*/
/*-*********************************************************/



/*-*********************************************************/
/*- FUNCTION DECLARATIONS ---------------------------------*/
/*-*********************************************************/\

/**
 *  @function	void twi_system_sleep_mode_forbiden(twi_bool b_forbid)
 *  @brief		This function is used to Increment/Decrement a Sleep Mode counter to prevent the Sleep Mode operation Based on the input argument.
 *	@param[in]	b_forbid Define if the Caller need to forbid going to the sleep Mode or not
 */
void twi_system_sleep_mode_forbiden(twi_bool b_forbid);

/**
 *	@function	twi_bool twi_system_is_sleep_forbiden(void)
 *	@brief		Return the Sleep Mode Forbiden Status
 *	@return		::TWI_FALSE in case of system is forbiden go to Sleep, ::TWI_TRUE once the System is ready going to Sleep Mode.
 */
twi_bool twi_system_is_sleep_forbiden(void);


/** @} */ /* TWI_SYSTEM_group s*/
#endif // __TWI_SYSTEM_H__
