/* 
 * File:   25LCxxxEEPROM_SPI.h
 * Author: OMAR AYMAN
 *
 * Created on December 31, 2022, 10:40 AM
 * this HAL operates with these models: 
 * 25LC010 , 25LC020
 * 25LC040
 * 25LC080 ,25LC160 ,25LC320 ,25LC640 ,25LC256 ,25LC512
 */

#ifndef EEPROM_SPI_25LCXXX_H
#define	EEPROM_SPI_25LCXXX_H
//===========================================================================
#include <stdint.h>
#include <stdlib.h>
//===========================================================================
/* do NOT forget to include your MCAL Drivers 
 *I am using ATMEGA32 here, you can replace it  
 * with any microcontroller you want. 
 * so, add Two MCLAs :
 * GPIO MCAL
 * SPI MCAL
 */
#include "SPImega32.h"
#include "GPIO_MEGA32.h"
/*this driver contains  [void delay_ms(int t)] function,it is mandatory ,so please build it 
*and include it as I include delayT0.h below .!
 * */
#include "delayT0.h" 
//===========================================================================
/*CSS MACROs
 *replace these two ( PORT_Reset_pin(GPIOB,_PIN4)) & (PORT_Set_pin(GPIOB,_PIN4))   
 * with your appropriate functions as it is written 
 * in your GPIO_MCAL driver 
 */ 
#define CSS_LOW()   PORT_Reset_pin(GPIOB,_PIN4)
#define CSS_HIGH()  PORT_Set_pin(GPIOB,_PIN4)
//===========================================================================
/* SPI MCAL MACROs
 * replace these two (SPI_Send(x) & SPI_Recieve(x))   
 * with your appropriate functions as it is written 
 * in your SPI_MCAL driver 
 */ 
#define SPI_WRITE(x)                    SPI_Send(x)
#define SPI_READ(x)                     SPI_Recieve(x)
//===========================================================================
 //SECTOR SELECTs
/**
 *  in case of  : 25LC010 : you have just one sector (8pages in total), so it is worthless to 
 *  enable  " EEPROM_SECTOR2 " MACRO !. 
 *  so you always enable "EEPROM_SECTOR1"
 * 
 *  in case of  : 25LC020 : you have just one sector (16pages in total), so it is worthless to 
 *  enable  " EEPROM_SECTOR2 " MACRO !. 
 *  so you always enable "EEPROM_SECTOR1"
 * 
 * in case of  : 25LC040 : you have two sectors to select in between 
 * (32pages in total - 16 pages in each sector).
 * so if you wanna use pages from page 1~16 Please enable "EEPROM_SECTOR1",
 *    if you wanna use pages from page 17~32 Please enable "EEPROM_SECTOR2"
 * 
 * in case of :  25LC080 ,25LC160 ,25LC320 ,25LC640 ,25LC256 ,25LC512 
 *  please enable " EEPROM_SECTOR1 " and " BIG_EEPROM "
 * 
 * 
 * ____________________________________________________________________________________
 * |______________EEPROM_SECTOR2___________EEPROM_SECTOR1_________BIG_EEPROM__________|                                 
 * |_25LC010__________NO_________________________YES___________________NO_____________|                                    
 * |__________________________________________________________________________________|
 * |_25LC020__________NO_________________________YES__________________NO______________|                                    
 * |__________________________________________________________________________________|                                     
 * |_25LC040__________YES________________________YES___________________NO_____________|                                   
 * |__________________________________________________________________________________|
 * |_25LC080___________NO_________________________YES__________________YES____________|
 * |__________________________________________________________________________________|
 * |_25LC160___________NO_________________________YES__________________YES____________|
 * |__________________________________________________________________________________|
 * |_25LC320___________NO_________________________YES__________________YES____________|
 * |__________________________________________________________________________________|
 * |_25LC640___________NO_________________________YES__________________YES____________|
 * |__________________________________________________________________________________|
 * |_25LC256___________NO_________________________YES__________________YES____________|
 * |__________________________________________________________________________________|
 * |_25LC512___________NO_________________________YES__________________YES____________|
 * 
 * 
 * 
 */
