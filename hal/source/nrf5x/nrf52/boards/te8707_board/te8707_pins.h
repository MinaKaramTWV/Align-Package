/****************************************************************************/
/* Copyright (c) 2023 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
 *   @file       te8707_pins.h
 *   @brief      This file contains the pins description of Nordic's TE8707 board.
 *               You can find all details through those links:
 *                  https://github.com/ThirdWayv/Docs/blob/ALGN-93/Projects/Align%20Project/TY_BLE_EYSHSNZWZ_DataReport_V1_3_20180530E.pdf
 *                  https://github.com/ThirdWayv/Docs/blob/ALGN-93/Projects/Align%20Project/TY_BLE_EYSHSN_EVBManual_V1_2_20180530.pdf
 *                  https://github.com/ThirdWayv/Docs/blob/ALGN-93/Projects/Align%20Project/BLE_POC.pdf
 */

#ifndef _TE8707_PINS_H_
#define _TE8707_PINS_H_

/**
 *	@defgroup	UART_MODULE_PINS	UART Module Pins Descriptions
 *	@brief		This is the description of UART module pins as used in TWI HAL
 *	@{
 */
#define UART0_RXD_PIN				INV_PIN	    /**< Set UART0_RXD to INV_PIN.*/
#define UART0_RXD_PORT				INV_PORT	/**< Define INV_PORT to be UART0_RXD port.*/
#define UART0_TXD_PIN				TWI_PIN2	/**< Set UART0_TXD to pin 2.*/
#define UART0_TXD_PORT				TWI_PORTA	/**< Define TWI_PORTA to be UART0_TXD port.*/
#define UART0_RTS_PIN				INV_PIN		/**< Set UART0_RTS to INV_PIN.*/
#define UART0_RTS_PORT				INV_PORT	/**< Define INV_PORT to be UART0_RTS port.*/
#define UART0_CTS_PIN				INV_PIN		/**< Set UART0_CTS to INV_PIN.*/
#define UART0_CTS_PORT				INV_PORT	/**< Define INV_PORT to be UART0_CTS port.*/
/** @} *//*UART_MODULE_PINS_*/

/**
 *	@defgroup	I2C_MODULE_PINS		I2C Module Pins Descriptions
 *	@brief		This is the description of I2C module pins as used in TWI HAL
 *	@{
 */
#define I2C0_SCL_PIN				TWI_PIN6	/**< Set I2C0_SCL to pin 6.*/
#define I2C0_SCL_PORT				TWI_PORTA	/**< Define TWI_PORTA to be I2C0_SCL port.*/
#define I2C0_SDA_PIN				TWI_PIN5	/**< Set I2C0_SDA to pin 5.*/
#define I2C0_SDA_PORT				TWI_PORTA	/**< Define TWI_PORTA to be I2C0_SDA port.*/

#define I2C1_SCL_PIN				INV_PIN		/**< Set I2C1_SCL to INV_PIN.*/
#define I2C1_SCL_PORT				INV_PORT	/**< Define INV_PORT to be I2C1_SCL port.*/
#define I2C1_SDA_PIN				INV_PIN		/**< Set I2C1_SDA to INV_PIN.*/
#define I2C1_SDA_PORT				INV_PORT	/**< Define INV_PORT to be I2C1_SDA port.*/

#define I2C0_PULL_TYPE				TWI_INT_PULL_UP 	/**< Set I2C0_PULL_TYPE to be externally pulled*/
#define I2C1_PULL_TYPE				TWI_INT_PULL_UP 	/**< Set I2C1_PULL_TYPE to be internally pulled*/
/** @} *//*I2C_MODULE_PINS_*/

/**
 *	@defgroup	SPI_MODULE_PINS		SPI Module Pins Descriptions
 *	@brief		This is the description of SPI module pins as used in TWI HAL
 *	@{
 */
#define SPI0_SCK_PIN				INV_PIN	    /**< Set SPI0_SCK to INV_PIN.*/
#define SPI0_SCK_PORT				INV_PORT	/**< Define INV_PORT to be SPI0_SCK port.*/
#define SPI0_MOSI_PIN				INV_PIN	    /**< Set SPI0_MOSI to INV_PIN.*/
#define SPI0_MOSI_PORT				INV_PORT	/**< Define INV_PORT to be SPI0_MOSI port.*/
#define SPI0_MISO_PIN				INV_PIN	    /**< Set SPI0_MISO to INV_PIN.*/
#define SPI0_MISO_PORT				INV_PORT	/**< Define INV_PORT to be SPI0_MISO port.*/

