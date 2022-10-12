/*
 *  File name: Timing.c
 *  Created on: Oct 11, 2022
 *  Author: Shashank Chandrasekaran
 *  Description: This C file contains the definitions of Systick timer related functions
 *  Reference: Dean Chapter 7 Listing 7.1
 */

#include <MKL25Z4.H>
#include "stdio.h"
//#include "stdint.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "peripherals.h"
#include "fsl_debug_console.h"
#include "core_cm0plus.h"
#include "Timing.h"

#define SYSTICK_LOAD (187500) //Load value for obtaining 62.5 msec delay

ticktime_t TimerMS_62_5=0, Start_Timer=0; //Variables used for timing calculations

/***************************Initializing SysTick Timer**************************************/
void Init_SysTick(void)
{
	SysTick->LOAD=SYSTICK_LOAD; //Set reload to get 62.5 ms delay
	NVIC_SetPriority(SysTick_IRQn,3); //Set interrupt priority to 3
	SysTick->VAL=0; //Force load of reload value
	SysTick->CTRL=SysTick_CTRL_TICKINT_Msk| //Enable Interrupt, alt. clock source
			      SysTick_CTRL_ENABLE_Msk; //Enable SysTick timer
}

/***************************SysTick interrupt handler**************************************/
void SysTick_Handler()
{
	TimerMS_62_5++;
}

/*************************Returns time since Startup**************************************/
ticktime_t now()
{
	return (TimerMS_62_5)*(MS_62_5);
}

/*************************Resets the Start timer variable**********************************/
void reset_timer()
{
	Start_Timer=TimerMS_62_5;
}

/***************Returns Start variable count since last call to reset ********************/
ticktime_t get_timer()
{
	return (TimerMS_62_5 - Start_Timer);
}
