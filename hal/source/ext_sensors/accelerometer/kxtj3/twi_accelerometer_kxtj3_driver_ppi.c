/*-**************************************************************************-*/
/*- Copyright 2022 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file					twi_accelerometer_kxtj3_driver_ppi.c
 *	@brief					This file holds the needed definitions for the Accelerometer "KXTJ3" chip driver.
 *							For more information, please, refer to the Accelerometer data sheet:
 *							https://kionixfs.azureedge.net/en/datasheet/KXTJ3-1057-Specifications-Rev-5.0.pdf
 */

/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/
#include "twi_accelerometer_kxtj3_driver_ppi.h"
#include "twi_acc_common_defines.h"
#include "twi_gpio.h"
#include "platform_pins.h"
#include "twi_hal_sys_init.h"
//#include "nrf_drv_clock.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_twi.h"

/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/
 //#define ACCELEROMETER_LISHD_DEBUG 
 //#define PRINT_REG_VALUE 
#ifdef  ACCELEROMETER_LISHD_DEBUG
#ifdef PRINT_REG_VALUE
	#include "twi_debug.h"
#endif
	#include "twi_debug.h"
	#define  ACC_KXTJ3_LOG(...)    TWI_LOGGER("[ACC_KXTJ3]: "__VA_ARGS__)
	#define  ACC_KXTJ3_LOG_ERR(...)    TWI_LOGGER_ERR("[ACC_ERR]: "__VA_ARGS__)
#else
	#define  ACC_KXTJ3_LOG(...)
	#define  ACC_KXTJ3_LOG_ERR(...) 
#endif

#define ACCELEROMETER_I2C_CHANNEL		(KXTJ3_ACC_SEN_I2C_CH)
#define KXTJ3_ACC_I2C_ADD_SIZE			(SEVEN_BITS)
#define KXTJ3_ACC_I2C_CLOCK				(I2C_SCL_100K)

#define MAX_NUM_REG                     		(10)
#define KXTJ3_INT_CTRL_REG1_DEFAULT_VALUE  		(0x10)
#define KXTJ3_INT_CTRL_REG1_NUM            		(2)
#define KXTJ3_INT_CTRL_REG2_DEFAULT_VALUE  		(0x3F)
#define KXTJ3_INT_CTRL_REG2_NUM            		(3)
#define KXTJ3_DATA_CTRL_REG_DEFAULT_VALUE  		(0x02)
#define KXTJ3_DATA_CTRL_REG_NUM            		(4)
#define KXTJ3_WAKE_UP_THR_H_REG_DEFAULT_VALUE  	(0x08)
#define KXTJ3_WAKE_UP_THR_H_REG_NUM            	(8)

#define MAX_NUM_TRIALS_READ_REG         		(5)

#define START_UP_DELAY_MS						(2)
#define POWER_UP_DELAY_MS 						(12)
#define I2C_RX_BUFFER_LENGTH 					(6)
#define I2C_RX_BUFFER_WIDTH						(10)
#define I2C_TX_BUFFER_LENGTH 					(6)
#define RTC1_CHANNEL_1        					1	
/*---------------------------------------------------------*/
/*- LOCAL STRUCTS AND UNIONS ------------------------------*/
/*---------------------------------------------------------*/
/**
*	@struct			tstr_twi_acc_kxtj3_reg_info
*	@brief			Structure holds the information of the accelerometer registers.
*/
typedef struct
{
	twi_u8 u8_reg_num;
	twi_u8 u8_reg_value;
}tstr_twi_acc_kxtj3_reg_info;

/*-*********************************************************/
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/*-*********************************************************/
static void kxtj3_init_global_reg_info_default_value(void);
static twi_s32 kxtj3_hw_init(void);
static twi_s32 kxtj3_write_reg(twi_u8 u8_reg_number, twi_u8 u8_reg_val);
static twi_s32 kxtj3_read_reg(twi_u8 u8_reg_number, twi_u8* pu8_reg_val);

/*-*********************************************************/
/*- GLOBAL Static VARIABLES -------------------------------*/
/*-*********************************************************/

static tstr_twi_acc_kxtj3_reg_info gastr_acc_kxtj3_reg_info[MAX_NUM_REG];
static nrf_drv_twi_t i2c_1_instance = NRF_DRV_TWI_INSTANCE(1);
static nrf_drv_rtc_t rtc_0_instance = NRF_DRV_RTC_INSTANCE(0);
static nrf_ppi_channel_t ppi_0_channel;

typedef struct array_list
{
	twi_u8 rx_buffer[I2C_RX_BUFFER_LENGTH];
}array_list_rx;

static array_list_rx i2c_rx_buffer[I2C_RX_BUFFER_WIDTH];
static twi_u8 i2c_tx_buffer[I2C_TX_BUFFER_LENGTH];

static twi_u8 * gpu8_acc_buffer = NULL;
static tpf_acc_data_ready gpf_acc_data_ready;

/*-***********************************************************/
/*- INLINE FUNCTIONS IMPLEMENTATION --------------------------*/
/*-***********************************************************/
__STATIC_INLINE uint32_t nrf_rtc_ms_to_ticks(uint32_t time_ms)
{
    uint32_t prescaler = 9; /*31.25 KHz*/ /* 16 MHZ / 31.25 KHZ = 512*/ /* 2^9 = 512*/
    ASSERT(time_ms <= (UINT32_MAX / 16000UL));
    return ((time_ms * 16000UL) >> prescaler);
}

