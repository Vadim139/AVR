
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "my_defs.h"
#include "sbit.h"

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
volatile uint8_t i, j = 0;
void LED_liczba();

int main(void) {

	LED_DDR_1 = 1; // enable output pins
	LED_1 = 0; // turn off leds



//	TCCR0A = 0b00000010;
//	TCCR0B = 0b00000001;
//	TIMSK = 0x01;
//	OCR0A = 1;

	MCUCR = 0x0F;
	GIMSK = 0xC0;

	TCCR1B = 0b00001001; //bez preskalera
	TIMSK = 0x40;
	OCR1A = 100;

	// 5 cm - 0,164 stopy
	// 1000000/s
	// x/164000 = fps



	LED_display_init();
	PORTB = zero;
	sei();


	while (1)
	{
		LED_liczba();

	}

	return 0;
}

volatile unsigned long int yu = 0;
volatile int yy = 0;
volatile long  int czas = 0;
//char czasa[8] = {0,0,0,0,0,0,0,0};
volatile char counting = 0;

ISR(INT0_vect)
{

	if (counting == 0)
		counting = 1;
//		else
//			counting = 0;
//	}

	LED_1 = 1;
//	liczba++;

//	liczba += 2;
}

ISR(INT1_vect)
{

		if (counting == 1) {
		counting = 0;
		liczba = (16400 / czas);
		czas = 0;
//		ultoa(czas, czasa,10);
//		ultoa((200000 / czas), czasa,10);
//		if (czas != 0){
//			lcd_xy(3,1);
//			lcd_puts(czasa);
//
		}
//		czas = 0;
//	}
//
//
//	if (yu == 1) {
//		LED_5 = 0;
//		yu = 0;
//	}

	LED_1 = 0;
//	liczba++;

//	liczba += 2;

}


ISR(TIMER1_COMPA_vect)
{
	//uint32_t tmp=100000;
	//		if (counting == 1)
	//			czas++;
	////			czas = czas + 10;
	//		else {
	//			liczba = (czas/100000);
	//			czas = 0;
	////			tmp = (czas/tmp);

	//			liczba = tmp;
	//		}
	////	if (czas == 80000)
	////		czas = 0;
	//	LED_1 = 1;

	if (counting == 1) {
		if (czas < 65000) {
			//		yu++;
			czas ++;
			//				LED_1 = 1;

		} else {
			liczba = 999;
			//		liczba = liczba + 2;

			czas = 0;
			counting = 0;
		}
	}

//	if (yu >= 1000000)
//	{
//
//		liczba++;
////		liczba = liczba + 2;
//
//		czas = 0;
//
//	} else {
////		yu++;
//		czas += 8;
//		//				LED_1 = 1;
//	}


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

LD_a = 1;
LD_b = 1;
LD_c = 1;
LD_d = 1;
LD_e = 1;
LD_f = 1;
LD_g = 1;
LD_dt = 1;

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

		LD_an_1 = 1;
		LD_an_2 = 1;
		LD_an_3 = 1;
		PORTB = cyfra[0];
		LD_an_1 = 0;
		LD_an_2 = 1;
		LD_an_3 = 1;

		LD_an_1 = 1;
		LD_an_2 = 1;
		LD_an_3 = 1;
		PORTB = cyfra[1];
		LD_an_1 = 1;
		LD_an_2 = 0;
		LD_an_3 = 1;

		LD_an_1 = 1;
		LD_an_2 = 1;
		LD_an_3 = 1;
		PORTB = cyfra[2];
		LD_an_1 = 1;
		LD_an_2 = 1;
		LD_an_3 = 0;

		LD_an_1 = 1;
		LD_an_2 = 1;
		LD_an_3 = 1;
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

