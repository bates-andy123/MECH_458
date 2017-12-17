/*
 * pwm.c
 *
 * Created: 2017-10-25 2:36:43 PM
 *  Author: abates
 */ 

#include <avr/io.h>

#include "pwm.h"

#define IA	(0x4)
#define EA	(0x1)
#define IB	(0x2)
#define EB	(0x8)

//Initialize PWM for the motor
extern void init_pwm(){
	//Turn on B7 to output mode
	DDRB |= 0x8F; 
	
	TCCR0A =(1<<COM0A1) | (1<<WGM01) | (1<<WGM00);	//Set timer counter compare register to Fast PWM

	TCCR0B = (1<<CS01) | (1<<CS00);
	OCR0A = 0;
}

//A convienent inline function to change motor speed
extern inline void set_dc_motor_speed(uint8_t speed){
	OCR0A = speed;
}

//Stop PWM and set the belt to brake
extern inline void stop_pwm(){
	set_dc_motor_speed(0);
	set_motor_setting(Brake_to_VCC);
}

//Turn PWM back on to a desired setting
extern inline void start_pwm(uint8_t speed){
	set_motor_setting(DC_Motor_Clockwise);
	set_dc_motor_speed(speed);
}


//Change the motor setting manually
extern void set_motor_setting(Motor_Setting setting){
	//Force all settings to off
	PORTB &= ~(IA | IB | EA | EB);
	
	if(setting == DC_Motor_Clockwise){
		PORTB |= IB;
	}
	else if (setting == DC_Motor_Counter_Clockwise){
		PORTB |= IA;
	}
	else if(setting = Brake_to_VCC){
		//do nothing
	}
	else if(setting == Brake_to_Ground){
		PORTB |= (IA | IB);
	}
}