/*-***********************************************************/
/*- LOCAL FUNCTIONS IMPLEMENTATION --------------------------*/
/*-***********************************************************/
/* Disabled by defult */
void rtc0_interrupt_handler(nrf_drv_rtc_int_type_t evt)
{
	if (evt == NRF_DRV_RTC_INT_TICK)
	{
		/* Disabled */
	}

	else if (evt == NRF_DRV_RTC_INT_COMPARE1)
    {
		TWI_MEMCPY(gpu8_acc_buffer, i2c_rx_buffer[0].rx_buffer,(I2C_RX_BUFFER_WIDTH*I2C_RX_BUFFER_LENGTH));

		gpf_acc_data_ready();

		/* Set the RX buffer to the first address */
		nrf_drv_twi_rx_buffer_set(&i2c_1_instance,(twi_u8 *)i2c_rx_buffer,6);
		
		/* Clear the RTC counter */
		nrf_drv_rtc_counter_clear(&rtc_0_instance);   

		/* Enable the interrupt handler of the compare mode is must */
		nrf_drv_rtc_int_enable(&rtc_0_instance, NRF_RTC_INT_COMPARE1_MASK);

		/* Calculate the acc */
		//twi_accelerometer_kxtj3_calculate_acc(); 

	}


}

/* Disabled by defult */
void i2c_interrupt_handler(nrf_drv_twi_evt_t const *p_evt, void *p_context)
{
	//TWI_LOGGER("i2c handler %d\n\r",p_evt->xfer_desc.type);
	switch (p_evt->type) 
	{
		case NRF_DRV_TWI_EVT_DONE:
		 	if (p_evt->xfer_desc.type == NRF_DRV_TWI_XFER_TX)
			{

			}
			else if (p_evt->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
			{

			}
			else if (p_evt->xfer_desc.type == NRF_DRV_TWI_XFER_TXRX)
			{
				
			}
			else if (p_evt->xfer_desc.type == NRF_DRV_TWI_XFER_TXTX)
			{

			}
			break;
		case NRF_DRV_TWI_EVT_ADDRESS_NACK:
			break;
		case NRF_DRV_TWI_EVT_DATA_NACK:
			break;
	}
}
/*-**************************************************************************************************
* Function Name: kxtj3_init_global_reg_info_default_value			                                *
*****************************************************************************************************
*	@function	static void kxtj3_init_global_reg_info_default_value(void)
*	@brief		Function used for intialize the defult values of registers for the Accelerometer "KXTJ3"
*	@param		none
*   @return     void.
*****************************************************************************************************/
static void kxtj3_init_global_reg_info_default_value(void)
{    
    twi_u8 u8_idx;
    /*Registers that need to check its validity (write registers)*/
    twi_u8 au8_reg_num[MAX_NUM_REG] = {KXTJ3_CTRL_REG1,
                                       KXTJ3_CTRL_REG2,
                                       KXTJ3_INT_CTRL_REG1,
                                       KXTJ3_INT_CTRL_REG2,
                                       KXTJ3_DATA_CTRL_REG,
                                       KXTJ3_WAKE_UP_COUNTER,
                                       KXTJ3_NA_COUNTER,
                                       KXTJ3_SELF_TEST,
                                       KXTJ3_WAKE_UP_THRESHOLD_H,
                                       KXTJ3_WAKE_UP_THRESHOLD_L};

    /*Set Registers value by its default value (zero)*/
    TWI_MEMSET(gastr_acc_kxtj3_reg_info, 0, (sizeof(tstr_twi_acc_kxtj3_reg_info) * MAX_NUM_REG));
                                  
    for(u8_idx = 0; u8_idx < MAX_NUM_REG; u8_idx++)
    {
        gastr_acc_kxtj3_reg_info[u8_idx].u8_reg_num = au8_reg_num[u8_idx];
    }

    /*Set Register KXTJ3_INT_CTRL_REG1 value by its default value*/
    gastr_acc_kxtj3_reg_info[KXTJ3_INT_CTRL_REG1_NUM].u8_reg_value = KXTJ3_INT_CTRL_REG1_DEFAULT_VALUE;
	/*Set Register KXTJ3_INT_CTRL_REG2 value by its default value*/
    gastr_acc_kxtj3_reg_info[KXTJ3_INT_CTRL_REG2_NUM].u8_reg_value = KXTJ3_INT_CTRL_REG2_DEFAULT_VALUE;
	/*Set Register KXTJ3_DATA_CTRL_REG value by its default value*/
    gastr_acc_kxtj3_reg_info[KXTJ3_DATA_CTRL_REG_NUM].u8_reg_value = KXTJ3_DATA_CTRL_REG_DEFAULT_VALUE;
	/*Set Register KXTJ3_WAKE_UP_THRESHOLD_H value by its default value*/
    gastr_acc_kxtj3_reg_info[KXTJ3_WAKE_UP_THR_H_REG_NUM].u8_reg_value = KXTJ3_WAKE_UP_THR_H_REG_DEFAULT_VALUE;
}

/*-**************************************************************************************************
* Function Name: kxtj3_hw_init												                        *
*****************************************************************************************************
*	@function	static twi_s32 kxtj3_hw_init(void)
*	@brief		Function used for configuration the hardware setup for the Accelerometer "KXTJ3"
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*****************************************************************************************************/
static twi_s32 kxtj3_hw_init(void)
{
	twi_s32 s32_retval = TWI_ERROR;

	nrf_drv_twi_config_t i2c_congig;
	i2c_congig.scl = 26;
	i2c_congig.sda = 27;
	i2c_congig.frequency = 26738688; /* 100k: 26738688 , 250k: 67108864 , 400k: 104857600 */
	i2c_congig.interrupt_priority = 3; /* 0,1,4,5 (nRF52) are reserved for SoftDevice */
	i2c_congig.clear_bus_init = 0;
	i2c_congig.hold_bus_uninit = 0;
	s32_retval = nrf_drv_twi_init(&i2c_1_instance, &i2c_congig, i2c_interrupt_handler,NULL);
	if(TWI_SUCCESS == s32_retval)
	{
		nrf_drv_twi_enable(&i2c_1_instance);
	}
	else
	{
		s32_retval = TWI_ACCELEROMETER_HW_INIT_ERROR;
	}

	return s32_retval;
}

/*-**************************************************************************************************
* Function Name: kxtj3_write_reg												                    *
*****************************************************************************************************
*	@function	static twi_s32 kxtj3_write_reg(twi_u8 u8_reg_number, twi_u8 u8_reg_val)
*	@brief		Function used for writing to the registers of the Accelerometer "KXTJ3".
*	@param		u8_reg_number,u8_reg_val
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*****************************************************************************************************/
static twi_s32 kxtj3_write_reg(twi_u8 u8_reg_number, twi_u8 u8_reg_val)
{
	twi_s32 s32_retval = TWI_SUCCESS;
    twi_u8 u8_i;
	twi_u8 au8_send_data[2];
	twi_mem_set(au8_send_data, 0, 2);
    for(u8_i = 0; u8_i < MAX_NUM_REG; u8_i++)
    {
        if(u8_reg_number == gastr_acc_kxtj3_reg_info[u8_i].u8_reg_num)
        {
            gastr_acc_kxtj3_reg_info[u8_i].u8_reg_value = u8_reg_val;
            break;
        }
    }
    
	au8_send_data[0] = u8_reg_number;
	au8_send_data[1] = u8_reg_val;

	s32_retval = nrf_drv_twi_tx(&i2c_1_instance, KXTJ3_I2C_ADD, au8_send_data, 2, TWI_FALSE);
	if(TWI_SUCCESS == s32_retval)
	{
		TWI_DELAY_US(400);
#ifdef PRINT_REG_VALUE
		TWI_LOGGER("Write REG ");
		TWI_LOGGER("0x%X",u8_reg_number);
		TWI_LOGGER(" : ");
		TWI_LOGGER("0x%X",u8_reg_val);
		TWI_LOGGER("\r\n");
#endif
	}
	else
	{
		ACC_KXTJ3_LOG_ERR("I2C Sending Error = %d \r\n",s32_retval);
	}

	return s32_retval;
}

/*-**************************************************************************************************
* Function Name: kxtj3_read_reg												                    	*
*****************************************************************************************************
*	@function	static twi_s32 kxtj3_read_reg(twi_u8 u8_reg_number, twi_u8* pu8_reg_val)
*	@brief		Function used for reading registers of the Accelerometer "KXTJ3".
*	@param		u8_reg_number,pu8_reg_val
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*****************************************************************************************************/
static twi_s32 kxtj3_read_reg(twi_u8 u8_reg_number, twi_u8* pu8_reg_val)
{
	twi_s32 s32_retval = TWI_SUCCESS;
	s32_retval = nrf_drv_twi_tx(&i2c_1_instance, KXTJ3_I2C_ADD, (twi_u8 *)&u8_reg_number, 1, TWI_FALSE);
	if(TWI_SUCCESS == s32_retval)
	{
		TWI_DELAY_US(400);
		s32_retval = nrf_drv_twi_rx(&i2c_1_instance, KXTJ3_I2C_ADD, (twi_u8 *)pu8_reg_val, 1);
		if(TWI_SUCCESS == s32_retval)
		{
			TWI_DELAY_US(400);
#ifdef PRINT_REG_VALUE
			TWI_LOGGER("Read REG ");
			TWI_LOGGER("0x%X",u8_reg_number);	
			TWI_LOGGER(" : ");
			TWI_LOGGER("0x%X",*pu8_reg_val);
			TWI_LOGGER("\r\n");
#endif
		}
		else
		{
			ACC_KXTJ3_LOG_ERR("I2C Receive Error = %d \r\n",s32_retval);
		}
	}
	else
	{
		ACC_KXTJ3_LOG_ERR("I2C Sending Error = %d \r\n",s32_retval);
	}

	return s32_retval;
}

/*-*********************************************************/
/*- API's Implementation ----------------------------------*/
/*-*********************************************************/

/*-***********************************************************************************************************
* Function Name: twi_accelerometer_kxtj3_init								                                 *
**************************************************************************************************************
*	@function	twi_s32 twi_accelerometer_kxtj3_init(void)
*	@brief		- Function used for initialization of Accelerometer "KXTJ3" and setting it into default state.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*************************************************************************************************************/
twi_s32 twi_accelerometer_kxtj3_init(void)
{
	twi_s32 s32_retval = TWI_SUCCESS;
    twi_u8 u8_reg_val = 0;

	s32_retval = kxtj3_hw_init();
	if(TWI_SUCCESS == s32_retval)
	{
		s32_retval = kxtj3_read_reg(KXTJ3_WHO_AM_I, &u8_reg_val);
		ACC_KXTJ3_LOG("WHO IAM VALUE = %d \n",u8_reg_val);
		if((TWI_SUCCESS == s32_retval) && (KXTJ3_WHO_AM_I_VALUE == u8_reg_val))
		{		
            kxtj3_init_global_reg_info_default_value();
			/*
			 * Rebooting RAM content (restart device)
			 */
			s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG2, (twi_u8)
												(1 << KXTJ3_CTRL_REG2_SRST));		/* Start Reboot RAM Routine */

#ifdef ENABLE_POWER_UP_DELAY
			/* Start up time is waiting for the duration of time specified in datasheet for completion of the Software Reset and proceed to the next step*/
			TWI_DELAY_MS(POWER_UP_DELAY_MS);
#endif

			s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG2, (twi_u8)
												(0 << KXTJ3_CTRL_REG2_SRST));		/* No Action */

			/*
			 * 1- Set the ACC range to +-2G.
			 * 2- Switch to stand-by mode.
			 * 3- Switch to Low Power mode (8-bit resolution).
			 * 4- Disable reporting of the availability of new acceleration data as an interrupt.
			 * 5- Disable wake-up at motion detection.
			 */
			s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, (twi_u8)
											((0 << KXTJ3_CTRL_REG1_GSEL0)	|		/* acceleration range selection:
																						0: +-16G  , 1: +-4G , 2: +-8G , 3: +-8G (14-bit) */
											 (0 << KXTJ3_CTRL_REG1_EN16G)	|		/* 0: Depend on GSEL,  1: ACC range is +-16G */								
											 (0 << KXTJ3_CTRL_REG1_PC1)		|		/* 0: Stand-by mode,   1: operating mode mode */
											 (0 << KXTJ3_CTRL_REG1_RES)		|		/* 0: Low Power 8-bit, 1: High Resolution 12/14-bit */
											 (0 << KXTJ3_CTRL_REG1_DRDYE)	|		/* 0: Enable reporting as interrupt, 1: Disable reporting */
											 (0 << KXTJ3_CTRL_REG1_WUFE)));			/* 0: Enable wake up motion detection, 1: Disable wake up */


			/*
			 * 1- Switch to normal mode mode.
			 * 2- Disable self test function.
			 * 3- Set the wake up data rate to 100 Hz.
			 */
			s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG2, (twi_u8)
											((0 << KXTJ3_CTRL_REG2_SRST)	|		/* 0: normal mode, 1: reboot RAM content */
											 (0 << KXTJ3_CTRL_REG2_DCST)	|		/* 0: No Action,  1: Start self test function */								
											 (1 << KXTJ3_CTRL_REG2_OWUFC)));		/* Data rate for Wake up function
																						0: 0.781Hz , 1: 1.563Hz , 2: 3.125Hz , 3: 6.25Hz,
																						4: 12.5Hz, 5: 25Hz, 6: 50Hz, 7: 100kHz */
			/*
			 * 1- Disable Physical INT pin.
			 * 2- Set the interrupt as active high.
			 * 3- Set INT pin to be latched until it is cleared by reading INT_REL.
			 * 4- Set Postive Polarity.
			 */
			s32_retval = kxtj3_write_reg(KXTJ3_INT_CTRL_REG1, (twi_u8)
											((0 << KXTJ3_CTRL_REG1_IEN)		|		/* 0: Disable INT pin,  1: Enable INT pin */								
											 (1 << KXTJ3_CTRL_REG1_IEA)		|		/* 0: Configure INT as active low, 1: active high */
											 (0 << KXTJ3_CTRL_REG1_IEL)		|		/* 	0:  INT latches until it is cleared by reading INT_REL,  
											 											1:  INT will transmit one pulse with a period of 0.03 */
											 (0 << KXTJ3_CTRL_REG1_STPOL)));		/* 0: Negative Polarity, 1: Positive Polarity */

			/*
			 * 1- Disable Unlatched mode.
			 * 2- Disable the 6 axises interrupts .
			 */
			s32_retval = kxtj3_write_reg(KXTJ3_INT_CTRL_REG2, (twi_u8)
											((0 << KXTJ3_CTRL_REG2_ULMODE)	|		/* 0:  Unlatched mode is disabled,  1:  Unlatched mode is enabled */								
											 (0 << KXTJ3_CTRL_REG2_XNWUE)	|		/* 0: Disable +x axis interrupt, 1: Enable +x axis interrupt */
											 (0 << KXTJ3_CTRL_REG2_XPWUE)	|		/* 0: Disable -x axis interrupt, 1: Enable -x axis interrupt */  
											 (0 << KXTJ3_CTRL_REG2_YNWUE)	|		/* 0: Disable +y axis interrupt, 1: +y axis interrupt */
											 (0 << KXTJ3_CTRL_REG2_YPWUE)	|		/* 0: Disable -y axis interrupt, 1: -y axis interrupt */
											 (0 << KXTJ3_CTRL_REG2_ZNWUE)	|		/* 0: Disable +z axis interrupt, 1: +z axis interrupt */
											 (0 << KXTJ3_CTRL_REG2_ZPWUE)));		/* 0: Disable -z axis interrupt, 1: -z axis interrupt */
			
			/*
			 * 1- Set the output data rate (ODR) to 100 Hz.
			 */
			s32_retval = kxtj3_write_reg(KXTJ3_DATA_CTRL_REG, (twi_u8)							
											 (2 << KXTJ3_CTRL_REG2_OWUFC));			/* ODR of Accelerometer output:
																						0: 12.5Hz , 1: 25Hz , 2: 50Hz , 3: 100Hz,
																						4: 200Hz, 5: 400Hz, 6: 800Hz, 7: 1600Hz, 
																						8: 0.781Hz 9: 1.563Hz 10: 3.125Hz  11: 6.25Hz*/

			s32_retval = kxtj3_read_reg(KXTJ3_INT_REL,&u8_reg_val);					/* Clear any interrupts */

			/*
			 * 1- Set the ACC range to +-2G.
			 * 2- Switch to operating mode.
			 * 3- Switch to Low Power mode.
			 * 4- Disable reporting of the availability of new acceleration data as an interrupt.
			 * 5- Disable wake-up at motion detection.
			 */
			s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, (twi_u8)
											((0 << KXTJ3_CTRL_REG1_GSEL0)	|		/* acceleration range selection:
																						0: +-2G  , 1: +-4G , 2: +-8G , 3: +-8G */
											 (0 << KXTJ3_CTRL_REG1_EN16G)	|		/* 0: Depend on GSEL,  1: ACC range is +-16G */								
											 (1 << KXTJ3_CTRL_REG1_PC1)		|		/* 0: Stand-by mode,   1: operating mode */
											 (0 << KXTJ3_CTRL_REG1_RES)		|		/* 0: Low Power 8-bit, 1: High Resolution 12/14-bit */
											 (0 << KXTJ3_CTRL_REG1_DRDYE)	|		/* 0: Disable reporting as interrupt, 1: Enable reporting */
											 (0 << KXTJ3_CTRL_REG1_WUFE)));			/* 0: Disable wake up motion detection, 1: Enable wake up */

