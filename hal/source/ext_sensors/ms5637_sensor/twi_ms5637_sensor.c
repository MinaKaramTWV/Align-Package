/****************************************************************************/
/* Copyright (c) 2022 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/*!
@file		twi_ms5637_sensor.c.
@brief		this is the driver of TE connectivity Barometric Pressure Sensor MS5637
			this sensor contains Peressure and Temp sensors.
*/
//***********************************************************
/*- INCLUDES ----------------------------------------------*/
//***********************************************************
#include "twi_i2c_master.h"

#if defined(MS5637_PRESS_SENSOR)
#include "twi_pressure_sensor.h"
#endif

#if defined(MS5637_TEMP_SENSOR)
#include "twi_temp_sensor.h"
#endif
//***********************************************************
/*- LOCAL MACROS ------------------------------------------*/
//***********************************************************

#ifdef  MS5637_SENSOR_LOG_ENABLE
	#include "twi_debug.h"
	#define	MS5637_SENSOR_LOG(...)								    TWI_LOGGER("[MS5637_SNSR]:  "__VA_ARGS__)
	#define MS5637_SENSOR_LOG_ERR(...)						        TWI_LOGGER_ERR("[MS5637_SNSR_ERR]: "__VA_ARGS__)
	#define MS5637_SENSOR_LOG_HEX(MSG, HEX_BUFFER, LEN)		        TWI_DUMP_BUF("[MS5637_SNSR]: "MSG, HEX_BUFFER, LEN)
#else
	#define	MS5637_SENSOR_LOG(...)
	#define MS5637_SENSOR_LOG_ERR(...)
	#define MS5637_SENSOR_LOG_HEX(MSG, HEX_BUFFER, LEN)
#endif


#define MS5637_I2C_CHANNEL								            (MS5637_TEMP_PRESS_SEN_I2C_CH)
#define MS5637_I2C_ADD_SIZE								            (SEVEN_BITS)
#define MS5637_I2C_CLOCK								            (I2C_SCL_100K)

// MS5637 device address
#define MS5637_SLAVE_ADD								            0x76 //0b1110110

// MS5637 device commands
#define MS5637_RESET_COMMAND										0x1E
#define MS5637_START_PRESSURE_ADC_CONVERSION						0x40
#define MS5637_START_TEMPERATURE_ADC_CONVERSION						0x50
#define MS5637_READ_ADC												0x00

#define MS5637_CONVERSION_OSR_MASK									0x0F


#define MS5637_CONVERSION_TIME_OSR_256								540
#define MS5637_CONVERSION_TIME_OSR_512								1100
#define MS5637_CONVERSION_TIME_OSR_1024								2080
#define MS5637_CONVERSION_TIME_OSR_2048								4130
#define MS5637_CONVERSION_TIME_OSR_4096								8220
#define MS5637_CONVERSION_TIME_OSR_8192								16440

// MS5637 commands
#define MS5637_PROM_ADDRESS_READ_ADDRESS_0							0xA0
#define MS5637_PROM_ADDRESS_READ_ADDRESS_1							0xA2
#define MS5637_PROM_ADDRESS_READ_ADDRESS_2							0xA4
#define MS5637_PROM_ADDRESS_READ_ADDRESS_3							0xA6
#define MS5637_PROM_ADDRESS_READ_ADDRESS_4							0xA8
#define MS5637_PROM_ADDRESS_READ_ADDRESS_5							0xAA
#define MS5637_PROM_ADDRESS_READ_ADDRESS_6							0xAC
#define MS5637_PROM_ADDRESS_READ_ADDRESS_7							0xAE

// Coefficients indexes for temperature and pressure computation
#define MS5637_CRC_INDEX											0
#define MS5637_PRESSURE_SENSITIVITY_INDEX							1 
#define MS5637_PRESSURE_OFFSET_INDEX								2
#define MS5637_TEMP_COEFF_OF_PRESSURE_SENSITIVITY_INDEX				3
#define MS5637_TEMP_COEFF_OF_PRESSURE_OFFSET_INDEX					4
#define MS5637_REFERENCE_TEMPERATURE_INDEX							5
#define MS5637_TEMP_COEFF_OF_TEMPERATURE_INDEX						6
#define MS5637_COEFFICIENT_NUMBERS									7

/*-***********************************************************/
/*- ENUMS ---------------------------------------------------*/
/*-***********************************************************/

 /**
 *	@enum		tenu_ms5637_resolution_osr
 *	@brief		ENUM of ms5637 resolution osr.
 */
