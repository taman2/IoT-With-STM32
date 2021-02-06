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
void ESP_Init (char *SSID, char *PASSWD)
{
	char data[80];

	Ringbuf_init();

	Uart_sendstring("AT+RST\r\n", wifi_uart);
	Uart_sendstring("RESETTING.", pc_uart);
	for (int i=0; i<5; i++)
	{
		Uart_sendstring(".", pc_uart);
		HAL_Delay(1000);
	}

	/********* AT **********/
	Uart_sendstring("AT\r\n", wifi_uart);
	while(!(Wait_for("AT\r\r\n\r\nOK\r\n", wifi_uart)));
	Uart_sendstring("AT---->OK\n\n", pc_uart);


	/********* AT+CWMODE=1 **********/
	Uart_sendstring("AT+CWMODE=1\r\n", wifi_uart);
	while (!(Wait_for("AT+CWMODE=1\r\r\n\r\nOK\r\n", wifi_uart)));
	Uart_sendstring("CW MODE---->1\n\n", pc_uart);


	/********* AT+CWJAP="SSID","PASSWD" **********/
	Uart_sendstring("connecting... to the provided AP\n", pc_uart);
	sprintf (data, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWD);
	Uart_sendstring(data, wifi_uart);
	while (!(Wait_for("WIFI GOT IP\r\n\r\nOK\r\n", wifi_uart)));
	sprintf (data, "Connected to,\"%s\"\n\n", SSID);
	Uart_sendstring(data,pc_uart);


	/********* AT+CIFSR **********/
	Uart_sendstring("AT+CIFSR\r\n", wifi_uart);
	while (!(Wait_for("CIFSR:STAIP,\"", wifi_uart)));
	while (!(Copy_upto("\"",buffer, wifi_uart)));
	while (!(Wait_for("OK\r\n", wifi_uart)));
	int len = strlen (buffer);
	buffer[len-1] = '\0';
	sprintf (data, "IP ADDR: %s\n\n", buffer);
	Uart_sendstring(data, pc_uart);


	Uart_sendstring("AT+CIPMUX=1\r\n", wifi_uart);
	while (!(Wait_for("AT+CIPMUX=1\r\r\n\r\nOK\r\n", wifi_uart)));
	Uart_sendstring("CIPMUX---->OK\n\n", pc_uart);

	Uart_sendstring("AT+CIPSERVER=1,80\r\n", wifi_uart);
	while (!(Wait_for("OK\r\n", wifi_uart)));
	Uart_sendstring("CIPSERVER---->OK\n\n", pc_uart);

	Uart_sendstring("Now Connect to the IP ADRESS\n\n", pc_uart);

}
