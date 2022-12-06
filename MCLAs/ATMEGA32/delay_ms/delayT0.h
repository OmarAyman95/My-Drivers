/* 
 * File:   delay.h
 * Author: OMAR AYMAN
 *
 * Created on December 6, 2022, 2:02 AM
 */

#ifndef DELAY_H
#define DELAY_H

#include"ATMGA32MCU.h"

//edit this MACRO (FCLK_CPU) when you change the cpu frequency 
//this frequency should be written ______in (HZ)_____ not in (MHZ) or (KHZ)
#define FCLK_CPU        10000000UL 




//do NOT edit any of those MACROs
#define FCLK_MHZ FCLK_CPU/1000000UL
#define XDELAY (FCLK_MHZ*1980UL/16UL)

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

void delay_ms(int t);

#ifdef  __cplusplus
extern "C" {
#endif




#ifdef  __cplusplus
}
#endif

#endif  /* DELAY_H */

