#include "oneshotutil.h"
#include "tm4c123gh6pm.h"

int32_t calculateDelay(int64_t delay_in_ns){
    return (delay_in_ns / 62.5) - 1;
}

void oneshotTimerInit(void){
    SYSCTL_RCGCTIMER_R |=  SYSCTL_RCGCTIMER_R0;
    TIMER0_CTL_R = 0x0;
    TIMER0_CFG_R = TIMER_CFG_32_BIT_TIMER;
    TIMER0_TAMR_R = TIMER_TAMR_TAMR_1_SHOT;

    TIMER0_TAILR_R = 16000 * ttimems - 1;

    TIMER0_CTL_R |= 0x01;
}

void waitForDelay(int64_t delay_in_ns){
    TIMER0_CTL_R = 0x0;
    int64_t temp = calculateDelay(delay_in_ns);
    TIMER0_TAILR_R = temp;

    TIMER0_CTL_R |= 0x01;
    if((TIMER0_RIS_R & TIMER_RIS_TATORIS) == 0){}
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;

    while ((TIMER0_RIS_R & TIMER_RIS_TATORIS) == 0) ;  /* STEP 8: wait for TimerA timeout flag to set*/
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;                 /*         clear the TimerA timeout flag*/
}

void delayMs(int64_t delay_in_ms)
{
    waitForDelay(delay_in_ms * 1000000);
}

void delayUs(int64_t delay_in_us)
{
    waitForDelay(delay_in_us * 1000);
}