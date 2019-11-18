#include "tm4c123gh6pm.h"
#include "systicktimerutil.h"

#define PORTC_INPUT_PINS 0xF0
#define PORTA_OUTPUT_PINS 0xF0

void porta_init(void) //port for rows->output
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
    //dummy loop
    while (!(SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R0))
    {
    }
    GPIO_PORTA_DEN_R |= PORTA_OUTPUT_PINS; // enables second 4 pins
    GPIO_PORTA_DIR_R |= PORTA_OUTPUT_PINS;
    GPIO_PORTA_DATA_R = 0;
    GPIO_PORTA_ODR_R = PORTA_OUTPUT_PINS;
}

void portc_init(void) //coulmns->input
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
    //dummy loop
    while (!(SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R2))
    {
    }
    GPIO_PORTC_DEN_R |= PORTC_INPUT_PINS;  // enables second 4 pins
    GPIO_PORTC_DIR_R &= ~PORTC_INPUT_PINS;
    GPIO_PORTC_PUR_R |= PORTC_INPUT_PINS;
}

void keypad_setup(void)
{
    porta_init();
    portc_init();
}

const int numIndex[4][4] =
    {
        {1, 2, 3, 10},
        {4, 5, 6, 11},
        {7, 8, 9, 12},
        {14, 0, 15, 13}};

int ReadKeypad(void)
{
    for (int i = 0; i < 4; i++)
    {
        GPIO_PORTA_DATA_R = ~(0x10 << i);
        waitForDelay(600*1000 *10);

        if (!(GPIO_PORTC_DATA_R & 0x10))
        {
            return (numIndex[i][0]);
        }
        if (!(GPIO_PORTC_DATA_R & 0x20))
        {
            return (numIndex[i][1]);
        }
        if (!(GPIO_PORTC_DATA_R & 0x40))
        {
            return (numIndex[i][2]);
        }
        if (!(GPIO_PORTC_DATA_R & 0x80))
        {
            return (numIndex[i][3]);
        }
    }
    return (-1);
}