#define SPI1_SCK_PIN				INV_PIN	    /**< Set SPI1_SCK to INV_PIN.*/
#define SPI1_SCK_PORT				INV_PORT	/**< Define INV_PORT to be SPI0_SCK port.*/
#define SPI1_MOSI_PIN				INV_PIN	    /**< Set SPI1_MOSI to INV_PIN.*/
#define SPI1_MOSI_PORT				INV_PORT	/**< Define INV_PORT to be SPI0_MOSI port.*/
#define SPI1_MISO_PIN				INV_PIN	    /**< Set SPI1_MISO to INV_PIN.*/
#define SPI1_MISO_PORT				INV_PORT	/**< Define INV_PORT to be SPI0_MISO port.*/
/** @} *//*SPI_MODULE_PINS_*/

/**
 *	@defgroup	SPI_SLAVE_MODULE_PINS	NRF51 Pins Descriptions
 *	@brief		This is the description of SPI slave module pins as used in TWI HAL
 *	@{
 */
#define SPIS0_SCK_PIN				INV_PIN	    /**< Set SPIS0_SCK to INV_PIN.*/
#define SPIS0_SCK_PORT				INV_PORT	/**< Define INV_PORT to be SPIS0_SCK port.*/
#define SPIS0_MOSI_PIN				INV_PIN	    /**< Set SPIS0_MOSI to INV_PIN.*/
#define SPIS0_MOSI_PORT				INV_PORT	/**< Define INV_PORT to be SPIS0_MOSI port.*/
#define SPIS0_MISO_PIN				INV_PIN	    /**< Set SPIS0_MISO to INV_PIN.*/
#define SPIS0_MISO_PORT				INV_PORT	/**< Define INV_PORT to be SPIS0_MISO port.*/
#define SPIS0_CSN_PIN				INV_PIN	    /**< Set SPIS0_CSN to INV_PIN.*/
#define SPIS0_CSN_PORT				INV_PORT	/**< Define INV_PORT to be SPIS0_CSN port.*/
/** @} *//*SPI_SLAVE_MODULE_PINS_*/

/**
 *	@defgroup	SPI_MASTER_MODULE_PINS	SPI Master Module Pins Descriptions
 *	@brief		This is the description of SPI master module pins as used in TWI HAL
 *	@{
 */
#define SPI_COMM_MASTER_INT_PIN		INV_PIN	    /**< Set SPI_COMM_MASTER_INT_PIN to INV_PIN.*/
#define SPI_COMM_MASTER_INT_PORT	INV_PORT	/**< Define INV_PORT to be SPI_COMM_MASTER_INT port.*/
#define SPI_COMM_SLAVE_INT_PIN		INV_PIN	    /**< Set SPI_COMM_SLAVE_INT_PIN to INV_PIN.*/
#define SPI_COMM_SLAVE_INT_PORT		INV_PORT	/**< Define INV_PORT to be SPI_COMM_SLAVE_INT port.*/
/** @} *//*SPI_MASTER_MODULE_PINS_*/

/**
 *	@defgroup	BTNS_PINS	Buttons Pins Descriptions
 *	@brief		This is the description of BTNS pins as used in TWI HAL
 *	@{
 */
#define PBTN0_PIN					INV_PIN	    /**< Set PBTN0 to INV_PIN.*/
#define PBTN0_PORT					INV_PORT	/**< Define INV_PORT to be PBTN0 port.*/
#define PBTN1_PIN					INV_PIN	    /**< Set PBTN1 to INV_PIN.*/
#define PBTN1_PORT					INV_PORT	/**< Define INV_PORT to be PBTN1 port.*/
#define PBTN2_PIN                   INV_PIN     /**< Set PBTN2 to INV_PIN.*/
#define PBTN2_PORT                  INV_PORT    /**< Define INV_PORT to be PBTN2 port.*/
#define PBTN3_PIN                   INV_PIN     /**< Set PBTN3 to INV_PIN.*/
#define PBTN3_PORT                  INV_PORT    /**< Define INV_PORT to be PBTN3 port.*/
/** @} *//*BTNS_PINS_*/

