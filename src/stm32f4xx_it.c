/**
 ******************************************************************************
 * @file    Project/STM32F4xx_StdPeriph_Template/stm32f4xx_it.c
 * @author  MCD Application Team
 * @version V1.1.0
 * @date    18-January-2013
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"

/** @addtogroup Template_Project
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief   This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
/*void SVC_Handler(void)
{
}
 */
/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
/*void PendSV_Handler(void)
{
}*/

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
	/*  TimingDelay_Decrement(); */
	osSystickHandler();
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s).                         */
/******************************************************************************/

/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */
/*void PPP_IRQHandler(void)
{
}*/

/**
 * @}
 */
extern volatile xQueueHandle mqWIFIResp;

volatile xHigherPriorityTaskWoken = pdFALSE;

volatile INT8U u8Char = 0;
volatile INT8U msgBuffer[80] = {0};
volatile INT8U msgBufferInd = 0;

volatile INT8U rawDataBuffer[4] = {0};
volatile INT8U rawDataBufferInd = 0;
volatile INT8U rawDataLen = 0;

enum RECV_state{
	RECV_NONE,RECV_PLUS,RECV_I,RECV_P,RECV_D,RECV_COMMA,RECV_DDOT,RECV_NORMAL_RESP
}RECV_State = RECV_NONE;


void USART1_IRQHandler(void){
	if(Uart_Getchar_Unblock(WIFI_UART,&u8Char)){
		//Uart_Putchar(USART_2,u8Char);
		switch (RECV_State) {
		case RECV_NONE:
			if(u8Char == '+'){
				RECV_State = RECV_PLUS;
			}
			else{
				if(u8Char != '\n' && msgBufferInd < 80){
					msgBuffer[msgBufferInd++] = u8Char;
				}else{
					if(msgBufferInd>1){
						msgBuffer[80-1] = msgBufferInd;
						xQueueSendFromISR(mqWIFIResp,msgBuffer,&xHigherPriorityTaskWoken);
						if(xHigherPriorityTaskWoken){
							portYIELD();
						}
					}
					msgBufferInd = 0;
					RECV_State = RECV_NONE;
				}
			}
			break;
		case RECV_PLUS:
			if(u8Char == 'I'){
				RECV_State = RECV_I;
			}
			else{
				RECV_State = RECV_NONE;
			}
			break;
		case RECV_I:
			if(u8Char == 'P'){
				RECV_State = RECV_P;
			}
			else{
				RECV_State = RECV_NONE;
			}
			break;
		case RECV_P:
			if(u8Char == 'D'){
				RECV_State = RECV_D;
			}
			else{
				RECV_State = RECV_NONE;
			}
			break;
		case RECV_D:
			if(u8Char == ','){
				RECV_State = RECV_COMMA;
				rawDataBufferInd = 0;
			}
			else{
				RECV_State = RECV_NONE;
			}
			break;
		case RECV_COMMA:
			if(u8Char == ':'){
				RECV_State = RECV_DDOT;
				rawDataBuffer[rawDataBufferInd] = 0;
				rawDataLen = atoi(rawDataBuffer);
				rawDataBufferInd = 0;
				msgBufferInd = 0;
			}else{
				rawDataBuffer[rawDataBufferInd++] = u8Char;
			}
			break;
		case RECV_DDOT:
			// Receive the raw data
			if(msgBufferInd<(rawDataLen)){
				if(msgBufferInd < 80){
					msgBuffer[msgBufferInd++] = u8Char;
				}else{
				}
			}
			if(msgBufferInd == rawDataLen){
				if(msgBufferInd>1){
					msgBuffer[80-1] = msgBufferInd;
					xQueueSendFromISR(mqWIFIResp,msgBuffer,&xHigherPriorityTaskWoken);
					if(xHigherPriorityTaskWoken){
						portYIELD();
					}
				}
				msgBufferInd = 0;
				RECV_State = RECV_NONE;
			}
			break;

		default:
			break;
		}
	}
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
