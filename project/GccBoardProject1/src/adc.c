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

uint16_t ADC_result;
bool ADC_keep_running;

extern void init_adc(){
	ADMUX = (1<< REFS0)|(1<<MUX0);			// Left adjust, and use VCC as top reference
	ADCSRA=(1<<ADEN)|(1<<ADIE);							//Set the values of the ADC Enable and ADC Interrupt Enable bits to 1
	DIDR0 = (1<<ADC1D);									//Turns off the digital input buffer for ADC1 on PF1
	
	ADC_result = 0;
	ADC_keep_running = false;
}

extern void adc_start_conv(){
	// initialize the ADC, start one conversion at the beginning ==========
	ADCSRA |= _BV(ADSC);
}

extern uint16_t read_ADC(){
	return ADC_result;
}

extern void ADC_interrupt(){
	ADC_result = (ADCH << 8) + ADCL;
	adc_start_conv();
}