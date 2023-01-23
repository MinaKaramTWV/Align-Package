/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_retval.h
*   @brief      This file contains TWI functions' return values.
*/

#ifndef _TWI_RETVAL_H_
#define _TWI_RETVAL_H_


/**
*   @defgroup twi_retval_group TWI return values
*   This is the definition of TWI return values. All TWI function's return values SHALL follow this group.
*   @{
*/

/**
*   @defgroup twi_common_retval_group Common return values
*   @{
*/
/**
*   @brief  This return value indicate that the function could run successfully and it returns no errors.
*/
#define TWI_SUCCESS                             		0

/**
*   @brief  This return value indicate that the selected resource not found in the platform.
*/
#define TWI_ERROR_RESOURCE_NOT_FOUND            		-1

/**
*   @brief  This return value indicate that the function tries to use an uninitialized module.
*/
#define TWI_ERROR_NOT_INITIALIZED						-2

/**
*   @brief  This return value indicate that you attempted to initialize an already initialized module.
*/
#define TWI_ERROR_ALREADY_INITIALIZED					-3

/**
*   @brief  This return value indicate that you attempted to de-initialize an already not initialized module.
*/
#define TWI_ERROR_ALREADY_DEINITIALIZED					-4

/**
*   @brief  This return value indicate that the function isn't used properly.
*/
#define TWI_ERROR_INVALID_ARGUMENTS             		-5

/**
*   @brief  This return value indicate that you attempted to access an already reserved resource.
*/
#define TWI_ERROR_ALREADY_RESERVED              		-6

/**
*   @brief  This return value indicate that you attempted to release an already released resource.
*/
#define TWI_ERROR_ALREADY_RELEASED              		-7

/**
*   @brief  This return value indicate that there is no enough room to achieve the task.
*/
#define TWI_ERROR_NO_ENOUGH_ROOM                		-8

/**
*   @brief  This return value indicate that the resource is configured in
*           a way that the function can NOT perform the required action.
*/
#define TWI_ERROR_INVALID_CONFIG                		-9

/**
*   @brief  This return value indicate that the resource HW doesn't respond in the time frame.
*/
#define TWI_ERROR_HW_TIMEOUT                    		-10

/**
*   @brief  This return value indicate that the function has error.
*/
#define TWI_ERROR		                        		-11

/**
*   @brief  This return value indicate that the function couldn't achieve the task due to an internal error.
*/
#define TWI_ERROR_INTERNAL_ERROR                		-12

/**
*   @brief  This return value indicate that the function doesn't achieve the task because it is already achieved.
*/
#define TWI_ERROR_ALREADY_SET      	          			-13

/**
*   @brief  This return value indicates not supported feature by the code.
*/
#define TWI_ERROR_NOT_SUPPORTED_FEATURE					-14

/**
*   @brief  This return value indicates that HW cant communicate with it.
*/
#define TWI_ERROR_HW_NOT_FOUND							-15

/**
*   @brief  This return value indicates that required task is not finished yet.
*/
#define TWI_ERROR_NOT_FINISHED_YET						-16

/**
*   @brief  This return value indicates that required task is not ready yet.
*/
#define TWI_ERROR_NOT_READY_YET							-17

/**
*   @brief  This return value indicates that required can not supported in the current state.
*/
#define TWI_ERROR_INVALID_STATE							-18

/**
*   @brief  This return value indicates that HW is busy and can not handle the current request at the current time.
*/
#define TWI_ERROR_BUSY									-19

/**
*   @brief  This return value indicates that BUF is locked and can not used the current request at the current time.
*/
#define TWI_ERROR_BUF_IS_LOCKED							-20

/**
*   @brief  scan already in progress
*/
#define TWI_ERROR_SCAN_INPROGRESS						-21

/**
*   @brief  Scan already stopped
*/
#define TWI_ERROR_SCAN_STOPPED							-22
/**
*   @brief  error null pointer
*/
#define TWI_ERROR_NULL_PV								-23
/**
*   @brief  error send in progress
*/
#define TWI_ERROR_SEND_INPROGRESS						-24

/**	
*	@brief  This return value indicates that Testing has a failure.
*/
#define TWI_ERROR_TESTING_FAILURE						-25

/**
*	@brief  This return value indicates that Length is invalid.
*/
#define TWI_ERROR_INVALID_LEN							-26

/**
*	@brief  This return value indicates that CRC is invalid.
*/
#define TWI_ERROR_INVALID_CRC							-27

/**
*	@brief  This return value indicates that session is closed.
*/
#define TWI_ERROR_SESSION_CLOSED						-28

/**
*	@brief  This return value indicates that timer already fired
*/
#define TWI_ERROR_ALREADY_FIRED 				        -29

/** @} */   /*twi_common_retval_group*/

/**
*   @defgroup twi_common_i2c_master_retval_group I2C module return values
*   @{
*/
/**
*   @brief  I2C return values base.
*/
#define TWI_ERROR_I2C_BASE                      		(-100)

/**
*   @brief  I2C channel is a free to use channel.
*/
#define TWI_I2C_FREE_CHANNEL                    		(TWI_ERROR_I2C_BASE - 1)

