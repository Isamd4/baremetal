#include <stdint.h>
#include <stdio.h>
#include "stm32f446xx.h"



//uart2-> APB1
// we want to concentrate on TX
//goto APB2, RCC of it

//alternate functino
//uart2_TX -> PA2,AF7

//port A
#define GPIOA_EN (1U<<0)
//mode-> set 10 as alternate on
	//pos 5 and 4 respectively
//gpio alternate funi->GPIOA_AFRL
	//AFRL2 = AF7= 0111 for 11,10,9,8
#define RCC_APB1_UART2EN (1U<<17)

//default sys freq 16MHZ
#define SYS_FREQ 16000000
//in the default state the divider for the buses is 1
#define APB1_CLK SYS_FREQ

#define UART_BAUDRATE 115200

#define CR1_TE_EN (1U<<3)
#define CR1_UART_EN (1U<<13)
#define SR_TXE (1U<<7)
static void uart_set_baudRate(USART_TypeDef *USARTx,uint32_t periphClk, uint32_t baudRate);
static uint16_t compute_uart_bd(uint32_t periphClk, uint32_t baudRate);
void uart2_tx_init(void);
void uart2_write(int ch);
int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}
int main (void){


	uart2_tx_init();
	while(1){
		printf("Hello from stm32....\n\r");

	}
}

void uart2_tx_init(void){
	/**configure uart gpio pin **/
	//enable clock access to gpioa
	RCC->AHB1ENR |= GPIOA_EN;
	//set PA2 mode to alternate function
	GPIOA->MODER |= (1U<<5);
	GPIOA->MODER &= ~(1U<<4);
	//set alternate function type to UART_TX (AF07)
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	 /* Configure uart module	 */
	//enable clock access to uart2
	RCC->APB1ENR |= RCC_APB1_UART2EN;
	//configure uart baudrate
	uart_set_baudRate(USART2,APB1_CLK,UART_BAUDRATE);
	//configure transfer direction
	//this just the tx, USART_CR1
	//transmitter enable
	USART2->CR1 = CR1_TE_EN;
	//we clear everything and set TE to 1

	//enable the uart module
	USART2->CR1 |= CR1_UART_EN;


}
void uart2_write(int ch){
	//USART2->BRR & SR+TXE te;;s trie
	while(!(USART2->BRR & SR_TXE)){}
	USART2->DR = (ch & 0xFF);
	//check if the DR is empty
}
static void uart_set_baudRate(USART_TypeDef *USARTx,uint32_t periphClk, uint32_t baudRate){
	USARTx->BRR = compute_uart_bd(periphClk,baudRate);
}
static uint16_t compute_uart_bd(uint32_t periphClk, uint32_t baudRate){
	return (periphClk +(baudRate/2U))/baudRate;
}