#ifdef ENABLE_START_UP_DELAY
			/* Start up time is from PC1 bit set to 1 in CTRL_REG1 register to valid outputs. Time varies with ODR and power mode*/
			TWI_DELAY_MS(START_UP_DELAY_MS);
#endif
		}
		else
		{
			ACC_KXTJ3_LOG_ERR("KXTJ3 INIT internal error\n");
			s32_retval = TWI_ACCELEROMETER_NOT_FOUND_ERROR;
		}
	}
	else
	{
		ACC_KXTJ3_LOG_ERR("Error in HW setup for the Accelerometer");
		s32_retval = TWI_ACCELEROMETER_HW_INIT_ERROR;
	}
	return s32_retval;
}

/*-******************************************************************************************************************
* Function Name: twi_accelerometer_kxtj3_set_full_scale					                                            *
*********************************************************************************************************************
*	@function	twi_s32 twi_accelerometer_kxtj3_set_full_scale(tenu_twi_accelerometer_full_scale_option enu_fs)
*	@brief		Function used to set the KXTJ3 Full Scale.
*	@param[in]	enu_fs	enum variable must be one of the following:
*	(KXTJ3_FULL_SCALE_2G_8_BIT ::), (KXTJ3_FULL_SCALE_2G_12_BIT ::),(KXTJ3_FULL_SCALE_4G_8_BIT ::), 
*	(KXTJ3_FULL_SCALE_4G_12_BIT ::), (KXTJ3_FULL_SCALE_8G_8_BIT ::),(KXTJ3_FULL_SCALE_8G_12_BIT ::), 
*	(KXTJ3_FULL_SCALE_8G_14_BIT ::),(KXTJ3_FULL_SCALE_16G_8_BIT ::), (KXTJ3_FULL_SCALE_16G_12_BIT ::), 
*	(KXTJ3_FULL_SCALE_16G_14_BIT ::)
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**********************************************************************************************************************/
twi_s32 twi_accelerometer_kxtj3_set_full_scale(tenu_twi_accelerometer_kxtj3_full_scale_option enu_fs)
{
	twi_s32 s32_retval;
	twi_u8 u8_reg_val;

	s32_retval = TWI_SUCCESS;
	u8_reg_val = 0;

	if( (KXTJ3_FULL_SCALE_2G_8_BIT == enu_fs) 	|| (KXTJ3_FULL_SCALE_2G_12_BIT == enu_fs) || /* check for valid input argument */
		(KXTJ3_FULL_SCALE_4G_8_BIT == enu_fs) 	|| (KXTJ3_FULL_SCALE_4G_12_BIT == enu_fs) ||
		(KXTJ3_FULL_SCALE_8G_8_BIT == enu_fs) 	|| (KXTJ3_FULL_SCALE_8G_12_BIT == enu_fs) ||
		(KXTJ3_FULL_SCALE_8G_14_BIT == enu_fs) 	|| (KXTJ3_FULL_SCALE_16G_8_BIT == enu_fs) ||
		(KXTJ3_FULL_SCALE_16G_12_BIT == enu_fs) || (KXTJ3_FULL_SCALE_16G_14_BIT == enu_fs))
	{
		s32_retval = kxtj3_read_reg(KXTJ3_CTRL_REG1, &u8_reg_val);
		if(TWI_SUCCESS == s32_retval)
		{
			/* Set the ACC in Stand-by mode in order to adjust the full scale */
			u8_reg_val &= 0x7F;
			u8_reg_val |= ((twi_u8)(0 << KXTJ3_CTRL_REG1_PC1));
			s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, u8_reg_val);
			if(TWI_SUCCESS == s32_retval)
			{
				s32_retval = kxtj3_read_reg(KXTJ3_CTRL_REG1, &u8_reg_val);
				if(TWI_SUCCESS == s32_retval)
				{
					u8_reg_val &= 0xA3;
					switch (enu_fs)
					{
						case  KXTJ3_FULL_SCALE_2G_8_BIT:
							u8_reg_val |= KXTJ3_FS_2G_8_BIT_VALUE;
							break;
						case  KXTJ3_FULL_SCALE_2G_12_BIT:
							u8_reg_val |= KXTJ3_FS_2G_12_BIT_VALUE;
							break;
						case  KXTJ3_FULL_SCALE_4G_8_BIT:
							u8_reg_val |= KXTJ3_FS_4G_8_BIT_VALUE;
							break;
						case  KXTJ3_FULL_SCALE_4G_12_BIT:
							u8_reg_val |= KXTJ3_FS_4G_12_BIT_VALUE;
							break;
						case  KXTJ3_FULL_SCALE_8G_8_BIT:
							u8_reg_val |= KXTJ3_FS_8G_8_BIT_VALUE;
							break;
						case  KXTJ3_FULL_SCALE_8G_12_BIT:
							u8_reg_val |= KXTJ3_FS_8G_12_BIT_VALUE;
							break;
						case  KXTJ3_FULL_SCALE_8G_14_BIT:
							u8_reg_val |= KXTJ3_FS_8G_14_BIT_VALUE;
							break;
						case  KXTJ3_FULL_SCALE_16G_8_BIT:
							u8_reg_val |= KXTJ3_FS_16G_8_BIT_VALUE1;
							break;
						case  KXTJ3_FULL_SCALE_16G_12_BIT:
							u8_reg_val |= KXTJ3_FS_16G_12_BIT_VALUE1;
							break;
						case  KXTJ3_FULL_SCALE_16G_14_BIT:
							u8_reg_val |= KXTJ3_FS_16G_14_BIT_VALUE;
							break;
					}

							
					s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, u8_reg_val);
					if(TWI_SUCCESS == s32_retval)
					{
						s32_retval = kxtj3_read_reg(KXTJ3_CTRL_REG1, &u8_reg_val);
						if(TWI_SUCCESS == s32_retval)
						{
							/* Set the ACC in operating mode */
							u8_reg_val &= 0x7F;
							u8_reg_val |= ((twi_u8)(1 << KXTJ3_CTRL_REG1_PC1));
							s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, u8_reg_val);
							if(TWI_SUCCESS == s32_retval)
							{
								/* Do Nothing */
							}
							else
							{
								s32_retval = TWI_ACCELEROMETER_WRITE_REG_ERROR;
							}
						}
						else
						{
							s32_retval = TWI_ACCELEROMETER_READ_REG_ERROR;
						}
					}
					else
					{
						s32_retval = TWI_ACCELEROMETER_WRITE_REG_ERROR;
					}
				}
				else
				{
					s32_retval = TWI_ACCELEROMETER_READ_REG_ERROR;
				}
			}
			else
			{
				s32_retval = TWI_ACCELEROMETER_WRITE_REG_ERROR;
			}
		}
		else
		{
			s32_retval = TWI_ACCELEROMETER_READ_REG_ERROR;
		}
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	}

