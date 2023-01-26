/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_i2c_master.h
*   @brief      This file contains TWI I2C HAL.
*/

#ifndef _TWI_I2C_MASTER_H_
#define _TWI_I2C_MASTER_H_
/**
*   @defgroup i2c_master_group TWI I2C HAL
*   This is the definition of TWI HAL for I2C.
*   @{
*/

/*----------------------------------------------------------*/
/*- INCLUDES -----------------------------------------------*/
/*----------------------------------------------------------*/

#include "twi_common.h"
#include "platform_defines.h"

/*----------------------------------------------------------*/
/*- CONSTANTS ----------------------------------------------*/
/*----------------------------------------------------------*/

/**
*   @defgroup i2c_master_scl_frequencey_group TWI I2C master HAL SCL frequencies
*   This is the definition of TWI HAL SCL frequency for I2C.
*   @{
*/

#define I2C_SCL_100K        PLATFORM_I2C_SCL_100K

#define I2C_SCL_250K        PLATFORM_I2C_SCL_250K

#define I2C_SCL_400K        PLATFORM_I2C_SCL_400K

/**
*   @defgroup i2c_master_ch TWI I2C master HAL Channels
*   This is the definition of TWI HAL Channels for I2C.
*   @{
*/
#define HDC10XX_HUM_SEN_I2C_CH              PLATFORM_HDC10XX_HUM_SEN_I2C_CH
#define SI7020A10_TEMP_SEN_I2C_CH   		PLATFORM_SI7020A10_TEMP_SEN_I2C_CH
#define FRIDGE_TAG_TEMP_SEN_CH				PLATFORM_FRIDGE_TAG_TEMP_SEN_CH
#define SI7020A10_HUM_SEN_I2C_CH   			PLATFORM_SI7020A10_HUM_SEN_I2C_CH
#define LIS3DH_ACC_SEN_I2C_CH				PLATFORM_LIS3DH_ACC_SEN_I2C_CH
#define DEBUG_I2C_CH						PLATFORM_DEBUG_I2C_CH

#define GET_I2C_PULL_CFG(ch) 				/*lint -save -e506 */PLATFORM_GET_I2C_PULL_CFG(ch)/*lint -restore */
/** @} */   /*i2c_master_scl_frequencey_group*/

#define SEVEN_BITS				7

#define TEN_BITS				10

#define TWI_INT_PULL_UP			0			/**< @brief Internal pull up resistor*/

#define TWI_EXT_PULL_UP			1			/**< @brief External pull up resistor*/
/*----------------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*----------------------------------------------------------*/

/**   @brief  The twi_i2c_master module input.
*/
typedef struct
{
    /**
    *   The I2C address size. It can be ::SEVEN_BITS or ::TEN_BITS.
    *   If the used address size is not supported by the platform, the initialization API will return an error.
    */
    twi_u8 u8_addr_size;
	
	
    /**
       *   Pull up resistor. It can be ::INT_PULL_UP or ::EXT_PULL_UP.
       */
    twi_u8  u8_pull_up;

    /**
    *   Set the SCL frequency of the module. The module SCL frequency can be one of @ref i2c_master_scl_frequencey_group.
    *   If the used frequency is not supported with the platform, the initialization API will return an error.
    */
    twi_u32 u32_clock;

    /**
       *   Enables the multiplexed instance of the i2c if it is supported.
       */
    twi_bool b_multiplex_enable;

}tstr_twi_i2c_master_config;

/*----------------------------------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/
/*----------------------------------------------------------*/

/**
*   @brief      This function initializes the I2C module.
*   @param[in]  u8_channel_num          The channel number. At least there will be channel 0.
*	@param[in]  pstr_i2c_master_cfg     a pointer to tstr_twi_i2c_master_config.
*                                       It defines the input methods and flags need by the module see @ref tstr_twi_i2c_master_config.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_i2c_master_init(twi_u8 u8_channel_num, const tstr_twi_i2c_master_config *pstr_i2c_master_cfg);

/**
*   @brief      This function de-initializes the I2C module.
*   @param[in]  u8_channel_num          The channel number.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_i2c_master_deinit(twi_u8 u8_channel_num);

/**
*   @brief      This function that sends array of bytes to slave device over I2C.
*   @param[in]  u8_channel_num  The channel number.
*   @param[in]  pu8_buf         A character array to be sent.
*	@param[in]  u16_len         The length of pu8_buf.
*	@param[in]  u16_addr         I2C slave address. The address size will be as given in tstr_twi_i2c_master_config::u8_addr_size.
*	@param[in]  b_stop          if ::TWI_TRUE, the I2C will send stop pattern at the end. Otherwise, it will not send it.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_i2c_master_send_n( twi_u8 u8_channel_num, const twi_u8 *pu8_buf, twi_u16 u16_len, twi_u16 u16_addr, twi_bool b_stop);


/**
*   @brief      This function receives array of bytes from slave device over I2C.
*   @param[in]  u8_channel_num  The channel number.
*   @param[out] pu8_buf         The received character array will be returned in it.
*	@param[in]  u16_len         The length of pu8_buf.
*	@param[in]  u16_addr        I2C slave address. The address size will be as given in tstr_twi_i2c_master_config::u8_addr_size
*	@param[in]  b_stop          if ::TWI_TRUE, the I2C will send stop pattern at the end. Otherwise, it will not send it.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_i2c_master_recv_n(twi_u8 u8_channel_num, twi_u8 *pu8_buf, twi_u16 u16_len, twi_u16 u16_addr, twi_bool b_stop);

/**
*   @brief      This is the function that continue receiving array of bytes from slave device over I2C.
*	@detail		This API will not initiate a new receiving frame. However, it will continue the current one.
* 				It will apply a start condition or addressing the slave with read bit.
*   @param[in]  u8_channel_num  The channel number.
*   @param[out] pu8_buf         The received character array will be returned in it.
*	@param[in]  u16_len         The length of @b pu8_buf.
*	@param[in]  b_stop          if ::TWI_TRUE, the I2C will send stop pattern at the end. Otherwise, it will not send it.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_i2c_master_cont_recv_n(twi_u8 u8_channel_num, twi_u8 *pu8_buf, twi_u16 u16_len, twi_bool b_stop);

/**
*   @brief      This function returns the status of the channel.
*   @param[in]  u8_channel_num  The channel number.
*   @return     ::TWI_I2C_FREE_CHANNEL, ::TWI_I2C_RESERVED_CHANNEL, ::TWI_ERROR_RESOURCE_NOT_FOUND.
*/
twi_s32 twi_i2c_master_status(twi_u8 u8_channel_num);

/** @} */   /*i2c_master_group*/

#endif  /*_I2C_MASTER_H_*/
