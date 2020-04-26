/*
 * SPI.h
 *
 * Created: 24-Apr-20 5:47:09 PM
 *  Author: Mohamed Merdan
 */ 


#ifndef SPI_H_
#define SPI_H_
#include <avr/io.h>

void SPISetup();

uint8_t SPITransmit(uint8_t data);


#endif /* SPI_H_ */