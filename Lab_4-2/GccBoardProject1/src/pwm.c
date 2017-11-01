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

extern void init_pwm(){
	//Turn on B7 to output mode
	DDRB |= 0x8F; 
	
	TCCR0A =(1<<COM0A1) | (1<<WGM01) | (1<<WGM00);	//Set timer counter compare register to Fast PWM

	TCCR0B = (1<<CS01) | (1<<CS00);
	OCR0A = 220;
}

extern inline void set_dc_motor_speed(uint8_t speed){
	OCR0A = speed;
}

extern void set_motor_setting(Motor_Setting setting){
	//Force all settings to off
	PORTB &= ~(IA | IB | EA | EB);
	
	if(setting == DC_Motor_Clockwise){
		PORTB |= IB;
	}
	else if (setting == DC_Motor_Counter_Clockwise){
		PORTB |= IA;
	}
}