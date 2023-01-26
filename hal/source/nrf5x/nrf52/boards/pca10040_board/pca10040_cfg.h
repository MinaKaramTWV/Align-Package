/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
 *	@file		pca10040_cfg.h
 *	@brief		This file contains the configuartion description of pca10040 board.
 */

#ifndef _PCA10040_CFG_H_
#define _PCA10040_CFG_H_

#define AS621X_TEMP_SEN_I2C_CH              (0)
#define TEMP102_TEMP_SEN_I2C_CH				(0)
#define PLATFORM_HDC10XX_HUM_SEN_I2C_CH		(1)
#define INSULET_DRIVER_I2C_CH				(0)
#define FXAS21002_GYRO_SEN_I2C_CH			(0)
#define MONZAX_CH_NUM						(0)
#define CP240x_I2C_CHANNEL_NUM				(0)
#define PH_ADC_VREF_CH                      (0)
#define PH_PIN_ADC_VIN_CH					(2) /*P0.5*/
#define PH_REF_PIN_ADC_VIN_CH				(3)	/*P0.4*/

#define DF_8800_FORCE_SEN_I2C_CH		    (0)

#define MS5637_TEMP_PRESS_SEN_I2C_CH                (0)
//#define PLATFORM_SI7020A10_TEMP_SEN_I2C_CH   		(0)
//#define PLATFORM_FRIDGE_TAG_TEMP_SEN_CH			(0)
//#define PLATFORM_NPA201_TEMP_PRESS_SEN_I2C_CH		(0)
#define NPA201_TEMP_PRESS_SEN_I2C_CH				(0)
//#define HDC10XX_TEMP_SEN_I2C_CH					(0)
//#define PLATFORM_SI7020A10_HUM_SEN_I2C_CH   		(0)
#define KXTJ3_ACC_SEN_I2C_CH                        (0) 
#define BME280_TEMP_HUM_PRESS_SEN_I2C_CH			(0)
#define BMP388_TEMP_PRESS_SEN_I2C_CH			(0)
#define BMP388_TEMP_PRESS_SEN_SPI_CH			(0)
//#define BMP388_USE_SPI_INTF
//#define BMP388_USE_I2C_INTF
#ifdef USE_I2C_LIS2DH
    #define LIS2DH_ACC_SEN_I2C_CH               (1)
#elif USE_SPI_LIS2DH
    #define LIS2DH_ACC_SEN_SPI_CH				(1)
#endif
#define RTC_I2C_CHANNEL                         (0)
//#define LIS3DH_ACC_SEN_I2C_CH			(0)
//#define PLATFORM_INSULT_DRIVER_I2C_CH				(0)
//#define PLATFORM_SHT20_TEMP_HUM_SEN_I2C_CH		(0)
//#define PLATFORM_DEBUG_I2C_CH						(1)

#define PLATFORM_SI4455_SPI_CH			(0)

#define RTC_1805_I2C_CH_NUM				0

#define SYS_RESET_PIN_CONF             TWI_GPIO_DIR_IN | TWI_GPIO_PULL_UP
#define SYS_RESET_PIN_FLAG             TWI_GPIO_EDGE_FALLING
#define CONFG_BTN_STAT                 TWI_FALSE
#define ULP_SPI_CH_NUM					0

#define EEPROM_TYPE__CAT24C08__
#define EEPROM_CAT24CXX_I2C_CH_NUM              (0)

#define EEPROM_HE24CXX_I2C_CH_NUM               (1)


#endif /* _PCA10040_CFG_H_ */
