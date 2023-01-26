/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_adc.h
*   @brief      This file contains TWI ADC HAL.
*/

#ifndef _ADC_H_
#define _ADC_H_
/**
*   @defgroup adc_group TWI ADC HAL
*   This is the definition of TWI HAL for ADC.
*   @{
*/

/*----------------------------------------------------------*/
/*- INCLUDES -----------------------------------------------*/
/*----------------------------------------------------------*/

#include "twi_common.h"

/*----------------------------------------------------------*/
/*- CONSTANTS ----------------------------------------------*/
/*----------------------------------------------------------*/

/**
*   @defgroup adc_flags_group TWI ADC HAL flags
*   This is the definition of TWI HAL flags for ADC.
*   @{
*/

/**
*   @brief      ADC resolution Position.
*/
#define TWI_ADC_RES_POS                                 0x00

/**
*   @brief      ADC resolution Mask.
*/
#define TWI_ADC_RES_MASK                                (0x07 << TWI_ADC_RES_POS)

/**
*   @brief  Set the AD resolution to 8-bits.
*/
#define TWI_ADC_RES_8_BITS                              (0 << TWI_ADC_RES_POS)

/**
*   @brief  Set the AD resolution to 9-bits.
*/
#define TWI_ADC_RES_9_BITS                              (1 << TWI_ADC_RES_POS)

/**
*   @brief  Set the AD resolution to 10-bits.
*/
#define TWI_ADC_RES_10_BITS                             (2 << TWI_ADC_RES_POS)

/**
*   @brief  Set the AD resolution to 10-bits.
*/
#define TWI_ADC_RES_12_BITS                             (3 << TWI_ADC_RES_POS)

/**
*   @brief  Set the AD resolution to 10-bits.
*/
#define TWI_ADC_RES_14_BITS                             (4 << TWI_ADC_RES_POS)

/**
*   @brief      ADC Vref Position.
*/
#define TWI_ADC_VREF_POS                                0x03

/**
*   @brief      ADC Vref Mask.
*/
#define TWI_ADC_VREF_MASK                               (0x03 << TWI_ADC_VREF_POS)

/**
*   @brief  use an internal reference voltage.
*/
#define TWI_ADC_VREF_INTERNAL_REF                       (0 << TWI_ADC_VREF_POS)

/**
*   @brief  Use an external reference voltage.
*/
#define TWI_ADC_VREF_EXTERNAL_REF                       (1 << TWI_ADC_VREF_POS)

/**
*   @brief  Use VDD as reference voltage.
*/
#define TWI_ADC_VREF_VDD_REF                            (2 << TWI_ADC_VREF_POS)

/**
*   @brief      ADC Vref divider.
*/
#define TWI_ADC_VREF_DIVIDER_POS                        0x05

/**
*   @brief      ADC Vref divider Mask.
*/
#define TWI_ADC_VREF_DIVIDER_MASK                       (0x03 << TWI_ADC_VREF_DIVIDER_POS)

/**
*   @brief  Use Vref/3.
*/
#define TWI_ADC_VREF_DIVIDER_ONE_THIRD                  (0 << TWI_ADC_VREF_DIVIDER_POS)

/**
*   @brief  Use Vref/2.
*/
#define TWI_ADC_VREF_DIVIDER_ONE_HALF                   (1 << TWI_ADC_VREF_DIVIDER_POS)

/**
*   @brief  Use 2*Vref/3.
*/
#define TWI_ADC_VREF_DIVIDER_TWO_THIRD                  (2 << TWI_ADC_VREF_DIVIDER_POS)

/**
*   @brief  Use Vref.
*/
#define TWI_ADC_VREF_DIVIDER_THREE_THIRD                (3 << TWI_ADC_VREF_DIVIDER_POS)

/**
*   @brief      ADC Vin Position.
*/
#define TWI_ADC_VIN_POS                                 0x07

/**
*   @brief      ADC Vin Mask.
*/
#define TWI_ADC_VIN_MASK                                (0x01 << TWI_ADC_VIN_POS)

/**
*   @brief  use VCC as an input voltage.
*/
#define TWI_ADC_VIN_VCC_INPUT                           (0 << TWI_ADC_VIN_POS)

/**
*   @brief  Use an external input voltage.
*/
#define TWI_ADC_VIN_EXTERNAL_INPUT                      (1 << TWI_ADC_VIN_POS)

/**
*   @brief      ADC Vin divider.
*/
#define TWI_ADC_VIN_GAIN_POS                            0x08

/**
*   @brief      ADC Vin divider Mask.
*/
#define TWI_ADC_VIN_GAIN_MASK                           (0xF << TWI_ADC_VIN_GAIN_POS)

