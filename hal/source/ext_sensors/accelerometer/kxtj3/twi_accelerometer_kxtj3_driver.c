/*-**************************************************************************-*/
/*- Copyright 2022 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file					twi_accelerometer_kxtj3_driver.c
 *	@brief					This file holds the needed definitions for the Accelerometer "KXTJ3" chip driver.
 *							For more information, please, refer to the Accelerometer data sheet:
 *							https://kionixfs.azureedge.net/en/datasheet/KXTJ3-1057-Specifications-Rev-5.0.pdf
 */

//***********************************************************
/*- INCLUDES ----------------------------------------------*/
//***********************************************************
#include "twi_accelerometer_kxtj3_driver.h"
#include "twi_acc_common_defines.h"
#include "twi_gpio.h"
#include "twi_i2c_master.h"
#include "platform_pins.h"
#include "twi_hal_sys_init.h"

//***********************************************************
/*- LOCAL MACROS ------------------------------------------*/
//***********************************************************
/* #define ACCELEROMETER_LISHD_DEBUG */
/* #define PRINT_REG_VALUE */
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

/*-***********************************************************/
/*- ENUMS ---------------------------------------------------*/
/*-***********************************************************/

/**
*	@struct			tstr_twi_acc_kxtj3_reg_info
*	@brief			Structure holds the information of the accelerometer registers.
*/
typedef struct
{
	twi_u8 u8_reg_num;
	twi_u8 u8_reg_value;
}tstr_twi_acc_kxtj3_reg_info;

//***********************************************************
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
//***********************************************************

static void kxtj3_init_global_reg_info_default_value(void);
static void kxtj3_int1_cb(void* pv_value);
static twi_s32 kxtj3_i2c_addr_init(void);
static twi_s32 kxtj3_i2c_addr_deinit(void);
static twi_s32 kxtj3_int1_init(void);
static twi_s32 kxtj3_int1_deinit(void);
static twi_s32 kxtj3_hw_init(void);
static twi_s32 kxtj3_hw_deinit(void);
static twi_s32 kxtj3_int1_enable(void);
static twi_s32 kxtj3_int1_disable(void);
static twi_s32 kxtj3_write_reg(twi_u8 u8_reg_number, twi_u8 u8_reg_val);
static twi_s32 kxtj3_read_reg(twi_u8 u8_reg_number, twi_u8* pu8_reg_val);
#ifndef KXTJ3_OPTIMIZATION_MODE
static twi_s32 kxtj3_get_full_scale(tenu_twi_accelerometer_kxtj3_full_scale_option* enu_fs);
#endif
static twi_s16 kxtj3_calculate_acceleration(tenu_twi_accelerometer_kxtj3_full_scale_option enu_fs, twi_s16 s16_adc_val);

//***********************************************************
/*- GLOBAL STATIC VARIABLES -------------------------------*/
//***********************************************************

static tpf_accelerometer_kxtj3_interrupt gpf_accelerometer_kxtj3_interrupt = NULL;
static tstr_twi_acc_kxtj3_reg_info gastr_acc_kxtj3_reg_info[MAX_NUM_REG];
#ifdef KXTJ3_OPTIMIZATION_MODE
static tenu_twi_accelerometer_kxtj3_full_scale_option genu_full_scale_optimization = KXTJ3_FULL_SCALE_2G_8_BIT;
#endif
//***********************************************************
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
//***********************************************************

//***********************************************************
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
//***********************************************************

/**
*	@function	static void kxtj3_init_global_reg_info_default_value(void)
*	@brief		Function used for intialize the defult values of registers for the Accelerometer "KXTJ3"
*	@param		none
*   @return     void.
**/
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

/**
*	@function	static twi_s32 kxtj3_int1_cb(void* pv_value)
*	@brief		Function used for the Call back interrupt of INT1 for Accelerometer"KXTJ3".
*	@param		none
*   @return     pv_value void pointer used to pass data from interrupt to user.
**/
static void kxtj3_int1_cb(void* pv_value)
{
	if(NULL != gpf_accelerometer_kxtj3_interrupt)
	{
		gpf_accelerometer_kxtj3_interrupt(NULL);
	}
	else
	{
		/* Do nothing */
	}
}

/**
*	@function	static twi_s32 kxtj3_i2c_addr_init(void)
*	@brief		Function used for init the I2C addresse selection pin for the Accelerometer "KXTJ3".
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
static twi_s32 kxtj3_i2c_addr_init(void)
{
	twi_s32 s32_retval = TWI_SUCCESS;

	do
	{
		/* Configuration for Accelerometer ADDR pin. */
		s32_retval = twi_gpio_select(ACCELEROMETER_I2C_ADDR_PORT, ACCELEROMETER_I2C_ADDR_PIN);
		TWI_ERROR_BREAK(s32_retval);

		s32_retval = twi_gpio_set_configure(ACCELEROMETER_I2C_ADDR_PORT, ACCELEROMETER_I2C_ADDR_PIN, TWI_GPIO_DIR_OUT, TWI_PIN_FUNC_GPIO, TWI_INVALID_CHANNEL_NUM);
		TWI_ERROR_BREAK(s32_retval);

		s32_retval = twi_gpio_set(ACCELEROMETER_I2C_ADDR_PORT, ACCELEROMETER_I2C_ADDR_PIN);
		TWI_ERROR_BREAK(s32_retval);
	}while(0);

	return s32_retval;
}

