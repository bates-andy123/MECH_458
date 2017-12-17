/*
 * adc.h
 *
 * Created: 2017-10-31 8:01:17 PM
 * Author: abates
 *
 * Purpose: This header file provides the prototypes to the ADC files 
 */ 


#include <stdbool.h>

#ifndef ADC_H_
#define ADC_H_

uint16_t ADC_result;
bool ADC_result_change_flag;
bool ADC_keep_running;

extern void init_adc();  //Initialize the ADC

extern inline void adc_start_conv();  //Do and ADC conversion

extern inline void adc_stop_conv(); //Stop the ADC and reset all the variables to zero

extern uint16_t read_Min_ADC();  //Return the minimum the ADC result

extern inline void ADC_interrupt();

extern inline void ADC_reset_count();

extern inline uint16_t ADC_return_Count();

extern inline uint16_t ADC_return_time_under();

extern inline uint16_t biggest_starting_value_func();

extern void set_default_voltage();

#endif /* ADC_H_ */