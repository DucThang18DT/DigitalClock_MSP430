#ifndef _DHT11_MSP430G2553_LIB_H_
#define _DHT11_MSP430G2553_LIB_H_

#include "msp430g2553.h"
#include "PORT.h"

//BIEN DHT11:
static unsigned char nhietdo, doam;
//==============================================================================
//CAC CHUONG TRINH GIAO TIEP DHT11:
//thu vien DHT11
static unsigned char dht_get(unsigned char *tem, unsigned char *humi)
{
  
  unsigned char buffer[5]={0,0,0,0,0};
  unsigned char i,ii;
  DHT_DIR = 1;//2.4 ra
  DHT_OUT=1;
   __delay_cycles(60);
  DHT_OUT=0;
  __delay_cycles(25000);
  DHT_OUT=1;
  DHT_DIR = 0;//2.4 vao
  __delay_cycles(60);//
   if(DHT_IN) return 0;
  else while(!DHT_IN); //doi Data len 1
   __delay_cycles(60);
   if(!DHT_IN) return 0;
  else while(DHT_IN); //doi Data xuong 0
  //doc du lieu
  for(i=0;i<5;i++)
  {
    for(ii=0;ii<8;ii++)
    {
      while(!DHT_IN); // doi len 1
      __delay_cycles(50);
      if(DHT_IN)
      {
        buffer[i]|=(1<<(7-ii));
        while(DHT_IN);
      }
    }
  }
 
    *humi =   buffer[0]; 
    *tem  =   buffer[2];
   return 1;
}

#endif