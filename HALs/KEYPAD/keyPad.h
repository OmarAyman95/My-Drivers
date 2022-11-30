/*
 * keyPad.h
 *
 *  Created on: Nov 22, 2022
 *      Author: OMAR
 *
 *
 *       #####################Instructions##################
 *		0. do NOT forget to include your MCAL GPIO Driver!
 *		1. this driver supports the 4X4 KeyPad connected to only 8 pins
 *      2. you should connect pins to any port as follow:
 *      ROWs(0,1,2,3)  >>> As input with pull down resistor pins(P0,P1,P2,P3)
 *      COLs(0,1,2,3)  >>> As output push pull pins(P4,P5,P6,P7),
 *      (do NOT connect COLs to open drain output mode MCU pins)
 *  	Note that : P is any port such as PORTA,PORTB,.....etc
 *      3. change (MCAL MACROs) as your MCAL GPIO Driver!
 *
 *
 */

#ifndef SRC_KEYPAD_H_
#define SRC_KEYPAD_H_

//MCAL GPIO Driver
#include "GPIOSTM32.h"

//MCAL MACROs
#define KEYPAD_PIN_HIGH(port,pin)   	(GPIO_Set_Pin(port,pin))
#define KEYPAD_PIN_LOW(port,pin)   		(GPIO_Reset_Pin(port,pin))
#define KEYPAD_PORT_HIGH(port,data) 	(GPIO_Set_pins(port,data))
#define KEYPAD_PORT_LOW(port,data) 		(GPIO_Reset_pins(port,data))
#define KEYPAD_PORT_CLR(port) 			(GPIO_Clear_pins(port))
#define KEYPAD_PORT_READ(port)       	(GPIO_Read_port(port))

//prototypes
char KeyPad_Scanning(volatile GPIO_t  *PORT);
#endif /* SRC_KEYPAD_H_ */
