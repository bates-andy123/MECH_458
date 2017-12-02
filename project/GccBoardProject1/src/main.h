/*
 * main.h
 *
 * Created: 2017-11-18 2:46:42 PM
 *  Author: abates
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <stdbool.h>

#define STEP_TIME_MS	(15)
#define TIME_BETWEEN_STEPS	(2500)

#define BLACK_ABOVE_TH_10b		(929)
#define BLACK_ABOVE_TH_8b		(BLACK_ABOVE_TH_10b/4)

#define WHITE_ABOVE_TH_10b		(850)
#define WHITE_ABOVE_TH_8b		(WHITE_ABOVE_TH_10b/4)

#define STEEL_ABOVE_TH_10b		(475)
#define STEEL_ABOVE_TH_8b		(STEEL_ABOVE_TH_10b/4)

typedef enum
{
	Aluminum = 0,
	White,
	Steel,
	Black,
	Unknown_material,
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