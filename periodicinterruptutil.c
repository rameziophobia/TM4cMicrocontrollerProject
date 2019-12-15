#include "periodicinterruptutil.h"
#include "tm4c123gh6pm.h"
#include "lcd.h"
#define TIMER_SYSCTL_CLOCK SYSCTL_RCGCTIMER_R0
#define TIMER_CTL TIMER0_CTL_R
#define TIMER_CFG TIMER0_CFG_R
#define TIMER_TAMR TIMER0_TAMR_R
#define TIMER_TAILR TIMER0_TAILR_R
#define TIMER_TAPR TIMER0_TAPR_R
#define TIMER_ICR TIMER0_ICR_R
#define TIMER_IMR TIMER0_IMR_R
#define TIMER_RIS TIMER0_RIS_R
#define INTERRUPT_PRIORITY_R NVIC_PRI4_R
#define INTERRUPT_PRIORITY 0x80000000
#define INTERRUPT_ENABLE_R NVIC_EN0_R
#define INTERRUPT_ENABLE 1 << 19

void (*PeriodicTask)(void);

void periodicInterruptInit(void (*task)(void), uint32_t period)
{
   
}
void capture_Init(void)
{
  SYSCTL_RCGCTIMER_R |=1;
  TIMER0_PP_R|=0xf;
  GPIO_PORTF_AFSEL_R|=0x01;
  GPIO_PORTF_PCTL_R&=~0x0000000F;
  GPIO_PORTF_PCTL_R|=0x00000007;
  TIMER0_CTL_R &=~1;
  TIMER0_CFG_R=0;
  TIMER0_TAMR_R=0x17;
  TIMER0_TAPR_R=0xFFFF;
  TIMER0_CTL_R &=~8;
  TIMER0_CTL_R |=4;
  TIMER0_CTL_R |=1;
}


void Timer0A_Capture(void)
{
  int past=TIMER0_TAV_R;
  int count=0;
  TIMER0_ICR_R=4;
  while((TIMER0_RIS_R & 4)==0)
  {
    if(TIMER0_TAV_R<past)
    {
     lcd_clear();
     lcd_cursor_first_line();
      count++;
      lcdDisplayNum(count);
      
    }
    
    past=TIMER0_TAV_R; 
  }

  count=count*pow(10,5)+TIMER0_TAR_R;
  lcd_displayIntAsFloat(count);
 
  
}

void enableTimer(){
    TIMER_CTL |= 0x01;
}

void disableTimer(){
    TIMER_CTL = 0x0;
}
