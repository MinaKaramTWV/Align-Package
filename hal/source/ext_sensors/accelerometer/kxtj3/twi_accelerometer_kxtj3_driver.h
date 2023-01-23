/*-**************************************************************************-*/
/*- Copyright 2022 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file					twi_accelerometer_kxtj3_driver.h
 *	@brief					This file holds the needed definitions for the Accelerometer "KXTJ3" chip driver.
 *							For more information, please, refer to the Accelerometer data sheet:
 *							https://kionixfs.azureedge.net/en/datasheet/KXTJ3-1057-Specifications-Rev-5.0.pdf
 */

#ifndef TWI_ACCELEROMETER_KXTJ3_DRIVER_H_
#define TWI_ACCELEROMETER_KXTJ3_DRIVER_H_

//***********************************************************
/*- INCLUDES -----------------------------------------------*/
//***********************************************************
#include "twi_common.h"

//***********************************************************
/*- LOCAL MACROS ------------------------------------------*/
//***********************************************************

/*
                        ---------------------------------- I2C ADDRESS -------------------------------------
 ADDR PAD    R/W        Bit7    Bit6   Bit5   Bit4   Bit3   Bit2(Factory cnfg)   Bit1(User cnfg)   Bit0(R/W)   
------------------------------------------------------------------------------------------------------------
 GND          W          0       0      0      1      1            1                   1               0
 GND          R          0       0      0      1      1            1                   1               1 
 VDD          W          0       0      0      1      1            1                   1               0
 VDD          R          0       0      0      1      1            1                   1               1
------------------------------------------------------------------------------------------------------------
*/
#define GND_ADDRESS_PAD                 (0)
#define VDD_ADDRESS_PAD                 (1)
#define ADDRESS_PAD_CONNECTION          (GND_ADDRESS_PAD)

	
#define KXTJ3_I2C_ADD					((twi_u8)(0x0E))
#define KXTJ3_WHO_AM_I_VALUE			((twi_u8)(0x35))


/* This Accelerometer is controlled through registers, which are: */
/* Registers (0x00 : 0x05) are reserved */

#define KXTJ3_OUT_X_L					((twi_u8)(0x06))		/* X-axis acceleration low data OUTPUT REGISTER */   	/*Read-only*/
#define KXTJ3_OUT_X_H					((twi_u8)(0x07))		/* X-axis acceleration high data OUTPUT REGISTER */  	/*Read-only*/
#define KXTJ3_OUT_Y_L					((twi_u8)(0x08))		/* Y-axis acceleration low data OUTPUT REGISTER */   	/*Read-only*/
#define KXTJ3_OUT_Y_H					((twi_u8)(0x09))		/* Y-axis acceleration high data OUTPUT REGISTER */  	/*Read-only*/
#define KXTJ3_OUT_Z_L					((twi_u8)(0x0A))		/* Z-axis acceleration low data OUTPUT REGISTER */   	/*Read-only*/
#define KXTJ3_OUT_Z_H					((twi_u8)(0x0B))		/* Z-axis acceleration high data OUTPUT REGISTER */ 	/*Read-only*/
#define KXTJ3_DCST_RESP					((twi_u8)(0x0C))		/* Verify IC functionality REGISTER */ 					/*Read-only*/

/* Registers (0x0D : 0x0E) are reserved */

#define KXTJ3_WHO_AM_I					((twi_u8)(0x0F))		/* Device identification REGISTER */                    /*Read-only*/

/* Registers (0x10 : 0x15) are reserved */

#define KXTJ3_INT1_SRC					((twi_u8)(0x16))		/* INTERRUPT 1 SOURCE REGISTER */                       /*Read-only*/
#define KXTJ3_INT2_SRC					((twi_u8)(0x17))		/* INTERRUPT 2 SOURCE REGISTER */                       /*Read-only*/
#define KXTJ3_STATUS_REG				((twi_u8)(0x18))		/* STATUS REGISTER */                                   /*Read-only*/

/* Register (0x19) is reserved */

#define KXTJ3_INT_REL					((twi_u8)(0x1A))		/* INTERRUPT Latch REGISTER */                          /*Read-only*/
#define KXTJ3_CTRL_REG1					((twi_u8)(0x1B))		/* CONTROL REGISTER 1 */ 								/*Read-Write*/

/* Register (0x1C) is reserved */

