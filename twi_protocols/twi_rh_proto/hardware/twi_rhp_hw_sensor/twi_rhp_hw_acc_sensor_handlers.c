/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/*
*   @file       twi_rhp_hw_sensor_handlers.c
*   @brief      This file contains RHAL APIs.
*/

/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/

/*Common include files.*/
#include "twi_debug.h"
#include "twi_common.h"
#include "platform_pins.h"
#include "platform_defines.h"

/*Hardware include files.*/
#include "twi_rhp_hw_acc_sensor_handlers.h"
#include "twi_acc_common_defines.h"
#include "twi_rhp_value.h"
#include "twi_accelerometer.h"
#include "timer_mgmt.h"

/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/

#if defined (TWI_ACC_ENABLE_FIFO_CONTENT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
#define TWI_RHP_HW_ACC_SENSOR_FIFO_MAX_LEVELS_NUM			(TWI_RHP_HW_ACC_SENSOR_FIFO_BUF_SIZE / 3)
#define GET_FIFO_SIZE_FROM_LEVELS_NUM(u8_fifo_levels_num)	(((u8_fifo_levels_num) << 1) + (u8_fifo_levels_num))				/* FIFO Size = FIFO LEVELS * 3. */
#endif

#if defined (TWI_ACC_ENABLE_CONTROL_SHOCK_LEVEL_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
#define ACC_SENSOR_DEFUALT_SHOCK_LEVEL_MG					(4000)
#define ACC_SENSOR_MAX_SHOCK_LEVEL_MG						(8000)
#define ACC_SENSOR_MIN_SHOCK_LEVEL_MG						(1)
#endif

#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
#define ACC_SENSOR_NOT_MOVED_DEFAULT_PERIOD					60000UL
#endif

/*Accelerometer configurations: FS = 8G.*/
#define ACC_SENSOR_FULL_SCALE								ACCELEROMETER_FULL_SCALE_8G			/* While change the default, you must change the following */
#define ACC_SENSOR_FULL_SCALE_MG							(8000)
#define ACC_SENSOR_FULL_SCALE_PRESCALER						(3)																	/* 2^3 = 8. */

#define ACC_SENSOR_MUL_ODR(val)								((val) * gu16_acc_sensor_odr)
#define ACC_SENSOR_DIV_ODR(val)								((val) / gu16_acc_sensor_odr)
#define ACC_SENSOR_FREE_FALL_DUR_CALC()						((gu16_acc_sensor_odr*120)/1000)
#define ACC_SENSOR_SHOCK_DUR_CALC()							((gu16_acc_sensor_odr*200)/1000)

/*Accelerometer Free Fall threshold. This is depending on the Accelerometer configurations.*/
#define ACC_SENSOR_FREE_FALL_THRESHOLD						(6)																	/* (6/128)*8000mG =  375mG. */

/*Accelerometer default values. */
#define ACC_SENSOR_DEFAULT_ODR								(25)
#define ACC_SENSOR_DEFAULT_MOVEMENT_DURATION				(5)																	/* 5/10Hz = 200mSec. */
#define ACC_SENSOR_DEFAULT_SHOCK_LEVEL_DIVIDER				(64)																/* (64/128)*FULL_SCALE = 4G */

#define MOV_DUR_IS_NOT_VALID(u8_movement_dur)				(127 <= ACC_SENSOR_MUL_ODR(u8_movement_dur))
/* Valid notification cause:
 * -------------------------
 * -->	Free Fall,
 * -->	Movement,
 * -->	No Movement,
 * -->	Shock,
 * -->	Shock or Free Fall,
 * -->	Shock or Movement,
 * -->	Shock or No Movement,
 * -->	Movement or No Movement,
 * -->	Shock or Movement or No Movement.
 */
#define ACC_SENSOR_VALID_NOTIFICATION_CAUSE(u8_cause)																							\
		(																																		\
				(!u8_cause)																								||						\
				(u8_cause & (TWI_RHP_HW_ACC_SENSOR_FREE_FALL_NOTIFY))													||						\
				(u8_cause & (TWI_RHP_HW_ACC_SENSOR_MOVEMENT_NOTIFY))													||						\
				(u8_cause & (TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY))													||						\
				(u8_cause & (TWI_RHP_HW_ACC_SENSOR_SHOCK_NOTIFY))														||						\
				(u8_cause & (TWI_RHP_HW_ACC_SENSOR_SHOCK_NOTIFY 		| TWI_RHP_HW_ACC_SENSOR_FREE_FALL_NOTIFY))		||						\
				(u8_cause & (TWI_RHP_HW_ACC_SENSOR_SHOCK_NOTIFY			| TWI_RHP_HW_ACC_SENSOR_MOVEMENT_NOTIFY))		||						\
				(u8_cause & (TWI_RHP_HW_ACC_SENSOR_SHOCK_NOTIFY 		| TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY))	||						\
				(u8_cause & (TWI_RHP_HW_ACC_SENSOR_MOVEMENT_NOTIFY 		| TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY))	||						\
				(u8_cause & (	TWI_RHP_HW_ACC_SENSOR_SHOCK_NOTIFY 		| 																		\
								TWI_RHP_HW_ACC_SENSOR_MOVEMENT_NOTIFY 	|																		\
								TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY	))																	\
		)


#ifdef RHP_HW_SENSOR_LOG_ENABLE
    #define RHP_HW_SENSOR_LOG(...)									TWI_LOGGER("[RHP_SENSOR_ACT]: " __VA_ARGS__)
	#define RHP_HW_SENSOR_LOG_COMBINED(STRING,INT)					TWI_LOGGER_("[RHP_SENSOR_ACT]: %s,%d\n", STRING, INT)

	#define RHP_HW_SENSOR_LOG_ERROR(...)							TWI_LOGGER_ERR("[RHP_SENSOR_ACT_ERR]: " __VA_ARGS__)
    #define RHP_HW_SENSOR_LOG_ERROR_COMBINED(STRING, INT)			TWI_LOGGER_ERR("[RHP_SENSOR_ACT_ERR]: %s,%d\n",STRING, INT)
#else
    #define RHP_HW_SENSOR_LOG(...)
	#define RHP_HW_SENSOR_LOG_COMBINED(STRING,INT)

	#define RHP_HW_SENSOR_LOG_ERROR(...)
    #define RHP_HW_SENSOR_LOG_ERROR_COMBINED(STRING, INT)
#endif

#define MAX_NUM_TRIALS                                      (10)
/*---------------------------------------------------------*/
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/*---------------------------------------------------------*/
static twi_s32 twi_rhp_hw_acc_sensor_init(const tstr_twi_hardware * pstr_hardware,tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn,tstr_twi_rhp_indct_hw* pstr_indct_hw, const tenu_permission enu_permission);
static twi_s32 twi_rhp_hw_acc_sensor_deinit(const tstr_twi_hardware * pstr_hardware);
static twi_s32 twi_rhp_hw_acc_sensor_interrupt_register(	const tstr_twi_hardware * pstr_hardware,
															tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn,
															tstr_twi_rhp_indct_hw* pstr_indct_hw	);
static twi_s32 twi_rhp_hw_acc_sensor_read(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src);
static twi_s32 twi_rhp_hw_acc_sensor_write(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src);
static twi_s32 accelerometer_interrupt(void* pv);
static twi_s32 accelerometer_set_detection_mode(twi_u8 u8_notify);
#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION) || defined (TWI_ACC_ENABLE_CONTROL_SENSITIVITY_FEATURE)
static twi_s32 accelerometer_set_threshold(tenu_accelerometer_sensitivity enu_sense);
#endif
#if defined (TWI_HW_ACC_FULL_FUNCTION) || defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_ACC_ENABLE_CONTROL_ODR_FEATURE) || (TWI_ACC_ENABLE_CONTROL_MOVE_DURATION_FEATURE)
static twi_s32 accelerometer_set_duration(twi_u8 u8_duration_sec);
#endif
#if defined (TWI_ACC_ENABLE_NOTIFICATION_CAUSE_FEATURE) || defined (TWI_ACC_ENABLE_CONTROL_SHOCK_LEVEL_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
static twi_s32 accelerometer_set_shock_level(twi_u16 u16_shock_level_mg);
#endif
static twi_s32 odr_map(twi_u16 odr_value, tenu_twi_accelerometer_odr_cfg* enu_mapped_value);

