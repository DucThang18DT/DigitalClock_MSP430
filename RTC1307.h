#ifndef _RTC1307_H_
#define _RTC1307_H_


// #include "string.h"
// #include "msp430g2452.h"
// #include <intrinsics.h>
#include "PORT.h"
#include "I2CProtocol.h"


static char sec,hour,min,day,date,month,year,year_20,set;
// static char *s[]={"MON","TUE","WED","THU","FRI","SAT","SUN"};
// char led7_data[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90 };
static char chop=0,dem=0;

static void _nop();
unsigned char _DS1307_read(unsigned char addr);
static void _DS1307_Write(unsigned char addr,unsigned char dat);
void read_DS1307();
void write_DS1307();
static void delay(unsigned int time);






// //******************************************************************
// // LCD

// void wait(void) 
// {    
//   int i;
//   for(i=0;i<1000;i++)
//     {
//       }
//   EN=0;// Dua xung cao xuong thap de chot 
// } 
// void LCDcontrol(char x) 
// {         
//   EN=1;// Dua chan cho fep len cao 
//   RS=0;// Chon thanh ghi lenh 
//   LCDdata=x;// Gia tri x 
//   EN=0;// Xung cao xuong thap 
//   wait();// Doi LCD san sang   
// }

// void LCDinit(void) 
// { 
//   LCDcontrol(0x30);//Che do 8 bit. 
//   LCDcontrol(0x30); 
//   LCDcontrol(0x38);// 2 dong va ma tran 5x7 
//   LCDcontrol(0x0C);// Bat con tro 
//   LCDcontrol(0x06);// Tang con tro xang fai 
//   LCDcontrol(0x01);// Xoa man hinh 
// }

// void LCDwrite(char c) 
// { 
//   EN=1;// Cho fep muc cao 
//   RS=1;// Ghi du lieu 
//   //RW=0;// Ghi len LCD 
//   LCDdata=c;// Gia tri C 
//   EN=0;// Xung cao xuong thap 
//   wait();// Cho     
// }

// void LCDputs(char *s,unsigned char row) 
// { 
// unsigned char len; 
// if(row==1) LCDcontrol(0x80);// Ep con tro ve dau dong 1 
// else LCDcontrol(0xC0);// Ep con tro ve dau dong 2 
//   len=strlen(s);// Lay do dai bien duoc tro boi con tro 
//   while(len!=0)// Khi do dai van con 
//   { 
//       LCDwrite(*s);// Ghi ra LCD gia tri duoc tro boi con tro 
//    s++;// Tang con tro 
//    len--;// Tru do dai 
//   } 
// }
// //******************************************************************
// void Set_Clock(void) // Kiem tra va hieu chinh gia tri cua gio,phut,giay
// {
// 	unsigned char y;
// 	y=(year%4)*100;
// //Tang
// 	if(min>59)  { min=0; }
// 	if(hour>23) { hour=0; }
// 	if(day>8) day=2;
// 	if((month==2)&&(date>29)&&(y==0)) { date=1; }
// 	else	if((month==2)&&(date>28)&&(y!=0)) { date=1; }
// 			else 	if(((month==4)||(month==6)||(month==9)||(month==11))&&(date>30)&&(y!=0)){ date=1; }
// 					else 	if(date>31) { date=1; }
// 	if(month>12)  { month=1; }
// 	if(year>99)   { year_20++; year=0; if(year_20>99){year_20=0;}  }
	
// //Giam
// 	if(min+1<1)  { min=59; }
// 	if(hour+1<1) { hour=23; }
// 	if(day<2) day=8;
// 	if((month==2)&&(date<1)&&(y==0)) { date=29; }
// 	else	if((month==2)&&(date<1)&&(y!=0)) { date=28; }
// 			else 	if(((month==4)||(month==6)||(month==9)||(month==11))&&(date<1)&&(y!=0)){ date=30; }
// 					else 	if(date<1) { date=31; }
// 	if(month<1)   { month=12; }
// 	if(year+1<1)    { year_20--; year=99; if(year_20+1<1){year_20=99;} }
	
// }
// //**********************************************************************
// //Khoi nut nhan
// void Keypad(void) // Kiem tra phim nhan.
// {
//  	if(!Ok)
// 	{
// 		set=0;
// 		Write_DS1307();	
		
// 	}

// //*********************************************************************
// 		if(!Set)
// 		{ 
// 			 set++; 
// 			if(set==7) set=0;
// 		}
// 		if(set==1)
// 		{

