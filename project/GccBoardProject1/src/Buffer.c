/*
 * Buffer.c
 *
 * Created: 2017-11-18 4:26:52 PM
 *  Author: abates
 *
 * Purpose: Custom written circle buffer
 * 		Allows the returning of the first material past certain points
		Also keeps a global count of the amount of items that passed certain points.
 */ 


/*Buffer - Circular FIFO Buffer implementation*/

#include "Buffer.h"
#include "usart.h"
#include <stdlib.h>
#include <avr/io.h>

uint8_t total_sorted;

extern void buf_init(){
	most_recent_pushed_idx = 0;
	current_push_idx = 0;
	first_on_belt = 0;
	most_recent_idx_to_past_second_prox_sensor = 0;
	
	
	//do know about totals
	white_sorted = 0;
	black_sorted = 0;
	alum_sorted = 0;
	steel_sorted = 0;

	total_sorted = 0;

}

extern void buf_new(){
	if(buf_length <= BUFFER_SIZE){
		//Save the item to the buffer
		//belt[current_push_idx].assumed_material = Black;
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

extern set_second_prox_sensor_item(Materials mat, Stage stag){
	belt[most_recent_idx_to_past_second_prox_sensor].assumed_material = mat;
	belt[most_recent_idx_to_past_second_prox_sensor].last_stage = stag;
	most_recent_idx_to_past_second_prox_sensor++;
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
	total_sorted++;
	buf_length--;
}

extern inline uint8_t buffer_get_length(){
	return buf_length;
}

extern inline uint8_t buffer_get_total_sorted(){
	return total_sorted;
}

extern inline buffer_print_first_on_belt(){
	if(belt[first_on_belt].assumed_material == Aluminum){
		//usartTXs("Alum\r\n");
	}else if(belt[first_on_belt].assumed_material == Steel){
		//usartTXs("Steel\r\n");
	}else if(belt[first_on_belt].assumed_material == White){
		//usartTXs("White\r\n");
	}else{
		//usartTXs("Black\r\n");
	}
}