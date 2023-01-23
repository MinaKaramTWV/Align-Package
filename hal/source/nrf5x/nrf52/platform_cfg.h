/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
 *   @file       platform_cfg.h
 *   @brief      This file contains TWI board's configuartion description for NRF51 platform.
 */

#ifndef _PLATFORM_CFG_H_
#define _PLATFORM_CFG_H_

#if defined(PCA10040)								/* This is PCA10040 board */
	#include "./boards/pca10040_board/pca10040_cfg.h"
#elif defined (TWI_EDWARDS_INDICATORS)
    #include "./boards/edwards_indicators_board/edwards_indicators_cfg.h"
#elif defined(TWI_EDWARDS_INDICATORS_V2)
    #include "./boards/edwards_indicators_v2_board/edwards_indicators_v2_cfg.h"
#elif defined(TWI_NURSE_TAG_BOARD)
    #include "./boards/nurse_tag_board/nurse_tag_cfg.h"
#elif defined(BT832X_MODULE)
    #include "./boards/bt832x_module_board/bt832x_cfg.h"
#elif defined(BT832X_GW)
    #include "./boards/bt832x_gw_board/bt832x_gw_cfg.h"
#elif defined(TWI_VIAL_BOARD)
    #include "./boards/twi_vial_board/twi_vial_cfg.h"
#elif defined(TWI_ULP_LOGGER)
    #include "./boards/ulp_logger/ulp_logger_cfg.h"
#elif defined(NBIOT_HIGHSIDE_002)
    #include "./boards/nbiot_highside_002_board/nbiot_highside_002_cfg.h"
#elif defined(TAGPCC_001)
    #include "./boards/tagpcc_001_board/tagpcc_001_cfg.h"
#elif defined(TAGVM_001)
    #include "./boards/tagvm_001_board/tagvm_001_cfg.h"
#elif defined(TAGVM_002)
    #include "./boards/tagvm_002_board/tagvm_002_cfg.h"
#elif defined(PILRO_001)
    #include "./boards/pilro_001_board/pilro_001_cfg.h"
#elif defined(PILRO_003)
    #include "./boards/pilro_003_board/pilro_003_cfg.h"
#elif defined(IPILL_FORMFIT_V1_0)
    #include "./boards/ipill_formfit_v1_0_board/ipill_formfit_v1_0_board_cfg.h"
#elif defined(IPILL_FORMFIT_V1_1)
    #include "./boards/ipill_formfit_v1_1_board/ipill_formfit_v1_1_board_cfg.h"
#elif defined(IPILL_FORMFIT_V1_12)
    #include "./boards/ipill_formfit_v1_12_board/ipill_formfit_v1_12_board_cfg.h"
#elif defined(TE8707)
    #include "./boards/te8707_board/te8707_cfg.h"
#else
    #error Undefined Kit in the platform_cfg.h file.
#endif

#endif  /*_PLATFORM_CFG_H_*/