#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
static void acc_not_moved_timer_cb(void *pv_user_data);
#endif

#if defined (TWI_ACC_ENABLE_TILT_ANGLE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
static twi_u8 calc_tilt_angle(twi_s16 s16_ax, twi_s16 s16_ay, twi_s16 s16_az);
#endif
/*---------------------------------------------------------*/
/*- LOCAL STRUCTS AND UNIONS ------------------------------*/
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/*---------------------------------------------------------*/

#if defined (TWI_ACC_ENABLE_NOTIFICATION_CAUSE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
const tstrt_hardware_handlers estr_acc_sensor_notification_cause_handlers =
{
	/*SENSOR, ACC_SENSOR_NOTIFICATIONS_CAUSE,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	twi_rhp_hw_acc_sensor_write,
};
#endif

#if defined (TWI_ACC_ENABLE_NOTIFICATION_REASON_DETECT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
const tstrt_hardware_handlers estr_acc_sensor_notifications_handlers =
{
	/*SENSOR, ACC_SENSOR_NOTIFICATIONS,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	NULL,
};
#endif

#if defined (TWI_ACC_ENABLE_CONTROL_ODR_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
const tstrt_hardware_handlers estr_acc_sensor_odr_handlers =
{
	/*SENSOR, ACC_SENSOR_ODR,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	twi_rhp_hw_acc_sensor_write,
};
#endif

#if defined (TWI_ACC_ENABLE_CONTROL_SENSITIVITY_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
const tstrt_hardware_handlers estr_acc_sensor_sensitivity_handlers =
{
	/*SENSOR, ACC_SENSOR_SENSITIVITY,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	twi_rhp_hw_acc_sensor_write,
};
#endif

#if defined (TWI_ACC_ENABLE_CONTROL_MOVE_DURATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
const tstrt_hardware_handlers estr_acc_sensor_back_off_sec_handlers =
{
	/*SENSOR, ACC_SENSOR_BACK_OFF_SEC,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	twi_rhp_hw_acc_sensor_write
};
#endif

#if defined (TWI_ACC_ENABLE_CONTROL_SHOCK_LEVEL_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
const tstrt_hardware_handlers estr_acc_sensor_shock_level_handlers =
{
	/*SENSOR, ACC_SENSOR_SHOCK_LEVEL,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	twi_rhp_hw_acc_sensor_write,
};
#endif

#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
const tstrt_hardware_handlers estr_acc_sensor_not_moved_period_handlers =
{
	/*SENSOR, ACC_SENSOR_NOT_MOVED_PERIOD_MS,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	twi_rhp_hw_acc_sensor_write,
};
#endif

#if defined (TWI_ACC_ENABLE_3_AXSIS_ACCELERATION_READING_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
const tstrt_hardware_handlers estr_acc_sensor_x_acc_handlers =
{
	/*SENSOR, ACC_SENSOR_X_ACC,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	NULL,
};
const tstrt_hardware_handlers estr_acc_sensor_y_acc_handlers =
{
	/*SENSOR, ACC_SENSOR_Y_ACC,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	NULL,
};
const tstrt_hardware_handlers estr_acc_sensor_z_acc_handlers =
{
	/*SENSOR, ACC_SENSOR_Z_ACC,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	NULL,
};
#endif

#if defined (TWI_ACC_ENABLE_FIFO_CONTENT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
const tstrt_hardware_handlers estr_acc_sensor_fifo_content_handlers =
{
	/*SENSOR, ACC_SENSOR_FIFO_CONTENT,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	NULL,
};
const tstrt_hardware_handlers estr_acc_sensor_num_of_fifo_levels_handlers =
{
	/*SENSOR, ACC_SENSOR_NUM_OF_FIFO_LEVELS,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	NULL,
};
#endif

#if defined (TWI_ACC_ENABLE_TILT_ANGLE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
const tstrt_hardware_handlers estr_acc_sensor_tilt_angle_handlers =
{
	/*SENSOR, ACC_SENSOR_TILT_ANGLE,*/
	twi_rhp_hw_acc_sensor_init,
	twi_rhp_hw_acc_sensor_deinit,
	twi_rhp_hw_acc_sensor_read,
	NULL,
};
#endif
#if defined (TWI_ACC_ENABLE_CONFIGRATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
const tstrt_hardware_handlers estr_acc_sensor_configration_handlers =
{
	/*SENSOR, ACC_SENSOR_CONFIGRATION,*/
	twi_rhp_hw_acc_sensor_init,
	NULL,
	twi_rhp_hw_acc_sensor_read,
	twi_rhp_hw_acc_sensor_write,
};
#endif
/*---------------------------------------------------------*/
/*- GLOBAL STATIC VARIABLES -------------------------------*/
/*---------------------------------------------------------*/

static volatile twi_bool 						gb_get_notification_cause       = TWI_FALSE;
static twi_bool 								gb_disable_interrupt_handling   = TWI_FALSE;
static twi_bool 								gb_acc_initialized              = TWI_FALSE;
#if defined (TWI_HW_ACC_FULL_FUNCTION) || defined (TWI_ACC_ENABLE_CONTROL_SENSITIVITY_FEATURE) || defined (TWI_ACC_ENABLE_NOTIFICATION_CAUSE_FEATURE)
static tenu_accelerometer_sensitivity 			genu_sensitivty         		= DEFAULT_SENSE;
#endif
#if defined (TWI_HW_ACC_FULL_FUNCTION) || defined (TWI_ACC_ENABLE_CONTROL_MOVE_DURATION_FEATURE) || defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_ACC_ENABLE_CONTROL_ODR_FEATURE)
static twi_u8 									gu8_movement_duration_sec    	= 0;
#endif
static twi_u8 									gu8_notification_cause			= TWI_RHP_HW_ACC_SENSOR_NO_NOTIFY;
static twi_u8 									gu8_notification				= 0;
#if defined (TWI_ACC_ENABLE_CONTROL_SHOCK_LEVEL_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
static twi_u16 									gu16_shock_level_mg				= 0;
#endif

static tstr_twi_rhp_indct_hw*					gpstr_indct_hw;
static tpf_rqst_ntfy_rhp_engn  					gpf_rqst_ntfy_rhp_engn;

#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
static volatile twi_bool 						gb_not_moved_notification       = TWI_FALSE;
static twi_u32 									gu32_acc_not_moved_period		= ACC_SENSOR_NOT_MOVED_DEFAULT_PERIOD;
static tstr_timer_mgmt_timer 					gstr_acc_not_moved_timer;
#endif

#if defined (TWI_ACC_ENABLE_FIFO_CONTENT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
static tstr_twi_acc_fifo_content TWI_ALIGN		gstr_acc_fifo_content			= {	.u16_fifo_levels_num 	= 0,
																					.as16_acc_fifo_content 	= {0}	};
#endif

static twi_u16 gu16_acc_sensor_odr = ACC_SENSOR_DEFAULT_ODR;				/*default Output Data Rate is 25 Hz*/
static twi_u8 gu8_acc_sensor_shock_duration ;		/*5/25HZ = 200 msec*/
static twi_u8 gu8_acc_sensor_free_fall_duration ;	/*3/25HZ = 120 msec*/
static twi_bool gb_handle_re_config_acc = TWI_FALSE;
static twi_bool gb_handle_acc_config_check = TWI_FALSE;
/*---------------------------------------------------------*/
/*- LOCAL FUNCTIONS Implementation-------------------------*/
/*---------------------------------------------------------*/

