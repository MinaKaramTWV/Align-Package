/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
*   @file       twi_temp_sensor.c
*   @brief      This file contains TWI temperature sensor HAL implementation.
*/

/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/

#include "twi_temp_sensor.h"
#include "platform_defines.h"
#include "nrf_sdm.h"

/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/

/*  Used to correct the negative values as described in PAN 28:
 *  "TEMP: Negative measured values are not represented correctly."
 *  found at Product Anomaly Notification document found at 
 *  https://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF51822/#Downloads
 */
#define MASK_SIGN                                                           	(0x00000200)
#define MASK_SIGN_EXTENSION                                                 	(0xFFFFFC00)

#define MAX_TIMEOUT_LOOPS                                                  		 (TWI_LOOP_TIME_OUT)

#define TEMP_RESOLUTION    	 	                                           		 2   /* Number of shifts (right shifts) that the temperature will be shifted with. */
#define GET_TEMP( TEMP, REAL,FRACTION, NUMBER, NUMBER_OF_SHIFTS )			do{									                                                                    \
                                                                                /* Check first if the number is negative or positive. */			                                    \
                                                                                if ( ( ( NUMBER ) < 0 ) && ( ( NUMBER_OF_SHIFTS ) > 0 ) )						                        \
                                                                                {																				                        \
                                                                                    /* The number is negative. */												                        \
                                                                                    /* Get the Absolute of the number at first, shift and, then return it back as negative. */			\
                                                                                    FRACTION = ( ( ( ~( NUMBER ) + 1 ) & 0b11 ) * 25 );													\
                                                                                    REAL = (twi_s16) ( ~( ( ~( NUMBER ) + 1 ) >> ( NUMBER_OF_SHIFTS ) ) + 1 );							\
                                                                                    TEMP = MUL100(REAL)-FRACTION;																		\
                                                                                }																										\
                                                                                else																									\
                                                                                {																										\
                                                                                    /* The number is positive. */																		\
                                                                                    FRACTION = ( NUMBER & 0b11 ) * 25;																	\
                                                                                    REAL = (twi_s16) ( ( NUMBER ) >> ( NUMBER_OF_SHIFTS ) );											\
                                                                                    TEMP = MUL100(REAL)+FRACTION;																		\
                                                                                }																										\
                                                                            }while(0)

/*---------------------------------------------------------*/
/*- GLOBAL STATIC VARIABLES -------------------------------*/
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
/*- APIs IMPLEMENTATION -----------------------------------*/
/*---------------------------------------------------------*/
/********************************************************************************
*	@function	twi_s32 twi_temp_sensor_init(void)
*
*	@brief		- Function used for initialization of Temperature sensor .
*
*   @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
*
*
*
*******************************************************************************/
twi_s32 twi_temp_sensor_init(void)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;
	return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_temp_sensor_deinit										   *
********************************************************************************
*	@function	twi_s32 twi_temp_sensor_deinit(void)
*
*	@brief		Function used for de-initialization of Temperature sensor.
*
*	@param		none
*
*   @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
*
*
*
*******************************************************************************/
twi_s32 twi_temp_sensor_deinit(void)
{
	twi_s32 s32_retval;
	s32_retval = TWI_SUCCESS;

	return s32_retval;
}
/*
*   @brief      This is a function that gets the temperature in °C. The temperature will be (*pu32_real + *pu32_frac / 100).
*
*   @param[out]  ps16_temp_val  is the temperature measurement*100.
*
*   @retval     ::TWI_SUCCESS, ::TWI_ERROR_INTERNAL_ERROR,
*               ::TWI_ERROR_HW_TIMEOUT, ::TWI_ERROR_INVALID_ARGUMENTS.
*/
twi_s32 twi_temp_sensor_read(twi_s16 *ps16_temp_val)
{
    twi_s32 s32_retval;
    twi_s32 s32_temp;
    twi_s8 s8_temp_real;
    twi_u8 u8_temp_frac;
    
    s32_retval = TWI_SUCCESS;
    s32_temp = 0;
    s8_temp_real = 0;
    u8_temp_frac = 0;
    
    /*Check parameters are a valid parameters.*/
    if(NULL != ps16_temp_val)
    {
        /*The parameters are valid.*/
        twi_u8 u8_softdevice_enabled;
 
        /*Check if the SD is enabled or not.*/
        sd_softdevice_is_enabled(&u8_softdevice_enabled);
        
        if(TWI_TRUE == u8_softdevice_enabled)
        {
            /*soft device is initialized.*/

            twi_s32 s32_error;
            
            s32_error = sd_temp_get(&s32_temp);
            if(0 != s32_error)
            {
                s32_retval = TWI_ERROR_INTERNAL_ERROR;
            }
        }
        else
        {
            /*soft device is not initialized.*/
            twi_u32 u32_timeout;

            /*  load the temperature offset as described in PAN 31:
             *  "TEMP: Temperature offset value has to be manually loaded to the TEMP module."
             *  found at Product Anomaly Notification document found at 
             *  https://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF51822/#Downloads
             */
            *(uint32_t *)0x4000C504 = 0x00000000;
            NRF_TEMP->TASKS_STOP = 1;
            NRF_TEMP->TASKS_START = 1;
            
            u32_timeout = MAX_TIMEOUT_LOOPS;
            while((1 != NRF_TEMP->EVENTS_DATARDY) && (0 != u32_timeout))
            {
                u32_timeout--;
            }
            if(0 != u32_timeout)
            {
                /*  Correct the negative values as described in PAN 28:
                 *  "TEMP: Negative measured values are not represented correctly."
                 *  found at Product Anomaly Notification document found at 
                 *  https://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF51822/#Downloads
                 */
                s32_temp = ((NRF_TEMP->TEMP & MASK_SIGN) != 0) ? (NRF_TEMP->TEMP | MASK_SIGN_EXTENSION) : (NRF_TEMP->TEMP);
                NRF_TEMP->EVENTS_DATARDY = 0;
                /*  Stop the TEMP module as described in PAN 30:
                 *  "TEMP: TEMP module analog front end does not power down when DATARDY event occurs."
                 *  found at Product Anomaly Notification document found at 
                 *  https://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF51822/#Downloads
                 */
                NRF_TEMP->TASKS_STOP = 1;
            }
            else
            {
                s32_retval = TWI_ERROR_HW_TIMEOUT;
            }
        }
        if(TWI_SUCCESS == s32_retval)
        {
        	GET_TEMP(*ps16_temp_val,s8_temp_real,u8_temp_frac, s32_temp, TEMP_RESOLUTION);
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
