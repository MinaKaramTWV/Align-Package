/****************************************************************************/
/* Copyright (c) 2022 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/**
* @file		twi_df_8800_sensor.c.
* @brief	this is the driver of the digital force gauge Sensor df-8800
*/

//***********************************************************
/*- INCLUDES ----------------------------------------------*/
//***********************************************************
#include "twi_force_sensor.h"
#include "twi_i2c_master.h"

//***********************************************************
/*- LOCAL MACROS ------------------------------------------*/
//***********************************************************
#ifdef  DF_8800_SENSOR_LOG_ENABLE
	#include "twi_debug.h"
	#define	DF_8800_SENSOR_LOG(...)								    TWI_LOGGER("[DF_8800_SNSR]:  "__VA_ARGS__)
	#define DF_8800_SENSOR_LOG_ERR(...)						        TWI_LOGGER_ERR("[DF_8800_SNSR_ERR]: "__VA_ARGS__)
	#define DF_8800_SENSOR_LOG_HEX(MSG, HEX_BUFFER, LEN)		    TWI_DUMP_BUF("[DF_8800_SNSR]: "MSG, HEX_BUFFER, LEN)
#else
	#define	DF_8800_SENSOR_LOG(...)
	#define DF_8800_SENSOR_LOG_ERR(...)
	#define DF_8800_SENSOR_LOG_HEX(MSG, HEX_BUFFER, LEN)
#endif


/* This force sensor is controlled through registers, which are: */
#define DF_8800_MAIN_CFG					((twi_u8)(0x00))		/* Main cofiguration register */
#define DF_8800_ANALOG_CFG				 	((twi_u8)(0x01))		/* Analog cofiguration register */
#define DF_8800_STATUS						((twi_u8)(0x02))		/* Status register */
#define DF_8800_ADC_DATA_H					((twi_u8)(0x03))		/* ADC sensor high byte */
#define DF_8800_ADC_DATA_L_SAMPLE_CNT_12	((twi_u8)(0x04))		/* ADC sensor low byte and sample counter-12bit */
#define DF_8800_SAMPLE_CNT_16				((twi_u8)(0x05))		/* Sample counter-16bit */
#define DF_8800_MISC_CTRL					((twi_u8)(0x06))		/* Misc. control register */
#define DF_8800_AUTOCAL_THR_H				((twi_u8)(0x07))		/* Autocal threshold high byte */
#define DF_8800_AUTOCAL_THR_L				((twi_u8)(0x08))		/* Autocal threshold low byte */
#define DF_8800_AUTOCAL_CFG_1				((twi_u8)(0x09))		/* Autocal cofiguration 1 */
#define DF_8800_AUTOCAL_CFG_2				((twi_u8)(0x0A))		/* Autocal cofiguration 2 */
#define DF_8800_AUTOCAL_CFG_3				((twi_u8)(0x0B))		/* Autocal cofiguration 3 */
#define DF_8800_INTRTHR_H			    	((twi_u8)(0x0C))		/* Interrupt threshold high byte */
#define DF_8800_INTRTHR_L			    	((twi_u8)(0x0D))		/* Interrupt threshold low byte */
#define DF_8800_INTR_CFG			    	((twi_u8)(0x0E))		/* Interrupt cofiguration register */
#define DF_8800_BASELINE_CTRL			    ((twi_u8)(0x0F))		/* Baseline control register */
#define DF_8800_NEG_ZONE_CFG			    ((twi_u8)(0x10))		/* Negative zone cofiguration register */
#define DF_8800_SENSOR_BASELINE_H			((twi_u8)(0x12))		/* Sensor baseline high byte */
#define DF_8800_SENSOR_BASELINE_L			((twi_u8)(0x13))		/* Sensor baseline low byte */
#define DF_8800_NEG_ZONE    			    ((twi_u8)(0x14))		/* Negative zone register */
#define DF_8800_PRELD_ADJ			        ((twi_u8)(0x15))		/* Preload adjust register */
#define DF_8800_FALLTHR_H			    	((twi_u8)(0x16))		/* Falling threshold high byte */
#define DF_8800_FALLTHR_L			    	((twi_u8)(0x17))		/* Falling threshold low byte */
#define DF_8800_TEMP_SENSOR_H			    ((twi_u8)(0x18))		/* Temperature sensor high byte */
#define DF_8800_TEMP_SENSOR_L			    ((twi_u8)(0x19))		/* Temperature sensor low byte */
#define DF_8800_TEMP_SENSOR_FIFO_H			((twi_u8)(0x1E))		/* Temperature sensor FIFO high byte */
#define DF_8800_TEMP_SENSOR_FIFO_L			((twi_u8)(0x1F))		/* Temperature sensor FIFO low byte */
#define DF_8800_FIFO_SENSOR_DATA_H			((twi_u8)(0x2E))		/* FIFO sensor data high byte */
#define DF_8800_FIFO_SENSOR_DATA_L			((twi_u8)(0x2F))		/* FIFO sensor data low byte */
#define DF_8800_DEVICE_AND_REV_ID			((twi_u8)(0x80))		/* DEVICE AND REVISION ID */


