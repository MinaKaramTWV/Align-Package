/*-**********************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved.	*/
/*-**********************************************************/

/**
 * @file			twi_internal_flash.c
 * @brief			This module contains the flash driver implementations.
 * 					In this module, the used technique is to queue
 * 				  	the flash events in a queue via the functions
 * 				  	"flash_opr_put" and "flash_opr_get" which push and
 * 				  	get the events in/to a queue. The physical operation
 * 				  	is done after receiving a notification via the call back
 * 				  	function "flash_cb_handler".
 * 				  	Finite state machine is used here also to control
 *				  	the flash states and transitions as the flash module
 *				  	takes some time to erase or write(about 50 ms to finish!).
 * @note	       	a- This Queue is used only in the case of write
 *						(word or buffer), erase only!
 * @warning			b- In case of using the function, "flash_write_buffer",
 *					 	It's the USER RESPONSIBILITY to allocate the buffer
 *					 	sent to the function, assure it's fixed through the
 *					 	write operation and, free the buffer after finishing the operation.
 */

/*-*********************************************************/
/*- INCLUDES ----------------------------------------------*/
/*-*********************************************************/

#include "twi_common.h"
#include "twi_internal_flash.h"
#include "nrf_soc.h"
#include "app_error.h"
#include "twi_debug.h"
#include "platform_defines.h"
#include "twi_swi.h"

#include "twi_nordic_sdk_include_cfg.h"

#ifdef	FLASH_LOG_ENABLE

	#define	FLASH_LOG(...)							TWI_LOGGER("[FLASH]: "__VA_ARGS__)
	#define	FLASH_LOG_COMBINED(STRING,INT)			TWI_LOGGER("[FLASH]: %s,%d\n",STRING, INT)

	#define	FLASH_LOG_ERROR(...)					TWI_LOGGER_ERR("[FLASH_ERR]: "__VA_ARGS__)
	#define	FLASH_LOG_COMBINED_ERROR(STRING,INT)	TWI_LOGGER_ERR("[FLASH_ERR]: %s,%d\n",STRING, INT)

#else

	#define	FLASH_LOG(...)
	#define	FLASH_LOG_COMBINED(...)

	#define	FLASH_LOG_ERROR(...)
	#define	FLASH_LOG_COMBINED_ERROR(...)

#endif

/*-*********************************************************/
/*- EXTERN  -----------------------------------------------*/
/*-*********************************************************/
extern twi_u32 __etext;                      /* END of code address */
extern twi_u32 __data_start__[];               /* Start address of data section in RAM */
extern twi_u32 __data_end__[];                 /* END address of data section in RAM */

/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------------*/
/*-*********************************************************/
#define END_CODE_ADDRESS (twi_u32)(&__etext) 				/**< @brief End address for the code in the flash memory
															(End of .text section in the memory) */

#define FLASH_DATA_SECTION_SIZE     (twi_u32)((twi_u32)(&__data_end__) - (twi_u32)(&__data_start__))

#ifdef nordic_sdk_16_0_0
#define APP_SOC_OBSERVER_PRIO       1                                   /**< Applications' SoC observer priority. You shoulnd't need to modify this value. */
#endif
/*-*********************************************************/
/*- FUNCTION LIKE MACROS ----------------------------------*/
/*-*********************************************************/


/**
 *	@brief		A flash macro used in the "read byte function" from the flash and returns
 *							the needed byte (depending on it's index).
 *  @details    This macro calls internally 1 macro "FLASH_OFFSET_CALCULATE"
 *  @param[in]  WORD    			 The original word.
 *  @param[in]  BYTE_OFFSET    The byte location in the word (byte index).
*/
#define FLASH_EXCLUDE_BYTE_WITH_OFFSET(WORD, BYTE_OFFSET)		(((WORD) & (0xFF << FLASH_OFFSET_CALCULATE(BYTE_OFFSET))) >> FLASH_OFFSET_CALCULATE(BYTE_OFFSET))

/**
 *	@brief		A flash macro used in the write/read byte from the flash and returns
 *						the input word after embedding the src_byte in it.
 *  @details    This macro calls internally 2 macros "FLASH_BYTE_TO_WORD" & "FLASH_OFFSET_CALCULATE"
 *  @param[in]  WORD    			 The original word.
 *  @param[in]  SRC_BYTE       The source byte needed to be converted.
 *  @param[in]  BYTE_OFFSET    The byte location in the word (byte index).
*/
#define FLASH_EMBED_BYTE_IN_OFFSET(WORD, SRC_BYTE, BYTE_OFFSET)	(twi_u32) (((WORD) & (FLASH_BYTE_TO_WORD( 0x00, BYTE_OFFSET )) ) | ((SRC_BYTE) << FLASH_OFFSET_CALCULATE(BYTE_OFFSET)) )

/**
 *	@brief		An internal flash macro that is used to convert the input byte to an all F 32 bit
 *  						except the byte itself, i.e.(0xFF-XX-FF-FF), byte location here is 2 "index".
 *  @param[in]  SRC_BYTE       The source byte needed to be converted.
 *  @param[in]  BYTE_OFFSET    The byte location in the word (byte index).
*/
#define FLASH_BYTE_TO_WORD(SRC_BYTE, BYTE_OFFSET)		(~( ( 0x000000FF & (~SRC_BYTE) ) << FLASH_OFFSET_CALCULATE(BYTE_OFFSET) ))

/**
 *	@brief		An internal flash macro that is used to calculate the byte location in the word, translates the index into the actual location (number of shifts).
 *  @param[in]  BYTE_OFFSET    The byte offset as an index.
*/
#define FLASH_OFFSET_CALCULATE(BYTE_OFFSET)				((BYTE_OFFSET) << 3)

/**
 *	@brief		A flash macro used in the write/read byte from the flash and returns the byte offset in the word.
 *  @param[in]  X    Address to get from it the byte offset.
*/
#define FLASH_BYTE_OFFSET(X)							(( X ) & ( 0x00000003 ))

/**
 *	@brief		A flash macro used to get the word aligned address.
 *  @param[in]  POINTER_TO_ADDRESS    Address with byte offset.
*/
#define FLASH_WORD_ALIGNED(POINTER_TO_ADDRESS)			(((twi_u32) (POINTER_TO_ADDRESS) ) & (0xFFFFFFFC ))

