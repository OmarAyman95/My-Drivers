/* 
 * File:   SPImega32.h
 * Author: OMAR
 *
 * Created on December 31, 2022, 6:28 PM
 */

#ifndef SPIMEGA32_H
#define  SPIMEGA32_H

#include <avr/interrupt.h>
#include"ATMGA32MCU.h"
#include"GPIO_MEGA32.h"
#include "delayT0.h"


typedef struct
{
   uint8_t DeviceMode;            //@ref DeviceMode
   uint8_t LsbOrMsb ;             //@ref LsbOrMsb
   uint8_t SCKfrequency ;         //@ref SCKfrequency
   uint8_t Interrupt_Enable ;     //@ref Interrupt_Enable
   uint8_t IdleState;             //@ref IdleState
   uint8_t ClkPhase;              //@ref ClkPhase
   void(*ptrToISR)(uint8_t);
}SPI_config;


//Device Mode
#define SPI_MASTER_MODE             (1U<<4) //SPCR
#define SPI_SLAVE_MODE              (0U<<4) //SPCR
//LsbOrMsb
#define SPI_LSB                     (1U<<5) //SPCR
#define SPI_MSB                     (0U<<5) //SPCR
//SCKfrequency
#define SPI_Fosc_BR4                ((0U<<1) | (0U<<0) ) //SPCR
#define SPI_Fosc_BR16               ((0U<<1) | (1U<<0) ) //SPCR
#define SPI_Fosc_BR64               ((1U<<1) | (0U<<0) ) //SPCR
#define SPI_Fosc_BR128              ((1U<<1) | (1U<<0) ) //SPCR

#define SPI_Fosc_BR2                (1U<<0)//SPSR | (SPI_Fosc_BR4)@SPCR
#define SPI_Fosc_BR8                (1U<<0)//SPSR | (SPI_Fosc_BR16)@SPCR
#define SPI_Fosc_BR32               (1U<<0)//SPSR | (SPI_Fosc_BR64)@SPCR

//Interrupt_Enable
#define SPI_INTERRUPT_ENABLE        (1U<<7) //SPCR
#define SPI_INTERRUPT_DISABLE       (0U<<7) //SPCR
// IdleState 
#define SPI_1IDLE                   (1U<<3) //SPCR
#define SPI_0IDLE                   (0U<<3) //SPCR
//ClkPhase
#define SPI_SECOND_EDGE_SAMPLING    (1U<<2) //SPCR
#define SPI_FIRST_EDGE_SAMPLING     (0U<<2) //SPCR

//prototypes

/**================================================================
* SPI_init
* this function initializes SPI module
* INPUTS : it takes 1 argument  :
* 1. SPI_OBJ : make sure you add one object of this struct 
 * in your app layer and initialize it properly as your project needs 
* it returns nothing !
 */
void SPI_init(SPI_config *SPI_OBJ);
/**================================================================
* SPI_Dinit
* this function Resets SPI module, it just clears two registers 
 * SPCR,SPSR.
* it returns nothing !
 */
void SPI_Dinit(void);
/* SPI_Send
* this function send 1 byte through SPI bus to other peripherals on the bus 
* INPUTS : it takes 1 argument  :
* 1. DATA : Data you want to send (1 byte )
* it returns nothing !
 */
void SPI_Send(uint8_t DATA);

/* SPI_Recieve
* this function receives 1 byte from other peripherals attached on the bus 
* INPUTS : it takes nothing  : 
* it returns received byte of data !
 */
uint8_t SPI_Recieve(void);

#ifdef   __cplusplus
extern "C" {
#endif




#ifdef   __cplusplus
}
#endif

#endif   /* SPIMEGA32_H */

