/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
 *	@file		tagpcc_001_pins.h
 *	@brief		This file contains the pins description of tagpcc_001 board.
 */

#ifndef _TAGPCC_001_PINS_H_
#define _TAGPCC_001_PINS_H_

/**
 *	@defgroup	UART_MODULE_PINS	UART Module Pins Descriptions
 *	@brief		This is the description of UART module pins as used in TWI HAL
 *	@{
 */
#define UART0_RXD_PIN						INV_PIN		/**< Set UART0_RXD to pin 8.*/
#define UART0_RXD_PORT						INV_PORT	/**< Define PORTA to be UART0_RXD port.*/
#define UART0_TXD_PIN						TWI_PIN18	/**< Set UART0_TXD to pin 18.*/
#define UART0_TXD_PORT						TWI_PORTA	/**< Define PORTA to be UART0_TXD port.*/

/** @} */   /*UART_MODULE_PINS*/

/**
 *	@defgroup	I2C_MODULE_PINS		I2C Module Pins Descriptions
 *	@brief		This is the description of I2C module pins as used in TWI HAL
 *	@{
 */
#define I2C0_SCL_PIN						TWI_PIN26	/**< Set I2C0_SCL to pin 26.*/
#define I2C0_SCL_PORT						TWI_PORTA	/**< Define PORTA to be I2C0_SCL port.*/
#define I2C0_SDA_PIN						TWI_PIN9	/**< Set I2C0_SDA to pin 9.*/
#define I2C0_SDA_PORT						TWI_PORTA	/**< Define PORTA to be I2C0_SDA port.*/

#define I2C1_SCL_PIN						TWI_PIN22	/**< Set I2C1_SCL to pin 20.*/
#define I2C1_SCL_PORT						TWI_PORTA	/**< Define TWI_PORTA to be I2C1_SCL port.*/
#define I2C1_SDA_PIN						TWI_PIN23	/**< Set I2C1_SDA to pin 21.*/
#define I2C1_SDA_PORT						TWI_PORTA	/**< Define TWI_PORTA to be I2C1_SDA port.*/

#define I2C0_PULL_TYPE				TWI_EXT_PULL_UP 	/**< Set I2C0_PULL_TYPE to be externally pulled*/
#define I2C1_PULL_TYPE				TWI_INT_PULL_UP 	/**< Set I2C1_PULL_TYPE to be internally pulled*/
/** @} *//*I2C_MODULE_PINS_*/

/**
 *	@defgroup	SOFT_UART		SOFT UART Module Pins Descriptions
 *	@brief		This is the description of soft UART module pins as used in TWI HAL
 *	@{
 */
#define	SUART0_TX_PIN						INV_PIN		/**< Set SUART TX PIN*/
#define SUART0_TX_PORT			 			INV_PORT	/**< Define TWI_PORTA to be SUART TX port.*/

/** @} */   /*SOFTUART_MODULE_PINS_*/

/**
 *	@defgroup	SPI_MODULE_PINS		SPI Module Pins Descriptions
 *	@brief		This is the description of SPI module pins as used in TWI HAL
 *	@{
 */
#define SPI0_SCK_PIN				TWI_PIN26	/**< Set SPI0_SCK to pin 12.*/
#define SPI0_SCK_PORT				TWI_PORTA	/**< Define TWI_PORTA to be SPI0_SCK port.*/
#define SPI0_MOSI_PIN				TWI_PIN27	/**< Set SPI0_MOSI to pin 13.*/
#define SPI0_MOSI_PORT				TWI_PORTA	/**< Define TWI_PORTA to be SPI0_MOSI port.*/
#define SPI0_MISO_PIN				TWI_PIN28	/**< Set SPI0_MISO to pin 14.*/
#define SPI0_MISO_PORT				TWI_PORTA	/**< Define TWI_PORTA to be SPI0_MISO port.*/

#define SPI1_SCK_PIN				INV_PIN	/**< Set SPI1_SCK to pin 20.*/
#define SPI1_SCK_PORT				INV_PORT	/**< Define TWI_PORTA to be SPI0_SCK port.*/
#define SPI1_MOSI_PIN				INV_PIN	/**< Set SPI1_MOSI to pin 21.*/
#define SPI1_MOSI_PORT				INV_PORT	/**< Define TWI_PORTA to be SPI0_MOSI port.*/
#define SPI1_MISO_PIN				INV_PIN	/**< Set SPI1_MISO to pin 22.*/
#define SPI1_MISO_PORT				INV_PORT	/**< Define TWI_PORTA to be SPI0_MISO port.*/
/** @} *//*SPI_MODULE_PINS_*/

 /**
 *	@defgroup	ADC_MODULE_PINS		ADC Module Pins Descriptions
 *	@brief		This is the description of ADC module pins as used in TWI HAL
 *	@{
 */
