/*
 * BOARD.h
 *
 *  Created on: Apr 13, 2019
 *      Author: Computer Market
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "stm32f4xx.h"
#include "data_types.h"


typedef struct {

	INT32U M0 : 2;
	INT32U M1 : 2;
	INT32U M2 : 2;
	INT32U M3 : 2;
	INT32U M4 : 2;
	INT32U M5 : 2;
	INT32U M6 : 2;
	INT32U M7 : 2;
	INT32U M8 : 2;
	INT32U M9 : 2;
	INT32U M10 : 2;
	INT32U M11 : 2;
	INT32U M12 : 2;
	INT32U M13: 2;
	INT32U M14 : 2;
	INT32U M15 : 2;

}MODER_BFD;

#define MODERA  ((volatile MODER_BFD *)(&(GPIOA-> MODER)))
#define MODERC  ((volatile MODER_BFD *)(&(GPIOC-> MODER)))

void Led_Init(void);
void Led_On(void);
void Led_Off(void);
void Led_Toggle(void);

void BTN_Init(void);

INT8U BTN_isPressed (void);



#endif /* BOARD_H_ */
