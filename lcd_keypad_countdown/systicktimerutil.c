
#include <stdint.h>
#include "tm4c123gh6pm.h"

// #define 

int32_t calculateDelay(int64_t delay_in_ns){
    return (delay_in_ns / 62.5) - 1;
}

void systickTimerInit(int64_t delay_in_ns)
{
    NVIC_ST_RELOAD_R = calculateDelay(delay_in_ns);
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;
}

void waitForDelay(int32_t delay_in_ns)
{
    NVIC_ST_CURRENT_R = calculateDelay(delay_in_ns);
    while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT))
        ;
}