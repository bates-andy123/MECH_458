/*
 * stepper.h
 *
 * Created: 2017-10-18 1:58:44 PM
 *  Author: abates
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdbool.h>
#include <avr/io.h>
#include "main.h"

typedef enum 
{
	step_1 = 0, 
	step_2,
	step_3,
	step_4,
	amount_of_steps
}stepper_steps;

typedef enum
{
	Clock_Wise = 1,
	Counter_Clock_Wise = -1
}stepper_direction;


/*
Purpose:	Used to initialize the stepper GPIO pins
Returns:	None
*/
extern inline void init_stepper();

/*
Purpose:	Get the stepper to do one step in desired direction
Argument:	The the direction you want
Returns:	None
*/
extern void step(stepper_direction dir);

extern bool check_if_home();
extern void block_till_stepper_home();

extern void stepper_repeat_steps(uint8_t steps, stepper_direction dir);

extern void go_to_material(Materials mat);
extern inline Materials get_current_stepper_material();

#endif /* STEPPER_H_ */