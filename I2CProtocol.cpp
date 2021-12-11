#include "I2CProtocol.h"

void _nop()
{
  int i=20;
  while(i--);
}


void I2C_start(void)
{
    SCL_DIR =1;
    SDA_DIR =1;
	SDA_OUT = 1; SCL_OUT = 1;
	_nop();
	SDA_OUT = 0; _nop();
	SCL_OUT = 0; _nop();
}
void I2C_stop(void)
{
      SCL_DIR =1;
      SDA_DIR =1;
      SCL_OUT = 1; SCL_OUT = 0;
	SDA_OUT = 0; _nop();
	SCL_OUT = 1; _nop();
	SDA_OUT = 1;
}
unsigned char I2C_write(unsigned char dat)
{
      SCL_DIR =1;
      SDA_DIR =1;

	unsigned char i;
	for (i=0;i<8;i++)
	{
		SDA_OUT = (dat & 0x80) ? 1:0;
		SCL_OUT=1;SCL_OUT=0;
		dat<<=1;
	}
	SCL_OUT = 1; _nop();
	SCL_OUT = 0;
	return dat;
}
unsigned char I2C_read(void)
{
	SCL_DIR =1;
	SDA_DIR =0;


	char rd_bit;
	unsigned char i, dat;
	dat = 0x00;
	for(i=0;i<8;i++) 		/* For loop read data 1 byte */
	{
		_nop();
		SCL_OUT = 1; _nop(); 	/* Set SCL */
		rd_bit = SDA_IN; 		/* Keep for check acknowledge */
		dat = dat<<1;
		dat = dat | rd_bit; /* Keep bit data in dat */
		SCL_OUT = 0; 			/* Clear SCL */
	}
	return dat;
}