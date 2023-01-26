/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

#ifndef __TWI_BLE_ADV_SCAN_CONF__
#define __TWI_BLE_ADV_SCAN_CONF__

#if defined (LABOR_GW)
#include "labor_ble_adv_scan_conf.h"
#elif defined (GENERAL_GW)
#include "general_ble_adv_scan_conf.h"
#elif defined (TRACK_AND_TRACE_GW)
#include "track_and_trace_ble_adv_scan_conf.h"
#endif

#ifdef TWI_RHP_HW_BLE
#include "twi_rhp_ble_adv_scan_conf.h"
#endif


#endif /* __TWI_BLE_ADV_SCAN_CONF__ */
