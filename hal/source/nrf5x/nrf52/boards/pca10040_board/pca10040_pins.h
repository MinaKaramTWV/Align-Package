/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
 *   @file       pca10040_pins.h
 *   @brief      This file contains the pins description of Nordic's PCA10040 board.
 */

#ifndef _PCA10040_PINS_H_
#define _PCA10040_PINS_H_

/**
 *	@defgroup	UART_MODULE_PINS	UART Module Pins Descriptions
 *	@brief		This is the description of UART module pins as used in TWI HAL
 *	@{
 */
#define UART0_RXD_PIN				TWI_PIN8	/**< Set UART0_RXD to pin 8.*/
#define UART0_RXD_PORT				TWI_PORTA	/**< Define TWI_PORTA to be UART0_RXD port.*/
#define UART0_TXD_PIN				TWI_PIN6	/**< Set UART0_TXD to pin 6.*/
#define UART0_TXD_PORT				TWI_PORTA	/**< Define TWI_PORTA to be UART0_TXD port.*/
#define UART0_RTS_PIN				INV_PIN		/**< Set UART0_RTS to pin 10.*/
#define UART0_RTS_PORT				INV_PORT	/**< Define TWI_PORTA to be UART0_RTS port.*/
#define UART0_CTS_PIN				INV_PIN		/**< Set UART0_CTS to pin 11.*/
#define UART0_CTS_PORT				INV_PORT	/**< Define TWI_PORTA to be UART0_CTS port.*/
/** @} *//*UART_MODULE_PINS_*/

/**
 *	@defgroup	I2C_MODULE_PINS		I2C Module Pins Descriptions
 *	@brief		This is the description of I2C module pins as used in TWI HAL
 *	@{
 */
#define I2C0_SCL_PIN				TWI_PIN22	/**< Set I2C0_SCL to pin 12.*/
#define I2C0_SCL_PORT				TWI_PORTA	/**< Define TWI_PORTA to be I2C0_SCL port.*/
#define I2C0_SDA_PIN				TWI_PIN23	/**< Set I2C0_SDA to pin 13.*/
#define I2C0_SDA_PORT				TWI_PORTA	/**< Define TWI_PORTA to be I2C0_SDA port.*/

#define I2C1_SCL_PIN				INV_PIN		/**< Set I2C1_SCL to pin 20.*/
#define I2C1_SCL_PORT				INV_PORT	/**< Define TWI_PORTA to be I2C1_SCL port.*/
#define I2C1_SDA_PIN				INV_PIN		/**< Set I2C1_SDA to pin 21.*/
#define I2C1_SDA_PORT				INV_PORT	/**< Define TWI_PORTA to be I2C1_SDA port.*/

#define I2C0_PULL_TYPE				TWI_INT_PULL_UP 	/**< Set I2C0_PULL_TYPE to be externally pulled*/
#define I2C1_PULL_TYPE				TWI_INT_PULL_UP 	/**< Set I2C1_PULL_TYPE to be internally pulled*/
/** @} *//*I2C_MODULE_PINS_*/

/**
 *	@defgroup	SOFT_UART		SOFT UART Module Pins Descriptions
 *	@brief		This is the description of soft UART module pins as used in TWI HAL
 *	@{
 */
#define	SUART0_TX_PIN				TWI_PIN20	/**< Set SUART TX PIN*/
#define SUART0_TX_PORT			 	TWI_PORTA	/**< Define TWI_PORTA to be SUART TX port.*/

/** @} *//*SOFTUART_MODULE_PINS_*/

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
#define SPI1_MOSI_PIN				TWI_PIN21	/**< Set SPI1_MOSI to pin 21.*/
#define SPI1_MOSI_PORT				TWI_PORTA	/**< Define TWI_PORTA to be SPI0_MOSI port.*/
#define SPI1_MISO_PIN				TWI_PIN22	/**< Set SPI1_MISO to pin 22.*/
#define SPI1_MISO_PORT				TWI_PORTA	/**< Define TWI_PORTA to be SPI0_MISO port.*/
/** @} *//*SPI_MODULE_PINS_*/

/**
 *	@defgroup	SPI_SLAVE_MODULE_PINS	NRF51 Pins Descriptions
 *	@brief		This is the description of SPI slave module pins as used in TWI HAL
 *	@{
 */
