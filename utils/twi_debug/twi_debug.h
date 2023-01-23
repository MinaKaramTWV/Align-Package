/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file		twi_debug.h
 *	@brief		This file is the header file of the LOGGER module.
 */

#ifndef TWI_DEBUG_H__
#define TWI_DEBUG_H__

#include "twi_types.h"
#include "twi_retval.h"
#include <stdio.h>
#include <stdarg.h>
/*-*********************************************************/
/*- GLOBAL MACROS ------------------------------------------*/
/*-*********************************************************/
#define TWI_LOG_LEVEL_NONE  (0)
#define TWI_LOG_LEVEL_ERR   (1)
#define TWI_LOG_LEVEL_INFO  (2)
#define TWI_LOG_LEVEL_DBG   (3)


#ifndef TWI_LOG_LEVEL
#define TWI_LOG_LEVEL   TWI_LOG_LEVEL_DBG
#endif

#ifndef TWI_LOG
#define TWI_LOG(...)
#endif
#define TWI_LOGGER_ERR(...)
#define TWI_LOGGER_SUCCESS(...)
#define TWI_LOGGER_INFO(...)
#define TWI_LOGGER(...)
#define TWI_LOG_PRINT(...)
#define TWI_DUMP_BUF(name,Buffer,size)
#define TWI_DUMP_HEX(Buffer,size)
#define TWI_DUMP_BUFC(name,Buffer,size)
#define TWI_LOG_TIME

#define TESTING_LOG_ERROR(...)
#define TESTING_LOG_SUCCESS(...)
#define TESTING_LOG_INFO(...)
#define TESTING_LOG(...)
#define	TESTING_LOG_COMBINED(STRING,INT)
#define	TESTING_LOG_HEX(MSG,HEX_BUFFER,LEN)
#define	TESTING_LOG_IP(MSG,IP_ADDR_BUFFER)
#define TESTING_LOG_MAC(MSG,MAC_ADDR_BUFFER)			
/*-*********************************************************/
/*- LOCAL MACROS ------------------------------------------*/
/*-*********************************************************/

/*-***********************************************************/
/*- FUNCTION LIKE MACROS ------------------------------------*/
/*-***********************************************************/

/**
*	@brief			TWI_LOGGER_INIT	macro that is used to initialize uart-logger module.
*					TWI_LOGGER 		macro that is used to print messages for debugging purpose, ::DEBUGGING_ENABLE flag must be enabled.
*					TWI_APP_ERROR	macro that is used to report an error to the app level.
*
*/
#ifdef DEBUGGING_ENABLE
    #define TWI_FUNCTION	__FUNCTION__
    #define TWI_LINE		__LINE__
    #define TWI_FILE		__FILE__

    #define TWI_LOGGER_INIT()						twi_logger_init(NULL)
    #define TWI_LOGGER_DEINIT()						twi_logger_deinit()
    #define TWI_LOGGER_INIT_RXTX(cb)				twi_logger_init(cb)
	
#if defined(TWI_CEEDLING_TEST)
    #include "unity.h"
	#include "assert.h"
	#undef TWI_LOG	
	#define TWI_LOG									printf
#else
	#undef TWI_LOG	
    #define TWI_LOG									twi_logger
