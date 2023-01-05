/*
 * I2CSTM32.c
 *
 *  Created on: Dec 30, 2022
 *      Author: OMAR
 */

#include "I2CSTM32.h"


I2C_config gI2C_structs[2];

#define I2C1_INDEX                        0U
#define I2C2_INDEX                        1U

static void I2C_GPIO_Init(volatile I2C_t *I2Cx)
{
	RCC_GPIOB_CLOCK_EN();
	if(I2Cx==I2C_1)
	{
		/*PB6 I2C1_SCL     PB7 I2C1_SDA*/
		GPIO_Init_Output_Pin(GPIOB,GPIO_PIN6,OUTPUT_ALT_OPEN_DRAIN_10MHZ);
		GPIO_Init_Output_Pin(GPIOB,GPIO_PIN7,OUTPUT_ALT_OPEN_DRAIN_10MHZ);
	}
	else if(I2Cx==I2C_2)
	{
		/*PB10 I2C2_SCL    PB11 I2C2_SDA*/
		GPIO_Init_Output_Pin(GPIOB,GPIO_PIN10,OUTPUT_ALT_OPEN_DRAIN_10MHZ);
		GPIO_Init_Output_Pin(GPIOB,GPIO_PIN11,OUTPUT_ALT_OPEN_DRAIN_10MHZ);
	}
}

