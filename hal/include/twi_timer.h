/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_timer.h
*   @brief      This file implements TWI Timer HAL.
*/

#ifndef _TWI_TIMER_H_
#define _TWI_TIMER_H_
/**
*   @defgroup timer_group TWI Timer HAL
*   This is the definition of TWI HAL for Timer.
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
*   @defgroup twi_rtc_timer_retval_group RTC Timer return values
*   @{
*/
#define TWI_RTC_TIMER_ALREADY_FIRED						(TWI_ERR_RTC_TIMER_BASE - 1)
/** @} */	/* twi_rtc_timer_retval_group */

/** @brief  The timer will run periodically with the same set time.
*/
#define TWI_TIMER_TYPE_POS          0

/** @brief  The timer will run periodically with the same set time.
*/
#define TWI_TIMER_TYPE_MASK         (1 << TWI_TIMER_TYPE_POS)



/**
 *	@enum		tenu_timer_mode
 *	@brief		enumeration for the timer mode
 */
typedef enum
{
	TIMER_TYPE_ONE_SHOT = 0,	/** @brief  The timer will run for a one shot with the set time. */
	TIMER_TYPE_PERIODIC			/** @brief  The timer will run periodically with the same set time. */
}tenu_timer_mode;

/**
 *	@enum		tenu_timer_chs_nums
 *	@brief		enumeration for the timer Channel numbers
 */
typedef enum
{
	TWI_TIMER_CH0 = 0,		/**< @brief Timer Channel 0. */
	TWI_TIMER_CH1,			/**< @brief Timer Channel 1. */
}tenu_timer_chs_nums;

/*----------------------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*----------------------------------------------------------*/

typedef void(*tpf_twi_timer_cb)(void *pv_user_data, volatile twi_u64 u64_fired_cntr_val);

/*----------------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*----------------------------------------------------------*/


/*----------------------------------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/
/*----------------------------------------------------------*/

/**
 *	@brief      This function initialize the Timer module.
 *	@param[in]  enu_ch_num	Timer Channel number.
 *	@return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_timer_init(tenu_timer_chs_nums enu_ch_num);

/**
 *	@brief      This function de-initialize the Timer module.
 *	@param[in]  enu_ch_num	Timer Channel number.
 *	@return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_timer_deinit(tenu_timer_chs_nums enu_ch_num);

/**
 *	@brief      This function starts timer in milliseconds.
 *	@param[in]  enu_ch_num	Timer Channel number.
 *	@param[in]  enu_mode        The timer mode: ::TWI_TIMER_TYPE_PERIODIC, ::TWI_TIMER_TYPE_ONE_SHOT
 *	@param[in]  u64_thr_ticks      threshold to timer fire at in timer counter ticks.
 *	@param[in]  u32_period_ticks        Period to wait in timer counter ticks.
 *	@param[in]  pf_timer_cb     A pointer to a callback function that will be called after the required delay.
 *	@param[in]  pv_user_data    User data to be passed to the start_timer_ms::pf_timer_cb.
 *	@return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_timer_start_timer(tenu_timer_chs_nums enu_ch_num, tenu_timer_mode enu_mode, twi_u64 u64_thr_ticks, twi_u32 u32_period_ticks, tpf_twi_timer_cb pf_timer_cb, void *pv_user_data);
/**
 *	@brief      This function stops the running timer.
 *	@param[in]  enu_ch_num	Timer Channel number.
 *	@return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_timer_stop_timer(tenu_timer_chs_nums enu_ch_num);

/**
*   @brief      This function gets the total number of ticks from the initialization of the module.
*   @param[in]  enu_ch_num        The timer channel
*   @param[in]  pu64_ticks       The number of the passed ticks from initialization.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_timer_get_time_since_init(tenu_timer_chs_nums enu_ch_num,twi_u64 *pu64_ticks);

/**
*   @brief      This function checks if the timer is running or not.
*	@param[in]  enu_ch_num	Timer Channel number.
*   @param[in]  pb_running      It is ::TWI_TRUE if timer is running and ::TW_FALSE if timer is not running.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_timer_is_running(tenu_timer_chs_nums enu_ch_num, twi_bool *pb_running);

/**
*   @brief      This function converts from time in 100 Micro Seconds to counter ticks.
*	@param[in]  u32_100usec	time in 100 Micro Seconds to be converted.
*   @return     converted counter ticks
*/
twi_u64 twi_timer_convert_to_ticks(twi_u64 u64_100usec);

/**
*   @brief      This function converts from counter ticks to time in milli Seconds.
*	@param[in]  u32_ticks	time in counter ticks be converted.
*   @return     converted time in milli Seconds
*/
twi_u32 twi_timer_convert_to_time(twi_u64 u64_ticks);

/** @} */   /*timer_group*/

#endif  /*_TWI_TIMER_H_*/
