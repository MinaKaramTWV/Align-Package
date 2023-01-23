/*-**************************************************************************-*/
/*- Copyright 2023 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 ** @file		twi_vita_logic_cfg.h
 ** @brief      This file implements vita logic CFG Header File.
 */

#ifndef TWI_VITA_LOGIC_CFG_H_
#define TWI_VITA_LOGIC_CFG_H_

/***********************************************************/
/*- INCLUDES ----------------------------------------------*/
/***********************************************************/

/*-***********************************************************/
/*- Global MACROS --------------------------------------------*/
/*-***********************************************************/

/* Grace Period feature is disabled for this product. */

#define TWI_GRACE_PERIOD_TIMEOUT_SEC           	(0)   	   /* 0 min */
#define GRACE_PERIOD_DIVIDED_TIMOUT_SEC        	(0)		   /* 0 min */

/* Set TWI_PERIODIC_NOTIFY_TIMEOUT_MS to zero to diable the periodic nudge */
#define TWI_PERIODIC_NOTIFY_TIMEOUT_MS			(0)        /* 0 min */

#define LOCK_NUDGE_STATUS						TWI_FALSE /*Don't need to nudge peer device with look reason*/


#endif /* TWI_VITA_LOGIC_CFG_H_ */
