#include <stm32f10x.h>
#include "systick.h"

uint32_t usTick = 0;
uint32_t msTick = 0;

void SysTick_Init(void) {
    SysTick->LOAD = SystemCoreClock / 1000 - 1;
    SysTick->VAL = 0; /* Reset current value register */
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
    NVIC_SetPriority(SysTick_IRQn, 1);
    NVIC_EnableIRQ(SysTick_IRQn);
}

void hal_IncTick(void) {
    msTick++;
}

uint32_t hal_GetTick(void) {
    return msTick;
}

void SysTick_Handler(void) {
    hal_IncTick(); /* Increment the millisecond tick */
}
	
uint32_t millis(void) {
    return msTick;
}

void hal_delay(uint32_t delay) {
    uint32_t tickstart = hal_GetTick();
    while ((hal_GetTick() - tickstart) < delay) {
        __NOP(); /* Prevent compiler optimizations */
    }
}
