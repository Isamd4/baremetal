#include "stm32f446xx.h"

#define GPIOBEN (1U << 1)
#define PIN7	(1U << 7)
#define LED_PIN PIN7

int main (void){

	RCC->AHB1ENR |= GPIOBEN;

	GPIOB->MODER |= (1U<<14);
	GPIOB->MODER &= ~(1U<<15);
	while(1){
		GPIOB->ODR ^=LED_PIN;
		for(int i=0;i<1000000;i++){}
	}
}
