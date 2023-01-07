#include "Timer0.h"

Timer0_config *gTMR0_config;
static uint32_t TCNT0_REF_start;

void TMR0_FAST_PWM_MODE_Init(uint32_t Foscn ,uint8_t DutyCycle)
{
    uint32_t tempOCR0=0x00;
    uint32_t PS=0x00,PS_true=0x00;
    uint32_t period=0x00,COUNTS_true=0x00,T0_start=0x00;
    //__________________________Frequency calculations__________________________
    
    PS = (uint32_t)(256 * Foscn);
    PS = (uint32_t)(FCPU_CLK / PS );
    
    if(PS<=1)
    {
        TCCR0_REG->_TCCR0 |= TMR0_INTERNAL_CLK_PS_1_SRC;
        PS_true = 1;
    }
    else if(PS>1 && PS<=8)
    {
        TCCR0_REG->_TCCR0 |= TMR0_INTERNAL_CLK_PS_8_SRC;
        PS_true = 8;
    }
    else if(PS>8 && PS<=64)
    {
        TCCR0_REG->_TCCR0 |= TMR0_INTERNAL_CLK_PS_64_SRC;
        PS_true = 64;
    }
    else if(PS>64 && PS<=256)
    {
        TCCR0_REG->_TCCR0 |= TMR0_INTERNAL_CLK_PS_256_SRC;
        PS_true = 256;
    }
    else if(PS>256 && PS<=1024)
    {
        TCCR0_REG->_TCCR0 |= TMR0_INTERNAL_CLK_PS_1024_SRC;
        PS_true = 1024;
    }
    //==========================================================================
    
    
    //___________________________ERROR CORRECTION_______________________________
    //period of frequency of PWM (using calculated PS)
    period = (uint32_t)(PS * 256);
    period = (uint32_t)(period / FCPU_CLK_IN_MHZ);
    
    //counts required to generate the frequency of PWM (using used PS)
    COUNTS_true = (uint32_t)(FCPU_CLK_IN_MHZ * period);
    COUNTS_true = (uint32_t)(COUNTS_true / PS_true);
    
    //reference that TMR0 must start at to generate the frequency of PWM
    T0_start = (uint32_t)(256 - COUNTS_true);
    TCNT0_REF_start = T0_start;
     //==========================================================================
    
    
    //__________________________Duty Cycle calculations_________________________
    tempOCR0 = (uint32_t)(COUNTS_true*DutyCycle);
    tempOCR0 = (uint32_t)(tempOCR0/100);
    tempOCR0 = (uint32_t)(T0_start + tempOCR0);
    OCR0_REG = tempOCR0;
    //==========================================================================
      
}

void TMR0_CTC_MODE_Init(uint32_t Foscn)
{
    uint32_t result;
    uint16_t PS=0x00;
    
    switch(gTMR0_config->Timer0_Clock_SRC)
    {
        case TMR0_INTERNAL_CLK_PS_1_SRC    :    PS = 1 ;    break;
        case TMR0_INTERNAL_CLK_PS_8_SRC    :    PS = 8 ;    break;   
        case TMR0_INTERNAL_CLK_PS_64_SRC   :    PS = 64 ;   break;
        case TMR0_INTERNAL_CLK_PS_256_SRC  :    PS = 256 ;  break;
        case TMR0_INTERNAL_CLK_PS_1024_SRC :    PS = 1024 ; break;
    }
   
    result = (uint32_t)(2 * Foscn * PS);
    result = (uint32_t)(FCPU_CLK / result);
    result -=1;
    OCR0_REG |= result;
      
}

void TMR0_init(Timer0_config *TMR0_config)
{
                            //save config_struct to global 
    gTMR0_config = TMR0_config;
     //=======================================================
                            //Setting TCCR0
    uint8_t tempTCCR0Reg = 0x00;
    tempTCCR0Reg |= TMR0_config->Timer0_Mode;
    tempTCCR0Reg |= TMR0_config->Timer0_COM_Mode;
    tempTCCR0Reg |= TMR0_config->Timer0_Clock_SRC;
    //=======================================================
                             //Setting TIMSK
    uint8_t tempTIMSKReg = 0x00;
    tempTIMSKReg |= TMR0_config->Timer0_Interrupt;
    tempTIMSKReg |= TMR0_config->Timer0_Compare_Interrupt;
    //=======================================================
                           //Pins setting
    if(TMR0_config->Timer0_COM_Mode != TMR0_OCR_PIN_DISCONNECTED)
        PORT_init(GPIOB,OUTPUT_MODE,_PIN3);
    if(TMR0_config->Timer0_Clock_SRC == TMR0_EXTERNAL_CLK_SRC_FALLING_EDGE || 
       TMR0_config->Timer0_Clock_SRC == TMR0_EXTERNAL_CLK_SRC_RISING_EDGE)
        PORT_init(GPIOB,INPUT_FLOATING_MODE,_PIN0);
                            //enable Global interrupt vector
    if((TMR0_config->Timer0_Interrupt == TMR0_INTERRUPT_ENABLE) ||
       (TMR0_config->Timer0_Compare_Interrupt == TMR0_COMPARE_INTERRUPT_ENABLE) )
        GLOBAL_INTERRUPT_ENABLE();
                            //Equalizations
    TCCR0_REG->_TCCR0 = tempTCCR0Reg; 
    TIMSK_REG->_TIMSK = tempTIMSKReg;
    //=======================================================
}



ISR(TIMER0_OVF_vect)
{
    TCNT0_REG = TCNT0_REF_start;
}

ISR(TIMER0_COMP_vect)
{
  
}