/**
*   @brief  I2C channel is a reserved to use channel.
*/
#define TWI_I2C_RESERVED_CHANNEL                		(TWI_ERROR_I2C_BASE - 2)

/**
*   @brief  I2C Slave is not ACK.
*/
#define TWI_ERROR_I2C_SLAVE_NACK                		(TWI_ERROR_I2C_BASE - 3)

/**
*   @brief  I2C Slave is not ACK.
*/
#define TWI_ERROR_I2C_SLAVE_ADDR_NACK           		(TWI_ERROR_I2C_BASE - 4)

/**
*   @brief  I2C Slave is not ACK.
*/
#define TWI_ERROR_I2C_SLAVE_DATA_NACK    				(TWI_ERROR_I2C_BASE - 5)

/**
*   @brief  I2C Error in Hardware setup.
*/
#define TWI_I2C_HW_INIT_ERROR							(TWI_ERROR_I2C_BASE - 6)

/**
*   @brief  I2C Error in Arbitration.
*/
#define TWI_I2C_ARB_LOSS_ERROR							(TWI_ERROR_I2C_BASE - 7)

/**
*   @brief  I2C Error in start or stop conditions.
*/
#define TWI_I2C_STRSTP_ERROR							(TWI_ERROR_I2C_BASE - 8)

/**
*   @brief  I2C state is not expected.
*/
#define TWI_I2C_UNEXPECTED_STATE						(TWI_ERROR_I2C_BASE - 9)

/** @} */   /*twi_common_i2c_master_retval_group*/

/**
*   @defgroup twi_common_spi_master_retval_group SPI module return values
*   @{
*/
/**
*   @brief  SPI return values base.
*/
#define TWI_ERROR_SPI_BASE                      		(-200)

/**
*   @brief  SPI channel is a free to use channel.
*/
#define TWI_SPI_FREE_CHANNEL                    		(TWI_ERROR_SPI_BASE -1)

/**
*   @brief  SPI channel is a reserved to use channel.
*/
#define TWI_SPI_RESERVED_CHANNEL                		(TWI_ERROR_SPI_BASE -2)

/**
*   @brief  SPI Master Error in Hardware setup.
*/
#define TWI_SPI_HW_INIT_ERROR							(TWI_ERROR_SPI_BASE -3)

/** @} */   /*twi_common_spi_master_retval_group*/

/**
*   @defgroup twi_common_uart_retval_group UART module return values
*   @{
*/

/**
*   @brief  UART return values base.
*/
#define TWI_ERROR_UART_BASE                     		(-300)

/**
*   @brief  UART channel is a free to use channel.
*/
#define TWI_UART_FREE_CHANNEL                   (TWI_ERROR_UART_BASE -1)

/**
*   @brief  UART channel is a reserved to use channel.
*/
#define TWI_UART_RESERVED_CHANNEL               (TWI_ERROR_UART_BASE -2)

/**
*   @brief  UART Error in Hardware setup.
*/
#define TWI_UART_HW_INIT_ERROR					(TWI_ERROR_UART_BASE -3)

/**
*   @brief  UART mode is invalid.
*/
#define TWI_UART_INVALID_MODE               (TWI_ERROR_UART_BASE -4)
/** @} */   /*twi_common_uart_retval_group*/

/**
*   @defgroup twi_common_spi_comm_slave_retval_group SPI_COMM module return values
*   @{
*/

/**
*   @brief  SPI_COMM return values base.
*/
#define TWI_ERROR_SPI_COMM_BASE                 		(-400)

/**
*   @brief  The read DATA register has been completely sent to the master and it is safe to re-assign it to a new data.
*/
#define TWI_SPI_COMM_CTS                        		(TWI_ERROR_SPI_COMM_BASE - 1)

/**
*   @brief  The read DATA register has NOT been completely sent to the master. If you re-assign it, the data will be lost before sent to the master.
*/
#define TWI_SPI_COMM_NCTS                       		(TWI_ERROR_SPI_COMM_BASE - 2)

/**
*   @brief  The slave interrupted the master to reset the connection. The data will NOT be written.
*/
#define TWI_SPI_COMM_RESET                      		(TWI_ERROR_SPI_COMM_BASE - 3)

/**
*   @brief  The slave interrupted the master to indicate the written data will overflow the slave buffer. The data will NOT be written.
*/
#define TWI_SPI_COMM_OVERFLOW                   		(TWI_ERROR_SPI_COMM_BASE - 4)

/**
*   @brief  The slave interrupted the master to indicate the written data_id can NOT be handled for now. The data will NOT be written.
*/
#define TWI_SPI_COMM_SEND_LATER                 		(TWI_ERROR_SPI_COMM_BASE - 5)

/**
*   @brief  SPI slave Error in Hardware setup.
*/
#define TWI_SPIS_HW_INIT_ERROR							(TWI_ERROR_SPI_COMM_BASE - 6)
/** @} */   /*spi_comm_slave_group*/

/**
*   @defgroup twi_tp_role_retval_group TP ROLE module return values
*   @{
*/

/**
*   @brief  TP ROLES error base return values.
*/
#define TWI_TP_ROLE_ERROR_BASE							-500

/** @} */   /*twi_tp_role_retval_group*/

/**
*   @defgroup twi_app_conn_retval_group Application-Connection module return values
*   @{
*/

