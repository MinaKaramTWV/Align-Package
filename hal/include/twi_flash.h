/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file		twi_flash.h
 *	@brief		This module contains the flash wrapping API'S fro internal and external flash
 */

#ifndef TWI_FLASH_H__
#define TWI_FLASH_H__
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

/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------------*/
/*-*********************************************************/
#define TWI_FLASH_ERR(...)
#define TWI_FLASH_INFO(...)
#define TWI_FLASH_DBG(...)

#define TWI_FLASH_LOG_LEVEL_NONE  (0)
#define TWI_FLASH_LOG_LEVEL_ERR   (1)
#define TWI_FLASH_LOG_LEVEL_INFO  (2)
#define TWI_FLASH_LOG_LEVEL_DBG   (3)

#ifndef TWI_FLASH_LOG_LEVEL
#define TWI_FLASH_LOG_LEVEL   TWI_FLASH_LOG_LEVEL_NONE
#endif

#define TWI_FLASH_PRINT(...) 		do{TWI_LOGGER(__VA_ARGS__);}while(0)

#if (TWI_FLASH_LOG_LEVEL >= TWI_FLASH_LOG_LEVEL_ERR)

	#undef TWI_FLASH_ERR
	#define TWI_FLASH_ERR(...) 	do{TWI_LOGGER("[ERR][%s][%d]",TWI_FUNCTION,TWI_LINE);TWI_LOGGER(__VA_ARGS__);}while(0)

	#if (TWI_FLASH_LOG_LEVEL >= TWI_FLASH_LOG_LEVEL_INFO)

		#undef TWI_FLASH_INFO
		#define TWI_FLASH_INFO(...) 	do{TWI_LOGGER("[FLASH]:[INFO]");TWI_LOGGER(__VA_ARGS__);}while(0)

		#if (TWI_FLASH_LOG_LEVEL >= TWI_FLASH_LOG_LEVEL_DBG)

			#undef TWI_FLASH_DBG
			#define TWI_FLASH_DBG(...) 	do{TWI_LOGGER("[FLASH]:[DBG][%s][%d]",TWI_FUNCTION,TWI_LINE);TWI_LOGGER(__VA_ARGS__);}while(0)
		#endif
	#endif
#endif
/**
*   @defgroup twi_flash_hal_retval_group Flash HAL module return values
*   @{
*/

#define TWI_FLASH_ERROR_QUEUE_NO_SPACE					(TWI_FLASH_ERR_BASE - 1)	/**< @brief Define error for no space in queue flash */

#define	TWI_FLASH_ERROR_PUT_OVERFLOW					(TWI_FLASH_ERR_BASE - 2)	/**< @brief Return value when put, if not ok "flash overflow" */

#define	TWI_FLASH_ERROR_DISPATCH_NOT_READY 				(TWI_FLASH_ERR_BASE - 3)  	/**< @brief Flash is not ready yet to dispatch any command */

#define	TWI_FLASH_ERROR_GET_EMPTY						(TWI_FLASH_ERR_BASE - 4)	/**< @brief Return value when get, if the queue is empty */

#define TWI_FLASH_QUEUE_EMPTY  							(TWI_FLASH_ERR_BASE - 5)	/**< @brief Return value when flush, but the queue is empty! */

#define TWI_FLASH_ERROR_NO_FREE_PAGES					(TWI_FLASH_ERR_BASE - 6)	/**< @brief Return value when try to allocate new page in the flash memory, but no free pages */

#define TWI_FLASH_ERROR_PAGES_NOT_ALLOC					(TWI_FLASH_ERR_BASE - 7)	/**< @brief Return value when try to de-allocate page in the flash memory, but no the page isn't allocated */

#define TWI_FLASH_ERROR_OPER_TIMEOUT					(TWI_FLASH_ERR_BASE - 8)	/** Return value when try to do flash operation, but the operation takes more time to be done. */

#define TWI_FLASH_ERROR_FLASH_BUSY						(TWI_FLASH_ERR_BASE - 9)	/** Return value when try to do flash operation, but the last operation is still in progress (Flash is busy). */

#define TWI_FLASH_ERROR_VERFICATION_FAIL				(TWI_FLASH_ERR_BASE - 10)	/** Return value when try to do flash operation, but the last operation is still in progress (Flash is busy). */

