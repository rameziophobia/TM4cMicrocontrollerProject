#ifndef LCD_UTIL
#define LCD_UTIL

#define Ports
#include "stdint.h"

void lcdInit(void);
void LCD_data(unsigned char data);
void LCD_word(char * word, uint8_t size);
void lcd_clear(void);
void lcd_displayNum(int num, int string_length);
void lcd_displayDigit(int digit);
void lcd_displayIntAsFloat(int num, int precision);
void lcd_cursor_first_line(void);
void lcd_display_on_cursor_off(void);
void display_float_test(void);

#endif //LCD_UTIL