#ifdef ENABLE_START_UP_DELAY
	/* Start up time is from PC1 bit set to 1 in CTRL_REG1 register to valid outputs. Time varies with ODR and power mode*/
	TWI_DELAY_MS(START_UP_DELAY_MS);
#endif

	return s32_retval;
}

/*-*****************************************************************************************************************
* Function Name: twi_accelerometer_kxtj3_set_data_rate_config				                                       *  
********************************************************************************************************************
*	@function	twi_s32 twi_accelerometer_kxtj3_set_data_rate_config(tenu_twi_accelerometer_kxtj3_odr_cfg enu_odr)
*	@brief		Function used to set the KXTJ3 Data rate configuration.
*	@param[in]	enu_odr	enum variable (Data Rate CFG) must be one of the following:
*					(KXTJ3_ODR_0_781Hz ::), (KXTJ3_ODR_1_563Hz ::), (KXTJ3_ODR_3_125Hz ::), (KXTJ3_ODR_6_25Hz ::), 
*    				(KXTJ3_ODR_12_5Hz ::)(KXTJ3_ODR_25Hz ::), (KXTJ3_ODR_50Hz::), (KXTJ3_ODR_100Hz ::),
*					(KXTJ3_ODR_200Hz ::),(KXTJ3_ODR_400Hz ::),(KXTJ3_ODR_800Hz ::),(KXTJ3_ODR_1600Hz ::)
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
********************************************************************************************************************/
twi_s32 twi_accelerometer_kxtj3_set_data_rate_config(tenu_twi_accelerometer_kxtj3_odr_cfg enu_odr)
{
	twi_s32 s32_retval = TWI_SUCCESS;
	twi_u8 u8_reg_val = 0;

	switch (enu_odr)
	{
		case KXTJ3_ODR_12_5Hz:
		case KXTJ3_ODR_25Hz:
		case KXTJ3_ODR_50Hz:
		case KXTJ3_ODR_100Hz:
		case KXTJ3_ODR_200Hz:
		case KXTJ3_ODR_400Hz:
		case KXTJ3_ODR_800Hz:
		case KXTJ3_ODR_1600Hz:
		case KXTJ3_ODR_0_781Hz:
		case KXTJ3_ODR_1_563Hz:
		case KXTJ3_ODR_3_125Hz:
		case KXTJ3_ODR_6_25Hz:


			s32_retval = kxtj3_read_reg(KXTJ3_CTRL_REG1, &u8_reg_val);
			if(TWI_SUCCESS == s32_retval)
			{
				/* Set the ACC in Stand-by mode in order to adjust the output data rate */
				u8_reg_val &= 0x7F;
				u8_reg_val |= ((twi_u8)(0 << KXTJ3_CTRL_REG1_PC1));
				s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, u8_reg_val);
				if(TWI_SUCCESS == s32_retval)
				{
					s32_retval = kxtj3_read_reg(KXTJ3_DATA_CTRL_REG, &u8_reg_val);
					if(TWI_SUCCESS == s32_retval)
					{
						u8_reg_val &= 0xF0;
						u8_reg_val |= ((twi_u8)(enu_odr << KXTJ3_DATA_CTRL_REG_OSAD));
						s32_retval = kxtj3_write_reg(KXTJ3_DATA_CTRL_REG, u8_reg_val);
						if(TWI_SUCCESS == s32_retval)
						{
							s32_retval = kxtj3_read_reg(KXTJ3_CTRL_REG1, &u8_reg_val);
							if(TWI_SUCCESS == s32_retval)
							{
								/* Set the ACC in operating mode */
								u8_reg_val &= 0x7F;
								u8_reg_val |= ((twi_u8)(1 << KXTJ3_CTRL_REG1_PC1));
								s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, u8_reg_val);
								if(TWI_SUCCESS == s32_retval)
								{
									/* Do Nothing */
								}
								else
								{
									s32_retval = TWI_ACCELEROMETER_WRITE_REG_ERROR;
								}
							}
							else
							{
								s32_retval = TWI_ACCELEROMETER_READ_REG_ERROR;
							}
						}
						else
						{
							s32_retval = TWI_ACCELEROMETER_WRITE_REG_ERROR;
						}
					}
					else
					{
						s32_retval = TWI_ACCELEROMETER_READ_REG_ERROR;
					}
				}
				else
				{
					s32_retval = TWI_ACCELEROMETER_WRITE_REG_ERROR;
				}
			}	
			else
			{
				s32_retval = TWI_ACCELEROMETER_READ_REG_ERROR;
			}
			break;
		default:
			s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
			break;
	}

