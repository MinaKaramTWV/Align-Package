/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
 *	@file		twi_adc.c
 *	@brief		This file contains implementation for TWI ADC HAL.
 */

/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/

#include "twi_adc.h"
#include "platform_defines.h"
#include "platform_pins.h"
#include "twi_gpio.h"
#include "nrf.h"

/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/

#define MAX_TIMEOUT_LOOPS                       (TWI_LOOP_TIME_OUT)

#define ADC_CONFIG_RESET_VALUE                  0x00020000UL

/*---------------------------------------------------------*/
/*- GLOBAL STATIC VARIABLES -------------------------------*/
/*---------------------------------------------------------*/
static twi_u8 gu8_used_vin_pstv_channel; /*Used to save the selected Vin channel to deselect it when stopped. */
static twi_u8 gu8_used_vin_ngtv_channel; /*Used to save the selected Vin channel to deselect it when stopped. */
static twi_bool gb_vin_pstv_selected = TWI_FALSE; /*Used to know if it use an external Vin and it selected it.*/
static twi_bool gb_vin_ngtv_selected = TWI_FALSE; /*Used to know if it use an external Vin and it selected it.*/
/*---------------------------------------------------------*/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
/*- APIs IMPLEMENTATION -----------------------------------*/
/*---------------------------------------------------------*/

/*
 *	@brief		This is a function that gets the number of available Vin channels.
 *	@param[out]	pu8_channel_num    Number of available channels.
 *	@retval		::TWI_SUCCESS, ::TWI_ERROR_INVALID_ARGUMENTS.
 */
twi_s32 twi_adc_get_vin_ch_num(twi_u8 *pu8_channel_num)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;

    if (NULL != pu8_channel_num)
    {
        *pu8_channel_num = PLATFORM_ADC_VIN_CH_NUM;
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }

    return s32_retval;
}

/*
 *	@brief		This is a function that gets the number of available Vref channels.
 *	@param[out]	pu8_channel_num    Number of available channels.
 *	@retval		::TWI_SUCCESS, ::TWI_ERROR_INVALID_ARGUMENTS.
 */
twi_s32 twi_adc_get_vref_ch_num(twi_u8 *pu8_channel_num)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;

    if (NULL != pu8_channel_num)
    {
        *pu8_channel_num = PLATFORM_ADC_VREF_CH_NUM;
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }

    return s32_retval;
}