/* Bit fields for the registers of the force sensore "DF-8800"*/

/* Main cofiguration register bit fields */
#define DF_8800_EN_IDX						(0)
#define DF_8800_TEMPWAIT_IDX				(1)
#define DF_8800_ADCRAW_IDX					(3)
#define DF_8800_WAIT_IDX					(4)
#define DF_8800_TOEN_IDX					(7)

/* Analog cofiguration register bit fields */
#define DF_8800_PRECHARGE_IDX				(0)
#define DF_8800_INAGAIN_IDX					(4)

/* Status register bit fields */
#define DF_8800_INTR_IDX					(0)
#define DF_8800_OVRACALTH_IDX				(2)
#define DF_8800_OVRINTRTH_IDX				(3)
#define DF_8800_BUSY_IDX					(7)

/* ADC sensor low byte and sample counter-12bit bit fields */
#define DF_8800_ADCOUT_IDX					(0)
#define DF_8800_SCOUNT12_L_IDX				(0)

/* Misc. control register bit fields */
#define DF_8800_FALLTHRSEL_IDX				(0)
#define DF_8800_SENSOR_SEL_IDX				(3)
#define DF_8800_HIGHORDER_IDX				(4)
#define DF_8800_ENFILTER_IDX				(5)
#define DF_8800_ENNEGZONE_IDX				(6)
#define DF_8800_AUTOPRELDADJ_IDX			(7)

/* Autocal cofiguration 1 bit fields */
#define DF_8800_CALPERIOD_IDX				(0)
#define DF_8800_INTRPOL_IDX	     			(3)
#define DF_8800_CALRESET_IDX				(4)
#define DF_8800_ENCALMODE_IDX				(7)

/* Autocal cofiguration 2 bit fields */
#define DF_8800_LIFTDELAY_IDX				(0)
#define DF_8800_RISEBLWGT_IDX				(4)

/* Autocal cofiguration 3 bit fields */
#define DF_8800_FALLBLWGT_IDX				(0)
#define DF_8800_TCO_IDX     				(4)
#define DF_8800_INVERT_IDX     				(7)

/* Interrupt cofiguration register bit fields */
#define DF_8800_INTRSAMPLES_IDX     		(0)
#define DF_8800_BTNMODE_IDX     			(4)
#define DF_8800_INTRPERSIST_IDX    			(5)
#define DF_8800_INTRMODE_IDX    			(6)
#define DF_8800_INTREN_IDX      			(7)

/* Negative zone cofiguration register bit fields */
#define DF_8800_RESETWGT_IDX      			(0)
#define DF_8800_NEGRESET_IDX     			(4)

