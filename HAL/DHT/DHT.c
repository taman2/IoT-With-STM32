/*
 * DHT.c
 *
 *  Created on: Sep 17, 2019
 *      Author: Computer Market
 */


#include "DHT.h"


/*
void Delay_us (INT32U u32DelayUS)
{
	INT32U i =0 ,j=0;

	for (i = 0 ; i< u32DelayUS ; i++)
	{
		for (j = 0 ; j< 2 ; j++)
		{

		}
	}
}
 */
void Request(void)
{

	GPIOA->MODER |= ( 01 << (DHT11_PIN*2) );
	GPIOA->ODR &= ~(1 << DHT11_PIN);
	DWT_Delay_us(18000);
	GPIOA->MODER &= ~( 11 << (DHT11_PIN*2) );

}

void Response(void)
{
	DWT_Delay_us(40);
	if( ((GPIOA->IDR >> DHT11_PIN) & 0x1) == 0 )
	{
		DWT_Delay_us(80);
	}
	while( ((GPIOA->IDR >> DHT11_PIN) & 0x1) == 1);


}

uint8_t Receive_data(void)
{
	uint8_t c=0;
		for (int q=0; q<8; q++)
		{
			while( ((GPIOA->IDR >> DHT11_PIN) & 0x1) == 0);
			DWT_Delay_us(40);
			if( ((GPIOA->IDR >> DHT11_PIN) & 0x1) == 0 )
				c &= ~(1<<(7-q));
			else
				c |= (1<<(7-q));
			while( ((GPIOA->IDR >> DHT11_PIN) & 0x1) == 1);
		}

//	while (1)
//	{
//
//		GPIOA->ODR &= ~(1 << DHT11_PIN);
//		DWT_Delay_us(50);
//		GPIOA->ODR |= (1 << DHT11_PIN);
//		DWT_Delay_us(50);
//	}
	return c;
}
