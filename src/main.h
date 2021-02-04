/*
 * main.h
 *
 *  Created on: Sep 17, 2019
 *      Author: Computer Market
 */

#ifndef MAIN_H_
#define MAIN_H_

/* Includes */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "mqtt.h"
#include "DHT.h"
#include "BOARD.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>


/* Private macro */
/* Private variables */
#define E_WIFI_OK			(1<<0)

#define E_MQTT_CONNACK		(1<<1)
#define E_MQTT_SUBACK		(1<<2)
#define E_MQTT_PUBACK		(1<<3)
#define E_MQTT_CONNECTED	(1<<4)

#define E_CONTROL_ON		(1<<5)
#define E_CONTROL_OFF		(1<<6)

EventGroupHandle_t		egEvents;

xSemaphoreHandle	bsDisconnectedEvent;
xSemaphoreHandle	mxWIFIRes;

volatile xQueueHandle		mqWIFIResp;


enum MQTT_state{
	MQTT_DISCONNECTED,
	MQTT_CONNECT,
	MQTT_SUBSCRIBE,
	MQTT_PUBLISH
}MQTT_State;

enum WIFI_state{
	WIFI_DISCONNECTED,
	WIFI_NETWORK_CONNECT,
	WIFI_TCP_CONNECT,
	WIFI_READY
}WIFI_State;


/* Private function prototypes */
void system_init(void);
void T_Monitor(void* pvData);
void T_Control(void* pvData);
void T_Connect(void* pvData);
void T_WIFIResHandle(void* pvData);

#endif /* MAIN_H_ */
