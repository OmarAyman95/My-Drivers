#ifndef __bspSM32_H_
#define __bspSM32_H_


//Includes
//-----------------------------
//-----------------------------
#include "stdint.h"
#include "stdlib.h"


//Base addresses for Memories
#define FLASH_BASE 								(0x08000000UL)
#define SYSTEM_MEMORY_BASE 						(0x1FFFF000UL)
#define OPTION_BYTES_BASE 						(0x1FFFF800UL)
#define SRAM_BASE 								(0x20000000UL)
#define PERIPHERALS_BASE						(0x40000000UL)
#define CORTEX_M3_INTERNAL_PERIPHERALS_BASE 	(0xE0000000UL)

//-----------------------------
//-----------------------------
//Base addresses for AHB BUS Peripherals
#define RCC_BASE    							(0x40021000UL)
//-----------------------------
//-----------------------------
//Base addresses for APB2 BUS Peripherals
#define AFIO_BASE   							(0x40010000UL)
#define EXTI_BASE   							(0x40010400UL)
#define GPIOA_BASE 								(0x40010800UL)
#define GPIOB_BASE								(0x40010C00UL)
#define GPIOC_BASE								(0x40011000UL)
#define GPIOD_BASE 								(0x40011400UL)
#define GPIOE_BASE								(0x40011800UL)
//-----------------------------
//-----------------------------
//Base addresses for APB2 BUS Peripherals
//-----------------------------
//-----------------------------
//Peripheral register:

//GPIOs
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_t;


//RCC
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_t;

//EXTIs
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR ;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_t;

//AFIO
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t R_E_S_E_R_V_E_D;
	volatile uint32_t MAPR2;
}AFIO_t;

//-----------------------------
//-----------------------------
//Peripheral Instants:
#define GPIOA    					((volatile GPIO_t  *)(GPIOA_BASE))
#define GPIOB    					((volatile GPIO_t  *)(GPIOB_BASE))
#define GPIOC    					((volatile GPIO_t  *)(GPIOC_BASE))
#define GPIOD    					((volatile GPIO_t  *)(GPIOD_BASE))
#define GPIOE    					((volatile GPIO_t  *)(GPIOE_BASE))

#define RCC    						((volatile RCC_t  *)(RCC_BASE))

#define EXTI    					((volatile EXTI_t  *)(EXTI_BASE))

#define AFIO    					((volatile AFIO_t  *)(AFIO_BASE))

//-----------------------------
//-----------------------------
//clock enable Macros:
#define RCC_GPIOA_CLOCK_EN (RCC->APB2ENR |=IOPAEN)
#define RCC_GPIOB_CLOCK_EN (RCC->APB2ENR |=IOPBEN)
#define RCC_GPIOC_CLOCK_EN (RCC->APB2ENR |=IOPCEN)
#define RCC_GPIOD_CLOCK_EN (RCC->APB2ENR |=IOPDEN)
#define RCC_GPIOE_CLOCK_EN (RCC->APB2ENR |=IOPEEN)
#define RCC_AFIO_CLOCK_EN  (RCC->APB2ENR |=AFIOEN)
//-----------------------------
//-----------------------------


//Generic Macros:


#define BIT(x) 			(1U<<x)
#define AFIOEN 			(1U<<0)
#define IOPAEN 			(1U<<2)
#define IOPBEN 			(1U<<3)
#define IOPCEN 			(1U<<4)
#define IOPDEN 			(1U<<5)
#define IOPEEN 			(1U<<6)

#define AFIORST			(1U<<0)
#define IOPARST         (1U<<2)
#define IOPBRST         (1U<<3)
#define IOPCRST         (1U<<4)
#define IOPDRST         (1U<<5)




#endif
