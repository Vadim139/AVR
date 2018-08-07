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
#include "uart.h"
#include "lcd_drv.h"
#include "main.h"
//#include "keypad.h"
//#include "ascii_code.h"


//char helper = 0;///////
char bufor;
//int bufori;//////////
int t_gpu;
char t_gpuc[3];
int t_cpu;
char t_cpuc[3];
volatile int t_cal = 0;
volatile int kr = 0;
char clock[6];
char date[11];
volatile bool auto_flag = false;
volatile bool menu_flag = false, zm_flag = false;
volatile bool click = false, obr = false;
volatile bool menu_out = false;
volatile uint8_t vect = 0;
//int uart_timeout = 0;
//volatile bool uart_timeout_b = false;
//int Led = 0;
//char buf[3];//////////

char Mot1c[4];
//char Mot2c[4];////////

int Mot[9] = {0,0,0,0,0,0,0,0,0};
volatile short int num_el = 0;

// Wiatraki
//
// 1 - Przód swiec¹cy
// 2 - Przód nieswiec¹cy
// 3 - Bok swiec¹cy
// 4 - Bok swiec¹cy
// 5 - Góra swiec¹cy
// 6 - Góra nieswiec¹cy
// 7 - Ty³ nieswiec¹cy
// 8 - Dodatkowy (Dysk twardy)

// 90 100 110 120 130 140 145 150 160

// Krzywa 1 (praca zwyk³a)
//short Mot1_8[8] = {0,0,0,2,4,7,10,15};///////////////
//short Mot1_7[8] = {0,0,0,2,4,7,10,15};
//short Mot3_5[8] = {0,0,0,0,4,8,12,15};
//short Mot2_6[5] = {,,,,,,,,,};
//short Mot4_8[5] = {,,,,,,,,,};

// Krzywa 2 (stres)
int Mot1_8s[9] = {4,6,9,12,15,16,18,20,20};
//short Mot1_7[8] = {4,6,9,12,15,14,16,18,20};
//short Mot3_5[8] = {0,4,7,11,13,14,16,18,20};
//short Mot2_6[8] = {0,0,6,10,13,14,16,18,20};
//short Mot4_8[8] = {0,0,4,8,12,14,16,18,20};

short Mot_minz[8] = {6,6,4,3,4,3,3,0};//////////
//short Mot_mins[9] = {0,1,3,2,4,3,4,1,3};//////////

char M[17][20] = {("Bok swiecacy 1  "),  // 0
				  ("Bok swiecacy 2  "),  // 1
				  ("Przod siecacy   "),  // 2
				  ("Przod nswiecacy "),  // 3
				  ("Gora swiecacy   "),  // 4
				  ("Gora nieswiecacy"),  // 5
				  ("Tyl             "),  // 6
				  ("Chlodnica       "),  // 7
				  ("Wszystkie       "),  // 8
				  ("Profile         "),  // 9
				  ("Pompa           "),  // 10
				  ("Wyjsc?          "),  // 11
				  ("Stan:           "),  // 12
				  ("Ekstremalnie    "),  // 13
				  ("Na spokojnie    "),  // 14
				  ("Calm down baby  "),  // 15
				  ("Cofnij          ")}; // 16
//char M1_1[] = ("Bok swiecacy 1");
//char M1_2[] = ("Stan: ");
//
//char M2_1[] = ("Bok swiecacy 2");
//char M2_2[] = ("Stan: ");
//
//char M3_1[] = ("Przod siecacy");
//char M3_2[] = ("Stan: ");
//
//char M4_1[] = ("Przod nswiecacy");
//char M4_2[] = ("Stan: ");
//
//char M5_1[] = ("Gora swiecacy");
//char M5_2[] = ("Stan: ");
//
//char M6_1[] = ("Gora nieswiecacy");
//char M6_2[] = ("Stan: ");
//
//char M7_1[] = ("Tyl");
//char M7_2[] = ("Stan: ");
//
//char M8_1[] = ("Chlodnica");
//char M8_2[] = ("Stan: ");
//
//char M9_1[] = ("Wszystkie");
//char M9_2[] = ("Stan: ");
//
//char M10_1[] = ("Pompa");
//char M10_2[] = ("Stan: ");


