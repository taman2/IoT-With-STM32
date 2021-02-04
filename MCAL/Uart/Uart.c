/*
 * Uart.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: cisco126
 */

#include "Uart.h"


void Uart_Init(USART_type USART_NUM, INT32U u32Buadrate){	/*usart2 ,  TX:PA2 , RX:PA3 , RCC:APB1 , CR1 , AF7 */
	float USARTDIV=0;
	INT32U intpart=10;
	INT32U fractpart=10;
	RCC_DeInit();
	SystemCoreClockUpdate();
	/*BRR*/
	USARTDIV = ((SystemCoreClock) / (16.0*u32Buadrate));
	intpart = (INT32U)USARTDIV;
	fractpart = (USARTDIV - intpart )*16 ;

	switch (USART_NUM)
	{
	case USART_1:
		/*RCC */
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; /* RCC for port A */
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN; /* RCC for USART1 */
		/*Pin set as alternative function usart2*/
		GPIOA->MODER &= ~ GPIO_MODER_MODER9_0 ; /*clear PA2 bit0 */
		GPIOA->MODER |=   GPIO_MODER_MODER9_1 ; /*set   PA2 bit1 */

		GPIOA->MODER &= ~ GPIO_MODER_MODER10_0 ; /*clear PA3 bit0 */
		GPIOA->MODER |=   GPIO_MODER_MODER10_1 ; /*set   PA3 bit1 */

		/*set Pin as alternative function usart1= AF7  */
		GPIOA->AFR[1] |= (7<<4);  /*set  PA2 mask AF7 0111 */
		GPIOA->AFR[1] &= ~(8<<4); /*clear PA2 mask AF7 1000 */

		GPIOA->AFR[1] |= (7<<8); /*set  PA3 mask AF7 0111 */
		GPIOA->AFR[1] &= ~(8<<8); /*clear PA3 mask AF7 1000 */



		USART1->BRR = (intpart<<4)+fractpart;
		USART1->CR1 = (USART_CR1_RXNEIE|USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
		//USART1->CR1 |= (USART_CR1_RXNEIE);
		NVIC_SetPriority(USART1_IRQn,6);
		NVIC_EnableIRQ(USART1_IRQn);
		__enable_irq();
		break;

	case USART_2:
		/*RCC */
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; /* */
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN; /* */
		/*Pin set as alternative function usart2*/
		GPIOA->MODER &= ~ GPIO_MODER_MODER2_0 ; /*clear PA2 bit0 */
		GPIOA->MODER |=   GPIO_MODER_MODER2_1 ; /*set   PA2 bit1 */
		GPIOA->MODER &= ~ GPIO_MODER_MODER3_0 ; /*clear PA3 bit0 */
		GPIOA->MODER |=   GPIO_MODER_MODER3_1 ; /*set   PA3 bit1 */

		/*set Pin as alternative function usart2= AF7  */
		GPIOA->AFR[0] |= (7<<8);  /*set  PA2 mask AF7 0111 */
		GPIOA->AFR[0] &= ~(8<<8); /*clear PA2 mask AF7 1000 */
		GPIOA->AFR[0] |= (7<<12); /*set  PA3 mask AF7 0111 */
		GPIOA->AFR[0] &= ~(8<<12); /*clear PA3 mask AF7 1000 */



		USART2->BRR = (intpart<<4)+fractpart;
		USART2->CR1 = (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
		break;

	case USART_6:
		/*RCC */
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; /* */
		RCC->APB2ENR |= RCC_APB2ENR_USART6EN; /* RCC for USART1 */
		/*Pin set as alternative function usart2*/
		GPIOA->MODER &= ~ GPIO_MODER_MODER11_0 ; /*clear PA2 bit0 */
		GPIOA->MODER |=   GPIO_MODER_MODER11_1 ; /*set   PA2 bit1 */
		GPIOA->MODER &= ~ GPIO_MODER_MODER12_0 ; /*clear PA3 bit0 */
		GPIOA->MODER |=   GPIO_MODER_MODER12_1 ; /*set   PA3 bit1 */

		/*set Pin as alternative function usart6= AF8  */
		GPIOA->AFR[1] |= (8<<12);  /*set  PA2 mask AF8 1000 */
		GPIOA->AFR[1] &= ~(7<<12); /*clear PA2 mask AF8 0111 */
		GPIOA->AFR[1] |= (8<<16); /*set  PA3 mask AF8 1000*/
		GPIOA->AFR[1] &= ~(7<<16); /*clear PA3 mask AF8 0111 */



		USART6->BRR = (intpart<<4)+fractpart;
		USART6->CR1 = (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
		break;

	default :
		break;


	}

}


void Uart_Putchar(USART_type USART_NUM,INT8U u8data ){
	//while(!(USART2->SR & USART_SR_TXE));
	//USART2->DR = u8data;
	switch (USART_NUM)
	{
	case USART_1:
		while(!(USART1->SR & USART_SR_TXE));
		USART1->DR = u8data;
		break;

	case USART_2:
		while(!(USART2->SR & USART_SR_TXE));
		USART2->DR = u8data;
		break;

	case USART_6:
		while(!(USART6->SR & USART_SR_TXE));
		USART6->DR = u8data;
		break;
	default :
		break;

	}

}


void Uart_Putstring(USART_type USART_NUM,INT8U* pu8str ){
	while(*pu8str){
		Uart_Putchar(USART_NUM,*pu8str);
		pu8str++;
	}
}


INT8U Uart_Getchar( USART_type USART_NUM ){
	// while(!(USART2->SR & USART_SR_RXNE));
	// return (USART2->DR);
	//if(USART2->SR & USART_SR_RXNE)
	//{
	//	return (USART2->DR);
	//	}
	//	else
	//		return (0);
	switch (USART_NUM)
	{

	case USART_1:
		while(!(USART1->SR & USART_SR_RXNE));
		return (USART1->DR);
		break;

	case USART_2:
		while(!(USART2->SR & USART_SR_RXNE));
		return (USART2->DR);
		break;

	case USART_6:

		while(!(USART6->SR & USART_SR_RXNE));
		return (USART6->DR);
		break;

	default :
		break;

	}
	return (0);
}

Bool Uart_Getchar_Unblock(USART_type USART_NUM, INT8U* Pu8data  ){
	switch (USART_NUM)
	{
	case USART_1:
		if(USART1->SR & USART_SR_RXNE)
		{*Pu8data = USART1->DR; return (TRUE);  }
		else
			return (FALSE);
		break;

	case USART_2:
	{
		if(USART2->SR & USART_SR_RXNE)
		{*Pu8data = USART2->DR; return (TRUE);  }
		else
			return (FALSE);
	}
	break;

	case USART_6:
	{
		if(USART6->SR & USART_SR_RXNE)
		{*Pu8data = USART6->DR; return (TRUE);  }
		else
			return (FALSE);
	}
	break;

	default :
		break;
	}

	return (FALSE);
}

void Uart_Putchars(USART_type USART_NUM,INT8U* Pu8data ,INT8U buffersize  ){
	while(buffersize){
		Uart_Putchar(USART_NUM,*Pu8data);
		Pu8data++;
		buffersize--;
	}

}
