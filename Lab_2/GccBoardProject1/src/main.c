/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "mtimer.h"
#include "led.h"
#include <util/delay_basic.h>

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	TCCR1B |= _BV(CS10);

	board_init();
	
	led_init();
	
	
	while(1){
		night_rider_update();
		mTimer(200);
	}
	
	return (0); //This line returns a 0 value to the calling program

	/* Insert application code here, after the board has been initialized. */
}