static twi_bool is_acc_hw(const tstr_twi_hardware* pstr_hardware)
{
	twi_bool b_ret = TWI_FALSE;

	if ((SENSOR == pstr_hardware->enu_type)||(WAKE_UP_SENSOR == pstr_hardware->enu_type))
	{
		switch (pstr_hardware->enu_subtype)
		{
		#if (defined (TWI_ACC_ENABLE_NOTIFICATION_CAUSE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION))
			case ACC_SENSOR_NOTIFICATIONS:
		#endif
		#if defined (TWI_ACC_ENABLE_NOTIFICATION_REASON_DETECT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_NOTIFICATIONS_CAUSE:
		#endif
        #if defined (TWI_ACC_ENABLE_CONFIGRATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_CONFIGRATION:
        #endif
		#if defined (TWI_ACC_ENABLE_CONTROL_ODR_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_ODR:
		#endif
		#if defined (TWI_ACC_ENABLE_CONTROL_SENSITIVITY_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_SENSITIVITY:
		#endif
		#if defined (TWI_ACC_ENABLE_CONTROL_MOVE_DURATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_MOVEMENT_DURATION_SEC:
		#endif
		#if defined (TWI_ACC_ENABLE_CONTROL_SHOCK_LEVEL_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_SHOCK_LEVEL:
		#endif
		#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_NOT_MOVED_PERIOD_MS:
		#endif
		#if defined (TWI_ACC_ENABLE_3_AXSIS_ACCELERATION_READING_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_X_ACC:
		case ACC_SENSOR_Y_ACC:
		case ACC_SENSOR_Z_ACC:
		#endif
		#if defined (TWI_ACC_ENABLE_FIFO_CONTENT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_FIFO_CONTENT:
		case ACC_SENSOR_NUM_OF_FIFO_LEVELS:
		#endif
		#if defined (TWI_ACC_ENABLE_TILT_ANGLE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_TILT_ANGLE:
		#endif
			b_ret = TWI_TRUE;
			break;
		default:
			break;
		}
	}
	else
	{
		/* code */
	}	
	return (b_ret);
}

static twi_s32 twi_acc_sensor_init(void)
{
    twi_s32 s32_retval = TWI_SUCCESS;

    s32_retval = twi_accelerometer_init(accelerometer_interrupt);
    if(TWI_SUCCESS == s32_retval)
    {
        s32_retval = twi_accelerometer_set_full_scale(ACC_SENSOR_FULL_SCALE);
        if(TWI_SUCCESS == s32_retval)
        {
            s32_retval = accelerometer_set_detection_mode(gu8_notification_cause);
            if(TWI_SUCCESS == s32_retval)
            {
                tenu_twi_accelerometer_odr_cfg enu_mapped_odr;
                s32_retval = odr_map(gu16_acc_sensor_odr, &enu_mapped_odr);
                if(TWI_SUCCESS == s32_retval)
                {
                    s32_retval = twi_accelerometer_set_data_rate_config(enu_mapped_odr);
                    if(TWI_SUCCESS == s32_retval)
                    {
                        gu8_acc_sensor_shock_duration = ACC_SENSOR_SHOCK_DUR_CALC();
                        gu8_acc_sensor_free_fall_duration = ACC_SENSOR_FREE_FALL_DUR_CALC();
#if defined (TWI_ACC_ENABLE_CONTROL_SHOCK_LEVEL_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
                        s32_retval = twi_accelerometer_set_shock_duration(gu8_acc_sensor_shock_duration);
#endif
                    }
                }
                else
                {
                    /*Do Nothing*/
                }
            }
        }
    }
    else
    {
        RHP_HW_SENSOR_LOG_ERROR("ACCELEROMETER INIT ERROR\n");
    }

    return s32_retval;
}

static twi_s32 twi_acc_sensor_re_init(void)
{
    twi_s32 s32_retval = TWI_SUCCESS;
    s32_retval = twi_accelerometer_deinit();
    if(TWI_SUCCESS == s32_retval)
    {
        gu8_notification            = 0;
        gu16_acc_sensor_odr 	    = ACC_SENSOR_DEFAULT_ODR;
        gu8_notification_cause 	    = TWI_RHP_HW_ACC_SENSOR_NO_NOTIFY;
        gb_get_notification_cause   = TWI_FALSE;
        s32_retval = twi_acc_sensor_init();
    }
    return s32_retval;
}

