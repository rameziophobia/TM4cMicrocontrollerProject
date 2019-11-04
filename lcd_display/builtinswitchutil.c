#include "tm4c123gh6pm.h"

#define sw1 1U << 4
#define sw2 1U

void portf_init(void)
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
    //dummy loop
    while (!(SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R5))
    {
    }
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R = 0x01f;   // -> 0001 1111
    GPIO_PORTF_DIR_R &= ~0x11; // -> 0001 0001 // sets the 2 switches as input
    GPIO_PORTF_DEN_R |= 0x011; // -> 0001 0001 // eneables both
    GPIO_PORTF_PUR_R |= sw1;
    GPIO_PORTF_PUR_R |= sw2;
}

int isSw1Pressed()
{
    return !(GPIO_PORTF_DATA_R & sw1);
}

int isSw2Pressed()
{
    return !(GPIO_PORTF_DATA_R & sw2);
}