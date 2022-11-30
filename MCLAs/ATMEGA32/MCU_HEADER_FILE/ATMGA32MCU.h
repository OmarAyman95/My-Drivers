/* 
 * File:   ATMGA32MCU.h
 * Author: OMAR
 *
 * Created on November 28, 2022, 3:57 AM
 */

#ifndef ATMGA32MCU_H
#define	ATMGA32MCU_H

//Includes
//-----------------------------
//-----------------------------
#include "stdint.h"
#include "stdlib.h"


//Base addresses for Memories
//-----------------------------
// SRAM 
#define REGISTER_FILE_BASE 						(0x0000U)
#define I_O_64_REGISTERS_BASE 					(0x0020U)
#define INTERNAL_SRAM_BASE 						(0x0060U)
// FLASH 
#define APPLICATION_SECTION_BASE 				(0x0000U)
#define BOOT_SECTION_BASE 					    (0x4000U)
//-----------------------------
//-----------------------------
//-----------------------------
//-----------------------------
//-----------------------------
//-----------------------------
//-----------------------------
//Base addresses for I/O Peripherals
#define SREG_BASE                   (0x5FU)
#define SPH_BASE                    (0x5EU)
#define SPL_BASE                    (0x5DU)
#define OCR0_BASE                   (0x5CU)
#define GICR_BASE                   (0x5BU)
#define GIFR_BASE                   (0x5AU)
#define TIMSK_BASE                  (0x59U)
#define TIFR_BASE                   (0x58U)
#define SPMCR_BASE                  (0x57U)
#define TWCR_BASE                   (0x56U)
#define MCUCR_BASE                  (0x55U)
#define MCUCSR_BASE                 (0x54U)
#define TCCR0_BASE                  (0x53U)
#define TCNT0_BASE                  (0x52U)
#define OSCCAL_OCDR_BASE            (0x51U)
#define SFIOR_BASE                  (0x50U)



#define TCCR1A_BASE                 (0x4FU)
#define TCCR1B_BASE                 (0x4EU)
#define TCNT1H_BASE                 (0x4DU)
#define TCNT1L_BASE                 (0x4CU)
#define OCR1AH_BASE                 (0x4BU)
#define OCR1AL_BASE                 (0x4AU)
#define OCR1BH_BASE                 (0x49U)
#define OCR1BL_BASE                 (0x48U)
#define ICR1H_BASE                  (0x47U)
#define ICR1L_BASE                  (0x46U)
#define TCCR2_BASE                  (0x45U)
#define TCNT2_BASE                  (0x44U)
#define OCR2_BASE                   (0x43U)
#define ASSR_BASE                   (0x42U)
#define WDTCR_BASE                  (0x41U)
#define UBRRH_UCSRC_BASE            (0x40U)


#define EEARH_BASE                  (0x3FU)
#define EEARL_BASE                  (0x3EU)
#define EEDR_BASE                   (0x3DU)
#define EECR_BASE                   (0x3CU)
#define PORTA_BASE                  (0x3BU)
#define DDRA_BASE                   (0x3AU)
#define PINA_BASE                   (0x39U)
#define PORTB_BASE                  (0x38U)
#define DDRB_BASE                   (0x37U)
#define PINB_BASE                   (0x36U)
#define PORTC_BASE                  (0x35U)
#define DDRC_BASE                   (0x34U)
#define PINC_BASE                   (0x33U)
#define PORTD_BASE                  (0x32U)
#define DDRD_BASE                   (0x31U)
#define PIND_BASE                   (0x30U)


#define SPDR_BASE                   (0x2FU)
#define SPSR_BASE                   (0x2EU)
#define SPCR_BASE                   (0x2DU)
#define UDR_BASE                    (0x2CU)
#define UCSRA_BASE                  (0x2BU)
#define UCSRB_BASE                  (0x2AU)
#define UBRRL_BASE                  (0x29U)
#define ACSR_BASE                   (0x28U)
#define ADMUX_BASE                  (0x27U)
#define ADCSRA_BASE                 (0x26U)
#define ADCH_BASE                   (0x25U)
#define ADCL_BASE                   (0x24U)
#define TWDR_BASE                   (0x23U)
#define TWAR_BASE                   (0x22U)
#define TWSR_BASE                   (0x21U)
#define TWBR_BASE                   (0x20U)
//Peripheral registers:





typedef union
{
    volatile uint8_t _DDRA;
struct 
{
	volatile uint8_t DDA0BIT:1 ;
	volatile uint8_t DDA1BIT:1 ;
	volatile uint8_t DDA2BIT:1 ;
	volatile uint8_t DDA3BIT:1 ;
	volatile uint8_t DDA4BIT:1 ;
	volatile uint8_t DDA5BIT:1 ;
	volatile uint8_t DDA6BIT:1 ;
    volatile uint8_t DDA7BIT:1 ;
};
}DDRA_t;



typedef union
{
    volatile uint8_t _DDRB;
struct 
{
	volatile uint8_t DDB0BIT:1 ;
	volatile uint8_t DDB1BIT:1 ;
	volatile uint8_t DDB2BIT:1 ;
	volatile uint8_t DDB3BIT:1 ;
	volatile uint8_t DDB4BIT:1 ;
	volatile uint8_t DDB5BIT:1 ;
	volatile uint8_t DDB6BIT:1 ;
    volatile uint8_t DDB7BIT:1 ;
};
}DDRB_t;


typedef union
{
    volatile uint8_t _DDRC;
struct 
{
	volatile uint8_t DDC0BIT:1 ;
	volatile uint8_t DDC1BIT:1 ;
	volatile uint8_t DDC2BIT:1 ;
	volatile uint8_t DDC3BIT:1 ;
	volatile uint8_t DDC4BIT:1 ;
	volatile uint8_t DDC5BIT:1 ;
	volatile uint8_t DDC6BIT:1 ;
    volatile uint8_t DDC7BIT:1 ;
};
}DDRC_t;


typedef union
{
    volatile uint8_t _DDRD;
struct 
{
	volatile uint8_t DDD0BIT:1 ;
	volatile uint8_t DDD1BIT:1 ;
	volatile uint8_t DDD2BIT:1 ;
	volatile uint8_t DDD3BIT:1 ;
	volatile uint8_t DDD4BIT:1 ;
	volatile uint8_t DDD5BIT:1 ;
	volatile uint8_t DDD6BIT:1 ;
    volatile uint8_t DDD7BIT:1 ;
};
}DDRD_t;



typedef union
{
    volatile uint8_t _PINA;
 struct
{
	volatile uint8_t PINA0BIT:1 ;
	volatile uint8_t PINA1BIT:1 ;
	volatile uint8_t PINA2BIT:1 ;
	volatile uint8_t PINA3BIT:1 ;
	volatile uint8_t PINA4BIT:1 ;
	volatile uint8_t PINA5BIT:1 ;
	volatile uint8_t PINA6BIT:1 ;
    volatile uint8_t PINA7BIT:1 ;
};
}PINA_t;

typedef union
{
    volatile uint8_t _PINB;
 struct
{
	volatile uint8_t PINB0BIT:1 ;
	volatile uint8_t PINB1BIT:1 ;
	volatile uint8_t PINB2BIT:1 ;
	volatile uint8_t PINB3BIT:1 ;
	volatile uint8_t PINB4BIT:1 ;
	volatile uint8_t PINB5BIT:1 ;
	volatile uint8_t PINB6BIT:1 ;
    volatile uint8_t PINB7BIT:1 ;
};
}PINB_t;

typedef union
{
    volatile uint8_t _PINC;
 struct
{
	volatile uint8_t PINC0BIT:1 ;
	volatile uint8_t PINC1BIT:1 ;
	volatile uint8_t PINC2BIT:1 ;
	volatile uint8_t PINC3BIT:1 ;
	volatile uint8_t PINC4BIT:1 ;
	volatile uint8_t PINC5BIT:1 ;
	volatile uint8_t PINC6BIT:1 ;
    volatile uint8_t PINC7BIT:1 ;
};
}PINC_t;


typedef union
{
    volatile uint8_t _PIND;
 struct
{
	volatile uint8_t PIND0BIT:1 ;
	volatile uint8_t PIND1BIT:1 ;
	volatile uint8_t PIND2BIT:1 ;
	volatile uint8_t PIND3BIT:1 ;
	volatile uint8_t PIND4BIT:1 ;
	volatile uint8_t PIND5BIT:1 ;
	volatile uint8_t PIND6BIT:1 ;
    volatile uint8_t PIND7BIT:1 ;
};
}PIND_t;



