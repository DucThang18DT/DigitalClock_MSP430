#ifndef _I2CPROTOCOL_H_
#define _I2CPROTOCOL_H_

// #define delay_1 nop() //generates 1 microsecond
#include "PORT.h"

//union reg {
//    struct bit {
//        unsigned char b0:1;  
//        unsigned char b1:1;    
//        unsigned char b2:1; 
//        unsigned char b3:1;
//        unsigned char b4:1;
//        unsigned char b5:1;
//        unsigned char b6:1;
//        unsigned char b7:1;
//            }_BIT;
//    unsigned char _BYTE;
//};
//static union reg* _P2_DIRECT = (union reg*)0x2A ;
//static union reg* _P2_OUT = (union reg*)0x29 ;
//static union reg* _I2C_IN = (union reg*)0x20 ;
//static union reg* _I2C_DIRECT = (union reg*)0x22 ;
//static union reg* _I2C_OUT = (union reg*)0x21 ;
//static union reg* _P2_SEL = (union reg*)0x2E ;


 void I2C_start(void);
 void I2C_stop(void);
 unsigned char I2C_write(unsigned char dat);
 unsigned char I2C_read(void);

#endif