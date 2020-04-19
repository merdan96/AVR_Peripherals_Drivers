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

void serialPrintf(const char* seq, ...){
	va_list args;
	va_start(args, seq);
	
	while (*seq)
	{
		if (*seq == '/')
		{
			seq++;
			switch (*seq)
			{
				case 'd':
				{
					int32_t i = va_arg(args, int);
					serialPrintInt(i);
				}
				break;
				case 's':
				{
					uint8_t* buf = va_arg(args, uint8_t*);
					serialPrint((const char*)buf);
				}
				break;
				case 'f':
				{
					double number = va_arg(args, double);
					serialPrintDouble(number);
				}
				break;
				case 'c':
				{
					uint8_t c = va_arg(args, int);
					serialWrite(c);
				}
				break;
				default:
					serialWrite(*seq);
				break;
			}
		}
		else
		{
			serialWrite(*seq);
		}
		seq++;
	}
	va_end(args);
}

void serialPrint(const char* word){
	while (*word)
	{
		serialWrite(*word);
		word++;
	}
}

void serialPrintDouble(double number){
	int32_t integer = (int32_t) number;
	uint32_t fraction = (uint32_t)((number - integer) * 1000);
	serialPrintInt(integer);
	serialWrite('.');
	serialPrintInt(fraction);
}

void serialPrintInt(int32_t integer){
	uint32_t factor = 1;
	
	if (integer == 0) serialWrite('0');
	else
	{
		if (integer < 0)
		{
			serialWrite('-');
			integer *= -1;
		}
		while ((integer / factor) / 10) factor *= 10;
		
		while (factor)
		{
			serialWrite((48 + ((integer / factor) - ((integer / (factor * 10)) * 10))));
			factor /= 10;
		}
	}
}


void serialWrite(uint8_t character){
	
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