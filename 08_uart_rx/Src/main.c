#include <stdint.h>
#include <stdio.h>
#include "stm32f446xx.h"
#include "uart.h"




int main (void){


	uart2_tx_init();
	while(1){
		printf("Hello from stm32....\n\r");

	}
}



