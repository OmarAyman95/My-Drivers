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

#define _SPI1_BASE								(0x40013000UL)
//-----------------------------
//-----------------------------
//Base addresses for APB1 BUS Peripherals
//-----------------------------
//-----------------------------
#define _SPI2_BASE								(0x40013800UL)
#define _I2C1_BASE								(0x40005400UL)
#define _I2C2_BASE								(0x40005800UL)
//-----------------------------
//-----------------------------
//Base addresses for CORTEX_M3_INTERNAL_PERIPHERALS
#define NVIC_ISER_BASE								(0xE000E100U)
#define NVIC_ICER_BASE								(0xE000E180U)


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


//registers structures

//_______________SPI_CR1
typedef union
{
	uint16_t SPI_CR1_REG;
	struct
	{
	uint16_t CPHA:1;
	uint16_t CPOL:1;
	uint16_t MSTR:1;
	uint16_t BR:3;
	uint16_t SPE:1;
	uint16_t LSBFIRST:1;
	uint16_t SSI:1;
	uint16_t SSM:1;
	uint16_t RXONLY:1;
	uint16_t DFF:1;
	uint16_t CRCNEXT:1;
	uint16_t CRCEN:1;
	uint16_t BIDIOE:1;
	uint16_t BIDIMODE:1;
	};
}SPI_CR1_type;
//_______________SPI_CR2
typedef union
{
	uint16_t SPI_CR2_REG;
	struct
	{
	uint16_t RXDMAEN:1;
	uint16_t TXDMAEN:1;
	uint16_t SSOE:1;
	uint16_t UNused:2;
	uint16_t ERRIE:1;
	uint16_t RXNEIE:1;
	uint16_t TXEIE:1;
	};
}SPI_CR2_type;
//_______________SPI_SR
typedef union
{
	uint16_t SPI_SR_REG;
	struct
	{
	uint16_t RXNE:1;
	uint16_t TXE:1;
	uint16_t CHSIDE:1;
	uint16_t UDR:2;
	uint16_t CRCERR:1;
	uint16_t MODF:1;
	uint16_t OVR:1;
	uint16_t BSY:1;
	};
}SPI_SR_type;
//_______________SPI_DR
//_______________SPI_CRCPR
//_______________SPI_RXCRCR
//_______________SPI_TXCRCR
//_______________SPI_I2SCFGR
//_______________SPI_I2SPR
//SPI
typedef struct
{
	volatile uint32_t SPI_CR1;
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint32_t SPI_DR;
	volatile uint32_t SPI_CRCPR;
	volatile uint32_t SPI_RXCRCR;
	volatile uint32_t SPI_TXCRCR;
	volatile uint32_t SPI_I2SCFGR;
	volatile uint32_t SPI_I2SPR;
}SPI_t;


typedef struct
{
	volatile uint32_t I2C_CR1;
	volatile uint32_t I2C_CR2;
	volatile uint32_t I2C_OAR1;
	volatile uint32_t I2C_OAR2;
	volatile uint32_t I2C_DR;
	volatile uint32_t I2C_SR1;
	volatile uint32_t I2C_SR2;
	volatile uint32_t I2C_CCR;
	volatile uint32_t I2C_TRISE;
}I2C_t;

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


#define SPI_1                        ((volatile SPI_t   *)(_SPI1_BASE))
#define SPI_2                        ((volatile SPI_t   *)(_SPI2_BASE))


#define I2C_1                        ((volatile I2C_t   *)(_I2C1_BASE))
#define I2C_2                        ((volatile I2C_t   *)(_I2C2_BASE))

#define NVIC_ISER0					(*((volatile uint32_t  *)(NVIC_ISER_BASE+0x00)))
#define NVIC_ISER1					(*((volatile uint32_t  *)(NVIC_ISER_BASE+0x04)))
#define NVIC_ISER2 					(*((volatile uint32_t  *)(NVIC_ISER_BASE+0x08)))
#define NVIC_ISER3 					(*((volatile uint32_t  *)(NVIC_ISER_BASE+0x0C)))
#define NVIC_ISER4 					(*((volatile uint32_t  *)(NVIC_ISER_BASE+0x10)))
#define NVIC_ISER5 					(*((volatile uint32_t  *)(NVIC_ISER_BASE+0x14)))
#define NVIC_ISER6 					(*((volatile uint32_t  *)(NVIC_ISER_BASE+0x18)))
#define NVIC_ISER7 					(*((volatile uint32_t  *)(NVIC_ISER_BASE+0x1C)))

#define NVIC_ICER0 					(*((volatile uint32_t  *)(NVIC_ICER_BASE+0x00)))
#define NVIC_ICER1 					(*((volatile uint32_t  *)(NVIC_ICER_BASE+0x04)))
#define NVIC_ICER2 					(*((volatile uint32_t  *)(NVIC_ICER_BASE+0x08)))
#define NVIC_ICER3 					(*((volatile uint32_t  *)(NVIC_ICER_BASE+0x0C)))
#define NVIC_ICER4 					(*((volatile uint32_t  *)(NVIC_ICER_BASE+0x10)))
#define NVIC_ICER5 					(*((volatile uint32_t  *)(NVIC_ICER_BASE+0x14)))
#define NVIC_ICER6 					(*((volatile uint32_t  *)(NVIC_ICER_BASE+0x18)))
#define NVIC_ICER7 					(*((volatile uint32_t  *)(NVIC_ICER_BASE+0x1C)))