#define KXTJ3_CTRL_REG2					((twi_u8)(0x1D))		/* CONTROL REGISTER 2 */ 								/*Read-Write*/
#define KXTJ3_INT_CTRL_REG1				((twi_u8)(0x1E))		/* INTERRUPT CONTROL REGISTER 1 */ 						/*Read-Write*/
#define KXTJ3_INT_CTRL_REG2				((twi_u8)(0x1F))		/* INTERRUPT CONTROL REGISTER 2 */						/*Read-Write*/

/* Register (0x20) is reserved */

#define KXTJ3_DATA_CTRL_REG				((twi_u8)(0x21))		/* Data CONTROL REGISTER  */ 							/*Read-Write*/

/* Registers (0x22 : 0x28) are reserved */

#define KXTJ3_WAKE_UP_COUNTER			((twi_u8)(0x29))		/* Motion Wake Up Counter REGISTER  */ 					/*Read-Write*/
#define KXTJ3_NA_COUNTER				((twi_u8)(0x2A))		/* Non_activity Wake Up Counter REGISTER  */ 			/*Read-Write*/

/* Registers (0x2B : 0x39) are reserved */

#define KXTJ3_SELF_TEST					((twi_u8)(0x3A))		/* MEMS Self-Test REGISTER */                          	/*Write-only*/

/* Registers (0x3B : 0x69) are reserved */

#define KXTJ3_WAKE_UP_THRESHOLD_H		((twi_u8)(0x6A))		/* Motion detection threshold High REGISTER */ 			/*Read-Write*/
#define KXTJ3_WAKE_UP_THRESHOLD_L		((twi_u8)(0x6B))		/* Motion detection threshold Low REGISTER */ 			/*Read-Write*/

/**
 * Bit fields for the registers of Accelerometer "KXTJ3"
 */

/* CONTROL REGISTER 1 Bit fields */
#define KXTJ3_CTRL_REG1_PC1				(7)         /* Control the operationg mode pf KXTJ3 */
#define KXTJ3_CTRL_REG1_RES				(6)			/* Determine the performance mode of KXTJ3 */
#define KXTJ3_CTRL_REG1_DRDYE			(5)         /* Enable the reporting of new data availability */
#define KXTJ3_CTRL_REG1_GSEL1			(4)         /* GSEL0, GSEL1, and EN16G select the acceleration range */
#define KXTJ3_CTRL_REG1_GSEL0			(3)
#define KXTJ3_CTRL_REG1_EN16G			(2)
#define KXTJ3_CTRL_REG1_WUFE			(1)         /* Enable the wake up at motion detection */

/* CONTROL REGISTER 2 Bit fields */
#define KXTJ3_CTRL_REG2_SRST			(7)         /* Performs the RAM reboot routine */
#define KXTJ3_CTRL_REG2_DCST			(4)			/* intialize the self test functionality */
#define KXTJ3_CTRL_REG2_OWUFA			(2)         /* OWUFA, OWUFB, and OWUFC set the output data rate of wake_up */
#define KXTJ3_CTRL_REG2_OWUFB			(1)         
#define KXTJ3_CTRL_REG2_OWUFC			(0)

/* INTERRUPT CONTROL REGISTER 1 Bit fields */
#define KXTJ3_CTRL_REG1_IEN				(5)         /* Enable the physical interrupt pin (INT) */
#define KXTJ3_CTRL_REG1_IEA				(4)			/* Sets the polarity of the physical interrupt pin */
#define KXTJ3_CTRL_REG1_IEL				(3)         /* Sets the response of physical interrupt pin */
#define KXTJ3_CTRL_REG1_STPOL			(1)         /* Self test the polarity */

/* INTERRUPT CONTROL REGISTER 2 Bit fields */
#define KXTJ3_CTRL_REG2_ULMODE			(7)         /* Set the unlatched mode */
#define KXTJ3_CTRL_REG2_XNWUE			(5)			
#define KXTJ3_CTRL_REG2_XPWUE			(4)        
#define KXTJ3_CTRL_REG2_YNWUE			(3)     
#define KXTJ3_CTRL_REG2_YPWUE			(2)       
#define KXTJ3_CTRL_REG2_ZNWUE			(1)
#define KXTJ3_CTRL_REG2_ZPWUE			(0)

