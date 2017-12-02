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

enum belt_status{
	belt_running,
	belt_stopped	
};



#define MOTOR_PWM	(60)
#define BELT_JOLT_TIME	(21)
/* global variables */
/* Avoid using these */

enum belt_status current_belt_status = belt_running;
enum pause_button_state  pause_state = paused_state_is_running;


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
	
	//timer0_init();
	sei();	
	
	usartTXs("Booting...\r\n");
	
	mTimer(200);
	block_till_stepper_home();
	
	mTimer(200);
	stepper_repeat_steps(8, Counter_Clock_Wise);
	
	
	mTimer(200);
	start_pwm(MOTOR_PWM);
	
	adc_start_conv();
	//PORTA = 0x80;

	mTimer(200);
	while(1){
		//PORTA |= (buf_get_first_item_material() == get_current_stepper_material());
		//PORTA ^= 2;
		if(buf_get_first_item_material() == get_current_stepper_material()){
			if(current_belt_status == belt_stopped && pause_state == paused_state_is_running){
				start_pwm(MOTOR_PWM);
				remove_first_item();
				current_belt_status = belt_running;
				start_pwm(250);
				mTimer(BELT_JOLT_TIME);
				start_pwm(MOTOR_PWM);
			}
		}else{
			go_to_material(buf_get_first_item_material());
		}

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
		mTimer(BELT_JOLT_TIME);
		remove_first_item();
	}else{
		stop_pwm();
		current_belt_status = belt_stopped;
	}
}

//Magnetic sensor
ISR(INT7_vect){
	//buf_is_magnetic();
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
		ADC_reset_count();
	}else{
		status_leds(top, orange);
		last_state = leaving;
		
		PORTA = read_Min_ADC();
		
		if(read_Min_ADC() > BLACK_ABOVE_TH_12b){
			usartTXs("Black ");
			set_second_prox_sensor_item(Black, Delay_stage);	
		}else if(read_Min_ADC() > WHITE_ABOVE_TH_12b){
			usartTXs("White ");
			set_second_prox_sensor_item(White, Delay_stage);
		}else if(read_Min_ADC() > STEEL_ABOVE_TH_12b){
			usartTXs("Steel ");
			set_second_prox_sensor_item(Steel, Delay_stage);
		}else{
			usartTXs("Alum ");
			set_second_prox_sensor_item(Aluminum, Delay_stage);
		}
		usartNumTXs(read_Min_ADC());
		usartTXs(" Count ");
		usartNumTXs(ADC_return_Count());
		usartTXs("\r\n");
		//stop_pwm();
		adc_stop_conv();
	}
}

ISR(INT1_vect){
	pause_state = !pause_state;
	if(pause_state == paused_state_is_stop){
		usartTXs("pause\r\n");
		stop_pwm();
	}else{
		start_pwm(MOTOR_PWM);
	}
	
}

ISR(TIMER0_OVF_vect)
{
	// keep a track of number of overflows
	usartTXs("i\r\n");
}