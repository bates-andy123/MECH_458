/*
 * usart.h
 *
 * Created: 2017-12-01 4:24:38 PM
 *  Author: abates
 */ 


#ifndef USART_H_
#define USART_H_


#include <asf.h>
#include <stdint.h>

#define RxEn		0b00010000
#define TxEn		0b00001000
#define Mode8Bit	0b00000110
#define DoubSpeed	0b00000010
#define TxBuffRdy	0b00100000

extern void usartInit (uint16_t baud);
extern void usartTX (unsigned char data);
extern void usartTXs (const char *string);

extern void usartNumTXs(uint16_t num);


#endif /* USART_H_ */