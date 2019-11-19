#include <stdint.h>
#include "tm4c123gh6pm.h"

int64_t calculateDelay(int64_t delay_in_ns){
    return delay_in_ns * 16000000 - 1;
}

void systickTimerInit(void)
{
    NVIC_ST_RELOAD_R = calculateDelay(10000);
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;
}

void waitForDelay(int64_t delay_in_ns)
{
    NVIC_ST_CURRENT_R = calculateDelay(delay_in_ns);
    while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT))
        ;
}

void delayMs(int64_t delay_in_ms)
{
    waitForDelay(delay_in_ms * 1000000);
}

void delayUs(int64_t delay_in_us)
{
    waitForDelay(delay_in_us * 1000);
}

void startDelayNonBlocking(int32_t delay_in_ns)
{
    NVIC_ST_CURRENT_R = calculateDelay(delay_in_ns);
}

int delayNotDone(void)
{
    return !(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT);
}