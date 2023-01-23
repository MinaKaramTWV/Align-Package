/*-**************************************************************************-*/
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */
/*- Unauthorized copying of this file or portions thereof,                    */
/*- via any medium, is strictly prohibited.                                   */
/*- Proprietary and confidential.                                             */
/*-**************************************************************************-*/

/**
*   @file       twi_gpio.h
*   @brief      This file implements TWI GPIO HAL Header File.
*/

#ifndef _TWI_GPIO_H_
#define _TWI_GPIO_H_
/**
*   @defgroup gpio_group TWI GPIO HAL
*   This is the definition of TWI HAL for GPIO.
*   @{
*/

/*----------------------------------------------------------*/
/*- INCLUDES -----------------------------------------------*/
/*----------------------------------------------------------*/

#include "twi_common.h"
#include "platform_defines.h"

/*----------------------------------------------------------*/
/*- CONSTANTS ----------------------------------------------*/
/*----------------------------------------------------------*/
#define TWI_GPIO_DISABLE_GPIO_IRQ()			twi_gpio_disable_gpio_irq()

#define	TWI_GPIO_ENABLE_GPIO_IRQ()			twi_gpio_enable_gpio_irq()
#define TWI_INVALID_CHANNEL_NUM                  (0xff)

#define PORT_POS                PLATFORM_PORT_POS				 /**<    @brief  The position of the Port.   */
#define PINS_MASK               PLATFORM_PIN_MASK				 /**<    @brief The mask for the pins.       */

#define TOTAL_PINS_COUNT        PLATFORM_TOTAL_PINS_COUNT   	 /**< 	 @The total number of GPIO pins in the platform.*/

#define PORTS_COUNT             PLATFORM_PORTS_COUNT        	 /**<    @brief  Number of available ports.  */

#define TWI_PORTA                   (0)                            /**<    @brief  GPIO TWI_PORTA. */
#define TWI_PORTB                   (1)                            /**<    @brief  GPIO TWI_PORTB. */
#define TWI_PORTC                   (2)
#define TWI_PORTD                   (3)
#define TWI_PORTE                   (4)
#define TWI_PORTF                   (5)
#define TWI_PORTG                   (6)
#define TWI_PORTH                   (7)
#define TWI_PORTI                   (8)
#define TWI_PORTJ                   (9)
#define TWI_PORTK                   (10)
#define TWI_PORTL                   (11)
#define TWI_PORTM                   (12)
#define TWI_PORTN                   (13)
#define TWI_PORTO                   (14)
#define TWI_PORTP                   (15)
#define TWI_PORTQ                   (16)

#define TWI_PORT0                   0                            /**<    @brief  GPIO TWI_PORT0. */

#define TWI_PORT1                   1                            /**<    @brief  GPIO TWI_PORT1. */

#define TWI_PORT2                   2                            /**<    @brief  GPIO TWI_PORT2. */

#define TWI_PORT3                   3                            /**<    @brief   GPIO TWI_PORT3. */

#define TWI_PORT4                   4                            /**<    @brief   GPIO TWI_PORT4. */

#define TWI_PORT5                   5                            /**<    @brief   GPIO TWI_PORT5. */

#define TWI_PORT6                   6                            /**<    @brief   GPIO TWI_PORT6. */

#define TWI_PORT7                   7                            /**<    @brief   GPIO TWI_PORT7. */

#define TWI_PORT8                   8                            /**<    @brief   GPIO TWI_PORT8. */

#define TWI_PORT9                   9                            /**<    @brief   GPIO TWI_PORT9. */

#define TWI_PORT10                  10                            /**<    @brief   GPIO TWI_PORT10. */

#define TWI_PORT11                 	11                            /**<    @brief   GPIO TWI_PORT11. */

#define TWI_PORT12                 	12                            /**<    @brief   GPIO TWI_PORT12. */

#define TWI_PORT13                  13                            /**<    @brief   GPIO TWI_PORT13. */

#define TWI_PORT14                  14                            /**<    @brief   GPIO TWI_PORT14. */


#define PINS_COUNT              PLATFORM_PINS_COUNT         	 /**<    @brief  Number of available pins.  */

#define TWI_PIN0                    0                            /**<    @brief  GPIO TWI_PIN0.  */

