#include <stm32f10x.h>
#include <math.h>
#include <stdio.h>
#include "i2c.h"
#include "mpu6050.h"
#include "lcd.h"
#include "systick.h"
#include "timer.h"
#include "gpio.h"

void GPIO_Init(void);
void Init(void);
extern uint8_t mode;
extern uint32_t step_count;
void EXTI9_5_IRQHandler(void);

uint8_t mode = 0;
uint32_t step_count = 0;

void EXTI9_5_IRQHandler(void) {	
	if (EXTI->PR & BUTTON_PAUSE) {
			if (mode == 0) {
					mode = 1;
						GPIOA->ODR &= ~GPIO_ODR_ODR4; 
            GPIOA->ODR |= LED_RED_PIN;   
        } else {
            GPIOA->ODR &= ~LED_RED_PIN; 
            GPIOA->ODR |= GPIO_ODR_ODR4; 
					mode = 0;
			}
			hal_delay(200);
			EXTI->PR |= BUTTON_PAUSE;
	} else if (EXTI->PR & BUTTON_RESET) {
					step_count = 0;
					LCD_1602A_SetCursor(0, 0);
					LCD_1602A_ClearScrean();
					LCD_1602A_WriteString("Steps: 0");
			hal_delay(200);
			EXTI->PR |= BUTTON_RESET;
	}
}

void Init() {
		char buf[17];
		GPIO_Config();
		SysTick_Init();
		I2C1_Init();
		MPU6050_init();				
		LCD_1602A_Init();
		TIM2_Config();				
		sprintf(buf, "%d", step_count);
		LCD_1602A_SetCursor(0, 0);
		LCD_1602A_WriteString("Steps: 0");
}

int main(void) {
		Init();
		while(1) {
		}
}