/* Temperature sensor low byte bit fields */
#define DF_8800_TCOUNT_IDX      			(0)
#define DF_8800_TEMP_IDX        			(4)

/* Temperature sensor FIFO low byte bit fields */
#define DF_8800_TBCOUNT_IDX       			(0)
#define DF_8800_TEMPBUF_IDX       			(4)

/* FIFO sensor data low byte bit fields */
#define DF_8800_FCOUNT_IDX       			(0)
#define DF_8800_ADCBUF_L_IDX       			(0)

/* DEVICE AND REVISION ID bit fields */
#define DF_8800_REVID_IDX       			(0)
#define DF_8800_DEVID_IDX       			(3)


#define DF_8800_I2C_CHANNEL							(DF_8800_FORCE_SEN_I2C_CH)
#define DF_8800_I2C_ADD_SIZE						(SEVEN_BITS)
#define DF_8800_I2C_CLOCK							(I2C_SCL_100K) 	/* Standard Mode (100 KHz), Full-Speed Mode (400 KHz) and Fast Mode (<= 1MHz) are supported. */ 

/* DF_8800 device configurations */

/* DF_8800 device address */
#define DF_8800_SLAVE_ADD							(0x4E) 			/* THR_ADR Pin = 3.3kohm-33kohm resistor to GND  ->  address = 0x4C 	
																	   THR_ADR Pin = 3.3kohm-33kohm resistor to VDD  ->  address = 0x4D
																	   THR_ADR Pin = GND -> address = 0x4E
																	   THR_ADR Pin = GND -> address = 0x4F */

/* Main cofiguration register */
#define DF_8800_EN								 	(1)              /* DF_8800_EN = 0 Shutdown Mode, DF_8800_EN = 1 Active Mode */
#define DF_8800_ADCRAW                              (0)              /* DF_8800_ADCRAW = 0 ADC out will be (row force - base line),
																		DF_8800_ADCRAW = 1 ADC out will be (row force) */
#define DF_8800_WAIT								(7)              /* Wait time between successive force sensor samples
																		(000 -> 0ms), (001 -> 1ms), (010 -> 4ms), (011 -> 8ms),
																		(100 -> 16ms), (101 -> 32ms), (110 -> 64ms), (111 -> 256ms) */ 
#define DF_8800_TOEN								(1)              /* DF_8800_TOEN = 0 i2c timeout disabled, DF_8800_TOEN = 1 i2c timeout enabled (51.2 ms) */

/* Analog cofiguration register */
#define DF_8800_PRECHARGE							(0)           	 /* The ADC will wait for this much time before conversion starts
																		(000 -> 50us), (001 -> 100us), (010 -> 200us), (011 -> 400us),
																		(100 -> 800us), (101 -> 1.6ms), (110 -> 3.2ms), (111 -> 6.4ms) */
#define DF_8800_INAGAIN								(5)      		 /* Instrumentation amplifier gain selection
																		(000 -> X1), (001 -> X8), (010 -> X16), (011 -> X31),
																		(100 -> X61), (101 -> X115), (110 -> X208), (111 -> X416) */

/* Misc. control register */
#define DF_8800_SENSOR_SEL				        	(0)      		 /* DF_8800_SENSOR_SEL = 0 Center sensor, DF_8800_SENSOR_SEL = 1 Edge sensor */
#define DF_8800_ENFILTER				        	(0)				 /* DF_8800_ENFILTER = 0 ULP (Ultra Low Power) Mode, DF_8800_ENFILTER = 1 HP (High Power) Mode */
#define DF_8800_ENNEGZONE				        	(0)				 /* DF_8800_ENNEGZONE = 0 Negative Baseline Settings Disabled, DF_8800_ENNEGZONE = 1 Negative Baseline Settings Enabled */
#define DF_8800_AUTOPRELDADJ 			        	(1)				 /* DF_8800_AUTOPRELDADJ = 0 Auto Preload Adjust Disabled, DF_8800_AUTOPRELDADJ = 1 Auto Preload Adjust Enabled */