#define SPIS0_SCK_PIN				TWI_PIN3	/**< Set SPIS0_SCK to pin 20.*/
#define SPIS0_SCK_PORT				TWI_PORTA	/**< Define TWI_PORTA to be SPIS0_SCK port.*/
#define SPIS0_MOSI_PIN				TWI_PIN4	/**< Set SPIS0_MOSI to pin 21.*/
#define SPIS0_MOSI_PORT				TWI_PORTA	/**< Define TWI_PORTA to be SPIS0_MOSI port.*/
#define SPIS0_MISO_PIN				TWI_PIN28	/**< Set SPIS0_MISO to pin 22.*/
#define SPIS0_MISO_PORT				TWI_PORTA	/**< Define TWI_PORTA to be SPIS0_MISO port.*/
#define SPIS0_CSN_PIN				TWI_PIN29	/**< Set SPIS0_CSN to pin 23.*/
#define SPIS0_CSN_PORT				TWI_PORTA	/**< Define TWI_PORTA to be SPIS0_CSN port.*/
/** @} *//*SPI_SLAVE_MODULE_PINS_*/

/**
 *	@defgroup	SPI_MASTER_MODULE_PINS	SPI Master Module Pins Descriptions
 *	@brief		This is the description of SPI master module pins as used in TWI HAL
 *	@{
 */
#define SPI_COMM_MASTER_INT_PIN		TWI_PIN0	/**< Set SPI_COMM_MASTER_INT_PIN to pin 0.*/
#define SPI_COMM_MASTER_INT_PORT	TWI_PORTA	/**< Define TWI_PORTA to be SPI_COMM_MASTER_INT port.*/
#define SPI_COMM_SLAVE_INT_PIN		TWI_PIN0	/**< Set SPI_COMM_SLAVE_INT_PIN to pin 0.*/
#define SPI_COMM_SLAVE_INT_PORT		TWI_PORTA	/**< Define TWI_PORTA to be SPI_COMM_SLAVE_INT port.*/
/** @} *//*SPI_MASTER_MODULE_PINS_*/

/**
 *	@defgroup	LEDS_PINS	LEDs Pins Descriptions
 *	@brief		This is the description of LEDS pins as used in TWI HAL
 *	@{
 */
#define LED0_PIN					TWI_PIN17	/**< Set LED0 to pin 17.*/
#define LED0_PORT					TWI_PORTA	/**< Define TWI_PORTA to be LED0 port.*/
#define LED1_PIN					TWI_PIN18	/**< Set LED1 to pin 18.*/
#define LED1_PORT					TWI_PORTA	/**< Define TWI_PORTA to be LED1 port.*/
#define LED2_PIN                    TWI_PIN19   /**< Set LED2 to pin 19.*/
#define LED2_PORT                   TWI_PORTA   /**< Define TWI_PORTA to be LED2 port.*/
#define LED3_PIN                    INV_PIN   /**< Set LED3 to pin 20.*/
#define LED3_PORT                   INV_PORT   /**< Define TWI_PORTA to be LED3 port.*/

#define ALERT_LED1_PORT             LED2_PORT
#define ALERT_LED1_PIN              LED2_PIN
#define ALERT_LED2_PORT             LED3_PORT
#define ALERT_LED2_PIN              LED3_PIN
#define ALERT_LED3_PORT             INV_PORT
#define ALERT_LED3_PIN              INV_PIN
#define ALERT_LED4_PORT             INV_PORT
#define ALERT_LED4_PIN              INV_PIN

#define LED0_IS_INVERTED			(1)
#define LED1_IS_INVERTED			(1)
#define LED2_IS_INVERTED			(1)
#define LED3_IS_INVERTED			(1)

/** @} *//*LEDS_PINS_*/

/* LCD Pins */
#define LCD_GDC0209_COM0_PORT		INV_PORT
#define LCD_GDC0209_COM1_PORT		INV_PORT
#define LCD_GDC0209_COM2_PORT		INV_PORT
#define LCD_GDC0209_COM3_PORT		INV_PORT
#define LCD_GDC0209_PIN5_PORT		INV_PORT
#define LCD_GDC0209_PIN6_PORT		INV_PORT
#define LCD_GDC0209_PIN7_PORT		INV_PORT
#define LCD_GDC0209_PIN8_PORT		INV_PORT
#define LCD_GDC0209_PIN9_PORT		INV_PORT
#define LCD_GDC0209_PIN10_PORT		INV_PORT
#define LCD_GDC0209_PIN11_PORT		INV_PORT
#define LCD_GDC0209_PIN12_PORT		INV_PORT
#define LCD_GDC0209_PIN13_PORT		INV_PORT
#define LCD_GDC0209_VDD_PORT		INV_PORT

