/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
 *   @file       Platform_defines.h
 *   @brief      This file contains Specific defines for each platform.
 */

#ifndef _PLATFORM_DEFINES_H_
#define _PLATFORM_DEFINES_H_

#include "nrf.h"
#include "ble_hci.h"
#include "twi_types.h"
#include "platform_pins.h"
#include "platform_cfg.h"
#include "app_util_platform.h"
#include "ble.h"
#include "nrf_delay.h"

#define UART_FC_ENABLE			(0)

#define PLATFORM_MAX_FRAGMENT_LENGTH				128

#define PLATFORM_PORT_POS       					5
#define PLATFORM_PIN_MASK       					0x1F
#define PLATFORM_PORTS_COUNT						1
#define PLATFORM_PINS_COUNT							32
#define PLATFORM_TOTAL_PINS_COUNT					32

#if defined NRF51
	#define PLATFORM_ADC_VIN_CH_NUM					6
	#define PLATFORM_HAL_RTC_TIMERS_COUNT			1
#elif defined NRF52
	#define PLATFORM_ADC_VIN_CH_NUM					8
	#define PLATFORM_HAL_RTC_TIMERS_COUNT			2
	#define NRF52_DIFFERENT_FREQ_PWM_COUNT			3
#else
	#error Need to define either NRF51 or NRF52.
#endif

#define PLATFORM_ADC_VREF_CH_NUM					2
#define PLATFORM_UART_CHANNELS_NUM					1
#define PLATFORM_SPI_MASTER_CHANNELS_NUM			2
#define PLATFORM_SPI_SLAVE_CHANNELS_NUM				1
#define PLATFORM_I2C_MASTER_CHANNELS_NUM			2
/*TODO: If there is more than one SWI, a flag needs to be used to indicate that it is inside SWI_IRQ instead of the flag used in timer_mgmt.c.*/
#define PLATFORM_SWI_CHANNELS_NUM					3
#define PLATFORM_TIMER_UTILS_SWI_CHANNEL			0
#define PLATFORM_FLASH_HAL_SWI_CHANNEL				1
#define PLATFORM_CRITICAL_VAR_UTILS_SWI_CHANNEL		2

#define PLATFORM_PULLED_UP_BUTTON

#define TIMER_SAFE_MARGIN							5

#define PLATFORM_HW_TIMER_MAX_CNTR_VAL				RTC_COUNTER_COUNTER_Msk - TIMER_SAFE_MARGIN

#define PLATFORM_DEBOUNCE_DELAY_MS					0

#define PLATFORM_UART_BAUD_1200K                    UART_BAUDRATE_BAUDRATE_Baud1200
#define PLATFORM_UART_BAUD_2400K                    UART_BAUDRATE_BAUDRATE_Baud2400
#define PLATFORM_UART_BAUD_4800K                    UART_BAUDRATE_BAUDRATE_Baud4800
#define PLATFORM_UART_BAUD_9600K                    UART_BAUDRATE_BAUDRATE_Baud9600
#define PLATFORM_UART_BAUD_14400K                   UART_BAUDRATE_BAUDRATE_Baud14400
#define PLATFORM_UART_BAUD_19200K                   UART_BAUDRATE_BAUDRATE_Baud19200
#define PLATFORM_UART_BAUD_28800K                   UART_BAUDRATE_BAUDRATE_Baud28800
#define PLATFORM_UART_BAUD_38400K                   UART_BAUDRATE_BAUDRATE_Baud38400
#define PLATFORM_UART_BAUD_57600K                   UART_BAUDRATE_BAUDRATE_Baud57600
#define PLATFORM_UART_BAUD_76800K                   UART_BAUDRATE_BAUDRATE_Baud76800
#define PLATFORM_UART_BAUD_115200K                  UART_BAUDRATE_BAUDRATE_Baud115200
#define PLATFORM_UART_BAUD_230400K                  UART_BAUDRATE_BAUDRATE_Baud230400
#define PLATFORM_UART_BAUD_250000K                  UART_BAUDRATE_BAUDRATE_Baud250000
#define PLATFORM_UART_BAUD_460800K                  UART_BAUDRATE_BAUDRATE_Baud460800
#define PLATFORM_UART_BAUD_921600K                  UART_BAUDRATE_BAUDRATE_Baud921600
#define PLATFORM_UART_BAUD_1M                       UART_BAUDRATE_BAUDRATE_Baud1M

#define PLATFORM_SUART_STOP_DELAY					(10)

