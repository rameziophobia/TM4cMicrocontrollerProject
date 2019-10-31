#include "tm4c123gh6pm.h"

#define LED_RED (1U<<1)
#define sw1 1U << 4

int main()
{
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
  
  //dummy loop
  while(!(SYSCTL_PRGPIO_R & 0x20)){}
  GPIO_PORTF_DEN_R |= ( LED_RED | sw1 );

  GPIO_PORTF_DIR_R |= ( LED_RED );
  GPIO_PORTF_DIR_R &= ~( sw1 );
  GPIO_PORTF_PUR_R |= sw1;
  // int count = 0;
  
  while(1)
  {
    if(!(GPIO_PORTF_DATA_R & sw1))
    {
      GPIO_PORTF_DATA_R |= LED_RED;
    }
    else
    {
      GPIO_PORTF_DATA_R &= ~LED_RED;
    }
    
    // count = 0;
    // while(count < 1000000)
    // {
    //   GPIO_PORTF_DATA_R &= ~LED_RED;
    //   GPIO_PORTF_DATA_R &= ~LED_BLUE;
    //   GPIO_PORTF_DATA_R |= LED_GREEN;
    //   count++;
    // }
    // count = 0;
    // while(count < 1000000)
    // {
    //   GPIO_PORTF_DATA_R &= ~LED_GREEN;
    //   GPIO_PORTF_DATA_R &= ~LED_RED;
    //   GPIO_PORTF_DATA_R |= LED_BLUE;
    //   count++;
    // }
  }    
}
