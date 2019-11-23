#include "keypad.h"
#include "lcd.h"
#include "systicktimerutil.h"
#include "builtinswitchutil.h"
#include "rgb_led.h"

#define COUNTDOWN_DELAY 200 * 1000 * 1000

#define True 1
#define False 0

void start_countdown(void);
void abort_countdown(void);

void countdown(void);
void readNumber();

void init(void);
void loop(void);

int main()
{
  init();
  loop();
  return 0;
}

void init()
{
  keypad_setup();
  lcdInit();
  builtin_switch_init();
  rgb_init();
  set_sw1_function(&start_countdown);
  set_sw2_function(&abort_countdown);
  //systickTimerInit(); //already called in lcdInit()
  
  // ! lcd_displayIntAsFloat(0);
}

int currentNum = 0;
int isCountingDown = False;
int prevNumber = 0;

void loop()
{
  while (1)
  {
    do_builtin_switch_functions();

    if (isCountingDown)
    {
      countdown();
    }
    else
    {
      prevNumber = currentNum;
      readNumber();
      if (prevNumber != currentNum)
      {
        //lcd_clear();
        lcd_cursor_first_line();
        lcd_displayIntAsFloat(currentNum);
      }
    }
  }
}

void start_countdown()
{
  isCountingDown = True;
}

void countdown()
{
  if (currentNum >= 0)
  {
    lcd_cursor_first_line();
    lcd_displayIntAsFloat(currentNum);
    delayMs(100);
    currentNum-=10;
  }
  else
  {
    isCountingDown = False;
    currentNum = 0;
    lcd_clear();
    //todo toggle red led
  }
}

void readNumber()
{
  int keyRead = ReadKeypad();
  if (keyRead != -1)
  {
    currentNum = currentNum * 10 + keyRead;
    delayMs(300);
  }
  currentNum = currentNum % 10000;
}

void abort_countdown()
{
  isCountingDown = False;
}