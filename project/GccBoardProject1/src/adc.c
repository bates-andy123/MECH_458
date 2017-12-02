/*
 * adc.c
 *
 * Created: 2017-10-31 8:00:58 PM
 *  Author: abates
 */ 

#include <avr/io.h>
#include <avr/interrupt.h> 
#include <stdbool.h>

#include "adc.h"
#include "mtimer.h"
#include "led.h"

volatile uint16_t ADC_Min_result;
bool ADC_keep_running;

extern void init_adc(){
	ADMUX = (1<< REFS0)|(1<<MUX0);			// Left adjust, and use VCC as top reference
	ADCSRA=(1<<ADEN)|(1<<ADIE);							//Set the values of the ADC Enable and ADC Interrupt Enable bits to 1
	DIDR0 = (1<<ADC1D);									//Turns off the digital input buffer for ADC1 on PF1
	
	ADC_Min_result = 0xFFFF;
	ADC_keep_running = false;
}

static inline void adc_do_conv(){
	// initialize the ADC, start one conversion at the beginning ==========
	ADCSRA |= _BV(ADSC);
}

extern inline void adc_start_conv(){
	// initialize the ADC, start one conversion at the beginning ==========
	ADCSRA |= _BV(ADSC);
	//PORTA ^= 0x20;
}

extern inline void adc_stop_conv(){
	ADC_Min_result = 0xFFFF;
}


extern uint16_t read_Min_ADC(){
	return ADC_Min_result;
}

extern void ADC_interrupt(){
	ADC_result = ADC;
	if(ADC_Min_result > ADC){
		ADC_Min_result = ADC;
	}
	adc_start_conv();
	//PORTA = ADC_Min_result;
	//status_leds(bottom, ADC_Min_result>>6);
}