/*
 *  File : GPIOSTM32.h
 *  Author: OMAR MOHAMED AYMAN
 *  https://github.com/OmarAyman95
 *  ommoor642@hotmail.com
 *  this MCAL file is used with STM32F103C6 MCU ARM-CORTEX-M3 based processor
 *  it contains APIs to read/write on the GPIO pins of the MCU
 *  Created on Nov 21, 2022     
 */

#ifndef SRC_GPIOSTM32_H_
#define SRC_GPIOSTM32_H_


/*--------------------------------includes----------------------------------*/
#include "STM32F103.h"
////////////////////////////////port initializations MACROs/////////////////////////////////////


/*--------------------------------macros----------------------------------*/
//PIN_INPUT_MODES_MACROS
#define INPUT_ANALOG         		 (0U)
#define INPUT_FLOATING       		 (1U<<2)
#define INPUT_PULL_UP_DOWN     	     (1U<<3)
#define UP 								(1U)
#define DOWN 							(0U)

//PIN_OUTPUT_MODES_MACROS
#define OUTPUT_PUSH_PULL_10MHZ         	0x1U
#define OUTPUT_PUSH_PULL_2MHZ           0x2U
#define OUTPUT_PUSH_PULL_50MHZ      	0x3U
#define OUTPUT_OPEN_DRAIN_10MHZ      	0x5U
#define OUTPUT_OPEN_DRAIN_2MHZ       	0x6U
#define OUTPUT_OPEN_DRAIN_50MHZ      	0x7U
#define OUTPUT_ALT_PUSH_PULL_10MHZ      0x9U
#define OUTPUT_ALT_PUSH_PULL_2MHZ       0xAU
#define OUTPUT_ALT_PUSH_PULL_50MHZ      0xBU
#define OUTPUT_ALT_OPEN_DRAIN_10MHZ     0xDU
#define OUTPUT_ALT_OPEN_DRAIN_2MHZ      0xEU
#define OUTPUT_ALT_OPEN_DRAIN_50MHZ     0xFU

//PORT_INPUT_MODES_MACROS
#define INPUT_FLOATING_ALL           (0x44444444UL)
#define INPUT_PULL_UP_DOWN_ALL       (0x88888888UL)
//PORT_OUTPUT_MODES_MACROS
#define OUTPUT_PUSH_PULL_10MHZ_ALL    (0x11111111UL)
#define OUTPUT_PUSH_PULL_2MHZ_ALL     (0x22222222UL)
#define OUTPUT_PUSH_PULL_50MHZ_ALL    (0x33333333UL)

//MACROs GPIO_PINx(0~15)

#define GPIO_PIN0                     (0U)
#define GPIO_PIN1                     (1U)
#define GPIO_PIN2                     (2U)
#define GPIO_PIN3                     (3U)
#define GPIO_PIN4                     (4U)
#define GPIO_PIN5                     (5U)
#define GPIO_PIN6                     (6U)
#define GPIO_PIN7                     (7U)
#define GPIO_PIN8                     (8U)
#define GPIO_PIN9                     (9U)
#define GPIO_PIN10                    (10U)
#define GPIO_PIN11                    (11U)
#define GPIO_PIN12                    (12U)
#define GPIO_PIN13                    (13U)
#define GPIO_PIN14                    (14U)
#define GPIO_PIN15                    (15U)

#define GPIO_PIN_ALL                  (0xffff)



/*--------------------------------APIs prototypes------------------------------*/

