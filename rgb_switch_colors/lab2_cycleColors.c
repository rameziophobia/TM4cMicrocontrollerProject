#include "tm4c123gh6pm.h"

/*
    on pressing sw1 the led toggles to the next color
    on pressing sw2 the led toggles to the previous color
    on reaching the last color it cycles again to the first
    must remove finger from the switch to toggle finger again
    on pressing both sw1, sw2 the led toggles to white
*/

#define LED_DARK (0U)
#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
#define LED_YELLOW (1U << 1) | (1U << 3)
#define LED_SKYBLUE (1U << 2) | (1U << 3)
#define LED_PINK (1U << 1) | (1U << 2)
#define LED_WHITE (1U << 1) | (1U << 2) | (1U << 3)
#define WHITE_INDEX 7
#define sw1 1U << 4
#define sw2 1U
#define TIME_DELAY 150000 // 150ms

void portf_init(void)
{
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
  //dummy loop
  while (!(SYSCTL_PRGPIO_R & 0x20))
  {
  }
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
  GPIO_PORTF_CR_R = 0x01f;   // -> 0001 1111
  GPIO_PORTF_DIR_R = 0x0e;   // -> 0000 1110 // sets RBG as output
  GPIO_PORTF_DIR_R &= ~0x11; // -> 0001 0001 // sets the 2 switches as input
  GPIO_PORTF_DEN_R |= 0x01f; // -> 0001 1111 // eneables both
  GPIO_PORTF_PUR_R |= sw1;
  GPIO_PORTF_PUR_R |= sw2;
}

int volatile color_index = 0; // range 0 -> 7
int color_arr[] = {
    LED_DARK,
    LED_RED,
    LED_BLUE,
    LED_GREEN,
    LED_YELLOW,
    LED_SKYBLUE,
    LED_PINK,
    LED_WHITE};

void setColor(int index)
{
  GPIO_PORTF_DATA_R = color_arr[index];
} 

int isSw1Pressed()
{
  return !(GPIO_PORTF_DATA_R & sw1);
}

int isSw2Pressed()
{
  return !(GPIO_PORTF_DATA_R & sw2);
}

void incrementColor()
{
  int color_arr_len = sizeof(color_arr) / sizeof(int);
  if (color_index == color_arr_len - 1)
  {
    color_index = -1;
  }
  setColor(++color_index);
  while (isSw1Pressed())
  {
    if(isSw2Pressed())
    {
      setColor(color_arr_len - 1);
      color_index = color_arr_len - 1;
    }
  }
}
void dencrementColor()
{
  int color_arr_len = sizeof(color_arr) / sizeof(int);
  if (color_index == 0)
  {
    color_index = color_arr_len;
  }
  setColor(--color_index);
  while (isSw2Pressed())
  {
    if(isSw1Pressed())
    {
      setColor(color_arr_len - 1);
      color_index = color_arr_len - 1;
    }
  }
}


int main()
{
  portf_init();

  int counter = 0;
  int switch1_pressed;
  int switch2_pressed;

  setColor(color_index);

  while (1)
  {
    switch1_pressed = isSw1Pressed();
    switch2_pressed = isSw2Pressed();

    if (counter == 0)
    {
      if (switch1_pressed && switch2_pressed)
      {
        counter = TIME_DELAY;
        color_index = WHITE_INDEX;
        setColor(color_index);
        while (isSw1Pressed() && isSw2Pressed())
          ;
      }
      else if (switch1_pressed)
      {
        counter = TIME_DELAY;
        incrementColor();
      }
      else if (switch2_pressed)
      {
        counter = TIME_DELAY;
        dencrementColor();
      }
    }
    else
    {
      counter--;
      if (switch1_pressed && switch2_pressed)
      {
        counter = 0;
      }
    }
  }
}