/* DATA CONTROL REGISTER Bit fields */
#define KXTJ3_DATA_CTRL_REG_OSAA		(3)        
#define KXTJ3_DATA_CTRL_REG_OSAB		(2)			
#define KXTJ3_DATA_CTRL_REG_OSAC		(1)        
#define KXTJ3_DATA_CTRL_REG_OSAD		(0)     

/* INTERRUPT SOURCE REGISTER 1 Bit fields */
#define KXTJ3_INT1_SRC_DRDY				(4)        
#define KXTJ3_INT1_SRC_WUFS				(1)			

/* INTERRUPT SOURCE REGISTER 2 Bit fields */
#define KXTJ3_INT2_SRC_XNWU				(5)        
#define KXTJ3_INT2_SRC_XPWU				(4)        
#define KXTJ3_INT2_SRC_YNWU				(3)        
#define KXTJ3_INT2_SRC_YPWU				(2)        
#define KXTJ3_INT2_SRC_ZNWU				(1)        
#define KXTJ3_INT2_SRC_ZPWU				(0)        

/**
 * Return Values for Accelerometer "KXTJ3"
 */
#define TWI_ACCELEROMETER_NOT_FOUND_ERROR			(TWI_ERR_ACCELEROMETER_BASE - 1)
#define TWI_ACCELEROMETER_READ_REG_ERROR			(TWI_ERR_ACCELEROMETER_BASE - 2)
#define TWI_ACCELEROMETER_WRITE_REG_ERROR			(TWI_ERR_ACCELEROMETER_BASE - 3)
#define TWI_ACCELEROMETER_HW_INIT_ERROR				(TWI_ERR_ACCELEROMETER_BASE - 4)
#define TWI_ACCELEROMETER_HW_DEINIT_ERROR			(TWI_ERR_ACCELEROMETER_BASE - 5)
#define TWI_ACCELEROMETER_UNSUPPORTED_FEATURE		(TWI_ERR_ACCELEROMETER_BASE - 6)
/**
* Enumeration for the Accelerometer interrupt case.
*/
typedef enum
{
	ACCELEROMTER_KXTJ3_FALL       =   0x01,	    	        /**< Free Fall. (Un-supported Feature)  */

	ACCELEROMTER_KXTJ3_MOVED      =   0x02, 		        /**< Movement. */

	ACCELEROMTER_KXTJ3_SHOCKED    =   0x04,		            /**< Shock. (Un-supported Feature)  */
}tenu_twi_accelerometer_kxtj3_interrupt_cause;

//***********************************************************
/*- ENUMS --------------------------------------------------*/
//***********************************************************

/**
* Enumeration for the Accelerometer"KXTJ3" Full Scale Option.
*/
typedef enum
{
	KXTJ3_FULL_SCALE_2G_8_BIT	= 0,	/**< full scale -/+ 2G  8-bit  */
	KXTJ3_FULL_SCALE_2G_12_BIT	= 1,	/**< full scale -/+ 2G  12-bit */
	KXTJ3_FULL_SCALE_4G_8_BIT	= 2,	/**< full scale -/+ 4G  8-bit  */
	KXTJ3_FULL_SCALE_4G_12_BIT	= 3,	/**< full scale -/+ 4G  12-bit */
	KXTJ3_FULL_SCALE_8G_8_BIT	= 4,	/**< full scale -/+ 8G  8-bit  */
	KXTJ3_FULL_SCALE_8G_12_BIT	= 5,	/**< full scale -/+ 8G  12-bit */
	KXTJ3_FULL_SCALE_8G_14_BIT	= 6,	/**< full scale -/+ 8G  14-bit */
	KXTJ3_FULL_SCALE_16G_8_BIT  = 7,	/**< full scale -/+ 16G 8-bit  */
	KXTJ3_FULL_SCALE_16G_12_BIT = 8,	/**< full scale -/+ 16G 12-bit */
	KXTJ3_FULL_SCALE_16G_14_BIT = 9		/**< full scale -/+ 16G 14-bit */
}tenu_twi_accelerometer_kxtj3_full_scale_option;