#define TWI_PIN1                    1                            /**<    @brief  GPIO TWI_PIN1.  */

#define TWI_PIN2                    2                            /**<    @brief  GPIO TWI_PIN2.  */

#define TWI_PIN3                    3                            /**<    @brief  GPIO TWI_PIN3.  */

#define TWI_PIN4                    4                            /**<    @brief  GPIO TWI_PIN4.  */

#define TWI_PIN5                    5                            /**<    @brief  GPIO TWI_PIN5.  */

#define TWI_PIN6                    6                            /**<    @brief  GPIO TWI_PIN6.  */

#define TWI_PIN7                    7                            /**<    @brief  GPIO TWI_PIN7.  */

#define TWI_PIN8                    8                            /**<    @brief  GPIO TWI_PIN8.  */

#define TWI_PIN9                    9                            /**<    @brief  GPIO TWI_PIN9.  */

#define TWI_PIN10                    10                          /**<    @brief  GPIO TWI_PIN10.  */

#define TWI_PIN11                   11                           /**<    @brief  GPIO TWI_PIN11.  */

#define TWI_PIN12                    12                           /**<    @brief  GPIO TWI_PIN12.  */

#define TWI_PIN13                    13                           /**<    @brief  GPIO TWI_PIN13.  */

#define TWI_PIN14                    14                           /**<    @brief  GPIO TWI_PIN14.  */

#define TWI_PIN15                    15                           /**<    @brief  GPIO TWI_PIN15.  */

#define TWI_PIN16                    16                           /**<    @brief  GPIO TWI_PIN16.  */

#define TWI_PIN17                    17                           /**<    @brief  GPIO TWI_PIN17.  */

#define TWI_PIN18                    18                           /**<    @brief  GPIO TWI_PIN18.  */

#define TWI_PIN19                    19                           /**<    @brief  GPIO TWI_PIN19.  */

#define TWI_PIN20                    20                           /**<    @brief  GPIO TWI_PIN20.  */

#define TWI_PIN21                    21                           /**<    @brief  GPIO TWI_PIN21.  */

#define TWI_PIN22                    22                           /**<    @brief  GPIO TWI_PIN22.  */

#define TWI_PIN23                    23                           /**<    @brief  GPIO TWI_PIN23.  */

#define TWI_PIN24                    24                           /**<    @brief  GPIO TWI_PIN24.  */

#define TWI_PIN25                    25                           /**<    @brief  GPIO TWI_PIN25.  */

#define TWI_PIN26                    26                           /**<    @brief  GPIO TWI_PIN26.  */

#define TWI_PIN27                    27                           /**<    @brief  GPIO TWI_PIN27.  */

#define TWI_PIN28                    28                           /**<    @brief  GPIO TWI_PIN28.  */

#define TWI_PIN29                    29                           /**<    @brief  GPIO TWI_PIN29.  */

#define TWI_PIN30                    30                           /**<    @brief  GPIO TWI_PIN30.  */

#define TWI_PIN31                    31                           /**<    @brief  GPIO TWI_PIN31.  */

#define INV_PORT					0xFF
#define INV_PIN						0xFF


#define TWI_GPIO_DIR            	0x1                           /**<    @brief  Pin direction mask.             */

#define TWI_GPIO_DIR_IN         	0x0                           /**<    @brief  Define the pin as an input pin. */

#define TWI_GPIO_DIR_OUT        	0x1                        	  /**<    @brief  Define the pin as an output pin.*/

#define TWI_GPIO_PULL           	0x6                        	  /**<    @brief  Pull resistor mask.             */

#define TWI_GPIO_PULL_UP        	0x2                        	  /**<    @brief  Pull UP mask */

#define TWI_GPIO_NO_PULL            0x0							/**<    @brief  Define the pin as a floating pin. */


#define TWI_GPIO_PULL_DOWN      	0x6                        	  /**<    @brief  Pull Down mask.*/

#define TWI_GPIO_MONITOR_ENABLE  	TWI_TRUE                  	  /**<    @brief  GPIO monitor enable.            */

#define TWI_GPIO_MONITOR_DISABLE 	TWI_FALSE                  	  /**<    @brief  GPIO monitor disable.           */

