/*
 * keyPad.c
 *
 *  Created on: Nov 22, 2022
 *      Author: OMAR
 */

#include "keyPad.h"

static unsigned pressed;

static void KeyPad_Send_Wave(unsigned n,volatile GPIO_t  *PORT)
{
	switch(n)
	{
		case 4:
			KEYPAD_PIN_HIGH(PORT,(4));
			KEYPAD_PIN_LOW(PORT,(7));
			break;
		case 5:
			KEYPAD_PIN_HIGH(PORT,(5));
			KEYPAD_PIN_LOW(PORT,(4));
			break;
		case 6:
			KEYPAD_PIN_HIGH(PORT,(6));
			KEYPAD_PIN_LOW(PORT,(5));
			break;
		case 7:
			KEYPAD_PIN_HIGH(PORT,(7));
			KEYPAD_PIN_LOW(PORT,(6));
			break;
		default:
			break;
	}
}

static void KeyPad_Waiting(volatile GPIO_t  *PORT,unsigned data)
{
	while(KEYPAD_PORT_READ(PORT)==data);
}

/**================================================================
* KeyPad_Scanning
* this returns the pressed key (one of those 16 keys below) .
* INPUTS : it takes 1 arguments :
* 1. PORT        >>>  GPIOx    (A-B-C-D)
* NOTETHAT : the pressed key is specialized to a specific keyPad
* 			 which has 16 keys as follow:
*       _______________________
* 		|	  7   8  9  /      |
* 		|	  4   5  6  X      |
* 		|	  1   2  3  -      |
* 		|	 CLR  0  =  +	   |
* 		|______________________|
*/
char KeyPad_Scanning(volatile GPIO_t  *PORT)
{
	KEYPAD_PORT_LOW(PORT,0xf0);

	KeyPad_Send_Wave(4,PORT);
	pressed = KEYPAD_PORT_READ(PORT);

	if( KEYPAD_PORT_READ(PORT)==0x11){KeyPad_Waiting(PORT,0x11);return('7');}
	else if( KEYPAD_PORT_READ(PORT)==0x12){KeyPad_Waiting(PORT,0x12);return('4');}
	else if( KEYPAD_PORT_READ(PORT)==0x14){KeyPad_Waiting(PORT,0x14);return('1');}
	else if( KEYPAD_PORT_READ(PORT)==0x18){KeyPad_Waiting(PORT,0x18);return('c');}
	else{}


	KeyPad_Send_Wave(5,PORT);
	pressed = KEYPAD_PORT_READ(PORT);
	if( KEYPAD_PORT_READ(PORT)==0x21){KeyPad_Waiting(PORT,0x21);return('8');}
	else if( KEYPAD_PORT_READ(PORT)==0x22){KeyPad_Waiting(PORT,0x22);return('5');}
	else if( KEYPAD_PORT_READ(PORT)==0x24){KeyPad_Waiting(PORT,0x24);return('2');}
	else if( KEYPAD_PORT_READ(PORT)==0x28){KeyPad_Waiting(PORT,0x28);return('0');}
	else{}


	KeyPad_Send_Wave(6,PORT);
	pressed = KEYPAD_PORT_READ(PORT);
	if( KEYPAD_PORT_READ(PORT)==0x41){KeyPad_Waiting(PORT,0x41);return('9');}
	else if( KEYPAD_PORT_READ(PORT)==0x42){KeyPad_Waiting(PORT,0x42);return('6');}
	else if( KEYPAD_PORT_READ(PORT)==0x44){KeyPad_Waiting(PORT,0x44);return('3');}
	else if( KEYPAD_PORT_READ(PORT)==0x48){KeyPad_Waiting(PORT,0x48);return('=');}
	else{}

	KeyPad_Send_Wave(7,PORT);
	pressed = KEYPAD_PORT_READ(PORT);
	if( KEYPAD_PORT_READ(PORT)==0x81){KeyPad_Waiting(PORT,0x81);return('/');}
	else if( KEYPAD_PORT_READ(PORT)==0x82){KeyPad_Waiting(PORT,0x82);return('X');}
	else if( KEYPAD_PORT_READ(PORT)==0x84){KeyPad_Waiting(PORT,0x84);return('-');}
	else if( KEYPAD_PORT_READ(PORT)==0x88){KeyPad_Waiting(PORT,0x88);return('+');}
	else{}
	return (0);
}


