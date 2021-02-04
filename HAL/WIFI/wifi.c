/*
 * wifi.c
 *
 *  Created on: Aug 27, 2019
 *      Author: «·Êÿ‰Ì…
 */

#include "wifi.h"

//static const INT8U CMD_SendSize[] = "AT+CIPSEND=";
INT8U commandBuffer[WIFI_CMD_BUFFER_SIZE];
void WIFI_Init(void){
	Uart_Init(WIFI_UART,WIFI_BAUDRATE);

}
void WIFI_sendPacket(INT8U* packet,INT8U packetLen){
	sprintf(commandBuffer,"AT+CIPSEND=%d\r\n",packetLen);
	Uart_Putstring(WIFI_UART,commandBuffer);
//	DWT_Delay_us(100000);
	vTaskDelay(100*TICKS_IN_MILLISECOND);
	Uart_Putchars(WIFI_UART,packet,packetLen);
}