/* Autocal threshold high byte, low byte */
#define DF_8800_AUTOCAL_H                           (0x02)           /* Value for Auto calibration high byte */
#define DF_8800_AUTOCAL_L                           (0x00)			 /* Value for Auto calibration low byte */

/* Autocal cofiguration 1 */
#define DF_8800_CALPERIOD							(2)              /* Auto calibration timeout, when the force measurements remain below the auto calibration threshold
																		(000 -> 25ms), (001 -> 50ms), (010 -> 100ms), (011 -> 200ms),
																		(100 -> 400ms), (101 -> 800ms), (110 -> 1600ms), (111 -> Infinite) */ 
#define DF_8800_INTRPOL	     						(1)              /* DF_8800_INTRPOL = 0 Interrupt polarity low, DF_8800_INTRPOL = 1 Interrupt polarity high */
#define DF_8800_CALRESET							(4)				 /* Timeout before triggering base recalibration, when the force measurements remain above the auto calibration threshold
																		(000 -> 0.5s), (001 -> 1s), (010 -> 2s), (011 -> 4s),
																		(100 -> 8s), (101 -> 16s), (110 -> 32s), (111 -> Infinite) */
#define DF_8800_ENCALMODE							(1)				 /* DF_8800_ENCALMODE = 0 CALRESET timeout triggers autocalibration when sensor readings are between AUTOCAL threshold and INT threshold (for long press),
 																	    DF_8800_ENCALMODE = 1 CALRESET timeout triggers autocalibration when sensor readings are above AUTOCAL (for button applications)*/

/* Autocal cofiguration 2 */
#define DF_8800_LIFTDELAY				          	(0)     		 /* Time to wait before baselining after a sensor value has fallen below the autocal threshold, starting with value above the interrupt threshold
																		(000 -> 0ms), (001 -> 20ms), (010 -> 40ms), (011 -> 80ms),
																		(100 -> 160ms), (101 -> 320ms), (110 -> 640ms), (111 -> 460ms) */
#define DF_8800_RISEBLWGT							(2)				 /* Used to compute the new baseline on CALPERIOD expiry, when the sensor force measurement is higher than current baseline
																		New baseline = ((Current baseline)(RISEBLWGT) + Current ADC reading)/(RISEBLWGT + 1)
																		(000 -> 0), (001 -> 1), (010 -> 3), (011 -> 7),
																		(100 -> 15), (101 -> 31), (110 -> 63), (111 -> 127) */

/* Autocal cofiguration 3 */
#define DF_8800_FALLBLWGT							(2)        		 /* Used to compute the new baseline on CALPERIOD expiry, when the sensor force measurement is lower than current baseline
																		New baseline = ((Current baseline)(FALLBLWGT) + Current ADC reading)/(FALLBLWGT + 1)
																		(000 -> 0), (001 -> 1), (010 -> 3), (011 -> 7),
																		(100 -> 15), (101 -> 31), (110 -> 63), (111 -> 127) */
#define DF_8800_INVERT     							(0)				 /* DF_8800_INVERT = 0 Digital Signal Inversion Disabled, DF_8800_INVERT = 1 Digital Signal Inversion Enabled */

/* Interrupt threshold high byte, low byte */
#define DF_8800_INTR_H                         		(0x04)           /* Value for Interrupt threshold high byte (the value of Interrupt threshold can be determined by the resisror on THR_ADR (R[in kohm] = (1047 / INTthredhold[in counts]) - 0.8))*/
#define DF_8800_INTR_L                           	(0xB0)			 /* Value for Interrupt threshold low byte */

/* Interrupt cofiguration register */
#define DF_8800_INTRSAMPLES     					(3)				 /* Default value (Number of samples above interrupt threshold after which an interrupt is asserted) */
#define DF_8800_BTNMODE     						(0)				 /* DF_8800_BTNMODE = 0 -> Interrupt function determined by INTREN, INTRMODE and INTRPERSIST
																		DF_8800_BTNMODE = 1 -> Button mode - Falling threshold to de-assert interrupt*/
