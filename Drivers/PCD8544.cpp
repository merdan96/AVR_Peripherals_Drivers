/*
 * PCD8544.cpp
 *
 * Created: 25-Apr-20 8:15:39 PM
 *  Author: Mohamed Merdan
 */ 
#include "PCD8544.h"

PCD8544 :: PCD8544(volatile uint8_t* cPort, uint8_t CS, uint8_t RST, uint8_t DC):
	cport{cPort},
	_csPin{CS},
	_rstPin{RST},
	dcPin{DC}
{

}

void PCD8544 :: begin(){
	
	SPISetup();
	(*(volatile uint8_t*)(cport - 1)) |= (1 << _rstPin) | (1 << _csPin) | (1 << dcPin);
	reset();
	sData(0x21, COMMAND);
	sData(0xC0, COMMAND);
	sData(0x07, COMMAND);
	sData(0x13, COMMAND);
	sData(0x20, COMMAND);
	sData(0x0C, COMMAND);
}

void PCD8544 :: reset(){
	
	(*(volatile uint8_t*)(cport)) &= ~(1 << _rstPin);
	for (uint16_t c = 0;c < 50000;c++);
	(*(volatile uint8_t*)(cport)) |= (1 << _rstPin);
	
}

void PCD8544 :: sData(uint8_t data, uint8_t DC){

	if (DC)
		(*(volatile uint8_t*)(cport)) |= (1 << dcPin);
	else
		(*(volatile uint8_t*)(cport)) &= ~(1 << dcPin);
	
	(*(volatile uint8_t*)(cport)) &= ~(1 << _csPin);
	SPITransmit(data);
	(*(volatile uint8_t*)(cport)) |= (1 << _csPin);
}