static void twi_twi_acc_sensor_event(twi_u8 u8_op_code)
{
    tstr_notifiy_request str_ntfy_rqst;
    tstr_handler_rqst_app str_handler_rqst_app;
    
    TWI_MEMSET(&str_handler_rqst_app, 0, sizeof(tstr_handler_rqst_app));
    TWI_MEMSET(&str_ntfy_rqst, 0, sizeof(tstr_notifiy_request));
    
    str_handler_rqst_app.enu_handler = ACCELEROMETER_HW;
    str_handler_rqst_app.u8_opcode = (twi_u8)(u8_op_code);
    str_handler_rqst_app.pv_data = NULL;
    
    str_ntfy_rqst.pv_data = (void *)&str_handler_rqst_app;
    str_ntfy_rqst.enu_type = HANDLER_RQST_APP;

    (void)gpf_rqst_ntfy_rhp_engn(&str_ntfy_rqst);
}
/*-*****************************************************************************
* Function Name: twi_rhp_hw_acc_sensor_init				   		   				*
*-******************************************************************************
*	@function	twi_s32 twi_rhp_hw_acc_sensor_init(const tstr_twi_hardware * pstr_hardware, const tenu_permission enu_permission)
*
*	@brief		This function used for initialization for Hardware accelerometer for RHP
*
*	@param[in]	pstr_hardware	Pointer to structure holds hardware specification(type, sub type, options).
*
*	@param[in]	enu_permission	permission for H/W can do.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
static twi_s32 twi_rhp_hw_acc_sensor_init(const tstr_twi_hardware * pstr_hardware,tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn,tstr_twi_rhp_indct_hw* pstr_indct_hw, const tenu_permission enu_permission)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;

    if(NULL != pstr_hardware)
    {
        /*Check if the Hardware is of type Sensor.*/
        if(TWI_TRUE == is_acc_hw(pstr_hardware))
        {
        	if(TWI_FALSE == gb_acc_initialized)
        	{
				gb_acc_initialized = TWI_TRUE;
				s32_retval = twi_acc_sensor_init();
        	}
			else
			{
				/*s32_retval = TWI_ERROR_ALREADY_INITIALIZED;*/
			}
			twi_rhp_hw_acc_sensor_interrupt_register(pstr_hardware,pf_rqst_ntfy_rhp_engn,pstr_indct_hw);
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

/*-*****************************************************************************
* Function Name: twi_rhp_hw_acc_sensor_deinit				   		   			   *
*-******************************************************************************
*	@function	twi_s32 twi_rhp_hw_acc_sensor_deinit(const tstr_twi_hardware * pstr_hardware)
*
*	@brief		This function used for de-initialization for Hardware accelerometer for RHP
*
*	@param[in]	pstr_hardware	Pointer to structure holds hardware specification(type, sub type, options).
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
static twi_s32 twi_rhp_hw_acc_sensor_deinit(const tstr_twi_hardware * pstr_hardware)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;

    if(NULL != pstr_hardware)
    {
        /*Check if the Hardware is of type Sensor.*/
        if(TWI_TRUE == is_acc_hw(pstr_hardware))
        {
        	if(TWI_TRUE == gb_acc_initialized)
        	{
				gb_acc_initialized = TWI_FALSE;
				s32_retval = twi_accelerometer_deinit();
				if(TWI_SUCCESS == s32_retval)
				{
					/* Do nothing (return with success) */
					/* User must set the notification cause */
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

    return s32_retval;
}
/*-*****************************************************************************
* Function Name: twi_rhp_hw_acc_sensor_interrupt_register	   		   			*
*-******************************************************************************
*	@function	twi_s32 twi_rhp_hw_acc_sensor_interrupt_register(const tstr_twi_hardware * pstr_hardware, tpf_twi_hw_interrupt_cb pf_hw_interrupt_cb, void * pv)
*
*	@brief		This function used for Hardware accelerometer sensor interrupt registration for RHP
*
*	@param[in]	pstr_hardware	Pointer to structure holds hardware specification(type, sub type, options).
*
*	@param[in]	pf_hw_interrupt_cb	Pointer to function of callback function for accelerometer interrupt.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
static twi_s32 twi_rhp_hw_acc_sensor_interrupt_register(	const tstr_twi_hardware * pstr_hardware,
															tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn,
															tstr_twi_rhp_indct_hw* pstr_indct_hw	)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;
    
    if((NULL != pstr_hardware) &&
		((SENSOR == pstr_hardware->enu_type) || (WAKE_UP_SENSOR == pstr_hardware->enu_type)) 
#if defined (TWI_ACC_ENABLE_NOTIFICATION_REASON_DETECT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)        
        && (ACC_SENSOR_NOTIFICATIONS == pstr_hardware->enu_subtype)
#endif	
        )
    {
		gpf_rqst_ntfy_rhp_engn = pf_rqst_ntfy_rhp_engn;
		gpstr_indct_hw = pstr_indct_hw;
    }
    else 
    {
    }

    return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_rhp_hw_acc_sensor_read				   		   				*
*-******************************************************************************
*	@function	twi_s32 twi_rhp_hw_acc_sensor_read(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src)
*
*	@brief		This function used for read the members of the accelerometer sensor.
*
*	@param[in]	pstr_hardware	Pointer to structure holds hardware specification(type, sub type, options).
*
*	@param[in]	pstr_value	Pointer to function of callback function for accelerometer interrupt.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
static twi_s32 twi_rhp_hw_acc_sensor_read(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;

    if((NULL != pstr_value) && (NULL != pstr_hardware))
    {
    	switch(pstr_hardware->enu_subtype)
    	{
#if defined (TWI_ACC_ENABLE_NOTIFICATION_CAUSE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
			case ACC_SENSOR_NOTIFICATIONS_CAUSE:
				pstr_value->enu_type = U8;
				pstr_value->uni_value.u8_int = gu8_notification_cause;
				break;
#endif
#if defined (TWI_ACC_ENABLE_NOTIFICATION_REASON_DETECT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
			case ACC_SENSOR_NOTIFICATIONS:
				pstr_value->enu_type = U8;
				pstr_value->uni_value.u8_int = gu8_notification;
                /*Self clear the notification.*/
				gu8_notification = 0;
				break; 
#endif
#if defined (TWI_ACC_ENABLE_CONFIGRATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
			case ACC_SENSOR_CONFIGRATION:
            {
				if(pstr_value->enu_type == HEX)
				{
					if((pstr_value->uni_value.str_hex_array.u16_len == sizeof(tstr_acc_config)) && (pstr_value->uni_value.str_hex_array.pu8_data != NULL))
					{
						tstr_acc_config* pstr_acc_config = (tstr_acc_config*)pstr_value->uni_value.str_hex_array.pu8_data;
						switch (pstr_acc_config->enu_acc_config_type)
						{
						case ACC_HARDWARE_CONFIG:
						{
							twi_bool b_validity;
							s32_retval = twi_accelerometer_check_validity_config(&b_validity);

							if (TWI_SUCCESS == s32_retval)
							{
								if (ACC_CONFIG_NOT_VALID == b_validity)
								{
									gb_handle_re_config_acc = TWI_TRUE;
								}
								pstr_value->enu_type = BOOLEAN;
								pstr_value->uni_value.b_boolean = b_validity;
							}
							else
							{
								gb_handle_acc_config_check = TWI_TRUE;
							}
							break;
						}
						
						case ACC_INTERRUPT_HANDLING:
						{
							s32_retval = TWI_ERROR_NOT_SUPPORTED_FEATURE;
							break;
						}
						
						default:
						{
							s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
							break;
						}
						}
					}
				}
				else
				{
					s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
				}
				break;
            }                
#endif
#if defined (TWI_ACC_ENABLE_CONTROL_ODR_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
            case ACC_SENSOR_ODR:
                pstr_value->enu_type = U16;
                pstr_value->uni_value.u16_int = gu16_acc_sensor_odr;
                break;  
#endif
#if defined (TWI_ACC_ENABLE_CONTROL_SENSITIVITY_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
			case ACC_SENSOR_SENSITIVITY:
				pstr_value->enu_type = U8;
				pstr_value->uni_value.u8_int = genu_sensitivty;
				break;
#endif
#if defined (TWI_ACC_ENABLE_CONTROL_MOVE_DURATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
			case ACC_SENSOR_MOVEMENT_DURATION_SEC:
				pstr_value->enu_type = U8;
				pstr_value->uni_value.u8_int = gu8_movement_duration_sec;
				break;
#endif
#if defined (TWI_ACC_ENABLE_CONTROL_SHOCK_LEVEL_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
			case ACC_SENSOR_SHOCK_LEVEL:
				pstr_value->enu_type = U16;
				pstr_value->uni_value.u16_int = gu16_shock_level_mg;
				break;
#endif
#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
			case ACC_SENSOR_NOT_MOVED_PERIOD_MS:
				pstr_value->enu_type = U32;
				pstr_value->uni_value.u32_int = gu32_acc_not_moved_period;
				break;
#endif
#if defined (TWI_ACC_ENABLE_3_AXSIS_ACCELERATION_READING_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
			case ACC_SENSOR_X_ACC:
				pstr_value->enu_type = S16;
				s32_retval = twi_accelerometer_get_axis_acc(ACCELEROMTER_X_AXIS_ACCELERATION, (twi_s16*)&(pstr_value->uni_value.s16_int));
				break;
			case ACC_SENSOR_Y_ACC:
				pstr_value->enu_type = S16;
				s32_retval = twi_accelerometer_get_axis_acc(ACCELEROMTER_Y_AXIS_ACCELERATION, (twi_s16*)&(pstr_value->uni_value.s16_int));
				break;
			case ACC_SENSOR_Z_ACC:
				pstr_value->enu_type = S16;
				s32_retval = twi_accelerometer_get_axis_acc(ACCELEROMTER_Z_AXIS_ACCELERATION, (twi_s16*)&(pstr_value->uni_value.s16_int));
				break;
#endif
#if defined (TWI_ACC_ENABLE_FIFO_CONTENT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
			case ACC_SENSOR_FIFO_CONTENT:
			{
				twi_u8 u8_i;
				
				pstr_value->enu_type = HEX;
				gstr_acc_fifo_content.u16_fifo_levels_num = 0;
				s32_retval = twi_accelerometer_get_fifo_content(	TWI_RHP_HW_ACC_SENSOR_FIFO_MAX_LEVELS_NUM,
																	gstr_acc_fifo_content.as16_acc_fifo_content,
																	(twi_u8*)(&(gstr_acc_fifo_content.u16_fifo_levels_num))	);
				TESTING_LOG_COMBINED("# of FIFO levels =", gstr_acc_fifo_content.u16_fifo_levels_num);
				/* Pad the FIFO Buffer with zeros. */
				for(u8_i = GET_FIFO_SIZE_FROM_LEVELS_NUM(gstr_acc_fifo_content.u16_fifo_levels_num); u8_i < TWI_RHP_HW_ACC_SENSOR_FIFO_BUF_SIZE; u8_i++)
				{
					gstr_acc_fifo_content.as16_acc_fifo_content[u8_i] = 0;
				}

				pstr_value->uni_value.str_hex_array.u16_len = sizeof(gstr_acc_fifo_content);
				pstr_value->uni_value.str_hex_array.pu8_data = (twi_u8*)&gstr_acc_fifo_content;
				TESTING_LOG_HEX("ACC FIFO Content = ", pstr_value->uni_value.str_hex_array.pu8_data, pstr_value->uni_value.str_hex_array.u16_len);
				break;
			}
			case ACC_SENSOR_NUM_OF_FIFO_LEVELS:
			{
				pstr_value->enu_type = U8;
				s32_retval = twi_accelerometer_get_num_of_fifo_levels((twi_u8*)&pstr_value->uni_value.u8_int);
				break;
			}
#endif
#if defined (TWI_ACC_ENABLE_TILT_ANGLE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
			case ACC_SENSOR_TILT_ANGLE:
			{
				twi_s16 s16_ax;
				twi_s16 s16_ay;
				twi_s16 s16_az;
				twi_s16 s16_temp;

				pstr_value->enu_type = U8;

				twi_accelerometer_get_axis_acc(ACCELEROMTER_X_AXIS_ACCELERATION, &s16_ax);
				twi_accelerometer_get_axis_acc(ACCELEROMTER_Y_AXIS_ACCELERATION, &s16_ay);
				twi_accelerometer_get_axis_acc(ACCELEROMTER_Z_AXIS_ACCELERATION, &s16_az);
				
				switch(pstr_hardware->uni_init_options.acc_sensor_tilt_angle_init_options.enu_accelerometer_alignment)
				{
				case PSITIVE_X_UP:
					/*Swap Z Direction with X Direction.*/
					s16_temp 	= s16_ax;
					s16_ax 		= s16_az;
					s16_az 		= s16_temp;
					break;
				case NEGATIVE_X_UP:
					/*Swap Z Direction with -X Direction.*/
					s16_temp 	= -s16_ax;
					s16_ax 		= s16_az;
					s16_az 		= s16_temp;
					break;
				case PSITIVE_Y_UP:
					/*Swap Z Direction with Y Direction.*/
					s16_temp 	= s16_ay;
					s16_ay 		= s16_az;
					s16_az 		= s16_temp;
					break;
				case NEGATIVE_Y_UP:
					/*Swap Z Direction with -Y Direction.*/
					s16_temp 	= -s16_ay;
					s16_ay 		= s16_az;
					s16_az 		= s16_temp;
					break;
				case PSITIVE_Z_UP:
					/*Do Nothing as calc_tilt_angle() assume that +Z Direction is Up.*/
					break;
				case NEGATIVE_Z_UP:
					/*Invert Z Direction.*/
					s16_az = -s16_az;
					break;
				default:
					/*Do Nothing*/
					break;
				}
				pstr_value->uni_value.u8_int = calc_tilt_angle(s16_ax, s16_ay, s16_az);
				TESTING_LOG_COMBINED("Tilt Angle = ", pstr_value->uni_value.u8_int);
				break;
			}
#endif
			default:
				s32_retval = TWI_ERROR_INVALID_CONFIG;
				break;
    	}
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }

    return s32_retval;
}

