#include "GPIO_MEGA32.h"


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
void PORT_init(volatile GPIO_t *GPIOx ,uint8_t port_mode,uint8_t pin_number)
{    
    if(pin_number >=0 && pin_number <=7 )
    {
        if(port_mode == INPUT_FLOATING_MODE)
        {
            GPIOx->DDR  &= ~(1U<<pin_number);
            GPIOx->PORT &= ~(1U<<pin_number);
             SFIOR_REG->PUDBIT =0;
        }
        else if(port_mode ==INPUT_PULL_UP_MODE)
        { 
            GPIOx->DDR  &= ~(1U<<pin_number);
            GPIOx->PORT |= (1U<<pin_number);
            SFIOR_REG->PUDBIT =0;
        }
        else if(port_mode ==OUTPUT_MODE)
        {
             GPIOx->DDR  |= (1U<<pin_number);
             GPIOx->PORT &= ~(1U<<pin_number);
        }
        else{}
    }
    else if (pin_number == ALL_PINS)
    {
        if(port_mode == INPUT_FLOATING_MODE)
        {
            GPIOx->DDR  &= ~(ALL_PINS);
            GPIOx->PORT |= (ALL_PINS);
            SFIOR_REG->PUDBIT =0;
        }
        else if(port_mode ==INPUT_PULL_UP_MODE)
        {
            GPIOx->DDR  &= ~(ALL_PINS);
            GPIOx->PORT |= (ALL_PINS);
            SFIOR_REG->PUDBIT =0;
            
        }
        else if(port_mode ==OUTPUT_MODE)
        {
             GPIOx->DDR  |= (ALL_PINS);
             GPIOx->PORT &= ~(ALL_PINS);  
        }
        else{}
    }
    else{}
}

/**================================================================
* PORT_Toggle_pin
* this function Toggles a pin of port from H to L and from
 * L to H 
* INPUTS : it takes 2 arguments :
* 1. GPIOx             >>>  (GPIOA-GPIOB-GPIOC-GPIOD)
* 2. pin_number        >>>  according to MACROs (_PIN0 ~ _PIN7)
* it returns nothing !
*/

void PORT_Toggle_pin(volatile GPIO_t *GPIOx ,uint8_t pin_number)
{
    if(pin_number<=7)
    GPIOx->PORT ^=(1U<<pin_number);
}


/**================================================================
* PORT_Set_pin
* this function Set a pin of port from L to H  
* INPUTS : it takes 2 arguments :
* 1. GPIOx             >>>  (GPIOA-GPIOB-GPIOC-GPIOD)
* 2. pin_number        >>>  according to MACROs (_PIN0 ~ _PIN7)
* it returns nothing !
*/
void PORT_Set_pin(volatile GPIO_t *GPIOx ,uint8_t pin_number)
{
    if(pin_number<=7)
    GPIOx->PORT |=(1U<<pin_number);
}

/**================================================================
* PORT_Reset_pin
* this function Reset a pin of port from H to L  
* INPUTS : it takes 2 arguments :
* 1. GPIOx             >>>  (GPIOA-GPIOB-GPIOC-GPIOD)
* 2. pin_number        >>>  according to MACROs (_PIN0 ~ _PIN7)
* it returns nothing !
*/
void PORT_Reset_pin(volatile GPIO_t *GPIOx ,uint8_t pin_number)
{
    if(pin_number<=7)
    GPIOx->PORT &= ~(1U<<pin_number);
}
/**================================================================
* PORT_Read
* this function Reads a port value.  
* INPUTS : it takes 1 argument :
* 1. GPIOx             >>>  (GPIOA-GPIOB-GPIOC-GPIOD)
* it returns the 8bit port value !
*/
uint8_t PORT_Read(volatile GPIO_t *GPIOx)
{
    return(GPIOx->PIN);
}

/**================================================================
* PORT_Write
* this function Writes a value to the whole port.  
 * this function takes an action and affects all the pins at the same time
* INPUTS : it takes 2 arguments :
* 1. GPIOx             >>>  (GPIOA-GPIOB-GPIOC-GPIOD)
* 2. data              >>>  (8bit) value to write it on the port 
* it returns nothing !
*/
void PORT_Write(volatile GPIO_t *GPIOx ,uint8_t data)
{
    GPIOx->PORT = data;
}
