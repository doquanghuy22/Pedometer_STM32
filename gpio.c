#include <stm32f10x.h>
#include <stdio.h>
#include "gpio.h"

void GPIO_Config(void) {
		/* Enable clock for GPIOC and GPIOA: */
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN;
		
		/*Init LED_GREEN at PA4*/
		GPIOA->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);
    GPIOA->CRL |= GPIO_CRL_MODE4_0;                
	
		/*Init LED_RED at PA5*/
		GPIOA->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
    GPIOA->CRL |= GPIO_CRL_MODE5_0;
	
		/*Init for BUTTON_PAUSE pin*/
		GPIOA->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6);  /* clear bits*/
		GPIOA->CRL |= GPIO_CRL_CNF6_1;  									/* input push-pull*/
		GPIOA->ODR |= GPIO_ODR_ODR6;  										/* PA6 is in Pull UP mode*/
	
		/*Interrupt configyre for BUTTON_PAUSE*/
		AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI6_PA;					/* Interrupt at port A*/
		EXTI->IMR |= BUTTON_PAUSE; 												/* Disable Int mask*/
		EXTI->FTSR |= BUTTON_PAUSE;												/* Trigger at Falling Edge*/
		
		/*Init for BUTTON_RESET pin*/
		GPIOA->CRL &= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);  /* clear bits*/
		GPIOA->CRL |= GPIO_CRL_CNF7_1;  									/* input push-pull*/
		GPIOA->ODR |= GPIO_ODR_ODR7;  										/* PA6 is in Pull UP mode*/
		
		/*Interrupt configure for BUTTON_PAUSE*/
		AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI7_PA;					/* Interrupt at port A*/
		EXTI->IMR |= BUTTON_RESET; 												/* Disable Int mask*/
		EXTI->FTSR |= BUTTON_RESET;												/* Trigger at Falling Edge*/
		
		/*Enable Interrupt*/
		NVIC_SetPriority(EXTI9_5_IRQn, 3);								
		NVIC_EnableIRQ (EXTI9_5_IRQn);		
}
