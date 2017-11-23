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

volatile uint8_t ADC_Min_result;
bool ADC_keep_running;

extern void init_adc(){
	ADMUX = (1<< REFS0)|(1<<MUX0)|(1<<ADLAR);			// Left adjust, and use VCC as top reference
	ADCSRA=(1<<ADEN)|(1<<ADIE);							//Set the values of the ADC Enable and ADC Interrupt Enable bits to 1
	DIDR0 = (1<<ADC1D);									//Turns off the digital input buffer for ADC1 on PF1
	
	ADC_Min_result = 0xFF;
	ADC_keep_running = false;
}

static void adc_do_conv(){
	// initialize the ADC, start one conversion at the beginning ==========
	ADCSRA |= _BV(ADSC);
}

extern void adc_start_conv(){
	// initialize the ADC, start one conversion at the beginning ==========
	ADCSRA |= _BV(ADSC);
	//PORTA ^= 0x20;
}

/*
extern void adc_start_conv(){
	// initialize the ADC, start one conversion at the beginning ==========
	ADC_keep_running = true;
	ADC_Max_result = 0;
	adc_do_conv();
}//*/

extern void adc_stop_conv(){
	ADC_Min_result = 0xFFFF;
}


extern uint16_t read_Max_ADC(){
	return ADC_Min_result;
}

extern void ADC_interrupt(){
	ADC_result = ADCH;
	if(ADC_Min_result > ADCH){
		ADC_Min_result = ADCH;
	}
	adc_start_conv();
	PORTA = ADC_Min_result;
	//OCR0A=ADCH;
	
}

/*extern void ADC_interrupt(){
	//status_leds(top, orange);
	uint16_t adc_temp_result = (ADCH << 8) + ADCL;
	//if(adc_temp_result > ADC_Max_result || true){
	ADC_Max_result = adc_temp_result;
	//}	if(ADC_keep_running == true){
	adc_do_conv();
	PORTA = ADCL;
}*/