#define LCD_GDC0209_COM0_PIN		INV_PIN
#define LCD_GDC0209_COM1_PIN		INV_PIN
#define LCD_GDC0209_COM2_PIN		INV_PIN
#define LCD_GDC0209_COM3_PIN		INV_PIN
#define LCD_GDC0209_PIN5_PIN		INV_PIN
#define LCD_GDC0209_PIN6_PIN		INV_PIN
#define LCD_GDC0209_PIN7_PIN		INV_PIN
#define LCD_GDC0209_PIN8_PIN		INV_PIN
#define LCD_GDC0209_PIN9_PIN		INV_PIN
#define LCD_GDC0209_PIN10_PIN		INV_PIN
#define LCD_GDC0209_PIN11_PIN		INV_PIN
#define LCD_GDC0209_PIN12_PIN		INV_PIN
#define LCD_GDC0209_PIN13_PIN		INV_PIN
#define LCD_GDC0209_VDD_PIN			INV_PIN

/**
 *	@defgroup	BTNS_PINS	Buttons Pins Descriptions
 *	@brief		This is the description of BTNS pins as used in TWI HAL
 *	@{
 */
#define PBTN0_PIN					TWI_PIN13	/**< Set PBTN0 to pin 13.*/
#define PBTN0_PORT					TWI_PORTA	/**< Define TWI_PORTa to be PBTN0 port.*/
#define PBTN1_PIN					TWI_PIN14	/**< Set PBTN1 to pin 14.*/
#define PBTN1_PORT					TWI_PORTA	/**< Define TWI_PORTA to be PBTN1 port.*/
#define PBTN2_PIN                   TWI_PIN15   /**< Set PBTN2 to pin 15.*/
#define PBTN2_PORT                  TWI_PORTA   /**< Define TWI_PORTA to be PBTN2 port.*/
#define PBTN3_PIN                   TWI_PIN16   /**< Set PBTN3 to pin 16.*/
#define PBTN3_PORT                  TWI_PORTA   /**< Define TWI_PORTA to be PBTN3 port.*/
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
#define ADC_CH2_VIN_PIN				TWI_PIN4	/**< Set ADC_CH2_VIN to pin 4. This is the AIN2.*/
#define ADC_CH2_VIN_PORT			TWI_PORTA	/**< Define TWI_PORTA to be ADC_CH2_VIN port. This is the AIN2.*/
#define ADC_CH3_VIN_PIN				TWI_PIN5	/**< Set ADC_CH3_VIN to pin 5. This is the AIN3.*/
#define ADC_CH3_VIN_PORT			TWI_PORTA	/**< Define TWI_PORTA to be ADC_CH3_VIN port. This is the AIN3.*/
#define ADC_CH4_VIN_PIN				TWI_PIN28	/**< Set ADC_CH4_VIN to pin 28. This is the AIN4.*/
#define ADC_CH4_VIN_PORT			TWI_PORTA	/**< Define TWI_PORTA to be ADC_CH4_VIN port. This is the AIN4.*/
#define ADC_CH5_VIN_PIN				TWI_PIN29	/**< Set ADC_CH5_VIN to pin 29. This is the AIN5.*/
#define ADC_CH5_VIN_PORT			TWI_PORTA	/**< Define TWI_PORTA to be ADC_CH5_VIN port. This is the AIN5.*/
#define ADC_CH6_VIN_PIN				TWI_PIN30	/**< Set ADC_CH6_VIN to pin 30. This is the AIN6.*/
#define ADC_CH6_VIN_PORT			TWI_PORTA	/**< Define TWI_PORTA to be ADC_CH6_VIN port. This is the AIN6.*/
#define ADC_CH7_VIN_PIN				TWI_PIN31	/**< Set ADC_CH7_VIN to pin 31. This is the AIN7.*/
#define ADC_CH7_VIN_PORT			TWI_PORTA	/**< Define TWI_PORTA to be ADC_CH7_VIN port. This is the AIN7.*/
/** @} *//*ADC_MODULE_PINS_*/

