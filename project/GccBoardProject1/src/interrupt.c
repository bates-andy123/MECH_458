/*
 * interrupt.c
 *
 * Created: 2017-11-18 2:11:00 PM
 *  Author: abates
 */ 

#include <avr/io.h>

void init_interrupt(){
	EICRB |= _BV(ISC51);
	
	EIMSK |= 0b00100000;
}