#define ADC_CH0_VIN_PIN						TWI_PIN2	/**< Set ADC_CH0_VIN to TWI_PIN2. This is the AIN4.*/
#define ADC_CH0_VIN_PORT					TWI_PORTA	/**< Define PORTA to be ADC_CH0_VIN port. This is the AIN4. */
/** @} */   /*ADC_MODULE_PINS_*/
/**
 *	@defgroup	LEDS_PINS	LEDs Pins Descriptions
 *	@brief		This is the description of LEDS pins as used in TWI HAL
 *	@{
 */
#define LED0_PIN							TWI_PIN8	/**< Set LED0 (Green LED) to pin 8 .*/
#define LED0_PORT							TWI_PORTA	/**< Define PORTA to be LED0 port.*/
#define LED1_PIN							TWI_PIN12	/**< Set LED1 (RED LED) to pin 12.*/
#define LED1_PORT							TWI_PORTA	/**< Define PORTA to be LED1 port.*/
#define LED2_PORT               			INV_PORT
#define LED2_PIN                			INV_PIN        
/** @} */	/*LEDS_PINS*/

 /**
 *	@defgroup	BTNS_PINS	Buttons Pins Descriptions
 *	@brief		This is the description of BTNS pins as used in TWI HAL
 *	@{
 */
#define PBTN0_PORT							TWI_PORTA	/**< Define PORTA to be PBTN0 port.*/
#define PBTN0_PIN							TWI_PIN13	/**< Set PBTN0 to pin 13.*/
/** @} */   /*BTNS_PINS_*/

#define BLE_PA_GPIO_PORT					TWI_PORTA
#define BLE_PA_GPIO_PIN						TWI_PIN17

#define BLE_LNA_GPIO_PORT					TWI_PORTA
#define BLE_LNA_GPIO_PIN					TWI_PIN19

#define BLE_CPS_GPIO_PORT					TWI_PORTA
#define BLE_CPS_GPIO_PIN					TWI_PIN6


#define PRESSURE_SENSOR_I2C_ADDR_PORT		TWI_PORTA	/**<  Define TWI_PORTA to be I2C address port for pressure sensor.*/
#define PRESSURE_SENSOR_I2C_ADDR_PIN		TWI_PIN3	/**<  Define TWI_PIN11 to be I2C address pin for pressure sensor.*/

#define PRESSURE_SENSOR_BMP388_CS_PORT		TWI_PORTA 	/**<  Define TWI_PORTA to be CS port for pressure sensor.*/
#define PRESSURE_SENSOR_BMP388_CS_PIN		TWI_PIN12	/**<  Define TWI_PIN12 to be CS pin for pressure sensor.*/


#define EEPROM_HE24CXX_A0_PORT                 	(INV_PORT)
#define EEPROM_HE24CXX_A0_PIN                  	(INV_PIN)
#define EEPROM_HE24CXX_A1_PORT                 	(INV_PORT)
#define EEPROM_HE24CXX_A1_PIN                  	(INV_PIN)
#define EEPROM_HE24CXX_A2_PORT                 	(INV_PORT)
#define EEPROM_HE24CXX_A2_PIN                  	(INV_PIN)
#define EEPROM_HE24CXX_WP_PORT                 	(INV_PORT)
#define EEPROM_HE24CXX_WP_PIN                  	(INV_PIN)

#define ACCELEROMETER_I2C_ADDR_PORT				(INV_PORT)	/**< Define INV_PORT to be Accelerometer I2C ADDR selection port.*/
#define ACCELEROMETER_I2C_ADDR_PIN				(INV_PIN)	/**< Set Accelerometer I2C ADDR selection to INV_PIN.*/

#define ACCELEROMETER_CS_PORT					(INV_PORT)	/**< Define INV_PORT to be Accelerometer I2C CS port.*/
#define ACCELEROMETER_CS_PIN					(INV_PIN)	/**< Set Accelerometer I2C CS to INV_PIN.*/

#define ACCELEROMETER_INT1_PORT					(INV_PORT)	/**< Define TWI_PORTA to be Accelerometer interrupt port.*/
#define ACCELEROMETER_INT1_PIN					(INV_PIN)   /**< Set Accelerometer interrupt to TWI_PIN12.*/  

#define ACCELEROMETER_EN_PORT		            (INV_PORT)	/**< Define INV_PORT to be Accelerometer enable port.*/
#define ACCELEROMETER_EN_PIN		            (INV_PIN)	/**< Set Accelerometer Addresses enable to INV_PIN.*/

#define PWM0_PORT                               (INV_PORT)
#define PWM0_PIN                                (INV_PIN)

#define SYSTEM_RESET_PORT           			INV_PORT
#define SYSTEM_RESET_PIN            			INV_PIN

#define SYS_RESET_PIN_CONF             			TWI_GPIO_DIR_IN | TWI_GPIO_PULL_UP
#define SYS_RESET_PIN_FLAG             			TWI_GPIO_EDGE_FALLING 
#define CONFG_BTN_STAT                      	TWI_FALSE