/*-*********************************************************/
/*- ENUMS -------------------------------------------------*/
/*-*********************************************************/

/**
*	@enum		tenu_flash_trigger
*	@brief		enum used to define the flash trigger states
*/
typedef enum
{
	NO_TRIGGER = 0,
	TRIGGER
}tenu_flash_trigger;

/**
 *	@enum		tenu_twi_internal_flash_operations
 *	@brief		ENUM used to define the flash operations
 */
typedef enum tenu_twi_internal_flash_operations
{
	NO_OP = 0,
	ERASE_OP,
	WRITE_WORD_OP,
	WRITE_BUFFER_OP,
	WRITE_BYTE_OP,
}tenu_twi_internal_flash_operations;

/**
*	@enum		tenu_twi_internal_flash_states
*	@brief		enum used to define the flash states
*/
typedef enum tenu_twi_internal_flash_states
{
	NOP_STATE = 0,
	ERASING_STATE,
	ERASING_DONE_STATE,
	STORING_STATE,
	STORING_DONE_STATE,
}tenu_twi_internal_flash_states;

/*-*********************************************************/
/*- STRUCTS AND UNIONS ------------------------------------*/
/*-*********************************************************/

/**
*	@struct		tstr_flash_write_data
*	@brief		structure used to hold the write operation parameters
*/
typedef struct
{
	twi_u16		u16_size;			/**< @brief Size of the data that will be saved in the flash memory. */
	twi_u32 *	pu32_flash_add;		/**< @brief Pointer to the flash address "destination" that the data will be saved in. */

	twi_u32 * 	pu32_src_data_copy;
	union data_type
	{
		twi_u32 * 	pu32_src_data_add;			/**< @brief Pointer to the data buffer that will be written to flash, in case of write buffer. */
		twi_u32		u32_src_data_word;			/**< @brief Data word variable, in case of flash word saving. */
	}uni_data_type;

}tstr_flash_write_data;

/**
*	@struct		tstr_flash_erase_data
*	@brief		structure used to hold the erase operation parameters
*/
typedef struct
{
	twi_u32 	u32_page_number;				/**< @brief Page number to be erased. */
}tstr_flash_erase_data;

/**
*	@struct		tstr_twi_internal_flash_opr_data
*	@brief		structure used to hold the operation and link to its parameters
*/
typedef struct
{
	tenu_twi_internal_flash_operations  enu_flash_operation;	/**< @brief This is the flash operation which will be applied to the flash;
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 write buffer, write word, erase page. */
	tpf_twi_flash_cb pf_flash_op_cb;		/**< @brief Pointer to call back function called when the write operation in the flash end */
	void * pv_user_cb_data;

	tstr_internal_flash_param str_cb_param;		/**< @brief Structure holds CB parameter must be passed to user after the flash operation completed */

	union 
	{
		tstr_flash_write_data  str_write_data;		/**< @brief Structure of the write operation data. */
		tstr_flash_erase_data  str_erase_data;		/**< @brief Structure of the erase operation data. */
	}uni_opr_type;

}tstr_twi_internal_flash_opr_data;

/**
*	@struct		tstr_twi_internal_flash_queue_info
*	@brief		structure used to hold the flash queue and its parameters
*/
typedef struct
{
	tenu_twi_internal_flash_states		enu_flash_state;						/**< @brief Define the flash state with NOPE_STATE */
	twi_u8								u8_num_free_space;						/**< @brief Number of free spaces in the the queue */
	twi_u8								read_index;								/**< @brief The location to start reading from. */
	twi_u8								write_index;							/**< @brief The location to start writing to. */
	tstr_twi_internal_flash_opr_data 	astr_flash_queue[FLASH_QUEUE_SIZE];		/**< @brief Define the queue with the length of FLASH_QUEUE_SIZE */
}tstr_twi_internal_flash_queue_info;

/*-***********************************************************/
/*- LOCAL FUNCTIONS Prototypes ------------------------------*/
/*-***********************************************************/


/*-***********************************************************/
/*- GLOBAL STATIC VARIABLES ---------------------------------*/
/*-***********************************************************/

static twi_bool gb_is_inited = TWI_FALSE;						/**< @brief Flag that represent the current state of the flash module.*/

static twi_bool gb_last_buffer_operation = TWI_FALSE;			/**< @brief Global variable indicates the buffer operation is
																	the last one in the buffer or not. */

static twi_bool gb_flash_op_done_success = TWI_TRUE;			/**< @brief Global variable indicates that the last operation
																	for the flash is success or failure */

static twi_u32 gu32_word_wrt = 0;								/**< @brief Global variable holds the word value need to be saved in the flash memory */

static tstr_twi_internal_flash_queue_info gstr_flash_queue_handle =		/**< @brief Define flash queue. */
{
	.enu_flash_state = NOP_STATE,
	.read_index = 0,
	.write_index = 0,
	.u8_num_free_space = FLASH_QUEUE_SIZE,
};

/*-*********************************************************/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/*-*********************************************************/

/**
 *	@brief		Dequeue a flash operation from the flash queue "used for write_word, write_buffer and, erase_page only".
 *  @param[out] p_flash_opr_data	Pointer to Pointer to a structure that holds the operation "write_word, write_buffer,
 *																				erase" and pointer to the operation related data.
 *  @return     FLASH_GET_SUCCESS       If the function succeeded to dequeue a flash operation/event.
 *  @return     FLASH_ERROR_GET_EMPTY	In case of empty queue, queue is empty!, return error.
*/
static twi_s32 flash_opr_get(tstr_twi_internal_flash_opr_data ** ppstr_flash_opr_data)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	if(gstr_flash_queue_handle.u8_num_free_space == FLASH_QUEUE_SIZE)			/* If the queue is not empty, not circular write */
	{
		/* In case of empty queue, return error. */
		s32_retval = TWI_FLASH_ERROR_GET_EMPTY;
	}
	else
	{
		/* In case of not empty queue, return the first event in the queue. */
		/* Dequeue the event in the next available queue location. */

		*ppstr_flash_opr_data = &(gstr_flash_queue_handle.astr_flash_queue[gstr_flash_queue_handle.read_index]);
		/* Advance the queue read index while the call back return with success. */
	}

	return s32_retval;
}

