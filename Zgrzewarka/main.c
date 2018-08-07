
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "my_defs.h"
#include "sbit.h"

//#define one 0b00000110
//#define two 0b01011011
//#define three 0b01001111
//#define four 0b01100110
//#define five 0b01101101
//#define six 0b01111101
//#define seven 0b00000111
//#define eight 0b01111111
//#define nine 0b01101111
//#define zero 0b00111111

#define one 0b11111001
#define two 0b10100100
#define three 0b10110000
#define four 0b10011001
#define five 0b10010010
#define six 0b10000010
#define seven 0b11111000
#define eight 0b10000000
#define nine 0b10010000
#define zero 0b11000000

int cyfra[3] = {0,0,0};

void LED_display_init(void);

volatile long int liczba = 0;
volatile int liczba_pop = 0;
volatile int cyf[3] = {0,0,0};
volatile uint8_t i = 0, j = 0;
void LED_liczba();

int main(void) {

//	LED_DDR_1 = 1; // enable output pins
//	LED_1 = 0; // turn off leds

	ADC_DDR_1 = 0;
	ADC_1 = 1;

	CON_DDR_1 = 1;
	CON_1 = 1;

	CON_DDR_2 = 1;
	CON_2 = 0;


	SW_DDR_1 = 0;
	SW_1 = 1;

	BUZ_DDR_1 = 1;
	BUZ_1 = 0;

	ADMUX = (1 << REFS1) | (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS0);// | (1 << ADPS1) ;

//	TCCR0 = 0b101;
//	TCNT0 = 244;
//	TIMSK = 0x01;

	TCCR1B = 0b00001101;
	OCR1AH = 2;
	OCR1AL = 254;
	TIMSK = 0b10000;

	MCUCR = 0x08;
	GICR = 0x80;

	LED_display_init();
	PORTB = zero;
	sei();

//
//	ADCSRA &= ~(1 << ADSC);
//	ADCSRA |= (1 << ADSC);
//	_delay_ms(500);
//	buff1 = ADCL;
//	buff2 = ADCH;
//	buff3 = (((buff1) + (buff2 << 8)));
////			lcd_blank();
//	//		lcd_xy(0,1);
//	//		lcd_lnumber(Time);
//	Time = buff3 * 0.0576;
//
//

	int Time = 0;
	while (1)
	{

//		while(liczba == liczba_pop)
//		{
//
//			ADCSRA &= ~(1 << ADSC);
//					ADCSRA |= (1 << ADSC);
//					_delay_ms(500);
//					buff1 = ADCL;
//					buff2 = ADCH;
//					buff3 = (((buff1) + (buff2 << 8)));
//				////			lcd_blank();
//				//	//		lcd_xy(0,1);
//				//	//		lcd_lnumber(Time);
//					liczba = buff3 /1.03;
//
//			LD_an_1 = 0;
//			LD_an_2 = 0;
//			LD_an_3 = 0;
//			PORTB = (cyfra[0]  | (1 << 7));
//			LD_an_1 = 1;
//			LD_an_2 = 0;
//			LD_an_3 = 0;
//			_delay_ms(5);
//
//			LD_an_1 = 0;
//			LD_an_2 = 0;
//			LD_an_3 = 0;
//			PORTB = cyfra[1];
//			LD_an_1 = 0;
//			LD_an_2 = 1;
//			LD_an_3 = 0;
//			_delay_ms(5);
//
//			LD_an_1 = 0;
//			LD_an_2 = 0;
//			LD_an_3 = 0;
//			PORTB = cyfra[2];
//			LD_an_1 = 0;
//			LD_an_2 = 0;
//			LD_an_3 = 1;
//			_delay_ms(5);
//
//			LD_an_1 = 0;
//			LD_an_2 = 0;
//			LD_an_3 = 0;
//		}
//
//
//			if(liczba < 10)
//			{
//	//			cyfra[0] = zero;
//	//			cyfra[1] = zero;
//	//			i = 2;
//				cyf[0] = 0;
//				cyf[1] = 0;
//				cyf[2] = liczba;
//				j = 1;
//			}else if(liczba < 100)
//			{
//	//			cyfra[0] = zero;
//	//			i = 1;
//				cyf[0] = 0;
//				cyf[1] = (liczba - (liczba%10))/10;
//				cyf[2] = liczba%10;
//				j = 10;
//			}else if(liczba < 1000)
//			{
//				cyf[0] = (liczba - (liczba%100))/100;
//				cyf[1] = (liczba/10)%10;//((liczba - (100 * cyf[0])) - (liczba%10))/10;
//				cyf[2] = liczba%10;
//	//			i = 0;
//				j = 100;
//			}
//
//			while(i<3)
//			{
//				switch (cyf[i]) {
//					case 0:
//						cyfra[i] = zero;
//						break;
//
//					case 1:
//						cyfra[i] = one;
//						break;
//
//					case 2:
//						cyfra[i] = two;
//						break;
//
//					case 3:
//						cyfra[i] = three;
//						break;
//
//					case 4:
//						cyfra[i] = four;
//						break;
//
//					case 5:
//						cyfra[i] = five;
//						break;
//
//					case 6:
//						cyfra[i] = six;
//						break;
//
//					case 7:
//						cyfra[i] = seven;
//						break;
//
//					case 8:
//						cyfra[i] = eight;
//						break;
//
//					case 9:
//						cyfra[i] = nine;
//						break;
//					default:
//						break;
//				}
//				i++;
//			}
//			liczba_pop = liczba;
//			i = 0;
		LED_liczba();

	}

	return 0;
}