#define EEPROM_SECTOR1 
//#define EEPROM_SECTOR2 
//===========================================================================
/**
 * please enable this " BIG_EEPROM " MACRO  in case of : 
 *  25LC080 ,25LC160 ,25LC320 ,25LC640 ,25LC256 ,25LC512
 */
#define BIG_EEPROM
//===========================================================================
//________________________--do NOT -- _ edit any of those below____________________________________
//===========================================================================
#define EEPROM_1SECTION_WRITE                         (0x02U)
#define EEPROM_1SECTION_READ                          (0x03U)
#define EEPROM_2SECTION_WRITE                         (0x0AU)
#define EEPROM_2SECTION_READ                          (0x0BU)

#ifdef  EEPROM_SECTOR1
#define EEPROM_WRITE_INSTRUCTION        EEPROM_1SECTION_WRITE
#define EEPROM_READ_INSTRUCTION         EEPROM_1SECTION_READ
#endif


#ifdef EEPROM_SECTOR2
#define EEPROM_WRITE_INSTRUCTION         EEPROM_2SECTION_WRITE
#define EEPROM_READ_INSTRUCTION          EEPROM_2SECTION_READ
#endif
//===========================================================================
//prototypes

/**================================================================
* EEPROM_Ext_Write_Bytes
* this function writes onto External EEPROM from 1byte to 16 bytes 
 * maximum data you can write in one call is 1page (16bytes of data)
* INPUTS : it takes 3 arguments :
* 1. start_address  >>>  (0x00 ~ 0x7f)
* 2. DATA[16]       >>>  array of bytes you wanna write (1~16max)
* 3. size           >>>  number of bytes you wanna write 
* 
* it returns nothing !
 */
void EEPROM_Ext_Write_Bytes(uint8_t start_address,uint8_t DATA[16],uint8_t size);
//===========================================================================
/**================================================================
* EEPROM_Ext_Write_Byte
* this function writes onto External EEPROM from 1byte to 16 bytes 
 * maximum data you can write in one call is 1page (16bytes of data)
* INPUTS : it takes 2 arguments :
* 1. address  >>>  (0x00 ~ 0xf0 or 0xff depends on model of eeprom)
* 2. DATA      >>>   byte you wanna write
* it returns nothing !
 */
void EEPROM_Ext_Write_Byte(uint8_t address,uint8_t DATA);
//===========================================================================
/**================================================================
* EEPROM_Ext_Write_Page
* this function writes onto External EEPROM from 1byte to 16 bytes 
 * maximum data you can write in one call is 1page (16bytes of data)
* INPUTS : it takes 3 arguments :
* 1. page_number  >>>  (1 ~ 8 or 16 depends on model of eeprom )
 *  25LC010 : page_number range is (1~8)
 *  25LC020 : page_number range is (1~16)
 *  25LC040 : page_number range is (1~16), you have to select what sector you want write on 
 *  @ ref " SECTOR SELECTs "
* 2. DATA[16]       >>>  array of bytes you wanna write on this page 
* 
* it returns nothing !
 */
void EEPROM_Ext_Write_Page(uint8_t page_number,uint8_t DATA[16]);
/**================================================================
* EEPROM_Ext_Read
* this function Reads from External EEPROM from 1byte to 16 bytes 
 * maximum data you can read in one call is a 1_page (16bytes of data)
* INPUTS : it takes 2 arguments :
* 1. start_addressLSB  >>>  (0x00 ~ 0x7f)
* 2. size       >>>   number of bytes you wanna read
* 
* it returns pointer to array of bytes you have read
 */
uint8_t* EEPROM_Ext_Read(uint8_t start_address,uint8_t size);
//===========================================================================

void EEPROM_Ext_Write_Byte_General(uint16_t address,uint8_t DATA);
uint8_t* EEPROM_Ext_Read_General(uint16_t start_address,uint8_t size);
void EEPROM_Ext_Write_Page_General(uint16_t page_number,uint8_t DATA[16]);
void EEPROM_Ext_Write_Bytes_General(uint16_t start_address,uint8_t DATA[16],uint8_t size);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* 25LCXXXEEPROM_SPI_H */

