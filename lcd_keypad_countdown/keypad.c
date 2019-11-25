#include "tm4c123gh6pm.h"
// #include "systicktimerutil.h"
#include "oneshotutil.h"

#define INPUT_COLUMNS_PINS 0xF0
#define OUTPUT_ROWS_PINS 0xF0

#define ROW_PIN_0 0x10
#define COLUMN_PIN_0 0x10

// Port A
#define KEYPAD_ROWS_CLK SYSCTL_RCGCGPIO_R0
#define KEYPAD_ROWS_DIR GPIO_PORTA_DIR_R
#define KEYPAD_ROWS_DEN GPIO_PORTA_DEN_R
#define KEYPAD_ROWS_DATA GPIO_PORTA_DATA_R
#define KEYPAD_ROWS_ODR GPIO_PORTA_ODR_R

// Port C
#define KEYPAD_COLUMNS_CLK SYSCTL_RCGCGPIO_R2
#define KEYPAD_COLUMNS_DIR GPIO_PORTC_DIR_R
#define KEYPAD_COLUMNS_DEN GPIO_PORTC_DEN_R
#define KEYPAD_COLUMNS_DATA GPIO_PORTC_DATA_R
#define KEYPAD_COLUMNS_PUR GPIO_PORTC_PUR_R

int check_column(int row);
int isKeyPressed(int row, int column);

void rowPort_init(void) //port for rows->output
{
    SYSCTL_RCGCGPIO_R |= KEYPAD_ROWS_CLK;
    //dummy loop
    while (!(SYSCTL_PRGPIO_R & KEYPAD_ROWS_CLK))
    {
    }
    KEYPAD_ROWS_DEN |= OUTPUT_ROWS_PINS; // enables second 4 pins
    KEYPAD_ROWS_DIR |= OUTPUT_ROWS_PINS;
    KEYPAD_ROWS_DATA = 0;
    KEYPAD_ROWS_ODR = OUTPUT_ROWS_PINS;
}

void columnPort_init(void) //coulmns->input
{
    SYSCTL_RCGCGPIO_R |= KEYPAD_COLUMNS_CLK;
    //dummy loop
    while (!(SYSCTL_PRGPIO_R & KEYPAD_COLUMNS_CLK))
    {
    }
    KEYPAD_COLUMNS_DEN |= INPUT_COLUMNS_PINS;  // enables second 4 pins
    KEYPAD_COLUMNS_DIR &= ~INPUT_COLUMNS_PINS;
    KEYPAD_COLUMNS_PUR |= INPUT_COLUMNS_PINS;
}

void keypad_setup(void)
{
    rowPort_init();
    columnPort_init();
}

const int numIndex[4][4] =
    {
        {1, 2, 3, 10},
        {4, 5, 6, 11},
        {7, 8, 9, 12},
        {14, 0, 15, 13}};

int ReadKeypad(void)
{
    for (int row = 0; row < 4; row++)
    {
        KEYPAD_ROWS_DATA = ~(ROW_PIN_0 << row);
        waitForDelay(600*1000*10);
        // delayMs(200);
        
        int pressed_key = check_column(row);
        if (pressed_key != -1)
        {
          return pressed_key;
        }
    }
    return (-1);
}

int check_column(int row)
{
    for (int column = 0; column < 4; column++)
    {
        int pressed_key = isKeyPressed(row, column);
        if (pressed_key != -1)
        {
          return pressed_key;
        }
    }
    return -1;
}

int isKeyPressed(int row, int column)
{
    if (!(KEYPAD_COLUMNS_DATA & (COLUMN_PIN_0 << column)))
    {
        return (numIndex[row][column]);
    }
    return -1;
}