/**
 *	@brief			Set the flash state.
 *  @param[in]  	current_state    Input for the current state of the flash.
 *  @param[in]  	trigger_option   Option value which triggers the end of the operation physically.
*/
static void set_flash_state(tenu_twi_internal_flash_states current_state, tenu_flash_trigger enu_trigger_option)
{
	switch(enu_trigger_option)				/* Check for the trigger option, in case of flash operation completion */
	{
		case TRIGGER:
			switch(gstr_flash_queue_handle.enu_flash_state)
			{
				case ERASING_STATE:
					/*Switch the flash state to be: Erasing finished.
						To be set by the call back function only*/
					gstr_flash_queue_handle.enu_flash_state = ERASING_DONE_STATE;
				break;

				case STORING_STATE:
					/*Switch the flash state to be: Storing finished.
						To be set by the call back function only*/
					gstr_flash_queue_handle.enu_flash_state = STORING_DONE_STATE;
				break;

				default:
					/*Do Nothing*/
				break;
			}
			break;
		case NO_TRIGGER:
			/* Just set the value */
			gstr_flash_queue_handle.enu_flash_state = current_state;
			break;
		default:
			/*Do Nothing*/
			break;
	}
}

static void byte_to_alligned_word(twi_u32 * pu32_dst, twi_u8 u8_src_byte, twi_u32* pu32_alligned_dst, twi_u32* pu32_word)
{
	twi_u8	u8_byte_offset;						/* Used to know the byte location in the word itself. */

	u8_byte_offset = FLASH_BYTE_OFFSET((twi_u32) pu32_dst);

	/* Remove the least 2 bits which are the byte offset in the word. */

	*pu32_alligned_dst = FLASH_WORD_ALIGNED(pu32_dst);

	*pu32_word = FLASH_EMBED_BYTE_IN_OFFSET(0xFFFFFFFF, u8_src_byte, u8_byte_offset);
}

/**
*	@brief		ERASE operation function that is used to ask the flash module to erase.
*	@param[in]  flash_opr_data  Pointer to a structure that holds the operation "write_word, write_buffer, erase" and
*																				pointer to the operation related data.
*/
static void erase_operation_do(tstr_twi_internal_flash_opr_data* pstr_flash_opr_data)
{
	twi_u32 u32_err_code;

	u32_err_code = NRF_SUCCESS;

	set_flash_state(ERASING_STATE, NO_TRIGGER);

	FLASH_LOG_COMBINED("Flash is Erasing Now!, Page Num = ", pstr_flash_opr_data->uni_opr_type.str_erase_data.u32_page_number);

	u32_err_code = sd_flash_page_erase((uint32_t)(pstr_flash_opr_data->uni_opr_type.str_erase_data.u32_page_number));
	if(NRF_SUCCESS != u32_err_code)
	{
		TESTING_LOG_ERROR("Erase using SoftDevice, SD Error number = %d\n", u32_err_code);
	}

	APP_ERROR_CHECK(u32_err_code);
}

/**
*	@brief		WRITE_WORD operation function that is used to ask the flash module to write a certain word.
*	@param[in]  flash_opr_data 	Pointer to a structure that holds the operation "write_word, write_buffer, erase" and
*																				pointer to the operation related data.
*/
static void write_word_operation_do(tstr_twi_internal_flash_opr_data* pstr_flash_opr_data)
{
	twi_u32 u32_err_code;

	u32_err_code = NRF_SUCCESS;

	set_flash_state(STORING_STATE, NO_TRIGGER);

	gu32_word_wrt = pstr_flash_opr_data->uni_opr_type.str_write_data.uni_data_type.u32_src_data_word;

	FLASH_LOG("Flash is Storing Word Now! %x %d %d\n\n",gu32_word_wrt,pstr_flash_opr_data->uni_opr_type.str_write_data.pu32_flash_add,(pstr_flash_opr_data->uni_opr_type.str_write_data.u16_size));

	u32_err_code = sd_flash_write((pstr_flash_opr_data->uni_opr_type.str_write_data.pu32_flash_add),
								&gu32_word_wrt, (pstr_flash_opr_data->uni_opr_type.str_write_data.u16_size));

	if(NRF_SUCCESS != u32_err_code)
	{
		TESTING_LOG_ERROR("Write word using SoftDevice, SD Error number = %d\n", u32_err_code);
	}

	APP_ERROR_CHECK(u32_err_code);
}

/**
*	@brief		WRITE_BUFFER operation function that is used to ask the flash module to write a certain buffer.
*	@param[in]  flash_opr_data  Pointer to a structure that holds the operation "write_word, write_buffer, erase" and
*																				pointer to the operation related data.
*/
static void write_buffer_operation_do(tstr_twi_internal_flash_opr_data* pstr_flash_opr_data)
{
	twi_u32 u32_err_code;

	u32_err_code = NRF_SUCCESS;

	set_flash_state(STORING_STATE, NO_TRIGGER);

	FLASH_LOG("Flash is Storing Buffer Now! \n\n");

	u32_err_code = sd_flash_write((pstr_flash_opr_data->uni_opr_type.str_write_data.pu32_flash_add),
								(pstr_flash_opr_data->uni_opr_type.str_write_data.uni_data_type.pu32_src_data_add),
										(pstr_flash_opr_data->uni_opr_type.str_write_data.u16_size));

	if(NRF_SUCCESS != u32_err_code)
	{
		TESTING_LOG_ERROR("Write Buffer using SoftDevice, SD Error number = %d\n", u32_err_code);
	}

	APP_ERROR_CHECK(u32_err_code);
}

