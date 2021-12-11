#include "RTC1307.h"

unsigned char _DS1307_read(unsigned char addr)
{
	unsigned int temp,ret;
	I2C_start(); 		/* Start i2c bus */
	I2C_write(0xD0); 	/* Connect to DS1307 */
	I2C_write(addr); 	/* Request RAM address on DS1307 */
	I2C_start(); 		/* Start i2c bus */
	I2C_write(0XD1); 	/* Connect to DS1307 for Read */
	ret = I2C_read(); 	/* Receive data */
	I2C_stop();
	//**********************************************************
	temp = ret; 							/*BCD to HEX*/
	 ret = (((ret/16)*10)+ (temp & 0x0f)); 	/*for Led 7seg*/
	//**********************************************************
	return ret;
}

void _DS1307_Write(unsigned char addr,unsigned char dat)
{
	unsigned int temp;
	//********************************************** 
	temp = dat ; 						/*HEX to BCD*/
	 dat = (((dat/10)*16)|(temp %10)); 	/*for Led 7seg*/
	//**********************************************
	I2C_start(); 		/* Start i2c bus */
	I2C_write(0XD0); 	/* Connect to DS1307 */
	I2C_write(addr); 	/* Request RAM address on DS1307 */
	I2C_write(dat); 	/* Connect to DS1307 for Read */
	I2C_stop();
}

void read_DS1307()
{
	sec   = _DS1307_read(SEC);
	min   = _DS1307_read(MIN);
	hour  = _DS1307_read(HOUR);
	day   = _DS1307_read(DAY);
	date  = _DS1307_read(DATE);
	month = _DS1307_read(MONTH);
	year  = _DS1307_read(YEAR);
}

void write_DS1307()
{
	_DS1307_Write(SEC,sec);
	_DS1307_Write(MIN,min);
	_DS1307_Write(HOUR,hour);
	_DS1307_Write(DAY,day);
	_DS1307_Write(DATE,date);
	_DS1307_Write(MONTH,month);
	_DS1307_Write(YEAR,year); 
}
//********************************************************************
void delay(unsigned int time)
{ 
	while(time--); 
}