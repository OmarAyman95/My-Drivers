#include "EEPROM_SPI_25LCxxx.h"

//to receive 1 page of data (16Bytes) from Eternal EEPROM
static uint8_t gbuffer[16];


void EEPROM_Ext_Write_Bytes(uint8_t start_address,uint8_t DATA[16],uint8_t size)
{
    uint8_t i;
     //just to see when CSS goes low 
    CSS_HIGH();delay_ms(10);
     //EN-Write because EEPROM has a type of protection (0x06)
    CSS_LOW();SPI_WRITE(0x06);delay_ms(10); CSS_HIGH();
    //Write instruction (0x02)
    CSS_LOW();SPI_WRITE(EEPROM_WRITE_INSTRUCTION); delay_ms(10);
    //the address you want to write at 
    SPI_WRITE(start_address); delay_ms(10);
    //bytes to be written 
    for(i=0;i<size;i++)
    {
             SPI_WRITE(DATA[i]);
             delay_ms(10);
             if(i==15)break;
    }
    CSS_HIGH();
}

void EEPROM_Ext_Write_Page(uint8_t page_number,uint8_t DATA[16])
{
    uint8_t i,start_address=page_number*16-16;
     //just to see when CSS goes low 
    CSS_HIGH();delay_ms(10);
     //EN-Write because EEPROM has a type of protection (0x06)
    CSS_LOW();SPI_WRITE(0x06);delay_ms(10); CSS_HIGH();
    //Write instruction (0x02)
    CSS_LOW();SPI_WRITE(EEPROM_WRITE_INSTRUCTION); delay_ms(10);
    //the address you want to write at 
    SPI_WRITE(start_address); delay_ms(10);
    //bytes to be written 
    for(i=0;i<=15;i++)
    {
             SPI_WRITE(DATA[i]);
             delay_ms(10);
    }
    CSS_HIGH();
}
void EEPROM_Ext_Write_Byte(uint8_t address,uint8_t DATA)
{
   //just to see when CSS goes low 
    CSS_HIGH();delay_ms(10);
     //EN-Write because EEPROM has a type of protection (0x06)
    CSS_LOW();SPI_WRITE(0x06);delay_ms(10); CSS_HIGH();
    //Write instruction (0x02)
    CSS_LOW();SPI_WRITE(EEPROM_WRITE_INSTRUCTION);
    //the address you want to write at 
    // SPI_WRITE(0x00); delay_ms(10); //MSB (25LC080)
    SPI_WRITE(address); 
    //byte to be written 
    SPI_WRITE(DATA);
    delay_ms(10);
   
    CSS_HIGH();  
    
}

uint8_t* EEPROM_Ext_Read(uint8_t start_address,uint8_t size)
{
    uint8_t index=0,i=0;
    for(i=start_address;i<(start_address+size);i++)
    {
         //just to see when CSS goes low 
        CSS_HIGH();delay_ms(10);
        CSS_LOW();delay_ms(10); 
        SPI_WRITE(EEPROM_READ_INSTRUCTION); //READ instruction
        SPI_WRITE(i); //the address you want to Read from (LSB)
        SPI_WRITE(0x00); //the address you want to Read from (MSB)
        gbuffer[index++] = SPI_READ(); // receive stored Data
        CSS_HIGH();
    }
    return gbuffer;
}

void EEPROM_Ext_Write_Byte_General(uint16_t address,uint8_t DATA)
{
    uint8_t AddressLSB=(uint8_t)address;
    #ifdef BIG_EEPROM 
        uint8_t  AddressMSB=(uint8_t)(address>>8);
    #endif
   //just to see when CSS goes low 
    CSS_HIGH();delay_ms(10);
     //EN-Write because EEPROM has a type of protection (0x06)
    CSS_LOW();SPI_WRITE(0x06);CSS_HIGH();
    //Write instruction (0x02)
    CSS_LOW();SPI_WRITE(EEPROM_WRITE_INSTRUCTION);
    //the address you want to write at 
   #ifdef BIG_EEPROM 
      SPI_WRITE(AddressMSB);  //(25LC080)
   #endif
    SPI_WRITE(AddressLSB); 
    delay_ms(10);
    //byte to be written 
    SPI_WRITE(DATA);
    delay_ms(10);
    CSS_HIGH();     
}

uint8_t* EEPROM_Ext_Read_General(uint16_t start_address,uint8_t size)
{
    uint16_t index=0,i=0;
    uint8_t AddressLSB=0;
    for(i=start_address;i<(start_address+size);i++)
    {
         AddressLSB=(uint8_t)i;
         #ifdef BIG_EEPROM
            uint8_t AddressMSB=(uint8_t)(i>>8);
         #endif
         //just to see when CSS goes low 
        CSS_HIGH();delay_ms(10);
        CSS_LOW();delay_ms(10); 
        SPI_WRITE(EEPROM_READ_INSTRUCTION);
        #ifdef BIG_EEPROM
            SPI_WRITE(AddressMSB); 
        #endif
        SPI_WRITE(AddressLSB);  
        SPI_WRITE(0x00); 
        gbuffer[index++] = SPI_READ(); 
        CSS_HIGH();
    }
    return gbuffer;
}

void EEPROM_Ext_Write_Page_General(uint16_t page_number,uint8_t DATA[16])
{
    uint16_t i,start_address=page_number*16-16;
    uint8_t AddressLSB=(uint8_t)start_address;
    #ifdef BIG_EEPROM 
        uint8_t  AddressMSB=(uint8_t)(start_address>>8);
    #endif
     //just to see when CSS goes low 
    CSS_HIGH();delay_ms(10);
     //EN-Write because EEPROM has a type of protection (0x06)
    CSS_LOW();SPI_WRITE(0x06);CSS_HIGH();
    //Write instruction (0x02)
    CSS_LOW();SPI_WRITE(EEPROM_WRITE_INSTRUCTION);
    //the address you want to write at 
    #ifdef BIG_EEPROM 
      SPI_WRITE(AddressMSB);  //(25LC080)
   #endif
      SPI_WRITE(AddressLSB); 
      delay_ms(10);
    //bytes to be written 
    for(i=0;i<=15;i++)
    {
             SPI_WRITE(DATA[i]);
             delay_ms(10);
    }
    CSS_HIGH();
}

void EEPROM_Ext_Write_Bytes_General(uint16_t start_address,uint8_t DATA[16],uint8_t size)
{
    uint8_t i,AddressLSB=(uint8_t)start_address;
    #ifdef BIG_EEPROM 
        uint8_t  AddressMSB=(uint8_t)(start_address>>8);
    #endif
     //just to see when CSS goes low 
    CSS_HIGH();delay_ms(10);
     //EN-Write because EEPROM has a type of protection (0x06)
    CSS_LOW();SPI_WRITE(0x06);CSS_HIGH();
    //Write instruction (0x02)
    CSS_LOW();SPI_WRITE(EEPROM_WRITE_INSTRUCTION);
    //the address you want to write at 
    #ifdef BIG_EEPROM 
      SPI_WRITE(AddressMSB);  //(25LC080)
    #endif
    SPI_WRITE(AddressLSB); 
    delay_ms(10);
    //bytes to be written 
    for(i=0;i<size;i++)
    {
             SPI_WRITE(DATA[i]);
             delay_ms(10);
             if(i==15)break;
    }
    CSS_HIGH();
}
