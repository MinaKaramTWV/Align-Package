/****************************************************************************/
/* Copyright (c) 2014 Thirdwayv, Inc. All Rights Reserved. 					*/
/****************************************************************************/

/*
*   @file       twi_rhp_hw_pressure_sensor_handlers.c
*   @brief      This file contains RHAL APIs.
*/

/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/

/*Common include files.*/
#include "twi_debug.h"
#include "twi_common.h"

/*Hardware include files.*/
#include "twi_rhp_hw_pressure_sensor_handlers.h"
#include "twi_pressure_sensor.h"

/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/

#ifdef RHP_HW_SENSOR_LOG_ENABLE
    #define RHP_HW_SENSOR_LOG(...)									TWI_LOGGER("[RHP_SENSOR_ACT]: " __VA_ARGS__)
	#define RHP_HW_SENSOR_LOG_COMBINED(STRING,INT)					TWI_LOGGER("[RHP_SENSOR_ACT]: %s,%d\n", STRING, INT)

	#define RHP_HW_SENSOR_LOG_ERROR(...)							TWI_LOGGER_ERR("[RHP_SENSOR_ACT_ERR]: " __VA_ARGS__)
    #define RHP_HW_SENSOR_LOG_ERROR_COMBINED(STRING, INT)			TWI_LOGGER_ERR("[RHP_SENSOR_ACT_ERR]: %s,%d\n", STRING, INT)
#else
    #define RHP_HW_SENSOR_LOG(...)
	#define RHP_HW_SENSOR_LOG_COMBINED(STRING,INT)

	#define RHP_HW_SENSOR_LOG_ERROR(...)
    #define RHP_HW_SENSOR_LOG_ERROR_COMBINED(STRING, INT)
#endif

/*---------------------------------------------------------*/
/*- GLOBAL STATIC VARIABLES -------------------------------*/
/*---------------------------------------------------------*/

static tstr_twi_rhp_indct_hw* gpstr_indct_hw = NULL;
static tpf_rqst_ntfy_rhp_engn gpf_rqst_ntfy_rhp_engn = NULL;

static twi_u32 gu32_press_calib_ref = 0;

/*---------------------------------------------------------*/
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/*---------------------------------------------------------*/

static twi_s32 twi_rhp_hw_pressure_sensor_init(const tstr_twi_hardware * pstr_hardware,tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn,tstr_twi_rhp_indct_hw* pstr_indct_hw, const tenu_permission enu_permission);
static twi_s32 twi_rhp_hw_pressure_sensor_deinit(const tstr_twi_hardware * pstr_hardware);

static twi_s32 twi_rhp_hw_pressure_interrupt_register(const tstr_twi_hardware * pstr_hardware, tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn, tstr_twi_rhp_indct_hw* pstr_indct_hw);

static twi_s32 twi_rhp_hw_pressure_sensor_read(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src);
static twi_s32 twi_rhp_hw_pressure_calib_err_init(const tstr_twi_hardware * pstr_hardware,tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn,tstr_twi_rhp_indct_hw* pstr_indct_hw, const tenu_permission enu_permission);
static twi_s32 twi_rhp_hw_pressure_calib_err_read(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src);
static twi_s32 twi_rhp_hw_pressure_calib_err_write(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src);
static twi_s32 twi_rhp_hw_pressure_calib_ref_read(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src);
static twi_s32 twi_rhp_hw_pressure_calib_ref_write(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src);

/*---------------------------------------------------------*/
/*- LOCAL STRUCTS AND UNIONS ------------------------------*/
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/*---------------------------------------------------------*/

const tstrt_hardware_handlers estr_pressure_sensor_handlers = {
	/*Pressure SENSOR*/
	twi_rhp_hw_pressure_sensor_init,
	twi_rhp_hw_pressure_sensor_deinit,
	twi_rhp_hw_pressure_sensor_read,
	NULL,
};

