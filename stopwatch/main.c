#include "lcd.h"
#include "builtinswitchutil.h"
#include "systicktimerutil.h"
#include "rgb_led.h"
#include "periodicinterruptutil.h"
#include "tm4c123gh6pm.h"

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
void loop_body(void);

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
  //periodicInterruptInit(&onPeriodicInterrupt, 16000 * 1000 - 1);
  //EnableInterrupts();

  lcdDisplayNum(0);
}

int isCounting = False;
int currentNum = 0;

void loop()
{
  while (1)
  {
        switch (GPIO_PORTF_DATA_R & 0x11)
    {
        case 1U:
              loop_body();
            break;
        default:
        break;
    }
  }
}

int64_t calculateDelay2(int64_t delay_in_ns){
    return (delay_in_ns / 62.5) - 1;
}

int my_num = 0;
void loop_body()
{
  while(1)
  {
    int64_t delay = 1000000000; //1 sec
    NVIC_ST_CTRL_R = 0;
    int64_t temp = calculateDelay2(delay);
    NVIC_ST_RELOAD_R = temp;
    NVIC_ST_CURRENT_R = temp;
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;
    //int stop = 0;
    while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT))
    {
        switch (GPIO_PORTF_DATA_R & 0x11)
        {
            case 1U << 4:
                    //stop = 1;
                    return;
                break;
            default:
            break;
        }
    }
    my_num++;
    lcd_clear();
      lcd_cursor_first_line();
    lcdDisplayNum(my_num);
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

void disableSysTimer()
{
}

void stopCounting()
{

    disableSysTimer();
    blink();
    delayMs(5); //Debouncing ??
}

void startCounting()
{
  // ! not bounce protected
  enableTimer();
}

void onPeriodicInterrupt(void)
{
  currentNum++;
  lcd_cursor_first_line();
  lcdDisplayNum(currentNum);
}