/* 
 * File:   delay.h
 * Author: OMAR AYMAN
 *
 * Created on December 1, 2022, 1:53 AM
 */

#ifndef DELAY_H
#define	DELAY_H

#include"ATMGA32MCU.h"
#define Fclk_CPU        16000000UL

//do NOT edit any of those MACROs
#define PS_NO()         TCCR0_REG->_TCCR0 &= ~(0b00000111U);//No PS
#define PS_8()          TCCR0_REG->_TCCR0 |=(0b00000010U);//PS = 8
#define PS_64()         TCCR0_REG->_TCCR0 |=(0b00000011U);//PS = 64
#define PS_256()        TCCR0_REG->_TCCR0 |=(0b00000100U);//PS = 256
#define PS_1024()       TCCR0_REG->_TCCR0 |=(0b00000101U);//PS = 1024


/**================================================================
* delay_ms
* this function gives your application some delay of time as you need 
 * 
* INPUTS : it takes 1 argument :
* 1. t      >>>>  time in milli seconds you can put any value from 1ms to 
 *                  (2^32) - 1 
 * NOTE THAT : this driver depends on your CPU frequency, so you should 
 *             edit the MACRO (Fclk_CPU) every time you want to edit the clock 
 *             frequency of the cpu.
* it returns nothing !
**/
void delay_ms(uint32_t t);


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

