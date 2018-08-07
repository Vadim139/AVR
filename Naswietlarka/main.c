/*===========================================================================================================================
 * main.c
 *
 *  Created on: 09-02-2012
 *      Author: Krzysztof Szromek
 *      Poligon doswiadczalny w obs³udze uart i RTC (poprzez TWI).
 *      Kod do obs³ugi poszczególnych elementów podzielony na osobne biblioteki.
 *		- uart_lib
 *		- lcd_drv
 *		- keypad
 *
 *      Konfiguracja sprzêtowa:
 *      PD.0 	- RxD
 *      PD.1 	- TxD
 *      PC.0-3 	- ROW_1-4  	- 4 linie wierszy klawiatury matrycowej
 *      PD.2 	- KEYINT 	- przerwanie z klawiatury
 *      PB.0-3 	- LED 		- 4x Ledy
 *
 *===========================================================================================================================*/

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "my_defs.h"
#include "sbit.h"
#include "lcd_drv.h"
#include "main.h"

char bufor;
//volatile char flag = 0;
volatile int Time, min, sek = 0;
volatile int flag = 0;



int main(void) {

	int buff1, buff2, buff3 = 0;

	KEYINT_DDR = 0;
	ADC_DDR_1 = 0;
	UV_DDR = 1;
	LED_DDR_7 = 1;
	LED_DDR_8 = 1;

	ADC_1 = 0;
	KEYINT = 1;
	UV = 0;
	LED_7 = 0;
	LED_8 = 0;
	ADMUX = (1 << REFS1) | (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS0);// | (1 << ADPS1) ;

	TCCR0 = 0b101;
	TCNT0 = 244;
	TIMSK = 0x01;

//	TCCR1B = 0b00001100;
//	TIMSK = 0x11;
//	OCR1A = 31;

//	TCCR3B = 0b00001101;
//	TIMSK3 = 0x02;
//	OCR3A = 1;//15625;

//	EICRA = 0x0A;
	MCUCR = 0x02;
//	EIMSK = 0x03;
	GICR = 0x40;
//

//	TCCR0B = 0b00000001;
//	TIMSK0 = 0x02;
//	OCR0A = 64;

	lcd_init();
	lcd_puts("1234");

	sei();
	lcd_blank();

	lcd_xy(0,0);
	lcd_puts("Min:");

	ADCSRA &= ~(1 << ADSC);
	ADCSRA |= (1 << ADSC);
	_delay_ms(300);
	buff1 = ADCL;
	buff2 = ADCH;
	Time = (((buff1) + (buff2 << 8)));
	flag = 1;

	while (1) {
		lcd_xy(0,0);
		lcd_puts("Min:");
		while (flag == 1) {
			ADCSRA &= ~(1 << ADSC);
			ADCSRA |= (1 << ADSC);
			_delay_ms(500);
			buff1 = ADCL;
			buff2 = ADCH;
			buff3 = (((buff1) + (buff2 << 8)));
//			lcd_blank();
			//		lcd_xy(0,1);
			//		lcd_lnumber(Time);
			Time = buff3 * 0.0576;
//			lcd_xy(0,0);
//			lcd_puts("Min:");
			lcd_xy(5,0);
			lcd_puts("     ");
			lcd_xy(5,0);
			lcd_number(Time);
		}
		lcd_xy(0,1);
		lcd_puts("Sek:");
		while (flag == 2) {
			ADCSRA &= ~(1 << ADSC);
			ADCSRA |= (1 << ADSC);
			_delay_ms(500);
			buff1 = ADCL;
			buff2 = ADCH;
			buff3 = (((buff1) + (buff2 << 8)));
//			lcd_blank();
			//		lcd_xy(0,1);
			//		lcd_lnumber(Time);
			Time = buff3 * 0.0576;
//			lcd_xy(0,0);
//			lcd_puts("Min:");
			lcd_xy(5,0);
			lcd_puts("     ");
			lcd_xy(5,0);
			lcd_number(min);
//			lcd_xy(0,1);
//			lcd_puts("Sek:");
			lcd_xy(5,1);
			lcd_puts("     ");
			lcd_xy(5,1);
			lcd_number(Time);
		}
		while (flag == 3) {
			_delay_ms(200);
//			lcd_blank();
//			lcd_xy(0,0);
//			lcd_puts("Min:");
			lcd_xy(5,0);
			lcd_puts("     ");
			lcd_xy(5,0);
			lcd_number(min);
//			lcd_xy(0,1);
//			lcd_puts("Sek:");
			lcd_xy(5,1);
			lcd_puts("     ");
			lcd_xy(5,1);
			lcd_number(sek);
		}
		//
	}

	return 0;
}



volatile short int counter = 0;

uint8_t stan[4] = {0b00, 0b01, 0b10, 0b11};///////
uint8_t stan_poprz, lp, vect = 0;///////



ISR(INT0_vect)
{
	switch (flag) {
		case 1:
		if (Time < 150)
		{
			min = Time;
			Time = 200;
			flag = 2;
		}

		break;
		case 2:
		if (Time < 150)
		{
			sek = Time;
			Time = 200;
			UV = 1;
			LED_8 = 1;
			flag = 3;
		}
		break;
		case 3:
		if (Time < 150)
		{
			Time = 200;
			UV = 0;
			LED_8 = 0;
			flag = 1;
		}
			break;
		default:
			break;
	}
//	PORTD ^= (1 << 7);
//	if (flag == 1)
//	{
//		min = Time;
////		flag++;
//	}else if (flag == 2)
//	{
//		sek = Time;
//		UV = 1;
//		LED_8 = 1;
////		flag++;
//	}
//	else if (flag == 3)
//	{
//		sek = Time;
//		flag++;
//	}
//	flag++;
//	if (flag == 3)
//		{
//			sek = 0;
//			min = 0;
//			LED_8 = 0;
//			UV = 0;
//			flag = 1;
//		}
	_delay_ms(200);
}

int flag0 = 0;

ISR(TIMER0_OVF_vect)
{
	flag0++;

	if (flag0 == 64) {
		if (flag == 3) {
			if (sek > 0)
				sek--;
			else if (min > 0) {
				min--;
				sek = 59;
			} else {
				flag = 1;
				UV = 0;
				LED_8 = 0;
			}
		}
		flag0 = 0;
	}

}

//ISR(TIMER1_COMPA_vect)
//{
//
//}

