/*
 * SPI.cpp
 *
 * Created: 26-Apr-20 4:50:22 AM
 *  Author: Mohamed Merdan
 */ 
#include "SPI.h"

void SPISetup(){
	DDRB = (1 << PB4) | (1 << PB5) | (1 << PB7);
	PORTB |= (1 << PB4);
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

uint8_t SPITransmit(uint8_t data){
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}