#ifdef ENABLE_START_UP_DELAY
	/* Start up time is from PC1 bit set to 1 in CTRL_REG1 register to valid outputs. Time varies with ODR and power mode*/
	TWI_DELAY_MS(START_UP_DELAY_MS);
#endif

	return s32_retval;
}

/*-***********************************************************************************************************
* Function Name:  twi_accelerometer_kxtj3_config_ppi_axis_acc					                             *
**************************************************************************************************************
*	@function 	twi_accelerometer_kxtj3_config_ppi_axis_acc(void)	
*	@brief 		Function used to set the KXTJ3 PPI module configurations		
*   @return     void
*************************************************************************************************************/
void twi_accelerometer_kxtj3_config_ppi_axis_acc(twi_u8* Pu8_acc_buffer, tpf_acc_data_ready pf_acc_data_ready)
{
	twi_s32 s32_retval = TWI_ERROR;
	gpu8_acc_buffer = Pu8_acc_buffer;
	gpf_acc_data_ready = pf_acc_data_ready;

	do 
	{
		i2c_tx_buffer [0] = KXTJ3_OUT_X_L;
		i2c_tx_buffer [1] = KXTJ3_OUT_X_H;
		i2c_tx_buffer [2] = KXTJ3_OUT_Y_L;
		i2c_tx_buffer [3] = KXTJ3_OUT_Y_H;
		i2c_tx_buffer [4] = KXTJ3_OUT_Z_L;
		i2c_tx_buffer [5] = KXTJ3_OUT_Z_H;

		nrf_drv_twi_xfer_desc_t xfer_cnfg = NRF_DRV_TWI_XFER_DESC_TXRX(KXTJ3_I2C_ADD, (twi_u8 *)i2c_tx_buffer, 6, (twi_u8 *)i2c_rx_buffer , 6);

		twi_u32 u32_xfer_flags =  /* NRF_DRV_TWI_FLAG_TX_POSTINC | */               /**< TX buffer address incremented after transfer. */
								  NRF_DRV_TWI_FLAG_RX_POSTINC | 					/**< RX buffer address incremented after transfer. */
								  NRF_DRV_TWI_FLAG_NO_XFER_EVT_HANDLER |			/**< Interrupt after each transfer is suppressed, and the event handler is not called. */
								  NRF_DRV_TWI_FLAG_HOLD_XFER | 						/**< Set up the transfer but do not start it. */
								  NRF_DRV_TWI_FLAG_REPEATED_XFER |					/**< Flag indicating that the transfer will be executed multiple times. */
								  NRF_DRV_TWI_FLAG_TX_NO_STOP ;						/**< Flag indicating that the TX transfer will not end with a stop condition. */


		s32_retval = nrf_drv_twi_xfer(&i2c_1_instance, &xfer_cnfg, u32_xfer_flags);
		TWI_ERROR_BREAK(s32_retval);
	}
	while(0);
}

