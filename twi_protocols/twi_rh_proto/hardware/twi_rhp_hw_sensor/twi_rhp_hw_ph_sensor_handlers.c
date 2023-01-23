/*-**************************************************************************-*/
/*- Copyright 2022 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file       twi_rhp_hw_ph_sensor_handlers.h
 ** @brief		This file contains RHAL APIs.
 */

/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/

/*Common include files.*/
#include "twi_debug.h"
#include "twi_common.h"

/*Hardware include files.*/
#include "twi_rhp_hw_ph_sensor_handlers.h"
#include "twi_ph_sensor.h"

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
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/*---------------------------------------------------------*/

static twi_s32 twi_rhp_hw_ph_sensor_init(const tstr_twi_hardware * pstr_hardware,tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn,tstr_twi_rhp_indct_hw* pstr_indct_hw, const tenu_permission enu_permission);
static twi_s32 twi_rhp_hw_ph_sensor_deinit(const tstr_twi_hardware * pstr_hardware);
static twi_s32 twi_rhp_hw_ph_sensor_read(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src);

/*---------------------------------------------------------*/
/*- LOCAL STRUCTS AND UNIONS ------------------------------*/
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/*---------------------------------------------------------*/

const tstrt_hardware_handlers estr_ph_sensor_handlers = 	{
																/*SENSOR, PH_SENSOR,*/
																twi_rhp_hw_ph_sensor_init,
																twi_rhp_hw_ph_sensor_deinit,
																twi_rhp_hw_ph_sensor_read,
																NULL,
															};

/*---------------------------------------------------------*/
/*- GLOBAL STATIC VARIABLES -------------------------------*/
/*---------------------------------------------------------*/
static tpf_rqst_ntfy_rhp_engn gpf_notify_engine = NULL;
static tstr_twi_rhp_indct_hw* gpstr_indicate_hardware = NULL;
static twi_u8 u8_old_ph_reading = 0;
/*---------------------------------------------------------*/
/*- LOCAL FUNCTIONS Implementation-------------------------*/
/*---------------------------------------------------------*/

/*
*   @brief      This is function that initialize the ph sensor attribute.
*   @param[in]  pstr_hardware	Pointer to hardware to initialize. This hardware has to be of type SENSOR and subtype PH_SENSOR.
*   @param[in] 	enu_permission 	The permission allowed on this attribute.
*   @return     ::TWI_SUCCESS, -ve error code otherwise.
*/
static twi_s32 twi_rhp_hw_ph_sensor_init(const tstr_twi_hardware * pstr_hardware,tpf_rqst_ntfy_rhp_engn pf_rqst_ntfy_rhp_engn,tstr_twi_rhp_indct_hw* pstr_indct_hw, const tenu_permission enu_permission)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;

    if(NULL != pstr_hardware)
    {
        /*Check if the Hardware is of type digital.*/
        if( (SENSOR == pstr_hardware->enu_type)     &&
            (PH_SENSOR     == pstr_hardware->enu_subtype)  &&
            ((READ_ONLY       == enu_permission) || (READ_AND_INDICATE == enu_permission))
          )
        {
            s32_retval = twi_ph_sensor_init();
            if (enu_permission == READ_AND_INDICATE)
            {
                gpf_notify_engine = pf_rqst_ntfy_rhp_engn;
                gpstr_indicate_hardware = pstr_indct_hw;
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

/*
*   @brief      This is function that de-initialize the ph sensor attribute.
*   @param[in]  pstr_hardware	Pointer to hardware  to de-initialize. This hardware has to be of type SENSOR and subtype PH_SENSOR.
*   @return     ::TWI_SUCCESS, -ve error code otherwise.
*/
static twi_s32 twi_rhp_hw_ph_sensor_deinit(const tstr_twi_hardware * pstr_hardware)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;

    if(NULL != pstr_hardware)
    {
        /*Check if the Hardware is of type digital.*/
        if((SENSOR == pstr_hardware->enu_type) && (PH_SENSOR == pstr_hardware->enu_subtype))
        {
            s32_retval = twi_ph_sensor_deinit();
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
*   @brief      This is function that initialize the ph sensor attribute.
*   @param[in]  pstr_hardware	Pointer to hardware  to initialize. This hardware has to be of type SENSOR and subtype PH_SENSOR.
*   @param[out] pstr_value 		The current value of the attribute.
*   @return     ::TWI_SUCCESS, -ve error code otherwise.
*/
static twi_s32 twi_rhp_hw_ph_sensor_read(const tstr_twi_hardware * pstr_hardware, tstr_twi_rhp_value * pstr_value, tenu_op_source enu_op_src)
{
    twi_s32 s32_retval;

    s32_retval = TWI_SUCCESS;

    if((NULL != pstr_value) && (NULL != pstr_hardware))
    {
        if((SENSOR == pstr_hardware->enu_type) && (PH_SENSOR == pstr_hardware->enu_subtype))
        {
            pstr_value->enu_type = U8;
            s32_retval = twi_ph_sensor_read(&pstr_value->uni_value.u8_int);
            if(TWI_SUCCESS == s32_retval)
            {
                RHP_HW_SENSOR_LOG("pH = %d\r\n", pstr_value->uni_value.u8_int);

                if ((gpstr_indicate_hardware != NULL) && (gpf_notify_engine != NULL))
                {
                    tstr_notifiy_request str_rqst_ntfy;
                    for (twi_u8 i = 0; i < gpstr_indicate_hardware->u8_indct_hw_cnt; i++)
                    {
                        if ((gpstr_indicate_hardware->ppstr_indct_hw_attrs[i]->pstr_hardware->enu_type == SENSOR)
                                && (gpstr_indicate_hardware->ppstr_indct_hw_attrs[i]->pstr_hardware->enu_subtype == PH_SENSOR))
                        {
                            if (u8_old_ph_reading != pstr_value->uni_value.u8_int)
                            {
                                str_rqst_ntfy.enu_type = ATTR_CHANGED;
                                str_rqst_ntfy.pv_data = (void*) gpstr_indicate_hardware->ppstr_indct_hw_attrs[i];
                                TWI_MEMCPY(gpstr_indicate_hardware->ppstr_indct_hw_attrs[i]->pstr_value, pstr_value, sizeof(tstr_twi_rhp_value));
                                (*gpf_notify_engine)(&str_rqst_ntfy);
                                u8_old_ph_reading = pstr_value->uni_value.u8_int;
                            }
                            break;
                        }
                    }
                }
            }
            else
            {
                TESTING_LOG("Error %d reading ph sensor\r\n", s32_retval);
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

/*---------------------------------------------------------*/
/*- APIs IMPLEMENTATION -----------------------------------*/
/*---------------------------------------------------------*/
void twi_rhp_hw_ph_sensor_dispatch(void)
{
	twi_ph_sensor_dispatch();
}