/**
 *	@defgroup	ADC_MODULE_PINS		ADC Module Pins Descriptions
 *	@brief		This is the description of ADC module pins as used in TWI HAL
 *	@{
 */
#define ADC_CH0_VIN_PIN				TWI_PIN2	/**< Set ADC_CH0_VIN to pin 2. This is the AIN0.*/
#define ADC_CH0_VIN_PORT			TWI_PORTA	/**< Define TWI_PORTA to be ADC_CH0_VIN port. This is the AIN0. */
#define ADC_CH1_VIN_PIN				TWI_PIN3	/**< Set ADC_CH1_VIN to pin 3. This is the AIN1.*/
#define ADC_CH1_VIN_PORT			TWI_PORTA	/**< Define TWI_PORTA to be ADC_CH1_VIN port. This is the AIN1.*/
#define ADC_CH2_VIN_PIN				TWI_PIN4	/**< Set ADC_CH2_VIN to pin 28. This is the AIN2.*/
#define ADC_CH2_VIN_PORT			TWI_PORTA	/**< Define TWI_PORTA to be ADC_CH2_VIN port. This is the AIN2.*/
#define ADC_CH3_VIN_PIN				TWI_PIN5	/**< Set ADC_CH3_VIN to pin 5. This is the AIN3.*/
#define ADC_CH3_VIN_PORT			TWI_PORTA	/**< Define TWI_PORTA to be ADC_CH3_VIN port. This is the AIN3.*/
#define ADC_CH4_VIN_PIN				TWI_PIN28	/**< Set ADC_CH4_VIN to pin 28. This is the AIN4.*/
#define ADC_CH4_VIN_PORT			TWI_PORTA	/**< Define TWI_PORTA to be ADC_CH4_VIN port. This is the AIN4.*/
#define ADC_CH5_VIN_PIN				INV_PIN	    /**< Set ADC_CH5_VIN to INV_PIN. This is the AIN5.*/
#define ADC_CH5_VIN_PORT			INV_PORT	/**< Define INV_PORT to be ADC_CH5_VIN port. This is the AIN5.*/
#define ADC_CH6_VIN_PIN				INV_PIN	    /**< Set ADC_CH6_VIN to INV_PIN. This is the AIN6.*/
#define ADC_CH6_VIN_PORT			INV_PORT	/**< Define INV_PORT to be ADC_CH6_VIN port. This is the AIN6.*/
#define ADC_CH7_VIN_PIN				INV_PIN	    /**< Set ADC_CH7_VIN to INV_PIN. This is the AIN7.*/
#define ADC_CH7_VIN_PORT			INV_PORT	/**< Define INV_PORT to be ADC_CH7_VIN port. This is the AIN7.*/
/** @} *//*ADC_MODULE_PINS_*/

/**
*	@defgroup	ACC_MODULE_PINS		Accelerometer Module Pins Descriptions
*	@brief		This is the description of Accelerometer module pins as used in TWI HAL
*	@{
*/

#define ACCELEROMETER_CS_PORT		(INV_PORT)	/**< Define INV_PORT to be Accelerometer CS port.*/
#define ACCELEROMETER_CS_PIN		(INV_PIN)	/**< Set Accelerometer CS to INV_PIN.*/

#define ACCELEROMETER_INT1_PORT	    (INV_PORT)	/**< Define INV_PORT to be Accelerometer interrupt port.*/
#define ACCELEROMETER_INT1_PIN	    (INV_PIN)	/**< Set Accelerometer interrupt to INV_PIN.*/

#define ACCELEROMETER_I2C_ADDR_PORT	(INV_PORT)	/**< Define TWI_PORTA to be Accelerometer Addresses select port.*/
#define ACCELEROMETER_I2C_ADDR_PIN	(INV_PIN)	/**< Set Accelerometer Addresses select to INV_PIN.*/

#define ACCELEROMETER_EN_PORT		(INV_PORT)	/**< Define INV_PORT to be Accelerometer enable port.*/
#define ACCELEROMETER_EN_PIN		(INV_PIN)	/**< Set Accelerometer Addresses enable to INV_PIN.*/

#endif /* _TE8707_PINS_H_ */
