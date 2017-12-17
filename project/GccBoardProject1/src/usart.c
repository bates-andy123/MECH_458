/*
 * UART.c
 *
 * Created: 2017-11-29 1:00:13 PM
 *  Author: abates
 */ 

#include "usart.h"
#include <string.h>
#include "mtimer.h"

//Initialize UART
extern void usartInit (uint16_t baud)
{
	//Set baud rate
	UBRR1H = (uint8_t)(baud >> 8);
	UBRR1L = (uint8_t)(baud);
	
	UCSR1A |= DoubSpeed;
	
	UCSR1B |= TxEn;			//Enable TX mode for USART1
	UCSR1C |= Mode8Bit;		//Set Usart to 8 bit data mode
	
}
//This function displace one char at a time on the serial port
//
//Pass this function a char.
extern void usartTX (unsigned char data)
{
	while (!(UCSR1A & TxBuffRdy));	//Wait for the TX buffer to be ready for data
	
	UDR1 = data;
}
//This function can display strings on the serial port by calling the display char
//function.
//Pass this function a string.
extern void usartTXs (const char *string)
{
	uint8_t c = 0;
	
	while (string [c] != 0)
	{
		usartTX(string[c]);
		c++;
	}
}

//Convert a number to ascii representation
extern void usartNumTXs(uint16_t num){

	usartTX((char)(((num/1000)%10) + 48));
	usartTX((char)(((num/100)%10) + 48));
	usartTX((char)(((num/10)%10) + 48));
	usartTX((char)((num%10) + 48));
}