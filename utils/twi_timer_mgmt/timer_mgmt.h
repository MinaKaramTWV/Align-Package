/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       timer_mgmt.h
*   @brief      This file contains TWI Timers management unit APIs and related declarations.
*/

#ifndef _TIMER_MGMT_H_
#define _TIMER_MGMT_H_
/**
*   @defgroup timer_mgmt_group TWI Timers management Module
*   This file contains TWI Timers management unit APIs and related declarations.
*   @{
*/

/*----------------------------------------------------------*/
/*- INCLUDES -----------------------------------------------*/
/*----------------------------------------------------------*/

#include "twi_types.h"
#include "twi_retval.h"

/*----------------------------------------------------------*/
/*- CONSTANTS ----------------------------------------------*/
/*----------------------------------------------------------*/



/*----------------------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*----------------------------------------------------------*/

typedef void(*tpf_twi_timer_mgmt_cb)(void *pv_user_data);

/*----------------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*----------------------------------------------------------*/


/**
 *	@enum		tenu_mgmt_timer_mode
 *	@brief		enumeration for the timer mode
 */
typedef enum
{
	TWI_TIMER_TYPE_ONE_SHOT = 0,	/**< @brief  The timer will run for a one shot with the set time. */
	TWI_TIMER_TYPE_PERIODIC			/**< @brief  The timer will run periodically with the same set time. */
}tenu_mgmt_timer_mode;

/**
*   @struct     _tstr_timer_mgmt_timer
*	@brief		Structure represents the data needed by timer management unit in order to start a timer.
*/
typedef struct _tstr_timer_mgmt_timer
{
    twi_bool b_is_active;                   /**< @brief Flag to indicate if the timer is active or not*/
    twi_u8 u8_mode;                         /**< @brief The timer mode: ::TWI_TIMER_TYPE_PERIODIC, ::TWI_TIMER_TYPE_ONE_SHOT */
    twi_s8* ps8_name;						/**< @brief Timer name*/
    void *pv_user_data;                     /**< @brief Arbitrary user void data */
    twi_u32 u32_reload_ms;					/**< @brief Reload value of time-out in ms */
	twi_u64 u64_reload_ticks;				/**< @brief Reload value of time-out in ticks */
	tpf_twi_timer_mgmt_cb pf_timer_mgmt_cb;	/**< @brief Pointer to timer callback function. It's very important to ensure that
														the implementation of this callback function will do minimum work as it's called
														from interrupt context */
	struct _tstr_timer_mgmt_timer *prev;	/**< @brief Pointer to previous timer node*/
	struct _tstr_timer_mgmt_timer *next;	/**< @brief Pointer to next timer node*/

    twi_u64 u64_threshold_ticks;            /**< @brief Reload value of time-out in ticks */
} tstr_timer_mgmt_timer;


/*----------------------------------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/
/*----------------------------------------------------------*/

/**
*   @brief      This function initializes the Timer module.
*   @return     ::TWI_SUCCESS, ::TWI_ERROR_ALREADY_INITIALIZED, ::TWI_ERROR_INVALID_ARGUMENTS.
*	@warning	This function should be called before using any function in the module.
*/
twi_s32 timer_mgmt_init(void);

/**
*   @brief      This function de-initializes the module.
*   @return     ::TWI_SUCCESS, ::TWI_ERROR_NOT_INITIALIZED.
*/
twi_s32 timer_mgmt_deinit(void);

/**
*   @brief      This function starts a Millisecond timer.
*	@param[in]	pstr_timer		Pointer to timer handle allocated by the caller. Can't be freed till timer removal
*	@param[in]	ps8_name		Pointer to timer name. This buffer can't be freed as long as the timer is active
*   @param[in]  u8_mode         The timer mode: ::TWI_TIMER_TYPE_PERIODIC, ::TWI_TIMER_TYPE_ONE_SHOT
*   @param[in]  u32_msec        Period to wait in milliseconds.
*   @param[in]  pf_timer_cb     A pointer to a callback function that will be called after the required delay.
*   @param[in]  pv_user_data    User data to be passed to the start_timer_ms::pf_timer_cb.
*   @return     ::TWI_SUCCESS, ::TWI_ERROR_NOT_INITIALIZED.
*/
twi_s32 start_timer(tstr_timer_mgmt_timer *pstr_timer, twi_s8 *ps8_name, tenu_mgmt_timer_mode enu_mode, twi_u32 u32_msec, tpf_twi_timer_mgmt_cb pf_timer_cb, void *pv_user_data);

/**
*   @brief      This function stops the running timer.
*	@param[in]	pstr_timer		Pointer to timer handle allocated by the caller. Can't be freed till timer removal
*   @return     ::TWI_SUCCESS, ::TWI_ERROR_NOT_INITIALIZED.
*/
twi_s32 stop_timer(tstr_timer_mgmt_timer *pstr_timer);

/**
*   @brief      This function gets the total number of microseconds from the last time the timer gets started.
*   @param[in]  pu32_msec       The number of the passed milliseconds from the last started timer.
*   @return     ::TWI_SUCCESS, ::TWI_ERROR_NOT_INITIALIZED, ::TWI_ERROR_INVALID_ARGUMENTS.
*/
twi_s32 get_time(const tstr_timer_mgmt_timer *pstr_timer, twi_u32 *pu32_msec);
/*
*   @brief      This function check if the timer is active or not.
*   @param[in]  pstr_timer		Pointer to timer handle allocated by the caller.
*   @param[out] pb_active       TWI_TRUE if the timer is active.
*   @return     ::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
*/
twi_s32 timer_is_active(const tstr_timer_mgmt_timer *pstr_timer, twi_bool *pb_active);

/** @} */   /*timer_mgmt_group*/

#endif  /*_TIMER_MGMT_H_*/
