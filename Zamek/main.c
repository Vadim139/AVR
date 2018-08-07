/*
 * main.c
 *
 *  Created on: 03-02-2012
 *      Author: Dawid
 */
//Konfiguracja sprzêtowa:
//dioda niebieska - PortB 0
//dioda zielona - PortB 1
//dioda czerwona - PortB 2
//przyciski - PortC 0 - 7
//buzzer - PortB 3

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

//LEDs
#define LED_P	PORTB
#define LED_D	DDRB

#define LED1		0
#define LED2		1
#define LED3		2
#define BUZZ		3

//Switches
#define SW_D   DDRC
#define SW_W   PORTC
#define SW_R   PINC

#define SW1		0
#define SW2		1
#define SW3		2
#define SW4		3
#define SW5		4
#define SW6		5
#define SW7		6
#define SW8		7

volatile int cyfra_odcz; //cyfra odczytana do liczby
volatile char cyfra = 1; //która cyfra
volatile int liczba; //kod w³asciwy
volatile int liczba_odcz; //liczba odczytana
volatile char zatw = 0; //zatwierdzenie wpisanego kodu
volatile char block = 0; //czy kod ju¿ zosta³ zapisany
volatile char zle = 0; //ilosæ b³êdów

int zmianapodst(void) {

	//Podci¹gamy wiersze
	SW_W |= (1 << SW1);
	SW_W |= (1 << SW2);
	SW_W |= (1 << SW3);
	SW_W |= (1 << SW4);

	//Wiersze jako wejscia
	SW_D &= ~(1 << SW1);
	SW_D &= ~(1 << SW2);
	SW_D &= ~(1 << SW3);
	SW_D &= ~(1 << SW4);

	//i kolumny jako wyjcia
	SW_D |= (1 << SW5);
	SW_D |= (1 << SW6);
	SW_D |= (1 << SW7);
	SW_D |= (1 << SW8);

	//Kolumny ustawiamy na 0
	SW_W &= ~(1 << SW5);
	SW_W &= ~(1 << SW6);
	SW_W &= ~(1 << SW7);
	SW_W &= ~(1 << SW8);

	return 0;
}

int zmiana(void) {

	//Podci¹gamy kolumny
	SW_W |= (1 << SW5);
	SW_W |= (1 << SW6);
	SW_W |= (1 << SW7);
	SW_W |= (1 << SW8);

	//Kolumny jako wejscia
	SW_D &= ~(1 << SW5);
	SW_D &= ~(1 << SW6);
	SW_D &= ~(1 << SW7);
	SW_D &= ~(1 << SW8);

	//Wiersze ustawiamy na 0
	SW_W &= ~(1 << SW1);
	SW_W &= ~(1 << SW2);
	SW_W &= ~(1 << SW3);
	SW_W &= ~(1 << SW4);

	//Wiersze jako wyjcia
	SW_D |= (1 << SW1);
	SW_D |= (1 << SW2);
	SW_D |= (1 << SW3);
	SW_D |= (1 << SW4);

	return 0;
}

//BEEP!
int beep(void) {

	int i;

	for (i = 0; i < 375; ++i) {
		LED_P ^= (1 << BUZZ);
		_delay_us(1350);
	}
	LED_P |= (1 << BUZZ);

	return 0;
}

//Liczba sprawdzaj¹ca
int liczba1(void) {

	if (cyfra_odcz < 10) {
		if (cyfra == 1)
			liczba += (cyfra_odcz * 1000);
		if (cyfra == 2)
			liczba += (cyfra_odcz * 100);
		if (cyfra == 3)
			liczba += (cyfra_odcz * 10);
		if (cyfra == 4)
			liczba += (cyfra_odcz * 1);
		cyfra++;
	}
	if (cyfra_odcz == 10)
	{
		liczba = 0;
		cyfra = 1;
	}
	if (cyfra_odcz == 11)
		zatw = 1;
	return 0;
}

//Liczba sprawdzana
int liczba_odcz1(void) {

	if (cyfra_odcz < 10) {
		if (cyfra == 1)
			liczba_odcz += (cyfra_odcz * 1000);
		if (cyfra == 2)
			liczba_odcz += (cyfra_odcz * 100);
		if (cyfra == 3)
			liczba_odcz += (cyfra_odcz * 10);
		if (cyfra == 4)
			liczba_odcz += (cyfra_odcz * 1);
		cyfra++;
	}
	if (cyfra_odcz == 10)
		if (cyfra_odcz == 10)
			{
				liczba_odcz = 0;
				cyfra = 1;
				if (zle >= 3)
					{
						zle = 2;
					}
			}
	if (cyfra_odcz == 11)
		zatw = 1;
	return 0;
}

