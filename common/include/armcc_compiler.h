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
#ifndef TWI_ARMCC_COMPILER_H_
#define TWI_ARMCC_COMPILER_H_

/*-*********************************************************/
/*- FUNCTION-LIKE MACROS ----------------------------------*/
/*-*********************************************************/

#define TWI_ALIGN						__attribute__ ((aligned(4)))
#define TWI_PACK( __Declaration__ )		__Declaration__ __attribute__((__packed__))
#define TWI_WEAK						__attribute__((weak))

#endif /* TWI_ARMCC_COMPILER_H_ */
