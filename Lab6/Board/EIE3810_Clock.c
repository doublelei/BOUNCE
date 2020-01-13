#include "stm32f10x.h"
#include "EIE3810_Clock.h"



void EIE3810_clock_tree_init(void)
{
	u8 PLL=7;//0b0111
	u8 temp=0;
	RCC->CR |= 0x00010000; //(HSEON = 0b1)HSE oscillator on
	while(!((RCC->CR>>17)&0x1));//(HSERDY)Wait until the HSE oscillator is ready
	RCC->CFGR &= 0xFFFDFFFF; //HSE clock not divided (PLL has same freq as HSE)
	RCC->CFGR |= 1<<16; //Set HSE clock as PLL input
	RCC->CFGR |= PLL<<18; //(PLLMUL = ?111)PLL input clock × 9       <---The 4th bit is undetermined?
	RCC->CR |=0x01000000;//(PLLON = 0b1)PLL on
	while(!(RCC->CR>>25));//(PLLRDY)Wait until the PLL is locked     <---Extract out the single bit?
    //(SW = 10)Set PLL as the system clock:
	RCC->CFGR &=0xFFFFFFFE;//(SW = ?0)Clear the 2nd bit of SW to 0  
	RCC->CFGR |=0x00000002;//(SW = 1?)Set the 1st bit of SW to 1     

	while(temp !=0x02) //Wait until the PLL is selected
	{
		temp=RCC->CFGR>>2;
		temp &= 0x03; //Extract out the last two bits of CFGR register (to check the state of PLL)
	}	
	RCC->CFGR &= 0xFFFFFC0F;//(HPRE = 0b0000)System AHB clock not divided; (PPRE1 = 0b?00)
	RCC->CFGR |= 0x00000400;//(PPRE1 = 0b1??) Now PPRE1 = 0b100, which is APB1 clock = PLL clock/2 = 72MHz/2 = 36MHz
	RCC->CFGR &= 0xFFFFDFFF;//(PPRE2 = 0b0??)APB2 clock = PLL =72MHz  
  	FLASH->ACR = 0x32;//Set FLASH with 2 wait states	
	RCC->APB1ENR |= 1<<17; //USART2 clock enable
	RCC->APB2ENR |= 1<<14;//USART1 clock enable
}