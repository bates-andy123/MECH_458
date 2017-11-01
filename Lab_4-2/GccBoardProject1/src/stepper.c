/*
 * stepper.c
 *
 * Created: 2017-10-18 1:58:29 PM
 *  Author: abates
 */ 

#include "stepper.h"
#include "asf.h"

//Start of local global variables
static steps_lookup[4] = {
	0b110000, //1100xx step_1
	0b000110, //0xx110 step_2
	0b101000, //1010xx step_3
	0b000101  //0xx101 step_4
};

static inline drive_stepper(stepper_steps current_step)
{
	PORTA = current_step;
	PORTD = steps_lookup[current_step];
}

extern inline void init_stepper()
{
	DDRA = 0xFF; /* Sets all pins on Port F to output */
	DDRD = 0xFF; /* Sets all pins on Port F to output */
}

extern void step(stepper_direction dir)
{
	static uint8_t current_step = step_1;
	
	if(dir == Clock_Wise){
		current_step = ((current_step + 1) % amount_of_steps);
	}else{
		if(current_step == step_1)
			current_step = step_4;
		else
			current_step = current_step - 1;
	}
	
	drive_stepper(current_step);
}