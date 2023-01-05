/*
 * EEPROM_I2C.h
 *
 *  Created on: Jan 4, 2023
 *      Author: OMAR_AYMAN
 *
 *      this HAL was written by me "Omar Ayman", is used to interface EEPROM ICs 24AAxxx
 *      xxx : (00,01,02,04,08,16,32,64,128,256,512)
 *      please follow each instructions I gave to you, to make sure it works properly.
 */

#ifndef SRC_EEPROM_I2C_H_
#define SRC_EEPROM_I2C_H_
//===========================================================================
#include <stdint.h>
#include <stdlib.h>
//===========================================================================
/* do NOT forget to include your MCAL Drivers
 *I am using STM32F103C6 here, you can replace it
 * with any microcontroller you want.
 * so, add Two MCLAs :
 * GPIO MCAL
 * I2C MCAL
 */
#include "I2CSTM32.h"
#include "GPIOSTM32.h"
//===========================================================================

/* I2C MCAL MACROs
 * replace these two (I2C_WR(EEPROMx_Address,DATA,datalen) & I2C_R(EEPROMx_Address,DATA,datalen) )
 * with your appropriate functions as it is written
 * in your I2C_MCAL driver
 */
#define I2C_WR(EEPROMx_Address,DATA,datalen)        I2C_Master_Tx(I2C_1, EEPROMx_Address,DATA,datalen, WITH_STOP, START)
#define I2C_R(EEPROMx_Address,DATA,datalen)         I2C_Master_Rx(I2C_1, EEPROMx_Address, DATA,datalen,WITH_STOP,REAPEATED_START);
//===========================================================================

//===========================================================================
//________________________--do NOT -- _ edit any of those below____________________________________
//===========================================================================
//EEPROM  DEVICE SELECT
#define EEPROM0_ADDRESS    (uint16_t)(0xA0U)
#define EEPROM1_ADDRESS    (uint16_t)(0xA1U)
#define EEPROM2_ADDRESS    (uint16_t)(0xA2U)
#define EEPROM3_ADDRESS    (uint16_t)(0xA3U)
#define EEPROM4_ADDRESS    (uint16_t)(0xA4U)
#define EEPROM5_ADDRESS    (uint16_t)(0xA5U)
#define EEPROM6_ADDRESS    (uint16_t)(0xA6U)
#define EEPROM7_ADDRESS    (uint16_t)(0xA7U)
//===========================================================================
//prototypes
/**================================================================
* EEPROM_I2C_Ext_Write
* this function writes onto External EEPROM from 1byte to 32 bytes
 * maximum data you can write in one call is 1page (32bytes of data)
* INPUTS : it takes 4 arguments :
* 1. EEPROMx_Address   >>>   @ref EEPROM  DEVICE SELECT
* 2. DATA_Address      >>>   its dependent on the model you use,
* for instance :(0x0000 ~0x1fff) in case of :(64Kbits)(8kbytes)(every page = 32bytes)
* 3. DATA              >>> pointer to Data you wanna send
* 4. datalen           >>> length of data you wanna send maximum (32) for each call, because the page capacity is 32 byte
* it returns nothing !
 */

void EEPROM_I2C_Ext_Write(uint8_t EEPROMx_Address,uint16_t DATA_Address,uint8_t *DATA,uint32_t datalen);

//===========================================================================
//prototypes
/**================================================================
* EEPROM_I2C_Ext_Read
* this function Read from External EEPROM from 1byte to 32 bytes
 * maximum data you can Read from one call is 1page (32bytes of data)
* INPUTS : it takes 4 arguments :
* 1. EEPROMx_Address   >>>   @ref EEPROM  DEVICE SELECT
* 2. DATA_Address      >>>   its dependent on the model you use,
* for instance :(0x0000 ~0x1fff) in case of :(64Kbits)(8kbytes)(every page = 32bytes)
* 3. DATA               >>> pointer to Data you wanna receive
* 4. datalen            >>>   length of data you wanna receive
* it returns nothing !
 */
void EEPROM_I2C_Ext_Read(uint8_t EEPROMx_Address,uint16_t DATA_Address,uint8_t *DATA,uint32_t datalen);








#endif /* SRC_EEPROM_I2C_H_ */
