/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file		twi_common.h
 ** @brief		This file includes the common macros/fns that can be used in the whole system.
 **
 */

 /** @defgroup TWI_COMMON_group TWI Common Functions
 * @{
 */
 
#ifndef TWI_COMMON_H__
#define TWI_COMMON_H__

/*-*********************************************************/
/*- INCLUDES ----------------------------------------------*/
/*-*********************************************************/ 
#include <string.h>
#include "twi_types.h"
#include "twi_retval.h"
#include "twi_debug.h"
#include "platform_defines.h"
#include "twi_compiler.h"

/*-*********************************************************/
/*- FUNCTION-LIKE MACROS ----------------------------------*/
/*-*********************************************************/



#define TWI_ERROR_BREAK(s32_error)													\
																					\
		if(TWI_SUCCESS != (s32_error))												\
		{																			\
			TWI_LOGGER_ERR("%d \r\n",s32_error);																	\
			break;																	\
		}			

/**
	Retrieve bytes from the given word
*/

#define TWI_BYTE_0(word)   					((twi_u8)(((word) >> 0 	) & 0x000000FFUL))
#define TWI_BYTE_1(word)  	 				((twi_u8)(((word) >> 8 	) & 0x000000FFUL))
#define TWI_BYTE_2(word)   					((twi_u8)(((word) >> 16  ) & 0x000000FFUL))
#define TWI_BYTE_3(word)   					((twi_u8)(((word) >> 24  ) & 0x000000FFUL))


#define SHORT_LOW(word)   					((twi_u16)(((word) >> 0 	) & 0x0000FFFFUL))
#define SHORT_HIGH(word)  	 				((twi_u16)(((word) >> 16 ) & 0x0000FFFFUL))
/*!<
	Retrieve 2 bytes from the given buffer at the given
	offset as 16-bit unsigned integer in the Network byte order.
*/

#define GETU16B(BUF,OFFSET)				((((twi_u16)((BUF)[OFFSET]) << 8)) |(((twi_u16)(BUF)[OFFSET + 1])))

#define GETU16L(BUF,OFFSET)				((((twi_u16)((BUF)[OFFSET + 1]) << 8)) |(((twi_u16)(BUF)[OFFSET])))


/*!<
	SET 2 bytes from the given value to the given buffer
	offset as 32-bit unsigned integer in the Network byte order.
*/

#define SETU16B(BUF,OFFSET,VALUE)                        \
	(BUF)[0 + OFFSET]  = (twi_u8) (((VALUE) >> 8) & 0xFF); \
	(BUF)[1 + OFFSET]  = (twi_u8) (((VALUE) >> 0) & 0xFF)

#define SETU16L(BUF,OFFSET,VALUE)                		 \
	(BUF)[0 + OFFSET]  = (twi_u8) (((VALUE) >> 0) & 0xFF); \
	(BUF)[1 + OFFSET]  = (twi_u8) (((VALUE) >> 8) & 0xFF)

/*!<
 Retrieve 8 bytes from the given buffer at the given
 offset as 64-bit unsigned integer in the Network byte order.
 */

#define GETU64B(BUF,OFFSET)				((((twi_u64)((BUF)[OFFSET]) << 56)) | (((twi_u64)((BUF)[OFFSET + 1]) << 48)) | \
										((((twi_u64)((BUF)[OFFSET+2]) << 40)) | (((twi_u64)((BUF)[OFFSET + 3]) << 32)) | \
										((((twi_u64)((BUF)[OFFSET+4]) << 24)) | (((twi_u64)((BUF)[OFFSET + 5]) << 16)) | \
										(((twi_u64)((BUF)[OFFSET +6]) << 8)) | ((twi_u64)((BUF)[OFFSET + 7])))))

/*!<
	Retrieve 4 bytes from the given buffer at the given
	offset as 32-bit unsigned integer in the Network byte order.
*/

