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
#include <avr/interrupt.h> 
#include "LinkedQueue.h" 	/* This is the attached header file, which cleans things up */
							/* Make sure you read it!!! */
#include "Switches.h"
#include "Led.h"
#include "mtimer.h"
#include "stepper.h"
#include "pwm.h"
#include "adc.h"

#define STEP_TIME_MS	(12)
#define TIME_BETWEEN_STEPS	(2500)

/* global variables */
/* Avoid using these */

/* main routine */
int main()
{	
	cli();
	mTimerConfig();
	init_led();

	init_stepper();
	init_pwm();
	//init_adc();
	sei();	
	
	//write_to_led_display(0xFF);
	
	//adc_start_conv();
	
	set_motor_setting(DC_Motor_Clockwise);
	//set_dc_motor_speed(50);
	while(1){
		step(Clock_Wise);
		mTimer(STEP_TIME_MS);
	}
	
}/* main */


/**************************************************************************************/
/***************************** SUBROUTINES ********************************************/
/**************************************************************************************/


ISR(INT5_vect){
	PORTA ^= 0x2;
}

ISR(ADC_vect)
{
	ADC_interrupt();
}

