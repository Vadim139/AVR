/*
 * ADC_temp.h
 *
 *  Created on: 26-08-2014
 *      Author: Dawid
 */

#ifndef ADC_TEMP_H_
#define ADC_TEMP_H_

void ADC_init(void)
{
	ADMUX = (1 << REFS1) | (1 << REFS0);                        // Internal 2.56V reference
	ADMUX = (1 << MUX2) | (1 << MUX1);							// PA6
	ADCSRA = (1 << ADPS2) | (1 << ADPS0) ;//| (1 << ADPS0);		// Prescaler 32
	ADCSRA = (1 << ADEN);										// ADC Enable
}

void ADC_put_temp(char x, char y, char i)
{
	int buff1, buff2 = 0;
	long int buff3 = 0;

	ADCSRA &= ~(1 << ADSC);
	ADCSRA |= (1 << ADSC);

	_delay_ms(300);

	lcd_xy(x,y);

	buff1 = ADCL;
	buff2 = ADCH;
	buff3 = (((buff1) + (buff2 << 8)) *5.13);

	lcd_lnumber(buff3 - 2731);
}

#endif /* ADC_TEMP_H_ */