int menu()
{
	int j = 0,k = 0;
	int profile_flag = 0;
	int temp = 0;
	while(menu_flag)
	{
		lcd_blank();
		lcd_xy(0,0);
		lcd_puts(M[j]);
		lcd_xy(0,1);
		if(j!=11 && j!=9) lcd_puts(M[12]);
		lcd_xy(7,1);
		if(j != 10){
			if(j==11);
			else if(j == 9){
				lcd_xy(0,1);
				if(profile_flag)
					lcd_puts(">");
				lcd_puts(M[13+k]);


			}else if(j != 8){
				if(!zm_flag) lcd_number(Mot[j+1]*5);
				else {
					lcd_xy(6,1);
					lcd_puts(">");
					lcd_number(temp*5);

				}
				lcd_xy(10,1);
				lcd_puts("%");
			}else{
				if ((Mot[1] == Mot[2] && Mot[1] == Mot[3] && Mot[1] == Mot[4] && Mot[1] == Mot[5] && Mot[1] == Mot[6] && Mot[1] == Mot[7] && Mot[1] == Mot[8]) || zm_flag)
				{
					if(!zm_flag) lcd_number(Mot[1]*5);
					else if(temp != 21) {
						lcd_xy(6,1);
						lcd_puts(">");
						lcd_number(temp*5);
					}
					else  {
						lcd_xy(6,1);
						lcd_puts(">");
						lcd_puts("Auto");
					}
					lcd_xy(10,1);
					if(temp != 21) lcd_puts("%");
				}else
				{
					lcd_puts("----");
				}
			}
		}else
		{
			if(!zm_flag){
				if(POMPpin)
					lcd_puts("Zal");
				else
					lcd_puts("Wyl");
			}else
			{
				lcd_xy(6,1);
				lcd_puts(">");
				if(temp)
					lcd_puts("Zal");
				else
					lcd_puts("Wyl");
			}

		}
		_delay_ms(300);

		while(!click && !obr){
//			if(menu_out && !ENpin_3){
//				menu_flag = false;
//				menu_out = false;
//				return 0;
//			}
//			if(!menu_out)
//				if(!ENpin_3)
//					menu_out = true;
		}

		if (obr) {
			if (!zm_flag && !profile_flag) {
				if (vect == 1) {
					if (j < 11)
						j++;
					else
						j = 0;
					//			vect = 0;
					obr = false;
				} else if (vect == 2) {
					if (j > 0)
						j--;
					else
						j = 11;
					//			vect = 0;
					obr = false;
				}
			}else
			{
				if(j<9){
//					temp = Mot[j];
					if(vect == 1)
					{
						if(temp<20)
							temp++;
						else if(j == 8 && temp<21)
							temp++;

					}
					if(vect == 2)
					{
						if(temp>0)
							temp--;

					}
				}else if(j == 10)
				{
					if(vect == 1)
					{
						if(temp);
						else temp = 1;

					}
					if(vect == 2)
					{
						if(temp) temp = 0;
						else;

					}

				}else if(j == 9)
				{
					if(vect == 1)
					{
						if(profile_flag && k<3)
							k++;
						else if(profile_flag)
							k = 0;

					}
					if(vect == 2)
					{
						if(profile_flag && k>0)
							k--;
						else if(profile_flag)
							k = 3;

					}

				}
				obr = false;
			}
		}

//		if(menu_out && !ENpin_3){
//			menu_flag = false;
//			menu_out = false;
//			return 0;
//		}
//		if(!menu_out && click)
//			if(!ENpin_3)
//				menu_out = true;

		if(click)
		{
			if(zm_flag)
			{
				if(j<8)
					Mot[j+1] = temp;
				else if(j == 8)
					if(temp !=21)
						for (short int j = 1; j < 9; j++)
							Mot[j] = temp;
					else {
						num_el = 9;
						auto_flag = true;
					}
				else if(j == 10)
					POMP = temp;

				zm_flag = false;

			}else if(j == 11)
			{
				menu_flag = false;
				menu_out = false;
				return 0;
			}
			else if(j<9)
			{
				zm_flag = true;
				if(j!=8)temp = Mot[j+1];
				else temp = Mot[1];
			}else if(j == 10)
			{
				zm_flag = true;
				if(POMPpin)temp = 1;
				else {temp = 0;
				}
			}else if(j == 9)
			{
				if(!profile_flag)
					profile_flag = 1;
				else{
					if(k == 3)
					{
						profile_flag = 0;
						k = 0;

					}else if(k == 0)
					{
						for (short int j = 1; j < 9; j++)
							Mot[j] = 20;

						POMP = 1;

						profile_flag = 0;
						k = 0;

					}else if(k == 1)
					{
						for (short int j = 1; j < 9; j++)
							Mot[j] = 15;

						profile_flag = 0;
						k = 0;

					}else if(k == 2)
					{
						for (short int j = 1; j < 9; j++)
							Mot[j] = 0;

						POMP = 0;

						profile_flag = 0;
						k = 0;
					}

				}
			}
			click = false;
		}
//		if(menu_out && !ENpin_3){
//			menu_flag = false;
//			menu_out = false;
//			return 0;
//		}
//		if(!menu_out && click)
//			if(!ENpin_3)
//				menu_out = true;

	}
	menu_flag = false;
	menu_out = false;
	return 0;
}

