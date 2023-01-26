/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*  @file		twi_fifo.h
*  @brief		This module contains TWI FIFO module declarations
*/

#ifndef _TWI_FIFO_H_
#define _TWI_FIFO_H_

/*-***********************************************************/
/*- INCLUDES ------------------------------------------------*/
/*-***********************************************************/

#include "twi_types.h"
#include "twi_retval.h"
#include "twi_settings_data.h"
#include "twi_flash.h"


/*-*********************************************************/
/*- FUNCTION-LIKE MACROS ----------------------------------*/
/*-*********************************************************/

#define TWI_ERR_FIFO_OVERFLOW					(TWI_ERR_FIFO_BASE - 1)
#define TWI_ERR_FIFO_UNDERFLOW					(TWI_ERR_FIFO_BASE - 2)
#define TWI_ERR_FIFO_NOTHING_TO_READ			(TWI_ERR_FIFO_BASE - 3)
#define TWI_ERR_FIFO_UNKNOWN					(TWI_ERR_FIFO_BASE - 4)
#define TWI_ERR_FIFO_NO_FREE_SPACE				(TWI_ERR_FIFO_BASE - 5)
#define TWI_ERR_FIFO_PAGE_ERASE					(TWI_ERR_FIFO_BASE - 6)
#define TWI_ERR_FIFO_WRITE_BYTE					(TWI_ERR_FIFO_BASE - 7)
#define TWI_ERR_FIFO_ADV_READ_WITHOUT_V_READ	(TWI_ERR_FIFO_BASE - 8)
#define TWI_ERR_FIFO_REWIND_WITHOUT_V_READ		(TWI_ERR_FIFO_BASE - 9)
#define TWI_ERR_FIFO_ALLOCATE_FLASH_PAGES		(TWI_ERR_FIFO_BASE - 10)
#define TWI_ERR_FIFO_DEALLOCATE_FLASH_PAGES		(TWI_ERR_FIFO_BASE - 11)
#define TWI_ERR_FIFO_INVALID_MODULE				(TWI_ERR_FIFO_BASE - 12)
#define TWI_ERR_FIFO_INVALID_MODULE_IDX			(TWI_ERR_FIFO_BASE - 13)
#define TWI_ERR_FIFO_WRITE_BUFFER				(TWI_ERR_FIFO_BASE - 14)
#define TWI_ERR_FIFO_OVERWRITTEN_BYTES			(TWI_ERR_FIFO_BASE - 15)
#define TWI_ERR_FIFO_INVALID_WRITE_INDX			(TWI_ERR_FIFO_BASE - 16)
#define TWI_ERR_FIFO_INVALID_ERASE_INDX			(TWI_ERR_FIFO_BASE - 17)
#define TWI_ERR_FIFO_INVALID_READ_INDX			(TWI_ERR_FIFO_BASE - 18)
#define TWI_ERR_FIFO_INVALID_LOADED_SETTINGS	(TWI_ERR_FIFO_BASE - 19)
#define TWI_ERR_FIFO_ADV_MORE_AVAL_DATA			(TWI_ERR_FIFO_BASE - 20)
#define TWI_ERR_FIFO_INVALID_OFFSET				(TWI_ERR_FIFO_BASE - 21)

/*-*********************************************************/
/*- ENUMS -------------------------------------------------*/
/*-*********************************************************/
/**
*	@enum		tenu_fifo_seek
*	@brief		enum used to set the seek offset beginning
*/
typedef enum
{
	TWI_FIFO_SEEK_SET,
	TWI_FIFO_SEEK_CUR,
	TWI_FIFO_SEEK_END
}tenu_fifo_seek;
/**
*	@enum		tenu_fifo_write_op_done
*	@brief		enum used to define the status of flash queue.
*/
typedef enum
{
	TWI_FIFO_WRITE_DONE,
}tenu_fifo_write_op_done;

/**
 *	@struct		tstr_fifo_write_cb_param
 *	@brief		structure used to hold the FIFO CB parameters
 */
typedef struct
{
	tenu_fifo_write_op_done	enu_fifo_wrt_op_done;
}tstr_fifo_write_cb_param;

/*----------------------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*----------------------------------------------------------*/
typedef void(*tpf_twi_fifo_cb)(tstr_fifo_write_cb_param* pstr_write_cb_param, void *pv_user_data);

/*-*********************************************************/
/*- STRUCTS AND UNIONS ------------------------------------*/
/*-*********************************************************/

/**
*	@struct	tstr_twi_circular_fifo_info
*	@brief		structure used to hold FIFO control parameters
*/
typedef struct
{
	twi_bool	b_fifo_is_circular;
	twi_u32	u32_overwritten_bytes;
} tstr_twi_circular_fifo_info;

