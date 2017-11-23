/*
 * main.h
 *
 * Created: 2017-11-18 2:46:42 PM
 *  Author: abates
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <stdbool.h>

#define STEP_TIME_MS	(10)
#define TIME_BETWEEN_STEPS	(2500)

typedef enum
{
	Aluminum,
	White,
	Steel,
	Black,
	amount_of_materials
}Materials;

typedef enum
{
	Unknown_stage,
	Promixity_stage,
	ADC_stage,
	Delay_stage,
	Complete
}Stage;

#endif /* MAIN_H_ */