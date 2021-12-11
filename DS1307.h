#ifndef _DS1307_H_
#define _DS1307_H_

#include "I2C_USCI.h"
#include "PORT.h"
#include "msp430g2553.h"
#include "LCD16x2.h"

static const unsigned char _posiX[] = {0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01};
static const unsigned char _posiY[] = {0x0A, 0x07, 0x04, 0x01, 0x05, 0x08, 0x0B};
static const unsigned char _symbolPosiY[] = {0x09, 0x06, 0x0C, 0x04, 0x07, 0x0A, 0x0F};
static const unsigned char _symbol[7] = {':', ':', ' ', ',', '/', '/', ' '};
static const unsigned int _maxVal[7] = {60, 60, 24, 8, 32, 13, 100};

/// year-sec-min-hour-day-date-month
volatile static unsigned char Temp[7];
/// sec-min-hour-day-date-month-year
volatile static unsigned char time10[7];

static void dsInit();
static void dsSetTime();
static void dsShowTime();
static void dsReadTime(); 
static void dsTimeConfig();
static unsigned char _maxDayofMonth(unsigned char month, unsigned char year);
static char* _weekdays(unsigned char day);


////////////////////////////////////////////////////

void dsInit()
{
    //Khoi tao cong giao tiep I2C Master,Slave la DS1307
    I2C_USCI_Init(DS1307_ADDRESS);
    //Cai dat chuc nang cho DS1307 xuat xung 1Hz
    I2C_USCI_Write_Byte(0x07,BIT4);
}

void dsSetTime()
{
  unsigned char _time[] = {0x50,0x59,0x23,0x04,0x05,0x06,0x07};
//  for (int i = 0x00; i < 0x07; i++)
//  {
////    _time[i] = (((_time[i]/10)<<4)+(_time[i]%10))&0x7F;
////    addr += i;
//    I2C_USCI_Write_Byte(i,_time[i] & 0x7F); // _time[i] & 0x7F
////     __delay_cycles(2);
//  }
  I2C_USCI_Write_Byte(0x00,_time[0]);
  I2C_USCI_Write_Byte(0x01,_time[1]); //
  I2C_USCI_Write_Byte(0x02,_time[2]); //
  I2C_USCI_Write_Byte(0x03,_time[3]); //
  I2C_USCI_Write_Byte(0x04,_time[4]); //
  I2C_USCI_Write_Byte(0x05,_time[5]); //
  I2C_USCI_Write_Byte(0x06,_time[6]);
}

void dsReadTime()
{
    for (int i = 0; i< 7; i++)
        Temp[i] = I2C_USCI_Read_Byte(i);
    for (int i = 1; i <= 7; i++)
        time10[i-1] = ((Temp[i%7] & 0x7F)>>4)*10+(Temp[i%7]&0x0F);
}

void dsShowTime()
{
    dsReadTime();
    for (int i = 0; i < 7; i++)
    {
      LCD_goto(_posiX[i], _posiY[i]);
      if (i != 3){
        if (i == 6) 
        {
          LCD_showALetter('2');
          LCD_showALetter('0');
        }
        LCD_showALetter(time10[i]/10 + 48);
        LCD_showALetter(time10[i]%10 + 48);
      }
      else{
          char *day = _weekdays(time10[3]);
          LCD_showALetter(day[0]);
          LCD_showALetter(day[1]);
          LCD_showALetter(day[2]);
      }
      LCD_goto(_posiX[i], _symbolPosiY[i]);
      LCD_showALetter(_symbol[i]);
    }
}

void dsTimeConfig()
{
    while (SET_BUT == 0);
    __delay_cycles(100);
    LCD_clear();

    for (int i = 6; i >= 0; i--)
    {
        while (SET_BUT)
        {
            __delay_cycles(100);
            LCD_goto(_posiX[i], _symbolPosiY[i]);
            LCD_showALetter(_symbol[i]);
            LCD_goto(_posiX[i], _posiY[i]);
            if (i != 3){
                if (i == 6) 
                {
                LCD_showALetter('2');
                LCD_showALetter('0');
                }
                LCD_showALetter(time10[i]/10 + 48);
                LCD_showALetter(time10[i]%10 + 48);
            }
            else{
                if (Temp[3] == 0) Temp[3] = 1;
                char *day = _weekdays(time10[3]);
                LCD_showALetter(day[0]);
                LCD_showALetter(day[1]);
                LCD_showALetter(day[2]);
            }
            if (UP_BUT == 0)
            {
                time10[i] = ++time10[i] % _maxVal[i];
                if (i == 4)
                    time10[4] %= _maxDayofMonth(time10[5], time10[6]);
                if ((i >= 3) && (i < 6) && (!time10[i])) time10[i] = 1;
            }
            if (DOWN_BUT == 0)
            {
                if (i == 4 && (time10[i] == 1)) time10[i] = _maxDayofMonth(time10[5], time10[6]) - 1;
                else if ((((i < 3) || (i==6)) && (!time10[i])) || ((i >= 3) && (i < 6) && (time10[i] == 1)))
                    time10[i] = _maxVal[i]-1;
                else --time10[i];
            }
            __delay_cycles(50000);
        }
        __delay_cycles(200000);
    }
    for (int i = 0x00; i < 0x07; i++)
    {
        time10[i] = (((time10[i]/10)<<4)+(time10[i]%10));
        I2C_USCI_Write_Byte(i, time10[i] &0x7F); 
        __delay_cycles(2);
    }
    __delay_cycles(200);
    dsReadTime();
}

unsigned char _maxDayofMonth(unsigned char month, unsigned char year)
{
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 32;
    case 2:
        if ((year + 2000) % 4 == 0) return 30;
        else
            return 29;
    default:
        return 31;
    }
}

char* _weekdays(unsigned char day)
{
    switch (day)
    {
    case 1:
        return "MON";
    case 2:
        return "TUE";
    case 3:
        return "WED";
    case 4:
        return "THU";
    case 5:
        return "FRI";
    case 6:
        return "SAT";
    case 7:
        return "SUN";
    default:
        return "SUN";
    }
}

#endif