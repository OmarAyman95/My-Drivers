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


void GPIO_Init_Output_Pin(volatile GPIO_t  *PORT,unsigned pin,unsigned output_mode)
{

	  if((pin>=0) && (pin<=7)) {PORT->CRL &= ~(0xf<<(4*pin)); PORT->CRL |=(output_mode<<(4*pin));}
 else if((pin>=8) && (pin<=15)){PORT->CRH &= ~(0xf<<(4*(pin-8))); PORT->CRH |=(output_mode<<(4*(pin-8)));}

}


void GPIO_Set_Pin_Atomic(volatile GPIO_t  *PORT,unsigned pin)
{
	PORT->BSRR = BIT(pin);
}


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


void GPIO_Reset_Pin_Atomic(volatile GPIO_t  *PORT,unsigned pin)
{
	PORT->BRR = BIT(pin);
}


void GPIO_Set_Pin(volatile GPIO_t  *PORT,unsigned pin)
{
	PORT->ODR |= (1<<pin);
}


void GPIO_Reset_Pin(volatile GPIO_t  *PORT,unsigned pin)
{ 
	PORT->ODR &= ~(1<<pin);
}


void GPIO_Toggle_Pin(volatile GPIO_t  *PORT,unsigned pin)
{
	PORT->ODR ^= (1<<pin);
}


unsigned GPIO_Read_Pin(volatile GPIO_t  *PORT,unsigned pin)
{
	return((PORT->IDR & (1<<pin)));
}


void GPIO_Set_pins(volatile GPIO_t  *PORT,unsigned GPIO_data)
{
	PORT->ODR |=(GPIO_data);
}


void GPIO_Reset_pins(volatile GPIO_t  *PORT,unsigned GPIO_data)
{
	PORT->ODR &= ~(GPIO_data);
}



void GPIO_Clear_pins(volatile GPIO_t  *PORT)
{
	PORT->ODR =(0x00000000UL);
}


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


void GPIO_Init_All_Output(volatile GPIO_t  *PORT,unsigned output_mode)
{
	PORT->CRL &= ~(0xffff);
	PORT->CRH &= ~(0xffff);

	PORT->CRL = (output_mode);
	PORT->CRH = (output_mode);
}


void GPIO_Write_port(volatile GPIO_t  *PORT,unsigned GPIO_data)
{
	PORT->ODR =(GPIO_data);
}


unsigned GPIO_Read_port(volatile GPIO_t  *PORT)
{
	return(PORT->IDR);
}

void GPIO_DeInit(volatile GPIO_t  *PORT)
{

	     if(PORT == GPIOA)  {RCC->APB2RSTR |=(IOPARST);RCC->APB2RSTR &= ~(IOPARST);}
	else if(PORT == GPIOB) 	{RCC->APB2RSTR |=(IOPBRST);RCC->APB2RSTR &= ~(IOPBRST);}
	else if(PORT == GPIOC)  {RCC->APB2RSTR |=(IOPCRST);RCC->APB2RSTR &= ~(IOPCRST);}
	else if(PORT == GPIOD) 	{RCC->APB2RSTR |=(IOPDRST);RCC->APB2RSTR &= ~(IOPDRST);}
	else    {}

}








