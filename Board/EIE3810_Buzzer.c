#include "stm32f10x.h"
#include "EIE3810_Buzzer.h"


void EIE3810_Buzzer_Init(void){
	//Enable PB clock
	RCC->APB2ENR |=1<<3;
	
	//Configure buzzer PB8
	GPIOB->CRH &=0xFFFFFFF0;//(4-bit a register, starting from register 0) Clear up
	GPIOB->CRH |=0x00000003;//Set register PB8's mode as 50Hz output (xx11) general push-pull (00xx)
	GPIOB->BRR = 1<<8;//(1-bit a register) Set register PB8 to 0 (off)
}