typedef union
{
    volatile uint8_t _PORTA;
struct
{
	volatile uint8_t PORTA0BIT:1 ;
	volatile uint8_t PORTA1BIT:1 ;
	volatile uint8_t PORTA2BIT:1 ;
	volatile uint8_t PORTA3BIT:1 ;
	volatile uint8_t PORTA4BIT:1 ;
	volatile uint8_t PORTA5BIT:1 ;
	volatile uint8_t PORTA6BIT:1 ;
    volatile uint8_t PORTA7BIT:1 ;
};
}PORTA_t;


typedef union
{
    volatile uint8_t _PORTB;
struct
{
	volatile uint8_t PORTB0BIT:1 ;
	volatile uint8_t PORTB1BIT:1 ;
	volatile uint8_t PORTB2BIT:1 ;
	volatile uint8_t PORTB3BIT:1 ;
	volatile uint8_t PORTB4BIT:1 ;
	volatile uint8_t PORTB5BIT:1 ;
	volatile uint8_t PORTB6BIT:1 ;
    volatile uint8_t PORTB7BIT:1 ;
};
}PORTB_t;

typedef union
{
    volatile uint8_t _PORTC;
struct
{
	volatile uint8_t PORTC0BIT:1 ;
	volatile uint8_t PORTC1BIT:1 ;
	volatile uint8_t PORTC2BIT:1 ;
	volatile uint8_t PORTC3BIT:1 ;
	volatile uint8_t PORTC4BIT:1 ;
	volatile uint8_t PORTC5BIT:1 ;
	volatile uint8_t PORTC6BIT:1 ;
    volatile uint8_t PORTC7BIT:1 ;
};
}PORTC_t;

typedef union
{
    volatile uint8_t _PORTD;
struct
{
	volatile uint8_t PORTD0BIT:1 ;
	volatile uint8_t PORTD1BIT:1 ;
	volatile uint8_t PORTD2BIT:1 ;
	volatile uint8_t PORTD3BIT:1 ;
	volatile uint8_t PORTD4BIT:1 ;
	volatile uint8_t PORTD5BIT:1 ;
	volatile uint8_t PORTD6BIT:1 ;
    volatile uint8_t PORTD7BIT:1 ;
};
}PORTD_t;


typedef struct
{
 uint8_t PIN;
 uint8_t DDR;
 uint8_t PORT;
}GPIO_t;



typedef union
{
    volatile uint8_t _SREG;
struct
{
	volatile uint8_t C:1 ;
    volatile uint8_t Z:1 ;
	volatile uint8_t N:1 ;
	volatile uint8_t V:1 ;
	volatile uint8_t S:1 ;
	volatile uint8_t H:1 ;
	volatile uint8_t T:1 ;
	volatile uint8_t I:1 ;
};
}SREG_t;


typedef union
{
volatile uint8_t _GICR;
struct
{
	volatile uint8_t IVCEBIT    :1 ;
	volatile uint8_t IVSELBIT   :1 ;
	volatile uint8_t UNUSED1    :1 ;
	volatile uint8_t UNUSED2    :1 ;
	volatile uint8_t UNUSED3    :1 ;
	volatile uint8_t INT2BIT    :1 ;
	volatile uint8_t INT1BIT    :1 ;
    volatile uint8_t INT0BIT    :1 ;
};
}GICR_t;

typedef union
{
volatile uint8_t _MCUCR;
struct
{
	volatile uint8_t ISC00BIT   :1 ;
	volatile uint8_t ISC01BIT   :1 ;
	volatile uint8_t ISC10BIT   :1 ;
	volatile uint8_t ISC11BIT   :1 ;
	volatile uint8_t SM0BIT     :1 ;
	volatile uint8_t SM1BIT     :1 ;
	volatile uint8_t SM2BIT     :1 ;
    volatile uint8_t SEBIT      :1 ;
};
}MCUCR_t;


typedef union
{
volatile uint8_t _MCUCSR;
struct
{
	volatile uint8_t PORFBIT    :1 ;
	volatile uint8_t EXTRFBIT   :1 ;
	volatile uint8_t BORFBIT    :1 ;
	volatile uint8_t WDRFBIT    :1 ;
	volatile uint8_t JTRFBIT    :1 ;
	volatile uint8_t UNUSED     :1 ;
	volatile uint8_t ISC2BIT    :1 ;
    volatile uint8_t JTDBIT     :1 ;
};
}MCUCSR_t;


