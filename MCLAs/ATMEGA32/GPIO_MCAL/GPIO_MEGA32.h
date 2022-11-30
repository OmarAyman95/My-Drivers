/* 
 * File:   GPIO.h
 * Author: OMAR
 *
 * Created on November 28, 2022, 4:01 AM
 */

#ifndef GPIO_H
#define	GPIO_H

#include "ATMGA32MCU.h"

//PINs_MODES_MACROs
#define INPUT_PULL_UP_MODE                  (0b010U)
#define INPUT_FLOATING_MODE                 (0b000U)
#define OUTPUT_MODE                         (0b101U)

//GPIO_PINx_MACROs
#define _PIN0                                (0U)
#define _PIN1                                (1U)
#define _PIN2                                (2U)
#define _PIN3                                (3U)
#define _PIN4                                (4U)
#define _PIN5                                (5U)
#define _PIN6                                (6U)
#define _PIN7                                (7U)
#define ALL_PINS                            (0xffU)                                                   




/**================================================================
* PORT_init
* this function initializes a specific pin to be input pin,
*  output pin , selects the mode it is working on
* INPUTS : it takes 3 arguments :
* 1. GPIOx             >>>  (GPIOA-GPIOB-GPIOC-GPIOD)
* 2. pin_number        >>>  according to MACROs (_PIN0 ~ _PIN7 - ALL_PINS)
* 3. port_mode         >>>  according to MACROs (PINs_MODES_MACROs)
* 
* it returns nothing !
* NOTETHAT : using this function, you can set just one pin,
 * as well as the whole port( pin_number = ALL_PINS)
 * 
*/
void PORT_init(volatile GPIO_t *GPIOx ,uint8_t port_mode,uint8_t pin_number);

/**================================================================
* PORT_Toggle_pin
* this function Toggles a pin of port from H to L and from
 * L to H 
* INPUTS : it takes 2 arguments :
* 1. GPIOx             >>>  (GPIOA-GPIOB-GPIOC-GPIOD)
* 2. pin_number        >>>  according to MACROs (_PIN0 ~ _PIN7)
* it returns nothing !
*/

void PORT_Toggle_pin(volatile GPIO_t *GPIOx ,uint8_t pin_number);

/**================================================================
* PORT_Set_pin
* this function Set a pin of port from L to H  
* INPUTS : it takes 2 arguments :
* 1. GPIOx             >>>  (GPIOA-GPIOB-GPIOC-GPIOD)
* 2. pin_number        >>>  according to MACROs (_PIN0 ~ _PIN7)
* it returns nothing !
*/
void PORT_Set_pin(volatile GPIO_t *GPIOx ,uint8_t pin_number);

/**================================================================
* PORT_Reset_pin
* this function Reset a pin of port from H to L  
* INPUTS : it takes 2 arguments :
* 1. GPIOx             >>>  (GPIOA-GPIOB-GPIOC-GPIOD)
* 2. pin_number        >>>  according to MACROs (_PIN0 ~ _PIN7)
* it returns nothing !
*/
void PORT_Reset_pin(volatile GPIO_t *GPIOx ,uint8_t pin_number);

/**================================================================
* PORT_Read
* this function Reads a port value.  
* INPUTS : it takes 1 argument :
* 1. GPIOx             >>>  (GPIOA-GPIOB-GPIOC-GPIOD)
* it returns the 8bit port value !
*/
uint8_t PORT_Read(volatile GPIO_t *GPIOx);

/**================================================================
* PORT_Write
* this function Writes a value to the whole port.  
 * this function takes an action and affects all the pins at the same time
* INPUTS : it takes 2 arguments :
* 1. GPIOx             >>>  (GPIOA-GPIOB-GPIOC-GPIOD)
* 2. data              >>>  (8bit) value to write it on the port 
* it returns nothing !
*/
void PORT_Write(volatile GPIO_t *GPIOx ,uint8_t data);


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_H */