#define DF_8800_INTRPERSIST    						(0)				 /* DF_8800_INTRPERSIST = 0 -> 100us interrupt pulse, DF_8800_INTRPERSIST = 1 -> Infinite - Untill the status register is read */
#define DF_8800_INTRMODE    						(0)				 /* DF_8800_INTRMODE = 0 -> Use INTRSAMPLES to qualify interrupt 
																		DF_8800_INTRMODE = 1 -> Interrupt generated after each sensor ADC conversion if the same value is above interrupt threshold */	
#define DF_8800_INTREN      						(0)				 /* DF_8800_INTREN = 0 -> Interrupt Disabled - unless BTNMODE = 1, DF_8800_INTREN = 1 -> Interrupt Enabled*/

/* Baseline control register */
#define DF_8800_FORCEBL      						(0)				 /* DF_8800_FORCEBL = 0 -> Auto-Baseline enabled, DF_8800_FORCEBL = 1 -> Forces baseline to the next ADC reading - This bit is automatically reset after baseline is updated */

/* Negative zone cofiguration register */
#define DF_8800_RESETWGT      						(0) 			 /* Used to compute the new baseline, when baseline update is a result of CALRESET or NEGRESET timeout
																		New baseline = ((Current baseline)(RESETWGT) + Current ADC reading)/(RESETWGT + 1)
																		(000 -> 0), (001 -> 1), (010 -> 3), (011 -> 7),
																		(100 -> 15), (101 -> 31), (110 -> 63), (111 -> 127) */
#define DF_8800_NEGRESET		     				(5)				 /* Timeout before triggering base recalibration, when the force measurements remain below the negative auto calibration threshold
																		(000 -> 0.5s), (001 -> 1s), (010 -> 2s), (011 -> 4s),
																		(100 -> 8s), (101 -> 16s), (110 -> 32s), (111 -> No reset) */

/* Negative zone register */
#define DF_8800_NEGTHSEL      						(0)				 /* Negative auto calibration threshold as a fraction of auto calibration threshold
																	    (00 -> X1), (01 -> X0.5), (10 -> X0.25), (11 -> X0.125) */

/* Preload adjust register */
#define DF_8800_PRELDADJ      						(0)				 /* Offset Adjustment - It is read only when AUTOPRELDADJ = 1 */

//***********************************************************
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
//***********************************************************

static twi_s32 df_8800_register_write(twi_u8 u8_register_address, twi_u8 u8_data);
static twi_s32 df_8800_read_adc(twi_s16 *ps16_adc);
static twi_s32 twi_df_8800_init(void);
static twi_s32 df_8800_read_force(twi_s16 *ps16_value);
static twi_s32 twi_df_8800_deinit(void);

//***********************************************************
/*- GLOBAL STATIC VARIABLES -------------------------------*/
//***********************************************************
static twi_bool gb_df_8800_is_init = TWI_FALSE;

//***********************************************************
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
//***********************************************************

