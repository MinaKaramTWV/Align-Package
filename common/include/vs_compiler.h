/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file		twi_common.h
 ** @brief		This file includes the common macros/fns that can be used in the whole system.
 **
 */

 /** @defgroup TWI_COMMON_group TWI Common Functions
 * @{
 */
#ifndef TWI_VISUAL_COMPILER_H_
#define TWI_VISUAL_COMPILER_H_
/*-*********************************************************/
/*- FUNCTION-LIKE MACROS ----------------------------------*/
/*-*********************************************************/

#define TWI_PACK( __Declaration__ )		__pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#define TWI_ALIGN				_declspec(align(4)) __attribute__

#define TWI_WEAK						
#endif
