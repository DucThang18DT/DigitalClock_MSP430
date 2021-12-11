#ifndef _PORT_H_
#define _PORT_H_

    #define     _Freq           1e6 // 1Mhz

    union reg {
    struct bit {
          unsigned char b0:1;  
          unsigned char b1:1;    
          unsigned char b2:1; 
          unsigned char b3:1;
          unsigned char b4:1;
          unsigned char b5:1;
          unsigned char b6:1;
          unsigned char b7:1;
              }_BIT;
          unsigned char _BYTE;
    };
    static union reg* P2_DIR=(union reg*)0x2a;  //khai bao dia chi o nho P2
    static union reg* P2_OUT=(union reg*)0x29;
    static union reg* P2_SEL=(union reg*)0x2e;
    static union reg* P2_IN=(union reg*)0x28;

    static union reg* P1_DIR=(union reg*)0x22;  //khai bao dia chi o nho P1
    static union reg* P1_OUT=(union reg*)0x21;
    static union reg* P1_SEL=(union reg*)0x26;
    static union reg* P1_IN=(union reg*)0x20;
    
    /// LCD's Pin
    #define     LCD_PORT        P2OUT
    #define     LCD_E_PIN       0x02
    #define     LCD_RS_PIN      0x01
    #define     HC_DS_PIN       0x04
    #define     HC_SH_PIN       0x08
    #define     HC_ST_PIN       0x10

    // I2C
    #define SCL_DIR         (P1_DIR->_BIT.b6)
    #define SCL_OUT         (P1_OUT->_BIT.b6)
    #define SDA_DIR         (P1_DIR->_BIT.b7)
    #define SDA_IN          (P1_IN->_BIT.b7)
    #define SDA_OUT         (P1_OUT->_BIT.b7)

    //===dinh nghia chan cho DHT11====:
    #define DHT_IN  (P1_IN->_BIT.b0)
    #define DHT_OUT (P1_OUT->_BIT.b0)
    #define DHT_DIR (P1_DIR->_BIT.b0)
    //================================

    /// Button block
    #define MODE_BUT    (P1_IN->_BIT.b2)
    #define SET_BUT     (P1_IN->_BIT.b3)
    #define UP_BUT      (P1_IN->_BIT.b4)
    #define DOWN_BUT    (P1_IN->_BIT.b5)

#endif