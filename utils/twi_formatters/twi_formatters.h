/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/*
 * twi_formatters.h
 *
 *  Created on: Jun 8, 2017
 *      Author: beshoy.saad
 */

#ifndef TWI_FORMATTERS_H_
#define TWI_FORMATTERS_H_

twi_u8 format_temp_1_byte_7_1(twi_s16 s16_raw_data);

void format_temp_4_bit_readings(twi_u8* pu8_msg_buf, twi_s16 s16_temp_raw_value, twi_u16* pu16_byte_count, twi_bool b_first_reading);

twi_u16 get_temp_logger_format_size(twi_u8 u8_logs_format);

twi_s32 format_temp_sensor_log(twi_u8* pu8_formated_data, twi_u16* pu16_byte_count, tstr_twi_rhp_logger* pstr_temp_logger,
        twi_u32* pu32_actual_read_sz, twi_bool b_is_first_read);

#endif /* TWI_FORMATTERS_H_ */
