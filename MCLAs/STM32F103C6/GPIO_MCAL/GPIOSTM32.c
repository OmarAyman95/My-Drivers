/*
 *  File : GPIOSTM32.c
 *  Author: OMAR MOHAMED AYMAN
 *  https://github.com/OmarAyman95
 *  ommoor642@hotmail.com
 *  this MCAL file is used with STM32F103C6 MCU ARM-CORTEX-M3 based processor
 *  it contains APIs to read/write on the GPIO pins of the MCU
 *  Created on Nov 21, 2022     
 */


/*--------------------------------includes----------------------------------*/
#include "GPIOSTM32.h"
 

/*--------------------------------Global Definitions-----------------------*/




/*--------------------------------APIs Definitions-----------------------*/




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
void GPIO_Init_Input_Pin(volatile GPIO_t  *PORT,unsigned pin,unsigned input_mode,unsigned up_down)
{
	//PULL UP - PULL DOWN - FLOATING _ANALOG
		 	  if((pin>=0) && (pin<=7))  {PORT->CRL &= ~(0xf<<(4*pin));PORT->CRL |=(input_mode<<(4*pin));}
		 else if((pin>=8) && (pin<=15)) {PORT->CRH &= ~(0xf<<(4*(pin-8)));PORT->CRH |=(input_mode<<(4*(pin-8)));}
   //PULL UP - PULL DOWN
		 	 if(input_mode == INPUT_PULL_UP_DOWN)
		 	 	{
		if(up_down == DOWN)     PORT->ODR&= ~(BIT(pin));
		else if(up_down == UP)  PORT->ODR|=(BIT(pin));
		 	 	}
}




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
void GPIO_Init_Output_Pin(volatile GPIO_t  *PORT,unsigned pin,unsigned output_mode)
{

	  if((pin>=0) && (pin<=7)) {PORT->CRL &= ~(0xf<<(4*pin)); PORT->CRL |=(output_mode<<(4*pin));}
 else if((pin>=8) && (pin<=15)){PORT->CRH &= ~(0xf<<(4*(pin-8))); PORT->CRH |=(output_mode<<(4*(pin-8)));}

}



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
void GPIO_Set_Pin_Atomic(volatile GPIO_t  *PORT,unsigned pin)
{
	PORT->BSRR = BIT(pin);
}

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

void GPIO_Reset_Pin_Atomic(volatile GPIO_t  *PORT,unsigned pin)
{
	PORT->BRR = BIT(pin);
}


/**================================================================
* GPIO_Set_Pin
* this function Sets a specific pin .
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. pin         >>>  according to MACROs GPIO_PINx(0~15)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/

void GPIO_Set_Pin(volatile GPIO_t  *PORT,unsigned pin)
{
	PORT->ODR |= (1<<pin);
}


/**================================================================
* GPIO_Reset_Pin
* this function Clears a specific pin .
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. pin         >>>  according to MACROs GPIO_PINx(0~15)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void GPIO_Reset_Pin(volatile GPIO_t  *PORT,unsigned pin)
{ 
	PORT->ODR &= ~(1<<pin);
}


/**================================================================
* GPIO_Toggle_Pin
* this function Toggles a specific pin .
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. pin         >>>  according to MACROs GPIO_PINx(0~15)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/


void GPIO_Toggle_Pin(volatile GPIO_t  *PORT,unsigned pin)
{
	PORT->ODR ^= (1<<pin);
}
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

unsigned GPIO_Read_Pin(volatile GPIO_t  *PORT,unsigned pin)
{
	return((PORT->IDR & (1<<pin)));
}
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

unsigned GPIO_Lock_Pin(volatile GPIO_t  *PORT,unsigned pin)
{
	volatile unsigned temp ;
	/*LOCK key writing sequence:
	Write 1
	Write 0
	Write 1
	Read 0
	Read 1 (this read is optional but confirms that the lock is active)
	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	Any error in the lock sequence will abort the lock.*/
	PORT->LCKR = ((1U<<16) | (~(1U<<pin)));
	PORT->LCKR = (1U<<pin);
	PORT->LCKR = ((1U<<16) | (~(1U<<pin)));
	temp = PORT->LCKR;
	temp = (PORT->LCKR & (1<<16));
	if(temp == (1<<16))return (1);
	else return (0);
}


/**================================================================
* GPIO_Set_pins
* this function Sets number of pins without affecting on the other pins .
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. data        >>>  (0x0000~0xffff)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/

void GPIO_Set_pins(volatile GPIO_t  *PORT,unsigned GPIO_data)
{
	PORT->ODR |=(GPIO_data);
}

/**================================================================
* GPIO_Reset_pins
* this function Resets number of pins without affecting on the other pins .
* INPUTS : it takes 2 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* 2. data        >>>  (0x0000~0xffff)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void GPIO_Reset_pins(volatile GPIO_t  *PORT,unsigned GPIO_data)
{
	PORT->ODR &= ~(GPIO_data);
}


/**================================================================
* GPIO_Clear_pins
* this function Clears the Whole port.
* INPUTS : it takes 1 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/


void GPIO_Clear_pins(volatile GPIO_t  *PORT)
{
	PORT->ODR =(0x00000000UL);
}

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

void GPIO_Init_All_Input(volatile GPIO_t  *PORT,unsigned input_mode,unsigned up_down)
{
	PORT->CRL &= ~(0xffff);
	PORT->CRH &= ~(0xffff);

	PORT->CRL = (input_mode);
	PORT->CRH = (input_mode);

	//PULL UP - PULL DOWN
	if(input_mode == INPUT_PULL_UP_DOWN)
	{
	if(up_down == DOWN)     PORT->ODR&= ~(0xffffffff);
	else if(up_down == UP)  PORT->ODR|=(0xffffffff);
	}
}
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

void GPIO_Init_All_Output(volatile GPIO_t  *PORT,unsigned output_mode)
{
	PORT->CRL &= ~(0xffff);
	PORT->CRH &= ~(0xffff);

	PORT->CRL = (output_mode);
	PORT->CRH = (output_mode);
}


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


void GPIO_Write_port(volatile GPIO_t  *PORT,unsigned GPIO_data)
{
	PORT->ODR =(GPIO_data);
}

/**================================================================
* GPIO_Read_port
* this function Reads the value on the Whole port
* INPUTS : it takes 1 arguments :
* 1. PORT            >>>  GPIOx    (A-B-C-D)
* it returns the value of the port. (pins voltages ones or zeros)
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
unsigned GPIO_Read_port(volatile GPIO_t  *PORT)
{
	return(PORT->IDR);
}
/**================================================================
* GPIO_DeInit
* this function Resets all  registers of a specific port.
* INPUTS : it takes 1 arguments :
* 1. PORT            >>>  GPIOx    (A-B-C-D)
* it returns nothing
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
*            GPIOC,GPIOD have 3,2 pins respectively
*/
void GPIO_DeInit(volatile GPIO_t  *PORT)
{

	     if(PORT == GPIOA)  {RCC->APB2RSTR |=(IOPARST);RCC->APB2RSTR &= ~(IOPARST);}
	else if(PORT == GPIOB) 	{RCC->APB2RSTR |=(IOPBRST);RCC->APB2RSTR &= ~(IOPBRST);}
	else if(PORT == GPIOC)  {RCC->APB2RSTR |=(IOPCRST);RCC->APB2RSTR &= ~(IOPCRST);}
	else if(PORT == GPIOD) 	{RCC->APB2RSTR |=(IOPDRST);RCC->APB2RSTR &= ~(IOPDRST);}
	else    {}

}