#define TWI_FLASH_ERROR_AHB_ERR							(TWI_FLASH_ERR_BASE - 11)
#define TWI_FLASH_ERROR_PROTECTION_VIOLATION			(TWI_FLASH_ERR_BASE - 12)
#define TWI_FLASH_ERROR_FLASH_INIT_ERR					(TWI_FLASH_ERR_BASE - 13)
#define TWI_FLASH_ERROR_FLASH_WRITE_ERR					(TWI_FLASH_ERR_BASE - 14)
#define TWI_FLASH_ERROR_FLASH_ERASE_ERR					(TWI_FLASH_ERR_BASE - 15)
#define TWI_FLASH_ERROR_FLASH_FAIL						(TWI_FLASH_ERR_BASE - 16)

/** @} */   /* twi_flash_hal_retval_group */



#define FLASH_INVALID_ADDRESS				(0)							/**< @brief This MACRO indicates the invalid address in the flash memory */

#define FLASH_EMPTY_BYTE_VALUE				(0xFF)						/**< @brief This is the value of the empty byte size when the flash is erased */

#define FLASH_EMPTY_WORD_VALUE				(0xFFFFFFFF)				/**< @brief This is the value of the empty word when the flash is erased */

/*-*********************************************************/
/*- ENUMS -------------------------------------------------*/
/*-*********************************************************/

/**
*	@enum		tenu_flash_operations_done
*	@brief		enum used to define the status of flash queue.
*/
typedef enum
{
	TWI_FLASH_ERASE_DONE,
	TWI_FLASH_WRITE_DONE
}tenu_flash_operations_done;


/**
*	@enum		tenu_flash_types
*	@brief		enum used to define flash types
*/
typedef enum
{
	TWI_INTERNAL_FLASH = 1,
	TWI_EXTERNAL_FLASH = 2
}tenu_flash_types;

/*-*********************************************************/
/*- STRUCTS AND UNIONS ------------------------------------*/
/*-*********************************************************/

/**
 *	@struct		tstr_flash_cb_param
 *	@brief		structure used to hold the flash operation call back parameters
 */
typedef struct
{
	tenu_flash_types enu_flash_type;
	tenu_flash_operations_done	enu_flash_op_done;
}tstr_flash_cb_param;

/*----------------------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*----------------------------------------------------------*/
typedef void(*tpf_twi_flash_cb)(tstr_flash_cb_param* pstr_cb_param, void *pv_user_data);

/*-*********************************************************/
/*- FUNCTION LIKE MACROS ----------------------------------*/
/*-*********************************************************/

/*-*********************************************************/
/*- APIs DECLARATIONS -------------------------------------*/
/*-*********************************************************/

/**
 *	@brief		API used for get the flash HAL size.
 *	@param[IN]	enuFlashType     	Flash Type (TWI_INTERNAL_FLASH.TWI_EXTEENAL_FLASH),@tenu_flash_types
 *  @return    ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_u32 twi_flash_get_size(tenu_flash_types enuFlashType);

/**
 *	@brief		API used for initializing the flash HAL module.
 *	@param[IN]	enuFlashType     	Flash Type (TWI_INTERNAL_FLASH.TWI_EXTEENAL_FLASH),@tenu_flash_types
 *  @return    ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_flash_init(void *pv,tenu_flash_types enuFlashType);

/**
 *	@brief		API used for de-initializing the flash HAL module.
 *	@param[IN]	enuFlashType     	Flash Type (TWI_INTERNAL_FLASH.TWI_EXTEENAL_FLASH),@tenu_flash_types
 *   @return    ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_flash_deinit(void *pv,tenu_flash_types enuFlashType);

/**
 *  @brief      get Flash min erase section size
 *  @param[IN]  enuFlashType         Flash Type (TWI_INTERNAL_FLASH.TWI_EXTEENAL_FLASH),@tenu_flash_types
 *  @return     section Size in bytes
 */
twi_u32 twi_flash_get_min_eraseable_sec(tenu_flash_types enuFlashType);