/**
*	@brief		WRITE_BYTE operation function that is used to ask the flash module to write a certain byte.
*	@param[in]  flash_opr_data  Pointer to a structure that holds the operation
*									 "write_word, write_buffer, erase" and pointer to the operation related data.
*/
static void write_byte_operation_do(tstr_twi_internal_flash_opr_data* pstr_flash_opr_data)
{
	twi_u32 u32_read_word;
	twi_u32 u32_err_code;

	u32_read_word = 0;
	u32_err_code = NRF_SUCCESS;

	set_flash_state(STORING_STATE, NO_TRIGGER);

	FLASH_LOG("Flash is Storing Byte Now! \n\n");

	/* Read the word from the flash, return it in the variable u32_read_word */
	u32_read_word = *((twi_u32*) (pstr_flash_opr_data->uni_opr_type.str_write_data.pu32_flash_add));

	gu32_word_wrt = u32_read_word & pstr_flash_opr_data->uni_opr_type.str_write_data.uni_data_type.u32_src_data_word;

	u32_err_code = sd_flash_write((pstr_flash_opr_data->uni_opr_type.str_write_data.pu32_flash_add), &gu32_word_wrt, 1);

	if(NRF_SUCCESS != u32_err_code)
	{
		TESTING_LOG_ERROR("Write word using SoftDevice, SD Error number = %d\n", u32_err_code);
	}

	APP_ERROR_CHECK(u32_err_code);
}

/**
 *	@brief		This function handle the buffer writing operation (divide the operation into multiple operation If the buffer not aligned as a word)
 *	@param[in]  flash_opr_data  Pointer to a structure that holds the operation of write buffer operation
 */
static void write_buffer_operations_logic(tstr_twi_internal_flash_opr_data* pstr_flash_opr_data)
{
	static tstr_twi_internal_flash_opr_data	str_flash_opr_data;	/* Structure holds the flash operation data */

	if(TWI_FALSE == gb_flash_op_done_success)
	{
		if(WRITE_BYTE_OP == str_flash_opr_data.enu_flash_operation)
		{
			write_byte_operation_do(&str_flash_opr_data);
		}
		else
		{
			write_buffer_operation_do(&str_flash_opr_data);
		}

		gb_flash_op_done_success = TWI_TRUE;
	}
	else
	{
		twi_u16 u16_src_size;
		twi_u16	u16_data_idx;						/* Variable holds the index of the data buffer */

		twi_u32	u32_write_flash_address;			/* Variable holds the flash address want to write in it */

		twi_u8* pu8_src_data;
		/* Not aligned address as word */


		u16_src_size = pstr_flash_opr_data->uni_opr_type.str_write_data.u16_size;
		pu8_src_data = (twi_u8 *) pstr_flash_opr_data->uni_opr_type.str_write_data.uni_data_type.pu32_src_data_add;
		u32_write_flash_address = (twi_u32) pstr_flash_opr_data->uni_opr_type.str_write_data.pu32_flash_add;

		u16_data_idx = 0;

		TWI_MEMSET(&str_flash_opr_data, 0, sizeof(tstr_twi_internal_flash_opr_data));

		if((CHECK_ADDRESS_ALIGNED_AS_WORD(u32_write_flash_address)) || (u16_src_size < WORD_SIZE))
		{
			twi_u32 u32_read_word;						/* Variable used to read the word in it. */
			twi_u32 u32_word_alligned_address;			/* Used to get the word aligned address in it. */

			/* Not aligned address as word  or the remaining data size smaller than one word */
			/* Write byte operation */

			if(1 == u16_src_size)
			{
				/* This is last write operation in the buffer */
				gb_last_buffer_operation = TWI_TRUE;
			}

			u32_read_word = 0;
			u32_word_alligned_address = 0;

			byte_to_alligned_word((twi_u32 *)(u32_write_flash_address), (twi_u8)pu8_src_data[u16_data_idx], &u32_word_alligned_address, &u32_read_word);

			str_flash_opr_data.enu_flash_operation = WRITE_BYTE_OP;													/* Set the operation to Write Byte. */
			str_flash_opr_data.uni_opr_type.str_write_data.pu32_flash_add = (twi_u32 *)u32_word_alligned_address;	/* Set the flash address to save the word to. */
			str_flash_opr_data.uni_opr_type.str_write_data.uni_data_type.u32_src_data_word = u32_read_word;			/* Set the buffer address to save to the flash. */
			str_flash_opr_data.uni_opr_type.str_write_data.u16_size = 1;											/* Set the word size (1 bytes) to be written to the flash. */

			write_byte_operation_do(&str_flash_opr_data);

			u32_write_flash_address++;
			u16_data_idx++;
			u16_src_size--;
		}
		else
		{
			twi_u16	u16_data_size_in_word;				/* Variable holds the data size in word */

			/* Aligned address as word && the remaining data size greater than one word */
			/* Write buffer operation */

			if(u16_src_size > twi_internal_flash_get_min_eraseable_sec())	/* Check for the buffer size is greater than the page size */
			{
				/* The buffer is greater than flash page size, we must divide them into multi-pages */
				u16_data_size_in_word = twi_internal_flash_get_min_eraseable_sec() >> WORD_SHIFT_NUM;
			}
			else
			{
				/* The buffer is lower than flash page size */
				u16_data_size_in_word = u16_src_size >> WORD_SHIFT_NUM;
			}

			if(u16_data_size_in_word << WORD_SHIFT_NUM == u16_src_size)
			{
				/* This is last write operation in the buffer */
				gb_last_buffer_operation = TWI_TRUE;
			}

			if(CHECK_ADDRESS_ALIGNED_AS_WORD((twi_u32)&pu8_src_data[u16_data_idx]))
			{

				twi_u8 * pu8_original_src_buff;
				pu8_original_src_buff = (twi_u8*)pstr_flash_opr_data->uni_opr_type.str_write_data.pu32_src_data_copy;
				/* Not aligned address as word */
				TWI_MEMCPY(pu8_original_src_buff, &pu8_src_data[u16_data_idx], u16_src_size);		/* Re-align the Source buffer */

				pu8_src_data = pu8_original_src_buff;

				u16_data_idx = 0;
			}
			else
			{
				/* Aligned address as word */
				/* Continue the buffer writing */
			}

			str_flash_opr_data.enu_flash_operation = WRITE_BUFFER_OP;																	/* Set the operation to Write Buffer */
			str_flash_opr_data.uni_opr_type.str_write_data.pu32_flash_add =	(twi_u32 *) u32_write_flash_address;						/* Set the flash address to save the buffer to */
			str_flash_opr_data.uni_opr_type.str_write_data.uni_data_type.pu32_src_data_add = (twi_u32*) &pu8_src_data[u16_data_idx];	/* Set the buffer address to save to the flash */
			str_flash_opr_data.uni_opr_type.str_write_data.u16_size = u16_data_size_in_word;											/* Set the buffer size to be written to the flash */

			write_buffer_operation_do(&str_flash_opr_data);

			u32_write_flash_address += (u16_data_size_in_word << WORD_SHIFT_NUM);

			u16_data_idx += (u16_data_size_in_word << WORD_SHIFT_NUM);
			u16_src_size -= (u16_data_size_in_word << WORD_SHIFT_NUM);
		}

		pstr_flash_opr_data->uni_opr_type.str_write_data.u16_size = u16_src_size;
		pstr_flash_opr_data->uni_opr_type.str_write_data.uni_data_type.pu32_src_data_add = (twi_u32*) &pu8_src_data[u16_data_idx];
		pstr_flash_opr_data->uni_opr_type.str_write_data.pu32_flash_add = (twi_u32 *) u32_write_flash_address;
	}
}

