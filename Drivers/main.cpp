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
#include "SPI.h"
#include "PCD8544.h"
#define  _RST 0
#define _CE 4
#define DC 1
//#include "ADC.h"
//#define BUF_SIZE	30
//uint8_t buf[BUF_SIZE];
uint8_t digits[] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B};

PCD8544 nokia5110(&PORTB, _CE, _RST, DC);

int main(void)
{
	serialBegin(F_CPU, 9600);
	
	nokia5110.begin();
	
	int h = 1;
	while(1){
		for (int i = 0;i<84 * 6;i++)
		{
			nokia5110.sData(0x00, DATA);
		}
		for (int i = 0;i<84 * 6;i++)
		{
			nokia5110.sData((i%h)? 0x00 : 0xFF, DATA);
		}
		h = (h == 4) ? 1 : (h+1);
		_delay_ms(250);
	}
		//_delay_ms(500);
		
		//serialPrintf("/d\n", SPITransmit(~(digits[i])));
		//i = (i == 9) ? 0 : (i+1);
		/*serialPrint("Enter a Message: ");
		uint8_t length = serialGetLine(buf, BUF_SIZE);
		serialPrintf("/s, L = /d\n", buf, length);*/
}