/**
*   @brief  application connection return values.
*/
#define TWI_ERROR_APP_CONN_BASE                 		(-600)

/** @} */   /* twi_app_conn_retval_group */

/**
*   @defgroup twi_app_retval_group Application layer return values
*   @{
*/
/**
*   @brief  application return values.
*/
#define TWI_ERROR_APP_BASE               	    		(-700)

/** @} */   /* twi_app_retval_group */

/**
*   @defgroup twi_rci_retval_group RCI module return values
*   @{
*/

/**
*   @brief  RCI return values.
*/
#define TWI_ERR_RCI_BASE								(-800)
#define TWI_RCI_SUCCESS		      	            		(TWI_SUCCESS)
#define TWI_ERR_RCI_INVALID_INPUT_PARAM					(TWI_ERR_RCI_BASE)
#define TWI_ERR_RCI_NOT_INITIALIZED						(TWI_ERR_RCI_BASE - 1)
#define	TWI_ERR_RCI_NOT_INIT_CALLBACK					(TWI_ERR_RCI_BASE - 2)
#define TWI_ERR_RCI_CMD_NOT_FOUND						(TWI_ERR_RCI_BASE - 3)
#define TWI_ERR_RCI_INVALID_CMD_SYNTAX					(TWI_ERR_RCI_BASE - 4)
#define TWI_ERR_RCI_INVALID_BIN_CMD						(TWI_ERR_RCI_BASE - 5)
#define TWI_RCI_FILL_ERROR								(TWI_ERR_RCI_BASE - 6)
#define TWI_RCI_COMPOSE_MSG_ERR							(TWI_ERR_RCI_BASE - 7)
#define TWI_ERR_UNKNOWN									(TWI_ERR_RCI_BASE - 8)
	
/** @} */   /* twi_rci_retval_group */


/**
*   @defgroup twi_comm_retval_group TWI Communication Protocol return values
*   @{
*/
/**
*   @brief  comm return values.
*/
#define TWI_ERR_COMM_BASE								(-900)


/** @} */   /* twi_comm_retval_group */

/**
*   @defgroup twi_fifo_group FIFO module return values
*   @{
*/
/**
*   @brief  FIFO return values.
*/
#define TWI_ERR_FIFO_BASE								(-1100)

/** @} */   /* twi_fifo_group */

/**
*   @defgroup twi_gpio_retval_group TWI GPIO HAL return values
*   @{
*/
/**
*   @brief  GPIO HAL error base return values.
*/
#define TWI_ERROR_GPIO_BASE                     		(-1200)

/**
*   @brief  No free GPIO interrupt channels.
*/
#define	TWI_GPIO_NO_FREE_INTERRUPT_CHANNEL				(TWI_ERROR_GPIO_BASE - 3)

/**
*   @brief  GPIO interrupt not assigned before.
*/
#define	TWI_GPIO_INTERRUPT_NOT_ASSIGNED					(TWI_ERROR_GPIO_BASE - 4)
/** @} */   /* twi_gpio_retval_group */

/**
*   @defgroup twi_adc_retval_group ADC module return values
*   @{
*/
/**
*   @brief  ADC return values base.
*/
#define TWI_ERROR_ADC_BASE                      		(-1300)

/** @} */   /*twi_adc_retval_group*/


/**
*   @defgroup twi_dm_group Device Manager module return values
*   @{
*/
/**
*   @brief  Gateways Device Manager return values base.
*/
#define	TWI_ERR_DM_BASE									(-1400)
/** @} */   /*twi_dm_group*/

/**
*   @defgroup twi_bat_group battery module return values
*   @{
*/
/**
*   @brief  battery return values.
*/
#define TWI_ERR_BATTERY_BASE							(-1500)
#define TWI_BATTERY_SUCCESS								(TWI_SUCCESS)
#define TWI_ERR_BATTERY_INVALID_ARGUMENT				(TWI_ERR_BATTERY_BASE)

/** @} */   /* twi_bat_group */

/**
*   @defgroup twi_app_hal_group Specific Application module return values
*   @{
*/
/**
*   @brief  APP_HAL return values.
*/
#define TWI_ERR_APP_HAL_BASE							(-1600)
#define TWI_APP_HAL_SUCCESS								(TWI_SUCCESS)
#define TWI_APP_HAL_SELECT_PIN_ERROR					(TWI_ERR_APP_HAL_BASE)
#define TWI_APP_HAL_CONFIGURE_PIN_ERROR					(TWI_ERR_APP_HAL_BASE - 1)
#define TWI_APP_HAL_SET_PIN_ERROR						(TWI_ERR_APP_HAL_BASE - 2)
#define TWI_APP_HAL_CLEAR_PIN_ERROR						(TWI_ERR_APP_HAL_BASE - 3)
#define TWI_APP_HAL_TOGGLE_PIN_ERROR					(TWI_ERR_APP_HAL_BASE - 4)

/** @} */   /* twi_app_hal_group */

/**
*   @defgroup twi_rhp_group RHP module return values
*   @{
*/
/**
*   @brief  TWI_RHP return values.
*/

#define TWI_RHP_ERR_BASE								(-1700)

/** @} */   /* twi_rhp_group */


/**
*   @defgroup twi_opp_group Opportunistic module return values
*   @{
*/

