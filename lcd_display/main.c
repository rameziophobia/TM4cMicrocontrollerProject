#include "lcd.h"
#include "builtinswitchutil.h"
#include "tm4c123gh6pm.h"

int word_index = 0;

char *NAMES[3] = {
    "HLA",
    "SAID",
    "RAMEZ"};

const int NAME_SIZE[3] = {
    3,
    4,
    5};

void incrementWord()
{
    int names_arr_len = 3;
    // int names_arr_len = sizeof(num_arr) / sizeof(int);
    if (word_index == names_arr_len - 1)
    {
        word_index = -1;
    }
    ++word_index;
    LCD_word(NAMES[word_index], NAME_SIZE[word_index]);
}

void decrementWord()
{
    int names_arr_len = 3;
    if (word_index == 0)
    {
        word_index = names_arr_len;
    }
    --word_index;
    LCD_word(NAMES[word_index], NAME_SIZE[word_index]);
}

int main()
{

    portf_init();
    lcdInit();
    LCD_word(NAMES[word_index], NAME_SIZE[word_index]);

    PressedSwitch pressedSwitch;
    while (1)
    {
        pressedSwitch = GPIO_PORTF_DATA_R & (sw1 | sw2);
        switch (pressedSwitch)
        {
        case switch_1_pressed:
            incrementWord();
            break;
        case switch_2_pressed:
            decrementWord();
            break;
        default:
            break;
        }
    }

    return 0;
}