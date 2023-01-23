/*-**************************************************************************-*/
/*- Copyright 2022 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
 *	@file					twi_accelerometer_kxtj3_driver_ppi.h
 *	@brief					This file holds the needed definitions for the Accelerometer "KXTJ3" chip driver.
 *							For more information, please, refer to the Accelerometer data sheet:
 *							https://kionixfs.azureedge.net/en/datasheet/KXTJ3-1057-Specifications-Rev-5.0.pdf
 */

#ifndef TWI_ACCELEROMETER_KXTJ3_DRIVER_H_
#define TWI_ACCELEROMETER_KXTJ3_DRIVER_H_

/*---------------------------------------------------------*/
/*- INCLUDES ----------------------------------------------*/
/*---------------------------------------------------------*/
#include "twi_common.h"

/*---------------------------------------------------------*/
/*- LOCAL MACROS ------------------------------------------*/
/*---------------------------------------------------------*/

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

/*-***********************************************************/
/*- ENUMS ---------------------------------------------------*/
/*-***********************************************************/

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
/*-**********************************************************/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*-**********************************************************/

typedef twi_s32(*tpf_accelerometer_kxtj3_interrupt)(void* pvalue);

typedef void(*tpf_acc_data_ready)(void);
/*-***********************************************************/
/*- STRUCTS AND UNIONS --------------------------------------*/
/*-***********************************************************/

/*-***********************************************************/
/*- API's Prototypes ----------------------------------------*/
/*-***********************************************************/

/*-***********************************************************************************************************
* Function Name: twi_accelerometer_kxtj3_init								                                 *
**************************************************************************************************************
*	@function	twi_s32 twi_accelerometer_kxtj3_init(void)
*	@brief		- Function used for initialization of Accelerometer "KXTJ3" and setting it into default state.
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
*************************************************************************************************************/
twi_s32 twi_accelerometer_kxtj3_init(void);

/*-******************************************************************************************************************
* Function Name: twi_accelerometer_kxtj3_set_full_scale					                                            *
*********************************************************************************************************************
*	@function	twi_s32 twi_accelerometer_kxtj3_set_full_scale(tenu_twi_accelerometer_full_scale_option enu_fs)
*	@brief		Function used to set the KXTJ3 Full Scale.
*	@param[in]	enu_fs	enum variable must be one of the following:
*	(KXTJ3_FULL_SCALE_2G_8_BIT ::), (KXTJ3_FULL_SCALE_2G_12_BIT ::),(KXTJ3_FULL_SCALE_4G_8_BIT ::), 
*	(KXTJ3_FULL_SCALE_4G_12_BIT ::), (KXTJ3_FULL_SCALE_8G_8_BIT ::),(KXTJ3_FULL_SCALE_8G_12_BIT ::), 
*	(KXTJ3_FULL_SCALE_8G_14_BIT ::),(KXTJ3_FULL_SCALE_16G_8_BIT ::), (KXTJ3_FULL_SCALE_16G_12_BIT ::), 
*	(KXTJ3_FULL_SCALE_16G_14_BIT ::)
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
**********************************************************************************************************************/
twi_s32 twi_accelerometer_kxtj3_set_full_scale(tenu_twi_accelerometer_kxtj3_full_scale_option enu_fs);

/*-*****************************************************************************************************************
* Function Name: twi_accelerometer_kxtj3_set_data_rate_config				                                       *  
********************************************************************************************************************
*	@function	twi_s32 twi_accelerometer_kxtj3_set_data_rate_config(tenu_twi_accelerometer_kxtj3_odr_cfg enu_odr)
*	@brief		Function used to set the KXTJ3 Data rate configuration.
*	@param[in]	enu_odr	enum variable (Data Rate CFG) must be one of the following:
*					(KXTJ3_ODR_0_781Hz ::), (KXTJ3_ODR_1_563Hz ::), (KXTJ3_ODR_3_125Hz ::), (KXTJ3_ODR_6_25Hz ::), 
*    				(KXTJ3_ODR_12_5Hz ::)(KXTJ3_ODR_25Hz ::), (KXTJ3_ODR_50Hz::), (KXTJ3_ODR_100Hz ::),
*					(KXTJ3_ODR_200Hz ::),(KXTJ3_ODR_400Hz ::),(KXTJ3_ODR_800Hz ::),(KXTJ3_ODR_1600Hz ::)
*   @return     Returns (TWI_SUCCESS ::) in case of success and (-ve) error value in case of failure.
********************************************************************************************************************/
twi_s32 twi_accelerometer_kxtj3_set_data_rate_config(tenu_twi_accelerometer_kxtj3_odr_cfg enu_odr);

/*-***********************************************************************************************************
* Function Name:  twi_accelerometer_kxtj3_config_ppi_axis_acc					                             *
**************************************************************************************************************
*	@function 	twi_accelerometer_kxtj3_config_ppi_axis_acc(void)	
*	@brief 		Function used to set the KXTJ3 PPI module configurations		
*   @return     void
*************************************************************************************************************/
void twi_accelerometer_kxtj3_config_ppi_axis_acc(twi_u8* Pu8_acc_buffer, tpf_acc_data_ready pf_acc_data_ready);

/*-***********************************************************************************************************
* Function Name: twi_accelerometer_kxtj3_rtc_config_init							                         *
**************************************************************************************************************
*	@function 	twi_accelerometer_kxtj3_rtc_config_init()	
*	@brief		Function used to set the KXTJ3 RTC module configurations
*   @return  	void   
*************************************************************************************************************/
void twi_accelerometer_kxtj3_rtc_config_init();

/*-***********************************************************************************************************
* Function Name: twi_accelerometer_kxtj3_ppi_init 							                                 *
**************************************************************************************************************
*	@function 	twi_accelerometer_kxtj3_ppi_init()	
*	@brief		Function used to initialize the PPI module
*   @return    	void
*************************************************************************************************************/
void twi_accelerometer_kxtj3_ppi_init();

/*-***********************************************************************************************************
* Function Name: twi_accelerometer_kxtj3_calculate_acc							                             *
**************************************************************************************************************
*	@function 	twi_accelerometer_kxtj3_calculate_acc()	
*	@brief		Function used to calculate the accelerometer values
*   @return    	void 
*************************************************************************************************************/
void twi_accelerometer_kxtj3_calculate_acc();
    
#endif	/* TWI_ACCELEROMETER_KXTJ3_DRIVER_H_ */
