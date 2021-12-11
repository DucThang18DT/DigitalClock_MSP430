#ifndef _SENSOR_DHT11_
#define _SENSOR_DHT11_

#include "msp430.h"
#include "PORT.h"

/// Bit sequence received from DHT11
static unsigned char bits[41];

/// parameters that store values: temperature, humidity, check sum.
static unsigned char dht11Temp, dht11Hum, dht11Checksum;

/// Send request to DHT11
static void dht11Request();

/// check received bit from DHT11
static int _checkBit(unsigned char cBit);

/// receive data from DHT11
static void dht11Response();

/// DHT11 process
unsigned char sensorDHT();

#endif