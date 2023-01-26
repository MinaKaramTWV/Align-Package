/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_power_mgmt.h
*   @brief      This file contains TWI Power management APIs.
*/

#ifndef _TWI_POWER_MGMT_H_
#define _TWI_POWER_MGMT_H_
/**
*   @defgroup TWI_power_mgmt_group TWI Power Management HAL
*   This is the definition of TWI HAL for Power Management.
*   @{
*/

/*----------------------------------------------------------*/
/*- INCLUDES -----------------------------------------------*/
/*----------------------------------------------------------*/

#include "twi_common.h"

#define POWER_ON_RESET_REASON           (0x01ul)
#define BROWN_DOWN_RESET_REASON			(0x02ul)
#define EXT_PIN_RESET_REASON       		(0x04ul)
#define WATCHDOG_RESET_REASON 			(0x08ul)
#define LOCK_UP_RESET_REASON			(0x10ul)
#define REBOOT_RESET_REASON				(0x20ul)
#define CPU_SYSYTEM_RESET_REASON		(0x40ul)
#define WAKE_UP_RESET_REASON			(0x80ul)
#define CPU_SW_RESET_REASON				(0x100ul)

#define REST_CAUSE_BIT_POS				(31)

#define TWI_POWER_MGMT_DS_KEEP_RAM_POS          0x01                                    /**<    @brief  Keep the RAM content in Deep Sleep flag position. */
#define TWI_POWER_MGMT_DS_KEEP_RAM_MASK         (1 << TWI_POWER_MGMT_DS_KEEP_RAM_POS)   /**<    @brief  Keep the RAM content in Deep Sleep flag mask. */

/**
*   @defgroup power_mgmt_ds_flags_group TWI Power Management Deep Sleep mode Flags
*   This is the Power Management Deep Sleep mode Flags.
*   @{
*/
#define TWI_POWER_MGMT_DS_KEEP_RAM_ON           (1 << TWI_POWER_MGMT_DS_KEEP_RAM_POS)   /**<    @brief  Keep the RAM content in Deep Sleep. */
#define TWI_POWER_MGMT_DS_KEEP_RAM_OFF          (0 << TWI_POWER_MGMT_DS_KEEP_RAM_POS)   /**<    @brief  Do not Keep the RAM content in Deep Sleep. */

/** @} */   /*power_mgmt_ds_flags_group*/

/*-***********************************************************/
/*- ENUMERATIONS --------------------------------------------*/
/*-***********************************************************/

/**
 *	@enum		_tenu_power_mgmt_wakeup_reason
 *	@brief		enumeration that indicates the reason of the wakeup
 */
typedef enum
{
	WAKEUP_FROM_NORMAL_START = 0,
	WAKEUP_FROM_DEEP_SLEEP,
	WAKEUP_FROM_WATCHDOG_TIMER,
	WAKEUP_FROM_SW_RESET,
	WAKEUP_FROM_CPU_SYSTEM_RESET,
	WAKEUP_FROM_BROWN_DOWN_RESET,
	WAKEUP_FROM_REBOOT,
	WAKEUP_FROM_LOCK_UP_RESET,
	WAKEUP_FROM_EXT_PIN_RESET,	/* Reset PBTN pressed */
	WAKEUP_FROM_NFC,			/* Wake up from NRF Interrupt. */
#ifdef SUPPORT_OTA_SERVICE_MANAGER
    WAKEUP_FROM_OTA_UPDATE,
#endif
	WAKEUP_FROM_UNHANDLED_REASON,
}tenu_power_mgmt_wakeup_reason;

/*----------------------------------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/
/*----------------------------------------------------------*/
/**
*   @brief      This function init the power mgmt uint
*   @return     ::TWI_SUCCESS, otherwise, refer to @ref twi_retval.h.
*/
twi_s32 twi_power_mgmt_init(void);
/**
*   @brief      This function puts the system into the sleep mode.
*   @return     ::TWI_SUCCESS, otherwise, refer to @ref twi_retval.h.
*/
twi_s32 twi_power_mgmt_sleep(void);

/**
*   @brief      This function puts the system into the deep sleep mode.
*   @details    In that mode the system will be at the minimum power consumption.
*   @param[in]  u8_flags    The flags of the deep sleep. Please check @ref power_mgmt_ds_flags_group.
*   @return     ::TWI_SUCCESS, otherwise, refer to @ref twi_retval.h.
*/
twi_s32 twi_power_mgmt_deep_sleep(twi_u8 u8_flags);


/**
*   @brief      This function gets the reason of reset.
*   @param[out] penu_wakeup_reason    The reset reason.
*   @return     ::TWI_SUCCESS, otherwise, refer to @ref twi_retval.h.
*/
twi_s32 twi_power_mgmt_wakeup_reason(tenu_power_mgmt_wakeup_reason* penu_wakeup_reason);

/** @} */   /*power_mgmt_group*/

#endif  /*_TWI_POWER_MGMT_H_*/