// 			if(!Up) { min++;delay(50000); }
// 			if(!Down) { min--; delay(50000); }
// 		}
// 		if(set==2)
// 		{ 
// 			if(!Up) 
// 			{
// 				hour=hour+1; delay(50000);
// 			}
// 			if(!Down) 
// 			{	
// 				hour=hour-1; delay(50000);
// 			}
// 		}
// 		if(set==3)
// 		{ 
// 			if(!Up) 
// 			{
// 				day=day+1; delay(50000);
// 			}
// 			if(!Down) 
// 			{	
// 				day=day-1; delay(50000);
// 			}
// 		}
// 		if(set==4)
// 		{ 
// 			if(!Up) 
// 			{
// 				date=date+1; delay(50000);
// 			}
// 			if(!Down) 
// 			{	
// 				date=date-1; delay(50000);
// 			}
// 		}
// 		if(set==5)
// 		{ 
// 			if(!Up) 
// 			{
// 				month=month+1; delay(50000);
// 			}
// 			if(!Down) 
// 			{	
// 				month=month-1; delay(50000);
// 			}
// 		}
// 		if(set==6)
// 		{ 
// 			if(!Up) 
// 			{
// 				year=year+1;delay(50000);
// 			}
// 			if(!Down) 
// 			{	
// 				year=year-1; delay(50000);
// 			}
// 		}
// Set_Clock();
// }
// //******************************************************************
// #pragma vector = TIMER0_A0_VECTOR
// //#pragma vector = TIMERA0_VECTOR

// __interrupt void TA0_ISR ( void )
// {
//   dem++;
//   if(dem==80)
//   {
//     dem=0;
//     chop=chop^1;
//   }
// }

// //******************************************************************
// void Out_1Hz(void)
// {
// 	I2C_start(); /* Start i2c bus */
// 	I2C_write(0xD0); /* Connect to DS1307 */
// 	I2C_write(0x07);   //vi tri con tro RTC
// 	I2C_write(0x10);
// 	I2C_stop();
// }
// //****************************************************************
// void hienthi(void)
// {
//   LCDputs("    ",1);
// if((set==2)&&(chop==1))
// {
// LCDwrite(32);
// LCDwrite(32);
// }
// else
// {
// LCDwrite((hour/10)+48);
// LCDwrite((hour%10)+48);

// }
// LCDwrite(58);//dau hai cham
// if((set==1)&&(chop==1))
// {
// LCDwrite(32);
// LCDwrite(32);

// }
// else
// {
// LCDwrite((min/10)+48);
// LCDwrite((min%10)+48);

// }
// LCDwrite(58);//dau hai cham
// LCDwrite((sec/10)+48);
// LCDwrite((sec%10)+48);
// if((set==3)&&(chop==1))
// {

//   LCDputs("   ",2);

// }
// else
// {
//   LCDputs(s[day-2],2);

// }
// LCDwrite(32);//hien dau cach'
// if((set==4)&&(chop==1))
// {
// LCDwrite(32);
// LCDwrite(32);

// }
// else
// {
//   LCDwrite((date/10)+48);
// LCDwrite((date%10)+48);

// }
// LCDwrite(45);//hien dau -
// if((set==5)&&(chop==1))
// {
// LCDwrite(32);
// LCDwrite(32);
// }
// else
// {
// LCDwrite((month/10)+48);
// LCDwrite((month%10)+48);

// }
// LCDwrite(45);//hien dau -
// if((set==6)&&(chop==1))
// {
// LCDwrite(32);
// LCDwrite(32);
// LCDwrite(32);
// LCDwrite(32);

// }
// else
// {
// LCDwrite((year_20/10)+48);
// LCDwrite((year_20%10)+48);
// LCDwrite((year/10)+48);
// LCDwrite((year%10)+48);

// }

// }
// //****************************************************************
// //***************************************************************

// void main( void )
// {
// 	// Stop watchdog timer to prevent time out reset
// 	WDTCTL = WDTPW + WDTHOLD;
// 	BCSCTL1 = CALBC1_1MHZ; //dinh nghia dao dong noi 1MHz
// 	DCOCTL = CALDCO_1MHZ;
// 	TACCTL0=CCIE;	// Cho phép ngat Timer_A
// 	TACCR0 = 5000;			// Cho chu ki là 5000
// 	TACTL = MC_1|ID_3 |TASSEL_2|TACLR;
//    __enable_interrupt ();

// _P2_DIRECT->_BYTE = 0xFF;
// _P2_SEL->_BIT.b6=0;
// _P2_SEL->_BIT.b7=0;
// _I2C_DIRECT->_BIT.b0 =1;
// _I2C_DIRECT->_BIT.b1 =1;
// _I2C_DIRECT->_BIT.b2 =0;
// _I2C_DIRECT->_BIT.b3 =0;
// _I2C_DIRECT->_BIT.b4 =0;
// _I2C_DIRECT->_BIT.b5 =0;
// LCDinit();
// year_20=20;
// set=0;
// Out_1Hz();

// while(1)
// {
// Keypad();
// if(set==0)
// {
// Read_DS1307();
// }
// else
// {
//  sec = DS1307_read(SEC); 
//   }
// hienthi();
//   }
// }



#endif