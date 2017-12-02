/*
 * adc.h
 *
 * Created: 2017-10-31 8:01:17 PM
 *  Author: abates
 */ 


#include <stdbool.h>

#ifndef ADC_H_
#define ADC_H_

uint16_t ADC_result;
bool ADC_result_change_flag;

extern void init_adc();

extern inline void adc_start_conv();

extern inline void adc_stop_conv();

extern uint16_t read_Min_ADC();

extern inline void ADC_interrupt();

extern void ADC_reset_count();

extern uint16_t ADC_return_Count();

#endif /* ADC_H_ */