volatile unsigned long int yu = 0;
volatile int yy = 0;
volatile long  int czas = 0;
//char czasa[8] = {0,0,0,0,0,0,0,0};
volatile char counting = 0;

//ISR(INT0_vect)
//{
//
//	if (counting == 0)
//		counting = 1;
////		else
////			counting = 0;
////	}
//
////	LED_1 = 1;
////	liczba++;
//
////	liczba += 2;
//}
int o = 0;
int flag = 0;
ISR(INT1_vect)
{
if(!flag){
	BUZ_1 = 1;
	CON_1 = 0;
	if(liczba>100){
		for(o = 0; o < liczba/100;o++)
			_delay_ms(1000);
		_delay_ms((liczba%100)*10);
	}
	else _delay_ms(liczba*10);
	BUZ_1 = 0;
	CON_1 = 1;
	_delay_ms(2);
	CON_2 = 1;
	_delay_ms(5);
	CON_2 = 0;
	_delay_ms(1000);
	flag = 1;
}
else flag = 0;


}
int buff1 = 0,buff2 = 0,buff3 = 0;

ISR(TIMER1_COMPA_vect)
{
	LD_an_1 = 0;
	LD_an_2 = 0;
	LD_an_3 = 0;
	ADCSRA &= ~(1 << ADSC);
			ADCSRA |= (1 << ADSC);
//			_delay_ms(2);
			buff1 = ADCL;
			buff2 = ADCH;
			buff3 = (((buff1) + (buff2 << 8)));
			liczba = (buff3 /1.025) - 30;
			if(liczba<0)
				liczba = 0;



}

void LED_display_init(void)
{

LD_DDR_a = 1;
LD_DDR_b = 1;
LD_DDR_c = 1;
LD_DDR_d = 1;
LD_DDR_e = 1;
LD_DDR_f = 1;
LD_DDR_g = 1;
LD_DDR_dt = 1;

LD_a = 0;
LD_b = 0;
LD_c = 0;
LD_d = 0;
LD_e = 0;
LD_f = 0;
LD_g = 0;
LD_dt = 0;

LD_DDRan_1 = 1;
LD_DDRan_2 = 1;
LD_DDRan_3 = 1;

LD_an_1 = 1;
LD_an_2 = 1;
LD_an_3 = 1;


}

//int liczba, liczba_pop = 0;
//int cyf[3] = {0,0,0};
//uint8_t i, j = 0;
void LED_liczba()
{
	while(1)
	{
	while(liczba == liczba_pop)
	{

		LD_an_1 = 0;
		LD_an_2 = 0;
		LD_an_3 = 0;
		PORTB = (cyfra[0]  & ~(1 << 7));
		LD_an_1 = 1;
		LD_an_2 = 0;
		LD_an_3 = 0;

		LD_an_1 = 0;
		LD_an_2 = 0;
		LD_an_3 = 0;
		PORTB = cyfra[1];
		LD_an_1 = 0;
		LD_an_2 = 1;
		LD_an_3 = 0;

		LD_an_1 = 0;
		LD_an_2 = 0;
		LD_an_3 = 0;
		PORTB = cyfra[2];
		LD_an_1 = 0;
		LD_an_2 = 0;
		LD_an_3 = 1;

		LD_an_1 = 0;
		LD_an_2 = 0;
		LD_an_3 = 0;
	}

	if(liczba != liczba_pop)
	{
		if(liczba < 10)
		{
//			cyfra[0] = zero;
//			cyfra[1] = zero;
//			i = 2;
			cyf[0] = 0;
			cyf[1] = 0;
			cyf[2] = liczba;
			j = 1;
		}else if(liczba < 100)
		{
//			cyfra[0] = zero;
//			i = 1;
			cyf[0] = 0;
			cyf[1] = (liczba - (liczba%10))/10;
			cyf[2] = liczba%10;
			j = 10;
		}else if(liczba < 1000)
		{
			cyf[0] = (liczba - (liczba%100))/100;
			cyf[1] = (liczba/10)%10;//((liczba - (100 * cyf[0])) - (liczba%10))/10;
			cyf[2] = liczba%10;
//			i = 0;
			j = 100;
		}

		while(i<3)
		{
			switch (cyf[i]) {
				case 0:
					cyfra[i] = zero;
					break;

				case 1:
					cyfra[i] = one;
					break;

				case 2:
					cyfra[i] = two;
					break;

				case 3:
					cyfra[i] = three;
					break;

				case 4:
					cyfra[i] = four;
					break;

				case 5:
					cyfra[i] = five;
					break;

				case 6:
					cyfra[i] = six;
					break;

				case 7:
					cyfra[i] = seven;
					break;

				case 8:
					cyfra[i] = eight;
					break;

				case 9:
					cyfra[i] = nine;
					break;
				default:
					break;
			}
			i++;
		}
		liczba_pop = liczba;
		i = 0;
	}
	}
}