/**
*   @brief  TWI_OPP return values.
*/

#define TWI_ERR_OPP_BASE								(-1800)

/** @} */   /* twi_opp_group */


/**
*   @defgroup twi_ethernet_group EtherNet Controller module return values
*   @{
*/
/**
*   @brief  TWI_ETHERNET_CNTRLR return values.
*/

#define TWI_ETHERNET_CNTRLR_ERROR_BASE     				(-1900)
#define TWI_ETHERNET_CNTRLR_SUCCESS						(TWI_SUCCESS)
#define TWI_ETHERNET_CNTRLR_TX_FAILURE					(TWI_ETHERNET_CNTRLR_ERROR_BASE - 1)
#define TWI_ETHERNET_CNTRLR_RX_FAILURE					(TWI_ETHERNET_CNTRLR_ERROR_BASE - 2)
#define TWI_ETHERNET_CNTRLR_BANK_SEL_ERROR				(TWI_ETHERNET_CNTRLR_ERROR_BASE - 3)
#define TWI_ETHERNET_CNTRLR_INVALID_INPUT				(TWI_ETHERNET_CNTRLR_ERROR_BASE - 4)
#define TWI_ETHERNET_CNTRLR_INVALID_OPERATION  			(TWI_ETHERNET_CNTRLR_ERROR_BASE - 5)
#define TWI_ETHERNET_CNTRLR_PHY_SETUP_LINK_ERR_READING  (TWI_ETHERNET_CNTRLR_ERROR_BASE - 6)
#define TWI_ETHERNET_CNTRLR_INITIALIZTION_FAILURE		(TWI_ETHERNET_CNTRLR_ERROR_BASE - 7)
#define TWI_ETHERNET_CNTRLR_PKT_LENGTH_ERROR			(TWI_ETHERNET_CNTRLR_ERROR_BASE - 8)
#define TWI_ETHERNET_CNTRLR_TX_LATE_COLLISION_DETECTED	(TWI_ETHERNET_CNTRLR_ERROR_BASE - 9)
#define TWI_ETHERNET_CNTRLR_NO_RX_PKTS					(TWI_ETHERNET_CNTRLR_ERROR_BASE - 10)
#define TWI_ETHERNET_CNTRLR_RX_PKT_EXCEEDS_MAX_LENGTH	(TWI_ETHERNET_CNTRLR_ERROR_BASE - 11)
#define TWI_ETHERNET_CNTRLR_RX_PKT_CORRUPTED			(TWI_ETHERNET_CNTRLR_ERROR_BASE - 12)
#define TWI_ETHERNET_READING_PHY_REG_FAILURE			(TWI_ETHERNET_CNTRLR_ERROR_BASE - 13)
#define TWI_ETHERNET_CNTRLR_RXEN_CONFIG_CHECK_FAILURE	(TWI_ETHERNET_CNTRLR_ERROR_BASE - 14)
#define TWI_ETHERNET_CNTRLR_RXRST_CONFIG_CHECK_FAILURE	(TWI_ETHERNET_CNTRLR_ERROR_BASE - 15)
#define TWI_ETHERNET_CNTRLR_TXRST_CONFIG_CHECK_FAILURE	(TWI_ETHERNET_CNTRLR_ERROR_BASE - 16)

/* In that case, the upper layer needs to read part of the packet in "complete read" mode, e.g.; PKT_LEN = 50 bytes and the layer wants to read 20 */
#define TWI_ETHERNET_CNTRLR_RDNG_PKT_LEN_LESS_THN_AVB	(TWI_ETHERNET_CNTRLR_ERROR_BASE - 14)

/** @} */   /* twi_ethernet_group */

/**
*   @defgroup twi_arp_group ARP module return values
*   @{
*/
/**
*   @brief  TWI_ARP return values.
*/


#define TWI_ARP_ERROR_BASE     							(-2000)
#define TWI_ARP_SUCCESS									(TWI_SUCCESS)								
#define TWI_ARP_SENDING_FAILURE							(TWI_ARP_ERROR_BASE - 1)
#define TWI_ARP_REPLY_NOT_RELATED_PKT					(TWI_ARP_ERROR_BASE - 2)
#define TWI_ARP_INVALID_INPUTS							(TWI_ARP_ERROR_BASE - 3)
#define TWI_ARP_INIT_FAILURE							(TWI_ARP_ERROR_BASE - 4)
/** @} */   /* twi_arp_group */

/**
*   @defgroup twi_icmp_group ICMP/PING module return values
*   @{
*/
/**
*   @brief  TWI_ICMP return values.
*/

#define TWI_ICMP_ERROR_BASE     						(-2100)
#define TWI_ICMP_SUCCESS								(TWI_SUCCESS)								
#define TWI_ICMP_PING_REQUEST_FAILURE					(TWI_ICMP_ERROR_BASE - 1)
#define TWI_ICMP_PING_REPLY_FAILURE						(TWI_ICMP_ERROR_BASE - 2)
#define TWI_ICMP_NOT_PING_REQUEST						(TWI_ICMP_ERROR_BASE - 3)
#define TWI_ICMP_INVALID_INPUT_ARGS						(TWI_ICMP_ERROR_BASE - 4)
#define TWI_ICMP_INIT_FAILURE							(TWI_ICMP_ERROR_BASE - 5)
#define TWI_ICMP_UNABLE_TO_SEND_IP_STACK_IS_BUSY		(TWI_ICMP_ERROR_BASE - 6)	/* Unable to send a new packet at this moment. */

