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


#define BELT_JOLT_TIME	(21)
/* global variables */
/* Avoid using these */

volatile uint8_t pause_fsm = 0;
volatile uint8_t pause_flag = 0;

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
	
	pause_fsm = paused_state_is_running;
	
	pause_state = paused_state_is_running;
	current_belt_status = belt_running;
	ramp_state = ramp_state_normal;
	
	usartTXs("Booting...");
	
	/*while(1){
		uTimer140(1);
		PORTA ^= 1;
	}//*/
	
	mTimer(200);
	block_till_stepper_home();
	
	mTimer(200);
	stepper_repeat_steps(8, Counter_Clock_Wise);
	
	
	mTimer(200);
	start_pwm(MOTOR_PWM);
	
	adc_start_conv();
	
	mTimer(2);
	set_default_voltage();

	usartTXs("OK!\r\n");
	mTimer(2);
	start_pwm(MOTOR_PWM);
	
	
	while(1){
		if(pause_state == paused_state_is_stop){
			usartTXs("\r\nBuffer: ");
			usartNumTXs(buffer_get_length());
			usartTXs("\r\nSteel: ");
			usartNumTXs(steel_sorted);
			usartTXs("\r\nAlum: ");
			usartNumTXs(alum_sorted);
			usartTXs("\r\nWhite: ");
			usartNumTXs(white_sorted);
			usartTXs("\r\nBlack: ");
			usartNumTXs(black_sorted);
			usartTXs("\r\n");
			while(pause_state == paused_state_is_stop){
			}
		}
		/*while(buffer_get_length() == 0 && ramp_state == ramp_state_do_ramp){
			mTimer(BELT_JOLT_TIME);
			stop_pwm();
		}*/
		
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
	if(ramp_state == ramp_state_normal){
		buf_new();
	}
}

//Final Promixity sensor
ISR(INT6_vect){
	if(buf_get_first_item_material() == Black){
		black_sorted++;
	}
	else if(buf_get_first_item_material() == White){
		white_sorted++;
	}
	else if(buf_get_first_item_material() == Aluminum){
		alum_sorted++;
	}
	else{
		steel_sorted++;
	}
	
	static uint8_t counter = 2;
	
	if(ramp_state == ramp_state_do_ramp){
		
		counter--;
	}
	
	if(get_current_stepper_material() == buf_get_first_item_material()){
		mTimer(BELT_JOLT_TIME);
		remove_first_item();
	}else{
		stop_pwm();
		current_belt_status = belt_stopped;
		go_to_material(buf_get_first_item_material());
		start_pwm(MOTOR_PWM);
		remove_first_item();
	}
	if(counter == 0){
		mTimer(150);
		stop_pwm();
		usartTXs("\r\nBuffer: ");
		usartNumTXs(0);
		usartTXs("\r\nSteel: ");
		usartNumTXs(steel_sorted);
		usartTXs("\r\nAlum: ");
		usartNumTXs(alum_sorted);
		usartTXs("\r\nWhite: ");
		usartNumTXs(white_sorted);
		usartTXs("\r\nBlack: ");
		usartNumTXs(black_sorted);
		usartTXs("\r\n");
		while(1);
	}
	
	/*//usartNumTXs(buffer_get_total_sorted());
	//usartTXs("\r\n");
	mTimer(7);//*/
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
	
	static uint16_t ratio_under = 0;
	//At start we can pretend an item just left	
	static enum states last_state = leaving;
	
	if(last_state == leaving){
		status_leds(top, green);
		last_state = entering;
		ADC_reset_count();
		ADC_keep_running = true;
		//adc_start_conv();
	}else{
		ADC_keep_running = false;
		status_leds(top, orange);
		last_state = leaving;
		
		PORTA = read_Min_ADC();
		
		ratio_under = (ADC_return_time_under() * 100) / ADC_return_Count();
		
		if(read_Min_ADC() > WHITE_ABOVE_TH_12b){
			if(ratio_under > 30){
				//usartTXs("White ");
				set_second_prox_sensor_item(White, Delay_stage);	
			}else{
				//usartTXs("Black ");
				set_second_prox_sensor_item(Black, Delay_stage);
			}
		}else if(read_Min_ADC() > STEEL_ABOVE_TH_12b){
			//usartTXs("Steel ");
			set_second_prox_sensor_item(Steel, Delay_stage);
		}else{
			//usartTXs("Alum ");
			set_second_prox_sensor_item(Aluminum, Delay_stage);
		}

		adc_stop_conv();
	}
}

ISR(INT1_vect){
	//usartNumTXs(pause_state);
	//usartTXs("\r\n");
	if(pause_state == paused_state_is_running){	
		pause_state = paused_state_is_stop;
		usartTXs("Pause ON\r\n");
		////usartNumTXs(pause_state);
		////usartTXs("\r\n");
		stop_pwm();
		////usartTXs("Items on Belt ");
		////usartNumTXs(buffer_get_length());
		////usartTXs("\r\n");
	}else{
		////usartNumTXs(pause_state);
		////usartTXs("\r\n");
		pause_state = paused_state_is_running;
		start_pwm(MOTOR_PWM);
		usartTXs("Pause OFF\r\n");
	}
	mTimer(5);
}

ISR(INT2_vect){
	ramp_state = !ramp_state;
	if(ramp_state == ramp_state_do_ramp){
		usartTXs("Ramp ON\r\n");
	}else{
		usartTXs("Ramp OFF\r\n");	
	}
	mTimer(5);
}

ISR(TIMER3_COMPA_vect )
{
	// keep a track of number of overflows
	
	//PORTA ^= 1;
	//TIFR3 |= _BV(OCF3A);
	//TIMSK3 |= _BV(OCIE3A);
}