/*
 *	@brief	This function used to get flash operation from the flash queue and execute it if the flash is not busy.
 */
static twi_s32 execute_flash_operation(void)
{
	twi_s32	s32_retval;

	if((gstr_flash_queue_handle.enu_flash_state != ERASING_STATE)	&&
	   (gstr_flash_queue_handle.enu_flash_state != STORING_STATE))	/* If the flash is not in progress of a certain command. */
	{
		tstr_twi_internal_flash_opr_data* pstr_flash_opr_data;

		pstr_flash_opr_data = NULL;

		/* The flash is not busy.
			Dequeue a flash command and, Dispatch it */
		s32_retval = flash_opr_get(&pstr_flash_opr_data);
		if(TWI_SUCCESS == s32_retval)
		{
			switch(pstr_flash_opr_data->enu_flash_operation)
			{
				case ERASE_OP:
					/* This is an Erase command, call the erase function */
					erase_operation_do(pstr_flash_opr_data);
					break;
				case WRITE_WORD_OP:
					/* This is a Write word command, call the write word function */
					/* Erasing should be done before using the write operation. */
					write_word_operation_do(pstr_flash_opr_data);
					break;
				case WRITE_BUFFER_OP:
					/* This is a Write buffer command, call the write buffer function */
					/* Erasing should be done before using the write operation. */
					write_buffer_operations_logic(pstr_flash_opr_data);
					break;
				case WRITE_BYTE_OP:
					/* This is a Write byte command, call the write byte Macro */
					write_byte_operation_do(pstr_flash_opr_data);
					break;
				case NO_OP:
					TESTING_LOG_ERROR("*********************************");
					TESTING_LOG_ERROR("No. of free space = %d\n", gstr_flash_queue_handle.u8_num_free_space);
					TESTING_LOG_ERROR("Read IDX = %d\n", gstr_flash_queue_handle.read_index);
					TESTING_LOG_ERROR("Write IDX = %d\n", gstr_flash_queue_handle.write_index);
					TESTING_LOG_ERROR("*********************************");
					break;
				default:
					/* Do Nothing */
				break;
			}
		}
		else
		{
			/* No commands to dispatch, empty queue. Return result as it is "TWI_FLASH_ERROR_GET_EMPTY" */
			s32_retval = TWI_FLASH_ERROR_GET_EMPTY;
		}
	}
	else
	{
		/* The flash is not ready */
		s32_retval = TWI_FLASH_ERROR_DISPATCH_NOT_READY;
	}

	return s32_retval;
}

/**
 *	@brief		This is a high priority block that is executed inside the SWI.
 */
static void dec_num_free_space(void)
{
	gstr_flash_queue_handle.u8_num_free_space--;
}

/**
 *	@brief		Enqueue a flash operation in the flash queue "used for write_word, write_buffer and, erase_page only".
 *  @param[in]  p_flash_opr_data	Pointer to a structure that holds the operation "write_word, write_buffer, erase" and
 *																						pointer to the operation related data.
 *  @return     ::FLASH_PUT_SUCCESS       	If the function succeeded to enqueue a flash operation/event.
 *  @return     ::TWI_FLASH_ERROR_QUEUE_NO_SPACE	In case of not enough space, queue is full!, return this error.
*/
static twi_s32 flash_opr_put(tstr_twi_internal_flash_opr_data * pstr_flash_opr_data)
{
	twi_s32 s32_retval;			/* The return value, declares the put operation result. */

	s32_retval = TWI_SUCCESS;

	/* In case of enough space, put the event in the queue. */
	if(gstr_flash_queue_handle.u8_num_free_space)	/* check for free space in flash queue */
	{
		/* Enqueue the event in the next available queue location. */
		TWI_MEMCPY(&(gstr_flash_queue_handle.astr_flash_queue[gstr_flash_queue_handle.write_index]), pstr_flash_opr_data, sizeof(*pstr_flash_opr_data));
		twi_next_circular_index(&gstr_flash_queue_handle.write_index, FLASH_QUEUE_SIZE); /* Advance the queue write index */
		twi_swi_trigger(PLATFORM_FLASH_HAL_SWI_CHANNEL);
	}
	else
	{
		FLASH_LOG_ERROR("Failed to put the operation in flash queue, queue is full\n");
		TESTING_LOG_ERROR("!!!!Flash Queue Full!!!!");
		s32_retval = TWI_FLASH_ERROR_QUEUE_NO_SPACE;    			/* return with error. */
	}

	execute_flash_operation();

	return s32_retval;
}

/**
 *	@brief		Flash call back function that handles and ensures the finishing of the flash events/operations.
 *						It's being called after the flash module finishes a certain operation.
 *						triggers the flash state from doing something to done!
 *  @param[in]  sys_evt		Indicator from the flash module about the operation.
 *								it will contain one of two values:
 * 									a- "::NRF_EVT_FLASH_OPERATION_SUCCESS", in case of successful operation.
 * 									b- "::NRF_EVT_FLASH_OPERATION_ERROR", in case of operation's failure.
 */
