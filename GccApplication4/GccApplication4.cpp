#include <avr/io.h>
#include <avr/interrupt.h>

ISR(ADC_vect)
{
	unsigned int ADCdata;
	ADCdata= ADCW;
	if (ADCdata > (2046 / 5))
	PORTD = 3;
	else if (ADCdata < (1023 / 5))
	PORTD = 6;
	else
	PORTD = 5;		
	ADCSRA |= 1<<ADSC;
}

int main(void)
{
	DDRD = 7;
	ADCSRA |= 1<<ADPS2 | 1<<ADPS1 | 0<<ADPS0;
	ADCSRA |= 1<<ADIE;
	ADCSRA |= 1<<ADEN;
	
	ADMUX |= 1<<REFS0 | 1<<REFS1;
	ADMUX |= 0<<MUX4 | 0<<MUX3 | 0<<MUX2 | 0<<MUX1 | 0<<MUX0;

	sei();
	
	ADCSRA |= 1<<ADSC;
	
	while(1);
}