/*-***********************************************************************************************************
* Function Name: twi_accelerometer_kxtj3_rtc_config_init							                         *
**************************************************************************************************************
*	@function 	twi_accelerometer_kxtj3_rtc_config_init()	
*	@brief		Function used to set the KXTJ3 RTC module configurations
*   @return  	void   
*************************************************************************************************************/
void twi_accelerometer_kxtj3_rtc_config_init(void)
{
	twi_s32 s32_retval = TWI_SUCCESS;

	do 
	{
		/* Configure the XTAL LF CLK */
    	/*s32_retval = nrf_drv_clock_init();
    	TWI_ERROR_BREAK(s32_retval);

    	nrf_drv_clock_lfclk_request(NULL);*/

		/* RTC 0*/
		/* Create RTC configurations and assign default configurations */
    	nrf_drv_rtc_config_t rtc0_cfg = NRF_DRV_RTC_DEFAULT_CONFIG;
		rtc0_cfg.prescaler = RTC_FREQ_TO_PRESCALER(10);

		/* initialze the RTC with default configurations */ 
    	s32_retval = nrf_drv_rtc_init(&rtc_0_instance, &rtc0_cfg, rtc0_interrupt_handler);
    	TWI_ERROR_BREAK(s32_retval);

		/* Enable The RTC ticking*/
		nrf_drv_rtc_tick_enable(&rtc_0_instance, false); /* true: IRQ , false : No IRQ*/

		/* Enable RTC compare channel */
		s32_retval = nrf_drv_rtc_cc_set(&rtc_0_instance, RTC1_CHANNEL_1, 10, true); /* True: IRQ , False : No IRQ*/
		TWI_ERROR_BREAK(s32_retval);

	}
	while(0);

	nrf_drv_rtc_enable(&rtc_0_instance);
}

