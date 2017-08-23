/*
 * SM_CommandLineInterface.c
 *
 */

#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "SM_CommandLineInterface.h"
#include "executeVariousCommand.h"


extern UART_HandleTypeDef huart1;
extern uint8_t rxBuffer;
onState currState = {receiveCharUART};

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	currState.whichState = receiveEnter;
	stateMachine();
}

void stateMachine(){

	switch(currState.whichState){
	case receiveCharUART:
	  HAL_UART_Receive_IT(&huart1, &rxBuffer, 1);
	 /* if (rxBuffer == 10)
	   currState.whichState = receiveEnter;
	  else
	    currState.whichState = receiveCharUART;*/
	break;
	case receiveEnter:

  	  executeCMD(&huart1);
  	  currState.whichState = receiveCharUART;
  	  stateMachine();
	break;
	default:
	  currState.whichState = receiveCharUART;
	}

}