typedef enum
{
	MS5637_RESOLUTION_OSR_256 = 0,
	MS5637_RESOLUTION_OSR_512,
	MS5637_RESOLUTION_OSR_1024,
	MS5637_RESOLUTION_OSR_2048,
	MS5637_RESOLUTION_OSR_4096,
	MS5637_RESOLUTION_OSR_8192
} tenu_ms5637_resolution_osr;

//***********************************************************
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
//***********************************************************
#if defined(MS5637_PRESS_SENSOR) || defined (MS5637_TEMP_SENSOR) 
static twi_s32 ms5637_write_command(twi_u8);
static twi_s32 ms5637_read_eeprom_coeff(twi_u8, twi_u16*);
static twi_s32 ms5637_read_eeprom(void);
static twi_s32 ms5637_conversion_and_read_adc( twi_u8, twi_u32 *);
static twi_s32 ms5637_crc_check (twi_u16 *pu16_n_prom, twi_u8 u8_crc, twi_bool *b_crc_check);
#endif
//***********************************************************
/*- GLOBAL STATIC VARIABLES -------------------------------*/
//***********************************************************
#if defined(MS5637_PRESS_SENSOR) || defined (MS5637_TEMP_SENSOR)
static twi_bool gb_ms5637_is_init = TWI_FALSE;
static tenu_ms5637_resolution_osr genu_ms5637_resolution_osr;
static twi_u16 gau16_eeprom_coeff[MS5637_COEFFICIENT_NUMBERS + 1];

// Default value to ensure coefficients are read before converting temperature
static twi_bool gb_ms5637_coeff_read = TWI_FALSE;

static twi_u32 gau32_conversion_time[6] = {	MS5637_CONVERSION_TIME_OSR_256,
										MS5637_CONVERSION_TIME_OSR_512,
										MS5637_CONVERSION_TIME_OSR_1024,
										MS5637_CONVERSION_TIME_OSR_2048,
										MS5637_CONVERSION_TIME_OSR_4096,
										MS5637_CONVERSION_TIME_OSR_8192};
#endif
//***********************************************************
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
//***********************************************************

//***********************************************************
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
//***********************************************************
#if defined(MS5637_PRESS_SENSOR) || defined (MS5637_TEMP_SENSOR)                                       
/*
 * @brief Writes the MS5637 8-bits command with the value passed
 * @param[in] twi_u8 : Command value to be written.
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
static twi_s32 ms5637_write_command(twi_u8 u8_cmd)
{
	twi_s32 s32_retval = TWI_SUCCESS;
	s32_retval = twi_i2c_master_send_n(MS5637_I2C_CHANNEL, &u8_cmd, sizeof(u8_cmd), MS5637_SLAVE_ADD, TWI_TRUE);
	if(TWI_SUCCESS == s32_retval)
	{
		MS5637_SENSOR_LOG("MS5637 write cmd successfully %x \r\n", u8_cmd);
	}
	else
	{
		MS5637_SENSOR_LOG_ERR("MS5637 write cmd Error = %d  cmd = %x\r\n", s32_retval, u8_cmd);
	}

	return s32_retval;
}

/*
 * @brief Reads the ms5637 EEPROM coefficient stored at address provided.
 * @param[in] twi_u8 : Address of coefficient in EEPROM
 * @param[out] twi_u16* : Value read in EEPROM
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
static twi_s32 ms5637_read_eeprom_coeff(twi_u8 u8_command, twi_u16 *pu16_coeff)
{
    twi_s32 s32_retval = TWI_SUCCESS;
    
    if(NULL != pu16_coeff)
	{
        twi_u8 au8_buffer[2] = {0};

        /* Send the conversion command */
        s32_retval = ms5637_write_command(u8_command);
        if(s32_retval == TWI_SUCCESS)
        {
            s32_retval = twi_i2c_master_recv_n(MS5637_I2C_CHANNEL, au8_buffer, sizeof(au8_buffer), MS5637_SLAVE_ADD, TWI_TRUE);
            if(s32_retval == TWI_SUCCESS)
            {
                *pu16_coeff = TWO_BYTE_CONCAT(au8_buffer[0], au8_buffer[1]);
                
                if(*pu16_coeff == 0)
                {
                    s32_retval = TWI_ERROR_INTERNAL_ERROR;
                }
            }
            else
            {
            }
        }
        else
        {
        }
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	}            
	return s32_retval;	
}

