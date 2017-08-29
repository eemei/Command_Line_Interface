#include "hardwareinterface.h"
#include "stm32f1xx_hal.h"
#include "executeVariousCommand.h"
#include "SM_CommandLineInterface.h"
#include <stdio.h>


extern UART_HandleTypeDef huart1;
extern uint8_t rxBuffer;
extern onState currState;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	currState.whichState = receiveEnter;
	stateMachine(start_EVT);
}

void uartReceive(void){
  HAL_UART_Receive_IT(&huart1, &rxBuffer, 1);
}

void response(void){
  executeCMD(&huart1);
}
