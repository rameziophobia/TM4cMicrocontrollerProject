#include "tm4c123gh6pm.h"
#define LIGHT (1U << 5)
#define switch_0 (1)

/*
    sets portB_pin5 on and off each second if the switch is pressed
*/
int main()
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    GPIO_PORTB_DEN_R |= (LIGHT | switch_0);
    GPIO_PORTB_DIR_R |= (LIGHT);                // 1 => output
    GPIO_PORTB_DIR_R &= ~switch_0;               // 0 => input
    //GPIO_PORTB_PDR_R |= switch_0;
  
    int count = 0;
    while (1)
    {
        if (GPIO_PORTB_DATA_R & switch_0)
        {
            GPIO_PORTB_DATA_R &= ~LIGHT;
            count = 0;
            while (count < 1000000)
            {
                count++;
            }
            GPIO_PORTB_DATA_R |= LIGHT;
        }
    }
}