int aflag = 0;

int main(void) {

//	LED_DDR_1 = 1; // enable output pins
//	LED_DDR_2 = 1;
	EN_DDR_3 = 0;
	EN_DDR_4 = 0;
	EN_DDR_5 = 0;
//	LED_DDR_5 = 1;
//	LED_DDR_6 = 1;
//	LED_DDR_7 = 1;
	POMP_DDR = 1;

//	LED_1 = 0; // turn off leds
//	LED_2 = 0;
	EN_3 = 1;
	EN_4 = 1;
	EN_5 = 1;
//	LED_5 = 0;
//	LED_6 = 0;
//	LED_7 = 0;
//	LED_8 = 1;

	MOT_DDR_1 = 1;
	MOT_DDR_2 = 1;
	MOT_DDR_3 = 1;
	MOT_DDR_4 = 1;
	MOT_DDR_5 = 1;
	MOT_DDR_6 = 1;
	MOT_DDR_7 = 1;
	MOT_DDR_8 = 1;

//	LED_1 = 0;
//	LED_2 = 0;
////	LED_3 = 0;
////	LED_4 = 0;
//	LED_5 = 0;
//	LED_6 = 0;
//	LED_7 = 0;
//	LED_8 = 0;

	TCCR0 = 0b101;
	TCNT0 = 101;;

	TCCR1B = 0b00001100;
	TIMSK = 0x11;
	OCR1A = 31;

//	TCCR3B = 0b00001101;
//	TIMSK3 = 0x02;
//	OCR3A = 1;//15625;

//	EICRA = 0x0A;
	MCUCR = 0x0A;
//	EIMSK = 0x03;
	GICR = 0xC0;
//

//	TCCR0B = 0b00000001;
//	TIMSK0 = 0x02;
//	OCR0A = 64;

	lcd_init();
	lcd_puts("1234");
	uart_init((UART_BAUD_SELECT((BAUD),xtalCpu)));
//	LED_4 = 1;

	sei();
//	LED_6 = 0;
	lcd_blank();
	lcd_xy(0,0);
	lcd_puts("ab");
//	UART_sendc('o');
//	Mot[1] = 19;
//	lcd_blank();

	lcd_xy(0,0);
	lcd_puts("GPU:  '  CPU:  '");

	while (1) {
//		uart_timeout_b = true;
//		UART_sendc('o');
		if ((bufor = uart_readc()) != 0) {
//			uart_timeout_b = false;
			switch (bufor) {
			case 'd':

				_delay_ms(50);
//				LED_8 = 0;
//				UART_sendc('o');
				lcd_xy(4,0);
				strcpy(t_gpuc, uart_gets(2));
				lcd_puts(t_gpuc);

				lcd_xy(13,0);
				strcpy(t_cpuc, uart_gets(2));
				lcd_puts(t_cpuc);

				if(atoi(t_cpu) >= 50){
					POMP = 1;
					aflag = 1;
				}
				if(aflag == 1 && (atoi(t_cpu) < 50)){
					POMP = 0;
					aflag = 0;
				}

				lcd_xy(0,1);
				strcpy(clock, uart_gets(5));
				lcd_puts(clock);

				if((clock[2] == '0' && clock[3] == '0') || (clock[2] == '3' && clock[3] == '0'))
					POMP = 1;

				if((clock[2] == '0' && clock[3] == '1') || (clock[2] == '3' && clock[3] == '1'))
					POMP = 0;

				lcd_xy(6,1);
				strcpy(date, uart_gets(10));
				lcd_puts(date);

				break;
			case 's':
				_delay_ms(50);
//				LED_8 = 1;
//				UART_sendc('c');
				bufor = uart_readc();

				switch (bufor) {
				case '0':

					break;

				case '1':
//					UART_sendc('k');
					bufor = uart_readc();
					if(bufor == '0')
					{
						strcpy(Mot1c, uart_gets(4));
						auto_flag = false;

						if((atoi(Mot1c) == 100))
							POMP = 1;
						else if((atoi(Mot1c) == 0))
							POMP = 0;

					}else{
					num_el = bufor - 48;
//					lcd_xy(3,0);
//					lcd_lnumber(num_el);
					strcpy(Mot1c, uart_gets(4));
					// 90 100 110 120 130 140 145 150 160
					if((atoi(Mot1c)) < 105)
					{
//						auto_flag = false;
						if (num_el != 9) {
							Mot[num_el] = (atoi(Mot1c) / 5);
//							lcd_lnumber(Mot[1]);
						} else {
							for (short int j = 1; j < 9; j++)
								Mot[j] = (atoi(Mot1c) / 5);
						}


					}else
					{//Mot1_8[8]

						auto_flag = true;
//						lcd_xy(5,0);
//											lcd_lnumber(t_cal);
						///////////////////
//						if(t_cal < 90 )
//							kr = 0;
//						else if(t_cal < 100 )
//							kr = 1;
//						else if(t_cal < 110 )
//							kr = 2;
//						else if(t_cal < 120 )
//							kr = 3;
//						else if(t_cal < 130 )
//							kr = 4;
//						else if(t_cal < 140 )
//							kr = 5;
//						else if(t_cal < 145 )
//							kr = 6;
//						else if(t_cal < 150 )
//							kr = 7;
//						else if(t_cal < 160 )
//							kr = 8;
////						else if(t_cal < 160 )
////							kr = 9;
//
//
//						if (num_el != 9) {
//							Mot[num_el] = Mot1_8s[kr];
////							lcd_lnumber(Mot[1]);
//						} else {
//							for (short int j = 1; j < 9; j++)
//								Mot[j] = Mot1_8s[kr];
//						}
						/////////////////
					}
					}

					uart_puts("OK");
					break;
				default:
					break;
				}

				break;
				////			case '3':
				////
				////				break;
				////			case '4':
				////
				////				break;
				////			case '0':
				////
				////				break;
				////			case 'h':
				//////
				////				break;
				////			case 'l':
				////
				////				break;
			default:
				break;
			}
		}else
			if(menu_flag){
				menu();
				lcd_blank();
				lcd_xy(0,0);
				lcd_puts("GPU:  '  CPU:  '");
			}

//		tu:
//		while(menu_flag)
//		{
//
//			lcd_xy(0,0);
//			lcd_puts(M1_1);
//			lcd_xy(0,1);
//			lcd_puts(M1_2);
//			lcd_xy(7,1);
//			lcd_number(Mot[1]*5);
//			lcd_xy(10,1);
//			lcd_puts(" %");
//			_delay_ms(0);
//
//		}

	}


	return 0;
}


