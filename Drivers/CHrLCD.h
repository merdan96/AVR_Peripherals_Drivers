/*
 * CHrLCD.h
 *
 * Created: 17-Mar-20 10:03:24 PM
 *  Author: Mohamed Merdan
 */ 


#ifndef CHRLCD_H_
#define CHRLCD_H_

#include "config.h"
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

#define LCD_FIRST_ROW 0x80
#define LCD_SECOND_ROW 0xC0
#define LCD_CLEAR 0x01

#define LCD_FUNCTIONS 0x20
#define LCD_DATA_MODE 0x10
#define LCD_NO_LINES 0x08
#define LCD_DOT_FORMAT 0x04

#define LCD_DISPLAY_CONTROL 0x08
#define LCD_DISPLAY_ON 0x04
#define LCD_CURSOR_ON_OFF 0x02
#define LCD_CURSOR_BLINK_ON_OFF 0x01

#define DATA 1
#define COMMAND 0

#define CMASK(a, b) ((1 << a) | (1 << b))
#if defined(SINGLE_LCD)

#elif defined(MULTIPLE_LCD)

class CHrLCD {
	private:
		volatile uint8_t *cport;
		volatile uint8_t *dport;
		uint8_t rs, en, doi;
		uint8_t valid;
		uint8_t _8_bit_mode;
		void wData(uint8_t cmd, uint8_t DC);
		void pulseEnable(uint8_t DC);
		
	public:
		
		CHrLCD(volatile uint8_t* cPort, uint8_t RS, uint8_t EN, volatile uint8_t* dPort, uint8_t dMask);
		void init();
		void print(const char* word);
		void print(int32_t integer);
		void setCursor(uint8_t row, uint8_t col = 0);
};
#endif // MULTIPLE_LCD


#endif /* CHRLCD_H_ */