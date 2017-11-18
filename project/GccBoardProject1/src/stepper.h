/*
 * stepper.h
 *
 * Created: 2017-10-18 1:58:44 PM
 *  Author: abates
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_


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



#endif /* STEPPER_H_ */