/**
*   @defgroup gpio_monitor_flags_group TWI GPIO Monitor Flags
*   This is the GPIO Monitor flags.
*   @{
*/

#define TWI_GPIO_EDGE_RISING_POS    1                                   /**<    @brief  Monitor raising edge flag position. */

#define TWI_GPIO_EDGE_RISING_MASK   (1 << TWI_GPIO_EDGE_RISING_POS)     /**<    @brief  Monitor raising edge flag mask. */

#define TWI_GPIO_EDGE_RISING        (1 << TWI_GPIO_EDGE_RISING_POS)     /**<    @brief  Monitor raising edge  flag. */

#define TWI_GPIO_EDGE_FALLING_POS   2                                   /**<    @brief  Monitor falling edge flag position. */

#define TWI_GPIO_EDGE_FALLING_MASK  (1 << TWI_GPIO_EDGE_FALLING_POS)    /**<    @brief  Monitor falling edge flag mask. */

#define TWI_GPIO_EDGE_FALLING       (1 << TWI_GPIO_EDGE_FALLING_POS)    /**<    @brief  Monitor falling edge flag. */

#define TWI_GPIO_LEVEL_POS          3                                   /**<    @brief  Monitor level flag position. */

#define TWI_GPIO_LEVEL_MASK         (3 << TWI_GPIO_LEVEL_POS)           /**<    @brief  Monitor level flag mask. */

#define TWI_GPIO_LEVEL_HIGH         (1 << TWI_GPIO_LEVEL_POS)           /**<    @brief  Monitor high level flag. */

#define TWI_GPIO_LEVEL_LOW          (2 << TWI_GPIO_LEVEL_POS)           /**<    @brief  Monitor low level flag. */

/** @} */   /*gpio_monitor_flags_group*/

/*----------------------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*----------------------------------------------------------*/

typedef void(*tpf_twi_gpio_cb)(twi_u8 u8_port, twi_u8 u8_pin);

/*----------------------------------------------------------*/
/*- ENUMS --------------------------------------------------*/
/*----------------------------------------------------------*/

typedef enum _tenu_gpio_func_mult
{
	TWI_PIN_FUNC_GPIO = 0,
	TWI_PIN_FUNC_I2C_SCL,
	TWI_PIN_FUNC_I2C_SDA,
    TWI_PIN_FUNC_UART_RX,
    TWI_PIN_FUNC_UART_TX,
	TWI_PIN_FUNC_PWM,
    TWI_PIN_FUNC_ENET_LED,
    TWI_PIN_FUNC_INVALID
}tenu_gpio_func_mult;

/*----------------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/
/*----------------------------------------------------------*/

