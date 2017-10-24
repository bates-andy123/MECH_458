/*
 * Switches.h
 *
 * Created: 2017-10-16 8:42:08 PM
 *  Author: abates
 */ 


#ifndef SWITCHES_H_
#define SWITCHES_H_

#define BUTTON_DEBOUNCE_MS	(20)

typedef enum{
	go_button = 0x01,
	pause_button = 0x02
} button;


#define BUTTON_STATUS(option) ((PINC & option) == option)

extern uint8_t is_button_pressed(button but);

#endif /* SWITCHES_H_ */