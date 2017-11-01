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

#define STEP_TIME_MS	(15)
#define TIME_BETWEEN_STEPS	(2500)

/* global variables */
/* Avoid using these */

/* main routine */
int main()
{	
	cli();
	mTimerConfig();
	init_led();

	//init_stepper();
	init_pwm();
	init_adc();
	sei();	
	
	adc_start_conv();
	Motor_Setting current_direction = DC_Motor_Counter_Clockwise;
	set_motor_setting(current_direction);
	DDRC = 0;
	while(1){
		if( (PINC & 0x01) > 0 ){
			mTimer(20);
			
			if(current_direction == DC_Motor_Clockwise){
				current_direction = DC_Motor_Counter_Clockwise;
			}else{
				current_direction = DC_Motor_Clockwise;
			}
			set_motor_setting(current_direction);
			while( (PINC & 0x01) > 0);
			mTimer(20);
		}
		//set_dc_motor_speed(read_ADC());
		mTimer(15);
	}
	
}/* main */


/**************************************************************************************/
/***************************** SUBROUTINES ********************************************/
/**************************************************************************************/


ISR(ADC_vect)
{
	ADC_interrupt();
}

