/*
 * USART.h
 *
 * Created: 14-Apr-20 12:11:50 PM
 *  Author: Mohamed Merdan
 */ 

#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void serialBegin(uint32_t fcpu, uint32_t baudrate);

void serialTransmit(uint8_t character);

uint8_t serialGetChar();

uint8_t serialGetLine(uint8_t* buf, uint8_t MAX_LEN);

void serialPrint(const char* word);

void serialPrintInt(uint32_t integer);

void serialPrintlnInt(uint32_t integer);

void serialPrintln(char word);

void serialPrintln(const char* word);

#endif /* USART_H_ */