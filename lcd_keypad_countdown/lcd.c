#include "tm4c123gh6pm.h"
#include <stdint.h>

#include "systicktimerutil.h"

#define LCD_COMMAND_CLEAR 0x1               // Clear display screen
#define LCD_COMMAND_RETURN_CURSOR 0x2       // Return cursor home
#define LCD_COMMAND_INC_CURSOR 0x6          // Increment cursor (shift cursor to right)
#define LCD_COMMAND_DISPLAY_ON 0xF          // Display on, cursor blinking
#define LCD_COMMAND_CURSOR_FIRST_LINE 0x80  // Force cursor to beginning of 1st line
#define LCD_COMMAND_CURSOR_SECOND_LINE 0xC0 // Force cursor to beginning of 2nd line
#define LCD_COMMAND_8_BIT 0x38              // 2 lines and 5x7 character (8-bit data, D0 to D7)
#define LCD_COMMAND_4_BIT 0x28              // 2 lines and 5x7 character (4-bit data, D4 to D7)
#define LCD_COMMAND_WAKEUP 0x30             // wakeup

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

void delayMs(int64_t delayAmount)
{
    waitForDelay(delayAmount * 1000000);
}

void delayUs(int64_t delayAmount)
{
    waitForDelay(delayAmount * 1000);
}

void LCD_command(unsigned char command)
{
    LCD_CTRL_DATA = LCD_CTRL_ZERO;
    LCD_DATA_DATA = command;
    LCD_CTRL_DATA = LCD_EN; /* pulse E */
    delayUs(1);             /* Enable pulse Width */
    LCD_CTRL_DATA = LCD_CTRL_ZERO;
    if (command > LCD_COMMAND_RETURN_CURSOR)
        delayUs(40); /* all others 40 us */
    else
        delayMs(2); /* command 1 and 2 needs up to 1.64ms */
}

void LCD_data(unsigned char data)
{
    LCD_CTRL_DATA = LCD_RS;
    LCD_DATA_DATA = data;
    LCD_CTRL_DATA = LCD_EN | LCD_RS; /* pulse E */
    delayUs(1);
    LCD_CTRL_DATA = LCD_CTRL_ZERO;
    delayUs(40);
}

void LCD_word(char * word, uint8_t size)
{
    LCD_command(LCD_COMMAND_CLEAR);
    for (int i = 0; i < size; i++)
    {
        LCD_data(*word++);
    }
}

void initDataPort(void){
    SYSCTL_RCGCGPIO_R |= LCD_DATA_CLK;
    while (!(SYSCTL_PRGPIO_R & LCD_DATA_CLK))
    {
    }
    LCD_DATA_DIR |= 0xFF;
    LCD_DATA_DEN |= 0xFF;
    LCD_DATA_DATA = 0;
}

void initCtrlPort(void){
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

void lcd_clear(void)
{
    LCD_command(LCD_COMMAND_CLEAR);
}

void lcdInit()
{
    initDataPort();
    initCtrlPort();
    systickTimerInit(100000000); //todo :( im not sad im just drawn this way :(((
    LCD_start();
}