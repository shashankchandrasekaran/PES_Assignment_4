/**
 * @file    PES_Assignment_4.c
 * @brief   Application entry point.
 */
#include <MKL25Z4.H>
#include "stdio.h"
#include "stdint.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "peripherals.h"
#include "fsl_debug_console.h"
#include "core_cm0plus.h"
#include "Touch.h"
#include "PWM.h"
#include "log.h"
#include "StateMachine.h"

#define PWM_PERIOD 256 //For obtaining intensity values from 0-255

int main(void) {
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif
	Init_SysTick(); //Initialize SysTick timer
	Init_RGB_LED_PWM(PWM_PERIOD); //Initialize PWM TPM channels
	Touch_Init(); //Initialize capacitive touch slider
	LOG("Main loop is starting:\n\r");
	while(1)
	{
		State_Machine(); //State machine infinite loop
	}
	return 0 ;
}