#ifdef __cplusplus
    extern "C"
    {
#endif

/**
*   @brief      This function Disables GPIO interrupts.
*/		
void twi_gpio_disable_gpio_irq(void);
	
/**
*   @brief      This function Enables GPIO interrupts.
*/			
void twi_gpio_enable_gpio_irq(void);
		
/**
*   @brief      This function initializes the GPIO module.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_gpio_init(void);

/**
*   @brief      This function used to select a GPIO pin.
*   @param[in]  u8_port    Port number. It can set to one of ::TWI_PORTA, ::TWI_PORTB, ::TWI_PORTC, or ::TWI_PORTD.
*   @param[in]  u8_pin     Pin number. It can be set in range from ::TWI_PIN0 to ::TWI_PIN7.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_gpio_select(twi_u8 u8_port, twi_u8 u8_pin);

/**
*   @brief      This function that de-select a GPIO pin.
*   @param[in]  u8_port     Port number. It can be ::TWI_PORTA, ::TWI_PORTB, ::TWI_PORTC, or ::TWI_PORTD.
*   @param[in]  u8_pin      Pin number.  It is in range from ::TWI_PIN0 to ::TWI_PIN7.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_gpio_deselect(twi_u8 u8_port, twi_u8 u8_pin);

/**
*   @brief      This function that set the configuration of the GPIO module.
*   @details    To guarantee proper work, that pin has to be selected using twi_gpio_select().
*   @param[in]  u8_port         Port number. It can be ::TWI_TWI_PORTA, ::TWI_TWI_PORTB, ::TWI_TWI_PORTC, or ::TWI_TWI_PORTD.
*   @param[in]  u8_pin          Pin number. It in range from ::TWI_TWI_PIN0 to ::TWI_PIN7.
*   @param[in]  u8_config       Pin configuration. It can be ::TWI_GPIO_DIR_IN, ::TWI_GPIO_DIR_OUT, ::TWI_GPIO_PULL_UP, and ::TWI_GPIO_PULL_DOWN.
*   @param[in]  enu_func    Functionality module. It is can be :: tenu_gpio_func_mult.
*   @param[in]  u8_channel_num       channel number. like :: I2C1, :: I2C2.
*   @return     ::TWI_SUCCESS in case of success, -ve number in case of error
*/
twi_s32 twi_gpio_set_configure(twi_u8 u8_port, twi_u8 u8_pin, twi_u8 u8_config, tenu_gpio_func_mult enu_func, twi_u8 u8_channel_num);

/**
*   @brief       This function that get the configuration of the GPIO module.
*   @details     To guarantee proper work, that pin has to be selected using twi_gpio_select().
*   @param[in]   u8_port         Port number. It can be ::TWI_TWI_PORTA, ::TWI_TWI_PORTB, ::TWI_TWI_PORTC, or ::TWI_TWI_PORTD.
*   @param[in]   u8_pin          Pin number. It in range from ::TWI_TWI_PIN0 to ::TWI_PIN7.
*   @param[out]  pu8_config      Pin configuration. It can be ::TWI_GPIO_DIR_IN, ::TWI_GPIO_DIR_OUT, ::TWI_GPIO_PULL_UP, and ::TWI_GPIO_PULL_DOWN.
*   @param[out]  enu_func        Functionality module. It is can be :: tenu_gpio_func_mult.
*   @param[out]  u8_channel_num   channel number. like :: I2C1, :: I2C2.
*   @return     ::TWI_SUCCESS    in case of success, -ve number in case of error
*/
twi_s32 twi_gpio_get_configure(twi_u8 u8_port, twi_u8 u8_pin, twi_u8* pu8_config, tenu_gpio_func_mult* penu_func, twi_u8* pu8_channel_num);

/**
*   @brief      This function that sets a GPIO to one.
*   @details    To guarantee proper work, that pin has to be selected using @ref twi_gpio_select and set as an output using @ref twi_gpio_set_configure
*   @param[in]  u8_port       Port number. It can be ::TWI_PORTA, ::TWI_PORTB, ::TWI_PORTC, or ::TWI_PORTD.
*   @param[in]  u8_pin        Pin number. It is in range from ::TWI_PIN0 to ::TWI_PIN7.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_gpio_set(twi_u8 u8_port, twi_u8 u8_pin);

/**
*   @brief      This function that clears a GPIO to zero.
*   @details    To guarantee proper work, that pin has to be selected using @ref twi_gpio_select and set as an output using @ref twi_gpio_set_configure
*   @param[in]  u8_port      Port number. It can be ::TWI_PORTA, ::TWI_PORTB, ::TWI_PORTC, or ::TWI_PORTD.
*   @param[in]  u8_pin       Pin number. It is in range from ::TWI_PIN0 to ::TWI_PIN7.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_gpio_clear(twi_u8 u8_port, twi_u8 u8_pin);

/**
*   @brief      This function that toggles a GPIO pin.
*   @details    To guarantee proper work, that pin has to be selected using
*               @ref twi_gpio_select and set as an output using
*               @ref twi_gpio_set_configure
*   @param[in]  u8_port     Port number. It can be ::TWI_PORTA, ::TWI_PORTB, ::TWI_PORTC, or ::TWI_PORTD.
*   @param[in]  u8_pin      Pin number. It is in range from ::TWI_PIN0 to ::TWI_PIN7.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_gpio_toggle(twi_u8 u8_port, twi_u8 u8_pin);

/**
*   @brief      This function that reads a GPIO pin.
*   @details    To guarantee proper work, that pin has to be selected using
*               @ref twi_gpio_select and set as an input using
*               @ref twi_gpio_set_configure
*   @param[in]  u8_port     Port number. It can be ::TWI_PORTA, ::TWI_PORTB, ::TWI_PORTC, or ::TWI_PORTD.
*   @param[in]  u8_pin      Pin number. It is in range from ::TWI_PIN0 to ::TWI_PIN7.
*   @param[out] pb_value    Pin value. It can be either :TWI_TRUE or ::TWI_FALSE.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_gpio_read(twi_u8 u8_port, twi_u8 u8_pin, twi_bool *pb_value);

/**
*   @brief      This function that monitors a GPIO pin.
*   @details    To guarantee proper work, that pin has to be selected using
*               twi_gpio_select(), set as an input using
*               twi_gpio_set_configure(), register the interrupt using this function, and
*               enable it using twi_gpio_enable_interrupt.
*   @param[in]  u8_port         Port number. It can be ::TWI_PORTA, ::TWI_PORTB, ::TWI_PORTC, or ::TWI_PORTD.
*   @param[in]  u8_pin          Pin number. It in range from ::TWI_PIN0 to ::TWI_PIN7.
*   @param[in]  u8_flags        Edge/Level to be monitored. Please check @ref gpio_monitor_flags_group.
*   @param[in]  twi_gpio_cb     Pointer to a call back function that will be called by the module when the trigger achieved.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_gpio_register_interrupt(twi_u8 u8_port, twi_u8 u8_pin, twi_u8 u8_flags, tpf_twi_gpio_cb twi_gpio_cb);

/**
*   @brief      This function that enable an already registered interrupt on a GPIO pin.
*   @param[in]  u8_port         Port number. It can be ::TWI_PORTA, ::TWI_PORTB, ::TWI_PORTC, or ::TWI_PORTD.
*   @param[in]  u8_pin          Pin number. It in range from ::TWI_PIN0 to ::TWI_PIN7.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_gpio_enable_interrupt(twi_u8 u8_port, twi_u8 u8_pin);

/**
*   @brief      This function that disable monitoring a GPIO pin.
*   @param[in]  u8_port         Port number. It can be ::TWI_PORTA, ::TWI_PORTB, ::TWI_PORTC, or ::TWI_PORTD.
*   @param[in]  u8_pin          Pin number. It in range from ::TWI_PIN0 to ::TWI_PIN7.
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_gpio_disable_interrupt(twi_u8 u8_port, twi_u8 u8_pin);

/**
*   @brief      This function that check if the interrupt is enabled for a specific pin or not.
*   @param[in]  u8_port         Port number. It can be ::TWI_PORTA, ::TWI_PORTB, ::TWI_PORTC, or ::TWI_PORTD.
*   @param[in]  u8_pin          Pin number. It in range from ::TWI_PIN0 to ::TWI_PIN7.
*	@param[out]	pb_val			value of the interrupt. TWI_TRUE if Enabled, TWI_FALSE otherwise
*   @return     ::TWI_SUCCESS in case of success, otherwise refer to @ref  twi_retval.h
*/
twi_s32 twi_gpio_interrupt_is_enabled(twi_u8 u8_port, twi_u8 u8_pin, twi_bool *pb_val);

/**
*	@brief      This function select and configure any GPIO module..
*   @param[in]  u8_port         Port number. It can be ::TWI_TWI_PORTA, ::TWI_TWI_PORTB, ::TWI_TWI_PORTC, or ::TWI_TWI_PORTD.
*   @param[in]  u8_pin          Pin number. It in range from ::TWI_TWI_PIN0 to ::TWI_PIN7.
*   @param[in]  u8_config       Pin configuration. It can be ::TWI_GPIO_DIR_IN, ::TWI_GPIO_DIR_OUT, ::TWI_GPIO_PULL_UP, and ::TWI_GPIO_PULL_DOWN.
*   @param[in]  enu_func    Functionality module. It is can be :: tenu_gpio_func_mult.
*   @param[in]  u8_channel_num       channel number. like :: I2C1, :: I2C2.
*   @return     ::TWI_SUCCESS in case of success, -ve number in case of error
*/
twi_s32 twi_gpio_pin_cnfg(twi_u8 u8_port, twi_u8 u8_pin, twi_u8 u8_config, tenu_gpio_func_mult enu_func, twi_u8 u8_channel_num);

#ifdef __cplusplus
    }
#endif

/** @} */   /*gpio_group*/

#endif  /*_TWI_GPIO_H_*/
