/*
 * SM_CommandLineInterface.h
 *
 */

#ifndef SM_COMMANDLINEINTERFACE_H_
#define SM_COMMANDLINEINTERFACE_H_

typedef enum startSM event;
enum startSM{
	start_EVT,
	off_EVT
};

typedef enum SMState state;
enum SMState{
	receiveCharUART,
	receiveEnter
	//SPITransmit,
	//SPIResponse
};

typedef struct stateInfo onState;
struct stateInfo{
	state whichState;
};

void stateMachine(event eventStatus);

#endif /* SM_COMMANDLINEINTERFACE_H_ */
