#include "LCD16x2.h"
#include "DHT11_MSP430G2553_LIB.h"
#include "I2C_USCI.h"
#include "DS1307.h"
#include "Clock.h"

volatile static unsigned char _isInterrupted = 0;

static void init();
static void showDHT();
static void read_dht();
static __interrupt void test(void);

//////////////////////////////////////////////////////

void init(){
  
  WDTCTL = WDTPW | WDTHOLD;  //Stop Watchdog
  DCOCTL = CALDCO_1MHZ;       // Clock=1Mhz
  BCSCTL1 = CALBC1_1MHZ;     
  
  P2DIR  = 0x1F;      // P2.0 -> P2.4 are output pins.
  P2OUT  = 0x00;      //Start with nothing being output
  P1DIR |= BIT6;
  //DHT
//  P1DIR &= ~BIT7;
//  P1DIR &= ~BIT1;
  

  /// set input pins for buttons
  P1_DIR->_BIT.b2 = 0;
  P1_DIR->_BIT.b3 = 0;
  P1_DIR->_BIT.b4 = 0;
  P1_DIR->_BIT.b5 = 0;
  
  P1IE |= BIT3 + BIT2;     //Cho phép ngắt ở P1.3, P1.2
  P1IES |=BIT3 + BIT2;   //Ngắt cạnh xuống,
  P1IFG &=~BIT3;           //Xóa cờ ngắt
  P1IFG &=~BIT2;
  
  __bis_SR_register(GIE);
  Select_Clock(DCO_1MHZ);
  dsInit();
  dsSetTime();
  LCD_init();
}

#pragma vector = PORT1_VECTOR
__interrupt void test(void)
{
  _isInterrupted = 1;
//  P1IE &= ~ (BIT3 + BIT2);     // Dừng cho phép ngắt ở P1.3, P1.2
  //Kiểm tra ngắt có phải là ở P1.3 không
  if(P1IFG&BIT3)
  {
    dsTimeConfig();
    P1IFG &=~BIT3;
  }
  if(P1IFG&BIT2)
  {
    showDHT();
    P1IFG &=~BIT2;
  }
//  P1IE |= BIT3 + BIT2;     //Cho phép ngắt ở P1.3, P1.2
//  P1IES |=BIT3 + BIT2;
}

void showDHT()
{
    __delay_cycles(100);
    LCD_clear();
    
    dht_get(&nhietdo, &doam);
    LCD_showString("Temp: ", 0);
    LCD_showALetter(nhietdo/10 + 48);
    LCD_showALetter(nhietdo%10 + 48);
//    LCD_showALetter('°');
    LCD_showALetter(' ');
    LCD_showALetter(223);
    LCD_showALetter('C');
    LCD_showString("Hum : ", 1);
    LCD_showALetter(doam/10 + 48);
    LCD_showALetter(doam%10 + 48);
    LCD_showALetter(' ');
    LCD_showALetter('%');
    __delay_cycles(2*_Freq);
    LCD_clear();
}