#define GETU32B(BUF,OFFSET)				((((twi_u32)((BUF)[OFFSET]) << 24)) | (((twi_u32)((BUF)[OFFSET + 1]) << 16)) | \
										(((twi_u32)((BUF)[OFFSET + 2]) << 8)) | ((twi_u32)((BUF)[OFFSET + 3])))
										
#define GETU32L(BUF,OFFSET)				((((twi_u32)((BUF)[OFFSET + 3]) << 24)) | (((twi_u32)((BUF)[OFFSET + 2]) << 16)) | \
										(((twi_u32)((BUF)[OFFSET + 1]) << 8)) | ((twi_u32)((BUF)[OFFSET])))
/*!<
 SET 8 bytes from the given value to the given buffer
 offset as 64-bit unsigned integer in the Network byte order.
 */
#define SETU64B(BUF,OFFSET,VALUE)                         \
	(BUF)[0 + OFFSET]  = (twi_u8) (((VALUE) >> 56) & 0xFF); \
	(BUF)[1 + OFFSET]  = (twi_u8) (((VALUE) >> 48) & 0xFF); \
	(BUF)[2 + OFFSET]  = (twi_u8) (((VALUE) >> 40 )& 0xFF); \
	(BUF)[3 + OFFSET]  = (twi_u8) (((VALUE) >> 32 )& 0xFF); \
	(BUF)[4 + OFFSET]  = (twi_u8) (((VALUE) >> 24) & 0xFF); \
	(BUF)[5 + OFFSET]  = (twi_u8) (((VALUE) >> 16) & 0xFF); \
	(BUF)[6 + OFFSET]  = (twi_u8) (((VALUE) >> 8 ) & 0xFF); \
	(BUF)[7 + OFFSET]  = (twi_u8) (((VALUE) >> 0 ) & 0xFF)

/*!<
	SET 4 bytes from the given value to the given buffer
	offset as 32-bit unsigned integer in the Network byte order.
*/

#define SETU32B(BUF,OFFSET,VALUE)                         \
	(BUF)[0 + OFFSET]  = (twi_u8) (((VALUE) >> 24) & 0xFF); \
	(BUF)[1 + OFFSET]  = (twi_u8) (((VALUE) >> 16) & 0xFF); \
	(BUF)[2 + OFFSET]  = (twi_u8) (((VALUE) >> 8 ) & 0xFF); \
	(BUF)[3 + OFFSET]  = (twi_u8) (((VALUE) >> 0 ) & 0xFF)

#define SETU32L(BUF,OFFSET,VALUE)                		  \
	(BUF)[0 + OFFSET]  = (twi_u8) (((VALUE) >> 0 ) & 0xFF); \
	(BUF)[1 + OFFSET]  = (twi_u8) (((VALUE) >> 8 ) & 0xFF); \
	(BUF)[2 + OFFSET]  = (twi_u8) (((VALUE) >> 16) & 0xFF); \
	(BUF)[3 + OFFSET]  = (twi_u8) (((VALUE) >> 24) & 0xFF)
/*!<
	convert 4/2 bytes from big endian to little endian
*/

#define BTOL32(x) ( 			  \
			(((x) & 0x000000FF) << 24)  + \
			(((x) & 0x0000FF00) << 8)   + \
			(((x) & 0x00FF0000) >> 8)   + \
			(((x) & 0xFF000000) >> 24))

#define BTOL16(x) ( 				\
					(((x) & 0x00FF) << 8) + \
					(((x) & 0xFF00) >> 8))
					/*!<
	convert Host to Network format
*/
					
#define NTOHS(x)		BTOL16(x)
#define NTOHL(x)		BTOL32(x)					

/*!<
 convert 8/4/2 bytes from little endian to Big endian
 */