#if defined (nordic_sdk_16_0_0)
static void twi_internal_flash_evt_handler(twi_u32 sys_evt, void * p_context)
#else
static void twi_internal_flash_evt_handler(twi_u32 sys_evt)
#endif
{
	if(TWI_TRUE == gb_is_inited)
	{
		tstr_twi_internal_flash_opr_data* pstr_flash_opr;

		pstr_flash_opr = &(gstr_flash_queue_handle.astr_flash_queue[gstr_flash_queue_handle.read_index]);

		switch(sys_evt)
		{
			case NRF_EVT_FLASH_OPERATION_SUCCESS:	/* The flash operation has finished successfully! */
			{
				if((WRITE_BUFFER_OP != pstr_flash_opr->enu_flash_operation)	||
						((WRITE_BUFFER_OP == pstr_flash_opr->enu_flash_operation) && (TWI_TRUE == gb_last_buffer_operation)))
				{
					twi_next_circular_index(&gstr_flash_queue_handle.read_index, FLASH_QUEUE_SIZE); /* Advance the queue read index */

					gstr_flash_queue_handle.u8_num_free_space++;
					if((NULL != pstr_flash_opr->pf_flash_op_cb) &&
							((STORING_STATE == gstr_flash_queue_handle.enu_flash_state) || ((ERASING_STATE == gstr_flash_queue_handle.enu_flash_state))))
					{
						tstr_flash_cb_param str_cb;
						str_cb.enu_flash_type = TWI_INTERNAL_FLASH;
						if(pstr_flash_opr->str_cb_param.enu_flash_op_done == TWI_FLASH_ERASE_OP_DONE)
						{
							str_cb.enu_flash_op_done = TWI_FLASH_ERASE_DONE;
						}
						else
						{
							str_cb.enu_flash_op_done = TWI_FLASH_WRITE_DONE;

						}

						pstr_flash_opr->pf_flash_op_cb(&str_cb, pstr_flash_opr->pv_user_cb_data);
					}

					pstr_flash_opr->enu_flash_operation = NO_OP;						/* Delete the event after executing it. */

					gb_last_buffer_operation = TWI_FALSE;
				}

				set_flash_state(gstr_flash_queue_handle.enu_flash_state, TRIGGER);		/* Trigger the state to Done! */

				FLASH_LOG("Flash Operation is Done!\n\n");
			}
				break;
			case NRF_EVT_FLASH_OPERATION_ERROR:		/* The flash operation has finished unsuccessfully! */
			{
				if(WRITE_BUFFER_OP == pstr_flash_opr->enu_flash_operation)
				{
					gb_flash_op_done_success = TWI_FALSE;
				}

				set_flash_state(gstr_flash_queue_handle.enu_flash_state, TRIGGER);		/* Trigger the state to Done! */

				FLASH_LOG_ERROR("Flash Operation Error!\n\n");
			}
				break;
			default:
				/* Do Nothing */
				break;
		}

		execute_flash_operation();
	}
}

/*-***********************************************************/
/*- APIs IMPLEMENTATION -------------------------------------*/
/*-***********************************************************/

/*
 *	@brief		API used for initializing the flash HAL module.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_internal_flash_init(void)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	if(TWI_FALSE == gb_is_inited)
	{
#if defined (nordic_sdk_16_0_0)
		NRF_SDH_SOC_OBSERVER(m_soc_observer, APP_SOC_OBSERVER_PRIO, twi_internal_flash_evt_handler, NULL);
#else
		s32_retval = softdevice_sys_evt_handler_set(twi_internal_flash_evt_handler);
#endif		
		if(s32_retval == TWI_SUCCESS)
		{
			s32_retval = twi_swi_init(PLATFORM_FLASH_HAL_SWI_CHANNEL, TWI_SWI_HIGH_PRIORITY, dec_num_free_space);
			if(TWI_SUCCESS == s32_retval)
			{
				gb_is_inited = TWI_TRUE;
			}
			else
			{
				TESTING_LOG_ERROR("ERROR: Flash SWI Init Failure\n");
				FLASH_LOG_ERROR("ERROR: Flash SWI Init Failure\n");
			}
		}
		else
		{
			TESTING_LOG_ERROR("ERROR: Flash Init Failure\n");
			FLASH_LOG_ERROR ("ERROR: Flash Init Failure\n");
		}
	}

	return s32_retval;
}

/*
 *	@brief		API used for de-initializing the flash HAL module.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_internal_flash_deinit(void)
{
	twi_s32 s32_retval;
	
	s32_retval = TWI_SUCCESS;
	
	if(TWI_TRUE == gb_is_inited)
	{
		s32_retval = twi_swi_deinit(PLATFORM_FLASH_HAL_SWI_CHANNEL);
		if(TWI_SUCCESS == s32_retval)
		{
			gb_is_inited = TWI_FALSE;
		}
	}
	
	return s32_retval;
}

/*
 *	@brief		API used for getting the base address of flash HAL module.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_u32 twi_internal_flash_get_base_addr(void)
{
	return ((FREE_SPACE_CODE_DATA + ((twi_u32) END_CODE_ADDRESS)) + FLASH_DATA_SECTION_SIZE);
}

/*
 *    @brief      Flash erase function that registers for an erase event/operation in the flash queue.
 */
twi_u32 twi_internal_flash_get_min_eraseable_sec(void)
{
    return INTERNAL_FLASH_PAGE_SIZE;
}

/*
 *	@brief		API used for getting the size of the allowed flash.
 *  @return   	The size of the internal flash in bytes
 */
twi_u32 twi_internal_flash_get_size(void)
{
	return INTERNAL_FLASH_END_ADDRESS - twi_internal_flash_get_base_addr();
}

/*
 *	@brief		Flash erase function that registers for an erase event/operation in the flash queue.
 *	@param[in]  page_number		The page number to be erased.
 *	@param[in] 	pf_erase_op_cb	Pointer to call back function called when the erase operation in the flash end.
 *	@param[in]	pv_user_cb_data	Void pointer holds user data need to pass through flash CB
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_internal_flash_erase(twi_u32 u32_page_number, tpf_twi_flash_cb pf_erase_op_cb, void* pv_user_cb_data)
{
	twi_s32	s32_retval;

	s32_retval = TWI_SUCCESS;

	if(TWI_TRUE == gb_is_inited)
	{
		tstr_twi_internal_flash_opr_data str_flash_opr_data;

		TWI_MEMSET(&str_flash_opr_data, 0, sizeof(tstr_twi_internal_flash_opr_data));

		str_flash_opr_data.enu_flash_operation = ERASE_OP;									/* Set the operation to Erase */
		str_flash_opr_data.uni_opr_type.str_erase_data.u32_page_number = u32_page_number;	/* Set the page to be erased */

		if(NULL != pf_erase_op_cb)	/* Set the call back parameters */
		{
			str_flash_opr_data.pf_flash_op_cb = pf_erase_op_cb;
			str_flash_opr_data.pv_user_cb_data = pv_user_cb_data;

			str_flash_opr_data.str_cb_param.enu_flash_op_done = TWI_FLASH_ERASE_OP_DONE;
		}

		s32_retval = flash_opr_put(&str_flash_opr_data);			/* Enqueue the flash erase event in the flash queue */
	}
	else
	{
		s32_retval = TWI_ERROR_NOT_INITIALIZED;
	}

	return s32_retval;
}

