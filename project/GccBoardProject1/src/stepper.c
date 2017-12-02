/*
 * stepper.c
 *
 * Created: 2017-10-18 1:58:29 PM
 *  Author: abates
 */ 

#include "stepper.h"
#include "asf.h"
#include "main.h"
#include "mtimer.h"
#include <stdbool.h>

#define STEPS_PER_DEGREE		(1.8)
#define STEPS_FOR_90_DEGREES	(50)
#define STEPS_FOR_180_DEGREES	(100)

//Start of local global variables
static steps_lookup[4] = {
	0b110110, //0b110000, //1100xx step_1
	0b101110, //0b000110, //0xx110 step_2
	0b101101, //0b101000, //1010xx step_3
	0b110101  //0b000101  //0xx101 step_4
};

bool home_flag;
Materials stepper_material_position;

static inline drive_stepper(stepper_steps current_step)
{
		PORTC = steps_lookup[current_step];
}

extern inline void init_stepper()
{
	home_flag = false;
	DDRC = 0xFF; /* Sets all pins on Port D to output */
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

extern inline Materials get_current_stepper_material(){
	return stepper_material_position;
}

extern bool check_if_home(){
	return (bool)(home_flag); 
}

extern void block_till_stepper_home(){
	while (check_if_home() == false){
		step(Clock_Wise);
		mTimer(STEP_TIME_MS);
	}
	stepper_material_position = Black;
}

extern void stepper_repeat_steps(uint8_t steps, stepper_direction dir){
	for(uint8_t i = 0; i < steps; i++){
		step(dir);
		if(i <= 4 || i >= (steps-4)){
		mTimer(STEP_TIME_MS);
		}else if(i <= 8 || i >= (steps-8)){
			mTimer((STEP_TIME_MS * 2) / 3);
		}else if(i <= 12 || i >= (steps-12)){
			mTimer(STEP_TIME_MS/2);
		}else if(i <= 16 || i >= (steps-16)){
			mTimer(STEP_TIME_MS/3);
		}else{
			mTimer(STEP_TIME_MS/4);
		}
	}
}

extern void go_to_material(Materials mat){
	if(stepper_material_position == Black){
		if(mat == Steel){
			stepper_repeat_steps(STEPS_FOR_90_DEGREES, Counter_Clock_Wise);
		}else if(mat == Aluminum){
			stepper_repeat_steps(STEPS_FOR_90_DEGREES, Clock_Wise);
		}else{
			stepper_repeat_steps(STEPS_FOR_180_DEGREES, Clock_Wise);
		}
	}
	if(stepper_material_position == Steel){
		if(mat == White)
			stepper_repeat_steps(STEPS_FOR_90_DEGREES, Counter_Clock_Wise);
		else if(mat == Black)
			stepper_repeat_steps(STEPS_FOR_90_DEGREES, Clock_Wise);
		else
			stepper_repeat_steps(STEPS_FOR_180_DEGREES, Clock_Wise);
	}
	if(stepper_material_position == White){
		if(mat == Aluminum)
			stepper_repeat_steps(STEPS_FOR_90_DEGREES, Counter_Clock_Wise);
		else if(mat == Steel)
			stepper_repeat_steps(STEPS_FOR_90_DEGREES, Clock_Wise);
		else
			stepper_repeat_steps(STEPS_FOR_180_DEGREES, Clock_Wise);
	}
	if(stepper_material_position == Aluminum){
		if(mat == Black)
			stepper_repeat_steps(STEPS_FOR_90_DEGREES, Counter_Clock_Wise);
		else if(mat == White){
			stepper_repeat_steps(STEPS_FOR_90_DEGREES, Clock_Wise);
		}else
			stepper_repeat_steps(STEPS_FOR_180_DEGREES, Clock_Wise);
	}//*/
	stepper_material_position = mat;
}

ISR(INT5_vect){
	home_flag = true;
}