#define PLATFORM_I2C_SCL_100K                       TWI_FREQUENCY_FREQUENCY_K100
#define PLATFORM_I2C_SCL_250K                       TWI_FREQUENCY_FREQUENCY_K250
#define PLATFORM_I2C_SCL_400K                       TWI_FREQUENCY_FREQUENCY_K400

#define PLATFORM_GET_I2C_PULL_CFG(ch)				((ch)? I2C1_PULL_TYPE:I2C0_PULL_TYPE)

#define PLATFORM_SPI_SCK_125K                       SPI_FREQUENCY_FREQUENCY_K125
#define PLATFORM_SPI_SCK_250K                       SPI_FREQUENCY_FREQUENCY_K250
#define PLATFORM_SPI_SCK_500K                       SPI_FREQUENCY_FREQUENCY_K500
#define PLATFORM_SPI_SCK_1M                         SPI_FREQUENCY_FREQUENCY_M1
#define PLATFORM_SPI_SCK_2M                         SPI_FREQUENCY_FREQUENCY_M2
#define PLATFORM_SPI_SCK_4M                         SPI_FREQUENCY_FREQUENCY_M4
#define PLATFORM_SPI_SCK_8M                         SPI_FREQUENCY_FREQUENCY_M8

#define PLATFORM_GET_ABS_PIN_INDEX(u8_port, u8_pin) (u8_pin)

#define PLATFORM_ADC_INTERNAL_VREF_MV               (1200)

#define PLATFORM_ADC_GET_VIN_CH(u8_port, u8_pin)    ((((u8_port) << 3) + (u8_pin)) - 1)
#define PLATFORM_ADC_GET_VIN_PORT(u8_channel)       (ADC_CH0_VIN_PORT)

#if defined (NRF51)
	#define PLATFORM_ADC_GET_VIN_PIN(u8_channel)        (ADC_CH0_VIN_PIN + u8_channel)
#elif defined (NRF52)
	#define PLATFORM_ADC_GET_VIN_PIN(u8_channel)        (((u8_channel) < 4) ? (ADC_CH0_VIN_PIN + u8_channel) : (ADC_CH0_VIN_PIN + u8_channel + 22))
#else
	#error Need to define either NRF51 or NRF52.
#endif

#define PLATFORM_ADC_GET_VREF_CH(u8_port, u8_pin)   ((((u8_port) << 3) + (u8_pin)) >> 2)
#define PLATFORM_ADC_GET_VREF_PORT(u8_channel)      (ADC_VREF_CH0_PORT)
#define PLATFORM_ADC_GET_VREF_PIN(u8_channel)       (((u8_channel) << 1) + ((u8_channel) << 2))

/*	Min and Maximum allowed transmission powers */
#if defined (NRF51)
	#define	PLATFORM_BLE_MIN_TX_PWR						-30			/**< @brief This is the minimum transmission power */
#elif defined (NRF52)
	#define	PLATFORM_BLE_MIN_TX_PWR						-40			/**< @brief This is the minimum transmission power */
#endif

#define	PLATFORM_BLE_MAX_TX_PWR		 	 			4			/**< @brief This is Radio transmit power in dBm, This value will limit the range of BLE.*/

/* The advertising interval for connect-able advertisement in milliseconds. This value can vary between 0x0020 and 0x4000 in 0.625 ms units (20ms to 10.24s). */
#define	PLATFORM_BLE_MIN_ADV_INT_MS					20					/* 20 ms */
#define	PLATFORM_BLE_MAX_ADV_INT_MS					10000				/* 10 sec */

#if defined (NRF51)
/* accepted values are -30, -20, -16, -12, -8, -4, 0, and 4 dBm */
#define IS_WITHIN_TX_PWR_RANGE(tx_pwr)				((tx_pwr == -30) || (tx_pwr == -20) || (tx_pwr == -16) ||	\
													 (tx_pwr == -12) || (tx_pwr == -8)	|| (tx_pwr == -4)  ||	\
													 (tx_pwr == 0)	 ||	(tx_pwr == 4))
#elif defined (NRF52)
/* accepted values are -40, -20, -16, -12, -8, -4, 0, 3, and 4 dBm */
#define IS_WITHIN_TX_PWR_RANGE(tx_pwr)				((tx_pwr == -40) || (tx_pwr == -20) || (tx_pwr == -16) ||	\
													 (tx_pwr == -12) || (tx_pwr == -8)	|| (tx_pwr == -4)  ||	\
													 (tx_pwr == 0)	 ||	(tx_pwr == 3)	|| (tx_pwr == 4))
#endif


#define AFTER_MANUFACTURING_BLE_TX_PWR				PLATFORM_BLE_MIN_TX_PWR

