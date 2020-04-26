/*
 * ADC.h
 *
 * Created: 22-Apr-20 10:37:51 PM
 *  Author: Mohamed Merdan
 */ 


#ifndef ADC_H_
#define ADC_H_

#define AD0 0
#define AD1 1
#define AD2 2
#define AD3 3
#define AD4 4
#define AD5 5
#define AD6 6
#define AD7 7

void analogSet(uint8_t analogPin)
{
	analogPin = (analogPin > 7) ? 7 : ((analogPin < 0) ? 0 : analogPin);
	DDRA &= ~(1 << analogPin);
	ADMUX = (1 << REFS0) | (analogPin << MUX0);
	ADCSRA = (7 << ADPS0) | (1 << ADEN);
}

uint16_t analogRead(uint8_t analogPin)
{
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	uint16_t reading = ADCL | (ADCH << 8);
	return reading;
}


#endif /* ADC_H_ */