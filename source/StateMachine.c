/*
 *  Filename: StateMachine.c
 *  Created on: Oct 11, 2022
 *  Author: Shashank Chandrasekaran
 *  Description: This C file contains the definitions of functions related to state machines
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
#include "StateMachine.h"
#include "PWM.h"
#include "log.h"

#define STOP_R 97 //Intensity value for Red Led in STOP state
#define STOP_G 30 //Intensity value for Green Led in STOP state
#define STOP_B 60 //Intensity value for Blue Led in STOP state
#define GO_R 34 //Intensity value for Red Led in GO state
#define GO_G 150 //Intensity value for Green Led in GO state
#define GO_B 34 //Intensity value for Blue Led in GO state
#define WARNING_R 255 //Intensity value for Red Led in WARNING state
#define WARNING_G 178 //Intensity value for Green Led in WARNING state
#define WARNING_B 0 //Intensity value for Blue Led in WARNING state
#define CROSSWALK_R 00 //Intensity value for Red Led in CROSSWALK state
#define CROSSWALK_G 16 //Intensity value for Green Led in CROSSWALK state
#define CROSSWALK_B 48 //Intensity value for Blue Led in CROSSWALK state
#define MS_1000 16 //Count for 1000 Ms delay
#define Touch_Det 5 //Threshold to detect touch from TSI
#define Blink_Count 10 //To blink for 10 times in crosswalk to obtain 1s delay
#define MS_250 4 //Count for 250 Ms delay
#define MS_750 12 //Count for 750 Ms delay
#define SCALE 1000 //Divides current time by 1000 for scaling

int R_Cur=0, G_Cur=0, B_Cur=0; /*Current intensity values for calculation
                                          during transition*/
int Touch_Val; //Used to store touch value received from touch_scan function

ticktime_t Current_Time,Previous_Time; /*Variables to store current and previous
                                         time to check if 62.5 msec has elapsed*/


//Defining states in enum
typedef enum {
	STOP,
	GO,
	WARNING,
	CROSSWALK
}state_t;

state_t Cur_State=STOP; //Assigning Current state to STOP
state_t Store_State; //Stores the previous state for use in transition logic


