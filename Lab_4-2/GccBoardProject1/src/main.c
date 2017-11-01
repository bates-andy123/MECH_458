/* Solution Set for the LinkedQueue.c */
/* 	
	Course		: UVic Mechatronics 458
	Milestone	: 3
	Title		: Data structures for MCUs and the Linked Queue Library

	Name 1:					Student ID:
	Name 2:					Student ID:
	
	Description: You can change the following after you read it.
	
	This main routine will only serve as a testing routine for now. At some point you can comment out
	The main routine, and can use the following library of functions in your other applications

	To do this...make sure both the .C file and the .H file are in the same directory as the .C file
	with the MAIN routine (this will make it more convenient)
*/

/* include libraries */
#include <stdlib.h>
#include <avr/io.h>
#include "LinkedQueue.h" 	/* This is the attached header file, which cleans things up */
							/* Make sure you read it!!! */
#include "Switches.h"
#include "Led.h"
#include "mtimer.h"
#include "stepper.h"
#include "pwm.h"
#include "adc.h"

#define STEP_TIME_MS	(15)
#define TIME_BETWEEN_STEPS	(2500)

/* global variables */
/* Avoid using these */

/* main routine */
int main()
{	
	mTimerConfig();
	init_led();
	init_stepper();
	init_pwm();
	init_adc();
	
	
	adc_start_conv();
	while(1){
		
		
		mTimer(10);
		OCR0A++;
		//write_to_led_display(OCR0A);
	}

	while(1)
	{
		uint8_t i = 0;
		for(i=0; i<50; i++){
			step(Clock_Wise);
			mTimer(STEP_TIME_MS);
		}
		mTimer(TIME_BETWEEN_STEPS);
		for(i=0; i<17; i++){
			step(Clock_Wise);
			mTimer(STEP_TIME_MS);
		}
		mTimer(TIME_BETWEEN_STEPS);
		for(i=0; i<34; i++){
			step(Clock_Wise);
			mTimer(STEP_TIME_MS);
		}
		mTimer(TIME_BETWEEN_STEPS);
		for(i=0; i<51; i++){
			step(Clock_Wise);
			mTimer(STEP_TIME_MS);
		}
		mTimer(TIME_BETWEEN_STEPS);
		for(i=0; i<17; i++){
			step(Counter_Clock_Wise);
			mTimer(STEP_TIME_MS);
		}
		mTimer(TIME_BETWEEN_STEPS);
		for(i=0; i<34; i++){
			step(Counter_Clock_Wise);
			mTimer(STEP_TIME_MS);
		}
		mTimer(TIME_BETWEEN_STEPS);
		for(i=0; i<51; i++){
			step(Counter_Clock_Wise);
			mTimer(STEP_TIME_MS);
		}
		while(1);
	}
	
}/* main */


/**************************************************************************************/
/***************************** SUBROUTINES ********************************************/
/**************************************************************************************/


ISR(ADC_vect)
{
	ADC_result = ADCH;
	ADC_result_change_flag = true;
	PORTA ^= 0x20;
}

