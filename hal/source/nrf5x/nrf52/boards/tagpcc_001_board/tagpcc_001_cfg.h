/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
 *	@file		tagpcc_001_cfg.h
 *	@brief		This file contains the configuration description of tagpcc_001 board.
 */

#ifndef _TAGPCC_001_CFG_H_
#define _TAGPCC_001_CFG_H_

#define BMP388_TEMP_PRESS_SEN_I2C_CH			    (0)
#define BMP388_TEMP_PRESS_SEN_SPI_CH			    (1)

#ifndef DISABLE_EXTENDED_RANGE
#define BLE_EXTEND_RANGE
#endif

#define AS621X_TEMP_SEN_I2C_CH                      (0)
#define DF_8800_FORCE_SEN_I2C_CH		            (0)
#define MS5637_TEMP_PRESS_SEN_I2C_CH                (0)
#define KXTJ3_ACC_SEN_I2C_CH                        (0) 
#define LIS2DH_ACC_SEN_I2C_CH						(1)
#define EEPROM_HE24CXX_I2C_CH_NUM                   (1)


#endif /* _TAGPCC_001_CFG_H_ */