/**================================================================
* GPIO_Init_Input_Pin
* this function initializes a specific pin to be input pin,
*  selects the mode it is working on
* INPUTS : it takes 4 arguments :
* 1. PORT       >>>  GPIOx    (A-B-C-D)
* 2. pin        >>>  according to MACROs GPIO_PINx(0~15)
* 3. input_mode >>>  according to MACROs (PIN_INPUT_MODES_MACROs)
* 4. up_down    >>>  according to MACROs (UP-DOWN)
* @param [out] -
* it returns nothing !
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void GPIO_Init_Input_Pin(volatile GPIO_t  *PORT,unsigned pin,unsigned input_mode,unsigned up_down);
/**================================================================
* GPIO_Init_Output_Pin
* this function initializes a specific pin to be output pin,
*  selects the mode,speed it is working on
* INPUTS : it takes 3 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. pin         >>>  according to MACROs  GPIO_PINx(0~15)
* 3. output_mode >>>  according to MACROs (PIN_OUTPUT_MODES_MACROS)
* it returns nothing !
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void GPIO_Init_Output_Pin(volatile GPIO_t  *PORT,unsigned pin,unsigned output_mode);
/**================================================================
* GPIO_Set_Pin_Atomic
* this function Sets a specific pin atomic (not using Read-Modify-Write) method.
* the write is done in one instruction.
* it is useful in ISRs.
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. pin         >>>  according to MACROs GPIO_PINx(0~15)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void GPIO_Set_Pin_Atomic(volatile GPIO_t  *PORT,unsigned pin);
/**================================================================
* GPIO_Reset_Pin_Atomic
* this function Clears a specific pin atomic (not using Read-Modify-Write) method.
* the write is done in one instruction.
* it is useful in ISRs.
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. pin         >>>  according to MACROs GPIO_PINx(0~15)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void    GPIO_Reset_Pin_Atomic(volatile GPIO_t  *PORT,unsigned pin);
/**================================================================
* GPIO_Set_Pin
* this function Sets a specific pin .
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. pin         >>>  according to MACROs GPIO_PINx(0~15)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void     GPIO_Set_Pin(volatile GPIO_t  *PORT,unsigned pin);
/**================================================================
* GPIO_Reset_Pin
* this function Clears a specific pin .
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. pin         >>>  according to MACROs GPIO_PINx(0~15)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void      GPIO_Reset_Pin(volatile GPIO_t  *PORT,unsigned pin);
/**================================================================
* GPIO_Toggle_Pin
* this function Toggles a specific pin .
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. pin         >>>  according to MACROs GPIO_PINx(0~15)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void      GPIO_Toggle_Pin(volatile GPIO_t  *PORT,unsigned pin);
/**================================================================
* GPIO_Read_Pin
* this function Reads a specific pin state .
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. pin         >>>  according to MACROs GPIO_PINx(0~15)
* it returns the state of that pin (1 or 0).
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
unsigned  GPIO_Read_Pin(volatile GPIO_t  *PORT,unsigned pin);

/**================================================================
* GPIO_Lock_Pin
* this function Locks a specific pin
* When the LOCK sequence has been applied on a port bit
*  it is no longer possible to modify
*  the value of the port bit until the next reset.
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. pin         >>>  according to MACROs GPIO_PINx(0~15)
* it returns ( 1 or 0 )
* 1: lock is done.
* 0: lock is NOT done.
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/

unsigned   GPIO_Lock_Pin(volatile GPIO_t  *PORT,unsigned pin);
/**================================================================
* GPIO_Set_pins
* this function Sets number of pins without affecting on the other pins .
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. data        >>>  (0x0000~0xffff)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void 		GPIO_Set_pins(volatile GPIO_t  *PORT,unsigned int GPIO_data);
/**================================================================
* GPIO_Reset_pins
* this function Resets number of pins without affecting on the other pins .
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. data        >>>  (0x0000~0xffff)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void 		GPIO_Reset_pins(volatile GPIO_t  *PORT,unsigned int GPIO_data);
/**================================================================
* GPIO_Clear_pins
* this function Clears the Whole port.
* INPUTS : it takes 1 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void 		GPIO_Clear_pins(volatile GPIO_t  *PORT);
/**================================================================
* GPIO_Init_All_Input
* this function initializes the Whole port to be input,
* selects the mode the port is working on.
* INPUTS : it takes 3 arguments :
* 1. PORT       >>>  GPIOx    (A-B-C-D)
* 2. input_mode >>>  according to MACROs (PORT_INPUT_MODES_MACROS)
* 3. up_down    >>>  according to MACROs (UP-DOWN)
* it returns nothing !
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void 		GPIO_Init_All_Input(volatile GPIO_t  *PORT,unsigned input_mode,unsigned up_down);
/**================================================================
* GPIO_Init_All_Output
* this function initializes the Whole port to be input,
* selects the mode the port is working on.
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. output_mode >>>  according to MACROs (PORT_OUTPUT_MODES_MACROS)
* it returns nothing !
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void 		GPIO_Init_All_Output(volatile GPIO_t  *PORT,unsigned output_mode);
/**================================================================
* GPIO_Write_port
* this function Writes a specific value on the Whole port
*  (its affecting on all pins of the port ) .
* INPUTS : it takes 2 arguments :
* 1. PORT            >>>  GPIOx    (A-B-C-D)
* 2. GPIO_data       >>>  (0x0000~0xffff)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void 		GPIO_Write_port(volatile GPIO_t  *PORT,unsigned int GPIO_data);

/**================================================================
* GPIO_Read_port
* this function Reads the value on the Whole port
* INPUTS : it takes 1 arguments :
* 1. PORT            >>>  GPIOx    (A-B-C-D)
* it returns the value of the port. (pins voltages ones or zeros)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/

unsigned 	GPIO_Read_port(volatile GPIO_t  *PORT);

/**================================================================
* GPIO_DeInit
* this function Resets all  registers of a specific port.
* INPUTS : it takes 1 arguments :
* 1. PORT            >>>  GPIOx    (A-B-C-D)
* it returns nothing
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void        GPIO_DeInit(volatile GPIO_t  *PORT);







#endif /* SRC_GPIOSTM32_H_ */
