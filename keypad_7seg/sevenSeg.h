#ifndef SEVENSEG_H
#define SEVENSEG_H

#define ZERO    0x7E
#define ONE     0x30
#define TWO     0x6D
#define THREE   0x79
#define FOUR    0x33
#define FIVE    0x5B
#define SIX     0x5F
#define SEVEN   0x70
#define EIGHT   0x7F
#define NINE    0x7B
#define LETTER_A 0x77
#define LETTER_B 0x1F
#define LETTER_C 0x4E
#define LETTER_D 0x3D
#define LETTER_E 0x4F
#define LETTER_F 0x47
#define sw1 1U << 4
#define sw2 1U
#define TIME_DELAY 100000 // ~100ms


typedef enum
{

    switch_1_pressed = sw2,
    switch_2_pressed = sw1,
    switch_12_pressed = 0

}PressedSwitch;

void setNum(int index);
void portf_init(void);
void portb_init(void);
void timer_init(void);
void incrementNum(void);
void decrementNum(void);
void resetNum(void);
void waitForDelay(void);


#endif // SEVENSEG_H