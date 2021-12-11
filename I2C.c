/*---------------------------------------------------*
			I2C.c
-*---------------------------------------------------*
	File     			: 	I2C.c  - Library file
	Creat   			: 	25/03/2020
	Lastest Modified 	        : 	16/05/2020
	By      			: 	Pham Duc Thang
	Require 			: 	#include "I2C.h"
                                                #include "Port.h"
-*---------------------------------------------------*/
// #include <REGX52.H>
#include "I2C.h"
#include "Port.h"
#include "msp430g2553.h"


/*----------------------------------------------------------------*
	I2c_Delay : Delay IC DS1307 for a very short period of time
-*-------- -------------------------------------------------------*/
void I2C_Delay(){
	char Count;
	for (Count = 0; Count < 10; Count++);
}

/*----------------------------------------------------------------*
	I2C_Delay_us : Delay IC DS1307 for a very short period of time
-*----------------------------------------------------------------*
	parameter : Time - time delay in micro second
-*-------- -------------------------------------------------------*/

void I2C_Delay_us(int time){
	// TMOD=0X02;
	// TH0=256-Time;
	// TR0=1;
	// while(!TF0);
	// TF0=0;
        int i = 0;
        for (i = 0; i < time; i++)
        {
          __delay_cycles(1);
        }
          
}


/*----------------------------------------------------------------*
	I2C_Delay_ms : Delay IC DS1307 for a very short period of time
-*----------------------------------------------------------------*
	parameter : Time - time delay in milli second
-*-------- -------------------------------------------------------*/
/*----------------------------------------------------------------*
void I2C_Delay_ms(unsigned int Time){
	int Count;
	TMOD=0X02;
	TH0=0x00;
	while(Time!=0)
	{
		for(Count = 0 ;Count < 4;Count++){
		TR0=1;
		while(!TF0);
		TF0=0;}
		Time--;
	}
}
-*-------- -------------------------------------------------------*/

/*----------------------------------------------------------------*
	I2C_Init : Initialization I2C communication  
						 - Allow communication I2C run
-*----------------------------------------------------------------*
	- Raise signal of SDA to High level
	- Raise signal of SCL to High level
-*-------- -------------------------------------------------------*/
void I2C_Init(){
	// I2C_SDA = 1;
	SDA_DIR = 1;
	SDA_OUT = 1;
	// I2C_SCL = 1;
        SCL_DIR = 1;
	SCL_OUT = 1;
}

/*----------------------------------------------------------------*
	I2C_Start : Give start signal to allow sending and receiving data
-*----------------------------------------------------------------*
	- Raise signal of SCL to High level
	- Fall signal of SDA to Low level
	- Fall signal of SCL to Low level
-*-------- -------------------------------------------------------*/
void I2C_Start(){
	// I2C_SCL = 0;
	SCL_OUT = 0;
	// I2C_SDA = 1;
	SDA_DIR = 1;
	SDA_OUT = 1;
	I2C_Delay_us(1);
	// I2C_SCL = 1;
	SCL_OUT = 1;
	I2C_Delay_us(1);
	// I2C_SDA = 0 ;
	SDA_OUT = 0;
	I2C_Delay_us(1);
	// I2C_SCL = 0;
	SCL_OUT = 0;
}

/*----------------------------------------------------------------*
	I2C_Stop : Give stop signal to stop I2C communication
-*----------------------------------------------------------------*
	- Fall signal of SDA to Low level
	- Raise signal of SCL to High level
	- Raise signal of SDA to High level
-*-------- -------------------------------------------------------*/
void I2C_Stop(){
	// I2C_SCL = 0;
	SCL_OUT = 0;
	I2C_Delay_us(1);
	// I2C_SDA = 0;
	SDA_DIR = 1;
	SDA_OUT = 0;
	I2C_Delay_us(1);
	// I2C_SCL = 1;
	SCL_OUT = 1;
	I2C_Delay_us(1);
	// I2C_SDA = 1;
	SDA_OUT = 1;
}

