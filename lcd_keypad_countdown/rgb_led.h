#ifndef RGB_LED
#define RGB_LED

#define LED_DARK (0U)
#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
#define LED_YELLOW (1U << 1) | (1U << 3)
#define LED_SKYBLUE (1U << 2) | (1U << 3)
#define LED_PINK (1U << 1) | (1U << 2)
#define LED_WHITE (1U << 1) | (1U << 2) | (1U << 3)

void rgb_init(void);
void rgb_display_color(int color);

#endif //RGB_LED