/*
 * @brief CRC check
 * @param[in] twi_u16 *: List of EEPROM coefficients
 * @param[in] twi_u8 : crc to compare with
 * @param[out] twi_bool* : TRUE if CRC is OK, FALSE if KO
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
static twi_s32 ms5637_crc_check (twi_u16 *pu16_n_prom, twi_u8 u8_crc, twi_bool *b_crc_check)
{
    twi_s32 s32_retval = TWI_SUCCESS;
    if((NULL != pu16_n_prom) && (NULL != b_crc_check))
    {
        twi_u8 u8_cnt = 0; // simple counter
        twi_u16 u16_n_rem = 0; // crc reminder
        twi_u8 u8_n_bit = 0;
        
        pu16_n_prom[0] = ((pu16_n_prom[0]) & 0x0FFF); // CRC byte is replaced by 0
        pu16_n_prom[7] = 0; // Subsidiary value, set to 0
        
        for (u8_cnt = 0; u8_cnt < 16; u8_cnt++) // operation is performed on bytes
        { // choose LSB or MSB
            if ((u8_cnt % 2) == 1)
            {
                u16_n_rem ^= (twi_u16)((pu16_n_prom[u8_cnt>>1]) & 0x00FF);
            }
            else
            {                
                u16_n_rem ^= (twi_u16)(pu16_n_prom[u8_cnt>>1]>>8);
            }
            
            for (u8_n_bit = 8; u8_n_bit > 0; u8_n_bit--)
            {
                if (u16_n_rem & (0x8000))
                {
                    u16_n_rem = (u16_n_rem << 1) ^ 0x3000;
                }
                else
                {
                    u16_n_rem = (u16_n_rem << 1);
                }
            }
        }
        
        u16_n_rem= ((u16_n_rem >> 12) & 0x000F); // final 4-bit reminder is CRC code
 
        *b_crc_check =  ( u16_n_rem == u8_crc );
    }
    else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	}
    
	return s32_retval;	
}

/*
 * @brief Reads the ms5637 EEPROM coefficients to store them for computation.
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
static twi_s32 ms5637_read_eeprom(void)
{
    twi_s32 s32_retval = TWI_SUCCESS;
	twi_u8 u8_i = 0;
	
	for( u8_i=0 ; u8_i < MS5637_COEFFICIENT_NUMBERS ; u8_i++)
	{
		s32_retval = ms5637_read_eeprom_coeff( (MS5637_PROM_ADDRESS_READ_ADDRESS_0 + u8_i*2), (gau16_eeprom_coeff + u8_i));
		if(s32_retval != TWI_SUCCESS)
        {
            break;
        }
	}
    
    if(s32_retval == TWI_SUCCESS)
    {
        twi_bool b_crc_check = 0;
        s32_retval = ms5637_crc_check( gau16_eeprom_coeff, (( gau16_eeprom_coeff[MS5637_CRC_INDEX] & 0xF000 ) >> 12), &b_crc_check);
        
        if(TWI_SUCCESS == s32_retval)
        {
            if(!b_crc_check)
            {
                s32_retval = TWI_ERROR_INVALID_CRC;
            }
            else
            {
                gb_ms5637_coeff_read = TWI_TRUE;
            }
        }
    }
	return s32_retval;
}

/*
 * @brief Triggers conversion and read ADC value
 * @param[in]  twi_u8 : Command used for conversion (will determine Temperature vs Pressure and osr)
 * @param[out] twi_u32* : ADC value.
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
static twi_s32 ms5637_conversion_and_read_adc(twi_u8 u8_cmd, twi_u32 *pu32_adc)
{
    twi_s32 s32_retval = TWI_SUCCESS;
	
    do
    {
        twi_u8 au8_buffer[3] = {0};
        if(NULL == pu32_adc)
        {
            s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
            break;
        }
        
        s32_retval = ms5637_write_command(u8_cmd);
        
        /* delay conversion depending on resolution*/
        /* TWI_DELAY_MS((gau32_conversion_time[ (u8_cmd & MS5637_CONVERSION_OSR_MASK)/2 ] / 1000)); */
        TWI_DELAY_US((gau32_conversion_time[ (u8_cmd & MS5637_CONVERSION_OSR_MASK)/2 ]));
        
        TWI_ERROR_BREAK(s32_retval);
        
        /* Send the read command*/
        s32_retval = ms5637_write_command(MS5637_READ_ADC);
        TWI_ERROR_BREAK(s32_retval);
        
        s32_retval = twi_i2c_master_recv_n(MS5637_I2C_CHANNEL, au8_buffer, sizeof(au8_buffer), MS5637_SLAVE_ADD, TWI_TRUE);
        TWI_ERROR_BREAK(s32_retval);
        
        *pu32_adc = ((twi_u32)au8_buffer[0] << 16) | ((twi_u32)au8_buffer[1] << 8) | au8_buffer[2];
        
    }while(0);
    
	return s32_retval;
}
#endif
#if defined(MS5637_PRESS_SENSOR)
/*
 * @brief Reads the temperature and pressure ADC value and compute the compensated pressure value.
 * @param[out] twi_u16* : mbar real pressure value range of reading values from 10 to 1200 mbar(hPa)
 * @param[out] twi_u8*  : mbar fraction pressure value
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
static twi_s32 ms5637_read_pressure(twi_u16 *pu16_press_real,twi_u8 *pu8_press_frac)
{
    twi_s32 s32_retval = TWI_SUCCESS;

    do
    {
        twi_u32 u32_adc_temperature = 0; 
        twi_u32 u32_adc_pressure = 0;
        twi_s32 dT = 0;
        twi_s32 TEMP = 0;
        twi_s64 OFF = 0;
        twi_s64 SENS = 0;
        twi_s64 P = 0;      
        twi_s64 OFF2 = 0;
        twi_s64 SENS2 = 0;
        twi_u8 u8_cmd = 0;
        
        
        if((NULL == pu16_press_real) || (NULL == pu8_press_frac))
        {
            s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
            break;
        }
        
        /* If first time adc is requested, get EEPROM coefficients*/
        if(gb_ms5637_coeff_read == TWI_FALSE)
        {
            s32_retval = ms5637_read_eeprom();
        }
        
        TWI_ERROR_BREAK(s32_retval);

        /* First read temperature*/
        u8_cmd = genu_ms5637_resolution_osr * 2;
        u8_cmd |= MS5637_START_TEMPERATURE_ADC_CONVERSION;

        s32_retval = ms5637_conversion_and_read_adc( u8_cmd, &u32_adc_temperature);
        TWI_ERROR_BREAK(s32_retval);

        /* Now read pressure*/
        u8_cmd = genu_ms5637_resolution_osr * 2;
        u8_cmd |= MS5637_START_PRESSURE_ADC_CONVERSION;
        
        s32_retval = ms5637_conversion_and_read_adc( u8_cmd, &u32_adc_pressure);
        TWI_ERROR_BREAK(s32_retval);
        
        if((u32_adc_temperature == 0) || (u32_adc_pressure == 0))
        {
            s32_retval = TWI_ERROR_INTERNAL_ERROR;
            break;
        }

        // Difference between actual and reference temperature = D2 - Tref
        dT = (twi_s32)u32_adc_temperature - ((twi_s32)gau16_eeprom_coeff[MS5637_REFERENCE_TEMPERATURE_INDEX] <<8 );
        
        // Actual temperature = 2000 + dT * TEMPSENS
        TEMP = 2000 + ((twi_s64)dT * (twi_s64)gau16_eeprom_coeff[MS5637_TEMP_COEFF_OF_TEMPERATURE_INDEX] >> 23) ;
        
        // Second order temperature compensation
        if(TEMP < 2000)
        {          
            OFF2 = 61 * ((twi_s64)TEMP - 2000) * ((twi_s64)TEMP - 2000) / 16 ;
            SENS2 = 29 * ((twi_s64)TEMP - 2000) * ((twi_s64)TEMP - 2000) / 16 ;
            
            if(TEMP < (-1500))
            {
                OFF2 += 17 * ((twi_s64)TEMP + 1500) * ((twi_s64)TEMP + 1500) ;
                SENS2 += 9 * ((twi_s64)TEMP + 1500) * ((twi_s64)TEMP + 1500) ;
            }
        }
        else
        {
            OFF2 = 0 ;
            SENS2 = 0 ;
        }
        
        // OFF = OFF_T1 + TCO * dT
        OFF = ( (twi_s64)(gau16_eeprom_coeff[MS5637_PRESSURE_OFFSET_INDEX]) << 17 ) + ( ( (twi_s64)(gau16_eeprom_coeff[MS5637_TEMP_COEFF_OF_PRESSURE_OFFSET_INDEX]) * dT ) >> 6 ) ;
        OFF -= OFF2 ;
        
        // Sensitivity at actual temperature = SENS_T1 + TCS * dT
        SENS = ( (twi_s64)gau16_eeprom_coeff[MS5637_PRESSURE_SENSITIVITY_INDEX] << 16 ) + ( ((twi_s64)gau16_eeprom_coeff[MS5637_TEMP_COEFF_OF_PRESSURE_SENSITIVITY_INDEX] * dT) >> 7 ) ;
        SENS -= SENS2 ;
        
        // Temperature compensated pressure = D1 * SENS - OFF
        P = ( ( (u32_adc_pressure * SENS) >> 21 ) - OFF ) >> 15 ;
       
        *pu16_press_real = P / 100;
        *pu8_press_frac  = P % 100;

    }while(0);
    
	return s32_retval;
}
#endif

