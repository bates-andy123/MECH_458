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
#include "usart.h"

uint16_t ADC_Min_result;
uint16_t Total_Count;
uint16_t default_voltage;
uint16_t default_voltage_90_percent;
uint16_t time_under_90_percent_volt;

extern void init_adc(){
	ADMUX = (1<< REFS0)|(1<<MUX0);			// Left adjust, and use VCC as top reference
	ADCSRA=(1<<ADEN)|(1<<ADIE);							//Set the values of the ADC Enable and ADC Interrupt Enable bits to 1
	DIDR0 = (1<<ADC1D);									//Turns off the digital input buffer for ADC1 on PF1
	
	ADC_Min_result = 0xFFFF;
	Total_Count = 0;
	ADC_keep_running = false;
	
	
	default_voltage = 0;
	default_voltage_90_percent = 0;
	time_under_90_percent_volt = 0;
}

extern void set_default_voltage(){
	default_voltage = ADC;
	//default_voltage_90_percent = (ADC*20)/18;
	default_voltage_90_percent = 976;
	usartTXs("Thres: ");
	usartNumTXs(default_voltage_90_percent);
	usartTXs("\r\n");
}

extern inline void adc_start_conv(){
	// initialize the ADC, start one conversion at the beginning ==========
	ADCSRA |= _BV(ADSC);
	//PORTA ^= 0x20;
}

extern inline void adc_stop_conv(){
	ADC_Min_result = 0xFFFF;
}


extern inline uint16_t read_Min_ADC(){
	return ADC_Min_result;
}

extern inline void ADC_reset_count(){
	Total_Count = 0;
	time_under_90_percent_volt = 0;
}

extern inline uint16_t ADC_return_Count(){
	return Total_Count;
}

extern inline uint16_t ADC_return_time_under(){
	return time_under_90_percent_volt;
}

extern inline void ADC_interrupt(){
	Total_Count = Total_Count + 1;
	if(ADC_Min_result > ADC){
		ADC_Min_result = ADC;
	}
	if(default_voltage_90_percent > ADC){
		time_under_90_percent_volt = time_under_90_percent_volt + 1;
	}
	//*/
	/*
	if(ADC_keep_running == true){
		usartNumTXs(ADC);
	}//*/
	//PORTA = Total_Count;
	adc_start_conv();
}