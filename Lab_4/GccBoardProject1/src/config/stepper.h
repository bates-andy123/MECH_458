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
	step_1 = 0b110000,
	step_2 = 0b000110,
	step_3 = 0b101000,
	step_4 = 0b000101
}stepper_steps;

typedef enum
{
	step_CW = 0,
	step_CounterCW
}stepper_direction;

/*
Purpose:	Used to initialize the stepper GPIO pins
Argument:	The the direction you want
Returns:	None
*/
extern void step(stepper_direction dir)

/*
Purpose:	Get the stepper to do one step in desired direction
Returns:	None
*/
extern void step();



#endif /* STEPPER_H_ */