#define LTOB64(x) ( 			  \
			(((x) & 0x00000000000000FF) << 56)  + \
			(((x) & 0x000000000000FF00) << 40)  + \
			(((x) & 0x0000000000FF0000) << 24)  + \
			(((x) & 0x00000000FF000000) << 8)  + \
			(((x) & 0x000000FF00000000) >> 8)  + \
			(((x) & 0x0000FF0000000000) >> 24)  + \
			(((x) & 0x00FF000000000000) >> 40)  + \
			(((x) & 0xFF00000000000000) >> 56))

#define LTOB32(x) ( 			  \
			(((x) & 0x000000FF) << 24)  + \
			(((x) & 0x0000FF00) << 8)   + \
			(((x) & 0x00FF0000) >> 8)   + \
			(((x) & 0xFF000000) >> 24))

#define LTOB16(x) ( 				\
					(((x) & 0x00FF) << 8) + \
					(((x) & 0xFF00) >> 8))
					
/*!<
	convert Host to Network format 
*/
#define HTONS(x)		LTOB16(x)
#define HTONL(x)		LTOB32(x)
#define HTOND(x)		LTOB64(x)
/**
 *	@brief			This macro is used when we are in the development phase only.
 *
*/
#if defined(TWI_UNIT_TEST) || defined(TWI_CEEDLING_TEST) || defined(STACK_PROFILING_ENABLED)
/*
 *  @brief			This macro is used to make the internal fn of any module not a private one,
 *					so that any unit test code can call it without building errors.
 */
	#define TWI_STATIC_FN
#else
	#define TWI_STATIC_FN					static
#endif



static __inline void TWI_SYS_HALT_FUNC  (void) {TWI_LOGGER_ERR("\t\nSYSTEM HALTED");}

#ifdef TWI_CEEDLING_TEST
#define TWI_SYS_HALT()        	do{\
									TWI_SYS_HALT_FUNC();\
                                    while(0);\
								  }while(0)
#else
#define TWI_SYS_HALT()        	do{\
									TWI_SYS_HALT_FUNC();\
                                    while(1);\
								  }while(0)
#endif
/*
 * @brief	The ASSERT functionality prints function name and line number in case of error and HALT the system
 *			In case of release: It prints function name and line number then reset the system
 */
#ifdef TWI_CEEDLING_TEST    
#define TWI_ASSERT(b_cond)       do{\
                                    if(!(b_cond))\
                                    {\
                                        assert(TWI_FALSE);\
                                    }\
                                   }while(0)									
#else
/*lint required while loop and the if condition to avoid lint warnning */    
#define TWI_ASSERT(b_cond)       do{\
                                    if(!(b_cond))\
                                    {\
                                        twi_assert((const twi_s8*)TWI_FUNCTION,(twi_u32)TWI_LINE,TWI_FALSE);\
                                        while(1);\
                                    }\
                                   }while(0)
#endif									   

/**
 *	@brief			Bit mask macro used to create a tmp variable that will be all zeros except the input bit location, used in masking.
 *  @param[in]  	u32_bit_num	:	The bit location needed to be only one.
*/
#define BIT_MASK(u32_bit_num)           (1UL << (u32_bit_num))

/**
 *	@brief		MACRO used to calculate the address of new module want to be saved based
 *					on the based address and the length of the last save operation.
 *	@param[in]	u32_base_addr	Last module saved base address (Must be aligned Address).
 *	@param[in]	u16_len			Last module saved size.
 *	@return		New address for the next module to save in.
 */
#define CALC_NEW_ALIGNED_ADDR(u32_base_addr, u16_len)	((u32_base_addr + u16_len) + \
														((CHECK_AS_WORD_ALIGNED(u16_len)) ? (WORD_SIZE - CHECK_AS_WORD_ALIGNED(u16_len)): 0))

/**
 *	@brief			Get bit status macro used to get value of a certain bit in a register/variable.
 *  @param[in]  	u32_var			:   The input variable/register.
 *  @param[in]  	u8_bit_number	:   The needed bit to be get in the variable/register.
*/
#define GET_BIT_STATUS(u32_var, u8_bit_number)	(0UL != ((u32_var) & (1UL<<(u8_bit_number))))

