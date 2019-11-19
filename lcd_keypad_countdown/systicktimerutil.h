#ifndef SYSTICK_TIMER_UTIL
#define SYSTICK_TIMER_UTIL

#include <stdint.h>

#define TIMER_DELAY_100_MS 0x001869FF

void systickTimerInit(int64_t delay_in_ns);
void waitForDelay(int64_t delay_in_ns);
int delayNotDone(void);
void startDelayNonBlocking(int32_t delay_in_ns);

#endif // SYSTICK_TIMER_UTIL