/*-*****************************************************************************
* Function Name: twi_rhp_hw_acc_sensor_write				   		   			*
*-******************************************************************************
*	@function	twi_s32 twi_rhp_hw_acc_sensor_write(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src)
*
*	@brief		This function used for write the members of the accelerometer sensor.
*
*	@param[in]	pstr_hardware	Pointer to structure holds hardware specification(type, sub type, options).
*
*	@param[in]	pstr_value	Pointer to the value to write it.
*
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
*
*
*
*******************************************************************************/
static twi_s32 twi_rhp_hw_acc_sensor_write(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;

    if((NULL != pstr_value) && (NULL != pstr_hardware))
    {
    	switch(pstr_hardware->enu_subtype)
    	{
#if defined (TWI_ACC_ENABLE_CONFIGRATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
			case ACC_SENSOR_CONFIGRATION:
            {
				if(pstr_value->enu_type == HEX)
				{
					if((pstr_value->uni_value.str_hex_array.u16_len == sizeof(tstr_acc_config)) && (pstr_value->uni_value.str_hex_array.pu8_data != NULL))
					{
						tstr_acc_config* pstr_acc_config = (tstr_acc_config*)pstr_value->uni_value.str_hex_array.pu8_data;
						switch (pstr_acc_config->enu_acc_config_type)
						{
						case ACC_HARDWARE_CONFIG:
						{
							s32_retval = TWI_ERROR_NOT_SUPPORTED_FEATURE;
							break;
						}
						
						case ACC_INTERRUPT_HANDLING:
						{
							gb_disable_interrupt_handling = pstr_acc_config->uni_config.b_disable_interrupt_handling;
							break;
						}
						
						default:
						{
							s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
							break;
						}
						}
					}
				}
				else
				{
					s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
				}
				break;
            }                
#endif
#if defined (TWI_ACC_ENABLE_NOTIFICATION_CAUSE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_NOTIFICATIONS_CAUSE:
			if(ACC_SENSOR_VALID_NOTIFICATION_CAUSE(pstr_value->uni_value.u8_int))
			{
				if(gu8_notification_cause != pstr_value->uni_value.u8_int)
				{
					s32_retval = accelerometer_set_detection_mode(TWI_RHP_HW_ACC_SENSOR_NO_NOTIFY);
					if(TWI_SUCCESS == s32_retval)
					{
						gu8_notification_cause = pstr_value->uni_value.u8_int;
#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
						stop_timer(&gstr_acc_not_moved_timer);
#endif
						if((gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_MOVEMENT_NOTIFY) || (gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY))
						{
							/*Re-set the sensitivity and duration according to the used definitions.*/
							s32_retval = accelerometer_set_threshold(genu_sensitivty);
							s32_retval = accelerometer_set_duration(gu8_movement_duration_sec);
						}
						else if(gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_FREE_FALL_NOTIFY)
						{
							/*Re-set the sensitivity and duration according to the Free Fall conditions.*/
							s32_retval = twi_accelerometer_set_interrupt_thershold(ACC_SENSOR_FREE_FALL_THRESHOLD);
							s32_retval = twi_accelerometer_set_interrupt_duration(gu8_acc_sensor_free_fall_duration);
						}
						if(gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_SHOCK_NOTIFY)
						{
							/*Re-set the shock level according to the user definitions.*/
							#if defined (TWI_ACC_ENABLE_CONTROL_SHOCK_LEVEL_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
							s32_retval = accelerometer_set_shock_level(gu16_shock_level_mg);
							#else
							s32_retval = accelerometer_set_shock_level(pstr_hardware->uni_init_options.acc_config.u16_acc_shock_th_mg);
							#endif
						}

#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
						if(gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY)
						{
							start_timer(&gstr_acc_not_moved_timer, (twi_s8*)"ACC_NOT_MOVED_TIMER", TWI_TIMER_TYPE_PERIODIC,
																		gu32_acc_not_moved_period, acc_not_moved_timer_cb, NULL);
						}
#endif
						s32_retval = accelerometer_set_detection_mode(gu8_notification_cause);
					}
					else
					{
						s32_retval = TWI_ERROR_INVALID_CONFIG;
					}
				}
				else
				{
					s32_retval = TWI_ERROR_ALREADY_SET;
				}
			}
			else
			{
				s32_retval = TWI_ERROR_INVALID_CONFIG;
			}
			break;
#endif        
#if defined (TWI_ACC_ENABLE_CONTROL_ODR_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
    	case ACC_SENSOR_ODR:
    		if(0 == pstr_value->uni_value.u16_int)
    		{
    			/*default value*/
    		    pstr_value->uni_value.u16_int = ACC_SENSOR_DEFAULT_ODR;
    		}
    		if( gu16_acc_sensor_odr == pstr_value->uni_value.u16_int )
    		{
    			s32_retval = TWI_ERROR_ALREADY_SET;
    		}
    		else
    		{
    			tenu_twi_accelerometer_odr_cfg enu_mapped_odr;
    			s32_retval = odr_map(pstr_value->uni_value.u16_int, &enu_mapped_odr);
    			if(TWI_SUCCESS == s32_retval)
    			{
					s32_retval = twi_accelerometer_set_data_rate_config(enu_mapped_odr);
					if(TWI_SUCCESS == s32_retval)
					{
						twi_u8 u8_temp;

						gu16_acc_sensor_odr = pstr_value->uni_value.u16_int;
						gu8_acc_sensor_free_fall_duration = ACC_SENSOR_FREE_FALL_DUR_CALC();
						u8_temp = ACC_SENSOR_SHOCK_DUR_CALC();
						s32_retval = twi_accelerometer_set_shock_duration(u8_temp);
						if(TWI_SUCCESS == s32_retval)
						{
							gu8_acc_sensor_shock_duration = u8_temp;
							if(MOV_DUR_IS_NOT_VALID(gu8_movement_duration_sec))
							{
								gu8_movement_duration_sec = 127 / gu16_acc_sensor_odr;
							}
							if((gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_MOVEMENT_NOTIFY) || (gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY))
							{
								/*Re-set the duration according to the used definitions.*/
								s32_retval = accelerometer_set_duration(gu8_movement_duration_sec);
							}
							else if(gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_FREE_FALL_NOTIFY)
							{
								u8_temp = ACC_SENSOR_FREE_FALL_DUR_CALC();
								/*Re-set the duration according to the Free Fall conditions.*/
								s32_retval = twi_accelerometer_set_interrupt_duration(gu8_acc_sensor_free_fall_duration);
							}
						}
						else
						{
							/*Do Nothing*/
						}
					}
					else
					{
						/*DO Nothing*/
					}
    			}
    			else
    			{
    				/*DO Nothing*/
    			}
    		}
    		break;
#endif
#if defined (TWI_ACC_ENABLE_CONTROL_SENSITIVITY_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_SENSITIVITY:
        	/*Apply the sensitivity only if the notification cause is MOVEMENT_NOTIFY or NO_MOVEMENT_NTIFY.*/
			if(genu_sensitivty != pstr_value->uni_value.u8_int)
			{
				if((gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_MOVEMENT_NOTIFY) ||(gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY))
				{
					s32_retval = accelerometer_set_threshold((tenu_accelerometer_sensitivity)pstr_value->uni_value.u8_int);
				}
				if(TWI_SUCCESS == s32_retval)
				{
					genu_sensitivty = (tenu_accelerometer_sensitivity)pstr_value->uni_value.u8_int;
				}
				else
				{
					s32_retval = TWI_ERROR_INVALID_CONFIG;
				}
			}
			else
			{
				s32_retval = TWI_ERROR_ALREADY_SET;
			}
			break;            
#endif
#if defined (TWI_ACC_ENABLE_CONTROL_MOVE_DURATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_MOVEMENT_DURATION_SEC:
			if(gu8_movement_duration_sec != pstr_value->uni_value.u8_int)
			{
				if(MOV_DUR_IS_NOT_VALID(pstr_value->uni_value.u8_int))
				{
					pstr_value->uni_value.u8_int = (127 / gu16_acc_sensor_odr);
				}
				if((gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_MOVEMENT_NOTIFY) ||(gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY))
				{
					s32_retval = accelerometer_set_duration(pstr_value->uni_value.u8_int);
				}
				if(TWI_SUCCESS == s32_retval)
				{
					gu8_movement_duration_sec = pstr_value->uni_value.u8_int;
				}
				else
				{
					s32_retval = TWI_ERROR_INVALID_CONFIG;
				}
			}
			else
			{
				s32_retval = TWI_ERROR_ALREADY_SET;
			}
			break;           
#endif
#if defined (TWI_ACC_ENABLE_CONTROL_SHOCK_LEVEL_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_SHOCK_LEVEL:
			if((ACC_SENSOR_MIN_SHOCK_LEVEL_MG > pstr_value->uni_value.u16_int) || (ACC_SENSOR_MAX_SHOCK_LEVEL_MG < pstr_value->uni_value.u16_int))
			{
			    /*default value*/
				pstr_value->uni_value.u16_int = ACC_SENSOR_DEFUALT_SHOCK_LEVEL_MG;
			}
			if(gu16_shock_level_mg != pstr_value->uni_value.u16_int)
			{
				/*Apply the shock level only if the notification cause is SHOCK_NOTIFY.*/
				if(gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_SHOCK_NOTIFY)
				{
					s32_retval = accelerometer_set_shock_level(pstr_value->uni_value.u16_int);
				}
				if(TWI_SUCCESS == s32_retval)
				{
					gu16_shock_level_mg = pstr_value->uni_value.u16_int;
				}
				else
				{
					s32_retval = TWI_ERROR_INVALID_CONFIG;
				}
			}
			else
			{
				s32_retval = TWI_ERROR_ALREADY_SET;
			}
			break;
#endif
#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
		case ACC_SENSOR_NOT_MOVED_PERIOD_MS:
			if(gu32_acc_not_moved_period != pstr_value->uni_value.u32_int)
			{
				gu32_acc_not_moved_period = pstr_value->uni_value.u32_int;
				stop_timer(&gstr_acc_not_moved_timer);
				if(gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY)
				{
					start_timer(&gstr_acc_not_moved_timer, (twi_s8*)"ACC_NOT_MOVED_TIMER", TWI_TIMER_TYPE_PERIODIC,
																gu32_acc_not_moved_period, acc_not_moved_timer_cb, NULL);
				}
        	}
			else
			{
				s32_retval = TWI_ERROR_ALREADY_SET;
			}
			break;
#endif            
		default:
			s32_retval = TWI_ERROR_INVALID_CONFIG;
			break;
    	}
    }
    else
    {
        s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
    }

    return s32_retval;
}

