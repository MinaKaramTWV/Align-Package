/****************************************************************************/
/* Copyright (c) 2022 Thirdwayv, Inc. All Rights Reserved. */
/****************************************************************************/
/**
 ** @file					twi_rhp_ble_align_tag.h
 */

#ifndef TWI_RHP_BLE_ALIGN_TAG_H
#define TWI_RHP_BLE_ALIGN_TAG_H

/***********************************************************/
/*- INCLUDES ----------------------------------------------*/
/***********************************************************/
#include "twi_sas_ids.h"
#include "twi_profile_ids.h"
#include "twi_opp_cfg.h"
#include "twi_settings_data.h"
/*-***********************************************************/
/*- Global MACROS --------------------------------------------*/
/*-***********************************************************/
#define PROFILE_ID								PROFILE_ID_BLE_ALIGN_TAG
#define FEATURE_ZERO_IDX					    (0)
#define FEATURE_ONE_IDX					        (1)
#define FEATURE_TWO_IDX					        (2)
#define FEATURE_THREE_IDX					    (3)
#define FEATURE_FOUR_IDX					    (4)

#define ATTRIBUTE_ZERO_IDX					    (0)
#define ATTRIBUTE_ONE_IDX						(1)
#define ATTRIBUTE_TWO_IDX						(2)
#define ATTRIBUTE_THREE_IDX				    	(3)
#define ATTRIBUTE_FOUR_IDX					    (4)
#define ATTRIBUTE_FIVE_IDX					    (5)
#define ATTRIBUTE_SIX_IDX					    (6)
#define ATTRIBUTE_SEVEN_IDX					    (7)

#if (TWI_ADV_MODE == TWI_ADV_MODE_2) || (TWI_ADV_MODE == TWI_ADV_MODE_BOTH)
	#define APP_DATA_SPEC_LENGTH				(0)
#endif

#define TWI_APP_ADV_DATA_INFO			    	TWI_BEACON_COMPOS_INFO(TWI_BEACON_VER)
#define FIXED_PART_128_UUID_SIZE				(9)
#define TWI_ALIGN_TAG_LOGGER_INTERVAL_S			(60)
#define TWI_ALIGN_TAG_REPORT_INTERVAL_S			(60)
#define TWI_ALIGN_TAG_LOGGER_REPORT_INTERVAL_S	(60)
#define TWI_ALIGN_TAG_LOG_SIZE					(105)

#define TWI_BEACON_VER				0

#define TWI_APP_ADV_DATA_INFO		TWI_BEACON_COMPOS_INFO(TWI_BEACON_VER)

#define DISABLE_SENSOR_READINGS                   	(0)
#define RESERVED_FIVE_BITS                          (0b00000)

#define ACC_READING_SIZE  							(6)
#define ACC_NUMBER_OF_READINGS  					(10)
#define ACC_DATA_SIZE_PER_LOGGING_INTERVAL  		(ACC_READING_SIZE * ACC_NUMBER_OF_READINGS)

#define PRESS_READING_SIZE  						(4)
#define PRESS_NUMBER_OF_READINGS  					(10)
#define PRESS_DATA_SIZE_PER_LOGGING_INTERVAL  		(PRESS_READING_SIZE * PRESS_NUMBER_OF_READINGS)

#define FORCE_READING_SIZE  						(2)
#define FORCE_NUMBER_OF_READINGS  					(1)
#define FORCE_DATA_SIZE_PER_LOGGING_INTERVAL  		(FORCE_READING_SIZE * FORCE_NUMBER_OF_READINGS)

#define TEMP_READING_SIZE  							(2)
#define TEMP_NUMBER_OF_READINGS  					(1)
#define TEMP_DATA_SIZE_PER_LOGGING_INTERVAL  		(TEMP_READING_SIZE * TEMP_NUMBER_OF_READINGS)

#define PH_READING_SIZE  							(1)
#define PH_NUMBER_OF_READINGS  						(1)
#define PH_DATA_SIZE_PER_LOGGING_INTERVAL  			(PH_READING_SIZE * PH_NUMBER_OF_READINGS)

#define TOTAL_DATA_SIZE_PER_LOGGING_INTERVAL  		(ACC_DATA_SIZE_PER_LOGGING_INTERVAL+PRESS_DATA_SIZE_PER_LOGGING_INTERVAL+FORCE_DATA_SIZE_PER_LOGGING_INTERVAL+TEMP_DATA_SIZE_PER_LOGGING_INTERVAL+PH_DATA_SIZE_PER_LOGGING_INTERVAL)

#define	DISCHARGING_STATUS_FULL_BATTERY			    (1100)	

/**
 * Disconnection Time-out for peripheral and central
 * */
#define	CEN_IDLE_TIMEOUT			    			(6)		/**< This is the auto-disconnection time out for the central role of TP manager in seconds.*/
#define	PER_IDLE_TIMEOUT			    			(0)		/*@brief This is the auto-disconnection time out for the peripheral role of TP manager in seconds.*/

/*-***********************************************************/
/*- ENUMERTAIONS --------------------------------------------*/
/*-***********************************************************/
typedef enum {
	POLLING_TAG_NOT_FOUND,
	POLLING_START,
	POLLING_TAG_FOUND,
	PDOWN_MODE,
}tenu_polling_states;

typedef enum {
	ALIGN_TAG_CONTINUS_MODE = 0,
	ALIGN_TAG_PERIODIC_MODE,
	ALIGN_TAG_EVENT_MODE,
	ALIGN_TAG_INVALID_MODE,
}tenu_align_operation_mode;

/*-**********************************************************/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*-**********************************************************/
TWI_PACK(typedef struct
{
	twi_u8  u8_reserved:5;              /* Reserved 5 bits */  
	twi_u8  u8_operation_mode:3;        /* Device operating mode */    
    twi_u8  u8_n0;          			/* Number of accelerometer readings per log (logger 0) */
    twi_u8  u8_m0;        				/* Number of pressure readings per log (logger 0) */
    twi_u8  u8_l0;       				/* Number of force readings per log (logger 0) */
    twi_u8  u8_y0;       				/* Number of temperature readings per log (logger 0) */
    twi_u8  u8_z0;   					/* Number of pH readings per log (logger 0) */
    twi_u8  u8_n1;          			/* Number of accelerometer readings per log (logger 1) */
    twi_u8  u8_m1;       				/* Number of pressure readings per log (logger 1) */
    twi_u8  u8_l1;       				/* Number of force readings per log (logger 1) */
    twi_u8  u8_y1;       				/* Number of temperature readings per log (logger 1) */
    twi_u8  u8_z1;         				/* Number of pH readings per log (logger 1) */
})tstr_align_session_status;
	
/*-***********************************************************/
/*- FUNCTIONS' PROTOTYPES -----------------------------------*/
/*-***********************************************************/

#endif /* TWI_RHP_BLE_ALIGN_TAG_H */