/** @} */   /* twi_icmp_group */

/**
*   @defgroup twi_ip_stack_group IP Stack module return values
*   @{
*/
/**
*   @brief  TWI_IP_STACK return values.
*/

#define TWI_IP_STACK_ERROR_BASE 						(-2200)
#define TWI_IP_STACK_SUCCESS							(TWI_SUCCESS)
#define TWI_IP_STACK_INVALID_INPUT_ARGS					(TWI_IP_STACK_ERROR_BASE - 1)
#define TWI_IP_STACK_ERROR_GETTING_MAC_ADDR				(TWI_IP_STACK_ERROR_BASE - 2)
#define TWI_IP_STACK_NETWORK_CABLE_UNPLUGGED			(TWI_IP_STACK_ERROR_BASE - 3)
#define TWI_IP_STACK_SEND_TIMER_TIMEOUT					(TWI_IP_STACK_ERROR_BASE - 4)
#define TWI_IP_STACK_TX_ERROR							(TWI_IP_STACK_ERROR_BASE - 5)
#define TWI_IP_STACK_TX_ERROR_DISCONNECTED				(TWI_IP_STACK_ERROR_BASE - 6)
#define TWI_IP_STACK_TX_ERROR_TX_TIMEOUT				(TWI_IP_STACK_ERROR_BASE - 7)
#define TWI_IP_STACK_RX_ERROR							(TWI_IP_STACK_ERROR_BASE - 8)

/** @} */   /* twi_ip_stack_group */

/**
*   @defgroup twi_udp_group UDP/IP module return values
*   @{
*/
/**
*   @brief  TWI_UDP return values.
*/

#define TWI_UDP_ERROR_BASE     							(-2300)
#define TWI_UDP_SUCCESS									(TWI_SUCCESS)
#define TWI_UDP_INVALID_INPUT_ARGS						(TWI_UDP_ERROR_BASE - 1)
#define TWI_UDP_STACK_IS_BUSY							(TWI_UDP_ERROR_BASE - 2)	/* Unable to send a new packet at this moment. */

/** @} */   /* twi_udp_group */

/**
*   @defgroup twi_dhcpc_group DHCPC/UDP module return values
*   DHCPC-Client/UDP layer return values.
*   @{
*/
/**
*   @brief  TWI_DHCPC return values.
*/

#define TWI_DHCPC_ERROR_BASE     						(-2400)
#define TWI_DHCPC_SUCCESS								(TWI_SUCCESS)
#define TWI_DHCPC_INVALID_INPUT_ARGS					(TWI_DHCPC_ERROR_BASE - 1)
/** @} */   /* twi_dhcpc_group */
/**
*   @defgroup twi_GYROSCOPE_group module return values
*    GYROSCOPE HAL layer return values.
*   @{
*/
/**
*   @brief  TWI_GYROSCOPE return values.
*/
#define TWI_ERR_GYROSCOPE_BASE							(-2500)
/** @} */   /* twi_GYROSCOPE_group */

/**
*   @defgroup twi_Accelerometer_group module return values
*    Accelerometer HAL layer return values.
*   @{
*/


/**
*   @defgroup twi_wifi_group module return values
*   WiFi HAL layer return values.
*   @{
*/
/**
*   @brief  TWI_wifi return values.
*/

#define TWI_ERR_WIFI_BASE								(-2600)
/** @} */   /* twi_wifi_group */

/**
*   @defgroup twi_wifi_conn_group module return values
*   WiFi Conn layer return values.
*   @{
*/
/**
*   @brief  TWI_wifi_conn return values.
*/

#define TWI_ERR_WIFI_CONN_BASE								(-2650)
/** @} */   /* twi_wifi_conn_group */

/**
*   @defgroup twi_rle_group RLE decoder module return values
*    RLE decoder  return values.
*   @{
*/
/**
*   @brief  RLE_DEC return values.
*/
#define TWI_RLE_ERROR_BASE     							(-2700)
/** @} */   /* twi_rle_group */

/**
*   @defgroup epd_flash_group EPD flash module return values
*   @{
*/
/**
*   @brief  EPD_FLASH return values.
*/

#define TWI_EPD_FLASH_ERROR_BASE     					(-2800)

/** @} */   /* epd_flash_group */

/**
*   @defgroup twi_ble_hal_group BLE HAL module return values
*   BLE HAL return values.
*   @{
*/

#define TWI_ERR_BLE_HAL_BASE							(-2900)

#define TWI_ERR_BLE_HAL_STK_BASE						(-3000)
#define TWI_BLE_HAL_SUCCESS								(TWI_SUCCESS)
/** @} */   /* twi_ble_hal_group */


/**   @defgroup epd_flash_file_sys_group EPD Flash file system.
*   	EPD Flash file system return values.
*   @{
*/
/**
*   @brief  EPD_FLASH_file_sys return values.
*/

#define TWI_EPD_FLASH_FILE_SYS_ERROR_BASE     			(-3100)

