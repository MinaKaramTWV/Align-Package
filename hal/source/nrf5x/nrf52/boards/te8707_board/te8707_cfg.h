/****************************************************************************/
/* Copyright (c) 2023 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
 *	@file		te8707_cfg.h
 *	@brief		This file contains the configuartion description of TE8707 board.
 */

#ifndef _TE8707_CFG_H_
#define _TE8707_CFG_H_

#define AS621X_TEMP_SEN_I2C_CH              (0)
#define FXAS21002_GYRO_SEN_I2C_CH			(0)
#define MONZAX_CH_NUM						(0)
#define CP240x_I2C_CHANNEL_NUM				(0)
#define PH_ADC_VREF_CH                      (0) /*P0.2*/
#define PH_PIN_ADC_VIN_CH					(2) /*P0.4*/
#define PH_REF_PIN_ADC_VIN_CH				(4)	/*P0.28*/

#define DF_8800_FORCE_SEN_I2C_CH		    (0)

#define MS5637_TEMP_PRESS_SEN_I2C_CH                (0)
#define NPA201_TEMP_PRESS_SEN_I2C_CH				(0)
#define KXTJ3_ACC_SEN_I2C_CH                        (0) 
#define BME280_TEMP_HUM_PRESS_SEN_I2C_CH			(0)
#define BMP388_TEMP_PRESS_SEN_I2C_CH			(0)
#define BMP388_TEMP_PRESS_SEN_SPI_CH			(0)
#ifdef USE_I2C_LIS2DH
    #define LIS2DH_ACC_SEN_I2C_CH               (1)
#elif USE_SPI_LIS2DH
    #define LIS2DH_ACC_SEN_SPI_CH				(1)
#endif
#define RTC_I2C_CHANNEL                         (0)

#define PLATFORM_SI4455_SPI_CH			(0)

#define RTC_1805_I2C_CH_NUM				0

#define SYS_RESET_PIN_CONF             TWI_GPIO_DIR_IN | TWI_GPIO_PULL_UP
#define SYS_RESET_PIN_FLAG             TWI_GPIO_EDGE_FALLING
#define CONFG_BTN_STAT                 TWI_FALSE

#endif /* _TE8707_CFG_H_ */