/*
 *	@brief		This is a function that starts an ADC conversion.
 *	@param[in]	u8_vin_ch_pstv		The ADC Vin Positive channel number to be used in case of using external Vin & Single Ended Mode.
 *								To get the available channel on that platform use ::twi_adc_get_vin_ch_num.
 *	@param[in]	u8_vin_ch_ngtv		The ADC Vin Negative channel number to be used in case of using Diffrential Mode.
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
twi_s32 twi_adc_start(twi_u8 u8_vin_ch_pstv,twi_u8 u8_vin_ch_ngtv, twi_u8 u8_vref_ch, twi_u16 u16_configs, twi_u32 *pu32_result)
{
    twi_s32 s32_retval = TWI_SUCCESS;

#ifndef DISABLE_ADC_BUG_ERRATA_WORKARROUND
        *(volatile twi_u32 *)((twi_u32)NRF_SAADC + 0xFFC) = 1;
#endif

    /* Check arguments */
    if ((u8_vin_ch_pstv < PLATFORM_ADC_VIN_CH_NUM) && (NULL != pu32_result)
    &&((u8_vin_ch_ngtv == ADC_DONOT_USE_DIFF_CHANNEL)||((u8_vin_ch_ngtv  != u8_vin_ch_pstv)&&(u8_vin_ch_ngtv < PLATFORM_ADC_VIN_CH_NUM))))
    {
        gu8_used_vin_pstv_channel = u8_vin_ch_pstv;
        /* See if ADC is busy */
        if ((SAADC_STATUS_STATUS_Ready << SAADC_STATUS_STATUS_Pos) == NRF_SAADC->STATUS)
        {
            if (TWI_ADC_VIN_EXTERNAL_INPUT == (u16_configs & TWI_ADC_VIN_MASK))
            {
                s32_retval = twi_gpio_select(PLATFORM_ADC_GET_VIN_PORT(gu8_used_vin_pstv_channel), PLATFORM_ADC_GET_VIN_PIN(gu8_used_vin_pstv_channel));
                if (TWI_SUCCESS == s32_retval)
                {
                    gb_vin_pstv_selected = TWI_TRUE;
                    NRF_SAADC->CH[u8_vin_ch_pstv].PSELP = SAADC_CH_PSELP_PSELP_AnalogInput0 + (unsigned long) gu8_used_vin_pstv_channel;
                    /*Check if it is working in Diffrential mode*/
                    if(u8_vin_ch_ngtv != ADC_DONOT_USE_DIFF_CHANNEL)
                    {
                        gu8_used_vin_ngtv_channel = u8_vin_ch_ngtv;
                        s32_retval = twi_gpio_select(PLATFORM_ADC_GET_VIN_PORT(gu8_used_vin_ngtv_channel), PLATFORM_ADC_GET_VIN_PIN(gu8_used_vin_ngtv_channel));
                        if (TWI_SUCCESS == s32_retval)
                        {
                            gb_vin_ngtv_selected = TWI_TRUE;
                            NRF_SAADC->CH[u8_vin_ch_ngtv].PSELN = SAADC_CH_PSELN_PSELN_AnalogInput0 + (unsigned long) gu8_used_vin_ngtv_channel;
                        }
                        else
                        {
                            gb_vin_ngtv_selected = TWI_FALSE;
                            /* Couldn't select gpio */
                            s32_retval = TWI_ERROR_ALREADY_RESERVED;
                        }
                    }
                }
                else
                {
                    gb_vin_pstv_selected = TWI_FALSE;
                    /* Couldn't select gpio */
                    s32_retval = TWI_ERROR_ALREADY_RESERVED;
                }
            }
            else
            {
                gb_vin_pstv_selected = TWI_FALSE;
                gb_vin_ngtv_selected = TWI_FALSE;
                /* Using internal input (VDD) */
                NRF_SAADC->CH[u8_vin_ch_pstv].PSELP = SAADC_CH_PSELP_PSELP_VDD;
            }
            if (s32_retval == TWI_SUCCESS)
            {
                /* Reset all settings */
                NRF_SAADC->CH[u8_vin_ch_pstv].CONFIG = ADC_CONFIG_RESET_VALUE;
                /*CFG for diffrential mode*/
                if(u8_vin_ch_ngtv != ADC_DONOT_USE_DIFF_CHANNEL)
                {
                    NRF_SAADC->CH[u8_vin_ch_pstv].CONFIG |= SAADC_CH_CONFIG_MODE_Diff << SAADC_CH_CONFIG_MODE_Pos;
                }
                /* Configure Gain */
                switch (u16_configs & TWI_ADC_VIN_GAIN_MASK)
                {
                    case TWI_ADC_VIN_GAIN_ONE_SIXTH:
                        NRF_SAADC->CH[u8_vin_ch_pstv].CONFIG |= SAADC_CH_CONFIG_GAIN_Gain1_6 << SAADC_CH_CONFIG_GAIN_Pos;
                        break;
                    case TWI_ADC_VIN_GAIN_ONE_FIFTH:
                        NRF_SAADC->CH[u8_vin_ch_pstv].CONFIG |= SAADC_CH_CONFIG_GAIN_Gain1_5 << SAADC_CH_CONFIG_GAIN_Pos;
                        break;
                    case TWI_ADC_VIN_GAIN_ONE_FOURTH:
                        NRF_SAADC->CH[u8_vin_ch_pstv].CONFIG |= SAADC_CH_CONFIG_GAIN_Gain1_4 << SAADC_CH_CONFIG_GAIN_Pos;
                        break;
                    case TWI_ADC_VIN_GAIN_ONE_THIRD:
                        NRF_SAADC->CH[u8_vin_ch_pstv].CONFIG |= SAADC_CH_CONFIG_GAIN_Gain1_3 << SAADC_CH_CONFIG_GAIN_Pos;
                        break;
                    case TWI_ADC_VIN_GAIN_ONE_HALF:
                        NRF_SAADC->CH[u8_vin_ch_pstv].CONFIG |= SAADC_CH_CONFIG_GAIN_Gain1_2 << SAADC_CH_CONFIG_GAIN_Pos;
                        break;
                    case TWI_ADC_VIN_GAIN_ONE:
                        NRF_SAADC->CH[u8_vin_ch_pstv].CONFIG |= SAADC_CH_CONFIG_GAIN_Gain1 << SAADC_CH_CONFIG_GAIN_Pos;
                        break;
                    case TWI_ADC_VIN_GAIN_TWO:
                        NRF_SAADC->CH[u8_vin_ch_pstv].CONFIG |= SAADC_CH_CONFIG_GAIN_Gain2 << SAADC_CH_CONFIG_GAIN_Pos;
                        break;
                    case TWI_ADC_VIN_GAIN_FOUR:
                        NRF_SAADC->CH[u8_vin_ch_pstv].CONFIG |= SAADC_CH_CONFIG_GAIN_Gain4 << SAADC_CH_CONFIG_GAIN_Pos;
                        break;
                    default:
                        s32_retval = TWI_ERROR_INVALID_CONFIG;
                        break;
                }
            }
            if (s32_retval == TWI_SUCCESS)
            {
                /* Vref divider not supported */
                if (TWI_ADC_VREF_DIVIDER_THREE_THIRD != (u16_configs & TWI_ADC_VREF_DIVIDER_MASK))
                {
                    s32_retval = TWI_ERROR_NOT_SUPPORTED_FEATURE;
                }
                else
                {
                    /* Configure Vref */
                    switch (u16_configs & TWI_ADC_VREF_MASK)
                    {
                        case TWI_ADC_VREF_INTERNAL_REF:
                            NRF_SAADC->CH[u8_vin_ch_pstv].CONFIG |= SAADC_CH_CONFIG_REFSEL_Internal << SAADC_CH_CONFIG_REFSEL_Pos;
                            break;
                        case TWI_ADC_VREF_VDD_REF:
                            NRF_SAADC->CH[u8_vin_ch_pstv].CONFIG |= SAADC_CH_CONFIG_REFSEL_VDD1_4 << SAADC_CH_CONFIG_REFSEL_Pos;
                            break;
                        default:
                            s32_retval = TWI_ERROR_INVALID_CONFIG;
                            break;
                    }
                }
            }
            if (s32_retval == TWI_SUCCESS)
            {
                /* Configure resolution */
                switch (u16_configs & TWI_ADC_RES_MASK)
                {
                    case TWI_ADC_RES_8_BITS:
                        NRF_SAADC->RESOLUTION = SAADC_RESOLUTION_VAL_8bit << SAADC_RESOLUTION_VAL_Pos;
                        break;
                    case TWI_ADC_RES_10_BITS:
                        NRF_SAADC->RESOLUTION = SAADC_RESOLUTION_VAL_10bit << SAADC_RESOLUTION_VAL_Pos;
                        break;
                    case TWI_ADC_RES_12_BITS:
                        NRF_SAADC->RESOLUTION = SAADC_RESOLUTION_VAL_12bit << SAADC_RESOLUTION_VAL_Pos;
                        break;
                    case TWI_ADC_RES_14_BITS:
                        NRF_SAADC->RESOLUTION = SAADC_RESOLUTION_VAL_14bit << SAADC_RESOLUTION_VAL_Pos;
                        break;
                    default:
                        s32_retval = TWI_ERROR_INVALID_CONFIG;
                        break;
                }
            }
            if (s32_retval == TWI_SUCCESS)
            {
                volatile twi_u32 u32_timeout;
                /* Set result address and count */
                NRF_SAADC->RESULT.PTR = (twi_u32) (pu32_result);
                NRF_SAADC->RESULT.MAXCNT = 1;
                /* Begin sampling */
                NRF_SAADC->ENABLE = SAADC_ENABLE_ENABLE_Enabled << SAADC_ENABLE_ENABLE_Pos;
                NRF_SAADC->TASKS_START = 1;

                u32_timeout = MAX_TIMEOUT_LOOPS;

                while ((NRF_SAADC->EVENTS_STARTED != 1) && (u32_timeout > 0))
                {
                    u32_timeout--;
                }

                if (u32_timeout > 0)
                {
                    NRF_SAADC->TASKS_SAMPLE = 1;

                    while ((NRF_SAADC->EVENTS_END != 1) && (u32_timeout > 0))
                    {
                        u32_timeout--;
                    }
                    if (u32_timeout == 0)
                    {
                        /* Conversion timed-out */
                        s32_retval = TWI_ERROR_HW_TIMEOUT;
                    }
                }
                else
                {
                    s32_retval = TWI_ERROR_HW_TIMEOUT;
                }
                /* Undo all changes */
                NRF_SAADC->TASKS_STOP = 1;
                NRF_SAADC->EVENTS_END = 0;
                NRF_SAADC->EVENTS_STARTED = 0;
                NRF_SAADC->ENABLE = SAADC_ENABLE_ENABLE_Disabled << SAADC_ENABLE_ENABLE_Pos;
#ifndef DISABLE_ADC_BUG_ERRATA_WORKARROUND
                *(volatile twi_u32 *)((twi_u32)NRF_SAADC + 0xFFC) = 0;
#endif
            }
        }
        else
        {
            s32_retval = TWI_ERROR_ALREADY_RESERVED;
        }
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }
    if (TWI_TRUE == gb_vin_pstv_selected)
    {
        (void) twi_gpio_deselect(PLATFORM_ADC_GET_VIN_PORT(gu8_used_vin_pstv_channel), PLATFORM_ADC_GET_VIN_PIN(gu8_used_vin_pstv_channel));
        gb_vin_pstv_selected = TWI_FALSE;
    }
    if (TWI_TRUE == gb_vin_ngtv_selected)
    {
        (void) twi_gpio_deselect(PLATFORM_ADC_GET_VIN_PORT(gu8_used_vin_ngtv_channel), PLATFORM_ADC_GET_VIN_PIN(gu8_used_vin_ngtv_channel));
        gb_vin_ngtv_selected = TWI_FALSE;
    }
    return s32_retval;
}

