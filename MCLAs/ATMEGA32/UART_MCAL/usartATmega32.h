/* 
 * File:   usartATmega.h
 * Author: OMAR
 *
 * Created on December 9, 2022, 8:02 PM
 */

#ifndef USARTATMEGA_H
#define	USARTATMEGA_H



#include"ATMGA32MCU.h"
#include"GPIO_MEGA32.h"
#include <avr/interrupt.h>
#include"delayT0.h"
#define F_CPU        8000000UL

typedef struct
{
    uint8_t                 USART_mode;//@ref MODES OF OPERATION
    uint32_t                USART_baudRate; //@ref BAUD_RATE_STANDARDS              
    uint8_t                 USART_payloadLenght;//@ref PAYLOADS_OPTIONS
    uint8_t                 USART_parity;//@ref PARITY_OPTIONS
    uint8_t                 USART_stopbits;//@ref STOP_BITS_OPTIONS
    uint8_t                 USART_interrupts;//@ref EN/DIS USART_ISR
    void(*USARTptrTofunction)(void);
            
}USART_config_t;

// MODES OF OPERATION
#define USART_RX_ONLY               (1U<<4)
#define USART_TX_ONLY               (1U<<3)
#define USART_TX_RX                 (1U<<3 | 1U<<4)

// BAUD_RATE_STANDARDS  
#define USART_110_BAUDRATE           110U
#define USART_300_BAUDRATE           300U
#define USART_1200_BAUDRATE          1200U
#define USART_2400_BAUDRATE          2400U
#define USART_4800_BAUDRATE          4800U
#define USART_9600_BAUDRATE          9600U
#define USART_19200_BAUDRATE         19200U
#define USART_38400_BAUDRATE         38400U
#define USART_57600_BAUDRATE         57600U
//PAYLOADS_OPTIONS
#define USART_5BITS_DATA_FORMAT     (~(uint8_t)(1U<<1 | 1U<<2)) // &= 
#define USART_6BITS_DATA_FORMAT     (1U<<1)
#define USART_7BITS_DATA_FORMAT     (1U<<2)
#define USART_8BITS_DATA_FORMAT     (1U<<1 | 1U<<2)//|=


//PARITY_OPTIONS
#define USART_NO_PARITY             (~(uint8_t)(1<<4 | 1U<<5))//&= 
#define USART_EVEN_PARITY           (1U<<5)
#define USART_ODD_PARITY            (1U<<4 | 1U<<5)//|=

//STOP_BITS_OPTIONS
#define USART_1BIT_STOP             (~(uint8_t)(1U<<3))
#define USART_2BIT_STOP             (1U<<3)

//EN/DIS USART_ISR
#define USART_ISR_EN                 (1U)
#define USART_ISR_DIS                (0U)


#define USART_BUFFER_CLEAR_INTERRUPT_ENABLE()               USART_REGs->UCSRB_R.UDRIEbit = 1 ;
#define USART_BUFFER_CLEAR_INTERRUPT_DISABLE()              USART_REGs->UCSRB_R.UDRIEbit = 0 ;
#define USART_TRANSMITTER_COMPLETE_INTERRUPT_ENABLE()       USART_REGs->UCSRB_R.TXCIEbit= 1; 
#define USART_TRANSMITTER_COMPLETE_INTERRUPT_DISABLE()      USART_REGs->UCSRB_R.TXCIEbit= 0;
#define USART_RECEIVER_INTERRUPT_ENABLE()                   USART_REGs->UCSRB_R.RXCIEbit=1;
#define USART_RECEIVER_INTERRUPT_DISABLE()                  USART_REGs->UCSRB_R.RXCIEbit=0;
#define GLOBAL_INTERRUPT_ENABLE()                           SREG_REG->I =1
#define GLOBAL_INTERRUPT_DESABLE()                          SREG_REG->I =0


/*******************************initialization******************************/

/**================================================================
* USART_init
* this function initializes USART module   
* INPUTS : it takes 1 argument :
* 1. USARTobj             >>>  it is a pointer to structure
 *                             (configuration stucture of USART)
 * you can do various things using this init function 
 * - select baud rate        @ref (BAUD_RATE_STANDARDS)
 * - mode of operation          @ref (MODES OF OPERATION)
 * - payload length    @ref (PAYLOADS_OPTIONS)
 * - no of stop bits @ref (STOP_BITS_OPTIONS)
 * - parity bit  @ref (PARITY_OPTIONS)
 * - interrupt   @ref(EN/DIS USART_ISR)
 * - USARTptrTofunction >> you can use this member to jump to function
 *                           at application level when an interrupt occurs 
* it returns nothing !  
*/
void USART_init(USART_config_t *USARTobj);
/*******************************POOLING**********************************/
/**================================================================
* USART_Transmit_Char
* this function sends one char at a time using pooling mechanism   
* INPUTS : it takes 1 argument :
* 1. data             >>>  the byte want to send 
* it returns nothing !  
*/
void USART_Transmit_Char( unsigned char data );
/**================================================================
* USART_Transmit_Text
* this function sends an array of char using pooling mechanism .
 * it keeps pool, until it finds the null '\0',
 *  then it will stop pooling and terminates.  
* INPUTS : it takes 1 argument :
* 1. data             >>>  the array want to send 
* it returns nothing !  
*/
void USART_Transmit_Text(char *data );
/**================================================================
* USART_Receive
* this function reads a char that was sent to UART module,using pooling mechanism . 
* INPUTS : it takes nothing!  
* it returns a char received by UART module.   
*/
char USART_Receive( void );


//using ISRs

/**================================================================
* USART_Send_Char
* this function sends one char at a time using ISR.   
* INPUTS : it takes 1 argument :
* 1. data             >>>  the byte want to send 
* it returns nothing !  
*/
void USART_Send_Char(char data);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* USARTATMEGA_H */

