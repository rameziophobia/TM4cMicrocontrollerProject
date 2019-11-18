#ifndef LCD_UTIL
#define LCD_UTIL

#define Ports
#include "stdint.h"

void lcdInit(void);
void LCD_data(unsigned char data);
void LCD_word(char * word, uint8_t size);
void lcd_clear(void);

#endif //LCD_UTIL