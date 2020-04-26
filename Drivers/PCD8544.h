/*
 * PCD8544.h
 *
 * Created: 25-Apr-20 3:15:26 PM
 *  Author: Mohamed Merdan
 */ 


#ifndef PCD8544_H_
#define PCD8544_H_

#include <stdint.h>
#include <avr/io.h>
//#include <util/delay.h>

#include "SPI.h"

#define RSTDELAY 100
#define COMMAND 0
#define DATA 1

class PCD8544 {
	
	private:
		volatile uint8_t *cport;
		uint8_t _csPin, _rstPin, dcPin;
		//void sData(uint8_t data, uint8_t DC);
		
	public:
		PCD8544(volatile uint8_t* cPort, uint8_t CS, uint8_t RST, uint8_t DC);
		void begin();
		void reset();
		void sData(uint8_t data, uint8_t DC);
};




#endif /* PCD8544_H_ */