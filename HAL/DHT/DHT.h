/*
 * DHT.h
 *
 *  Created on: Sep 17, 2019
 *      Author: Computer Market
 */

#ifndef DHT_DHT_H_
#define DHT_DHT_H_

#include "data_types.h"
#include "stm32f4xx.h"
#include "BOARD.h"
#include "dwt_stm32_delay.h"


#define DHT11_PIN 8

//void Delay_us (INT32U u32DelayUS);
void Response(void);
void Request(void);
INT8U Receive_data(void);

#endif /* DHT_DHT_H_ */
