/*
 * mtimer.c
 *
 * Created: 2017-10-03 1:41:07 PM
 *  Author: abates
 */ 

#include <asf.h>
#include <avr/io.h>
#include "mtimer.h"
#include "..\..\..\..\..\toolchain\avr8\avr8-gnu-toolchain\avr\include\avr\iousbxx6_7.h"

/*This is the driver for the timer*/
void mTimer(int count){
    /* System clock is 8MHz. The non-prescaled
    timer will work at 1 MHZ and you can scale the value by
    8, 64, 256, etfc.. The period is 1 microsecond. */
    int i;
 
    i = 0;
    /*Set the wavefrom generation mode bit description to clear
    timer on compare math mode(CTC) only */
 
    TCCR1B|=_BV(WGM12); /*sets WGM bits to 0100, WGM is spread over two registers */
 
    OCR1A = 0x03e8; /*set output compare register for 1000 cycles/ 1 milisecond */
 
    TCNT1= 0x0000; /*sets the initial value of the timer counter to 0x0000*/
 
    TIMSK1 = TIMSK1 |0b00000010; /*enable the output compare interrupt*/
 
    TIFR1 |=_BV(OCF1A); /*clear the timer interupt flag and begin timer*/
/*poll the timer to determine when the timer has reached 0x03e8*/
    while(i<count){
 
        if((TIFR1 & 0x02) ==0x02){
            /*clear the interrupt flag by writing a 1 to the bit*/
            TIFR1 |=_BV(OCF1A);
            i++;
            /* Note the timer resets on its own*/
        } /*end if */
 
    }//end while
    return;
}