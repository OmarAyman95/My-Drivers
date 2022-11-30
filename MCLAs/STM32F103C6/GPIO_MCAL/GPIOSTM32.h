/*
 * GPIOSTM32.h
 *
 *  Created on: Nov 21, 2022
 *      Author: OMAR
 */

#ifndef SRC_GPIOSTM32_H_
#define SRC_GPIOSTM32_H_

#include "STM32F103.h"
////////////////////////////////port initializations MACROs/////////////////////////////////////

//PIN_INPUT_MODES_MACROS
#define INPUT_ANALOG         		 (0U)
#define INPUT_FLOATING       		 (1U<<2)
#define INPUT_PULL_UP_DOWN     	     (1U<<3)
#define UP 								(1U)
#define DOWN 							(0U)

//PIN_OUTPUT_MODES_MACROS
#define OUTPUT_PUSH_PULL_10MHZ         	0x1U
#define OUTPUT_PUSH_PULL_2MHZ           0x2U
#define OUTPUT_PUSH_PULL_50MHZ      	0x3U
#define OUTPUT_OPEN_DRAIN_10MHZ      	0x5U
#define OUTPUT_OPEN_DRAIN_2MHZ       	0x6U
#define OUTPUT_OPEN_DRAIN_50MHZ      	0x7U
#define OUTPUT_ALT_PUSH_PULL_10MHZ      0x9U
#define OUTPUT_ALT_PUSH_PULL_2MHZ       0xAU
#define OUTPUT_ALT_PUSH_PULL_50MHZ      0xBU
#define OUTPUT_ALT_OPEN_DRAIN_10MHZ     0xDU
#define OUTPUT_ALT_OPEN_DRAIN_2MHZ      0xEU
#define OUTPUT_ALT_OPEN_DRAIN_50MHZ     0xFU

//PORT_INPUT_MODES_MACROS
#define INPUT_FLOATING_ALL           (0x44444444UL)
#define INPUT_PULL_UP_DOWN_ALL       (0x88888888UL)
//PORT_OUTPUT_MODES_MACROS
#define OUTPUT_PUSH_PULL_10MHZ_ALL    (0x11111111UL)
#define OUTPUT_PUSH_PULL_2MHZ_ALL     (0x22222222UL)
#define OUTPUT_PUSH_PULL_50MHZ_ALL    (0x33333333UL)

//MACROs GPIO_PINx(0~15)

#define GPIO_PIN0                     (0U)
#define GPIO_PIN1                     (1U)
#define GPIO_PIN2                     (2U)
#define GPIO_PIN3                     (3U)
#define GPIO_PIN4                     (4U)
#define GPIO_PIN5                     (5U)
#define GPIO_PIN6                     (6U)
#define GPIO_PIN7                     (7U)
#define GPIO_PIN8                     (8U)
#define GPIO_PIN9                     (9U)
#define GPIO_PIN10                    (10U)
#define GPIO_PIN11                    (11U)
#define GPIO_PIN12                    (12U)
#define GPIO_PIN13                    (13U)
#define GPIO_PIN14                    (14U)
#define GPIO_PIN15                    (15U)

#define GPIO_PIN_ALL                  (0xffff)




void GPIO_Init_Input_Pin(volatile GPIO_t  *PORT,unsigned pin,unsigned input_mode,unsigned up_down);
void GPIO_Init_Output_Pin(volatile GPIO_t  *PORT,unsigned pin,unsigned output_mode);
void GPIO_Set_Pin_Atomic(volatile GPIO_t  *PORT,unsigned pin);
void GPIO_Reset_Pin_Atomic(volatile GPIO_t  *PORT,unsigned pin);
void GPIO_Set_Pin(volatile GPIO_t  *PORT,unsigned pin);
void GPIO_Reset_Pin(volatile GPIO_t  *PORT,unsigned pin);
void GPIO_Toggle_Pin(volatile GPIO_t  *PORT,unsigned pin);
unsigned GPIO_Read_Pin(volatile GPIO_t  *PORT,unsigned pin);
unsigned GPIO_Lock_Pin(volatile GPIO_t  *PORT,unsigned pin);

void 		GPIO_Set_pins(volatile GPIO_t  *PORT,unsigned int GPIO_data);
void 		GPIO_Reset_pins(volatile GPIO_t  *PORT,unsigned int GPIO_data);
void 		GPIO_Clear_pins(volatile GPIO_t  *PORT);
void 		GPIO_Init_All_Input(volatile GPIO_t  *PORT,unsigned input_mode,unsigned up_down);
void 		GPIO_Init_All_Output(volatile GPIO_t  *PORT,unsigned output_mode);
void 		GPIO_Write_port(volatile GPIO_t  *PORT,unsigned int GPIO_data);
unsigned 	GPIO_Read_port(volatile GPIO_t  *PORT);
void        GPIO_DeInit(volatile GPIO_t  *PORT);





#endif /* SRC_GPIOSTM32_H_ */
