#include "keypad.h"
#include "lcd.h"
#include "systicktimerutil.h"

#define COUNTDOWN_DELAY 200*1000 *1000

void init(){
  keypad_setup();
  lcdInit();
  systickTimerInit(COUNTDOWN_DELAY);
}

int currentNum = -1;
void loop(){
  while (1)
  {
    int keyRead = ReadKeypad();
    if (keyRead != -1)
    {
      currentNum = keyRead;
    }
    if (currentNum != -1)
    {
        char my_char;
        int tempCurrentNum = currentNum;
        lcd_clear();
        while(tempCurrentNum != 0){
          my_char = '0' + (char)(tempCurrentNum %10);
          LCD_data(my_char);
          tempCurrentNum /= 10;
        }
        waitForDelay(COUNTDOWN_DELAY);
        currentNum--; //todo clear
    }
  }
}



int main()
{
  init();
  loop();
  return 0;
}