//Obs³uga przycisków
int klawiatura(void) {

	if (zle >= 3)
	{
		LED_P ^= (1 << LED3);
		beep();
	}

	if ((SW_R & (1 << SW1)) == 0) {

		zmiana();

		if ((SW_R & (1 << SW5)) == 0) {
			if (cyfra < 5) {
				cyfra_odcz = 1;
				if (block == 0)
					liczba1();
				if (block == 1)
					liczba_odcz1();
			}
			beep();
		}
		if ((SW_R & (1 << SW6)) == 0) {
			if (cyfra < 5) {
				cyfra_odcz = 2;
				if (block == 0)
					liczba1();
				if (block == 1)
					liczba_odcz1();
			}
			beep();
		}
		if ((SW_R & (1 << SW7)) == 0) {
			if (cyfra < 5) {
				cyfra_odcz = 3;
				if (block == 0)
					liczba1();
				if (block == 1)
					liczba_odcz1();
			}
			beep();
		}
		if ((SW_R & (1 << SW8)) == 0) {
			beep();
		}
		zmianapodst();
	}
	if ((SW_R & (1 << SW2)) == 0) {

		zmiana();

		if ((SW_R & (1 << SW5)) == 0) {
			if (cyfra < 5) {
				cyfra_odcz = 4;
				if (block == 0)
					liczba1();
				if (block == 1)
					liczba_odcz1();
			}
			beep();
		}
		if ((SW_R & (1 << SW6)) == 0) {
			if (cyfra < 5) {
				cyfra_odcz = 5;
				if (block == 0)
					liczba1();
				if (block == 1)
					liczba_odcz1();
			}
			beep();
		}
		if ((SW_R & (1 << SW7)) == 0) {
			if (cyfra < 5) {
				cyfra_odcz = 6;
				if (block == 0)
					liczba1();
				if (block == 1)
					liczba_odcz1();
			}
			beep();
		}
		if ((SW_R & (1 << SW8)) == 0) {
			beep();
		}
		zmianapodst();
	}
	if ((SW_R & (1 << SW3)) == 0) {

		zmiana();

		if ((SW_R & (1 << SW5)) == 0) {
			if (cyfra < 5) {
				cyfra_odcz = 7;
				if (block == 0)
					liczba1();
				if (block == 1)
					liczba_odcz1();
			}
			beep();
		}
		if ((SW_R & (1 << SW6)) == 0) {
			if (cyfra < 5) {
				cyfra_odcz = 8;
				if (block == 0)
					liczba1();
				if (block == 1)
					liczba_odcz1();
			}
			beep();
		}
		if ((SW_R & (1 << SW7)) == 0) {
			if (cyfra < 5) {
				cyfra_odcz = 9;
				if (block == 0)
					liczba1();
				if (block == 1)
					liczba_odcz1();
			}
			beep();
		}
		if ((SW_R & (1 << SW8)) == 0) {
			beep();
		}
		zmianapodst();
	}
	if ((SW_R & (1 << SW4)) == 0) {

		zmiana();

		if ((SW_R & (1 << SW5)) == 0) {
			if (cyfra < 5) {
				cyfra_odcz = 10;
				if (block == 0)
					liczba1();
				if (block == 1)
					liczba_odcz1();
			}
			beep();
		}
		if ((SW_R & (1 << SW6)) == 0) {
			if (cyfra < 5) {
				cyfra_odcz = 0;
				if (block == 0)
					liczba1();
				if (block == 1)
					liczba_odcz1();
			}
			beep();
		}
		if ((SW_R & (1 << SW7)) == 0) {
			if (cyfra < 5) {
				cyfra_odcz = 11;
				if (block == 0)
					liczba1();
				if (block == 1)
					liczba_odcz1();
			}
			beep();
		}
		if ((SW_R & (1 << SW8)) == 0) {
			beep();
		}
		zmianapodst();
	}
	return 0;

}

int main(void) {

	//Przyciski jako wejscia
	SW_D &= ~(1 << SW1);
	SW_D &= ~(1 << SW2);
	SW_D &= ~(1 << SW3);
	SW_D &= ~(1 << SW4);
	//		i wyjcia
	SW_D |= (1 << SW5);
	SW_D |= (1 << SW6);
	SW_D |= (1 << SW7);
	SW_D |= (1 << SW8);

	//Podci¹gamy
	SW_W |= (1 << SW1);
	SW_W |= (1 << SW2);
	SW_W |= (1 << SW3);
	SW_W |= (1 << SW4);
	//		ustawiamy na 0
	SW_W &= ~(1 << SW5);
	SW_W &= ~(1 << SW6);
	SW_W &= ~(1 << SW7);
	SW_W &= ~(1 << SW8);

	LED_D |= (1 << LED1);
	LED_D |= (1 << LED2);
	LED_D |= (1 << LED3);
	LED_D |= (1 << BUZZ);
	LED_P &= ~(1 << LED2) | (1 << LED3);
	LED_P |= (1 << LED1);
	LED_P |= (1 << BUZZ);

	int D1 = 0;
	int i2 = 0;

	while (cyfra < 5) {
		if (D1 == 500) {
			LED_P ^= (1 << LED1);
			D1 = 0;
		}
		D1++;
		klawiatura();

		if (cyfra == 5)
			block = 1;
	}

//Pêtla g³ówna
	while (1) {
		LED_P |= (1 << LED1);

		if (cyfra == 5) {
			block = 1;
			cyfra = 1;
		}
		klawiatura();
		if (zatw == 1) {
			if (liczba == liczba_odcz) {
				LED_P |= (1 << LED2);
				for(i2 = 0;i2 < 4;i2++)
				{
					beep();
					_delay_ms(300);
				}
				LED_P |= (1 << BUZZ);
				zatw = 0;
				zle = 0;
				LED_P &= ~(1 << LED3);
				_delay_ms(5000);
				LED_P &= ~(1 << LED2);
			} else if (liczba != liczba_odcz)
			{
				LED_P ^= (1 << LED3);
				for(i2 = 0;i2<8;i2++)
				{
					beep();
					LED_P ^= (1 << LED3);
				}
				LED_P |= (1 << BUZZ);
				zatw = 0;
				zle++;
				LED_P |= (1 << LED3);
				_delay_ms(5000);
				LED_P &= ~(1 << LED3);
			}

		}

	}

	return 0;
}
