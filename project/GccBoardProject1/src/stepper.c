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
#include "usart.h"
#include "pwm.h"
#include "Buffer.h"
#include <stdbool.h>

#define STEPS_PER_DEGREE		(1.8)
#define STEPS_FOR_90_DEGREES	(50)
#define STEPS_FOR_180_DEGREES	(100)

//Look up tables to get optimal motor torque times

uint16_t less_than_5_rev_up[20] = {280, 265, 250, 235, 220, 205, 190, 160, 150, 140, 130, 120, 110, 100, 90, 90, 90, 90, 90, 90};
uint16_t less_than_5_rev_dw[10] = {90, 120, 150, 180, 210, 240, 270, 300, 330, 360};

uint16_t less_than_10_rev_up[20] = {280, 265, 250, 235, 220, 205, 190, 160, 150, 140, 130, 120, 110, 100, 100, 100, 100, 100, 100, 100};
uint16_t less_than_10_rev_dw[10] = {100, 120, 150, 180, 210, 240, 270, 300, 330, 360};
	
uint16_t less_than_15_rev_up[20] = {320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 130, 120, 110, 110, 110, 110, 110, 110, 110, 110};
uint16_t less_than_15_rev_dw[10] = {100, 120, 150, 180, 210, 240, 270, 300, 330, 360};
	
uint16_t less_than_20_rev_up[20] = {340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 110, 100, 100, 100, 100, 100, 100, 100};
uint16_t less_than_20_rev_dw[10] = {100, 120, 150, 180, 210, 240, 270, 300, 330, 360};
	
uint16_t more_than_20_rev_up[20] = {260, 240, 220, 210, 200, 180, 170, 160, 150, 140, 130, 120, 110, 100, 100, 100, 100, 100, 100, 100};
uint16_t more_than_20_rev_dw[10] = {100, 120, 150, 180, 210, 240, 270, 300, 330, 360};

//Start of local global variables
static steps_lookup[4] = {
	0b110110, //0b110000, //1100xx step_1
	0b101110, //0b000110, //0xx110 step_2
	0b101101, //0b101000, //1010xx step_3
	0b110101  //0b000101  //0xx101 step_4
};

//Local global variables
bool home_flag;
Materials stepper_material_position;

//Drive the stepper to the desired step
static inline drive_stepper(stepper_steps current_step)
{
	PORTC = steps_lookup[current_step];
}

//Initialize the stepper peripheals
extern inline void init_stepper()
{
	home_flag = false;
	DDRC = 0xFF; /* Sets all pins on Port D to output */
}

//A function that tracks the current stepper step and does the next one
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

//Return the current position on the stepper
extern inline Materials get_current_stepper_material(){
	return stepper_material_position;
}

//Check if the stepper is in the home position
extern bool check_if_home(){
	return (bool)(home_flag); 
}

//Block until the stepper reaches the home position
extern void block_till_stepper_home(){
	while (check_if_home() == false){
		step(Clock_Wise);
		mTimer(STEP_TIME_MS);
	}
	stepper_material_position = Black;
}

//Repeat steps until the stepper completes desired number of steps
extern void stepper_repeat_steps(uint8_t steps, stepper_direction dir){
	#define STEP_CONSTANT (2)
	uint16_t *up;
	uint16_t *dw;
	if (buffer_get_total_sorted() < 5)
	{
		//usartTXs("5\r\n");
		up = less_than_20_rev_up;
		dw = less_than_20_rev_dw;
	}
	else if (buffer_get_total_sorted() < 10)
	{
		//usartTXs("10\r\n");
		up = less_than_20_rev_up;
		dw = less_than_20_rev_dw;
	}//*/
	else if (buffer_get_total_sorted() < 15)
	{
		//usartTXs("15\r\n");
		up = less_than_20_rev_up;
		dw = less_than_20_rev_dw;
	}
	else if (buffer_get_total_sorted() < 20)
	{
		up = less_than_20_rev_up;
		dw = less_than_20_rev_dw;
	}else{
		up = less_than_20_rev_up;
		dw = less_than_20_rev_dw;
	}
	
	
	for(uint8_t i = 0; i < steps; i++){
		step(dir);
		if(i < 18){
			uTimer140(*up);
			up++;
		}else if(steps - i < 10){
			uTimer140(*dw);
			dw++;
		}else{
			uTimer140(*up);
		}
		if(steps - i < 36){
			start_pwm(MOTOR_PWM);
		}
	}
}


//Based on the current position go to another position, block until there
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

//The ISR used for the home position
ISR(INT5_vect){
	home_flag = true;
}