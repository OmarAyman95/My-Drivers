/*
 * EEPROM_I2C.c
 *
 *  Created on: Jan 4, 2023
 *      Author: OMAR
 */

#include "EEPROM_I2C.h"

void EEPROM_I2C_Ext_Write(uint8_t EEPROMx_Address,uint16_t DATA_Address,uint8_t *DATA,uint32_t datalen)
{
	uint8_t Buffer[34],i;
	Buffer[0]=(uint8_t)(DATA_Address>>8);//MSB
	Buffer[1]=(uint8_t)(DATA_Address);//LSB
	datalen+=1;

	for(i=2;i<datalen;i++)
		Buffer[i]=DATA[i-2];

	//I2C_Master_Tx(I2C_1, EEPROMx_Address,Buffer,datalen, WITH_STOP, START);
	I2C_WR(EEPROMx_Address,Buffer,datalen);
}

void EEPROM_I2C_Ext_Read(uint8_t EEPROMx_Address,uint16_t DATA_Address,uint8_t *DATA,uint32_t datalen)
{
		uint8_t READ_ADDRESS[2];
		READ_ADDRESS[0]=(uint8_t)(DATA_Address>>8);
		READ_ADDRESS[1]=(uint8_t)(DATA_Address);
		I2C_WR(EEPROMx_Address,READ_ADDRESS,2);
		I2C_R(EEPROMx_Address, DATA,datalen);
}