/*-***********************************************************************************************************
* Function Name: twi_accelerometer_kxtj3_ppi_init 							                                 *
**************************************************************************************************************
*	@function 	twi_accelerometer_kxtj3_ppi_init()	
*	@brief		Function used to initialize the PPI module
*   @return    	void
*************************************************************************************************************/
void twi_accelerometer_kxtj3_ppi_init(void)
{
	twi_s32 s32_retval = TWI_SUCCESS;

  	/* they are needed to connect with the PPI TEP(Task End Point) & PPI EEP (Event End Point) */ 
    twi_u32 u32_rtc_evt_addr;  			/* Variable to hold the event address */ 
    twi_u32 u32_i2c_task_addr;			/* Variable to hold the task address */

	do 
	{
		/* Initialize the PPI module, make sure its only enabled once in your code */
   		s32_retval =  nrf_drv_ppi_init();
   		TWI_ERROR_BREAK(s32_retval);

		/* Allocate the channel from the available PPI channels */
    	s32_retval = nrf_drv_ppi_channel_alloc(&ppi_0_channel);
    	TWI_ERROR_BREAK(s32_retval);

		/* Get the address of the respective event and tasks from the pins */
    	u32_rtc_evt_addr =  nrf_drv_rtc_event_address_get(&rtc_0_instance, NRF_RTC_EVENT_TICK);
    	u32_i2c_task_addr = nrf_drv_twi_start_task_get(&i2c_1_instance, NRF_DRV_TWI_XFER_TXRX);

		/* connect the EEP & TEP with Peripheral Events & Tasks using their addresses and assign them to an allocated channel */
    	s32_retval = nrf_drv_ppi_channel_assign(ppi_0_channel, u32_rtc_evt_addr, u32_i2c_task_addr);
    	TWI_ERROR_BREAK(s32_retval);

		/* Enable the channel so that it can start receiving events and then route them to tasks */
   	 	s32_retval = nrf_drv_ppi_channel_enable(ppi_0_channel);
    	TWI_ERROR_BREAK(s32_retval);
	}
	while(0);
}

