/*
 * Buffer.c
 *
 * Created: 2017-11-18 4:26:52 PM
 *  Author: abates
 */ 


/*Buffer - Circular FIFO Buffer implementation*/

#include "Buffer.h"
#include <stdlib.h>
#include <avr/io.h>

extern void buf_init(){
	most_recent_pushed_idx = 0;
	current_push_idx = 0;
	starting_idx = 0;
	first_on_belt = 0;
}

extern void buf_new(){
	if(buf_length <= BUFFER_SIZE){
		//Save the item to the buffer
		belt[current_push_idx].assumed_material = Black;
		belt[current_push_idx].last_stage = Promixity_stage;
		belt[current_push_idx].magnetic = false;
		belt[current_push_idx].max_adc = 0;

		//Increment the variables for next time		
		most_recent_pushed_idx = current_push_idx;
		current_push_idx = (current_push_idx + 1) % BUFFER_SIZE;
		buf_length++;
	}
}

extern set_first_item(Materials mat, Stage stag){
	belt[first_on_belt].assumed_material = mat;
	belt[first_on_belt].last_stage = stag;
}

extern buf_is_magnetic(){
	belt[most_recent_pushed_idx].magnetic = true;
	belt[most_recent_pushed_idx].assumed_material = Steel;
}

extern inline Materials buf_get_first_item_material(){
	return belt[first_on_belt].assumed_material;
}

extern inline remove_first_item(){
	belt[first_on_belt].last_stage = Complete;
	first_on_belt++;
}