//-----------------------------
//-----------------------------
//clock enable Macros:
#define RCC_GPIOA_CLOCK_EN()		 	(RCC->APB2ENR |=IOPAEN)
#define RCC_GPIOB_CLOCK_EN()		  	(RCC->APB2ENR |=IOPBEN)
#define RCC_GPIOC_CLOCK_EN()		  	(RCC->APB2ENR |=IOPCEN)
#define RCC_GPIOD_CLOCK_EN()		  	(RCC->APB2ENR |=IOPDEN)
#define RCC_GPIOE_CLOCK_EN()		  	(RCC->APB2ENR |=IOPEEN)
#define RCC_AFIO_CLOCK_EN()		 	  	(RCC->APB2ENR |=AFIOEN)


#define RCC_SPI1_CLOCK_EN()  (RCC->APB2ENR |=SPI1EN)
#define RCC_SPI2_CLOCK_EN()  (RCC->APB1ENR |=SPI2EN)

#define RCC_I2C1_CLOCK_EN()  (RCC->APB1ENR |=I2C1EN)
#define RCC_I2C2_CLOCK_EN()  (RCC->APB1ENR |=I2C2EN)

//Resets Macros:

#define RCC_SPI1_RESET()  (RCC->APB2RSTR |=SPI1RST)
#define RCC_SPI2_RESET()  (RCC->APB1RSTR |=SPI2RST)

#define RCC_I2C1_RESET()  (RCC->APB1RSTR |=I2C1RST)
#define RCC_I2C2_RESET()  (RCC->APB1RSTR |=I2C2RST)
//-----------------------------
//-----------------------------


//Generic Macros:


#define BIT(x) 			(1U<<x)


//clock Enable Macros
#define AFIOEN 			(1U<<0)
#define IOPAEN 			(1U<<2)
#define IOPBEN 			(1U<<3)
#define IOPCEN 			(1U<<4)
#define IOPDEN 			(1U<<5)
#define IOPEEN 			(1U<<6)
#define PWREN           (1U<<28)

#define SPI1EN 			(1U<<12)
#define SPI2EN 			(1U<<14)

#define I2C1EN          (1U<<21)
#define I2C2EN          (1U<<22)

//reset Macros
#define AFIORST			(1U<<0)
#define IOPARST         (1U<<2)
#define IOPBRST         (1U<<3)
#define IOPCRST         (1U<<4)
#define IOPDRST         (1U<<5)
#define IOPERST         (1U<<6)

#define SPI1RST 		(1U<<12)
#define SPI2RST 		(1U<<14)

#define I2C1RST         (1U<<21)
#define I2C2RST         (1U<<22)

//IRQs Macros
//ISER0
#define WWDG_IRQ        	(1U<<0)
#define PVD_IRQ        		(1U<<1)
#define TAMPER_IRQ        	(1U<<2)
#define RTC_IRQ        		(1U<<3)
#define FLASH_IRQ        	(1U<<4)
#define RCC_IRQ        		(1U<<5)
#define EXTI0_IRQ        	(1U<<6)
#define EXTI1_IRQ        	(1U<<7)
#define EXTI2_IRQ        	(1U<<8)
#define EXTI3_IRQ        	(1U<<9)
#define EXTI4_IRQ        	(1U<<10)
#define I2C1_EV_IRQ        	(1U<<31)
//ISER1
#define I2C1_ER_IRQ        	(1U<<0)
#define I2C2_EV_IRQ        	(1U<<1)
#define I2C2_ER_IRQ        	(1U<<2)
#define SPI1_IRQ        	(1U<<3)
#define SPI2_IRQ        	(1U<<4)
#define USART1_IRQ        	(1U<<5)
#define USART2_IRQ        	(1U<<6)
#define USART3_IRQ        	(1U<<7)
#define EXTI15_10_IRQ       (1U<<8)


//Enable / Disable interrupts
#define SPI1_INTERRUPT_EN()  					(NVIC_ISER1|=(SPI1_IRQ))
#define SPI2_INTERRUPT_EN()  					(NVIC_ISER1|=(SPI2_IRQ))
#define SPI1_INTERRUPT_DIS()  					(NVIC_ICER1|=(SPI1_IRQ))
#define SPI2_INTERRUPT_DIS()  					(NVIC_ICER1|=(SPI2_IRQ))


#define I2C1_EV_INTERRUPT_EN()  					(NVIC_ISER0|=(I2C1_EV_IRQ))
#define I2C1_ER_INTERRUPT_EN()  					(NVIC_ISER1|=(I2C1_ER_IRQ))
#define I2C2_EV_INTERRUPT_EN()  					(NVIC_ISER1|=(I2C2_EV_IRQ))
#define I2C2_ER_INTERRUPT_EN()  					(NVIC_ISER1|=(I2C2_ER_IRQ))

#define I2C1_EV_INTERRUPT_DIS()  					(NVIC_ICER0|=(I2C1_EV_IRQ))
#define I2C1_ER_INTERRUPT_DIS()  					(NVIC_ICER1|=(I2C1_ER_IRQ))
#define I2C2_EV_INTERRUPT_DIS()  					(NVIC_ICER1|=(I2C2_EV_IRQ))
#define I2C2_ER_INTERRUPT_DIS()  					(NVIC_ICER1|=(I2C2_ER_IRQ))












/********************************************************/
/********************************************************/
/********************************************************/
/*******************  Bit definition  ********************/
/********************************************************/
/********************************************************/



/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */
/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */
/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)
/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */
#endif
