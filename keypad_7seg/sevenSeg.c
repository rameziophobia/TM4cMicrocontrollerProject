#include "sevenSeg.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"

#define TIMER_DELAY 0x001869FF // 100 ms

int num_arr[] = {
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    LETTER_A,
    LETTER_B,
    LETTER_C,
    LETTER_D,
    LETTER_E,
    LETTER_F};

volatile int8_t num_index = 0;

void portf_init(void)
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
    //dummy loop
    while (!(SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R5))
    {
    }
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R = 0x01f;   // -> 0001 1111
    GPIO_PORTF_DIR_R &= ~0x11; // -> 0001 0001 // sets the 2 switches as input
    GPIO_PORTF_DEN_R |= 0x011; // -> 0001 0001 // eneables both
    GPIO_PORTF_PUR_R |= sw1;
    GPIO_PORTF_PUR_R |= sw2;
}

void portb_init(void)
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    //dummy loop
    while (!(SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R1))
    {
    }
    GPIO_PORTB_DEN_R |= 0x7F; // -> 0111 1111 // enables the 7 seg bits
    GPIO_PORTB_DIR_R |= 0x7F; // -> 0111 1111 // sets the dir of 7 seg bits as output
    GPIO_PORTB_DATA_R = ZERO;
}
void timer_init(void)
{
    NVIC_ST_RELOAD_R = TIMER_DELAY;
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;
}

int isSw1Pressed()
{
    return !(GPIO_PORTF_DATA_R & sw1);
}

int isSw2Pressed()
{
    return !(GPIO_PORTF_DATA_R & sw2);
}

void setNum(int index)
{
    GPIO_PORTB_DATA_R = num_arr[index];
}

void resetNum(void)
{
    num_index = 0;
    setNum(num_index);
}

void incrementNum(void)
{
    int num_arr_len = sizeof(num_arr) / sizeof(int);
    if (num_index == num_arr_len - 1)
    {
        num_index = -1;
    }
    setNum(++num_index);

    while (isSw1Pressed())
    {
        if (isSw2Pressed())
        {
            resetNum();
        }
    }
}

void decrementNum()
{
    int num_arr_len = sizeof(num_arr) / sizeof(int);
    if (num_index == 0)
    {
        num_index = num_arr_len;
    }
    setNum(--num_index);
    while (isSw2Pressed())
    {
        if (isSw1Pressed())
        {
            resetNum();
        }
    }
}

void waitForDelay(void){
    NVIC_ST_CURRENT_R = TIMER_DELAY;
    while (!(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT))
    {
    }
}