#endif

	#undef TWI_LOG_PRINT
	#define TWI_LOG_PRINT(...) 		do{TWI_LOG((twi_u8*)__VA_ARGS__);}while(0)
		
	#ifdef	TESTING_LOG_ENABLE
		#if (TWI_LOG_LEVEL >= TWI_LOG_LEVEL_ERR)
			#undef TESTING_LOG_ERROR
			#undef TESTING_LOG_SUCCESS
			#define TESTING_LOG_ERROR(...) 	twi_logger_err((const twi_u8*)TWI_FUNCTION,TWI_LINE,(const twi_u8*)__VA_ARGS__)
			#define TESTING_LOG_SUCCESS(...) 	twi_logger_success((const twi_u8*)TWI_FUNCTION,TWI_LINE,(const twi_u8*)__VA_ARGS__)
			#if (TWI_LOG_LEVEL >= TWI_LOG_LEVEL_INFO)
				#undef TESTING_LOG_INFO
				#define TESTING_LOG_INFO(...) 	twi_logger_info((const twi_u8*)__VA_ARGS__)
				#if (TWI_LOG_LEVEL >= TWI_LOG_LEVEL_DBG)
					#undef TESTING_LOG
					#define TESTING_LOG(...) 		twi_logger_debug((const twi_u8*)__VA_ARGS__)
				#endif
			#endif
		#endif	
	
		#undef 		TESTING_LOG_COMBINED			
		#define		TESTING_LOG_COMBINED(STRING,INT)		\
		do{													\
			TESTING_LOG("%s %d\n",STRING,INT);				\
		}while(0)
		
		#undef 		TESTING_LOG_HEX
		#define		TESTING_LOG_HEX(MSG, HEX_BUFFER, LEN)	\
		do{													\
			TWI_LOGGER(MSG" = \r\n");						\
			TWI_LOGGER_BUF_HEX(HEX_BUFFER, LEN);			\
		}while(0)

		#undef	TESTING_LOG_IP
		#define	TESTING_LOG_IP( MSG , IP_ADDR_BUFFER)		\
		do													\
		{													\
			TWI_LOGGER_IP(MSG,IP_ADDR_BUFFER);				\
		}while(0)

		#undef 	TESTING_LOG_MAC
		#define TESTING_LOG_MAC( MSG , MAC_ADDR_BUFFER)		\
		do													\
		{													\
			TWI_LOGGER_MAC(MSG,MAC_ADDR_BUFFER);			\
		}while(0)
	#endif
	
	#ifdef I2C_DEBUG
		#define I2C_DEBUG_CHANNEL 			DEBUG_I2C_CH
		#define I2C_DEBUG_SLAVE_ADD 		85
		#define MAX_STR_LEN 				1000
	#else
    #if !defined(UART_DEBUG_CHANNEL)
            #define UART_DEBUG_CHANNEL 			0
    #endif
    #endif
		
#ifdef DEBUG_TIME_ENABLE
    #undef TWI_LOG_TIME
	extern volatile twi_u32      gu32_Jiff;
    #define TWI_LOG_TIME         TWI_LOG((const twi_u8*)"(%d)",gu32_Jiff)
#endif 
	#if (TWI_LOG_LEVEL >= TWI_LOG_LEVEL_ERR)
		#undef TWI_LOGGER_ERR
		#undef TWI_LOGGER_SUCCESS
        #define TWI_LOGGER_ERR(...) 	twi_logger_err((const twi_u8*)__FUNCTION__,__LINE__,(const twi_u8*)__VA_ARGS__)
		#define TWI_LOGGER_SUCCESS(...) 	twi_logger_success((const twi_u8*)TWI_FUNCTION,TWI_LINE,(const twi_u8*)__VA_ARGS__)
		#if (TWI_LOG_LEVEL >= TWI_LOG_LEVEL_INFO)
			#undef TWI_LOGGER_INFO
            #define TWI_LOGGER_INFO(...) 	twi_logger_info((const twi_u8*)__VA_ARGS__)
			#if (TWI_LOG_LEVEL >= TWI_LOG_LEVEL_DBG)
                
				#undef TWI_LOGGER
#if defined(WIN32)
				#define TWI_LOGGER(...) 		printf((twi_u8*)__VA_ARGS__)
#else	
                #define TWI_LOGGER(...) 		twi_logger_debug((const twi_u8*)__VA_ARGS__)