#if defined(MS5637_TEMP_SENSOR)
/*
 * @brief Reads the temperature ADC value and compute the compensated temperature value.
 * @param[out] twi_s16 *  : Celsius Degree temperature value range of reading values from -40 To 85(°C)
 * @return twi_s32 ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
 */
static twi_s32 ms5637_read_temperature(twi_s16 *ps16_temp_val)
{
    twi_s32 s32_retval = TWI_SUCCESS;

    do
    {
        twi_u32 u32_adc_temperature = 0;
        twi_s32 dT = 0;
        twi_s32 TEMP = 0;        
        twi_s64 T2 = 0;       
        twi_u8 u8_cmd = 0;
        
        
        if(NULL == ps16_temp_val)
        {
            s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
            break;
        }
        
        /* If first time adc is requested, get EEPROM coefficients*/
        if(gb_ms5637_coeff_read == TWI_FALSE)
        {
            s32_retval = ms5637_read_eeprom();
        }
        
        TWI_ERROR_BREAK(s32_retval);

        /* First read temperature*/
        u8_cmd = genu_ms5637_resolution_osr * 2;
        u8_cmd |= MS5637_START_TEMPERATURE_ADC_CONVERSION;

        s32_retval = ms5637_conversion_and_read_adc( u8_cmd, &u32_adc_temperature);
        TWI_ERROR_BREAK(s32_retval);
       
        if(u32_adc_temperature == 0)
        {
            s32_retval = TWI_ERROR_INTERNAL_ERROR;
            break;
        }

        // Difference between actual and reference temperature = D2 - Tref
        dT = (twi_s32)u32_adc_temperature - ((twi_s32)gau16_eeprom_coeff[MS5637_REFERENCE_TEMPERATURE_INDEX] <<8 );
        
        // Actual temperature = 2000 + dT * TEMPSENS
        TEMP = 2000 + ((twi_s64)dT * (twi_s64)gau16_eeprom_coeff[MS5637_TEMP_COEFF_OF_TEMPERATURE_INDEX] >> 23) ;
        
        // Second order temperature compensation
        if(TEMP < 2000)
        {
            T2 = ( 3 * ( (int64_t)dT  * (int64_t)dT  ) ) >> 33;         
        }
        else
        {
            T2 = ( 5 * ( (int64_t)dT  * (int64_t)dT  ) ) >> 38;;
        }
    
        *ps16_temp_val = (TEMP - T2 ) / 100;

    }while(0);
    
	return s32_retval;    
}
#endif