/** @} */   /* epd_flash_file_sys_group */



/**
*   @defgroup twi_conn_mngr_retval_group connection manager module return values
*   @{
*/

/**
*   @brief  connection manager return values.
*/
#define TWI_CONN_MNGR_BASE                				(-3200)

/** @} */   /* twi_conn_mngr_retval_group */


/**
*   @defgroup twi_flash_hal_retval_group Flash HAL module return values
*   @{
*/

/**
*   @brief  flash HAL return values.
*/
#define TWI_FLASH_ERR_BASE                				(-3300)

/** @} */   /* twi_flash_hal_retval_group */


/**
*   @defgroup twi_rhp_logger_retval_group RHP logger module return values
*   @{
*/
/**
*   @brief  RHP logger Error base value.
*/
#define TWI_RHP_LOGGER_ERR_BASE							(-3400)
/** @} */	/*twi_rhp_logger_retval_group*/


/**
*   @defgroup twi_settings_retval_group TWI settings module return values
*   @{
*/
/**
*   @brief	Settings module Error base value.
*/
#define TWI_SETTINGS_ERROR_BASE							(-3500)
/** @} */	/*twi_settings_retval_group*/

/**
*   @defgroup twi_queue_retval_group TWI Queue module return values
*   @{
*/
/**
*   @brief	Queue module Error base value.
*/
#define TWI_QUEUE_ERROR_BASE							(-3600)
/** @} */	/*twi_queue_retval_group*/

/**
*   @defgroup GW_SERVER_retval_group GW-sever return values
*   @{
*/
/**
*   @brief	GW/Server interface module Error base value.
*/
#define TWI_GW_SERVER_INTERFACE_ERROR_BASE				(-3700)
/** @} */	/*GW_SERVER_retval_group*/

/**
*   @defgroup Gw_BLE_retval_group GW-BLE return values
*   @{
*/
/**
*   @brief	GW/BLE interface module Error base value.
*/
#define TWI_GW_BLE_INTERFACE_ERROR_BASE					(-3800)
/** @} */	/*Gw_BLE_retval_group*/


/**
*   @defgroup twi_rhp_parser_composer_retval_group RHP parser/composer module return values
*   @{
*/
/**
 *	@brief	RHP Parser & Composer module Error base value.
 */
#define TWI_ERROR_PRSR_CMPSR_BASE			(-3900)
#define TWI_ERROR_PRSR_CMPSR_INV_MSG_CFG		(TWI_ERROR_PRSR_CMPSR_BASE - 1)
#define TWI_ERROR_PRSR_CMPSR_INV_BUFF_LEN		(TWI_ERROR_PRSR_CMPSR_BASE - 2)
/** @} */	/*twi_rhp_parser_composer_retval_group*/

/**
*   @defgroup twi_aml_retval_group Advertising Management Layer return values
*   @{
*/
/**
 *	@brief	Advertising Management Layer Error Base.
 */
#define TWI_AML_ERROR_BASE								(-4000)
/** @} */	/*twi_aml_retval_group*/

/**
*   @defgroup twi_cust1_dvc_module0_group  TWI Cust1 Driver module return values
*   @{
*/
/**
 *	@brief	Cust1 Device Module Error Base.
 */
#define TWI_CUST1_DVC_MODULE0_ERROR_BASE				(-4100)
/** @} */ /*twi_cust1_dvc_module0_group*/

/**
*   @defgroup twi_tp_group Transmission Protocol Module return values
*   @{
*/
/**
 *	@brief	Transmission Protocol Module Error Base.
 */
#define TWI_TP_ERROR_BASE								(-4200)
/** @} */ /*twi_tp_group*/

/**
*   @defgroup gw_uart_retval_group GW-UART return values
*   @{
*/
/**
 *   @brief	GW/UART interface module Error base value.
 */
#define TWI_GW_UART_INTERFACE_ERROR_BASE				(-4300)
/** @} */ /*gw_uart_retval_group*/

/**
*   @defgroup twi_mnfctr_pair_retval_group manufacture and pairing Module return values
*   @{
*/
/**
 *	@brief	manufacture and pairing Module Error Base.
 */
#define TWI_MNFCTR_PAIR_ERROR_BASE						(-4400)
/** @} */	/* twi_mnfctr_pair_retval_group*/

/**
*   @defgroup twi_aes_retval_group AES Module return values
*   @{
*/
/**
 *	@brief	AES encryption Module Error Base.
 */
#define TWI_AES_ERROR_BASE								(-4500)
/** @} */	/* twi_aes_retval_group */

/**
*   @defgroup twi_ccm_aes_retval_group CCM AES Module return values
*   @{
*/
 /**
 *	@brief	CCM_AES encryption authentication Module Error Base.
 */
#define TWI_CCM_AES_ERROR_BASE							(-4600)
/** @} */	/* twi_ccm_aes_retval_group */

/**
*   @defgroup twi_sec_mngr_retval_group Security Manager Module return values
*   @{
*/
 /**
 *	@brief	Security Manager Module Error Base.
 */
#define TWI_SEC_MNGR_ERROR_BASE							(-4700)
 /** @} */	/* twi_sec_mngr_retval_group */

 /**
*   @defgroup twi_aka_retval_group Authentication and Key Agreement Module return values
*   @{
*/
 /**
 *	@brief	AKA (Authentication and Key Agreement) Module Error Base.
 */