/**
*	@function	static twi_s32 kxtj3_i2c_addr_deinit(void)
*	@brief		Function used for deinit the I2C addresse selection pin for the Accelerometer "KXTJ3".
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
static twi_s32 kxtj3_i2c_addr_deinit(void)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	/* Disable the configuration for Accelerometer ADDR pin. */
	s32_retval = twi_gpio_deselect(ACCELEROMETER_I2C_ADDR_PORT, ACCELEROMETER_I2C_ADDR_PIN);
	if(TWI_SUCCESS == s32_retval)
	{
		/* Do Nothing (return with success). */
	}
	else
	{
		ACC_KXTJ3_LOG_ERR("Error ACC I2C ADDR selection GPIO de-select\r\n");
		s32_retval = TWI_ERROR;
	}
	return s32_retval;
}

/**
*	@function	static twi_s32 kxtj3_int1_init(void)
*	@brief		Function used for init the INT1 pin for the Accelerometer "KXTJ3".
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*   @note		This function does't enable the interrupt pin. It's just configure it.
**/
static twi_s32 kxtj3_int1_init(void)
{
	twi_s32 s32_retval = TWI_SUCCESS;

	do
	{
		/* Configuration for Accelerometer Interrupt pin. */
		s32_retval = twi_gpio_select(ACCELEROMETER_INT1_PORT, ACCELEROMETER_INT1_PIN);
		TWI_ERROR_BREAK(s32_retval);

#ifdef ACC_INT_USING_EXT_PULL_DOWN
		s32_retval = twi_gpio_set_configure(ACCELEROMETER_INT1_PORT, ACCELEROMETER_INT1_PIN, TWI_GPIO_DIR_IN|TWI_GPIO_NO_PULL, TWI_PIN_FUNC_GPIO, TWI_INVALID_CHANNEL_NUM);
#else
		s32_retval = twi_gpio_set_configure(ACCELEROMETER_INT1_PORT, ACCELEROMETER_INT1_PIN, TWI_GPIO_DIR_IN|TWI_GPIO_PULL_DOWN, TWI_PIN_FUNC_GPIO, TWI_INVALID_CHANNEL_NUM);
#endif
		TWI_ERROR_BREAK(s32_retval);

		s32_retval = twi_gpio_register_interrupt(ACCELEROMETER_INT1_PORT, ACCELEROMETER_INT1_PIN, TWI_GPIO_EDGE_RISING, (tpf_twi_gpio_cb)&kxtj3_int1_cb);
		TWI_ERROR_BREAK(s32_retval);
	}while(0);

	return s32_retval;
}

/**
*	@function	static twi_s32 kxtj3_int1_deinit(void)
*	@brief		Function used for de-init the INT1 pin for the Accelerometer "KXTJ3".
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
static twi_s32 kxtj3_int1_deinit(void)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	/* Disable the configuration for Accelerometer Interrupt pin. */
	s32_retval = twi_gpio_disable_interrupt(ACCELEROMETER_INT1_PORT, ACCELEROMETER_INT1_PIN);
	if(TWI_SUCCESS == s32_retval)
	{
		s32_retval = twi_gpio_deselect(ACCELEROMETER_INT1_PORT, ACCELEROMETER_INT1_PIN);
		if(TWI_SUCCESS == s32_retval)
		{
			/* Do Nothing (return with success) */
		}
		else
		{
			ACC_KXTJ3_LOG_ERR("Error ACC INT1 de-select\r\n");
			s32_retval = TWI_ERROR;
		}
	}
	else
	{
		ACC_KXTJ3_LOG_ERR("Error ACC INT1 en\r\n");
		s32_retval = TWI_ERROR;
	}
	return s32_retval;
}

/**
*	@function	static twi_s32 kxtj3_hw_init(void)
*	@brief		Function used for configuration the hardware setup for the Accelerometer "KXTJ3"
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
static twi_s32 kxtj3_hw_init(void)
{
	twi_s32 s32_retval;
	s32_retval = TWI_ERROR;

    s32_retval = twi_gpio_init();
	if(TWI_SUCCESS == s32_retval)
	{
		tstr_twi_i2c_master_config str_i2c_master_cfg;
		str_i2c_master_cfg.u32_clock = KXTJ3_ACC_I2C_CLOCK;
		str_i2c_master_cfg.u8_addr_size = KXTJ3_ACC_I2C_ADD_SIZE;
		str_i2c_master_cfg.u8_pull_up = GET_I2C_PULL_CFG(ACCELEROMETER_I2C_CHANNEL);
	   	s32_retval = twi_i2c_master_init(ACCELEROMETER_I2C_CHANNEL, &str_i2c_master_cfg);
		if(TWI_SUCCESS == s32_retval)
		{
			/* No need for CS intialization as the acc only support I2C comm */
			s32_retval = kxtj3_i2c_addr_init();
			if(TWI_SUCCESS == s32_retval)
			{
				s32_retval = kxtj3_int1_init();
				if(TWI_SUCCESS == s32_retval)
				{
					// Do Nothing (return with Success)
				}
				else
				{
					s32_retval = TWI_ACCELEROMETER_HW_INIT_ERROR;
				}
			}
		}
		else
		{
			s32_retval = TWI_ACCELEROMETER_HW_INIT_ERROR;
		}
	}
	else
	{
		s32_retval = TWI_ERROR;
	}

	return s32_retval;
}

/**
*	@function	static twi_s32 kxtj3_hw_deinit(void)
*	@brief		Function used for de-initialization for the Accelerometer "KXTJ3"
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
static twi_s32 kxtj3_hw_deinit(void)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	s32_retval = kxtj3_int1_deinit();	/* Disable the configuration for the INT1 pin of the accelerometer "KXTJ3" */

	if(TWI_SUCCESS == s32_retval)
	{
		s32_retval = kxtj3_i2c_addr_deinit();
		if(TWI_SUCCESS == s32_retval)
		{
			s32_retval = twi_i2c_master_deinit(ACCELEROMETER_I2C_CHANNEL);	/* Disable the I2C Communication of the accelerometer "KXTJ3" */
		}
	}
	else
	{
		s32_retval = TWI_ACCELEROMETER_HW_DEINIT_ERROR;
	}

	return s32_retval;
}

