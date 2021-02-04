/*
 * BOARD.c
 *
 *  Created on: Apr 13, 2019
 *      Author: Computer Market
 */

#include "BOARD.h"

void Led_Init(void)
{
	/*LED PA5*/
	/*Enable Port A*/
	RCC-> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	/*Direction of PA5*/
	MODERA -> M5 = GPIO_Mode_OUT;
}
void Led_On(void)
{
	/*Set PA5*/
	GPIOA -> ODR |= GPIO_ODR_ODR_5;
}
void Led_Off(void)
{
	/*Clear PA5*/
	GPIOA -> ODR &= ~GPIO_ODR_ODR_5;
}
void Led_Toggle(void)
{
	GPIOA -> ODR ^= GPIO_ODR_ODR_5;
}

void BTN_Init(void)
{
	/*Button PC13*/
	/*Enable Port C Clock*/
	RCC-> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	/*Direction of PC13*/
	MODERC -> M13 = GPIO_Mode_IN;

}

INT8U BTN_isPressed (void)
{
	return ( (GPIOC -> IDR & GPIO_IDR_IDR_13) == 0);
}