/*-***********************************************************************************************************
* Function Name: twi_accelerometer_kxtj3_calculate_acc							                             *
**************************************************************************************************************
*	@function 	twi_accelerometer_kxtj3_calculate_acc()	
*	@brief		Function used to calculate the accelerometer values
*   @return    	void 
*************************************************************************************************************/
void twi_accelerometer_kxtj3_calculate_acc(void)
{
		twi_s16 s16_acc_val = (twi_s16) (i2c_rx_buffer[8].rx_buffer[0] | (i2c_rx_buffer[8].rx_buffer[1] << 8));
		twi_s16 s16_x_axis_acc_mg = (twi_s16) (((MUL1000(s16_acc_val) << 1) >> 15));

		s16_acc_val = (twi_s16) (i2c_rx_buffer[8].rx_buffer[2] | (i2c_rx_buffer[8].rx_buffer[3] << 8));
		twi_s16 s16_y_axis_acc_mg = (twi_s16) (((MUL1000(s16_acc_val) << 1) >> 15));

		s16_acc_val = (twi_s16) (i2c_rx_buffer[8].rx_buffer[4] | (i2c_rx_buffer[8].rx_buffer[5] << 8));
		twi_s16 s16_z_axis_acc_mg = (twi_s16) (((MUL1000(s16_acc_val) << 1) >> 15));

		if ((ABS(s16_x_axis_acc_mg) < 250) && (ABS(s16_z_axis_acc_mg) < 250) && (s16_y_axis_acc_mg < 0 ))
		{
        	//TWI_LOGGER("\033[1;33m");
        	TWI_LOGGER("A = Vertical \r\n");
        	//TWI_LOGGER((const twi_u8*)"\033[0m\r\n");
    	}
		else if ((ABS(s16_x_axis_acc_mg) < 250) && (ABS(s16_y_axis_acc_mg) < 250) && (s16_z_axis_acc_mg > 0 ))
		{
        	//TWI_LOGGER("\033[1;32m");
        	TWI_LOGGER("A = Horizontal \r\n");
        	//TWI_LOGGER((const twi_u8*)"\033[0m\r\n");
    	}
    	else
    	{
        	//TWI_LOGGER("\033[1;31m");
        	TWI_LOGGER("A = Unknown \r\n");
        	//TWI_LOGGER((const twi_u8*)"\033[0m\r\n");
    	}
	
}