#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
static void acc_not_moved_timer_cb(void *pv_user_data)
{
  twi_u8 u8_i;
	tstr_notifiy_request	str_ntfy_rqst;
	
	TWI_MEMSET(&str_ntfy_rqst, 0, sizeof(tstr_notifiy_request) );
	str_ntfy_rqst.enu_type = ATTR_CHANGED;
	/*Not Moved for the defined period.*/
	/*Get the CB other arguments.*/
	for(u8_i = 0; u8_i < gpstr_indct_hw->u8_indct_hw_cnt; u8_i++)
	{
		if(ACC_SENSOR_NOTIFICATIONS == gpstr_indct_hw->ppstr_indct_hw_attrs[u8_i]->pstr_hardware->enu_subtype)
		{
			str_ntfy_rqst.pv_data = (void*)gpstr_indct_hw->ppstr_indct_hw_attrs[u8_i];
			break;
		}
	}
	((const tstr_twi_rhp_attr*)(str_ntfy_rqst.pv_data))->pstr_value->enu_type = U8;
	gu8_notification = TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY;
	((const tstr_twi_rhp_attr*)(str_ntfy_rqst.pv_data))->pstr_value->uni_value.u8_int = gu8_notification;
    RHP_HW_SENSOR_LOG_COMBINED("\r\n+++++++++++++++++++++++++++\r\nAccelerometer Notification", gu8_notification);
    RHP_HW_SENSOR_LOG("\r\n+++++++++++++++++++++++++++\r\n");
    gpf_rqst_ntfy_rhp_engn(&str_ntfy_rqst);

}
#endif

static twi_s32 accelerometer_interrupt(void* pv)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	if(NULL != gpf_rqst_ntfy_rhp_engn)
	{
		if(!gb_disable_interrupt_handling)
		{
			/*Rise the flag to get the interrupt cause.*/
			gb_get_notification_cause = TWI_TRUE;
		}
	}
	else
	{
		s32_retval = TWI_ERROR;
	}

	return s32_retval;
}

