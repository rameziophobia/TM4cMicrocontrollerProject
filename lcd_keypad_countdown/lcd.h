#ifndef LCD_UTIL
#define LCD_UTIL

#define Ports
#include "stdint.h"

void lcdInit(void);
void LCD_data(unsigned char data);
void LCD_word(char * word, uint8_t size);
void lcd_clear(void);
void lcd_displayNum(int num);
void lcd_displayDigit(int digit);

#endif //LCD_UTIL