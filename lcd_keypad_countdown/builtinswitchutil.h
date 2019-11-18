#ifndef BUILT_IN_SWITCH_UTIL
#define BUILT_IN_SWITCH_UTIL
#define sw1 1U << 4
#define sw2 1U

typedef enum
{

    switch_1_pressed = sw2,
    switch_2_pressed = sw1,
    switch_12_pressed = 0

}PressedSwitch;

void portf_init(void);
int isSw1Pressed();
int isSw2Pressed();

#endif // BUILT_IN_SWITCH_UTIL