/**
* Enumeration for the Accelerometer"KXTJ3" Full Scale Option Bit Mask.
*/
typedef enum
{
	KXTJ3_FS_2G_8_BIT_VALUE		= 0x00,
	KXTJ3_FS_2G_12_BIT_VALUE	= 0x40,
	KXTJ3_FS_4G_8_BIT_VALUE		= 0x08,
	KXTJ3_FS_4G_12_BIT_VALUE	= 0x48,
	KXTJ3_FS_8G_8_BIT_VALUE		= 0x10,
	KXTJ3_FS_8G_12_BIT_VALUE	= 0x50,
	KXTJ3_FS_8G_14_BIT_VALUE	= 0x58,
	KXTJ3_FS_16G_8_BIT_VALUE1	= 0x04,
	KXTJ3_FS_16G_8_BIT_VALUE2	= 0x0C,
	KXTJ3_FS_16G_8_BIT_VALUE3	= 0x14,
	KXTJ3_FS_16G_12_BIT_VALUE1	= 0x44,
	KXTJ3_FS_16G_12_BIT_VALUE2	= 0x4C,
	KXTJ3_FS_16G_12_BIT_VALUE3	= 0x54,
	KXTJ3_FS_16G_14_BIT_VALUE	= 0x5C	
}tenu_twi_accelerometer_kxtj3_full_scale_mask_values;

/**
* Enumeration for the Accelerometer"KXTJ3" Data Rate Configuration.
*/
typedef enum
{
	KXTJ3_ODR_12_5Hz	= 0x00,		/**< Data rate = 12.5Hz */
	KXTJ3_ODR_25Hz		= 0x01,		/**< Data rate = 25Hz */
	KXTJ3_ODR_50Hz		= 0x02,		/**< Data rate = 50Hz */
	KXTJ3_ODR_100Hz		= 0x03,		/**< Data rate = 100Hz */
	KXTJ3_ODR_200Hz		= 0x04,		/**< Data rate = 200Hz */
	KXTJ3_ODR_400Hz		= 0x05,		/**< Data rate = 400Hz */
	KXTJ3_ODR_800Hz		= 0x06,		/**< Data rate = 800Hz */
	KXTJ3_ODR_1600Hz	= 0x07,		/**< Data rate = 1600Hz */
	KXTJ3_ODR_0_781Hz	= 0x08,		/**< Data rate = 0.781Hz */
	KXTJ3_ODR_1_563Hz	= 0x09,		/**< Data rate = 1.563Hz */
	KXTJ3_ODR_3_125Hz	= 0x0A,		/**< Data rate = 3.125Hz */
	KXTJ3_ODR_6_25Hz	= 0x0B		/**< Data rate = 6.25Hz */
}tenu_twi_accelerometer_kxtj3_odr_cfg;

/**
* Enumeration for the Accelerometer"KXTJ3" 6D Positions.
*/
typedef enum
{
	KXTJ3_NO_MOVE		= (twi_u8)0x00,	/**< No move */

	KXTJ3_MOVE_X_NEG	= (twi_u8)0x20,	/**< X -ve position */

	KXTJ3_MOVE_X_POS	= (twi_u8)0x10,	/**< X +ve position */

	KXTJ3_MOVE_Y_NEG	= (twi_u8)0x08,	/**< Y -ve position */

	KXTJ3_MOVE_Y_POS	= (twi_u8)0x04,	/**< Y +ve position */

	KXTJ3_MOVE_Z_NEG	= (twi_u8)0x02,	/**< Z -ve position */

	KXTJ3_MOVE_Z_POS	= (twi_u8)0x01	/**< Z +ve position */
}tenu_twi_accelerometer_kxtj3_6d_direction;


/**
* Enumeration for the Accelerometer"KXTJ3" axis acceleration.
*/
typedef enum
{
	KXTJ3_X_AXIS_ACCELERATION,			/**< X axis acceleration */

	KXTJ3_Y_AXIS_ACCELERATION,			/**< Y axis acceleration */

	KXTJ3_Z_AXIS_ACCELERATION,			/**< Z axis acceleration */

}tenu_twi_accelerometer_kxtj3_axis_acceleration;

//***********************************************************
/*- PRIMITIVE TYPES ----------------------------------------*/
//***********************************************************

typedef twi_s32(*tpf_accelerometer_kxtj3_interrupt)(void* pvalue);

//***********************************************************
/*- STRUCTS AND UNIONS -------------------------------------*/
//***********************************************************

