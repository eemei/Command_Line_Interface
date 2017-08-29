/*
 * test_SM_CommandLineInterface.c
 *
 *  Created on: Aug 28, 2017
 *      Author: liewe
 */

#include "unity.h"
#include "SM_CommandLineInterface.h"
#include "mock_hardwareinterface.h"

extern onState currState;

void setUp(void)
{}

void tearDown(void)
{}

void test_stateMachine_with_eventstart(void)
{
	currState.whichState = receiveCharUART;
	uartReceive_Expect();
	stateMachine(start_EVT);
    TEST_ASSERT_EQUAL(receiveCharUART, currState.whichState);
}

void test_stateMachine_with_eventstart_currentSate_is_receiveEnter(void)
{
	currState.whichState = receiveEnter;
	response_Expect();
	stateMachine_Expect(start_EVT);
    TEST_ASSERT_EQUAL(receiveEnter, currState.whichState);
}
