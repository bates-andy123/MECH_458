/*
 * interrupt.c
 *
 * Created: 2017-11-18 2:11:00 PM
 *  Author: abates
 */ 

#include <avr/io.h>

void init_interrupt(){
	//EICRA |= _BV(ISC00);
	EICRA |= _BV(ISC01);
	
	EICRB |= _BV(ISC51);
	EICRB |= _BV(ISC41);
	EICRB |= _BV(ISC61);
	EICRB |= _BV(ISC71);
	
	EIMSK |= 0b11110001;
}