/*
 * @brief Read ADC value
 * @param[out] twi_s16* : ADC value.
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
static twi_s32 df_8800_read_adc(twi_s16 *ps16_adc)
{
    twi_s32 s32_retval = TWI_SUCCESS;
	
	if(NULL != ps16_adc)
    {
		twi_u8 au8_buffer[2] = {0};
		twi_u8 u8_adc_reg_h_add = DF_8800_ADC_DATA_H;
		s32_retval = twi_i2c_master_send_n(DF_8800_I2C_CHANNEL, (twi_u8 *)&u8_adc_reg_h_add, sizeof(twi_u8), DF_8800_SLAVE_ADD, TWI_FALSE);

		if(TWI_SUCCESS == s32_retval)
		{
			s32_retval = twi_i2c_master_recv_n(DF_8800_I2C_CHANNEL, (twi_u8 *)au8_buffer, sizeof(twi_u16), DF_8800_SLAVE_ADD, TWI_TRUE);

			if(TWI_SUCCESS != s32_retval)
			{
				DF_8800_SENSOR_LOG_ERR("df_8800_read_adc :  twi_i2c_master_recv_n %d\n",s32_retval);
				/* Do nothing (return with I2C Receive Error) */
			}
		}
		else
		{
			DF_8800_SENSOR_LOG_ERR("df_8800_read_adc :  twi_i2c_master_send_n %d\n",s32_retval);
			/* Do nothing (return with I2C Send Error) */
		}
	
		if(TWI_SUCCESS == s32_retval)
		{
			*ps16_adc = TWO_BYTE_CONCAT(au8_buffer[0], au8_buffer[1]);
		}
	}
	else
	{
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }
    return s32_retval;
}

/*
 * @brief Write to a register of the force sensor DF-8800
 * @param[in] twi_u8 : Register address
 * @param[in] twi_u8 : Data
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
static twi_s32 df_8800_register_write(twi_u8 u8_register_address, twi_u8 u8_data)
{
    twi_s32 s32_retval = TWI_SUCCESS;

	twi_u8 au8_register_write[2] = {u8_register_address, u8_data};

	s32_retval = twi_i2c_master_send_n(DF_8800_I2C_CHANNEL, (twi_u8 *)au8_register_write, TWI_ARRAY_LEN(au8_register_write), DF_8800_SLAVE_ADD, TWI_TRUE);

	if(TWI_SUCCESS == s32_retval)
	{
		DF_8800_SENSOR_LOG("DF-8800 write data to the register successfully \r\n");
	}
	else
	{
		DF_8800_SENSOR_LOG("DF-8800 failed to write data to the register \r\n");
	}
	
	return s32_retval;
}

/*
 * @brief	The function that Initializes and enables the force sensor DF-8800 with the configuration.
 */
