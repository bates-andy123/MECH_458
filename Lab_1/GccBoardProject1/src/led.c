/*
 * led.c
 *
 * Created: 2017-10-03 1:48:30 PM
 *  Author: abates
 */ 

#include <asf.h>


extern void led_init(){
	DDRD = 0b11111111; /* Sets all pins on Port D to output */
	PORTD = 0x07; /* initialize port to high – turn on LEDs */
}

extern void night_rider_update(){
	//local variables
	static uint8_t current_LED = 0;
	if(current_LED < 5){
		PORTD <<= 1;	
	}else{
		PORTD >>= 1;	
	}
	
	current_LED++;
	current_LED %= 10;
}