/*
 * mtimer.c
 *
 * Created: 2017-10-03 1:41:07 PM
 *  Author: abates
 */ 

#include <asf.h>
#include <avr/io.h>
#include "mtimer.h"

extern void mTimerConfig()
{
	/* Insert system clock initialization code here (sysclk_init()). */
	TCCR1B |= _BV(CS10);
	TCCR1B |= _BV(WGM12); /*CTC mode*/
	
	OCR1A = 44; //50
}

extern void timer0_init()
{
	TCCR3B |= _BV(CS30);
	TIMSK3 |= _BV(OCIE3A);
	TCCR3A |= _BV(WGM31);
	OCR3A = 50; //1000
}

extern void mTimer(uint8_t count)
{
	uint8_t i = 0;
	
	TCNT1 = 0x0000;
	
	//TIMSK1 |= 0b00000010;
	
	TIFR1 |= _BV(OCF1A);
	
	while (i < count)
	{
		uTimer140(20);
		i++;
	}
	return;
}

extern void inline uTimer140(uint16_t count){
	uint16_t i = 0;
	
	TCNT1 = 0x0000;
	
	//TIMSK1 |= 0b00000010;
	
	TIFR1 |= _BV(OCF1A);
	
	while (i < count)
	{
		if ((TIFR1 & 0x02) == 0x02)
		{
			TIFR1 |= _BV(OCF1A);
			i++;
		}
	}
	return;
}

/*
*/