const tstrt_hardware_handlers estr_pressure_calib_err_handlers = {
	/* Pressure Err */
	twi_rhp_hw_pressure_calib_err_init,
	NULL,
	twi_rhp_hw_pressure_calib_err_read,
	twi_rhp_hw_pressure_calib_err_write,
};

const tstrt_hardware_handlers estr_pressure_calib_ref_handlers = {
	/* Pressure Ref */
	NULL,
	NULL,
	twi_rhp_hw_pressure_calib_ref_read,
	twi_rhp_hw_pressure_calib_ref_write,
};
/*---------------------------------------------------------*/
/*- LOCAL FUNCTIONS Implementation-------------------------*/
/*---------------------------------------------------------*/

/*
*   @brief      This is function that initialize the pressure sensor subtype.
*   @param[in]  pstr_hardware   Pointer to the hardware structure.
*   @param[in] 	enu_permission	hardware permission.
*   @return     ::TWI_SUCCESS in success and (-ve) error number otherwise.
*/
static twi_s32 twi_rhp_hw_pressure_sensor_init(const tstr_twi_hardware * pstr_hardware,tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn,tstr_twi_rhp_indct_hw* pstr_indct_hw, const tenu_permission enu_permission)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;
    if(NULL != pstr_hardware)
    {
        /*Check if the Hardware is of type digital.*/
        if( (SENSOR == pstr_hardware->enu_type) && (PRESSURE_SENSOR == pstr_hardware->enu_subtype) && (READ_ONLY == enu_permission))
        {
		s32_retval = twi_pressure_sensor_init();
        }
        else
        {
            s32_retval = TWI_ERROR_INVALID_CONFIG;
        }
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }

    return s32_retval;
}

/*
*   @brief      This is function that de-initialize the pressure sensor subtype.
*   @param[in]  pstr_hardware   Pointer to the hardware structure.
*   @return     ::TWI_SUCCESS in success and (-ve) error number otherwise.
*/
static twi_s32 twi_rhp_hw_pressure_sensor_deinit(const tstr_twi_hardware * pstr_hardware)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;

    if(NULL != pstr_hardware)
    {
        /*Check if the Hardware is of type digital.*/
        if((SENSOR == pstr_hardware->enu_type) && (PRESSURE_SENSOR == pstr_hardware->enu_subtype))
        {
            s32_retval = twi_pressure_sensor_deinit();
        }
        else
        {
            s32_retval = TWI_ERROR_INVALID_CONFIG;
        }
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }

    return s32_retval;
}

/*
 *	@brief		This function used for Hardware pressure interrupt registration for RHP
 *
 *	@param[in]	pstr_hardware	Pointer to structure holds hardware specification(type, sub type, options).
 *	@param[in]	pf_hw_interrupt_cb	Pointer to function of callback function for accelerometer interrupt.
 *
 *	@return		Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
 *
 */
