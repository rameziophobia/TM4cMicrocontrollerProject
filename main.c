#include "lcd.h"
#include "builtinswitchutil.h"
#include "systicktimerutil.h"
#include "rgb_led.h"
#include "periodicinterruptutil.h"

#define COUNTDOWN_DELAY 200 * 1000 * 1000

#define True 1
#define False 0

void startCounting(void);
void stopCounting(void);

void blink();
void onPeriodicInterrupt(void);

void EnableInterrupts(void);

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
  systickTimerInit();
  lcdInit();
  builtin_switch_init();
  rgb_init();
  set_sw1_function(&startCounting);
  set_sw2_function(&stopCounting);
  lcd_display_on_cursor_off();
  lcdDisplayNum(0);
}

int isCounting = False;
int currentNum = 0;

void loop()
{
  while (1)
  {
    do_builtin_switch_functions();
  }
}

void blink()
{
  int volatile i = 5;
  while (i > 0)
  {
    rgb_display_color(LED_RED);
    delayMs(500);
    rgb_display_color(LED_DARK);
    delayMs(500);
    i--;
    if (isSw2Pressed())
    {
      i = 0;
    }
  }
}

void stopCounting()
{
 // if (isCounting)
  //{
   // disableTimer();
    blink();
    //delayMs(5); //Debouncing ??
  //}
}

void startCounting()
{
  // ! not bounce protected
  capture_Init();
  Timer0A_Capture();
}

void onPeriodicInterrupt(void)
{
  currentNum++;
  lcd_cursor_first_line();
  lcdDisplayNum(currentNum);
}