/*
* This is a function used to enable detection on one or more event i.e. Free Fall, Movement, Shock.
* In case of zero, it will disable the detection for all event;
*/
static twi_s32 accelerometer_set_detection_mode(twi_u8 u8_notify)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	if(TWI_RHP_HW_ACC_SENSOR_NO_NOTIFY == u8_notify)
	{
		/*Disable detection for all events. */
		s32_retval = twi_accelerometer_detect_mode(ACCELEROMTER_NO_DETECT);
	}
	else
	{
		if(u8_notify & TWI_RHP_HW_ACC_SENSOR_FREE_FALL_NOTIFY)
		{
			s32_retval = twi_accelerometer_detect_mode(ACCELEROMTER_DETECT_FREE_FALL);
		}
		if((u8_notify & TWI_RHP_HW_ACC_SENSOR_MOVEMENT_NOTIFY) || (u8_notify & TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY))
		{
			s32_retval = twi_accelerometer_detect_mode(ACCELEROMTER_DETECT_MOVEMENT);
		}
		if(u8_notify & TWI_RHP_HW_ACC_SENSOR_SHOCK_NOTIFY)
		{
			s32_retval = twi_accelerometer_detect_mode(ACCELEROMTER_DETECT_SHOCK);
		}
	}

	return s32_retval;
}

/*This is a function that is used to set the minimum Movement threshold to be detected by the Accelerometer. */
#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION) || defined (TWI_ACC_ENABLE_CONTROL_SENSITIVITY_FEATURE)
static twi_s32 accelerometer_set_threshold(tenu_accelerometer_sensitivity enu_sense)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	switch (enu_sense)
	{
		case LOW_SENSE:
			/*Sensitive to 1G = (reg_val/128)*FULL_SCALE ---> reg_val = (128 * 1) / FULL_SCALE. */
			s32_retval = twi_accelerometer_set_interrupt_thershold((twi_u8) ((128) >> ACC_SENSOR_FULL_SCALE_PRESCALER));
			break;
		case MEDIUM_SENSE:
			/*Sensitive to 0.5G = (reg_val/128)*FULL_SCALE ---> reg_val = (128 * 0.5) / FULL_SCALE. */
			s32_retval = twi_accelerometer_set_interrupt_thershold((twi_u8) ((128 >> 1) >> ACC_SENSOR_FULL_SCALE_PRESCALER));
			break;
		case HIGH_SENSE:
			/*Sensitive to 0.25G = (reg_val/128)*FULL_SCALE ---> reg_val = (128 * 0.25) / FULL_SCALE. */
			s32_retval = twi_accelerometer_set_interrupt_thershold((twi_u8) ((128 >> 2) >> ACC_SENSOR_FULL_SCALE_PRESCALER));
			break;
		default:
			/*Set the sensitivity to the Default value which is the medium.*/
			/*Sensitive to 0.625G = (reg_val/128)*FULL_SCALE ---> reg_val = (128 * 0.625) / FULL_SCALE. */
			s32_retval = twi_accelerometer_set_interrupt_thershold((twi_u8) (((128 >> 1) + (128 >> 3)) >> ACC_SENSOR_FULL_SCALE_PRESCALER));
			break;
	}

	return s32_retval;
}
#endif

/*This is a function that is used to set the minimum Movement duration to be detected by the Accelerometer.*/
#if defined (TWI_HW_ACC_FULL_FUNCTION) || defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_ACC_ENABLE_CONTROL_ODR_FEATURE) || (TWI_ACC_ENABLE_CONTROL_MOVE_DURATION_FEATURE)
static twi_s32 accelerometer_set_duration(twi_u8 u8_duration_sec)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	if (u8_duration_sec <= ACC_SENSOR_DIV_ODR(127))
	{
		if(0 != u8_duration_sec)
		{
			s32_retval = twi_accelerometer_set_interrupt_duration(ACC_SENSOR_MUL_ODR(u8_duration_sec));
		}
		else
		{
			s32_retval = twi_accelerometer_set_interrupt_duration(ACC_SENSOR_DEFAULT_MOVEMENT_DURATION);
		}
	}
	else
	{
		s32_retval = TWI_ERROR_INVALID_ARGUMENTS;
	}

	return s32_retval;
}
#endif

/*Is is a function that is used to set the minimum threshold of a Shock to be detected by the Accelerometer.*/
#if defined (TWI_ACC_ENABLE_NOTIFICATION_CAUSE_FEATURE) || defined (TWI_ACC_ENABLE_CONTROL_SHOCK_LEVEL_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
static twi_s32 accelerometer_set_shock_level(twi_u16 u16_shock_level_mg)
{
	twi_s32 s32_retval;

	s32_retval = TWI_SUCCESS;

	if ((u16_shock_level_mg > 0) && (u16_shock_level_mg <= ACC_SENSOR_FULL_SCALE_MG))
	{
		twi_u8 u8_shock_lvl;

		u8_shock_lvl = (twi_u8) (((twi_u32)u16_shock_level_mg << 7) / ACC_SENSOR_FULL_SCALE_MG);

		/* (reg value = shoch level in mg *128 / full scale value) I use the full scale value near power of 2*/
		s32_retval = twi_accelerometer_set_shock_thershold(u8_shock_lvl);
	}
	else
	{
		/* setting the default values */
		s32_retval = twi_accelerometer_set_shock_thershold((twi_u8) (ACC_SENSOR_DEFAULT_SHOCK_LEVEL_DIVIDER));
	}
	return s32_retval;
}
#endif

#if defined (TWI_ACC_ENABLE_TILT_ANGLE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
/*
 *	@brief		This function used to calculate tilt angle (angle between the plane and the horizontal).
 *
 *	@param[in]	s16_ax	x-axis acceleration.
 *	@param[in]	s16_ay	y-axis acceleration.
 *	@param[in]	s16_az	z-axis acceleration.
 *
 *	@return     Returns the degree in range 0 to 180.
 *
 */
static twi_u8 calc_tilt_angle(twi_s16 s16_ax, twi_s16 s16_ay, twi_s16 s16_az)
{
	/* tilt_angle 	= arctan(Numerator/Denominator)
	 * Numerator 	= sqrt(Ax^2 (Ax^2 + Az^2) + Ay^2 (Ay^2 + Az^2))
	 * Denominator	= sqrt(Ax^2 + Az^2) * sqrt(Ay^2 + Az^2)
	 */
	twi_s16 s16_angle;
	twi_u32 u32_ax_pwr_2;
	twi_u32 u32_ay_pwr_2;
	twi_u32 u32_az_pwr_2;
	twi_u32 u32_numenator;
	twi_u32 u32_denominator;
	
	u32_ax_pwr_2 = (twi_u32)((twi_s32)s16_ax * (twi_s32)s16_ax);
	u32_ay_pwr_2 = (twi_u32)((twi_s32)s16_ay * (twi_s32)s16_ay);
	u32_az_pwr_2 = (twi_u32)((twi_s32)s16_az * (twi_s32)s16_az);

	u32_numenator	 = twi_sqrt(MUL1000(	(twi_u64)u32_ax_pwr_2 * (twi_u64)(u32_ax_pwr_2 + u32_az_pwr_2) +
											(twi_u64)u32_ay_pwr_2 * (twi_u64)(u32_ay_pwr_2 + u32_az_pwr_2) ));
	u32_numenator	/= 1000UL;

	u32_denominator	 = 	(twi_u32)(	((twi_u64)twi_sqrt(MUL1000((twi_u64)(u32_ax_pwr_2 + u32_az_pwr_2)))	* 
									(twi_u64)twi_sqrt(MUL1000((twi_u64)(u32_ay_pwr_2 + u32_az_pwr_2)))) /
									1000UL 																/
									1000UL	);

	s16_angle = twi_arctan(u32_numenator, u32_denominator);
	
	/*Detect upside down condition*/
	if(0 > s16_az)
	{
		s16_angle = 180 - s16_angle;
	}
	
	return (twi_u8)s16_angle;
}
#endif