static twi_s32 twi_df_8800_init(void)
{
	twi_s32 s32_retval = TWI_SUCCESS;
    if(TWI_FALSE == gb_df_8800_is_init)
	{
		do
		{
        	tstr_twi_i2c_master_config str_i2c;
        
        	TWI_MEMSET(&str_i2c, 0, sizeof(tstr_twi_i2c_master_config));
        
        	/* Initialize and enable device with config. */
        	str_i2c.u8_addr_size = DF_8800_I2C_ADD_SIZE;
        	str_i2c.u32_clock    = DF_8800_I2C_CLOCK;
        	str_i2c.u8_pull_up   = GET_I2C_PULL_CFG(DF_8800_I2C_CHANNEL);
        
        	s32_retval = twi_i2c_master_init(DF_8800_I2C_CHANNEL, &str_i2c);
			TWI_ERROR_BREAK(s32_retval);
			/* Main cofiguration register */
            s32_retval = df_8800_register_write(DF_8800_MAIN_CFG, (twi_u8)
													((DF_8800_EN << DF_8800_EN_IDX)				|
											 		 (0 << DF_8800_TEMPWAIT_IDX)				|   /* No temprature conversion */
											 	 	 (DF_8800_ADCRAW << DF_8800_ADCRAW_IDX)     |
													 (DF_8800_WAIT << DF_8800_WAIT_IDX)         |
													 (DF_8800_TOEN << DF_8800_TOEN_IDX)));		
			TWI_ERROR_BREAK(s32_retval);
			/* Analog cofiguration register */						
            s32_retval = df_8800_register_write(DF_8800_ANALOG_CFG, (twi_u8)
												((DF_8800_PRECHARGE << DF_8800_PRECHARGE_IDX)	|
												 (DF_8800_INAGAIN << DF_8800_INAGAIN_IDX)));
			TWI_ERROR_BREAK(s32_retval);
			/* Misc. control register */
			s32_retval = df_8800_register_write(DF_8800_MISC_CTRL, (twi_u8)
												((4 << DF_8800_EN_IDX)							|	/* Default value, It isn't used as BTNMODE = 0 */
											 	(DF_8800_SENSOR_SEL << DF_8800_SENSOR_SEL_IDX)	|   
											 	(0 << DF_8800_HIGHORDER_IDX)     				|	/* Default value, It isn't used as ENFILTER = 0 */
												(DF_8800_ENFILTER << DF_8800_ENFILTER_IDX)     	|
												(DF_8800_ENNEGZONE << DF_8800_ENNEGZONE_IDX)	|
												(DF_8800_AUTOPRELDADJ << DF_8800_AUTOPRELDADJ_IDX)));
			TWI_ERROR_BREAK(s32_retval);
			/* Autocal threshold high byte */
			s32_retval = df_8800_register_write(DF_8800_AUTOCAL_THR_H, (twi_u8)(DF_8800_AUTOCAL_H));
			TWI_ERROR_BREAK(s32_retval);
			/* Autocal threshold low byte */
			s32_retval = df_8800_register_write(DF_8800_AUTOCAL_THR_L, (twi_u8)(DF_8800_AUTOCAL_L));
			TWI_ERROR_BREAK(s32_retval);
			/* Autocal cofiguration 1 */
			s32_retval = df_8800_register_write(DF_8800_AUTOCAL_CFG_1, (twi_u8)
												((DF_8800_CALPERIOD << DF_8800_CALPERIOD_IDX)	|
											 	(DF_8800_INTRPOL << DF_8800_INTRPOL_IDX)		|   
											 	(DF_8800_CALRESET << DF_8800_CALRESET_IDX)      |
											    (DF_8800_ENCALMODE << DF_8800_ENCALMODE_IDX)));
			TWI_ERROR_BREAK(s32_retval);			
			/* Autocal cofiguration 2 */
			s32_retval = df_8800_register_write(DF_8800_AUTOCAL_CFG_2, (twi_u8)
												((DF_8800_LIFTDELAY << DF_8800_LIFTDELAY_IDX)	|
												 (DF_8800_RISEBLWGT << DF_8800_RISEBLWGT_IDX)));

			/* Autocal cofiguration 3 */
			s32_retval = df_8800_register_write(DF_8800_AUTOCAL_CFG_3, (twi_u8)
												((DF_8800_FALLBLWGT << DF_8800_FALLBLWGT_IDX)	|
											 	(0 << DF_8800_TCO_IDX)      					|  	/* Temprature Coefficient (Temprature Sensor is Disabled) */ 
											    (DF_8800_INVERT << DF_8800_INVERT_IDX)));
			TWI_ERROR_BREAK(s32_retval);
			/* Interrupt threshold high byte */
			//s32_retval = df_8800_register_write(DF_8800_INTRTHR_H, (twi_u8)(DF_8800_INTR_H));     /* Using the resistor on THR_ADR to determine the Interrupt threshold value */
			//TWI_ERROR_BREAK(s32_retval);

			/* Interrupt threshold low byte */
			//s32_retval = df_8800_register_write(DF_8800_INTRTHR_L, (twi_u8)(DF_8800_INTR_L));
			//TWI_ERROR_BREAK(s32_retval);

			/* Interrupt cofiguration register */
			s32_retval = df_8800_register_write(DF_8800_INTR_CFG, (twi_u8)
											  ((DF_8800_INTRSAMPLES << DF_8800_INTRSAMPLES_IDX)	|
											   (DF_8800_BTNMODE << DF_8800_BTNMODE_IDX)			|   
											   (DF_8800_INTRPERSIST << DF_8800_INTRPERSIST_IDX) |
											   (DF_8800_INTRMODE << DF_8800_INTRMODE_IDX)		|
											   (DF_8800_INTREN << DF_8800_INTREN_IDX)));
			TWI_ERROR_BREAK(s32_retval);
			/* Baseline control register */
			s32_retval = df_8800_register_write(DF_8800_BASELINE_CTRL, (twi_u8)(DF_8800_FORCEBL));
			
			/* Negative zone cofiguration register */
			s32_retval = df_8800_register_write(DF_8800_NEG_ZONE_CFG, (twi_u8)
												((DF_8800_RESETWGT << DF_8800_RESETWGT_IDX)		|
												 (DF_8800_NEGRESET << DF_8800_NEGRESET_IDX)));
			TWI_ERROR_BREAK(s32_retval);
			/* Negative zone register */
			s32_retval = df_8800_register_write(DF_8800_NEG_ZONE, (twi_u8)(DF_8800_NEGTHSEL));
			TWI_ERROR_BREAK(s32_retval);
			/* Preload adjust register */
			//s32_retval = df_8800_register_write(DF_8800_PRELD_ADJ, (twi_u8)(DF_8800_PRELDADJ)); 	 /* It is read only when AUTOPRELDADJ = 1 */
			//TWI_ERROR_BREAK(s32_retval);

		} while (0);
			
		if(TWI_SUCCESS == s32_retval)
		{
			gb_df_8800_is_init = TWI_TRUE;
			DF_8800_SENSOR_LOG("DF-8800 Sensor init successfully \r\n");
		}
        else
        {
            DF_8800_SENSOR_LOG("DF-8800 Sensor init Error = %d \r\n", s32_retval);
        }
    }
	else
	{
		DF_8800_SENSOR_LOG("DF-8800 Sensor initialized \r\n");
	}    

	return s32_retval;
}