/**
 *  @defgroup   WIFI_MODULE_PINS    WIFI Module Pins Descriptions
 *  @brief      This is the description of WIFI module pins as used in TWI HAL
 *  @{
 */

#define WIFI_KM22_RESET_PORT		TWI_PORTA	/**< @brief  control port used for control km22    */
#define WIFI_KM22_RESET_PIN			TWI_PIN12	/**< @brief  km22 reset pin*/

#define WIFI_KM22_PWR_EN_PORT       INV_PORT    /**< @brief  Power enable port used for KM22 */
#define WIFI_KM22_PWR_EN_PIN        INV_PIN     /**< @brief  Power enable pin for KM22 */

#define WIFI_KM22_GPIO1_PORT		INV_PORT	/**< @brief   GPIO1 PORT*/
#define WIFI_KM22_GPIO1_PIN			INV_PIN 	/**< @brief  GPIO1 PIN*/

#define PRESSURE_SENSOR_BME280_CS_PORT		INV_PORT	/**<  Define TWI_PORTA to be CS port for pressure sensor.*/
#define PRESSURE_SENSOR_BME280_CS_PIN		INV_PIN	/**<  Define TWI_PIN1 to be CS pin for pressure sensor.*/

#define PRESSURE_SENSOR_BMP388_CS_PORT		TWI_PORTA 	/**<  Define TWI_PORTA to be CS port for pressure sensor.*/
#define PRESSURE_SENSOR_BMP388_CS_PIN		TWI_PIN29	/**<  Define TWI_PIN1 to be CS pin for pressure sensor.*/

#define PRESSURE_SENSOR_I2C_ADDR_PORT		TWI_PORTA	/**<  Define TWI_PORTA to be I2C address port for pressure sensor.*/
#define PRESSURE_SENSOR_I2C_ADDR_PIN		TWI_PIN20	/**<  Define TWI_PIN1 to be I2C address pin for pressure sensor.*/

/** @} *//* KM22 wifi module pins */

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

/** @} */   /*ACC_MODULE_PINS_*/

#define POD_I2C_DRIVER_RQST_PIN		TWI_PIN28	/**< Define PIN4 to be the pin for request pin of insulet_i2c_driver.*/
#define POD_I2C_DRIVER_RQST_PORT	TWI_PORTA	/**< Define PORTD to be the port for request pin of insulet_i2c_driver.*/

#define POD_I2C_DRIVER_ACK_PIN		TWI_PIN29	/**< Define PIN5 to be the pin for request pin of insulet_i2c_driver.*/
#define POD_I2C_DRIVER_ACK_PORT		TWI_PORTA	/**< Define PORTD to be the port for ack pin of insulet_i2c_driver.*/

#ifdef CUST1_DEMO

#define POD_INSULIN_ENABLE_PIN		TWI_PIN3	/**< Define PIN3 to be the pin for VETO signal (controling insulen delivery).*/
#define POD_INSULIN_ENABLE_PORT		TWI_PORTA	/**< Define PORTA to be the port for VETO signal (controling insulen delivery).*/

#define POD_INSULIN_PIEZO_0_PIN		TWI_PIN4	/**< Define PIN4 to be the pin for Alarm PIEZO signal 0.*/
#define POD_INSULIN_PIEZO_0_PORT	TWI_PORTA	/**< Define PORTA to be the port for for Alarm PIEZO signal 0.*/

#define POD_INSULIN_PIEZO_1_PIN		TWI_PIN5	/**< Define PIN5 to be the pin for Alarm PIEZO signal 1.*/
#define POD_INSULIN_PIEZO_1_PORT	TWI_PORTA	/**< Define PORTA to be the port for Alarm PIEZO signal 1.*/

#define POD_INSULIN_SW_1_PIN		TWI_PIN9	/**< Define PIN9 to be the pin for Insulin delivery first wire.*/
#define POD_INSULIN_SW_1_PORT		TWI_PORTA	/**< Define PORTA to be the port for Insulin delivery first wire.*/

