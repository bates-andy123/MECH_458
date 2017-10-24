/*
 * led.c
 *
 * Created: 2017-10-03 1:48:30 PM
 *  Author: abates
 */ 

#include <asf.h>


extern void init_led(){
	DDRA = 0b11111111; /* Sets all pins on Port D to output */
	PORTA = 0x0; /* initialize port to high – turn on LEDs */
}

extern void night_rider_update(){
	//local variables
	static uint8_t current_LED = 0;
	if(current_LED < 5){
		PORTA <<= 1;	
	}else{
		PORTA >>= 1;	
	}
	
	current_LED++;
	current_LED %= 10;
}