//int yu = 0;//////////

//volatile int Mot1_flag = 0;/////////
volatile short int counter = 0;

uint8_t stan[4] = {0b00, 0b01, 0b10, 0b11};///////
uint8_t stan_poprz, lp;///////


ISR(INT0_vect)
{
//	PORTD |= (1 << 4);
	_delay_us(10);

	if(!(PIND & (1 << 4)) && !(PIND & (1 << 3)))
	{
		if (stan_poprz == 0b01)
			vect = 1;

		else if (stan_poprz == 0b11)
			vect = 2;

		stan_poprz = 0b00;

	}

	if((PIND & (1 << 4)) && !(PIND & (1 << 3)))
	{
		if (stan_poprz == 0b10)
			vect = 1;

		else if (stan_poprz == 0b00)
			vect = 2;

		stan_poprz = 0b01;

	}

	if(!(PIND & (1 << 4)) && (PIND & (1 << 3)))
	{
		if (stan_poprz == 0b11)
			vect = 1;

		else if (stan_poprz == 0b01)
			vect = 2;

		stan_poprz = 0b10;

	}

	if((PIND & (1 << 4)) && (PIND & (1 << 3)))
	{
		if (stan_poprz == 0b00)
			vect = 1;

		else if (stan_poprz == 0b10)
			vect = 2;

		stan_poprz = 0b11;

	}

	obr = true;
//	if(vect == 2){
//		if(Led > 0)
//			Led--;}
////		PORTD |= (1 << 7);
//	else if(vect == 1){
//		if(Led < 20)
//			Led++;}
//		PORTD &= ~(1 << 7);
}