typedef union
{
volatile uint8_t _SFIOR;
struct
{
	volatile uint8_t PSR10BIT       :1 ;
	volatile uint8_t PSR2BIT        :1 ;
	volatile uint8_t PUDBIT         :1 ;
	volatile uint8_t ACMEBIT        :1 ;
	volatile uint8_t UNUSED         :1 ;
	volatile uint8_t ADTS0BIT       :1 ;
	volatile uint8_t ADTS1BIT       :1 ;
    volatile uint8_t ADTS2BIT       :1 ;
};
}SFIOR_t;


typedef union
{
volatile uint8_t _MCUCR;
struct
{
	volatile uint8_t ISC00bit      :1 ;
	volatile uint8_t ISC01bit      :1 ;
	volatile uint8_t ISC10bit      :1 ;
	volatile uint8_t ISC11bit      :1 ;
	volatile uint8_t SM0bit        :1 ;
	volatile uint8_t SM1bit        :1 ;
	volatile uint8_t SM2bit        :1 ;
    volatile uint8_t SEbit         :1 ;
};
}MCUCR_REG_t;


typedef union
{
volatile uint8_t _MCUSCR;
struct
{
	volatile uint8_t PORFbit      :1 ;
	volatile uint8_t EXTRFbit      :1 ;
	volatile uint8_t BORFbit      :1 ;
	volatile uint8_t WDRFbit      :1 ;
	volatile uint8_t JTRFbit        :1 ;
	volatile uint8_t UNUSED        :1 ;
	volatile uint8_t ISC2bit        :1 ;
    volatile uint8_t JTDbit         :1 ;
};
}MCUSCR_t;


typedef union
{
volatile uint8_t _GICR;
struct
{
	volatile uint8_t IVCEbit        :1 ;
	volatile uint8_t IVSELbit       :1 ;
	volatile uint8_t UNUSED1         :1;
    volatile uint8_t UNUSED2        :1 ;
    volatile uint8_t UNUSED3         :1 ;
	volatile uint8_t INT2bit        :1 ;
	volatile uint8_t INT0bit        :1 ;
    volatile uint8_t INT1bit        :1 ;
};
}GICR_REG_t;


typedef union
{
volatile uint8_t _GIFR;
struct
{
	volatile uint8_t UNUSED         :5 ;
	volatile uint8_t INT2bit        :1 ;
	volatile uint8_t INT0bit        :1 ;
    volatile uint8_t INT1bit        :1 ;
};
}GIFR_REG_t;



//Peripheral Instants:

#define   GPIOA                      ((volatile GPIO_t *)(PINA_BASE))
#define   GPIOB                      ((volatile GPIO_t *)(PINB_BASE))
#define   GPIOC                      ((volatile GPIO_t *)(PINC_BASE))
#define   GPIOD                      ((volatile GPIO_t *)(PIND_BASE))

#define   PINA_REG                  ((volatile PINA_t *)(PINA_BASE))
#define   PINB_REG                  ((volatile PINB_t *)(PINB_BASE))
#define   PINC_REG                  ((volatile PINC_t *)(PINC_BASE))
#define   PIND_REG                  ((volatile PIND_t *)(PIND_BASE))

#define   DDRA_REG                  ((volatile DDRA_t *)(DDRA_BASE))
#define   DDRB_REG                  ((volatile DDRB_t *)(DDRB_BASE))
#define   DDRC_REG                  ((volatile DDRC_t *)(DDRC_BASE))
#define   DDRD_REG                  ((volatile DDRD_t *)(DDRD_BASE))

#define   PORTA_REG                 ((volatile PORTA_t *)(PORTA_BASE))
#define   PORTB_REG                 ((volatile PORTB_t *)(PORTB_BASE))
#define   PORTC_REG                 ((volatile PORTC_t *)(PORTC_BASE))
#define   PORTD_REG                 ((volatile PORTD_t *)(PORTD_BASE))

#define   SREG_REG                  ((volatile SREG_t *)(SREG_BASE))
#define   GICR_REG                  ((volatile GICR_REG_t *)(GICR_BASE))
#define   MCUCR_REG                 ((volatile MCUCR_t *)(MCUCR_BASE))
#define   MCUCSR_REG                ((volatile MCUCSR_t *)(MCUCSR_BASE))
#define   SFIOR_REG                 ((volatile SFIOR_t *)(SFIOR_BASE))




//Generic Macros:
//-----------------------------
//-----------------------------
//-----------------------------
//-----------------------------
//-----------------------------
//-----------------------------

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* ATMGA32MCU_H */

