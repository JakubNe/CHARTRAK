/*
 * StateMachine.h
 *
 *  Created on: Mar 9, 2025
 *      Author: Admin
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

typedef enum {
	UNICARD_OFF = 0,
	UNICARD_NOTRECOGNISED,
	UNICARD_CON,
	UNICARD_OVERCURRENT,
	UNICARD_COMFAIL
} CardStates;

void FSM_CHANGESTATE(CardStates newstate);

#endif /* STATEMACHINE_H_ */
