/*
 *  File : I2CSTM32.h
 *  Author: OMAR MOHAMED AYMAN
 *  https://github.com/OmarAyman95
 *  ommoor642@hotmail.com
 *  this MCAL file is used with STM32F103C6 MCU ARM-CORTEX-M3 based processor
 *  it contains APIs to Send/recieve data through I2C Module of the MCU
 *  Created on: JAN 1, 2023
 */

#ifndef SRC_I2CSTM32_H_
#define SRC_I2CSTM32_H_


/*----------------------------------------includes----------------------------*/
#include "STM32F103.h"
#include "GPIOSTM32.h"


/*---------------------User Defined DataTypes----------------------------*/

typedef struct
{
	uint16_t Addressing_mode;//@ ref Slave_Addressing_Modes
	uint16_t Dual;
	uint16_t Primary_address;
	uint16_t Secondary_address;
}S_i2C_Slave_Device_Address_t;

typedef enum{
		I2C_EV_STOP,
		I2C_ER_AF,
		I2C_EV_ADDRESS_MATCHED,
		I2C_EV_DATA_REQ,
		I2C_EV_DATA_REC,

}Slave_State;

typedef enum{WITH_STOP,WITHOUT_STOP}Stop_State;

typedef enum{START,REAPEATED_START}Repeated_Start_State;

typedef enum{DISABLE=0 ,ENABLE=1}Functional_State;

typedef enum{RESET =0,SET=1}Flag_Status;

typedef enum{I2C_WRITE =0,I2C_READ=1}I2C_Direction;

typedef enum
{
	I2C_FLAG_BUSY=0
	,EV5=1         //EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	,EV6        // EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	,EV7       //EV7: RxNE=1, cleared by reading DR register
	,EV7_1    //EV7_1: RxNE=1 cleared by reading DR register,program ACK=0and STOP request.
	,EV8      //EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
	,EV8_1     //EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	,EV8_2   //EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	,MASTER_BYTE_TRANSMITTING = ((uint32_t)(0x00070080UL))
}Status;

typedef struct
{
	uint32_t 								I2CBusSpeed; //@ref BUS_SPEED
	uint32_t 								ClockStretchingEnable; //@ref Stretching_EN_DIS
	uint32_t 								I2CDeviceMode; // @ref I2C_GENERAL_ODES
	S_i2C_Slave_Device_Address_t 			I2CDeviceAddress;
	uint32_t 								I2CAckEnable;//@ref  I2CAckEnable
	uint32_t 								General_Call_Address_Detection;//@ref General_Call_Enable

	void                                    (*ptrToSlaveEventISR)(Slave_State state);


}I2C_config;




/*----------------------------------------Macros----------------------------*/


#define FAPB1_CLK_SPEED 				                  (8UL)
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING				(0x00070080UL)
/*
 *    fPCLK1 must be at least 2 MHz to achieve Sm mode I²C frequencies.
 *        It must be at least 4 MHz to achieve Fm mode I²C frequencies.
 *   It must be a multiple of 10MHz to reach the 400 kHz maximum I²C Fm mode clock
 *
 *
 *   The following is the required sequence in master mode.
 *
• Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
	(FREQ bits <bit5:bit0> in I2C_CR2 register )


• Configure the clock control registers
	(CCR bits <bit11 : bit0> in I2C_CCR register)
	CCR = (FAPB1/2FI2C) = (tH/tPCLK1) = (tL/tPCLK1)
	where :
	tPCLK1 = (1/FAPB1) , tH = On_interval of FI2C, tL = Off_interval of FI2C

• Configure the rise time register
	( TRISE bits <bit5 : bit0> in I2C_TRISE register)
	TRISE = (maximum allowed SCL rise time / tPCLK1 +1)
	where :
	in standard mode (sm) : maximum allowed SCL rise time = 1000ns
	for instance : if FAPB1 = 8MHZ (tPCLK1 = 125ns), the TRISE = 1000ns/125ns+1 =8+1 = 9


• Program the I2C_CR1 register to enable the peripheral
• Set the START bit in the I2C_CR1 register to generate a Start condition
 * */
//BUS_SPEED

#define I2C_CLOCK_SM_50K				(50000UL)
#define I2C_CLOCK_SM_100K				(100000UL)
#define I2C_CLOCK_FM_200K				(200000UL)
#define I2C_CLOCK_FM_400K				(400000UL)


//Stretching_EN_DIS
/*
 * at I2C_CR1 reg
 *
 * 	Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
	This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, until
	it is reset by software.
	0: Clock stretching enabled
	1: Clock stretching disabled
 *
 * */
#define I2C_STRETCHING_EN						(0U)
#define I2C_STRETCHING_DIS						(I2C_CR1_NOSTRETCH)

// I2C_GENERAL_ODES

/*
 * at I2C_CR1 reg
 *
    Bit 1 SMBUS: SMBus mode
	0: I2C mode
	1: SMBus mode
 * */

#define I2C_I2C_MODE							   (0U)
#define I2C_SMBUS_MODE							(I2C_CR1_SMBUS)


//Slave_Addressing_Modes

/*
 * at I2C_OAR1 reg
	 *
	Bit 15 ADDMODE Addressing mode (slave mode)
	0: 7-bit slave address (10-bit address not acknowledged)
	1: 10-bit slave address (7-bit address not acknowledged)
 * */

