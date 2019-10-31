#include "tm4c123gh6pm.h"
#include "sevenSeg.h"

#define PORTA_INPUT_PINS 0xF0
#define PORTD_OUTPUT_PINS 0x0F

// void portd_init(void)
// {
//     SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
//     //dummy loop
//     while (!(SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R3))
//     {
//     }
//     GPIO_PORTD_DEN_R |= (PORTD_OUTPUT_PINS);
//     GPIO_PORTD_DIR_R |= PORTD_OUTPUT_PINS;
//     GPIO_PORTD_ODR_R |= PORTD_OUTPUT_PINS;
// }
// void porta_init(void)
// {
//     SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
//     //dummy loop
//     while (!(SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R0))
//     {
//     }
//     GPIO_PORTA_DEN_R |= PORTA_INPUT_PINS;
//     GPIO_PORTA_DIR_R &= ~PORTA_INPUT_PINS;
//     GPIO_PORTA_PUR_R |= PORTA_INPUT_PINS;
// }

void porta_init(void) //port for rows->output
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
    //dummy loop
    while (!(SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R0))
    {
    }
    GPIO_PORTA_DEN_R |= 0xF0; // -> 1111 1111 // enables second 4 pins
    GPIO_PORTA_DIR_R |= 0xF0;
    GPIO_PORTA_DATA_R = 0x0;
    GPIO_PORTA_ODR_R = 0xF0;
}
void porte_init(void) //coulmns input
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
    //dummy loop
    while (!(SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R4))
    {
    }
    GPIO_PORTE_DEN_R |= 0x0F; // -> 1111 1111 // enables all rows and columns
    GPIO_PORTE_DIR_R &= ~0xF; // -> 0000 1111 // sets the dir of rows' pins and columns' pins
    GPIO_PORTE_PUR_R |= 0x0F;
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
        waitForDelay();

        if (!(GPIO_PORTE_DATA_R & 0x01))
        {
            return (numIndex[i][0]);
        }
        if (!(GPIO_PORTE_DATA_R & 0x02))
        {
            return (numIndex[i][1]);
        }
        if (!(GPIO_PORTE_DATA_R & 0x04))
        {
            return (numIndex[i][2]);
        }
        if (!(GPIO_PORTE_DATA_R & 0x08))
        {
            return (numIndex[i][3]);
        }
    }
    return (-1);
}