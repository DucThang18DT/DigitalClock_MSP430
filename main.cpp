#include "functions.cpp"

int main()
{
  init();
  while(1){
    if (_isInterrupt)
    {
        LCD_clear();
        _isInterrupt = 0;
    }
    dsShowTime();
  }
}

