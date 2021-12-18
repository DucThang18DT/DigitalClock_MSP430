#include "functions.cpp"

int main()
{
  init();
  while(1){
    if (_isInterrupted)
    {
        LCD_clear();
        _isInterrupted = 0;
    }
//    LCD_showALetter('A');
//    __delay_cycles(_Freq);
//    LCD_clear();
//    __delay_cycles(_Freq/2);
    dsShowTime();
    dht_get(&nhietdo, &doam);
  }
}