/**
 *	@brief			Set bit macro used to set a certain bit in a register/variable.
 *  @param[in]  	u32_var			:   The input variable/register.
 *  @param[in]  	u8_bit_number	:   The needed bit to be set in the variable/register.
 *
*/
#define TWI_SET_BIT(u32_var, u8_bit_number) (u32_var) |= (1UL << (u8_bit_number))

/**
 *	@brief			Clear bit macro used to clear a certain bit in a register/variable.
 *  @param[in]  	u32_var			:   The input variable/register.
 *  @param[in]  	u8_bit_number	:   The needed bit to be cleared in the variable/register.
*/
#define TWI_CLR_BIT(u32_var, u8_bit_number) (u32_var) &= (~(1UL << (u8_bit_number)))

/**
 *	@brief			Toggle bit macro used to toggle a certain bit in a register/variable.
 *  @param[in]  	u32_var			:   The input variable/register.
 *  @param[in]  	u8_bit_number	:   The needed bit to be toggled in the variable/register.
*/
#define TWI_TOG_BIT(u32_var, u8_bit_number) (u32_var) ^= (1UL << (u8_bit_number))\

/**
 *	@brief			Assign bit macro used to assign a certain value to a certain bit in a register/variable.
 *  @param[in]  	u32_var			:   The input variable/register.
 *  @param[in]  	u8_bit_number	:   The needed bit to be cleared in the variable/register.
 *  @param[in]  	b_bit_val		:   The value to be assigned to the bit. It is either 0 or 1.
*/
#define TWI_ASSIGN_BIT(u32_var, u8_bit_number, b_bit_val) (u32_var) = (((u32_var) & (~(1UL << (u8_bit_number)))) | (((b_bit_val) & 1UL) << (u8_bit_number)))

/**
 *	@brief			Check if the given variable is an even variable.
 *
 *  @param[in]  	u32_var			:   The input variable/register. 
 *
*/
#define IS_EVEN(u32_var)	(0 == GET_BIT_STATUS(u32_var, 0))

/**
 *	@brief			Check if the given variable is an odd variable.
 *
 *  @param[in]  	u32_var			:   The input variable/register. 
 *
*/
#define IS_ODD(u32_var)	(1 == GET_BIT_STATUS(u32_var, 0))

/**
 *	@brief			Macro used to get the byte of a certain 32-bit value/register.
 *  @param[in]  	u32_var			:The input variable/register.
 *  @param[in]  	u8_byte_number	:The Byte index.
*/
#define GET_BYTE_STATUS(u32_var, u8_byte_number) (((u32_var) & (0xFFUL << ((u8_byte_number & 0x03) << 3))) >> ((u8_byte_number) << 3))
/**
 *	@brief			Macro used to get the most significant byte of a certain 16-bit value/register.
 *  @param[in]  	REG			:   The input variable/register.
*/
//lint -emacro(572,MOST_SIG_BYTE) // Suppress warning 572 "Excessive shift value"
#define MOST_SIG_BYTE(REG) (((REG) & 0xFF00) >> 8)

/**
 *	@brief			Macro used to get the least significant byte of a certain 16-bit value/register.
 *  @param[in]  	REG			:   The input variable/register.
*/
#define LEAST_SIG_BYTE(REG) ((REG) & 0xFF)

/**
 *	@brief			Macro used to concatenate two bytes in 16-bit.
 *  @param[in]  	MSB			:   The needed byte which needed to push in MSB.
 *  @param[in]  	LSB			:   The needed byte which needed to push in LSB.
*/
#define TWO_BYTE_CONCAT(MSB,LSB) ( ( ( MSB << 8 ) | ( 0x00FF ) ) & ( ( 0xFF00 ) | LSB ) )


