/*
 *  File name:Timing.h
 *  Created on: Oct 11, 2022
 *  Author: Shashank Chandrasekaran
 *  Description: This H file contains the declaration of Systick timer related functions
 *  Reference: Assignment 4 Page 3 (Note on timer APIs)
 */

#ifndef TIMING_H_
#define TIMING_H_

typedef uint32_t ticktime_t; //Time since boot, in sixteenth of a second

#define MS_62_5 (62.5) //Value used to obtain time in multiples of 62.5 msec

/*
 * Function for initialization of SysTick timer
 * Purpose: This function initializes the registers related to SysTick timer
 * Parameter passed: None
 * Parameters returned: None
 */
void Init_SysTick(void);

/*
 * Function to define operation to be performed when SysTick interrupt is called
 * Purpose: This function increments a variable every 63.5 msec
 * Parameter passed: None
 * Parameters returned: None
 */
void SysTick_Handler();

/*
 * Function to return time since startup, in sixteenth of a second
 * Purpose: This function returns the time by multiplying the variable called
 * in the interrupt handler with 62.5 to obtain the total time since startup
 * Parameter passed: None
 * Parameters returned: Total time since startup: TimerMS_62_5++
 */
ticktime_t now();


/*
 * Function to reset a variable that is used for calculating certain delay
 * Purpose: This function resets a variable every time it is called,
 * so that the counting can start again. But it doesn't affect the now() values
 * Parameter passed: None
 * Parameters returned: None
 */
void reset_timer();

/*
 * Function to return the variable count (used for calculating delay) since
 * last call to reset function
 * Parameter passed: None
 * Parameters returned: Variable's count value since reset: TimerMS_62_5 - Start_Timer
 */
ticktime_t get_timer();

#endif /* TIMING_H_ */
