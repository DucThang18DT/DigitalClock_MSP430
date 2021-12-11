/*---------------------------------------------------*
					IC_DS1307.c
-*---------------------------------------------------*
	File     				 	: 	IC_DS1307.c  - Library file
	Creat   					: 	21/03/2020
	Lastest Modified 	: 	16/05/2020
	By      					: 	Pham Duc Thang
	Require 					: 	#include "IC_DS1307.h"
												#include "I2C.h"
-*---------------------------------------------------*/

#include "I2C.h"
#include "IC_DS1307.h"
#include "Port.h"


/*----------------------------------------------------------------*
	DS1307_Init : initialization IC DS1307 - Allow IC DS1307 run
-*----------------------------------------------------------------*
	- Read value of register 0x00
	- Neglect of bit 7 then write into register 0x00
-*-------- -------------------------------------------------------*/
void DS1307_Init(){
        I2C_Init();
	char Init;
	Init = DS1307_Read_1_Byte(0x00);
	Init &= 0x7F;
	DS1307_Write_1_Byte(0x00, Init);
}


/*----------------------------------------------------------------*
	DS1307_Write_1_Byte : Write 1 byte into required Register in IC DS1307 
-*----------------------------------------------------------------*
	- Veriable "Address"   : Adddresss of Register need to be valued
	- Veriable "Data"      : Data is written to the Register
  
  - Give "Data" into "Address"
-*-------- -------------------------------------------------------*/
void DS1307_Write_1_Byte(char Address, char Data){
	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(Address);
	Data = (((Data/10)<<4)+(Data%10));
	I2C_Write(Data & 0x7F);
	I2C_Stop();
}

/*----------------------------------------------------------------*
	DS1307_Read_1_Byte : Read 1 byte at required Register in IC DS1307 
-*----------------------------------------------------------------*
	- Veriable "Address"   : Adddresss of Register need reading data
  
  - Read data at "Address"
-*-------- -------------------------------------------------------*/
char DS1307_Read_1_Byte(char Address){
	char Data;
	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(Address);
	I2C_Start();
	I2C_Write(0xD1);
	Data = I2C_Read(1);
	I2C_Stop();
	return Data;
}

/*----------------------------------------------------------------*
	DS1307_Read_Time : Read time in IC DS1307, include: Second, 
										 Minute and Hour (mode 24h) 
-*----------------------------------------------------------------*
	Parameter : *second, *minute, *hour - save time-value.
							Sec, Min, H - Save time-value which are read from DS1307
  return    : *second, *minute, *hour in Decimal
-*-------- -------------------------------------------------------*/
void DS1307_Read_Time(char* second, char* minute, char* hour){
	char Sec, Min, H;
	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(0x00);
	I2C_Start();
	I2C_Write(0xD1);
	Sec = I2C_Read(0);
	Min = I2C_Read(0);
	H   = I2C_Read(1);
	I2C_Stop();
	
	// Convert time in Ds1307 to time in Decimal
	Sec    &= 0x7F;
	*second = (Sec>>4)*10 + (Sec & 0x0F);
	Min &= 0x7F;
	*minute = (Min>>4)*10 + (Min & 0x0F);
	if (H &0x40){  //Mode 12h
		if (H & 0x20){  // PM
			H    &= 0x3F;
			*hour = (H>>4)*10 + (H & 0x0F) + 12; // +12 -> Convert to mode 24h
			}
		else {  //AM
			H    &= 0x3F;
			*hour = (H>>4)*10 + (H & 0x0F);
			}
	}
	else{ //Mode 24h
		H    &= 0x3F;
		*hour = (H>>4)*10 + (H & 0x0F);
	}
}

/*----------------------------------------------------------------*
	DS1307_Read_Date : Read date in IC DS1307, include: Day, 
										 Date, Month and Year 
										 (The last two digits of the year) 
-*----------------------------------------------------------------*
	Parameter : *day, *date, *month, *year - save date-value.
							Day, Date, Month, Year - Save date-value which are read from DS1307
  return    : *day, *date, *month, *year in Decimal
-*-------- -------------------------------------------------------*/
void DS1307_Read_Date(char* day, char* date, char* month, char* year){
	char Day, Date, Month, Year;
	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(0x03);
	I2C_Start();
	I2C_Write(0xD1);
	Day    = I2C_Read(0);
	Date   = I2C_Read(0);
	Month  = I2C_Read(0);
	Year   = I2C_Read(1);
	I2C_Stop();
	
	//Convert date in Ds1307 to time in Decimal
	*day      =  Day & 0x07;
	 Date    &=  0x3F;
	*date     = (Date>>4)*10 + (Date & 0x0F);
	 Month   &=  0x1F;
	*month    = (Month>>4)*10 + (Month & 0x0F);
	*year     = ((Year>>4)*10 + (Year & 0x0F)) % 100;	// The last two digits of the year
}

/*----------------------------------------------------------------*
	DS1307_Write_Time : Write time into IC DS1307, include: second,  
										  minute and hour
-*----------------------------------------------------------------*
	Parameter : second, minute, hour - save time-value that should be 
							recorded into DS1307
-*-------- -------------------------------------------------------*/
void DS1307_Write_Time(char second, char minute, char hour){
	// Convert time in Decimal to time in DS1307
	second = (second%10) + ((second/10)<<4);
	minute = (minute%10) + ((minute/10)<<4);
	hour   = (hour  %10) + ((hour  /10)<<4);
	
	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(0x00);
	I2C_Write(second & 0x7F);
	I2C_Write(minute & 0x7F);
	I2C_Write(hour   & 0x7f);
	I2C_Stop();
}

/*----------------------------------------------------------------*
	DS1307_Read_Date : Write date into IC DS1307, include: Day, 
										 Date, Month and Year 
-*----------------------------------------------------------------*
	Parameter : day, date, month, year - save date-value.
							Day, Date, Month, Year - Save date-value that should be 
							recorded into DS1307
-*-------- -------------------------------------------------------*/
void DS1307_Write_Date(unsigned char day ,unsigned char date ,unsigned char month ,unsigned char year){
	// Convert date in Decimal to time in DS1307
	date 	  = (date  % 10) + ((date  /10) <<4);
	month 	= (month % 10) + ((month /10) <<4);
	year	  = (year  % 10) + ((year  /10) <<4);
	
	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(0x03);
	I2C_Write(day);
	I2C_Write(date);
	I2C_Write(month);
	I2C_Write(year);
	I2C_Stop;
}

/*---------------------------------------------------*
-*---------------- End File -------------------------*
-*---------------------------------------------------*/