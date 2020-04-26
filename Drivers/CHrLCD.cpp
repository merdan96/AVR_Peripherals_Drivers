/*
 * CHrLCD.c
 *
 * Created: 18-Mar-20 12:11:29 AM
 *  Author: Mohamed Merdan
 */ 
#include "CHrLCD.h"


#if defined(SINGLE_LCD)

#elif defined(MULTIPLE_LCD)

//define LCD control and data pins and initialize LCD
CHrLCD :: CHrLCD(volatile uint8_t* cPort, uint8_t RS, uint8_t EN, volatile uint8_t* dPort, uint8_t dMask):
	cport{cPort},
	dport{dPort},
	rs{RS},
	en{EN},
	doi{(uint8_t)(dMask / 15)},
	valid{(doi == 1 || doi == 16 || doi == 17)},
	_8_bit_mode{(dMask == 0xFF)}
{
	
}

void CHrLCD :: init()
{
	if(valid){
		doi /= 4;
		(*(volatile uint8_t*)(cport - 1)) |= CMASK(rs, en);
		(*(volatile uint8_t*)(dport - 1)) |= (_8_bit_mode) ? 0xFF : (0x0F << doi);
	}
	_delay_ms(20);
	if (_8_bit_mode)
	{
		wData((LCD_FUNCTIONS | LCD_NO_LINES | LCD_DATA_MODE), COMMAND);//8-bit,2-line,5*8
	}
	else
	{
		wData((LCD_FUNCTIONS | LCD_NO_LINES), COMMAND);//4-bit,2-line,5*8
	}
	wData((LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON), COMMAND);//display on,cursor off,cursor blink off
	wData(0x06, COMMAND);
	wData(LCD_CLEAR, COMMAND);//clear display
	wData(LCD_FIRST_ROW, COMMAND);//set DDRAM address to 0
}

void CHrLCD :: print(const char* word)
{
	while (*word != 0)
	{
		wData(*word, DATA);
		word++;
	}
}

void CHrLCD :: print(int32_t integer){
	uint32_t factor = 1;
	
	if (integer == 0) wData('0', DATA);
	else
	{
		while ((integer / factor) / 10) factor *= 10;
	
		while (factor)
		{
			wData((48 + ((integer / factor) - ((integer / (factor * 10)) * 10)))
					, DATA);
			factor /= 10;
		}
	}
}

void CHrLCD :: wData(uint8_t cmd, uint8_t DC)
{
	(*(volatile uint8_t*)(cport)) &= (~CMASK(rs, en));
	
	if(!(_8_bit_mode))
	{
		((*(volatile uint8_t*)(dport)) &= ~(0x0F << doi));
		(*(volatile uint8_t*)(dport)) |= ((cmd & 0xF0) >> (4 - doi));
		pulseEnable(DC);
		
		_delay_us(200);
		((*(volatile uint8_t*)(dport)) &= ~(0x0F << doi));
		(*(volatile uint8_t*)(dport)) |= ((cmd & 0x0F) << doi);
		
		(*(volatile uint8_t*)(cport)) &= (~CMASK(rs, en));
	}
	else
	{
		(*(volatile uint8_t*)(dport)) = cmd;
	}
	pulseEnable(DC);
	
	_delay_ms(2);
}

void CHrLCD :: setCursor(uint8_t row, uint8_t col){
	
	col = (col > 15) ? 15 : ((col < 0) ? 0 : col);
	if (row == 0) wData((LCD_FIRST_ROW | col), COMMAND);
	
	else if (row == 1) wData((LCD_SECOND_ROW | col), COMMAND);

}

void CHrLCD :: pulseEnable(uint8_t DC)
{
	(*(volatile uint8_t*)(cport)) |= ((DC << rs) | (1 << en));
	_delay_us(1);
	(*(volatile uint8_t*)(cport)) &= (~CMASK(rs, en));
}
#endif // MULTIPLE_LCD