/**
*	@function	static twi_s32 kxtj3_int1_enable(void)
*	@brief		Function used for INT1 pin Enable for the Accelerometer "KXTJ3".
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
static twi_s32 kxtj3_int1_enable(void)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	/* Configuration for Accelerometer Interrupt pin. */
	s32_retval = twi_gpio_enable_interrupt(ACCELEROMETER_INT1_PORT, ACCELEROMETER_INT1_PIN);
	if(TWI_SUCCESS != s32_retval)
	{
		ACC_KXTJ3_LOG_ERR("Error ACC INT1 en\r\n");
	}
	else
	{

	}
	return s32_retval;
}

/**
*	@function	static twi_s32 kxtj3_int1_disable(void)
*	@brief		Function used for INT1 pin disable for the Accelerometer "KXTJ3".
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
static twi_s32 kxtj3_int1_disable(void)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	/* Enable for Accelerometer Interrupt pin. */
	s32_retval = twi_gpio_disable_interrupt(ACCELEROMETER_INT1_PORT, ACCELEROMETER_INT1_PIN);
	if(TWI_SUCCESS != s32_retval)
	{
		ACC_KXTJ3_LOG_ERR("Error ACC INT1 disable\r\n");
	}
	else
	{
		/* Do Nothing (return with success) */
	}
	return s32_retval;
}

/**
*	@function	static twi_s32 kxtj3_write_reg(twi_u8 u8_reg_number, twi_u8 u8_reg_val)
*	@brief		Function used for writing to the registers of the Accelerometer "KXTJ3".
*	@param		u8_reg_number,u8_reg_val
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
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

	s32_retval = twi_i2c_master_send_n(ACCELEROMETER_I2C_CHANNEL, au8_send_data, 2, KXTJ3_I2C_ADD, TWI_TRUE);
	if(TWI_SUCCESS == s32_retval)
	{
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

/**
*	@function	static twi_s32 kxtj3_read_reg(twi_u8 u8_reg_number, twi_u8* pu8_reg_val)
*	@brief		Function used for reading registers of the Accelerometer "KXTJ3".
*	@param		u8_reg_number,pu8_reg_val
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
static twi_s32 kxtj3_read_reg(twi_u8 u8_reg_number, twi_u8* pu8_reg_val)
{
	twi_s32 s32_retval = TWI_SUCCESS;
	s32_retval = twi_i2c_master_send_n(ACCELEROMETER_I2C_CHANNEL, (twi_u8 *)&u8_reg_number, 1, KXTJ3_I2C_ADD, TWI_FALSE);
	if(TWI_SUCCESS == s32_retval)
	{
		s32_retval = twi_i2c_master_recv_n(ACCELEROMETER_I2C_CHANNEL, (twi_u8 *)pu8_reg_val, 1, KXTJ3_I2C_ADD, TWI_TRUE);
		if(TWI_SUCCESS == s32_retval)
		{
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

#ifndef KXTJ3_OPTIMIZATION_MODE
/**
*	@function	static twi_s32 kxtj3_get_full_scale(tenu_twi_accelerometer_kxtj3_full_scale_option* enu_fs)
*	@brief		Function used for reading the full scale value for the Accelerometer "KXTJ3".
*	@param[out]	enu_fs pointer to full scale value
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
static twi_s32 kxtj3_get_full_scale(tenu_twi_accelerometer_kxtj3_full_scale_option* enu_fs)
{
	twi_s32 s32_retval;
	twi_u8 u8_reg_value;

	s32_retval = TWI_SUCCESS;
	u8_reg_value = 0;

	s32_retval = kxtj3_read_reg(KXTJ3_CTRL_REG1, &u8_reg_value);
	if(TWI_SUCCESS == s32_retval)
	{
		/* Mask (RES, GSEL1, GSEL0, and EN16G) in control regiser 1 */
		/*
			Bit7    Bit6    Bit5    Bit4    Bit3    Bit2    Bit1    Bit0
			-------------------------------------------------------------
			PC1   	RES   	DRDYE   GSEL1   GSEL0   EN16G    WUFE    0
			-------------------------------------------------------------
		*/
		u8_reg_value &= 0x5C;

		if(u8_reg_value == KXTJ3_FS_2G_8_BIT_VALUE)
		{
			*enu_fs = KXTJ3_FULL_SCALE_2G_8_BIT;
		}
		else if(u8_reg_value == KXTJ3_FS_2G_12_BIT_VALUE)
		{
			*enu_fs = KXTJ3_FULL_SCALE_2G_12_BIT;
		}
		else if(u8_reg_value == KXTJ3_FS_4G_8_BIT_VALUE)
		{
			*enu_fs = KXTJ3_FULL_SCALE_4G_8_BIT;
		}
		else if(u8_reg_value == KXTJ3_FS_4G_12_BIT_VALUE)
		{
			*enu_fs = KXTJ3_FULL_SCALE_4G_12_BIT;
		}
		else if(u8_reg_value == KXTJ3_FS_8G_8_BIT_VALUE)
		{
			*enu_fs = KXTJ3_FULL_SCALE_8G_8_BIT;
		}
		else if(u8_reg_value == KXTJ3_FS_8G_12_BIT_VALUE)
		{
			*enu_fs = KXTJ3_FULL_SCALE_8G_12_BIT;
		}
		else if(u8_reg_value == KXTJ3_FS_8G_14_BIT_VALUE)
		{
			*enu_fs = KXTJ3_FULL_SCALE_8G_14_BIT;
		}
		else if(u8_reg_value == KXTJ3_FS_16G_8_BIT_VALUE1 || u8_reg_value == KXTJ3_FS_16G_8_BIT_VALUE2 || u8_reg_value == KXTJ3_FS_16G_8_BIT_VALUE3)
		{
			*enu_fs = KXTJ3_FULL_SCALE_16G_8_BIT;
		}
		else if(u8_reg_value == KXTJ3_FS_16G_12_BIT_VALUE1 || u8_reg_value == KXTJ3_FS_16G_12_BIT_VALUE2 || u8_reg_value == KXTJ3_FS_16G_12_BIT_VALUE3)
		{
			*enu_fs = KXTJ3_FULL_SCALE_16G_12_BIT;
		}
		else if(u8_reg_value == KXTJ3_FS_16G_14_BIT_VALUE)
		{
			*enu_fs = KXTJ3_FULL_SCALE_16G_14_BIT;
		}
		else
		{
			s32_retval = TWI_ERROR;
		}
	}
	else
	{
		s32_retval = TWI_ACCELEROMETER_READ_REG_ERROR;
	}
	return s32_retval;
}
#endif