#define POD_INSULIN_SW_2_PIN		TWI_PIN24	/**< Define PIN24 to be the pin for Insulin delivery second wire.*/
#define POD_INSULIN_SW_2_PORT		TWI_PORTA	/**< Define PORTA to be the port for Insulin delivery second wire.*/
#endif

#ifdef ENABLE_SYSTEM_RESET_MODULE
#define SYSTEM_RESET_PIN			PBTN1_PIN
#define SYSTEM_RESET_PORT			PBTN1_PORT

#endif

#define TWI_VAPE_LIBRARY_USB_DETECTION_PORT			INV_PORT
#define TWI_VAPE_LIBRARY_USB_DETECTION_PIN			INV_PIN

/* RFID Chip Pins Configuration */
#define RFID_DCI_PORT				INV_PORT
#define RFID_DCI_PIN				INV_PIN

#define CP240x_INT_PORT                TWI_PORTA
#define CP240x_INT_PIN                 TWI_PIN2
#define CP240x_CLK_PORT                TWI_PORTA
#define CP240x_CLK_PIN                 TWI_PIN27
#define CP240x_LED_PORT                TWI_PORTA
#define CP240x_LED_PIN                 TWI_PIN26
#define CP240x_RST_PORT                TWI_PORTA
#define CP240x_RST_PIN                 TWI_PIN25
#define CP240x_PWR_PORT                TWI_PORTA
#define CP240x_PWR_PIN                 TWI_PIN24

/* Si4455 Chip Pins Configuration */
#define SPI_SDN_PORT					TWI_PORTA
#define SPI_NIRQ_PORT					TWI_PORTA
#define SPI_NSEL_PORT					TWI_PORTA

#define SPI_NSEL_PIN					TWI_PIN29
#define SPI_NIRQ_PIN					TWI_PIN30
#define SPI_SDN_PIN						TWI_PIN31


#define DOOR_GPIO_PORT				TWI_PORTA
#define DOOR_GPIO_PIN			    TWI_PIN19    /**<LED1>*/

#define LIGHT_GPIO_PORT				TWI_PORTA
#define LIGHT_GPIO_PIN				TWI_PIN18    /**<LED2>*/

/*ULP project*/
#define ULP_INT_PIN          		TWI_PIN27	/**<Interrupt to BLE side (Input).*/
#define ULP_NFC_RST_PIN      		TWI_PIN31	/**<NFC reset signal (Output).*/
#define ULP_NFC_COMMON_PORT  		TWI_PORTA 

#define VIAL_EVENT_PORT 			TWI_PORTA
#define VIAL_EVENT_PIN				TWI_PIN18

/**
 *	@defgroup	EEPROM_CAT24CXX_PINS Pins Descriptions
 *	@brief		This is the description of EEPROM_CAT24CXX pins as used in TWI HAL
 *	@{
 */

#define EEPROM_CAT24CXX_WP_PORT                 (TWI_PORTA)
#define EEPROM_CAT24CXX_WP_PIN                  (TWI_PIN0)

#define EEPROM_CAT24CXX_A0_PORT                 (INV_PORT)
#define EEPROM_CAT24CXX_A0_PIN                  (INV_PIN)

#define EEPROM_CAT24CXX_A1_PORT                 (INV_PORT)
#define EEPROM_CAT24CXX_A1_PIN                  (INV_PIN)

#define EEPROM_CAT24CXX_A2_PORT                 (INV_PORT)
#define EEPROM_CAT24CXX_A2_PIN                  (INV_PIN)


#define EEPROM_HE24CXX_A0_PORT                 (INV_PORT)
#define EEPROM_HE24CXX_A0_PIN                  (INV_PIN)
#define EEPROM_HE24CXX_A1_PORT                 (INV_PORT)
#define EEPROM_HE24CXX_A1_PIN                  (INV_PIN)
#define EEPROM_HE24CXX_A2_PORT                 (INV_PORT)
#define EEPROM_HE24CXX_A2_PIN                  (INV_PIN)
#define EEPROM_HE24CXX_WP_PORT                 (INV_PORT)
#define EEPROM_HE24CXX_WP_PIN                  (INV_PIN)
 

 /** @} *//*EEPROM_CAT24CXX_PINS*/
#define PWM0_PORT                              (INV_PORT)
#define PWM0_PIN                               (INV_PIN)

