/*
 * stepper.c
 *
 * Created: 2017-10-18 1:58:29 PM
 *  Author: abates
 */ 

#include "stepper.h"
#include "asf.h"

extern inline void init_stepper()
{
	DDRF = 0xFF; /* Sets all pins on Port F to output */
}

extern void step()
{
	

}