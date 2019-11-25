#ifndef ONE_SHOT_TIMER
#define ONE_SHOT_TIMER
#define ttimems  1000

#include <stdint.h>

#define TIMER_DELAY_100_MS 0x001869FF

void oneshotTimerInit(void);
void waitForDelay(int64_t delay_in_ns);
void delayMs(int64_t delay_in_ms);
void delayUs(int64_t delay_in_us);

#endif // ONE_SHOT_TIMER