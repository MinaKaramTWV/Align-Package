/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_types.h
*   @brief      This file contains TWI data types definitions.
*/

#ifndef _TWI_TYPES_H_
#define _TWI_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/** @defgroup TWI_TYPES_group TWI Data Types.
* @{
*/

#define TWI_TRUE    true
#define TWI_FALSE   false

/**
*   @brief  Constant
*/
#define	twi_const const

/**
*   @brief  twi_float.
*/
typedef float twi_float;

/**
*   @brief  twi_double.
*/
typedef double twi_double;

/**
*   @brief  Boolean. Use TWI_TRUE and TWI_FALSE
*/
typedef bool twi_bool;

/**
*   @brief  Unsigned 8-bit integer.
*/
typedef uint8_t twi_u8;

/**
*   @brief  Signed 8-bit integer.
*/
typedef int8_t twi_s8;

/**
*   @brief  Unsigned 16-bit integer.
*/
typedef uint16_t twi_u16;

/**
*   @brief  Signed 16-bit integer.
*/
typedef int16_t twi_s16;

/**
*   @brief  Unsigned 32-bit integer.
*/
typedef uint32_t twi_u32;

/**
*   @brief  Signed 32-bit integer.
*/
typedef int32_t twi_s32;

/**
*   @brief  Unsigned 64-bit integer.
*/
typedef uint64_t twi_u64;

/**
*   @brief  Signed 64-bit integer.
*/
typedef int64_t twi_s64;

/**
 * @brief Signed Pointer
 */
typedef intptr_t twi_sptr;

/**
 * @brief Unsigned Pointer
 */
typedef uintptr_t twi_uptr;

/** @} */

#endif  /*_TWI_TYPES_H_*/

