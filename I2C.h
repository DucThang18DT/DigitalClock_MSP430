#ifndef _I2C_H_
#define _I2C_H_
	

	void I2C_Delay();
	void I2C_Delay_us(int);
	//void I2C_Delay_ms(unsigned int);
	void I2C_Init();
	void I2C_Start();
	void I2C_Stop();
	//void I2C_ReStart();
	unsigned char I2C_Get_Ack();
	void I2C_AK();
	void I2C_NAK();
	unsigned char I2C_Write(char);
	unsigned char I2C_Read(char);
	

#endif