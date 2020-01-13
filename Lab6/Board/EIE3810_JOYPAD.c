#include "stm32f10x.h"
#include "EIE3810_JOYPAD.h"

void JOYPAD_Init(void)
{
    //Initialize PB11 and PD3 as output pin, PB10 as input pin:
    RCC->APB2ENR |= 1 << 3;//Enable portB clock
    RCC->APB2ENR |= 1 << 5;//Enable portD clock
    GPIOB->CRH &= 0xFFFF00FF;//Reset PB10 PB11 control register
    GPIOB->CRH |= 0x00003800;//PB10: Input pull-up/pull-down mode; PB11: Output push-pull mode with max speed 50MHz
    GPIOB->ODR |= 3<<10;//Set PB10 and PB11 output data to 1
    GPIOD->CRL &= 0xFFFF0FFF;//Reset PD3 control register
    GPIOD->CRL |= 0x00003000;//PD3: Output push-pull mode with max speed 50MHz
    GPIOD->ODR |= 1<<3;//Set PD3 output data to 1
}

u8 JOYPAD_Read(void)
{
    vu8 temp = 0; 
    u8 t;
    //Pulse of PB11 to indicate the start of JOYPAD reading:
    GPIOB->BSRR |= (1<<11);//PB11 set to 1
    Delay(80);//Pulse width of PB11
    GPIOB->BSRR |= (1<<27);//PB11 reset to 0
    for (t=0;t<8;t++)
    {
        temp >>= 1;//
        if ((((GPIOB->IDR)>>10)&0x01)==0) temp |= 0x80;//When input to PB10 is 0 (i.e. a key is pressed), 
                                                        //set the first bit of an 8-bit number to 1,
                                                        //start to count the corresponding bit of the pressed key
                                                        //in order to find the key
        GPIOD->BSRR |= (1<<3);//PD3 set to 1
        Delay(80);//Pulse width of PD3
        GPIOD->BSRR |= (1<<19);//PD3 reset to 0
        Delay(80);
    }
    return temp;
}