/**
 *	@brief			Macro used to concatenate two 16-bit in 32-bit.
 *  @param[in]  	MSB			:   The needed byte which needed to push in MSB.
 *  @param[in]  	LSB			:   The needed byte which needed to push in LSB.
*/
#define TWO_16BITS_CONCAT(MSB,LSB) ( ( (twi_u32)( (MSB) << 16 ) | ( 0x0000FFFF ) ) & ( ( 0xFFFF0000 ) | (twi_u32)(LSB) ) )

/**
*	@brief			Macro used to swap the endianess of 16-bits value (reverse the byte order)
*   @param[in]  	REG	:   The input variable/register.
*/
#define SWAP_2_BYTES_ENDIANS(REG)	((MOST_SIG_BYTE(REG)) | ((LEAST_SIG_BYTE(REG))<<8))

/**
 *	@brief			MUL10(x), macro that is used to multiply input number to 10.
 *  @param[in]  	VAR			:   The input variable/number.
*/
#define MUL10(VAR)	((((twi_u32)(VAR))<<1) + (((twi_u32)(VAR))<<3))
#define MUL10_64(VAR)	((((twi_u64)(VAR))<<1) + (((twi_u64)(VAR))<<3))

/**
 *	@brief			MUL100(x), macro that is used to multiply input number to 100.
 *  @param[in]  	VAR			:   The input variable/number.
*/
#define MUL100(VAR)	((((twi_u32)(VAR))<<2) + (((twi_u32)(VAR))<<5) + (((twi_u32)(VAR))<<6))

/**
 *	@brief			MUL1000(x), macro that is used to multiply input number to 1000.
 *  @param[in]  	VAR			:   The input variable/number.
*/
#define MUL1000(VAR)	((((twi_u64)(VAR))<<10) - (((twi_u64)(VAR))<<4) - (((twi_u64)(VAR))<<3))

/**
*	@brief		IS_NUMBER(VAR), macro that is used to check if the given character is a number.
*  @param[in]  	VAR		:   The input character.
*/
#define IS_NUMBER(VAR)	(((VAR) == '0') || ((VAR) == '1') || ((VAR) == '2') || ((VAR) == '3') || ((VAR) == '4') ||  \
                         ((VAR) == '5') || ((VAR) == '6') || ((VAR) == '7') || ((VAR) == '8') || ((VAR) == '9'))

/**
 *	@brief			Macro that copies the data at source "src" to destination "dst".
 *  @param[in]  	dst			:   Pointer to the destination.
 *  @param[in]  	src			:   Pointer to the source.
 *  @param[in]  	sz			:   number of bytes to be copied
*/
#define TWI_MEMCPY(dst,src,sz)          (twi_mem_cpy((twi_u8*)(dst), (twi_u8*)(src), (twi_u16)(sz)))

/**
 *	@brief			Macro that invert the data at source "src" to destination "dst".
 *  @param[in]  	dst			:   Pointer to the destination.
 *  @param[in]  	src			:   Pointer to the source.
 *  @param[in]  	sz			:   number of bytes to be copied
*/
#define TWI_INVERT_ADD(dst,src,sz)      (twi_invert_add((twi_u8*)(dst), (twi_u8*)(src), (twi_u32)(sz)))
/**
 *	@brief			Macro that copies the data at source "src" to destination "dst". Support source/destination overlapping.
 *  @param[in]  	dst			:   Pointer to the destination.
 *  @param[in]  	src			:   Pointer to the source.
 *  @param[in]  	sz			:   number of bytes to be copied
*/
#define TWI_MEMMOVE(dst,src,sz)          (memmove((twi_u8*)(dst), (twi_u8*)(src), (twi_u16)(sz)))

/**
 *	@brief			Macro that sets "dst" with the value "val"
 *  @param[in]  	dst			:   pointer to destination.
 *  @param[in]  	val			:   value.
 *  @param[in]  	sz			:   Size of Value in Bytes.
*/
#define TWI_MEMSET(dst,val,sz)          (twi_mem_set((twi_u8*)(dst), (twi_u8)(val), (twi_u16)(sz)))