//************************************************************
/*- API's Prototypes ---------------------------------------*/
//************************************************************

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_init(tpf_accelerometer_kxtj3_interrupt pf_cb)
*	@brief		Function used for initialization of Accelerometer "KXTJ3" and setting it into default state.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_init(tpf_accelerometer_kxtj3_interrupt pf_cb);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_deinit(void)
*	@brief		Function used for de-initialization of Accelerometer"KXTJ3".
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_deinit(void);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_get_axis_acc(tenu_twi_accelerometer_kxtj3_axis_acceleration enu_axis, twi_s16* ps16_axis_acc_mg)
*	@brief		Function used to read the Acceleration Values for X or Y or Z axis.
*	@param[in]	enu_axis	The type of the axis (X, Y, Z).
*	@param[out]	ps16_axis_acc_mg		Pointer to value that holds the acceleration of the axis. (The output is in mg)
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
**/
twi_s32 twi_accelerometer_kxtj3_get_axis_acc(tenu_twi_accelerometer_kxtj3_axis_acceleration enu_axis, twi_s16* ps16_axis_acc_mg);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_get_6d_direction(tenu_twi_accelerometer_kxtj3_6d_direction* penu_6d_dir)
*	@brief		Function used to read the movement direction for the Accelerometer"KXTJ3" Usage when interrupt occurs.
*	@param[out]	penu_6d_dir	pointer to the direction of movement.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*   @note		You must not call it from interrupt context. if you call it from interrupt context, System shall crash.
**/
twi_s32 twi_accelerometer_kxtj3_get_6d_direction(tenu_twi_accelerometer_kxtj3_6d_direction* penu_6d_dir);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_set_full_scale(tenu_twi_accelerometer_full_scale_option enu_fs)
*	@brief		Function used to set the KXTJ3 Full Scale.
*	@param[in]	enu_fs	enum variable must be one of the following:
*	(KXTJ3_FULL_SCALE_2G_8_BIT ::), (KXTJ3_FULL_SCALE_2G_12_BIT ::),(KXTJ3_FULL_SCALE_4G_8_BIT ::), 
*	(KXTJ3_FULL_SCALE_4G_12_BIT ::), (KXTJ3_FULL_SCALE_8G_8_BIT ::),(KXTJ3_FULL_SCALE_8G_12_BIT ::), 
*	(KXTJ3_FULL_SCALE_8G_14_BIT ::),(KXTJ3_FULL_SCALE_16G_8_BIT ::), (KXTJ3_FULL_SCALE_16G_12_BIT ::), 
*	(KXTJ3_FULL_SCALE_16G_14_BIT ::)
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_set_full_scale(tenu_twi_accelerometer_kxtj3_full_scale_option enu_fs);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_set_data_rate_config(tenu_twi_accelerometer_kxtj3_odr_cfg enu_odr)
*	@brief		Function used to set the KXTJ3 Data rate configuration.
*	@param[in]	enu_odr	enum variable (Data Rate CFG) must be one of the following:
*					(KXTJ3_ODR_0_781Hz ::), (KXTJ3_ODR_1_563Hz ::), (KXTJ3_ODR_3_125Hz ::), (KXTJ3_ODR_6_25Hz ::), 
*    				(KXTJ3_ODR_12_5Hz ::)(KXTJ3_ODR_25Hz ::), (KXTJ3_ODR_50Hz::), (KXTJ3_ODR_100Hz ::),
*					(KXTJ3_ODR_200Hz ::),(KXTJ3_ODR_400Hz ::),(KXTJ3_ODR_800Hz ::),(KXTJ3_ODR_1600Hz ::)
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_set_data_rate_config(tenu_twi_accelerometer_kxtj3_odr_cfg enu_odr);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_set_interrupt_thershold(twi_u8 u8_th_val)
*	@brief		Function used to set the threshold of the interrupt accelerometer "KXTJ3".
*				WAKEUP_THRESHOLD (counts) = Desired Threshold (g) x 256 (counts/g)
*	@param[in]	u8_th_val	Threshold value for Interrupt 1 (value from 0 to 127) else error value should be returned.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_set_interrupt_thershold(twi_u8 u8_th_val);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_set_shock_thershold(twi_u8 u8_th_val)
*	@brief		Function used to set the threshold of the shock interrupt accelerometer "KXTJ3".
*	@param[in]	u8_th_val	Threshold value for Interrupt 1 (value from 0 to 127) else error value should be returned.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_set_shock_thershold(twi_u8 u8_th_val);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_set_shock_duration(twi_u8 u8_th_val)
*	@brief		Function used to set the Set the minimum duration of the Shock Interrupt 1 event to be recognized for the accelerometer "KXTJ3".
*	@param[in]	u8_duration_val	Duration value for Interrupt 1 (value from 0 to 127) else error value should be returned.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_set_shock_duration(twi_u8 u8_th_val);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_set_interrupt_duration(twi_u8 u8_duration_val)
*	@brief		Function used to set the Set the minimum duration of the Interrupt 1 event to be recognized for the accelerometer "KXTJ3".
*				The duration value depends on the ODR value (It's 7 bits only full scale 2^7 = 128).
*				Duration LSB value = 1/ODR. The next table indicates the duration LSB values.
*					 ___________________________________________
*					|				|							|
*					|	 ODR (Hz)	|	Duration LSB value (ms)	|
*					|_______________|___________________________|
*					|	1 (1.563)	|		(1000) 1563			|
*					|_______________|___________________________|
*					|	10 (12.5)	|		(100) 125			|
*					|_______________|___________________________|
*					|	  	25		|			40				|
*					|_______________|___________________________|
*					|	 	50		|			20				|
*					|_______________|___________________________|
*					|	 	100		|			10				|
*					|_______________|___________________________|
*					|	 	200		|			5				|
*					|_______________|___________________________|
*					|	 	400		|			2.5				|
*					|_______________|___________________________|
*
*	@param[in]	u8_duration_val	Duration value for Interrupt 1 (value from 0 to 127) else error value should be returned.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_set_interrupt_duration(twi_u8 u8_duration_val);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_free_fall_detect(void)
*	@brief		Function used to enable the free fall detection interrupt.
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_free_fall_detect(void);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_movement_detect(void)
*	@brief		Function used to enable the movement detection interrupt.
*				- It sets the following settings:
*					+ Disable the accelerometer interrupt.
*					+ Clear any previous interrupts.
*					+ Re-enable the accelerometer interrupt.
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_movement_detect(void);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_position_detect(void)
*	@brief		Function used to enable the position detection interrupt.
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_position_detect(void);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_shock_detect(void)
*	@brief		Function used to enable the shock detection interrupt.
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_shock_detect(void); 

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_no_detect(void)
*	@brief		Function used to disable the detection interrupt on all events.
*				- It sets the following settings:
*					+ Disable the accelerometer interrupt.
*					+ Clear any previous interrupts.
*	@param		none
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_no_detect(void);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_get_interrupt_cause(twi_u8 *pu8_interrupt_cause)
*	@brief		Function used to Get the cause of the interrupt of the accelerometer.
*	@param[out]	pu8_interrupt_cause	    filled with the cause of interrupt. It is an ORed flags of tenu_twi_accelerometer_kxtj3_interrupt_cause.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_get_interrupt_cause(twi_u8 *pu8_interrupt_cause);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_get_fifo_content(twi_u8 u8_needed_levels_num, twi_s16 *ps16_acc_fifo_buf, twi_u8* pu8_actual_levels_num)
*	@brief		Function used to Get the content of the FIFO.
*	@param[in]		u8_needed_levels_num	    the number of level to read.
*	@param[in,out]	ps16_acc_fifo_buf   		the FIFO buffer.
*	@param[out]		pu8_actual_levels_num	    the actual number or read levels.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_get_fifo_content(twi_u8 u8_needed_levels_num, twi_s16 *ps16_acc_fifo_buf, twi_u8* pu8_actual_levels_num);

/**
*	@function	twi_s32 twi_accelerometer_kxtj3_get_num_of_fifo_levels(twi_u8* pu8_actual_levels_num)
*	@brief		Function used to Get the actual number of the FIFO levels.
*	@param[out]		pu8_actual_levels_num	    the actual number or read levels.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_get_num_of_fifo_levels(twi_u8* pu8_actual_levels_num);

/**
*	@function	twi_accelerometer_kxtj3_check_validity_config(twi_bool* pb_validity)
*	@brief		Function used for validity the configration of the Accelerometer "KXTJ3".
*	@param[out]		pb_validity	the accelerometer configration validity, valid : TWI_TRUE or not valid: TWI_FALSE.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**/
twi_s32 twi_accelerometer_kxtj3_check_validity_config(twi_bool* pb_validity);
    
#endif	/* TWI_ACCELEROMETER_KXTJ3_DRIVER_H_ */
