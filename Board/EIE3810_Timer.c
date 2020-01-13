#include "stm32f10x.h"
#include "EIE3810_Timer.h"


void EIE3810_TIM3_Init(u16 arr, u16 psc)
{
    //TIM3 initialization:
    RCC->APB1ENR |= 1<<1;//TIM3 clock enable
    TIM3->ARR = arr;//Set auto-reload value
    TIM3->PSC = psc;//Set prescalar value
    TIM3->CR1 |= 0x01;//TIM3 counter enable
    //TIM3 interrupt initialization:
    TIM3->DIER |= 1<<0;//Update interrupt enable
    NVIC->IP[29] = 0x45;//Set priority of interrupt #29 (i.e. interrupt from TIM3) to 0b0100 0101
    NVIC->ISER[0] = (1<<29);//Enable interrupt #29 (i.e. interrupt from TIM3)
}

void EIE3810_SYSTICK_Init(u32 load)
{
    SysTick->CTRL = 0;
    SysTick->LOAD = load;
    SysTick->CTRL = 0x00000003;
}