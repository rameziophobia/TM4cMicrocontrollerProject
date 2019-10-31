#include "sevenSeg.h"
#include "tm4c123gh6pm.h"

int main()
{
  portf_init();
  portb_init();
  timer_init();

  PressedSwitch pressedSwitch;
  while (1)
  {
    pressedSwitch = GPIO_PORTF_DATA_R & (sw1 | sw2);
    switch (pressedSwitch)
    {
    case switch_1_pressed:
      incrementNum();
      break;
    case switch_2_pressed:
      decrementNum();
      break;
    case switch_12_pressed:
      resetNum();
      break;
    default:
      break;
    }

    waitForDelay();
  }
  return 0;
}