#define TWI_VAPE_LIBRARY_USB_DETECTION_PORT		INV_PORT
#define TWI_VAPE_LIBRARY_USB_DETECTION_PIN		INV_PIN
/**
* @defgroup	BUZZER_PINS	Buzzer Pins Descriptions
* @brief    This is the description of BUZZER pins as used in TWI HAL
*/
#define BUZZER_PORT							INV_PORT 	/**< Define PORTA to be BUZZER port.*/
#define BUZZER_DIN_PIN						INV_PIN     /**< Set BUZZER_IN_PIN to invalid pin.*/
#define BUZZER_EN1_PIN						INV_PIN     /**< Set BUZZER_EN1_PIN to invalid pin.*/
#define BUZZER_EN2_PIN						INV_PIN     /**< Set BUZZER_EN2_PIN to invalid pin.*/
/** @} */	/*BUZZER_PINS*/

#define PRESSURE_SENSOR_HW_EN_PORT          TWI_PORTA 	/**<  Define TWI_PORTA to be Enable port for pressure sensor.*/
#define PRESSURE_SENSOR_HW_EN_PIN           TWI_PIN10	/**<  Define TWI_PIN10 to be Enable pin for pressure sensor.*/

#define SEAL_STATUS_PORT                    TWI_PORTA 	/**<  Define TWI_PORTA to be seal port.*/
#define SEAL_STATUS_PIN                     TWI_PIN20   /**<  Define TWI_PIN20 to be seal pin.*/

#define CART_PIN_PULL_TYPE   				CART_PIN_PULL_UP
#define CART_PIN_NUM 						CART_PIN_13
/**
* @defgroup	IPILL_PINS Dispenser Pins Descriptions
* @brief    This is the description of pins needed for iPill Dispenser project
*/
#define	ENCODER_A_PIN	    	INV_PIN
#define	ENCODER_A_PORT		    INV_PORT

#define	ENCODER_B_PIN		    INV_PIN
#define	ENCODER_B_PORT		    INV_PORT

#define	MOTOR_ENABLE_PIN		INV_PIN
#define	MOTOR_ENABLE_PORT		INV_PORT

#define	ENCODER_A_PIN		                INV_PIN
#define	ENCODER_A_PORT		                INV_PORT

#define	ENCODER_B_PIN		                INV_PIN
#define	ENCODER_B_PORT		                INV_PORT

#define	MOTOR_PHASE_PIN			INV_PIN
#define	MOTOR_PHASE_PORT		INV_PORT

#define ROTATION_SW1_PIN        INV_PIN
#define	ROTATION_SW1_PORT		INV_PORT

#define ROTATION_SW2_PIN        INV_PIN
#define	ROTATION_SW2_PORT		INV_PORT

#define	PBTN1_PIN				INV_PIN
#define PBTN1_PORT			 	INV_PORT

#define ALIGN_PBTN_PIN          INV_PIN
#define ALIGN_PBTN_PORT         INV_PORT

#define MOTOR_SLEEP_PIN         INV_PIN
#define MOTOR_SLEEP_PORT        INV_PORT

#define MOTOR_POWER_CONTROL_GND_PIN		INV_PIN
#define MOTOR_POWER_CONTROL_GND_PORT	INV_PORT

#define LIGHT_SENSOR_1_PIN			INV_PIN
#define LIGHT_SENSOR_1_PORT			INV_PORT

#define LIGHT_SENSOR_2_PIN			INV_PIN
#define LIGHT_SENSOR_2_PORT			INV_PORT

#define LIGHT_SENSOR_PWR_PIN		INV_PIN
#define LIGHT_SENSOR_PWR_PORT		INV_PORT

#define TWI_BAT_REF_PIN				INV_PIN
#define TWI_BAT_REF_PORT			INV_PORT

#define TWI_BAT_REF_EN_PIN			INV_PIN
#define TWI_BAT_REF_EN_PORT			INV_PORT
 
#ifdef TESTING_DISPENSE
#define TEST_DISPENSE_PORT                  TWI_PORTA
#define TEST_DISPENSE_PIN                   TWI_PIN20
#endif


#if defined(IPILL_DISPENSER) && defined(USE_LEDS_TESTING)
 /**
 *	@defgroup	SOLENOID_CTRL_PINS	Pill Destruction Pins Descriptions
 *	@brief		This is the description of soleniod control pin as used in TWI HAL
 *	@{
 */
#define SOLENOID_CTRL_PORT			        LED0_PORT	        /**< Define TWI_PORTA to be soleniod control port.*/
#define SOLENOID_CTRL_PIN				    LED0_PIN            /**< Set soleniod control pin  to TWI_PIN8.*/ 
/** @} *//*SOLENOID_CTRL_PINS_*/

/**
* @defgroup	BUZZER_PINS	Buzzer Pins Descriptions
* @brief    This is the description of BUZZER pins as used in TWI HAL
*/
#define BUZZER_EN_PORT					    INV_PORT 	        /**< Define INV_PORT to be BUZZER port.*/
#define BUZZER_EN_PIN				        INV_PIN             /**< Set BUZZER_EN_PIN to invalid pin.*/
/** @} */	/*BUZZER_PINS*/ 
#endif

#endif /* _TAGPCC_001_PINS_H_ */
