/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*  @file	twi_nvds.h
*  @brief	This module contains TWI security flash module interfaces
*/

#ifndef _TWI_NVDS_H_
#define _TWI_NVDS_H_

/** @defgroup TWI_NVDS_group TWI Security Flash interface Module
 * This module is responsible for saving the state of different security parameters in the flash to be retrieved once the system re-initializes.
 * @{
 */
/*-***********************************************************/
/*- INCLUDES ------------------------------------------------*/
/*-***********************************************************/

#include "twi_types.h"
#include "twi_retval.h"
#include "twi_nvds_tags.h"
#define TWI_NVDS_NO_LOAD_DATA_ERROR			(TWI_NVDS_ERROR_BASE - 1)
#define TWI_NVDS_NO_ERASE_DATA_ERROR		(TWI_NVDS_ERROR_BASE - 2)

/*-*********************************************************/
/*- ENUMS -------------------------------------------------*/
/*-*********************************************************/

/**
 *	@enum		tenu_save_status
 *	@brief		enum used to define the saving status.
 */
typedef enum
{
	TWI_NVDS_INVALID_STATUS = 0,	/**< @brief	Invalid saving status. */
	TWI_NVDS_NOT_SAVED,			/**< @brief	saving operation failed status. */
	TWI_NVDS_SAVED					/**< @brief	saving operation success status. */
}tenu_save_status;

/*-*********************************************************/
/*- STRUCTS AND UNIONS ------------------------------------*/
/*-*********************************************************/
/** @brief Saving CB function type */
typedef void (*tpf_twi_nvds_cb)(tenu_save_status enu_save_status, tenu_tlv_nvds_tag enu_module_id, void * pv_arg);

/*-*********************************************************/
/*- APIs DECLARATIONS -------------------------------------*/
/*-*********************************************************/

/**
 *	@brief		This function initializes the security flash module.
 *	@return     ::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
twi_s32 twi_nvds_init(void);

/**
 *	@brief		This function saves security data into flash memory.
 *	@param[in]	enu_module_id			The module id that will be saved in the flash memory.
 *	@param[in]	pu8_buf					Pointer to the data that will be saved in the flash memory. The buffer shouldn't be changed till the cb is called.
 *	@param[in]	u16_len					Size of the data buffer.
 *	@param[in]	pf_save_cb				Pointer to CB function to be called when the save operation is done.
 *	@return     ::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
twi_s32 twi_nvds_save(tenu_tlv_nvds_tag enu_module_id, twi_u8* pu8_buf, twi_u16 u16_len, tpf_twi_nvds_cb pf_save_cb, void * pv_arg);

/**
 *  @brief          Function used to load setting from the flash memory.
 *  @param[in]      enu_module_id           The module id that will be loaded from the flash memory.
 *  @param[in]      pu8_buf                 Pointer to the buffer to load from the flash memory into it.
 *  @param[in/out]  pu16_len                This argument must contain the input buffer size,
 *                                          if this size is less than the tag's length, this function will return error
 *                                          Other wise will return the loaded length.
 *  @return         ::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h twi_settings.h.
 */
twi_s32 twi_nvds_load(tenu_tlv_nvds_tag enu_module_id, twi_u8* pu8_buf, twi_u16* pu16_len);

/**
 *  @brief      Function used to delete setting from the flash memory.
 *  @param[in]  enu_module_id           The module id that will be loaded from the flash memory.
 *  @return     ::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h twi_settings.h.
 */
twi_s32 twi_nvds_del(tenu_tlv_nvds_tag enu_module_id);

/*
 *  @function   twi_nvds_del_all(void)
 *  @brief      Function used to delete all setting from the flash memory.
 *  @return     ::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h twi_settings.h.
 */
twi_s32 twi_nvds_del_all(void);

/**
 *	@brief		Dispatch Function of security flash module.
 *	@return     None.
 */
void twi_nvds_dispatch(void);

/** @}*/
#endif		/* _TWI_NVDS_H_ */
