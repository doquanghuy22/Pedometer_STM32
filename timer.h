#ifndef __TIMER2_H
#define __TIMER2_H

#include <stm32f10x.h>

void TIM2_Config(void);
void TIM2_IRQHandler(void);
void peakDetection(int x, int y, int z);
extern uint8_t blink;
#endif 
