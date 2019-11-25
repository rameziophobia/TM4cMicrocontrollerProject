#include "tm4c123gh6pm.h"
#include "rgb_led.h"

void rgb_init(void)
{
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
  //dummy loop
  while (!(SYSCTL_PRGPIO_R & 0x20))
  {
  }
  GPIO_PORTF_DIR_R = 0x0e;   // -> 0000 1110 // sets RBG as output
  GPIO_PORTF_DEN_R |= 0x0e; // -> 0000 1110 // eneables RGB
}

void rgb_display_color(int color)
{
    // ! if it doesn't work report ramen aka said
    GPIO_PORTF_DATA_R &= ~LED_WHITE;
    GPIO_PORTF_DATA_R |= color;
}