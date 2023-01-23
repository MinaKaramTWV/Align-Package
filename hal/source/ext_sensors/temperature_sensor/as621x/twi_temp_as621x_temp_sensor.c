/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved.                  */
/****************************************************************************/

/**
 *	@file					twi_temp_as621x_temp_sensor.c
 *
 *	@brief					This file includes implementation of AS621x temperature sensor
 *							TS stands for temperature sensor
 *							AS621x data sheet :
 *							https://dammedia.osram.info/media/resource/hires/osram-dam-25175641/AS621x_DS000677_3-00.pdf
 */

/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/
#include "twi_i2c_master.h"
#include "platform_defines.h"

/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/

#ifdef  TEMP_SENSE_LOG_ENABLE
	#include"twi_debug.h"
	#define	TEMP_SENSE_LOG(MSG)								TWI_LOGGER("[TEMP_SENSE]: "MSG)
	#define TEMP_SENSE_LOG_ERR(MSG)							TWI_LOGGER_ERR("[TEMP_SENSE_ERR]: "MSG)
#else
	#define	TEMP_SENSE_LOG(MSG)
	#define TEMP_SENSE_LOG_ERR(MSG)
#endif

#define AS621X_I2C_CHANNEL								(AS621X_TEMP_SEN_I2C_CH)
#define AS621X_I2C_ADD_SIZE								(SEVEN_BITS)
#define AS621X_I2C_CLOCK								(I2C_SCL_100K)
#define AS621X_SLAVE_ADD								(0x48)							/* AS621x I2C slave address */


/*-*********************************************************/
/* 			   AS621X Register list     			       */
/*-*********************************************************/

#define	AS621X_TEMP_TVAL_REG 					    (0x00)							/* Contains the temperature value. */
#define	AS621X_CONFIG_REG	 				        (0x01)							/* Configuration settings of the temperature sensor. */
#define	AS621X_TLOW_REG 				            (0x02)							/* Low temperature threshold value. */
#define	AS621X_THIGH_REG 				            (0x03)							/* High temperature threshold value. */


#define AS621X_CONFIG_REG_VAL_MSB					(0xA0)							/* 1010 0000; Sleep Mode disabled, interrupt mode disabled, continuous conversion mode. */		
#define AS621X_CONFIG_REG_VAL_LSB					(0x40)							/* 0100 0000; Conversion rate = 1 Hz. */						

/*---------------------------------------------------------*/
/*- Global Variables --------------------------------------*/
/*---------------------------------------------------------*/
twi_bool gb_as621x_is_init = TWI_FALSE;

/*---------------------------------------------------------*/
/*- API's Implementation ----------------------------------*/
/*---------------------------------------------------------*/

/*
 *	@function	twi_s32 twi_temp_sensor_init(void)
 *  @brief		Function used for initialization of Temperature sensor "AS621x".
 *  @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */
twi_s32 twi_temp_sensor_init(void)
{
	twi_s32 s32_retval = TWI_SUCCESS;

	tstr_twi_i2c_master_config str_i2c;

	str_i2c.u8_addr_size = AS621X_I2C_ADD_SIZE;
	str_i2c.u32_clock = AS621X_I2C_CLOCK;
	str_i2c.u8_pull_up = GET_I2C_PULL_CFG(AS621X_I2C_CHANNEL);
	
	s32_retval = twi_i2c_master_init(AS621X_I2C_CHANNEL, &str_i2c);
	if(TWI_SUCCESS == s32_retval)
	{
		twi_u8 au8_tx_buff[]={AS621X_CONFIG_REG, AS621X_CONFIG_REG_VAL_MSB, AS621X_CONFIG_REG_VAL_LSB};

		s32_retval = twi_i2c_master_send_n(AS621X_I2C_CHANNEL, au8_tx_buff, sizeof(au8_tx_buff), AS621X_SLAVE_ADD, TWI_TRUE);
		if(TWI_SUCCESS == s32_retval)
		{
			TEMP_SENSE_LOG("AS621x Temp Sensor successfully init \n");
			gb_as621x_is_init =	TWI_TRUE;
		}
		else
		{
			/* Do Nothing, return with error */
			TWI_LOGGER_ERR("AS621x Error = %d\r\n", s32_retval);
		}
	}
	else
	{
		/* Do Nothing, return with error */
	}

	return s32_retval;
}

/*
 *	@function	twi_s32 twi_temp_sensor_deinit(void)
 *  @brief		Function used for de-initialization of Temperature sensor "AS621x".
 *  @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */
twi_s32 twi_temp_sensor_deinit(void)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;
	if(TWI_TRUE == gb_as621x_is_init)
	{
		s32_retval = twi_i2c_master_deinit(AS621X_I2C_CHANNEL);
		gb_as621x_is_init =	TWI_FALSE;
	}

	return s32_retval;
}

/*
 *	@function	twi_s32 twi_temp_sensor_read(twi_s16 *ps16_temp_val)
 *  @brief		Function used for reading temperature sensor "AS621x".
 *  @param[out] ps16_temp_val   The temperature value read from the temperature sensor multipled by 100.
 *  @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */
twi_s32 twi_temp_sensor_read(twi_s16 *ps16_temp_val)
{
	twi_s32 s32_retval = TWI_SUCCESS;
	twi_s16 s16_temp_val = 0;

	twi_u8 au8_tx_buf[] = {AS621X_TEMP_TVAL_REG};							/* 1 byte just enough for transmitting measure temperature command */
	twi_u8 au8_rx_buf[] = {0x00, 0x00};								/* 2 bytes just enough for receiving MSB and LSB of temperature */

	if(NULL != ps16_temp_val)
	{
		if(TWI_TRUE == gb_as621x_is_init)
		{
			s32_retval = twi_i2c_master_send_n(AS621X_I2C_CHANNEL, au8_tx_buf, sizeof(au8_tx_buf), AS621X_SLAVE_ADD, TWI_FALSE);
			if(TWI_SUCCESS == s32_retval)
			{
				s32_retval = twi_i2c_master_recv_n(AS621X_I2C_CHANNEL, au8_rx_buf, sizeof(au8_rx_buf), AS621X_SLAVE_ADD, TWI_TRUE);
				if(TWI_SUCCESS == s32_retval)
				{

					s16_temp_val = TWO_BYTE_CONCAT(au8_rx_buf[0], au8_rx_buf[1]);

					*ps16_temp_val = (twi_s32) (((twi_s32) s16_temp_val) * 100) / 128;
				}
				else
				{
					/* Do Nothing, return with error */
				}
			}
			else
			{
				/* Do Nothing, return with error */
			}
		}
		else
		{
			s32_retval = TWI_ERROR_NOT_INITIALIZED;
		}
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	}

	return s32_retval;
}

/*
 *   @brief      This is a function that dispatch global flags.
 *   @param[out]  void.
 *   @retval      void.
 */
void twi_temp_sensor_dispatch(void)
{
	/*Do Nothing.*/
}

