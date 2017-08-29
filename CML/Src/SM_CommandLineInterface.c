/*
 * SM_CommandLineInterface.c
 *
 */

#include <stdio.h>
//#include "stm32f1xx_hal.h"
#include "main.h"
#include "SM_CommandLineInterface.h"
#include "hardwareinterface.h"
//#include "executeVariousCommand.h"

onState currState = {receiveCharUART};
event eventStatus;

void stateMachine(event eventStatus){

	switch(currState.whichState){
	case receiveCharUART:
	  if(eventStatus == start_EVT){
	    uartReceive();
	  }
	break;

	case receiveEnter:
	  response();
  	  currState.whichState = receiveCharUART;
  	  stateMachine(eventStatus);
	break;
	default:
	  currState.whichState = receiveCharUART;
	}

}

