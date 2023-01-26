/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file		twi_rhp_value.h
 *	@brief		This file implements the RHP value operations header file.
 */
#ifndef _TWI_RHP_VALUE_H_
#define _TWI_RHP_VALUE_H_
/**
*   @defgroup value_group RHP VALUE
*   This is the definition of RHP VALUE.
*   @{
*/

#include "twi_rhp_types.h"

/**
 * @function		twi_bool twi_rhp_value_is_equal_to(const tstr_twi_rhp_value * pstr_left_val, const tstr_twi_rhp_value * pstr_right_val)
 * @brief			This function checks if two RHP values are equal.
 * @param[in]		pstr_left_val: pointer to one of the compare values
 * @param[in]		pstr_right_val: pointer to the other value
 * @return			twi_bool: TWI_TRUE if comparison is true. TWI_FALSE otherwise
 */
twi_bool twi_rhp_value_is_equal_to(const tstr_twi_rhp_value * pstr_left_val, const tstr_twi_rhp_value * pstr_right_val);

/**
 * @function		twi_bool twi_rhp_value_is_not_equal_to(const tstr_twi_rhp_value * pstr_left_val, const tstr_twi_rhp_value * pstr_right_val)
 * @brief			This function checks if two RHP values are not equal.
 * @param[in]		pstr_left_val: pointer to one of the compare values
 * @param[in]		pstr_right_val: pointer to the other value
 * @return			twi_bool: TWI_TRUE if comparison is true. TWI_FALSE otherwise
 */
twi_bool twi_rhp_value_is_not_equal_to(const tstr_twi_rhp_value * pstr_left_val, const tstr_twi_rhp_value * pstr_right_val);

/**
 * @function		twi_bool twi_rhp_value_is_greater_than(const tstr_twi_rhp_value * pstr_left_val, const tstr_twi_rhp_value * pstr_right_val)
 * @brief			This function checks if left RHP Value is greater than the right RHP value.
 * @param[in]		pstr_left_val: pointer to one of the compare values
 * @param[in]		pstr_right_val: pointer to the other value
 * @return			twi_bool: TWI_TRUE if comparison is true. TWI_FALSE otherwise
 */
twi_bool twi_rhp_value_is_greater_than(const tstr_twi_rhp_value * pstr_left_val, const tstr_twi_rhp_value * pstr_right_val);

/**
 * @function		twi_u16 twi_rhp_value_get_size(const tstr_twi_rhp_value * pstr_val)
 * @brief			This function gets the size of data from RHP value structure.
 * @param[in]		pstr_val: pointer to value
 * @return			the value size in u16
 */
twi_u16  twi_rhp_value_get_size(const tstr_twi_rhp_value * pstr_val);

/**
 * @function		twi_bool twi_rhp_value_is_greater_than_or_equal_to(const tstr_twi_rhp_value * pstr_left_val, const tstr_twi_rhp_value * pstr_right_val)
 * @brief			This function checks if left RHP Value is greater than or equal the right RHP value.
 * @param[in]		pstr_left_val: pointer to one of the compare values
 * @param[in]		pstr_right_val: pointer to the other value
 * @return			twi_bool: TWI_TRUE if comparison is true. TWI_FALSE otherwise
 */
twi_bool twi_rhp_value_is_greater_than_or_equal_to(const tstr_twi_rhp_value * pstr_left_val, const tstr_twi_rhp_value * pstr_right_val);

/**
 * @function		twi_bool twi_rhp_value_is_less_than(const tstr_twi_rhp_value * pstr_left_val, const tstr_twi_rhp_value * pstr_right_val)
 * @brief			This function checks if left RHP Value is less than the right RHP value.
 * @param[in]		pstr_left_val: pointer to one of the compare values
 * @param[in]		pstr_right_val: pointer to the other value
 * @return			twi_bool: TWI_TRUE if comparison is true. TWI_FALSE otherwise
 */
