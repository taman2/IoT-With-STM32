/*
 * mqtt.c
 *
 * Created: 02/09/2019 11:10:30 ص
 *  Author: MahmoudH
 */ 
#include "mqtt.h"

static void sendUTFString(uint8_t* pu8Str);


const uint8_t protocolName[] 	= "MQTT";
uint8_t packetBuffer[150]		= {0};
uint8_t packetBufferInd			= 0;
uint16_t packetID				= 1;

/* Assume: Packet Len <= 127 */
void MQTT_GetMsg(uint8_t* pu8PubPacket,uint8_t* pu8MsgStartInd,uint8_t* pu8Msglen){
	if(pu8PubPacket[0] == 0x30){ /* qos = 0 */
		(*pu8MsgStartInd)	= 4 + pu8PubPacket[3];
		(*pu8Msglen)		= 2 + pu8PubPacket[1] - (*pu8MsgStartInd);
	}
	else{

	}
}
void MQTT_Init(void){
	WIFI_Init();
}
void MQTT_Connect(uint8_t* pu8ID){
	uint8_t u8RemLen = 2 + strlen(protocolName) + 1 + 1 + 2 + 2 + strlen(pu8ID);
	packetBufferInd	= 0;
	packetBuffer[packetBufferInd++] = 0x10;				/* Type */
	packetBuffer[packetBufferInd++] = u8RemLen;			/* RL */
	sendUTFString(protocolName);						/* Pro. Name */
	packetBuffer[packetBufferInd++] = 0x04;				/* Pro. Level */
	packetBuffer[packetBufferInd++] = 0x02;				/* Flags */
	packetBuffer[packetBufferInd++] = 0xFF;				/* KAT MSB*/
	packetBuffer[packetBufferInd++] = 0xFF;				/* KAT LSB*/
	sendUTFString(pu8ID);								/* Client ID */
	WIFI_sendPacket(packetBuffer,packetBufferInd);
}
void MQTT_Publish(uint8_t* pu8Topic,uint8_t* pu8Msg,uint8_t u8MsgLen,uint8_t u8QoS){
	uint8_t u8RemLen = 2 + strlen(pu8Topic) + u8MsgLen;
	uint8_t i = 0;
	packetBufferInd	= 0;
	if(u8QoS > 0){
		u8RemLen = u8RemLen + 2;
		packetBuffer[packetBufferInd++] = 0x32;						/* Type */
	}else{
		packetBuffer[packetBufferInd++] = 0x30;						/* Type */
	}
	packetBuffer[packetBufferInd++] = u8RemLen;						/* RL */
	sendUTFString(pu8Topic);										/* Topic */

	if(u8QoS > 0){
		/* Packet ID */
		packetBuffer[packetBufferInd++] = (uint8_t)(packetID>>8);	/* MSB */
		packetBuffer[packetBufferInd++] = (uint8_t)(packetID);		/* LSB */
		packetID++;
	}
	for (i = 0; i < u8MsgLen; ++i) {
		packetBuffer[packetBufferInd++] = pu8Msg[i];
	}
	WIFI_sendPacket(packetBuffer,packetBufferInd);
}
void MQTT_Subscribe(uint8_t* pu8Topic){
	uint8_t u8RemLen = 2 + 2 + strlen(pu8Topic) + 1;
	packetBufferInd	= 0;
	packetBuffer[packetBufferInd++] = 0x82;				/* Type */
	packetBuffer[packetBufferInd++] = u8RemLen;			/* RL */

	/* Packet ID */
	packetBuffer[packetBufferInd++] = (uint8_t)(packetID>>8);	/* MSB */
	packetBuffer[packetBufferInd++] = (uint8_t)(packetID);		/* LSB */
	packetID++;

	sendUTFString(pu8Topic);										/* Topic */

	packetBuffer[packetBufferInd++] = 0x01;				/* Req-QoS */
	WIFI_sendPacket(packetBuffer,packetBufferInd);
}
static void sendUTFString(uint8_t* pu8Str){
		packetBuffer[packetBufferInd++] = 0x00;				/* MSB */
		packetBuffer[packetBufferInd++] = strlen(pu8Str);	/* LSB */
		while(*pu8Str){
			packetBuffer[packetBufferInd++] = (*pu8Str);
			pu8Str++;
		}
}
