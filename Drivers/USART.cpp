/*
 * USART.c
 *
 * Created: 14-Apr-20 12:11:34 PM
 *  Author: Mohamed Merdan
 */ 
#include "USART.h"

void serialBegin(uint32_t fcpu, uint32_t baudrate){
	//set-up baudrate
	uint16_t ubrr = fcpu / 16 / baudrate - 1;
	UBRRL = (uint8_t) ubrr;
	UBRRH = (uint8_t) (ubrr >> 8);
	//RX&TX enabled
	UCSRB = (1 << RXEN) | (1 << TXEN);
	//8-bit character size set
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
}

void serialPrint(const char* word){
	while (*word)
	{
		serialTransmit(*word);
		word++;
	}
}

void serialPrintInt(uint32_t integer){
	uint32_t factor = 1;
	
	if (integer == 0) serialTransmit('0');
	else
	{
		while ((integer / factor) / 10) factor *= 10;
		
		while (factor)
		{
			serialTransmit((48 + ((integer / factor) - ((integer / (factor * 10)) * 10))));
			factor /= 10;
		}
	}
}

void serialPrintlnInt(uint32_t integer){
	serialPrintInt(integer);
	serialTransmit('\n');
}

void serialPrintln(const char* word){
	serialPrint(word);
	serialTransmit('\n');
}

void serialPrintln(char word){
	serialTransmit(word);
	serialTransmit('\n');
}

void serialTransmit(uint8_t character){
	
	while (!(UCSRA & (1 << UDRE)));
	UDR = character;
}

uint8_t serialGetChar(){
	while (!(UCSRA & (1 << RXC)));
	return UDR;
}

uint8_t serialGetLine(uint8_t* buf, uint8_t MAX_LEN){
	uint8_t i = 0;
	char c = serialGetChar();
	while (c != '\n' && c != '\r')
	{
		if (i < MAX_LEN - 1){
			buf[i] = c;
			i++;
		}
		c = serialGetChar();
	}
	buf[i] = 0;
	serialGetChar();
	return i;
}