/**
* @defgroup	BUZZER_PINS	Buzzer Pins Descriptions
* @brief    This is the description of BUZZER pins as used in TWI HAL
*/
#define BUZZER_PORT							INV_PORT 	/**< Define PORTA to be BUZZER port.*/
#define BUZZER_DIN_PIN						INV_PIN     /**< Set BUZZER_IN_PIN to invalid pin.*/
#define BUZZER_EN1_PIN						INV_PIN     /**< Set BUZZER_EN1_PIN to invalid pin.*/
#define BUZZER_EN2_PIN						INV_PIN     /**< Set BUZZER_EN2_PIN to invalid pin.*/
/** @} */	/*BUZZER_PINS*/

#define PRESSURE_SENSOR_HW_EN_PORT          INV_PORT 	/**<  Define TWI_PORTA to be Enable port for pressure sensor.*/
#define PRESSURE_SENSOR_HW_EN_PIN           INV_PIN     /**<  Define TWI_PIN10 to be Enable pin for pressure sensor.*/

#define SEAL_STATUS_PORT                    TWI_PORTA 	/**<  Define TWI_PORTA to be seal port.*/
#define SEAL_STATUS_PIN                     TWI_PIN20   /**<  Define TWI_PIN20 to be seal pin.*/

#define CART_PIN_PULL_TYPE   				CART_PIN_PULL_UP
#define CART_PIN_NUM 						CART_PIN_13



/**
* @defgroup	IPILL_PINS Dispenser Pins Descriptions
* @brief    This is the description of pins needed for iPill Dispenser project
*/
#define	ENCODER_A_PIN		TWI_PIN25
#define	ENCODER_A_PORT		TWI_PORTA

#define	ENCODER_B_PIN		TWI_PIN23
#define	ENCODER_B_PORT		TWI_PORTA

#define	MOTOR_ENABLE_PIN		TWI_PIN11
#define	MOTOR_ENABLE_PORT		TWI_PORTA

#define	MOTOR_PHASE_PIN			TWI_PIN12
#define	MOTOR_PHASE_PORT		TWI_PORTA

#define	MOTOR_SLEEP_PIN			TWI_PIN24
#define	MOTOR_SLEEP_PORT		TWI_PORTA

#define ROTATION_SW1_PIN        TWI_PIN26
#define	ROTATION_SW1_PORT		TWI_PORTA

#define ROTATION_SW2_PIN        TWI_PIN27
#define	ROTATION_SW2_PORT		TWI_PORTA

#define ALIGN_PBTN_PIN          PBTN0_PIN
#define ALIGN_PBTN_PORT         PBTN0_PORT 

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
/** @} */	/*IPILL_PINS*/


#if defined(IPILL_DISPENSER) && defined(USE_LEDS_TESTING)
 /**
 *	@defgroup	SOLENOID_CTRL_PINS	Pill Destruction Pins Descriptions
 *	@brief		This is the description of soleniod control pin as used in TWI HAL
 *	@{
 */
#define SOLENOID_CTRL_PORT			        LED3_PORT	        /**< Define TWI_PORTA to be soleniod control port.*/
#define SOLENOID_CTRL_PIN				    LED3_PIN           /**< Set soleniod control pin  to TWI_PIN17.*/  
/** @} *//*SOLENOID_CTRL_PINS_*/

 /**
 *	@defgroup	MOTOR_IN_PINS	Pill Destruction Pins Descriptions
 *	@brief		This is the description of motor control pin as used in TWI HAL
 *	@{
 */
#define MOTOR_IN1_PORT			            INV_PORT	        /**< Define INV_PORT to be MOTOR_IN1 port.*/
#define MOTOR_IN1_PIN				        INV_PIN             /**< Set MOTOR_IN1 pin  to INV_PIN.*/  
#define MOTOR_IN2_PORT			            INV_PORT	        /**< Define INV_PORT to be MOTOR_IN2 port.*/
#define MOTOR_IN2_PIN				        INV_PIN             /**< Set MOTOR_IN2 pin  to INV_PIN.*/  
/** @} *//*MOTOR_IN_PINS_*/

