/* 
 * File:   EXTI.h
 * Author: OMAR
 *
 * Created on November 28, 2022, 3:56 AM
 */

#ifndef EXTI_H
#define	EXTI_H

#include "ATMGA32MCU.h"
#include "GPIO_MEGA32.h"
#include <avr/interrupt.h>

//Enable and disable interrupt
#define GLOBAL_INTERRUPT_ENABLE()      SREG_REG->I =1
#define GLOBAL_INTERRUPT_DESABLE()     SREG_REG->I =0


//interrupt_number
#define INT_0                           (0U)
#define INT_1                           (2U)
#define INT_2                           (3U)


//interrupt_modes
#define RISING_EDGE_MODE                    (0b11U)
#define FALLING_EDGE_MODE                   (0b10U)
#define BOTH_EDGES_MODE                     (0b01U)
#define LOW_LEVEL_MODE                      (0b00U)




typedef struct
{
    uint8_t interrupt_no   : 2;
    uint8_t interrupt_mode : 2;
}Ext_interrupt_t;



/**================================================================
* ExtInterrupt_init
* this function initializes a specific pin to be external interrupt pin,
* selects the mode it is working on
* INPUTS : it takes 1 argument :
* 1. Ext_interrupt_t *    
* it returns nothing !
* object examples : : 
   Ext_interrupt_t ext_INT0={INT_0,RISING_EDGE_MODE};
   Ext_interrupt_t ext_INT1={INT_1,BOTH_EDGES_MODE};
   Ext_interrupt_t ext_INT2={INT_2,FALLING_EDGE_MODE};
 
**/
void ExtInterrupt_init(Ext_interrupt_t *ext_object);


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* EXTI_H */

