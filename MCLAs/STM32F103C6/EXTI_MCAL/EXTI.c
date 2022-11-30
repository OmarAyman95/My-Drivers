/*
 * EXTI.c
 *
 *  Created on: Nov 25, 2022
 *      Author: OMAR
 */

#include "EXTI.h"

int32_t External_Interrupt_Line= -1;
void(*ptrToIRQx[15])(void);

static void External_Interrupt_Edge_Selector(uint8_t pin_no,uint8_t edge)
{

	EXTI->FTSR &=~(1U<<pin_no);
	EXTI->RTSR &=~(1U<<pin_no);

	      if (edge == 0)EXTI->FTSR|=(1U<<pin_no);
	 else if (edge == 1)EXTI->RTSR|=(1U<<pin_no);
	 else if (edge == 2){EXTI->FTSR|=(1U<<pin_no);EXTI->RTSR|=(1U<<pin_no);}
	 else               {}
}

static void Interrupt_Mask_Enable(uint8_t pin_no)
{
	EXTI->IMR |=(1U<<pin_no);
}


static void Interrupt_Setting(uint8_t pin_no,uint8_t edge,void(*ptrTofun)(void))
{
		Interrupt_Mask_Enable(pin_no);
		External_Interrupt_Edge_Selector(pin_no, edge);
		ptrToIRQx[pin_no] = ptrTofun;
		Enable_IRQx(pin_no);
}

/**================================================================
* Enable_IRQx
* this function Enables a specific line of interrupt
* INPUTS : it takes 1 argument :
* 1. external_interrupt_line   >>>  according to (Disable_IRQx & Enable_IRQx MACROs)
*    or pin_number(0~15);
* it returns nothing !
*/

void Enable_IRQx(uint8_t external_interrupt_line)
{
	if(external_interrupt_line == 0)
		{NVIC_ISER0 |= (NVIC_EXTI0);}
	else if(external_interrupt_line == 1)
		{NVIC_ISER0 |= (NVIC_EXTI1);}
	else if(external_interrupt_line ==2)
		{NVIC_ISER0 |= (NVIC_EXTI2);}
	else if(external_interrupt_line ==3)
		{NVIC_ISER0 |= (NVIC_EXTI3);}
	else if(external_interrupt_line ==4)
		{NVIC_ISER0 |= (NVIC_EXTI4);}
	else if((external_interrupt_line >=5) && (external_interrupt_line<=9))
		{NVIC_ISER0 |= (NVIC_EXTI5_9);}
	else if((external_interrupt_line >=10) && (external_interrupt_line<=15))
		{NVIC_ISER1 |= (NVIC_EXTI10_15);}
	else{}
}

