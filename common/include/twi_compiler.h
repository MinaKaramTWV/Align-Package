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
#ifndef COMPILER_H_
#define COMPILER_H_

/*-*********************************************************/
/*- INCLUDE COMPILER FILE  ----------------------------------*/
/*-*********************************************************/

#if defined ( __CC_ARM   )
	#include"armcc_compiler.h"
#elif defined   (  __GNUC__  )
	#include"gcc_compiler.h"
#elif defined   (WIN32 )
	#include"vs_compiler.h"
#elif defined   (__TI_COMPILER_VERSION__ )
     #include"ti_compiler.h"
#endif



#endif /* COMPILER_H_ */