/*******************Transition function from one state to other****************************/
void Transition(ticktime_t Current_State,ticktime_t Desired_State)
{
	//Declare Current and next state color variables for RGB
	int Cur_State_R, Cur_State_G,Cur_State_B,Next_State_R,Next_State_G,Next_State_B;
	//Declare 2D arrays for printing the states
#ifdef DEBUG
	char array_S[3][50]={"STOP to GO","GO to WARNING","WARNING to STOP"};
	char array_C[3][50]={"STOP to CROSSWALK","GO to CROSSWALK","WARNING to CROSSWALK"};
#endif

	//Set current and next state colors as per current and desired states
	if (Current_State==STOP && Desired_State==GO)
	{
		Cur_State_R=STOP_R;
		Cur_State_G=STOP_G;
		Cur_State_B=STOP_B;
		Next_State_R=GO_R;
		Next_State_G=GO_G;
		Next_State_B=GO_B;
	}
	else if (Current_State==GO && Desired_State==WARNING)
	{
		Cur_State_R=GO_R;
		Cur_State_G=GO_G;
		Cur_State_B=GO_B;
		Next_State_R=WARNING_R;
		Next_State_G=WARNING_G;
		Next_State_B=WARNING_B;
	}
	else if (Current_State==WARNING && Desired_State==STOP)
	{
		Cur_State_R=WARNING_R;
		Cur_State_G=WARNING_G;
		Cur_State_B=WARNING_B;
		Next_State_R=STOP_R;
		Next_State_G=STOP_G;
		Next_State_B=STOP_B;
	}
	else if (Current_State==CROSSWALK && Desired_State==GO)
	{
		Cur_State_R=CROSSWALK_R;
		Cur_State_G=CROSSWALK_G;
		Cur_State_B=CROSSWALK_B;
		Next_State_R=GO_R;
		Next_State_G=GO_G;
		Next_State_B=GO_B;
	}
	else if (Desired_State==CROSSWALK)
	{
		Cur_State_R=R_Cur;
		Cur_State_G=G_Cur;
		Cur_State_B=B_Cur;
		Next_State_R=CROSSWALK_R;
		Next_State_G=CROSSWALK_G;
		Next_State_B=CROSSWALK_B;
	}
	reset_timer(); //Reset the current time to start counting from 0 to 1000 msec
	Current_Time=get_timer(); //Get the current time
	Previous_Time=0; //Reset the Previous time
	while(Current_Time<MS_1000)
	{
		Current_Time=get_timer(); //Keep updating current time
		if(Current_Time>Previous_Time) //Check if 62.5 msec has elapsed
		{
			Previous_Time=Current_Time; //Store the current time to previous time
			if(Cur_State!=CROSSWALK) //Polling of TSI to be done in all states except CROSSWALK
			{
				Touch_Val=Touch_Scan_LH(); //Poll TSI every 62.5 msec
				if(Touch_Val>=Touch_Det) //If touch detected
				{
					Cur_State=CROSSWALK; //Change state to CROSSWALK
					return;
				}
			}
			//Calculation of RGB values at every 62.5 msec
			R_Cur=Cur_State_R+((Next_State_R-Cur_State_R)*(Current_Time*(MS_62_5/SCALE)));
			G_Cur=Cur_State_G+((Next_State_G-Cur_State_G)*(Current_Time*(MS_62_5/SCALE)));
			B_Cur=Cur_State_B+((Next_State_B-Cur_State_B)*(Current_Time*(MS_62_5/SCALE)));

			//Write these calculated RGB values to the TPM channels
			TPM2->CONTROLS[0].CnV=R_Cur;
			TPM2->CONTROLS[1].CnV=G_Cur;
			TPM0->CONTROLS[1].CnV=B_Cur;
		}
	}
#ifdef DEBUG
	if(Current_State==CROSSWALK)
	{
		LOG("State change from CROSSWALK to GO - %d msec since startup\n\r",now());
	}
	else if(Desired_State!=CROSSWALK)
	{
		LOG("State change from %s - %d msec since startup\n\r",array_S[Current_State],now());
	}
	else if(Desired_State==CROSSWALK)
	{
		LOG("State change from %s - %d msec since startup\n\r",array_C[Current_State],now());
	}
#endif

	Cur_State=Desired_State; //After transition, change the state
	Previous_Time=0; //Reset previous time
	reset_timer(); //Reset the current time
}


