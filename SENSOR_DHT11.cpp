#include "SENSOR_DHT11.h"

void dht11Request()
{
  DHT_SET_OUT;
  DHT_OUT_LOW; 
  __delay_cycles(20*_Freq/1000); //180000    20*_Freq/1000
  DHT_OUT_HIGH;
  // __delay_cycles(30);
  DHT_SET_IN;
}

int _checkBit(unsigned char cBit)
{
int _timeDelay = 0;
while ((DHT_IN_VALUE == cBit) & (_timeDelay<90))
  {
    _timeDelay++;
    // __delay_cycles(1);
  };
return _timeDelay;
}

void dht11Response()
{
  unsigned int bit0, bit1;
  unsigned char count;
  for(count = 0; count <= 40; count++)
  {
    bit0 = _checkBit(0);
    bit1 = _checkBit(1);
    if (bit0 < bit1) bits[count] = 1;
    else bits[count] = 0;
  }
}

unsigned char sensorDHT()
{
  dht11Request();
  dht11Response();
  dht11Temp = 0;
  dht11Hum = 0;
  dht11Checksum=0;

  unsigned char i;
  for (i = 1; i < 9; i++)
    dht11Hum = (dht11Hum<<1)|bits[i];

  for(i=17;i<25;i++)
    dht11Temp=(dht11Temp<<1)|bits[i];

  for(i=33;i<41;i++)
    dht11Checksum=(dht11Checksum<<1)|bits[i];

  if((dht11Temp!=255)&(dht11Hum!=0)&(dht11Checksum==(dht11Temp+dht11Hum))) return 1;
  else return 0;
}