/**
*	@function	static twi_s16 kxtj3_calculate_acceleration(tenu_twi_accelerometer_kxtj3_full_scale_option enu_fs, twi_s16 s16_adc_val)
*	@brief		Function used for calculate the acceleration value form the ADC reading and the full scale.
*	@param[in]	enu_fs Full scale value
*	@param[in]	s16_adc_val ADC value
*   @return     Returns the calculated acceleration value.
**/
static twi_s16 kxtj3_calculate_acceleration(tenu_twi_accelerometer_kxtj3_full_scale_option enu_fs, twi_s16 s16_adc_val)
{
	twi_s16 s16_acc_val;

	switch (enu_fs)
	{
		case KXTJ3_FULL_SCALE_2G_8_BIT:
		case KXTJ3_FULL_SCALE_2G_12_BIT:
			/* s16_acc_val = (twi_s16)((s16_adc_val * 2000ul) /32767); */
			s16_acc_val = (twi_s16) (((MUL1000(s16_adc_val) << 1) >> 15));
			break;
		case KXTJ3_FULL_SCALE_4G_8_BIT:
		case KXTJ3_FULL_SCALE_4G_12_BIT:
			/* s16_acc_val = (twi_s16)((s16_adc_val * 4000ul) /32767); */
			s16_acc_val = (twi_s16) (((MUL1000(s16_adc_val) << 2) >> 15));
			break;
		case KXTJ3_FULL_SCALE_8G_8_BIT:
		case KXTJ3_FULL_SCALE_8G_12_BIT:
		case KXTJ3_FULL_SCALE_8G_14_BIT:
			/* s16_acc_val = (twi_s16)((s16_adc_val * 8000ul) /32767); */
			s16_acc_val = (twi_s16) (((MUL1000(s16_adc_val) << 3) >> 15));
			break;
		case KXTJ3_FULL_SCALE_16G_8_BIT:
		case KXTJ3_FULL_SCALE_16G_12_BIT:
		case KXTJ3_FULL_SCALE_16G_14_BIT:
			/* s16_acc_val = (twi_s16)((s16_adc_val * 16000ul) /32767); */
			s16_acc_val = (twi_s16) (((MUL1000(s16_adc_val) << 4) >> 15));
			break;
		default:
			s16_acc_val = 0;
			break;
	}
	
	return s16_acc_val;
}

//***********************************************************
/*- APIs IMPLEMENTATION -----------------------------------*/
//***********************************************************
/**
*	@function	twi_s32 twi_accelerometer_kxtj3_init(tpf_accelerometer_kxtj3_interrupt pf_cb)
*	@brief		- Function used for initialization of Accelerometer "KXTJ3" and setting it into default state.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_init(tpf_accelerometer_kxtj3_interrupt pf_cb)
{
	twi_s32 s32_retval;
    twi_u8 u8_reg_val;

	s32_retval = TWI_SUCCESS;
	u8_reg_val = 0;

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

			if(NULL != pf_cb)
			{
				gpf_accelerometer_kxtj3_interrupt = pf_cb;		/* Setting the user Call Back function */
			}
			else
			{
				/* NO interrupt shall be called */
				s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
			}
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

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_deinit(void)
*	@brief		Function used for de-initialization of Accelerometer"KXTJ3".
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_deinit(void)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;
	/*
	 * Going to Power Down Mode.
	 */
	s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, (twi_u8)0);

	if(TWI_SUCCESS == s32_retval)
	{
		s32_retval = kxtj3_hw_deinit();

		if(TWI_SUCCESS == s32_retval)
		{
            kxtj3_init_global_reg_info_default_value();
		}
		else
		{
			s32_retval = TWI_ACCELEROMETER_HW_DEINIT_ERROR;
		}
	}
	else
	{
		s32_retval = TWI_ACCELEROMETER_HW_DEINIT_ERROR;
	}
	return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_get_axis_acc(tenu_twi_accelerometer_kxtj3_axis_acceleration enu_axis, twi_s16* ps16_axis_acc_mg)