#define IS_WITHIN_ADV_INT_RANGE(adv_int)			((adv_int>=PLATFORM_BLE_MIN_ADV_INT_MS) &&	(adv_int<=PLATFORM_BLE_MAX_ADV_INT_MS)	)

/* GATT Write Operations
 */
#define PLATFORM_BLE_GATT_OP_INVALID  							BLE_GATT_OP_INVALID
#define PLATFORM_BLE_GATT_OP_WRITE_REQ							BLE_GATT_OP_WRITE_REQ
#define PLATFORM_BLE_GATT_OP_WRITE_CMD							BLE_GATT_OP_WRITE_CMD

#ifdef nordic_sdk_16_0_0
#define PLATFORM_BLE_GAP_ADV_TYPE_ADV_IND						BLE_GAP_ADV_TYPE_CONNECTABLE_SCANNABLE_UNDIRECTED
#else
#define PLATFORM_BLE_GAP_ADV_TYPE_ADV_IND						BLE_GAP_ADV_TYPE_ADV_IND
#endif
#define PLATFORM_BLE_GAP_EVT_BASE								BLE_GAP_EVT_BASE
#define PLATFORM_BLE_CONN_HANDLE_INVALID						BLE_CONN_HANDLE_INVALID
#define	PLATFORM_BLE_GAP_AD_TYPE_MANFCTR_SPECIFIC_DATA			BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA
#define	PLATFORM_BLE_GAP_AD_TYPE_COMPLETE_NAME					BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME
#define	PLATFORM_BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE	BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE

/* BLE Disconnect Reasons
 */
#define PLATFORM_BLE_DISCON_INVALID_CMD_PARAMETERS	        BLE_HCI_STATUS_CODE_INVALID_BTLE_COMMAND_PARAMETERS
#define PLATFORM_BLE_DISCON_REMOTE_USER						BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION
#define PLATFORM_BLE_DISCON_LOCAL_HOST						BLE_HCI_LOCAL_HOST_TERMINATED_CONNECTION
#define PLATFORM_BLE_DISCON_RMTE_DEV_PWR_OFF				BLE_HCI_REMOTE_DEV_TERMINATION_DUE_TO_POWER_OFF
#define PLATFORM_BLE_DISCON_REMOTE_DEV_LOW_RES		BLE_HCI_REMOTE_DEV_TERMINATION_DUE_TO_LOW_RESOURCES
#define PLATFORM_BLE_DISCON_TIMEOUT							BLE_HCI_CONNECTION_TIMEOUT
#define PLATFORM_BLE_DISCON_FAILED_EST	                    BLE_HCI_CONN_FAILED_TO_BE_ESTABLISHED



#if defined (NRF51)
	#define PLATFORM_GET_CHIP_ID()									(NRF_FICR->CONFIGID)
#elif defined (NRF52)
	#define PLATFORM_GET_CHIP_ID()									(NRF_FICR->INFO.VARIANT)
#endif


/* Timer Channels */
#define TM_TIMER_CH							TWI_TIMER_CH0		/* Timer Channel 0 is used for Timer Management unit */
#if defined (NRF52)
	#define LOGGER_TIMER_CH					TWI_TIMER_CH1		/* Timer Channel 1 is used for RHP Logger */
#endif

/*-*********************************************************/
/*- NORDIC FLASH MEMORY PARAMETERS ------------------------*/
/*-*********************************************************/
/* Define parameters for flash memory */



/* Define parameters for flash memory */
/**< @brief This MACRO depends on ::FLASH_PAGE_SIZE MACRO, as the shift depends on the size of the flash page */
#if defined (NRF51)		/* Page Size = 1024 */
	#define INTERNAL_FLASH_PAGE_SIZE_SHIFT		(10)
	/* define number of reserved pages suppose to be multiple of 2 */
#elif defined (NRF52)	/* Page Size = 4096 */
	#define INTERNAL_FLASH_PAGE_SIZE_SHIFT		(12)
	/* define number of reserved pages suppose to be multiple of 2 */
#endif
#define FLASH_QUEUE_SIZE                (50)                                                        /**< @brief The queue size, Multiple of 2 */

#define OTA_CODE_SIZE                   (160 * 1024)                                                /**< @breif max OTA_APP size is 160KBytes */
#define OTA_CODE_BANK_PAGES             (OTA_CODE_SIZE/INTERNAL_FLASH_PAGE_SIZE)                    /**< @brief The number of pages per CODE-BANK area*/
#define APP1_BASE_ADDR                  (0x26000)                                                   /**< must start at a flash page start address*/
#define APP2_BASE_ADDR                  (APP1_BASE_ADDR + OTA_CODE_SIZE)
#if defined(OTA_APP1) || defined(OTA_APP_WITH_AL)
    #define NUM_FREE_PAGES_CODE_DATA     (OTA_CODE_BANK_PAGES + (OTA_CODE_BANK_PAGES - ((twi_u32)__etext/INTERNAL_FLASH_PAGE_SIZE)))                                        /**< @brief Macro indicates the number of free pages betweenlast address of the code & the user data in the flash */
