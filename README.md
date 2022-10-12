# PES_Assignment_4
PES Assignment 4 on State Machines
/*************Peer reveiew comments************/ 
Reviewer - Harsh Beriwal
Date and time of review: 10/11/2022 at 11 PM
Review comments and action taken:
•	No bugs. Code works properly with accurate timing. Crosswalk multiple touches are ignored, as required and transitions are smooth. Although by decreasing TPM clock frequency by using prescaler, the Transitions could be made smoother. 
No action taken as transitions were smooth with period 256 and clock source 48 MHz. Verified by printing values on console and checking the timing.   
•	#define not used everywhere. Like I can see some magic numbers floating around. Like while using the Transition formula, I can see values like 1000 which could be included with macros to make it more readable and portable.
Action taken: Created #define for 1000 used in calculation during transition
•	There are Indentation issues in code as well. The Statemachine.c readability issues can be resolved by making the indentation clear. Check State_Machine() Function.
Action: Corrected the indendation issues in the State_Machine().

/**************Approach toward the program***********/
State machine was developed identifying the states and events. Based on that, approach was finalized to use switch case based on states.
Each functionality was individually tested. Like testing SysTick timer first, then PWM and then integrating both with the state machine. The approach of dividing time every sixteenth second was taken and that time was recorded and used for delay and transition calculations. The TSI logic for crosswalk was introduced in the end and the touch slider is polled every 62.5msec except when it is in crosswalk state. For debug and production mode, Log header file was created for defining different times and printf functionality. 
Testing was done in debug and release mode and timings are accurate. The printing from one state to another is shown after the state transition has taken place i.e. The STOP to GO state in debug mode would be 6 Sec (5 Sec in STOP mode + 1 sec in transition), at 6 seconds the logging would happen indicating a state change.
The timings obtained on the UART were compared with the expected times. The capacitive touch slider was touch during any state, transition and there is a gradual change from that state to the CROSSWALK state. But when the state is in CROSSWALK, the touch slider is ignored. The same test was done on release mode with stopwatch to ensure correct timings.
In order to check the smoothness and correctness of transitions, for testing purpose, values of the R,G and B were printed every 62.5 msec and compared with the expected values.

Challenges faced: While trying to attempt extra credit 2, the interrupt was being called even when switch connected to GPIO pin is unpressed. Due to this entire logic was failing and the code for GPIO was removed. 

The submission contains :
All the project files
State Machine pdf
Readme
Video demonstrating working of project
