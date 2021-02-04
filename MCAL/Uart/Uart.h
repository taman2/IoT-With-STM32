/*
 * Uart.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: cisco126
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32f4xx.h"
#include "Data_types.h"

typedef enum {
	USART_1=1 ,USART_2=2 ,USART_6=6 //moawad beeeh
	}USART_type;

void Uart_Init(USART_type USART_NUM, INT32U u32Buadrate);
void Uart_Putchar(USART_type USART_NUM,INT8U u8data );
void Uart_Putchars(USART_type USART_NUM,INT8U* Pu8data ,INT8U buffersize  );
void Uart_Putstring(USART_type USART_NUM,INT8U* pu8str );

INT8U Uart_Getchar( USART_type USART_NUM );
Bool Uart_Getchar_Unblock(USART_type USART_NUM, INT8U* Pu8data  );





#endif /* INC_UART_H_ */