#if defined(MS5637_PRESS_SENSOR) || defined (MS5637_TEMP_SENSOR) 
/*
 * @brief	The function that Initializes and enables the sensor with the configuration.
 */
static twi_s32 twi_ms5637_init(void)
{
	twi_s32 s32_retval = TWI_SUCCESS;
    if(TWI_FALSE == gb_ms5637_is_init)
	{
        tstr_twi_i2c_master_config str_i2c;
        
        TWI_MEMSET(&str_i2c, 0, sizeof(tstr_twi_i2c_master_config));
        
        /* Initialize and enable device with config. */
        str_i2c.u8_addr_size = MS5637_I2C_ADD_SIZE;
        str_i2c.u32_clock    = MS5637_I2C_CLOCK;
        str_i2c.u8_pull_up   = GET_I2C_PULL_CFG(MS5637_I2C_CHANNEL);
        
        s32_retval = twi_i2c_master_init(MS5637_I2C_CHANNEL, &str_i2c);
        if(TWI_SUCCESS == s32_retval)
        {
            /* Reset the MS5637 device */
            s32_retval = ms5637_write_command(MS5637_RESET_COMMAND);
            if(TWI_SUCCESS == s32_retval)
            {
                genu_ms5637_resolution_osr = MS5637_RESOLUTION_OSR_512;
                gb_ms5637_is_init =	TWI_TRUE;
                MS5637_SENSOR_LOG("MS5637 Sensor successfully init \r\n");
            }
            else
            {
                MS5637_SENSOR_LOG_ERR("MS5637 Sensor init Error = %d \r\n", s32_retval);
            }
        }
        else
        {
            MS5637_SENSOR_LOG_ERR("MS5637 Sensor init Error = %d \r\n", s32_retval);
        }
    	}
	else
	{
		MS5637_SENSOR_LOG("MS5637 Sensor initialized \r\n");
	}    

	return s32_retval;
}

