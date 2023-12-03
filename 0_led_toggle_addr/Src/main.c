//blink user LED2 connected to PB7

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

//set the mode of the portb
#define GPIO_MODE_OFFSET (0x00)
#define GPIO_MODE_R (*(volatile unsigned int*)(GPIOB_BASE + GPIO_MODE_OFFSET))
//to set as output pin 7 then we need to set the mode of bit pos 14 and 15 to be 0 and 1 consec
#define GPIO_MODE_SET14 (1<<14)

//output data
#define GPIO_OUTPUTDATA_OFFSET (0x14)
#define GPIO_OUTPUTDATA_R (*(volatile unsigned int*)(GPIOB_BASE + GPIO_OUTPUTDATA_OFFSET))
#define SET_PIN7 (1<<7)

int main(void){
	RCC_AHB1EN_R |= RCC_SET_GPIOB;
	GPIO_MODE_R |= GPIO_MODE_SET14;
	GPIO_MODE_R &= ~(1<<15);
	while(1){
		GPIO_OUTPUTDATA_R ^= SET_PIN7;
		for(int i=0;i<1000000;i++){}
	}
}
