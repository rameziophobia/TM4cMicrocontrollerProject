#include "keypad.h"
#include "lcd.h"
#include "systicktimerutil.h"

#define COUNTDOWN_DELAY 200*1000 *1000

void init(){
  keypad_setup();
  lcdInit();
  systickTimerInit(COUNTDOWN_DELAY);
}

int currentNum = 0;

void loop()
{
  startDelayNonBlocking(COUNTDOWN_DELAY * 3);
  while (1)
  {
    if (delayNotDone())
    {
      int keyRead = ReadKeypad();
      if (keyRead != -1)
      {
        currentNum = currentNum * 10 + keyRead;
        startDelayNonBlocking(COUNTDOWN_DELAY * 3);
      }
    }
    else
    {
      if (currentNum != -1)
      {
        lcd_clear(); 
        lcd_displayNum(currentNum);
        waitForDelay(COUNTDOWN_DELAY);
        currentNum--;
      }
    }
  }
}

int main()
{
  init();
  loop();
  return 0;
}