/***************Function to control traffic signal based on the current state*************/
void Traffic_Light(ticktime_t State)
{
	if(State==STOP)
	{ 	//Provide RGB with the required intensity for STOP signal
		TPM2->CONTROLS[0].CnV=STOP_R;
		TPM2->CONTROLS[1].CnV=STOP_G;
		TPM0->CONTROLS[1].CnV=STOP_B;
		Current_Time=get_timer();
		while(Current_Time<TIMEOUT) //Check if timer has elapsed the delay time
		{
			Current_Time=get_timer();
			if(Current_Time>Previous_Time) //Check if 62.5 msec has elapsed
			{
				Touch_Val=Touch_Scan_LH(); //Poll TSI every 62.5 msec
				Previous_Time=Current_Time;
				if(Touch_Val>=Touch_Det) //If touch detected
				{
					LOG("Button press detected, with the system time- %d msec"
							"since startup\n\r",now());
					Store_State=Cur_State; //Store current state when touch is detected
					Cur_State=CROSSWALK; //Change state to CROSSWALK
					//Store current values of R,G and B to be used in transition
					R_Cur=STOP_R;
					G_Cur=STOP_G;
					B_Cur=STOP_B;
					return;
				}
			}
		}
		Previous_Time=0; //Reset previous time
	}
	else if(State==GO)
	{
		//Provide RGB with the required intensity for GO signal
		TPM2->CONTROLS[0].CnV=GO_R;
		TPM2->CONTROLS[1].CnV=GO_G;
		TPM0->CONTROLS[1].CnV=GO_B;
		Current_Time=get_timer();
		while(Current_Time<TIMEOUT) //Check if timer has elapsed the delay time
		{
			Current_Time=get_timer();
			if(Current_Time>Previous_Time) //Check if 62.5 msec has elapsed
			{
				Touch_Val=Touch_Scan_LH(); //Poll TSI every 62.5 msec
				Previous_Time=Current_Time;
				if(Touch_Val>=Touch_Det) //If touch detected
				{
					LOG("Button press detected, with the system time- %d msec"
							"since startup\n\r",now());
					Store_State=Cur_State;
					Cur_State=CROSSWALK; //Change state to CROSSWALK
					//Store current values of R,G and B to be used in transition
					R_Cur=GO_R;
					G_Cur=GO_G;
					B_Cur=GO_B;
					return;
				}
			}
		}
		Previous_Time=0; //Reset previous time
	}
	else if(State==WARNING)
	{
		//Provide RGB with the required intensity for WARNING signal
		TPM2->CONTROLS[0].CnV=WARNING_R;
		TPM2->CONTROLS[1].CnV=WARNING_G;
		TPM0->CONTROLS[1].CnV=WARNING_B;
		Current_Time=get_timer();
		while(Current_Time<WAR_TIMEOUT)  //Check if timer has elapsed the delay time
		{
			Current_Time=get_timer();
			if(Current_Time>Previous_Time) //Check if 62.5 msec has elapsed
			{
				Touch_Val=Touch_Scan_LH(); //Poll TSI every 62.5 msec
				Previous_Time=Current_Time;
				if(Touch_Val>=Touch_Det) //If touch detected
				{
					LOG("Button press detected, with the system time- %d msec"
							"since startup\n\r",now());
					Store_State=Cur_State;
					Cur_State=CROSSWALK; //Change state to CROSSWALK
					//Store current values of R,G and B to be used in transition
					R_Cur=WARNING_R;
					G_Cur=WARNING_G;
					B_Cur=WARNING_B;
					return;
				}
			}
		}
		Previous_Time=0; //Reset previous time
	}
	else if(State==CROSSWALK)
	{
		int i;
		reset_timer();
		Current_Time=get_timer();
		for(i=0;i<Blink_Count;i++) //Run loop for blinking 10 times
		{
			Current_Time=get_timer();
			while(Current_Time<MS_250) //For 250 msec off delay
			{
				Current_Time=get_timer();
				//Set RGB intensity to 0
				TPM2->CONTROLS[0].CnV=0;
				TPM2->CONTROLS[1].CnV=0;
				TPM0->CONTROLS[1].CnV=0;
			}
			reset_timer();
			Current_Time=get_timer();
			while(Current_Time<MS_750) //For 750 msec on delay
			{
				Current_Time=get_timer();
				//Provide RGB with the required intensity for CROSSWALK signal
				TPM2->CONTROLS[0].CnV=CROSSWALK_R;
				TPM2->CONTROLS[1].CnV=CROSSWALK_G;
				TPM0->CONTROLS[1].CnV=CROSSWALK_B;
			}
			reset_timer();
		}
		Previous_Time=0; //Reset previous time
	}
}

/************************************State machine****************************************/
void State_Machine()
{
	switch(Cur_State)
	{
	case STOP:
		Traffic_Light(STOP); //Set the STOP color with the delay
		if(Cur_State==CROSSWALK) //If state changed to CROSSWALK, exit
			break;
		else
			Transition(STOP,GO); //Else transition from STOP to GO signal
		break;

	case GO:
		Traffic_Light(GO); //Set the GO color with the delay
		if(Cur_State==CROSSWALK)
			break;
		else
			Transition(GO,WARNING); //Transition from GO to WARNING signal
		break;

	case WARNING:
		Traffic_Light(WARNING); //Set the WARNING color with the delay
		if(Cur_State==CROSSWALK)
			break;
		else
			Transition(WARNING,STOP); //Transition from WARNING to STOP signal
		break;

	case CROSSWALK:
		Transition(Store_State,CROSSWALK); //Transition from current state to CROSSWALK
		Traffic_Light(CROSSWALK); //Blink for 10 msec with CROSSWALK color
		Transition(CROSSWALK,GO); //Transition from CROSSWALK to GO signal
		break;
	}
}
