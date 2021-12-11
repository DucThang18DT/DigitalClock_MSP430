/*
 * 
 * Engineer: Bryce Feigum (bafeigum at gmail)
 * Date: December 22, 2012
 *
 * Version: 1.0 - Initial Release
 * Version: 1.1 - Added GNUv2 License
 *
 * Copyright (C) 2013  Bryce Feigum
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * Project:  DHT11_LIB
 * File:	DHT11_LIB.h
 */
#define DHT11_H_


#include "msp430.h"

#define DHT1X_DIR	P2DIR
#define DHT1X_IN	P2IN
#define DHT1X_OUT	P2OUT
#define DHT1X_BIT	BIT5

//=================================================
//Khong thay doi ke tu dong nay
//=================================================
#define SETDHT_OUT 	DHT1X_DIR |= DHT1X_BIT
#define SETDHT_IN 	DHT1X_DIR &= ~DHT1X_BIT
#define OUTDHT_1 	DHT1X_OUT |= DHT1X_BIT
#define OUTDHT_0 	DHT1X_OUT &= ~DHT1X_BIT
#define INDHT 		((P2IN&BIT5)==DHT1X_BIT)


static unsigned char bit[41];//mang luu gia tri chuoi 40 bit nhan duoc tu DHT11 (+1 bit ket thuc)


//biendanh cho cam bien nhiet do do am
static unsigned char dht1x_temp, dht1x_rh, dht1x_checksum;
//int dht1x_temp_dec, dht1x_rh_dec;//khong can dung den cac bien nay

//=====================================//
//=================DHT-11==============//
//=====================================//

//------------------------Request (Gui yeu cau cho DHT11)
static void dht1x_rq(void)
{
  SETDHT_OUT;
  OUTDHT_0;
  __delay_cycles(180000);
  OUTDHT_1;
 //__delay_cycles(54);
  SETDHT_IN;
}

//------------------------Kiem tra bit
static int checkbit(unsigned char tbit)
{
int tdelay=0;
while ((INDHT==tbit)&(tdelay<90))
  {
    tdelay++;
    //__delay_cycles(1);
  };
return tdelay;
}

//------------------------Response (Nhan du lieu tu DHT11)
static void dht1x_rp(void)
{

  unsigned int a, b;
  unsigned char idht;
  for(idht=0;idht<41;idht++)
  {
    a=checkbit(0);
    b=checkbit(1);
    if(a<b) bit[idht]=1;
      else bit[idht]=0;
  }
}
//------------------------Ham lay gia tri cua DTH11
static unsigned char dht1x(void)
{
  dht1x_rq();
  dht1x_rp();
  dht1x_temp=0;
  dht1x_rh=0;
//Dong sau danh cho DHT22
//  dht1x_temp_dec=0;
//  dht1x_rh_dec=0;
  dht1x_checksum=0;
  unsigned char i;
  for(i=1;i<9;i++)
    dht1x_rh=(dht1x_rh<<1)|bit[i];
//Dong sau danh cho DHT22
//  for(i=9;i<17;i++)
//    dht1x_rh_dec=(dht1x_rh_dec<<1)|bit[i];
  for(i=17;i<25;i++)
    dht1x_temp=(dht1x_temp << 1) | bit[i];
//Dong sau danh cho DHT22
//  for(i=25;i<33;i++)
//    dht1x_temp_dec=(dht1x_temp_dec<<1)|bit[i];
  for(i=33;i<41;i++)
    dht1x_checksum=(dht1x_checksum<<1)|bit[i];
  if((dht1x_temp!=255)&(dht1x_rh!=0)&(dht1x_checksum==(dht1x_temp+dht1x_rh))) return 1;
  else return 0;
}