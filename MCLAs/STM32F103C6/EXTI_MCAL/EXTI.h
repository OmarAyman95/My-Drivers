/*
 * EXTI.h
 *
 *  Created on: Nov 25, 2022
 *      Author: OMAR
 */

#ifndef SRC_EXTI_H_
#define SRC_EXTI_H_

#include "STM32F103.h"
#include "GPIOSTM32.h"


extern int32_t External_Interrupt_Line;


//Edges Macros
#define FALLING_EDGE   (0U)
#define RISING_EDGE    (1U)
#define BOTH_EDGES     (2U)

//Disable_IRQx & Enable_IRQx
#define LINE_0          (0U)
#define LINE_1          (1U)
#define LINE_2          (2U)
#define LINE_3          (3U)
#define LINE_4          (4U)
#define LINE_5_9        (5U)
#define LINE_10_15      (10U)



//prototypes
void External_Interrupt_Init(volatile GPIO_t *PORT,uint8_t pin_no,uint8_t edge,void(*ptrTofun)(void));
void External_Interrupt_Reset(void);
void Software_Interrupt_Trigger(uint8_t pin_no,void(*ptrTofun)(void));
void Disable_IRQx(uint8_t external_interrupt_line);
void Enable_IRQx(uint8_t external_interrupt_line);


#endif /* SRC_EXTI_H_ */
