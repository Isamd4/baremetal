#include "stm32f446xx.h"
//the button is connected to pc13
//port C
//pin 13

#define GPIOBEN (1U<<1)
#define GPIOCEN (1U<<2)
#define PIN7	(1U<<7)
#define PIN13	(1U<<13)
#define SET7 PIN7
#define RESET7 (1U<<23)
#define BTN_PIN PIN13
int main (void){

	RCC->AHB1ENR |= GPIOBEN;
	RCC->AHB1ENR |= GPIOCEN;

	GPIOB->MODER |= (1U<<14);
	GPIOB->MODER &= ~(1U<<15);

	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);
	while(1){
		int get_pin13 = (GPIOC->IDR & BTN_PIN)<<0;
		if(!get_pin13){
		GPIOB->BSRR = SET7;
		}
		else{
		GPIOB->BSRR = RESET7;
		}
	}
}