static twi_s32 twi_rhp_hw_pressure_interrupt_register(const tstr_twi_hardware * pstr_hardware, tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn, tstr_twi_rhp_indct_hw* pstr_indct_hw)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	if((NULL != pstr_hardware) && (pstr_hardware->enu_type == SENSOR))
	{
		gpf_rqst_ntfy_rhp_engn = pf_rqst_ntfy_rhp_engn;
		gpstr_indct_hw = pstr_indct_hw;
	}
	else 
	{
	}

	return s32_retval;
}
/*
*   @brief      This is function that set the configuration of the pin.
*   @details    To guarantee proper work, that pin has to be selected using
*               twi_gpio_select().
*   @param[in]  u8_port         Port number. It can be ::TWI_PORTA, ::TWI_PORTB, ::TWI_PORTC, or ::TWI_PORTD.
*   @param[in]  u8_pin          Pin number. It in range from ::TWI_PIN0 to ::TWI_PIN7.
*   @param[in]  u8_config       Pin configuration. It can be ::TWI_IN, ::TWI_OUT, ::TWI_PULL_UP, and ::TWI_PULL_DOWN.
*   @return     ::TWI_SUCCESS, ::TWI_ERROR_ALREADY_RELEASED, ::TWI_ERROR_RESOURCE_NOT_FOUND.
*/
static twi_s32 twi_rhp_hw_pressure_sensor_read(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;

    if((NULL != pstr_value) && (NULL != pstr_hardware))
    {
        if((SENSOR == pstr_hardware->enu_type) && (PRESSURE_SENSOR == pstr_hardware->enu_subtype))
        {
		twi_u16 u16_pressure_real;
		twi_u8 u8_pressure_fraction;

		u16_pressure_real = 0;
		u8_pressure_fraction = 0;

		pstr_value->enu_type = U32;
		s32_retval = twi_pressure_sensor_read(&u16_pressure_real,&u8_pressure_fraction);
		if(TWI_SUCCESS == s32_retval)
		{
			pstr_value->enu_type = U32;
			pstr_value->uni_value.u32_int  = MUL100(u16_pressure_real) + u8_pressure_fraction;

			RHP_HW_SENSOR_LOG_COMBINED("pressure Real part = ", u16_pressure_real);
			RHP_HW_SENSOR_LOG_COMBINED("pressure Fraction part = ", u8_pressure_fraction);

			TESTING_LOG_COMBINED("pressure Real part = ", u16_pressure_real);
			TESTING_LOG_COMBINED("pressure Fraction part = ", u8_pressure_fraction);
		}
        }
        else
        {
            s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
        }
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }
 
    return s32_retval;
}

static twi_s32 twi_rhp_hw_pressure_calib_err_init(const tstr_twi_hardware * pstr_hardware,tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn,tstr_twi_rhp_indct_hw* pstr_indct_hw, const tenu_permission enu_permission)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;
    if(NULL != pstr_hardware)
    {
        /*Check if the Hardware is of type digital.*/
	    if((pstr_hardware->enu_type == SENSOR) && (pstr_hardware->enu_subtype == PRESSURE_SENSOR_CALIB_ERR) &&
			    enu_permission == READ_AND_INDICATE)
        {
		s32_retval = twi_rhp_hw_pressure_interrupt_register(pstr_hardware,pf_rqst_ntfy_rhp_engn,pstr_indct_hw);

        }
        else
        {
            s32_retval = TWI_ERROR_INVALID_CONFIG;
        }
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }

    return s32_retval;
}

static twi_s32 twi_rhp_hw_pressure_calib_err_read(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src)
{
	twi_s32 s32_retval;
	twi_s32 s32_press_calib_err;

	s32_retval = TWI_SUCCESS;
	if(NULL != pstr_hardware)
	{
		/*Check if the Hardware is of type sensor.*/
		if((pstr_hardware->enu_type == SENSOR) && (pstr_hardware->enu_subtype == PRESSURE_SENSOR_CALIB_ERR))
		{
			s32_retval = twi_pressure_sensor_calib_err_get(&s32_press_calib_err);
			pstr_value->enu_type = S32;
			pstr_value->uni_value.s32_int = s32_press_calib_err;
		}
		else
		{
			s32_retval = TWI_ERROR_INVALID_CONFIG;
		}
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	}
	s32_retval = TWI_SUCCESS;
	return s32_retval;
}

static twi_s32 twi_rhp_hw_pressure_calib_err_write(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src)
{
	twi_s32 s32_retval;
	twi_s32 s32_press_calib_err;

	s32_retval = TWI_SUCCESS;
	if(NULL != pstr_hardware)
	{
		/*Check if the Hardware is of type sensor.*/
		if((pstr_hardware->enu_type == SENSOR) && (pstr_hardware->enu_subtype == PRESSURE_SENSOR_CALIB_ERR))
		{
			s32_press_calib_err = pstr_value->uni_value.s32_int;

			s32_retval = twi_pressure_sensor_calib_err_set(s32_press_calib_err);
		}
		else
		{
			s32_retval = TWI_ERROR_INVALID_CONFIG;
		}
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	}
	s32_retval = TWI_SUCCESS;
	return s32_retval;
}