*	@brief		Function used to read the Acceleration Values for X or Y or Z axis.
*	@param[in]	enu_axis	The type of the axis (X, Y, Z).
*	@param[out]	ps16_axis_acc_mg		Pointer to value that holds the acceleration of the axis. (The output is in mg)
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
**/
twi_s32 twi_accelerometer_kxtj3_get_axis_acc(tenu_twi_accelerometer_kxtj3_axis_acceleration enu_axis, twi_s16* ps16_axis_acc_mg)
{
	twi_s32 s32_retval = TWI_SUCCESS;

	twi_u8 u8_axis_val_L = 0;
	twi_u8 u8_axis_val_H = 0;
	twi_s16 s16_acc_val = 0;
	twi_u8 u8_reg_val = 0;
	tenu_twi_accelerometer_kxtj3_full_scale_option enu_fs;
	TWI_MEMSET(&enu_fs, 0, sizeof(enu_fs));

	if (NULL != ps16_axis_acc_mg)
	{
		twi_u8 u8_kxtj3_out_l = 0;
		twi_u8 u8_kxtj3_out_h = 0;
		
		switch (enu_axis)
		{
			case KXTJ3_X_AXIS_ACCELERATION:
				u8_kxtj3_out_l = KXTJ3_OUT_X_L;
				u8_kxtj3_out_h = KXTJ3_OUT_X_H;
				break;
			case KXTJ3_Y_AXIS_ACCELERATION:
				u8_kxtj3_out_l = KXTJ3_OUT_Y_L;
				u8_kxtj3_out_h = KXTJ3_OUT_Y_H;
				break;
			case KXTJ3_Z_AXIS_ACCELERATION:
				u8_kxtj3_out_l = KXTJ3_OUT_Z_L;
				u8_kxtj3_out_h = KXTJ3_OUT_Z_H;
				break;
			default:
				s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
				break;
		}

#ifndef KXTJ3_OPTIMIZATION_MODE
		/* ensure that the acc in the operation mode */
		s32_retval = kxtj3_read_reg(KXTJ3_CTRL_REG1, &u8_reg_val);
#endif	
		if(TWI_SUCCESS == s32_retval)
		{
			u8_reg_val &= 0x7F;
			u8_reg_val |= ((twi_u8)(1 << KXTJ3_CTRL_REG1_PC1));
#ifndef KXTJ3_OPTIMIZATION_MODE
			/* TODO: Check the mode first before this step */
			s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, u8_reg_val);
#endif	
			if(TWI_SUCCESS == s32_retval)
			{
				do{
					s32_retval = kxtj3_read_reg(u8_kxtj3_out_l, &u8_axis_val_L);
					TWI_ERROR_BREAK(s32_retval);
					s32_retval = kxtj3_read_reg(u8_kxtj3_out_h, &u8_axis_val_H);
					TWI_ERROR_BREAK(s32_retval);
					s16_acc_val = (twi_s16) (u8_axis_val_L | (u8_axis_val_H << 8));
#ifdef KXTJ3_OPTIMIZATION_MODE
					enu_fs = genu_full_scale_optimization;
#else
					s32_retval = kxtj3_get_full_scale(&enu_fs);
					TWI_ERROR_BREAK(s32_retval);
#endif
					
				}while (0);

				*ps16_axis_acc_mg = kxtj3_calculate_acceleration(enu_fs, s16_acc_val);
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

	return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_get_6d_direction(tenu_twi_accelerometer_kxtj3_6d_direction* penu_6d_dir)
*	@brief		Function used to read the movement direction for the Accelerometer"KXTJ3" Usage when interrupt occurs.
*	@param[out]	penu_6d_dir	pointer to the direction of movement.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
**/
twi_s32 twi_accelerometer_kxtj3_get_6d_direction(tenu_twi_accelerometer_kxtj3_6d_direction* penu_6d_dir)
{
	twi_s32 s32_retval;
	twi_u8 u8_reg_val;

	s32_retval = TWI_SUCCESS;
	u8_reg_val = 0;

	if(NULL != penu_6d_dir)
	{
		s32_retval = kxtj3_read_reg(KXTJ3_INT2_SRC, &u8_reg_val);
		if(TWI_SUCCESS == s32_retval)
		{
			/* Mask the 6 Least Significant Bits in interrupt source 2 register */
			/*
			  	Bit7    Bit6    Bit5    Bit4    Bit3    Bit2    Bit1    Bit0
			   	-------------------------------------------------------------
				 0   	 0   	XNWU    XNWU    YNWU    YNWU    ZNWU    ZNWU
				-------------------------------------------------------------
			*/
			u8_reg_val &= 0x3F;

			switch (u8_reg_val)
			{
				case KXTJ3_MOVE_X_NEG:
				case KXTJ3_MOVE_X_POS:
				case KXTJ3_MOVE_Y_NEG:
				case KXTJ3_MOVE_Y_POS:
				case KXTJ3_MOVE_Z_NEG:
				case KXTJ3_MOVE_Z_POS:
					*penu_6d_dir = (tenu_twi_accelerometer_kxtj3_6d_direction)u8_reg_val;
					break;
				default:
					*penu_6d_dir = KXTJ3_NO_MOVE;
					break;
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

	return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_set_full_scale(tenu_twi_accelerometer_full_scale_option enu_fs)
*	@brief		Function used to set the KXTJ3 Full Scale.
*	@param[in]	enu_fs	enum variable must be one of the following:
*	(KXTJ3_FULL_SCALE_2G_8_BIT ::), (KXTJ3_FULL_SCALE_2G_12_BIT ::),(KXTJ3_FULL_SCALE_4G_8_BIT ::), 
*	(KXTJ3_FULL_SCALE_4G_12_BIT ::), (KXTJ3_FULL_SCALE_8G_8_BIT ::),(KXTJ3_FULL_SCALE_8G_12_BIT ::), 
*	(KXTJ3_FULL_SCALE_8G_14_BIT ::),(KXTJ3_FULL_SCALE_16G_8_BIT ::), (KXTJ3_FULL_SCALE_16G_12_BIT ::), 
*	(KXTJ3_FULL_SCALE_16G_14_BIT ::)
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
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

#ifdef KXTJ3_OPTIMIZATION_MODE
	genu_full_scale_optimization = enu_fs;
#endif

#ifdef ENABLE_START_UP_DELAY
	/* Start up time is from PC1 bit set to 1 in CTRL_REG1 register to valid outputs. Time varies with ODR and power mode*/
	TWI_DELAY_MS(START_UP_DELAY_MS);
#endif

	return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_set_data_rate_config(tenu_twi_accelerometer_kxtj3_odr_cfg enu_odr)
*	@brief		Function used to set the KXTJ3 Data rate configuration.
*	@param[in]	enu_odr	enum variable (Data Rate CFG) must be one of the following:
*					(KXTJ3_ODR_0_781Hz ::), (KXTJ3_ODR_1_563Hz ::), (KXTJ3_ODR_3_125Hz ::), (KXTJ3_ODR_6_25Hz ::), 
*    				(KXTJ3_ODR_12_5Hz ::)(KXTJ3_ODR_25Hz ::), (KXTJ3_ODR_50Hz::), (KXTJ3_ODR_100Hz ::),
*					(KXTJ3_ODR_200Hz ::),(KXTJ3_ODR_400Hz ::),(KXTJ3_ODR_800Hz ::),(KXTJ3_ODR_1600Hz ::)
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
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

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_set_interrupt_thershold(twi_u8 u8_th_val)
*	@brief		Function used to set the threshold of the interrupt accelerometer "KXTJ3".
*				WAKEUP_THRESHOLD (counts) = Desired Threshold (g) x 256 (counts/g)
*	@param[in]	u8_th_val	Threshold value for Interrupt 1 (value from 0 to 127) else error value should be returned.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_set_interrupt_thershold(twi_u8 u8_th_val)
{
	twi_s32 s32_retval = TWI_SUCCESS;
	twi_u8 u8_reg_val = 0;

	if(u8_th_val <= 127)
	{
		/*
		 *      The Threshold register value range of this accelerometer is 0: 4096 (12-bits)
		 *  	we will use the MSB Threshold register "THRESHOLD_H" only to match the other accelerometers.
		 * 		We will discard the LSB 4 bits in "THRESHOLD_H" and handle the threshold as 8-bits.
		 * 		Threshold = ((u8_th_val << 4) /256)
		 */
		s32_retval = kxtj3_read_reg(KXTJ3_CTRL_REG1, &u8_reg_val);
		if(TWI_SUCCESS == s32_retval)
		{
			/* Set the ACC in Stand-by mode in order to set the interrupt threshold */
			u8_reg_val &= 0x7F;
			u8_reg_val |= ((twi_u8)(0 << KXTJ3_CTRL_REG1_PC1));
			s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, u8_reg_val);
			if(TWI_SUCCESS == s32_retval)
			{
				s32_retval = kxtj3_write_reg(KXTJ3_WAKE_UP_THRESHOLD_H, u8_th_val);
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

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_set_shock_thershold(twi_u8 u8_th_val)
*	@brief		Function used to set the threshold of the shock interrupt accelerometer "KXTJ3".
*	@param[in]	u8_th_val	Threshold value for Interrupt 1 (value from 0 to 127) else error value should be returned.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_set_shock_thershold(twi_u8 u8_th_val)
{
	twi_s32 s32_retval = TWI_ACCELEROMETER_UNSUPPORTED_FEATURE;

	return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_set_shock_duration(twi_u8 u8_th_val)
*	@brief		Function used to set the Set the minimum duration of the Shock Interrupt 1 event to be recognized for the accelerometer "KXTJ3".
*	@param[in]	u8_duration_val	Duration value for Interrupt 1 (value from 0 to 127) else error value should be returned.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_set_shock_duration(twi_u8 u8_th_val)
{
	twi_s32 s32_retval = TWI_ACCELEROMETER_UNSUPPORTED_FEATURE;

	return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_set_interrupt_duration(twi_u8 u8_duration_val)
*	@brief		Function used to set the Set the minimum duration of the Interrupt 1 event to be recognized for the accelerometer "KXTJ3".
*				The duration value depends on the ODR value (It's 7 bits only full scale 2^7 = 128).
*				Duration LSB value = 1/ODR. The next table indicates the duration LSB values.
*					 ___________________________________________
*					|				|							|
*					|	 ODR (Hz)	|	Duration LSB value (ms)	|
*					|_______________|___________________________|
*					|	1 (1.563)	|		(1000) 1563			|
*					|_______________|___________________________|
*					|	10 (12.5)	|		(100) 125			|
*					|_______________|___________________________|
*					|	  	25		|			40				|
*					|_______________|___________________________|
*					|	 	50		|			20				|
*					|_______________|___________________________|
*					|	 	100		|			10				|
*					|_______________|___________________________|
*					|	 	200		|			5				|
*					|_______________|___________________________|
*					|	 	400		|			2.5				|
*					|_______________|___________________________|
*
*	@param[in]	u8_duration_val	Duration value for Interrupt 1 (value from 0 to 127) else error value should be returned.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_set_interrupt_duration(twi_u8 u8_duration_val)
{
	twi_s32 s32_retval = TWI_SUCCESS;
	twi_u8 u8_reg_val = 0;

	if(u8_duration_val <= 127)
	{
		s32_retval = kxtj3_read_reg(KXTJ3_CTRL_REG1, &u8_reg_val);
		if(TWI_SUCCESS == s32_retval)
		{
			/* Set the ACC in Stand-by mode in order to adjust the interrupt duration */
			u8_reg_val &= 0x7F;
			u8_reg_val |= ((twi_u8)(0 << KXTJ3_CTRL_REG1_PC1));
			s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, u8_reg_val);
			if(TWI_SUCCESS == s32_retval)
			{
				s32_retval = kxtj3_write_reg(KXTJ3_WAKE_UP_COUNTER, u8_duration_val);
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

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_free_fall_detect(void)
*	@brief		Function used to enable the free fall detection interrupt.
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_free_fall_detect(void)
{
	twi_s32 s32_retval = TWI_ACCELEROMETER_UNSUPPORTED_FEATURE;

	return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_movement_detect(void)
*	@brief		Function used to enable the movement detection interrupt.
*				- It sets the following settings:
*					+ Disable the accelerometer interrupt.
*					+ Clear any previous interrupts.
*					+ Re-enable the accelerometer interrupt.
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_movement_detect(void)
{
	twi_s32 s32_retval = TWI_SUCCESS;
	twi_u8 u8_reg_val = 0;

	/* Disable Accelerometer interrupt */
	s32_retval = kxtj3_int1_disable();	

	s32_retval = kxtj3_read_reg(KXTJ3_CTRL_REG1, &u8_reg_val);
	if(TWI_SUCCESS == s32_retval)
	{
		/* Set the ACC in Stand-by mode in order to enable the motion detection */
		u8_reg_val &= 0x7F;
		u8_reg_val |= ((twi_u8)(0 << KXTJ3_CTRL_REG1_PC1));
		s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, u8_reg_val);
		if(TWI_SUCCESS == s32_retval)
		{
			/*Get the enabled interrupts. This is for supporting Shock + Movement.*/
    		s32_retval = kxtj3_read_reg(KXTJ3_INT_CTRL_REG1, &u8_reg_val);

			u8_reg_val |= (1 << KXTJ3_CTRL_REG1_IEN);		/* 0: Disable physical interrupt pin (INT), 1: Enable physical interrupt pin (INT) */
			u8_reg_val |= (1 << KXTJ3_CTRL_REG1_IEA);		/* 0: INT is active LOW, 1: INT is active HIGH */
			u8_reg_val |= (0 << KXTJ3_CTRL_REG1_IEL);		/* 0: INT latches until it is cleared by reading INT_REL, 1:INT transmit one pulse with a period of 0.03 */

			s32_retval = kxtj3_write_reg(KXTJ3_INT_CTRL_REG1, u8_reg_val);

			/*
			 * Configuration for the movement detection interrupt:
			 * 		1- Enable the interrupt 1 for OR combination of interrupt events.
			 * 		2- Enable the interrupt of all 6D directions (X+/-, Y+/-, Z+/-).
			 */
			s32_retval = kxtj3_write_reg(KXTJ3_INT_CTRL_REG2, (twi_u8)
											((0 << KXTJ3_CTRL_REG2_ULMODE)	|	/* 0: Disable the unlatched mode  1: Enable the unlatched mode */
											 (1 << KXTJ3_CTRL_REG2_XNWUE)	|	/* Enable interrupt generation on X -ve event or on Direction recognition.
														 	 	 	 		 	 	(0: disable interrupt request  1: enable interrupt request) */
											 (1 << KXTJ3_CTRL_REG2_XPWUE)	|	/* Enable interrupt generation on X +ve event or on Direction recognition.
														 	 	 	 		 	 	(0: disable interrupt request  1: enable interrupt request) */
											 (1 << KXTJ3_CTRL_REG2_YNWUE)	|	/* Enable interrupt generation on Y -ve event or on Direction recognition.
														 	 	 	 		 	 	(0: disable interrupt request  1: enable interrupt request) */
											 (1 << KXTJ3_CTRL_REG2_YPWUE)	|	/* Enable interrupt generation on Y +ve event or on Direction recognition.
														 	 	 	 		 	 	(0: disable interrupt request  1: enable interrupt request) */
											 (1 << KXTJ3_CTRL_REG2_ZNWUE)	|	/* Enable interrupt generation on Z -ve event or on Direction recognition.
														 	 	 	 	 	 		(0: disable interrupt request  1: enable interrupt request) */
											 (1 << KXTJ3_CTRL_REG2_ZPWUE)));	/* Enable interrupt generation om Z +ve event or on Direction recognition.
														 	 	 	 	 	 	 	 (0: disable interrupt request  1: enable interrupt request) */


			s32_retval = kxtj3_read_reg(KXTJ3_INT_REL,&u8_reg_val);				/* Clear any interrupts */
			s32_retval = kxtj3_read_reg(KXTJ3_INT_REL,&u8_reg_val);				/* Clear any interrupts */

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

#ifdef ENABLE_START_UP_DELAY
	/* Start up time is from PC1 bit set to 1 in CTRL_REG1 register to valid outputs. Time varies with ODR and power mode*/
	TWI_DELAY_MS(START_UP_DELAY_MS);
#endif

	s32_retval = kxtj3_int1_enable();				/* Re-enable the Accelerometer interrupt */

  	return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_position_detect(void)
*	@brief		Function used to enable the position detection interrupt.
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_position_detect(void)
{
	twi_s32 s32_retval = TWI_ACCELEROMETER_UNSUPPORTED_FEATURE;

	return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_shock_detect(void)
*	@brief		Function used to enable the shock detection interrupt.
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_shock_detect(void)
{
	twi_s32 s32_retval = TWI_ACCELEROMETER_UNSUPPORTED_FEATURE;

	return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_no_detect(void)
*	@brief		Function used to disable the detection interrupt on all events.
*				- It sets the following settings:
*					+ Disable the accelerometer interrupt.
*					+ Clear any previous interrupts.
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_no_detect(void)
{
	twi_u8 u8_reg_val = 0;
	twi_s32 s32_retval = TWI_SUCCESS;
	
	s32_retval = kxtj3_int1_disable();	/* Disable Accelerometer interrupt */

	s32_retval = kxtj3_read_reg(KXTJ3_CTRL_REG1, &u8_reg_val);
	if(TWI_SUCCESS == s32_retval)
	{
		/* Set the ACC in Stand-by mode in order to disable the motion detection */
		u8_reg_val &= 0x7F;
		u8_reg_val |= ((twi_u8)(0 << KXTJ3_CTRL_REG1_PC1));
		s32_retval = kxtj3_write_reg(KXTJ3_CTRL_REG1, u8_reg_val);
		if(TWI_SUCCESS == s32_retval)
		{
			s32_retval = kxtj3_write_reg(KXTJ3_INT_CTRL_REG1, (twi_u8)(0x00));		/* Clear KXTJ3_INT_CTRL_REG1 */
			s32_retval = kxtj3_write_reg(KXTJ3_INT_CTRL_REG2, (twi_u8)(0x00));		/* Clear KXTJ3_INT_CTRL_REG2 */
			s32_retval = kxtj3_read_reg(KXTJ3_INT_REL,&u8_reg_val);					/* Clear any interrupts */

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

#ifdef ENABLE_START_UP_DELAY
	/* Start up time is from PC1 bit set to 1 in CTRL_REG1 register to valid outputs. Time varies with ODR and power mode*/
	TWI_DELAY_MS(START_UP_DELAY_MS);
#endif

	return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_get_interrupt_cause(twi_u8 *pu8_interrupt_cause)
*	@brief		Function used to Get the cause of the interrupt of the accelerometer.
*	@param[out]	pu8_interrupt_cause	    filled with the cause of interrupt. It is an ORed flags of tenu_twi_accelerometer_kxtj3_interrupt_cause.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_get_interrupt_cause(twi_u8 *pu8_interrupt_cause)
{
    twi_s32 s32_retval;
    
    if(NULL != pu8_interrupt_cause)
    {
        twi_u8 u8_reg_val;
        *pu8_interrupt_cause = 0;

        /*Check Wake up interrupt .*/
        u8_reg_val = 0;
        s32_retval = kxtj3_read_reg(KXTJ3_INT1_SRC, &u8_reg_val);
        if(u8_reg_val & (1 << KXTJ3_INT1_SRC_WUFS))
        {        
        	/*Check if the interrupt is due to movement or free fall.*/
        	u8_reg_val = 0;
        	s32_retval = kxtj3_read_reg(KXTJ3_INT2_SRC, &u8_reg_val);
        	if( (u8_reg_val & (1 << KXTJ3_INT2_SRC_XNWU)) ||
        	    (u8_reg_val & (1 << KXTJ3_INT2_SRC_XPWU)) ||
				(u8_reg_val & (1 << KXTJ3_INT2_SRC_YNWU)) ||
				(u8_reg_val & (1 << KXTJ3_INT2_SRC_YPWU)) ||
				(u8_reg_val & (1 << KXTJ3_INT2_SRC_ZNWU)) ||
        	    (u8_reg_val & (1 << KXTJ3_INT2_SRC_ZPWU)) )
        	{
        	        /*Free Fall.*/
        	        *pu8_interrupt_cause |= ACCELEROMTER_KXTJ3_MOVED;
        	}
		}
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }
    
    return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_get_fifo_content(twi_u8 u8_needed_levels_num, twi_s16 *ps16_acc_fifo_buf, twi_u8* pu8_actual_levels_num)
*	@brief		Function used to Get the content of the FIFO.
*	@param[in]		u8_needed_levels_num	    the number of level to read.
*	@param[in,out]	ps16_acc_fifo_buf   		the FIFO buffer.
*	@param[out]		pu8_actual_levels_num	    the actual number or read levels.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_get_fifo_content(twi_u8 u8_needed_levels_num, twi_s16 *ps16_acc_fifo_buf, twi_u8* pu8_actual_levels_num)
{
	twi_s32 s32_retval = TWI_ACCELEROMETER_UNSUPPORTED_FEATURE;

	return s32_retval;
}

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_get_num_of_fifo_levels(twi_u8* pu8_actual_levels_num)
*	@brief		Function used to Get the actual number of the FIFO levels.
*	@param[out]		pu8_actual_levels_num	    the actual number or read levels.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_get_num_of_fifo_levels(twi_u8* pu8_actual_levels_num)
{
	twi_s32 s32_retval = TWI_ACCELEROMETER_UNSUPPORTED_FEATURE;

	return s32_retval;
}

/**
*	@function	twi_accelerometer_kxtj3_check_validity_config(twi_bool* pb_validity)
*	@brief		Function used for validity the configration of the Accelerometer "KXTJ3".
*	@param[out]		pb_validity	the accelerometer configration validity, valid : TWI_TRUE or not valid: TWI_FALSE.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_check_validity_config(twi_bool* pb_validity)
{
	twi_s32 s32_retval = TWI_SUCCESS;
    if(NULL != pb_validity)
    {
        twi_u8 u8_idx;
        *pb_validity = ACC_CONFIG_VALID;
        
        for(u8_idx = 0; u8_idx < MAX_NUM_REG; u8_idx++)
        {
            twi_u8 u8_trial_counter = MAX_NUM_TRIALS_READ_REG;
            do
            {
                twi_u8 u8_reg_val = 0;
                s32_retval = kxtj3_read_reg(gastr_acc_kxtj3_reg_info[u8_idx].u8_reg_num, &u8_reg_val);
                if(TWI_SUCCESS == s32_retval)
                {
                    if(u8_reg_val != gastr_acc_kxtj3_reg_info[u8_idx].u8_reg_value)
                    {
                        *pb_validity = ACC_CONFIG_NOT_VALID;
                        break; 
                    }
                }
            }while((TWI_SUCCESS != s32_retval) && (u8_trial_counter--));
            
			if((TWI_SUCCESS != s32_retval) || (ACC_CONFIG_NOT_VALID == *pb_validity))
			{
				break; 
			}
        }
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }
    
	return s32_retval;
}
