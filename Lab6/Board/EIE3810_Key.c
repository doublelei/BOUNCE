#include "stm32f10x.h"
#include "EIE3810_KEY.h"


void EIE3810_Key_Init(void){
	//Enable PE clock
	RCC->APB2ENR |=1<<6;
	//Enable PA clock
	RCC->APB2ENR |=1<<2;
	
	//Configure button PE2
	GPIOE->CRL &=0xFFFFF0FF;// (4-bit a register, starting from register 0) Clear up
	GPIOE->CRL |=0x00000800;//Set register PE2's mode as input (xx00) pull-up/pull-down (10xx)
	
	//Configure button PE3
	GPIOE->CRL &=0xFFFF0FFF;
	GPIOE->CRL |=0x00008000;
	
	//Configure button PE4
	GPIOE->CRL &=0xFFF0FFFF;
	GPIOE->CRL |=0x00080000;

	//Configure button PA0
	GPIOA->CRL &=0xFFFFFFF0;
	GPIOA->CRL |=0x00000008;
	
	//Set both PE2, PE3 and PE4 as pull-up
	GPIOE ->ODR = 0x0000001C;
	
	//Set PA0 as pull-down
	GPIOA ->ODR = 0x00000000;
}
