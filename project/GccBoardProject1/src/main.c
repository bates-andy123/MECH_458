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
#include "interrupt.h"
#include "main.h"
#include "Buffer.h"
#include "usart.h"

/* global variables */
/* Avoid using these */


/* main routine */
int main()
{	
	cli();
	mTimerConfig();
	init_led();
	init_interrupt();
	init_stepper();
	init_pwm();
	init_adc();
	buf_init();
	usartInit(0xC);
	sei();	
	
	usartTXs("Booting...\r\n");
	usartNumTXs(100);
	
	mTimer(200);
	block_till_stepper_home();
	
	mTimer(200);
	set_motor_setting(DC_Motor_Clockwise);
	set_dc_motor_speed(30);
	
	adc_start_conv();
	//PORTA = 0x80;
	set_first_item(White, Delay_stage);

	mTimer(200);
	while(1){
		//PORTA |= (buf_get_first_item_material() == get_current_stepper_material());
		//PORTA ^= 2;
		if(buf_get_first_item_material() == get_current_stepper_material()){
			set_motor_setting(DC_Motor_Clockwise);
			set_dc_motor_speed(30);
		}else{
			//PORTA ^= 0x80;
			go_to_material(buf_get_first_item_material());
		}
		mTimer(100);
	}
	
}/* main */


/**************************************************************************************/
/***************************** SUBROUTINES ********************************************/
/**************************************************************************************/


ISR(ADC_vect)
{
	ADC_interrupt();
}

//First Promixity sensor
ISR(INT4_vect){
	buf_new();
}

//Final Promixity sensor
ISR(INT6_vect){
	if(get_current_stepper_material() == buf_get_first_item_material()){
		
	}else{
		stop_pwm();
	}
}

//Magnetic sensor
ISR(INT7_vect){
	buf_is_magnetic();
	//stop_pwm();
	//go_to_material(buf_get_first_item_material());
}

ISR(INT0_vect){
	//local to this interrupts
	enum states{
		entering,
		leaving
	};
	
	//At start we can pretend an item just left	
	static enum states last_state = leaving;
	
	if(last_state == leaving){
		status_leds(top, green);
		last_state = entering;
	}else{
		status_leds(top, orange);
		last_state = leaving;
		
		PORTA = read_Min_ADC();
		
		if(read_Min_ADC() > BLACK_ABOVE_TH_8b){
			set_first_item(Black, Delay_stage);	
		}else if(read_Min_ADC() > WHITE_ABOVE_TH_8b){
			set_first_item(White, Delay_stage);
		}else if(read_Min_ADC() > STEEL_ABOVE_TH_8b){
			set_first_item(Steel, Delay_stage);
		}else{
			set_first_item(Aluminum, Delay_stage);
		}

		//stop_pwm();
		adc_stop_conv();
	}
}
