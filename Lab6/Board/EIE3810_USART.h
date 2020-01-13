#ifndef __EIE3810_USART_H
#define __EIE3810_USART_H
#include "stm32f10x.h"

//USART1 initialization:
void EIE3810_USART1_init(u32, u32);

//USART2 initialization:
void EIE3810_USART2_init(u32, u32);

//Port select and string transmit:
void USART_print(u8, char*);

#endif