/*----------------------------------------------------------------*
	I2C_Stop : Give reStart signal to restart I2C communication
						 - Less used
-*----------------------------------------------------------------*
	- Call Stop function
	- Call Start function
-*-------- -------------------------------------------------------*/
/*
void I2C_ReStart(){
	I2C_Stop();
	I2C_Start();
}
*/

/*----------------------------------------------------------------*
	I2C_Get_Ack : Check Ack signal from Slave
-*----------------------------------------------------------------*
	- Result    : 1 - Not Ack
							: 0 - Ack
-*-------- -------------------------------------------------------*/
unsigned char I2C_Get_Ack(){
	// bit result;
	unsigned char result;
	// I2C_SDA = 1;
	SDA_DIR = 1;
	SDA_OUT = 1;
	I2C_Delay();
	// I2C_SCL = 1;
	SCL_OUT = 1;
	I2C_Delay();
	// result = I2C_SDA;
	SDA_DIR = 0;
	result = SDA_IN;
	// I2C_SCL = 0;
	SCL_OUT = 0;
	return result;
}

/*----------------------------------------------------------------*
	I2C_AK : Give Ack signal to Slave
-*-------- -------------------------------------------------------*/
void I2C_AK(){
	// I2C_SDA = 0;
	SDA_DIR = 1;
	SDA_OUT = 0;
	I2C_Delay_us(1);
	// I2C_SCL = 1;
	SCL_OUT = 1;
	I2C_Delay_us(1);
	// I2C_SCL = 0;
	SCL_OUT = 0;
	// I2C_SDA = 1;
	SDA_OUT = 1;
}

/*----------------------------------------------------------------*
	I2C_NAK : Give Not Ack signal to Slave
-*-------- -------------------------------------------------------*/
void I2C_NAK(){
	// I2C_SDA = 1;
	SDA_DIR = 1;
	SDA_OUT = 1;
	I2C_Delay_us(1);
	// I2C_SCL = 1;
	SCL_OUT = 1;
	I2C_Delay_us(1);
	// I2C_SCL = 0;
	SCL_OUT = 0;
	// I2C_SDA = 1 ;
	SDA_OUT = 1;
}

/*----------------------------------------------------------------*
	I2C_Write  : Write 1 byte data from Master to Slave
-*----------------------------------------------------------------*
	Parameter	 : Data - data needed give into Slave
							 Count - count bit of data
	Return     : 1 - Not Ack
							 0 - Ack
-*-------- -------------------------------------------------------*/
unsigned char I2C_Write(char Data){
	char Count;
        SDA_DIR = 1;
	for (Count =0; Count < 8; Count++){
		// I2C_SDA = (Data & 0x80);
		SDA_OUT = (Data & 0x80);
		// I2C_SCL = 1;
		SCL_OUT = 1;
		// I2C_SCL = 0;
		SCL_OUT = 0;
		Data <<=1;
	}
	return I2C_Get_Ack();
}

/*----------------------------------------------------------------*
	I2C_Read  : Read 1 byte data from Slave to Master
-*----------------------------------------------------------------*
	Parameter : AK_OR_NAK - 0 : continue giving data
													1 : stop giving data
							Data - data from Slave
							Count_Bit - count bit of byte data
	Return    : 1 byte data from Slave
-*-------- -------------------------------------------------------*/
unsigned char I2C_Read(char AK_OR_NAK){
	unsigned char Data = 0, Count_Bit;
	for (Count_Bit = 0;Count_Bit < 8; Count_Bit++){
		Data    = Data <<1;
		// I2C_SDA = 1 ;
		SDA_DIR = 1;
		SDA_OUT = 1;
		// I2C_SCL = 1;
		SCL_OUT = 1;
		// Data   |= I2C_SDA;
		SDA_DIR = 0;
		Data |= SDA_IN;
		// I2C_SCL = 0;
		SCL_OUT = 0;
	}
	if (AK_OR_NAK == 0) I2C_AK();
	else I2C_NAK();
	return Data;
}

/*---------------------------------------------------*
-*---------------- End File -------------------------*
-*---------------------------------------------------*/