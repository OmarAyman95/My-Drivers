/* 
 * File:   Timer0.h
 * Author: OMAR AYMAN
 *
 * Created on January 5, 2023, 9:39 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

#include "ATMGA32MCU.h"
#include "GPIO_MEGA32.h"
#include "delayT0.h"
#include <avr/interrupt.h>

typedef struct
{
    uint8_t             Timer0_Mode;//@ ref Timer0_Modes
    uint8_t             Timer0_Clock_SRC;//@ ref Timer0_Clock_SRC
    uint8_t             Timer0_COM_Mode;//@ ref Timer0_COM_Mode  
    uint8_t             Timer0_Interrupt;//@ ref Timer0_Interrupt
    uint8_t             Timer0_Compare_Interrupt;//@ ref Timer0_Compare_Interrupt
    
}Timer0_config;

#endif	/* TIMER0_H */

#define WGM00_ON                            (1U<<6)                   
#define WGM00_OFF                           (0U<<6)  
#define WGM01_ON                            (1U<<3)  
#define WGM01_OFF                           (0U<<3)  

//Timer0_Modes
#define TMR0_NORMAL_MODE                        (WGM01_OFF | WGM00_OFF) //at TCCR0
#define TMR0_PHASE_CORRECT_PWM_MODE             (WGM01_OFF | WGM00_ON) //at TCCR0
#define TMR0_CTC_MODE                           (WGM01_ON  | WGM00_OFF) //at TCCR0
#define TMR0_FAST_PWM_MODE                      (WGM01_ON  | WGM00_ON) //at TCCR0

//Timer0_Clock_SRC
#define TMR0_NO_CLK_SRC                     ((0U<<2) | (0U<<1) | (0U<<0)) //at TCCR0
#define TMR0_INTERNAL_CLK_PS_1_SRC          ((0U<<2) | (0U<<1) | (1U<<0)) //at TCCR0
#define TMR0_INTERNAL_CLK_PS_8_SRC          ((0U<<2) | (1U<<1) | (0U<<0)) //at TCCR0
#define TMR0_INTERNAL_CLK_PS_64_SRC         ((0U<<2) | (1U<<1) | (1U<<0)) //at TCCR0
#define TMR0_INTERNAL_CLK_PS_256_SRC        ((1U<<2) | (0U<<1) | (0U<<0)) //at TCCR0
#define TMR0_INTERNAL_CLK_PS_1024_SRC       ((1U<<2) | (0U<<1) | (1U<<0)) //at TCCR0
#define TMR0_EXTERNAL_CLK_SRC_FALLING_EDGE  ((1U<<2) | (1U<<1) | (0U<<0)) //at TCCR0
#define TMR0_EXTERNAL_CLK_SRC_RISING_EDGE   ((1U<<2) | (1U<<1) | (1U<<0)) //at TCCR0

//Timer0_COM_Mode
#define TMR0_OCR_PIN_DISCONNECTED           ((0U<<5) | (0U<<4))//at TCCR0 
#define TMR0_OCR_PIN_TOGGLE                 ((0U<<5) | (1U<<4))//at TCCR0 (reserved in PWM modes)
#define TMR0_OCR_PIN_CLEAR                  ((1U<<5) | (0U<<4))//at TCCR0 
#define TMR0_OCR_PIN_SET                    ((1U<<5) | (1U<<4))//at TCCR0 


#define TMR0_OCR_PIN_SET_AT_BOTTOM          ((1U<<5) | (0U<<4))//at TCCR0 
#define TMR0_OCR_PIN_CLEAR_AT_BOTTOM        ((1U<<5) | (1U<<4))//at TCCR0 

#define TMR0_OCR_PIN_CLEAR                  ((1U<<5) | (0U<<4))//at TCCR0 
#define TMR0_OCR_PIN_SET                    ((1U<<5) | (1U<<4))//at TCCR0 


//Timer0_Interrupt
#define TMR0_INTERRUPT_ENABLE               (1U<<0)//at TIMSK
#define TMR0_INTERRUPT_DISABLE              (0U<<0)//at TIMSK

//Timer0_Compare_Interrupt
#define TMR0_COMPARE_INTERRUPT_ENABLE       (1U<<1)//at TIMSK
#define TMR0_COMPARE_INTERRUPT_DISABLE      (0U<<1)//at TIMSK

//Global interrupts vector
#define GLOBAL_INTERRUPT_ENABLE()      SREG_REG->I =1
#define GLOBAL_INTERRUPT_DESABLE()     SREG_REG->I =0

//FCPU_CLK 
#define FCPU_CLK                            (8000000U)
#define FCPU_CLK_IN_MHZ                    (FCPU_CLK/1000000)
//prototypes

/**================================================================
* TMR0_init
* this function initializes Timer0
* INPUTS : it takes 1 argument :
* 1. Timer0_config     
* it returns nothing !
**/
void TMR0_init(Timer0_config *TMR0_config);
/**================================================================
* TMR0_FAST_PWM_MODE_Init
* this function initializes Timer0 when user want to use FAST PWM mode
* INPUTS : it takes 2 arguments :
* 1.Foscn     >>> PWM frequency in HZ
 * 2. DutyCycle >> from 0~100
* it returns nothing !
**/
void TMR0_FAST_PWM_MODE_Init(uint32_t Foscn ,uint8_t DutyCycle);
/**================================================================
* TMR0_CTC_MODE_Init
* this function initializes Timer0 when user want to use CTC mode
* INPUTS : it takes 1 argument :
* 1.Foscn     >>> CTC frequency in HZ
* it returns nothing !
**/
void TMR0_CTC_MODE_Init(uint32_t Foscn);