/*
 * @brief Read Force sensor DF-8800
 * @param[out] twi_s16* : Force sensor value.
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
static twi_s32 df_8800_read_force(twi_s16 *ps16_value)
{
	twi_s32 s32_retval = TWI_SUCCESS;
	
	if(NULL != ps16_value)
    {
		s32_retval = df_8800_read_adc(ps16_value);
	}
	else
	{
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }
	
	return s32_retval;
}

/*
 * @brief Function that is used to de-initialize DF-8800 Sensor
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
static twi_s32 twi_df_8800_deinit(void)
{
	twi_s32 s32_retval = TWI_SUCCESS;
    
    if(TWI_TRUE == gb_df_8800_is_init)
    {
		/*Shutdown Mode*/
		s32_retval = df_8800_register_write(DF_8800_MAIN_CFG, (twi_u8)(0 << DF_8800_EN_IDX));

        s32_retval = twi_i2c_master_deinit(DF_8800_I2C_CHANNEL);

        gb_df_8800_is_init = TWI_FALSE;
    }
    return s32_retval;
}

//***********************************************************
/*- APIs IMPLEMENTATION -----------------------------------*/
//***********************************************************
/**
*	@function	twi_s32 twi_force_sensor_init(void)
*
*	@brief		- Function used for initialization of Force sensor.
*
*   @return     Returns (TWI_SUCCESSS ::) in case of success and (-ve) error value in case of failure.
 */

twi_s32 twi_force_sensor_init(void)
{
	twi_s32 s32_retval = TWI_ERROR;
        s32_retval = twi_df_8800_init();
        return s32_retval;
}

/**
 * @brief Read Force sensor 
 * @param[out] twi_s16* : Force sensor value.
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */

twi_s32 twi_force_sensor_read(twi_s16 *ps16_value)
{
	twi_s32 s32_retval = TWI_ERROR;
        s32_retval = df_8800_read_force(ps16_value);
        return s32_retval;
}

/**
 * @brief Function that is used to de-initialize force Sensor
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
twi_s32 twi_force_sensor_deinit(void)
{
	twi_s32 s32_retval = TWI_ERROR;
        s32_retval = twi_df_8800_deinit();
        return s32_retval;
}
