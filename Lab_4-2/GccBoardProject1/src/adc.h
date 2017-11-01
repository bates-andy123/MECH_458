/*
 * adc.h
 *
 * Created: 2017-10-31 8:01:17 PM
 *  Author: abates
 */ 


#include <stdbool.h>

#ifndef ADC_H_
#define ADC_H_

uint8_t ADC_result;
bool ADC_result_change_flag;

extern void init_adc();

extern void adc_start_conv();

extern uint8_t read_ADC();

extern void inline ADC_interrupt();

#endif /* ADC_H_ */