/*
 * Buffer.h
 *
 * Created: 2017-11-18 4:27:20 PM
 * Author: abates
 * Purpose: Prototypes to the buffer file, allowing scope to be maintained. 
 *
 */ 


#ifndef BUFFER_H_
#define BUFFER_H_



#include <string.h>
#include <avr/io.h>
#include <stdbool.h>
#include "main.h"

#define BUFFER_SIZE		(50)

typedef struct buf{
	uint16_t max_adc;
	bool magnetic;
	Materials assumed_material;
	Stage last_stage;
}Buf;

Buf belt[BUFFER_SIZE];

uint8_t first_on_belt;
uint8_t most_recent_pushed_idx;
uint8_t current_push_idx;
uint8_t most_recent_idx_to_past_second_prox_sensor;
uint8_t buf_length;

uint8_t white_sorted;
uint8_t black_sorted;
uint8_t alum_sorted;
uint8_t steel_sorted;

extern void buf_init();

extern void buf_new();

extern buf_is_magnetic();

extern inline Materials buf_get_first_item_material();

extern set_first_item(Materials mat, Stage stag);

extern inline remove_first_item();

extern set_second_prox_sensor_item(Materials mat, Stage stag);

extern inline buffer_print_first_on_belt();

extern inline uint8_t buffer_get_total_sorted();

extern inline uint8_t buffer_get_length();

#endif /* BUFFER_H_ */