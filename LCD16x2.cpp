#include "LCD16x2.h"

void _send2LCD(char data, int mode)
{
    // shiftOut(DS_Pin, SH_Pin, MSBFIRST, data);
    char i;
	for (i = 0; i < 8; i++)  {
        // digitalWrite(dataPin, !!(val & (1 << (7 - i))));
        if ((data >> (7 - i)) & 0x01)
            LCD_PORT |= HC_DS_PIN;
        else LCD_PORT &= ~HC_DS_PIN;
		// digitalWrite(clockPin, HIGH);
        // digitalWrite(clockPin, LOW);	
        LCD_PORT |= HC_SH_PIN;
        LCD_PORT &= ~HC_SH_PIN;
	}

    __delay_cycles(10*_Freq/1000); // 10*_Freq/1000   // 900
    
    // digitalWrite(ST_Pin, HIGH);
    // digitalWrite(ST_Pin, LOW);
    LCD_PORT |= HC_ST_PIN;
    LCD_PORT &= ~HC_ST_PIN;
    
    // digitalWrite(RS_Pin, mode == Mode::cmd?LOW:HIGH);
    if (mode == 0x00) // Mode::cmd
        LCD_PORT &= ~LCD_RS_PIN;
    else // Mode::data
        LCD_PORT |= LCD_RS_PIN;
    
    // digitalWrite(E_Pin, LOW);
    LCD_PORT &= ~LCD_E_PIN;

    // digitalWrite(E_Pin, HIGH);
    LCD_PORT |= LCD_E_PIN;
    __delay_cycles(2*_Freq/1000); // 2*_Freq/1000   // 200
}

void _cmd(char cmd)
{
    _send2LCD(cmd, 0);
}

void LCD_showALetter(char letter)
{
    _send2LCD(letter, 1);
}

void LCD_showString(const char *str, int posi)
{
    if (posi == 1) // Position::bottom
        _send2LCD(0xC0, 0);  // Mode:: cmd
    else _send2LCD(0x80, 0); // Mode:: cmd
    int count = 0;
    while (str[count] != '\0')
    {
        LCD_showALetter(str[count]);
        ++count;
    }
}

void LCD_clear()
{
    _send2LCD(0x01, 0); // Mode::cmd
}

void LCD_init()
{
    for (int i = 0; i < 4; i++)
    {
        _send2LCD(0x38, 0); // Mode::cmd
        __delay_cycles(5*_Freq/1000);
    }
    
    _send2LCD(0x0C, 0); // Mode::cmd
    LCD_clear();
}

void LCD_goto(unsigned char x, unsigned char y)
{   
    if (x == 0x00) // line 1
        _send2LCD(0x80 + y, 0);
    else _send2LCD(0xC0 + y, 0); // line 2
    // for (int i = 1; i <= y; i++)
    //     _send2LCD(0x06, 0);
}