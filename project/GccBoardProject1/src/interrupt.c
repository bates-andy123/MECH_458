/*
 * interrupt.c
 *
 * Created: 2017-11-18 2:11:00 PM
 *  Author: abates
 */ 

#include <avr/io.h>

void init_interrupt(){
	//EICRA |= _BV(ISC00);
	EICRA |= _BV(ISC00);
	
	//Stepper motor at home, active low
	EICRB |= _BV(ISC51);
	
	//First promixity sensor, active low
	EICRB |= _BV(ISC41);
	
	//Last promixity sensor, active low
	EICRB |= _BV(ISC61);
	
	//Magnetic detection sensor, active low
	EICRB |= _BV(ISC71);
	
	EIMSK |= 0b11110001;
}