twi_bool twi_rhp_value_is_less_than(const tstr_twi_rhp_value * pstr_left_val, const tstr_twi_rhp_value * pstr_right_val);

/**
 * @function		twi_bool twi_rhp_value_is_less_than_or_equal_to(const tstr_twi_rhp_value * pstr_left_val, const tstr_twi_rhp_value * pstr_right_val)
 * @brief			This function checks if left RHP Value is less than or equal the right RHP value.
 * @param[in]		pstr_left_val: pointer to one of the compare values
 * @param[in]		pstr_right_val: pointer to the other value
 * @return			twi_bool: TWI_TRUE if comparison is true. TWI_FALSE otherwise
 */
twi_bool twi_rhp_value_is_less_than_or_equal_to(const tstr_twi_rhp_value * pstr_left_val, const tstr_twi_rhp_value * pstr_right_val);

/**
 * @function		twi_s16 twi_rhp_value_to_string(twi_const tstr_twi_rhp_value * pstr_value, twi_u8 * pu8_str, twi_u16 u16_len)
 * @brief			This function converts value to its string representation.
 * @param[in]		pstr_value: pointer to the value
 * @param[in]		pu8_str: pointer to the string buffer to fill up
 * @param[in]		u16_len: length of the available string buffer
 * 					This length is not checked and should be sufficiently large
 * @return 			twi_s16: length of the string buffer which is actually used. in case of error it returns -1.
 */
twi_s16 twi_rhp_value_to_string(twi_const tstr_twi_rhp_value * pstr_value, twi_u8 * pu8_str, twi_u16 u16_len);

/**
 * @function		twi_rhp_copy_value(tstr_twi_rhp_value * pstr_to_value, const tstr_twi_rhp_value * pstr_from_value)
 * @brief			This function copies RHP value to another RHP value structure.
 * @param[in]		pstr_attr: pointer to the value to copy to
 * @param[in]		new_value: pointer to the value to copy from
 */
void twi_rhp_copy_value(tstr_twi_rhp_value * pstr_to_value, const tstr_twi_rhp_value * pstr_from_value);

/**
 * @function		twi_s32 twi_rhp_string_to_value(twi_u8* pu8_str, twi_u16 u16_len, tenu_value_type enu_type,tstr_twi_rhp_value* pstr_value)
 * @brief			This function converts a string to a value
 * @param[in]		pu8_str: pointer to the string
 * @param[in]		u16_len: length of the string
 * @param[in]		u8_type: type of the RHP value want the string to convert to
 * @param[in]		pstr_value: pointer to the value to set
 * @return 			twi_s32: length of the string parsed. -1 if invalid value.
 */
twi_s32 twi_rhp_string_to_value(twi_u8* pu8_str, twi_u16 u16_len, tenu_value_type enu_type,
		tstr_twi_rhp_value* pstr_value);

/**
 * @function		twi_s32 twi_rhp_evaluate_condition(twi_const tstr_twi_rhp_condition * pstr_condition, twi_bool * pb_result)
 * @brief			This function evaluates the condition by computing both values of the condition then comparing them.
 * @param[in]		pstr_condition: pointer to the condition which will be evaluated
 * @param[out]		pb_result: pointer to the boolean to store the result of the comparison
 * @return    	    ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_evaluate_condition(twi_const tstr_twi_rhp_condition * pstr_condition, twi_bool * pb_result);

/**
 * @function		twi_s32 twi_rhp_evaluate_computed_value(twi_const tstr_twi_rhp_computed_value * pstr_computed,tstr_twi_rhp_value * pstr_result)
 * @brief			This function evaluates the computed value by checking the type of computation then performing it
 * @param[in]		pstr_computed: pointer to the computation value which will be executed
 * @param[out]		pstr_result: pointer to the value structure to set with the result
 * @return 	    	::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_rhp_evaluate_computed_value(twi_const tstr_twi_rhp_computed_value * pstr_computed,
		tstr_twi_rhp_value * pstr_result);

/** @} */   /*value_group*/

#endif