#endif    
				#undef TWI_DUMP_BUF
					/* Dumping the contents of a buffer in hex Format. */
                #define TWI_DUMP_BUF(name,Buffer,size)		twi_logger_dump_buf((const twi_u8*)name,(const twi_u8*)Buffer,size)						
				/*lint -restore*/
				#undef TWI_DUMP_HEX
				/* Dumping the contents of a buffer in hex Format. */
                #define TWI_DUMP_HEX(Buffer,size)			twi_logger_dump_hex((const twi_u8*)Buffer,size)		  

				#undef TWI_DUMP_BUFC
				/* Dumping the contents of a buffer in ASCII Format. */
                #define TWI_DUMP_BUFC(name,Buffer,size)		twi_logger_dump_bufc((const twi_u8*)name,(const twi_u8*)Buffer,size)						
			#endif
		#endif
	#endif

    #define FUN_IN                                  TWI_LOGGER("FUN_IN >>>%s %d\r\n",TWI_FUNCTION,TWI_LINE)
                
    #define STACK_IN                                TWI_LOGGER_INFO("STACK_IN >>%s %d STACK %x IPSR %d\n",TWI_FUNCTION,TWI_LINE,__get_MSP(),__get_IPSR())
	#define TWI_APP_ERROR(ERROR)					do													\
													{													\
														if(TWI_APP_SUCCESS != ERROR)					\
														{												\
															/* Error reported here. */					\
															TWI_LOGGER("Error number = %d\r\n",ERROR);	\
														}												\
													}while(0)

	#define TWI_LOGGER_BUF_HEX(pu8_buf, u16_len)	TWI_DUMP_HEX(pu8_buf, u16_len)

	#define TWI_LOGGER_COMBINED(MSG, NUM)			TWI_LOGGER("%s %d\r\n",MSG,NUM)
	#define TWI_LOGGER_IP(MSG, IP_ADDR_BUFFER)		TWI_LOGGER("%s %d.%d.%d.%d\r\n",MSG,IP_ADDR_BUFFER[0],IP_ADDR_BUFFER[1],IP_ADDR_BUFFER[2],IP_ADDR_BUFFER[3])

	#define TWI_LOGGER_MAC(MSG, MAC_ADDR_BUFFER)	TWI_LOGGER("%s %d:%d:%d:%d:%d:%d\r\n",MSG,IP_ADDR_BUFFER[0],IP_ADDR_BUFFER[1],IP_ADDR_BUFFER[2],IP_ADDR_BUFFER[3],IP_ADDR_BUFFER[4],IP_ADDR_BUFFER[5])													\


	#ifdef UNIT_TEST_LOGGER_ENABLE
		extern twi_u8 gu8_current_tc_number;
		#define UNIT_TEST_LOGGER(...)										do {TWI_LOGGER("[TEST CASE %d] -- ", gu8_current_tc_number); \
																					TWI_LOGGER(__VA_ARGS__); \
																					TWI_LOGGER("\r\n"); \
																					} while(0)
		#define UNIT_TEST_LOGGER_ERROR(...)									do {TWI_LOGGER("[TEST CASE %d] -- ERROR -- ", gu8_current_tc_number); \
																					TWI_LOGGER(__VA_ARGS__); \
																					TWI_LOGGER("\r\n"); \
																					} while(0)
		#define UNIT_TEST_DUMP_BUF(name,Buffer,size)		TWI_DUMP_BUF(name,Buffer,size)
	#else
		#define UNIT_TEST_LOGGER(...)
		#define UNIT_TEST_DUMP_BUF(name,Buffer,size)
	#endif
#else
	#define TWI_LOGGER_INIT()                          
    #define TWI_LOGGER_DEINIT()
	#define TWI_LOGGER(...)
	#define TWI_LOGGER_INT(INT_NUM)
	#define TWI_APP_ERROR(ERROR)
    #define TWI_LOGGER_HEX(u8_x)
    #define TWI_LOGGER_BUF_HEX(pu8_buf, u16_len)
	#define TWI_LOGGER_COMBINED(MSG, NUM)
	#define TWI_LOGGER_IP(MSG, IP_ADDR_BUFFER)
	#define TWI_LOGGER_MAC(MSG, MAC_ADDR_BUFFER)
    #define FUN_IN 
    #define STACK_IN                                                                                     
	#define UNIT_TEST_LOGGER(...)
	#define UNIT_TEST_DUMP_BUF(name,Buffer,size)
	#define TWI_FUNCTION	""
    #define TWI_LINE		0
    #define TWI_FILE		""
#endif

/*----------------------------------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/
/*----------------------------------------------------------*/
#if defined(DEBUGGING_ENABLE)

#ifdef __cplusplus
    extern "C"
    {
#endif
	/**
	 *	@brief	logger function init
	 */
	void twi_logger_init(void *cb);
	/**
	 *	@brief	logger function deinit
	 */
    void twi_logger_deinit(void);
	/**
	 *	@brief	logger function print 
	 */
	void twi_logger(const twi_u8* pu8_prnt_msg,...);
         
    void twi_logger_debug(const twi_u8* pu8_prnt_msg,...);

    void twi_logger_info(const twi_u8* pu8_prnt_msg,...);

    void twi_logger_err(const twi_u8* pu8_file_name, const twi_u32 u32_line, const twi_u8* pu8_prnt_msg,...);

	void twi_logger_success(const twi_u8* pu8_file_name, const twi_u32 u32_line, const twi_u8* pu8_prnt_msg,...);

    void twi_logger_dump_buf(const twi_u8* name, const twi_u8* Buffer, const twi_u32 size);

    void twi_logger_dump_hex(const twi_u8* Buffer, const twi_u32 size);

    void twi_logger_dump_bufc(const twi_u8* name,const twi_u8* Buffer, const twi_u32 size);

	void twi_logger_var(const char* pu8_prnt_msg, va_list argp,int u8_strlen);
#ifdef __cplusplus
    }
#endif

#endif
/** @} */ /* twi_debug_group */

#endif  /*__TWI_DEBUG_H__*/
