/*
 * pwm.c
 *
 * Created: 2017-10-25 2:36:43 PM
 *  Author: abates
 */ 

#include <avr/io.h>

#include "pwm.h"

extern void init_pwm(){
	//Turn on B7 to output mode
	DDRB |= 0x80; 
	
	TCCR0A =(1<<COM0A1) | (1<<WGM01) | (1<<WGM00);	//Set timer counter compare register to Fast PWM

	TCCR0B = (1<<CS01);
	OCR0A = 120;
}

extern inline void set_dc_motor_speed(uint8_t speed){
	OCR0A = speed;
}