/**================================================================
* Disable_IRQx
* this function Disables a specific line of interrupt
* INPUTS : it takes 1 argument :
* 1. external_interrupt_line   >>>  according to (Disable_IRQx & Enable_IRQx MACROs)
*                                   or (GPIO_PINx_MACROs)
* it returns nothing !
*/
void Disable_IRQx(uint8_t external_interrupt_line)
{
			 if(external_interrupt_line == 0)
			{NVIC_ICER0 |= (NVIC_EXTI0);}
		else if(external_interrupt_line == 1)
			{NVIC_ICER0 |= (NVIC_EXTI1);}
		else if(external_interrupt_line ==2)
			{NVIC_ICER0 |= (NVIC_EXTI2);}
		else if(external_interrupt_line ==3)
			{NVIC_ICER0 |= (NVIC_EXTI3);}
		else if(external_interrupt_line ==4)
			{NVIC_ICER0 |= (NVIC_EXTI4);}
		else if((external_interrupt_line >=5) && (external_interrupt_line<=9))
			{NVIC_ICER0 |= (NVIC_EXTI5_9);}
		else if((external_interrupt_line >=10) && (external_interrupt_line<=15))
			{NVIC_ICER1 |= (NVIC_EXTI10_15);}
		else {}

}
/**================================================================
* interrupt_init
* this function initializes a specific pin to be input pin,
*  selects the mode it is working on
* INPUTS : it takes 4 arguments :
* 1. PORT          >>>  GPIOx    (A-B-C-D)
* 2. pin_no        >>>  according to MACROs (GPIO_PINx_MACROs) or (0~15)
* 3. edge          >>>  according to MACROs (Edges MACROs) or (0,1,2)
* 4. ptrTofun      >>>  according to your function in application layer
* 						this pointer points to function that performs when
* 					    a specific (SW/HW) interrupt is happening.
* it returns nothing !
* NOTETHAT : GPIOA,GPIOB have 16 pins,but
* 			 GPIOC,GPIOD have 3,2 pins respectively
*/
void External_Interrupt_Init(volatile GPIO_t *PORT,uint8_t pin_no,uint8_t edge,void(*ptrTofun)(void))
{
	//port init
	GPIO_Init_Input_Pin(PORT,pin_no,INPUT_FLOATING,0);


	//select source of interrupt
	if(pin_no >=0 && pin_no<=3)
	{
		AFIO->EXTICR1 &= ~(0b0000 << ( pin_no * 4) );
			 if(PORT==GPIOA){AFIO->EXTICR1 &= ~(0b0000 << ( pin_no * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
		else if(PORT==GPIOB){AFIO->EXTICR1 |=(0b0001 << ( pin_no * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
		//else if(PORT==GPIOC){AFIO->EXTICR1 |=(0b0010 << ( pin_no * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
		else if(PORT==GPIOD && pin_no<=1){AFIO->EXTICR1 |=(0b0011 << ( pin_no * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}

	}
	else if(pin_no >=4 && pin_no<=7)
	{
		AFIO->EXTICR2 &= ~(0b0000 << ( (pin_no-4) * 4) );
			 if(PORT==GPIOA){AFIO->EXTICR2 &= ~(0b0000 << ( (pin_no-4) * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
		else if(PORT==GPIOB){AFIO->EXTICR2 |=(0b0001 << ( (pin_no-4) * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
		//else if(PORT==GPIOC){AFIO->EXTICR2 |=(0b0010 << ( (pin_no-4) * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
		//else if(PORT==GPIOD){AFIO->EXTICR2 |=(0b0011 << ( (pin_no-4) * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
	}
	else if(pin_no >=8 && pin_no<=11)
	{
		AFIO->EXTICR3 &= ~(0b0000 << ( (pin_no-8) * 4) );
			 if(PORT==GPIOA){AFIO->EXTICR3 &= ~(0b0000 << ( (pin_no-8) * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
		else if(PORT==GPIOB){AFIO->EXTICR3 |=(0b0001 << ( (pin_no-8) * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
		//else if(PORT==GPIOC){AFIO->EXTICR3 |=(0b0010 << ( (pin_no-8) * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
		//else if(PORT==GPIOD){AFIO->EXTICR3 |=(0b0011 << ( (pin_no-8) * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
	}
	else if(pin_no >=12 && pin_no<=15)
	{
		AFIO->EXTICR4 &= ~(0b0000 << ( (pin_no-12) * 4) );
			 if(PORT==GPIOA){AFIO->EXTICR4 &= ~(0b0000 << ( (pin_no-12) * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
		else if(PORT==GPIOB){AFIO->EXTICR4 |=(0b0001 << ( (pin_no-12) * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
		else if(PORT==GPIOC && pin_no !=12){AFIO->EXTICR4 |=(0b0010 << ( (pin_no-12) * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
		//else if(PORT==GPIOD){AFIO->EXTICR4 |=(0b0011 << ( (pin_no-12) * 4) );Interrupt_Setting(pin_no, edge, ptrTofun);}
	}
	else{}
}

/**================================================================
* External_Interrupt_Reset
* this function resets, disables all external interrupt.
* INPUTS : it takes nothing .
*		   it returns nothing !
*/
void External_Interrupt_Reset(void)
{
	EXTI->EMR   = 0x00000000;
	EXTI->EMR   = 0x00000000;
	EXTI->FTSR  = 0x00000000;
	EXTI->RTSR  = 0x00000000;
	EXTI->SWIER = 0x00000000;
	EXTI->PR    = 0xffffffff;

	//disable all IRQs from NVIC
	Disable_IRQx(0);
	Disable_IRQx(1);
	Disable_IRQx(2);
	Disable_IRQx(3);
	Disable_IRQx(4);
	Disable_IRQx(5);
	Disable_IRQx(10);
}

/**================================================================
* Software_Interrupt_Trigger
* this function triggers a specific line of interrupt
* INPUTS : it takes 1 argument :
* 1. pin_no        >>>  according to MACROs (GPIO_PINx_MACROs)
* it returns nothing !
*/
void Software_Interrupt_Trigger(uint8_t pin_no,void(*ptrTofun)(void))
{
	if(pin_no>=0 && pin_no<=15)
	{
	ptrToIRQx[pin_no] = ptrTofun;
	Interrupt_Mask_Enable(pin_no);
	Enable_IRQx(pin_no);
	EXTI->SWIER =(1U<<pin_no);
	}
	else {}
}





void EXTI0_IRQHandler(void)
{
	if(EXTI->PR & (1U<<0))
			{
		EXTI->PR |= (1U<<0);
		External_Interrupt_Line = 0;
		ptrToIRQx[0]();
		/***ISR0 HERE***/
			}
}

void EXTI1_IRQHandler(void)
{
	if(EXTI->PR & (1U<<1))
			{
		EXTI->PR |= (1U<<1);
		External_Interrupt_Line = 1;
		ptrToIRQx[1]();
		/***ISR1 HERE***/
			}
}


void EXTI2_IRQHandler(void)
{
	if(EXTI->PR & (1U<<2))
			{
		EXTI->PR |= (1U<<2);
		External_Interrupt_Line = 2;
		ptrToIRQx[2]();
		/***ISR2 HERE***/
			}
}

void EXTI3_IRQHandler(void)
{
	if(EXTI->PR & (1U<<3))
			{
		EXTI->PR |= (1U<<3);
		External_Interrupt_Line = 3;
		ptrToIRQx[3]();
		/***ISR3 HERE***/
			}
}
void EXTI4_IRQHandler(void)
{
		if(EXTI->PR & (1U<<4))
		{
		External_Interrupt_Line = 4;
		EXTI->PR |= (1U<<4);
		ptrToIRQx[4]();
		/***ISR4 HERE***/
		}

}
void EXTI9_5_IRQHandler(void)
{
	     if (EXTI->PR & (1U<<5)) {EXTI->PR |= (1U<<5);External_Interrupt_Line = 5;ptrToIRQx[5]();/**ISR5 CODE HERE***/}
	else if (EXTI->PR & (1U<<6)) {EXTI->PR |= (1U<<6);External_Interrupt_Line = 6;ptrToIRQx[6]();/**ISR6 CODE HERE***/}
	else if (EXTI->PR & (1U<<7)) {EXTI->PR |= (1U<<7);External_Interrupt_Line = 7;ptrToIRQx[7]();/**ISR7 CODE HERE***/}
	else if (EXTI->PR & (1U<<8)) {EXTI->PR |= (1U<<8);External_Interrupt_Line = 8;ptrToIRQx[8]();/**ISR8 CODE HERE***/}
	else if (EXTI->PR & (1U<<9)) {EXTI->PR |= (1U<<9);External_Interrupt_Line = 9;ptrToIRQx[9]();/**ISR9 CODE HERE***/}

}
void EXTI15_10_IRQHandler(void)
{
	      if (EXTI->PR & (1U<<10)){EXTI->PR |= (1U<<10);External_Interrupt_Line = 10;ptrToIRQx[10]();/**ISR10 CODE HERE***/}
	 else if (EXTI->PR & (1U<<11)){EXTI->PR |= (1U<<11);External_Interrupt_Line = 11;ptrToIRQx[11]();/**ISR11 CODE HERE***/}
	 else if (EXTI->PR & (1U<<12)){EXTI->PR |= (1U<<12);External_Interrupt_Line = 12;ptrToIRQx[12]();/**ISR12 CODE HERE***/}
	 else if (EXTI->PR & (1U<<13)){EXTI->PR |= (1U<<13);External_Interrupt_Line = 13;ptrToIRQx[13]();/**ISR13 CODE HERE***/}
     else if (EXTI->PR & (1U<<14)){EXTI->PR |= (1U<<14);External_Interrupt_Line = 14;ptrToIRQx[14]();/**ISR14 CODE HERE***/}
     else if (EXTI->PR & (1U<<15)){EXTI->PR |= (1U<<15);External_Interrupt_Line = 15;ptrToIRQx[15]();/**ISR15 CODE HERE***/}

}

