/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file		twi_internal_flash.h
 *	@brief		This module contains the flash driver declarations.
 *				In this module, the used technique is to queue
 *				  	the flash events in a queue via the functions
 *       		  	"flash_opr_put" and "flash_opr_get" which push and
 * 			  	  	get the events in/to a queue. The physical operation
 *       		  	is done after receiving a notification via the call back
 *				  	function "flash_cb_handler".
 *				  	Finite state machine is used here also to control
 *				  	the flash states and transitions as the flash module
 *				  	takes some time to erase or write(about 50 ms to finish!).
 *
 *	@note       a- This Queue is used only in the case of write
 *					 (word or buffer), erase only!
 *	@warning	  b- In case of using the function, "flash_write_buffer",
 *					 It's the USER RESPONSIBILITY to allocate the buffer
 *					 sent to the function, assure it's fixed through the
 *					 write operation and, free the buffer after finishing
 *					 the operation.
 */

#ifndef TWI_INTERNAL_FLASH_H__
#define TWI_INTERNAL_FLASH_H__
/**
*   @defgroup flash_group TWI Flash HAL
*   This is the definition of TWI HAL for Flash.
*   @{
*/

/*-*********************************************************/
/*- INCLUDES ----------------------------------------------*/
/*-*********************************************************/

#include "twi_types.h"
#include "twi_retval.h"
#include "platform_defines.h"
#include "twi_flash.h"

/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------------*/
/*-*********************************************************/

/*-*********************************************************/
/*- NORDIC FLASH MEMORY PARAMETERS ------------------------*/
/*-*********************************************************/

/*-*********************************************************/
/*- ENUMS -------------------------------------------------*/
/*-*********************************************************/

/**
*	@enum		tenu_flash_operations_done
*	@brief		enum used to define the status of flash queue.
*/
typedef enum
{
	TWI_FLASH_ERASE_OP_DONE,

	TWI_FLASH_WRITE_BYTE_OP_DONE,

	TWI_FLASH_WRITE_WORD_OP_DONE,

	TWI_FLASH_WRITE_BUFFER_OP_DONE
}tenu_flash_internal_operations_done;

/*-*********************************************************/
/*- STRUCTS AND UNIONS ------------------------------------*/
/*-*********************************************************/

/**
 *	@struct		tstr_internal_flash_param
 *	@brief		structure used to hold the flash operation call back parameters
 */
typedef struct
{
	tenu_flash_internal_operations_done	enu_flash_op_done;
}tstr_internal_flash_param;

/*----------------------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*----------------------------------------------------------*/

/*-*********************************************************/
/*- FUNCTION LIKE MACROS ----------------------------------*/
/*-*********************************************************/

/**
 *	@brief			GET_FLASH_PAGE_NUMBER(u32_page_address)	, Macro that get the page number (0 - 255) from the page address.
 *  @param[in]  	u32_page_address			:   The input variable/number.
*/
#define GET_INT_FLASH_PAGE_NUMBER(u32_page_address)						twi_internal_flash_get_page_num_from_addr(u32_page_address)

/*-*********************************************************/
/*- APIs DECLARATIONS -------------------------------------*/
/*-*********************************************************/
/**
 *	@brief		API used for flash reinit in case of pwdata in wakeup .
 */
twi_s32 flash_restore_init(void);
/**
 *	@brief		API used for initializing the flash HAL module.
 *  @return    ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_internal_flash_init(void);

/**
 *	@brief		API used for de-initializing the flash HAL module.
 *   @return    ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_internal_flash_deinit(void);

/**
 *	@brief		API used for getting the base address of flash HAL module.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_u32 twi_internal_flash_get_base_addr(void);

/**
 *    @brief      get min section erasable size
 */
twi_u32 twi_internal_flash_get_min_eraseable_sec(void);

/**
 *	@brief		API used for getting the size of the allowed flash.
 *  @return   	The size of the internal flash in bytes
 */
twi_u32 twi_internal_flash_get_size(void);