void I2C_init(volatile I2C_t *I2Cx ,I2C_config *I2C_init_struct)
{

	/*______________________________RCC clock peripheral  Enable________________________________*/
	if(I2Cx==I2C_1)
	{
		gI2C_structs[I2C1_INDEX] = *I2C_init_struct;
		RCC_I2C1_CLOCK_EN();
	}
	else if(I2Cx==I2C_2)
	{
		gI2C_structs[I2C2_INDEX] = *I2C_init_struct;
		RCC_I2C2_CLOCK_EN();
	}


	if(I2C_init_struct->I2CDeviceMode == I2C_I2C_MODE)
	{

		/*____________________________timing_______________________________*/
		uint32_t tempReg=I2Cx->I2C_CR2;
		//Frequency set (FREQ bits <bit5:bit0> in I2C_CR2 register )
		tempReg |= (FAPB1_CLK_SPEED & 0x3fU);
		I2Cx->I2C_CR2 = tempReg;
		// disable I2C first
		I2Cx->I2C_CR1 &= ~(I2C_CR1_PE);

		tempReg = 0x00;
		//BUS SPEED
		if(I2C_init_struct->I2CBusSpeed == I2C_CLOCK_SM_50K || I2C_init_struct->I2CBusSpeed == I2C_CLOCK_SM_100K)
		{
			/*
			 * 	Configure the clock control registers
	(CCR bits <bit11 : bit0> in I2C_CCR register)
	CCR = (FAPB1/2FI2C) = (tH/tPCLK1) = (tL/tPCLK1)
	where :
	tPCLK1 = (1/FAPB1) ,
	tH = On_interval of FI2C,
	tL = Off_interval of FI2C


			 *******************
			 ******************  Bit 15 F/S: I2C master mode selection
							0: Sm mode I2C
							1: Fm mode I2C
			 *******************
			 */

			tempReg = (((FAPB1_CLK_SPEED * 1000000)/(2 * I2C_init_struct->I2CBusSpeed)) & 0xfff);
			I2Cx->I2C_CCR = tempReg;
			I2Cx->I2C_CCR &= ~(1U<<15);
			/*
	 • Configure the rise time register
	( TRISE bits <bit5 : bit0> in I2C_TRISE register)
	TRISE = (maximum allowed SCL rise time / tPCLK1 +1)
	where :
	in standard mode (sm) : maximum allowed SCL rise time = 1000ns
	for instance : if FAPB1 = 8MHZ (tPCLK1 = 125ns),
	 the TRISE = 1000ns/125ns+1 =8+1 = 9
			 *
			 */
			tempReg = 0x00 ;
			tempReg |= ( (FAPB1_CLK_SPEED  + 1) & 0x3fU );
			I2Cx->I2C_TRISE = tempReg;
		}
		else if(I2C_init_struct->I2CBusSpeed == I2C_CLOCK_FM_200K || I2C_init_struct->I2CBusSpeed == I2C_CLOCK_FM_400K)
		{
			//Not Supported Yet
		}

		/*____________________________CR1 configurations_______________________________*/

		tempReg = I2Cx->I2C_CR1 ;
		tempReg |= I2C_init_struct->I2CAckEnable;
		tempReg |= I2C_init_struct->General_Call_Address_Detection;
		tempReg |= I2C_init_struct->ClockStretchingEnable;
		tempReg |= I2C_init_struct->I2CDeviceMode;

		I2Cx->I2C_CR1 = tempReg;
		/*____________________________OAR2 configurations_______________________________*/

		tempReg = 0x00 ;
		if(I2C_init_struct->I2CDeviceAddress.Dual ==1)
		{
			tempReg = I2C_OAR2_ENDUAL;
			tempReg |= (I2C_init_struct->I2CDeviceAddress.Secondary_address << I2C_OAR2_ENDUAL);
			I2Cx->I2C_OAR2 = tempReg;
		}
		/*____________________________OAR1 configurations_______________________________*/
		tempReg = 0x00 ;

		tempReg|= (I2C_init_struct->I2CDeviceAddress.Primary_address << 1);//bits 1~7
		tempReg|=  I2C_init_struct->I2CDeviceAddress.Addressing_mode;
		//R/W !?

		I2Cx->I2C_OAR1 = tempReg;
		/*____________________________pointer to ISR in case of Slave_______________________________*/
		if(I2C_init_struct->ptrToSlaveEventISR != NULL)
		{
			//that enables the Slave interrupts
			I2Cx->I2C_CR2 |= I2C_CR2_ITBUFEN;
			I2Cx->I2C_CR2 |= I2C_CR2_ITERREN;
			I2Cx->I2C_CR2 |= I2C_CR2_ITEVTEN;

			//NVIC
			if(I2Cx == I2C_1)
			{
				I2C1_EV_INTERRUPT_EN();
				I2C1_ER_INTERRUPT_EN();
			}
			else if (I2Cx == I2C_2)
			{
				I2C2_EV_INTERRUPT_EN();
				I2C2_ER_INTERRUPT_EN();
			}
		}
		/*___________________________________init GPIOs_________________________________*/
		I2C_GPIO_Init(I2Cx);
		/*__________________________________Enable I2C peripheral_______________________*/
		I2Cx->I2C_CR1 |= (I2C_CR1_PE);
	}
	// SMBus ******************************Not Supported*********************************************************
	else
	{
		//Not Supported
	}
}


void I2C_Dinit(volatile I2C_t *I2Cx)
{
	if(I2Cx==I2C_1)
	{
		RCC_I2C1_RESET();
		I2C1_EV_INTERRUPT_DIS();
		I2C1_ER_INTERRUPT_DIS();
	}
	else if(I2Cx==I2C_2)
	{
		RCC_I2C2_RESET();
		I2C2_EV_INTERRUPT_DIS();
		I2C2_ER_INTERRUPT_DIS();
	}

}