/**
*   @brief  Use Vin/6.
*/
#define TWI_ADC_VIN_GAIN_ONE_SIXTH                      (0 << TWI_ADC_VIN_GAIN_POS)

/**
*   @brief  Use Vin/5.
*/
#define TWI_ADC_VIN_GAIN_ONE_FIFTH                      (1 << TWI_ADC_VIN_GAIN_POS)

/**
*   @brief  Use Vin/4.
*/
#define TWI_ADC_VIN_GAIN_ONE_FOURTH                     (2 << TWI_ADC_VIN_GAIN_POS)

/**
*   @brief  Use Vin/3.
*/
#define TWI_ADC_VIN_GAIN_ONE_THIRD                      (3 << TWI_ADC_VIN_GAIN_POS)

/**
*   @brief  Use Vin/2.
*/
#define TWI_ADC_VIN_GAIN_ONE_HALF                       (4 << TWI_ADC_VIN_GAIN_POS)

/**
*   @brief  Use 2*Vin/3.
*/
#define TWI_ADC_VIN_GAIN_TWO_THIRD                      (5 << TWI_ADC_VIN_GAIN_POS)

/**
*   @brief  Use Vin.
*/
#define TWI_ADC_VIN_GAIN_ONE                            (6 << TWI_ADC_VIN_GAIN_POS)

/**
*   @brief  Use 2*Vin.
*/
#define TWI_ADC_VIN_GAIN_TWO                            (7 << TWI_ADC_VIN_GAIN_POS)

/**
*   @brief  Use 4*Vin.
*/
#define TWI_ADC_VIN_GAIN_FOUR                           (8 << TWI_ADC_VIN_GAIN_POS)

/** @} */   /*adc_flags_group*/
/*Used in case the Single Ended mode is used*/
#define ADC_DONOT_USE_DIFF_CHANNEL                      (0xFF)
/*----------------------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/
/*----------------------------------------------------------*/

/**
*   @brief      This is a function that gets the number of available Vin channels.
*   @param[out]  pu8_channel_num    Number of available channels.
*   @retval     ::TWI_SUCCESS, ::TWI_ERROR_INVALID_ARGUMENTS.
*/
twi_s32 twi_adc_get_vin_ch_num(twi_u8 *pu8_channel_num);

/**
*   @brief      This is a function that gets the number of available Vref channels.
*   @param[out]  pu8_channel_num    Number of available channels.
*   @retval     ::TWI_SUCCESS, ::TWI_ERROR_INVALID_ARGUMENTS.
*/
twi_s32 twi_adc_get_vref_ch_num(twi_u8 *pu8_channel_num);

/**
 *	@brief		This is a function that starts an ADC conversion.
 *	@param[in]	u8_vin_ch		The ADC Vin Positive channel number to be used in case of using external Vin & Single Ended Mode.
 *								To get the available channel on that platform use ::twi_adc_get_vin_ch_num.
 *	@param[in]	u8_vin_ch_diff		The ADC Vin Negative channel number to be used in case of using Diffrential Mode.
 *								To get the available channel on that platform use ::twi_adc_get_vin_ch_num.
                                If not used, Just Pass  0xFF ADC_DONOT_USE_DIFF_CHANNEL
 *	@param[in]  u8_vref_ch		The ADC Vref channel number to be used in case of using external Vref.
 *								To get the available Vref channels on that platform use ::twi_adc_get_vref_ch_num.
 *								This is unused in nRF52 as there's no external reference available.
 *	@param[in]	u16_configs		Configuration flags. See @refadc_flags_group.
 *	@param[in]	pu32_result		The result value.
 *	@retval		::TWI_SUCCESS, ::TWI_ERROR_INVALID_CONFIG,
 *				::TWI_ERROR_HW_TIMEOUT, ::TWI_ERROR_ALREADY_RESERVED,
 *				::TWI_ERROR_INVALID_ARGUMENTS.
 */
twi_s32 twi_adc_start(twi_u8 u8_vin_ch,twi_u8 u8_vin_ch_diff, twi_u8 u8_vref_ch, twi_u16 u16_configs, twi_u32 *pu32_result);

/**
*   @brief      This is a function that stops the running ADC conversion.
*   @retval     ::TWI_SUCCESS.
*/
twi_s32 twi_adc_stop(void);

/**
*   @brief      This is a function that gets an ADC channel status.
*   @param[out] pb_running      ADC status. If it is ::TWI_TRUE, the ADC is running, otherwise it is stopped.
*   @retval     ::TWI_SUCCESS, ::TWI_ERROR_INVALID_ARGUMENTS.
*/
twi_s32 twi_adc_status(twi_bool *pb_running);

/** @} */   /*adc_group*/

#endif  /*_ADC_H_*/