#define TWI_AKA_ERROR_BASE								(-4800)
 /** @} */	/* twi_aka_retval_group */

  /**
*   @defgroup twi_eap_aka_retval_group Extensible Authentication Protocol for Authentication and Key Agreement Module return values
*   @{
*/
 /**
 *	@brief	EAP_AKA (Extensible Authentication Protocol for Authentication and Key Agreement) Module Error Base.
 */
#define TWI_EAP_AKA_ERROR_BASE							(-4900)
 /** @} */	/* twi_eap_aka_retval_group */

/**
*   @defgroup twi_sec_pair_retval_group Security Pairing Module return values
*   @{
*/
 /**
 *	@brief	Security Pairing Module Error Base.
 */
#define TWI_SEC_PAIR_ERROR_BASE							(-5000)
/** @} */ /* twi_sec_pair_retval_group */

/**
*   @defgroup twi_sdt20_sensor_retval_group Temperature/Humidity Sensor Module return values
*   @{
*/
/**
 *	@brief	Temperature/Humidity SDT20 Sensor Module Error Base.
 */
#define TWI_SDT20_SENSOR_ERROR_BASE						(-5100)
/** @} */ /* twi_sdt20_sensor_retval_group */


/**
*   @defgroup twi_cust1_dvc_module1_retval_group CUST1 DVC Module return values
*   @{
*/
/**
*	@brief	CUST1 DVC Module1 Error Base.
*/
#define TWI_CUST1_DVC_MODULE1_ERROR_BASE				(-5200)
/** @} */ /* twi_cust1_dvc_module1_retval_group */

/**
*   @defgroup twi_critical_var_retval_group Critical Variable return values
*   @{
*/
/**
*	@brief	Critical Variables Error Base.
*/
#define TWI_CRITICAL_VAR_ERROR_BASE						(-5300)
/** @} */ /* twi_critical_var_retval_group */
/**
*   @defgroup twi_cgm_base CGM communication Error Base
*   @{
*/
/**
*	@brief	CGM communication Error Base.
*/
#define TWI_ERR_CGM_BASE								(-5400)
/** @} */ /* twi_cgm_base */

/**
*   @defgroup twi_rtc_timer_base RTC HAL Timer Error Base
*   @{
*/
/**
*	@brief	RTC timer HAL Error Base.
*/
#define TWI_ERR_RTC_TIMER_BASE							(-5500)
/** @} */ /* twi_rtc_timer_base */

/**
*   @defgroup twi_tlv_base TLV Module Error Base
*   @{
*/
/**
*   @brief  TLV Error Base.
*/
#define TWI_ERR_TLV_BASE                                (-5600)

/** @} */ /* twi_tlv_base */


/**
*   @defgroup OTA_PARSER_COMPOSER_base OTA Parser Error Base
*   @{
*/
/**
*   @brief  OTA_PARSER_COMPOSER Error Base.
*/
#define OTA_PARSER_COMPOSER_ERR_BASE            		(-5700)
/** @} */ /* OTA_PARSER_COMPOSER_base */

/**
*   @defgroup TWI_OTA_Security_Header_Parser OTA security header parser Error Base
*   @{
*/
/**
*   @brief	OTA Security Header Parser Error Base.
*/
#define TWI_ERR_OTA_SEC_HEADER_BASE						(-5800)
/** @} */ /* TWI_OTA_Security_Header_Parser */


/**
*   @defgroup TWI_ERR_ECDSA_ERR_BASE
*   @{
*/
/**
*   @brief	ECDSA Signing Algorithm Error Base.
*/
#define TWI_ERR_ECDSA_ERR_BASE							(-5900)
/** @} */ /* TWI_ERR_ECDSA_ERR_BASE */

#define TWI_SPAKE2_BASE_ERROR							(-6000)

#define TWI_HB_ERROR_BASE                         		(-6100)

#define TWI_NFC_ERROR_BASE								(-6200)

/**
*   @defgroup TWI_NFC_PARSER_BASE_ERR TWI NFC commands parser Error Base
*   @{
*/
/**
*   @brief	TWI NFC commands parser Error Base
*/
#define TWI_NFC_PARSER_COMPOSER_BASE_ERR				(-6300)
/** @} */ /* TWI_NFC_PARSER_BASE_ERR */

/**
*   @defgroup TWI_CGM_SRV_BASE_ERR
*   @{
*/
/**
*   @brief	TWI CGM Server Error Base
*/
#define TWI_CGM_SRV_BASE_ERROR							(-6400)
/** @} */ /* TWI_CGM_SRV_BASE_ERR */

/**
*   @defgroup TWI_SCDD_CMD_PARSER_BASE_ERR
*   @{
*/
/**
*   @brief	TWI CSDD commands parser Error Base
*/
#define TWI_SCDD_CMD_PARSER_BASE_ERR					(-6500)
/** @} */ /* TWI_SCDD_CMD_PARSER_BASE_ERR */

/**
*   @brief	TWI CSDD commands parser Error Base
*/
#define TWI_SRV_WIFI_BASE_ERR							(-6600)