/*
 *	@brief		Flash write_byte function that registers for an write_byte event/operation in the flash queue.
 *
 *	@param[in]  pu32_dst			Pointer to the flash, "destination", address to save the data byte to.
 *	@param[in]  u8_src_byte 		The data byte to be saved in the flash.
 *	@param[in] 	pf_write_byte_op_cb	Pointer to call back function called when the write operation in the flash end.
 *	@param[in]	pv_user_cb_data		Void pointer holds user data need to pass through flash CB
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 *	@note 		You must erase the destination address before writing operation.
*/
twi_s32 twi_internal_flash_write_byte(twi_u32 * pu32_dst, twi_u8 u8_src_byte, tpf_twi_flash_cb pf_write_byte_op_cb, void* pv_user_cb_data)
{
	twi_s32	s32_retval;
	
	s32_retval = TWI_SUCCESS;
	if(TWI_TRUE == gb_is_inited)
	{
		twi_u32 u32_read_word;						/* Variable used to read the word in it. */
		twi_u32 u32_word_alligned_address;			/* Used to get the word aligned address in it. */

		tstr_twi_internal_flash_opr_data	str_flash_opr_data;

		u32_read_word = 0;
		u32_word_alligned_address = 0;


		TWI_MEMSET(&str_flash_opr_data, 0, sizeof(tstr_twi_internal_flash_opr_data));

		byte_to_alligned_word(pu32_dst, u8_src_byte, &u32_word_alligned_address, &u32_read_word);

		str_flash_opr_data.enu_flash_operation = WRITE_BYTE_OP;													/* Set the operation to Write Byte. */
		str_flash_opr_data.uni_opr_type.str_write_data.pu32_flash_add = (twi_u32 *)u32_word_alligned_address;	/* Set the flash address to save the word to. */
		str_flash_opr_data.uni_opr_type.str_write_data.uni_data_type.u32_src_data_word = u32_read_word;			/* Set the buffer address to save to the flash. */
		str_flash_opr_data.uni_opr_type.str_write_data.u16_size = 1;											/* Set the word size (1 bytes) to be written to the flash. */

		if(NULL != pf_write_byte_op_cb)	/* Set the call back parameters */
		{
			str_flash_opr_data.pf_flash_op_cb = pf_write_byte_op_cb;
			str_flash_opr_data.pv_user_cb_data = pv_user_cb_data;

			str_flash_opr_data.str_cb_param.enu_flash_op_done = TWI_FLASH_WRITE_BYTE_OP_DONE;
		}

		s32_retval = flash_opr_put(&str_flash_opr_data);				/* Enqueue the flash write event in the flash queue. */
	}
	else
	{
		s32_retval = TWI_ERROR_NOT_INITIALIZED;
	}

	return s32_retval;												/* Return the result, if the event is enqueued or not! */
}

/*
 *	@brief		Flash write_word function that registers for an write_word event/operation in the flash queue.
 *	@param[in]  pu32_dst			Pointer to the flash, "destination", address to save the data word to.
 *	@param[in]  u32_src_word		The data word, "4 bytes", to be saved to the flash.
 *	@param[in] 	pf_write_word_op_cb	Pointer to call back function called when the write operation in the flash end.
 *	@param[in]	pv_user_cb_data		Void pointer holds user data need to pass through flash CB.
 *   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 *	@note 		You must erase the destination address before writing operation.
*/
twi_s32 twi_internal_flash_write_word(twi_u32 * pu32_dst, twi_u32  u32_src_word, tpf_twi_flash_cb pf_write_word_op_cb, void* pv_user_cb_data)
{
	twi_s32	s32_retval;

	s32_retval = TWI_SUCCESS;

	if(TWI_TRUE == gb_is_inited)
	{
		tstr_twi_internal_flash_opr_data   str_flash_opr_data;

		TWI_MEMSET(&str_flash_opr_data, 0, sizeof(tstr_twi_internal_flash_opr_data));

		str_flash_opr_data.enu_flash_operation = WRITE_WORD_OP;										/* Set the operation to Write WORD. */
		str_flash_opr_data.uni_opr_type.str_write_data.pu32_flash_add = pu32_dst;	 					/* Set the flash address to save the word to. */
		str_flash_opr_data.uni_opr_type.str_write_data.uni_data_type.u32_src_data_word = u32_src_word;	/* Set the buffer address to save to the flash. */
		str_flash_opr_data.uni_opr_type.str_write_data.u16_size = 1;								/* Set the word size (4 bytes) to be written to the flash. */


		if(NULL != pf_write_word_op_cb)	/* Set the call back parameters */
		{
			str_flash_opr_data.pf_flash_op_cb = pf_write_word_op_cb;
			str_flash_opr_data.pv_user_cb_data = pv_user_cb_data;

			str_flash_opr_data.str_cb_param.enu_flash_op_done = TWI_FLASH_WRITE_WORD_OP_DONE;
		}

		s32_retval = flash_opr_put(&str_flash_opr_data);											/* Enqueue the flash write event in the flash queue. */
	}
	else
	{
		s32_retval = TWI_ERROR_NOT_INITIALIZED;
	}

	return s32_retval;																			/* Return the result, if the event is enqueued or not! */
}

/*
 *	@brief		Flash write buffer function that registers for an write buffer event/operation in the flash queue.
 *  @param[in]  pu32_dst_address	Pointer to the flash, "destination", address to save the data to.
 *  @param[in]  pu8_src_data		Pointer to the data, "source", address to be saved to the flash. (Must be aligned)
 *  								(USER MUST save this data until the operation is done, May be edit in this buffer).
 *  @param[in]  u16_src_size		The data buffer size in bytes.
 *  @param[in] 	pf_write_buff_op_cb	Pointer to call back function called when the write operation in the flash end.
 *	@param[in]	pv_user_cb_data		Void pointer holds user data need to pass through flash CB.
 *  @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 *	@note 		You must erase the destination address before writing operation.
 */
