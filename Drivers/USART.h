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
#include <stdarg.h>

void serialBegin(uint32_t fcpu, uint32_t baudrate);

void serialWrite(uint8_t character);

uint8_t serialGetChar();

uint8_t serialGetLine(uint8_t* buf, uint8_t MAX_LEN);

void serialPrint(const char* word);

void serialPrintf(const char* seq, ...);

void serialPrintInt(int32_t integer);

void serialPrintDouble(double number);


#endif /* USART_H_ */