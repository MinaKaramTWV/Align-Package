/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
 *   @file       platform_pins.h
 *   @brief      This file contains TWI pin description for NRF52 platform.
 */

#ifndef _PLATFORM_PINS_H_
#define _PLATFORM_PINS_H_

#include "twi_gpio.h"

#if defined(PCA10040)								/* This is PCA10040 board */
	#include "./boards/pca10040_board/pca10040_pins.h"
#elif defined(TWI_EDWARDS_INDICATORS)
    #include "./boards/edwards_indicators_board/edwards_indicators_pins.h"
#elif defined(TWI_EDWARDS_INDICATORS_V2)
    #include "./boards/edwards_indicators_v2_board/edwards_indicators_v2_pins.h"
#elif defined(TWI_NURSE_TAG_BOARD)
    #include "./boards/nurse_tag_board/nurse_tag_pins.h"
#elif defined(BT832X_MODULE)
    #include "./boards/bt832x_module_board/bt832x_pins.h"
#elif defined(BT832X_GW)
    #include "./boards/bt832x_gw_board/bt832x_gw_pins.h"
#elif defined(TWI_ULP_LOGGER)
    #include "./boards/ulp_logger/ulp_logger_pins.h"
#elif defined(TWI_VIAL_BOARD)
    #include "./boards/twi_vial_board/twi_vial_pins.h"
#elif defined(NBIOT_HIGHSIDE_002)
    #include "./boards/nbiot_highside_002_board/nbiot_highside_002_pins.h"
#elif defined(TAGPCC_001)
    #include "./boards/tagpcc_001_board/tagpcc_001_pins.h"
#elif defined(TAGVM_001)
    #include "./boards/tagvm_001_board/tagvm_001_pins.h"
#elif defined(TAGVM_002)
    #include "./boards/tagvm_002_board/tagvm_002_pins.h"
#elif defined(PILRO_001)
    #include "./boards/pilro_001_board/pilro_001_pins.h"
#elif defined(PILRO_003)
    #include "./boards/pilro_003_board/pilro_003_pins.h"
#elif defined(IPILL_FORMFIT_V1_0)
    #include "./boards/ipill_formfit_v1_0_board/ipill_formfit_v1_0_board_pins.h"
#elif defined(IPILL_FORMFIT_V1_1)
    #include "./boards/ipill_formfit_v1_1_board/ipill_formfit_v1_1_board_pins.h"
#elif defined(IPILL_FORMFIT_V1_12)
    #include "./boards/ipill_formfit_v1_12_board/ipill_formfit_v1_12_board_pins.h"
#elif defined(TE8707)
    #include "./boards/te8707_board/te8707_pins.h"
#else
    #error Undefined Kit in the platform_pins.h file.
#endif

#endif  /*_PLATFORM_PINS_H_*/
