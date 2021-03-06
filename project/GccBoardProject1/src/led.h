/*
 * led.h
 *
 * Created: 2017-10-03 1:50:52 PM
 *  Author: abates
 */ 


#ifndef LED_H_
#define LED_H_

typedef enum{
	off = 0x00,
	red = 0x1,
	green = 0x2,
	orange = 0x3
}Status_LED_Colour;

typedef enum{
	top = 6,
	bottom = 4
}Status_LED_Position;

extern void init_led();

extern void write_to_led_display(uint8_t value);

extern void night_rider_update();

extern void status_leds(Status_LED_Position pos, Status_LED_Colour colour);


#endif /* LED_H_ */