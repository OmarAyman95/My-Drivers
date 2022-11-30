/* 
 * File:   GPIO.h
 * Author: OMAR
 *
 * Created on November 28, 2022, 4:01 AM
 */

#ifndef GPIO_H
#define	GPIO_H

#include "ATMGA32MCU.h"

//PINs_MODES_MACROs
#define INPUT_PULL_UP_MODE                  (0b010U)
#define INPUT_FLOATING_MODE                 (0b000U)
#define OUTPUT_MODE                         (0b101U)

//GPIO_PINx_MACROs
#define _PIN0                                (0U)
#define _PIN1                                (1U)
#define _PIN2                                (2U)
#define _PIN3                                (3U)
#define _PIN4                                (4U)
#define _PIN5                                (5U)
#define _PIN6                                (6U)
#define _PIN7                                (7U)
#define ALL_PINS                            (0xffU)                                                   





void PORT_init(volatile GPIO_t *GPIOx ,uint8_t port_mode,uint8_t pin_number);
void PORT_Toggle_pin(volatile GPIO_t *GPIOx ,uint8_t pin_number);
void PORT_Set_pin(volatile GPIO_t *GPIOx ,uint8_t pin_number);
void PORT_Reset_pin(volatile GPIO_t *GPIOx ,uint8_t pin_number);

uint8_t PORT_Read(volatile GPIO_t *GPIOx);
void PORT_Write(volatile GPIO_t *GPIOx ,uint8_t data);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_H */