Flag_Status I2C_Get_Flag_Status(volatile I2C_t *I2Cx ,Status flag)
{
	Flag_Status bitstatus = RESET ;
	volatile uint32_t dummy ;
	switch(flag)
	{
	case  I2C_FLAG_BUSY :
	{
		if(I2Cx->I2C_SR2 & (I2C_SR2_BUSY))
			bitstatus = SET;
		else
			bitstatus = RESET;
		break;
	}
	case  EV5 :
	{
		if(I2Cx->I2C_SR1 & (I2C_SR1_SB))
			bitstatus = SET;
		else
			bitstatus = RESET;
		break;
	}

	case  EV6 :
	{
		if(I2Cx->I2C_SR1 & (I2C_SR1_ADDR))
			bitstatus = SET;
		else
			bitstatus = RESET;
		// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
		dummy = I2Cx->I2C_SR2;// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
		break;
	}

	case  EV7:
	case  EV7_1:
	{
		if(I2Cx->I2C_SR1 & (I2C_SR1_RXNE))
			bitstatus = SET;
		else
			bitstatus = RESET;
		break;
	}

	case  MASTER_BYTE_TRANSMITTING :
	{
		if (((uint32_t)(((I2Cx->I2C_SR2)<<16) | I2Cx->I2C_SR1) & (MASTER_BYTE_TRANSMITTING)) ==MASTER_BYTE_TRANSMITTING)
			bitstatus = SET;
		else
			bitstatus = RESET;
		break;
	}
	case  EV8 :
	case  EV8_1 :
	{
		if(I2Cx->I2C_SR1 & (I2C_SR1_TXE))
			bitstatus = SET;
		else
			bitstatus = RESET;
		break;
	}
	case  EV8_2 :
	{
		if( (I2Cx->I2C_SR1 & (I2C_SR1_TXE)) & (I2Cx->I2C_SR1 & (I2C_SR1_BTF)))
			bitstatus = SET;
		else
			bitstatus = RESET;
		break;
	}

	}

	return bitstatus ;
}
void I2C_Generate_Start(volatile I2C_t *I2Cx , Functional_State Newstate, Repeated_Start_State start)
{


	/*
	 * Bit 1 BUSY: Bus busy
					0: No communication on the bus
					1: Communication ongoing on the bus
					– Set by hardware on detection of SDA or SCL low
					– cleared by hardware on detection of a Stop condition.
					It indicates a communication in progress on the bus. This information is still updated when
					the interface is disabled (PE=0).		 *
	 * */

	if(start != REAPEATED_START)
		while(I2C_Get_Flag_Status(I2Cx,I2C_FLAG_BUSY));


	/*
	 * Bit 8 START: Start generation
		This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
		In Master Mode:
		0: No Start generation
		1: Repeated start generation
		In Slave mode:
		0: No Start generation
		1: Start generation when the bus is free
	 * */

	if(Newstate == ENABLE)
	{
		I2Cx->I2C_CR1 |= I2C_CR1_START;
	}
	else if(Newstate == DISABLE)
	{
		I2Cx->I2C_CR1 &= ~(I2C_CR1_START);
	}
}

void I2C_Generate_Stop(volatile I2C_t *I2Cx , Functional_State Newstate)
{
	if(Newstate == ENABLE)
	{
		I2Cx->I2C_CR1 |= I2C_CR1_STOP;
	}
	else if(Newstate == DISABLE)
	{
		I2Cx->I2C_CR1 &= ~(I2C_CR1_STOP);
	}
}


void I2C_Generate_ACK(volatile I2C_t *I2Cx , Functional_State Newstate)
{
	if(Newstate == ENABLE)
	{
		I2Cx->I2C_CR1 |= I2C_CR1_ACK;
	}
	else if(Newstate == DISABLE)
	{
		I2Cx->I2C_CR1 &= ~(I2C_CR1_ACK);
	}
}
void I2C_Send_Address(volatile I2C_t *I2Cx , uint16_t Slave_address , I2C_Direction R_W)
{
	uint32_t tempDR=0x00;
	if(I2Cx == I2C_1)
	{
		if(gI2C_structs[I2C1_INDEX].I2CDeviceAddress.Addressing_mode ==I2C_7bit_Address_Mode)
		{

			tempDR = ( (Slave_address & 0xf0) | ((Slave_address & 0x0f)<<1) );

			if(R_W==I2C_WRITE)
				tempDR &= ~(1U<<0);
			else if(R_W==I2C_READ)
				tempDR |= (1U<<0);

			I2Cx->I2C_DR = tempDR;
		}

		else if(gI2C_structs[I2C1_INDEX].I2CDeviceAddress.Addressing_mode ==I2C_10bit_Address_Mode)
		{
			//not supported Yet
		}
	}
	else if (I2Cx == I2C_2)
	{
		if(gI2C_structs[I2C2_INDEX].I2CDeviceAddress.Addressing_mode ==I2C_7bit_Address_Mode)
		{
			tempDR |= (Slave_address <<1);
			if(R_W==I2C_WRITE)
				tempDR &= ~(0x01);
			else if(R_W==I2C_READ)
				tempDR |= (0x01);

			I2Cx->I2C_DR = tempDR;
		}

		else if(gI2C_structs[I2C2_INDEX].I2CDeviceAddress.Addressing_mode ==I2C_10bit_Address_Mode)
		{
			//not supported Yet
		}
	}

}
void I2C_delay_ms(int x)
{
	int i,j;
	for(i=0;i<x;i++){
	for(j=0;j<530;j++){}
	}
}

