#include "stm32f10x.h"
#include "EIE3810_Interrupt.h"

void EIE3810_NVIC_SetPriorityGroup(u8 prigroup)
{
    u32 temp1, temp2;
    temp2 = prigroup & 0x00000007;
    temp2 <<= 8;//Why? Priority group setting is from 8th bit of SCB->AIRCR
    temp1 = SCB->AIRCR;//Access all bits of SCB->AIRCR
    temp1 &= 0x0000F8FF;//Reset VECTKEY/VECTKEYSTAT (upper 16 bits) and PRIGROUP (bit 10:8), 
                        //while masking the rest
    temp1 |= 0x05FA0000;//Set VECTKEY/VECTKEYSTAT
    temp1 |= temp2;
    SCB->AIRCR = temp1;
}


void EIE3810_Key2_EXTIInit(void)
{
    RCC->APB2ENR |= 1<<6;//(IOPEEN = 1)IO port E clock enable
    GPIOE->CRL &= 0xFFFFF0FF;//(Register2 of port E)Input mode, Analog mode
    GPIOE->CRL |= 0x00000800;//(Register2 of port E)Input mode, Input with pull-up/pull-down
    GPIOE->ODR |= 1<<2;//(Register2 of port E)Input pull-up
    RCC->APB2ENR |= 0x01;//(AFIOEN = 1)Alternate Function IO clock enable
    AFIO->EXTICR[0] &= 0xFFFFF0FF;//(AFIO_EXTICR1)EXTI2 reset
    AFIO->EXTICR[0] |= 0x00000400;//(AFIO_EXTICR1)EXTI2 connect to PE2
    EXTI->IMR |= 1<<2;//(Interrupt Mask Register)Mask all interrupts except IRQ from line EXTI2
    
    EXTI->FTSR |= 1<<2;//(Falling trigger selection register)Falling trigger enabled for line EXTI2
	//EXTI->RTSR |= 1<<2;//(Rising trigger selection register)Rising trigger enabled for line EXTI2
    
    NVIC->IP[8] = 0x65;//(Interrupt Priority)Interrupt #8 priority set to 0b0110 0101
    NVIC->ISER[0] |= (1<<8);//(Interrupt Enable)Enable interrupt #8
}

void EIE3810_KeyUp_EXTIInit(void)
{
    RCC->APB2ENR |= 1<<2;//(IOPAEN = 1)IO port A clock enable
    GPIOA->CRL &= 0xFFFFFFF0;//(Register0 of port A)Input mode, Analog mode
    GPIOA->CRL |= 0x00000008;//(Register0 of port A)Input mode, Input with pull-up/pull-down
    GPIOA->ODR = 0x00000000;//(Register0 of port A)Input pull-down
    RCC->APB2ENR |= 0x01;//(AFIOEN = 1)Alternate Function IO clock enable
    AFIO->EXTICR[0] &= 0xFFFFFFF0;//(AFIO_EXTICR1)EXTI0 reset
    AFIO->EXTICR[0] |= 0x00000000;//(AFIO_EXTICR1)EXTI0 connect to PA0
    EXTI->IMR |= 1<<0;//(Interrupt Mask Register)Mask all interrupts except IRQ from line EXTI0

    //EXTI->FTSR |= 1<<0;//(Falling trigger selection register)Falling trigger enabled for line EXTI0
	EXTI->RTSR |= 1<<0;//(Rising trigger selection register)Rising trigger enabled for line EXTI0

    NVIC->IP[6] = 0x65;//(Interrupt Priority)Interrupt #6 priority set to 0b0110 0101
    NVIC->ISER[0] |= (1<<6);//(Interrupt Enable)Enable interrupt #6
}


void EIE3810_Key0_EXTIInit(void)
{
    RCC->APB2ENR |= 1<<6;//(IOPEEN = 1)IO port E clock enable
    GPIOE->CRL &= 0xFFF0FFFF;//(Register4 of port E)Input mode, Analog mode
    GPIOE->CRL |= 0x00080000;//(Register4 of port E)Input mode, Input with pull-up/pull-down
    GPIOE->ODR |= 1<<4;//(Register4 of port E)Input pull-up
    RCC->APB2ENR |= 0x01;//(AFIOEN = 1)Alternate Function IO clock enable
    AFIO->EXTICR[1] &= 0xFFFFFFF0;//(AFIO_EXTICR1)EXTI4 reset
    AFIO->EXTICR[1] |= 0x00000004;//(AFIO_EXTICR1)EXTI4 connect to PE4
    EXTI->IMR |= 1<<4;//(Interrupt Mask Register)Mask all interrupts except IRQ from line EXTI4
    
    EXTI->FTSR |= 1<<4;//(Falling trigger selection register)Falling trigger enabled for line EXTI4
	//EXTI->RTSR |= 1<<4;//(Rising trigger selection register)Rising trigger enabled for line EXTI4
    
    NVIC->IP[10] = 0x65;//(Interrupt Priority)Interrupt #10 priority set to 0b0110 0101
    NVIC->ISER[0] |= (1<<10);//(Interrupt Enable)Enable interrupt #10
}

void EIE3810_Key1_EXTIInit(void)
{
    RCC->APB2ENR |= 1<<6;//(IOPEEN = 1)IO port E clock enable
    GPIOE->CRL &= 0xFFFF0FFF;//(Register3 of port E)Input mode, Analog mode
    GPIOE->CRL |= 0x00008000;//(Register3 of port E)Input mode, Input with pull-up/pull-down
    GPIOE->ODR |= 1<<3;//(Register3 of port E)Input pull-up
    RCC->APB2ENR |= 0x01;//(AFIOEN = 1)Alternate Function IO clock enable
    AFIO->EXTICR[0] &= 0xFFFF0FFF;//(AFIO_EXTICR1)EXTI3 reset
    AFIO->EXTICR[0] |= 0x00004000;//(AFIO_EXTICR1)EXTI3 connect to PE3
    EXTI->IMR |= 1<<3;//(Interrupt Mask Register)Mask all interrupts except IRQ from line EXTI3
    
    EXTI->FTSR |= 1<<3;//(Falling trigger selection register)Falling trigger enabled for line EXTI3
	//EXTI->RTSR |= 1<<3;//(Rising trigger selection register)Rising trigger enabled for line EXTI3
    
    NVIC->IP[9] = 0x65;//(Interrupt Priority)Interrupt #9 priority set to 0b0110 0101
    NVIC->ISER[0] |= (1<<9);//(Interrupt Enable)Enable interrupt #9
}

void EIE3810_USART1_EXTIInit(void)
{
	NVIC -> IP[37] = 0x65;
	NVIC -> ISER[1] |= 1<<5;
}