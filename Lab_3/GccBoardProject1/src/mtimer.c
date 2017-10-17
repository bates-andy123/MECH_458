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
}

extern void mTimer(int count)
{
	int i = 0;
	
	TCCR1B |= _BV(WGM12); /*CTC mode*/
	
	OCR1A = 0x03e8; //1000
	
	TCNT1 = 0x0000;
	
	TIMSK1 |= 0b00000010;
	
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