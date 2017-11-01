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

uint8_t ADC_result;
bool ADC_result_change_flag;

extern void init_adc(){
	/*cli(); // disable all of the interrupt ==========================
	// config the external interrupt ======================================
	EIMSK |= (_BV(INT2)); // enable INT2
	EICRA |= (_BV(ISC21) | _BV(ISC20)); // rising edge interrupt
	// config ADC =========================================================
	// by default, the ADC input (analog input is set to be ADC0 / PORTF0
	ADCSRA |= _BV(ADEN); // enable ADC
	ADCSRA |= _BV(ADIE); // enable interrupt of ADC
	ADMUX |= _BV(ADLAR) | _BV(REFS0);
	// set the PORTA as output to display the ADC result ==================
	DDRA = 0xff;
	// sets the Global Enable for all interrupts ==========================
	sei();//*/
	
	ADMUX = (1<< REFS0)|(1<<MUX0)|(1<<ADLAR);			// Left adjust, and use VCC as top reference
	ADCSRA=(1<<ADEN)|(1<<ADIE);							//Set the values of the ADC Enable and ADC Interrupt Enable bits to 1
	DIDR0 = (1<<ADC1D);									//Turns off the digital input buffer for ADC1 on PF1
	
	PORTA |= 0x01;
	
	ADC_result = 0;
	ADC_result_change_flag = false;
}

extern inline void adc_start_conv(){
	// initialize the ADC, start one conversion at the beginning ==========
	ADCSRA |= _BV(ADSC);
	PORTA |= 0x02;
}

extern bool peak_for_adc_change(){
	return ADC_result_change_flag;
	PORTA ^= 0x40;
}

extern uint8_t read_ADC(){
	ADC_result_change_flag = false;
	return ADC_result;
	PORTA ^= 0x10;
}