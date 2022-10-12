/*
 *  File name:Touch.c
 *  Created on: Oct 11, 2022
 *  Author: Shashank Chandrasekaran
 *  Description: This c file contains TSI declaration and scan function definitions
 *  Links: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense.
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

#define TOUCH_DATA (TSI0->DATA & 0xFFFF) //To store exact scan value
#define TOUCH_OFFSET (72)  // offset to be subtracted from scanned value

/****************************************Calibrating capacitive touch***********************/
void Touch_Init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; // enabling the clock

	TSI0->GENCS = TSI_GENCS_MODE(0u) | //operating in non-noise mode
			TSI_GENCS_REFCHRG(0u) | //reference oscillator charge and discharge value 500nA
			TSI_GENCS_DVOLT(0u) | //oscillator voltage rails set to default
			TSI_GENCS_EXTCHRG(3u) | //electrode oscillator charge and discharge value 500nA
			TSI_GENCS_PS(0u) |  // frequency clock divided by one
			TSI_GENCS_NSCN(31u) | //scanning the electrode 32 times
			TSI_GENCS_TSIEN_MASK | //enabling the TSI module
			TSI_GENCS_EOSF_MASK; // writing one to clear the end of scan flag
}

/*************************************TSI Touch value function*******************************/
int Touch_Scan_LH(void)
{
	unsigned int scan = 0;
	TSI0->DATA = TSI_DATA_TSICH(10u); //Select channel 10
	TSI0->DATA |= TSI_DATA_SWTS_MASK; //software trigger to start the scan
	while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK)); // waiting for the scan to complete 32 times
	scan = TOUCH_DATA; //Obtain the touch value
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; //writing one to clear the end of scan flag
	return scan-TOUCH_OFFSET; //Return touch value removing offset
}
