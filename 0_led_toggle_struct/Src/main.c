
//blink user LED2 connected to PB7
#include <stdint.h>
//we need to get the perpheral base
#define PERIPH_BASE (0x40000000)

//need to get the bus for which the port is connected to -> AHB1
#define AHB1_OFFSET (0x00020000)
#define AHB1_BASE	(PERIPH_BASE+AHB1_OFFSET)

//need to know the location of the switch to AHB1 for PORTB -> RCC
#define RCC_OFFSET (0x3800)
#define RCC_BASE (AHB1_BASE + RCC_OFFSET)

//GPIO PORT B
#define GPIOB_OFFSET (0x00000400)
#define GPIOB_BASE (AHB1_BASE + GPIOB_OFFSET)

//Enable the rcc
#define RCC_AHB1ENR_OFFSET (0x30)
#define RCC_AHB1EN_R (*(volatile unsigned int*)(RCC_BASE + RCC_AHB1ENR_OFFSET))
#define RCC_SET_GPIOB (1<<1)

#define GPIO_MODE_SET14 (1<<14)


#define SET_PIN7 (1<<7)



typedef struct{
	volatile uint32_t GPIO_MODER;
	volatile uint32_t GPIO_OTYPER;
	volatile uint32_t GPIO_OSPEEDR;
	volatile uint32_t GPIO_PUPDR;
	volatile uint32_t GPIO_IDR;
	volatile uint32_t GPIO_ODR;
	volatile uint32_t GPIO_BSRR;
	volatile uint32_t GPIO_LCKR;
	volatile uint32_t GPIO_AFRL;
	volatile uint32_t GPIO_AFRH;

}GPIO_STRUCT;

typedef struct{
	volatile uint32_t OTHERS[12];
	volatile uint32_t AHB1ENR;
}RCC_STRUCT;
#define GPIOB ((GPIO_STRUCT*)GPIOB_BASE)
#define RCC ((RCC_STRUCT*)RCC_BASE)
int main(void){
	RCC->AHB1ENR |= RCC_SET_GPIOB;
	GPIOB->GPIO_MODER |= GPIO_MODE_SET14;
	GPIOB->GPIO_MODER &= ~(1<<15);
	while(1){
		GPIOB->GPIO_ODR ^= SET_PIN7;
		for(int i=0;i<100000;i++){}
	}
}
