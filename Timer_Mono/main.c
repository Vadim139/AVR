/*===========================================================================================================================
 * main.c
 *
 *  Created on: 28-11-2014
 *      Author: Dawid Szromek
 *      Timer monostabilny regulowany przez pot na ADC.

 *
 *      Konfiguracja sprzêtowa:
 *      PB.0 	- SW
 *      PB.4 	- ADC
 *      PB.3 	- OUT
 *
 *===========================================================================================================================*/

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "my_defs.h"
#include "sbit.h"
#include "main.h"

volatile int Time = 0;
volatile int flag = 0;

ISR(__vector_default){

}

int main(void) {

 int buff1, buff2, buff3 = 0;

	SW_DDR_1 = 0;
	ADC_DDR_1 = 0;
	ADC_DDR_2 = 0;

	SW_1 = 1;
	ADC_1 = 0;
	ADC_2 = 0;

	OUT_DDR_1 = 1;
	OUT_DDR_2 = 1;

	OUT_2 = 0;

    //Timer 0 -  122 Hz
	TCCR0A = 0x02;
	TCCR0B = 0x05;
//	TIMSK = 0x30;
	OCR0A = 8;

	TCCR1 = 0x54;
//	GTCCR = 0x60;
	TIMSK = 0x50;
	OCR1A = 0;
	OCR1C = 255;

	// ADC PB2
	ADMUX = 0x02;
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS0) ;//	ADCSRA = 0x80;


	sei();

	while (1) {


		if(!SWpin_1)
		{
			if(flag == 1)
			{
				Time = 0;
				flag = 0;
				OUT_2 = 0;
				OCR1A = 0;
				_delay_ms(300);
//				break;
			}else
			{
				ADMUX = 0x02;
				ADCSRA &= ~(1 << ADSC);
				ADCSRA |= (1 << ADSC);
				_delay_ms(300);
				buff1 = ADCL;
				buff2 = ADCH;
				Time = (((buff1) + (buff2 << 8)));

				ADMUX = 0x01;
				ADCSRA &= ~(1 << ADSC);
				ADCSRA |= (1 << ADSC);
				_delay_ms(300);
				buff1 = ADCL;
				buff2 = ADCH;
				OCR1A = (((buff1) + (buff2 << 8)) >> 2);

				flag = 1;
				OUT_2 = 1;
			}

		}

	}
	return 0;

}


ISR(TIMER0_COMPA_vect)
{
	if(flag == 1)
	{
		Time--;

	if(Time <= 0)
	{
		flag = 0;
		OCR1A = 0;
		OUT_2 = 0;
	}
	}
}

