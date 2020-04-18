/*
 * Drivers.cpp
 *
 * Created: 14-Apr-20 12:00:41 PM
 * Author : Mohamed Merdan
 */ 
#define F_CPU 8000000L
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "USART.h"
#define BUF_SIZE	30
uint8_t buf[BUF_SIZE];
int main(void)
{
	serialBegin(F_CPU, 9600);
    while (1) 
    {
		serialPrint("Enter a Message: ");
		uint8_t length = serialGetLine(buf, BUF_SIZE);
		serialPrint((const char*)buf);
		serialPrint(", L = ");
		serialPrintlnInt(length);
    }
}