/*
 * @brief	Function that is used to de-initialize MS5637 Sensor
 */
static twi_s32 twi_ms5637_deinit(void)
{
	twi_s32 s32_retval = TWI_SUCCESS;
    
    if(TWI_TRUE == gb_ms5637_is_init)
    {
        s32_retval = twi_i2c_master_deinit(MS5637_I2C_CHANNEL);
        gb_ms5637_is_init =	TWI_FALSE;
    }
    return s32_retval;
}
#endif
/*
 ****************************************************************************
 ****************************************************************************
 ************************ MS5637 SENSOR APIs ********************************
 ****************************************************************************
 ****************************************************************************
 */


//***********************************************************
/*- APIs IMPLEMENTATION -----------------------------------*/
//***********************************************************
#if defined(MS5637_PRESS_SENSOR) 
/*
 *************************************************************
 *************************************************************
 ***************** PRESSURE SENSOR APIs **********************
 *************************************************************
 *************************************************************
 */

/*
 * @brief	Function that is used to initialize Barometer Pressure Sensor
 */
twi_s32 twi_pressure_sensor_init(void)
{
	return twi_ms5637_init();
}

/*
 * @brief	Function that is used to de-initialize Barometer Pressure Sensor
 */
twi_s32 twi_pressure_sensor_deinit(void)
{
	return twi_ms5637_deinit();
}

/*
 *@brief	Function that calibrate the sensor
 */
twi_s32 twi_pressure_sensor_calib_err_set(twi_s32 s32_press_calib_error)
{
	twi_s32 s32_retval = TWI_ERROR_NOT_SUPPORTED_FEATURE;

	return s32_retval;
}

/*
 *@brief	Function that calibrate the sensor
 */
twi_s32 twi_pressure_sensor_calib_err_get(twi_s32 * ps32_press_calib_error)
{
	twi_s32 s32_retval = TWI_ERROR_NOT_SUPPORTED_FEATURE;

	return s32_retval;
}

/*
 * @brief	Function that is used to read Barometer Pressure Sensor
 */
twi_s32 twi_pressure_sensor_read(twi_u16 *pu16_press_real,twi_u8 *pu8_press_frac)
{
	twi_s32 s32_retval = TWI_SUCCESS;
    
    if((NULL != pu16_press_real) && (NULL != pu8_press_frac))
	{
		if(TWI_TRUE == gb_ms5637_is_init)
		{
            s32_retval = ms5637_read_pressure(pu16_press_real, pu8_press_frac);
		}
		else
		{
			s32_retval = TWI_ERROR_NOT_INITIALIZED;
		}
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	} 

	return s32_retval;
}
#endif

#if defined(MS5637_TEMP_SENSOR)
/*
 *************************************************************
 *************************************************************
 *************** TEMPERATURE SENSOR APIs *********************
 *************************************************************
 *************************************************************
 */
 
/*
 * @brief	Function that is used to initialize Temperature Sensor
 */
twi_s32 twi_temp_sensor_init(void)
{
	return twi_ms5637_init();
}

/*
 * @brief	Function that is used to de-initialize Temperature Sensor
 */
twi_s32 twi_temp_sensor_deinit(void)
{
    return twi_ms5637_deinit();
}

/*
 * @brief	Function that is used to read Temperature Sensor
 */
twi_s32 twi_temp_sensor_read(twi_s16 *ps16_temp_val)
{
	twi_s32 s32_retval = TWI_SUCCESS;
    
    if(NULL != ps16_temp_val)
	{
		if(TWI_TRUE == gb_ms5637_is_init)
		{
            s32_retval = ms5637_read_temperature(ps16_temp_val);
		}
		else
		{
			s32_retval = TWI_ERROR_NOT_INITIALIZED;
		}
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	} 

	return s32_retval;
}

/*
*   @brief      This is a function that dispatch global flags.
*   @param[out]  void.
*   @retval      void.
*/
void twi_temp_sensor_dispatch(void)
{
	/*Do Nothing.*/
}
#endif