#elif defined(OTA_APP2)
    #define NUM_FREE_PAGES_CODE_DATA     (3)
#else
    #define NUM_FREE_PAGES_CODE_DATA     (3)
#endif

#define FREE_SPACE_CODE_DATA        (NUM_FREE_PAGES_CODE_DATA * INTERNAL_FLASH_PAGE_SIZE)       /**< @brief Macro indicates the memory free space between
                                                                                                last address of the code & the user data in the flash */

#define INTERNAL_FLASH_NUM_OF_PAGES (NRF_FICR->CODESIZE)                                        /**< @brief Number of pages for the flash memory */

#define INTERNAL_FLASH_END_ADDRESS  (INTERNAL_FLASH_PAGE_SIZE * INTERNAL_FLASH_NUM_OF_PAGES)    /**< @brief End address of the flash memory */

#define INTERNAL_FLASH_PAGE_SIZE    (NRF_FICR->CODEPAGESIZE)                                    /**< @brief Flash memory page size (1024 for nrf51, 4096 for nrf52).
                                                                                                 If this value is changed, You must change the value of ::FLASH_PAGE_SIZE_SHIFT */
#define WORD_SIZE				    (4)

#if (WORD_SIZE == 4)
	#define WORD_SHIFT_NUM							(2)
	#define CHECK_ADDRESS_ALIGNED_AS_WORD(address)	(address & 3)				/* (address % WORD_SIZE) */
	#define CHECK_AS_WORD_ALIGNED(var)				(var & 3)					/* (var % WORD_SIZE) */
#elif (WORD_SIZE == 2)
	#define WORD_SHIFT_NUM							(1)
	#define CHECK_ADDRESS_ALIGNED_AS_WORD(address)	(address & 1)				/* (address % WORD_SIZE) */
	#define CHECK_AS_WORD_ALIGNED(var)				(var & 1)					/* (var % WORD_SIZE) */
#else
	#error "Please, define the 'SHIFT_NUM' & 'CHECK_ADDRESS_ALIGNED_AS_WORD' for the WORD_SIZE != 2 or 4 "
#endif

#if defined (NRF51)		/* CPU Clock Speed 16 MHz */
	#define TWI_LOOP_TIME_OUT					(20000UL)
	#define TWI_FLASH_ERASE_TIME_OUT			(0xFFFFFUL)
#elif defined (NRF52)	/* CPU Clock Speed 64 MHz */
	#define TWI_LOOP_TIME_OUT					(80000UL)
	#define TWI_FLASH_ERASE_TIME_OUT			(0xEFFFFUL)
#endif

/***********************************************************************/

#define TWI_DELAY_US(u32_us)	nrf_delay_us(u32_us)
#define TWI_DELAY_MS(u32_ms)	do							\
								{							\
									twi_u32 u32_delay;		\
															\
									u32_delay = u32_ms;		\
									while (u32_delay != 0)	\
									{						\
									u32_delay--;			\
									nrf_delay_us(999);		\
									}						\
								}while (0)



static __inline void  TWI_SOFTWARE_RESET_FUNC (void)  
{
#ifndef TWI_CEEDLING_TEST
    volatile unsigned int* _aircr = (volatile unsigned int* )(0xE000ED0C);	
	*_aircr = (0x05FAul<<16) | (0x4);	
#endif    
}

/**
 *	@brief			This macro is used to reset the system
*/
#define TWI_SOFTWARE_RESET()	    do{\
                                        TWI_SOFTWARE_RESET_FUNC ();\
                                        while (1){}\
                                      }while(0)

/**
 *	@brief			This macro is used to raise system error and restart system
*/

#define RAISE_SYSTEM_ERROR(sys_err)													\
do 																					\
{ 																					\
	TWI_LOGGER_ERR("**********************************************");				\
	TWI_LOGGER_ERR("SYS ERR %d,Fn %s,Line %d\n",sys_err,__FUNCTION__,__LINE__);		\
	TWI_LOGGER_ERR("**********************************************");				\
	TWI_SOFTWARE_RESET();															\
}while(0)																			\


/*****************************************************************************************************************/
/*
*	@function	 	twi_platform_init
*/
void twi_platform_init(void);


#endif  /* _PLATFORM_DEFINES_H_ */