/**
 *	@brief		API used for logically allocation for pages in the flash memory.
 *	@param[in]	u16_number_pages		Number of pages want to allocate in the flash memory to use.
 *	@param[out]	pu32_pages_base_addr	Pointer to base address of the pages.
 *	@param[IN]	enuFlashType     	Flash Type (TWI_INTERNAL_FLASH.TWI_EXTEENAL_FLASH),@tenu_flash_types
 *  @return    ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_flash_pages_alloc(twi_u16 u16_number_pages, twi_u32 *pu32_pages_base_addr,tenu_flash_types enuFlashType);

/**
 *	@brief		Flash erase function
 *	@param[in]  u32_page_addr		The page address to be erased.
 *	@param[in] 	pf_erase_op_cb	Pointer to call back function called when the erase operation in the flash end.
 *	@param[in]	pv_user_cb_data	Void pointer holds user data need to pass through flash CB
 *	@param[IN]	enuFlashType     	Flash Type (TWI_INTERNAL_FLASH.TWI_EXTEENAL_FLASH),@tenu_flash_types
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_flash_erase(twi_u32 u32_page_addr, tpf_twi_flash_cb pf_erase_op_cb, void* pv_user_cb_data,tenu_flash_types enuFlashType);

/**
 *	@brief		Flash write operations
 *  @param[in]  u32_Address     	flash address, "destination", address to save the data to.
 *  @param[in]  pu8_src_data		Pointer to the data, "source", address to be saved to the flash. (Must be aligned)
 *  								(USER MUST save this data until the operation is done, May be edit in this buffer).
 *  @param[in]  u32_src_size		The data buffer size in bytes.
 *  @param[in] 	pf_write_buff_op_cb	Pointer to call back function called when the write operation in the flash end.
 *	@param[in]	pv_user_cb_data		Void pointer holds user data need to pass through flash CB.
 *	@param[IN]	enuFlashType     	Flash Type (TWI_INTERNAL_FLASH.TWI_EXTEENAL_FLASH),@tenu_flash_types
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_flash_write(twi_u32 u32_Address, twi_u8 * pu8_src_data, twi_u32 u32_src_size, tpf_twi_flash_cb pf_write_buff_op_cb,
		void* pv_user_cb_data,tenu_flash_types enuFlashType);
/**
 *	@brief		Flash read function that reads directly a certain data corresponds to a certain address
 *							from the flash memory without registering for a queue event!
 *  @param[in]  u32_flash_addr	The flash data location to read the data from.
 *  @param[in]  pu8_read_buffer	Pointer to the buffer to load the flash data into.
 *  @param[in]  u16_read_size	The size of the data needed to be read.
 *	@param[IN]	enuFlashType     Flash Type (TWI_INTERNAL_FLASH.TWI_EXTEENAL_FLASH),@tenu_flash_types
 *
 *	@return		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_flash_read(twi_u32 u32_Addr, twi_u8 * pu8_read_buffer, twi_u32 u32_read_size,tenu_flash_types enuFlashType);
/**
 *	@fn		twi_spi_flash_verfiy
 *	@brief	verification of writing to spi flash
 *	@param[IN]	pu8VerifyBuffer
 *					Pointer to data buffer
 *	@param[IN]	u32FlashAddr
 *					Address at the SPI flash
 *	@param[IN]	u32VerifySize
 *					Data size
 *	@param[IN]	enuFlashType
 *					Flash Type
 *	@return	 Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */
twi_s32 twi_flash_verfiy(twi_u8 *pu8VerifyBuffer, twi_u32 u32FlashAddr,twi_u32 u32VerifySize,tenu_flash_types enuFlashType);
/**
 *	@fn		twi_flash_copy
 *	@brief	copy from the flash to the same flash
 *	@param[IN]	u32SrcFlashAddr
 *					Pointer to data buffer
 *	@param[IN]	u32DestFlashAddr
 *					Address at the SPI flash
 *	@param[IN]	u32FlashSize
 *					Data size
 *	@param[IN]	enuFlashType
 *					Flash Type
 *  @param[in] 	pf_write_buff_op_cb	Pointer to call back function called when the write operation in the flash end.
 *	@param[in]	pv_user_cb_data		Void pointer holds user data need to pass through flash CB.
 *	@return	 Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */
twi_s32 twi_flash_copy(twi_u32 u32DestFlashAddr,twi_u32 u32SrcFlashAddr, twi_u32 u32FlashSize,tpf_twi_flash_cb pf_write_buff_op_cb,
		void* pv_user_cb_data,tenu_flash_types enuFlashType);
/**
 *	@brief		Flash operations dispatcher, that responsible of calling the internal or external flash dispatch
 *  @return     ::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
twi_s32 twi_flash_dispatch(void);

/**
*   @brief      This is a function that protect the memory from SWD Read/Write/Erase.
*	@return		::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
*/
twi_s32 twi_flash_protect(void);

/**
*   @brief      This is a function that gets memory protection status.
*   @param[out] pb_protected      Memory is protected.
*	@return		::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
*/
twi_s32 twi_flash_protect_status(twi_bool *pb_protected);

#endif
