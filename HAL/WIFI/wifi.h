/*
 * wifi.h
 *
 *  Created on: Aug 27, 2019
 *      
  */

#ifndef WIFI_WIFI_H_
#define WIFI_WIFI_H_

#include "FreeRTOS.h"
#include "task.h"
#include "dwt_stm32_delay.h"
#include "Uart.h"
#include "stdio.h"

#define WIFI_UART					USART_1
#define WIFI_BAUDRATE				9600

#define WIFI_CMD_BUFFER_SIZE		500

void WIFI_Init(void);
void WIFI_sendPacket(INT8U* packet,INT8U packetLen);

#endif /* WIFI_WIFI_H_ */
