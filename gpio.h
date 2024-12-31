#include <stm32f10x.h>

#define BUTTON_PAUSE (1u<<6)
#define BUTTON_RESET (1u<<7)
#define LED_RED_PIN (1u<<5)
#define LED_GREEN_PIN (1u<<4)

void GPIO_Config(void);
