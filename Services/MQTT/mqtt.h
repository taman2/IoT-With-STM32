/*
 * mqtt.h
 *
 * Created: 02/09/2019 11:10:43 ص
 *  Author: MahmoudH
 */ 


#ifndef MQTT_H_
#define MQTT_H_

#include "wifi.h"
#include "stdint.h"
#include "string.h"

void MQTT_Init(void);
void MQTT_Connect(uint8_t* pu8ID);
void MQTT_Publish(uint8_t* pu8Topic,uint8_t* pu8Msg,uint8_t u8MsgLen,uint8_t u8QoS);
void MQTT_Subscribe(uint8_t* pu8Topic);
void MQTT_GetMsg(uint8_t* pu8PubPacket,uint8_t* pu8MsgStartInd,uint8_t* pu8Msglen);


#endif /* MQTT_H_ */
