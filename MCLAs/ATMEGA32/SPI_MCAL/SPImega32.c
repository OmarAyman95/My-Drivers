#include "SPImega32.h"

SPI_config *gSPI_config;

static void SPI_Set_Pins(void)
{ /*    
   * SS :   PB4 : OUT
     MOSI:  PB5 : OUT
     MISO:  PB6 : IN
     SCK :  PB7 : OUT
     */
    if(gSPI_config->DeviceMode == SPI_MASTER_MODE)
    {
        PORT_init(GPIOB,OUTPUT_MODE,_PIN4);
        PORT_init(GPIOB,OUTPUT_MODE,_PIN5);
        PORT_init(GPIOB,OUTPUT_MODE,_PIN7);
    }
    else if(gSPI_config->DeviceMode == SPI_SLAVE_MODE)
    {
        PORT_init(GPIOB,OUTPUT_MODE,_PIN6);  
    }
}

void SPI_init(SPI_config *SPI_OBJ)
{
    uint8_t temp_SPCR = 0x00,temp_SPSR = 0x00;
    gSPI_config = SPI_OBJ;
    // Enable SPI
    temp_SPCR = (1U<<6);
    // set device Mode 
    temp_SPCR |= SPI_OBJ->DeviceMode;
    //set LSB or MSB 
    temp_SPCR |= SPI_OBJ->LsbOrMsb; 
    //set SCK clock
    if(SPI_OBJ->SCKfrequency == SPI_Fosc_BR2)
    {
        temp_SPSR |= SPI_Fosc_BR2;
        temp_SPCR |= SPI_Fosc_BR4;
    }
    else if(SPI_OBJ->SCKfrequency == SPI_Fosc_BR8)
    {
        temp_SPSR |= SPI_Fosc_BR8;
        temp_SPCR |= SPI_Fosc_BR16;
    }
    else if(SPI_OBJ->SCKfrequency == SPI_Fosc_BR32)
    {
        temp_SPSR |= SPI_Fosc_BR32;
        temp_SPCR |= SPI_Fosc_BR64;
    }
    else 
    {
       temp_SPCR |= SPI_OBJ->SCKfrequency;  
    }
    //set Interrupt_Enable
    temp_SPCR |= SPI_OBJ->Interrupt_Enable;
    if(SPI_OBJ->Interrupt_Enable == SPI_INTERRUPT_ENABLE)
    {
        SREG_REG->I = 1; 
    }
    //set IdleState 
    temp_SPCR |= SPI_OBJ->IdleState;
    //set ClkPhase
    temp_SPCR |= SPI_OBJ->ClkPhase;
    //Set pins 
    SPI_Set_Pins();
    //write On SPCR & SPSR
    SPCR_REG->_SPCR = temp_SPCR;
    SPSR_REG->_SPSR = temp_SPSR;
    
}


void SPI_Dinit(void)
{
    SPCR_REG->_SPCR = 0x00 ;
    SPSR_REG->_SPSR = 0x00 ; 
}
void SPI_Send(uint8_t DATA)
{
    SPDR_REG = DATA;
    while(SPSR_REG->SPIFbit == 0);
    SPSR_REG->SPIFbit = 0 ;
}
uint8_t SPI_Recieve(void)
{
    while(SPSR_REG->SPIFbit == 0);
    SPSR_REG->SPIFbit = 0 ;
    return SPDR_REG;
}
ISR(SPI_STC_vect)
{   
    
}