#define I2C_7bit_Address_Mode                    (0U)
#define I2C_10bit_Address_Mode					 (1U<<15)

//I2CAckEnable

/*
 * at I2C_CR1 reg
	Bit 10 ACK: Acknowledge enable
	This bit is set and cleared by software and cleared by hardware when PE=0.
	0: No acknowledge returned
	1: Acknowledge returned after a byte is received (matched address or data
 * */

#define I2C_ACK_EN							(I2C_CR1_ACK)
#define I2C_ACK_DIS							(0U)


//

/*
 * at I2C_CR1 reg
 *
	Bit 6 ENGC: General call enable
	0: General call disabled. Address 00h is NACKed.
	1: General call enabled. Address 00h is ACKed.
 * */

#define I2C_GEN_CALL_EN							(I2C_CR1_ENGC)
#define I2C_GEN_CALL_DIS                        (0U)





//===============================================================================
//__________________________APIs prototypes____________________________________
//===========================================================================
/**================================================================
* I2C_init
* this function init I2C Module, so it is able to
* work in different modes
* INPUTS : it takes 2 arguments :
* 1. I2Cx  				  >>> I2C_1 Or I2C_2
* 2. I2C_init_struct      >>> configuration structure
* it returns nothing !
 */
void I2C_init(volatile I2C_t *I2Cx ,I2C_config *I2C_init_struct);
//===========================================================================
/**================================================================
* I2C_Dinit
* this function Reset I2Cx module and disable the interrupts of the module
* INPUTS : it takes 1 argument :
* 1. I2Cx  				  >>> I2C_1 Or I2C_2
* it returns nothing !
	 */
void I2C_Dinit(volatile I2C_t *I2Cx);
//===========================================================================
/**================================================================
* I2C_Master_Tx
* this function used to send data from Master to slaves that attached to the bus
* INPUTS : it takes 6 arguments :
* 1. I2Cx  				  >>> I2C_1 Or I2C_2
* 2. Slave_address        >>> the address of the slave you want send data to
* 3. data_buffer          >>> the data you want to send
* 4. datalen              >>> size of the send data in bytes
* 5. stop                 >>> stop_state its enumeration data type@ref "Stop_State"
* 6. start         		  >>> start_state its enumeration data type@ref "Repeated_Start_State"
* it returns nothing !
 */
void I2C_Master_Tx(volatile I2C_t *I2Cx , uint16_t Slave_address , uint8_t *data_buffer, uint32_t datalen,Stop_State stop,Repeated_Start_State start);
//===========================================================================
/**================================================================
* I2C_Master_Rx
* this function used to receive data from slaves that attached to the bus
* INPUTS : it takes 6 arguments :
* 1. I2Cx  				  >>> I2C_1 Or I2C_2
* 2. Slave_address        >>> the address of the slave you want receive data from
* 3. data_buffer          >>> the data you are going to receive
* 4. datalen              >>> size of the received data in bytes
* 5. stop                 >>> stop_state its enumeration data type@ref "Stop_State"
* 6. start         		  >>> start_state its enumeration data type@ref "Repeated_Start_State"
* it returns nothing !
 */
void I2C_Master_Rx(volatile I2C_t *I2Cx , uint16_t Slave_address , uint8_t *data_buffer, uint32_t datalen,Stop_State stop,Repeated_Start_State start);
//===========================================================================
/**================================================================
* I2C_Generate_Start
* this function used to generate start, repeated start from master to slaves
* INPUTS : it takes 3 arguments :
* 1. I2Cx  				  >>> I2C_1 Or I2C_2
* 2. Newstate             >>> Functional_State its enumeration data type @ref "Functional_State"
* 3. start         		  >>> start_state its enumeration data type@ref "Repeated_Start_State"
* it returns nothing !
 */
void I2C_Generate_Start(volatile I2C_t *I2Cx , Functional_State Newstate, Repeated_Start_State start);
//===========================================================================
/**================================================================
* I2C_Generate_Stop
* this function used to generate stop at the end of packets from master to slaves
* INPUTS : it takes 3 arguments :
* 1. I2Cx  				  >>> I2C_1 Or I2C_2
* 2. Newstate             >>> Functional_State its enumeration data type @ref "Functional_State"
* it returns nothing !
 */
void I2C_Generate_Stop(volatile I2C_t *I2Cx , Functional_State Newstate);
//===========================================================================
/**================================================================
* I2C_Generate_ACK
* this function used to generate Ack at the end of received byte.
* INPUTS : it takes 3 arguments :
* 1. I2Cx  				  >>> I2C_1 Or I2C_2
* 2. Newstate             >>> Functional_State its enumeration data type @ref "Functional_State"
* it returns nothing !
 */
void I2C_Generate_ACK(volatile I2C_t *I2Cx , Functional_State Newstate);
Flag_Status I2C_Get_Flag_Status(volatile I2C_t *I2Cx ,Status flag);
void I2C_Send_Address(volatile I2C_t *I2Cx , uint16_t Slave_address , I2C_Direction R_W);
void I2C_delay_ms(int x);

#endif /* SRC_I2CSTM32_H_ */
