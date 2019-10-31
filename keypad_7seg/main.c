#include "sevenSeg.h"
#include "keypad.h"
#include "tm4c123gh6pm.h"

int main()
{
  porta_init();
  portb_init();
  porte_init();
  portf_init();
  timer_init();

  setNum(0);
  PressedSwitch pressedSwitch;
  while (1)
  {
    int keyRead = ReadKeypad();
    if (keyRead != -1)
    {
      setNum(keyRead);
      waitForDelay();
    }
    pressedSwitch = GPIO_PORTF_DATA_R & (sw1 | sw2);
    switch (pressedSwitch)
    {
    case switch_1_pressed:
      incrementNum();
      waitForDelay();
      break;
    case switch_2_pressed:
      decrementNum();
      waitForDelay();
      break;
    case switch_12_pressed:
      resetNum();
      waitForDelay();

      break;
    default:
      break;
    }
  }
  return 0;
}
