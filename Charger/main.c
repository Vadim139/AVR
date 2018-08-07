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

volatile int V1 = 0, V2 = 0;
volatile int flag = 0;

ISR( __vector_default) {

}

int main(void) {

	int buff1, buff2, buff3 = 0;

	ADC_DDR_1 = 0;

	ADC_1 = 0;

	LED_DDR_1 = 1;
	LED_DDR_2 = 1;
	SW_DDR_1 = 1;
	SW_DDR_2 = 1;

	LED_2 = 0;
	LED_1 = 1;
	SW_1 = 0;
	SW_2 = 0;

	_delay_ms(3000);

	SW_2 = 1;

	// ADC PB4
	ADMUX = 0x02;
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS0); //	ADCSRA = 0x80;

	sei();


	while (1) {

		_delay_ms(300);

		ADMUX = 0x02;
		ADCSRA &= ~(1 << ADSC);
		ADCSRA |= (1 << ADSC);
		_delay_ms(300);
		buff1 = ADCL;
		buff2 = ADCH;
		V1 = (((buff1) + (buff2 << 8)));

//				ADMUX = 0x03;
//				ADCSRA &= ~(1 << ADSC);
//				ADCSRA |= (1 << ADSC);
//				_delay_ms(300);
//				buff1 = ADCL;
//				buff2 = ADCH;
//				V2 = (((buff1) + (buff2 << 8)));

		if (V1 < 100) {
			LED_1 = 1;
			LED_2 = 0;
			SW_1 = 0;
			flag = 0;
		} else if (V1 > 100) {
			if (flag == 5) {
				LED_1 = 0;
				LED_2 = 1;
				SW_1 = 1;
				flag = 6;
			} else if (flag == 1 || flag == 3) {
				LED_1 = 1;
				LED_2 = 1;
				flag++;
				_delay_ms(3000);
			} else if (flag == 0 || flag == 2 || flag == 4) {
				LED_1 = 0;
				LED_2 = 1;
				flag++;
				_delay_ms(3000);
			}
		} else {
			LED_1 = 0;
			LED_2 = 0;
			SW_1 = 0;
		}

	}
	return 0;

}