ISR(INT1_vect)
{

	if(!click)
		click = true;
	else
		menu_out = true;

	if(!menu_flag){
		menu_flag = true;
		click = false;
//		menu();
	}

//	PORTD ^= (1 << 4);
//	PORTD &= ~(1 << 4);
//	PORTD &= ~(1 << 6);
//	PORTD &= ~(1 << 7);

//	PORTD ^= (1 << 7);
}

int flag0 = 0;
int flag1 = 0;
ISR(TIMER0_OVF_vect)
{

//	if(uart_timeout_b){
//		uart_timeout++;
//		if(uart_timeout == 10)
//			goto tu;
//	}

	t_gpu = atoi(t_gpuc);
	t_cpu = atoi(t_cpuc);
	t_cal = t_gpu + t_cpu;

	if (flag0 == 300) {
		if (auto_flag) {
			if(t_gpuc[0] == 'G')
			{

			}else if(t_gpuc[0] == 'Z')
			{
				flag1 = 1;
			}else if(flag1 == 1)
			{
			if (t_cal < 90)
				kr = 0;
			else if (t_cal < 100)
				kr = 1;
			else if (t_cal < 110)
				kr = 2;
			else if (t_cal < 120)
				kr = 3;
			else if (t_cal < 130)
				kr = 4;
			else if (t_cal < 140)
				kr = 5;
			else if (t_cal < 145)
				kr = 6;
			else if (t_cal < 150)
				kr = 7;
			else if (t_cal < 160)
				kr = 8;
			//						else if(t_cal < 160 )
			//							kr = 9;


			if (num_el != 9) {
				if (Mot1_8s[kr] >= Mot_minz[num_el])
					Mot[num_el] = Mot1_8s[kr];
				else
					Mot[num_el] = 0;
				//							lcd_lnumber(Mot[1]);
			} else {
				for (short int j = 1; j < 9; j++)
					if (Mot1_8s[kr] >= Mot_minz[j])
						Mot[j] = Mot1_8s[kr];
					else
						Mot[j] = 0;
			}
			flag1 = 0;
		}
		}
		flag0 = 0;
	} else
		flag0++;
}

ISR(TIMER1_COMPA_vect) {

	if (Mot[1] == 0)
		MOT_1 = 0;
	else if (counter <= Mot[1])
		MOT_1 = 1;
	else
		MOT_1 = 0;

	if (Mot[2] == 0)
		MOT_2 = 0;
	else if (counter <= Mot[2])
		MOT_2 = 1;
	else
		MOT_2 = 0;

	if (Mot[3] == 0)
		MOT_3 = 0;
	else if (counter <= Mot[3])
		MOT_3 = 1;
	else
		MOT_3 = 0;

	if (Mot[4] == 0)
		MOT_4 = 0;
	else if (counter <= Mot[4])
		MOT_4 = 1;
	else
		MOT_4 = 0;

	if (Mot[5] == 0)
		MOT_5 = 0;
	else if (counter <= Mot[5])
		MOT_5 = 1;
	else
		MOT_5 = 0;

	if (Mot[6] == 0)
		MOT_6 = 0;
	else if (counter <= Mot[6])
		MOT_6 = 1;
	else
		MOT_6 = 0;

	if (Mot[7] == 0)
		MOT_7 = 0;
	else if (counter <= Mot[7])
		MOT_7 = 1;
	else
		MOT_7 = 0;

	if (Mot[8] == 0)
		MOT_8 = 0;
	else if (counter <= Mot[8])
		MOT_8 = 1;
	else
		MOT_8 = 0;

//	if (Led == 0)
//		LED_8 = 0;
//	else if (counter <= Led)
//		LED_8 = 1;
//	else
//		LED_8 = 0;

	counter++;
	if (counter == 20)
		counter = 0;
}

