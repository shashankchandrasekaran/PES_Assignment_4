/*
 *  File name: Touch.h
 *  Created on: Oct 11, 2022
 *  Author: Shashank Chandrasekaran
 *  Description: This c file contains TSI declaration and scan function declarations
 */

#ifndef TOUCH_H_
#define TOUCH_H_

/*
 * Function for initialization of TSI registers
 * Purpose: This function initializes the capacitive touch slider (TSI)
 * Parameter passed: None
 * Parameters returned: None
 */
void Touch_Init(void);

/*
 * Function to scan/poll value from TSI
 * Purpose: This function detects if there is a touch on the capacitive
 * touch slider.
 * Parameters passed: None
 * Parameters returned: Touch value from TSI removing the offset
 */
int Touch_Scan_LH(void);

#endif /* TOUCH_H_ */
