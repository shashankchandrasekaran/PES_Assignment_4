/*
 *  Filename: StateMachine.h
 *  Created on: Oct 11, 2022
 *  Author: Shashank Chandrasekaran
 *  Description: This H file contains the decleration of functions related to state machines
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "Timing.h"
/*
 * Function for transitioning from one state to the other
 * Purpose: This function ensures the transition from one state to another in 1 second.
 * The colour transitions smoothly every 62.5 msec till it reaches 1 second. In between
 * the transition, slider is polled and if detected, it exits the function.
 * Parameter passed: Current state and desired/next state: Current_State, Desired_State
 * Parameters returned: None
 */
void Transition(ticktime_t Current_State,ticktime_t Desired_State);

/*
 * Function to control traffic light based on current state
 * Purpose: This function sets the RGB values according to the current state with the
 * respective delay. Touch slider polling is done every 62.5 msec and if detected,
 * it changes the state to CROSSWALK and exits the function
 * Parameter passed: Current state: State
 * Parameters returned: None
 */
void Traffic_Light(ticktime_t State);

/*
 * State Machine function
 * Purpose: This function defines the state machine in switch case where the cases are
 * the states. Button press event for CROSSWALK and timeout event is checked in each state
 * and exited from that state if detected.
 * Parameter passed: None
 * Parameters returned: None
 */
void State_Machine();

#endif /* STATEMACHINE_H_ */
