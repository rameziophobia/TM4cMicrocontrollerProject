#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <math.h>
#include <stdio.h>

#include "systicktimerutil.h"

#define LCD_COMMAND_CLEAR 0x1                 // Clear display screen
#define LCD_COMMAND_RETURN_CURSOR 0x2         // Return cursor home
#define LCD_COMMAND_INC_CURSOR 0x6            // Increment cursor (shift cursor to right)
#define LCD_COMMAND_DISPLAY_ON 0xF            // Display on, cursor blinking
#define LCD_COMMAND_DISPLAY_ON_CURSOR_OFF 0xC // Display on, cursor off
#define LCD_COMMAND_CURSOR_FIRST_LINE 0x80    // Force cursor to beginning of 1st line
#define LCD_COMMAND_CURSOR_SECOND_LINE 0xC0   // Force cursor to beginning of 2nd line
#define LCD_COMMAND_8_BIT 0x38                // 2 lines and 5x7 character (8-bit data, D0 to D7)
#define LCD_COMMAND_4_BIT 0x28                // 2 lines and 5x7 character (4-bit data, D4 to D7)
#define LCD_COMMAND_WAKEUP 0x30               // wakeup

#define LCD_CTRL_ZERO 0
#define LCD_RS 0x1 // 0000
#define LCD_RW 0x2 // 0010
#define LCD_EN 0x4 // 0100

#define LCD_CTRL_CLK SYSCTL_RCGCGPIO_R4
#define LCD_CTRL_DIR GPIO_PORTE_DIR_R
#define LCD_CTRL_DEN GPIO_PORTE_DEN_R
#define LCD_DATA_CLK SYSCTL_RCGCGPIO_R1
#define LCD_DATA_DIR GPIO_PORTB_DIR_R
#define LCD_DATA_DEN GPIO_PORTB_DEN_R
#define LCD_CTRL_DATA GPIO_PORTE_DATA_R
#define LCD_DATA_DATA GPIO_PORTB_DATA_R

#define DISPLAY_FLOAT_PRECISION 100
#define DISPLAY_FLOAT_SCALE 100

int inverseNum(int num);
void lcd_displayDigit(int digit);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void initDataPort(void);
void initCtrlPort(void);
void LCD_start(void);

void lcdInit()
{
    initDataPort();
    initCtrlPort();
    systickTimerInit(); //todo :( im not sad im just drawn this way :(((
    LCD_start();
    //display_float_test();
}

void LCD_word(char *word, uint8_t size)
{
    LCD_command(LCD_COMMAND_CLEAR);
    for (int i = 0; i < size; i++)
    {
        LCD_data(*word++);
    }
}

void LCD_data(unsigned char data)
{
    //printf("%c", data);
    LCD_CTRL_DATA = LCD_RS;
    LCD_DATA_DATA = data;
    LCD_CTRL_DATA = LCD_EN | LCD_RS; /* pulse E */
    delayUs(1);
    LCD_CTRL_DATA = LCD_CTRL_ZERO;
    delayUs(40);
}

void initDataPort(void)
{
    SYSCTL_RCGCGPIO_R |= LCD_DATA_CLK;
    while (!(SYSCTL_PRGPIO_R & LCD_DATA_CLK))
    {
    }
    LCD_DATA_DIR |= 0xFF;
    LCD_DATA_DEN |= 0xFF;
    LCD_DATA_DATA = 0;
}

void initCtrlPort(void)
{
    SYSCTL_RCGCGPIO_R |= LCD_CTRL_CLK;
    while (!(SYSCTL_PRGPIO_R & LCD_CTRL_CLK))
    {
    }
    LCD_CTRL_DEN |= 0x07; // XX00 0111
    LCD_CTRL_DIR |= 0x07; // XX00 0111
    LCD_CTRL_DATA = 0;
}

void LCD_start(void)
{
    delayMs(20); // Wait >15 ms after power is applied
    /* initialization sequence */
    LCD_command(LCD_COMMAND_WAKEUP);
    delayMs(5); // must wait 5ms, busy flag not available
    LCD_command(LCD_COMMAND_WAKEUP);
    delayUs(100); // must wait 100us, busy flag not available
    LCD_command(LCD_COMMAND_WAKEUP);
    delayUs(100); // must wait 100us, busy flag not available
    /* Prepare LCD Operation and Function */
    LCD_command(LCD_COMMAND_8_BIT);
    LCD_command(LCD_COMMAND_INC_CURSOR);
    LCD_command(LCD_COMMAND_CLEAR);
    LCD_command(LCD_COMMAND_DISPLAY_ON);
}

void LCD_command(unsigned char command)
{
    LCD_CTRL_DATA = LCD_CTRL_ZERO;
    LCD_DATA_DATA = command;
    LCD_CTRL_DATA = LCD_EN; /* pulse E */
    delayUs(1);             /* Enable pulse Width */
    LCD_CTRL_DATA = LCD_CTRL_ZERO;
    if (command > LCD_COMMAND_RETURN_CURSOR)
        delayUs(50); /* all others 50 us */
    else
        delayMs(2); /* command 1 and 2 needs up to 1.64ms */
}

void lcd_clear(void)
{
    LCD_command(LCD_COMMAND_CLEAR);
}

void lcd_cursor_first_line(void)
{
    LCD_command(LCD_COMMAND_CURSOR_FIRST_LINE);
}

void lcd_display_on_cursor_off(void)
{
    LCD_command(LCD_COMMAND_DISPLAY_ON_CURSOR_OFF);
}

void lcd_displayNum(int num, int string_length)
{
    int num_size = (int)((ceil(log10(num + 1))) * sizeof(char));
    char str[17];
    char zeroes[17];
    int leading_zeroes_num = string_length - num_size;
    for (int i = 0; i < leading_zeroes_num; i++)
    {
        zeroes[i] = '0';
    }
    zeroes[leading_zeroes_num] = 0;

    if(num == 0)
    {
       sprintf(str, "%s",zeroes);
    }
    else
    {
       sprintf(str, "%s%d",zeroes, num);
    }
    LCD_word(str, string_length);
    //printf("%s", str);
}

void lcd_displayIntAsFloat(int num, int precision)
{
    precision = pow(10, precision);
    lcd_displayNum(num / precision, 4);
    LCD_data('.');
    //printf(".");
    lcd_displayNum(num % precision, 2);
    //printf("\n");
}

void lcd_displayDigit(int digit)
{
    char my_char = '0' + (char)(digit);
    LCD_data(my_char);
} 

void display_float_test()
{
  lcd_displayIntAsFloat(734540, 2);
  lcd_displayIntAsFloat(4273, 2);
  lcd_displayIntAsFloat(600, 2);
  lcd_displayIntAsFloat(1, 2);
  lcd_displayIntAsFloat(0, 2);
  lcd_displayIntAsFloat(10, 2);
  lcd_displayIntAsFloat(15662, 2);
  lcd_displayIntAsFloat(999999, 2);
}