static twi_s32 twi_rhp_hw_pressure_calib_ref_read(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;
	if(NULL != pstr_hardware)
	{
		/*Check if the Hardware is of type sensor.*/
		if((pstr_hardware->enu_type == SENSOR) && (pstr_hardware->enu_subtype == PRESSURE_SENSOR_CALIB_REF))
		{
			pstr_value->enu_type = U32;
			pstr_value->uni_value.u32_int = gu32_press_calib_ref;
		}

		else
		{
			s32_retval = TWI_ERROR_INVALID_CONFIG;
		}
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	}
	s32_retval = TWI_SUCCESS;
	return s32_retval;
}

static twi_s32 twi_rhp_hw_pressure_calib_ref_write(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src)
{
	twi_s32 s32_retval;

	twi_u16	u16_press_real_part;
	twi_u8	u8_press_frac_part;
	twi_s32 s32_press_calib_err = 0;

	twi_u32 u32_press_real_part_sum = 0;
	twi_u16 u16_press_frac_part_sum = 0;

	s32_retval = TWI_SUCCESS;
	if(NULL != pstr_hardware)
	{
		/*Check if the Hardware is of type sensor.*/
		if((pstr_hardware->enu_type == SENSOR) && (pstr_hardware->enu_subtype == PRESSURE_SENSOR_CALIB_REF)
				&& (pstr_value->uni_value.u32_int != 0))
		{
			/* reset the calibration error to zero to recalibrate the sensor */
			twi_pressure_sensor_calib_err_set(s32_press_calib_err);

			gu32_press_calib_ref = pstr_value->uni_value.u32_int;
			twi_u8 u8_read_index;
			for(u8_read_index = 0; u8_read_index < 5; u8_read_index++)
			{
				s32_retval = twi_pressure_sensor_read(&u16_press_real_part, &u8_press_frac_part);
				TWI_ASSERT(s32_retval == TWI_SUCCESS);
				u32_press_real_part_sum += u16_press_real_part;
				u16_press_frac_part_sum += u8_press_frac_part;
			}
			
			u16_press_real_part = u32_press_real_part_sum / 5;
			u8_press_frac_part = u16_press_frac_part_sum / 5;

			s32_press_calib_err = gu32_press_calib_ref - ((u16_press_real_part*100) + (u8_press_frac_part%100));
			s32_retval = twi_pressure_sensor_calib_err_set(s32_press_calib_err);

			if(gpf_rqst_ntfy_rhp_engn != NULL)
			{
				twi_u8 u8_profile_index;
				for(u8_profile_index = 0; u8_profile_index < gpstr_indct_hw->u8_indct_hw_cnt; u8_profile_index++)
				{

					if(PRESSURE_SENSOR_CALIB_ERR == gpstr_indct_hw->ppstr_indct_hw_attrs[u8_profile_index]->pstr_hardware->enu_subtype)	
					{
						tstr_notifiy_request str_ntfy_rqst;

						TWI_MEMSET(&str_ntfy_rqst, 0, sizeof(tstr_notifiy_request));

						str_ntfy_rqst.enu_type = ATTR_CHANGED;
						str_ntfy_rqst.pv_data = (void*)gpstr_indct_hw->ppstr_indct_hw_attrs[u8_profile_index];
						((const tstr_twi_rhp_attr*)(str_ntfy_rqst.pv_data))->pstr_value->enu_type = S32;
						((const tstr_twi_rhp_attr*)(str_ntfy_rqst.pv_data))->pstr_value->uni_value.s32_int = s32_press_calib_err;
						gpf_rqst_ntfy_rhp_engn(&str_ntfy_rqst);

						break;

					}
				}
			}
		}

		else
		{
			s32_retval = TWI_ERROR_INVALID_CONFIG;
		}
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	}
	s32_retval = TWI_SUCCESS;
	return s32_retval;
}


/*---------------------------------------------------------*/
/*- APIs IMPLEMENTATION -----------------------------------*/
/*---------------------------------------------------------*/