/*
 *	@brief		This is a function that stops the running ADC conversion.
 *	@retval		::TWI_SUCCESS.
 */
twi_s32 twi_adc_stop(void)
{
    twi_s32 s32_retval = TWI_SUCCESS;

    NRF_SAADC->TASKS_STOP = 1;

    NRF_SAADC->ENABLE = SAADC_ENABLE_ENABLE_Disabled << SAADC_ENABLE_ENABLE_Pos;

    if (TWI_TRUE == gb_vin_pstv_selected)
    {
        (void) twi_gpio_deselect(PLATFORM_ADC_GET_VIN_PORT(gu8_used_vin_pstv_channel), PLATFORM_ADC_GET_VIN_PIN(gu8_used_vin_pstv_channel));
        gb_vin_pstv_selected = TWI_FALSE;
    }
    if (TWI_TRUE == gb_vin_ngtv_selected)
    {
        (void) twi_gpio_deselect(PLATFORM_ADC_GET_VIN_PORT(gu8_used_vin_ngtv_channel), PLATFORM_ADC_GET_VIN_PIN(gu8_used_vin_ngtv_channel));
        gb_vin_ngtv_selected = TWI_FALSE;
    }

    return s32_retval;
}

/*
 *	@brief		This is a function that gets an ADC channel status.
 *	@param[out]	pb_running	ADC status. If it is ::TWI_TRUE, the ADC is running, otherwise it is stopped.
 *	@retval		::TWI_SUCCESS,::TWI_ERROR_INVALID_ARGUMENTS.
 */
twi_s32 twi_adc_status(twi_bool *pb_running)
{
    twi_s32 s32_retval = TWI_SUCCESS;

    if (NULL != pb_running)
    {
        *pb_running = NRF_SAADC->STATUS;
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }

    return s32_retval;
}
