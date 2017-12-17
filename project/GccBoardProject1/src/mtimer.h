/*
 * mtimer.h
 *
 * Created: 2017-10-03 1:40:06 PM
 *  Author: abates
 */ 


#ifndef MTIMER_H_
#define MTIMER_H_

extern void mTimer(uint8_t count);
extern void mTimerConfig();
extern inline void uTimer140(uint16_t count);

extern void timer0_init();


#endif /* MTIMER_H_ */