/**
*   @brief  ITM return values base.
*/
#define TWI_ERROR_ITM_BASE                     	 		(-6700)


/**
*   @brief	TWI QN3000 Driver Error Base
*/
#define QN3000_DRIVER_BASE_ERR							(-6600)


/**
*   @brief	TWI SAW Interface Error Base
*/
#define TWI_SAW_IF_ERR_BASE								(-6700)

/**
*   @defgroup twi_pwm_group module return values
*   @{
*/
/**
*   @brief  TWI_PWM_ return values.
*/
#define TWI_PWM_ERR_BASE								(-6800)
/** @} */ /* twi_pwm_group */

/**
*   @defgroup twi_certificate module return values
*   @{
*/
/**
*   @brief  TWI_PWM_ return values.
*/


#define TWI_CERT_ERR_BASE								(-6900)
/** @} */ /* twi_certificate */

/**
*   @defgroup twi_sec_cert_mngr_retval_group Security Certificate manager module return values
*   @{
*/
/**
*   @brief  TWI_SEC_CERT_MNGR_ERROR_BASE return values.
*/
#define TWI_SEC_CERT_MNGR_ERROR_BASE					(-7000)

/** @} */ /* twi_sec_cert_mngr_retval_group */

/**
*   @defgroup twi_sec_app_mngr_retval_group Security App Module return values
*   @{
*/
/**
*   @brief  TWI_SEC_APP_ERROR_BASE return values.
*/
#define TWI_SEC_APP_ERROR_BASE							(-7100)

/** @} */ /* twi_sec_app_mngr_retval_group */

/**
*   @defgroup twi_sec_pair_intrfc_retval_group Security pair interface Module return values
*   @{
*/
/**
*   @brief  TWI_SEC_PAIR_INTRFC_ERROR_BASE return values.
*/
#define TWI_SEC_PAIR_INTRFC_ERROR_BASE					(-7200)

/** @} */ /* twi_sec_pair_intrfc_retval_group */

/**
*   @brief  TWI_CONN_PARAM_MGMT_ERROR_BASE return values.
*/
#define TWI_CONN_PARAM_MGMT_ERROR_BASE						(-7300)


/**
*   @brief	TWI Misc Module Error Base
*/
#define TWI_MISC_ERR_BASE                                         (-7400)
/** @} */ /* TWI_MISC_MODULE */


/**
*   @defgroup twi_elv_module_group module return values
*   @{
*/
/**
*   @brief  TWI_ELV_MODULE return values.
*/
#define TWI_ELV_ERR_BASE									(-7500)
/** @} */ /* TWI_ELV_MODULE */

/**
*   @brief  TWI_ACCELEROMETER return values.
*/

#define TWI_ERR_ACCELEROMETER_BASE						(-7600)

/** @} */   /* twi_Accelerometer_group */

/**
*   @brief  TWI_REPORTING_UTIL return values.
*/
#define TWI_REPORT_UTIL_ERR_BASE									(-7700)
/** @} */ /* TWI_REPORTING_UTIL */

/**
*   @brief  TWI_PAIRING_DATA_FLASH_ERROR_BASE return values.
*/
#define TWI_PAIRING_DATA_FLASH_ERROR_BASE					(-7800)

/**
*   @brief  TWI_NVDS_ERROR_BASE return values.
*/
#define TWI_NVDS_ERROR_BASE							(-7900)

/**
*   @brief  TWI_NFC_READER_ERROR_BASE return values.
*/
#define TWI_NFC_READER_ERROR_BASE							(-8000)

/**
*   @brief  TWI_SHA256_ERROR_BASE return values.
*/
#define TWI_SHA256_ERROR_BASE							(-8100)


/**
*   @defgroup twi_app_auth_error_group Security Auth interface Module return values
*   @{
*/
/**
*   @brief  TWI_APP_AUTH_ERROR_BASE return values.
*/
#define TWI_APP_AUTH_ERROR_BASE							(-8200)
/** @} */ /* twi_app_auth_error_group */

/**
*   @brief  TWI_CONSUMER_LIST_ERROR_BASE return values.
*/
#define TWI_CONSUMER_LIST_ERROR_BASE					(-8300)

/**
*   @brief  TWI Dongle Host Protocol Parser and composer return values.
*/
#define TWI_HOST_PROTOCOL_PARSER_COMPOSER_ERROR_BASE        (-8400)

/**
*   @brief  TWI_BLE_ADV return values.
*/
#define TWI_ERR_BLE_ADV_SCAN_BASE					(-8500)

/**
*   @brief  TWI_ERR_OTA_SEC_MNGR_BASE return values.
*/
#define TWI_ERR_OTA_SEC_MNGR_BASE					(-8600)

/**
*   @brief  TWI_PILL_DRIVER_ERROR_BASE return values.
*/
#define TWI_PILL_DRV_ERROR_BASE					(-8700)

/**
*   @brief  TWI_DC_MOTOR return values.
*/
#define TWI_ERR_DC_MOTOR_BASE					(-8800)
/** @} */ /* TWI_DC_MOTOR */

#define TWI_IPILL_RX_ERROR_BASE					(-8900)
/** @} */ /* TWI_DC_MOTOR */

#endif  /*_TWI_RETVAL_H_*/
