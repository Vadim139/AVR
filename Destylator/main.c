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
#include <stdint.h>

#include "main.h"
#include "my_defs.h"
#include "sbit.h"
#include "i2c.h"
#include "LCD_SSD1803a.h"
#include "NTC.h"
#include "soft_i2c.h"
//#include "ds18b20.h"
//#include "uart.h"

volatile uint8_t channel = 0;
volatile uint8_t temp_zad = 70;

int main(void) {
//	LED_DDR_1 = 1; // enable output pins
//	LED_DDR_2 = 1;
//	LED_DDR_7 = 1;
//	LED_DDR_4 = 1;
//	LED_DDR_5 = 1;
//	LED_DDR_6 = 1;
//	LED_DDR_8 = 1;

//
//	LED_1 = 0; // turn off leds
//	LED_2 = 0;
//	LED_7 = 0;
//	LED_4 = 0;
//	LED_5 = 0;
//	LED_6 = 0;
//	LED_8 = 0;

	int buff1, buff2, buff3 = 0;
	int16_t Temp;
	uint8_t beep_c = 0;

	ADC0_DDR = 0;
	ADC1_DDR = 0;
	ADC2_DDR = 0;
	ADC3_DDR = 0;
	ADC4_DDR = 0;
	ADC5_DDR = 0;
	L_RES_DDR = 1;
	L_LED_DDR = 1;
	BEEP_DDR = 1;
	KEYINT1_DDR = 0;
	KEYINT2_DDR = 0;
	G1_DDR = 1;
	G2_DDR = 1;

	ADC0 = 0;
	ADC1 = 0;
	ADC2 = 0;
	ADC3 = 0;
	ADC4 = 0;
	ADC5 = 0;
	L_RES = 1;
	L_LED  = 1;
	KEYINT1 = 1;
	KEYINT2 = 1;
	G1 = 0;
	G2 = 0;
	BEEP = 1;

	ADMUX = (1 << REFS0) | (1 << REFS1);  // avcc ref
	ADCSRA = (1 << ADEN) | (1 << ADPS0) |(1 << ADPS1) | (1 << ADPS2); //adc prescaler

	MCUCR = 0x0A;
	GICR = 0xC0;  //int0, int1 , falling

	TCCR0 = 0b101;
	TCNT0 = 244;  //1/64 sekundy
	TIMSK = 0x01;

	SoftI2CInit();
//	i2cInit();
//	LCDSSD_init();
//	SoftI2CInit();

	sei();

	LCD_Init();

	LCD_xy(10,3);
	LCD_str("Zad");
	LCD_str(":");
	LCD_int_SM_N(temp_zad,2,0,0);
	LCD_xy(0,0);

	while (1) {
//		ADCSRA &= ~(1 << ADEN);
//		ADMUX = (0 << MUX0) | (0 << MUX1);// | (0 << MUX2) | (0 << MUX3);//
//		ADCSRA |= (1 << ADEN);

		ADMUX = 192 + channel; //(1 << REFS0) | (1 << REFS1)
		ADCSRA |= (1 << ADSC);
		_delay_ms(100);
		ADCSRA |= (1 << ADSC);
		_delay_ms(100);
		buff1 = ADCL;
		buff2 = ADCH;
		buff3 = (((buff1) + (buff2 << 8)));

		if (buff3 > 1000)
		{
			ADMUX = (1 << REFS0) +channel;
			ADCSRA |= (1 << ADSC);
			_delay_ms(100);
			buff1 = ADCL;
			buff2 = ADCH;
			buff3 = (((buff1) + (buff2 << 8)));
			Temp = calcNTC(buff3, channel, 0);
		}else
		{
			Temp = calcNTC(buff3, channel, 1);
//			ADMUX = (1 << REFS0) | (1 << REFS1) +channel;
		}

		switch(channel){
		case 0:
			LCD_xy(0,0);
			break;
		case 1:
			LCD_xy(0,1);
			break;
		case 2:
			LCD_xy(0,2);
			break;
		case 3:

			if ((int)Temp/100>=temp_zad)
			{
				if(beep_c++<20)
				{
				BEEP = 0;
				_delay_ms(200);
				BEEP = 1;
				LCD_xy(19,3);
				LCD_str("*");
				}
			}
				LCD_xy(0,3);
			break;
		case 4:
			LCD_xy(10,0);
			break;
		case 5:
			LCD_xy(10,1);

			break;
		default:
			break;
		}
		LCD_str("T");
//		LCD_int_SM_N(channel, 1,0,0);
		LCD_int(channel + 1);
		LCD_str(":");
		LCD_int_SM_N(Temp,5,2,0);
//		LCD_str("");

		if(++channel>=6)channel = 0;
	}

	return 0;
}

int flag0 = 0;

ISR(TIMER0_OVF_vect)
{
	flag0++;

	if (flag0 == 64) {


		flag0 = 0;
	}

}

ISR(INT0_vect)
{
	LCD_xy(14,3);
	temp_zad++;
	LCD_int_SM_N(temp_zad,2,0,0);

	switch(channel){
	case 0:
		LCD_xy(0,0);
		break;
	case 1:
		LCD_xy(0,1);
		break;
	case 2:
		LCD_xy(0,2);
		break;
	case 3:
		LCD_xy(0,3);
		break;
	case 4:
		LCD_xy(10,0);
		break;
	case 5:
		LCD_xy(10,1);
		break;
	default:
		break;
	}
	_delay_ms(200);
}

ISR(INT1_vect)
{
	LCD_xy(14,3);
	temp_zad--;
	LCD_int_SM_N(temp_zad,2,0,0);

	switch(channel){
	case 0:
		LCD_xy(0,0);
		break;
	case 1:
		LCD_xy(0,1);
		break;
	case 2:
		LCD_xy(0,2);
		break;
	case 3:
		LCD_xy(0,3);
		break;
	case 4:
		LCD_xy(10,0);
		break;
	case 5:
		LCD_xy(10,1);
		break;
	default:
		break;
	}
	_delay_ms(200);
}
