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

uint8_t ADC_result;
bool ADC_result_change_flag;

extern void init_adc(){
	ADMUX = (1<< REFS0)|(1<<MUX0)|(1<<ADLAR);			// Left adjust, and use VCC as top reference
	ADCSRA=(1<<ADEN)|(1<<ADIE);							//Set the values of the ADC Enable and ADC Interrupt Enable bits to 1
	DIDR0 = (1<<ADC1D);									//Turns off the digital input buffer for ADC1 on PF1
	
	PORTA ^= 0x01;
	
	ADC_result = 0;
	ADC_result_change_flag = false;
}

extern inline void adc_start_conv(){
	// initialize the ADC, start one conversion at the beginning ==========
	ADCSRA |= _BV(ADSC);
	PORTA ^= 0x02;
}

extern uint8_t read_ADC(){
	return ADC_result;
	//PORTA ^= 0x10; 
}

extern void inline ADC_interrupt(){
	ADC_result = ADCH;
	adc_start_conv();
	//PORTA ^= 0x40;
	PORTA = ADCH;
	mTimer(1000);
}