/**
* @defgroup	BUZZER_PINS	Buzzer Pins Descriptions
* @brief    This is the description of BUZZER pins as used in TWI HAL
*/
#define BUZZER_EN_PORT					    LED2_PORT 	       /**< Define INV_PORT to be BUZZER port.*/
#define BUZZER_EN_PIN				        LED2_PIN           /**< Set BUZZER_EN_PIN to invalid pin.*/
/** @} */	/*BUZZER_PINS*/
#endif

#if defined (BLE_ALIGN_TAG)
 /**
 *	@defgroup	PH_PINS	Pill Destruction Pins Descriptions
 *	@brief		This is the description of pH sensor pins as used in TWI HAL
 *	@{
 */
#define PH_ADC_VREF_PORT		    	    ADC_CH0_VIN_PORT	        /**< Define ADC_CH0_VIN_PORT to be pH Vref port.*/
#define PH_ADC_VREF_PIN				        ADC_CH0_VIN_PIN             /**< Set pH Vref pin  to ADC_CH0_VIN_PIN.*/ 
#define PH_ADC_VIN_PORT			    	    ADC_CH2_VIN_PORT	        /**< Define ADC_CH2_VIN_PORT to be pH Vin.*/
#define PH_ADC_VIN_PIN				        ADC_CH2_VIN_PIN             /**< Set pH Vin pin to ADC_CH2_VIN_PIN.*/ 
#define PH_REF_ADC_VIN_PORT			        ADC_CH3_VIN_PORT	        /**< Define ADC_CH3_VIN_PORT to be pH ref Vin port.*/
#define PH_REF_ADC_VIN_PIN		            ADC_CH3_VIN_PIN             /**< Set pH ref Vin pin to ADC_CH3_VIN_PIN.*/ 
/** @} *//*PH_PINS_*/    
#endif


#if defined(IPILL_DISPENSER) 
 /**
 *	@defgroup	RTC_PINS	RTC Pins Descriptions
 *	@brief		This is the description of RTC pins as used in TWI HAL
 *	@{
 */
#define RTC_INT_PORT			    	    TWI_PORTA	        /**< Define INV_PORT to be RTC interrupt port.*/
#define RTC_INT_PIN				            TWI_PIN24           /**< Set Accelerometer interrupt to INV_PIN.*/  

#define RTC_EN_PORT			    	        INV_PORT	        /**< Define INV_PORT to be RTC interrupt port.*/
#define RTC_EN_PIN				            INV_PIN             /**< Set Power enable pin to INV_PIN.*/  

#ifdef ADVANCE_TIME_HACK
#define TIME_HACK_PORT			    	    TWI_PORTA
#define TIME_HACK_PIN   		            TWI_PIN13
#endif
/** @} *//*RTC_PINS_*/

 /**
 *	@defgroup	PILL_DESTRUCTION_PINS	Pill Destruction Pins Descriptions
 *	@brief		This is the description of RTC pins as used in TWI HAL
 *	@{
 */
#define PILL_DESTRUCTION_1_PORT			    INV_PORT	        /**< Define INV_PORT to be Pill Destruction 1 port.*/
#define PILL_DESTRUCTION_1_PIN			    INV_PIN             /**< Set Pill Destruction 1 pin  to INV_PIN.*/ 
#define PILL_DESTRUCTION_2_PORT			    INV_PORT	        /**< Define INV_PORT to be Pill Destruction 2 port.*/
#define PILL_DESTRUCTION_2_PIN		        INV_PIN             /**< Set Pill Destruction 2 pin to INV_PIN.*/   
/** @} *//*PILL_DESTRUCTION_PINS_*/

 /**
 *	@defgroup	LIGHT_PINS	Pill Destruction Pins Descriptions
 *	@brief		This is the description of light sensor pins as used in TWI HAL
 *	@{
 */
#define LIGHT_FET_1_PORT			    	INV_PORT	        /**< Define INV_PORT to be light mosfet 1 port.*/
#define LIGHT_FET_1_PIN				        INV_PIN             /**< Set flex pcb 1 pin  to INV_PIN.*/ 
#define LIGHT_FET_2_PORT			    	INV_PORT	        /**< Define INV_PORT to be light mosfet 2 port.*/
#define LIGHT_FET_2_PIN				        INV_PIN             /**< Set flex pcb 2 pin to INV_PIN.*/ 
/** @} *//*LIGHT_PINS_*/
#endif

#endif /* _PCA10040_PINS_H_ */