twi_s32 twi_internal_flash_write_buffer(twi_u32 * pu32_dst_address, twi_u8 * pu8_src_data, twi_u16 u16_src_size, tpf_twi_flash_cb pf_write_buff_op_cb, void* pv_user_cb_data)
{
	twi_s32	s32_retval;

	s32_retval = TWI_SUCCESS;

	if(TWI_TRUE == gb_is_inited)
	{
		if((NULL != pu32_dst_address) && (NULL != pu8_src_data) && (0 < u16_src_size) && !(CHECK_ADDRESS_ALIGNED_AS_WORD((twi_u32) pu8_src_data)))
		{
			tstr_twi_internal_flash_opr_data   str_flash_opr_data;
			TWI_MEMSET(&str_flash_opr_data, 0, sizeof(tstr_twi_internal_flash_opr_data));

			str_flash_opr_data.enu_flash_operation = WRITE_BUFFER_OP;													/* Set the operation to Write Buffer */
			str_flash_opr_data.uni_opr_type.str_write_data.pu32_flash_add =	(twi_u32 *) pu32_dst_address;				/* Set the flash address to save the buffer to */
			str_flash_opr_data.uni_opr_type.str_write_data.uni_data_type.pu32_src_data_add = (twi_u32*) pu8_src_data;	/* Set the buffer address to save to the flash */
			str_flash_opr_data.uni_opr_type.str_write_data.pu32_src_data_copy = (twi_u32*) pu8_src_data;
			str_flash_opr_data.uni_opr_type.str_write_data.u16_size = u16_src_size;


			if(NULL != pf_write_buff_op_cb)				/* Set the call back parameters */
			{
				str_flash_opr_data.pf_flash_op_cb = pf_write_buff_op_cb;
				str_flash_opr_data.pv_user_cb_data = pv_user_cb_data;

				str_flash_opr_data.str_cb_param.enu_flash_op_done = TWI_FLASH_WRITE_BUFFER_OP_DONE;
			}

			s32_retval = flash_opr_put(&str_flash_opr_data);											/* Enqueue the flash write event in the flash queue. */
		}
		else
		{
			s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
		}
	}
	else
	{
		s32_retval = TWI_ERROR_NOT_INITIALIZED;
	}

	return s32_retval;
}

/*
 *	@brief		Flash operations dispatcher that is responsible for handling the events/operations saved in the flash queue in order.
 *
 *  @return     FLASH_DISPATCH_SUCCESS		In case of successful event dispatching.
 *  @return     FLASH_ERROR_GET_EMPTY		In case of empty queue, return error.
 *  @return     FLASH_DISPATCH_FAILED		In case of that, the flash module is busy, return error.
 *
 */
twi_s32 twi_internal_flash_dispatch(void)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;
	if(TWI_TRUE == gb_is_inited)
	{
		twi_s32 s32_execute_retval;

		s32_execute_retval	= TWI_SUCCESS;

		s32_execute_retval = execute_flash_operation();
		if(TWI_FLASH_ERROR_GET_EMPTY == s32_execute_retval)
		{
			s32_retval = TWI_SUCCESS;
		}
		else
		{
#if 0
			TESTING_LOG_COMBINED("QUEUE SIZE :: ", FLASH_QUEUE_SIZE - gstr_flash_queue_handle.u8_num_free_space);
#endif
		}
	}

	return s32_retval;
}
/*
 *	@brief		Flash read function that reads directly a certain data corresponds to a certain address
 *							from the flash memory without registering for a queue event!
 *  @param[in]  u32_flash_addr	The flash data location to read the data from.
 *  @param[in]  pu8_read_buffer	Pointer to the buffer to load the flash data into.
 *  @param[in]  u32_read_size	The size of the data needed to be read.
 *	@return		::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 
*/
twi_s32 twi_internal_flash_read(twi_u32 u32_flash_addr, twi_u8* pu8_read_buffer, twi_u32 u32_read_size)
{
	twi_s32	s32_retval;

	s32_retval = TWI_SUCCESS;
	
	if(TWI_TRUE == gb_is_inited)
	{
		if((u32_flash_addr >= (twi_u32) twi_internal_flash_get_base_addr()) &&
				((u32_flash_addr + u32_read_size) <= (twi_internal_flash_get_base_addr() + twi_internal_flash_get_size())) &&
				(NULL != pu8_read_buffer) && (0 < u32_read_size))
		{
			TWI_MEMCPY(pu8_read_buffer, (twi_u8*) u32_flash_addr, u32_read_size);
		}
		else
		{
			s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
		}
	}
	else
	{
		s32_retval = TWI_ERROR_NOT_INITIALIZED;
	}
	
	return s32_retval;
}

/*
 *	@brief		Function that maps the page address to page number
 *  @param[in]  u32_page_addr	the page address that needs to be maped to page number.
 *
 *	@return		the page number starting from 0 at the flash start.
*/
twi_u32 twi_internal_flash_get_page_num_from_addr(twi_u32 u32_page_addr)
{
	return (((twi_u32) (u32_page_addr)) >> INTERNAL_FLASH_PAGE_SIZE_SHIFT);
}

/*
*   @brief      This is a function that protect the meory from SWD Read/Write/Erase.
*	@return		::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
*/
twi_s32 twi_flash_protect(void)
{
	twi_s32 s32_retval;
	
	s32_retval = TWI_SUCCESS;
	
	return s32_retval;
}

/*
*   @brief      This is a function that gets memory protection status.
*   @param[out] pb_protected      Memory is protected.
*	@return		::TWI_SUCCESS in case of success, otherwise, refer to @ref twi_retval.h.
*/
twi_s32 twi_flash_protect_status(twi_bool *pb_protected)
{
	twi_s32 s32_retval;
	
	s32_retval = TWI_SUCCESS;
	if(NULL != pb_protected)
	{
		*pb_protected = TWI_FALSE;
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	}

	return s32_retval;
}
