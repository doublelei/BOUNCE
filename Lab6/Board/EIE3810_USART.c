#include "stm32f10x.h"
#include "EIE3810_USART.h"


//USART1 initialization:
void EIE3810_USART1_init(u32 pclk2, u32 baudrate)
{
    float temp;
    u16 mantissa;
    u16 fraction;
    temp=(float) (pclk2*1000000)/(baudrate*16);
    mantissa=temp;//Automatically delete the fration part when converting float(temp) to u16(mantissa)
    fraction=(temp-mantissa)*16;//"*16" convert decimal to hexdecimal
    mantissa<<=4;//Leave the last 4 bits for fraction part
    mantissa+=fraction;//mantissa now represents the whole USARTDIV
    RCC->APB2ENR |= 1<<2;//Enable port A clock	
    GPIOA->CRH &= 0xFFFFF00F;//Clear mode setting bits for register PA9 and PA10
    GPIOA->CRH |= 0x000008B0;//(Register 9:0b1011; Register 10:0b1000)PA9 mode: max 50MHz output push-pull; PA10 mode: input pull-up/pull-down
    RCC->APB2RSTR |= 1<<14;//USART1 reset
    RCC->APB2RSTR &= ~(1<<14);//Clear USART2 reset
    USART1->BRR=mantissa;//Normalized form(bit 0 - 3: fraction; bit 4 - 11: mantissa) of transmition rate loaded to baud rate register
    USART1->CR1=0x202E;//(TE = 0b1)Transmitter enable; (UE = 0b1)USART enable

}

//USART2 initialization:
void EIE3810_USART2_init(u32 pclk1, u32 baudrate)
{//pclk1: f_CK (unit: MHz)
	float temp;
	u16 mantissa;
	u16 fraction;
	temp=(float) (pclk1*1000000)/(baudrate*16);
	mantissa=temp;//Automatically delete the fration part when converting float(temp) to u16(mantissa)
	fraction=(temp-mantissa)*16;//"*16" convert decimal to hexdecimal
	mantissa<<=4;//Leave the last 4 bits for fraction part
	mantissa+=fraction; //mantissa now represents the whole USARTDIV
	RCC->APB2ENR |= 1<<2; //Enable port A clock	
	GPIOA->CRL &= 0xFFFF00FF; //Clear mode setting bits for register PA2 and PA3
	GPIOA->CRL |= 0x00008B00; //(Register 2:0b1011; Register 3:0b1000)PA2 mode: max 50MHz output push-pull; PA3 mode: input pull-up/pull-down
	RCC->APB1RSTR |= 1<<17; //USART2 reset
	RCC->APB1RSTR &= ~(1<<17); //Clear USART2 reset
	USART2->BRR=mantissa;//Normalized form of transmition rate loaded to baud rate register
	USART2->CR1=0x2008; //(TE = 0b1)Transmitter enable; (UE = 0b1)USART enable
}

//Port select and string transmit:
void USART_print(u8 USARTport, char *st)
{//USARTport: port number; st: string to transmit
	u8 i=0;
	while(st[i] != 0x00)
	{
		if (USARTport == 1) {
			USART1->DR =st[i];
			while (!((USART1->SR>>7)&0x1));   //<=== Replace Delay() with TXT register bit checker
		}
		
		if (USARTport == 2) {
			USART2->DR =st[i]; 
			while (!((USART2->SR>>7)&0x1));   //<=== Replace Delay() with TXT register bit checker
		}

		if (i==255) break;
		i++;
	}
}