/**
*	@struct		tstr_twi_fifo_ctrl
*	@brief		structure used to hold FIFO control parameters
*/
typedef struct
{
	tenu_flash_types 	enu_flash_type;
	twi_u8				u8_fifo_idx;					/*!< represent the index of this FIFO, in case that system has multiple FIFOs. */
	twi_bool			b_fifo_is_init;					/*!< FIFO is INIT or not */
	twi_bool			b_virtual_read_done;			/*!< This flag is raised when there is a virtual operation done */
	twi_bool			b_save_inprogress;				/*!< This flag indicates if there is a save operation in-progress or not */
	twi_bool			b_fifo_is_overwrite;			/*!< This Flag indicates that this FIFO is Over-writable, i.e will not overflow */
	twi_bool 			b_is_critical;					/*!< This Flag indicates that this FIFO is critical, i.e will be stored in the critical section*/
	twi_u32				u32_base_add;					/*!< Base address of the FIFO */
	twi_u32				u32_r_idx;						/*!< read index (within the current page)*/
	twi_u32				u32_w_idx;						/*!< write index (within the current page)*/
	twi_u32				u32_r_page_idx;					/*!< read page index */
	twi_u32				u32_w_page_idx; 				/*!< write page index */
	twi_u32				u32_origin_page_idx;			/*!< oldest valid page index */
	twi_u32				u32_virtual_r_idx;				/*!< virtual read index */
	twi_u32				u32_virtual_r_page_idx;			/*!< virtual read page index */
	twi_u32				u32_num_virtual_data;	        /*!< virtual available data */
	twi_u32	 			u32_num_available_data;	        /*!< number of entries ready to be read*/
	twi_u32				u32_num_valid_data;		        /*!< total number of data in FIFO */
	twi_u32				u32_max_num_pages;				/*!< maximum number of pages assigned for the FIFO */
	twi_u32	 			u32_num_free_pages;				/*!< the number of currently free (erased pages) */
	twi_u32				u32_page_size;					/*!< page size in bytes (Output for user) */
	twi_u32				u32_num_free_bytes;				/*!< The number of free bytes in the FIFO*/
	tpf_twi_fifo_cb		pf_fifo_cb;						/*!< FIFO Call back called when the operation of writing happen */
	void *				pv_user_cb_data;				/*!< Pointer to user data need to passed when CB */
	twi_u8 TWI_ALIGN	au8_settings_buf[sizeof(tstr_fifo_settings)]; /*!< This buffer holds the settings that will be saved in the flash memory. */
}tstr_twi_fifo_ctrl;






/*-*********************************************************/
/*- FUNCTION DECLARATIONS ---------------------------------*/
/*-*********************************************************/

/**
 *	@function	twi_s32 twi_fifo_init(tstr_twi_fifo_ctrl *pstr_fifo_ctrl, twi_u32 u32_num_pages, tpf_twi_fifo_cb pf_fifo_cb, void* pv_user_cb_data)
 *	@brief		Initialize Flash FIFO
 *
 *	@param[in]	p_str_fifo_ctrl	Pointer to input structure allocated by the caller for the FIFO control parameters
 *	@param[in]	u32_num_pages	Number of pages used for FIFO operation.
 *	@param[in]	u32_page_size	Usable part length of pages. u32_page_size <= FLASH_PAGE_SIZE.
 *	@param[in]	pf_fifo_cb		Pointer to Call Back function .
 *	@param[in]	pv_user_cb_data	Pointer to user data passed with the CB function.
 *
 *	@return		Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
 *
 */
twi_s32 twi_fifo_init(tstr_twi_fifo_ctrl *pstr_fifo_ctrl, twi_u32 u32_num_pages, twi_u32 u32_page_size, tpf_twi_fifo_cb pf_fifo_cb, twi_bool b_is_overwritable, twi_bool b_is_critical, tenu_flash_types enu_flash_type,void *pv_user_cb_data);

/**
*	@function	twi_s32 twi_fifo_deinit(tstr_twi_fifo_ctrl* pstr_fifo_ctrl)
*	@brief		De-Initialize Flash FIFO module.
*/
twi_s32 twi_fifo_deinit(tstr_twi_fifo_ctrl* pstr_fifo_ctrl);

/**
 *	@function	twi_s32 twi_fifo_reset(tstr_twi_fifo_ctrl *pstr_fifo_ctrl)
 *	@brief		Reset the indexes of the Flash FIFO. The FIFO has to be initialized before reset it.
 *
 *	@param[in]	p_str_fifo_ctrl	Pointer to input structure allocated by the caller for the FIFO control parameters
 *
 *	@return		Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
 *
 */
twi_s32 twi_fifo_reset(tstr_twi_fifo_ctrl *pstr_fifo_ctrl);
/**
*	@function	twi_s32 twi_fifo_put_buffer(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u8* pu8_data, twi_u16 u16_data_size)
*	@brief		FIFO put buffer function
*	@param[in]	pstr_fifo_ctrl	Pointer to the structure for the fifo control.
*	@param[in]	pu8_data		Pointer of the data to be put in the fifo.
*	@param[in]	u32_data_size	data size
*	@return		TWI_SUCCESS in case of success and (-v) error code in case of failure
*/
twi_s32 twi_fifo_put_buffer(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u8* pu8_data, twi_u32 u32_data_size, tstr_twi_circular_fifo_info *pstr_circular_fifo);