/**
 *	@brief		Flash erase function that registers for an erase event/operation in the flash queue.
 *	@param[in]  page_number		The page number to be erased.
 *	@param[in] 	pf_erase_op_cb	Pointer to call back function called when the erase operation in the flash end.
 *	@param[in]	pv_user_cb_data	Void pointer holds user data need to pass through flash CB
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_internal_flash_erase(twi_u32 u32_page_number, tpf_twi_flash_cb pf_erase_op_cb, void* pv_user_cb_data);

/**
 *	@brief		Flash write_byte function that registers for an write_byte event/operation in the flash queue.
 *	@param[in]  pu32_dst			Pointer to the flash, "destination", address to save the data byte to.
 *	@param[in]  u8_src_byte 		The data byte to be saved in the flash.
 *	@param[in] 	pf_write_byte_op_cb	Pointer to call back function called when the write operation in the flash end.
 *	@param[in]	pv_user_cb_data		Void pointer holds user data need to pass through flash CB
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_internal_flash_write_byte(twi_u32 * pu32_dst, twi_u8 u8_src_byte, tpf_twi_flash_cb pf_write_byte_op_cb, void* pv_user_cb_data);

/**
 *	@brief		Flash write_word function that registers for an write_word event/operation in the flash queue.
 *	@param[in]  pu32_dst			Pointer to the flash, "destination", address to save the data word to.
 *	@param[in]  u32_src_word		The data word, "4 bytes", to be saved to the flash.
 *	@param[in] 	pf_write_word_op_cb	Pointer to call back function called when the write operation in the flash end.
 *	@param[in]	pv_user_cb_data		Void pointer holds user data need to pass through flash CB.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h.
*/
twi_s32 twi_internal_flash_write_word(twi_u32 * pu32_dst, twi_u32  u32_src_word, tpf_twi_flash_cb pf_write_word_op_cb, void* pv_user_cb_data);

/**
 *	@brief		Flash write buffer function that registers for an write buffer event/operation in the flash queue.
 *  @param[in]  pu32_dst_address	Pointer to the flash, "destination", address to save the data to.
 *  @param[in]  pu8_src_data		Pointer to the data, "source", address to be saved to the flash. (Must be aligned)
 *  								(USER MUST save this data until the operation is done, May be edit in this buffer).
 *  @param[in]  u16_src_size		The data buffer size in bytes.
 *  @param[in] 	pf_write_buff_op_cb	Pointer to call back function called when the write operation in the flash end.
 *	@param[in]	pv_user_cb_data		Void pointer holds user data need to pass through flash CB.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_internal_flash_write_buffer(twi_u32 * pu32_dst_address, twi_u8 * pu8_src_data, twi_u16 u16_src_size, tpf_twi_flash_cb pf_write_buff_op_cb, void* pv_user_cb_data);

/**
 *	@brief		Flash operations dispatcher that is responsible for handling the events/operations saved in the flash queue in order.
 *  @return     ::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
twi_s32 twi_internal_flash_dispatch(void);
/**
 *	@brief		Flash read function that reads directly a certain data corresponds to a certain address
 *							from the flash memory without registering for a queue event!
 *  @param[in]  u32_flash_addr	The flash data location to read the data from.
 *  @param[in]  pu8_read_buffer	Pointer to the buffer to load the flash data into.
 *  @param[in]  u32_read_size	The size of the data needed to be read.
 *
 *	@return		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_internal_flash_read(twi_u32 u32_flash_addr, twi_u8 * pu8_read_buffer, twi_u32 u32_read_size);
/**
 *	@brief		Function that maps the page address to page number
 *  @param[in]  u32_page_addr	the page address that needs to be maped to page number.
 *
 *	@return		the page number starting from 0 at the flash start.
*/
twi_u32 twi_internal_flash_get_page_num_from_addr(twi_u32 u32_page_addr);

#endif /*TWI_INTERNAL_FLASH_H_*/