static twi_s32 odr_map(twi_u16 odr_value, tenu_twi_accelerometer_odr_cfg* enu_mapped_value)
{
	twi_s32 s32_retval = TWI_SUCCESS;
	switch(odr_value)
	{
	case 1:
		*enu_mapped_value = ACCELEROMETER_ODR_1Hz;
		break;
	case 10:
		*enu_mapped_value = ACCELEROMETER_ODR_10Hz;
		break;
	case 25:
		*enu_mapped_value = ACCELEROMETER_ODR_25Hz;
		break;
	case 50:
		*enu_mapped_value = ACCELEROMETER_ODR_50Hz;
		break;
	case 100:
		*enu_mapped_value = ACCELEROMETER_ODR_100Hz;
		break;
	case 200:
		*enu_mapped_value = ACCELEROMETER_ODR_200Hz;
		break;
	case 400:
		*enu_mapped_value = ACCELEROMETER_ODR_400Hz;
		break;
	default:
		s32_retval = TWI_ERROR_INVALID_CONFIG;
	}
	return s32_retval;
}

/*---------------------------------------------------------*/
/*- APIs IMPLEMENTATION -----------------------------------*/
/*---------------------------------------------------------*/
void twi_rhp_hw_acc_dispatch(void)
{
    static twi_u8 u8_trial_counter = MAX_NUM_TRIALS;
    static twi_u8 u8_trial_check_config = MAX_NUM_TRIALS;
    static twi_u8 u8_trial_get_interrupt_cause = MAX_NUM_TRIALS;
	twi_s32 s32_retval = TWI_SUCCESS;
	
    if(TWI_TRUE == gb_get_notification_cause)
    {       
		twi_u8 u8_interrupt_cause = 0;
		twi_bool b_valid_interrupt = TWI_FALSE;
		twi_u8 u8_i;

        /*Get the interrupt cause.*/
        s32_retval = twi_accelerometer_get_interrupt_cause(&u8_interrupt_cause);
        if(TWI_SUCCESS != s32_retval)
        {
            u8_trial_get_interrupt_cause--;
        }
        else
        {
            /*Check if it is a valid interrupt or not.*/
            gu8_notification = 0;
            if(gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_FREE_FALL_NOTIFY)
            {
                if(ACCELEROMTER_FALL & u8_interrupt_cause)
                {
                    gu8_notification |= TWI_RHP_HW_ACC_SENSOR_FREE_FALL_NOTIFY;
                    b_valid_interrupt = TWI_TRUE;
                }
            }
            if(gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_MOVEMENT_NOTIFY)
            {
                if(ACCELEROMTER_MOVED & u8_interrupt_cause)
                {
                    gu8_notification |= TWI_RHP_HW_ACC_SENSOR_MOVEMENT_NOTIFY;
                    b_valid_interrupt = TWI_TRUE;
                }
            }
#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
            if(gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY)
            {
                if(ACCELEROMTER_MOVED & u8_interrupt_cause)
                {
                    /*Reset not_moved_timer if it is a NO_Movement Notify and there is a movement.*/
                    stop_timer(&gstr_acc_not_moved_timer);
                    start_timer(&gstr_acc_not_moved_timer, (twi_s8*)"ACC_NOT_MOVED_TIMER", TWI_TIMER_TYPE_PERIODIC,
                                                                    gu32_acc_not_moved_period,acc_not_moved_timer_cb, NULL);
                }
                if(TWI_TRUE == gb_not_moved_notification)
                {
                    /*No Movement Notification.*/
                    gu8_notification |= TWI_RHP_HW_ACC_SENSOR_NO_MOVEMENT_NOTIFY;
                    b_valid_interrupt = TWI_TRUE;
                    gb_not_moved_notification = TWI_FALSE;
                }
            }
#endif            
            if(gu8_notification_cause & TWI_RHP_HW_ACC_SENSOR_SHOCK_NOTIFY)
            {
            	if(ACCELEROMTER_SHOCKED & u8_interrupt_cause)
            	{
            		gu8_notification |= TWI_RHP_HW_ACC_SENSOR_SHOCK_NOTIFY;
                	b_valid_interrupt = TWI_TRUE;
            	}
			}

        	if(TWI_TRUE == b_valid_interrupt)
            {/*It is a valid interrupt.*/
                tstr_notifiy_request	str_ntfy_rqst;
                TWI_MEMSET(&str_ntfy_rqst, 0, sizeof(tstr_notifiy_request) );

                str_ntfy_rqst.enu_type = ATTR_CHANGED;    

                /*Get the CB other arguments.*/
                for(u8_i = 0; u8_i < gpstr_indct_hw->u8_indct_hw_cnt; u8_i++)
                {
#if defined (TWI_ACC_ENABLE_NOTIFICATION_REASON_DETECT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
                    if(ACC_SENSOR_NOTIFICATIONS == gpstr_indct_hw->ppstr_indct_hw_attrs[u8_i]->pstr_hardware->enu_subtype)
                    {
                        str_ntfy_rqst.pv_data = (void*)gpstr_indct_hw->ppstr_indct_hw_attrs[u8_i];
                        break;
                    }
#endif                
                }
                ((const tstr_twi_rhp_attr*)(str_ntfy_rqst.pv_data))->pstr_value->uni_value.u8_int = gu8_notification;

                TWI_ASSERT(NULL != gpf_rqst_ntfy_rhp_engn);
                gpf_rqst_ntfy_rhp_engn(&str_ntfy_rqst);
                gb_get_notification_cause = TWI_FALSE;
                RHP_HW_SENSOR_LOG_COMBINED("\r\n+++++++++++++++++++++++++++\r\nAccelerometer Notification %d \r\n", gu8_notification);
                RHP_HW_SENSOR_LOG("\r\n+++++++++++++++++++++++++++\r\n");
            }
            else
            {
                if(0 != u8_interrupt_cause)
                {
                    u8_trial_get_interrupt_cause--;
                }
                else
                {
                    u8_trial_get_interrupt_cause = MAX_NUM_TRIALS;
                    gb_get_notification_cause = TWI_FALSE;
                }
            }
        }
        
        if(0 == u8_trial_get_interrupt_cause)
        {
            u8_trial_get_interrupt_cause = MAX_NUM_TRIALS;
            gb_handle_re_config_acc = TWI_TRUE;
            gb_get_notification_cause = TWI_FALSE;
        }
    }

    if(TWI_TRUE == gb_handle_re_config_acc)
    {      
        s32_retval = twi_acc_sensor_re_init();
        
        if(TWI_SUCCESS == s32_retval)
        {
            gb_handle_re_config_acc = TWI_FALSE;
			u8_trial_counter = MAX_NUM_TRIALS;
            twi_twi_acc_sensor_event(HANDLER_RQST_ACC_CONFIG_OPCODE);
        }
        else
        {
            u8_trial_counter--;
            if(0 == u8_trial_counter)
            {
                gb_handle_re_config_acc = TWI_FALSE;
				u8_trial_counter = MAX_NUM_TRIALS;
                twi_twi_acc_sensor_event(HANDLER_RQST_ACC_FAILED_OPCODE);
            }
        }
    }
    
    if(TWI_TRUE == gb_handle_acc_config_check)
    {
        twi_bool b_validity;
        s32_retval = twi_accelerometer_check_validity_config(&b_validity);
        
        if(TWI_SUCCESS == s32_retval)
        {
            gb_handle_acc_config_check = TWI_FALSE;
            u8_trial_check_config = MAX_NUM_TRIALS;
            if(ACC_CONFIG_NOT_VALID == b_validity)
            {
                gb_handle_re_config_acc = TWI_TRUE;
            }
        }
        else
        {
			u8_trial_check_config--;
            if(0 == u8_trial_check_config)
            {
                gb_handle_acc_config_check = TWI_FALSE;
                u8_trial_check_config = MAX_NUM_TRIALS;
                twi_twi_acc_sensor_event(HANDLER_RQST_ACC_FAILED_OPCODE);
            }
        }
    }
}