/**
 *	@brief			Macro that Compares the data at source and destination.
 *  @param[in]  	b1			:   source 1.
 *  @param[in]  	b2			:   source 2
 *  @param[in]  	sz			:   number of bytes to be compared.
 *  *@return		0 in case of comparison success, -1 in case index 0 is unmatched, other return with unmatched index
*/
#define TWI_MEMCMP(b1,b2,sz)            (twi_mem_cmp((twi_u8*)(b1), (twi_u8*)(b2), (twi_u16)(sz)))

/**
 *	@brief			TWI_MIN(a, b), macro that takes two values and return the least of them
*/
#define TWI_MIN(a, b) 				(twi_get_min((twi_s64)(a), (twi_s64)(b)))

/**
 *	@brief			TWI_MAX(a, b), macro that takes two values and return the larger.
*/
#define TWI_MAX(a, b) 				(twi_get_max((twi_s64)(a), (twi_s64)(b)))


/**
 *	@brief			MSHW(a, b), macro that computes the most significant half word of a 32 bit value.
*/
#define	MSHW(val)					((twi_u16)(((val) & 0xFFFF0000) >> 16))

/**
 *	@brief			LSHW(a, b), macro that computes the least significant half word of a 32 bit value
*/
#define	LSHW(val)					((twi_u16)((val) & 0x0000FFFF))

#define TWI_LOWERCASE(str, len)     twi_lowercase((twi_u8*)(str), (twi_u32)(len))

#define TWI_UPPERCASE(str, len)     twi_uppercase((twi_u8*)(str), (twi_u32)(len))

#define TWI_ARRAY_LEN(arr)			(sizeof(arr)/sizeof(arr[0]))
#define TWI_STRING_SZ(str)              (sizeof(str)-1)  

/**
 *	@brief			TWO_S_COMPLEMENT(VAR), macro that is used to multiply input number with -1.
 *  @param[in]  	VAR			:   The input variable/number.
*/
#define TWO_S_COMPLEMENT(VAR)	( ( ~(VAR) ) + 1 )

/**
 *	@brief			Absolute macro.
 *  @param[in]  X : Expression to get its absolute.
*/
#define ABS(X)           (((X) < 0) ? -(X) : (X))

/**
 *	@brief			VAR_BITS_SIZE(VAR), macro that is used to get the number of bits in a variable.
 *  @param[in]  	VAR			:   The input variable/number.
*/
#define VAR_BITS_SIZE(VAR)		(sizeof(VAR) * 8)


/**
 *  @brief          CEIL(a, b): Divide a by b and round up.
 *  @param[in]      a: dividend
 *  @param[in]      b: divisor
*/
#define CEIL(a, b) (((a) / (b)) + (((a) % (b)) > 0 ? 1 : 0))


/**
 *  @brief          ROUND_UP(X,N): round up Integer number (X) to be multipule of N.
 *  @param[in]      X: input number
 *  @param[in]      N: base number
*/
#define ROUND_UP(X,N)   (N*(((X)+N-1)/N))

/*-*********************************************************/
/*- NEW TYPES ---------------------------------------------*/
/*-*********************************************************/
/**
 *	@brief			A new type that holds a void pointer to a void fn.
*/
typedef  void (* pf_void_ptr_to_fun)(void);

/*-*********************************************************/
/*- FUNCTION DECLARATIONS ---------------------------------*/
/*-*********************************************************/

