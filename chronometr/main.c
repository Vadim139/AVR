
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "my_defs.h"
#include "sbit.h"
#include "uart.h"
#include "lcd_drv.h"
#include "keypad.h"


int main(void) {

//	LED_DDR_1 = 1; // enable output pins
//	LED_DDR_2 = 1;
	LED_DDR_3 = 0;
	LED_DDR_4 = 0;
	LED_DDR_5 = 1;
	LED_DDR_6 = 1;

//	LED_1 = 0; // turn off leds
//	LED_2 = 0;
	LED_3 = 1;
	LED_4 = 1;
	LED_5 = 0;
	LED_6 = 1;

	MOT_DDR_1 = 1;
	MOT_DDR_2 = 1;
	MOT_DDR_3 = 1;
	MOT_DDR_4 = 1;
	MOT_DDR_5 = 1;
	MOT_DDR_6 = 1;
	MOT_DDR_7 = 1;
	MOT_DDR_8 = 1;

	LED_1 = 0;
	LED_2 = 0;
//	LED_3 = 0;
	LED_4 = 0;
	LED_5 = 0;
	LED_6 = 0;
	LED_7 = 0;
	LED_8 = 0;

	TCCR1B = 0b00001001;
	TIMSK1 = 0x02;
	OCR1A = 16;

//	TCCR3B = 0b00001101;
//	TIMSK3 = 0x02;
//	OCR3A = 1;//15625;

	EICRA = 0x0F;
	EIMSK = 0x03;
//
//	TCCR0A = 0b00000010;
//	TCCR0B = 0b00000001;
//	TIMSK0 = 0x02;
//	OCR0A = 64;

	lcd_init();
	lcd_puts("1234");
	LED_4 = 1;

	sei();
	LED_6 = 0;
	lcd_blank();

	while (1)
	{

	}

	return 0;
}

int yu = 0;

volatile long long int czas = 0;
char czasa[8] = {0,0,0,0,0,0,0,0};
volatile char counting = 0;

ISR(INT0_vect)
{

	if (counting == 0) {
//		czas = 0;
		counting = 1;
	}
//		else
//		{
//			counting = 0;
//			lcd_blank();
//			lcd_xy(3,0);
//			ultoa(czas, czasa,10);
//			if (czas != 0)
//				lcd_puts(czasa);
////			if(czas!=0)
////				lcd_lnumber((200000 / czas));
//			czas = 0;
//		}

	if (yu == 0) {
		LED_5 = 1;
		yu = 1;
	}
	//	else
	//	{
	//		LED_5 = 0;
	//		yu = 0;
	//	}

}

ISR(INT1_vect)
{

		if (counting == 1) {
		counting = 0;
		lcd_blank();
		lcd_xy(3,0);
		ultoa(czas, czasa,10);
		lcd_puts(czasa);
		ultoa((200000 / czas), czasa,10);
		if (czas != 0){
			lcd_xy(3,1);
			lcd_puts(czasa);
//			lcd_lnumber(czas);
//			lcd_lnumber((200000 / czas));
		}
		czas = 0;
	}

	//	else
	//	{
	//		counting = 0;
	//		lcd_blank();
	//		lcd_xy(3,0);
	//		if(czas!=0)
	//			lcd_lnumber((200000 / czas));
	//		czas = 0;
	//	}

	if (yu == 1) {
		LED_5 = 0;
		yu = 0;
	}
	//	else
	//	{
	//		LED_5 = 0;
	//		yu = 0;
	//	}
}

//ISR(TIMER0_COMPA_vect)
//{
//	if (counting == 1)
////		{
////			czas++;
//		czas = czas + 4;
////		}
////	if (czas == 200000)
////		czas = 0;
////		counting = 0;
//}

ISR(TIMER1_COMPA_vect) {

	if (counting == 1)
	//		{
		czas = czas + 10;
//	czas = czas + 5;
//	if (czas == 80000)
//		czas = 0;
//			czas = czas + 4;
	//		}

}

