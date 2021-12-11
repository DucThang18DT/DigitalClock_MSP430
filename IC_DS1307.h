#ifndef _IC_DS1307_H_
#define _IC_DS1307_H_

	void DS1307_Init();
	static void DS1307_Write_1_Byte(char, char );
	static char DS1307_Read_1_Byte(char);
	void DS1307_Read_Time(char* , char* , char* );
	void DS1307_Read_Date(char* , char* , char* , char* );
	void DS1307_Write_Time(char , char , char );
	void DS1307_Write_Date(unsigned char ,unsigned char ,unsigned char ,unsigned char );
	
#endif