void I2C_Master_Tx(volatile I2C_t *I2Cx , uint16_t Slave_address , uint8_t *data_buffer, uint32_t datalen,Stop_State stop,Repeated_Start_State start)
{
	uint32_t i ;
													//1 . Send START bit
	I2C_Generate_Start(I2Cx,ENABLE,start);

	/*wait for EV5 .......
	 * EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	 *
	 * Bit 0
	 *  SB: Start bit (Master mode)
		0: No Start condition
        1: Start condition generated.
		– Set when a Start condition generated.
		– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		hardware when PE=0
	 */
													//2 . Wait EV5
	while(!(I2C_Get_Flag_Status(I2Cx,EV5)));
	//Write the Address of the slave :
													//3 . Send Slave Address
	I2C_Send_Address(I2Cx, Slave_address,I2C_WRITE);
	/*wait EV6
		Bit 1
		ADDR: Address sent (master mode)/matched (slave mode)
		This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
		when PE=0.
		Address matched (Slave)
		0: Address mismatched or not received.
		1: Received address matched.
		– Set by hardware as soon as the received slave address matched with the OAR registers
		content or a general call or a SMBus Device Default Address or SMBus Host or SMBus Alert
		is recognized. (when enabled depending on configuration).
		Note: In slave mode, it is recommended to perform the complete clearing sequence (READ
		SR1 then READ SR2) after ADDR is set. Refer to Figure 272
	 */
													//4 . Wait EV6
	while(!(I2C_Get_Flag_Status(I2Cx,EV6)));
													//5 . TRA , BUSY , MSL , TXE flags
	while(!(I2C_Get_Flag_Status(I2Cx,MASTER_BYTE_TRANSMITTING)));
													//6 . Write Data to send
	for(i=0;i<datalen;i++)
	{
		I2Cx->I2C_DR=data_buffer[i];
		while(!(I2C_Get_Flag_Status(I2Cx,EV8)));
		I2C_delay_ms(5);
	}
												 //7 . wait EV8_2
	/*
	 *
	 * Bit 2 BTF: Byte transfer finished
		0: Data byte transfer not done
		1: Data byte transfer succeeded
		– Set by hardware when NOSTRETCH=0 and:
		– In reception when a new byte is received (including ACK pulse) and DR has not been read
		yet (RxNE=1).
		– In transmission when a new byte should be sent and DR has not been written yet (TxE=1).
		– Cleared by software reading SR1 followed by either a read or write in the DR register or by
		hardware after a start or a stop condition in transmission or when PE=0.
		Note: The BTF bit is not set after a NACK reception
		The BTF bit is not set if next byte to be transmitted is the PEC (TRA=1 in I2C_SR2
		register and PEC=1 in I2C_CR1 register)
	 *
	 * */
	//while(!(I2C_Get_Flag_Status(I2Cx,EV8_2)));
											//8 . Send STOP
		/*
		 * Bit 9 STOP: Stop generation
		The bit is set and cleared by software, cleared by hardware when a Stop condition is
		detected, set by hardware when a timeout error is detected.
		In Master Mode:
		0: No Stop generation.
		1: Stop generation after the current byte transfer or after the current Start condition is sent.
		In Slave mode:
		0: No Stop generation.
		1: Release the SCL and SDA lines after the current byte transfer.
		 * */
	if(stop == WITH_STOP)
		I2C_Generate_Stop(I2Cx,ENABLE);

}



