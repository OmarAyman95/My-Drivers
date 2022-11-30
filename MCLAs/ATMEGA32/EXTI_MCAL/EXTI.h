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

#define GLOBAL_INTERRUPT_ENABLE()      SREG_REG->I =1
#define GLOBAL_INTERRUPT_DESABLE()     SREG_REG->I =0

#define INT_0                           (0U)
#define INT_1                           (2U)
#define INT_2                           (3U)

#define RISING_EDGE_MODE                    (0b11U)
#define FALLING_EDGE_MODE                   (0b10U)
#define BOTH_EDGES_MODE                     (0b01U)
#define LOW_LEVEL_MODE                      (0b00U)


typedef struct
{
    uint8_t interrupt_no   : 2;
    uint8_t interrupt_mode : 2;
}Ext_interrupt_t;

void ExtInterrupt_init(Ext_interrupt_t *ext_object);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* EXTI_H */