#ifdef __cplusplus
    extern "C"
    {
#endif

/**
 *  @fn		        twi_s64 get_max(twi_s64 a, twi_s64 b)
 *  @brief			Internal implementation of function that takes two values and return the larger of them .
 *  @param[in]  	a			:	 First number.
 *  @param[in]  	b			:	 Second number.
 *  @return		the larger number
 */
static inline twi_s64 twi_get_max(twi_s64 a, twi_s64 b){return (a < b)? b : a;}

/**
 *  @fn		        twi_s64 get_max(twi_s64 a, twi_s64 b)
 *  @brief			Internal implementation of function that takes two values and return the least of them .
 *  @param[in]  	a			:	 First number.
 *  @param[in]  	b			:	 Second number.
 *  @return		the least number
 */
static inline twi_s64 twi_get_min(twi_s64 a, twi_s64 b){	return (a < b)? a : b;}
/**
 *  @function		void twi_assert(const twi_s8 *ps8_fun,const twi_u32 u32_line, twi_bool b_cond)
 *  @brief			ASSERT function
 *  @param[in]  	ps8_fun			:	 Pointer to funtion name
 *  @param[in]  	u32_line		:	 line number
 *  @param[in]  	b_cond			:	 Condition for the assert
 */
void twi_assert(const twi_s8 *ps8_fun,const twi_u32 u32_line, twi_bool b_cond);
/**
 *  @fn		        void twi_mem_cpy(twi_u8 * pu8_dst, twi_u8 * pu8_src, twi_u32  u32_sz)
 *  @brief			Internal implementation of memory copy fn, used to copy a block memory from location to another.
 *  @param[in]  	pu8_dst			:	 Pointer to the destination memory location that will hold the data.
 *  @param[in]  	pu8_src			:	 Pointer to the source memory location that holds the data already.
 *  @param[in]  	u32_sz			:	 Size of the data that will be copied in terms of bytes.
 */
void twi_mem_cpy(twi_u8 * pu8_dst, twi_u8 * pu8_src, twi_u32  u32_sz);

/**
 *  @fn		void twi_mem_set(twi_u8 * pu8_dst, twi_u8   u8_val,  twi_u32  u32_sz)
 *  @brief			Internal implementation of memory set fn, used to set a block memory with a certain input value.
 *  @param[in]  	pu8_dst			:	 Pointer to the destination memory location that will hold the data.
 *  @param[in]  	u8_val			:	 The value that the destination block will set to.
 *  @param[in]  	u32_sz			:	 Size of the data that will be set in terms of bytes.
 */
void twi_mem_set(twi_u8 * pu8_dst, twi_u8   u8_val,  twi_u32  u32_sz);

/**
 *  @fn		twi_s32 twi_mem_cmp( twi_u8 * pu8_b1,  twi_u8 * pu8_b2,  twi_u32  u32_sz)
 *  @brief			Internal implementation of memory compare fn, used to compare a block memory location with another one.
 *  @param[in]  	pu8_b1			:	 Pointer to the first memory buffer/location.
 *  @param[in]  	pu8_b2			:	 Pointer to the second memory buffer/location.
 *  @param[in]  	u32_sz			:	 Size of the data that will be compared in terms of bytes.
 *  @return		0 in case of comparison success, -1 in case index 0 is unmatched, other return with unmatched index
 */
twi_s32 twi_mem_cmp( twi_u8 * pu8_b1,  twi_u8 * pu8_b2,  twi_u32  u32_sz);

/**
 *  @fn		void twi_reverse(twi_u8 au8_str[], twi_u8 u8_len)
 *  @brief			Internal implementation of byte array reverse fn
 *  @param[in]  	pu8_str		:   the byte array
 *  @param[in]  	u16_len			:   the length of the byte array
*/
void twi_reverse(twi_u8 *pu8_str, twi_u16 u16_len);

/**
 *  @fn		        twi_u16 twi_atos64(const twi_u8* pu8_str, twi_u16 u16_len, twi_s64 *ps64_result)
 *  @brief			Internal implementation of string to integer conversion
 *  @details        It will parse the given string and convert it to a twi_s16. It will stop parsing at the first non-numeric character
 *  @param[in]  	pu8_str		:   A pointer to a string buffer
 *  @param[in]  	u16_len		:   The length of the string
 *  @param[out]     ps64_result :   The converted integer
 *	@return 		twi_u16		:	The actual length of the parsed string
*/
twi_u16 twi_atos64(const twi_u8* pu8_str, twi_u16 u16_len, twi_s64 *ps64_result);

/**
 *  @fn		        twi_s16 twi_s64toa(twi_s64 s64_num, twi_u16 u16_str_len, twi_u8 * pu8_str)
 *  @brief			Internal implementation of integer to string fn
 *  @param[in]  	s64_num			:   integer to convert
 *  @param[in]  	u16_str_len		:   Length of the given string
 *  @param[Out] 	pu8_str			:   pointer to the string
 *	@return			twi_s16         : the index at which the '\0' was placed. Which is the length of the string. In case of error it returns -1.
*/
twi_s16 twi_s64toa(twi_s64 s64_num, twi_u16 u16_str_len, twi_u8 * pu8_str);

/**
 *  @fn		twi_u16 twi_strlen(twi_u8 * pu8_str)
 *  @brief			Internal implementation of string length fn
 *  @param[in]  	pu8_str	:   pointer to the string
 *	@return			twi_u16 : the length of the string
*/
twi_u16 twi_strlen(twi_u8 * pu8_str);

/**
 * @fn		twi_str_contains
 * @brief			determines whether a string has a given character
 * @param[IN]		pu8_str: pointer to the beginning of the string
 * @param[IN]		u16_len: length of the given string
 * @param[IN]		u8_search: character to search for inside the string
 * @return 			twi_s32: the index of the character if found. -1 otherwise.
 */
twi_s32 twi_str_contains(const twi_u8 * pu8_str, twi_u16 u16_len, twi_u8 u8_search);

/**
* @fn		twi_lowercase
* @brief		Convert the upper case characters to a lower case characters.
* @param[IN]		pu8_str: pointer to the beginning of the string
* @param[IN]		u32_len: length of the given string
* @return 		::TWI_SUCCESS, ::TWI_ERROR_INVALID_ARGUMENTS.
*/
twi_s32 twi_lowercase(twi_u8 *pu8_str, twi_u32 u32_len);

/**
* @fn		twi_uppercase
* @brief		Convert the lower case characters to an upper case characters.
* @param[IN]		pu8_str: pointer to the beginning of the string
* @param[IN]		u32_len: length of the given string
* @return 		::TWI_SUCCESS, ::TWI_ERROR_INVALID_ARGUMENTS.
*/
twi_s32 twi_uppercase(twi_u8 *pu8_str, twi_u32 u32_len);


/**
 *	@brief	fn to increment the index of a circular buffer
 */
void twi_next_circular_index(twi_u8* pu8_index, twi_u8 u8_queue_len);

/**
 *	@brief		This fn used to calculate the square root.
 *	@param[in]	u64_num:	Number to calculate the square root for, it's multiplied by 1000.
 *	@return     Returns the square root multiplied by 1000.
 */
twi_u32 twi_sqrt(twi_u64 u64_num);

/**
 *	@brief		This fn used to calculate the arctan(u32_numenator/u32_denumenator) in degrees.
 *	@param[in]	s32_numerator	Numerator.
 *	@param[in]	u32_denominator	Denominator.
 *	@return     Returns the degree in range -90 to 90.
 */
twi_s16 twi_arctan(twi_s32 s32_numerator, twi_u32 u32_denominator);

/**
 *  @function		void twi_invert_add(twi_u8* pu8_des_add,twi_u8* pu8_src_add)
 *  @brief			invert the data at source "pu8_src_add" to destination "pu8_des_add".
 *  @param[in]  	pu8_des_add			:	 Pointer to the destination memory location that will hold the data.
 *  @param[in]  	pu8_src_add			:	 Pointer to the source memory location that holds the data already.
 *  @param[in]  	u32_sz			    :	 Size of the data that will be copied in terms of bytes.
 */
void twi_invert_add(twi_u8* pu8_des_add,twi_u8* pu8_src_add,twi_u32  u32_sz);
			
#ifdef __cplusplus
    }
#endif

/** @} */ /* TWI_COMMON_group s*/
#endif // TWI_COMMON_H__