/**
*	@function	twi_s32 twi_fifo_get(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u8 *pu8_data)
*	@brief		FIFO get function
*	@return		TWI_SUCCESS in case of success and (-v) error code in case of failure
*/
twi_s32 twi_fifo_get(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u8 *pu8_data);

/**
*	@function	twi_s32 twi_fifo_get_num_of_available_locations(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u32 * pu32_no_of_locations)
*	@brief		FIFO get number of locations function
*	@return		TWI_SUCCESS in case of success and (-v) error code in case of failure
*/
twi_s32 twi_fifo_get_num_of_available_locations(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u32 * pu32_no_of_locations);
/*
*	@function	 twi_s32 twi_fifo_get_num_of_virtual_locations(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u32 * pu32_no_of_locations)
*	@brief		get the number of bytes stored in the virtual FIFO
*	@return		TWI_SUCCESS in case of success and (-v) error code in case of failure
*/
twi_s32 twi_fifo_get_num_of_virtual_locations(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u32 * pu32_no_of_locations);
/*
*	@function	 twi_s32 twi_fifo_get_num_of_valid_locations(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u32 * pu32_no_of_locations)
*	@brief		get the number of bytes stored in the Valid FIFO
*	@return		TWI_SUCCESS in case of success and (-v) error code in case of failure
*/
twi_s32 twi_fifo_get_num_of_valid_locations(tstr_twi_fifo_ctrl *pstr_fifo_ctrl, twi_u32 *pu32_no_of_locations);
/**
*	@function	twi_s32 twi_fifo_virtual_read_buffer(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u8 *pu8_buf, twi_u32 u32_r_sz, twi_u32 *pu32_act_r_sz)
*	@brief		FIFO read buffer function
*	@return		TWI_SUCCESS in case of success and (-v) error code in case of failure
*/
twi_s32 twi_fifo_virtual_read_buffer(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u8 *pu8_buf, twi_u32 u32_r_sz, twi_u32 *pu32_act_r_sz);
/**
*	@brief		FIFO seek function
*	@return		TWI_SUCCESS in case of success and (-v) error code in case of failure
*/
twi_s32 twi_fifo_seek_virtual_read_idx(tstr_twi_fifo_ctrl* pstr_fifo_ctrl,twi_s32 s32_offset,tenu_fifo_seek enu_orgin,twi_bool b_use_fifo_origin);
/*
*	@function	twi_s32 twi_fifo_advance_write_idx(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u32 r_sz)
*	@brief		Advance write index
*	@param[in]	pstr_fifo_ctrl	Pointer to the structure for the fifo control.
*	@param[in]	u32_w_sz	data size
*	@return		TWI_SUCCESS in case of success and (-v) error code in case of failure
*/
twi_s32 twi_fifo_advance_write_idx(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u32 u32_w_sz);
/**
*	@function	twi_s32 twi_fifo_rewind_virtual_read_idx(tstr_twi_fifo_ctrl* pstr_fifo_ctrl)
*	@brief		revert all the previous virtual read operation.
*	@return		TWI_SUCCESS in case of success and (-v) error code in case of failure
*/
twi_s32 twi_fifo_rewind_virtual_read_idx(tstr_twi_fifo_ctrl* pstr_fifo_ctrl);

/**
*	@function	twi_s32 twi_fifo_advance_read_idx(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u32 u32_r_sz)
*	@brief		confirm FIFO read buffer function. It'll simply update FIFO read pointers to the previous virtual read pointers.
*				this function should be called after making the virtual read operation.
*	@return		TWI_SUCCESS in case of success and (-v) error code in case of failure
*/
twi_s32 twi_fifo_advance_read_idx(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u32 u32_r_sz);
/*
*	@function	twi_s32 twi_fifo_rewind_read_idx(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u32 r_sz)
*	@brief		Rewind read index
*	@return		TWI_SUCCESS in case of success and (-v) error code in case of failure
*/
twi_s32 twi_fifo_rewind_read_idx(tstr_twi_fifo_ctrl* pstr_fifo_ctrl, twi_u32 u32_r_sz);
/**
 *	@brief		FIFO  dispatcher, that responsible of calling the flash dispatch
 *  @return     ::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
 */
void twi_fifo_dispatch(void);
/**
 *	@function	twi_s32 twi_fifo_save_settings(tstr_twi_fifo_ctrl * pstr_fifo_ctrl)
 *
 *	@brief		This function used to save the FIFO settings in the flash memory.
 *
 *	@param[in]	pstr_fifo_ctrl			Pointer to structure holds FIFO members.
 *
 *	@return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
 *
 */
twi_s32 twi_fifo_save_settings(tstr_twi_fifo_ctrl * pstr_fifo_ctrl);

/**
 *	@function	twi_s32 twi_fifo_load_settings(tstr_twi_fifo_ctrl * pstr_fifo_ctrl)
 *
 *	@brief		This function used to load the FIFO settings that are already saved before in the flash memory.
 *
 * 	@param[in]	pstr_fifo_ctrl			Pointer to structure holds FIFO members.
 *
 *	@return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
 *
 */
twi_s32 twi_fifo_load_settings(tstr_twi_fifo_ctrl * pstr_fifo_ctrl);


#endif // _TWI_FIFO_H_