void I2C_Master_Rx(volatile I2C_t *I2Cx , uint16_t Slave_address , uint8_t *data_buffer, uint32_t datalen,Stop_State stop,Repeated_Start_State start)
{
		uint32_t i ;
												//1 . Send START bit
		I2C_Generate_Start(I2Cx,ENABLE,start);
		/*wait for EV5 .......
			 * EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
			 *
			 * Bit 0
			 *  SB: Start bit (Master mode)
				0: No Start condition
		        1: Start condition generated.
				– Set when a Start condition generated.
				– Cleared by software by reading the SR1 register followed by writing the DR register, or by
				hardware when PE=0
			 */
													//2 . Wait EV5
			while(!(I2C_Get_Flag_Status(I2Cx,EV5)));
													//3 . Send Slave Address
			I2C_Send_Address(I2Cx, Slave_address,I2C_READ);
			/*wait EV6
			Bit 1
			ADDR: Address sent (master mode)/matched (slave mode)
			This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
			when PE=0.
			Address matched (Slave)
			0: Address mismatched or not received.
			1: Received address matched.
			– Set by hardware as soon as the received slave address matched with the OAR registers
			content or a general call or a SMBus Device Default Address or SMBus Host or SMBus Alert
			is recognized. (when enabled depending on configuration).
			Note: In slave mode, it is recommended to perform the complete clearing sequence (READ
			SR1 then READ SR2) after ADDR is set. Refer to Figure 272
			*/
													//4 . Wait EV6
			while(!(I2C_Get_Flag_Status(I2Cx,EV6)));
													//5 . Read received DRs , 6 . wait EV7

			I2C_Generate_ACK(I2Cx,ENABLE);
			if(datalen)
			{
				for(i=0;i<datalen;i++)
				{
				data_buffer[i] = I2Cx->I2C_DR;
				while(!(I2C_Get_Flag_Status(I2Cx,EV7)));

				}
			}
													//7 . wait EV7_1
			while(!(I2C_Get_Flag_Status(I2Cx,EV7_1)));

													//8 . Send ACK = 0, STOP =1
			/*
					 * Bit 10 ACK: Acknowledge enable
					This bit is set and cleared by software and cleared by hardware when PE=0.
					0: No acknowledge returned
					1: Acknowledge returned after a byte is received (matched address or data)
					 * Bit 9 STOP: Stop generation
					The bit is set and cleared by software, cleared by hardware when a Stop condition is
					detected, set by hardware when a timeout error is detected.
					In Master Mode:
					0: No Stop generation.
					1: Stop generation after the current byte transfer or after the current Start condition is sent.
					In Slave mode:
					0: No Stop generation.
					1: Release the SCL and SDA lines after the current byte transfer.
					 * */
				I2C_Generate_ACK(I2Cx,DISABLE);
				if(stop == WITH_STOP)
					I2C_Generate_Stop(I2Cx,ENABLE);


				if(I2Cx==I2C_1 && gI2C_structs[I2C1_INDEX].I2CAckEnable == I2C_ACK_EN)
				{
					I2C_Generate_ACK(I2Cx,ENABLE);
				}
				else if(I2Cx==I2C_2 && gI2C_structs[I2C2_INDEX].I2CAckEnable == I2C_ACK_EN)
				{
					I2C_Generate_ACK(I2Cx,ENABLE);
				}

}



void I2C1_EV_IRQHandler(void)
{

}

void I2C2_EV_IRQHandler(void)
{

}
