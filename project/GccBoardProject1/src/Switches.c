/*
 * Switches.c
 *
 * Created: 2017-10-16 8:41:40 PM
 *  Author: abates
 */ 

#include <inttypes.h>
#include "Switches.h"
#include "asf.h"

extern inline uint8_t is_button_pressed(button but){
	return((PINC & but) == but);
}