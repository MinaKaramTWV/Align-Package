/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file					twi_rhp_hw_acc_sensor_handlers.h
 ** @brief					This file includes the interface for the hardware with Remote HAL Protocol
 */

#ifndef TWI_RHP_HW_ACC_SENSOR_HANDLERS_H_
#define TWI_RHP_HW_ACC_SENSOR_HANDLERS_H_

//***********************************************************
/*- INCLUDES -----------------------------------------------*/
//***********************************************************

#include "twi_rhp_types.h"

/************************************************************/
/*- GLOBAL EXTERN VARIABLES --------------------------------*/
/************************************************************/
#if defined (TWI_ACC_ENABLE_NOTIFICATION_CAUSE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_acc_sensor_notification_cause_handlers;
#endif

#if defined (TWI_ACC_ENABLE_NOTIFICATION_REASON_DETECT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_acc_sensor_notifications_handlers;
#endif
#if defined (TWI_ACC_ENABLE_CONFIGRATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_acc_sensor_configration_handlers;
#endif
#if defined (TWI_ACC_ENABLE_CONTROL_ODR_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_acc_sensor_odr_handlers;
#endif

#if defined (TWI_ACC_ENABLE_CONTROL_SENSITIVITY_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_acc_sensor_sensitivity_handlers;
#endif

#if defined (TWI_ACC_ENABLE_CONTROL_MOVE_DURATION_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_acc_sensor_back_off_sec_handlers;
#endif

#if defined (TWI_ACC_ENABLE_CONTROL_SHOCK_LEVEL_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_acc_sensor_shock_level_handlers;
#endif

#if defined (TWI_ACC_ENABLE_CONTROL_NOT_MOVE_PERIOD_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_acc_sensor_not_moved_period_handlers;
#endif

#if defined (TWI_ACC_ENABLE_3_AXSIS_ACCELERATION_READING_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_acc_sensor_x_acc_handlers;
extern const tstrt_hardware_handlers estr_acc_sensor_y_acc_handlers;
extern const tstrt_hardware_handlers estr_acc_sensor_z_acc_handlers;
#endif

#if defined (TWI_ACC_ENABLE_FIFO_CONTENT_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_acc_sensor_fifo_content_handlers;
extern const tstrt_hardware_handlers estr_acc_sensor_num_of_fifo_levels_handlers;
#endif

#if defined (TWI_ACC_ENABLE_TILT_ANGLE_FEATURE) || defined (TWI_HW_ACC_FULL_FUNCTION)
extern const tstrt_hardware_handlers estr_acc_sensor_tilt_angle_handlers;
#endif

/************************************************************/
/*- CONSTANTS ----------------------------------------------*/
/************************************************************/

/*-***********************************************************/
/*- STRUCTS AND UNIONS --------------------------------------*/
/*-***********************************************************/

/*-***********************************************************/
/*- FUNCTIONS' PROTOTYPES -----------------------------------*/
/*-***********************************************************/

void twi_rhp_hw_acc_dispatch(void);

#endif /* TWI_RHP_HW_ACC_SENSOR_HANDLERS_H_ */
