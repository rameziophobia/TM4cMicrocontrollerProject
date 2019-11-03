#ifndef LCD_H
#define LCD_H
void cmd_write( char cmd);
void LCD_DataWrite(char dat);
void LCD_start(unsigned char command);
void LCD_data(unsigned char data);
void LCD_command(unsigned char command);
#endif LCD_H
